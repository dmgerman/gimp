begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<mypaint-surface.h>
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrushsurface.h"
end_include

begin_struct
DECL|struct|_GimpMybrushSurface
struct|struct
name|_GimpMybrushSurface
block|{
DECL|member|surface
name|MyPaintSurface
name|surface
decl_stmt|;
DECL|member|buffer
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
DECL|member|dirty
name|GeglRectangle
name|dirty
decl_stmt|;
DECL|member|component_mask
name|GimpComponentMask
name|component_mask
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* --- Taken from mypaint-tiled-surface.c --- */
end_comment

begin_function
specifier|static
specifier|inline
name|float
DECL|function|calculate_rr (int xp,int yp,float x,float y,float aspect_ratio,float sn,float cs,float one_over_radius2)
name|calculate_rr
parameter_list|(
name|int
name|xp
parameter_list|,
name|int
name|yp
parameter_list|,
name|float
name|x
parameter_list|,
name|float
name|y
parameter_list|,
name|float
name|aspect_ratio
parameter_list|,
name|float
name|sn
parameter_list|,
name|float
name|cs
parameter_list|,
name|float
name|one_over_radius2
parameter_list|)
block|{
comment|/* code duplication, see brush::count_dabs_to() */
specifier|const
name|float
name|yy
init|=
operator|(
name|yp
operator|+
literal|0.5f
operator|-
name|y
operator|)
decl_stmt|;
specifier|const
name|float
name|xx
init|=
operator|(
name|xp
operator|+
literal|0.5f
operator|-
name|x
operator|)
decl_stmt|;
specifier|const
name|float
name|yyr
init|=
operator|(
name|yy
operator|*
name|cs
operator|-
name|xx
operator|*
name|sn
operator|)
operator|*
name|aspect_ratio
decl_stmt|;
specifier|const
name|float
name|xxr
init|=
name|yy
operator|*
name|sn
operator|+
name|xx
operator|*
name|cs
decl_stmt|;
specifier|const
name|float
name|rr
init|=
operator|(
name|yyr
operator|*
name|yyr
operator|+
name|xxr
operator|*
name|xxr
operator|)
operator|*
name|one_over_radius2
decl_stmt|;
comment|/* rr is in range 0.0..1.0*sqrt(2) */
return|return
name|rr
return|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|float
DECL|function|calculate_r_sample (float x,float y,float aspect_ratio,float sn,float cs)
name|calculate_r_sample
parameter_list|(
name|float
name|x
parameter_list|,
name|float
name|y
parameter_list|,
name|float
name|aspect_ratio
parameter_list|,
name|float
name|sn
parameter_list|,
name|float
name|cs
parameter_list|)
block|{
specifier|const
name|float
name|yyr
init|=
operator|(
name|y
operator|*
name|cs
operator|-
name|x
operator|*
name|sn
operator|)
operator|*
name|aspect_ratio
decl_stmt|;
specifier|const
name|float
name|xxr
init|=
name|y
operator|*
name|sn
operator|+
name|x
operator|*
name|cs
decl_stmt|;
specifier|const
name|float
name|r
init|=
operator|(
name|yyr
operator|*
name|yyr
operator|+
name|xxr
operator|*
name|xxr
operator|)
decl_stmt|;
return|return
name|r
return|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|float
DECL|function|sign_point_in_line (float px,float py,float vx,float vy)
name|sign_point_in_line
parameter_list|(
name|float
name|px
parameter_list|,
name|float
name|py
parameter_list|,
name|float
name|vx
parameter_list|,
name|float
name|vy
parameter_list|)
block|{
return|return
operator|(
name|px
operator|-
name|vx
operator|)
operator|*
operator|(
operator|-
name|vy
operator|)
operator|-
operator|(
name|vx
operator|)
operator|*
operator|(
name|py
operator|-
name|vy
operator|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|closest_point_to_line (float lx,float ly,float px,float py,float * ox,float * oy)
name|closest_point_to_line
parameter_list|(
name|float
name|lx
parameter_list|,
name|float
name|ly
parameter_list|,
name|float
name|px
parameter_list|,
name|float
name|py
parameter_list|,
name|float
modifier|*
name|ox
parameter_list|,
name|float
modifier|*
name|oy
parameter_list|)
block|{
specifier|const
name|float
name|l2
init|=
name|lx
operator|*
name|lx
operator|+
name|ly
operator|*
name|ly
decl_stmt|;
specifier|const
name|float
name|ltp_dot
init|=
name|px
operator|*
name|lx
operator|+
name|py
operator|*
name|ly
decl_stmt|;
specifier|const
name|float
name|t
init|=
name|ltp_dot
operator|/
name|l2
decl_stmt|;
operator|*
name|ox
operator|=
name|lx
operator|*
name|t
expr_stmt|;
operator|*
name|oy
operator|=
name|ly
operator|*
name|t
expr_stmt|;
block|}
end_function

begin_comment
comment|/* This works by taking the visibility at the nearest point  * and dividing by 1.0 + delta.  *  * - nearest point: point where the dab has more influence  * - farthest point: point at a fixed distance away from  *                   the nearest point  * - delta: how much occluded is the farthest point relative  *          to the nearest point  */
end_comment

begin_function
specifier|static
specifier|inline
name|float
DECL|function|calculate_rr_antialiased (int xp,int yp,float x,float y,float aspect_ratio,float sn,float cs,float one_over_radius2,float r_aa_start)
name|calculate_rr_antialiased
parameter_list|(
name|int
name|xp
parameter_list|,
name|int
name|yp
parameter_list|,
name|float
name|x
parameter_list|,
name|float
name|y
parameter_list|,
name|float
name|aspect_ratio
parameter_list|,
name|float
name|sn
parameter_list|,
name|float
name|cs
parameter_list|,
name|float
name|one_over_radius2
parameter_list|,
name|float
name|r_aa_start
parameter_list|)
block|{
comment|/* calculate pixel position and borders in a way      * that the dab's center is always at zero */
name|float
name|pixel_right
init|=
name|x
operator|-
operator|(
name|float
operator|)
name|xp
decl_stmt|;
name|float
name|pixel_bottom
init|=
name|y
operator|-
operator|(
name|float
operator|)
name|yp
decl_stmt|;
name|float
name|pixel_center_x
init|=
name|pixel_right
operator|-
literal|0.5f
decl_stmt|;
name|float
name|pixel_center_y
init|=
name|pixel_bottom
operator|-
literal|0.5f
decl_stmt|;
name|float
name|pixel_left
init|=
name|pixel_right
operator|-
literal|1.0f
decl_stmt|;
name|float
name|pixel_top
init|=
name|pixel_bottom
operator|-
literal|1.0f
decl_stmt|;
name|float
name|nearest_x
decl_stmt|,
name|nearest_y
decl_stmt|;
comment|/* nearest to origin, but still inside pixel */
name|float
name|farthest_x
decl_stmt|,
name|farthest_y
decl_stmt|;
comment|/* farthest from origin, but still inside pixel */
name|float
name|r_near
decl_stmt|,
name|r_far
decl_stmt|,
name|rr_near
decl_stmt|,
name|rr_far
decl_stmt|;
name|float
name|center_sign
decl_stmt|,
name|rad_area_1
decl_stmt|,
name|visibilityNear
decl_stmt|,
name|delta
decl_stmt|,
name|delta2
decl_stmt|;
comment|/* Dab's center is inside pixel? */
if|if
condition|(
name|pixel_left
operator|<
literal|0
operator|&&
name|pixel_right
operator|>
literal|0
operator|&&
name|pixel_top
operator|<
literal|0
operator|&&
name|pixel_bottom
operator|>
literal|0
condition|)
block|{
name|nearest_x
operator|=
literal|0
expr_stmt|;
name|nearest_y
operator|=
literal|0
expr_stmt|;
name|r_near
operator|=
name|rr_near
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|closest_point_to_line
argument_list|(
name|cs
argument_list|,
name|sn
argument_list|,
name|pixel_center_x
argument_list|,
name|pixel_center_y
argument_list|,
operator|&
name|nearest_x
argument_list|,
operator|&
name|nearest_y
argument_list|)
expr_stmt|;
name|nearest_x
operator|=
name|CLAMP
argument_list|(
name|nearest_x
argument_list|,
name|pixel_left
argument_list|,
name|pixel_right
argument_list|)
expr_stmt|;
name|nearest_y
operator|=
name|CLAMP
argument_list|(
name|nearest_y
argument_list|,
name|pixel_top
argument_list|,
name|pixel_bottom
argument_list|)
expr_stmt|;
comment|/* XXX: precision of "nearest" values could be improved          * by intersecting the line that goes from nearest_x/Y to 0          * with the pixel's borders here, however the improvements          * would probably not justify the perdormance cost.          */
name|r_near
operator|=
name|calculate_r_sample
argument_list|(
name|nearest_x
argument_list|,
name|nearest_y
argument_list|,
name|aspect_ratio
argument_list|,
name|sn
argument_list|,
name|cs
argument_list|)
expr_stmt|;
name|rr_near
operator|=
name|r_near
operator|*
name|one_over_radius2
expr_stmt|;
block|}
comment|/* out of dab's reach? */
if|if
condition|(
name|rr_near
operator|>
literal|1.0f
condition|)
return|return
name|rr_near
return|;
comment|/* check on which side of the dab's line is the pixel center */
name|center_sign
operator|=
name|sign_point_in_line
argument_list|(
name|pixel_center_x
argument_list|,
name|pixel_center_y
argument_list|,
name|cs
argument_list|,
operator|-
name|sn
argument_list|)
expr_stmt|;
comment|/* radius of a circle with area=1      *   A = pi * r * r      *   r = sqrt(1/pi)      */
name|rad_area_1
operator|=
name|sqrtf
argument_list|(
literal|1.0f
operator|/
name|M_PI
argument_list|)
expr_stmt|;
comment|/* center is below dab */
if|if
condition|(
name|center_sign
operator|<
literal|0
condition|)
block|{
name|farthest_x
operator|=
name|nearest_x
operator|-
name|sn
operator|*
name|rad_area_1
expr_stmt|;
name|farthest_y
operator|=
name|nearest_y
operator|+
name|cs
operator|*
name|rad_area_1
expr_stmt|;
block|}
comment|/* above dab */
else|else
block|{
name|farthest_x
operator|=
name|nearest_x
operator|+
name|sn
operator|*
name|rad_area_1
expr_stmt|;
name|farthest_y
operator|=
name|nearest_y
operator|-
name|cs
operator|*
name|rad_area_1
expr_stmt|;
block|}
name|r_far
operator|=
name|calculate_r_sample
argument_list|(
name|farthest_x
argument_list|,
name|farthest_y
argument_list|,
name|aspect_ratio
argument_list|,
name|sn
argument_list|,
name|cs
argument_list|)
expr_stmt|;
name|rr_far
operator|=
name|r_far
operator|*
name|one_over_radius2
expr_stmt|;
comment|/* check if we can skip heavier AA */
if|if
condition|(
name|r_far
operator|<
name|r_aa_start
condition|)
return|return
operator|(
name|rr_far
operator|+
name|rr_near
operator|)
operator|*
literal|0.5f
return|;
comment|/* calculate AA approximate */
name|visibilityNear
operator|=
literal|1.0f
operator|-
name|rr_near
expr_stmt|;
name|delta
operator|=
name|rr_far
operator|-
name|rr_near
expr_stmt|;
name|delta2
operator|=
literal|1.0f
operator|+
name|delta
expr_stmt|;
name|visibilityNear
operator|/=
name|delta2
expr_stmt|;
return|return
literal|1.0f
operator|-
name|visibilityNear
return|;
block|}
end_function

begin_comment
comment|/* -- end mypaint code */
end_comment

begin_function
specifier|static
specifier|inline
name|float
DECL|function|calculate_alpha_for_rr (float rr,float hardness,float slope1,float slope2)
name|calculate_alpha_for_rr
parameter_list|(
name|float
name|rr
parameter_list|,
name|float
name|hardness
parameter_list|,
name|float
name|slope1
parameter_list|,
name|float
name|slope2
parameter_list|)
block|{
if|if
condition|(
name|rr
operator|>
literal|1.0f
condition|)
return|return
literal|0.0f
return|;
elseif|else
if|if
condition|(
name|rr
operator|<=
name|hardness
condition|)
return|return
literal|1.0f
operator|+
name|rr
operator|*
name|slope1
return|;
else|else
return|return
name|rr
operator|*
name|slope2
operator|-
name|slope2
return|;
block|}
end_function

begin_function
specifier|static
name|GeglRectangle
DECL|function|calculate_dab_roi (float x,float y,float radius)
name|calculate_dab_roi
parameter_list|(
name|float
name|x
parameter_list|,
name|float
name|y
parameter_list|,
name|float
name|radius
parameter_list|)
block|{
name|int
name|x0
init|=
name|floor
argument_list|(
name|x
operator|-
name|radius
argument_list|)
decl_stmt|;
name|int
name|x1
init|=
name|ceil
argument_list|(
name|x
operator|+
name|radius
argument_list|)
decl_stmt|;
name|int
name|y0
init|=
name|floor
argument_list|(
name|y
operator|-
name|radius
argument_list|)
decl_stmt|;
name|int
name|y1
init|=
name|ceil
argument_list|(
name|y
operator|+
name|radius
argument_list|)
decl_stmt|;
return|return
operator|*
name|GEGL_RECTANGLE
argument_list|(
name|x0
argument_list|,
name|y0
argument_list|,
name|x1
operator|-
name|x0
argument_list|,
name|y1
operator|-
name|y0
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mypaint_surface_get_color (MyPaintSurface * base_surface,float x,float y,float radius,float * color_r,float * color_g,float * color_b,float * color_a)
name|gimp_mypaint_surface_get_color
parameter_list|(
name|MyPaintSurface
modifier|*
name|base_surface
parameter_list|,
name|float
name|x
parameter_list|,
name|float
name|y
parameter_list|,
name|float
name|radius
parameter_list|,
name|float
modifier|*
name|color_r
parameter_list|,
name|float
modifier|*
name|color_g
parameter_list|,
name|float
modifier|*
name|color_b
parameter_list|,
name|float
modifier|*
name|color_a
parameter_list|)
block|{
name|GimpMybrushSurface
modifier|*
name|surface
init|=
operator|(
name|GimpMybrushSurface
operator|*
operator|)
name|base_surface
decl_stmt|;
name|GeglRectangle
name|dabRect
decl_stmt|;
if|if
condition|(
name|radius
operator|<
literal|1.0f
condition|)
name|radius
operator|=
literal|1.0f
expr_stmt|;
name|dabRect
operator|=
name|calculate_dab_roi
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|radius
argument_list|)
expr_stmt|;
operator|*
name|color_r
operator|=
literal|0.0f
expr_stmt|;
operator|*
name|color_g
operator|=
literal|0.0f
expr_stmt|;
operator|*
name|color_b
operator|=
literal|0.0f
expr_stmt|;
operator|*
name|color_a
operator|=
literal|0.0f
expr_stmt|;
if|if
condition|(
name|dabRect
operator|.
name|width
operator|>
literal|0
operator|||
name|dabRect
operator|.
name|height
operator|>
literal|0
condition|)
block|{
specifier|const
name|float
name|one_over_radius2
init|=
literal|1.0f
operator|/
operator|(
name|radius
operator|*
name|radius
operator|)
decl_stmt|;
name|float
name|sum_weight
init|=
literal|0.0f
decl_stmt|;
name|float
name|sum_r
init|=
literal|0.0f
decl_stmt|;
name|float
name|sum_g
init|=
literal|0.0f
decl_stmt|;
name|float
name|sum_b
init|=
literal|0.0f
decl_stmt|;
name|float
name|sum_a
init|=
literal|0.0f
decl_stmt|;
comment|/* Read in clamp mode to avoid transparency bleeding in at the edges */
name|GeglBufferIterator
modifier|*
name|iter
init|=
name|gegl_buffer_iterator_new
argument_list|(
name|surface
operator|->
name|buffer
argument_list|,
operator|&
name|dabRect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"R'aG'aB'aA float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_CLAMP
argument_list|)
decl_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|float
modifier|*
name|pixel
init|=
operator|(
name|float
operator|*
operator|)
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|int
name|iy
decl_stmt|,
name|ix
decl_stmt|;
for|for
control|(
name|iy
operator|=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|y
init|;
name|iy
operator|<
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|y
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|height
condition|;
name|iy
operator|++
control|)
block|{
name|float
name|yy
init|=
operator|(
name|iy
operator|+
literal|0.5f
operator|-
name|y
operator|)
decl_stmt|;
for|for
control|(
name|ix
operator|=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|x
init|;
name|ix
operator|<
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|x
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|width
condition|;
name|ix
operator|++
control|)
block|{
comment|/* pixel_weight == a standard dab with hardness = 0.5, aspect_ratio = 1.0, and angle = 0.0 */
name|float
name|xx
init|=
operator|(
name|ix
operator|+
literal|0.5f
operator|-
name|x
operator|)
decl_stmt|;
name|float
name|rr
init|=
operator|(
name|yy
operator|*
name|yy
operator|+
name|xx
operator|*
name|xx
operator|)
operator|*
name|one_over_radius2
decl_stmt|;
name|float
name|pixel_weight
init|=
literal|0.0f
decl_stmt|;
if|if
condition|(
name|rr
operator|<=
literal|1.0f
condition|)
name|pixel_weight
operator|=
literal|1.0f
operator|-
name|rr
expr_stmt|;
name|sum_r
operator|+=
name|pixel_weight
operator|*
name|pixel
index|[
name|RED
index|]
expr_stmt|;
name|sum_g
operator|+=
name|pixel_weight
operator|*
name|pixel
index|[
name|GREEN
index|]
expr_stmt|;
name|sum_b
operator|+=
name|pixel_weight
operator|*
name|pixel
index|[
name|BLUE
index|]
expr_stmt|;
name|sum_a
operator|+=
name|pixel_weight
operator|*
name|pixel
index|[
name|ALPHA
index|]
expr_stmt|;
name|sum_weight
operator|+=
name|pixel_weight
expr_stmt|;
name|pixel
operator|+=
literal|4
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|sum_a
operator|>
literal|0.0f
operator|&&
name|sum_weight
operator|>
literal|0.0f
condition|)
block|{
name|sum_r
operator|/=
name|sum_weight
expr_stmt|;
name|sum_g
operator|/=
name|sum_weight
expr_stmt|;
name|sum_b
operator|/=
name|sum_weight
expr_stmt|;
name|sum_a
operator|/=
name|sum_weight
expr_stmt|;
name|sum_r
operator|/=
name|sum_a
expr_stmt|;
name|sum_g
operator|/=
name|sum_a
expr_stmt|;
name|sum_b
operator|/=
name|sum_a
expr_stmt|;
comment|/* FIXME: Clamping is wrong because GEGL allows alpha> 1, this should probably re-multipy things */
operator|*
name|color_r
operator|=
name|CLAMP
argument_list|(
name|sum_r
argument_list|,
literal|0.0f
argument_list|,
literal|1.0f
argument_list|)
expr_stmt|;
operator|*
name|color_g
operator|=
name|CLAMP
argument_list|(
name|sum_g
argument_list|,
literal|0.0f
argument_list|,
literal|1.0f
argument_list|)
expr_stmt|;
operator|*
name|color_b
operator|=
name|CLAMP
argument_list|(
name|sum_b
argument_list|,
literal|0.0f
argument_list|,
literal|1.0f
argument_list|)
expr_stmt|;
operator|*
name|color_a
operator|=
name|CLAMP
argument_list|(
name|sum_a
argument_list|,
literal|0.0f
argument_list|,
literal|1.0f
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|gimp_mypaint_surface_draw_dab (MyPaintSurface * base_surface,float x,float y,float radius,float color_r,float color_g,float color_b,float opaque,float hardness,float color_a,float aspect_ratio,float angle,float lock_alpha,float colorize)
name|gimp_mypaint_surface_draw_dab
parameter_list|(
name|MyPaintSurface
modifier|*
name|base_surface
parameter_list|,
name|float
name|x
parameter_list|,
name|float
name|y
parameter_list|,
name|float
name|radius
parameter_list|,
name|float
name|color_r
parameter_list|,
name|float
name|color_g
parameter_list|,
name|float
name|color_b
parameter_list|,
name|float
name|opaque
parameter_list|,
name|float
name|hardness
parameter_list|,
name|float
name|color_a
parameter_list|,
name|float
name|aspect_ratio
parameter_list|,
name|float
name|angle
parameter_list|,
name|float
name|lock_alpha
parameter_list|,
name|float
name|colorize
parameter_list|)
block|{
name|GimpMybrushSurface
modifier|*
name|surface
init|=
operator|(
name|GimpMybrushSurface
operator|*
operator|)
name|base_surface
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|GeglRectangle
name|dabRect
decl_stmt|;
name|GimpComponentMask
name|component_mask
init|=
name|surface
operator|->
name|component_mask
decl_stmt|;
specifier|const
name|float
name|one_over_radius2
init|=
literal|1.0f
operator|/
operator|(
name|radius
operator|*
name|radius
operator|)
decl_stmt|;
specifier|const
name|double
name|angle_rad
init|=
name|angle
operator|/
literal|360
operator|*
literal|2
operator|*
name|M_PI
decl_stmt|;
specifier|const
name|float
name|cs
init|=
name|cos
argument_list|(
name|angle_rad
argument_list|)
decl_stmt|;
specifier|const
name|float
name|sn
init|=
name|sin
argument_list|(
name|angle_rad
argument_list|)
decl_stmt|;
name|float
name|segment1_slope
decl_stmt|;
name|float
name|segment2_slope
decl_stmt|;
name|float
name|r_aa_start
decl_stmt|;
name|float
name|mixbuf
index|[
literal|4
index|]
decl_stmt|;
name|hardness
operator|=
name|CLAMP
argument_list|(
name|hardness
argument_list|,
literal|0.0f
argument_list|,
literal|1.0f
argument_list|)
expr_stmt|;
name|segment1_slope
operator|=
operator|-
operator|(
literal|1.0f
operator|/
name|hardness
operator|-
literal|1.0f
operator|)
expr_stmt|;
name|segment2_slope
operator|=
operator|-
name|hardness
operator|/
operator|(
literal|1.0f
operator|-
name|hardness
operator|)
expr_stmt|;
name|aspect_ratio
operator|=
name|MAX
argument_list|(
literal|1.0f
argument_list|,
name|aspect_ratio
argument_list|)
expr_stmt|;
name|r_aa_start
operator|=
name|radius
operator|-
literal|1.0f
expr_stmt|;
name|r_aa_start
operator|=
name|MAX
argument_list|(
name|r_aa_start
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|r_aa_start
operator|=
operator|(
name|r_aa_start
operator|*
name|r_aa_start
operator|)
operator|/
name|aspect_ratio
expr_stmt|;
comment|/* FIXME: This should use the real matrix values to trim aspect_ratio dabs */
name|dabRect
operator|=
name|calculate_dab_roi
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|radius
argument_list|)
expr_stmt|;
name|gegl_rectangle_intersect
argument_list|(
operator|&
name|dabRect
argument_list|,
operator|&
name|dabRect
argument_list|,
name|gegl_buffer_get_extent
argument_list|(
name|surface
operator|->
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dabRect
operator|.
name|width
operator|<=
literal|0
operator|||
name|dabRect
operator|.
name|height
operator|<=
literal|0
condition|)
return|return
literal|0
return|;
name|gegl_rectangle_bounding_box
argument_list|(
operator|&
name|surface
operator|->
name|dirty
argument_list|,
operator|&
name|surface
operator|->
name|dirty
argument_list|,
operator|&
name|dabRect
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|surface
operator|->
name|buffer
argument_list|,
operator|&
name|dabRect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_READWRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|float
modifier|*
name|pixel
init|=
operator|(
name|float
operator|*
operator|)
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|int
name|iy
decl_stmt|,
name|ix
decl_stmt|;
for|for
control|(
name|iy
operator|=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|y
init|;
name|iy
operator|<
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|y
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|height
condition|;
name|iy
operator|++
control|)
block|{
for|for
control|(
name|ix
operator|=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|x
init|;
name|ix
operator|<
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|x
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|width
condition|;
name|ix
operator|++
control|)
block|{
name|float
name|rr
decl_stmt|,
name|alpha
decl_stmt|,
name|dst_alpha
decl_stmt|,
name|a
decl_stmt|;
name|float
modifier|*
name|dst_pixel
init|=
operator|(
name|component_mask
operator|!=
name|GIMP_COMPONENT_MASK_ALL
operator|)
condition|?
name|mixbuf
else|:
name|pixel
decl_stmt|;
if|if
condition|(
name|radius
operator|<
literal|3.0f
condition|)
name|rr
operator|=
name|calculate_rr_antialiased
argument_list|(
name|ix
argument_list|,
name|iy
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|aspect_ratio
argument_list|,
name|sn
argument_list|,
name|cs
argument_list|,
name|one_over_radius2
argument_list|,
name|r_aa_start
argument_list|)
expr_stmt|;
else|else
name|rr
operator|=
name|calculate_rr
argument_list|(
name|ix
argument_list|,
name|iy
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|aspect_ratio
argument_list|,
name|sn
argument_list|,
name|cs
argument_list|,
name|one_over_radius2
argument_list|)
expr_stmt|;
name|alpha
operator|=
name|calculate_alpha_for_rr
argument_list|(
name|rr
argument_list|,
name|hardness
argument_list|,
name|segment1_slope
argument_list|,
name|segment2_slope
argument_list|)
operator|*
name|opaque
expr_stmt|;
name|dst_alpha
operator|=
name|pixel
index|[
name|ALPHA
index|]
expr_stmt|;
comment|/* a = alpha * color_a + dst_alpha * (1.0f - alpha);                * which converts to: */
name|a
operator|=
name|alpha
operator|*
operator|(
name|color_a
operator|-
name|dst_alpha
operator|)
operator|+
name|dst_alpha
expr_stmt|;
if|if
condition|(
name|a
operator|>
literal|0.0f
condition|)
block|{
comment|/* By definition the ratio between each color[] and pixel[] component in a non-pre-multipled blend always sums to 1.0f.                    * Originaly this would have been "(color[n] * alpha * color_a + pixel[n] * dst_alpha * (1.0f - alpha)) / a",                    * instead we only calculate the cheaper term. */
name|float
name|src_term
init|=
operator|(
name|alpha
operator|*
name|color_a
operator|)
operator|/
name|a
decl_stmt|;
name|float
name|dst_term
init|=
literal|1.0f
operator|-
name|src_term
decl_stmt|;
name|dst_pixel
index|[
name|RED
index|]
operator|=
name|color_r
operator|*
name|src_term
operator|+
name|pixel
index|[
name|RED
index|]
operator|*
name|dst_term
expr_stmt|;
name|dst_pixel
index|[
name|GREEN
index|]
operator|=
name|color_g
operator|*
name|src_term
operator|+
name|pixel
index|[
name|GREEN
index|]
operator|*
name|dst_term
expr_stmt|;
name|dst_pixel
index|[
name|BLUE
index|]
operator|=
name|color_b
operator|*
name|src_term
operator|+
name|pixel
index|[
name|BLUE
index|]
operator|*
name|dst_term
expr_stmt|;
block|}
name|dst_pixel
index|[
name|ALPHA
index|]
operator|=
name|a
expr_stmt|;
comment|/* FIXME: Implement mypaint style lock-alpha mode */
comment|/* FIXME: Implement colorize mode */
if|if
condition|(
name|component_mask
operator|!=
name|GIMP_COMPONENT_MASK_ALL
condition|)
block|{
if|if
condition|(
name|component_mask
operator|&
name|GIMP_COMPONENT_MASK_RED
condition|)
name|pixel
index|[
name|RED
index|]
operator|=
name|mixbuf
index|[
name|RED
index|]
expr_stmt|;
if|if
condition|(
name|component_mask
operator|&
name|GIMP_COMPONENT_MASK_GREEN
condition|)
name|pixel
index|[
name|GREEN
index|]
operator|=
name|mixbuf
index|[
name|GREEN
index|]
expr_stmt|;
if|if
condition|(
name|component_mask
operator|&
name|GIMP_COMPONENT_MASK_BLUE
condition|)
name|pixel
index|[
name|BLUE
index|]
operator|=
name|mixbuf
index|[
name|BLUE
index|]
expr_stmt|;
if|if
condition|(
name|component_mask
operator|&
name|GIMP_COMPONENT_MASK_ALPHA
condition|)
name|pixel
index|[
name|ALPHA
index|]
operator|=
name|mixbuf
index|[
name|ALPHA
index|]
expr_stmt|;
block|}
name|pixel
operator|+=
literal|4
expr_stmt|;
block|}
block|}
block|}
return|return
literal|1
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mypaint_surface_begin_atomic (MyPaintSurface * base_surface)
name|gimp_mypaint_surface_begin_atomic
parameter_list|(
name|MyPaintSurface
modifier|*
name|base_surface
parameter_list|)
block|{  }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mypaint_surface_end_atomic (MyPaintSurface * base_surface,MyPaintRectangle * roi)
name|gimp_mypaint_surface_end_atomic
parameter_list|(
name|MyPaintSurface
modifier|*
name|base_surface
parameter_list|,
name|MyPaintRectangle
modifier|*
name|roi
parameter_list|)
block|{
name|GimpMybrushSurface
modifier|*
name|surface
init|=
operator|(
name|GimpMybrushSurface
operator|*
operator|)
name|base_surface
decl_stmt|;
name|roi
operator|->
name|x
operator|=
name|surface
operator|->
name|dirty
operator|.
name|x
expr_stmt|;
name|roi
operator|->
name|y
operator|=
name|surface
operator|->
name|dirty
operator|.
name|y
expr_stmt|;
name|roi
operator|->
name|width
operator|=
name|surface
operator|->
name|dirty
operator|.
name|width
expr_stmt|;
name|roi
operator|->
name|height
operator|=
name|surface
operator|->
name|dirty
operator|.
name|height
expr_stmt|;
name|surface
operator|->
name|dirty
operator|=
operator|*
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mypaint_surface_destroy (MyPaintSurface * base_surface)
name|gimp_mypaint_surface_destroy
parameter_list|(
name|MyPaintSurface
modifier|*
name|base_surface
parameter_list|)
block|{
name|GimpMybrushSurface
modifier|*
name|surface
init|=
operator|(
name|GimpMybrushSurface
operator|*
operator|)
name|base_surface
decl_stmt|;
name|g_object_unref
argument_list|(
name|surface
operator|->
name|buffer
argument_list|)
expr_stmt|;
name|surface
operator|->
name|buffer
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|GimpMybrushSurface
modifier|*
DECL|function|gimp_mypaint_surface_new (GeglBuffer * buffer,GimpComponentMask component_mask)
name|gimp_mypaint_surface_new
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpComponentMask
name|component_mask
parameter_list|)
block|{
name|GimpMybrushSurface
modifier|*
name|surface
init|=
name|g_malloc0
argument_list|(
sizeof|sizeof
argument_list|(
name|GimpMybrushSurface
argument_list|)
argument_list|)
decl_stmt|;
name|mypaint_surface_init
argument_list|(
operator|(
name|MyPaintSurface
operator|*
operator|)
name|surface
argument_list|)
expr_stmt|;
name|surface
operator|->
name|surface
operator|.
name|get_color
operator|=
name|gimp_mypaint_surface_get_color
expr_stmt|;
name|surface
operator|->
name|surface
operator|.
name|draw_dab
operator|=
name|gimp_mypaint_surface_draw_dab
expr_stmt|;
name|surface
operator|->
name|surface
operator|.
name|begin_atomic
operator|=
name|gimp_mypaint_surface_begin_atomic
expr_stmt|;
name|surface
operator|->
name|surface
operator|.
name|end_atomic
operator|=
name|gimp_mypaint_surface_end_atomic
expr_stmt|;
name|surface
operator|->
name|surface
operator|.
name|destroy
operator|=
name|gimp_mypaint_surface_destroy
expr_stmt|;
name|surface
operator|->
name|component_mask
operator|=
name|component_mask
expr_stmt|;
name|surface
operator|->
name|buffer
operator|=
name|g_object_ref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|surface
operator|->
name|dirty
operator|=
operator|*
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|surface
return|;
block|}
end_function

end_unit

