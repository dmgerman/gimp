begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMAGE_MASK_H__
end_ifndef

begin_define
DECL|macro|__GIMAGE_MASK_H__
define|#
directive|define
name|__GIMAGE_MASK_H__
end_define

begin_include
include|#
directive|include
file|"boundary.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_comment
comment|/*  mask functions  */
end_comment

begin_function_decl
name|int
name|gimage_mask_boundary
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|BoundSeg
modifier|*
modifier|*
parameter_list|,
name|BoundSeg
modifier|*
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_mask_bounds
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_invalidate
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_mask_value
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_mask_is_empty
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_translate
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|gimage_mask_extract
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimage_mask_float
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_clear
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_undo
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_invert
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_sharpen
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_all
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_none
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_feather
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_border
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_grow
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_shrink
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_layer_alpha
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_layer_mask
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_mask_load
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimage_mask_save
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_mask_stroke
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMAGE_MASK_H__  */
end_comment

end_unit

