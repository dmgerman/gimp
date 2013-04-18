begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvassamplepoint.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpcanvas.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvas-style.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvassamplepoint.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_define
DECL|macro|GIMP_SAMPLE_POINT_DRAW_SIZE
define|#
directive|define
name|GIMP_SAMPLE_POINT_DRAW_SIZE
value|10
end_define

begin_enum
enum|enum
DECL|enum|__anon27504b690103
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
DECL|enumerator|PROP_INDEX
name|PROP_INDEX
block|,
DECL|enumerator|PROP_SAMPLE_POINT_STYLE
name|PROP_SAMPLE_POINT_STYLE
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasSamplePointPrivate
typedef|typedef
name|struct
name|_GimpCanvasSamplePointPrivate
name|GimpCanvasSamplePointPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasSamplePointPrivate
struct|struct
name|_GimpCanvasSamplePointPrivate
block|{
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
DECL|member|index
name|gint
name|index
decl_stmt|;
DECL|member|sample_point_style
name|gboolean
name|sample_point_style
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (sample_point)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|sample_point
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (sample_point, \                                      GIMP_TYPE_CANVAS_SAMPLE_POINT, \                                      GimpCanvasSamplePointPrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_sample_point_set_property
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
name|gimp_canvas_sample_point_get_property
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
name|gimp_canvas_sample_point_draw
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
name|gimp_canvas_sample_point_get_extents
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

begin_function_decl
specifier|static
name|void
name|gimp_canvas_sample_point_stroke
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
name|void
name|gimp_canvas_sample_point_fill
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCanvasSamplePoint,gimp_canvas_sample_point,GIMP_TYPE_CANVAS_ITEM)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCanvasSamplePoint
argument_list|,
argument|gimp_canvas_sample_point
argument_list|,
argument|GIMP_TYPE_CANVAS_ITEM
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_sample_point_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_sample_point_class_init
parameter_list|(
name|GimpCanvasSamplePointClass
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
name|gimp_canvas_sample_point_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_sample_point_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_sample_point_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_sample_point_get_extents
expr_stmt|;
name|item_class
operator|->
name|stroke
operator|=
name|gimp_canvas_sample_point_stroke
expr_stmt|;
name|item_class
operator|->
name|fill
operator|=
name|gimp_canvas_sample_point_fill
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
name|PROP_INDEX
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"index"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
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
name|PROP_SAMPLE_POINT_STYLE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"sample-point-style"
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
name|GimpCanvasSamplePointPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_sample_point_init (GimpCanvasSamplePoint * sample_point)
name|gimp_canvas_sample_point_init
parameter_list|(
name|GimpCanvasSamplePoint
modifier|*
name|sample_point
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_sample_point_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_sample_point_set_property
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
name|GimpCanvasSamplePointPrivate
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
name|PROP_INDEX
case|:
name|private
operator|->
name|index
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAMPLE_POINT_STYLE
case|:
name|private
operator|->
name|sample_point_style
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
DECL|function|gimp_canvas_sample_point_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_sample_point_get_property
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
name|GimpCanvasSamplePointPrivate
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
name|x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INDEX
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
name|PROP_SAMPLE_POINT_STYLE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|sample_point_style
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
DECL|function|gimp_canvas_sample_point_transform (GimpCanvasItem * item,gdouble * x,gdouble * y)
name|gimp_canvas_sample_point_transform
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
name|GimpCanvasSamplePointPrivate
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
operator|+
literal|0.5
argument_list|,
name|private
operator|->
name|y
operator|+
literal|0.5
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
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
block|}
end_function

begin_define
DECL|macro|HALF_SIZE
define|#
directive|define
name|HALF_SIZE
value|(GIMP_SAMPLE_POINT_DRAW_SIZE / 2)
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_sample_point_draw (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_sample_point_draw
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
name|GimpCanvasSamplePointPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|PangoLayout
modifier|*
name|layout
decl_stmt|;
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|y1
decl_stmt|,
name|y2
decl_stmt|;
name|gimp_canvas_sample_point_transform
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
name|x1
operator|=
name|x
operator|-
name|GIMP_SAMPLE_POINT_DRAW_SIZE
expr_stmt|;
name|x2
operator|=
name|x
operator|+
name|GIMP_SAMPLE_POINT_DRAW_SIZE
expr_stmt|;
name|y1
operator|=
name|y
operator|-
name|GIMP_SAMPLE_POINT_DRAW_SIZE
expr_stmt|;
name|y2
operator|=
name|y
operator|+
name|GIMP_SAMPLE_POINT_DRAW_SIZE
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y1
operator|+
name|HALF_SIZE
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y2
operator|-
name|HALF_SIZE
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x1
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x1
operator|+
name|HALF_SIZE
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x2
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x2
operator|-
name|HALF_SIZE
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_arc_negative
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|HALF_SIZE
argument_list|,
literal|0.0
argument_list|,
literal|0.5
operator|*
name|G_PI
argument_list|)
expr_stmt|;
name|_gimp_canvas_item_stroke
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
name|layout
operator|=
name|gimp_canvas_get_layout
argument_list|(
name|GIMP_CANVAS
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
literal|"%d"
argument_list|,
name|private
operator|->
name|index
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
literal|2.5
argument_list|,
name|y
operator|+
literal|2.5
argument_list|)
expr_stmt|;
name|pango_cairo_show_layout
argument_list|(
name|cr
argument_list|,
name|layout
argument_list|)
expr_stmt|;
name|_gimp_canvas_item_fill
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
DECL|function|gimp_canvas_sample_point_get_extents (GimpCanvasItem * item,GimpDisplayShell * shell)
name|gimp_canvas_sample_point_get_extents
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
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|y1
decl_stmt|,
name|y2
decl_stmt|;
name|gimp_canvas_sample_point_transform
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
name|x1
operator|=
name|floor
argument_list|(
name|x
operator|-
name|GIMP_SAMPLE_POINT_DRAW_SIZE
argument_list|)
expr_stmt|;
name|x2
operator|=
name|ceil
argument_list|(
name|x
operator|+
name|GIMP_SAMPLE_POINT_DRAW_SIZE
argument_list|)
expr_stmt|;
name|y1
operator|=
name|floor
argument_list|(
name|y
operator|-
name|GIMP_SAMPLE_POINT_DRAW_SIZE
argument_list|)
expr_stmt|;
name|y2
operator|=
name|ceil
argument_list|(
name|y
operator|+
name|GIMP_SAMPLE_POINT_DRAW_SIZE
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|x
operator|=
name|x1
operator|-
literal|1.5
expr_stmt|;
name|rectangle
operator|.
name|y
operator|=
name|y1
operator|-
literal|1.5
expr_stmt|;
name|rectangle
operator|.
name|width
operator|=
name|x2
operator|-
name|x1
operator|+
literal|3.0
expr_stmt|;
name|rectangle
operator|.
name|height
operator|=
name|y2
operator|-
name|y1
operator|+
literal|3.0
expr_stmt|;
comment|/* HACK: add 5 so the number gets cleared too */
name|rectangle
operator|.
name|width
operator|+=
literal|5
expr_stmt|;
name|rectangle
operator|.
name|height
operator|+=
literal|5
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
specifier|static
name|void
DECL|function|gimp_canvas_sample_point_stroke (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_sample_point_stroke
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
name|GimpCanvasSamplePointPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|sample_point_style
condition|)
block|{
name|gimp_canvas_set_sample_point_style
argument_list|(
name|gimp_canvas_item_get_canvas
argument_list|(
name|item
argument_list|)
argument_list|,
name|cr
argument_list|,
name|gimp_canvas_item_get_highlight
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GIMP_CANVAS_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|stroke
argument_list|(
name|item
argument_list|,
name|shell
argument_list|,
name|cr
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_sample_point_fill (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_sample_point_fill
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
name|GimpCanvasSamplePointPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|sample_point_style
condition|)
block|{
name|gimp_canvas_set_sample_point_style
argument_list|(
name|gimp_canvas_item_get_canvas
argument_list|(
name|item
argument_list|)
argument_list|,
name|cr
argument_list|,
name|gimp_canvas_item_get_highlight
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GIMP_CANVAS_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|fill
argument_list|(
name|item
argument_list|,
name|shell
argument_list|,
name|cr
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_canvas_sample_point_new (GimpDisplayShell * shell,gint x,gint y,gint index,gboolean sample_point_style)
name|gimp_canvas_sample_point_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|index
parameter_list|,
name|gboolean
name|sample_point_style
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
name|GIMP_TYPE_CANVAS_SAMPLE_POINT
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
literal|"index"
argument_list|,
name|index
argument_list|,
literal|"sample-point-style"
argument_list|,
name|sample_point_style
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_sample_point_set (GimpCanvasItem * sample_point,gint x,gint y)
name|gimp_canvas_sample_point_set
parameter_list|(
name|GimpCanvasItem
modifier|*
name|sample_point
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CANVAS_SAMPLE_POINT
argument_list|(
name|sample_point
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_item_begin_change
argument_list|(
name|sample_point
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|sample_point
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
name|sample_point
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

