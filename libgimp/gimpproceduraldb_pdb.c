begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpproceduraldb_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_function
name|void
DECL|function|gimp_procedural_db_dump (gchar * filename)
name|gimp_procedural_db_dump
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_procedural_db_dump"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|filename
argument_list|,
name|GIMP_PDB_END
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
name|void
DECL|function|gimp_procedural_db_query (gchar * name,gchar * blurb,gchar * help,gchar * author,gchar * copyright,gchar * date,gchar * proc_type,gint * num_matches,gchar *** procedure_names)
name|gimp_procedural_db_query
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
name|date
parameter_list|,
name|gchar
modifier|*
name|proc_type
parameter_list|,
name|gint
modifier|*
name|num_matches
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|procedure_names
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
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|blurb
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|help
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|author
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|copyright
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|date
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|proc_type
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|num_matches
operator|=
literal|0
expr_stmt|;
operator|*
name|procedure_names
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
name|GIMP_PDB_SUCCESS
condition|)
block|{
operator|*
name|num_matches
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
name|procedure_names
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
operator|*
name|num_matches
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
name|num_matches
condition|;
name|i
operator|++
control|)
operator|(
operator|*
name|procedure_names
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
name|void
DECL|function|_gimp_procedural_db_proc_info (gchar * procedure,gchar ** blurb,gchar ** help,gchar ** author,gchar ** copyright,gchar ** date,GimpPDBProcType * proc_type,gint * num_args,gint * num_values)
name|_gimp_procedural_db_proc_info
parameter_list|(
name|gchar
modifier|*
name|procedure
parameter_list|,
name|gchar
modifier|*
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
modifier|*
name|date
parameter_list|,
name|GimpPDBProcType
modifier|*
name|proc_type
parameter_list|,
name|gint
modifier|*
name|num_args
parameter_list|,
name|gint
modifier|*
name|num_values
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_procedural_db_proc_info"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|procedure
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|blurb
operator|=
name|NULL
expr_stmt|;
operator|*
name|help
operator|=
name|NULL
expr_stmt|;
operator|*
name|author
operator|=
name|NULL
expr_stmt|;
operator|*
name|copyright
operator|=
name|NULL
expr_stmt|;
operator|*
name|date
operator|=
name|NULL
expr_stmt|;
operator|*
name|proc_type
operator|=
literal|0
expr_stmt|;
operator|*
name|num_args
operator|=
literal|0
expr_stmt|;
operator|*
name|num_values
operator|=
literal|0
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
name|GIMP_PDB_SUCCESS
condition|)
block|{
operator|*
name|blurb
operator|=
name|g_strdup
argument_list|(
name|return_vals
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
name|help
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
name|d_string
argument_list|)
expr_stmt|;
operator|*
name|author
operator|=
name|g_strdup
argument_list|(
name|return_vals
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
name|copyright
operator|=
name|g_strdup
argument_list|(
name|return_vals
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
name|date
operator|=
name|g_strdup
argument_list|(
name|return_vals
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
name|return_vals
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|num_args
operator|=
name|return_vals
index|[
literal|7
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|num_values
operator|=
name|return_vals
index|[
literal|8
index|]
operator|.
name|data
operator|.
name|d_int32
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
DECL|function|_gimp_procedural_db_proc_arg (gchar * procedure,gint arg_num,GimpPDBArgType * arg_type,gchar ** arg_name,gchar ** arg_desc)
name|_gimp_procedural_db_proc_arg
parameter_list|(
name|gchar
modifier|*
name|procedure
parameter_list|,
name|gint
name|arg_num
parameter_list|,
name|GimpPDBArgType
modifier|*
name|arg_type
parameter_list|,
name|gchar
modifier|*
modifier|*
name|arg_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|arg_desc
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_procedural_db_proc_arg"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|arg_num
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|arg_type
operator|=
literal|0
expr_stmt|;
operator|*
name|arg_name
operator|=
name|NULL
expr_stmt|;
operator|*
name|arg_desc
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
name|GIMP_PDB_SUCCESS
condition|)
block|{
operator|*
name|arg_type
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
name|arg_name
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
name|d_string
argument_list|)
expr_stmt|;
operator|*
name|arg_desc
operator|=
name|g_strdup
argument_list|(
name|return_vals
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
DECL|function|_gimp_procedural_db_proc_val (gchar * procedure,gint val_num,GimpPDBArgType * val_type,gchar ** val_name,gchar ** val_desc)
name|_gimp_procedural_db_proc_val
parameter_list|(
name|gchar
modifier|*
name|procedure
parameter_list|,
name|gint
name|val_num
parameter_list|,
name|GimpPDBArgType
modifier|*
name|val_type
parameter_list|,
name|gchar
modifier|*
modifier|*
name|val_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|val_desc
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_procedural_db_proc_val"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|val_num
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|val_type
operator|=
literal|0
expr_stmt|;
operator|*
name|val_name
operator|=
name|NULL
expr_stmt|;
operator|*
name|val_desc
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
name|GIMP_PDB_SUCCESS
condition|)
block|{
operator|*
name|val_type
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
name|val_name
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
name|d_string
argument_list|)
expr_stmt|;
operator|*
name|val_desc
operator|=
name|g_strdup
argument_list|(
name|return_vals
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
DECL|function|_gimp_procedural_db_get_data (gchar * identifier,gint * bytes,guint8 ** data)
name|_gimp_procedural_db_get_data
parameter_list|(
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gint
modifier|*
name|bytes
parameter_list|,
name|guint8
modifier|*
modifier|*
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
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_procedural_db_get_data"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|identifier
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|bytes
operator|=
literal|0
expr_stmt|;
operator|*
name|data
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
name|GIMP_PDB_SUCCESS
condition|)
block|{
operator|*
name|bytes
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
name|data
operator|=
name|g_new
argument_list|(
name|guint8
argument_list|,
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
operator|*
name|data
argument_list|,
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int8array
argument_list|,
operator|*
name|bytes
operator|*
sizeof|sizeof
argument_list|(
name|guint8
argument_list|)
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
name|gint
DECL|function|gimp_procedural_db_get_data_size (gchar * identifier)
name|gimp_procedural_db_get_data_size
parameter_list|(
name|gchar
modifier|*
name|identifier
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
name|bytes
init|=
literal|0
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
name|GIMP_PDB_STRING
argument_list|,
name|identifier
argument_list|,
name|GIMP_PDB_END
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
name|GIMP_PDB_SUCCESS
condition|)
name|bytes
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
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|bytes
return|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_procedural_db_set_data (gchar * identifier,gint bytes,guint8 * data)
name|_gimp_procedural_db_set_data
parameter_list|(
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|guint8
modifier|*
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
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_procedural_db_set_data"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|identifier
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|bytes
argument_list|,
name|GIMP_PDB_INT8ARRAY
argument_list|,
name|data
argument_list|,
name|GIMP_PDB_END
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

end_unit

