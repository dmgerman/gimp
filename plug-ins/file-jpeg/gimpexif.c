begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*  * EXIF-handling code for the metadata library.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_EXIF
end_ifdef

begin_include
include|#
directive|include
file|<libexif/exif-data.h>
end_include

begin_include
include|#
directive|include
file|<libexif/exif-content.h>
end_include

begin_include
include|#
directive|include
file|<libexif/exif-utils.h>
end_include

begin_include
include|#
directive|include
file|"gimpexif.h"
end_include

begin_comment
comment|/*  * gimp_metadata_store_exif:  * @image_ID:    the GIMP image to work on.  * @exif_data:   the Exif data that is to be stored.  *  * This function is supposed to load the "gimp-metadata" parasite  * (which is in XMP format), parse it, add the exif information,  * reformat it into XMP, and store the result as the new parasite.  * The infrastructure to do this is not yet available, so for the  * moment it does something much simpler -- it calls upon libexif  * to serialize the exif data, and stores the result in a parasite  * called "exif-data".  */
end_comment

begin_function
DECL|function|gimp_metadata_store_exif (gint32 image_ID,ExifData * exif_data)
name|void
name|gimp_metadata_store_exif
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|ExifData
modifier|*
name|exif_data
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
init|=
name|NULL
decl_stmt|;
name|guchar
modifier|*
name|exif_buf
init|=
name|NULL
decl_stmt|;
name|guint
name|exif_buf_len
init|=
literal|0
decl_stmt|;
name|exif_data_save_data
argument_list|(
name|exif_data
argument_list|,
operator|&
name|exif_buf
argument_list|,
operator|&
name|exif_buf_len
argument_list|)
expr_stmt|;
if|if
condition|(
name|exif_buf_len
operator|>
name|EXIF_HEADER_SIZE
condition|)
block|{
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"exif-data"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|exif_buf_len
argument_list|,
name|exif_buf
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
argument_list|(
name|image_ID
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"plug-in-metadata-decode-exif"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|exif_data
operator|->
name|size
argument_list|,
name|GIMP_PDB_INT8ARRAY
argument_list|,
name|exif_data
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|!=
name|GIMP_PDB_SUCCESS
condition|)
name|g_warning
argument_list|(
literal|"JPEG Exif -> XMP Merge failed"
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|exif_buf
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * gimp_metadata_generate_exif:  * @image_ID:   the ID of the GIMP image to work on.  *  * This function is supposed to load the "gimp-metadata" parasite  * (which is a block of XMP info), parse it, extract the exif  * values, and build an ExifData structure from them.  * The infrastructure to do this is not yet available, so for the  * moment it does something much simpler -- it loads the "exif-data"  * parasite (which is a serialized representation of the exif data),  * and calls upon libexif to parse it into an ExifData struct.  *  * returns: The reconstructed exif data, or NULL if none exists.  */
end_comment

begin_function
name|ExifData
modifier|*
DECL|function|gimp_metadata_generate_exif (gint32 image_ID)
name|gimp_metadata_generate_exif
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
name|ExifData
modifier|*
name|exif_data
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
init|=
name|gimp_image_parasite_find
argument_list|(
name|image_ID
argument_list|,
literal|"exif-data"
argument_list|)
decl_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|exif_data
operator|=
name|exif_data_new_from_data
argument_list|(
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
return|return
name|exif_data
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*  * gimp_exif_content_get_value:  * @content:   ExifContent block from which to get value  * @tag:       Tag whose value to get  * @value:     Place to put the result  * @maxlen:    Maximum size of returned string  *  * This function is a wrapper around the libexif function  * exif_content_get_value(), necessary to deal with an incompatible  * API change.  It looks up the value of the specifed tag,  * returning the result as a human-readable string.  Note that  * @value must be pre-allocated.  */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_exif_content_get_value (ExifContent * content,ExifTag tag,gchar * value,gint maxlen)
name|gimp_exif_content_get_value
parameter_list|(
name|ExifContent
modifier|*
name|content
parameter_list|,
name|ExifTag
name|tag
parameter_list|,
name|gchar
modifier|*
name|value
parameter_list|,
name|gint
name|maxlen
parameter_list|)
block|{
name|ExifEntry
modifier|*
name|entry
init|=
name|exif_content_get_entry
argument_list|(
name|content
argument_list|,
name|tag
argument_list|)
decl_stmt|;
if|if
condition|(
name|entry
condition|)
return|return
name|exif_entry_get_value
argument_list|(
name|entry
argument_list|,
name|value
argument_list|,
name|maxlen
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*  * gimp_exif_data_remove_entry:  * @data:      ExifData pointer  * @ifd:       Index of the ifd holding the entry to be removed  * @tag:       Tag of the entry to be removed  *  * This is a convenience function for removing a specified  * entry from an exif data structure.  If no such entry  * exists, the function returns without doing anything.  */
end_comment

begin_function
name|void
DECL|function|gimp_exif_data_remove_entry (ExifData * exif_data,ExifIfd ifd,ExifTag tag)
name|gimp_exif_data_remove_entry
parameter_list|(
name|ExifData
modifier|*
name|exif_data
parameter_list|,
name|ExifIfd
name|ifd
parameter_list|,
name|ExifTag
name|tag
parameter_list|)
block|{
name|ExifEntry
modifier|*
name|entry
init|=
name|exif_content_get_entry
argument_list|(
name|exif_data
operator|->
name|ifd
index|[
name|ifd
index|]
argument_list|,
name|tag
argument_list|)
decl_stmt|;
if|if
condition|(
name|entry
condition|)
name|exif_content_remove_entry
argument_list|(
name|exif_data
operator|->
name|ifd
index|[
name|ifd
index|]
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_EXIF */
end_comment

end_unit

