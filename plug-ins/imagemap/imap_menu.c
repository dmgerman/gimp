begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2002 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
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
file|"imap_popup.h"
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
file|"imap_tools.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
DECL|variable|_menu_callback_lock
specifier|static
name|gint
name|_menu_callback_lock
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|_menu
specifier|static
name|Menu_t
name|_menu
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|menu_select (GtkWidget * item)
name|menu_select
parameter_list|(
name|GtkWidget
modifier|*
name|item
parameter_list|)
block|{
name|_menu_callback_lock
operator|=
name|TRUE
expr_stmt|;
name|gtk_check_menu_item_set_active
argument_list|(
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|item
argument_list|)
argument_list|,
name|TRUE
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
name|gtk_widget_set_sensitive
argument_list|(
name|_menu
operator|.
name|zoom_in
argument_list|,
name|factor
operator|<
literal|8
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|_menu
operator|.
name|zoom_out
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
name|gtk_widget_set_sensitive
argument_list|(
name|_menu
operator|.
name|cut
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|_menu
operator|.
name|copy
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|_menu
operator|.
name|clear
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|_menu
operator|.
name|edit
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|_menu
operator|.
name|deselect_all
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|menu_zoom_to (GtkWidget * widget,gpointer data)
name|menu_zoom_to
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|gtk_check_menu_item_get_active
argument_list|(
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
argument_list|)
condition|)
block|{
name|gint
name|factor
init|=
operator|(
name|gint
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|_menu_callback_lock
condition|)
block|{
name|_menu_callback_lock
operator|--
expr_stmt|;
block|}
else|else
block|{
name|set_zoom
argument_list|(
name|factor
argument_list|)
expr_stmt|;
block|}
name|menu_set_zoom_sensitivity
argument_list|(
name|factor
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|menu_rectangle (GtkWidget * widget,gpointer data)
name|menu_rectangle
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|_menu_callback_lock
condition|)
block|{
name|_menu_callback_lock
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|set_rectangle_func
argument_list|()
expr_stmt|;
name|tools_select_rectangle
argument_list|()
expr_stmt|;
name|popup_select_rectangle
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|menu_circle (GtkWidget * widget,gpointer data)
name|menu_circle
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|_menu_callback_lock
condition|)
block|{
name|_menu_callback_lock
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|set_circle_func
argument_list|()
expr_stmt|;
name|tools_select_circle
argument_list|()
expr_stmt|;
name|popup_select_circle
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|menu_polygon (GtkWidget * widget,gpointer data)
name|menu_polygon
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|_menu_callback_lock
condition|)
block|{
name|_menu_callback_lock
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|set_polygon_func
argument_list|()
expr_stmt|;
name|tools_select_polygon
argument_list|()
expr_stmt|;
name|popup_select_polygon
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|menu_arrow (GtkWidget * widget,gpointer data)
name|menu_arrow
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|_menu_callback_lock
condition|)
block|{
name|_menu_callback_lock
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|set_arrow_func
argument_list|()
expr_stmt|;
name|tools_select_arrow
argument_list|()
expr_stmt|;
name|popup_select_arrow
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|menu_fuzzy_select (GtkWidget * widget,gpointer data)
name|menu_fuzzy_select
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|_menu_callback_lock
condition|)
block|{
name|_menu_callback_lock
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
comment|/*       set_fuzzy_select_func();       tools_select_fuzzy();       popup_select_fuzzy(); */
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|menu_grid (GtkWidget * widget,gpointer data)
name|menu_grid
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|_menu_callback_lock
condition|)
block|{
name|_menu_callback_lock
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|gint
name|grid
init|=
name|toggle_grid
argument_list|()
decl_stmt|;
name|popup_check_grid
argument_list|(
name|grid
argument_list|)
expr_stmt|;
name|main_toolbar_set_grid
argument_list|(
name|grid
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|make_file_menu (GtkWidget * menu_bar)
name|make_file_menu
parameter_list|(
name|GtkWidget
modifier|*
name|menu_bar
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|file_menu
init|=
name|make_menu_bar_item
argument_list|(
name|menu_bar
argument_list|,
name|_
argument_list|(
literal|"_File"
argument_list|)
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|item
decl_stmt|;
name|_menu
operator|.
name|file_menu
operator|=
name|file_menu
expr_stmt|;
name|make_item_with_image
argument_list|(
name|file_menu
argument_list|,
name|GTK_STOCK_OPEN
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_open
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|open_recent
operator|=
name|make_sub_menu
argument_list|(
name|file_menu
argument_list|,
name|_
argument_list|(
literal|"Open Recent"
argument_list|)
argument_list|)
expr_stmt|;
name|make_item_with_image
argument_list|(
name|file_menu
argument_list|,
name|GTK_STOCK_SAVE
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_save
argument_list|)
expr_stmt|;
name|item
operator|=
name|make_item_with_image
argument_list|(
name|file_menu
argument_list|,
name|GTK_STOCK_SAVE_AS
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_save_as
argument_list|)
expr_stmt|;
name|add_accelerator
argument_list|(
name|item
argument_list|,
literal|'S'
argument_list|,
name|GDK_SHIFT_MASK
operator||
name|GDK_CONTROL_MASK
argument_list|)
expr_stmt|;
name|make_separator
argument_list|(
name|file_menu
argument_list|)
expr_stmt|;
name|make_item_with_image
argument_list|(
name|file_menu
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_close
argument_list|)
expr_stmt|;
name|make_item_with_image
argument_list|(
name|file_menu
argument_list|,
name|GTK_STOCK_QUIT
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_quit
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
name|gchar
modifier|*
name|scratch
decl_stmt|;
name|GtkWidget
modifier|*
name|icon
decl_stmt|;
comment|/* Set undo entry */
if|if
condition|(
name|_menu
operator|.
name|undo
condition|)
name|gtk_widget_destroy
argument_list|(
name|_menu
operator|.
name|undo
argument_list|)
expr_stmt|;
name|scratch
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
name|_menu
operator|.
name|undo
operator|=
name|insert_item_with_label
argument_list|(
name|_menu
operator|.
name|edit_menu
argument_list|,
literal|1
argument_list|,
name|scratch
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_undo
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|scratch
argument_list|)
expr_stmt|;
name|add_accelerator
argument_list|(
name|_menu
operator|.
name|undo
argument_list|,
literal|'Z'
argument_list|,
name|GDK_CONTROL_MASK
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|_menu
operator|.
name|undo
argument_list|,
operator|(
name|command
operator|!=
name|NULL
operator|)
argument_list|)
expr_stmt|;
name|icon
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|GTK_STOCK_UNDO
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|)
expr_stmt|;
name|gtk_image_menu_item_set_image
argument_list|(
name|GTK_IMAGE_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|undo
argument_list|)
argument_list|,
name|icon
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|icon
argument_list|)
expr_stmt|;
comment|/* Set redo entry */
name|command
operator|=
name|command_list_get_redo_command
argument_list|()
expr_stmt|;
if|if
condition|(
name|_menu
operator|.
name|redo
condition|)
name|gtk_widget_destroy
argument_list|(
name|_menu
operator|.
name|redo
argument_list|)
expr_stmt|;
name|scratch
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
name|_menu
operator|.
name|redo
operator|=
name|insert_item_with_label
argument_list|(
name|_menu
operator|.
name|edit_menu
argument_list|,
literal|2
argument_list|,
name|scratch
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_redo
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|scratch
argument_list|)
expr_stmt|;
name|add_accelerator
argument_list|(
name|_menu
operator|.
name|redo
argument_list|,
literal|'Z'
argument_list|,
name|GDK_SHIFT_MASK
operator||
name|GDK_CONTROL_MASK
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|_menu
operator|.
name|redo
argument_list|,
operator|(
name|command
operator|!=
name|NULL
operator|)
argument_list|)
expr_stmt|;
name|icon
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|GTK_STOCK_REDO
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|)
expr_stmt|;
name|gtk_image_menu_item_set_image
argument_list|(
name|GTK_IMAGE_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|redo
argument_list|)
argument_list|,
name|icon
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|icon
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
name|gtk_widget_set_sensitive
argument_list|(
operator|(
name|GtkWidget
operator|*
operator|)
name|data
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
name|gtk_widget_set_sensitive
argument_list|(
operator|(
name|GtkWidget
operator|*
operator|)
name|data
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|make_edit_menu (GtkWidget * menu_bar)
name|make_edit_menu
parameter_list|(
name|GtkWidget
modifier|*
name|menu_bar
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|edit_menu
init|=
name|make_menu_bar_item
argument_list|(
name|menu_bar
argument_list|,
name|_
argument_list|(
literal|"_Edit"
argument_list|)
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|item
decl_stmt|,
modifier|*
name|paste
decl_stmt|;
name|_menu
operator|.
name|edit_menu
operator|=
name|edit_menu
expr_stmt|;
name|command_list_changed
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|make_separator
argument_list|(
name|edit_menu
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|cut
operator|=
name|make_item_with_image
argument_list|(
name|edit_menu
argument_list|,
name|GTK_STOCK_CUT
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_cut
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|copy
operator|=
name|make_item_with_image
argument_list|(
name|edit_menu
argument_list|,
name|GTK_STOCK_COPY
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_copy
argument_list|)
expr_stmt|;
name|paste
operator|=
name|make_item_with_image
argument_list|(
name|edit_menu
argument_list|,
name|GTK_STOCK_PASTE
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_paste
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|paste
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|clear
operator|=
name|make_item_with_image
argument_list|(
name|edit_menu
argument_list|,
name|GTK_STOCK_CLEAR
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_clear
argument_list|)
expr_stmt|;
name|add_accelerator
argument_list|(
name|_menu
operator|.
name|clear
argument_list|,
literal|'K'
argument_list|,
name|GDK_CONTROL_MASK
argument_list|)
expr_stmt|;
name|make_separator
argument_list|(
name|edit_menu
argument_list|)
expr_stmt|;
name|item
operator|=
name|make_item_with_label
argument_list|(
name|edit_menu
argument_list|,
name|_
argument_list|(
literal|"Select _All"
argument_list|)
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_select_all
argument_list|)
expr_stmt|;
name|add_accelerator
argument_list|(
name|item
argument_list|,
literal|'A'
argument_list|,
name|GDK_CONTROL_MASK
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|deselect_all
operator|=
name|make_item_with_label
argument_list|(
name|edit_menu
argument_list|,
name|_
argument_list|(
literal|"Deselect _All"
argument_list|)
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_deselect_all
argument_list|)
expr_stmt|;
name|add_accelerator
argument_list|(
name|_menu
operator|.
name|deselect_all
argument_list|,
literal|'A'
argument_list|,
name|GDK_SHIFT_MASK
operator||
name|GDK_CONTROL_MASK
argument_list|)
expr_stmt|;
name|make_separator
argument_list|(
name|edit_menu
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|edit
operator|=
name|make_item_with_label
argument_list|(
name|edit_menu
argument_list|,
name|_
argument_list|(
literal|"Edit Area Info..."
argument_list|)
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_edit_area_info
argument_list|)
expr_stmt|;
name|make_separator
argument_list|(
name|edit_menu
argument_list|)
expr_stmt|;
name|make_item_with_image
argument_list|(
name|edit_menu
argument_list|,
name|GTK_STOCK_PREFERENCES
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_preferences
argument_list|)
expr_stmt|;
name|paste_buffer_add_add_cb
argument_list|(
name|paste_buffer_added
argument_list|,
operator|(
name|gpointer
operator|)
name|paste
argument_list|)
expr_stmt|;
name|paste_buffer_add_remove_cb
argument_list|(
name|paste_buffer_removed
argument_list|,
operator|(
name|gpointer
operator|)
name|paste
argument_list|)
expr_stmt|;
name|command_list_add_update_cb
argument_list|(
name|command_list_changed
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|make_view_menu (GtkWidget * menu_bar)
name|make_view_menu
parameter_list|(
name|GtkWidget
modifier|*
name|menu_bar
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|view_menu
init|=
name|make_menu_bar_item
argument_list|(
name|menu_bar
argument_list|,
name|_
argument_list|(
literal|"_View"
argument_list|)
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|zoom_menu
decl_stmt|,
modifier|*
name|item
decl_stmt|;
name|GSList
modifier|*
name|group
init|=
name|NULL
decl_stmt|;
name|item
operator|=
name|make_check_item
argument_list|(
name|view_menu
argument_list|,
name|_
argument_list|(
literal|"Area List"
argument_list|)
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_area_list
argument_list|)
expr_stmt|;
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|item
argument_list|)
operator|->
name|active
operator|=
name|TRUE
expr_stmt|;
name|make_item_with_label
argument_list|(
name|view_menu
argument_list|,
name|_
argument_list|(
literal|"Source..."
argument_list|)
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_source
argument_list|)
expr_stmt|;
name|make_separator
argument_list|(
name|view_menu
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|color
operator|=
name|make_radio_item
argument_list|(
name|view_menu
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Color"
argument_list|)
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_color
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_menu_item_get_group
argument_list|(
name|GTK_RADIO_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|color
argument_list|)
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|gray
operator|=
name|make_radio_item
argument_list|(
name|view_menu
argument_list|,
name|group
argument_list|,
name|_
argument_list|(
literal|"Grayscale"
argument_list|)
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_gray
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_menu_item_get_group
argument_list|(
name|GTK_RADIO_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|gray
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|get_map_info
argument_list|()
operator|->
name|color
condition|)
block|{
comment|/* Gray image */
name|gtk_widget_set_sensitive
argument_list|(
name|_menu
operator|.
name|color
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|color
argument_list|)
operator|->
name|active
operator|=
name|FALSE
expr_stmt|;
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|gray
argument_list|)
operator|->
name|active
operator|=
name|TRUE
expr_stmt|;
block|}
name|make_separator
argument_list|(
name|view_menu
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|zoom_in
operator|=
name|make_item_with_image
argument_list|(
name|view_menu
argument_list|,
name|GTK_STOCK_ZOOM_IN
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_zoom_in
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|zoom_out
operator|=
name|make_item_with_image
argument_list|(
name|view_menu
argument_list|,
name|GTK_STOCK_ZOOM_OUT
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_zoom_out
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|_menu
operator|.
name|zoom_out
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|zoom_menu
operator|=
name|make_sub_menu
argument_list|(
name|view_menu
argument_list|,
name|_
argument_list|(
literal|"Zoom To"
argument_list|)
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|zoom
index|[
literal|0
index|]
operator|=
name|make_radio_item
argument_list|(
name|zoom_menu
argument_list|,
name|NULL
argument_list|,
literal|"1:1"
argument_list|,
name|menu_zoom_to
argument_list|,
operator|(
name|gpointer
operator|)
literal|1
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_menu_item_get_group
argument_list|(
name|GTK_RADIO_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|zoom
index|[
literal|0
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|zoom
index|[
literal|1
index|]
operator|=
name|make_radio_item
argument_list|(
name|zoom_menu
argument_list|,
name|group
argument_list|,
literal|"1:2"
argument_list|,
name|menu_zoom_to
argument_list|,
operator|(
name|gpointer
operator|)
literal|2
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_menu_item_get_group
argument_list|(
name|GTK_RADIO_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|zoom
index|[
literal|1
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|zoom
index|[
literal|2
index|]
operator|=
name|make_radio_item
argument_list|(
name|zoom_menu
argument_list|,
name|group
argument_list|,
literal|"1:3"
argument_list|,
name|menu_zoom_to
argument_list|,
operator|(
name|gpointer
operator|)
literal|3
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_menu_item_get_group
argument_list|(
name|GTK_RADIO_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|zoom
index|[
literal|2
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|zoom
index|[
literal|3
index|]
operator|=
name|make_radio_item
argument_list|(
name|zoom_menu
argument_list|,
name|group
argument_list|,
literal|"1:4"
argument_list|,
name|menu_zoom_to
argument_list|,
operator|(
name|gpointer
operator|)
literal|4
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_menu_item_get_group
argument_list|(
name|GTK_RADIO_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|zoom
index|[
literal|3
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|zoom
index|[
literal|4
index|]
operator|=
name|make_radio_item
argument_list|(
name|zoom_menu
argument_list|,
name|group
argument_list|,
literal|"1:5"
argument_list|,
name|menu_zoom_to
argument_list|,
operator|(
name|gpointer
operator|)
literal|5
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_menu_item_get_group
argument_list|(
name|GTK_RADIO_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|zoom
index|[
literal|4
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|zoom
index|[
literal|5
index|]
operator|=
name|make_radio_item
argument_list|(
name|zoom_menu
argument_list|,
name|group
argument_list|,
literal|"1:6"
argument_list|,
name|menu_zoom_to
argument_list|,
operator|(
name|gpointer
operator|)
literal|6
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_menu_item_get_group
argument_list|(
name|GTK_RADIO_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|zoom
index|[
literal|5
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|zoom
index|[
literal|6
index|]
operator|=
name|make_radio_item
argument_list|(
name|zoom_menu
argument_list|,
name|group
argument_list|,
literal|"1:7"
argument_list|,
name|menu_zoom_to
argument_list|,
operator|(
name|gpointer
operator|)
literal|7
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_menu_item_get_group
argument_list|(
name|GTK_RADIO_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|zoom
index|[
literal|6
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|zoom
index|[
literal|7
index|]
operator|=
name|make_radio_item
argument_list|(
name|zoom_menu
argument_list|,
name|group
argument_list|,
literal|"1:8"
argument_list|,
name|menu_zoom_to
argument_list|,
operator|(
name|gpointer
operator|)
literal|8
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|make_mapping_menu (GtkWidget * menu_bar)
name|make_mapping_menu
parameter_list|(
name|GtkWidget
modifier|*
name|menu_bar
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|menu
init|=
name|make_menu_bar_item
argument_list|(
name|menu_bar
argument_list|,
name|_
argument_list|(
literal|"_Mapping"
argument_list|)
argument_list|)
decl_stmt|;
name|GSList
modifier|*
name|group
decl_stmt|;
name|_menu
operator|.
name|arrow
operator|=
name|make_radio_item
argument_list|(
name|menu
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Arrow"
argument_list|)
argument_list|,
name|menu_arrow
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_menu_item_get_group
argument_list|(
name|GTK_RADIO_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|arrow
argument_list|)
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|fuzzy_select
operator|=
name|make_radio_item
argument_list|(
name|menu
argument_list|,
name|group
argument_list|,
name|_
argument_list|(
literal|"Select Contiguous Region"
argument_list|)
argument_list|,
name|menu_fuzzy_select
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_menu_item_get_group
argument_list|(
name|GTK_RADIO_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|fuzzy_select
argument_list|)
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|rectangle
operator|=
name|make_radio_item
argument_list|(
name|menu
argument_list|,
name|group
argument_list|,
name|_
argument_list|(
literal|"Rectangle"
argument_list|)
argument_list|,
name|menu_rectangle
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_menu_item_get_group
argument_list|(
name|GTK_RADIO_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|rectangle
argument_list|)
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|circle
operator|=
name|make_radio_item
argument_list|(
name|menu
argument_list|,
name|group
argument_list|,
name|_
argument_list|(
literal|"Circle"
argument_list|)
argument_list|,
name|menu_circle
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_menu_item_get_group
argument_list|(
name|GTK_RADIO_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|circle
argument_list|)
argument_list|)
expr_stmt|;
name|_menu
operator|.
name|polygon
operator|=
name|make_radio_item
argument_list|(
name|menu
argument_list|,
name|group
argument_list|,
name|_
argument_list|(
literal|"Polygon"
argument_list|)
argument_list|,
name|menu_polygon
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|make_separator
argument_list|(
name|menu
argument_list|)
expr_stmt|;
name|make_item_with_image
argument_list|(
name|menu
argument_list|,
name|IMAP_STOCK_MAP_INFO
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_edit_map_info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|make_tools_menu (GtkWidget * menu_bar)
name|make_tools_menu
parameter_list|(
name|GtkWidget
modifier|*
name|menu_bar
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|tools_menu
init|=
name|make_menu_bar_item
argument_list|(
name|menu_bar
argument_list|,
name|_
argument_list|(
literal|"_Tools"
argument_list|)
argument_list|)
decl_stmt|;
name|_menu
operator|.
name|grid
operator|=
name|make_check_item
argument_list|(
name|tools_menu
argument_list|,
name|_
argument_list|(
literal|"Grid"
argument_list|)
argument_list|,
name|menu_grid
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|make_item_with_label
argument_list|(
name|tools_menu
argument_list|,
name|_
argument_list|(
literal|"Grid Settings..."
argument_list|)
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_grid_settings
argument_list|)
expr_stmt|;
name|make_separator
argument_list|(
name|tools_menu
argument_list|)
expr_stmt|;
name|make_item_with_label
argument_list|(
name|tools_menu
argument_list|,
name|_
argument_list|(
literal|"Use GIMP Guides..."
argument_list|)
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_use_gimp_guides
argument_list|)
expr_stmt|;
name|make_item_with_label
argument_list|(
name|tools_menu
argument_list|,
name|_
argument_list|(
literal|"Create Guides..."
argument_list|)
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_create_guides
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|make_help_menu (GtkWidget * menu_bar)
name|make_help_menu
parameter_list|(
name|GtkWidget
modifier|*
name|menu_bar
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|help_menu
init|=
name|make_menu_bar_item
argument_list|(
name|menu_bar
argument_list|,
name|_
argument_list|(
literal|"_Help"
argument_list|)
argument_list|)
decl_stmt|;
name|gtk_menu_item_set_right_justified
argument_list|(
name|GTK_MENU_ITEM
argument_list|(
name|gtk_menu_get_attach_widget
argument_list|(
name|GTK_MENU
argument_list|(
name|help_menu
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|make_item_with_label
argument_list|(
name|help_menu
argument_list|,
name|_
argument_list|(
literal|"About ImageMap..."
argument_list|)
argument_list|,
name|menu_command
argument_list|,
operator|&
name|_menu
operator|.
name|cmd_about
argument_list|)
expr_stmt|;
block|}
end_function

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
name|menu_bar
init|=
name|gtk_menu_bar_new
argument_list|()
decl_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|menu_bar
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menu_bar
argument_list|)
expr_stmt|;
name|init_accel_group
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|make_file_menu
argument_list|(
name|menu_bar
argument_list|)
expr_stmt|;
name|make_edit_menu
argument_list|(
name|menu_bar
argument_list|)
expr_stmt|;
name|make_view_menu
argument_list|(
name|menu_bar
argument_list|)
expr_stmt|;
name|make_mapping_menu
argument_list|(
name|menu_bar
argument_list|)
expr_stmt|;
name|make_tools_menu
argument_list|(
name|menu_bar
argument_list|)
expr_stmt|;
name|make_help_menu
argument_list|(
name|menu_bar
argument_list|)
expr_stmt|;
name|menu_shapes_selected
argument_list|(
literal|0
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
operator|+
literal|1
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menu_select_arrow (void)
name|menu_select_arrow
parameter_list|(
name|void
parameter_list|)
block|{
name|menu_select
argument_list|(
name|_menu
operator|.
name|arrow
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menu_select_fuzzy_select (void)
name|menu_select_fuzzy_select
parameter_list|(
name|void
parameter_list|)
block|{
name|menu_select
argument_list|(
name|_menu
operator|.
name|fuzzy_select
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menu_select_rectangle (void)
name|menu_select_rectangle
parameter_list|(
name|void
parameter_list|)
block|{
name|menu_select
argument_list|(
name|_menu
operator|.
name|rectangle
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menu_select_circle (void)
name|menu_select_circle
parameter_list|(
name|void
parameter_list|)
block|{
name|menu_select
argument_list|(
name|_menu
operator|.
name|circle
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menu_select_polygon (void)
name|menu_select_polygon
parameter_list|(
name|void
parameter_list|)
block|{
name|menu_select
argument_list|(
name|_menu
operator|.
name|polygon
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menu_check_grid (gint check)
name|menu_check_grid
parameter_list|(
name|gint
name|check
parameter_list|)
block|{
name|_menu_callback_lock
operator|=
name|TRUE
expr_stmt|;
name|gtk_check_menu_item_set_active
argument_list|(
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|grid
argument_list|)
argument_list|,
name|check
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
name|_menu_callback_lock
operator|=
literal|2
expr_stmt|;
name|gtk_check_menu_item_set_active
argument_list|(
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|_menu
operator|.
name|zoom
index|[
name|factor
operator|-
literal|1
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|menu_set_zoom_sensitivity
argument_list|(
name|factor
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

