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

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"gimpimageF.h"
end_include

begin_comment
comment|/*  Procedural database types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2797742e0103
block|{
DECL|enumerator|PDB_INT32
name|PDB_INT32
block|,
DECL|enumerator|PDB_INT16
name|PDB_INT16
block|,
DECL|enumerator|PDB_INT8
name|PDB_INT8
block|,
DECL|enumerator|PDB_FLOAT
name|PDB_FLOAT
block|,
DECL|enumerator|PDB_STRING
name|PDB_STRING
block|,
DECL|enumerator|PDB_INT32ARRAY
name|PDB_INT32ARRAY
block|,
DECL|enumerator|PDB_INT16ARRAY
name|PDB_INT16ARRAY
block|,
DECL|enumerator|PDB_INT8ARRAY
name|PDB_INT8ARRAY
block|,
DECL|enumerator|PDB_FLOATARRAY
name|PDB_FLOATARRAY
block|,
DECL|enumerator|PDB_STRINGARRAY
name|PDB_STRINGARRAY
block|,
DECL|enumerator|PDB_COLOR
name|PDB_COLOR
block|,
DECL|enumerator|PDB_REGION
name|PDB_REGION
block|,
DECL|enumerator|PDB_DISPLAY
name|PDB_DISPLAY
block|,
DECL|enumerator|PDB_IMAGE
name|PDB_IMAGE
block|,
DECL|enumerator|PDB_LAYER
name|PDB_LAYER
block|,
DECL|enumerator|PDB_CHANNEL
name|PDB_CHANNEL
block|,
DECL|enumerator|PDB_DRAWABLE
name|PDB_DRAWABLE
block|,
DECL|enumerator|PDB_SELECTION
name|PDB_SELECTION
block|,
DECL|enumerator|PDB_BOUNDARY
name|PDB_BOUNDARY
block|,
DECL|enumerator|PDB_PATH
name|PDB_PATH
block|,
DECL|enumerator|PDB_PARASITE
name|PDB_PARASITE
block|,
DECL|enumerator|PDB_STATUS
name|PDB_STATUS
block|,
DECL|enumerator|PDB_END
name|PDB_END
DECL|typedef|PDBArgType
block|}
name|PDBArgType
typedef|;
end_typedef

begin_comment
comment|/* NOTE: If you change the PDBArgType enum above, you _must_ change  * the type_str array in procedural_db.c to match. */
end_comment

begin_comment
comment|/*  Error types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2797742e0203
block|{
DECL|enumerator|PDB_EXECUTION_ERROR
name|PDB_EXECUTION_ERROR
block|,
DECL|enumerator|PDB_CALLING_ERROR
name|PDB_CALLING_ERROR
block|,
DECL|enumerator|PDB_PASS_THROUGH
name|PDB_PASS_THROUGH
block|,
DECL|enumerator|PDB_SUCCESS
name|PDB_SUCCESS
DECL|typedef|PDBStatusType
block|}
name|PDBStatusType
typedef|;
end_typedef

begin_comment
comment|/*  Procedure types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2797742e0303
block|{
DECL|enumerator|PDB_INTERNAL
name|PDB_INTERNAL
block|,
DECL|enumerator|PDB_PLUGIN
name|PDB_PLUGIN
block|,
DECL|enumerator|PDB_EXTENSION
name|PDB_EXTENSION
block|,
DECL|enumerator|PDB_TEMPORARY
name|PDB_TEMPORARY
DECL|typedef|PDBProcType
block|}
name|PDBProcType
typedef|;
end_typedef

begin_comment
comment|/*  Argument type  */
end_comment

begin_typedef
DECL|typedef|Argument
typedef|typedef
name|struct
name|_Argument
name|Argument
typedef|;
end_typedef

