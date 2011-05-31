begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdisplayshell-grab.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdeviceinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdevices.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdevicemanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-grab.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_display_shell_pointer_grab (GimpDisplayShell * shell,const GdkEvent * event,GdkEventMask event_mask)
name|gimp_display_shell_pointer_grab
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GdkEventMask
name|event_mask
parameter_list|)
block|{
name|GdkGrabStatus
name|status
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
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
name|g_return_val_if_fail
argument_list|(
name|shell
operator|->
name|pointer_grabbed
operator|==
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|status
operator|=
name|gdk_pointer_grab
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|event_mask
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gdk_event_get_time
argument_list|(
name|event
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GDK_GRAB_SUCCESS
condition|)
block|{
name|shell
operator|->
name|pointer_grabbed
operator|=
name|TRUE
expr_stmt|;
return|return
name|TRUE
return|;
block|}
elseif|else
if|if
condition|(
name|status
operator|==
name|GDK_GRAB_ALREADY_GRABBED
condition|)
block|{
name|GimpDeviceManager
modifier|*
name|manager
decl_stmt|;
name|GdkDisplay
modifier|*
name|gdk_display
decl_stmt|;
name|manager
operator|=
name|gimp_devices_get_manager
argument_list|(
name|shell
operator|->
name|display
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|gdk_display
operator|=
name|gtk_widget_get_display
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  EEK: trying to grab an extended device always returns        *  ALREADY_GRABBED, so simply assume the grab succeeded anyway        */
if|if
condition|(
name|gimp_device_manager_get_current_device
argument_list|(
name|manager
argument_list|)
operator|->
name|device
operator|!=
name|gdk_display_get_core_pointer
argument_list|(
name|gdk_display
argument_list|)
condition|)
block|{
name|shell
operator|->
name|pointer_grabbed
operator|=
name|TRUE
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
name|g_printerr
argument_list|(
literal|"%s: gdk_pointer_grab failed with status %d\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|status
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_pointer_ungrab (GimpDisplayShell * shell,const GdkEvent * event)
name|gimp_display_shell_pointer_ungrab
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GdkEvent
modifier|*
name|event
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|event
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|shell
operator|->
name|pointer_grabbed
operator|==
name|TRUE
argument_list|)
expr_stmt|;
name|gdk_display_pointer_ungrab
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
name|gdk_event_get_time
argument_list|(
name|event
argument_list|)
argument_list|)
expr_stmt|;
name|shell
operator|->
name|pointer_grabbed
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_keyboard_grab (GimpDisplayShell * shell,const GdkEvent * event)
name|gimp_display_shell_keyboard_grab
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GdkEvent
modifier|*
name|event
parameter_list|)
block|{
name|GdkGrabStatus
name|status
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
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
name|g_return_val_if_fail
argument_list|(
name|shell
operator|->
name|keyboard_grabbed
operator|==
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|status
operator|=
name|gdk_keyboard_grab
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|gdk_event_get_time
argument_list|(
name|event
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GDK_GRAB_SUCCESS
condition|)
block|{
name|shell
operator|->
name|keyboard_grabbed
operator|=
name|TRUE
expr_stmt|;
return|return
name|TRUE
return|;
block|}
name|g_printerr
argument_list|(
literal|"%s: gdk_keyboard_grab failed with status %d\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|status
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_keyboard_ungrab (GimpDisplayShell * shell,const GdkEvent * event)
name|gimp_display_shell_keyboard_ungrab
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GdkEvent
modifier|*
name|event
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|event
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|shell
operator|->
name|keyboard_grabbed
operator|==
name|TRUE
argument_list|)
expr_stmt|;
name|gdk_display_keyboard_ungrab
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
name|gdk_event_get_time
argument_list|(
name|event
argument_list|)
argument_list|)
expr_stmt|;
name|shell
operator|->
name|keyboard_grabbed
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

