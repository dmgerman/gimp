begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* exif-decode.h - decode exif data and convert it to XMP  *  * Copyright (C) 2008, RÃ³man Joost<romanofski@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|EXIF_DECODE_H
end_ifndef

begin_define
DECL|macro|EXIF_DECODE_H
define|#
directive|define
name|EXIF_DECODE_H
end_define

begin_function_decl
name|G_BEGIN_DECLS
name|gboolean
name|exif_merge_to_xmp
parameter_list|(
name|XMPModel
modifier|*
name|xmp_model
parameter_list|,
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
name|gboolean
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
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* EXIF_DECODE_H */
end_comment

end_unit

