begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationdissolve.c  * Copyright (C) 2012 Ville Sokk<ville.sokk@gmail.com>  *               2012 Ãyvind KolÃ¥s<pippin@gimp.org>  *               2003 Helvetix Victorinox  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl-plugin.h>
end_include

begin_include
include|#
directive|include
file|"../operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationdissolve.h"
end_include

begin_define
DECL|macro|RANDOM_TABLE_SIZE
define|#
directive|define
name|RANDOM_TABLE_SIZE
value|4096
end_define

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_dissolve_process
parameter_list|(
name|GeglOperation
modifier|*
name|op
parameter_list|,
name|void
modifier|*
name|in
parameter_list|,
name|void
modifier|*
name|layer
parameter_list|,
name|void
modifier|*
name|mask
parameter_list|,
name|void
modifier|*
name|out
parameter_list|,
name|glong
name|samples
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|result
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpLayerCompositeRegion
name|gimp_operation_dissolve_get_affected_region
parameter_list|(
name|GimpOperationLayerMode
modifier|*
name|layer_mode
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationDissolve,gimp_operation_dissolve,GIMP_TYPE_OPERATION_LAYER_MODE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationDissolve
argument_list|,
argument|gimp_operation_dissolve
argument_list|,
argument|GIMP_TYPE_OPERATION_LAYER_MODE
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|gint32
name|random_table
index|[
name|RANDOM_TABLE_SIZE
index|]
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
name|gimp_operation_dissolve_class_init
parameter_list|(
name|GimpOperationDissolveClass
modifier|*
name|klass
parameter_list|)
block|{
name|GeglOperationClass
modifier|*
name|operation_class
init|=
name|GEGL_OPERATION_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpOperationLayerModeClass
modifier|*
name|layer_mode_class
init|=
name|GIMP_OPERATION_LAYER_MODE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GRand
modifier|*
name|gr
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:dissolve"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP dissolve mode operation"
argument_list|,
literal|"categories"
argument_list|,
literal|"compositors"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|layer_mode_class
operator|->
name|process
operator|=
name|gimp_operation_dissolve_process
expr_stmt|;
name|layer_mode_class
operator|->
name|get_affected_region
operator|=
name|gimp_operation_dissolve_get_affected_region
expr_stmt|;
comment|/* generate a table of random seeds */
name|gr
operator|=
name|g_rand_new_with_seed
argument_list|(
literal|314159265
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
name|RANDOM_TABLE_SIZE
condition|;
name|i
operator|++
control|)
name|random_table
index|[
name|i
index|]
operator|=
name|g_rand_int
argument_list|(
name|gr
argument_list|)
expr_stmt|;
name|g_rand_free
argument_list|(
name|gr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_dissolve_init (GimpOperationDissolve * self)
name|gimp_operation_dissolve_init
parameter_list|(
name|GimpOperationDissolve
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_dissolve_process (GeglOperation * op,void * in_p,void * layer_p,void * mask_p,void * out_p,glong samples,const GeglRectangle * result,gint level)
name|gimp_operation_dissolve_process
parameter_list|(
name|GeglOperation
modifier|*
name|op
parameter_list|,
name|void
modifier|*
name|in_p
parameter_list|,
name|void
modifier|*
name|layer_p
parameter_list|,
name|void
modifier|*
name|mask_p
parameter_list|,
name|void
modifier|*
name|out_p
parameter_list|,
name|glong
name|samples
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|result
parameter_list|,
name|gint
name|level
parameter_list|)
block|{
name|GimpOperationLayerMode
modifier|*
name|layer_mode
init|=
operator|(
name|gpointer
operator|)
name|op
decl_stmt|;
name|gfloat
modifier|*
name|in
init|=
name|in_p
decl_stmt|;
name|gfloat
modifier|*
name|out
init|=
name|out_p
decl_stmt|;
name|gfloat
modifier|*
name|layer
init|=
name|layer_p
decl_stmt|;
name|gfloat
modifier|*
name|mask
init|=
name|mask_p
decl_stmt|;
name|gfloat
name|opacity
init|=
name|layer_mode
operator|->
name|opacity
decl_stmt|;
specifier|const
name|gboolean
name|has_mask
init|=
name|mask
operator|!=
name|NULL
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
name|result
operator|->
name|y
init|;
name|y
operator|<
name|result
operator|->
name|y
operator|+
name|result
operator|->
name|height
condition|;
name|y
operator|++
control|)
block|{
name|GRand
modifier|*
name|gr
init|=
name|g_rand_new_with_seed
argument_list|(
name|random_table
index|[
name|y
operator|%
name|RANDOM_TABLE_SIZE
index|]
argument_list|)
decl_stmt|;
comment|/* fast forward through the rows pseudo random sequence */
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|result
operator|->
name|x
condition|;
name|x
operator|++
control|)
name|g_rand_int
argument_list|(
name|gr
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
name|result
operator|->
name|x
init|;
name|x
operator|<
name|result
operator|->
name|x
operator|+
name|result
operator|->
name|width
condition|;
name|x
operator|++
control|)
block|{
name|gfloat
name|value
init|=
name|layer
index|[
name|ALPHA
index|]
operator|*
name|opacity
operator|*
literal|255
decl_stmt|;
if|if
condition|(
name|has_mask
condition|)
name|value
operator|*=
operator|*
name|mask
expr_stmt|;
if|if
condition|(
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
operator|>=
name|value
condition|)
block|{
name|out
index|[
literal|0
index|]
operator|=
name|in
index|[
literal|0
index|]
expr_stmt|;
name|out
index|[
literal|1
index|]
operator|=
name|in
index|[
literal|1
index|]
expr_stmt|;
name|out
index|[
literal|2
index|]
operator|=
name|in
index|[
literal|2
index|]
expr_stmt|;
if|if
condition|(
name|layer_mode
operator|->
name|real_composite_mode
operator|==
name|GIMP_LAYER_COMPOSITE_UNION
operator|||
name|layer_mode
operator|->
name|real_composite_mode
operator|==
name|GIMP_LAYER_COMPOSITE_CLIP_TO_BACKDROP
condition|)
block|{
name|out
index|[
literal|3
index|]
operator|=
name|in
index|[
literal|3
index|]
expr_stmt|;
block|}
else|else
block|{
name|out
index|[
literal|3
index|]
operator|=
literal|0.0f
expr_stmt|;
block|}
block|}
else|else
block|{
name|out
index|[
literal|0
index|]
operator|=
name|layer
index|[
literal|0
index|]
expr_stmt|;
name|out
index|[
literal|1
index|]
operator|=
name|layer
index|[
literal|1
index|]
expr_stmt|;
name|out
index|[
literal|2
index|]
operator|=
name|layer
index|[
literal|2
index|]
expr_stmt|;
if|if
condition|(
name|layer_mode
operator|->
name|real_composite_mode
operator|==
name|GIMP_LAYER_COMPOSITE_UNION
operator|||
name|layer_mode
operator|->
name|real_composite_mode
operator|==
name|GIMP_LAYER_COMPOSITE_CLIP_TO_LAYER
condition|)
block|{
name|out
index|[
literal|3
index|]
operator|=
literal|1.0f
expr_stmt|;
block|}
else|else
block|{
name|out
index|[
literal|3
index|]
operator|=
name|in
index|[
literal|3
index|]
expr_stmt|;
block|}
block|}
name|in
operator|+=
literal|4
expr_stmt|;
name|layer
operator|+=
literal|4
expr_stmt|;
name|out
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|has_mask
condition|)
name|mask
operator|++
expr_stmt|;
block|}
name|g_rand_free
argument_list|(
name|gr
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|GimpLayerCompositeRegion
DECL|function|gimp_operation_dissolve_get_affected_region (GimpOperationLayerMode * layer_mode)
name|gimp_operation_dissolve_get_affected_region
parameter_list|(
name|GimpOperationLayerMode
modifier|*
name|layer_mode
parameter_list|)
block|{
return|return
name|GIMP_LAYER_COMPOSITE_REGION_SOURCE
return|;
block|}
end_function

end_unit

