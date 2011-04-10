begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvasarc.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"widgets/gimpcairo.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasarc.h"
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
DECL|enum|__anon2c42f5060103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CENTER_X
name|PROP_CENTER_X
block|,
DECL|enumerator|PROP_CENTER_Y
name|PROP_CENTER_Y
block|,
DECL|enumerator|PROP_RADIUS_X
name|PROP_RADIUS_X
block|,
DECL|enumerator|PROP_RADIUS_Y
name|PROP_RADIUS_Y
block|,
DECL|enumerator|PROP_START_ANGLE
name|PROP_START_ANGLE
block|,
DECL|enumerator|PROP_SLICE_ANGLE
name|PROP_SLICE_ANGLE
block|,
DECL|enumerator|PROP_FILLED
name|PROP_FILLED
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasArcPrivate
typedef|typedef
name|struct
name|_GimpCanvasArcPrivate
name|GimpCanvasArcPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasArcPrivate
struct|struct
name|_GimpCanvasArcPrivate
block|{
DECL|member|center_x
name|gdouble
name|center_x
decl_stmt|;
DECL|member|center_y
name|gdouble
name|center_y
decl_stmt|;
DECL|member|radius_x
name|gdouble
name|radius_x
decl_stmt|;
DECL|member|radius_y
name|gdouble
name|radius_y
decl_stmt|;
DECL|member|start_angle
name|gdouble
name|start_angle
decl_stmt|;
DECL|member|slice_angle
name|gdouble
name|slice_angle
decl_stmt|;
empty_stmt|;
DECL|member|filled
name|gboolean
name|filled
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (arc)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|arc
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (arc, \                                      GIMP_TYPE_CANVAS_ARC, \                                      GimpCanvasArcPrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_arc_set_property
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
name|gimp_canvas_arc_get_property
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
name|gimp_canvas_arc_draw
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
name|gimp_canvas_arc_get_extents
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
DECL|function|G_DEFINE_TYPE (GimpCanvasArc,gimp_canvas_arc,GIMP_TYPE_CANVAS_ITEM)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCanvasArc
argument_list|,
argument|gimp_canvas_arc
argument_list|,
argument|GIMP_TYPE_CANVAS_ITEM
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_arc_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_arc_class_init
parameter_list|(
name|GimpCanvasArcClass
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
name|gimp_canvas_arc_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_arc_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_arc_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_arc_get_extents
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CENTER_X
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"center-x"
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
name|PROP_CENTER_Y
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"center-y"
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
name|PROP_RADIUS_X
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"radius-x"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
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
name|PROP_RADIUS_Y
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"radius-y"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
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
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_FILLED
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"filled"
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
name|GimpCanvasArcPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_arc_init (GimpCanvasArc * arc)
name|gimp_canvas_arc_init
parameter_list|(
name|GimpCanvasArc
modifier|*
name|arc
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_arc_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_arc_set_property
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
name|GimpCanvasArcPrivate
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
name|PROP_CENTER_X
case|:
name|private
operator|->
name|center_x
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CENTER_Y
case|:
name|private
operator|->
name|center_y
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RADIUS_X
case|:
name|private
operator|->
name|radius_x
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RADIUS_Y
case|:
name|private
operator|->
name|radius_y
operator|=
name|g_value_get_double
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
case|case
name|PROP_FILLED
case|:
name|private
operator|->
name|filled
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
DECL|function|gimp_canvas_arc_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_arc_get_property
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
name|GimpCanvasArcPrivate
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
name|PROP_CENTER_X
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|center_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CENTER_Y
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|center_y
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RADIUS_X
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|radius_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RADIUS_Y
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|radius_y
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
case|case
name|PROP_FILLED
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|filled
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
DECL|function|gimp_canvas_arc_transform (GimpCanvasItem * item,GimpDisplayShell * shell,gdouble * center_x,gdouble * center_y,gdouble * radius_x,gdouble * radius_y)
name|gimp_canvas_arc_transform
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
name|center_x
parameter_list|,
name|gdouble
modifier|*
name|center_y
parameter_list|,
name|gdouble
modifier|*
name|radius_x
parameter_list|,
name|gdouble
modifier|*
name|radius_y
parameter_list|)
block|{
name|GimpCanvasArcPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gdouble
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gdouble
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|private
operator|->
name|center_x
operator|-
name|private
operator|->
name|radius_x
argument_list|,
name|private
operator|->
name|center_y
operator|-
name|private
operator|->
name|radius_y
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|private
operator|->
name|center_x
operator|+
name|private
operator|->
name|radius_x
argument_list|,
name|private
operator|->
name|center_y
operator|+
name|private
operator|->
name|radius_y
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|x1
operator|=
name|floor
argument_list|(
name|x1
argument_list|)
expr_stmt|;
name|y1
operator|=
name|floor
argument_list|(
name|y1
argument_list|)
expr_stmt|;
name|x2
operator|=
name|ceil
argument_list|(
name|x2
argument_list|)
expr_stmt|;
name|y2
operator|=
name|ceil
argument_list|(
name|y2
argument_list|)
expr_stmt|;
operator|*
name|center_x
operator|=
operator|(
name|x1
operator|+
name|x2
operator|)
operator|/
literal|2.0
expr_stmt|;
operator|*
name|center_y
operator|=
operator|(
name|y1
operator|+
name|y2
operator|)
operator|/
literal|2.0
expr_stmt|;
operator|*
name|radius_x
operator|=
operator|(
name|x2
operator|-
name|x1
operator|)
operator|/
literal|2.0
expr_stmt|;
operator|*
name|radius_y
operator|=
operator|(
name|y2
operator|-
name|y1
operator|)
operator|/
literal|2.0
expr_stmt|;
if|if
condition|(
operator|!
name|private
operator|->
name|filled
condition|)
block|{
operator|*
name|radius_x
operator|-=
literal|0.5
expr_stmt|;
operator|*
name|radius_y
operator|-=
literal|0.5
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_arc_draw (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_arc_draw
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
name|GimpCanvasArcPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gdouble
name|center_x
decl_stmt|,
name|center_y
decl_stmt|;
name|gdouble
name|radius_x
decl_stmt|,
name|radius_y
decl_stmt|;
name|gimp_canvas_arc_transform
argument_list|(
name|item
argument_list|,
name|shell
argument_list|,
operator|&
name|center_x
argument_list|,
operator|&
name|center_y
argument_list|,
operator|&
name|radius_x
argument_list|,
operator|&
name|radius_y
argument_list|)
expr_stmt|;
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|center_x
argument_list|,
name|center_y
argument_list|)
expr_stmt|;
name|cairo_scale
argument_list|(
name|cr
argument_list|,
name|radius_x
argument_list|,
name|radius_y
argument_list|)
expr_stmt|;
name|gimp_cairo_add_arc
argument_list|(
name|cr
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
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
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|filled
condition|)
name|_gimp_canvas_item_fill
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
else|else
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
DECL|function|gimp_canvas_arc_get_extents (GimpCanvasItem * item,GimpDisplayShell * shell)
name|gimp_canvas_arc_get_extents
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
name|cairo_rectangle_int_t
name|rectangle
decl_stmt|;
name|gdouble
name|center_x
decl_stmt|,
name|center_y
decl_stmt|;
name|gdouble
name|radius_x
decl_stmt|,
name|radius_y
decl_stmt|;
name|gimp_canvas_arc_transform
argument_list|(
name|item
argument_list|,
name|shell
argument_list|,
operator|&
name|center_x
argument_list|,
operator|&
name|center_y
argument_list|,
operator|&
name|radius_x
argument_list|,
operator|&
name|radius_y
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|x
operator|=
name|floor
argument_list|(
name|center_x
operator|-
name|radius_x
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
name|center_y
operator|-
name|radius_y
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
name|center_x
operator|+
name|radius_x
operator|+
literal|1.5
argument_list|)
operator|-
name|rectangle
operator|.
name|x
expr_stmt|;
name|rectangle
operator|.
name|height
operator|=
name|ceil
argument_list|(
name|center_y
operator|+
name|radius_y
operator|+
literal|1.5
argument_list|)
operator|-
name|rectangle
operator|.
name|y
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
DECL|function|gimp_canvas_arc_new (GimpDisplayShell * shell,gdouble center_x,gdouble center_y,gdouble radius_x,gdouble radius_y,gdouble start_angle,gdouble slice_angle,gboolean filled)
name|gimp_canvas_arc_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|,
name|gdouble
name|radius_x
parameter_list|,
name|gdouble
name|radius_y
parameter_list|,
name|gdouble
name|start_angle
parameter_list|,
name|gdouble
name|slice_angle
parameter_list|,
name|gboolean
name|filled
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
name|GIMP_TYPE_CANVAS_ARC
argument_list|,
literal|"shell"
argument_list|,
name|shell
argument_list|,
literal|"center-x"
argument_list|,
name|center_x
argument_list|,
literal|"center-y"
argument_list|,
name|center_y
argument_list|,
literal|"radius-x"
argument_list|,
name|radius_x
argument_list|,
literal|"radius-y"
argument_list|,
name|radius_y
argument_list|,
literal|"start-angle"
argument_list|,
name|start_angle
argument_list|,
literal|"slice-angle"
argument_list|,
name|slice_angle
argument_list|,
literal|"filled"
argument_list|,
name|filled
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

