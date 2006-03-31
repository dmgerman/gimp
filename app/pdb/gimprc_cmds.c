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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmodule/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"config/gimprc.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptemplate.h"
end_include

begin_decl_stmt
DECL|variable|gimprc_query_proc
specifier|static
name|ProcRecord
name|gimprc_query_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimprc_set_proc
specifier|static
name|ProcRecord
name|gimprc_set_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|get_default_comment_proc
specifier|static
name|ProcRecord
name|get_default_comment_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|get_monitor_resolution_proc
specifier|static
name|ProcRecord
name|get_monitor_resolution_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|get_theme_dir_proc
specifier|static
name|ProcRecord
name|get_theme_dir_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|get_color_configuration_proc
specifier|static
name|ProcRecord
name|get_color_configuration_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|get_module_load_inhibit_proc
specifier|static
name|ProcRecord
name|get_module_load_inhibit_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_gimprc_procs (Gimp * gimp)
name|register_gimprc_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|ProcRecord
modifier|*
name|procedure
decl_stmt|;
comment|/*    * gimprc_query    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|gimprc_query_proc
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"token"
argument_list|,
literal|"token"
argument_list|,
literal|"The token to query for"
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
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"value"
argument_list|,
literal|"value"
argument_list|,
literal|"The value associated with the queried token"
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
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimprc_set    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|gimprc_set_proc
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"token"
argument_list|,
literal|"token"
argument_list|,
literal|"The token to add or modify"
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
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"value"
argument_list|,
literal|"value"
argument_list|,
literal|"The value to set the token to"
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
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * get_default_comment    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|get_default_comment_proc
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"comment"
argument_list|,
literal|"comment"
argument_list|,
literal|"Default Image Comment"
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
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * get_monitor_resolution    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|get_monitor_resolution_proc
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"xres"
argument_list|,
literal|"xres"
argument_list|,
literal|"X resolution"
argument_list|,
operator|-
name|G_MAXDOUBLE
argument_list|,
name|G_MAXDOUBLE
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
name|GIMP_PDB_FLOAT
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"yres"
argument_list|,
literal|"yres"
argument_list|,
literal|"Y resolution"
argument_list|,
operator|-
name|G_MAXDOUBLE
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * get_theme_dir    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|get_theme_dir_proc
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"theme-dir"
argument_list|,
literal|"theme dir"
argument_list|,
literal|"The GUI theme dir"
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
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * get_color_configuration    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|get_color_configuration_proc
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"config"
argument_list|,
literal|"config"
argument_list|,
literal|"Serialized color management configuration"
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
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * get_module_load_inhibit    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|get_module_load_inhibit_proc
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"load-inhibit"
argument_list|,
literal|"load inhibit"
argument_list|,
literal|"The list of modules"
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
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimprc_query_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|gimprc_query_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|token
decl_stmt|;
name|gchar
modifier|*
name|value
init|=
name|NULL
decl_stmt|;
name|token
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|strlen
argument_list|(
name|token
argument_list|)
condition|)
block|{
comment|/*  use edit_config because unknown tokens are set there  */
name|value
operator|=
name|gimp_rc_query
argument_list|(
name|GIMP_RC
argument_list|(
name|gimp
operator|->
name|edit_config
argument_list|)
argument_list|,
name|token
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|value
condition|)
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
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_take_string
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|value
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimprc_query_proc
specifier|static
name|ProcRecord
name|gimprc_query_proc
init|=
block|{
literal|"gimp-gimprc-query"
block|,
literal|"gimp-gimprc-query"
block|,
literal|"Queries the gimprc file parser for information on a specified token."
block|,
literal|"This procedure is used to locate additional information contained in the gimprc file considered extraneous to the operation of the GIMP. Plug-ins that need configuration information can expect it will be stored in the user gimprc file and can use this procedure to retrieve it. This query procedure will return the value associated with the specified token. This corresponds _only_ to entries with the format: (<token><value>). The value must be a string. Entries not corresponding to this format will cause warnings to be issued on gimprc parsing and will not be queryable."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1997"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|gimprc_query_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimprc_set_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|gimprc_set_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|token
decl_stmt|;
name|gchar
modifier|*
name|value
decl_stmt|;
name|token
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|value
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|strlen
argument_list|(
name|token
argument_list|)
condition|)
block|{
comment|/*  use edit_config because that's the one that gets saved  */
name|gimp_rc_set_unknown_token
argument_list|(
name|GIMP_RC
argument_list|(
name|gimp
operator|->
name|edit_config
argument_list|)
argument_list|,
name|token
argument_list|,
name|value
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
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimprc_set_proc
specifier|static
name|ProcRecord
name|gimprc_set_proc
init|=
block|{
literal|"gimp-gimprc-set"
block|,
literal|"gimp-gimprc-set"
block|,
literal|"Sets a gimprc token to a value and saves it in the gimprc."
block|,
literal|"This procedure is used to add or change additional information in the gimprc file that is considered extraneous to the operation of the GIMP. Plug-ins that need configuration information can use this function to store it, and gimp_gimprc_query to retrieve it. This will accept _only_ string values in UTF-8 encoding."
block|,
literal|"Seth Burgess"
block|,
literal|"Seth Burgess"
block|,
literal|"1999"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|gimprc_set_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|get_default_comment_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|get_default_comment_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|comment
init|=
name|NULL
decl_stmt|;
name|comment
operator|=
name|g_strdup
argument_list|(
name|gimp
operator|->
name|config
operator|->
name|default_image
operator|->
name|comment
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_value_take_string
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|comment
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|get_default_comment_proc
specifier|static
name|ProcRecord
name|get_default_comment_proc
init|=
block|{
literal|"gimp-get-default-comment"
block|,
literal|"gimp-get-default-comment"
block|,
literal|"Get the default image comment as specified in the Preferences."
block|,
literal|"Returns a copy of the default image comment."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|get_default_comment_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|get_monitor_resolution_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|get_monitor_resolution_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gdouble
name|xres
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|yres
init|=
literal|0.0
decl_stmt|;
name|xres
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|monitor_xres
expr_stmt|;
name|yres
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|monitor_yres
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|xres
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
operator|&
name|return_vals
index|[
literal|2
index|]
operator|.
name|value
argument_list|,
name|yres
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|get_monitor_resolution_proc
specifier|static
name|ProcRecord
name|get_monitor_resolution_proc
init|=
block|{
literal|"gimp-get-monitor-resolution"
block|,
literal|"gimp-get-monitor-resolution"
block|,
literal|"Get the monitor resolution as specified in the Preferences."
block|,
literal|"Returns the resolution of the monitor in pixels/inch. This value is taken from the Preferences (or the windowing system if this is set in the Preferences) and there's no guarantee for the value to be reasonable."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|get_monitor_resolution_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|get_theme_dir_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|get_theme_dir_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|theme_dir
init|=
name|NULL
decl_stmt|;
name|theme_dir
operator|=
name|g_strdup
argument_list|(
name|gimp_get_theme_dir
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_value_take_string
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|theme_dir
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|get_theme_dir_proc
specifier|static
name|ProcRecord
name|get_theme_dir_proc
init|=
block|{
literal|"gimp-get-theme-dir"
block|,
literal|"gimp-get-theme-dir"
block|,
literal|"Get the directory of the current GUI theme."
block|,
literal|"Returns a copy of the current GUI theme dir."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|get_theme_dir_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|get_color_configuration_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|get_color_configuration_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|config
init|=
name|NULL
decl_stmt|;
name|config
operator|=
name|gimp_config_serialize_to_string
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|gimp
operator|->
name|config
operator|->
name|color_management
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_value_take_string
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|config
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|get_color_configuration_proc
specifier|static
name|ProcRecord
name|get_color_configuration_proc
init|=
block|{
literal|"gimp-get-color-configuration"
block|,
literal|"gimp-get-color-configuration"
block|,
literal|"Get a serialized version of the color management configuration."
block|,
literal|"Returns a string that can be deserialized into a GimpColorConfig object representing the current color management configuration."
block|,
literal|"Sven Neumann<sven@gimp.org>"
block|,
literal|"Sven Neumann"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|get_color_configuration_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|get_module_load_inhibit_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|get_module_load_inhibit_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|load_inhibit
init|=
name|NULL
decl_stmt|;
name|load_inhibit
operator|=
name|g_strdup
argument_list|(
name|gimp_module_db_get_load_inhibit
argument_list|(
name|gimp
operator|->
name|module_db
argument_list|)
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_value_take_string
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|load_inhibit
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|get_module_load_inhibit_proc
specifier|static
name|ProcRecord
name|get_module_load_inhibit_proc
init|=
block|{
literal|"gimp-get-module-load-inhibit"
block|,
literal|"gimp-get-module-load-inhibit"
block|,
literal|"Get the list of modules which should not be loaded."
block|,
literal|"Returns a copy of the list of modules which should not be loaded."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|get_module_load_inhibit_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

