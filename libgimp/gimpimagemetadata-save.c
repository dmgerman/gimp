begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpimagemetadata-save.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<sys/time.h>
end_include

begin_include
include|#
directive|include
file|<gexiv2/gexiv2.h>
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagemetadata.h"
end_include

begin_include
include|#
directive|include
file|"libgimp-intl.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c0b75a80108
block|{
DECL|member|tag
name|gchar
modifier|*
name|tag
decl_stmt|;
DECL|member|type
name|gint
name|type
decl_stmt|;
DECL|typedef|XmpStructs
block|}
name|XmpStructs
typedef|;
end_typedef

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_image_metadata_save_prepare:  * @image:           The original image  * @mime_type:       The saved file's mime-type  * @suggested_flags: Suggested default values for the @flags passed to  *                   gimp_image_metadata_save_finish()  *  * Gets the image metadata for saving it using  * gimp_image_metadata_save_finish().  *  * The @suggested_flags are determined from what kind of metadata  * (Exif, XMP, ...) is actually present in the image and the preferences  * for metadata exporting.  * The calling application may still update @available_flags, for  * instance to follow the settings from a previous export in the same  * session, or a previous export of the same image. But it should not  * override the preferences without a good reason since it is a data  * leak.  *  * The suggested value for %GIMP_METADATA_SAVE_THUMBNAIL is determined by  * whether there was a thumbnail in the previously imported image.  *  * Returns: (transfer full): The image's metadata, prepared for saving.  *  * Since: 2.10  */
end_comment

