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
file|"gimp-intl.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in.h"
end_include

begin_decl_stmt
DECL|variable|message_proc
specifier|static
name|ProcRecord
name|message_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|message_get_handler_proc
specifier|static
name|ProcRecord
name|message_get_handler_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|message_set_handler_proc
specifier|static
name|ProcRecord
name|message_set_handler_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_message_procs (Gimp * gimp)
name|register_message_procs
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
name|message_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|message_get_handler_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|message_set_handler_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|message_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|message_invoker
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
name|message
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
if|if
condition|(
name|message
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|message
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
name|gchar
modifier|*
name|domain
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
condition|)
name|domain
operator|=
name|plug_in_get_undo_desc
argument_list|(
name|gimp
operator|->
name|current_plug_in
argument_list|)
expr_stmt|;
name|gimp_message
argument_list|(
name|gimp
argument_list|,
name|domain
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|domain
argument_list|)
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|message_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|message_inargs
specifier|static
name|ProcArg
name|message_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"message"
block|,
literal|"Message to display in the dialog"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|message_proc
specifier|static
name|ProcRecord
name|message_proc
init|=
block|{
literal|"gimp_message"
block|,
literal|"Displays a dialog box with a message."
block|,
literal|"Displays a dialog box with a message. Useful for status or error reporting. The message must be in UTF-8 encoding."
block|,
literal|"Manish Singh"
block|,
literal|"Manish Singh"
block|,
literal|"1998"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|message_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|message_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|message_get_handler_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|message_get_handler_invoker
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
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|message_get_handler_proc
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
name|gimp
operator|->
name|message_handler
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|message_get_handler_outargs
specifier|static
name|ProcArg
name|message_get_handler_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"handler"
block|,
literal|"The current handler type: { GIMP_MESSAGE_BOX (0), GIMP_CONSOLE (1), GIMP_ERROR_CONSOLE (2) }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|message_get_handler_proc
specifier|static
name|ProcRecord
name|message_get_handler_proc
init|=
block|{
literal|"gimp_message_get_handler"
block|,
literal|"Returns the current state of where warning messages are displayed."
block|,
literal|"This procedure returns the way g_message warnings are displayed. They can be shown in a dialog box or printed on the console where gimp was started."
block|,
literal|"Manish Singh"
block|,
literal|"Manish Singh"
block|,
literal|"1998"
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|1
block|,
name|message_get_handler_outargs
block|,
block|{
block|{
name|message_get_handler_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|message_set_handler_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|message_set_handler_invoker
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
name|gint32
name|handler
decl_stmt|;
name|handler
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|handler
operator|<
name|GIMP_MESSAGE_BOX
operator|||
name|handler
operator|>
name|GIMP_ERROR_CONSOLE
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|gimp
operator|->
name|message_handler
operator|=
name|handler
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|message_set_handler_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|message_set_handler_inargs
specifier|static
name|ProcArg
name|message_set_handler_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"handler"
block|,
literal|"The new handler type: { GIMP_MESSAGE_BOX (0), GIMP_CONSOLE (1), GIMP_ERROR_CONSOLE (2) }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|message_set_handler_proc
specifier|static
name|ProcRecord
name|message_set_handler_proc
init|=
block|{
literal|"gimp_message_set_handler"
block|,
literal|"Controls where warning messages are displayed."
block|,
literal|"This procedure controls how g_message warnings are displayed. They can be shown in a dialog box or printed on the console where gimp was started."
block|,
literal|"Manish Singh"
block|,
literal|"Manish Singh"
block|,
literal|"1998"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|message_set_handler_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|message_set_handler_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

