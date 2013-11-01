begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2006 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpui.h"
end_include

begin_include
include|#
directive|include
file|"imap_about.h"
end_include

begin_include
include|#
directive|include
file|"imap_circle.h"
end_include

begin_include
include|#
directive|include
file|"imap_file.h"
end_include

begin_include
include|#
directive|include
file|"imap_grid.h"
end_include

begin_include
include|#
directive|include
file|"imap_main.h"
end_include

begin_include
include|#
directive|include
file|"imap_menu.h"
end_include

begin_include
include|#
directive|include
file|"imap_menu_funcs.h"
end_include

begin_include
include|#
directive|include
file|"imap_polygon.h"
end_include

begin_include
include|#
directive|include
file|"imap_preferences.h"
end_include

begin_include
include|#
directive|include
file|"imap_rectangle.h"
end_include

begin_include
include|#
directive|include
file|"imap_settings.h"
end_include

begin_include
include|#
directive|include
file|"imap_stock.h"
end_include

begin_include
include|#
directive|include
file|"imap_source.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
DECL|variable|_menu
specifier|static
name|Menu_t
name|_menu
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ui_manager
specifier|static
name|GtkUIManager
modifier|*
name|ui_manager
decl_stmt|;
end_decl_stmt

begin_function
name|GtkWidget
modifier|*
DECL|function|menu_get_widget (const gchar * path)
name|menu_get_widget
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|)
block|{
return|return
name|gtk_ui_manager_get_widget
argument_list|(
name|ui_manager
argument_list|,
name|path
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|set_sensitive (const gchar * path,gboolean sensitive)
name|set_sensitive
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
block|{
name|GtkAction
modifier|*
name|action
init|=
name|gtk_ui_manager_get_action
argument_list|(
name|ui_manager
argument_list|,
name|path
argument_list|)
decl_stmt|;
name|g_object_set
argument_list|(
name|action
argument_list|,
literal|"sensitive"
argument_list|,
name|sensitive
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|menu_mru (GtkWidget * widget,gpointer data)
name|menu_mru
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|MRU_t
modifier|*
name|mru
init|=
name|get_mru
argument_list|()
decl_stmt|;
name|char
modifier|*
name|filename
init|=
operator|(
name|char
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
condition|)
block|{
name|load
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|do_file_error_dialog
argument_list|(
name|_
argument_list|(
literal|"Error opening file"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|mru_remove
argument_list|(
name|mru
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|menu_build_mru_items
argument_list|(
name|mru
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|menu_set_zoom_sensitivity (gint factor)
name|menu_set_zoom_sensitivity
parameter_list|(
name|gint
name|factor
parameter_list|)
block|{
name|set_sensitive
argument_list|(
literal|"/MainMenu/ViewMenu/ZoomIn"
argument_list|,
name|factor
operator|<
literal|8
argument_list|)
expr_stmt|;
name|set_sensitive
argument_list|(
literal|"/MainMenu/ViewMenu/ZoomOut"
argument_list|,
name|factor
operator|>
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menu_set_zoom (gint factor)
name|menu_set_zoom
parameter_list|(
name|gint
name|factor
parameter_list|)
block|{
name|menu_set_zoom_sensitivity
argument_list|(
name|factor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menu_shapes_selected (gint count)
name|menu_shapes_selected
parameter_list|(
name|gint
name|count
parameter_list|)
block|{
name|gboolean
name|sensitive
init|=
operator|(
name|count
operator|>
literal|0
operator|)
decl_stmt|;
name|set_sensitive
argument_list|(
literal|"/MainMenu/EditMenu/Cut"
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|set_sensitive
argument_list|(
literal|"/MainMenu/EditMenu/Copy"
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|set_sensitive
argument_list|(
literal|"/MainMenu/EditMenu/Clear"
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|set_sensitive
argument_list|(
literal|"/MainMenu/EditMenu/EditAreaInfo"
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|set_sensitive
argument_list|(
literal|"/MainMenu/EditMenu/DeselectAll"
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|command_list_changed (Command_t * command,gpointer data)
name|command_list_changed
parameter_list|(
name|Command_t
modifier|*
name|command
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|action
operator|=
name|gtk_ui_manager_get_action
argument_list|(
name|ui_manager
argument_list|,
literal|"/MainMenu/EditMenu/Undo"
argument_list|)
expr_stmt|;
name|label
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"_Undo %s"
argument_list|)
argument_list|,
name|command
operator|&&
name|command
operator|->
name|name
condition|?
name|command
operator|->
name|name
else|:
literal|""
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|action
argument_list|,
literal|"label"
argument_list|,
name|label
argument_list|,
literal|"sensitive"
argument_list|,
name|command
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|command
operator|=
name|command_list_get_redo_command
argument_list|()
expr_stmt|;
name|action
operator|=
name|gtk_ui_manager_get_action
argument_list|(
name|ui_manager
argument_list|,
literal|"/MainMenu/EditMenu/Redo"
argument_list|)
expr_stmt|;
name|label
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"_Redo %s"
argument_list|)
argument_list|,
name|command
operator|&&
name|command
operator|->
name|name
condition|?
name|command
operator|->
name|name
else|:
literal|""
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|action
argument_list|,
literal|"label"
argument_list|,
name|label
argument_list|,
literal|"sensitive"
argument_list|,
name|command
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|paste_buffer_added (Object_t * obj,gpointer data)
name|paste_buffer_added
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|set_sensitive
argument_list|(
literal|"/MainMenu/EditMenu/Paste"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|paste_buffer_removed (Object_t * obj,gpointer data)
name|paste_buffer_removed
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|set_sensitive
argument_list|(
literal|"/MainMenu/EditMenu/Paste"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Normal items */
end_comment

begin_decl_stmt
DECL|variable|entries
specifier|static
specifier|const
name|GtkActionEntry
name|entries
index|[]
init|=
block|{
block|{
literal|"FileMenu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_File"
argument_list|)
block|}
block|,
block|{
literal|"Open"
block|,
name|GTK_STOCK_OPEN
block|,
name|N_
argument_list|(
literal|"_Open..."
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Open"
argument_list|)
block|,
name|do_file_open_dialog
block|}
block|,
block|{
literal|"Save"
block|,
name|GTK_STOCK_SAVE
block|,
name|N_
argument_list|(
literal|"_Save..."
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Save"
argument_list|)
block|,
name|save
block|}
block|,
block|{
literal|"SaveAs"
block|,
name|GTK_STOCK_SAVE_AS
block|,
name|N_
argument_list|(
literal|"Save _As..."
argument_list|)
block|,
literal|"<shift><control>S"
block|,
name|NULL
block|,
name|do_file_save_as_dialog
block|}
block|,
block|{
literal|"Close"
block|,
name|GTK_STOCK_CLOSE
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|do_close
block|}
block|,
block|{
literal|"Quit"
block|,
name|GTK_STOCK_QUIT
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|do_quit
block|}
block|,
block|{
literal|"EditMenu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Edit"
argument_list|)
block|}
block|,
block|{
literal|"Undo"
block|,
name|GTK_STOCK_UNDO
block|,
name|NULL
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Undo"
argument_list|)
block|,
name|do_undo
block|}
block|,
block|{
literal|"Redo"
block|,
name|GTK_STOCK_REDO
block|,
name|NULL
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Redo"
argument_list|)
block|,
name|do_redo
block|}
block|,
block|{
literal|"Cut"
block|,
name|GTK_STOCK_CUT
block|,
name|NULL
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Cut"
argument_list|)
block|,
name|do_cut
block|}
block|,
block|{
literal|"Copy"
block|,
name|GTK_STOCK_COPY
block|,
name|NULL
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Copy"
argument_list|)
block|,
name|do_copy
block|}
block|,
block|{
literal|"Paste"
block|,
name|GTK_STOCK_PASTE
block|,
name|NULL
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Paste"
argument_list|)
block|,
name|do_paste
block|}
block|,
block|{
literal|"Clear"
block|,
name|GTK_STOCK_DELETE
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Delete"
argument_list|)
block|,
name|NULL
block|,
name|do_clear
block|}
block|,
block|{
literal|"SelectAll"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Select _All"
argument_list|)
block|,
literal|"<control>A"
block|,
name|NULL
block|,
name|do_select_all
block|}
block|,
block|{
literal|"DeselectAll"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"D_eselect All"
argument_list|)
block|,
literal|"<shift><control>A"
block|,
name|NULL
block|,
name|do_deselect_all
block|}
block|,
block|{
literal|"EditAreaInfo"
block|,
name|GTK_STOCK_EDIT
block|,
name|N_
argument_list|(
literal|"Edit Area _Info..."
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Edit selected area info"
argument_list|)
block|,
name|do_edit_selected_shape
block|}
block|,
block|{
literal|"Preferences"
block|,
name|GTK_STOCK_PREFERENCES
block|,
name|NULL
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Preferences"
argument_list|)
block|,
name|do_preferences_dialog
block|}
block|,
block|{
literal|"MoveToFront"
block|,
name|IMAP_STOCK_TO_FRONT
block|,
literal|""
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Move Area to Front"
argument_list|)
block|,
name|do_move_to_front
block|}
block|,
block|{
literal|"SendToBack"
block|,
name|IMAP_STOCK_TO_BACK
block|,
literal|""
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Move Area to Bottom"
argument_list|)
block|,
name|do_send_to_back
block|}
block|,
block|{
literal|"DeleteArea"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Delete Area"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
literal|"MoveUp"
block|,
name|GTK_STOCK_GO_UP
block|,
name|N_
argument_list|(
literal|"Move Up"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
literal|"MoveDown"
block|,
name|GTK_STOCK_GO_DOWN
block|,
name|N_
argument_list|(
literal|"Move Down"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
literal|"InsertPoint"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Insert Point"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|polygon_insert_point
block|}
block|,
block|{
literal|"DeletePoint"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Delete Point"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|polygon_delete_point
block|}
block|,
block|{
literal|"ViewMenu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_View"
argument_list|)
block|}
block|,
block|{
literal|"Source"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Source..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|do_source_dialog
block|}
block|,
block|{
literal|"ZoomIn"
block|,
name|GTK_STOCK_ZOOM_IN
block|,
name|NULL
block|,
literal|"plus"
block|,
name|N_
argument_list|(
literal|"Zoom in"
argument_list|)
block|,
name|do_zoom_in
block|}
block|,
block|{
literal|"ZoomOut"
block|,
name|GTK_STOCK_ZOOM_OUT
block|,
name|NULL
block|,
literal|"minus"
block|,
name|N_
argument_list|(
literal|"Zoom out"
argument_list|)
block|,
name|do_zoom_out
block|}
block|,
block|{
literal|"ZoomToMenu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Zoom To"
argument_list|)
block|}
block|,
block|{
literal|"MappingMenu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Mapping"
argument_list|)
block|}
block|,
block|{
literal|"EditMapInfo"
block|,
name|GTK_STOCK_INFO
block|,
name|N_
argument_list|(
literal|"Edit Map Info..."
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Edit Map Info"
argument_list|)
block|,
name|do_settings_dialog
block|}
block|,
block|{
literal|"ToolsMenu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Tools"
argument_list|)
block|}
block|,
block|{
literal|"GridSettings"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Grid Settings..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|do_grid_settings_dialog
block|}
block|,
block|{
literal|"UseGimpGuides"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Use GIMP Guides..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|do_use_gimp_guides_dialog
block|}
block|,
block|{
literal|"CreateGuides"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Create Guides..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|do_create_guides_dialog
block|}
block|,
block|{
literal|"HelpMenu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Help"
argument_list|)
block|}
block|,
block|{
literal|"Contents"
block|,
name|GTK_STOCK_HELP
block|,
name|N_
argument_list|(
literal|"_Contents"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|imap_help
block|}
block|,
block|{
literal|"About"
block|,
name|GTK_STOCK_ABOUT
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|do_about_dialog
block|}
block|,
block|{
literal|"ZoomMenu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Zoom"
argument_list|)
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Toggle items */
end_comment

begin_decl_stmt
DECL|variable|toggle_entries
specifier|static
specifier|const
name|GtkToggleActionEntry
name|toggle_entries
index|[]
init|=
block|{
block|{
literal|"AreaList"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Area List"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|TRUE
block|}
block|,
block|{
literal|"Grid"
block|,
name|GIMP_STOCK_GRID
block|,
name|N_
argument_list|(
literal|"_Grid"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Grid"
argument_list|)
block|,
name|toggle_grid
block|,
name|FALSE
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_entries
specifier|static
specifier|const
name|GtkRadioActionEntry
name|color_entries
index|[]
init|=
block|{
block|{
literal|"Color"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Color"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|0
block|}
block|,
block|{
literal|"Gray"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Gray"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|1
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|mapping_entries
specifier|static
specifier|const
name|GtkRadioActionEntry
name|mapping_entries
index|[]
init|=
block|{
block|{
literal|"Arrow"
block|,
name|GIMP_STOCK_CURSOR
block|,
name|N_
argument_list|(
literal|"Arrow"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Select existing area"
argument_list|)
block|,
literal|0
block|}
block|,
block|{
literal|"Rectangle"
block|,
name|IMAP_STOCK_RECTANGLE
block|,
name|N_
argument_list|(
literal|"Rectangle"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Define Rectangle area"
argument_list|)
block|,
literal|1
block|}
block|,
block|{
literal|"Circle"
block|,
name|IMAP_STOCK_CIRCLE
block|,
name|N_
argument_list|(
literal|"Circle"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Define Circle/Oval area"
argument_list|)
block|,
literal|2
block|}
block|,
block|{
literal|"Polygon"
block|,
name|IMAP_STOCK_POLYGON
block|,
name|N_
argument_list|(
literal|"Polygon"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Define Polygon area"
argument_list|)
block|,
literal|3
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|zoom_entries
specifier|static
specifier|const
name|GtkRadioActionEntry
name|zoom_entries
index|[]
init|=
block|{
block|{
literal|"Zoom1:1"
block|,
name|NULL
block|,
literal|"1:1"
block|,
name|NULL
block|,
name|NULL
block|,
literal|0
block|}
block|,
block|{
literal|"Zoom1:2"
block|,
name|NULL
block|,
literal|"1:2"
block|,
name|NULL
block|,
name|NULL
block|,
literal|1
block|}
block|,
block|{
literal|"Zoom1:3"
block|,
name|NULL
block|,
literal|"1:3"
block|,
name|NULL
block|,
name|NULL
block|,
literal|2
block|}
block|,
block|{
literal|"Zoom1:4"
block|,
name|NULL
block|,
literal|"1:4"
block|,
name|NULL
block|,
name|NULL
block|,
literal|3
block|}
block|,
block|{
literal|"Zoom1:5"
block|,
name|NULL
block|,
literal|"1:5"
block|,
name|NULL
block|,
name|NULL
block|,
literal|4
block|}
block|,
block|{
literal|"Zoom1:6"
block|,
name|NULL
block|,
literal|"1:6"
block|,
name|NULL
block|,
name|NULL
block|,
literal|5
block|}
block|,
block|{
literal|"Zoom1:7"
block|,
name|NULL
block|,
literal|"1:7"
block|,
name|NULL
block|,
name|NULL
block|,
literal|6
block|}
block|,
block|{
literal|"Zoom1:8"
block|,
name|NULL
block|,
literal|"1:8"
block|,
name|NULL
block|,
name|NULL
block|,
literal|7
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ui_description
specifier|static
specifier|const
name|gchar
name|ui_description
index|[]
init|=
literal|"<ui>"
literal|"<menubar name='MainMenu'>"
literal|"<menu action='FileMenu'>"
literal|"<menuitem action='Open'/>"
literal|"<menuitem action='Save'/>"
literal|"<menuitem action='SaveAs'/>"
literal|"<separator/>"
literal|"<menuitem action='Close'/>"
literal|"<menuitem action='Quit'/>"
literal|"</menu>"
literal|"<menu action='EditMenu'>"
literal|"<menuitem action='Undo'/>"
literal|"<menuitem action='Redo'/>"
literal|"<menuitem action='Cut'/>"
literal|"<menuitem action='Copy'/>"
literal|"<menuitem action='Paste'/>"
literal|"<menuitem action='Clear'/>"
literal|"<separator/>"
literal|"<menuitem action='SelectAll'/>"
literal|"<menuitem action='DeselectAll'/>"
literal|"<separator/>"
literal|"<menuitem action='EditAreaInfo'/>"
literal|"<separator/>"
literal|"<menuitem action='Preferences'/>"
literal|"</menu>"
literal|"<menu action='ViewMenu'>"
literal|"<menuitem action='AreaList'/>"
literal|"<menuitem action='Source'/>"
literal|"<separator/>"
literal|"<menuitem action='Color'/>"
literal|"<menuitem action='Gray'/>"
literal|"<separator/>"
literal|"<menuitem action='ZoomIn'/>"
literal|"<menuitem action='ZoomOut'/>"
literal|"<menu action='ZoomToMenu'>"
literal|"<menuitem action='Zoom1:1'/>"
literal|"<menuitem action='Zoom1:2'/>"
literal|"<menuitem action='Zoom1:3'/>"
literal|"<menuitem action='Zoom1:4'/>"
literal|"<menuitem action='Zoom1:5'/>"
literal|"<menuitem action='Zoom1:6'/>"
literal|"<menuitem action='Zoom1:7'/>"
literal|"<menuitem action='Zoom1:8'/>"
literal|"</menu>"
literal|"</menu>"
literal|"<menu action='MappingMenu'>"
literal|"<menuitem action='Arrow'/>"
literal|"<menuitem action='Rectangle'/>"
literal|"<menuitem action='Circle'/>"
literal|"<menuitem action='Polygon'/>"
literal|"<separator/>"
literal|"<menuitem action='EditMapInfo'/>"
literal|"</menu>"
literal|"<menu action='ToolsMenu'>"
literal|"<menuitem action='Grid'/>"
literal|"<menuitem action='GridSettings'/>"
literal|"<separator/>"
literal|"<menuitem action='UseGimpGuides'/>"
literal|"<menuitem action='CreateGuides'/>"
literal|"</menu>"
literal|"<menu action='HelpMenu'>"
literal|"<menuitem action='Contents'/>"
literal|"<menuitem action='About'/>"
literal|"</menu>"
literal|"</menubar>"
literal|""
literal|"<popup name='PopupMenu'>"
literal|"<menuitem action='EditMapInfo'/>"
literal|"<menu action='ToolsMenu'>"
literal|"<menuitem action='Arrow'/>"
literal|"<menuitem action='Rectangle'/>"
literal|"<menuitem action='Circle'/>"
literal|"<menuitem action='Polygon'/>"
literal|"</menu>"
literal|"<menu action='ZoomMenu'>"
literal|"<menuitem action='ZoomIn'/>"
literal|"<menuitem action='ZoomOut'/>"
literal|"</menu>"
literal|"<menuitem action='Grid'/>"
literal|"<menuitem action='GridSettings'/>"
literal|"<menuitem action='CreateGuides'/>"
literal|"<menuitem action='Paste'/>"
literal|"</popup>"
literal|""
literal|"<popup name='ObjectPopupMenu'>"
literal|"<menuitem action='EditAreaInfo'/>"
literal|"<menuitem action='DeleteArea'/>"
literal|"<menuitem action='MoveUp'/>"
literal|"<menuitem action='MoveDown'/>"
literal|"<menuitem action='Cut'/>"
literal|"<menuitem action='Copy'/>"
literal|"</popup>"
literal|""
literal|"<popup name='PolygonPopupMenu'>"
literal|"<menuitem action='InsertPoint'/>"
literal|"<menuitem action='DeletePoint'/>"
literal|"<menuitem action='EditAreaInfo'/>"
literal|"<menuitem action='DeleteArea'/>"
literal|"<menuitem action='MoveUp'/>"
literal|"<menuitem action='MoveDown'/>"
literal|"<menuitem action='Cut'/>"
literal|"<menuitem action='Copy'/>"
literal|"</popup>"
literal|""
literal|"<toolbar name='Toolbar'>"
literal|"<toolitem action='Open'/>"
literal|"<toolitem action='Save'/>"
literal|"<separator/>"
literal|"<toolitem action='Preferences'/>"
literal|"<separator/>"
literal|"<toolitem action='Undo'/>"
literal|"<toolitem action='Redo'/>"
literal|"<separator/>"
literal|"<toolitem action='Cut'/>"
literal|"<toolitem action='Copy'/>"
literal|"<toolitem action='Paste'/>"
literal|"<separator/>"
literal|"<toolitem action='ZoomIn'/>"
literal|"<toolitem action='ZoomOut'/>"
literal|"<separator/>"
literal|"<toolitem action='EditMapInfo'/>"
literal|"<separator/>"
literal|"<toolitem action='MoveToFront'/>"
literal|"<toolitem action='SendToBack'/>"
literal|"<separator/>"
literal|"<toolitem action='Grid'/>"
literal|"</toolbar>"
literal|""
literal|"<toolbar name='Tools'>"
literal|"<toolitem action='Arrow'/>"
literal|"<toolitem action='Rectangle'/>"
literal|"<toolitem action='Circle'/>"
literal|"<toolitem action='Polygon'/>"
literal|"<separator/>"
literal|"<toolitem action='EditAreaInfo'/>"
literal|"</toolbar>"
literal|""
literal|"<toolbar name='Selection'>"
literal|"<toolitem action='MoveUp'/>"
literal|"<toolitem action='MoveDown'/>"
literal|"<toolitem action='EditAreaInfo'/>"
literal|"<toolitem action='Clear'/>"
literal|"</toolbar>"
literal|"</ui>"
decl_stmt|;
end_decl_stmt

begin_function
name|Menu_t
modifier|*
DECL|function|make_menu (GtkWidget * main_vbox,GtkWidget * window)
name|make_menu
parameter_list|(
name|GtkWidget
modifier|*
name|main_vbox
parameter_list|,
name|GtkWidget
modifier|*
name|window
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|menubar
decl_stmt|;
name|GtkActionGroup
modifier|*
name|action_group
decl_stmt|;
name|GtkAccelGroup
modifier|*
name|accel_group
decl_stmt|;
name|GError
modifier|*
name|error
decl_stmt|;
name|action_group
operator|=
name|gtk_action_group_new
argument_list|(
literal|"MenuActions"
argument_list|)
expr_stmt|;
name|gtk_action_group_set_translation_domain
argument_list|(
name|action_group
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_action_group_add_actions
argument_list|(
name|action_group
argument_list|,
name|entries
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|entries
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
name|gtk_action_group_add_toggle_actions
argument_list|(
name|action_group
argument_list|,
name|toggle_entries
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|toggle_entries
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
name|gtk_action_group_add_radio_actions
argument_list|(
name|action_group
argument_list|,
name|color_entries
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|color_entries
argument_list|)
argument_list|,
literal|0
argument_list|,
name|G_CALLBACK
argument_list|(
name|set_preview_color
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_action_group_add_radio_actions
argument_list|(
name|action_group
argument_list|,
name|zoom_entries
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|zoom_entries
argument_list|)
argument_list|,
literal|0
argument_list|,
name|G_CALLBACK
argument_list|(
name|set_zoom_factor
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_action_group_add_radio_actions
argument_list|(
name|action_group
argument_list|,
name|mapping_entries
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|mapping_entries
argument_list|)
argument_list|,
literal|0
argument_list|,
name|G_CALLBACK
argument_list|(
name|set_func
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
name|ui_manager
operator|=
name|gtk_ui_manager_new
argument_list|()
expr_stmt|;
name|gtk_ui_manager_insert_action_group
argument_list|(
name|ui_manager
argument_list|,
name|action_group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|accel_group
operator|=
name|gtk_ui_manager_get_accel_group
argument_list|(
name|ui_manager
argument_list|)
expr_stmt|;
name|gtk_window_add_accel_group
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|accel_group
argument_list|)
expr_stmt|;
name|error
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_ui_manager_add_ui_from_string
argument_list|(
name|ui_manager
argument_list|,
name|ui_description
argument_list|,
operator|-
literal|1
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"building menus failed: %s"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
comment|/* exit (EXIT_FAILURE); */
block|}
name|menubar
operator|=
name|gtk_ui_manager_get_widget
argument_list|(
name|ui_manager
argument_list|,
literal|"/MainMenu"
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menubar
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|menubar
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|paste_buffer_add_add_cb
argument_list|(
name|paste_buffer_added
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|paste_buffer_add_remove_cb
argument_list|(
name|paste_buffer_removed
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|set_sensitive
argument_list|(
literal|"/MainMenu/EditMenu/Paste"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|menu_shapes_selected
argument_list|(
literal|0
argument_list|)
expr_stmt|;
name|menu_set_zoom_sensitivity
argument_list|(
literal|1
argument_list|)
expr_stmt|;
name|command_list_add_update_cb
argument_list|(
name|command_list_changed
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|command_list_changed
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
operator|&
name|_menu
return|;
block|}
end_function

begin_function
name|void
DECL|function|menu_build_mru_items (MRU_t * mru)
name|menu_build_mru_items
parameter_list|(
name|MRU_t
modifier|*
name|mru
parameter_list|)
block|{
name|GList
modifier|*
name|p
decl_stmt|;
name|gint
name|position
init|=
literal|0
decl_stmt|;
name|int
name|i
decl_stmt|;
return|return;
if|if
condition|(
name|_menu
operator|.
name|nr_off_mru_items
condition|)
block|{
name|GList
modifier|*
name|children
decl_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|_menu
operator|.
name|open_recent
argument_list|)
argument_list|)
expr_stmt|;
name|p
operator|=
name|g_list_nth
argument_list|(
name|children
argument_list|,
name|position
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|_menu
operator|.
name|nr_off_mru_items
condition|;
name|i
operator|++
operator|,
name|p
operator|=
name|p
operator|->
name|next
control|)
block|{
name|gtk_widget_destroy
argument_list|(
operator|(
name|GtkWidget
operator|*
operator|)
name|p
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
block|}
name|i
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|p
operator|=
name|mru
operator|->
name|list
init|;
name|p
condition|;
name|p
operator|=
name|p
operator|->
name|next
operator|,
name|i
operator|++
control|)
block|{
name|GtkWidget
modifier|*
name|item
init|=
name|insert_item_with_label
argument_list|(
name|_menu
operator|.
name|open_recent
argument_list|,
name|position
operator|++
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|p
operator|->
name|data
argument_list|,
name|menu_mru
argument_list|,
name|p
operator|->
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|i
operator|<
literal|9
condition|)
block|{
name|guchar
name|accelerator_key
init|=
literal|'1'
operator|+
name|i
decl_stmt|;
name|add_accelerator
argument_list|(
name|item
argument_list|,
name|accelerator_key
argument_list|,
name|GDK_CONTROL_MASK
argument_list|)
expr_stmt|;
block|}
block|}
name|_menu
operator|.
name|nr_off_mru_items
operator|=
name|i
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|do_main_popup_menu (GdkEventButton * event)
name|do_main_popup_menu
parameter_list|(
name|GdkEventButton
modifier|*
name|event
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|popup
init|=
name|gtk_ui_manager_get_widget
argument_list|(
name|ui_manager
argument_list|,
literal|"/PopupMenu"
argument_list|)
decl_stmt|;
name|gtk_menu_popup
argument_list|(
name|GTK_MENU
argument_list|(
name|popup
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|event
operator|->
name|button
argument_list|,
name|event
operator|->
name|time
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menu_check_grid (gboolean check)
name|menu_check_grid
parameter_list|(
name|gboolean
name|check
parameter_list|)
block|{
name|GtkAction
modifier|*
name|action
init|=
name|gtk_ui_manager_get_action
argument_list|(
name|ui_manager
argument_list|,
literal|"/MainMenu/ToolsMenu/Grid"
argument_list|)
decl_stmt|;
name|gtk_toggle_action_set_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|,
name|check
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|make_toolbar (GtkWidget * main_vbox,GtkWidget * window)
name|make_toolbar
parameter_list|(
name|GtkWidget
modifier|*
name|main_vbox
parameter_list|,
name|GtkWidget
modifier|*
name|window
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|toolbar
decl_stmt|;
name|toolbar
operator|=
name|gtk_ui_manager_get_widget
argument_list|(
name|ui_manager
argument_list|,
literal|"/Toolbar"
argument_list|)
expr_stmt|;
name|gtk_toolbar_set_style
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|GTK_TOOLBAR_ICONS
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|toolbar
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|toolbar
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toolbar
argument_list|)
expr_stmt|;
return|return
name|toolbar
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|make_tools (GtkWidget * window)
name|make_tools
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|toolbar
decl_stmt|;
name|toolbar
operator|=
name|gtk_ui_manager_get_widget
argument_list|(
name|ui_manager
argument_list|,
literal|"/Tools"
argument_list|)
expr_stmt|;
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|GTK_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
name|gtk_toolbar_set_style
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|GTK_TOOLBAR_ICONS
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|toolbar
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toolbar
argument_list|)
expr_stmt|;
return|return
name|toolbar
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|make_selection_toolbar (void)
name|make_selection_toolbar
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|toolbar
decl_stmt|;
name|toolbar
operator|=
name|gtk_ui_manager_get_widget
argument_list|(
name|ui_manager
argument_list|,
literal|"/Selection"
argument_list|)
expr_stmt|;
name|gtk_toolbar_set_style
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|GTK_TOOLBAR_ICONS
argument_list|)
expr_stmt|;
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|GTK_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|toolbar
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toolbar
argument_list|)
expr_stmt|;
return|return
name|toolbar
return|;
block|}
end_function

end_unit

