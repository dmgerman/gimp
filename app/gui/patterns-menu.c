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
file|"patterns-menu.h"
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
DECL|variable|patterns_menu_entries
name|GimpItemFactoryEntry
name|patterns_menu_entries
index|[]
init|=
block|{
if|#
directive|if
literal|0
comment|/*  disabled because they are useless now  */
block|{ { N_("/_Edit Pattern..."), NULL,       data_edit_data_cmd_callback, 0,       "<StockItem>", GIMP_STOCK_EDIT },     NULL,     GIMP_HELP_PATTERN_EDIT, NULL },    MENU_SEPARATOR ("/---"),    { { N_("/_New Pattern"), "",       data_new_data_cmd_callback, 0,       "<StockItem>", GTK_STOCK_NEW },     NULL,     GIMP_HELP_PATTERN_NEW, NULL },   { { N_("/D_uplicate Pattern"), NULL,       data_duplicate_data_cmd_callback, 0,       "<StockItem>", GIMP_STOCK_DUPLICATE },     NULL,     GIMP_HELP_PATTERN_DUPLICATE, NULL },
endif|#
directive|endif
block|{
block|{
name|N_
argument_list|(
literal|"/_Delete Pattern..."
argument_list|)
block|,
literal|""
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
name|GIMP_HELP_PATTERN_DELETE
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
literal|"/_Refresh Patterns"
argument_list|)
block|,
literal|""
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
name|GIMP_HELP_PATTERN_REFRESH
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gint
name|n_patterns_menu_entries
init|=
name|G_N_ELEMENTS
argument_list|(
name|patterns_menu_entries
argument_list|)
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|patterns_menu_update (GtkItemFactory * factory,gpointer user_data)
name|patterns_menu_update
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
name|GimpPattern
modifier|*
name|pattern
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
name|pattern
operator|=
name|gimp_context_get_pattern
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
name|pattern
condition|)
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|pattern
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
if|#
directive|if
literal|0
block|SET_SENSITIVE ("/Edit Pattern...", 		 pattern&& GIMP_DATA_FACTORY_VIEW (editor)->data_edit_func);   SET_SENSITIVE ("/Duplicate Pattern", 		 pattern&& GIMP_DATA_GET_CLASS (data)->duplicate);
endif|#
directive|endif
name|SET_SENSITIVE
argument_list|(
literal|"/Delete Pattern..."
argument_list|,
name|pattern
operator|&&
name|data
operator|->
name|deletable
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

