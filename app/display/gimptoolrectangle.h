begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolrectangle.h  * Copyright (C) 2017 Michael Natterer<mitch@gimp.org>  *  * Based on GimpRectangleTool  * Copyright (C) 2007 Martin Nordholts  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_RECTANGLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_RECTANGLE_H__
define|#
directive|define
name|__GIMP_TOOL_RECTANGLE_H__
end_define

begin_include
include|#
directive|include
file|"gimptoolwidget.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bd3ecdc0103
block|{
DECL|enumerator|GIMP_TOOL_RECTANGLE_DEAD
name|GIMP_TOOL_RECTANGLE_DEAD
block|,
DECL|enumerator|GIMP_TOOL_RECTANGLE_CREATING
name|GIMP_TOOL_RECTANGLE_CREATING
block|,
DECL|enumerator|GIMP_TOOL_RECTANGLE_MOVING
name|GIMP_TOOL_RECTANGLE_MOVING
block|,
DECL|enumerator|GIMP_TOOL_RECTANGLE_RESIZING_UPPER_LEFT
name|GIMP_TOOL_RECTANGLE_RESIZING_UPPER_LEFT
block|,
DECL|enumerator|GIMP_TOOL_RECTANGLE_RESIZING_UPPER_RIGHT
name|GIMP_TOOL_RECTANGLE_RESIZING_UPPER_RIGHT
block|,
DECL|enumerator|GIMP_TOOL_RECTANGLE_RESIZING_LOWER_LEFT
name|GIMP_TOOL_RECTANGLE_RESIZING_LOWER_LEFT
block|,
DECL|enumerator|GIMP_TOOL_RECTANGLE_RESIZING_LOWER_RIGHT
name|GIMP_TOOL_RECTANGLE_RESIZING_LOWER_RIGHT
block|,
DECL|enumerator|GIMP_TOOL_RECTANGLE_RESIZING_LEFT
name|GIMP_TOOL_RECTANGLE_RESIZING_LEFT
block|,
DECL|enumerator|GIMP_TOOL_RECTANGLE_RESIZING_RIGHT
name|GIMP_TOOL_RECTANGLE_RESIZING_RIGHT
block|,
DECL|enumerator|GIMP_TOOL_RECTANGLE_RESIZING_TOP
name|GIMP_TOOL_RECTANGLE_RESIZING_TOP
block|,
DECL|enumerator|GIMP_TOOL_RECTANGLE_RESIZING_BOTTOM
name|GIMP_TOOL_RECTANGLE_RESIZING_BOTTOM
block|,
DECL|enumerator|GIMP_TOOL_RECTANGLE_AUTO_SHRINK
name|GIMP_TOOL_RECTANGLE_AUTO_SHRINK
block|,
DECL|enumerator|GIMP_TOOL_RECTANGLE_EXECUTING
name|GIMP_TOOL_RECTANGLE_EXECUTING
block|,
DECL|enumerator|GIMP_N_TOOL_RECTANGLE_FUNCTIONS
name|GIMP_N_TOOL_RECTANGLE_FUNCTIONS
DECL|typedef|GimpRectangleFunction
block|}
name|GimpRectangleFunction
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TOOL_RECTANGLE
define|#
directive|define
name|GIMP_TYPE_TOOL_RECTANGLE
value|(gimp_tool_rectangle_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_RECTANGLE (obj)
define|#
directive|define
name|GIMP_TOOL_RECTANGLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_RECTANGLE, GimpToolRectangle))
end_define

begin_define
DECL|macro|GIMP_TOOL_RECTANGLE_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_RECTANGLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_RECTANGLE, GimpToolRectangleClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_RECTANGLE (obj)
define|#
directive|define
name|GIMP_IS_TOOL_RECTANGLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_RECTANGLE))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_RECTANGLE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_RECTANGLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_RECTANGLE))
end_define

begin_define
DECL|macro|GIMP_TOOL_RECTANGLE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_RECTANGLE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_RECTANGLE, GimpToolRectangleClass))
end_define

begin_typedef
DECL|typedef|GimpToolRectangle
typedef|typedef
name|struct
name|_GimpToolRectangle
name|GimpToolRectangle
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolRectanglePrivate
typedef|typedef
name|struct
name|_GimpToolRectanglePrivate
name|GimpToolRectanglePrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolRectangleClass
typedef|typedef
name|struct
name|_GimpToolRectangleClass
name|GimpToolRectangleClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolRectangle
struct|struct
name|_GimpToolRectangle
block|{
DECL|member|parent_instance
name|GimpToolWidget
name|parent_instance
decl_stmt|;
DECL|member|private
name|GimpToolRectanglePrivate
modifier|*
name|private
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolRectangleClass
struct|struct
name|_GimpToolRectangleClass
block|{
DECL|member|parent_class
name|GimpToolWidgetClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|change_complete
name|gboolean
function_decl|(
modifier|*
name|change_complete
function_decl|)
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectangle
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_rectangle_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpToolWidget
modifier|*
name|gimp_tool_rectangle_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpRectangleFunction
name|gimp_tool_rectangle_get_function
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectangle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_rectangle_set_function
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectangle
parameter_list|,
name|GimpRectangleFunction
name|function
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_rectangle_set_constraint
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectangle
parameter_list|,
name|GimpRectangleConstraint
name|constraint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpRectangleConstraint
name|gimp_tool_rectangle_get_constraint
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectangle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_rectangle_get_public_rect
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectangle
parameter_list|,
name|gdouble
modifier|*
name|pub_x1
parameter_list|,
name|gdouble
modifier|*
name|pub_y1
parameter_list|,
name|gdouble
modifier|*
name|pub_x2
parameter_list|,
name|gdouble
modifier|*
name|pub_y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_rectangle_pending_size_set
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectangle
parameter_list|,
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|width_property
parameter_list|,
specifier|const
name|gchar
modifier|*
name|height_property
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_rectangle_constraint_size_set
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectangle
parameter_list|,
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|width_property
parameter_list|,
specifier|const
name|gchar
modifier|*
name|height_property
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_rectangle_rectangle_is_first
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectangle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_rectangle_rectangle_is_new
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectangle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_rectangle_point_in_rectangle
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectangle
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
name|gimp_tool_rectangle_frame_item
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectangle
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_rectangle_auto_shrink
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectrectangle
parameter_list|,
name|gboolean
name|shrink_merged
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TOOL_RECTANGLE_H__ */
end_comment

end_unit

