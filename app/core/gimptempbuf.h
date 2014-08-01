begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEMP_BUF_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEMP_BUF_H__
define|#
directive|define
name|__GIMP_TEMP_BUF_H__
end_define

begin_decl_stmt
name|GimpTempBuf
modifier|*
name|gimp_temp_buf_new
argument_list|(
name|gint
name|width
argument_list|,
name|gint
name|height
argument_list|,
specifier|const
name|Babl
operator|*
name|format
argument_list|)
name|G_GNUC_WARN_UNUSED_RESULT
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GimpTempBuf
modifier|*
name|gimp_temp_buf_new_from_pixbuf
argument_list|(
name|GdkPixbuf
operator|*
name|pixbuf
argument_list|,
specifier|const
name|Babl
operator|*
name|f_or_null
argument_list|)
name|G_GNUC_WARN_UNUSED_RESULT
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GimpTempBuf
modifier|*
name|gimp_temp_buf_copy
argument_list|(
specifier|const
name|GimpTempBuf
operator|*
name|src
argument_list|)
name|G_GNUC_WARN_UNUSED_RESULT
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpTempBuf
modifier|*
name|gimp_temp_buf_ref
parameter_list|(
name|GimpTempBuf
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_temp_buf_unref
parameter_list|(
name|GimpTempBuf
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GimpTempBuf
modifier|*
name|gimp_temp_buf_scale
argument_list|(
specifier|const
name|GimpTempBuf
operator|*
name|buf
argument_list|,
name|gint
name|width
argument_list|,
name|gint
name|height
argument_list|)
name|G_GNUC_WARN_UNUSED_RESULT
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gint
name|gimp_temp_buf_get_width
parameter_list|(
specifier|const
name|GimpTempBuf
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_temp_buf_get_height
parameter_list|(
specifier|const
name|GimpTempBuf
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_temp_buf_get_format
parameter_list|(
specifier|const
name|GimpTempBuf
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_temp_buf_set_format
parameter_list|(
name|GimpTempBuf
modifier|*
name|buf
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_temp_buf_get_data
parameter_list|(
specifier|const
name|GimpTempBuf
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gsize
name|gimp_temp_buf_get_data_size
parameter_list|(
specifier|const
name|GimpTempBuf
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_temp_buf_data_clear
parameter_list|(
name|GimpTempBuf
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gsize
name|gimp_temp_buf_get_memsize
parameter_list|(
specifier|const
name|GimpTempBuf
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GeglBuffer
modifier|*
name|gimp_temp_buf_create_buffer
argument_list|(
name|GimpTempBuf
operator|*
name|temp_buf
argument_list|)
name|G_GNUC_WARN_UNUSED_RESULT
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GdkPixbuf
modifier|*
name|gimp_temp_buf_create_pixbuf
argument_list|(
name|GimpTempBuf
operator|*
name|temp_buf
argument_list|)
name|G_GNUC_WARN_UNUSED_RESULT
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpTempBuf
modifier|*
name|gimp_gegl_buffer_get_temp_buf
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TEMP_BUF_H__  */
end_comment

end_unit

