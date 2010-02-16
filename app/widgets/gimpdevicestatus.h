begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdevicestatus.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DEVICE_STATUS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DEVICE_STATUS_H__
define|#
directive|define
name|__GIMP_DEVICE_STATUS_H__
end_define

begin_include
include|#
directive|include
file|"gimpeditor.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DEVICE_STATUS
define|#
directive|define
name|GIMP_TYPE_DEVICE_STATUS
value|(gimp_device_status_get_type ())
end_define

begin_define
DECL|macro|GIMP_DEVICE_STATUS (obj)
define|#
directive|define
name|GIMP_DEVICE_STATUS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DEVICE_STATUS, GimpDeviceStatus))
end_define

begin_define
DECL|macro|GIMP_DEVICE_STATUS_CLASS (klass)
define|#
directive|define
name|GIMP_DEVICE_STATUS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DEVICE_STATUS, GimpDeviceStatusClass))
end_define

begin_define
DECL|macro|GIMP_IS_DEVICE_STATUS (obj)
define|#
directive|define
name|GIMP_IS_DEVICE_STATUS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DEVICE_STATUS))
end_define

begin_define
DECL|macro|GIMP_IS_DEVICE_STATUS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DEVICE_STATUS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DEVICE_STATUS))
end_define

begin_define
DECL|macro|GIMP_DEVICE_STATUS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DEVICE_STATUS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DEVICE_STATUS, GimpDeviceStatusClass))
end_define

begin_typedef
DECL|typedef|GimpDeviceStatusEntry
typedef|typedef
name|struct
name|_GimpDeviceStatusEntry
name|GimpDeviceStatusEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDeviceStatusClass
typedef|typedef
name|struct
name|_GimpDeviceStatusClass
name|GimpDeviceStatusClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDeviceStatus
struct|struct
name|_GimpDeviceStatus
block|{
DECL|member|parent_instance
name|GimpEditor
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|current_device
name|GimpDeviceInfo
modifier|*
name|current_device
decl_stmt|;
DECL|member|devices
name|GList
modifier|*
name|devices
decl_stmt|;
DECL|member|vbox
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
DECL|member|save_button
name|GtkWidget
modifier|*
name|save_button
decl_stmt|;
DECL|member|edit_button
name|GtkWidget
modifier|*
name|edit_button
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDeviceStatusClass
struct|struct
name|_GimpDeviceStatusClass
block|{
DECL|member|parent_class
name|GimpEditorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_device_status_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_device_status_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_device_status_update
parameter_list|(
name|GimpDeviceStatus
modifier|*
name|status
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DEVICE_STATUS_H__  */
end_comment

end_unit

