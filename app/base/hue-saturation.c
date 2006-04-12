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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"base-types.h"
end_include

begin_include
include|#
directive|include
file|"hue-saturation.h"
end_include

begin_include
include|#
directive|include
file|"pixel-region.h"
end_include

begin_function
name|void
DECL|function|hue_saturation_init (HueSaturation * hs)
name|hue_saturation_init
parameter_list|(
name|HueSaturation
modifier|*
name|hs
parameter_list|)
block|{
name|GimpHueRange
name|partition
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|hs
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|hs
operator|->
name|overlap
operator|=
literal|0.0
expr_stmt|;
for|for
control|(
name|partition
operator|=
name|GIMP_ALL_HUES
init|;
name|partition
operator|<=
name|GIMP_MAGENTA_HUES
condition|;
name|partition
operator|++
control|)
name|hue_saturation_partition_reset
argument_list|(
name|hs
argument_list|,
name|partition
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|hue_saturation_partition_reset (HueSaturation * hs,GimpHueRange partition)
name|hue_saturation_partition_reset
parameter_list|(
name|HueSaturation
modifier|*
name|hs
parameter_list|,
name|GimpHueRange
name|partition
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|hs
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|hs
operator|->
name|hue
index|[
name|partition
index|]
operator|=
literal|0.0
expr_stmt|;
name|hs
operator|->
name|lightness
index|[
name|partition
index|]
operator|=
literal|0.0
expr_stmt|;
name|hs
operator|->
name|saturation
index|[
name|partition
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|hue_saturation_calculate_transfers (HueSaturation * hs)
name|hue_saturation_calculate_transfers
parameter_list|(
name|HueSaturation
modifier|*
name|hs
parameter_list|)
block|{
name|gint
name|value
decl_stmt|;
name|gint
name|hue
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|hs
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Calculate transfers  */
for|for
control|(
name|hue
operator|=
literal|0
init|;
name|hue
operator|<
literal|6
condition|;
name|hue
operator|++
control|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
block|{
name|value
operator|=
operator|(
name|hs
operator|->
name|hue
index|[
literal|0
index|]
operator|+
name|hs
operator|->
name|hue
index|[
name|hue
operator|+
literal|1
index|]
operator|)
operator|*
literal|255.0
operator|/
literal|360.0
expr_stmt|;
if|if
condition|(
operator|(
name|i
operator|+
name|value
operator|)
operator|<
literal|0
condition|)
name|hs
operator|->
name|hue_transfer
index|[
name|hue
index|]
index|[
name|i
index|]
operator|=
literal|255
operator|+
operator|(
name|i
operator|+
name|value
operator|)
expr_stmt|;
elseif|else
if|if
condition|(
operator|(
name|i
operator|+
name|value
operator|)
operator|>
literal|255
condition|)
name|hs
operator|->
name|hue_transfer
index|[
name|hue
index|]
index|[
name|i
index|]
operator|=
name|i
operator|+
name|value
operator|-
literal|255
expr_stmt|;
else|else
name|hs
operator|->
name|hue_transfer
index|[
name|hue
index|]
index|[
name|i
index|]
operator|=
name|i
operator|+
name|value
expr_stmt|;
comment|/*  Lightness  */
name|value
operator|=
operator|(
name|hs
operator|->
name|lightness
index|[
literal|0
index|]
operator|+
name|hs
operator|->
name|lightness
index|[
name|hue
operator|+
literal|1
index|]
operator|)
operator|*
literal|127.0
operator|/
literal|100.0
expr_stmt|;
name|value
operator|=
name|CLAMP
argument_list|(
name|value
argument_list|,
operator|-
literal|255
argument_list|,
literal|255
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|<
literal|0
condition|)
name|hs
operator|->
name|lightness_transfer
index|[
name|hue
index|]
index|[
name|i
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
operator|(
name|i
operator|*
operator|(
literal|255
operator|+
name|value
operator|)
operator|)
operator|/
literal|255
argument_list|)
expr_stmt|;
else|else
name|hs
operator|->
name|lightness_transfer
index|[
name|hue
index|]
index|[
name|i
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|i
operator|+
operator|(
operator|(
literal|255
operator|-
name|i
operator|)
operator|*
name|value
operator|)
operator|/
literal|255
argument_list|)
expr_stmt|;
comment|/*  Saturation  */
name|value
operator|=
operator|(
name|hs
operator|->
name|saturation
index|[
literal|0
index|]
operator|+
name|hs
operator|->
name|saturation
index|[
name|hue
operator|+
literal|1
index|]
operator|)
operator|*
literal|255.0
operator|/
literal|100.0
expr_stmt|;
name|value
operator|=
name|CLAMP
argument_list|(
name|value
argument_list|,
operator|-
literal|255
argument_list|,
literal|255
argument_list|)
expr_stmt|;
comment|/* This change affects the way saturation is computed. With the            old code (different code for value< 0), increasing the            saturation affected muted colors very much, and bright colors            less. With the new code, it affects muted colors and bright            colors more or less evenly. For enhancing the color in photos,            the new behavior is exactly what you want. It's hard for me            to imagine a case in which the old behavior is better.          */
name|hs
operator|->
name|saturation_transfer
index|[
name|hue
index|]
index|[
name|i
index|]
operator|=
name|CLAMP
argument_list|(
operator|(
name|i
operator|*
operator|(
literal|255
operator|+
name|value
operator|)
operator|)
operator|/
literal|255
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|hue_saturation (HueSaturation * hs,PixelRegion * srcPR,PixelRegion * destPR)
name|hue_saturation
parameter_list|(
name|HueSaturation
modifier|*
name|hs
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|s
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|,
modifier|*
name|d
decl_stmt|;
specifier|const
name|gint
name|hue_thresholds
index|[]
init|=
block|{
literal|21
block|,
literal|64
block|,
literal|106
block|,
literal|149
block|,
literal|192
block|,
literal|234
block|,
literal|255
block|}
decl_stmt|;
name|gint
name|alpha
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|hue
decl_stmt|;
name|gint
name|hue_counter
decl_stmt|;
name|gint
name|secondary_hue
init|=
literal|0
decl_stmt|;
name|gboolean
name|use_secondary_hue
init|=
name|FALSE
decl_stmt|;
name|gfloat
name|primary_intensity
init|=
literal|0.0
decl_stmt|;
name|gfloat
name|secondary_intensity
init|=
literal|0.0
decl_stmt|;
name|gfloat
name|overlap_hue
init|=
operator|(
name|hs
operator|->
name|overlap
operator|/
literal|100.0
operator|)
operator|*
literal|21
decl_stmt|;
comment|/*  Set the transfer arrays  (for speed)  */
name|h
operator|=
name|srcPR
operator|->
name|h
expr_stmt|;
name|src
operator|=
name|srcPR
operator|->
name|data
expr_stmt|;
name|dest
operator|=
name|destPR
operator|->
name|data
expr_stmt|;
name|alpha
operator|=
operator|(
name|srcPR
operator|->
name|bytes
operator|==
literal|4
operator|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
while|while
condition|(
name|h
operator|--
condition|)
block|{
name|w
operator|=
name|srcPR
operator|->
name|w
expr_stmt|;
name|s
operator|=
name|src
expr_stmt|;
name|d
operator|=
name|dest
expr_stmt|;
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|r
operator|=
name|s
index|[
name|RED_PIX
index|]
expr_stmt|;
name|g
operator|=
name|s
index|[
name|GREEN_PIX
index|]
expr_stmt|;
name|b
operator|=
name|s
index|[
name|BLUE_PIX
index|]
expr_stmt|;
name|gimp_rgb_to_hsl_int
argument_list|(
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|hue
operator|=
operator|(
name|r
operator|+
operator|(
literal|128
operator|/
literal|6
operator|)
operator|)
operator|/
literal|6
expr_stmt|;
for|for
control|(
name|hue_counter
operator|=
literal|0
init|;
name|hue_counter
operator|<
literal|7
condition|;
name|hue_counter
operator|++
control|)
if|if
condition|(
name|r
operator|<
name|hue_thresholds
index|[
name|hue_counter
index|]
operator|+
name|overlap_hue
condition|)
block|{
name|gint
name|hue_threshold
init|=
name|hue_thresholds
index|[
name|hue_counter
index|]
decl_stmt|;
name|hue
operator|=
name|hue_counter
expr_stmt|;
if|if
condition|(
name|overlap_hue
operator|>
literal|1.0
operator|&&
name|r
operator|>
name|hue_threshold
operator|-
name|overlap_hue
condition|)
block|{
name|secondary_hue
operator|=
name|hue_counter
operator|+
literal|1
expr_stmt|;
name|use_secondary_hue
operator|=
name|TRUE
expr_stmt|;
name|secondary_intensity
operator|=
operator|(
name|r
operator|-
name|hue_threshold
operator|+
name|overlap_hue
operator|)
operator|/
operator|(
literal|2.0
operator|*
name|overlap_hue
operator|)
expr_stmt|;
name|primary_intensity
operator|=
literal|1.0
operator|-
name|secondary_intensity
expr_stmt|;
block|}
else|else
block|{
name|use_secondary_hue
operator|=
name|FALSE
expr_stmt|;
block|}
break|break;
block|}
if|if
condition|(
name|hue
operator|>=
literal|6
condition|)
block|{
name|hue
operator|=
literal|0
expr_stmt|;
name|use_secondary_hue
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|secondary_hue
operator|>=
literal|6
condition|)
name|secondary_hue
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|use_secondary_hue
condition|)
block|{
name|r
operator|=
name|hs
operator|->
name|hue_transfer
index|[
name|hue
index|]
index|[
name|r
index|]
operator|*
name|primary_intensity
operator|+
name|hs
operator|->
name|hue_transfer
index|[
name|secondary_hue
index|]
index|[
name|r
index|]
operator|*
name|secondary_intensity
expr_stmt|;
name|g
operator|=
name|hs
operator|->
name|saturation_transfer
index|[
name|hue
index|]
index|[
name|g
index|]
operator|*
name|primary_intensity
operator|+
name|hs
operator|->
name|saturation_transfer
index|[
name|secondary_hue
index|]
index|[
name|g
index|]
operator|*
name|secondary_intensity
expr_stmt|;
name|b
operator|=
name|hs
operator|->
name|lightness_transfer
index|[
name|hue
index|]
index|[
name|b
index|]
operator|*
name|primary_intensity
operator|+
name|hs
operator|->
name|lightness_transfer
index|[
name|secondary_hue
index|]
index|[
name|b
index|]
operator|*
name|secondary_intensity
expr_stmt|;
block|}
else|else
block|{
name|r
operator|=
name|hs
operator|->
name|hue_transfer
index|[
name|hue
index|]
index|[
name|r
index|]
expr_stmt|;
name|g
operator|=
name|hs
operator|->
name|saturation_transfer
index|[
name|hue
index|]
index|[
name|g
index|]
expr_stmt|;
name|b
operator|=
name|hs
operator|->
name|lightness_transfer
index|[
name|hue
index|]
index|[
name|b
index|]
expr_stmt|;
block|}
name|gimp_hsl_to_rgb_int
argument_list|(
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|d
index|[
name|RED_PIX
index|]
operator|=
name|r
expr_stmt|;
name|d
index|[
name|GREEN_PIX
index|]
operator|=
name|g
expr_stmt|;
name|d
index|[
name|BLUE_PIX
index|]
operator|=
name|b
expr_stmt|;
if|if
condition|(
name|alpha
condition|)
name|d
index|[
name|ALPHA_PIX
index|]
operator|=
name|s
index|[
name|ALPHA_PIX
index|]
expr_stmt|;
name|s
operator|+=
name|srcPR
operator|->
name|bytes
expr_stmt|;
name|d
operator|+=
name|destPR
operator|->
name|bytes
expr_stmt|;
block|}
name|src
operator|+=
name|srcPR
operator|->
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|destPR
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
end_function

end_unit

