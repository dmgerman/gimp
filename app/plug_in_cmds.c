begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2000 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
end_comment

begin_include
include|#
directive|include
file|"procedural_db.h"
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
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"plug_in.h"
end_include

begin_include
include|#
directive|include
file|"regex.h"
end_include

begin_decl_stmt
DECL|variable|progress_init_proc
specifier|static
name|ProcRecord
name|progress_init_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|progress_update_proc
specifier|static
name|ProcRecord
name|progress_update_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|temp_PDB_name_proc
specifier|static
name|ProcRecord
name|temp_PDB_name_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugins_query_proc
specifier|static
name|ProcRecord
name|plugins_query_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_domain_add_proc
specifier|static
name|ProcRecord
name|plugin_domain_add_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_plug_in_procs (void)
name|register_plug_in_procs
parameter_list|(
name|void
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
operator|&
name|progress_init_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|progress_update_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|temp_PDB_name_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|plugins_query_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|plugin_domain_add_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|match_strings (regex_t * preg,gchar * a)
name|match_strings
parameter_list|(
name|regex_t
modifier|*
name|preg
parameter_list|,
name|gchar
modifier|*
name|a
parameter_list|)
block|{
return|return
name|regexec
argument_list|(
name|preg
argument_list|,
name|a
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|progress_init_invoker (Argument * args)
name|progress_init_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
name|gchar
modifier|*
name|message
decl_stmt|;
name|gint32
name|gdisplay
decl_stmt|;
name|message
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
name|gdisplay
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
name|current_plug_in
operator|&&
name|current_plug_in
operator|->
name|open
condition|)
block|{
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|!
name|no_interface
condition|)
name|plug_in_progress_init
argument_list|(
name|current_plug_in
argument_list|,
name|message
argument_list|,
name|gdisplay
argument_list|)
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|progress_init_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|progress_init_inargs
specifier|static
name|ProcArg
name|progress_init_inargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"message"
block|,
literal|"Message to use in the progress dialog"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"gdisplay"
block|,
literal|"GDisplay to update progressbar in, or -1 for a seperate window"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|progress_init_proc
specifier|static
name|ProcRecord
name|progress_init_proc
init|=
block|{
literal|"gimp_progress_init"
block|,
literal|"Initializes the progress bar for the current plug-in."
block|,
literal|"Initializes the progress bar for the current plug-in. It is only valid to call this procedure from a plug-in."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
literal|2
block|,
name|progress_init_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|progress_init_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|progress_update_invoker (Argument * args)
name|progress_update_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
name|gdouble
name|percentage
decl_stmt|;
name|percentage
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|current_plug_in
operator|&&
name|current_plug_in
operator|->
name|open
condition|)
block|{
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|!
name|no_interface
condition|)
name|plug_in_progress_update
argument_list|(
name|current_plug_in
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|progress_update_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|progress_update_inargs
specifier|static
name|ProcArg
name|progress_update_inargs
index|[]
init|=
block|{
block|{
name|PDB_FLOAT
block|,
literal|"percentage"
block|,
literal|"Percentage of progress completed"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|progress_update_proc
specifier|static
name|ProcRecord
name|progress_update_proc
init|=
block|{
literal|"gimp_progress_update"
block|,
literal|"Updates the progress bar for the current plug-in."
block|,
literal|"Updates the progress bar for the current plug-in. It is only valid to call this procedure from a plug-in."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|progress_update_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|progress_update_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|temp_PDB_name_invoker (Argument * args)
name|temp_PDB_name_invoker
parameter_list|(
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
name|temp_name
decl_stmt|;
specifier|static
name|gint
name|proc_number
init|=
literal|0
decl_stmt|;
name|temp_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"temp_plugin_number_%d"
argument_list|,
name|proc_number
operator|++
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|temp_PDB_name_proc
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
name|pdb_pointer
operator|=
name|temp_name
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|temp_PDB_name_outargs
specifier|static
name|ProcArg
name|temp_PDB_name_outargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"temp_name"
block|,
literal|"A unique temporary name for a temporary PDB entry"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|temp_PDB_name_proc
specifier|static
name|ProcRecord
name|temp_PDB_name_proc
init|=
block|{
literal|"gimp_temp_PDB_name"
block|,
literal|"Generates a unique temporary PDB name."
block|,
literal|"This procedure generates a temporary PDB entry name that is guaranteed to be unique. It is many used by the interactive popup dialogs to generate a PDB entry name."
block|,
literal|"Andy Thomas"
block|,
literal|"Andy Thomas"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|1
block|,
name|temp_PDB_name_outargs
block|,
block|{
block|{
name|temp_PDB_name_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plugins_query_invoker (Argument * args)
name|plugins_query_invoker
parameter_list|(
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
name|PlugInProcDef
modifier|*
name|proc_def
decl_stmt|;
name|GSList
modifier|*
name|tmp
init|=
name|NULL
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
name|regex_t
name|sregex
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
if|if
condition|(
name|search_str
operator|&&
name|strlen
argument_list|(
name|search_str
argument_list|)
condition|)
name|regcomp
argument_list|(
operator|&
name|sregex
argument_list|,
name|search_str
argument_list|,
name|REG_ICASE
argument_list|)
expr_stmt|;
else|else
name|search_str
operator|=
name|NULL
expr_stmt|;
comment|/* count number of plugin entries, then allocate 4 arrays of correct size    * where we can store the strings.    */
name|tmp
operator|=
name|proc_defs
expr_stmt|;
while|while
condition|(
name|tmp
condition|)
block|{
name|proc_def
operator|=
name|tmp
operator|->
name|data
expr_stmt|;
name|tmp
operator|=
name|tmp
operator|->
name|next
expr_stmt|;
if|if
condition|(
name|proc_def
operator|->
name|prog
operator|&&
name|proc_def
operator|->
name|menu_path
condition|)
block|{
name|gchar
modifier|*
name|name
init|=
name|strrchr
argument_list|(
name|proc_def
operator|->
name|menu_path
argument_list|,
literal|'/'
argument_list|)
decl_stmt|;
if|if
condition|(
name|name
condition|)
name|name
operator|=
name|name
operator|+
literal|1
expr_stmt|;
else|else
name|name
operator|=
name|proc_def
operator|->
name|menu_path
expr_stmt|;
if|if
condition|(
name|search_str
operator|&&
name|match_strings
argument_list|(
operator|&
name|sregex
argument_list|,
name|name
argument_list|)
condition|)
continue|continue;
name|num_plugins
operator|++
expr_stmt|;
block|}
block|}
name|menu_strs
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|accel_strs
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|prog_strs
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|types_strs
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|realname_strs
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|time_ints
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|proc_defs
expr_stmt|;
while|while
condition|(
name|tmp
condition|)
block|{
if|if
condition|(
name|i
operator|>
name|num_plugins
condition|)
name|g_error
argument_list|(
literal|"Internal error counting plugins"
argument_list|)
expr_stmt|;
name|proc_def
operator|=
name|tmp
operator|->
name|data
expr_stmt|;
name|tmp
operator|=
name|tmp
operator|->
name|next
expr_stmt|;
if|if
condition|(
name|proc_def
operator|->
name|prog
operator|&&
name|proc_def
operator|->
name|menu_path
condition|)
block|{
name|ProcRecord
modifier|*
name|pr
init|=
operator|&
name|proc_def
operator|->
name|db_info
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|strrchr
argument_list|(
name|proc_def
operator|->
name|menu_path
argument_list|,
literal|'/'
argument_list|)
decl_stmt|;
if|if
condition|(
name|name
condition|)
name|name
operator|=
name|name
operator|+
literal|1
expr_stmt|;
else|else
name|name
operator|=
name|proc_def
operator|->
name|menu_path
expr_stmt|;
if|if
condition|(
name|search_str
operator|&&
name|match_strings
argument_list|(
operator|&
name|sregex
argument_list|,
name|name
argument_list|)
condition|)
continue|continue;
name|menu_strs
index|[
name|i
index|]
operator|=
name|g_strdup
argument_list|(
name|proc_def
operator|->
name|menu_path
argument_list|)
expr_stmt|;
name|accel_strs
index|[
name|i
index|]
operator|=
name|g_strdup
argument_list|(
name|proc_def
operator|->
name|accelerator
argument_list|)
expr_stmt|;
name|prog_strs
index|[
name|i
index|]
operator|=
name|g_strdup
argument_list|(
name|proc_def
operator|->
name|prog
argument_list|)
expr_stmt|;
name|types_strs
index|[
name|i
index|]
operator|=
name|g_strdup
argument_list|(
name|proc_def
operator|->
name|image_types
argument_list|)
expr_stmt|;
name|realname_strs
index|[
name|i
index|]
operator|=
name|g_strdup
argument_list|(
name|pr
operator|->
name|name
argument_list|)
expr_stmt|;
name|time_ints
index|[
name|i
index|]
operator|=
name|proc_def
operator|->
name|mtime
expr_stmt|;
name|i
operator|++
expr_stmt|;
block|}
block|}
comment|/* This I hope frees up internal stuff */
if|if
condition|(
name|search_str
condition|)
name|free
argument_list|(
name|sregex
operator|.
name|buffer
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
name|PDB_STRING
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
name|PDB_INT32
block|,
literal|"num_plugins"
block|,
literal|"The number of plugins"
block|}
block|,
block|{
name|PDB_STRINGARRAY
block|,
literal|"menu_path"
block|,
literal|"The menu path of the plugin"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"num_plugins"
block|,
literal|"The number of plugins"
block|}
block|,
block|{
name|PDB_STRINGARRAY
block|,
literal|"plugin_accelerator"
block|,
literal|"String representing keyboard accelerator (could be empty string)"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"num_plugins"
block|,
literal|"The number of plugins"
block|}
block|,
block|{
name|PDB_STRINGARRAY
block|,
literal|"plugin_location"
block|,
literal|"Location of the plugin program"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"num_plugins"
block|,
literal|"The number of plugins"
block|}
block|,
block|{
name|PDB_STRINGARRAY
block|,
literal|"plugin_image_type"
block|,
literal|"Type of image that this plugin will work on"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"num_plugins"
block|,
literal|"The number of plugins"
block|}
block|,
block|{
name|PDB_INT32ARRAY
block|,
literal|"plugin_install_time"
block|,
literal|"Time that the plugin was installed"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"num_plugins"
block|,
literal|"The number of plugins"
block|}
block|,
block|{
name|PDB_STRINGARRAY
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
name|PDB_INTERNAL
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
DECL|function|plugin_domain_add_invoker (Argument * args)
name|plugin_domain_add_invoker
parameter_list|(
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
name|PlugInDef
modifier|*
name|plug_in_def
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
name|current_plug_in
operator|&&
name|current_plug_in
operator|->
name|query
condition|)
block|{
name|plug_in_def
operator|=
name|current_plug_in
operator|->
name|user_data
expr_stmt|;
if|if
condition|(
name|plug_in_def
operator|->
name|locale_domain
condition|)
name|g_free
argument_list|(
name|plug_in_def
operator|->
name|locale_domain
argument_list|)
expr_stmt|;
name|plug_in_def
operator|->
name|locale_domain
operator|=
name|g_strdup
argument_list|(
name|domain_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_def
operator|->
name|locale_path
condition|)
empty_stmt|;
name|g_free
argument_list|(
name|plug_in_def
operator|->
name|locale_path
argument_list|)
expr_stmt|;
name|plug_in_def
operator|->
name|locale_path
operator|=
name|domain_path
condition|?
name|g_strdup
argument_list|(
name|domain_path
argument_list|)
else|:
name|NULL
expr_stmt|;
block|}
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|plugin_domain_add_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|plugin_domain_add_inargs
specifier|static
name|ProcArg
name|plugin_domain_add_inargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"domain_name"
block|,
literal|"The name of the textdomain (must be unique)."
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"domain_path"
block|,
literal|"The absolute path to the compiled message catalog (may be NULL)."
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_domain_add_proc
specifier|static
name|ProcRecord
name|plugin_domain_add_proc
init|=
block|{
literal|"gimp_plugin_domain_add"
block|,
literal|"Adds a textdomain for localisation."
block|,
literal|"This procedure adds a textdomain to the list of domains Gimp searches for strings when translating its menu entries. There is no need to call this function for plug-ins that have their strings included in the gimp-stdplugins domain as that is use by default. If the compiled message catalog is not in the standard location, you may specify an absolute path to another location. This procedure can only be called in the query function of a plug-in and it has to be called before a procedure is installed."
block|,
literal|"Sven Neumann"
block|,
literal|"Sven Neumann"
block|,
literal|"2000"
block|,
name|PDB_INTERNAL
block|,
literal|2
block|,
name|plugin_domain_add_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|plugin_domain_add_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

