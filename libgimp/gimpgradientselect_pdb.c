begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpgradientselect_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
comment|/**  * gimp_gradients_popup:  * @gradient_callback: The callback PDB proc to call when gradient selection is made.  * @popup_title: Title to give the gradient popup window.  * @initial_gradient: The name of the pattern to set as the first selected.  * @sample_size: Size of the sample to return when the gradient is changed.  *  * Invokes the Gimp gradients selection.  *  * This procedure popups the gradients selection dialog.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_gradients_popup (const gchar * gradient_callback,const gchar * popup_title,const gchar * initial_gradient,gint sample_size)
name|gimp_gradients_popup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|gradient_callback
parameter_list|,
specifier|const
name|gchar
modifier|*
name|popup_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|initial_gradient
parameter_list|,
name|gint
name|sample_size
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
literal|"gimp_gradients_popup"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gradient_callback
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|popup_title
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|initial_gradient
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|sample_size
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
comment|/**  * gimp_gradients_close_popup:  * @gradient_callback: The name of the callback registered for this popup.  *  * Popdown the Gimp gradient selection.  *  * This procedure closes an opened gradient selection dialog.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_gradients_close_popup (const gchar * gradient_callback)
name|gimp_gradients_close_popup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|gradient_callback
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
literal|"gimp_gradients_close_popup"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gradient_callback
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
comment|/**  * gimp_gradients_set_popup:  * @gradient_callback: The name of the callback registered for this popup.  * @gradient_name: The name of the gradient to set as selected.  *  * Sets the current gradient selection in a popup.  *  * Sets the current gradient selection in a popup.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_gradients_set_popup (const gchar * gradient_callback,const gchar * gradient_name)
name|gimp_gradients_set_popup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|gradient_callback
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
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
literal|"gimp_gradients_set_popup"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gradient_callback
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gradient_name
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

