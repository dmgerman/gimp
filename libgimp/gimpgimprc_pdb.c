begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpgimprc_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimpgimprc  * @title: gimpgimprc  * @short_description: Interactions with settings from gimprc.  *  * Interactions with settings from gimprc.  **/
end_comment

begin_comment
comment|/**  * gimp_gimprc_query:  * @token: The token to query for.  *  * Queries the gimprc file parser for information on a specified token.  *  * This procedure is used to locate additional information contained in  * the gimprc file considered extraneous to the operation of GIMP.  * Plug-ins that need configuration information can expect it will be  * stored in the user gimprc file and can use this procedure to  * retrieve it. This query procedure will return the value associated  * with the specified token. This corresponds _only_ to entries with  * the format: (&lt;token&gt;&lt;value&gt;). The value must be a  * string. Entries not corresponding to this format will cause warnings  * to be issued on gimprc parsing and will not be queryable.  *  * Returns: The value associated with the queried token.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_gimprc_query (const gchar * token)
name|gimp_gimprc_query
parameter_list|(
specifier|const
name|gchar
modifier|*
name|token
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
name|value
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-gimprc-query"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|token
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
name|value
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
name|value
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_gimprc_set:  * @token: The token to add or modify.  * @value: The value to set the token to.  *  * Sets a gimprc token to a value and saves it in the gimprc.  *  * This procedure is used to add or change additional information in  * the gimprc file that is considered extraneous to the operation of  * GIMP. Plug-ins that need configuration information can use this  * function to store it, and gimp_gimprc_query() to retrieve it. This  * will accept _only_ string values in UTF-8 encoding.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_gimprc_set (const gchar * token,const gchar * value)
name|gimp_gimprc_set
parameter_list|(
specifier|const
name|gchar
modifier|*
name|token
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
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
literal|"gimp-gimprc-set"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|token
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|value
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
comment|/**  * gimp_get_default_comment:  *  * Get the default image comment as specified in the Preferences.  *  * Returns a copy of the default image comment.  *  * Returns: Default image comment.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_get_default_comment (void)
name|gimp_get_default_comment
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
name|comment
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-get-default-comment"
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
name|comment
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
name|comment
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_get_default_unit:  *  * Get the default unit (taken from the user's locale).  *  * Returns the default unit's integer ID.  *  * Returns: Default unit.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|GimpUnit
DECL|function|gimp_get_default_unit (void)
name|gimp_get_default_unit
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
name|GimpUnit
name|unit_id
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-get-default-unit"
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
name|unit_id
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_unit
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|unit_id
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_get_monitor_resolution:  * @xres: X resolution.  * @yres: Y resolution.  *  * Get the monitor resolution as specified in the Preferences.  *  * Returns the resolution of the monitor in pixels/inch. This value is  * taken from the Preferences (or the windowing system if this is set  * in the Preferences) and there's no guarantee for the value to be  * reasonable.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_get_monitor_resolution (gdouble * xres,gdouble * yres)
name|gimp_get_monitor_resolution
parameter_list|(
name|gdouble
modifier|*
name|xres
parameter_list|,
name|gdouble
modifier|*
name|yres
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
literal|"gimp-get-monitor-resolution"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|xres
operator|=
literal|0.0
expr_stmt|;
operator|*
name|yres
operator|=
literal|0.0
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
name|xres
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
operator|*
name|yres
operator|=
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_float
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
comment|/**  * gimp_get_theme_dir:  *  * Get the directory of the current GUI theme.  *  * Returns a copy of the current GUI theme dir.  *  * Returns: The GUI theme dir.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_get_theme_dir (void)
name|gimp_get_theme_dir
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
name|theme_dir
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-get-theme-dir"
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
name|theme_dir
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
name|theme_dir
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_get_color_configuration:  *  * Get a serialized version of the color management configuration.  *  * Returns a string that can be deserialized into a GimpColorConfig  * object representing the current color management configuration.  *  * Returns: Serialized color management configuration.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_get_color_configuration (void)
name|_gimp_get_color_configuration
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
name|config
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-get-color-configuration"
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
name|config
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
name|config
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_get_module_load_inhibit:  *  * Get the list of modules which should not be loaded.  *  * Returns a copy of the list of modules which should not be loaded.  *  * Returns: The list of modules.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_get_module_load_inhibit (void)
name|gimp_get_module_load_inhibit
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
name|load_inhibit
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-get-module-load-inhibit"
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
name|load_inhibit
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
name|load_inhibit
return|;
block|}
end_function

end_unit

