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
file|"color_area.h"
end_include

begin_include
include|#
directive|include
file|"color_select.h"
end_include

begin_include
include|#
directive|include
file|"colormaps.h"
end_include

begin_include
include|#
directive|include
file|"palette.h"
end_include

begin_define
DECL|macro|FORE_AREA
define|#
directive|define
name|FORE_AREA
value|0
end_define

begin_define
DECL|macro|BACK_AREA
define|#
directive|define
name|BACK_AREA
value|1
end_define

begin_define
DECL|macro|SWAP_AREA
define|#
directive|define
name|SWAP_AREA
value|2
end_define

begin_define
DECL|macro|DEF_AREA
define|#
directive|define
name|DEF_AREA
value|3
end_define

begin_comment
comment|/*  Global variables  */
end_comment

begin_decl_stmt
DECL|variable|active_color
name|int
name|active_color
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Static variables  */
end_comment

begin_decl_stmt
DECL|variable|color_area_gc
specifier|static
name|GdkGC
modifier|*
name|color_area_gc
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_area
specifier|static
name|GtkWidget
modifier|*
name|color_area
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_area_pixmap
specifier|static
name|GdkPixmap
modifier|*
name|color_area_pixmap
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|default_pixmap
specifier|static
name|GdkPixmap
modifier|*
name|default_pixmap
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|swap_pixmap
specifier|static
name|GdkPixmap
modifier|*
name|swap_pixmap
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_select
specifier|static
name|ColorSelectP
name|color_select
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_select_active
specifier|static
name|int
name|color_select_active
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_color
specifier|static
name|int
name|edit_color
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|revert_fg_r
DECL|variable|revert_fg_g
DECL|variable|revert_fg_b
specifier|static
name|unsigned
name|char
name|revert_fg_r
decl_stmt|,
name|revert_fg_g
decl_stmt|,
name|revert_fg_b
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|revert_bg_r
DECL|variable|revert_bg_g
DECL|variable|revert_bg_b
specifier|static
name|unsigned
name|char
name|revert_bg_r
decl_stmt|,
name|revert_bg_g
decl_stmt|,
name|revert_bg_b
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Local functions  */
end_comment

