begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAW_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAW_TOOL_H__
define|#
directive|define
name|__GIMP_DRAW_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimptool.h"
end_include

begin_define
DECL|macro|GIMP_TOOL_HANDLE_SIZE_CIRCLE
define|#
directive|define
name|GIMP_TOOL_HANDLE_SIZE_CIRCLE
value|13
end_define

begin_define
DECL|macro|GIMP_TOOL_HANDLE_SIZE_CROSS
define|#
directive|define
name|GIMP_TOOL_HANDLE_SIZE_CROSS
value|15
end_define

begin_define
DECL|macro|GIMP_TOOL_HANDLE_SIZE_CROSSHAIR
define|#
directive|define
name|GIMP_TOOL_HANDLE_SIZE_CROSSHAIR
value|43
end_define

begin_define
DECL|macro|GIMP_TOOL_HANDLE_SIZE_LARGE
define|#
directive|define
name|GIMP_TOOL_HANDLE_SIZE_LARGE
value|25
end_define

begin_define
DECL|macro|GIMP_TOOL_HANDLE_SIZE_SMALL
define|#
directive|define
name|GIMP_TOOL_HANDLE_SIZE_SMALL
value|7
end_define

begin_define
DECL|macro|GIMP_TYPE_DRAW_TOOL
define|#
directive|define
name|GIMP_TYPE_DRAW_TOOL
value|(gimp_draw_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_DRAW_TOOL (obj)
define|#
directive|define
name|GIMP_DRAW_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DRAW_TOOL, GimpDrawTool))
end_define

begin_define
DECL|macro|GIMP_DRAW_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_DRAW_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DRAW_TOOL, GimpDrawToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_DRAW_TOOL (obj)
define|#
directive|define
name|GIMP_IS_DRAW_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DRAW_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_DRAW_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DRAW_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DRAW_TOOL))
end_define

begin_define
DECL|macro|GIMP_DRAW_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DRAW_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DRAW_TOOL, GimpDrawToolClass))
end_define

begin_typedef
DECL|typedef|GimpDrawToolClass
typedef|typedef
name|struct
name|_GimpDrawToolClass
name|GimpDrawToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDrawTool
struct|struct
name|_GimpDrawTool
block|{
DECL|member|parent_instance
name|GimpTool
name|parent_instance
decl_stmt|;
DECL|member|display
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
comment|/*  The display we are drawing to (may be                                    *  a different one than tool->display)                                    */
DECL|member|paused_count
name|gint
name|paused_count
decl_stmt|;
comment|/*  count to keep track of multiple pauses  */
DECL|member|draw_timeout
name|guint
name|draw_timeout
decl_stmt|;
comment|/*  draw delay timeout ID                   */
DECL|member|last_draw_time
name|guint64
name|last_draw_time
decl_stmt|;
comment|/*  time of last draw(), monotonically      */
DECL|member|preview
name|GimpCanvasItem
modifier|*
name|preview
decl_stmt|;
DECL|member|item
name|GimpCanvasItem
modifier|*
name|item
decl_stmt|;
DECL|member|group_stack
name|GList
modifier|*
name|group_stack
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDrawToolClass
struct|struct
name|_GimpDrawToolClass
block|{
DECL|member|parent_class
name|GimpToolClass
name|parent_class
decl_stmt|;
comment|/*  virtual function  */
DECL|member|draw
name|void
function_decl|(
modifier|*
name|draw
function_decl|)
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_draw_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_draw_tool_start
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_stop
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_draw_tool_is_active
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_pause
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_resume
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_draw_tool_calc_distance
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_draw_tool_calc_distance_square
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_add_preview
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_remove_preview
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_add_item
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_remove_item
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasGroup
modifier|*
name|gimp_draw_tool_add_stroke_group
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasGroup
modifier|*
name|gimp_draw_tool_add_fill_group
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_push_group
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpCanvasGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_pop_group
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_line
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_guide
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|,
name|gint
name|position
parameter_list|,
name|GimpGuideStyle
name|style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_crosshair
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|gint
name|position_x
parameter_list|,
name|gint
name|position_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_sample_point
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_rectangle
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|gboolean
name|filled
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_rectangle_guides
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpGuidesType
name|type
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_arc
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|gboolean
name|filled
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|,
name|gdouble
name|start_angle
parameter_list|,
name|gdouble
name|slice_angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_transform_preview
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|transform
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
name|gboolean
name|perspective
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_handle
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpHandleType
name|type
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpHandleAnchor
name|anchor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_corner
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|gboolean
name|highlight
parameter_list|,
name|gboolean
name|put_outside
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpHandleAnchor
name|anchor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_lines
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|gboolean
name|filled
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_strokes
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|gboolean
name|filled
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_path
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
specifier|const
name|GimpBezierDesc
modifier|*
name|desc
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_pen
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpActiveColor
name|color
parameter_list|,
name|gint
name|width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_boundary
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
specifier|const
name|GimpBoundSeg
modifier|*
name|bound_segs
parameter_list|,
name|gint
name|n_bound_segs
parameter_list|,
name|GimpMatrix3
modifier|*
name|transform
parameter_list|,
name|gdouble
name|offset_x
parameter_list|,
name|gdouble
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_draw_tool_add_text_cursor
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|PangoRectangle
modifier|*
name|cursor
parameter_list|,
name|gboolean
name|overwrite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_draw_tool_on_handle
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GimpHandleType
name|type
parameter_list|,
name|gdouble
name|handle_x
parameter_list|,
name|gdouble
name|handle_y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpHandleAnchor
name|anchor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_draw_tool_on_vectors_handle
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpAnchorType
name|preferred
parameter_list|,
name|gboolean
name|exclusive
parameter_list|,
name|GimpAnchor
modifier|*
modifier|*
name|ret_anchor
parameter_list|,
name|GimpStroke
modifier|*
modifier|*
name|ret_stroke
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_draw_tool_on_vectors_curve
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpCoords
modifier|*
name|ret_coords
parameter_list|,
name|gdouble
modifier|*
name|ret_pos
parameter_list|,
name|GimpAnchor
modifier|*
modifier|*
name|ret_segment_start
parameter_list|,
name|GimpAnchor
modifier|*
modifier|*
name|ret_segment_end
parameter_list|,
name|GimpStroke
modifier|*
modifier|*
name|ret_stroke
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_draw_tool_on_vectors
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpCoords
modifier|*
name|ret_coords
parameter_list|,
name|gdouble
modifier|*
name|ret_pos
parameter_list|,
name|GimpAnchor
modifier|*
modifier|*
name|ret_segment_start
parameter_list|,
name|GimpAnchor
modifier|*
modifier|*
name|ret_segment_end
parameter_list|,
name|GimpStroke
modifier|*
modifier|*
name|ret_stroke
parameter_list|,
name|GimpVectors
modifier|*
modifier|*
name|ret_vectors
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DRAW_TOOL_H__  */
end_comment

end_unit

