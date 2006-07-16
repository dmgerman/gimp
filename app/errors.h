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

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_APP_GLUE_COMPILATION
end_ifndef

begin_error
error|#
directive|error
error|You must not #include "errors.h" from an app/ subdir
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|void
name|gimp_errors_init
parameter_list|(
specifier|const
name|gchar
modifier|*
name|full_prog_name
parameter_list|,
name|gboolean
name|use_debug_handler
parameter_list|,
name|GimpStackTraceMode
name|stack_trace_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
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

begin_decl_stmt
name|void
name|gimp_fatal_error
argument_list|(
specifier|const
name|gchar
operator|*
name|format
argument_list|,
operator|...
argument_list|)
name|G_GNUC_PRINTF
argument_list|(
literal|1
argument_list|,
literal|2
argument_list|)
name|G_GNUC_NORETURN
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|void
name|gimp_terminate
argument_list|(
specifier|const
name|gchar
operator|*
name|format
argument_list|,
operator|...
argument_list|)
name|G_GNUC_PRINTF
argument_list|(
literal|1
argument_list|,
literal|2
argument_list|)
name|G_GNUC_NORETURN
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __ERRORS_H__ */
end_comment

end_unit

