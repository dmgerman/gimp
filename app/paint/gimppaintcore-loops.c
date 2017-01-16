begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2013 Daniel Sabo  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptempbuf.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes/gimplayermodefunctions.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintcore-loops.h"
end_include

begin_function
name|void
DECL|function|combine_paint_mask_to_canvas_mask (const GimpTempBuf * paint_mask,gint mask_x_offset,gint mask_y_offset,GeglBuffer * canvas_buffer,gint x_offset,gint y_offset,gfloat opacity,gboolean stipple)
name|combine_paint_mask_to_canvas_mask
parameter_list|(
specifier|const
name|GimpTempBuf
modifier|*
name|paint_mask
parameter_list|,
name|gint
name|mask_x_offset
parameter_list|,
name|gint
name|mask_y_offset
parameter_list|,
name|GeglBuffer
modifier|*
name|canvas_buffer
parameter_list|,
name|gint
name|x_offset
parameter_list|,
name|gint
name|y_offset
parameter_list|,
name|gfloat
name|opacity
parameter_list|,
name|gboolean
name|stipple
parameter_list|)
block|{
name|GeglRectangle
name|roi
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
specifier|const
name|gint
name|mask_stride
init|=
name|gimp_temp_buf_get_width
argument_list|(
name|paint_mask
argument_list|)
decl_stmt|;
specifier|const
name|gint
name|mask_start_offset
init|=
name|mask_y_offset
operator|*
name|mask_stride
operator|+
name|mask_x_offset
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|mask_format
init|=
name|gimp_temp_buf_get_format
argument_list|(
name|paint_mask
argument_list|)
decl_stmt|;
name|GimpTempBuf
modifier|*
name|modified_mask
init|=
name|gimp_temp_buf_copy
argument_list|(
name|paint_mask
argument_list|)
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|width
operator|=
name|gimp_temp_buf_get_width
argument_list|(
name|modified_mask
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_temp_buf_get_height
argument_list|(
name|modified_mask
argument_list|)
expr_stmt|;
name|roi
operator|.
name|x
operator|=
name|x_offset
expr_stmt|;
name|roi
operator|.
name|y
operator|=
name|y_offset
expr_stmt|;
name|roi
operator|.
name|width
operator|=
name|width
operator|-
name|mask_x_offset
expr_stmt|;
name|roi
operator|.
name|height
operator|=
name|height
operator|-
name|mask_y_offset
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|canvas_buffer
argument_list|,
operator|&
name|roi
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|,
name|GEGL_ACCESS_READWRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|stipple
condition|)
block|{
if|if
condition|(
name|mask_format
operator|==
name|babl_format
argument_list|(
literal|"Y u8"
argument_list|)
condition|)
block|{
specifier|const
name|guint8
modifier|*
name|mask_data
init|=
operator|(
specifier|const
name|guint8
operator|*
operator|)
name|gimp_temp_buf_get_data
argument_list|(
name|modified_mask
argument_list|)
decl_stmt|;
name|mask_data
operator|+=
name|mask_start_offset
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|gfloat
modifier|*
name|out_pixel
init|=
operator|(
name|gfloat
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
literal|0
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
name|height
condition|;
name|iy
operator|++
control|)
block|{
name|int
name|mask_offset
init|=
operator|(
name|iy
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|y
operator|-
name|roi
operator|.
name|y
operator|)
operator|*
name|mask_stride
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|x
operator|-
name|roi
operator|.
name|x
decl_stmt|;
specifier|const
name|guint8
modifier|*
name|mask_pixel
init|=
operator|&
name|mask_data
index|[
name|mask_offset
index|]
decl_stmt|;
for|for
control|(
name|ix
operator|=
literal|0
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
name|width
condition|;
name|ix
operator|++
control|)
block|{
name|out_pixel
index|[
literal|0
index|]
operator|+=
operator|(
literal|1.0
operator|-
name|out_pixel
index|[
literal|0
index|]
operator|)
operator|*
operator|(
operator|*
name|mask_pixel
operator|/
literal|255.0f
operator|)
operator|*
name|opacity
expr_stmt|;
name|mask_pixel
operator|+=
literal|1
expr_stmt|;
name|out_pixel
operator|+=
literal|1
expr_stmt|;
block|}
block|}
block|}
block|}
elseif|else
if|if
condition|(
name|mask_format
operator|==
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
condition|)
block|{
specifier|const
name|gfloat
modifier|*
name|mask_data
init|=
operator|(
specifier|const
name|gfloat
operator|*
operator|)
name|gimp_temp_buf_get_data
argument_list|(
name|modified_mask
argument_list|)
decl_stmt|;
name|mask_data
operator|+=
name|mask_start_offset
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|gfloat
modifier|*
name|out_pixel
init|=
operator|(
name|gfloat
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
literal|0
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
name|height
condition|;
name|iy
operator|++
control|)
block|{
name|int
name|mask_offset
init|=
operator|(
name|iy
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|y
operator|-
name|roi
operator|.
name|y
operator|)
operator|*
name|mask_stride
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|x
operator|-
name|roi
operator|.
name|x
decl_stmt|;
specifier|const
name|gfloat
modifier|*
name|mask_pixel
init|=
operator|&
name|mask_data
index|[
name|mask_offset
index|]
decl_stmt|;
for|for
control|(
name|ix
operator|=
literal|0
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
name|width
condition|;
name|ix
operator|++
control|)
block|{
name|out_pixel
index|[
literal|0
index|]
operator|+=
operator|(
literal|1.0
operator|-
name|out_pixel
index|[
literal|0
index|]
operator|)
operator|*
operator|(
operator|*
name|mask_pixel
operator|)
operator|*
name|opacity
expr_stmt|;
name|mask_pixel
operator|+=
literal|1
expr_stmt|;
name|out_pixel
operator|+=
literal|1
expr_stmt|;
block|}
block|}
block|}
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"Mask format not supported: %s"
argument_list|,
name|babl_get_name
argument_list|(
name|mask_format
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|mask_format
operator|==
name|babl_format
argument_list|(
literal|"Y u8"
argument_list|)
condition|)
block|{
specifier|const
name|guint8
modifier|*
name|mask_data
init|=
operator|(
specifier|const
name|guint8
operator|*
operator|)
name|gimp_temp_buf_get_data
argument_list|(
name|modified_mask
argument_list|)
decl_stmt|;
name|mask_data
operator|+=
name|mask_start_offset
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|gfloat
modifier|*
name|out_pixel
init|=
operator|(
name|gfloat
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
literal|0
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
name|height
condition|;
name|iy
operator|++
control|)
block|{
name|int
name|mask_offset
init|=
operator|(
name|iy
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|y
operator|-
name|roi
operator|.
name|y
operator|)
operator|*
name|mask_stride
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|x
operator|-
name|roi
operator|.
name|x
decl_stmt|;
specifier|const
name|guint8
modifier|*
name|mask_pixel
init|=
operator|&
name|mask_data
index|[
name|mask_offset
index|]
decl_stmt|;
for|for
control|(
name|ix
operator|=
literal|0
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
name|width
condition|;
name|ix
operator|++
control|)
block|{
if|if
condition|(
name|opacity
operator|>
name|out_pixel
index|[
literal|0
index|]
condition|)
name|out_pixel
index|[
literal|0
index|]
operator|+=
operator|(
name|opacity
operator|-
name|out_pixel
index|[
literal|0
index|]
operator|)
operator|*
operator|(
operator|*
name|mask_pixel
operator|/
literal|255.0f
operator|)
operator|*
name|opacity
expr_stmt|;
name|mask_pixel
operator|+=
literal|1
expr_stmt|;
name|out_pixel
operator|+=
literal|1
expr_stmt|;
block|}
block|}
block|}
block|}
elseif|else
if|if
condition|(
name|mask_format
operator|==
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
condition|)
block|{
specifier|const
name|gfloat
modifier|*
name|mask_data
init|=
operator|(
specifier|const
name|gfloat
operator|*
operator|)
name|gimp_temp_buf_get_data
argument_list|(
name|modified_mask
argument_list|)
decl_stmt|;
name|mask_data
operator|+=
name|mask_start_offset
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|gfloat
modifier|*
name|out_pixel
init|=
operator|(
name|gfloat
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
literal|0
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
name|height
condition|;
name|iy
operator|++
control|)
block|{
name|int
name|mask_offset
init|=
operator|(
name|iy
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|y
operator|-
name|roi
operator|.
name|y
operator|)
operator|*
name|mask_stride
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|x
operator|-
name|roi
operator|.
name|x
decl_stmt|;
specifier|const
name|gfloat
modifier|*
name|mask_pixel
init|=
operator|&
name|mask_data
index|[
name|mask_offset
index|]
decl_stmt|;
for|for
control|(
name|ix
operator|=
literal|0
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
name|width
condition|;
name|ix
operator|++
control|)
block|{
if|if
condition|(
name|opacity
operator|>
name|out_pixel
index|[
literal|0
index|]
condition|)
name|out_pixel
index|[
literal|0
index|]
operator|+=
operator|(
name|opacity
operator|-
name|out_pixel
index|[
literal|0
index|]
operator|)
operator|*
operator|(
operator|*
name|mask_pixel
operator|)
operator|*
name|opacity
expr_stmt|;
name|mask_pixel
operator|+=
literal|1
expr_stmt|;
name|out_pixel
operator|+=
literal|1
expr_stmt|;
block|}
block|}
block|}
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"Mask format not supported: %s"
argument_list|,
name|babl_get_name
argument_list|(
name|mask_format
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_temp_buf_unref
argument_list|(
name|modified_mask
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|canvas_buffer_to_paint_buf_alpha (GimpTempBuf * paint_buf,GeglBuffer * canvas_buffer,gint x_offset,gint y_offset)
name|canvas_buffer_to_paint_buf_alpha
parameter_list|(
name|GimpTempBuf
modifier|*
name|paint_buf
parameter_list|,
name|GeglBuffer
modifier|*
name|canvas_buffer
parameter_list|,
name|gint
name|x_offset
parameter_list|,
name|gint
name|y_offset
parameter_list|)
block|{
comment|/* Copy the canvas buffer in rect to the paint buffer's alpha channel */
name|GeglRectangle
name|roi
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
specifier|const
name|guint
name|paint_stride
init|=
name|gimp_temp_buf_get_width
argument_list|(
name|paint_buf
argument_list|)
decl_stmt|;
name|gfloat
modifier|*
name|paint_data
init|=
operator|(
name|gfloat
operator|*
operator|)
name|gimp_temp_buf_get_data
argument_list|(
name|paint_buf
argument_list|)
decl_stmt|;
name|roi
operator|.
name|x
operator|=
name|x_offset
expr_stmt|;
name|roi
operator|.
name|y
operator|=
name|y_offset
expr_stmt|;
name|roi
operator|.
name|width
operator|=
name|gimp_temp_buf_get_width
argument_list|(
name|paint_buf
argument_list|)
expr_stmt|;
name|roi
operator|.
name|height
operator|=
name|gimp_temp_buf_get_height
argument_list|(
name|paint_buf
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|canvas_buffer
argument_list|,
operator|&
name|roi
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|,
name|GEGL_ACCESS_READ
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
name|gfloat
modifier|*
name|canvas_pixel
init|=
operator|(
name|gfloat
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
literal|0
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
name|height
condition|;
name|iy
operator|++
control|)
block|{
name|int
name|paint_offset
init|=
operator|(
name|iy
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|y
operator|-
name|roi
operator|.
name|y
operator|)
operator|*
name|paint_stride
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|x
operator|-
name|roi
operator|.
name|x
decl_stmt|;
name|float
modifier|*
name|paint_pixel
init|=
operator|&
name|paint_data
index|[
name|paint_offset
operator|*
literal|4
index|]
decl_stmt|;
for|for
control|(
name|ix
operator|=
literal|0
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
name|width
condition|;
name|ix
operator|++
control|)
block|{
name|paint_pixel
index|[
literal|3
index|]
operator|*=
operator|*
name|canvas_pixel
expr_stmt|;
name|canvas_pixel
operator|+=
literal|1
expr_stmt|;
name|paint_pixel
operator|+=
literal|4
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|paint_mask_to_paint_buffer (const GimpTempBuf * paint_mask,gint mask_x_offset,gint mask_y_offset,GimpTempBuf * paint_buf,gfloat paint_opacity)
name|paint_mask_to_paint_buffer
parameter_list|(
specifier|const
name|GimpTempBuf
modifier|*
name|paint_mask
parameter_list|,
name|gint
name|mask_x_offset
parameter_list|,
name|gint
name|mask_y_offset
parameter_list|,
name|GimpTempBuf
modifier|*
name|paint_buf
parameter_list|,
name|gfloat
name|paint_opacity
parameter_list|)
block|{
name|gint
name|width
init|=
name|gimp_temp_buf_get_width
argument_list|(
name|paint_buf
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|gimp_temp_buf_get_height
argument_list|(
name|paint_buf
argument_list|)
decl_stmt|;
specifier|const
name|gint
name|mask_stride
init|=
name|gimp_temp_buf_get_width
argument_list|(
name|paint_mask
argument_list|)
decl_stmt|;
specifier|const
name|gint
name|mask_start_offset
init|=
name|mask_y_offset
operator|*
name|mask_stride
operator|+
name|mask_x_offset
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|mask_format
init|=
name|gimp_temp_buf_get_format
argument_list|(
name|paint_mask
argument_list|)
decl_stmt|;
name|int
name|iy
decl_stmt|,
name|ix
decl_stmt|;
name|gfloat
modifier|*
name|paint_pixel
init|=
operator|(
name|gfloat
operator|*
operator|)
name|gimp_temp_buf_get_data
argument_list|(
name|paint_buf
argument_list|)
decl_stmt|;
comment|/* Validate that the paint buffer is withing the bounds of the paint mask */
name|g_return_if_fail
argument_list|(
name|width
operator|<=
name|gimp_temp_buf_get_width
argument_list|(
name|paint_mask
argument_list|)
operator|-
name|mask_x_offset
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|height
operator|<=
name|gimp_temp_buf_get_height
argument_list|(
name|paint_mask
argument_list|)
operator|-
name|mask_y_offset
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask_format
operator|==
name|babl_format
argument_list|(
literal|"Y u8"
argument_list|)
condition|)
block|{
specifier|const
name|guint8
modifier|*
name|mask_data
init|=
operator|(
specifier|const
name|guint8
operator|*
operator|)
name|gimp_temp_buf_get_data
argument_list|(
name|paint_mask
argument_list|)
decl_stmt|;
name|mask_data
operator|+=
name|mask_start_offset
expr_stmt|;
for|for
control|(
name|iy
operator|=
literal|0
init|;
name|iy
operator|<
name|height
condition|;
name|iy
operator|++
control|)
block|{
name|int
name|mask_offset
init|=
name|iy
operator|*
name|mask_stride
decl_stmt|;
specifier|const
name|guint8
modifier|*
name|mask_pixel
init|=
operator|&
name|mask_data
index|[
name|mask_offset
index|]
decl_stmt|;
for|for
control|(
name|ix
operator|=
literal|0
init|;
name|ix
operator|<
name|width
condition|;
name|ix
operator|++
control|)
block|{
name|paint_pixel
index|[
literal|3
index|]
operator|*=
operator|(
operator|(
operator|(
name|gfloat
operator|)
operator|*
name|mask_pixel
operator|)
operator|/
literal|255.0f
operator|)
operator|*
name|paint_opacity
expr_stmt|;
name|mask_pixel
operator|+=
literal|1
expr_stmt|;
name|paint_pixel
operator|+=
literal|4
expr_stmt|;
block|}
block|}
block|}
elseif|else
if|if
condition|(
name|mask_format
operator|==
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
condition|)
block|{
specifier|const
name|gfloat
modifier|*
name|mask_data
init|=
operator|(
specifier|const
name|gfloat
operator|*
operator|)
name|gimp_temp_buf_get_data
argument_list|(
name|paint_mask
argument_list|)
decl_stmt|;
name|mask_data
operator|+=
name|mask_start_offset
expr_stmt|;
for|for
control|(
name|iy
operator|=
literal|0
init|;
name|iy
operator|<
name|height
condition|;
name|iy
operator|++
control|)
block|{
name|int
name|mask_offset
init|=
name|iy
operator|*
name|mask_stride
decl_stmt|;
specifier|const
name|gfloat
modifier|*
name|mask_pixel
init|=
operator|&
name|mask_data
index|[
name|mask_offset
index|]
decl_stmt|;
for|for
control|(
name|ix
operator|=
literal|0
init|;
name|ix
operator|<
name|width
condition|;
name|ix
operator|++
control|)
block|{
name|paint_pixel
index|[
literal|3
index|]
operator|*=
operator|(
operator|*
name|mask_pixel
operator|)
operator|*
name|paint_opacity
expr_stmt|;
name|mask_pixel
operator|+=
literal|1
expr_stmt|;
name|paint_pixel
operator|+=
literal|4
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|do_layer_blend (GeglBuffer * src_buffer,GeglBuffer * dst_buffer,GimpTempBuf * paint_buf,GeglBuffer * mask_buffer,gfloat opacity,gint x_offset,gint y_offset,gint mask_x_offset,gint mask_y_offset,gboolean linear_mode,GimpLayerMode paint_mode)
name|do_layer_blend
parameter_list|(
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
name|GeglBuffer
modifier|*
name|dst_buffer
parameter_list|,
name|GimpTempBuf
modifier|*
name|paint_buf
parameter_list|,
name|GeglBuffer
modifier|*
name|mask_buffer
parameter_list|,
name|gfloat
name|opacity
parameter_list|,
name|gint
name|x_offset
parameter_list|,
name|gint
name|y_offset
parameter_list|,
name|gint
name|mask_x_offset
parameter_list|,
name|gint
name|mask_y_offset
parameter_list|,
name|gboolean
name|linear_mode
parameter_list|,
name|GimpLayerMode
name|paint_mode
parameter_list|)
block|{
name|GeglRectangle
name|roi
decl_stmt|;
name|GeglRectangle
name|mask_roi
decl_stmt|;
name|GeglRectangle
name|process_roi
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|iterator_format
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
specifier|const
name|guint
name|paint_stride
init|=
name|gimp_temp_buf_get_width
argument_list|(
name|paint_buf
argument_list|)
decl_stmt|;
name|gfloat
modifier|*
name|paint_data
init|=
operator|(
name|gfloat
operator|*
operator|)
name|gimp_temp_buf_get_data
argument_list|(
name|paint_buf
argument_list|)
decl_stmt|;
name|GimpLayerModeFunc
name|apply_func
init|=
name|gimp_get_layer_mode_function
argument_list|(
name|paint_mode
argument_list|,
name|linear_mode
argument_list|)
decl_stmt|;
if|if
condition|(
name|linear_mode
condition|)
name|iterator_format
operator|=
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
expr_stmt|;
else|else
name|iterator_format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
expr_stmt|;
name|roi
operator|.
name|x
operator|=
name|x_offset
expr_stmt|;
name|roi
operator|.
name|y
operator|=
name|y_offset
expr_stmt|;
name|roi
operator|.
name|width
operator|=
name|gimp_temp_buf_get_width
argument_list|(
name|paint_buf
argument_list|)
expr_stmt|;
name|roi
operator|.
name|height
operator|=
name|gimp_temp_buf_get_height
argument_list|(
name|paint_buf
argument_list|)
expr_stmt|;
name|mask_roi
operator|.
name|x
operator|=
name|roi
operator|.
name|x
operator|-
name|mask_x_offset
expr_stmt|;
name|mask_roi
operator|.
name|y
operator|=
name|roi
operator|.
name|y
operator|-
name|mask_y_offset
expr_stmt|;
name|mask_roi
operator|.
name|width
operator|=
name|roi
operator|.
name|width
expr_stmt|;
name|mask_roi
operator|.
name|height
operator|=
name|roi
operator|.
name|height
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_temp_buf_get_format
argument_list|(
name|paint_buf
argument_list|)
operator|==
name|iterator_format
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|dst_buffer
argument_list|,
operator|&
name|roi
argument_list|,
literal|0
argument_list|,
name|iterator_format
argument_list|,
name|GEGL_ACCESS_WRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|src_buffer
argument_list|,
operator|&
name|roi
argument_list|,
literal|0
argument_list|,
name|iterator_format
argument_list|,
name|GEGL_ACCESS_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask_buffer
condition|)
block|{
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|mask_buffer
argument_list|,
operator|&
name|mask_roi
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|,
name|GEGL_ACCESS_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
block|}
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|gfloat
modifier|*
name|out_pixel
init|=
operator|(
name|gfloat
operator|*
operator|)
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|gfloat
modifier|*
name|in_pixel
init|=
operator|(
name|gfloat
operator|*
operator|)
name|iter
operator|->
name|data
index|[
literal|1
index|]
decl_stmt|;
name|gfloat
modifier|*
name|mask_pixel
init|=
name|NULL
decl_stmt|;
name|gfloat
modifier|*
name|paint_pixel
init|=
name|paint_data
operator|+
operator|(
operator|(
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|y
operator|-
name|roi
operator|.
name|y
operator|)
operator|*
name|paint_stride
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|x
operator|-
name|roi
operator|.
name|x
operator|)
operator|*
literal|4
decl_stmt|;
name|int
name|iy
decl_stmt|;
if|if
condition|(
name|mask_buffer
condition|)
name|mask_pixel
operator|=
operator|(
name|gfloat
operator|*
operator|)
name|iter
operator|->
name|data
index|[
literal|2
index|]
expr_stmt|;
name|process_roi
operator|.
name|x
operator|=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|x
expr_stmt|;
name|process_roi
operator|.
name|width
operator|=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|width
expr_stmt|;
name|process_roi
operator|.
name|height
operator|=
literal|1
expr_stmt|;
for|for
control|(
name|iy
operator|=
literal|0
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
name|height
condition|;
name|iy
operator|++
control|)
block|{
name|process_roi
operator|.
name|y
operator|=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|y
operator|+
name|iy
expr_stmt|;
call|(
modifier|*
name|apply_func
call|)
argument_list|(
name|in_pixel
argument_list|,
name|paint_pixel
argument_list|,
name|mask_pixel
argument_list|,
name|out_pixel
argument_list|,
name|opacity
argument_list|,
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|width
argument_list|,
operator|&
name|process_roi
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|in_pixel
operator|+=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|width
operator|*
literal|4
expr_stmt|;
name|out_pixel
operator|+=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|width
operator|*
literal|4
expr_stmt|;
if|if
condition|(
name|mask_buffer
condition|)
name|mask_pixel
operator|+=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|width
expr_stmt|;
name|paint_pixel
operator|+=
name|paint_stride
operator|*
literal|4
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|mask_components_onto (GeglBuffer * src_buffer,GeglBuffer * aux_buffer,GeglBuffer * dst_buffer,GeglRectangle * roi,GimpComponentMask mask,gboolean linear_mode)
name|mask_components_onto
parameter_list|(
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
name|GeglBuffer
modifier|*
name|aux_buffer
parameter_list|,
name|GeglBuffer
modifier|*
name|dst_buffer
parameter_list|,
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|GimpComponentMask
name|mask
parameter_list|,
name|gboolean
name|linear_mode
parameter_list|)
block|{
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|iterator_format
decl_stmt|;
if|if
condition|(
name|linear_mode
condition|)
name|iterator_format
operator|=
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
expr_stmt|;
else|else
name|iterator_format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|dst_buffer
argument_list|,
name|roi
argument_list|,
literal|0
argument_list|,
name|iterator_format
argument_list|,
name|GEGL_ACCESS_WRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|src_buffer
argument_list|,
name|roi
argument_list|,
literal|0
argument_list|,
name|iterator_format
argument_list|,
name|GEGL_ACCESS_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|aux_buffer
argument_list|,
name|roi
argument_list|,
literal|0
argument_list|,
name|iterator_format
argument_list|,
name|GEGL_ACCESS_READ
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
name|gfloat
modifier|*
name|dest
init|=
operator|(
name|gfloat
operator|*
operator|)
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|gfloat
modifier|*
name|src
init|=
operator|(
name|gfloat
operator|*
operator|)
name|iter
operator|->
name|data
index|[
literal|1
index|]
decl_stmt|;
name|gfloat
modifier|*
name|aux
init|=
operator|(
name|gfloat
operator|*
operator|)
name|iter
operator|->
name|data
index|[
literal|2
index|]
decl_stmt|;
name|glong
name|samples
init|=
name|iter
operator|->
name|length
decl_stmt|;
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|dest
index|[
name|RED
index|]
operator|=
operator|(
name|mask
operator|&
name|GIMP_COMPONENT_MASK_RED
operator|)
condition|?
name|aux
index|[
name|RED
index|]
else|:
name|src
index|[
name|RED
index|]
expr_stmt|;
name|dest
index|[
name|GREEN
index|]
operator|=
operator|(
name|mask
operator|&
name|GIMP_COMPONENT_MASK_GREEN
operator|)
condition|?
name|aux
index|[
name|GREEN
index|]
else|:
name|src
index|[
name|GREEN
index|]
expr_stmt|;
name|dest
index|[
name|BLUE
index|]
operator|=
operator|(
name|mask
operator|&
name|GIMP_COMPONENT_MASK_BLUE
operator|)
condition|?
name|aux
index|[
name|BLUE
index|]
else|:
name|src
index|[
name|BLUE
index|]
expr_stmt|;
name|dest
index|[
name|ALPHA
index|]
operator|=
operator|(
name|mask
operator|&
name|GIMP_COMPONENT_MASK_ALPHA
operator|)
condition|?
name|aux
index|[
name|ALPHA
index|]
else|:
name|src
index|[
name|ALPHA
index|]
expr_stmt|;
name|src
operator|+=
literal|4
expr_stmt|;
name|aux
operator|+=
literal|4
expr_stmt|;
name|dest
operator|+=
literal|4
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

