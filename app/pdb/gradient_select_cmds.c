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

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_decl_stmt
DECL|variable|gradients_popup_proc
specifier|static
name|ProcRecord
name|gradients_popup_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_close_popup_proc
specifier|static
name|ProcRecord
name|gradients_close_popup_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_set_popup_proc
specifier|static
name|ProcRecord
name|gradients_set_popup_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_gradient_select_procs (Gimp * gimp)
name|register_gradient_select_procs
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
name|gradients_popup_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|gradients_close_popup_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|gradients_set_popup_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gradients_popup_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|gradients_popup_invoker
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
name|gradient_callback
decl_stmt|;
name|gchar
modifier|*
name|popup_title
decl_stmt|;
name|gchar
modifier|*
name|initial_gradient
decl_stmt|;
name|gint32
name|sample_size
decl_stmt|;
name|gradient_callback
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
name|gradient_callback
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|gradient_callback
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
name|initial_gradient
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
name|initial_gradient
operator|&&
operator|!
name|g_utf8_validate
argument_list|(
name|initial_gradient
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
name|sample_size
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|sample_size
operator|<=
literal|0
operator|||
name|sample_size
operator|>
literal|10000
condition|)
name|sample_size
operator|=
name|GIMP_GRADIENT_DEFAULT_SAMPLE_SIZE
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
name|gradient_callback
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
name|gradient_factory
operator|->
name|container
argument_list|,
name|popup_title
argument_list|,
name|gradient_callback
argument_list|,
name|initial_gradient
argument_list|,
literal|"sample-size"
argument_list|,
name|sample_size
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
name|gradients_popup_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gradients_popup_inargs
specifier|static
name|ProcArg
name|gradients_popup_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"gradient_callback"
block|,
literal|"The callback PDB proc to call when gradient selection is made"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"popup_title"
block|,
literal|"Title to give the gradient popup window"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"initial_gradient"
block|,
literal|"The name of the pattern to set as the first selected"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"sample_size"
block|,
literal|"Size of the sample to return when the gradient is changed (0< sample_size<= 10000)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_popup_proc
specifier|static
name|ProcRecord
name|gradients_popup_proc
init|=
block|{
literal|"gimp_gradients_popup"
block|,
literal|"Invokes the Gimp gradients selection."
block|,
literal|"This procedure popups the gradients selection dialog."
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
literal|4
block|,
name|gradients_popup_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|gradients_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gradients_close_popup_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|gradients_close_popup_invoker
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
name|gradient_callback
decl_stmt|;
name|gradient_callback
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
name|gradient_callback
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|gradient_callback
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
name|gradient_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_close
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|gradient_factory
operator|->
name|container
argument_list|,
name|gradient_callback
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
name|gradients_close_popup_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gradients_close_popup_inargs
specifier|static
name|ProcArg
name|gradients_close_popup_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"gradient_callback"
block|,
literal|"The name of the callback registered for this popup"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_close_popup_proc
specifier|static
name|ProcRecord
name|gradients_close_popup_proc
init|=
block|{
literal|"gimp_gradients_close_popup"
block|,
literal|"Popdown the Gimp gradient selection."
block|,
literal|"This procedure closes an opened gradient selection dialog."
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
name|gradients_close_popup_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|gradients_close_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gradients_set_popup_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|gradients_set_popup_invoker
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
name|gradient_callback
decl_stmt|;
name|gchar
modifier|*
name|gradient_name
decl_stmt|;
name|gradient_callback
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
name|gradient_callback
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|gradient_callback
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
name|gradient_name
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
name|gradient_name
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|gradient_name
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
name|gradient_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_set
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|gradient_factory
operator|->
name|container
argument_list|,
name|gradient_callback
argument_list|,
name|gradient_name
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
name|gradients_set_popup_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gradients_set_popup_inargs
specifier|static
name|ProcArg
name|gradients_set_popup_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"gradient_callback"
block|,
literal|"The name of the callback registered for this popup"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"gradient_name"
block|,
literal|"The name of the gradient to set as selected"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_set_popup_proc
specifier|static
name|ProcRecord
name|gradients_set_popup_proc
init|=
block|{
literal|"gimp_gradients_set_popup"
block|,
literal|"Sets the current gradient selection in a popup."
block|,
literal|"Sets the current gradient selection in a popup."
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
name|gradients_set_popup_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|gradients_set_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

