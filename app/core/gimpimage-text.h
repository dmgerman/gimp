begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattisbvf  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_TEXT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_TEXT_H__
define|#
directive|define
name|__GIMP_IMAGE_TEXT_H__
end_define

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_image_text_render
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpText
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* convenience functions using the old API */
end_comment

begin_function_decl
name|GimpLayer
modifier|*
name|text_render
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|text_x
parameter_list|,
name|gint
name|text_y
parameter_list|,
specifier|const
name|gchar
modifier|*
name|fontname
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|border
parameter_list|,
name|gint
name|antialias
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|text_get_extents
parameter_list|(
specifier|const
name|gchar
modifier|*
name|fontname
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
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
name|ascent
parameter_list|,
name|gint
modifier|*
name|descent
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_TEXT_H__ */
end_comment

end_unit

