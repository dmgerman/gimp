begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GRADIENT_HEADER_H__
end_ifndef

begin_define
DECL|macro|__GRADIENT_HEADER_H__
define|#
directive|define
name|__GRADIENT_HEADER_H__
end_define

begin_define
DECL|macro|GRAD_LIST_WIDTH
define|#
directive|define
name|GRAD_LIST_WIDTH
value|300
end_define

begin_define
DECL|macro|GRAD_LIST_HEIGHT
define|#
directive|define
name|GRAD_LIST_HEIGHT
value|80
end_define

begin_define
DECL|macro|GRAD_SCROLLBAR_STEP_SIZE
define|#
directive|define
name|GRAD_SCROLLBAR_STEP_SIZE
value|0.05
end_define

begin_define
DECL|macro|GRAD_SCROLLBAR_PAGE_SIZE
define|#
directive|define
name|GRAD_SCROLLBAR_PAGE_SIZE
value|0.75
end_define

begin_define
DECL|macro|GRAD_CLOSE_BUTTON_WIDTH
define|#
directive|define
name|GRAD_CLOSE_BUTTON_WIDTH
value|45
end_define

begin_define
DECL|macro|GRAD_PREVIEW_WIDTH
define|#
directive|define
name|GRAD_PREVIEW_WIDTH
value|600
end_define

begin_define
DECL|macro|GRAD_PREVIEW_HEIGHT
define|#
directive|define
name|GRAD_PREVIEW_HEIGHT
value|64
end_define

begin_define
DECL|macro|GRAD_CONTROL_HEIGHT
define|#
directive|define
name|GRAD_CONTROL_HEIGHT
value|10
end_define

begin_define
DECL|macro|GRAD_CHECK_SIZE
define|#
directive|define
name|GRAD_CHECK_SIZE
value|8
end_define

begin_define
DECL|macro|GRAD_CHECK_SIZE_SM
define|#
directive|define
name|GRAD_CHECK_SIZE_SM
value|4
end_define

begin_define
DECL|macro|GRAD_CHECK_DARK
define|#
directive|define
name|GRAD_CHECK_DARK
value|(1.0 / 3.0)
end_define

begin_define
DECL|macro|GRAD_CHECK_LIGHT
define|#
directive|define
name|GRAD_CHECK_LIGHT
value|(2.0 / 3.0)
end_define

begin_define
DECL|macro|GRAD_COLOR_BOX_WIDTH
define|#
directive|define
name|GRAD_COLOR_BOX_WIDTH
value|24
end_define

begin_define
DECL|macro|GRAD_COLOR_BOX_HEIGHT
define|#
directive|define
name|GRAD_COLOR_BOX_HEIGHT
value|16
end_define

begin_define
DECL|macro|GRAD_NUM_COLORS
define|#
directive|define
name|GRAD_NUM_COLORS
value|10
end_define

begin_define
DECL|macro|GRAD_MOVE_TIME
define|#
directive|define
name|GRAD_MOVE_TIME
value|150
end_define

begin_comment
DECL|macro|GRAD_MOVE_TIME
comment|/* ms between mouse click and detection of movement in gradient control */
end_comment

begin_define
DECL|macro|GRAD_PREVIEW_EVENT_MASK
define|#
directive|define
name|GRAD_PREVIEW_EVENT_MASK
value|(GDK_EXPOSURE_MASK | GDK_LEAVE_NOTIFY_MASK | \ 				 GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK | \ 				 GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK)
end_define

begin_define
DECL|macro|GRAD_CONTROL_EVENT_MASK
define|#
directive|define
name|GRAD_CONTROL_EVENT_MASK
value|(GDK_EXPOSURE_MASK |		\ 				 GDK_LEAVE_NOTIFY_MASK |	\ 				 GDK_POINTER_MOTION_MASK |	\ 				 GDK_POINTER_MOTION_HINT_MASK |	\ 				 GDK_BUTTON_PRESS_MASK |	\ 				 GDK_BUTTON_RELEASE_MASK |	\ 				 GDK_BUTTON1_MOTION_MASK)
end_define

