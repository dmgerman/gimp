begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * Thumbnail handling according to the Thumbnail Managing Standard.  * http://triq.net/~pearl/thumbnail-spec/  *  * Copyright (C) 2001-2004  Sven Neumann<sven@gimp.org>  *                          Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_THUMBNAIL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_THUMBNAIL_H__
define|#
directive|define
name|__GIMP_THUMBNAIL_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_THUMBNAIL
define|#
directive|define
name|GIMP_TYPE_THUMBNAIL
value|(gimp_thumbnail_get_type ())
end_define

begin_define
DECL|macro|GIMP_THUMBNAIL (obj)
define|#
directive|define
name|GIMP_THUMBNAIL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_THUMBNAIL, GimpThumbnail))
end_define

begin_define
DECL|macro|GIMP_THUMBNAIL_CLASS (klass)
define|#
directive|define
name|GIMP_THUMBNAIL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_THUMBNAIL, GimpThumbnailClass))
end_define

begin_define
DECL|macro|GIMP_IS_THUMBNAIL (obj)
define|#
directive|define
name|GIMP_IS_THUMBNAIL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_THUMBNAIL))
end_define

begin_define
DECL|macro|GIMP_IS_THUMBNAIL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_THUMBNAIL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_THUMBNAIL))
end_define

begin_define
DECL|macro|GIMP_THUMBNAIL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_THUMBNAIL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_THUMBNAIL, GimpThumbnailClass))
end_define

begin_typedef
DECL|typedef|GimpThumbnailClass
typedef|typedef
name|struct
name|_GimpThumbnailClass
name|GimpThumbnailClass
typedef|;
end_typedef

begin_comment
comment|/**  * GimpThumbnail:  *  * All members of #GimpThumbnail are private and should only be accessed  * using object properties.  **/
end_comment

begin_struct
DECL|struct|_GimpThumbnail
struct|struct
name|_GimpThumbnail
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
comment|/*< private>*/
DECL|member|image_state
name|GimpThumbState
name|image_state
decl_stmt|;
DECL|member|image_uri
name|gchar
modifier|*
name|image_uri
decl_stmt|;
DECL|member|image_filename
name|gchar
modifier|*
name|image_filename
decl_stmt|;
DECL|member|image_filesize
name|gint64
name|image_filesize
decl_stmt|;
DECL|member|image_mtime
name|gint64
name|image_mtime
decl_stmt|;
DECL|member|image_not_found_errno
name|gint
name|image_not_found_errno
decl_stmt|;
DECL|member|image_width
name|gint
name|image_width
decl_stmt|;
DECL|member|image_height
name|gint
name|image_height
decl_stmt|;
DECL|member|image_type
name|gchar
modifier|*
name|image_type
decl_stmt|;
DECL|member|image_num_layers
name|gint
name|image_num_layers
decl_stmt|;
DECL|member|thumb_state
name|GimpThumbState
name|thumb_state
decl_stmt|;
DECL|member|thumb_size
name|GimpThumbSize
name|thumb_size
decl_stmt|;
DECL|member|thumb_filename
name|gchar
modifier|*
name|thumb_filename
decl_stmt|;
DECL|member|thumb_filesize
name|gint64
name|thumb_filesize
decl_stmt|;
DECL|member|thumb_mtime
name|gint64
name|thumb_mtime
decl_stmt|;
DECL|member|image_mimetype
name|gchar
modifier|*
name|image_mimetype
decl_stmt|;
DECL|member|_reserved_2
name|gpointer
name|_reserved_2
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpThumbnailClass
struct|struct
name|_GimpThumbnailClass
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
name|gimp_thumbnail_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpThumbnail
modifier|*
name|gimp_thumbnail_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_thumbnail_set_uri
parameter_list|(
name|GimpThumbnail
modifier|*
name|thumbnail
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_thumbnail_set_filename
parameter_list|(
name|GimpThumbnail
modifier|*
name|thumbnail
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
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
name|gimp_thumbnail_set_from_thumb
parameter_list|(
name|GimpThumbnail
modifier|*
name|thumbnail
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpThumbState
name|gimp_thumbnail_peek_image
parameter_list|(
name|GimpThumbnail
modifier|*
name|thumbnail
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpThumbState
name|gimp_thumbnail_peek_thumb
parameter_list|(
name|GimpThumbnail
modifier|*
name|thumbnail
parameter_list|,
name|GimpThumbSize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpThumbState
name|gimp_thumbnail_check_thumb
parameter_list|(
name|GimpThumbnail
modifier|*
name|thumbnail
parameter_list|,
name|GimpThumbSize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkPixbuf
modifier|*
name|gimp_thumbnail_load_thumb
parameter_list|(
name|GimpThumbnail
modifier|*
name|thumbnail
parameter_list|,
name|GimpThumbSize
name|size
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
name|gimp_thumbnail_save_thumb
parameter_list|(
name|GimpThumbnail
modifier|*
name|thumbnail
parameter_list|,
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
specifier|const
name|gchar
modifier|*
name|software
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
name|gimp_thumbnail_save_thumb_local
parameter_list|(
name|GimpThumbnail
modifier|*
name|thumbnail
parameter_list|,
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
specifier|const
name|gchar
modifier|*
name|software
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
name|gimp_thumbnail_save_failure
parameter_list|(
name|GimpThumbnail
modifier|*
name|thumbnail
parameter_list|,
specifier|const
name|gchar
modifier|*
name|software
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
name|gimp_thumbnail_delete_failure
parameter_list|(
name|GimpThumbnail
modifier|*
name|thumbnail
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_thumbnail_delete_others
parameter_list|(
name|GimpThumbnail
modifier|*
name|thumbnail
parameter_list|,
name|GimpThumbSize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_thumbnail_has_failed
parameter_list|(
name|GimpThumbnail
modifier|*
name|thumbnail
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
comment|/* __GIMP_THUMBNAIL_H__ */
end_comment

end_unit

