begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpimage.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_H__
define|#
directive|define
name|__GIMP_IMAGE_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
comment|/* For information look into the C source or the html documentation */
DECL|macro|gimp_image_convert_rgb
define|#
directive|define
name|gimp_image_convert_rgb
value|gimp_convert_rgb
DECL|macro|gimp_image_convert_grayscale
define|#
directive|define
name|gimp_image_convert_grayscale
value|gimp_convert_grayscale
DECL|macro|gimp_image_convert_indexed
define|#
directive|define
name|gimp_image_convert_indexed
value|gimp_convert_indexed
DECL|macro|gimp_image_duplicate
define|#
directive|define
name|gimp_image_duplicate
value|gimp_channel_ops_duplicate
name|guchar
modifier|*
name|gimp_image_get_cmap
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|num_colors
parameter_list|)
function_decl|;
name|void
name|gimp_image_set_cmap
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|guchar
modifier|*
name|cmap
parameter_list|,
name|gint
name|num_colors
parameter_list|)
function_decl|;
name|guchar
modifier|*
name|gimp_image_get_thumbnail_data
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|bpp
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_H__ */
end_comment

end_unit

