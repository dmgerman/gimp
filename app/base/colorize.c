begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"colorize.h"
end_include

begin_include
include|#
directive|include
file|"pixel-region.h"
end_include

begin_function
name|void
DECL|function|colorize_init (Colorize * colorize)
name|colorize_init
parameter_list|(
name|Colorize
modifier|*
name|colorize
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|colorize
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|colorize
operator|->
name|hue
operator|=
literal|180.0
expr_stmt|;
name|colorize
operator|->
name|saturation
operator|=
literal|50.0
expr_stmt|;
name|colorize
operator|->
name|lightness
operator|=
literal|0.0
expr_stmt|;
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
name|colorize
operator|->
name|lum_red_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
name|GIMP_RGB_LUMINANCE_RED
expr_stmt|;
name|colorize
operator|->
name|lum_green_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
name|GIMP_RGB_LUMINANCE_GREEN
expr_stmt|;
name|colorize
operator|->
name|lum_blue_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
name|GIMP_RGB_LUMINANCE_BLUE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|colorize_calculate (Colorize * colorize)
name|colorize_calculate
parameter_list|(
name|Colorize
modifier|*
name|colorize
parameter_list|)
block|{
name|GimpHSL
name|hsl
decl_stmt|;
name|GimpRGB
name|rgb
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|colorize
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|hsl
operator|.
name|h
operator|=
name|colorize
operator|->
name|hue
operator|/
literal|360.0
expr_stmt|;
name|hsl
operator|.
name|s
operator|=
name|colorize
operator|->
name|saturation
operator|/
literal|100.0
expr_stmt|;
comment|/*  Calculate transfers  */
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
name|hsl
operator|.
name|l
operator|=
operator|(
name|gdouble
operator|)
name|i
operator|/
literal|255.0
expr_stmt|;
name|gimp_hsl_to_rgb
argument_list|(
operator|&
name|hsl
argument_list|,
operator|&
name|rgb
argument_list|)
expr_stmt|;
comment|/*  this used to read i * rgb.r,g,b in GIMP 2.4, but this produced        *  darkened results, multiplying with 255 is correct and preserves        *  the lightness unless modified with the slider.        */
name|colorize
operator|->
name|final_red_lookup
index|[
name|i
index|]
operator|=
literal|255.0
operator|*
name|rgb
operator|.
name|r
expr_stmt|;
name|colorize
operator|->
name|final_green_lookup
index|[
name|i
index|]
operator|=
literal|255.0
operator|*
name|rgb
operator|.
name|g
expr_stmt|;
name|colorize
operator|->
name|final_blue_lookup
index|[
name|i
index|]
operator|=
literal|255.0
operator|*
name|rgb
operator|.
name|b
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|colorize (Colorize * colorize,PixelRegion * srcPR,PixelRegion * destPR)
name|colorize
parameter_list|(
name|Colorize
modifier|*
name|colorize
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
name|gboolean
name|alpha
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|lum
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
name|lum
operator|=
operator|(
name|colorize
operator|->
name|lum_red_lookup
index|[
name|s
index|[
name|RED_PIX
index|]
index|]
operator|+
name|colorize
operator|->
name|lum_green_lookup
index|[
name|s
index|[
name|GREEN_PIX
index|]
index|]
operator|+
name|colorize
operator|->
name|lum_blue_lookup
index|[
name|s
index|[
name|BLUE_PIX
index|]
index|]
operator|)
expr_stmt|;
comment|/* luminosity */
if|if
condition|(
name|colorize
operator|->
name|lightness
operator|>
literal|0
condition|)
block|{
name|lum
operator|=
operator|(
name|gdouble
operator|)
name|lum
operator|*
operator|(
literal|100.0
operator|-
name|colorize
operator|->
name|lightness
operator|)
operator|/
literal|100.0
expr_stmt|;
name|lum
operator|+=
literal|255
operator|-
operator|(
literal|100.0
operator|-
name|colorize
operator|->
name|lightness
operator|)
operator|*
literal|255.0
operator|/
literal|100.0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|colorize
operator|->
name|lightness
operator|<
literal|0
condition|)
block|{
name|lum
operator|=
operator|(
name|gdouble
operator|)
name|lum
operator|*
operator|(
name|colorize
operator|->
name|lightness
operator|+
literal|100.0
operator|)
operator|/
literal|100.0
expr_stmt|;
block|}
name|d
index|[
name|RED_PIX
index|]
operator|=
name|colorize
operator|->
name|final_red_lookup
index|[
name|lum
index|]
expr_stmt|;
name|d
index|[
name|GREEN_PIX
index|]
operator|=
name|colorize
operator|->
name|final_green_lookup
index|[
name|lum
index|]
expr_stmt|;
name|d
index|[
name|BLUE_PIX
index|]
operator|=
name|colorize
operator|->
name|final_blue_lookup
index|[
name|lum
index|]
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

