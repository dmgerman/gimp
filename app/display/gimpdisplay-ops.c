begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"actionarea.h"
end_include

begin_include
include|#
directive|include
file|"colormaps.h"
end_include

begin_include
include|#
directive|include
file|"cursorutil.h"
end_include

begin_include
include|#
directive|include
file|"fileops.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay_ops.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"gximage.h"
end_include

begin_include
include|#
directive|include
file|"interface.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"scale.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_function_decl
specifier|static
name|void
name|gdisplay_close_warning_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gdisplay_cancel_warning_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gdisplay_close_warning_dialog
parameter_list|(
name|char
modifier|*
parameter_list|,
name|GDisplay
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|warning_dialog
specifier|static
name|GtkWidget
modifier|*
name|warning_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  *  This file is for operations on the gdisplay object  */
end_comment

begin_function
name|gulong
DECL|function|gdisplay_white_pixel (GDisplay * gdisp)
name|gdisplay_white_pixel
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
return|return
name|g_white_pixel
return|;
block|}
end_function

begin_function
name|gulong
DECL|function|gdisplay_gray_pixel (GDisplay * gdisp)
name|gdisplay_gray_pixel
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
return|return
name|g_gray_pixel
return|;
block|}
end_function

begin_function
name|gulong
DECL|function|gdisplay_black_pixel (GDisplay * gdisp)
name|gdisplay_black_pixel
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
return|return
name|g_black_pixel
return|;
block|}
end_function

begin_function
name|gulong
DECL|function|gdisplay_color_pixel (GDisplay * gdisp)
name|gdisplay_color_pixel
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
return|return
name|g_color_pixel
return|;
block|}
end_function

