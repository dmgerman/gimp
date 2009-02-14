begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbrush-transform.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush-transform.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_brush_transform_matrix
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_transform_bounding_box
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_brush_real_transform_size (GimpBrush * brush,gdouble scale_x,gdouble scale_y,gdouble angle,gint * width,gint * height)
name|gimp_brush_real_transform_size
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gdouble
name|angle
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
name|GimpMatrix3
name|matrix
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gimp_brush_transform_matrix
argument_list|(
name|brush
argument_list|,
name|scale_x
argument_list|,
name|scale_y
argument_list|,
name|angle
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
name|gimp_brush_transform_bounding_box
argument_list|(
name|brush
argument_list|,
operator|&
name|matrix
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_brush_real_transform_mask (GimpBrush * brush,gdouble scale_x,gdouble scale_y,gdouble angle)
name|gimp_brush_real_transform_mask
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gdouble
name|angle
parameter_list|)
block|{
name|TempBuf
modifier|*
name|result
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|GimpMatrix3
name|matrix
decl_stmt|;
name|gint
name|src_width
decl_stmt|;
name|gint
name|src_height
decl_stmt|;
name|gint
name|dest_width
decl_stmt|;
name|gint
name|dest_height
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gimp_brush_transform_matrix
argument_list|(
name|brush
argument_list|,
name|scale_x
argument_list|,
name|scale_y
argument_list|,
name|angle
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_matrix3_is_identity
argument_list|(
operator|&
name|matrix
argument_list|)
condition|)
return|return
name|temp_buf_copy
argument_list|(
name|brush
operator|->
name|mask
argument_list|,
name|NULL
argument_list|)
return|;
name|src_width
operator|=
name|brush
operator|->
name|mask
operator|->
name|width
expr_stmt|;
name|src_height
operator|=
name|brush
operator|->
name|mask
operator|->
name|height
expr_stmt|;
name|gimp_brush_transform_bounding_box
argument_list|(
name|brush
argument_list|,
operator|&
name|matrix
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|dest_width
argument_list|,
operator|&
name|dest_height
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
operator|&
name|matrix
argument_list|,
operator|-
name|x
argument_list|,
operator|-
name|y
argument_list|)
expr_stmt|;
name|gimp_matrix3_invert
argument_list|(
operator|&
name|matrix
argument_list|)
expr_stmt|;
name|result
operator|=
name|temp_buf_new
argument_list|(
name|dest_width
argument_list|,
name|dest_height
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dest
operator|=
name|temp_buf_get_data
argument_list|(
name|result
argument_list|)
expr_stmt|;
name|src
operator|=
name|temp_buf_get_data
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|dest_height
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
name|dest_width
condition|;
name|x
operator|++
control|)
block|{
name|gdouble
name|dx
decl_stmt|,
name|dy
decl_stmt|;
name|gint
name|ix
decl_stmt|,
name|iy
decl_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|dx
argument_list|,
operator|&
name|dy
argument_list|)
expr_stmt|;
name|ix
operator|=
name|ROUND
argument_list|(
name|dx
argument_list|)
expr_stmt|;
name|iy
operator|=
name|ROUND
argument_list|(
name|dy
argument_list|)
expr_stmt|;
if|if
condition|(
name|ix
operator|>
literal|0
operator|&&
name|ix
operator|<
name|src_width
operator|&&
name|iy
operator|>
literal|0
operator|&&
name|iy
operator|<
name|src_height
condition|)
block|{
operator|*
name|dest
operator|=
name|src
index|[
name|iy
operator|*
name|src_width
operator|+
name|ix
index|]
expr_stmt|;
block|}
else|else
block|{
operator|*
name|dest
operator|=
literal|0
expr_stmt|;
block|}
name|dest
operator|++
expr_stmt|;
block|}
block|}
return|return
name|result
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_brush_real_transform_pixmap (GimpBrush * brush,gdouble scale_x,gdouble scale_y,gdouble angle)
name|gimp_brush_real_transform_pixmap
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gdouble
name|angle
parameter_list|)
block|{
name|TempBuf
modifier|*
name|result
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|GimpMatrix3
name|matrix
decl_stmt|;
name|gint
name|src_width
decl_stmt|;
name|gint
name|src_height
decl_stmt|;
name|gint
name|dest_width
decl_stmt|;
name|gint
name|dest_height
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gimp_brush_transform_matrix
argument_list|(
name|brush
argument_list|,
name|scale_x
argument_list|,
name|scale_y
argument_list|,
name|angle
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_matrix3_is_identity
argument_list|(
operator|&
name|matrix
argument_list|)
condition|)
return|return
name|temp_buf_copy
argument_list|(
name|brush
operator|->
name|pixmap
argument_list|,
name|NULL
argument_list|)
return|;
name|src_width
operator|=
name|brush
operator|->
name|pixmap
operator|->
name|width
expr_stmt|;
name|src_height
operator|=
name|brush
operator|->
name|pixmap
operator|->
name|height
expr_stmt|;
name|gimp_brush_transform_bounding_box
argument_list|(
name|brush
argument_list|,
operator|&
name|matrix
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|dest_width
argument_list|,
operator|&
name|dest_height
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
operator|&
name|matrix
argument_list|,
operator|-
name|x
argument_list|,
operator|-
name|y
argument_list|)
expr_stmt|;
name|gimp_matrix3_invert
argument_list|(
operator|&
name|matrix
argument_list|)
expr_stmt|;
name|result
operator|=
name|temp_buf_new
argument_list|(
name|dest_width
argument_list|,
name|dest_height
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dest
operator|=
name|temp_buf_get_data
argument_list|(
name|result
argument_list|)
expr_stmt|;
name|src
operator|=
name|temp_buf_get_data
argument_list|(
name|brush
operator|->
name|pixmap
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|dest_height
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
name|dest_width
condition|;
name|x
operator|++
control|)
block|{
name|gdouble
name|dx
decl_stmt|,
name|dy
decl_stmt|;
name|gint
name|ix
decl_stmt|,
name|iy
decl_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|dx
argument_list|,
operator|&
name|dy
argument_list|)
expr_stmt|;
name|ix
operator|=
name|ROUND
argument_list|(
name|dx
argument_list|)
expr_stmt|;
name|iy
operator|=
name|ROUND
argument_list|(
name|dy
argument_list|)
expr_stmt|;
if|if
condition|(
name|ix
operator|>
literal|0
operator|&&
name|ix
operator|<
name|src_width
operator|&&
name|iy
operator|>
literal|0
operator|&&
name|iy
operator|<
name|src_height
condition|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
operator|+
literal|3
operator|*
operator|(
name|iy
operator|*
name|src_width
operator|+
name|ix
operator|)
decl_stmt|;
name|dest
index|[
literal|0
index|]
operator|=
name|s
index|[
literal|0
index|]
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|s
index|[
literal|1
index|]
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|s
index|[
literal|2
index|]
expr_stmt|;
block|}
else|else
block|{
name|dest
index|[
literal|0
index|]
operator|=
literal|0
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
literal|0
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
literal|0
expr_stmt|;
block|}
name|dest
operator|+=
literal|3
expr_stmt|;
block|}
block|}
return|return
name|result
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_brush_transform_matrix (GimpBrush * brush,gdouble scale_x,gdouble scale_y,gdouble angle,GimpMatrix3 * matrix)
name|gimp_brush_transform_matrix
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
block|{
specifier|const
name|gdouble
name|center_x
init|=
name|brush
operator|->
name|mask
operator|->
name|width
operator|/
literal|2
decl_stmt|;
specifier|const
name|gdouble
name|center_y
init|=
name|brush
operator|->
name|mask
operator|->
name|height
operator|/
literal|2
decl_stmt|;
name|gimp_matrix3_identity
argument_list|(
name|matrix
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
operator|-
name|center_x
argument_list|,
operator|-
name|center_x
argument_list|)
expr_stmt|;
name|gimp_matrix3_rotate
argument_list|(
name|matrix
argument_list|,
operator|-
literal|2
operator|*
name|G_PI
operator|*
name|angle
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
name|center_x
argument_list|,
name|center_y
argument_list|)
expr_stmt|;
name|gimp_matrix3_scale
argument_list|(
name|matrix
argument_list|,
name|scale_x
argument_list|,
name|scale_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_transform_bounding_box (GimpBrush * brush,const GimpMatrix3 * matrix,gint * x,gint * y,gint * width,gint * height)
name|gimp_brush_transform_bounding_box
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
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
specifier|const
name|gdouble
name|w
init|=
name|brush
operator|->
name|mask
operator|->
name|width
decl_stmt|;
specifier|const
name|gdouble
name|h
init|=
name|brush
operator|->
name|mask
operator|->
name|height
decl_stmt|;
name|gdouble
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|x3
decl_stmt|,
name|x4
decl_stmt|;
name|gdouble
name|y1
decl_stmt|,
name|y2
decl_stmt|,
name|y3
decl_stmt|,
name|y4
decl_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|matrix
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|matrix
argument_list|,
name|w
argument_list|,
literal|0
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|matrix
argument_list|,
literal|0
argument_list|,
name|h
argument_list|,
operator|&
name|x3
argument_list|,
operator|&
name|y3
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|matrix
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
operator|&
name|x4
argument_list|,
operator|&
name|y4
argument_list|)
expr_stmt|;
operator|*
name|x
operator|=
name|floor
argument_list|(
name|MIN
argument_list|(
name|MIN
argument_list|(
name|x1
argument_list|,
name|x2
argument_list|)
argument_list|,
name|MIN
argument_list|(
name|x3
argument_list|,
name|x4
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|y
operator|=
name|floor
argument_list|(
name|MIN
argument_list|(
name|MIN
argument_list|(
name|y1
argument_list|,
name|y2
argument_list|)
argument_list|,
name|MIN
argument_list|(
name|y3
argument_list|,
name|y4
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|width
operator|=
call|(
name|gint
call|)
argument_list|(
name|ceil
argument_list|(
name|MAX
argument_list|(
name|MAX
argument_list|(
name|x1
argument_list|,
name|x2
argument_list|)
argument_list|,
name|MAX
argument_list|(
name|x3
argument_list|,
name|x4
argument_list|)
argument_list|)
argument_list|)
operator|-
operator|*
name|x
argument_list|)
expr_stmt|;
operator|*
name|height
operator|=
call|(
name|gint
call|)
argument_list|(
name|ceil
argument_list|(
name|MAX
argument_list|(
name|MAX
argument_list|(
name|y1
argument_list|,
name|y2
argument_list|)
argument_list|,
name|MAX
argument_list|(
name|y3
argument_list|,
name|y4
argument_list|)
argument_list|)
argument_list|)
operator|-
operator|*
name|y
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

