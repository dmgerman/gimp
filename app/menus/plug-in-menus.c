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
file|<string.h>
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
file|"menus-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager-locale-domain.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginprocedure.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-menus.h"
end_include

begin_include
include|#
directive|include
file|"gimp-log.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|PlugInMenuEntry
typedef|typedef
name|struct
name|_PlugInMenuEntry
name|PlugInMenuEntry
typedef|;
end_typedef

begin_struct
DECL|struct|_PlugInMenuEntry
struct|struct
name|_PlugInMenuEntry
block|{
DECL|member|proc
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
DECL|member|menu_path
specifier|const
name|gchar
modifier|*
name|menu_path
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|plug_in_menus_register_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|plug_in_menus_unregister_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|plug_in_menus_menu_path_added
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
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|plug_in_menus_add_proc
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|plug_in_menus_tree_insert
parameter_list|(
name|GTree
modifier|*
name|entries
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|PlugInMenuEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|plug_in_menus_tree_traverse
parameter_list|(
name|gpointer
name|key
parameter_list|,
name|PlugInMenuEntry
modifier|*
name|entry
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|plug_in_menus_build_path
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|,
name|guint
name|merge_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
name|gboolean
name|for_menu
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|plug_in_menu_entry_free
parameter_list|(
name|PlugInMenuEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|plug_in_menus_setup (GimpUIManager * manager,const gchar * ui_path)
name|plug_in_menus_setup
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
name|GimpPlugInManager
modifier|*
name|plug_in_manager
decl_stmt|;
name|GTree
modifier|*
name|menu_entries
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|guint
name|merge_id
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|ui_path
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|plug_in_manager
operator|=
name|manager
operator|->
name|gimp
operator|->
name|plug_in_manager
expr_stmt|;
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
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|manager
operator|->
name|gimp
operator|->
name|config
operator|->
name|plug_in_history_size
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
name|action_path
decl_stmt|;
name|action_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"plug-in-recent-%02d"
argument_list|,
name|i
operator|+
literal|1
argument_list|)
expr_stmt|;
name|action_path
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s/Filters/Recently Used/Plug-Ins"
argument_list|,
name|ui_path
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
name|action_path
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
name|action_path
argument_list|)
expr_stmt|;
block|}
name|menu_entries
operator|=
name|g_tree_new_full
argument_list|(
operator|(
name|GCompareDataFunc
operator|)
name|strcmp
argument_list|,
name|NULL
argument_list|,
name|g_free
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|plug_in_menu_entry_free
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|plug_in_manager
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
operator|!
name|plug_in_proc
operator|->
name|prog
condition|)
continue|continue;
name|g_signal_connect_object
argument_list|(
name|plug_in_proc
argument_list|,
literal|"menu-path-added"
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_menus_menu_path_added
argument_list|)
argument_list|,
name|manager
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_proc
operator|->
name|menu_paths
operator|&&
operator|!
name|plug_in_proc
operator|->
name|file_proc
condition|)
block|{
name|GList
modifier|*
name|path
decl_stmt|;
for|for
control|(
name|path
operator|=
name|plug_in_proc
operator|->
name|menu_paths
init|;
name|path
condition|;
name|path
operator|=
name|g_list_next
argument_list|(
name|path
argument_list|)
control|)
block|{
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|path
operator|->
name|data
argument_list|,
name|manager
operator|->
name|name
argument_list|)
condition|)
block|{
name|PlugInMenuEntry
modifier|*
name|entry
init|=
name|g_slice_new0
argument_list|(
name|PlugInMenuEntry
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|progname
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|locale_domain
decl_stmt|;
name|entry
operator|->
name|proc
operator|=
name|plug_in_proc
expr_stmt|;
name|entry
operator|->
name|menu_path
operator|=
name|path
operator|->
name|data
expr_stmt|;
name|progname
operator|=
name|gimp_plug_in_procedure_get_progname
argument_list|(
name|plug_in_proc
argument_list|)
expr_stmt|;
name|locale_domain
operator|=
name|gimp_plug_in_manager_get_locale_domain
argument_list|(
name|plug_in_manager
argument_list|,
name|progname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_proc
operator|->
name|menu_label
condition|)
block|{
name|gchar
modifier|*
name|menu
decl_stmt|;
name|menu
operator|=
name|g_strconcat
argument_list|(
name|dgettext
argument_list|(
name|locale_domain
argument_list|,
name|path
operator|->
name|data
argument_list|)
argument_list|,
literal|"/"
argument_list|,
name|dgettext
argument_list|(
name|locale_domain
argument_list|,
name|plug_in_proc
operator|->
name|menu_label
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|plug_in_menus_tree_insert
argument_list|(
name|menu_entries
argument_list|,
name|menu
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|menu
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|plug_in_menus_tree_insert
argument_list|(
name|menu_entries
argument_list|,
name|dgettext
argument_list|(
name|locale_domain
argument_list|,
name|path
operator|->
name|data
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
block|}
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
literal|"ui-path"
argument_list|,
operator|(
name|gpointer
operator|)
name|ui_path
argument_list|)
expr_stmt|;
name|g_tree_foreach
argument_list|(
name|menu_entries
argument_list|,
operator|(
name|GTraverseFunc
operator|)
name|plug_in_menus_tree_traverse
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
literal|"ui-path"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_tree_destroy
argument_list|(
name|menu_entries
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|manager
operator|->
name|gimp
operator|->
name|pdb
argument_list|,
literal|"register-procedure"
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_menus_register_procedure
argument_list|)
argument_list|,
name|manager
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|manager
operator|->
name|gimp
operator|->
name|pdb
argument_list|,
literal|"unregister-procedure"
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_menus_unregister_procedure
argument_list|)
argument_list|,
name|manager
argument_list|,
literal|0
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
DECL|function|plug_in_menus_register_procedure (GimpPDB * pdb,GimpProcedure * procedure,GimpUIManager * manager)
name|plug_in_menus_register_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
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
name|plug_in_menus_menu_path_added
argument_list|)
argument_list|,
name|manager
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|plug_in_proc
operator|->
name|menu_label
operator|||
name|plug_in_proc
operator|->
name|menu_paths
operator|)
operator|&&
operator|!
name|plug_in_proc
operator|->
name|file_proc
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GIMP_LOG
argument_list|(
name|MENUS
argument_list|,
literal|"register procedure: %s"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|plug_in_proc
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
name|plug_in_menus_menu_path_added
argument_list|(
name|plug_in_proc
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|manager
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|plug_in_menus_unregister_procedure (GimpPDB * pdb,GimpProcedure * procedure,GimpUIManager * manager)
name|plug_in_menus_unregister_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
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
name|plug_in_menus_menu_path_added
argument_list|,
name|manager
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|plug_in_proc
operator|->
name|menu_label
operator|||
name|plug_in_proc
operator|->
name|menu_paths
operator|)
operator|&&
operator|!
name|plug_in_proc
operator|->
name|file_proc
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GIMP_LOG
argument_list|(
name|MENUS
argument_list|,
literal|"unregister procedure: %s"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|plug_in_proc
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
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|manager
operator|->
name|name
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|merge_key
decl_stmt|;
name|guint
name|merge_id
decl_stmt|;
name|merge_key
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-merge-id"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|plug_in_proc
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
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
name|merge_key
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|merge_key
argument_list|)
expr_stmt|;
if|if
condition|(
name|merge_id
condition|)
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
break|break;
block|}
block|}
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|plug_in_menus_menu_path_added (GimpPlugInProcedure * plug_in_proc,const gchar * menu_path,GimpUIManager * manager)
name|plug_in_menus_menu_path_added
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
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
block|{
name|GIMP_LOG
argument_list|(
name|MENUS
argument_list|,
literal|"menu path added: %s (%s)"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|plug_in_proc
argument_list|)
argument_list|)
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|menu_path
argument_list|,
name|manager
operator|->
name|name
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|manager
operator|->
name|name
argument_list|,
literal|"<Image>"
argument_list|)
condition|)
block|{
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
literal|"/image-menubar"
argument_list|,
name|plug_in_proc
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
literal|"/dummy-menubar/image-popup"
argument_list|,
name|plug_in_proc
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|manager
operator|->
name|name
argument_list|,
literal|"<Toolbox>"
argument_list|)
condition|)
block|{
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
literal|"/toolbox-menubar"
argument_list|,
name|plug_in_proc
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|manager
operator|->
name|name
argument_list|,
literal|"<Layers>"
argument_list|)
condition|)
block|{
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
literal|"/layers-popup"
argument_list|,
name|plug_in_proc
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|manager
operator|->
name|name
argument_list|,
literal|"<Channels>"
argument_list|)
condition|)
block|{
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
literal|"/channels-popup"
argument_list|,
name|plug_in_proc
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|manager
operator|->
name|name
argument_list|,
literal|"<Vectors>"
argument_list|)
condition|)
block|{
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
literal|"/vectors-popup"
argument_list|,
name|plug_in_proc
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|manager
operator|->
name|name
argument_list|,
literal|"<Colormap>"
argument_list|)
condition|)
block|{
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
literal|"/colormap-popup"
argument_list|,
name|plug_in_proc
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|manager
operator|->
name|name
argument_list|,
literal|"<Brushes>"
argument_list|)
condition|)
block|{
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
literal|"/brushes-popup"
argument_list|,
name|plug_in_proc
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|manager
operator|->
name|name
argument_list|,
literal|"<Dynamics>"
argument_list|)
condition|)
block|{
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
literal|"/dynamics-popup"
argument_list|,
name|plug_in_proc
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|manager
operator|->
name|name
argument_list|,
literal|"<Gradients>"
argument_list|)
condition|)
block|{
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
literal|"/gradients-popup"
argument_list|,
name|plug_in_proc
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|manager
operator|->
name|name
argument_list|,
literal|"<Palettes>"
argument_list|)
condition|)
block|{
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
literal|"/palettes-popup"
argument_list|,
name|plug_in_proc
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|manager
operator|->
name|name
argument_list|,
literal|"<Patterns>"
argument_list|)
condition|)
block|{
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
literal|"/patterns-popup"
argument_list|,
name|plug_in_proc
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|manager
operator|->
name|name
argument_list|,
literal|"<Fonts>"
argument_list|)
condition|)
block|{
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
literal|"/fonts-popup"
argument_list|,
name|plug_in_proc
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|manager
operator|->
name|name
argument_list|,
literal|"<Buffers>"
argument_list|)
condition|)
block|{
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
literal|"/buffers-popup"
argument_list|,
name|plug_in_proc
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|plug_in_menus_add_proc (GimpUIManager * manager,const gchar * ui_path,GimpPlugInProcedure * proc,const gchar * menu_path)
name|plug_in_menus_add_proc
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|)
block|{
name|gchar
modifier|*
name|path
decl_stmt|;
name|gchar
modifier|*
name|merge_key
decl_stmt|;
name|gchar
modifier|*
name|stripped_path
decl_stmt|;
name|gchar
modifier|*
name|action_path
decl_stmt|;
name|guint
name|merge_id
decl_stmt|;
name|guint
name|menu_merge_id
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|ui_path
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_PROCEDURE
argument_list|(
name|proc
argument_list|)
argument_list|)
expr_stmt|;
name|path
operator|=
name|g_strdup
argument_list|(
name|menu_path
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
operator|->
name|menu_label
condition|)
block|{
name|gchar
modifier|*
name|p
decl_stmt|;
if|if
condition|(
operator|!
name|path
condition|)
return|return;
name|p
operator|=
name|strrchr
argument_list|(
name|path
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|p
condition|)
block|{
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
return|return;
block|}
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
block|}
name|merge_key
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-merge-id"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|proc
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
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
name|merge_key
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|merge_id
condition|)
block|{
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
name|merge_key
argument_list|,
name|GUINT_TO_POINTER
argument_list|(
name|merge_id
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|merge_key
argument_list|)
expr_stmt|;
name|menu_merge_id
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
literal|"plug-in-menu-merge-id"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|menu_merge_id
condition|)
block|{
name|menu_merge_id
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
literal|"plug-in-menu-merge-id"
argument_list|,
name|GUINT_TO_POINTER
argument_list|(
name|menu_merge_id
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|stripped_path
operator|=
name|gimp_strip_uline
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|action_path
operator|=
name|plug_in_menus_build_path
argument_list|(
name|manager
argument_list|,
name|ui_path
argument_list|,
name|menu_merge_id
argument_list|,
name|stripped_path
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stripped_path
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|action_path
condition|)
block|{
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
return|return;
block|}
name|GIMP_LOG
argument_list|(
name|MENUS
argument_list|,
literal|"adding menu item for '%s' (@ %s)"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|proc
argument_list|)
operator|->
name|name
argument_list|,
name|action_path
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
name|action_path
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|proc
argument_list|)
operator|->
name|name
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|proc
argument_list|)
operator|->
name|name
argument_list|,
name|GTK_UI_MANAGER_MENUITEM
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|action_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|plug_in_menus_tree_insert (GTree * entries,const gchar * path,PlugInMenuEntry * entry)
name|plug_in_menus_tree_insert
parameter_list|(
name|GTree
modifier|*
name|entries
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|PlugInMenuEntry
modifier|*
name|entry
parameter_list|)
block|{
name|gchar
modifier|*
name|strip
init|=
name|gimp_strip_uline
argument_list|(
name|path
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|key
decl_stmt|;
comment|/* Append the procedure name to the menu path in order to get a unique    * key even if two procedures are installed to the same menu entry.    */
name|key
operator|=
name|g_strconcat
argument_list|(
name|strip
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|entry
operator|->
name|proc
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_tree_insert
argument_list|(
name|entries
argument_list|,
name|g_utf8_collate_key
argument_list|(
name|key
argument_list|,
operator|-
literal|1
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|key
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|strip
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|plug_in_menus_tree_traverse (gpointer key,PlugInMenuEntry * entry,GimpUIManager * manager)
name|plug_in_menus_tree_traverse
parameter_list|(
name|gpointer
name|key
parameter_list|,
name|PlugInMenuEntry
modifier|*
name|entry
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|ui_path
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
literal|"ui-path"
argument_list|)
decl_stmt|;
name|plug_in_menus_add_proc
argument_list|(
name|manager
argument_list|,
name|ui_path
argument_list|,
name|entry
operator|->
name|proc
argument_list|,
name|entry
operator|->
name|menu_path
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|plug_in_menus_build_path (GimpUIManager * manager,const gchar * ui_path,guint merge_id,const gchar * menu_path,gboolean for_menu)
name|plug_in_menus_build_path
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|,
name|guint
name|merge_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
name|gboolean
name|for_menu
parameter_list|)
block|{
name|gchar
modifier|*
name|action_path
decl_stmt|;
if|if
condition|(
operator|!
name|strchr
argument_list|(
name|menu_path
argument_list|,
literal|'/'
argument_list|)
condition|)
block|{
name|action_path
operator|=
name|g_strdup
argument_list|(
name|ui_path
argument_list|)
expr_stmt|;
goto|goto
name|make_placeholder
goto|;
block|}
name|action_path
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s%s"
argument_list|,
name|ui_path
argument_list|,
name|strchr
argument_list|(
name|menu_path
argument_list|,
literal|'/'
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_ui_manager_get_widget
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|action_path
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|parent_menu_path
init|=
name|g_strdup
argument_list|(
name|menu_path
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|parent_action_path
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|menu_item_name
decl_stmt|;
name|menu_item_name
operator|=
name|strrchr
argument_list|(
name|parent_menu_path
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
operator|*
name|menu_item_name
operator|++
operator|=
literal|'\0'
expr_stmt|;
if|if
condition|(
name|menu_item_name
condition|)
name|parent_action_path
operator|=
name|plug_in_menus_build_path
argument_list|(
name|manager
argument_list|,
name|ui_path
argument_list|,
name|merge_id
argument_list|,
name|parent_menu_path
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|parent_action_path
condition|)
block|{
name|g_free
argument_list|(
name|action_path
argument_list|)
expr_stmt|;
name|action_path
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s/%s"
argument_list|,
name|parent_action_path
argument_list|,
name|menu_item_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_ui_manager_get_widget
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|action_path
argument_list|)
condition|)
block|{
name|GIMP_LOG
argument_list|(
name|MENUS
argument_list|,
literal|"adding menu '%s' at path '%s' for action '%s'"
argument_list|,
name|menu_item_name
argument_list|,
name|action_path
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
name|parent_action_path
argument_list|,
name|menu_item_name
argument_list|,
name|menu_path
argument_list|,
name|GTK_UI_MANAGER_MENU
argument_list|,
name|FALSE
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
name|action_path
argument_list|,
literal|"Menus"
argument_list|,
name|NULL
argument_list|,
name|GTK_UI_MANAGER_PLACEHOLDER
argument_list|,
name|FALSE
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
name|action_path
argument_list|,
literal|"Separator"
argument_list|,
name|NULL
argument_list|,
name|GTK_UI_MANAGER_SEPARATOR
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|parent_action_path
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
name|action_path
argument_list|)
expr_stmt|;
name|action_path
operator|=
name|NULL
expr_stmt|;
block|}
name|g_free
argument_list|(
name|parent_menu_path
argument_list|)
expr_stmt|;
block|}
name|make_placeholder
label|:
if|if
condition|(
name|action_path
operator|&&
name|for_menu
condition|)
block|{
name|gchar
modifier|*
name|placeholder_path
init|=
name|g_strdup_printf
argument_list|(
literal|"%s/%s"
argument_list|,
name|action_path
argument_list|,
literal|"Menus"
argument_list|)
decl_stmt|;
if|if
condition|(
name|gtk_ui_manager_get_widget
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|placeholder_path
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|action_path
argument_list|)
expr_stmt|;
return|return
name|placeholder_path
return|;
block|}
name|g_free
argument_list|(
name|placeholder_path
argument_list|)
expr_stmt|;
block|}
return|return
name|action_path
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|plug_in_menu_entry_free (PlugInMenuEntry * entry)
name|plug_in_menu_entry_free
parameter_list|(
name|PlugInMenuEntry
modifier|*
name|entry
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|PlugInMenuEntry
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

