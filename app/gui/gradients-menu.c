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
file|"core/gimpdata.h"
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
file|"widgets/gimpdatafactoryview.h"
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
file|"data-commands.h"
end_include

begin_include
include|#
directive|include
file|"gradients-commands.h"
end_include

begin_include
include|#
directive|include
file|"gradients-menu.h"
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
DECL|variable|gradients_menu_entries
name|GimpItemFactoryEntry
name|gradients_menu_entries
index|[]
init|=
block|{
block|{
block|{
name|N_
argument_list|(
literal|"/_New Gradient"
argument_list|)
block|,
name|NULL
block|,
name|data_new_data_cmd_callback
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
name|GIMP_HELP_GRADIENT_NEW
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/D_uplicate Gradient"
argument_list|)
block|,
name|NULL
block|,
name|data_duplicate_data_cmd_callback
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
name|GIMP_HELP_GRADIENT_DUPLICATE
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/_Edit Gradient..."
argument_list|)
block|,
name|NULL
block|,
name|data_edit_data_cmd_callback
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
name|GIMP_HELP_GRADIENT_EDIT
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/_Delete Gradient..."
argument_list|)
block|,
name|NULL
block|,
name|data_delete_data_cmd_callback
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
name|GIMP_HELP_GRADIENT_DELETE
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
literal|"/_Refresh Gradients"
argument_list|)
block|,
name|NULL
block|,
name|data_refresh_data_cmd_callback
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
name|GIMP_HELP_GRADIENT_REFRESH
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
literal|"/Save as _POV-Ray..."
argument_list|)
block|,
name|NULL
block|,
name|gradients_save_as_pov_ray_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_SAVE_AS
block|}
block|,
name|NULL
block|,
name|GIMP_HELP_GRADIENT_SAVE_AS_POV
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gint
name|n_gradients_menu_entries
init|=
name|G_N_ELEMENTS
argument_list|(
name|gradients_menu_entries
argument_list|)
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gradients_menu_update (GtkItemFactory * factory,gpointer user_data)
name|gradients_menu_update
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|GimpData
modifier|*
name|data
init|=
name|NULL
decl_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|user_data
argument_list|)
expr_stmt|;
name|gradient
operator|=
name|gimp_context_get_gradient
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|gradient
condition|)
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|gradient
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
literal|"/Duplicate Gradient"
argument_list|,
name|gradient
operator|&&
name|GIMP_DATA_GET_CLASS
argument_list|(
name|data
argument_list|)
operator|->
name|duplicate
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Edit Gradient..."
argument_list|,
name|gradient
operator|&&
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|editor
argument_list|)
operator|->
name|data_edit_func
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Delete Gradient..."
argument_list|,
name|gradient
operator|&&
name|data
operator|->
name|writeable
operator|&&
operator|!
name|data
operator|->
name|internal
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Save as POV-Ray..."
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

