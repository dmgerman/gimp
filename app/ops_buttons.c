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
file|"ops_buttons.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
name|void
name|ops_button_pressed_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|GdkEventButton
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ops_button_extended_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GtkWidget
modifier|*
DECL|function|ops_button_box_new (GtkWidget * parent,GtkTooltips * tool_tips,OpsButton * ops_button,OpsButtonType ops_type)
name|ops_button_box_new
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GtkTooltips
modifier|*
name|tool_tips
parameter_list|,
name|OpsButton
modifier|*
name|ops_button
parameter_list|,
name|OpsButtonType
name|ops_type
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|button_box
decl_stmt|;
name|GtkWidget
modifier|*
name|box
decl_stmt|;
name|GtkWidget
modifier|*
name|pixmapwid
decl_stmt|;
name|GdkPixmap
modifier|*
name|pixmap
decl_stmt|;
name|GdkBitmap
modifier|*
name|mask
decl_stmt|;
name|GtkStyle
modifier|*
name|style
decl_stmt|;
name|GSList
modifier|*
name|group
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|box_list
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|gint
name|max_width
init|=
literal|0
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gtk_widget_realize
argument_list|(
name|parent
argument_list|)
expr_stmt|;
name|style
operator|=
name|gtk_widget_get_style
argument_list|(
name|parent
argument_list|)
expr_stmt|;
name|button_box
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
while|while
condition|(
name|ops_button
operator|->
name|xpm_data
condition|)
block|{
name|box
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|box
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|pixmap
operator|=
name|gdk_pixmap_create_from_xpm_d
argument_list|(
name|parent
operator|->
name|window
argument_list|,
operator|&
name|mask
argument_list|,
operator|&
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|ops_button
operator|->
name|xpm_data
argument_list|)
expr_stmt|;
name|gdk_window_get_size
argument_list|(
name|pixmap
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|max_width
operator|=
name|MAX
argument_list|(
name|max_width
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|pixmapwid
operator|=
name|gtk_pixmap_new
argument_list|(
name|pixmap
argument_list|,
name|mask
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|pixmapwid
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pixmapwid
argument_list|)
expr_stmt|;
name|box_list
operator|=
name|g_slist_prepend
argument_list|(
name|box_list
argument_list|,
name|box
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|ops_type
condition|)
block|{
case|case
name|OPS_BUTTON_NORMAL
case|:
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
break|break;
case|case
name|OPS_BUTTON_RADIO
case|:
name|button
operator|=
name|gtk_radio_button_new
argument_list|(
name|group
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_mode
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
break|break;
default|default :
name|button
operator|=
name|NULL
expr_stmt|;
comment|/*stop compiler complaints */
name|g_error
argument_list|(
literal|"ops_button_box_new: unknown type %d\n"
argument_list|,
name|ops_type
argument_list|)
expr_stmt|;
break|break;
block|}
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
if|if
condition|(
name|ops_button
operator|->
name|ext_callbacks
operator|==
name|NULL
condition|)
block|{
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|ops_button
operator|->
name|callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"button_press_event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|ops_button_pressed_callback
argument_list|,
name|ops_button
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|ops_button_extended_callback
argument_list|,
name|ops_button
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|tool_tips
operator|!=
name|NULL
condition|)
name|gtk_tooltips_set_tip
argument_list|(
name|tool_tips
argument_list|,
name|button
argument_list|,
name|gettext
argument_list|(
name|ops_button
operator|->
name|tooltip
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|button_box
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|ops_button
operator|->
name|widget
operator|=
name|button
expr_stmt|;
name|ops_button
operator|->
name|modifier
operator|=
name|OPS_BUTTON_MODIFIER_NONE
expr_stmt|;
name|ops_button
operator|++
expr_stmt|;
block|}
for|for
control|(
name|list
operator|=
name|box_list
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|gtk_widget_set_usize
argument_list|(
name|GTK_WIDGET
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|,
name|max_width
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|box_list
argument_list|)
expr_stmt|;
return|return
operator|(
name|button_box
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|ops_button_box_set_insensitive (OpsButton * ops_button)
name|ops_button_box_set_insensitive
parameter_list|(
name|OpsButton
modifier|*
name|ops_button
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|ops_button
operator|!=
name|NULL
argument_list|)
expr_stmt|;
while|while
condition|(
name|ops_button
operator|->
name|widget
condition|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|ops_button
operator|->
name|widget
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|ops_button
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|ops_button_pressed_callback (GtkWidget * widget,GdkEventButton * bevent,gpointer client_data)
name|ops_button_pressed_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|OpsButton
modifier|*
name|ops_button
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|client_data
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|ops_button
operator|=
operator|(
name|OpsButton
operator|*
operator|)
name|client_data
expr_stmt|;
if|if
condition|(
name|bevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
if|if
condition|(
name|bevent
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
name|ops_button
operator|->
name|modifier
operator|=
name|OPS_BUTTON_MODIFIER_SHIFT_CTRL
expr_stmt|;
else|else
name|ops_button
operator|->
name|modifier
operator|=
name|OPS_BUTTON_MODIFIER_SHIFT
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|bevent
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
name|ops_button
operator|->
name|modifier
operator|=
name|OPS_BUTTON_MODIFIER_CTRL
expr_stmt|;
elseif|else
if|if
condition|(
name|bevent
operator|->
name|state
operator|&
name|GDK_MOD1_MASK
condition|)
name|ops_button
operator|->
name|modifier
operator|=
name|OPS_BUTTON_MODIFIER_ALT
expr_stmt|;
else|else
name|ops_button
operator|->
name|modifier
operator|=
name|OPS_BUTTON_MODIFIER_NONE
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|ops_button_extended_callback (GtkWidget * widget,gpointer client_data)
name|ops_button_extended_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|OpsButton
modifier|*
name|ops_button
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|client_data
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|ops_button
operator|=
operator|(
name|OpsButton
operator|*
operator|)
name|client_data
expr_stmt|;
if|if
condition|(
name|ops_button
operator|->
name|modifier
operator|>
name|OPS_BUTTON_MODIFIER_NONE
operator|&&
name|ops_button
operator|->
name|modifier
operator|<
name|OPS_BUTTON_MODIFIER_LAST
condition|)
block|{
if|if
condition|(
name|ops_button
operator|->
name|ext_callbacks
index|[
name|ops_button
operator|->
name|modifier
operator|-
literal|1
index|]
operator|!=
name|NULL
condition|)
operator|(
name|ops_button
operator|->
name|ext_callbacks
index|[
name|ops_button
operator|->
name|modifier
operator|-
literal|1
index|]
operator|)
operator|(
name|widget
operator|,
name|NULL
operator|)
expr_stmt|;
else|else
call|(
name|ops_button
operator|->
name|callback
call|)
argument_list|(
name|widget
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
call|(
name|ops_button
operator|->
name|callback
call|)
argument_list|(
name|widget
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ops_button
operator|->
name|modifier
operator|=
name|OPS_BUTTON_MODIFIER_NONE
expr_stmt|;
block|}
end_function

end_unit

