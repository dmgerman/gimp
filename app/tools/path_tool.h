begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  *   * This file Copyright (C) 1999 Simon Budig  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PATH_TOOL_H__
end_ifndef

begin_define
DECL|macro|__PATH_TOOL_H__
define|#
directive|define
name|__PATH_TOOL_H__
end_define

begin_comment
comment|/*  * Every new curve-type has to have a parameter between 0 and 1, and  * should go from a starting to a target point.  */
end_comment

begin_comment
comment|/* Some defines... */
end_comment

begin_define
DECL|macro|PATH_TOOL_WIDTH
define|#
directive|define
name|PATH_TOOL_WIDTH
value|8
end_define

begin_define
DECL|macro|PATH_TOOL_HALFWIDTH
define|#
directive|define
name|PATH_TOOL_HALFWIDTH
value|4
end_define

begin_comment
comment|/*  function prototypes  */
end_comment

begin_comment
comment|/* Small functions to determine coordinates, iterate over path/curve/segment */
end_comment

begin_function_decl
name|void
name|path_segment_get_coordinates
parameter_list|(
name|PathSegment
modifier|*
parameter_list|,
name|gdouble
parameter_list|,
name|gint
modifier|*
parameter_list|,
name|gint
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_traverse_path
parameter_list|(
name|NPath
modifier|*
parameter_list|,
name|PathTraverseFunc
parameter_list|,
name|CurveTraverseFunc
parameter_list|,
name|SegmentTraverseFunc
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_traverse_curve
parameter_list|(
name|NPath
modifier|*
parameter_list|,
name|PathCurve
modifier|*
parameter_list|,
name|CurveTraverseFunc
parameter_list|,
name|SegmentTraverseFunc
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_traverse_segment
parameter_list|(
name|NPath
modifier|*
parameter_list|,
name|PathCurve
modifier|*
parameter_list|,
name|PathSegment
modifier|*
parameter_list|,
name|SegmentTraverseFunc
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|path_locate_point
parameter_list|(
name|NPath
modifier|*
parameter_list|,
name|PathCurve
modifier|*
modifier|*
parameter_list|,
name|PathSegment
modifier|*
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Tools to manipulate paths, curves, segments */
end_comment

begin_function_decl
name|PathCurve
modifier|*
name|path_add_curve
parameter_list|(
name|NPath
modifier|*
parameter_list|,
name|gdouble
parameter_list|,
name|gdouble
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PathSegment
modifier|*
name|path_append_segment
parameter_list|(
name|NPath
modifier|*
parameter_list|,
name|PathCurve
modifier|*
parameter_list|,
name|SegmentType
parameter_list|,
name|gdouble
parameter_list|,
name|gdouble
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PathSegment
modifier|*
name|path_prepend_segment
parameter_list|(
name|NPath
modifier|*
parameter_list|,
name|PathCurve
modifier|*
parameter_list|,
name|SegmentType
parameter_list|,
name|gdouble
parameter_list|,
name|gdouble
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PathSegment
modifier|*
name|path_split_segment
parameter_list|(
name|PathSegment
modifier|*
parameter_list|,
name|gdouble
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_join_curves
parameter_list|(
name|PathSegment
modifier|*
parameter_list|,
name|PathSegment
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_flip_curve
parameter_list|(
name|PathCurve
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_free_path
parameter_list|(
name|NPath
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_free_curve
parameter_list|(
name|PathCurve
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_free_segment
parameter_list|(
name|PathSegment
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_delete_segment
parameter_list|(
name|PathSegment
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_print
parameter_list|(
name|NPath
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_offset_active
parameter_list|(
name|NPath
modifier|*
parameter_list|,
name|gdouble
parameter_list|,
name|gdouble
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_set_flags
parameter_list|(
name|GimpPathTool
modifier|*
parameter_list|,
name|NPath
modifier|*
parameter_list|,
name|PathCurve
modifier|*
parameter_list|,
name|PathSegment
modifier|*
parameter_list|,
name|guint32
parameter_list|,
name|guint32
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* High level image-manipulation functions */
end_comment

begin_function_decl
name|void
name|path_stroke
parameter_list|(
name|GimpPathTool
modifier|*
parameter_list|,
name|NPath
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_to_selection
parameter_list|(
name|GimpPathTool
modifier|*
parameter_list|,
name|NPath
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PATH_TOOL_H__ */
end_comment

end_unit

