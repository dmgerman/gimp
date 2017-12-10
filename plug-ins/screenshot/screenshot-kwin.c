begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Screenshot plug-in  * Copyright 1998-2007 Sven Neumann<sven@gimp.org>  * Copyright 2003      Henrik Brix Andersen<brix@gimp.org>  * Copyright 2016      Michael Natterer<mitch@gimp.org>  * Copyright 2017      Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_comment
comment|/* g_unlink() */
end_comment

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"screenshot.h"
end_include

begin_include
include|#
directive|include
file|"screenshot-kwin.h"
end_include

begin_decl_stmt
DECL|variable|proxy
specifier|static
name|GDBusProxy
modifier|*
name|proxy
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|gboolean
DECL|function|screenshot_kwin_available (void)
name|screenshot_kwin_available
parameter_list|(
name|void
parameter_list|)
block|{
name|proxy
operator|=
name|g_dbus_proxy_new_for_bus_sync
argument_list|(
name|G_BUS_TYPE_SESSION
argument_list|,
name|G_DBUS_PROXY_FLAGS_DO_NOT_AUTO_START
argument_list|,
name|NULL
argument_list|,
literal|"org.kde.KWin"
argument_list|,
literal|"/Screenshot"
argument_list|,
literal|"org.kde.kwin.Screenshot"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|proxy
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_dbus_proxy_call_sync
argument_list|(
name|proxy
argument_list|,
literal|"org.freedesktop.DBus.Peer.Ping"
argument_list|,
name|NULL
argument_list|,
name|G_DBUS_CALL_FLAGS_NONE
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|error
condition|)
return|return
name|TRUE
return|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|proxy
argument_list|)
expr_stmt|;
name|proxy
operator|=
name|NULL
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|ScreenshotCapabilities
DECL|function|screenshot_kwin_get_capabilities (void)
name|screenshot_kwin_get_capabilities
parameter_list|(
name|void
parameter_list|)
block|{
return|return
operator|(
name|SCREENSHOT_CAN_SHOOT_DECORATIONS
operator||
name|SCREENSHOT_CAN_SHOOT_POINTER
operator||
name|SCREENSHOT_CAN_PICK_WINDOW
operator|)
return|;
comment|/* TODO: SCREENSHOT_CAN_SHOOT_REGION.    * The KDE API has "screenshotArea" method but no method to get    * coordinates could be found. See below.    */
block|}
end_function

begin_function
name|GimpPDBStatusType
DECL|function|screenshot_kwin_shoot (ScreenshotValues * shootvals,GdkScreen * screen,gint32 * image_ID,GError ** error)
name|screenshot_kwin_shoot
parameter_list|(
name|ScreenshotValues
modifier|*
name|shootvals
parameter_list|,
name|GdkScreen
modifier|*
name|screen
parameter_list|,
name|gint32
modifier|*
name|image_ID
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|method
init|=
name|NULL
decl_stmt|;
name|GVariant
modifier|*
name|args
init|=
name|NULL
decl_stmt|;
name|GVariant
modifier|*
name|retval
decl_stmt|;
name|gint
name|monitor
init|=
name|shootvals
operator|->
name|monitor
decl_stmt|;
name|gint32
name|mask
decl_stmt|;
switch|switch
condition|(
name|shootvals
operator|->
name|shoot_type
condition|)
block|{
case|case
name|SHOOT_ROOT
case|:
if|if
condition|(
name|shootvals
operator|->
name|screenshot_delay
operator|>
literal|0
condition|)
name|screenshot_delay
argument_list|(
name|shootvals
operator|->
name|screenshot_delay
argument_list|)
expr_stmt|;
else|else
block|{
comment|/* As an exception, I force a delay of at least 0.5 seconds            * for KWin. Because of windows effect slowly fading out, the            * screenshot plug-in GUI was constantly visible (with            * transparency as it is fading out) in 0s-delay screenshots.            */
name|g_usleep
argument_list|(
literal|500000
argument_list|)
expr_stmt|;
block|}
name|method
operator|=
literal|"screenshotFullscreen"
expr_stmt|;
name|args
operator|=
name|g_variant_new
argument_list|(
literal|"(b)"
argument_list|,
name|shootvals
operator|->
name|show_cursor
argument_list|)
expr_stmt|;
comment|/* FIXME: figure profile */
break|break;
case|case
name|SHOOT_REGION
case|:
break|break;
comment|/* FIXME: GNOME-shell has a "SelectArea" returning coordinates        * which can be fed to "ScreenshotArea". KDE has the equivalent        * "screenshotArea", but no "SelectArea" equivalent that I could        * find.        * Also at first, I expected "interactive" method to take care of        * the whole selecting-are-then-screenshotting workflow, but this        * is apparently only made to select interactively a specific        * window, not an area.        */
name|method
operator|=
literal|"screenshotArea"
expr_stmt|;
name|args
operator|=
name|g_variant_new
argument_list|(
literal|"(iiii)"
argument_list|,
name|shootvals
operator|->
name|x1
argument_list|,
name|shootvals
operator|->
name|y1
argument_list|,
name|shootvals
operator|->
name|x2
operator|-
name|shootvals
operator|->
name|x1
argument_list|,
name|shootvals
operator|->
name|y2
operator|-
name|shootvals
operator|->
name|y1
argument_list|)
expr_stmt|;
name|args
operator|=
name|NULL
expr_stmt|;
break|break;
case|case
name|SHOOT_WINDOW
case|:
if|if
condition|(
name|shootvals
operator|->
name|select_delay
operator|>
literal|0
condition|)
name|screenshot_delay
argument_list|(
name|shootvals
operator|->
name|select_delay
argument_list|)
expr_stmt|;
comment|/* XXX I expected "screenshotWindowUnderCursor" method to be the        * right one, but it returns nothing, nor is there a file        * descriptor in argument. So I don't understand how to grab the        * screenshot. Also "interactive" changes the cursor to a        * crosshair, waiting for click, which is more helpful than        * immediate screenshot under cursor.        */
name|method
operator|=
literal|"interactive"
expr_stmt|;
name|mask
operator|=
operator|(
name|shootvals
operator|->
name|decorate
condition|?
literal|1
else|:
literal|0
operator|)
operator||
operator|(
name|shootvals
operator|->
name|show_cursor
condition|?
literal|1
operator|<<
literal|1
else|:
literal|0
operator|)
expr_stmt|;
name|args
operator|=
name|g_variant_new
argument_list|(
literal|"(i)"
argument_list|,
name|mask
argument_list|)
expr_stmt|;
comment|/* FIXME: figure monitor */
break|break;
block|}
name|retval
operator|=
name|g_dbus_proxy_call_sync
argument_list|(
name|proxy
argument_list|,
name|method
argument_list|,
name|args
argument_list|,
name|G_DBUS_CALL_FLAGS_NONE
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|retval
condition|)
goto|goto
name|failure
goto|;
name|g_variant_get
argument_list|(
name|retval
argument_list|,
literal|"(s)"
argument_list|,
operator|&
name|filename
argument_list|)
expr_stmt|;
name|g_variant_unref
argument_list|(
name|retval
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|GimpColorProfile
modifier|*
name|profile
decl_stmt|;
operator|*
name|image_ID
operator|=
name|gimp_file_load
argument_list|(
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|filename
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_image_set_filename
argument_list|(
operator|*
name|image_ID
argument_list|,
literal|"screenshot.png"
argument_list|)
expr_stmt|;
comment|/* This is very wrong in multi-display setups since we have no        * idea which profile is to be used. Let's keep it anyway and        * assume always the monitor 0, which will still work in common        * cases.        */
name|profile
operator|=
name|gimp_screen_get_color_profile
argument_list|(
name|screen
argument_list|,
name|monitor
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
condition|)
block|{
name|gimp_image_set_color_profile
argument_list|(
operator|*
name|image_ID
argument_list|,
name|profile
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
name|g_unlink
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|proxy
argument_list|)
expr_stmt|;
name|proxy
operator|=
name|NULL
expr_stmt|;
return|return
name|GIMP_PDB_SUCCESS
return|;
block|}
name|failure
label|:
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|proxy
argument_list|)
expr_stmt|;
name|proxy
operator|=
name|NULL
expr_stmt|;
return|return
name|GIMP_PDB_EXECUTION_ERROR
return|;
block|}
end_function

end_unit

