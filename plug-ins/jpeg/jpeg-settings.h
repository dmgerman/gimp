begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * jpeg-settings.h  * Copyright (C) 2007 RaphaÃ«l Quinet<raphael@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_function_decl
name|gboolean
name|jpeg_detect_original_settings
parameter_list|(
name|struct
name|jpeg_decompress_struct
modifier|*
name|cinfo
parameter_list|,
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|jpeg_restore_original_settings
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|quality
parameter_list|,
name|gint
modifier|*
name|subsmp
parameter_list|,
name|gint
modifier|*
name|num_quant_tables
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint
modifier|*
modifier|*
name|jpeg_restore_original_tables
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|num_quant_tables
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|jpeg_swap_original_settings
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

end_unit

