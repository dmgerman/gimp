begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/base.h"
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
file|"batch.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|BATCH_DEFAULT_EVAL_PROC
define|#
directive|define
name|BATCH_DEFAULT_EVAL_PROC
value|"plug-in-script-fu-eval"
end_define

begin_function_decl
specifier|static
name|gboolean
name|batch_exit_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|kill_it
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|batch_run_cmd
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
specifier|const
name|gchar
modifier|*
name|cmd
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|batch_run (Gimp * gimp,const gchar * batch_interpreter,const gchar ** batch_commands)
name|batch_run
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|batch_interpreter
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|batch_commands
parameter_list|)
block|{
name|gulong
name|exit_id
decl_stmt|;
if|if
condition|(
operator|!
name|batch_commands
operator|||
operator|!
name|batch_commands
index|[
literal|0
index|]
condition|)
return|return;
name|exit_id
operator|=
name|g_signal_connect_after
argument_list|(
name|gimp
argument_list|,
literal|"exit"
argument_list|,
name|G_CALLBACK
argument_list|(
name|batch_exit_after_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|batch_interpreter
condition|)
block|{
name|batch_interpreter
operator|=
name|g_getenv
argument_list|(
literal|"GIMP_BATCH_INTERPRETER"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|batch_interpreter
condition|)
block|{
name|batch_interpreter
operator|=
name|BATCH_DEFAULT_EVAL_PROC
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_printerr
argument_list|(
name|_
argument_list|(
literal|"No batch interpreter specified, using the default "
literal|"'%s'.\n"
argument_list|)
argument_list|,
name|batch_interpreter
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  script-fu text console, hardcoded for backward compatibility  */
if|if
condition|(
name|strcmp
argument_list|(
name|batch_interpreter
argument_list|,
literal|"plug-in-script-fu-eval"
argument_list|)
operator|==
literal|0
operator|&&
name|strcmp
argument_list|(
name|batch_commands
index|[
literal|0
index|]
argument_list|,
literal|"-"
argument_list|)
operator|==
literal|0
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|proc_name
init|=
literal|"plug-in-script-fu-text-console"
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
init|=
name|gimp_pdb_lookup_procedure
argument_list|(
name|gimp
operator|->
name|pdb
argument_list|,
name|proc_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|procedure
condition|)
name|batch_run_cmd
argument_list|(
name|gimp
argument_list|,
name|proc_name
argument_list|,
name|procedure
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|g_message
argument_list|(
name|_
argument_list|(
literal|"The batch interpreter '%s' is not available. "
literal|"Batch mode disabled."
argument_list|)
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpProcedure
modifier|*
name|eval_proc
init|=
name|gimp_pdb_lookup_procedure
argument_list|(
name|gimp
operator|->
name|pdb
argument_list|,
name|batch_interpreter
argument_list|)
decl_stmt|;
if|if
condition|(
name|eval_proc
condition|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|batch_commands
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
name|batch_run_cmd
argument_list|(
name|gimp
argument_list|,
name|batch_interpreter
argument_list|,
name|eval_proc
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|batch_commands
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"The batch interpreter '%s' is not available. "
literal|"Batch mode disabled."
argument_list|)
argument_list|,
name|batch_interpreter
argument_list|)
expr_stmt|;
block|}
block|}
name|g_signal_handler_disconnect
argument_list|(
name|gimp
argument_list|,
name|exit_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|batch_exit_after_callback (Gimp * gimp,gboolean kill_it)
name|batch_exit_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|kill_it
parameter_list|)
block|{
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"EXIT: %s\n"
argument_list|,
name|G_STRLOC
argument_list|)
expr_stmt|;
comment|/*  make sure that the swap file is removed before we quit */
name|base_exit
argument_list|()
expr_stmt|;
name|exit
argument_list|(
name|EXIT_SUCCESS
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|batch_run_cmd (Gimp * gimp,const gchar * proc_name,GimpProcedure * procedure,GimpRunMode run_mode,const gchar * cmd)
name|batch_run_cmd
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
specifier|const
name|gchar
modifier|*
name|cmd
parameter_list|)
block|{
name|GValueArray
modifier|*
name|args
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
name|args
operator|=
name|gimp_procedure_get_arguments
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
operator|->
name|num_args
operator|>
name|i
operator|&&
name|GIMP_IS_PARAM_SPEC_INT32
argument_list|(
name|procedure
operator|->
name|args
index|[
name|i
index|]
argument_list|)
condition|)
name|g_value_set_int
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
name|i
operator|++
index|]
argument_list|,
name|run_mode
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
operator|->
name|num_args
operator|>
name|i
operator|&&
name|GIMP_IS_PARAM_SPEC_STRING
argument_list|(
name|procedure
operator|->
name|args
index|[
name|i
index|]
argument_list|)
condition|)
name|g_value_set_static_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
name|i
operator|++
index|]
argument_list|,
name|cmd
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_execute_procedure_by_name_args
argument_list|(
name|gimp
operator|->
name|pdb
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|,
name|proc_name
argument_list|,
name|args
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|g_value_get_enum
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
condition|)
block|{
case|case
name|GIMP_PDB_EXECUTION_ERROR
case|:
if|if
condition|(
name|error
condition|)
block|{
name|g_printerr
argument_list|(
literal|"batch command experienced an execution error: %s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"batch command experienced an execution error\n"
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_CALLING_ERROR
case|:
if|if
condition|(
name|error
condition|)
block|{
name|g_printerr
argument_list|(
literal|"batch command experienced a calling error: %s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"batch command experienced a calling error\n"
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PDB_SUCCESS
case|:
name|g_printerr
argument_list|(
literal|"batch command executed successfully\n"
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_value_array_free
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
name|g_value_array_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
return|return;
block|}
end_function

end_unit

