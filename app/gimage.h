begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMAGE_H__
end_ifndef

begin_define
DECL|macro|__GIMAGE_H__
define|#
directive|define
name|__GIMAGE_H__
end_define

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_function_decl
name|GImage
modifier|*
name|gimage_new
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpImageBaseType
name|base_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_set_layer_mask_apply
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_set_layer_mask_edit
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|edit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_set_layer_mask_show
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|guint32
name|next_guide_id
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMAGE_H__ */
end_comment

end_unit

