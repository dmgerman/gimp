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
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"window-commands.h"
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
DECL|function|window_close_cmd_callback (GimpAction * action,gpointer data)
name|window_close_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_widget_is_toplevel
argument_list|(
name|widget
argument_list|)
condition|)
name|widget
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
operator|&&
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GdkEvent
modifier|*
name|event
init|=
name|gdk_event_new
argument_list|(
name|GDK_DELETE
argument_list|)
decl_stmt|;
name|event
operator|->
name|any
operator|.
name|window
operator|=
name|g_object_ref
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|event
operator|->
name|any
operator|.
name|send_event
operator|=
name|TRUE
expr_stmt|;
name|gtk_main_do_event
argument_list|(
name|event
argument_list|)
expr_stmt|;
name|gdk_event_free
argument_list|(
name|event
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|window_open_display_cmd_callback (GimpAction * action,gpointer data)
name|window_open_display_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
literal|"Open Display"
argument_list|,
name|GIMP_ICON_WILBER_EEK
argument_list|,
name|widget
argument_list|,
name|GTK_DIALOG_MODAL
argument_list|,
name|NULL
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
literal|"_OK"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
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
name|gimp_message_box_set_primary_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
literal|"Experimental multi-display stuff!\n"
literal|"Click OK and have fun crashing GIMP..."
argument_list|)
expr_stmt|;
name|gimp_message_box_set_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
literal|"Please enter the name of the new display:"
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_entry_set_activates_default
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|)
argument_list|,
name|entry
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|gtk_widget_show_all
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
while|while
condition|(
name|gtk_dialog_run
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|gchar
modifier|*
name|screen_name
decl_stmt|;
name|screen_name
operator|=
name|gtk_editable_get_chars
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|screen_name
argument_list|,
literal|""
argument_list|)
condition|)
block|{
name|GdkDisplay
modifier|*
name|display
decl_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|dialog
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|display
operator|=
name|gdk_display_open
argument_list|(
name|screen_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|display
condition|)
name|gimp_message_box_set_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
literal|"Can't open display '%s'. "
literal|"Please try another one:"
argument_list|,
name|screen_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|screen_name
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|dialog
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|display
condition|)
break|break;
block|}
name|gtk_widget_grab_focus
argument_list|(
name|entry
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

begin_function
name|void
DECL|function|window_move_to_screen_cmd_callback (GimpAction * action,GimpAction * current,gpointer data)
name|window_move_to_screen_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GimpAction
modifier|*
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_widget_is_toplevel
argument_list|(
name|widget
argument_list|)
condition|)
name|widget
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|screen
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|current
argument_list|)
argument_list|,
literal|"screen"
argument_list|)
expr_stmt|;
if|if
condition|(
name|GDK_IS_SCREEN
argument_list|(
name|screen
argument_list|)
operator|&&
name|screen
operator|!=
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|widget
argument_list|)
argument_list|,
name|screen
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

