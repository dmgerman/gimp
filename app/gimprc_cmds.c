begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_function
name|void
DECL|function|register_gimprc_procs (void)
name|register_gimprc_procs
parameter_list|(
name|void
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
operator|&
name|gimprc_query_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|gimprc_set_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimprc_query_invoker (Argument * args)
name|gimprc_query_invoker
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
name|Argument
modifier|*
name|return_args
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
name|PDB_STRING
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
name|PDB_STRING
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
literal|"This procedure is used to locate additional information contained in the gimprc file considered extraneous to the operation of the GIMP. Plug-ins that need configuration information can expect it will be stored in the user gimprc file and can use this procedure to retrieve it. This query procedure will return the value associated with the specified token. This corresponds _only_ to entries with the format: (<token><value>). The value must be a string. Entries not corresponding to this format will cause warnings to be issued on gimprc parsing a nd will not be queryable."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
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
DECL|function|gimprc_set_invoker (Argument * args)
name|gimprc_set_invoker
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
name|PDB_STRING
block|,
literal|"token"
block|,
literal|"The token to modify"
block|}
block|,
block|{
name|PDB_STRING
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
name|PDB_INTERNAL
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

end_unit

