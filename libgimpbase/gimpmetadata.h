begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPMETADATA_H__
end_ifndef

begin_define
DECL|macro|__GIMPMETADATA_H__
define|#
directive|define
name|__GIMPMETADATA_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_include
include|#
directive|include
file|<gexiv2/gexiv2.h>
end_include

begin_define
DECL|macro|TYPE_GIMP_METADATA
define|#
directive|define
name|TYPE_GIMP_METADATA
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
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_GIMP_METADATA, GimpMetadata))
end_define

begin_define
DECL|macro|GIMP_METADATA_CLASS (klass)
define|#
directive|define
name|GIMP_METADATA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_GIMP_METADATA, GimpMetadataClass))
end_define

begin_define
DECL|macro|IS_GIMP_METADATA (obj)
define|#
directive|define
name|IS_GIMP_METADATA
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_GIMP_METADATA))
end_define

begin_define
DECL|macro|IS_GIMP_METADATA_CLASS (klass)
define|#
directive|define
name|IS_GIMP_METADATA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_GIMP_METADATA))
end_define

begin_define
DECL|macro|GIMP_METADATA_GET_CLASS (obj)
define|#
directive|define
name|GIMP_METADATA_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_GIMP_METADATA, GimpMetadataClass))
end_define

begin_define
DECL|macro|GIMP_METADATA_GET_PRIVATE (obj)
define|#
directive|define
name|GIMP_METADATA_GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_PRIVATE ((obj), TYPE_GIMP_METADATA, GimpMetadataPrivate))
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2949126b0103
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

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2949126b0203
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
DECL|enumerator|GIMP_METADATA_SAVE_ALL
name|GIMP_METADATA_SAVE_ALL
init|=
literal|0xffffffff
DECL|typedef|GimpMetadataSaveFlags
block|}
name|GimpMetadataSaveFlags
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2949126b0303
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
name|gint
name|gimp_metadata_size
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
name|gimp_metadata_duplicate
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GHashTable
modifier|*
name|gimp_metadata_get_table
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_metadata_add_attribute
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
name|GimpAttribute
modifier|*
name|attribute
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpAttribute
modifier|*
name|gimp_metadata_get_attribute
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_metadata_remove_attribute
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_metadata_has_attribute
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_metadata_new_attribute
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|value
parameter_list|,
name|GimpAttributeValueType
name|type
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
name|GimpMetadata
modifier|*
name|gimp_metadata_deserialize
parameter_list|(
specifier|const
name|gchar
modifier|*
name|xml
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_metadata_print
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_metadata_to_xmp_packet
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_metadata_has_tag_type
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
name|GimpAttributeTagType
name|tag_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_metadata_iter_init
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
name|GList
modifier|*
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_metadata_iter_next
parameter_list|(
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
name|GimpAttribute
modifier|*
modifier|*
name|attribute
parameter_list|,
name|GList
modifier|*
modifier|*
name|prev
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

begin_comment
comment|//GimpMetadata *                            gimp_metadata_from_gexiv2metadata                        (GimpMetadata             *metadata,
end_comment

begin_comment
comment|//                                                                                                    GimpMetadata             *gexivdata);
end_comment

begin_comment
comment|//void                                      gimp_metadata_to_gexiv2metadata                          (GimpMetadata             *metadata,
end_comment

begin_comment
comment|//                                                                                                    GimpMetadata             *gexivdata,
end_comment

begin_comment
comment|//                                                                                                    const gchar              *mime_type);
end_comment

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

end_unit

