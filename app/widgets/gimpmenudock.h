begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmenudock.h  * Copyright (C) 2001-2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MENU_DOCK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MENU_DOCK_H__
define|#
directive|define
name|__GIMP_MENU_DOCK_H__
end_define

begin_include
include|#
directive|include
file|"gimpdock.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_MENU_DOCK
define|#
directive|define
name|GIMP_TYPE_MENU_DOCK
value|(gimp_menu_dock_get_type ())
end_define

begin_define
DECL|macro|GIMP_MENU_DOCK (obj)
define|#
directive|define
name|GIMP_MENU_DOCK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_MENU_DOCK, GimpMenuDock))
end_define

begin_define
DECL|macro|GIMP_MENU_DOCK_CLASS (klass)
define|#
directive|define
name|GIMP_MENU_DOCK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_MENU_DOCK, GimpMenuDockClass))
end_define

begin_define
DECL|macro|GIMP_IS_MENU_DOCK (obj)
define|#
directive|define
name|GIMP_IS_MENU_DOCK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_MENU_DOCK))
end_define

begin_define
DECL|macro|GIMP_IS_MENU_DOCK_CLASS (klass)
define|#
directive|define
name|GIMP_IS_MENU_DOCK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_MENU_DOCK))
end_define

begin_define
DECL|macro|GIMP_MENU_DOCK_GET_CLASS (obj)
define|#
directive|define
name|GIMP_MENU_DOCK_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_MENU_DOCK, GimpMenuDockClass))
end_define

begin_typedef
DECL|typedef|GimpMenuDockPrivate
typedef|typedef
name|struct
name|_GimpMenuDockPrivate
name|GimpMenuDockPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMenuDockClass
typedef|typedef
name|struct
name|_GimpMenuDockClass
name|GimpMenuDockClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpMenuDock
struct|struct
name|_GimpMenuDock
block|{
DECL|member|parent_instance
name|GimpDock
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpMenuDockPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpMenuDockClass
struct|struct
name|_GimpMenuDockClass
block|{
DECL|member|parent_class
name|GimpDockClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_menu_dock_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_menu_dock_new
parameter_list|(
name|GimpDialogFactory
modifier|*
name|dialog_factory
parameter_list|,
name|GimpContainer
modifier|*
name|image_container
parameter_list|,
name|GimpContainer
modifier|*
name|display_container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_menu_dock_get_auto_follow_active
parameter_list|(
name|GimpMenuDock
modifier|*
name|menu_dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_menu_dock_set_auto_follow_active
parameter_list|(
name|GimpMenuDock
modifier|*
name|menu_dock
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_menu_dock_get_show_image_menu
parameter_list|(
name|GimpMenuDock
modifier|*
name|menu_dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_menu_dock_set_show_image_menu
parameter_list|(
name|GimpMenuDock
modifier|*
name|menu_dock
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MENU_DOCK_H__ */
end_comment

end_unit