begin_function
name|void
DECL|function|gdisplay_new_view (GDisplay * gdisp)
name|gdisplay_new_view
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GDisplay
modifier|*
name|new_gdisp
decl_stmt|;
comment|/* make sure the image has been fully loaded... */
if|if
condition|(
name|gdisp
operator|->
name|gimage
condition|)
block|{
name|new_gdisp
operator|=
name|gdisplay_new
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|gdisp
operator|->
name|scale
argument_list|)
expr_stmt|;
name|new_gdisp
operator|->
name|scale
operator|=
name|gdisp
operator|->
name|scale
expr_stmt|;
name|new_gdisp
operator|->
name|offset_x
operator|=
name|gdisp
operator|->
name|offset_x
expr_stmt|;
name|new_gdisp
operator|->
name|offset_y
operator|=
name|gdisp
operator|->
name|offset_y
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gdisplay_close_window (GDisplay * gdisp,int kill_it)
name|gdisplay_close_window
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|int
name|kill_it
parameter_list|)
block|{
comment|/*  If the image has been modified, give the user a chance to save    *  it before nuking it--this only applies if its the last view    *  to an image canvas.  (a gimage with ref_count = 1)    */
if|if
condition|(
operator|!
name|kill_it
operator|&&
operator|(
name|gdisp
operator|->
name|gimage
operator|->
name|ref_count
operator|==
literal|1
operator|)
operator|&&
operator|(
name|gdisp
operator|->
name|gimage
operator|->
name|dirty
operator|>
literal|0
operator|)
operator|&&
name|confirm_on_close
condition|)
name|gdisplay_close_warning_dialog
argument_list|(
name|prune_filename
argument_list|(
name|gimage_filename
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
else|else
block|{
comment|/* If POPUP_SHELL references this shell, then reset it. */
if|if
condition|(
name|popup_shell
operator|==
name|gdisp
operator|->
name|shell
condition|)
name|popup_shell
operator|=
name|NULL
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gdisplay_shrink_wrap (GDisplay * gdisp)
name|gdisplay_shrink_wrap
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|disp_width
decl_stmt|,
name|disp_height
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|shell_x
decl_stmt|,
name|shell_y
decl_stmt|;
name|gint
name|shell_width
decl_stmt|,
name|shell_height
decl_stmt|;
name|gint
name|max_auto_width
decl_stmt|,
name|max_auto_height
decl_stmt|;
name|gint
name|border_x
decl_stmt|,
name|border_y
decl_stmt|;
name|int
name|s_width
decl_stmt|,
name|s_height
decl_stmt|;
name|s_width
operator|=
name|gdk_screen_width
argument_list|()
expr_stmt|;
name|s_height
operator|=
name|gdk_screen_height
argument_list|()
expr_stmt|;
name|width
operator|=
name|SCALE
argument_list|(
name|gdisp
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|height
operator|=
name|SCALE
argument_list|(
name|gdisp
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|disp_width
operator|=
name|gdisp
operator|->
name|disp_width
expr_stmt|;
name|disp_height
operator|=
name|gdisp
operator|->
name|disp_height
expr_stmt|;
name|shell_width
operator|=
name|gdisp
operator|->
name|shell
operator|->
name|allocation
operator|.
name|width
expr_stmt|;
name|shell_height
operator|=
name|gdisp
operator|->
name|shell
operator|->
name|allocation
operator|.
name|height
expr_stmt|;
name|border_x
operator|=
name|shell_width
operator|-
name|disp_width
expr_stmt|;
name|border_y
operator|=
name|shell_height
operator|-
name|disp_height
expr_stmt|;
name|max_auto_width
operator|=
operator|(
name|s_width
operator|-
name|border_x
operator|)
operator|*
literal|0.75
expr_stmt|;
name|max_auto_height
operator|=
operator|(
name|s_height
operator|-
name|border_y
operator|)
operator|*
literal|0.75
expr_stmt|;
comment|/*  If 1) the projected width& height are smaller than screen size,&    *     2) the current display size isn't already the desired size, expand    */
if|if
condition|(
operator|(
operator|(
name|width
operator|+
name|border_x
operator|)
operator|<
name|s_width
operator|||
operator|(
name|height
operator|+
name|border_y
operator|)
operator|<
name|s_height
operator|)
operator|&&
operator|(
name|width
operator|!=
name|disp_width
operator|||
name|height
operator|!=
name|disp_height
operator|)
condition|)
block|{
name|width
operator|=
operator|(
operator|(
name|width
operator|+
name|border_x
operator|)
operator|<
name|s_width
operator|)
condition|?
name|width
else|:
name|max_auto_width
expr_stmt|;
name|height
operator|=
operator|(
operator|(
name|height
operator|+
name|border_y
operator|)
operator|<
name|s_height
operator|)
condition|?
name|height
else|:
name|max_auto_height
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|gdisp
operator|->
name|canvas
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gdisp
operator|->
name|canvas
argument_list|)
expr_stmt|;
name|gdk_window_get_origin
argument_list|(
name|gdisp
operator|->
name|shell
operator|->
name|window
argument_list|,
operator|&
name|shell_x
argument_list|,
operator|&
name|shell_y
argument_list|)
expr_stmt|;
name|shell_width
operator|=
name|width
operator|+
name|border_x
expr_stmt|;
name|shell_height
operator|=
name|height
operator|+
name|border_y
expr_stmt|;
name|x
operator|=
name|HIGHPASS
argument_list|(
name|shell_x
argument_list|,
name|BOUNDS
argument_list|(
name|s_width
operator|-
name|shell_width
argument_list|,
name|border_x
argument_list|,
name|s_width
argument_list|)
argument_list|)
expr_stmt|;
name|y
operator|=
name|HIGHPASS
argument_list|(
name|shell_y
argument_list|,
name|BOUNDS
argument_list|(
name|s_height
operator|-
name|shell_height
argument_list|,
name|border_y
argument_list|,
name|s_height
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|!=
name|shell_x
operator|||
name|y
operator|!=
name|shell_y
condition|)
name|gdk_window_move
argument_list|(
name|gdisp
operator|->
name|shell
operator|->
name|window
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
comment|/*  Set the new disp_width and disp_height values  */
name|gdisp
operator|->
name|disp_width
operator|=
name|width
expr_stmt|;
name|gdisp
operator|->
name|disp_height
operator|=
name|height
expr_stmt|;
block|}
comment|/*  If the projected width is greater than current, but less than    *  3/4 of the screen size, expand automagically    */
elseif|else
if|if
condition|(
operator|(
name|width
operator|>
name|disp_width
operator|||
name|height
operator|>
name|disp_height
operator|)
operator|&&
operator|(
name|disp_width
operator|<
name|max_auto_width
operator|||
name|disp_height
operator|<
name|max_auto_height
operator|)
condition|)
block|{
name|max_auto_width
operator|=
name|MINIMUM
argument_list|(
name|max_auto_width
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|max_auto_height
operator|=
name|MINIMUM
argument_list|(
name|max_auto_height
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|gdisp
operator|->
name|canvas
argument_list|,
name|max_auto_width
argument_list|,
name|max_auto_height
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gdisp
operator|->
name|canvas
argument_list|)
expr_stmt|;
name|gdk_window_get_origin
argument_list|(
name|gdisp
operator|->
name|shell
operator|->
name|window
argument_list|,
operator|&
name|shell_x
argument_list|,
operator|&
name|shell_y
argument_list|)
expr_stmt|;
name|shell_width
operator|=
name|width
operator|+
name|border_x
expr_stmt|;
name|shell_height
operator|=
name|height
operator|+
name|border_y
expr_stmt|;
name|x
operator|=
name|HIGHPASS
argument_list|(
name|shell_x
argument_list|,
name|BOUNDS
argument_list|(
name|s_width
operator|-
name|shell_width
argument_list|,
name|border_x
argument_list|,
name|s_width
argument_list|)
argument_list|)
expr_stmt|;
name|y
operator|=
name|HIGHPASS
argument_list|(
name|shell_y
argument_list|,
name|BOUNDS
argument_list|(
name|s_height
operator|-
name|shell_height
argument_list|,
name|border_y
argument_list|,
name|s_height
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|!=
name|shell_x
operator|||
name|y
operator|!=
name|shell_y
condition|)
name|gdk_window_move
argument_list|(
name|gdisp
operator|->
name|shell
operator|->
name|window
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
comment|/*  Set the new disp_width and disp_height values  */
name|gdisp
operator|->
name|disp_width
operator|=
name|max_auto_width
expr_stmt|;
name|gdisp
operator|->
name|disp_height
operator|=
name|max_auto_height
expr_stmt|;
block|}
comment|/*  Otherwise, reexpose by hand to reflect changes  */
else|else
name|gdisplay_expose_full
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
comment|/*  If the width or height of the display has changed, recalculate    *  the display offsets...    */
if|if
condition|(
name|disp_width
operator|!=
name|gdisp
operator|->
name|disp_width
operator|||
name|disp_height
operator|!=
name|gdisp
operator|->
name|disp_height
condition|)
block|{
name|gdisp
operator|->
name|offset_x
operator|+=
operator|(
name|disp_width
operator|-
name|gdisp
operator|->
name|disp_width
operator|)
operator|/
literal|2
expr_stmt|;
name|gdisp
operator|->
name|offset_y
operator|+=
operator|(
name|disp_height
operator|-
name|gdisp
operator|->
name|disp_height
operator|)
operator|/
literal|2
expr_stmt|;
name|bounds_checking
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|int
DECL|function|gdisplay_resize_image (GDisplay * gdisp)
name|gdisplay_resize_image
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|int
name|sx
decl_stmt|,
name|sy
decl_stmt|;
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
comment|/*  Calculate the width and height of the new canvas  */
name|sx
operator|=
name|SCALE
argument_list|(
name|gdisp
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|sy
operator|=
name|SCALE
argument_list|(
name|gdisp
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|width
operator|=
name|HIGHPASS
argument_list|(
name|sx
argument_list|,
name|gdisp
operator|->
name|disp_width
argument_list|)
expr_stmt|;
name|height
operator|=
name|HIGHPASS
argument_list|(
name|sy
argument_list|,
name|gdisp
operator|->
name|disp_height
argument_list|)
expr_stmt|;
comment|/* if the new dimensions of the ximage are different than the old...resize */
if|if
condition|(
name|width
operator|!=
name|gdisp
operator|->
name|disp_width
operator|||
name|height
operator|!=
name|gdisp
operator|->
name|disp_height
condition|)
block|{
comment|/*  adjust the gdisplay offsets -- we need to set them so that the        *  center of our viewport is at the center of the image.        */
name|gdisp
operator|->
name|offset_x
operator|=
operator|(
name|sx
operator|/
literal|2
operator|)
operator|-
operator|(
name|width
operator|/
literal|2
operator|)
expr_stmt|;
name|gdisp
operator|->
name|offset_y
operator|=
operator|(
name|sy
operator|/
literal|2
operator|)
operator|-
operator|(
name|height
operator|/
literal|2
operator|)
expr_stmt|;
name|gdisp
operator|->
name|disp_width
operator|=
name|width
expr_stmt|;
name|gdisp
operator|->
name|disp_height
operator|=
name|height
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|gdisp
operator|->
name|canvas
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|gdisp
operator|->
name|canvas
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|gdisp
operator|->
name|canvas
argument_list|,
name|gdisp
operator|->
name|disp_width
argument_list|,
name|gdisp
operator|->
name|disp_height
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gdisp
operator|->
name|canvas
argument_list|)
expr_stmt|;
block|}
return|return
literal|1
return|;
block|}
end_function

begin_comment
comment|/********************************************************  *   Routines to query before closing a dirty image     *  ********************************************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|gdisplay_close_warning_callback (GtkWidget * w,gpointer client_data)
name|gdisplay_close_warning_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GtkWidget
modifier|*
name|mbox
decl_stmt|;
name|menus_set_sensitive
argument_list|(
literal|"<Image>/File/Close"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|mbox
operator|=
operator|(
name|GtkWidget
operator|*
operator|)
name|client_data
expr_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gtk_object_get_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|mbox
argument_list|)
argument_list|)
expr_stmt|;
comment|/* If POPUP_SHELL references this shell, then reset it. */
if|if
condition|(
name|popup_shell
operator|==
name|gdisp
operator|->
name|shell
condition|)
name|popup_shell
operator|=
name|NULL
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|mbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gdisplay_cancel_warning_callback (GtkWidget * w,gpointer client_data)
name|gdisplay_cancel_warning_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|mbox
decl_stmt|;
name|menus_set_sensitive
argument_list|(
literal|"<Image>/File/Close"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|mbox
operator|=
operator|(
name|GtkWidget
operator|*
operator|)
name|client_data
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|mbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gdisplay_delete_warning_callback (GtkWidget * widget,GdkEvent * event,gpointer client_data)
name|gdisplay_delete_warning_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|menus_set_sensitive
argument_list|(
literal|"<Image>/File/Close"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gdisplay_destroy_warning_callback (GtkWidget * widget,gpointer client_data)
name|gdisplay_destroy_warning_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|warning_dialog
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gdisplay_close_warning_dialog (char * image_name,GDisplay * gdisp)
name|gdisplay_close_warning_dialog
parameter_list|(
name|char
modifier|*
name|image_name
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
specifier|static
name|ActionAreaItem
name|mbox_action_items
index|[
literal|2
index|]
init|=
block|{
block|{
literal|"Close"
block|,
name|gdisplay_close_warning_callback
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
literal|"Cancel"
block|,
name|gdisplay_cancel_warning_callback
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
name|GtkWidget
modifier|*
name|mbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|char
modifier|*
name|warning_buf
decl_stmt|;
comment|/* FIXUP this will raise any prexsisting close dialogs, which can be a      a bit confusing if you tried to close a new window because you had      forgotten the old dialog was still around */
comment|/* If a warning dialog already exists raise the window and get out */
if|if
condition|(
name|warning_dialog
operator|!=
name|NULL
condition|)
block|{
name|gdk_window_raise
argument_list|(
name|warning_dialog
operator|->
name|window
argument_list|)
expr_stmt|;
return|return;
block|}
name|menus_set_sensitive
argument_list|(
literal|"<Image>/File/Close"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|warning_dialog
operator|=
name|mbox
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
comment|/* should this be image_window or the actual image name??? */
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|mbox
argument_list|)
argument_list|,
literal|"really_close"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|mbox
argument_list|)
argument_list|,
name|image_name
argument_list|)
expr_stmt|;
name|gtk_window_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|mbox
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_object_set_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|mbox
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|mbox
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gdisplay_delete_warning_callback
argument_list|)
argument_list|,
name|mbox
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|mbox
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gdisplay_destroy_warning_callback
argument_list|)
argument_list|,
name|mbox
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|mbox
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|warning_buf
operator|=
operator|(
name|char
operator|*
operator|)
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|image_name
argument_list|)
operator|+
literal|50
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|warning_buf
argument_list|,
literal|"Changes made to %s.  Close anyway?"
argument_list|,
name|image_name
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|warning_buf
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|warning_buf
argument_list|)
expr_stmt|;
name|mbox_action_items
index|[
literal|0
index|]
operator|.
name|user_data
operator|=
name|mbox
expr_stmt|;
name|mbox_action_items
index|[
literal|1
index|]
operator|.
name|user_data
operator|=
name|mbox
expr_stmt|;
name|build_action_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|mbox
argument_list|)
argument_list|,
name|mbox_action_items
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|mbox
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

