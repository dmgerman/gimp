begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *   * gimpcageconfig.c  * Copyright (C) 2010 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmodule/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmathtypes.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbaseenums.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpvector.h"
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"gimpcageconfig.h"
end_include

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpCageConfig
argument_list|,
argument|gimp_cage_config
argument_list|,
argument|GIMP_TYPE_IMAGE_MAP_CONFIG
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 NULL)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_cage_config_parent_class
end_define

begin_define
DECL|macro|N_ITEMS_PER_ALLOC
define|#
directive|define
name|N_ITEMS_PER_ALLOC
value|10
end_define

begin_function_decl
specifier|static
name|void
name|gimp_cage_config_finalize
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
name|gimp_cage_config_get_property
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
name|gimp_cage_config_set_property
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
name|gimp_cage_config_compute_scaling_factor
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* FIXME: to debug only */
end_comment

begin_function
specifier|static
name|void
DECL|function|print_cage (GimpCageConfig * gcc)
name|print_cage
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|GeglRectangle
name|bounding_box
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CAGE_CONFIG
argument_list|(
name|gcc
argument_list|)
argument_list|)
expr_stmt|;
name|bounding_box
operator|=
name|gimp_cage_config_get_bounding_box
argument_list|(
name|gcc
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
name|gcc
operator|->
name|cage_vertice_number
condition|;
name|i
operator|++
control|)
block|{
name|printf
argument_list|(
literal|"cgx: %.0f    cgy: %.0f    cvdx: %.0f    cvdy: %.0f  sf: %.2f\n"
argument_list|,
name|gcc
operator|->
name|cage_vertices
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|gcc
operator|->
name|cage_vertices
index|[
name|i
index|]
operator|.
name|y
argument_list|,
name|gcc
operator|->
name|cage_vertices_d
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|gcc
operator|->
name|cage_vertices_d
index|[
name|i
index|]
operator|.
name|y
argument_list|,
name|gcc
operator|->
name|scaling_factor
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|printf
argument_list|(
literal|"bounding box: x: %d  y: %d  width: %d  height: %d\n"
argument_list|,
name|bounding_box
operator|.
name|x
argument_list|,
name|bounding_box
operator|.
name|y
argument_list|,
name|bounding_box
operator|.
name|width
argument_list|,
name|bounding_box
operator|.
name|height
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"done\n"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_config_class_init (GimpCageConfigClass * klass)
name|gimp_cage_config_class_init
parameter_list|(
name|GimpCageConfigClass
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
name|object_class
operator|->
name|set_property
operator|=
name|gimp_cage_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_cage_config_get_property
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_cage_config_finalize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_config_init (GimpCageConfig * self)
name|gimp_cage_config_init
parameter_list|(
name|GimpCageConfig
modifier|*
name|self
parameter_list|)
block|{
name|self
operator|->
name|cage_vertice_number
operator|=
literal|0
expr_stmt|;
name|self
operator|->
name|cage_vertices_max
operator|=
literal|50
expr_stmt|;
comment|//pre-allocation for 50 vertices for the cage.
name|self
operator|->
name|cage_vertices
operator|=
name|g_new
argument_list|(
name|GimpVector2
argument_list|,
name|self
operator|->
name|cage_vertices_max
argument_list|)
expr_stmt|;
name|self
operator|->
name|cage_vertices_d
operator|=
name|g_new
argument_list|(
name|GimpVector2
argument_list|,
name|self
operator|->
name|cage_vertices_max
argument_list|)
expr_stmt|;
name|self
operator|->
name|scaling_factor
operator|=
name|g_malloc
argument_list|(
name|self
operator|->
name|cage_vertices_max
operator|*
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_config_finalize (GObject * object)
name|gimp_cage_config_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCageConfig
modifier|*
name|gcc
init|=
name|GIMP_CAGE_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|gcc
operator|->
name|cage_vertices
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gcc
operator|->
name|cage_vertices_d
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gcc
operator|->
name|scaling_factor
argument_list|)
expr_stmt|;
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
DECL|function|gimp_cage_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_cage_config_get_property
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
comment|/* GimpCageConfig *gcc = GIMP_CAGE_CONFIG (object); */
switch|switch
condition|(
name|property_id
condition|)
block|{
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
DECL|function|gimp_cage_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_cage_config_set_property
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
comment|/* GimpCageConfig *gcc = GIMP_CAGE_CONFIG (object); */
switch|switch
condition|(
name|property_id
condition|)
block|{
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
name|void
DECL|function|gimp_cage_config_add_cage_point (GimpCageConfig * gcc,gdouble x,gdouble y)
name|gimp_cage_config_add_cage_point
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CAGE_CONFIG
argument_list|(
name|gcc
argument_list|)
argument_list|)
expr_stmt|;
comment|/* reallocate memory if needed */
if|if
condition|(
name|gcc
operator|->
name|cage_vertice_number
operator|>=
name|gcc
operator|->
name|cage_vertices_max
condition|)
block|{
name|gcc
operator|->
name|cage_vertices_max
operator|+=
name|N_ITEMS_PER_ALLOC
expr_stmt|;
name|gcc
operator|->
name|cage_vertices
operator|=
name|g_renew
argument_list|(
name|GimpVector2
argument_list|,
name|gcc
operator|->
name|cage_vertices
argument_list|,
name|gcc
operator|->
name|cage_vertices_max
argument_list|)
expr_stmt|;
name|gcc
operator|->
name|cage_vertices_d
operator|=
name|g_renew
argument_list|(
name|GimpVector2
argument_list|,
name|gcc
operator|->
name|cage_vertices_d
argument_list|,
name|gcc
operator|->
name|cage_vertices_max
argument_list|)
expr_stmt|;
name|gcc
operator|->
name|scaling_factor
operator|=
name|g_realloc
argument_list|(
name|gcc
operator|->
name|scaling_factor
argument_list|,
name|gcc
operator|->
name|cage_vertices_max
operator|*
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gcc
operator|->
name|cage_vertices
index|[
name|gcc
operator|->
name|cage_vertice_number
index|]
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|gcc
operator|->
name|cage_vertices
index|[
name|gcc
operator|->
name|cage_vertice_number
index|]
operator|.
name|y
operator|=
name|y
expr_stmt|;
name|gcc
operator|->
name|cage_vertices_d
index|[
name|gcc
operator|->
name|cage_vertice_number
index|]
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|gcc
operator|->
name|cage_vertices_d
index|[
name|gcc
operator|->
name|cage_vertice_number
index|]
operator|.
name|y
operator|=
name|y
expr_stmt|;
name|gcc
operator|->
name|cage_vertice_number
operator|++
expr_stmt|;
name|gimp_cage_config_compute_scaling_factor
argument_list|(
name|gcc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_cage_config_remove_last_cage_point (GimpCageConfig * gcc)
name|gimp_cage_config_remove_last_cage_point
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CAGE_CONFIG
argument_list|(
name|gcc
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gcc
operator|->
name|cage_vertice_number
operator|>=
literal|1
condition|)
name|gcc
operator|->
name|cage_vertice_number
operator|--
expr_stmt|;
name|gimp_cage_config_compute_scaling_factor
argument_list|(
name|gcc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_cage_config_is_on_handle (GimpCageConfig * gcc,GimpCageMode mode,gdouble x,gdouble y,gint handle_size)
name|gimp_cage_config_is_on_handle
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|,
name|GimpCageMode
name|mode
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gint
name|handle_size
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gdouble
name|vert_x
decl_stmt|,
name|vert_y
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CAGE_CONFIG
argument_list|(
name|gcc
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|gcc
operator|->
name|cage_vertice_number
operator|==
literal|0
condition|)
return|return
operator|-
literal|1
return|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|gcc
operator|->
name|cage_vertice_number
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|mode
operator|==
name|GIMP_CAGE_MODE_CAGE_CHANGE
condition|)
block|{
name|vert_x
operator|=
name|gcc
operator|->
name|cage_vertices
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|vert_y
operator|=
name|gcc
operator|->
name|cage_vertices
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
block|}
else|else
block|{
name|vert_x
operator|=
name|gcc
operator|->
name|cage_vertices_d
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|vert_y
operator|=
name|gcc
operator|->
name|cage_vertices_d
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
block|}
if|if
condition|(
name|x
operator|<
name|vert_x
operator|+
name|handle_size
operator|/
literal|2
operator|&&
name|x
operator|>
name|vert_x
operator|-
name|handle_size
operator|/
literal|2
operator|&&
name|y
operator|<
name|vert_y
operator|+
name|handle_size
operator|/
literal|2
operator|&&
name|y
operator|>
name|vert_y
operator|-
name|handle_size
operator|/
literal|2
condition|)
block|{
return|return
name|i
return|;
block|}
block|}
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_cage_config_move_cage_point (GimpCageConfig * gcc,GimpCageMode mode,gint point_number,gdouble x,gdouble y)
name|gimp_cage_config_move_cage_point
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|,
name|GimpCageMode
name|mode
parameter_list|,
name|gint
name|point_number
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CAGE_CONFIG
argument_list|(
name|gcc
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|point_number
operator|<
name|gcc
operator|->
name|cage_vertice_number
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|point_number
operator|>=
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|mode
operator|==
name|GIMP_CAGE_MODE_CAGE_CHANGE
condition|)
block|{
name|gcc
operator|->
name|cage_vertices
index|[
name|point_number
index|]
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|gcc
operator|->
name|cage_vertices
index|[
name|point_number
index|]
operator|.
name|y
operator|=
name|y
expr_stmt|;
block|}
else|else
block|{
name|gcc
operator|->
name|cage_vertices_d
index|[
name|point_number
index|]
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|gcc
operator|->
name|cage_vertices_d
index|[
name|point_number
index|]
operator|.
name|y
operator|=
name|y
expr_stmt|;
block|}
name|gimp_cage_config_compute_scaling_factor
argument_list|(
name|gcc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpVector2
DECL|function|gimp_cage_config_get_edge_normal (GimpCageConfig * gcc,gint edge_index)
name|gimp_cage_config_get_edge_normal
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|,
name|gint
name|edge_index
parameter_list|)
block|{
name|GimpVector2
name|result
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CAGE_CONFIG
argument_list|(
name|gcc
argument_list|)
argument_list|,
name|gimp_vector2_new
argument_list|(
literal|1
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|edge_index
operator|>=
literal|0
argument_list|,
name|gimp_vector2_new
argument_list|(
literal|1
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|edge_index
operator|<
name|gcc
operator|->
name|cage_vertice_number
argument_list|,
name|gimp_vector2_new
argument_list|(
literal|1
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_vector2_sub
argument_list|(
operator|&
name|result
argument_list|,
operator|&
name|gcc
operator|->
name|cage_vertices_d
index|[
operator|(
name|edge_index
operator|+
literal|1
operator|)
operator|%
name|gcc
operator|->
name|cage_vertice_number
index|]
argument_list|,
operator|&
name|gcc
operator|->
name|cage_vertices_d
index|[
name|edge_index
index|]
argument_list|)
expr_stmt|;
return|return
name|gimp_vector2_normal
argument_list|(
operator|&
name|result
argument_list|)
return|;
block|}
end_function

begin_function
name|GeglRectangle
DECL|function|gimp_cage_config_get_bounding_box (GimpCageConfig * gcc)
name|gimp_cage_config_get_bounding_box
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|GeglRectangle
name|bounding_box
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CAGE_CONFIG
argument_list|(
name|gcc
argument_list|)
argument_list|,
name|bounding_box
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gcc
operator|->
name|cage_vertice_number
operator|>=
literal|0
argument_list|,
name|bounding_box
argument_list|)
expr_stmt|;
name|bounding_box
operator|.
name|x
operator|=
name|gcc
operator|->
name|cage_vertices
index|[
literal|0
index|]
operator|.
name|x
expr_stmt|;
name|bounding_box
operator|.
name|y
operator|=
name|gcc
operator|->
name|cage_vertices
index|[
literal|0
index|]
operator|.
name|y
expr_stmt|;
name|bounding_box
operator|.
name|height
operator|=
literal|0
expr_stmt|;
name|bounding_box
operator|.
name|width
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|gcc
operator|->
name|cage_vertice_number
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|x
operator|=
name|gcc
operator|->
name|cage_vertices
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|y
operator|=
name|gcc
operator|->
name|cage_vertices
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
if|if
condition|(
name|x
operator|<
name|bounding_box
operator|.
name|x
condition|)
block|{
name|bounding_box
operator|.
name|width
operator|+=
name|bounding_box
operator|.
name|x
operator|-
name|x
expr_stmt|;
name|bounding_box
operator|.
name|x
operator|=
name|x
expr_stmt|;
block|}
if|if
condition|(
name|y
operator|<
name|bounding_box
operator|.
name|y
condition|)
block|{
name|bounding_box
operator|.
name|height
operator|+=
name|bounding_box
operator|.
name|y
operator|-
name|y
expr_stmt|;
name|bounding_box
operator|.
name|y
operator|=
name|y
expr_stmt|;
block|}
if|if
condition|(
name|x
operator|>
name|bounding_box
operator|.
name|x
operator|+
name|bounding_box
operator|.
name|width
condition|)
block|{
name|bounding_box
operator|.
name|width
operator|=
name|x
operator|-
name|bounding_box
operator|.
name|x
expr_stmt|;
block|}
if|if
condition|(
name|y
operator|>
name|bounding_box
operator|.
name|y
operator|+
name|bounding_box
operator|.
name|height
condition|)
block|{
name|bounding_box
operator|.
name|height
operator|=
name|y
operator|-
name|bounding_box
operator|.
name|y
expr_stmt|;
block|}
block|}
return|return
name|bounding_box
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_cage_config_reverse_cage (GimpCageConfig * gcc)
name|gimp_cage_config_reverse_cage
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|GimpVector2
name|temp
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CAGE_CONFIG
argument_list|(
name|gcc
argument_list|)
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
name|gcc
operator|->
name|cage_vertice_number
operator|/
literal|2
condition|;
name|i
operator|++
control|)
block|{
name|temp
operator|=
name|gcc
operator|->
name|cage_vertices
index|[
name|i
index|]
expr_stmt|;
name|gcc
operator|->
name|cage_vertices
index|[
name|i
index|]
operator|=
name|gcc
operator|->
name|cage_vertices
index|[
name|gcc
operator|->
name|cage_vertice_number
operator|-
name|i
operator|-
literal|1
index|]
expr_stmt|;
name|gcc
operator|->
name|cage_vertices
index|[
name|gcc
operator|->
name|cage_vertice_number
operator|-
name|i
operator|-
literal|1
index|]
operator|=
name|temp
expr_stmt|;
name|temp
operator|=
name|gcc
operator|->
name|cage_vertices_d
index|[
name|i
index|]
expr_stmt|;
name|gcc
operator|->
name|cage_vertices_d
index|[
name|i
index|]
operator|=
name|gcc
operator|->
name|cage_vertices_d
index|[
name|gcc
operator|->
name|cage_vertice_number
operator|-
name|i
operator|-
literal|1
index|]
expr_stmt|;
name|gcc
operator|->
name|cage_vertices_d
index|[
name|gcc
operator|->
name|cage_vertice_number
operator|-
name|i
operator|-
literal|1
index|]
operator|=
name|temp
expr_stmt|;
block|}
name|gimp_cage_config_compute_scaling_factor
argument_list|(
name|gcc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_cage_config_reverse_cage_if_needed (GimpCageConfig * gcc)
name|gimp_cage_config_reverse_cage_if_needed
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gdouble
name|sum
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CAGE_CONFIG
argument_list|(
name|gcc
argument_list|)
argument_list|)
expr_stmt|;
name|sum
operator|=
literal|0.0
expr_stmt|;
comment|/* this is a bit crappy, but should works most of the case */
comment|/* we do the sum of the projection of each point to the previous segment, and see the final sign */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|gcc
operator|->
name|cage_vertice_number
condition|;
name|i
operator|++
control|)
block|{
name|GimpVector2
name|P1
decl_stmt|,
name|P2
decl_stmt|,
name|P3
decl_stmt|;
name|gdouble
name|z
decl_stmt|;
name|P1
operator|=
name|gcc
operator|->
name|cage_vertices
index|[
name|i
index|]
expr_stmt|;
name|P2
operator|=
name|gcc
operator|->
name|cage_vertices
index|[
operator|(
name|i
operator|+
literal|1
operator|)
operator|%
name|gcc
operator|->
name|cage_vertice_number
index|]
expr_stmt|;
name|P3
operator|=
name|gcc
operator|->
name|cage_vertices
index|[
operator|(
name|i
operator|+
literal|2
operator|)
operator|%
name|gcc
operator|->
name|cage_vertice_number
index|]
expr_stmt|;
name|z
operator|=
name|P1
operator|.
name|x
operator|*
operator|(
name|P2
operator|.
name|y
operator|-
name|P3
operator|.
name|y
operator|)
operator|+
name|P2
operator|.
name|x
operator|*
operator|(
name|P3
operator|.
name|y
operator|-
name|P1
operator|.
name|y
operator|)
operator|+
name|P3
operator|.
name|x
operator|*
operator|(
name|P1
operator|.
name|y
operator|-
name|P2
operator|.
name|y
operator|)
expr_stmt|;
name|sum
operator|+=
name|z
expr_stmt|;
block|}
comment|/* sum> 0 mean a cage defined counter-clockwise, so we reverse it */
if|if
condition|(
name|sum
operator|>
literal|0
condition|)
block|{
name|gimp_cage_config_reverse_cage
argument_list|(
name|gcc
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"reverse the cage !\n"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|printf
argument_list|(
literal|"Cage OK !\n"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_config_compute_scaling_factor (GimpCageConfig * gcc)
name|gimp_cage_config_compute_scaling_factor
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gdouble
name|length
decl_stmt|,
name|length_d
decl_stmt|;
name|GimpVector2
name|edge
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CAGE_CONFIG
argument_list|(
name|gcc
argument_list|)
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
name|gcc
operator|->
name|cage_vertice_number
condition|;
name|i
operator|++
control|)
block|{
name|gimp_vector2_sub
argument_list|(
operator|&
name|edge
argument_list|,
operator|&
name|gcc
operator|->
name|cage_vertices
index|[
name|i
index|]
argument_list|,
operator|&
name|gcc
operator|->
name|cage_vertices
index|[
operator|(
name|i
operator|+
literal|1
operator|)
operator|%
name|gcc
operator|->
name|cage_vertice_number
index|]
argument_list|)
expr_stmt|;
name|length
operator|=
name|gimp_vector2_length
argument_list|(
operator|&
name|edge
argument_list|)
expr_stmt|;
name|gimp_vector2_sub
argument_list|(
operator|&
name|edge
argument_list|,
operator|&
name|gcc
operator|->
name|cage_vertices_d
index|[
name|i
index|]
argument_list|,
operator|&
name|gcc
operator|->
name|cage_vertices_d
index|[
operator|(
name|i
operator|+
literal|1
operator|)
operator|%
name|gcc
operator|->
name|cage_vertice_number
index|]
argument_list|)
expr_stmt|;
name|length_d
operator|=
name|gimp_vector2_length
argument_list|(
operator|&
name|edge
argument_list|)
expr_stmt|;
name|gcc
operator|->
name|scaling_factor
index|[
name|i
index|]
operator|=
name|length_d
operator|/
name|length
expr_stmt|;
block|}
name|print_cage
argument_list|(
name|gcc
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

