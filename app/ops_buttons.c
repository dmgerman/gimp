begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* To do this more elegantly, there should be a GtkWidget pixmap_button,    * probably derived from a simple hbox. It should keep track of the widgets   * sensitivity and draw the related pixmap. This way one could avoid the    * need to have a special function to set sensitivity as you'll find below.               *                                                      (sven@gimp.org)  */
end_comment

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"ops_buttons.h"
end_include

begin_function
DECL|function|ops_button_box_new (GtkWidget * parent,GtkTooltips * tool_tips,OpsButton * ops_buttons)
name|GtkWidget
modifier|*
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
name|ops_buttons
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
name|GdkPixmap
modifier|*
name|is_pixmap
decl_stmt|;
name|GdkBitmap
modifier|*
name|is_mask
decl_stmt|;
name|GtkStyle
modifier|*
name|style
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
name|ops_buttons
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
name|gtk_container_border_width
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
name|ops_buttons
operator|->
name|xpm_data
argument_list|)
expr_stmt|;
name|is_pixmap
operator|=
name|gdk_pixmap_create_from_xpm_d
argument_list|(
name|parent
operator|->
name|window
argument_list|,
operator|&
name|is_mask
argument_list|,
operator|&
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|ops_buttons
operator|->
name|xpm_is_data
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
literal|3
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pixmapwid
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
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
name|ops_buttons
operator|->
name|callback
argument_list|,
name|GTK_OBJECT
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
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
name|ops_buttons
operator|->
name|tooltip
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
name|ops_buttons
operator|->
name|pixmap
operator|=
name|pixmap
expr_stmt|;
name|ops_buttons
operator|->
name|mask
operator|=
name|mask
expr_stmt|;
name|ops_buttons
operator|->
name|is_pixmap
operator|=
name|is_pixmap
expr_stmt|;
name|ops_buttons
operator|->
name|is_mask
operator|=
name|is_mask
expr_stmt|;
name|ops_buttons
operator|->
name|pixmapwid
operator|=
name|pixmapwid
expr_stmt|;
name|ops_buttons
operator|->
name|widget
operator|=
name|button
expr_stmt|;
name|ops_buttons
operator|++
expr_stmt|;
block|}
return|return
operator|(
name|button_box
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|ops_button_box_set_insensitive (OpsButton * ops_buttons)
name|ops_button_box_set_insensitive
parameter_list|(
name|OpsButton
modifier|*
name|ops_buttons
parameter_list|)
block|{
while|while
condition|(
name|ops_buttons
operator|->
name|widget
condition|)
block|{
name|ops_button_set_sensitive
argument_list|(
operator|*
name|ops_buttons
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|ops_buttons
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|ops_button_set_sensitive (OpsButton ops_button,gint sensitive)
name|ops_button_set_sensitive
parameter_list|(
name|OpsButton
name|ops_button
parameter_list|,
name|gint
name|sensitive
parameter_list|)
block|{
name|sensitive
operator|=
operator|(
name|sensitive
operator|!=
name|FALSE
operator|)
expr_stmt|;
if|if
condition|(
name|sensitive
operator|==
operator|(
name|GTK_WIDGET_SENSITIVE
argument_list|(
name|ops_button
operator|.
name|widget
argument_list|)
operator|!=
name|FALSE
operator|)
condition|)
return|return;
if|if
condition|(
name|sensitive
condition|)
name|gtk_pixmap_set
argument_list|(
name|GTK_PIXMAP
argument_list|(
name|ops_button
operator|.
name|pixmapwid
argument_list|)
argument_list|,
name|ops_button
operator|.
name|pixmap
argument_list|,
name|ops_button
operator|.
name|mask
argument_list|)
expr_stmt|;
else|else
name|gtk_pixmap_set
argument_list|(
name|GTK_PIXMAP
argument_list|(
name|ops_button
operator|.
name|pixmapwid
argument_list|)
argument_list|,
name|ops_button
operator|.
name|is_pixmap
argument_list|,
name|ops_button
operator|.
name|is_mask
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|ops_button
operator|.
name|widget
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

