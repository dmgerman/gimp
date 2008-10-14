begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl-utils.h  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-utils.h"
end_include

begin_comment
comment|/**  * gimp_bpp_to_babl_format:  * @bpp: bytes per pixel  * @linear: whether the pixels are linear or gamma-corrected.  *  * Return the Babl format to use for a given number of bytes per pixel.  * This function assumes that the data is 8bit.  *  * Return value: the Babl format to use  **/
end_comment

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_bpp_to_babl_format (guint bpp,gboolean linear)
name|gimp_bpp_to_babl_format
parameter_list|(
name|guint
name|bpp
parameter_list|,
name|gboolean
name|linear
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|bpp
operator|>
literal|0
operator|&&
name|bpp
operator|<=
literal|4
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|linear
condition|)
block|{
switch|switch
condition|(
name|bpp
condition|)
block|{
case|case
literal|1
case|:
return|return
name|babl_format
argument_list|(
literal|"Y u8"
argument_list|)
return|;
case|case
literal|2
case|:
return|return
name|babl_format
argument_list|(
literal|"YA u8"
argument_list|)
return|;
case|case
literal|3
case|:
return|return
name|babl_format
argument_list|(
literal|"RGB u8"
argument_list|)
return|;
case|case
literal|4
case|:
return|return
name|babl_format
argument_list|(
literal|"RGBA u8"
argument_list|)
return|;
block|}
block|}
else|else
block|{
switch|switch
condition|(
name|bpp
condition|)
block|{
case|case
literal|1
case|:
return|return
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
return|;
case|case
literal|2
case|:
return|return
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
return|;
case|case
literal|3
case|:
return|return
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
return|;
case|case
literal|4
case|:
return|return
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
return|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_layer_mode_to_gegl_operation (GimpLayerModeEffects mode)
name|gimp_layer_mode_to_gegl_operation
parameter_list|(
name|GimpLayerModeEffects
name|mode
parameter_list|)
block|{
switch|switch
condition|(
name|mode
condition|)
block|{
case|case
name|GIMP_NORMAL_MODE
case|:
return|return
literal|"gegl:normal"
return|;
case|case
name|GIMP_DISSOLVE_MODE
case|:
return|return
literal|"gimp-dissolve-mode"
return|;
case|case
name|GIMP_BEHIND_MODE
case|:
return|return
literal|"gimp-behind-mode"
return|;
case|case
name|GIMP_MULTIPLY_MODE
case|:
return|return
literal|"gimp-multiply-mode"
return|;
case|case
name|GIMP_SCREEN_MODE
case|:
return|return
literal|"gimp-screen-mode"
return|;
case|case
name|GIMP_OVERLAY_MODE
case|:
return|return
literal|"gimp-overlay-mode"
return|;
case|case
name|GIMP_DIFFERENCE_MODE
case|:
return|return
literal|"gimp-difference-mode"
return|;
case|case
name|GIMP_ADDITION_MODE
case|:
return|return
literal|"gimp-addition-mode"
return|;
case|case
name|GIMP_SUBTRACT_MODE
case|:
return|return
literal|"gimp-subtract-mode"
return|;
case|case
name|GIMP_DARKEN_ONLY_MODE
case|:
return|return
literal|"gimp-darken-mode"
return|;
case|case
name|GIMP_LIGHTEN_ONLY_MODE
case|:
return|return
literal|"gimp-lighten-mode"
return|;
case|case
name|GIMP_HUE_MODE
case|:
return|return
literal|"gimp-hue-mode"
return|;
case|case
name|GIMP_SATURATION_MODE
case|:
return|return
literal|"gimp-saturation-mode"
return|;
case|case
name|GIMP_COLOR_MODE
case|:
return|return
literal|"gimp-color-mode"
return|;
case|case
name|GIMP_VALUE_MODE
case|:
return|return
literal|"gimp-value-mode"
return|;
case|case
name|GIMP_DIVIDE_MODE
case|:
return|return
literal|"gimp-divide-mode"
return|;
case|case
name|GIMP_DODGE_MODE
case|:
return|return
literal|"gimp-dodge-mode"
return|;
case|case
name|GIMP_BURN_MODE
case|:
return|return
literal|"gimp-burn-mode"
return|;
case|case
name|GIMP_HARDLIGHT_MODE
case|:
return|return
literal|"gimp-hardlight-mode"
return|;
case|case
name|GIMP_SOFTLIGHT_MODE
case|:
return|return
literal|"gimp-softlight-mode"
return|;
case|case
name|GIMP_GRAIN_EXTRACT_MODE
case|:
return|return
literal|"gimp-grain-extract-mode"
return|;
case|case
name|GIMP_GRAIN_MERGE_MODE
case|:
return|return
literal|"gimp-grain-merge-mode"
return|;
case|case
name|GIMP_COLOR_ERASE_MODE
case|:
return|return
literal|"gimp-color-erase-mode"
return|;
case|case
name|GIMP_ERASE_MODE
case|:
return|return
literal|"gimp-erase-mode"
return|;
case|case
name|GIMP_REPLACE_MODE
case|:
return|return
literal|"gimp-replace-mode"
return|;
case|case
name|GIMP_ANTI_ERASE_MODE
case|:
return|return
literal|"gimp-anti-erase-mode"
return|;
default|default:
break|break;
block|}
return|return
literal|"gegl:normal"
return|;
block|}
end_function

end_unit

