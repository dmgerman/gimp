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
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainereditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
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
file|"actions/documents-commands.h"
end_include

begin_include
include|#
directive|include
file|"documents-menu.h"
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
DECL|variable|documents_menu_entries
name|GimpItemFactoryEntry
name|documents_menu_entries
index|[]
init|=
block|{
block|{
block|{
name|N_
argument_list|(
literal|"/_Open Image"
argument_list|)
block|,
literal|""
block|,
name|documents_open_document_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_OPEN
block|}
block|,
name|NULL
block|,
name|GIMP_HELP_DOCUMENT_OPEN
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/_Raise or Open Image"
argument_list|)
block|,
literal|""
block|,
name|documents_raise_or_open_document_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_OPEN
block|}
block|,
name|NULL
block|,
name|GIMP_HELP_DOCUMENT_OPEN
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File Open _Dialog"
argument_list|)
block|,
literal|""
block|,
name|documents_file_open_dialog_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_OPEN
block|}
block|,
name|NULL
block|,
name|GIMP_HELP_DOCUMENT_OPEN
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Remove _Entry"
argument_list|)
block|,
name|NULL
block|,
name|documents_remove_document_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_REMOVE
block|}
block|,
name|NULL
block|,
name|GIMP_HELP_DOCUMENT_REMOVE
block|,
name|NULL
block|}
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/---"
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Recreate _Preview"
argument_list|)
block|,
literal|""
block|,
name|documents_recreate_preview_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_REFRESH
block|}
block|,
name|NULL
block|,
name|GIMP_HELP_DOCUMENT_REFRESH
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Reload _all Previews"
argument_list|)
block|,
literal|""
block|,
name|documents_reload_previews_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_REFRESH
block|}
block|,
name|NULL
block|,
name|GIMP_HELP_DOCUMENT_REFRESH
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Remove Dangling E_ntries"
argument_list|)
block|,
literal|""
block|,
name|documents_delete_dangling_documents_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_REFRESH
block|}
block|,
name|NULL
block|,
name|GIMP_HELP_DOCUMENT_REFRESH
block|,
name|NULL
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gint
name|n_documents_menu_entries
init|=
name|G_N_ELEMENTS
argument_list|(
name|documents_menu_entries
argument_list|)
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|documents_menu_update (GtkItemFactory * factory,gpointer data)
name|documents_menu_update
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|imagefile
operator|=
name|gimp_context_get_imagefile
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
argument_list|)
expr_stmt|;
DECL|macro|SET_SENSITIVE (menu,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|menu
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_item_factory_set_sensitive (factory, menu, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"/Open Image"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Raise or Open Image"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/File Open Dialog"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Remove Entry"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Recreate Preview"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Reload all Previews"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Remove Dangling Entries"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

