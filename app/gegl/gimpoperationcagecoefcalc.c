begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpoperationcagecoefcalc.c  * Copyright (C) 2010 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gegl-buffer-iterator.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcagecoefcalc.h"
end_include

begin_include
include|#
directive|include
file|"gimpcageconfig.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_operation_cage_coef_calc_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_operation_cage_coef_calc_finalize
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
name|gimp_operation_cage_coef_calc_get_property
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
name|gimp_operation_cage_coef_calc_set_property
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
name|gimp_operation_cage_coef_calc_get_bounding_box
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
name|gimp_operation_cage_coef_calc_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|GeglBuffer
modifier|*
name|output
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationCageCoefCalc,gimp_operation_cage_coef_calc,GEGL_TYPE_OPERATION_SOURCE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationCageCoefCalc
argument_list|,
argument|gimp_operation_cage_coef_calc
argument_list|,
argument|GEGL_TYPE_OPERATION_SOURCE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_cage_coef_calc_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_cage_coef_calc_class_init
parameter_list|(
name|GimpOperationCageCoefCalcClass
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
name|GeglOperationSourceClass
modifier|*
name|source_class
init|=
name|GEGL_OPERATION_SOURCE_CLASS
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
name|operation_class
operator|->
name|name
operator|=
literal|"gimp:cage-coef-calc"
expr_stmt|;
name|operation_class
operator|->
name|categories
operator|=
literal|"transform"
expr_stmt|;
name|operation_class
operator|->
name|description
operator|=
literal|"GIMP cage transform coefficient calc"
expr_stmt|;
name|operation_class
operator|->
name|prepare
operator|=
name|gimp_operation_cage_coef_calc_prepare
expr_stmt|;
name|operation_class
operator|->
name|get_bounding_box
operator|=
name|gimp_operation_cage_coef_calc_get_bounding_box
expr_stmt|;
name|operation_class
operator|->
name|no_cache
operator|=
name|FALSE
expr_stmt|;
name|operation_class
operator|->
name|get_cached_region
operator|=
name|NULL
expr_stmt|;
name|source_class
operator|->
name|process
operator|=
name|gimp_operation_cage_coef_calc_process
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_cage_coef_calc_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_operation_cage_coef_calc_set_property
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_operation_cage_coef_calc_finalize
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_OPERATION_CAGE_COEF_CALC_PROP_CONFIG
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"config"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CAGE_CONFIG
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
DECL|function|gimp_operation_cage_coef_calc_init (GimpOperationCageCoefCalc * self)
name|gimp_operation_cage_coef_calc_init
parameter_list|(
name|GimpOperationCageCoefCalc
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_cage_coef_calc_prepare (GeglOperation * operation)
name|gimp_operation_cage_coef_calc_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
block|{
name|GimpOperationCageCoefCalc
modifier|*
name|occc
init|=
name|GIMP_OPERATION_CAGE_COEF_CALC
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|GimpCageConfig
modifier|*
name|config
init|=
name|GIMP_CAGE_CONFIG
argument_list|(
name|occc
operator|->
name|config
argument_list|)
decl_stmt|;
name|gegl_operation_set_format
argument_list|(
name|operation
argument_list|,
literal|"output"
argument_list|,
name|babl_format_n
argument_list|(
name|babl_type
argument_list|(
literal|"float"
argument_list|)
argument_list|,
literal|2
operator|*
name|gimp_cage_config_get_n_points
argument_list|(
name|config
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_cage_coef_calc_finalize (GObject * object)
name|gimp_operation_cage_coef_calc_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpOperationCageCoefCalc
modifier|*
name|self
init|=
name|GIMP_OPERATION_CAGE_COEF_CALC
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
DECL|function|gimp_operation_cage_coef_calc_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_cage_coef_calc_get_property
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
name|GimpOperationCageCoefCalc
modifier|*
name|self
init|=
name|GIMP_OPERATION_CAGE_COEF_CALC
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
name|GIMP_OPERATION_CAGE_COEF_CALC_PROP_CONFIG
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
DECL|function|gimp_operation_cage_coef_calc_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_cage_coef_calc_set_property
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
name|GimpOperationCageCoefCalc
modifier|*
name|self
init|=
name|GIMP_OPERATION_CAGE_COEF_CALC
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
name|GIMP_OPERATION_CAGE_COEF_CALC_PROP_CONFIG
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
name|gboolean
DECL|function|gimp_operation_cage_coef_calc_is_on_straight (GimpVector2 * d1,GimpVector2 * d2,GimpVector2 * p)
name|gimp_operation_cage_coef_calc_is_on_straight
parameter_list|(
name|GimpVector2
modifier|*
name|d1
parameter_list|,
name|GimpVector2
modifier|*
name|d2
parameter_list|,
name|GimpVector2
modifier|*
name|p
parameter_list|)
block|{
name|GimpVector2
name|v1
decl_stmt|,
name|v2
decl_stmt|;
name|gfloat
name|deter
decl_stmt|;
name|v1
operator|.
name|x
operator|=
name|p
operator|->
name|x
operator|-
name|d1
operator|->
name|x
expr_stmt|;
name|v1
operator|.
name|y
operator|=
name|p
operator|->
name|y
operator|-
name|d1
operator|->
name|y
expr_stmt|;
name|v2
operator|.
name|x
operator|=
name|d2
operator|->
name|x
operator|-
name|d1
operator|->
name|x
expr_stmt|;
name|v2
operator|.
name|y
operator|=
name|d2
operator|->
name|y
operator|-
name|d1
operator|->
name|y
expr_stmt|;
name|gimp_vector2_normalize
argument_list|(
operator|&
name|v1
argument_list|)
expr_stmt|;
name|gimp_vector2_normalize
argument_list|(
operator|&
name|v2
argument_list|)
expr_stmt|;
name|deter
operator|=
name|v1
operator|.
name|x
operator|*
name|v2
operator|.
name|y
operator|-
name|v2
operator|.
name|x
operator|*
name|v1
operator|.
name|y
expr_stmt|;
return|return
operator|(
name|deter
operator|<
literal|0.000000001
operator|)
operator|&&
operator|(
name|deter
operator|>
operator|-
literal|0.000000001
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|GeglRectangle
DECL|function|gimp_operation_cage_coef_calc_get_bounding_box (GeglOperation * operation)
name|gimp_operation_cage_coef_calc_get_bounding_box
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
block|{
name|GimpOperationCageCoefCalc
modifier|*
name|occc
init|=
name|GIMP_OPERATION_CAGE_COEF_CALC
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|GimpCageConfig
modifier|*
name|config
init|=
name|GIMP_CAGE_CONFIG
argument_list|(
name|occc
operator|->
name|config
argument_list|)
decl_stmt|;
return|return
name|gimp_cage_config_get_bounding_box
argument_list|(
name|config
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_cage_coef_calc_process (GeglOperation * operation,GeglBuffer * output,const GeglRectangle * roi)
name|gimp_operation_cage_coef_calc_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|GeglBuffer
modifier|*
name|output
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
block|{
name|GimpOperationCageCoefCalc
modifier|*
name|occc
init|=
name|GIMP_OPERATION_CAGE_COEF_CALC
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|GimpCageConfig
modifier|*
name|config
init|=
name|GIMP_CAGE_CONFIG
argument_list|(
name|occc
operator|->
name|config
argument_list|)
decl_stmt|;
name|Babl
modifier|*
name|format
init|=
name|babl_format_n
argument_list|(
name|babl_type
argument_list|(
literal|"float"
argument_list|)
argument_list|,
literal|2
operator|*
name|gimp_cage_config_get_n_points
argument_list|(
name|config
argument_list|)
argument_list|)
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|it
decl_stmt|;
name|guint
name|n_cage_vertices
decl_stmt|;
name|GimpCagePoint
modifier|*
name|current
decl_stmt|,
modifier|*
name|last
decl_stmt|;
if|if
condition|(
operator|!
name|config
condition|)
return|return
name|FALSE
return|;
name|n_cage_vertices
operator|=
name|gimp_cage_config_get_n_points
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|it
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|output
argument_list|,
name|roi
argument_list|,
name|format
argument_list|,
name|GEGL_BUFFER_READWRITE
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|it
argument_list|)
condition|)
block|{
comment|/* iterate inside the roi */
name|gint
name|n_pixels
init|=
name|it
operator|->
name|length
decl_stmt|;
name|gint
name|x
init|=
name|it
operator|->
name|roi
operator|->
name|x
decl_stmt|;
comment|/* initial x                   */
name|gint
name|y
init|=
name|it
operator|->
name|roi
operator|->
name|y
decl_stmt|;
comment|/*           and y coordinates */
name|gint
name|j
decl_stmt|;
name|gfloat
modifier|*
name|coef
init|=
name|it
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
while|while
condition|(
name|n_pixels
operator|--
condition|)
block|{
if|if
condition|(
name|gimp_cage_config_point_inside
argument_list|(
name|config
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
condition|)
block|{
name|last
operator|=
operator|&
operator|(
name|g_array_index
argument_list|(
name|config
operator|->
name|cage_points
argument_list|,
name|GimpCagePoint
argument_list|,
literal|0
argument_list|)
operator|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|n_cage_vertices
condition|;
name|j
operator|++
control|)
block|{
name|GimpVector2
name|v1
decl_stmt|,
name|v2
decl_stmt|,
name|a
decl_stmt|,
name|b
decl_stmt|,
name|p
decl_stmt|;
name|gdouble
name|BA
decl_stmt|,
name|SRT
decl_stmt|,
name|L0
decl_stmt|,
name|L1
decl_stmt|,
name|A0
decl_stmt|,
name|A1
decl_stmt|,
name|A10
decl_stmt|,
name|L10
decl_stmt|,
name|Q
decl_stmt|,
name|S
decl_stmt|,
name|R
decl_stmt|,
name|absa
decl_stmt|;
name|current
operator|=
operator|&
operator|(
name|g_array_index
argument_list|(
name|config
operator|->
name|cage_points
argument_list|,
name|GimpCagePoint
argument_list|,
operator|(
name|j
operator|+
literal|1
operator|)
operator|%
name|n_cage_vertices
argument_list|)
operator|)
expr_stmt|;
name|v1
operator|=
name|last
operator|->
name|src_point
expr_stmt|;
name|v2
operator|=
name|current
operator|->
name|src_point
expr_stmt|;
name|p
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|p
operator|.
name|y
operator|=
name|y
expr_stmt|;
name|a
operator|.
name|x
operator|=
name|v2
operator|.
name|x
operator|-
name|v1
operator|.
name|x
expr_stmt|;
name|a
operator|.
name|y
operator|=
name|v2
operator|.
name|y
operator|-
name|v1
operator|.
name|y
expr_stmt|;
name|absa
operator|=
name|gimp_vector2_length
argument_list|(
operator|&
name|a
argument_list|)
expr_stmt|;
name|b
operator|.
name|x
operator|=
name|v1
operator|.
name|x
operator|-
name|x
expr_stmt|;
name|b
operator|.
name|y
operator|=
name|v1
operator|.
name|y
operator|-
name|y
expr_stmt|;
name|Q
operator|=
name|a
operator|.
name|x
operator|*
name|a
operator|.
name|x
operator|+
name|a
operator|.
name|y
operator|*
name|a
operator|.
name|y
expr_stmt|;
name|S
operator|=
name|b
operator|.
name|x
operator|*
name|b
operator|.
name|x
operator|+
name|b
operator|.
name|y
operator|*
name|b
operator|.
name|y
expr_stmt|;
name|R
operator|=
literal|2.0
operator|*
operator|(
name|a
operator|.
name|x
operator|*
name|b
operator|.
name|x
operator|+
name|a
operator|.
name|y
operator|*
name|b
operator|.
name|y
operator|)
expr_stmt|;
name|BA
operator|=
name|b
operator|.
name|x
operator|*
name|a
operator|.
name|y
operator|-
name|b
operator|.
name|y
operator|*
name|a
operator|.
name|x
expr_stmt|;
name|SRT
operator|=
name|sqrt
argument_list|(
literal|4.0
operator|*
name|S
operator|*
name|Q
operator|-
name|R
operator|*
name|R
argument_list|)
expr_stmt|;
name|L0
operator|=
name|log
argument_list|(
name|S
argument_list|)
expr_stmt|;
name|L1
operator|=
name|log
argument_list|(
name|S
operator|+
name|Q
operator|+
name|R
argument_list|)
expr_stmt|;
name|A0
operator|=
name|atan2
argument_list|(
name|R
argument_list|,
name|SRT
argument_list|)
operator|/
name|SRT
expr_stmt|;
name|A1
operator|=
name|atan2
argument_list|(
literal|2.0
operator|*
name|Q
operator|+
name|R
argument_list|,
name|SRT
argument_list|)
operator|/
name|SRT
expr_stmt|;
name|A10
operator|=
name|A1
operator|-
name|A0
expr_stmt|;
name|L10
operator|=
name|L1
operator|-
name|L0
expr_stmt|;
comment|/* edge coef */
name|coef
index|[
name|j
operator|+
name|n_cage_vertices
index|]
operator|=
operator|(
operator|-
name|absa
operator|/
operator|(
literal|4.0
operator|*
name|M_PI
operator|)
operator|)
operator|*
operator|(
operator|(
literal|4.0
operator|*
name|S
operator|-
operator|(
name|R
operator|*
name|R
operator|)
operator|/
name|Q
operator|)
operator|*
name|A10
operator|+
operator|(
name|R
operator|/
operator|(
literal|2.0
operator|*
name|Q
operator|)
operator|)
operator|*
name|L10
operator|+
name|L1
operator|-
literal|2.0
operator|)
expr_stmt|;
if|if
condition|(
name|isnan
argument_list|(
name|coef
index|[
name|j
operator|+
name|n_cage_vertices
index|]
argument_list|)
condition|)
block|{
name|coef
index|[
name|j
operator|+
name|n_cage_vertices
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
comment|/* vertice coef */
if|if
condition|(
operator|!
name|gimp_operation_cage_coef_calc_is_on_straight
argument_list|(
operator|&
name|v1
argument_list|,
operator|&
name|v2
argument_list|,
operator|&
name|p
argument_list|)
condition|)
block|{
name|coef
index|[
name|j
index|]
operator|+=
operator|(
name|BA
operator|/
operator|(
literal|2.0
operator|*
name|M_PI
operator|)
operator|)
operator|*
operator|(
name|L10
operator|/
operator|(
literal|2.0
operator|*
name|Q
operator|)
operator|-
name|A10
operator|*
operator|(
literal|2.0
operator|+
name|R
operator|/
name|Q
operator|)
operator|)
expr_stmt|;
name|coef
index|[
operator|(
name|j
operator|+
literal|1
operator|)
operator|%
name|n_cage_vertices
index|]
operator|-=
operator|(
name|BA
operator|/
operator|(
literal|2.0
operator|*
name|M_PI
operator|)
operator|)
operator|*
operator|(
name|L10
operator|/
operator|(
literal|2.0
operator|*
name|Q
operator|)
operator|-
name|A10
operator|*
operator|(
name|R
operator|/
name|Q
operator|)
operator|)
expr_stmt|;
block|}
name|last
operator|=
name|current
expr_stmt|;
block|}
block|}
name|coef
operator|+=
literal|2
operator|*
name|n_cage_vertices
expr_stmt|;
comment|/* update x and y coordinates */
name|x
operator|++
expr_stmt|;
if|if
condition|(
name|x
operator|>=
operator|(
name|it
operator|->
name|roi
operator|->
name|x
operator|+
name|it
operator|->
name|roi
operator|->
name|width
operator|)
condition|)
block|{
name|x
operator|=
name|it
operator|->
name|roi
operator|->
name|x
expr_stmt|;
name|y
operator|++
expr_stmt|;
block|}
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

