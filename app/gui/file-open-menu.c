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
file|"plug-in/plug-ins.h"
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
name|file_type_cmd_callback
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
DECL|function|file_open_menu_setup (GimpItemFactory * factory,gpointer callback_data)
name|file_open_menu_setup
parameter_list|(
name|GimpItemFactory
modifier|*
name|factory
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
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
name|PlugInProcDef
modifier|*
name|file_proc
init|=
name|list
operator|->
name|data
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|locale_domain
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|item_type
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|stock_id
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|help_id
decl_stmt|;
name|GimpItemFactoryEntry
name|entry
decl_stmt|;
name|gboolean
name|is_xcf
decl_stmt|;
name|GtkWidget
modifier|*
name|menu_item
decl_stmt|;
if|if
condition|(
operator|!
name|file_proc
operator|->
name|menu_path
condition|)
continue|continue;
name|is_xcf
operator|=
operator|(
name|strcmp
argument_list|(
name|file_proc
operator|->
name|db_info
operator|.
name|name
argument_list|,
literal|"gimp_xcf_load"
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
if|if
condition|(
name|is_xcf
condition|)
block|{
name|item_type
operator|=
literal|"<StockItem>"
expr_stmt|;
name|stock_id
operator|=
name|GIMP_STOCK_WILBER
expr_stmt|;
name|help_id
operator|=
name|g_strdup
argument_list|(
name|GIMP_HELP_FILE_OPEN_XCF
argument_list|)
expr_stmt|;
block|}
else|else
block|{
specifier|const
name|gchar
modifier|*
name|progname
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|help_domain
decl_stmt|;
name|progname
operator|=
name|plug_in_proc_def_get_progname
argument_list|(
name|file_proc
argument_list|)
expr_stmt|;
name|locale_domain
operator|=
name|plug_ins_locale_domain
argument_list|(
name|factory
operator|->
name|gimp
argument_list|,
name|progname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|help_domain
operator|=
name|plug_ins_help_domain
argument_list|(
name|factory
operator|->
name|gimp
argument_list|,
name|progname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|help_id
operator|=
name|plug_in_proc_def_get_help_id
argument_list|(
name|file_proc
argument_list|,
name|help_domain
argument_list|)
expr_stmt|;
block|}
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
name|file_type_cmd_callback
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
operator|(
name|gchar
operator|*
operator|)
name|item_type
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|extra_data
operator|=
name|stock_id
expr_stmt|;
name|entry
operator|.
name|quark_string
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|help_id
operator|=
name|help_id
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
name|locale_domain
argument_list|,
name|callback_data
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|menu_item
operator|=
name|gtk_item_factory_get_widget
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
name|entry
operator|.
name|entry
operator|.
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu_item
condition|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menu_item
argument_list|)
argument_list|,
literal|"file-proc"
argument_list|,
name|file_proc
argument_list|)
expr_stmt|;
if|if
condition|(
name|is_xcf
condition|)
name|gtk_menu_reorder_child
argument_list|(
name|GTK_MENU
argument_list|(
name|menu_item
operator|->
name|parent
argument_list|)
argument_list|,
name|menu_item
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|help_id
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

