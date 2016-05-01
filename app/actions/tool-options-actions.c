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
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
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
file|"tool-options-actions.h"
end_include

begin_include
include|#
directive|include
file|"tool-options-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|tool_options_actions_update_presets
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_prefix
parameter_list|,
name|GCallback
name|callback
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpContainer
modifier|*
name|presets
parameter_list|,
name|gboolean
name|need_writable
parameter_list|,
name|gboolean
name|need_deletable
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  global variables  */
end_comment

begin_decl_stmt
DECL|variable|tool_options_actions
specifier|static
specifier|const
name|GimpActionEntry
name|tool_options_actions
index|[]
init|=
block|{
block|{
literal|"tool-options-popup"
block|,
name|GIMP_STOCK_TOOL_OPTIONS
block|,
name|NC_
argument_list|(
literal|"tool-options-action"
argument_list|,
literal|"Tool Options Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_TOOL_OPTIONS_DIALOG
block|}
block|,
block|{
literal|"tool-options-save-preset-menu"
block|,
literal|"document-save"
block|,
name|NC_
argument_list|(
literal|"tool-options-action"
argument_list|,
literal|"_Save Tool Preset"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_TOOL_OPTIONS_SAVE
block|}
block|,
block|{
literal|"tool-options-restore-preset-menu"
block|,
literal|"document-revert"
block|,
name|NC_
argument_list|(
literal|"tool-options-action"
argument_list|,
literal|"_Restore Tool Preset"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_TOOL_OPTIONS_RESTORE
block|}
block|,
block|{
literal|"tool-options-edit-preset-menu"
block|,
literal|"gtk-edit"
block|,
name|NC_
argument_list|(
literal|"tool-options-action"
argument_list|,
literal|"E_dit Tool Preset"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_TOOL_OPTIONS_EDIT
block|}
block|,
block|{
literal|"tool-options-delete-preset-menu"
block|,
literal|"edit-delete"
block|,
name|NC_
argument_list|(
literal|"tool-options-action"
argument_list|,
literal|"_Delete Tool Preset"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_TOOL_OPTIONS_DELETE
block|}
block|,
block|{
literal|"tool-options-save-new-preset"
block|,
literal|"document-new"
block|,
name|NC_
argument_list|(
literal|"tool-options-action"
argument_list|,
literal|"_New Tool Preset..."
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|tool_options_save_new_preset_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOL_OPTIONS_SAVE
block|}
block|,
block|{
literal|"tool-options-reset"
block|,
name|GIMP_STOCK_RESET
block|,
name|NC_
argument_list|(
literal|"tool-options-action"
argument_list|,
literal|"R_eset Tool Options"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"tool-options-action"
argument_list|,
literal|"Reset to default values"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|tool_options_reset_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOL_OPTIONS_RESET
block|}
block|,
block|{
literal|"tool-options-reset-all"
block|,
name|GIMP_STOCK_RESET
block|,
name|NC_
argument_list|(
literal|"tool-options-action"
argument_list|,
literal|"Reset _all Tool Options"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"tool-options-action"
argument_list|,
literal|"Reset all tool options"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|tool_options_reset_all_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOL_OPTIONS_RESET
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_define
DECL|macro|SET_VISIBLE (action,condition)
define|#
directive|define
name|SET_VISIBLE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_visible (group, action, (condition) != 0)
end_define

begin_define
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
end_define

begin_define
DECL|macro|SET_HIDE_EMPTY (action,condition)
define|#
directive|define
name|SET_HIDE_EMPTY
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_hide_empty (group, action, (condition) != 0)
end_define

begin_function
name|void
DECL|function|tool_options_actions_setup (GimpActionGroup * group)
name|tool_options_actions_setup
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
literal|"tool-options-action"
argument_list|,
name|tool_options_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|tool_options_actions
argument_list|)
argument_list|)
expr_stmt|;
name|SET_HIDE_EMPTY
argument_list|(
literal|"tool-options-restore-preset-menu"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|SET_HIDE_EMPTY
argument_list|(
literal|"tool-options-edit-preset-menu"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|SET_HIDE_EMPTY
argument_list|(
literal|"tool-options-delete-preset-menu"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_actions_update (GimpActionGroup * group,gpointer data)
name|tool_options_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|gimp_get_user_context
argument_list|(
name|group
operator|->
name|gimp
argument_list|)
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
decl_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"tool-options-save-preset-menu"
argument_list|,
name|tool_info
operator|->
name|presets
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"tool-options-restore-preset-menu"
argument_list|,
name|tool_info
operator|->
name|presets
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"tool-options-edit-preset-menu"
argument_list|,
name|tool_info
operator|->
name|presets
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"tool-options-delete-preset-menu"
argument_list|,
name|tool_info
operator|->
name|presets
argument_list|)
expr_stmt|;
name|tool_options_actions_update_presets
argument_list|(
name|group
argument_list|,
literal|"tool-options-save-preset"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_save_preset_cmd_callback
argument_list|)
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_SAVE
argument_list|,
name|tool_info
operator|->
name|presets
argument_list|,
name|TRUE
comment|/* writable */
argument_list|,
name|FALSE
comment|/* deletable */
argument_list|)
expr_stmt|;
name|tool_options_actions_update_presets
argument_list|(
name|group
argument_list|,
literal|"tool-options-restore-preset"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_restore_preset_cmd_callback
argument_list|)
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_RESTORE
argument_list|,
name|tool_info
operator|->
name|presets
argument_list|,
name|FALSE
comment|/* writable */
argument_list|,
name|FALSE
comment|/* deletable */
argument_list|)
expr_stmt|;
name|tool_options_actions_update_presets
argument_list|(
name|group
argument_list|,
literal|"tool-options-edit-preset"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_edit_preset_cmd_callback
argument_list|)
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_EDIT
argument_list|,
name|tool_info
operator|->
name|presets
argument_list|,
name|FALSE
comment|/* writable */
argument_list|,
name|FALSE
comment|/* deletable */
argument_list|)
expr_stmt|;
name|tool_options_actions_update_presets
argument_list|(
name|group
argument_list|,
literal|"tool-options-delete-preset"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_delete_preset_cmd_callback
argument_list|)
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_DELETE
argument_list|,
name|tool_info
operator|->
name|presets
argument_list|,
name|FALSE
comment|/* writable */
argument_list|,
name|TRUE
comment|/* deletable */
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private function  */
end_comment

begin_function
specifier|static
name|void
DECL|function|tool_options_actions_update_presets (GimpActionGroup * group,const gchar * action_prefix,GCallback callback,const gchar * help_id,GimpContainer * presets,gboolean need_writable,gboolean need_deletable)
name|tool_options_actions_update_presets
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_prefix
parameter_list|,
name|GCallback
name|callback
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpContainer
modifier|*
name|presets
parameter_list|,
name|gboolean
name|need_writable
parameter_list|,
name|gboolean
name|need_deletable
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|n_children
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
condition|;
name|i
operator|++
control|)
block|{
name|gchar
modifier|*
name|action_name
decl_stmt|;
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|action_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-%03d"
argument_list|,
name|action_prefix
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|action
condition|)
break|break;
name|gtk_action_group_remove_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|presets
condition|)
name|n_children
operator|=
name|gimp_container_get_n_children
argument_list|(
name|presets
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_children
operator|>
literal|0
condition|)
block|{
name|GimpEnumActionEntry
name|entry
decl_stmt|;
name|entry
operator|.
name|name
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|label
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|accelerator
operator|=
literal|""
expr_stmt|;
name|entry
operator|.
name|tooltip
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|value
operator|=
literal|0
expr_stmt|;
name|entry
operator|.
name|value_variable
operator|=
name|FALSE
expr_stmt|;
name|entry
operator|.
name|help_id
operator|=
name|help_id
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|presets
argument_list|)
operator|->
name|queue
operator|->
name|head
operator|,
name|i
operator|=
literal|0
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
operator|,
name|i
operator|++
control|)
block|{
name|GimpObject
modifier|*
name|preset
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
init|=
name|NULL
decl_stmt|;
name|entry
operator|.
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-%03d"
argument_list|,
name|action_prefix
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|entry
operator|.
name|label
operator|=
name|gimp_object_get_name
argument_list|(
name|preset
argument_list|)
expr_stmt|;
name|entry
operator|.
name|icon_name
operator|=
name|gimp_viewable_get_icon_name
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|preset
argument_list|)
argument_list|)
expr_stmt|;
name|entry
operator|.
name|value
operator|=
name|i
expr_stmt|;
name|g_object_get
argument_list|(
name|preset
argument_list|,
literal|"icon-pixbuf"
argument_list|,
operator|&
name|pixbuf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|NULL
argument_list|,
operator|&
name|entry
argument_list|,
literal|1
argument_list|,
name|callback
argument_list|)
expr_stmt|;
if|if
condition|(
name|need_writable
condition|)
name|SET_SENSITIVE
argument_list|(
name|entry
operator|.
name|name
argument_list|,
name|gimp_data_is_writable
argument_list|(
name|GIMP_DATA
argument_list|(
name|preset
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|need_deletable
condition|)
name|SET_SENSITIVE
argument_list|(
name|entry
operator|.
name|name
argument_list|,
name|gimp_data_is_deletable
argument_list|(
name|GIMP_DATA
argument_list|(
name|preset
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
name|gimp_action_group_set_action_pixbuf
argument_list|(
name|group
argument_list|,
name|entry
operator|.
name|name
argument_list|,
name|pixbuf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|entry
operator|.
name|name
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_undef
undef|#
directive|undef
name|SET_VISIBLE
end_undef

begin_undef
undef|#
directive|undef
name|SET_SENSITIVE
end_undef

begin_undef
undef|#
directive|undef
name|SET_HIDE_EMPTY
end_undef

end_unit

