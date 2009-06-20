begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* exif-decode.c - decodes exif data and converts it to XMP  *  * Copyright (C) 2004-2005, RÃ³man Joost<romanofski@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libexif/exif-data.h>
end_include

begin_include
include|#
directive|include
file|"xmp-model.h"
end_include

begin_include
include|#
directive|include
file|"xmp-schemas.h"
end_include

begin_include
include|#
directive|include
file|"exif-decode.h"
end_include

begin_comment
comment|/* prototypes of local functions */
end_comment

begin_comment
comment|// static void         exif_iter_content           (XMPModel    *xmp_model,
end_comment

begin_comment
comment|//                                                 ExifData    *data);
end_comment

begin_function_decl
specifier|static
name|void
name|exif_foreach_content_cb
parameter_list|(
name|ExifContent
modifier|*
name|content
parameter_list|,
name|XMPModel
modifier|*
name|xmp_model
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|exif_foreach_entry_cb
parameter_list|(
name|ExifEntry
modifier|*
name|entry
parameter_list|,
name|XMPModel
modifier|*
name|xmp_model
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|gboolean
DECL|function|xmp_merge_from_exifbuffer (XMPModel * xmp_model,gint32 image_ID,GError ** error)
name|xmp_merge_from_exifbuffer
parameter_list|(
name|XMPModel
modifier|*
name|xmp_model
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|g_warning
argument_list|(
literal|"Found parasite, extracting exif"
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|exif_data
condition|)
block|{
name|exif_data_foreach_content
argument_list|(
name|exif_data
argument_list|,
operator|(
name|void
operator|*
operator|)
name|exif_foreach_content_cb
argument_list|,
name|xmp_model
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"\nSomething went wrong, when reading from buffer.\n"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|exif_foreach_content_cb (ExifContent * content,XMPModel * xmp_model)
name|exif_foreach_content_cb
parameter_list|(
name|ExifContent
modifier|*
name|content
parameter_list|,
name|XMPModel
modifier|*
name|xmp_model
parameter_list|)
block|{
name|exif_content_foreach_entry
argument_list|(
name|content
argument_list|,
operator|(
name|void
operator|*
operator|)
name|exif_foreach_entry_cb
argument_list|,
name|xmp_model
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|exif_foreach_entry_cb (ExifEntry * entry,XMPModel * xmp_model)
name|exif_foreach_entry_cb
parameter_list|(
name|ExifEntry
modifier|*
name|entry
parameter_list|,
name|XMPModel
modifier|*
name|xmp_model
parameter_list|)
block|{
name|g_printerr
argument_list|(
literal|"\nWuff! Wuff!:"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

