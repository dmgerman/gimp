begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerlistview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_container_list_view_class_init
parameter_list|(
name|GimpContainerListViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_list_view_init
parameter_list|(
name|GimpContainerListView
modifier|*
name|panel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_list_view_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gpointer
name|gimp_container_list_view_insert_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_list_view_remove_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_list_view_select_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_list_view_clear_items
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_list_view_set_preview_size
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_list_view_name_changed
parameter_list|(
name|GimpContainerListView
modifier|*
name|list_view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_list_view_item_selected
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpContainerViewClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_container_list_view_get_type (void)
name|gimp_container_list_view_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|guint
name|list_view_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|list_view_type
condition|)
block|{
name|GtkTypeInfo
name|list_view_info
init|=
block|{
literal|"GimpContainerListView"
block|,
sizeof|sizeof
argument_list|(
name|GimpContainerListView
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpContainerListViewClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_container_list_view_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_container_list_view_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|list_view_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_CONTAINER_VIEW
argument_list|,
operator|&
name|list_view_info
argument_list|)
expr_stmt|;
block|}
return|return
name|list_view_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_list_view_class_init (GimpContainerListViewClass * klass)
name|gimp_container_list_view_class_init
parameter_list|(
name|GimpContainerListViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpContainerViewClass
modifier|*
name|container_view_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|container_view_class
operator|=
operator|(
name|GimpContainerViewClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_CONTAINER_VIEW
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_container_list_view_destroy
expr_stmt|;
name|container_view_class
operator|->
name|insert_item
operator|=
name|gimp_container_list_view_insert_item
expr_stmt|;
name|container_view_class
operator|->
name|remove_item
operator|=
name|gimp_container_list_view_remove_item
expr_stmt|;
name|container_view_class
operator|->
name|select_item
operator|=
name|gimp_container_list_view_select_item
expr_stmt|;
name|container_view_class
operator|->
name|clear_items
operator|=
name|gimp_container_list_view_clear_items
expr_stmt|;
name|container_view_class
operator|->
name|set_preview_size
operator|=
name|gimp_container_list_view_set_preview_size
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_list_view_init (GimpContainerListView * list_view)
name|gimp_container_list_view_init
parameter_list|(
name|GimpContainerListView
modifier|*
name|list_view
parameter_list|)
block|{
name|list_view
operator|->
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
name|list_view
operator|->
name|scrolled_win
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_ALWAYS
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|list_view
argument_list|)
argument_list|,
name|list_view
operator|->
name|scrolled_win
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|list_view
operator|->
name|gtk_list
operator|=
name|gtk_list_new
argument_list|()
expr_stmt|;
name|gtk_scrolled_window_add_with_viewport
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|list_view
operator|->
name|scrolled_win
argument_list|)
argument_list|,
name|list_view
operator|->
name|gtk_list
argument_list|)
expr_stmt|;
name|gtk_list_set_selection_mode
argument_list|(
name|GTK_LIST
argument_list|(
name|list_view
operator|->
name|gtk_list
argument_list|)
argument_list|,
name|GTK_SELECTION_BROWSE
argument_list|)
expr_stmt|;
name|gtk_container_set_focus_vadjustment
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|list_view
operator|->
name|gtk_list
argument_list|)
argument_list|,
name|gtk_scrolled_window_get_vadjustment
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|list_view
operator|->
name|scrolled_win
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|GTK_WIDGET_UNSET_FLAGS
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|list_view
operator|->
name|scrolled_win
argument_list|)
operator|->
name|vscrollbar
argument_list|,
name|GTK_CAN_FOCUS
argument_list|)
expr_stmt|;
name|gtk_signal_connect_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list_view
operator|->
name|gtk_list
argument_list|)
argument_list|,
literal|"select_child"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_container_list_view_item_selected
argument_list|)
argument_list|,
name|list_view
argument_list|,
name|GTK_OBJECT
argument_list|(
name|list_view
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|list_view
operator|->
name|gtk_list
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|list_view
operator|->
name|scrolled_win
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_list_view_destroy (GtkObject * object)
name|gimp_container_list_view_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpContainerListView
modifier|*
name|list_view
decl_stmt|;
name|list_view
operator|=
name|GIMP_CONTAINER_LIST_VIEW
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_container_list_view_new (GimpContainer * container,GimpContext * context,gint preview_size,gint min_items_x,gint min_items_y)
name|gimp_container_list_view_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|preview_size
parameter_list|,
name|gint
name|min_items_x
parameter_list|,
name|gint
name|min_items_y
parameter_list|)
block|{
name|GimpContainerListView
modifier|*
name|list_view
decl_stmt|;
name|GimpContainerView
modifier|*
name|view
decl_stmt|;
name|gint
name|window_border
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|container
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|!
name|context
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|preview_size
operator|>
literal|0
operator|&&
name|preview_size
operator|<=
literal|64
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|min_items_x
operator|>
literal|0
operator|&&
name|min_items_x
operator|<=
literal|64
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|min_items_y
operator|>
literal|0
operator|&&
name|min_items_y
operator|<=
literal|64
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|list_view
operator|=
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_CONTAINER_LIST_VIEW
argument_list|)
expr_stmt|;
name|view
operator|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|list_view
argument_list|)
expr_stmt|;
name|view
operator|->
name|preview_size
operator|=
name|preview_size
expr_stmt|;
name|window_border
operator|=
name|GTK_SCROLLED_WINDOW
argument_list|(
name|list_view
operator|->
name|scrolled_win
argument_list|)
operator|->
name|vscrollbar
operator|->
name|requisition
operator|.
name|width
operator|+
name|GTK_SCROLLED_WINDOW_CLASS
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list_view
operator|->
name|scrolled_win
argument_list|)
operator|->
name|klass
argument_list|)
operator|->
name|scrollbar_spacing
operator|+
name|list_view
operator|->
name|scrolled_win
operator|->
name|style
operator|->
name|klass
operator|->
name|xthickness
operator|*
literal|4
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|list_view
operator|->
name|gtk_list
operator|->
name|parent
argument_list|,
operator|(
name|preview_size
operator|+
literal|2
operator|)
operator|*
name|min_items_x
operator|+
name|window_border
argument_list|,
operator|(
name|preview_size
operator|+
literal|2
operator|)
operator|*
name|min_items_y
operator|+
name|window_border
argument_list|)
expr_stmt|;
name|gimp_container_view_set_container
argument_list|(
name|view
argument_list|,
name|container
argument_list|)
expr_stmt|;
name|gimp_container_view_set_context
argument_list|(
name|view
argument_list|,
name|context
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|list_view
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gpointer
DECL|function|gimp_container_list_view_insert_item (GimpContainerView * view,GimpViewable * viewable,gint index)
name|gimp_container_list_view_insert_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|GimpContainerListView
modifier|*
name|list_view
decl_stmt|;
name|GtkWidget
modifier|*
name|list_item
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|list_view
operator|=
name|GIMP_CONTAINER_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|list_item
operator|=
name|gtk_list_item_new
argument_list|()
expr_stmt|;
comment|/*   gtk_signal_connect_object_while_alive     (GTK_OBJECT (viewable), "name_changed",      GTK_SIGNAL_FUNC (gimp_container_list_view_name_changed),      GTK_OBJECT (list_view));   */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|list_item
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
name|preview
operator|=
name|gimp_preview_new
argument_list|(
name|viewable
argument_list|,
name|view
operator|->
name|preview_size
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|preview
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
name|preview
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list_item
argument_list|)
argument_list|,
literal|"preview"
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list_item
argument_list|)
argument_list|,
literal|"label"
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|list_item
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_prepend
argument_list|(
name|NULL
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|==
operator|-
literal|1
condition|)
name|gtk_list_append_items
argument_list|(
name|GTK_LIST
argument_list|(
name|list_view
operator|->
name|gtk_list
argument_list|)
argument_list|,
name|list
argument_list|)
expr_stmt|;
else|else
name|gtk_list_insert_items
argument_list|(
name|GTK_LIST
argument_list|(
name|list_view
operator|->
name|gtk_list
argument_list|)
argument_list|,
name|list
argument_list|,
name|index
argument_list|)
expr_stmt|;
return|return
operator|(
name|gpointer
operator|)
name|list_item
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_list_view_remove_item (GimpContainerView * view,GimpViewable * viewable,gpointer insert_data)
name|gimp_container_list_view_remove_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
block|{
name|GimpContainerListView
modifier|*
name|list_view
decl_stmt|;
name|GtkWidget
modifier|*
name|list_item
decl_stmt|;
name|list_view
operator|=
name|GIMP_CONTAINER_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|insert_data
condition|)
name|list_item
operator|=
name|GTK_WIDGET
argument_list|(
name|insert_data
argument_list|)
expr_stmt|;
else|else
name|list_item
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|list_item
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|g_list_prepend
argument_list|(
name|NULL
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
name|gtk_list_remove_items
argument_list|(
name|GTK_LIST
argument_list|(
name|list_view
operator|->
name|gtk_list
argument_list|)
argument_list|,
name|list
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_list_view_select_item (GimpContainerView * view,GimpViewable * viewable,gpointer insert_data)
name|gimp_container_list_view_select_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
block|{
name|GimpContainerListView
modifier|*
name|list_view
decl_stmt|;
name|GtkWidget
modifier|*
name|list_item
decl_stmt|;
name|list_view
operator|=
name|GIMP_CONTAINER_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|insert_data
condition|)
name|list_item
operator|=
name|GTK_WIDGET
argument_list|(
name|insert_data
argument_list|)
expr_stmt|;
else|else
name|list_item
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|list_item
condition|)
block|{
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|gint
name|item_height
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|adj
operator|=
name|gtk_scrolled_window_get_vadjustment
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|list_view
operator|->
name|scrolled_win
argument_list|)
argument_list|)
expr_stmt|;
name|item_height
operator|=
name|list_item
operator|->
name|allocation
operator|.
name|height
expr_stmt|;
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|view
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_handler_block_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list_view
operator|->
name|gtk_list
argument_list|)
argument_list|,
name|gimp_container_list_view_item_selected
argument_list|,
name|list_view
argument_list|)
expr_stmt|;
name|gtk_list_select_child
argument_list|(
name|GTK_LIST
argument_list|(
name|list_view
operator|->
name|gtk_list
argument_list|)
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|*
name|item_height
operator|<
name|adj
operator|->
name|value
condition|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|adj
argument_list|,
name|index
operator|*
name|item_height
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|index
operator|+
literal|1
operator|)
operator|*
name|item_height
operator|>
name|adj
operator|->
name|value
operator|+
name|adj
operator|->
name|page_size
condition|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|adj
argument_list|,
operator|(
name|index
operator|+
literal|1
operator|)
operator|*
name|item_height
operator|-
name|adj
operator|->
name|page_size
argument_list|)
expr_stmt|;
block|}
name|gtk_signal_handler_unblock_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list_view
operator|->
name|gtk_list
argument_list|)
argument_list|,
name|gimp_container_list_view_item_selected
argument_list|,
name|list_view
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_list_view_clear_items (GimpContainerView * view)
name|gimp_container_list_view_clear_items
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContainerListView
modifier|*
name|list_view
decl_stmt|;
name|list_view
operator|=
name|GIMP_CONTAINER_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|gtk_list_clear_items
argument_list|(
name|GTK_LIST
argument_list|(
name|list_view
operator|->
name|gtk_list
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
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|clear_items
condition|)
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|clear_items
argument_list|(
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_list_view_set_preview_size (GimpContainerView * view)
name|gimp_container_list_view_set_preview_size
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContainerListView
modifier|*
name|list_view
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|list_view
operator|=
name|GIMP_CONTAINER_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GTK_LIST
argument_list|(
name|list_view
operator|->
name|gtk_list
argument_list|)
operator|->
name|children
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
name|GimpPreview
modifier|*
name|preview
decl_stmt|;
name|preview
operator|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|,
literal|"preview"
argument_list|)
expr_stmt|;
name|gimp_preview_set_size
argument_list|(
name|preview
argument_list|,
name|view
operator|->
name|preview_size
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_queue_resize
argument_list|(
name|list_view
operator|->
name|gtk_list
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_list_view_name_changed (GimpContainerListView * list_view,GimpViewable * viewable)
name|gimp_container_list_view_name_changed
parameter_list|(
name|GimpContainerListView
modifier|*
name|list_view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|list_item
decl_stmt|;
name|list_item
operator|=
name|g_hash_table_lookup
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|list_view
argument_list|)
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|list_item
condition|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|label
operator|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list_item
argument_list|)
argument_list|,
literal|"label"
argument_list|)
expr_stmt|;
if|if
condition|(
name|label
condition|)
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_list_view_item_selected (GtkWidget * widget,GtkWidget * child,gpointer data)
name|gimp_container_list_view_item_selected
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
name|viewable
operator|=
name|GIMP_PREVIEW
argument_list|(
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|child
argument_list|)
argument_list|,
literal|"preview"
argument_list|)
argument_list|)
operator|->
name|viewable
expr_stmt|;
name|gimp_container_view_item_selected
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|data
argument_list|)
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

