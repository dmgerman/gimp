begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpplugin_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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

begin_include
include|#
directive|include
file|"gimpplugin_pdb.h"
end_include

begin_comment
comment|/**  * _gimp_plugin_domain_register:  * @domain_name: The name of the textdomain (must be unique).  * @domain_path: The absolute path to the compiled message catalog (may be NULL).  *  * Registers a textdomain for localisation.  *  * This procedure adds a textdomain to the list of domains Gimp  * searches for strings when translating its menu entries. There is no  * need to call this function for plug-ins that have their strings  * included in the 'gimp-std-plugins' domain as that is used by  * default. If the compiled message catalog is not in the standard  * location, you may specify an absolute path to another location. This  * procedure can only be called in the query function of a plug-in and  * it has to be called before any procedure is installed.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_plugin_domain_register (const gchar * domain_name,const gchar * domain_path)
name|_gimp_plugin_domain_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_path
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
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|domain_name
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|domain_path
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-plugin-domain-register"
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
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
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
comment|/**  * _gimp_plugin_help_register:  * @domain_name: The XML namespace of the plug-in's help pages.  * @domain_uri: The root URI of the plug-in's help pages.  *  * Register a help path for a plug-in.  *  * This procedure registers user documentation for the calling plug-in  * with the GIMP help system. The domain_uri parameter points to the  * root directory where the plug-in help is installed. For each  * supported language there should be a file called 'gimp-help.xml'  * that maps the help IDs to the actual help files.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_plugin_help_register (const gchar * domain_name,const gchar * domain_uri)
name|_gimp_plugin_help_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_uri
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
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|domain_name
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|domain_uri
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-plugin-help-register"
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
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
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
comment|/**  * _gimp_plugin_menu_branch_register:  * @menu_path: The sub-menu's menu path.  * @menu_name: The name of the sub-menu.  *  * Register a sub-menu.  *  * This procedure installs a sub-menu which does not belong to any  * procedure. The menu-name should be the untranslated menu label. GIMP  * will look up the translation in the textdomain registered for the  * plug-in.  *  * Returns: TRUE on success.  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_plugin_menu_branch_register (const gchar * menu_path,const gchar * menu_name)
name|_gimp_plugin_menu_branch_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_name
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
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|menu_path
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|menu_name
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-plugin-menu-branch-register"
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
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
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
comment|/**  * _gimp_plugin_set_pdb_error_handler:  * @handler: Who is responsible for handling procedure call errors.  *  * Sets an error handler for procedure calls.  *  * This procedure changes the way that errors in procedure calls are  * handled. By default GIMP will raise an error dialog if a procedure  * call made by a plug-in fails. Using this procedure the plug-in can  * change this behavior. If the error handler is set to  * %GIMP_PDB_ERROR_HANDLER_PLUGIN, then the plug-in is responsible for  * calling gimp_get_pdb_error() and handling the error whenever one if  * its procedure calls fails. It can do this by displaying the error  * message or by forwarding it in its own return values.  *  * Returns: TRUE on success.  *  * Since: 2.6  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_plugin_set_pdb_error_handler (GimpPDBErrorHandler handler)
name|_gimp_plugin_set_pdb_error_handler
parameter_list|(
name|GimpPDBErrorHandler
name|handler
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
name|NULL
argument_list|,
name|GIMP_TYPE_PDB_ERROR_HANDLER
argument_list|,
name|handler
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-plugin-set-pdb-error-handler"
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
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
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
comment|/**  * _gimp_plugin_get_pdb_error_handler:  *  * Retrieves the active error handler for procedure calls.  *  * This procedure retrieves the currently active error handler for  * procedure calls made by the calling plug-in. See  * gimp_plugin_set_pdb_error_handler() for details.  *  * Returns: Who is responsible for handling procedure call errors.  *  * Since: 2.6  **/
end_comment

begin_function
name|GimpPDBErrorHandler
DECL|function|_gimp_plugin_get_pdb_error_handler (void)
name|_gimp_plugin_get_pdb_error_handler
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
name|GimpPDBErrorHandler
name|handler
init|=
literal|0
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
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-plugin-get-pdb-error-handler"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|handler
operator|=
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|handler
return|;
block|}
end_function

end_unit

