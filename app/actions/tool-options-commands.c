begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolpreset.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdataeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmessagebox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmessagedialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptooloptionseditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwindowstrategy.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/data-delete-dialog.h"
end_include

begin_include
include|#
directive|include
file|"tool-options-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|tool_options_show_preset_editor
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpEditor
modifier|*
name|editor
parameter_list|,
name|GimpToolPreset
modifier|*
name|preset
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|tool_options_save_new_preset_cmd_callback (GimpAction * action,GVariant * value,gpointer user_data)
name|tool_options_save_new_preset_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GVariant
modifier|*
name|value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|editor
init|=
name|GIMP_EDITOR
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|Gimp
modifier|*
name|gimp
init|=
name|gimp_editor_get_ui_manager
argument_list|(
name|editor
argument_list|)
operator|->
name|gimp
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
decl_stmt|;
name|GimpData
modifier|*
name|data
decl_stmt|;
name|data
operator|=
name|gimp_data_factory_data_new
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|tool_preset_factory
argument_list|,
name|context
argument_list|,
name|_
argument_list|(
literal|"Untitled"
argument_list|)
argument_list|)
expr_stmt|;
name|tool_options_show_preset_editor
argument_list|(
name|gimp
argument_list|,
name|editor
argument_list|,
name|GIMP_TOOL_PRESET
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_save_preset_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|tool_options_save_preset_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GVariant
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|editor
init|=
name|GIMP_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|Gimp
modifier|*
name|gimp
init|=
name|gimp_editor_get_ui_manager
argument_list|(
name|editor
argument_list|)
operator|->
name|gimp
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
decl_stmt|;
name|GimpToolPreset
modifier|*
name|preset
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|index
operator|=
name|g_variant_get_int32
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|preset
operator|=
operator|(
name|GimpToolPreset
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|tool_info
operator|->
name|presets
argument_list|,
name|index
argument_list|)
expr_stmt|;
if|if
condition|(
name|preset
condition|)
block|{
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|preset
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|tool_options_show_preset_editor
argument_list|(
name|gimp
argument_list|,
name|editor
argument_list|,
name|preset
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_options_restore_preset_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|tool_options_restore_preset_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GVariant
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|editor
init|=
name|GIMP_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|Gimp
modifier|*
name|gimp
init|=
name|gimp_editor_get_ui_manager
argument_list|(
name|editor
argument_list|)
operator|->
name|gimp
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
decl_stmt|;
name|GimpToolPreset
modifier|*
name|preset
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|index
operator|=
name|g_variant_get_int32
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|preset
operator|=
operator|(
name|GimpToolPreset
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|tool_info
operator|->
name|presets
argument_list|,
name|index
argument_list|)
expr_stmt|;
if|if
condition|(
name|preset
condition|)
block|{
if|if
condition|(
name|gimp_context_get_tool_preset
argument_list|(
name|context
argument_list|)
operator|!=
name|preset
condition|)
name|gimp_context_set_tool_preset
argument_list|(
name|context
argument_list|,
name|preset
argument_list|)
expr_stmt|;
else|else
name|gimp_context_tool_preset_changed
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_options_edit_preset_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|tool_options_edit_preset_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GVariant
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|editor
init|=
name|GIMP_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|Gimp
modifier|*
name|gimp
init|=
name|gimp_editor_get_ui_manager
argument_list|(
name|editor
argument_list|)
operator|->
name|gimp
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
decl_stmt|;
name|GimpToolPreset
modifier|*
name|preset
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|index
operator|=
name|g_variant_get_int32
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|preset
operator|=
operator|(
name|GimpToolPreset
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|tool_info
operator|->
name|presets
argument_list|,
name|index
argument_list|)
expr_stmt|;
if|if
condition|(
name|preset
condition|)
block|{
name|tool_options_show_preset_editor
argument_list|(
name|gimp
argument_list|,
name|editor
argument_list|,
name|preset
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_options_delete_preset_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|tool_options_delete_preset_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GVariant
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|editor
init|=
name|GIMP_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|gimp_get_user_context
argument_list|(
name|gimp_editor_get_ui_manager
argument_list|(
name|editor
argument_list|)
operator|->
name|gimp
argument_list|)
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
decl_stmt|;
name|GimpToolPreset
modifier|*
name|preset
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|index
operator|=
name|g_variant_get_int32
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|preset
operator|=
operator|(
name|GimpToolPreset
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|tool_info
operator|->
name|presets
argument_list|,
name|index
argument_list|)
expr_stmt|;
if|if
condition|(
name|preset
operator|&&
name|gimp_data_is_deletable
argument_list|(
name|GIMP_DATA
argument_list|(
name|preset
argument_list|)
argument_list|)
condition|)
block|{
name|GimpDataFactory
modifier|*
name|factory
init|=
name|context
operator|->
name|gimp
operator|->
name|tool_preset_factory
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|data_delete_dialog_new
argument_list|(
name|factory
argument_list|,
name|GIMP_DATA
argument_list|(
name|preset
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_options_reset_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|tool_options_reset_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GVariant
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|editor
init|=
name|GIMP_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|gimp_get_user_context
argument_list|(
name|gimp_editor_get_ui_manager
argument_list|(
name|editor
argument_list|)
operator|->
name|gimp
argument_list|)
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
decl_stmt|;
name|gimp_config_reset
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_reset_all_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|tool_options_reset_all_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GVariant
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|editor
init|=
name|GIMP_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Reset All Tool Options"
argument_list|)
argument_list|,
name|GIMP_ICON_DIALOG_QUESTION
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_DIALOG_MODAL
operator||
name|GTK_DIALOG_DESTROY_WITH_PARENT
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"_Cancel"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|_
argument_list|(
literal|"_Reset"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|)
expr_stmt|;
name|gimp_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
argument_list|,
literal|"unmap"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|dialog
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|gimp_message_box_set_primary_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"Do you really want to reset all "
literal|"tool options to default values?"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|gimp_editor_get_ui_manager
argument_list|(
name|editor
argument_list|)
operator|->
name|gimp
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_get_tool_info_iter
argument_list|(
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
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_config_reset
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|tool_options_show_preset_editor (Gimp * gimp,GimpEditor * editor,GimpToolPreset * preset)
name|tool_options_show_preset_editor
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpEditor
modifier|*
name|editor
parameter_list|,
name|GimpToolPreset
modifier|*
name|preset
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dockable
decl_stmt|;
name|dockable
operator|=
name|gimp_window_strategy_show_dockable_dialog
argument_list|(
name|GIMP_WINDOW_STRATEGY
argument_list|(
name|gimp_get_window_strategy
argument_list|(
name|gimp
argument_list|)
argument_list|)
argument_list|,
name|gimp
argument_list|,
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|gimp_widget_get_monitor
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
argument_list|,
literal|"gimp-tool-preset-editor"
argument_list|)
expr_stmt|;
name|gimp_data_editor_set_data
argument_list|(
name|GIMP_DATA_EDITOR
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|GIMP_DATA
argument_list|(
name|preset
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

