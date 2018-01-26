begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_define
DECL|macro|_GNU_SOURCE
define|#
directive|define
name|_GNU_SOURCE
end_define

begin_comment
DECL|macro|_GNU_SOURCE
comment|/* need the POSIX signal API */
end_comment

begin_include
include|#
directive|include
file|<signal.h>
end_include

begin_include
include|#
directive|include
file|<stdarg.h>
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

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/wait.h>
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

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|MAX_TRACES
define|#
directive|define
name|MAX_TRACES
value|3
end_define

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|the_errors_gimp
specifier|static
name|Gimp
modifier|*
name|the_errors_gimp
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|use_debug_handler
specifier|static
name|gboolean
name|use_debug_handler
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|stack_trace_mode
specifier|static
name|GimpStackTraceMode
name|stack_trace_mode
init|=
name|GIMP_STACK_TRACE_QUERY
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|full_prog_name
specifier|static
name|gchar
modifier|*
name|full_prog_name
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_third_party_message_log_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|log_domain
parameter_list|,
name|GLogLevelFlags
name|flags
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_message_log_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|log_domain
parameter_list|,
name|GLogLevelFlags
name|flags
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|static
name|void
name|gimp_error_log_func
argument_list|(
specifier|const
name|gchar
operator|*
name|domain
argument_list|,
name|GLogLevelFlags
name|flags
argument_list|,
specifier|const
name|gchar
operator|*
name|message
argument_list|,
name|gpointer
name|data
argument_list|)
name|G_GNUC_NORETURN
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|G_GNUC_NORETURN
name|void
name|gimp_eek
parameter_list|(
specifier|const
name|gchar
modifier|*
name|reason
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|use_handler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_get_stack_trace
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|errors_init (Gimp * gimp,const gchar * _full_prog_name,gboolean _use_debug_handler,GimpStackTraceMode _stack_trace_mode)
name|errors_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|_full_prog_name
parameter_list|,
name|gboolean
name|_use_debug_handler
parameter_list|,
name|GimpStackTraceMode
name|_stack_trace_mode
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
specifier|const
name|log_domains
index|[]
init|=
block|{
literal|"Gimp"
block|,
literal|"Gimp-Actions"
block|,
literal|"Gimp-Base"
block|,
literal|"Gimp-Composite"
block|,
literal|"Gimp-Config"
block|,
literal|"Gimp-Core"
block|,
literal|"Gimp-Dialogs"
block|,
literal|"Gimp-Display"
block|,
literal|"Gimp-File"
block|,
literal|"Gimp-GEGL"
block|,
literal|"Gimp-GUI"
block|,
literal|"Gimp-Menus"
block|,
literal|"Gimp-Operations"
block|,
literal|"Gimp-PDB"
block|,
literal|"Gimp-Paint"
block|,
literal|"Gimp-Paint-Funcs"
block|,
literal|"Gimp-Plug-In"
block|,
literal|"Gimp-Text"
block|,
literal|"Gimp-Tools"
block|,
literal|"Gimp-Vectors"
block|,
literal|"Gimp-Widgets"
block|,
literal|"Gimp-XCF"
block|,
literal|"LibGimpBase"
block|,
literal|"LibGimpColor"
block|,
literal|"LibGimpConfig"
block|,
literal|"LibGimpMath"
block|,
literal|"LibGimpModule"
block|,
literal|"LibGimpThumb"
block|,
literal|"LibGimpWidgets"
block|}
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|_full_prog_name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|full_prog_name
operator|==
name|NULL
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
name|g_printerr
argument_list|(
literal|"This is a development version of GIMP.  "
literal|"Debug messages may appear here.\n\n"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* GIMP_UNSTABLE */
name|the_errors_gimp
operator|=
name|gimp
expr_stmt|;
name|use_debug_handler
operator|=
name|_use_debug_handler
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|stack_trace_mode
operator|=
name|_stack_trace_mode
expr_stmt|;
name|full_prog_name
operator|=
name|g_strdup
argument_list|(
name|_full_prog_name
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
name|G_N_ELEMENTS
argument_list|(
name|log_domains
argument_list|)
condition|;
name|i
operator|++
control|)
name|g_log_set_handler
argument_list|(
name|log_domains
index|[
name|i
index|]
argument_list|,
name|G_LOG_LEVEL_MESSAGE
operator||
name|G_LOG_LEVEL_CRITICAL
argument_list|,
name|gimp_message_log_func
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"GEGL"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_third_party_message_log_func
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
name|NULL
argument_list|,
name|G_LOG_LEVEL_ERROR
operator||
name|G_LOG_FLAG_FATAL
argument_list|,
name|gimp_error_log_func
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|errors_exit (void)
name|errors_exit
parameter_list|(
name|void
parameter_list|)
block|{
name|the_errors_gimp
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_fatal_error (const gchar * message)
name|gimp_fatal_error
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|gimp_eek
argument_list|(
literal|"fatal error"
argument_list|,
name|message
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_terminate (const gchar * message)
name|gimp_terminate
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|gimp_eek
argument_list|(
literal|"terminated"
argument_list|,
name|message
argument_list|,
name|use_debug_handler
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_third_party_message_log_func (const gchar * log_domain,GLogLevelFlags flags,const gchar * message,gpointer data)
name|gimp_third_party_message_log_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|log_domain
parameter_list|,
name|GLogLevelFlags
name|flags
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|data
decl_stmt|;
if|if
condition|(
name|gimp
condition|)
block|{
comment|/* Whereas all GIMP messages are processed under the same domain,        * we need to keep the log domain information for third party        * messages.        */
name|gimp_show_message
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_WARNING
argument_list|,
name|log_domain
argument_list|,
name|message
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"%s: %s\n\n"
argument_list|,
name|log_domain
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_message_log_func (const gchar * log_domain,GLogLevelFlags flags,const gchar * message,gpointer data)
name|gimp_message_log_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|log_domain
parameter_list|,
name|GLogLevelFlags
name|flags
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
specifier|static
name|gint
name|n_traces
decl_stmt|;
name|GimpMessageSeverity
name|severity
init|=
name|GIMP_MESSAGE_WARNING
decl_stmt|;
name|Gimp
modifier|*
name|gimp
init|=
name|data
decl_stmt|;
name|gchar
modifier|*
name|trace
init|=
name|NULL
decl_stmt|;
name|GimpCoreConfig
modifier|*
name|config
init|=
name|gimp
operator|->
name|config
decl_stmt|;
name|gboolean
name|generate_backtrace
init|=
name|FALSE
decl_stmt|;
name|g_object_get
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"generate-backtrace"
argument_list|,
operator|&
name|generate_backtrace
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|generate_backtrace
operator|&&
operator|(
name|flags
operator|&
name|G_LOG_LEVEL_CRITICAL
operator|)
condition|)
block|{
name|severity
operator|=
name|GIMP_MESSAGE_ERROR
expr_stmt|;
if|if
condition|(
name|n_traces
operator|<
name|MAX_TRACES
condition|)
block|{
comment|/* Getting debug traces is time-expensive, and worse, some            * critical errors have the bad habit to create more errors            * (the first ones are therefore usually the most useful).            * This is why we keep track of how many times we made traces            * and stop doing them after a while.            * Hence when this happens, critical errors are simply processed as            * lower level errors.            */
name|trace
operator|=
name|gimp_get_stack_trace
argument_list|()
expr_stmt|;
name|n_traces
operator|++
expr_stmt|;
block|}
block|}
if|if
condition|(
name|gimp
condition|)
block|{
name|gimp_show_message
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|severity
argument_list|,
name|NULL
argument_list|,
name|message
argument_list|,
name|trace
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"%s: %s\n\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|full_prog_name
argument_list|)
argument_list|,
name|message
argument_list|)
expr_stmt|;
if|if
condition|(
name|trace
condition|)
name|g_printerr
argument_list|(
literal|"Back trace:\n%s\n\n"
argument_list|,
name|trace
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|trace
condition|)
name|g_free
argument_list|(
name|trace
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_error_log_func (const gchar * domain,GLogLevelFlags flags,const gchar * message,gpointer data)
name|gimp_error_log_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
name|GLogLevelFlags
name|flags
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_fatal_error
argument_list|(
name|message
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_eek (const gchar * reason,const gchar * message,gboolean use_handler)
name|gimp_eek
parameter_list|(
specifier|const
name|gchar
modifier|*
name|reason
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|use_handler
parameter_list|)
block|{
name|GimpCoreConfig
modifier|*
name|config
init|=
name|the_errors_gimp
operator|->
name|config
decl_stmt|;
name|gboolean
name|generate_backtrace
init|=
name|FALSE
decl_stmt|;
comment|/* GIMP has 2 ways to handle termination signals and fatal errors: one    * is the stack trace mode which is set at start as command line    * option --stack-trace-mode, this won't change for the length of the    * session and outputs a trace in terminal; the other is set in    * preferences, outputs a trace in a GUI and can change anytime during    * the session.    * The GUI backtrace has priority if it is set.    */
name|g_object_get
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"generate-backtrace"
argument_list|,
operator|&
name|generate_backtrace
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
ifndef|#
directive|ifndef
name|G_OS_WIN32
name|g_printerr
argument_list|(
literal|"%s: %s: %s\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|full_prog_name
argument_list|)
argument_list|,
name|reason
argument_list|,
name|message
argument_list|)
expr_stmt|;
if|if
condition|(
name|use_handler
condition|)
block|{
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
if|if
condition|(
name|generate_backtrace
operator|&&
operator|!
name|the_errors_gimp
operator|->
name|no_interface
condition|)
block|{
comment|/* If enabled (it is disabled by default), the GUI preference            * takes precedence over the command line argument.            */
name|gchar
modifier|*
name|args
index|[
literal|6
index|]
init|=
block|{
literal|"gimpdebug-2.0"
block|,
name|full_prog_name
block|,
name|NULL
block|,
operator|(
name|gchar
operator|*
operator|)
name|reason
block|,
operator|(
name|gchar
operator|*
operator|)
name|message
block|,
name|NULL
block|}
decl_stmt|;
name|gchar
name|pid
index|[
literal|16
index|]
decl_stmt|;
name|gint
name|exit_status
decl_stmt|;
name|g_snprintf
argument_list|(
name|pid
argument_list|,
literal|16
argument_list|,
literal|"%u"
argument_list|,
operator|(
name|guint
operator|)
name|getpid
argument_list|()
argument_list|)
expr_stmt|;
name|args
index|[
literal|2
index|]
operator|=
name|pid
expr_stmt|;
comment|/* We don't care about any return value. If it fails, too            * bad, we just won't have any stack trace.            * We still need to use the sync() variant because we have            * to keep GIMP up long enough for the debugger to get its            * trace.            */
name|g_spawn_sync
argument_list|(
name|NULL
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|,
name|G_SPAWN_SEARCH_PATH
operator||
name|G_SPAWN_STDERR_TO_DEV_NULL
operator||
name|G_SPAWN_STDOUT_TO_DEV_NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|exit_status
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
endif|#
directive|endif
block|{
switch|switch
condition|(
name|stack_trace_mode
condition|)
block|{
case|case
name|GIMP_STACK_TRACE_NEVER
case|:
break|break;
case|case
name|GIMP_STACK_TRACE_QUERY
case|:
block|{
name|sigset_t
name|sigset
decl_stmt|;
name|sigemptyset
argument_list|(
operator|&
name|sigset
argument_list|)
expr_stmt|;
name|sigprocmask
argument_list|(
name|SIG_SETMASK
argument_list|,
operator|&
name|sigset
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|the_errors_gimp
condition|)
name|gimp_gui_ungrab
argument_list|(
name|the_errors_gimp
argument_list|)
expr_stmt|;
name|g_on_error_query
argument_list|(
name|full_prog_name
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_STACK_TRACE_ALWAYS
case|:
block|{
name|sigset_t
name|sigset
decl_stmt|;
name|sigemptyset
argument_list|(
operator|&
name|sigset
argument_list|)
expr_stmt|;
name|sigprocmask
argument_list|(
name|SIG_SETMASK
argument_list|,
operator|&
name|sigset
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_on_error_stack_trace
argument_list|(
name|full_prog_name
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
block|}
block|}
else|#
directive|else
comment|/* g_on_error_* don't do anything reasonable on Win32. */
name|MessageBox
argument_list|(
name|NULL
argument_list|,
name|g_strdup_printf
argument_list|(
literal|"%s: %s"
argument_list|,
name|reason
argument_list|,
name|message
argument_list|)
argument_list|,
name|full_prog_name
argument_list|,
name|MB_OK
operator||
name|MB_ICONERROR
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* ! G_OS_WIN32 */
name|exit
argument_list|(
name|EXIT_FAILURE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_get_stack_trace (void)
name|gimp_get_stack_trace
parameter_list|(
name|void
parameter_list|)
block|{
name|gchar
modifier|*
name|trace
init|=
name|NULL
decl_stmt|;
ifndef|#
directive|ifndef
name|G_OS_WIN32
name|gchar
modifier|*
name|args
index|[
literal|7
index|]
init|=
block|{
literal|"gdb"
block|,
literal|"-batch"
block|,
literal|"-ex"
block|,
literal|"backtrace full"
block|,
name|full_prog_name
block|,
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
name|gchar
modifier|*
name|gdb_stdout
decl_stmt|;
name|gchar
name|pid
index|[
literal|16
index|]
decl_stmt|;
endif|#
directive|endif
comment|/* Though we should theoretically ask with GIMP_STACK_TRACE_QUERY, we    * just assume yes right now. TODO: improve this!    */
if|if
condition|(
name|stack_trace_mode
operator|==
name|GIMP_STACK_TRACE_NEVER
condition|)
return|return
name|NULL
return|;
comment|/* This works only on UNIX systems. On Windows, we'll have to find    * another method, probably with DrMingW.    */
ifndef|#
directive|ifndef
name|G_OS_WIN32
name|g_snprintf
argument_list|(
name|pid
argument_list|,
literal|16
argument_list|,
literal|"%u"
argument_list|,
operator|(
name|guint
operator|)
name|getpid
argument_list|()
argument_list|)
expr_stmt|;
name|args
index|[
literal|5
index|]
operator|=
name|pid
expr_stmt|;
if|if
condition|(
name|g_spawn_sync
argument_list|(
name|NULL
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|,
name|G_SPAWN_SEARCH_PATH
operator||
name|G_SPAWN_STDERR_TO_DEV_NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|gdb_stdout
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|trace
operator|=
name|g_strdup
argument_list|(
name|gdb_stdout
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gdb_stdout
condition|)
block|{
name|g_free
argument_list|(
name|gdb_stdout
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
return|return
name|trace
return|;
block|}
end_function

end_unit

