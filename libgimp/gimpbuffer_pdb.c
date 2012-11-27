begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpbuffer_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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

begin_comment
comment|/**  * SECTION: gimpbuffer  * @title: gimpbuffer  * @short_description: Functions for manipulating cut buffers.  *  * Functions related to named cut buffers.  **/
end_comment

begin_comment
comment|/**  * gimp_buffers_get_list:  * @filter: An optional regular expression used to filter the list.  * @num_buffers: The number of buffers.  *  * Retrieve a complete listing of the available buffers.  *  * This procedure returns a complete listing of available named  * buffers.  *  * Returns: The list of buffer names.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gchar
modifier|*
modifier|*
DECL|function|gimp_buffers_get_list (const gchar * filter,gint * num_buffers)
name|gimp_buffers_get_list
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filter
parameter_list|,
name|gint
modifier|*
name|num_buffers
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
modifier|*
name|buffer_list
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-buffers-get-list"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|filter
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|num_buffers
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
name|num_buffers
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
name|buffer_list
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
operator|*
name|num_buffers
operator|+
literal|1
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
name|num_buffers
condition|;
name|i
operator|++
control|)
name|buffer_list
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
name|buffer_list
index|[
name|i
index|]
operator|=
name|NULL
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
name|buffer_list
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_buffer_rename:  * @buffer_name: The buffer name.  * @new_name: The buffer's new name.  *  * Renames a named buffer.  *  * This procedure renames a named buffer.  *  * Returns: The real name given to the buffer.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_buffer_rename (const gchar * buffer_name,const gchar * new_name)
name|gimp_buffer_rename
parameter_list|(
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
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
name|real_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-buffer-rename"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|buffer_name
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|new_name
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
name|real_name
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
name|real_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_buffer_delete:  * @buffer_name: The buffer name.  *  * Deletes a named buffer.  *  * This procedure deletes a named buffer.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_buffer_delete (const gchar * buffer_name)
name|gimp_buffer_delete
parameter_list|(
specifier|const
name|gchar
modifier|*
name|buffer_name
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
literal|"gimp-buffer-delete"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|buffer_name
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
comment|/**  * gimp_buffer_get_width:  * @buffer_name: The buffer name.  *  * Retrieves the specified buffer's width.  *  * This procedure retrieves the specified named buffer's width.  *  * Returns: The buffer width.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gint
DECL|function|gimp_buffer_get_width (const gchar * buffer_name)
name|gimp_buffer_get_width
parameter_list|(
specifier|const
name|gchar
modifier|*
name|buffer_name
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
name|width
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-buffer-get-width"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|buffer_name
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
name|width
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
name|width
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_buffer_get_height:  * @buffer_name: The buffer name.  *  * Retrieves the specified buffer's height.  *  * This procedure retrieves the specified named buffer's height.  *  * Returns: The buffer height.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gint
DECL|function|gimp_buffer_get_height (const gchar * buffer_name)
name|gimp_buffer_get_height
parameter_list|(
specifier|const
name|gchar
modifier|*
name|buffer_name
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
name|height
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-buffer-get-height"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|buffer_name
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
name|height
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
name|height
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_buffer_get_bytes:  * @buffer_name: The buffer name.  *  * Retrieves the specified buffer's bytes.  *  * This procedure retrieves the specified named buffer's bytes.  *  * Returns: The buffer bpp.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gint
DECL|function|gimp_buffer_get_bytes (const gchar * buffer_name)
name|gimp_buffer_get_bytes
parameter_list|(
specifier|const
name|gchar
modifier|*
name|buffer_name
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
literal|"gimp-buffer-get-bytes"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|buffer_name
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
comment|/**  * gimp_buffer_get_image_type:  * @buffer_name: The buffer name.  *  * Retrieves the specified buffer's image type.  *  * This procedure retrieves the specified named buffer's image type.  *  * Returns: The buffer image type.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|GimpImageBaseType
DECL|function|gimp_buffer_get_image_type (const gchar * buffer_name)
name|gimp_buffer_get_image_type
parameter_list|(
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|GimpImageBaseType
name|image_type
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-buffer-get-image-type"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|buffer_name
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
name|image_type
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
name|image_type
return|;
block|}
end_function

end_unit

