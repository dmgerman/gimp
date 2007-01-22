begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpDBusService  * Copyright (C) 2007 Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DBUS_SERVICE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DBUS_SERVICE_H__
define|#
directive|define
name|__GIMP_DBUS_SERVICE_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_DBUS_SERVICE_NAME
define|#
directive|define
name|GIMP_DBUS_SERVICE_NAME
value|"org.gimp.GIMP"
end_define

begin_define
DECL|macro|GIMP_DBUS_SERVICE_PATH
define|#
directive|define
name|GIMP_DBUS_SERVICE_PATH
value|"/org/gimp/GIMP"
end_define

begin_define
DECL|macro|GIMP_DBUS_SERVICE_INTERFACE
define|#
directive|define
name|GIMP_DBUS_SERVICE_INTERFACE
value|"org.gimp.GIMP"
end_define

begin_define
DECL|macro|GIMP_TYPE_DBUS_SERVICE
define|#
directive|define
name|GIMP_TYPE_DBUS_SERVICE
value|(gimp_dbus_service_get_type ())
end_define

begin_define
DECL|macro|GIMP_DBUS_SERVICE (obj)
define|#
directive|define
name|GIMP_DBUS_SERVICE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DBUS_SERVICE, GimpDBusService))
end_define

begin_define
DECL|macro|GIMP_DBUS_SERVICE_CLASS (klass)
define|#
directive|define
name|GIMP_DBUS_SERVICE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DBUS_SERVICE, GimpDBusServiceClass))
end_define

begin_define
DECL|macro|GIMP_IS_DBUS_SERVICE (obj)
define|#
directive|define
name|GIMP_IS_DBUS_SERVICE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DBUS_SERVICE))
end_define

begin_define
DECL|macro|GIMP_IS_DBUS_SERVICE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DBUS_SERVICE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DBUS_SERVICE))
end_define

begin_define
DECL|macro|GIMP_DBUS_SERVICE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DBUS_SERVICE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DBUS_SERVICE, GimpDBusServiceClass))
end_define

begin_typedef
DECL|typedef|GimpDBusService
typedef|typedef
name|struct
name|_GimpDBusService
name|GimpDBusService
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDBusServiceClass
typedef|typedef
name|struct
name|_GimpDBusServiceClass
name|GimpDBusServiceClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDBusService
struct|struct
name|_GimpDBusService
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDBusServiceClass
struct|struct
name|_GimpDBusServiceClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dbus_service_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GObject
modifier|*
name|gimp_dbus_service_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dbus_service_open
parameter_list|(
name|GimpDBusService
modifier|*
name|service
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|uris
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dbus_service_activate
parameter_list|(
name|GimpDBusService
modifier|*
name|service
parameter_list|,
name|GError
modifier|*
modifier|*
name|dbus_error
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DBUS_SERVICE_H__ */
end_comment

end_unit

