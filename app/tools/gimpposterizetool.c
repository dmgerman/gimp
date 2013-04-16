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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"operations/gimpposterizeconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimperror.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagemapoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpposterizetool.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|SLIDER_WIDTH
define|#
directive|define
name|SLIDER_WIDTH
value|200
end_define

begin_function_decl
specifier|static
name|gboolean
name|gimp_posterize_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GeglNode
modifier|*
name|gimp_posterize_tool_get_operation
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|,
name|GObject
modifier|*
modifier|*
name|config
parameter_list|,
name|gchar
modifier|*
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_posterize_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_posterize_tool_config_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpPosterizeTool
modifier|*
name|posterize_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_posterize_tool_levels_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpPosterizeTool
modifier|*
name|posterize_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpPosterizeTool,gimp_posterize_tool,GIMP_TYPE_IMAGE_MAP_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPosterizeTool
argument_list|,
argument|gimp_posterize_tool
argument_list|,
argument|GIMP_TYPE_IMAGE_MAP_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_posterize_tool_parent_class
end_define

begin_function
name|void
name|gimp_posterize_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_POSTERIZE_TOOL
argument_list|,
name|GIMP_TYPE_IMAGE_MAP_OPTIONS
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|"gimp-posterize-tool"
argument_list|,
name|_
argument_list|(
literal|"Posterize"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Posterize Tool: Reduce to a limited set of colors"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Posterize..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_POSTERIZE
argument_list|,
name|GIMP_STOCK_TOOL_POSTERIZE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_posterize_tool_class_init (GimpPosterizeToolClass * klass)
name|gimp_posterize_tool_class_init
parameter_list|(
name|GimpPosterizeToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
init|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpImageMapToolClass
modifier|*
name|im_tool_class
init|=
name|GIMP_IMAGE_MAP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_posterize_tool_initialize
expr_stmt|;
name|im_tool_class
operator|->
name|dialog_desc
operator|=
name|_
argument_list|(
literal|"Posterize (Reduce Number of Colors)"
argument_list|)
expr_stmt|;
name|im_tool_class
operator|->
name|get_operation
operator|=
name|gimp_posterize_tool_get_operation
expr_stmt|;
name|im_tool_class
operator|->
name|dialog
operator|=
name|gimp_posterize_tool_dialog
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_posterize_tool_init (GimpPosterizeTool * posterize_tool)
name|gimp_posterize_tool_init
parameter_list|(
name|GimpPosterizeTool
modifier|*
name|posterize_tool
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_posterize_tool_initialize (GimpTool * tool,GimpDisplay * display,GError ** error)
name|gimp_posterize_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPosterizeTool
modifier|*
name|posterize_tool
init|=
name|GIMP_POSTERIZE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|initialize
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|error
argument_list|)
condition|)
block|{
return|return
name|FALSE
return|;
block|}
name|gtk_adjustment_set_value
argument_list|(
name|posterize_tool
operator|->
name|levels_data
argument_list|,
name|posterize_tool
operator|->
name|config
operator|->
name|levels
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|GeglNode
modifier|*
DECL|function|gimp_posterize_tool_get_operation (GimpImageMapTool * image_map_tool,GObject ** config,gchar ** undo_desc)
name|gimp_posterize_tool_get_operation
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|,
name|GObject
modifier|*
modifier|*
name|config
parameter_list|,
name|gchar
modifier|*
modifier|*
name|undo_desc
parameter_list|)
block|{
name|GimpPosterizeTool
modifier|*
name|posterize_tool
init|=
name|GIMP_POSTERIZE_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|posterize_tool
operator|->
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_POSTERIZE_CONFIG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|posterize_tool
operator|->
name|config
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_posterize_tool_config_notify
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|posterize_tool
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
operator|*
name|config
operator|=
name|G_OBJECT
argument_list|(
name|posterize_tool
operator|->
name|config
argument_list|)
expr_stmt|;
return|return
name|gegl_node_new_child
argument_list|(
name|NULL
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:posterize"
argument_list|,
literal|"config"
argument_list|,
name|posterize_tool
operator|->
name|config
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**********************/
end_comment

begin_comment
comment|/*  Posterize dialog  */
end_comment

begin_comment
comment|/**********************/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_posterize_tool_dialog (GimpImageMapTool * image_map_tool)
name|gimp_posterize_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpPosterizeTool
modifier|*
name|posterize_tool
init|=
name|GIMP_POSTERIZE_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkObject
modifier|*
name|data
decl_stmt|;
name|main_vbox
operator|=
name|gimp_image_map_tool_dialog_get_vbox
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
comment|/*  The table containing sliders  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|data
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Posterize _levels:"
argument_list|)
argument_list|,
name|SLIDER_WIDTH
argument_list|,
operator|-
literal|1
argument_list|,
name|posterize_tool
operator|->
name|config
operator|->
name|levels
argument_list|,
literal|2.0
argument_list|,
literal|256.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_scale_entry_set_logarithmic
argument_list|(
name|data
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|posterize_tool
operator|->
name|levels_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|posterize_tool
operator|->
name|levels_data
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_posterize_tool_levels_changed
argument_list|)
argument_list|,
name|posterize_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_posterize_tool_config_notify (GObject * object,GParamSpec * pspec,GimpPosterizeTool * posterize_tool)
name|gimp_posterize_tool_config_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpPosterizeTool
modifier|*
name|posterize_tool
parameter_list|)
block|{
name|GimpPosterizeConfig
modifier|*
name|config
init|=
name|GIMP_POSTERIZE_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|posterize_tool
operator|->
name|levels_data
condition|)
return|return;
name|gtk_adjustment_set_value
argument_list|(
name|posterize_tool
operator|->
name|levels_data
argument_list|,
name|config
operator|->
name|levels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_posterize_tool_levels_changed (GtkAdjustment * adjustment,GimpPosterizeTool * posterize_tool)
name|gimp_posterize_tool_levels_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpPosterizeTool
modifier|*
name|posterize_tool
parameter_list|)
block|{
name|gint
name|value
init|=
name|ROUND
argument_list|(
name|gtk_adjustment_get_value
argument_list|(
name|adjustment
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|posterize_tool
operator|->
name|config
operator|->
name|levels
operator|!=
name|value
condition|)
block|{
name|g_object_set
argument_list|(
name|posterize_tool
operator|->
name|config
argument_list|,
literal|"levels"
argument_list|,
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

