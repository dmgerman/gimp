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
file|<string.h>
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
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimpinkoptions.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpenumaction.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimp-tools.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimpcoloroptions.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimpforegroundselectoptions.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimprectangleoptions.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimpimagemaptool.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimptransformoptions.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"tools-commands.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|tools_activate_enum_action
parameter_list|(
specifier|const
name|gchar
modifier|*
name|action_desc
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|tools_select_cmd_callback (GtkAction * action,const gchar * value,gpointer data)
name|tools_select_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|gboolean
name|rotate_layer
init|=
name|FALSE
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
comment|/*  special case gimp-rotate-tool being called from the Layer menu  */
if|if
condition|(
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"gimp-rotate-layer"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|rotate_layer
operator|=
name|TRUE
expr_stmt|;
name|value
operator|=
literal|"gimp-rotate-tool"
expr_stmt|;
block|}
name|tool_info
operator|=
name|gimp_get_tool_info
argument_list|(
name|gimp
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
comment|/*  always allocate a new tool when selected from the image menu    */
if|if
condition|(
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
operator|!=
name|tool_info
condition|)
block|{
name|gimp_context_set_tool
argument_list|(
name|context
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
if|if
condition|(
name|rotate_layer
condition|)
name|g_object_set
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|,
literal|"type"
argument_list|,
name|GIMP_TRANSFORM_TYPE_LAYER
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_context_tool_changed
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
name|display
operator|=
name|gimp_context_get_display
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|display
operator|&&
name|display
operator|->
name|image
condition|)
name|tool_manager_initialize_active
argument_list|(
name|gimp
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_toggle_visibility_cmd_callback (GtkAction * action,gpointer data)
name|tools_toggle_visibility_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
condition|)
block|{
name|gboolean
name|active
init|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|active
operator|!=
name|tool_info
operator|->
name|visible
condition|)
name|g_object_set
argument_list|(
name|tool_info
argument_list|,
literal|"visible"
argument_list|,
name|active
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_raise_cmd_callback (GtkAction * action,gpointer data)
name|tools_raise_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
condition|)
block|{
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|container
operator|=
name|context
operator|->
name|gimp
operator|->
name|tool_info_list
expr_stmt|;
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|>
literal|0
condition|)
name|gimp_container_reorder
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|index
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_raise_to_top_cmd_callback (GtkAction * action,gpointer data)
name|tools_raise_to_top_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
condition|)
block|{
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|container
operator|=
name|context
operator|->
name|gimp
operator|->
name|tool_info_list
expr_stmt|;
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|>
literal|0
condition|)
name|gimp_container_reorder
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_lower_cmd_callback (GtkAction * action,gpointer data)
name|tools_lower_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
condition|)
block|{
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|container
operator|=
name|context
operator|->
name|gimp
operator|->
name|tool_info_list
expr_stmt|;
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|+
literal|1
operator|<
name|gimp_container_get_n_children
argument_list|(
name|container
argument_list|)
condition|)
name|gimp_container_reorder
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|index
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_lower_to_bottom_cmd_callback (GtkAction * action,gpointer data)
name|tools_lower_to_bottom_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
condition|)
block|{
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|container
operator|=
name|context
operator|->
name|gimp
operator|->
name|tool_info_list
expr_stmt|;
name|index
operator|=
name|gimp_container_get_n_children
argument_list|(
name|container
argument_list|)
operator|-
literal|1
expr_stmt|;
name|index
operator|=
name|index
operator|>=
literal|0
condition|?
name|index
else|:
literal|0
expr_stmt|;
name|gimp_container_reorder
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|index
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_reset_cmd_callback (GtkAction * action,gpointer data)
name|tools_reset_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|container
operator|=
name|context
operator|->
name|gimp
operator|->
name|tool_info_list
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_tools_get_default_order
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpObject
modifier|*
name|object
init|=
name|gimp_container_get_child_by_name
argument_list|(
name|container
argument_list|,
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|object
condition|)
block|{
name|gboolean
name|visible
decl_stmt|;
name|gimp_container_reorder
argument_list|(
name|container
argument_list|,
name|object
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|visible
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
literal|"gimp-tool-default-visible"
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|object
argument_list|,
literal|"visible"
argument_list|,
name|visible
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|i
operator|++
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_color_average_radius_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tools_color_average_radius_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|GIMP_IS_COLOR_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
condition|)
block|{
name|action_select_property
argument_list|(
operator|(
name|GimpActionSelectType
operator|)
name|value
argument_list|,
name|action_data_get_display
argument_list|(
name|data
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|"average-radius"
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_paint_brush_scale_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tools_paint_brush_scale_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
condition|)
block|{
name|action_select_property
argument_list|(
operator|(
name|GimpActionSelectType
operator|)
name|value
argument_list|,
name|action_data_get_display
argument_list|(
name|data
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|"brush-scale"
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_paint_brush_angle_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tools_paint_brush_angle_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
condition|)
block|{
name|action_select_property
argument_list|(
operator|(
name|GimpActionSelectType
operator|)
name|value
argument_list|,
name|action_data_get_display
argument_list|(
name|data
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|"brush-angle"
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|15.0
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_ink_blob_size_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tools_ink_blob_size_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|GIMP_IS_INK_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
condition|)
block|{
name|action_select_property
argument_list|(
operator|(
name|GimpActionSelectType
operator|)
name|value
argument_list|,
name|action_data_get_display
argument_list|(
name|data
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|"size"
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_ink_blob_aspect_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tools_ink_blob_aspect_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|GIMP_IS_INK_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
condition|)
block|{
name|action_select_property
argument_list|(
operator|(
name|GimpActionSelectType
operator|)
name|value
argument_list|,
name|action_data_get_display
argument_list|(
name|data
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|"blob-aspect"
argument_list|,
literal|1.0
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_ink_blob_angle_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tools_ink_blob_angle_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|GIMP_IS_INK_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
condition|)
block|{
name|action_select_property
argument_list|(
operator|(
name|GimpActionSelectType
operator|)
name|value
argument_list|,
name|action_data_get_display
argument_list|(
name|data
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|"blob-angle"
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|15.0
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_fg_select_brush_size_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tools_fg_select_brush_size_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|GIMP_IS_FOREGROUND_SELECT_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
condition|)
block|{
name|action_select_property
argument_list|(
operator|(
name|GimpActionSelectType
operator|)
name|value
argument_list|,
name|action_data_get_display
argument_list|(
name|data
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|"stroke-width"
argument_list|,
literal|1.0
argument_list|,
literal|4.0
argument_list|,
literal|16.0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_transform_preview_opacity_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tools_transform_preview_opacity_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|GIMP_IS_TRANSFORM_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
condition|)
block|{
name|action_select_property
argument_list|(
operator|(
name|GimpActionSelectType
operator|)
name|value
argument_list|,
name|action_data_get_display
argument_list|(
name|data
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|"preview-opacity"
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|0.5
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_value_1_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tools_value_1_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool
operator|=
name|tool_manager_get_active
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|action_desc
decl_stmt|;
name|action_desc
operator|=
name|gimp_tool_control_get_action_value_1
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
if|if
condition|(
name|action_desc
condition|)
name|tools_activate_enum_action
argument_list|(
name|action_desc
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_value_2_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tools_value_2_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool
operator|=
name|tool_manager_get_active
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|action_desc
decl_stmt|;
name|action_desc
operator|=
name|gimp_tool_control_get_action_value_2
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
if|if
condition|(
name|action_desc
condition|)
name|tools_activate_enum_action
argument_list|(
name|action_desc
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_value_3_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tools_value_3_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool
operator|=
name|tool_manager_get_active
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|action_desc
decl_stmt|;
name|action_desc
operator|=
name|gimp_tool_control_get_action_value_3
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
if|if
condition|(
name|action_desc
condition|)
name|tools_activate_enum_action
argument_list|(
name|action_desc
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_value_4_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tools_value_4_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool
operator|=
name|tool_manager_get_active
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|action_desc
decl_stmt|;
name|action_desc
operator|=
name|gimp_tool_control_get_action_value_4
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
if|if
condition|(
name|action_desc
condition|)
name|tools_activate_enum_action
argument_list|(
name|action_desc
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_object_1_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tools_object_1_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool
operator|=
name|tool_manager_get_active
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|action_desc
decl_stmt|;
name|action_desc
operator|=
name|gimp_tool_control_get_action_object_1
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
if|if
condition|(
name|action_desc
condition|)
name|tools_activate_enum_action
argument_list|(
name|action_desc
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_object_2_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tools_object_2_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|tool
operator|=
name|tool_manager_get_active
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|action_desc
decl_stmt|;
name|action_desc
operator|=
name|gimp_tool_control_get_action_object_2
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
if|if
condition|(
name|action_desc
condition|)
name|tools_activate_enum_action
argument_list|(
name|action_desc
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|tools_activate_enum_action (const gchar * action_desc,gint value)
name|tools_activate_enum_action
parameter_list|(
specifier|const
name|gchar
modifier|*
name|action_desc
parameter_list|,
name|gint
name|value
parameter_list|)
block|{
name|gchar
modifier|*
name|group_name
decl_stmt|;
name|gchar
modifier|*
name|action_name
decl_stmt|;
name|group_name
operator|=
name|g_strdup
argument_list|(
name|action_desc
argument_list|)
expr_stmt|;
name|action_name
operator|=
name|strchr
argument_list|(
name|group_name
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
name|action_name
condition|)
block|{
name|GList
modifier|*
name|managers
decl_stmt|;
name|GtkAction
modifier|*
name|action
decl_stmt|;
operator|*
name|action_name
operator|++
operator|=
literal|'\0'
expr_stmt|;
name|managers
operator|=
name|gimp_ui_managers_from_name
argument_list|(
literal|"<Image>"
argument_list|)
expr_stmt|;
name|action
operator|=
name|gimp_ui_manager_find_action
argument_list|(
name|managers
operator|->
name|data
argument_list|,
name|group_name
argument_list|,
name|action_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_ENUM_ACTION
argument_list|(
name|action
argument_list|)
operator|&&
name|GIMP_ENUM_ACTION
argument_list|(
name|action
argument_list|)
operator|->
name|value_variable
condition|)
block|{
name|gimp_enum_action_selected
argument_list|(
name|GIMP_ENUM_ACTION
argument_list|(
name|action
argument_list|)
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|group_name
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