begin_struct
DECL|struct|_Argument
struct|struct
name|_Argument
block|{
DECL|member|arg_type
name|PDBArgType
name|arg_type
decl_stmt|;
comment|/*  argument type  */
DECL|union|_ArgValue
union|union
name|_ArgValue
block|{
DECL|member|pdb_int
name|gint32
name|pdb_int
decl_stmt|;
comment|/*  Integer type  */
DECL|member|pdb_float
name|gdouble
name|pdb_float
decl_stmt|;
comment|/*  Floating point type  */
DECL|member|pdb_pointer
name|gpointer
name|pdb_pointer
decl_stmt|;
comment|/*  Pointer type  */
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
name|Argument
modifier|*
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

begin_typedef
DECL|typedef|NetExec
typedef|typedef
name|struct
name|_NetExec
name|NetExec
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

begin_struct
DECL|struct|_NetExec
struct|struct
name|_NetExec
block|{
DECL|member|host
name|gchar
modifier|*
name|host
decl_stmt|;
comment|/*  Host responsible for procedure execution  */
DECL|member|port
name|gint32
name|port
decl_stmt|;
comment|/*  Port on host to send data to  */
block|}
struct|;
end_struct

begin_comment
comment|/*  Structure for a procedure argument  */
end_comment

begin_typedef
DECL|typedef|ProcArg
typedef|typedef
name|struct
name|_ProcArg
name|ProcArg
typedef|;
end_typedef

begin_struct
DECL|struct|_ProcArg
struct|struct
name|_ProcArg
block|{
DECL|member|arg_type
name|PDBArgType
name|arg_type
decl_stmt|;
comment|/*  Argument type (int, char, char *, etc)  */
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
comment|/*  Argument name  */
DECL|member|description
name|char
modifier|*
name|description
decl_stmt|;
comment|/*  Argument description  */
block|}
struct|;
end_struct

begin_comment
comment|/*  Structure for a procedure  */
end_comment

begin_typedef
DECL|typedef|ProcRecord
typedef|typedef
name|struct
name|_ProcRecord
name|ProcRecord
typedef|;
end_typedef

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
comment|/*  Procedure type  */
DECL|member|proc_type
name|PDBProcType
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
comment|/*  Array of procedure arguments  */
comment|/*  Output values  */
DECL|member|num_values
name|gint32
name|num_values
decl_stmt|;
comment|/*  Number of return values  */
DECL|member|values
name|ProcArg
modifier|*
name|values
decl_stmt|;
comment|/*  Array of return values  */
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
comment|/*  External data  */
end_comment

begin_decl_stmt
specifier|extern
name|ProcRecord
name|procedural_db_dump_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|procedural_db_query_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|procedural_db_proc_info_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|procedural_db_proc_arg_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|procedural_db_proc_val_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|procedural_db_get_data_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|procedural_db_set_data_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|procedural_db_get_data_size_proc
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Functions  */
end_comment

begin_function_decl
name|void
name|procedural_db_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|procedural_db_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|procedural_db_register
parameter_list|(
name|ProcRecord
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|procedural_db_unregister
parameter_list|(
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ProcRecord
modifier|*
name|procedural_db_lookup
parameter_list|(
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Argument
modifier|*
name|procedural_db_execute
parameter_list|(
name|gchar
modifier|*
parameter_list|,
name|Argument
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Argument
modifier|*
name|procedural_db_run_proc
parameter_list|(
name|gchar
modifier|*
parameter_list|,
name|gint
modifier|*
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Argument
modifier|*
name|procedural_db_return_args
parameter_list|(
name|ProcRecord
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|procedural_db_destroy_args
parameter_list|(
name|Argument
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pdb_add_image
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|pdb_image_to_id
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|pdb_id_to_image
parameter_list|(
name|gint
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pdb_remove_image
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* "type" should really be a PDBArgType, but we can cope with  *  out-of-range values. */
end_comment

begin_function_decl
specifier|const
name|char
modifier|*
name|pdb_type_name
parameter_list|(
name|gint
name|type
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

