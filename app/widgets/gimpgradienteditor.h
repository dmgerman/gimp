begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Gradient editor module copyight (C) 1996-1997 Federico Mena Quintero  * federico@nuclecu.unam.mx  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GRADIENT_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GRADIENT_EDITOR_H__
define|#
directive|define
name|__GRADIENT_EDITOR_H__
end_define

begin_define
DECL|macro|GRAD_NUM_COLORS
define|#
directive|define
name|GRAD_NUM_COLORS
value|10
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28fefe890103
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
DECL|typedef|GradientEditorDragMode
block|}
name|GradientEditorDragMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28fefe890203
block|{
DECL|enumerator|GRAD_UPDATE_GRADIENT
name|GRAD_UPDATE_GRADIENT
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GRAD_UPDATE_PREVIEW
name|GRAD_UPDATE_PREVIEW
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GRAD_UPDATE_CONTROL
name|GRAD_UPDATE_CONTROL
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GRAD_RESET_CONTROL
name|GRAD_RESET_CONTROL
init|=
literal|1
operator|<<
literal|3
DECL|typedef|GradientEditorUpdateMask
block|}
name|GradientEditorUpdateMask
typedef|;
end_typedef

begin_struct
DECL|struct|_GradientEditor
struct|struct
name|_GradientEditor
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|name
name|GtkWidget
modifier|*
name|name
decl_stmt|;
DECL|member|hint_label
name|GtkWidget
modifier|*
name|hint_label
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
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
comment|/*  Zoom and scrollbar  */
DECL|member|zoom_factor
name|guint
name|zoom_factor
decl_stmt|;
DECL|member|scroll_data
name|GtkObject
modifier|*
name|scroll_data
decl_stmt|;
comment|/*  Instant update  */
DECL|member|instant_update
name|gboolean
name|instant_update
decl_stmt|;
comment|/*  Gradient preview  */
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
name|gboolean
name|preview_button_down
decl_stmt|;
comment|/*  Gradient control  */
DECL|member|control_pixmap
name|GdkPixmap
modifier|*
name|control_pixmap
decl_stmt|;
DECL|member|control_drag_segment
name|GimpGradientSegment
modifier|*
name|control_drag_segment
decl_stmt|;
comment|/* Segment which is being dragged */
DECL|member|control_sel_l
name|GimpGradientSegment
modifier|*
name|control_sel_l
decl_stmt|;
comment|/* Left segment of selection */
DECL|member|control_sel_r
name|GimpGradientSegment
modifier|*
name|control_sel_r
decl_stmt|;
comment|/* Right segment of selection */
DECL|member|control_drag_mode
name|GradientEditorDragMode
name|control_drag_mode
decl_stmt|;
comment|/* What is being dragged? */
DECL|member|control_click_time
name|guint32
name|control_click_time
decl_stmt|;
comment|/* Time when mouse was pressed */
DECL|member|control_compress
name|gboolean
name|control_compress
decl_stmt|;
comment|/* Compressing/expanding handles */
DECL|member|control_last_x
name|gint
name|control_last_x
decl_stmt|;
comment|/* Last mouse position when dragging */
DECL|member|control_last_gx
name|gdouble
name|control_last_gx
decl_stmt|;
comment|/* Last position (wrt gradient) when dragging */
DECL|member|control_orig_pos
name|gdouble
name|control_orig_pos
decl_stmt|;
comment|/* Original click position when dragging */
comment|/*  Split uniformly dialog  */
DECL|member|split_parts
name|gint
name|split_parts
decl_stmt|;
comment|/*  Replicate dialog  */
DECL|member|replicate_times
name|gint
name|replicate_times
decl_stmt|;
comment|/*  Saved colors  */
DECL|member|saved_colors
name|GimpRGB
name|saved_colors
index|[
name|GRAD_NUM_COLORS
index|]
decl_stmt|;
comment|/*  Color dialogs  */
DECL|member|left_saved_segments
name|GimpGradientSegment
modifier|*
name|left_saved_segments
decl_stmt|;
DECL|member|left_saved_dirty
name|gboolean
name|left_saved_dirty
decl_stmt|;
DECL|member|right_saved_segments
name|GimpGradientSegment
modifier|*
name|right_saved_segments
decl_stmt|;
DECL|member|right_saved_dirty
name|gboolean
name|right_saved_dirty
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GradientEditor
modifier|*
name|gradient_editor_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_set_gradient
parameter_list|(
name|GradientEditor
modifier|*
name|gradient_editor
parameter_list|,
name|GimpGradient
modifier|*
name|gradient
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_free
parameter_list|(
name|GradientEditor
modifier|*
name|gradient_editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_update
parameter_list|(
name|GradientEditor
modifier|*
name|gradient_editor
parameter_list|,
name|GradientEditorUpdateMask
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GRADIENT_EDITOR_H__ */
end_comment

end_unit

