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
file|"draw_core.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"info_window.h"
end_include

begin_include
include|#
directive|include
file|"magnify.h"
end_include

begin_include
include|#
directive|include
file|"scale.h"
end_include

begin_include
include|#
directive|include
file|"tool_options_ui.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  types of magnify operations  */
end_comment

begin_define
DECL|macro|ZOOMIN
define|#
directive|define
name|ZOOMIN
value|0
end_define

begin_define
DECL|macro|ZOOMOUT
define|#
directive|define
name|ZOOMOUT
value|1
end_define

begin_comment
comment|/*  the magnify structures  */
end_comment

begin_typedef
DECL|typedef|Magnify
typedef|typedef
name|struct
name|_magnify
name|Magnify
typedef|;
end_typedef

begin_struct
DECL|struct|_magnify
struct|struct
name|_magnify
block|{
DECL|member|core
name|DrawCore
modifier|*
name|core
decl_stmt|;
comment|/*  Core select object          */
DECL|member|x
DECL|member|y
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  upper left hand coordinate  */
DECL|member|w
DECL|member|h
name|int
name|w
decl_stmt|,
name|h
decl_stmt|;
comment|/*  width and height            */
DECL|member|op
name|int
name|op
decl_stmt|;
comment|/*  magnify operation           */
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|MagnifyOptions
typedef|typedef
name|struct
name|_MagnifyOptions
name|MagnifyOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_MagnifyOptions
struct|struct
name|_MagnifyOptions
block|{
DECL|member|tool_options
name|ToolOptions
name|tool_options
decl_stmt|;
comment|/* int       allow_resize_windows; (from gimprc) */
DECL|member|allow_resize_d
name|int
name|allow_resize_d
decl_stmt|;
DECL|member|allow_resize_w
name|GtkWidget
modifier|*
name|allow_resize_w
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  the magnify tool options  */
end_comment

begin_decl_stmt
DECL|variable|magnify_options
specifier|static
name|MagnifyOptions
modifier|*
name|magnify_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  magnify utility functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|zoom_in
parameter_list|(
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|zoom_out
parameter_list|(
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  magnify action functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|magnify_button_press
parameter_list|(
name|Tool
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
specifier|static
name|void
name|magnify_button_release
parameter_list|(
name|Tool
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
specifier|static
name|void
name|magnify_motion
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|magnify_cursor_update
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|magnify_control
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|int
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  magnify tool options functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|magnify_options_reset (void)
name|magnify_options_reset
parameter_list|(
name|void
parameter_list|)
block|{
name|MagnifyOptions
modifier|*
name|options
init|=
name|magnify_options
decl_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|allow_resize_w
argument_list|)
argument_list|,
name|options
operator|->
name|allow_resize_d
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|MagnifyOptions
modifier|*
DECL|function|magnify_options_new (void)
name|magnify_options_new
parameter_list|(
name|void
parameter_list|)
block|{
name|MagnifyOptions
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
comment|/*  the new magnify tool options structure  */
name|options
operator|=
operator|(
name|MagnifyOptions
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|MagnifyOptions
argument_list|)
argument_list|)
expr_stmt|;
name|tool_options_init
argument_list|(
operator|(
name|ToolOptions
operator|*
operator|)
name|options
argument_list|,
name|_
argument_list|(
literal|"Magnify Options"
argument_list|)
argument_list|,
name|magnify_options_reset
argument_list|)
expr_stmt|;
name|options
operator|->
name|allow_resize_d
operator|=
name|allow_resize_windows
expr_stmt|;
comment|/*  the main vbox  */
name|vbox
operator|=
name|options
operator|->
name|tool_options
operator|.
name|main_vbox
expr_stmt|;
comment|/*  the allow_resize toggle button  */
name|options
operator|->
name|allow_resize_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Allow Window Resizing"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|allow_resize_w
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|tool_options_toggle_update
argument_list|,
operator|&
name|allow_resize_windows
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|allow_resize_w
argument_list|)
argument_list|,
name|allow_resize_windows
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|options
operator|->
name|allow_resize_w
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|allow_resize_w
argument_list|)
expr_stmt|;
return|return
name|options
return|;
block|}
end_function

begin_comment
comment|/*  magnify utility functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|zoom_in (int * src,int * dest,int scale)
name|zoom_in
parameter_list|(
name|int
modifier|*
name|src
parameter_list|,
name|int
modifier|*
name|dest
parameter_list|,
name|int
name|scale
parameter_list|)
block|{
while|while
condition|(
name|scale
operator|--
condition|)
block|{
if|if
condition|(
operator|*
name|src
operator|>
literal|1
condition|)
operator|(
operator|*
name|src
operator|)
operator|--
expr_stmt|;
elseif|else
if|if
condition|(
operator|*
name|dest
operator|<
literal|0x10
condition|)
operator|(
operator|*
name|dest
operator|)
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|zoom_out (int * src,int * dest,int scale)
name|zoom_out
parameter_list|(
name|int
modifier|*
name|src
parameter_list|,
name|int
modifier|*
name|dest
parameter_list|,
name|int
name|scale
parameter_list|)
block|{
while|while
condition|(
name|scale
operator|--
condition|)
block|{
if|if
condition|(
operator|*
name|dest
operator|>
literal|1
condition|)
operator|(
operator|*
name|dest
operator|)
operator|--
expr_stmt|;
elseif|else
if|if
condition|(
operator|*
name|src
operator|<
literal|0x10
condition|)
operator|(
operator|*
name|src
operator|)
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  magnify action functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|magnify_button_press (Tool * tool,GdkEventButton * bevent,gpointer gdisp_ptr)
name|magnify_button_press
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|Magnify
modifier|*
name|magnify
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
name|magnify
operator|=
operator|(
name|Magnify
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|gdisplay_untransform_coords
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
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|magnify
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|magnify
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|magnify
operator|->
name|w
operator|=
literal|0
expr_stmt|;
name|magnify
operator|->
name|h
operator|=
literal|0
expr_stmt|;
name|gdk_pointer_grab
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|FALSE
argument_list|,
name|GDK_POINTER_MOTION_HINT_MASK
operator||
name|GDK_BUTTON1_MOTION_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
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
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
name|tool
operator|->
name|gdisp_ptr
operator|=
name|gdisp_ptr
expr_stmt|;
if|if
condition|(
name|bevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
name|magnify
operator|->
name|op
operator|=
name|ZOOMOUT
expr_stmt|;
else|else
name|magnify
operator|->
name|op
operator|=
name|ZOOMIN
expr_stmt|;
comment|/*  default  */
name|draw_core_start
argument_list|(
name|magnify
operator|->
name|core
argument_list|,
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|magnify_button_release (Tool * tool,GdkEventButton * bevent,gpointer gdisp_ptr)
name|magnify_button_release
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|Magnify
modifier|*
name|magnify
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|int
name|win_width
decl_stmt|,
name|win_height
decl_stmt|;
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
name|int
name|scalesrc
decl_stmt|,
name|scaledest
decl_stmt|;
name|int
name|scale
decl_stmt|;
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
name|magnify
operator|=
operator|(
name|Magnify
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|gdk_pointer_ungrab
argument_list|(
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
name|draw_core_stop
argument_list|(
name|magnify
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
comment|/*  First take care of the case where the user "cancels" the action  */
if|if
condition|(
operator|!
operator|(
name|bevent
operator|->
name|state
operator|&
name|GDK_BUTTON3_MASK
operator|)
condition|)
block|{
name|x1
operator|=
operator|(
name|magnify
operator|->
name|w
operator|<
literal|0
operator|)
condition|?
name|magnify
operator|->
name|x
operator|+
name|magnify
operator|->
name|w
else|:
name|magnify
operator|->
name|x
expr_stmt|;
name|y1
operator|=
operator|(
name|magnify
operator|->
name|h
operator|<
literal|0
operator|)
condition|?
name|magnify
operator|->
name|y
operator|+
name|magnify
operator|->
name|h
else|:
name|magnify
operator|->
name|y
expr_stmt|;
name|w
operator|=
operator|(
name|magnify
operator|->
name|w
operator|<
literal|0
operator|)
condition|?
operator|-
name|magnify
operator|->
name|w
else|:
name|magnify
operator|->
name|w
expr_stmt|;
name|h
operator|=
operator|(
name|magnify
operator|->
name|h
operator|<
literal|0
operator|)
condition|?
operator|-
name|magnify
operator|->
name|h
else|:
name|magnify
operator|->
name|h
expr_stmt|;
name|x2
operator|=
name|x1
operator|+
name|w
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
name|h
expr_stmt|;
comment|/* these change the user zoom level, so should not be changed to        * the resolution-aware scale macros -- austin */
name|scalesrc
operator|=
name|SCALESRC
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|scaledest
operator|=
name|SCALEDEST
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|win_width
operator|=
name|gdisp
operator|->
name|disp_width
expr_stmt|;
name|win_height
operator|=
name|gdisp
operator|->
name|disp_height
expr_stmt|;
name|width
operator|=
operator|(
name|win_width
operator|*
name|scalesrc
operator|)
operator|/
name|scaledest
expr_stmt|;
name|height
operator|=
operator|(
name|win_height
operator|*
name|scalesrc
operator|)
operator|/
name|scaledest
expr_stmt|;
if|if
condition|(
operator|!
name|w
operator|||
operator|!
name|h
condition|)
name|scale
operator|=
literal|1
expr_stmt|;
else|else
name|scale
operator|=
name|MINIMUM
argument_list|(
operator|(
name|width
operator|/
name|w
operator|)
argument_list|,
operator|(
name|height
operator|/
name|h
operator|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|magnify
operator|->
name|op
condition|)
block|{
case|case
name|ZOOMIN
case|:
name|zoom_in
argument_list|(
operator|&
name|scalesrc
argument_list|,
operator|&
name|scaledest
argument_list|,
name|scale
argument_list|)
expr_stmt|;
break|break;
case|case
name|ZOOMOUT
case|:
name|zoom_out
argument_list|(
operator|&
name|scalesrc
argument_list|,
operator|&
name|scaledest
argument_list|,
name|scale
argument_list|)
expr_stmt|;
break|break;
block|}
name|gdisp
operator|->
name|scale
operator|=
operator|(
name|scaledest
operator|<<
literal|8
operator|)
operator|+
name|scalesrc
expr_stmt|;
name|gdisp
operator|->
name|offset_x
operator|=
operator|(
name|scaledest
operator|*
operator|(
operator|(
name|x1
operator|+
name|x2
operator|)
operator|/
literal|2
operator|)
operator|)
operator|/
name|scalesrc
operator|-
operator|(
name|win_width
operator|/
literal|2
operator|)
expr_stmt|;
name|gdisp
operator|->
name|offset_y
operator|=
operator|(
name|scaledest
operator|*
operator|(
operator|(
name|y1
operator|+
name|y2
operator|)
operator|/
literal|2
operator|)
operator|)
operator|/
name|scalesrc
operator|-
operator|(
name|win_height
operator|/
literal|2
operator|)
expr_stmt|;
comment|/*  resize the image  */
name|resize_display
argument_list|(
name|gdisp
argument_list|,
name|allow_resize_windows
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|magnify_motion (Tool * tool,GdkEventMotion * mevent,gpointer gdisp_ptr)
name|magnify_motion
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|Magnify
modifier|*
name|magnify
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|state
operator|!=
name|ACTIVE
condition|)
return|return;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
name|magnify
operator|=
operator|(
name|Magnify
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|draw_core_pause
argument_list|(
name|magnify
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|gdisplay_untransform_coords
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
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|magnify
operator|->
name|w
operator|=
operator|(
name|x
operator|-
name|magnify
operator|->
name|x
operator|)
expr_stmt|;
name|magnify
operator|->
name|h
operator|=
operator|(
name|y
operator|-
name|magnify
operator|->
name|y
operator|)
expr_stmt|;
name|draw_core_resume
argument_list|(
name|magnify
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|magnify_cursor_update (Tool * tool,GdkEventMotion * mevent,gpointer gdisp_ptr)
name|magnify_cursor_update
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|gpointer
name|gdisp_ptr
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
name|gdisp_ptr
expr_stmt|;
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_TCROSS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|magnify_draw (Tool * tool)
name|magnify_draw
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|Magnify
modifier|*
name|magnify
decl_stmt|;
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|tool
operator|->
name|gdisp_ptr
expr_stmt|;
name|magnify
operator|=
operator|(
name|Magnify
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|x1
operator|=
name|MINIMUM
argument_list|(
name|magnify
operator|->
name|x
argument_list|,
name|magnify
operator|->
name|x
operator|+
name|magnify
operator|->
name|w
argument_list|)
expr_stmt|;
name|y1
operator|=
name|MINIMUM
argument_list|(
name|magnify
operator|->
name|y
argument_list|,
name|magnify
operator|->
name|y
operator|+
name|magnify
operator|->
name|h
argument_list|)
expr_stmt|;
name|x2
operator|=
name|MAXIMUM
argument_list|(
name|magnify
operator|->
name|x
argument_list|,
name|magnify
operator|->
name|x
operator|+
name|magnify
operator|->
name|w
argument_list|)
expr_stmt|;
name|y2
operator|=
name|MAXIMUM
argument_list|(
name|magnify
operator|->
name|y
argument_list|,
name|magnify
operator|->
name|y
operator|+
name|magnify
operator|->
name|h
argument_list|)
expr_stmt|;
name|gdisplay_transform_coords
argument_list|(
name|gdisp
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gdisplay_transform_coords
argument_list|(
name|gdisp
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gdk_draw_rectangle
argument_list|(
name|magnify
operator|->
name|core
operator|->
name|win
argument_list|,
name|magnify
operator|->
name|core
operator|->
name|gc
argument_list|,
literal|0
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|magnify_control (Tool * tool,int action,gpointer gdisp_ptr)
name|magnify_control
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|int
name|action
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|Magnify
modifier|*
name|magnify
decl_stmt|;
name|magnify
operator|=
operator|(
name|Magnify
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|PAUSE
case|:
name|draw_core_pause
argument_list|(
name|magnify
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|RESUME
case|:
name|draw_core_resume
argument_list|(
name|magnify
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|HALT
case|:
name|draw_core_stop
argument_list|(
name|magnify
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_magnify (void)
name|tools_new_magnify
parameter_list|(
name|void
parameter_list|)
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|Magnify
modifier|*
name|private
decl_stmt|;
comment|/*  The tool options  */
if|if
condition|(
operator|!
name|magnify_options
condition|)
block|{
name|magnify_options
operator|=
name|magnify_options_new
argument_list|()
expr_stmt|;
name|tools_register
argument_list|(
name|MAGNIFY
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|magnify_options
argument_list|)
expr_stmt|;
block|}
name|tool
operator|=
operator|(
name|Tool
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|Tool
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
operator|(
name|Magnify
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|Magnify
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|->
name|core
operator|=
name|draw_core_new
argument_list|(
name|magnify_draw
argument_list|)
expr_stmt|;
name|private
operator|->
name|x
operator|=
name|private
operator|->
name|y
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|w
operator|=
name|private
operator|->
name|h
operator|=
literal|0
expr_stmt|;
name|tool
operator|->
name|type
operator|=
name|MAGNIFY
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
literal|1
expr_stmt|;
comment|/*  disallow scrolling  */
name|tool
operator|->
name|auto_snap_to
operator|=
name|FALSE
expr_stmt|;
name|tool
operator|->
name|private
operator|=
operator|(
name|void
operator|*
operator|)
name|private
expr_stmt|;
name|tool
operator|->
name|button_press_func
operator|=
name|magnify_button_press
expr_stmt|;
name|tool
operator|->
name|button_release_func
operator|=
name|magnify_button_release
expr_stmt|;
name|tool
operator|->
name|motion_func
operator|=
name|magnify_motion
expr_stmt|;
name|tool
operator|->
name|arrow_keys_func
operator|=
name|standard_arrow_keys_func
expr_stmt|;
name|tool
operator|->
name|cursor_update_func
operator|=
name|magnify_cursor_update
expr_stmt|;
name|tool
operator|->
name|control_func
operator|=
name|magnify_control
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_magnify (Tool * tool)
name|tools_free_magnify
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|Magnify
modifier|*
name|magnify
decl_stmt|;
name|magnify
operator|=
operator|(
name|Magnify
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|draw_core_free
argument_list|(
name|magnify
operator|->
name|core
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|magnify
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

