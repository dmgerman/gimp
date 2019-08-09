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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimperrorconsole.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptextbuffer.h"
end_include

begin_include
include|#
directive|include
file|"error-console-commands.h"
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
name|error_console_save_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpErrorConsole
modifier|*
name|console
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|error_console_clear_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|error_console_clear_cmd_callback
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
name|GimpErrorConsole
modifier|*
name|console
init|=
name|GIMP_ERROR_CONSOLE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GtkTextIter
name|start_iter
decl_stmt|;
name|GtkTextIter
name|end_iter
decl_stmt|;
name|gtk_text_buffer_get_bounds
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
operator|&
name|start_iter
argument_list|,
operator|&
name|end_iter
argument_list|)
expr_stmt|;
name|gtk_text_buffer_delete
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
operator|&
name|start_iter
argument_list|,
operator|&
name|end_iter
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|error_console_select_all_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|error_console_select_all_cmd_callback
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
name|GimpErrorConsole
modifier|*
name|console
init|=
name|GIMP_ERROR_CONSOLE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GtkTextIter
name|start_iter
decl_stmt|;
name|GtkTextIter
name|end_iter
decl_stmt|;
name|gtk_text_buffer_get_bounds
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
operator|&
name|start_iter
argument_list|,
operator|&
name|end_iter
argument_list|)
expr_stmt|;
name|gtk_text_buffer_select_range
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
operator|&
name|start_iter
argument_list|,
operator|&
name|end_iter
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|error_console_save_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|error_console_save_cmd_callback
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
name|GimpErrorConsole
modifier|*
name|console
init|=
name|GIMP_ERROR_CONSOLE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gboolean
name|selection
init|=
operator|(
name|gboolean
operator|)
name|g_variant_get_int32
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|selection
operator|&&
operator|!
name|gtk_text_buffer_get_selection_bounds
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|console
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|console
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
argument_list|,
name|_
argument_list|(
literal|"Cannot save. Nothing is selected."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|console
operator|->
name|file_dialog
condition|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|console
operator|->
name|file_dialog
operator|=
name|gtk_file_chooser_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Save Error Log to File"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GTK_FILE_CHOOSER_ACTION_SAVE
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
literal|"_Save"
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
name|GTK_RESPONSE_OK
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
name|console
operator|->
name|save_selection
operator|=
name|selection
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|console
operator|->
name|file_dialog
argument_list|)
expr_stmt|;
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|GTK_WIDGET
argument_list|(
name|console
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-save-errors"
argument_list|)
expr_stmt|;
name|gtk_file_chooser_set_do_overwrite_confirmation
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|error_console_save_response
argument_list|)
argument_list|,
name|console
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
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
name|gimp_help_connect
argument_list|(
name|dialog
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_ERRORS_DIALOG
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|console
operator|->
name|file_dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|error_console_highlight_error_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|error_console_highlight_error_cmd_callback
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
name|GimpErrorConsole
modifier|*
name|console
init|=
name|GIMP_ERROR_CONSOLE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gboolean
name|active
init|=
name|g_variant_get_boolean
argument_list|(
name|value
argument_list|)
decl_stmt|;
name|console
operator|->
name|highlight
index|[
name|GIMP_MESSAGE_ERROR
index|]
operator|=
name|active
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|error_console_highlight_warning_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|error_console_highlight_warning_cmd_callback
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
name|GimpErrorConsole
modifier|*
name|console
init|=
name|GIMP_ERROR_CONSOLE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gboolean
name|active
init|=
name|g_variant_get_boolean
argument_list|(
name|value
argument_list|)
decl_stmt|;
name|console
operator|->
name|highlight
index|[
name|GIMP_MESSAGE_WARNING
index|]
operator|=
name|active
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|error_console_highlight_info_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|error_console_highlight_info_cmd_callback
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
name|GimpErrorConsole
modifier|*
name|console
init|=
name|GIMP_ERROR_CONSOLE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gboolean
name|active
init|=
name|g_variant_get_boolean
argument_list|(
name|value
argument_list|)
decl_stmt|;
name|console
operator|->
name|highlight
index|[
name|GIMP_MESSAGE_INFO
index|]
operator|=
name|active
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|error_console_save_response (GtkWidget * dialog,gint response_id,GimpErrorConsole * console)
name|error_console_save_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpErrorConsole
modifier|*
name|console
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GFile
modifier|*
name|file
init|=
name|gtk_file_chooser_get_file
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_text_buffer_save
argument_list|(
name|GIMP_TEXT_BUFFER
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|)
argument_list|,
name|file
argument_list|,
name|console
operator|->
name|save_selection
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|console
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
literal|"Error writing file '%s':\n%s"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
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
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

