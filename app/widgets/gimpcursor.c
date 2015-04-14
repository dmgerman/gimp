begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcursor.h"
end_include

begin_include
include|#
directive|include
file|"cursors/gimp-tool-cursors.c"
end_include

begin_define
DECL|macro|cursor_default_x_hot
define|#
directive|define
name|cursor_default_x_hot
value|10
end_define

begin_define
DECL|macro|cursor_default_y_hot
define|#
directive|define
name|cursor_default_y_hot
value|10
end_define

begin_define
DECL|macro|cursor_mouse_x_hot
define|#
directive|define
name|cursor_mouse_x_hot
value|3
end_define

begin_define
DECL|macro|cursor_mouse_y_hot
define|#
directive|define
name|cursor_mouse_y_hot
value|2
end_define

begin_define
DECL|macro|cursor_crosshair_x_hot
define|#
directive|define
name|cursor_crosshair_x_hot
value|15
end_define

begin_define
DECL|macro|cursor_crosshair_y_hot
define|#
directive|define
name|cursor_crosshair_y_hot
value|15
end_define

begin_define
DECL|macro|cursor_zoom_x_hot
define|#
directive|define
name|cursor_zoom_x_hot
value|8
end_define

begin_define
DECL|macro|cursor_zoom_y_hot
define|#
directive|define
name|cursor_zoom_y_hot
value|8
end_define

begin_define
DECL|macro|cursor_color_picker_x_hot
define|#
directive|define
name|cursor_color_picker_x_hot
value|1
end_define

begin_define
DECL|macro|cursor_color_picker_y_hot
define|#
directive|define
name|cursor_color_picker_y_hot
value|30
end_define

