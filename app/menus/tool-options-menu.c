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
file|"menus-types.h"
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
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"tool-options-menu.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|tool_options_menu_update
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
name|gpointer
name|update_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_options_menu_update_after
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
name|gpointer
name|update_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_options_menu_update_presets
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
name|guint
name|merge_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|which_action
parameter_list|,
name|GimpContainer
modifier|*
name|presets
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|tool_options_menu_setup (GimpUIManager * manager,const gchar * ui_path)
name|tool_options_menu_setup
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|)
block|{
name|g_signal_connect
argument_list|(
name|manager
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_menu_update
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|ui_path
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|manager
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_menu_update_after
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|ui_path
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|tool_options_menu_update (GimpUIManager * manager,gpointer update_data,const gchar * ui_path)
name|tool_options_menu_update
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
name|gpointer
name|update_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|)
block|{
name|guint
name|merge_id
decl_stmt|;
name|merge_id
operator|=
name|GPOINTER_TO_UINT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
literal|"tool-options-merge-id"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|merge_id
condition|)
block|{
name|gtk_ui_manager_remove_ui
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_id
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
literal|"tool-options-merge-id"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_ui_manager_ensure_update
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_options_menu_update_after (GimpUIManager * manager,gpointer update_data,const gchar * ui_path)
name|tool_options_menu_update_after
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
name|gpointer
name|update_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|guint
name|merge_id
decl_stmt|;
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|manager
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tool_info
operator|->
name|options_presets
condition|)
return|return;
name|merge_id
operator|=
name|gtk_ui_manager_new_merge_id
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
literal|"tool-options-merge-id"
argument_list|,
name|GUINT_TO_POINTER
argument_list|(
name|merge_id
argument_list|)
argument_list|)
expr_stmt|;
name|tool_options_menu_update_presets
argument_list|(
name|manager
argument_list|,
name|merge_id
argument_list|,
name|ui_path
argument_list|,
literal|"Save"
argument_list|,
literal|"save"
argument_list|,
name|tool_info
operator|->
name|options_presets
argument_list|)
expr_stmt|;
name|tool_options_menu_update_presets
argument_list|(
name|manager
argument_list|,
name|merge_id
argument_list|,
name|ui_path
argument_list|,
literal|"Restore"
argument_list|,
literal|"restore"
argument_list|,
name|tool_info
operator|->
name|options_presets
argument_list|)
expr_stmt|;
name|tool_options_menu_update_presets
argument_list|(
name|manager
argument_list|,
name|merge_id
argument_list|,
name|ui_path
argument_list|,
literal|"Rename"
argument_list|,
literal|"rename"
argument_list|,
name|tool_info
operator|->
name|options_presets
argument_list|)
expr_stmt|;
name|tool_options_menu_update_presets
argument_list|(
name|manager
argument_list|,
name|merge_id
argument_list|,
name|ui_path
argument_list|,
literal|"Delete"
argument_list|,
literal|"delete"
argument_list|,
name|tool_info
operator|->
name|options_presets
argument_list|)
expr_stmt|;
name|gtk_ui_manager_ensure_update
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_options_menu_update_presets (GimpUIManager * manager,guint merge_id,const gchar * ui_path,const gchar * menu_path,const gchar * which_action,GimpContainer * presets)
name|tool_options_menu_update_presets
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
name|guint
name|merge_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|which_action
parameter_list|,
name|GimpContainer
modifier|*
name|presets
parameter_list|)
block|{
name|gint
name|n_children
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|n_children
operator|=
name|gimp_container_num_children
argument_list|(
name|presets
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_children
condition|;
name|i
operator|++
control|)
block|{
name|gchar
modifier|*
name|action_name
decl_stmt|;
name|gchar
modifier|*
name|path
decl_stmt|;
name|action_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"tool-options-%s-%03d"
argument_list|,
name|which_action
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|path
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s/%s"
argument_list|,
name|ui_path
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
name|gtk_ui_manager_add_ui
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_id
argument_list|,
name|path
argument_list|,
name|action_name
argument_list|,
name|action_name
argument_list|,
name|GTK_UI_MANAGER_MENUITEM
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

