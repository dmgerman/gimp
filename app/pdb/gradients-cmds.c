begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl. */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer-filter.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"internal-procs.h"
end_include

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|gradients_refresh_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|gradients_refresh_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gimp_data_factory_data_refresh
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|,
name|context
argument_list|)
expr_stmt|;
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|gradients_get_list_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|gradients_get_list_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|filter
decl_stmt|;
name|gint32
name|num_gradients
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|gradient_list
init|=
name|NULL
decl_stmt|;
name|filter
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|gradient_list
operator|=
name|gimp_container_get_filtered_name_array
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
argument_list|,
name|filter
argument_list|,
operator|&
name|num_gradients
argument_list|)
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|num_gradients
argument_list|)
expr_stmt|;
name|gimp_value_take_stringarray
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|2
index|]
argument_list|,
name|gradient_list
argument_list|,
name|num_gradients
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|gradients_sample_uniform_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|gradients_sample_uniform_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint32
name|num_samples
decl_stmt|;
name|gboolean
name|reverse
decl_stmt|;
name|gint32
name|array_length
init|=
literal|0
decl_stmt|;
name|gdouble
modifier|*
name|color_samples
init|=
name|NULL
decl_stmt|;
name|num_samples
operator|=
name|g_value_get_int
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|reverse
operator|=
name|g_value_get_boolean
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|GimpGradientSegment
modifier|*
name|seg
init|=
name|NULL
decl_stmt|;
name|gdouble
name|pos
decl_stmt|,
name|delta
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gdouble
modifier|*
name|pv
decl_stmt|;
name|pos
operator|=
literal|0.0
expr_stmt|;
name|delta
operator|=
literal|1.0
operator|/
operator|(
name|num_samples
operator|-
literal|1
operator|)
expr_stmt|;
name|array_length
operator|=
name|num_samples
operator|*
literal|4
expr_stmt|;
name|pv
operator|=
name|color_samples
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|array_length
argument_list|)
expr_stmt|;
name|gradient
operator|=
name|gimp_context_get_gradient
argument_list|(
name|context
argument_list|)
expr_stmt|;
while|while
condition|(
name|num_samples
operator|--
condition|)
block|{
name|seg
operator|=
name|gimp_gradient_get_color_at
argument_list|(
name|gradient
argument_list|,
name|context
argument_list|,
name|seg
argument_list|,
name|pos
argument_list|,
name|reverse
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|r
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|g
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|b
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|a
expr_stmt|;
name|pos
operator|+=
name|delta
expr_stmt|;
block|}
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|array_length
argument_list|)
expr_stmt|;
name|gimp_value_take_floatarray
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|2
index|]
argument_list|,
name|color_samples
argument_list|,
name|array_length
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|gradients_sample_custom_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|gradients_sample_custom_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint32
name|num_samples
decl_stmt|;
specifier|const
name|gdouble
modifier|*
name|positions
decl_stmt|;
name|gboolean
name|reverse
decl_stmt|;
name|gint32
name|array_length
init|=
literal|0
decl_stmt|;
name|gdouble
modifier|*
name|color_samples
init|=
name|NULL
decl_stmt|;
name|num_samples
operator|=
name|g_value_get_int
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|positions
operator|=
name|gimp_value_get_floatarray
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|reverse
operator|=
name|g_value_get_boolean
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|GimpGradientSegment
modifier|*
name|seg
init|=
name|NULL
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gdouble
modifier|*
name|pv
decl_stmt|;
name|array_length
operator|=
name|num_samples
operator|*
literal|4
expr_stmt|;
name|pv
operator|=
name|color_samples
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|array_length
argument_list|)
expr_stmt|;
name|gradient
operator|=
name|gimp_context_get_gradient
argument_list|(
name|context
argument_list|)
expr_stmt|;
while|while
condition|(
name|num_samples
operator|--
condition|)
block|{
name|seg
operator|=
name|gimp_gradient_get_color_at
argument_list|(
name|gradient
argument_list|,
name|context
argument_list|,
name|seg
argument_list|,
operator|*
name|positions
argument_list|,
name|reverse
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|r
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|g
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|b
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|a
expr_stmt|;
name|positions
operator|++
expr_stmt|;
block|}
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|array_length
argument_list|)
expr_stmt|;
name|gimp_value_take_floatarray
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|2
index|]
argument_list|,
name|color_samples
argument_list|,
name|array_length
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|gradients_get_gradient_data_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|gradients_get_gradient_data_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|gint32
name|sample_size
decl_stmt|;
name|gboolean
name|reverse
decl_stmt|;
name|gchar
modifier|*
name|actual_name
init|=
name|NULL
decl_stmt|;
name|gint32
name|width
init|=
literal|0
decl_stmt|;
name|gdouble
modifier|*
name|grad_data
init|=
name|NULL
decl_stmt|;
name|name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|sample_size
operator|=
name|g_value_get_int
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|reverse
operator|=
name|g_value_get_boolean
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
if|if
condition|(
name|sample_size
operator|<
literal|1
operator|||
name|sample_size
operator|>
literal|10000
condition|)
name|sample_size
operator|=
name|GIMP_GRADIENT_DEFAULT_SAMPLE_SIZE
expr_stmt|;
if|if
condition|(
name|name
operator|&&
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
name|gradient
operator|=
name|gimp_pdb_get_gradient
argument_list|(
name|gimp
argument_list|,
name|name
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
else|else
name|gradient
operator|=
name|gimp_context_get_gradient
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|gradient
condition|)
block|{
name|GimpGradientSegment
modifier|*
name|seg
init|=
name|NULL
decl_stmt|;
name|gdouble
modifier|*
name|pv
decl_stmt|;
name|gdouble
name|pos
decl_stmt|,
name|delta
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|pos
operator|=
literal|0.0
expr_stmt|;
name|delta
operator|=
literal|1.0
operator|/
operator|(
name|sample_size
operator|-
literal|1
operator|)
expr_stmt|;
name|actual_name
operator|=
name|g_strdup
argument_list|(
name|gimp_object_get_name
argument_list|(
name|gradient
argument_list|)
argument_list|)
expr_stmt|;
name|grad_data
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|sample_size
operator|*
literal|4
argument_list|)
expr_stmt|;
name|width
operator|=
name|sample_size
operator|*
literal|4
expr_stmt|;
name|pv
operator|=
name|grad_data
expr_stmt|;
while|while
condition|(
name|sample_size
condition|)
block|{
name|seg
operator|=
name|gimp_gradient_get_color_at
argument_list|(
name|gradient
argument_list|,
name|context
argument_list|,
name|seg
argument_list|,
name|pos
argument_list|,
name|reverse
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|r
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|g
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|b
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|a
expr_stmt|;
name|pos
operator|+=
name|delta
expr_stmt|;
block|}
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|g_value_take_string
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|actual_name
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|2
index|]
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|gimp_value_take_floatarray
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|3
index|]
argument_list|,
name|grad_data
argument_list|,
name|width
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|void
DECL|function|register_gradients_procs (GimpPDB * pdb)
name|register_gradients_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
comment|/*    * gimp-gradients-refresh    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|gradients_refresh_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-gradients-refresh"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-gradients-refresh"
argument_list|,
literal|"Refresh current gradients. This function always succeeds."
argument_list|,
literal|"This procedure retrieves all gradients currently in the user's gradient path and updates the gradient dialogs accordingly."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2002"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-gradients-get-list    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|gradients_get_list_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-gradients-get-list"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-gradients-get-list"
argument_list|,
literal|"Retrieve the list of loaded gradients."
argument_list|,
literal|"This procedure returns a list of the gradients that are currently loaded. You can later use the 'gimp-context-set-gradient' function to set the active gradient."
argument_list|,
literal|"Federico Mena Quintero"
argument_list|,
literal|"Federico Mena Quintero"
argument_list|,
literal|"1997"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"filter"
argument_list|,
literal|"filter"
argument_list|,
literal|"An optional regular expression used to filter the list"
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-gradients"
argument_list|,
literal|"num gradients"
argument_list|,
literal|"The number of loaded gradients"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string_array
argument_list|(
literal|"gradient-list"
argument_list|,
literal|"gradient list"
argument_list|,
literal|"The list of gradient names"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-gradients-sample-uniform    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|gradients_sample_uniform_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-gradients-sample-uniform"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-gradients-sample-uniform"
argument_list|,
literal|"This procedure is deprecated! Use 'gimp-gradient-get-uniform-samples' instead."
argument_list|,
literal|"This procedure is deprecated! Use 'gimp-gradient-get-uniform-samples' instead."
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|"gimp-gradient-get-uniform-samples"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-samples"
argument_list|,
literal|"num samples"
argument_list|,
literal|"The number of samples to take"
argument_list|,
literal|2
argument_list|,
name|G_MAXINT32
argument_list|,
literal|2
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"reverse"
argument_list|,
literal|"reverse"
argument_list|,
literal|"Use the reverse gradient"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"array-length"
argument_list|,
literal|"array length"
argument_list|,
literal|"Length of the color_samples array (4 * num_samples)"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_float_array
argument_list|(
literal|"color-samples"
argument_list|,
literal|"color samples"
argument_list|,
literal|"Color samples: { R1, G1, B1, A1, ..., Rn, Gn, Bn, An }"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-gradients-sample-custom    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|gradients_sample_custom_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-gradients-sample-custom"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-gradients-sample-custom"
argument_list|,
literal|"This procedure is deprecated! Use 'gimp-gradient-get-custom-samples' instead."
argument_list|,
literal|"This procedure is deprecated! Use 'gimp-gradient-get-custom-samples' instead."
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|"gimp-gradient-get-custom-samples"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-samples"
argument_list|,
literal|"num samples"
argument_list|,
literal|"The number of samples to take"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_float_array
argument_list|(
literal|"positions"
argument_list|,
literal|"positions"
argument_list|,
literal|"The list of positions to sample along the gradient"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"reverse"
argument_list|,
literal|"reverse"
argument_list|,
literal|"Use the reverse gradient"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"array-length"
argument_list|,
literal|"array length"
argument_list|,
literal|"Length of the color_samples array (4 * num_samples)"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_float_array
argument_list|(
literal|"color-samples"
argument_list|,
literal|"color samples"
argument_list|,
literal|"Color samples: { R1, G1, B1, A1, ..., Rn, Gn, Bn, An }"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-gradients-get-gradient-data    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|gradients_get_gradient_data_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-gradients-get-gradient-data"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-gradients-get-gradient-data"
argument_list|,
literal|"This procedure is deprecated! Use 'gimp-gradient-get-uniform-samples' instead."
argument_list|,
literal|"This procedure is deprecated! Use 'gimp-gradient-get-uniform-samples' instead."
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|"gimp-gradient-get-uniform-samples"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"name"
argument_list|,
literal|"name"
argument_list|,
literal|"The gradient name (\"\" means current active gradient)"
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"sample-size"
argument_list|,
literal|"sample size"
argument_list|,
literal|"Size of the sample to return when the gradient is changed"
argument_list|,
literal|1
argument_list|,
literal|10000
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|GIMP_PARAM_NO_VALIDATE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"reverse"
argument_list|,
literal|"reverse"
argument_list|,
literal|"Use the reverse gradient"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"actual-name"
argument_list|,
literal|"actual name"
argument_list|,
literal|"The gradient name"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"width"
argument_list|,
literal|"width"
argument_list|,
literal|"The gradient sample width (r,g,b,a)"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_float_array
argument_list|(
literal|"grad-data"
argument_list|,
literal|"grad data"
argument_list|,
literal|"The gradient sample data"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

