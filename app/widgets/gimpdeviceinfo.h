begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DEVICE_INFO_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DEVICE_INFO_H__
define|#
directive|define
name|__GIMP_DEVICE_INFO_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_DEVICE_INFO_CONTEXT_MASK
define|#
directive|define
name|GIMP_DEVICE_INFO_CONTEXT_MASK
value|(GIMP_CONTEXT_TOOL_MASK       | \                                        GIMP_CONTEXT_PAINT_INFO_MASK | \                                        GIMP_CONTEXT_FOREGROUND_MASK | \                                        GIMP_CONTEXT_BACKGROUND_MASK | \                                        GIMP_CONTEXT_BRUSH_MASK      | \                                        GIMP_CONTEXT_DYNAMICS_MASK   | \                                        GIMP_CONTEXT_PATTERN_MASK    | \                                        GIMP_CONTEXT_GRADIENT_MASK)
end_define

begin_define
DECL|macro|GIMP_TYPE_DEVICE_INFO
define|#
directive|define
name|GIMP_TYPE_DEVICE_INFO
value|(gimp_device_info_get_type ())
end_define

begin_define
DECL|macro|GIMP_DEVICE_INFO (obj)
define|#
directive|define
name|GIMP_DEVICE_INFO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DEVICE_INFO, GimpDeviceInfo))
end_define

begin_define
DECL|macro|GIMP_DEVICE_INFO_CLASS (klass)
define|#
directive|define
name|GIMP_DEVICE_INFO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DEVICE_INFO, GimpDeviceInfoClass))
end_define

begin_define
DECL|macro|GIMP_IS_DEVICE_INFO (obj)
define|#
directive|define
name|GIMP_IS_DEVICE_INFO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DEVICE_INFO))
end_define

begin_define
DECL|macro|GIMP_IS_DEVICE_INFO_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DEVICE_INFO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DEVICE_INFO))
end_define

begin_define
DECL|macro|GIMP_DEVICE_INFO_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DEVICE_INFO_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DEVICE_INFO, GimpDeviceInfoClass))
end_define

begin_typedef
DECL|typedef|GimpDeviceInfoClass
typedef|typedef
name|struct
name|_GimpDeviceInfoClass
name|GimpDeviceInfoClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDeviceInfo
struct|struct
name|_GimpDeviceInfo
block|{
DECL|member|parent_instance
name|GimpContext
name|parent_instance
decl_stmt|;
DECL|member|device
name|GdkDevice
modifier|*
name|device
decl_stmt|;
DECL|member|display
name|GdkDisplay
modifier|*
name|display
decl_stmt|;
comment|/*  either "device" or the options below are set  */
DECL|member|mode
name|GdkInputMode
name|mode
decl_stmt|;
DECL|member|num_axes
name|gint
name|num_axes
decl_stmt|;
DECL|member|axes
name|GdkAxisUse
modifier|*
name|axes
decl_stmt|;
DECL|member|num_keys
name|gint
name|num_keys
decl_stmt|;
DECL|member|keys
name|GdkDeviceKey
modifier|*
name|keys
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDeviceInfoClass
struct|struct
name|_GimpDeviceInfoClass
block|{
DECL|member|parent_class
name|GimpContextClass
name|parent_class
decl_stmt|;
DECL|member|changed
name|void
function_decl|(
modifier|*
name|changed
function_decl|)
parameter_list|(
name|GimpDeviceInfo
modifier|*
name|device_info
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_device_info_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpDeviceInfo
modifier|*
name|gimp_device_info_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDeviceInfo
modifier|*
name|gimp_device_info_set_from_device
parameter_list|(
name|GimpDeviceInfo
modifier|*
name|device_info
parameter_list|,
name|GdkDevice
modifier|*
name|device
parameter_list|,
name|GdkDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_device_info_changed
parameter_list|(
name|GimpDeviceInfo
modifier|*
name|device_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDeviceInfo
modifier|*
name|gimp_device_info_get_by_device
parameter_list|(
name|GdkDevice
modifier|*
name|device
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_device_info_changed_by_device
parameter_list|(
name|GdkDevice
modifier|*
name|device
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
comment|/* __GIMP_DEVICE_INFO_H__ */
end_comment

end_unit

