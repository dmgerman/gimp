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
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"templates-commands.h"
end_include

begin_include
include|#
directive|include
file|"templates-menu.h"
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
DECL|variable|templates_menu_entries
name|GimpItemFactoryEntry
name|templates_menu_entries
index|[]
init|=
block|{
block|{
block|{
name|N_
argument_list|(
literal|"/New Template..."
argument_list|)
block|,
literal|""
block|,
name|templates_new_template_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_NEW
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Duplicate Template..."
argument_list|)
block|,
literal|""
block|,
name|templates_duplicate_template_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_DUPLICATE
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Edit Template..."
argument_list|)
block|,
literal|""
block|,
name|templates_edit_template_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_EDIT
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Create Image from Template..."
argument_list|)
block|,
literal|""
block|,
name|templates_create_image_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_IMAGE
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Delete Template..."
argument_list|)
block|,
literal|""
block|,
name|templates_delete_template_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_DELETE
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gint
name|n_templates_menu_entries
init|=
name|G_N_ELEMENTS
argument_list|(
name|templates_menu_entries
argument_list|)
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|templates_menu_update (GtkItemFactory * factory,gpointer data)
name|templates_menu_update
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
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|template
operator|=
name|gimp_context_get_template
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
literal|"/New Template..."
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Duplicate Template..."
argument_list|,
name|template
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Edit Template..."
argument_list|,
name|template
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Create Image from Template..."
argument_list|,
name|template
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Delete Template..."
argument_list|,
name|template
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

