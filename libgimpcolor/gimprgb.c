begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolortypes.h"
end_include

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_comment
comment|/*  for GIMP_RGB_INTENSITY()  */
end_comment

begin_include
include|#
directive|include
file|"gimprgb.h"
end_include

begin_comment
comment|/*  RGB type  */
end_comment

begin_function_decl
specifier|static
name|GimpRGB
modifier|*
name|rgb_copy
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_rgb_get_type (void)
name|gimp_rgb_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|rgb_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|rgb_type
condition|)
name|rgb_type
operator|=
name|g_boxed_type_register_static
argument_list|(
literal|"GimpRGB"
argument_list|,
operator|(
name|GBoxedCopyFunc
operator|)
name|rgb_copy
argument_list|,
operator|(
name|GBoxedFreeFunc
operator|)
name|g_free
argument_list|)
expr_stmt|;
return|return
name|rgb_type
return|;
block|}
end_function

begin_function
specifier|static
name|GimpRGB
modifier|*
DECL|function|rgb_copy (const GimpRGB * rgb)
name|rgb_copy
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
return|return
name|g_memdup
argument_list|(
name|rgb
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpRGB
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  RGB functions  */
end_comment

begin_comment
comment|/**  * gimp_rgb_set:  * @rgb: a #GimpRGB struct  * @red:  * @green:  * @blue:  *  * Sets the red, green and blue components of @rgb and leaves the  * alpha component unchanged. The color values should be between 0.0  * and 1.0 but there is no check to enforce this and the values are  * set exactly as they are passed in.  **/
end_comment

begin_function
name|void
DECL|function|gimp_rgb_set (GimpRGB * rgb,gdouble r,gdouble g,gdouble b)
name|gimp_rgb_set
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|gdouble
name|r
parameter_list|,
name|gdouble
name|g
parameter_list|,
name|gdouble
name|b
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|rgb
operator|->
name|r
operator|=
name|r
expr_stmt|;
name|rgb
operator|->
name|g
operator|=
name|g
expr_stmt|;
name|rgb
operator|->
name|b
operator|=
name|b
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_rgb_set_alpha:  * @rgb: a #GimpRGB struct  * @alpha:  *  * Sets the alpha component of @rgb and leaves the RGB components unchanged.  **/
end_comment

begin_function
name|void
DECL|function|gimp_rgb_set_alpha (GimpRGB * rgb,gdouble a)
name|gimp_rgb_set_alpha
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|gdouble
name|a
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|rgb
operator|->
name|a
operator|=
name|a
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_rgb_set_uchar:  * @rgb: a #GimpRGB struct  * @red:  * @green:  * @blue:  *  * Sets the red, green and blue components of @rgb from 8bit values  * (0 to 255) and leaves the alpha component unchanged.  **/
end_comment

begin_function
name|void
DECL|function|gimp_rgb_set_uchar (GimpRGB * rgb,guchar r,guchar g,guchar b)
name|gimp_rgb_set_uchar
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|rgb
operator|->
name|r
operator|=
operator|(
name|gdouble
operator|)
name|r
operator|/
literal|255.0
expr_stmt|;
name|rgb
operator|->
name|g
operator|=
operator|(
name|gdouble
operator|)
name|g
operator|/
literal|255.0
expr_stmt|;
name|rgb
operator|->
name|b
operator|=
operator|(
name|gdouble
operator|)
name|b
operator|/
literal|255.0
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgb_get_uchar (const GimpRGB * rgb,guchar * r,guchar * g,guchar * b)
name|gimp_rgb_get_uchar
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|guchar
modifier|*
name|r
parameter_list|,
name|guchar
modifier|*
name|g
parameter_list|,
name|guchar
modifier|*
name|b
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
condition|)
operator|*
name|r
operator|=
name|ROUND
argument_list|(
name|CLAMP
argument_list|(
name|rgb
operator|->
name|r
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
operator|*
literal|255.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|g
condition|)
operator|*
name|g
operator|=
name|ROUND
argument_list|(
name|CLAMP
argument_list|(
name|rgb
operator|->
name|g
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
operator|*
literal|255.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|b
condition|)
operator|*
name|b
operator|=
name|ROUND
argument_list|(
name|CLAMP
argument_list|(
name|rgb
operator|->
name|b
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
operator|*
literal|255.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgb_add (GimpRGB * rgb1,const GimpRGB * rgb2)
name|gimp_rgb_add
parameter_list|(
name|GimpRGB
modifier|*
name|rgb1
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb2
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|rgb1
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rgb2
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|rgb1
operator|->
name|r
operator|+=
name|rgb2
operator|->
name|r
expr_stmt|;
name|rgb1
operator|->
name|g
operator|+=
name|rgb2
operator|->
name|g
expr_stmt|;
name|rgb1
operator|->
name|b
operator|+=
name|rgb2
operator|->
name|b
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgb_subtract (GimpRGB * rgb1,const GimpRGB * rgb2)
name|gimp_rgb_subtract
parameter_list|(
name|GimpRGB
modifier|*
name|rgb1
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb2
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|rgb1
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rgb2
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|rgb1
operator|->
name|r
operator|-=
name|rgb2
operator|->
name|r
expr_stmt|;
name|rgb1
operator|->
name|g
operator|-=
name|rgb2
operator|->
name|g
expr_stmt|;
name|rgb1
operator|->
name|b
operator|-=
name|rgb2
operator|->
name|b
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgb_multiply (GimpRGB * rgb,gdouble factor)
name|gimp_rgb_multiply
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|gdouble
name|factor
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|rgb
operator|->
name|r
operator|*=
name|factor
expr_stmt|;
name|rgb
operator|->
name|g
operator|*=
name|factor
expr_stmt|;
name|rgb
operator|->
name|b
operator|*=
name|factor
expr_stmt|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_rgb_distance (const GimpRGB * rgb1,const GimpRGB * rgb2)
name|gimp_rgb_distance
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb1
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb2
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|rgb1
operator|!=
name|NULL
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rgb2
operator|!=
name|NULL
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
return|return
operator|(
name|fabs
argument_list|(
name|rgb1
operator|->
name|r
operator|-
name|rgb2
operator|->
name|r
argument_list|)
operator|+
name|fabs
argument_list|(
name|rgb1
operator|->
name|g
operator|-
name|rgb2
operator|->
name|g
argument_list|)
operator|+
name|fabs
argument_list|(
name|rgb1
operator|->
name|b
operator|-
name|rgb2
operator|->
name|b
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_rgb_max (const GimpRGB * rgb)
name|gimp_rgb_max
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|rgb
operator|->
name|r
operator|>
name|rgb
operator|->
name|g
condition|)
return|return
operator|(
name|rgb
operator|->
name|r
operator|>
name|rgb
operator|->
name|b
operator|)
condition|?
name|rgb
operator|->
name|r
else|:
name|rgb
operator|->
name|b
return|;
return|return
operator|(
name|rgb
operator|->
name|g
operator|>
name|rgb
operator|->
name|b
operator|)
condition|?
name|rgb
operator|->
name|g
else|:
name|rgb
operator|->
name|b
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_rgb_min (const GimpRGB * rgb)
name|gimp_rgb_min
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|rgb
operator|->
name|r
operator|<
name|rgb
operator|->
name|g
condition|)
return|return
operator|(
name|rgb
operator|->
name|r
operator|<
name|rgb
operator|->
name|b
operator|)
condition|?
name|rgb
operator|->
name|r
else|:
name|rgb
operator|->
name|b
return|;
return|return
operator|(
name|rgb
operator|->
name|g
operator|<
name|rgb
operator|->
name|b
operator|)
condition|?
name|rgb
operator|->
name|g
else|:
name|rgb
operator|->
name|b
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgb_clamp (GimpRGB * rgb)
name|gimp_rgb_clamp
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|rgb
operator|->
name|r
operator|=
name|CLAMP
argument_list|(
name|rgb
operator|->
name|r
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|rgb
operator|->
name|g
operator|=
name|CLAMP
argument_list|(
name|rgb
operator|->
name|g
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|rgb
operator|->
name|b
operator|=
name|CLAMP
argument_list|(
name|rgb
operator|->
name|b
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|rgb
operator|->
name|a
operator|=
name|CLAMP
argument_list|(
name|rgb
operator|->
name|a
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgb_gamma (GimpRGB * rgb,gdouble gamma)
name|gimp_rgb_gamma
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|gdouble
name|gamma
parameter_list|)
block|{
name|gdouble
name|ig
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gamma
operator|!=
literal|0.0
condition|)
name|ig
operator|=
literal|1.0
operator|/
name|gamma
expr_stmt|;
else|else
name|ig
operator|=
literal|0.0
expr_stmt|;
name|rgb
operator|->
name|r
operator|=
name|pow
argument_list|(
name|rgb
operator|->
name|r
argument_list|,
name|ig
argument_list|)
expr_stmt|;
name|rgb
operator|->
name|g
operator|=
name|pow
argument_list|(
name|rgb
operator|->
name|g
argument_list|,
name|ig
argument_list|)
expr_stmt|;
name|rgb
operator|->
name|b
operator|=
name|pow
argument_list|(
name|rgb
operator|->
name|b
argument_list|,
name|ig
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_rgb_luminance:  * @rgb:  *  * Return value: the luminous intensity of the range from 0.0 to 1.0.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_rgb_luminance (const GimpRGB * rgb)
name|gimp_rgb_luminance
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|gdouble
name|luminance
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|luminance
operator|=
name|GIMP_RGB_LUMINANCE
argument_list|(
name|rgb
operator|->
name|r
argument_list|,
name|rgb
operator|->
name|g
argument_list|,
name|rgb
operator|->
name|b
argument_list|)
expr_stmt|;
return|return
name|CLAMP
argument_list|(
name|luminance
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_rgb_luminance_uchar:  * @rgb:  *  * Return value: the luminous intensity in the range from 0 to 255.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|guchar
DECL|function|gimp_rgb_luminance_uchar (const GimpRGB * rgb)
name|gimp_rgb_luminance_uchar
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|ROUND
argument_list|(
name|gimp_rgb_luminance
argument_list|(
name|rgb
argument_list|)
operator|*
literal|255.0
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_rgb_intensity:  * @rgb:  *  * This function is deprecated! Use gimp_rgb_luminance() instead.  *  * Return value: the intensity in the range from 0.0 to 1.0.  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_rgb_intensity (const GimpRGB * rgb)
name|gimp_rgb_intensity
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|gdouble
name|intensity
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|intensity
operator|=
name|GIMP_RGB_INTENSITY
argument_list|(
name|rgb
operator|->
name|r
argument_list|,
name|rgb
operator|->
name|g
argument_list|,
name|rgb
operator|->
name|b
argument_list|)
expr_stmt|;
return|return
name|CLAMP
argument_list|(
name|intensity
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_rgb_intensity_uchar:  * @rgb:  *  * This function is deprecated! Use gimp_rgb_luminance_uchar() instead.  *  * Return value: the intensity in the range from 0 to 255.  **/
end_comment

begin_function
name|guchar
DECL|function|gimp_rgb_intensity_uchar (const GimpRGB * rgb)
name|gimp_rgb_intensity_uchar
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|ROUND
argument_list|(
name|gimp_rgb_intensity
argument_list|(
name|rgb
argument_list|)
operator|*
literal|255.0
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgb_composite (GimpRGB * color1,const GimpRGB * color2,GimpRGBCompositeMode mode)
name|gimp_rgb_composite
parameter_list|(
name|GimpRGB
modifier|*
name|color1
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color2
parameter_list|,
name|GimpRGBCompositeMode
name|mode
parameter_list|)
block|{
name|gdouble
name|factor
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|color1
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color2
operator|!=
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|mode
condition|)
block|{
case|case
name|GIMP_RGB_COMPOSITE_NONE
case|:
break|break;
case|case
name|GIMP_RGB_COMPOSITE_NORMAL
case|:
comment|/*  put color2 on top of color1  */
if|if
condition|(
name|color2
operator|->
name|a
operator|==
literal|1.0
condition|)
block|{
operator|*
name|color1
operator|=
operator|*
name|color2
expr_stmt|;
block|}
else|else
block|{
name|factor
operator|=
name|color1
operator|->
name|a
operator|*
operator|(
literal|1.0
operator|-
name|color2
operator|->
name|a
operator|)
expr_stmt|;
name|color1
operator|->
name|r
operator|=
name|color1
operator|->
name|r
operator|*
name|factor
operator|+
name|color2
operator|->
name|r
operator|*
name|color2
operator|->
name|a
expr_stmt|;
name|color1
operator|->
name|g
operator|=
name|color1
operator|->
name|g
operator|*
name|factor
operator|+
name|color2
operator|->
name|g
operator|*
name|color2
operator|->
name|a
expr_stmt|;
name|color1
operator|->
name|b
operator|=
name|color1
operator|->
name|b
operator|*
name|factor
operator|+
name|color2
operator|->
name|b
operator|*
name|color2
operator|->
name|a
expr_stmt|;
name|color1
operator|->
name|a
operator|=
name|factor
operator|+
name|color2
operator|->
name|a
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RGB_COMPOSITE_BEHIND
case|:
comment|/*  put color2 below color1  */
if|if
condition|(
name|color1
operator|->
name|a
operator|<
literal|1.0
condition|)
block|{
name|factor
operator|=
name|color2
operator|->
name|a
operator|*
operator|(
literal|1.0
operator|-
name|color1
operator|->
name|a
operator|)
expr_stmt|;
name|color1
operator|->
name|r
operator|=
name|color2
operator|->
name|r
operator|*
name|factor
operator|+
name|color1
operator|->
name|r
operator|*
name|color1
operator|->
name|a
expr_stmt|;
name|color1
operator|->
name|g
operator|=
name|color2
operator|->
name|g
operator|*
name|factor
operator|+
name|color1
operator|->
name|g
operator|*
name|color1
operator|->
name|a
expr_stmt|;
name|color1
operator|->
name|b
operator|=
name|color2
operator|->
name|b
operator|*
name|factor
operator|+
name|color1
operator|->
name|b
operator|*
name|color1
operator|->
name|a
expr_stmt|;
name|color1
operator|->
name|a
operator|=
name|factor
operator|+
name|color1
operator|->
name|a
expr_stmt|;
block|}
break|break;
block|}
block|}
end_function

begin_comment
comment|/*  RGBA functions  */
end_comment

begin_comment
comment|/**  * gimp_rgba_set:  * @rgba: a #GimpRGB struct  * @red:  * @green:  * @blue:  * @alpha:  *  * Sets the red, green, blue and alpha components of @rgb. The values  * should be between 0.0 and 1.0 but there is no check to enforce this  * and the values are set exactly as they are passed in.  **/
end_comment

begin_function
name|void
DECL|function|gimp_rgba_set (GimpRGB * rgba,gdouble r,gdouble g,gdouble b,gdouble a)
name|gimp_rgba_set
parameter_list|(
name|GimpRGB
modifier|*
name|rgba
parameter_list|,
name|gdouble
name|r
parameter_list|,
name|gdouble
name|g
parameter_list|,
name|gdouble
name|b
parameter_list|,
name|gdouble
name|a
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|rgba
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|rgba
operator|->
name|r
operator|=
name|r
expr_stmt|;
name|rgba
operator|->
name|g
operator|=
name|g
expr_stmt|;
name|rgba
operator|->
name|b
operator|=
name|b
expr_stmt|;
name|rgba
operator|->
name|a
operator|=
name|a
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_rgba_set_uchar:  * @rgba: a #GimpRGB struct  * @red:  * @green:  * @blue:  * @alpha:  *  * Sets the red, green, blue and alpha components of @rgb from 8bit  * values (0 to 255).  **/
end_comment

begin_function
name|void
DECL|function|gimp_rgba_set_uchar (GimpRGB * rgba,guchar r,guchar g,guchar b,guchar a)
name|gimp_rgba_set_uchar
parameter_list|(
name|GimpRGB
modifier|*
name|rgba
parameter_list|,
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|,
name|guchar
name|a
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|rgba
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|rgba
operator|->
name|r
operator|=
operator|(
name|gdouble
operator|)
name|r
operator|/
literal|255.0
expr_stmt|;
name|rgba
operator|->
name|g
operator|=
operator|(
name|gdouble
operator|)
name|g
operator|/
literal|255.0
expr_stmt|;
name|rgba
operator|->
name|b
operator|=
operator|(
name|gdouble
operator|)
name|b
operator|/
literal|255.0
expr_stmt|;
name|rgba
operator|->
name|a
operator|=
operator|(
name|gdouble
operator|)
name|a
operator|/
literal|255.0
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgba_get_uchar (const GimpRGB * rgba,guchar * r,guchar * g,guchar * b,guchar * a)
name|gimp_rgba_get_uchar
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgba
parameter_list|,
name|guchar
modifier|*
name|r
parameter_list|,
name|guchar
modifier|*
name|g
parameter_list|,
name|guchar
modifier|*
name|b
parameter_list|,
name|guchar
modifier|*
name|a
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|rgba
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
condition|)
operator|*
name|r
operator|=
name|ROUND
argument_list|(
name|CLAMP
argument_list|(
name|rgba
operator|->
name|r
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
operator|*
literal|255.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|g
condition|)
operator|*
name|g
operator|=
name|ROUND
argument_list|(
name|CLAMP
argument_list|(
name|rgba
operator|->
name|g
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
operator|*
literal|255.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|b
condition|)
operator|*
name|b
operator|=
name|ROUND
argument_list|(
name|CLAMP
argument_list|(
name|rgba
operator|->
name|b
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
operator|*
literal|255.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|a
condition|)
operator|*
name|a
operator|=
name|ROUND
argument_list|(
name|CLAMP
argument_list|(
name|rgba
operator|->
name|a
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
operator|*
literal|255.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgba_add (GimpRGB * rgba1,const GimpRGB * rgba2)
name|gimp_rgba_add
parameter_list|(
name|GimpRGB
modifier|*
name|rgba1
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgba2
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|rgba1
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rgba2
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|rgba1
operator|->
name|r
operator|+=
name|rgba2
operator|->
name|r
expr_stmt|;
name|rgba1
operator|->
name|g
operator|+=
name|rgba2
operator|->
name|g
expr_stmt|;
name|rgba1
operator|->
name|b
operator|+=
name|rgba2
operator|->
name|b
expr_stmt|;
name|rgba1
operator|->
name|a
operator|+=
name|rgba2
operator|->
name|a
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgba_subtract (GimpRGB * rgba1,const GimpRGB * rgba2)
name|gimp_rgba_subtract
parameter_list|(
name|GimpRGB
modifier|*
name|rgba1
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgba2
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|rgba1
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rgba2
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|rgba1
operator|->
name|r
operator|-=
name|rgba2
operator|->
name|r
expr_stmt|;
name|rgba1
operator|->
name|g
operator|-=
name|rgba2
operator|->
name|g
expr_stmt|;
name|rgba1
operator|->
name|b
operator|-=
name|rgba2
operator|->
name|b
expr_stmt|;
name|rgba1
operator|->
name|a
operator|-=
name|rgba2
operator|->
name|a
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgba_multiply (GimpRGB * rgba,gdouble factor)
name|gimp_rgba_multiply
parameter_list|(
name|GimpRGB
modifier|*
name|rgba
parameter_list|,
name|gdouble
name|factor
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|rgba
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|rgba
operator|->
name|r
operator|*=
name|factor
expr_stmt|;
name|rgba
operator|->
name|g
operator|*=
name|factor
expr_stmt|;
name|rgba
operator|->
name|b
operator|*=
name|factor
expr_stmt|;
name|rgba
operator|->
name|a
operator|*=
name|factor
expr_stmt|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_rgba_distance (const GimpRGB * rgba1,const GimpRGB * rgba2)
name|gimp_rgba_distance
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgba1
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgba2
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|rgba1
operator|!=
name|NULL
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rgba2
operator|!=
name|NULL
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
return|return
operator|(
name|fabs
argument_list|(
name|rgba1
operator|->
name|r
operator|-
name|rgba2
operator|->
name|r
argument_list|)
operator|+
name|fabs
argument_list|(
name|rgba1
operator|->
name|g
operator|-
name|rgba2
operator|->
name|g
argument_list|)
operator|+
name|fabs
argument_list|(
name|rgba1
operator|->
name|b
operator|-
name|rgba2
operator|->
name|b
argument_list|)
operator|+
name|fabs
argument_list|(
name|rgba1
operator|->
name|a
operator|-
name|rgba2
operator|->
name|a
argument_list|)
operator|)
return|;
block|}
end_function

begin_comment
comment|/*  * GIMP_TYPE_PARAM_RGB  */
end_comment

begin_define
DECL|macro|GIMP_PARAM_SPEC_RGB (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_RGB
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_RGB, GimpParamSpecRGB))
end_define

begin_function_decl
specifier|static
name|void
name|gimp_param_rgb_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_param_rgb_init
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_param_rgb_set_default
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_param_rgb_validate
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_param_rgb_values_cmp
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value1
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value2
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|typedef|GimpParamSpecRGB
typedef|typedef
name|struct
name|_GimpParamSpecRGB
name|GimpParamSpecRGB
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecRGB
struct|struct
name|_GimpParamSpecRGB
block|{
DECL|member|parent_instance
name|GParamSpecBoxed
name|parent_instance
decl_stmt|;
DECL|member|default_value
name|GimpRGB
name|default_value
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/**  * gimp_param_rgb_get_type:  *  * Reveals the object type  *  * Returns: the #GType for a GimpParamRGB object  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|GType
DECL|function|gimp_param_rgb_get_type (void)
name|gimp_param_rgb_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|spec_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|spec_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|type_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GParamSpecClass
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_param_rgb_class_init
block|,
name|NULL
block|,
name|NULL
block|,
sizeof|sizeof
argument_list|(
name|GimpParamSpecRGB
argument_list|)
block|,
literal|0
block|,
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_param_rgb_init
block|}
decl_stmt|;
name|spec_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_PARAM_BOXED
argument_list|,
literal|"GimpParamRGB"
argument_list|,
operator|&
name|type_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|spec_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_rgb_class_init (GParamSpecClass * class)
name|gimp_param_rgb_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
block|{
name|class
operator|->
name|value_type
operator|=
name|GIMP_TYPE_RGB
expr_stmt|;
name|class
operator|->
name|value_set_default
operator|=
name|gimp_param_rgb_set_default
expr_stmt|;
name|class
operator|->
name|value_validate
operator|=
name|gimp_param_rgb_validate
expr_stmt|;
name|class
operator|->
name|values_cmp
operator|=
name|gimp_param_rgb_values_cmp
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_rgb_init (GParamSpec * pspec)
name|gimp_param_rgb_init
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpParamSpecRGB
modifier|*
name|cspec
init|=
name|GIMP_PARAM_SPEC_RGB
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|cspec
operator|->
name|default_value
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_rgb_set_default (GParamSpec * pspec,GValue * value)
name|gimp_param_rgb_set_default
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|GimpParamSpecRGB
modifier|*
name|cspec
init|=
name|GIMP_PARAM_SPEC_RGB
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|g_value_set_static_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|cspec
operator|->
name|default_value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_param_rgb_validate (GParamSpec * pspec,GValue * value)
name|gimp_param_rgb_validate
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|GimpRGB
modifier|*
name|rgb
decl_stmt|;
name|rgb
operator|=
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
expr_stmt|;
if|if
condition|(
name|rgb
condition|)
block|{
name|GimpRGB
name|oval
decl_stmt|;
name|oval
operator|=
operator|*
name|rgb
expr_stmt|;
name|gimp_rgb_clamp
argument_list|(
name|rgb
argument_list|)
expr_stmt|;
return|return
operator|(
name|oval
operator|.
name|r
operator|!=
name|rgb
operator|->
name|r
operator|||
name|oval
operator|.
name|g
operator|!=
name|rgb
operator|->
name|g
operator|||
name|oval
operator|.
name|b
operator|!=
name|rgb
operator|->
name|b
operator|||
name|oval
operator|.
name|a
operator|!=
name|rgb
operator|->
name|a
operator|)
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_param_rgb_values_cmp (GParamSpec * pspec,const GValue * value1,const GValue * value2)
name|gimp_param_rgb_values_cmp
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value1
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value2
parameter_list|)
block|{
name|GimpRGB
modifier|*
name|rgb1
decl_stmt|;
name|GimpRGB
modifier|*
name|rgb2
decl_stmt|;
name|rgb1
operator|=
name|value1
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
expr_stmt|;
name|rgb2
operator|=
name|value2
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
expr_stmt|;
comment|/*  try to return at least *something*, it's useless anyway...  */
if|if
condition|(
operator|!
name|rgb1
condition|)
return|return
name|rgb2
operator|!=
name|NULL
condition|?
operator|-
literal|1
else|:
literal|0
return|;
elseif|else
if|if
condition|(
operator|!
name|rgb2
condition|)
return|return
name|rgb1
operator|!=
name|NULL
return|;
else|else
block|{
name|guint32
name|int1
decl_stmt|,
name|int2
decl_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
name|rgb1
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int1
operator|)
operator|+
literal|0
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int1
operator|)
operator|+
literal|1
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int1
operator|)
operator|+
literal|2
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int1
operator|)
operator|+
literal|3
argument_list|)
expr_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
name|rgb2
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int2
operator|)
operator|+
literal|0
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int2
operator|)
operator|+
literal|1
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int2
operator|)
operator|+
literal|2
argument_list|,
operator|(
operator|(
name|guchar
operator|*
operator|)
operator|&
name|int2
operator|)
operator|+
literal|3
argument_list|)
expr_stmt|;
return|return
name|int1
operator|-
name|int2
return|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_param_spec_rgb:  * @name:          Canonical name of the param  * @nick:          Nickname of the param  * @blurb:         Brief desciption of param.  * @default_value: Value to use if none is assigned.  * @flags:         a combination of #GParamFlags  *  * Creates a param spec to hold an #GimpRGB value.  * See g_param_spec_internal() for more information.  *  * Returns: a newly allocated #GParamSpec instance  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|GParamSpec
modifier|*
DECL|function|gimp_param_spec_rgb (const gchar * name,const gchar * nick,const gchar * blurb,const GimpRGB * default_value,GParamFlags flags)
name|gimp_param_spec_rgb
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GimpParamSpecRGB
modifier|*
name|cspec
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|default_value
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cspec
operator|=
name|g_param_spec_internal
argument_list|(
name|GIMP_TYPE_PARAM_RGB
argument_list|,
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|cspec
operator|->
name|default_value
operator|=
operator|*
name|default_value
expr_stmt|;
return|return
name|G_PARAM_SPEC
argument_list|(
name|cspec
argument_list|)
return|;
block|}
end_function

end_unit

