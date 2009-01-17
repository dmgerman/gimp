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
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"config-actions.h"
end_include

begin_include
include|#
directive|include
file|"config-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|config_toggle_actions
specifier|static
specifier|const
name|GimpToggleActionEntry
name|config_toggle_actions
index|[]
init|=
block|{
block|{
literal|"config-use-gegl"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"config-action"
argument_list|,
literal|"Use _GEGL"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"config-action"
argument_list|,
literal|"If possible, use GEGL for image processing"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|config_use_gegl_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_CONFIG_USE_GEGL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|config_actions_use_gegl_notify (GObject * config,GParamSpec * pspec,GimpActionGroup * group)
name|config_actions_use_gegl_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gboolean
name|active
decl_stmt|;
name|g_object_get
argument_list|(
name|config
argument_list|,
literal|"use-gegl"
argument_list|,
operator|&
name|active
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_active
argument_list|(
name|group
argument_list|,
literal|"config-use-gegl"
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|config_actions_setup (GimpActionGroup * group)
name|config_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_add_toggle_actions
argument_list|(
name|group
argument_list|,
literal|"config-action"
argument_list|,
name|config_toggle_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|config_toggle_actions
argument_list|)
argument_list|)
expr_stmt|;
name|config_actions_use_gegl_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|group
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::use-gegl"
argument_list|,
name|G_CALLBACK
argument_list|(
name|config_actions_use_gegl_notify
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|config_actions_update (GimpActionGroup * group,gpointer data)
name|config_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{ }
end_function

end_unit

