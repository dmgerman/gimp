begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimppdb_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb_pdb.h"
end_include

begin_comment
comment|/**  * _gimp_pdb_temp_name:  *  * Generates a unique temporary PDB name.  *  * This procedure generates a temporary PDB entry name that is  * guaranteed to be unique.  *  * Returns: (transfer full): A unique temporary name for a temporary PDB entry.  *          The returned value must be freed with g_free().  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_pdb_temp_name (void)
name|_gimp_pdb_temp_name
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|temp_name
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-pdb-temp-name"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|temp_name
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|temp_name
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_pdb_dump:  * @filename: The dump filename.  *  * Dumps the current contents of the procedural database  *  * This procedure dumps the contents of the procedural database to the  * specified file. The file will contain all of the information  * provided for each registered procedure.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_pdb_dump (const gchar * filename)
name|_gimp_pdb_dump
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|filename
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-pdb-dump"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_pdb_query:  * @name: The regex for procedure name.  * @blurb: The regex for procedure blurb.  * @help: The regex for procedure help.  * @authors: The regex for procedure authors.  * @copyright: The regex for procedure copyright.  * @date: The regex for procedure date.  * @proc_type: The regex for procedure type: { 'Internal GIMP procedure', 'GIMP Plug-in', 'GIMP Extension', 'Temporary Procedure' }.  * @num_matches: (out): The number of matching procedures.  * @procedure_names: (out) (array length=num_matches) (element-type gchar*) (transfer full): The list of procedure names.  *  * Queries the procedural database for its contents using regular  * expression matching.  *  * This procedure queries the contents of the procedural database. It  * is supplied with seven arguments matching procedures on { name,  * blurb, help, authors, copyright, date, procedure type}. This is  * accomplished using regular expression matching. For instance, to  * find all procedures with \"jpeg\" listed in the blurb, all seven  * arguments can be supplied as \".*\", except for the second, which  * can be supplied as \".*jpeg.*\". There are two return arguments for  * this procedure. The first is the number of procedures matching the  * query. The second is a concatenated list of procedure names  * corresponding to those matching the query. If no matching entries  * are found, then the returned string is NULL and the number of  * entries is 0.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_pdb_query (const gchar * name,const gchar * blurb,const gchar * help,const gchar * authors,const gchar * copyright,const gchar * date,const gchar * proc_type,gint * num_matches,gchar *** procedure_names)
name|_gimp_pdb_query
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
name|authors
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
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|name
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|blurb
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|help
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|authors
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|copyright
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|date
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|proc_type
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-pdb-query"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
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
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|procedure_names
operator|=
name|gimp_value_dup_string_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_pdb_proc_exists:  * @procedure_name: The procedure name.  *  * Checks if the specified procedure exists in the procedural database  *  * This procedure checks if the specified procedure is registered in  * the procedural database.  *  * Returns: Whether a procedure of that name is registered.  *  * Since: 2.6  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_pdb_proc_exists (const gchar * procedure_name)
name|_gimp_pdb_proc_exists
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|exists
init|=
name|FALSE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|procedure_name
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-pdb-proc-exists"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|exists
operator|=
name|g_value_get_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|exists
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_pdb_proc_info:  * @procedure_name: The procedure name.  * @proc_type: (out): The procedure type.  * @num_args: (out): The number of input arguments.  * @num_values: (out): The number of return values.  *  * Queries the procedural database for information on the specified  * procedure.  *  * This procedure returns information on the specified procedure. The  * procedure type, number of input, and number of return values are  * returned. For specific information on each input argument and return  * value, use the gimp_pdb_db_proc_argument() and  * gimp_pdb_db_proc_return_value() procedures.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_pdb_proc_info (const gchar * procedure_name,GimpPDBProcType * proc_type,gint * num_args,gint * num_values)
name|_gimp_pdb_proc_info
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
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
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|procedure_name
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-pdb-proc-info"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
operator|*
name|proc_type
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|num_args
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|num_values
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_pdb_proc_documentation:  * @procedure_name: The procedure name.  * @blurb: (out) (transfer full): A short blurb.  * @help: (out) (transfer full): Detailed procedure help.  * @help_id: (out) (transfer full): The procedure help_id.  *  * Queries the procedural database for documentation on the specified  * procedure.  *  * This procedure returns documentation on the specified procedure. A  * short blurb, detailed help and help_id.  *  * Returns: TRUE on success.  *  * Since: 3.0  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_pdb_proc_documentation (const gchar * procedure_name,gchar ** blurb,gchar ** help,gchar ** help_id)
name|_gimp_pdb_proc_documentation
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
name|help_id
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|procedure_name
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-pdb-proc-documentation"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
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
name|help_id
operator|=
name|NULL
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
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
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|help
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|help_id
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_pdb_proc_attribution:  * @procedure_name: The procedure name.  * @authors: (out) (transfer full): Authors of the procedure.  * @copyright: (out) (transfer full): The copyright.  * @date: (out) (transfer full): Copyright date.  *  * Queries the procedural database for attribution information on the  * specified procedure.  *  * This procedure returns attribution information on the specified  * procedure. The authors, copyright information and date are returned.  *  * Returns: TRUE on success.  *  * Since: 3.0  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_pdb_proc_attribution (const gchar * procedure_name,gchar ** authors,gchar ** copyright,gchar ** date)
name|_gimp_pdb_proc_attribution
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|authors
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
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|procedure_name
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-pdb-proc-attribution"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
operator|*
name|authors
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
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
operator|*
name|authors
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|copyright
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|date
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_pdb_proc_argument:  * @procedure_name: The procedure name.  * @arg_num: The argument number.  *  * Queries the procedural database for information on the specified  * procedure's argument.  *  * This procedure returns the #GParamSpec of procedure_name's argument.  *  * Returns: (transfer full): The GParamSpec of the argument.  *          The returned value must be freed with g_param_spec_unref().  *  * Since: 3.0  **/
end_comment

