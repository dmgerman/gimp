begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BEZIER_SELECTP_H__
end_ifndef

begin_define
DECL|macro|__BEZIER_SELECTP_H__
define|#
directive|define
name|__BEZIER_SELECTP_H__
end_define

begin_include
include|#
directive|include
file|"draw_core.h"
end_include

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
DECL|enum|__anon2c48a27a0103
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

begin_struct
DECL|struct|_BezierPoint
struct|struct
name|_BezierPoint
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
name|BezierPoint
modifier|*
name|next
decl_stmt|;
comment|/* next point on curve               */
DECL|member|prev
name|BezierPoint
modifier|*
name|prev
decl_stmt|;
comment|/* prev point on curve               */
DECL|member|next_curve
name|BezierPoint
modifier|*
name|next_curve
decl_stmt|;
comment|/* Next curve segment                */
DECL|member|pointflags
name|gint
name|pointflags
decl_stmt|;
comment|/* Status of point 0 = not selected  			       * 1 = selected  			       */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_BezierSelect
struct|struct
name|_BezierSelect
block|{
DECL|member|state
name|gint
name|state
decl_stmt|;
comment|/* start, add, edit or drag          */
DECL|member|draw
name|gint
name|draw
decl_stmt|;
comment|/* all or part                       */
DECL|member|closed
name|gint
name|closed
decl_stmt|;
comment|/* is the last curve closed          */
DECL|member|core
name|DrawCore
modifier|*
name|core
decl_stmt|;
comment|/* Core drawing object               */
DECL|member|points
name|BezierPoint
modifier|*
name|points
decl_stmt|;
comment|/* the curve                         */
DECL|member|cur_anchor
name|BezierPoint
modifier|*
name|cur_anchor
decl_stmt|;
comment|/* the current active anchor point   */
DECL|member|cur_control
name|BezierPoint
modifier|*
name|cur_control
decl_stmt|;
comment|/* the current active control point  */
DECL|member|last_point
name|BezierPoint
modifier|*
name|last_point
decl_stmt|;
comment|/* the last point on the curve       */
DECL|member|num_points
name|gint
name|num_points
decl_stmt|;
comment|/* number of points in the curve     */
DECL|member|mask
name|Channel
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

begin_comment
comment|/* All udata that are passed to the bezier_draw_curve must  * have this structure as the first element.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c48a27a0208
block|{
DECL|member|count
name|gint
name|count
decl_stmt|;
DECL|typedef|CountCurves
block|}
name|CountCurves
typedef|;
end_typedef

begin_typedef
DECL|typedef|BezierPointsFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|BezierPointsFunc
function_decl|)
parameter_list|(
name|BezierSelect
modifier|*
parameter_list|,
name|GdkPoint
modifier|*
parameter_list|,
name|int
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  Functions  */
end_comment

begin_function_decl
name|int
name|bezier_select_load
parameter_list|(
name|void
modifier|*
parameter_list|,
name|BezierPoint
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_draw_curve
parameter_list|(
name|BezierSelect
modifier|*
parameter_list|,
name|BezierPointsFunc
parameter_list|,
name|gint
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_select_reset
parameter_list|(
name|BezierSelect
modifier|*
name|bezier_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_select_free
parameter_list|(
name|BezierSelect
modifier|*
name|bezier_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_add_point
parameter_list|(
name|BezierSelect
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gdouble
parameter_list|,
name|gdouble
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_paste_bezierselect_to_current
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|BezierSelect
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
name|BezierSelect
modifier|*
name|bezier_sel
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_to_selection
parameter_list|(
name|BezierSelect
modifier|*
name|bezier_sel
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|bezier_distance_along
parameter_list|(
name|BezierSelect
modifier|*
name|bezier_sel
parameter_list|,
name|gint
parameter_list|,
name|gdouble
parameter_list|,
name|gint
modifier|*
parameter_list|,
name|gint
modifier|*
parameter_list|,
name|gdouble
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_draw
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|BezierSelect
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
comment|/* __BEZIER_SELECTP_H__ */
end_comment

end_unit

