begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimp_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimp  * @title: gimp  * @short_description: Miscellaneous procedures  *  * Miscellaneous procedures not fitting in any category.  **/
end_comment

begin_comment
comment|/**  * gimp_version:  *  * Returns the host GIMP version.  *  * This procedure returns the version number of the currently running  * GIMP.  *  * Returns: GIMP version number.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_version (void)
name|gimp_version
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
name|version
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-version"
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
name|version
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
name|version
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_getpid:  *  * Returns the PID of the host GIMP process.  *  * This procedure returns the process ID of the currently running GIMP.  *  * Returns: The PID.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gint
DECL|function|gimp_getpid (void)
name|gimp_getpid
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
name|gint
name|pid
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-getpid"
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
name|pid
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
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|pid
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_attach_parasite:  * @parasite: The parasite to attach.  *  * Add a global parasite.  *  * This procedure attaches a global parasite. It has no return values.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_attach_parasite (const GimpParasite * parasite)
name|gimp_attach_parasite
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
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
literal|"gimp-attach-parasite"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_PARASITE
argument_list|,
name|parasite
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
comment|/**  * gimp_detach_parasite:  * @name: The name of the parasite to detach.  *  * Removes a global parasite.  *  * This procedure detaches a global parasite from. It has no return  * values.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_detach_parasite (const gchar * name)
name|gimp_detach_parasite
parameter_list|(
specifier|const
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
literal|"gimp-detach-parasite"
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
comment|/**  * gimp_get_parasite:  * @name: The name of the parasite to find.  *  * Look up a global parasite.  *  * Finds and returns the global parasite that was previously attached.  *  * Returns: The found parasite.  *  * Since: GIMP 2.8  **/
end_comment

begin_function
name|GimpParasite
modifier|*
DECL|function|gimp_get_parasite (const gchar * name)
name|gimp_get_parasite
parameter_list|(
specifier|const
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
name|GimpParasite
modifier|*
name|parasite
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-get-parasite"
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
name|parasite
operator|=
name|gimp_parasite_copy
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_parasite
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
name|parasite
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_get_parasite_list:  * @num_parasites: The number of attached parasites.  *  * List all parasites.  *  * Returns a list of all currently attached global parasites.  *  * Returns: The names of currently attached parasites. The returned value must be freed with g_strfreev().  *  * Since: GIMP 2.8  **/
end_comment

begin_function
name|gchar
modifier|*
modifier|*
DECL|function|gimp_get_parasite_list (gint * num_parasites)
name|gimp_get_parasite_list
parameter_list|(
name|gint
modifier|*
name|num_parasites
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
name|parasites
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
literal|"gimp-get-parasite-list"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|num_parasites
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
name|num_parasites
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
name|parasites
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
operator|*
name|num_parasites
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
name|num_parasites
condition|;
name|i
operator|++
control|)
name|parasites
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
name|parasites
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
name|parasites
return|;
block|}
end_function

end_unit

