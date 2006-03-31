begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROCEDURE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROCEDURE_H__
define|#
directive|define
name|__GIMP_PROCEDURE_H__
end_define

begin_comment
comment|/*  Execution types  */
end_comment

begin_typedef
DECL|typedef|IntExec
typedef|typedef
name|struct
name|_IntExec
name|IntExec
typedef|;
end_typedef

begin_typedef
DECL|typedef|PlugInExec
typedef|typedef
name|struct
name|_PlugInExec
name|PlugInExec
typedef|;
end_typedef

begin_typedef
DECL|typedef|ExtExec
typedef|typedef
name|struct
name|_ExtExec
name|ExtExec
typedef|;
end_typedef

begin_typedef
DECL|typedef|TempExec
typedef|typedef
name|struct
name|_TempExec
name|TempExec
typedef|;
end_typedef

begin_struct
DECL|struct|_IntExec
struct|struct
name|_IntExec
block|{
comment|/*  Function called to marshal arguments  */
DECL|member|marshal_func
name|GimpArgument
modifier|*
function_decl|(
modifier|*
name|marshal_func
function_decl|)
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
name|GimpArgument
modifier|*
name|args
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_PlugInExec
struct|struct
name|_PlugInExec
block|{
comment|/*  Where is the executable on disk?  */
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_ExtExec
struct|struct
name|_ExtExec
block|{
comment|/*  Where is the executable on disk?  */
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_TempExec
struct|struct
name|_TempExec
block|{
comment|/*  Plug-in that registered this temp proc  */
DECL|member|plug_in
name|void
modifier|*
name|plug_in
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_IS_PROCEDURE (obj)
define|#
directive|define
name|GIMP_IS_PROCEDURE
parameter_list|(
name|obj
parameter_list|)
value|((obj) != NULL)
end_define

begin_struct
DECL|struct|_GimpProcedure
struct|struct
name|_GimpProcedure
block|{
comment|/*  Flags  */
DECL|member|static_proc
name|gboolean
name|static_proc
decl_stmt|;
comment|/* Is the procedure allocated?                */
DECL|member|static_strings
name|gboolean
name|static_strings
decl_stmt|;
comment|/* Are the procedure's strings allocated?     */
comment|/*  Procedure information  */
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/* Procedure name                             */
DECL|member|original_name
name|gchar
modifier|*
name|original_name
decl_stmt|;
comment|/* Procedure name before canonicalization     */
DECL|member|blurb
name|gchar
modifier|*
name|blurb
decl_stmt|;
comment|/* Short procedure description                */
DECL|member|help
name|gchar
modifier|*
name|help
decl_stmt|;
comment|/* Detailed help instructions                 */
DECL|member|author
name|gchar
modifier|*
name|author
decl_stmt|;
comment|/* Author field                               */
DECL|member|copyright
name|gchar
modifier|*
name|copyright
decl_stmt|;
comment|/* Copyright field                            */
DECL|member|date
name|gchar
modifier|*
name|date
decl_stmt|;
comment|/* Date field                                 */
DECL|member|deprecated
name|gchar
modifier|*
name|deprecated
decl_stmt|;
comment|/* Replacement if the procedure is deprecated */
comment|/*  Procedure type  */
DECL|member|proc_type
name|GimpPDBProcType
name|proc_type
decl_stmt|;
comment|/* Type of procedure                          */
comment|/*  Input arguments  */
DECL|member|num_args
name|gint32
name|num_args
decl_stmt|;
comment|/* Number of procedure arguments              */
DECL|member|args
name|GimpArgumentSpec
modifier|*
name|args
decl_stmt|;
comment|/* Array of procedure arguments               */
comment|/*  Output values  */
DECL|member|num_values
name|gint32
name|num_values
decl_stmt|;
comment|/* Number of return values                    */
DECL|member|values
name|GimpArgumentSpec
modifier|*
name|values
decl_stmt|;
comment|/* Array of return values                     */
comment|/*  Method of procedure execution  */
DECL|union|_ExecMethod
union|union
name|_ExecMethod
block|{
DECL|member|internal
name|IntExec
name|internal
decl_stmt|;
comment|/* Execution information for internal procs   */
DECL|member|plug_in
name|PlugInExec
name|plug_in
decl_stmt|;
comment|/* ..................... for plug-ins         */
DECL|member|extension
name|ExtExec
name|extension
decl_stmt|;
comment|/* ..................... for extensions       */
DECL|member|temporary
name|TempExec
name|temporary
decl_stmt|;
comment|/* ..................... for temp procs       */
DECL|member|exec_method
block|}
name|exec_method
union|;
block|}
struct|;
end_struct

begin_function_decl
name|GimpProcedure
modifier|*
name|gimp_procedure_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_free
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpProcedure
modifier|*
name|gimp_procedure_init
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gint
name|n_arguments
parameter_list|,
name|gint
name|n_return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_set_strings
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|original_name
parameter_list|,
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
name|date
parameter_list|,
name|gchar
modifier|*
name|deprecated
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_set_static_strings
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|original_name
parameter_list|,
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
name|date
parameter_list|,
name|gchar
modifier|*
name|deprecated
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_take_strings
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|original_name
parameter_list|,
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
name|date
parameter_list|,
name|gchar
modifier|*
name|deprecated
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_add_argument
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpPDBArgType
name|arg_type
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_add_return_value
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpPDBArgType
name|arg_type
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_add_compat_arg
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPDBArgType
name|arg_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_add_compat_value
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPDBArgType
name|arg_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpArgument
modifier|*
name|gimp_procedure_get_arguments
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpArgument
modifier|*
name|gimp_procedure_get_return_values
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gboolean
name|success
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpArgument
modifier|*
name|gimp_procedure_execute
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
name|GimpArgument
modifier|*
name|args
parameter_list|,
name|gint
name|n_args
parameter_list|,
name|gint
modifier|*
name|n_return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PROCEDURE_H__  */
end_comment

end_unit

