begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpproceduraldb_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_function
name|void
DECL|function|gimp_procedural_db_set_data (gchar * id,gpointer data,guint32 length)
name|gimp_procedural_db_set_data
parameter_list|(
name|gchar
modifier|*
name|id
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint32
name|length
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_procedural_db_set_data"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_STRING
argument_list|,
name|id
argument_list|,
name|PARAM_INT32
argument_list|,
name|length
argument_list|,
name|PARAM_INT8ARRAY
argument_list|,
name|data
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|guint32
DECL|function|gimp_procedural_db_get_data_size (gchar * id)
name|gimp_procedural_db_get_data_size
parameter_list|(
name|gchar
modifier|*
name|id
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|guint32
name|length
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_procedural_db_get_data_size"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_STRING
argument_list|,
name|id
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|length
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
else|else
name|length
operator|=
literal|0
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|length
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_procedural_db_get_data (gchar * id,gpointer data)
name|gimp_procedural_db_get_data
parameter_list|(
name|gchar
modifier|*
name|id
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint
name|length
decl_stmt|;
name|gchar
modifier|*
name|returned_data
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_procedural_db_get_data"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_STRING
argument_list|,
name|id
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
name|length
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|returned_data
operator|=
operator|(
name|gchar
operator|*
operator|)
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int8array
expr_stmt|;
name|memcpy
argument_list|(
name|data
argument_list|,
name|returned_data
argument_list|,
name|length
argument_list|)
expr_stmt|;
block|}
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_procedural_db_query (gchar * name_regexp,gchar * blurb_regexp,gchar * help_regexp,gchar * author_regexp,gchar * copyright_regexp,gchar * date_regexp,gchar * proc_type_regexp,gint * nprocs,gchar *** proc_names)
name|gimp_procedural_db_query
parameter_list|(
name|gchar
modifier|*
name|name_regexp
parameter_list|,
name|gchar
modifier|*
name|blurb_regexp
parameter_list|,
name|gchar
modifier|*
name|help_regexp
parameter_list|,
name|gchar
modifier|*
name|author_regexp
parameter_list|,
name|gchar
modifier|*
name|copyright_regexp
parameter_list|,
name|gchar
modifier|*
name|date_regexp
parameter_list|,
name|gchar
modifier|*
name|proc_type_regexp
parameter_list|,
name|gint
modifier|*
name|nprocs
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|proc_names
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_procedural_db_query"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_STRING
argument_list|,
name|name_regexp
argument_list|,
name|PARAM_STRING
argument_list|,
name|blurb_regexp
argument_list|,
name|PARAM_STRING
argument_list|,
name|help_regexp
argument_list|,
name|PARAM_STRING
argument_list|,
name|author_regexp
argument_list|,
name|PARAM_STRING
argument_list|,
name|copyright_regexp
argument_list|,
name|PARAM_STRING
argument_list|,
name|date_regexp
argument_list|,
name|PARAM_STRING
argument_list|,
name|proc_type_regexp
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
operator|*
name|nprocs
operator|=
literal|0
expr_stmt|;
operator|*
name|proc_names
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
operator|*
name|nprocs
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|proc_names
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
operator|*
name|nprocs
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
operator|*
name|nprocs
condition|;
name|i
operator|++
control|)
operator|(
operator|*
name|proc_names
operator|)
index|[
name|i
index|]
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_stringarray
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_procedural_db_proc_info (gchar * proc_name,gchar ** proc_blurb,gchar ** proc_help,gchar ** proc_author,gchar ** proc_copyright,gchar ** proc_date,gint * proc_type,gint * nparams,gint * nreturn_vals,GimpParamDef ** params,GimpParamDef ** return_vals)
name|gimp_procedural_db_proc_info
parameter_list|(
name|gchar
modifier|*
name|proc_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|proc_blurb
parameter_list|,
name|gchar
modifier|*
modifier|*
name|proc_help
parameter_list|,
name|gchar
modifier|*
modifier|*
name|proc_author
parameter_list|,
name|gchar
modifier|*
modifier|*
name|proc_copyright
parameter_list|,
name|gchar
modifier|*
modifier|*
name|proc_date
parameter_list|,
name|gint
modifier|*
name|proc_type
parameter_list|,
name|gint
modifier|*
name|nparams
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParamDef
modifier|*
modifier|*
name|params
parameter_list|,
name|GimpParamDef
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
name|GimpParam
modifier|*
name|ret_vals
decl_stmt|;
name|gint
name|nret_vals
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|ret_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_procedural_db_proc_info"
argument_list|,
operator|&
name|nret_vals
argument_list|,
name|PARAM_STRING
argument_list|,
name|proc_name
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|ret_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
operator|*
name|proc_blurb
operator|=
name|g_strdup
argument_list|(
name|ret_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
operator|*
name|proc_help
operator|=
name|g_strdup
argument_list|(
name|ret_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
operator|*
name|proc_author
operator|=
name|g_strdup
argument_list|(
name|ret_vals
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
operator|*
name|proc_copyright
operator|=
name|g_strdup
argument_list|(
name|ret_vals
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
operator|*
name|proc_date
operator|=
name|g_strdup
argument_list|(
name|ret_vals
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
operator|*
name|proc_type
operator|=
name|ret_vals
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|nparams
operator|=
name|ret_vals
index|[
literal|7
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
name|ret_vals
index|[
literal|8
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|params
operator|=
name|g_new
argument_list|(
name|GimpParamDef
argument_list|,
operator|*
name|nparams
argument_list|)
expr_stmt|;
operator|*
name|return_vals
operator|=
name|g_new
argument_list|(
name|GimpParamDef
argument_list|,
operator|*
name|nreturn_vals
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
operator|*
name|nparams
condition|;
name|i
operator|++
control|)
block|{
name|GimpParam
modifier|*
name|rvals
decl_stmt|;
name|gint
name|nrvals
decl_stmt|;
name|rvals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_procedural_db_proc_arg"
argument_list|,
operator|&
name|nrvals
argument_list|,
name|PARAM_STRING
argument_list|,
name|proc_name
argument_list|,
name|PARAM_INT32
argument_list|,
name|i
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|rvals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
operator|(
operator|*
name|params
operator|)
index|[
name|i
index|]
operator|.
name|type
operator|=
name|rvals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|(
operator|*
name|params
operator|)
index|[
name|i
index|]
operator|.
name|name
operator|=
name|g_strdup
argument_list|(
name|rvals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
operator|(
operator|*
name|params
operator|)
index|[
name|i
index|]
operator|.
name|description
operator|=
name|g_strdup
argument_list|(
name|rvals
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
operator|*
name|params
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
operator|*
name|return_vals
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|rvals
argument_list|,
name|nrvals
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_destroy_params
argument_list|(
name|rvals
argument_list|,
name|nrvals
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
operator|*
name|nreturn_vals
condition|;
name|i
operator|++
control|)
block|{
name|GimpParam
modifier|*
name|rvals
decl_stmt|;
name|gint
name|nrvals
decl_stmt|;
name|rvals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_procedural_db_proc_val"
argument_list|,
operator|&
name|nrvals
argument_list|,
name|PARAM_STRING
argument_list|,
name|proc_name
argument_list|,
name|PARAM_INT32
argument_list|,
name|i
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|rvals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
operator|(
operator|*
name|return_vals
operator|)
index|[
name|i
index|]
operator|.
name|type
operator|=
name|rvals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|(
operator|*
name|return_vals
operator|)
index|[
name|i
index|]
operator|.
name|name
operator|=
name|g_strdup
argument_list|(
name|rvals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
operator|(
operator|*
name|return_vals
operator|)
index|[
name|i
index|]
operator|.
name|description
operator|=
name|g_strdup
argument_list|(
name|rvals
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
operator|*
name|params
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
operator|*
name|return_vals
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|rvals
argument_list|,
name|nrvals
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_destroy_params
argument_list|(
name|rvals
argument_list|,
name|nrvals
argument_list|)
expr_stmt|;
block|}
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|ret_vals
argument_list|,
name|nret_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

