begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PDB_H__
define|#
directive|define
name|__GIMP_PDB_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PDB
define|#
directive|define
name|GIMP_TYPE_PDB
value|(gimp_pdb_get_type ())
end_define

begin_define
DECL|macro|GIMP_PDB (obj)
define|#
directive|define
name|GIMP_PDB
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PDB, GimpPDB))
end_define

begin_define
DECL|macro|GIMP_PDB_CLASS (klass)
define|#
directive|define
name|GIMP_PDB_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PDB, GimpPDBClass))
end_define

begin_define
DECL|macro|GIMP_IS_PDB (obj)
define|#
directive|define
name|GIMP_IS_PDB
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PDB))
end_define

begin_define
DECL|macro|GIMP_IS_PDB_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PDB_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PDB))
end_define

begin_define
DECL|macro|GIMP_PDB_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PDB_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PDB, GimpPDBClass))
end_define

begin_typedef
DECL|typedef|GimpPDBClass
typedef|typedef
name|struct
name|_GimpPDBClass
name|GimpPDBClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPDB
struct|struct
name|_GimpPDB
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|procedures
name|GHashTable
modifier|*
name|procedures
decl_stmt|;
DECL|member|compat_proc_names
name|GHashTable
modifier|*
name|compat_proc_names
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPDBClass
struct|struct
name|_GimpPDBClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|register_procedure
name|void
function_decl|(
modifier|*
name|register_procedure
function_decl|)
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
DECL|member|unregister_procedure
name|void
function_decl|(
modifier|*
name|unregister_procedure
function_decl|)
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_pdb_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpPDB
modifier|*
name|gimp_pdb_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pdb_register_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pdb_unregister_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpProcedure
modifier|*
name|gimp_pdb_lookup_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pdb_register_compat_proc_name
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|old_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_pdb_lookup_compat_proc_name
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|old_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GValueArray
modifier|*
name|gimp_pdb_execute_procedure_by_name_args
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GValueArray
modifier|*
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GValueArray
modifier|*
name|gimp_pdb_execute_procedure_by_name
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_pdb_get_deprecated_procedures
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PDB_H__  */
end_comment

end_unit

