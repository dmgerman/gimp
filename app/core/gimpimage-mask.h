begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_empty
empty|#
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_empty

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_MASK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_MASK_H__
define|#
directive|define
name|__GIMP_IMAGE_MASK_H__
end_define

begin_comment
comment|/*  really implemented here:  */
end_comment

begin_function_decl
name|TileManager
modifier|*
name|gimp_image_mask_extract
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|cut_image
parameter_list|,
name|gboolean
name|keep_indexed
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_image_mask_float
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|cut_image
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_IMAGE_MASK_H__  */
end_comment

end_unit

