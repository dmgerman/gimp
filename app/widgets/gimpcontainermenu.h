begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainermenu.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_MENU_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_MENU_H__
define|#
directive|define
name|__GIMP_CONTAINER_MENU_H__
end_define

begin_comment
comment|/*  keep everything in sync with GimpContainerView so we can easily make  *  and interface out of it with GTK+ 2.0  */
end_comment

begin_include
include|#
directive|include
file|<gtk/gtkmenu.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_CONTAINER_MENU
define|#
directive|define
name|GIMP_TYPE_CONTAINER_MENU
value|(gimp_container_menu_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTAINER_MENU (obj)
define|#
directive|define
name|GIMP_CONTAINER_MENU
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTAINER_MENU, GimpContainerMenu))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_MENU_CLASS (klass)
define|#
directive|define
name|GIMP_CONTAINER_MENU_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTAINER_MENU, GimpContainerMenuClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_MENU (obj)
define|#
directive|define
name|GIMP_IS_CONTAINER_MENU
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTAINER_MENU))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_MENU_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTAINER_MENU_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTAINER_MENU))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_MENU_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTAINER_MENU_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTAINER_MENU, GimpContainerMenuClass))
end_define

begin_typedef
DECL|typedef|GimpContainerMenuClass
typedef|typedef
name|struct
name|_GimpContainerMenuClass
name|GimpContainerMenuClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContainerMenu
struct|struct
name|_GimpContainerMenu
block|{
DECL|member|parent_instance
name|GtkMenu
name|parent_instance
decl_stmt|;
DECL|member|container
name|GimpContainer
modifier|*
name|container
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|hash_table
name|GHashTable
modifier|*
name|hash_table
decl_stmt|;
DECL|member|preview_size
name|gint
name|preview_size
decl_stmt|;
DECL|member|preview_border_width
name|gint
name|preview_border_width
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpContainerMenuClass
struct|struct
name|_GimpContainerMenuClass
block|{
DECL|member|parent_class
name|GtkMenuClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|select_item
name|void
function_decl|(
modifier|*
name|select_item
function_decl|)
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
DECL|member|activate_item
name|void
function_decl|(
modifier|*
name|activate_item
function_decl|)
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
DECL|member|context_item
name|void
function_decl|(
modifier|*
name|context_item
function_decl|)
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
comment|/*  virtual functions  */
DECL|member|set_container
name|void
function_decl|(
modifier|*
name|set_container
function_decl|)
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
DECL|member|insert_item
name|gpointer
function_decl|(
modifier|*
name|insert_item
function_decl|)
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
DECL|member|remove_item
name|void
function_decl|(
modifier|*
name|remove_item
function_decl|)
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
DECL|member|reorder_item
name|void
function_decl|(
modifier|*
name|reorder_item
function_decl|)
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gint
name|new_index
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
DECL|member|clear_items
name|void
function_decl|(
modifier|*
name|clear_items
function_decl|)
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|)
function_decl|;
DECL|member|set_preview_size
name|void
function_decl|(
modifier|*
name|set_preview_size
function_decl|)
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_container_menu_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_container_menu_set_container
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_menu_set_context
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_menu_set_preview_size
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|gint
name|preview_size
parameter_list|,
name|gint
name|preview_border_width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_menu_select_item
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_menu_activate_item
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_menu_context_item
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private  */
end_comment

begin_function_decl
name|void
name|gimp_container_menu_item_selected
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_menu_item_activated
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_menu_item_context
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CONTAINER_MENU_H__  */
end_comment

end_unit

