begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpdeviceinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpdevices.h"
end_include

begin_define
DECL|macro|GIMP_DEVICE_MANAGER_DATA_KEY
define|#
directive|define
name|GIMP_DEVICE_MANAGER_DATA_KEY
value|"gimp-device-manager"
end_define

begin_typedef
DECL|typedef|GimpDeviceManager
typedef|typedef
name|struct
name|_GimpDeviceManager
name|GimpDeviceManager
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDeviceManager
struct|struct
name|_GimpDeviceManager
block|{
DECL|member|device_info_list
name|GimpContainer
modifier|*
name|device_info_list
decl_stmt|;
DECL|member|current_device
name|GdkDevice
modifier|*
name|current_device
decl_stmt|;
DECL|member|change_notify
name|GimpDeviceChangeNotify
name|change_notify
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GimpDeviceManager
modifier|*
name|gimp_device_manager_get
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_devices_init (Gimp * gimp,GimpDeviceChangeNotify change_notify)
name|gimp_devices_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpDeviceChangeNotify
name|change_notify
parameter_list|)
block|{
name|GimpDeviceManager
modifier|*
name|manager
decl_stmt|;
name|GdkDevice
modifier|*
name|device
decl_stmt|;
name|GimpDeviceInfo
modifier|*
name|device_info
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_device_manager_get
argument_list|(
name|gimp
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|manager
operator|=
name|g_new0
argument_list|(
name|GimpDeviceManager
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|GIMP_DEVICE_MANAGER_DATA_KEY
argument_list|,
name|manager
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|manager
operator|->
name|device_info_list
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_DEVICE_INFO
argument_list|,
name|GIMP_CONTAINER_POLICY_STRONG
argument_list|)
expr_stmt|;
name|manager
operator|->
name|current_device
operator|=
name|gdk_device_get_core_pointer
argument_list|()
expr_stmt|;
name|manager
operator|->
name|change_notify
operator|=
name|change_notify
expr_stmt|;
comment|/*  create device info structures for present devices */
for|for
control|(
name|list
operator|=
name|gdk_devices_list
argument_list|()
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|device
operator|=
operator|(
name|GdkDevice
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|device_info
operator|=
name|gimp_device_info_new
argument_list|(
name|gimp
argument_list|,
name|device
operator|->
name|name
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|manager
operator|->
name|device_info_list
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|device_info
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|device_info
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_device_info_set_from_device
argument_list|(
name|device_info
argument_list|,
name|device
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_devices_exit (Gimp * gimp)
name|gimp_devices_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpDeviceManager
modifier|*
name|manager
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|manager
operator|=
name|gimp_device_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|manager
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
operator|->
name|device_info_list
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|GIMP_DEVICE_MANAGER_DATA_KEY
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_devices_restore (Gimp * gimp)
name|gimp_devices_restore
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpDeviceManager
modifier|*
name|manager
decl_stmt|;
name|GimpDeviceInfo
modifier|*
name|device_info
decl_stmt|;
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|manager
operator|=
name|gimp_device_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|manager
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"devicerc"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
operator|->
name|device_info_list
argument_list|)
argument_list|,
name|filename
argument_list|,
name|gimp
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
name|error
operator|->
name|code
operator|!=
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
condition|)
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
comment|/* don't bail out here */
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gimp_list_reverse
argument_list|(
name|GIMP_LIST
argument_list|(
name|manager
operator|->
name|device_info_list
argument_list|)
argument_list|)
expr_stmt|;
name|device_info
operator|=
name|gimp_device_info_get_by_device
argument_list|(
name|manager
operator|->
name|current_device
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DEVICE_INFO
argument_list|(
name|device_info
argument_list|)
argument_list|)
expr_stmt|;
name|user_context
operator|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_context_copy_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|device_info
argument_list|)
argument_list|,
name|user_context
argument_list|,
name|GIMP_DEVICE_INFO_CONTEXT_MASK
argument_list|)
expr_stmt|;
name|gimp_context_set_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|device_info
argument_list|)
argument_list|,
name|user_context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_devices_save (Gimp * gimp)
name|gimp_devices_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpDeviceManager
modifier|*
name|manager
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|manager
operator|=
name|gimp_device_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|manager
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"devicerc"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_serialize
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
operator|->
name|device_info_list
argument_list|)
argument_list|,
name|filename
argument_list|,
literal|"# GIMP devicerc\n"
argument_list|,
literal|"# end devicerc"
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GdkDevice
modifier|*
DECL|function|gimp_devices_get_current (Gimp * gimp)
name|gimp_devices_get_current
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpDeviceManager
modifier|*
name|manager
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|manager
operator|=
name|gimp_device_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|manager
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|manager
operator|->
name|current_device
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_devices_select_device (Gimp * gimp,GdkDevice * new_device)
name|gimp_devices_select_device
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GdkDevice
modifier|*
name|new_device
parameter_list|)
block|{
name|GimpDeviceManager
modifier|*
name|manager
decl_stmt|;
name|GimpDeviceInfo
modifier|*
name|current_device_info
decl_stmt|;
name|GimpDeviceInfo
modifier|*
name|new_device_info
decl_stmt|;
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GDK_IS_DEVICE
argument_list|(
name|new_device
argument_list|)
argument_list|)
expr_stmt|;
name|manager
operator|=
name|gimp_device_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|manager
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|current_device_info
operator|=
name|gimp_device_info_get_by_device
argument_list|(
name|manager
operator|->
name|current_device
argument_list|)
expr_stmt|;
name|new_device_info
operator|=
name|gimp_device_info_get_by_device
argument_list|(
name|new_device
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DEVICE_INFO
argument_list|(
name|current_device_info
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DEVICE_INFO
argument_list|(
name|new_device_info
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_context_unset_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|current_device_info
argument_list|)
argument_list|)
expr_stmt|;
name|manager
operator|->
name|current_device
operator|=
name|new_device
expr_stmt|;
name|user_context
operator|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_context_copy_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|new_device_info
argument_list|)
argument_list|,
name|user_context
argument_list|,
name|GIMP_DEVICE_INFO_CONTEXT_MASK
argument_list|)
expr_stmt|;
name|gimp_context_set_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|new_device_info
argument_list|)
argument_list|,
name|user_context
argument_list|)
expr_stmt|;
if|if
condition|(
name|manager
operator|->
name|change_notify
condition|)
name|manager
operator|->
name|change_notify
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_devices_check_change (Gimp * gimp,GdkEvent * event)
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
block|{
name|GimpDeviceManager
modifier|*
name|manager
decl_stmt|;
name|GdkDevice
modifier|*
name|device
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|event
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|manager
operator|=
name|gimp_device_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|manager
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|event
operator|->
name|type
condition|)
block|{
case|case
name|GDK_MOTION_NOTIFY
case|:
name|device
operator|=
operator|(
operator|(
name|GdkEventMotion
operator|*
operator|)
name|event
operator|)
operator|->
name|device
expr_stmt|;
break|break;
case|case
name|GDK_BUTTON_PRESS
case|:
case|case
name|GDK_2BUTTON_PRESS
case|:
case|case
name|GDK_3BUTTON_PRESS
case|:
case|case
name|GDK_BUTTON_RELEASE
case|:
name|device
operator|=
operator|(
operator|(
name|GdkEventButton
operator|*
operator|)
name|event
operator|)
operator|->
name|device
expr_stmt|;
break|break;
case|case
name|GDK_PROXIMITY_IN
case|:
case|case
name|GDK_PROXIMITY_OUT
case|:
name|device
operator|=
operator|(
operator|(
name|GdkEventProximity
operator|*
operator|)
name|event
operator|)
operator|->
name|device
expr_stmt|;
break|break;
case|case
name|GDK_SCROLL
case|:
name|device
operator|=
operator|(
operator|(
name|GdkEventScroll
operator|*
operator|)
name|event
operator|)
operator|->
name|device
expr_stmt|;
break|break;
default|default:
name|device
operator|=
name|manager
operator|->
name|current_device
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|device
operator|!=
name|manager
operator|->
name|current_device
condition|)
block|{
name|gimp_devices_select_device
argument_list|(
name|gimp
argument_list|,
name|device
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpDeviceManager
modifier|*
DECL|function|gimp_device_manager_get (Gimp * gimp)
name|gimp_device_manager_get
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
return|return
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|GIMP_DEVICE_MANAGER_DATA_KEY
argument_list|)
return|;
block|}
end_function

end_unit

