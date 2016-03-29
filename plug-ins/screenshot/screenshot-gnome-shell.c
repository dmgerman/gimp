begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Screenshot plug-in  * Copyright 1998-2007 Sven Neumann<sven@gimp.org>  * Copyright 2003      Henrik Brix Andersen<brix@gimp.org>  * Copyright 2016      Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"screenshot-gnome-shell.h"
end_include

begin_function
name|gboolean
DECL|function|screenshot_gnome_shell_available (void)
name|screenshot_gnome_shell_available
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|ScreenshotCapabilities
DECL|function|screenshot_gnome_shell_get_capabilities (void)
name|screenshot_gnome_shell_get_capabilities
parameter_list|(
name|void
parameter_list|)
block|{
return|return
literal|0
return|;
block|}
end_function

begin_function
name|GimpPDBStatusType
DECL|function|screenshot_gnome_shell_shoot (ScreenshotValues * shootvals,GdkScreen * screen,gint32 * image_ID)
name|screenshot_gnome_shell_shoot
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
return|return
name|GIMP_PDB_SUCCESS
return|;
block|}
end_function

end_unit

