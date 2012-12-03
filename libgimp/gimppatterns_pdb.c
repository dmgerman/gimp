begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimppatterns_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimppatterns  * @title: gimppatterns  * @short_description: Functions relating to patterns.  *  * Functions relating to patterns.  **/
end_comment

begin_comment
comment|/**  * gimp_patterns_refresh:  *  * Refresh current patterns. This function always succeeds.  *  * This procedure retrieves all patterns currently in the user's  * pattern path and updates all pattern dialogs accordingly.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_patterns_refresh (void)
name|gimp_patterns_refresh
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-patterns-refresh"
argument_list|,
operator|&
name|nreturn_vals
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
comment|/**  * gimp_patterns_get_list:  * @filter: An optional regular expression used to filter the list.  * @num_patterns: The number of patterns in the pattern list.  *  * Retrieve a complete listing of the available patterns.  *  * This procedure returns a complete listing of available GIMP  * patterns. Each name returned can be used as input to the  * gimp_context_set_pattern().  *  * Returns: The list of pattern names. The returned value must be freed with g_strfreev().  **/
end_comment

begin_function
name|gchar
modifier|*
modifier|*
DECL|function|gimp_patterns_get_list (const gchar * filter,gint * num_patterns)
name|gimp_patterns_get_list
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filter
parameter_list|,
name|gint
modifier|*
name|num_patterns
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
name|pattern_list
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
literal|"gimp-patterns-get-list"
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
name|num_patterns
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
name|num_patterns
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
name|pattern_list
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
operator|*
name|num_patterns
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
name|num_patterns
condition|;
name|i
operator|++
control|)
name|pattern_list
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
name|pattern_list
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
name|pattern_list
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_patterns_get_pattern:  * @width: The pattern width.  * @height: The pattern height.  *  * Deprecated: Use gimp_context_get_pattern() instead.  *  * Returns: The pattern name.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_patterns_get_pattern (gint * width,gint * height)
name|gimp_patterns_get_pattern
parameter_list|(
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
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
name|name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-patterns-get-pattern"
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
block|{
name|name
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
name|width
operator|=
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|height
operator|=
name|return_vals
index|[
literal|3
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
name|name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_patterns_get_pattern_data:  * @name: The pattern name (\"\" means currently active pattern).  * @width: The pattern width.  * @height: The pattern height.  * @mask_bpp: Pattern bytes per pixel.  * @length: Length of pattern mask data.  * @mask_data: The pattern mask data.  *  * Deprecated: Use gimp_pattern_get_pixels() instead.  *  * Returns: The pattern name.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_patterns_get_pattern_data (const gchar * name,gint * width,gint * height,gint * mask_bpp,gint * length,guint8 ** mask_data)
name|gimp_patterns_get_pattern_data
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|mask_bpp
parameter_list|,
name|gint
modifier|*
name|length
parameter_list|,
name|guint8
modifier|*
modifier|*
name|mask_data
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
literal|"gimp-patterns-get-pattern-data"
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
name|length
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
operator|*
name|width
operator|=
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|height
operator|=
name|return_vals
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|mask_bpp
operator|=
name|return_vals
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|length
operator|=
name|return_vals
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|mask_data
operator|=
name|g_new
argument_list|(
name|guint8
argument_list|,
operator|*
name|length
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
operator|*
name|mask_data
argument_list|,
name|return_vals
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int8array
argument_list|,
operator|*
name|length
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
name|actual_name
return|;
block|}
end_function

end_unit

