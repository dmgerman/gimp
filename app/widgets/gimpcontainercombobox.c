begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainercombobox.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpcontainercombobox.h"
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

begin_enum
enum|enum
DECL|enum|__anon293ffcb30103
block|{
DECL|enumerator|COLUMN_RENDERER
name|COLUMN_RENDERER
block|,
DECL|enumerator|COLUMN_NAME
name|COLUMN_NAME
block|,
DECL|enumerator|NUM_COLUMNS
name|NUM_COLUMNS
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_container_combo_box_class_init
parameter_list|(
name|GimpContainerComboBoxClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_combo_box_init
parameter_list|(
name|GimpContainerComboBox
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_combo_box_view_iface_init
parameter_list|(
name|GimpContainerViewInterface
modifier|*
name|view_iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gpointer
name|gimp_container_combo_box_insert_item
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
name|gimp_container_combo_box_remove_item
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
name|gimp_container_combo_box_reorder_item
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
name|gimp_container_combo_box_rename_item
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
name|gimp_container_combo_box_select_item
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
name|gimp_container_combo_box_clear_items
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
name|gimp_container_combo_box_set_preview_size
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
name|gimp_container_combo_box_changed
parameter_list|(
name|GtkComboBox
modifier|*
name|combo_box
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
name|gimp_container_combo_box_renderer_update
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkComboBoxClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_view_iface
specifier|static
name|GimpContainerViewInterface
modifier|*
name|parent_view_iface
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_container_combo_box_get_type (void)
name|gimp_container_combo_box_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|view_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|view_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|view_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpContainerComboBoxClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init      */
name|NULL
block|,
comment|/* base_finalize  */
operator|(
name|GClassInitFunc
operator|)
name|gimp_container_combo_box_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpContainerComboBox
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_container_combo_box_init
block|,       }
decl_stmt|;
specifier|static
specifier|const
name|GInterfaceInfo
name|view_iface_info
init|=
block|{
operator|(
name|GInterfaceInitFunc
operator|)
name|gimp_container_combo_box_view_iface_init
block|,
name|NULL
block|,
comment|/* iface_finalize */
name|NULL
comment|/* iface_data     */
block|}
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_COMBO_BOX
argument_list|,
literal|"GimpContainerComboBox"
argument_list|,
operator|&
name|view_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|view_type
argument_list|,
name|GIMP_TYPE_CONTAINER_VIEW
argument_list|,
operator|&
name|view_iface_info
argument_list|)
expr_stmt|;
block|}
return|return
name|view_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_combo_box_class_init (GimpContainerComboBoxClass * klass)
name|gimp_container_combo_box_class_init
parameter_list|(
name|GimpContainerComboBoxClass
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
name|g_object_class_override_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_CONTAINER_VIEW_PROP_CONTAINER
argument_list|,
literal|"container"
argument_list|)
expr_stmt|;
name|g_object_class_override_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_CONTAINER_VIEW_PROP_CONTEXT
argument_list|,
literal|"context"
argument_list|)
expr_stmt|;
name|g_object_class_override_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_CONTAINER_VIEW_PROP_REORDERABLE
argument_list|,
literal|"reorderable"
argument_list|)
expr_stmt|;
name|g_object_class_override_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_CONTAINER_VIEW_PROP_PREVIEW_SIZE
argument_list|,
literal|"preview-size"
argument_list|)
expr_stmt|;
name|g_object_class_override_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_CONTAINER_VIEW_PROP_PREVIEW_BORDER_WIDTH
argument_list|,
literal|"preview-border-width"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_combo_box_init (GimpContainerComboBox * combo_box)
name|gimp_container_combo_box_init
parameter_list|(
name|GimpContainerComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GtkCellLayout
modifier|*
name|layout
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|store
operator|=
name|gtk_list_store_new
argument_list|(
name|NUM_COLUMNS
argument_list|,
name|GIMP_TYPE_VIEW_RENDERER
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
name|gtk_combo_box_set_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|layout
operator|=
name|GTK_CELL_LAYOUT
argument_list|(
name|combo_box
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gimp_cell_renderer_viewable_new
argument_list|()
expr_stmt|;
name|gtk_cell_layout_pack_start
argument_list|(
name|layout
argument_list|,
name|cell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_cell_layout_set_attributes
argument_list|(
name|layout
argument_list|,
name|cell
argument_list|,
literal|"renderer"
argument_list|,
name|COLUMN_RENDERER
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|combo_box
operator|->
name|viewable_renderer
operator|=
name|cell
expr_stmt|;
name|cell
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_CELL_RENDERER_TEXT
argument_list|,
literal|"ellipsize"
argument_list|,
name|PANGO_ELLIPSIZE_MIDDLE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_cell_layout_pack_start
argument_list|(
name|layout
argument_list|,
name|cell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_cell_layout_set_attributes
argument_list|(
name|layout
argument_list|,
name|cell
argument_list|,
literal|"text"
argument_list|,
name|COLUMN_NAME
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo_box
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_combo_box_changed
argument_list|)
argument_list|,
name|combo_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_combo_box_view_iface_init (GimpContainerViewInterface * view_iface)
name|gimp_container_combo_box_view_iface_init
parameter_list|(
name|GimpContainerViewInterface
modifier|*
name|view_iface
parameter_list|)
block|{
name|parent_view_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|view_iface
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
name|view_iface
operator|->
name|insert_item
operator|=
name|gimp_container_combo_box_insert_item
expr_stmt|;
name|view_iface
operator|->
name|remove_item
operator|=
name|gimp_container_combo_box_remove_item
expr_stmt|;
name|view_iface
operator|->
name|reorder_item
operator|=
name|gimp_container_combo_box_reorder_item
expr_stmt|;
name|view_iface
operator|->
name|rename_item
operator|=
name|gimp_container_combo_box_rename_item
expr_stmt|;
name|view_iface
operator|->
name|select_item
operator|=
name|gimp_container_combo_box_select_item
expr_stmt|;
name|view_iface
operator|->
name|clear_items
operator|=
name|gimp_container_combo_box_clear_items
expr_stmt|;
name|view_iface
operator|->
name|set_preview_size
operator|=
name|gimp_container_combo_box_set_preview_size
expr_stmt|;
name|view_iface
operator|->
name|insert_data_free
operator|=
operator|(
name|GDestroyNotify
operator|)
name|g_free
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_container_combo_box_new (GimpContainer * container,GimpContext * context,gint preview_size,gint preview_border_width)
name|gimp_container_combo_box_new
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
name|preview_border_width
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|combo_box
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
name|combo_box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CONTAINER_COMBO_BOX
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|view
operator|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|combo_box
argument_list|)
expr_stmt|;
name|gimp_container_view_set_preview_size
argument_list|(
name|view
argument_list|,
name|preview_size
argument_list|,
name|preview_border_width
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
name|combo_box
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_combo_box_set (GimpContainerComboBox * combo_box,GtkTreeIter * iter,GimpViewable * viewable)
name|gimp_container_combo_box_set
parameter_list|(
name|GimpContainerComboBox
modifier|*
name|combo_box
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|GimpContainerView
modifier|*
name|view
init|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|combo_box
argument_list|)
decl_stmt|;
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GimpViewRenderer
modifier|*
name|renderer
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gint
name|preview_size
decl_stmt|;
name|gint
name|border_width
decl_stmt|;
name|model
operator|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
name|preview_size
operator|=
name|gimp_container_view_get_preview_size
argument_list|(
name|view
argument_list|,
operator|&
name|border_width
argument_list|)
expr_stmt|;
name|name
operator|=
name|gimp_viewable_get_description
argument_list|(
name|viewable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|renderer
operator|=
name|gimp_view_renderer_new
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|preview_size
argument_list|,
name|border_width
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_view_renderer_set_viewable
argument_list|(
name|renderer
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
name|gimp_view_renderer_remove_idle
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|renderer
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_combo_box_renderer_update
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|iter
argument_list|,
name|COLUMN_RENDERER
argument_list|,
name|renderer
argument_list|,
name|COLUMN_NAME
argument_list|,
name|name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  GimpContainerView methods  */
end_comment

begin_function
specifier|static
name|gpointer
DECL|function|gimp_container_combo_box_insert_item (GimpContainerView * view,GimpViewable * viewable,gint index)
name|gimp_container_combo_box_insert_item
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
name|GtkTreeModel
modifier|*
name|model
init|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|view
argument_list|)
argument_list|)
decl_stmt|;
name|GtkTreeIter
modifier|*
name|iter
decl_stmt|;
name|iter
operator|=
name|g_new0
argument_list|(
name|GtkTreeIter
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|==
operator|-
literal|1
condition|)
name|gtk_list_store_append
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|iter
argument_list|)
expr_stmt|;
else|else
name|gtk_list_store_insert
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|iter
argument_list|,
name|index
argument_list|)
expr_stmt|;
name|gimp_container_combo_box_set
argument_list|(
name|GIMP_CONTAINER_COMBO_BOX
argument_list|(
name|view
argument_list|)
argument_list|,
name|iter
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
return|return
operator|(
name|gpointer
operator|)
name|iter
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_combo_box_remove_item (GimpContainerView * view,GimpViewable * viewable,gpointer insert_data)
name|gimp_container_combo_box_remove_item
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
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|view
argument_list|)
argument_list|)
decl_stmt|;
name|GtkTreeIter
modifier|*
name|iter
init|=
name|insert_data
decl_stmt|;
if|if
condition|(
name|iter
condition|)
block|{
name|gtk_list_store_remove
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|iter
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: remove this hack as soon as bug #149906 is fixed
endif|#
directive|endif
comment|/*  if the store is empty after this remove, clear out renderers        *  from all cells so they don't keep refing the viewables        */
if|if
condition|(
operator|!
name|gtk_tree_model_iter_n_children
argument_list|(
name|model
argument_list|,
name|NULL
argument_list|)
condition|)
name|g_object_set
argument_list|(
name|GIMP_CONTAINER_COMBO_BOX
argument_list|(
name|view
argument_list|)
operator|->
name|viewable_renderer
argument_list|,
literal|"renderer"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_combo_box_reorder_item (GimpContainerView * view,GimpViewable * viewable,gint new_index,gpointer insert_data)
name|gimp_container_combo_box_reorder_item
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
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|view
argument_list|)
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
name|GtkTreeIter
modifier|*
name|iter
init|=
name|insert_data
decl_stmt|;
if|if
condition|(
operator|!
name|iter
condition|)
return|return;
if|if
condition|(
name|new_index
operator|==
operator|-
literal|1
operator|||
name|new_index
operator|==
name|container
operator|->
name|num_children
operator|-
literal|1
condition|)
block|{
name|gtk_list_store_move_before
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|iter
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|new_index
operator|==
literal|0
condition|)
block|{
name|gtk_list_store_move_after
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|iter
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|gint
name|old_index
decl_stmt|;
name|path
operator|=
name|gtk_tree_model_get_path
argument_list|(
name|model
argument_list|,
name|iter
argument_list|)
expr_stmt|;
name|old_index
operator|=
name|gtk_tree_path_get_indices
argument_list|(
name|path
argument_list|)
index|[
literal|0
index|]
expr_stmt|;
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_index
operator|!=
name|old_index
condition|)
block|{
name|GtkTreeIter
name|place
decl_stmt|;
name|path
operator|=
name|gtk_tree_path_new_from_indices
argument_list|(
name|new_index
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_tree_model_get_iter
argument_list|(
name|model
argument_list|,
operator|&
name|place
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_index
operator|>
name|old_index
condition|)
name|gtk_list_store_move_after
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|iter
argument_list|,
operator|&
name|place
argument_list|)
expr_stmt|;
else|else
name|gtk_list_store_move_before
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|iter
argument_list|,
operator|&
name|place
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_combo_box_rename_item (GimpContainerView * view,GimpViewable * viewable,gpointer insert_data)
name|gimp_container_combo_box_rename_item
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
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|view
argument_list|)
argument_list|)
decl_stmt|;
name|GtkTreeIter
modifier|*
name|iter
init|=
name|insert_data
decl_stmt|;
if|if
condition|(
name|iter
condition|)
block|{
name|gchar
modifier|*
name|name
init|=
name|gimp_viewable_get_description
argument_list|(
name|viewable
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|iter
argument_list|,
name|COLUMN_NAME
argument_list|,
name|name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_container_combo_box_select_item (GimpContainerView * view,GimpViewable * viewable,gpointer insert_data)
name|gimp_container_combo_box_select_item
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
name|GtkComboBox
modifier|*
name|combo_box
init|=
name|GTK_COMBO_BOX
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
name|combo_box
argument_list|,
name|gimp_container_combo_box_changed
argument_list|,
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|iter
condition|)
block|{
name|gtk_combo_box_set_active_iter
argument_list|(
name|combo_box
argument_list|,
name|iter
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_combo_box_set_active
argument_list|(
name|combo_box
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
name|g_signal_handlers_unblock_by_func
argument_list|(
name|combo_box
argument_list|,
name|gimp_container_combo_box_changed
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
DECL|function|gimp_container_combo_box_clear_items (GimpContainerView * view)
name|gimp_container_combo_box_clear_items
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
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|view
argument_list|)
argument_list|)
decl_stmt|;
name|gtk_list_store_clear
argument_list|(
name|GTK_LIST_STORE
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
DECL|function|gimp_container_combo_box_set_preview_size (GimpContainerView * view)
name|gimp_container_combo_box_set_preview_size
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
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|view
argument_list|)
argument_list|)
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
name|gint
name|preview_size
decl_stmt|;
name|gint
name|border_width
decl_stmt|;
name|preview_size
operator|=
name|gimp_container_view_get_preview_size
argument_list|(
name|view
argument_list|,
operator|&
name|border_width
argument_list|)
expr_stmt|;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
control|)
block|{
name|GimpViewRenderer
modifier|*
name|renderer
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_RENDERER
argument_list|,
operator|&
name|renderer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_view_renderer_set_size
argument_list|(
name|renderer
argument_list|,
name|preview_size
argument_list|,
name|border_width
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_combo_box_changed (GtkComboBox * combo_box,GimpContainerView * view)
name|gimp_container_combo_box_changed
parameter_list|(
name|GtkComboBox
modifier|*
name|combo_box
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
name|parent_class
operator|->
name|changed
condition|)
name|parent_class
operator|->
name|changed
argument_list|(
name|combo_box
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_combo_box_get_active_iter
argument_list|(
name|combo_box
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|GimpViewRenderer
modifier|*
name|renderer
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|gtk_combo_box_get_model
argument_list|(
name|combo_box
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_RENDERER
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_combo_box_renderer_update (GimpViewRenderer * renderer,GimpContainerView * view)
name|gimp_container_combo_box_renderer_update
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|GtkTreeIter
modifier|*
name|iter
init|=
name|gimp_container_view_lookup
argument_list|(
name|view
argument_list|,
name|renderer
operator|->
name|viewable
argument_list|)
decl_stmt|;
if|if
condition|(
name|iter
condition|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|view
argument_list|)
argument_list|)
decl_stmt|;
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|path
operator|=
name|gtk_tree_model_get_path
argument_list|(
name|model
argument_list|,
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_model_row_changed
argument_list|(
name|model
argument_list|,
name|path
argument_list|,
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

