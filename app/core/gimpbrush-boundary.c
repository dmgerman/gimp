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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpbezierdesc.h"
end_include

begin_include
include|#
directive|include
file|"gimpboundary.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush-boundary.h"
end_include

begin_function
specifier|static
name|GimpBezierDesc
modifier|*
DECL|function|gimp_brush_transform_boundary_exact (GimpBrush * brush,gdouble scale,gdouble aspect_ratio,gdouble angle,gdouble hardness)
name|gimp_brush_transform_boundary_exact
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gdouble
name|aspect_ratio
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|hardness
parameter_list|)
block|{
specifier|const
name|TempBuf
modifier|*
name|mask
decl_stmt|;
name|mask
operator|=
name|gimp_brush_transform_mask
argument_list|(
name|brush
argument_list|,
name|scale
argument_list|,
name|aspect_ratio
argument_list|,
name|angle
argument_list|,
name|hardness
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask
condition|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GimpBoundSeg
modifier|*
name|bound_segs
decl_stmt|;
name|gint
name|n_bound_segs
decl_stmt|;
name|buffer
operator|=
name|gimp_temp_buf_create_buffer
argument_list|(
operator|(
name|TempBuf
operator|*
operator|)
name|mask
argument_list|,
name|babl_format
argument_list|(
literal|"Y u8"
argument_list|)
argument_list|)
expr_stmt|;
name|bound_segs
operator|=
name|gimp_boundary_find
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|GIMP_BOUNDARY_WITHIN_BOUNDS
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|&
name|n_bound_segs
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|bound_segs
condition|)
block|{
name|GimpBoundSeg
modifier|*
name|stroke_segs
decl_stmt|;
name|gint
name|n_stroke_groups
decl_stmt|;
name|stroke_segs
operator|=
name|gimp_boundary_sort
argument_list|(
name|bound_segs
argument_list|,
name|n_bound_segs
argument_list|,
operator|&
name|n_stroke_groups
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bound_segs
argument_list|)
expr_stmt|;
if|if
condition|(
name|stroke_segs
condition|)
block|{
name|GimpBezierDesc
modifier|*
name|path
decl_stmt|;
name|path
operator|=
name|gimp_bezier_desc_new_from_bound_segs
argument_list|(
name|stroke_segs
argument_list|,
name|n_bound_segs
argument_list|,
name|n_stroke_groups
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stroke_segs
argument_list|)
expr_stmt|;
return|return
name|path
return|;
block|}
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|GimpBezierDesc
modifier|*
DECL|function|gimp_brush_transform_boundary_approx (GimpBrush * brush,gdouble scale,gdouble aspect_ratio,gdouble angle,gdouble hardness)
name|gimp_brush_transform_boundary_approx
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gdouble
name|aspect_ratio
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|hardness
parameter_list|)
block|{
return|return
name|gimp_brush_transform_boundary_exact
argument_list|(
name|brush
argument_list|,
name|scale
argument_list|,
name|aspect_ratio
argument_list|,
name|angle
argument_list|,
name|hardness
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpBezierDesc
modifier|*
DECL|function|gimp_brush_real_transform_boundary (GimpBrush * brush,gdouble scale,gdouble aspect_ratio,gdouble angle,gdouble hardness,gint * width,gint * height)
name|gimp_brush_real_transform_boundary
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gdouble
name|aspect_ratio
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|hardness
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
name|gimp_brush_transform_size
argument_list|(
name|brush
argument_list|,
name|scale
argument_list|,
name|aspect_ratio
argument_list|,
name|angle
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|width
operator|<
literal|256
operator|&&
operator|*
name|height
operator|<
literal|256
condition|)
block|{
return|return
name|gimp_brush_transform_boundary_exact
argument_list|(
name|brush
argument_list|,
name|scale
argument_list|,
name|aspect_ratio
argument_list|,
name|angle
argument_list|,
name|hardness
argument_list|)
return|;
block|}
return|return
name|gimp_brush_transform_boundary_approx
argument_list|(
name|brush
argument_list|,
name|scale
argument_list|,
name|aspect_ratio
argument_list|,
name|angle
argument_list|,
name|hardness
argument_list|)
return|;
block|}
end_function

end_unit

