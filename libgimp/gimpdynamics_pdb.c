begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpdynamics_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimpdynamics  * @title: gimpdynamics  * @short_description: Operations related to paint dynamics.  *  * Operations related to paint dynamics.  **/
end_comment

begin_comment
comment|/**  * gimp_dynamics_refresh:  *  * Refresh current paint dynamics. This function always succeeds.  *  * This procedure retrieves all paint dynamics currently in the user's  * paint dynamics path and updates the paint dynamics dialogs  * accordingly.  *  * Returns: TRUE on success.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_dynamics_refresh (void)
name|gimp_dynamics_refresh
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpPDB
modifier|*
name|pdb
init|=
name|gimp_get_pdb
argument_list|()
decl_stmt|;
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
name|NULL
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb
condition|)
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|pdb
argument_list|,
literal|"gimp-dynamics-refresh"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-dynamics-refresh"
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
comment|/**  * gimp_dynamics_get_list:  * @filter: An optional regular expression used to filter the list.  * @num_dynamics: (out): The number of available paint dynamics.  *  * Retrieve the list of loaded paint dynamics.  *  * This procedure returns a list of the paint dynamics that are  * currently available.  *  * Returns: (array length=num_dynamics) (element-type gchar*) (transfer full):  *          The list of paint dynamics names.  *          The returned value must be freed with g_strfreev().  *  * Since: 2.8  **/
end_comment

begin_function
name|gchar
modifier|*
modifier|*
DECL|function|gimp_dynamics_get_list (const gchar * filter,gint * num_dynamics)
name|gimp_dynamics_get_list
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filter
parameter_list|,
name|gint
modifier|*
name|num_dynamics
parameter_list|)
block|{
name|GimpPDB
modifier|*
name|pdb
init|=
name|gimp_get_pdb
argument_list|()
decl_stmt|;
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
name|dynamics_list
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|filter
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb
condition|)
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|pdb
argument_list|,
literal|"gimp-dynamics-get-list"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-dynamics-get-list"
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
name|num_dynamics
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
name|num_dynamics
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
name|dynamics_list
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
name|dynamics_list
return|;
block|}
end_function

end_unit

