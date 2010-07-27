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
file|"gimpoperationcage.h"
end_include

begin_include
include|#
directive|include
file|"gimpcageconfig.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_operation_cage_finalize
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
name|gimp_operation_cage_get_property
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
name|gimp_operation_cage_set_property
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
name|gimp_operation_cage_prepare
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
name|gimp_operation_cage_process
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
name|GeglRectangle
name|gimp_operation_cage_get_cached_region
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
name|gimp_operation_cage_get_required_for_output
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationCage,gimp_operation_cage,GEGL_TYPE_OPERATION_COMPOSER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationCage
argument_list|,
argument|gimp_operation_cage
argument_list|,
argument|GEGL_TYPE_OPERATION_COMPOSER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_cage_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_cage_class_init
parameter_list|(
name|GimpOperationCageClass
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
name|composer_class
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
name|gimp_operation_cage_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_operation_cage_set_property
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_operation_cage_finalize
expr_stmt|;
comment|/* FIXME: wrong categories and name, to appears in the gegl tool */
name|operation_class
operator|->
name|name
operator|=
literal|"gegl:cage"
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
literal|"GIMP cage transform"
expr_stmt|;
name|operation_class
operator|->
name|prepare
operator|=
name|gimp_operation_cage_prepare
expr_stmt|;
name|operation_class
operator|->
name|get_required_for_output
operator|=
name|gimp_operation_cage_get_required_for_output
expr_stmt|;
name|operation_class
operator|->
name|get_cached_region
operator|=
name|gimp_operation_cage_get_cached_region
expr_stmt|;
name|operation_class
operator|->
name|no_cache
operator|=
name|FALSE
expr_stmt|;
name|composer_class
operator|->
name|process
operator|=
name|gimp_operation_cage_process
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_OPERATION_CAGE_PROP_CONFIG
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
DECL|function|gimp_operation_cage_init (GimpOperationCage * self)
name|gimp_operation_cage_init
parameter_list|(
name|GimpOperationCage
modifier|*
name|self
parameter_list|)
block|{  }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_cage_finalize (GObject * object)
name|gimp_operation_cage_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpOperationCage
modifier|*
name|self
init|=
name|GIMP_OPERATION_CAGE
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
DECL|function|gimp_operation_cage_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_cage_get_property
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
name|GimpOperationCage
modifier|*
name|self
init|=
name|GIMP_OPERATION_CAGE
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
name|GIMP_OPERATION_CAGE_PROP_CONFIG
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
DECL|function|gimp_operation_cage_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_cage_set_property
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
name|GimpOperationCage
modifier|*
name|self
init|=
name|GIMP_OPERATION_CAGE
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
name|GIMP_OPERATION_CAGE_PROP_CONFIG
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
DECL|function|gimp_operation_cage_prepare (GeglOperation * operation)
name|gimp_operation_cage_prepare
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
literal|"RGBA float"
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
literal|"RGBA float"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_cage_process (GeglOperation * operation,GeglBuffer * in_buf,GeglBuffer * aux_buf,GeglBuffer * out_buf,const GeglRectangle * roi)
name|gimp_operation_cage_process
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
name|GimpOperationCage
modifier|*
name|oc
init|=
name|GIMP_OPERATION_CAGE
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
name|oc
operator|->
name|config
argument_list|)
decl_stmt|;
name|Babl
modifier|*
name|format_io
init|=
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
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
name|config
operator|->
name|cage_vertice_number
argument_list|)
decl_stmt|;
name|gint
name|in_index
decl_stmt|,
name|coef_index
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GeglRectangle
name|rect
decl_stmt|,
name|bb_cage
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|it
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
name|bb_cage
operator|=
name|gimp_cage_config_get_bounding_box
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|it
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|in_buf
argument_list|,
operator|&
name|bb_cage
argument_list|,
name|format_io
argument_list|,
name|GEGL_BUFFER_READ
argument_list|)
expr_stmt|;
name|in_index
operator|=
literal|0
expr_stmt|;
name|coef_index
operator|=
name|gegl_buffer_iterator_add
argument_list|(
name|it
argument_list|,
name|aux_buf
argument_list|,
operator|&
name|bb_cage
argument_list|,
name|format_coef
argument_list|,
name|GEGL_BUFFER_READ
argument_list|)
expr_stmt|;
comment|/* pre-copy the input buffer to the out buffer */
comment|//gegl_buffer_copy (aux_buf, roi, out_buf, roi);
comment|/* iterate on GeglBuffer */
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
name|cvn
init|=
name|config
operator|->
name|cage_vertice_number
decl_stmt|;
name|gfloat
modifier|*
name|source
init|=
name|it
operator|->
name|data
index|[
name|in_index
index|]
decl_stmt|;
name|gfloat
modifier|*
name|coef
init|=
name|it
operator|->
name|data
index|[
name|coef_index
index|]
decl_stmt|;
while|while
condition|(
name|n_pixels
operator|--
condition|)
block|{
comment|/* computing of the final position of the source pixel */
name|gdouble
name|pos_x
decl_stmt|,
name|pos_y
decl_stmt|;
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
name|rect
operator|.
name|x
operator|=
operator|(
name|gint
operator|)
name|rint
argument_list|(
name|pos_x
argument_list|)
expr_stmt|;
name|rect
operator|.
name|y
operator|=
operator|(
name|gint
operator|)
name|rint
argument_list|(
name|pos_y
argument_list|)
expr_stmt|;
comment|/*if (sqrt ((pos_x-x) * (pos_x-x) + (pos_y-y) * (pos_y-y))< 20)       {         if (rect.x != x || rect.y != y)         {           printf("x: %d    y: %d\n", rect.x, rect.y);         }       }*/
comment|/* copy the source pixel in the out buffer */
name|gegl_buffer_set
argument_list|(
name|out_buf
argument_list|,
operator|&
name|rect
argument_list|,
name|format_io
argument_list|,
name|source
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
name|source
operator|+=
literal|4
expr_stmt|;
name|coef
operator|+=
literal|2
operator|*
name|cvn
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

begin_function
name|GeglRectangle
DECL|function|gimp_operation_cage_get_cached_region (GeglOperation * operation,const GeglRectangle * roi)
name|gimp_operation_cage_get_cached_region
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
DECL|function|gimp_operation_cage_get_required_for_output (GeglOperation * operation,const gchar * input_pad,const GeglRectangle * roi)
name|gimp_operation_cage_get_required_for_output
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

end_unit

