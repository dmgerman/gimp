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
file|<glib-object.h>
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
file|"core/gimpdatafactory.h"
end_include

begin_decl_stmt
DECL|variable|patterns_popup_proc
specifier|static
name|ProcRecord
name|patterns_popup_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_close_popup_proc
specifier|static
name|ProcRecord
name|patterns_close_popup_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_set_popup_proc
specifier|static
name|ProcRecord
name|patterns_set_popup_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_pattern_select_procs (Gimp * gimp)
name|register_pattern_select_procs
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
name|patterns_popup_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|patterns_close_popup_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|patterns_set_popup_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|patterns_popup_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|patterns_popup_invoker
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
name|pattern_callback
decl_stmt|;
name|gchar
modifier|*
name|popup_title
decl_stmt|;
name|gchar
modifier|*
name|initial_pattern
decl_stmt|;
name|pattern_callback
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
name|pattern_callback
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|pattern_callback
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
name|popup_title
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
name|popup_title
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|popup_title
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
name|initial_pattern
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|initial_pattern
operator|&&
operator|!
name|g_utf8_validate
argument_list|(
name|initial_pattern
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
name|no_interface
operator|||
operator|!
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|pattern_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_new
argument_list|(
name|gimp
argument_list|,
name|context
argument_list|,
name|gimp
operator|->
name|pattern_factory
operator|->
name|container
argument_list|,
name|popup_title
argument_list|,
name|pattern_callback
argument_list|,
name|initial_pattern
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|patterns_popup_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|patterns_popup_inargs
specifier|static
name|ProcArg
name|patterns_popup_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"pattern_callback"
block|,
literal|"The callback PDB proc to call when pattern selection is made"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"popup_title"
block|,
literal|"Title to give the pattern popup window"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"initial_pattern"
block|,
literal|"The name of the pattern to set as the first selected"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_popup_proc
specifier|static
name|ProcRecord
name|patterns_popup_proc
init|=
block|{
literal|"gimp_patterns_popup"
block|,
literal|"Invokes the Gimp pattern selection."
block|,
literal|"This procedure popups the pattern selection dialog."
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
literal|3
block|,
name|patterns_popup_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|patterns_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|patterns_close_popup_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|patterns_close_popup_invoker
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
name|pattern_callback
decl_stmt|;
name|pattern_callback
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
name|pattern_callback
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|pattern_callback
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
name|no_interface
operator|||
operator|!
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|pattern_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_close
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|pattern_factory
operator|->
name|container
argument_list|,
name|pattern_callback
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|patterns_close_popup_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|patterns_close_popup_inargs
specifier|static
name|ProcArg
name|patterns_close_popup_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"pattern_callback"
block|,
literal|"The name of the callback registered for this popup"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_close_popup_proc
specifier|static
name|ProcRecord
name|patterns_close_popup_proc
init|=
block|{
literal|"gimp_patterns_close_popup"
block|,
literal|"Popdown the Gimp pattern selection."
block|,
literal|"This procedure closes an opened pattern selection dialog."
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
name|patterns_close_popup_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|patterns_close_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|patterns_set_popup_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|patterns_set_popup_invoker
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
name|pattern_callback
decl_stmt|;
name|gchar
modifier|*
name|pattern_name
decl_stmt|;
name|pattern_callback
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
name|pattern_callback
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|pattern_callback
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
name|pattern_name
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
name|pattern_name
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|pattern_name
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
name|no_interface
operator|||
operator|!
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|pattern_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_set
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|pattern_factory
operator|->
name|container
argument_list|,
name|pattern_callback
argument_list|,
name|pattern_name
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|patterns_set_popup_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|patterns_set_popup_inargs
specifier|static
name|ProcArg
name|patterns_set_popup_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"pattern_callback"
block|,
literal|"The name of the callback registered for this popup"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"pattern_name"
block|,
literal|"The name of the pattern to set as selected"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_set_popup_proc
specifier|static
name|ProcRecord
name|patterns_set_popup_proc
init|=
block|{
literal|"gimp_patterns_set_popup"
block|,
literal|"Sets the current pattern selection in a popup."
block|,
literal|"Sets the current pattern selection in a popup."
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
literal|2
block|,
name|patterns_set_popup_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|patterns_set_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

