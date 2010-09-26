begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvaspolygon.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvaspolygon.h"
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
DECL|enum|__anon2bdc7a980103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_POINTS
name|PROP_POINTS
block|,
DECL|enumerator|PROP_FILLED
name|PROP_FILLED
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasPolygonPrivate
typedef|typedef
name|struct
name|_GimpCanvasPolygonPrivate
name|GimpCanvasPolygonPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasPolygonPrivate
struct|struct
name|_GimpCanvasPolygonPrivate
block|{
DECL|member|points
name|GimpVector2
modifier|*
name|points
decl_stmt|;
DECL|member|n_points
name|gint
name|n_points
decl_stmt|;
DECL|member|filled
name|gboolean
name|filled
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (polygon)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|polygon
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (polygon, \                                      GIMP_TYPE_CANVAS_POLYGON, \                                      GimpCanvasPolygonPrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_polygon_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_canvas_polygon_set_property
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
name|gimp_canvas_polygon_get_property
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
name|gimp_canvas_polygon_draw
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
name|GdkRegion
modifier|*
name|gimp_canvas_polygon_get_extents
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
DECL|function|G_DEFINE_TYPE (GimpCanvasPolygon,gimp_canvas_polygon,GIMP_TYPE_CANVAS_ITEM)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCanvasPolygon
argument_list|,
argument|gimp_canvas_polygon
argument_list|,
argument|GIMP_TYPE_CANVAS_ITEM
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_polygon_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_polygon_class_init
parameter_list|(
name|GimpCanvasPolygonClass
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
name|finalize
operator|=
name|gimp_canvas_polygon_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_canvas_polygon_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_polygon_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_polygon_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_polygon_get_extents
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_POINTS
argument_list|,
name|gimp_param_spec_array
argument_list|(
literal|"points"
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
name|GimpCanvasPolygonPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_polygon_init (GimpCanvasPolygon * polygon)
name|gimp_canvas_polygon_init
parameter_list|(
name|GimpCanvasPolygon
modifier|*
name|polygon
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_polygon_finalize (GObject * object)
name|gimp_canvas_polygon_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCanvasPolygonPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|points
condition|)
block|{
name|g_free
argument_list|(
name|private
operator|->
name|points
argument_list|)
expr_stmt|;
name|private
operator|->
name|points
operator|=
name|NULL
expr_stmt|;
name|private
operator|->
name|n_points
operator|=
literal|0
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_polygon_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_polygon_set_property
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
name|GimpCanvasPolygonPrivate
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
name|PROP_POINTS
case|:
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
DECL|function|gimp_canvas_polygon_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_polygon_get_property
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
name|GimpCanvasPolygonPrivate
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
name|PROP_POINTS
case|:
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
DECL|function|gimp_canvas_polygon_transform (GimpCanvasItem * item,GimpDisplayShell * shell,GimpVector2 * points)
name|gimp_canvas_polygon_transform
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpVector2
modifier|*
name|points
parameter_list|)
block|{
name|GimpCanvasPolygonPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|private
operator|->
name|n_points
condition|;
name|i
operator|++
control|)
block|{
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|private
operator|->
name|points
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|private
operator|->
name|points
index|[
name|i
index|]
operator|.
name|y
argument_list|,
operator|&
name|points
index|[
name|i
index|]
operator|.
name|x
argument_list|,
operator|&
name|points
index|[
name|i
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
name|points
index|[
name|i
index|]
operator|.
name|x
operator|=
name|PROJ_ROUND
argument_list|(
name|points
index|[
name|i
index|]
operator|.
name|x
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|points
index|[
name|i
index|]
operator|.
name|y
operator|=
name|PROJ_ROUND
argument_list|(
name|points
index|[
name|i
index|]
operator|.
name|y
argument_list|)
operator|+
literal|0.5
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_polygon_draw (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_polygon_draw
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
name|GimpCanvasPolygonPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GimpVector2
modifier|*
name|points
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|points
operator|=
name|g_new0
argument_list|(
name|GimpVector2
argument_list|,
name|private
operator|->
name|n_points
argument_list|)
expr_stmt|;
name|gimp_canvas_polygon_transform
argument_list|(
name|item
argument_list|,
name|shell
argument_list|,
name|points
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|points
index|[
literal|0
index|]
operator|.
name|x
argument_list|,
name|points
index|[
literal|0
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|private
operator|->
name|n_points
condition|;
name|i
operator|++
control|)
block|{
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|points
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|points
index|[
name|i
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
block|}
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
name|shell
argument_list|,
name|cr
argument_list|)
expr_stmt|;
else|else
name|_gimp_canvas_item_stroke
argument_list|(
name|item
argument_list|,
name|shell
argument_list|,
name|cr
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|points
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GdkRegion
modifier|*
DECL|function|gimp_canvas_polygon_get_extents (GimpCanvasItem * item,GimpDisplayShell * shell)
name|gimp_canvas_polygon_get_extents
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
name|GimpCanvasPolygonPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GdkRectangle
name|rectangle
decl_stmt|;
name|GimpVector2
modifier|*
name|points
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|points
operator|=
name|g_new0
argument_list|(
name|GimpVector2
argument_list|,
name|private
operator|->
name|n_points
argument_list|)
expr_stmt|;
name|gimp_canvas_polygon_transform
argument_list|(
name|item
argument_list|,
name|shell
argument_list|,
name|points
argument_list|)
expr_stmt|;
name|x1
operator|=
name|floor
argument_list|(
name|points
index|[
literal|0
index|]
operator|.
name|x
operator|-
literal|1.5
argument_list|)
expr_stmt|;
name|y1
operator|=
name|floor
argument_list|(
name|points
index|[
literal|0
index|]
operator|.
name|y
operator|-
literal|1.5
argument_list|)
expr_stmt|;
name|x2
operator|=
name|x1
operator|+
literal|3
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
literal|3
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|private
operator|->
name|n_points
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|x3
init|=
name|floor
argument_list|(
name|points
index|[
name|i
index|]
operator|.
name|x
operator|-
literal|1.5
argument_list|)
decl_stmt|;
name|gint
name|y3
init|=
name|floor
argument_list|(
name|points
index|[
name|i
index|]
operator|.
name|y
operator|-
literal|1.5
argument_list|)
decl_stmt|;
name|gint
name|x4
init|=
name|x3
operator|+
literal|3
decl_stmt|;
name|gint
name|y4
init|=
name|y3
operator|+
literal|3
decl_stmt|;
name|x1
operator|=
name|MIN
argument_list|(
name|x1
argument_list|,
name|x3
argument_list|)
expr_stmt|;
name|y1
operator|=
name|MIN
argument_list|(
name|y1
argument_list|,
name|y3
argument_list|)
expr_stmt|;
name|x2
operator|=
name|MAX
argument_list|(
name|x2
argument_list|,
name|x4
argument_list|)
expr_stmt|;
name|y2
operator|=
name|MAX
argument_list|(
name|y2
argument_list|,
name|y4
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|points
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|x
operator|=
name|x1
expr_stmt|;
name|rectangle
operator|.
name|y
operator|=
name|y1
expr_stmt|;
name|rectangle
operator|.
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|rectangle
operator|.
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
return|return
name|gdk_region_rectangle
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
DECL|function|gimp_canvas_polygon_new (const GimpVector2 * points,gint n_points,gboolean filled)
name|gimp_canvas_polygon_new
parameter_list|(
specifier|const
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|gboolean
name|filled
parameter_list|)
block|{
name|GimpCanvasItem
modifier|*
name|item
decl_stmt|;
name|GimpCanvasPolygonPrivate
modifier|*
name|private
decl_stmt|;
name|item
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CANVAS_POLYGON
argument_list|,
literal|"filled"
argument_list|,
name|filled
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
expr_stmt|;
comment|/* puke */
name|private
operator|->
name|points
operator|=
name|g_memdup
argument_list|(
name|points
argument_list|,
name|n_points
operator|*
sizeof|sizeof
argument_list|(
name|GimpVector2
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|->
name|n_points
operator|=
name|n_points
expr_stmt|;
return|return
name|item
return|;
block|}
end_function

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_canvas_polygon_new_from_coords (const GimpCoords * points,gint n_points,gboolean filled)
name|gimp_canvas_polygon_new_from_coords
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|gboolean
name|filled
parameter_list|)
block|{
name|GimpCanvasItem
modifier|*
name|item
decl_stmt|;
name|GimpCanvasPolygonPrivate
modifier|*
name|private
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|item
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CANVAS_POLYGON
argument_list|,
literal|"filled"
argument_list|,
name|filled
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
expr_stmt|;
comment|/* puke */
name|private
operator|->
name|points
operator|=
name|g_new
argument_list|(
name|GimpVector2
argument_list|,
name|n_points
argument_list|)
expr_stmt|;
name|private
operator|->
name|n_points
operator|=
name|n_points
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_points
condition|;
name|i
operator|++
control|)
block|{
name|private
operator|->
name|points
index|[
name|i
index|]
operator|.
name|x
operator|=
name|points
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|private
operator|->
name|points
index|[
name|i
index|]
operator|.
name|y
operator|=
name|points
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
block|}
return|return
name|item
return|;
block|}
end_function

end_unit

