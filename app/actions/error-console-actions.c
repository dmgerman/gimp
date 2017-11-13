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
file|"widgets/gimperrorconsole.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"error-console-actions.h"
end_include

begin_include
include|#
directive|include
file|"error-console-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|error_console_actions
specifier|static
specifier|const
name|GimpActionEntry
name|error_console_actions
index|[]
init|=
block|{
block|{
literal|"error-console-popup"
block|,
name|GIMP_ICON_DIALOG_WARNING
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"Error Console Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_ERRORS_DIALOG
block|}
block|,
block|{
literal|"error-console-clear"
block|,
name|GIMP_ICON_EDIT_CLEAR
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"_Clear"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"Clear error console"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|error_console_clear_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_ERRORS_CLEAR
block|}
block|,
block|{
literal|"error-console-select-all"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"Select _All"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"Select all error messages"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|error_console_select_all_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_ERRORS_SELECT_ALL
block|}
block|,
block|{
literal|"error-console-highlight"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"_Highlight"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_ERRORS_HIGHLIGHT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_console_save_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|error_console_save_actions
index|[]
init|=
block|{
block|{
literal|"error-console-save-all"
block|,
name|GIMP_ICON_DOCUMENT_SAVE_AS
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"_Save Error Log to File..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"Write all error messages to a file"
argument_list|)
block|,
name|FALSE
block|,
name|FALSE
block|,
name|GIMP_HELP_ERRORS_SAVE
block|}
block|,
block|{
literal|"error-console-save-selection"
block|,
name|GIMP_ICON_DOCUMENT_SAVE_AS
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"Save S_election to File..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"Write the selected error messages to a file"
argument_list|)
block|,
name|TRUE
block|,
name|FALSE
block|,
name|GIMP_HELP_ERRORS_SAVE
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_console_highlight_actions
specifier|static
specifier|const
name|GimpToggleActionEntry
name|error_console_highlight_actions
index|[]
init|=
block|{
block|{
literal|"error-console-highlight-error"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"_Errors"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"Highlight error console on errors"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|error_console_highlight_error_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_ERRORS_HIGHLIGHT
block|}
block|,
block|{
literal|"error-console-highlight-warning"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"_Warnings"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"Highlight error console on warnings"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|error_console_highlight_warning_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_ERRORS_HIGHLIGHT
block|}
block|,
block|{
literal|"error-console-highlight-info"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"_Messages"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"error-console-action"
argument_list|,
literal|"Highlight error console on messages"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|error_console_highlight_info_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_ERRORS_HIGHLIGHT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|error_console_actions_setup (GimpActionGroup * group)
name|error_console_actions_setup
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
literal|"error-console-action"
argument_list|,
name|error_console_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|error_console_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
literal|"error-console-action"
argument_list|,
name|error_console_save_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|error_console_save_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|error_console_save_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_toggle_actions
argument_list|(
name|group
argument_list|,
literal|"error-console-action"
argument_list|,
name|error_console_highlight_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|error_console_highlight_actions
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|error_console_actions_update (GimpActionGroup * group,gpointer data)
name|error_console_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpErrorConsole
modifier|*
name|console
init|=
name|GIMP_ERROR_CONSOLE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gboolean
name|selection
decl_stmt|;
name|selection
operator|=
name|gtk_text_buffer_get_selection_bounds
argument_list|(
name|console
operator|->
name|text_buffer
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
literal|"error-console-clear"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"error-console-select-all"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"error-console-save-all"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"error-console-save-selection"
argument_list|,
name|selection
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"error-console-highlight"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"error-console-highlight-error"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"error-console-highlight-error"
argument_list|,
name|console
operator|->
name|highlight
index|[
name|GIMP_MESSAGE_ERROR
index|]
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"error-console-highlight-warning"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"error-console-highlight-warning"
argument_list|,
name|console
operator|->
name|highlight
index|[
name|GIMP_MESSAGE_WARNING
index|]
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"error-console-highlight-info"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"error-console-highlight-info"
argument_list|,
name|console
operator|->
name|highlight
index|[
name|GIMP_MESSAGE_INFO
index|]
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_ACTIVE
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

