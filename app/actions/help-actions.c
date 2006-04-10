begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
name|N_
argument_list|(
literal|"_Help"
argument_list|)
block|}
block|,
block|{
literal|"help-help"
block|,
name|GTK_STOCK_HELP
block|,
name|N_
argument_list|(
literal|"_Help"
argument_list|)
block|,
literal|"F1"
block|,
name|NULL
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
name|GTK_STOCK_HELP
block|,
name|N_
argument_list|(
literal|"_Context Help"
argument_list|)
block|,
literal|"<shift>F1"
block|,
name|NULL
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

