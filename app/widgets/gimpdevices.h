begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DEVICES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DEVICES_H__
define|#
directive|define
name|__GIMP_DEVICES_H__
end_define

begin_typedef
DECL|typedef|GimpDeviceChangeNotify
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDeviceChangeNotify
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_devices_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpDeviceChangeNotify
name|callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_devices_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_devices_restore
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_devices_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|always_save
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_devices_clear
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_devices_get_list
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
name|gimp_devices_get_current
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_devices_check_change
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DEVICES_H__ */
end_comment

end_unit

