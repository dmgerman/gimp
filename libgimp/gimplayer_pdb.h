begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimplayer_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimp.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LAYER_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LAYER_PDB_H__
define|#
directive|define
name|__GIMP_LAYER_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
ifndef|#
directive|ifndef
name|GIMP_DEPRECATED_REPLACE_NEW_API
name|G_GNUC_INTERNAL
name|GimpLayer
modifier|*
name|_gimp_layer_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpImageType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_layer_new_from_visible
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_layer_new_from_drawable
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_layer_group_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|GimpLayer
modifier|*
name|_gimp_layer_copy
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_add_alpha
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_flatten
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_scale
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gboolean
name|local_origin
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_resize
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_resize_to_image_size
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_set_offsets
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerMask
modifier|*
name|gimp_layer_create_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpAddMaskType
name|mask_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerMask
modifier|*
name|gimp_layer_get_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_layer_from_mask
parameter_list|(
name|GimpLayerMask
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_add_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerMask
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_remove_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpMaskApplyMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_is_floating_sel
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_get_lock_alpha
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_set_lock_alpha
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|lock_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_get_apply_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_set_apply_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|apply_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_get_show_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_set_show_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|show_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_get_edit_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_set_edit_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|edit_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_layer_get_opacity
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_set_opacity
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerMode
name|gimp_layer_get_mode
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_set_mode
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerColorSpace
name|gimp_layer_get_blend_space
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_set_blend_space
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerColorSpace
name|blend_space
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerColorSpace
name|gimp_layer_get_composite_space
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_set_composite_space
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerColorSpace
name|composite_space
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerCompositeMode
name|gimp_layer_get_composite_mode
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_set_composite_mode
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerCompositeMode
name|composite_mode
parameter_list|)
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* GIMP_DEPRECATED_REPLACE_NEW_API */
end_comment

begin_define
define|#
directive|define
name|_gimp_layer_new
value|__gimp_layer_new
end_define

begin_define
define|#
directive|define
name|gimp_layer_new_from_visible
value|_gimp_layer_new_from_visible
end_define

begin_define
define|#
directive|define
name|gimp_layer_new_from_drawable
value|_gimp_layer_new_from_drawable
end_define

begin_define
define|#
directive|define
name|gimp_layer_group_new
value|_gimp_layer_group_new
end_define

begin_define
define|#
directive|define
name|_gimp_layer_copy
value|__gimp_layer_copy
end_define

begin_define
define|#
directive|define
name|gimp_layer_add_alpha
value|_gimp_layer_add_alpha
end_define

begin_define
define|#
directive|define
name|gimp_layer_flatten
value|_gimp_layer_flatten
end_define

begin_define
define|#
directive|define
name|gimp_layer_scale
value|_gimp_layer_scale
end_define

begin_define
define|#
directive|define
name|gimp_layer_resize
value|_gimp_layer_resize
end_define

begin_define
define|#
directive|define
name|gimp_layer_resize_to_image_size
value|_gimp_layer_resize_to_image_size
end_define

begin_define
define|#
directive|define
name|gimp_layer_set_offsets
value|_gimp_layer_set_offsets
end_define

begin_define
define|#
directive|define
name|gimp_layer_create_mask
value|_gimp_layer_create_mask
end_define

begin_define
define|#
directive|define
name|gimp_layer_get_mask
value|_gimp_layer_get_mask
end_define

begin_define
define|#
directive|define
name|gimp_layer_from_mask
value|_gimp_layer_from_mask
end_define

begin_define
define|#
directive|define
name|gimp_layer_add_mask
value|_gimp_layer_add_mask
end_define

begin_define
define|#
directive|define
name|gimp_layer_remove_mask
value|_gimp_layer_remove_mask
end_define

begin_define
define|#
directive|define
name|gimp_layer_is_floating_sel
value|_gimp_layer_is_floating_sel
end_define

begin_define
define|#
directive|define
name|gimp_layer_get_lock_alpha
value|_gimp_layer_get_lock_alpha
end_define

