begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SCHEME_WRAPPER_H__
end_ifndef

begin_define
DECL|macro|__SCHEME_WRAPPER_H__
define|#
directive|define
name|__SCHEME_WRAPPER_H__
end_define

begin_include
include|#
directive|include
file|"tinyscheme/scheme.h"
end_include

begin_function_decl
name|void
name|tinyscheme_init
parameter_list|(
name|GList
modifier|*
name|path
parameter_list|,
name|gboolean
name|register_scripts
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ts_set_run_mode
parameter_list|(
name|GimpRunMode
name|run_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ts_set_print_flag
parameter_list|(
name|gint
name|print_flag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ts_print_welcome
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|ts_get_success_msg
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ts_interpret_stdin
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* if the return value is 0, success. error otherwise. */
end_comment

begin_function_decl
name|gint
name|ts_interpret_string
parameter_list|(
specifier|const
name|gchar
modifier|*
name|expr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ts_stdout_output_func
parameter_list|(
name|TsOutputType
name|type
parameter_list|,
specifier|const
name|char
modifier|*
name|string
parameter_list|,
name|int
name|len
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ts_gstring_output_func
parameter_list|(
name|TsOutputType
name|type
parameter_list|,
specifier|const
name|char
modifier|*
name|string
parameter_list|,
name|int
name|len
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __SCHEME_WRAPPER_H__ */
end_comment

end_unit

