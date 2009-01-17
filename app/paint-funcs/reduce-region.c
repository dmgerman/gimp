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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"reduce-region.h"
end_include

begin_function_decl
specifier|static
name|void
name|reduce_pixel_region
parameter_list|(
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|guchar
modifier|*
name|dst
parameter_list|,
name|gint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|reduce_buffer
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dst
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|reduce_row
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dst
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gint
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|reduce_bilinear_pr
parameter_list|(
name|PixelRegion
modifier|*
name|dstPR
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|reduce_bilinear
parameter_list|(
name|PixelRegion
modifier|*
name|dstPR
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|gint
name|source_w
parameter_list|,
name|gint
name|source_h
parameter_list|,
name|gint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|reduce_region (PixelRegion * srcPR,PixelRegion * dstPR,GimpProgressFunc progress_callback,gpointer progress_data)
name|reduce_region
parameter_list|(
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|dstPR
parameter_list|,
name|GimpProgressFunc
name|progress_callback
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
block|{
specifier|const
name|gint
name|bytes
init|=
name|dstPR
operator|->
name|bytes
decl_stmt|;
name|gint
name|alpha
init|=
literal|0
decl_stmt|;
name|gint
name|level
init|=
literal|0
decl_stmt|;
name|gdouble
name|scale
init|=
operator|(
name|gdouble
operator|)
name|dstPR
operator|->
name|h
operator|/
operator|(
name|gdouble
operator|)
name|srcPR
operator|->
name|h
decl_stmt|;
if|if
condition|(
name|pixel_region_has_alpha
argument_list|(
name|srcPR
argument_list|)
condition|)
name|alpha
operator|=
name|bytes
operator|-
literal|1
expr_stmt|;
while|while
condition|(
name|scale
operator|<=
literal|0.5
condition|)
block|{
name|scale
operator|*=
literal|2
expr_stmt|;
name|level
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|level
operator|>
literal|0
condition|)
block|{
name|gint
name|width
init|=
name|srcPR
operator|->
name|w
operator|/
literal|2
decl_stmt|;
name|gint
name|height
init|=
name|srcPR
operator|->
name|h
operator|/
literal|2
decl_stmt|;
name|guchar
modifier|*
name|dst
init|=
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
decl_stmt|;
name|reduce_pixel_region
argument_list|(
name|srcPR
argument_list|,
name|dst
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
name|level
operator|--
expr_stmt|;
if|if
condition|(
name|level
operator|>
literal|0
condition|)
block|{
while|while
condition|(
name|level
condition|)
block|{
name|guchar
modifier|*
name|src
init|=
name|dst
decl_stmt|;
name|width
operator|=
name|width
operator|/
literal|2
expr_stmt|;
name|height
operator|=
name|height
operator|/
literal|2
expr_stmt|;
name|dst
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
name|reduce_buffer
argument_list|(
name|src
argument_list|,
name|dst
argument_list|,
name|bytes
argument_list|,
name|width
operator|*
literal|2
argument_list|,
name|height
operator|*
literal|2
argument_list|,
name|alpha
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
name|level
operator|--
expr_stmt|;
block|}
block|}
name|reduce_bilinear
argument_list|(
name|dstPR
argument_list|,
name|dst
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dst
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|reduce_bilinear_pr
argument_list|(
name|dstPR
argument_list|,
name|srcPR
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|reduce_pixel_region (PixelRegion * srcPR,guchar * dst,gint bytes)
name|reduce_pixel_region
parameter_list|(
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|guchar
modifier|*
name|dst
parameter_list|,
name|gint
name|bytes
parameter_list|)
block|{
name|guchar
modifier|*
name|src_buf
decl_stmt|,
modifier|*
name|row0
decl_stmt|,
modifier|*
name|row1
decl_stmt|,
modifier|*
name|row2
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|gint
name|src_width
init|=
name|srcPR
operator|->
name|w
decl_stmt|;
name|gint
name|dst_width
init|=
name|srcPR
operator|->
name|w
operator|/
literal|2
decl_stmt|;
name|guchar
modifier|*
name|dst_ptr
decl_stmt|;
name|gint
name|alpha
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|pixel_region_has_alpha
argument_list|(
name|srcPR
argument_list|)
condition|)
name|alpha
operator|=
name|bytes
operator|-
literal|1
expr_stmt|;
name|src_buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|src_width
operator|*
name|bytes
operator|*
literal|3
argument_list|)
expr_stmt|;
name|row0
operator|=
name|src_buf
expr_stmt|;
name|row1
operator|=
name|row0
operator|+
name|src_width
operator|*
name|bytes
expr_stmt|;
name|row2
operator|=
name|row1
operator|+
name|src_width
operator|*
name|bytes
expr_stmt|;
name|dst_ptr
operator|=
name|dst
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|srcPR
operator|->
name|h
condition|;
name|y
operator|+=
literal|2
control|)
block|{
name|pixel_region_get_row
argument_list|(
name|srcPR
argument_list|,
literal|0
argument_list|,
name|ABS
argument_list|(
name|y
operator|-
literal|1
argument_list|)
argument_list|,
name|src_width
argument_list|,
name|row0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pixel_region_get_row
argument_list|(
name|srcPR
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|src_width
argument_list|,
name|row1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pixel_region_get_row
argument_list|(
name|srcPR
argument_list|,
literal|0
argument_list|,
name|y
operator|+
literal|1
argument_list|,
name|src_width
argument_list|,
name|row2
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|reduce_row
argument_list|(
name|src_buf
argument_list|,
name|dst_ptr
argument_list|,
name|src_width
argument_list|,
name|bytes
argument_list|,
name|alpha
argument_list|)
expr_stmt|;
name|dst_ptr
operator|+=
name|dst_width
operator|*
name|bytes
expr_stmt|;
block|}
name|g_free
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|reduce_buffer (const guchar * src,guchar * dst,gint bytes,gint width,gint height,gint alpha)
name|reduce_buffer
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dst
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|alpha
parameter_list|)
block|{
name|guchar
modifier|*
name|src_buf
decl_stmt|;
name|guchar
modifier|*
name|row0
decl_stmt|,
modifier|*
name|row1
decl_stmt|,
modifier|*
name|row2
decl_stmt|;
name|gint
name|y
decl_stmt|,
name|pos
decl_stmt|;
name|gint
name|dst_width
init|=
name|width
operator|/
literal|2
decl_stmt|;
name|guchar
modifier|*
name|dstptr
decl_stmt|;
name|gint
name|rowstride
init|=
name|width
operator|*
name|bytes
decl_stmt|;
name|src_buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|rowstride
operator|*
literal|3
argument_list|)
expr_stmt|;
name|row0
operator|=
name|src_buf
expr_stmt|;
name|row1
operator|=
name|row0
operator|+
name|rowstride
expr_stmt|;
name|row2
operator|=
name|row1
operator|+
name|rowstride
expr_stmt|;
name|dstptr
operator|=
name|dst
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|+=
literal|2
control|)
block|{
name|pos
operator|=
name|ABS
argument_list|(
name|y
operator|-
literal|1
argument_list|)
operator|*
name|rowstride
expr_stmt|;
name|memcpy
argument_list|(
name|row0
argument_list|,
name|src
operator|+
name|pos
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
name|pos
operator|=
name|y
operator|*
name|rowstride
expr_stmt|;
name|memcpy
argument_list|(
name|row1
argument_list|,
name|src
operator|+
name|pos
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
name|pos
operator|=
operator|(
name|y
operator|+
literal|1
operator|)
operator|*
name|rowstride
expr_stmt|;
name|memcpy
argument_list|(
name|row2
argument_list|,
name|src
operator|+
name|pos
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
name|reduce_row
argument_list|(
name|src_buf
argument_list|,
name|dstptr
argument_list|,
name|width
argument_list|,
name|bytes
argument_list|,
name|alpha
argument_list|)
expr_stmt|;
name|dstptr
operator|+=
name|dst_width
operator|*
name|bytes
expr_stmt|;
block|}
name|g_free
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|reduce_row (const guchar * src,guchar * dst,gint width,gint bytes,gint alpha)
name|reduce_row
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dst
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gint
name|alpha
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|b
decl_stmt|,
name|start
decl_stmt|;
name|gdouble
name|alpha_sum
decl_stmt|;
name|gdouble
name|sum
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src0
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src1
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src2
decl_stmt|;
name|guchar
modifier|*
name|dstptr
decl_stmt|;
comment|/*  Pre calculated gausian matrix */
comment|/*  Standard deviation = 0.71        12 32 12       32 86 32       12 32 12        Matrix sum is = 262       Normalize by dividing with 273    */
name|dstptr
operator|=
name|dst
expr_stmt|;
name|src0
operator|=
name|src
expr_stmt|;
name|src1
operator|=
name|src
operator|+
name|width
operator|*
name|bytes
expr_stmt|;
name|src2
operator|=
name|src1
operator|+
name|width
operator|*
name|bytes
expr_stmt|;
name|start
operator|=
name|bytes
operator|-
literal|1
expr_stmt|;
name|sum
operator|=
literal|0.0
expr_stmt|;
name|alpha_sum
operator|=
literal|0.0
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|+=
literal|2
control|)
block|{
for|for
control|(
name|b
operator|=
name|start
init|;
name|b
operator|>=
literal|0
condition|;
name|b
operator|--
control|)
block|{
name|sum
operator|+=
name|src0
index|[
name|ABS
argument_list|(
name|x
operator|-
literal|1
argument_list|)
operator|*
name|bytes
operator|+
name|b
index|]
operator|*
literal|12
expr_stmt|;
name|sum
operator|+=
name|src0
index|[
name|ABS
argument_list|(
name|x
argument_list|)
operator|*
name|bytes
operator|+
name|b
index|]
operator|*
literal|32
expr_stmt|;
name|sum
operator|+=
name|src0
index|[
name|ABS
argument_list|(
name|x
operator|+
literal|1
argument_list|)
operator|*
name|bytes
operator|+
name|b
index|]
operator|*
literal|12
expr_stmt|;
name|sum
operator|+=
name|src1
index|[
name|ABS
argument_list|(
name|x
operator|-
literal|1
argument_list|)
operator|*
name|bytes
operator|+
name|b
index|]
operator|*
literal|32
expr_stmt|;
name|sum
operator|+=
name|src1
index|[
name|ABS
argument_list|(
name|x
argument_list|)
operator|*
name|bytes
operator|+
name|b
index|]
operator|*
literal|86
expr_stmt|;
name|sum
operator|+=
name|src1
index|[
name|ABS
argument_list|(
name|x
operator|+
literal|1
argument_list|)
operator|*
name|bytes
operator|+
name|b
index|]
operator|*
literal|32
expr_stmt|;
name|sum
operator|+=
name|src2
index|[
name|ABS
argument_list|(
name|x
operator|-
literal|1
argument_list|)
operator|*
name|bytes
operator|+
name|b
index|]
operator|*
literal|12
expr_stmt|;
name|sum
operator|+=
name|src2
index|[
name|ABS
argument_list|(
name|x
argument_list|)
operator|*
name|bytes
operator|+
name|b
index|]
operator|*
literal|32
expr_stmt|;
name|sum
operator|+=
name|src2
index|[
name|ABS
argument_list|(
name|x
operator|+
literal|1
argument_list|)
operator|*
name|bytes
operator|+
name|b
index|]
operator|*
literal|12
expr_stmt|;
name|sum
operator|/=
literal|273.0
expr_stmt|;
if|if
condition|(
name|alpha
operator|&&
operator|(
name|b
operator|==
name|alpha
operator|)
condition|)
block|{
name|alpha_sum
operator|=
name|sum
expr_stmt|;
name|dstptr
index|[
name|b
index|]
operator|=
operator|(
name|guchar
operator|)
name|alpha_sum
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|alpha
condition|)
block|{
if|if
condition|(
name|alpha_sum
operator|!=
literal|0.0
condition|)
name|sum
operator|=
name|sum
operator|*
operator|(
literal|262.0
operator|/
name|alpha_sum
operator|)
expr_stmt|;
else|else
name|sum
operator|=
literal|0.0
expr_stmt|;
block|}
name|dstptr
index|[
name|b
index|]
operator|=
operator|(
name|guchar
operator|)
name|sum
expr_stmt|;
block|}
block|}
name|dstptr
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|reduce_bilinear (PixelRegion * dstPR,const guchar * src,gint source_w,gint source_h,gint bytes)
name|reduce_bilinear
parameter_list|(
name|PixelRegion
modifier|*
name|dstPR
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|gint
name|source_w
parameter_list|,
name|gint
name|source_h
parameter_list|,
name|gint
name|bytes
parameter_list|)
block|{
specifier|const
name|gdouble
name|scale
init|=
operator|(
name|gdouble
operator|)
name|dstPR
operator|->
name|h
operator|/
operator|(
name|gdouble
operator|)
name|source_h
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|x0
decl_stmt|,
name|x1
decl_stmt|,
name|y0
decl_stmt|,
name|y1
decl_stmt|;
name|gdouble
name|xfrac
decl_stmt|,
name|yfrac
decl_stmt|;
name|gdouble
name|s00
decl_stmt|,
name|s01
decl_stmt|,
name|s10
decl_stmt|,
name|s11
decl_stmt|;
name|guchar
name|value
decl_stmt|;
name|guchar
modifier|*
name|dst
decl_stmt|;
name|dst
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|dstPR
operator|->
name|w
operator|*
name|dstPR
operator|->
name|h
operator|*
name|bytes
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
name|dstPR
operator|->
name|h
condition|;
name|y
operator|++
control|)
block|{
name|yfrac
operator|=
operator|(
name|y
operator|/
name|scale
operator|)
expr_stmt|;
name|y0
operator|=
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|yfrac
argument_list|)
expr_stmt|;
name|y1
operator|=
operator|(
name|gint
operator|)
name|ceil
argument_list|(
name|yfrac
argument_list|)
expr_stmt|;
name|yfrac
operator|=
name|yfrac
operator|-
name|y0
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|dstPR
operator|->
name|w
condition|;
name|x
operator|++
control|)
block|{
name|xfrac
operator|=
operator|(
name|x
operator|/
name|scale
operator|)
expr_stmt|;
name|x0
operator|=
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|xfrac
argument_list|)
expr_stmt|;
name|x1
operator|=
operator|(
name|gint
operator|)
name|ceil
argument_list|(
name|xfrac
argument_list|)
expr_stmt|;
name|xfrac
operator|=
name|xfrac
operator|-
name|x0
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bytes
condition|;
name|b
operator|++
control|)
block|{
name|s00
operator|=
name|src
index|[
operator|(
name|x0
operator|+
name|y0
operator|*
name|source_w
operator|)
operator|*
name|bytes
operator|+
name|b
index|]
expr_stmt|;
name|s10
operator|=
name|src
index|[
operator|(
name|x1
operator|+
name|y0
operator|*
name|source_w
operator|)
operator|*
name|bytes
operator|+
name|b
index|]
expr_stmt|;
name|s01
operator|=
name|src
index|[
operator|(
name|x0
operator|+
name|y1
operator|*
name|source_w
operator|)
operator|*
name|bytes
operator|+
name|b
index|]
expr_stmt|;
name|s11
operator|=
name|src
index|[
operator|(
name|x1
operator|+
name|y1
operator|*
name|source_w
operator|)
operator|*
name|bytes
operator|+
name|b
index|]
expr_stmt|;
name|value
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
literal|1
operator|-
name|yfrac
operator|)
operator|*
operator|(
operator|(
literal|1
operator|-
name|xfrac
operator|)
operator|*
name|s00
operator|+
name|xfrac
operator|*
name|s01
operator|)
operator|+
name|yfrac
operator|*
operator|(
operator|(
literal|1
operator|-
name|xfrac
operator|)
operator|*
name|s10
operator|+
name|xfrac
operator|*
name|s11
operator|)
argument_list|)
expr_stmt|;
name|dst
index|[
name|x
operator|*
name|bytes
operator|+
name|b
index|]
operator|=
name|value
expr_stmt|;
block|}
block|}
name|pixel_region_set_row
argument_list|(
name|dstPR
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|dstPR
operator|->
name|w
argument_list|,
name|dst
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|reduce_bilinear_pr (PixelRegion * dstPR,PixelRegion * srcPR)
name|reduce_bilinear_pr
parameter_list|(
name|PixelRegion
modifier|*
name|dstPR
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|)
block|{
specifier|const
name|gint
name|bytes
init|=
name|dstPR
operator|->
name|bytes
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|x0
decl_stmt|,
name|x1
decl_stmt|,
name|y0
decl_stmt|,
name|y1
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
name|gdouble
name|xfrac
decl_stmt|,
name|yfrac
decl_stmt|;
name|gdouble
name|s00
decl_stmt|,
name|s01
decl_stmt|,
name|s10
decl_stmt|,
name|s11
decl_stmt|;
name|guchar
name|value
decl_stmt|;
name|guchar
modifier|*
name|dst
decl_stmt|;
name|guchar
modifier|*
name|src0
decl_stmt|;
name|guchar
modifier|*
name|src1
decl_stmt|;
comment|/* Copy and return if scale = 1.0 */
if|if
condition|(
name|srcPR
operator|->
name|h
operator|==
name|dstPR
operator|->
name|h
condition|)
block|{
name|copy_region
argument_list|(
name|srcPR
argument_list|,
name|dstPR
argument_list|)
expr_stmt|;
return|return;
block|}
name|scale
operator|=
operator|(
name|gdouble
operator|)
name|dstPR
operator|->
name|h
operator|/
operator|(
name|gdouble
operator|)
name|srcPR
operator|->
name|h
expr_stmt|;
comment|/* Interpolate */
name|src0
operator|=
name|g_new0
argument_list|(
name|guchar
argument_list|,
name|srcPR
operator|->
name|w
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|src1
operator|=
name|g_new0
argument_list|(
name|guchar
argument_list|,
name|srcPR
operator|->
name|w
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|dst
operator|=
name|g_new0
argument_list|(
name|guchar
argument_list|,
name|dstPR
operator|->
name|w
operator|*
name|bytes
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
name|dstPR
operator|->
name|h
condition|;
name|y
operator|++
control|)
block|{
name|yfrac
operator|=
name|y
operator|/
name|scale
expr_stmt|;
name|y0
operator|=
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|yfrac
argument_list|)
expr_stmt|;
name|y1
operator|=
operator|(
name|gint
operator|)
name|ceil
argument_list|(
name|yfrac
argument_list|)
expr_stmt|;
name|yfrac
operator|=
name|yfrac
operator|-
name|y0
expr_stmt|;
name|pixel_region_get_row
argument_list|(
name|srcPR
argument_list|,
literal|0
argument_list|,
name|y0
argument_list|,
name|srcPR
operator|->
name|w
argument_list|,
name|src0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pixel_region_get_row
argument_list|(
name|srcPR
argument_list|,
literal|0
argument_list|,
name|y1
argument_list|,
name|srcPR
operator|->
name|w
argument_list|,
name|src1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|dstPR
operator|->
name|w
condition|;
name|x
operator|++
control|)
block|{
name|xfrac
operator|=
operator|(
name|x
operator|/
name|scale
operator|)
expr_stmt|;
name|x0
operator|=
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|xfrac
argument_list|)
expr_stmt|;
name|x1
operator|=
operator|(
name|gint
operator|)
name|ceil
argument_list|(
name|xfrac
argument_list|)
expr_stmt|;
name|xfrac
operator|=
name|xfrac
operator|-
name|x0
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bytes
condition|;
name|b
operator|++
control|)
block|{
name|s00
operator|=
name|src0
index|[
name|x0
operator|*
name|bytes
operator|+
name|b
index|]
expr_stmt|;
name|s01
operator|=
name|src0
index|[
name|x1
operator|*
name|bytes
operator|+
name|b
index|]
expr_stmt|;
name|s10
operator|=
name|src1
index|[
name|x0
operator|*
name|bytes
operator|+
name|b
index|]
expr_stmt|;
name|s11
operator|=
name|src1
index|[
name|x1
operator|*
name|bytes
operator|+
name|b
index|]
expr_stmt|;
name|value
operator|=
operator|(
literal|1
operator|-
name|yfrac
operator|)
operator|*
operator|(
operator|(
literal|1
operator|-
name|xfrac
operator|)
operator|*
name|s00
operator|+
name|xfrac
operator|*
name|s01
operator|)
operator|+
name|yfrac
operator|*
operator|(
operator|(
literal|1
operator|-
name|xfrac
operator|)
operator|*
name|s10
operator|+
name|xfrac
operator|*
name|s11
operator|)
expr_stmt|;
name|dst
index|[
name|x
operator|*
name|bytes
operator|+
name|b
index|]
operator|=
operator|(
name|guchar
operator|)
name|value
expr_stmt|;
block|}
block|}
name|pixel_region_set_row
argument_list|(
name|dstPR
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|dstPR
operator|->
name|w
argument_list|,
name|dst
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|src0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dst
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

