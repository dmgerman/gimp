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
file|"appenv.h"
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
file|"cursorutil.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_comment
comment|/*  This is the delay before dithering begins  *  for example, after an operation such as scrolling  */
end_comment

begin_define
DECL|macro|DITHER_DELAY
define|#
directive|define
name|DITHER_DELAY
value|250
end_define

begin_comment
DECL|macro|DITHER_DELAY
comment|/*  milliseconds  */
end_comment

begin_comment
comment|/*  Locally defined functions  */
end_comment

begin_function_decl
specifier|static
name|int
name|scroll_display
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  STATIC variables  */
end_comment

begin_comment
comment|/*  These are the values of the initial pointer grab   */
end_comment

begin_decl_stmt
DECL|variable|startx
DECL|variable|starty
specifier|static
name|int
name|startx
decl_stmt|,
name|starty
decl_stmt|;
end_decl_stmt

begin_function
name|gint
DECL|function|scrollbar_vert_update (GtkAdjustment * adjustment,gpointer data)
name|scrollbar_vert_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
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
name|scroll_display
argument_list|(
name|gdisp
argument_list|,
literal|0
argument_list|,
operator|(
name|adjustment
operator|->
name|value
operator|-
name|gdisp
operator|->
name|offset_y
operator|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gint
DECL|function|scrollbar_horz_update (GtkAdjustment * adjustment,gpointer data)
name|scrollbar_horz_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
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
name|scroll_display
argument_list|(
name|gdisp
argument_list|,
operator|(
name|adjustment
operator|->
name|value
operator|-
name|gdisp
operator|->
name|offset_x
operator|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|start_grab_and_scroll (GDisplay * gdisp,GdkEventButton * bevent)
name|start_grab_and_scroll
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
block|{
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
name|startx
operator|=
name|bevent
operator|->
name|x
operator|+
name|gdisp
operator|->
name|offset_x
expr_stmt|;
name|starty
operator|=
name|bevent
operator|->
name|y
operator|+
name|gdisp
operator|->
name|offset_y
expr_stmt|;
name|cursor
operator|=
name|gdk_cursor_new
argument_list|(
name|GDK_FLEUR
argument_list|)
expr_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|cursor
argument_list|)
expr_stmt|;
name|gdk_cursor_destroy
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|end_grab_and_scroll (GDisplay * gdisp,GdkEventButton * bevent)
name|end_grab_and_scroll
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
block|{
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
name|cursor
operator|=
name|gdk_cursor_new
argument_list|(
name|gdisp
operator|->
name|current_cursor
argument_list|)
expr_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|cursor
argument_list|)
expr_stmt|;
name|gdk_cursor_destroy
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|grab_and_scroll (GDisplay * gdisp,GdkEventMotion * mevent)
name|grab_and_scroll
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|)
block|{
name|scroll_display
argument_list|(
name|gdisp
argument_list|,
operator|(
name|startx
operator|-
name|mevent
operator|->
name|x
operator|-
name|gdisp
operator|->
name|offset_x
operator|)
argument_list|,
operator|(
name|starty
operator|-
name|mevent
operator|->
name|y
operator|-
name|gdisp
operator|->
name|offset_y
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|scroll_to_pointer_position (GDisplay * gdisp,GdkEventMotion * mevent)
name|scroll_to_pointer_position
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|)
block|{
name|int
name|child_x
decl_stmt|,
name|child_y
decl_stmt|;
name|int
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|off_x
operator|=
name|off_y
operator|=
literal|0
expr_stmt|;
comment|/*  The cases for scrolling  */
if|if
condition|(
name|mevent
operator|->
name|x
operator|<
literal|0
condition|)
name|off_x
operator|=
name|mevent
operator|->
name|x
expr_stmt|;
elseif|else
if|if
condition|(
name|mevent
operator|->
name|x
operator|>
name|gdisp
operator|->
name|disp_width
condition|)
name|off_x
operator|=
name|mevent
operator|->
name|x
operator|-
name|gdisp
operator|->
name|disp_width
expr_stmt|;
if|if
condition|(
name|mevent
operator|->
name|y
operator|<
literal|0
condition|)
name|off_y
operator|=
name|mevent
operator|->
name|y
expr_stmt|;
elseif|else
if|if
condition|(
name|mevent
operator|->
name|y
operator|>
name|gdisp
operator|->
name|disp_height
condition|)
name|off_y
operator|=
name|mevent
operator|->
name|y
operator|-
name|gdisp
operator|->
name|disp_height
expr_stmt|;
if|if
condition|(
name|scroll_display
argument_list|(
name|gdisp
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|)
condition|)
block|{
name|gdk_window_get_pointer
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
operator|&
name|child_x
argument_list|,
operator|&
name|child_y
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|child_x
operator|==
name|mevent
operator|->
name|x
operator|&&
name|child_y
operator|==
name|mevent
operator|->
name|y
condition|)
comment|/*  Put this event back on the queue -- so it keeps scrolling */
name|gdk_event_put
argument_list|(
operator|(
name|GdkEvent
operator|*
operator|)
name|mevent
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|scroll_display (GDisplay * gdisp,int x_offset,int y_offset)
name|scroll_display
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|int
name|x_offset
parameter_list|,
name|int
name|y_offset
parameter_list|)
block|{
name|int
name|old_x
decl_stmt|,
name|old_y
decl_stmt|;
name|int
name|src_x
decl_stmt|,
name|src_y
decl_stmt|;
name|int
name|dest_x
decl_stmt|,
name|dest_y
decl_stmt|;
name|GdkEvent
modifier|*
name|event
decl_stmt|;
name|old_x
operator|=
name|gdisp
operator|->
name|offset_x
expr_stmt|;
name|old_y
operator|=
name|gdisp
operator|->
name|offset_y
expr_stmt|;
name|gdisp
operator|->
name|offset_x
operator|+=
name|x_offset
expr_stmt|;
name|gdisp
operator|->
name|offset_y
operator|+=
name|y_offset
expr_stmt|;
name|bounds_checking
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
comment|/*  the actual changes in offset  */
name|x_offset
operator|=
operator|(
name|gdisp
operator|->
name|offset_x
operator|-
name|old_x
operator|)
expr_stmt|;
name|y_offset
operator|=
operator|(
name|gdisp
operator|->
name|offset_y
operator|-
name|old_y
operator|)
expr_stmt|;
if|if
condition|(
name|x_offset
operator|||
name|y_offset
condition|)
block|{
name|setup_scale
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|src_x
operator|=
operator|(
name|x_offset
operator|<
literal|0
operator|)
condition|?
literal|0
else|:
name|x_offset
expr_stmt|;
name|src_y
operator|=
operator|(
name|y_offset
operator|<
literal|0
operator|)
condition|?
literal|0
else|:
name|y_offset
expr_stmt|;
name|dest_x
operator|=
operator|(
name|x_offset
operator|<
literal|0
operator|)
condition|?
operator|-
name|x_offset
else|:
literal|0
expr_stmt|;
name|dest_y
operator|=
operator|(
name|y_offset
operator|<
literal|0
operator|)
condition|?
operator|-
name|y_offset
else|:
literal|0
expr_stmt|;
comment|/*  reset the old values so that the tool can accurately redraw  */
name|gdisp
operator|->
name|offset_x
operator|=
name|old_x
expr_stmt|;
name|gdisp
operator|->
name|offset_y
operator|=
name|old_y
expr_stmt|;
comment|/*  stop the currently active tool  */
name|active_tool_control
argument_list|(
name|PAUSE
argument_list|,
operator|(
name|void
operator|*
operator|)
name|gdisp
argument_list|)
expr_stmt|;
comment|/*  set the offsets back to the new values  */
name|gdisp
operator|->
name|offset_x
operator|+=
name|x_offset
expr_stmt|;
name|gdisp
operator|->
name|offset_y
operator|+=
name|y_offset
expr_stmt|;
name|gdk_draw_pixmap
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|gdisp
operator|->
name|scroll_gc
argument_list|,
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|src_x
argument_list|,
name|src_y
argument_list|,
name|dest_x
argument_list|,
name|dest_y
argument_list|,
operator|(
name|gdisp
operator|->
name|disp_width
operator|-
name|abs
argument_list|(
name|x_offset
argument_list|)
operator|)
argument_list|,
operator|(
name|gdisp
operator|->
name|disp_height
operator|-
name|abs
argument_list|(
name|y_offset
argument_list|)
operator|)
argument_list|)
expr_stmt|;
comment|/*  resume the currently active tool  */
name|active_tool_control
argument_list|(
name|RESUME
argument_list|,
operator|(
name|void
operator|*
operator|)
name|gdisp
argument_list|)
expr_stmt|;
comment|/*  scale the image into the exposed regions  */
if|if
condition|(
name|x_offset
condition|)
block|{
name|src_x
operator|=
operator|(
name|x_offset
operator|<
literal|0
operator|)
condition|?
literal|0
else|:
name|gdisp
operator|->
name|disp_width
operator|-
name|x_offset
expr_stmt|;
name|src_y
operator|=
literal|0
expr_stmt|;
name|gdisplay_expose_area
argument_list|(
name|gdisp
argument_list|,
name|src_x
argument_list|,
name|src_y
argument_list|,
name|abs
argument_list|(
name|x_offset
argument_list|)
argument_list|,
name|gdisp
operator|->
name|disp_height
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|y_offset
condition|)
block|{
name|src_x
operator|=
literal|0
expr_stmt|;
name|src_y
operator|=
operator|(
name|y_offset
operator|<
literal|0
operator|)
condition|?
literal|0
else|:
name|gdisp
operator|->
name|disp_height
operator|-
name|y_offset
expr_stmt|;
name|gdisplay_expose_area
argument_list|(
name|gdisp
argument_list|,
name|src_x
argument_list|,
name|src_y
argument_list|,
name|gdisp
operator|->
name|disp_width
argument_list|,
name|abs
argument_list|(
name|y_offset
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|x_offset
operator|||
name|y_offset
condition|)
name|gdisplays_flush
argument_list|()
expr_stmt|;
comment|/* Make sure graphics expose events are processed before scrolling        * again */
while|while
condition|(
operator|(
name|event
operator|=
name|gdk_event_get_graphics_expose
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
name|gtk_widget_event
argument_list|(
name|gdisp
operator|->
name|canvas
argument_list|,
name|event
argument_list|)
expr_stmt|;
if|if
condition|(
name|event
operator|->
name|expose
operator|.
name|count
operator|==
literal|0
condition|)
block|{
name|gdk_event_free
argument_list|(
name|event
argument_list|)
expr_stmt|;
break|break;
block|}
name|gdk_event_free
argument_list|(
name|event
argument_list|)
expr_stmt|;
block|}
return|return
literal|1
return|;
block|}
return|return
literal|0
return|;
block|}
end_function

end_unit

