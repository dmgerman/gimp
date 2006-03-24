begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimppalette_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
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
comment|/**  * gimp_palette_new:  * @name: The requested name of the new palette.  *  * Creates a new palette  *  * This procedure creates a new, uninitialized palette  *  * Returns: The actual new palette name.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_palette_new (const gchar * name)
name|gimp_palette_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
name|actual_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-palette-new"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|actual_name
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
name|actual_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_palette_duplicate:  * @name: The palette name.  *  * Duplicates a palette  *  * This procedure creates an identical palette by a different name  *  * Returns: The name of the palette's copy.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_palette_duplicate (const gchar * name)
name|gimp_palette_duplicate
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
name|copy_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-palette-duplicate"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|copy_name
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
name|copy_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_palette_rename:  * @name: The palette name.  * @new_name: The new name of the palette.  *  * Rename a palette  *  * This procedure renames a palette  *  * Returns: The actual new name of the palette.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_palette_rename (const gchar * name,const gchar * new_name)
name|gimp_palette_rename
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
name|actual_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-palette-rename"
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
name|actual_name
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
name|actual_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_palette_delete:  * @name: The palette name.  *  * Deletes a palette  *  * This procedure deletes a palette  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_palette_delete (const gchar * name)
name|gimp_palette_delete
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
literal|"gimp-palette-delete"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
comment|/**  * gimp_palette_is_editable:  * @name: The palette name.  *  * Tests if palette can be edited  *  * Returns TRUE if you have permission to change the palette  *  * Returns: TRUE if the palette can be edited.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_palette_is_editable (const gchar * name)
name|gimp_palette_is_editable
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
name|editable
init|=
name|FALSE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-palette-is-editable"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|editable
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
name|editable
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_palette_get_info:  * @name: The palette name.  * @num_colors: The number of colors in the palette.  *  * Retrieve information about the specified palette.  *  * This procedure retrieves information about the specified palette.  * This includes the name, and the number of colors.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_palette_get_info (const gchar * name,gint * num_colors)
name|gimp_palette_get_info
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
modifier|*
name|num_colors
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
literal|"gimp-palette-get-info"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|num_colors
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
operator|*
name|num_colors
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
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_palette_get_columns:  * @name: The palette name.  *  * Retrieves the number of columns to use to display this palette  *  * This procedures retrieves the prefered number of columns to use when  * the palette is being displayed.  *  * Returns: The number of columns used to display this palette.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gint
DECL|function|gimp_palette_get_columns (const gchar * name)
name|gimp_palette_get_columns
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
name|num_columns
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-palette-get-columns"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|num_columns
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
name|num_columns
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_palette_set_columns:  * @name: The palette name.  * @columns: The new number of columns.  *  * Sets the number of columns to use when displaying the palette  *  * This procedures allows to control how many colors are shown per row  * when the palette is being displayed. This value can only be changed  * if the palette is writable. The maximum allowed value is 64.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_palette_set_columns (const gchar * name,gint columns)
name|gimp_palette_set_columns
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|columns
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
literal|"gimp-palette-set-columns"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|columns
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
comment|/**  * gimp_palette_add_entry:  * @name: The palette name.  * @entry_name: The name of the entry.  * @color: The new entry's color color.  * @entry_num: The index of the added entry.  *  * Adds a palette entry to the specified palette.  *  * This procedure adds an entry to the specifed palette. It returns an  * error if the entry palette does not exist.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_palette_add_entry (const gchar * name,const gchar * entry_name,const GimpRGB * color,gint * entry_num)
name|gimp_palette_add_entry
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|entry_name
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
modifier|*
name|entry_num
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
literal|"gimp-palette-add-entry"
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
name|entry_name
argument_list|,
name|GIMP_PDB_COLOR
argument_list|,
name|color
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|entry_num
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
operator|*
name|entry_num
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
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_palette_delete_entry:  * @name: The palette name.  * @entry_num: The index of the added entry.  *  * Deletes a palette entry from the specified palette.  *  * This procedure deletes an entry from the specifed palette. It  * returns an error if the entry palette does not exist.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_palette_delete_entry (const gchar * name,gint entry_num)
name|gimp_palette_delete_entry
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|entry_num
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
literal|"gimp-palette-delete-entry"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|entry_num
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
comment|/**  * gimp_palette_entry_get_color:  * @name: The palette name.  * @entry_num: The entry to retrieve.  * @color: The color requested.  *  * Gets the specified palette entry from the specified palette.  *  * This procedure retrieves the color of the zero-based entry specifed  * for the specified palette. It returns an error if the entry does not  * exist.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_palette_entry_get_color (const gchar * name,gint entry_num,GimpRGB * color)
name|gimp_palette_entry_get_color
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|entry_num
parameter_list|,
name|GimpRGB
modifier|*
name|color
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
literal|"gimp-palette-entry-get-color"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|entry_num
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
if|if
condition|(
name|success
condition|)
operator|*
name|color
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_color
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
comment|/**  * gimp_palette_entry_set_color:  * @name: The palette name.  * @entry_num: The entry to retrieve.  * @color: The new color.  *  * Sets the specified palette entry in the specified palette.  *  * This procedure sets the color of the zero-based entry specifed for  * the specified palette. It returns an error if the entry does not  * exist.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_palette_entry_set_color (const gchar * name,gint entry_num,const GimpRGB * color)
name|gimp_palette_entry_set_color
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|entry_num
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
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
literal|"gimp-palette-entry-set-color"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|entry_num
argument_list|,
name|GIMP_PDB_COLOR
argument_list|,
name|color
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
comment|/**  * gimp_palette_entry_get_name:  * @name: The palette name.  * @entry_num: The entry to retrieve.  * @entry_name: The name requested.  *  * Gets the specified palette entry from the specified palette.  *  * This procedure retrieves the name of the zero-based entry specifed  * for the specified palette. It returns an error if the entry does not  * exist.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_palette_entry_get_name (const gchar * name,gint entry_num,gchar ** entry_name)
name|gimp_palette_entry_get_name
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|entry_num
parameter_list|,
name|gchar
modifier|*
modifier|*
name|entry_name
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
literal|"gimp-palette-entry-get-name"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|entry_num
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|entry_name
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
operator|*
name|entry_name
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
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_palette_entry_set_name:  * @name: The palette name.  * @entry_num: The entry to retrieve.  * @entry_name: The new name.  *  * Sets the specified palette entry in the specified palette.  *  * This procedure sets the name of the zero-based entry specifed for  * the specified palette. It returns an error if the entry does not  * exist.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_palette_entry_set_name (const gchar * name,gint entry_num,const gchar * entry_name)
name|gimp_palette_entry_set_name
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|entry_num
parameter_list|,
specifier|const
name|gchar
modifier|*
name|entry_name
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
literal|"gimp-palette-entry-set-name"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|entry_num
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|entry_name
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

