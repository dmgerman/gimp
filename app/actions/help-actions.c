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
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"actions-types.h"
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
file|"help-actions.h"
end_include

begin_include
include|#
directive|include
file|"help-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|help_actions
specifier|static
specifier|const
name|GimpActionEntry
name|help_actions
index|[]
init|=
block|{
block|{
literal|"help-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"help-action"
argument_list|,
literal|"_Help"
argument_list|)
block|}
block|,
block|{
literal|"help-help"
block|,
literal|"gimp-prefs-help-system"
block|,
name|NC_
argument_list|(
literal|"help-action"
argument_list|,
literal|"_Help"
argument_list|)
block|,
literal|"F1"
block|,
name|NC_
argument_list|(
literal|"help-action"
argument_list|,
literal|"Open the GIMP user manual"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|help_help_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_HELP
block|}
block|,
block|{
literal|"help-context-help"
block|,
literal|"gimp-prefs-help-system"
block|,
name|NC_
argument_list|(
literal|"help-action"
argument_list|,
literal|"_Context Help"
argument_list|)
block|,
literal|"<shift>F1"
block|,
name|NC_
argument_list|(
literal|"help-action"
argument_list|,
literal|"Show the help for a specific user interface item"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|help_context_help_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_HELP_CONTEXT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|help_actions_setup (GimpActionGroup * group)
name|help_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
literal|"help-action"
argument_list|,
name|help_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|help_actions
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|help_actions_update (GimpActionGroup * group,gpointer data)
name|help_actions_update
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

