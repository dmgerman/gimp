begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SCRIPT_FU_SCRIPT_H__
end_ifndef

begin_define
DECL|macro|__SCRIPT_FU_SCRIPT_H__
define|#
directive|define
name|__SCRIPT_FU_SCRIPT_H__
end_define

begin_function_decl
name|SFScript
modifier|*
name|script_fu_script_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|author
parameter_list|,
specifier|const
name|gchar
modifier|*
name|copyright
parameter_list|,
specifier|const
name|gchar
modifier|*
name|date
parameter_list|,
specifier|const
name|gchar
modifier|*
name|image_types
parameter_list|,
name|gint
name|n_args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|script_fu_script_free
parameter_list|(
name|SFScript
modifier|*
name|script
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|script_fu_script_install_proc
parameter_list|(
name|SFScript
modifier|*
name|script
parameter_list|,
name|GimpRunProc
name|run_proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|script_fu_script_uninstall_proc
parameter_list|(
name|SFScript
modifier|*
name|script
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __SCRIPT_FU_SCRIPT__  */
end_comment

end_unit

