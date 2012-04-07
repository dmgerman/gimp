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
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_include
include|#
directive|include
file|<babl/babl.h>
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"base-types.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"temp-buf.h"
end_include

begin_function_decl
specifier|static
name|void
name|temp_buf_to_color
parameter_list|(
name|TempBuf
modifier|*
name|src_buf
parameter_list|,
name|TempBuf
modifier|*
name|dest_buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|temp_buf_to_gray
parameter_list|(
name|TempBuf
modifier|*
name|src_buf
parameter_list|,
name|TempBuf
modifier|*
name|dest_buf
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|TempBuf
modifier|*
DECL|function|temp_buf_new (gint width,gint height,gint bytes)
name|temp_buf_new
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bytes
parameter_list|)
block|{
name|TempBuf
modifier|*
name|temp
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
operator|&&
name|height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|bytes
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|temp
operator|=
name|g_slice_new
argument_list|(
name|TempBuf
argument_list|)
expr_stmt|;
name|temp
operator|->
name|bytes
operator|=
name|bytes
expr_stmt|;
name|temp
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|temp
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|temp
operator|->
name|x
operator|=
literal|0
expr_stmt|;
name|temp
operator|->
name|y
operator|=
literal|0
expr_stmt|;
name|temp
operator|->
name|data
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|height
operator|*
name|bytes
argument_list|)
expr_stmt|;
return|return
name|temp
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|temp_buf_copy (TempBuf * src,TempBuf * dest)
name|temp_buf_copy
parameter_list|(
name|TempBuf
modifier|*
name|src
parameter_list|,
name|TempBuf
modifier|*
name|dest
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|src
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|!
name|dest
operator|||
operator|(
name|dest
operator|->
name|width
operator|==
name|src
operator|->
name|width
operator|&&
name|dest
operator|->
name|height
operator|==
name|src
operator|->
name|height
operator|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dest
condition|)
name|dest
operator|=
name|temp_buf_new
argument_list|(
name|src
operator|->
name|width
argument_list|,
name|src
operator|->
name|height
argument_list|,
name|src
operator|->
name|bytes
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dest
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|src
operator|->
name|bytes
operator|!=
name|dest
operator|->
name|bytes
condition|)
block|{
if|if
condition|(
name|src
operator|->
name|bytes
operator|==
literal|4
operator|&&
name|dest
operator|->
name|bytes
operator|==
literal|2
condition|)
comment|/* RGBA  -> GRAYA */
name|temp_buf_to_gray
argument_list|(
name|src
argument_list|,
name|dest
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|bytes
operator|==
literal|3
operator|&&
name|dest
operator|->
name|bytes
operator|==
literal|1
condition|)
comment|/* RGB   -> GRAY  */
name|temp_buf_to_gray
argument_list|(
name|src
argument_list|,
name|dest
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|bytes
operator|==
literal|2
operator|&&
name|dest
operator|->
name|bytes
operator|==
literal|4
condition|)
comment|/* GRAYA -> RGBA  */
name|temp_buf_to_color
argument_list|(
name|src
argument_list|,
name|dest
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|bytes
operator|==
literal|1
operator|&&
name|dest
operator|->
name|bytes
operator|==
literal|3
condition|)
comment|/* GRAY  -> RGB   */
name|temp_buf_to_color
argument_list|(
name|src
argument_list|,
name|dest
argument_list|)
expr_stmt|;
else|else
name|g_warning
argument_list|(
literal|"temp_buf_copy(): unimplemented color conversion"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|memcpy
argument_list|(
name|temp_buf_get_data
argument_list|(
name|dest
argument_list|)
argument_list|,
name|temp_buf_get_data
argument_list|(
name|src
argument_list|)
argument_list|,
name|temp_buf_get_data_size
argument_list|(
name|src
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|dest
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|temp_buf_resize (TempBuf * buf,gint bytes,gint x,gint y,gint width,gint height)
name|temp_buf_resize
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
operator|&&
name|height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|buf
condition|)
block|{
name|buf
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
name|buf
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|buf
operator|->
name|y
operator|=
name|y
expr_stmt|;
block|}
else|else
block|{
name|gsize
name|size
init|=
name|width
operator|*
name|height
operator|*
name|bytes
decl_stmt|;
if|if
condition|(
name|size
operator|!=
operator|(
name|buf
operator|->
name|width
operator|*
name|buf
operator|->
name|height
operator|*
name|buf
operator|->
name|bytes
operator|)
condition|)
block|{
name|buf
operator|->
name|data
operator|=
name|g_renew
argument_list|(
name|guchar
argument_list|,
name|buf
operator|->
name|data
argument_list|,
name|size
argument_list|)
expr_stmt|;
block|}
name|buf
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|buf
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|buf
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|buf
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|buf
operator|->
name|bytes
operator|=
name|bytes
expr_stmt|;
block|}
return|return
name|buf
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|temp_buf_scale (TempBuf * src,gint new_width,gint new_height)
name|temp_buf_scale
parameter_list|(
name|TempBuf
modifier|*
name|src
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|)
block|{
name|TempBuf
modifier|*
name|dest
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src_data
decl_stmt|;
name|guchar
modifier|*
name|dest_data
decl_stmt|;
name|gdouble
name|x_ratio
decl_stmt|;
name|gdouble
name|y_ratio
decl_stmt|;
name|gint
name|loop1
decl_stmt|;
name|gint
name|loop2
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|new_width
operator|>
literal|0
operator|&&
name|new_height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dest
operator|=
name|temp_buf_new
argument_list|(
name|new_width
argument_list|,
name|new_height
argument_list|,
name|src
operator|->
name|bytes
argument_list|)
expr_stmt|;
name|src_data
operator|=
name|temp_buf_get_data
argument_list|(
name|src
argument_list|)
expr_stmt|;
name|dest_data
operator|=
name|temp_buf_get_data
argument_list|(
name|dest
argument_list|)
expr_stmt|;
name|x_ratio
operator|=
operator|(
name|gdouble
operator|)
name|src
operator|->
name|width
operator|/
operator|(
name|gdouble
operator|)
name|new_width
expr_stmt|;
name|y_ratio
operator|=
operator|(
name|gdouble
operator|)
name|src
operator|->
name|height
operator|/
operator|(
name|gdouble
operator|)
name|new_height
expr_stmt|;
for|for
control|(
name|loop1
operator|=
literal|0
init|;
name|loop1
operator|<
name|new_height
condition|;
name|loop1
operator|++
control|)
block|{
for|for
control|(
name|loop2
operator|=
literal|0
init|;
name|loop2
operator|<
name|new_width
condition|;
name|loop2
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|src_pixel
decl_stmt|;
name|guchar
modifier|*
name|dest_pixel
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|src_pixel
operator|=
name|src_data
operator|+
call|(
name|gint
call|)
argument_list|(
name|loop2
operator|*
name|x_ratio
argument_list|)
operator|*
name|src
operator|->
name|bytes
operator|+
call|(
name|gint
call|)
argument_list|(
name|loop1
operator|*
name|y_ratio
argument_list|)
operator|*
name|src
operator|->
name|bytes
operator|*
name|src
operator|->
name|width
expr_stmt|;
name|dest_pixel
operator|=
name|dest_data
operator|+
operator|(
name|loop2
operator|+
name|loop1
operator|*
name|new_width
operator|)
operator|*
name|src
operator|->
name|bytes
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|src
operator|->
name|bytes
condition|;
name|i
operator|++
control|)
operator|*
name|dest_pixel
operator|++
operator|=
operator|*
name|src_pixel
operator|++
expr_stmt|;
block|}
block|}
return|return
name|dest
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|temp_buf_copy_area (TempBuf * src,TempBuf * dest,gint x,gint y,gint width,gint height,gint dest_x,gint dest_y)
name|temp_buf_copy_area
parameter_list|(
name|TempBuf
modifier|*
name|src
parameter_list|,
name|TempBuf
modifier|*
name|dest
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|dest_x
parameter_list|,
name|gint
name|dest_y
parameter_list|)
block|{
name|TempBuf
modifier|*
name|new
decl_stmt|;
name|PixelRegion
name|srcPR
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|PixelRegion
name|destPR
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src
operator|!=
name|NULL
argument_list|,
name|dest
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|!
name|dest
operator|||
name|dest
operator|->
name|bytes
operator|==
name|src
operator|->
name|bytes
argument_list|,
name|dest
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|+
name|dest_x
operator|>
literal|0
argument_list|,
name|dest
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|height
operator|+
name|dest_y
operator|>
literal|0
argument_list|,
name|dest
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|!
name|dest
operator|||
name|dest
operator|->
name|width
operator|>=
name|width
operator|+
name|dest_x
argument_list|,
name|dest
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|!
name|dest
operator|||
name|dest
operator|->
name|height
operator|>=
name|height
operator|+
name|dest_y
argument_list|,
name|dest
argument_list|)
expr_stmt|;
comment|/*  some bounds checking  */
name|x1
operator|=
name|CLAMP
argument_list|(
name|x
argument_list|,
literal|0
argument_list|,
name|src
operator|->
name|width
operator|-
literal|1
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|y
argument_list|,
literal|0
argument_list|,
name|src
operator|->
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|x
operator|+
name|width
operator|-
literal|1
argument_list|,
literal|0
argument_list|,
name|src
operator|->
name|width
operator|-
literal|1
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|y
operator|+
name|height
operator|-
literal|1
argument_list|,
literal|0
argument_list|,
name|src
operator|->
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|x2
operator|-
name|x1
operator|)
operator|||
operator|!
operator|(
name|y2
operator|-
name|y1
operator|)
condition|)
return|return
name|dest
return|;
name|width
operator|=
name|x2
operator|-
name|x1
operator|+
literal|1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
operator|+
literal|1
expr_stmt|;
if|if
condition|(
operator|!
name|dest
condition|)
block|{
name|new
operator|=
name|temp_buf_new
argument_list|(
name|width
operator|+
name|dest_x
argument_list|,
name|height
operator|+
name|dest_y
argument_list|,
name|src
operator|->
name|bytes
argument_list|)
expr_stmt|;
name|temp_buf_data_clear
argument_list|(
name|new
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|new
operator|=
name|dest
expr_stmt|;
block|}
comment|/*  Copy the region  */
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|srcPR
argument_list|,
name|src
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|destPR
argument_list|,
name|new
argument_list|,
name|dest_x
argument_list|,
name|dest_y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
return|return
name|new
return|;
block|}
end_function

begin_comment
comment|/**  * temp_buf_demultiply:  * @buf:  *  * Converts a TempBuf with pre-multiplied alpha to a 'normal' TempBuf.  */
end_comment

begin_function
name|void
DECL|function|temp_buf_demultiply (TempBuf * buf)
name|temp_buf_demultiply
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|)
block|{
name|guchar
modifier|*
name|data
decl_stmt|;
name|gint
name|pixels
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|buf
operator|!=
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|buf
operator|->
name|bytes
condition|)
block|{
case|case
literal|1
case|:
break|break;
case|case
literal|2
case|:
name|data
operator|=
name|temp_buf_get_data
argument_list|(
name|buf
argument_list|)
expr_stmt|;
name|pixels
operator|=
name|buf
operator|->
name|width
operator|*
name|buf
operator|->
name|height
expr_stmt|;
while|while
condition|(
name|pixels
operator|--
condition|)
block|{
name|data
index|[
literal|0
index|]
operator|=
operator|(
name|data
index|[
literal|0
index|]
operator|<<
literal|8
operator|)
operator|/
operator|(
name|data
index|[
literal|1
index|]
operator|+
literal|1
operator|)
expr_stmt|;
name|data
operator|+=
literal|2
expr_stmt|;
block|}
break|break;
case|case
literal|3
case|:
break|break;
case|case
literal|4
case|:
name|data
operator|=
name|temp_buf_get_data
argument_list|(
name|buf
argument_list|)
expr_stmt|;
name|pixels
operator|=
name|buf
operator|->
name|width
operator|*
name|buf
operator|->
name|height
expr_stmt|;
while|while
condition|(
name|pixels
operator|--
condition|)
block|{
name|data
index|[
literal|0
index|]
operator|=
operator|(
name|data
index|[
literal|0
index|]
operator|<<
literal|8
operator|)
operator|/
operator|(
name|data
index|[
literal|3
index|]
operator|+
literal|1
operator|)
expr_stmt|;
name|data
index|[
literal|1
index|]
operator|=
operator|(
name|data
index|[
literal|1
index|]
operator|<<
literal|8
operator|)
operator|/
operator|(
name|data
index|[
literal|3
index|]
operator|+
literal|1
operator|)
expr_stmt|;
name|data
index|[
literal|2
index|]
operator|=
operator|(
name|data
index|[
literal|2
index|]
operator|<<
literal|8
operator|)
operator|/
operator|(
name|data
index|[
literal|3
index|]
operator|+
literal|1
operator|)
expr_stmt|;
name|data
operator|+=
literal|4
expr_stmt|;
block|}
break|break;
default|default:
name|g_return_if_reached
argument_list|()
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
name|void
DECL|function|temp_buf_free (TempBuf * buf)
name|temp_buf_free
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|buf
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|buf
operator|->
name|data
condition|)
name|g_free
argument_list|(
name|buf
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|TempBuf
argument_list|,
name|buf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|guchar
modifier|*
DECL|function|temp_buf_get_data (const TempBuf * buf)
name|temp_buf_get_data
parameter_list|(
specifier|const
name|TempBuf
modifier|*
name|buf
parameter_list|)
block|{
return|return
name|buf
operator|->
name|data
return|;
block|}
end_function

begin_function
name|gsize
DECL|function|temp_buf_get_data_size (TempBuf * buf)
name|temp_buf_get_data_size
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|)
block|{
return|return
name|buf
operator|->
name|bytes
operator|*
name|buf
operator|->
name|width
operator|*
name|buf
operator|->
name|height
return|;
block|}
end_function

begin_function
name|guchar
modifier|*
DECL|function|temp_buf_data_clear (TempBuf * buf)
name|temp_buf_data_clear
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|)
block|{
name|memset
argument_list|(
name|buf
operator|->
name|data
argument_list|,
literal|0
argument_list|,
name|buf
operator|->
name|height
operator|*
name|buf
operator|->
name|width
operator|*
name|buf
operator|->
name|bytes
argument_list|)
expr_stmt|;
return|return
name|buf
operator|->
name|data
return|;
block|}
end_function

begin_function
name|gsize
DECL|function|temp_buf_get_memsize (TempBuf * buf)
name|temp_buf_get_memsize
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|)
block|{
if|if
condition|(
name|buf
condition|)
return|return
operator|(
sizeof|sizeof
argument_list|(
name|TempBuf
argument_list|)
operator|+
name|temp_buf_get_data_size
argument_list|(
name|buf
argument_list|)
operator|)
return|;
return|return
literal|0
return|;
block|}
end_function

begin_comment
comment|/**  * temp_buf_dump:  * @buf:  * @file:  *  * Dumps a TempBuf to a raw RGB image that is easy to analyze, for  * example with GIMP.  **/
end_comment

begin_function
name|void
DECL|function|temp_buf_dump (TempBuf * buf,const gchar * filename)
name|temp_buf_dump
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|gint
name|fd
init|=
name|g_open
argument_list|(
name|filename
argument_list|,
name|O_CREAT
operator||
name|O_TRUNC
operator||
name|O_WRONLY
argument_list|,
literal|0666
argument_list|)
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|fd
operator|!=
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|buf
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|temp_buf_get_data
argument_list|(
name|buf
argument_list|)
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|write
argument_list|(
name|fd
argument_list|,
name|temp_buf_get_data
argument_list|(
name|buf
argument_list|)
argument_list|,
name|temp_buf_get_data_size
argument_list|(
name|buf
argument_list|)
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  The conversion routines  */
end_comment

begin_function
specifier|static
name|void
DECL|function|temp_buf_to_color (TempBuf * src_buf,TempBuf * dest_buf)
name|temp_buf_to_color
parameter_list|(
name|TempBuf
modifier|*
name|src_buf
parameter_list|,
name|TempBuf
modifier|*
name|dest_buf
parameter_list|)
block|{
name|guchar
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|glong
name|num_pixels
decl_stmt|;
name|src
operator|=
name|temp_buf_get_data
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
name|dest
operator|=
name|temp_buf_get_data
argument_list|(
name|dest_buf
argument_list|)
expr_stmt|;
name|num_pixels
operator|=
name|src_buf
operator|->
name|width
operator|*
name|src_buf
operator|->
name|height
expr_stmt|;
switch|switch
condition|(
name|dest_buf
operator|->
name|bytes
condition|)
block|{
case|case
literal|3
case|:
name|g_return_if_fail
argument_list|(
name|src_buf
operator|->
name|bytes
operator|==
literal|1
argument_list|)
expr_stmt|;
while|while
condition|(
name|num_pixels
operator|--
condition|)
block|{
name|guchar
name|tmp
decl_stmt|;
operator|*
name|dest
operator|++
operator|=
name|tmp
operator|=
operator|*
name|src
operator|++
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|tmp
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|tmp
expr_stmt|;
block|}
break|break;
case|case
literal|4
case|:
name|g_return_if_fail
argument_list|(
name|src_buf
operator|->
name|bytes
operator|==
literal|2
argument_list|)
expr_stmt|;
while|while
condition|(
name|num_pixels
operator|--
condition|)
block|{
name|guchar
name|tmp
decl_stmt|;
operator|*
name|dest
operator|++
operator|=
name|tmp
operator|=
operator|*
name|src
operator|++
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|tmp
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|tmp
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
comment|/* alpha channel */
block|}
break|break;
default|default:
name|g_return_if_reached
argument_list|()
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|temp_buf_to_gray (TempBuf * src_buf,TempBuf * dest_buf)
name|temp_buf_to_gray
parameter_list|(
name|TempBuf
modifier|*
name|src_buf
parameter_list|,
name|TempBuf
modifier|*
name|dest_buf
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|glong
name|num_pixels
decl_stmt|;
name|src
operator|=
name|temp_buf_get_data
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
name|dest
operator|=
name|temp_buf_get_data
argument_list|(
name|dest_buf
argument_list|)
expr_stmt|;
name|num_pixels
operator|=
name|src_buf
operator|->
name|width
operator|*
name|src_buf
operator|->
name|height
expr_stmt|;
switch|switch
condition|(
name|dest_buf
operator|->
name|bytes
condition|)
block|{
case|case
literal|1
case|:
name|g_return_if_fail
argument_list|(
name|src_buf
operator|->
name|bytes
operator|==
literal|3
argument_list|)
expr_stmt|;
while|while
condition|(
name|num_pixels
operator|--
condition|)
block|{
name|gint
name|lum
init|=
name|GIMP_RGB_LUMINANCE
argument_list|(
name|src
index|[
literal|0
index|]
argument_list|,
name|src
index|[
literal|1
index|]
argument_list|,
name|src
index|[
literal|2
index|]
argument_list|)
operator|+
literal|0.5
decl_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|(
name|guchar
operator|)
name|lum
expr_stmt|;
name|src
operator|+=
literal|3
expr_stmt|;
block|}
break|break;
case|case
literal|2
case|:
name|g_return_if_fail
argument_list|(
name|src_buf
operator|->
name|bytes
operator|==
literal|4
argument_list|)
expr_stmt|;
while|while
condition|(
name|num_pixels
operator|--
condition|)
block|{
name|gint
name|lum
init|=
name|GIMP_RGB_LUMINANCE
argument_list|(
name|src
index|[
literal|0
index|]
argument_list|,
name|src
index|[
literal|1
index|]
argument_list|,
name|src
index|[
literal|2
index|]
argument_list|)
operator|+
literal|0.5
decl_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|(
name|guchar
operator|)
name|lum
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|src
index|[
literal|3
index|]
expr_stmt|;
comment|/* alpha channel */
name|src
operator|+=
literal|4
expr_stmt|;
block|}
break|break;
default|default:
name|g_return_if_reached
argument_list|()
expr_stmt|;
break|break;
block|}
block|}
end_function

end_unit

