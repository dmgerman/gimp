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
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbasetypes.h"
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
file|"core/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
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
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|gimprc_query_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|gimprc_set_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|get_default_comment_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|get_monitor_resolution_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimprc_query_invoker (Gimp * gimp,Argument * args)
name|gimprc_query_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|return_args
decl_stmt|;
name|gchar
modifier|*
name|token
decl_stmt|;
specifier|const
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
name|token
operator|==
name|NULL
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
name|success
operator|=
operator|(
name|value
operator|=
name|gimprc_find_token
argument_list|(
name|token
argument_list|)
operator|)
operator|!=
name|NULL
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
comment|/* custom ones failed, try the standard ones */
name|success
operator|=
operator|(
name|value
operator|=
name|gimprc_value_to_str
argument_list|(
name|token
argument_list|)
operator|)
operator|!=
name|NULL
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|gimprc_query_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|g_strdup
argument_list|(
name|value
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimprc_query_inargs
specifier|static
name|ProcArg
name|gimprc_query_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"token"
block|,
literal|"The token to query for"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimprc_query_outargs
specifier|static
name|ProcArg
name|gimprc_query_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"value"
block|,
literal|"The value associated with the queried token"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimprc_query_proc
specifier|static
name|ProcRecord
name|gimprc_query_proc
init|=
block|{
literal|"gimp_gimprc_query"
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
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|gimprc_query_inargs
block|,
literal|1
block|,
name|gimprc_query_outargs
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
DECL|function|gimprc_set_invoker (Gimp * gimp,Argument * args)
name|gimprc_set_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|token
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|value
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
name|value
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|save_gimprc_strings
argument_list|(
name|token
argument_list|,
name|value
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gimprc_set_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimprc_set_inargs
specifier|static
name|ProcArg
name|gimprc_set_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"token"
block|,
literal|"The token to modify"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"value"
block|,
literal|"The value to set the token to"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimprc_set_proc
specifier|static
name|ProcRecord
name|gimprc_set_proc
init|=
block|{
literal|"gimp_gimprc_set"
block|,
literal|"Sets a gimprc token to a value and saves it in the gimprc."
block|,
literal|"This procedure is used to add or change additional information in the gimprc file that is considered extraneous to the operation of the GIMP. Plug-ins that need configuration information can use this function to store it, and gimp_gimprc_query to retrieve it. This will accept _only_ parameters in the format of (<token><value>), where<token> and<value> must be strings. Entries not corresponding to this format will be eaten and no action will be performed. If the gimprc can not be written for whatever reason, gimp will complain loudly and the old gimprc will be saved in gimprc.old."
block|,
literal|"Seth Burgess"
block|,
literal|"Seth Burgess"
block|,
literal|"1999"
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|gimprc_set_inargs
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
DECL|function|get_default_comment_invoker (Gimp * gimp,Argument * args)
name|get_default_comment_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|return_args
decl_stmt|;
name|gchar
modifier|*
name|comment
decl_stmt|;
name|comment
operator|=
name|g_strdup
argument_list|(
name|gimp
operator|->
name|config
operator|->
name|default_comment
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|get_default_comment_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|comment
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|get_default_comment_outargs
specifier|static
name|ProcArg
name|get_default_comment_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"comment"
block|,
literal|"Default Image Comment"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|get_default_comment_proc
specifier|static
name|ProcRecord
name|get_default_comment_proc
init|=
block|{
literal|"gimp_get_default_comment"
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
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|1
block|,
name|get_default_comment_outargs
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
DECL|function|get_monitor_resolution_invoker (Gimp * gimp,Argument * args)
name|get_monitor_resolution_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|return_args
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|xres
operator|=
name|gimprc
operator|.
name|monitor_xres
expr_stmt|;
name|yres
operator|=
name|gimprc
operator|.
name|monitor_yres
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|get_monitor_resolution_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_float
operator|=
name|xres
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_float
operator|=
name|yres
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|get_monitor_resolution_outargs
specifier|static
name|ProcArg
name|get_monitor_resolution_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"xres"
block|,
literal|"X resolution"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"yres"
block|,
literal|"Y resolution"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|get_monitor_resolution_proc
specifier|static
name|ProcRecord
name|get_monitor_resolution_proc
init|=
block|{
literal|"gimp_get_monitor_resolution"
block|,
literal|"Get the monitor resolution as specified in the Preferences."
block|,
literal|"Returns the resolution of the monitor in pixels/inch. This value is taken from the Preferences (or the X-Server if this is set in the Preferences) and there's no guarantee for the value to be reasonable."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|2
block|,
name|get_monitor_resolution_outargs
block|,
block|{
block|{
name|get_monitor_resolution_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

