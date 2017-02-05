begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-operations.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-operations.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationblend.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationborder.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcagecoefcalc.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcagetransform.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcomposecrop.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationequalize.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationflood.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationgrow.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationhistogramsink.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationmaskcomponents.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationprofiletransform.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationscalarmultiply.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationsemiflatten.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationsetalpha.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationshapeburst.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationshrink.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationthresholdalpha.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationbrightnesscontrast.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcolorbalance.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcolorize.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcurves.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationdesaturate.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationhuesaturation.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlevels.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationposterize.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationthreshold.h"
end_include

begin_include
include|#
directive|include
file|"gimp-operation-config.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrightnesscontrastconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorbalanceconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorizeconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpcurvesconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimphuesaturationconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimplevelsconfig.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationadditionlegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationburnlegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationdarkenonlylegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationdifferencelegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationdividelegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationdodgelegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationgrainextractlegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationgrainmergelegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationhardlightlegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationhsvcolorlegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationhsvhuelegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationhsvsaturationlegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationhsvvaluelegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationlightenonlylegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationmultiplylegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationscreenlegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationsoftlightlegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes-legacy/gimpoperationsubtractlegacy.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes/gimp-layer-modes.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes/gimpoperationantierase.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes/gimpoperationbehind.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes/gimpoperationerase.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes/gimpoperationcolorerase.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes/gimpoperationdissolve.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes/gimpoperationnormal.h"
end_include

begin_include
include|#
directive|include
file|"layer-modes/gimpoperationreplace.h"
end_include

begin_function
name|void
DECL|function|gimp_operations_init (void)
name|gimp_operations_init
parameter_list|(
name|void
parameter_list|)
block|{
name|gimp_layer_modes_init
argument_list|()
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_BLEND
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_BORDER
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_CAGE_COEF_CALC
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_CAGE_TRANSFORM
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_COMPOSE_CROP
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_EQUALIZE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_FLOOD
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_GROW
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_HISTOGRAM_SINK
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_MASK_COMPONENTS
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_PROFILE_TRANSFORM
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_SCALAR_MULTIPLY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_SEMI_FLATTEN
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_SET_ALPHA
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_SHAPEBURST
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_SHRINK
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_THRESHOLD_ALPHA
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_BRIGHTNESS_CONTRAST
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_COLOR_BALANCE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_COLORIZE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_CURVES
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_DESATURATE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_HUE_SATURATION
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_LEVELS
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_POSTERIZE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_THRESHOLD
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_NORMAL
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_DISSOLVE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_BEHIND
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_MULTIPLY_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_SCREEN_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_DIFFERENCE_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_ADDITION_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_SUBTRACT_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_DARKEN_ONLY_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_LIGHTEN_ONLY_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_HSV_HUE_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_HSV_SATURATION_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_HSV_COLOR_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_HSV_VALUE_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_DIVIDE_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_DODGE_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_BURN_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_HARDLIGHT_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_SOFTLIGHT_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_GRAIN_EXTRACT_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_GRAIN_MERGE_LEGACY
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_COLOR_ERASE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_ERASE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_REPLACE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_ANTI_ERASE
argument_list|)
expr_stmt|;
name|gimp_operation_config_register
argument_list|(
literal|"gimp:brightness-contrast"
argument_list|,
name|GIMP_TYPE_BRIGHTNESS_CONTRAST_CONFIG
argument_list|)
expr_stmt|;
name|gimp_operation_config_register
argument_list|(
literal|"gimp:color-balance"
argument_list|,
name|GIMP_TYPE_COLOR_BALANCE_CONFIG
argument_list|)
expr_stmt|;
name|gimp_operation_config_register
argument_list|(
literal|"gimp:colorize"
argument_list|,
name|GIMP_TYPE_COLORIZE_CONFIG
argument_list|)
expr_stmt|;
name|gimp_operation_config_register
argument_list|(
literal|"gimp:curves"
argument_list|,
name|GIMP_TYPE_CURVES_CONFIG
argument_list|)
expr_stmt|;
name|gimp_operation_config_register
argument_list|(
literal|"gimp:hue-saturation"
argument_list|,
name|GIMP_TYPE_HUE_SATURATION_CONFIG
argument_list|)
expr_stmt|;
name|gimp_operation_config_register
argument_list|(
literal|"gimp:levels"
argument_list|,
name|GIMP_TYPE_LEVELS_CONFIG
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

