begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpplugin_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
name|__GIMP_PLUG_IN_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_PDB_H__
define|#
directive|define
name|__GIMP_PLUG_IN_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_plugin_domain_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_plugin_help_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_plugin_menu_branch_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_plugin_menu_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_plugin_icon_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|GimpIconType
name|icon_type
parameter_list|,
name|gint
name|icon_data_length
parameter_list|,
specifier|const
name|guint8
modifier|*
name|icon_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_plugin_set_pdb_error_handler
parameter_list|(
name|GimpPDBErrorHandler
name|handler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|GimpPDBErrorHandler
name|_gimp_plugin_get_pdb_error_handler
parameter_list|(
name|void
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
comment|/* __GIMP_PLUG_IN_PDB_H__ */
end_comment

end_unit

