begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PATH_TOOLP_H__
end_ifndef

begin_define
DECL|macro|__PATH_TOOLP_H__
define|#
directive|define
name|__PATH_TOOLP_H__
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
DECL|macro|SEGMENT_ACTIVE
define|#
directive|define
name|SEGMENT_ACTIVE
value|1
end_define

begin_define
DECL|macro|PATH_TOOL_DRAG
define|#
directive|define
name|PATH_TOOL_DRAG
value|1
end_define

begin_define
DECL|macro|PATH_TOOL_REDRAW_ALL
define|#
directive|define
name|PATH_TOOL_REDRAW_ALL
value|1
end_define

begin_define
DECL|macro|PATH_TOOL_REDRAW_ACTIVE
define|#
directive|define
name|PATH_TOOL_REDRAW_ACTIVE
value|2
end_define

begin_define
DECL|macro|PATH_TOOL_REDRAW_HANDLES
define|#
directive|define
name|PATH_TOOL_REDRAW_HANDLES
value|4
end_define

begin_define
DECL|macro|SUBDIVIDE
define|#
directive|define
name|SUBDIVIDE
value|1000
end_define

begin_enum
DECL|enum|__anon2a0528e90103
DECL|enumerator|ON_ANCHOR
DECL|enumerator|ON_HANDLE
DECL|enumerator|ON_CURVE
DECL|enumerator|ON_CANVAS
enum|enum
block|{
name|ON_ANCHOR
block|,
name|ON_HANDLE
block|,
name|ON_CURVE
block|,
name|ON_CANVAS
block|}
enum|;
end_enum

begin_typedef
DECL|enum|__anon2a0528e90203
DECL|enumerator|SEGMENT_LINE
DECL|enumerator|SEGMENT_BEZIER
DECL|typedef|SegmentType
typedef|typedef
enum|enum
block|{
name|SEGMENT_LINE
block|,
name|SEGMENT_BEZIER
block|}
name|SegmentType
typedef|;
end_typedef

begin_typedef
DECL|typedef|PathSegment
typedef|typedef
name|struct
name|_path_segment
name|PathSegment
typedef|;
end_typedef

begin_struct
DECL|struct|_path_segment
struct|struct
name|_path_segment
block|{
DECL|member|type
name|SegmentType
name|type
decl_stmt|;
comment|/* What type of segment */
DECL|member|x
DECL|member|y
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/* location of starting-point in image space  */
DECL|member|flags
name|guint32
name|flags
decl_stmt|;
comment|/* Various Flags: Is the Segment active? */
DECL|member|next
name|PathSegment
modifier|*
name|next
decl_stmt|;
comment|/* Next Segment or NULL */
DECL|member|prev
name|PathSegment
modifier|*
name|prev
decl_stmt|;
comment|/* Previous Segment or NULL */
DECL|member|data
name|gpointer
name|data
decl_stmt|;
comment|/* Additional data, dependant of segment-type */
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|PathCurve
typedef|typedef
name|struct
name|_path_curve
name|PathCurve
typedef|;
end_typedef

begin_struct
DECL|struct|_path_curve
struct|struct
name|_path_curve
block|{
DECL|member|segments
name|PathSegment
modifier|*
name|segments
decl_stmt|;
comment|/* The segments of the curve */
DECL|member|cur_segment
name|PathSegment
modifier|*
name|cur_segment
decl_stmt|;
comment|/* the current segment */
DECL|member|next
name|PathCurve
modifier|*
name|next
decl_stmt|;
comment|/* Next Curve or NULL */
DECL|member|prev
name|PathCurve
modifier|*
name|prev
decl_stmt|;
comment|/* Previous Curve or NULL */
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|Path
typedef|typedef
name|struct
name|_path
name|Path
typedef|;
end_typedef

begin_struct
DECL|struct|_path
struct|struct
name|_path
block|{
DECL|member|curves
name|PathCurve
modifier|*
name|curves
decl_stmt|;
comment|/* the curves */
DECL|member|cur_curve
name|PathCurve
modifier|*
name|cur_curve
decl_stmt|;
comment|/* the current curve */
DECL|member|name
name|GString
modifier|*
name|name
decl_stmt|;
comment|/* the name of the path */
DECL|member|state
name|guint32
name|state
decl_stmt|;
comment|/* is the path locked? */
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|PathTool
typedef|typedef
name|struct
name|_path_tool
name|PathTool
typedef|;
end_typedef

begin_struct
DECL|struct|_path_tool
struct|struct
name|_path_tool
block|{
DECL|member|click_pos
name|gint
name|click_pos
decl_stmt|;
comment|/* where did the user click?         */
DECL|member|click_x
name|gint
name|click_x
decl_stmt|;
comment|/* X-coordinate of the click         */
DECL|member|click_y
name|gint
name|click_y
decl_stmt|;
comment|/* Y-coordinate of the click         */
DECL|member|click_halfwidth
name|gint
name|click_halfwidth
decl_stmt|;
DECL|member|click_modifier
name|guint
name|click_modifier
decl_stmt|;
comment|/* what modifiers were pressed?      */
DECL|member|click_path
name|Path
modifier|*
name|click_path
decl_stmt|;
comment|/* On which Path/Curve/Segment       */
DECL|member|click_curve
name|PathCurve
modifier|*
name|click_curve
decl_stmt|;
comment|/* was the click?                    */
DECL|member|click_segment
name|PathSegment
modifier|*
name|click_segment
decl_stmt|;
DECL|member|state
name|gint
name|state
decl_stmt|;
comment|/* state of tool                     */
DECL|member|draw
name|gint
name|draw
decl_stmt|;
comment|/* all or part                       */
DECL|member|core
name|DrawCore
modifier|*
name|core
decl_stmt|;
comment|/* Core drawing object               */
DECL|member|cur_path
name|Path
modifier|*
name|cur_path
decl_stmt|;
comment|/* the current active path           */
DECL|member|scanlines
name|GSList
modifier|*
modifier|*
name|scanlines
decl_stmt|;
comment|/* used in converting a path         */
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|PathTraverseFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|PathTraverseFunc
function_decl|)
parameter_list|(
name|Path
modifier|*
parameter_list|,
name|PathCurve
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|CurveTraverseFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|CurveTraverseFunc
function_decl|)
parameter_list|(
name|Path
modifier|*
parameter_list|,
name|PathCurve
modifier|*
parameter_list|,
name|PathSegment
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|SegmentTraverseFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|SegmentTraverseFunc
function_decl|)
parameter_list|(
name|Path
modifier|*
parameter_list|,
name|PathCurve
modifier|*
parameter_list|,
name|PathSegment
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/* typedef void (*SegmentTraverseFunc) (PathTool *, GdkPoint *, gint, gpointer);*/
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PATH_TOOLP_H__ */
end_comment

end_unit

