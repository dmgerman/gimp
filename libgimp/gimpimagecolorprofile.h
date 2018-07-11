begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpimagecolorprofile.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
name|__GIMP_IMAGE_COLOR_PROFILE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_COLOR_PROFILE_H__
define|#
directive|define
name|__GIMP_IMAGE_COLOR_PROFILE_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|GimpColorProfile
modifier|*
name|gimp_image_get_color_profile
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_color_profile
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfile
modifier|*
name|gimp_image_get_effective_color_profile
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_convert_color_profile
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpColorProfile
modifier|*
name|profile
parameter_list|,
name|GimpColorRenderingIntent
name|intent
parameter_list|,
name|gboolean
name|bpc
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
comment|/* __GIMP_IMAGE_COLOR_PROFILE_H__ */
end_comment

end_unit

