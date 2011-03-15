begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdisplay-utils.c  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/**  * Utility functions for the display module (not only the GimpDisplay  * class).  */
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
file|"gimpdisplay-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_comment
comment|/**  * gimp_display_get_action_name:  * @display:  *  * Returns: The action name for the given display. The action name  * depends on the display ID. The result must be freed with g_free().  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_display_get_action_name (GimpDisplay * display)
name|gimp_display_get_action_name
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
return|return
name|g_strdup_printf
argument_list|(
literal|"windows-display-%04d"
argument_list|,
name|gimp_display_get_ID
argument_list|(
name|display
argument_list|)
argument_list|)
return|;
block|}
end_function

end_unit

