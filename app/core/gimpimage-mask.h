begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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

begin_function_decl
name|gboolean
name|gimp_image_mask_boundary
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|BoundSeg
modifier|*
modifier|*
name|segs_in
parameter_list|,
name|BoundSeg
modifier|*
modifier|*
name|segs_out
parameter_list|,
name|gint
modifier|*
name|num_segs_in
parameter_list|,
name|gint
modifier|*
name|num_segs_out
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_mask_bounds
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_mask_invalidate
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_mask_value
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_mask_is_empty
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

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
name|cut_gimage
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
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_mask_push_undo
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_mask_feather
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_mask_sharpen
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_mask_clear
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_mask_all
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_mask_invert
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_mask_border
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|border_radius_x
parameter_list|,
name|gint
name|border_radius_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_mask_grow
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|grow_pixels_x
parameter_list|,
name|gint
name|grow_pixels_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_mask_shrink
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|shrink_pixels_x
parameter_list|,
name|gint
name|shrink_pixels_y
parameter_list|,
name|gboolean
name|edge_lock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_mask_translate
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_mask_load
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_mask_layer_alpha
parameter_list|(
name|GimpImage
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
name|gimp_image_mask_layer_mask
parameter_list|(
name|GimpImage
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
name|GimpChannel
modifier|*
name|gimp_image_mask_save
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_mask_stroke
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
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

