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
file|"gimp.h"
end_include

begin_comment
comment|/**  * gimp_gradients_popup:  * @gradients_callback: The callback PDB proc to call when gradient selection is made.  * @popup_title: Title to give the gradient popup window.  * @initial_gradient: The name of the pattern to set as the first selected.  * @sample_size: Size of the sample to return when the gradient is changed.  *  * Invokes the Gimp gradients selection.  *  * This procedure popups the gradients selection dialog.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_gradients_popup (gchar * gradients_callback,gchar * popup_title,gchar * initial_gradient,gint sample_size)
name|gimp_gradients_popup
parameter_list|(
name|gchar
modifier|*
name|gradients_callback
parameter_list|,
name|gchar
modifier|*
name|popup_title
parameter_list|,
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
name|gradients_callback
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
comment|/**  * gimp_gradients_close_popup:  * @gradients_callback: The name of the callback registered for this popup.  *  * Popdown the Gimp gradient selection.  *  * This procedure closes an opened gradient selection dialog.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_gradients_close_popup (gchar * gradients_callback)
name|gimp_gradients_close_popup
parameter_list|(
name|gchar
modifier|*
name|gradients_callback
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
name|gradients_callback
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
comment|/**  * gimp_gradients_set_popup:  * @gradients_callback: The name of the callback registered for this popup.  * @gradient_name: The name of the gradient to set as selected.  *  * Sets the current gradient selection in a popup.  *  * Sets the current gradient selection in a popup.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_gradients_set_popup (gchar * gradients_callback,gchar * gradient_name)
name|gimp_gradients_set_popup
parameter_list|(
name|gchar
modifier|*
name|gradients_callback
parameter_list|,
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
name|gradients_callback
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

begin_comment
comment|/**  * _gimp_gradients_get_gradient_data:  * @name: The gradient name (\"\" means current active gradient).  * @sample_size: Size of the sample to return when the gradient is changed.  * @width: The gradient sample width (r,g,b,a).  * @grad_data: The gradient sample data.  *  * Retrieve information about the specified gradient (including data).  *  * This procedure retrieves information about the gradient. This  * includes the gradient name, and the sample data for the gradient.  *  * Returns: The gradient name.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_gradients_get_gradient_data (gchar * name,gint sample_size,gint * width,gdouble ** grad_data)
name|_gimp_gradients_get_gradient_data
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|sample_size
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gdouble
modifier|*
modifier|*
name|grad_data
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
name|ret_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_gradients_get_gradient_data"
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
name|sample_size
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|width
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
name|ret_name
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
name|grad_data
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
operator|*
name|width
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
operator|*
name|grad_data
argument_list|,
name|return_vals
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_floatarray
argument_list|,
operator|*
name|width
operator|*
sizeof|sizeof
argument_list|(
name|gdouble
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
name|ret_name
return|;
block|}
end_function

end_unit

