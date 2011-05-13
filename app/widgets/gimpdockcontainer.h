begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockcontainer.h  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DOCK_CONTAINER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DOCK_CONTAINER_H__
define|#
directive|define
name|__GIMP_DOCK_CONTAINER_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_DOCK_CONTAINER
define|#
directive|define
name|GIMP_TYPE_DOCK_CONTAINER
value|(gimp_dock_container_interface_get_type ())
end_define

begin_define
DECL|macro|GIMP_DOCK_CONTAINER (obj)
define|#
directive|define
name|GIMP_DOCK_CONTAINER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DOCK_CONTAINER, GimpDockContainer))
end_define

begin_define
DECL|macro|GIMP_IS_DOCK_CONTAINER (obj)
define|#
directive|define
name|GIMP_IS_DOCK_CONTAINER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DOCK_CONTAINER))
end_define

begin_define
DECL|macro|GIMP_DOCK_CONTAINER_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_DOCK_CONTAINER_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_DOCK_CONTAINER, GimpDockContainerInterface))
end_define

begin_typedef
DECL|typedef|GimpDockContainerInterface
typedef|typedef
name|struct
name|_GimpDockContainerInterface
name|GimpDockContainerInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDockContainerInterface
struct|struct
name|_GimpDockContainerInterface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|get_docks
name|GList
modifier|*
function_decl|(
modifier|*
name|get_docks
function_decl|)
parameter_list|(
name|GimpDockContainer
modifier|*
name|container
parameter_list|)
function_decl|;
DECL|member|get_ui_manager
name|GimpUIManager
modifier|*
function_decl|(
modifier|*
name|get_ui_manager
function_decl|)
parameter_list|(
name|GimpDockContainer
modifier|*
name|container
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dock_container_interface_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GList
modifier|*
name|gimp_dock_container_get_docks
parameter_list|(
name|GimpDockContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUIManager
modifier|*
name|gimp_dock_container_get_ui_manager
parameter_list|(
name|GimpDockContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DOCK_CONTAINER_H__  */
end_comment

end_unit