begin_define
define|#
directive|define
name|gimp_layer_set_lock_alpha
value|_gimp_layer_set_lock_alpha
end_define

begin_define
define|#
directive|define
name|gimp_layer_get_apply_mask
value|_gimp_layer_get_apply_mask
end_define

begin_define
define|#
directive|define
name|gimp_layer_set_apply_mask
value|_gimp_layer_set_apply_mask
end_define

begin_define
define|#
directive|define
name|gimp_layer_get_show_mask
value|_gimp_layer_get_show_mask
end_define

begin_define
define|#
directive|define
name|gimp_layer_set_show_mask
value|_gimp_layer_set_show_mask
end_define

begin_define
define|#
directive|define
name|gimp_layer_get_edit_mask
value|_gimp_layer_get_edit_mask
end_define

begin_define
define|#
directive|define
name|gimp_layer_set_edit_mask
value|_gimp_layer_set_edit_mask
end_define

begin_define
define|#
directive|define
name|gimp_layer_get_opacity
value|_gimp_layer_get_opacity
end_define

begin_define
define|#
directive|define
name|gimp_layer_set_opacity
value|_gimp_layer_set_opacity
end_define

begin_define
define|#
directive|define
name|gimp_layer_get_mode
value|_gimp_layer_get_mode
end_define

begin_define
define|#
directive|define
name|gimp_layer_set_mode
value|_gimp_layer_set_mode
end_define

begin_define
define|#
directive|define
name|gimp_layer_get_blend_space
value|_gimp_layer_get_blend_space
end_define

begin_define
define|#
directive|define
name|gimp_layer_set_blend_space
value|_gimp_layer_set_blend_space
end_define

begin_define
define|#
directive|define
name|gimp_layer_get_composite_space
value|_gimp_layer_get_composite_space
end_define

begin_define
define|#
directive|define
name|gimp_layer_set_composite_space
value|_gimp_layer_set_composite_space
end_define

begin_define
define|#
directive|define
name|gimp_layer_get_composite_mode
value|_gimp_layer_get_composite_mode
end_define

begin_define
define|#
directive|define
name|gimp_layer_set_composite_mode
value|_gimp_layer_set_composite_mode
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DEPRECATED_REPLACE_NEW_API */
end_comment

begin_comment
comment|/* Below API are deprecated and should not be used by new plug-ins.  * They are not marked internal as a trick to keep the old API alive for now.  */
end_comment

begin_function_decl
name|gint32
name|__gimp_layer_new
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpImageType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|_gimp_layer_new_from_visible
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|dest_image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|_gimp_layer_new_from_drawable
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint32
name|dest_image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|_gimp_layer_group_new
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|__gimp_layer_copy
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_add_alpha
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_flatten
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_scale
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gboolean
name|local_origin
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_resize
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_resize_to_image_size
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_set_offsets
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|_gimp_layer_create_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|GimpAddMaskType
name|mask_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|_gimp_layer_get_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|_gimp_layer_from_mask
parameter_list|(
name|gint32
name|mask_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_add_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gint32
name|mask_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_remove_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|GimpMaskApplyMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_is_floating_sel
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_get_lock_alpha
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_set_lock_alpha
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|lock_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_get_apply_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_set_apply_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|apply_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_get_show_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_set_show_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|show_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_get_edit_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_set_edit_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|edit_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|_gimp_layer_get_opacity
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_set_opacity
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerMode
name|_gimp_layer_get_mode
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_set_mode
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerColorSpace
name|_gimp_layer_get_blend_space
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_set_blend_space
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|GimpLayerColorSpace
name|blend_space
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerColorSpace
name|_gimp_layer_get_composite_space
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_set_composite_space
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|GimpLayerColorSpace
name|composite_space
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerCompositeMode
name|_gimp_layer_get_composite_mode
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_layer_set_composite_mode
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|GimpLayerCompositeMode
name|composite_mode
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LAYER_PDB_H__ */
end_comment

end_unit

