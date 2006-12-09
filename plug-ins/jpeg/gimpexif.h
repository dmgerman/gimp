begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * EXIF-handling code for the metadata library.  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_EXIF
end_ifdef

begin_define
DECL|macro|EXIF_HEADER_SIZE
define|#
directive|define
name|EXIF_HEADER_SIZE
value|8
end_define

begin_function_decl
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
function_decl|;
end_function_decl

begin_function_decl
name|ExifData
modifier|*
name|gimp_metadata_generate_exif
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
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
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_exif_entry_get_value
parameter_list|(
name|ExifEntry
modifier|*
name|entry
parameter_list|,
name|gchar
modifier|*
name|value
parameter_list|,
name|guint
name|maxlen
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_EXIF */
end_comment

end_unit

