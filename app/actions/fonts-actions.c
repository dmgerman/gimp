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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"text/gimpfont.h"
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
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"fonts-actions.h"
end_include

begin_include
include|#
directive|include
file|"fonts-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|fonts_actions
specifier|static
specifier|const
name|GimpActionEntry
name|fonts_actions
index|[]
init|=
block|{
block|{
literal|"fonts-popup"
block|,
literal|"gtk-select-font"
block|,
name|NC_
argument_list|(
literal|"fonts-action"
argument_list|,
literal|"Fonts Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_FONT_DIALOG
block|}
block|,
block|{
literal|"fonts-refresh"
block|,
literal|"view-refresh"
block|,
name|NC_
argument_list|(
literal|"fonts-action"
argument_list|,
literal|"_Rescan Font List"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"fonts-action"
argument_list|,
literal|"Rescan the installed fonts"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|fonts_refresh_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FONT_REFRESH
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|fonts_actions_setup (GimpActionGroup * group)
name|fonts_actions_setup
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
literal|"fonts-action"
argument_list|,
name|fonts_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|fonts_actions
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|fonts_actions_update (GimpActionGroup * group,gpointer data)
name|fonts_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
DECL|macro|SET_SENSITIVE (action,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_sensitive (group, action, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"fonts-refresh"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

