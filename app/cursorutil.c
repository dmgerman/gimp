begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"cursorutil.h"
end_include

begin_include
include|#
directive|include
file|"dialog_handler.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_comment
comment|/* for gdisplay_*_override_cursor() */
end_comment

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"cursors/mouse.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/mouse_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/crosshair.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/crosshair_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/crosshair_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/crosshair_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/bad.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/bad_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/zoom.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/zoom_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/dropper.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/dropper_mask.xbm"
end_include

begin_comment
comment|/* modifiers */
end_comment

begin_include
include|#
directive|include
file|"cursors/plus.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/plus_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/minus.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/minus_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/intersect.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/intersect_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/move.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/move_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/resize.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/resize_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/control.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/control_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/anchor.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/anchor_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/foreground.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/foreground_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/background.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/background_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/pattern.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/pattern_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/hand.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/hand_mask.xbm"
end_include

begin_comment
comment|/* FIXME: gimp_busy HACK */
end_comment

begin_decl_stmt
DECL|variable|gimp_busy
name|gboolean
name|gimp_busy
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_cursors
specifier|static
name|BitmapCursor
name|gimp_cursors
index|[]
init|=
comment|/* these have to match up with the enum in cursorutil.h */
block|{
block|{
name|mouse_bits
block|,
name|mouse_mask_bits
block|,
name|mouse_width
block|,
name|mouse_height
block|,
name|mouse_x_hot
block|,
name|mouse_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|crosshair_bits
block|,
name|crosshair_mask_bits
block|,
name|crosshair_width
block|,
name|crosshair_height
block|,
name|crosshair_x_hot
block|,
name|crosshair_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|crosshair_small_bits
block|,
name|crosshair_small_mask_bits
block|,
name|crosshair_small_width
block|,
name|crosshair_small_height
block|,
name|crosshair_small_x_hot
block|,
name|crosshair_small_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|bad_bits
block|,
name|bad_mask_bits
block|,
name|bad_width
block|,
name|bad_height
block|,
name|bad_x_hot
block|,
name|bad_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|zoom_bits
block|,
name|zoom_mask_bits
block|,
name|zoom_width
block|,
name|zoom_height
block|,
name|zoom_x_hot
block|,
name|zoom_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|dropper_bits
block|,
name|dropper_mask_bits
block|,
name|dropper_width
block|,
name|dropper_height
block|,
name|dropper_x_hot
block|,
name|dropper_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_enum
enum|enum
DECL|enum|__anon2b4517d20103
block|{
DECL|enumerator|GIMP_PLUS_CURSOR
name|GIMP_PLUS_CURSOR
init|=
name|GIMP_LAST_CURSOR_ENTRY
operator|+
literal|1
block|,
DECL|enumerator|GIMP_MINUS_CURSOR
name|GIMP_MINUS_CURSOR
block|,
DECL|enumerator|GIMP_INTERSECT_CURSOR
name|GIMP_INTERSECT_CURSOR
block|,
DECL|enumerator|GIMP_MOVE_CURSOR
name|GIMP_MOVE_CURSOR
block|,
DECL|enumerator|GIMP_RESIZE_CURSOR
name|GIMP_RESIZE_CURSOR
block|,
DECL|enumerator|GIMP_CONTROL_CURSOR
name|GIMP_CONTROL_CURSOR
block|,
DECL|enumerator|GIMP_ANCHOR_CURSOR
name|GIMP_ANCHOR_CURSOR
block|,
DECL|enumerator|GIMP_FOREGROUND_CURSOR
name|GIMP_FOREGROUND_CURSOR
block|,
DECL|enumerator|GIMP_BACKGROUND_CURSOR
name|GIMP_BACKGROUND_CURSOR
block|,
DECL|enumerator|GIMP_PATTERN_CURSOR
name|GIMP_PATTERN_CURSOR
block|,
DECL|enumerator|GIMP_HAND_CURSOR
name|GIMP_HAND_CURSOR
block|}
enum|;
end_enum

begin_decl_stmt
DECL|variable|modifier_cursors
specifier|static
name|BitmapCursor
name|modifier_cursors
index|[]
init|=
comment|/* these have to match up with the enum above */
block|{
block|{
name|plus_bits
block|,
name|plus_mask_bits
block|,
name|plus_width
block|,
name|plus_height
block|,
name|plus_x_hot
block|,
name|plus_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|minus_bits
block|,
name|minus_mask_bits
block|,
name|minus_width
block|,
name|minus_height
block|,
name|minus_x_hot
block|,
name|minus_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|intersect_bits
block|,
name|intersect_mask_bits
block|,
name|intersect_width
block|,
name|intersect_height
block|,
name|intersect_x_hot
block|,
name|intersect_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|move_bits
block|,
name|move_mask_bits
block|,
name|move_width
block|,
name|move_height
block|,
name|move_x_hot
block|,
name|move_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|resize_bits
block|,
name|resize_mask_bits
block|,
name|resize_width
block|,
name|resize_height
block|,
name|resize_x_hot
block|,
name|resize_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|control_bits
block|,
name|control_mask_bits
block|,
name|control_width
block|,
name|control_height
block|,
name|control_x_hot
block|,
name|control_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|anchor_bits
block|,
name|anchor_mask_bits
block|,
name|anchor_width
block|,
name|anchor_height
block|,
name|anchor_x_hot
block|,
name|anchor_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|foreground_bits
block|,
name|foreground_mask_bits
block|,
name|foreground_width
block|,
name|foreground_height
block|,
name|foreground_x_hot
block|,
name|foreground_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|background_bits
block|,
name|background_mask_bits
block|,
name|background_width
block|,
name|background_height
block|,
name|background_x_hot
block|,
name|background_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|pattern_bits
block|,
name|pattern_mask_bits
block|,
name|pattern_width
block|,
name|pattern_height
block|,
name|pattern_x_hot
block|,
name|pattern_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|hand_bits
block|,
name|hand_mask_bits
block|,
name|hand_width
block|,
name|hand_height
block|,
name|hand_x_hot
block|,
name|hand_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|display_list
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* It's in gdisplay.c, FYI */
end_comment

begin_decl_stmt
DECL|variable|pending_removebusy
specifier|static
name|gboolean
name|pending_removebusy
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|create_cursor_bitmaps (BitmapCursor * bmcursor)
name|create_cursor_bitmaps
parameter_list|(
name|BitmapCursor
modifier|*
name|bmcursor
parameter_list|)
block|{
if|if
condition|(
name|bmcursor
operator|->
name|bitmap
operator|==
name|NULL
condition|)
name|bmcursor
operator|->
name|bitmap
operator|=
name|gdk_bitmap_create_from_data
argument_list|(
name|NULL
argument_list|,
name|bmcursor
operator|->
name|bits
argument_list|,
name|bmcursor
operator|->
name|width
argument_list|,
name|bmcursor
operator|->
name|height
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|bmcursor
operator|->
name|bitmap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|bmcursor
operator|->
name|mask
operator|==
name|NULL
condition|)
name|bmcursor
operator|->
name|mask
operator|=
name|gdk_bitmap_create_from_data
argument_list|(
name|NULL
argument_list|,
name|bmcursor
operator|->
name|mask_bits
argument_list|,
name|bmcursor
operator|->
name|width
argument_list|,
name|bmcursor
operator|->
name|height
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|bmcursor
operator|->
name|mask
operator|!=
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|create_cursor (BitmapCursor * bmcursor)
name|create_cursor
parameter_list|(
name|BitmapCursor
modifier|*
name|bmcursor
parameter_list|)
block|{
if|if
condition|(
name|bmcursor
operator|->
name|bitmap
operator|==
name|NULL
operator|||
name|bmcursor
operator|->
name|mask
operator|==
name|NULL
condition|)
name|create_cursor_bitmaps
argument_list|(
name|bmcursor
argument_list|)
expr_stmt|;
if|if
condition|(
name|bmcursor
operator|->
name|cursor
operator|==
name|NULL
condition|)
block|{
name|GdkColor
name|fg
decl_stmt|,
name|bg
decl_stmt|;
comment|/* should have a way to configure the mouse colors */
name|gdk_color_parse
argument_list|(
literal|"#FFFFFF"
argument_list|,
operator|&
name|bg
argument_list|)
expr_stmt|;
name|gdk_color_parse
argument_list|(
literal|"#000000"
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
name|bmcursor
operator|->
name|cursor
operator|=
name|gdk_cursor_new_from_pixmap
argument_list|(
name|bmcursor
operator|->
name|bitmap
argument_list|,
name|bmcursor
operator|->
name|mask
argument_list|,
operator|&
name|fg
argument_list|,
operator|&
name|bg
argument_list|,
name|bmcursor
operator|->
name|x_hot
argument_list|,
name|bmcursor
operator|->
name|y_hot
argument_list|)
expr_stmt|;
block|}
name|g_return_if_fail
argument_list|(
name|bmcursor
operator|->
name|cursor
operator|!=
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_change_win_cursor (GdkWindow * win,GimpCursorType curtype,ToolType tool_type,CursorModifier modifier,gboolean toggle_cursor)
name|gimp_change_win_cursor
parameter_list|(
name|GdkWindow
modifier|*
name|win
parameter_list|,
name|GimpCursorType
name|curtype
parameter_list|,
name|ToolType
name|tool_type
parameter_list|,
name|CursorModifier
name|modifier
parameter_list|,
name|gboolean
name|toggle_cursor
parameter_list|)
block|{
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
name|GimpCursorType
name|modtype
init|=
name|GIMP_PLUS_CURSOR
decl_stmt|;
name|GdkBitmap
modifier|*
name|bitmap
decl_stmt|;
name|GdkBitmap
modifier|*
name|mask
decl_stmt|;
name|GdkColor
name|color
decl_stmt|;
name|GdkColor
name|fg
decl_stmt|,
name|bg
decl_stmt|;
specifier|static
name|GdkGC
modifier|*
name|gc
init|=
name|NULL
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|BitmapCursor
modifier|*
name|bmcursor
init|=
name|NULL
decl_stmt|;
name|BitmapCursor
modifier|*
name|bmmodifier
init|=
name|NULL
decl_stmt|;
name|BitmapCursor
modifier|*
name|bmtool
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|curtype
operator|<
name|GIMP_LAST_CURSOR_ENTRY
argument_list|)
expr_stmt|;
comment|/*  allow the small tool cursor only with the standard mouse,    *  the small crosshair and the bad cursor    */
if|if
condition|(
name|curtype
operator|!=
name|GIMP_MOUSE_CURSOR
operator|&&
name|curtype
operator|!=
name|GIMP_CROSSHAIR_SMALL_CURSOR
operator|&&
name|curtype
operator|!=
name|GIMP_BAD_CURSOR
condition|)
name|tool_type
operator|=
name|TOOL_TYPE_NONE
expr_stmt|;
name|curtype
operator|-=
name|GIMP_MOUSE_CURSOR
expr_stmt|;
name|bmcursor
operator|=
operator|&
name|gimp_cursors
index|[
operator|(
name|int
operator|)
name|curtype
index|]
expr_stmt|;
if|if
condition|(
name|modifier
operator|==
name|CURSOR_MODIFIER_NONE
operator|&&
name|tool_type
operator|==
name|TOOL_TYPE_NONE
condition|)
block|{
if|if
condition|(
name|bmcursor
operator|->
name|cursor
operator|==
name|NULL
condition|)
name|create_cursor
argument_list|(
name|bmcursor
argument_list|)
expr_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|win
argument_list|,
name|bmcursor
operator|->
name|cursor
argument_list|)
expr_stmt|;
return|return;
block|}
switch|switch
condition|(
name|modifier
condition|)
block|{
case|case
name|CURSOR_MODIFIER_PLUS
case|:
name|modtype
operator|=
name|GIMP_PLUS_CURSOR
expr_stmt|;
break|break;
case|case
name|CURSOR_MODIFIER_MINUS
case|:
name|modtype
operator|=
name|GIMP_MINUS_CURSOR
expr_stmt|;
break|break;
case|case
name|CURSOR_MODIFIER_INTERSECT
case|:
name|modtype
operator|=
name|GIMP_INTERSECT_CURSOR
expr_stmt|;
break|break;
case|case
name|CURSOR_MODIFIER_MOVE
case|:
name|modtype
operator|=
name|GIMP_MOVE_CURSOR
expr_stmt|;
break|break;
case|case
name|CURSOR_MODIFIER_RESIZE
case|:
name|modtype
operator|=
name|GIMP_RESIZE_CURSOR
expr_stmt|;
break|break;
case|case
name|CURSOR_MODIFIER_CONTROL
case|:
name|modtype
operator|=
name|GIMP_CONTROL_CURSOR
expr_stmt|;
break|break;
case|case
name|CURSOR_MODIFIER_ANCHOR
case|:
name|modtype
operator|=
name|GIMP_ANCHOR_CURSOR
expr_stmt|;
break|break;
case|case
name|CURSOR_MODIFIER_FOREGROUND
case|:
name|modtype
operator|=
name|GIMP_FOREGROUND_CURSOR
expr_stmt|;
break|break;
case|case
name|CURSOR_MODIFIER_BACKGROUND
case|:
name|modtype
operator|=
name|GIMP_BACKGROUND_CURSOR
expr_stmt|;
break|break;
case|case
name|CURSOR_MODIFIER_PATTERN
case|:
name|modtype
operator|=
name|GIMP_PATTERN_CURSOR
expr_stmt|;
break|break;
case|case
name|CURSOR_MODIFIER_HAND
case|:
name|modtype
operator|=
name|GIMP_HAND_CURSOR
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|modifier
operator|!=
name|CURSOR_MODIFIER_NONE
condition|)
block|{
name|modtype
operator|-=
name|GIMP_PLUS_CURSOR
expr_stmt|;
name|bmmodifier
operator|=
operator|&
name|modifier_cursors
index|[
operator|(
name|int
operator|)
name|modtype
index|]
expr_stmt|;
block|}
if|if
condition|(
name|tool_type
operator|!=
name|TOOL_TYPE_NONE
condition|)
block|{
if|if
condition|(
name|toggle_cursor
condition|)
block|{
if|if
condition|(
name|tool_info
index|[
operator|(
name|gint
operator|)
name|tool_type
index|]
operator|.
name|toggle_cursor
operator|.
name|bits
operator|!=
name|NULL
operator|&&
name|tool_info
index|[
operator|(
name|gint
operator|)
name|tool_type
index|]
operator|.
name|toggle_cursor
operator|.
name|mask_bits
operator|!=
name|NULL
condition|)
name|bmtool
operator|=
operator|&
name|tool_info
index|[
operator|(
name|gint
operator|)
name|tool_type
index|]
operator|.
name|toggle_cursor
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|tool_info
index|[
operator|(
name|gint
operator|)
name|tool_type
index|]
operator|.
name|tool_cursor
operator|.
name|bits
operator|!=
name|NULL
operator|&&
name|tool_info
index|[
operator|(
name|gint
operator|)
name|tool_type
index|]
operator|.
name|tool_cursor
operator|.
name|mask_bits
operator|!=
name|NULL
condition|)
name|bmtool
operator|=
operator|&
name|tool_info
index|[
operator|(
name|gint
operator|)
name|tool_type
index|]
operator|.
name|tool_cursor
expr_stmt|;
block|}
block|}
if|if
condition|(
name|bmcursor
operator|->
name|bitmap
operator|==
name|NULL
operator|||
name|bmcursor
operator|->
name|mask
operator|==
name|NULL
condition|)
name|create_cursor_bitmaps
argument_list|(
name|bmcursor
argument_list|)
expr_stmt|;
if|if
condition|(
name|bmmodifier
operator|&&
operator|(
name|bmmodifier
operator|->
name|bitmap
operator|==
name|NULL
operator|||
name|bmmodifier
operator|->
name|mask
operator|==
name|NULL
operator|)
condition|)
name|create_cursor_bitmaps
argument_list|(
name|bmmodifier
argument_list|)
expr_stmt|;
if|if
condition|(
name|bmtool
operator|&&
operator|(
name|bmtool
operator|->
name|bitmap
operator|==
name|NULL
operator|||
name|bmtool
operator|->
name|mask
operator|==
name|NULL
operator|)
condition|)
name|create_cursor_bitmaps
argument_list|(
name|bmtool
argument_list|)
expr_stmt|;
if|if
condition|(
name|gc
operator|==
name|NULL
condition|)
name|gc
operator|=
name|gdk_gc_new
argument_list|(
name|bmcursor
operator|->
name|bitmap
argument_list|)
expr_stmt|;
name|gdk_window_get_size
argument_list|(
name|bmcursor
operator|->
name|bitmap
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|bitmap
operator|=
name|gdk_pixmap_new
argument_list|(
name|NULL
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gdk_pixmap_new
argument_list|(
name|NULL
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|color
operator|.
name|pixel
operator|=
literal|1
expr_stmt|;
name|gdk_gc_set_foreground
argument_list|(
name|gc
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gdk_draw_pixmap
argument_list|(
name|bitmap
argument_list|,
name|gc
argument_list|,
name|bmcursor
operator|->
name|bitmap
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
if|if
condition|(
name|bmmodifier
condition|)
block|{
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|bmmodifier
operator|->
name|bitmap
argument_list|)
expr_stmt|;
name|gdk_draw_pixmap
argument_list|(
name|bitmap
argument_list|,
name|gc
argument_list|,
name|bmmodifier
operator|->
name|bitmap
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
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|bmtool
condition|)
block|{
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|bmtool
operator|->
name|bitmap
argument_list|)
expr_stmt|;
name|gdk_draw_pixmap
argument_list|(
name|bitmap
argument_list|,
name|gc
argument_list|,
name|bmtool
operator|->
name|bitmap
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
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gdk_draw_pixmap
argument_list|(
name|mask
argument_list|,
name|gc
argument_list|,
name|bmcursor
operator|->
name|mask
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
if|if
condition|(
name|bmmodifier
condition|)
block|{
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|bmmodifier
operator|->
name|mask
argument_list|)
expr_stmt|;
name|gdk_draw_pixmap
argument_list|(
name|mask
argument_list|,
name|gc
argument_list|,
name|bmmodifier
operator|->
name|mask
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
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|bmtool
condition|)
block|{
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|bmtool
operator|->
name|mask
argument_list|)
expr_stmt|;
name|gdk_draw_pixmap
argument_list|(
name|mask
argument_list|,
name|gc
argument_list|,
name|bmtool
operator|->
name|mask
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
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
comment|/* should have a way to configure the mouse colors */
name|gdk_color_parse
argument_list|(
literal|"#FFFFFF"
argument_list|,
operator|&
name|bg
argument_list|)
expr_stmt|;
name|gdk_color_parse
argument_list|(
literal|"#000000"
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
name|cursor
operator|=
name|gdk_cursor_new_from_pixmap
argument_list|(
name|bitmap
argument_list|,
name|mask
argument_list|,
operator|&
name|fg
argument_list|,
operator|&
name|bg
argument_list|,
name|bmcursor
operator|->
name|x_hot
argument_list|,
name|bmcursor
operator|->
name|y_hot
argument_list|)
expr_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|win
argument_list|,
name|cursor
argument_list|)
expr_stmt|;
name|gdk_cursor_destroy
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
name|gdk_bitmap_unref
argument_list|(
name|bitmap
argument_list|)
expr_stmt|;
name|gdk_bitmap_unref
argument_list|(
name|mask
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|change_win_cursor (GdkWindow * win,GdkCursorType cursortype,ToolType tool_type,CursorModifier modifier,gboolean toggle_cursor)
name|change_win_cursor
parameter_list|(
name|GdkWindow
modifier|*
name|win
parameter_list|,
name|GdkCursorType
name|cursortype
parameter_list|,
name|ToolType
name|tool_type
parameter_list|,
name|CursorModifier
name|modifier
parameter_list|,
name|gboolean
name|toggle_cursor
parameter_list|)
block|{
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
if|if
condition|(
name|cursortype
operator|>
name|GDK_LAST_CURSOR
condition|)
block|{
name|gimp_change_win_cursor
argument_list|(
name|win
argument_list|,
operator|(
name|GimpCursorType
operator|)
name|cursortype
argument_list|,
name|tool_type
argument_list|,
name|modifier
argument_list|,
name|toggle_cursor
argument_list|)
expr_stmt|;
return|return;
block|}
name|cursor
operator|=
name|gdk_cursor_new
argument_list|(
name|cursortype
argument_list|)
expr_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|win
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
DECL|function|unset_win_cursor (GdkWindow * win)
name|unset_win_cursor
parameter_list|(
name|GdkWindow
modifier|*
name|win
parameter_list|)
block|{
name|gdk_window_set_cursor
argument_list|(
name|win
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_add_busy_cursors_until_idle (void)
name|gimp_add_busy_cursors_until_idle
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|pending_removebusy
condition|)
block|{
name|gimp_add_busy_cursors
argument_list|()
expr_stmt|;
name|gtk_idle_add_priority
argument_list|(
name|GTK_PRIORITY_HIGH
argument_list|,
name|gimp_remove_busy_cursors
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pending_removebusy
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_add_busy_cursors (void)
name|gimp_add_busy_cursors
parameter_list|(
name|void
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
comment|/* FIXME: gimp_busy HACK */
name|gimp_busy
operator|=
name|TRUE
expr_stmt|;
comment|/* Canvases */
for|for
control|(
name|list
operator|=
name|display_list
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gdisplay_install_override_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_WATCH
argument_list|)
expr_stmt|;
block|}
comment|/* Dialogs */
name|dialog_idle_all
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_remove_busy_cursors (gpointer data)
name|gimp_remove_busy_cursors
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
comment|/* Canvases */
for|for
control|(
name|list
operator|=
name|display_list
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gdisplay_remove_override_cursor
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
comment|/* Dialogs */
name|dialog_unidle_all
argument_list|()
expr_stmt|;
name|pending_removebusy
operator|=
name|FALSE
expr_stmt|;
comment|/* FIXME: gimp_busy HACK */
name|gimp_busy
operator|=
name|FALSE
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_comment
comment|/***************************************************************/
end_comment

begin_comment
comment|/* gtkutil_compress_motion:     This function walks the whole GDK event queue seeking motion events    corresponding to the widget 'widget'.  If it finds any it will    remove them from the queue, write the most recent motion offset    to 'lastmotion_x' and 'lastmotion_y', then return TRUE.  Otherwise    it will return FALSE and 'lastmotion_x' / 'lastmotion_y' will be    untouched.  */
end_comment

begin_comment
comment|/* The gtkutil_compress_motion function source may be re-used under    the XFree86-style license.<adam@gimp.org> */
end_comment

begin_function
name|gboolean
DECL|function|gtkutil_compress_motion (GtkWidget * widget,gdouble * lastmotion_x,gdouble * lastmotion_y)
name|gtkutil_compress_motion
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
modifier|*
name|lastmotion_x
parameter_list|,
name|gdouble
modifier|*
name|lastmotion_y
parameter_list|)
block|{
name|GdkEvent
modifier|*
name|event
decl_stmt|;
name|GList
modifier|*
name|requeued_events
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
comment|/* Move the entire GDK event queue to a private list, filtering      out any motion events for the desired widget. */
while|while
condition|(
name|gdk_events_pending
argument_list|()
condition|)
block|{
name|event
operator|=
name|gdk_event_get
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|event
condition|)
block|{
comment|/* Do nothing */
block|}
elseif|else
if|if
condition|(
operator|(
name|gtk_get_event_widget
argument_list|(
name|event
argument_list|)
operator|==
name|widget
operator|)
operator|&&
operator|(
name|event
operator|->
name|any
operator|.
name|type
operator|==
name|GDK_MOTION_NOTIFY
operator|)
condition|)
block|{
operator|*
name|lastmotion_x
operator|=
name|event
operator|->
name|motion
operator|.
name|x
expr_stmt|;
operator|*
name|lastmotion_y
operator|=
name|event
operator|->
name|motion
operator|.
name|y
expr_stmt|;
name|gdk_event_free
argument_list|(
name|event
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|requeued_events
operator|=
name|g_list_prepend
argument_list|(
name|requeued_events
argument_list|,
name|event
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* Replay the remains of our private event list back into the      event queue in order. */
name|requeued_events
operator|=
name|g_list_reverse
argument_list|(
name|requeued_events
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|requeued_events
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|gdk_event_put
argument_list|(
operator|(
name|GdkEvent
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gdk_event_free
argument_list|(
operator|(
name|GdkEvent
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|requeued_events
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

