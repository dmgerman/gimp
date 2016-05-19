begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpitemtreeview.h  * Copyright (C) 2001-2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ITEM_TREE_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ITEM_TREE_VIEW_H__
define|#
directive|define
name|__GIMP_ITEM_TREE_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpcontainertreeview.h"
end_include

begin_typedef
DECL|typedef|GimpGetContainerFunc
typedef|typedef
name|GimpContainer
modifier|*
function_decl|(
modifier|*
name|GimpGetContainerFunc
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpGetItemFunc
typedef|typedef
name|GimpItem
modifier|*
function_decl|(
modifier|*
name|GimpGetItemFunc
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpSetItemFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpSetItemFunc
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpAddItemFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpAddItemFunc
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|index
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpRemoveItemFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpRemoveItemFunc
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
name|GimpItem
modifier|*
name|new_active
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpNewItemFunc
typedef|typedef
name|GimpItem
modifier|*
function_decl|(
modifier|*
name|GimpNewItemFunc
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ITEM_TREE_VIEW
define|#
directive|define
name|GIMP_TYPE_ITEM_TREE_VIEW
value|(gimp_item_tree_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_ITEM_TREE_VIEW (obj)
define|#
directive|define
name|GIMP_ITEM_TREE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ITEM_TREE_VIEW, GimpItemTreeView))
end_define

begin_define
DECL|macro|GIMP_ITEM_TREE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_ITEM_TREE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ITEM_TREE_VIEW, GimpItemTreeViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_ITEM_TREE_VIEW (obj)
define|#
directive|define
name|GIMP_IS_ITEM_TREE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ITEM_TREE_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_ITEM_TREE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ITEM_TREE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ITEM_TREE_VIEW))
end_define

begin_define
DECL|macro|GIMP_ITEM_TREE_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ITEM_TREE_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ITEM_TREE_VIEW, GimpItemTreeViewClass))
end_define

begin_typedef
DECL|typedef|GimpItemTreeViewClass
typedef|typedef
name|struct
name|_GimpItemTreeViewClass
name|GimpItemTreeViewClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpItemTreeViewPriv
typedef|typedef
name|struct
name|_GimpItemTreeViewPriv
name|GimpItemTreeViewPriv
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpItemTreeView
struct|struct
name|_GimpItemTreeView
block|{
DECL|member|parent_instance
name|GimpContainerTreeView
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpItemTreeViewPriv
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpItemTreeViewClass
struct|struct
name|_GimpItemTreeViewClass
block|{
DECL|member|parent_class
name|GimpContainerTreeViewClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|set_image
name|void
function_decl|(
modifier|*
name|set_image
function_decl|)
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
DECL|member|item_type
name|GType
name|item_type
decl_stmt|;
DECL|member|signal_name
specifier|const
name|gchar
modifier|*
name|signal_name
decl_stmt|;
comment|/*  virtual functions for manipulating the image's item tree  */
DECL|member|get_container
name|GimpGetContainerFunc
name|get_container
decl_stmt|;
DECL|member|get_active_item
name|GimpGetItemFunc
name|get_active_item
decl_stmt|;
DECL|member|set_active_item
name|GimpSetItemFunc
name|set_active_item
decl_stmt|;
DECL|member|add_item
name|GimpAddItemFunc
name|add_item
decl_stmt|;
DECL|member|remove_item
name|GimpRemoveItemFunc
name|remove_item
decl_stmt|;
DECL|member|new_item
name|GimpNewItemFunc
name|new_item
decl_stmt|;
comment|/*  action names  */
DECL|member|action_group
specifier|const
name|gchar
modifier|*
name|action_group
decl_stmt|;
DECL|member|activate_action
specifier|const
name|gchar
modifier|*
name|activate_action
decl_stmt|;
DECL|member|edit_action
specifier|const
name|gchar
modifier|*
name|edit_action
decl_stmt|;
DECL|member|new_action
specifier|const
name|gchar
modifier|*
name|new_action
decl_stmt|;
DECL|member|new_default_action
specifier|const
name|gchar
modifier|*
name|new_default_action
decl_stmt|;
DECL|member|raise_action
specifier|const
name|gchar
modifier|*
name|raise_action
decl_stmt|;
DECL|member|raise_top_action
specifier|const
name|gchar
modifier|*
name|raise_top_action
decl_stmt|;
DECL|member|lower_action
specifier|const
name|gchar
modifier|*
name|lower_action
decl_stmt|;
DECL|member|lower_bottom_action
specifier|const
name|gchar
modifier|*
name|lower_bottom_action
decl_stmt|;
DECL|member|duplicate_action
specifier|const
name|gchar
modifier|*
name|duplicate_action
decl_stmt|;
DECL|member|delete_action
specifier|const
name|gchar
modifier|*
name|delete_action
decl_stmt|;
comment|/*  lock content button appearance  */
DECL|member|lock_content_icon_name
specifier|const
name|gchar
modifier|*
name|lock_content_icon_name
decl_stmt|;
DECL|member|lock_content_tooltip
specifier|const
name|gchar
modifier|*
name|lock_content_tooltip
decl_stmt|;
DECL|member|lock_content_help_id
specifier|const
name|gchar
modifier|*
name|lock_content_help_id
decl_stmt|;
comment|/* lock position (translation and transformation) button appearance */
DECL|member|lock_position_icon_name
specifier|const
name|gchar
modifier|*
name|lock_position_icon_name
decl_stmt|;
DECL|member|lock_position_tooltip
specifier|const
name|gchar
modifier|*
name|lock_position_tooltip
decl_stmt|;
DECL|member|lock_position_help_id
specifier|const
name|gchar
modifier|*
name|lock_position_help_id
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_item_tree_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_item_tree_view_new
parameter_list|(
name|GType
name|view_type
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_facotry
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_identifier
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_tree_view_set_image
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_item_tree_view_get_image
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_tree_view_add_options
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|GtkWidget
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_item_tree_view_get_lock_box
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_item_tree_view_get_new_button
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_item_tree_view_get_edit_button
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_item_tree_view_get_drop_index
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|dest_viewable
parameter_list|,
name|GtkTreeViewDropPosition
name|drop_pos
parameter_list|,
name|GimpViewable
modifier|*
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_ITEM_TREE_VIEW_H__  */
end_comment

end_unit

