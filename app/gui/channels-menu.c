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
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcomponenteditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemtreeview.h"
end_include

begin_include
include|#
directive|include
file|"channels-commands.h"
end_include

begin_include
include|#
directive|include
file|"channels-menu.h"
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
DECL|variable|channels_menu_entries
name|GimpItemFactoryEntry
name|channels_menu_entries
index|[]
init|=
block|{
block|{
block|{
name|N_
argument_list|(
literal|"/New Channel..."
argument_list|)
block|,
literal|"<control>N"
block|,
name|channels_new_channel_cmd_callback
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
literal|"dialogs/new_channel.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Raise Channel"
argument_list|)
block|,
literal|"<control>F"
block|,
name|channels_raise_channel_cmd_callback
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
literal|"raise_channel.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Lower Channel"
argument_list|)
block|,
literal|"<control>B"
block|,
name|channels_lower_channel_cmd_callback
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
literal|"lower_channel.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Duplicate Channel"
argument_list|)
block|,
literal|"<control>C"
block|,
name|channels_duplicate_channel_cmd_callback
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
literal|"duplicate_channel.html"
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
literal|"/Channel to Selection"
argument_list|)
block|,
literal|"<control>S"
block|,
name|channels_channel_to_sel_cmd_callback
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
literal|"channel_to_selection.html"
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
name|channels_add_channel_to_sel_cmd_callback
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
literal|"channel_to_selection.html#add"
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
name|channels_sub_channel_from_sel_cmd_callback
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
literal|"channel_to_selection.html#subtract"
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
name|channels_intersect_channel_with_sel_cmd_callback
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
literal|"channel_to_selection.html#intersect"
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
literal|"/Delete Channel"
argument_list|)
block|,
literal|"<control>X"
block|,
name|channels_delete_channel_cmd_callback
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
literal|"delete_channel.html"
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
literal|"/Edit Channel Attributes..."
argument_list|)
block|,
name|NULL
block|,
name|channels_edit_channel_attributes_cmd_callback
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
literal|"dialogs/edit_channel_attributes.html"
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gint
name|n_channels_menu_entries
init|=
name|G_N_ELEMENTS
argument_list|(
name|channels_menu_entries
argument_list|)
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|channels_menu_update (GtkItemFactory * factory,gpointer data)
name|channels_menu_update
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
name|GimpChannel
modifier|*
name|channel
init|=
name|NULL
decl_stmt|;
name|gboolean
name|fs
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|component
init|=
name|FALSE
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
if|if
condition|(
name|GIMP_IS_COMPONENT_EDITOR
argument_list|(
name|data
argument_list|)
condition|)
block|{
name|gimage
operator|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|data
argument_list|)
operator|->
name|gimage
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
if|if
condition|(
name|GIMP_COMPONENT_EDITOR
argument_list|(
name|data
argument_list|)
operator|->
name|clicked_component
operator|!=
operator|-
literal|1
condition|)
name|component
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
else|else
block|{
name|gimage
operator|=
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
operator|->
name|gimage
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|channel
operator|=
name|gimp_image_get_active_channel
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimage
operator|->
name|channels
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
name|channel
operator|==
operator|(
name|GimpChannel
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
block|}
block|}
if|if
condition|(
name|gimage
condition|)
name|fs
operator|=
operator|(
name|gimp_image_floating_sel
argument_list|(
name|gimage
argument_list|)
operator|!=
name|NULL
operator|)
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
literal|"/New Channel..."
argument_list|,
operator|!
name|fs
operator|&&
name|gimage
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Raise Channel"
argument_list|,
operator|!
name|fs
operator|&&
name|channel
operator|&&
name|prev
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Lower Channel"
argument_list|,
operator|!
name|fs
operator|&&
name|channel
operator|&&
name|next
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Duplicate Channel"
argument_list|,
operator|!
name|fs
operator|&&
operator|(
name|channel
operator|||
name|component
operator|)
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Channel to Selection"
argument_list|,
operator|!
name|fs
operator|&&
operator|(
name|channel
operator|||
name|component
operator|)
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Add to Selection"
argument_list|,
operator|!
name|fs
operator|&&
operator|(
name|channel
operator|||
name|component
operator|)
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Subtract from Selection"
argument_list|,
operator|!
name|fs
operator|&&
operator|(
name|channel
operator|||
name|component
operator|)
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Intersect with Selection"
argument_list|,
operator|!
name|fs
operator|&&
operator|(
name|channel
operator|||
name|component
operator|)
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Delete Channel"
argument_list|,
operator|!
name|fs
operator|&&
name|channel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Edit Channel Attributes..."
argument_list|,
operator|!
name|fs
operator|&&
name|channel
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

