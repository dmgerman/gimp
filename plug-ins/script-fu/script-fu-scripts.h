begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SCRIPT_FU_SCRIPTS_H__
end_ifndef

begin_define
DECL|macro|__SCRIPT_FU_SCRIPTS_H__
define|#
directive|define
name|__SCRIPT_FU_SCRIPTS_H__
end_define

begin_function_decl
name|void
name|script_fu_find_scripts
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|script_fu_add_script
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|a
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|script_fu_add_menu
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|a
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|script_fu_error_msg
parameter_list|(
specifier|const
name|gchar
modifier|*
name|command
parameter_list|,
specifier|const
name|gchar
modifier|*
name|msg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|script_fu_strescape
parameter_list|(
specifier|const
name|gchar
modifier|*
name|source
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __SCRIPT_FU_SCRIPTS__  */
end_comment

end_unit

