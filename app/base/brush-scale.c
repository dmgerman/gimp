begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"base-types.h"
end_include

begin_include
include|#
directive|include
file|"brush-scale.h"
end_include

begin_include
include|#
directive|include
file|"temp-buf.h"
end_include

begin_function
name|MaskBuf
modifier|*
DECL|function|brush_scale_mask (MaskBuf * brush_mask,gint dest_width,gint dest_height)
name|brush_scale_mask
parameter_list|(
name|MaskBuf
modifier|*
name|brush_mask
parameter_list|,
name|gint
name|dest_width
parameter_list|,
name|gint
name|dest_height
parameter_list|)
block|{
name|MaskBuf
modifier|*
name|scale_brush
decl_stmt|;
name|gint
name|src_width
decl_stmt|;
name|gint
name|src_height
decl_stmt|;
name|gint
name|value
decl_stmt|;
name|gint
name|area
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|x0
decl_stmt|,
name|y
decl_stmt|,
name|y0
decl_stmt|;
name|gint
name|dx
decl_stmt|,
name|dx0
decl_stmt|,
name|dy
decl_stmt|,
name|dy0
decl_stmt|;
name|gint
name|fx
decl_stmt|,
name|fx0
decl_stmt|,
name|fy
decl_stmt|,
name|fy0
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|brush_mask
operator|!=
name|NULL
operator|&&
name|dest_width
operator|!=
literal|0
operator|&&
name|dest_height
operator|!=
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|src_width
operator|=
name|brush_mask
operator|->
name|width
expr_stmt|;
name|src_height
operator|=
name|brush_mask
operator|->
name|height
expr_stmt|;
name|scale_brush
operator|=
name|mask_buf_new
argument_list|(
name|dest_width
argument_list|,
name|dest_height
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|scale_brush
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  get the data  */
name|dest
operator|=
name|mask_buf_data
argument_list|(
name|scale_brush
argument_list|)
expr_stmt|;
name|src
operator|=
name|mask_buf_data
argument_list|(
name|brush_mask
argument_list|)
expr_stmt|;
name|fx
operator|=
name|fx0
operator|=
operator|(
literal|256.0
operator|*
name|src_width
operator|)
operator|/
name|dest_width
expr_stmt|;
name|fy
operator|=
name|fy0
operator|=
operator|(
literal|256.0
operator|*
name|src_height
operator|)
operator|/
name|dest_height
expr_stmt|;
name|area
operator|=
name|fx0
operator|*
name|fy0
expr_stmt|;
name|x
operator|=
name|x0
operator|=
literal|0
expr_stmt|;
name|y
operator|=
name|y0
operator|=
literal|0
expr_stmt|;
name|dx
operator|=
name|dx0
operator|=
literal|0
expr_stmt|;
name|dy
operator|=
name|dy0
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|dest_height
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|dest_width
condition|;
name|j
operator|++
control|)
block|{
name|value
operator|=
literal|0
expr_stmt|;
name|fy
operator|=
name|fy0
expr_stmt|;
name|y
operator|=
name|y0
expr_stmt|;
name|dy
operator|=
name|dy0
expr_stmt|;
if|if
condition|(
name|dy
condition|)
block|{
name|fx
operator|=
name|fx0
expr_stmt|;
name|x
operator|=
name|x0
expr_stmt|;
name|dx
operator|=
name|dx0
expr_stmt|;
if|if
condition|(
name|dx
condition|)
block|{
name|value
operator|+=
name|dx
operator|*
name|dy
operator|*
name|src
index|[
name|x
operator|+
name|src_width
operator|*
name|y
index|]
expr_stmt|;
name|x
operator|++
expr_stmt|;
name|fx
operator|-=
name|dx
expr_stmt|;
name|dx
operator|=
literal|0
expr_stmt|;
block|}
while|while
condition|(
name|fx
operator|>=
literal|256
condition|)
block|{
name|value
operator|+=
literal|256
operator|*
name|dy
operator|*
name|src
index|[
name|x
operator|+
name|src_width
operator|*
name|y
index|]
expr_stmt|;
name|x
operator|++
expr_stmt|;
name|fx
operator|-=
literal|256
expr_stmt|;
block|}
if|if
condition|(
name|fx
condition|)
block|{
name|value
operator|+=
name|fx
operator|*
name|dy
operator|*
name|src
index|[
name|x
operator|+
name|src_width
operator|*
name|y
index|]
expr_stmt|;
name|dx
operator|=
literal|256
operator|-
name|fx
expr_stmt|;
block|}
name|y
operator|++
expr_stmt|;
name|fy
operator|-=
name|dy
expr_stmt|;
name|dy
operator|=
literal|0
expr_stmt|;
block|}
while|while
condition|(
name|fy
operator|>=
literal|256
condition|)
block|{
name|fx
operator|=
name|fx0
expr_stmt|;
name|x
operator|=
name|x0
expr_stmt|;
name|dx
operator|=
name|dx0
expr_stmt|;
if|if
condition|(
name|dx
condition|)
block|{
name|value
operator|+=
name|dx
operator|*
literal|256
operator|*
name|src
index|[
name|x
operator|+
name|src_width
operator|*
name|y
index|]
expr_stmt|;
name|x
operator|++
expr_stmt|;
name|fx
operator|-=
name|dx
expr_stmt|;
name|dx
operator|=
literal|0
expr_stmt|;
block|}
while|while
condition|(
name|fx
operator|>=
literal|256
condition|)
block|{
name|value
operator|+=
literal|256
operator|*
literal|256
operator|*
name|src
index|[
name|x
operator|+
name|src_width
operator|*
name|y
index|]
expr_stmt|;
name|x
operator|++
expr_stmt|;
name|fx
operator|-=
literal|256
expr_stmt|;
block|}
if|if
condition|(
name|fx
condition|)
block|{
name|value
operator|+=
name|fx
operator|*
literal|256
operator|*
name|src
index|[
name|x
operator|+
name|src_width
operator|*
name|y
index|]
expr_stmt|;
name|dx
operator|=
literal|256
operator|-
name|fx
expr_stmt|;
block|}
name|y
operator|++
expr_stmt|;
name|fy
operator|-=
literal|256
expr_stmt|;
block|}
if|if
condition|(
name|fy
condition|)
block|{
name|fx
operator|=
name|fx0
expr_stmt|;
name|x
operator|=
name|x0
expr_stmt|;
name|dx
operator|=
name|dx0
expr_stmt|;
if|if
condition|(
name|dx
condition|)
block|{
name|value
operator|+=
name|dx
operator|*
name|fy
operator|*
name|src
index|[
name|x
operator|+
name|src_width
operator|*
name|y
index|]
expr_stmt|;
name|x
operator|++
expr_stmt|;
name|fx
operator|-=
name|dx
expr_stmt|;
name|dx
operator|=
literal|0
expr_stmt|;
block|}
while|while
condition|(
name|fx
operator|>=
literal|256
condition|)
block|{
name|value
operator|+=
literal|256
operator|*
name|fy
operator|*
name|src
index|[
name|x
operator|+
name|src_width
operator|*
name|y
index|]
expr_stmt|;
name|x
operator|++
expr_stmt|;
name|fx
operator|-=
literal|256
expr_stmt|;
block|}
if|if
condition|(
name|fx
condition|)
block|{
name|value
operator|+=
name|fx
operator|*
name|fy
operator|*
name|src
index|[
name|x
operator|+
name|src_width
operator|*
name|y
index|]
expr_stmt|;
name|dx
operator|=
literal|256
operator|-
name|fx
expr_stmt|;
block|}
name|dy
operator|=
literal|256
operator|-
name|fy
expr_stmt|;
block|}
operator|*
name|dest
operator|++
operator|=
name|MIN
argument_list|(
operator|(
name|value
operator|/
name|area
operator|)
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|x0
operator|=
name|x
expr_stmt|;
name|dx0
operator|=
name|dx
expr_stmt|;
block|}
name|x0
operator|=
literal|0
expr_stmt|;
name|dx0
operator|=
literal|0
expr_stmt|;
name|y0
operator|=
name|y
expr_stmt|;
name|dy0
operator|=
name|dy
expr_stmt|;
block|}
return|return
name|scale_brush
return|;
block|}
end_function

