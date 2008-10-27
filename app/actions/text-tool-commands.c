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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
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
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimptexttool.h"
end_include

begin_include
include|#
directive|include
file|"text-tool-commands.h"
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
name|text_tool_load_dialog_destroyed
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GObject
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|text_tool_load_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpTextTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|text_tool_cut_cmd_callback (GtkAction * action,gpointer data)
name|text_tool_cut_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTextTool
modifier|*
name|text_tool
init|=
name|GIMP_TEXT_TOOL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_text_tool_clipboard_cut
argument_list|(
name|text_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|text_tool_copy_cmd_callback (GtkAction * action,gpointer data)
name|text_tool_copy_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTextTool
modifier|*
name|text_tool
init|=
name|GIMP_TEXT_TOOL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_text_tool_clipboard_copy
argument_list|(
name|text_tool
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|text_tool_paste_cmd_callback (GtkAction * action,gpointer data)
name|text_tool_paste_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTextTool
modifier|*
name|text_tool
init|=
name|GIMP_TEXT_TOOL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_text_tool_clipboard_paste
argument_list|(
name|text_tool
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|text_tool_delete_cmd_callback (GtkAction * action,gpointer data)
name|text_tool_delete_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTextTool
modifier|*
name|text_tool
init|=
name|GIMP_TEXT_TOOL
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|gtk_text_buffer_get_has_selection
argument_list|(
name|text_tool
operator|->
name|text_buffer
argument_list|)
condition|)
name|gimp_text_tool_delete_text
argument_list|(
name|text_tool
argument_list|,
name|TRUE
comment|/* unused */
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|text_tool_load_cmd_callback (GtkAction * action,gpointer data)
name|text_tool_load_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTextTool
modifier|*
name|text_tool
init|=
name|GIMP_TEXT_TOOL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|parent
init|=
name|NULL
decl_stmt|;
name|GtkFileChooser
modifier|*
name|chooser
decl_stmt|;
name|dialog
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|text_tool
argument_list|)
argument_list|,
literal|"gimp-text-file-dialog"
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|GIMP_TOOL
argument_list|(
name|text_tool
argument_list|)
operator|->
name|display
condition|)
name|parent
operator|=
name|GIMP_TOOL
argument_list|(
name|text_tool
argument_list|)
operator|->
name|display
operator|->
name|shell
expr_stmt|;
name|dialog
operator|=
name|gtk_file_chooser_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Open Text File (UTF-8)"
argument_list|)
argument_list|,
name|parent
condition|?
name|GTK_WINDOW
argument_list|(
name|parent
argument_list|)
else|:
name|NULL
argument_list|,
name|GTK_FILE_CHOOSER_ACTION_OPEN
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OPEN
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|chooser
operator|=
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
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
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|text_tool
argument_list|)
argument_list|,
literal|"gimp-text-file-dialog"
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|text_tool_load_dialog_destroyed
argument_list|)
argument_list|,
name|text_tool
argument_list|)
expr_stmt|;
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|,
literal|"gimp-text-load-file"
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|chooser
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|chooser
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|text_tool_load_dialog_response
argument_list|)
argument_list|,
name|text_tool
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|chooser
argument_list|,
literal|"delete-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_true
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|chooser
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|text_tool_clear_cmd_callback (GtkAction * action,gpointer data)
name|text_tool_clear_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTextTool
modifier|*
name|text_tool
init|=
name|GIMP_TEXT_TOOL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GtkTextIter
name|start
decl_stmt|,
name|end
decl_stmt|;
name|gtk_text_buffer_get_bounds
argument_list|(
name|text_tool
operator|->
name|text_buffer
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
name|gtk_text_buffer_select_range
argument_list|(
name|text_tool
operator|->
name|text_buffer
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
name|gimp_text_tool_delete_text
argument_list|(
name|text_tool
argument_list|,
name|TRUE
comment|/* unused */
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|text_tool_path_from_text_cmd_callback (GtkAction * action,gpointer data)
name|text_tool_path_from_text_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTextTool
modifier|*
name|text_tool
init|=
name|GIMP_TEXT_TOOL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_text_tool_create_vectors
argument_list|(
name|text_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|text_tool_text_along_path_cmd_callback (GtkAction * action,gpointer data)
name|text_tool_text_along_path_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTextTool
modifier|*
name|text_tool
init|=
name|GIMP_TEXT_TOOL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_text_tool_create_vectors_warped
argument_list|(
name|text_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|text_tool_direction_cmd_callback (GtkAction * action,GtkAction * current,gpointer data)
name|text_tool_direction_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GtkAction
modifier|*
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTextTool
modifier|*
name|text_tool
init|=
name|GIMP_TEXT_TOOL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gint
name|value
decl_stmt|;
name|value
operator|=
name|gtk_radio_action_get_current_value
argument_list|(
name|GTK_RADIO_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|text_tool
operator|->
name|proxy
argument_list|,
literal|"base-direction"
argument_list|,
operator|(
name|GimpTextDirection
operator|)
name|value
argument_list|,
name|NULL
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
DECL|function|text_tool_load_dialog_destroyed (GtkWidget * dialog,GObject * tool)
name|text_tool_load_dialog_destroyed
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GObject
modifier|*
name|tool
parameter_list|)
block|{
name|g_object_set_data
argument_list|(
name|tool
argument_list|,
literal|"gimp-text-file-dialog"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|text_tool_load_dialog_response (GtkWidget * dialog,gint response_id,GimpTextTool * tool)
name|text_tool_load_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpTextTool
modifier|*
name|tool
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|filename
operator|=
name|gtk_file_chooser_get_filename
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_text_buffer_load
argument_list|(
name|tool
operator|->
name|text_buffer
argument_list|,
name|filename
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|GIMP_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|tool_info
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_hide
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

