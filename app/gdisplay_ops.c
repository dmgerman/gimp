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
file|"appenv.h"
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
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"gximage.h"
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

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gdisplay_close_warning_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|close
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gdisplay_close_warning_dialog
parameter_list|(
name|gchar
modifier|*
name|image_name
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

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
DECL|function|gdisplay_xserver_resolution (gdouble * xres,gdouble * yres)
name|gdisplay_xserver_resolution
parameter_list|(
name|gdouble
modifier|*
name|xres
parameter_list|,
name|gdouble
modifier|*
name|yres
parameter_list|)
block|{
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|widthMM
decl_stmt|,
name|heightMM
decl_stmt|;
name|width
operator|=
name|gdk_screen_width
argument_list|()
expr_stmt|;
name|height
operator|=
name|gdk_screen_height
argument_list|()
expr_stmt|;
name|widthMM
operator|=
name|gdk_screen_width_mm
argument_list|()
expr_stmt|;
name|heightMM
operator|=
name|gdk_screen_height_mm
argument_list|()
expr_stmt|;
comment|/*    * From xdpyinfo.c:    *    * there are 2.54 centimeters to an inch; so there are 25.4 millimeters.    *    *     dpi = N pixels / (M millimeters / (25.4 millimeters / 1 inch))    *         = N pixels / (M inch / 25.4)    *         = N * 25.4 pixels / M inch    */
operator|*
name|xres
operator|=
operator|(
name|width
operator|*
literal|25.4
operator|)
operator|/
operator|(
operator|(
name|gdouble
operator|)
name|widthMM
operator|)
expr_stmt|;
operator|*
name|yres
operator|=
operator|(
name|height
operator|*
literal|25.4
operator|)
operator|/
operator|(
operator|(
name|gdouble
operator|)
name|heightMM
operator|)
expr_stmt|;
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
block|}
block|}
end_function

