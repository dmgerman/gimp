begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplistitem.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LIST_ITEM_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LIST_ITEM_H__
define|#
directive|define
name|__GIMP_LIST_ITEM_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtklistitem.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_LIST_ITEM
define|#
directive|define
name|GIMP_TYPE_LIST_ITEM
value|(gimp_list_item_get_type ())
end_define

begin_define
DECL|macro|GIMP_LIST_ITEM (obj)
define|#
directive|define
name|GIMP_LIST_ITEM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LIST_ITEM, GimpListItem))
end_define

begin_define
DECL|macro|GIMP_LIST_ITEM_CLASS (klass)
define|#
directive|define
name|GIMP_LIST_ITEM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LIST_ITEM, GimpListItemClass))
end_define

begin_define
DECL|macro|GIMP_IS_LIST_ITEM (obj)
define|#
directive|define
name|GIMP_IS_LIST_ITEM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LIST_ITEM))
end_define

begin_define
DECL|macro|GIMP_IS_LIST_ITEM_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LIST_ITEM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LIST_ITEM))
end_define

begin_define
DECL|macro|GIMP_LIST_ITEM_GET_CLASS (obj)
define|#
directive|define
name|GIMP_LIST_ITEM_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_LIST_ITEM, GimpListItemClass))
end_define

begin_typedef
DECL|typedef|GimpListItemClass
typedef|typedef
name|struct
name|_GimpListItemClass
name|GimpListItemClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpListItem
struct|struct
name|_GimpListItem
block|{
DECL|member|parent_instance
name|GtkListItem
name|parent_instance
decl_stmt|;
DECL|member|hbox
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|name_label
name|GtkWidget
modifier|*
name|name_label
decl_stmt|;
comment|/*< protected>*/
DECL|member|preview_size
name|gint
name|preview_size
decl_stmt|;
comment|/*< private>*/
DECL|member|reorderable
name|gboolean
name|reorderable
decl_stmt|;
DECL|member|container
name|GimpContainer
modifier|*
name|container
decl_stmt|;
DECL|member|drop_type
name|GimpDropType
name|drop_type
decl_stmt|;
DECL|member|get_name_func
name|GimpItemGetNameFunc
name|get_name_func
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpListItemClass
struct|struct
name|_GimpListItemClass
block|{
DECL|member|parent_class
name|GtkListItemClass
name|parent_class
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|set_viewable
name|void
function_decl|(
modifier|*
name|set_viewable
function_decl|)
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
DECL|member|set_preview_size
name|void
function_decl|(
modifier|*
name|set_preview_size
function_decl|)
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_list_item_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_list_item_new
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|preview_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_list_item_set_viewable
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_list_item_set_preview_size
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|,
name|gint
name|preview_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_list_item_set_reorderable
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|,
name|gboolean
name|reorderable
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_list_item_set_name_func
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|,
name|GimpItemGetNameFunc
name|get_name_func
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  protected  */
end_comment

begin_function_decl
name|gboolean
name|gimp_list_item_check_drag
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
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
name|GimpViewable
modifier|*
modifier|*
name|src_viewable
parameter_list|,
name|gint
modifier|*
name|dest_index
parameter_list|,
name|GdkDragAction
modifier|*
name|drag_action
parameter_list|,
name|GimpDropType
modifier|*
name|drop_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_list_item_button_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_list_item_button_state_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStateType
name|previous_state
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LIST_ITEM_H__ */
end_comment

end_unit

