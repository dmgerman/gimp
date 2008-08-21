begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SCRIPT_FU_INTERFACE_H__
end_ifndef

begin_define
DECL|macro|__SCRIPT_FU_INTERFACE_H__
define|#
directive|define
name|__SCRIPT_FU_INTERFACE_H__
end_define

begin_function_decl
name|GimpPDBStatusType
name|script_fu_interface
parameter_list|(
name|SFScript
modifier|*
name|script
parameter_list|,
name|gint
name|start_arg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|script_fu_interface_report_cc
parameter_list|(
specifier|const
name|gchar
modifier|*
name|command
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|script_fu_interface_is_active
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __SCRIPT_FU_INTERFACE_H__  */
end_comment

end_unit

