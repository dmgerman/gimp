begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * GIMP Plug-in for Windows Icon files.  * Copyright (C) 2002 Christian Kreibich<christian@whoop.org>.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__ICO_LOAD_H__
end_ifndef

begin_define
DECL|macro|__ICO_LOAD_H__
define|#
directive|define
name|__ICO_LOAD_H__
end_define

begin_function_decl
name|gint32
name|ico_load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|ico_load_thumbnail_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|ico_get_bit_from_data
parameter_list|(
specifier|const
name|guint8
modifier|*
name|data
parameter_list|,
name|gint
name|line_width
parameter_list|,
name|gint
name|bit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|ico_get_nibble_from_data
parameter_list|(
specifier|const
name|guint8
modifier|*
name|data
parameter_list|,
name|gint
name|line_width
parameter_list|,
name|gint
name|nibble
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|ico_get_byte_from_data
parameter_list|(
specifier|const
name|guint8
modifier|*
name|data
parameter_list|,
name|gint
name|line_width
parameter_list|,
name|gint
name|byte
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __ICO_LOAD_H__ */
end_comment

end_unit

