begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/color-balance.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimpcolorbalanceconfig.h"
end_include

begin_comment
comment|/* temp */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-color-balance.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-operation.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-process.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_drawable_color_balance (GimpDrawable * drawable,GimpProgress * progress,GimpTransferMode range,gdouble cyan_red,gdouble magenta_green,gdouble yellow_blue,gboolean preserve_luminosity)
name|gimp_drawable_color_balance
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpTransferMode
name|range
parameter_list|,
name|gdouble
name|cyan_red
parameter_list|,
name|gdouble
name|magenta_green
parameter_list|,
name|gdouble
name|yellow_blue
parameter_list|,
name|gboolean
name|preserve_luminosity
parameter_list|)
block|{
name|GimpColorBalanceConfig
modifier|*
name|config
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_BALANCE_CONFIG
argument_list|,
literal|"range"
argument_list|,
name|range
argument_list|,
literal|"preserve-luminosity"
argument_list|,
name|preserve_luminosity
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|config
argument_list|,
literal|"cyan-red"
argument_list|,
name|cyan_red
operator|/
literal|100.0
argument_list|,
literal|"magenta-green"
argument_list|,
name|magenta_green
operator|/
literal|100.0
argument_list|,
literal|"yellow-blue"
argument_list|,
name|yellow_blue
operator|/
literal|100.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_use_gegl
argument_list|(
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|->
name|gimp
argument_list|)
condition|)
block|{
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|node
operator|=
name|g_object_new
argument_list|(
name|GEGL_TYPE_NODE
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:color-balance"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|node
argument_list|,
literal|"config"
argument_list|,
name|config
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_operation
argument_list|(
name|drawable
argument_list|,
name|progress
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Color Balance"
argument_list|)
argument_list|,
name|node
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|node
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|ColorBalance
name|cruft
decl_stmt|;
name|gimp_color_balance_config_to_cruft
argument_list|(
name|config
argument_list|,
operator|&
name|cruft
argument_list|)
expr_stmt|;
name|gimp_drawable_process
argument_list|(
name|drawable
argument_list|,
name|progress
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Color Balance"
argument_list|)
argument_list|,
operator|(
name|PixelProcessorFunc
operator|)
name|color_balance
argument_list|,
operator|&
name|cruft
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|config
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

