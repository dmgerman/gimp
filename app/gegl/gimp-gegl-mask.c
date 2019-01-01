begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-mask.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_gegl_mask_bounds (GeglBuffer * buffer,gint * x1,gint * y1,gint * x2,gint * y2)
name|gimp_gegl_mask_bounds
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
block|{
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|GeglRectangle
modifier|*
name|roi
decl_stmt|;
name|gint
name|tx1
decl_stmt|,
name|tx2
decl_stmt|,
name|ty1
decl_stmt|,
name|ty2
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|x1
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|y1
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|x2
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|y2
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  go through and calculate the bounds  */
name|tx1
operator|=
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|ty1
operator|=
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|tx2
operator|=
literal|0
expr_stmt|;
name|ty2
operator|=
literal|0
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|buffer
argument_list|,
name|NULL
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
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|roi
operator|=
operator|&
name|iter
operator|->
name|items
index|[
literal|0
index|]
operator|.
name|roi
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
name|data
init|=
name|iter
operator|->
name|items
index|[
literal|0
index|]
operator|.
name|data
decl_stmt|;
name|gfloat
modifier|*
name|data1
init|=
name|data
decl_stmt|;
name|gint
name|ex
init|=
name|roi
operator|->
name|x
operator|+
name|roi
operator|->
name|width
decl_stmt|;
name|gint
name|ey
init|=
name|roi
operator|->
name|y
operator|+
name|roi
operator|->
name|height
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  only check the pixels if this tile is not fully within the        *  currently computed bounds        */
if|if
condition|(
name|roi
operator|->
name|x
operator|<
name|tx1
operator|||
name|ex
operator|>
name|tx2
operator|||
name|roi
operator|->
name|y
operator|<
name|ty1
operator|||
name|ey
operator|>
name|ty2
condition|)
block|{
comment|/* Check upper left and lower right corners to see if we can            * avoid checking the rest of the pixels in this tile            */
if|if
condition|(
name|data
index|[
literal|0
index|]
operator|&&
name|data
index|[
name|iter
operator|->
name|length
operator|-
literal|1
index|]
condition|)
block|{
comment|/*  "ex/ey - 1" because the internal variables are the                *  right/bottom pixel of the mask's contents, not one                *  right/below it like the return values.                */
if|if
condition|(
name|roi
operator|->
name|x
operator|<
name|tx1
condition|)
name|tx1
operator|=
name|roi
operator|->
name|x
expr_stmt|;
if|if
condition|(
name|ex
operator|>
name|tx2
condition|)
name|tx2
operator|=
name|ex
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|roi
operator|->
name|y
operator|<
name|ty1
condition|)
name|ty1
operator|=
name|roi
operator|->
name|y
expr_stmt|;
if|if
condition|(
name|ey
operator|>
name|ty2
condition|)
name|ty2
operator|=
name|ey
operator|-
literal|1
expr_stmt|;
block|}
else|else
block|{
for|for
control|(
name|y
operator|=
name|roi
operator|->
name|y
init|;
name|y
operator|<
name|ey
condition|;
name|y
operator|++
operator|,
name|data1
operator|+=
name|roi
operator|->
name|width
control|)
block|{
for|for
control|(
name|x
operator|=
name|roi
operator|->
name|x
operator|,
name|data
operator|=
name|data1
init|;
name|x
operator|<
name|ex
condition|;
name|x
operator|++
operator|,
name|data
operator|++
control|)
block|{
if|if
condition|(
operator|*
name|data
condition|)
block|{
name|gint
name|minx
init|=
name|x
decl_stmt|;
name|gint
name|maxx
init|=
name|x
decl_stmt|;
for|for
control|(
init|;
name|x
operator|<
name|ex
condition|;
name|x
operator|++
operator|,
name|data
operator|++
control|)
if|if
condition|(
operator|*
name|data
condition|)
name|maxx
operator|=
name|x
expr_stmt|;
if|if
condition|(
name|minx
operator|<
name|tx1
condition|)
name|tx1
operator|=
name|minx
expr_stmt|;
if|if
condition|(
name|maxx
operator|>
name|tx2
condition|)
name|tx2
operator|=
name|maxx
expr_stmt|;
if|if
condition|(
name|y
operator|<
name|ty1
condition|)
name|ty1
operator|=
name|y
expr_stmt|;
if|if
condition|(
name|y
operator|>
name|ty2
condition|)
name|ty2
operator|=
name|y
expr_stmt|;
block|}
block|}
block|}
block|}
block|}
block|}
name|tx2
operator|=
name|CLAMP
argument_list|(
name|tx2
operator|+
literal|1
argument_list|,
literal|0
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|ty2
operator|=
name|CLAMP
argument_list|(
name|ty2
operator|+
literal|1
argument_list|,
literal|0
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|tx1
operator|==
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
operator|&&
name|ty1
operator|==
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
condition|)
block|{
operator|*
name|x1
operator|=
literal|0
expr_stmt|;
operator|*
name|y1
operator|=
literal|0
expr_stmt|;
operator|*
name|x2
operator|=
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
operator|*
name|y2
operator|=
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
operator|*
name|x1
operator|=
name|tx1
expr_stmt|;
operator|*
name|y1
operator|=
name|ty1
expr_stmt|;
operator|*
name|x2
operator|=
name|tx2
expr_stmt|;
operator|*
name|y2
operator|=
name|ty2
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_gegl_mask_is_empty (GeglBuffer * buffer)
name|gimp_gegl_mask_is_empty
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|format
operator|=
name|gegl_buffer_get_format
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|format
argument_list|,
name|GEGL_ACCESS_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
literal|1
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
if|if
condition|(
operator|!
name|gegl_memeq_zero
argument_list|(
name|iter
operator|->
name|items
index|[
literal|0
index|]
operator|.
name|data
argument_list|,
name|bpp
operator|*
name|iter
operator|->
name|length
argument_list|)
condition|)
block|{
name|gegl_buffer_iterator_stop
argument_list|(
name|iter
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

