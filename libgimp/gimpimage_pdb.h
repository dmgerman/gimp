begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpimage_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_PDB_H__
define|#
directive|define
name|__GIMP_IMAGE_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gint
modifier|*
name|gimp_image_list
parameter_list|(
name|gint
modifier|*
name|num_images
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_image_new
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpImageBaseType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_image_duplicate
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_delete
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageBaseType
name|gimp_image_base_type
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_width
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_height
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_free_shadow
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_resize
parameter_list|(
name|gint32
name|image_ID
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
name|gimp_image_resize_to_layers
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_scale
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_crop
parameter_list|(
name|gint32
name|image_ID
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
name|gimp_image_flip
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_rotate
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpRotationType
name|rotate_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
modifier|*
name|gimp_image_get_layers
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|num_layers
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
modifier|*
name|gimp_image_get_channels
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|num_channels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
modifier|*
name|gimp_image_get_vectors
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|num_vectors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_image_get_active_drawable
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_unset_active_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_image_get_floating_sel
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_image_floating_sel_attached_to
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_pick_color
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gboolean
name|sample_average
parameter_list|,
name|gdouble
name|average_radius
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_image_pick_correlate_layer
parameter_list|(
name|gint32
name|image_ID
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
name|gimp_image_add_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_remove_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_raise_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_lower_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_raise_layer_to_top
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_lower_layer_to_bottom
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_raise_vectors
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_lower_vectors
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_raise_vectors_to_top
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_lower_vectors_to_bottom
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_add_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|channel_ID
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_remove_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|channel_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_add_vectors
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_remove_vectors
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_raise_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|channel_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_lower_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|channel_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_image_flatten
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_image_merge_visible_layers
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpMergeType
name|merge_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_image_merge_down
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|merge_layer_ID
parameter_list|,
name|GimpMergeType
name|merge_type
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|guint8
modifier|*
name|_gimp_image_get_colormap
argument_list|(
name|gint32
name|image_ID
argument_list|,
name|gint
operator|*
name|num_bytes
argument_list|)
name|G_GNUC_INTERNAL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gboolean
name|_gimp_image_set_colormap
argument_list|(
name|gint32
name|image_ID
argument_list|,
name|gint
name|num_bytes
argument_list|,
specifier|const
name|guint8
operator|*
name|colormap
argument_list|)
name|G_GNUC_INTERNAL
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
name|gimp_image_clean_all
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_is_dirty
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|gboolean
name|_gimp_image_thumbnail
argument_list|(
name|gint32
name|image_ID
argument_list|,
name|gint
name|width
argument_list|,
name|gint
name|height
argument_list|,
name|gint
operator|*
name|actual_width
argument_list|,
name|gint
operator|*
name|actual_height
argument_list|,
name|gint
operator|*
name|bpp
argument_list|,
name|gint
operator|*
name|thumbnail_data_count
argument_list|,
name|guint8
operator|*
operator|*
name|thumbnail_data
argument_list|)
name|G_GNUC_INTERNAL
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gint32
name|gimp_image_get_active_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_active_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|active_layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_image_get_active_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_active_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|active_channel_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_image_get_active_vectors
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_active_vectors
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|active_vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_image_get_selection
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_get_component_active
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpChannelType
name|component
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_component_active
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpChannelType
name|component
parameter_list|,
name|gboolean
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_get_component_visible
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpChannelType
name|component
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_component_visible
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpChannelType
name|component
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_image_get_filename
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_filename
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_image_get_name
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_get_resolution
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gdouble
modifier|*
name|xresolution
parameter_list|,
name|gdouble
modifier|*
name|yresolution
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_resolution
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gdouble
name|xresolution
parameter_list|,
name|gdouble
name|yresolution
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUnit
name|gimp_image_get_unit
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_unit
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_tattoo_state
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_tattoo_state
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|tattoo_state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_image_get_layer_by_tattoo
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|tattoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_image_get_channel_by_tattoo
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|tattoo
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
comment|/* __GIMP_IMAGE_PDB_H__ */
end_comment

end_unit

