begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpgradientselect.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2ad56fc10108
block|{
DECL|member|gradient_callback
name|gchar
modifier|*
name|gradient_callback
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
DECL|member|gradient_name
name|gchar
modifier|*
name|gradient_name
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|gradient_data
name|gdouble
modifier|*
name|gradient_data
decl_stmt|;
DECL|member|callback
name|GimpRunGradientCallback
name|callback
decl_stmt|;
DECL|member|closing
name|gboolean
name|closing
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
DECL|member|data_destroy
name|GDestroyNotify
name|data_destroy
decl_stmt|;
DECL|typedef|GimpGradientData
block|}
name|GimpGradientData
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_gradient_data_free
parameter_list|(
name|GimpGradientData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|gimp_temp_gradient_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_temp_gradient_idle
parameter_list|(
name|GimpGradientData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_gradient_select_new (const gchar * title,const gchar * gradient_name,gint sample_size,GimpRunGradientCallback callback,gpointer data,GDestroyNotify data_destroy)
name|gimp_gradient_select_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|,
name|gint
name|sample_size
parameter_list|,
name|GimpRunGradientCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GDestroyNotify
name|data_destroy
parameter_list|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp_get_plug_in
argument_list|()
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|gchar
modifier|*
name|gradient_callback
decl_stmt|;
name|GimpGradientData
modifier|*
name|gradient_data
decl_stmt|;
name|gradient_callback
operator|=
name|gimp_pdb_temp_procedure_name
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|)
expr_stmt|;
name|gradient_data
operator|=
name|g_slice_new0
argument_list|(
name|GimpGradientData
argument_list|)
expr_stmt|;
name|gradient_data
operator|->
name|gradient_callback
operator|=
name|gradient_callback
expr_stmt|;
name|gradient_data
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|gradient_data
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|gradient_data
operator|->
name|data_destroy
operator|=
name|data_destroy
expr_stmt|;
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|gradient_callback
argument_list|,
name|GIMP_TEMPORARY
argument_list|,
name|gimp_temp_gradient_run
argument_list|,
name|gradient_data
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_gradient_data_free
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"gradient-name"
argument_list|,
literal|"Gradient name"
argument_list|,
literal|"The gradient name"
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"gradient-width"
argument_list|,
literal|"Gradient width"
argument_list|,
literal|"The gradient width"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_float_array
argument_list|(
literal|"gradient-data"
argument_list|,
literal|"Gradient data"
argument_list|,
literal|"The gradient "
literal|"data"
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"closing"
argument_list|,
literal|"Closing"
argument_list|,
literal|"If the dialog was "
literal|"closing"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_add_temp_procedure
argument_list|(
name|plug_in
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_gradients_popup
argument_list|(
name|gradient_callback
argument_list|,
name|title
argument_list|,
name|gradient_name
argument_list|,
name|sample_size
argument_list|)
condition|)
block|{
comment|/* Allow callbacks to be watched */
name|gimp_plug_in_extension_enable
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
return|return
name|gradient_callback
return|;
block|}
name|gimp_plug_in_remove_temp_procedure
argument_list|(
name|plug_in
argument_list|,
name|gradient_callback
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_gradient_select_destroy (const gchar * gradient_callback)
name|gimp_gradient_select_destroy
parameter_list|(
specifier|const
name|gchar
modifier|*
name|gradient_callback
parameter_list|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp_get_plug_in
argument_list|()
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|gradient_callback
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plug_in_remove_temp_procedure
argument_list|(
name|plug_in
argument_list|,
name|gradient_callback
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_data_free (GimpGradientData * data)
name|gimp_gradient_data_free
parameter_list|(
name|GimpGradientData
modifier|*
name|data
parameter_list|)
block|{
if|if
condition|(
name|data
operator|->
name|idle_id
condition|)
name|g_source_remove
argument_list|(
name|data
operator|->
name|idle_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|gradient_callback
condition|)
block|{
name|gimp_gradients_close_popup
argument_list|(
name|data
operator|->
name|gradient_callback
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|gradient_callback
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|data
operator|->
name|gradient_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|gradient_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|data_destroy
condition|)
name|data
operator|->
name|data_destroy
argument_list|(
name|data
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpGradientData
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|gimp_temp_gradient_run (GimpProcedure * procedure,const GimpValueArray * args,gpointer run_data)
name|gimp_temp_gradient_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
block|{
name|GimpGradientData
modifier|*
name|data
init|=
name|run_data
decl_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|gradient_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|gradient_data
argument_list|)
expr_stmt|;
name|data
operator|->
name|gradient_name
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|width
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|gradient_data
operator|=
name|gimp_value_dup_float_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|closing
operator|=
name|g_value_get_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|data
operator|->
name|idle_id
condition|)
name|data
operator|->
name|idle_id
operator|=
name|g_idle_add
argument_list|(
operator|(
name|GSourceFunc
operator|)
name|gimp_temp_gradient_idle
argument_list|,
name|data
argument_list|)
expr_stmt|;
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_SUCCESS
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_temp_gradient_idle (GimpGradientData * data)
name|gimp_temp_gradient_idle
parameter_list|(
name|GimpGradientData
modifier|*
name|data
parameter_list|)
block|{
name|data
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|callback
condition|)
name|data
operator|->
name|callback
argument_list|(
name|data
operator|->
name|gradient_name
argument_list|,
name|data
operator|->
name|width
argument_list|,
name|data
operator|->
name|gradient_data
argument_list|,
name|data
operator|->
name|closing
argument_list|,
name|data
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|closing
condition|)
block|{
name|gchar
modifier|*
name|gradient_callback
init|=
name|data
operator|->
name|gradient_callback
decl_stmt|;
name|data
operator|->
name|gradient_callback
operator|=
name|NULL
expr_stmt|;
name|gimp_gradient_select_destroy
argument_list|(
name|gradient_callback
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gradient_callback
argument_list|)
expr_stmt|;
block|}
return|return
name|G_SOURCE_REMOVE
return|;
block|}
end_function

end_unit

