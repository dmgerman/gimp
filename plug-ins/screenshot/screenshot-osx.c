begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Screenshot plug-in  * Copyright 1998-2007 Sven Neumann<sven@gimp.org>  * Copyright 2003      Henrik Brix Andersen<brix@gimp.org>  * Copyright 2012      Simone Karin Lehmann - OS X patches  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|PLATFORM_OSX
end_ifdef

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_comment
comment|/* for system() on OSX */
end_comment

begin_include
include|#
directive|include
file|<string.h>
end_include

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
file|"screenshot-osx.h"
end_include

begin_comment
comment|/*  * Mac OS X uses a rootless X server. This won't let us use  * gdk_pixbuf_get_from_drawable() and similar function on the root  * window to get the entire screen contents. With a nytive OS X build  * we have to do this without X as well.  *  * Since Mac OS X 10.2 a system utility for screencapturing is  * included. We can safely use this, since it's available on every OS  * X version GIMP is running on.  *  * The main drawbacks are that it's not possible to shoot windows or  * regions in scripts in noninteractive mode, and that windows always  * include decorations, since decorations are different between X11  * windows and native OS X app windows. But we can use this switch  * to capture the shadow of a window, which is indeed very Mac-ish.  *  * This routines works well with X11 and as a navtive build  */
end_comment

begin_function
name|gboolean
DECL|function|screenshot_osx_available (void)
name|screenshot_osx_available
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|ScreenshotCapabilities
DECL|function|screenshot_osx_get_capabilities (void)
name|screenshot_osx_get_capabilities
parameter_list|(
name|void
parameter_list|)
block|{
return|return
operator|(
name|SCREENSHOT_CAN_SHOOT_DECORATIONS
operator||
name|SCREENSHOT_CAN_SHOOT_POINTER
operator|)
return|;
block|}
end_function

begin_function
name|GimpPDBStatusType
DECL|function|screenshot_osx_shoot (ScreenshotValues * shootvals,GdkScreen * screen,gint32 * image_ID)
name|screenshot_osx_shoot
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
parameter_list|)
block|{
name|gchar
modifier|*
name|mode
init|=
literal|" "
decl_stmt|;
name|gchar
modifier|*
name|delay
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|cursor
init|=
literal|" "
decl_stmt|;
name|gchar
modifier|*
name|command
init|=
name|NULL
decl_stmt|;
switch|switch
condition|(
name|shootvals
operator|->
name|shoot_type
condition|)
block|{
case|case
name|SHOOT_REGION
case|:
name|mode
operator|=
literal|"-is"
expr_stmt|;
break|break;
case|case
name|SHOOT_WINDOW
case|:
name|mode
operator|=
literal|"-iwo"
expr_stmt|;
if|if
condition|(
name|shootvals
operator|->
name|decorate
condition|)
name|mode
operator|=
literal|"-iw"
expr_stmt|;
break|break;
case|case
name|SHOOT_ROOT
case|:
name|mode
operator|=
literal|" "
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|delay
operator|=
name|g_strdup_printf
argument_list|(
literal|"-T %i"
argument_list|,
name|shootvals
operator|->
name|select_delay
argument_list|)
expr_stmt|;
if|if
condition|(
name|shootvals
operator|->
name|show_cursor
condition|)
name|cursor
operator|=
literal|"-C"
expr_stmt|;
name|command
operator|=
name|g_strjoin
argument_list|(
literal|" "
argument_list|,
literal|"/usr/sbin/screencapture"
argument_list|,
name|mode
argument_list|,
name|cursor
argument_list|,
name|delay
argument_list|,
literal|"/tmp/screenshot.png"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|system
argument_list|(
operator|(
specifier|const
name|char
operator|*
operator|)
name|command
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|command
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|delay
argument_list|)
expr_stmt|;
operator|*
name|image_ID
operator|=
name|gimp_file_load
argument_list|(
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
literal|"/tmp/screenshot.png"
argument_list|,
literal|"/tmp/screenshot.png"
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
return|return
name|GIMP_PDB_SUCCESS
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* PLATFORM_OSX */
end_comment

end_unit

