begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GIMP PSD Plug-in  * Copyright 2007 by John Marshall  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PSD_UTIL_H__
end_ifndef

begin_define
DECL|macro|__PSD_UTIL_H__
define|#
directive|define
name|__PSD_UTIL_H__
end_define

begin_comment
comment|/*  *  Set file read error  */
end_comment

begin_function_decl
name|void
name|psd_set_error
parameter_list|(
name|gboolean
name|file_eof
parameter_list|,
name|gint
name|err_no
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * Reads a pascal string from the file padded to a multiple of mod_len  * and returns a utf-8 string.  */
end_comment

begin_function_decl
name|gchar
modifier|*
name|fread_pascal_string
parameter_list|(
name|gint32
modifier|*
name|bytes_read
parameter_list|,
name|gint32
modifier|*
name|bytes_written
parameter_list|,
name|guint16
name|mod_len
parameter_list|,
name|FILE
modifier|*
name|f
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  *  Converts utf-8 string to current locale and writes as pascal  *  string with padding to a multiple of mod_len.  */
end_comment

begin_function_decl
name|gint32
name|fwrite_pascal_string
parameter_list|(
specifier|const
name|gchar
modifier|*
name|src
parameter_list|,
name|guint16
name|mod_len
parameter_list|,
name|FILE
modifier|*
name|f
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * Reads a utf-16 string from the file padded to a multiple of mod_len  * and returns a utf-8 string.  */
end_comment

begin_function_decl
name|gchar
modifier|*
name|fread_unicode_string
parameter_list|(
name|gint32
modifier|*
name|bytes_read
parameter_list|,
name|gint32
modifier|*
name|bytes_written
parameter_list|,
name|guint16
name|mod_len
parameter_list|,
name|FILE
modifier|*
name|f
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  *  Converts utf-8 string to utf-16 and writes 4 byte length  *  then string padding to multiple of mod_len.  */
end_comment

begin_function_decl
name|gint32
name|fwrite_unicode_string
parameter_list|(
specifier|const
name|gchar
modifier|*
name|src
parameter_list|,
name|guint16
name|mod_len
parameter_list|,
name|FILE
modifier|*
name|f
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
name|decode_packbits
parameter_list|(
specifier|const
name|gchar
modifier|*
name|src
parameter_list|,
name|gchar
modifier|*
name|dst
parameter_list|,
name|guint16
name|packed_len
parameter_list|,
name|guint32
name|unpacked_len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|encode_packbits
parameter_list|(
specifier|const
name|gchar
modifier|*
name|src
parameter_list|,
name|guint32
name|unpacked_len
parameter_list|,
name|guint16
modifier|*
name|packed_len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|psd_to_gimp_blend_mode
parameter_list|(
specifier|const
name|gchar
modifier|*
name|psd_mode
parameter_list|,
name|LayerModeInfo
modifier|*
name|mode_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_to_psd_blend_mode
parameter_list|(
specifier|const
name|LayerModeInfo
modifier|*
name|mode_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorTag
name|psd_to_gimp_layer_color_tag
parameter_list|(
name|guint16
name|layer_color_tag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint16
name|gimp_to_psd_layer_color_tag
parameter_list|(
name|GimpColorTag
name|layer_color_tag
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PSD_UTIL_H__ */
end_comment

end_unit

