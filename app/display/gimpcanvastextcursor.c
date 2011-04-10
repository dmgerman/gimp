begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvastextcursor.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvastextcursor.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-transform.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon274b40530103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_X
name|PROP_X
block|,
DECL|enumerator|PROP_Y
name|PROP_Y
block|,
DECL|enumerator|PROP_WIDTH
name|PROP_WIDTH
block|,
DECL|enumerator|PROP_HEIGHT
name|PROP_HEIGHT
block|,
DECL|enumerator|PROP_OVERWRITE
name|PROP_OVERWRITE
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasTextCursorPrivate
typedef|typedef
name|struct
name|_GimpCanvasTextCursorPrivate
name|GimpCanvasTextCursorPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasTextCursorPrivate
struct|struct
name|_GimpCanvasTextCursorPrivate
block|{
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|overwrite
name|gboolean
name|overwrite
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (text_cursor)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|text_cursor
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (text_cursor, \                                      GIMP_TYPE_CANVAS_TEXT_CURSOR, \                                      GimpCanvasTextCursorPrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_text_cursor_set_property
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
specifier|static
name|void
name|gimp_canvas_text_cursor_get_property
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

begin_function_decl
specifier|static
name|void
name|gimp_canvas_text_cursor_draw
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|cairo_region_t
modifier|*
name|gimp_canvas_text_cursor_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCanvasTextCursor,gimp_canvas_text_cursor,GIMP_TYPE_CANVAS_ITEM)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCanvasTextCursor
argument_list|,
argument|gimp_canvas_text_cursor
argument_list|,
argument|GIMP_TYPE_CANVAS_ITEM
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_text_cursor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_text_cursor_class_init
parameter_list|(
name|GimpCanvasTextCursorClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpCanvasItemClass
modifier|*
name|item_class
init|=
name|GIMP_CANVAS_ITEM_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_canvas_text_cursor_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_text_cursor_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_text_cursor_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_text_cursor_get_extents
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_X
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"x"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_Y
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"y"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_WIDTH
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"width"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_HEIGHT
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"height"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_OVERWRITE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"overwrite"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpCanvasTextCursorPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_text_cursor_init (GimpCanvasTextCursor * text_cursor)
name|gimp_canvas_text_cursor_init
parameter_list|(
name|GimpCanvasTextCursor
modifier|*
name|text_cursor
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_text_cursor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_text_cursor_set_property
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
block|{
name|GimpCanvasTextCursorPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_X
case|:
name|private
operator|->
name|x
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_Y
case|:
name|private
operator|->
name|y
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WIDTH
case|:
name|private
operator|->
name|width
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HEIGHT
case|:
name|private
operator|->
name|height
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OVERWRITE
case|:
name|private
operator|->
name|overwrite
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_text_cursor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_text_cursor_get_property
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
block|{
name|GimpCanvasTextCursorPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_X
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_Y
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|y
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WIDTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HEIGHT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|height
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OVERWRITE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|overwrite
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_text_cursor_transform (GimpCanvasItem * item,GimpDisplayShell * shell,gdouble * x,gdouble * y,gdouble * w,gdouble * h)
name|gimp_canvas_text_cursor_transform
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|,
name|gdouble
modifier|*
name|w
parameter_list|,
name|gdouble
modifier|*
name|h
parameter_list|)
block|{
name|GimpCanvasTextCursorPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|MIN
argument_list|(
name|private
operator|->
name|x
argument_list|,
name|private
operator|->
name|x
operator|+
name|private
operator|->
name|width
argument_list|)
argument_list|,
name|MIN
argument_list|(
name|private
operator|->
name|y
argument_list|,
name|private
operator|->
name|y
operator|+
name|private
operator|->
name|height
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|MAX
argument_list|(
name|private
operator|->
name|x
argument_list|,
name|private
operator|->
name|x
operator|+
name|private
operator|->
name|width
argument_list|)
argument_list|,
name|MAX
argument_list|(
name|private
operator|->
name|y
argument_list|,
name|private
operator|->
name|y
operator|+
name|private
operator|->
name|height
argument_list|)
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
operator|*
name|w
operator|-=
operator|*
name|x
expr_stmt|;
operator|*
name|h
operator|-=
operator|*
name|y
expr_stmt|;
operator|*
name|x
operator|=
name|floor
argument_list|(
operator|*
name|x
argument_list|)
operator|+
literal|0.5
expr_stmt|;
operator|*
name|y
operator|=
name|floor
argument_list|(
operator|*
name|y
argument_list|)
operator|+
literal|0.5
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|overwrite
condition|)
block|{
operator|*
name|w
operator|=
name|ceil
argument_list|(
operator|*
name|w
argument_list|)
operator|-
literal|1.0
expr_stmt|;
operator|*
name|h
operator|=
name|ceil
argument_list|(
operator|*
name|h
argument_list|)
operator|-
literal|1.0
expr_stmt|;
block|}
else|else
block|{
operator|*
name|w
operator|=
literal|0
expr_stmt|;
operator|*
name|h
operator|=
name|ceil
argument_list|(
operator|*
name|h
argument_list|)
operator|-
literal|1.0
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_text_cursor_draw (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_text_cursor_draw
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|GimpCanvasTextCursorPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdouble
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gimp_canvas_text_cursor_transform
argument_list|(
name|item
argument_list|,
name|shell
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|overwrite
condition|)
block|{
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
operator|+
name|h
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
operator|-
literal|3.0
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
literal|3.0
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
operator|-
literal|3.0
argument_list|,
name|y
operator|+
name|h
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
literal|3.0
argument_list|,
name|y
operator|+
name|h
argument_list|)
expr_stmt|;
block|}
name|_gimp_canvas_item_stroke
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|cairo_region_t
modifier|*
DECL|function|gimp_canvas_text_cursor_get_extents (GimpCanvasItem * item,GimpDisplayShell * shell)
name|gimp_canvas_text_cursor_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpCanvasTextCursorPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|cairo_rectangle_int_t
name|rectangle
decl_stmt|;
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdouble
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gimp_canvas_text_cursor_transform
argument_list|(
name|item
argument_list|,
name|shell
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|overwrite
condition|)
block|{
name|rectangle
operator|.
name|x
operator|=
name|floor
argument_list|(
name|x
operator|-
literal|1.5
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|y
operator|=
name|floor
argument_list|(
name|y
operator|-
literal|1.5
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|width
operator|=
name|ceil
argument_list|(
name|w
operator|+
literal|3.0
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|height
operator|=
name|ceil
argument_list|(
name|h
operator|+
literal|3.0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|rectangle
operator|.
name|x
operator|=
name|floor
argument_list|(
name|x
operator|-
literal|4.5
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|y
operator|=
name|floor
argument_list|(
name|y
operator|-
literal|1.5
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|width
operator|=
name|ceil
argument_list|(
literal|9.0
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|height
operator|=
name|ceil
argument_list|(
name|h
operator|+
literal|3.0
argument_list|)
expr_stmt|;
block|}
return|return
name|cairo_region_create_rectangle
argument_list|(
operator|&
name|rectangle
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_canvas_text_cursor_new (GimpDisplayShell * shell,PangoRectangle * cursor,gboolean overwrite)
name|gimp_canvas_text_cursor_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|PangoRectangle
modifier|*
name|cursor
parameter_list|,
name|gboolean
name|overwrite
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|cursor
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CANVAS_TEXT_CURSOR
argument_list|,
literal|"shell"
argument_list|,
name|shell
argument_list|,
literal|"x"
argument_list|,
name|cursor
operator|->
name|x
argument_list|,
literal|"y"
argument_list|,
name|cursor
operator|->
name|y
argument_list|,
literal|"width"
argument_list|,
name|cursor
operator|->
name|width
argument_list|,
literal|"height"
argument_list|,
name|cursor
operator|->
name|height
argument_list|,
literal|"overwrite"
argument_list|,
name|overwrite
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

