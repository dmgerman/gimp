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
file|"indicator_area.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushlist.h"
end_include

begin_define
DECL|macro|CELL_SIZE
define|#
directive|define
name|CELL_SIZE
value|23
end_define

begin_comment
DECL|macro|CELL_SIZE
comment|/* The size of the previews */
end_comment

begin_define
DECL|macro|CELL_PADDING
define|#
directive|define
name|CELL_PADDING
value|2
end_define

begin_comment
DECL|macro|CELL_PADDING
comment|/* How much between brush and pattern cells */
end_comment

begin_define
DECL|macro|PREVIEW_EVENT_MASK
define|#
directive|define
name|PREVIEW_EVENT_MASK
value|GDK_EXPOSURE_MASK | \                           GDK_BUTTON_PRESS_MASK | \                           GDK_BUTTON_RELEASE_MASK | \                           GDK_BUTTON1_MOTION_MASK | \                           GDK_ENTER_NOTIFY_MASK | \                           GDK_LEAVE_NOTIFY_MASK
end_define

begin_comment
comment|/*  Global variables  */
end_comment

begin_function_decl
specifier|static
name|void
name|brush_popup_open
parameter_list|(
name|GimpBrushP
name|brush
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Prototypes */
end_comment

begin_function_decl
specifier|static
name|void
name|brush_popup_open
parameter_list|(
name|GimpBrushP
name|brush
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|brush_area_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|pattern_popup_open
parameter_list|(
name|GPatternP
name|brush
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|pattern_area_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Static variables  */
end_comment

begin_decl_stmt
DECL|variable|indicator_table
specifier|static
name|GtkWidget
modifier|*
name|indicator_table
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brush_preview
specifier|static
name|GtkWidget
modifier|*
name|brush_preview
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pattern_preview
specifier|static
name|GtkWidget
modifier|*
name|pattern_preview
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|device_bpopup
specifier|static
name|GtkWidget
modifier|*
name|device_bpopup
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|device_bpreview
specifier|static
name|GtkWidget
modifier|*
name|device_bpreview
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|device_patpopup
specifier|static
name|GtkWidget
modifier|*
name|device_patpopup
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|device_patpreview
specifier|static
name|GtkWidget
modifier|*
name|device_patpreview
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|brush_popup_open (GimpBrushP brush,int x,int y)
name|brush_popup_open
parameter_list|(
name|GimpBrushP
name|brush
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|)
block|{
name|gint
name|x_org
decl_stmt|,
name|y_org
decl_stmt|;
name|gint
name|scr_w
decl_stmt|,
name|scr_h
decl_stmt|;
name|gchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|buf
decl_stmt|;
comment|/* make sure the popup exists and is not visible */
if|if
condition|(
name|device_bpopup
operator|==
name|NULL
condition|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|device_bpopup
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_POPUP
argument_list|)
expr_stmt|;
name|gtk_window_set_policy
argument_list|(
name|GTK_WINDOW
argument_list|(
name|device_bpopup
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|device_bpopup
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|device_bpreview
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_GRAYSCALE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|device_bpreview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|device_bpreview
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_hide
argument_list|(
name|device_bpopup
argument_list|)
expr_stmt|;
block|}
comment|/* decide where to put the popup */
name|gdk_window_get_origin
argument_list|(
name|brush_preview
operator|->
name|window
argument_list|,
operator|&
name|x_org
argument_list|,
operator|&
name|y_org
argument_list|)
expr_stmt|;
name|scr_w
operator|=
name|gdk_screen_width
argument_list|()
expr_stmt|;
name|scr_h
operator|=
name|gdk_screen_height
argument_list|()
expr_stmt|;
name|x
operator|=
name|x_org
operator|+
name|x
operator|-
operator|(
name|brush
operator|->
name|mask
operator|->
name|width
operator|>>
literal|1
operator|)
expr_stmt|;
name|y
operator|=
name|y_org
operator|+
name|y
operator|-
operator|(
name|brush
operator|->
name|mask
operator|->
name|height
operator|>>
literal|1
operator|)
expr_stmt|;
name|x
operator|=
operator|(
name|x
operator|<
literal|0
operator|)
condition|?
literal|0
else|:
name|x
expr_stmt|;
name|y
operator|=
operator|(
name|y
operator|<
literal|0
operator|)
condition|?
literal|0
else|:
name|y
expr_stmt|;
name|x
operator|=
operator|(
name|x
operator|+
name|brush
operator|->
name|mask
operator|->
name|width
operator|>
name|scr_w
operator|)
condition|?
name|scr_w
operator|-
name|brush
operator|->
name|mask
operator|->
name|width
else|:
name|x
expr_stmt|;
name|y
operator|=
operator|(
name|y
operator|+
name|brush
operator|->
name|mask
operator|->
name|height
operator|>
name|scr_h
operator|)
condition|?
name|scr_h
operator|-
name|brush
operator|->
name|mask
operator|->
name|height
else|:
name|y
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|device_bpreview
argument_list|)
argument_list|,
name|brush
operator|->
name|mask
operator|->
name|width
argument_list|,
name|brush
operator|->
name|mask
operator|->
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_popup
argument_list|(
name|device_bpopup
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
comment|/*  Draw the brush  */
name|buf
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|brush
operator|->
name|mask
operator|->
name|width
argument_list|)
expr_stmt|;
name|src
operator|=
operator|(
name|gchar
operator|*
operator|)
name|temp_buf_data
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|brush
operator|->
name|mask
operator|->
name|height
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|brush
operator|->
name|mask
operator|->
name|width
condition|;
name|x
operator|++
control|)
name|buf
index|[
name|x
index|]
operator|=
literal|255
operator|-
name|src
index|[
name|x
index|]
expr_stmt|;
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|device_bpreview
argument_list|)
argument_list|,
operator|(
name|guchar
operator|*
operator|)
name|buf
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|brush
operator|->
name|mask
operator|->
name|width
argument_list|)
expr_stmt|;
name|src
operator|+=
name|brush
operator|->
name|mask
operator|->
name|width
expr_stmt|;
block|}
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
comment|/*  Draw the brush preview  */
name|gtk_widget_draw
argument_list|(
name|device_bpreview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|brush_area_update ()
name|brush_area_update
parameter_list|()
block|{
name|guchar
name|buffer
index|[
name|CELL_SIZE
index|]
decl_stmt|;
name|TempBuf
modifier|*
name|brush_buf
decl_stmt|;
name|GimpBrushP
name|brush
decl_stmt|;
name|unsigned
name|char
modifier|*
name|src
decl_stmt|,
modifier|*
name|s
init|=
name|NULL
decl_stmt|;
name|unsigned
name|char
modifier|*
name|b
decl_stmt|;
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
name|int
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
name|int
name|yend
decl_stmt|;
name|int
name|ystart
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
name|brush
operator|=
name|get_active_brush
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|brush
condition|)
block|{
name|g_warning
argument_list|(
literal|"No gimp brush found\n"
argument_list|)
expr_stmt|;
return|return;
block|}
name|brush_buf
operator|=
name|brush
operator|->
name|mask
expr_stmt|;
comment|/*  Get the pointer into the brush mask data  */
name|src
operator|=
name|mask_buf_data
argument_list|(
name|brush_buf
argument_list|)
expr_stmt|;
comment|/* Limit to cell size */
name|width
operator|=
operator|(
name|brush_buf
operator|->
name|width
operator|>
name|CELL_SIZE
operator|)
condition|?
name|CELL_SIZE
else|:
name|brush_buf
operator|->
name|width
expr_stmt|;
name|height
operator|=
operator|(
name|brush_buf
operator|->
name|height
operator|>
name|CELL_SIZE
operator|)
condition|?
name|CELL_SIZE
else|:
name|brush_buf
operator|->
name|height
expr_stmt|;
comment|/* Set buffer to white */
name|memset
argument_list|(
name|buffer
argument_list|,
literal|255
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
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
name|CELL_SIZE
condition|;
name|i
operator|++
control|)
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|brush_preview
argument_list|)
argument_list|,
name|buffer
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|offset_x
operator|=
operator|(
operator|(
name|CELL_SIZE
operator|-
name|width
operator|)
operator|>>
literal|1
operator|)
expr_stmt|;
name|offset_y
operator|=
operator|(
operator|(
name|CELL_SIZE
operator|-
name|height
operator|)
operator|>>
literal|1
operator|)
expr_stmt|;
name|ystart
operator|=
name|BOUNDS
argument_list|(
name|offset_y
argument_list|,
literal|0
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|yend
operator|=
name|BOUNDS
argument_list|(
name|offset_y
operator|+
name|height
argument_list|,
literal|0
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
name|ystart
init|;
name|i
operator|<
name|yend
condition|;
name|i
operator|++
control|)
block|{
comment|/*  Invert the mask for display.  We're doing this because        *  a value of 255 in the  mask means it is full intensity.        *  However, it makes more sense for full intensity to show        *  up as black in this brush preview window...        */
name|s
operator|=
name|src
expr_stmt|;
name|b
operator|=
name|buffer
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|width
condition|;
name|j
operator|++
control|)
operator|*
name|b
operator|++
operator|=
literal|255
operator|-
operator|*
name|s
operator|++
expr_stmt|;
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|brush_preview
argument_list|)
argument_list|,
name|buffer
argument_list|,
name|offset_x
argument_list|,
name|i
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|src
operator|+=
name|brush_buf
operator|->
name|width
expr_stmt|;
block|}
name|gtk_widget_draw
argument_list|(
name|brush_preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|brush_preview
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|brush_area_events (GtkWidget * widget,GdkEvent * event)
name|brush_area_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
block|{
name|GdkEventButton
modifier|*
name|bevent
decl_stmt|;
name|GimpBrushP
name|brush
decl_stmt|;
name|brush
operator|=
name|get_active_brush
argument_list|()
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
break|break;
case|case
name|GDK_BUTTON_RELEASE
case|:
if|if
condition|(
name|device_bpopup
operator|!=
name|NULL
condition|)
name|gtk_widget_hide
argument_list|(
name|device_bpopup
argument_list|)
expr_stmt|;
name|brush_area_update
argument_list|()
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
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
comment|/* pop up the brush selection dialog accordingly */
name|create_brush_dialog
argument_list|()
expr_stmt|;
comment|/*  Show the brush popup window if the brush is too large  */
if|if
condition|(
name|brush
operator|->
name|mask
operator|->
name|width
operator|>
name|CELL_SIZE
operator|||
name|brush
operator|->
name|mask
operator|->
name|height
operator|>
name|CELL_SIZE
condition|)
name|brush_popup_open
argument_list|(
name|brush
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GDK_DELETE
case|:
break|break;
default|default:
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|pattern_area_update ()
name|pattern_area_update
parameter_list|()
block|{
name|guchar
modifier|*
name|buffer
init|=
name|NULL
decl_stmt|;
name|TempBuf
modifier|*
name|pattern_buf
decl_stmt|;
name|unsigned
name|char
modifier|*
name|src
decl_stmt|,
modifier|*
name|s
init|=
name|NULL
decl_stmt|;
name|unsigned
name|char
modifier|*
name|b
decl_stmt|;
name|int
name|rowstride
decl_stmt|;
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
name|int
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
name|int
name|yend
decl_stmt|;
name|int
name|ystart
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
name|GPatternP
name|pattern
init|=
name|get_active_pattern
argument_list|()
decl_stmt|;
name|buffer
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|pattern_buf
operator|=
name|pattern
operator|->
name|mask
expr_stmt|;
comment|/* Limit to cell size */
name|width
operator|=
operator|(
name|pattern_buf
operator|->
name|width
operator|>
name|CELL_SIZE
operator|)
condition|?
name|CELL_SIZE
else|:
name|pattern_buf
operator|->
name|width
expr_stmt|;
name|height
operator|=
operator|(
name|pattern_buf
operator|->
name|height
operator|>
name|CELL_SIZE
operator|)
condition|?
name|CELL_SIZE
else|:
name|pattern_buf
operator|->
name|height
expr_stmt|;
comment|/* Set buffer to white */
name|memset
argument_list|(
name|buffer
argument_list|,
literal|255
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
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
name|CELL_SIZE
condition|;
name|i
operator|++
control|)
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|pattern_preview
argument_list|)
argument_list|,
name|buffer
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|offset_x
operator|=
operator|(
operator|(
name|CELL_SIZE
operator|-
name|width
operator|)
operator|>>
literal|1
operator|)
expr_stmt|;
name|offset_y
operator|=
operator|(
operator|(
name|CELL_SIZE
operator|-
name|height
operator|)
operator|>>
literal|1
operator|)
expr_stmt|;
name|ystart
operator|=
name|BOUNDS
argument_list|(
name|offset_y
argument_list|,
literal|0
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|yend
operator|=
name|BOUNDS
argument_list|(
name|offset_y
operator|+
name|height
argument_list|,
literal|0
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
comment|/*  Get the pointer into the brush mask data  */
name|rowstride
operator|=
name|pattern_buf
operator|->
name|width
operator|*
name|pattern_buf
operator|->
name|bytes
expr_stmt|;
name|src
operator|=
name|mask_buf_data
argument_list|(
name|pattern_buf
argument_list|)
operator|+
operator|(
name|ystart
operator|-
name|offset_y
operator|)
operator|*
name|rowstride
expr_stmt|;
for|for
control|(
name|i
operator|=
name|ystart
init|;
name|i
operator|<
name|yend
condition|;
name|i
operator|++
control|)
block|{
name|s
operator|=
name|src
expr_stmt|;
name|b
operator|=
name|buffer
expr_stmt|;
if|if
condition|(
name|pattern_buf
operator|->
name|bytes
operator|==
literal|1
condition|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|width
condition|;
name|j
operator|++
control|)
block|{
operator|*
name|b
operator|++
operator|=
operator|*
name|s
expr_stmt|;
operator|*
name|b
operator|++
operator|=
operator|*
name|s
expr_stmt|;
operator|*
name|b
operator|++
operator|=
operator|*
name|s
operator|++
expr_stmt|;
block|}
else|else
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|width
condition|;
name|j
operator|++
control|)
block|{
operator|*
name|b
operator|++
operator|=
operator|*
name|s
operator|++
expr_stmt|;
operator|*
name|b
operator|++
operator|=
operator|*
name|s
operator|++
expr_stmt|;
operator|*
name|b
operator|++
operator|=
operator|*
name|s
operator|++
expr_stmt|;
block|}
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|pattern_preview
argument_list|)
argument_list|,
name|buffer
argument_list|,
name|offset_x
argument_list|,
name|i
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|src
operator|+=
name|rowstride
expr_stmt|;
block|}
name|gtk_widget_draw
argument_list|(
name|pattern_preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pattern_preview
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pattern_popup_open (GPatternP pattern,int x,int y)
name|pattern_popup_open
parameter_list|(
name|GPatternP
name|pattern
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|)
block|{
name|gint
name|x_org
decl_stmt|,
name|y_org
decl_stmt|;
name|gint
name|scr_w
decl_stmt|,
name|scr_h
decl_stmt|;
name|gchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|buf
decl_stmt|;
comment|/* make sure the popup exists and is not visible */
if|if
condition|(
name|device_patpopup
operator|==
name|NULL
condition|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|device_patpopup
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_POPUP
argument_list|)
expr_stmt|;
name|gtk_window_set_policy
argument_list|(
name|GTK_WINDOW
argument_list|(
name|device_patpopup
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|device_patpopup
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|device_patpreview
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_COLOR
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|device_patpreview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|device_patpreview
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_hide
argument_list|(
name|device_patpopup
argument_list|)
expr_stmt|;
block|}
comment|/* decide where to put the popup */
name|gdk_window_get_origin
argument_list|(
name|pattern_preview
operator|->
name|window
argument_list|,
operator|&
name|x_org
argument_list|,
operator|&
name|y_org
argument_list|)
expr_stmt|;
name|scr_w
operator|=
name|gdk_screen_width
argument_list|()
expr_stmt|;
name|scr_h
operator|=
name|gdk_screen_height
argument_list|()
expr_stmt|;
name|x
operator|=
name|x_org
operator|+
name|x
operator|-
operator|(
name|pattern
operator|->
name|mask
operator|->
name|width
operator|>>
literal|1
operator|)
expr_stmt|;
name|y
operator|=
name|y_org
operator|+
name|y
operator|-
operator|(
name|pattern
operator|->
name|mask
operator|->
name|height
operator|>>
literal|1
operator|)
expr_stmt|;
name|x
operator|=
operator|(
name|x
operator|<
literal|0
operator|)
condition|?
literal|0
else|:
name|x
expr_stmt|;
name|y
operator|=
operator|(
name|y
operator|<
literal|0
operator|)
condition|?
literal|0
else|:
name|y
expr_stmt|;
name|x
operator|=
operator|(
name|x
operator|+
name|pattern
operator|->
name|mask
operator|->
name|width
operator|>
name|scr_w
operator|)
condition|?
name|scr_w
operator|-
name|pattern
operator|->
name|mask
operator|->
name|width
else|:
name|x
expr_stmt|;
name|y
operator|=
operator|(
name|y
operator|+
name|pattern
operator|->
name|mask
operator|->
name|height
operator|>
name|scr_h
operator|)
condition|?
name|scr_h
operator|-
name|pattern
operator|->
name|mask
operator|->
name|height
else|:
name|y
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|device_patpreview
argument_list|)
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|width
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_popup
argument_list|(
name|device_patpopup
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
comment|/*  Draw the pattern  */
name|buf
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|src
operator|=
operator|(
name|gchar
operator|*
operator|)
name|temp_buf_data
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|pattern
operator|->
name|mask
operator|->
name|height
condition|;
name|y
operator|++
control|)
block|{
if|if
condition|(
name|pattern
operator|->
name|mask
operator|->
name|bytes
operator|==
literal|1
condition|)
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|pattern
operator|->
name|mask
operator|->
name|width
condition|;
name|x
operator|++
control|)
block|{
name|buf
index|[
name|x
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|src
index|[
name|x
index|]
expr_stmt|;
name|buf
index|[
name|x
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|src
index|[
name|x
index|]
expr_stmt|;
name|buf
index|[
name|x
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|src
index|[
name|x
index|]
expr_stmt|;
block|}
else|else
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|pattern
operator|->
name|mask
operator|->
name|width
condition|;
name|x
operator|++
control|)
block|{
name|buf
index|[
name|x
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|src
index|[
name|x
operator|*
literal|3
operator|+
literal|0
index|]
expr_stmt|;
name|buf
index|[
name|x
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|src
index|[
name|x
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
name|buf
index|[
name|x
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|src
index|[
name|x
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
block|}
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|device_patpreview
argument_list|)
argument_list|,
operator|(
name|guchar
operator|*
operator|)
name|buf
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|width
argument_list|)
expr_stmt|;
name|src
operator|+=
name|pattern
operator|->
name|mask
operator|->
name|width
operator|*
name|pattern
operator|->
name|mask
operator|->
name|bytes
expr_stmt|;
block|}
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
comment|/*  Draw the brush preview  */
name|gtk_widget_draw
argument_list|(
name|device_patpreview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|pattern_area_events (GtkWidget * widget,GdkEvent * event)
name|pattern_area_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
block|{
name|GdkEventButton
modifier|*
name|bevent
decl_stmt|;
name|GPatternP
name|pattern
decl_stmt|;
name|pattern
operator|=
name|get_active_pattern
argument_list|()
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
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|gdk_pointer_grab
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|FALSE
argument_list|,
operator|(
name|GDK_POINTER_MOTION_HINT_MASK
operator||
name|GDK_BUTTON1_MOTION_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
operator|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|create_pattern_dialog
argument_list|()
expr_stmt|;
comment|/*  Show the pattern popup window if the pattern is too large  */
if|if
condition|(
name|pattern
operator|->
name|mask
operator|->
name|width
operator|>
name|CELL_SIZE
operator|||
name|pattern
operator|->
name|mask
operator|->
name|height
operator|>
name|CELL_SIZE
condition|)
name|pattern_popup_open
argument_list|(
name|pattern
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
name|gdk_pointer_ungrab
argument_list|(
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
block|{
if|if
condition|(
name|device_patpopup
operator|!=
name|NULL
condition|)
name|gtk_widget_hide
argument_list|(
name|device_patpopup
argument_list|)
expr_stmt|;
name|pattern_area_update
argument_list|()
expr_stmt|;
block|}
break|break;
case|case
name|GDK_DELETE
case|:
break|break;
default|default:
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|indicator_area_create (int width,int height)
name|indicator_area_create
parameter_list|(
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|)
block|{
comment|/* Put the brush in the table */
name|indicator_table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|brush_preview
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_GRAYSCALE
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|brush_preview
argument_list|)
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|brush_preview
argument_list|,
name|PREVIEW_EVENT_MASK
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|brush_preview
argument_list|)
argument_list|,
literal|"event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|brush_area_events
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|indicator_table
argument_list|)
argument_list|,
name|brush_preview
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pattern_preview
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_COLOR
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|pattern_preview
argument_list|)
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|pattern_preview
argument_list|,
name|PREVIEW_EVENT_MASK
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|pattern_preview
argument_list|)
argument_list|,
literal|"event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|pattern_area_events
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|indicator_table
argument_list|)
argument_list|,
name|pattern_preview
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|brush_area_update
argument_list|()
expr_stmt|;
name|pattern_area_update
argument_list|()
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|indicator_table
argument_list|)
expr_stmt|;
return|return
name|indicator_table
return|;
block|}
end_function

end_unit

