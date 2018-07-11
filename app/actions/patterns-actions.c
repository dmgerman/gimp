begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"core/gimpdata.h"
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
file|"data-commands.h"
end_include

begin_include
include|#
directive|include
file|"patterns-actions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|patterns_actions
specifier|static
specifier|const
name|GimpActionEntry
name|patterns_actions
index|[]
init|=
block|{
block|{
literal|"patterns-popup"
block|,
name|GIMP_ICON_PATTERN
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"Patterns Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_PATTERN_DIALOG
block|}
block|,
block|{
literal|"patterns-open-as-image"
block|,
name|GIMP_ICON_DOCUMENT_OPEN
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"_Open Pattern as Image"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"Open this pattern as an image"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_open_as_image_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATTERN_OPEN_AS_IMAGE
block|}
block|,
block|{
literal|"patterns-new"
block|,
name|GIMP_ICON_DOCUMENT_NEW
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"_New Pattern"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"Create a new pattern"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_new_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATTERN_NEW
block|}
block|,
block|{
literal|"patterns-duplicate"
block|,
name|GIMP_ICON_OBJECT_DUPLICATE
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"D_uplicate Pattern"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"Duplicate this pattern"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_duplicate_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATTERN_DUPLICATE
block|}
block|,
block|{
literal|"patterns-copy-location"
block|,
name|GIMP_ICON_EDIT_COPY
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"Copy Pattern _Location"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"Copy pattern file location to clipboard"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_copy_location_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATTERN_COPY_LOCATION
block|}
block|,
block|{
literal|"patterns-show-in-file-manager"
block|,
name|GIMP_ICON_FILE_MANAGER
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"Show in _File Manager"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"Show pattern file location in the file manager"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_show_in_file_manager_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATTERN_SHOW_IN_FILE_MANAGER
block|}
block|,
block|{
literal|"patterns-delete"
block|,
name|GIMP_ICON_EDIT_DELETE
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"_Delete Pattern"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"Delete this pattern"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_delete_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATTERN_DELETE
block|}
block|,
block|{
literal|"patterns-refresh"
block|,
name|GIMP_ICON_VIEW_REFRESH
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"_Refresh Patterns"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"Refresh patterns"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_refresh_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATTERN_REFRESH
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_edit_actions
specifier|static
specifier|const
name|GimpStringActionEntry
name|patterns_edit_actions
index|[]
init|=
block|{
block|{
literal|"patterns-edit"
block|,
name|GIMP_ICON_EDIT
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"_Edit Pattern..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"patterns-action"
argument_list|,
literal|"Edit pattern"
argument_list|)
block|,
literal|"gimp-pattern-editor"
block|,
name|GIMP_HELP_PATTERN_EDIT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|patterns_actions_setup (GimpActionGroup * group)
name|patterns_actions_setup
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
literal|"patterns-action"
argument_list|,
name|patterns_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|patterns_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_string_actions
argument_list|(
name|group
argument_list|,
literal|"patterns-action"
argument_list|,
name|patterns_edit_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|patterns_edit_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|data_edit_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|patterns_actions_update (GimpActionGroup * group,gpointer user_data)
name|patterns_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|action_data_get_context
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|GimpPattern
modifier|*
name|pattern
init|=
name|NULL
decl_stmt|;
name|GimpData
modifier|*
name|data
init|=
name|NULL
decl_stmt|;
name|GFile
modifier|*
name|file
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|context
condition|)
block|{
name|pattern
operator|=
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|action_data_sel_count
argument_list|(
name|user_data
argument_list|)
operator|>
literal|1
condition|)
block|{
name|pattern
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|pattern
condition|)
block|{
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
name|file
operator|=
name|gimp_data_get_file
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
block|}
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
literal|"patterns-edit"
argument_list|,
name|pattern
operator|&&
name|FALSE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"patterns-open-as-image"
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"patterns-duplicate"
argument_list|,
name|pattern
operator|&&
name|gimp_data_is_duplicatable
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"patterns-copy-location"
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"patterns-show-in-file-manager"
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"patterns-delete"
argument_list|,
name|pattern
operator|&&
name|gimp_data_is_deletable
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