begin_define
DECL|macro|GRAD_UPDATE_PREVIEW
define|#
directive|define
name|GRAD_UPDATE_PREVIEW
value|0x0001
end_define

begin_define
DECL|macro|GRAD_UPDATE_CONTROL
define|#
directive|define
name|GRAD_UPDATE_CONTROL
value|0x0002
end_define

begin_define
DECL|macro|GRAD_RESET_CONTROL
define|#
directive|define
name|GRAD_RESET_CONTROL
value|0X0004
end_define

begin_comment
comment|/***** Types *****/
end_comment

begin_comment
comment|/* Gradient segment type */
end_comment

begin_typedef
DECL|enum|__anon29bd465f0103
typedef|typedef
enum|enum
block|{
DECL|enumerator|GRAD_LINEAR
name|GRAD_LINEAR
init|=
literal|0
block|,
DECL|enumerator|GRAD_CURVED
name|GRAD_CURVED
block|,
DECL|enumerator|GRAD_SINE
name|GRAD_SINE
block|,
DECL|enumerator|GRAD_SPHERE_INCREASING
name|GRAD_SPHERE_INCREASING
block|,
DECL|enumerator|GRAD_SPHERE_DECREASING
name|GRAD_SPHERE_DECREASING
DECL|typedef|grad_type_t
block|}
name|grad_type_t
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon29bd465f0203
typedef|typedef
enum|enum
block|{
DECL|enumerator|GRAD_RGB
name|GRAD_RGB
init|=
literal|0
block|,
comment|/* normal RGB */
DECL|enumerator|GRAD_HSV_CCW
name|GRAD_HSV_CCW
block|,
comment|/* counterclockwise hue */
DECL|enumerator|GRAD_HSV_CW
name|GRAD_HSV_CW
comment|/* clockwise hue */
DECL|typedef|grad_color_t
block|}
name|grad_color_t
typedef|;
end_typedef

begin_typedef
DECL|struct|_grad_segment_t
typedef|typedef
struct|struct
name|_grad_segment_t
block|{
DECL|member|left
DECL|member|middle
DECL|member|right
name|double
name|left
decl_stmt|,
name|middle
decl_stmt|,
name|right
decl_stmt|;
comment|/* Left pos, midpoint, right pos */
DECL|member|r0
DECL|member|g0
DECL|member|b0
DECL|member|a0
name|double
name|r0
decl_stmt|,
name|g0
decl_stmt|,
name|b0
decl_stmt|,
name|a0
decl_stmt|;
comment|/* Left color */
DECL|member|r1
DECL|member|g1
DECL|member|b1
DECL|member|a1
name|double
name|r1
decl_stmt|,
name|g1
decl_stmt|,
name|b1
decl_stmt|,
name|a1
decl_stmt|;
comment|/* Right color */
DECL|member|type
name|grad_type_t
name|type
decl_stmt|;
comment|/* Segment's blending function */
DECL|member|color
name|grad_color_t
name|color
decl_stmt|;
comment|/* Segment's coloring type */
DECL|member|prev
DECL|member|next
name|struct
name|_grad_segment_t
modifier|*
name|prev
decl_stmt|,
modifier|*
name|next
decl_stmt|;
comment|/* For linked list of segments */
DECL|typedef|grad_segment_t
block|}
name|grad_segment_t
typedef|;
end_typedef

begin_comment
comment|/* Complete gradient type */
end_comment

begin_typedef
DECL|struct|_gradient_t
typedef|typedef
struct|struct
name|_gradient_t
block|{
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|segments
name|grad_segment_t
modifier|*
name|segments
decl_stmt|;
DECL|member|last_visited
name|grad_segment_t
modifier|*
name|last_visited
decl_stmt|;
DECL|member|dirty
name|int
name|dirty
decl_stmt|;
DECL|member|filename
name|char
modifier|*
name|filename
decl_stmt|;
DECL|member|pixmap
name|GdkPixmap
modifier|*
name|pixmap
decl_stmt|;
DECL|typedef|gradient_t
block|}
name|gradient_t
typedef|;
end_typedef

