begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BEZIER_SELECT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BEZIER_SELECT_TOOL_H__
define|#
directive|define
name|__GIMP_BEZIER_SELECT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpselectiontool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_BEZIER_SELECT_TOOL
define|#
directive|define
name|GIMP_TYPE_BEZIER_SELECT_TOOL
value|(gimp_bezier_select_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_BEZIER_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_BEZIER_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BEZIER_SELECT_TOOL, GimpBezierSelectTool))
end_define

begin_define
DECL|macro|GIMP_BEZIER_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_BEZIER_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BEZIER_SELECT_TOOL, GimpBezierSelectToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_BEZIER_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_IS_BEZIER_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BEZIER_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_BEZIER_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BEZIER_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BEZIER_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_BEZIER_SELECT_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BEZIER_SELECT_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BEZIER_SELECT_TOOL, GimpBezierSelectToolClass))
end_define

begin_define
DECL|macro|BEZIER_START
define|#
directive|define
name|BEZIER_START
value|1
end_define

begin_define
DECL|macro|BEZIER_ADD
define|#
directive|define
name|BEZIER_ADD
value|2
end_define

begin_define
DECL|macro|BEZIER_EDIT
define|#
directive|define
name|BEZIER_EDIT
value|4
end_define

begin_define
DECL|macro|BEZIER_DRAG
define|#
directive|define
name|BEZIER_DRAG
value|8
end_define

begin_define
DECL|macro|BEZIER_ANCHOR
define|#
directive|define
name|BEZIER_ANCHOR
value|1
end_define

begin_define
DECL|macro|BEZIER_CONTROL
define|#
directive|define
name|BEZIER_CONTROL
value|2
end_define

begin_define
DECL|macro|BEZIER_MOVE
define|#
directive|define
name|BEZIER_MOVE
value|3
end_define

begin_define
DECL|macro|IMAGE_COORDS
define|#
directive|define
name|IMAGE_COORDS
value|1
end_define

begin_define
DECL|macro|AA_IMAGE_COORDS
define|#
directive|define
name|AA_IMAGE_COORDS
value|2
end_define

begin_define
DECL|macro|SCREEN_COORDS
define|#
directive|define
name|SCREEN_COORDS
value|3
end_define

begin_define
DECL|macro|SUBDIVIDE
define|#
directive|define
name|SUBDIVIDE
value|1000
end_define

begin_enum
DECL|enum|__anon2a0e19250103
DECL|enumerator|EXTEND_EDIT
DECL|enumerator|EXTEND_ADD
DECL|enumerator|EXTEND_REMOVE
DECL|enumerator|EXTEND_NEW
enum|enum
block|{
name|EXTEND_EDIT
block|,
name|EXTEND_ADD
block|,
name|EXTEND_REMOVE
block|,
name|EXTEND_NEW
block|}
enum|;
end_enum

begin_comment
comment|/* typedef struct _GimpBezierSelectTool      GimpBezierSelectTool;  * typedef struct _GimpBezierSelectPoint     GimpBezierSelectPoint; */
end_comment

