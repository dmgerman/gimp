begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|SIOD_WRAPPER_H
end_ifndef

begin_define
DECL|macro|SIOD_WRAPPER_H
define|#
directive|define
name|SIOD_WRAPPER_H
end_define

begin_function_decl
name|void
name|siod_init
parameter_list|(
name|gboolean
name|register_scripts
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|FILE
modifier|*
name|siod_get_output_file
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|siod_set_output_file
parameter_list|(
name|FILE
modifier|*
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|siod_get_verbose_level
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|siod_set_verbose_level
parameter_list|(
name|gint
name|verbose_level
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|siod_print_welcome
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|siod_get_error_msg
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|siod_get_success_msg
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
name|siod_interpret_string
parameter_list|(
specifier|const
name|gchar
modifier|*
name|expr
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* SIOD_WRAPPER_H */
end_comment

end_unit

