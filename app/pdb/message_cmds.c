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
file|"gimpargument.h"
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
file|"plug-in/plug-in-progress.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in.h"
end_include

begin_decl_stmt
DECL|variable|message_proc
specifier|static
name|GimpProcedure
name|message_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|message_get_handler_proc
specifier|static
name|GimpProcedure
name|message_get_handler_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|message_set_handler_proc
specifier|static
name|GimpProcedure
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
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
comment|/*    * message    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|message_proc
argument_list|,
literal|1
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
literal|"message"
argument_list|,
literal|"message"
argument_list|,
literal|"Message to display in the dialog"
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
comment|/*    * message_get_handler    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|message_get_handler_proc
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
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"handler"
argument_list|,
literal|"handler"
argument_list|,
literal|"The current handler type: { GIMP_MESSAGE_BOX (0), GIMP_CONSOLE (1), GIMP_ERROR_CONSOLE (2) }"
argument_list|,
name|GIMP_TYPE_MESSAGE_HANDLER_TYPE
argument_list|,
name|GIMP_MESSAGE_BOX
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
comment|/*    * message_set_handler    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|message_set_handler_proc
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"handler"
argument_list|,
literal|"handler"
argument_list|,
literal|"The new handler type: { GIMP_MESSAGE_BOX (0), GIMP_CONSOLE (1), GIMP_ERROR_CONSOLE (2) }"
argument_list|,
name|GIMP_TYPE_MESSAGE_HANDLER_TYPE
argument_list|,
name|GIMP_MESSAGE_BOX
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
DECL|function|message_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|message_invoker
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
name|gimp
operator|->
name|current_plug_in
condition|)
name|plug_in_progress_message
argument_list|(
name|gimp
operator|->
name|current_plug_in
argument_list|,
name|message
argument_list|)
expr_stmt|;
else|else
name|gimp_message
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|message
argument_list|)
expr_stmt|;
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

begin_decl_stmt
DECL|variable|message_proc
specifier|static
name|GimpProcedure
name|message_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-message"
block|,
literal|"gimp-message"
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
DECL|function|message_get_handler_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|message_get_handler_invoker
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gint32
name|handler
init|=
literal|0
decl_stmt|;
name|handler
operator|=
name|gimp
operator|->
name|message_handler
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
name|g_value_set_enum
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|handler
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|message_get_handler_proc
specifier|static
name|GimpProcedure
name|message_get_handler_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-message-get-handler"
block|,
literal|"gimp-message-get-handler"
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
DECL|function|message_set_handler_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|message_set_handler_invoker
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
name|g_value_get_enum
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
name|gimp
operator|->
name|message_handler
operator|=
name|handler
expr_stmt|;
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

begin_decl_stmt
DECL|variable|message_set_handler_proc
specifier|static
name|GimpProcedure
name|message_set_handler_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-message-set-handler"
block|,
literal|"gimp-message-set-handler"
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
name|message_set_handler_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

