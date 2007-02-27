begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ba465df0103
block|{
DECL|enumerator|GIMP_RECTANGLE_TOOL_PROP_0
name|GIMP_RECTANGLE_TOOL_PROP_0
block|,
DECL|enumerator|GIMP_RECTANGLE_TOOL_PROP_X1
name|GIMP_RECTANGLE_TOOL_PROP_X1
block|,
DECL|enumerator|GIMP_RECTANGLE_TOOL_PROP_Y1
name|GIMP_RECTANGLE_TOOL_PROP_Y1
block|,
DECL|enumerator|GIMP_RECTANGLE_TOOL_PROP_X2
name|GIMP_RECTANGLE_TOOL_PROP_X2
block|,
DECL|enumerator|GIMP_RECTANGLE_TOOL_PROP_Y2
name|GIMP_RECTANGLE_TOOL_PROP_Y2
block|,
DECL|enumerator|GIMP_RECTANGLE_TOOL_PROP_CONSTRAINT
name|GIMP_RECTANGLE_TOOL_PROP_CONSTRAINT
block|,
DECL|enumerator|GIMP_RECTANGLE_TOOL_PROP_LAST
name|GIMP_RECTANGLE_TOOL_PROP_LAST
init|=
name|GIMP_RECTANGLE_TOOL_PROP_CONSTRAINT
DECL|typedef|GimpRectangleToolProp
block|}
name|GimpRectangleToolProp
typedef|;
end_typedef

begin_comment
comment|/*  possible functions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ba465df0203
block|{
DECL|enumerator|RECT_INACTIVE
name|RECT_INACTIVE
block|,
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
DECL|typedef|GimpRectangleFunction
block|}
name|GimpRectangleFunction
typedef|;
end_typedef

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

begin_define
DECL|macro|GIMP_RECTANGLE_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_RECTANGLE_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_RECTANGLE_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

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
DECL|member|cancel
name|void
function_decl|(
modifier|*
name|cancel
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rect_tool
parameter_list|)
function_decl|;
comment|/*  signals  */
DECL|member|rectangle_changed
name|gboolean
function_decl|(
modifier|*
name|rectangle_changed
function_decl|)
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rect_tool
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
name|display
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
name|display
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
name|GimpButtonReleaseType
name|release_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
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
name|display
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
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_active_modifier_key
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
name|display
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
name|gboolean
name|proximity
parameter_list|,
name|GimpDisplay
modifier|*
name|display
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
name|display
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_cancel
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rect_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_configure
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rectangle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_constraint
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rectangle
parameter_list|,
name|GimpRectangleConstraint
name|constraint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpRectangleFunction
name|gimp_rectangle_tool_get_function
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rectangle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_function
parameter_list|(
name|GimpRectangleTool
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
name|gimp_rectangle_tool_get_press_coords
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rectangle
parameter_list|,
name|gint
modifier|*
name|pressx_ptr
parameter_list|,
name|gint
modifier|*
name|pressy_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  convenience functions  */
end_comment

begin_function_decl
name|void
name|gimp_rectangle_tool_install_properties
parameter_list|(
name|GObjectClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_tool_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
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

