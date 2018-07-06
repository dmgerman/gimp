begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationsemiflatten.c  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  * Ported from the semi-flatten plug-in  * by Adam D. Moss, adam@foxbox.org.  1998/01/27  */
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
file|"operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationsemiflatten.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a1970350103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_COLOR
name|PROP_COLOR
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_operation_semi_flatten_get_property
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
name|gimp_operation_semi_flatten_set_property
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
name|gimp_operation_semi_flatten_prepare
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
name|gimp_operation_semi_flatten_process
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
DECL|function|G_DEFINE_TYPE (GimpOperationSemiFlatten,gimp_operation_semi_flatten,GEGL_TYPE_OPERATION_POINT_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationSemiFlatten
argument_list|,
argument|gimp_operation_semi_flatten
argument_list|,
argument|GEGL_TYPE_OPERATION_POINT_FILTER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_semi_flatten_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_semi_flatten_class_init
parameter_list|(
name|GimpOperationSemiFlattenClass
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
name|GimpRGB
name|white
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_operation_semi_flatten_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_semi_flatten_get_property
expr_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:semi-flatten"
argument_list|,
literal|"categories"
argument_list|,
literal|"color"
argument_list|,
literal|"description"
argument_list|,
name|_
argument_list|(
literal|"Replace partial transparency with a color"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|operation_class
operator|->
name|prepare
operator|=
name|gimp_operation_semi_flatten_prepare
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_semi_flatten_process
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|white
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_COLOR
argument_list|,
name|gimp_param_spec_rgb
argument_list|(
literal|"color"
argument_list|,
literal|"Color"
argument_list|,
literal|"The color"
argument_list|,
name|FALSE
argument_list|,
operator|&
name|white
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
DECL|function|gimp_operation_semi_flatten_init (GimpOperationSemiFlatten * self)
name|gimp_operation_semi_flatten_init
parameter_list|(
name|GimpOperationSemiFlatten
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_semi_flatten_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_semi_flatten_get_property
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
name|GimpOperationSemiFlatten
modifier|*
name|self
init|=
name|GIMP_OPERATION_SEMI_FLATTEN
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
name|PROP_COLOR
case|:
name|gimp_value_set_rgb
argument_list|(
name|value
argument_list|,
operator|&
name|self
operator|->
name|color
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
DECL|function|gimp_operation_semi_flatten_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_semi_flatten_set_property
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
name|GimpOperationSemiFlatten
modifier|*
name|self
init|=
name|GIMP_OPERATION_SEMI_FLATTEN
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
name|PROP_COLOR
case|:
name|gimp_value_get_rgb
argument_list|(
name|value
argument_list|,
operator|&
name|self
operator|->
name|color
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
DECL|function|gimp_operation_semi_flatten_prepare (GeglOperation * operation)
name|gimp_operation_semi_flatten_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
block|{
specifier|const
name|Babl
modifier|*
name|space
init|=
name|gegl_operation_get_source_space
argument_list|(
name|operation
argument_list|,
literal|"input"
argument_list|)
decl_stmt|;
name|gegl_operation_set_format
argument_list|(
name|operation
argument_list|,
literal|"input"
argument_list|,
name|babl_format_with_space
argument_list|(
literal|"RGBA float"
argument_list|,
name|space
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_operation_set_format
argument_list|(
name|operation
argument_list|,
literal|"output"
argument_list|,
name|babl_format_with_space
argument_list|(
literal|"RGBA float"
argument_list|,
name|space
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_semi_flatten_process (GeglOperation * operation,void * in_buf,void * out_buf,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_semi_flatten_process
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
name|GimpOperationSemiFlatten
modifier|*
name|self
init|=
name|GIMP_OPERATION_SEMI_FLATTEN
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
name|gfloat
name|alpha
init|=
name|src
index|[
name|ALPHA
index|]
decl_stmt|;
if|if
condition|(
name|alpha
operator|<=
literal|0.0
operator|||
name|alpha
operator|>=
literal|1.0
condition|)
block|{
name|dest
index|[
name|RED
index|]
operator|=
name|src
index|[
name|RED
index|]
expr_stmt|;
name|dest
index|[
name|GREEN
index|]
operator|=
name|src
index|[
name|GREEN
index|]
expr_stmt|;
name|dest
index|[
name|BLUE
index|]
operator|=
name|src
index|[
name|BLUE
index|]
expr_stmt|;
name|dest
index|[
name|ALPHA
index|]
operator|=
name|alpha
expr_stmt|;
block|}
else|else
block|{
name|dest
index|[
name|RED
index|]
operator|=
name|src
index|[
name|RED
index|]
operator|*
name|alpha
operator|+
name|self
operator|->
name|color
operator|.
name|r
operator|*
operator|(
literal|1.0
operator|-
name|alpha
operator|)
expr_stmt|;
name|dest
index|[
name|GREEN
index|]
operator|=
name|src
index|[
name|GREEN
index|]
operator|*
name|alpha
operator|+
name|self
operator|->
name|color
operator|.
name|g
operator|*
operator|(
literal|1.0
operator|-
name|alpha
operator|)
expr_stmt|;
name|dest
index|[
name|BLUE
index|]
operator|=
name|src
index|[
name|BLUE
index|]
operator|*
name|alpha
operator|+
name|self
operator|->
name|color
operator|.
name|b
operator|*
operator|(
literal|1.0
operator|-
name|alpha
operator|)
expr_stmt|;
name|dest
index|[
name|ALPHA
index|]
operator|=
literal|1.0
expr_stmt|;
block|}
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

