begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
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
file|"libgimpbase/gimpprotocol.h"
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-def.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-params.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc-def.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-ins-query.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-ins.h"
end_include

begin_decl_stmt
DECL|variable|plugins_query_proc
specifier|static
name|ProcRecord
name|plugins_query_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_domain_register_proc
specifier|static
name|ProcRecord
name|plugin_domain_register_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_help_register_proc
specifier|static
name|ProcRecord
name|plugin_help_register_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_menu_register_proc
specifier|static
name|ProcRecord
name|plugin_menu_register_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_menu_branch_register_proc
specifier|static
name|ProcRecord
name|plugin_menu_branch_register_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_icon_register_proc
specifier|static
name|ProcRecord
name|plugin_icon_register_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_plug_in_procs (Gimp * gimp)
name|register_plug_in_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|plugins_query_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|plugin_domain_register_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|plugin_help_register_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|plugin_menu_register_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|plugin_menu_branch_register_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|plugin_icon_register_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plugins_query_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|plugins_query_invoker
parameter_list|(
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gchar
modifier|*
name|search_str
decl_stmt|;
name|gint32
name|num_plugins
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|menu_strs
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|accel_strs
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|prog_strs
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|types_strs
decl_stmt|;
name|gint32
modifier|*
name|time_ints
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|realname_strs
decl_stmt|;
name|search_str
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
name|num_plugins
operator|=
name|plug_ins_query
argument_list|(
name|gimp
argument_list|,
name|search_str
argument_list|,
operator|&
name|menu_strs
argument_list|,
operator|&
name|accel_strs
argument_list|,
operator|&
name|prog_strs
argument_list|,
operator|&
name|types_strs
argument_list|,
operator|&
name|realname_strs
argument_list|,
operator|&
name|time_ints
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|plugins_query_proc
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|num_plugins
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|menu_strs
expr_stmt|;
name|return_args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|num_plugins
expr_stmt|;
name|return_args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|accel_strs
expr_stmt|;
name|return_args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|num_plugins
expr_stmt|;
name|return_args
index|[
literal|6
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|prog_strs
expr_stmt|;
name|return_args
index|[
literal|7
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|num_plugins
expr_stmt|;
name|return_args
index|[
literal|8
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|types_strs
expr_stmt|;
name|return_args
index|[
literal|9
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|num_plugins
expr_stmt|;
name|return_args
index|[
literal|10
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|time_ints
expr_stmt|;
name|return_args
index|[
literal|11
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|num_plugins
expr_stmt|;
name|return_args
index|[
literal|12
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|realname_strs
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|plugins_query_inargs
specifier|static
name|ProcArg
name|plugins_query_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"search_string"
block|,
literal|"If not an empty string then use this as a search pattern"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugins_query_outargs
specifier|static
name|ProcArg
name|plugins_query_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"num_plugins"
block|,
literal|"The number of plugins"
block|}
block|,
block|{
name|GIMP_PDB_STRINGARRAY
block|,
literal|"menu_path"
block|,
literal|"The menu path of the plugin"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"num_plugins"
block|,
literal|"The number of plugins"
block|}
block|,
block|{
name|GIMP_PDB_STRINGARRAY
block|,
literal|"plugin_accelerator"
block|,
literal|"String representing keyboard accelerator (could be empty string)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"num_plugins"
block|,
literal|"The number of plugins"
block|}
block|,
block|{
name|GIMP_PDB_STRINGARRAY
block|,
literal|"plugin_location"
block|,
literal|"Location of the plugin program"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"num_plugins"
block|,
literal|"The number of plugins"
block|}
block|,
block|{
name|GIMP_PDB_STRINGARRAY
block|,
literal|"plugin_image_type"
block|,
literal|"Type of image that this plugin will work on"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"num_plugins"
block|,
literal|"The number of plugins"
block|}
block|,
block|{
name|GIMP_PDB_INT32ARRAY
block|,
literal|"plugin_install_time"
block|,
literal|"Time that the plugin was installed"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"num_plugins"
block|,
literal|"The number of plugins"
block|}
block|,
block|{
name|GIMP_PDB_STRINGARRAY
block|,
literal|"plugin_real_name"
block|,
literal|"The internal name of the plugin"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugins_query_proc
specifier|static
name|ProcRecord
name|plugins_query_proc
init|=
block|{
literal|"gimp_plugins_query"
block|,
literal|"Queries the plugin database for its contents."
block|,
literal|"This procedure queries the contents of the plugin database."
block|,
literal|"Andy Thomas"
block|,
literal|"Andy Thomas"
block|,
literal|"1998"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|plugins_query_inargs
block|,
literal|12
block|,
name|plugins_query_outargs
block|,
block|{
block|{
name|plugins_query_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plugin_domain_register_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|plugin_domain_register_invoker
parameter_list|(
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|domain_name
decl_stmt|;
name|gchar
modifier|*
name|domain_path
decl_stmt|;
name|domain_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|domain_name
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|domain_name
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|domain_path
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
operator|&&
name|gimp
operator|->
name|current_plug_in
operator|->
name|query
condition|)
block|{
name|plug_in_def_set_locale_domain_name
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|plug_in_def
argument_list|,
name|domain_name
argument_list|)
expr_stmt|;
name|plug_in_def_set_locale_domain_path
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|plug_in_def
argument_list|,
name|domain_path
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|plugin_domain_register_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|plugin_domain_register_inargs
specifier|static
name|ProcArg
name|plugin_domain_register_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"domain_name"
block|,
literal|"The name of the textdomain (must be unique)"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"domain_path"
block|,
literal|"The absolute path to the compiled message catalog (may be NULL)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_domain_register_proc
specifier|static
name|ProcRecord
name|plugin_domain_register_proc
init|=
block|{
literal|"gimp_plugin_domain_register"
block|,
literal|"Registers a textdomain for localisation."
block|,
literal|"This procedure adds a textdomain to the list of domains Gimp searches for strings when translating its menu entries. There is no need to call this function for plug-ins that have their strings included in the gimp-std-plugins domain as that is used by default. If the compiled message catalog is not in the standard location, you may specify an absolute path to another location. This procedure can only be called in the query function of a plug-in and it has to be called before any procedure is installed."
block|,
literal|"Sven Neumann"
block|,
literal|"Sven Neumann"
block|,
literal|"2000"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|plugin_domain_register_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|plugin_domain_register_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plugin_help_register_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|plugin_help_register_invoker
parameter_list|(
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|domain_name
decl_stmt|;
name|gchar
modifier|*
name|domain_uri
decl_stmt|;
name|domain_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|domain_name
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|domain_name
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|domain_uri
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|domain_uri
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|domain_uri
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
operator|&&
name|gimp
operator|->
name|current_plug_in
operator|->
name|query
condition|)
block|{
name|plug_in_def_set_help_domain_name
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|plug_in_def
argument_list|,
name|domain_name
argument_list|)
expr_stmt|;
name|plug_in_def_set_help_domain_uri
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|plug_in_def
argument_list|,
name|domain_uri
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|plugin_help_register_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|plugin_help_register_inargs
specifier|static
name|ProcArg
name|plugin_help_register_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"domain_name"
block|,
literal|"The XML namespace of the plug-in's help pages"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"domain_uri"
block|,
literal|"The root URI of the plug-in's help pages"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_help_register_proc
specifier|static
name|ProcRecord
name|plugin_help_register_proc
init|=
block|{
literal|"gimp_plugin_help_register"
block|,
literal|"Register a help path for a plug-in."
block|,
literal|"This procedure changes the help rootdir for the plug-in which calls it. All subsequent calls of gimp_help from this plug-in will be interpreted relative to this rootdir."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"2000"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|plugin_help_register_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|plugin_help_register_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plugin_menu_register_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|plugin_menu_register_invoker
parameter_list|(
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|procedure_name
decl_stmt|;
name|gchar
modifier|*
name|menu_path
decl_stmt|;
name|procedure_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|procedure_name
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|procedure_name
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|menu_path
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|menu_path
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|menu_path
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
condition|)
block|{
name|PlugInProcDef
modifier|*
name|proc_def
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|plug_in_def
condition|)
name|proc_def
operator|=
name|plug_in_proc_def_find
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|plug_in_def
operator|->
name|proc_defs
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc_def
condition|)
name|proc_def
operator|=
name|plug_in_proc_def_find
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|temp_proc_defs
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_def
condition|)
block|{
if|if
condition|(
name|proc_def
operator|->
name|menu_label
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|plug_in_proc_args_check
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|name
argument_list|,
name|gimp
operator|->
name|current_plug_in
operator|->
name|prog
argument_list|,
name|procedure_name
argument_list|,
name|menu_path
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|args
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|num_args
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|values
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|num_values
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
switch|switch
condition|(
name|proc_def
operator|->
name|db_info
operator|.
name|proc_type
condition|)
block|{
case|case
name|GIMP_INTERNAL
case|:
name|success
operator|=
name|FALSE
expr_stmt|;
break|break;
case|case
name|GIMP_PLUGIN
case|:
case|case
name|GIMP_EXTENSION
case|:
if|if
condition|(
operator|!
name|gimp
operator|->
name|current_plug_in
operator|->
name|query
operator|&&
operator|!
name|gimp
operator|->
name|current_plug_in
operator|->
name|init
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
break|break;
case|case
name|GIMP_TEMPORARY
case|:
break|break;
block|}
if|if
condition|(
name|success
condition|)
block|{
name|proc_def
operator|->
name|menu_paths
operator|=
name|g_list_append
argument_list|(
name|proc_def
operator|->
name|menu_paths
argument_list|,
name|g_strdup
argument_list|(
name|menu_path
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp
operator|->
name|no_interface
operator|&&
name|proc_def
operator|->
name|db_info
operator|.
name|proc_type
operator|==
name|GIMP_TEMPORARY
condition|)
block|{
name|gimp_menus_create_item
argument_list|(
name|gimp
argument_list|,
name|proc_def
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
else|else
block|{
name|g_message
argument_list|(
literal|"Plug-In \"%s\"\n(%s)\n\n"
literal|"attempted to install additional menu_path \"%s\"\n"
literal|"for procedure \"%s\".\n"
literal|"However the menu_path given in "
literal|"gimp_install_procedure() already contained "
literal|"a path. To make this work, pass just the menu's "
literal|"label to gimp_install_procedure()."
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|name
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|prog
argument_list|)
argument_list|,
name|menu_path
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|plugin_menu_register_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|plugin_menu_register_inargs
specifier|static
name|ProcArg
name|plugin_menu_register_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"procedure_name"
block|,
literal|"The procedure for which to install the menu path"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"menu_path"
block|,
literal|"The procedure's additional menu path"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_menu_register_proc
specifier|static
name|ProcRecord
name|plugin_menu_register_proc
init|=
block|{
literal|"gimp_plugin_menu_register"
block|,
literal|"Register an additional menu path for a plug-in procedure."
block|,
literal|"This procedure installs an additional menu entry for the given procedure."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"2004"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|plugin_menu_register_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|plugin_menu_register_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plugin_menu_branch_register_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|plugin_menu_branch_register_invoker
parameter_list|(
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|menu_path
decl_stmt|;
name|gchar
modifier|*
name|menu_name
decl_stmt|;
name|menu_path
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|menu_path
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|menu_path
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|menu_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|menu_name
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|menu_name
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
condition|)
block|{
name|plug_ins_menu_branch_add
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|current_plug_in
operator|->
name|prog
argument_list|,
name|menu_path
argument_list|,
name|menu_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp
operator|->
name|no_interface
condition|)
block|{
name|gimp_menus_create_branch
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|current_plug_in
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
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|plugin_menu_branch_register_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|plugin_menu_branch_register_inargs
specifier|static
name|ProcArg
name|plugin_menu_branch_register_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"menu_path"
block|,
literal|"The sub-menu's menu path"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"menu_name"
block|,
literal|"The name of the sub-menu"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_menu_branch_register_proc
specifier|static
name|ProcRecord
name|plugin_menu_branch_register_proc
init|=
block|{
literal|"gimp_plugin_menu_branch_register"
block|,
literal|"Register a sub-menu."
block|,
literal|"This procedure installs an sub-menu which does not belong to any procedure."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|plugin_menu_branch_register_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|plugin_menu_branch_register_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plugin_icon_register_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|plugin_icon_register_invoker
parameter_list|(
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
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
name|guint8
modifier|*
name|icon_data
decl_stmt|;
name|procedure_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|procedure_name
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|procedure_name
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|icon_type
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|icon_type
operator|<
name|GIMP_ICON_TYPE_STOCK_ID
operator|||
name|icon_type
operator|>
name|GIMP_ICON_TYPE_IMAGE_FILE
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|icon_data_length
operator|=
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|icon_data_length
operator|<=
literal|0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|icon_data
operator|=
operator|(
name|guint8
operator|*
operator|)
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
operator|&&
name|gimp
operator|->
name|current_plug_in
operator|->
name|query
condition|)
block|{
name|PlugInProcDef
modifier|*
name|proc_def
decl_stmt|;
name|proc_def
operator|=
name|plug_in_proc_def_find
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|plug_in_def
operator|->
name|proc_defs
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_def
condition|)
name|plug_in_proc_def_set_icon
argument_list|(
name|proc_def
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
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|plugin_icon_register_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|plugin_icon_register_inargs
specifier|static
name|ProcArg
name|plugin_icon_register_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"procedure_name"
block|,
literal|"The procedure for which to install the icon"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"icon_type"
block|,
literal|"The type of the icon"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"icon_data_length"
block|,
literal|"The length of 'icon_data': 0< icon_data_length"
block|}
block|,
block|{
name|GIMP_PDB_INT8ARRAY
block|,
literal|"icon_data"
block|,
literal|"The procedure's icon. The format depends on the 'icon_type' parameter"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_icon_register_proc
specifier|static
name|ProcRecord
name|plugin_icon_register_proc
init|=
block|{
literal|"gimp_plugin_icon_register"
block|,
literal|"Register an icon for a plug-in procedure."
block|,
literal|"This procedure installs an icon for the given procedure."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"2004"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|4
block|,
name|plugin_icon_register_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|plugin_icon_register_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

