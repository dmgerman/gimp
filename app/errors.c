begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<stdarg.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
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
DECL|function|gimp_errors_init (const gchar * _full_prog_name,gboolean _use_debug_handler,GimpStackTraceMode _stack_trace_mode)
name|gimp_errors_init
parameter_list|(
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
name|g_return_if_fail
argument_list|(
name|_full_prog_name
operator|!=
name|NULL
argument_list|)
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
block|}
end_function

begin_function
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
modifier|*
name|gimp
init|=
operator|(
name|Gimp
operator|*
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|gimp
operator|&&
name|GIMP_IS_GIMP
argument_list|(
operator|*
name|gimp
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
operator|*
name|gimp
argument_list|,
name|NULL
argument_list|,
name|message
argument_list|)
expr_stmt|;
return|return;
block|}
name|g_printerr
argument_list|(
literal|"%s: %s\n"
argument_list|,
name|full_prog_name
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
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
name|void
DECL|function|gimp_fatal_error (const gchar * fmt,...)
name|gimp_fatal_error
parameter_list|(
specifier|const
name|gchar
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|gchar
modifier|*
name|message
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|fmt
argument_list|)
expr_stmt|;
name|message
operator|=
name|g_strdup_vprintf
argument_list|(
name|fmt
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
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
DECL|function|gimp_terminate (const gchar * fmt,...)
name|gimp_terminate
parameter_list|(
specifier|const
name|gchar
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|gchar
modifier|*
name|message
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|fmt
argument_list|)
expr_stmt|;
name|message
operator|=
name|g_strdup_vprintf
argument_list|(
name|fmt
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
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
ifndef|#
directive|ifndef
name|G_OS_WIN32
name|g_printerr
argument_list|(
literal|"%s: %s: %s\n"
argument_list|,
name|full_prog_name
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

end_unit

