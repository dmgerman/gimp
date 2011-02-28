begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GSEAL_ENABLE
end_undef

begin_include
include|#
directive|include
file|<glib/gstdio.h>
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|"libgimpbase/gimpwin32-io.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

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
file|"gimpdeviceinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpdevicemanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpdevices.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|GIMP_DEVICE_MANAGER_DATA_KEY
define|#
directive|define
name|GIMP_DEVICE_MANAGER_DATA_KEY
value|"gimp-device-manager"
end_define

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

begin_decl_stmt
DECL|variable|devicerc_deleted
specifier|static
name|gboolean
name|devicerc_deleted
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_devices_init (Gimp * gimp)
name|gimp_devices_init
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
name|gimp_device_manager_new
argument_list|(
name|gimp
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
name|g_object_unref
argument_list|)
expr_stmt|;
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
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
name|GList
modifier|*
name|list
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
name|user_context
operator|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|manager
argument_list|)
operator|->
name|list
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
name|GimpDeviceInfo
modifier|*
name|device_info
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_context_copy_properties
argument_list|(
name|user_context
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|device_info
argument_list|)
argument_list|,
name|GIMP_DEVICE_INFO_CONTEXT_MASK
argument_list|)
expr_stmt|;
block|}
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"devicerc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|manager
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
name|gimp_message_literal
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
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
name|gimp_context_copy_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|gimp_device_manager_get_current_device
argument_list|(
name|manager
argument_list|)
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
name|gimp_device_manager_get_current_device
argument_list|(
name|manager
argument_list|)
argument_list|)
argument_list|,
name|user_context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_devices_save (Gimp * gimp,gboolean always_save)
name|gimp_devices_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|always_save
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
if|if
condition|(
name|devicerc_deleted
operator|&&
operator|!
name|always_save
condition|)
return|return;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"devicerc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Writing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_serialize_to_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|manager
argument_list|)
argument_list|,
name|filename
argument_list|,
literal|"GIMP devicerc"
argument_list|,
literal|"end of devicerc"
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
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
name|devicerc_deleted
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_devices_clear (Gimp * gimp,GError ** error)
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
block|{
name|GimpDeviceManager
modifier|*
name|manager
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
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
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"devicerc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_unlink
argument_list|(
name|filename
argument_list|)
operator|!=
literal|0
operator|&&
name|errno
operator|!=
name|ENOENT
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|g_file_error_from_errno
argument_list|(
name|errno
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Deleting \"%s\" failed: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|devicerc_deleted
operator|=
name|TRUE
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
name|GimpContainer
modifier|*
DECL|function|gimp_devices_get_list (Gimp * gimp)
name|gimp_devices_get_list
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
name|GIMP_CONTAINER
argument_list|(
name|manager
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpDeviceInfo
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
name|gimp_device_manager_get_current_device
argument_list|(
name|manager
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_devices_add_widget (Gimp * gimp,GtkWidget * widget)
name|gimp_devices_add_widget
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
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
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_extension_events
argument_list|(
name|widget
argument_list|,
name|GDK_EXTENSION_EVENTS_ALL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"motion-notify-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_devices_check_callback
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_devices_check_callback (GtkWidget * widget,GdkEvent * event,Gimp * gimp)
name|gimp_devices_check_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|event
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
if|if
condition|(
operator|!
name|gimp
operator|->
name|busy
condition|)
name|gimp_devices_check_change
argument_list|(
name|gimp
argument_list|,
name|event
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
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
name|GimpDeviceInfo
modifier|*
name|device_info
decl_stmt|;
name|GtkWidget
modifier|*
name|source
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
comment|/* It is possible that the event was propagated from a widget that does not      want extension events and therefore always sends core pointer events.      This can cause a false switch to the core pointer device. */
name|source
operator|=
name|gtk_get_event_widget
argument_list|(
name|event
argument_list|)
expr_stmt|;
if|if
condition|(
name|source
operator|&&
name|gtk_widget_get_extension_events
argument_list|(
name|source
argument_list|)
operator|==
name|GDK_EXTENSION_EVENTS_NONE
condition|)
return|return
name|FALSE
return|;
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
name|gimp_device_manager_get_current_device
argument_list|(
name|manager
argument_list|)
operator|->
name|device
expr_stmt|;
break|break;
block|}
name|device_info
operator|=
name|gimp_device_info_get_by_device
argument_list|(
name|device
argument_list|)
expr_stmt|;
if|if
condition|(
name|device_info
operator|!=
name|gimp_device_manager_get_current_device
argument_list|(
name|manager
argument_list|)
condition|)
block|{
name|gimp_device_manager_set_current_device
argument_list|(
name|manager
argument_list|,
name|device_info
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

