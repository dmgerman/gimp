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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"config-commands.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|config_use_gegl_cmd_callback (GtkAction * action,gpointer data)
name|config_use_gegl_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkToggleAction
modifier|*
name|toggle_action
init|=
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
decl_stmt|;
name|Gimp
modifier|*
name|gimp
init|=
name|NULL
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
literal|"use-gegl"
argument_list|,
name|gtk_toggle_action_get_active
argument_list|(
name|toggle_action
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

