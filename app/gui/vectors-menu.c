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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemlistview.h"
end_include

begin_include
include|#
directive|include
file|"vectors-commands.h"
end_include

begin_include
include|#
directive|include
file|"vectors-menu.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_decl_stmt
DECL|variable|vectors_menu_entries
name|GimpItemFactoryEntry
name|vectors_menu_entries
index|[]
init|=
block|{
block|{
block|{
name|N_
argument_list|(
literal|"/New Path..."
argument_list|)
block|,
literal|"<control>N"
block|,
name|vectors_new_vectors_cmd_callback
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
literal|"new_path.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Raise Path"
argument_list|)
block|,
literal|"<control>F"
block|,
name|vectors_raise_vectors_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_GO_UP
block|}
block|,
name|NULL
block|,
literal|"raise_path.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Lower Path"
argument_list|)
block|,
literal|"<control>B"
block|,
name|vectors_lower_vectors_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_GO_DOWN
block|}
block|,
name|NULL
block|,
literal|"lower_path.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Duplicate Path"
argument_list|)
block|,
literal|"<control>U"
block|,
name|vectors_duplicate_vectors_cmd_callback
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
literal|"duplicate_path.html"
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
literal|"/Path to Selection"
argument_list|)
block|,
literal|"<control>S"
block|,
name|vectors_vectors_to_sel_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_SELECTION_REPLACE
block|}
block|,
name|NULL
block|,
literal|"path_to_selection.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Add to Selection"
argument_list|)
block|,
name|NULL
block|,
name|vectors_add_vectors_to_sel_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_SELECTION_ADD
block|}
block|,
name|NULL
block|,
literal|"path_to_selection.html#add"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Subtract from Selection"
argument_list|)
block|,
name|NULL
block|,
name|vectors_sub_vectors_from_sel_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_SELECTION_SUBTRACT
block|}
block|,
name|NULL
block|,
literal|"path_to_selection.html#subtract"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Intersect with Selection"
argument_list|)
block|,
name|NULL
block|,
name|vectors_intersect_vectors_with_sel_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_SELECTION_INTERSECT
block|}
block|,
name|NULL
block|,
literal|"path_to_selection.html#intersect"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Selection to Path"
argument_list|)
block|,
literal|"<control>P"
block|,
name|vectors_sel_to_vectors_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_SELECTION_TO_PATH
block|}
block|,
name|NULL
block|,
literal|"filters/sel2path.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Stroke Path"
argument_list|)
block|,
literal|"<control>T"
block|,
name|vectors_stroke_vectors_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_PATH_STROKE
block|}
block|,
name|NULL
block|,
literal|"stroke_path.html"
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
literal|"/Copy Path"
argument_list|)
block|,
literal|"<control>C"
block|,
name|vectors_copy_vectors_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_COPY
block|}
block|,
name|NULL
block|,
literal|"copy_path.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Paste Path"
argument_list|)
block|,
literal|"<control>V"
block|,
name|vectors_paste_vectors_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_PASTE
block|}
block|,
name|NULL
block|,
literal|"paste_path.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Import Path..."
argument_list|)
block|,
literal|"<control>I"
block|,
name|vectors_import_vectors_cmd_callback
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
literal|"dialogs/import_path.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Export Path..."
argument_list|)
block|,
literal|"<control>E"
block|,
name|vectors_export_vectors_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_SAVE
block|}
block|,
name|NULL
block|,
literal|"dialogs/export_path.html"
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
literal|"/Delete Path"
argument_list|)
block|,
literal|"<control>X"
block|,
name|vectors_delete_vectors_cmd_callback
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
literal|"delete_path.html"
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
literal|"/Path Tool"
argument_list|)
block|,
name|NULL
block|,
name|vectors_vectors_tool_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_TOOL_PATH
block|}
block|,
name|NULL
block|,
literal|"tools/path_tool.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Edit Path Attributes..."
argument_list|)
block|,
name|NULL
block|,
name|vectors_edit_vectors_attributes_cmd_callback
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
literal|"dialogs/edit_path_attributes.html"
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gint
name|n_vectors_menu_entries
init|=
name|G_N_ELEMENTS
argument_list|(
name|vectors_menu_entries
argument_list|)
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|vectors_menu_update (GtkItemFactory * factory,gpointer data)
name|vectors_menu_update
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|gboolean
name|mask_empty
decl_stmt|;
name|gboolean
name|global_buf
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GList
modifier|*
name|next
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|prev
init|=
name|NULL
decl_stmt|;
name|gimage
operator|=
name|GIMP_ITEM_LIST_VIEW
argument_list|(
name|data
argument_list|)
operator|->
name|gimage
expr_stmt|;
name|vectors
operator|=
name|gimp_image_get_active_vectors
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|mask_empty
operator|=
name|gimp_image_mask_is_empty
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|global_buf
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimage
operator|->
name|vectors
argument_list|)
operator|->
name|list
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
name|vectors
operator|==
operator|(
name|GimpVectors
operator|*
operator|)
name|list
operator|->
name|data
condition|)
block|{
name|prev
operator|=
name|g_list_previous
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|next
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
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
literal|"/New Path..."
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Raise Path"
argument_list|,
name|vectors
operator|&&
name|prev
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Lower Path"
argument_list|,
name|vectors
operator|&&
name|next
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Duplicate Path"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Path to Selection"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Add to Selection"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Subtract from Selection"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Intersect with Selection"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Selection to Path"
argument_list|,
operator|!
name|mask_empty
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Stroke Path"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Delete Path"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Copy Path"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Paste Path"
argument_list|,
name|global_buf
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Import Path..."
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Export Path..."
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Path Tool"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Edit Path Attributes..."
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

