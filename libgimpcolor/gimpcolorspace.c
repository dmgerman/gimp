begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<babl/babl.h>
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
file|"gimpcolortypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorspace.h"
end_include

begin_include
include|#
directive|include
file|"gimprgb.h"
end_include

begin_include
include|#
directive|include
file|"gimphsv.h"
end_include

begin_comment
comment|/**  * SECTION: gimpcolorspace  * @title: GimpColorSpace  * @short_description: Utility functions which convert colors between  *                     different color models.  *  * When programming pixel data manipulation functions you will often  * use algorithms operating on a color model different from the one  * GIMP uses.  This file provides utility functions to convert colors  * between different color spaces.  **/
end_comment

begin_define
DECL|macro|GIMP_HSL_UNDEFINED
define|#
directive|define
name|GIMP_HSL_UNDEFINED
value|-1.0
end_define

begin_comment
comment|/*  GimpRGB functions  */
end_comment

begin_comment
comment|/**  * gimp_rgb_to_hsv:  * @rgb: A color value in the RGB colorspace  * @hsv: The value converted to the HSV colorspace  *  * Does a conversion from RGB to HSV (Hue, Saturation,  * Value) colorspace.  **/
end_comment

begin_function
name|void
DECL|function|gimp_rgb_to_hsv (const GimpRGB * rgb,GimpHSV * hsv)
name|gimp_rgb_to_hsv
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
block|{
name|gdouble
name|max
decl_stmt|,
name|min
decl_stmt|,
name|delta
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|hsv
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|max
operator|=
name|gimp_rgb_max
argument_list|(
name|rgb
argument_list|)
expr_stmt|;
name|min
operator|=
name|gimp_rgb_min
argument_list|(
name|rgb
argument_list|)
expr_stmt|;
name|hsv
operator|->
name|v
operator|=
name|max
expr_stmt|;
name|delta
operator|=
name|max
operator|-
name|min
expr_stmt|;
if|if
condition|(
name|delta
operator|>
literal|0.0001
condition|)
block|{
name|hsv
operator|->
name|s
operator|=
name|delta
operator|/
name|max
expr_stmt|;
if|if
condition|(
name|rgb
operator|->
name|r
operator|==
name|max
condition|)
block|{
name|hsv
operator|->
name|h
operator|=
operator|(
name|rgb
operator|->
name|g
operator|-
name|rgb
operator|->
name|b
operator|)
operator|/
name|delta
expr_stmt|;
if|if
condition|(
name|hsv
operator|->
name|h
operator|<
literal|0.0
condition|)
name|hsv
operator|->
name|h
operator|+=
literal|6.0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|rgb
operator|->
name|g
operator|==
name|max
condition|)
block|{
name|hsv
operator|->
name|h
operator|=
literal|2.0
operator|+
operator|(
name|rgb
operator|->
name|b
operator|-
name|rgb
operator|->
name|r
operator|)
operator|/
name|delta
expr_stmt|;
block|}
else|else
block|{
name|hsv
operator|->
name|h
operator|=
literal|4.0
operator|+
operator|(
name|rgb
operator|->
name|r
operator|-
name|rgb
operator|->
name|g
operator|)
operator|/
name|delta
expr_stmt|;
block|}
name|hsv
operator|->
name|h
operator|/=
literal|6.0
expr_stmt|;
block|}
else|else
block|{
name|hsv
operator|->
name|s
operator|=
literal|0.0
expr_stmt|;
name|hsv
operator|->
name|h
operator|=
literal|0.0
expr_stmt|;
block|}
name|hsv
operator|->
name|a
operator|=
name|rgb
operator|->
name|a
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_hsv_to_rgb:  * @hsv: A color value in the HSV colorspace  * @rgb: The returned RGB value.  *  * Converts a color value from HSV to RGB colorspace  **/
end_comment

begin_function
name|void
DECL|function|gimp_hsv_to_rgb (const GimpHSV * hsv,GimpRGB * rgb)
name|gimp_hsv_to_rgb
parameter_list|(
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|,
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gdouble
name|f
decl_stmt|,
name|w
decl_stmt|,
name|q
decl_stmt|,
name|t
decl_stmt|;
name|gdouble
name|hue
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|hsv
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|hsv
operator|->
name|s
operator|==
literal|0.0
condition|)
block|{
name|rgb
operator|->
name|r
operator|=
name|hsv
operator|->
name|v
expr_stmt|;
name|rgb
operator|->
name|g
operator|=
name|hsv
operator|->
name|v
expr_stmt|;
name|rgb
operator|->
name|b
operator|=
name|hsv
operator|->
name|v
expr_stmt|;
block|}
else|else
block|{
name|hue
operator|=
name|hsv
operator|->
name|h
expr_stmt|;
if|if
condition|(
name|hue
operator|==
literal|1.0
condition|)
name|hue
operator|=
literal|0.0
expr_stmt|;
name|hue
operator|*=
literal|6.0
expr_stmt|;
name|i
operator|=
operator|(
name|gint
operator|)
name|hue
expr_stmt|;
name|f
operator|=
name|hue
operator|-
name|i
expr_stmt|;
name|w
operator|=
name|hsv
operator|->
name|v
operator|*
operator|(
literal|1.0
operator|-
name|hsv
operator|->
name|s
operator|)
expr_stmt|;
name|q
operator|=
name|hsv
operator|->
name|v
operator|*
operator|(
literal|1.0
operator|-
operator|(
name|hsv
operator|->
name|s
operator|*
name|f
operator|)
operator|)
expr_stmt|;
name|t
operator|=
name|hsv
operator|->
name|v
operator|*
operator|(
literal|1.0
operator|-
operator|(
name|hsv
operator|->
name|s
operator|*
operator|(
literal|1.0
operator|-
name|f
operator|)
operator|)
operator|)
expr_stmt|;
switch|switch
condition|(
name|i
condition|)
block|{
case|case
literal|0
case|:
name|rgb
operator|->
name|r
operator|=
name|hsv
operator|->
name|v
expr_stmt|;
name|rgb
operator|->
name|g
operator|=
name|t
expr_stmt|;
name|rgb
operator|->
name|b
operator|=
name|w
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|rgb
operator|->
name|r
operator|=
name|q
expr_stmt|;
name|rgb
operator|->
name|g
operator|=
name|hsv
operator|->
name|v
expr_stmt|;
name|rgb
operator|->
name|b
operator|=
name|w
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|rgb
operator|->
name|r
operator|=
name|w
expr_stmt|;
name|rgb
operator|->
name|g
operator|=
name|hsv
operator|->
name|v
expr_stmt|;
name|rgb
operator|->
name|b
operator|=
name|t
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|rgb
operator|->
name|r
operator|=
name|w
expr_stmt|;
name|rgb
operator|->
name|g
operator|=
name|q
expr_stmt|;
name|rgb
operator|->
name|b
operator|=
name|hsv
operator|->
name|v
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|rgb
operator|->
name|r
operator|=
name|t
expr_stmt|;
name|rgb
operator|->
name|g
operator|=
name|w
expr_stmt|;
name|rgb
operator|->
name|b
operator|=
name|hsv
operator|->
name|v
expr_stmt|;
break|break;
case|case
literal|5
case|:
name|rgb
operator|->
name|r
operator|=
name|hsv
operator|->
name|v
expr_stmt|;
name|rgb
operator|->
name|g
operator|=
name|w
expr_stmt|;
name|rgb
operator|->
name|b
operator|=
name|q
expr_stmt|;
break|break;
block|}
block|}
name|rgb
operator|->
name|a
operator|=
name|hsv
operator|->
name|a
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_rgb_to_hsl:  * @rgb: A color value in the RGB colorspace  * @hsl: The value converted to HSL  *  * Convert an RGB color value to a HSL (Hue, Saturation, Lightness)  * color value.  **/
end_comment

begin_function
name|void
DECL|function|gimp_rgb_to_hsl (const GimpRGB * rgb,GimpHSL * hsl)
name|gimp_rgb_to_hsl
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|GimpHSL
modifier|*
name|hsl
parameter_list|)
block|{
name|gdouble
name|max
decl_stmt|,
name|min
decl_stmt|,
name|delta
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|hsl
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|max
operator|=
name|gimp_rgb_max
argument_list|(
name|rgb
argument_list|)
expr_stmt|;
name|min
operator|=
name|gimp_rgb_min
argument_list|(
name|rgb
argument_list|)
expr_stmt|;
name|hsl
operator|->
name|l
operator|=
operator|(
name|max
operator|+
name|min
operator|)
operator|/
literal|2.0
expr_stmt|;
if|if
condition|(
name|max
operator|==
name|min
condition|)
block|{
name|hsl
operator|->
name|s
operator|=
literal|0.0
expr_stmt|;
name|hsl
operator|->
name|h
operator|=
name|GIMP_HSL_UNDEFINED
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|hsl
operator|->
name|l
operator|<=
literal|0.5
condition|)
name|hsl
operator|->
name|s
operator|=
operator|(
name|max
operator|-
name|min
operator|)
operator|/
operator|(
name|max
operator|+
name|min
operator|)
expr_stmt|;
else|else
name|hsl
operator|->
name|s
operator|=
operator|(
name|max
operator|-
name|min
operator|)
operator|/
operator|(
literal|2.0
operator|-
name|max
operator|-
name|min
operator|)
expr_stmt|;
name|delta
operator|=
name|max
operator|-
name|min
expr_stmt|;
if|if
condition|(
name|delta
operator|==
literal|0.0
condition|)
name|delta
operator|=
literal|1.0
expr_stmt|;
if|if
condition|(
name|rgb
operator|->
name|r
operator|==
name|max
condition|)
block|{
name|hsl
operator|->
name|h
operator|=
operator|(
name|rgb
operator|->
name|g
operator|-
name|rgb
operator|->
name|b
operator|)
operator|/
name|delta
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|rgb
operator|->
name|g
operator|==
name|max
condition|)
block|{
name|hsl
operator|->
name|h
operator|=
literal|2.0
operator|+
operator|(
name|rgb
operator|->
name|b
operator|-
name|rgb
operator|->
name|r
operator|)
operator|/
name|delta
expr_stmt|;
block|}
else|else
block|{
name|hsl
operator|->
name|h
operator|=
literal|4.0
operator|+
operator|(
name|rgb
operator|->
name|r
operator|-
name|rgb
operator|->
name|g
operator|)
operator|/
name|delta
expr_stmt|;
block|}
name|hsl
operator|->
name|h
operator|/=
literal|6.0
expr_stmt|;
if|if
condition|(
name|hsl
operator|->
name|h
operator|<
literal|0.0
condition|)
name|hsl
operator|->
name|h
operator|+=
literal|1.0
expr_stmt|;
block|}
name|hsl
operator|->
name|a
operator|=
name|rgb
operator|->
name|a
expr_stmt|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|gdouble
DECL|function|gimp_hsl_value (gdouble n1,gdouble n2,gdouble hue)
name|gimp_hsl_value
parameter_list|(
name|gdouble
name|n1
parameter_list|,
name|gdouble
name|n2
parameter_list|,
name|gdouble
name|hue
parameter_list|)
block|{
name|gdouble
name|val
decl_stmt|;
if|if
condition|(
name|hue
operator|>
literal|6.0
condition|)
name|hue
operator|-=
literal|6.0
expr_stmt|;
elseif|else
if|if
condition|(
name|hue
operator|<
literal|0.0
condition|)
name|hue
operator|+=
literal|6.0
expr_stmt|;
if|if
condition|(
name|hue
operator|<
literal|1.0
condition|)
name|val
operator|=
name|n1
operator|+
operator|(
name|n2
operator|-
name|n1
operator|)
operator|*
name|hue
expr_stmt|;
elseif|else
if|if
condition|(
name|hue
operator|<
literal|3.0
condition|)
name|val
operator|=
name|n2
expr_stmt|;
elseif|else
if|if
condition|(
name|hue
operator|<
literal|4.0
condition|)
name|val
operator|=
name|n1
operator|+
operator|(
name|n2
operator|-
name|n1
operator|)
operator|*
operator|(
literal|4.0
operator|-
name|hue
operator|)
expr_stmt|;
else|else
name|val
operator|=
name|n1
expr_stmt|;
return|return
name|val
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_hsl_to_rgb:  * @hsl: A color value in the HSL colorspace  * @rgb: The value converted to a value in the RGB colorspace  *  * Convert a HSL color value to an RGB color value.  **/
end_comment

begin_function
name|void
DECL|function|gimp_hsl_to_rgb (const GimpHSL * hsl,GimpRGB * rgb)
name|gimp_hsl_to_rgb
parameter_list|(
specifier|const
name|GimpHSL
modifier|*
name|hsl
parameter_list|,
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|hsl
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|hsl
operator|->
name|s
operator|==
literal|0
condition|)
block|{
comment|/*  achromatic case  */
name|rgb
operator|->
name|r
operator|=
name|hsl
operator|->
name|l
expr_stmt|;
name|rgb
operator|->
name|g
operator|=
name|hsl
operator|->
name|l
expr_stmt|;
name|rgb
operator|->
name|b
operator|=
name|hsl
operator|->
name|l
expr_stmt|;
block|}
else|else
block|{
name|gdouble
name|m1
decl_stmt|,
name|m2
decl_stmt|;
if|if
condition|(
name|hsl
operator|->
name|l
operator|<=
literal|0.5
condition|)
name|m2
operator|=
name|hsl
operator|->
name|l
operator|*
operator|(
literal|1.0
operator|+
name|hsl
operator|->
name|s
operator|)
expr_stmt|;
else|else
name|m2
operator|=
name|hsl
operator|->
name|l
operator|+
name|hsl
operator|->
name|s
operator|-
name|hsl
operator|->
name|l
operator|*
name|hsl
operator|->
name|s
expr_stmt|;
name|m1
operator|=
literal|2.0
operator|*
name|hsl
operator|->
name|l
operator|-
name|m2
expr_stmt|;
name|rgb
operator|->
name|r
operator|=
name|gimp_hsl_value
argument_list|(
name|m1
argument_list|,
name|m2
argument_list|,
name|hsl
operator|->
name|h
operator|*
literal|6.0
operator|+
literal|2.0
argument_list|)
expr_stmt|;
name|rgb
operator|->
name|g
operator|=
name|gimp_hsl_value
argument_list|(
name|m1
argument_list|,
name|m2
argument_list|,
name|hsl
operator|->
name|h
operator|*
literal|6.0
argument_list|)
expr_stmt|;
name|rgb
operator|->
name|b
operator|=
name|gimp_hsl_value
argument_list|(
name|m1
argument_list|,
name|m2
argument_list|,
name|hsl
operator|->
name|h
operator|*
literal|6.0
operator|-
literal|2.0
argument_list|)
expr_stmt|;
block|}
name|rgb
operator|->
name|a
operator|=
name|hsl
operator|->
name|a
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_rgb_to_cmyk:  * @rgb: A value in the RGB colorspace  * @pullout: A scaling value (0-1) indicating how much black should be  *           pulled out  * @cmyk: The input value naively converted to the CMYK colorspace  *  * Does a naive conversion from RGB to CMYK colorspace. A simple  * formula that doesn't take any color-profiles into account is used.  * The amount of black pullout how can be controlled via the @pullout  * parameter. A @pullout value of 0 makes this a conversion to CMY.  * A value of 1 causes the maximum amount of black to be pulled out.  **/
end_comment

begin_function
name|void
DECL|function|gimp_rgb_to_cmyk (const GimpRGB * rgb,gdouble pullout,GimpCMYK * cmyk)
name|gimp_rgb_to_cmyk
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|gdouble
name|pullout
parameter_list|,
name|GimpCMYK
modifier|*
name|cmyk
parameter_list|)
block|{
name|gdouble
name|c
decl_stmt|,
name|m
decl_stmt|,
name|y
decl_stmt|,
name|k
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|cmyk
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|c
operator|=
literal|1.0
operator|-
name|rgb
operator|->
name|r
expr_stmt|;
name|m
operator|=
literal|1.0
operator|-
name|rgb
operator|->
name|g
expr_stmt|;
name|y
operator|=
literal|1.0
operator|-
name|rgb
operator|->
name|b
expr_stmt|;
name|k
operator|=
literal|1.0
expr_stmt|;
if|if
condition|(
name|c
operator|<
name|k
condition|)
name|k
operator|=
name|c
expr_stmt|;
if|if
condition|(
name|m
operator|<
name|k
condition|)
name|k
operator|=
name|m
expr_stmt|;
if|if
condition|(
name|y
operator|<
name|k
condition|)
name|k
operator|=
name|y
expr_stmt|;
name|k
operator|*=
name|pullout
expr_stmt|;
if|if
condition|(
name|k
operator|<
literal|1.0
condition|)
block|{
name|cmyk
operator|->
name|c
operator|=
operator|(
name|c
operator|-
name|k
operator|)
operator|/
operator|(
literal|1.0
operator|-
name|k
operator|)
expr_stmt|;
name|cmyk
operator|->
name|m
operator|=
operator|(
name|m
operator|-
name|k
operator|)
operator|/
operator|(
literal|1.0
operator|-
name|k
operator|)
expr_stmt|;
name|cmyk
operator|->
name|y
operator|=
operator|(
name|y
operator|-
name|k
operator|)
operator|/
operator|(
literal|1.0
operator|-
name|k
operator|)
expr_stmt|;
block|}
else|else
block|{
name|cmyk
operator|->
name|c
operator|=
literal|0.0
expr_stmt|;
name|cmyk
operator|->
name|m
operator|=
literal|0.0
expr_stmt|;
name|cmyk
operator|->
name|y
operator|=
literal|0.0
expr_stmt|;
block|}
name|cmyk
operator|->
name|k
operator|=
name|k
expr_stmt|;
name|cmyk
operator|->
name|a
operator|=
name|rgb
operator|->
name|a
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_cmyk_to_rgb:  * @cmyk: A color value in the CMYK colorspace  * @rgb: The value converted to the RGB colorspace  *  * Does a simple transformation from the CMYK colorspace to the RGB  * colorspace, without taking color profiles into account.  **/
end_comment

begin_function
name|void
DECL|function|gimp_cmyk_to_rgb (const GimpCMYK * cmyk,GimpRGB * rgb)
name|gimp_cmyk_to_rgb
parameter_list|(
specifier|const
name|GimpCMYK
modifier|*
name|cmyk
parameter_list|,
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|gdouble
name|c
decl_stmt|,
name|m
decl_stmt|,
name|y
decl_stmt|,
name|k
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|cmyk
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|k
operator|=
name|cmyk
operator|->
name|k
expr_stmt|;
if|if
condition|(
name|k
operator|<
literal|1.0
condition|)
block|{
name|c
operator|=
name|cmyk
operator|->
name|c
operator|*
operator|(
literal|1.0
operator|-
name|k
operator|)
operator|+
name|k
expr_stmt|;
name|m
operator|=
name|cmyk
operator|->
name|m
operator|*
operator|(
literal|1.0
operator|-
name|k
operator|)
operator|+
name|k
expr_stmt|;
name|y
operator|=
name|cmyk
operator|->
name|y
operator|*
operator|(
literal|1.0
operator|-
name|k
operator|)
operator|+
name|k
expr_stmt|;
block|}
else|else
block|{
name|c
operator|=
literal|1.0
expr_stmt|;
name|m
operator|=
literal|1.0
expr_stmt|;
name|y
operator|=
literal|1.0
expr_stmt|;
block|}
name|rgb
operator|->
name|r
operator|=
literal|1.0
operator|-
name|c
expr_stmt|;
name|rgb
operator|->
name|g
operator|=
literal|1.0
operator|-
name|m
expr_stmt|;
name|rgb
operator|->
name|b
operator|=
literal|1.0
operator|-
name|y
expr_stmt|;
name|rgb
operator|->
name|a
operator|=
name|cmyk
operator|->
name|a
expr_stmt|;
block|}
end_function

end_unit

