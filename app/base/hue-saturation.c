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
name|unsigned
name|char
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
name|unsigned
name|char
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
comment|/* This change affects the way saturation is computed. With the 	   old code (different code for value< 0), increasing the 	   saturation affected muted colors very much, and bright colors 	   less. With the new code, it affects muted colors and bright 	   colors more or less evenly. For enhancing the color in photos, 	   the new behavior is exactly what you want. It's hard for me 	   to imagine a case in which the old behavior is better. 	*/
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
DECL|function|hue_saturation (PixelRegion * srcPR,PixelRegion * destPR,gpointer data)
name|hue_saturation
parameter_list|(
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|HueSaturation
modifier|*
name|hs
decl_stmt|;
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
name|hs
operator|=
operator|(
name|HueSaturation
operator|*
operator|)
name|data
expr_stmt|;
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
name|gimp_rgb_to_hls_int
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
if|if
condition|(
name|r
operator|<
literal|43
condition|)
name|hue
operator|=
literal|0
expr_stmt|;
elseif|else
if|if
condition|(
name|r
operator|<
literal|85
condition|)
name|hue
operator|=
literal|1
expr_stmt|;
elseif|else
if|if
condition|(
name|r
operator|<
literal|128
condition|)
name|hue
operator|=
literal|2
expr_stmt|;
elseif|else
if|if
condition|(
name|r
operator|<
literal|171
condition|)
name|hue
operator|=
literal|3
expr_stmt|;
elseif|else
if|if
condition|(
name|r
operator|<
literal|213
condition|)
name|hue
operator|=
literal|4
expr_stmt|;
else|else
name|hue
operator|=
literal|5
expr_stmt|;
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
name|lightness_transfer
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
name|saturation_transfer
index|[
name|hue
index|]
index|[
name|b
index|]
expr_stmt|;
name|gimp_hls_to_rgb_int
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

