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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"widgets/widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gui/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"gui/error-console-dialog.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
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
if|if
condition|(
name|console_messages
operator|==
name|FALSE
condition|)
block|{
switch|switch
condition|(
name|message_handler
condition|)
block|{
case|case
name|MESSAGE_BOX
case|:
name|gimp_message_box
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|message
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|ERROR_CONSOLE
case|:
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dock_factory
argument_list|,
literal|"gimp:error-console"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|error_console_add
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|message
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_printerr
argument_list|(
literal|"%s: %s\n"
argument_list|,
name|prog_name
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|message
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"%s: %s\n"
argument_list|,
name|prog_name
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|message
argument_list|)
expr_stmt|;
block|}
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
literal|"%s"
argument_list|,
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
ifndef|#
directive|ifndef
name|G_OS_WIN32
name|g_printerr
argument_list|(
literal|"%s: fatal error: %s\n"
argument_list|,
name|prog_name
argument_list|,
name|message
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|stack_trace_mode
condition|)
block|{
case|case
name|STACK_TRACE_NEVER
case|:
break|break;
case|case
name|STACK_TRACE_QUERY
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
name|prog_name
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|STACK_TRACE_ALWAYS
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
name|prog_name
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
else|#
directive|else
comment|/* g_on_error_* don't do anything reasonable on Win32. */
name|MessageBox
argument_list|(
name|NULL
argument_list|,
name|message
argument_list|,
name|prog_name
argument_list|,
name|MB_OK
operator||
name|MB_ICONERROR
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* ! G_OS_WIN32 */
name|gtk_exit
argument_list|(
literal|1
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
ifndef|#
directive|ifndef
name|G_OS_WIN32
name|g_printerr
argument_list|(
literal|"%s terminated: %s\n"
argument_list|,
name|prog_name
argument_list|,
name|message
argument_list|)
expr_stmt|;
if|if
condition|(
name|use_debug_handler
condition|)
block|{
switch|switch
condition|(
name|stack_trace_mode
condition|)
block|{
case|case
name|STACK_TRACE_NEVER
case|:
break|break;
case|case
name|STACK_TRACE_QUERY
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
name|prog_name
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|STACK_TRACE_ALWAYS
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
name|prog_name
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
name|message
argument_list|,
name|prog_name
argument_list|,
name|MB_OK
operator||
name|MB_ICONERROR
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* ! G_OS_WIN32 */
name|gtk_exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

