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
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockbook.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpimagedock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-commands.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-menu.h"
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

begin_define
DECL|macro|ADD_TAB (path,id,type,stock_id)
define|#
directive|define
name|ADD_TAB
parameter_list|(
name|path
parameter_list|,
name|id
parameter_list|,
name|type
parameter_list|,
name|stock_id
parameter_list|)
define|\
value|{ { (path), "foo", dialogs_add_tab_cmd_callback, 0, (type), (stock_id) }, \     (id), NULL, NULL }
end_define

begin_define
DECL|macro|PREVIEW_SIZE (path,size)
define|#
directive|define
name|PREVIEW_SIZE
parameter_list|(
name|path
parameter_list|,
name|size
parameter_list|)
define|\
value|{ { (path), NULL, dialogs_preview_size_cmd_callback, \       (size), "/Preview Size/Tiny" }, NULL, NULL, NULL }
end_define

begin_decl_stmt
DECL|variable|dialogs_menu_entries
name|GimpItemFactoryEntry
name|dialogs_menu_entries
index|[]
init|=
block|{
block|{
block|{
name|N_
argument_list|(
literal|"/Select Tab"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|0
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Tool Options..."
argument_list|)
argument_list|,
literal|"gimp-tool-options"
argument_list|,
literal|"<StockItem>"
argument_list|,
name|GIMP_STOCK_TOOL_OPTIONS
argument_list|)
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/Add Tab/---"
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Layers..."
argument_list|)
argument_list|,
literal|"gimp-layer-list"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Channels..."
argument_list|)
argument_list|,
literal|"gimp-channel-list"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Paths..."
argument_list|)
argument_list|,
literal|"gimp-vectors-list"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Indexed Palette..."
argument_list|)
argument_list|,
literal|"gimp-indexed-palette"
argument_list|,
literal|"<StockItem>"
argument_list|,
name|GTK_STOCK_SELECT_COLOR
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Selection Editor..."
argument_list|)
argument_list|,
literal|"gimp-selection-editor"
argument_list|,
literal|"<StockItem>"
argument_list|,
name|GIMP_STOCK_TOOL_RECT_SELECT
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Navigation..."
argument_list|)
argument_list|,
literal|"gimp-navigation-view"
argument_list|,
literal|"<StockItem>"
argument_list|,
name|GIMP_STOCK_NAVIGATION
argument_list|)
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/Add Tab/---"
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Colors..."
argument_list|)
argument_list|,
literal|"gimp-color-editor"
argument_list|,
literal|"<StockItem>"
argument_list|,
name|GTK_STOCK_SELECT_COLOR
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Brushes..."
argument_list|)
argument_list|,
literal|"gimp-brush-grid"
argument_list|,
literal|"<StockItem>"
argument_list|,
name|GIMP_STOCK_TOOL_PAINTBRUSH
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Patterns..."
argument_list|)
argument_list|,
literal|"gimp-pattern-grid"
argument_list|,
literal|"<StockItem>"
argument_list|,
name|GIMP_STOCK_TOOL_BUCKET_FILL
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Gradients..."
argument_list|)
argument_list|,
literal|"gimp-gradient-list"
argument_list|,
literal|"<StockItem>"
argument_list|,
name|GIMP_STOCK_TOOL_BLEND
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Palettes..."
argument_list|)
argument_list|,
literal|"gimp-palette-list"
argument_list|,
literal|"<StockItem>"
argument_list|,
name|GTK_STOCK_SELECT_COLOR
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Buffers..."
argument_list|)
argument_list|,
literal|"gimp-buffer-list"
argument_list|,
literal|"<StockItem>"
argument_list|,
name|GTK_STOCK_PASTE
argument_list|)
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/Add Tab/---"
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Images..."
argument_list|)
argument_list|,
literal|"gimp-image-list"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Document History..."
argument_list|)
argument_list|,
literal|"gimp-document-history"
argument_list|,
literal|"<StockItem>"
argument_list|,
name|GTK_STOCK_OPEN
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Error Console..."
argument_list|)
argument_list|,
literal|"gimp-error-console"
argument_list|,
literal|"<StockItem>"
argument_list|,
name|GIMP_STOCK_WARNING
argument_list|)
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/Add Tab/---"
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Tools..."
argument_list|)
argument_list|,
literal|"gimp-tool-list"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
block|,
name|ADD_TAB
argument_list|(
name|N_
argument_list|(
literal|"/Add Tab/Old Paths..."
argument_list|)
argument_list|,
literal|"gimp-path-list"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Remove Tab"
argument_list|)
block|,
name|NULL
block|,
name|dialogs_remove_tab_cmd_callback
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
name|NULL
block|,
name|NULL
block|}
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/view-type-separator"
argument_list|)
block|,
name|MENU_BRANCH
argument_list|(
literal|"/Preview Size"
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Preview Size/Tiny"
argument_list|)
block|,
name|NULL
block|,
name|dialogs_preview_size_cmd_callback
block|,
name|GIMP_PREVIEW_SIZE_TINY
block|,
literal|"<RadioItem>"
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
name|PREVIEW_SIZE
argument_list|(
name|N_
argument_list|(
literal|"/Preview Size/Extra Small"
argument_list|)
argument_list|,
name|GIMP_PREVIEW_SIZE_EXTRA_SMALL
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
name|N_
argument_list|(
literal|"/Preview Size/Small"
argument_list|)
argument_list|,
name|GIMP_PREVIEW_SIZE_SMALL
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
name|N_
argument_list|(
literal|"/Preview Size/Medium"
argument_list|)
argument_list|,
name|GIMP_PREVIEW_SIZE_MEDIUM
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
name|N_
argument_list|(
literal|"/Preview Size/Large"
argument_list|)
argument_list|,
name|GIMP_PREVIEW_SIZE_LARGE
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
name|N_
argument_list|(
literal|"/Preview Size/Extra Large"
argument_list|)
argument_list|,
name|GIMP_PREVIEW_SIZE_EXTRA_LARGE
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
name|N_
argument_list|(
literal|"/Preview Size/Huge"
argument_list|)
argument_list|,
name|GIMP_PREVIEW_SIZE_HUGE
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
name|N_
argument_list|(
literal|"/Preview Size/Enormous"
argument_list|)
argument_list|,
name|GIMP_PREVIEW_SIZE_ENORMOUS
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
name|N_
argument_list|(
literal|"/Preview Size/Gigantic"
argument_list|)
argument_list|,
name|GIMP_PREVIEW_SIZE_GIGANTIC
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/View as List"
argument_list|)
block|,
name|NULL
block|,
name|dialogs_toggle_view_cmd_callback
block|,
name|GIMP_VIEW_TYPE_LIST
block|,
literal|"<RadioItem>"
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
literal|"/View as Grid"
argument_list|)
block|,
name|NULL
block|,
name|dialogs_toggle_view_cmd_callback
block|,
name|GIMP_VIEW_TYPE_GRID
block|,
literal|"/View as List"
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/image-menu-separator"
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Show Image Menu"
argument_list|)
block|,
name|NULL
block|,
name|dialogs_toggle_image_menu_cmd_callback
block|,
literal|0
block|,
literal|"<ToggleItem>"
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
literal|"/Auto Follow Active Image"
argument_list|)
block|,
name|NULL
block|,
name|dialogs_toggle_auto_cmd_callback
block|,
literal|0
block|,
literal|"<ToggleItem>"
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

