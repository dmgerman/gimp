begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpbacktrace-linux.c  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_define
DECL|macro|_GNU_SOURCE
define|#
directive|define
name|_GNU_SOURCE
end_define

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimpbacktrace-backend.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|GIMP_BACKTRACE_BACKEND_LINUX
end_ifdef

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<sys/syscall.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<dirent.h>
end_include

begin_include
include|#
directive|include
file|<signal.h>
end_include

begin_include
include|#
directive|include
file|<execinfo.h>
end_include

begin_include
include|#
directive|include
file|<dlfcn.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_LIBUNWIND
end_ifdef

begin_define
DECL|macro|UNW_LOCAL_ONLY
define|#
directive|define
name|UNW_LOCAL_ONLY
end_define

begin_include
include|#
directive|include
file|<libunwind.h>
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
DECL|macro|MAX_THREAD_NAME_SIZE
define|#
directive|define
name|MAX_THREAD_NAME_SIZE
value|32
end_define

begin_define
DECL|macro|N_SKIPPED_FRAMES
define|#
directive|define
name|N_SKIPPED_FRAMES
value|2
end_define

begin_define
DECL|macro|MAX_WAIT_TIME
define|#
directive|define
name|MAX_WAIT_TIME
value|(G_TIME_SPAN_SECOND / 2)
end_define

begin_define
DECL|macro|BACKTRACE_SIGNAL
define|#
directive|define
name|BACKTRACE_SIGNAL
value|SIGUSR1
end_define

