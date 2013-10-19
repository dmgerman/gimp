begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpimage.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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

begin_function_decl
name|GimpMetadata
modifier|*
name|gimp_image_get_metadata
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_metadata
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpMetadata
modifier|*
name|metadata
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_get_colormap
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_set_colormap
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_get_item_position
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_raise_item
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_lower_item
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_raise_item_to_top
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_lower_item_to_bottom
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_get_item_position
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_raise_item
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_lower_item
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_get_item_position
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_raise_item
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_lower_item
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_raise_item_to_top
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_lower_item_to_bottom
argument_list|)
end_macro

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

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_get_parasite
argument_list|)
end_macro

begin_function_decl
name|GimpParasite
modifier|*
name|gimp_image_parasite_find
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_attach_parasite
argument_list|)
end_macro

begin_function_decl
name|gboolean
name|gimp_image_parasite_attach
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_detach_parasite
argument_list|)
end_macro

begin_function_decl
name|gboolean
name|gimp_image_parasite_detach
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_get_parasite_list
argument_list|)
end_macro

begin_function_decl
name|gboolean
name|gimp_image_parasite_list
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|num_parasites
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|parasites
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_image_attach_parasite
argument_list|)
end_macro

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

