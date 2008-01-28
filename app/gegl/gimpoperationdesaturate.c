begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationdesaturate.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationdesaturate.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29a0c3370103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_MODE
name|PROP_MODE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_operation_desaturate_get_property
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
name|gimp_operation_desaturate_set_property
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
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationDesaturate,gimp_operation_desaturate,GEGL_TYPE_OPERATION_POINT_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationDesaturate
argument_list|,
argument|gimp_operation_desaturate
argument_list|,
argument|GEGL_TYPE_OPERATION_POINT_FILTER
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
name|gimp_operation_desaturate_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_desaturate_get_property
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_desaturate_process
expr_stmt|;
name|gegl_operation_class_set_name
argument_list|(
name|operation_class
argument_list|,
literal|"gimp-desaturate"
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_MODE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"mode"
argument_list|,
literal|"Mode"
argument_list|,
literal|"The desaturate mode"
argument_list|,
name|GIMP_TYPE_DESATURATE_MODE
argument_list|,
name|GIMP_DESATURATE_LIGHTNESS
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
DECL|function|gimp_operation_desaturate_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_desaturate_get_property
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
name|GimpOperationDesaturate
modifier|*
name|self
init|=
name|GIMP_OPERATION_DESATURATE
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
name|PROP_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|mode
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
DECL|function|gimp_operation_desaturate_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_desaturate_set_property
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
name|GimpOperationDesaturate
modifier|*
name|self
init|=
name|GIMP_OPERATION_DESATURATE
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
name|PROP_MODE
case|:
name|self
operator|->
name|mode
operator|=
name|g_value_get_enum
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
name|gboolean
DECL|function|gimp_operation_desaturate_process (GeglOperation * operation,void * in_buf,void * out_buf,glong samples)
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
parameter_list|)
block|{
name|GimpOperationDesaturate
modifier|*
name|self
init|=
name|GIMP_OPERATION_DESATURATE
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
name|glong
name|sample
decl_stmt|;
for|for
control|(
name|sample
operator|=
literal|0
init|;
name|sample
operator|<
name|samples
condition|;
name|sample
operator|++
control|)
block|{
name|gfloat
name|value
init|=
literal|0.0
decl_stmt|;
switch|switch
condition|(
name|self
operator|->
name|mode
condition|)
block|{
case|case
name|GIMP_DESATURATE_LIGHTNESS
case|:
block|{
name|gfloat
name|min
decl_stmt|,
name|max
decl_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: cant use FOO_PIX but have no constants from babl???
endif|#
directive|endif
name|max
operator|=
name|MAX
argument_list|(
name|src
index|[
name|RED_PIX
index|]
argument_list|,
name|src
index|[
name|GREEN_PIX
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
name|BLUE_PIX
index|]
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|src
index|[
name|RED_PIX
index|]
argument_list|,
name|src
index|[
name|GREEN_PIX
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
name|BLUE_PIX
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
block|}
break|break;
case|case
name|GIMP_DESATURATE_LUMINOSITY
case|:
name|value
operator|=
name|GIMP_RGB_LUMINANCE
argument_list|(
name|src
index|[
name|RED_PIX
index|]
argument_list|,
name|src
index|[
name|GREEN_PIX
index|]
argument_list|,
name|src
index|[
name|BLUE_PIX
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_DESATURATE_AVERAGE
case|:
name|value
operator|=
operator|(
name|src
index|[
name|RED_PIX
index|]
operator|+
name|src
index|[
name|GREEN_PIX
index|]
operator|+
name|src
index|[
name|BLUE_PIX
index|]
operator|)
operator|/
literal|3
expr_stmt|;
break|break;
block|}
name|dest
index|[
name|RED_PIX
index|]
operator|=
name|value
expr_stmt|;
name|dest
index|[
name|GREEN_PIX
index|]
operator|=
name|value
expr_stmt|;
name|dest
index|[
name|BLUE_PIX
index|]
operator|=
name|value
expr_stmt|;
name|dest
index|[
name|ALPHA_PIX
index|]
operator|=
name|src
index|[
name|ALPHA_PIX
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

