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
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpradioaction.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptextbuffer.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptexteditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"text-editor-commands.h"
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
name|text_editor_load_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpTextEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|text_editor_load_cmd_callback (GtkAction * action,gpointer data)
name|text_editor_load_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTextEditor
modifier|*
name|editor
init|=
name|GIMP_TEXT_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|editor
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
name|editor
operator|->
name|file_dialog
operator|=
name|gtk_file_chooser_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Open Text File (UTF-8)"
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_FILE_CHOOSER_ACTION_OPEN
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
literal|"_Open"
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
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-text-load-file"
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
name|gtk_window_set_destroy_with_parent
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|TRUE
argument_list|)
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
name|editor
operator|->
name|file_dialog
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
name|text_editor_load_response
argument_list|)
argument_list|,
name|editor
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
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|editor
operator|->
name|file_dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|text_editor_clear_cmd_callback (GtkAction * action,gpointer data)
name|text_editor_clear_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTextEditor
modifier|*
name|editor
init|=
name|GIMP_TEXT_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
name|buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_text_buffer_set_text
argument_list|(
name|buffer
argument_list|,
literal|""
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|text_editor_direction_cmd_callback (GtkAction * action,GtkAction * current,gpointer data)
name|text_editor_direction_cmd_callback
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
name|GimpTextEditor
modifier|*
name|editor
init|=
name|GIMP_TEXT_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gint
name|value
decl_stmt|;
name|value
operator|=
name|gimp_radio_action_get_current_value
argument_list|(
name|GIMP_RADIO_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_text_editor_set_direction
argument_list|(
name|editor
argument_list|,
operator|(
name|GimpTextDirection
operator|)
name|value
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
DECL|function|text_editor_load_response (GtkWidget * dialog,gint response_id,GimpTextEditor * editor)
name|text_editor_load_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpTextEditor
modifier|*
name|editor
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
name|GFile
modifier|*
name|file
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|file
operator|=
name|gtk_file_chooser_get_file
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
name|GIMP_TEXT_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|file
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|editor
operator|->
name|ui_manager
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
name|gtk_widget_hide
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

