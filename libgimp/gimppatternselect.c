begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppatternselect.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
DECL|struct|__anon2b731b9c0108
block|{
DECL|member|pattern_callback
name|gchar
modifier|*
name|pattern_callback
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
DECL|member|pattern_name
name|gchar
modifier|*
name|pattern_name
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|bytes
name|gint
name|bytes
decl_stmt|;
DECL|member|pattern_mask_data
name|guchar
modifier|*
name|pattern_mask_data
decl_stmt|;
DECL|member|callback
name|GimpRunPatternCallback
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
DECL|typedef|GimpPatternData
block|}
name|GimpPatternData
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_pattern_data_free
parameter_list|(
name|GimpPatternData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|gimp_temp_pattern_run
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
name|gimp_temp_pattern_idle
parameter_list|(
name|GimpPatternData
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
DECL|function|gimp_pattern_select_new (const gchar * title,const gchar * pattern_name,GimpRunPatternCallback callback,gpointer data,GDestroyNotify data_destroy)
name|gimp_pattern_select_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pattern_name
parameter_list|,
name|GimpRunPatternCallback
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
name|pattern_callback
decl_stmt|;
name|GimpPatternData
modifier|*
name|pattern_data
decl_stmt|;
name|pattern_callback
operator|=
name|gimp_pdb_temp_procedure_name
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|)
expr_stmt|;
name|pattern_data
operator|=
name|g_slice_new0
argument_list|(
name|GimpPatternData
argument_list|)
expr_stmt|;
name|pattern_data
operator|->
name|pattern_callback
operator|=
name|pattern_callback
expr_stmt|;
name|pattern_data
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|pattern_data
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|pattern_data
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
name|pattern_callback
argument_list|,
name|GIMP_TEMPORARY
argument_list|,
name|gimp_temp_pattern_run
argument_list|,
name|pattern_data
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_pattern_data_free
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"pattern-name"
argument_list|,
literal|"Pattern name"
argument_list|,
literal|"The pattern name"
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
literal|"mask-width"
argument_list|,
literal|"Mask width"
argument_list|,
literal|"Pattern width"
argument_list|,
literal|0
argument_list|,
literal|10000
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
name|g_param_spec_int
argument_list|(
literal|"mask-height"
argument_list|,
literal|"Mask height"
argument_list|,
literal|"Pattern height"
argument_list|,
literal|0
argument_list|,
literal|10000
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
name|g_param_spec_int
argument_list|(
literal|"mask-bpp"
argument_list|,
literal|"Mask bpp"
argument_list|,
literal|"Pattern bytes per pixel"
argument_list|,
literal|0
argument_list|,
literal|10000
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
name|gimp_param_spec_int32
argument_list|(
literal|"mask-len"
argument_list|,
literal|"Mask length"
argument_list|,
literal|"Length of pattern "
literal|"mask data"
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
name|gimp_param_spec_int8_array
argument_list|(
literal|"mask-data"
argument_list|,
literal|"Mask data"
argument_list|,
literal|"The pattern mask "
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
literal|"cloaing"
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
name|gimp_patterns_popup
argument_list|(
name|pattern_callback
argument_list|,
name|title
argument_list|,
name|pattern_name
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
name|pattern_callback
return|;
block|}
name|gimp_plug_in_remove_temp_procedure
argument_list|(
name|plug_in
argument_list|,
name|pattern_callback
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_pattern_select_destroy (const gchar * pattern_callback)
name|gimp_pattern_select_destroy
parameter_list|(
specifier|const
name|gchar
modifier|*
name|pattern_callback
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
name|pattern_callback
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plug_in_remove_temp_procedure
argument_list|(
name|plug_in
argument_list|,
name|pattern_callback
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
DECL|function|gimp_pattern_data_free (GimpPatternData * data)
name|gimp_pattern_data_free
parameter_list|(
name|GimpPatternData
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
name|pattern_callback
condition|)
block|{
name|gimp_patterns_close_popup
argument_list|(
name|data
operator|->
name|pattern_callback
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|pattern_callback
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|data
operator|->
name|pattern_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|pattern_mask_data
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
name|GimpPatternData
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
DECL|function|gimp_temp_pattern_run (GimpProcedure * procedure,const GimpValueArray * args,gpointer run_data)
name|gimp_temp_pattern_run
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
name|GimpPatternData
modifier|*
name|data
init|=
name|run_data
decl_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|pattern_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|pattern_mask_data
argument_list|)
expr_stmt|;
name|data
operator|->
name|pattern_name
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
name|height
operator|=
name|g_value_get_int
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
name|bytes
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|pattern_mask_data
operator|=
name|gimp_value_dup_int8_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|5
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
literal|6
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
name|gimp_temp_pattern_idle
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
DECL|function|gimp_temp_pattern_idle (GimpPatternData * data)
name|gimp_temp_pattern_idle
parameter_list|(
name|GimpPatternData
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
name|pattern_name
argument_list|,
name|data
operator|->
name|width
argument_list|,
name|data
operator|->
name|height
argument_list|,
name|data
operator|->
name|bytes
argument_list|,
name|data
operator|->
name|pattern_mask_data
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
name|pattern_callback
init|=
name|data
operator|->
name|pattern_callback
decl_stmt|;
name|data
operator|->
name|pattern_callback
operator|=
name|NULL
expr_stmt|;
name|gimp_pattern_select_destroy
argument_list|(
name|pattern_callback
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pattern_callback
argument_list|)
expr_stmt|;
block|}
return|return
name|G_SOURCE_REMOVE
return|;
block|}
end_function

end_unit

