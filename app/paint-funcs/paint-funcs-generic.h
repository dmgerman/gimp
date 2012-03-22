begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*  * This file is supposed to contain the generic (read: C) implementation  * of the pixel fiddling paint-functions.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PAINT_FUNCS_GENERIC_H__
end_ifndef

begin_define
DECL|macro|__PAINT_FUNCS_GENERIC_H__
define|#
directive|define
name|__PAINT_FUNCS_GENERIC_H__
end_define

begin_function
name|void
DECL|function|color_pixels (guchar * dest,const guchar * color,guint w,guint bytes)
name|color_pixels
parameter_list|(
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|color
parameter_list|,
name|guint
name|w
parameter_list|,
name|guint
name|bytes
parameter_list|)
block|{
switch|switch
condition|(
name|bytes
condition|)
block|{
case|case
literal|1
case|:
name|memset
argument_list|(
name|dest
argument_list|,
operator|*
name|color
argument_list|,
name|w
argument_list|)
expr_stmt|;
break|break;
case|case
literal|2
case|:
if|#
directive|if
name|defined
argument_list|(
name|sparc
argument_list|)
operator|||
name|defined
argument_list|(
name|__sparc__
argument_list|)
block|{
specifier|const
name|guchar
name|c0
init|=
name|color
index|[
literal|0
index|]
decl_stmt|;
specifier|const
name|guchar
name|c1
init|=
name|color
index|[
literal|1
index|]
decl_stmt|;
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|c0
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|c1
expr_stmt|;
name|dest
operator|+=
literal|2
expr_stmt|;
block|}
block|}
else|#
directive|else
block|{
specifier|const
name|guint16
name|shortc
init|=
operator|(
operator|(
specifier|const
name|guint16
operator|*
operator|)
name|color
operator|)
index|[
literal|0
index|]
decl_stmt|;
name|guint16
modifier|*
name|shortd
init|=
operator|(
name|guint16
operator|*
operator|)
name|dest
decl_stmt|;
while|while
condition|(
name|w
operator|--
condition|)
block|{
operator|*
name|shortd
operator|=
name|shortc
expr_stmt|;
name|shortd
operator|++
expr_stmt|;
block|}
block|}
endif|#
directive|endif
comment|/* sparc || __sparc__ */
break|break;
case|case
literal|3
case|:
block|{
specifier|const
name|guchar
name|c0
init|=
name|color
index|[
literal|0
index|]
decl_stmt|;
specifier|const
name|guchar
name|c1
init|=
name|color
index|[
literal|1
index|]
decl_stmt|;
specifier|const
name|guchar
name|c2
init|=
name|color
index|[
literal|2
index|]
decl_stmt|;
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|c0
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|c1
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|c2
expr_stmt|;
name|dest
operator|+=
literal|3
expr_stmt|;
block|}
block|}
break|break;
case|case
literal|4
case|:
if|#
directive|if
name|defined
argument_list|(
name|sparc
argument_list|)
operator|||
name|defined
argument_list|(
name|__sparc__
argument_list|)
block|{
specifier|const
name|guchar
name|c0
init|=
name|color
index|[
literal|0
index|]
decl_stmt|;
specifier|const
name|guchar
name|c1
init|=
name|color
index|[
literal|1
index|]
decl_stmt|;
specifier|const
name|guchar
name|c2
init|=
name|color
index|[
literal|2
index|]
decl_stmt|;
specifier|const
name|guchar
name|c3
init|=
name|color
index|[
literal|3
index|]
decl_stmt|;
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|c0
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|c1
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|c2
expr_stmt|;
name|dest
index|[
literal|3
index|]
operator|=
name|c3
expr_stmt|;
name|dest
operator|+=
literal|4
expr_stmt|;
block|}
block|}
else|#
directive|else
block|{
specifier|const
name|guint32
name|longc
init|=
operator|(
operator|(
specifier|const
name|guint32
operator|*
operator|)
name|color
operator|)
index|[
literal|0
index|]
decl_stmt|;
name|guint32
modifier|*
name|longd
init|=
operator|(
name|guint32
operator|*
operator|)
name|dest
decl_stmt|;
while|while
condition|(
name|w
operator|--
condition|)
block|{
operator|*
name|longd
operator|=
name|longc
expr_stmt|;
name|longd
operator|++
expr_stmt|;
block|}
block|}
endif|#
directive|endif
comment|/* sparc || __sparc__ */
break|break;
default|default:
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|memcpy
argument_list|(
name|dest
argument_list|,
name|color
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
name|dest
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  * blend_pixels patched 8-24-05 to fix bug #163721.  Note that this change  * causes the function to treat src1 and src2 asymmetrically.  This gives the  * right behavior for the smudge tool, which is the only user of this function  * at the time of patching.  If you want to use the function for something  * else, caveat emptor.  */
end_comment

begin_function
specifier|inline
name|void
DECL|function|blend_pixels (const guchar * src1,const guchar * src2,guchar * dest,guchar blend,guint w,guint bytes)
name|blend_pixels
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|guchar
name|blend
parameter_list|,
name|guint
name|w
parameter_list|,
name|guint
name|bytes
parameter_list|)
block|{
if|if
condition|(
name|HAS_ALPHA
argument_list|(
name|bytes
argument_list|)
condition|)
block|{
specifier|const
name|guint
name|blend1
init|=
literal|255
operator|-
name|blend
decl_stmt|;
specifier|const
name|guint
name|blend2
init|=
name|blend
operator|+
literal|1
decl_stmt|;
specifier|const
name|guint
name|c
init|=
name|bytes
operator|-
literal|1
decl_stmt|;
while|while
condition|(
name|w
operator|--
condition|)
block|{
specifier|const
name|gint
name|a1
init|=
name|blend1
operator|*
name|src1
index|[
name|c
index|]
decl_stmt|;
specifier|const
name|gint
name|a2
init|=
name|blend2
operator|*
name|src2
index|[
name|c
index|]
decl_stmt|;
specifier|const
name|gint
name|a
init|=
name|a1
operator|+
name|a2
decl_stmt|;
name|guint
name|b
decl_stmt|;
if|if
condition|(
operator|!
name|a
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
name|bytes
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
name|c
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
name|src1
index|[
name|b
index|]
operator|+
operator|(
name|src1
index|[
name|b
index|]
operator|*
name|a1
operator|+
name|src2
index|[
name|b
index|]
operator|*
name|a2
operator|-
name|a
operator|*
name|src1
index|[
name|b
index|]
operator|)
operator|/
name|a
expr_stmt|;
name|dest
index|[
name|c
index|]
operator|=
name|a
operator|>>
literal|8
expr_stmt|;
block|}
name|src1
operator|+=
name|bytes
expr_stmt|;
name|src2
operator|+=
name|bytes
expr_stmt|;
name|dest
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
else|else
block|{
specifier|const
name|guchar
name|blend1
init|=
literal|255
operator|-
name|blend
decl_stmt|;
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|guint
name|b
decl_stmt|;
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
name|dest
index|[
name|b
index|]
operator|=
name|src1
index|[
name|b
index|]
operator|+
operator|(
name|src1
index|[
name|b
index|]
operator|*
name|blend1
operator|+
name|src2
index|[
name|b
index|]
operator|*
name|blend
operator|-
name|src1
index|[
name|b
index|]
operator|*
literal|255
operator|)
operator|/
literal|255
expr_stmt|;
name|src1
operator|+=
name|bytes
expr_stmt|;
name|src2
operator|+=
name|bytes
expr_stmt|;
name|dest
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|replace_pixels (const guchar * src1,const guchar * src2,guchar * dest,const guchar * mask,gint length,gint opacity,const gboolean * affect,gint bytes1,gint bytes2)
name|replace_pixels
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
name|gint
name|length
parameter_list|,
name|gint
name|opacity
parameter_list|,
specifier|const
name|gboolean
modifier|*
name|affect
parameter_list|,
name|gint
name|bytes1
parameter_list|,
name|gint
name|bytes2
parameter_list|)
block|{
specifier|const
name|gint
name|alpha
init|=
name|bytes1
operator|-
literal|1
decl_stmt|;
specifier|const
name|gdouble
name|norm_opacity
init|=
name|opacity
operator|*
operator|(
literal|1.0
operator|/
literal|65536.0
operator|)
decl_stmt|;
if|if
condition|(
name|bytes1
operator|!=
name|bytes2
condition|)
block|{
name|g_warning
argument_list|(
literal|"replace_pixels only works on commensurate pixel regions"
argument_list|)
expr_stmt|;
return|return;
block|}
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|guint
name|b
decl_stmt|;
name|gdouble
name|mask_val
init|=
name|mask
index|[
literal|0
index|]
operator|*
name|norm_opacity
decl_stmt|;
comment|/* calculate new alpha first. */
name|gint
name|s1_a
init|=
name|src1
index|[
name|alpha
index|]
decl_stmt|;
name|gint
name|s2_a
init|=
name|src2
index|[
name|alpha
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
literal|0
condition|)
comment|/* In any case, write out versions of the blending function */
comment|/* that result when combinations of s1_a, s2_a, and         */
comment|/* mask_val --> 0 (or mask_val -->1)                        */
block|{
comment|/* Case 1: s1_a, s2_a, AND mask_val all approach 0+:               */
comment|/* Case 2: s1_a AND s2_a both approach 0+, regardless of mask_val: */
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
name|alpha
condition|;
name|b
operator|++
control|)
block|{
name|gint
name|new_val
init|=
literal|0.5
operator|+
operator|(
name|gdouble
operator|)
name|src1
index|[
name|b
index|]
operator|+
name|mask_val
operator|*
operator|(
operator|(
name|gdouble
operator|)
name|src2
index|[
name|b
index|]
operator|-
operator|(
name|gdouble
operator|)
name|src1
index|[
name|b
index|]
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
literal|255
argument_list|)
else|:
name|src1
index|[
name|b
index|]
expr_stmt|;
block|}
block|}
comment|/* Case 3: mask_val AND s1_a both approach 0+, regardless of s2_a  */
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
name|alpha
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
name|src1
index|[
name|b
index|]
expr_stmt|;
block|}
comment|/* Case 4: mask_val -->1 AND s2_a -->0, regardless of s1_a         */
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
name|alpha
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
name|src2
index|[
name|b
index|]
else|:
name|src1
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
comment|/* possible optimization: fold a_recip into s1_a and s2_a           */
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|alpha
condition|;
name|b
operator|++
control|)
block|{
name|gint
name|new_val
init|=
literal|0.5
operator|+
name|a_recip
operator|*
operator|(
name|src1
index|[
name|b
index|]
operator|*
name|s1_a
operator|+
name|mask_val
operator|*
operator|(
name|src2
index|[
name|b
index|]
operator|*
name|s2_a
operator|-
name|src1
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
literal|255
argument_list|)
else|:
name|src1
index|[
name|b
index|]
expr_stmt|;
block|}
block|}
name|dest
index|[
name|alpha
index|]
operator|=
name|affect
index|[
name|alpha
index|]
condition|?
name|a_val
operator|+
literal|0.5
else|:
name|s1_a
expr_stmt|;
name|src1
operator|+=
name|bytes1
expr_stmt|;
name|src2
operator|+=
name|bytes2
expr_stmt|;
name|dest
operator|+=
name|bytes2
expr_stmt|;
name|mask
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|inline
name|void
DECL|function|scale_pixels (const guchar * src,guchar * dest,guint length,gint scale)
name|scale_pixels
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|guint
name|length
parameter_list|,
name|gint
name|scale
parameter_list|)
block|{
name|gint
name|tmp
decl_stmt|;
while|while
condition|(
name|length
operator|--
condition|)
block|{
operator|*
name|dest
operator|++
operator|=
operator|(
name|guchar
operator|)
name|INT_MULT
argument_list|(
operator|*
name|src
argument_list|,
name|scale
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|src
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|inline
name|void
DECL|function|add_alpha_pixels (const guchar * src,guchar * dest,guint length,guint bytes)
name|add_alpha_pixels
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
block|{
specifier|const
name|guint
name|alpha
init|=
name|bytes
operator|+
literal|1
decl_stmt|;
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|guint
name|b
decl_stmt|;
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
name|dest
index|[
name|b
index|]
operator|=
name|src
index|[
name|b
index|]
expr_stmt|;
name|dest
index|[
name|b
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
name|src
operator|+=
name|bytes
expr_stmt|;
name|dest
operator|+=
name|alpha
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|inline
name|void
DECL|function|gray_to_rgb_pixels (const guchar * src,guchar * dest,guint length,guint bytes)
name|gray_to_rgb_pixels
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
block|{
specifier|const
name|gboolean
name|has_alpha
init|=
operator|(
name|bytes
operator|==
literal|2
operator|)
condition|?
name|TRUE
else|:
name|FALSE
decl_stmt|;
specifier|const
name|gint
name|dest_bytes
init|=
operator|(
name|has_alpha
operator|)
condition|?
literal|4
else|:
literal|3
decl_stmt|;
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|guint
name|b
decl_stmt|;
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
name|dest
index|[
name|b
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|dest
index|[
literal|3
index|]
operator|=
name|src
index|[
literal|1
index|]
expr_stmt|;
name|src
operator|+=
name|bytes
expr_stmt|;
name|dest
operator|+=
name|dest_bytes
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|inline
name|void
DECL|function|apply_mask_to_alpha_channel (guchar * src,const guchar * mask,guint opacity,guint length,guint bytes)
name|apply_mask_to_alpha_channel
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
name|guint
name|opacity
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
block|{
name|src
operator|+=
name|bytes
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|opacity
operator|==
literal|255
condition|)
block|{
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|glong
name|tmp
decl_stmt|;
operator|*
name|src
operator|=
name|INT_MULT
argument_list|(
operator|*
name|src
argument_list|,
operator|*
name|mask
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|mask
operator|++
expr_stmt|;
name|src
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
else|else
block|{
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|glong
name|tmp
decl_stmt|;
operator|*
name|src
operator|=
name|INT_MULT3
argument_list|(
operator|*
name|src
argument_list|,
operator|*
name|mask
argument_list|,
name|opacity
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|mask
operator|++
expr_stmt|;
name|src
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|inline
name|void
DECL|function|combine_mask_and_alpha_channel_stipple (guchar * src,const guchar * mask,guint opacity,guint length,guint bytes)
name|combine_mask_and_alpha_channel_stipple
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
name|guint
name|opacity
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
block|{
comment|/* align with alpha channel */
name|src
operator|+=
name|bytes
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|opacity
operator|!=
literal|255
condition|)
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|gint
name|tmp
decl_stmt|;
name|gint
name|mask_val
init|=
name|INT_MULT
argument_list|(
operator|*
name|mask
argument_list|,
name|opacity
argument_list|,
name|tmp
argument_list|)
decl_stmt|;
operator|*
name|src
operator|=
operator|*
name|src
operator|+
name|INT_MULT
argument_list|(
operator|(
literal|255
operator|-
operator|*
name|src
operator|)
argument_list|,
name|mask_val
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|src
operator|+=
name|bytes
expr_stmt|;
name|mask
operator|++
expr_stmt|;
block|}
else|else
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|gint
name|tmp
decl_stmt|;
operator|*
name|src
operator|=
operator|*
name|src
operator|+
name|INT_MULT
argument_list|(
operator|(
literal|255
operator|-
operator|*
name|src
operator|)
argument_list|,
operator|*
name|mask
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|src
operator|+=
name|bytes
expr_stmt|;
name|mask
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|inline
name|void
DECL|function|combine_mask_and_alpha_channel_stroke (guchar * src,const guchar * mask,guint opacity,guint length,guint bytes)
name|combine_mask_and_alpha_channel_stroke
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
name|guint
name|opacity
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
block|{
comment|/* align with alpha channel */
name|src
operator|+=
name|bytes
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|opacity
operator|!=
literal|255
condition|)
while|while
condition|(
name|length
operator|--
condition|)
block|{
if|if
condition|(
name|opacity
operator|>
operator|*
name|src
condition|)
block|{
name|gint
name|tmp
decl_stmt|;
name|gint
name|mask_val
init|=
name|INT_MULT
argument_list|(
operator|*
name|mask
argument_list|,
name|opacity
argument_list|,
name|tmp
argument_list|)
decl_stmt|;
operator|*
name|src
operator|=
operator|*
name|src
operator|+
name|INT_MULT
argument_list|(
operator|(
name|opacity
operator|-
operator|*
name|src
operator|)
argument_list|,
name|mask_val
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
block|}
name|src
operator|+=
name|bytes
expr_stmt|;
name|mask
operator|++
expr_stmt|;
block|}
else|else
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|gint
name|tmp
decl_stmt|;
operator|*
name|src
operator|=
operator|*
name|src
operator|+
name|INT_MULT
argument_list|(
operator|(
literal|255
operator|-
operator|*
name|src
operator|)
argument_list|,
operator|*
name|mask
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|src
operator|+=
name|bytes
expr_stmt|;
name|mask
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|inline
name|void
DECL|function|copy_gray_to_inten_a_pixels (const guchar * src,guchar * dest,guint length,guint bytes)
name|copy_gray_to_inten_a_pixels
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
block|{
specifier|const
name|guint
name|alpha
init|=
name|bytes
operator|-
literal|1
decl_stmt|;
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|guint
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|alpha
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
operator|*
name|src
expr_stmt|;
name|dest
index|[
name|b
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
name|src
operator|++
expr_stmt|;
name|dest
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|inline
name|void
DECL|function|initial_channel_pixels (const guchar * src,guchar * dest,guint length,guint bytes)
name|initial_channel_pixels
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
block|{
specifier|const
name|guint
name|alpha
init|=
name|bytes
operator|-
literal|1
decl_stmt|;
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|guint
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|alpha
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
name|dest
index|[
name|alpha
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
name|dest
operator|+=
name|bytes
expr_stmt|;
name|src
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|inline
name|void
DECL|function|initial_indexed_pixels (const guchar * src,guchar * dest,const guchar * cmap,guint length)
name|initial_indexed_pixels
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|cmap
parameter_list|,
name|guint
name|length
parameter_list|)
block|{
comment|/*  This function assumes always that we're mapping from    *  an RGB colormap to an RGBA image...    */
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|gint
name|col_index
init|=
operator|*
name|src
operator|++
operator|*
literal|3
decl_stmt|;
operator|*
name|dest
operator|++
operator|=
name|cmap
index|[
name|col_index
operator|++
index|]
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|cmap
index|[
name|col_index
operator|++
index|]
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|cmap
index|[
name|col_index
operator|++
index|]
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|inline
name|void
DECL|function|initial_indexed_a_pixels (const guchar * src,guchar * dest,const guchar * mask,const guchar * no_mask,const guchar * cmap,guint opacity,guint length)
name|initial_indexed_a_pixels
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
specifier|const
name|guchar
modifier|*
name|no_mask
parameter_list|,
specifier|const
name|guchar
modifier|*
name|cmap
parameter_list|,
name|guint
name|opacity
parameter_list|,
name|guint
name|length
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|m
init|=
name|mask
condition|?
name|mask
else|:
name|no_mask
decl_stmt|;
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|gint
name|col_index
init|=
operator|*
name|src
operator|++
operator|*
literal|3
decl_stmt|;
name|glong
name|tmp
decl_stmt|;
name|guchar
name|new_alpha
init|=
name|INT_MULT3
argument_list|(
operator|*
name|src
argument_list|,
operator|*
name|m
argument_list|,
name|opacity
argument_list|,
name|tmp
argument_list|)
decl_stmt|;
name|src
operator|++
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|cmap
index|[
name|col_index
operator|++
index|]
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|cmap
index|[
name|col_index
operator|++
index|]
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|cmap
index|[
name|col_index
operator|++
index|]
expr_stmt|;
comment|/*  Set the alpha channel  */
operator|*
name|dest
operator|++
operator|=
operator|(
name|new_alpha
operator|>
literal|127
operator|)
condition|?
name|OPAQUE_OPACITY
else|:
name|TRANSPARENT_OPACITY
expr_stmt|;
if|if
condition|(
name|mask
condition|)
name|m
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|inline
name|void
DECL|function|initial_inten_pixels (const guchar * src,guchar * dest,const guchar * mask,const guchar * no_mask,guint opacity,const gboolean * affect,guint length,guint bytes)
name|initial_inten_pixels
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
specifier|const
name|guchar
modifier|*
name|no_mask
parameter_list|,
name|guint
name|opacity
parameter_list|,
specifier|const
name|gboolean
modifier|*
name|affect
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|srcp
decl_stmt|;
specifier|const
name|gint
name|dest_bytes
init|=
name|bytes
operator|+
literal|1
decl_stmt|;
name|guchar
modifier|*
name|destp
decl_stmt|;
name|gint
name|b
decl_stmt|,
name|l
decl_stmt|;
if|if
condition|(
name|mask
condition|)
block|{
specifier|const
name|guchar
modifier|*
name|m
init|=
name|mask
decl_stmt|;
comment|/*  This function assumes the source has no alpha channel and        *  the destination has an alpha channel.  So dest_bytes = bytes + 1        */
if|if
condition|(
name|bytes
operator|==
literal|3
operator|&&
name|affect
index|[
literal|0
index|]
operator|&&
name|affect
index|[
literal|1
index|]
operator|&&
name|affect
index|[
literal|2
index|]
condition|)
block|{
if|if
condition|(
operator|!
name|affect
index|[
name|bytes
index|]
condition|)
name|opacity
operator|=
literal|0
expr_stmt|;
name|destp
operator|=
name|dest
operator|+
name|bytes
expr_stmt|;
if|if
condition|(
name|opacity
operator|!=
literal|0
condition|)
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|gint
name|tmp
decl_stmt|;
name|dest
index|[
literal|0
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|src
index|[
literal|1
index|]
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|src
index|[
literal|2
index|]
expr_stmt|;
name|dest
index|[
literal|3
index|]
operator|=
name|INT_MULT
argument_list|(
name|opacity
argument_list|,
operator|*
name|m
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|src
operator|+=
name|bytes
expr_stmt|;
name|dest
operator|+=
name|dest_bytes
expr_stmt|;
name|m
operator|++
expr_stmt|;
block|}
else|else
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|src
index|[
literal|1
index|]
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|src
index|[
literal|2
index|]
expr_stmt|;
name|dest
index|[
literal|3
index|]
operator|=
name|opacity
expr_stmt|;
name|src
operator|+=
name|bytes
expr_stmt|;
name|dest
operator|+=
name|dest_bytes
expr_stmt|;
block|}
return|return;
block|}
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
name|destp
operator|=
name|dest
operator|+
name|b
expr_stmt|;
name|srcp
operator|=
name|src
operator|+
name|b
expr_stmt|;
name|l
operator|=
name|length
expr_stmt|;
if|if
condition|(
name|affect
index|[
name|b
index|]
condition|)
while|while
condition|(
name|l
operator|--
condition|)
block|{
operator|*
name|destp
operator|=
operator|*
name|srcp
expr_stmt|;
name|srcp
operator|+=
name|bytes
expr_stmt|;
name|destp
operator|+=
name|dest_bytes
expr_stmt|;
block|}
else|else
while|while
condition|(
name|l
operator|--
condition|)
block|{
operator|*
name|destp
operator|=
literal|0
expr_stmt|;
name|destp
operator|+=
name|dest_bytes
expr_stmt|;
block|}
block|}
comment|/* fill the alpha channel */
if|if
condition|(
operator|!
name|affect
index|[
name|bytes
index|]
condition|)
name|opacity
operator|=
literal|0
expr_stmt|;
name|destp
operator|=
name|dest
operator|+
name|bytes
expr_stmt|;
if|if
condition|(
name|opacity
operator|!=
literal|0
condition|)
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|gint
name|tmp
decl_stmt|;
operator|*
name|destp
operator|=
name|INT_MULT
argument_list|(
name|opacity
argument_list|,
operator|*
name|m
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|destp
operator|+=
name|dest_bytes
expr_stmt|;
name|m
operator|++
expr_stmt|;
block|}
else|else
while|while
condition|(
name|length
operator|--
condition|)
block|{
operator|*
name|destp
operator|=
name|opacity
expr_stmt|;
name|destp
operator|+=
name|dest_bytes
expr_stmt|;
block|}
block|}
else|else
comment|/* no mask */
block|{
comment|/*  This function assumes the source has no alpha channel and        *  the destination has an alpha channel.  So dest_bytes = bytes + 1        */
if|if
condition|(
name|bytes
operator|==
literal|3
operator|&&
name|affect
index|[
literal|0
index|]
operator|&&
name|affect
index|[
literal|1
index|]
operator|&&
name|affect
index|[
literal|2
index|]
condition|)
block|{
if|if
condition|(
operator|!
name|affect
index|[
name|bytes
index|]
condition|)
name|opacity
operator|=
literal|0
expr_stmt|;
name|destp
operator|=
name|dest
operator|+
name|bytes
expr_stmt|;
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|src
index|[
literal|1
index|]
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|src
index|[
literal|2
index|]
expr_stmt|;
name|dest
index|[
literal|3
index|]
operator|=
name|opacity
expr_stmt|;
name|src
operator|+=
name|bytes
expr_stmt|;
name|dest
operator|+=
name|dest_bytes
expr_stmt|;
block|}
return|return;
block|}
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
name|destp
operator|=
name|dest
operator|+
name|b
expr_stmt|;
name|srcp
operator|=
name|src
operator|+
name|b
expr_stmt|;
name|l
operator|=
name|length
expr_stmt|;
if|if
condition|(
name|affect
index|[
name|b
index|]
condition|)
while|while
condition|(
name|l
operator|--
condition|)
block|{
operator|*
name|destp
operator|=
operator|*
name|srcp
expr_stmt|;
name|srcp
operator|+=
name|bytes
expr_stmt|;
name|destp
operator|+=
name|dest_bytes
expr_stmt|;
block|}
else|else
while|while
condition|(
name|l
operator|--
condition|)
block|{
operator|*
name|destp
operator|=
literal|0
expr_stmt|;
name|destp
operator|+=
name|dest_bytes
expr_stmt|;
block|}
block|}
comment|/* fill the alpha channel */
if|if
condition|(
operator|!
name|affect
index|[
name|bytes
index|]
condition|)
name|opacity
operator|=
literal|0
expr_stmt|;
name|destp
operator|=
name|dest
operator|+
name|bytes
expr_stmt|;
while|while
condition|(
name|length
operator|--
condition|)
block|{
operator|*
name|destp
operator|=
name|opacity
expr_stmt|;
name|destp
operator|+=
name|dest_bytes
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|inline
name|void
DECL|function|initial_inten_a_pixels (const guchar * src,guchar * dest,const guchar * mask,guint opacity,const gboolean * affect,guint length,guint bytes)
name|initial_inten_a_pixels
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
name|guint
name|opacity
parameter_list|,
specifier|const
name|gboolean
modifier|*
name|affect
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
block|{
specifier|const
name|guint
name|alpha
init|=
name|bytes
operator|-
literal|1
decl_stmt|;
if|if
condition|(
name|mask
condition|)
block|{
specifier|const
name|guchar
modifier|*
name|m
init|=
name|mask
decl_stmt|;
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|guint
name|b
decl_stmt|;
name|glong
name|tmp
decl_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|alpha
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
name|src
index|[
name|b
index|]
operator|*
name|affect
index|[
name|b
index|]
expr_stmt|;
comment|/*  Set the alpha channel  */
name|dest
index|[
name|alpha
index|]
operator|=
operator|(
name|affect
index|[
name|alpha
index|]
condition|?
name|INT_MULT3
argument_list|(
name|opacity
argument_list|,
name|src
index|[
name|alpha
index|]
argument_list|,
operator|*
name|m
argument_list|,
name|tmp
argument_list|)
else|:
literal|0
operator|)
expr_stmt|;
name|m
operator|++
expr_stmt|;
name|dest
operator|+=
name|bytes
expr_stmt|;
name|src
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
else|else
block|{
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|guint
name|b
decl_stmt|;
name|glong
name|tmp
decl_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|alpha
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
name|src
index|[
name|b
index|]
operator|*
name|affect
index|[
name|b
index|]
expr_stmt|;
comment|/*  Set the alpha channel  */
name|dest
index|[
name|alpha
index|]
operator|=
operator|(
name|affect
index|[
name|alpha
index|]
condition|?
name|INT_MULT
argument_list|(
name|opacity
argument_list|,
name|src
index|[
name|alpha
index|]
argument_list|,
name|tmp
argument_list|)
else|:
literal|0
operator|)
expr_stmt|;
name|dest
operator|+=
name|bytes
expr_stmt|;
name|src
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PAINT_FUNCS_GENERIC_H__  */
end_comment

end_unit

