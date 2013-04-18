begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvascorner.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpcanvascorner.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29029fbe0103
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
DECL|enumerator|PROP_ANCHOR
name|PROP_ANCHOR
block|,
DECL|enumerator|PROP_CORNER_WIDTH
name|PROP_CORNER_WIDTH
block|,
DECL|enumerator|PROP_CORNER_HEIGHT
name|PROP_CORNER_HEIGHT
block|,
DECL|enumerator|PROP_OUTSIDE
name|PROP_OUTSIDE
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasCornerPrivate
typedef|typedef
name|struct
name|_GimpCanvasCornerPrivate
name|GimpCanvasCornerPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasCornerPrivate
struct|struct
name|_GimpCanvasCornerPrivate
block|{
DECL|member|x
name|gdouble
name|x
decl_stmt|;
DECL|member|y
name|gdouble
name|y
decl_stmt|;
DECL|member|width
name|gdouble
name|width
decl_stmt|;
DECL|member|height
name|gdouble
name|height
decl_stmt|;
DECL|member|anchor
name|GimpHandleAnchor
name|anchor
decl_stmt|;
DECL|member|corner_width
name|gint
name|corner_width
decl_stmt|;
DECL|member|corner_height
name|gint
name|corner_height
decl_stmt|;
DECL|member|outside
name|gboolean
name|outside
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (corner)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|corner
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (corner, \                                      GIMP_TYPE_CANVAS_CORNER, \                                      GimpCanvasCornerPrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_corner_set_property
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
name|gimp_canvas_corner_get_property
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
name|gimp_canvas_corner_draw
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
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
name|gimp_canvas_corner_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCanvasCorner,gimp_canvas_corner,GIMP_TYPE_CANVAS_ITEM)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCanvasCorner
argument_list|,
argument|gimp_canvas_corner
argument_list|,
argument|GIMP_TYPE_CANVAS_ITEM
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_corner_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_corner_class_init
parameter_list|(
name|GimpCanvasCornerClass
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
name|gimp_canvas_corner_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_corner_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_corner_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_corner_get_extents
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_X
argument_list|,
name|g_param_spec_double
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
name|g_param_spec_double
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
name|g_param_spec_double
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
name|g_param_spec_double
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
name|PROP_ANCHOR
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"anchor"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_HANDLE_ANCHOR
argument_list|,
name|GIMP_HANDLE_ANCHOR_CENTER
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CORNER_WIDTH
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"corner-width"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|3
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|3
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CORNER_HEIGHT
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"corner-height"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|3
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|3
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_OUTSIDE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"outside"
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
name|GimpCanvasCornerPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_corner_init (GimpCanvasCorner * corner)
name|gimp_canvas_corner_init
parameter_list|(
name|GimpCanvasCorner
modifier|*
name|corner
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_corner_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_corner_set_property
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
name|GimpCanvasCornerPrivate
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
name|g_value_get_double
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
name|g_value_get_double
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
name|g_value_get_double
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
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ANCHOR
case|:
name|private
operator|->
name|anchor
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CORNER_WIDTH
case|:
name|private
operator|->
name|corner_width
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CORNER_HEIGHT
case|:
name|private
operator|->
name|corner_height
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OUTSIDE
case|:
name|private
operator|->
name|outside
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
DECL|function|gimp_canvas_corner_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_corner_get_property
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
name|GimpCanvasCornerPrivate
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
name|g_value_set_double
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
name|g_value_set_double
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
name|g_value_set_double
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
name|g_value_set_double
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
name|PROP_ANCHOR
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|anchor
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CORNER_WIDTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|corner_width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CORNER_HEIGHT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|corner_height
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OUTSIDE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|outside
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
DECL|function|gimp_canvas_corner_transform (GimpCanvasItem * item,gdouble * x,gdouble * y,gdouble * w,gdouble * h)
name|gimp_canvas_corner_transform
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
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
name|GimpCanvasCornerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gdouble
name|rx
decl_stmt|,
name|ry
decl_stmt|;
name|gdouble
name|rw
decl_stmt|,
name|rh
decl_stmt|;
name|gint
name|top_and_bottom_handle_x_offset
decl_stmt|;
name|gint
name|left_and_right_handle_y_offset
decl_stmt|;
name|gimp_canvas_item_transform_xy_f
argument_list|(
name|item
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
operator|&
name|rx
argument_list|,
operator|&
name|ry
argument_list|)
expr_stmt|;
name|gimp_canvas_item_transform_xy_f
argument_list|(
name|item
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
operator|&
name|rw
argument_list|,
operator|&
name|rh
argument_list|)
expr_stmt|;
name|rw
operator|-=
name|rx
expr_stmt|;
name|rh
operator|-=
name|ry
expr_stmt|;
name|rx
operator|=
name|floor
argument_list|(
name|rx
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|ry
operator|=
name|floor
argument_list|(
name|ry
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|rw
operator|=
name|ceil
argument_list|(
name|rw
argument_list|)
operator|-
literal|1.0
expr_stmt|;
name|rh
operator|=
name|ceil
argument_list|(
name|rh
argument_list|)
operator|-
literal|1.0
expr_stmt|;
name|top_and_bottom_handle_x_offset
operator|=
operator|(
name|rw
operator|-
name|private
operator|->
name|corner_width
operator|)
operator|/
literal|2
expr_stmt|;
name|left_and_right_handle_y_offset
operator|=
operator|(
name|rh
operator|-
name|private
operator|->
name|corner_height
operator|)
operator|/
literal|2
expr_stmt|;
operator|*
name|w
operator|=
name|private
operator|->
name|corner_width
expr_stmt|;
operator|*
name|h
operator|=
name|private
operator|->
name|corner_height
expr_stmt|;
switch|switch
condition|(
name|private
operator|->
name|anchor
condition|)
block|{
case|case
name|GIMP_HANDLE_ANCHOR_CENTER
case|:
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_NORTH_WEST
case|:
if|if
condition|(
name|private
operator|->
name|outside
condition|)
block|{
operator|*
name|x
operator|=
name|rx
operator|-
name|private
operator|->
name|corner_width
expr_stmt|;
operator|*
name|y
operator|=
name|ry
operator|-
name|private
operator|->
name|corner_height
expr_stmt|;
block|}
else|else
block|{
operator|*
name|x
operator|=
name|rx
expr_stmt|;
operator|*
name|y
operator|=
name|ry
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_NORTH_EAST
case|:
if|if
condition|(
name|private
operator|->
name|outside
condition|)
block|{
operator|*
name|x
operator|=
name|rx
operator|+
name|rw
expr_stmt|;
operator|*
name|y
operator|=
name|ry
operator|-
name|private
operator|->
name|corner_height
expr_stmt|;
block|}
else|else
block|{
operator|*
name|x
operator|=
name|rx
operator|+
name|rw
operator|-
name|private
operator|->
name|corner_width
expr_stmt|;
operator|*
name|y
operator|=
name|ry
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_SOUTH_WEST
case|:
if|if
condition|(
name|private
operator|->
name|outside
condition|)
block|{
operator|*
name|x
operator|=
name|rx
operator|-
name|private
operator|->
name|corner_width
expr_stmt|;
operator|*
name|y
operator|=
name|ry
operator|+
name|rh
expr_stmt|;
block|}
else|else
block|{
operator|*
name|x
operator|=
name|rx
expr_stmt|;
operator|*
name|y
operator|=
name|ry
operator|+
name|rh
operator|-
name|private
operator|->
name|corner_height
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_SOUTH_EAST
case|:
if|if
condition|(
name|private
operator|->
name|outside
condition|)
block|{
operator|*
name|x
operator|=
name|rx
operator|+
name|rw
expr_stmt|;
operator|*
name|y
operator|=
name|ry
operator|+
name|rh
expr_stmt|;
block|}
else|else
block|{
operator|*
name|x
operator|=
name|rx
operator|+
name|rw
operator|-
name|private
operator|->
name|corner_width
expr_stmt|;
operator|*
name|y
operator|=
name|ry
operator|+
name|rh
operator|-
name|private
operator|->
name|corner_height
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_NORTH
case|:
if|if
condition|(
name|private
operator|->
name|outside
condition|)
block|{
operator|*
name|x
operator|=
name|rx
expr_stmt|;
operator|*
name|y
operator|=
name|ry
operator|-
name|private
operator|->
name|corner_height
expr_stmt|;
operator|*
name|w
operator|=
name|rw
expr_stmt|;
block|}
else|else
block|{
operator|*
name|x
operator|=
name|rx
operator|+
name|top_and_bottom_handle_x_offset
expr_stmt|;
operator|*
name|y
operator|=
name|ry
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_SOUTH
case|:
if|if
condition|(
name|private
operator|->
name|outside
condition|)
block|{
operator|*
name|x
operator|=
name|rx
expr_stmt|;
operator|*
name|y
operator|=
name|ry
operator|+
name|rh
expr_stmt|;
operator|*
name|w
operator|=
name|rw
expr_stmt|;
block|}
else|else
block|{
operator|*
name|x
operator|=
name|rx
operator|+
name|top_and_bottom_handle_x_offset
expr_stmt|;
operator|*
name|y
operator|=
name|ry
operator|+
name|rh
operator|-
name|private
operator|->
name|corner_height
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_WEST
case|:
if|if
condition|(
name|private
operator|->
name|outside
condition|)
block|{
operator|*
name|x
operator|=
name|rx
operator|-
name|private
operator|->
name|corner_width
expr_stmt|;
operator|*
name|y
operator|=
name|ry
expr_stmt|;
operator|*
name|h
operator|=
name|rh
expr_stmt|;
block|}
else|else
block|{
operator|*
name|x
operator|=
name|rx
expr_stmt|;
operator|*
name|y
operator|=
name|ry
operator|+
name|left_and_right_handle_y_offset
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_EAST
case|:
if|if
condition|(
name|private
operator|->
name|outside
condition|)
block|{
operator|*
name|x
operator|=
name|rx
operator|+
name|rw
expr_stmt|;
operator|*
name|y
operator|=
name|ry
expr_stmt|;
operator|*
name|h
operator|=
name|rh
expr_stmt|;
block|}
else|else
block|{
operator|*
name|x
operator|=
name|rx
operator|+
name|rw
operator|-
name|private
operator|->
name|corner_width
expr_stmt|;
operator|*
name|y
operator|=
name|ry
operator|+
name|left_and_right_handle_y_offset
expr_stmt|;
block|}
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_corner_draw (GimpCanvasItem * item,cairo_t * cr)
name|gimp_canvas_corner_draw
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
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
name|gimp_canvas_corner_transform
argument_list|(
name|item
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
DECL|function|gimp_canvas_corner_get_extents (GimpCanvasItem * item)
name|gimp_canvas_corner_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
block|{
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
name|gimp_canvas_corner_transform
argument_list|(
name|item
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
DECL|function|gimp_canvas_corner_new (GimpDisplayShell * shell,gdouble x,gdouble y,gdouble width,gdouble height,GimpHandleAnchor anchor,gint corner_width,gint corner_height,gboolean outside)
name|gimp_canvas_corner_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|,
name|GimpHandleAnchor
name|anchor
parameter_list|,
name|gint
name|corner_width
parameter_list|,
name|gint
name|corner_height
parameter_list|,
name|gboolean
name|outside
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
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CANVAS_CORNER
argument_list|,
literal|"shell"
argument_list|,
name|shell
argument_list|,
literal|"x"
argument_list|,
name|x
argument_list|,
literal|"y"
argument_list|,
name|y
argument_list|,
literal|"width"
argument_list|,
name|width
argument_list|,
literal|"height"
argument_list|,
name|height
argument_list|,
literal|"anchor"
argument_list|,
name|anchor
argument_list|,
literal|"corner-width"
argument_list|,
name|corner_width
argument_list|,
literal|"corner-height"
argument_list|,
name|corner_height
argument_list|,
literal|"outside"
argument_list|,
name|outside
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

