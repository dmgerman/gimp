begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvasboundary.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"core/gimp-transform-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpboundary.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasboundary.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c192b080103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SEGS
name|PROP_SEGS
block|,
DECL|enumerator|PROP_TRANSFORM
name|PROP_TRANSFORM
block|,
DECL|enumerator|PROP_OFFSET_X
name|PROP_OFFSET_X
block|,
DECL|enumerator|PROP_OFFSET_Y
name|PROP_OFFSET_Y
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasBoundaryPrivate
typedef|typedef
name|struct
name|_GimpCanvasBoundaryPrivate
name|GimpCanvasBoundaryPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasBoundaryPrivate
struct|struct
name|_GimpCanvasBoundaryPrivate
block|{
DECL|member|segs
name|GimpBoundSeg
modifier|*
name|segs
decl_stmt|;
DECL|member|n_segs
name|gint
name|n_segs
decl_stmt|;
DECL|member|transform
name|GimpMatrix3
modifier|*
name|transform
decl_stmt|;
DECL|member|offset_x
name|gdouble
name|offset_x
decl_stmt|;
DECL|member|offset_y
name|gdouble
name|offset_y
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (boundary)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|boundary
parameter_list|)
define|\
value|((GimpCanvasBoundaryPrivate *) gimp_canvas_boundary_get_instance_private ((GimpCanvasBoundary *) (boundary)))
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_boundary_finalize
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
name|gimp_canvas_boundary_set_property
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
name|gimp_canvas_boundary_get_property
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
name|gimp_canvas_boundary_draw
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
name|gimp_canvas_boundary_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpCanvasBoundary,gimp_canvas_boundary,GIMP_TYPE_CANVAS_ITEM)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpCanvasBoundary
argument_list|,
argument|gimp_canvas_boundary
argument_list|,
argument|GIMP_TYPE_CANVAS_ITEM
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_boundary_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_boundary_class_init
parameter_list|(
name|GimpCanvasBoundaryClass
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
name|gimp_canvas_boundary_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_canvas_boundary_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_boundary_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_boundary_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_boundary_get_extents
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SEGS
argument_list|,
name|gimp_param_spec_array
argument_list|(
literal|"segs"
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
name|PROP_TRANSFORM
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"transform"
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
name|PROP_OFFSET_X
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"offset-x"
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
name|PROP_OFFSET_Y
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"offset-y"
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_boundary_init (GimpCanvasBoundary * boundary)
name|gimp_canvas_boundary_init
parameter_list|(
name|GimpCanvasBoundary
modifier|*
name|boundary
parameter_list|)
block|{
name|gimp_canvas_item_set_line_cap
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|boundary
argument_list|)
argument_list|,
name|CAIRO_LINE_CAP_SQUARE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_boundary_finalize (GObject * object)
name|gimp_canvas_boundary_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCanvasBoundaryPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|private
operator|->
name|segs
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|private
operator|->
name|n_segs
operator|=
literal|0
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|private
operator|->
name|transform
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
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
DECL|function|gimp_canvas_boundary_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_boundary_set_property
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
name|GimpCanvasBoundaryPrivate
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
name|PROP_SEGS
case|:
break|break;
case|case
name|PROP_TRANSFORM
case|:
block|{
name|GimpMatrix3
modifier|*
name|transform
init|=
name|g_value_get_pointer
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|transform
condition|)
name|g_free
argument_list|(
name|private
operator|->
name|transform
argument_list|)
expr_stmt|;
if|if
condition|(
name|transform
condition|)
name|private
operator|->
name|transform
operator|=
name|g_memdup
argument_list|(
name|transform
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpMatrix3
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|private
operator|->
name|transform
operator|=
name|NULL
expr_stmt|;
block|}
break|break;
case|case
name|PROP_OFFSET_X
case|:
name|private
operator|->
name|offset_x
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OFFSET_Y
case|:
name|private
operator|->
name|offset_y
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
DECL|function|gimp_canvas_boundary_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_boundary_get_property
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
name|GimpCanvasBoundaryPrivate
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
name|PROP_SEGS
case|:
break|break;
case|case
name|PROP_TRANSFORM
case|:
name|g_value_set_pointer
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|transform
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OFFSET_X
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|offset_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OFFSET_Y
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|offset_y
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
DECL|function|gimp_canvas_boundary_transform (GimpCanvasItem * item,GimpSegment * segs,gint * n_segs)
name|gimp_canvas_boundary_transform
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpSegment
modifier|*
name|segs
parameter_list|,
name|gint
modifier|*
name|n_segs
parameter_list|)
block|{
name|GimpCanvasBoundaryPrivate
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
if|if
condition|(
name|private
operator|->
name|transform
condition|)
block|{
name|gint
name|n
init|=
literal|0
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
name|n_segs
condition|;
name|i
operator|++
control|)
block|{
name|GimpVector2
name|vertices
index|[
literal|2
index|]
decl_stmt|;
name|GimpVector2
name|t_vertices
index|[
literal|2
index|]
decl_stmt|;
name|gint
name|n_t_vertices
decl_stmt|;
name|vertices
index|[
literal|0
index|]
operator|=
operator|(
name|GimpVector2
operator|)
block|{
name|private
operator|->
name|segs
index|[
name|i
index|]
operator|.
name|x1
block|,
name|private
operator|->
name|segs
index|[
name|i
index|]
operator|.
name|y1
block|}
expr_stmt|;
name|vertices
index|[
literal|1
index|]
operator|=
operator|(
name|GimpVector2
operator|)
block|{
name|private
operator|->
name|segs
index|[
name|i
index|]
operator|.
name|x2
block|,
name|private
operator|->
name|segs
index|[
name|i
index|]
operator|.
name|y2
block|}
expr_stmt|;
name|gimp_transform_polygon
argument_list|(
name|private
operator|->
name|transform
argument_list|,
name|vertices
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|,
name|t_vertices
argument_list|,
operator|&
name|n_t_vertices
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_t_vertices
operator|==
literal|2
condition|)
block|{
name|gimp_canvas_item_transform_xy
argument_list|(
name|item
argument_list|,
name|t_vertices
index|[
literal|0
index|]
operator|.
name|x
operator|+
name|private
operator|->
name|offset_x
argument_list|,
name|t_vertices
index|[
literal|0
index|]
operator|.
name|y
operator|+
name|private
operator|->
name|offset_y
argument_list|,
operator|&
name|segs
index|[
name|n
index|]
operator|.
name|x1
argument_list|,
operator|&
name|segs
index|[
name|n
index|]
operator|.
name|y1
argument_list|)
expr_stmt|;
name|gimp_canvas_item_transform_xy
argument_list|(
name|item
argument_list|,
name|t_vertices
index|[
literal|1
index|]
operator|.
name|x
operator|+
name|private
operator|->
name|offset_x
argument_list|,
name|t_vertices
index|[
literal|1
index|]
operator|.
name|y
operator|+
name|private
operator|->
name|offset_y
argument_list|,
operator|&
name|segs
index|[
name|n
index|]
operator|.
name|x2
argument_list|,
operator|&
name|segs
index|[
name|n
index|]
operator|.
name|y2
argument_list|)
expr_stmt|;
name|n
operator|++
expr_stmt|;
block|}
block|}
operator|*
name|n_segs
operator|=
name|n
expr_stmt|;
block|}
else|else
block|{
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
name|n_segs
condition|;
name|i
operator|++
control|)
block|{
name|gimp_canvas_item_transform_xy
argument_list|(
name|item
argument_list|,
name|private
operator|->
name|segs
index|[
name|i
index|]
operator|.
name|x1
operator|+
name|private
operator|->
name|offset_x
argument_list|,
name|private
operator|->
name|segs
index|[
name|i
index|]
operator|.
name|y1
operator|+
name|private
operator|->
name|offset_y
argument_list|,
operator|&
name|segs
index|[
name|i
index|]
operator|.
name|x1
argument_list|,
operator|&
name|segs
index|[
name|i
index|]
operator|.
name|y1
argument_list|)
expr_stmt|;
name|gimp_canvas_item_transform_xy
argument_list|(
name|item
argument_list|,
name|private
operator|->
name|segs
index|[
name|i
index|]
operator|.
name|x2
operator|+
name|private
operator|->
name|offset_x
argument_list|,
name|private
operator|->
name|segs
index|[
name|i
index|]
operator|.
name|y2
operator|+
name|private
operator|->
name|offset_y
argument_list|,
operator|&
name|segs
index|[
name|i
index|]
operator|.
name|x2
argument_list|,
operator|&
name|segs
index|[
name|i
index|]
operator|.
name|y2
argument_list|)
expr_stmt|;
comment|/*  If this segment is a closing segment&& the segments lie inside            *  the region, OR if this is an opening segment and the segments            *  lie outside the region...            *  we need to transform it by one display pixel            */
if|if
condition|(
operator|!
name|private
operator|->
name|segs
index|[
name|i
index|]
operator|.
name|open
condition|)
block|{
comment|/*  If it is vertical  */
if|if
condition|(
name|segs
index|[
name|i
index|]
operator|.
name|x1
operator|==
name|segs
index|[
name|i
index|]
operator|.
name|x2
condition|)
block|{
name|segs
index|[
name|i
index|]
operator|.
name|x1
operator|-=
literal|1
expr_stmt|;
name|segs
index|[
name|i
index|]
operator|.
name|x2
operator|-=
literal|1
expr_stmt|;
block|}
else|else
block|{
name|segs
index|[
name|i
index|]
operator|.
name|y1
operator|-=
literal|1
expr_stmt|;
name|segs
index|[
name|i
index|]
operator|.
name|y2
operator|-=
literal|1
expr_stmt|;
block|}
block|}
block|}
operator|*
name|n_segs
operator|=
name|private
operator|->
name|n_segs
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_boundary_draw (GimpCanvasItem * item,cairo_t * cr)
name|gimp_canvas_boundary_draw
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
name|GimpCanvasBoundaryPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GimpSegment
modifier|*
name|segs
decl_stmt|;
name|gint
name|n_segs
decl_stmt|;
name|segs
operator|=
name|g_new0
argument_list|(
name|GimpSegment
argument_list|,
name|private
operator|->
name|n_segs
argument_list|)
expr_stmt|;
name|gimp_canvas_boundary_transform
argument_list|(
name|item
argument_list|,
name|segs
argument_list|,
operator|&
name|n_segs
argument_list|)
expr_stmt|;
name|gimp_cairo_segments
argument_list|(
name|cr
argument_list|,
name|segs
argument_list|,
name|n_segs
argument_list|)
expr_stmt|;
name|_gimp_canvas_item_stroke
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|segs
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|cairo_region_t
modifier|*
DECL|function|gimp_canvas_boundary_get_extents (GimpCanvasItem * item)
name|gimp_canvas_boundary_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
block|{
name|GimpCanvasBoundaryPrivate
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
name|GimpSegment
modifier|*
name|segs
decl_stmt|;
name|gint
name|n_segs
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
name|segs
operator|=
name|g_new0
argument_list|(
name|GimpSegment
argument_list|,
name|private
operator|->
name|n_segs
argument_list|)
expr_stmt|;
name|gimp_canvas_boundary_transform
argument_list|(
name|item
argument_list|,
name|segs
argument_list|,
operator|&
name|n_segs
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_segs
operator|==
literal|0
condition|)
block|{
name|g_free
argument_list|(
name|segs
argument_list|)
expr_stmt|;
return|return
name|cairo_region_create
argument_list|()
return|;
block|}
name|x1
operator|=
name|MIN
argument_list|(
name|segs
index|[
literal|0
index|]
operator|.
name|x1
argument_list|,
name|segs
index|[
literal|0
index|]
operator|.
name|x2
argument_list|)
expr_stmt|;
name|y1
operator|=
name|MIN
argument_list|(
name|segs
index|[
literal|0
index|]
operator|.
name|y1
argument_list|,
name|segs
index|[
literal|0
index|]
operator|.
name|y2
argument_list|)
expr_stmt|;
name|x2
operator|=
name|MAX
argument_list|(
name|segs
index|[
literal|0
index|]
operator|.
name|x1
argument_list|,
name|segs
index|[
literal|0
index|]
operator|.
name|x2
argument_list|)
expr_stmt|;
name|y2
operator|=
name|MAX
argument_list|(
name|segs
index|[
literal|0
index|]
operator|.
name|y1
argument_list|,
name|segs
index|[
literal|0
index|]
operator|.
name|y2
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
name|n_segs
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|x3
init|=
name|MIN
argument_list|(
name|segs
index|[
name|i
index|]
operator|.
name|x1
argument_list|,
name|segs
index|[
name|i
index|]
operator|.
name|x2
argument_list|)
decl_stmt|;
name|gint
name|y3
init|=
name|MIN
argument_list|(
name|segs
index|[
name|i
index|]
operator|.
name|y1
argument_list|,
name|segs
index|[
name|i
index|]
operator|.
name|y2
argument_list|)
decl_stmt|;
name|gint
name|x4
init|=
name|MAX
argument_list|(
name|segs
index|[
name|i
index|]
operator|.
name|x1
argument_list|,
name|segs
index|[
name|i
index|]
operator|.
name|x2
argument_list|)
decl_stmt|;
name|gint
name|y4
init|=
name|MAX
argument_list|(
name|segs
index|[
name|i
index|]
operator|.
name|y1
argument_list|,
name|segs
index|[
name|i
index|]
operator|.
name|y2
argument_list|)
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
name|segs
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|x
operator|=
name|x1
operator|-
literal|2
expr_stmt|;
name|rectangle
operator|.
name|y
operator|=
name|y1
operator|-
literal|2
expr_stmt|;
name|rectangle
operator|.
name|width
operator|=
name|x2
operator|-
name|x1
operator|+
literal|4
expr_stmt|;
name|rectangle
operator|.
name|height
operator|=
name|y2
operator|-
name|y1
operator|+
literal|4
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
DECL|function|gimp_canvas_boundary_new (GimpDisplayShell * shell,const GimpBoundSeg * segs,gint n_segs,GimpMatrix3 * transform,gdouble offset_x,gdouble offset_y)
name|gimp_canvas_boundary_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GimpBoundSeg
modifier|*
name|segs
parameter_list|,
name|gint
name|n_segs
parameter_list|,
name|GimpMatrix3
modifier|*
name|transform
parameter_list|,
name|gdouble
name|offset_x
parameter_list|,
name|gdouble
name|offset_y
parameter_list|)
block|{
name|GimpCanvasItem
modifier|*
name|item
decl_stmt|;
name|GimpCanvasBoundaryPrivate
modifier|*
name|private
decl_stmt|;
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
name|item
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CANVAS_BOUNDARY
argument_list|,
literal|"shell"
argument_list|,
name|shell
argument_list|,
literal|"transform"
argument_list|,
name|transform
argument_list|,
literal|"offset-x"
argument_list|,
name|offset_x
argument_list|,
literal|"offset-y"
argument_list|,
name|offset_y
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
name|segs
operator|=
name|g_memdup
argument_list|(
name|segs
argument_list|,
name|n_segs
operator|*
sizeof|sizeof
argument_list|(
name|GimpBoundSeg
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|->
name|n_segs
operator|=
name|n_segs
expr_stmt|;
return|return
name|item
return|;
block|}
end_function

end_unit

