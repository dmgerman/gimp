begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-webp - WebP file format plug-in for the GIMP  * Copyright (C) 2015  Nathan Osman  * Copyright (C) 2016  Ben Touchette  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation, either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__WEBP_SAVE_H__
end_ifndef

begin_define
DECL|macro|__WEBP_SAVE_H__
define|#
directive|define
name|__WEBP_SAVE_H__
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2acff4920108
block|{
DECL|member|preset
name|gchar
modifier|*
name|preset
decl_stmt|;
DECL|member|lossless
name|gboolean
name|lossless
decl_stmt|;
DECL|member|animation
name|gboolean
name|animation
decl_stmt|;
DECL|member|loop
name|gboolean
name|loop
decl_stmt|;
DECL|member|quality
name|gfloat
name|quality
decl_stmt|;
DECL|member|alpha_quality
name|gfloat
name|alpha_quality
decl_stmt|;
DECL|typedef|WebPSaveParams
block|}
name|WebPSaveParams
typedef|;
end_typedef

begin_function_decl
name|gboolean
name|save_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|nLayers
parameter_list|,
name|gint32
modifier|*
name|allLayers
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|WebPSaveParams
modifier|*
name|params
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __WEBP_SAVE_H__ */
end_comment

end_unit

