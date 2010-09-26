begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimppattern_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimppattern  * @title: gimppattern  * @short_description: Functions operating on a single pattern.  *  * Functions operating on a single pattern.  **/
end_comment

begin_comment
comment|/**  * gimp_pattern_get_info:  * @name: The pattern name.  * @width: The pattern width.  * @height: The pattern height.  * @bpp: The pattern bpp.  *  * Retrieve information about the specified pattern.  *  * This procedure retrieves information about the specified pattern.  * This includes the pattern extents (width and height).  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_pattern_get_info (const gchar * name,gint * width,gint * height,gint * bpp)
name|gimp_pattern_get_info
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
name|bpp
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
literal|"gimp-pattern-get-info"
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
name|width
operator|=
literal|0
expr_stmt|;
operator|*
name|height
operator|=
literal|0
expr_stmt|;
operator|*
name|bpp
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
operator|*
name|height
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
name|bpp
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
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pattern_get_pixels:  * @name: The pattern name.  * @width: The pattern width.  * @height: The pattern height.  * @bpp: The pattern bpp.  * @num_color_bytes: Number of pattern bytes.  * @color_bytes: The pattern data.  *  * Retrieve information about the specified pattern (including pixels).  *  * This procedure retrieves information about the specified. This  * includes the pattern extents (width and height), its bpp and its  * pixel data.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_pattern_get_pixels (const gchar * name,gint * width,gint * height,gint * bpp,gint * num_color_bytes,guint8 ** color_bytes)
name|gimp_pattern_get_pixels
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
name|bpp
parameter_list|,
name|gint
modifier|*
name|num_color_bytes
parameter_list|,
name|guint8
modifier|*
modifier|*
name|color_bytes
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
literal|"gimp-pattern-get-pixels"
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
name|width
operator|=
literal|0
expr_stmt|;
operator|*
name|height
operator|=
literal|0
expr_stmt|;
operator|*
name|bpp
operator|=
literal|0
expr_stmt|;
operator|*
name|num_color_bytes
operator|=
literal|0
expr_stmt|;
operator|*
name|color_bytes
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
operator|*
name|height
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
name|bpp
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
name|num_color_bytes
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
name|color_bytes
operator|=
name|g_new
argument_list|(
name|guint8
argument_list|,
operator|*
name|num_color_bytes
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
operator|*
name|color_bytes
argument_list|,
name|return_vals
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int8array
argument_list|,
operator|*
name|num_color_bytes
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

end_unit

