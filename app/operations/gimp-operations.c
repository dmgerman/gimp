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
file|<gio/gio.h>
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
file|"gimpoperationequalize.h"
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
file|"gimpoperationpointlayermode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationnormalmode.h"
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
file|"gimpoperationmultiplymode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationscreenmode.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationoverlaymode.h"
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
file|"gimpoperationdodgemode.h"
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
name|void
DECL|function|gimp_operations_init (void)
name|gimp_operations_init
parameter_list|(
name|void
parameter_list|)
block|{
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
name|GIMP_TYPE_OPERATION_EQUALIZE
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
name|GIMP_TYPE_OPERATION_POINT_LAYER_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_NORMAL_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_DISSOLVE_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_BEHIND_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_MULTIPLY_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_SCREEN_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_OVERLAY_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_DIFFERENCE_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_ADDITION_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_SUBTRACT_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_DARKEN_ONLY_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_LIGHTEN_ONLY_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_HUE_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_SATURATION_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_COLOR_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_VALUE_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_DIVIDE_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_DODGE_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_BURN_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_HARDLIGHT_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_SOFTLIGHT_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_GRAIN_EXTRACT_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_GRAIN_MERGE_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_COLOR_ERASE_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_LCH_HUE_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_LCH_CHROMA_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_LCH_COLOR_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_LCH_LIGHTNESS_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_ERASE_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_REPLACE_MODE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_ANTI_ERASE_MODE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

