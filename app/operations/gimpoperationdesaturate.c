begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationdesaturate.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpoperationdesaturate.h"
end_include

begin_include
include|#
directive|include
file|"gimpdesaturateconfig.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_operation_desaturate_prepare
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
name|gimp_operation_desaturate_process
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
DECL|function|G_DEFINE_TYPE (GimpOperationDesaturate,gimp_operation_desaturate,GIMP_TYPE_OPERATION_POINT_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationDesaturate
argument_list|,
argument|gimp_operation_desaturate
argument_list|,
argument|GIMP_TYPE_OPERATION_POINT_FILTER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_desaturate_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_desaturate_class_init
parameter_list|(
name|GimpOperationDesaturateClass
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
name|set_property
operator|=
name|gimp_operation_point_filter_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_point_filter_get_property
expr_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:desaturate"
argument_list|,
literal|"categories"
argument_list|,
literal|"color"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP Desaturate operation"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|operation_class
operator|->
name|prepare
operator|=
name|gimp_operation_desaturate_prepare
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_desaturate_process
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_OPERATION_POINT_FILTER_PROP_CONFIG
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"config"
argument_list|,
literal|"Config"
argument_list|,
literal|"The config object"
argument_list|,
name|GIMP_TYPE_DESATURATE_CONFIG
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
DECL|function|gimp_operation_desaturate_init (GimpOperationDesaturate * self)
name|gimp_operation_desaturate_init
parameter_list|(
name|GimpOperationDesaturate
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_desaturate_prepare (GeglOperation * operation)
name|gimp_operation_desaturate_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
block|{
name|GimpOperationPointFilter
modifier|*
name|point
init|=
name|GIMP_OPERATION_POINT_FILTER
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|GimpDesaturateConfig
modifier|*
name|config
init|=
name|GIMP_DESATURATE_CONFIG
argument_list|(
name|point
operator|->
name|config
argument_list|)
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
if|if
condition|(
name|config
operator|->
name|mode
operator|==
name|GIMP_DESATURATE_LUMINANCE
condition|)
block|{
name|format
operator|=
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
expr_stmt|;
block|}
name|gegl_operation_set_format
argument_list|(
name|operation
argument_list|,
literal|"input"
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|gegl_operation_set_format
argument_list|(
name|operation
argument_list|,
literal|"output"
argument_list|,
name|format
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_desaturate_process (GeglOperation * operation,void * in_buf,void * out_buf,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_desaturate_process
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
name|GimpOperationPointFilter
modifier|*
name|point
init|=
name|GIMP_OPERATION_POINT_FILTER
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|GimpDesaturateConfig
modifier|*
name|config
init|=
name|GIMP_DESATURATE_CONFIG
argument_list|(
name|point
operator|->
name|config
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
if|if
condition|(
operator|!
name|config
condition|)
return|return
name|FALSE
return|;
switch|switch
condition|(
name|config
operator|->
name|mode
condition|)
block|{
case|case
name|GIMP_DESATURATE_LIGHTNESS
case|:
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|min
decl_stmt|,
name|max
decl_stmt|,
name|value
decl_stmt|;
name|max
operator|=
name|MAX
argument_list|(
name|src
index|[
literal|0
index|]
argument_list|,
name|src
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|max
operator|=
name|MAX
argument_list|(
name|max
argument_list|,
name|src
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|src
index|[
literal|0
index|]
argument_list|,
name|src
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|min
argument_list|,
name|src
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|value
operator|=
operator|(
name|max
operator|+
name|min
operator|)
operator|/
literal|2
expr_stmt|;
name|dest
index|[
literal|0
index|]
operator|=
name|value
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|value
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|value
expr_stmt|;
name|dest
index|[
literal|3
index|]
operator|=
name|src
index|[
literal|3
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
break|break;
case|case
name|GIMP_DESATURATE_LUMA
case|:
case|case
name|GIMP_DESATURATE_LUMINANCE
case|:
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|value
init|=
name|GIMP_RGB_LUMINANCE
argument_list|(
name|src
index|[
literal|0
index|]
argument_list|,
name|src
index|[
literal|1
index|]
argument_list|,
name|src
index|[
literal|2
index|]
argument_list|)
decl_stmt|;
name|dest
index|[
literal|0
index|]
operator|=
name|value
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|value
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|value
expr_stmt|;
name|dest
index|[
literal|3
index|]
operator|=
name|src
index|[
literal|3
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
break|break;
case|case
name|GIMP_DESATURATE_AVERAGE
case|:
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|value
init|=
operator|(
name|src
index|[
literal|0
index|]
operator|+
name|src
index|[
literal|1
index|]
operator|+
name|src
index|[
literal|2
index|]
operator|)
operator|/
literal|3
decl_stmt|;
name|dest
index|[
literal|0
index|]
operator|=
name|value
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|value
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|value
expr_stmt|;
name|dest
index|[
literal|3
index|]
operator|=
name|src
index|[
literal|3
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
break|break;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

