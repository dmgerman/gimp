begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpbacktrace-windows.c  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|"gimpbacktrace-backend.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|GIMP_BACKTRACE_BACKEND_WINDOWS
end_ifdef

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_include
include|#
directive|include
file|<psapi.h>
end_include

begin_include
include|#
directive|include
file|<tlhelp32.h>
end_include

begin_include
include|#
directive|include
file|<dbghelp.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpbacktrace.h"
end_include

begin_define
DECL|macro|MAX_N_THREADS
define|#
directive|define
name|MAX_N_THREADS
value|256
end_define

begin_define
DECL|macro|MAX_N_FRAMES
define|#
directive|define
name|MAX_N_FRAMES
value|256
end_define

begin_define
DECL|macro|THREAD_ENUMERATION_INTERVAL
define|#
directive|define
name|THREAD_ENUMERATION_INTERVAL
value|G_TIME_SPAN_SECOND
end_define

begin_typedef
DECL|typedef|Thread
typedef|typedef
name|struct
name|_Thread
name|Thread
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBacktraceThread
typedef|typedef
name|struct
name|_GimpBacktraceThread
name|GimpBacktraceThread
typedef|;
end_typedef

begin_struct
DECL|struct|_Thread
struct|struct
name|_Thread
block|{
DECL|member|tid
name|DWORD
name|tid
decl_stmt|;
union|union
DECL|union|__anon29e313fe010a
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|time
name|guint64
name|time
decl_stmt|;
block|}
union|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBacktraceThread
struct|struct
name|_GimpBacktraceThread
block|{
DECL|member|tid
name|DWORD
name|tid
decl_stmt|;
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|time
name|guint64
name|time
decl_stmt|;
DECL|member|last_time
name|guint64
name|last_time
decl_stmt|;
DECL|member|frames
name|guintptr
name|frames
index|[
name|MAX_N_FRAMES
index|]
decl_stmt|;
DECL|member|n_frames
name|gint
name|n_frames
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBacktrace
struct|struct
name|_GimpBacktrace
block|{
DECL|member|threads
name|GimpBacktraceThread
modifier|*
name|threads
decl_stmt|;
DECL|member|n_threads
name|gint
name|n_threads
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
specifier|inline
name|gint
name|gimp_backtrace_normalize_frame
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|,
name|gint
name|thread
parameter_list|,
name|gint
name|frame
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_backtrace_enumerate_threads
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|LONG
name|gimp_backtrace_exception_handler
parameter_list|(
name|PEXCEPTION_POINTERS
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  static variables  */
end_comment

begin_decl_stmt
DECL|variable|mutex
specifier|static
name|GMutex
name|mutex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|n_initializations
specifier|static
name|gint
name|n_initializations
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|initialized
specifier|static
name|gboolean
name|initialized
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|threads
name|Thread
name|threads
index|[
name|MAX_N_THREADS
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|n_threads
name|gint
name|n_threads
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|last_thread_enumeration_time
name|gint64
name|last_thread_enumeration_time
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|thread_names
name|Thread
name|thread_names
index|[
name|MAX_N_THREADS
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|n_thread_names
name|gint
name|n_thread_names
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|thread_names_spinlock
name|gint
name|thread_names_spinlock
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|thread_times
name|Thread
name|thread_times
index|[
name|MAX_N_THREADS
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|n_thread_times
name|gint
name|n_thread_times
decl_stmt|;
end_decl_stmt

begin_function_decl
DECL|variable|gimp_backtrace_SymSetOptions
name|DWORD
name|WINAPI
function_decl|(
modifier|*
name|gimp_backtrace_SymSetOptions
function_decl|)
parameter_list|(
name|DWORD
name|SymOptions
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
DECL|variable|gimp_backtrace_SymInitialize
name|BOOL
name|WINAPI
function_decl|(
modifier|*
name|gimp_backtrace_SymInitialize
function_decl|)
parameter_list|(
name|HANDLE
name|hProcess
parameter_list|,
name|PCSTR
name|UserSearchPath
parameter_list|,
name|BOOL
name|fInvadeProcess
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
DECL|variable|gimp_backtrace_SymCleanup
name|BOOL
name|WINAPI
function_decl|(
modifier|*
name|gimp_backtrace_SymCleanup
function_decl|)
parameter_list|(
name|HANDLE
name|hProcess
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
DECL|variable|gimp_backtrace_SymFromAddr
name|BOOL
name|WINAPI
function_decl|(
modifier|*
name|gimp_backtrace_SymFromAddr
function_decl|)
parameter_list|(
name|HANDLE
name|hProcess
parameter_list|,
name|DWORD64
name|Address
parameter_list|,
name|PDWORD64
name|Displacement
parameter_list|,
name|PSYMBOL_INFO
name|Symbol
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
DECL|variable|gimp_backtrace_SymGetLineFromAddr64
name|BOOL
name|WINAPI
function_decl|(
modifier|*
name|gimp_backtrace_SymGetLineFromAddr64
function_decl|)
parameter_list|(
name|HANDLE
name|hProcess
parameter_list|,
name|DWORD64
name|qwAddr
parameter_list|,
name|PDWORD
name|pdwDisplacement
parameter_list|,
name|PIMAGEHLP_LINE64
name|Line64
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
specifier|inline
name|gint
DECL|function|gimp_backtrace_normalize_frame (GimpBacktrace * backtrace,gint thread,gint frame)
name|gimp_backtrace_normalize_frame
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|,
name|gint
name|thread
parameter_list|,
name|gint
name|frame
parameter_list|)
block|{
if|if
condition|(
name|frame
operator|>=
literal|0
condition|)
return|return
name|frame
return|;
else|else
return|return
name|backtrace
operator|->
name|threads
index|[
name|thread
index|]
operator|.
name|n_frames
operator|+
name|frame
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_backtrace_enumerate_threads (void)
name|gimp_backtrace_enumerate_threads
parameter_list|(
name|void
parameter_list|)
block|{
name|HANDLE
name|hThreadSnap
decl_stmt|;
name|THREADENTRY32
name|te32
decl_stmt|;
name|DWORD
name|pid
decl_stmt|;
name|gint64
name|time
decl_stmt|;
name|time
operator|=
name|g_get_monotonic_time
argument_list|()
expr_stmt|;
if|if
condition|(
name|time
operator|-
name|last_thread_enumeration_time
operator|<
name|THREAD_ENUMERATION_INTERVAL
condition|)
return|return
name|n_threads
operator|>
literal|0
return|;
name|last_thread_enumeration_time
operator|=
name|time
expr_stmt|;
name|n_threads
operator|=
literal|0
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
return|return
name|FALSE
return|;
name|te32
operator|.
name|dwSize
operator|=
sizeof|sizeof
argument_list|(
name|te32
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|Thread32First
argument_list|(
name|hThreadSnap
argument_list|,
operator|&
name|te32
argument_list|)
condition|)
block|{
name|CloseHandle
argument_list|(
name|hThreadSnap
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|pid
operator|=
name|GetCurrentProcessId
argument_list|()
expr_stmt|;
while|while
condition|(
operator|!
name|g_atomic_int_compare_and_exchange
argument_list|(
operator|&
name|thread_names_spinlock
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
condition|)
empty_stmt|;
do|do
block|{
if|if
condition|(
name|n_threads
operator|==
name|MAX_N_THREADS
condition|)
break|break;
if|if
condition|(
name|te32
operator|.
name|th32OwnerProcessID
operator|==
name|pid
condition|)
block|{
name|Thread
modifier|*
name|thread
init|=
operator|&
name|threads
index|[
name|n_threads
operator|++
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|thread
operator|->
name|tid
operator|=
name|te32
operator|.
name|th32ThreadID
expr_stmt|;
name|thread
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|i
operator|=
name|n_thread_names
operator|-
literal|1
init|;
name|i
operator|>=
literal|0
condition|;
name|i
operator|--
control|)
block|{
if|if
condition|(
name|thread
operator|->
name|tid
operator|==
name|thread_names
index|[
name|i
index|]
operator|.
name|tid
condition|)
block|{
name|thread
operator|->
name|name
operator|=
name|thread_names
index|[
name|i
index|]
operator|.
name|name
expr_stmt|;
break|break;
block|}
block|}
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
name|g_atomic_int_set
argument_list|(
operator|&
name|thread_names_spinlock
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|CloseHandle
argument_list|(
name|hThreadSnap
argument_list|)
expr_stmt|;
return|return
name|n_threads
operator|>
literal|0
return|;
block|}
end_function

begin_function
specifier|static
name|LONG
DECL|function|gimp_backtrace_exception_handler (PEXCEPTION_POINTERS info)
name|gimp_backtrace_exception_handler
parameter_list|(
name|PEXCEPTION_POINTERS
name|info
parameter_list|)
block|{
DECL|macro|EXCEPTION_SET_THREAD_NAME
define|#
directive|define
name|EXCEPTION_SET_THREAD_NAME
value|((DWORD) 0x406D1388)
DECL|struct|_THREADNAME_INFO
typedef|typedef
struct|struct
name|_THREADNAME_INFO
block|{
DECL|member|dwType
name|DWORD
name|dwType
decl_stmt|;
comment|/* must be 0x1000                        */
DECL|member|szName
name|LPCSTR
name|szName
decl_stmt|;
comment|/* pointer to name (in user addr space)  */
DECL|member|dwThreadID
name|DWORD
name|dwThreadID
decl_stmt|;
comment|/* thread ID (-1=caller thread)          */
DECL|member|dwFlags
name|DWORD
name|dwFlags
decl_stmt|;
comment|/* reserved for future use, must be zero */
DECL|typedef|THREADNAME_INFO
block|}
name|THREADNAME_INFO
typedef|;
if|if
condition|(
name|info
operator|->
name|ExceptionRecord
operator|!=
name|NULL
operator|&&
name|info
operator|->
name|ExceptionRecord
operator|->
name|ExceptionCode
operator|==
name|EXCEPTION_SET_THREAD_NAME
operator|&&
name|info
operator|->
name|ExceptionRecord
operator|->
name|NumberParameters
operator|*
sizeof|sizeof
argument_list|(
name|ULONG_PTR
argument_list|)
operator|==
sizeof|sizeof
argument_list|(
name|THREADNAME_INFO
argument_list|)
condition|)
block|{
name|THREADNAME_INFO
name|name_info
decl_stmt|;
name|memcpy
argument_list|(
operator|&
name|name_info
argument_list|,
name|info
operator|->
name|ExceptionRecord
operator|->
name|ExceptionInformation
argument_list|,
sizeof|sizeof
argument_list|(
name|name_info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|name_info
operator|.
name|dwType
operator|==
literal|0x1000
condition|)
block|{
name|DWORD
name|tid
init|=
name|name_info
operator|.
name|dwThreadID
decl_stmt|;
if|if
condition|(
name|tid
operator|==
operator|-
literal|1
condition|)
name|tid
operator|=
name|GetCurrentThreadId
argument_list|()
expr_stmt|;
while|while
condition|(
operator|!
name|g_atomic_int_compare_and_exchange
argument_list|(
operator|&
name|thread_names_spinlock
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
condition|)
empty_stmt|;
if|if
condition|(
name|n_thread_names
operator|<
name|MAX_N_THREADS
condition|)
block|{
name|Thread
modifier|*
name|thread
init|=
operator|&
name|thread_names
index|[
name|n_thread_names
operator|++
index|]
decl_stmt|;
name|thread
operator|->
name|tid
operator|=
name|tid
expr_stmt|;
name|thread
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name_info
operator|.
name|szName
argument_list|)
expr_stmt|;
block|}
name|g_atomic_int_set
argument_list|(
operator|&
name|thread_names_spinlock
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|EXCEPTION_CONTINUE_EXECUTION
return|;
block|}
block|}
return|return
name|EXCEPTION_CONTINUE_SEARCH
return|;
undef|#
directive|undef
name|EXCEPTION_SET_THREAD_NAME
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_backtrace_init (void)
name|gimp_backtrace_init
parameter_list|(
name|void
parameter_list|)
block|{
name|AddVectoredExceptionHandler
argument_list|(
name|TRUE
argument_list|,
name|gimp_backtrace_exception_handler
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_backtrace_start (void)
name|gimp_backtrace_start
parameter_list|(
name|void
parameter_list|)
block|{
name|g_mutex_lock
argument_list|(
operator|&
name|mutex
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_initializations
operator|==
literal|0
condition|)
block|{
name|HMODULE
name|hModule
decl_stmt|;
name|DWORD
name|options
decl_stmt|;
name|hModule
operator|=
name|LoadLibraryA
argument_list|(
literal|"mgwhelp.dll"
argument_list|)
expr_stmt|;
DECL|macro|INIT_PROC (name)
define|#
directive|define
name|INIT_PROC
parameter_list|(
name|name
parameter_list|)
define|\
value|G_STMT_START                                             \           {                                                      \             gimp_backtrace_##name = name;                        \                                                                  \             if (hModule)                                         \               {                                                  \                 gpointer proc = GetProcAddress (hModule, #name); \                                                                  \                 if (proc)                                        \                   gimp_backtrace_##name = proc;                  \               }                                                  \           }                                                      \         G_STMT_END
name|INIT_PROC
argument_list|(
name|SymSetOptions
argument_list|)
expr_stmt|;
name|INIT_PROC
argument_list|(
name|SymInitialize
argument_list|)
expr_stmt|;
name|INIT_PROC
argument_list|(
name|SymCleanup
argument_list|)
expr_stmt|;
name|INIT_PROC
argument_list|(
name|SymFromAddr
argument_list|)
expr_stmt|;
name|INIT_PROC
argument_list|(
name|SymGetLineFromAddr64
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|INIT_PROC
name|options
operator|=
name|SymGetOptions
argument_list|()
expr_stmt|;
name|options
operator|&=
operator|~
name|SYMOPT_UNDNAME
expr_stmt|;
name|options
operator||=
name|SYMOPT_OMAP_FIND_NEAREST
operator||
name|SYMOPT_DEFERRED_LOADS
operator||
name|SYMOPT_DEBUG
expr_stmt|;
ifdef|#
directive|ifdef
name|ARCH_X86_64
name|options
operator||=
name|SYMOPT_INCLUDE_32BIT_MODULES
expr_stmt|;
endif|#
directive|endif
name|gimp_backtrace_SymSetOptions
argument_list|(
name|options
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_backtrace_SymInitialize
argument_list|(
name|GetCurrentProcess
argument_list|()
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
condition|)
block|{
name|n_threads
operator|=
literal|0
expr_stmt|;
name|last_thread_enumeration_time
operator|=
literal|0
expr_stmt|;
name|n_thread_times
operator|=
literal|0
expr_stmt|;
name|initialized
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
name|n_initializations
operator|++
expr_stmt|;
name|g_mutex_unlock
argument_list|(
operator|&
name|mutex
argument_list|)
expr_stmt|;
return|return
name|initialized
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_backtrace_stop (void)
name|gimp_backtrace_stop
parameter_list|(
name|void
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|n_initializations
operator|>
literal|0
argument_list|)
expr_stmt|;
name|g_mutex_lock
argument_list|(
operator|&
name|mutex
argument_list|)
expr_stmt|;
name|n_initializations
operator|--
expr_stmt|;
if|if
condition|(
name|n_initializations
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|initialized
condition|)
block|{
name|gimp_backtrace_SymCleanup
argument_list|(
name|GetCurrentProcess
argument_list|()
argument_list|)
expr_stmt|;
name|initialized
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
name|g_mutex_unlock
argument_list|(
operator|&
name|mutex
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpBacktrace
modifier|*
DECL|function|gimp_backtrace_new (gboolean include_current_thread)
name|gimp_backtrace_new
parameter_list|(
name|gboolean
name|include_current_thread
parameter_list|)
block|{
name|GimpBacktrace
modifier|*
name|backtrace
decl_stmt|;
name|HANDLE
name|hProcess
decl_stmt|;
name|DWORD
name|tid
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_mutex_lock
argument_list|(
operator|&
name|mutex
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_backtrace_enumerate_threads
argument_list|()
condition|)
block|{
name|g_mutex_unlock
argument_list|(
operator|&
name|mutex
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|hProcess
operator|=
name|GetCurrentProcess
argument_list|()
expr_stmt|;
name|tid
operator|=
name|GetCurrentThreadId
argument_list|()
expr_stmt|;
name|backtrace
operator|=
name|g_slice_new
argument_list|(
name|GimpBacktrace
argument_list|)
expr_stmt|;
name|backtrace
operator|->
name|threads
operator|=
name|g_new
argument_list|(
name|GimpBacktraceThread
argument_list|,
name|n_threads
argument_list|)
expr_stmt|;
name|backtrace
operator|->
name|n_threads
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_threads
condition|;
name|i
operator|++
control|)
block|{
name|GimpBacktraceThread
modifier|*
name|thread
init|=
operator|&
name|backtrace
operator|->
name|threads
index|[
name|backtrace
operator|->
name|n_threads
index|]
decl_stmt|;
name|HANDLE
name|hThread
decl_stmt|;
name|CONTEXT
name|context
init|=
block|{}
decl_stmt|;
name|STACKFRAME64
name|frame
init|=
block|{}
decl_stmt|;
name|DWORD
name|machine_type
decl_stmt|;
name|FILETIME
name|creation_time
decl_stmt|;
name|FILETIME
name|exit_time
decl_stmt|;
name|FILETIME
name|kernel_time
decl_stmt|;
name|FILETIME
name|user_time
decl_stmt|;
if|if
condition|(
operator|!
name|include_current_thread
operator|&&
name|threads
index|[
name|i
index|]
operator|.
name|tid
operator|==
name|tid
condition|)
continue|continue;
name|hThread
operator|=
name|OpenThread
argument_list|(
name|THREAD_QUERY_INFORMATION
operator||
name|THREAD_GET_CONTEXT
operator||
name|THREAD_SUSPEND_RESUME
argument_list|,
name|FALSE
argument_list|,
name|threads
index|[
name|i
index|]
operator|.
name|tid
argument_list|)
expr_stmt|;
if|if
condition|(
name|hThread
operator|==
name|INVALID_HANDLE_VALUE
condition|)
continue|continue;
if|if
condition|(
name|threads
index|[
name|i
index|]
operator|.
name|tid
operator|!=
name|tid
operator|&&
name|SuspendThread
argument_list|(
name|hThread
argument_list|)
operator|==
operator|(
name|DWORD
operator|)
operator|-
literal|1
condition|)
block|{
name|CloseHandle
argument_list|(
name|hThread
argument_list|)
expr_stmt|;
continue|continue;
block|}
name|context
operator|.
name|ContextFlags
operator|=
name|CONTEXT_FULL
expr_stmt|;
if|if
condition|(
operator|!
name|GetThreadContext
argument_list|(
name|hThread
argument_list|,
operator|&
name|context
argument_list|)
condition|)
block|{
if|if
condition|(
name|threads
index|[
name|i
index|]
operator|.
name|tid
operator|!=
name|tid
condition|)
name|ResumeThread
argument_list|(
name|hThread
argument_list|)
expr_stmt|;
name|CloseHandle
argument_list|(
name|hThread
argument_list|)
expr_stmt|;
continue|continue;
block|}
ifdef|#
directive|ifdef
name|ARCH_X86_64
name|machine_type
operator|=
name|IMAGE_FILE_MACHINE_AMD64
expr_stmt|;
name|frame
operator|.
name|AddrPC
operator|.
name|Offset
operator|=
name|context
operator|.
name|Rip
expr_stmt|;
name|frame
operator|.
name|AddrPC
operator|.
name|Mode
operator|=
name|AddrModeFlat
expr_stmt|;
name|frame
operator|.
name|AddrStack
operator|.
name|Offset
operator|=
name|context
operator|.
name|Rsp
expr_stmt|;
name|frame
operator|.
name|AddrStack
operator|.
name|Mode
operator|=
name|AddrModeFlat
expr_stmt|;
name|frame
operator|.
name|AddrFrame
operator|.
name|Offset
operator|=
name|context
operator|.
name|Rbp
expr_stmt|;
name|frame
operator|.
name|AddrFrame
operator|.
name|Mode
operator|=
name|AddrModeFlat
expr_stmt|;
elif|#
directive|elif
name|defined
argument_list|(
name|ARCH_X86
argument_list|)
name|machine_type
operator|=
name|IMAGE_FILE_MACHINE_I386
expr_stmt|;
name|frame
operator|.
name|AddrPC
operator|.
name|Offset
operator|=
name|context
operator|.
name|Eip
expr_stmt|;
name|frame
operator|.
name|AddrPC
operator|.
name|Mode
operator|=
name|AddrModeFlat
expr_stmt|;
name|frame
operator|.
name|AddrStack
operator|.
name|Offset
operator|=
name|context
operator|.
name|Esp
expr_stmt|;
name|frame
operator|.
name|AddrStack
operator|.
name|Mode
operator|=
name|AddrModeFlat
expr_stmt|;
name|frame
operator|.
name|AddrFrame
operator|.
name|Offset
operator|=
name|context
operator|.
name|Ebp
expr_stmt|;
name|frame
operator|.
name|AddrFrame
operator|.
name|Mode
operator|=
name|AddrModeFlat
expr_stmt|;
else|#
directive|else
error|#
directive|error
error|unsupported architecture
endif|#
directive|endif
name|thread
operator|->
name|tid
operator|=
name|threads
index|[
name|i
index|]
operator|.
name|tid
expr_stmt|;
name|thread
operator|->
name|name
operator|=
name|threads
index|[
name|i
index|]
operator|.
name|name
expr_stmt|;
name|thread
operator|->
name|last_time
operator|=
literal|0
expr_stmt|;
name|thread
operator|->
name|time
operator|=
literal|0
expr_stmt|;
name|thread
operator|->
name|n_frames
operator|=
literal|0
expr_stmt|;
while|while
condition|(
name|thread
operator|->
name|n_frames
operator|<
name|MAX_N_FRAMES
operator|&&
name|StackWalk64
argument_list|(
name|machine_type
argument_list|,
name|hProcess
argument_list|,
name|hThread
argument_list|,
operator|&
name|frame
argument_list|,
operator|&
name|context
argument_list|,
name|NULL
argument_list|,
name|SymFunctionTableAccess64
argument_list|,
name|SymGetModuleBase64
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|thread
operator|->
name|frames
index|[
name|thread
operator|->
name|n_frames
operator|++
index|]
operator|=
name|frame
operator|.
name|AddrPC
operator|.
name|Offset
expr_stmt|;
if|if
condition|(
name|frame
operator|.
name|AddrPC
operator|.
name|Offset
operator|==
name|frame
operator|.
name|AddrReturn
operator|.
name|Offset
condition|)
break|break;
block|}
if|if
condition|(
name|GetThreadTimes
argument_list|(
name|hThread
argument_list|,
operator|&
name|creation_time
argument_list|,
operator|&
name|exit_time
argument_list|,
operator|&
name|kernel_time
argument_list|,
operator|&
name|user_time
argument_list|)
condition|)
block|{
name|thread
operator|->
name|time
operator|=
operator|(
operator|(
operator|(
name|guint64
operator|)
name|kernel_time
operator|.
name|dwHighDateTime
operator|<<
literal|32
operator|)
operator||
operator|(
operator|(
name|guint64
operator|)
name|kernel_time
operator|.
name|dwLowDateTime
operator|)
operator|)
operator|+
operator|(
operator|(
operator|(
name|guint64
operator|)
name|user_time
operator|.
name|dwHighDateTime
operator|<<
literal|32
operator|)
operator||
operator|(
operator|(
name|guint64
operator|)
name|user_time
operator|.
name|dwLowDateTime
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|i
operator|<
name|n_thread_times
operator|&&
name|thread
operator|->
name|tid
operator|==
name|thread_times
index|[
name|i
index|]
operator|.
name|tid
condition|)
block|{
name|thread
operator|->
name|last_time
operator|=
name|thread_times
index|[
name|i
index|]
operator|.
name|time
expr_stmt|;
block|}
else|else
block|{
name|gint
name|j
decl_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|n_thread_times
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
name|thread
operator|->
name|tid
operator|==
name|thread_times
index|[
name|j
index|]
operator|.
name|tid
condition|)
block|{
name|thread
operator|->
name|last_time
operator|=
name|thread_times
index|[
name|j
index|]
operator|.
name|time
expr_stmt|;
break|break;
block|}
block|}
block|}
block|}
if|if
condition|(
name|threads
index|[
name|i
index|]
operator|.
name|tid
operator|!=
name|tid
condition|)
name|ResumeThread
argument_list|(
name|hThread
argument_list|)
expr_stmt|;
name|CloseHandle
argument_list|(
name|hThread
argument_list|)
expr_stmt|;
if|if
condition|(
name|thread
operator|->
name|n_frames
operator|>
literal|0
condition|)
name|backtrace
operator|->
name|n_threads
operator|++
expr_stmt|;
block|}
name|n_thread_times
operator|=
name|backtrace
operator|->
name|n_threads
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|backtrace
operator|->
name|n_threads
condition|;
name|i
operator|++
control|)
block|{
name|thread_times
index|[
name|i
index|]
operator|.
name|tid
operator|=
name|backtrace
operator|->
name|threads
index|[
name|i
index|]
operator|.
name|tid
expr_stmt|;
name|thread_times
index|[
name|i
index|]
operator|.
name|time
operator|=
name|backtrace
operator|->
name|threads
index|[
name|i
index|]
operator|.
name|time
expr_stmt|;
block|}
name|g_mutex_unlock
argument_list|(
operator|&
name|mutex
argument_list|)
expr_stmt|;
if|if
condition|(
name|backtrace
operator|->
name|n_threads
operator|==
literal|0
condition|)
block|{
name|gimp_backtrace_free
argument_list|(
name|backtrace
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|backtrace
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_backtrace_free (GimpBacktrace * backtrace)
name|gimp_backtrace_free
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|)
block|{
if|if
condition|(
name|backtrace
condition|)
block|{
name|g_free
argument_list|(
name|backtrace
operator|->
name|threads
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpBacktrace
argument_list|,
name|backtrace
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gint
DECL|function|gimp_backtrace_get_n_threads (GimpBacktrace * backtrace)
name|gimp_backtrace_get_n_threads
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|backtrace
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|backtrace
operator|->
name|n_threads
return|;
block|}
end_function

begin_function
name|guintptr
DECL|function|gimp_backtrace_get_thread_id (GimpBacktrace * backtrace,gint thread)
name|gimp_backtrace_get_thread_id
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|,
name|gint
name|thread
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|backtrace
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|thread
operator|>=
literal|0
operator|&&
name|thread
operator|<
name|backtrace
operator|->
name|n_threads
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|backtrace
operator|->
name|threads
index|[
name|thread
index|]
operator|.
name|tid
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_backtrace_get_thread_name (GimpBacktrace * backtrace,gint thread)
name|gimp_backtrace_get_thread_name
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|,
name|gint
name|thread
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|backtrace
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|thread
operator|>=
literal|0
operator|&&
name|thread
operator|<
name|backtrace
operator|->
name|n_threads
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|backtrace
operator|->
name|threads
index|[
name|thread
index|]
operator|.
name|name
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_backtrace_is_thread_running (GimpBacktrace * backtrace,gint thread)
name|gimp_backtrace_is_thread_running
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|,
name|gint
name|thread
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|backtrace
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|thread
operator|>=
literal|0
operator|&&
name|thread
operator|<
name|backtrace
operator|->
name|n_threads
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|backtrace
operator|->
name|threads
index|[
name|thread
index|]
operator|.
name|time
operator|>
name|backtrace
operator|->
name|threads
index|[
name|thread
index|]
operator|.
name|last_time
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_backtrace_find_thread_by_id (GimpBacktrace * backtrace,guintptr thread_id,gint thread_hint)
name|gimp_backtrace_find_thread_by_id
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|,
name|guintptr
name|thread_id
parameter_list|,
name|gint
name|thread_hint
parameter_list|)
block|{
name|DWORD
name|tid
init|=
name|thread_id
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|backtrace
operator|!=
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|thread_hint
operator|>=
literal|0
operator|&&
name|thread_hint
operator|<
name|backtrace
operator|->
name|n_threads
operator|&&
name|backtrace
operator|->
name|threads
index|[
name|thread_hint
index|]
operator|.
name|tid
operator|==
name|tid
condition|)
block|{
return|return
name|thread_hint
return|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|backtrace
operator|->
name|n_threads
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|backtrace
operator|->
name|threads
index|[
name|i
index|]
operator|.
name|tid
operator|==
name|tid
condition|)
return|return
name|i
return|;
block|}
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_backtrace_get_n_frames (GimpBacktrace * backtrace,gint thread)
name|gimp_backtrace_get_n_frames
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|,
name|gint
name|thread
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|backtrace
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|thread
operator|>=
literal|0
operator|&&
name|thread
operator|<
name|backtrace
operator|->
name|n_threads
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|backtrace
operator|->
name|threads
index|[
name|thread
index|]
operator|.
name|n_frames
return|;
block|}
end_function

begin_function
name|guintptr
DECL|function|gimp_backtrace_get_frame_address (GimpBacktrace * backtrace,gint thread,gint frame)
name|gimp_backtrace_get_frame_address
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|,
name|gint
name|thread
parameter_list|,
name|gint
name|frame
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|backtrace
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|thread
operator|>=
literal|0
operator|&&
name|thread
operator|<
name|backtrace
operator|->
name|n_threads
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_backtrace_normalize_frame
argument_list|(
name|backtrace
argument_list|,
name|thread
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|frame
operator|>=
literal|0
operator|&&
name|frame
operator|<
name|backtrace
operator|->
name|threads
index|[
name|thread
index|]
operator|.
name|n_frames
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|backtrace
operator|->
name|threads
index|[
name|thread
index|]
operator|.
name|frames
index|[
name|frame
index|]
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_backtrace_get_address_info (guintptr address,GimpBacktraceAddressInfo * info)
name|gimp_backtrace_get_address_info
parameter_list|(
name|guintptr
name|address
parameter_list|,
name|GimpBacktraceAddressInfo
modifier|*
name|info
parameter_list|)
block|{
name|SYMBOL_INFO
modifier|*
name|symbol_info
decl_stmt|;
name|HANDLE
name|hProcess
decl_stmt|;
name|HMODULE
name|hModule
decl_stmt|;
name|DWORD64
name|offset
init|=
literal|0
decl_stmt|;
name|IMAGEHLP_LINE64
name|line
init|=
block|{}
decl_stmt|;
name|DWORD
name|line_offset
init|=
literal|0
decl_stmt|;
name|gboolean
name|result
init|=
name|FALSE
decl_stmt|;
name|hProcess
operator|=
name|GetCurrentProcess
argument_list|()
expr_stmt|;
name|hModule
operator|=
operator|(
name|HMODULE
operator|)
name|SymGetModuleBase64
argument_list|(
name|hProcess
argument_list|,
name|address
argument_list|)
expr_stmt|;
if|if
condition|(
name|hModule
operator|&&
name|GetModuleFileNameExA
argument_list|(
name|hProcess
argument_list|,
name|hModule
argument_list|,
name|info
operator|->
name|object_name
argument_list|,
sizeof|sizeof
argument_list|(
name|info
operator|->
name|object_name
argument_list|)
argument_list|)
condition|)
block|{
name|result
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|info
operator|->
name|object_name
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
block|}
name|symbol_info
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|SYMBOL_INFO
argument_list|)
operator|+
sizeof|sizeof
argument_list|(
name|info
operator|->
name|symbol_name
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|symbol_info
operator|->
name|SizeOfStruct
operator|=
sizeof|sizeof
argument_list|(
name|SYMBOL_INFO
argument_list|)
expr_stmt|;
name|symbol_info
operator|->
name|MaxNameLen
operator|=
sizeof|sizeof
argument_list|(
name|info
operator|->
name|symbol_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_backtrace_SymFromAddr
argument_list|(
name|hProcess
argument_list|,
name|address
argument_list|,
operator|&
name|offset
argument_list|,
name|symbol_info
argument_list|)
condition|)
block|{
name|g_strlcpy
argument_list|(
name|info
operator|->
name|symbol_name
argument_list|,
name|symbol_info
operator|->
name|Name
argument_list|,
sizeof|sizeof
argument_list|(
name|info
operator|->
name|symbol_name
argument_list|)
argument_list|)
expr_stmt|;
name|info
operator|->
name|symbol_address
operator|=
name|address
operator|-
name|offset
expr_stmt|;
name|result
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|info
operator|->
name|symbol_name
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
name|info
operator|->
name|symbol_address
operator|=
literal|0
expr_stmt|;
block|}
name|g_free
argument_list|(
name|symbol_info
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_backtrace_SymGetLineFromAddr64
argument_list|(
name|hProcess
argument_list|,
name|address
argument_list|,
operator|&
name|line_offset
argument_list|,
operator|&
name|line
argument_list|)
condition|)
block|{
name|g_strlcpy
argument_list|(
name|info
operator|->
name|source_file
argument_list|,
name|line
operator|.
name|FileName
argument_list|,
sizeof|sizeof
argument_list|(
name|info
operator|->
name|source_file
argument_list|)
argument_list|)
expr_stmt|;
name|info
operator|->
name|source_line
operator|=
name|line
operator|.
name|LineNumber
expr_stmt|;
name|result
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|info
operator|->
name|source_file
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
name|info
operator|->
name|source_line
operator|=
literal|0
expr_stmt|;
block|}
return|return
name|result
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_BACKTRACE_BACKEND_WINDOWS */
end_comment

end_unit
