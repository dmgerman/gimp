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
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay_ops.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"nav_window.h"
end_include

begin_include
include|#
directive|include
file|"scale.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_function
name|void
DECL|function|bounds_checking (GDisplay * gdisp)
name|bounds_checking
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
name|sx
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
name|sy
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
name|gdisp
operator|->
name|offset_x
operator|=
name|BOUNDS
argument_list|(
name|gdisp
operator|->
name|offset_x
argument_list|,
literal|0
argument_list|,
name|LOWPASS
argument_list|(
name|sx
operator|-
name|gdisp
operator|->
name|disp_width
argument_list|)
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|offset_y
operator|=
name|BOUNDS
argument_list|(
name|gdisp
operator|->
name|offset_y
argument_list|,
literal|0
argument_list|,
name|LOWPASS
argument_list|(
name|sy
operator|-
name|gdisp
operator|->
name|disp_height
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|resize_display (GDisplay * gdisp,int resize_window,int redisplay)
name|resize_display
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|int
name|resize_window
parameter_list|,
name|int
name|redisplay
parameter_list|)
block|{
comment|/* freeze the active tool */
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
if|if
condition|(
name|resize_window
condition|)
name|gdisplay_shrink_wrap
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|bounds_checking
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|setup_scale
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
if|if
condition|(
name|redisplay
condition|)
block|{
name|gdisplay_expose_full
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
comment|/* title may have changed if it includes the zoom ratio */
name|gdisplay_update_title
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
comment|/* re-enable the active tool */
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
block|}
end_function

begin_function
name|void
DECL|function|shrink_wrap_display (GDisplay * gdisp)
name|shrink_wrap_display
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
comment|/* freeze the active tool */
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
name|gdisplay_shrink_wrap
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|bounds_checking
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|setup_scale
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|gdisplay_expose_full
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
comment|/* re-enable the active tool */
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
block|}
end_function

begin_function
name|void
DECL|function|change_scale (GDisplay * gdisp,int dir)
name|change_scale
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|int
name|dir
parameter_list|)
block|{
name|unsigned
name|char
name|scalesrc
decl_stmt|,
name|scaledest
decl_stmt|;
name|double
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
name|long
name|sx
decl_stmt|,
name|sy
decl_stmt|;
comment|/* user zoom control, so resolution versions not needed -- austin */
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
name|offset_x
operator|=
name|gdisp
operator|->
name|offset_x
operator|+
operator|(
name|gdisp
operator|->
name|disp_width
operator|/
literal|2.0
operator|)
expr_stmt|;
name|offset_y
operator|=
name|gdisp
operator|->
name|offset_y
operator|+
operator|(
name|gdisp
operator|->
name|disp_height
operator|/
literal|2.0
operator|)
expr_stmt|;
name|offset_x
operator|*=
operator|(
operator|(
name|double
operator|)
name|scalesrc
operator|/
operator|(
name|double
operator|)
name|scaledest
operator|)
expr_stmt|;
name|offset_y
operator|*=
operator|(
operator|(
name|double
operator|)
name|scalesrc
operator|/
operator|(
name|double
operator|)
name|scaledest
operator|)
expr_stmt|;
switch|switch
condition|(
name|dir
condition|)
block|{
case|case
name|ZOOMIN
case|:
if|if
condition|(
name|scalesrc
operator|>
literal|1
condition|)
name|scalesrc
operator|--
expr_stmt|;
elseif|else
if|if
condition|(
name|scaledest
operator|<
literal|0x10
condition|)
name|scaledest
operator|++
expr_stmt|;
break|break;
case|case
name|ZOOMOUT
case|:
if|if
condition|(
name|scaledest
operator|>
literal|1
condition|)
name|scaledest
operator|--
expr_stmt|;
elseif|else
if|if
condition|(
name|scalesrc
operator|<
literal|0x10
condition|)
name|scalesrc
operator|++
expr_stmt|;
break|break;
default|default :
name|scalesrc
operator|=
name|dir
operator|%
literal|100
expr_stmt|;
if|if
condition|(
name|scalesrc
operator|<
literal|1
condition|)
name|scalesrc
operator|=
literal|1
expr_stmt|;
elseif|else
if|if
condition|(
name|scalesrc
operator|>
literal|0x10
condition|)
name|scalesrc
operator|=
literal|0x10
expr_stmt|;
name|scaledest
operator|=
name|dir
operator|/
literal|100
expr_stmt|;
if|if
condition|(
name|scaledest
operator|<
literal|1
condition|)
name|scaledest
operator|=
literal|1
expr_stmt|;
elseif|else
if|if
condition|(
name|scaledest
operator|>
literal|0x10
condition|)
name|scaledest
operator|=
literal|0x10
expr_stmt|;
break|break;
block|}
name|sx
operator|=
operator|(
name|gdisp
operator|->
name|gimage
operator|->
name|width
operator|*
name|scaledest
operator|)
operator|/
name|scalesrc
expr_stmt|;
name|sy
operator|=
operator|(
name|gdisp
operator|->
name|gimage
operator|->
name|height
operator|*
name|scaledest
operator|)
operator|/
name|scalesrc
expr_stmt|;
comment|/*  The slider value is a short, so make sure we are within its       range.  If we are trying to scale past it, then stop the scale  */
if|if
condition|(
name|sx
operator|<
literal|0xffff
operator|&&
name|sy
operator|<
literal|0xffff
condition|)
block|{
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
comment|/*  set the offsets  */
name|offset_x
operator|*=
operator|(
operator|(
name|double
operator|)
name|scaledest
operator|/
operator|(
name|double
operator|)
name|scalesrc
operator|)
expr_stmt|;
name|offset_y
operator|*=
operator|(
operator|(
name|double
operator|)
name|scaledest
operator|/
operator|(
name|double
operator|)
name|scalesrc
operator|)
expr_stmt|;
name|gdisp
operator|->
name|offset_x
operator|=
call|(
name|int
call|)
argument_list|(
name|offset_x
operator|-
operator|(
name|gdisp
operator|->
name|disp_width
operator|/
literal|2
operator|)
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|offset_y
operator|=
call|(
name|int
call|)
argument_list|(
name|offset_y
operator|-
operator|(
name|gdisp
operator|->
name|disp_height
operator|/
literal|2
operator|)
argument_list|)
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

begin_comment
comment|/* scale image coord to realworld units (cm, inches, pixels) */
end_comment

begin_comment
comment|/* 27/Feb/1999 I tried inlining this, but the result was slightly  * slower (poorer cache locality, probably) -- austin */
end_comment

begin_function
specifier|static
name|gdouble
DECL|function|img2real (GDisplay * gdisp,gboolean xdir,gdouble a)
name|img2real
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|gboolean
name|xdir
parameter_list|,
name|gdouble
name|a
parameter_list|)
block|{
name|gdouble
name|res
decl_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|dot_for_dot
condition|)
return|return
name|a
return|;
if|if
condition|(
name|xdir
condition|)
name|res
operator|=
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
expr_stmt|;
else|else
name|res
operator|=
name|gdisp
operator|->
name|gimage
operator|->
name|yresolution
expr_stmt|;
return|return
name|a
operator|*
name|gimp_unit_get_factor
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|unit
argument_list|)
operator|/
name|res
return|;
block|}
end_function

begin_function
name|void
DECL|function|setup_scale (GDisplay * gdisp)
name|setup_scale
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GtkRuler
modifier|*
name|hruler
decl_stmt|;
name|GtkRuler
modifier|*
name|vruler
decl_stmt|;
name|gfloat
name|sx
decl_stmt|,
name|sy
decl_stmt|;
name|gfloat
name|stepx
decl_stmt|,
name|stepy
decl_stmt|;
name|sx
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
name|sy
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
name|stepx
operator|=
name|SCALEFACTOR_X
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|stepy
operator|=
name|SCALEFACTOR_Y
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|hsbdata
operator|->
name|value
operator|=
name|gdisp
operator|->
name|offset_x
expr_stmt|;
name|gdisp
operator|->
name|hsbdata
operator|->
name|upper
operator|=
name|sx
expr_stmt|;
name|gdisp
operator|->
name|hsbdata
operator|->
name|page_size
operator|=
name|MIN
argument_list|(
name|sx
argument_list|,
name|gdisp
operator|->
name|disp_width
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|hsbdata
operator|->
name|page_increment
operator|=
operator|(
name|gdisp
operator|->
name|disp_width
operator|/
literal|2
operator|)
expr_stmt|;
name|gdisp
operator|->
name|hsbdata
operator|->
name|step_increment
operator|=
name|stepx
expr_stmt|;
name|gdisp
operator|->
name|vsbdata
operator|->
name|value
operator|=
name|gdisp
operator|->
name|offset_y
expr_stmt|;
name|gdisp
operator|->
name|vsbdata
operator|->
name|upper
operator|=
name|sy
expr_stmt|;
name|gdisp
operator|->
name|vsbdata
operator|->
name|page_size
operator|=
name|MIN
argument_list|(
name|sy
argument_list|,
name|gdisp
operator|->
name|disp_height
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|vsbdata
operator|->
name|page_increment
operator|=
operator|(
name|gdisp
operator|->
name|disp_height
operator|/
literal|2
operator|)
expr_stmt|;
name|gdisp
operator|->
name|vsbdata
operator|->
name|step_increment
operator|=
name|stepy
expr_stmt|;
name|gtk_signal_emit_by_name
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gdisp
operator|->
name|hsbdata
argument_list|)
argument_list|,
literal|"changed"
argument_list|)
expr_stmt|;
name|gtk_signal_emit_by_name
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gdisp
operator|->
name|vsbdata
argument_list|)
argument_list|,
literal|"changed"
argument_list|)
expr_stmt|;
name|hruler
operator|=
name|GTK_RULER
argument_list|(
name|gdisp
operator|->
name|hrule
argument_list|)
expr_stmt|;
name|vruler
operator|=
name|GTK_RULER
argument_list|(
name|gdisp
operator|->
name|vrule
argument_list|)
expr_stmt|;
name|hruler
operator|->
name|lower
operator|=
literal|0
expr_stmt|;
name|hruler
operator|->
name|upper
operator|=
name|img2real
argument_list|(
name|gdisp
argument_list|,
name|TRUE
argument_list|,
name|FUNSCALEX
argument_list|(
name|gdisp
argument_list|,
name|gdisp
operator|->
name|disp_width
argument_list|)
argument_list|)
expr_stmt|;
name|hruler
operator|->
name|max_size
operator|=
name|img2real
argument_list|(
name|gdisp
argument_list|,
name|TRUE
argument_list|,
name|MAXIMUM
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
argument_list|)
expr_stmt|;
name|vruler
operator|->
name|lower
operator|=
literal|0
expr_stmt|;
name|vruler
operator|->
name|upper
operator|=
name|img2real
argument_list|(
name|gdisp
argument_list|,
name|FALSE
argument_list|,
name|FUNSCALEY
argument_list|(
name|gdisp
argument_list|,
name|gdisp
operator|->
name|disp_height
argument_list|)
argument_list|)
expr_stmt|;
name|vruler
operator|->
name|max_size
operator|=
name|img2real
argument_list|(
name|gdisp
argument_list|,
name|FALSE
argument_list|,
name|MAXIMUM
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|sx
operator|<
name|gdisp
operator|->
name|disp_width
condition|)
block|{
name|gdisp
operator|->
name|disp_xoffset
operator|=
operator|(
name|gdisp
operator|->
name|disp_width
operator|-
name|sx
operator|)
operator|/
literal|2
expr_stmt|;
name|hruler
operator|->
name|lower
operator|-=
name|img2real
argument_list|(
name|gdisp
argument_list|,
name|TRUE
argument_list|,
name|FUNSCALEX
argument_list|(
name|gdisp
argument_list|,
operator|(
name|double
operator|)
name|gdisp
operator|->
name|disp_xoffset
argument_list|)
argument_list|)
expr_stmt|;
name|hruler
operator|->
name|upper
operator|-=
name|img2real
argument_list|(
name|gdisp
argument_list|,
name|TRUE
argument_list|,
name|FUNSCALEX
argument_list|(
name|gdisp
argument_list|,
operator|(
name|double
operator|)
name|gdisp
operator|->
name|disp_xoffset
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdisp
operator|->
name|disp_xoffset
operator|=
literal|0
expr_stmt|;
name|hruler
operator|->
name|lower
operator|+=
name|img2real
argument_list|(
name|gdisp
argument_list|,
name|TRUE
argument_list|,
name|FUNSCALEX
argument_list|(
name|gdisp
argument_list|,
operator|(
name|double
operator|)
name|gdisp
operator|->
name|offset_x
argument_list|)
argument_list|)
expr_stmt|;
name|hruler
operator|->
name|upper
operator|+=
name|img2real
argument_list|(
name|gdisp
argument_list|,
name|TRUE
argument_list|,
name|FUNSCALEX
argument_list|(
name|gdisp
argument_list|,
operator|(
name|double
operator|)
name|gdisp
operator|->
name|offset_x
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|sy
operator|<
name|gdisp
operator|->
name|disp_height
condition|)
block|{
name|gdisp
operator|->
name|disp_yoffset
operator|=
operator|(
name|gdisp
operator|->
name|disp_height
operator|-
name|sy
operator|)
operator|/
literal|2
expr_stmt|;
name|vruler
operator|->
name|lower
operator|-=
name|img2real
argument_list|(
name|gdisp
argument_list|,
name|FALSE
argument_list|,
name|FUNSCALEY
argument_list|(
name|gdisp
argument_list|,
operator|(
name|double
operator|)
name|gdisp
operator|->
name|disp_yoffset
argument_list|)
argument_list|)
expr_stmt|;
name|vruler
operator|->
name|upper
operator|-=
name|img2real
argument_list|(
name|gdisp
argument_list|,
name|FALSE
argument_list|,
name|FUNSCALEY
argument_list|(
name|gdisp
argument_list|,
operator|(
name|double
operator|)
name|gdisp
operator|->
name|disp_yoffset
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdisp
operator|->
name|disp_yoffset
operator|=
literal|0
expr_stmt|;
name|vruler
operator|->
name|lower
operator|+=
name|img2real
argument_list|(
name|gdisp
argument_list|,
name|FALSE
argument_list|,
name|FUNSCALEY
argument_list|(
name|gdisp
argument_list|,
operator|(
name|double
operator|)
name|gdisp
operator|->
name|offset_y
argument_list|)
argument_list|)
expr_stmt|;
name|vruler
operator|->
name|upper
operator|+=
name|img2real
argument_list|(
name|gdisp
argument_list|,
name|FALSE
argument_list|,
name|FUNSCALEY
argument_list|(
name|gdisp
argument_list|,
operator|(
name|double
operator|)
name|gdisp
operator|->
name|offset_y
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|hruler
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|vruler
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|window_nav_dialog
condition|)
name|nav_window_update_window_marker
argument_list|(
name|gdisp
operator|->
name|window_nav_dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