begin_typedef
DECL|typedef|GimpBezierSelectToolClass
typedef|typedef
name|struct
name|_GimpBezierSelectToolClass
name|GimpBezierSelectToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBezierSelectPoint
struct|struct
name|_GimpBezierSelectPoint
block|{
DECL|member|type
name|gint
name|type
decl_stmt|;
comment|/* type of point (anchor/control/move) */
DECL|member|x
DECL|member|y
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/* location of point in image space  */
DECL|member|sx
DECL|member|sy
name|gint
name|sx
decl_stmt|,
name|sy
decl_stmt|;
comment|/* location of point in screen space */
DECL|member|next
name|GimpBezierSelectPoint
modifier|*
name|next
decl_stmt|;
comment|/* next point on curve               */
DECL|member|prev
name|GimpBezierSelectPoint
modifier|*
name|prev
decl_stmt|;
comment|/* prev point on curve               */
DECL|member|next_curve
name|GimpBezierSelectPoint
modifier|*
name|next_curve
decl_stmt|;
comment|/* Next curve segment                */
DECL|member|pointflags
name|guint
name|pointflags
range|:
literal|1
decl_stmt|;
comment|/* Status of point 0 = not selected  			        * 1 = selected */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBezierSelectTool
struct|struct
name|_GimpBezierSelectTool
block|{
DECL|member|parent_instance
name|GimpSelectionTool
name|parent_instance
decl_stmt|;
DECL|member|state
name|gint
name|state
decl_stmt|;
comment|/* start, add, edit or drag          */
DECL|member|draw_mode
name|gint
name|draw_mode
decl_stmt|;
comment|/* all or part                       */
DECL|member|closed
name|gint
name|closed
decl_stmt|;
comment|/* is the last curve closed          */
DECL|member|points
name|GimpBezierSelectPoint
modifier|*
name|points
decl_stmt|;
comment|/* the curve                         */
DECL|member|cur_anchor
name|GimpBezierSelectPoint
modifier|*
name|cur_anchor
decl_stmt|;
comment|/* the current active anchor point   */
DECL|member|cur_control
name|GimpBezierSelectPoint
modifier|*
name|cur_control
decl_stmt|;
comment|/* the current active control point  */
DECL|member|last_point
name|GimpBezierSelectPoint
modifier|*
name|last_point
decl_stmt|;
comment|/* the last point on the curve       */
DECL|member|num_points
name|guint
name|num_points
decl_stmt|;
comment|/* number of points in the curve     */
DECL|member|mask
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
comment|/* null if the curve is open         */
DECL|member|scanlines
name|GSList
modifier|*
modifier|*
name|scanlines
decl_stmt|;
comment|/* used in converting a curve        */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBezierSelectToolClass
struct|struct
name|_GimpBezierSelectToolClass
block|{
DECL|member|parent_class
name|GimpSelectionToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpBezierSelectPointsFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpBezierSelectPointsFunc
function_decl|)
parameter_list|(
name|GimpBezierSelectTool
modifier|*
name|bezier_sel
parameter_list|,
name|GdkPoint
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2a0e19250208
block|{
DECL|member|count
name|guint
name|count
decl_stmt|;
DECL|typedef|CountCurves
block|}
name|CountCurves
typedef|;
end_typedef

begin_comment
comment|/* Public functions */
end_comment

begin_function_decl
name|void
name|gimp_bezier_select_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolRegisterCallback
name|callback
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_bezier_select_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
name|bezier_tool_selected
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_bezier_select_tool_bezier_select
parameter_list|(
name|GimpBezierSelectTool
modifier|*
name|rect_tool
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_select
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|SelectOps
name|op
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|bezier_select_load
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|GimpBezierSelectPoint
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|gint
name|closed
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_draw_curve
parameter_list|(
name|GimpBezierSelectTool
modifier|*
name|bezier_sel
parameter_list|,
name|GimpBezierSelectPointsFunc
name|func
parameter_list|,
name|gint
name|coord
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_select_reset
parameter_list|(
name|GimpBezierSelectTool
modifier|*
name|bezier_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_select_free
parameter_list|(
name|GimpBezierSelectTool
modifier|*
name|bezier_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBezierSelectTool
modifier|*
name|path_to_beziersel
parameter_list|(
name|Path
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_add_point
parameter_list|(
name|GimpBezierSelectTool
modifier|*
name|bezier_sel
parameter_list|,
name|gint
name|type
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
name|void
name|bezier_paste_bezierselect_to_current
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|GimpBezierSelectTool
modifier|*
name|bezier_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_select_mode
parameter_list|(
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_stroke
parameter_list|(
name|GimpBezierSelectTool
modifier|*
name|bezier_sel
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|gint
name|subdivisions
parameter_list|,
name|gint
name|open_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_to_selection
parameter_list|(
name|GimpBezierSelectTool
modifier|*
name|bezier_sel
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|bezier_distance_along
parameter_list|(
name|GimpBezierSelectTool
modifier|*
name|bezier_sel
parameter_list|,
name|gint
name|open_path
parameter_list|,
name|gdouble
name|dist
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gdouble
modifier|*
name|gradient
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_draw
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|GimpBezierSelectTool
modifier|*
name|bezier_sel
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BEZIER_SELECT_TOOL_H__  */
end_comment

end_unit