begin_typedef
DECL|typedef|GimpBacktraceThread
typedef|typedef
name|struct
name|_GimpBacktraceThread
name|GimpBacktraceThread
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBacktraceThread
struct|struct
name|_GimpBacktraceThread
block|{
DECL|member|tid
name|pid_t
name|tid
decl_stmt|;
DECL|member|name
name|gchar
name|name
index|[
name|MAX_THREAD_NAME_SIZE
index|]
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
DECL|member|n_remaining_threads
name|gint
name|n_remaining_threads
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
name|gint
name|gimp_backtrace_enumerate_threads
parameter_list|(
name|gboolean
name|include_current_thread
parameter_list|,
name|pid_t
modifier|*
name|threads
parameter_list|,
name|gint
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_backtrace_read_thread_name
parameter_list|(
name|pid_t
name|tid
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_backtrace_signal_handler
parameter_list|(
name|gint
name|signum
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
DECL|variable|orig_action
specifier|static
name|struct
name|sigaction
name|orig_action
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|blacklisted_threads
specifier|static
name|pid_t
name|blacklisted_threads
index|[
name|MAX_N_THREADS
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|n_blacklisted_threads
specifier|static
name|gint
name|n_blacklisted_threads
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|handler_backtrace
specifier|static
name|GimpBacktrace
modifier|*
name|handler_backtrace
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|blacklisted_thread_names
specifier|static
specifier|const
name|gchar
modifier|*
name|blacklisted_thread_names
index|[]
init|=
block|{
literal|"gmain"
block|}
decl_stmt|;
end_decl_stmt

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
operator|+
name|N_SKIPPED_FRAMES
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
name|gint
DECL|function|gimp_backtrace_enumerate_threads (gboolean include_current_thread,pid_t * threads,gint size)
name|gimp_backtrace_enumerate_threads
parameter_list|(
name|gboolean
name|include_current_thread
parameter_list|,
name|pid_t
modifier|*
name|threads
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
name|DIR
modifier|*
name|dir
decl_stmt|;
name|struct
name|dirent
modifier|*
name|dirent
decl_stmt|;
name|pid_t
name|tid
decl_stmt|;
name|gint
name|n_threads
decl_stmt|;
name|dir
operator|=
name|opendir
argument_list|(
literal|"/proc/self/task"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir
condition|)
return|return
literal|0
return|;
name|tid
operator|=
name|syscall
argument_list|(
name|SYS_gettid
argument_list|)
expr_stmt|;
name|n_threads
operator|=
literal|0
expr_stmt|;
while|while
condition|(
name|n_threads
operator|<
name|size
operator|&&
operator|(
name|dirent
operator|=
name|readdir
argument_list|(
name|dir
argument_list|)
operator|)
condition|)
block|{
name|pid_t
name|id
init|=
name|g_ascii_strtoull
argument_list|(
name|dirent
operator|->
name|d_name
argument_list|,
name|NULL
argument_list|,
literal|10
argument_list|)
decl_stmt|;
if|if
condition|(
name|id
condition|)
block|{
if|if
condition|(
operator|!
name|include_current_thread
operator|&&
name|id
operator|==
name|tid
condition|)
name|id
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|id
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
name|i
operator|<
name|n_blacklisted_threads
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|id
operator|==
name|blacklisted_threads
index|[
name|i
index|]
condition|)
block|{
name|id
operator|=
literal|0
expr_stmt|;
break|break;
block|}
block|}
block|}
if|if
condition|(
name|id
condition|)
name|threads
index|[
name|n_threads
operator|++
index|]
operator|=
name|id
expr_stmt|;
block|}
name|closedir
argument_list|(
name|dir
argument_list|)
expr_stmt|;
return|return
name|n_threads
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_backtrace_read_thread_name (pid_t tid,gchar * name,gint size)
name|gimp_backtrace_read_thread_name
parameter_list|(
name|pid_t
name|tid
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
name|gchar
name|filename
index|[
literal|64
index|]
decl_stmt|;
name|gint
name|fd
decl_stmt|;
if|if
condition|(
name|size
operator|<=
literal|0
condition|)
return|return;
name|name
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
name|g_snprintf
argument_list|(
name|filename
argument_list|,
sizeof|sizeof
argument_list|(
name|filename
argument_list|)
argument_list|,
literal|"/proc/self/task/%llu/comm"
argument_list|,
operator|(
name|unsigned
name|long
name|long
operator|)
name|tid
argument_list|)
expr_stmt|;
name|fd
operator|=
name|open
argument_list|(
name|filename
argument_list|,
name|O_RDONLY
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|>=
literal|0
condition|)
block|{
name|gint
name|n
init|=
name|read
argument_list|(
name|fd
argument_list|,
name|name
argument_list|,
name|size
argument_list|)
decl_stmt|;
if|if
condition|(
name|n
operator|>
literal|0
condition|)
name|name
index|[
name|n
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_backtrace_signal_handler (gint signum)
name|gimp_backtrace_signal_handler
parameter_list|(
name|gint
name|signum
parameter_list|)
block|{
name|GimpBacktrace
modifier|*
name|curr_backtrace
init|=
name|g_atomic_pointer_get
argument_list|(
operator|&
name|handler_backtrace
argument_list|)
decl_stmt|;
name|pid_t
name|tid
init|=
name|syscall
argument_list|(
name|SYS_gettid
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|curr_backtrace
operator|->
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
name|curr_backtrace
operator|->
name|threads
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
name|thread
operator|->
name|tid
operator|==
name|tid
condition|)
block|{
name|thread
operator|->
name|n_frames
operator|=
name|backtrace
argument_list|(
operator|(
name|gpointer
operator|*
operator|)
name|thread
operator|->
name|frames
argument_list|,
name|MAX_N_FRAMES
argument_list|)
expr_stmt|;
name|g_atomic_int_dec_and_test
argument_list|(
operator|&
name|curr_backtrace
operator|->
name|n_remaining_threads
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_backtrace_init (void)
name|gimp_backtrace_init
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
name|struct
name|sigaction
name|action
init|=
block|{}
decl_stmt|;
name|action
operator|.
name|sa_handler
operator|=
name|gimp_backtrace_signal_handler
expr_stmt|;
name|sigemptyset
argument_list|(
operator|&
name|action
operator|.
name|sa_mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|sigaction
argument_list|(
name|BACKTRACE_SIGNAL
argument_list|,
operator|&
name|action
argument_list|,
operator|&
name|orig_action
argument_list|)
operator|==
literal|0
condition|)
block|{
name|pid_t
modifier|*
name|threads
decl_stmt|;
name|gint
name|n_threads
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|n_blacklisted_threads
operator|=
literal|0
expr_stmt|;
name|threads
operator|=
name|g_new
argument_list|(
name|pid_t
argument_list|,
name|MAX_N_THREADS
argument_list|)
expr_stmt|;
name|n_threads
operator|=
name|gimp_backtrace_enumerate_threads
argument_list|(
name|TRUE
argument_list|,
name|threads
argument_list|,
name|MAX_N_THREADS
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
name|n_threads
condition|;
name|i
operator|++
control|)
block|{
name|gchar
name|name
index|[
name|MAX_THREAD_NAME_SIZE
index|]
decl_stmt|;
name|gint
name|j
decl_stmt|;
name|gimp_backtrace_read_thread_name
argument_list|(
name|threads
index|[
name|i
index|]
argument_list|,
name|name
argument_list|,
name|MAX_THREAD_NAME_SIZE
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|G_N_ELEMENTS
argument_list|(
name|blacklisted_thread_names
argument_list|)
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|blacklisted_thread_names
index|[
name|j
index|]
argument_list|)
condition|)
block|{
name|blacklisted_threads
index|[
name|n_blacklisted_threads
operator|++
index|]
operator|=
name|threads
index|[
name|i
index|]
expr_stmt|;
block|}
block|}
block|}
name|g_free
argument_list|(
name|threads
argument_list|)
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
DECL|function|gimp_backtrace_shutdown (void)
name|gimp_backtrace_shutdown
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
operator|&&
name|initialized
condition|)
block|{
if|if
condition|(
name|sigaction
argument_list|(
name|BACKTRACE_SIGNAL
argument_list|,
operator|&
name|orig_action
argument_list|,
name|NULL
argument_list|)
operator|<
literal|0
condition|)
name|g_warning
argument_list|(
literal|"failed to restore origianl backtrace signal handler"
argument_list|)
expr_stmt|;
name|initialized
operator|=
name|FALSE
expr_stmt|;
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
name|pid_t
name|pid
decl_stmt|;
name|pid_t
modifier|*
name|threads
decl_stmt|;
name|gint
name|n_threads
decl_stmt|;
name|gint
name|n_remaining_threads
decl_stmt|;
name|gint
name|prev_n_remaining_threads
decl_stmt|;
name|gint64
name|start_time
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
operator|!
name|initialized
condition|)
return|return
name|NULL
return|;
name|pid
operator|=
name|getpid
argument_list|()
expr_stmt|;
name|threads
operator|=
name|g_new
argument_list|(
name|pid_t
argument_list|,
name|MAX_N_THREADS
argument_list|)
expr_stmt|;
name|n_threads
operator|=
name|gimp_backtrace_enumerate_threads
argument_list|(
name|include_current_thread
argument_list|,
name|threads
argument_list|,
name|MAX_N_THREADS
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_threads
operator|==
literal|0
condition|)
block|{
name|g_free
argument_list|(
name|threads
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|g_mutex_lock
argument_list|(
operator|&
name|mutex
argument_list|)
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
name|n_threads
expr_stmt|;
name|backtrace
operator|->
name|n_remaining_threads
operator|=
name|n_threads
expr_stmt|;
name|g_atomic_pointer_set
argument_list|(
operator|&
name|handler_backtrace
argument_list|,
name|backtrace
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
name|i
index|]
decl_stmt|;
name|thread
operator|->
name|tid
operator|=
name|threads
index|[
name|i
index|]
expr_stmt|;
name|thread
operator|->
name|n_frames
operator|=
literal|0
expr_stmt|;
name|gimp_backtrace_read_thread_name
argument_list|(
name|thread
operator|->
name|tid
argument_list|,
name|thread
operator|->
name|name
argument_list|,
name|MAX_THREAD_NAME_SIZE
argument_list|)
expr_stmt|;
name|syscall
argument_list|(
name|SYS_tgkill
argument_list|,
name|pid
argument_list|,
name|threads
index|[
name|i
index|]
argument_list|,
name|BACKTRACE_SIGNAL
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|threads
argument_list|)
expr_stmt|;
name|start_time
operator|=
name|g_get_monotonic_time
argument_list|()
expr_stmt|;
name|prev_n_remaining_threads
operator|=
name|g_atomic_int_get
argument_list|(
operator|&
name|backtrace
operator|->
name|n_remaining_threads
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|n_remaining_threads
operator|=
name|g_atomic_int_get
argument_list|(
operator|&
name|backtrace
operator|->
name|n_remaining_threads
argument_list|)
operator|>
literal|0
operator|)
condition|)
block|{
name|gint64
name|time
init|=
name|g_get_monotonic_time
argument_list|()
decl_stmt|;
if|if
condition|(
name|n_remaining_threads
operator|<
name|prev_n_remaining_threads
condition|)
block|{
name|prev_n_remaining_threads
operator|=
name|n_remaining_threads
expr_stmt|;
name|start_time
operator|=
name|time
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|time
operator|-
name|start_time
operator|>
name|MAX_WAIT_TIME
condition|)
block|{
break|break;
block|}
block|}
name|handler_backtrace
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|n_remaining_threads
operator|>
literal|0
condition|)
block|{
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
if|if
condition|(
name|backtrace
operator|->
name|threads
index|[
name|i
index|]
operator|.
name|n_frames
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|n_blacklisted_threads
operator|<
name|MAX_N_THREADS
condition|)
block|{
name|blacklisted_threads
index|[
name|n_blacklisted_threads
operator|++
index|]
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
block|}
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
block|}
block|}
name|g_mutex_unlock
argument_list|(
operator|&
name|mutex
argument_list|)
expr_stmt|;
if|if
condition|(
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
operator|!
name|backtrace
operator|||
name|backtrace
operator|->
name|n_remaining_threads
operator|>
literal|0
condition|)
return|return;
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
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|backtrace
operator|->
name|threads
index|[
name|thread
index|]
operator|.
name|name
index|[
literal|0
index|]
condition|)
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
else|else
return|return
name|NULL
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
name|pid_t
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
operator|-
name|N_SKIPPED_FRAMES
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
name|N_SKIPPED_FRAMES
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
name|Dl_info
name|dl_info
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|info
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|HAVE_LIBUNWIND
block|{
name|unw_context_t
name|context
init|=
block|{}
decl_stmt|;
name|unw_cursor_t
name|cursor
decl_stmt|;
name|unw_word_t
name|offset
decl_stmt|;
if|if
condition|(
name|dladdr
argument_list|(
operator|(
name|gpointer
operator|)
name|address
argument_list|,
operator|&
name|dl_info
argument_list|)
operator|&&
name|dl_info
operator|.
name|dli_fname
condition|)
block|{
name|g_strlcpy
argument_list|(
name|info
operator|->
name|object_name
argument_list|,
name|dl_info
operator|.
name|dli_fname
argument_list|,
sizeof|sizeof
argument_list|(
name|info
operator|->
name|object_name
argument_list|)
argument_list|)
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
if|if
condition|(
name|unw_init_local
argument_list|(
operator|&
name|cursor
argument_list|,
operator|&
name|context
argument_list|)
operator|==
literal|0
operator|&&
name|unw_set_reg
argument_list|(
operator|&
name|cursor
argument_list|,
name|UNW_REG_IP
argument_list|,
name|address
argument_list|)
operator|==
literal|0
operator|&&
name|unw_get_proc_name
argument_list|(
operator|&
name|cursor
argument_list|,
name|info
operator|->
name|symbol_name
argument_list|,
sizeof|sizeof
argument_list|(
name|info
operator|->
name|symbol_name
argument_list|)
argument_list|,
operator|&
name|offset
argument_list|)
operator|==
literal|0
condition|)
block|{
name|info
operator|->
name|symbol_address
operator|=
name|address
operator|-
name|offset
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
block|}
else|#
directive|else
if|if
condition|(
operator|!
name|dladdr
argument_list|(
operator|(
name|gpointer
operator|)
name|address
argument_list|,
operator|&
name|dl_info
argument_list|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|dl_info
operator|.
name|dli_fname
condition|)
block|{
name|g_strlcpy
argument_list|(
name|info
operator|->
name|object_name
argument_list|,
name|dl_info
operator|.
name|dli_fname
argument_list|,
sizeof|sizeof
argument_list|(
name|info
operator|->
name|object_name
argument_list|)
argument_list|)
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
if|if
condition|(
name|dl_info
operator|.
name|dli_sname
condition|)
block|{
name|g_strlcpy
argument_list|(
name|info
operator|->
name|symbol_name
argument_list|,
name|dl_info
operator|.
name|dli_sname
argument_list|,
sizeof|sizeof
argument_list|(
name|info
operator|->
name|symbol_name
argument_list|)
argument_list|)
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
block|}
name|info
operator|->
name|symbol_address
operator|=
operator|(
name|guintptr
operator|)
name|dl_info
operator|.
name|dli_saddr
expr_stmt|;
endif|#
directive|endif
return|return
name|TRUE
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_BACKTRACE_BACKEND_LINUX */
end_comment

end_unit

