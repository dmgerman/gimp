begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationshapeburst.c  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpoperationshapeburst.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a042af50103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_NORMALIZE
name|PROP_NORMALIZE
block|,
DECL|enumerator|PROP_PROGRESS
name|PROP_PROGRESS
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_operation_shapeburst_get_property
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
name|gimp_operation_shapeburst_set_property
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
name|GeglRectangle
name|gimp_operation_shapeburst_get_required_for_output
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
name|gimp_operation_shapeburst_get_cached_region
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
name|void
name|gimp_operation_shapeburst_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_shapeburst_process
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
DECL|function|G_DEFINE_TYPE (GimpOperationShapeburst,gimp_operation_shapeburst,GEGL_TYPE_OPERATION_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationShapeburst
argument_list|,
argument|gimp_operation_shapeburst
argument_list|,
argument|GEGL_TYPE_OPERATION_FILTER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_shapeburst_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_shapeburst_class_init
parameter_list|(
name|GimpOperationShapeburstClass
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
name|gimp_operation_shapeburst_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_shapeburst_get_property
expr_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:shapeburst"
argument_list|,
literal|"categories"
argument_list|,
literal|"gimp"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP Shapeburst operation"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|operation_class
operator|->
name|prepare
operator|=
name|gimp_operation_shapeburst_prepare
expr_stmt|;
name|operation_class
operator|->
name|get_required_for_output
operator|=
name|gimp_operation_shapeburst_get_required_for_output
expr_stmt|;
name|operation_class
operator|->
name|get_cached_region
operator|=
name|gimp_operation_shapeburst_get_cached_region
expr_stmt|;
name|filter_class
operator|->
name|process
operator|=
name|gimp_operation_shapeburst_process
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_NORMALIZE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"normalize"
argument_list|,
literal|"Normalize"
argument_list|,
literal|"Normalize"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PROGRESS
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"progress"
argument_list|,
literal|"Progress"
argument_list|,
literal|"Progress indicator, and a bad hack"
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_shapeburst_init (GimpOperationShapeburst * self)
name|gimp_operation_shapeburst_init
parameter_list|(
name|GimpOperationShapeburst
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_shapeburst_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_shapeburst_get_property
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
name|GimpOperationShapeburst
modifier|*
name|self
init|=
name|GIMP_OPERATION_SHAPEBURST
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
name|PROP_NORMALIZE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|normalize
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PROGRESS
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|progress
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
DECL|function|gimp_operation_shapeburst_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_shapeburst_set_property
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
name|GimpOperationShapeburst
modifier|*
name|self
init|=
name|GIMP_OPERATION_SHAPEBURST
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
name|PROP_NORMALIZE
case|:
name|self
operator|->
name|normalize
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PROGRESS
case|:
name|self
operator|->
name|progress
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
DECL|function|gimp_operation_shapeburst_prepare (GeglOperation * operation)
name|gimp_operation_shapeburst_prepare
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
DECL|function|gimp_operation_shapeburst_get_required_for_output (GeglOperation * self,const gchar * input_pad,const GeglRectangle * roi)
name|gimp_operation_shapeburst_get_required_for_output
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
DECL|function|gimp_operation_shapeburst_get_cached_region (GeglOperation * self,const GeglRectangle * roi)
name|gimp_operation_shapeburst_get_cached_region
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
name|gboolean
DECL|function|gimp_operation_shapeburst_process (GeglOperation * operation,GeglBuffer * input,GeglBuffer * output,const GeglRectangle * roi,gint level)
name|gimp_operation_shapeburst_process
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
name|gfloat
name|max_dist
init|=
literal|0.0
decl_stmt|;
name|gfloat
modifier|*
name|distbuf
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|distbuf
operator|=
name|g_new0
argument_list|(
name|gfloat
argument_list|,
operator|(
name|roi
operator|->
name|width
operator|+
literal|1
operator|)
operator|*
literal|2
argument_list|)
expr_stmt|;
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
name|gfloat
modifier|*
name|distbuf_cur
decl_stmt|;
name|gfloat
modifier|*
name|distbuf_prev
decl_stmt|;
name|gfloat
name|src
init|=
literal|0.0
decl_stmt|;
comment|/* toggling distance buffers for the current and previous row.        * with one spare zero element on the left side */
if|if
condition|(
name|y
operator|%
literal|2
condition|)
block|{
name|distbuf_prev
operator|=
name|distbuf
operator|+
literal|1
expr_stmt|;
name|distbuf_cur
operator|=
name|distbuf
operator|+
literal|1
operator|+
name|roi
operator|->
name|width
operator|+
literal|1
expr_stmt|;
block|}
else|else
block|{
name|distbuf_prev
operator|=
name|distbuf
operator|+
literal|1
operator|+
name|roi
operator|->
name|width
operator|+
literal|1
expr_stmt|;
name|distbuf_cur
operator|=
name|distbuf
operator|+
literal|1
expr_stmt|;
block|}
comment|/*  clear the current rows distbuffer */
name|memset
argument_list|(
name|distbuf_cur
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
operator|*
name|roi
operator|->
name|width
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
block|{
name|gfloat
name|dist_nw
init|=
name|MIN
argument_list|(
name|distbuf_cur
index|[
name|x
operator|-
literal|1
index|]
argument_list|,
name|distbuf_prev
index|[
name|x
index|]
argument_list|)
decl_stmt|;
name|gfloat
name|dist_se
init|=
name|MIN
argument_list|(
operator|(
name|roi
operator|->
name|width
operator|-
name|x
operator|-
literal|1
operator|)
argument_list|,
operator|(
name|roi
operator|->
name|height
operator|-
name|y
operator|-
literal|1
operator|)
argument_list|)
decl_stmt|;
name|gfloat
name|dist
init|=
name|MIN
argument_list|(
name|dist_se
argument_list|,
name|dist_nw
argument_list|)
decl_stmt|;
name|gfloat
name|frac
init|=
literal|1.0
decl_stmt|;
name|gint
name|k
decl_stmt|;
DECL|macro|EPSILON
define|#
directive|define
name|EPSILON
value|0.0001
comment|/*  This loop used to start at "k = (dist) ? (dist - 1) : 0"            *  and this comment suggested it might have to be changed to            *  "k = 0", but "k = 0" increases processing time significantly.            *            *  When porting this to float, i noticed that starting at            *  "dist - 2" gets rid of a lot of 8-bit artifacts, while starting            *  at "dist - 3" or smaller would introduce different artifacts.            *            *  Note that I didn't really understand the entire algorithm,            *  I just "blindly" ported it to float :) --mitch            */
comment|/* the idea here is to check the south-eastern "thick" diagonal            * along the already established accumulated minimum distance.            *            * it is easy to understand why it is sufficient to check            * the triangle to this diagonal (k=0), but in fact we can            * omit that, since this check has already been incorporated            * in the accumulated minimum distance of the previous pixels.            *            * Not sure however if this is implemented properly.            *      -- simon            */
for|for
control|(
name|k
operator|=
name|MAX
argument_list|(
name|dist
operator|-
literal|2
argument_list|,
literal|0
argument_list|)
init|;
name|k
operator|<=
name|dist
condition|;
name|k
operator|++
control|)
block|{
name|gint
name|x1
init|=
name|x
decl_stmt|;
name|gint
name|y1
init|=
name|y
operator|+
name|k
decl_stmt|;
while|while
condition|(
name|y1
operator|>=
name|y
condition|)
block|{
comment|/* FIXME: this should be much faster, it converts to                    * 32 bit rgba intermediately, bah...                    */
name|gegl_buffer_sample
argument_list|(
name|input
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|NULL
argument_list|,
operator|&
name|src
argument_list|,
name|input_format
argument_list|,
name|GEGL_SAMPLER_NEAREST
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|src
operator|<
name|EPSILON
condition|)
block|{
name|dist
operator|=
name|k
expr_stmt|;
break|break;
block|}
name|frac
operator|=
name|MIN
argument_list|(
name|frac
argument_list|,
name|src
argument_list|)
expr_stmt|;
name|x1
operator|++
expr_stmt|;
name|y1
operator|--
expr_stmt|;
block|}
block|}
if|if
condition|(
name|src
operator|>
name|EPSILON
condition|)
block|{
comment|/*  If dist_se != dist_nw use the previous frac                *   if it is less than the one found                */
if|if
condition|(
name|dist_se
operator|!=
name|dist
condition|)
block|{
name|gfloat
name|prev_frac
init|=
name|dist_nw
operator|-
name|dist
decl_stmt|;
if|if
condition|(
name|ABS
argument_list|(
name|prev_frac
operator|-
literal|1.0
argument_list|)
operator|<
name|EPSILON
condition|)
name|prev_frac
operator|=
literal|0.0
expr_stmt|;
name|frac
operator|=
name|MIN
argument_list|(
name|frac
argument_list|,
name|prev_frac
argument_list|)
expr_stmt|;
block|}
name|dist
operator|+=
literal|1.0
expr_stmt|;
block|}
name|distbuf_cur
index|[
name|x
index|]
operator|=
name|dist
operator|+
name|frac
expr_stmt|;
name|max_dist
operator|=
name|MAX
argument_list|(
name|max_dist
argument_list|,
name|distbuf_cur
index|[
name|x
index|]
argument_list|)
expr_stmt|;
block|}
comment|/*  set the dist row  */
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
literal|0
argument_list|,
name|output_format
argument_list|,
name|distbuf_cur
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|operation
argument_list|,
literal|"progress"
argument_list|,
operator|(
name|gdouble
operator|)
name|y
operator|/
name|roi
operator|->
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|distbuf
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_OPERATION_SHAPEBURST
argument_list|(
name|operation
argument_list|)
operator|->
name|normalize
operator|&&
name|max_dist
operator|>
literal|0.0
condition|)
block|{
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|output
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|GEGL_ACCESS_READWRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|gint
name|count
init|=
name|iter
operator|->
name|length
decl_stmt|;
name|gfloat
modifier|*
name|data
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
while|while
condition|(
name|count
operator|--
condition|)
operator|*
name|data
operator|++
operator|/=
name|max_dist
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

