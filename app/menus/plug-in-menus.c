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
file|"string.h"
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-ins.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-def.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc.h"
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
DECL|member|proc_def
name|PlugInProcDef
modifier|*
name|proc_def
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
name|gboolean
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
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|plug_in_menus_init (Gimp * gimp,GSList * plug_in_defs,const gchar * std_plugins_domain)
name|plug_in_menus_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GSList
modifier|*
name|plug_in_defs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|std_plugins_domain
parameter_list|)
block|{
name|GSList
modifier|*
name|domains
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|tmp
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|std_plugins_domain
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|domains
operator|=
name|g_slist_append
argument_list|(
name|domains
argument_list|,
operator|(
name|gpointer
operator|)
name|std_plugins_domain
argument_list|)
expr_stmt|;
name|bindtextdomain
argument_list|(
name|std_plugins_domain
argument_list|,
name|gimp_locale_directory
argument_list|()
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|HAVE_BIND_TEXTDOMAIN_CODESET
name|bind_textdomain_codeset
argument_list|(
name|std_plugins_domain
argument_list|,
literal|"UTF-8"
argument_list|)
expr_stmt|;
endif|#
directive|endif
for|for
control|(
name|tmp
operator|=
name|plug_in_defs
init|;
name|tmp
condition|;
name|tmp
operator|=
name|g_slist_next
argument_list|(
name|tmp
argument_list|)
control|)
block|{
name|PlugInDef
modifier|*
name|plug_in_def
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|locale_domain
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|locale_path
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|plug_in_def
operator|=
operator|(
name|PlugInDef
operator|*
operator|)
name|tmp
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|plug_in_def
operator|->
name|proc_defs
condition|)
continue|continue;
name|locale_domain
operator|=
name|plug_ins_locale_domain
argument_list|(
name|gimp
argument_list|,
name|plug_in_def
operator|->
name|prog
argument_list|,
operator|&
name|locale_path
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|domains
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|locale_domain
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
condition|)
break|break;
if|if
condition|(
operator|!
name|list
condition|)
block|{
name|domains
operator|=
name|g_slist_append
argument_list|(
name|domains
argument_list|,
operator|(
name|gpointer
operator|)
name|locale_domain
argument_list|)
expr_stmt|;
name|bindtextdomain
argument_list|(
name|locale_domain
argument_list|,
name|locale_path
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|HAVE_BIND_TEXTDOMAIN_CODESET
name|bind_textdomain_codeset
argument_list|(
name|locale_domain
argument_list|,
literal|"UTF-8"
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
block|}
name|g_slist_free
argument_list|(
name|domains
argument_list|)
expr_stmt|;
block|}
end_function

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
name|GTree
modifier|*
name|menu_entries
decl_stmt|;
name|GSList
modifier|*
name|list
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
name|menu_entries
operator|=
name|g_tree_new_full
argument_list|(
operator|(
name|GCompareDataFunc
operator|)
name|g_utf8_collate
argument_list|,
name|NULL
argument_list|,
name|g_free
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|manager
operator|->
name|gimp
operator|->
name|plug_in_proc_defs
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
name|PlugInProcDef
modifier|*
name|proc_def
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|proc_def
operator|->
name|prog
operator|&&
name|proc_def
operator|->
name|menu_paths
operator|&&
operator|!
name|proc_def
operator|->
name|extensions
operator|&&
operator|!
name|proc_def
operator|->
name|prefixes
operator|&&
operator|!
name|proc_def
operator|->
name|magics
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
name|proc_def
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
operator|(
operator|!
name|strncmp
argument_list|(
name|path
operator|->
name|data
argument_list|,
literal|"<Toolbox>"
argument_list|,
literal|9
argument_list|)
operator|&&
operator|!
name|strcmp
argument_list|(
name|ui_path
argument_list|,
literal|"/toolbox-menubar"
argument_list|)
operator|)
operator|||
operator|(
operator|!
name|strncmp
argument_list|(
name|path
operator|->
name|data
argument_list|,
literal|"<Image>"
argument_list|,
literal|7
argument_list|)
operator|&&
operator|(
operator|!
name|strcmp
argument_list|(
name|ui_path
argument_list|,
literal|"/image-menubar"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|ui_path
argument_list|,
literal|"/image-popup"
argument_list|)
operator|)
operator|)
condition|)
block|{
name|PlugInMenuEntry
modifier|*
name|entry
init|=
name|g_new0
argument_list|(
name|PlugInMenuEntry
argument_list|,
literal|1
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
name|gchar
modifier|*
name|stripped
decl_stmt|;
name|gchar
modifier|*
name|key
decl_stmt|;
name|entry
operator|->
name|proc_def
operator|=
name|proc_def
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
name|plug_in_proc_def_get_progname
argument_list|(
name|proc_def
argument_list|)
expr_stmt|;
name|locale_domain
operator|=
name|plug_ins_locale_domain
argument_list|(
name|manager
operator|->
name|gimp
argument_list|,
name|progname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|stripped
operator|=
name|gimp_strip_uline
argument_list|(
name|dgettext
argument_list|(
name|locale_domain
argument_list|,
name|path
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_def
operator|->
name|menu_label
condition|)
name|key
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s/%s"
argument_list|,
name|stripped
argument_list|,
name|proc_def
operator|->
name|menu_label
argument_list|)
expr_stmt|;
else|else
name|key
operator|=
name|g_strdup
argument_list|(
name|stripped
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stripped
argument_list|)
expr_stmt|;
name|g_tree_insert
argument_list|(
name|menu_entries
argument_list|,
name|key
argument_list|,
name|entry
argument_list|)
expr_stmt|;
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
block|}
end_function

begin_function
name|void
DECL|function|plug_in_menus_add_proc (GimpUIManager * manager,const gchar * ui_path,PlugInProcDef * proc_def,const gchar * menu_path)
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
name|PlugInProcDef
modifier|*
name|proc_def
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
name|action_path
decl_stmt|;
name|guint
name|merge_id
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
name|proc_def
operator|!=
name|NULL
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
name|proc_def
operator|->
name|menu_label
condition|)
block|{
name|gchar
modifier|*
name|p
init|=
name|strrchr
argument_list|(
name|path
argument_list|,
literal|'/'
argument_list|)
decl_stmt|;
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
name|proc_def
operator|->
name|db_info
operator|.
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
if|if
condition|(
name|strchr
argument_list|(
name|path
argument_list|,
literal|'/'
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|plug_in_menus_build_path
argument_list|(
name|manager
argument_list|,
name|ui_path
argument_list|,
name|merge_id
argument_list|,
name|path
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
return|return;
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
name|path
argument_list|,
literal|'/'
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|action_path
operator|=
name|g_strdup
argument_list|(
name|ui_path
argument_list|)
expr_stmt|;
block|}
if|#
directive|if
literal|0
block|g_print ("adding menu item for '%s' (@ %s)\n",            proc_def->db_info.name, action_path);
endif|#
directive|endif
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
name|proc_def
operator|->
name|db_info
operator|.
name|name
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
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
name|void
DECL|function|plug_in_menus_remove_proc (GimpUIManager * manager,PlugInProcDef * proc_def)
name|plug_in_menus_remove_proc
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
block|{
name|gchar
modifier|*
name|merge_key
decl_stmt|;
name|guint
name|merge_id
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
name|proc_def
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|merge_key
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-merge-id"
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
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
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

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
name|proc_def
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
name|gboolean
DECL|function|plug_in_menus_build_path (GimpUIManager * manager,const gchar * ui_path,guint merge_id,const gchar * menu_path)
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
parameter_list|)
block|{
name|gchar
modifier|*
name|action_path
decl_stmt|;
name|gboolean
name|retval
init|=
name|TRUE
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
return|return
name|TRUE
return|;
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
name|p
decl_stmt|;
name|p
operator|=
name|strrchr
argument_list|(
name|parent_menu_path
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
if|if
condition|(
name|plug_in_menus_build_path
argument_list|(
name|manager
argument_list|,
name|ui_path
argument_list|,
name|merge_id
argument_list|,
name|parent_menu_path
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|parent_action_path
init|=
name|action_path
decl_stmt|;
comment|/* no strdup() needed */
name|gchar
modifier|*
name|menu_item_name
decl_stmt|;
name|p
operator|=
name|strrchr
argument_list|(
name|parent_action_path
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
name|menu_item_name
operator|=
name|strrchr
argument_list|(
name|menu_path
argument_list|,
literal|'/'
argument_list|)
operator|+
literal|1
expr_stmt|;
if|#
directive|if
literal|0
block|g_print ("adding menu '%s' at path '%s' for action '%s'\n",                    menu_item_name, action_path, menu_path);
endif|#
directive|endif
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
block|}
else|else
block|{
name|retval
operator|=
name|FALSE
expr_stmt|;
block|}
name|g_free
argument_list|(
name|parent_menu_path
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|action_path
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

end_unit

