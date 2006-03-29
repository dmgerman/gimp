begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PROCEDURAL_DB_H__
end_ifndef

begin_define
DECL|macro|__PROCEDURAL_DB_H__
define|#
directive|define
name|__PROCEDURAL_DB_H__
end_define

begin_struct
DECL|struct|_Argument
struct|struct
name|_Argument
block|{
DECL|member|arg_type
name|GimpPDBArgType
name|arg_type
decl_stmt|;
comment|/*  argument type        */
DECL|union|_ArgValue
union|union
name|_ArgValue
block|{
DECL|member|pdb_int
name|gint32
name|pdb_int
decl_stmt|;
comment|/*  Integer type         */
DECL|member|pdb_float
name|gdouble
name|pdb_float
decl_stmt|;
comment|/*  Floating point type  */
DECL|member|pdb_pointer
name|gpointer
name|pdb_pointer
decl_stmt|;
comment|/*  Pointer type         */
DECL|member|pdb_color
name|GimpRGB
name|pdb_color
decl_stmt|;
comment|/*  Color type           */
DECL|member|value
block|}
name|value
union|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Argument marshalling procedures  */
end_comment

begin_typedef
DECL|typedef|ArgMarshal
typedef|typedef
name|Argument
modifier|*
function_decl|(
modifier|*
name|ArgMarshal
function_decl|)
parameter_list|(
name|ProcRecord
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
name|Argument
modifier|*
name|args
parameter_list|)
function_decl|;
end_typedef

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
DECL|member|marshal_func
name|ArgMarshal
name|marshal_func
decl_stmt|;
comment|/*  Function called to marshal arguments  */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_PlugInExec
struct|struct
name|_PlugInExec
block|{
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
comment|/*  Where is the executable on disk?  */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_ExtExec
struct|struct
name|_ExtExec
block|{
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
comment|/*  Where is the executable on disk?  */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_TempExec
struct|struct
name|_TempExec
block|{
DECL|member|plug_in
name|void
modifier|*
name|plug_in
decl_stmt|;
comment|/*  Plug-in that registered this temp proc  */
block|}
struct|;
end_struct

begin_comment
comment|/*  Structure for a procedure argument  */
end_comment

begin_struct
DECL|struct|_ProcArg
struct|struct
name|_ProcArg
block|{
DECL|member|arg_type
name|GimpPDBArgType
name|arg_type
decl_stmt|;
comment|/*  Argument type (int, char, char *, etc)  */
DECL|member|pspec
name|GParamSpec
modifier|*
name|pspec
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Structure for a procedure  */
end_comment

begin_struct
DECL|struct|_ProcRecord
struct|struct
name|_ProcRecord
block|{
comment|/*  Procedure information  */
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/*  Procedure name  */
DECL|member|original_name
name|gchar
modifier|*
name|original_name
decl_stmt|;
comment|/*  Procedure name before canonicalization  */
DECL|member|blurb
name|gchar
modifier|*
name|blurb
decl_stmt|;
comment|/*  Short procedure description  */
DECL|member|help
name|gchar
modifier|*
name|help
decl_stmt|;
comment|/*  Detailed help instructions  */
DECL|member|author
name|gchar
modifier|*
name|author
decl_stmt|;
comment|/*  Author field  */
DECL|member|copyright
name|gchar
modifier|*
name|copyright
decl_stmt|;
comment|/*  Copyright field  */
DECL|member|date
name|gchar
modifier|*
name|date
decl_stmt|;
comment|/*  Date field  */
DECL|member|deprecated
name|gchar
modifier|*
name|deprecated
decl_stmt|;
comment|/*  Replacement if the procedure is deprecated  */
comment|/*  Procedure type  */
DECL|member|proc_type
name|GimpPDBProcType
name|proc_type
decl_stmt|;
comment|/*  Type of procedure--Internal, Plug-In, Extension  */
comment|/*  Input arguments  */
DECL|member|num_args
name|gint32
name|num_args
decl_stmt|;
comment|/*  Number of procedure arguments  */
DECL|member|args
name|ProcArg
modifier|*
name|args
decl_stmt|;
comment|/*  Array of procedure arguments   */
comment|/*  Output values  */
DECL|member|num_values
name|gint32
name|num_values
decl_stmt|;
comment|/*  Number of return values        */
DECL|member|values
name|ProcArg
modifier|*
name|values
decl_stmt|;
comment|/*  Array of return values         */
comment|/*  Method of procedure execution  */
DECL|union|_ExecMethod
union|union
name|_ExecMethod
block|{
DECL|member|internal
name|IntExec
name|internal
decl_stmt|;
comment|/*  Execution information for internal procs  */
DECL|member|plug_in
name|PlugInExec
name|plug_in
decl_stmt|;
comment|/*  ..................... for plug-ins  */
DECL|member|extension
name|ExtExec
name|extension
decl_stmt|;
comment|/*  ..................... for extensions  */
DECL|member|temporary
name|TempExec
name|temporary
decl_stmt|;
comment|/*  ..................... for temp procs  */
DECL|member|exec_method
block|}
name|exec_method
union|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Functions  */
end_comment

begin_function_decl
name|void
name|procedural_db_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|procedural_db_free
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|procedural_db_init_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|procedural_db_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|ProcRecord
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|procedural_db_unregister
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ProcRecord
modifier|*
name|procedural_db_lookup
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Argument
modifier|*
name|procedural_db_execute
parameter_list|(
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
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Argument
modifier|*
name|procedural_db_run_proc
parameter_list|(
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
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Argument
modifier|*
name|procedural_db_arguments
parameter_list|(
name|ProcRecord
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Argument
modifier|*
name|procedural_db_return_values
parameter_list|(
name|ProcRecord
modifier|*
name|procedure
parameter_list|,
name|gboolean
name|success
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|procedural_db_destroy_args
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|,
name|gint
name|nargs
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ProcRecord
modifier|*
name|procedural_db_init_proc
parameter_list|(
name|ProcRecord
modifier|*
name|procedure
parameter_list|,
name|gint
name|n_arguments
parameter_list|,
name|gint
name|n_return_values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|procedural_db_add_argument
parameter_list|(
name|ProcRecord
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
name|procedural_db_add_return_value
parameter_list|(
name|ProcRecord
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
name|procedural_db_add_compat_arg
parameter_list|(
name|ProcRecord
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
name|procedural_db_add_compat_value
parameter_list|(
name|ProcRecord
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PROCEDURAL_DB_H__  */
end_comment

end_unit

