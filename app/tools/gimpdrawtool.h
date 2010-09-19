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

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27da71460103
block|{
DECL|enumerator|GIMP_HANDLE_SQUARE
name|GIMP_HANDLE_SQUARE
block|,
DECL|enumerator|GIMP_HANDLE_FILLED_SQUARE
name|GIMP_HANDLE_FILLED_SQUARE
block|,
DECL|enumerator|GIMP_HANDLE_CIRCLE
name|GIMP_HANDLE_CIRCLE
block|,
DECL|enumerator|GIMP_HANDLE_FILLED_CIRCLE
name|GIMP_HANDLE_FILLED_CIRCLE
block|,
DECL|enumerator|GIMP_HANDLE_CROSS
name|GIMP_HANDLE_CROSS
DECL|typedef|GimpHandleType
block|}
name|GimpHandleType
typedef|;
end_typedef

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
comment|/*  The display we are drawing to (may be                                  *  a different one than tool->display)                                  */
DECL|member|paused_count
name|gint
name|paused_count
decl_stmt|;
comment|/*  count to keep track of multiple pauses  */
DECL|member|is_drawn
name|gboolean
name|is_drawn
decl_stmt|;
comment|/*  is the stuff we draw currently visible  */
DECL|member|draw_timeout
name|guint
name|draw_timeout
decl_stmt|;
comment|/*  draw delay timeout ID                   */
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
name|gboolean
name|gimp_draw_tool_is_drawn
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_set_transform
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GimpMatrix3
modifier|*
name|transform
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
name|gboolean
name|gimp_draw_tool_in_radius
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
parameter_list|,
name|gint
name|radius
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_draw_line
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
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_draw_dashed_line
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
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_draw_guide_line
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_draw_rectangle
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
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_draw_arc
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
name|gint
name|angle1
parameter_list|,
name|gint
name|angle2
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_draw_rectangle_by_anchor
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
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GtkAnchorType
name|anchor
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_draw_arc_by_anchor
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
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|angle1
parameter_list|,
name|gint
name|angle2
parameter_list|,
name|GtkAnchorType
name|anchor
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_draw_cross_by_anchor
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
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
name|GtkAnchorType
name|anchor
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_draw_handle
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
name|GtkAnchorType
name|anchor
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_draw_corner
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
name|GtkAnchorType
name|anchor
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_draw_lines
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
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_draw_strokes
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
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_draw_boundary
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
specifier|const
name|BoundSeg
modifier|*
name|bound_segs
parameter_list|,
name|gint
name|n_bound_segs
parameter_list|,
name|gdouble
name|offset_x
parameter_list|,
name|gdouble
name|offset_y
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_draw_text_cursor
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
parameter_list|,
name|gboolean
name|use_offsets
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
name|GtkAnchorType
name|anchor
parameter_list|,
name|gboolean
name|use_offsets
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

