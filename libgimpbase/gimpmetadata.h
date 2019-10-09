begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMPBASE - The GIMP Basic Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmetadata.h  * Copyright (C) 2013 Hartmut Kuhse<hartmutkuhse@src.gnome.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_METADATA_H__
end_ifndef

begin_define
DECL|macro|__GIMP_METADATA_H__
define|#
directive|define
name|__GIMP_METADATA_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_METADATA
define|#
directive|define
name|GIMP_TYPE_METADATA
value|(gimp_metadata_get_type ())
end_define

begin_define
DECL|macro|GIMP_METADATA (obj)
define|#
directive|define
name|GIMP_METADATA
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_METADATA, GimpMetadata))
end_define

begin_define
DECL|macro|GIMP_METADATA_CLASS (klass)
define|#
directive|define
name|GIMP_METADATA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_METADATA, GimpMetadataClass))
end_define

begin_define
DECL|macro|GIMP_IS_METADATA (obj)
define|#
directive|define
name|GIMP_IS_METADATA
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_METADATA))
end_define

begin_define
DECL|macro|GIMP_IS_METADATA_CLASS (klass)
define|#
directive|define
name|GIMP_IS_METADATA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_METADATA))
end_define

begin_define
DECL|macro|GIMP_METADATA_GET_CLASS (obj)
define|#
directive|define
name|GIMP_METADATA_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_METADATA, GimpMetadataClass))
end_define

begin_comment
comment|/**  * GimpMetadataLoadFlags:  * @GIMP_METADATA_LOAD_COMMENT:     Load the comment  * @GIMP_METADATA_LOAD_RESOLUTION:  Load the resolution  * @GIMP_METADATA_LOAD_ORIENTATION: Load the orientation (rotation)  * @GIMP_METADATA_LOAD_COLORSPACE:  Load the colorspace  * @GIMP_METADATA_LOAD_ALL:         Load all of the above  *  * What metadata to load when importing images.  **/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b97a1b40103
block|{
DECL|enumerator|GIMP_METADATA_LOAD_COMMENT
name|GIMP_METADATA_LOAD_COMMENT
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_METADATA_LOAD_RESOLUTION
name|GIMP_METADATA_LOAD_RESOLUTION
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_METADATA_LOAD_ORIENTATION
name|GIMP_METADATA_LOAD_ORIENTATION
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_METADATA_LOAD_COLORSPACE
name|GIMP_METADATA_LOAD_COLORSPACE
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_METADATA_LOAD_ALL
name|GIMP_METADATA_LOAD_ALL
init|=
literal|0xffffffff
DECL|typedef|GimpMetadataLoadFlags
block|}
name|GimpMetadataLoadFlags
typedef|;
end_typedef

begin_comment
comment|/**  * GimpMetadataSaveFlags:  * @GIMP_METADATA_SAVE_EXIF:          Save EXIF  * @GIMP_METADATA_SAVE_XMP:           Save XMP  * @GIMP_METADATA_SAVE_IPTC:          Save IPTC  * @GIMP_METADATA_SAVE_THUMBNAIL:     Save a thumbnail of the image  * @GIMP_METADATA_SAVE_COLOR_PROFILE: Save the image's color profile  *                                    Since: 2.10.10  * @GIMP_METADATA_SAVE_COMMENT:       Save the image's comment  *                                    Since: 3.0  * @GIMP_METADATA_SAVE_ALL:           Save all of the above  *  * What kinds of metadata to save when exporting images.  **/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b97a1b40203
block|{
DECL|enumerator|GIMP_METADATA_SAVE_EXIF
name|GIMP_METADATA_SAVE_EXIF
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_METADATA_SAVE_XMP
name|GIMP_METADATA_SAVE_XMP
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_METADATA_SAVE_IPTC
name|GIMP_METADATA_SAVE_IPTC
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_METADATA_SAVE_THUMBNAIL
name|GIMP_METADATA_SAVE_THUMBNAIL
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_METADATA_SAVE_COLOR_PROFILE
name|GIMP_METADATA_SAVE_COLOR_PROFILE
init|=
literal|1
operator|<<
literal|4
block|,
DECL|enumerator|GIMP_METADATA_SAVE_COMMENT
name|GIMP_METADATA_SAVE_COMMENT
init|=
literal|1
operator|<<
literal|5
block|,
DECL|enumerator|GIMP_METADATA_SAVE_ALL
name|GIMP_METADATA_SAVE_ALL
init|=
literal|0xffffffff
DECL|typedef|GimpMetadataSaveFlags
block|}
name|GimpMetadataSaveFlags
typedef|;
end_typedef

