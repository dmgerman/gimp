begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdevicemanager.h  * Copyright (C) 2011 Michael Natterer  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DEVICE_MANAGER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DEVICE_MANAGER_H__
define|#
directive|define
name|__GIMP_DEVICE_MANAGER_H__
end_define

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_DEVICE_MANAGER
define|#
directive|define
name|GIMP_TYPE_DEVICE_MANAGER
value|(gimp_device_manager_get_type ())
end_define

begin_define
DECL|macro|GIMP_DEVICE_MANAGER (obj)
define|#
directive|define
name|GIMP_DEVICE_MANAGER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DEVICE_MANAGER, GimpDeviceManager))
end_define

begin_define
DECL|macro|GIMP_DEVICE_MANAGER_CLASS (klass)
define|#
directive|define
name|GIMP_DEVICE_MANAGER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DEVICE_MANAGER, GimpDeviceManagerClass))
end_define

begin_define
DECL|macro|GIMP_IS_DEVICE_MANAGER (obj)
define|#
directive|define
name|GIMP_IS_DEVICE_MANAGER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DEVICE_MANAGER))
end_define

begin_define
DECL|macro|GIMP_IS_DEVICE_MANAGER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DEVICE_MANAGER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DEVICE_MANAGER))
end_define

begin_define
DECL|macro|GIMP_DEVICE_MANAGER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DEVICE_MANAGER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DEVICE_MANAGER, GimpDeviceManagerClass))
end_define

begin_typedef
DECL|typedef|GimpDeviceManagerClass
typedef|typedef
name|struct
name|_GimpDeviceManagerClass
name|GimpDeviceManagerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDeviceManager
struct|struct
name|_GimpDeviceManager
block|{
DECL|member|parent_instance
name|GimpList
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDeviceManagerClass
struct|struct
name|_GimpDeviceManagerClass
block|{
DECL|member|parent_class
name|GimpListClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_device_manager_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpDeviceManager
modifier|*
name|gimp_device_manager_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDeviceInfo
modifier|*
name|gimp_device_manager_get_current_device
parameter_list|(
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_device_manager_set_current_device
parameter_list|(
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|,
name|GimpDeviceInfo
modifier|*
name|info
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
comment|/* __GIMP_DEVICE_MANAGER_H__ */
end_comment

end_unit