begin_undef
undef|#
directive|undef
name|ADD_TAB
end_undef

begin_undef
undef|#
directive|undef
name|PREVIEW_SIZE
end_undef

begin_decl_stmt
name|gint
name|n_dialogs_menu_entries
init|=
name|G_N_ELEMENTS
argument_list|(
name|dialogs_menu_entries
argument_list|)
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|dialogs_menu_update (GtkItemFactory * factory,gpointer data)
name|dialogs_menu_update
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockbook
modifier|*
name|dockbook
decl_stmt|;
name|dockbook
operator|=
name|GIMP_DOCKBOOK
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockbook
condition|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|gint
name|page_num
decl_stmt|;
name|GimpDialogFactoryEntry
modifier|*
name|entry
decl_stmt|;
name|GimpContainerView
modifier|*
name|view
decl_stmt|;
name|GimpViewType
name|view_type
init|=
operator|-
literal|1
decl_stmt|;
name|gboolean
name|other_view_type
init|=
name|FALSE
decl_stmt|;
name|GimpPreviewSize
name|preview_size
init|=
name|GIMP_PREVIEW_SIZE_NONE
decl_stmt|;
name|page_num
operator|=
name|gtk_notebook_get_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|dockable
operator|=
operator|(
name|GimpDockable
operator|*
operator|)
name|gtk_notebook_get_nth_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
name|entry
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|,
literal|"gimp-dialog-factory-entry"
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
condition|)
block|{
name|gchar
modifier|*
name|identifier
decl_stmt|;
name|gchar
modifier|*
name|substring
init|=
name|NULL
decl_stmt|;
name|identifier
operator|=
name|g_strdup
argument_list|(
name|entry
operator|->
name|identifier
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|substring
operator|=
name|strstr
argument_list|(
name|identifier
argument_list|,
literal|"grid"
argument_list|)
operator|)
condition|)
name|view_type
operator|=
name|GIMP_VIEW_TYPE_GRID
expr_stmt|;
elseif|else
if|if
condition|(
operator|(
name|substring
operator|=
name|strstr
argument_list|(
name|identifier
argument_list|,
literal|"list"
argument_list|)
operator|)
condition|)
name|view_type
operator|=
name|GIMP_VIEW_TYPE_LIST
expr_stmt|;
if|if
condition|(
name|substring
condition|)
block|{
if|if
condition|(
name|view_type
operator|==
name|GIMP_VIEW_TYPE_GRID
condition|)
name|memcpy
argument_list|(
name|substring
argument_list|,
literal|"list"
argument_list|,
literal|4
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|view_type
operator|==
name|GIMP_VIEW_TYPE_LIST
condition|)
name|memcpy
argument_list|(
name|substring
argument_list|,
literal|"grid"
argument_list|,
literal|4
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_dialog_factory_find_entry
argument_list|(
name|dockbook
operator|->
name|dock
operator|->
name|dialog_factory
argument_list|,
name|identifier
argument_list|)
condition|)
name|other_view_type
operator|=
name|TRUE
expr_stmt|;
block|}
name|g_free
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
block|}
name|view
operator|=
name|gimp_container_view_get_by_dockable
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
condition|)
name|preview_size
operator|=
name|view
operator|->
name|preview_size
expr_stmt|;
DECL|macro|SET_ACTIVE (path,active)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|path
parameter_list|,
name|active
parameter_list|)
define|\
value|gimp_item_factory_set_active (factory, (path), (active))
DECL|macro|SET_VISIBLE (path,active)
define|#
directive|define
name|SET_VISIBLE
parameter_list|(
name|path
parameter_list|,
name|active
parameter_list|)
define|\
value|gimp_item_factory_set_visible (factory, (path), (active))
DECL|macro|SET_SENSITIVE (path,sensitive)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|path
parameter_list|,
name|sensitive
parameter_list|)
define|\
value|gimp_item_factory_set_sensitive (factory, (path), (sensitive))
name|SET_VISIBLE
argument_list|(
literal|"/view-type-separator"
argument_list|,
name|preview_size
operator|!=
name|GIMP_PREVIEW_SIZE_NONE
operator|||
name|view_type
operator|!=
operator|-
literal|1
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"/Preview Size"
argument_list|,
name|preview_size
operator|!=
name|GIMP_PREVIEW_SIZE_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview_size
operator|!=
name|GIMP_PREVIEW_SIZE_NONE
condition|)
block|{
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_PREVIEW_SIZE_GIGANTIC
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"/Preview Size/Gigantic"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_PREVIEW_SIZE_ENORMOUS
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"/Preview Size/Enormous"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_PREVIEW_SIZE_HUGE
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"/Preview Size/Huge"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_PREVIEW_SIZE_EXTRA_LARGE
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"/Preview Size/Extra Large"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_PREVIEW_SIZE_LARGE
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"/Preview Size/Large"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_PREVIEW_SIZE_MEDIUM
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"/Preview Size/Medium"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_PREVIEW_SIZE_SMALL
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"/Preview Size/Small"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_PREVIEW_SIZE_EXTRA_SMALL
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"/Preview Size/Extra Small"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_PREVIEW_SIZE_TINY
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"/Preview Size/Tiny"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
name|SET_VISIBLE
argument_list|(
literal|"/View as Grid"
argument_list|,
name|view_type
operator|!=
operator|-
literal|1
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"/View as List"
argument_list|,
name|view_type
operator|!=
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|view_type
operator|!=
operator|-
literal|1
condition|)
block|{
if|if
condition|(
name|view_type
operator|==
name|GIMP_VIEW_TYPE_LIST
condition|)
name|SET_ACTIVE
argument_list|(
literal|"/View as List"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
else|else
name|SET_ACTIVE
argument_list|(
literal|"/View as Grid"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/View as Grid"
argument_list|,
name|other_view_type
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/View as List"
argument_list|,
name|other_view_type
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|GIMP_IS_IMAGE_DOCK
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|)
condition|)
block|{
name|SET_VISIBLE
argument_list|(
literal|"/image-menu-separator"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"/Show Image Menu"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"/Auto Follow Active Image"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"/Show Image Menu"
argument_list|,
name|GIMP_IMAGE_DOCK
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|)
operator|->
name|show_image_menu
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"/Auto Follow Active Image"
argument_list|,
name|GIMP_IMAGE_DOCK
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|)
operator|->
name|auto_follow_active
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|SET_VISIBLE
argument_list|(
literal|"/image-menu-separator"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"/Show Image Menu"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"/Auto Follow Active Image"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
undef|#
directive|undef
name|SET_ACTIVE
undef|#
directive|undef
name|SET_VISIBLE
undef|#
directive|undef
name|SET_SENSITIVE
block|}
block|}
end_function

end_unit

