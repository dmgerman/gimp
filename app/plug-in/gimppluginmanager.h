begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * plug-ins.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PLUG_INS_H__
end_ifndef

begin_define
DECL|macro|__PLUG_INS_H__
define|#
directive|define
name|__PLUG_INS_H__
end_define

begin_function_decl
name|void
name|plug_ins_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_ins_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Register a plug-in. This function is public for file load-save  * handlers, which are organized around the plug-in data structure.  * This could all be done a little better, but oh well.  -josh  */
end_comment

begin_function_decl
name|void
name|plug_ins_procedure_add
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add/Remove temporary procedures. */
end_comment

begin_function_decl
name|void
name|plug_ins_temp_procedure_add
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpTemporaryProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_ins_temp_procedure_remove
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpTemporaryProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PLUG_INS_H__ */
end_comment

end_unit

