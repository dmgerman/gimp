begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DRAWABLE_H__
end_ifndef

begin_define
DECL|macro|__DRAWABLE_H__
define|#
directive|define
name|__DRAWABLE_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_function_decl
name|int
name|drawable_ID
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|drawable_fill
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|fill_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|drawable_update
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|drawable_apply_image
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|TileManager
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|drawable_merge_shadow
define|#
directive|define
name|drawable_merge_shadow
value|gimp_drawable_merge_shadow
end_define

begin_define
DECL|macro|drawable_mask_bounds
define|#
directive|define
name|drawable_mask_bounds
value|gimp_drawable_mask_bounds
end_define

begin_define
DECL|macro|drawable_invalidate_preview
define|#
directive|define
name|drawable_invalidate_preview
value|gimp_drawable_invalidate_preview
end_define

begin_define
DECL|macro|drawable_dirty
define|#
directive|define
name|drawable_dirty
value|gimp_drawable_dirty
end_define

begin_define
DECL|macro|drawable_clean
define|#
directive|define
name|drawable_clean
value|gimp_drawable_clean
end_define

begin_define
DECL|macro|drawable_type
define|#
directive|define
name|drawable_type
value|gimp_drawable_type
end_define

begin_define
DECL|macro|drawable_has_alpha
define|#
directive|define
name|drawable_has_alpha
value|gimp_drawable_has_alpha
end_define

begin_define
DECL|macro|drawable_type_with_alpha
define|#
directive|define
name|drawable_type_with_alpha
value|gimp_drawable_type_with_alpha
end_define

begin_define
DECL|macro|drawable_color
define|#
directive|define
name|drawable_color
value|gimp_drawable_color
end_define

begin_define
DECL|macro|drawable_gray
define|#
directive|define
name|drawable_gray
value|gimp_drawable_gray
end_define

begin_define
DECL|macro|drawable_indexed
define|#
directive|define
name|drawable_indexed
value|gimp_drawable_indexed
end_define

begin_define
DECL|macro|drawable_data
define|#
directive|define
name|drawable_data
value|gimp_drawable_data
end_define

begin_define
DECL|macro|drawable_shadow
define|#
directive|define
name|drawable_shadow
value|gimp_drawable_shadow
end_define

begin_define
DECL|macro|drawable_bytes
define|#
directive|define
name|drawable_bytes
value|gimp_drawable_bytes
end_define

begin_define
DECL|macro|drawable_width
define|#
directive|define
name|drawable_width
value|gimp_drawable_width
end_define

begin_define
DECL|macro|drawable_height
define|#
directive|define
name|drawable_height
value|gimp_drawable_height
end_define

begin_define
DECL|macro|drawable_visible
define|#
directive|define
name|drawable_visible
value|gimp_drawable_visible
end_define

begin_define
DECL|macro|drawable_offsets
define|#
directive|define
name|drawable_offsets
value|gimp_drawable_offsets
end_define

begin_define
DECL|macro|drawable_cmap
define|#
directive|define
name|drawable_cmap
value|gimp_drawable_cmap
end_define

begin_define
DECL|macro|drawable_get_name
define|#
directive|define
name|drawable_get_name
value|gimp_drawable_get_name
end_define

begin_define
DECL|macro|drawable_set_name
define|#
directive|define
name|drawable_set_name
value|gimp_drawable_set_name
end_define

begin_define
DECL|macro|drawable_get_ID
define|#
directive|define
name|drawable_get_ID
value|gimp_drawable_get_ID
end_define

begin_define
DECL|macro|drawable_deallocate
define|#
directive|define
name|drawable_deallocate
value|gimp_drawable_deallocate
end_define

begin_define
DECL|macro|drawable_gimage
define|#
directive|define
name|drawable_gimage
value|gimp_drawable_gimage
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DRAWABLE_H__ */
end_comment

end_unit

