begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpimage.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_IMAGE
define|#
directive|define
name|GIMP_TYPE_IMAGE
value|(gimp_image_get_type ())
end_define

begin_define
DECL|macro|GIMP_IMAGE (obj)
define|#
directive|define
name|GIMP_IMAGE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_IMAGE, GimpImage))
end_define

begin_define
DECL|macro|GIMP_IMAGE_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_IMAGE, GimpImageClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE (obj)
define|#
directive|define
name|GIMP_IS_IMAGE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_IMAGE))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGE))
end_define

begin_define
DECL|macro|GIMP_IMAGE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_IMAGE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_IMAGE, GimpImageClass))
end_define

begin_typedef
DECL|typedef|GimpImageClass
typedef|typedef
name|struct
name|_GimpImageClass
name|GimpImageClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpImagePrivate
typedef|typedef
name|struct
name|_GimpImagePrivate
name|GimpImagePrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImage
struct|struct
name|_GimpImage
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpImagePrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpImageClass
struct|struct
name|_GimpImageClass
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
DECL|member|_gimp_reserved5
name|void
function_decl|(
modifier|*
name|_gimp_reserved5
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved6
name|void
function_decl|(
modifier|*
name|_gimp_reserved6
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved7
name|void
function_decl|(
modifier|*
name|_gimp_reserved7
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved8
name|void
function_decl|(
modifier|*
name|_gimp_reserved8
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
name|gimp_image_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gint32
name|gimp_image_get_id
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
name|gimp_image_get_by_id
parameter_list|(
name|gint32
name|image_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
modifier|*
name|gimp_get_images
parameter_list|(
name|gint
modifier|*
name|num_images
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_list_images
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DEPRECATED_REPLACE_NEW_API
end_ifndef

begin_function_decl
name|GimpLayer
modifier|*
modifier|*
name|gimp_image_get_layers
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
modifier|*
name|num_layers
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpChannel
modifier|*
modifier|*
name|gimp_image_get_channels
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
modifier|*
name|num_channels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVectors
modifier|*
modifier|*
name|gimp_image_get_vectors
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
modifier|*
name|num_vectors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_image_list_layers
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_image_list_channels
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_image_list_vectors
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_image_get_colormap
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|num_colors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_image_get_thumbnail_data
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|GdkPixbuf
modifier|*
name|gimp_image_get_thumbnail
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpPixbufTransparency
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpMetadata
modifier|*
name|gimp_image_get_metadata
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_metadata
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpMetadata
modifier|*
name|metadata
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
DECL|macro|gimp_image_get_layers
define|#
directive|define
name|gimp_image_get_layers
value|gimp_image_get_layers_deprecated
end_define

begin_define
DECL|macro|gimp_image_get_colormap
define|#
directive|define
name|gimp_image_get_colormap
value|gimp_image_get_colormap_deprecated
end_define

begin_define
DECL|macro|gimp_image_set_colormap
define|#
directive|define
name|gimp_image_set_colormap
value|gimp_image_set_colormap_deprecated
end_define

begin_define
DECL|macro|gimp_image_get_metadata
define|#
directive|define
name|gimp_image_get_metadata
value|gimp_image_get_metadata_deprecated
end_define

begin_define
DECL|macro|gimp_image_set_metadata
define|#
directive|define
name|gimp_image_set_metadata
value|gimp_image_set_metadata_deprecated
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DEPRECATED_REPLACE_NEW_API */
end_comment

begin_function_decl
name|gint
modifier|*
name|gimp_image_get_layers_deprecated
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint
modifier|*
name|num_layers
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_image_get_colormap_deprecated
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint
modifier|*
name|num_colors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_colormap_deprecated
parameter_list|(
name|gint32
name|image_id
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
name|GimpMetadata
modifier|*
name|gimp_image_get_metadata_deprecated
parameter_list|(
name|gint32
name|image_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_metadata_deprecated
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|GimpMetadata
modifier|*
name|metadata
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

