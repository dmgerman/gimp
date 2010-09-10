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
file|"cursors/gimp-tool-cursors.h"
end_include

begin_define
DECL|macro|cursor_none_x_hot
define|#
directive|define
name|cursor_none_x_hot
value|10
end_define

begin_define
DECL|macro|cursor_none_y_hot
define|#
directive|define
name|cursor_none_y_hot
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
DECL|macro|cursor_crosshair_small_x_hot
define|#
directive|define
name|cursor_crosshair_small_x_hot
value|10
end_define

begin_define
DECL|macro|cursor_crosshair_small_y_hot
define|#
directive|define
name|cursor_crosshair_small_y_hot
value|10
end_define

begin_define
DECL|macro|cursor_bad_x_hot
define|#
directive|define
name|cursor_bad_x_hot
value|10
end_define

begin_define
DECL|macro|cursor_bad_y_hot
define|#
directive|define
name|cursor_bad_y_hot
value|10
end_define

begin_define
DECL|macro|cursor_move_x_hot
define|#
directive|define
name|cursor_move_x_hot
value|10
end_define

begin_define
DECL|macro|cursor_move_y_hot
define|#
directive|define
name|cursor_move_y_hot
value|10
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

begin_define
DECL|macro|cursor_corner_top_left_x_hot
define|#
directive|define
name|cursor_corner_top_left_x_hot
value|10
end_define

begin_define
DECL|macro|cursor_corner_top_left_y_hot
define|#
directive|define
name|cursor_corner_top_left_y_hot
value|10
end_define

begin_define
DECL|macro|cursor_corner_top_right_x_hot
define|#
directive|define
name|cursor_corner_top_right_x_hot
value|10
end_define

begin_define
DECL|macro|cursor_corner_top_right_y_hot
define|#
directive|define
name|cursor_corner_top_right_y_hot
value|10
end_define

begin_define
DECL|macro|cursor_corner_bottom_left_x_hot
define|#
directive|define
name|cursor_corner_bottom_left_x_hot
value|10
end_define

begin_define
DECL|macro|cursor_corner_bottom_left_y_hot
define|#
directive|define
name|cursor_corner_bottom_left_y_hot
value|10
end_define

begin_define
DECL|macro|cursor_corner_bottom_right_x_hot
define|#
directive|define
name|cursor_corner_bottom_right_x_hot
value|10
end_define

begin_define
DECL|macro|cursor_corner_bottom_right_y_hot
define|#
directive|define
name|cursor_corner_bottom_right_y_hot
value|10
end_define

begin_define
DECL|macro|cursor_side_top_x_hot
define|#
directive|define
name|cursor_side_top_x_hot
value|10
end_define

begin_define
DECL|macro|cursor_side_top_y_hot
define|#
directive|define
name|cursor_side_top_y_hot
value|10
end_define

begin_define
DECL|macro|cursor_side_left_x_hot
define|#
directive|define
name|cursor_side_left_x_hot
value|10
end_define

begin_define
DECL|macro|cursor_side_left_y_hot
define|#
directive|define
name|cursor_side_left_y_hot
value|10
end_define

begin_define
DECL|macro|cursor_side_right_x_hot
define|#
directive|define
name|cursor_side_right_x_hot
value|10
end_define

begin_define
DECL|macro|cursor_side_right_y_hot
define|#
directive|define
name|cursor_side_right_y_hot
value|10
end_define

begin_define
DECL|macro|cursor_side_bottom_x_hot
define|#
directive|define
name|cursor_side_bottom_x_hot
value|10
end_define

