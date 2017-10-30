begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainerentry.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpcellrendererviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerentry.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainertreestore.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_container_entry_view_iface_init
parameter_list|(
name|GimpContainerViewInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_entry_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_entry_set_context
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gpointer
name|gimp_container_entry_insert_item
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
name|parent_insert_data
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_entry_remove_item
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
name|gimp_container_entry_reorder_item
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
name|new_index
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_entry_rename_item
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
name|gboolean
name|gimp_container_entry_select_item
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
name|gimp_container_entry_clear_items
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
name|gimp_container_entry_set_view_size
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
name|gimp_container_entry_changed
parameter_list|(
name|GtkEntry
modifier|*
name|entry
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_entry_match_selected
parameter_list|(
name|GtkEntryCompletion
modifier|*
name|widget
parameter_list|,
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpContainerEntry
argument_list|,
argument|gimp_container_entry
argument_list|,
argument|GTK_TYPE_ENTRY
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONTAINER_VIEW,                                                 gimp_container_entry_view_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_container_entry_parent_class
end_define

begin_decl_stmt
specifier|static
name|GimpContainerViewInterface
modifier|*
name|parent_view_iface
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_container_entry_class_init (GimpContainerEntryClass * klass)
name|gimp_container_entry_class_init
parameter_list|(
name|GimpContainerEntryClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_container_view_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_container_view_get_property
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_container_entry_finalize
expr_stmt|;
name|gimp_container_view_install_properties
argument_list|(
name|object_class
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_entry_view_iface_init (GimpContainerViewInterface * iface)
name|gimp_container_entry_view_iface_init
parameter_list|(
name|GimpContainerViewInterface
modifier|*
name|iface
parameter_list|)
block|{
name|parent_view_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|iface
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|parent_view_iface
condition|)
name|parent_view_iface
operator|=
name|g_type_default_interface_peek
argument_list|(
name|GIMP_TYPE_CONTAINER_VIEW
argument_list|)
expr_stmt|;
name|iface
operator|->
name|set_context
operator|=
name|gimp_container_entry_set_context
expr_stmt|;
name|iface
operator|->
name|insert_item
operator|=
name|gimp_container_entry_insert_item
expr_stmt|;
name|iface
operator|->
name|remove_item
operator|=
name|gimp_container_entry_remove_item
expr_stmt|;
name|iface
operator|->
name|reorder_item
operator|=
name|gimp_container_entry_reorder_item
expr_stmt|;
name|iface
operator|->
name|rename_item
operator|=
name|gimp_container_entry_rename_item
expr_stmt|;
name|iface
operator|->
name|select_item
operator|=
name|gimp_container_entry_select_item
expr_stmt|;
name|iface
operator|->
name|clear_items
operator|=
name|gimp_container_entry_clear_items
expr_stmt|;
name|iface
operator|->
name|set_view_size
operator|=
name|gimp_container_entry_set_view_size
expr_stmt|;
name|iface
operator|->
name|insert_data_free
operator|=
operator|(
name|GDestroyNotify
operator|)
name|gtk_tree_iter_free
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_entry_init (GimpContainerEntry * entry)
name|gimp_container_entry_init
parameter_list|(
name|GimpContainerEntry
modifier|*
name|entry
parameter_list|)
block|{
name|GtkEntryCompletion
modifier|*
name|completion
decl_stmt|;
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|GType
name|types
index|[
name|GIMP_CONTAINER_TREE_STORE_N_COLUMNS
index|]
decl_stmt|;
name|gint
name|n_types
init|=
literal|0
decl_stmt|;
name|entry
operator|->
name|viewable
operator|=
name|NULL
expr_stmt|;
name|completion
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_ENTRY_COMPLETION
argument_list|,
literal|"inline-completion"
argument_list|,
name|TRUE
argument_list|,
literal|"popup-single-match"
argument_list|,
name|FALSE
argument_list|,
literal|"popup-set-width"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_tree_store_columns_init
argument_list|(
name|types
argument_list|,
operator|&
name|n_types
argument_list|)
expr_stmt|;
name|model
operator|=
name|gimp_container_tree_store_new
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|entry
argument_list|)
argument_list|,
name|n_types
argument_list|,
name|types
argument_list|)
expr_stmt|;
name|gimp_container_tree_store_set_use_name
argument_list|(
name|GIMP_CONTAINER_TREE_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_completion_set_model
argument_list|(
name|completion
argument_list|,
name|model
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|model
argument_list|)
expr_stmt|;
name|gtk_entry_set_completion
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|completion
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|completion
argument_list|,
literal|"match-selected"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_entry_match_selected
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|completion
argument_list|)
expr_stmt|;
comment|/*  FIXME: This can be done better with GTK+ 2.6.  */
name|cell
operator|=
name|gimp_cell_renderer_viewable_new
argument_list|()
expr_stmt|;
name|gtk_cell_layout_pack_start
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|completion
argument_list|)
argument_list|,
name|cell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_cell_layout_set_attributes
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|completion
argument_list|)
argument_list|,
name|cell
argument_list|,
literal|"renderer"
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_RENDERER
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_tree_store_add_renderer_cell
argument_list|(
name|GIMP_CONTAINER_TREE_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|cell
argument_list|)
expr_stmt|;
name|gtk_entry_completion_set_text_column
argument_list|(
name|completion
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_entry_changed
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_container_entry_new (GimpContainer * container,GimpContext * context,gint view_size,gint view_border_width)
name|gimp_container_entry_new
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
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|GimpContainerView
modifier|*
name|view
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|container
operator|==
name|NULL
operator|||
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
name|context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|entry
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CONTAINER_ENTRY
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|view
operator|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|gimp_container_view_set_view_size
argument_list|(
name|view
argument_list|,
name|view_size
argument_list|,
name|view_border_width
argument_list|)
expr_stmt|;
if|if
condition|(
name|container
condition|)
name|gimp_container_view_set_container
argument_list|(
name|view
argument_list|,
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|context
condition|)
name|gimp_container_view_set_context
argument_list|(
name|view
argument_list|,
name|context
argument_list|)
expr_stmt|;
return|return
name|entry
return|;
block|}
end_function

begin_comment
comment|/*  GimpContainerView methods  */
end_comment

begin_function
specifier|static
name|GtkTreeModel
modifier|*
DECL|function|gimp_container_entry_get_model (GimpContainerView * view)
name|gimp_container_entry_get_model
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|GtkEntryCompletion
modifier|*
name|completion
decl_stmt|;
name|completion
operator|=
name|gtk_entry_get_completion
argument_list|(
name|GTK_ENTRY
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|completion
condition|)
return|return
name|gtk_entry_completion_get_model
argument_list|(
name|completion
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_entry_finalize (GObject * object)
name|gimp_container_entry_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpContainerEntry
modifier|*
name|entry
init|=
name|GIMP_CONTAINER_ENTRY
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|entry
operator|->
name|viewable
condition|)
block|{
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|entry
operator|->
name|viewable
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|entry
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|entry
operator|->
name|viewable
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_entry_set_context (GimpContainerView * view,GimpContext * context)
name|gimp_container_entry_set_context
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|gimp_container_entry_get_model
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|parent_view_iface
operator|->
name|set_context
argument_list|(
name|view
argument_list|,
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|model
condition|)
name|gimp_container_tree_store_set_context
argument_list|(
name|GIMP_CONTAINER_TREE_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gpointer
DECL|function|gimp_container_entry_insert_item (GimpContainerView * view,GimpViewable * viewable,gpointer parent_insert_data,gint index)
name|gimp_container_entry_insert_item
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
name|parent_insert_data
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|gimp_container_entry_get_model
argument_list|(
name|view
argument_list|)
decl_stmt|;
return|return
name|gimp_container_tree_store_insert_item
argument_list|(
name|GIMP_CONTAINER_TREE_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|viewable
argument_list|,
name|parent_insert_data
argument_list|,
name|index
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_entry_remove_item (GimpContainerView * view,GimpViewable * viewable,gpointer insert_data)
name|gimp_container_entry_remove_item
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
name|GtkTreeModel
modifier|*
name|model
init|=
name|gimp_container_entry_get_model
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|gimp_container_tree_store_remove_item
argument_list|(
name|GIMP_CONTAINER_TREE_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|viewable
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_entry_reorder_item (GimpContainerView * view,GimpViewable * viewable,gint new_index,gpointer insert_data)
name|gimp_container_entry_reorder_item
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
name|new_index
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|gimp_container_entry_get_model
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|gimp_container_tree_store_reorder_item
argument_list|(
name|GIMP_CONTAINER_TREE_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|viewable
argument_list|,
name|new_index
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_entry_rename_item (GimpContainerView * view,GimpViewable * viewable,gpointer insert_data)
name|gimp_container_entry_rename_item
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
name|GimpContainerEntry
modifier|*
name|container_entry
init|=
name|GIMP_CONTAINER_ENTRY
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GtkEntry
modifier|*
name|entry
init|=
name|GTK_ENTRY
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GtkTreeModel
modifier|*
name|model
init|=
name|gimp_container_entry_get_model
argument_list|(
name|view
argument_list|)
decl_stmt|;
if|if
condition|(
name|viewable
operator|==
name|container_entry
operator|->
name|viewable
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|entry
argument_list|,
name|gimp_container_entry_changed
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|entry
argument_list|,
name|gimp_object_get_name
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|entry
argument_list|,
name|gimp_container_entry_changed
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
name|gimp_container_tree_store_rename_item
argument_list|(
name|GIMP_CONTAINER_TREE_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|viewable
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_container_entry_select_item (GimpContainerView * view,GimpViewable * viewable,gpointer insert_data)
name|gimp_container_entry_select_item
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
name|GimpContainerEntry
modifier|*
name|container_entry
init|=
name|GIMP_CONTAINER_ENTRY
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GtkEntry
modifier|*
name|entry
init|=
name|GTK_ENTRY
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GtkTreeIter
modifier|*
name|iter
init|=
name|insert_data
decl_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|entry
argument_list|,
name|gimp_container_entry_changed
argument_list|,
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|container_entry
operator|->
name|viewable
condition|)
block|{
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|container_entry
operator|->
name|viewable
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|container_entry
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|container_entry
operator|->
name|viewable
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|iter
condition|)
block|{
name|container_entry
operator|->
name|viewable
operator|=
name|viewable
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|container_entry
operator|->
name|viewable
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|container_entry
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|gtk_widget_modify_text
argument_list|(
name|GTK_WIDGET
argument_list|(
name|entry
argument_list|)
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* The selected item does not exist. */
name|GdkColor
name|gdk_red
decl_stmt|;
name|gdk_red
operator|.
name|red
operator|=
literal|65535
expr_stmt|;
name|gdk_red
operator|.
name|green
operator|=
literal|0
expr_stmt|;
name|gdk_red
operator|.
name|blue
operator|=
literal|0
expr_stmt|;
name|gtk_widget_modify_text
argument_list|(
name|GTK_WIDGET
argument_list|(
name|entry
argument_list|)
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
operator|&
name|gdk_red
argument_list|)
expr_stmt|;
block|}
name|gtk_entry_set_text
argument_list|(
name|entry
argument_list|,
name|viewable
condition|?
name|gimp_object_get_name
argument_list|(
name|viewable
argument_list|)
else|:
literal|""
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|entry
argument_list|,
name|gimp_container_entry_changed
argument_list|,
name|view
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
DECL|function|gimp_container_entry_clear_items (GimpContainerView * view)
name|gimp_container_entry_clear_items
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|gimp_container_entry_get_model
argument_list|(
name|view
argument_list|)
decl_stmt|;
comment|/* model is NULL in dispose() */
if|if
condition|(
name|model
condition|)
name|gimp_container_tree_store_clear_items
argument_list|(
name|GIMP_CONTAINER_TREE_STORE
argument_list|(
name|model
argument_list|)
argument_list|)
expr_stmt|;
name|parent_view_iface
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
DECL|function|gimp_container_entry_set_view_size (GimpContainerView * view)
name|gimp_container_entry_set_view_size
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|gimp_container_entry_get_model
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|gimp_container_tree_store_set_view_size
argument_list|(
name|GIMP_CONTAINER_TREE_STORE
argument_list|(
name|model
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_entry_changed (GtkEntry * entry,GimpContainerView * view)
name|gimp_container_entry_changed
parameter_list|(
name|GtkEntry
modifier|*
name|entry
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContainerEntry
modifier|*
name|container_entry
init|=
name|GIMP_CONTAINER_ENTRY
argument_list|(
name|entry
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
init|=
name|gimp_container_view_get_container
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GimpObject
modifier|*
name|object
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|text
decl_stmt|;
if|if
condition|(
operator|!
name|container
condition|)
return|return;
if|if
condition|(
name|container_entry
operator|->
name|viewable
condition|)
block|{
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|container_entry
operator|->
name|viewable
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|container_entry
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|container_entry
operator|->
name|viewable
operator|=
name|NULL
expr_stmt|;
block|}
name|text
operator|=
name|gtk_entry_get_text
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|object
operator|=
name|gimp_container_get_child_by_name
argument_list|(
name|container
argument_list|,
name|text
argument_list|)
expr_stmt|;
if|if
condition|(
name|object
condition|)
block|{
name|container_entry
operator|->
name|viewable
operator|=
name|GIMP_VIEWABLE
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|container_entry
operator|->
name|viewable
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|container_entry
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|gtk_widget_modify_text
argument_list|(
name|GTK_WIDGET
argument_list|(
name|entry
argument_list|)
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_view_item_selected
argument_list|(
name|view
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* While editing the entry, contents shows in red for non-existent item. */
name|GdkColor
name|gdk_red
decl_stmt|;
name|gdk_red
operator|.
name|red
operator|=
literal|65535
expr_stmt|;
name|gdk_red
operator|.
name|green
operator|=
literal|0
expr_stmt|;
name|gdk_red
operator|.
name|blue
operator|=
literal|0
expr_stmt|;
name|gtk_widget_modify_text
argument_list|(
name|GTK_WIDGET
argument_list|(
name|entry
argument_list|)
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
operator|&
name|gdk_red
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_entry_match_selected (GtkEntryCompletion * widget,GtkTreeModel * model,GtkTreeIter * iter,GimpContainerView * view)
name|gimp_container_entry_match_selected
parameter_list|(
name|GtkEntryCompletion
modifier|*
name|widget
parameter_list|,
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|GimpViewRenderer
modifier|*
name|renderer
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_RENDERER
argument_list|,
operator|&
name|renderer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_container_view_item_selected
argument_list|(
name|view
argument_list|,
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

