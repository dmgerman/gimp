begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationcurves.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcurvesconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcurves.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c88f68b0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONFIG
name|PROP_CONFIG
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_operation_curves_finalize
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
name|gimp_operation_curves_get_property
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
name|gimp_operation_curves_set_property
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
name|gimp_operation_curves_process
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
DECL|function|G_DEFINE_TYPE (GimpOperationCurves,gimp_operation_curves,GEGL_TYPE_OPERATION_POINT_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationCurves
argument_list|,
argument|gimp_operation_curves
argument_list|,
argument|GEGL_TYPE_OPERATION_POINT_FILTER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_curves_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_curves_class_init
parameter_list|(
name|GimpOperationCurvesClass
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
name|gimp_operation_curves_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_operation_curves_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_curves_get_property
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_curves_process
expr_stmt|;
name|gegl_operation_class_set_name
argument_list|(
name|operation_class
argument_list|,
literal|"gimp-curves"
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONFIG
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"config"
argument_list|,
literal|"Config"
argument_list|,
literal|"The config object"
argument_list|,
name|GIMP_TYPE_CURVES_CONFIG
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
DECL|function|gimp_operation_curves_init (GimpOperationCurves * self)
name|gimp_operation_curves_init
parameter_list|(
name|GimpOperationCurves
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_curves_finalize (GObject * object)
name|gimp_operation_curves_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpOperationCurves
modifier|*
name|self
init|=
name|GIMP_OPERATION_CURVES
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|self
operator|->
name|config
condition|)
block|{
name|g_object_unref
argument_list|(
name|self
operator|->
name|config
argument_list|)
expr_stmt|;
name|self
operator|->
name|config
operator|=
name|NULL
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
DECL|function|gimp_operation_curves_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_curves_get_property
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
name|GimpOperationCurves
modifier|*
name|self
init|=
name|GIMP_OPERATION_CURVES
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
name|PROP_CONFIG
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|config
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
DECL|function|gimp_operation_curves_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_curves_set_property
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
name|GimpOperationCurves
modifier|*
name|self
init|=
name|GIMP_OPERATION_CURVES
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
name|PROP_CONFIG
case|:
if|if
condition|(
name|self
operator|->
name|config
condition|)
name|g_object_unref
argument_list|(
name|self
operator|->
name|config
argument_list|)
expr_stmt|;
name|self
operator|->
name|config
operator|=
name|g_value_dup_object
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
specifier|inline
name|gdouble
DECL|function|gimp_operation_curves_map (gdouble value,GimpCurve * curve)
name|gimp_operation_curves_map
parameter_list|(
name|gdouble
name|value
parameter_list|,
name|GimpCurve
modifier|*
name|curve
parameter_list|)
block|{
if|if
condition|(
name|value
operator|<
literal|0.0
condition|)
block|{
name|value
operator|=
name|curve
operator|->
name|curve
index|[
literal|0
index|]
operator|/
literal|255.0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|value
operator|>=
literal|1.0
condition|)
block|{
name|value
operator|=
name|curve
operator|->
name|curve
index|[
literal|255
index|]
operator|/
literal|255.0
expr_stmt|;
block|}
else|else
comment|/* interpolate the curve */
block|{
name|gint
name|index
init|=
name|floor
argument_list|(
name|value
operator|*
literal|255.0
argument_list|)
decl_stmt|;
name|gdouble
name|f
init|=
name|value
operator|*
literal|255.0
operator|-
name|index
decl_stmt|;
name|value
operator|=
operator|(
operator|(
literal|1.0
operator|-
name|f
operator|)
operator|*
name|curve
operator|->
name|curve
index|[
name|index
index|]
operator|+
name|f
operator|*
name|curve
operator|->
name|curve
index|[
name|index
operator|+
literal|1
index|]
operator|)
operator|/
literal|255.0
expr_stmt|;
block|}
return|return
name|value
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_curves_process (GeglOperation * operation,void * in_buf,void * out_buf,glong samples)
name|gimp_operation_curves_process
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
name|GimpOperationCurves
modifier|*
name|self
init|=
name|GIMP_OPERATION_CURVES
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|GimpCurvesConfig
modifier|*
name|config
init|=
name|self
operator|->
name|config
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
if|if
condition|(
operator|!
name|config
condition|)
return|return
name|FALSE
return|;
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
name|gint
name|channel
decl_stmt|;
for|for
control|(
name|channel
operator|=
literal|0
init|;
name|channel
operator|<
literal|4
condition|;
name|channel
operator|++
control|)
block|{
name|gdouble
name|value
decl_stmt|;
name|value
operator|=
name|gimp_operation_curves_map
argument_list|(
name|src
index|[
name|channel
index|]
argument_list|,
name|config
operator|->
name|curve
index|[
name|channel
operator|+
literal|1
index|]
argument_list|)
expr_stmt|;
comment|/* don't apply the overall curve to the alpha channel */
if|if
condition|(
name|channel
operator|!=
name|ALPHA_PIX
condition|)
name|value
operator|=
name|gimp_operation_curves_map
argument_list|(
name|value
argument_list|,
name|config
operator|->
name|curve
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|dest
index|[
name|channel
index|]
operator|=
name|value
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

