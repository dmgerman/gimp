begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvastransformguides.c  * Copyright (C) 2011 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimp-transform-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvastransformguides.h"
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

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29a1fabd0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TRANSFORM
name|PROP_TRANSFORM
block|,
DECL|enumerator|PROP_X1
name|PROP_X1
block|,
DECL|enumerator|PROP_Y1
name|PROP_Y1
block|,
DECL|enumerator|PROP_X2
name|PROP_X2
block|,
DECL|enumerator|PROP_Y2
name|PROP_Y2
block|,
DECL|enumerator|PROP_TYPE
name|PROP_TYPE
block|,
DECL|enumerator|PROP_N_GUIDES
name|PROP_N_GUIDES
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasTransformGuidesPrivate
typedef|typedef
name|struct
name|_GimpCanvasTransformGuidesPrivate
name|GimpCanvasTransformGuidesPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasTransformGuidesPrivate
struct|struct
name|_GimpCanvasTransformGuidesPrivate
block|{
DECL|member|transform
name|GimpMatrix3
name|transform
decl_stmt|;
DECL|member|x1
DECL|member|y1
name|gdouble
name|x1
decl_stmt|,
name|y1
decl_stmt|;
DECL|member|x2
DECL|member|y2
name|gdouble
name|x2
decl_stmt|,
name|y2
decl_stmt|;
DECL|member|type
name|GimpGuidesType
name|type
decl_stmt|;
DECL|member|n_guides
name|gint
name|n_guides
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (transform)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|transform
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (transform, \                                      GIMP_TYPE_CANVAS_TRANSFORM_GUIDES, \                                      GimpCanvasTransformGuidesPrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_transform_guides_set_property
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
name|gimp_canvas_transform_guides_get_property
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
name|gimp_canvas_transform_guides_draw
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
name|gimp_canvas_transform_guides_get_extents
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
DECL|function|G_DEFINE_TYPE (GimpCanvasTransformGuides,gimp_canvas_transform_guides,GIMP_TYPE_CANVAS_ITEM)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCanvasTransformGuides
argument_list|,
argument|gimp_canvas_transform_guides
argument_list|,
argument|GIMP_TYPE_CANVAS_ITEM
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_transform_guides_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_transform_guides_class_init
parameter_list|(
name|GimpCanvasTransformGuidesClass
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
name|gimp_canvas_transform_guides_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_transform_guides_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_transform_guides_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_transform_guides_get_extents
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_TRANSFORM
argument_list|,
name|gimp_param_spec_matrix3
argument_list|(
literal|"transform"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_X1
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"x1"
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
literal|0.0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_Y1
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"y1"
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
literal|0.0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_X2
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"x2"
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
literal|0.0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_Y2
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"y2"
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
literal|0.0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
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
name|GIMP_TYPE_GUIDES_TYPE
argument_list|,
name|GIMP_GUIDES_NONE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_N_GUIDES
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"n-guides"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
literal|128
argument_list|,
literal|4
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
name|GimpCanvasTransformGuidesPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_transform_guides_init (GimpCanvasTransformGuides * transform)
name|gimp_canvas_transform_guides_init
parameter_list|(
name|GimpCanvasTransformGuides
modifier|*
name|transform
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_transform_guides_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_transform_guides_set_property
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
name|GimpCanvasTransformGuidesPrivate
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
name|PROP_TRANSFORM
case|:
block|{
name|GimpMatrix3
modifier|*
name|transform
init|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|transform
condition|)
name|private
operator|->
name|transform
operator|=
operator|*
name|transform
expr_stmt|;
else|else
name|gimp_matrix3_identity
argument_list|(
operator|&
name|private
operator|->
name|transform
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|PROP_X1
case|:
name|private
operator|->
name|x1
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_Y1
case|:
name|private
operator|->
name|y1
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_X2
case|:
name|private
operator|->
name|x2
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_Y2
case|:
name|private
operator|->
name|y2
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
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
name|PROP_N_GUIDES
case|:
name|private
operator|->
name|n_guides
operator|=
name|g_value_get_int
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
DECL|function|gimp_canvas_transform_guides_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_transform_guides_get_property
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
name|GimpCanvasTransformGuidesPrivate
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
name|PROP_TRANSFORM
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|private
operator|->
name|transform
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_X1
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|x1
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_Y1
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|y1
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_X2
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|x2
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_Y2
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|y2
argument_list|)
expr_stmt|;
break|break;
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
name|PROP_N_GUIDES
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|n_guides
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
name|gboolean
DECL|function|gimp_canvas_transform_guides_transform (GimpCanvasItem * item,GimpDisplayShell * shell,gdouble * tx1,gdouble * ty1,gdouble * tx2,gdouble * ty2,gdouble * tx3,gdouble * ty3,gdouble * tx4,gdouble * ty4)
name|gimp_canvas_transform_guides_transform
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
name|tx1
parameter_list|,
name|gdouble
modifier|*
name|ty1
parameter_list|,
name|gdouble
modifier|*
name|tx2
parameter_list|,
name|gdouble
modifier|*
name|ty2
parameter_list|,
name|gdouble
modifier|*
name|tx3
parameter_list|,
name|gdouble
modifier|*
name|ty3
parameter_list|,
name|gdouble
modifier|*
name|tx4
parameter_list|,
name|gdouble
modifier|*
name|ty4
parameter_list|)
block|{
name|GimpCanvasTransformGuidesPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|private
operator|->
name|transform
argument_list|,
name|private
operator|->
name|x1
argument_list|,
name|private
operator|->
name|y1
argument_list|,
name|tx1
argument_list|,
name|ty1
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|private
operator|->
name|transform
argument_list|,
name|private
operator|->
name|x2
argument_list|,
name|private
operator|->
name|y1
argument_list|,
name|tx2
argument_list|,
name|ty2
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|private
operator|->
name|transform
argument_list|,
name|private
operator|->
name|x1
argument_list|,
name|private
operator|->
name|y2
argument_list|,
name|tx3
argument_list|,
name|ty3
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|private
operator|->
name|transform
argument_list|,
name|private
operator|->
name|x2
argument_list|,
name|private
operator|->
name|y2
argument_list|,
name|tx4
argument_list|,
name|ty4
argument_list|)
expr_stmt|;
return|return
name|gimp_transform_polygon_is_convex
argument_list|(
operator|*
name|tx1
argument_list|,
operator|*
name|ty1
argument_list|,
operator|*
name|tx2
argument_list|,
operator|*
name|ty2
argument_list|,
operator|*
name|tx3
argument_list|,
operator|*
name|ty3
argument_list|,
operator|*
name|tx4
argument_list|,
operator|*
name|ty4
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|draw_line (cairo_t * cr,GimpDisplayShell * shell,GimpMatrix3 * transform,gdouble x1,gdouble y1,gdouble x2,gdouble y2)
name|draw_line
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpMatrix3
modifier|*
name|transform
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|)
block|{
name|gimp_matrix3_transform_point
argument_list|(
name|transform
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|transform
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|x1
argument_list|,
name|y1
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
name|x2
argument_list|,
name|y2
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
operator|+
literal|0.5
expr_stmt|;
name|y1
operator|=
name|floor
argument_list|(
name|y1
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|x2
operator|=
name|floor
argument_list|(
name|x2
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|y2
operator|=
name|floor
argument_list|(
name|y2
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_transform_guides_draw (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_transform_guides_draw
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
name|GimpCanvasTransformGuidesPrivate
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
name|gdouble
name|x3
decl_stmt|,
name|y3
decl_stmt|;
name|gdouble
name|x4
decl_stmt|,
name|y4
decl_stmt|;
name|gboolean
name|convex
decl_stmt|;
name|convex
operator|=
name|gimp_canvas_transform_guides_transform
argument_list|(
name|item
argument_list|,
name|shell
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|,
operator|&
name|x3
argument_list|,
operator|&
name|y3
argument_list|,
operator|&
name|x4
argument_list|,
operator|&
name|y4
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|x1
argument_list|,
name|y1
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
name|x2
argument_list|,
name|y2
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|x3
argument_list|,
name|y3
argument_list|,
operator|&
name|x3
argument_list|,
operator|&
name|y3
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|x4
argument_list|,
name|y4
argument_list|,
operator|&
name|x4
argument_list|,
operator|&
name|y4
argument_list|)
expr_stmt|;
name|x1
operator|=
name|floor
argument_list|(
name|x1
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|y1
operator|=
name|floor
argument_list|(
name|y1
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|x2
operator|=
name|floor
argument_list|(
name|x2
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|y2
operator|=
name|floor
argument_list|(
name|y2
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|x3
operator|=
name|floor
argument_list|(
name|x3
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|y3
operator|=
name|floor
argument_list|(
name|y3
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|x4
operator|=
name|floor
argument_list|(
name|x4
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|y4
operator|=
name|floor
argument_list|(
name|y4
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x4
argument_list|,
name|y4
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x3
argument_list|,
name|y3
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|convex
condition|)
block|{
name|_gimp_canvas_item_stroke
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
return|return;
block|}
switch|switch
condition|(
name|private
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_GUIDES_NONE
case|:
break|break;
case|case
name|GIMP_GUIDES_CENTER_LINES
case|:
comment|/* TODO */
break|break;
case|case
name|GIMP_GUIDES_THIRDS
case|:
comment|/* TODO */
break|break;
case|case
name|GIMP_GUIDES_FIFTHS
case|:
comment|/* TODO */
break|break;
case|case
name|GIMP_GUIDES_GOLDEN
case|:
comment|/* TODO */
break|break;
case|case
name|GIMP_GUIDES_DIAGONALS
case|:
comment|/* TODO */
break|break;
case|case
name|GIMP_GUIDES_N_LINES
case|:
case|case
name|GIMP_GUIDES_SPACING
case|:
block|{
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|ngx
decl_stmt|,
name|ngy
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|width
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
name|private
operator|->
name|x2
operator|-
name|private
operator|->
name|x1
argument_list|)
expr_stmt|;
name|height
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
name|private
operator|->
name|y2
operator|-
name|private
operator|->
name|y1
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|type
operator|==
name|GIMP_GUIDES_N_LINES
condition|)
block|{
if|if
condition|(
name|width
operator|<=
name|height
condition|)
block|{
name|ngx
operator|=
name|private
operator|->
name|n_guides
expr_stmt|;
name|ngy
operator|=
name|ngx
operator|*
name|MAX
argument_list|(
literal|1
argument_list|,
name|height
operator|/
name|width
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|ngy
operator|=
name|private
operator|->
name|n_guides
expr_stmt|;
name|ngx
operator|=
name|ngy
operator|*
name|MAX
argument_list|(
literal|1
argument_list|,
name|width
operator|/
name|height
argument_list|)
expr_stmt|;
block|}
block|}
else|else
comment|/* GIMP_GUIDES_SPACING */
block|{
name|gint
name|grid_size
init|=
name|MAX
argument_list|(
literal|2
argument_list|,
name|private
operator|->
name|n_guides
argument_list|)
decl_stmt|;
name|ngx
operator|=
name|width
operator|/
name|grid_size
expr_stmt|;
name|ngy
operator|=
name|height
operator|/
name|grid_size
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<=
name|ngx
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|x
init|=
name|private
operator|->
name|x1
operator|+
operator|(
operator|(
operator|(
name|gdouble
operator|)
name|i
operator|)
operator|/
operator|(
name|ngx
operator|+
literal|1
operator|)
operator|*
operator|(
name|private
operator|->
name|x2
operator|-
name|private
operator|->
name|x1
operator|)
operator|)
decl_stmt|;
name|draw_line
argument_list|(
name|cr
argument_list|,
name|shell
argument_list|,
operator|&
name|private
operator|->
name|transform
argument_list|,
name|x
argument_list|,
name|private
operator|->
name|y1
argument_list|,
name|x
argument_list|,
name|private
operator|->
name|y2
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<=
name|ngy
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|y
init|=
name|private
operator|->
name|y1
operator|+
operator|(
operator|(
operator|(
name|gdouble
operator|)
name|i
operator|)
operator|/
operator|(
name|ngy
operator|+
literal|1
operator|)
operator|*
operator|(
name|private
operator|->
name|y2
operator|-
name|private
operator|->
name|y1
operator|)
operator|)
decl_stmt|;
name|draw_line
argument_list|(
name|cr
argument_list|,
name|shell
argument_list|,
operator|&
name|private
operator|->
name|transform
argument_list|,
name|private
operator|->
name|x1
argument_list|,
name|y
argument_list|,
name|private
operator|->
name|x2
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
block|}
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
DECL|function|gimp_canvas_transform_guides_get_extents (GimpCanvasItem * item,GimpDisplayShell * shell)
name|gimp_canvas_transform_guides_get_extents
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
name|gdouble
name|x3
decl_stmt|,
name|y3
decl_stmt|;
name|gdouble
name|x4
decl_stmt|,
name|y4
decl_stmt|;
name|cairo_rectangle_int_t
name|extents
decl_stmt|;
name|gimp_canvas_transform_guides_transform
argument_list|(
name|item
argument_list|,
name|shell
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|,
operator|&
name|x3
argument_list|,
operator|&
name|y3
argument_list|,
operator|&
name|x4
argument_list|,
operator|&
name|y4
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|x1
argument_list|,
name|y1
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
name|x2
argument_list|,
name|y2
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|x3
argument_list|,
name|y3
argument_list|,
operator|&
name|x3
argument_list|,
operator|&
name|y3
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|x4
argument_list|,
name|y4
argument_list|,
operator|&
name|x4
argument_list|,
operator|&
name|y4
argument_list|)
expr_stmt|;
name|extents
operator|.
name|x
operator|=
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|MIN4
argument_list|(
name|x1
argument_list|,
name|x2
argument_list|,
name|x3
argument_list|,
name|x4
argument_list|)
operator|-
literal|1.5
argument_list|)
expr_stmt|;
name|extents
operator|.
name|y
operator|=
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|MIN4
argument_list|(
name|y1
argument_list|,
name|y2
argument_list|,
name|y3
argument_list|,
name|y4
argument_list|)
operator|-
literal|1.5
argument_list|)
expr_stmt|;
name|extents
operator|.
name|width
operator|=
operator|(
name|gint
operator|)
name|ceil
argument_list|(
name|MAX4
argument_list|(
name|x1
argument_list|,
name|x2
argument_list|,
name|x3
argument_list|,
name|x4
argument_list|)
operator|+
literal|1.5
argument_list|)
expr_stmt|;
name|extents
operator|.
name|height
operator|=
operator|(
name|gint
operator|)
name|ceil
argument_list|(
name|MAX4
argument_list|(
name|y1
argument_list|,
name|y2
argument_list|,
name|y3
argument_list|,
name|y4
argument_list|)
operator|+
literal|1.5
argument_list|)
expr_stmt|;
name|extents
operator|.
name|width
operator|-=
name|extents
operator|.
name|x
expr_stmt|;
name|extents
operator|.
name|height
operator|-=
name|extents
operator|.
name|y
expr_stmt|;
return|return
name|cairo_region_create_rectangle
argument_list|(
operator|&
name|extents
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_canvas_transform_guides_new (GimpDisplayShell * shell,const GimpMatrix3 * transform,gdouble x1,gdouble y1,gdouble x2,gdouble y2,GimpGuidesType type,gint n_guides)
name|gimp_canvas_transform_guides_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|transform
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
name|GimpGuidesType
name|type
parameter_list|,
name|gint
name|n_guides
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
name|GIMP_TYPE_CANVAS_TRANSFORM_GUIDES
argument_list|,
literal|"shell"
argument_list|,
name|shell
argument_list|,
literal|"transform"
argument_list|,
name|transform
argument_list|,
literal|"x1"
argument_list|,
name|x1
argument_list|,
literal|"y1"
argument_list|,
name|y1
argument_list|,
literal|"x2"
argument_list|,
name|x2
argument_list|,
literal|"y2"
argument_list|,
name|y2
argument_list|,
literal|"type"
argument_list|,
name|type
argument_list|,
literal|"n-guides"
argument_list|,
name|n_guides
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_transform_guides_set (GimpCanvasItem * guides,const GimpMatrix3 * transform,GimpGuidesType type,gint n_guides)
name|gimp_canvas_transform_guides_set
parameter_list|(
name|GimpCanvasItem
modifier|*
name|guides
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|transform
parameter_list|,
name|GimpGuidesType
name|type
parameter_list|,
name|gint
name|n_guides
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CANVAS_TRANSFORM_GUIDES
argument_list|(
name|guides
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_item_begin_change
argument_list|(
name|guides
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|guides
argument_list|,
literal|"transform"
argument_list|,
name|transform
argument_list|,
literal|"type"
argument_list|,
name|type
argument_list|,
literal|"n-guides"
argument_list|,
name|n_guides
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_canvas_item_end_change
argument_list|(
name|guides
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