begin_define
DECL|macro|cursor_side_bottom_y_hot
define|#
directive|define
name|cursor_side_bottom_y_hot
value|10
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
DECL|member|pixbuf_data
specifier|const
name|guint8
modifier|*
name|pixbuf_data
decl_stmt|;
DECL|member|pixbuf_data_bw
specifier|const
name|guint8
modifier|*
name|pixbuf_data_bw
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
DECL|member|pixbuf_bw
name|GdkPixbuf
modifier|*
name|pixbuf_bw
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
name|cursor_none
block|,
name|cursor_none_bw
block|,
name|cursor_none_x_hot
block|,
name|cursor_none_y_hot
block|}
block|,
block|{
name|cursor_mouse
block|,
name|cursor_mouse_bw
block|,
name|cursor_mouse_x_hot
block|,
name|cursor_mouse_y_hot
block|}
block|,
block|{
name|cursor_crosshair
block|,
name|cursor_crosshair_bw
block|,
name|cursor_crosshair_x_hot
block|,
name|cursor_crosshair_y_hot
block|}
block|,
block|{
name|cursor_crosshair_small
block|,
name|cursor_crosshair_small_bw
block|,
name|cursor_crosshair_small_x_hot
block|,
name|cursor_crosshair_small_y_hot
block|}
block|,
block|{
name|cursor_bad
block|,
name|cursor_bad_bw
block|,
name|cursor_bad_x_hot
block|,
name|cursor_bad_y_hot
block|}
block|,
block|{
name|cursor_move
block|,
name|cursor_move_bw
block|,
name|cursor_move_x_hot
block|,
name|cursor_move_y_hot
block|}
block|,
block|{
name|cursor_zoom
block|,
name|cursor_zoom_bw
block|,
name|cursor_zoom_x_hot
block|,
name|cursor_zoom_y_hot
block|}
block|,
block|{
name|cursor_color_picker
block|,
name|cursor_color_picker_bw
block|,
name|cursor_color_picker_x_hot
block|,
name|cursor_color_picker_y_hot
block|}
block|,
block|{
name|cursor_corner_top_left
block|,
name|cursor_corner_top_left_bw
block|,
name|cursor_corner_top_left_x_hot
block|,
name|cursor_corner_top_left_y_hot
block|}
block|,
block|{
name|cursor_corner_top_right
block|,
name|cursor_corner_top_right_bw
block|,
name|cursor_corner_top_right_x_hot
block|,
name|cursor_corner_top_right_y_hot
block|}
block|,
block|{
name|cursor_corner_bottom_left
block|,
name|cursor_corner_bottom_left_bw
block|,
name|cursor_corner_bottom_left_x_hot
block|,
name|cursor_corner_bottom_left_y_hot
block|}
block|,
block|{
name|cursor_corner_bottom_right
block|,
name|cursor_corner_bottom_right_bw
block|,
name|cursor_corner_bottom_right_x_hot
block|,
name|cursor_corner_bottom_right_y_hot
block|}
block|,
block|{
name|cursor_side_top
block|,
name|cursor_side_top_bw
block|,
name|cursor_side_top_x_hot
block|,
name|cursor_side_top_y_hot
block|}
block|,
block|{
name|cursor_side_left
block|,
name|cursor_side_left_bw
block|,
name|cursor_side_left_x_hot
block|,
name|cursor_side_left_y_hot
block|}
block|,
block|{
name|cursor_side_right
block|,
name|cursor_side_right_bw
block|,
name|cursor_side_right_x_hot
block|,
name|cursor_side_right_y_hot
block|}
block|,
block|{
name|cursor_side_bottom
block|,
name|cursor_side_bottom_bw
block|,
name|cursor_side_bottom_x_hot
block|,
name|cursor_side_bottom_y_hot
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
name|tool_rect_select
block|,
name|tool_rect_select_bw
block|}
block|,
block|{
name|tool_ellipse_select
block|,
name|tool_ellipse_select_bw
block|}
block|,
block|{
name|tool_free_select
block|,
name|tool_free_select_bw
block|}
block|,
block|{
name|tool_polygon_select
block|,
name|tool_polygon_select_bw
block|}
block|,
block|{
name|tool_fuzzy_select
block|,
name|tool_fuzzy_select_bw
block|}
block|,
block|{
name|tool_paths
block|,
name|tool_paths_bw
block|}
block|,
block|{
name|tool_paths_anchor
block|,
name|tool_paths_anchor_bw
block|}
block|,
block|{
name|tool_paths_control
block|,
name|tool_paths_control_bw
block|}
block|,
block|{
name|tool_paths_segment
block|,
name|tool_paths_segment_bw
block|}
block|,
block|{
name|tool_iscissors
block|,
name|tool_iscissors_bw
block|}
block|,
block|{
name|tool_move
block|,
name|tool_move_bw
block|}
block|,
block|{
name|tool_zoom
block|,
name|tool_zoom_bw
block|}
block|,
block|{
name|tool_crop
block|,
name|tool_crop_bw
block|}
block|,
block|{
name|tool_resize
block|,
name|tool_resize_bw
block|}
block|,
block|{
name|tool_rotate
block|,
name|tool_rotate_bw
block|}
block|,
block|{
name|tool_shear
block|,
name|tool_shear_bw
block|}
block|,
block|{
name|tool_perspective
block|,
name|tool_perspective_bw
block|}
block|,
block|{
name|tool_flip_horizontal
block|,
name|tool_flip_horizontal_bw
block|}
block|,
block|{
name|tool_flip_vertical
block|,
name|tool_flip_vertical_bw
block|}
block|,
block|{
name|tool_text
block|,
name|tool_text_bw
block|}
block|,
block|{
name|tool_color_picker
block|,
name|tool_color_picker_bw
block|}
block|,
block|{
name|tool_bucket_fill
block|,
name|tool_bucket_fill_bw
block|}
block|,
block|{
name|tool_blend
block|,
name|tool_blend_bw
block|}
block|,
block|{
name|tool_pencil
block|,
name|tool_pencil_bw
block|}
block|,
block|{
name|tool_paintbrush
block|,
name|tool_paintbrush_bw
block|}
block|,
block|{
name|tool_airbrush
block|,
name|tool_airbrush_bw
block|}
block|,
block|{
name|tool_ink
block|,
name|tool_ink_bw
block|}
block|,
block|{
name|tool_clone
block|,
name|tool_clone_bw
block|}
block|,
block|{
name|tool_heal
block|,
name|tool_heal_bw
block|}
block|,
block|{
name|tool_eraser
block|,
name|tool_eraser_bw
block|}
block|,
block|{
name|tool_smudge
block|,
name|tool_smudge_bw
block|}
block|,
block|{
name|tool_blur
block|,
name|tool_blur_bw
block|}
block|,
block|{
name|tool_dodge
block|,
name|tool_dodge_bw
block|}
block|,
block|{
name|tool_burn
block|,
name|tool_burn_bw
block|}
block|,
block|{
name|tool_measure
block|,
name|tool_measure_bw
block|}
block|,
block|{
name|tool_hand
block|,
name|tool_hand_bw
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
name|modifier_bad
block|,
name|modifier_bad
block|}
block|,
block|{
name|modifier_plus
block|,
name|modifier_plus
block|}
block|,
block|{
name|modifier_minus
block|,
name|modifier_minus
block|}
block|,
block|{
name|modifier_intersect
block|,
name|modifier_intersect
block|}
block|,
block|{
name|modifier_move
block|,
name|modifier_move
block|}
block|,
block|{
name|modifier_resize
block|,
name|modifier_resize
block|}
block|,
block|{
name|modifier_control
block|,
name|modifier_control
block|}
block|,
block|{
name|modifier_anchor
block|,
name|modifier_anchor
block|}
block|,
block|{
name|modifier_foreground
block|,
name|modifier_foreground
block|}
block|,
block|{
name|modifier_background
block|,
name|modifier_background
block|}
block|,
block|{
name|modifier_pattern
block|,
name|modifier_pattern
block|}
block|,
block|{
name|modifier_join
block|,
name|modifier_join
block|}
block|,
block|{
name|modifier_select
block|,
name|modifier_select
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
specifier|const
name|GdkPixbuf
modifier|*
DECL|function|get_cursor_pixbuf (GimpCursor * cursor,gboolean bw)
name|get_cursor_pixbuf
parameter_list|(
name|GimpCursor
modifier|*
name|cursor
parameter_list|,
name|gboolean
name|bw
parameter_list|)
block|{
name|GdkPixbuf
modifier|*
modifier|*
name|pixbuf
decl_stmt|;
if|if
condition|(
name|bw
condition|)
name|pixbuf
operator|=
operator|&
name|cursor
operator|->
name|pixbuf_bw
expr_stmt|;
else|else
name|pixbuf
operator|=
operator|&
name|cursor
operator|->
name|pixbuf
expr_stmt|;
if|if
condition|(
operator|!
operator|*
name|pixbuf
condition|)
operator|*
name|pixbuf
operator|=
name|gdk_pixbuf_new_from_inline
argument_list|(
operator|-
literal|1
argument_list|,
name|bw
condition|?
name|cursor
operator|->
name|pixbuf_data_bw
else|:
name|cursor
operator|->
name|pixbuf_data
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|*
name|pixbuf
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
operator|*
name|pixbuf
return|;
block|}
end_function

begin_function
name|GdkCursor
modifier|*
DECL|function|gimp_cursor_new (GdkDisplay * display,GimpCursorFormat cursor_format,GimpCursorType cursor_type,GimpToolCursorType tool_cursor,GimpCursorModifier modifier)
name|gimp_cursor_new
parameter_list|(
name|GdkDisplay
modifier|*
name|display
parameter_list|,
name|GimpCursorFormat
name|cursor_format
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
name|gboolean
name|bw
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
name|GDK_LAST_CURSOR
condition|)
return|return
name|gdk_cursor_new_for_display
argument_list|(
name|display
argument_list|,
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
if|if
condition|(
name|cursor_format
operator|!=
name|GIMP_CURSOR_FORMAT_BITMAP
operator|&&
name|gdk_display_supports_cursor_alpha
argument_list|(
name|display
argument_list|)
operator|&&
name|gdk_display_supports_cursor_color
argument_list|(
name|display
argument_list|)
condition|)
block|{
name|bw
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|bw
operator|=
name|TRUE
expr_stmt|;
block|}
name|pixbuf
operator|=
name|gdk_pixbuf_copy
argument_list|(
name|get_cursor_pixbuf
argument_list|(
name|bmcursor
argument_list|,
name|bw
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
argument_list|,
name|bw
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
name|bw
condition|?
literal|255
else|:
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
argument_list|,
name|bw
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
name|bw
condition|?
literal|255
else|:
literal|200
argument_list|)
expr_stmt|;
block|}
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
DECL|function|gimp_cursor_set (GtkWidget * widget,GimpCursorFormat cursor_format,GimpCursorType cursor_type,GimpToolCursorType tool_cursor,GimpCursorModifier modifier)
name|gimp_cursor_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpCursorFormat
name|cursor_format
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
name|cursor_format
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
block|}
end_function

end_unit

