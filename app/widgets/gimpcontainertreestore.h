begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainertreestore.h  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_TREE_STORE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_TREE_STORE_H__
define|#
directive|define
name|__GIMP_CONTAINER_TREE_STORE_H__
end_define

begin_enum
enum|enum
DECL|enum|__anon2b849b7f0103
block|{
DECL|enumerator|GIMP_CONTAINER_TREE_STORE_COLUMN_RENDERER
name|GIMP_CONTAINER_TREE_STORE_COLUMN_RENDERER
block|,
DECL|enumerator|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME
name|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME
block|,
DECL|enumerator|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME_ATTRIBUTES
name|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME_ATTRIBUTES
block|,
DECL|enumerator|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME_SENSITIVE
name|GIMP_CONTAINER_TREE_STORE_COLUMN_NAME_SENSITIVE
block|,
DECL|enumerator|GIMP_CONTAINER_TREE_STORE_COLUMN_USER_DATA
name|GIMP_CONTAINER_TREE_STORE_COLUMN_USER_DATA
block|,
DECL|enumerator|GIMP_CONTAINER_TREE_STORE_N_COLUMNS
name|GIMP_CONTAINER_TREE_STORE_N_COLUMNS
block|}
enum|;
end_enum

begin_define
DECL|macro|GIMP_TYPE_CONTAINER_TREE_STORE
define|#
directive|define
name|GIMP_TYPE_CONTAINER_TREE_STORE
value|(gimp_container_tree_store_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTAINER_TREE_STORE (obj)
define|#
directive|define
name|GIMP_CONTAINER_TREE_STORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTAINER_TREE_STORE, GimpContainerTreeStore))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_TREE_STORE_CLASS (klass)
define|#
directive|define
name|GIMP_CONTAINER_TREE_STORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTAINER_TREE_STORE, GimpContainerTreeStoreClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_TREE_STORE (obj)
define|#
directive|define
name|GIMP_IS_CONTAINER_TREE_STORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTAINER_TREE_STORE))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_TREE_STORE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTAINER_TREE_STORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTAINER_TREE_STORE))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_TREE_STORE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTAINER_TREE_STORE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTAINER_TREE_STORE, GimpContainerTreeStoreClass))
end_define

begin_typedef
DECL|typedef|GimpContainerTreeStoreClass
typedef|typedef
name|struct
name|_GimpContainerTreeStoreClass
name|GimpContainerTreeStoreClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContainerTreeStore
struct|struct
name|_GimpContainerTreeStore
block|{
DECL|member|parent_instance
name|GtkTreeStore
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpContainerTreeStoreClass
struct|struct
name|_GimpContainerTreeStoreClass
block|{
DECL|member|parent_class
name|GtkTreeStoreClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_container_tree_store_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|gint
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
function_decl|;
end_function_decl

begin_function_decl
name|GtkTreeModel
modifier|*
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
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_tree_store_set_use_name
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|,
name|gboolean
name|use_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_container_tree_store_get_use_name
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|GtkTreeIter
modifier|*
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
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_tree_store_clear_items
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_tree_store_set_view_size
parameter_list|(
name|GimpContainerTreeStore
modifier|*
name|store
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CONTAINER_TREE_STORE_H__  */
end_comment

end_unit

