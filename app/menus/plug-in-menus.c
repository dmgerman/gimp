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
file|"plug-in/plug-in.h"
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
file|"widgets/gimpitemfactory.h"
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
file|"libgimp/gimpintl.h"
end_include

begin_function
name|void
DECL|function|plug_in_make_menu (GSList * plug_in_defs,const gchar * std_plugins_domain)
name|plug_in_make_menu
parameter_list|(
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
name|PlugInDef
modifier|*
name|plug_in_def
decl_stmt|;
name|PlugInProcDef
modifier|*
name|proc_def
decl_stmt|;
name|PlugInMenuEntry
modifier|*
name|menu_entry
decl_stmt|;
name|GSList
modifier|*
name|domains
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|procs
decl_stmt|;
name|GSList
modifier|*
name|tmp
decl_stmt|;
name|GTree
modifier|*
name|menu_entries
decl_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_NLS
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
endif|#
directive|endif
ifdef|#
directive|ifdef
name|ENABLE_NLS
name|menu_entries
operator|=
name|g_tree_new
argument_list|(
operator|(
name|GCompareFunc
operator|)
name|strcoll
argument_list|)
expr_stmt|;
else|#
directive|else
name|menu_entries
operator|=
name|g_tree_new
argument_list|(
operator|(
name|GCompareFunc
operator|)
name|strcmp
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|tmp
operator|=
name|plug_in_defs
expr_stmt|;
while|while
condition|(
name|tmp
condition|)
block|{
name|plug_in_def
operator|=
name|tmp
operator|->
name|data
expr_stmt|;
name|tmp
operator|=
name|tmp
operator|->
name|next
expr_stmt|;
name|procs
operator|=
name|plug_in_def
operator|->
name|proc_defs
expr_stmt|;
if|if
condition|(
operator|!
name|procs
condition|)
continue|continue;
ifdef|#
directive|ifdef
name|ENABLE_NLS
block|{
name|gchar
modifier|*
name|domain
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|gboolean
name|found
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|plug_in_def
operator|->
name|locale_domain
condition|)
block|{
name|domain
operator|=
name|plug_in_def
operator|->
name|locale_domain
expr_stmt|;
for|for
control|(
name|list
operator|=
name|domains
init|;
name|list
operator|&&
operator|!
name|found
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
name|strcmp
argument_list|(
name|domain
argument_list|,
operator|(
name|gchar
operator|*
operator|)
operator|(
name|list
operator|->
name|data
operator|)
argument_list|)
operator|==
literal|0
condition|)
name|found
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|found
condition|)
block|{
name|domains
operator|=
name|g_slist_append
argument_list|(
name|domains
argument_list|,
name|domain
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_def
operator|->
name|locale_path
condition|)
name|bindtextdomain
argument_list|(
name|domain
argument_list|,
name|plug_in_def
operator|->
name|locale_path
argument_list|)
expr_stmt|;
else|else
name|bindtextdomain
argument_list|(
name|domain
argument_list|,
name|gimp_locale_directory
argument_list|()
argument_list|)
expr_stmt|;
name|bind_textdomain_codeset
argument_list|(
name|domain
argument_list|,
literal|"UTF-8"
argument_list|)
expr_stmt|;
block|}
block|}
block|}
endif|#
directive|endif
comment|/*  ENABLE_NLS  */
while|while
condition|(
name|procs
condition|)
block|{
name|proc_def
operator|=
name|procs
operator|->
name|data
expr_stmt|;
name|procs
operator|=
name|procs
operator|->
name|next
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
operator|(
name|plug_in_def
operator|->
name|locale_domain
condition|?
name|plug_in_def
operator|->
name|locale_domain
else|:
operator|(
name|gchar
operator|*
operator|)
name|std_plugins_domain
operator|)
expr_stmt|;
name|menu_entry
operator|->
name|help_path
operator|=
name|plug_in_def
operator|->
name|help_path
expr_stmt|;
name|g_tree_insert
argument_list|(
name|menu_entries
argument_list|,
name|dgettext
argument_list|(
name|menu_entry
operator|->
name|domain
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
block|}
name|g_tree_foreach
argument_list|(
name|menu_entries
argument_list|,
operator|(
name|GTraverseFunc
operator|)
name|plug_in_make_menu_entry
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_tree_destroy
argument_list|(
name|menu_entries
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|domains
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|plug_in_escape_uline (const gchar * menu_path)
name|plug_in_escape_uline
parameter_list|(
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|)
block|{
name|gchar
modifier|*
name|uline
decl_stmt|;
name|gchar
modifier|*
name|escaped
decl_stmt|;
name|gchar
modifier|*
name|tmp
decl_stmt|;
name|escaped
operator|=
name|g_strdup
argument_list|(
name|menu_path
argument_list|)
expr_stmt|;
name|uline
operator|=
name|strchr
argument_list|(
name|escaped
argument_list|,
literal|'_'
argument_list|)
expr_stmt|;
while|while
condition|(
name|uline
condition|)
block|{
name|tmp
operator|=
name|escaped
expr_stmt|;
name|escaped
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|strlen
argument_list|(
name|tmp
argument_list|)
operator|+
literal|2
argument_list|)
expr_stmt|;
if|if
condition|(
name|uline
operator|>
name|tmp
condition|)
name|strncpy
argument_list|(
name|escaped
argument_list|,
name|tmp
argument_list|,
operator|(
name|uline
operator|-
name|tmp
operator|)
argument_list|)
expr_stmt|;
name|escaped
index|[
name|uline
operator|-
name|tmp
index|]
operator|=
literal|'_'
expr_stmt|;
name|strcpy
argument_list|(
operator|&
name|escaped
index|[
name|uline
operator|-
name|tmp
operator|+
literal|1
index|]
argument_list|,
name|uline
argument_list|)
expr_stmt|;
name|uline
operator|=
name|strchr
argument_list|(
name|escaped
operator|+
operator|(
name|uline
operator|-
name|tmp
operator|)
operator|+
literal|2
argument_list|,
literal|'_'
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
return|return
name|escaped
return|;
block|}
end_function

begin_comment
comment|/*  The following function has to be a GTraverseFunction,   *  but is also called directly. Please note that it frees the  *  menu_entry strcuture.                --Sven   */
end_comment

begin_function
name|gint
DECL|function|plug_in_make_menu_entry (gpointer foo,PlugInMenuEntry * menu_entry,gpointer bar)
name|plug_in_make_menu_entry
parameter_list|(
name|gpointer
name|foo
parameter_list|,
name|PlugInMenuEntry
modifier|*
name|menu_entry
parameter_list|,
name|gpointer
name|bar
parameter_list|)
block|{
name|GimpItemFactoryEntry
name|entry
decl_stmt|;
name|gchar
modifier|*
name|menu_path
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
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|menu_entry
operator|->
name|proc_def
operator|->
name|prog
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu_entry
operator|->
name|help_path
condition|)
block|{
name|help_page
operator|=
name|g_strconcat
argument_list|(
name|menu_entry
operator|->
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
name|menu_path
operator|=
name|plug_in_escape_uline
argument_list|(
name|strstr
argument_list|(
name|menu_entry
operator|->
name|proc_def
operator|->
name|menu_path
argument_list|,
literal|"/"
argument_list|)
argument_list|)
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|path
operator|=
name|menu_path
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|accelerator
operator|=
name|menu_entry
operator|->
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
block|{
name|GimpItemFactory
modifier|*
name|item_factory
decl_stmt|;
name|item_factory
operator|=
name|gimp_item_factory_from_path
argument_list|(
name|menu_entry
operator|->
name|proc_def
operator|->
name|menu_path
argument_list|)
expr_stmt|;
name|gimp_item_factory_create_item
argument_list|(
name|item_factory
argument_list|,
operator|&
name|entry
argument_list|,
name|menu_entry
operator|->
name|domain
argument_list|,
operator|&
name|menu_entry
operator|->
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
name|g_free
argument_list|(
name|menu_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lowercase_page
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|menu_entry
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|plug_in_delete_menu_entry (const gchar * menu_path)
name|plug_in_delete_menu_entry
parameter_list|(
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|)
block|{
name|GimpItemFactory
modifier|*
name|item_factory
decl_stmt|;
name|item_factory
operator|=
name|gimp_item_factory_from_path
argument_list|(
name|menu_path
argument_list|)
expr_stmt|;
name|gtk_item_factory_delete_item
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|plug_in_set_menu_sensitivity (GimpImageType type)
name|plug_in_set_menu_sensitivity
parameter_list|(
name|GimpImageType
name|type
parameter_list|)
block|{
name|GtkItemFactory
modifier|*
name|item_factory
decl_stmt|;
name|PlugInProcDef
modifier|*
name|proc_def
decl_stmt|;
name|GSList
modifier|*
name|tmp
decl_stmt|;
name|gboolean
name|sensitive
init|=
name|FALSE
decl_stmt|;
for|for
control|(
name|tmp
operator|=
name|proc_defs
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
name|proc_def
operator|=
name|tmp
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|proc_def
operator|->
name|image_types_val
operator|&&
name|proc_def
operator|->
name|menu_path
condition|)
block|{
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
name|item_factory
operator|=
name|GTK_ITEM_FACTORY
argument_list|(
name|gimp_item_factory_from_path
argument_list|(
name|proc_def
operator|->
name|menu_path
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_sensitive
argument_list|(
name|item_factory
argument_list|,
name|proc_def
operator|->
name|menu_path
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
if|if
condition|(
name|last_plug_in
operator|&&
operator|(
name|last_plug_in
operator|==
operator|&
operator|(
name|proc_def
operator|->
name|db_info
operator|)
operator|)
condition|)
block|{
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
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|proc_def
operator|->
name|menu_path
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
literal|"Repeat \"%s\""
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
literal|"Re-show \"%s\""
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
name|item_factory
argument_list|,
literal|"/Filters/Repeat Last"
argument_list|,
name|repeat
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_label
argument_list|(
name|item_factory
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
name|item_factory
argument_list|,
literal|"/Filters/Repeat Last"
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_sensitive
argument_list|(
name|item_factory
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
operator|!
name|last_plug_in
condition|)
block|{
name|item_factory
operator|=
name|GTK_ITEM_FACTORY
argument_list|(
name|gimp_item_factory_from_path
argument_list|(
literal|"<Image>"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_label
argument_list|(
name|item_factory
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
name|item_factory
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
name|item_factory
argument_list|,
literal|"/Filters/Repeat Last"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_sensitive
argument_list|(
name|item_factory
argument_list|,
literal|"/Filters/Re-Show Last"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

