begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainermenuimpl.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_MENU_IMPL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_MENU_IMPL_H__
define|#
directive|define
name|__GIMP_CONTAINER_MENU_IMPL_H__
end_define

begin_include
include|#
directive|include
file|"gimpcontainermenu.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CONTAINER_MENU_IMPL
define|#
directive|define
name|GIMP_TYPE_CONTAINER_MENU_IMPL
value|(gimp_container_menu_impl_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTAINER_MENU_IMPL (obj)
define|#
directive|define
name|GIMP_CONTAINER_MENU_IMPL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTAINER_MENU_IMPL, GimpContainerMenuImpl))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_MENU_IMPL_CLASS (klass)
define|#
directive|define
name|GIMP_CONTAINER_MENU_IMPL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTAINER_MENU_IMPL, GimpContainerMenuImplClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_MENU_IMPL (obj)
define|#
directive|define
name|GIMP_IS_CONTAINER_MENU_IMPL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTAINER_MENU_IMPL))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_MENU_IMPL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTAINER_MENU_IMPL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTAINER_MENU_IMPL))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_MENU_IMPL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTAINER_MENU_IMPL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTAINER_MENU_IMPL, GimpContainerMenuImplClass))
end_define

begin_typedef
DECL|typedef|GimpContainerMenuImplClass
typedef|typedef
name|struct
name|_GimpContainerMenuImplClass
name|GimpContainerMenuImplClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContainerMenuImpl
struct|struct
name|_GimpContainerMenuImpl
block|{
DECL|member|parent_instance
name|GimpContainerMenu
name|parent_instance
decl_stmt|;
DECL|member|empty_item
name|GtkWidget
modifier|*
name|empty_item
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpContainerMenuImplClass
struct|struct
name|_GimpContainerMenuImplClass
block|{
DECL|member|parent_class
name|GimpContainerMenuClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_container_menu_impl_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_container_menu_new
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
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CONTAINER_MENU_IMPL_H__  */
end_comment

end_unit

