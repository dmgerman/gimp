begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpimage.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_H__
define|#
directive|define
name|__GIMP_IMAGE_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|guchar
modifier|*
name|gimp_image_get_colormap
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|num_colors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_colormap
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|guchar
modifier|*
name|colormap
parameter_list|,
name|gint
name|num_colors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_image_get_thumbnail_data
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|bpp
parameter_list|)
function_decl|;
end_function_decl

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

begin_function_decl
name|guchar
modifier|*
name|gimp_image_get_cmap
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|num_colors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_cmap
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|guchar
modifier|*
name|cmap
parameter_list|,
name|gint
name|num_colors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_layer_position
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_raise_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_lower_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_raise_layer_to_top
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_lower_layer_to_bottom
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_channel_position
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|channel_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_raise_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|channel_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_lower_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|channel_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_vectors_position
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_raise_vectors
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_lower_vectors
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_raise_vectors_to_top
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_lower_vectors_to_bottom
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_attach_new_parasite
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|flags
parameter_list|,
name|gint
name|size
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DISABLE_DEPRECATED */
end_comment

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_H__ */
end_comment

end_unit

