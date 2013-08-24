begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationshrink.c  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationshrink.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2bd4fd1a0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_RADIUS_X
name|PROP_RADIUS_X
block|,
DECL|enumerator|PROP_RADIUS_Y
name|PROP_RADIUS_Y
block|,
DECL|enumerator|PROP_EDGE_LOCK
name|PROP_EDGE_LOCK
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_operation_shrink_get_property
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
name|gimp_operation_shrink_set_property
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
name|gimp_operation_shrink_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GeglRectangle
name|gimp_operation_shrink_get_required_for_output
parameter_list|(
name|GeglOperation
modifier|*
name|self
parameter_list|,
specifier|const
name|gchar
modifier|*
name|input_pad
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GeglRectangle
name|gimp_operation_shrink_get_cached_region
parameter_list|(
name|GeglOperation
modifier|*
name|self
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_shrink_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|GeglBuffer
modifier|*
name|input
parameter_list|,
name|GeglBuffer
modifier|*
name|output
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationShrink,gimp_operation_shrink,GEGL_TYPE_OPERATION_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationShrink
argument_list|,
argument|gimp_operation_shrink
argument_list|,
argument|GEGL_TYPE_OPERATION_FILTER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_shrink_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_shrink_class_init
parameter_list|(
name|GimpOperationShrinkClass
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
name|GeglOperationClass
modifier|*
name|operation_class
init|=
name|GEGL_OPERATION_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GeglOperationFilterClass
modifier|*
name|filter_class
init|=
name|GEGL_OPERATION_FILTER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_operation_shrink_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_shrink_get_property
expr_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:shrink"
argument_list|,
literal|"categories"
argument_list|,
literal|"gimp"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP Shrink operation"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|operation_class
operator|->
name|prepare
operator|=
name|gimp_operation_shrink_prepare
expr_stmt|;
name|operation_class
operator|->
name|get_required_for_output
operator|=
name|gimp_operation_shrink_get_required_for_output
expr_stmt|;
name|operation_class
operator|->
name|get_cached_region
operator|=
name|gimp_operation_shrink_get_cached_region
expr_stmt|;
name|filter_class
operator|->
name|process
operator|=
name|gimp_operation_shrink_process
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_RADIUS_X
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"radius-x"
argument_list|,
literal|"Radius X"
argument_list|,
literal|"Shrink radius in X diection"
argument_list|,
literal|1
argument_list|,
literal|2342
argument_list|,
literal|1
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_RADIUS_Y
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"radius-y"
argument_list|,
literal|"Radius Y"
argument_list|,
literal|"Shrink radius in Y diection"
argument_list|,
literal|1
argument_list|,
literal|2342
argument_list|,
literal|1
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_EDGE_LOCK
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"edge-lock"
argument_list|,
literal|"Edge Lock"
argument_list|,
literal|"Shrink from border"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_shrink_init (GimpOperationShrink * self)
name|gimp_operation_shrink_init
parameter_list|(
name|GimpOperationShrink
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_shrink_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_shrink_get_property
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
name|GimpOperationShrink
modifier|*
name|self
init|=
name|GIMP_OPERATION_SHRINK
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
name|PROP_RADIUS_X
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|radius_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RADIUS_Y
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|radius_y
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EDGE_LOCK
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|edge_lock
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
DECL|function|gimp_operation_shrink_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_shrink_set_property
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
name|GimpOperationShrink
modifier|*
name|self
init|=
name|GIMP_OPERATION_SHRINK
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
name|PROP_RADIUS_X
case|:
name|self
operator|->
name|radius_x
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RADIUS_Y
case|:
name|self
operator|->
name|radius_y
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EDGE_LOCK
case|:
name|self
operator|->
name|edge_lock
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
DECL|function|gimp_operation_shrink_prepare (GeglOperation * operation)
name|gimp_operation_shrink_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
block|{
name|gegl_operation_set_format
argument_list|(
name|operation
argument_list|,
literal|"input"
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_operation_set_format
argument_list|(
name|operation
argument_list|,
literal|"output"
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GeglRectangle
DECL|function|gimp_operation_shrink_get_required_for_output (GeglOperation * self,const gchar * input_pad,const GeglRectangle * roi)
name|gimp_operation_shrink_get_required_for_output
parameter_list|(
name|GeglOperation
modifier|*
name|self
parameter_list|,
specifier|const
name|gchar
modifier|*
name|input_pad
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
block|{
return|return
operator|*
name|gegl_operation_source_get_bounding_box
argument_list|(
name|self
argument_list|,
literal|"input"
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GeglRectangle
DECL|function|gimp_operation_shrink_get_cached_region (GeglOperation * self,const GeglRectangle * roi)
name|gimp_operation_shrink_get_cached_region
parameter_list|(
name|GeglOperation
modifier|*
name|self
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
block|{
return|return
operator|*
name|gegl_operation_source_get_bounding_box
argument_list|(
name|self
argument_list|,
literal|"input"
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|compute_border (gint16 * circ,guint16 xradius,guint16 yradius)
name|compute_border
parameter_list|(
name|gint16
modifier|*
name|circ
parameter_list|,
name|guint16
name|xradius
parameter_list|,
name|guint16
name|yradius
parameter_list|)
block|{
name|gint32
name|i
decl_stmt|;
name|gint32
name|diameter
init|=
name|xradius
operator|*
literal|2
operator|+
literal|1
decl_stmt|;
name|gdouble
name|tmp
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|diameter
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|i
operator|>
name|xradius
condition|)
name|tmp
operator|=
operator|(
name|i
operator|-
name|xradius
operator|)
operator|-
literal|0.5
expr_stmt|;
elseif|else
if|if
condition|(
name|i
operator|<
name|xradius
condition|)
name|tmp
operator|=
operator|(
name|xradius
operator|-
name|i
operator|)
operator|-
literal|0.5
expr_stmt|;
else|else
name|tmp
operator|=
literal|0.0
expr_stmt|;
name|circ
index|[
name|i
index|]
operator|=
name|RINT
argument_list|(
name|yradius
operator|/
operator|(
name|gdouble
operator|)
name|xradius
operator|*
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|xradius
argument_list|)
operator|-
name|SQR
argument_list|(
name|tmp
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|rotate_pointers (gfloat ** p,guint32 n)
name|rotate_pointers
parameter_list|(
name|gfloat
modifier|*
modifier|*
name|p
parameter_list|,
name|guint32
name|n
parameter_list|)
block|{
name|guint32
name|i
decl_stmt|;
name|gfloat
modifier|*
name|tmp
decl_stmt|;
name|tmp
operator|=
name|p
index|[
literal|0
index|]
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n
operator|-
literal|1
condition|;
name|i
operator|++
control|)
name|p
index|[
name|i
index|]
operator|=
name|p
index|[
name|i
operator|+
literal|1
index|]
expr_stmt|;
name|p
index|[
name|i
index|]
operator|=
name|tmp
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_shrink_process (GeglOperation * operation,GeglBuffer * input,GeglBuffer * output,const GeglRectangle * roi,gint level)
name|gimp_operation_shrink_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|GeglBuffer
modifier|*
name|input
parameter_list|,
name|GeglBuffer
modifier|*
name|output
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|gint
name|level
parameter_list|)
block|{
comment|/* Pretty much the same as fatten_region only different.    * Blame all bugs in this function on jaycox@gimp.org    *    * If edge_lock is true we assume that pixels outside the region we    * are passed are identical to the edge pixels.  If edge_lock is    * false, we assume that pixels outside the region are 0    */
name|GimpOperationShrink
modifier|*
name|self
init|=
name|GIMP_OPERATION_SHRINK
argument_list|(
name|operation
argument_list|)
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|input_format
init|=
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|output_format
init|=
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
decl_stmt|;
name|gint32
name|i
decl_stmt|,
name|j
decl_stmt|,
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gfloat
modifier|*
modifier|*
name|buf
decl_stmt|;
comment|/* caches the the region's pixels */
name|gfloat
modifier|*
name|out
decl_stmt|;
comment|/* holds the new scan line we are computing */
name|gfloat
modifier|*
modifier|*
name|max
decl_stmt|;
comment|/* caches the smallest values for each column */
name|gint16
modifier|*
name|circ
decl_stmt|;
comment|/* holds the y coords of the filter's mask */
name|gfloat
name|last_max
decl_stmt|;
name|gint16
name|last_index
decl_stmt|;
name|gfloat
modifier|*
name|buffer
decl_stmt|;
name|gint
name|buffer_size
decl_stmt|;
name|max
operator|=
name|g_new
argument_list|(
name|gfloat
operator|*
argument_list|,
name|roi
operator|->
name|width
operator|+
literal|2
operator|*
name|self
operator|->
name|radius_x
argument_list|)
expr_stmt|;
name|buf
operator|=
name|g_new
argument_list|(
name|gfloat
operator|*
argument_list|,
name|self
operator|->
name|radius_y
operator|+
literal|1
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|self
operator|->
name|radius_y
operator|+
literal|1
condition|;
name|i
operator|++
control|)
name|buf
index|[
name|i
index|]
operator|=
name|g_new
argument_list|(
name|gfloat
argument_list|,
name|roi
operator|->
name|width
argument_list|)
expr_stmt|;
name|buffer_size
operator|=
operator|(
name|roi
operator|->
name|width
operator|+
literal|2
operator|*
name|self
operator|->
name|radius_x
operator|+
literal|1
operator|)
operator|*
operator|(
name|self
operator|->
name|radius_y
operator|+
literal|1
operator|)
expr_stmt|;
name|buffer
operator|=
name|g_new
argument_list|(
name|gfloat
argument_list|,
name|buffer_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|self
operator|->
name|edge_lock
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|buffer_size
condition|;
name|i
operator|++
control|)
name|buffer
index|[
name|i
index|]
operator|=
literal|1.0
expr_stmt|;
block|}
else|else
block|{
name|memset
argument_list|(
name|buffer
argument_list|,
literal|0
argument_list|,
name|buffer_size
operator|*
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|roi
operator|->
name|width
operator|+
literal|2
operator|*
name|self
operator|->
name|radius_x
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|i
operator|<
name|self
operator|->
name|radius_x
condition|)
block|{
if|if
condition|(
name|self
operator|->
name|edge_lock
condition|)
name|max
index|[
name|i
index|]
operator|=
name|buffer
expr_stmt|;
else|else
name|max
index|[
name|i
index|]
operator|=
operator|&
name|buffer
index|[
operator|(
name|self
operator|->
name|radius_x
operator|+
literal|1
operator|)
operator|*
operator|(
name|roi
operator|->
name|width
operator|+
name|self
operator|->
name|radius_x
operator|)
index|]
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|i
operator|<
name|roi
operator|->
name|width
operator|+
name|self
operator|->
name|radius_x
condition|)
block|{
name|max
index|[
name|i
index|]
operator|=
operator|&
name|buffer
index|[
operator|(
name|self
operator|->
name|radius_y
operator|+
literal|1
operator|)
operator|*
operator|(
name|i
operator|-
name|self
operator|->
name|radius_x
operator|)
index|]
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|self
operator|->
name|edge_lock
condition|)
name|max
index|[
name|i
index|]
operator|=
operator|&
name|buffer
index|[
operator|(
name|self
operator|->
name|radius_x
operator|+
literal|1
operator|)
operator|*
operator|(
name|roi
operator|->
name|width
operator|+
name|self
operator|->
name|radius_x
operator|-
literal|1
operator|)
index|]
expr_stmt|;
else|else
name|max
index|[
name|i
index|]
operator|=
operator|&
name|buffer
index|[
operator|(
name|self
operator|->
name|radius_x
operator|+
literal|1
operator|)
operator|*
operator|(
name|roi
operator|->
name|width
operator|+
name|self
operator|->
name|radius_x
operator|)
index|]
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|self
operator|->
name|edge_lock
condition|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|self
operator|->
name|radius_x
operator|+
literal|1
condition|;
name|j
operator|++
control|)
name|max
index|[
literal|0
index|]
index|[
name|j
index|]
operator|=
literal|0.0
expr_stmt|;
comment|/* offset the max pointer by self->radius_x so the range of the    * array is [-self->radius_x] to [roi->width + self->radius_x]    */
name|max
operator|+=
name|self
operator|->
name|radius_x
expr_stmt|;
name|out
operator|=
name|g_new
argument_list|(
name|gfloat
argument_list|,
name|roi
operator|->
name|width
argument_list|)
expr_stmt|;
name|circ
operator|=
name|g_new
argument_list|(
name|gint16
argument_list|,
literal|2
operator|*
name|self
operator|->
name|radius_x
operator|+
literal|1
argument_list|)
expr_stmt|;
name|compute_border
argument_list|(
name|circ
argument_list|,
name|self
operator|->
name|radius_x
argument_list|,
name|self
operator|->
name|radius_y
argument_list|)
expr_stmt|;
comment|/* offset the circ pointer by self->radius_x so the range of the   * array is [-self->radius_x] to [self->radius_x]   */
name|circ
operator|+=
name|self
operator|->
name|radius_x
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|self
operator|->
name|radius_y
operator|&&
name|i
operator|<
name|roi
operator|->
name|height
condition|;
name|i
operator|++
control|)
comment|/* load top of image */
name|gegl_buffer_get
argument_list|(
name|input
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|roi
operator|->
name|x
argument_list|,
name|roi
operator|->
name|y
operator|+
name|i
argument_list|,
name|roi
operator|->
name|width
argument_list|,
literal|1
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|input_format
argument_list|,
name|buf
index|[
name|i
operator|+
literal|1
index|]
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|self
operator|->
name|edge_lock
condition|)
name|memcpy
argument_list|(
name|buf
index|[
literal|0
index|]
argument_list|,
name|buf
index|[
literal|1
index|]
argument_list|,
name|roi
operator|->
name|width
operator|*
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|memset
argument_list|(
name|buf
index|[
literal|0
index|]
argument_list|,
literal|0
argument_list|,
name|roi
operator|->
name|width
operator|*
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|roi
operator|->
name|width
condition|;
name|x
operator|++
control|)
comment|/* set up max for top of image */
block|{
name|max
index|[
name|x
index|]
index|[
literal|0
index|]
operator|=
name|buf
index|[
literal|0
index|]
index|[
name|x
index|]
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|1
init|;
name|j
operator|<
name|self
operator|->
name|radius_y
operator|+
literal|1
condition|;
name|j
operator|++
control|)
name|max
index|[
name|x
index|]
index|[
name|j
index|]
operator|=
name|MIN
argument_list|(
name|buf
index|[
name|j
index|]
index|[
name|x
index|]
argument_list|,
name|max
index|[
name|x
index|]
index|[
name|j
operator|-
literal|1
index|]
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|roi
operator|->
name|height
condition|;
name|y
operator|++
control|)
block|{
name|rotate_pointers
argument_list|(
name|buf
argument_list|,
name|self
operator|->
name|radius_y
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|y
operator|<
name|roi
operator|->
name|height
operator|-
name|self
operator|->
name|radius_y
condition|)
name|gegl_buffer_get
argument_list|(
name|input
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|roi
operator|->
name|x
argument_list|,
name|roi
operator|->
name|y
operator|+
name|y
operator|+
name|self
operator|->
name|radius_y
argument_list|,
name|roi
operator|->
name|width
argument_list|,
literal|1
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|input_format
argument_list|,
name|buf
index|[
name|self
operator|->
name|radius_y
index|]
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|self
operator|->
name|edge_lock
condition|)
name|memcpy
argument_list|(
name|buf
index|[
name|self
operator|->
name|radius_y
index|]
argument_list|,
name|buf
index|[
name|self
operator|->
name|radius_y
operator|-
literal|1
index|]
argument_list|,
name|roi
operator|->
name|width
operator|*
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|memset
argument_list|(
name|buf
index|[
name|self
operator|->
name|radius_y
index|]
argument_list|,
literal|0
argument_list|,
name|roi
operator|->
name|width
operator|*
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|roi
operator|->
name|width
condition|;
name|x
operator|++
control|)
comment|/* update max array */
block|{
for|for
control|(
name|i
operator|=
name|self
operator|->
name|radius_y
init|;
name|i
operator|>
literal|0
condition|;
name|i
operator|--
control|)
name|max
index|[
name|x
index|]
index|[
name|i
index|]
operator|=
name|MIN
argument_list|(
name|MIN
argument_list|(
name|max
index|[
name|x
index|]
index|[
name|i
operator|-
literal|1
index|]
argument_list|,
name|buf
index|[
name|i
operator|-
literal|1
index|]
index|[
name|x
index|]
argument_list|)
argument_list|,
name|buf
index|[
name|i
index|]
index|[
name|x
index|]
argument_list|)
expr_stmt|;
name|max
index|[
name|x
index|]
index|[
literal|0
index|]
operator|=
name|buf
index|[
literal|0
index|]
index|[
name|x
index|]
expr_stmt|;
block|}
name|last_max
operator|=
name|max
index|[
literal|0
index|]
index|[
name|circ
index|[
operator|-
literal|1
index|]
index|]
expr_stmt|;
name|last_index
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|roi
operator|->
name|width
condition|;
name|x
operator|++
control|)
comment|/* render scan line */
block|{
name|last_index
operator|--
expr_stmt|;
if|if
condition|(
name|last_index
operator|>=
literal|0
condition|)
block|{
if|if
condition|(
name|last_max
operator|<=
literal|0.0
condition|)
block|{
name|out
index|[
name|x
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
else|else
block|{
name|last_max
operator|=
literal|1.0
expr_stmt|;
for|for
control|(
name|i
operator|=
name|self
operator|->
name|radius_x
init|;
name|i
operator|>=
literal|0
condition|;
name|i
operator|--
control|)
if|if
condition|(
name|last_max
operator|>
name|max
index|[
name|x
operator|+
name|i
index|]
index|[
name|circ
index|[
name|i
index|]
index|]
condition|)
block|{
name|last_max
operator|=
name|max
index|[
name|x
operator|+
name|i
index|]
index|[
name|circ
index|[
name|i
index|]
index|]
expr_stmt|;
name|last_index
operator|=
name|i
expr_stmt|;
block|}
name|out
index|[
name|x
index|]
operator|=
name|last_max
expr_stmt|;
block|}
block|}
else|else
block|{
name|last_index
operator|=
name|self
operator|->
name|radius_x
expr_stmt|;
name|last_max
operator|=
name|max
index|[
name|x
operator|+
name|self
operator|->
name|radius_y
index|]
index|[
name|circ
index|[
name|self
operator|->
name|radius_x
index|]
index|]
expr_stmt|;
for|for
control|(
name|i
operator|=
name|self
operator|->
name|radius_x
operator|-
literal|1
init|;
name|i
operator|>=
operator|-
name|self
operator|->
name|radius_x
condition|;
name|i
operator|--
control|)
if|if
condition|(
name|last_max
operator|>
name|max
index|[
name|x
operator|+
name|i
index|]
index|[
name|circ
index|[
name|i
index|]
index|]
condition|)
block|{
name|last_max
operator|=
name|max
index|[
name|x
operator|+
name|i
index|]
index|[
name|circ
index|[
name|i
index|]
index|]
expr_stmt|;
name|last_index
operator|=
name|i
expr_stmt|;
block|}
name|out
index|[
name|x
index|]
operator|=
name|last_max
expr_stmt|;
block|}
block|}
name|gegl_buffer_set
argument_list|(
name|output
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|roi
operator|->
name|x
argument_list|,
name|roi
operator|->
name|y
operator|+
name|y
argument_list|,
name|roi
operator|->
name|width
argument_list|,
literal|1
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|output_format
argument_list|,
name|out
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
block|}
comment|/* undo the offsets to the pointers so we can free the malloced memmory */
name|circ
operator|-=
name|self
operator|->
name|radius_x
expr_stmt|;
name|max
operator|-=
name|self
operator|->
name|radius_x
expr_stmt|;
comment|/* free the memmory */
name|g_free
argument_list|(
name|circ
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|max
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|self
operator|->
name|radius_x
operator|+
literal|1
condition|;
name|i
operator|++
control|)
name|g_free
argument_list|(
name|buf
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|out
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

