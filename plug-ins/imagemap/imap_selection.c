begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2003 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|GTK_DISABLE_DEPRECATED
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"imap_commands.h"
end_include

begin_include
include|#
directive|include
file|"imap_edit_area_info.h"
end_include

begin_include
include|#
directive|include
file|"imap_main.h"
end_include

begin_include
include|#
directive|include
file|"imap_misc.h"
end_include

begin_include
include|#
directive|include
file|"imap_selection.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function
specifier|static
name|void
DECL|function|set_buttons (Selection_t * data)
name|set_buttons
parameter_list|(
name|Selection_t
modifier|*
name|data
parameter_list|)
block|{
if|if
condition|(
name|data
operator|->
name|selected_child
condition|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|arrow_up
argument_list|,
operator|(
name|data
operator|->
name|selected_row
operator|)
condition|?
name|TRUE
else|:
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|selected_row
operator|<
name|GTK_CLIST
argument_list|(
name|data
operator|->
name|list
argument_list|)
operator|->
name|rows
operator|-
literal|1
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|arrow_down
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|arrow_down
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|remove
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|edit
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|arrow_up
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|arrow_down
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|remove
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|edit
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_row_cb (GtkWidget * widget,gint row,gint column,GdkEventButton * event,Selection_t * data)
name|select_row_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|column
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|Selection_t
modifier|*
name|data
parameter_list|)
block|{
name|data
operator|->
name|selected_child
operator|=
name|widget
expr_stmt|;
name|data
operator|->
name|selected_row
operator|=
name|row
expr_stmt|;
name|set_buttons
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|select_lock
condition|)
block|{
name|data
operator|->
name|select_lock
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|Object_t
modifier|*
name|obj
init|=
name|gtk_clist_get_row_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|data
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|)
decl_stmt|;
name|Command_t
modifier|*
name|command
decl_stmt|;
comment|/* Note: event can be NULL if select_row_cb is called as a result of 	 a key press! */
if|if
condition|(
name|event
operator|&&
name|event
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
name|command
operator|=
name|select_command_new
argument_list|(
name|obj
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|Command_t
modifier|*
name|sub_command
decl_stmt|;
name|command
operator|=
name|subcommand_start
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|sub_command
operator|=
name|unselect_all_command_new
argument_list|(
name|data
operator|->
name|object_list
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|command_add_subcommand
argument_list|(
name|command
argument_list|,
name|sub_command
argument_list|)
expr_stmt|;
name|sub_command
operator|=
name|select_command_new
argument_list|(
name|obj
argument_list|)
expr_stmt|;
name|command_add_subcommand
argument_list|(
name|command
argument_list|,
name|sub_command
argument_list|)
expr_stmt|;
name|command_set_name
argument_list|(
name|command
argument_list|,
name|sub_command
operator|->
name|name
argument_list|)
expr_stmt|;
name|subcommand_end
argument_list|()
expr_stmt|;
block|}
name|command_execute
argument_list|(
name|command
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|unselect_row_cb (GtkWidget * widget,gint row,gint column,GdkEventButton * event,Selection_t * data)
name|unselect_row_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|column
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|Selection_t
modifier|*
name|data
parameter_list|)
block|{
if|if
condition|(
name|data
operator|->
name|unselect_lock
condition|)
block|{
name|data
operator|->
name|unselect_lock
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|Object_t
modifier|*
name|obj
init|=
name|gtk_clist_get_row_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|data
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|)
decl_stmt|;
name|Command_t
modifier|*
name|command
decl_stmt|;
name|command
operator|=
name|unselect_command_new
argument_list|(
name|obj
argument_list|)
expr_stmt|;
name|command_execute
argument_list|(
name|command
argument_list|)
expr_stmt|;
block|}
name|data
operator|->
name|selected_child
operator|=
name|NULL
expr_stmt|;
name|set_buttons
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|row_move_cb (GtkWidget * widget,gint src,gint des)
name|row_move_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|src
parameter_list|,
name|gint
name|des
parameter_list|)
block|{
name|printf
argument_list|(
literal|"move: %d %d\n"
argument_list|,
name|src
argument_list|,
name|des
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|doubleclick
specifier|static
name|gboolean
name|doubleclick
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|gboolean
DECL|function|button_press_cb (GtkWidget * widget,GdkEventButton * event,Selection_t * data)
name|button_press_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|Selection_t
modifier|*
name|data
parameter_list|)
block|{
if|if
condition|(
name|event
operator|->
name|button
operator|==
literal|1
condition|)
block|{
if|if
condition|(
name|doubleclick
condition|)
block|{
name|gint
name|row
decl_stmt|,
name|column
decl_stmt|;
name|doubleclick
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|gtk_clist_get_selection_info
argument_list|(
name|GTK_CLIST
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
name|event
operator|->
name|x
argument_list|,
operator|(
name|gint
operator|)
name|event
operator|->
name|y
argument_list|,
operator|&
name|row
argument_list|,
operator|&
name|column
argument_list|)
condition|)
block|{
name|Object_t
modifier|*
name|obj
init|=
name|gtk_clist_get_row_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|data
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|)
decl_stmt|;
name|object_edit
argument_list|(
name|obj
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|doubleclick
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|button_release_cb (GtkWidget * widget,GdkEventButton * event,gpointer data)
name|button_release_cb
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
if|if
condition|(
name|event
operator|->
name|button
operator|==
literal|1
condition|)
name|doubleclick
operator|=
name|FALSE
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|selection_command (GtkWidget * widget,gpointer data)
name|selection_command
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|CommandFactory_t
modifier|*
name|factory
init|=
operator|(
name|CommandFactory_t
operator|*
operator|)
name|data
decl_stmt|;
name|Command_t
modifier|*
name|command
init|=
call|(
modifier|*
name|factory
call|)
argument_list|()
decl_stmt|;
name|command_execute
argument_list|(
name|command
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|make_selection_toolbar (Selection_t * data)
name|make_selection_toolbar
parameter_list|(
name|Selection_t
modifier|*
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|toolbar
decl_stmt|;
name|toolbar
operator|=
name|gtk_toolbar_new
argument_list|()
expr_stmt|;
name|gtk_toolbar_set_style
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|GTK_TOOLBAR_ICONS
argument_list|)
expr_stmt|;
name|gtk_toolbar_set_orientation
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|GTK_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|toolbar
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|data
operator|->
name|arrow_up
operator|=
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|GTK_STOCK_GO_UP
argument_list|,
literal|"MoveUp"
argument_list|,
name|_
argument_list|(
literal|"Move Up"
argument_list|)
argument_list|,
name|selection_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_move_up
argument_list|)
expr_stmt|;
name|data
operator|->
name|arrow_down
operator|=
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|GTK_STOCK_GO_DOWN
argument_list|,
literal|"MoveDown"
argument_list|,
name|_
argument_list|(
literal|"Move Down"
argument_list|)
argument_list|,
name|selection_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_move_down
argument_list|)
expr_stmt|;
name|gtk_toolbar_append_space
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|edit
operator|=
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|GTK_STOCK_PROPERTIES
argument_list|,
literal|"Edit"
argument_list|,
name|_
argument_list|(
literal|"Edit"
argument_list|)
argument_list|,
name|selection_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_edit
argument_list|)
expr_stmt|;
name|gtk_toolbar_append_space
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|remove
operator|=
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|GTK_STOCK_DELETE
argument_list|,
literal|"Delete"
argument_list|,
name|_
argument_list|(
literal|"Delete"
argument_list|)
argument_list|,
name|selection_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_delete
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toolbar
argument_list|)
expr_stmt|;
return|return
name|toolbar
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|selection_update (Selection_t * selection,gint row,Object_t * obj)
name|selection_update
parameter_list|(
name|Selection_t
modifier|*
name|selection
parameter_list|,
name|gint
name|row
parameter_list|,
name|Object_t
modifier|*
name|obj
parameter_list|)
block|{
name|GdkBitmap
modifier|*
name|mask
decl_stmt|;
name|GdkPixmap
modifier|*
name|icon
init|=
name|object_get_icon
argument_list|(
name|obj
argument_list|,
name|selection
operator|->
name|list
argument_list|,
operator|&
name|mask
argument_list|)
decl_stmt|;
ifdef|#
directive|ifdef
name|_NOT_READY_YET_
name|gtk_clist_set_pixtext
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|,
literal|1
argument_list|,
name|obj
operator|->
name|url
argument_list|,
literal|8
argument_list|,
name|icon
argument_list|,
name|mask
argument_list|)
expr_stmt|;
else|#
directive|else
name|gtk_clist_set_text
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|,
literal|1
argument_list|,
name|obj
operator|->
name|url
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gtk_clist_set_text
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|,
literal|2
argument_list|,
name|obj
operator|->
name|target
argument_list|)
expr_stmt|;
name|gtk_clist_set_text
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|,
literal|3
argument_list|,
name|obj
operator|->
name|comment
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|selection_renumber (Selection_t * selection,gint row)
name|selection_renumber
parameter_list|(
name|Selection_t
modifier|*
name|selection
parameter_list|,
name|gint
name|row
parameter_list|)
block|{
for|for
control|(
init|;
name|row
operator|<
name|selection
operator|->
name|nr_rows
condition|;
name|row
operator|++
control|)
block|{
name|char
name|scratch
index|[
literal|16
index|]
decl_stmt|;
name|sprintf
argument_list|(
name|scratch
argument_list|,
literal|"%d"
argument_list|,
name|row
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gtk_clist_set_text
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|,
literal|0
argument_list|,
name|scratch
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|selection_set_selected (Selection_t * selection,gint row)
name|selection_set_selected
parameter_list|(
name|Selection_t
modifier|*
name|selection
parameter_list|,
name|gint
name|row
parameter_list|)
block|{
name|Object_t
modifier|*
name|obj
init|=
name|gtk_clist_get_row_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|)
decl_stmt|;
if|if
condition|(
name|obj
operator|->
name|selected
condition|)
block|{
name|selection
operator|->
name|select_lock
operator|=
name|TRUE
expr_stmt|;
name|gtk_clist_select_row
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|selection
operator|->
name|unselect_lock
operator|=
name|TRUE
expr_stmt|;
name|gtk_clist_unselect_row
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|object_added_cb (Object_t * obj,gpointer data)
name|object_added_cb
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Selection_t
modifier|*
name|selection
init|=
operator|(
name|Selection_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|row
init|=
name|object_get_position_in_list
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|char
name|scratch
index|[
literal|16
index|]
decl_stmt|;
name|gchar
modifier|*
name|text
index|[
literal|4
index|]
decl_stmt|;
name|selection
operator|->
name|nr_rows
operator|++
expr_stmt|;
name|text
index|[
literal|0
index|]
operator|=
name|scratch
expr_stmt|;
name|text
index|[
literal|1
index|]
operator|=
name|obj
operator|->
name|url
expr_stmt|;
name|text
index|[
literal|2
index|]
operator|=
name|obj
operator|->
name|target
expr_stmt|;
name|text
index|[
literal|3
index|]
operator|=
name|obj
operator|->
name|comment
expr_stmt|;
if|if
condition|(
name|row
operator|<
name|selection
operator|->
name|nr_rows
operator|-
literal|1
condition|)
block|{
name|sprintf
argument_list|(
name|scratch
argument_list|,
literal|"%d"
argument_list|,
name|row
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gtk_clist_insert
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|selection_renumber
argument_list|(
name|selection
argument_list|,
name|row
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|sprintf
argument_list|(
name|scratch
argument_list|,
literal|"%d"
argument_list|,
name|selection
operator|->
name|nr_rows
argument_list|)
expr_stmt|;
name|gtk_clist_append
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
block|}
name|selection_update
argument_list|(
name|selection
argument_list|,
name|row
argument_list|,
name|obj
argument_list|)
expr_stmt|;
name|gtk_clist_set_row_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|,
operator|(
name|gpointer
operator|)
name|obj
argument_list|)
expr_stmt|;
name|selection_set_selected
argument_list|(
name|selection
argument_list|,
name|row
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|selection_find_object (Selection_t * selection,Object_t * obj)
name|selection_find_object
parameter_list|(
name|Selection_t
modifier|*
name|selection
parameter_list|,
name|Object_t
modifier|*
name|obj
parameter_list|)
block|{
return|return
name|gtk_clist_find_row_from_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|obj
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|object_updated_cb (Object_t * obj,gpointer data)
name|object_updated_cb
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Selection_t
modifier|*
name|selection
init|=
operator|(
name|Selection_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|row
init|=
name|selection_find_object
argument_list|(
name|selection
argument_list|,
name|obj
argument_list|)
decl_stmt|;
name|selection_update
argument_list|(
name|selection
argument_list|,
name|row
argument_list|,
name|obj
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|object_removed_cb (Object_t * obj,gpointer data)
name|object_removed_cb
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Selection_t
modifier|*
name|selection
init|=
operator|(
name|Selection_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|row
init|=
name|selection_find_object
argument_list|(
name|selection
argument_list|,
name|obj
argument_list|)
decl_stmt|;
name|selection
operator|->
name|unselect_lock
operator|=
name|TRUE
expr_stmt|;
name|gtk_clist_unselect_row
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_clist_remove
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|)
expr_stmt|;
name|selection_renumber
argument_list|(
name|selection
argument_list|,
name|row
argument_list|)
expr_stmt|;
name|selection
operator|->
name|selected_child
operator|=
name|NULL
expr_stmt|;
name|selection
operator|->
name|nr_rows
operator|--
expr_stmt|;
name|set_buttons
argument_list|(
name|selection
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|object_selected_cb (Object_t * obj,gpointer data)
name|object_selected_cb
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Selection_t
modifier|*
name|selection
init|=
operator|(
name|Selection_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|row
init|=
name|selection_find_object
argument_list|(
name|selection
argument_list|,
name|obj
argument_list|)
decl_stmt|;
name|selection_set_selected
argument_list|(
name|selection
argument_list|,
name|row
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|object_moved_cb (Object_t * obj,gpointer data)
name|object_moved_cb
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Selection_t
modifier|*
name|selection
init|=
operator|(
name|Selection_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|row
init|=
name|object_get_position_in_list
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|selection
operator|->
name|select_lock
operator|=
name|TRUE
expr_stmt|;
name|gtk_clist_set_row_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|selection
operator|->
name|list
argument_list|)
argument_list|,
name|row
argument_list|,
operator|(
name|gpointer
operator|)
name|obj
argument_list|)
expr_stmt|;
name|selection_set_selected
argument_list|(
name|selection
argument_list|,
name|row
argument_list|)
expr_stmt|;
name|selection_update
argument_list|(
name|selection
argument_list|,
name|row
argument_list|,
name|obj
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|toggle_order (GtkWidget * widget,gint column,gpointer data)
name|toggle_order
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|column
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
comment|/* Fix me! */
block|}
end_function

begin_decl_stmt
DECL|variable|target_table
specifier|static
name|GtkTargetEntry
name|target_table
index|[]
init|=
block|{
block|{
literal|"STRING"
block|,
literal|0
block|,
literal|1
block|}
block|,
block|{
literal|"text/plain"
block|,
literal|0
block|,
literal|2
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|handle_drop (GtkWidget * widget,GdkDragContext * context,gint x,gint y,GtkSelectionData * data,guint info,guint time)
name|handle_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GtkSelectionData
modifier|*
name|data
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|data
operator|->
name|length
operator|>=
literal|0
operator|&&
name|data
operator|->
name|format
operator|==
literal|8
condition|)
block|{
name|gint
name|row
decl_stmt|,
name|column
decl_stmt|;
if|if
condition|(
name|gtk_clist_get_selection_info
argument_list|(
name|GTK_CLIST
argument_list|(
name|widget
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|row
argument_list|,
operator|&
name|column
argument_list|)
condition|)
block|{
name|Object_t
modifier|*
name|obj
init|=
name|gtk_clist_get_row_data
argument_list|(
name|GTK_CLIST
argument_list|(
name|widget
argument_list|)
argument_list|,
name|row
operator|+
literal|1
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|obj
operator|->
name|locked
condition|)
block|{
name|command_list_add
argument_list|(
name|edit_object_command_new
argument_list|(
name|obj
argument_list|)
argument_list|)
expr_stmt|;
name|object_set_url
argument_list|(
name|obj
argument_list|,
name|data
operator|->
name|data
argument_list|)
expr_stmt|;
name|object_emit_update_signal
argument_list|(
name|obj
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
name|gtk_drag_finish
argument_list|(
name|context
argument_list|,
name|success
argument_list|,
name|FALSE
argument_list|,
name|time
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Selection_t
modifier|*
DECL|function|make_selection (ObjectList_t * object_list)
name|make_selection
parameter_list|(
name|ObjectList_t
modifier|*
name|object_list
parameter_list|)
block|{
name|Selection_t
modifier|*
name|data
init|=
name|g_new
argument_list|(
name|Selection_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|swin
decl_stmt|,
modifier|*
name|frame
decl_stmt|,
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|toolbar
decl_stmt|;
name|GtkWidget
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|titles
index|[]
init|=
block|{
literal|"#"
block|,
name|N_
argument_list|(
literal|"URL"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Target"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Comment"
argument_list|)
block|}
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|data
operator|->
name|object_list
operator|=
name|object_list
expr_stmt|;
name|data
operator|->
name|selected_child
operator|=
name|NULL
expr_stmt|;
name|data
operator|->
name|is_visible
operator|=
name|TRUE
expr_stmt|;
name|data
operator|->
name|nr_rows
operator|=
literal|0
expr_stmt|;
name|data
operator|->
name|select_lock
operator|=
name|FALSE
expr_stmt|;
name|data
operator|->
name|unselect_lock
operator|=
name|FALSE
expr_stmt|;
name|data
operator|->
name|container
operator|=
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|toolbar
operator|=
name|make_selection_toolbar
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|toolbar
argument_list|)
expr_stmt|;
comment|/* Create selection */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Selection"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
name|titles
index|[
name|i
index|]
operator|=
name|gettext
argument_list|(
name|titles
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|data
operator|->
name|list
operator|=
name|list
operator|=
name|gtk_clist_new_with_titles
argument_list|(
literal|4
argument_list|,
name|titles
argument_list|)
expr_stmt|;
name|GTK_WIDGET_UNSET_FLAGS
argument_list|(
name|data
operator|->
name|list
argument_list|,
name|GTK_CAN_FOCUS
argument_list|)
expr_stmt|;
name|gtk_clist_column_titles_passive
argument_list|(
name|GTK_CLIST
argument_list|(
name|list
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_clist_column_title_active
argument_list|(
name|GTK_CLIST
argument_list|(
name|list
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_clist_set_column_width
argument_list|(
name|GTK_CLIST
argument_list|(
name|list
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|gtk_clist_set_column_width
argument_list|(
name|GTK_CLIST
argument_list|(
name|list
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|80
argument_list|)
expr_stmt|;
name|gtk_clist_set_column_width
argument_list|(
name|GTK_CLIST
argument_list|(
name|list
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|64
argument_list|)
expr_stmt|;
name|gtk_clist_set_column_width
argument_list|(
name|GTK_CLIST
argument_list|(
name|list
argument_list|)
argument_list|,
literal|3
argument_list|,
literal|64
argument_list|)
expr_stmt|;
comment|/*   gtk_clist_set_reorderable(GTK_CLIST(list), TRUE); */
comment|/* Create scrollable window */
name|swin
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|swin
argument_list|,
literal|16
operator|+
literal|80
operator|+
literal|2
operator|*
literal|64
operator|+
literal|16
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|swin
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|swin
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_add_with_viewport
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|swin
argument_list|)
argument_list|,
name|list
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|list
argument_list|)
expr_stmt|;
comment|/* Drop support */
name|gtk_drag_dest_set
argument_list|(
name|list
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|target_table
argument_list|,
literal|2
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|list
argument_list|)
argument_list|,
literal|"drag_data_received"
argument_list|,
name|G_CALLBACK
argument_list|(
name|handle_drop
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Callbacks we are interested in */
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|list
argument_list|)
argument_list|,
literal|"click_column"
argument_list|,
name|G_CALLBACK
argument_list|(
name|toggle_order
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|list
argument_list|)
argument_list|,
literal|"select_row"
argument_list|,
name|G_CALLBACK
argument_list|(
name|select_row_cb
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|list
argument_list|)
argument_list|,
literal|"unselect_row"
argument_list|,
name|G_CALLBACK
argument_list|(
name|unselect_row_cb
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|list
argument_list|)
argument_list|,
literal|"row_move"
argument_list|,
name|G_CALLBACK
argument_list|(
name|row_move_cb
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
comment|/* For handling doubleclick */
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|list
argument_list|)
argument_list|,
literal|"button_press_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|button_press_cb
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|list
argument_list|)
argument_list|,
literal|"button_release_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|button_release_cb
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gtk_clist_set_selection_mode
argument_list|(
name|GTK_CLIST
argument_list|(
name|list
argument_list|)
argument_list|,
name|GTK_SELECTION_MULTIPLE
argument_list|)
expr_stmt|;
name|set_buttons
argument_list|(
name|data
argument_list|)
expr_stmt|;
comment|/* Set object list callbacks we're interested in */
name|object_list_add_add_cb
argument_list|(
name|object_list
argument_list|,
name|object_added_cb
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|object_list_add_update_cb
argument_list|(
name|object_list
argument_list|,
name|object_updated_cb
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|object_list_add_remove_cb
argument_list|(
name|object_list
argument_list|,
name|object_removed_cb
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|object_list_add_select_cb
argument_list|(
name|object_list
argument_list|,
name|object_selected_cb
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|object_list_add_move_cb
argument_list|(
name|object_list
argument_list|,
name|object_moved_cb
argument_list|,
name|data
argument_list|)
expr_stmt|;
return|return
name|data
return|;
block|}
end_function

begin_function
name|void
DECL|function|selection_toggle_visibility (Selection_t * selection)
name|selection_toggle_visibility
parameter_list|(
name|Selection_t
modifier|*
name|selection
parameter_list|)
block|{
if|if
condition|(
name|selection
operator|->
name|is_visible
condition|)
block|{
name|gtk_widget_hide
argument_list|(
name|selection
operator|->
name|container
argument_list|)
expr_stmt|;
name|selection
operator|->
name|is_visible
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_show
argument_list|(
name|selection
operator|->
name|container
argument_list|)
expr_stmt|;
name|selection
operator|->
name|is_visible
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|selection_freeze (Selection_t * selection)
name|selection_freeze
parameter_list|(
name|Selection_t
modifier|*
name|selection
parameter_list|)
block|{
name|gtk_clist_freeze
argument_list|(
name|GTK_CLIST
argument_list|(
operator|(
name|selection
operator|)
operator|->
name|list
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|selection_thaw (Selection_t * selection)
name|selection_thaw
parameter_list|(
name|Selection_t
modifier|*
name|selection
parameter_list|)
block|{
name|gtk_clist_thaw
argument_list|(
name|GTK_CLIST
argument_list|(
operator|(
name|selection
operator|)
operator|->
name|list
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

