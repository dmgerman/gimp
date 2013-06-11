begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationequalize.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimphistogram.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationequalize.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28b480a40103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_HISTOGRAM
name|PROP_HISTOGRAM
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_operation_equalize_finalize
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
name|gimp_operation_equalize_get_property
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
name|gimp_operation_equalize_set_property
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
name|gboolean
name|gimp_operation_equalize_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|void
modifier|*
name|in_buf
parameter_list|,
name|void
modifier|*
name|out_buf
parameter_list|,
name|glong
name|samples
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
DECL|function|G_DEFINE_TYPE (GimpOperationEqualize,gimp_operation_equalize,GIMP_TYPE_OPERATION_POINT_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationEqualize
argument_list|,
argument|gimp_operation_equalize
argument_list|,
argument|GIMP_TYPE_OPERATION_POINT_FILTER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_equalize_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_equalize_class_init
parameter_list|(
name|GimpOperationEqualizeClass
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
name|GeglOperationPointFilterClass
modifier|*
name|point_class
init|=
name|GEGL_OPERATION_POINT_FILTER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_operation_equalize_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_operation_equalize_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_equalize_get_property
expr_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:equalize"
argument_list|,
literal|"categories"
argument_list|,
literal|"color"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP Equalize operation"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_equalize_process
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_HISTOGRAM
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"histogram"
argument_list|,
literal|"Histogram"
argument_list|,
literal|"The histogram"
argument_list|,
name|GIMP_TYPE_HISTOGRAM
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_equalize_init (GimpOperationEqualize * self)
name|gimp_operation_equalize_init
parameter_list|(
name|GimpOperationEqualize
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_equalize_finalize (GObject * object)
name|gimp_operation_equalize_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpOperationEqualize
modifier|*
name|self
init|=
name|GIMP_OPERATION_EQUALIZE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|self
operator|->
name|histogram
condition|)
block|{
name|g_object_unref
argument_list|(
name|self
operator|->
name|histogram
argument_list|)
expr_stmt|;
name|self
operator|->
name|histogram
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_equalize_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_equalize_get_property
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
name|GimpOperationEqualize
modifier|*
name|self
init|=
name|GIMP_OPERATION_EQUALIZE
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
name|PROP_HISTOGRAM
case|:
name|g_value_set_pointer
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|histogram
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
DECL|function|gimp_operation_equalize_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_equalize_set_property
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
name|GimpOperationEqualize
modifier|*
name|self
init|=
name|GIMP_OPERATION_EQUALIZE
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
name|PROP_HISTOGRAM
case|:
if|if
condition|(
name|self
operator|->
name|histogram
condition|)
name|g_object_unref
argument_list|(
name|self
operator|->
name|histogram
argument_list|)
expr_stmt|;
name|self
operator|->
name|histogram
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|self
operator|->
name|histogram
condition|)
block|{
name|gdouble
name|pixels
decl_stmt|;
name|gint
name|max
decl_stmt|;
name|gint
name|k
decl_stmt|;
name|pixels
operator|=
name|gimp_histogram_get_count
argument_list|(
name|self
operator|->
name|histogram
argument_list|,
name|GIMP_HISTOGRAM_VALUE
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_histogram_n_channels
argument_list|(
name|self
operator|->
name|histogram
argument_list|)
operator|==
literal|1
operator|||
name|gimp_histogram_n_channels
argument_list|(
name|self
operator|->
name|histogram
argument_list|)
operator|==
literal|2
condition|)
name|max
operator|=
literal|1
expr_stmt|;
else|else
name|max
operator|=
literal|3
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
literal|3
condition|;
name|k
operator|++
control|)
block|{
name|gdouble
name|sum
init|=
literal|0
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
literal|256
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|histi
decl_stmt|;
name|histi
operator|=
name|gimp_histogram_get_channel
argument_list|(
name|self
operator|->
name|histogram
argument_list|,
name|k
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|sum
operator|+=
name|histi
expr_stmt|;
name|self
operator|->
name|part
index|[
name|k
index|]
index|[
name|i
index|]
operator|=
name|sum
operator|/
name|pixels
expr_stmt|;
if|if
condition|(
name|max
operator|==
literal|1
condition|)
block|{
name|self
operator|->
name|part
index|[
literal|1
index|]
index|[
name|i
index|]
operator|=
name|self
operator|->
name|part
index|[
literal|0
index|]
index|[
name|i
index|]
expr_stmt|;
name|self
operator|->
name|part
index|[
literal|2
index|]
index|[
name|i
index|]
operator|=
name|self
operator|->
name|part
index|[
literal|0
index|]
index|[
name|i
index|]
expr_stmt|;
block|}
block|}
block|}
block|}
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
specifier|inline
name|float
DECL|function|gimp_operation_equalize_map (GimpOperationEqualize * self,gint component,gfloat value)
name|gimp_operation_equalize_map
parameter_list|(
name|GimpOperationEqualize
modifier|*
name|self
parameter_list|,
name|gint
name|component
parameter_list|,
name|gfloat
name|value
parameter_list|)
block|{
name|gint
name|index
init|=
operator|(
name|gint
operator|)
name|CLAMP
argument_list|(
name|value
operator|*
literal|255.0
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
decl_stmt|;
return|return
name|self
operator|->
name|part
index|[
name|component
index|]
index|[
name|index
index|]
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_equalize_process (GeglOperation * operation,void * in_buf,void * out_buf,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_equalize_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|void
modifier|*
name|in_buf
parameter_list|,
name|void
modifier|*
name|out_buf
parameter_list|,
name|glong
name|samples
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
name|GimpOperationEqualize
modifier|*
name|self
init|=
name|GIMP_OPERATION_EQUALIZE
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|gfloat
modifier|*
name|src
init|=
name|in_buf
decl_stmt|;
name|gfloat
modifier|*
name|dest
init|=
name|out_buf
decl_stmt|;
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|dest
index|[
name|RED
index|]
operator|=
name|gimp_operation_equalize_map
argument_list|(
name|self
argument_list|,
name|RED
argument_list|,
name|src
index|[
name|RED
index|]
argument_list|)
expr_stmt|;
name|dest
index|[
name|GREEN
index|]
operator|=
name|gimp_operation_equalize_map
argument_list|(
name|self
argument_list|,
name|GREEN
argument_list|,
name|src
index|[
name|GREEN
index|]
argument_list|)
expr_stmt|;
name|dest
index|[
name|BLUE
index|]
operator|=
name|gimp_operation_equalize_map
argument_list|(
name|self
argument_list|,
name|BLUE
argument_list|,
name|src
index|[
name|BLUE
index|]
argument_list|)
expr_stmt|;
name|dest
index|[
name|ALPHA
index|]
operator|=
name|src
index|[
name|ALPHA
index|]
expr_stmt|;
name|src
operator|+=
literal|4
expr_stmt|;
name|dest
operator|+=
literal|4
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

