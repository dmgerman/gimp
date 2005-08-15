begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_RECTANGLE_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RECTANGLE_TOOL_H__
define|#
directive|define
name|__GIMP_RECTANGLE_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimptool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_RECTANGLE_TOOL
define|#
directive|define
name|GIMP_TYPE_RECTANGLE_TOOL
value|(gimp_rectangle_tool_interface_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_RECTANGLE_TOOL (obj)
define|#
directive|define
name|GIMP_IS_RECTANGLE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_RECTANGLE_TOOL))
end_define

begin_define
DECL|macro|GIMP_RECTANGLE_TOOL (obj)
define|#
directive|define
name|GIMP_RECTANGLE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_RECTANGLE_TOOL, GimpRectangleTool))
end_define

begin_define
DECL|macro|GIMP_RECTANGLE_TOOL_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_RECTANGLE_TOOL_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_RECTANGLE_TOOL, GimpRectangleToolInterface))
end_define

begin_comment
comment|/*  possible functions  */
end_comment

begin_enum
enum|enum
DECL|enum|__anon2bc2fed00103
block|{
DECL|enumerator|RECT_CREATING
name|RECT_CREATING
block|,
DECL|enumerator|RECT_MOVING
name|RECT_MOVING
block|,
DECL|enumerator|RECT_RESIZING_UPPER_LEFT
name|RECT_RESIZING_UPPER_LEFT
block|,
DECL|enumerator|RECT_RESIZING_UPPER_RIGHT
name|RECT_RESIZING_UPPER_RIGHT
block|,
DECL|enumerator|RECT_RESIZING_LOWER_LEFT
name|RECT_RESIZING_LOWER_LEFT
block|,
DECL|enumerator|RECT_RESIZING_LOWER_RIGHT
name|RECT_RESIZING_LOWER_RIGHT
block|,
DECL|enumerator|RECT_RESIZING_LEFT
name|RECT_RESIZING_LEFT
block|,
DECL|enumerator|RECT_RESIZING_RIGHT
name|RECT_RESIZING_RIGHT
block|,
DECL|enumerator|RECT_RESIZING_TOP
name|RECT_RESIZING_TOP
block|,
DECL|enumerator|RECT_RESIZING_BOTTOM
name|RECT_RESIZING_BOTTOM
block|,
DECL|enumerator|RECT_EXECUTING
name|RECT_EXECUTING
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpRectangleTool
typedef|typedef
name|struct
name|_GimpRectangleTool
name|GimpRectangleTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpRectangleToolInterface
typedef|typedef
name|struct
name|_GimpRectangleToolInterface
name|GimpRectangleToolInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpRectangleToolInterface
struct|struct
name|_GimpRectangleToolInterface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|set_controls
name|void
function_decl|(
modifier|*
name|set_controls
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|GtkWidget
modifier|*
name|controls
parameter_list|)
function_decl|;
DECL|member|get_controls
name|GtkWidget
modifier|*
function_decl|(
modifier|*
name|get_controls
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_entry
name|void
function_decl|(
modifier|*
name|set_entry
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|GtkWidget
modifier|*
name|entry
parameter_list|)
function_decl|;
DECL|member|get_entry
name|GtkWidget
modifier|*
function_decl|(
modifier|*
name|get_entry
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
comment|/*  starting coordinates  */
DECL|member|set_startx
name|void
function_decl|(
modifier|*
name|set_startx
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|startx
parameter_list|)
function_decl|;
DECL|member|get_startx
name|gint
function_decl|(
modifier|*
name|get_startx
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_starty
name|void
function_decl|(
modifier|*
name|set_starty
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|starty
parameter_list|)
function_decl|;
DECL|member|get_starty
name|gint
function_decl|(
modifier|*
name|get_starty
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
comment|/*  previous coordinates  */
DECL|member|set_lastx
name|void
function_decl|(
modifier|*
name|set_lastx
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|lastx
parameter_list|)
function_decl|;
DECL|member|get_lastx
name|gint
function_decl|(
modifier|*
name|get_lastx
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_lasty
name|void
function_decl|(
modifier|*
name|set_lasty
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|lasty
parameter_list|)
function_decl|;
DECL|member|get_lasty
name|gint
function_decl|(
modifier|*
name|get_lasty
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
comment|/*  button pressed coordinates  */
DECL|member|set_pressx
name|void
function_decl|(
modifier|*
name|set_pressx
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|pressx
parameter_list|)
function_decl|;
DECL|member|get_pressx
name|gint
function_decl|(
modifier|*
name|get_pressx
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_pressy
name|void
function_decl|(
modifier|*
name|set_pressy
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|pressy
parameter_list|)
function_decl|;
DECL|member|get_pressy
name|gint
function_decl|(
modifier|*
name|get_pressy
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
comment|/*  upper left hand coordinates  */
DECL|member|set_x1
name|void
function_decl|(
modifier|*
name|set_x1
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|x1
parameter_list|)
function_decl|;
DECL|member|get_x1
name|gint
function_decl|(
modifier|*
name|get_x1
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_y1
name|void
function_decl|(
modifier|*
name|set_y1
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|y1
parameter_list|)
function_decl|;
DECL|member|get_y1
name|gint
function_decl|(
modifier|*
name|get_y1
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
comment|/*  lower right hand coordinates  */
DECL|member|set_x2
name|void
function_decl|(
modifier|*
name|set_x2
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|x2
parameter_list|)
function_decl|;
DECL|member|get_x2
name|gint
function_decl|(
modifier|*
name|get_x2
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_y2
name|void
function_decl|(
modifier|*
name|set_y2
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|y2
parameter_list|)
function_decl|;
DECL|member|get_y2
name|gint
function_decl|(
modifier|*
name|get_y2
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_function
name|void
function_decl|(
modifier|*
name|set_function
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|guint
name|function
parameter_list|)
function_decl|;
DECL|member|get_function
name|guint
function_decl|(
modifier|*
name|get_function
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
comment|/*  display coords              */
DECL|member|set_dx1
name|void
function_decl|(
modifier|*
name|set_dx1
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|dx1
parameter_list|)
function_decl|;
DECL|member|get_dx1
name|gint
function_decl|(
modifier|*
name|get_dx1
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_dy1
name|void
function_decl|(
modifier|*
name|set_dy1
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|dy1
parameter_list|)
function_decl|;
DECL|member|get_dy1
name|gint
function_decl|(
modifier|*
name|get_dy1
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_dx2
name|void
function_decl|(
modifier|*
name|set_dx2
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|dx2
parameter_list|)
function_decl|;
DECL|member|get_dx2
name|gint
function_decl|(
modifier|*
name|get_dx2
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_dy2
name|void
function_decl|(
modifier|*
name|set_dy2
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|dy2
parameter_list|)
function_decl|;
DECL|member|get_dy2
name|gint
function_decl|(
modifier|*
name|get_dy2
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
comment|/*  width and height of edges   */
DECL|member|set_dcw
name|void
function_decl|(
modifier|*
name|set_dcw
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|dcw
parameter_list|)
function_decl|;
DECL|member|get_dcw
name|gint
function_decl|(
modifier|*
name|get_dcw
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_dch
name|void
function_decl|(
modifier|*
name|set_dch
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|dch
parameter_list|)
function_decl|;
DECL|member|get_dch
name|gint
function_decl|(
modifier|*
name|get_dch
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_origx
name|void
function_decl|(
modifier|*
name|set_origx
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gdouble
name|origx
parameter_list|)
function_decl|;
DECL|member|get_origx
name|gdouble
function_decl|(
modifier|*
name|get_origx
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_origy
name|void
function_decl|(
modifier|*
name|set_origy
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gdouble
name|origy
parameter_list|)
function_decl|;
DECL|member|get_origy
name|gdouble
function_decl|(
modifier|*
name|get_origy
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_sizew
name|void
function_decl|(
modifier|*
name|set_sizew
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gdouble
name|sizew
parameter_list|)
function_decl|;
DECL|member|get_sizew
name|gdouble
function_decl|(
modifier|*
name|get_sizew
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|set_sizeh
name|void
function_decl|(
modifier|*
name|set_sizeh
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gdouble
name|sizeh
parameter_list|)
function_decl|;
DECL|member|get_sizeh
name|gdouble
function_decl|(
modifier|*
name|get_sizeh
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|execute
name|gboolean
function_decl|(
modifier|*
name|execute
function_decl|)
parameter_list|(
name|GimpRectangleTool
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
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_rectangle_tool_interface_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_rectangle_tool_set_controls
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|GtkWidget
modifier|*
name|controls
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_rectangle_tool_get_controls
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_entry
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|GtkWidget
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_rectangle_tool_get_entry
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_startx
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|startx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_startx
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_starty
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|starty
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_starty
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_lastx
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|lastx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_lastx
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_lasty
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|lasty
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_lasty
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_pressx
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|pressx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_pressx
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_pressy
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|pressy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_pressy
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_x1
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|x1
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_x1
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_y1
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|y1
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_y1
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_x2
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|x2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_x2
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_y2
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_y2
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_function
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|guint
name|function
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint
name|gimp_rectangle_tool_get_function
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_dx1
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|dx1
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_dx1
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_dy1
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|dy1
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_dy1
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_dx2
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|dx2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_dx2
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_dy2
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|dy2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_dy2
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_dcw
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|dcw
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_dcw
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_dch
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gint
name|dch
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rectangle_tool_get_dch
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_origx
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gdouble
name|origx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_rectangle_tool_get_origx
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_origy
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gdouble
name|origy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_rectangle_tool_get_origy
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_sizew
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gdouble
name|sizew
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_rectangle_tool_get_sizew
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_sizeh
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|,
name|gdouble
name|sizeh
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_rectangle_tool_get_sizeh
parameter_list|(
name|GimpRectangleTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_constructor
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_rectangle_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_rectangle_tool_key_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_oper_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_rectangle_tool_execute
parameter_list|(
name|GimpRectangleTool
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_RECTANGLE_TOOL_H__  */
end_comment

end_unit