begin_comment
comment|/* Gradient editor type */
end_comment

begin_typedef
DECL|enum|__anon29bd465f0303
typedef|typedef
enum|enum
block|{
DECL|enumerator|GRAD_DRAG_NONE
name|GRAD_DRAG_NONE
init|=
literal|0
block|,
DECL|enumerator|GRAD_DRAG_LEFT
name|GRAD_DRAG_LEFT
block|,
DECL|enumerator|GRAD_DRAG_MIDDLE
name|GRAD_DRAG_MIDDLE
block|,
DECL|enumerator|GRAD_DRAG_ALL
name|GRAD_DRAG_ALL
DECL|typedef|control_drag_mode_t
block|}
name|control_drag_mode_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29bd465f0408
typedef|typedef
struct|struct
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|gc
name|GdkGC
modifier|*
name|gc
decl_stmt|;
DECL|member|hint_label
name|GtkWidget
modifier|*
name|hint_label
decl_stmt|;
DECL|member|clist
name|GtkWidget
modifier|*
name|clist
decl_stmt|;
DECL|member|scrollbar
name|GtkWidget
modifier|*
name|scrollbar
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|control
name|GtkWidget
modifier|*
name|control
decl_stmt|;
comment|/* Zoom and scrollbar */
DECL|member|zoom_factor
name|unsigned
name|int
name|zoom_factor
decl_stmt|;
DECL|member|scroll_data
name|GtkObject
modifier|*
name|scroll_data
decl_stmt|;
comment|/* Instant update */
DECL|member|instant_update
name|int
name|instant_update
decl_stmt|;
comment|/* Gradient preview */
DECL|member|preview_rows
name|guchar
modifier|*
name|preview_rows
index|[
literal|2
index|]
decl_stmt|;
comment|/* For caching redraw info */
DECL|member|preview_last_x
name|gint
name|preview_last_x
decl_stmt|;
DECL|member|preview_button_down
name|int
name|preview_button_down
decl_stmt|;
comment|/* Gradient control */
DECL|member|control_pixmap
name|GdkPixmap
modifier|*
name|control_pixmap
decl_stmt|;
DECL|member|control_drag_segment
name|grad_segment_t
modifier|*
name|control_drag_segment
decl_stmt|;
comment|/* Segment which is being dragged */
DECL|member|control_sel_l
name|grad_segment_t
modifier|*
name|control_sel_l
decl_stmt|;
comment|/* Left segment of selection */
DECL|member|control_sel_r
name|grad_segment_t
modifier|*
name|control_sel_r
decl_stmt|;
comment|/* Right segment of selection */
DECL|member|control_drag_mode
name|control_drag_mode_t
name|control_drag_mode
decl_stmt|;
comment|/* What is being dragged? */
DECL|member|control_click_time
name|guint32
name|control_click_time
decl_stmt|;
comment|/* Time when mouse was pressed */
DECL|member|control_compress
name|int
name|control_compress
decl_stmt|;
comment|/* Compressing/expanding handles */
DECL|member|control_last_x
name|gint
name|control_last_x
decl_stmt|;
comment|/* Last mouse position when dragging */
DECL|member|control_last_gx
name|double
name|control_last_gx
decl_stmt|;
comment|/* Last position (wrt gradient) when dragging */
DECL|member|control_orig_pos
name|double
name|control_orig_pos
decl_stmt|;
comment|/* Original click position when dragging */
DECL|member|control_main_popup
name|GtkWidget
modifier|*
name|control_main_popup
decl_stmt|;
comment|/* Popup menu */
DECL|member|control_blending_label
name|GtkWidget
modifier|*
name|control_blending_label
decl_stmt|;
comment|/* Blending function label */
DECL|member|control_coloring_label
name|GtkWidget
modifier|*
name|control_coloring_label
decl_stmt|;
comment|/* Coloring type label */
DECL|member|control_splitm_label
name|GtkWidget
modifier|*
name|control_splitm_label
decl_stmt|;
comment|/* Split at midpoint label */
DECL|member|control_splitu_label
name|GtkWidget
modifier|*
name|control_splitu_label
decl_stmt|;
comment|/* Split uniformly label */
DECL|member|control_delete_menu_item
name|GtkWidget
modifier|*
name|control_delete_menu_item
decl_stmt|;
comment|/* Delete menu item */
DECL|member|control_delete_label
name|GtkWidget
modifier|*
name|control_delete_label
decl_stmt|;
comment|/* Delete label */
DECL|member|control_recenter_label
name|GtkWidget
modifier|*
name|control_recenter_label
decl_stmt|;
comment|/* Re-center label */
DECL|member|control_redistribute_label
name|GtkWidget
modifier|*
name|control_redistribute_label
decl_stmt|;
comment|/* Re-distribute label */
DECL|member|control_flip_label
name|GtkWidget
modifier|*
name|control_flip_label
decl_stmt|;
comment|/* Flip label */
DECL|member|control_replicate_label
name|GtkWidget
modifier|*
name|control_replicate_label
decl_stmt|;
comment|/* Replicate label */
DECL|member|control_blend_colors_menu_item
name|GtkWidget
modifier|*
name|control_blend_colors_menu_item
decl_stmt|;
comment|/* Blend colors menu item */
DECL|member|control_blend_opacity_menu_item
name|GtkWidget
modifier|*
name|control_blend_opacity_menu_item
decl_stmt|;
comment|/* Blend opacity menu item */
DECL|member|control_left_load_popup
name|GtkWidget
modifier|*
name|control_left_load_popup
decl_stmt|;
comment|/* Left endpoint load menu */
DECL|member|control_left_save_popup
name|GtkWidget
modifier|*
name|control_left_save_popup
decl_stmt|;
comment|/* Left endpoint save menu */
DECL|member|control_right_load_popup
name|GtkWidget
modifier|*
name|control_right_load_popup
decl_stmt|;
comment|/* Right endpoint load menu */
DECL|member|control_right_save_popup
name|GtkWidget
modifier|*
name|control_right_save_popup
decl_stmt|;
comment|/* Right endpoint save menu */
DECL|member|control_blending_popup
name|GtkWidget
modifier|*
name|control_blending_popup
decl_stmt|;
comment|/* Blending function menu */
DECL|member|control_coloring_popup
name|GtkWidget
modifier|*
name|control_coloring_popup
decl_stmt|;
comment|/* Coloring type menu */
DECL|member|control_sel_ops_popup
name|GtkWidget
modifier|*
name|control_sel_ops_popup
decl_stmt|;
comment|/* Selection ops menu */
DECL|member|accel_group
name|GtkAccelGroup
modifier|*
name|accel_group
decl_stmt|;
comment|/* Blending and coloring menus */
DECL|member|control_blending_items
name|GtkWidget
modifier|*
name|control_blending_items
index|[
literal|5
operator|+
literal|1
index|]
decl_stmt|;
comment|/* Add 1 for the "Varies" item */
DECL|member|control_coloring_items
name|GtkWidget
modifier|*
name|control_coloring_items
index|[
literal|3
operator|+
literal|1
index|]
decl_stmt|;
comment|/* Split uniformly dialog */
DECL|member|split_parts
name|int
name|split_parts
decl_stmt|;
comment|/* Replicate dialog */
DECL|member|replicate_times
name|int
name|replicate_times
decl_stmt|;
comment|/* Saved colors */
DECL|struct|__anon29bd465f0508
struct|struct
block|{
DECL|member|r
DECL|member|g
DECL|member|b
DECL|member|a
name|double
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
DECL|member|saved_colors
block|}
name|saved_colors
index|[
name|GRAD_NUM_COLORS
index|]
struct|;
DECL|member|left_load_color_boxes
name|GtkWidget
modifier|*
name|left_load_color_boxes
index|[
name|GRAD_NUM_COLORS
operator|+
literal|3
index|]
decl_stmt|;
DECL|member|left_load_labels
name|GtkWidget
modifier|*
name|left_load_labels
index|[
name|GRAD_NUM_COLORS
operator|+
literal|3
index|]
decl_stmt|;
DECL|member|left_save_color_boxes
name|GtkWidget
modifier|*
name|left_save_color_boxes
index|[
name|GRAD_NUM_COLORS
index|]
decl_stmt|;
DECL|member|left_save_labels
name|GtkWidget
modifier|*
name|left_save_labels
index|[
name|GRAD_NUM_COLORS
index|]
decl_stmt|;
DECL|member|right_load_color_boxes
name|GtkWidget
modifier|*
name|right_load_color_boxes
index|[
name|GRAD_NUM_COLORS
operator|+
literal|3
index|]
decl_stmt|;
DECL|member|right_load_labels
name|GtkWidget
modifier|*
name|right_load_labels
index|[
name|GRAD_NUM_COLORS
operator|+
literal|3
index|]
decl_stmt|;
DECL|member|right_save_color_boxes
name|GtkWidget
modifier|*
name|right_save_color_boxes
index|[
name|GRAD_NUM_COLORS
index|]
decl_stmt|;
DECL|member|right_save_labels
name|GtkWidget
modifier|*
name|right_save_labels
index|[
name|GRAD_NUM_COLORS
index|]
decl_stmt|;
comment|/* Color dialogs */
DECL|member|left_color_preview
name|GtkWidget
modifier|*
name|left_color_preview
decl_stmt|;
DECL|member|left_saved_segments
name|grad_segment_t
modifier|*
name|left_saved_segments
decl_stmt|;
DECL|member|left_saved_dirty
name|int
name|left_saved_dirty
decl_stmt|;
DECL|member|right_color_preview
name|GtkWidget
modifier|*
name|right_color_preview
decl_stmt|;
DECL|member|right_saved_segments
name|grad_segment_t
modifier|*
name|right_saved_segments
decl_stmt|;
DECL|member|right_saved_dirty
name|int
name|right_saved_dirty
decl_stmt|;
DECL|typedef|gradient_editor_t
block|}
name|gradient_editor_t
typedef|;
end_typedef

