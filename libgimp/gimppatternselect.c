begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppatternselect.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
DECL|struct|__anon290f5fef0108
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
name|void
name|gimp_temp_pattern_run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_temp_pattern_run_idle
parameter_list|(
name|GimpPatternData
modifier|*
name|pattern_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|gimp_pattern_select_ht
specifier|static
name|GHashTable
modifier|*
name|gimp_pattern_select_ht
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_pattern_select_new (const gchar * title,const gchar * pattern_name,GimpRunPatternCallback callback,gpointer data)
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
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"str"
block|,
literal|"String"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"mask width"
block|,
literal|"Pattern width"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"mask height"
block|,
literal|"Pattern height"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"mask bpp"
block|,
literal|"Pattern bytes per pixel"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"mask len"
block|,
literal|"Length of pattern mask data"
block|}
block|,
block|{
name|GIMP_PDB_INT8ARRAY
block|,
literal|"mask data"
block|,
literal|"The pattern mask data"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"dialog status"
block|,
literal|"If the dialog was closing "
literal|"[0 = No, 1 = Yes]"
block|}
block|}
decl_stmt|;
name|gchar
modifier|*
name|pattern_callback
init|=
name|gimp_procedural_db_temp_name
argument_list|()
decl_stmt|;
name|gimp_install_temp_proc
argument_list|(
name|pattern_callback
argument_list|,
literal|"Temporary pattern popup callback procedure"
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
name|NULL
argument_list|,
literal|""
argument_list|,
name|GIMP_TEMPORARY
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|,
name|gimp_temp_pattern_run
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
name|GimpPatternData
modifier|*
name|pattern_data
decl_stmt|;
name|gimp_extension_enable
argument_list|()
expr_stmt|;
comment|/* Allow callbacks to be watched */
comment|/* Now add to hash table so we can find it again */
if|if
condition|(
operator|!
name|gimp_pattern_select_ht
condition|)
block|{
name|gimp_pattern_select_ht
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
name|g_free
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_pattern_data_free
argument_list|)
expr_stmt|;
block|}
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
name|g_hash_table_insert
argument_list|(
name|gimp_pattern_select_ht
argument_list|,
name|pattern_callback
argument_list|,
name|pattern_data
argument_list|)
expr_stmt|;
return|return
name|pattern_callback
return|;
block|}
name|gimp_uninstall_temp_proc
argument_list|(
name|pattern_callback
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
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
name|GimpPatternData
modifier|*
name|pattern_data
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|pattern_callback
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_pattern_select_ht
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|pattern_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp_pattern_select_ht
argument_list|,
name|pattern_callback
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pattern_data
condition|)
block|{
name|g_warning
argument_list|(
literal|"Can't find internal pattern data"
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|pattern_data
operator|->
name|idle_id
condition|)
name|g_source_remove
argument_list|(
name|pattern_data
operator|->
name|idle_id
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pattern_data
operator|->
name|pattern_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pattern_data
operator|->
name|pattern_mask_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|pattern_data
operator|->
name|pattern_callback
condition|)
name|gimp_patterns_close_popup
argument_list|(
name|pattern_data
operator|->
name|pattern_callback
argument_list|)
expr_stmt|;
name|gimp_uninstall_temp_proc
argument_list|(
name|pattern_callback
argument_list|)
expr_stmt|;
name|g_hash_table_remove
argument_list|(
name|gimp_pattern_select_ht
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
name|void
DECL|function|gimp_temp_pattern_run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|gimp_temp_pattern_run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|GimpPatternData
modifier|*
name|pattern_data
decl_stmt|;
name|pattern_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp_pattern_select_ht
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pattern_data
condition|)
block|{
name|g_warning
argument_list|(
literal|"Can't find internal pattern data"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
name|pattern_data
operator|->
name|pattern_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pattern_data
operator|->
name|pattern_mask_data
argument_list|)
expr_stmt|;
name|pattern_data
operator|->
name|pattern_name
operator|=
name|g_strdup
argument_list|(
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|pattern_data
operator|->
name|width
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|pattern_data
operator|->
name|height
operator|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|pattern_data
operator|->
name|bytes
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|pattern_data
operator|->
name|pattern_mask_data
operator|=
name|g_memdup
argument_list|(
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int8array
argument_list|,
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
name|pattern_data
operator|->
name|closing
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
if|if
condition|(
operator|!
name|pattern_data
operator|->
name|idle_id
condition|)
name|pattern_data
operator|->
name|idle_id
operator|=
name|g_idle_add
argument_list|(
operator|(
name|GSourceFunc
operator|)
name|gimp_temp_pattern_run_idle
argument_list|,
name|pattern_data
argument_list|)
expr_stmt|;
block|}
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_temp_pattern_run_idle (GimpPatternData * pattern_data)
name|gimp_temp_pattern_run_idle
parameter_list|(
name|GimpPatternData
modifier|*
name|pattern_data
parameter_list|)
block|{
name|pattern_data
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|pattern_data
operator|->
name|callback
condition|)
name|pattern_data
operator|->
name|callback
argument_list|(
name|pattern_data
operator|->
name|pattern_name
argument_list|,
name|pattern_data
operator|->
name|width
argument_list|,
name|pattern_data
operator|->
name|height
argument_list|,
name|pattern_data
operator|->
name|bytes
argument_list|,
name|pattern_data
operator|->
name|pattern_mask_data
argument_list|,
name|pattern_data
operator|->
name|closing
argument_list|,
name|pattern_data
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|pattern_data
operator|->
name|closing
condition|)
block|{
name|gchar
modifier|*
name|pattern_callback
init|=
name|pattern_data
operator|->
name|pattern_callback
decl_stmt|;
name|pattern_data
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
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