begin_comment
comment|/**  * GimpMetadataColorspace:  * @GIMP_METADATA_COLORSPACE_UNSPECIFIED:  Unspecified  * @GIMP_METADATA_COLORSPACE_UNCALIBRATED: Uncalibrated  * @GIMP_METADATA_COLORSPACE_SRGB:         sRGB  * @GIMP_METADATA_COLORSPACE_ADOBERGB:     Adobe RGB  *  * Well-defined colorspace information available from metadata  **/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b97a1b40303
block|{
DECL|enumerator|GIMP_METADATA_COLORSPACE_UNSPECIFIED
name|GIMP_METADATA_COLORSPACE_UNSPECIFIED
block|,
DECL|enumerator|GIMP_METADATA_COLORSPACE_UNCALIBRATED
name|GIMP_METADATA_COLORSPACE_UNCALIBRATED
block|,
DECL|enumerator|GIMP_METADATA_COLORSPACE_SRGB
name|GIMP_METADATA_COLORSPACE_SRGB
block|,
DECL|enumerator|GIMP_METADATA_COLORSPACE_ADOBERGB
name|GIMP_METADATA_COLORSPACE_ADOBERGB
DECL|typedef|GimpMetadataColorspace
block|}
name|GimpMetadataColorspace
typedef|;
end_typedef

begin_decl_stmt
name|GType
name|gimp_metadata_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpMetadata
modifier|*
name|gimp_metadata_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpMetadata
modifier|*
name|gimp_metadata_duplicate
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpMetadata
modifier|*
name|gimp_metadata_deserialize
parameter_list|(
specifier|const
name|gchar
modifier|*
name|metadata_xml
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_metadata_serialize
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_metadata_get_guid
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_metadata_add_xmp_history
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
name|gchar
modifier|*
name|state_status
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpMetadata
modifier|*
name|gimp_metadata_load_from_file
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
name|gboolean
name|gimp_metadata_save_to_file
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
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
name|gboolean
name|gimp_metadata_set_from_exif
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
specifier|const
name|guchar
modifier|*
name|exif_data
parameter_list|,
name|gint
name|exif_data_length
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
name|gimp_metadata_set_from_iptc
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
specifier|const
name|guchar
modifier|*
name|iptc_data
parameter_list|,
name|gint
name|iptc_data_length
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
name|gimp_metadata_set_from_xmp
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
specifier|const
name|guchar
modifier|*
name|xmp_data
parameter_list|,
name|gint
name|xmp_data_length
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
name|gimp_metadata_set_pixel_size
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_metadata_set_bits_per_sample
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
name|gint
name|bits_per_sample
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_metadata_get_resolution
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
name|gdouble
modifier|*
name|xres
parameter_list|,
name|gdouble
modifier|*
name|yres
parameter_list|,
name|GimpUnit
modifier|*
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_metadata_set_resolution
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|yres
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpMetadataColorspace
name|gimp_metadata_get_colorspace
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_metadata_set_colorspace
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
name|GimpMetadataColorspace
name|colorspace
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_metadata_is_tag_supported
parameter_list|(
specifier|const
name|gchar
modifier|*
name|tag
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_type
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
comment|/* __GIMP_METADATA_H__ */
end_comment

end_unit