begin_function
name|GParamSpec
modifier|*
DECL|function|_gimp_pdb_proc_argument (const gchar * procedure_name,gint arg_num)
name|_gimp_pdb_proc_argument
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|gint
name|arg_num
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GParamSpec
modifier|*
name|param_spec
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|procedure_name
argument_list|,
name|G_TYPE_INT
argument_list|,
name|arg_num
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-pdb-proc-argument"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|param_spec
operator|=
name|g_value_dup_param
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|param_spec
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_pdb_proc_return_value:  * @procedure_name: The procedure name.  * @val_num: The return value number.  *  * Queries the procedural database for information on the specified  * procedure's return value.  *  * This procedure returns the #GParamSpec of procedure_name's return  * value.  *  * Returns: (transfer full): The GParamSpec of the return value.  *          The returned value must be freed with g_param_spec_unref().  *  * Since: 3.0  **/
end_comment

begin_function
name|GParamSpec
modifier|*
DECL|function|_gimp_pdb_proc_return_value (const gchar * procedure_name,gint val_num)
name|_gimp_pdb_proc_return_value
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|gint
name|val_num
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GParamSpec
modifier|*
name|param_spec
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|procedure_name
argument_list|,
name|G_TYPE_INT
argument_list|,
name|val_num
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-pdb-proc-return-value"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|param_spec
operator|=
name|g_value_dup_param
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|param_spec
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_pdb_get_data:  * @identifier: The identifier associated with data.  * @bytes: (out): The number of bytes in the data.  * @data: (out) (array length=bytes) (element-type guint8) (transfer full): A byte array containing data.  *  * Returns data associated with the specified identifier.  *  * This procedure returns any data which may have been associated with  * the specified identifier. The data is a variable length array of  * bytes. If no data has been associated with the identifier, an error  * is returned.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_pdb_get_data (const gchar * identifier,gint * bytes,guint8 ** data)
name|_gimp_pdb_get_data
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
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|identifier
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-pdb-get-data"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
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
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|data
operator|=
name|gimp_value_dup_uint8_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_pdb_get_data_size:  * @identifier: The identifier associated with data.  *  * Returns size of data associated with the specified identifier.  *  * This procedure returns the size of any data which may have been  * associated with the specified identifier. If no data has been  * associated with the identifier, an error is returned.  *  * Returns: The number of bytes in the data.  **/
end_comment

begin_function
name|gint
DECL|function|_gimp_pdb_get_data_size (const gchar * identifier)
name|_gimp_pdb_get_data_size
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|bytes
init|=
literal|0
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|identifier
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-pdb-get-data-size"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|bytes
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|bytes
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_pdb_set_data:  * @identifier: The identifier associated with data.  * @bytes: The number of bytes in the data.  * @data: (array length=bytes) (element-type guint8): A byte array containing data.  *  * Associates the specified identifier with the supplied data.  *  * This procedure associates the supplied data with the provided  * identifier. The data may be subsequently retrieved by a call to  * 'procedural-db-get-data'.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_pdb_set_data (const gchar * identifier,gint bytes,const guint8 * data)
name|_gimp_pdb_set_data
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
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|identifier
argument_list|,
name|G_TYPE_INT
argument_list|,
name|bytes
argument_list|,
name|GIMP_TYPE_UINT8_ARRAY
argument_list|,
name|NULL
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_uint8_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|data
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-pdb-set-data"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

