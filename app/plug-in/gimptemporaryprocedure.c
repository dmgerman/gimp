begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptemporaryprocedure.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin.h"
end_include

begin_define
DECL|macro|__YES_I_NEED_GIMP_PLUG_IN_MANAGER_CALL__
define|#
directive|define
name|__YES_I_NEED_GIMP_PLUG_IN_MANAGER_CALL__
end_define

begin_include
include|#
directive|include
file|"gimppluginmanager-call.h"
end_include

begin_include
include|#
directive|include
file|"gimptemporaryprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_temporary_procedure_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|gimp_temporary_procedure_execute
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_temporary_procedure_execute_async
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GFile
modifier|*
name|gimp_temporary_procedure_get_file
parameter_list|(
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpTemporaryProcedure,gimp_temporary_procedure,GIMP_TYPE_PLUG_IN_PROCEDURE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTemporaryProcedure
argument_list|,
argument|gimp_temporary_procedure
argument_list|,
argument|GIMP_TYPE_PLUG_IN_PROCEDURE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_temporary_procedure_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_temporary_procedure_class_init
parameter_list|(
name|GimpTemporaryProcedureClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpProcedureClass
modifier|*
name|proc_class
init|=
name|GIMP_PROCEDURE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpPlugInProcedureClass
modifier|*
name|plug_class
init|=
name|GIMP_PLUG_IN_PROCEDURE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_temporary_procedure_finalize
expr_stmt|;
name|proc_class
operator|->
name|execute
operator|=
name|gimp_temporary_procedure_execute
expr_stmt|;
name|proc_class
operator|->
name|execute_async
operator|=
name|gimp_temporary_procedure_execute_async
expr_stmt|;
name|plug_class
operator|->
name|get_file
operator|=
name|gimp_temporary_procedure_get_file
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_temporary_procedure_init (GimpTemporaryProcedure * proc)
name|gimp_temporary_procedure_init
parameter_list|(
name|GimpTemporaryProcedure
modifier|*
name|proc
parameter_list|)
block|{
name|GIMP_PROCEDURE
argument_list|(
name|proc
argument_list|)
operator|->
name|proc_type
operator|=
name|GIMP_PDB_PROC_TYPE_TEMPORARY
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_temporary_procedure_finalize (GObject * object)
name|gimp_temporary_procedure_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
comment|/* GimpTemporaryProcedure *proc = GIMP_TEMPORARY_PROCEDURE (object); */
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|gimp_temporary_procedure_execute (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,GimpValueArray * args,GError ** error)
name|gimp_temporary_procedure_execute
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
return|return
name|gimp_plug_in_manager_call_run_temp
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|GIMP_TEMPORARY_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|args
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_temporary_procedure_execute_async (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,GimpValueArray * args,GimpDisplay * display)
name|gimp_temporary_procedure_execute_async
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpTemporaryProcedure
modifier|*
name|temp_procedure
init|=
name|GIMP_TEMPORARY_PROCEDURE
argument_list|(
name|procedure
argument_list|)
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_plug_in_manager_call_run_temp
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|temp_procedure
argument_list|,
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
condition|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
init|=
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
decl_stmt|;
name|gimp_plug_in_procedure_handle_return_values
argument_list|(
name|proc
argument_list|,
name|gimp
argument_list|,
name|progress
argument_list|,
name|return_vals
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GFile
modifier|*
DECL|function|gimp_temporary_procedure_get_file (GimpPlugInProcedure * procedure)
name|gimp_temporary_procedure_get_file
parameter_list|(
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|)
block|{
return|return
name|GIMP_TEMPORARY_PROCEDURE
argument_list|(
name|procedure
argument_list|)
operator|->
name|plug_in
operator|->
name|file
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpProcedure
modifier|*
DECL|function|gimp_temporary_procedure_new (GimpPlugIn * plug_in)
name|gimp_temporary_procedure_new
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|GimpTemporaryProcedure
modifier|*
name|proc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|proc
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEMPORARY_PROCEDURE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|proc
operator|->
name|plug_in
operator|=
name|plug_in
expr_stmt|;
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|proc
argument_list|)
operator|->
name|file
operator|=
name|g_file_new_for_path
argument_list|(
literal|"none"
argument_list|)
expr_stmt|;
return|return
name|GIMP_PROCEDURE
argument_list|(
name|proc
argument_list|)
return|;
block|}
end_function

end_unit

