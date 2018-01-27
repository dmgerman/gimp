begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<signal.h>
end_include

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

begin_include
include|#
directive|include
file|"signals.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_EXCHNDL
end_ifdef

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_include
include|#
directive|include
file|<exchndl.h>
end_include

begin_decl_stmt
DECL|variable|g_prevExceptionFilter
specifier|static
name|LPTOP_LEVEL_EXCEPTION_FILTER
name|g_prevExceptionFilter
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|LONG
name|WINAPI
name|gimp_sigfatal_handler
parameter_list|(
name|PEXCEPTION_POINTERS
name|pExceptionInfo
parameter_list|)
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_decl_stmt
specifier|static
name|void
name|gimp_sigfatal_handler
argument_list|(
name|gint
name|sig_num
argument_list|)
name|G_GNUC_NORETURN
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|void
DECL|function|gimp_init_signal_handlers (gchar ** backtrace_file)
name|gimp_init_signal_handlers
parameter_list|(
name|gchar
modifier|*
modifier|*
name|backtrace_file
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
comment|/* Use Dr. Mingw (dumps backtrace on crash) if it is available. Do    * nothing otherwise on Win32.    * The user won't get any stack trace from glib anyhow.    * Without Dr. MinGW, It's better to let Windows inform about the    * program error, and offer debugging (if the user has installed MSVC    * or some other compiler that knows how to install itself as a    * handler for program errors).    */
ifdef|#
directive|ifdef
name|HAVE_EXCHNDL
name|time_t
name|t
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|dir
decl_stmt|;
comment|/* Order is very important here. We need to add our signal handler    * first, then run ExcHndlInit() which will add its own handler, so    * that ExcHnl's handler runs first since that's in FILO order.    */
if|if
condition|(
operator|!
name|g_prevExceptionFilter
condition|)
name|g_prevExceptionFilter
operator|=
name|SetUnhandledExceptionFilter
argument_list|(
name|gimp_sigfatal_handler
argument_list|)
expr_stmt|;
comment|/* This has to be the non-roaming directory (i.e., the local      directory) as backtraces correspond to the binaries on this      system. */
name|dir
operator|=
name|g_build_filename
argument_list|(
name|g_get_user_data_dir
argument_list|()
argument_list|,
name|GIMPDIR
argument_list|,
name|GIMP_USER_VERSION
argument_list|,
literal|"CrashLog"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Ensure the path exists. */
name|g_mkdir_with_parents
argument_list|(
name|dir
argument_list|,
literal|0700
argument_list|)
expr_stmt|;
name|time
argument_list|(
operator|&
name|t
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-crash-%"
name|G_GUINT64_FORMAT
literal|".txt"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|,
name|t
argument_list|)
expr_stmt|;
operator|*
name|backtrace_file
operator|=
name|g_build_filename
argument_list|(
name|dir
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dir
argument_list|)
expr_stmt|;
name|ExcHndlInit
argument_list|()
expr_stmt|;
name|ExcHndlSetLogFileNameA
argument_list|(
operator|*
name|backtrace_file
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* HAVE_EXCHNDL */
else|#
directive|else
comment|/* Handle fatal signals */
comment|/* these are handled by gimp_terminate() */
name|gimp_signal_private
argument_list|(
name|SIGHUP
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_signal_private
argument_list|(
name|SIGINT
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_signal_private
argument_list|(
name|SIGQUIT
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_signal_private
argument_list|(
name|SIGABRT
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_signal_private
argument_list|(
name|SIGTERM
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* these are handled by gimp_fatal_error() */
name|gimp_signal_private
argument_list|(
name|SIGBUS
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_signal_private
argument_list|(
name|SIGSEGV
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_signal_private
argument_list|(
name|SIGFPE
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* Ignore SIGPIPE because plug_in.c handles broken pipes */
name|gimp_signal_private
argument_list|(
name|SIGPIPE
argument_list|,
name|SIG_IGN
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* Restart syscalls on SIGCHLD */
name|gimp_signal_private
argument_list|(
name|SIGCHLD
argument_list|,
name|SIG_DFL
argument_list|,
name|SA_RESTART
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* G_OS_WIN32 */
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_EXCHNDL
end_ifdef

begin_function
specifier|static
name|LONG
name|WINAPI
DECL|function|gimp_sigfatal_handler (PEXCEPTION_POINTERS pExceptionInfo)
name|gimp_sigfatal_handler
parameter_list|(
name|PEXCEPTION_POINTERS
name|pExceptionInfo
parameter_list|)
block|{
comment|/* Just in case, so that we don't loop or anything similar, just    * re-establish previous handler.    */
name|SetUnhandledExceptionFilter
argument_list|(
name|g_prevExceptionFilter
argument_list|)
expr_stmt|;
comment|/* Now process the exception. */
name|gimp_fatal_error
argument_list|(
literal|"unhandled exception"
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_prevExceptionFilter
operator|&&
name|g_prevExceptionFilter
operator|!=
name|gimp_sigfatal_handler
condition|)
return|return
name|g_prevExceptionFilter
argument_list|(
name|pExceptionInfo
argument_list|)
return|;
else|else
return|return
name|EXCEPTION_CONTINUE_SEARCH
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* gimp core signal handler for fatal signals */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_sigfatal_handler (gint sig_num)
name|gimp_sigfatal_handler
parameter_list|(
name|gint
name|sig_num
parameter_list|)
block|{
switch|switch
condition|(
name|sig_num
condition|)
block|{
case|case
name|SIGHUP
case|:
case|case
name|SIGINT
case|:
case|case
name|SIGQUIT
case|:
case|case
name|SIGABRT
case|:
case|case
name|SIGTERM
case|:
name|gimp_terminate
argument_list|(
name|g_strsignal
argument_list|(
name|sig_num
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|SIGBUS
case|:
case|case
name|SIGSEGV
case|:
case|case
name|SIGFPE
case|:
default|default:
name|gimp_fatal_error
argument_list|(
name|g_strsignal
argument_list|(
name|sig_num
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* G_OS_WIN32 */
end_comment

end_unit

