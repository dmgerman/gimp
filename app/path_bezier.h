begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  *  * This file Copyright (C) 1999 Simon Budig  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * This function is to get a set of npoints different coordinates for  * the range from start to end (each in the range from 0 to 1 and  * start< end.  * returns the number of created coords. Make sure that the points-  * Array is allocated.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PATH_BEZIER_H__
end_ifndef

begin_define
DECL|macro|__PATH_BEZIER_H__
define|#
directive|define
name|__PATH_BEZIER_H__
end_define

begin_include
include|#
directive|include
file|<gdk/gdk.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"path_toolP.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b046e580108
block|{
DECL|member|x1
name|gdouble
name|x1
decl_stmt|;
DECL|member|y1
name|gdouble
name|y1
decl_stmt|;
DECL|member|x2
name|gdouble
name|x2
decl_stmt|;
DECL|member|y2
name|gdouble
name|y2
decl_stmt|;
DECL|typedef|PathBezierData
block|}
name|PathBezierData
typedef|;
end_typedef

begin_function_decl
name|guint
name|path_bezier_get_points
parameter_list|(
name|PathTool
modifier|*
name|path_tool
parameter_list|,
name|PathSegment
modifier|*
name|segment
parameter_list|,
name|GdkPoint
modifier|*
name|points
parameter_list|,
name|guint
name|npoints
parameter_list|,
name|gdouble
name|start
parameter_list|,
name|gdouble
name|end
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_bezier_get_point
parameter_list|(
name|PathTool
modifier|*
name|path_tool
parameter_list|,
name|PathSegment
modifier|*
name|segment
parameter_list|,
name|gdouble
name|position
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_bezier_draw_handles
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|PathSegment
modifier|*
name|segment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_bezier_draw_segment
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|PathSegment
modifier|*
name|segment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|path_bezier_on_segment
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|PathSegment
modifier|*
name|segment
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|halfwidth
parameter_list|,
name|gint
modifier|*
name|distance
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_bezier_drag_segment
parameter_list|(
name|PathTool
modifier|*
name|path_tool
parameter_list|,
name|PathSegment
modifier|*
name|segment
parameter_list|,
name|gdouble
name|position
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|path_bezier_on_handles
parameter_list|(
name|PathTool
modifier|*
name|path_tool
parameter_list|,
name|PathSegment
modifier|*
name|segment
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|halfwidth
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_bezier_drag_handles
parameter_list|(
name|PathTool
modifier|*
name|path_tool
parameter_list|,
name|PathSegment
modifier|*
name|segment
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|handle_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PathSegment
modifier|*
name|path_bezier_insert_anchor
parameter_list|(
name|PathTool
modifier|*
name|path_tool
parameter_list|,
name|PathSegment
modifier|*
name|segment
parameter_list|,
name|gdouble
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_bezier_update_segment
parameter_list|(
name|PathTool
modifier|*
name|path_tool
parameter_list|,
name|PathSegment
modifier|*
name|segment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_bezier_flip_segment
parameter_list|(
name|PathTool
modifier|*
name|path_tool
parameter_list|,
name|PathSegment
modifier|*
name|segment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_bezier_init_segment
parameter_list|(
name|PathTool
modifier|*
name|path_tool
parameter_list|,
name|PathSegment
modifier|*
name|segment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_bezier_cleanup_segment
parameter_list|(
name|PathTool
modifier|*
name|path_tool
parameter_list|,
name|PathSegment
modifier|*
name|segment
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PATH_BEZIER_H__ */
end_comment

end_unit

