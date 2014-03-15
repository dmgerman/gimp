begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimplcms.h  * Copyright (C) 2014  Michael Natterer<mitch@gimp.org>  *                     Elle Stone<ellestone@ninedegreesbelow.com>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_COLOR_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COLOR_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpcolor/gimpcolor.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LCMS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LCMS_H__
define|#
directive|define
name|__GIMP_LCMS_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_typedef
DECL|typedef|GimpColorProfile
typedef|typedef
name|gpointer
name|GimpColorProfile
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_LCMS_MD5_DIGEST_LENGTH
define|#
directive|define
name|GIMP_LCMS_MD5_DIGEST_LENGTH
value|16
end_define

begin_function_decl
name|GimpColorProfile
name|gimp_lcms_profile_open_from_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|guint8
modifier|*
name|md5_digest
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfile
name|gimp_lcms_profile_open_from_data
parameter_list|(
specifier|const
name|guint8
modifier|*
name|data
parameter_list|,
name|gsize
name|length
parameter_list|,
name|guint8
modifier|*
name|md5_digest
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_lcms_profile_get_description
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_lcms_profile_get_manufacturer
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_lcms_profile_get_model
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_lcms_profile_get_copyright
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_lcms_profile_get_summary
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_lcms_profile_is_rgb
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_lcms_profile_is_cmyk
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfile
name|gimp_lcms_create_srgb_profile
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
comment|/* __GIMP_LCMS_H__ */
end_comment

end_unit

