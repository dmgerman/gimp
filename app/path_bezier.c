begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  *  * This file Copyright (C) 1999 Simon Budig  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"path_bezier.h"
end_include

begin_comment
comment|/*  * This function is to get a set of npoints different coordinates for  * the range from start to end (each in the range from 0 to 1 and  * start< end.  * returns the number of created coords. Make sure that the points-  * Array is allocated.  */
end_comment

begin_function
name|guint
DECL|function|path_bezier_get_points (PathTool * path_tool,PathSegment * segment,GdkPoint * points,guint npoints,gdouble start,gdouble end)
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
block|{
return|return
literal|0
return|;
block|}
end_function

begin_function
name|void
DECL|function|path_bezier_get_point (PathTool * path_tool,PathSegment * segment,gdouble position,gdouble * x,gdouble * y)
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
block|{
return|return;
block|}
end_function

begin_function
name|void
DECL|function|path_bezier_draw_handles (Tool * tool,PathSegment * segment)
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
block|{
return|return;
block|}
end_function

begin_function
name|void
DECL|function|path_bezier_draw_segment (Tool * tool,PathSegment * segment)
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
block|{
return|return;
block|}
end_function

begin_function
name|gdouble
DECL|function|path_bezier_on_segment (Tool * tool,PathSegment * segment,gint x,gint y,gint halfwidth,gint * distance)
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
block|{
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|void
DECL|function|path_bezier_drag_segment (PathTool * path_tool,PathSegment * segment,gdouble position,gint x,gint y)
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
block|{
return|return;
block|}
end_function

begin_function
name|gint
DECL|function|path_bezier_on_handles (PathTool * path_tool,PathSegment * segment,gint x,gint y,gint halfwidth)
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
block|{
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|path_bezier_drag_handles (PathTool * path_tool,PathSegment * segment,gint x,gint y,gint handle_id)
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
block|{
return|return;
block|}
end_function

begin_function
name|PathSegment
modifier|*
DECL|function|path_bezier_insert_anchor (PathTool * path_tool,PathSegment * segment,gdouble position)
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
block|{
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|path_bezier_update_segment (PathTool * path_tool,PathSegment * segment)
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
block|{
return|return;
block|}
end_function

begin_function
name|void
DECL|function|path_bezier_flip_segment (PathTool * path_tool,PathSegment * segment)
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
block|{
return|return;
block|}
end_function

begin_function
name|void
DECL|function|path_bezier_init_segment (PathTool * path_tool,PathSegment * segment)
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
block|{
return|return;
block|}
end_function

begin_function
name|void
DECL|function|path_bezier_cleanup_segment (PathTool * path_tool,PathSegment * segment)
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
block|{
return|return;
block|}
end_function

end_unit