begin_comment
comment|/* Selection dialog functions */
end_comment

begin_function_decl
name|void
name|sel_update_dialogs
parameter_list|(
name|gint
name|row
parameter_list|,
name|gradient_t
modifier|*
name|grad
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|grad_sel_free_all
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|grad_sel_refill_all
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|grad_sel_rename_all
parameter_list|(
name|gint
name|n
parameter_list|,
name|gradient_t
modifier|*
name|grad
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|grad_sel_new_all
parameter_list|(
name|gint
name|n
parameter_list|,
name|gradient_t
modifier|*
name|grad
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|grad_sel_copy_all
parameter_list|(
name|gint
name|n
parameter_list|,
name|gradient_t
modifier|*
name|grad
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|grad_sel_delete_all
parameter_list|(
name|gint
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|grad_create_gradient_editor_init
parameter_list|(
name|gint
name|need_show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ed_insert_in_gradients_listbox
parameter_list|(
name|GdkGC
modifier|*
parameter_list|,
name|GtkWidget
modifier|*
parameter_list|,
name|gradient_t
modifier|*
name|grad
parameter_list|,
name|int
name|pos
parameter_list|,
name|int
name|select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|grad_set_grad_to_name
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|ed_set_list_of_gradients
parameter_list|(
name|GdkGC
modifier|*
parameter_list|,
name|GtkWidget
modifier|*
parameter_list|,
name|gradient_t
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Varibles used */
end_comment

begin_decl_stmt
specifier|extern
name|gradient_t
modifier|*
name|curr_gradient
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* The active gradient */
end_comment

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|gradients_list
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* The list of gradients */
end_comment

begin_decl_stmt
specifier|extern
name|gradient_t
modifier|*
name|grad_default_gradient
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gradient_editor_t
modifier|*
name|g_editor
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* The gradient editor */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GRADIENT_HEADER_H__  */
end_comment

end_unit

