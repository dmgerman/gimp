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
file|"libgimpwidgets/gimpwidgets.h"
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
file|"plug-in/plug-in-proc.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"file-commands.h"
end_include

begin_include
include|#
directive|include
file|"file-open-menu.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|file_open_menu_entries
name|GimpItemFactoryEntry
name|file_open_menu_entries
index|[]
init|=
block|{
block|{
block|{
name|N_
argument_list|(
literal|"/Automatic"
argument_list|)
block|,
name|NULL
block|,
name|file_open_by_extension_cmd_callback
block|,
literal|0
block|}
block|,
name|NULL
block|,
name|GIMP_HELP_FILE_OPEN_BY_EXTENSION
block|,
name|NULL
block|}
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/---"
argument_list|)
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gint
name|n_file_open_menu_entries
init|=
name|G_N_ELEMENTS
argument_list|(
name|file_open_menu_entries
argument_list|)
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|file_open_menu_setup (GimpItemFactory * factory)
name|file_open_menu_setup
parameter_list|(
name|GimpItemFactory
modifier|*
name|factory
parameter_list|)
block|{
name|GimpItemFactoryEntry
name|entry
decl_stmt|;
name|PlugInProcDef
modifier|*
name|file_proc
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|factory
operator|->
name|gimp
operator|->
name|load_procs
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
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|lowercase_basename
decl_stmt|;
name|gchar
modifier|*
name|help_page
decl_stmt|;
name|file_proc
operator|=
operator|(
name|PlugInProcDef
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|file_proc
operator|->
name|prog
argument_list|)
expr_stmt|;
name|lowercase_basename
operator|=
name|g_ascii_strdown
argument_list|(
name|basename
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
comment|/*  NOT g_build_filename() because this is a relative URI */
name|help_page
operator|=
name|g_strconcat
argument_list|(
literal|"filters/"
argument_list|,
name|lowercase_basename
argument_list|,
literal|".html"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lowercase_basename
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
name|file_proc
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
name|NULL
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|callback
operator|=
name|file_open_type_cmd_callback
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
name|help_page
expr_stmt|;
name|entry
operator|.
name|description
operator|=
name|NULL
expr_stmt|;
name|gimp_item_factory_create_item
argument_list|(
name|factory
argument_list|,
operator|&
name|entry
argument_list|,
name|NULL
argument_list|,
name|file_proc
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|help_page
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

