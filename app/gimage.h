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

begin_comment
comment|/* icky.. this is temporary */
end_comment

begin_include
include|#
directive|include
file|"gimpimageP.h"
end_include

begin_typedef
DECL|typedef|GImage
typedef|typedef
name|GimpImage
name|GImage
typedef|;
end_typedef

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
name|GImage
modifier|*
name|gimage_get_ID
parameter_list|(
name|gint
name|ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_delete
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_invalidate_previews
parameter_list|(
name|void
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

begin_function_decl
name|void
name|gimage_foreach
parameter_list|(
name|GFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|gimage_set_filename
define|#
directive|define
name|gimage_set_filename
value|gimp_image_set_filename
end_define

begin_define
DECL|macro|gimage_set_resolution
define|#
directive|define
name|gimage_set_resolution
value|gimp_image_set_resolution
end_define

begin_define
DECL|macro|gimage_get_resolution
define|#
directive|define
name|gimage_get_resolution
value|gimp_image_get_resolution
end_define

begin_define
DECL|macro|gimage_set_unit
define|#
directive|define
name|gimage_set_unit
value|gimp_image_set_unit
end_define

begin_define
DECL|macro|gimage_get_unit
define|#
directive|define
name|gimage_get_unit
value|gimp_image_get_unit
end_define

begin_define
DECL|macro|gimage_set_save_proc
define|#
directive|define
name|gimage_set_save_proc
value|gimp_image_set_save_proc
end_define

begin_define
DECL|macro|gimage_get_save_proc
define|#
directive|define
name|gimage_get_save_proc
value|gimp_image_get_save_proc
end_define

begin_define
DECL|macro|gimage_resize
define|#
directive|define
name|gimage_resize
value|gimp_image_resize
end_define

begin_define
DECL|macro|gimage_scale
define|#
directive|define
name|gimage_scale
value|gimp_image_scale
end_define

begin_define
DECL|macro|gimage_shadow
define|#
directive|define
name|gimage_shadow
value|gimp_image_shadow
end_define

begin_define
DECL|macro|gimage_free_shadow
define|#
directive|define
name|gimage_free_shadow
value|gimp_image_free_shadow
end_define

begin_define
DECL|macro|gimage_apply_image
define|#
directive|define
name|gimage_apply_image
value|gimp_image_apply_image
end_define

begin_define
DECL|macro|gimage_replace_image
define|#
directive|define
name|gimage_replace_image
value|gimp_image_replace_image
end_define

begin_define
DECL|macro|gimage_get_foreground
define|#
directive|define
name|gimage_get_foreground
value|gimp_image_get_foreground
end_define

begin_define
DECL|macro|gimage_get_background
define|#
directive|define
name|gimage_get_background
value|gimp_image_get_background
end_define

begin_define
DECL|macro|gimage_get_color
define|#
directive|define
name|gimage_get_color
value|gimp_image_get_color
end_define

begin_define
DECL|macro|gimage_transform_color
define|#
directive|define
name|gimage_transform_color
value|gimp_image_transform_color
end_define

begin_define
DECL|macro|gimage_add_hguide
define|#
directive|define
name|gimage_add_hguide
value|gimp_image_add_hguide
end_define

begin_define
DECL|macro|gimage_add_vguide
define|#
directive|define
name|gimage_add_vguide
value|gimp_image_add_vguide
end_define

begin_define
DECL|macro|gimage_add_guide
define|#
directive|define
name|gimage_add_guide
value|gimp_image_add_guide
end_define

begin_define
DECL|macro|gimage_remove_guide
define|#
directive|define
name|gimage_remove_guide
value|gimp_image_remove_guide
end_define

begin_define
DECL|macro|gimage_delete_guide
define|#
directive|define
name|gimage_delete_guide
value|gimp_image_delete_guide
end_define

begin_define
DECL|macro|gimage_get_layer_index
define|#
directive|define
name|gimage_get_layer_index
value|gimp_image_get_layer_index
end_define

begin_define
DECL|macro|gimage_get_channel_index
define|#
directive|define
name|gimage_get_channel_index
value|gimp_image_get_channel_index
end_define

begin_define
DECL|macro|gimage_get_active_layer
define|#
directive|define
name|gimage_get_active_layer
value|gimp_image_get_active_layer
end_define

begin_define
DECL|macro|gimage_get_active_channel
define|#
directive|define
name|gimage_get_active_channel
value|gimp_image_get_active_channel
end_define

begin_define
DECL|macro|gimage_get_mask
define|#
directive|define
name|gimage_get_mask
value|gimp_image_get_mask
end_define

begin_define
DECL|macro|gimage_get_component_active
define|#
directive|define
name|gimage_get_component_active
value|gimp_image_get_component_active
end_define

begin_define
DECL|macro|gimage_get_component_visible
define|#
directive|define
name|gimage_get_component_visible
value|gimp_image_get_component_visible
end_define

begin_define
DECL|macro|gimage_layer_boundary
define|#
directive|define
name|gimage_layer_boundary
value|gimp_image_layer_boundary
end_define

begin_define
DECL|macro|gimage_set_active_layer
define|#
directive|define
name|gimage_set_active_layer
value|gimp_image_set_active_layer
end_define

begin_define
DECL|macro|gimage_set_active_channel
define|#
directive|define
name|gimage_set_active_channel
value|gimp_image_set_active_channel
end_define

begin_define
DECL|macro|gimage_unset_active_channel
define|#
directive|define
name|gimage_unset_active_channel
value|gimp_image_unset_active_channel
end_define

begin_define
DECL|macro|gimage_set_component_active
define|#
directive|define
name|gimage_set_component_active
value|gimp_image_set_component_active
end_define

begin_define
DECL|macro|gimage_set_component_visible
define|#
directive|define
name|gimage_set_component_visible
value|gimp_image_set_component_visible
end_define

begin_define
DECL|macro|gimage_pick_correlate_layer
define|#
directive|define
name|gimage_pick_correlate_layer
value|gimp_image_pick_correlate_layer
end_define

begin_define
DECL|macro|gimage_raise_layer
define|#
directive|define
name|gimage_raise_layer
value|gimp_image_raise_layer
end_define

begin_define
DECL|macro|gimage_lower_layer
define|#
directive|define
name|gimage_lower_layer
value|gimp_image_lower_layer
end_define

begin_define
DECL|macro|gimage_raise_layer_to_top
define|#
directive|define
name|gimage_raise_layer_to_top
value|gimp_image_raise_layer_to_top
end_define

begin_define
DECL|macro|gimage_lower_layer_to_bottom
define|#
directive|define
name|gimage_lower_layer_to_bottom
value|gimp_image_lower_layer_to_bottom
end_define

begin_define
DECL|macro|gimage_position_layer
define|#
directive|define
name|gimage_position_layer
value|gimp_image_position_layer
end_define

begin_define
DECL|macro|gimage_merge_visible_layers
define|#
directive|define
name|gimage_merge_visible_layers
value|gimp_image_merge_visible_layers
end_define

begin_define
DECL|macro|gimage_flatten
define|#
directive|define
name|gimage_flatten
value|gimp_image_flatten
end_define

begin_define
DECL|macro|gimage_merge_layers
define|#
directive|define
name|gimage_merge_layers
value|gimp_image_merge_layers
end_define

begin_define
DECL|macro|gimage_add_layer
define|#
directive|define
name|gimage_add_layer
value|gimp_image_add_layer
end_define

begin_define
DECL|macro|gimage_remove_layer
define|#
directive|define
name|gimage_remove_layer
value|gimp_image_remove_layer
end_define

begin_define
DECL|macro|gimage_add_layer_mask
define|#
directive|define
name|gimage_add_layer_mask
value|gimp_image_add_layer_mask
end_define

begin_define
DECL|macro|gimage_remove_layer_mask
define|#
directive|define
name|gimage_remove_layer_mask
value|gimp_image_remove_layer_mask
end_define

begin_define
DECL|macro|gimage_raise_channel
define|#
directive|define
name|gimage_raise_channel
value|gimp_image_raise_channel
end_define

begin_define
DECL|macro|gimage_lower_channel
define|#
directive|define
name|gimage_lower_channel
value|gimp_image_lower_channel
end_define

begin_define
DECL|macro|gimage_position_channel
define|#
directive|define
name|gimage_position_channel
value|gimp_image_position_channel
end_define

begin_define
DECL|macro|gimage_add_channel
define|#
directive|define
name|gimage_add_channel
value|gimp_image_add_channel
end_define

begin_define
DECL|macro|gimage_remove_channel
define|#
directive|define
name|gimage_remove_channel
value|gimp_image_remove_channel
end_define

begin_define
DECL|macro|gimage_construct
define|#
directive|define
name|gimage_construct
value|gimp_image_construct
end_define

begin_define
DECL|macro|gimage_invalidate_without_render
define|#
directive|define
name|gimage_invalidate_without_render
value|gimp_image_invalidate_without_render
end_define

begin_define
DECL|macro|gimage_invalidate
define|#
directive|define
name|gimage_invalidate
value|gimp_image_invalidate
end_define

begin_define
DECL|macro|gimage_validate
define|#
directive|define
name|gimage_validate
value|gimp_image_validate
end_define

begin_define
DECL|macro|gimage_is_empty
define|#
directive|define
name|gimage_is_empty
value|gimp_image_is_empty
end_define

begin_define
DECL|macro|gimage_active_drawable
define|#
directive|define
name|gimage_active_drawable
value|gimp_image_active_drawable
end_define

begin_define
DECL|macro|gimage_base_type
define|#
directive|define
name|gimage_base_type
value|gimp_image_base_type
end_define

begin_define
DECL|macro|gimage_base_type_with_alpha
define|#
directive|define
name|gimage_base_type_with_alpha
value|gimp_image_base_type_with_alpha
end_define

begin_define
DECL|macro|gimage_filename
define|#
directive|define
name|gimage_filename
value|gimp_image_filename
end_define

begin_define
DECL|macro|gimage_enable_undo
define|#
directive|define
name|gimage_enable_undo
value|gimp_image_enable_undo
end_define

begin_define
DECL|macro|gimage_disable_undo
define|#
directive|define
name|gimage_disable_undo
value|gimp_image_disable_undo
end_define

begin_define
DECL|macro|gimage_thaw_undo
define|#
directive|define
name|gimage_thaw_undo
value|gimp_image_thaw_undo
end_define

begin_define
DECL|macro|gimage_freeze_undo
define|#
directive|define
name|gimage_freeze_undo
value|gimp_image_freeze_undo
end_define

begin_define
DECL|macro|gimage_dirty
define|#
directive|define
name|gimage_dirty
value|gimp_image_dirty
end_define

begin_define
DECL|macro|gimage_clean
define|#
directive|define
name|gimage_clean
value|gimp_image_clean
end_define

begin_define
DECL|macro|gimage_clean_all
define|#
directive|define
name|gimage_clean_all
value|gimp_image_clean_all
end_define

begin_define
DECL|macro|gimage_floating_sel
define|#
directive|define
name|gimage_floating_sel
value|gimp_image_floating_sel
end_define

begin_define
DECL|macro|gimage_cmap
define|#
directive|define
name|gimage_cmap
value|gimp_image_cmap
end_define

begin_define
DECL|macro|gimage_projection
define|#
directive|define
name|gimage_projection
value|gimp_image_projection
end_define

begin_define
DECL|macro|gimage_projection_type
define|#
directive|define
name|gimage_projection_type
value|gimp_image_projection_type
end_define

begin_define
DECL|macro|gimage_projection_bytes
define|#
directive|define
name|gimage_projection_bytes
value|gimp_image_projection_bytes
end_define

begin_define
DECL|macro|gimage_projection_opacity
define|#
directive|define
name|gimage_projection_opacity
value|gimp_image_projection_opacity
end_define

begin_define
DECL|macro|gimage_projection_realloc
define|#
directive|define
name|gimage_projection_realloc
value|gimp_image_projection_realloc
end_define

begin_define
DECL|macro|gimage_composite
define|#
directive|define
name|gimage_composite
value|gimp_image_composite
end_define

begin_define
DECL|macro|gimage_composite_type
define|#
directive|define
name|gimage_composite_type
value|gimp_image_composite_type
end_define

begin_define
DECL|macro|gimage_composite_bytes
define|#
directive|define
name|gimage_composite_bytes
value|gimp_image_composite_bytes
end_define

begin_define
DECL|macro|gimage_composite_preview
define|#
directive|define
name|gimage_composite_preview
value|gimp_image_composite_preview
end_define

begin_define
DECL|macro|gimage_preview_valid
define|#
directive|define
name|gimage_preview_valid
value|gimp_image_preview_valid
end_define

begin_define
DECL|macro|gimage_invalidate_preview
define|#
directive|define
name|gimage_invalidate_preview
value|gimp_image_invalidate_preview
end_define

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