begin_function
specifier|static
name|int
DECL|function|color_area_target (int x,int y)
name|color_area_target
parameter_list|(
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|)
block|{
name|int
name|rect_w
decl_stmt|,
name|rect_h
decl_stmt|;
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gdk_window_get_size
argument_list|(
name|color_area_pixmap
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|rect_w
operator|=
name|width
operator|*
literal|0.65
expr_stmt|;
name|rect_h
operator|=
name|height
operator|*
literal|0.65
expr_stmt|;
comment|/*  foreground active  */
if|if
condition|(
name|x
operator|>
literal|0
operator|&&
name|x
operator|<
name|rect_w
operator|&&
name|y
operator|>
literal|0
operator|&&
name|y
operator|<
name|rect_h
condition|)
return|return
name|FORE_AREA
return|;
elseif|else
if|if
condition|(
name|x
operator|>
operator|(
name|width
operator|-
name|rect_w
operator|)
operator|&&
name|x
operator|<
name|width
operator|&&
name|y
operator|>
operator|(
name|height
operator|-
name|rect_h
operator|)
operator|&&
name|y
operator|<
name|height
condition|)
return|return
name|BACK_AREA
return|;
elseif|else
if|if
condition|(
name|x
operator|>
literal|0
operator|&&
name|x
operator|<
operator|(
name|width
operator|-
name|rect_w
operator|)
operator|&&
name|y
operator|>
name|rect_h
operator|&&
name|y
operator|<
name|height
condition|)
return|return
name|DEF_AREA
return|;
elseif|else
if|if
condition|(
name|x
operator|>
name|rect_w
operator|&&
name|x
operator|<
name|width
operator|&&
name|y
operator|>
literal|0
operator|&&
name|y
operator|<
operator|(
name|height
operator|-
name|rect_h
operator|)
condition|)
return|return
name|SWAP_AREA
return|;
else|else
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_area_draw (void)
name|color_area_draw
parameter_list|(
name|void
parameter_list|)
block|{
name|GdkColor
modifier|*
name|win_bg
decl_stmt|;
name|GdkColor
name|fg
decl_stmt|,
name|bg
decl_stmt|,
name|bd
decl_stmt|;
name|int
name|rect_w
decl_stmt|,
name|rect_h
decl_stmt|;
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
name|int
name|def_width
decl_stmt|,
name|def_height
decl_stmt|;
name|int
name|swap_width
decl_stmt|,
name|swap_height
decl_stmt|;
if|if
condition|(
operator|!
name|color_area_pixmap
condition|)
comment|/* we haven't gotten initial expose yet,                                * no point in drawing anything */
return|return;
name|gdk_window_get_size
argument_list|(
name|color_area_pixmap
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|win_bg
operator|=
operator|&
operator|(
name|color_area
operator|->
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
operator|)
expr_stmt|;
name|fg
operator|.
name|pixel
operator|=
name|foreground_pixel
expr_stmt|;
name|bg
operator|.
name|pixel
operator|=
name|background_pixel
expr_stmt|;
name|bd
operator|.
name|pixel
operator|=
name|g_black_pixel
expr_stmt|;
name|rect_w
operator|=
name|width
operator|*
literal|0.65
expr_stmt|;
name|rect_h
operator|=
name|height
operator|*
literal|0.65
expr_stmt|;
name|gdk_gc_set_foreground
argument_list|(
name|color_area_gc
argument_list|,
name|win_bg
argument_list|)
expr_stmt|;
name|gdk_draw_rectangle
argument_list|(
name|color_area_pixmap
argument_list|,
name|color_area_gc
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gdk_gc_set_foreground
argument_list|(
name|color_area_gc
argument_list|,
operator|&
name|bg
argument_list|)
expr_stmt|;
name|gdk_draw_rectangle
argument_list|(
name|color_area_pixmap
argument_list|,
name|color_area_gc
argument_list|,
literal|1
argument_list|,
operator|(
name|width
operator|-
name|rect_w
operator|)
argument_list|,
operator|(
name|height
operator|-
name|rect_h
operator|)
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
if|if
condition|(
name|active_color
operator|==
name|FOREGROUND
condition|)
name|gtk_draw_shadow
argument_list|(
name|color_area
operator|->
name|style
argument_list|,
name|color_area_pixmap
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|GTK_SHADOW_OUT
argument_list|,
operator|(
name|width
operator|-
name|rect_w
operator|)
argument_list|,
operator|(
name|height
operator|-
name|rect_h
operator|)
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
else|else
name|gtk_draw_shadow
argument_list|(
name|color_area
operator|->
name|style
argument_list|,
name|color_area_pixmap
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|GTK_SHADOW_IN
argument_list|,
operator|(
name|width
operator|-
name|rect_w
operator|)
argument_list|,
operator|(
name|height
operator|-
name|rect_h
operator|)
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
name|gdk_gc_set_foreground
argument_list|(
name|color_area_gc
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
name|gdk_draw_rectangle
argument_list|(
name|color_area_pixmap
argument_list|,
name|color_area_gc
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
if|if
condition|(
name|active_color
operator|==
name|FOREGROUND
condition|)
name|gtk_draw_shadow
argument_list|(
name|color_area
operator|->
name|style
argument_list|,
name|color_area_pixmap
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|GTK_SHADOW_IN
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
else|else
name|gtk_draw_shadow
argument_list|(
name|color_area
operator|->
name|style
argument_list|,
name|color_area_pixmap
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|GTK_SHADOW_OUT
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
name|gdk_window_get_size
argument_list|(
name|default_pixmap
argument_list|,
operator|&
name|def_width
argument_list|,
operator|&
name|def_height
argument_list|)
expr_stmt|;
name|gdk_draw_pixmap
argument_list|(
name|color_area_pixmap
argument_list|,
name|color_area_gc
argument_list|,
name|default_pixmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|height
operator|-
name|def_height
argument_list|,
name|def_width
argument_list|,
name|def_height
argument_list|)
expr_stmt|;
name|gdk_window_get_size
argument_list|(
name|swap_pixmap
argument_list|,
operator|&
name|swap_width
argument_list|,
operator|&
name|swap_height
argument_list|)
expr_stmt|;
name|gdk_draw_pixmap
argument_list|(
name|color_area_pixmap
argument_list|,
name|color_area_gc
argument_list|,
name|swap_pixmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
operator|-
name|swap_width
argument_list|,
literal|0
argument_list|,
name|swap_width
argument_list|,
name|swap_height
argument_list|)
expr_stmt|;
name|gdk_draw_pixmap
argument_list|(
name|color_area
operator|->
name|window
argument_list|,
name|color_area_gc
argument_list|,
name|color_area_pixmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_area_select_callback (int r,int g,int b,ColorSelectState state,void * client_data)
name|color_area_select_callback
parameter_list|(
name|int
name|r
parameter_list|,
name|int
name|g
parameter_list|,
name|int
name|b
parameter_list|,
name|ColorSelectState
name|state
parameter_list|,
name|void
modifier|*
name|client_data
parameter_list|)
block|{
if|if
condition|(
name|color_select
condition|)
block|{
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|COLOR_SELECT_OK
case|:
name|color_select_hide
argument_list|(
name|color_select
argument_list|)
expr_stmt|;
name|color_select_active
operator|=
literal|0
expr_stmt|;
comment|/* Fallthrough */
case|case
name|COLOR_SELECT_UPDATE
case|:
if|if
condition|(
name|edit_color
operator|==
name|FOREGROUND
condition|)
name|palette_set_foreground
argument_list|(
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
else|else
name|palette_set_background
argument_list|(
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
break|break;
case|case
name|COLOR_SELECT_CANCEL
case|:
name|color_select_hide
argument_list|(
name|color_select
argument_list|)
expr_stmt|;
name|color_select_active
operator|=
literal|0
expr_stmt|;
name|palette_set_foreground
argument_list|(
name|revert_fg_r
argument_list|,
name|revert_fg_g
argument_list|,
name|revert_fg_b
argument_list|)
expr_stmt|;
name|palette_set_background
argument_list|(
name|revert_bg_r
argument_list|,
name|revert_bg_g
argument_list|,
name|revert_bg_b
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_area_edit (void)
name|color_area_edit
parameter_list|(
name|void
parameter_list|)
block|{
name|unsigned
name|char
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
if|if
condition|(
operator|!
name|color_select_active
condition|)
block|{
name|palette_get_foreground
argument_list|(
operator|&
name|revert_fg_r
argument_list|,
operator|&
name|revert_fg_g
argument_list|,
operator|&
name|revert_fg_b
argument_list|)
expr_stmt|;
name|palette_get_background
argument_list|(
operator|&
name|revert_bg_r
argument_list|,
operator|&
name|revert_bg_g
argument_list|,
operator|&
name|revert_bg_b
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|active_color
operator|==
name|FOREGROUND
condition|)
block|{
name|palette_get_foreground
argument_list|(
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|edit_color
operator|=
name|FOREGROUND
expr_stmt|;
block|}
else|else
block|{
name|palette_get_background
argument_list|(
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|edit_color
operator|=
name|BACKGROUND
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|color_select
condition|)
block|{
name|color_select
operator|=
name|color_select_new
argument_list|(
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
name|color_area_select_callback
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_select_active
operator|=
literal|1
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|color_select_active
condition|)
name|color_select_show
argument_list|(
name|color_select
argument_list|)
expr_stmt|;
else|else
name|gdk_window_raise
argument_list|(
name|color_select
operator|->
name|shell
operator|->
name|window
argument_list|)
expr_stmt|;
name|color_select_set_color
argument_list|(
name|color_select
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|color_area_events (GtkWidget * widget,GdkEvent * event)
name|color_area_events
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
name|int
name|target
decl_stmt|;
switch|switch
condition|(
name|event
operator|->
name|type
condition|)
block|{
case|case
name|GDK_CONFIGURE
case|:
if|if
condition|(
name|color_area_pixmap
condition|)
name|gdk_pixmap_unref
argument_list|(
name|color_area_pixmap
argument_list|)
expr_stmt|;
name|color_area_pixmap
operator|=
name|gdk_pixmap_new
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|width
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|height
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
break|break;
case|case
name|GDK_EXPOSE
case|:
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|widget
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|color_area_gc
condition|)
name|color_area_gc
operator|=
name|gdk_gc_new
argument_list|(
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
name|color_area_draw
argument_list|()
expr_stmt|;
block|}
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
switch|switch
condition|(
operator|(
name|target
operator|=
name|color_area_target
argument_list|(
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|)
operator|)
condition|)
block|{
case|case
name|FORE_AREA
case|:
case|case
name|BACK_AREA
case|:
if|if
condition|(
name|target
operator|==
name|active_color
condition|)
name|color_area_edit
argument_list|()
expr_stmt|;
else|else
block|{
name|active_color
operator|=
name|target
expr_stmt|;
name|color_area_draw
argument_list|()
expr_stmt|;
block|}
break|break;
case|case
name|SWAP_AREA
case|:
name|palette_swap_colors
argument_list|()
expr_stmt|;
name|color_area_draw
argument_list|()
expr_stmt|;
break|break;
case|case
name|DEF_AREA
case|:
name|palette_set_default_colors
argument_list|()
expr_stmt|;
name|color_area_draw
argument_list|()
expr_stmt|;
break|break;
block|}
block|}
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
DECL|function|color_area_create (int width,int height,GdkPixmap * default_pmap,GdkPixmap * swap_pmap)
name|color_area_create
parameter_list|(
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|,
name|GdkPixmap
modifier|*
name|default_pmap
parameter_list|,
name|GdkPixmap
modifier|*
name|swap_pmap
parameter_list|)
block|{
name|color_area
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gtk_drawing_area_size
argument_list|(
name|GTK_DRAWING_AREA
argument_list|(
name|color_area
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|color_area
argument_list|,
name|GDK_EXPOSURE_MASK
operator||
name|GDK_BUTTON_PRESS_MASK
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|color_area
argument_list|)
argument_list|,
literal|"event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|color_area_events
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|default_pixmap
operator|=
name|default_pmap
expr_stmt|;
name|swap_pixmap
operator|=
name|swap_pmap
expr_stmt|;
return|return
name|color_area
return|;
block|}
end_function

begin_function
name|void
DECL|function|color_area_update ()
name|color_area_update
parameter_list|()
block|{
name|color_area_draw
argument_list|()
expr_stmt|;
block|}
end_function

end_unit

