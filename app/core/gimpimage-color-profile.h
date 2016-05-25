begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimage-color-profile.h  * Copyright (C) 2015 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_COLOR_PROFILE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_COLOR_PROFILE_H__
define|#
directive|define
name|__GIMP_IMAGE_COLOR_PROFILE_H__
end_define

begin_define
DECL|macro|GIMP_ICC_PROFILE_PARASITE_NAME
define|#
directive|define
name|GIMP_ICC_PROFILE_PARASITE_NAME
value|"icc-profile"
end_define

begin_function_decl
name|gboolean
name|gimp_image_get_is_color_managed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_is_color_managed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|is_color_managed
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_validate_icc_parasite
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|icc_parasite
parameter_list|,
name|gboolean
modifier|*
name|is_builtin
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
name|GimpParasite
modifier|*
name|gimp_image_get_icc_parasite
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_icc_parasite
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|icc_parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_validate_icc_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|guint8
modifier|*
name|data
parameter_list|,
name|gsize
name|length
parameter_list|,
name|gboolean
modifier|*
name|is_builtin
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
name|gimp_image_get_icc_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gsize
modifier|*
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_icc_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
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
name|gboolean
name|gimp_image_validate_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpColorProfile
modifier|*
name|profile
parameter_list|,
name|gboolean
modifier|*
name|is_builtin
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
name|gimp_image_get_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpColorProfile
modifier|*
name|profile
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_validate_color_profile_by_format
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|GimpColorProfile
modifier|*
name|profile
parameter_list|,
name|gboolean
modifier|*
name|is_builtin
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
name|gimp_image_get_builtin_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_convert_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|,
name|GimpColorRenderingIntent
name|intent
parameter_list|,
name|gboolean
name|bpc
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_import_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gboolean
name|interactive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorTransform
modifier|*
name|gimp_image_get_color_transform_to_srgb_u8
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorTransform
modifier|*
name|gimp_image_get_color_transform_from_srgb_u8
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorTransform
modifier|*
name|gimp_image_get_color_transform_to_srgb_double
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorTransform
modifier|*
name|gimp_image_get_color_transform_from_srgb_double
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_color_profile_pixel_to_srgb
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|Babl
modifier|*
name|pixel_format
parameter_list|,
name|gpointer
name|pixel
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_color_profile_srgb_to_pixel
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
specifier|const
name|Babl
modifier|*
name|pixel_format
parameter_list|,
name|gpointer
name|pixel
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  internal API, to be called only from gimpimage.c  */
end_comment

begin_function_decl
name|void
name|_gimp_image_free_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_image_update_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|icc_parasite
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_COLOR_PROFILE_H__ */
end_comment

end_unit

