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

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|FIXME #include "gui/gui-types.h"
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"gui/gui-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpselectiontool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_RECTANGLE_TOOL
define|#
directive|define
name|GIMP_TYPE_RECTANGLE_TOOL
value|(gimp_rectangle_tool_get_type ())
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
DECL|macro|GIMP_RECTANGLE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_RECTANGLE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_RECTANGLE_TOOL, GimpRectangleToolClass))
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
DECL|macro|GIMP_RECTANGLE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_RECTANGLE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_RECTANGLE_TOOL, GimpRectangleToolClass))
end_define

begin_define
DECL|macro|GIMP_RECTANGLE_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_RECTANGLE_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_RECTANGLE_TOOL, GimpRectangleToolClass))
end_define

begin_comment
comment|/*  possible functions  */
end_comment

begin_enum
enum|enum
DECL|enum|__anon2add5fd40103
block|{
DECL|enumerator|RECT_CREATING
name|RECT_CREATING
block|,
DECL|enumerator|RECT_MOVING
name|RECT_MOVING
block|,
DECL|enumerator|RECT_RESIZING_LEFT
name|RECT_RESIZING_LEFT
block|,
DECL|enumerator|RECT_RESIZING_RIGHT
name|RECT_RESIZING_RIGHT
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
DECL|typedef|GimpRectangleToolClass
typedef|typedef
name|struct
name|_GimpRectangleToolClass
name|GimpRectangleToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpRectangleTool
struct|struct
name|_GimpRectangleTool
block|{
DECL|member|parent_instance
name|GimpSelectionTool
name|parent_instance
decl_stmt|;
DECL|member|controls
name|GtkWidget
modifier|*
name|controls
decl_stmt|;
DECL|member|dimensions_entry
name|GtkWidget
modifier|*
name|dimensions_entry
decl_stmt|;
DECL|member|startx
name|gint
name|startx
decl_stmt|;
comment|/*  starting x coord            */
DECL|member|starty
name|gint
name|starty
decl_stmt|;
comment|/*  starting y coord            */
DECL|member|lastx
name|gint
name|lastx
decl_stmt|;
comment|/*  previous x coord            */
DECL|member|lasty
name|gint
name|lasty
decl_stmt|;
comment|/*  previous y coord            */
DECL|member|x1
DECL|member|y1
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  upper left hand coordinate  */
DECL|member|x2
DECL|member|y2
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  lower right hand coords     */
DECL|member|function
name|guint
name|function
decl_stmt|;
comment|/*  moving or resizing          */
DECL|member|dx1
DECL|member|dy1
name|gint
name|dx1
decl_stmt|,
name|dy1
decl_stmt|;
comment|/*  display coords              */
DECL|member|dx2
DECL|member|dy2
name|gint
name|dx2
decl_stmt|,
name|dy2
decl_stmt|;
comment|/*                              */
DECL|member|dcw
DECL|member|dch
name|gint
name|dcw
decl_stmt|,
name|dch
decl_stmt|;
comment|/*  width and height of corners */
DECL|member|orig_vals
name|gdouble
name|orig_vals
index|[
literal|2
index|]
decl_stmt|;
DECL|member|size_vals
name|gdouble
name|size_vals
index|[
literal|2
index|]
decl_stmt|;
DECL|member|aspect_ratio
name|gdouble
name|aspect_ratio
decl_stmt|;
DECL|member|change_aspect_ratio
name|gboolean
name|change_aspect_ratio
decl_stmt|;
comment|/* Boolean for the rectangle_info_update function */
comment|/* aspect_ratio should not be changed whith   */
comment|/* rectangle_info_update when it is called from      */
comment|/* rectangle_aspect_changed, due to the inaccurate*/
comment|/* decimal precision                         */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpRectangleToolClass
struct|struct
name|_GimpRectangleToolClass
block|{
DECL|member|parent_class
name|GimpSelectionToolClass
name|parent_class
decl_stmt|;
comment|/*  virtual function  */
DECL|member|execute
name|void
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
name|gimp_rectangle_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_RECTANGLE_TOOL_H__  */
end_comment

end_unit

