begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpproceduraldb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_comment
comment|/* memcmp */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * gimp_procedural_db_proc_info:  * @procedure: The procedure name.  * @blurb: A short blurb.  * @help: Detailed procedure help.  * @author: Author(s) of the procedure.  * @copyright: The copyright.  * @date: Copyright date.  * @proc_type: The procedure type.  * @num_args: The number of input arguments.  * @num_values: The number of return values.  * @args: The input arguments.  * @return_vals: The return values.  *  * Queries the procedural database for information on the specified  * procedure.  *  * This procedure returns information on the specified procedure. A  * short blurb, detailed help, author(s), copyright information,  * procedure type, number of input, and number of return values are   * returned. Additionally this function returns specific information   * about each input argument and return value.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_procedural_db_proc_info (const gchar * procedure,gchar ** blurb,gchar ** help,gchar ** author,gchar ** copyright,gchar ** date,GimpPDBProcType * proc_type,gint * num_args,gint * num_values,GimpParamDef ** args,GimpParamDef ** return_vals)
name|gimp_procedural_db_proc_info
parameter_list|(
specifier|const
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
parameter_list|,
name|GimpParamDef
modifier|*
modifier|*
name|args
parameter_list|,
name|GimpParamDef
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|success
operator|=
name|_gimp_procedural_db_proc_info
argument_list|(
name|procedure
argument_list|,
name|blurb
argument_list|,
name|help
argument_list|,
name|author
argument_list|,
name|copyright
argument_list|,
name|date
argument_list|,
name|proc_type
argument_list|,
name|num_args
argument_list|,
name|num_values
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
operator|*
name|args
operator|=
name|g_new
argument_list|(
name|GimpParamDef
argument_list|,
operator|*
name|num_args
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
name|num_values
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
name|num_args
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|gimp_procedural_db_proc_arg
argument_list|(
name|procedure
argument_list|,
name|i
argument_list|,
operator|&
operator|(
operator|*
name|args
operator|)
index|[
name|i
index|]
operator|.
name|type
argument_list|,
operator|&
operator|(
operator|*
name|args
operator|)
index|[
name|i
index|]
operator|.
name|name
argument_list|,
operator|&
operator|(
operator|*
name|args
operator|)
index|[
name|i
index|]
operator|.
name|description
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
operator|*
name|args
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
operator|*
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
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
name|num_values
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|gimp_procedural_db_proc_val
argument_list|(
name|procedure
argument_list|,
name|i
argument_list|,
operator|&
operator|(
operator|*
name|return_vals
operator|)
index|[
name|i
index|]
operator|.
name|type
argument_list|,
operator|&
operator|(
operator|*
name|return_vals
operator|)
index|[
name|i
index|]
operator|.
name|name
argument_list|,
operator|&
operator|(
operator|*
name|return_vals
operator|)
index|[
name|i
index|]
operator|.
name|description
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
operator|*
name|args
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
operator|*
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
block|}
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_procedural_db_get_data:  * @identifier: The identifier associated with data.  * @data: A byte array containing data.  *  * Returns data associated with the specified identifier.  *  * This procedure returns any data which may have been associated with  * the specified identifier. The data is copied into the given memory   * location.  *  * Returns: TRUE on success, FALSE if no data has been associated with   * the identifier  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_procedural_db_get_data (const gchar * identifier,gpointer data)
name|gimp_procedural_db_get_data
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gint
name|size
decl_stmt|;
name|guint8
modifier|*
name|hack
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|success
operator|=
name|_gimp_procedural_db_get_data
argument_list|(
name|identifier
argument_list|,
operator|&
name|size
argument_list|,
operator|&
name|hack
argument_list|)
expr_stmt|;
if|if
condition|(
name|hack
condition|)
block|{
name|memcpy
argument_list|(
name|data
argument_list|,
operator|(
name|gpointer
operator|)
name|hack
argument_list|,
name|size
operator|*
sizeof|sizeof
argument_list|(
name|guint8
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|hack
argument_list|)
expr_stmt|;
block|}
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_procedural_db_set_data:  * @identifier: The identifier associated with data.  * @data: A byte array containing data.  * @bytes: The number of bytes in the data  *  * Associates the specified identifier with the supplied data.  *  * This procedure associates the supplied data with the provided  * identifier. The data may be subsequently retrieved by a call to  * 'procedural-db-get-data'.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_procedural_db_set_data (const gchar * identifier,gpointer data,guint32 bytes)
name|gimp_procedural_db_set_data
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint32
name|bytes
parameter_list|)
block|{
return|return
name|_gimp_procedural_db_set_data
argument_list|(
name|identifier
argument_list|,
name|bytes
argument_list|,
name|data
argument_list|)
return|;
block|}
end_function

end_unit

