begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextEditor  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
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
file|"widgets/gimptexteditor.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|TextEditorData
typedef|typedef
name|struct
name|_TextEditorData
name|TextEditorData
typedef|;
end_typedef

begin_struct
DECL|struct|_TextEditorData
struct|struct
name|_TextEditorData
block|{
DECL|member|buffer
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
DECL|member|editor
name|GtkWidget
modifier|*
name|editor
decl_stmt|;
DECL|member|filesel
name|GtkWidget
modifier|*
name|filesel
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_text_editor_load
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|TextEditorData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_editor_load_ok
parameter_list|(
name|TextEditorData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_text_editor_load_file
parameter_list|(
name|GtkTextBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_editor_clear
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|TextEditorData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_text_editor_new (const gchar * title,GtkTextBuffer * buffer)
name|gimp_text_editor_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|GtkTextBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|editor
decl_stmt|;
name|GtkWidget
modifier|*
name|toolbar
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_window
decl_stmt|;
name|GtkWidget
modifier|*
name|text_view
decl_stmt|;
name|TextEditorData
modifier|*
name|data
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_TEXT_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|=
name|gimp_dialog_new
argument_list|(
name|title
argument_list|,
literal|"text_editor"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/text_editor.html"
argument_list|,
name|GTK_WIN_POS_NONE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|=
name|g_new0
argument_list|(
name|TextEditorData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|data
operator|->
name|buffer
operator|=
name|buffer
expr_stmt|;
name|data
operator|->
name|editor
operator|=
name|editor
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_free
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gtk_dialog_set_has_separator
argument_list|(
name|GTK_DIALOG
argument_list|(
name|editor
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|toolbar
operator|=
name|gtk_toolbar_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|editor
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|toolbar
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
name|toolbar
argument_list|)
expr_stmt|;
name|gtk_toolbar_insert_stock
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|GTK_STOCK_OPEN
argument_list|,
name|_
argument_list|(
literal|"Load Text from File"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_text_editor_load
argument_list|)
argument_list|,
name|data
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toolbar_insert_stock
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|GTK_STOCK_CLEAR
argument_list|,
name|_
argument_list|(
literal|"Clear all Text"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_text_editor_clear
argument_list|)
argument_list|,
name|data
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|scrolled_window
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|editor
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|scrolled_window
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
name|scrolled_window
argument_list|)
expr_stmt|;
name|text_view
operator|=
name|gtk_text_view_new_with_buffer
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|text_view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|text_view
argument_list|)
expr_stmt|;
return|return
name|editor
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_editor_load (GtkWidget * widget,TextEditorData * data)
name|gimp_text_editor_load
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|TextEditorData
modifier|*
name|data
parameter_list|)
block|{
name|GtkFileSelection
modifier|*
name|filesel
decl_stmt|;
if|if
condition|(
name|data
operator|->
name|filesel
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|data
operator|->
name|filesel
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|filesel
operator|=
name|GTK_FILE_SELECTION
argument_list|(
name|gtk_file_selection_new
argument_list|(
name|_
argument_list|(
literal|"Open Text File (UTF-8)"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesel
argument_list|)
argument_list|,
literal|"gimp-text-load-file"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesel
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|filesel
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|filesel
operator|->
name|button_area
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesel
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|data
operator|->
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_destroy_with_parent
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesel
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|filesel
operator|->
name|ok_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_text_editor_load_ok
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|filesel
operator|->
name|cancel_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|filesel
argument_list|)
expr_stmt|;
name|data
operator|->
name|filesel
operator|=
name|GTK_WIDGET
argument_list|(
name|filesel
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|filesel
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|data
operator|->
name|filesel
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|filesel
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_editor_load_ok (TextEditorData * data)
name|gimp_text_editor_load_ok
parameter_list|(
name|TextEditorData
modifier|*
name|data
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|gtk_file_selection_get_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|data
operator|->
name|filesel
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_text_editor_load_file
argument_list|(
name|data
operator|->
name|buffer
argument_list|,
name|filename
argument_list|)
condition|)
name|gtk_widget_destroy
argument_list|(
name|data
operator|->
name|filesel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_text_editor_load_file (GtkTextBuffer * buffer,const gchar * filename)
name|gimp_text_editor_load_file
parameter_list|(
name|GtkTextBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|FILE
modifier|*
name|file
decl_stmt|;
name|gchar
name|buf
index|[
literal|2048
index|]
decl_stmt|;
name|gint
name|remaining
init|=
literal|0
decl_stmt|;
name|GtkTextIter
name|iter
decl_stmt|;
name|file
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Error opening file '%s': %s"
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
return|return
name|FALSE
return|;
block|}
name|gtk_text_buffer_set_text
argument_list|(
name|buffer
argument_list|,
literal|""
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_text_buffer_get_iter_at_offset
argument_list|(
name|buffer
argument_list|,
operator|&
name|iter
argument_list|,
literal|0
argument_list|)
expr_stmt|;
while|while
condition|(
operator|!
name|feof
argument_list|(
name|file
argument_list|)
condition|)
block|{
specifier|const
name|char
modifier|*
name|leftover
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|gint
name|to_read
init|=
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
operator|-
name|remaining
operator|-
literal|1
decl_stmt|;
name|count
operator|=
name|fread
argument_list|(
name|buf
operator|+
name|remaining
argument_list|,
literal|1
argument_list|,
name|to_read
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|buf
index|[
name|count
operator|+
name|remaining
index|]
operator|=
literal|'\0'
expr_stmt|;
name|g_utf8_validate
argument_list|(
name|buf
argument_list|,
name|count
operator|+
name|remaining
argument_list|,
operator|&
name|leftover
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert
argument_list|(
name|buffer
argument_list|,
operator|&
name|iter
argument_list|,
name|buf
argument_list|,
name|leftover
operator|-
name|buf
argument_list|)
expr_stmt|;
name|remaining
operator|=
operator|(
name|buf
operator|+
name|remaining
operator|+
name|count
operator|)
operator|-
name|leftover
expr_stmt|;
name|g_memmove
argument_list|(
name|buf
argument_list|,
name|leftover
argument_list|,
name|remaining
argument_list|)
expr_stmt|;
if|if
condition|(
name|remaining
operator|>
literal|6
operator|||
name|count
operator|<
name|to_read
condition|)
break|break;
block|}
if|if
condition|(
name|remaining
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Invalid UTF-8 data in file '%s'."
argument_list|)
argument_list|,
name|filename
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
DECL|function|gimp_text_editor_clear (GtkWidget * widget,TextEditorData * data)
name|gimp_text_editor_clear
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|TextEditorData
modifier|*
name|data
parameter_list|)
block|{
name|gtk_text_buffer_set_text
argument_list|(
name|data
operator|->
name|buffer
argument_list|,
literal|""
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

