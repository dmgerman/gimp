begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpplugin_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_function
name|void
DECL|function|gimp_progress_init (gchar * message)
name|gimp_progress_init
parameter_list|(
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_progress_init"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|message
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|gimp_default_display
argument_list|()
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_progress_update (gdouble percentage)
name|gimp_progress_update
parameter_list|(
name|gdouble
name|percentage
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_progress_update"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|percentage
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_temp_PDB_name (void)
name|gimp_temp_PDB_name
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
name|temp_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_temp_PDB_name"
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
name|temp_name
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
name|temp_name
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plugin_domain_register (gchar * domain_name,gchar * domain_path)
name|gimp_plugin_domain_register
parameter_list|(
name|gchar
modifier|*
name|domain_name
parameter_list|,
name|gchar
modifier|*
name|domain_path
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_plugin_domain_register"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|domain_name
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|domain_path
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plugin_help_register (gchar * help_path)
name|gimp_plugin_help_register
parameter_list|(
name|gchar
modifier|*
name|help_path
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_plugin_help_register"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|help_path
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

