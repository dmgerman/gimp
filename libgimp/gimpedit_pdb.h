begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpedit_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
name|__GIMP_EDIT_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_EDIT_PDB_H__
define|#
directive|define
name|__GIMP_EDIT_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_edit_cut
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_edit_copy
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_edit_paste
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|paste_into
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_edit_named_cut
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_edit_named_copy
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_edit_named_paste
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|,
name|gboolean
name|paste_into
parameter_list|)
function_decl|;
end_function_decl

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DEPRECATED_REPLACE_NEW_API
end_ifndef

begin_function_decl
name|gboolean
name|gimp_edit_copy_visible
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_edit_paste_as_new_image
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_edit_named_copy_visible
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_edit_named_paste_as_new_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|)
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* GIMP_DEPRECATED_REPLACE_NEW_API */
end_comment

begin_define
DECL|macro|gimp_edit_copy_visible
define|#
directive|define
name|gimp_edit_copy_visible
value|_gimp_edit_copy_visible
end_define

begin_define
DECL|macro|gimp_edit_paste_as_new_image
define|#
directive|define
name|gimp_edit_paste_as_new_image
value|_gimp_edit_paste_as_new_image
end_define

begin_define
DECL|macro|gimp_edit_named_copy_visible
define|#
directive|define
name|gimp_edit_named_copy_visible
value|_gimp_edit_named_copy_visible
end_define

begin_define
DECL|macro|gimp_edit_named_paste_as_new_image
define|#
directive|define
name|gimp_edit_named_paste_as_new_image
value|_gimp_edit_named_paste_as_new_image
end_define

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

begin_function_decl
name|gboolean
name|_gimp_edit_copy_visible
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|_gimp_edit_paste_as_new_image
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|_gimp_edit_named_copy_visible
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|_gimp_edit_named_paste_as_new_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|buffer_name
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
comment|/* __GIMP_EDIT_PDB_H__ */
end_comment

end_unit

