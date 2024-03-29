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
file|<string.h>
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
file|"libgimpbase/gimpbase.h"
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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager-help-domain.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager-locale-domain.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager-menu-branch.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginprocedure.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpaction.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactionimpl.h"
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
file|"plug-in-actions.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-commands.h"
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
name|plug_in_actions_menu_branch_added
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_label
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|plug_in_actions_register_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|plug_in_actions_unregister_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|plug_in_actions_menu_path_added
parameter_list|(
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|plug_in_actions_add_proc
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|plug_in_actions_check_translation
parameter_list|(
specifier|const
name|gchar
modifier|*
name|original
parameter_list|,
specifier|const
name|gchar
modifier|*
name|translated
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|plug_in_actions_build_path
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|original
parameter_list|,
specifier|const
name|gchar
modifier|*
name|translated
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|plug_in_actions
specifier|static
specifier|const
name|GimpActionEntry
name|plug_in_actions
index|[]
init|=
block|{
block|{
literal|"plug-in-reset-all"
block|,
name|GIMP_ICON_RESET
block|,
name|NC_
argument_list|(
literal|"plug-in-action"
argument_list|,
literal|"Reset all _Filters"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"plug-in-action"
argument_list|,
literal|"Reset all plug-ins to their default settings"
argument_list|)
block|,
name|plug_in_reset_all_cmd_callback
block|,
name|GIMP_HELP_FILTER_RESET_ALL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|plug_in_actions_setup (GimpActionGroup * group)
name|plug_in_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GimpPlugInManager
modifier|*
name|manager
init|=
name|group
operator|->
name|gimp
operator|->
name|plug_in_manager
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
literal|"plug-in-action"
argument_list|,
name|plug_in_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|plug_in_actions
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_plug_in_manager_get_menu_branches
argument_list|(
name|manager
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPlugInMenuBranch
modifier|*
name|branch
init|=
name|list
operator|->
name|data
decl_stmt|;
name|plug_in_actions_menu_branch_added
argument_list|(
name|manager
argument_list|,
name|branch
operator|->
name|file
argument_list|,
name|branch
operator|->
name|menu_path
argument_list|,
name|branch
operator|->
name|menu_label
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
name|g_signal_connect_object
argument_list|(
name|manager
argument_list|,
literal|"menu-branch-added"
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_actions_menu_branch_added
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|manager
operator|->
name|plug_in_procedures
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPlugInProcedure
modifier|*
name|plug_in_proc
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|plug_in_proc
operator|->
name|file
condition|)
name|plug_in_actions_register_procedure
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|pdb
argument_list|,
name|GIMP_PROCEDURE
argument_list|(
name|plug_in_proc
argument_list|)
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
name|g_signal_connect_object
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|pdb
argument_list|,
literal|"register-procedure"
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_actions_register_procedure
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|pdb
argument_list|,
literal|"unregister-procedure"
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_actions_unregister_procedure
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|plug_in_actions_update (GimpActionGroup * group,gpointer data)
name|plug_in_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|action_data_get_image
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpPlugInManager
modifier|*
name|manager
init|=
name|group
operator|->
name|gimp
operator|->
name|plug_in_manager
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
name|image
condition|)
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|manager
operator|->
name|plug_in_procedures
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|proc
operator|->
name|menu_label
operator|&&
operator|!
name|proc
operator|->
name|file_proc
operator|&&
name|proc
operator|->
name|image_types_val
condition|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|GIMP_PROCEDURE
argument_list|(
name|proc
argument_list|)
decl_stmt|;
name|gboolean
name|sensitive
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|tooltip
decl_stmt|;
name|sensitive
operator|=
name|gimp_procedure_get_sensitive
argument_list|(
name|procedure
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|tooltip
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_sensitive
argument_list|(
name|group
argument_list|,
name|gimp_object_get_name
argument_list|(
name|proc
argument_list|)
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
if|if
condition|(
name|sensitive
operator|||
operator|!
name|drawable
operator|||
operator|!
name|tooltip
condition|)
name|tooltip
operator|=
name|gimp_procedure_get_blurb
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_tooltip
argument_list|(
name|group
argument_list|,
name|gimp_object_get_name
argument_list|(
name|proc
argument_list|)
argument_list|,
name|tooltip
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|plug_in_actions_menu_branch_added (GimpPlugInManager * manager,GFile * file,const gchar * menu_path,const gchar * menu_label,GimpActionGroup * group)
name|plug_in_actions_menu_branch_added
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_label
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|locale_domain
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|path_translated
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|label_translated
decl_stmt|;
name|gchar
modifier|*
name|full
decl_stmt|;
name|gchar
modifier|*
name|full_translated
decl_stmt|;
name|locale_domain
operator|=
name|gimp_plug_in_manager_get_locale_domain
argument_list|(
name|manager
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|path_translated
operator|=
name|dgettext
argument_list|(
name|locale_domain
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
name|label_translated
operator|=
name|dgettext
argument_list|(
name|locale_domain
argument_list|,
name|menu_label
argument_list|)
expr_stmt|;
name|full
operator|=
name|g_strconcat
argument_list|(
name|menu_path
argument_list|,
literal|"/"
argument_list|,
name|menu_label
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|full_translated
operator|=
name|g_strconcat
argument_list|(
name|path_translated
argument_list|,
literal|"/"
argument_list|,
name|label_translated
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_actions_check_translation
argument_list|(
name|full
argument_list|,
name|full_translated
argument_list|)
condition|)
name|plug_in_actions_build_path
argument_list|(
name|group
argument_list|,
name|full
argument_list|,
name|full_translated
argument_list|)
expr_stmt|;
else|else
name|plug_in_actions_build_path
argument_list|(
name|group
argument_list|,
name|full
argument_list|,
name|full
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|full_translated
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|full
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|plug_in_actions_register_procedure (GimpPDB * pdb,GimpProcedure * procedure,GimpActionGroup * group)
name|plug_in_actions_register_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
if|if
condition|(
name|GIMP_IS_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
condition|)
block|{
name|GimpPlugInProcedure
modifier|*
name|plug_in_proc
init|=
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
decl_stmt|;
name|g_signal_connect_object
argument_list|(
name|plug_in_proc
argument_list|,
literal|"menu-path-added"
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_actions_menu_path_added
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_proc
operator|->
name|menu_label
operator|&&
operator|!
name|plug_in_proc
operator|->
name|file_proc
condition|)
block|{
if|#
directive|if
literal|0
block|g_print ("%s: %s\n", G_STRFUNC,                    gimp_object_get_name (procedure));
endif|#
directive|endif
name|plug_in_actions_add_proc
argument_list|(
name|group
argument_list|,
name|plug_in_proc
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|plug_in_actions_unregister_procedure (GimpPDB * pdb,GimpProcedure * procedure,GimpActionGroup * group)
name|plug_in_actions_unregister_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
if|if
condition|(
name|GIMP_IS_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
condition|)
block|{
name|GimpPlugInProcedure
modifier|*
name|plug_in_proc
init|=
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
decl_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|plug_in_proc
argument_list|,
name|plug_in_actions_menu_path_added
argument_list|,
name|group
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_proc
operator|->
name|menu_label
operator|&&
operator|!
name|plug_in_proc
operator|->
name|file_proc
condition|)
block|{
name|GimpAction
modifier|*
name|action
decl_stmt|;
if|#
directive|if
literal|0
block|g_print ("%s: %s\n", G_STRFUNC,                    gimp_object_get_name (procedure));
endif|#
directive|endif
name|action
operator|=
name|gimp_action_group_get_action
argument_list|(
name|group
argument_list|,
name|gimp_object_get_name
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
condition|)
name|gimp_action_group_remove_action
argument_list|(
name|group
argument_list|,
name|action
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|plug_in_actions_menu_path_added (GimpPlugInProcedure * plug_in_proc,const gchar * menu_path,GimpActionGroup * group)
name|plug_in_actions_menu_path_added
parameter_list|(
name|GimpPlugInProcedure
modifier|*
name|plug_in_proc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|locale_domain
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|path_translated
decl_stmt|;
if|#
directive|if
literal|0
block|g_print ("%s: %s (%s)\n", G_STRFUNC,            gimp_object_get_name (plug_in_proc), menu_path);
endif|#
directive|endif
name|locale_domain
operator|=
name|gimp_plug_in_procedure_get_locale_domain
argument_list|(
name|plug_in_proc
argument_list|)
expr_stmt|;
name|path_translated
operator|=
name|dgettext
argument_list|(
name|locale_domain
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_actions_check_translation
argument_list|(
name|menu_path
argument_list|,
name|path_translated
argument_list|)
condition|)
name|plug_in_actions_build_path
argument_list|(
name|group
argument_list|,
name|menu_path
argument_list|,
name|path_translated
argument_list|)
expr_stmt|;
else|else
name|plug_in_actions_build_path
argument_list|(
name|group
argument_list|,
name|menu_path
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|plug_in_actions_add_proc (GimpActionGroup * group,GimpPlugInProcedure * proc)
name|plug_in_actions_add_proc
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
block|{
name|GimpProcedureActionEntry
name|entry
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|locale_domain
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|locale_domain
operator|=
name|gimp_plug_in_procedure_get_locale_domain
argument_list|(
name|proc
argument_list|)
expr_stmt|;
name|entry
operator|.
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|proc
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
name|proc
argument_list|)
argument_list|)
expr_stmt|;
name|entry
operator|.
name|label
operator|=
name|gimp_procedure_get_menu_label
argument_list|(
name|GIMP_PROCEDURE
argument_list|(
name|proc
argument_list|)
argument_list|)
expr_stmt|;
name|entry
operator|.
name|accelerator
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|tooltip
operator|=
name|gimp_procedure_get_blurb
argument_list|(
name|GIMP_PROCEDURE
argument_list|(
name|proc
argument_list|)
argument_list|)
expr_stmt|;
name|entry
operator|.
name|procedure
operator|=
name|GIMP_PROCEDURE
argument_list|(
name|proc
argument_list|)
expr_stmt|;
name|entry
operator|.
name|help_id
operator|=
name|gimp_procedure_get_help_id
argument_list|(
name|GIMP_PROCEDURE
argument_list|(
name|proc
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_procedure_actions
argument_list|(
name|group
argument_list|,
operator|&
name|entry
argument_list|,
literal|1
argument_list|,
name|plug_in_run_cmd_callback
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|proc
operator|->
name|menu_paths
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
specifier|const
name|gchar
modifier|*
name|original
init|=
name|list
operator|->
name|data
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|translated
init|=
name|dgettext
argument_list|(
name|locale_domain
argument_list|,
name|original
argument_list|)
decl_stmt|;
if|if
condition|(
name|plug_in_actions_check_translation
argument_list|(
name|original
argument_list|,
name|translated
argument_list|)
condition|)
name|plug_in_actions_build_path
argument_list|(
name|group
argument_list|,
name|original
argument_list|,
name|translated
argument_list|)
expr_stmt|;
else|else
name|plug_in_actions_build_path
argument_list|(
name|group
argument_list|,
name|original
argument_list|,
name|original
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|proc
operator|->
name|image_types_val
condition|)
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
name|GimpImage
modifier|*
name|image
init|=
name|gimp_context_get_image
argument_list|(
name|context
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|NULL
decl_stmt|;
name|gboolean
name|sensitive
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|tooltip
decl_stmt|;
if|if
condition|(
name|image
condition|)
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|sensitive
operator|=
name|gimp_procedure_get_sensitive
argument_list|(
name|GIMP_PROCEDURE
argument_list|(
name|proc
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|tooltip
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_sensitive
argument_list|(
name|group
argument_list|,
name|gimp_object_get_name
argument_list|(
name|proc
argument_list|)
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sensitive
operator|&&
name|drawable
operator|&&
name|tooltip
condition|)
name|gimp_action_group_set_action_tooltip
argument_list|(
name|group
argument_list|,
name|gimp_object_get_name
argument_list|(
name|proc
argument_list|)
argument_list|,
name|tooltip
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|plug_in_actions_check_translation (const gchar * original,const gchar * translated)
name|plug_in_actions_check_translation
parameter_list|(
specifier|const
name|gchar
modifier|*
name|original
parameter_list|,
specifier|const
name|gchar
modifier|*
name|translated
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|p1
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|p2
decl_stmt|;
comment|/*  first check if<Prefix> is present and identical in both strings  */
name|p1
operator|=
name|strchr
argument_list|(
name|original
argument_list|,
literal|'>'
argument_list|)
expr_stmt|;
name|p2
operator|=
name|strchr
argument_list|(
name|translated
argument_list|,
literal|'>'
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|p1
operator|||
operator|!
name|p2
operator|||
operator|(
name|p1
operator|-
name|original
operator|)
operator|!=
operator|(
name|p2
operator|-
name|translated
operator|)
operator|||
name|strncmp
argument_list|(
name|original
argument_list|,
name|translated
argument_list|,
name|p1
operator|-
name|original
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"bad translation \"%s\"\n"
literal|"for menu path   \"%s\"\n"
literal|"(<Prefix> must not be translated)\n\n"
argument_list|,
name|translated
argument_list|,
name|original
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|p1
operator|++
expr_stmt|;
name|p2
operator|++
expr_stmt|;
comment|/*  then check if either a '/' or nothing follows in *both* strings  */
if|if
condition|(
operator|!
operator|(
operator|(
operator|*
name|p1
operator|==
literal|'/'
operator|&&
operator|*
name|p2
operator|==
literal|'/'
operator|)
operator|||
operator|(
operator|*
name|p1
operator|==
literal|'\0'
operator|&&
operator|*
name|p2
operator|==
literal|'\0'
operator|)
operator|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"bad translation \"%s\"\n"
literal|"for menu path   \"%s\"\n"
literal|"(<Prefix> must be followed by either nothing or '/')\n\n"
argument_list|,
name|translated
argument_list|,
name|original
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/*  then check the number of slashes in the remaining string  */
while|while
condition|(
name|p1
operator|&&
name|p2
condition|)
block|{
name|p1
operator|=
name|strchr
argument_list|(
name|p1
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
name|p2
operator|=
name|strchr
argument_list|(
name|p2
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
name|p1
condition|)
name|p1
operator|++
expr_stmt|;
if|if
condition|(
name|p2
condition|)
name|p2
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|p1
operator|||
name|p2
condition|)
block|{
name|g_printerr
argument_list|(
literal|"bad translation \"%s\"\n"
literal|"for menu path   \"%s\"\n"
literal|"(number of '/' must be the same)\n\n"
argument_list|,
name|translated
argument_list|,
name|original
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|plug_in_actions_build_path (GimpActionGroup * group,const gchar * path_original,const gchar * path_translated)
name|plug_in_actions_build_path
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_original
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_translated
parameter_list|)
block|{
name|GHashTable
modifier|*
name|path_table
decl_stmt|;
name|gchar
modifier|*
name|copy_original
decl_stmt|;
name|gchar
modifier|*
name|copy_translated
decl_stmt|;
name|gchar
modifier|*
name|p1
decl_stmt|,
modifier|*
name|p2
decl_stmt|;
name|path_table
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|group
argument_list|)
argument_list|,
literal|"plug-in-path-table"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|path_table
condition|)
block|{
name|path_table
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|group
argument_list|)
argument_list|,
literal|"plug-in-path-table"
argument_list|,
name|path_table
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_hash_table_destroy
argument_list|)
expr_stmt|;
block|}
name|copy_original
operator|=
name|gimp_strip_uline
argument_list|(
name|path_original
argument_list|)
expr_stmt|;
name|copy_translated
operator|=
name|g_strdup
argument_list|(
name|path_translated
argument_list|)
expr_stmt|;
name|p1
operator|=
name|strrchr
argument_list|(
name|copy_original
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
name|p2
operator|=
name|strrchr
argument_list|(
name|copy_translated
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
name|p1
operator|&&
name|p2
operator|&&
operator|!
name|g_hash_table_lookup
argument_list|(
name|path_table
argument_list|,
name|copy_original
argument_list|)
condition|)
block|{
name|GimpAction
modifier|*
name|action
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|label
operator|=
name|p2
operator|+
literal|1
expr_stmt|;
if|#
directive|if
literal|0
block|g_print ("adding plug-in submenu '%s' (%s)\n",                copy_original, label);
endif|#
directive|endif
name|action
operator|=
name|gimp_action_impl_new
argument_list|(
name|copy_original
argument_list|,
name|label
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_action_group_add_action
argument_list|(
name|group
argument_list|,
name|action
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|action
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|path_table
argument_list|,
name|g_strdup
argument_list|(
name|copy_original
argument_list|)
argument_list|,
name|action
argument_list|)
expr_stmt|;
operator|*
name|p1
operator|=
literal|'\0'
expr_stmt|;
operator|*
name|p2
operator|=
literal|'\0'
expr_stmt|;
comment|/* recursively call ourselves with the last part of the path removed */
name|plug_in_actions_build_path
argument_list|(
name|group
argument_list|,
name|copy_original
argument_list|,
name|copy_translated
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|copy_original
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|copy_translated
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

