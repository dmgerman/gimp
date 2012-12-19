begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl-loops.c  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-babl.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-loops.h"
end_include

begin_function
name|void
DECL|function|gimp_gegl_convolve (GeglBuffer * src_buffer,const GeglRectangle * src_rect,GeglBuffer * dest_buffer,const GeglRectangle * dest_rect,const gfloat * kernel,gint kernel_size,gdouble divisor,GimpConvolutionType mode,gboolean alpha_weighting)
name|gimp_gegl_convolve
parameter_list|(
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|src_rect
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|dest_rect
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|kernel
parameter_list|,
name|gint
name|kernel_size
parameter_list|,
name|gdouble
name|divisor
parameter_list|,
name|GimpConvolutionType
name|mode
parameter_list|,
name|gboolean
name|alpha_weighting
parameter_list|)
block|{
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|GeglRectangle
modifier|*
name|src_roi
decl_stmt|;
name|GeglRectangle
modifier|*
name|dest_roi
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|src_format
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|dest_format
decl_stmt|;
name|gint
name|src_components
decl_stmt|;
name|gint
name|dest_components
decl_stmt|;
name|src_format
operator|=
name|gegl_buffer_get_format
argument_list|(
name|src_buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|babl_format_is_palette
argument_list|(
name|src_format
argument_list|)
condition|)
name|src_format
operator|=
name|gimp_babl_format
argument_list|(
name|GIMP_RGB
argument_list|,
name|GIMP_PRECISION_FLOAT
argument_list|,
name|babl_format_has_alpha
argument_list|(
name|src_format
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|src_format
operator|=
name|gimp_babl_format
argument_list|(
name|gimp_babl_format_get_base_type
argument_list|(
name|src_format
argument_list|)
argument_list|,
name|GIMP_PRECISION_FLOAT
argument_list|,
name|babl_format_has_alpha
argument_list|(
name|src_format
argument_list|)
argument_list|)
expr_stmt|;
name|dest_format
operator|=
name|gegl_buffer_get_format
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|babl_format_is_palette
argument_list|(
name|dest_format
argument_list|)
condition|)
name|dest_format
operator|=
name|gimp_babl_format
argument_list|(
name|GIMP_RGB
argument_list|,
name|GIMP_PRECISION_FLOAT
argument_list|,
name|babl_format_has_alpha
argument_list|(
name|dest_format
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|dest_format
operator|=
name|gimp_babl_format
argument_list|(
name|gimp_babl_format_get_base_type
argument_list|(
name|dest_format
argument_list|)
argument_list|,
name|GIMP_PRECISION_FLOAT
argument_list|,
name|babl_format_has_alpha
argument_list|(
name|dest_format
argument_list|)
argument_list|)
expr_stmt|;
name|src_components
operator|=
name|babl_format_get_n_components
argument_list|(
name|src_format
argument_list|)
expr_stmt|;
name|dest_components
operator|=
name|babl_format_get_n_components
argument_list|(
name|dest_format
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|src_buffer
argument_list|,
name|src_rect
argument_list|,
literal|0
argument_list|,
name|src_format
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|src_roi
operator|=
operator|&
name|iter
operator|->
name|roi
index|[
literal|0
index|]
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|dest_buffer
argument_list|,
name|dest_rect
argument_list|,
literal|0
argument_list|,
name|dest_format
argument_list|,
name|GEGL_BUFFER_WRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|dest_roi
operator|=
operator|&
name|iter
operator|->
name|roi
index|[
literal|1
index|]
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
comment|/*  Convolve the src image using the convolution kernel, writing        *  to dest Convolve is not tile-enabled--use accordingly        */
specifier|const
name|gfloat
modifier|*
name|src
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|gfloat
modifier|*
name|dest
init|=
name|iter
operator|->
name|data
index|[
literal|1
index|]
decl_stmt|;
specifier|const
name|gint
name|components
init|=
name|src_components
decl_stmt|;
specifier|const
name|gint
name|a_component
init|=
name|components
operator|-
literal|1
decl_stmt|;
specifier|const
name|gint
name|rowstride
init|=
name|src_components
operator|*
name|src_roi
operator|->
name|width
decl_stmt|;
specifier|const
name|gint
name|margin
init|=
name|kernel_size
operator|/
literal|2
decl_stmt|;
specifier|const
name|gint
name|x1
init|=
name|src_roi
operator|->
name|x
decl_stmt|;
specifier|const
name|gint
name|y1
init|=
name|src_roi
operator|->
name|y
decl_stmt|;
specifier|const
name|gint
name|x2
init|=
name|src_roi
operator|->
name|x
operator|+
name|src_roi
operator|->
name|width
operator|-
literal|1
decl_stmt|;
specifier|const
name|gint
name|y2
init|=
name|src_roi
operator|->
name|y
operator|+
name|src_roi
operator|->
name|height
operator|-
literal|1
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gfloat
name|offset
decl_stmt|;
comment|/*  If the mode is NEGATIVE_CONVOL, the offset should be 128  */
if|if
condition|(
name|mode
operator|==
name|GIMP_NEGATIVE_CONVOL
condition|)
block|{
name|offset
operator|=
literal|0.5
expr_stmt|;
name|mode
operator|=
name|GIMP_NORMAL_CONVOL
expr_stmt|;
block|}
else|else
block|{
name|offset
operator|=
literal|0.0
expr_stmt|;
block|}
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|dest_roi
operator|->
name|height
condition|;
name|y
operator|++
control|)
block|{
name|gfloat
modifier|*
name|d
init|=
name|dest
decl_stmt|;
if|if
condition|(
name|alpha_weighting
condition|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|dest_roi
operator|->
name|width
condition|;
name|x
operator|++
control|)
block|{
specifier|const
name|gfloat
modifier|*
name|m
init|=
name|kernel
decl_stmt|;
name|gdouble
name|total
index|[
literal|4
index|]
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|}
decl_stmt|;
name|gdouble
name|weighted_divisor
init|=
literal|0.0
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|b
decl_stmt|;
for|for
control|(
name|j
operator|=
name|y
operator|-
name|margin
init|;
name|j
operator|<=
name|y
operator|+
name|margin
condition|;
name|j
operator|++
control|)
block|{
for|for
control|(
name|i
operator|=
name|x
operator|-
name|margin
init|;
name|i
operator|<=
name|x
operator|+
name|margin
condition|;
name|i
operator|++
operator|,
name|m
operator|++
control|)
block|{
name|gint
name|xx
init|=
name|CLAMP
argument_list|(
name|i
argument_list|,
name|x1
argument_list|,
name|x2
argument_list|)
decl_stmt|;
name|gint
name|yy
init|=
name|CLAMP
argument_list|(
name|j
argument_list|,
name|y1
argument_list|,
name|y2
argument_list|)
decl_stmt|;
specifier|const
name|gfloat
modifier|*
name|s
init|=
name|src
operator|+
name|yy
operator|*
name|rowstride
operator|+
name|xx
operator|*
name|components
decl_stmt|;
specifier|const
name|gfloat
name|a
init|=
name|s
index|[
name|a_component
index|]
decl_stmt|;
if|if
condition|(
name|a
condition|)
block|{
name|gdouble
name|mult_alpha
init|=
operator|*
name|m
operator|*
name|a
decl_stmt|;
name|weighted_divisor
operator|+=
name|mult_alpha
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|a_component
condition|;
name|b
operator|++
control|)
name|total
index|[
name|b
index|]
operator|+=
name|mult_alpha
operator|*
name|s
index|[
name|b
index|]
expr_stmt|;
name|total
index|[
name|a_component
index|]
operator|+=
name|mult_alpha
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|weighted_divisor
operator|==
literal|0.0
condition|)
name|weighted_divisor
operator|=
name|divisor
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|a_component
condition|;
name|b
operator|++
control|)
name|total
index|[
name|b
index|]
operator|/=
name|weighted_divisor
expr_stmt|;
name|total
index|[
name|a_component
index|]
operator|/=
name|divisor
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|components
condition|;
name|b
operator|++
control|)
block|{
name|total
index|[
name|b
index|]
operator|+=
name|offset
expr_stmt|;
if|if
condition|(
name|mode
operator|!=
name|GIMP_NORMAL_CONVOL
operator|&&
name|total
index|[
name|b
index|]
operator|<
literal|0.0
condition|)
name|total
index|[
name|b
index|]
operator|=
operator|-
name|total
index|[
name|b
index|]
expr_stmt|;
operator|*
name|d
operator|++
operator|=
name|CLAMP
argument_list|(
name|total
index|[
name|b
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|dest_roi
operator|->
name|width
condition|;
name|x
operator|++
control|)
block|{
specifier|const
name|gfloat
modifier|*
name|m
init|=
name|kernel
decl_stmt|;
name|gdouble
name|total
index|[
literal|4
index|]
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|}
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|b
decl_stmt|;
for|for
control|(
name|j
operator|=
name|y
operator|-
name|margin
init|;
name|j
operator|<=
name|y
operator|+
name|margin
condition|;
name|j
operator|++
control|)
block|{
for|for
control|(
name|i
operator|=
name|x
operator|-
name|margin
init|;
name|i
operator|<=
name|x
operator|+
name|margin
condition|;
name|i
operator|++
operator|,
name|m
operator|++
control|)
block|{
name|gint
name|xx
init|=
name|CLAMP
argument_list|(
name|i
argument_list|,
name|x1
argument_list|,
name|x2
argument_list|)
decl_stmt|;
name|gint
name|yy
init|=
name|CLAMP
argument_list|(
name|j
argument_list|,
name|y1
argument_list|,
name|y2
argument_list|)
decl_stmt|;
specifier|const
name|gfloat
modifier|*
name|s
init|=
name|src
operator|+
name|yy
operator|*
name|rowstride
operator|+
name|xx
operator|*
name|components
decl_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|components
condition|;
name|b
operator|++
control|)
name|total
index|[
name|b
index|]
operator|+=
operator|*
name|m
operator|*
name|s
index|[
name|b
index|]
expr_stmt|;
block|}
block|}
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|components
condition|;
name|b
operator|++
control|)
block|{
name|total
index|[
name|b
index|]
operator|=
name|total
index|[
name|b
index|]
operator|/
name|divisor
operator|+
name|offset
expr_stmt|;
if|if
condition|(
name|mode
operator|!=
name|GIMP_NORMAL_CONVOL
operator|&&
name|total
index|[
name|b
index|]
operator|<
literal|0.0
condition|)
name|total
index|[
name|b
index|]
operator|=
operator|-
name|total
index|[
name|b
index|]
expr_stmt|;
name|total
index|[
name|b
index|]
operator|=
name|CLAMP
argument_list|(
name|total
index|[
name|b
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|dest
operator|+=
name|dest_roi
operator|->
name|width
operator|*
name|dest_components
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_gegl_dodgeburn (GeglBuffer * src_buffer,const GeglRectangle * src_rect,GeglBuffer * dest_buffer,const GeglRectangle * dest_rect,gdouble exposure,GimpDodgeBurnType type,GimpTransferMode mode)
name|gimp_gegl_dodgeburn
parameter_list|(
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|src_rect
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|dest_rect
parameter_list|,
name|gdouble
name|exposure
parameter_list|,
name|GimpDodgeBurnType
name|type
parameter_list|,
name|GimpTransferMode
name|mode
parameter_list|)
block|{
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
if|if
condition|(
name|type
operator|==
name|GIMP_BURN
condition|)
name|exposure
operator|=
operator|-
name|exposure
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|src_buffer
argument_list|,
name|src_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|dest_buffer
argument_list|,
name|dest_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_WRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|mode
condition|)
block|{
name|gfloat
name|factor
decl_stmt|;
case|case
name|GIMP_HIGHLIGHTS
case|:
name|factor
operator|=
literal|1.0
operator|+
name|exposure
operator|*
operator|(
literal|0.333333
operator|)
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
name|src
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|gfloat
modifier|*
name|dest
init|=
name|iter
operator|->
name|data
index|[
literal|1
index|]
decl_stmt|;
while|while
condition|(
name|iter
operator|->
name|length
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
operator|*
name|factor
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
operator|*
name|factor
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
operator|*
name|factor
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
block|}
block|}
break|break;
case|case
name|GIMP_MIDTONES
case|:
if|if
condition|(
name|exposure
operator|<
literal|0
condition|)
name|factor
operator|=
literal|1.0
operator|-
name|exposure
operator|*
operator|(
literal|0.333333
operator|)
expr_stmt|;
else|else
name|factor
operator|=
literal|1.0
operator|/
operator|(
literal|1.0
operator|+
name|exposure
operator|)
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
name|src
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|gfloat
modifier|*
name|dest
init|=
name|iter
operator|->
name|data
index|[
literal|1
index|]
decl_stmt|;
while|while
condition|(
name|iter
operator|->
name|length
operator|--
condition|)
block|{
operator|*
name|dest
operator|++
operator|=
name|pow
argument_list|(
operator|*
name|src
operator|++
argument_list|,
name|factor
argument_list|)
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|pow
argument_list|(
operator|*
name|src
operator|++
argument_list|,
name|factor
argument_list|)
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|pow
argument_list|(
operator|*
name|src
operator|++
argument_list|,
name|factor
argument_list|)
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
block|}
block|}
break|break;
case|case
name|GIMP_SHADOWS
case|:
if|if
condition|(
name|exposure
operator|>=
literal|0
condition|)
name|factor
operator|=
literal|0.333333
operator|*
name|exposure
expr_stmt|;
else|else
name|factor
operator|=
operator|-
literal|0.333333
operator|*
name|exposure
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
name|src
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|gfloat
modifier|*
name|dest
init|=
name|iter
operator|->
name|data
index|[
literal|1
index|]
decl_stmt|;
while|while
condition|(
name|iter
operator|->
name|length
operator|--
condition|)
block|{
if|if
condition|(
name|exposure
operator|>=
literal|0
condition|)
block|{
name|gfloat
name|s
decl_stmt|;
name|s
operator|=
operator|*
name|src
operator|++
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|factor
operator|+
name|s
operator|-
name|factor
operator|*
name|s
expr_stmt|;
name|s
operator|=
operator|*
name|src
operator|++
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|factor
operator|+
name|s
operator|-
name|factor
operator|*
name|s
expr_stmt|;
name|s
operator|=
operator|*
name|src
operator|++
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|factor
operator|+
name|s
operator|-
name|factor
operator|*
name|s
expr_stmt|;
block|}
else|else
block|{
name|gfloat
name|s
decl_stmt|;
name|s
operator|=
operator|*
name|src
operator|++
expr_stmt|;
if|if
condition|(
name|s
operator|<
name|factor
condition|)
operator|*
name|dest
operator|++
operator|=
literal|0
expr_stmt|;
else|else
comment|/* factor<= value<=1 */
operator|*
name|dest
operator|++
operator|=
operator|(
name|s
operator|-
name|factor
operator|)
operator|/
operator|(
literal|1.0
operator|-
name|factor
operator|)
expr_stmt|;
name|s
operator|=
operator|*
name|src
operator|++
expr_stmt|;
if|if
condition|(
name|s
operator|<
name|factor
condition|)
operator|*
name|dest
operator|++
operator|=
literal|0
expr_stmt|;
else|else
comment|/* factor<= value<=1 */
operator|*
name|dest
operator|++
operator|=
operator|(
name|s
operator|-
name|factor
operator|)
operator|/
operator|(
literal|1.0
operator|-
name|factor
operator|)
expr_stmt|;
name|s
operator|=
operator|*
name|src
operator|++
expr_stmt|;
if|if
condition|(
name|s
operator|<
name|factor
condition|)
operator|*
name|dest
operator|++
operator|=
literal|0
expr_stmt|;
else|else
comment|/* factor<= value<=1 */
operator|*
name|dest
operator|++
operator|=
operator|(
name|s
operator|-
name|factor
operator|)
operator|/
operator|(
literal|1.0
operator|-
name|factor
operator|)
expr_stmt|;
block|}
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
block|}
block|}
break|break;
block|}
block|}
end_function

begin_comment
comment|/*  * blend_pixels patched 8-24-05 to fix bug #163721.  Note that this change  * causes the function to treat src1 and src2 asymmetrically.  This gives the  * right behavior for the smudge tool, which is the only user of this function  * at the time of patching.  If you want to use the function for something  * else, caveat emptor.  */
end_comment

begin_function
name|void
DECL|function|gimp_gegl_smudge_blend (GeglBuffer * top_buffer,const GeglRectangle * top_rect,GeglBuffer * bottom_buffer,const GeglRectangle * bottom_rect,GeglBuffer * dest_buffer,const GeglRectangle * dest_rect,gdouble blend)
name|gimp_gegl_smudge_blend
parameter_list|(
name|GeglBuffer
modifier|*
name|top_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|top_rect
parameter_list|,
name|GeglBuffer
modifier|*
name|bottom_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|bottom_rect
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|dest_rect
parameter_list|,
name|gdouble
name|blend
parameter_list|)
block|{
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|top_buffer
argument_list|,
name|top_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|bottom_buffer
argument_list|,
name|bottom_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|dest_buffer
argument_list|,
name|dest_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_WRITE
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
specifier|const
name|gfloat
modifier|*
name|top
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
specifier|const
name|gfloat
modifier|*
name|bottom
init|=
name|iter
operator|->
name|data
index|[
literal|1
index|]
decl_stmt|;
name|gfloat
modifier|*
name|dest
init|=
name|iter
operator|->
name|data
index|[
literal|2
index|]
decl_stmt|;
specifier|const
name|gfloat
name|blend1
init|=
literal|1.0
operator|-
name|blend
decl_stmt|;
specifier|const
name|gfloat
name|blend2
init|=
name|blend
decl_stmt|;
while|while
condition|(
name|iter
operator|->
name|length
operator|--
condition|)
block|{
specifier|const
name|gfloat
name|a1
init|=
name|blend1
operator|*
name|bottom
index|[
literal|3
index|]
decl_stmt|;
specifier|const
name|gfloat
name|a2
init|=
name|blend2
operator|*
name|top
index|[
literal|3
index|]
decl_stmt|;
specifier|const
name|gfloat
name|a
init|=
name|a1
operator|+
name|a2
decl_stmt|;
name|gint
name|b
decl_stmt|;
if|if
condition|(
name|a
operator|==
literal|0
condition|)
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
literal|4
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
literal|3
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
name|bottom
index|[
name|b
index|]
operator|+
operator|(
name|bottom
index|[
name|b
index|]
operator|*
name|a1
operator|+
name|top
index|[
name|b
index|]
operator|*
name|a2
operator|-
name|a
operator|*
name|bottom
index|[
name|b
index|]
operator|)
expr_stmt|;
name|dest
index|[
literal|3
index|]
operator|=
name|a
expr_stmt|;
block|}
name|top
operator|+=
literal|4
expr_stmt|;
name|bottom
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

begin_function
name|void
DECL|function|gimp_gegl_apply_mask (GeglBuffer * mask_buffer,const GeglRectangle * mask_rect,GeglBuffer * dest_buffer,const GeglRectangle * dest_rect,gdouble opacity)
name|gimp_gegl_apply_mask
parameter_list|(
name|GeglBuffer
modifier|*
name|mask_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|mask_rect
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|dest_rect
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
block|{
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|mask_buffer
argument_list|,
name|mask_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|dest_buffer
argument_list|,
name|dest_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"RGBA float"
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
specifier|const
name|gfloat
modifier|*
name|mask
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|gfloat
modifier|*
name|dest
init|=
name|iter
operator|->
name|data
index|[
literal|1
index|]
decl_stmt|;
while|while
condition|(
name|iter
operator|->
name|length
operator|--
condition|)
block|{
name|dest
index|[
literal|3
index|]
operator|*=
operator|*
name|mask
operator|*
name|opacity
expr_stmt|;
name|mask
operator|+=
literal|1
expr_stmt|;
name|dest
operator|+=
literal|4
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_gegl_combine_mask (GeglBuffer * mask_buffer,const GeglRectangle * mask_rect,GeglBuffer * dest_buffer,const GeglRectangle * dest_rect,gdouble opacity)
name|gimp_gegl_combine_mask
parameter_list|(
name|GeglBuffer
modifier|*
name|mask_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|mask_rect
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|dest_rect
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
block|{
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|mask_buffer
argument_list|,
name|mask_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|dest_buffer
argument_list|,
name|dest_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
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
specifier|const
name|gfloat
modifier|*
name|mask
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|gfloat
modifier|*
name|dest
init|=
name|iter
operator|->
name|data
index|[
literal|1
index|]
decl_stmt|;
while|while
condition|(
name|iter
operator|->
name|length
operator|--
condition|)
block|{
operator|*
name|dest
operator|*=
operator|*
name|mask
operator|*
name|opacity
expr_stmt|;
name|mask
operator|+=
literal|1
expr_stmt|;
name|dest
operator|+=
literal|1
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_gegl_combine_mask_weird (GeglBuffer * mask_buffer,const GeglRectangle * mask_rect,GeglBuffer * dest_buffer,const GeglRectangle * dest_rect,gdouble opacity,gboolean stipple)
name|gimp_gegl_combine_mask_weird
parameter_list|(
name|GeglBuffer
modifier|*
name|mask_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|mask_rect
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|dest_rect
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gboolean
name|stipple
parameter_list|)
block|{
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|mask_buffer
argument_list|,
name|mask_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|dest_buffer
argument_list|,
name|dest_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
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
specifier|const
name|gfloat
modifier|*
name|mask
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|gfloat
modifier|*
name|dest
init|=
name|iter
operator|->
name|data
index|[
literal|1
index|]
decl_stmt|;
if|if
condition|(
name|stipple
condition|)
block|{
while|while
condition|(
name|iter
operator|->
name|length
operator|--
condition|)
block|{
name|dest
index|[
literal|0
index|]
operator|+=
operator|(
literal|1.0
operator|-
name|dest
index|[
literal|0
index|]
operator|)
operator|*
operator|*
name|mask
operator|*
name|opacity
expr_stmt|;
name|mask
operator|+=
literal|1
expr_stmt|;
name|dest
operator|+=
literal|1
expr_stmt|;
block|}
block|}
else|else
block|{
while|while
condition|(
name|iter
operator|->
name|length
operator|--
condition|)
block|{
if|if
condition|(
name|opacity
operator|>
name|dest
index|[
literal|0
index|]
condition|)
name|dest
index|[
literal|0
index|]
operator|+=
operator|(
name|opacity
operator|-
name|dest
index|[
literal|0
index|]
operator|)
operator|*
operator|*
name|mask
operator|*
name|opacity
expr_stmt|;
name|mask
operator|+=
literal|1
expr_stmt|;
name|dest
operator|+=
literal|1
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_gegl_replace (GeglBuffer * top_buffer,const GeglRectangle * top_rect,GeglBuffer * bottom_buffer,const GeglRectangle * bottom_rect,GeglBuffer * mask_buffer,const GeglRectangle * mask_rect,GeglBuffer * dest_buffer,const GeglRectangle * dest_rect,gdouble opacity,const gboolean * affect)
name|gimp_gegl_replace
parameter_list|(
name|GeglBuffer
modifier|*
name|top_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|top_rect
parameter_list|,
name|GeglBuffer
modifier|*
name|bottom_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|bottom_rect
parameter_list|,
name|GeglBuffer
modifier|*
name|mask_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|mask_rect
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|dest_rect
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
specifier|const
name|gboolean
modifier|*
name|affect
parameter_list|)
block|{
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|top_buffer
argument_list|,
name|top_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|bottom_buffer
argument_list|,
name|bottom_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|mask_buffer
argument_list|,
name|mask_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|dest_buffer
argument_list|,
name|dest_rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
argument_list|,
name|GEGL_BUFFER_WRITE
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
specifier|const
name|gfloat
modifier|*
name|top
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
specifier|const
name|gfloat
modifier|*
name|bottom
init|=
name|iter
operator|->
name|data
index|[
literal|1
index|]
decl_stmt|;
specifier|const
name|gfloat
modifier|*
name|mask
init|=
name|iter
operator|->
name|data
index|[
literal|2
index|]
decl_stmt|;
name|gfloat
modifier|*
name|dest
init|=
name|iter
operator|->
name|data
index|[
literal|3
index|]
decl_stmt|;
while|while
condition|(
name|iter
operator|->
name|length
operator|--
condition|)
block|{
name|gint
name|b
decl_stmt|;
name|gdouble
name|mask_val
init|=
operator|*
name|mask
operator|*
name|opacity
decl_stmt|;
comment|/* calculate new alpha first. */
name|gfloat
name|s1_a
init|=
name|bottom
index|[
literal|3
index|]
decl_stmt|;
name|gfloat
name|s2_a
init|=
name|top
index|[
literal|3
index|]
decl_stmt|;
name|gdouble
name|a_val
init|=
name|s1_a
operator|+
name|mask_val
operator|*
operator|(
name|s2_a
operator|-
name|s1_a
operator|)
decl_stmt|;
if|if
condition|(
name|a_val
operator|==
literal|0.0
condition|)
block|{
comment|/* In any case, write out versions of the blending                * function that result when combinations of s1_a, s2_a,                * and mask_val --> 0 (or mask_val -->1)                */
comment|/* 1: s1_a, s2_a, AND mask_val all approach 0+: */
comment|/* 2: s1_a AND s2_a both approach 0+, regardless of mask_val: */
if|if
condition|(
name|s1_a
operator|+
name|s2_a
operator|==
literal|0.0
condition|)
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
literal|3
condition|;
name|b
operator|++
control|)
block|{
name|gfloat
name|new_val
decl_stmt|;
name|new_val
operator|=
name|bottom
index|[
name|b
index|]
operator|+
name|mask_val
operator|*
operator|(
name|top
index|[
name|b
index|]
operator|-
name|bottom
index|[
name|b
index|]
operator|)
expr_stmt|;
name|dest
index|[
name|b
index|]
operator|=
name|affect
index|[
name|b
index|]
condition|?
name|MIN
argument_list|(
name|new_val
argument_list|,
literal|1.0
argument_list|)
else|:
name|bottom
index|[
name|b
index|]
expr_stmt|;
block|}
block|}
comment|/* 3: mask_val AND s1_a both approach 0+, regardless of s2_a  */
elseif|else
if|if
condition|(
name|s1_a
operator|+
name|mask_val
operator|==
literal|0.0
condition|)
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
literal|3
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
name|bottom
index|[
name|b
index|]
expr_stmt|;
block|}
comment|/* 4: mask_val -->1 AND s2_a -->0, regardless of s1_a */
elseif|else
if|if
condition|(
literal|1.0
operator|-
name|mask_val
operator|+
name|s2_a
operator|==
literal|0.0
condition|)
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
literal|3
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
name|affect
index|[
name|b
index|]
condition|?
name|top
index|[
name|b
index|]
else|:
name|bottom
index|[
name|b
index|]
expr_stmt|;
block|}
block|}
else|else
block|{
name|gdouble
name|a_recip
init|=
literal|1.0
operator|/
name|a_val
decl_stmt|;
comment|/* possible optimization: fold a_recip into s1_a and s2_a */
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
literal|3
condition|;
name|b
operator|++
control|)
block|{
name|gfloat
name|new_val
init|=
name|a_recip
operator|*
operator|(
name|bottom
index|[
name|b
index|]
operator|*
name|s1_a
operator|+
name|mask_val
operator|*
operator|(
name|top
index|[
name|b
index|]
operator|*
name|s2_a
operator|-
name|bottom
index|[
name|b
index|]
operator|*
name|s1_a
operator|)
operator|)
decl_stmt|;
name|dest
index|[
name|b
index|]
operator|=
name|affect
index|[
name|b
index|]
condition|?
name|MIN
argument_list|(
name|new_val
argument_list|,
literal|1.0
argument_list|)
else|:
name|bottom
index|[
name|b
index|]
expr_stmt|;
block|}
block|}
name|dest
index|[
literal|3
index|]
operator|=
name|affect
index|[
literal|3
index|]
condition|?
name|a_val
else|:
name|s1_a
expr_stmt|;
name|top
operator|+=
literal|4
expr_stmt|;
name|bottom
operator|+=
literal|4
expr_stmt|;
name|mask
operator|+=
literal|1
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

