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
file|"operations/gimpdesaturateconfig.h"
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
file|"gimpdesaturatetool.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_desaturate_tool_initialize
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
name|gimp_desaturate_tool_get_operation
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
name|gimp_desaturate_tool_dialog
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
name|gimp_desaturate_tool_config_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDesaturateTool
modifier|*
name|desaturate_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_desaturate_tool_mode_changed
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpDesaturateTool
modifier|*
name|desaturate_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDesaturateTool,gimp_desaturate_tool,GIMP_TYPE_IMAGE_MAP_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDesaturateTool
argument_list|,
argument|gimp_desaturate_tool
argument_list|,
argument|GIMP_TYPE_IMAGE_MAP_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_desaturate_tool_parent_class
end_define

begin_function
name|void
name|gimp_desaturate_tool_register
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
name|GIMP_TYPE_DESATURATE_TOOL
argument_list|,
name|GIMP_TYPE_IMAGE_MAP_OPTIONS
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|"gimp-desaturate-tool"
argument_list|,
name|_
argument_list|(
literal|"Desaturate"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Desaturate Tool: Turn colors into shades of gray"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Desaturate..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_DESATURATE
argument_list|,
name|GIMP_STOCK_TOOL_DESATURATE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_desaturate_tool_class_init (GimpDesaturateToolClass * klass)
name|gimp_desaturate_tool_class_init
parameter_list|(
name|GimpDesaturateToolClass
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
name|gimp_desaturate_tool_initialize
expr_stmt|;
name|im_tool_class
operator|->
name|dialog_desc
operator|=
name|_
argument_list|(
literal|"Desaturate (Remove Colors)"
argument_list|)
expr_stmt|;
name|im_tool_class
operator|->
name|get_operation
operator|=
name|gimp_desaturate_tool_get_operation
expr_stmt|;
name|im_tool_class
operator|->
name|dialog
operator|=
name|gimp_desaturate_tool_dialog
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_desaturate_tool_init (GimpDesaturateTool * desaturate_tool)
name|gimp_desaturate_tool_init
parameter_list|(
name|GimpDesaturateTool
modifier|*
name|desaturate_tool
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_desaturate_tool_initialize (GimpTool * tool,GimpDisplay * display,GError ** error)
name|gimp_desaturate_tool_initialize
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
name|GimpDesaturateTool
modifier|*
name|desaturate_tool
init|=
name|GIMP_DESATURATE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"Desaturate only operates on RGB layers."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_config_reset
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|desaturate_tool
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
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
name|gimp_int_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|desaturate_tool
operator|->
name|button
argument_list|)
argument_list|,
name|desaturate_tool
operator|->
name|config
operator|->
name|mode
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|desaturate_tool
argument_list|)
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
DECL|function|gimp_desaturate_tool_get_operation (GimpImageMapTool * image_map_tool,GObject ** config,gchar ** undo_desc)
name|gimp_desaturate_tool_get_operation
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
name|GimpDesaturateTool
modifier|*
name|desaturate_tool
init|=
name|GIMP_DESATURATE_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|desaturate_tool
operator|->
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DESATURATE_CONFIG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|desaturate_tool
operator|->
name|config
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_desaturate_tool_config_notify
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|desaturate_tool
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
name|desaturate_tool
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
literal|"gimp:desaturate"
argument_list|,
literal|"config"
argument_list|,
name|desaturate_tool
operator|->
name|config
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/***********************/
end_comment

begin_comment
comment|/*  Desaturate dialog  */
end_comment

begin_comment
comment|/***********************/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_desaturate_tool_dialog (GimpImageMapTool * image_map_tool)
name|gimp_desaturate_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpDesaturateTool
modifier|*
name|desaturate_tool
init|=
name|GIMP_DESATURATE_TOOL
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
name|frame
decl_stmt|;
name|main_vbox
operator|=
name|gimp_image_map_tool_dialog_get_vbox
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
comment|/*  The table containing sliders  */
name|frame
operator|=
name|gimp_enum_radio_frame_new
argument_list|(
name|GIMP_TYPE_DESATURATE_MODE
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Choose shade of gray based on:"
argument_list|)
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_desaturate_tool_mode_changed
argument_list|)
argument_list|,
name|desaturate_tool
argument_list|,
operator|&
name|desaturate_tool
operator|->
name|button
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_desaturate_tool_config_notify (GObject * object,GParamSpec * pspec,GimpDesaturateTool * desaturate_tool)
name|gimp_desaturate_tool_config_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDesaturateTool
modifier|*
name|desaturate_tool
parameter_list|)
block|{
name|GimpDesaturateConfig
modifier|*
name|config
init|=
name|GIMP_DESATURATE_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|desaturate_tool
operator|->
name|button
condition|)
return|return;
name|gimp_int_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|desaturate_tool
operator|->
name|button
argument_list|)
argument_list|,
name|config
operator|->
name|mode
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_desaturate_tool_mode_changed (GtkWidget * button,GimpDesaturateTool * desaturate_tool)
name|gimp_desaturate_tool_mode_changed
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpDesaturateTool
modifier|*
name|desaturate_tool
parameter_list|)
block|{
name|GimpDesaturateConfig
modifier|*
name|config
init|=
name|desaturate_tool
operator|->
name|config
decl_stmt|;
name|GimpDesaturateMode
name|mode
decl_stmt|;
name|mode
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|mode
operator|!=
name|mode
condition|)
block|{
name|g_object_set
argument_list|(
name|config
argument_list|,
literal|"mode"
argument_list|,
name|mode
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

