begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* docindexif.c - Interface file for the docindex for gimp.  *  * Copyright (C) 1998 Chris Lahey.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2, or (at your option)  * any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  */
end_comment

begin_include
include|#
directive|include
file|<ctype.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"docindex.h"
end_include

begin_include
include|#
directive|include
file|"docindexif.h"
end_include

begin_include
include|#
directive|include
file|"fileops.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function
name|void
DECL|function|raise_if_match (gpointer data,gpointer user_data)
name|raise_if_match
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
init|=
name|GIMP_IMAGE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|struct
name|bool_char_pair
modifier|*
name|pair
init|=
operator|(
expr|struct
name|bool_char_pair
operator|*
operator|)
name|user_data
decl_stmt|;
if|if
condition|(
operator|(
operator|!
name|pair
operator|->
name|boole
operator|)
operator|&&
name|gimage
operator|->
name|has_filename
condition|)
if|if
condition|(
name|strcmp
argument_list|(
name|pair
operator|->
name|string
argument_list|,
name|gimage
operator|->
name|filename
argument_list|)
operator|==
literal|0
condition|)
block|{
name|pair
operator|->
name|boole
operator|=
name|TRUE
expr_stmt|;
comment|/* gdk_raise_window( NULL, gimage-> ); */
comment|/* FIXME */
block|}
block|}
end_function

begin_function
name|void
DECL|function|open_or_raise (gchar * file_name)
name|open_or_raise
parameter_list|(
name|gchar
modifier|*
name|file_name
parameter_list|)
block|{
name|struct
name|bool_char_pair
name|pair
decl_stmt|;
name|pair
operator|.
name|boole
operator|=
name|FALSE
expr_stmt|;
name|pair
operator|.
name|string
operator|=
name|file_name
expr_stmt|;
name|gimage_foreach
argument_list|(
name|raise_if_match
argument_list|,
operator|&
name|pair
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pair
operator|.
name|boole
condition|)
block|{
name|file_open
argument_list|(
name|file_name
argument_list|,
name|file_name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|exit_from_go ()
name|exit_from_go
parameter_list|()
block|{
return|return
name|FALSE
return|;
block|}
end_function

begin_function
DECL|function|open_file_in_position (gchar * filename,gint position)
name|void
name|open_file_in_position
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint
name|position
parameter_list|)
block|{
name|file_open
argument_list|(
name|filename
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|create_idea_menu ()
name|GtkMenuFactory
modifier|*
name|create_idea_menu
parameter_list|()
block|{
return|return
name|NULL
return|;
block|}
end_function

begin_function
DECL|function|create_idea_toolbar ()
name|GtkWidget
modifier|*
name|create_idea_toolbar
parameter_list|()
block|{
name|GtkWidget
modifier|*
name|toolbar
decl_stmt|;
name|toolbar
operator|=
name|gtk_toolbar_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
name|GTK_TOOLBAR_BOTH
argument_list|)
expr_stmt|;
name|gtk_toolbar_set_button_relief
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|GTK_RELIEF_NONE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toolbar
argument_list|)
expr_stmt|;
name|gtk_toolbar_append_item
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Open"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Open a file"
argument_list|)
argument_list|,
literal|"Toolbar/Open"
argument_list|,
name|NULL
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|file_open_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_toolbar_append_item
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Up"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Move the selected entry up in the index"
argument_list|)
argument_list|,
literal|"Toolbar/Up"
argument_list|,
name|NULL
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|idea_up_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_toolbar_append_item
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Down"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Move the selected entry down in the index"
argument_list|)
argument_list|,
literal|"Toolbar/Down"
argument_list|,
name|NULL
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|idea_down_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_toolbar_append_item
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Remove"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Remove the selected entry from the index"
argument_list|)
argument_list|,
literal|"Toolbar/Remove"
argument_list|,
name|NULL
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|idea_remove_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_toolbar_append_item
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Close"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Close the Document Index"
argument_list|)
argument_list|,
literal|"Toolbar/Hide"
argument_list|,
name|NULL
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|idea_hide_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|toolbar
return|;
block|}
end_function

