begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppdb.h  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimp.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

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

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

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

begin_typedef
DECL|typedef|GimpPDBPrivate
typedef|typedef
name|struct
name|_GimpPDBPrivate
name|GimpPDBPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPDB
struct|struct
name|_GimpPDB
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpPDBPrivate
modifier|*
name|priv
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
name|GObjectClass
name|parent_class
decl_stmt|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved5
name|void
function_decl|(
modifier|*
name|_gimp_reserved5
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved6
name|void
function_decl|(
modifier|*
name|_gimp_reserved6
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved7
name|void
function_decl|(
modifier|*
name|_gimp_reserved7
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved8
name|void
function_decl|(
modifier|*
name|_gimp_reserved8
function_decl|)
parameter_list|(
name|void
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
name|gboolean
name|gimp_pdb_procedure_exists
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
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
name|procedure_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpValueArray
modifier|*
name|gimp_pdb_run_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|GType
name|first_type
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpValueArray
modifier|*
name|gimp_pdb_run_procedure_valist
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|GType
name|first_type
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpValueArray
modifier|*
name|gimp_pdb_run_procedure_array
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|arguments
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_pdb_temp_procedure_name
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_pdb_dump_to_file
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gimp_pdb_query_procedures
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|authors
parameter_list|,
specifier|const
name|gchar
modifier|*
name|copyright
parameter_list|,
specifier|const
name|gchar
modifier|*
name|date
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_type
parameter_list|,
name|gint
modifier|*
name|num_matches
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Cruft API  */
end_comment

begin_function_decl
name|gboolean
name|gimp_pdb_get_data
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_pdb_get_data_size
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_pdb_set_data
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gconstpointer
name|data
parameter_list|,
name|guint32
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PDB_H__  */
end_comment

end_unit

