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
file|"widgets/gimpsamplepointeditor.h"
end_include

begin_include
include|#
directive|include
file|"sample-points-actions.h"
end_include

begin_include
include|#
directive|include
file|"sample-points-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|sample_points_actions
specifier|static
specifier|const
name|GimpActionEntry
name|sample_points_actions
index|[]
init|=
block|{
block|{
literal|"sample-points-popup"
block|,
name|GIMP_STOCK_SAMPLE_POINT
block|,
name|NC_
argument_list|(
literal|"sample-points-action"
argument_list|,
literal|"Sample Point Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_SAMPLE_POINT_DIALOG
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|sample_points_toggle_actions
specifier|static
specifier|const
name|GimpToggleActionEntry
name|sample_points_toggle_actions
index|[]
init|=
block|{
block|{
literal|"sample-points-sample-merged"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"sample-points-action"
argument_list|,
literal|"_Sample Merged"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"sample-points-action"
argument_list|,
literal|"Use the composite color of all visible layers"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|sample_points_sample_merged_cmd_callback
argument_list|)
block|,
name|TRUE
block|,
name|GIMP_HELP_SAMPLE_POINT_SAMPLE_MERGED
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|sample_points_actions_setup (GimpActionGroup * group)
name|sample_points_actions_setup
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
literal|"sample-points-action"
argument_list|,
name|sample_points_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|sample_points_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_toggle_actions
argument_list|(
name|group
argument_list|,
literal|"sample-points-action"
argument_list|,
name|sample_points_toggle_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|sample_points_toggle_actions
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|sample_points_actions_update (GimpActionGroup * group,gpointer data)
name|sample_points_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpSamplePointEditor
modifier|*
name|editor
init|=
name|GIMP_SAMPLE_POINT_EDITOR
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
literal|"sample-points-sample-merged"
argument_list|,
name|gimp_sample_point_editor_get_sample_merged
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_ACTIVE
block|}
end_function

end_unit

