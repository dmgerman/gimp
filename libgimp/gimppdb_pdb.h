begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimppdb_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
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
name|__GIMP_PDB_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PDB_PDB_H__
define|#
directive|define
name|__GIMP_PDB_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_pdb_temp_name
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_pdb_dump
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_pdb_query
parameter_list|(
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
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|procedure_names
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_pdb_proc_exists
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_pdb_proc_info
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|GimpPDBProcType
modifier|*
name|proc_type
parameter_list|,
name|gint
modifier|*
name|num_args
parameter_list|,
name|gint
modifier|*
name|num_values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_pdb_proc_documentation
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_pdb_proc_attribution
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|authors
parameter_list|,
name|gchar
modifier|*
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
modifier|*
name|date
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|GParamSpec
modifier|*
name|_gimp_pdb_proc_argument
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|gint
name|arg_num
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|GParamSpec
modifier|*
name|_gimp_pdb_proc_return_value
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|gint
name|val_num
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_pdb_get_data
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gint
modifier|*
name|bytes
parameter_list|,
name|guint8
modifier|*
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gint
name|_gimp_pdb_get_data_size
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_pdb_set_data
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gint
name|bytes
parameter_list|,
specifier|const
name|guint8
modifier|*
name|data
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
comment|/* __GIMP_PDB_PDB_H__ */
end_comment

end_unit