begin_function
name|GimpMetadata
modifier|*
DECL|function|gimp_image_metadata_save_prepare (GimpImage * image,const gchar * mime_type,GimpMetadataSaveFlags * suggested_flags)
name|gimp_image_metadata_save_prepare
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_type
parameter_list|,
name|GimpMetadataSaveFlags
modifier|*
name|suggested_flags
parameter_list|)
block|{
name|GimpMetadata
modifier|*
name|metadata
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|mime_type
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|suggested_flags
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|suggested_flags
operator|=
name|GIMP_METADATA_SAVE_ALL
expr_stmt|;
name|metadata
operator|=
name|gimp_image_get_metadata
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata
condition|)
block|{
name|GDateTime
modifier|*
name|datetime
decl_stmt|;
specifier|const
name|GimpParasite
modifier|*
name|comment_parasite
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|comment
init|=
name|NULL
decl_stmt|;
name|gint
name|image_width
decl_stmt|;
name|gint
name|image_height
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gchar
name|buffer
index|[
literal|32
index|]
decl_stmt|;
name|GExiv2Metadata
modifier|*
name|g2metadata
init|=
name|GEXIV2_METADATA
argument_list|(
name|metadata
argument_list|)
decl_stmt|;
name|image_width
operator|=
name|gimp_image_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|image_height
operator|=
name|gimp_image_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|datetime
operator|=
name|g_date_time_new_now_local
argument_list|()
expr_stmt|;
name|comment_parasite
operator|=
name|gimp_image_get_parasite
argument_list|(
name|image
argument_list|,
literal|"gimp-comment"
argument_list|)
expr_stmt|;
if|if
condition|(
name|comment_parasite
condition|)
name|comment
operator|=
name|gimp_parasite_data
argument_list|(
name|comment_parasite
argument_list|)
expr_stmt|;
comment|/* Exif */
if|if
condition|(
operator|!
name|gimp_export_exif
argument_list|()
operator|||
operator|!
name|gexiv2_metadata_has_exif
argument_list|(
name|g2metadata
argument_list|)
condition|)
operator|*
name|suggested_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_EXIF
expr_stmt|;
if|if
condition|(
name|comment
condition|)
block|{
name|gexiv2_metadata_set_tag_string
argument_list|(
name|g2metadata
argument_list|,
literal|"Exif.Photo.UserComment"
argument_list|,
name|comment
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|g2metadata
argument_list|,
literal|"Exif.Image.ImageDescription"
argument_list|,
name|comment
argument_list|)
expr_stmt|;
block|}
name|g_snprintf
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|"%d:%02d:%02d %02d:%02d:%02d"
argument_list|,
name|g_date_time_get_year
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_month
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_day_of_month
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_hour
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_minute
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_second
argument_list|(
name|datetime
argument_list|)
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|g2metadata
argument_list|,
literal|"Exif.Image.DateTime"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|g2metadata
argument_list|,
literal|"Exif.Image.Software"
argument_list|,
name|PACKAGE_STRING
argument_list|)
expr_stmt|;
name|gimp_metadata_set_pixel_size
argument_list|(
name|metadata
argument_list|,
name|image_width
argument_list|,
name|image_height
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|gimp_metadata_set_resolution
argument_list|(
name|metadata
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|,
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
comment|/* XMP */
if|if
condition|(
operator|!
name|gimp_export_xmp
argument_list|()
operator|||
operator|!
name|gexiv2_metadata_has_xmp
argument_list|(
name|g2metadata
argument_list|)
condition|)
operator|*
name|suggested_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_XMP
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|g2metadata
argument_list|,
literal|"Xmp.dc.Format"
argument_list|,
name|mime_type
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_strcmp0
argument_list|(
name|mime_type
argument_list|,
literal|"image/tiff"
argument_list|)
condition|)
block|{
comment|/* TIFF specific XMP data */
name|g_snprintf
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|"%d"
argument_list|,
name|image_width
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|g2metadata
argument_list|,
literal|"Xmp.tiff.ImageWidth"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|"%d"
argument_list|,
name|image_height
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|g2metadata
argument_list|,
literal|"Xmp.tiff.ImageLength"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|"%d:%02d:%02d %02d:%02d:%02d"
argument_list|,
name|g_date_time_get_year
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_month
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_day_of_month
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_hour
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_minute
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_second
argument_list|(
name|datetime
argument_list|)
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|g2metadata
argument_list|,
literal|"Xmp.tiff.DateTime"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
block|}
comment|/* IPTC */
if|if
condition|(
operator|!
name|gimp_export_iptc
argument_list|()
operator|||
operator|!
name|gexiv2_metadata_has_iptc
argument_list|(
name|g2metadata
argument_list|)
condition|)
operator|*
name|suggested_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_IPTC
expr_stmt|;
name|g_snprintf
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|"%d-%d-%d"
argument_list|,
name|g_date_time_get_year
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_month
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_day_of_month
argument_list|(
name|datetime
argument_list|)
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|g2metadata
argument_list|,
literal|"Iptc.Application2.DateCreated"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|"%02d:%02d:%02d-%02d:%02d"
argument_list|,
name|g_date_time_get_hour
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_minute
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_second
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_hour
argument_list|(
name|datetime
argument_list|)
argument_list|,
name|g_date_time_get_minute
argument_list|(
name|datetime
argument_list|)
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|g2metadata
argument_list|,
literal|"Iptc.Application2.TimeCreated"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|g_date_time_unref
argument_list|(
name|datetime
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* At least initialize the returned flags with preferences defaults */
if|if
condition|(
operator|!
name|gimp_export_exif
argument_list|()
condition|)
operator|*
name|suggested_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_EXIF
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_export_xmp
argument_list|()
condition|)
operator|*
name|suggested_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_XMP
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_export_iptc
argument_list|()
condition|)
operator|*
name|suggested_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_IPTC
expr_stmt|;
block|}
comment|/* Thumbnail */
if|if
condition|(
name|FALSE
comment|/* FIXME if (original image had a thumbnail) */
condition|)
operator|*
name|suggested_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_THUMBNAIL
expr_stmt|;
comment|/* Color profile */
if|if
condition|(
operator|!
name|gimp_export_color_profile
argument_list|()
condition|)
operator|*
name|suggested_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_COLOR_PROFILE
expr_stmt|;
comment|/* Comment */
if|if
condition|(
operator|!
name|gimp_export_comment
argument_list|()
condition|)
operator|*
name|suggested_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_COMMENT
expr_stmt|;
return|return
name|metadata
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_metadata_copy_tag (GExiv2Metadata * src,GExiv2Metadata * dest,const gchar * tag)
name|gimp_image_metadata_copy_tag
parameter_list|(
name|GExiv2Metadata
modifier|*
name|src
parameter_list|,
name|GExiv2Metadata
modifier|*
name|dest
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tag
parameter_list|)
block|{
name|gchar
modifier|*
modifier|*
name|values
init|=
name|gexiv2_metadata_get_tag_multiple
argument_list|(
name|src
argument_list|,
name|tag
argument_list|)
decl_stmt|;
if|if
condition|(
name|values
condition|)
block|{
name|gexiv2_metadata_set_tag_multiple
argument_list|(
name|dest
argument_list|,
name|tag
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
name|values
argument_list|)
expr_stmt|;
name|g_strfreev
argument_list|(
name|values
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|value
init|=
name|gexiv2_metadata_get_tag_string
argument_list|(
name|src
argument_list|,
name|tag
argument_list|)
decl_stmt|;
if|if
condition|(
name|value
condition|)
block|{
name|gexiv2_metadata_set_tag_string
argument_list|(
name|dest
argument_list|,
name|tag
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_image_metadata_save_finish:  * @image:     The actually saved image  * @mime_type: The saved file's mime-type  * @metadata:  The metadata to write to @file  * @flags:     Flags to specify what of the metadata to save  * @file:      The file @image was saved to  * @error:     Return location for error message  *  * Saves the @metadata retrieved from the image with  * gimp_image_metadata_save_prepare() to @file, taking into account  * the passed @flags.  *  * Note that the @image passed to this function might be different  * from the image passed to gimp_image_metadata_save_prepare(), due  * to whatever file export conversion happened in the meantime  *  * Returns: Whether the save was successful.  *  * Since: 2.10  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_metadata_save_finish (GimpImage * image,const gchar * mime_type,GimpMetadata * metadata,GimpMetadataSaveFlags flags,GFile * file,GError ** error)
name|gimp_image_metadata_save_finish
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_type
parameter_list|,
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
name|GimpMetadataSaveFlags
name|flags
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
block|{
name|GimpMetadata
modifier|*
name|new_metadata
decl_stmt|;
name|GExiv2Metadata
modifier|*
name|new_g2metadata
decl_stmt|;
name|gboolean
name|support_exif
decl_stmt|;
name|gboolean
name|support_xmp
decl_stmt|;
name|gboolean
name|support_iptc
decl_stmt|;
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|mime_type
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GEXIV2_IS_METADATA
argument_list|(
name|metadata
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|flags
operator|&
operator|(
name|GIMP_METADATA_SAVE_EXIF
operator||
name|GIMP_METADATA_SAVE_XMP
operator||
name|GIMP_METADATA_SAVE_IPTC
operator||
name|GIMP_METADATA_SAVE_THUMBNAIL
operator|)
operator|)
condition|)
return|return
name|TRUE
return|;
comment|/* read metadata from saved file */
name|new_metadata
operator|=
name|gimp_metadata_load_from_file
argument_list|(
name|file
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|new_g2metadata
operator|=
name|GEXIV2_METADATA
argument_list|(
name|new_metadata
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|new_metadata
condition|)
return|return
name|FALSE
return|;
name|support_exif
operator|=
name|gexiv2_metadata_get_supports_exif
argument_list|(
name|new_g2metadata
argument_list|)
expr_stmt|;
name|support_xmp
operator|=
name|gexiv2_metadata_get_supports_xmp
argument_list|(
name|new_g2metadata
argument_list|)
expr_stmt|;
name|support_iptc
operator|=
name|gexiv2_metadata_get_supports_iptc
argument_list|(
name|new_g2metadata
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|flags
operator|&
name|GIMP_METADATA_SAVE_EXIF
operator|)
operator|&&
name|support_exif
condition|)
block|{
name|gchar
modifier|*
modifier|*
name|exif_data
init|=
name|gexiv2_metadata_get_exif_tags
argument_list|(
name|GEXIV2_METADATA
argument_list|(
name|metadata
argument_list|)
argument_list|)
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|exif_data
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|gexiv2_metadata_has_tag
argument_list|(
name|new_g2metadata
argument_list|,
name|exif_data
index|[
name|i
index|]
argument_list|)
operator|&&
name|gimp_metadata_is_tag_supported
argument_list|(
name|exif_data
index|[
name|i
index|]
argument_list|,
name|mime_type
argument_list|)
condition|)
block|{
name|gimp_image_metadata_copy_tag
argument_list|(
name|GEXIV2_METADATA
argument_list|(
name|metadata
argument_list|)
argument_list|,
name|new_g2metadata
argument_list|,
name|exif_data
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
block|}
name|g_strfreev
argument_list|(
name|exif_data
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|flags
operator|&
name|GIMP_METADATA_SAVE_XMP
operator|)
operator|&&
name|support_xmp
condition|)
block|{
specifier|static
specifier|const
name|XmpStructs
name|structlist
index|[]
init|=
block|{
block|{
literal|"Xmp.iptcExt.LocationCreated"
block|,
name|GEXIV2_STRUCTURE_XA_BAG
block|}
block|,
block|{
literal|"Xmp.iptcExt.LocationShown"
block|,
name|GEXIV2_STRUCTURE_XA_BAG
block|}
block|,
block|{
literal|"Xmp.iptcExt.ArtworkOrObject"
block|,
name|GEXIV2_STRUCTURE_XA_BAG
block|}
block|,
block|{
literal|"Xmp.iptcExt.RegistryId"
block|,
name|GEXIV2_STRUCTURE_XA_BAG
block|}
block|,
block|{
literal|"Xmp.xmpMM.History"
block|,
name|GEXIV2_STRUCTURE_XA_SEQ
block|}
block|,
block|{
literal|"Xmp.plus.ImageSupplier"
block|,
name|GEXIV2_STRUCTURE_XA_SEQ
block|}
block|,
block|{
literal|"Xmp.plus.ImageCreator"
block|,
name|GEXIV2_STRUCTURE_XA_SEQ
block|}
block|,
block|{
literal|"Xmp.plus.CopyrightOwner"
block|,
name|GEXIV2_STRUCTURE_XA_SEQ
block|}
block|,
block|{
literal|"Xmp.plus.Licensor"
block|,
name|GEXIV2_STRUCTURE_XA_SEQ
block|}
block|}
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|xmp_data
decl_stmt|;
name|struct
name|timeval
name|timer_usec
decl_stmt|;
name|gint64
name|timestamp_usec
decl_stmt|;
name|gchar
name|ts
index|[
literal|128
index|]
decl_stmt|;
name|gettimeofday
argument_list|(
operator|&
name|timer_usec
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|timestamp_usec
operator|=
operator|(
operator|(
name|gint64
operator|)
name|timer_usec
operator|.
name|tv_sec
operator|)
operator|*
literal|1000000ll
operator|+
operator|(
name|gint64
operator|)
name|timer_usec
operator|.
name|tv_usec
expr_stmt|;
name|g_snprintf
argument_list|(
name|ts
argument_list|,
sizeof|sizeof
argument_list|(
name|ts
argument_list|)
argument_list|,
literal|"%"
name|G_GINT64_FORMAT
argument_list|,
name|timestamp_usec
argument_list|)
expr_stmt|;
name|gimp_metadata_add_xmp_history
argument_list|(
name|metadata
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|GEXIV2_METADATA
argument_list|(
name|metadata
argument_list|)
argument_list|,
literal|"Xmp.GIMP.TimeStamp"
argument_list|,
name|ts
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|GEXIV2_METADATA
argument_list|(
name|metadata
argument_list|)
argument_list|,
literal|"Xmp.xmp.CreatorTool"
argument_list|,
name|N_
argument_list|(
literal|"GIMP 2.10"
argument_list|)
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|GEXIV2_METADATA
argument_list|(
name|metadata
argument_list|)
argument_list|,
literal|"Xmp.GIMP.Version"
argument_list|,
name|GIMP_VERSION
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|GEXIV2_METADATA
argument_list|(
name|metadata
argument_list|)
argument_list|,
literal|"Xmp.GIMP.API"
argument_list|,
name|GIMP_API_VERSION
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|GEXIV2_METADATA
argument_list|(
name|metadata
argument_list|)
argument_list|,
literal|"Xmp.GIMP.Platform"
argument_list|,
if|#
directive|if
name|defined
argument_list|(
name|_WIN32
argument_list|)
operator|||
name|defined
argument_list|(
name|__CYGWIN__
argument_list|)
operator|||
name|defined
argument_list|(
name|__MINGW32__
argument_list|)
literal|"Windows"
elif|#
directive|elif
name|defined
argument_list|(
name|__linux__
argument_list|)
literal|"Linux"
elif|#
directive|elif
name|defined
argument_list|(
name|__APPLE__
argument_list|)
operator|&&
name|defined
argument_list|(
name|__MACH__
argument_list|)
literal|"Mac OS"
elif|#
directive|elif
name|defined
argument_list|(
name|unix
argument_list|)
operator|||
name|defined
argument_list|(
name|__unix__
argument_list|)
operator|||
name|defined
argument_list|(
name|__unix
argument_list|)
literal|"Unix"
else|#
directive|else
literal|"Unknown"
endif|#
directive|endif
argument_list|)
expr_stmt|;
name|xmp_data
operator|=
name|gexiv2_metadata_get_xmp_tags
argument_list|(
name|GEXIV2_METADATA
argument_list|(
name|metadata
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Patch necessary structures */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|structlist
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|gexiv2_metadata_set_xmp_tag_struct
argument_list|(
name|GEXIV2_METADATA
argument_list|(
name|new_g2metadata
argument_list|)
argument_list|,
name|structlist
index|[
name|i
index|]
operator|.
name|tag
argument_list|,
name|structlist
index|[
name|i
index|]
operator|.
name|type
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|xmp_data
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|gexiv2_metadata_has_tag
argument_list|(
name|new_g2metadata
argument_list|,
name|xmp_data
index|[
name|i
index|]
argument_list|)
operator|&&
name|gimp_metadata_is_tag_supported
argument_list|(
name|xmp_data
index|[
name|i
index|]
argument_list|,
name|mime_type
argument_list|)
condition|)
block|{
name|gimp_image_metadata_copy_tag
argument_list|(
name|GEXIV2_METADATA
argument_list|(
name|metadata
argument_list|)
argument_list|,
name|new_g2metadata
argument_list|,
name|xmp_data
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
block|}
name|g_strfreev
argument_list|(
name|xmp_data
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|flags
operator|&
name|GIMP_METADATA_SAVE_IPTC
operator|)
operator|&&
name|support_iptc
condition|)
block|{
name|gchar
modifier|*
modifier|*
name|iptc_data
init|=
name|gexiv2_metadata_get_iptc_tags
argument_list|(
name|GEXIV2_METADATA
argument_list|(
name|metadata
argument_list|)
argument_list|)
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|iptc_data
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|gexiv2_metadata_has_tag
argument_list|(
name|new_g2metadata
argument_list|,
name|iptc_data
index|[
name|i
index|]
argument_list|)
operator|&&
name|gimp_metadata_is_tag_supported
argument_list|(
name|iptc_data
index|[
name|i
index|]
argument_list|,
name|mime_type
argument_list|)
condition|)
block|{
name|gimp_image_metadata_copy_tag
argument_list|(
name|GEXIV2_METADATA
argument_list|(
name|metadata
argument_list|)
argument_list|,
name|new_g2metadata
argument_list|,
name|iptc_data
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
block|}
name|g_strfreev
argument_list|(
name|iptc_data
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|flags
operator|&
name|GIMP_METADATA_SAVE_THUMBNAIL
condition|)
block|{
name|GdkPixbuf
modifier|*
name|thumb_pixbuf
decl_stmt|;
name|gchar
modifier|*
name|thumb_buffer
decl_stmt|;
name|gint
name|image_width
decl_stmt|;
name|gint
name|image_height
decl_stmt|;
name|gsize
name|count
decl_stmt|;
name|gint
name|thumbw
decl_stmt|;
name|gint
name|thumbh
decl_stmt|;
DECL|macro|EXIF_THUMBNAIL_SIZE
define|#
directive|define
name|EXIF_THUMBNAIL_SIZE
value|256
name|image_width
operator|=
name|gimp_image_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|image_height
operator|=
name|gimp_image_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_width
operator|>
name|image_height
condition|)
block|{
name|thumbw
operator|=
name|EXIF_THUMBNAIL_SIZE
expr_stmt|;
name|thumbh
operator|=
name|EXIF_THUMBNAIL_SIZE
operator|*
name|image_height
operator|/
name|image_width
expr_stmt|;
block|}
else|else
block|{
name|thumbh
operator|=
name|EXIF_THUMBNAIL_SIZE
expr_stmt|;
name|thumbw
operator|=
name|EXIF_THUMBNAIL_SIZE
operator|*
name|image_width
operator|/
name|image_height
expr_stmt|;
block|}
name|thumb_pixbuf
operator|=
name|gimp_image_get_thumbnail
argument_list|(
name|image
argument_list|,
name|thumbw
argument_list|,
name|thumbh
argument_list|,
name|GIMP_PIXBUF_KEEP_ALPHA
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdk_pixbuf_save_to_buffer
argument_list|(
name|thumb_pixbuf
argument_list|,
operator|&
name|thumb_buffer
argument_list|,
operator|&
name|count
argument_list|,
literal|"jpeg"
argument_list|,
name|NULL
argument_list|,
literal|"quality"
argument_list|,
literal|"75"
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gchar
name|buffer
index|[
literal|32
index|]
decl_stmt|;
name|gexiv2_metadata_set_exif_thumbnail_from_buffer
argument_list|(
name|new_g2metadata
argument_list|,
operator|(
name|guchar
operator|*
operator|)
name|thumb_buffer
argument_list|,
name|count
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|"%d"
argument_list|,
name|thumbw
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|new_g2metadata
argument_list|,
literal|"Exif.Thumbnail.ImageWidth"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|"%d"
argument_list|,
name|thumbh
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|new_g2metadata
argument_list|,
literal|"Exif.Thumbnail.ImageLength"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|new_g2metadata
argument_list|,
literal|"Exif.Thumbnail.BitsPerSample"
argument_list|,
literal|"8 8 8"
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|new_g2metadata
argument_list|,
literal|"Exif.Thumbnail.SamplesPerPixel"
argument_list|,
literal|"3"
argument_list|)
expr_stmt|;
name|gexiv2_metadata_set_tag_string
argument_list|(
name|new_g2metadata
argument_list|,
literal|"Exif.Thumbnail.PhotometricInterpretation"
argument_list|,
literal|"6"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|thumb_buffer
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|thumb_pixbuf
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|flags
operator|&
name|GIMP_METADATA_SAVE_COLOR_PROFILE
condition|)
block|{
comment|/* nothing to do, but if we ever need to modify metadata based        * on the exported color profile, this is probably the place to        * add it        */
block|}
if|if
condition|(
name|flags
operator|&
name|GIMP_METADATA_SAVE_COMMENT
condition|)
block|{
comment|/* nothing to do, blah blah */
block|}
name|success
operator|=
name|gimp_metadata_save_to_file
argument_list|(
name|new_metadata
argument_list|,
name|file
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|new_metadata
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

