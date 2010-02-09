begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpitemtree.h  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ITEM_TREE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ITEM_TREE_H__
define|#
directive|define
name|__GIMP_ITEM_TREE_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_ITEM_TREE
define|#
directive|define
name|GIMP_TYPE_ITEM_TREE
value|(gimp_item_tree_get_type ())
end_define

begin_define
DECL|macro|GIMP_ITEM_TREE (obj)
define|#
directive|define
name|GIMP_ITEM_TREE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ITEM_TREE, GimpItemTree))
end_define

begin_define
DECL|macro|GIMP_ITEM_TREE_CLASS (klass)
define|#
directive|define
name|GIMP_ITEM_TREE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ITEM_TREE, GimpItemTreeClass))
end_define

begin_define
DECL|macro|GIMP_IS_ITEM_TREE (obj)
define|#
directive|define
name|GIMP_IS_ITEM_TREE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ITEM_TREE))
end_define

begin_define
DECL|macro|GIMP_IS_ITEM_TREE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ITEM_TREE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ITEM_TREE))
end_define

begin_typedef
DECL|typedef|GimpItemTreeClass
typedef|typedef
name|struct
name|_GimpItemTreeClass
name|GimpItemTreeClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpItemTree
struct|struct
name|_GimpItemTree
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|container
name|GimpContainer
modifier|*
name|container
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpItemTreeClass
struct|struct
name|_GimpItemTreeClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_item_tree_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpItemTree
modifier|*
name|gimp_item_tree_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GType
name|container_type
parameter_list|,
name|GType
name|item_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|gimp_item_tree_get_active_item
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_tree_set_active_item
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|gimp_item_tree_get_item_by_name
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_tree_get_insert_pos
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpItem
modifier|*
modifier|*
name|parent
parameter_list|,
name|gint
modifier|*
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_tree_add_item
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpItem
modifier|*
name|parent
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|gimp_item_tree_remove_item
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpItem
modifier|*
name|new_active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_tree_reorder_item
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpItem
modifier|*
name|new_parent
parameter_list|,
name|gint
name|new_index
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_tree_rename_item
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_ITEM_TREE_H__  */
end_comment

end_unit

