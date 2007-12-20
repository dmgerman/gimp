begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GIMP PSD Plug-in  * Copyright 2007 by John Marshall  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
specifier|const
name|guint16
name|pad_len
parameter_list|,
name|FILE
modifier|*
name|f
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|fwrite_pascal_string
parameter_list|(
specifier|const
name|gchar
modifier|*
name|src
parameter_list|,
specifier|const
name|guint16
name|pad_len
parameter_list|,
name|FILE
modifier|*
name|f
parameter_list|)
function_decl|;
end_function_decl

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
specifier|const
name|guint16
name|pad_len
parameter_list|,
name|FILE
modifier|*
name|f
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|fwrite_unicode_string
parameter_list|(
specifier|const
name|gchar
modifier|*
name|src
parameter_list|,
specifier|const
name|guint16
name|pad_len
parameter_list|,
name|FILE
modifier|*
name|f
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
specifier|const
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
name|GimpLayerModeEffects
name|psd_to_gimp_blend_mode
parameter_list|(
specifier|const
name|gchar
modifier|*
name|psd_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_to_psd_blend_mode
parameter_list|(
specifier|const
name|GimpLayerModeEffects
name|gimp_layer_mode
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

