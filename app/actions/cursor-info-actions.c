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
file|"widgets/gimpcursorview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"cursor-info-actions.h"
end_include

begin_include
include|#
directive|include
file|"cursor-info-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|cursor_info_actions
specifier|static
specifier|const
name|GimpActionEntry
name|cursor_info_actions
index|[]
init|=
block|{
block|{
literal|"cursor-info-popup"
block|,
name|GIMP_STOCK_CURSOR
block|,
name|N_
argument_list|(
literal|"Pointer Information Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_POINTER_INFO_DIALOG
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cursor_info_toggle_actions
specifier|static
specifier|const
name|GimpToggleActionEntry
name|cursor_info_toggle_actions
index|[]
init|=
block|{
block|{
literal|"cursor-info-sample-merged"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Sample Merged"
argument_list|)
block|,
literal|""
block|,
name|N_
argument_list|(
literal|"Sample Merged"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|cursor_info_sample_merged_cmd_callback
argument_list|)
block|,
name|TRUE
block|,
name|GIMP_HELP_POINTER_INFO_SAMPLE_MERGED
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|cursor_info_actions_setup (GimpActionGroup * group)
name|cursor_info_actions_setup
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
name|cursor_info_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|cursor_info_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_toggle_actions
argument_list|(
name|group
argument_list|,
name|cursor_info_toggle_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|cursor_info_toggle_actions
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|cursor_info_actions_update (GimpActionGroup * group,gpointer data)
name|cursor_info_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpCursorView
modifier|*
name|view
init|=
name|GIMP_CURSOR_VIEW
argument_list|(
name|data
argument_list|)
decl_stmt|;
DECL|macro|SET_ACTIVE (action,condition)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_active (group, action, (condition) != 0)
name|SET_ACTIVE
argument_list|(
literal|"cursor-info-sample-merged"
argument_list|,
name|gimp_cursor_view_get_sample_merged
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_ACTIVE
block|}
end_function

end_unit

