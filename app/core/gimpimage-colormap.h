begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattisbvf  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_COLORMAP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_COLORMAP_H__
define|#
directive|define
name|__GIMP_IMAGE_COLORMAP_H__
end_define

begin_define
DECL|macro|GIMP_IMAGE_COLORMAP_SIZE
define|#
directive|define
name|GIMP_IMAGE_COLORMAP_SIZE
value|768
end_define

begin_function_decl
name|void
name|gimp_image_colormap_init
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_colormap_dispose
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_colormap_free
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPalette
modifier|*
name|gimp_image_get_colormap_palette
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|guchar
modifier|*
name|gimp_image_get_colormap
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_colormap_size
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
name|gimp_image_set_colormap
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|guchar
modifier|*
name|colormap
parameter_list|,
name|gint
name|n_colors
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_get_colormap_entry
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|color_index
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_colormap_entry
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|color_index
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_add_colormap_entry
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_COLORMAP_H__ */
end_comment

end_unit

