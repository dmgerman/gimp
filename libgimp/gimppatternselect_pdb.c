begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimppatternselect_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
comment|/**  * gimp_patterns_popup:  * @pattern_callback: The callback PDB proc to call when pattern selection is made.  * @popup_title: Title of the pattern selection dialog.  * @initial_pattern: The name of the pattern to set as the first selected.  *  * Invokes the Gimp pattern selection.  *  * This procedure opens the pattern selection dialog.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_patterns_popup (const gchar * pattern_callback,const gchar * popup_title,const gchar * initial_pattern)
name|gimp_patterns_popup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|pattern_callback
parameter_list|,
specifier|const
name|gchar
modifier|*
name|popup_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|initial_pattern
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
literal|"gimp-patterns-popup"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|pattern_callback
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|popup_title
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|initial_pattern
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
comment|/**  * gimp_patterns_close_popup:  * @pattern_callback: The name of the callback registered for this pop-up.  *  * Close the pattern selection dialog.  *  * This procedure closes an opened pattern selection dialog.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_patterns_close_popup (const gchar * pattern_callback)
name|gimp_patterns_close_popup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|pattern_callback
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
literal|"gimp-patterns-close-popup"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|pattern_callback
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
comment|/**  * gimp_patterns_set_popup:  * @pattern_callback: The name of the callback registered for this pop-up.  * @pattern_name: The name of the pattern to set as selected.  *  * Sets the current pattern in a pattern selection dialog.  *  * Sets the current pattern in a pattern selection dialog.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_patterns_set_popup (const gchar * pattern_callback,const gchar * pattern_name)
name|gimp_patterns_set_popup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|pattern_callback
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pattern_name
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
literal|"gimp-patterns-set-popup"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|pattern_callback
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|pattern_name
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

