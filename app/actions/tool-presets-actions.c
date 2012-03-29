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
file|"core/gimpdata.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolpreset.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
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
file|"tool-presets-actions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|tool_presets_actions
specifier|static
specifier|const
name|GimpActionEntry
name|tool_presets_actions
index|[]
init|=
block|{
block|{
literal|"tool-presets-popup"
block|,
name|GIMP_STOCK_TOOL_PRESET
block|,
name|NC_
argument_list|(
literal|"tool-presets-action"
argument_list|,
literal|"Tool Presets Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_TOOL_PRESET_DIALOG
block|}
block|,
block|{
literal|"tool-presets-new"
block|,
name|GTK_STOCK_NEW
block|,
name|NC_
argument_list|(
literal|"tool-presets-action"
argument_list|,
literal|"_New Tool Preset"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"tool-presets-action"
argument_list|,
literal|"Create a new tool preset"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_new_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOL_PRESET_NEW
block|}
block|,
block|{
literal|"tool-presets-duplicate"
block|,
name|GIMP_STOCK_DUPLICATE
block|,
name|NC_
argument_list|(
literal|"tool-presets-action"
argument_list|,
literal|"D_uplicate Tool Preset"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"tool-presets-action"
argument_list|,
literal|"Duplicate this tool preset"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_duplicate_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOL_PRESET_DUPLICATE
block|}
block|,
block|{
literal|"tool-presets-copy-location"
block|,
name|GTK_STOCK_COPY
block|,
name|NC_
argument_list|(
literal|"tool-presets-action"
argument_list|,
literal|"Copy Tool Preset _Location"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"tool-presets-action"
argument_list|,
literal|"Copy tool preset file location to clipboard"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_copy_location_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOL_PRESET_COPY_LOCATION
block|}
block|,
block|{
literal|"tool-presets-delete"
block|,
name|GTK_STOCK_DELETE
block|,
name|NC_
argument_list|(
literal|"tool-presets-action"
argument_list|,
literal|"_Delete Tool Preset"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"tool-presets-action"
argument_list|,
literal|"Delete this tool preset"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_delete_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOL_PRESET_DELETE
block|}
block|,
block|{
literal|"tool-presets-refresh"
block|,
name|GTK_STOCK_REFRESH
block|,
name|NC_
argument_list|(
literal|"tool-presets-action"
argument_list|,
literal|"_Refresh Tool Presets"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"tool-presets-action"
argument_list|,
literal|"Refresh tool presets"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_refresh_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOL_PRESET_REFRESH
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tool_presets_edit_actions
specifier|static
specifier|const
name|GimpStringActionEntry
name|tool_presets_edit_actions
index|[]
init|=
block|{
block|{
literal|"tool-presets-edit"
block|,
name|GTK_STOCK_EDIT
block|,
name|NC_
argument_list|(
literal|"tool-presets-action"
argument_list|,
literal|"_Edit Tool Preset..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"tool-presets-action"
argument_list|,
literal|"Edit this tool preset"
argument_list|)
block|,
literal|"gimp-tool-preset-editor"
block|,
name|GIMP_HELP_TOOL_PRESET_EDIT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|tool_presets_actions_setup (GimpActionGroup * group)
name|tool_presets_actions_setup
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
literal|"tool-presets-action"
argument_list|,
name|tool_presets_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|tool_presets_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_string_actions
argument_list|(
name|group
argument_list|,
literal|"tool-presets-action"
argument_list|,
name|tool_presets_edit_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|tool_presets_edit_actions
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
DECL|function|tool_presets_actions_update (GimpActionGroup * group,gpointer user_data)
name|tool_presets_actions_update
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
name|GimpToolPreset
modifier|*
name|tool_preset
init|=
name|NULL
decl_stmt|;
name|GimpData
modifier|*
name|data
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|filename
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|context
condition|)
block|{
name|tool_preset
operator|=
name|gimp_context_get_tool_preset
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_preset
condition|)
block|{
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|tool_preset
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_data_get_filename
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
literal|"tool-presets-edit"
argument_list|,
name|tool_preset
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"tool-presets-duplicate"
argument_list|,
name|tool_preset
operator|&&
name|GIMP_DATA_GET_CLASS
argument_list|(
name|data
argument_list|)
operator|->
name|duplicate
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"tool-presets-copy-location"
argument_list|,
name|tool_preset
operator|&&
name|filename
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"tool-presets-delete"
argument_list|,
name|tool_preset
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

