begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-layer-modes.c  * Copyright (C) 2017 Michael Natterer<mitch@gimp.org>  *                    Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-layer-modes.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_layer_mode_is_legacy (GimpLayerMode mode)
name|gimp_layer_mode_is_legacy
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
block|{
switch|switch
condition|(
name|mode
condition|)
block|{
case|case
name|GIMP_LAYER_MODE_MULTIPLY_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_SCREEN_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_OVERLAY_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_DIFFERENCE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_ADDITION_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_SUBTRACT_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HSV_HUE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HSV_COLOR_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_DIVIDE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_DODGE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_BURN_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
case|:
return|return
name|TRUE
return|;
default|default:
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_layer_mode_is_linear (GimpLayerMode mode)
name|gimp_layer_mode_is_linear
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
block|{
switch|switch
condition|(
name|mode
condition|)
block|{
case|case
name|GIMP_LAYER_MODE_NORMAL_NON_LINEAR
case|:
return|return
name|FALSE
return|;
case|case
name|GIMP_LAYER_MODE_DISSOLVE
case|:
return|return
name|TRUE
return|;
case|case
name|GIMP_LAYER_MODE_BEHIND
case|:
return|return
name|FALSE
return|;
case|case
name|GIMP_LAYER_MODE_MULTIPLY_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_SCREEN_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_OVERLAY_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_DIFFERENCE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_ADDITION_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_SUBTRACT_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HSV_HUE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HSV_COLOR_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_DIVIDE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_DODGE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_BURN_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
case|:
return|return
name|FALSE
return|;
case|case
name|GIMP_LAYER_MODE_COLOR_ERASE
case|:
case|case
name|GIMP_LAYER_MODE_OVERLAY
case|:
case|case
name|GIMP_LAYER_MODE_LCH_HUE
case|:
case|case
name|GIMP_LAYER_MODE_LCH_CHROMA
case|:
case|case
name|GIMP_LAYER_MODE_LCH_COLOR
case|:
case|case
name|GIMP_LAYER_MODE_LCH_LIGHTNESS
case|:
return|return
name|FALSE
return|;
case|case
name|GIMP_LAYER_MODE_NORMAL
case|:
return|return
name|TRUE
return|;
case|case
name|GIMP_LAYER_MODE_MULTIPLY
case|:
case|case
name|GIMP_LAYER_MODE_SCREEN
case|:
case|case
name|GIMP_LAYER_MODE_DIFFERENCE
case|:
case|case
name|GIMP_LAYER_MODE_ADDITION
case|:
case|case
name|GIMP_LAYER_MODE_SUBTRACT
case|:
case|case
name|GIMP_LAYER_MODE_DARKEN_ONLY
case|:
case|case
name|GIMP_LAYER_MODE_LIGHTEN_ONLY
case|:
case|case
name|GIMP_LAYER_MODE_HSV_HUE
case|:
case|case
name|GIMP_LAYER_MODE_HSV_SATURATION
case|:
case|case
name|GIMP_LAYER_MODE_HSV_COLOR
case|:
case|case
name|GIMP_LAYER_MODE_HSV_VALUE
case|:
case|case
name|GIMP_LAYER_MODE_DIVIDE
case|:
case|case
name|GIMP_LAYER_MODE_DODGE
case|:
case|case
name|GIMP_LAYER_MODE_BURN
case|:
case|case
name|GIMP_LAYER_MODE_HARDLIGHT
case|:
case|case
name|GIMP_LAYER_MODE_SOFTLIGHT
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_EXTRACT
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_MERGE
case|:
return|return
name|FALSE
return|;
case|case
name|GIMP_LAYER_MODE_BEHIND_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_MULTIPLY_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_SCREEN_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_OVERLAY_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_DIFFERENCE_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_ADDITION_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_SUBTRACT_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_DARKEN_ONLY_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_DIVIDE_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_DODGE_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_BURN_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_HARDLIGHT_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_SOFTLIGHT_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_MERGE_LINEAR
case|:
return|return
name|TRUE
return|;
case|case
name|GIMP_LAYER_MODE_ERASE
case|:
return|return
name|TRUE
return|;
case|case
name|GIMP_LAYER_MODE_REPLACE
case|:
return|return
name|FALSE
return|;
case|case
name|GIMP_LAYER_MODE_ANTI_ERASE
case|:
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|GimpLayerBlendTRC
DECL|function|gimp_layer_mode_get_blend_trc (GimpLayerMode mode)
name|gimp_layer_mode_get_blend_trc
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
block|{
switch|switch
condition|(
name|mode
condition|)
block|{
case|case
name|GIMP_LAYER_MODE_NORMAL_NON_LINEAR
case|:
return|return
name|GIMP_LAYER_BLEND_RGB_PERCEPTUAL
return|;
case|case
name|GIMP_LAYER_MODE_DISSOLVE
case|:
return|return
name|GIMP_LAYER_BLEND_RGB_LINEAR
return|;
case|case
name|GIMP_LAYER_MODE_BEHIND
case|:
return|return
name|GIMP_LAYER_BLEND_RGB_PERCEPTUAL
return|;
case|case
name|GIMP_LAYER_MODE_MULTIPLY_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_SCREEN_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_OVERLAY_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_DIFFERENCE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_ADDITION_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_SUBTRACT_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HSV_HUE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HSV_COLOR_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_DIVIDE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_DODGE_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_BURN_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
case|:
return|return
name|FALSE
return|;
case|case
name|GIMP_LAYER_MODE_COLOR_ERASE
case|:
case|case
name|GIMP_LAYER_MODE_OVERLAY
case|:
return|return
name|GIMP_LAYER_BLEND_RGB_PERCEPTUAL
return|;
case|case
name|GIMP_LAYER_MODE_LCH_HUE
case|:
case|case
name|GIMP_LAYER_MODE_LCH_CHROMA
case|:
case|case
name|GIMP_LAYER_MODE_LCH_COLOR
case|:
case|case
name|GIMP_LAYER_MODE_LCH_LIGHTNESS
case|:
return|return
name|GIMP_LAYER_BLEND_LAB
return|;
case|case
name|GIMP_LAYER_MODE_NORMAL
case|:
return|return
name|GIMP_LAYER_BLEND_RGB_LINEAR
return|;
case|case
name|GIMP_LAYER_MODE_MULTIPLY
case|:
case|case
name|GIMP_LAYER_MODE_SCREEN
case|:
case|case
name|GIMP_LAYER_MODE_DIFFERENCE
case|:
case|case
name|GIMP_LAYER_MODE_ADDITION
case|:
case|case
name|GIMP_LAYER_MODE_SUBTRACT
case|:
case|case
name|GIMP_LAYER_MODE_DARKEN_ONLY
case|:
case|case
name|GIMP_LAYER_MODE_LIGHTEN_ONLY
case|:
case|case
name|GIMP_LAYER_MODE_HSV_HUE
case|:
case|case
name|GIMP_LAYER_MODE_HSV_SATURATION
case|:
case|case
name|GIMP_LAYER_MODE_HSV_COLOR
case|:
case|case
name|GIMP_LAYER_MODE_HSV_VALUE
case|:
case|case
name|GIMP_LAYER_MODE_DIVIDE
case|:
case|case
name|GIMP_LAYER_MODE_DODGE
case|:
case|case
name|GIMP_LAYER_MODE_BURN
case|:
case|case
name|GIMP_LAYER_MODE_HARDLIGHT
case|:
case|case
name|GIMP_LAYER_MODE_SOFTLIGHT
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_EXTRACT
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_MERGE
case|:
return|return
name|GIMP_LAYER_BLEND_RGB_PERCEPTUAL
return|;
case|case
name|GIMP_LAYER_MODE_BEHIND_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_MULTIPLY_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_SCREEN_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_OVERLAY_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_DIFFERENCE_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_ADDITION_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_SUBTRACT_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_DARKEN_ONLY_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_DIVIDE_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_DODGE_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_BURN_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_HARDLIGHT_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_SOFTLIGHT_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_MERGE_LINEAR
case|:
return|return
name|GIMP_LAYER_BLEND_RGB_LINEAR
return|;
case|case
name|GIMP_LAYER_MODE_ERASE
case|:
return|return
name|GIMP_LAYER_BLEND_RGB_LINEAR
return|;
case|case
name|GIMP_LAYER_MODE_REPLACE
case|:
return|return
name|GIMP_LAYER_BLEND_RGB_PERCEPTUAL
return|;
case|case
name|GIMP_LAYER_MODE_ANTI_ERASE
case|:
return|return
name|GIMP_LAYER_BLEND_RGB_LINEAR
return|;
block|}
return|return
name|GIMP_LAYER_BLEND_RGB_LINEAR
return|;
block|}
end_function

begin_function
name|GimpLayerBlendTRC
DECL|function|gimp_layer_mode_get_composite_trc (GimpLayerMode mode)
name|gimp_layer_mode_get_composite_trc
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
block|{
return|return
name|GIMP_LAYER_BLEND_RGB_LINEAR
return|;
block|}
end_function

begin_function
name|GimpLayerCompositeMode
DECL|function|gimp_layer_mode_get_composite_mode (GimpLayerMode mode)
name|gimp_layer_mode_get_composite_mode
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
block|{
return|return
name|GIMP_LAYER_COMPOSITE_SRC_OVER
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_layer_mode_get_operation (GimpLayerMode mode)
name|gimp_layer_mode_get_operation
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
block|{
switch|switch
condition|(
name|mode
condition|)
block|{
case|case
name|GIMP_LAYER_MODE_NORMAL_NON_LINEAR
case|:
case|case
name|GIMP_LAYER_MODE_NORMAL
case|:
return|return
literal|"gimp:normal"
return|;
case|case
name|GIMP_LAYER_MODE_DISSOLVE
case|:
return|return
literal|"gimp:dissolve"
return|;
case|case
name|GIMP_LAYER_MODE_BEHIND
case|:
case|case
name|GIMP_LAYER_MODE_BEHIND_LINEAR
case|:
return|return
literal|"gimp:behind"
return|;
case|case
name|GIMP_LAYER_MODE_MULTIPLY_LEGACY
case|:
return|return
literal|"gimp:multiply-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_MULTIPLY
case|:
case|case
name|GIMP_LAYER_MODE_MULTIPLY_LINEAR
case|:
return|return
literal|"gimp:multiply"
return|;
case|case
name|GIMP_LAYER_MODE_SCREEN_LEGACY
case|:
return|return
literal|"gimp:screen-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_SCREEN
case|:
case|case
name|GIMP_LAYER_MODE_SCREEN_LINEAR
case|:
return|return
literal|"gimp:screen"
return|;
case|case
name|GIMP_LAYER_MODE_OVERLAY_LEGACY
case|:
return|return
literal|"gimp:softlight-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_OVERLAY
case|:
case|case
name|GIMP_LAYER_MODE_OVERLAY_LINEAR
case|:
return|return
literal|"gimp:overlay"
return|;
case|case
name|GIMP_LAYER_MODE_DIFFERENCE_LEGACY
case|:
return|return
literal|"gimp:difference-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_DIFFERENCE
case|:
case|case
name|GIMP_LAYER_MODE_DIFFERENCE_LINEAR
case|:
return|return
literal|"gimp:difference"
return|;
case|case
name|GIMP_LAYER_MODE_ADDITION_LEGACY
case|:
return|return
literal|"gimp:addition-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_ADDITION
case|:
case|case
name|GIMP_LAYER_MODE_ADDITION_LINEAR
case|:
return|return
literal|"gimp:addition"
return|;
case|case
name|GIMP_LAYER_MODE_SUBTRACT_LEGACY
case|:
return|return
literal|"gimp:subtract-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_SUBTRACT
case|:
case|case
name|GIMP_LAYER_MODE_SUBTRACT_LINEAR
case|:
return|return
literal|"gimp:subtract"
return|;
case|case
name|GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
case|:
return|return
literal|"gimp:darken-only-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_DARKEN_ONLY
case|:
case|case
name|GIMP_LAYER_MODE_DARKEN_ONLY_LINEAR
case|:
return|return
literal|"gimp:darken-only"
return|;
case|case
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
case|:
return|return
literal|"gimp:lighten-only-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_LIGHTEN_ONLY
case|:
case|case
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LINEAR
case|:
return|return
literal|"gimp:lighten-only"
return|;
case|case
name|GIMP_LAYER_MODE_HSV_HUE_LEGACY
case|:
return|return
literal|"gimp:hsv-hue-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_HSV_HUE
case|:
return|return
literal|"gimp:hsv-hue"
return|;
case|case
name|GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
case|:
return|return
literal|"gimp:hsv-saturation-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_HSV_SATURATION
case|:
return|return
literal|"gimp:hsv-saturation"
return|;
case|case
name|GIMP_LAYER_MODE_HSV_COLOR_LEGACY
case|:
return|return
literal|"gimp:hsv-color-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_HSV_COLOR
case|:
return|return
literal|"gimp:hsv-color"
return|;
case|case
name|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
case|:
return|return
literal|"gimp:hsv-value-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_HSV_VALUE
case|:
return|return
literal|"gimp:hsv-value"
return|;
case|case
name|GIMP_LAYER_MODE_DIVIDE_LEGACY
case|:
return|return
literal|"gimp:divide-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_DIVIDE
case|:
case|case
name|GIMP_LAYER_MODE_DIVIDE_LINEAR
case|:
return|return
literal|"gimp:divide"
return|;
case|case
name|GIMP_LAYER_MODE_DODGE_LEGACY
case|:
return|return
literal|"gimp:dodge-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_DODGE
case|:
case|case
name|GIMP_LAYER_MODE_DODGE_LINEAR
case|:
return|return
literal|"gimp:dodge"
return|;
case|case
name|GIMP_LAYER_MODE_BURN_LEGACY
case|:
return|return
literal|"gimp:burn-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_BURN
case|:
case|case
name|GIMP_LAYER_MODE_BURN_LINEAR
case|:
return|return
literal|"gimp:burn"
return|;
case|case
name|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
case|:
return|return
literal|"gimp:hardlight-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_HARDLIGHT
case|:
case|case
name|GIMP_LAYER_MODE_HARDLIGHT_LINEAR
case|:
return|return
literal|"gimp:hardlight"
return|;
case|case
name|GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
case|:
return|return
literal|"gimp:softlight-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_SOFTLIGHT
case|:
case|case
name|GIMP_LAYER_MODE_SOFTLIGHT_LINEAR
case|:
return|return
literal|"gimp:softlight"
return|;
case|case
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
case|:
return|return
literal|"gimp:grain-extract-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_GRAIN_EXTRACT
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LINEAR
case|:
return|return
literal|"gimp:grain-extract"
return|;
case|case
name|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
case|:
return|return
literal|"gimp:grain-merge-legacy"
return|;
case|case
name|GIMP_LAYER_MODE_GRAIN_MERGE
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_MERGE_LINEAR
case|:
return|return
literal|"gimp:grain-merge"
return|;
case|case
name|GIMP_LAYER_MODE_COLOR_ERASE
case|:
return|return
literal|"gimp:color-erase"
return|;
case|case
name|GIMP_LAYER_MODE_LCH_HUE
case|:
return|return
literal|"gimp:lch-hue"
return|;
case|case
name|GIMP_LAYER_MODE_LCH_CHROMA
case|:
return|return
literal|"gimp:lch-chroma"
return|;
case|case
name|GIMP_LAYER_MODE_LCH_COLOR
case|:
return|return
literal|"gimp:lch-color"
return|;
case|case
name|GIMP_LAYER_MODE_LCH_LIGHTNESS
case|:
return|return
literal|"gimp:lch-lightness"
return|;
case|case
name|GIMP_LAYER_MODE_ERASE
case|:
return|return
literal|"gimp:erase"
return|;
case|case
name|GIMP_LAYER_MODE_REPLACE
case|:
return|return
literal|"gimp:replace"
return|;
case|case
name|GIMP_LAYER_MODE_ANTI_ERASE
case|:
return|return
literal|"gimp:anti-erase"
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

