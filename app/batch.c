begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<ctype.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
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

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|NATIVE_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"batch.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|batch_run_cmd
parameter_list|(
name|char
modifier|*
name|cmd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|batch_read
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gint
name|source
parameter_list|,
name|GdkInputCondition
name|condition
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|batch_pserver
parameter_list|(
name|int
name|run_mode
parameter_list|,
name|int
name|flags
parameter_list|,
name|int
name|extra
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|eval_proc
specifier|static
name|ProcRecord
modifier|*
name|eval_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|batch_init ()
name|batch_init
parameter_list|()
block|{
specifier|extern
name|char
modifier|*
modifier|*
name|batch_cmds
decl_stmt|;
name|int
name|read_from_stdin
decl_stmt|;
name|int
name|i
decl_stmt|;
name|int
name|perl_server_already_running
init|=
literal|0
decl_stmt|;
name|eval_proc
operator|=
name|procedural_db_lookup
argument_list|(
literal|"extension_script_fu_eval"
argument_list|)
expr_stmt|;
name|read_from_stdin
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|batch_cmds
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
comment|/* until --batch-interp=xxx or something similar is implemented         * and gimp-1.0 is not extinct use a shortcut to speed up starting the        * perl-server tremendously. This is also fully compatible to 1.0.        */
block|{
name|int
name|run_mode
decl_stmt|,
name|flags
decl_stmt|,
name|extra
decl_stmt|;
if|if
condition|(
name|sscanf
argument_list|(
name|batch_cmds
index|[
name|i
index|]
argument_list|,
literal|"(extension%*[-_]perl%*[-_]server %i %i %i)"
argument_list|,
operator|&
name|run_mode
argument_list|,
operator|&
name|flags
argument_list|,
operator|&
name|extra
argument_list|)
operator|==
literal|3
condition|)
block|{
if|if
condition|(
operator|!
name|perl_server_already_running
condition|)
block|{
name|batch_pserver
argument_list|(
name|run_mode
argument_list|,
name|flags
argument_list|,
name|extra
argument_list|)
expr_stmt|;
name|perl_server_already_running
operator|=
literal|1
expr_stmt|;
block|}
continue|continue;
block|}
block|}
if|if
condition|(
operator|!
name|eval_proc
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"script-fu not available: batch mode disabled\n"
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|strcmp
argument_list|(
name|batch_cmds
index|[
name|i
index|]
argument_list|,
literal|"-"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
operator|!
name|read_from_stdin
condition|)
block|{
ifndef|#
directive|ifndef
name|NATIVE_WIN32
comment|/* for now */
name|g_print
argument_list|(
name|_
argument_list|(
literal|"reading batch commands from stdin\n"
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_input_add
argument_list|(
name|STDIN_FILENO
argument_list|,
name|GDK_INPUT_READ
argument_list|,
name|batch_read
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|read_from_stdin
operator|=
name|TRUE
expr_stmt|;
else|#
directive|else
name|g_error
argument_list|(
literal|"Batch mode from standard input not implemented on Win32"
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
block|}
else|else
block|{
name|batch_run_cmd
argument_list|(
name|batch_cmds
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|batch_run_cmd (char * cmd)
name|batch_run_cmd
parameter_list|(
name|char
modifier|*
name|cmd
parameter_list|)
block|{
name|Argument
modifier|*
name|args
decl_stmt|;
name|Argument
modifier|*
name|vals
decl_stmt|;
name|int
name|i
decl_stmt|;
if|if
condition|(
name|g_strcasecmp
argument_list|(
name|cmd
argument_list|,
literal|"(gimp-quit 0)"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|app_exit
argument_list|(
literal|0
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|0
argument_list|)
expr_stmt|;
block|}
name|args
operator|=
name|g_new0
argument_list|(
name|Argument
argument_list|,
name|eval_proc
operator|->
name|num_args
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|eval_proc
operator|->
name|num_args
condition|;
name|i
operator|++
control|)
name|args
index|[
name|i
index|]
operator|.
name|arg_type
operator|=
name|eval_proc
operator|->
name|args
index|[
name|i
index|]
operator|.
name|arg_type
expr_stmt|;
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
literal|1
expr_stmt|;
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|cmd
expr_stmt|;
name|vals
operator|=
name|procedural_db_execute
argument_list|(
literal|"extension_script_fu_eval"
argument_list|,
name|args
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|vals
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
condition|)
block|{
case|case
name|PDB_EXECUTION_ERROR
case|:
name|g_print
argument_list|(
name|_
argument_list|(
literal|"batch command: experienced an execution error.\n"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PDB_CALLING_ERROR
case|:
name|g_print
argument_list|(
name|_
argument_list|(
literal|"batch command: experienced a calling error.\n"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PDB_SUCCESS
case|:
name|g_print
argument_list|(
name|_
argument_list|(
literal|"batch command: executed successfully.\n"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|procedural_db_destroy_args
argument_list|(
name|vals
argument_list|,
name|eval_proc
operator|->
name|num_values
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|batch_read (gpointer data,gint source,GdkInputCondition condition)
name|batch_read
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gint
name|source
parameter_list|,
name|GdkInputCondition
name|condition
parameter_list|)
block|{
specifier|static
name|GString
modifier|*
name|string
decl_stmt|;
name|char
name|buf
index|[
literal|32
index|]
decl_stmt|,
modifier|*
name|t
decl_stmt|;
name|int
name|nread
decl_stmt|,
name|done
decl_stmt|;
if|if
condition|(
name|condition
operator|&
name|GDK_INPUT_READ
condition|)
block|{
do|do
block|{
name|nread
operator|=
name|read
argument_list|(
name|source
argument_list|,
operator|&
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|char
argument_list|)
operator|*
literal|31
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
operator|(
name|nread
operator|==
operator|-
literal|1
operator|)
operator|&&
operator|(
operator|(
name|errno
operator|==
name|EAGAIN
operator|)
operator|||
operator|(
name|errno
operator|==
name|EINTR
operator|)
operator|)
condition|)
do|;
if|if
condition|(
operator|(
name|nread
operator|==
literal|0
operator|)
operator|&&
operator|(
operator|!
name|string
operator|||
operator|(
name|string
operator|->
name|len
operator|==
literal|0
operator|)
operator|)
condition|)
name|app_exit
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
name|buf
index|[
name|nread
index|]
operator|=
literal|'\0'
expr_stmt|;
if|if
condition|(
operator|!
name|string
condition|)
name|string
operator|=
name|g_string_new
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|t
operator|=
name|buf
expr_stmt|;
if|if
condition|(
name|string
operator|->
name|len
operator|==
literal|0
condition|)
block|{
while|while
condition|(
operator|*
name|t
condition|)
block|{
if|if
condition|(
name|isspace
argument_list|(
operator|*
name|t
argument_list|)
condition|)
name|t
operator|++
expr_stmt|;
else|else
break|break;
block|}
block|}
name|g_string_append
argument_list|(
name|string
argument_list|,
name|t
argument_list|)
expr_stmt|;
name|done
operator|=
name|FALSE
expr_stmt|;
while|while
condition|(
operator|*
name|t
condition|)
block|{
if|if
condition|(
operator|(
operator|*
name|t
operator|==
literal|'\n'
operator|)
operator|||
operator|(
operator|*
name|t
operator|==
literal|'\r'
operator|)
condition|)
name|done
operator|=
name|TRUE
expr_stmt|;
name|t
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|done
condition|)
block|{
name|batch_run_cmd
argument_list|(
name|string
operator|->
name|str
argument_list|)
expr_stmt|;
name|g_string_truncate
argument_list|(
name|string
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|batch_pserver (int run_mode,int flags,int extra)
name|batch_pserver
parameter_list|(
name|int
name|run_mode
parameter_list|,
name|int
name|flags
parameter_list|,
name|int
name|extra
parameter_list|)
block|{
name|ProcRecord
modifier|*
name|pserver_proc
decl_stmt|;
name|Argument
modifier|*
name|args
decl_stmt|;
name|Argument
modifier|*
name|vals
decl_stmt|;
name|int
name|i
decl_stmt|;
name|pserver_proc
operator|=
name|procedural_db_lookup
argument_list|(
literal|"extension_perl_server"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pserver_proc
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"extension_perl_server not available: unable to start the perl server\n"
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|args
operator|=
name|g_new0
argument_list|(
name|Argument
argument_list|,
name|pserver_proc
operator|->
name|num_args
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|pserver_proc
operator|->
name|num_args
condition|;
name|i
operator|++
control|)
name|args
index|[
name|i
index|]
operator|.
name|arg_type
operator|=
name|pserver_proc
operator|->
name|args
index|[
name|i
index|]
operator|.
name|arg_type
expr_stmt|;
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|run_mode
expr_stmt|;
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|flags
expr_stmt|;
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|extra
expr_stmt|;
name|vals
operator|=
name|procedural_db_execute
argument_list|(
literal|"extension_perl_server"
argument_list|,
name|args
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|vals
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
condition|)
block|{
case|case
name|PDB_EXECUTION_ERROR
case|:
name|g_print
argument_list|(
name|_
argument_list|(
literal|"perl server: experienced an execution error.\n"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PDB_CALLING_ERROR
case|:
name|g_print
argument_list|(
name|_
argument_list|(
literal|"perl server: experienced a calling error.\n"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PDB_SUCCESS
case|:
name|g_print
argument_list|(
name|_
argument_list|(
literal|"perl server: executed successfully.\n"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|procedural_db_destroy_args
argument_list|(
name|vals
argument_list|,
name|pserver_proc
operator|->
name|num_values
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return;
block|}
end_function

end_unit

