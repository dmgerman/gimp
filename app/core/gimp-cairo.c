begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-cairo.c  * Copyright (C) 2010-2012  Michael Natterer<mitch@gimp.org>  *  * Some code here is based on code from librsvg that was originally  * written by Raph Levien<raph@artofcode.com> for Gill.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-cairo.h"
end_include

begin_decl_stmt
DECL|variable|surface_data_key
specifier|static
name|cairo_user_data_key_t
name|surface_data_key
init|=
block|{
literal|0
block|, }
decl_stmt|;
end_decl_stmt

begin_function
name|cairo_pattern_t
modifier|*
DECL|function|gimp_cairo_pattern_create_stipple (const GimpRGB * fg,const GimpRGB * bg,gint index,gdouble offset_x,gdouble offset_y)
name|gimp_cairo_pattern_create_stipple
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|fg
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|bg
parameter_list|,
name|gint
name|index
parameter_list|,
name|gdouble
name|offset_x
parameter_list|,
name|gdouble
name|offset_y
parameter_list|)
block|{
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
name|cairo_pattern_t
modifier|*
name|pattern
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|guchar
modifier|*
name|d
decl_stmt|;
name|guchar
name|fg_r
decl_stmt|,
name|fg_g
decl_stmt|,
name|fg_b
decl_stmt|,
name|fg_a
decl_stmt|;
name|guchar
name|bg_r
decl_stmt|,
name|bg_g
decl_stmt|,
name|bg_b
decl_stmt|,
name|bg_a
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|fg
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|bg
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|=
name|g_malloc
argument_list|(
literal|8
operator|*
literal|8
operator|*
literal|4
argument_list|)
expr_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
name|fg
argument_list|,
operator|&
name|fg_r
argument_list|,
operator|&
name|fg_g
argument_list|,
operator|&
name|fg_b
argument_list|,
operator|&
name|fg_a
argument_list|)
expr_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
name|bg
argument_list|,
operator|&
name|bg_r
argument_list|,
operator|&
name|bg_g
argument_list|,
operator|&
name|bg_b
argument_list|,
operator|&
name|bg_a
argument_list|)
expr_stmt|;
name|d
operator|=
name|data
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
literal|8
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
literal|8
condition|;
name|x
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|x
operator|+
name|y
operator|+
name|index
operator|)
operator|%
literal|8
operator|>=
literal|4
condition|)
name|GIMP_CAIRO_ARGB32_SET_PIXEL
argument_list|(
name|d
argument_list|,
name|fg_r
argument_list|,
name|fg_g
argument_list|,
name|fg_b
argument_list|,
name|fg_a
argument_list|)
expr_stmt|;
else|else
name|GIMP_CAIRO_ARGB32_SET_PIXEL
argument_list|(
name|d
argument_list|,
name|bg_r
argument_list|,
name|bg_g
argument_list|,
name|bg_b
argument_list|,
name|bg_a
argument_list|)
expr_stmt|;
name|d
operator|+=
literal|4
expr_stmt|;
block|}
block|}
name|surface
operator|=
name|cairo_image_surface_create_for_data
argument_list|(
name|data
argument_list|,
name|CAIRO_FORMAT_ARGB32
argument_list|,
literal|8
argument_list|,
literal|8
argument_list|,
literal|8
operator|*
literal|4
argument_list|)
expr_stmt|;
name|cairo_surface_set_user_data
argument_list|(
name|surface
argument_list|,
operator|&
name|surface_data_key
argument_list|,
name|data
argument_list|,
operator|(
name|cairo_destroy_func_t
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|pattern
operator|=
name|cairo_pattern_create_for_surface
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|cairo_pattern_set_extend
argument_list|(
name|pattern
argument_list|,
name|CAIRO_EXTEND_REPEAT
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|surface
argument_list|)
expr_stmt|;
if|if
condition|(
name|offset_x
operator|!=
literal|0.0
operator|||
name|offset_y
operator|!=
literal|0.0
condition|)
block|{
name|cairo_matrix_t
name|matrix
decl_stmt|;
name|cairo_matrix_init_translate
argument_list|(
operator|&
name|matrix
argument_list|,
name|fmod
argument_list|(
name|offset_x
argument_list|,
literal|8
argument_list|)
argument_list|,
name|fmod
argument_list|(
name|offset_y
argument_list|,
literal|8
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_pattern_set_matrix
argument_list|(
name|pattern
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
block|}
return|return
name|pattern
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_cairo_arc (cairo_t * cr,gdouble center_x,gdouble center_y,gdouble radius,gdouble start_angle,gdouble slice_angle)
name|gimp_cairo_arc
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|,
name|gdouble
name|radius
parameter_list|,
name|gdouble
name|start_angle
parameter_list|,
name|gdouble
name|slice_angle
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|slice_angle
operator|>=
literal|0
condition|)
block|{
name|cairo_arc_negative
argument_list|(
name|cr
argument_list|,
name|center_x
argument_list|,
name|center_y
argument_list|,
name|radius
argument_list|,
operator|-
name|start_angle
argument_list|,
operator|-
name|start_angle
operator|-
name|slice_angle
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|cairo_arc
argument_list|(
name|cr
argument_list|,
name|center_x
argument_list|,
name|center_y
argument_list|,
name|radius
argument_list|,
operator|-
name|start_angle
argument_list|,
operator|-
name|start_angle
operator|-
name|slice_angle
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_cairo_segments (cairo_t * cr,GimpSegment * segs,gint n_segs)
name|gimp_cairo_segments
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GimpSegment
modifier|*
name|segs
parameter_list|,
name|gint
name|n_segs
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|segs
operator|!=
name|NULL
operator|&&
name|n_segs
operator|>
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_segs
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|segs
index|[
name|i
index|]
operator|.
name|x1
operator|==
name|segs
index|[
name|i
index|]
operator|.
name|x2
condition|)
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|segs
index|[
name|i
index|]
operator|.
name|x1
operator|+
literal|0.5
argument_list|,
name|segs
index|[
name|i
index|]
operator|.
name|y1
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|segs
index|[
name|i
index|]
operator|.
name|x2
operator|+
literal|0.5
argument_list|,
name|segs
index|[
name|i
index|]
operator|.
name|y2
operator|-
literal|0.5
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|segs
index|[
name|i
index|]
operator|.
name|x1
operator|+
literal|0.5
argument_list|,
name|segs
index|[
name|i
index|]
operator|.
name|y1
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|segs
index|[
name|i
index|]
operator|.
name|x2
operator|-
literal|0.5
argument_list|,
name|segs
index|[
name|i
index|]
operator|.
name|y2
operator|+
literal|0.5
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

