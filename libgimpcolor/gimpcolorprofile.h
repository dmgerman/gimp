begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpcolorprofile.h  * Copyright (C) 2014  Michael Natterer<mitch@gimp.org>  *                     Elle Stone<ellestone@ninedegreesbelow.com>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_COLOR_PROFILE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_PROFILE_H__
define|#
directive|define
name|__GIMP_COLOR_PROFILE_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_COLOR_PROFILE
define|#
directive|define
name|GIMP_TYPE_COLOR_PROFILE
value|(gimp_color_profile_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_PROFILE (obj)
define|#
directive|define
name|GIMP_COLOR_PROFILE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_PROFILE, GimpColorProfile))
end_define

begin_define
DECL|macro|GIMP_COLOR_PROFILE_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_PROFILE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_PROFILE, GimpColorProfileClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_PROFILE (obj)
define|#
directive|define
name|GIMP_IS_COLOR_PROFILE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_PROFILE))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_PROFILE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_PROFILE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_PROFILE))
end_define

begin_define
DECL|macro|GIMP_COLOR_PROFILE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_PROFILE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_PROFILE, GimpColorProfileClass))
end_define

begin_typedef
DECL|typedef|GimpColorProfileClass
typedef|typedef
name|struct
name|_GimpColorProfileClass
name|GimpColorProfileClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorProfilePrivate
typedef|typedef
name|struct
name|_GimpColorProfilePrivate
name|GimpColorProfilePrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorProfile
struct|struct
name|_GimpColorProfile
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpColorProfilePrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorProfileClass
struct|struct
name|_GimpColorProfileClass
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
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_profile_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpColorProfile
modifier|*
name|gimp_color_profile_new_rgb_srgb
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfile
modifier|*
name|gimp_color_profile_new_rgb_srgb_linear
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfile
modifier|*
name|gimp_color_profile_new_rgb_adobe
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfile
modifier|*
name|gimp_color_profile_new_d65_gray_srgb_trc
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfile
modifier|*
name|gimp_color_profile_new_d65_gray_linear
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfile
modifier|*
name|gimp_color_profile_new_srgb_trc_from_color_profile
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfile
modifier|*
name|gimp_color_profile_new_linear_from_color_profile
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfile
modifier|*
name|gimp_color_profile_new_from_file
parameter_list|(
name|GFile
modifier|*
name|file
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
modifier|*
name|gimp_color_profile_new_from_icc_profile
parameter_list|(
specifier|const
name|guint8
modifier|*
name|data
parameter_list|,
name|gsize
name|length
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
modifier|*
name|gimp_color_profile_new_from_lcms_profile
parameter_list|(
name|gpointer
name|lcms_profile
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|guint8
modifier|*
name|gimp_color_profile_get_icc_profile
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|,
name|gsize
modifier|*
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|gimp_color_profile_get_lcms_profile
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_color_profile_get_description
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_color_profile_get_manufacturer
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_color_profile_get_model
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_color_profile_get_copyright
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_color_profile_get_label
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_color_profile_get_summary
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_color_profile_is_equal
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile1
parameter_list|,
name|GimpColorProfile
modifier|*
name|profile2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_color_profile_is_rgb
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_color_profile_is_gray
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_color_profile_is_cmyk
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_color_profile_is_linear
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_color_profile_get_format
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|guint32
modifier|*
name|lcms_format
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
comment|/* __GIMP_COLOR_PROFILE_H__ */
end_comment

end_unit

