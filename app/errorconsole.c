begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * errorconsole.c - text window for collecting error messages  * Copyright (C) 1998 Nick Fetchak<nuke@bayside.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<dirent.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"commands.h"
end_include

begin_include
include|#
directive|include
file|"session.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|ERRORS_ALL
define|#
directive|define
name|ERRORS_ALL
value|0
end_define

begin_define
DECL|macro|ERRORS_SELECTION
define|#
directive|define
name|ERRORS_SELECTION
value|1
end_define

begin_function_decl
name|void
name|error_console_add
parameter_list|(
name|gchar
modifier|*
name|errormsg
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|error_console
specifier|static
name|GtkWidget
modifier|*
name|error_console
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|text
specifier|static
name|GtkWidget
modifier|*
name|text
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|error_console_close_callback (GtkWidget * widget,GdkEvent * event,gpointer data)
name|error_console_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_widget_hide
argument_list|(
name|error_console
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|error_console_free (void)
name|error_console_free
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|error_console
condition|)
name|session_get_window_info
argument_list|(
name|error_console
argument_list|,
operator|&
name|error_console_session_info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|error_console_write_file (gchar * path,gint textscope)
name|error_console_write_file
parameter_list|(
name|gchar
modifier|*
name|path
parameter_list|,
name|gint
name|textscope
parameter_list|)
block|{
name|gint
name|fd
decl_stmt|;
name|gint
name|text_length
decl_stmt|;
name|gint
name|bytes_written
decl_stmt|;
name|gchar
modifier|*
name|text_contents
decl_stmt|;
name|GtkText
modifier|*
name|gtext
decl_stmt|;
name|gtext
operator|=
name|GTK_TEXT
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|fd
operator|=
name|open
argument_list|(
name|path
argument_list|,
name|O_WRONLY
operator||
name|O_CREAT
operator||
name|O_APPEND
argument_list|,
name|S_IRUSR
operator||
name|S_IWUSR
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|==
operator|-
literal|1
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|textscope
operator|==
name|ERRORS_ALL
condition|)
block|{
name|text_contents
operator|=
name|gtk_editable_get_chars
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|text
argument_list|)
argument_list|,
literal|0
argument_list|,
name|gtk_text_get_length
argument_list|(
name|GTK_TEXT
argument_list|(
name|text
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|selection_start
decl_stmt|,
name|selection_end
decl_stmt|,
name|temp
decl_stmt|;
name|selection_start
operator|=
name|GTK_TEXT
argument_list|(
name|text
argument_list|)
operator|->
name|editable
operator|.
name|selection_start_pos
expr_stmt|;
name|selection_end
operator|=
name|GTK_TEXT
argument_list|(
name|text
argument_list|)
operator|->
name|editable
operator|.
name|selection_end_pos
expr_stmt|;
if|if
condition|(
name|selection_start
operator|>
name|selection_end
condition|)
block|{
name|temp
operator|=
name|selection_start
expr_stmt|;
name|selection_start
operator|=
name|selection_end
expr_stmt|;
name|selection_end
operator|=
name|temp
expr_stmt|;
block|}
name|text_contents
operator|=
name|gtk_editable_get_chars
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|text
argument_list|)
argument_list|,
name|selection_start
argument_list|,
name|selection_end
argument_list|)
expr_stmt|;
block|}
name|text_length
operator|=
name|strlen
argument_list|(
name|text_contents
argument_list|)
expr_stmt|;
if|if
condition|(
name|text_contents
operator|&&
operator|(
name|text_length
operator|>
literal|0
operator|)
condition|)
block|{
name|bytes_written
operator|=
name|write
argument_list|(
name|fd
argument_list|,
name|text_contents
argument_list|,
name|text_length
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text_contents
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
if|if
condition|(
name|bytes_written
operator|!=
name|text_length
condition|)
return|return
name|FALSE
return|;
else|else
return|return
name|TRUE
return|;
block|}
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|error_console_file_ok_callback (GtkWidget * widget,gpointer data)
name|error_console_file_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|filesel
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gint
name|textscope
decl_stmt|;
name|filesel
operator|=
operator|(
name|GtkWidget
operator|*
operator|)
name|data
expr_stmt|;
name|filename
operator|=
name|gtk_file_selection_get_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|filesel
argument_list|)
argument_list|)
expr_stmt|;
name|textscope
operator|=
operator|(
name|gint
operator|)
name|gtk_object_get_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|filesel
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|error_console_write_file
argument_list|(
name|filename
argument_list|,
name|textscope
argument_list|)
condition|)
block|{
name|GString
modifier|*
name|string
decl_stmt|;
name|string
operator|=
name|g_string_new
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|g_string_sprintf
argument_list|(
name|string
argument_list|,
name|_
argument_list|(
literal|"Error opening file %s: %s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
name|string
operator|->
name|str
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|string
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
name|gtk_widget_destroy
argument_list|(
name|filesel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|error_console_menu_callback (gint textscope)
name|error_console_menu_callback
parameter_list|(
name|gint
name|textscope
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|filesel
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|GTK_TEXT
argument_list|(
name|text
argument_list|)
operator|->
name|editable
operator|.
name|has_selection
operator|)
operator|&&
operator|(
name|textscope
operator|==
name|ERRORS_SELECTION
operator|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Can't save, nothing selected!"
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|filesel
operator|=
name|gtk_file_selection_new
argument_list|(
name|_
argument_list|(
literal|"Save error log to file..."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesel
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesel
argument_list|)
argument_list|,
literal|"save_errors"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|filesel
argument_list|)
operator|->
name|cancel_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gtk_widget_destroy
argument_list|,
name|GTK_OBJECT
argument_list|(
name|filesel
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_set_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|filesel
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|textscope
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|filesel
argument_list|)
operator|->
name|ok_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|error_console_file_ok_callback
argument_list|,
name|filesel
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|filesel
argument_list|)
operator|->
name|cancel_button
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gtk_widget_destroy
argument_list|,
name|GTK_OBJECT
argument_list|(
name|filesel
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|filesel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|text_clicked_callback (GtkWidget * widget,GdkEventButton * event,gpointer data)
name|text_clicked_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkMenu
modifier|*
name|menu
init|=
operator|(
name|GtkMenu
operator|*
operator|)
name|data
decl_stmt|;
name|GtkText
modifier|*
name|gtext
decl_stmt|;
name|gtext
operator|=
name|GTK_TEXT
argument_list|(
name|text
argument_list|)
expr_stmt|;
if|if
condition|(
name|event
operator|->
name|button
operator|==
literal|3
condition|)
block|{
name|gtk_signal_emit_stop_by_name
argument_list|(
name|GTK_OBJECT
argument_list|(
name|text
argument_list|)
argument_list|,
literal|"button_press_event"
argument_list|)
expr_stmt|;
name|gtk_menu_popup
argument_list|(
name|menu
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|event
operator|->
name|button
argument_list|,
name|event
operator|->
name|time
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|error_console_create_window (void)
name|error_console_create_window
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|vscrollbar
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|GtkWidget
modifier|*
name|menuitem
decl_stmt|;
name|error_console
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|error_console
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"GIMP Error console"
argument_list|)
argument_list|)
expr_stmt|;
name|session_set_window_geometry
argument_list|(
name|error_console
argument_list|,
operator|&
name|error_console_session_info
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* The next line should disappear when setting the size works in SM */
name|gtk_widget_set_usize
argument_list|(
name|error_console
argument_list|,
literal|250
argument_list|,
literal|300
argument_list|)
expr_stmt|;
name|gtk_window_set_policy
argument_list|(
name|GTK_WINDOW
argument_list|(
name|error_console
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|error_console
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|error_console_close_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|error_console
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|error_console
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
comment|/*  Action area  */
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Close"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|error_console_close_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|error_console
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|menu
operator|=
name|gtk_menu_new
argument_list|()
expr_stmt|;
name|menuitem
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Write all errors to file..."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menuitem
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menuitem
argument_list|)
argument_list|,
literal|"activate"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|error_console_menu_callback
argument_list|,
operator|(
name|gpointer
operator|)
name|ERRORS_ALL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menuitem
argument_list|)
expr_stmt|;
name|menuitem
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Write selection to file..."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menuitem
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menuitem
argument_list|)
argument_list|,
literal|"activate"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|error_console_menu_callback
argument_list|,
operator|(
name|gpointer
operator|)
name|ERRORS_SELECTION
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menuitem
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|error_console
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|table
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
comment|/*  The output text widget  */
name|text
operator|=
name|gtk_text_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_text_set_editable
argument_list|(
name|GTK_TEXT
argument_list|(
name|text
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_text_set_word_wrap
argument_list|(
name|GTK_TEXT
argument_list|(
name|text
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|text
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|text
argument_list|,
name|GDK_BUTTON_PRESS_MASK
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|text
argument_list|)
argument_list|,
literal|"button_press_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|text_clicked_callback
argument_list|)
argument_list|,
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|vscrollbar
operator|=
name|gtk_vscrollbar_new
argument_list|(
name|GTK_TEXT
argument_list|(
name|text
argument_list|)
operator|->
name|vadj
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|vscrollbar
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vscrollbar
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|error_console
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|error_console_add (gchar * errormsg)
name|error_console_add
parameter_list|(
name|gchar
modifier|*
name|errormsg
parameter_list|)
block|{
if|if
condition|(
operator|!
name|error_console
condition|)
block|{
name|error_console_create_window
argument_list|()
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|error_console
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|error_console
argument_list|)
expr_stmt|;
else|else
name|gdk_window_raise
argument_list|(
name|error_console
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|errormsg
condition|)
block|{
name|gtk_text_insert
argument_list|(
name|GTK_TEXT
argument_list|(
name|text
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|errormsg
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_text_insert
argument_list|(
name|GTK_TEXT
argument_list|(
name|text
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"\n"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

