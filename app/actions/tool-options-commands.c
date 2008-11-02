begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimptoolpresets.h"
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
name|tool_options_save_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_options_rename_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|tool_options_save_new_cmd_callback (GtkAction * action,gpointer data)
name|tool_options_save_new_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
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
name|editor
operator|->
name|ui_manager
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
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|editor
operator|->
name|ui_manager
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_query_string_box
argument_list|(
name|_
argument_list|(
literal|"Save Tool Options"
argument_list|)
argument_list|,
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_DIALOG
argument_list|,
name|_
argument_list|(
literal|"Enter a name for the saved options"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Saved Options"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|tool_options_save_callback
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_save_to_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tool_options_save_to_cmd_callback
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
name|editor
operator|->
name|ui_manager
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
name|GimpToolOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|gimp_tool_presets_get_options
argument_list|(
name|tool_info
operator|->
name|presets
argument_list|,
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
condition|)
block|{
name|gchar
modifier|*
name|name
init|=
name|g_strdup
argument_list|(
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|)
decl_stmt|;
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
name|options
argument_list|)
argument_list|,
name|GIMP_CONFIG_PARAM_SERIALIZE
argument_list|)
expr_stmt|;
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_options_restore_from_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tool_options_restore_from_cmd_callback
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
name|editor
operator|->
name|ui_manager
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
name|GimpToolOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|gimp_tool_presets_get_options
argument_list|(
name|tool_info
operator|->
name|presets
argument_list|,
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
condition|)
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|GIMP_CONFIG_PARAM_SERIALIZE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_rename_saved_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tool_options_rename_saved_cmd_callback
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
name|editor
operator|->
name|ui_manager
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
name|GimpToolOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|gimp_tool_presets_get_options
argument_list|(
name|tool_info
operator|->
name|presets
argument_list|,
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
condition|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|gimp_query_string_box
argument_list|(
name|_
argument_list|(
literal|"Rename Saved Tool Options"
argument_list|)
argument_list|,
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_DIALOG
argument_list|,
name|_
argument_list|(
literal|"Enter a new name for the saved options"
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
operator|->
name|name
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|tool_options_rename_callback
argument_list|,
name|options
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
DECL|function|tool_options_delete_saved_cmd_callback (GtkAction * action,gint value,gpointer data)
name|tool_options_delete_saved_cmd_callback
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
name|editor
operator|->
name|ui_manager
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
name|GimpToolOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|gimp_tool_presets_get_options
argument_list|(
name|tool_info
operator|->
name|presets
argument_list|,
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
condition|)
name|gimp_container_remove
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|tool_info
operator|->
name|presets
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_reset_cmd_callback (GtkAction * action,gpointer data)
name|tool_options_reset_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
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
name|editor
operator|->
name|ui_manager
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
name|gimp_tool_options_reset
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_reset_all_cmd_callback (GtkAction * action,gpointer data)
name|tool_options_reset_all_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
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
literal|"Reset Tool Options"
argument_list|)
argument_list|,
name|GIMP_STOCK_QUESTION
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
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
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
name|editor
operator|->
name|ui_manager
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
name|gimp_tool_options_reset
argument_list|(
name|tool_info
operator|->
name|tool_options
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
DECL|function|tool_options_save_callback (GtkWidget * widget,const gchar * name,gpointer data)
name|tool_options_save_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|GIMP_TOOL_INFO
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpConfig
modifier|*
name|copy
decl_stmt|;
name|copy
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|name
operator|&&
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|copy
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
else|else
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|copy
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Saved Options"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_insert
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|tool_info
operator|->
name|presets
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|copy
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|copy
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_options_rename_callback (GtkWidget * widget,const gchar * name,gpointer data)
name|tool_options_rename_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpToolOptions
modifier|*
name|options
init|=
name|GIMP_TOOL_OPTIONS
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|name
operator|&&
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
else|else
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Saved Options"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

