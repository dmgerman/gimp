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
file|"gui-types.h"
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
file|"plug-in/plug-in-run.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-commands.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-menus.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpenv.h"
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
DECL|member|domain
specifier|const
name|gchar
modifier|*
name|domain
decl_stmt|;
DECL|member|help_path
specifier|const
name|gchar
modifier|*
name|help_path
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
name|plug_in_menu_tree_traverse_func
parameter_list|(
name|gpointer
name|foo
parameter_list|,
name|PlugInMenuEntry
modifier|*
name|menu_entry
parameter_list|,
name|GimpItemFactory
modifier|*
name|item_factory
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
name|bind_textdomain_codeset
argument_list|(
name|std_plugins_domain
argument_list|,
literal|"UTF-8"
argument_list|)
expr_stmt|;
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
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|locale_domain
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
condition|)
break|break;
block|}
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
name|bind_textdomain_codeset
argument_list|(
name|locale_domain
argument_list|,
literal|"UTF-8"
argument_list|)
expr_stmt|;
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
DECL|function|plug_in_menus_create (GimpItemFactory * item_factory,GSList * proc_defs)
name|plug_in_menus_create
parameter_list|(
name|GimpItemFactory
modifier|*
name|item_factory
parameter_list|,
name|GSList
modifier|*
name|proc_defs
parameter_list|)
block|{
name|PlugInProcDef
modifier|*
name|proc_def
decl_stmt|;
name|GSList
modifier|*
name|procs
decl_stmt|;
name|GTree
modifier|*
name|menu_entries
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|proc_defs
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
name|NULL
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
for|for
control|(
name|procs
operator|=
name|proc_defs
init|;
name|procs
condition|;
name|procs
operator|=
name|procs
operator|->
name|next
control|)
block|{
name|proc_def
operator|=
name|procs
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|proc_def
operator|->
name|prog
operator|&&
name|proc_def
operator|->
name|menu_path
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
name|PlugInMenuEntry
modifier|*
name|menu_entry
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
specifier|const
name|gchar
modifier|*
name|help_path
decl_stmt|;
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
name|item_factory
operator|->
name|gimp
argument_list|,
name|progname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|help_path
operator|=
name|plug_ins_help_path
argument_list|(
name|item_factory
operator|->
name|gimp
argument_list|,
name|progname
argument_list|)
expr_stmt|;
name|menu_entry
operator|=
name|g_new0
argument_list|(
name|PlugInMenuEntry
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|menu_entry
operator|->
name|proc_def
operator|=
name|proc_def
expr_stmt|;
name|menu_entry
operator|->
name|domain
operator|=
name|locale_domain
expr_stmt|;
name|menu_entry
operator|->
name|help_path
operator|=
name|help_path
expr_stmt|;
name|g_tree_insert
argument_list|(
name|menu_entries
argument_list|,
name|dgettext
argument_list|(
name|locale_domain
argument_list|,
name|proc_def
operator|->
name|menu_path
argument_list|)
argument_list|,
name|menu_entry
argument_list|)
expr_stmt|;
block|}
block|}
name|g_tree_foreach
argument_list|(
name|menu_entries
argument_list|,
operator|(
name|GTraverseFunc
operator|)
name|plug_in_menu_tree_traverse_func
argument_list|,
name|item_factory
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
DECL|function|plug_in_menus_create_entry (GimpItemFactory * item_factory,PlugInProcDef * proc_def,const gchar * locale_domain,const gchar * help_path)
name|plug_in_menus_create_entry
parameter_list|(
name|GimpItemFactory
modifier|*
name|item_factory
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|,
specifier|const
name|gchar
modifier|*
name|locale_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_path
parameter_list|)
block|{
name|GimpItemFactoryEntry
name|entry
decl_stmt|;
name|gchar
modifier|*
name|help_page
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|lowercase_page
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|item_factory
operator|==
name|NULL
operator|||
name|GIMP_IS_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|)
expr_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|proc_def
operator|->
name|prog
argument_list|)
expr_stmt|;
if|if
condition|(
name|help_path
condition|)
block|{
name|help_page
operator|=
name|g_strconcat
argument_list|(
name|help_path
argument_list|,
literal|"@"
argument_list|,
comment|/* HACK: locale subdir */
name|basename
argument_list|,
literal|".html"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|help_page
operator|=
name|g_strconcat
argument_list|(
literal|"filters/"
argument_list|,
comment|/* _not_ G_DIR_SEPARATOR_S */
name|basename
argument_list|,
literal|".html"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|lowercase_page
operator|=
name|g_ascii_strdown
argument_list|(
name|help_page
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|help_page
argument_list|)
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|path
operator|=
name|strstr
argument_list|(
name|proc_def
operator|->
name|menu_path
argument_list|,
literal|"/"
argument_list|)
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|accelerator
operator|=
name|proc_def
operator|->
name|accelerator
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|callback
operator|=
name|plug_in_run_cmd_callback
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|callback_action
operator|=
literal|0
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|item_type
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|quark_string
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|help_page
operator|=
name|lowercase_page
expr_stmt|;
name|entry
operator|.
name|description
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|item_factory
condition|)
block|{
name|gchar
modifier|*
name|factory_path
decl_stmt|;
name|factory_path
operator|=
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
operator|->
name|path
expr_stmt|;
if|if
condition|(
operator|!
name|strncmp
argument_list|(
name|proc_def
operator|->
name|menu_path
argument_list|,
name|factory_path
argument_list|,
name|strlen
argument_list|(
name|factory_path
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_item_factory_create_item
argument_list|(
name|item_factory
argument_list|,
operator|&
name|entry
argument_list|,
name|locale_domain
argument_list|,
operator|&
name|proc_def
operator|->
name|db_info
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_item_factories_from_path
argument_list|(
name|proc_def
operator|->
name|menu_path
argument_list|)
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
name|item_factory
operator|=
name|list
operator|->
name|data
expr_stmt|;
name|gimp_item_factory_create_item
argument_list|(
name|item_factory
argument_list|,
operator|&
name|entry
argument_list|,
name|locale_domain
argument_list|,
operator|&
name|proc_def
operator|->
name|db_info
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|lowercase_page
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|plug_in_menus_delete_entry (const gchar * menu_path)
name|plug_in_menus_delete_entry
parameter_list|(
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|path
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|menu_path
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|path
operator|=
name|gimp_menu_path_strip_uline
argument_list|(
name|menu_path
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_item_factories_from_path
argument_list|(
name|menu_path
argument_list|)
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
name|GtkItemFactory
modifier|*
name|item_factory
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gtk_item_factory_delete_item
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
name|path
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|plug_in_menus_update (GimpItemFactory * item_factory,GimpImageType type)
name|plug_in_menus_update
parameter_list|(
name|GimpItemFactory
modifier|*
name|item_factory
parameter_list|,
name|GimpImageType
name|type
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|factory_path
decl_stmt|;
name|gint
name|factory_path_len
decl_stmt|;
name|gboolean
name|is_image_factory
init|=
name|FALSE
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|)
expr_stmt|;
name|factory_path
operator|=
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
operator|->
name|path
expr_stmt|;
name|factory_path_len
operator|=
name|strlen
argument_list|(
name|factory_path
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|factory_path
argument_list|,
literal|"<Image>"
argument_list|)
condition|)
name|is_image_factory
operator|=
name|TRUE
expr_stmt|;
for|for
control|(
name|list
operator|=
name|item_factory
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
name|menu_path
operator|&&
name|proc_def
operator|->
name|image_types_val
condition|)
block|{
name|gboolean
name|sensitive
decl_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_RGB_IMAGE
case|:
name|sensitive
operator|=
name|proc_def
operator|->
name|image_types_val
operator|&
name|PLUG_IN_RGB_IMAGE
expr_stmt|;
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
name|sensitive
operator|=
name|proc_def
operator|->
name|image_types_val
operator|&
name|PLUG_IN_RGBA_IMAGE
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY_IMAGE
case|:
name|sensitive
operator|=
name|proc_def
operator|->
name|image_types_val
operator|&
name|PLUG_IN_GRAY_IMAGE
expr_stmt|;
break|break;
case|case
name|GIMP_GRAYA_IMAGE
case|:
name|sensitive
operator|=
name|proc_def
operator|->
name|image_types_val
operator|&
name|PLUG_IN_GRAYA_IMAGE
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED_IMAGE
case|:
name|sensitive
operator|=
name|proc_def
operator|->
name|image_types_val
operator|&
name|PLUG_IN_INDEXED_IMAGE
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
name|sensitive
operator|=
name|proc_def
operator|->
name|image_types_val
operator|&
name|PLUG_IN_INDEXEDA_IMAGE
expr_stmt|;
break|break;
default|default:
name|sensitive
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|!
name|strncmp
argument_list|(
name|proc_def
operator|->
name|menu_path
argument_list|,
name|factory_path
argument_list|,
name|factory_path_len
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|menu_path
decl_stmt|;
name|menu_path
operator|=
name|gimp_menu_path_strip_uline
argument_list|(
name|proc_def
operator|->
name|menu_path
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_sensitive
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
name|menu_path
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|menu_path
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|is_image_factory
operator|&&
name|item_factory
operator|->
name|gimp
operator|->
name|last_plug_in
operator|&&
name|item_factory
operator|->
name|gimp
operator|->
name|last_plug_in
operator|==
operator|&
name|proc_def
operator|->
name|db_info
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|progname
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|path
decl_stmt|;
name|gchar
modifier|*
name|stripped
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|ellipses
decl_stmt|;
name|gchar
modifier|*
name|repeat
decl_stmt|;
name|gchar
modifier|*
name|reshow
decl_stmt|;
name|progname
operator|=
name|plug_in_proc_def_get_progname
argument_list|(
name|proc_def
argument_list|)
expr_stmt|;
name|path
operator|=
name|dgettext
argument_list|(
name|plug_ins_locale_domain
argument_list|(
name|item_factory
operator|->
name|gimp
argument_list|,
name|progname
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|proc_def
operator|->
name|menu_path
argument_list|)
expr_stmt|;
name|stripped
operator|=
name|gimp_menu_path_strip_uline
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|stripped
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stripped
argument_list|)
expr_stmt|;
name|ellipses
operator|=
name|strstr
argument_list|(
name|basename
argument_list|,
literal|"..."
argument_list|)
expr_stmt|;
if|if
condition|(
name|ellipses
operator|&&
name|ellipses
operator|==
operator|(
name|basename
operator|+
name|strlen
argument_list|(
name|basename
argument_list|)
operator|-
literal|3
operator|)
condition|)
operator|*
name|ellipses
operator|=
literal|'\0'
expr_stmt|;
name|repeat
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Re_peat \"%s\""
argument_list|)
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|reshow
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"R_e-show \"%s\""
argument_list|)
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_label
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
literal|"/Filters/Repeat Last"
argument_list|,
name|repeat
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_label
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
literal|"/Filters/Re-Show Last"
argument_list|,
name|reshow
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|repeat
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|reshow
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_sensitive
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
literal|"/Filters/Repeat Last"
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_sensitive
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
literal|"/Filters/Re-Show Last"
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|is_image_factory
operator|&&
operator|!
name|item_factory
operator|->
name|gimp
operator|->
name|last_plug_in
condition|)
block|{
name|gimp_item_factory_set_label
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
literal|"/Filters/Repeat Last"
argument_list|,
name|_
argument_list|(
literal|"Repeat Last"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_label
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
literal|"/Filters/Re-Show Last"
argument_list|,
name|_
argument_list|(
literal|"Re-Show Last"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_sensitive
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
literal|"/Filters/Repeat Last"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_sensitive
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
literal|"/Filters/Re-Show Last"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|plug_in_menu_tree_traverse_func (gpointer foo,PlugInMenuEntry * menu_entry,GimpItemFactory * item_factory)
name|plug_in_menu_tree_traverse_func
parameter_list|(
name|gpointer
name|foo
parameter_list|,
name|PlugInMenuEntry
modifier|*
name|menu_entry
parameter_list|,
name|GimpItemFactory
modifier|*
name|item_factory
parameter_list|)
block|{
name|plug_in_menus_create_entry
argument_list|(
name|item_factory
argument_list|,
name|menu_entry
operator|->
name|proc_def
argument_list|,
name|menu_entry
operator|->
name|domain
argument_list|,
name|menu_entry
operator|->
name|help_path
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit

