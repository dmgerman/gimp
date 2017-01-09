begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimplayermodefunctions.c  * Copyright (C) 2013 Daniel Sabo<DanielSabo@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimplayermodefunctions.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes/gimpoperationnormal.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationdissolvemode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationbehindmode.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes/gimpoperationmultiply.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationmultiplylegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes/gimpoperationscreen.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationscreenlegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes/gimpoperationoverlay.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationdifferencemode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationadditionmode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationsubtractmode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationdarkenonlymode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlightenonlymode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationhuemode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationsaturationmode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcolormode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationvaluemode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationdividemode.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes/gimpoperationdodge.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationdodgelegacy.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationburnmode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationhardlightmode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationsoftlightmode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationgrainextractmode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationgrainmergemode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcolorerasemode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlchhuemode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlchchromamode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlchcolormode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlchlightnessmode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationerasemode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationreplacemode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationantierasemode.h"
end_include

begin_function
name|GimpLayerModeFunction
DECL|function|get_layer_mode_function (GimpLayerMode paint_mode,gboolean linear_mode)
name|get_layer_mode_function
parameter_list|(
name|GimpLayerMode
name|paint_mode
parameter_list|,
name|gboolean
name|linear_mode
parameter_list|)
block|{
name|GimpLayerModeFunction
name|func
init|=
name|gimp_operation_normal_process_pixels
decl_stmt|;
switch|switch
condition|(
name|paint_mode
condition|)
block|{
case|case
name|GIMP_LAYER_MODE_NORMAL
case|:
name|func
operator|=
name|gimp_operation_normal_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_DISSOLVE
case|:
name|func
operator|=
name|gimp_operation_dissolve_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_BEHIND
case|:
name|func
operator|=
name|gimp_operation_behind_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_MULTIPLY_LEGACY
case|:
name|func
operator|=
name|gimp_operation_multiply_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_MULTIPLY
case|:
name|func
operator|=
name|gimp_operation_multiply_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_SCREEN_LEGACY
case|:
name|func
operator|=
name|gimp_operation_screen_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_SCREEN
case|:
name|func
operator|=
name|gimp_operation_screen_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_OVERLAY_LEGACY
case|:
name|func
operator|=
name|gimp_operation_softlight_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_DIFFERENCE_LEGACY
case|:
name|func
operator|=
name|gimp_operation_difference_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_ADDITION_LEGACY
case|:
name|func
operator|=
name|gimp_operation_addition_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_SUBTRACT_LEGACY
case|:
name|func
operator|=
name|gimp_operation_subtract_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
case|:
name|func
operator|=
name|gimp_operation_darken_only_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
case|:
name|func
operator|=
name|gimp_operation_lighten_only_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HSV_HUE_LEGACY
case|:
name|func
operator|=
name|gimp_operation_hue_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
case|:
name|func
operator|=
name|gimp_operation_saturation_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HSV_COLOR_LEGACY
case|:
name|func
operator|=
name|gimp_operation_color_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
case|:
name|func
operator|=
name|gimp_operation_value_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_DIVIDE_LEGACY
case|:
name|func
operator|=
name|gimp_operation_divide_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_DODGE
case|:
name|func
operator|=
name|gimp_operation_dodge_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_DODGE_LEGACY
case|:
name|func
operator|=
name|gimp_operation_dodge_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_BURN_LEGACY
case|:
name|func
operator|=
name|gimp_operation_burn_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
case|:
name|func
operator|=
name|gimp_operation_hardlight_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
case|:
name|func
operator|=
name|gimp_operation_softlight_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
case|:
name|func
operator|=
name|gimp_operation_grain_extract_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
case|:
name|func
operator|=
name|gimp_operation_grain_merge_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_COLOR_ERASE
case|:
name|func
operator|=
name|gimp_operation_color_erase_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_OVERLAY
case|:
name|func
operator|=
name|gimp_operation_overlay_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_LCH_HUE
case|:
name|func
operator|=
name|linear_mode
condition|?
name|gimp_operation_lch_hue_mode_process_pixels_linear
else|:
name|gimp_operation_lch_hue_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_LCH_CHROMA
case|:
name|func
operator|=
name|linear_mode
condition|?
name|gimp_operation_lch_chroma_mode_process_pixels_linear
else|:
name|gimp_operation_lch_chroma_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_LCH_COLOR
case|:
name|func
operator|=
name|linear_mode
condition|?
name|gimp_operation_lch_color_mode_process_pixels_linear
else|:
name|gimp_operation_lch_color_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_LCH_LIGHTNESS
case|:
name|func
operator|=
name|linear_mode
condition|?
name|gimp_operation_lch_lightness_mode_process_pixels_linear
else|:
name|gimp_operation_lch_lightness_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_ERASE
case|:
name|func
operator|=
name|gimp_operation_erase_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_REPLACE
case|:
name|func
operator|=
name|gimp_operation_replace_mode_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_ANTI_ERASE
case|:
name|func
operator|=
name|gimp_operation_anti_erase_mode_process_pixels
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"No direct function for layer mode (%d), using gimp:normal-mode"
argument_list|,
name|paint_mode
argument_list|)
expr_stmt|;
name|func
operator|=
name|gimp_operation_normal_process_pixels
expr_stmt|;
break|break;
block|}
return|return
name|func
return|;
block|}
end_function

end_unit

