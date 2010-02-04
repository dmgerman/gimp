begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_QUICK_MASK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_QUICK_MASK_H__
define|#
directive|define
name|__GIMP_IMAGE_QUICK_MASK_H__
end_define

begin_comment
comment|/*  don't change this string, it's used to identify the Quick Mask  *  when opening files.  */
end_comment

begin_define
DECL|macro|GIMP_IMAGE_QUICK_MASK_NAME
define|#
directive|define
name|GIMP_IMAGE_QUICK_MASK_NAME
value|"Qmask"
end_define

begin_function_decl
name|void
name|gimp_image_set_quick_mask_state
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_get_quick_mask_state
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_quick_mask_color
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_get_quick_mask_color
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_image_get_quick_mask
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_quick_mask_invert
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_get_quick_mask_inverted
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_QUICK_MASK_H__ */
end_comment

end_unit

