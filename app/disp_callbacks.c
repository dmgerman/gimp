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
file|"gdk/gdkkeysyms.h"
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
file|"devices.h"
end_include

begin_include
include|#
directive|include
file|"disp_callbacks.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"interface.h"
end_include

begin_include
include|#
directive|include
file|"layer_select.h"
end_include

begin_include
include|#
directive|include
file|"move.h"
end_include

begin_include
include|#
directive|include
file|"scale.h"
end_include

begin_include
include|#
directive|include
file|"scroll.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_define
DECL|macro|HORIZONTAL
define|#
directive|define
name|HORIZONTAL
value|1
end_define

begin_define
DECL|macro|VERTICAL
define|#
directive|define
name|VERTICAL
value|2
end_define

begin_comment
comment|/* Function declarations */
end_comment

begin_function_decl
specifier|static
name|void
name|gdisplay_check_device_cursor
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|redraw (GDisplay * gdisp,int x,int y,int w,int h)
name|redraw
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|)
block|{
name|long
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  coordinate of rectangle corners  */
name|x1
operator|=
name|x
expr_stmt|;
name|y1
operator|=
name|y
expr_stmt|;
name|x2
operator|=
operator|(
name|x
operator|+
name|w
operator|)
expr_stmt|;
name|y2
operator|=
operator|(
name|y
operator|+
name|h
operator|)
expr_stmt|;
name|x1
operator|=
name|BOUNDS
argument_list|(
name|x1
argument_list|,
literal|0
argument_list|,
name|gdisp
operator|->
name|disp_width
argument_list|)
expr_stmt|;
name|y1
operator|=
name|BOUNDS
argument_list|(
name|y1
argument_list|,
literal|0
argument_list|,
name|gdisp
operator|->
name|disp_height
argument_list|)
expr_stmt|;
name|x2
operator|=
name|BOUNDS
argument_list|(
name|x2
argument_list|,
literal|0
argument_list|,
name|gdisp
operator|->
name|disp_width
argument_list|)
expr_stmt|;
name|y2
operator|=
name|BOUNDS
argument_list|(
name|y2
argument_list|,
literal|0
argument_list|,
name|gdisp
operator|->
name|disp_height
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|x2
operator|-
name|x1
operator|)
operator|&&
operator|(
name|y2
operator|-
name|y1
operator|)
condition|)
block|{
name|gdisplay_expose_area
argument_list|(
name|gdisp
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gdisplay_check_device_cursor (GDisplay * gdisp)
name|gdisplay_check_device_cursor
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GList
modifier|*
name|tmp_list
decl_stmt|;
comment|/* gdk_input_list_devices returns an internal list, so we shouldn't      free it afterwards */
name|tmp_list
operator|=
name|gdk_input_list_devices
argument_list|()
expr_stmt|;
while|while
condition|(
name|tmp_list
condition|)
block|{
name|GdkDeviceInfo
modifier|*
name|info
init|=
operator|(
name|GdkDeviceInfo
operator|*
operator|)
name|tmp_list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|info
operator|->
name|deviceid
operator|==
name|current_device
condition|)
block|{
name|gdisp
operator|->
name|draw_cursor
operator|=
operator|!
name|info
operator|->
name|has_cursor
expr_stmt|;
break|break;
block|}
name|tmp_list
operator|=
name|tmp_list
operator|->
name|next
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gint
DECL|function|gdisplay_canvas_events (GtkWidget * canvas,GdkEvent * event)
name|gdisplay_canvas_events
parameter_list|(
name|GtkWidget
modifier|*
name|canvas
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GdkEventExpose
modifier|*
name|eevent
decl_stmt|;
name|GdkEventMotion
modifier|*
name|mevent
decl_stmt|;
name|GdkEventButton
modifier|*
name|bevent
decl_stmt|;
name|GdkEventKey
modifier|*
name|kevent
decl_stmt|;
name|gdouble
name|tx
decl_stmt|,
name|ty
decl_stmt|;
name|guint
name|state
init|=
literal|0
decl_stmt|;
name|gint
name|return_val
init|=
name|FALSE
decl_stmt|;
specifier|static
name|gboolean
name|scrolled
init|=
name|FALSE
decl_stmt|;
specifier|static
name|guint
name|key_signal_id
init|=
literal|0
decl_stmt|;
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
name|canvas
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|canvas
operator|->
name|window
condition|)
return|return
name|FALSE
return|;
comment|/*  If this is the first event...  */
if|if
condition|(
operator|!
name|gdisp
operator|->
name|select
condition|)
block|{
comment|/*  create the selection object  */
name|gdisp
operator|->
name|select
operator|=
name|selection_create
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|gdisp
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|,
name|marching_speed
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|disp_width
operator|=
name|gdisp
operator|->
name|canvas
operator|->
name|allocation
operator|.
name|width
expr_stmt|;
name|gdisp
operator|->
name|disp_height
operator|=
name|gdisp
operator|->
name|canvas
operator|->
name|allocation
operator|.
name|height
expr_stmt|;
comment|/*  create GC for scrolling */
name|gdisp
operator|->
name|scroll_gc
operator|=
name|gdk_gc_new
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|)
expr_stmt|;
name|gdk_gc_set_exposures
argument_list|(
name|gdisp
operator|->
name|scroll_gc
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  set up the scrollbar observers  */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gdisp
operator|->
name|hsbdata
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|scrollbar_horz_update
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gdisp
operator|->
name|vsbdata
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|scrollbar_vert_update
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
comment|/*  setup scale properly  */
name|setup_scale
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
comment|/* Find out what device the event occurred upon */
if|if
condition|(
name|devices_check_change
argument_list|(
name|event
argument_list|)
condition|)
name|gdisplay_check_device_cursor
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|event
operator|->
name|type
condition|)
block|{
case|case
name|GDK_EXPOSE
case|:
name|eevent
operator|=
operator|(
name|GdkEventExpose
operator|*
operator|)
name|event
expr_stmt|;
name|redraw
argument_list|(
name|gdisp
argument_list|,
name|eevent
operator|->
name|area
operator|.
name|x
argument_list|,
name|eevent
operator|->
name|area
operator|.
name|y
argument_list|,
name|eevent
operator|->
name|area
operator|.
name|width
argument_list|,
name|eevent
operator|->
name|area
operator|.
name|height
argument_list|)
expr_stmt|;
break|break;
case|case
name|GDK_CONFIGURE
case|:
if|if
condition|(
operator|(
name|gdisp
operator|->
name|disp_width
operator|!=
name|gdisp
operator|->
name|canvas
operator|->
name|allocation
operator|.
name|width
operator|)
operator|||
operator|(
name|gdisp
operator|->
name|disp_height
operator|!=
name|gdisp
operator|->
name|canvas
operator|->
name|allocation
operator|.
name|height
operator|)
condition|)
block|{
name|gdisp
operator|->
name|disp_width
operator|=
name|gdisp
operator|->
name|canvas
operator|->
name|allocation
operator|.
name|width
expr_stmt|;
name|gdisp
operator|->
name|disp_height
operator|=
name|gdisp
operator|->
name|canvas
operator|->
name|allocation
operator|.
name|height
expr_stmt|;
name|resize_display
argument_list|(
name|gdisp
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GDK_LEAVE_NOTIFY
case|:
name|gdisp
operator|->
name|proximity
operator|=
name|FALSE
expr_stmt|;
name|gdisplay_update_cursor
argument_list|(
name|gdisp
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GDK_PROXIMITY_OUT
case|:
name|gdisp
operator|->
name|proximity
operator|=
name|FALSE
expr_stmt|;
name|gdisplay_update_cursor
argument_list|(
name|gdisp
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GDK_BUTTON_PRESS
case|:
name|bevent
operator|=
operator|(
name|GdkEventButton
operator|*
operator|)
name|event
expr_stmt|;
name|state
operator|=
name|bevent
operator|->
name|state
expr_stmt|;
switch|switch
condition|(
name|bevent
operator|->
name|button
condition|)
block|{
case|case
literal|1
case|:
name|gtk_grab_add
argument_list|(
name|canvas
argument_list|)
expr_stmt|;
comment|/* This is a hack to prevent other stuff being run in the middle of 	     a tool operation (like changing image types.... brrrr). We just 	     block all the keypress event. A better solution is to implement 	     some sort of locking for images. 	     Note that this is dependent on specific GTK behavior, and isn't 	     guaranteed to work in future versions of GTK. 	     -Yosh 	   */
if|if
condition|(
name|key_signal_id
operator|==
literal|0
condition|)
name|key_signal_id
operator|=
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|canvas
argument_list|)
argument_list|,
literal|"key_press_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_true
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|active_tool
operator|&&
operator|(
operator|(
name|active_tool
operator|->
name|type
operator|==
name|MOVE
operator|)
operator|||
operator|!
name|gimage_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|)
condition|)
block|{
if|if
condition|(
name|active_tool
operator|->
name|auto_snap_to
condition|)
block|{
name|gdisplay_snap_point
argument_list|(
name|gdisp
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|,
operator|&
name|tx
argument_list|,
operator|&
name|ty
argument_list|)
expr_stmt|;
name|bevent
operator|->
name|x
operator|=
name|tx
expr_stmt|;
name|bevent
operator|->
name|y
operator|=
name|ty
expr_stmt|;
block|}
comment|/* reset the current tool if we're changing gdisplays */
comment|/* 		if (active_tool->gdisp_ptr) { 		  tool_gdisp = active_tool->gdisp_ptr; 		  if (tool_gdisp->ID != gdisp->ID) { 		    tools_initialize (active_tool->type, gdisp); 		    active_tool->drawable = gimage_active_drawable(gdisp->gimage); 		  } 		} else 		*/
comment|/* reset the current tool if we're changing drawables */
if|if
condition|(
name|active_tool
operator|->
name|drawable
condition|)
block|{
if|if
condition|(
operator|(
operator|(
name|gimage_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|)
operator|!=
name|active_tool
operator|->
name|drawable
operator|)
operator|&&
operator|!
name|active_tool
operator|->
name|preserve
condition|)
name|tools_initialize
argument_list|(
name|active_tool
operator|->
name|type
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
else|else
name|active_tool
operator|->
name|drawable
operator|=
name|gimage_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
call|(
modifier|*
name|active_tool
operator|->
name|button_press_func
call|)
argument_list|(
name|active_tool
argument_list|,
name|bevent
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
literal|2
case|:
name|scrolled
operator|=
name|TRUE
expr_stmt|;
name|gtk_grab_add
argument_list|(
name|canvas
argument_list|)
expr_stmt|;
name|start_grab_and_scroll
argument_list|(
name|gdisp
argument_list|,
name|bevent
argument_list|)
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|popup_shell
operator|=
name|gdisp
operator|->
name|shell
expr_stmt|;
name|gdisplay_set_menu_sensitivity
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|gtk_menu_popup
argument_list|(
name|GTK_MENU
argument_list|(
name|gdisp
operator|->
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
literal|3
argument_list|,
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
break|break;
case|case
name|GDK_BUTTON_RELEASE
case|:
name|bevent
operator|=
operator|(
name|GdkEventButton
operator|*
operator|)
name|event
expr_stmt|;
name|state
operator|=
name|bevent
operator|->
name|state
expr_stmt|;
switch|switch
condition|(
name|bevent
operator|->
name|button
condition|)
block|{
case|case
literal|1
case|:
comment|/* Lame hack. See above */
if|if
condition|(
name|key_signal_id
condition|)
block|{
name|gtk_signal_disconnect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|canvas
argument_list|)
argument_list|,
name|key_signal_id
argument_list|)
expr_stmt|;
name|key_signal_id
operator|=
literal|0
expr_stmt|;
block|}
name|gtk_grab_remove
argument_list|(
name|canvas
argument_list|)
expr_stmt|;
name|gdk_pointer_ungrab
argument_list|(
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
comment|/* fixes pointer grab bug */
if|if
condition|(
name|active_tool
operator|&&
operator|(
operator|(
name|active_tool
operator|->
name|type
operator|==
name|MOVE
operator|)
operator|||
operator|!
name|gimage_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|)
condition|)
if|if
condition|(
name|active_tool
operator|->
name|state
operator|==
name|ACTIVE
condition|)
block|{
if|if
condition|(
name|active_tool
operator|->
name|auto_snap_to
condition|)
block|{
name|gdisplay_snap_point
argument_list|(
name|gdisp
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|,
operator|&
name|tx
argument_list|,
operator|&
name|ty
argument_list|)
expr_stmt|;
name|bevent
operator|->
name|x
operator|=
name|tx
expr_stmt|;
name|bevent
operator|->
name|y
operator|=
name|ty
expr_stmt|;
block|}
call|(
modifier|*
name|active_tool
operator|->
name|button_release_func
call|)
argument_list|(
name|active_tool
argument_list|,
name|bevent
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
literal|2
case|:
name|scrolled
operator|=
name|FALSE
expr_stmt|;
name|gtk_grab_remove
argument_list|(
name|canvas
argument_list|)
expr_stmt|;
name|end_grab_and_scroll
argument_list|(
name|gdisp
argument_list|,
name|bevent
argument_list|)
expr_stmt|;
break|break;
case|case
literal|3
case|:
break|break;
default|default:
break|break;
block|}
break|break;
case|case
name|GDK_MOTION_NOTIFY
case|:
name|mevent
operator|=
operator|(
name|GdkEventMotion
operator|*
operator|)
name|event
expr_stmt|;
name|state
operator|=
name|mevent
operator|->
name|state
expr_stmt|;
comment|/* Ask for the pointer position, but ignore it except for cursor       * handling, so motion events sync with the button press/release events */
if|if
condition|(
name|mevent
operator|->
name|is_hint
condition|)
name|gdk_input_window_get_pointer
argument_list|(
name|canvas
operator|->
name|window
argument_list|,
name|current_device
argument_list|,
operator|&
name|tx
argument_list|,
operator|&
name|ty
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
block|{
name|tx
operator|=
name|mevent
operator|->
name|x
expr_stmt|;
name|ty
operator|=
name|mevent
operator|->
name|y
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|gdisp
operator|->
name|proximity
condition|)
block|{
name|gdisp
operator|->
name|proximity
operator|=
name|TRUE
expr_stmt|;
name|gdisplay_check_device_cursor
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|active_tool
operator|&&
operator|(
operator|(
name|active_tool
operator|->
name|type
operator|==
name|MOVE
operator|)
operator|||
operator|!
name|gimage_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|)
operator|&&
operator|(
name|mevent
operator|->
name|state
operator|&
name|GDK_BUTTON1_MASK
operator|)
condition|)
block|{
if|if
condition|(
name|active_tool
operator|->
name|state
operator|==
name|ACTIVE
condition|)
block|{
comment|/*  if the first mouse button is down, check for automatic 	       *  scrolling... 	       */
if|if
condition|(
operator|(
name|mevent
operator|->
name|state
operator|&
name|Button1Mask
operator|)
operator|&&
operator|!
name|active_tool
operator|->
name|scroll_lock
condition|)
block|{
if|if
condition|(
name|mevent
operator|->
name|x
operator|<
literal|0
operator|||
name|mevent
operator|->
name|y
operator|<
literal|0
operator|||
name|mevent
operator|->
name|x
operator|>
name|gdisp
operator|->
name|disp_width
operator|||
name|mevent
operator|->
name|y
operator|>
name|gdisp
operator|->
name|disp_height
condition|)
name|scroll_to_pointer_position
argument_list|(
name|gdisp
argument_list|,
name|mevent
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|active_tool
operator|->
name|auto_snap_to
condition|)
block|{
name|gdisplay_snap_point
argument_list|(
name|gdisp
argument_list|,
name|mevent
operator|->
name|x
argument_list|,
name|mevent
operator|->
name|y
argument_list|,
operator|&
name|tx
argument_list|,
operator|&
name|ty
argument_list|)
expr_stmt|;
name|mevent
operator|->
name|x
operator|=
name|tx
expr_stmt|;
name|mevent
operator|->
name|y
operator|=
name|ty
expr_stmt|;
block|}
call|(
modifier|*
name|active_tool
operator|->
name|motion_func
call|)
argument_list|(
name|active_tool
argument_list|,
name|mevent
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
operator|(
name|mevent
operator|->
name|state
operator|&
name|GDK_BUTTON2_MASK
operator|)
operator|&&
name|scrolled
condition|)
block|{
name|grab_and_scroll
argument_list|(
name|gdisp
argument_list|,
name|mevent
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GDK_KEY_PRESS
case|:
name|kevent
operator|=
operator|(
name|GdkEventKey
operator|*
operator|)
name|event
expr_stmt|;
name|state
operator|=
name|kevent
operator|->
name|state
expr_stmt|;
switch|switch
condition|(
name|kevent
operator|->
name|keyval
condition|)
block|{
case|case
name|GDK_Left
case|:
case|case
name|GDK_Right
case|:
case|case
name|GDK_Up
case|:
case|case
name|GDK_Down
case|:
if|if
condition|(
name|active_tool
operator|&&
operator|!
name|gimage_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
condition|)
call|(
modifier|*
name|active_tool
operator|->
name|arrow_keys_func
call|)
argument_list|(
name|active_tool
argument_list|,
name|kevent
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|return_val
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GDK_Tab
case|:
if|if
condition|(
name|kevent
operator|->
name|state
operator|&
name|GDK_MOD1_MASK
operator|&&
operator|!
name|gimage_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
condition|)
name|layer_select_init
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
literal|1
argument_list|,
name|kevent
operator|->
name|time
argument_list|)
expr_stmt|;
if|if
condition|(
name|kevent
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
operator|&&
operator|!
name|gimage_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
condition|)
name|layer_select_init
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
operator|-
literal|1
argument_list|,
name|kevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|return_val
operator|=
name|TRUE
expr_stmt|;
break|break;
comment|/*  Update the state based on modifiers being pressed  */
case|case
name|GDK_Alt_L
case|:
case|case
name|GDK_Alt_R
case|:
name|state
operator||=
name|GDK_MOD1_MASK
expr_stmt|;
break|break;
case|case
name|GDK_Shift_L
case|:
case|case
name|GDK_Shift_R
case|:
name|state
operator||=
name|GDK_SHIFT_MASK
expr_stmt|;
break|break;
case|case
name|GDK_Control_L
case|:
case|case
name|GDK_Control_R
case|:
name|state
operator||=
name|GDK_CONTROL_MASK
expr_stmt|;
break|break;
block|}
comment|/*  We need this here in case of accelerators  */
name|gdisplay_set_menu_sensitivity
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
break|break;
case|case
name|GDK_KEY_RELEASE
case|:
name|kevent
operator|=
operator|(
name|GdkEventKey
operator|*
operator|)
name|event
expr_stmt|;
name|state
operator|=
name|kevent
operator|->
name|state
expr_stmt|;
switch|switch
condition|(
name|kevent
operator|->
name|keyval
condition|)
block|{
case|case
name|GDK_Alt_L
case|:
case|case
name|GDK_Alt_R
case|:
name|state
operator|&=
operator|~
name|GDK_MOD1_MASK
expr_stmt|;
break|break;
case|case
name|GDK_Shift_L
case|:
case|case
name|GDK_Shift_R
case|:
name|kevent
operator|->
name|state
operator|&=
operator|~
name|GDK_SHIFT_MASK
expr_stmt|;
break|break;
case|case
name|GDK_Control_L
case|:
case|case
name|GDK_Control_R
case|:
name|kevent
operator|->
name|state
operator|&=
operator|~
name|GDK_CONTROL_MASK
expr_stmt|;
break|break;
block|}
name|return_val
operator|=
name|TRUE
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|no_cursor_updating
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|active_tool
operator|&&
operator|!
name|gimage_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|&&
operator|!
operator|(
name|state
operator|&
operator|(
name|GDK_BUTTON1_MASK
operator||
name|GDK_BUTTON2_MASK
operator||
name|GDK_BUTTON3_MASK
operator|)
operator|)
condition|)
block|{
name|GdkEventMotion
name|me
decl_stmt|;
name|me
operator|.
name|x
operator|=
name|tx
expr_stmt|;
name|me
operator|.
name|y
operator|=
name|ty
expr_stmt|;
name|me
operator|.
name|state
operator|=
name|state
expr_stmt|;
call|(
modifier|*
name|active_tool
operator|->
name|cursor_update_func
call|)
argument_list|(
name|active_tool
argument_list|,
operator|&
name|me
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimage_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
condition|)
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_TOP_LEFT_ARROW
argument_list|)
expr_stmt|;
block|}
name|gdisplay_update_cursor
argument_list|(
name|gdisp
argument_list|,
name|tx
argument_list|,
name|ty
argument_list|)
expr_stmt|;
return|return
name|return_val
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gdisplay_hruler_button_press (GtkWidget * widget,GdkEventButton * event,gpointer data)
name|gdisplay_hruler_button_press
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
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
if|if
condition|(
name|event
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|gdisp
operator|=
name|data
expr_stmt|;
name|gtk_widget_activate
argument_list|(
name|tool_info
index|[
operator|(
name|int
operator|)
name|MOVE
index|]
operator|.
name|tool_widget
argument_list|)
expr_stmt|;
name|move_tool_start_hguide
argument_list|(
name|active_tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|gtk_grab_add
argument_list|(
name|gdisp
operator|->
name|canvas
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gdisplay_vruler_button_press (GtkWidget * widget,GdkEventButton * event,gpointer data)
name|gdisplay_vruler_button_press
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
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
if|if
condition|(
name|event
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|gdisp
operator|=
name|data
expr_stmt|;
name|gtk_widget_activate
argument_list|(
name|tool_info
index|[
operator|(
name|int
operator|)
name|MOVE
index|]
operator|.
name|tool_widget
argument_list|)
expr_stmt|;
name|move_tool_start_vguide
argument_list|(
name|active_tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|gtk_grab_add
argument_list|(
name|gdisp
operator|->
name|canvas
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gdisplay_origin_button_press (GtkWidget * widget,GdkEventButton * event,gpointer data)
name|gdisplay_origin_button_press
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
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
if|if
condition|(
name|event
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|gdisp
operator|=
name|data
expr_stmt|;
name|popup_shell
operator|=
name|gdisp
operator|->
name|shell
expr_stmt|;
name|gdisplay_set_menu_sensitivity
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|gtk_menu_popup
argument_list|(
name|GTK_MENU
argument_list|(
name|gdisp
operator|->
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
literal|1
argument_list|,
name|event
operator|->
name|time
argument_list|)
expr_stmt|;
comment|/* Stop the signal emission so the button doesn't grab the        * pointer away from us        */
name|gtk_signal_emit_stop_by_name
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"button_press_event"
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

