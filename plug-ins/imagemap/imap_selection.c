begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2005 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
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
file|"imap_commands.h"
end_include

begin_include
include|#
directive|include
file|"imap_main.h"
end_include

begin_include
include|#
directive|include
file|"imap_menu.h"
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
ifdef|#
directive|ifdef
name|_OLD_
if|if
condition|(
name|gtk_tree_selection_count_selected_rows
argument_list|(
name|data
operator|->
name|selection
argument_list|)
condition|)
block|{
ifdef|#
directive|ifdef
name|_OLD_
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
endif|#
directive|endif
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
endif|#
directive|endif
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|changed_cb (GtkTreeSelection * selection,gpointer param)
name|changed_cb
parameter_list|(
name|GtkTreeSelection
modifier|*
name|selection
parameter_list|,
name|gpointer
name|param
parameter_list|)
block|{
name|Selection_t
modifier|*
name|data
init|=
operator|(
name|Selection_t
operator|*
operator|)
name|param
decl_stmt|;
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
name|Command_t
modifier|*
name|command
decl_stmt|,
modifier|*
name|sub_command
decl_stmt|;
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|,
modifier|*
name|selected_rows
decl_stmt|;
name|selected_rows
operator|=
name|gtk_tree_selection_get_selected_rows
argument_list|(
name|selection
argument_list|,
operator|&
name|model
argument_list|)
expr_stmt|;
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
for|for
control|(
name|list
operator|=
name|selected_rows
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|Object_t
modifier|*
name|obj
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|GtkTreePath
modifier|*
name|path
init|=
operator|(
name|GtkTreePath
operator|*
operator|)
name|list
operator|->
name|data
decl_stmt|;
name|gtk_tree_model_get_iter
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
literal|0
argument_list|,
operator|&
name|obj
argument_list|,
operator|-
literal|1
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
block|}
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
name|command_execute
argument_list|(
name|command
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|selected_rows
argument_list|,
operator|(
name|GFunc
operator|)
name|gtk_tree_path_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|selected_rows
argument_list|)
expr_stmt|;
name|set_buttons
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

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
name|data
operator|->
name|doubleclick
condition|)
block|{
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|data
operator|->
name|doubleclick
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|gtk_tree_view_get_path_at_pos
argument_list|(
name|GTK_TREE_VIEW
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
name|path
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|data
operator|->
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|path
argument_list|)
condition|)
block|{
name|Object_t
modifier|*
name|obj
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|data
operator|->
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
literal|0
argument_list|,
operator|&
name|obj
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|object_edit
argument_list|(
name|obj
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|data
operator|->
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
DECL|function|button_release_cb (GtkWidget * widget,GdkEventButton * event,Selection_t * data)
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
name|data
operator|->
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
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
name|gtk_tree_model_iter_nth_child
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|selection
operator|->
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|NULL
argument_list|,
name|row
argument_list|)
condition|)
block|{
name|Object_t
modifier|*
name|obj
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|selection
operator|->
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
literal|0
argument_list|,
operator|&
name|obj
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|selection
operator|->
name|select_lock
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|obj
operator|->
name|selected
condition|)
block|{
name|gtk_tree_selection_select_iter
argument_list|(
name|selection
operator|->
name|selection
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_tree_selection_unselect_iter
argument_list|(
name|selection
operator|->
name|selection
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
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
name|GtkTreeIter
name|iter
decl_stmt|;
name|gint
name|position
init|=
name|object_get_position_in_list
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|selection
operator|->
name|nr_rows
operator|++
expr_stmt|;
if|if
condition|(
name|position
operator|<
name|selection
operator|->
name|nr_rows
operator|-
literal|1
condition|)
block|{
name|gtk_list_store_insert
argument_list|(
name|selection
operator|->
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|position
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_list_store_append
argument_list|(
name|selection
operator|->
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
name|gtk_list_store_set
argument_list|(
name|selection
operator|->
name|store
argument_list|,
operator|&
name|iter
argument_list|,
literal|0
argument_list|,
name|obj
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|selection_find_object (Selection_t * selection,Object_t * lookup,GtkTreeIter * iter)
name|selection_find_object
parameter_list|(
name|Selection_t
modifier|*
name|selection
parameter_list|,
name|Object_t
modifier|*
name|lookup
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
if|if
condition|(
name|gtk_tree_model_get_iter_first
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|selection
operator|->
name|store
argument_list|)
argument_list|,
name|iter
argument_list|)
condition|)
block|{
do|do
block|{
name|Object_t
modifier|*
name|obj
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|selection
operator|->
name|store
argument_list|)
argument_list|,
name|iter
argument_list|,
literal|0
argument_list|,
operator|&
name|obj
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|obj
operator|==
name|lookup
condition|)
return|return
name|TRUE
return|;
block|}
do|while
condition|(
name|gtk_tree_model_iter_next
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|selection
operator|->
name|store
argument_list|)
argument_list|,
name|iter
argument_list|)
condition|)
do|;
block|}
return|return
name|FALSE
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
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
name|selection_find_object
argument_list|(
name|selection
argument_list|,
name|obj
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|path
operator|=
name|gtk_tree_model_get_path
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|selection
operator|->
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_model_row_changed
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|selection
operator|->
name|store
argument_list|)
argument_list|,
name|path
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
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
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
name|selection_find_object
argument_list|(
name|selection
argument_list|,
name|obj
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|gtk_list_store_remove
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|selection
operator|->
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|set_buttons
argument_list|(
name|selection
argument_list|)
expr_stmt|;
block|}
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
name|position
init|=
name|object_get_position_in_list
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|selection_set_selected
argument_list|(
name|selection
argument_list|,
name|position
argument_list|)
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
name|selection
operator|->
name|select_lock
operator|=
name|TRUE
expr_stmt|;
ifdef|#
directive|ifdef
name|_OLD_
block|{
name|gint
name|row
init|=
name|object_get_position_in_list
argument_list|(
name|obj
argument_list|)
decl_stmt|;
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
endif|#
directive|endif
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
name|Object_t
modifier|*
DECL|function|selection_get_object (GtkTreeModel * tree_model,GtkTreeIter * iter)
name|selection_get_object
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|Object_t
modifier|*
name|obj
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|tree_model
argument_list|,
name|iter
argument_list|,
literal|0
argument_list|,
operator|&
name|obj
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|obj
return|;
block|}
end_function

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
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
if|if
condition|(
name|gtk_tree_view_get_path_at_pos
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|widget
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|path
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|gtk_tree_view_get_model
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|path
argument_list|)
condition|)
block|{
name|Object_t
modifier|*
name|obj
init|=
name|selection_get_object
argument_list|(
name|model
argument_list|,
operator|&
name|iter
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
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
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
specifier|static
name|void
DECL|function|render_image (GtkTreeViewColumn * column,GtkCellRenderer * cell,GtkTreeModel * tree_model,GtkTreeIter * iter,gpointer data)
name|render_image
parameter_list|(
name|GtkTreeViewColumn
modifier|*
name|column
parameter_list|,
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Object_t
modifier|*
name|obj
init|=
name|selection_get_object
argument_list|(
name|tree_model
argument_list|,
name|iter
argument_list|)
decl_stmt|;
name|g_object_set
argument_list|(
name|cell
argument_list|,
literal|"stock-id"
argument_list|,
name|object_get_stock_icon_name
argument_list|(
name|obj
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|render_nr (GtkTreeViewColumn * column,GtkCellRenderer * cell,GtkTreeModel * tree_model,GtkTreeIter * iter,gpointer data)
name|render_nr
parameter_list|(
name|GtkTreeViewColumn
modifier|*
name|column
parameter_list|,
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Object_t
modifier|*
name|obj
init|=
name|selection_get_object
argument_list|(
name|tree_model
argument_list|,
name|iter
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|scratch
decl_stmt|;
name|scratch
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d"
argument_list|,
name|object_get_position_in_list
argument_list|(
name|obj
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|cell
argument_list|,
literal|"text"
argument_list|,
name|scratch
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|scratch
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|render_url (GtkTreeViewColumn * column,GtkCellRenderer * cell,GtkTreeModel * tree_model,GtkTreeIter * iter,gpointer data)
name|render_url
parameter_list|(
name|GtkTreeViewColumn
modifier|*
name|column
parameter_list|,
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Object_t
modifier|*
name|obj
init|=
name|selection_get_object
argument_list|(
name|tree_model
argument_list|,
name|iter
argument_list|)
decl_stmt|;
name|g_object_set
argument_list|(
name|cell
argument_list|,
literal|"text"
argument_list|,
name|obj
operator|->
name|url
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|render_target (GtkTreeViewColumn * column,GtkCellRenderer * cell,GtkTreeModel * tree_model,GtkTreeIter * iter,gpointer data)
name|render_target
parameter_list|(
name|GtkTreeViewColumn
modifier|*
name|column
parameter_list|,
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Object_t
modifier|*
name|obj
init|=
name|selection_get_object
argument_list|(
name|tree_model
argument_list|,
name|iter
argument_list|)
decl_stmt|;
name|g_object_set
argument_list|(
name|cell
argument_list|,
literal|"text"
argument_list|,
name|obj
operator|->
name|target
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|render_comment (GtkTreeViewColumn * column,GtkCellRenderer * cell,GtkTreeModel * tree_model,GtkTreeIter * iter,gpointer data)
name|render_comment
parameter_list|(
name|GtkTreeViewColumn
modifier|*
name|column
parameter_list|,
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Object_t
modifier|*
name|obj
init|=
name|selection_get_object
argument_list|(
name|tree_model
argument_list|,
name|iter
argument_list|)
decl_stmt|;
name|g_object_set
argument_list|(
name|cell
argument_list|,
literal|"text"
argument_list|,
name|obj
operator|->
name|comment
argument_list|,
name|NULL
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
name|GtkCellRenderer
modifier|*
name|renderer
decl_stmt|;
name|GtkTreeViewColumn
modifier|*
name|column
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
name|doubleclick
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
literal|6
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
argument_list|()
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
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Selection"
argument_list|)
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
name|data
operator|->
name|store
operator|=
name|gtk_list_store_new
argument_list|(
literal|1
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|data
operator|->
name|list
operator|=
name|gtk_tree_view_new_with_model
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|data
operator|->
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|data
operator|->
name|list
expr_stmt|;
name|g_object_unref
argument_list|(
name|data
operator|->
name|store
argument_list|)
expr_stmt|;
name|renderer
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|column
operator|=
name|gtk_tree_view_column_new_with_attributes
argument_list|(
name|N_
argument_list|(
literal|"#"
argument_list|)
argument_list|,
name|renderer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_cell_data_func
argument_list|(
name|column
argument_list|,
name|renderer
argument_list|,
name|render_nr
argument_list|,
name|data
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_min_width
argument_list|(
name|column
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_sizing
argument_list|(
name|column
argument_list|,
name|GTK_TREE_VIEW_COLUMN_AUTOSIZE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_alignment
argument_list|(
name|column
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_tree_view_append_column
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|list
argument_list|)
argument_list|,
name|column
argument_list|)
expr_stmt|;
name|column
operator|=
name|gtk_tree_view_column_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_set_title
argument_list|(
name|column
argument_list|,
name|_
argument_list|(
literal|"URL"
argument_list|)
argument_list|)
expr_stmt|;
name|renderer
operator|=
name|gtk_cell_renderer_pixbuf_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|column
argument_list|,
name|renderer
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_cell_data_func
argument_list|(
name|column
argument_list|,
name|renderer
argument_list|,
name|render_image
argument_list|,
name|data
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|renderer
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|column
argument_list|,
name|renderer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_cell_data_func
argument_list|(
name|column
argument_list|,
name|renderer
argument_list|,
name|render_url
argument_list|,
name|data
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_min_width
argument_list|(
name|column
argument_list|,
literal|80
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_resizable
argument_list|(
name|column
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_alignment
argument_list|(
name|column
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_tree_view_append_column
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|list
argument_list|)
argument_list|,
name|column
argument_list|)
expr_stmt|;
name|renderer
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|column
operator|=
name|gtk_tree_view_column_new_with_attributes
argument_list|(
name|_
argument_list|(
literal|"ALT Text"
argument_list|)
argument_list|,
name|renderer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_cell_data_func
argument_list|(
name|column
argument_list|,
name|renderer
argument_list|,
name|render_comment
argument_list|,
name|data
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_min_width
argument_list|(
name|column
argument_list|,
literal|64
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_resizable
argument_list|(
name|column
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_alignment
argument_list|(
name|column
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_tree_view_append_column
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|list
argument_list|)
argument_list|,
name|column
argument_list|)
expr_stmt|;
name|renderer
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|column
operator|=
name|gtk_tree_view_column_new_with_attributes
argument_list|(
name|_
argument_list|(
literal|"Target"
argument_list|)
argument_list|,
name|renderer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_cell_data_func
argument_list|(
name|column
argument_list|,
name|renderer
argument_list|,
name|render_target
argument_list|,
name|data
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_min_width
argument_list|(
name|column
argument_list|,
literal|64
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_resizable
argument_list|(
name|column
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_alignment
argument_list|(
name|column
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_tree_view_append_column
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|list
argument_list|)
argument_list|,
name|column
argument_list|)
expr_stmt|;
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
name|gtk_widget_set_size_request
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
name|list
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
comment|/* For handling doubleclick */
name|g_signal_connect
argument_list|(
name|list
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
name|list
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
comment|/* Callbacks we are interested in */
name|data
operator|->
name|selection
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|list
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_tree_selection_set_mode
argument_list|(
name|data
operator|->
name|selection
argument_list|,
name|GTK_SELECTION_MULTIPLE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
operator|->
name|selection
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|changed_cb
argument_list|)
argument_list|,
name|data
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
block|{ }
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
block|{ }
end_function

end_unit

