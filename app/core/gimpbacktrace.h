begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbacktrace.h  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BACKTRACE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BACKTRACE_H__
define|#
directive|define
name|__GIMP_BACKTRACE_H__
end_define

begin_typedef
DECL|typedef|GimpBacktraceAddressInfo
typedef|typedef
name|struct
name|_GimpBacktraceAddressInfo
name|GimpBacktraceAddressInfo
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBacktraceAddressInfo
struct|struct
name|_GimpBacktraceAddressInfo
block|{
DECL|member|object_name
name|gchar
name|object_name
index|[
literal|256
index|]
decl_stmt|;
DECL|member|symbol_name
name|gchar
name|symbol_name
index|[
literal|256
index|]
decl_stmt|;
DECL|member|symbol_address
name|guintptr
name|symbol_address
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|gboolean
name|gimp_backtrace_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_backtrace_shutdown
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBacktrace
modifier|*
name|gimp_backtrace_new
parameter_list|(
name|gboolean
name|include_current_thread
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_backtrace_free
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_backtrace_get_n_threads
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guintptr
name|gimp_backtrace_get_thread_id
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|,
name|gint
name|thread
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_backtrace_get_thread_name
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|,
name|gint
name|thread
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
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
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_backtrace_get_n_frames
parameter_list|(
name|GimpBacktrace
modifier|*
name|backtrace
parameter_list|,
name|gint
name|thread
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guintptr
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
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_backtrace_get_address_info
parameter_list|(
name|guintptr
name|address
parameter_list|,
name|GimpBacktraceAddressInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BACKTRACE_H__  */
end_comment

end_unit

