begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PLUG_IN_PROC_H__
end_ifndef

begin_define
DECL|macro|__PLUG_IN_PROC_H__
define|#
directive|define
name|__PLUG_IN_PROC_H__
end_define

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_comment
comment|/* time_t */
end_comment

begin_include
include|#
directive|include
file|"pdb/procedural_db.h"
end_include

begin_comment
comment|/* ProcRecord */
end_comment

begin_struct
DECL|struct|_PlugInProcDef
struct|struct
name|_PlugInProcDef
block|{
DECL|member|prog
name|gchar
modifier|*
name|prog
decl_stmt|;
DECL|member|menu_path
name|gchar
modifier|*
name|menu_path
decl_stmt|;
DECL|member|accelerator
name|gchar
modifier|*
name|accelerator
decl_stmt|;
DECL|member|extensions
name|gchar
modifier|*
name|extensions
decl_stmt|;
DECL|member|prefixes
name|gchar
modifier|*
name|prefixes
decl_stmt|;
DECL|member|magics
name|gchar
modifier|*
name|magics
decl_stmt|;
DECL|member|image_types
name|gchar
modifier|*
name|image_types
decl_stmt|;
DECL|member|image_types_val
name|PlugInImageType
name|image_types_val
decl_stmt|;
DECL|member|db_info
name|ProcRecord
name|db_info
decl_stmt|;
DECL|member|extensions_list
name|GSList
modifier|*
name|extensions_list
decl_stmt|;
DECL|member|prefixes_list
name|GSList
modifier|*
name|prefixes_list
decl_stmt|;
DECL|member|magics_list
name|GSList
modifier|*
name|magics_list
decl_stmt|;
DECL|member|mtime
name|time_t
name|mtime
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|PlugInProcDef
modifier|*
name|plug_in_proc_def_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_proc_def_free
parameter_list|(
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ProcRecord
modifier|*
name|plug_in_proc_def_get_proc
parameter_list|(
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|plug_in_proc_def_get_progname
parameter_list|(
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PLUG_IN_PROC_H__ */
end_comment

end_unit

