begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpgradients_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
end_comment

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
comment|/**  * gimp_gradients_get_list:  * @num_gradients: The number of loaded gradients.  *  * Retrieve the list of loaded gradients.  *  * This procedure returns a list of the gradients that are currently  * loaded in the gradient editor. You can later use the  * gimp_gradients_set_active function to set the active gradient.  *  * Returns: The list of gradient names.  */
end_comment

begin_function
name|gchar
modifier|*
modifier|*
DECL|function|gimp_gradients_get_list (gint * num_gradients)
name|gimp_gradients_get_list
parameter_list|(
name|gint
modifier|*
name|num_gradients
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
name|gradient_names
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
literal|"gimp_gradients_get_list"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|num_gradients
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
name|num_gradients
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
name|gradient_names
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
operator|*
name|num_gradients
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
name|num_gradients
condition|;
name|i
operator|++
control|)
name|gradient_names
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
block|}
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|gradient_names
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_gradients_get_active:  *  * Retrieve the name of the active gradient.  *  * This procedure returns the name of the active gradient in the  * gradient editor.  *  * Returns: The name of the active gradient.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_gradients_get_active (void)
name|gimp_gradients_get_active
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
literal|"gimp_gradients_get_active"
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
comment|/**  * gimp_gradients_set_active:  * @name: The name of the gradient to set.  *  * Sets the specified gradient as the active gradient.  *  * This procedure lets you set the specified gradient as the active or  * \"current\" one. The name is simply a string which corresponds to  * one of the loaded gradients in the gradient editor. If no matching  * gradient is found, this procedure will return an error. Otherwise,  * the specified gradient will become active and will be used for  * subsequent custom gradient operations.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_gradients_set_active (gchar * name)
name|gimp_gradients_set_active
parameter_list|(
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
literal|"gimp_gradients_set_active"
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
comment|/**  * gimp_gradients_sample_uniform:  * @num_samples: The number of samples to take.  *  * Sample the active gradient in uniform parts.  *  * This procedure samples the active gradient from the gradient editor  * in the specified number of uniform parts. It returns a list of  * floating-point values which correspond to the RGBA values for each  * sample. The minimum number of samples to take is 2, in which case  * the returned colors will correspond to the { 0.0, 1.0 } positions in  * the gradient. For example, if the number of samples is 3, the  * procedure will return the colors at positions { 0.0, 0.5, 1.0 }.  *  * Returns: Color samples: { R1, G1, B1, A1, ..., Rn, Gn, Bn, An }.  */
end_comment

begin_function
name|gdouble
modifier|*
DECL|function|gimp_gradients_sample_uniform (gint num_samples)
name|gimp_gradients_sample_uniform
parameter_list|(
name|gint
name|num_samples
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gdouble
modifier|*
name|color_samples
init|=
name|NULL
decl_stmt|;
name|gint
name|num_color_samples
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_gradients_sample_uniform"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|num_samples
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
name|num_color_samples
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
name|color_samples
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|num_color_samples
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|color_samples
argument_list|,
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_floatarray
argument_list|,
name|num_color_samples
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
name|color_samples
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_gradients_sample_custom:  * @num_samples: The number of samples to take.  * @positions: The list of positions to sample along the gradient.  *  * Sample the active gradient in custom positions.  *  * This procedure samples the active gradient from the gradient editor  * in the specified number of points. The procedure will sample the  * gradient in the specified positions from the list. The left endpoint  * of the gradient corresponds to position 0.0, and the right endpoint  * corresponds to 1.0. The procedure returns a list of floating-point  * values which correspond to the RGBA values for each sample.  *  * Returns: Color samples: { R1, G1, B1, A1, ..., Rn, Gn, Bn, An }.  */
end_comment

begin_function
name|gdouble
modifier|*
DECL|function|gimp_gradients_sample_custom (gint num_samples,gdouble * positions)
name|gimp_gradients_sample_custom
parameter_list|(
name|gint
name|num_samples
parameter_list|,
name|gdouble
modifier|*
name|positions
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gdouble
modifier|*
name|color_samples
init|=
name|NULL
decl_stmt|;
name|gint
name|num_color_samples
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_gradients_sample_custom"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|num_samples
argument_list|,
name|GIMP_PDB_FLOATARRAY
argument_list|,
name|positions
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
name|num_color_samples
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
name|color_samples
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|num_color_samples
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|color_samples
argument_list|,
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_floatarray
argument_list|,
name|num_color_samples
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
name|color_samples
return|;
block|}
end_function

end_unit