begin_define
DECL|macro|ADD_RGB (dest,factor,src)
define|#
directive|define
name|ADD_RGB
parameter_list|(
name|dest
parameter_list|,
name|factor
parameter_list|,
name|src
parameter_list|)
define|\
value|dest[0] += factor * src[0]; \   dest[1] += factor * src[1]; \   dest[2] += factor * src[2];
end_define

begin_function
name|MaskBuf
modifier|*
DECL|function|brush_scale_pixmap (MaskBuf * pixmap,gint dest_width,gint dest_height)
name|brush_scale_pixmap
parameter_list|(
name|MaskBuf
modifier|*
name|pixmap
parameter_list|,
name|gint
name|dest_width
parameter_list|,
name|gint
name|dest_height
parameter_list|)
block|{
name|MaskBuf
modifier|*
name|scale_brush
decl_stmt|;
name|gint
name|src_width
decl_stmt|;
name|gint
name|src_height
decl_stmt|;
name|gint
name|value
index|[
literal|3
index|]
decl_stmt|;
name|gint
name|factor
decl_stmt|;
name|gint
name|area
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|x0
decl_stmt|,
name|y
decl_stmt|,
name|y0
decl_stmt|;
name|gint
name|dx
decl_stmt|,
name|dx0
decl_stmt|,
name|dy
decl_stmt|,
name|dy0
decl_stmt|;
name|gint
name|fx
decl_stmt|,
name|fx0
decl_stmt|,
name|fy
decl_stmt|,
name|fy0
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|src_ptr
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|pixmap
operator|!=
name|NULL
operator|&&
name|pixmap
operator|->
name|bytes
operator|==
literal|3
operator|&&
name|dest_width
operator|!=
literal|0
operator|&&
name|dest_height
operator|!=
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|src_width
operator|=
name|pixmap
operator|->
name|width
expr_stmt|;
name|src_height
operator|=
name|pixmap
operator|->
name|height
expr_stmt|;
name|scale_brush
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
name|g_return_val_if_fail
argument_list|(
name|scale_brush
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  get the data  */
name|dest
operator|=
name|mask_buf_data
argument_list|(
name|scale_brush
argument_list|)
expr_stmt|;
name|src
operator|=
name|mask_buf_data
argument_list|(
name|pixmap
argument_list|)
expr_stmt|;
name|fx
operator|=
name|fx0
operator|=
operator|(
literal|256.0
operator|*
name|src_width
operator|)
operator|/
name|dest_width
expr_stmt|;
name|fy
operator|=
name|fy0
operator|=
operator|(
literal|256.0
operator|*
name|src_height
operator|)
operator|/
name|dest_height
expr_stmt|;
name|area
operator|=
name|fx0
operator|*
name|fy0
expr_stmt|;
name|x
operator|=
name|x0
operator|=
literal|0
expr_stmt|;
name|y
operator|=
name|y0
operator|=
literal|0
expr_stmt|;
name|dx
operator|=
name|dx0
operator|=
literal|0
expr_stmt|;
name|dy
operator|=
name|dy0
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|dest_height
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|dest_width
condition|;
name|j
operator|++
control|)
block|{
name|value
index|[
literal|0
index|]
operator|=
literal|0
expr_stmt|;
name|value
index|[
literal|1
index|]
operator|=
literal|0
expr_stmt|;
name|value
index|[
literal|2
index|]
operator|=
literal|0
expr_stmt|;
name|fy
operator|=
name|fy0
expr_stmt|;
name|y
operator|=
name|y0
expr_stmt|;
name|dy
operator|=
name|dy0
expr_stmt|;
if|if
condition|(
name|dy
condition|)
block|{
name|fx
operator|=
name|fx0
expr_stmt|;
name|x
operator|=
name|x0
expr_stmt|;
name|dx
operator|=
name|dx0
expr_stmt|;
if|if
condition|(
name|dx
condition|)
block|{
name|factor
operator|=
name|dx
operator|*
name|dy
expr_stmt|;
name|src_ptr
operator|=
name|src
operator|+
literal|3
operator|*
operator|(
name|x
operator|+
name|y
operator|*
name|src_width
operator|)
expr_stmt|;
name|ADD_RGB
argument_list|(
name|value
argument_list|,
name|factor
argument_list|,
name|src_ptr
argument_list|)
expr_stmt|;
name|x
operator|++
expr_stmt|;
name|fx
operator|-=
name|dx
expr_stmt|;
name|dx
operator|=
literal|0
expr_stmt|;
block|}
while|while
condition|(
name|fx
operator|>=
literal|256
condition|)
block|{
name|factor
operator|=
literal|256
operator|*
name|dy
expr_stmt|;
name|src_ptr
operator|=
name|src
operator|+
literal|3
operator|*
operator|(
name|x
operator|+
name|y
operator|*
name|src_width
operator|)
expr_stmt|;
name|ADD_RGB
argument_list|(
name|value
argument_list|,
name|factor
argument_list|,
name|src_ptr
argument_list|)
expr_stmt|;
name|x
operator|++
expr_stmt|;
name|fx
operator|-=
literal|256
expr_stmt|;
block|}
if|if
condition|(
name|fx
condition|)
block|{
name|factor
operator|=
name|fx
operator|*
name|dy
expr_stmt|;
name|src_ptr
operator|=
name|src
operator|+
literal|3
operator|*
operator|(
name|x
operator|+
name|y
operator|*
name|src_width
operator|)
expr_stmt|;
name|ADD_RGB
argument_list|(
name|value
argument_list|,
name|factor
argument_list|,
name|src_ptr
argument_list|)
expr_stmt|;
name|dx
operator|=
literal|256
operator|-
name|fx
expr_stmt|;
block|}
name|y
operator|++
expr_stmt|;
name|fy
operator|-=
name|dy
expr_stmt|;
name|dy
operator|=
literal|0
expr_stmt|;
block|}
while|while
condition|(
name|fy
operator|>=
literal|256
condition|)
block|{
name|fx
operator|=
name|fx0
expr_stmt|;
name|x
operator|=
name|x0
expr_stmt|;
name|dx
operator|=
name|dx0
expr_stmt|;
if|if
condition|(
name|dx
condition|)
block|{
name|factor
operator|=
name|dx
operator|*
literal|256
expr_stmt|;
name|src_ptr
operator|=
name|src
operator|+
literal|3
operator|*
operator|(
name|x
operator|+
name|y
operator|*
name|src_width
operator|)
expr_stmt|;
name|ADD_RGB
argument_list|(
name|value
argument_list|,
name|factor
argument_list|,
name|src_ptr
argument_list|)
expr_stmt|;
name|x
operator|++
expr_stmt|;
name|fx
operator|-=
name|dx
expr_stmt|;
name|dx
operator|=
literal|0
expr_stmt|;
block|}
while|while
condition|(
name|fx
operator|>=
literal|256
condition|)
block|{
name|factor
operator|=
literal|256
operator|*
literal|256
expr_stmt|;
name|src_ptr
operator|=
name|src
operator|+
literal|3
operator|*
operator|(
name|x
operator|+
name|y
operator|*
name|src_width
operator|)
expr_stmt|;
name|ADD_RGB
argument_list|(
name|value
argument_list|,
name|factor
argument_list|,
name|src_ptr
argument_list|)
expr_stmt|;
name|x
operator|++
expr_stmt|;
name|fx
operator|-=
literal|256
expr_stmt|;
block|}
if|if
condition|(
name|fx
condition|)
block|{
name|factor
operator|=
name|fx
operator|*
literal|256
expr_stmt|;
name|src_ptr
operator|=
name|src
operator|+
literal|3
operator|*
operator|(
name|x
operator|+
name|y
operator|*
name|src_width
operator|)
expr_stmt|;
name|ADD_RGB
argument_list|(
name|value
argument_list|,
name|factor
argument_list|,
name|src_ptr
argument_list|)
expr_stmt|;
name|dx
operator|=
literal|256
operator|-
name|fx
expr_stmt|;
block|}
name|y
operator|++
expr_stmt|;
name|fy
operator|-=
literal|256
expr_stmt|;
block|}
if|if
condition|(
name|fy
condition|)
block|{
name|fx
operator|=
name|fx0
expr_stmt|;
name|x
operator|=
name|x0
expr_stmt|;
name|dx
operator|=
name|dx0
expr_stmt|;
if|if
condition|(
name|dx
condition|)
block|{
name|factor
operator|=
name|dx
operator|*
name|fy
expr_stmt|;
name|src_ptr
operator|=
name|src
operator|+
literal|3
operator|*
operator|(
name|x
operator|+
name|y
operator|*
name|src_width
operator|)
expr_stmt|;
name|ADD_RGB
argument_list|(
name|value
argument_list|,
name|factor
argument_list|,
name|src_ptr
argument_list|)
expr_stmt|;
name|x
operator|++
expr_stmt|;
name|fx
operator|-=
name|dx
expr_stmt|;
name|dx
operator|=
literal|0
expr_stmt|;
block|}
while|while
condition|(
name|fx
operator|>=
literal|256
condition|)
block|{
name|factor
operator|=
literal|256
operator|*
name|fy
expr_stmt|;
name|src_ptr
operator|=
name|src
operator|+
literal|3
operator|*
operator|(
name|x
operator|+
name|y
operator|*
name|src_width
operator|)
expr_stmt|;
name|ADD_RGB
argument_list|(
name|value
argument_list|,
name|factor
argument_list|,
name|src_ptr
argument_list|)
expr_stmt|;
name|x
operator|++
expr_stmt|;
name|fx
operator|-=
literal|256
expr_stmt|;
block|}
if|if
condition|(
name|fx
condition|)
block|{
name|factor
operator|=
name|fx
operator|*
name|fy
expr_stmt|;
name|src_ptr
operator|=
name|src
operator|+
literal|3
operator|*
operator|(
name|x
operator|+
name|y
operator|*
name|src_width
operator|)
expr_stmt|;
name|ADD_RGB
argument_list|(
name|value
argument_list|,
name|factor
argument_list|,
name|src_ptr
argument_list|)
expr_stmt|;
name|dx
operator|=
literal|256
operator|-
name|fx
expr_stmt|;
block|}
name|dy
operator|=
literal|256
operator|-
name|fy
expr_stmt|;
block|}
operator|*
name|dest
operator|++
operator|=
name|MIN
argument_list|(
operator|(
name|value
index|[
literal|0
index|]
operator|/
name|area
operator|)
argument_list|,
literal|255
argument_list|)
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|MIN
argument_list|(
operator|(
name|value
index|[
literal|1
index|]
operator|/
name|area
operator|)
argument_list|,
literal|255
argument_list|)
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|MIN
argument_list|(
operator|(
name|value
index|[
literal|2
index|]
operator|/
name|area
operator|)
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|x0
operator|=
name|x
expr_stmt|;
name|dx0
operator|=
name|dx
expr_stmt|;
block|}
name|x0
operator|=
literal|0
expr_stmt|;
name|dx0
operator|=
literal|0
expr_stmt|;
name|y0
operator|=
name|y
expr_stmt|;
name|dy0
operator|=
name|dy
expr_stmt|;
block|}
return|return
name|scale_brush
return|;
block|}
end_function

begin_undef
undef|#
directive|undef
name|ADD_RGB
end_undef

end_unit

