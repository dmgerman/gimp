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
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<process.h>
end_include

begin_comment
comment|/* For _getpid() */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"paint_funcs.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpcolorspace.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|unsigned
name|char
modifier|*
name|temp_buf_allocate
parameter_list|(
name|unsigned
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|temp_buf_to_color
parameter_list|(
name|TempBuf
modifier|*
parameter_list|,
name|TempBuf
modifier|*
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
parameter_list|,
name|TempBuf
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Memory management  */
end_comment

begin_function
specifier|static
name|unsigned
name|char
modifier|*
DECL|function|temp_buf_allocate (unsigned int size)
name|temp_buf_allocate
parameter_list|(
name|unsigned
name|int
name|size
parameter_list|)
block|{
name|unsigned
name|char
modifier|*
name|data
decl_stmt|;
name|data
operator|=
operator|(
name|unsigned
name|char
operator|*
operator|)
name|g_malloc
argument_list|(
name|size
argument_list|)
expr_stmt|;
return|return
name|data
return|;
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
name|unsigned
name|char
modifier|*
name|src
decl_stmt|;
name|unsigned
name|char
modifier|*
name|dest
decl_stmt|;
name|long
name|num_bytes
decl_stmt|;
name|src
operator|=
name|temp_buf_data
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
name|dest
operator|=
name|temp_buf_data
argument_list|(
name|dest_buf
argument_list|)
expr_stmt|;
name|num_bytes
operator|=
name|src_buf
operator|->
name|width
operator|*
name|src_buf
operator|->
name|height
expr_stmt|;
while|while
condition|(
name|num_bytes
operator|--
condition|)
block|{
name|unsigned
name|char
name|tmpch
decl_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
comment|/* alpha channel */
operator|*
name|dest
operator|++
operator|=
name|tmpch
operator|=
operator|*
name|src
operator|++
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|tmpch
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|tmpch
expr_stmt|;
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
name|unsigned
name|char
modifier|*
name|src
decl_stmt|;
name|unsigned
name|char
modifier|*
name|dest
decl_stmt|;
name|long
name|num_bytes
decl_stmt|;
name|float
name|pix
decl_stmt|;
name|src
operator|=
name|temp_buf_data
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
name|dest
operator|=
name|temp_buf_data
argument_list|(
name|dest_buf
argument_list|)
expr_stmt|;
name|num_bytes
operator|=
name|src_buf
operator|->
name|width
operator|*
name|src_buf
operator|->
name|height
expr_stmt|;
while|while
condition|(
name|num_bytes
operator|--
condition|)
block|{
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
comment|/* alpha channel */
name|pix
operator|=
name|INTENSITY
argument_list|(
operator|*
name|src
operator|++
argument_list|,
operator|*
name|src
operator|++
argument_list|,
operator|*
name|src
operator|++
argument_list|)
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|(
name|unsigned
name|char
operator|)
name|pix
expr_stmt|;
block|}
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|temp_buf_new (int width,int height,int bytes,int x,int y,unsigned char * col)
name|temp_buf_new
parameter_list|(
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|,
name|int
name|bytes
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|unsigned
name|char
modifier|*
name|col
parameter_list|)
block|{
name|long
name|i
decl_stmt|;
name|int
name|j
decl_stmt|;
name|unsigned
name|char
modifier|*
name|data
decl_stmt|;
name|TempBuf
modifier|*
name|temp
decl_stmt|;
name|temp
operator|=
operator|(
name|TempBuf
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|TempBuf
argument_list|)
argument_list|)
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
name|bytes
operator|=
name|bytes
expr_stmt|;
name|temp
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|temp
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|temp
operator|->
name|swapped
operator|=
name|FALSE
expr_stmt|;
name|temp
operator|->
name|filename
operator|=
name|NULL
expr_stmt|;
name|temp
operator|->
name|data
operator|=
name|data
operator|=
name|temp_buf_allocate
argument_list|(
name|width
operator|*
name|height
operator|*
name|bytes
argument_list|)
expr_stmt|;
comment|/*  initialize the data  */
if|if
condition|(
name|col
condition|)
block|{
comment|/* First check if we can save a lot of work */
if|if
condition|(
name|bytes
operator|==
literal|1
condition|)
block|{
name|memset
argument_list|(
name|data
argument_list|,
operator|*
name|col
argument_list|,
name|width
operator|*
name|height
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|bytes
operator|==
literal|3
operator|)
operator|&&
operator|(
name|col
index|[
literal|1
index|]
operator|==
operator|*
name|col
operator|)
operator|&&
operator|(
operator|*
name|col
operator|==
name|col
index|[
literal|2
index|]
operator|)
condition|)
block|{
name|memset
argument_list|(
name|data
argument_list|,
operator|*
name|col
argument_list|,
name|width
operator|*
name|height
operator|*
literal|3
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|bytes
operator|==
literal|4
operator|)
operator|&&
operator|(
name|col
index|[
literal|1
index|]
operator|==
operator|*
name|col
operator|)
operator|&&
operator|(
operator|*
name|col
operator|==
name|col
index|[
literal|2
index|]
operator|)
operator|&&
operator|(
name|col
index|[
literal|2
index|]
operator|==
name|col
index|[
literal|3
index|]
operator|)
condition|)
block|{
name|memset
argument_list|(
name|data
argument_list|,
operator|*
name|col
argument_list|,
operator|(
name|width
operator|*
name|height
operator|)
operator|<<
literal|2
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* No, we cannot */
name|unsigned
name|char
modifier|*
name|dptr
decl_stmt|;
comment|/* Fill the first row */
name|dptr
operator|=
name|data
expr_stmt|;
for|for
control|(
name|i
operator|=
name|width
operator|-
literal|1
init|;
name|i
operator|>=
literal|0
condition|;
operator|--
name|i
control|)
block|{
name|unsigned
name|char
modifier|*
name|init
decl_stmt|;
name|j
operator|=
name|bytes
expr_stmt|;
name|init
operator|=
name|col
expr_stmt|;
while|while
condition|(
name|j
operator|--
condition|)
operator|*
name|dptr
operator|++
operator|=
operator|*
name|init
operator|++
expr_stmt|;
block|}
comment|/* Now copy from it (we set bytes to bytesperrow now) */
name|bytes
operator|*=
name|width
expr_stmt|;
while|while
condition|(
operator|--
name|height
condition|)
block|{
name|memcpy
argument_list|(
name|dptr
argument_list|,
name|data
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
name|dptr
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
block|}
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
name|TempBuf
modifier|*
name|new
decl_stmt|;
name|long
name|length
decl_stmt|;
if|if
condition|(
operator|!
name|src
condition|)
block|{
name|g_message
argument_list|(
literal|"trying to copy a temp buf which is NULL."
argument_list|)
expr_stmt|;
return|return
name|dest
return|;
block|}
if|if
condition|(
operator|!
name|dest
condition|)
name|new
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
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
block|{
name|new
operator|=
name|dest
expr_stmt|;
if|if
condition|(
name|dest
operator|->
name|width
operator|!=
name|src
operator|->
name|width
operator|||
name|dest
operator|->
name|height
operator|!=
name|src
operator|->
name|height
condition|)
name|g_message
argument_list|(
literal|"In temp_buf_copy, the widths or heights don't match."
argument_list|)
expr_stmt|;
comment|/*  The temp buf is smart, and can translate between color and gray  */
comment|/*  (only necessary if not we allocated it */
if|if
condition|(
name|src
operator|->
name|bytes
operator|!=
name|new
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
condition|)
comment|/* RGB color */
name|temp_buf_to_gray
argument_list|(
name|src
argument_list|,
name|new
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
condition|)
comment|/* grayscale */
name|temp_buf_to_color
argument_list|(
name|src
argument_list|,
name|new
argument_list|)
expr_stmt|;
else|else
name|g_message
argument_list|(
literal|"Cannot convert from indexed color."
argument_list|)
expr_stmt|;
return|return
name|new
return|;
block|}
block|}
comment|/* make the copy */
name|length
operator|=
name|src
operator|->
name|width
operator|*
name|src
operator|->
name|height
operator|*
name|src
operator|->
name|bytes
expr_stmt|;
name|memcpy
argument_list|(
name|temp_buf_data
argument_list|(
name|new
argument_list|)
argument_list|,
name|temp_buf_data
argument_list|(
name|src
argument_list|)
argument_list|,
name|length
argument_list|)
expr_stmt|;
return|return
name|new
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|temp_buf_resize (TempBuf * buf,int bytes,int x,int y,int w,int h)
name|temp_buf_resize
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|,
name|int
name|bytes
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|)
block|{
name|int
name|size
decl_stmt|;
comment|/*  calculate the requested size  */
name|size
operator|=
name|w
operator|*
name|h
operator|*
name|bytes
expr_stmt|;
comment|/*  First, configure the canvas buffer  */
if|if
condition|(
operator|!
name|buf
condition|)
name|buf
operator|=
name|temp_buf_new
argument_list|(
name|w
argument_list|,
name|h
argument_list|,
name|bytes
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
block|{
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
comment|/*  Make sure the temp buf is unswapped  */
name|temp_buf_unswap
argument_list|(
name|buf
argument_list|)
expr_stmt|;
comment|/*  Reallocate the data for it  */
name|buf
operator|->
name|data
operator|=
name|g_realloc
argument_list|(
name|buf
operator|->
name|data
argument_list|,
name|size
argument_list|)
expr_stmt|;
block|}
comment|/*  Make sure the temp buf fields are valid  */
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
name|w
expr_stmt|;
name|buf
operator|->
name|height
operator|=
name|h
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
DECL|function|temp_buf_copy_area (TempBuf * src,TempBuf * dest,int x,int y,int w,int h,int border)
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
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|,
name|int
name|border
parameter_list|)
block|{
name|TempBuf
modifier|*
name|new
decl_stmt|;
name|PixelRegion
name|srcR
decl_stmt|,
name|destR
decl_stmt|;
name|unsigned
name|char
name|empty
index|[
name|MAX_CHANNELS
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
if|if
condition|(
operator|!
name|src
condition|)
block|{
name|g_message
argument_list|(
literal|"trying to copy a temp buf which is NULL."
argument_list|)
expr_stmt|;
return|return
name|dest
return|;
block|}
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
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|x
operator|+
name|w
argument_list|,
literal|0
argument_list|,
name|src
operator|->
name|width
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|y
operator|+
name|h
argument_list|,
literal|0
argument_list|,
name|src
operator|->
name|height
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
name|x
operator|=
name|x1
operator|-
name|border
expr_stmt|;
name|y
operator|=
name|y1
operator|-
name|border
expr_stmt|;
name|w
operator|=
operator|(
name|x2
operator|-
name|x1
operator|)
operator|+
name|border
operator|*
literal|2
expr_stmt|;
name|h
operator|=
operator|(
name|y2
operator|-
name|y1
operator|)
operator|+
name|border
operator|*
literal|2
expr_stmt|;
if|if
condition|(
operator|!
name|dest
condition|)
name|new
operator|=
name|temp_buf_new
argument_list|(
name|w
argument_list|,
name|h
argument_list|,
name|src
operator|->
name|bytes
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|empty
argument_list|)
expr_stmt|;
else|else
block|{
name|new
operator|=
name|dest
expr_stmt|;
if|if
condition|(
name|dest
operator|->
name|bytes
operator|!=
name|src
operator|->
name|bytes
condition|)
name|g_message
argument_list|(
literal|"In temp_buf_copy_area, the widths or heights or bytes don't match."
argument_list|)
expr_stmt|;
block|}
comment|/*  Set the offsets for the dest  */
name|new
operator|->
name|x
operator|=
name|src
operator|->
name|x
operator|+
name|x
expr_stmt|;
name|new
operator|->
name|y
operator|=
name|src
operator|->
name|y
operator|+
name|y
expr_stmt|;
comment|/*  Copy the region  */
name|srcR
operator|.
name|bytes
operator|=
name|src
operator|->
name|bytes
expr_stmt|;
name|srcR
operator|.
name|w
operator|=
operator|(
name|x2
operator|-
name|x1
operator|)
expr_stmt|;
name|srcR
operator|.
name|h
operator|=
operator|(
name|y2
operator|-
name|y1
operator|)
expr_stmt|;
name|srcR
operator|.
name|rowstride
operator|=
name|src
operator|->
name|bytes
operator|*
name|src
operator|->
name|width
expr_stmt|;
name|srcR
operator|.
name|data
operator|=
name|temp_buf_data
argument_list|(
name|src
argument_list|)
operator|+
name|y1
operator|*
name|srcR
operator|.
name|rowstride
operator|+
name|x1
operator|*
name|srcR
operator|.
name|bytes
expr_stmt|;
name|destR
operator|.
name|rowstride
operator|=
name|new
operator|->
name|bytes
operator|*
name|new
operator|->
name|width
expr_stmt|;
name|destR
operator|.
name|data
operator|=
name|temp_buf_data
argument_list|(
name|new
argument_list|)
operator|+
operator|(
name|y1
operator|-
name|y
operator|)
operator|*
name|destR
operator|.
name|rowstride
operator|+
operator|(
name|x1
operator|-
name|x
operator|)
operator|*
name|srcR
operator|.
name|bytes
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcR
argument_list|,
operator|&
name|destR
argument_list|)
expr_stmt|;
return|return
name|new
return|;
block|}
end_function

begin_function
name|void
DECL|function|temp_buf_free (TempBuf * temp_buf)
name|temp_buf_free
parameter_list|(
name|TempBuf
modifier|*
name|temp_buf
parameter_list|)
block|{
if|if
condition|(
name|temp_buf
operator|->
name|data
condition|)
name|g_free
argument_list|(
name|temp_buf
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|temp_buf
operator|->
name|swapped
condition|)
name|temp_buf_swap_free
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|unsigned
name|char
modifier|*
DECL|function|temp_buf_data (TempBuf * temp_buf)
name|temp_buf_data
parameter_list|(
name|TempBuf
modifier|*
name|temp_buf
parameter_list|)
block|{
if|if
condition|(
name|temp_buf
operator|->
name|swapped
condition|)
name|temp_buf_unswap
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
return|return
name|temp_buf
operator|->
name|data
return|;
block|}
end_function

begin_comment
comment|/******************************************************************  *  Mask buffer functions                                         *  ******************************************************************/
end_comment

begin_function
name|MaskBuf
modifier|*
DECL|function|mask_buf_new (int width,int height)
name|mask_buf_new
parameter_list|(
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|)
block|{
specifier|static
name|unsigned
name|char
name|empty
init|=
literal|0
decl_stmt|;
return|return
operator|(
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|empty
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|mask_buf_free (MaskBuf * mask)
name|mask_buf_free
parameter_list|(
name|MaskBuf
modifier|*
name|mask
parameter_list|)
block|{
name|temp_buf_free
argument_list|(
operator|(
name|TempBuf
operator|*
operator|)
name|mask
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|unsigned
name|char
modifier|*
DECL|function|mask_buf_data (MaskBuf * mask_buf)
name|mask_buf_data
parameter_list|(
name|MaskBuf
modifier|*
name|mask_buf
parameter_list|)
block|{
if|if
condition|(
name|mask_buf
operator|->
name|swapped
condition|)
name|temp_buf_unswap
argument_list|(
name|mask_buf
argument_list|)
expr_stmt|;
return|return
name|mask_buf
operator|->
name|data
return|;
block|}
end_function

begin_comment
comment|/******************************************************************  *  temp buffer disk caching functions                            *  ******************************************************************/
end_comment

begin_comment
comment|/*  NOTES:  *  Disk caching is setup as follows:  *    On a call to temp_buf_swap, the TempBuf parameter is stored  *    in a temporary variable called cached_in_memory.  *    On the next call to temp_buf_swap, if cached_in_memory is non-null,  *    cached_in_memory is moved to disk, and the latest TempBuf parameter  *    is stored in cached_in_memory.  This method keeps the latest TempBuf  *    structure in memory instead of moving it directly to disk as requested.  *    On a call to temp_buf_unswap, if cached_in_memory is non-null, it is  *    compared against the requested TempBuf.  If they are the same, nothing  *    must be moved in from disk since it still resides in memory.  However,  *    if the two pointers are different, the requested TempBuf is retrieved  *    from disk.  In the former case, cached_in_memory is set to NULL;  *    in the latter case, cached_in_memory is left unchanged.  *    If temp_buf_swap_free is called, cached_in_memory must be checked  *    against the temp buf being freed.  If they are the same, then   *    cached_in_memory must be set to NULL;  *  *  In the case where memory usage is set to "stingy":  *    temp bufs are not cached in memory at all, they go right to disk.  */
end_comment

begin_comment
comment|/*  a static counter for generating unique filenames  */
end_comment

begin_decl_stmt
DECL|variable|swap_index
specifier|static
name|int
name|swap_index
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  a static pointer which keeps track of the last request for a swapped buffer  */
end_comment

begin_decl_stmt
DECL|variable|cached_in_memory
specifier|static
name|TempBuf
modifier|*
name|cached_in_memory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|char
modifier|*
DECL|function|generate_unique_filename (void)
name|generate_unique_filename
parameter_list|(
name|void
parameter_list|)
block|{
name|pid_t
name|pid
decl_stmt|;
name|pid
operator|=
name|getpid
argument_list|()
expr_stmt|;
return|return
name|g_strdup_printf
argument_list|(
literal|"%s"
name|G_DIR_SEPARATOR_S
literal|"gimp%d.%d"
argument_list|,
name|temp_path
argument_list|,
operator|(
name|int
operator|)
name|pid
argument_list|,
name|swap_index
operator|++
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|temp_buf_swap (TempBuf * buf)
name|temp_buf_swap
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|)
block|{
name|TempBuf
modifier|*
name|swap
decl_stmt|;
name|char
modifier|*
name|filename
decl_stmt|;
name|struct
name|stat
name|stat_buf
decl_stmt|;
name|int
name|err
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
if|if
condition|(
operator|!
name|buf
operator|||
name|buf
operator|->
name|swapped
condition|)
return|return;
comment|/*  Set the swapped flag  */
name|buf
operator|->
name|swapped
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|stingy_memory_use
condition|)
name|swap
operator|=
name|buf
expr_stmt|;
else|else
block|{
name|swap
operator|=
name|cached_in_memory
expr_stmt|;
name|cached_in_memory
operator|=
name|buf
expr_stmt|;
block|}
comment|/*  For the case where there is no temp buf ready to be moved to disk, return  */
if|if
condition|(
operator|!
name|swap
condition|)
return|return;
comment|/*  Get a unique filename for caching the data to a UNIX file  */
name|filename
operator|=
name|generate_unique_filename
argument_list|()
expr_stmt|;
comment|/*  Check if generated filename is valid  */
name|err
operator|=
name|stat
argument_list|(
name|filename
argument_list|,
operator|&
name|stat_buf
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|err
condition|)
block|{
if|if
condition|(
name|stat_buf
operator|.
name|st_mode
operator|&
name|S_IFDIR
condition|)
block|{
name|g_message
argument_list|(
literal|"Error in temp buf caching: \"%s\" is a directory (cannot overwrite)"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
comment|/*  Open file for overwrite  */
if|if
condition|(
operator|(
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"wb"
argument_list|)
operator|)
condition|)
block|{
name|size_t
name|blocks_written
decl_stmt|;
name|blocks_written
operator|=
name|fwrite
argument_list|(
name|swap
operator|->
name|data
argument_list|,
name|swap
operator|->
name|width
operator|*
name|swap
operator|->
name|height
operator|*
name|swap
operator|->
name|bytes
argument_list|,
literal|1
argument_list|,
name|fp
argument_list|)
expr_stmt|;
comment|/* Check whether all bytes were written and fclose() was able to flush its buffers */
if|if
condition|(
operator|(
literal|0
operator|!=
name|fclose
argument_list|(
name|fp
argument_list|)
operator|)
operator|||
operator|(
literal|1
operator|!=
name|blocks_written
operator|)
condition|)
block|{
operator|(
name|void
operator|)
name|unlink
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|perror
argument_list|(
literal|"Write error on temp buf"
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
literal|"Cannot write \"%s\""
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
else|else
block|{
operator|(
name|void
operator|)
name|unlink
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|perror
argument_list|(
literal|"Error in temp buf caching"
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
literal|"Cannot write \"%s\""
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  Finally, free the buffer's data  */
name|g_free
argument_list|(
name|swap
operator|->
name|data
argument_list|)
expr_stmt|;
name|swap
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
name|swap
operator|->
name|filename
operator|=
name|filename
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|temp_buf_unswap (TempBuf * buf)
name|temp_buf_unswap
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|)
block|{
name|struct
name|stat
name|stat_buf
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|gboolean
name|succ
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
operator|!
name|buf
operator|||
operator|!
name|buf
operator|->
name|swapped
condition|)
return|return;
comment|/*  Set the swapped flag  */
name|buf
operator|->
name|swapped
operator|=
name|FALSE
expr_stmt|;
comment|/*  If the requested temp buf is still in memory, simply return  */
if|if
condition|(
name|cached_in_memory
operator|==
name|buf
condition|)
block|{
name|cached_in_memory
operator|=
name|NULL
expr_stmt|;
return|return;
block|}
comment|/*  Allocate memory for the buffer's data  */
name|buf
operator|->
name|data
operator|=
name|temp_buf_allocate
argument_list|(
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
argument_list|)
expr_stmt|;
comment|/*  Find out if the filename of the swapped data is an existing file... */
comment|/*  (buf->filname HAS to be != 0 */
if|if
condition|(
operator|!
name|stat
argument_list|(
name|buf
operator|->
name|filename
argument_list|,
operator|&
name|stat_buf
argument_list|)
condition|)
block|{
if|if
condition|(
operator|(
name|fp
operator|=
name|fopen
argument_list|(
name|buf
operator|->
name|filename
argument_list|,
literal|"rb"
argument_list|)
operator|)
condition|)
block|{
name|size_t
name|blocks_read
decl_stmt|;
name|blocks_read
operator|=
name|fread
argument_list|(
name|buf
operator|->
name|data
argument_list|,
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
argument_list|,
literal|1
argument_list|,
name|fp
argument_list|)
expr_stmt|;
operator|(
name|void
operator|)
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
if|if
condition|(
name|blocks_read
operator|!=
literal|1
condition|)
name|perror
argument_list|(
literal|"Read error on temp buf"
argument_list|)
expr_stmt|;
else|else
name|succ
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
name|perror
argument_list|(
literal|"Error in temp buf caching"
argument_list|)
expr_stmt|;
comment|/*  Delete the swap file  */
name|unlink
argument_list|(
name|buf
operator|->
name|filename
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|succ
condition|)
name|g_message
argument_list|(
literal|"Error in temp buf caching: information swapped to disk was lost!"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buf
operator|->
name|filename
argument_list|)
expr_stmt|;
comment|/*  free filename  */
name|buf
operator|->
name|filename
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|temp_buf_swap_free (TempBuf * buf)
name|temp_buf_swap_free
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|)
block|{
name|struct
name|stat
name|stat_buf
decl_stmt|;
if|if
condition|(
operator|!
name|buf
operator|->
name|swapped
condition|)
return|return;
comment|/*  Set the swapped flag  */
name|buf
operator|->
name|swapped
operator|=
name|FALSE
expr_stmt|;
comment|/*  If the requested temp buf is cached in memory...  */
if|if
condition|(
name|cached_in_memory
operator|==
name|buf
condition|)
block|{
name|cached_in_memory
operator|=
name|NULL
expr_stmt|;
return|return;
block|}
comment|/*  Find out if the filename of the swapped data is an existing file... */
if|if
condition|(
operator|!
name|stat
argument_list|(
name|buf
operator|->
name|filename
argument_list|,
operator|&
name|stat_buf
argument_list|)
condition|)
block|{
comment|/*  Delete the swap file  */
name|unlink
argument_list|(
name|buf
operator|->
name|filename
argument_list|)
expr_stmt|;
block|}
else|else
name|g_message
argument_list|(
literal|"Error in temp buf disk swapping: information swapped to disk was lost!"
argument_list|)
expr_stmt|;
if|if
condition|(
name|buf
operator|->
name|filename
condition|)
name|g_free
argument_list|(
name|buf
operator|->
name|filename
argument_list|)
expr_stmt|;
comment|/*  free filename  */
name|buf
operator|->
name|filename
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|swapping_free (void)
name|swapping_free
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|cached_in_memory
condition|)
name|temp_buf_free
argument_list|(
name|cached_in_memory
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

