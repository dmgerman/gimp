begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvashandle.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimp-cairo.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvashandle.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasitem-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon27fafa6e0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TYPE
name|PROP_TYPE
block|,
DECL|enumerator|PROP_ANCHOR
name|PROP_ANCHOR
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
DECL|enumerator|PROP_START_ANGLE
name|PROP_START_ANGLE
block|,
DECL|enumerator|PROP_SLICE_ANGLE
name|PROP_SLICE_ANGLE
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasHandlePrivate
typedef|typedef
name|struct
name|_GimpCanvasHandlePrivate
name|GimpCanvasHandlePrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasHandlePrivate
struct|struct
name|_GimpCanvasHandlePrivate
block|{
DECL|member|type
name|GimpHandleType
name|type
decl_stmt|;
DECL|member|anchor
name|GimpHandleAnchor
name|anchor
decl_stmt|;
DECL|member|x
name|gdouble
name|x
decl_stmt|;
DECL|member|y
name|gdouble
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
DECL|member|start_angle
name|gdouble
name|start_angle
decl_stmt|;
DECL|member|slice_angle
name|gdouble
name|slice_angle
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (handle)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|handle
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (handle, \                                      GIMP_TYPE_CANVAS_HANDLE, \                                      GimpCanvasHandlePrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_handle_set_property
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
name|gimp_canvas_handle_get_property
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
name|gimp_canvas_handle_draw
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
name|gimp_canvas_handle_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_canvas_handle_hit
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCanvasHandle,gimp_canvas_handle,GIMP_TYPE_CANVAS_ITEM)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCanvasHandle
argument_list|,
argument|gimp_canvas_handle
argument_list|,
argument|GIMP_TYPE_CANVAS_ITEM
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_handle_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_handle_class_init
parameter_list|(
name|GimpCanvasHandleClass
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
name|gimp_canvas_handle_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_handle_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_handle_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_handle_get_extents
expr_stmt|;
name|item_class
operator|->
name|hit
operator|=
name|gimp_canvas_handle_hit
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_TYPE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"type"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_HANDLE_TYPE
argument_list|,
name|GIMP_HANDLE_CROSS
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
name|g_param_spec_int
argument_list|(
literal|"width"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|3
argument_list|,
literal|1001
argument_list|,
literal|7
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
literal|3
argument_list|,
literal|1001
argument_list|,
literal|7
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_START_ANGLE
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"start-angle"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1000
argument_list|,
literal|1000
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
name|PROP_SLICE_ANGLE
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"slice-angle"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1000
argument_list|,
literal|1000
argument_list|,
literal|2
operator|*
name|G_PI
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
name|GimpCanvasHandlePrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_handle_init (GimpCanvasHandle * handle)
name|gimp_canvas_handle_init
parameter_list|(
name|GimpCanvasHandle
modifier|*
name|handle
parameter_list|)
block|{
name|GimpCanvasHandlePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|handle
argument_list|)
decl_stmt|;
name|gimp_canvas_item_set_line_cap
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|handle
argument_list|)
argument_list|,
name|CAIRO_LINE_CAP_SQUARE
argument_list|)
expr_stmt|;
name|private
operator|->
name|start_angle
operator|=
literal|0.0
expr_stmt|;
name|private
operator|->
name|slice_angle
operator|=
literal|2.0
operator|*
name|G_PI
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_handle_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_handle_set_property
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
name|GimpCanvasHandlePrivate
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
name|PROP_TYPE
case|:
name|private
operator|->
name|type
operator|=
name|g_value_get_enum
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
name|PROP_START_ANGLE
case|:
name|private
operator|->
name|start_angle
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SLICE_ANGLE
case|:
name|private
operator|->
name|slice_angle
operator|=
name|g_value_get_double
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
DECL|function|gimp_canvas_handle_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_handle_get_property
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
name|GimpCanvasHandlePrivate
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
name|PROP_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|type
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
name|PROP_START_ANGLE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|start_angle
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SLICE_ANGLE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|slice_angle
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
DECL|function|gimp_canvas_handle_transform (GimpCanvasItem * item,gdouble * x,gdouble * y)
name|gimp_canvas_handle_transform
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
parameter_list|)
block|{
name|GimpCanvasHandlePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gimp_canvas_item_transform_xy_f
argument_list|(
name|item
argument_list|,
name|private
operator|->
name|x
argument_list|,
name|private
operator|->
name|y
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|private
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_HANDLE_SQUARE
case|:
case|case
name|GIMP_HANDLE_FILLED_SQUARE
case|:
name|gimp_canvas_item_shift_to_north_west
argument_list|(
name|private
operator|->
name|anchor
argument_list|,
operator|*
name|x
argument_list|,
operator|*
name|y
argument_list|,
name|private
operator|->
name|width
argument_list|,
name|private
operator|->
name|height
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_CIRCLE
case|:
case|case
name|GIMP_HANDLE_FILLED_CIRCLE
case|:
case|case
name|GIMP_HANDLE_CROSS
case|:
case|case
name|GIMP_HANDLE_DIAMOND
case|:
case|case
name|GIMP_HANDLE_FILLED_DIAMOND
case|:
name|gimp_canvas_item_shift_to_center
argument_list|(
name|private
operator|->
name|anchor
argument_list|,
operator|*
name|x
argument_list|,
operator|*
name|y
argument_list|,
name|private
operator|->
name|width
argument_list|,
name|private
operator|->
name|height
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_handle_draw (GimpCanvasItem * item,cairo_t * cr)
name|gimp_canvas_handle_draw
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
name|GimpCanvasHandlePrivate
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
decl_stmt|,
name|tx
decl_stmt|,
name|ty
decl_stmt|;
name|gimp_canvas_handle_transform
argument_list|(
name|item
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|gimp_canvas_item_transform_xy_f
argument_list|(
name|item
argument_list|,
name|private
operator|->
name|x
argument_list|,
name|private
operator|->
name|y
argument_list|,
operator|&
name|tx
argument_list|,
operator|&
name|ty
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|private
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_HANDLE_SQUARE
case|:
case|case
name|GIMP_HANDLE_FILLED_SQUARE
case|:
case|case
name|GIMP_HANDLE_DIAMOND
case|:
case|case
name|GIMP_HANDLE_FILLED_DIAMOND
case|:
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|tx
argument_list|,
name|ty
argument_list|)
expr_stmt|;
name|cairo_rotate
argument_list|(
name|cr
argument_list|,
name|private
operator|->
name|start_angle
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
operator|-
name|tx
argument_list|,
operator|-
name|ty
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|private
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_HANDLE_SQUARE
case|:
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|private
operator|->
name|width
operator|-
literal|1.0
argument_list|,
name|private
operator|->
name|height
operator|-
literal|1.0
argument_list|)
expr_stmt|;
name|_gimp_canvas_item_stroke
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_FILLED_SQUARE
case|:
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|x
operator|-
literal|0.5
argument_list|,
name|y
operator|-
literal|0.5
argument_list|,
name|private
operator|->
name|width
argument_list|,
name|private
operator|->
name|height
argument_list|)
expr_stmt|;
name|_gimp_canvas_item_fill
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_DIAMOND
case|:
case|case
name|GIMP_HANDLE_FILLED_DIAMOND
case|:
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
operator|-
operator|(
name|gdouble
operator|)
name|private
operator|->
name|height
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
operator|(
name|gdouble
operator|)
name|private
operator|->
name|width
operator|/
literal|2.0
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
operator|(
name|gdouble
operator|)
name|private
operator|->
name|height
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|-
operator|(
name|gdouble
operator|)
name|private
operator|->
name|width
operator|/
literal|2.0
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
operator|-
operator|(
name|gdouble
operator|)
name|private
operator|->
name|height
operator|/
literal|2.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|type
operator|==
name|GIMP_HANDLE_DIAMOND
condition|)
name|_gimp_canvas_item_stroke
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
else|else
name|_gimp_canvas_item_fill
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
block|}
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_CIRCLE
case|:
name|gimp_cairo_add_arc
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|private
operator|->
name|width
operator|/
literal|2
argument_list|,
name|private
operator|->
name|start_angle
argument_list|,
name|private
operator|->
name|slice_angle
argument_list|)
expr_stmt|;
name|_gimp_canvas_item_stroke
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_FILLED_CIRCLE
case|:
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gimp_cairo_add_arc
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|(
name|gdouble
operator|)
name|private
operator|->
name|width
operator|/
literal|2.0
argument_list|,
name|private
operator|->
name|start_angle
argument_list|,
name|private
operator|->
name|slice_angle
argument_list|)
expr_stmt|;
name|_gimp_canvas_item_fill
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_CROSS
case|:
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
operator|-
name|private
operator|->
name|width
operator|/
literal|2
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
name|private
operator|->
name|width
operator|/
literal|2
operator|-
literal|0.5
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
operator|-
name|private
operator|->
name|height
operator|/
literal|2
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
name|private
operator|->
name|height
operator|/
literal|2
operator|-
literal|0.5
argument_list|)
expr_stmt|;
name|_gimp_canvas_item_stroke
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|cairo_region_t
modifier|*
DECL|function|gimp_canvas_handle_get_extents (GimpCanvasItem * item)
name|gimp_canvas_handle_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
block|{
name|GimpCanvasHandlePrivate
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
name|gimp_canvas_handle_transform
argument_list|(
name|item
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|private
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_HANDLE_SQUARE
case|:
case|case
name|GIMP_HANDLE_FILLED_SQUARE
case|:
name|w
operator|=
name|private
operator|->
name|width
operator|*
operator|(
name|sqrt
argument_list|(
literal|2
argument_list|)
operator|-
literal|1
operator|)
operator|/
literal|2
expr_stmt|;
name|h
operator|=
name|private
operator|->
name|height
operator|*
operator|(
name|sqrt
argument_list|(
literal|2
argument_list|)
operator|-
literal|1
operator|)
operator|/
literal|2
expr_stmt|;
name|rectangle
operator|.
name|x
operator|=
name|x
operator|-
literal|1.5
operator|-
name|w
expr_stmt|;
name|rectangle
operator|.
name|y
operator|=
name|y
operator|-
literal|1.5
operator|-
name|h
expr_stmt|;
name|rectangle
operator|.
name|width
operator|=
name|private
operator|->
name|width
operator|+
literal|3.0
operator|+
name|w
operator|*
literal|2
expr_stmt|;
name|rectangle
operator|.
name|height
operator|=
name|private
operator|->
name|height
operator|+
literal|3.0
operator|+
name|h
operator|*
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_CIRCLE
case|:
case|case
name|GIMP_HANDLE_FILLED_CIRCLE
case|:
case|case
name|GIMP_HANDLE_CROSS
case|:
case|case
name|GIMP_HANDLE_DIAMOND
case|:
case|case
name|GIMP_HANDLE_FILLED_DIAMOND
case|:
name|rectangle
operator|.
name|x
operator|=
name|x
operator|-
name|private
operator|->
name|width
operator|/
literal|2
operator|-
literal|2.0
expr_stmt|;
name|rectangle
operator|.
name|y
operator|=
name|y
operator|-
name|private
operator|->
name|height
operator|/
literal|2
operator|-
literal|2.0
expr_stmt|;
name|rectangle
operator|.
name|width
operator|=
name|private
operator|->
name|width
operator|+
literal|4.0
expr_stmt|;
name|rectangle
operator|.
name|height
operator|=
name|private
operator|->
name|height
operator|+
literal|4.0
expr_stmt|;
break|break;
default|default:
break|break;
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
specifier|static
name|gboolean
DECL|function|gimp_canvas_handle_hit (GimpCanvasItem * item,gdouble x,gdouble y)
name|gimp_canvas_handle_hit
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|GimpCanvasHandlePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gdouble
name|handle_tx
decl_stmt|,
name|handle_ty
decl_stmt|;
name|gdouble
name|mx
decl_stmt|,
name|my
decl_stmt|,
name|tx
decl_stmt|,
name|ty
decl_stmt|,
name|mmx
decl_stmt|,
name|mmy
decl_stmt|;
name|gdouble
name|diamond_offset_x
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|diamond_offset_y
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|angle
init|=
operator|-
name|private
operator|->
name|start_angle
decl_stmt|;
name|gimp_canvas_handle_transform
argument_list|(
name|item
argument_list|,
operator|&
name|handle_tx
argument_list|,
operator|&
name|handle_ty
argument_list|)
expr_stmt|;
name|gimp_canvas_item_transform_xy_f
argument_list|(
name|item
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|mx
argument_list|,
operator|&
name|my
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|private
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_HANDLE_DIAMOND
case|:
case|case
name|GIMP_HANDLE_FILLED_DIAMOND
case|:
name|angle
operator|-=
name|G_PI
operator|/
literal|4.0
expr_stmt|;
name|diamond_offset_x
operator|=
name|private
operator|->
name|width
operator|/
literal|2.0
expr_stmt|;
name|diamond_offset_y
operator|=
name|private
operator|->
name|height
operator|/
literal|2.0
expr_stmt|;
case|case
name|GIMP_HANDLE_SQUARE
case|:
case|case
name|GIMP_HANDLE_FILLED_SQUARE
case|:
name|gimp_canvas_item_transform_xy_f
argument_list|(
name|item
argument_list|,
name|private
operator|->
name|x
argument_list|,
name|private
operator|->
name|y
argument_list|,
operator|&
name|tx
argument_list|,
operator|&
name|ty
argument_list|)
expr_stmt|;
name|mmx
operator|=
name|mx
operator|-
name|tx
expr_stmt|;
name|mmy
operator|=
name|my
operator|-
name|ty
expr_stmt|;
name|mx
operator|=
name|cos
argument_list|(
name|angle
argument_list|)
operator|*
name|mmx
operator|-
name|sin
argument_list|(
name|angle
argument_list|)
operator|*
name|mmy
operator|+
name|tx
operator|+
name|diamond_offset_x
expr_stmt|;
name|my
operator|=
name|sin
argument_list|(
name|angle
argument_list|)
operator|*
name|mmx
operator|+
name|cos
argument_list|(
name|angle
argument_list|)
operator|*
name|mmy
operator|+
name|ty
operator|+
name|diamond_offset_y
expr_stmt|;
return|return
name|mx
operator|>
name|handle_tx
operator|&&
name|mx
operator|<
name|handle_tx
operator|+
name|private
operator|->
name|width
operator|&&
name|my
operator|>
name|handle_ty
operator|&&
name|my
operator|<
name|handle_ty
operator|+
name|private
operator|->
name|height
return|;
case|case
name|GIMP_HANDLE_CIRCLE
case|:
case|case
name|GIMP_HANDLE_FILLED_CIRCLE
case|:
case|case
name|GIMP_HANDLE_CROSS
case|:
block|{
name|gint
name|width
init|=
name|private
operator|->
name|width
decl_stmt|;
if|if
condition|(
name|width
operator|!=
name|private
operator|->
name|height
condition|)
name|width
operator|=
operator|(
name|width
operator|+
name|private
operator|->
name|height
operator|)
operator|/
literal|2
expr_stmt|;
name|width
operator|/=
literal|2
expr_stmt|;
return|return
operator|(
operator|(
name|SQR
argument_list|(
name|handle_tx
operator|-
name|mx
argument_list|)
operator|+
name|SQR
argument_list|(
name|handle_ty
operator|-
name|my
argument_list|)
operator|)
operator|<
name|SQR
argument_list|(
name|width
argument_list|)
operator|)
return|;
block|}
default|default:
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_canvas_handle_new (GimpDisplayShell * shell,GimpHandleType type,GimpHandleAnchor anchor,gdouble x,gdouble y,gint width,gint height)
name|gimp_canvas_handle_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpHandleType
name|type
parameter_list|,
name|GimpHandleAnchor
name|anchor
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
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
name|GIMP_TYPE_CANVAS_HANDLE
argument_list|,
literal|"shell"
argument_list|,
name|shell
argument_list|,
literal|"type"
argument_list|,
name|type
argument_list|,
literal|"anchor"
argument_list|,
name|anchor
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
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_handle_get_position (GimpCanvasItem * handle,gdouble * x,gdouble * y)
name|gimp_canvas_handle_get_position
parameter_list|(
name|GimpCanvasItem
modifier|*
name|handle
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CANVAS_HANDLE
argument_list|(
name|handle
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|x
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|y
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|handle
argument_list|,
literal|"x"
argument_list|,
name|x
argument_list|,
literal|"y"
argument_list|,
name|y
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_handle_set_position (GimpCanvasItem * handle,gdouble x,gdouble y)
name|gimp_canvas_handle_set_position
parameter_list|(
name|GimpCanvasItem
modifier|*
name|handle
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CANVAS_HANDLE
argument_list|(
name|handle
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_item_begin_change
argument_list|(
name|handle
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|handle
argument_list|,
literal|"x"
argument_list|,
name|x
argument_list|,
literal|"y"
argument_list|,
name|y
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_canvas_item_end_change
argument_list|(
name|handle
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_handle_set_angles (GimpCanvasItem * handle,gdouble start_angle,gdouble slice_angle)
name|gimp_canvas_handle_set_angles
parameter_list|(
name|GimpCanvasItem
modifier|*
name|handle
parameter_list|,
name|gdouble
name|start_angle
parameter_list|,
name|gdouble
name|slice_angle
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CANVAS_HANDLE
argument_list|(
name|handle
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_item_begin_change
argument_list|(
name|handle
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|handle
argument_list|,
literal|"start-angle"
argument_list|,
name|start_angle
argument_list|,
literal|"slice-angle"
argument_list|,
name|slice_angle
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_canvas_item_end_change
argument_list|(
name|handle
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

