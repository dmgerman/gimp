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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdataeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"data-editor-commands.h"
end_include

begin_include
include|#
directive|include
file|"tool-preset-editor-actions.h"
end_include

begin_include
include|#
directive|include
file|"tool-preset-editor-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|tool_preset_editor_actions
specifier|static
specifier|const
name|GimpActionEntry
name|tool_preset_editor_actions
index|[]
init|=
block|{
block|{
literal|"tool-preset-editor-popup"
block|,
name|GIMP_ICON_TOOL_PRESET
block|,
name|NC_
argument_list|(
literal|"tool-preset-editor-action"
argument_list|,
literal|"Tool Preset Editor Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_TOOL_PRESET_EDITOR_DIALOG
block|}
block|,
block|{
literal|"tool-preset-editor-save"
block|,
name|GIMP_ICON_DOCUMENT_SAVE
block|,
name|NC_
argument_list|(
literal|"tool-preset-editor-action"
argument_list|,
literal|"_Save Tool Options to Preset"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"tool-preset-editor-action"
argument_list|,
literal|"Save the active tool options to this "
literal|"tool preset"
argument_list|)
block|,
name|tool_preset_editor_save_cmd_callback
block|,
name|GIMP_HELP_TOOL_PRESET_SAVE
block|}
block|,
block|{
literal|"tool-preset-editor-restore"
block|,
name|GIMP_ICON_DOCUMENT_REVERT
block|,
name|NC_
argument_list|(
literal|"tool-preset-editor-action"
argument_list|,
literal|"_Restore Tool Preset"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"tool-preset-editor-action"
argument_list|,
literal|"Restore this tool preset"
argument_list|)
block|,
name|tool_preset_editor_restore_cmd_callback
block|,
name|GIMP_HELP_TOOL_PRESET_RESTORE
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tool_preset_editor_toggle_actions
specifier|static
specifier|const
name|GimpToggleActionEntry
name|tool_preset_editor_toggle_actions
index|[]
init|=
block|{
block|{
literal|"tool-preset-editor-edit-active"
block|,
name|GIMP_ICON_LINKED
block|,
name|NC_
argument_list|(
literal|"tool-preset-editor-action"
argument_list|,
literal|"Edit Active Tool Preset"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|data_editor_edit_active_cmd_callback
block|,
name|FALSE
block|,
name|GIMP_HELP_TOOL_PRESET_EDITOR_EDIT_ACTIVE
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|tool_preset_editor_actions_setup (GimpActionGroup * group)
name|tool_preset_editor_actions_setup
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
literal|"tool-preset-editor-action"
argument_list|,
name|tool_preset_editor_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|tool_preset_editor_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_toggle_actions
argument_list|(
name|group
argument_list|,
literal|"tool-preset-editor-action"
argument_list|,
name|tool_preset_editor_toggle_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|tool_preset_editor_toggle_actions
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_preset_editor_actions_update (GimpActionGroup * group,gpointer user_data)
name|tool_preset_editor_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|data_editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|gboolean
name|edit_active
init|=
name|FALSE
decl_stmt|;
name|edit_active
operator|=
name|gimp_data_editor_get_edit_active
argument_list|(
name|data_editor
argument_list|)
expr_stmt|;
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
name|SET_SENSITIVE
argument_list|(
literal|"tool-preset-editor-save"
argument_list|,
name|data_editor
operator|->
name|data
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"tool-preset-editor-restore"
argument_list|,
name|data_editor
operator|->
name|data
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"tool-preset-editor-edit-active"
argument_list|,
name|edit_active
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
undef|#
directive|undef
name|SET_ACTIVE
block|}
end_function

end_unit

