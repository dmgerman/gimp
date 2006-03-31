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
DECL|member|type
name|GimpPDBArgType
name|type
decl_stmt|;
DECL|member|value
name|GValue
name|value
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_ProcArg
struct|struct
name|_ProcArg
block|{
DECL|member|type
name|GimpPDBArgType
name|type
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

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/*  Argument marshalling procedures  */
end_comment

begin_comment
unit|typedef Argument * (* ArgMarshal) (ProcRecord   *procedure,                                    Gimp         *gimp,                                    GimpContext  *context,                                    GimpProgress *progress,                                    Argument     *args);
comment|/*  Execution types  */
end_comment

begin_comment
unit|typedef struct _IntExec    IntExec; typedef struct _PlugInExec PlugInExec; typedef struct _ExtExec    ExtExec; typedef struct _TempExec   TempExec;   struct _IntExec {   ArgMarshal  marshal_func;
comment|/*  Function called to marshal arguments  */
end_comment

begin_comment
unit|};  struct _PlugInExec {   gchar      *filename;
comment|/*  Where is the executable on disk?  */
end_comment

begin_comment
unit|};  struct _ExtExec {   gchar      *filename;
comment|/*  Where is the executable on disk?  */
end_comment

begin_comment
unit|};  struct _TempExec {   void       *plug_in;
comment|/*  Plug-in that registered this temp proc  */
end_comment

begin_comment
unit|};
comment|/*  Structure for a procedure  */
end_comment

begin_comment
unit|struct _ProcRecord {
comment|/*  Procedure information  */
end_comment

begin_comment
unit|gchar       *name;
comment|/*  Procedure name  */
end_comment

begin_comment
unit|gchar       *original_name;
comment|/*  Procedure name before canonicalization  */
end_comment

begin_comment
unit|gchar       *blurb;
comment|/*  Short procedure description  */
end_comment

begin_comment
unit|gchar       *help;
comment|/*  Detailed help instructions  */
end_comment

begin_comment
unit|gchar       *author;
comment|/*  Author field  */
end_comment

begin_comment
unit|gchar       *copyright;
comment|/*  Copyright field  */
end_comment

begin_comment
unit|gchar       *date;
comment|/*  Date field  */
end_comment

begin_comment
unit|gchar       *deprecated;
comment|/*  Replacement if the procedure is deprecated  */
end_comment

begin_comment
comment|/*  Procedure type  */
end_comment

begin_comment
unit|GimpPDBProcType  proc_type;
comment|/*  Type of procedure--Internal, Plug-In, Extension  */
end_comment

begin_comment
comment|/*  Input arguments  */
end_comment

begin_comment
unit|gint32       num_args;
comment|/*  Number of procedure arguments  */
end_comment

begin_comment
unit|ProcArg     *args;
comment|/*  Array of procedure arguments   */
end_comment

begin_comment
comment|/*  Output values  */
end_comment

begin_comment
unit|gint32       num_values;
comment|/*  Number of return values        */
end_comment

begin_comment
unit|ProcArg     *values;
comment|/*  Array of return values         */
end_comment

begin_comment
comment|/*  Method of procedure execution  */
end_comment

begin_comment
unit|union _ExecMethod   {     IntExec     internal;
comment|/*  Execution information for internal procs  */
end_comment

begin_comment
unit|PlugInExec  plug_in;
comment|/*  ..................... for plug-ins  */
end_comment

begin_comment
unit|ExtExec     extension;
comment|/*  ..................... for extensions  */
end_comment

begin_comment
unit|TempExec    temporary;
comment|/*  ..................... for temp procs  */
end_comment

begin_endif
unit|} exec_method; };
endif|#
directive|endif
end_endif

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
name|n_return_vals
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|procedural_db_argument_init
parameter_list|(
name|Argument
modifier|*
name|arg
parameter_list|,
name|ProcArg
modifier|*
name|proc_arg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|procedural_db_compat_arg_init
parameter_list|(
name|Argument
modifier|*
name|arg
parameter_list|,
name|GimpPDBArgType
name|arg_type
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
name|n_args
parameter_list|,
name|gboolean
name|full_destroy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|procedural_db_type_name
parameter_list|(
name|GimpPDBArgType
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

