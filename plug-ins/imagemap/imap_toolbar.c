begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2004 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
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
file|"imap_main.h"
end_include

begin_include
include|#
directive|include
file|"imap_misc.h"
end_include

begin_include
include|#
directive|include
file|"imap_stock.h"
end_include

begin_include
include|#
directive|include
file|"imap_toolbar.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpstock.h"
end_include

begin_decl_stmt
DECL|variable|_command_lock
specifier|static
name|gboolean
name|_command_lock
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|toolbar_command (GtkWidget * widget,gpointer data)
name|toolbar_command
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
name|_command_lock
condition|)
block|{
name|_command_lock
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|CommandFactory_t
modifier|*
name|factory
init|=
operator|(
name|CommandFactory_t
operator|*
operator|)
name|data
decl_stmt|;
name|Command_t
modifier|*
name|command
init|=
call|(
modifier|*
name|factory
call|)
argument_list|()
decl_stmt|;
name|command_execute
argument_list|(
name|command
argument_list|)
expr_stmt|;
block|}
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
name|ToolBar_t
modifier|*
name|toolbar
init|=
operator|(
name|ToolBar_t
operator|*
operator|)
name|data
decl_stmt|;
comment|/* Set undo entry */
name|gtk_widget_set_sensitive
argument_list|(
name|toolbar
operator|->
name|undo
argument_list|,
operator|(
name|command
operator|!=
name|NULL
operator|)
argument_list|)
expr_stmt|;
comment|/* Set redo entry */
name|command
operator|=
name|command_list_get_redo_command
argument_list|()
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|toolbar
operator|->
name|redo
argument_list|,
operator|(
name|command
operator|!=
name|NULL
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|toolbar_shapes_selected (ToolBar_t * toolbar,gint count)
name|toolbar_shapes_selected
parameter_list|(
name|ToolBar_t
modifier|*
name|toolbar
parameter_list|,
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
name|toolbar
operator|->
name|cut
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|toolbar
operator|->
name|copy
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|toolbar
operator|->
name|to_front
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|toolbar
operator|->
name|to_back
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|ToolBar_t
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
name|ToolBar_t
modifier|*
name|data
init|=
name|g_new
argument_list|(
name|ToolBar_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|handlebox
decl_stmt|,
modifier|*
name|toolbar
decl_stmt|,
modifier|*
name|paste
decl_stmt|;
name|handlebox
operator|=
name|gtk_handle_box_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|handlebox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|data
operator|->
name|toolbar
operator|=
name|toolbar
operator|=
name|gtk_toolbar_new
argument_list|()
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
name|gtk_toolbar_set_orientation
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|,
name|GTK_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|toolbar
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|handlebox
argument_list|)
argument_list|,
name|toolbar
argument_list|)
expr_stmt|;
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|GTK_STOCK_OPEN
argument_list|,
literal|"Open"
argument_list|,
name|_
argument_list|(
literal|"Open"
argument_list|)
argument_list|,
name|toolbar_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_open
argument_list|)
expr_stmt|;
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|GTK_STOCK_SAVE
argument_list|,
literal|"Save"
argument_list|,
name|_
argument_list|(
literal|"Save"
argument_list|)
argument_list|,
name|toolbar_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_save
argument_list|)
expr_stmt|;
name|gtk_toolbar_append_space
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|)
expr_stmt|;
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|GTK_STOCK_PREFERENCES
argument_list|,
literal|"Preferences"
argument_list|,
name|_
argument_list|(
literal|"Preferences"
argument_list|)
argument_list|,
name|toolbar_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_preferences
argument_list|)
expr_stmt|;
name|gtk_toolbar_append_space
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|undo
operator|=
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|GTK_STOCK_UNDO
argument_list|,
literal|"Undo"
argument_list|,
name|_
argument_list|(
literal|"Undo"
argument_list|)
argument_list|,
name|toolbar_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_undo
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|undo
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|data
operator|->
name|redo
operator|=
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|GTK_STOCK_REDO
argument_list|,
literal|"Redo"
argument_list|,
name|_
argument_list|(
literal|"Redo"
argument_list|)
argument_list|,
name|toolbar_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_redo
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|redo
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|command_list_add_update_cb
argument_list|(
name|command_list_changed
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gtk_toolbar_append_space
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|cut
operator|=
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|GTK_STOCK_CUT
argument_list|,
literal|"Cut"
argument_list|,
name|_
argument_list|(
literal|"Cut"
argument_list|)
argument_list|,
name|toolbar_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_cut
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|cut
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|data
operator|->
name|copy
operator|=
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|GTK_STOCK_COPY
argument_list|,
literal|"Copy"
argument_list|,
name|_
argument_list|(
literal|"Copy"
argument_list|)
argument_list|,
name|toolbar_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_copy
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|copy
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|paste
operator|=
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|GTK_STOCK_PASTE
argument_list|,
literal|"Paste"
argument_list|,
name|_
argument_list|(
literal|"Paste"
argument_list|)
argument_list|,
name|toolbar_command
argument_list|,
operator|&
name|data
operator|->
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
name|gtk_toolbar_append_space
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|zoom_in
operator|=
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|GTK_STOCK_ZOOM_IN
argument_list|,
literal|"ZoomIn"
argument_list|,
name|_
argument_list|(
literal|"Zoom in"
argument_list|)
argument_list|,
name|toolbar_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_zoom_in
argument_list|)
expr_stmt|;
name|data
operator|->
name|zoom_out
operator|=
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|GTK_STOCK_ZOOM_OUT
argument_list|,
literal|"ZoomOut"
argument_list|,
name|_
argument_list|(
literal|"Zoom out"
argument_list|)
argument_list|,
name|toolbar_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_zoom_out
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|zoom_out
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_toolbar_append_space
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|)
expr_stmt|;
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|IMAP_STOCK_MAP_INFO
argument_list|,
literal|"EditMapInfo"
argument_list|,
name|_
argument_list|(
literal|"Edit Map Info"
argument_list|)
argument_list|,
name|toolbar_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_edit_map_info
argument_list|)
expr_stmt|;
name|gtk_toolbar_append_space
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|to_front
operator|=
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|IMAP_STOCK_TO_FRONT
argument_list|,
literal|"ToFront"
argument_list|,
name|_
argument_list|(
literal|"Move To Front"
argument_list|)
argument_list|,
name|toolbar_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_move_to_front
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|to_front
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|data
operator|->
name|to_back
operator|=
name|make_toolbar_stock_icon
argument_list|(
name|toolbar
argument_list|,
name|IMAP_STOCK_TO_BACK
argument_list|,
literal|"ToBack"
argument_list|,
name|_
argument_list|(
literal|"Send To Back"
argument_list|)
argument_list|,
name|toolbar_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_send_to_back
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|to_back
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_toolbar_append_space
argument_list|(
name|GTK_TOOLBAR
argument_list|(
name|toolbar
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|grid
operator|=
name|make_toolbar_toggle_icon
argument_list|(
name|toolbar
argument_list|,
name|GIMP_STOCK_GRID
argument_list|,
literal|"Grid"
argument_list|,
name|_
argument_list|(
literal|"Grid"
argument_list|)
argument_list|,
name|toolbar_command
argument_list|,
operator|&
name|data
operator|->
name|cmd_grid
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toolbar
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|handlebox
argument_list|)
expr_stmt|;
return|return
name|data
return|;
block|}
end_function

begin_function
name|void
DECL|function|toolbar_set_zoom_sensitivity (ToolBar_t * toolbar,gint factor)
name|toolbar_set_zoom_sensitivity
parameter_list|(
name|ToolBar_t
modifier|*
name|toolbar
parameter_list|,
name|gint
name|factor
parameter_list|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|toolbar
operator|->
name|zoom_in
argument_list|,
name|factor
operator|<
literal|8
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|toolbar
operator|->
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
DECL|function|toolbar_set_grid (ToolBar_t * toolbar,gboolean active)
name|toolbar_set_grid
parameter_list|(
name|ToolBar_t
modifier|*
name|toolbar
parameter_list|,
name|gboolean
name|active
parameter_list|)
block|{
name|_command_lock
operator|=
name|TRUE
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toolbar
operator|->
name|grid
argument_list|)
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

