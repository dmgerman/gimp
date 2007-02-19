begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginmanager-call.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_MANAGER_CALL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_MANAGER_CALL_H__
define|#
directive|define
name|__GIMP_PLUG_IN_MANAGER_CALL_H__
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|__YES_I_NEED_GIMP_PLUG_IN_MANAGER_CALL__
end_ifndef

begin_error
error|#
directive|error
error|Do not use gimp_plug_in_manager_call_run*(), use gimp_procedure_execute*() instead.
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  Call the plug-in's query() function  */
end_comment

begin_function_decl
name|void
name|gimp_plug_in_manager_call_query
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Call the plug-in's init() function  */
end_comment

begin_function_decl
name|void
name|gimp_plug_in_manager_call_init
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Run a plug-in as if it were a procedure database procedure  */
end_comment

begin_function_decl
name|GValueArray
modifier|*
name|gimp_plug_in_manager_call_run
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|,
name|GValueArray
modifier|*
name|args
parameter_list|,
name|gboolean
name|synchronous
parameter_list|,
name|gboolean
name|destroy_return_vals
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Run a temp plug-in proc as if it were a procedure database procedure  */
end_comment

begin_function_decl
name|GValueArray
modifier|*
name|gimp_plug_in_manager_call_run_temp
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpTemporaryProcedure
modifier|*
name|procedure
parameter_list|,
name|GValueArray
modifier|*
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PLUG_IN_MANAGER_CALL_H__ */
end_comment

end_unit

