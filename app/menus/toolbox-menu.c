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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-ins.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"debug-commands.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-commands.h"
end_include

begin_include
include|#
directive|include
file|"file-commands.h"
end_include

begin_include
include|#
directive|include
file|"help-commands.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-menus.h"
end_include

begin_include
include|#
directive|include
file|"test-commands.h"
end_include

begin_include
include|#
directive|include
file|"toolbox-menu.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|toolbox_menu_entries
name|GimpItemFactoryEntry
name|toolbox_menu_entries
index|[]
init|=
block|{
comment|/*<Toolbox>/File  */
name|MENU_BRANCH
argument_list|(
name|N_
argument_list|(
literal|"/_File"
argument_list|)
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/New..."
argument_list|)
block|,
literal|"<control>N"
block|,
name|file_new_cmd_callback
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
literal|"file/dialogs/file_new.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Open..."
argument_list|)
block|,
literal|"<control>O"
block|,
name|file_open_cmd_callback
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
literal|"file/dialogs/file_open.html"
block|,
name|NULL
block|}
block|,
comment|/*<Toolbox>/File/Open Recent  */
block|{
block|{
name|N_
argument_list|(
literal|"/File/Open Recent/(None)"
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
comment|/*<Toolbox>/File/Acquire  */
name|MENU_BRANCH
argument_list|(
name|N_
argument_list|(
literal|"/File/Acquire"
argument_list|)
argument_list|)
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/File/---"
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Preferences..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_toplevel_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_PREFERENCES
block|}
block|,
literal|"gimp-preferences-dialog"
block|,
literal|"file/dialogs/preferences/preferences.html"
block|,
name|NULL
block|}
block|,
comment|/*<Toolbox>/File/Dialogs  */
block|{
block|{
name|N_
argument_list|(
literal|"/File/Dialogs/Layers, Channels& Paths..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_lc_cmd_callback
block|,
literal|0
block|}
block|,
name|NULL
block|,
literal|"file/dialogs/layers_and_channels.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Dialogs/Brushes, Patterns& Stuff..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_stuff_cmd_callback
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
block|{
block|{
name|N_
argument_list|(
literal|"/File/Dialogs/Tool Options..."
argument_list|)
block|,
literal|"<control><shift>T"
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_TOOL_OPTIONS
block|}
block|,
literal|"gimp-tool-options"
block|,
literal|"file/dialogs/tool_options.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Dialogs/Device Status..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_toplevel_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_DEVICE_STATUS
block|}
block|,
literal|"gimp-device-status-dialog"
block|,
literal|"file/dialogs/device_status.html"
block|,
name|NULL
block|}
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/File/Dialogs/---"
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Dialogs/Layers..."
argument_list|)
block|,
literal|"<control>L"
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_LAYERS
block|}
block|,
literal|"gimp-layer-list"
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
literal|"/File/Dialogs/Channels..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_CHANNELS
block|}
block|,
literal|"gimp-channel-list"
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
literal|"/File/Dialogs/Paths..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_PATHS
block|}
block|,
literal|"gimp-vectors-list"
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
literal|"/File/Dialogs/Indexed Palette..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_SELECT_COLOR
block|}
block|,
literal|"gimp-indexed-palette"
block|,
literal|"file/dialogs/indexed_palette.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Dialogs/Selection Editor..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_TOOL_RECT_SELECT
block|}
block|,
literal|"gimp-selection-editor"
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
literal|"/File/Dialogs/Navigation..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_NAVIGATION
block|}
block|,
literal|"gimp-navigation-view"
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
literal|"/File/Dialogs/Undo History..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_UNDO
block|}
block|,
literal|"gimp-undo-history"
block|,
name|NULL
block|,
name|NULL
block|}
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/File/Dialogs/---"
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Dialogs/Colors..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_SELECT_COLOR
block|}
block|,
literal|"gimp-color-editor"
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
literal|"/File/Dialogs/Brushes..."
argument_list|)
block|,
literal|"<control><shift>B"
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_TOOL_PAINTBRUSH
block|}
block|,
literal|"gimp-brush-grid"
block|,
literal|"file/dialogs/brush_selection.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Dialogs/Patterns..."
argument_list|)
block|,
literal|"<control><shift>P"
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_TOOL_BUCKET_FILL
block|}
block|,
literal|"gimp-pattern-grid"
block|,
literal|"file/dialogs/pattern_selection.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Dialogs/Gradients..."
argument_list|)
block|,
literal|"<control>G"
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_TOOL_BLEND
block|}
block|,
literal|"gimp-gradient-list"
block|,
literal|"file/dialogs/gradient_selection.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Dialogs/Palettes..."
argument_list|)
block|,
literal|"<control>P"
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_SELECT_COLOR
block|}
block|,
literal|"gimp-palette-list"
block|,
literal|"file/dialogs/palette_selection.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Dialogs/Fonts..."
argument_list|)
block|,
literal|"<control>P"
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_SELECT_FONT
block|}
block|,
literal|"gimp-font-list"
block|,
literal|"file/dialogs/font_selection.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Dialogs/Buffers..."
argument_list|)
block|,
literal|"foo"
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_PASTE
block|}
block|,
literal|"gimp-buffer-list"
block|,
name|NULL
block|,
name|NULL
block|}
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/File/Dialogs/---"
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Dialogs/Images..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_IMAGES
block|}
block|,
literal|"gimp-image-list"
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
literal|"/File/Dialogs/Document History..."
argument_list|)
block|,
literal|"foo"
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_OPEN
block|}
block|,
literal|"gimp-document-list"
block|,
literal|"file/dialogs/document_index.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Dialogs/Error Console..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_dockable_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_WARNING
block|}
block|,
literal|"gimp-error-console"
block|,
literal|"file/dialogs/error_console.html"
block|,
name|NULL
block|}
block|,
ifdef|#
directive|ifdef
name|ENABLE_DEBUG_ENTRIES
block|{
block|{
literal|"/File/Debug/Test Dialogs/Multi List..."
block|,
name|NULL
block|,
name|test_multi_container_list_view_cmd_callback
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
block|{
block|{
literal|"/File/Debug/Test Dialogs/Multi Grid..."
block|,
name|NULL
block|,
name|test_multi_container_grid_view_cmd_callback
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
block|{
block|{
literal|"/File/Debug/Mem Profile"
block|,
name|NULL
block|,
name|debug_mem_profile_cmd_callback
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
block|{
block|{
literal|"/File/Debug/Dump Items"
block|,
name|NULL
block|,
name|debug_dump_menus_cmd_callback
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
block|{
block|{
literal|"/File/Debug/Serialize User Context"
block|,
name|NULL
block|,
name|test_serialize_context_cmd_callback
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
block|{
block|{
literal|"/File/Debug/Deserialize User Context"
block|,
name|NULL
block|,
name|test_deserialize_context_cmd_callback
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
endif|#
directive|endif
name|MENU_SEPARATOR
argument_list|(
literal|"/File/---"
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/File/Quit"
argument_list|)
block|,
literal|"<control>Q"
block|,
name|file_quit_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_QUIT
block|}
block|,
name|NULL
block|,
literal|"file/quit.html"
block|,
name|NULL
block|}
block|,
comment|/*<Toolbox>/Xtns  */
name|MENU_BRANCH
argument_list|(
name|N_
argument_list|(
literal|"/_Xtns"
argument_list|)
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Xtns/Module Browser..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_toplevel_cmd_callback
block|,
literal|0
block|}
block|,
literal|"gimp-module-browser-dialog"
block|,
literal|"dialogs/module_browser.html"
block|,
name|NULL
block|}
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/Xtns/---"
argument_list|)
block|,
comment|/*<Toolbox>/Help  */
name|MENU_BRANCH
argument_list|(
name|N_
argument_list|(
literal|"/_Help"
argument_list|)
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Help/Help..."
argument_list|)
block|,
literal|"F1"
block|,
name|help_help_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_HELP
block|}
block|,
name|NULL
block|,
literal|"help/dialogs/help.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Help/Context Help..."
argument_list|)
block|,
literal|"<shift>F1"
block|,
name|help_context_help_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GTK_STOCK_HELP
block|}
block|,
name|NULL
block|,
literal|"help/context_help.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Help/Tip of the Day..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_toplevel_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_INFO
block|}
block|,
literal|"gimp-tips-dialog"
block|,
literal|"help/dialogs/tip_of_the_day.html"
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Help/About..."
argument_list|)
block|,
name|NULL
block|,
name|dialogs_create_toplevel_cmd_callback
block|,
literal|0
block|,
literal|"<StockItem>"
block|,
name|GIMP_STOCK_WILBER
block|}
block|,
literal|"gimp-about-dialog"
block|,
literal|"help/dialogs/about.html"
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gint
name|n_toolbox_menu_entries
init|=
name|G_N_ELEMENTS
argument_list|(
name|toolbox_menu_entries
argument_list|)
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|toolbox_menu_setup (GimpItemFactory * factory)
name|toolbox_menu_setup
parameter_list|(
name|GimpItemFactory
modifier|*
name|factory
parameter_list|)
block|{
specifier|static
name|gchar
modifier|*
name|reorder_subsubmenus
index|[]
init|=
block|{
literal|"/Xtns"
block|}
decl_stmt|;
name|GtkWidget
modifier|*
name|menu_item
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|pos
decl_stmt|;
name|menus_last_opened_add
argument_list|(
name|factory
argument_list|,
name|factory
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|plug_in_menus_create
argument_list|(
name|factory
argument_list|,
name|factory
operator|->
name|gimp
operator|->
name|plug_in_proc_defs
argument_list|)
expr_stmt|;
comment|/*  Move all menu items under "<Toolbox>/Xtns" which are not submenus or    *  separators to the top of the menu    */
name|pos
operator|=
literal|1
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
literal|"/Xtns/Module Browser..."
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu_item
operator|&&
name|menu_item
operator|->
name|parent
operator|&&
name|GTK_IS_MENU
argument_list|(
name|menu_item
operator|->
name|parent
argument_list|)
condition|)
block|{
name|menu
operator|=
name|menu_item
operator|->
name|parent
expr_stmt|;
for|for
control|(
name|list
operator|=
name|g_list_nth
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
operator|->
name|children
argument_list|,
name|pos
argument_list|)
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
name|menu_item
operator|=
name|GTK_WIDGET
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_MENU_ITEM
argument_list|(
name|menu_item
argument_list|)
operator|->
name|submenu
operator|&&
name|GTK_IS_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|menu_item
argument_list|)
operator|->
name|child
argument_list|)
condition|)
block|{
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
name|pos
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_nth
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
operator|->
name|children
argument_list|,
name|pos
argument_list|)
expr_stmt|;
name|pos
operator|++
expr_stmt|;
block|}
block|}
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|reorder_subsubmenus
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|menu
operator|=
name|gtk_item_factory_get_widget
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
name|reorder_subsubmenus
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu
operator|&&
name|GTK_IS_MENU
argument_list|(
name|menu
argument_list|)
condition|)
block|{
for|for
control|(
name|list
operator|=
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
operator|->
name|children
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
name|GtkMenuItem
modifier|*
name|menu_item
decl_stmt|;
name|menu_item
operator|=
name|GTK_MENU_ITEM
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu_item
operator|->
name|submenu
condition|)
name|menus_filters_subdirs_to_top
argument_list|(
name|GTK_MENU
argument_list|(
name|menu_item
operator|->
name|submenu
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

end_unit

