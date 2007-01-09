begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpproceduraldb_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
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
file|"gimp.h"
end_include

begin_comment
comment|/**  * gimp_procedural_db_temp_name:  *  * Generates a unique temporary PDB name.  *  * This procedure generates a temporary PDB entry name that is  * guaranteed to be unique.  *  * Returns: A unique temporary name for a temporary PDB entry.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_procedural_db_temp_name (void)
name|gimp_procedural_db_temp_name
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|temp_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-procedural-db-temp-name"
argument_list|,
operator|&
name|nreturn_vals
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
name|temp_name
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
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|temp_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_procedural_db_dump:  * @filename: The dump filename.  *  * Dumps the current contents of the procedural database  *  * This procedure dumps the contents of the procedural database to the  * specified file. The file will contain all of the information  * provided for each registered procedure. This file is in a format  * appropriate for use with the supplied \"pdb_self_doc.el\" Elisp  * script, which generates a texinfo document.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_procedural_db_dump (const gchar * filename)
name|gimp_procedural_db_dump
parameter_list|(
specifier|const
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-procedural-db-dump"
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
name|success
operator|=
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
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_procedural_db_query:  * @name: The regex for procedure name.  * @blurb: The regex for procedure blurb.  * @help: The regex for procedure help.  * @author: The regex for procedure author.  * @copyright: The regex for procedure copyright.  * @date: The regex for procedure date.  * @proc_type: The regex for procedure type: { 'Internal GIMP procedure', 'GIMP Plug-In', 'GIMP Extension', 'Temporary Procedure' }.  * @num_matches: The number of matching procedures.  * @procedure_names: The list of procedure names.  *  * Queries the procedural database for its contents using regular  * expression matching.  *  * This procedure queries the contents of the procedural database. It  * is supplied with seven arguments matching procedures on { name,  * blurb, help, author, copyright, date, procedure type}. This is  * accomplished using regular expression matching. For instance, to  * find all procedures with \"jpeg\" listed in the blurb, all seven  * arguments can be supplied as \".*\", except for the second, which  * can be supplied as \".*jpeg.*\". There are two return arguments for  * this procedure. The first is the number of procedures matching the  * query. The second is a concatenated list of procedure names  * corresponding to those matching the query. If no matching entries  * are found, then the returned string is NULL and the number of  * entries is 0.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_procedural_db_query (const gchar * name,const gchar * blurb,const gchar * help,const gchar * author,const gchar * copyright,const gchar * date,const gchar * proc_type,gint * num_matches,gchar *** procedure_names)
name|gimp_procedural_db_query
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|,
specifier|const
name|gchar
modifier|*
name|author
parameter_list|,
specifier|const
name|gchar
modifier|*
name|copyright
parameter_list|,
specifier|const
name|gchar
modifier|*
name|date
parameter_list|,
specifier|const
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-procedural-db-query"
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
name|success
operator|=
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
expr_stmt|;
if|if
condition|(
name|success
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
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_procedural_db_proc_info:  * @procedure_name: The procedure name.  * @blurb: A short blurb.  * @help: Detailed procedure help.  * @author: Author(s) of the procedure.  * @copyright: The copyright.  * @date: Copyright date.  * @proc_type: The procedure type.  * @num_args: The number of input arguments.  * @num_values: The number of return values.  *  * Queries the procedural database for information on the specified  * procedure.  *  * This procedure returns information on the specified procedure. A  * short blurb, detailed help, author(s), copyright information,  * procedure type, number of input, and number of return values are  * returned. For specific information on each input argument and return  * value, use the gimp_procedural_db_proc_arg() and  * gimp_procedural_db_proc_val() procedures.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|_gimp_procedural_db_proc_info (const gchar * procedure_name,gchar ** blurb,gchar ** help,gchar ** author,gchar ** copyright,gchar ** date,GimpPDBProcType * proc_type,gint * num_args,gint * num_values)
name|_gimp_procedural_db_proc_info
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-procedural-db-proc-info"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|procedure_name
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
name|success
operator|=
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
expr_stmt|;
if|if
condition|(
name|success
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
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_procedural_db_proc_arg:  * @procedure_name: The procedure name.  * @arg_num: The argument number.  * @arg_type: The type of argument.  * @arg_name: The name of the argument.  * @arg_desc: A description of the argument.  *  * Queries the procedural database for information on the specified  * procedure's argument.  *  * This procedure returns information on the specified procedure's  * argument. The argument type, name, and a description are retrieved.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_procedural_db_proc_arg (const gchar * procedure_name,gint arg_num,GimpPDBArgType * arg_type,gchar ** arg_name,gchar ** arg_desc)
name|gimp_procedural_db_proc_arg
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-procedural-db-proc-arg"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|procedure_name
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
name|success
operator|=
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
expr_stmt|;
if|if
condition|(
name|success
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
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_procedural_db_proc_val:  * @procedure_name: The procedure name.  * @val_num: The return value number.  * @val_type: The type of return value.  * @val_name: The name of the return value.  * @val_desc: A description of the return value.  *  * Queries the procedural database for information on the specified  * procedure's return value.  *  * This procedure returns information on the specified procedure's  * return value. The return value type, name, and a description are  * retrieved.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_procedural_db_proc_val (const gchar * procedure_name,gint val_num,GimpPDBArgType * val_type,gchar ** val_name,gchar ** val_desc)
name|gimp_procedural_db_proc_val
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-procedural-db-proc-val"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|procedure_name
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
name|success
operator|=
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
expr_stmt|;
if|if
condition|(
name|success
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
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_procedural_db_get_data:  * @identifier: The identifier associated with data.  * @bytes: The number of bytes in the data.  * @data: A byte array containing data.  *  * Returns data associated with the specified identifier.  *  * This procedure returns any data which may have been associated with  * the specified identifier. The data is a variable length array of  * bytes. If no data has been associated with the identifier, an error  * is returned.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|_gimp_procedural_db_get_data (const gchar * identifier,gint * bytes,guint8 ** data)
name|_gimp_procedural_db_get_data
parameter_list|(
specifier|const
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-procedural-db-get-data"
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
name|success
operator|=
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
expr_stmt|;
if|if
condition|(
name|success
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
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_procedural_db_get_data_size:  * @identifier: The identifier associated with data.  *  * Returns size of data associated with the specified identifier.  *  * This procedure returns the size of any data which may have been  * associated with the specified identifier. If no data has been  * associated with the identifier, an error is returned.  *  * Returns: The number of bytes in the data.  */
end_comment

begin_function
name|gint
DECL|function|gimp_procedural_db_get_data_size (const gchar * identifier)
name|gimp_procedural_db_get_data_size
parameter_list|(
specifier|const
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
literal|"gimp-procedural-db-get-data-size"
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

begin_comment
comment|/**  * _gimp_procedural_db_set_data:  * @identifier: The identifier associated with data.  * @bytes: The number of bytes in the data.  * @data: A byte array containing data.  *  * Associates the specified identifier with the supplied data.  *  * This procedure associates the supplied data with the provided  * identifier. The data may be subsequently retrieved by a call to  * 'procedural-db-get-data'.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|_gimp_procedural_db_set_data (const gchar * identifier,gint bytes,const guint8 * data)
name|_gimp_procedural_db_set_data
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gint
name|bytes
parameter_list|,
specifier|const
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-procedural-db-set-data"
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
name|success
operator|=
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
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

