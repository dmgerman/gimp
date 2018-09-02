begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * backtrace-none.c  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

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
name|GIMP_BACKTRACE_BACKEND_NONE
end_ifdef

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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpbacktrace.h"
end_include

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
return|return
name|FALSE
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
block|{ }
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
return|return
name|NULL
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
name|g_return_if_fail
argument_list|(
name|backtrace
operator|==
name|NULL
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
name|g_return_val_if_reached
argument_list|(
literal|0
argument_list|)
expr_stmt|;
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
name|g_return_val_if_reached
argument_list|(
literal|0
argument_list|)
expr_stmt|;
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
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
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
name|g_return_val_if_reached
argument_list|(
operator|-
literal|1
argument_list|)
expr_stmt|;
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
name|g_return_val_if_reached
argument_list|(
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gpointer
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
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_backtrace_get_symbol_info (guintptr address,GimpBacktraceSymbolInfo * info)
name|gimp_backtrace_get_symbol_info
parameter_list|(
name|guintptr
name|address
parameter_list|,
name|GimpBacktraceSymbolInfo
modifier|*
name|info
parameter_list|)
block|{
return|return
name|FALSE
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_BACKTRACE_BACKEND_NONE */
end_comment

end_unit

