begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DEVICES_H__
end_ifndef

begin_define
DECL|macro|__DEVICES_H__
define|#
directive|define
name|__DEVICES_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6436080103
block|{
DECL|enumerator|DEVICE_MODE
name|DEVICE_MODE
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|DEVICE_AXES
name|DEVICE_AXES
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|DEVICE_KEYS
name|DEVICE_KEYS
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|DEVICE_TOOL
name|DEVICE_TOOL
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|DEVICE_FOREGROUND
name|DEVICE_FOREGROUND
init|=
literal|1
operator|<<
literal|4
block|,
DECL|enumerator|DEVICE_BACKGROUND
name|DEVICE_BACKGROUND
init|=
literal|1
operator|<<
literal|5
block|,
DECL|enumerator|DEVICE_BRUSH
name|DEVICE_BRUSH
init|=
literal|1
operator|<<
literal|6
block|,
DECL|enumerator|DEVICE_PATTERN
name|DEVICE_PATTERN
init|=
literal|1
operator|<<
literal|7
block|,
DECL|enumerator|DEVICE_GRADIENT
name|DEVICE_GRADIENT
init|=
literal|1
operator|<<
literal|8
DECL|typedef|DeviceValues
block|}
name|DeviceValues
typedef|;
end_typedef

begin_comment
comment|/*  Initialize the input devices  */
end_comment

begin_function_decl
name|void
name|devices_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Restores device settings from rc file  */
end_comment

begin_function_decl
name|void
name|devices_restore
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Create device info dialog  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|input_dialog_create
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Create the device status dialog  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|device_status_create
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Returns TRUE, and makes necessary global changes  *  if event is not for current_device  */
end_comment

begin_function_decl
name|gint
name|devices_check_change
parameter_list|(
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Loads stored device settings (tool, cursor, ...)  */
end_comment

begin_function_decl
name|void
name|select_device
parameter_list|(
name|GdkDevice
modifier|*
name|device
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add information about one tool from rc file */
end_comment

begin_function_decl
name|void
name|devices_rc_update
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|DeviceValues
name|values
parameter_list|,
name|GdkInputMode
name|mode
parameter_list|,
name|gint
name|num_axes
parameter_list|,
name|GdkAxisUse
modifier|*
name|axes
parameter_list|,
name|gint
name|num_keys
parameter_list|,
name|GdkDeviceKey
modifier|*
name|keys
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tool_name
parameter_list|,
name|GimpRGB
modifier|*
name|foreground
parameter_list|,
name|GimpRGB
modifier|*
name|background
parameter_list|,
specifier|const
name|gchar
modifier|*
name|brush_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pattern_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Free device status (only for session-managment)  */
end_comment

begin_function_decl
name|void
name|device_status_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Current device  */
end_comment

begin_decl_stmt
specifier|extern
name|GdkDevice
modifier|*
name|current_device
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DEVICES_H__ */
end_comment

end_unit

