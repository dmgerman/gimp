begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"imap_circle.h"
end_include

begin_include
include|#
directive|include
file|"imap_edit_area_info.h"
end_include

begin_include
include|#
directive|include
file|"imap_main.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_include
include|#
directive|include
file|"imap_menu.h"
end_include

begin_include
include|#
directive|include
file|"imap_misc.h"
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
file|"imap_rectangle.h"
end_include

begin_include
include|#
directive|include
file|"imap_tools.h"
end_include

begin_include
include|#
directive|include
file|"arrow.xpm"
end_include

begin_include
include|#
directive|include
file|"rectangle.xpm"
end_include

begin_include
include|#
directive|include
file|"circle.xpm"
end_include

begin_include
include|#
directive|include
file|"polygon.xpm"
end_include

begin_include
include|#
directive|include
file|"delete.xpm"
end_include

begin_include
include|#
directive|include
file|"edit.xpm"
end_include

begin_decl_stmt
DECL|variable|_callback_lock
specifier|static
name|gboolean
name|_callback_lock
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|_tools
specifier|static
name|Tools_t
name|_tools
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|tools_command (GtkWidget * widget,gpointer data)
name|tools_command
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
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
end_function

begin_function
name|void
DECL|function|arrow_on_button_press (GtkWidget * widget,GdkEventButton * event,gpointer data)
name|arrow_on_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|event
operator|->
name|button
operator|==
literal|1
condition|)
block|{
if|if
condition|(
name|event
operator|->
name|type
operator|==
name|GDK_2BUTTON_PRESS
condition|)
name|edit_shape
argument_list|(
operator|(
name|gint
operator|)
name|event
operator|->
name|x
argument_list|,
operator|(
name|gint
operator|)
name|event
operator|->
name|y
argument_list|)
expr_stmt|;
else|else
name|select_shape
argument_list|(
name|widget
argument_list|,
name|event
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|do_popup_menu
argument_list|(
name|event
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|arrow_clicked (GtkWidget * widget,gpointer data)
name|arrow_clicked
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
name|_callback_lock
condition|)
block|{
name|_callback_lock
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|set_arrow_func
argument_list|()
expr_stmt|;
name|menu_select_arrow
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
DECL|function|rectangle_clicked (GtkWidget * widget,gpointer data)
name|rectangle_clicked
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
name|_callback_lock
condition|)
block|{
name|_callback_lock
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|set_rectangle_func
argument_list|()
expr_stmt|;
name|menu_select_rectangle
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
DECL|function|circle_clicked (GtkWidget * widget,gpointer data)
name|circle_clicked
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
name|_callback_lock
condition|)
block|{
name|_callback_lock
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|set_circle_func
argument_list|()
expr_stmt|;
name|menu_select_circle
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
DECL|function|polygon_clicked (GtkWidget * widget,gpointer data)
name|polygon_clicked
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
name|_callback_lock
condition|)
block|{
name|_callback_lock
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|set_polygon_func
argument_list|()
expr_stmt|;
name|menu_select_polygon
argument_list|()
expr_stmt|;
name|popup_select_polygon
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
name|Tools_t
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
name|handlebox
decl_stmt|;
name|GtkWidget
modifier|*
name|toolbar
decl_stmt|;
name|toolbar
operator|=
name|gtk_toolbar_new
argument_list|()
expr_stmt|;
name|_tools
operator|.
name|container
operator|=
name|handlebox
operator|=
name|gtk_handle_box_new
argument_list|()
expr_stmt|;
name|gtk_toolbar_set_orientation
argument_list|(
name|GTK_TOOLBAR
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
literal|5
argument_list|)
expr_stmt|;
comment|/* FIXME: replacement    gtk_toolbar_set_space_size(GTK_TOOLBAR(toolbar), 5); */
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
name|_tools
operator|.
name|arrow
operator|=
name|make_toolbar_radio_icon
argument_list|(
name|toolbar
argument_list|,
name|window
argument_list|,
name|NULL
argument_list|,
name|arrow_xpm
argument_list|,
literal|"Select"
argument_list|,
name|_
argument_list|(
literal|"Select existing area"
argument_list|)
argument_list|,
name|arrow_clicked
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|_tools
operator|.
name|rectangle
operator|=
name|make_toolbar_radio_icon
argument_list|(
name|toolbar
argument_list|,
name|window
argument_list|,
name|_tools
operator|.
name|arrow
argument_list|,
name|rectangle_xpm
argument_list|,
literal|"Rectangle"
argument_list|,
name|_
argument_list|(
literal|"Define Rectangle area"
argument_list|)
argument_list|,
name|rectangle_clicked
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|_tools
operator|.
name|circle
operator|=
name|make_toolbar_radio_icon
argument_list|(
name|toolbar
argument_list|,
name|window
argument_list|,
name|_tools
operator|.
name|rectangle
argument_list|,
name|circle_xpm
argument_list|,
literal|"Circle"
argument_list|,
name|_
argument_list|(
literal|"Define Circle/Oval area"
argument_list|)
argument_list|,
name|circle_clicked
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|_tools
operator|.
name|polygon
operator|=
name|make_toolbar_radio_icon
argument_list|(
name|toolbar
argument_list|,
name|window
argument_list|,
name|_tools
operator|.
name|circle
argument_list|,
name|polygon_xpm
argument_list|,
literal|"Polygon"
argument_list|,
name|_
argument_list|(
literal|"Define Polygon area"
argument_list|)
argument_list|,
name|polygon_clicked
argument_list|,
name|NULL
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
name|_tools
operator|.
name|edit
operator|=
name|make_toolbar_icon
argument_list|(
name|toolbar
argument_list|,
name|window
argument_list|,
name|edit_xpm
argument_list|,
literal|"Edit"
argument_list|,
name|_
argument_list|(
literal|"Edit selected area info"
argument_list|)
argument_list|,
name|tools_command
argument_list|,
operator|&
name|_tools
operator|.
name|cmd_edit
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
name|_tools
operator|.
name|delete
operator|=
name|make_toolbar_icon
argument_list|(
name|toolbar
argument_list|,
name|window
argument_list|,
name|delete_xpm
argument_list|,
literal|"Delete"
argument_list|,
name|_
argument_list|(
literal|"Delete selected area"
argument_list|)
argument_list|,
name|tools_command
argument_list|,
operator|&
name|_tools
operator|.
name|cmd_delete
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
name|tools_set_sensitive
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
name|set_arrow_func
argument_list|()
expr_stmt|;
return|return
operator|&
name|_tools
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tools_select (GtkWidget * widget)
name|tools_select
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|_callback_lock
operator|=
name|TRUE
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_select_arrow (void)
name|tools_select_arrow
parameter_list|(
name|void
parameter_list|)
block|{
name|tools_select
argument_list|(
name|_tools
operator|.
name|arrow
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_select_rectangle (void)
name|tools_select_rectangle
parameter_list|(
name|void
parameter_list|)
block|{
name|tools_select
argument_list|(
name|_tools
operator|.
name|rectangle
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_select_circle (void)
name|tools_select_circle
parameter_list|(
name|void
parameter_list|)
block|{
name|tools_select
argument_list|(
name|_tools
operator|.
name|circle
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_select_polygon (void)
name|tools_select_polygon
parameter_list|(
name|void
parameter_list|)
block|{
name|tools_select
argument_list|(
name|_tools
operator|.
name|polygon
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_set_sensitive (gboolean sensitive)
name|tools_set_sensitive
parameter_list|(
name|gboolean
name|sensitive
parameter_list|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|_tools
operator|.
name|edit
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|_tools
operator|.
name|delete
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

