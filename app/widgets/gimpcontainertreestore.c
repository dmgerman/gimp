begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainertreestore.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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

begin_enum
enum|enum
DECL|enum|__anon2b688e5d0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONTAINER_VIEW
name|PROP_CONTAINER_VIEW
block|,
DECL|enumerator|PROP_USE_NAME
name|PROP_USE_NAME
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpContainerTreeStorePrivate
typedef|typedef
name|struct
name|_GimpContainerTreeStorePrivate
name|GimpContainerTreeStorePrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContainerTreeStorePrivate
struct|struct
name|_GimpContainerTreeStorePrivate
block|{
DECL|member|container_view
name|GimpContainerView
modifier|*
name|container_view
decl_stmt|;
DECL|member|renderer_cells
name|GList
modifier|*
name|renderer_cells
decl_stmt|;
DECL|member|use_name
name|gboolean
name|use_name
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (store)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|store
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (store, \                                      GIMP_TYPE_CONTAINER_TREE_STORE, \                                      GimpContainerTreeStorePrivate)
end_define

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_container_tree_store_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_tree_store_finalize
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
name|gimp_container_tree_store_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_tree_store_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_tree_store_set
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
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
name|gimp_container_tree_store_renderer_update
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpContainerTreeStore,gimp_container_tree_store,GTK_TYPE_TREE_STORE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpContainerTreeStore
argument_list|,
argument|gimp_container_tree_store
argument_list|,
argument|GTK_TYPE_TREE_STORE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_container_tree_store_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_container_tree_store_class_init
parameter_list|(
name|GimpContainerTreeStoreClass
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
name|constructor
operator|=
name|gimp_container_tree_store_constructor
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_container_tree_store_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_container_tree_store_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_container_tree_store_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTAINER_VIEW
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"container-view"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CONTAINER_VIEW
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_NAME
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"use-name"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpContainerTreeStorePrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_tree_store_init (GimpContainerTreeStore * store)
name|gimp_container_tree_store_init
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_container_tree_store_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_container_tree_store_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GimpContainerTreeStore
modifier|*
name|store
decl_stmt|;
name|GObject
modifier|*
name|object
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|store
operator|=
name|GIMP_CONTAINER_TREE_STORE
argument_list|(
name|object
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_tree_store_finalize (GObject * object)
name|gimp_container_tree_store_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpContainerTreeStorePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|renderer_cells
condition|)
block|{
name|g_list_free
argument_list|(
name|private
operator|->
name|renderer_cells
argument_list|)
expr_stmt|;
name|private
operator|->
name|renderer_cells
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
DECL|function|gimp_container_tree_store_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_container_tree_store_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpContainerTreeStorePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CONTAINER_VIEW
case|:
name|private
operator|->
name|container_view
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
comment|/* don't ref */
break|break;
case|case
name|PROP_USE_NAME
case|:
name|private
operator|->
name|use_name
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_tree_store_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_container_tree_store_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpContainerTreeStorePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CONTAINER_VIEW
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|container_view
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_NAME
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|use_name
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkTreeModel
modifier|*
DECL|function|gimp_container_tree_store_new (GimpContainerView * container_view,gint n_columns,GType * types)
name|gimp_container_tree_store_new
parameter_list|(
name|GimpContainerView
modifier|*
name|container_view
parameter_list|,
name|gint
name|n_columns
parameter_list|,
name|GType
modifier|*
name|types
parameter_list|)
block|{
name|GimpContainerTreeStore
modifier|*
name|store
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_VIEW
argument_list|(
name|container_view
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_columns
operator|>=
name|GIMP_CONTAINER_TREE_STORE_N_COLUMNS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|types
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|store
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CONTAINER_TREE_STORE
argument_list|,
literal|"container-view"
argument_list|,
name|container_view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_store_set_column_types
argument_list|(
name|GTK_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|n_columns
argument_list|,
name|types
argument_list|)
expr_stmt|;
return|return
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_tree_store_add_renderer_cell (GimpContainerTreeStore * store,GtkCellRenderer * cell)
name|gimp_container_tree_store_add_renderer_cell
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|,
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|)
block|{
name|GimpContainerTreeStorePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CELL_RENDERER_VIEWABLE
argument_list|(
name|cell
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|private
operator|->
name|renderer_cells
operator|=
name|g_list_prepend
argument_list|(
name|private
operator|->
name|renderer_cells
argument_list|,
name|cell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_tree_store_set_use_name (GimpContainerTreeStore * store,gboolean use_name)
name|gimp_container_tree_store_set_use_name
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|,
name|gboolean
name|use_name
parameter_list|)
block|{
name|GimpContainerTreeStorePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|use_name
operator|!=
name|use_name
condition|)
block|{
name|private
operator|->
name|use_name
operator|=
name|use_name
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|store
argument_list|)
argument_list|,
literal|"use-name"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_container_tree_store_get_use_name (GimpContainerTreeStore * store)
name|gimp_container_tree_store_get_use_name
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
operator|->
name|use_name
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_container_tree_store_set_context_foreach (GtkTreeModel * model,GtkTreePath * path,GtkTreeIter * iter,gpointer data)
name|gimp_container_tree_store_set_context_foreach
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreePath
modifier|*
name|path
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|data
decl_stmt|;
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
name|gimp_view_renderer_set_context
argument_list|(
name|renderer
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_tree_store_set_context (GimpContainerTreeStore * store,GimpContext * context)
name|gimp_container_tree_store_set_context
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_tree_model_foreach
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|,
name|gimp_container_tree_store_set_context_foreach
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkTreeIter
modifier|*
DECL|function|gimp_container_tree_store_insert_item (GimpContainerTreeStore * store,GimpViewable * viewable,GtkTreeIter * parent,gint index)
name|gimp_container_tree_store_insert_item
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GtkTreeIter
modifier|*
name|parent
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|==
operator|-
literal|1
condition|)
name|gtk_tree_store_append
argument_list|(
name|GTK_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|parent
argument_list|)
expr_stmt|;
else|else
name|gtk_tree_store_insert
argument_list|(
name|GTK_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|parent
argument_list|,
name|index
argument_list|)
expr_stmt|;
name|gimp_container_tree_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
return|return
name|gtk_tree_iter_copy
argument_list|(
operator|&
name|iter
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_tree_store_remove_item (GimpContainerTreeStore * store,GimpViewable * viewable,GtkTreeIter * iter)
name|gimp_container_tree_store_remove_item
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
if|if
condition|(
name|iter
condition|)
block|{
name|gtk_tree_store_remove
argument_list|(
name|GTK_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|iter
argument_list|)
expr_stmt|;
comment|/*  If the store is empty after this remove, clear out renderers        *  from all cells so they don't keep refing the viewables        *  (see bug #149906).        */
if|if
condition|(
operator|!
name|gtk_tree_model_iter_n_children
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|GimpContainerTreeStorePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|private
operator|->
name|renderer_cells
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
name|g_object_set
argument_list|(
name|list
operator|->
name|data
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
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_tree_store_reorder_item (GimpContainerTreeStore * store,GimpViewable * viewable,gint new_index,GtkTreeIter * iter)
name|gimp_container_tree_store_reorder_item
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|new_index
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|GimpContainerTreeStorePrivate
modifier|*
name|private
decl_stmt|;
name|GimpViewable
modifier|*
name|parent
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|iter
condition|)
return|return;
name|parent
operator|=
name|gimp_viewable_get_parent
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|parent
condition|)
name|container
operator|=
name|gimp_viewable_get_children
argument_list|(
name|parent
argument_list|)
expr_stmt|;
else|else
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|private
operator|->
name|container_view
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_index
operator|==
operator|-
literal|1
operator|||
name|new_index
operator|==
name|gimp_container_get_n_children
argument_list|(
name|container
argument_list|)
operator|-
literal|1
condition|)
block|{
name|gtk_tree_store_move_before
argument_list|(
name|GTK_TREE_STORE
argument_list|(
name|store
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
name|gtk_tree_store_move_after
argument_list|(
name|GTK_TREE_STORE
argument_list|(
name|store
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
name|GtkTreeIter
name|place_iter
decl_stmt|;
name|gint
name|depth
decl_stmt|;
name|gint
modifier|*
name|indices
decl_stmt|;
name|gint
name|old_index
decl_stmt|;
name|path
operator|=
name|gtk_tree_model_get_path
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|,
name|iter
argument_list|)
expr_stmt|;
name|indices
operator|=
name|gtk_tree_path_get_indices
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|depth
operator|=
name|gtk_tree_path_get_depth
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|old_index
operator|=
name|indices
index|[
name|depth
operator|-
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|new_index
operator|!=
name|old_index
condition|)
block|{
name|indices
index|[
name|depth
operator|-
literal|1
index|]
operator|=
name|new_index
expr_stmt|;
name|gtk_tree_model_get_iter
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|place_iter
argument_list|,
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_index
operator|>
name|old_index
condition|)
name|gtk_tree_store_move_after
argument_list|(
name|GTK_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|iter
argument_list|,
operator|&
name|place_iter
argument_list|)
expr_stmt|;
else|else
name|gtk_tree_store_move_before
argument_list|(
name|GTK_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|iter
argument_list|,
operator|&
name|place_iter
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
end_function

begin_function
name|gboolean
DECL|function|gimp_container_tree_store_rename_item (GimpContainerTreeStore * store,GimpViewable * viewable,GtkTreeIter * iter)
name|gimp_container_tree_store_rename_item
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|gboolean
name|new_name_shorter
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|iter
condition|)
block|{
name|GimpContainerTreeStorePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
modifier|*
name|old_name
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|use_name
condition|)
name|name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gimp_object_get_name
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
else|else
name|name
operator|=
name|gimp_viewable_get_description
argument_list|(
name|viewable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|,
name|iter
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME
argument_list|,
operator|&
name|old_name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_tree_store_set
argument_list|(
name|GTK_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|iter
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME
argument_list|,
name|name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|name
operator|&&
name|old_name
operator|&&
name|strlen
argument_list|(
name|name
argument_list|)
operator|<
name|strlen
argument_list|(
name|old_name
argument_list|)
condition|)
name|new_name_shorter
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|!
name|private
operator|->
name|use_name
condition|)
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|old_name
argument_list|)
expr_stmt|;
block|}
return|return
name|new_name_shorter
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_tree_store_clear_items (GimpContainerTreeStore * store)
name|gimp_container_tree_store_clear_items
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_tree_store_clear
argument_list|(
name|GTK_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  If the store is empty after this remove, clear out renderers    *  from all cells so they don't keep refing the viewables    *  (see bug #149906).    */
if|if
condition|(
operator|!
name|gtk_tree_model_iter_n_children
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|GimpContainerTreeStorePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|private
operator|->
name|renderer_cells
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
name|g_object_set
argument_list|(
name|list
operator|->
name|data
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b688e5d0208
block|{
DECL|member|view_size
name|gint
name|view_size
decl_stmt|;
DECL|member|border_width
name|gint
name|border_width
decl_stmt|;
DECL|typedef|SetSizeForeachData
block|}
name|SetSizeForeachData
typedef|;
end_typedef

begin_function
specifier|static
name|gboolean
DECL|function|gimp_container_tree_store_set_view_size_foreach (GtkTreeModel * model,GtkTreePath * path,GtkTreeIter * iter,gpointer data)
name|gimp_container_tree_store_set_view_size_foreach
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreePath
modifier|*
name|path
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|SetSizeForeachData
modifier|*
name|size_data
init|=
name|data
decl_stmt|;
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
name|gimp_view_renderer_set_size
argument_list|(
name|renderer
argument_list|,
name|size_data
operator|->
name|view_size
argument_list|,
name|size_data
operator|->
name|border_width
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_tree_store_set_view_size (GimpContainerTreeStore * store)
name|gimp_container_tree_store_set_view_size
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|)
block|{
name|GimpContainerTreeStorePrivate
modifier|*
name|private
decl_stmt|;
name|SetSizeForeachData
name|size_data
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|size_data
operator|.
name|view_size
operator|=
name|gimp_container_view_get_view_size
argument_list|(
name|private
operator|->
name|container_view
argument_list|,
operator|&
name|size_data
operator|.
name|border_width
argument_list|)
expr_stmt|;
name|gtk_tree_model_foreach
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|,
name|gimp_container_tree_store_set_view_size_foreach
argument_list|,
operator|&
name|size_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
name|void
DECL|function|gimp_container_tree_store_columns_init (GType * types,gint * n_types)
name|gimp_container_tree_store_columns_init
parameter_list|(
name|GType
modifier|*
name|types
parameter_list|,
name|gint
modifier|*
name|n_types
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|types
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|n_types
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|*
name|n_types
operator|==
literal|0
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_CONTAINER_TREE_STORE_COLUMN_RENDERER
operator|==
name|gimp_container_tree_store_columns_add
argument_list|(
name|types
argument_list|,
name|n_types
argument_list|,
name|GIMP_TYPE_VIEW_RENDERER
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME
operator|==
name|gimp_container_tree_store_columns_add
argument_list|(
name|types
argument_list|,
name|n_types
argument_list|,
name|G_TYPE_STRING
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME_ATTRIBUTES
operator|==
name|gimp_container_tree_store_columns_add
argument_list|(
name|types
argument_list|,
name|n_types
argument_list|,
name|PANGO_TYPE_ATTR_LIST
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME_SENSITIVE
operator|==
name|gimp_container_tree_store_columns_add
argument_list|(
name|types
argument_list|,
name|n_types
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_CONTAINER_TREE_STORE_COLUMN_USER_DATA
operator|==
name|gimp_container_tree_store_columns_add
argument_list|(
name|types
argument_list|,
name|n_types
argument_list|,
name|G_TYPE_POINTER
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_container_tree_store_columns_add (GType * types,gint * n_types,GType type)
name|gimp_container_tree_store_columns_add
parameter_list|(
name|GType
modifier|*
name|types
parameter_list|,
name|gint
modifier|*
name|n_types
parameter_list|,
name|GType
name|type
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|types
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_types
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|*
name|n_types
operator|>=
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|types
index|[
operator|*
name|n_types
index|]
operator|=
name|type
expr_stmt|;
operator|(
operator|*
name|n_types
operator|)
operator|++
expr_stmt|;
return|return
operator|*
name|n_types
operator|-
literal|1
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_tree_store_set (GimpContainerTreeStore * store,GtkTreeIter * iter,GimpViewable * viewable)
name|gimp_container_tree_store_set
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
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
name|GimpContainerTreeStorePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
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
name|view_size
decl_stmt|;
name|gint
name|border_width
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|private
operator|->
name|container_view
argument_list|)
expr_stmt|;
name|view_size
operator|=
name|gimp_container_view_get_view_size
argument_list|(
name|private
operator|->
name|container_view
argument_list|,
operator|&
name|border_width
argument_list|)
expr_stmt|;
name|renderer
operator|=
name|gimp_view_renderer_new
argument_list|(
name|context
argument_list|,
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|view_size
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
name|gimp_container_tree_store_renderer_update
argument_list|)
argument_list|,
name|store
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|use_name
condition|)
name|name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gimp_object_get_name
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
else|else
name|name
operator|=
name|gimp_viewable_get_description
argument_list|(
name|viewable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_store_set
argument_list|(
name|GTK_TREE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|iter
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_RENDERER
argument_list|,
name|renderer
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME
argument_list|,
name|name
argument_list|,
name|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME_SENSITIVE
argument_list|,
name|TRUE
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|private
operator|->
name|use_name
condition|)
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_tree_store_renderer_update (GimpViewRenderer * renderer,GimpContainerTreeStore * store)
name|gimp_container_tree_store_renderer_update
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|)
block|{
name|GimpContainerTreeStorePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
decl_stmt|;
name|GtkTreeIter
modifier|*
name|iter
decl_stmt|;
name|iter
operator|=
name|gimp_container_view_lookup
argument_list|(
name|private
operator|->
name|container_view
argument_list|,
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|iter
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
name|store
argument_list|)
argument_list|,
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_model_row_changed
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
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

