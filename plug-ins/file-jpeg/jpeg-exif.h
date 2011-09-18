begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__JPEG_EXIF_H__
end_ifndef

begin_define
DECL|macro|__JPEG_EXIF_H__
define|#
directive|define
name|__JPEG_EXIF_H__
end_define

begin_decl_stmt
specifier|extern
name|ExifData
modifier|*
name|exif_data
decl_stmt|;
end_decl_stmt

begin_function_decl
name|ExifData
modifier|*
name|jpeg_exif_data_new_from_file
parameter_list|(
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
name|gint
name|jpeg_exif_get_orientation
parameter_list|(
name|ExifData
modifier|*
name|exif_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|jpeg_exif_get_resolution
parameter_list|(
name|ExifData
modifier|*
name|exif_data
parameter_list|,
name|gdouble
modifier|*
name|xresolution
parameter_list|,
name|gdouble
modifier|*
name|yresolution
parameter_list|,
name|gint
modifier|*
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|jpeg_setup_exif_for_save
parameter_list|(
name|ExifData
modifier|*
name|exif_data
parameter_list|,
specifier|const
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|jpeg_exif_rotate
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|jpeg_exif_rotate_query
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __JPEG_EXIF_H__ */
end_comment

end_unit

