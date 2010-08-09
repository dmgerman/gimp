begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpoperationcage.c  * Copyright (C) 2010 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|<gegl-buffer-iterator.h>
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
file|"gimpoperationcagetransform.h"
end_include

begin_include
include|#
directive|include
file|"gimpcageconfig.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_operation_cage_transform_finalize
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
name|gimp_operation_cage_transform_get_property
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
name|gimp_operation_cage_transform_set_property
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
name|gimp_operation_cage_transform_prepare
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
name|gimp_operation_cage_transform_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|GeglBuffer
modifier|*
name|in_buf
parameter_list|,
name|GeglBuffer
modifier|*
name|aux_buf
parameter_list|,
name|GeglBuffer
modifier|*
name|out_buf
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
name|gimp_operation_cage_transform_interpolate_source_coords_recurs
parameter_list|(
name|GimpOperationCageTransform
modifier|*
name|oct
parameter_list|,
name|GeglBuffer
modifier|*
name|out_buf
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|GimpCoords
name|p1_s
parameter_list|,
name|GimpCoords
name|p1_d
parameter_list|,
name|GimpCoords
name|p2_s
parameter_list|,
name|GimpCoords
name|p2_d
parameter_list|,
name|GimpCoords
name|p3_s
parameter_list|,
name|GimpCoords
name|p3_d
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpCoords
name|gimp_cage_transform_compute_destination
parameter_list|(
name|GimpCageConfig
modifier|*
name|config
parameter_list|,
name|GeglBuffer
modifier|*
name|coef_buf
parameter_list|,
name|GimpCoords
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglRectangle
name|gimp_operation_cage_transform_get_cached_region
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglRectangle
name|gimp_operation_cage_transform_get_required_for_output
parameter_list|(
name|GeglOperation
modifier|*
name|operation
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
name|GeglRectangle
name|gimp_operation_cage_get_bounding_box
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationCageTransform,gimp_operation_cage_transform,GEGL_TYPE_OPERATION_COMPOSER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationCageTransform
argument_list|,
argument|gimp_operation_cage_transform
argument_list|,
argument|GEGL_TYPE_OPERATION_COMPOSER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_cage_transform_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_cage_transform_class_init
parameter_list|(
name|GimpOperationCageTransformClass
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
name|GeglOperationComposerClass
modifier|*
name|filter_class
init|=
name|GEGL_OPERATION_COMPOSER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_cage_transform_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_operation_cage_transform_set_property
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_operation_cage_transform_finalize
expr_stmt|;
comment|/* FIXME: wrong categories and name, to appears in the gegl tool */
name|operation_class
operator|->
name|name
operator|=
literal|"gegl:cage_transform"
expr_stmt|;
name|operation_class
operator|->
name|categories
operator|=
literal|"color"
expr_stmt|;
name|operation_class
operator|->
name|description
operator|=
literal|"GIMP cage reverse transform"
expr_stmt|;
name|operation_class
operator|->
name|prepare
operator|=
name|gimp_operation_cage_transform_prepare
expr_stmt|;
name|operation_class
operator|->
name|get_required_for_output
operator|=
name|gimp_operation_cage_transform_get_required_for_output
expr_stmt|;
name|operation_class
operator|->
name|get_cached_region
operator|=
name|gimp_operation_cage_transform_get_cached_region
expr_stmt|;
name|operation_class
operator|->
name|no_cache
operator|=
name|FALSE
expr_stmt|;
name|operation_class
operator|->
name|get_bounding_box
operator|=
name|gimp_operation_cage_get_bounding_box
expr_stmt|;
name|filter_class
operator|->
name|process
operator|=
name|gimp_operation_cage_transform_process
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_OPERATION_CAGE_TRANSFORM_PROP_CONFIG
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
DECL|function|gimp_operation_cage_transform_init (GimpOperationCageTransform * self)
name|gimp_operation_cage_transform_init
parameter_list|(
name|GimpOperationCageTransform
modifier|*
name|self
parameter_list|)
block|{
name|self
operator|->
name|format_coords
operator|=
name|babl_format_n
argument_list|(
name|babl_type
argument_list|(
literal|"float"
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_cage_transform_finalize (GObject * object)
name|gimp_operation_cage_transform_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpOperationCageTransform
modifier|*
name|self
init|=
name|GIMP_OPERATION_CAGE_TRANSFORM
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
DECL|function|gimp_operation_cage_transform_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_cage_transform_get_property
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
name|GimpOperationCageTransform
modifier|*
name|self
init|=
name|GIMP_OPERATION_CAGE_TRANSFORM
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
name|GIMP_OPERATION_CAGE_TRANSFORM_PROP_CONFIG
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
DECL|function|gimp_operation_cage_transform_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_cage_transform_set_property
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
name|GimpOperationCageTransform
modifier|*
name|self
init|=
name|GIMP_OPERATION_CAGE_TRANSFORM
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
name|GIMP_OPERATION_CAGE_TRANSFORM_PROP_CONFIG
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
name|void
DECL|function|gimp_operation_cage_transform_prepare (GeglOperation * operation)
name|gimp_operation_cage_transform_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
block|{
name|GimpOperationCageTransform
modifier|*
name|oct
init|=
name|GIMP_OPERATION_CAGE_TRANSFORM
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
name|oct
operator|->
name|config
argument_list|)
decl_stmt|;
name|gegl_operation_set_format
argument_list|(
name|operation
argument_list|,
literal|"input"
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
name|config
operator|->
name|cage_vertice_number
argument_list|)
argument_list|)
expr_stmt|;
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
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_cage_transform_process (GeglOperation * operation,GeglBuffer * in_buf,GeglBuffer * aux_buf,GeglBuffer * out_buf,const GeglRectangle * roi)
name|gimp_operation_cage_transform_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|GeglBuffer
modifier|*
name|in_buf
parameter_list|,
name|GeglBuffer
modifier|*
name|aux_buf
parameter_list|,
name|GeglBuffer
modifier|*
name|out_buf
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
block|{
name|GimpOperationCageTransform
modifier|*
name|oct
init|=
name|GIMP_OPERATION_CAGE_TRANSFORM
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
name|oct
operator|->
name|config
argument_list|)
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|GeglRectangle
name|cage_bb
init|=
name|gimp_cage_config_get_bounding_box
argument_list|(
name|config
argument_list|)
decl_stmt|;
name|GeglRectangle
name|buffer_bb
init|=
operator|*
name|gegl_operation_source_get_bounding_box
argument_list|(
name|operation
argument_list|,
literal|"input"
argument_list|)
decl_stmt|;
for|for
control|(
name|x
operator|=
name|cage_bb
operator|.
name|x
init|;
name|x
operator|<
name|cage_bb
operator|.
name|x
operator|+
name|cage_bb
operator|.
name|width
operator|-
literal|1
condition|;
name|x
operator|++
control|)
block|{
for|for
control|(
name|y
operator|=
name|cage_bb
operator|.
name|y
init|;
name|y
operator|<
name|cage_bb
operator|.
name|y
operator|+
name|cage_bb
operator|.
name|height
operator|-
literal|1
condition|;
name|y
operator|++
control|)
block|{
name|GimpCoords
name|p1_s
init|=
block|{
name|x
block|,
name|y
block|, }
decl_stmt|;
name|GimpCoords
name|p2_s
init|=
block|{
name|x
operator|+
literal|1
block|,
name|y
block|, }
decl_stmt|;
name|GimpCoords
name|p3_s
init|=
block|{
name|x
operator|+
literal|1
block|,
name|y
operator|+
literal|1
block|, }
decl_stmt|;
name|GimpCoords
name|p4_s
init|=
block|{
name|x
block|,
name|y
operator|+
literal|1
block|, }
decl_stmt|;
name|GimpCoords
name|p1_d
decl_stmt|,
name|p2_d
decl_stmt|,
name|p3_d
decl_stmt|,
name|p4_d
decl_stmt|;
name|p1_d
operator|=
name|gimp_cage_transform_compute_destination
argument_list|(
name|config
argument_list|,
name|aux_buf
argument_list|,
name|p1_s
argument_list|)
expr_stmt|;
name|p2_d
operator|=
name|gimp_cage_transform_compute_destination
argument_list|(
name|config
argument_list|,
name|aux_buf
argument_list|,
name|p2_s
argument_list|)
expr_stmt|;
name|p3_d
operator|=
name|gimp_cage_transform_compute_destination
argument_list|(
name|config
argument_list|,
name|aux_buf
argument_list|,
name|p3_s
argument_list|)
expr_stmt|;
name|p4_d
operator|=
name|gimp_cage_transform_compute_destination
argument_list|(
name|config
argument_list|,
name|aux_buf
argument_list|,
name|p4_s
argument_list|)
expr_stmt|;
name|gimp_operation_cage_transform_interpolate_source_coords_recurs
argument_list|(
name|oct
argument_list|,
name|out_buf
argument_list|,
operator|&
name|buffer_bb
argument_list|,
name|p1_s
argument_list|,
name|p1_d
argument_list|,
name|p2_s
argument_list|,
name|p2_d
argument_list|,
name|p3_s
argument_list|,
name|p3_d
argument_list|)
expr_stmt|;
name|gimp_operation_cage_transform_interpolate_source_coords_recurs
argument_list|(
name|oct
argument_list|,
name|out_buf
argument_list|,
operator|&
name|buffer_bb
argument_list|,
name|p1_s
argument_list|,
name|p1_d
argument_list|,
name|p3_s
argument_list|,
name|p3_d
argument_list|,
name|p4_s
argument_list|,
name|p4_d
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_cage_transform_interpolate_source_coords_recurs (GimpOperationCageTransform * oct,GeglBuffer * out_buf,const GeglRectangle * roi,GimpCoords p1_s,GimpCoords p1_d,GimpCoords p2_s,GimpCoords p2_d,GimpCoords p3_s,GimpCoords p3_d)
name|gimp_operation_cage_transform_interpolate_source_coords_recurs
parameter_list|(
name|GimpOperationCageTransform
modifier|*
name|oct
parameter_list|,
name|GeglBuffer
modifier|*
name|out_buf
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|GimpCoords
name|p1_s
parameter_list|,
name|GimpCoords
name|p1_d
parameter_list|,
name|GimpCoords
name|p2_s
parameter_list|,
name|GimpCoords
name|p2_d
parameter_list|,
name|GimpCoords
name|p3_s
parameter_list|,
name|GimpCoords
name|p3_d
parameter_list|)
block|{
name|gint
name|xmin
decl_stmt|,
name|xmax
decl_stmt|,
name|ymin
decl_stmt|,
name|ymax
decl_stmt|;
name|GeglRectangle
name|rect
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|1
block|,
literal|1
block|}
decl_stmt|;
name|gfloat
modifier|*
name|coords
decl_stmt|;
name|coords
operator|=
name|g_malloc
argument_list|(
literal|2
operator|*
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|p1_d
operator|.
name|x
operator|>
name|roi
operator|->
name|width
condition|)
return|return;
if|if
condition|(
name|p2_d
operator|.
name|x
operator|>
name|roi
operator|->
name|width
condition|)
return|return;
if|if
condition|(
name|p3_d
operator|.
name|x
operator|>
name|roi
operator|->
name|width
condition|)
return|return;
if|if
condition|(
name|p1_d
operator|.
name|x
operator|<
literal|0
condition|)
return|return;
if|if
condition|(
name|p2_d
operator|.
name|x
operator|<
literal|0
condition|)
return|return;
if|if
condition|(
name|p3_d
operator|.
name|x
operator|<
literal|0
condition|)
return|return;
if|if
condition|(
name|p1_d
operator|.
name|y
operator|>
name|roi
operator|->
name|height
condition|)
return|return;
if|if
condition|(
name|p2_d
operator|.
name|y
operator|>
name|roi
operator|->
name|height
condition|)
return|return;
if|if
condition|(
name|p3_d
operator|.
name|y
operator|>
name|roi
operator|->
name|height
condition|)
return|return;
if|if
condition|(
name|p1_d
operator|.
name|y
operator|<
literal|0
condition|)
return|return;
if|if
condition|(
name|p2_d
operator|.
name|y
operator|<
literal|0
condition|)
return|return;
if|if
condition|(
name|p3_d
operator|.
name|y
operator|<
literal|0
condition|)
return|return;
name|xmin
operator|=
name|xmax
operator|=
name|p1_d
operator|.
name|x
expr_stmt|;
name|ymin
operator|=
name|ymax
operator|=
name|p1_d
operator|.
name|y
expr_stmt|;
if|if
condition|(
name|xmin
operator|>
name|p2_d
operator|.
name|x
condition|)
name|xmin
operator|=
name|p2_d
operator|.
name|x
expr_stmt|;
if|if
condition|(
name|xmin
operator|>
name|p3_d
operator|.
name|x
condition|)
name|xmin
operator|=
name|p3_d
operator|.
name|x
expr_stmt|;
if|if
condition|(
name|xmax
operator|<
name|p2_d
operator|.
name|x
condition|)
name|xmax
operator|=
name|p2_d
operator|.
name|x
expr_stmt|;
if|if
condition|(
name|xmax
operator|<
name|p3_d
operator|.
name|x
condition|)
name|xmax
operator|=
name|p3_d
operator|.
name|x
expr_stmt|;
if|if
condition|(
name|ymin
operator|>
name|p2_d
operator|.
name|y
condition|)
name|ymin
operator|=
name|p2_d
operator|.
name|y
expr_stmt|;
if|if
condition|(
name|ymin
operator|>
name|p3_d
operator|.
name|y
condition|)
name|ymin
operator|=
name|p3_d
operator|.
name|y
expr_stmt|;
if|if
condition|(
name|ymax
operator|<
name|p2_d
operator|.
name|y
condition|)
name|ymax
operator|=
name|p2_d
operator|.
name|y
expr_stmt|;
if|if
condition|(
name|ymax
operator|<
name|p3_d
operator|.
name|y
condition|)
name|ymax
operator|=
name|p3_d
operator|.
name|y
expr_stmt|;
comment|/* test if there is no more pixel in the triangle */
if|if
condition|(
name|xmin
operator|==
name|xmax
operator|||
name|ymin
operator|==
name|ymax
condition|)
return|return;
comment|/* test if the triangle is small enough.    * if yes, we compute the coefficient of the barycenter for the pixel (x,y) and see if a pixel is inside (ie the 3 coef have the same sign).    */
if|if
condition|(
name|xmax
operator|-
name|xmin
operator|==
literal|1
operator|&&
name|ymax
operator|-
name|ymin
operator|==
literal|1
condition|)
block|{
name|gfloat
name|a
decl_stmt|,
name|b
decl_stmt|,
name|c
decl_stmt|,
name|denom
decl_stmt|,
name|x
decl_stmt|,
name|y
decl_stmt|;
name|rect
operator|.
name|x
operator|=
name|xmax
expr_stmt|;
name|rect
operator|.
name|y
operator|=
name|ymax
expr_stmt|;
name|x
operator|=
operator|(
name|gfloat
operator|)
name|xmax
expr_stmt|;
name|y
operator|=
operator|(
name|gfloat
operator|)
name|ymax
expr_stmt|;
name|denom
operator|=
operator|(
name|p2_d
operator|.
name|x
operator|-
name|p1_d
operator|.
name|x
operator|)
operator|*
name|p3_d
operator|.
name|y
operator|+
operator|(
name|p1_d
operator|.
name|x
operator|-
name|p3_d
operator|.
name|x
operator|)
operator|*
name|p2_d
operator|.
name|y
operator|+
operator|(
name|p3_d
operator|.
name|x
operator|-
name|p2_d
operator|.
name|x
operator|)
operator|*
name|p1_d
operator|.
name|y
expr_stmt|;
name|a
operator|=
operator|(
operator|(
name|p2_d
operator|.
name|x
operator|-
name|x
operator|)
operator|*
name|p3_d
operator|.
name|y
operator|+
operator|(
name|x
operator|-
name|p3_d
operator|.
name|x
operator|)
operator|*
name|p2_d
operator|.
name|y
operator|+
operator|(
name|p3_d
operator|.
name|x
operator|-
name|p2_d
operator|.
name|x
operator|)
operator|*
name|y
operator|)
operator|/
name|denom
expr_stmt|;
name|b
operator|=
operator|-
operator|(
operator|(
name|p1_d
operator|.
name|x
operator|-
name|x
operator|)
operator|*
name|p3_d
operator|.
name|y
operator|+
operator|(
name|x
operator|-
name|p3_d
operator|.
name|x
operator|)
operator|*
name|p1_d
operator|.
name|y
operator|+
operator|(
name|p3_d
operator|.
name|x
operator|-
name|p1_d
operator|.
name|x
operator|)
operator|*
name|y
operator|)
operator|/
name|denom
expr_stmt|;
name|c
operator|=
literal|1.0
operator|-
name|a
operator|-
name|b
expr_stmt|;
comment|/* if a pixel is inside, we compute his source coordinate and set it in the output buffer */
if|if
condition|(
operator|(
name|a
operator|>
literal|0
operator|&&
name|b
operator|>
literal|0
operator|&&
name|c
operator|>
literal|0
operator|)
operator|||
operator|(
name|a
operator|<
literal|0
operator|&&
name|b
operator|<
literal|0
operator|&&
name|c
operator|<
literal|0
operator|)
condition|)
block|{
name|coords
index|[
literal|0
index|]
operator|=
operator|(
name|a
operator|*
name|p1_s
operator|.
name|x
operator|+
name|b
operator|*
name|p2_s
operator|.
name|x
operator|+
name|c
operator|*
name|p3_s
operator|.
name|x
operator|)
expr_stmt|;
name|coords
index|[
literal|1
index|]
operator|=
operator|(
name|a
operator|*
name|p1_s
operator|.
name|y
operator|+
name|b
operator|*
name|p2_s
operator|.
name|y
operator|+
name|c
operator|*
name|p3_s
operator|.
name|y
operator|)
expr_stmt|;
name|gegl_buffer_set
argument_list|(
name|out_buf
argument_list|,
operator|&
name|rect
argument_list|,
name|oct
operator|->
name|format_coords
argument_list|,
name|coords
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/* we cut the triangle in 4 sub-triangle and treat it recursively */
comment|/*      *       /\      *      /__\      *     /\  /\      *    /__\/__\      *       */
name|GimpCoords
name|pm1_d
decl_stmt|,
name|pm2_d
decl_stmt|,
name|pm3_d
decl_stmt|;
name|GimpCoords
name|pm1_s
decl_stmt|,
name|pm2_s
decl_stmt|,
name|pm3_s
decl_stmt|;
name|pm1_d
operator|.
name|x
operator|=
operator|(
name|p1_d
operator|.
name|x
operator|+
name|p2_d
operator|.
name|x
operator|)
operator|/
literal|2.0
expr_stmt|;
name|pm1_d
operator|.
name|y
operator|=
operator|(
name|p1_d
operator|.
name|y
operator|+
name|p2_d
operator|.
name|y
operator|)
operator|/
literal|2.0
expr_stmt|;
name|pm2_d
operator|.
name|x
operator|=
operator|(
name|p2_d
operator|.
name|x
operator|+
name|p3_d
operator|.
name|x
operator|)
operator|/
literal|2.0
expr_stmt|;
name|pm2_d
operator|.
name|y
operator|=
operator|(
name|p2_d
operator|.
name|y
operator|+
name|p3_d
operator|.
name|y
operator|)
operator|/
literal|2.0
expr_stmt|;
name|pm3_d
operator|.
name|x
operator|=
operator|(
name|p3_d
operator|.
name|x
operator|+
name|p1_d
operator|.
name|x
operator|)
operator|/
literal|2.0
expr_stmt|;
name|pm3_d
operator|.
name|y
operator|=
operator|(
name|p3_d
operator|.
name|y
operator|+
name|p1_d
operator|.
name|y
operator|)
operator|/
literal|2.0
expr_stmt|;
name|pm1_s
operator|.
name|x
operator|=
operator|(
name|p1_s
operator|.
name|x
operator|+
name|p2_s
operator|.
name|x
operator|)
operator|/
literal|2.0
expr_stmt|;
name|pm1_s
operator|.
name|y
operator|=
operator|(
name|p1_s
operator|.
name|y
operator|+
name|p2_s
operator|.
name|y
operator|)
operator|/
literal|2.0
expr_stmt|;
name|pm2_s
operator|.
name|x
operator|=
operator|(
name|p2_s
operator|.
name|x
operator|+
name|p3_s
operator|.
name|x
operator|)
operator|/
literal|2.0
expr_stmt|;
name|pm2_s
operator|.
name|y
operator|=
operator|(
name|p2_s
operator|.
name|y
operator|+
name|p3_s
operator|.
name|y
operator|)
operator|/
literal|2.0
expr_stmt|;
name|pm3_s
operator|.
name|x
operator|=
operator|(
name|p3_s
operator|.
name|x
operator|+
name|p1_s
operator|.
name|x
operator|)
operator|/
literal|2.0
expr_stmt|;
name|pm3_s
operator|.
name|y
operator|=
operator|(
name|p3_s
operator|.
name|y
operator|+
name|p1_s
operator|.
name|y
operator|)
operator|/
literal|2.0
expr_stmt|;
name|gimp_operation_cage_transform_interpolate_source_coords_recurs
argument_list|(
name|oct
argument_list|,
name|out_buf
argument_list|,
name|roi
argument_list|,
name|p1_s
argument_list|,
name|p1_d
argument_list|,
name|pm1_s
argument_list|,
name|pm1_d
argument_list|,
name|pm3_s
argument_list|,
name|pm3_d
argument_list|)
expr_stmt|;
name|gimp_operation_cage_transform_interpolate_source_coords_recurs
argument_list|(
name|oct
argument_list|,
name|out_buf
argument_list|,
name|roi
argument_list|,
name|pm1_s
argument_list|,
name|pm1_d
argument_list|,
name|p2_s
argument_list|,
name|p2_d
argument_list|,
name|pm2_s
argument_list|,
name|pm2_d
argument_list|)
expr_stmt|;
name|gimp_operation_cage_transform_interpolate_source_coords_recurs
argument_list|(
name|oct
argument_list|,
name|out_buf
argument_list|,
name|roi
argument_list|,
name|pm1_s
argument_list|,
name|pm1_d
argument_list|,
name|pm2_s
argument_list|,
name|pm2_d
argument_list|,
name|pm3_s
argument_list|,
name|pm3_d
argument_list|)
expr_stmt|;
name|gimp_operation_cage_transform_interpolate_source_coords_recurs
argument_list|(
name|oct
argument_list|,
name|out_buf
argument_list|,
name|roi
argument_list|,
name|pm3_s
argument_list|,
name|pm3_d
argument_list|,
name|pm2_s
argument_list|,
name|pm2_d
argument_list|,
name|p3_s
argument_list|,
name|p3_d
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|coords
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpCoords
DECL|function|gimp_cage_transform_compute_destination (GimpCageConfig * config,GeglBuffer * coef_buf,GimpCoords coords)
name|gimp_cage_transform_compute_destination
parameter_list|(
name|GimpCageConfig
modifier|*
name|config
parameter_list|,
name|GeglBuffer
modifier|*
name|coef_buf
parameter_list|,
name|GimpCoords
name|coords
parameter_list|)
block|{
name|gfloat
modifier|*
name|coef
decl_stmt|;
name|gdouble
name|pos_x
decl_stmt|,
name|pos_y
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GeglRectangle
name|rect
decl_stmt|;
name|GimpCoords
name|result
decl_stmt|;
name|gint
name|cvn
init|=
name|config
operator|->
name|cage_vertice_number
decl_stmt|;
name|Babl
modifier|*
name|format_coef
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
name|cvn
argument_list|)
decl_stmt|;
name|rect
operator|.
name|height
operator|=
literal|1
expr_stmt|;
name|rect
operator|.
name|width
operator|=
literal|1
expr_stmt|;
name|rect
operator|.
name|x
operator|=
name|coords
operator|.
name|x
expr_stmt|;
name|rect
operator|.
name|y
operator|=
name|coords
operator|.
name|y
expr_stmt|;
name|coef
operator|=
name|g_malloc
argument_list|(
name|config
operator|->
name|cage_vertice_number
operator|*
literal|2
operator|*
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|coef_buf
argument_list|,
literal|1
argument_list|,
operator|&
name|rect
argument_list|,
name|format_coef
argument_list|,
name|coef
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
name|pos_x
operator|=
literal|0
expr_stmt|;
name|pos_y
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|cvn
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|isnan
argument_list|(
name|coef
index|[
name|i
index|]
argument_list|)
condition|)
block|{
name|pos_x
operator|+=
name|coef
index|[
name|i
index|]
operator|*
name|config
operator|->
name|cage_vertices_d
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|pos_y
operator|+=
name|coef
index|[
name|i
index|]
operator|*
name|config
operator|->
name|cage_vertices_d
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
block|}
name|g_assert
argument_list|(
operator|!
name|isnan
argument_list|(
name|pos_x
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
operator|!
name|isnan
argument_list|(
name|pos_y
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
name|cvn
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|isnan
argument_list|(
name|coef
index|[
name|i
index|]
argument_list|)
condition|)
block|{
name|pos_x
operator|+=
name|coef
index|[
name|i
operator|+
name|cvn
index|]
operator|*
name|config
operator|->
name|scaling_factor
index|[
name|i
index|]
operator|*
name|gimp_cage_config_get_edge_normal
argument_list|(
name|config
argument_list|,
name|i
argument_list|)
operator|.
name|x
expr_stmt|;
name|pos_y
operator|+=
name|coef
index|[
name|i
operator|+
name|cvn
index|]
operator|*
name|config
operator|->
name|scaling_factor
index|[
name|i
index|]
operator|*
name|gimp_cage_config_get_edge_normal
argument_list|(
name|config
argument_list|,
name|i
argument_list|)
operator|.
name|y
expr_stmt|;
block|}
name|g_assert
argument_list|(
operator|!
name|isnan
argument_list|(
name|pos_x
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
operator|!
name|isnan
argument_list|(
name|pos_y
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|result
operator|.
name|x
operator|=
name|pos_x
expr_stmt|;
name|result
operator|.
name|y
operator|=
name|pos_y
expr_stmt|;
name|g_free
argument_list|(
name|coef
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
name|GeglRectangle
DECL|function|gimp_operation_cage_transform_get_cached_region (GeglOperation * operation,const GeglRectangle * roi)
name|gimp_operation_cage_transform_get_cached_region
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
block|{
name|GeglRectangle
name|result
init|=
operator|*
name|gegl_operation_source_get_bounding_box
argument_list|(
name|operation
argument_list|,
literal|"input"
argument_list|)
decl_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
name|GeglRectangle
DECL|function|gimp_operation_cage_transform_get_required_for_output (GeglOperation * operation,const gchar * input_pad,const GeglRectangle * roi)
name|gimp_operation_cage_transform_get_required_for_output
parameter_list|(
name|GeglOperation
modifier|*
name|operation
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
name|GeglRectangle
name|result
init|=
operator|*
name|gegl_operation_source_get_bounding_box
argument_list|(
name|operation
argument_list|,
literal|"input"
argument_list|)
decl_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
name|GeglRectangle
DECL|function|gimp_operation_cage_get_bounding_box (GeglOperation * operation)
name|gimp_operation_cage_get_bounding_box
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
block|{
name|GeglRectangle
name|result
init|=
operator|*
name|gegl_operation_source_get_bounding_box
argument_list|(
name|operation
argument_list|,
literal|"input"
argument_list|)
decl_stmt|;
return|return
name|result
return|;
block|}
end_function

end_unit

