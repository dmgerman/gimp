begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__ERRORS_H__
end_ifndef

begin_define
DECL|macro|__ERRORS_H__
define|#
directive|define
name|__ERRORS_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a4d7f500103
block|{
DECL|enumerator|STACK_TRACE_NEVER
name|STACK_TRACE_NEVER
block|,
DECL|enumerator|STACK_TRACE_QUERY
name|STACK_TRACE_QUERY
block|,
DECL|enumerator|STACK_TRACE_ALWAYS
name|STACK_TRACE_ALWAYS
DECL|typedef|StackTraceMode
block|}
name|StackTraceMode
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|StackTraceMode
name|stack_trace_mode
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_message_func
parameter_list|(
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_fatal_error
parameter_list|(
name|gchar
modifier|*
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_terminate
parameter_list|(
name|gchar
modifier|*
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __ERRORS_H__ */
end_comment

end_unit

