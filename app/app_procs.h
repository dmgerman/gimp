begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__APP_PROCS_H__
end_ifndef

begin_define
DECL|macro|__APP_PROCS_H__
define|#
directive|define
name|__APP_PROCS_H__
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_APP_GLUE_COMPILATION
end_ifndef

begin_error
error|#
directive|error
error|You must not #include "app_procs.h" from an app/ subdir
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  *  this is a temp hack  */
end_comment

begin_decl_stmt
specifier|extern
name|Gimp
modifier|*
name|the_gimp
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
name|app_gui_libs_init
parameter_list|(
name|gint
modifier|*
name|gimp_argc
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|gimp_argv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|app_init
parameter_list|(
specifier|const
name|gchar
modifier|*
name|full_prog_name
parameter_list|,
name|gint
name|gimp_argc
parameter_list|,
name|gchar
modifier|*
modifier|*
name|gimp_argv
parameter_list|,
specifier|const
name|gchar
modifier|*
name|alternate_system_gimprc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|alternate_gimprc
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|batch_cmds
parameter_list|,
name|gboolean
name|no_interface
parameter_list|,
name|gboolean
name|no_data
parameter_list|,
name|gboolean
name|no_splash
parameter_list|,
name|gboolean
name|no_splash_image
parameter_list|,
name|gboolean
name|be_verbose
parameter_list|,
name|gboolean
name|use_shm
parameter_list|,
name|gboolean
name|use_mmx
parameter_list|,
name|gboolean
name|console_messages
parameter_list|,
name|GimpStackTraceMode
name|stack_trace_mode
parameter_list|,
name|gboolean
name|restore_session
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __APP_PROCS_H__ */
end_comment

end_unit