begin_function
name|void
DECL|function|gdisplay_close_window (GDisplay * gdisp,gboolean kill_it)
name|gdisplay_close_window
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|gboolean
name|kill_it
parameter_list|)
block|{
comment|/*  FIXME: gimp_busy HACK not really appropriate here because we only    *  want to prevent the busy image and display to be closed.  --Mitch    */
if|if
condition|(
name|gimp_busy
condition|)
return|return;
comment|/*  If the image has been modified, give the user a chance to save    *  it before nuking it--this only applies if its the last view    *  to an image canvas.  (a gimage with disp_count = 1)    */
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
name|disp_count
operator|==
literal|1
operator|)
operator|&&
name|gdisp
operator|->
name|gimage
operator|->
name|dirty
operator|&&
name|confirm_on_close
condition|)
block|{
name|gdisplay_close_warning_dialog
argument_list|(
name|g_basename
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
block|}
else|else
block|{
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
comment|/*     * I'm pretty sure this assumes that the current size is< display size    * Is this a valid assumption?     */
name|GtkAllocation
name|allocation
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
name|gint
name|s_width
decl_stmt|,
name|s_height
decl_stmt|;
name|gboolean
name|resize
init|=
name|FALSE
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
name|SCALEX
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
name|SCALEY
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
name|allocation
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|allocation
operator|.
name|y
operator|=
literal|0
expr_stmt|;
comment|/* If one of the display dimensions has changed and one of the    * dimensions fits inside the screen    */
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
name|resize
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/*  If the projected dimension is greater than current, but less than    *  3/4 of the screen size, expand automagically    */
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
name|width
operator|=
name|MIN
argument_list|(
name|max_auto_width
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|height
operator|=
name|MIN
argument_list|(
name|max_auto_height
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|resize
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
name|resize
condition|)
block|{
if|if
condition|(
name|width
operator|<
name|gdisp
operator|->
name|statusarea
operator|->
name|requisition
operator|.
name|width
condition|)
block|{
name|width
operator|=
name|gdisp
operator|->
name|statusarea
operator|->
name|requisition
operator|.
name|width
expr_stmt|;
block|}
undef|#
directive|undef
name|RESIZE_DEBUG
ifdef|#
directive|ifdef
name|RESIZE_DEBUG
name|g_print
argument_list|(
literal|"1w:%d/%d d:%d/%d s:%d/%d b:%d/%d\n"
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|disp_width
argument_list|,
name|disp_height
argument_list|,
name|shell_width
argument_list|,
name|shell_height
argument_list|,
name|border_x
argument_list|,
name|border_y
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* RESIZE_DEBUG */
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
name|allocation
operator|.
name|width
operator|=
name|width
operator|+
name|border_x
expr_stmt|;
name|allocation
operator|.
name|height
operator|=
name|height
operator|+
name|border_y
expr_stmt|;
comment|/*  don't call gdisplay_canvas_events() on any of the following        *  changes because our caller has to do a full display update anyway        */
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gdisp
operator|->
name|canvas
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|gtk_widget_size_allocate
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|gdk_window_resize
argument_list|(
name|gdisp
operator|->
name|shell
operator|->
name|window
argument_list|,
name|allocation
operator|.
name|width
argument_list|,
name|allocation
operator|.
name|height
argument_list|)
expr_stmt|;
comment|/*  let Gtk/X/WM position the window  */
while|while
condition|(
name|gtk_events_pending
argument_list|()
condition|)
name|gtk_main_iteration
argument_list|()
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
comment|/*  if the window is offscreen, center it...  */
if|if
condition|(
name|shell_x
operator|>
name|s_width
operator|||
name|shell_y
operator|>
name|s_height
operator|||
operator|(
name|shell_x
operator|+
name|width
operator|+
name|border_x
operator|)
operator|<
literal|0
operator|||
operator|(
name|shell_y
operator|+
name|height
operator|+
name|border_y
operator|)
operator|<
literal|0
condition|)
block|{
name|shell_x
operator|=
operator|(
name|s_width
operator|-
name|width
operator|-
name|border_x
operator|)
operator|>>
literal|1
expr_stmt|;
name|shell_y
operator|=
operator|(
name|s_height
operator|-
name|height
operator|-
name|border_y
operator|)
operator|>>
literal|1
expr_stmt|;
name|gdk_window_move
argument_list|(
name|gdisp
operator|->
name|shell
operator|->
name|window
argument_list|,
name|shell_x
argument_list|,
name|shell_y
argument_list|)
expr_stmt|;
block|}
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gdisp
operator|->
name|canvas
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
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
block|}
block|}
end_function

begin_comment
comment|/********************************************************  *   Routines to query before closing a dirty image     *  ********************************************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|gdisplay_close_warning_callback (GtkWidget * widget,gboolean close,gpointer data)
name|gdisplay_close_warning_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|close
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|data
expr_stmt|;
name|gdisp
operator|->
name|warning_dialog
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|close
condition|)
name|gtk_widget_destroy
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gdisplay_close_warning_dialog (gchar * image_name,GDisplay * gdisp)
name|gdisplay_close_warning_dialog
parameter_list|(
name|gchar
modifier|*
name|image_name
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|mbox
decl_stmt|;
name|gchar
modifier|*
name|warning_buf
decl_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|warning_dialog
operator|!=
name|NULL
condition|)
block|{
name|gdk_window_raise
argument_list|(
name|gdisp
operator|->
name|warning_dialog
operator|->
name|window
argument_list|)
expr_stmt|;
return|return;
block|}
name|warning_buf
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Changes were made to %s.\nClose anyway?"
argument_list|)
argument_list|,
name|image_name
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|warning_dialog
operator|=
name|mbox
operator|=
name|gimp_query_boolean_box
argument_list|(
name|image_name
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/really_close.html"
argument_list|,
name|FALSE
argument_list|,
name|warning_buf
argument_list|,
name|_
argument_list|(
literal|"Close"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Cancel"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gdisplay_close_warning_callback
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|warning_buf
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

