begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimppattern_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimppattern  * @title: gimppattern  * @short_description: Functions operating on a single pattern.  *  * Functions operating on a single pattern.  **/
end_comment

begin_comment
comment|/**  * gimp_pattern_get_info:  * @name: The pattern name.  * @width: (out): The pattern width.  * @height: (out): The pattern height.  * @bpp: (out): The pattern bpp.  *  * Retrieve information about the specified pattern.  *  * This procedure retrieves information about the specified pattern.  * This includes the pattern extents (width and height).  *  * Returns: TRUE on success.  *  * Since: 2.2  **/
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
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-pattern-get-info"
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
name|width
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
name|height
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
name|bpp
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
comment|/**  * gimp_pattern_get_pixels:  * @name: The pattern name.  * @width: (out): The pattern width.  * @height: (out): The pattern height.  * @bpp: (out): The pattern bpp.  * @num_color_bytes: (out): Number of pattern bytes.  * @color_bytes: (out) (array length=num_color_bytes) (element-type guint8) (transfer full): The pattern data.  *  * Retrieve information about the specified pattern (including pixels).  *  * This procedure retrieves information about the specified. This  * includes the pattern extents (width and height), its bpp and its  * pixel data.  *  * Returns: TRUE on success.  *  * Since: 2.2  **/
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
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-pattern-get-pixels"
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
name|width
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
name|height
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
name|bpp
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
operator|*
name|num_color_bytes
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|4
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|color_bytes
operator|=
name|gimp_value_dup_int8_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|5
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

end_unit

