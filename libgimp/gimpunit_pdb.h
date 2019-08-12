begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpunit_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
name|__GIMP_UNIT_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UNIT_PDB_H__
define|#
directive|define
name|__GIMP_UNIT_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|G_GNUC_INTERNAL
name|gint
name|_gimp_unit_get_number_of_units
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gint
name|_gimp_unit_get_number_of_built_in_units
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|GimpUnit
name|_gimp_unit_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gdouble
name|factor
parameter_list|,
name|gint
name|digits
parameter_list|,
specifier|const
name|gchar
modifier|*
name|symbol
parameter_list|,
specifier|const
name|gchar
modifier|*
name|abbreviation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|singular
parameter_list|,
specifier|const
name|gchar
modifier|*
name|plural
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_unit_get_deletion_flag
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_unit_set_deletion_flag
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|,
name|gboolean
name|deletion_flag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_unit_get_identifier
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gdouble
name|_gimp_unit_get_factor
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gint
name|_gimp_unit_get_digits
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_unit_get_symbol
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_unit_get_abbreviation
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_unit_get_singular
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_unit_get_plural
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
function_decl|;
end_function_decl

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DEPRECATED_REPLACE_NEW_API
end_ifndef

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* GIMP_DEPRECATED_REPLACE_NEW_API */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DEPRECATED_REPLACE_NEW_API */
end_comment

begin_comment
comment|/* Below API are deprecated and should not be used by new plug-ins.  * They are not marked internal as a trick to keep the old API alive for now.  */
end_comment

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_UNIT_PDB_H__ */
end_comment

end_unit

