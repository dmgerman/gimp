begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpitemlistview.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ITEM_LIST_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ITEM_LIST_VIEW_H__
define|#
directive|define
name|__GIMP_ITEM_LIST_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpcontainerlistview.h"
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
specifier|const
name|GimpImage
modifier|*
name|gimage
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
specifier|const
name|GimpImage
modifier|*
name|gimage
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
name|gimage
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpReorderItemFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpReorderItemFunc
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpItem
modifier|*
name|item
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
name|gimage
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|index
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
name|gimage
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpConvertItemFunc
typedef|typedef
name|GimpItem
modifier|*
function_decl|(
modifier|*
name|GimpConvertItemFunc
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpImage
modifier|*
name|dest_gimage
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpNewItemFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpNewItemFunc
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpItem
modifier|*
name|template
parameter_list|,
name|gboolean
name|interactive
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpEditItemFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpEditItemFunc
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpActivateItemFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpActivateItemFunc
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ITEM_LIST_VIEW
define|#
directive|define
name|GIMP_TYPE_ITEM_LIST_VIEW
value|(gimp_item_list_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_ITEM_LIST_VIEW (obj)
define|#
directive|define
name|GIMP_ITEM_LIST_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ITEM_LIST_VIEW, GimpItemListView))
end_define

begin_define
DECL|macro|GIMP_ITEM_LIST_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_ITEM_LIST_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ITEM_LIST_VIEW, GimpItemListViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_ITEM_LIST_VIEW (obj)
define|#
directive|define
name|GIMP_IS_ITEM_LIST_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ITEM_LIST_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_ITEM_LIST_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ITEM_LIST_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ITEM_LIST_VIEW))
end_define

begin_define
DECL|macro|GIMP_ITEM_LIST_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ITEM_LIST_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ITEM_LIST_VIEW, GimpItemListViewClass))
end_define

begin_typedef
DECL|typedef|GimpItemListViewClass
typedef|typedef
name|struct
name|_GimpItemListViewClass
name|GimpItemListViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpItemListView
struct|struct
name|_GimpItemListView
block|{
DECL|member|parent_instance
name|GimpContainerListView
name|parent_instance
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
DECL|member|item_type
name|GType
name|item_type
decl_stmt|;
DECL|member|signal_name
name|gchar
modifier|*
name|signal_name
decl_stmt|;
DECL|member|new_item_func
name|GimpNewItemFunc
name|new_item_func
decl_stmt|;
DECL|member|edit_item_func
name|GimpEditItemFunc
name|edit_item_func
decl_stmt|;
DECL|member|activate_item_func
name|GimpActivateItemFunc
name|activate_item_func
decl_stmt|;
DECL|member|menu_factory
name|GimpMenuFactory
modifier|*
name|menu_factory
decl_stmt|;
DECL|member|item_factory
name|GimpItemFactory
modifier|*
name|item_factory
decl_stmt|;
DECL|member|new_button
name|GtkWidget
modifier|*
name|new_button
decl_stmt|;
DECL|member|raise_button
name|GtkWidget
modifier|*
name|raise_button
decl_stmt|;
DECL|member|lower_button
name|GtkWidget
modifier|*
name|lower_button
decl_stmt|;
DECL|member|duplicate_button
name|GtkWidget
modifier|*
name|duplicate_button
decl_stmt|;
DECL|member|edit_button
name|GtkWidget
modifier|*
name|edit_button
decl_stmt|;
DECL|member|delete_button
name|GtkWidget
modifier|*
name|delete_button
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpItemListViewClass
struct|struct
name|_GimpItemListViewClass
block|{
DECL|member|parent_class
name|GimpContainerListViewClass
name|parent_class
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|set_image
name|void
function_decl|(
modifier|*
name|set_image
function_decl|)
parameter_list|(
name|GimpItemListView
modifier|*
name|view
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
comment|/*  virtual functions for manipulating the image's item list  */
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
DECL|member|reorder_item
name|GimpReorderItemFunc
name|reorder_item
decl_stmt|;
DECL|member|add_item
name|GimpAddItemFunc
name|add_item
decl_stmt|;
DECL|member|remove_item
name|GimpRemoveItemFunc
name|remove_item
decl_stmt|;
DECL|member|convert_item
name|GimpConvertItemFunc
name|convert_item
decl_stmt|;
comment|/*  various descriptive strings for tooltips and undo steps  */
DECL|member|new_desc
specifier|const
name|gchar
modifier|*
name|new_desc
decl_stmt|;
DECL|member|duplicate_desc
specifier|const
name|gchar
modifier|*
name|duplicate_desc
decl_stmt|;
DECL|member|edit_desc
specifier|const
name|gchar
modifier|*
name|edit_desc
decl_stmt|;
DECL|member|delete_desc
specifier|const
name|gchar
modifier|*
name|delete_desc
decl_stmt|;
DECL|member|raise_desc
specifier|const
name|gchar
modifier|*
name|raise_desc
decl_stmt|;
DECL|member|raise_to_top_desc
specifier|const
name|gchar
modifier|*
name|raise_to_top_desc
decl_stmt|;
DECL|member|lower_desc
specifier|const
name|gchar
modifier|*
name|lower_desc
decl_stmt|;
DECL|member|lower_to_bottom_desc
specifier|const
name|gchar
modifier|*
name|lower_to_bottom_desc
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_item_list_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_item_list_view_new
parameter_list|(
name|gint
name|preview_size
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GType
name|item_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|signal_name
parameter_list|,
name|GimpNewItemFunc
name|new_item_func
parameter_list|,
name|GimpEditItemFunc
name|edit_item_func
parameter_list|,
name|GimpActivateItemFunc
name|activate_item_func
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_facotry
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_identifier
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_list_view_set_image
parameter_list|(
name|GimpItemListView
modifier|*
name|view
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_ITEM_LIST_VIEW_H__  */
end_comment

end_unit