begin_function
DECL|function|append2 (gchar * string1,gboolean del1,gchar * string2,gboolean del2)
name|gchar
modifier|*
name|append2
parameter_list|(
name|gchar
modifier|*
name|string1
parameter_list|,
name|gboolean
name|del1
parameter_list|,
name|gchar
modifier|*
name|string2
parameter_list|,
name|gboolean
name|del2
parameter_list|)
block|{
name|gchar
modifier|*
name|newstring
init|=
name|g_strconcat
argument_list|(
name|string1
argument_list|,
name|string2
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|del1
condition|)
name|g_free
argument_list|(
name|string1
argument_list|)
expr_stmt|;
if|if
condition|(
name|del2
condition|)
name|g_free
argument_list|(
name|string2
argument_list|)
expr_stmt|;
return|return
name|newstring
return|;
block|}
end_function

begin_function
name|gint
DECL|function|getinteger (FILE * fp)
name|getinteger
parameter_list|(
name|FILE
modifier|*
name|fp
parameter_list|)
block|{
name|gchar
name|nextchar
decl_stmt|;
name|gint
name|response
init|=
literal|0
decl_stmt|;
name|gboolean
name|negative
init|=
name|FALSE
decl_stmt|;
while|while
condition|(
name|isspace
argument_list|(
name|nextchar
operator|=
name|fgetc
argument_list|(
name|fp
argument_list|)
argument_list|)
condition|)
comment|/* empty statement */
empty_stmt|;
if|if
condition|(
name|nextchar
operator|==
literal|'-'
condition|)
block|{
name|negative
operator|=
name|TRUE
expr_stmt|;
while|while
condition|(
name|isspace
argument_list|(
name|nextchar
operator|=
name|fgetc
argument_list|(
name|fp
argument_list|)
argument_list|)
condition|)
comment|/* empty statement */
empty_stmt|;
block|}
for|for
control|(
init|;
literal|'0'
operator|<=
name|nextchar
operator|&&
literal|'9'
operator|>=
name|nextchar
condition|;
name|nextchar
operator|=
name|fgetc
argument_list|(
name|fp
argument_list|)
control|)
block|{
name|response
operator|*=
literal|10
expr_stmt|;
name|response
operator|+=
name|nextchar
operator|-
literal|'0'
expr_stmt|;
block|}
for|for
control|(
init|;
name|isspace
argument_list|(
name|nextchar
argument_list|)
condition|;
name|nextchar
operator|=
name|fgetc
argument_list|(
name|fp
argument_list|)
control|)
comment|/* empty statement */
empty_stmt|;
name|ungetc
argument_list|(
name|nextchar
argument_list|,
name|fp
argument_list|)
expr_stmt|;
if|if
condition|(
name|negative
condition|)
name|response
operator|=
operator|-
name|response
expr_stmt|;
return|return
name|response
return|;
block|}
end_function

