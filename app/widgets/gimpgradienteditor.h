begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Gradient editor module copyight (C) 1996-1997 Federico Mena Quintero  * federico@nuclecu.unam.mx  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GRADIENT_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GRADIENT_EDITOR_H__
define|#
directive|define
name|__GIMP_GRADIENT_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|"gimpdataeditor.h"
end_include

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
DECL|enum|__anon292ac8020103
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

begin_define
DECL|macro|GIMP_TYPE_GRADIENT_EDITOR
define|#
directive|define
name|GIMP_TYPE_GRADIENT_EDITOR
value|(gimp_gradient_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_GRADIENT_EDITOR (obj)
define|#
directive|define
name|GIMP_GRADIENT_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_GRADIENT_EDITOR, GimpGradientEditor))
end_define

begin_define
DECL|macro|GIMP_GRADIENT_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_GRADIENT_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_GRADIENT_EDITOR, GimpGradientEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_GRADIENT_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_GRADIENT_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_GRADIENT_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_GRADIENT_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_GRADIENT_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_GRADIENT_EDITOR))
end_define

begin_define
DECL|macro|GIMP_GRADIENT_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_GRADIENT_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_GRADIENT_EDITOR, GimpGradientEditorClass))
end_define

begin_typedef
DECL|typedef|GimpGradientEditorClass
typedef|typedef
name|struct
name|_GimpGradientEditorClass
name|GimpGradientEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpGradientEditor
struct|struct
name|_GimpGradientEditor
block|{
DECL|member|parent_instance
name|GimpDataEditor
name|parent_instance
decl_stmt|;
DECL|member|current_color
name|GtkWidget
modifier|*
name|current_color
decl_stmt|;
DECL|member|hint_label1
name|GtkWidget
modifier|*
name|hint_label1
decl_stmt|;
DECL|member|hint_label2
name|GtkWidget
modifier|*
name|hint_label2
decl_stmt|;
DECL|member|hint_label3
name|GtkWidget
modifier|*
name|hint_label3
decl_stmt|;
DECL|member|hint_label4
name|GtkWidget
modifier|*
name|hint_label4
decl_stmt|;
DECL|member|scrollbar
name|GtkWidget
modifier|*
name|scrollbar
decl_stmt|;
DECL|member|control
name|GtkWidget
modifier|*
name|control
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
comment|/*  Color dialog  */
DECL|member|color_dialog
name|GtkWidget
modifier|*
name|color_dialog
decl_stmt|;
comment|/*  Gradient view  */
DECL|member|view_last_x
name|gint
name|view_last_x
decl_stmt|;
DECL|member|view_button_down
name|gboolean
name|view_button_down
decl_stmt|;
comment|/*  Gradient control  */
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

begin_struct
DECL|struct|_GimpGradientEditorClass
struct|struct
name|_GimpGradientEditorClass
block|{
DECL|member|parent_class
name|GimpDataEditorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_gradient_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_gradient_editor_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gradient_editor_update
parameter_list|(
name|GimpGradientEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gradient_editor_zoom
parameter_list|(
name|GimpGradientEditor
modifier|*
name|editor
parameter_list|,
name|GimpZoomType
name|zoom_type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GRADIENT_EDITOR_H__ */
end_comment

end_unit

