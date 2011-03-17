begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_define
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-jpeg-load"
end_define

begin_define
DECL|macro|LOAD_THUMB_PROC
define|#
directive|define
name|LOAD_THUMB_PROC
value|"file-jpeg-load-thumb"
end_define

begin_define
DECL|macro|SAVE_PROC
define|#
directive|define
name|SAVE_PROC
value|"file-jpeg-save"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-jpeg"
end_define

begin_comment
comment|/* headers used in some APPn markers */
end_comment

begin_define
DECL|macro|JPEG_APP_HEADER_EXIF
define|#
directive|define
name|JPEG_APP_HEADER_EXIF
value|"Exif\0\0"
end_define

begin_define
DECL|macro|JPEG_APP_HEADER_XMP
define|#
directive|define
name|JPEG_APP_HEADER_XMP
value|"http://ns.adobe.com/xap/1.0/"
end_define

begin_typedef
DECL|struct|my_error_mgr
typedef|typedef
struct|struct
name|my_error_mgr
block|{
DECL|member|pub
name|struct
name|jpeg_error_mgr
name|pub
decl_stmt|;
comment|/* "public" fields */
ifdef|#
directive|ifdef
name|__ia64__
comment|/* Ugh, the jmp_buf field needs to be 16-byte aligned on ia64 and some    * glibc/icc combinations don't guarantee this. So we pad. See bug #138357    * for details.    */
DECL|member|dummy
name|long
name|double
name|dummy
decl_stmt|;
endif|#
directive|endif
DECL|member|setjmp_buffer
name|jmp_buf
name|setjmp_buffer
decl_stmt|;
comment|/* for return to caller */
DECL|typedef|my_error_ptr
block|}
typedef|*
name|my_error_ptr
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b507d360103
block|{
DECL|enumerator|JPEG_SUPSAMPLING_2x2_1x1_1x1
name|JPEG_SUPSAMPLING_2x2_1x1_1x1
init|=
literal|0
block|,
comment|/* smallest file */
DECL|enumerator|JPEG_SUPSAMPLING_2x1_1x1_1x1
name|JPEG_SUPSAMPLING_2x1_1x1_1x1
init|=
literal|1
block|,
comment|/* 4:2:2         */
DECL|enumerator|JPEG_SUPSAMPLING_1x1_1x1_1x1
name|JPEG_SUPSAMPLING_1x1_1x1_1x1
init|=
literal|2
block|,
DECL|enumerator|JPEG_SUPSAMPLING_1x2_1x1_1x1
name|JPEG_SUPSAMPLING_1x2_1x1_1x1
init|=
literal|3
DECL|typedef|JpegSubsampling
block|}
name|JpegSubsampling
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|gint32
specifier|volatile
name|preview_image_ID
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint32
name|preview_layer_ID
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpDrawable
modifier|*
name|drawable_global
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|undo_touched
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|load_interactive
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint32
name|display_ID
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|image_comment
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|has_metadata
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|orig_quality
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|JpegSubsampling
name|orig_subsmp
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|num_quant_tables
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|destroy_preview
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|my_error_exit
parameter_list|(
name|j_common_ptr
name|cinfo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|my_emit_message
parameter_list|(
name|j_common_ptr
name|cinfo
parameter_list|,
name|int
name|msg_level
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|my_output_message
parameter_list|(
name|j_common_ptr
name|cinfo
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_EXIF
end_ifdef

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
comment|/* HAVE_EXIF */
end_comment

end_unit