begin_function
name|void
DECL|function|clear_white (FILE * fp)
name|clear_white
parameter_list|(
name|FILE
modifier|*
name|fp
parameter_list|)
block|{
name|gint
name|nextchar
decl_stmt|;
while|while
condition|(
name|isspace
argument_list|(
name|nextchar
operator|=
name|fgetc
argument_list|(
name|fp
argument_list|)
argument_list|)
condition|)
comment|/* empty statement */
empty_stmt|;
if|if
condition|(
name|nextchar
operator|!=
name|EOF
condition|)
name|ungetc
argument_list|(
name|nextchar
argument_list|,
name|fp
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* reset_usize  *  A callback so that the window can be resized smaller. */
end_comment

begin_function
name|gint
DECL|function|reset_usize (gpointer data)
name|reset_usize
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_widget_set_usize
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|make_idea_window (gint x,gint y)
name|make_idea_window
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|,
modifier|*
name|menu
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_win
decl_stmt|;
name|GtkWidget
modifier|*
name|toolbar
decl_stmt|;
name|GtkAccelGroup
modifier|*
name|accel
decl_stmt|;
comment|/* malloc idea_manager */
name|ideas
operator|=
name|g_malloc0
argument_list|(
sizeof|sizeof
argument_list|(
name|idea_manager
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Setup tree */
name|ideas
operator|->
name|tree
operator|=
name|gtk_tree_new
argument_list|()
expr_stmt|;
name|gtk_tree_set_selection_mode
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
argument_list|,
name|GTK_SELECTION_BROWSE
argument_list|)
expr_stmt|;
comment|/* Setup scrolled window */
name|scrolled_win
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
name|scrolled_win
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_ALWAYS
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_add_with_viewport
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|ideas
operator|->
name|tree
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
expr_stmt|;
comment|/* allocate the window and attach the menu */
name|ideas
operator|->
name|window
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_TOPLEVEL
argument_list|)
expr_stmt|;
name|ideas
operator|->
name|menubar
operator|=
name|create_idea_menu
argument_list|(
name|ideas
argument_list|)
expr_stmt|;
if|if
condition|(
name|ideas
operator|->
name|menubar
condition|)
block|{
name|menu
operator|=
name|ideas
operator|->
name|menubar
operator|->
name|widget
expr_stmt|;
comment|/* Setup accelerator (hotkey) table */
name|accel
operator|=
name|ideas
operator|->
name|menubar
operator|->
name|accel_group
expr_stmt|;
comment|/* Add accelerators to window widget */
name|gtk_window_add_accel_group
argument_list|(
name|GTK_WINDOW
argument_list|(
name|ideas
operator|->
name|window
argument_list|)
argument_list|,
name|accel
argument_list|)
expr_stmt|;
block|}
else|else
name|menu
operator|=
name|NULL
expr_stmt|;
comment|/* Setup the status bar */
name|ideas
operator|->
name|status
operator|=
name|gtk_statusbar_new
argument_list|()
expr_stmt|;
name|ideas
operator|->
name|contextid
operator|=
name|gtk_statusbar_get_context_id
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|ideas
operator|->
name|status
argument_list|)
argument_list|,
literal|"main context"
argument_list|)
expr_stmt|;
comment|/* Setup the toolbar */
name|toolbar
operator|=
name|create_idea_toolbar
argument_list|()
expr_stmt|;
comment|/* Setup a vbox to contain the menu */
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu
condition|)
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|menu
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|scrolled_win
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|ideas
operator|->
name|status
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu
condition|)
name|gtk_widget_show
argument_list|(
name|menu
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scrolled_win
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|ideas
operator|->
name|status
argument_list|)
expr_stmt|;
comment|/* Set the GOWindow title */
name|ideas
operator|->
name|title
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"Document Index"
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Set the GtkWindow title */
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|ideas
operator|->
name|window
argument_list|)
argument_list|,
name|ideas
operator|->
name|title
argument_list|)
expr_stmt|;
comment|/* Set the initial status message */
name|gtk_statusbar_push
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|ideas
operator|->
name|status
argument_list|)
argument_list|,
name|ideas
operator|->
name|contextid
argument_list|,
name|_
argument_list|(
literal|"GTK successfully started"
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Connect the signals */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|ideas
operator|->
name|window
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|idea_window_delete_event_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Add the main vbox to the window */
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|ideas
operator|->
name|window
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|ideas
operator|->
name|window
argument_list|)
argument_list|,
name|main_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|docindex_configure_drop_on_widget
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
expr_stmt|;
comment|/* Load and Show window */
name|load_idea_manager
argument_list|(
name|ideas
argument_list|)
expr_stmt|;
comment|/* Set the position of the window if it was requested */
if|if
condition|(
name|x
operator|>=
literal|0
operator|&&
name|y
operator|>=
literal|0
condition|)
name|gtk_widget_set_uposition
argument_list|(
name|ideas
operator|->
name|window
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
comment|/*  Connect the "F1" help key  */
name|gimp_help_connect_help_accel
argument_list|(
name|ideas
operator|->
name|window
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/document_index.html"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

