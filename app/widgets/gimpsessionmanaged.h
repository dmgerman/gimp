begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessionmanaged.h  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SESSION_MANAGED_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SESSION_MANAGED_H__
define|#
directive|define
name|__GIMP_SESSION_MANAGED_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_SESSION_MANAGED
define|#
directive|define
name|GIMP_TYPE_SESSION_MANAGED
value|(gimp_session_managed_interface_get_type ())
end_define

begin_define
DECL|macro|GIMP_SESSION_MANAGED (obj)
define|#
directive|define
name|GIMP_SESSION_MANAGED
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SESSION_MANAGED, GimpSessionManaged))
end_define

begin_define
DECL|macro|GIMP_IS_SESSION_MANAGED (obj)
define|#
directive|define
name|GIMP_IS_SESSION_MANAGED
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SESSION_MANAGED))
end_define

begin_define
DECL|macro|GIMP_SESSION_MANAGED_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_SESSION_MANAGED_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_SESSION_MANAGED, GimpSessionManagedInterface))
end_define

begin_typedef
DECL|typedef|GimpSessionManagedInterface
typedef|typedef
name|struct
name|_GimpSessionManagedInterface
name|GimpSessionManagedInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSessionManagedInterface
struct|struct
name|_GimpSessionManagedInterface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|get_aux_info
name|GList
modifier|*
function_decl|(
modifier|*
name|get_aux_info
function_decl|)
parameter_list|(
name|GimpSessionManaged
modifier|*
name|session_managed
parameter_list|)
function_decl|;
DECL|member|set_aux_info
name|void
function_decl|(
modifier|*
name|set_aux_info
function_decl|)
parameter_list|(
name|GimpSessionManaged
modifier|*
name|session_managed
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_session_managed_interface_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GList
modifier|*
name|gimp_session_managed_get_aux_info
parameter_list|(
name|GimpSessionManaged
modifier|*
name|session_managed
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_managed_set_aux_info
parameter_list|(
name|GimpSessionManaged
modifier|*
name|session_managed
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_SESSION_MANAGED_H__  */
end_comment

end_unit

