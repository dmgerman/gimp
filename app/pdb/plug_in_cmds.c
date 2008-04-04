begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl. */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimpplugin.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimpplugindef.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager-menu-branch.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager-query.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"internal_procs.h"
end_include

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|plugins_query_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|plugins_query_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|search_string
decl_stmt|;
name|gint32
name|num_plugins
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|menu_path
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|plugin_accelerator
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|plugin_location
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|plugin_image_type
init|=
name|NULL
decl_stmt|;
name|gint32
modifier|*
name|plugin_install_time
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|plugin_real_name
init|=
name|NULL
decl_stmt|;
name|search_string
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|num_plugins
operator|=
name|gimp_plug_in_manager_query
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|search_string
argument_list|,
operator|&
name|menu_path
argument_list|,
operator|&
name|plugin_accelerator
argument_list|,
operator|&
name|plugin_location
argument_list|,
operator|&
name|plugin_image_type
argument_list|,
operator|&
name|plugin_real_name
argument_list|,
operator|&
name|plugin_install_time
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|gimp_value_take_stringarray
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|2
index|]
argument_list|,
name|menu_path
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|3
index|]
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|gimp_value_take_stringarray
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|4
index|]
argument_list|,
name|plugin_accelerator
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|5
index|]
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|gimp_value_take_stringarray
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|6
index|]
argument_list|,
name|plugin_location
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|7
index|]
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|gimp_value_take_stringarray
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|8
index|]
argument_list|,
name|plugin_image_type
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|9
index|]
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|gimp_value_take_int32array
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|10
index|]
argument_list|,
name|plugin_install_time
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|11
index|]
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|gimp_value_take_stringarray
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|12
index|]
argument_list|,
name|plugin_real_name
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|plugin_domain_register_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|plugin_domain_register_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|domain_name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|domain_path
decl_stmt|;
name|domain_name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|domain_path
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp
operator|->
name|plug_in_manager
operator|->
name|current_plug_in
decl_stmt|;
if|if
condition|(
name|plug_in
operator|&&
name|plug_in
operator|->
name|call_mode
operator|==
name|GIMP_PLUG_IN_CALL_QUERY
condition|)
block|{
name|gimp_plug_in_def_set_locale_domain
argument_list|(
name|plug_in
operator|->
name|plug_in_def
argument_list|,
name|domain_name
argument_list|,
name|domain_path
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|plugin_help_register_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|plugin_help_register_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|domain_name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|domain_uri
decl_stmt|;
name|domain_name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|domain_uri
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp
operator|->
name|plug_in_manager
operator|->
name|current_plug_in
decl_stmt|;
if|if
condition|(
name|plug_in
operator|&&
name|plug_in
operator|->
name|call_mode
operator|==
name|GIMP_PLUG_IN_CALL_QUERY
condition|)
block|{
name|gimp_plug_in_def_set_help_domain
argument_list|(
name|plug_in
operator|->
name|plug_in_def
argument_list|,
name|domain_name
argument_list|,
name|domain_uri
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|plugin_menu_register_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|plugin_menu_register_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|procedure_name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|menu_path
decl_stmt|;
name|procedure_name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|menu_path
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp
operator|->
name|plug_in_manager
operator|->
name|current_plug_in
decl_stmt|;
if|if
condition|(
name|plug_in
condition|)
block|{
name|gchar
modifier|*
name|canonical
init|=
name|gimp_canonicalize_identifier
argument_list|(
name|procedure_name
argument_list|)
decl_stmt|;
name|success
operator|=
name|gimp_plug_in_menu_register
argument_list|(
name|plug_in
argument_list|,
name|canonical
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|canonical
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|plugin_menu_branch_register_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|plugin_menu_branch_register_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|menu_path
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|menu_name
decl_stmt|;
name|menu_path
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|menu_name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp
operator|->
name|plug_in_manager
operator|->
name|current_plug_in
decl_stmt|;
if|if
condition|(
name|plug_in
condition|)
block|{
name|gimp_plug_in_manager_add_menu_branch
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|plug_in
operator|->
name|prog
argument_list|,
name|menu_path
argument_list|,
name|menu_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|plugin_icon_register_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|plugin_icon_register_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|procedure_name
decl_stmt|;
name|gint32
name|icon_type
decl_stmt|;
name|gint32
name|icon_data_length
decl_stmt|;
specifier|const
name|guint8
modifier|*
name|icon_data
decl_stmt|;
name|procedure_name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|icon_type
operator|=
name|g_value_get_enum
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|icon_data_length
operator|=
name|g_value_get_int
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|icon_data
operator|=
name|gimp_value_get_int8array
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp
operator|->
name|plug_in_manager
operator|->
name|current_plug_in
decl_stmt|;
if|if
condition|(
name|plug_in
operator|&&
name|plug_in
operator|->
name|call_mode
operator|==
name|GIMP_PLUG_IN_CALL_QUERY
condition|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|gchar
modifier|*
name|canonical
decl_stmt|;
name|canonical
operator|=
name|gimp_canonicalize_identifier
argument_list|(
name|procedure_name
argument_list|)
expr_stmt|;
name|proc
operator|=
name|gimp_plug_in_procedure_find
argument_list|(
name|plug_in
operator|->
name|plug_in_def
operator|->
name|procedures
argument_list|,
name|canonical
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|canonical
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc
condition|)
name|gimp_plug_in_procedure_set_icon
argument_list|(
name|proc
argument_list|,
name|icon_type
argument_list|,
name|icon_data
argument_list|,
name|icon_data_length
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|register_plug_in_procs (GimpPDB * pdb)
name|register_plug_in_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
comment|/*    * gimp-plugins-query    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plugins_query_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-plugins-query"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-plugins-query"
argument_list|,
literal|"Queries the plugin database for its contents."
argument_list|,
literal|"This procedure queries the contents of the plugin database."
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"1998"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"search-string"
argument_list|,
literal|"search string"
argument_list|,
literal|"If not an empty string then use this as a search pattern"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|GIMP_PARAM_NO_VALIDATE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-plugins"
argument_list|,
literal|"num plugins"
argument_list|,
literal|"The number of plugins"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string_array
argument_list|(
literal|"menu-path"
argument_list|,
literal|"menu path"
argument_list|,
literal|"The menu path of the plugin"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-plugins"
argument_list|,
literal|"num plugins"
argument_list|,
literal|"The number of plugins"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string_array
argument_list|(
literal|"plugin-accelerator"
argument_list|,
literal|"plugin accelerator"
argument_list|,
literal|"String representing keyboard accelerator (could be empty string)"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-plugins"
argument_list|,
literal|"num plugins"
argument_list|,
literal|"The number of plugins"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string_array
argument_list|(
literal|"plugin-location"
argument_list|,
literal|"plugin location"
argument_list|,
literal|"Location of the plugin program"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-plugins"
argument_list|,
literal|"num plugins"
argument_list|,
literal|"The number of plugins"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string_array
argument_list|(
literal|"plugin-image-type"
argument_list|,
literal|"plugin image type"
argument_list|,
literal|"Type of image that this plugin will work on"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-plugins"
argument_list|,
literal|"num plugins"
argument_list|,
literal|"The number of plugins"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32_array
argument_list|(
literal|"plugin-install-time"
argument_list|,
literal|"plugin install time"
argument_list|,
literal|"Time that the plugin was installed"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-plugins"
argument_list|,
literal|"num plugins"
argument_list|,
literal|"The number of plugins"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string_array
argument_list|(
literal|"plugin-real-name"
argument_list|,
literal|"plugin real name"
argument_list|,
literal|"The internal name of the plugin"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-plugin-domain-register    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plugin_domain_register_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-plugin-domain-register"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-plugin-domain-register"
argument_list|,
literal|"Registers a textdomain for localisation."
argument_list|,
literal|"This procedure adds a textdomain to the list of domains Gimp searches for strings when translating its menu entries. There is no need to call this function for plug-ins that have their strings included in the gimp-std-plugins domain as that is used by default. If the compiled message catalog is not in the standard location, you may specify an absolute path to another location. This procedure can only be called in the query function of a plug-in and it has to be called before any procedure is installed."
argument_list|,
literal|"Sven Neumann<sven@gimp.org>"
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"2000"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"domain-name"
argument_list|,
literal|"domain name"
argument_list|,
literal|"The name of the textdomain (must be unique)"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"domain-path"
argument_list|,
literal|"domain path"
argument_list|,
literal|"The absolute path to the compiled message catalog (may be NULL)"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|GIMP_PARAM_NO_VALIDATE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-plugin-help-register    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plugin_help_register_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-plugin-help-register"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-plugin-help-register"
argument_list|,
literal|"Register a help path for a plug-in."
argument_list|,
literal|"This procedure changes the help rootdir for the plug-in which calls it. All subsequent calls of 'gimp-help' from this plug-in will be interpreted relative to this rootdir."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2000"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"domain-name"
argument_list|,
literal|"domain name"
argument_list|,
literal|"The XML namespace of the plug-in's help pages"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"domain-uri"
argument_list|,
literal|"domain uri"
argument_list|,
literal|"The root URI of the plug-in's help pages"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-plugin-menu-register    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plugin_menu_register_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-plugin-menu-register"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-plugin-menu-register"
argument_list|,
literal|"Register an additional menu path for a plug-in procedure."
argument_list|,
literal|"This procedure installs an additional menu entry for the given procedure."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2004"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"procedure-name"
argument_list|,
literal|"procedure name"
argument_list|,
literal|"The procedure for which to install the menu path"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"menu-path"
argument_list|,
literal|"menu path"
argument_list|,
literal|"The procedure's additional menu path"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-plugin-menu-branch-register    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plugin_menu_branch_register_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-plugin-menu-branch-register"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-plugin-menu-branch-register"
argument_list|,
literal|"Register a sub-menu."
argument_list|,
literal|"This procedure installs a sub-menu which does not belong to any procedure. The menu-name should be the untranslated menu label. GIMP will look up the translation in the textdomain registered for the plug-in."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"menu-path"
argument_list|,
literal|"menu path"
argument_list|,
literal|"The sub-menu's menu path"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"menu-name"
argument_list|,
literal|"menu name"
argument_list|,
literal|"The name of the sub-menu"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-plugin-icon-register    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plugin_icon_register_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-plugin-icon-register"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-plugin-icon-register"
argument_list|,
literal|"Register an icon for a plug-in procedure."
argument_list|,
literal|"This procedure installs an icon for the given procedure."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2004"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"procedure-name"
argument_list|,
literal|"procedure name"
argument_list|,
literal|"The procedure for which to install the icon"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"icon-type"
argument_list|,
literal|"icon type"
argument_list|,
literal|"The type of the icon"
argument_list|,
name|GIMP_TYPE_ICON_TYPE
argument_list|,
name|GIMP_ICON_TYPE_STOCK_ID
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"icon-data-length"
argument_list|,
literal|"icon data length"
argument_list|,
literal|"The length of 'icon-data'"
argument_list|,
literal|1
argument_list|,
name|G_MAXINT32
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int8_array
argument_list|(
literal|"icon-data"
argument_list|,
literal|"icon data"
argument_list|,
literal|"The procedure's icon. The format depends on the 'icon_type' parameter"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

