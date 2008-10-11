begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl.c  * Copyright (C) 2007 Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"base/tile.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl.h"
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
file|"gimpoperationtilesink.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationtilesource.h"
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
DECL|function|gimp_gegl_init (void)
name|gimp_gegl_init
parameter_list|(
name|void
parameter_list|)
block|{
name|g_object_set
argument_list|(
name|gegl_config
argument_list|()
argument_list|,
literal|"tile-width"
argument_list|,
name|TILE_WIDTH
argument_list|,
literal|"tile-height"
argument_list|,
name|TILE_HEIGHT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_TILE_SINK
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_OPERATION_TILE_SOURCE
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

