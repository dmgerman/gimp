begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpfonts_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimpfonts  * @title: gimpfonts  * @short_description: Operations related to fonts.  *  * Operations related to fonts.  **/
end_comment

begin_comment
comment|/**  * gimp_fonts_refresh:  *  * Refresh current fonts. This function always succeeds.  *  * This procedure retrieves all fonts currently in the user's font path  * and updates the font dialogs accordingly. Depending on the amount of  * fonts on the system, this can take considerable time.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_fonts_refresh (void)
name|gimp_fonts_refresh
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-fonts-refresh"
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
comment|/**  * gimp_fonts_get_list:  * @filter: An optional regular expression used to filter the list.  * @num_fonts: The number of available fonts.  *  * Retrieve the list of loaded fonts.  *  * This procedure returns a list of the fonts that are currently  * available.  *  * Returns: (transfer full) The list of font names. The returned value  * must be freed with g_strfreev().  **/
end_comment

begin_function
name|gchar
modifier|*
modifier|*
DECL|function|gimp_fonts_get_list (const gchar * filter,gint * num_fonts)
name|gimp_fonts_get_list
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filter
parameter_list|,
name|gint
modifier|*
name|num_fonts
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
modifier|*
name|font_list
init|=
name|NULL
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
name|filter
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-fonts-get-list"
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
name|num_fonts
operator|=
literal|0
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
block|{
operator|*
name|num_fonts
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
name|font_list
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
name|font_list
return|;
block|}
end_function

end_unit