begin_typedef
DECL|typedef|GimpCursor
typedef|typedef
name|struct
name|_GimpCursor
name|GimpCursor
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCursor
struct|struct
name|_GimpCursor
block|{
DECL|member|resource_name
specifier|const
name|gchar
modifier|*
name|resource_name
decl_stmt|;
DECL|member|x_hot
DECL|member|y_hot
specifier|const
name|gint
name|x_hot
decl_stmt|,
name|y_hot
decl_stmt|;
DECL|member|pixbuf
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
DECL|variable|gimp_cursors
specifier|static
name|GimpCursor
name|gimp_cursors
index|[]
init|=
block|{
comment|/* these have to match up with enum GimpCursorType in widgets-enums.h */
block|{
literal|"cursor-none.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-mouse.png"
block|,
name|cursor_mouse_x_hot
block|,
name|cursor_mouse_y_hot
block|}
block|,
block|{
literal|"cursor-crosshair.png"
block|,
name|cursor_crosshair_x_hot
block|,
name|cursor_crosshair_y_hot
block|}
block|,
block|{
literal|"cursor-crosshair-small.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-bad.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-move.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-zoom.png"
block|,
name|cursor_zoom_x_hot
block|,
name|cursor_zoom_y_hot
block|}
block|,
block|{
literal|"cursor-color-picker.png"
block|,
name|cursor_color_picker_x_hot
block|,
name|cursor_color_picker_y_hot
block|}
block|,
block|{
literal|"cursor-corner-top.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-corner-top-right.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-corner-right.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-corner-bottom-right.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-corner-bottom.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-corner-bottom-left.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-corner-left.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-corner-top-left.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-sid-_top.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-side-top-right.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-side-right.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-side-bottom-right.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-side-bottom.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-side-bottom-left.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-side-left.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|,
block|{
literal|"cursor-side-top-left.png"
block|,
name|cursor_default_x_hot
block|,
name|cursor_default_y_hot
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_tool_cursors
specifier|static
name|GimpCursor
name|gimp_tool_cursors
index|[]
init|=
block|{
comment|/* these have to match up with enum GimpToolCursorType in widgets-enums.h */
block|{
name|NULL
block|}
block|,
block|{
literal|"tool-rect-select.png"
block|}
block|,
block|{
literal|"tool-ellipse-select.png"
block|}
block|,
block|{
literal|"tool-free-select.png"
block|}
block|,
block|{
literal|"tool-polygon-select.png"
block|}
block|,
block|{
literal|"tool-fuzzy-select.png"
block|}
block|,
block|{
literal|"tool-paths.png"
block|}
block|,
block|{
literal|"tool-paths-anchor.png"
block|}
block|,
block|{
literal|"tool-paths-control.png"
block|}
block|,
block|{
literal|"tool-paths-segment.png"
block|}
block|,
block|{
literal|"tool-iscissors.png"
block|}
block|,
block|{
literal|"tool-move.png"
block|}
block|,
block|{
literal|"tool-zoom.png"
block|}
block|,
block|{
literal|"tool-crop.png"
block|}
block|,
block|{
literal|"tool-resize.png"
block|}
block|,
block|{
literal|"tool-rotate.png"
block|}
block|,
block|{
literal|"tool-shear.png"
block|}
block|,
block|{
literal|"tool-perspective.png"
block|}
block|,
block|{
literal|"tool-flip-horizontal.png"
block|}
block|,
block|{
literal|"tool-flip-vertical.png"
block|}
block|,
block|{
literal|"tool-text.png"
block|}
block|,
block|{
literal|"tool-color-picker.png"
block|}
block|,
block|{
literal|"tool-bucket-fill.png"
block|}
block|,
block|{
literal|"tool-blend.png"
block|}
block|,
block|{
literal|"tool-pencil.png"
block|}
block|,
block|{
literal|"tool-paintbrush.png"
block|}
block|,
block|{
literal|"tool-airbrush.png"
block|}
block|,
block|{
literal|"tool-ink.png"
block|}
block|,
block|{
literal|"tool-clone.png"
block|}
block|,
block|{
literal|"tool-heal.png"
block|}
block|,
block|{
literal|"tool-eraser.png"
block|}
block|,
block|{
literal|"tool-smudge.png"
block|}
block|,
block|{
literal|"tool-blur.png"
block|}
block|,
block|{
literal|"tool-dodge.png"
block|}
block|,
block|{
literal|"tool-burn.png"
block|}
block|,
block|{
literal|"tool-measure.png"
block|}
block|,
block|{
literal|"tool-hand.png"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_cursor_modifiers
specifier|static
name|GimpCursor
name|gimp_cursor_modifiers
index|[]
init|=
block|{
comment|/* these have to match up with enum GimpCursorModifier in widgets-enums.h */
block|{
name|NULL
block|}
block|,
block|{
literal|"modifier-bad.png"
block|}
block|,
block|{
literal|"modifier-plus.png"
block|}
block|,
block|{
literal|"modifier-minus.png"
block|}
block|,
block|{
literal|"modifier-intersect.png"
block|}
block|,
block|{
literal|"modifier-move.png"
block|}
block|,
block|{
literal|"modifier-resize.png"
block|}
block|,
block|{
literal|"modifier-control.png"
block|}
block|,
block|{
literal|"modifier-anchor.png"
block|}
block|,
block|{
literal|"modifier-foreground.png"
block|}
block|,
block|{
literal|"modifier-background.png"
block|}
block|,
block|{
literal|"modifier-pattern.png"
block|}
block|,
block|{
literal|"modifier-join.png"
block|}
block|,
block|{
literal|"modifier-select.png"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
specifier|const
name|GdkPixbuf
modifier|*
DECL|function|get_cursor_pixbuf (GimpCursor * cursor)
name|get_cursor_pixbuf
parameter_list|(
name|GimpCursor
modifier|*
name|cursor
parameter_list|)
block|{
if|if
condition|(
operator|!
name|cursor
operator|->
name|pixbuf
condition|)
block|{
name|gchar
modifier|*
name|resource_path
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|resource_path
operator|=
name|g_strconcat
argument_list|(
literal|"/org/gimp/tool-cursors/"
argument_list|,
name|cursor
operator|->
name|resource_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cursor
operator|->
name|pixbuf
operator|=
name|gdk_pixbuf_new_from_resource
argument_list|(
name|resource_path
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|cursor
operator|->
name|pixbuf
condition|)
block|{
name|g_critical
argument_list|(
literal|"Failed to create cursor image: %s"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|resource_path
argument_list|)
expr_stmt|;
block|}
return|return
name|cursor
operator|->
name|pixbuf
return|;
block|}
end_function

begin_function
name|GdkCursor
modifier|*
DECL|function|gimp_cursor_new (GdkDisplay * display,GimpHandedness cursor_handedness,GimpCursorType cursor_type,GimpToolCursorType tool_cursor,GimpCursorModifier modifier)
name|gimp_cursor_new
parameter_list|(
name|GdkDisplay
modifier|*
name|display
parameter_list|,
name|GimpHandedness
name|cursor_handedness
parameter_list|,
name|GimpCursorType
name|cursor_type
parameter_list|,
name|GimpToolCursorType
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
name|modifier
parameter_list|)
block|{
name|GimpCursor
modifier|*
name|bmcursor
init|=
name|NULL
decl_stmt|;
name|GimpCursor
modifier|*
name|bmmodifier
init|=
name|NULL
decl_stmt|;
name|GimpCursor
modifier|*
name|bmtool
init|=
name|NULL
decl_stmt|;
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GDK_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|cursor_type
operator|<
name|GIMP_CURSOR_LAST
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|cursor_type
operator|<=
operator|(
name|GimpCursorType
operator|)
name|GDK_LAST_CURSOR
condition|)
return|return
name|gdk_cursor_new_for_display
argument_list|(
name|display
argument_list|,
operator|(
name|GdkCursorType
operator|)
name|cursor_type
argument_list|)
return|;
name|g_return_val_if_fail
argument_list|(
name|cursor_type
operator|>=
name|GIMP_CURSOR_NONE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  disallow the small tool cursor with some cursors    */
if|if
condition|(
name|cursor_type
operator|<=
name|GIMP_CURSOR_NONE
operator|||
name|cursor_type
operator|==
name|GIMP_CURSOR_CROSSHAIR
operator|||
name|cursor_type
operator|==
name|GIMP_CURSOR_ZOOM
operator|||
name|cursor_type
operator|==
name|GIMP_CURSOR_COLOR_PICKER
operator|||
name|cursor_type
operator|>=
name|GIMP_CURSOR_LAST
condition|)
block|{
name|tool_cursor
operator|=
name|GIMP_TOOL_CURSOR_NONE
expr_stmt|;
block|}
comment|/*  don't allow anything with the empty cursor    */
if|if
condition|(
name|cursor_type
operator|==
name|GIMP_CURSOR_NONE
condition|)
block|{
name|tool_cursor
operator|=
name|GIMP_TOOL_CURSOR_NONE
expr_stmt|;
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_NONE
expr_stmt|;
block|}
comment|/*  some more sanity checks    */
if|if
condition|(
name|cursor_type
operator|==
name|GIMP_CURSOR_MOVE
operator|&&
name|modifier
operator|==
name|GIMP_CURSOR_MODIFIER_MOVE
condition|)
block|{
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_NONE
expr_stmt|;
block|}
comment|/*  when cursor is "corner" or "side" sides must be exchanged for    *  left-hand-mice-flipping of pixbuf below    */
if|if
condition|(
name|cursor_handedness
operator|==
name|GIMP_HANDEDNESS_LEFT
condition|)
block|{
switch|switch
condition|(
name|cursor_type
condition|)
block|{
case|case
name|GIMP_CURSOR_CORNER_TOP_LEFT
case|:
name|cursor_type
operator|=
name|GIMP_CURSOR_CORNER_TOP_RIGHT
expr_stmt|;
break|break;
case|case
name|GIMP_CURSOR_CORNER_TOP_RIGHT
case|:
name|cursor_type
operator|=
name|GIMP_CURSOR_CORNER_TOP_LEFT
expr_stmt|;
break|break;
case|case
name|GIMP_CURSOR_CORNER_LEFT
case|:
name|cursor_type
operator|=
name|GIMP_CURSOR_CORNER_RIGHT
expr_stmt|;
break|break;
case|case
name|GIMP_CURSOR_CORNER_RIGHT
case|:
name|cursor_type
operator|=
name|GIMP_CURSOR_CORNER_LEFT
expr_stmt|;
break|break;
case|case
name|GIMP_CURSOR_CORNER_BOTTOM_LEFT
case|:
name|cursor_type
operator|=
name|GIMP_CURSOR_CORNER_BOTTOM_RIGHT
expr_stmt|;
break|break;
case|case
name|GIMP_CURSOR_CORNER_BOTTOM_RIGHT
case|:
name|cursor_type
operator|=
name|GIMP_CURSOR_CORNER_BOTTOM_LEFT
expr_stmt|;
break|break;
case|case
name|GIMP_CURSOR_SIDE_TOP_LEFT
case|:
name|cursor_type
operator|=
name|GIMP_CURSOR_SIDE_TOP_RIGHT
expr_stmt|;
break|break;
case|case
name|GIMP_CURSOR_SIDE_TOP_RIGHT
case|:
name|cursor_type
operator|=
name|GIMP_CURSOR_SIDE_TOP_LEFT
expr_stmt|;
break|break;
case|case
name|GIMP_CURSOR_SIDE_LEFT
case|:
name|cursor_type
operator|=
name|GIMP_CURSOR_SIDE_RIGHT
expr_stmt|;
break|break;
case|case
name|GIMP_CURSOR_SIDE_RIGHT
case|:
name|cursor_type
operator|=
name|GIMP_CURSOR_SIDE_LEFT
expr_stmt|;
break|break;
case|case
name|GIMP_CURSOR_SIDE_BOTTOM_LEFT
case|:
name|cursor_type
operator|=
name|GIMP_CURSOR_SIDE_BOTTOM_RIGHT
expr_stmt|;
break|break;
case|case
name|GIMP_CURSOR_SIDE_BOTTOM_RIGHT
case|:
name|cursor_type
operator|=
name|GIMP_CURSOR_SIDE_BOTTOM_LEFT
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
comment|/*  prepare the main cursor  */
name|cursor_type
operator|-=
name|GIMP_CURSOR_NONE
expr_stmt|;
name|bmcursor
operator|=
operator|&
name|gimp_cursors
index|[
name|cursor_type
index|]
expr_stmt|;
comment|/*  prepare the tool cursor  */
if|if
condition|(
name|tool_cursor
operator|>
name|GIMP_TOOL_CURSOR_NONE
operator|&&
name|tool_cursor
operator|<
name|GIMP_TOOL_CURSOR_LAST
condition|)
block|{
name|bmtool
operator|=
operator|&
name|gimp_tool_cursors
index|[
name|tool_cursor
index|]
expr_stmt|;
block|}
comment|/*  prepare the cursor modifier  */
if|if
condition|(
name|modifier
operator|>
name|GIMP_CURSOR_MODIFIER_NONE
operator|&&
name|modifier
operator|<
name|GIMP_CURSOR_MODIFIER_LAST
condition|)
block|{
name|bmmodifier
operator|=
operator|&
name|gimp_cursor_modifiers
index|[
name|modifier
index|]
expr_stmt|;
block|}
name|pixbuf
operator|=
name|gdk_pixbuf_copy
argument_list|(
name|get_cursor_pixbuf
argument_list|(
name|bmcursor
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|bmmodifier
operator|||
name|bmtool
condition|)
block|{
name|gint
name|width
init|=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
decl_stmt|;
if|if
condition|(
name|bmmodifier
condition|)
name|gdk_pixbuf_composite
argument_list|(
name|get_cursor_pixbuf
argument_list|(
name|bmmodifier
argument_list|)
argument_list|,
name|pixbuf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|GDK_INTERP_NEAREST
argument_list|,
literal|200
argument_list|)
expr_stmt|;
if|if
condition|(
name|bmtool
condition|)
name|gdk_pixbuf_composite
argument_list|(
name|get_cursor_pixbuf
argument_list|(
name|bmtool
argument_list|)
argument_list|,
name|pixbuf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|GDK_INTERP_NEAREST
argument_list|,
literal|200
argument_list|)
expr_stmt|;
block|}
comment|/*  flip the cursor if mouse setting is left-handed  */
if|if
condition|(
name|cursor_handedness
operator|==
name|GIMP_HANDEDNESS_LEFT
condition|)
block|{
name|GdkPixbuf
modifier|*
name|flipped
init|=
name|gdk_pixbuf_flip
argument_list|(
name|pixbuf
argument_list|,
name|TRUE
argument_list|)
decl_stmt|;
name|gint
name|width
init|=
name|gdk_pixbuf_get_width
argument_list|(
name|flipped
argument_list|)
decl_stmt|;
name|cursor
operator|=
name|gdk_cursor_new_from_pixbuf
argument_list|(
name|display
argument_list|,
name|flipped
argument_list|,
operator|(
name|width
operator|-
literal|1
operator|)
operator|-
name|bmcursor
operator|->
name|x_hot
argument_list|,
name|bmcursor
operator|->
name|y_hot
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|flipped
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|cursor
operator|=
name|gdk_cursor_new_from_pixbuf
argument_list|(
name|display
argument_list|,
name|pixbuf
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
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
return|return
name|cursor
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_cursor_set (GtkWidget * widget,GimpHandedness cursor_handedness,GimpCursorType cursor_type,GimpToolCursorType tool_cursor,GimpCursorModifier modifier)
name|gimp_cursor_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpHandedness
name|cursor_handedness
parameter_list|,
name|GimpCursorType
name|cursor_type
parameter_list|,
name|GimpToolCursorType
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
name|modifier
parameter_list|)
block|{
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gtk_widget_get_realized
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|cursor
operator|=
name|gimp_cursor_new
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
argument_list|,
name|cursor_handedness
argument_list|,
name|cursor_type
argument_list|,
name|tool_cursor
argument_list|,
name|modifier
argument_list|)
expr_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
name|cursor
argument_list|)
expr_stmt|;
name|gdk_cursor_unref
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
name|gdk_display_flush
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpCursorType
DECL|function|gimp_cursor_rotate (GimpCursorType cursor,gdouble angle)
name|gimp_cursor_rotate
parameter_list|(
name|GimpCursorType
name|cursor
parameter_list|,
name|gdouble
name|angle
parameter_list|)
block|{
if|if
condition|(
name|cursor
operator|>=
name|GIMP_CURSOR_CORNER_TOP
operator|&&
name|cursor
operator|<=
name|GIMP_CURSOR_SIDE_TOP_LEFT
condition|)
block|{
name|gint
name|offset
init|=
call|(
name|gint
call|)
argument_list|(
name|angle
operator|/
literal|45
operator|+
literal|0.5
argument_list|)
decl_stmt|;
if|if
condition|(
name|cursor
operator|<
name|GIMP_CURSOR_SIDE_TOP
condition|)
block|{
name|cursor
operator|+=
name|offset
expr_stmt|;
if|if
condition|(
name|cursor
operator|>
name|GIMP_CURSOR_CORNER_TOP_LEFT
condition|)
name|cursor
operator|-=
literal|8
expr_stmt|;
block|}
else|else
block|{
name|cursor
operator|+=
name|offset
expr_stmt|;
if|if
condition|(
name|cursor
operator|>
name|GIMP_CURSOR_SIDE_TOP_LEFT
condition|)
name|cursor
operator|-=
literal|8
expr_stmt|;
block|}
block|}
return|return
name|cursor
return|;
block|}
end_function

end_unit

