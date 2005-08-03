begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|125
end_define

begin_comment
comment|/* See bugs #63610 and #61088 for a discussion about the quality settings */
end_comment

begin_define
DECL|macro|DEFAULT_QUALITY
define|#
directive|define
name|DEFAULT_QUALITY
value|85.0
end_define

begin_define
DECL|macro|DEFAULT_SMOOTHING
define|#
directive|define
name|DEFAULT_SMOOTHING
value|0.0
end_define

begin_define
DECL|macro|DEFAULT_OPTIMIZE
define|#
directive|define
name|DEFAULT_OPTIMIZE
value|TRUE
end_define

begin_define
DECL|macro|DEFAULT_PROGRESSIVE
define|#
directive|define
name|DEFAULT_PROGRESSIVE
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_BASELINE
define|#
directive|define
name|DEFAULT_BASELINE
value|TRUE
end_define

begin_define
DECL|macro|DEFAULT_SUBSMP
define|#
directive|define
name|DEFAULT_SUBSMP
value|0
end_define

begin_define
DECL|macro|DEFAULT_RESTART
define|#
directive|define
name|DEFAULT_RESTART
value|0
end_define

begin_define
DECL|macro|DEFAULT_DCT
define|#
directive|define
name|DEFAULT_DCT
value|0
end_define

begin_define
DECL|macro|DEFAULT_PREVIEW
define|#
directive|define
name|DEFAULT_PREVIEW
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_EXIF
define|#
directive|define
name|DEFAULT_EXIF
value|TRUE
end_define

begin_define
DECL|macro|DEFAULT_THUMBNAIL
define|#
directive|define
name|DEFAULT_THUMBNAIL
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_XMP
define|#
directive|define
name|DEFAULT_XMP
value|TRUE
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28b9f5490108
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
DECL|member|progressive
name|gboolean
name|progressive
decl_stmt|;
DECL|member|baseline
name|gboolean
name|baseline
decl_stmt|;
DECL|member|subsmp
name|gint
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
DECL|member|save_thumbnail
name|gboolean
name|save_thumbnail
decl_stmt|;
DECL|member|save_xmp
name|gboolean
name|save_xmp
decl_stmt|;
DECL|typedef|JpegSaveVals
block|}
name|JpegSaveVals
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|jsvals
name|JpegSaveVals
name|jsvals
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|orig_image_ID_global
name|gint32
name|orig_image_ID_global
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_ID_global
name|gint32
name|drawable_ID_global
decl_stmt|;
end_decl_stmt

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
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gint32
name|orig_image_ID
parameter_list|,
name|gboolean
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|save_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

end_unit

