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
file|"../operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimplayermodefunctions.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationadditionlegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationburnlegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationdarkenonlylegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationdifferencelegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationdividelegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationdodgelegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationgrainextractlegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationgrainmergelegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationhardlightlegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationhsvcolorlegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationhsvhuelegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationhsvsaturationlegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationhsvvaluelegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationlightenonlylegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationmultiplylegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationscreenlegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationsoftlightlegacy.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes-legacy/gimpoperationsubtractlegacy.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationaddition.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationantierase.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationbehind.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationburn.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcolorerase.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationdarkenonly.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationdifference.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationdissolve.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationdivide.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationdodge.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationerase.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationgrainextract.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationgrainmerge.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationhardlight.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationhsvcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationhsvhue.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationhsvsaturation.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationhsvvalue.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlchchroma.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlchcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlchhue.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlchlightness.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlightenonly.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationmultiply.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationnormal.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationoverlay.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationreplace.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationscreen.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationsoftlight.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationsubtract.h"
end_include

begin_function
name|GimpLayerModeFunc
DECL|function|gimp_get_layer_mode_function (GimpLayerMode paint_mode)
name|gimp_get_layer_mode_function
parameter_list|(
name|GimpLayerMode
name|paint_mode
parameter_list|)
block|{
name|GimpLayerModeFunc
name|func
decl_stmt|;
switch|switch
condition|(
name|paint_mode
condition|)
block|{
case|case
name|GIMP_LAYER_MODE_NORMAL
case|:
case|case
name|GIMP_LAYER_MODE_NORMAL_NON_LINEAR
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
name|gimp_operation_dissolve_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_BEHIND
case|:
case|case
name|GIMP_LAYER_MODE_BEHIND_LINEAR
case|:
name|func
operator|=
name|gimp_operation_behind_process_pixels
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
case|case
name|GIMP_LAYER_MODE_MULTIPLY_LINEAR
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
name|gimp_operation_softlight_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_DIFFERENCE_LEGACY
case|:
name|func
operator|=
name|gimp_operation_difference_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_DIFFERENCE
case|:
case|case
name|GIMP_LAYER_MODE_DIFFERENCE_LINEAR
case|:
name|func
operator|=
name|gimp_operation_difference_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_ADDITION_LEGACY
case|:
name|func
operator|=
name|gimp_operation_addition_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_ADDITION
case|:
case|case
name|GIMP_LAYER_MODE_ADDITION_LINEAR
case|:
name|func
operator|=
name|gimp_operation_addition_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_SUBTRACT_LEGACY
case|:
name|func
operator|=
name|gimp_operation_subtract_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_SUBTRACT
case|:
case|case
name|GIMP_LAYER_MODE_SUBTRACT_LINEAR
case|:
name|func
operator|=
name|gimp_operation_subtract_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
case|:
name|func
operator|=
name|gimp_operation_darken_only_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_DARKEN_ONLY
case|:
case|case
name|GIMP_LAYER_MODE_DARKEN_ONLY_LINEAR
case|:
name|func
operator|=
name|gimp_operation_darken_only_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
case|:
name|func
operator|=
name|gimp_operation_lighten_only_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_LIGHTEN_ONLY
case|:
case|case
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LINEAR
case|:
name|func
operator|=
name|gimp_operation_lighten_only_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HSV_HUE
case|:
name|func
operator|=
name|gimp_operation_hsv_hue_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HSV_HUE_LEGACY
case|:
name|func
operator|=
name|gimp_operation_hsv_hue_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HSV_SATURATION
case|:
name|func
operator|=
name|gimp_operation_hsv_saturation_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
case|:
name|func
operator|=
name|gimp_operation_hsv_saturation_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HSV_COLOR
case|:
name|func
operator|=
name|gimp_operation_hsv_color_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HSV_COLOR_LEGACY
case|:
name|func
operator|=
name|gimp_operation_hsv_color_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HSV_VALUE
case|:
name|func
operator|=
name|gimp_operation_hsv_value_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
case|:
name|func
operator|=
name|gimp_operation_hsv_value_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_DIVIDE_LEGACY
case|:
name|func
operator|=
name|gimp_operation_divide_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_DIVIDE
case|:
case|case
name|GIMP_LAYER_MODE_DIVIDE_LINEAR
case|:
name|func
operator|=
name|gimp_operation_divide_process_pixels
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
name|GIMP_LAYER_MODE_DODGE
case|:
case|case
name|GIMP_LAYER_MODE_DODGE_LINEAR
case|:
name|func
operator|=
name|gimp_operation_dodge_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_BURN_LEGACY
case|:
name|func
operator|=
name|gimp_operation_burn_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_BURN
case|:
case|case
name|GIMP_LAYER_MODE_BURN_LINEAR
case|:
name|func
operator|=
name|gimp_operation_burn_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
case|:
name|func
operator|=
name|gimp_operation_hardlight_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_HARDLIGHT
case|:
name|func
operator|=
name|gimp_operation_hardlight_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
case|:
name|func
operator|=
name|gimp_operation_softlight_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_SOFTLIGHT
case|:
name|func
operator|=
name|gimp_operation_softlight_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
case|:
name|func
operator|=
name|gimp_operation_grain_extract_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_GRAIN_EXTRACT
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LINEAR
case|:
name|func
operator|=
name|gimp_operation_grain_extract_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
case|:
name|func
operator|=
name|gimp_operation_grain_merge_legacy_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_GRAIN_MERGE
case|:
case|case
name|GIMP_LAYER_MODE_GRAIN_MERGE_LINEAR
case|:
name|func
operator|=
name|gimp_operation_grain_merge_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_COLOR_ERASE
case|:
name|func
operator|=
name|gimp_operation_color_erase_process_pixels
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
name|gimp_operation_lch_hue_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_LCH_CHROMA
case|:
name|func
operator|=
name|gimp_operation_lch_chroma_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_LCH_COLOR
case|:
name|func
operator|=
name|gimp_operation_lch_color_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_LCH_LIGHTNESS
case|:
name|func
operator|=
name|gimp_operation_lch_lightness_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_ERASE
case|:
name|func
operator|=
name|gimp_operation_erase_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_REPLACE
case|:
name|func
operator|=
name|gimp_operation_replace_process_pixels
expr_stmt|;
break|break;
case|case
name|GIMP_LAYER_MODE_ANTI_ERASE
case|:
name|func
operator|=
name|gimp_operation_anti_erase_process_pixels
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"No direct function for layer mode (%d), using gimp:normal"
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

