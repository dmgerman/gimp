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

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
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

begin_decl_stmt
DECL|variable|backtrace_file
specifier|static
name|gchar
modifier|*
name|backtrace_file
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|errors_init (Gimp * gimp,const gchar * _full_prog_name,gboolean _use_debug_handler,GimpStackTraceMode _stack_trace_mode,const gchar * _backtrace_file)
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
parameter_list|,
specifier|const
name|gchar
modifier|*
name|_backtrace_file
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
name|backtrace_file
operator|=
name|g_strdup
argument_list|(
name|_backtrace_file
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
name|G_LOG_LEVEL_WARNING
operator||
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
if|if
condition|(
name|backtrace_file
condition|)
name|g_free
argument_list|(
name|backtrace_file
argument_list|)
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
name|Gimp
modifier|*
name|gimp
init|=
name|data
decl_stmt|;
name|GimpMessageSeverity
name|severity
init|=
name|GIMP_MESSAGE_WARNING
decl_stmt|;
if|if
condition|(
name|flags
operator|&
operator|(
name|G_LOG_LEVEL_CRITICAL
operator||
name|G_LOG_LEVEL_WARNING
operator|)
condition|)
block|{
name|GimpCoreConfig
modifier|*
name|config
init|=
name|gimp
operator|->
name|config
decl_stmt|;
name|GimpDebugPolicy
name|debug_policy
decl_stmt|;
name|g_object_get
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"debug-policy"
argument_list|,
operator|&
name|debug_policy
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|debug_policy
operator|==
name|GIMP_DEBUG_POLICY_CRITICAL
operator|&&
operator|(
name|flags
operator|&
name|G_LOG_LEVEL_CRITICAL
operator|)
operator|)
operator|||
name|debug_policy
operator|==
name|GIMP_DEBUG_POLICY_WARNING
condition|)
block|{
name|severity
operator|=
name|GIMP_MESSAGE_ERROR
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
argument_list|)
expr_stmt|;
block|}
else|else
block|{
specifier|const
name|gchar
modifier|*
name|reason
decl_stmt|;
switch|switch
condition|(
name|flags
operator|&
name|G_LOG_LEVEL_MASK
condition|)
block|{
case|case
name|G_LOG_LEVEL_WARNING
case|:
name|reason
operator|=
literal|"WARNING"
expr_stmt|;
break|break;
case|case
name|G_LOG_LEVEL_CRITICAL
case|:
name|reason
operator|=
literal|"CRITICAL"
expr_stmt|;
break|break;
default|default:
name|reason
operator|=
literal|"MESSAGE"
expr_stmt|;
break|break;
block|}
name|g_printerr
argument_list|(
literal|"%s: %s-%s: %s\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|full_prog_name
argument_list|)
argument_list|,
name|log_domain
argument_list|,
name|reason
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
name|GimpDebugPolicy
name|debug_policy
decl_stmt|;
name|gboolean
name|eek_handled
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
literal|"debug-policy"
argument_list|,
operator|&
name|debug_policy
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Let's just always output on stdout at least so that there is a    * trace if the rest fails. */
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
if|#
directive|if
operator|!
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
operator|||
name|defined
argument_list|(
name|HAVE_EXCHNDL
argument_list|)
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
name|debug_policy
operator|!=
name|GIMP_DEBUG_POLICY_NEVER
operator|&&
operator|!
name|the_errors_gimp
operator|->
name|no_interface
condition|)
block|{
name|FILE
modifier|*
name|fd
decl_stmt|;
name|gboolean
name|has_backtrace
init|=
name|TRUE
decl_stmt|;
comment|/* If GUI backtrace enabled (it is disabled by default), it            * takes precedence over the command line argument.            */
ifdef|#
directive|ifdef
name|G_OS_WIN32
specifier|const
name|gchar
modifier|*
name|gimpdebug
init|=
literal|"gimp-debug-tool-"
name|GIMP_TOOL_VERSION
literal|".exe"
decl_stmt|;
elif|#
directive|elif
name|defined
argument_list|(
name|PLATFORM_OSX
argument_list|)
specifier|const
name|gchar
modifier|*
name|gimpdebug
init|=
literal|"gimp-debug-tool-"
name|GIMP_TOOL_VERSION
decl_stmt|;
else|#
directive|else
specifier|const
name|gchar
modifier|*
name|gimpdebug
init|=
name|LIBEXECDIR
literal|"/gimp-debug-tool-"
name|GIMP_TOOL_VERSION
decl_stmt|;
endif|#
directive|endif
name|gchar
modifier|*
name|args
index|[
literal|7
index|]
init|=
block|{
operator|(
name|gchar
operator|*
operator|)
name|gimpdebug
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
name|backtrace_file
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
ifndef|#
directive|ifndef
name|G_OS_WIN32
comment|/* On Win32, the trace has already been processed by ExcHnl            * and is waiting for us in a text file.            */
name|fd
operator|=
name|g_fopen
argument_list|(
name|backtrace_file
argument_list|,
literal|"w"
argument_list|)
expr_stmt|;
name|has_backtrace
operator|=
name|gimp_print_stack_trace
argument_list|(
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|full_prog_name
argument_list|,
name|fd
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fd
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* We don't care about any return value. If it fails, too            * bad, we just won't have any stack trace.            * We still need to use the sync() variant because we have            * to keep GIMP up long enough for the debugger to get its            * trace.            */
if|if
condition|(
name|has_backtrace
operator|&&
name|g_file_test
argument_list|(
name|backtrace_file
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
operator|&&
name|g_spawn_async
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
argument_list|)
condition|)
name|eek_handled
operator|=
name|TRUE
expr_stmt|;
block|}
endif|#
directive|endif
comment|/* !GIMP_CONSOLE_COMPILATION */
ifndef|#
directive|ifndef
name|G_OS_WIN32
if|if
condition|(
operator|!
name|eek_handled
condition|)
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
name|gimp_on_error_query
argument_list|(
operator|(
specifier|const
name|gchar
operator|*
operator|)
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
name|gimp_print_stack_trace
argument_list|(
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|full_prog_name
argument_list|,
name|stdout
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
block|}
endif|#
directive|endif
comment|/* ! G_OS_WIN32 */
block|}
endif|#
directive|endif
comment|/* ! G_OS_WIN32 || HAVE_EXCHNDL */
if|#
directive|if
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_CONSOLE_COMPILATION
argument_list|)
comment|/* g_on_error_* don't do anything reasonable on Win32. */
if|if
condition|(
operator|!
name|eek_handled
operator|&&
operator|!
name|the_errors_gimp
operator|->
name|no_interface
condition|)
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
name|exit
argument_list|(
name|EXIT_FAILURE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

