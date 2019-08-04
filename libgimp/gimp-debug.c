begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimp-debug.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|G_OS_WIN32
end_ifndef

begin_include
include|#
directive|include
file|"libgimpbase/gimpsignal.h"
end_include

begin_else
else|#
directive|else
end_else

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_EXCHNDL
end_ifdef

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

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<signal.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
operator|||
name|defined
argument_list|(
name|G_WITH_CYGWIN
argument_list|)
end_if

begin_ifdef
ifdef|#
directive|ifdef
name|STRICT
end_ifdef

begin_undef
undef|#
directive|undef
name|STRICT
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|STRICT
define|#
directive|define
name|STRICT
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|_WIN32_WINNT
end_ifdef

begin_undef
undef|#
directive|undef
name|_WIN32_WINNT
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|_WIN32_WINNT
define|#
directive|define
name|_WIN32_WINNT
value|0x0601
end_define

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_include
include|#
directive|include
file|<tlhelp32.h>
end_include

begin_undef
undef|#
directive|undef
name|RGB
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-debug.h"
end_include

begin_decl_stmt
DECL|variable|gimp_debug_keys
specifier|static
specifier|const
name|GDebugKey
name|gimp_debug_keys
index|[]
init|=
block|{
block|{
literal|"pid"
block|,
name|GIMP_DEBUG_PID
block|}
block|,
block|{
literal|"fatal-warnings"
block|,
name|GIMP_DEBUG_FATAL_WARNINGS
block|}
block|,
block|{
literal|"fw"
block|,
name|GIMP_DEBUG_FATAL_WARNINGS
block|}
block|,
block|{
literal|"query"
block|,
name|GIMP_DEBUG_QUERY
block|}
block|,
block|{
literal|"init"
block|,
name|GIMP_DEBUG_INIT
block|}
block|,
block|{
literal|"run"
block|,
name|GIMP_DEBUG_RUN
block|}
block|,
block|{
literal|"quit"
block|,
name|GIMP_DEBUG_QUIT
block|}
block|,
block|{
literal|"on"
block|,
name|GIMP_DEBUG_DEFAULT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_debug_flags
specifier|static
name|guint
name|gimp_debug_flags
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|_gimp_debug_init (const gchar * basename)
name|_gimp_debug_init
parameter_list|(
specifier|const
name|gchar
modifier|*
name|basename
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|env_string
init|=
name|g_getenv
argument_list|(
literal|"GIMP_PLUGIN_DEBUG"
argument_list|)
decl_stmt|;
if|if
condition|(
name|env_string
condition|)
block|{
name|gchar
modifier|*
name|debug_string
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|debug_messages
decl_stmt|;
name|debug_string
operator|=
name|strchr
argument_list|(
name|env_string
argument_list|,
literal|','
argument_list|)
expr_stmt|;
if|if
condition|(
name|debug_string
condition|)
block|{
name|gint
name|len
init|=
name|debug_string
operator|-
name|env_string
decl_stmt|;
if|if
condition|(
operator|(
name|strlen
argument_list|(
name|basename
argument_list|)
operator|==
name|len
operator|)
operator|&&
operator|(
name|strncmp
argument_list|(
name|basename
argument_list|,
name|env_string
argument_list|,
name|len
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|gimp_debug_flags
operator|=
name|g_parse_debug_string
argument_list|(
name|debug_string
operator|+
literal|1
argument_list|,
name|gimp_debug_keys
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|gimp_debug_keys
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|env_string
argument_list|,
name|basename
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gimp_debug_flags
operator|=
name|GIMP_DEBUG_DEFAULT
expr_stmt|;
block|}
comment|/*  make debug output visible by setting G_MESSAGES_DEBUG  */
name|debug_messages
operator|=
name|g_getenv
argument_list|(
literal|"G_MESSAGES_DEBUG"
argument_list|)
expr_stmt|;
if|if
condition|(
name|debug_messages
condition|)
block|{
name|gchar
modifier|*
name|tmp
init|=
name|g_strconcat
argument_list|(
name|debug_messages
argument_list|,
literal|",LibGimp"
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_setenv
argument_list|(
literal|"G_MESSAGES_DEBUG"
argument_list|,
name|tmp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_setenv
argument_list|(
literal|"G_MESSAGES_DEBUG"
argument_list|,
literal|"LibGimp"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|guint
DECL|function|_gimp_debug_flags (void)
name|_gimp_debug_flags
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|gimp_debug_flags
return|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_debug_stop (void)
name|_gimp_debug_stop
parameter_list|(
name|void
parameter_list|)
block|{
ifndef|#
directive|ifndef
name|G_OS_WIN32
name|g_log
argument_list|(
name|G_LOG_DOMAIN
argument_list|,
name|G_LOG_LEVEL_DEBUG
argument_list|,
literal|"Waiting for debugger..."
argument_list|)
expr_stmt|;
name|raise
argument_list|(
name|SIGSTOP
argument_list|)
expr_stmt|;
else|#
directive|else
name|HANDLE
name|hThreadSnap
init|=
name|NULL
decl_stmt|;
name|THREADENTRY32
name|te32
init|=
block|{
literal|0
block|}
decl_stmt|;
name|pid_t
name|opid
init|=
name|getpid
argument_list|()
decl_stmt|;
name|g_log
argument_list|(
name|G_LOG_DOMAIN
argument_list|,
name|G_LOG_LEVEL_DEBUG
argument_list|,
literal|"Debugging (restart externally): %ld"
argument_list|,
operator|(
name|long
name|int
operator|)
name|opid
argument_list|)
expr_stmt|;
name|hThreadSnap
operator|=
name|CreateToolhelp32Snapshot
argument_list|(
name|TH32CS_SNAPTHREAD
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|hThreadSnap
operator|==
name|INVALID_HANDLE_VALUE
condition|)
block|{
name|g_log
argument_list|(
name|G_LOG_DOMAIN
argument_list|,
name|G_LOG_LEVEL_DEBUG
argument_list|,
literal|"error getting threadsnap - debugging impossible"
argument_list|)
expr_stmt|;
return|return;
block|}
name|te32
operator|.
name|dwSize
operator|=
sizeof|sizeof
argument_list|(
name|THREADENTRY32
argument_list|)
expr_stmt|;
if|if
condition|(
name|Thread32First
argument_list|(
name|hThreadSnap
argument_list|,
operator|&
name|te32
argument_list|)
condition|)
block|{
do|do
block|{
if|if
condition|(
name|te32
operator|.
name|th32OwnerProcessID
operator|==
name|opid
condition|)
block|{
name|HANDLE
name|hThread
init|=
name|OpenThread
argument_list|(
name|THREAD_SUSPEND_RESUME
argument_list|,
name|FALSE
argument_list|,
name|te32
operator|.
name|th32ThreadID
argument_list|)
decl_stmt|;
name|SuspendThread
argument_list|(
name|hThread
argument_list|)
expr_stmt|;
name|CloseHandle
argument_list|(
name|hThread
argument_list|)
expr_stmt|;
block|}
block|}
do|while
condition|(
name|Thread32Next
argument_list|(
name|hThreadSnap
argument_list|,
operator|&
name|te32
argument_list|)
condition|)
do|;
block|}
else|else
block|{
name|g_log
argument_list|(
name|G_LOG_DOMAIN
argument_list|,
name|G_LOG_LEVEL_DEBUG
argument_list|,
literal|"error getting threads"
argument_list|)
expr_stmt|;
block|}
name|CloseHandle
argument_list|(
name|hThreadSnap
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

end_unit
