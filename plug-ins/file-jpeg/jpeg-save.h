begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__JPEG_SAVE_H__
end_ifndef

begin_define
DECL|macro|__JPEG_SAVE_H__
define|#
directive|define
name|__JPEG_SAVE_H__
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2912182d0108
block|{
DECL|member|quality
name|gdouble
name|quality
decl_stmt|;
DECL|member|smoothing
name|gdouble
name|smoothing
decl_stmt|;
DECL|member|optimize
name|gboolean
name|optimize
decl_stmt|;
DECL|member|arithmetic_coding
name|gboolean
name|arithmetic_coding
decl_stmt|;
DECL|member|progressive
name|gboolean
name|progressive
decl_stmt|;
DECL|member|baseline
name|gboolean
name|baseline
decl_stmt|;
DECL|member|subsmp
name|JpegSubsampling
name|subsmp
decl_stmt|;
DECL|member|restart
name|gint
name|restart
decl_stmt|;
DECL|member|dct
name|gint
name|dct
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|member|save_exif
name|gboolean
name|save_exif
decl_stmt|;
DECL|member|save_xmp
name|gboolean
name|save_xmp
decl_stmt|;
DECL|member|save_iptc
name|gboolean
name|save_iptc
decl_stmt|;
DECL|member|save_thumbnail
name|gboolean
name|save_thumbnail
decl_stmt|;
DECL|member|save_profile
name|gboolean
name|save_profile
decl_stmt|;
DECL|member|use_orig_quality
name|gboolean
name|use_orig_quality
decl_stmt|;
DECL|typedef|JpegSaveVals
block|}
name|JpegSaveVals
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|JpegSaveVals
name|jsvals
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpImage
modifier|*
name|orig_image_global
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpDrawable
modifier|*
name|drawable_global
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
name|save_image
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
name|orig_image
parameter_list|,
name|gboolean
name|preview
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
name|save_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|load_defaults
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|load_parasite
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __JPEG_SAVE_H__ */
end_comment

end_unit

