begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpimage_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
name|gint32
name|gimp_image_new
parameter_list|(
name|guint
name|width
parameter_list|,
name|guint
name|height
parameter_list|,
name|GimpImageBaseType
name|type
parameter_list|)
function_decl|;
name|gint32
name|gimp_image_duplicate
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_delete
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|guint
name|gimp_image_width
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|guint
name|gimp_image_height
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|GimpImageBaseType
name|gimp_image_base_type
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|gint32
name|gimp_image_floating_selection
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|void
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
name|void
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
name|void
name|gimp_image_add_layer_mask
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|,
name|gint32
name|mask_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_clean_all
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_undo_disable
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_undo_enable
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_undo_freeze
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_undo_thaw
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|void
name|gimp_undo_push_group_start
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|void
name|gimp_undo_push_group_end
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_clean_all
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|gint32
name|gimp_image_flatten
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_lower_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|channel_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_lower_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
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
name|void
name|gimp_image_raise_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|channel_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_raise_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_remove_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|channel_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_remove_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_remove_layer_mask
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|,
name|gint
name|mode
parameter_list|)
function_decl|;
name|void
name|gimp_image_resize
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|guint
name|new_width
parameter_list|,
name|guint
name|new_height
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
function_decl|;
name|gint32
name|gimp_image_get_active_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|gint32
name|gimp_image_get_active_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|gint32
modifier|*
name|gimp_image_get_channels
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|nchannels
parameter_list|)
function_decl|;
name|guchar
modifier|*
name|gimp_image_get_cmap
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|ncolors
parameter_list|)
function_decl|;
name|gboolean
name|gimp_image_get_component_active
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|component
parameter_list|)
function_decl|;
name|gboolean
name|gimp_image_get_component_visible
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|component
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_image_get_filename
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|gint32
modifier|*
name|gimp_image_get_layers
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|nlayers
parameter_list|)
function_decl|;
name|gint32
name|gimp_image_get_selection
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_set_active_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|channel_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_set_active_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
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
name|ncolors
parameter_list|)
function_decl|;
name|void
name|gimp_image_set_component_active
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|component
parameter_list|,
name|gboolean
name|active
parameter_list|)
function_decl|;
name|void
name|gimp_image_set_component_visible
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|component
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
name|void
name|gimp_image_set_filename
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
name|GimpParasite
modifier|*
name|gimp_image_parasite_find
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
name|void
name|gimp_image_parasite_attach
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
name|void
name|gimp_image_attach_new_parasite
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|flags
parameter_list|,
name|gint
name|size
parameter_list|,
specifier|const
name|gpointer
name|data
parameter_list|)
function_decl|;
name|void
name|gimp_image_parasite_detach
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
name|void
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
name|void
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
name|void
name|gimp_image_set_unit
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
name|GimpUnit
name|gimp_image_get_unit
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|gint32
name|gimp_image_get_layer_by_tattoo
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|tattoo
parameter_list|)
function_decl|;
name|gint32
name|gimp_image_get_channel_by_tattoo
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|tattoo
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
name|bytes
parameter_list|)
function_decl|;
name|void
name|gimp_image_convert_rgb
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_convert_grayscale
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
name|void
name|gimp_image_convert_indexed
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpConvertDitherType
name|dither_type
parameter_list|,
name|GimpConvertPaletteType
name|palette_type
parameter_list|,
name|gint
name|num_colors
parameter_list|,
name|gint
name|alpha_dither
parameter_list|,
name|gint
name|remove_unused
parameter_list|,
name|gchar
modifier|*
name|palette
parameter_list|)
function_decl|;
comment|/****************************************  *              Guides                  *  ****************************************/
name|gint32
name|gimp_image_add_hguide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|yposition
parameter_list|)
function_decl|;
name|gint32
name|gimp_image_add_vguide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|xposition
parameter_list|)
function_decl|;
name|void
name|gimp_image_delete_guide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
parameter_list|)
function_decl|;
name|gint32
name|gimp_image_find_next_guide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
parameter_list|)
function_decl|;
name|GOrientation
name|gimp_image_get_guide_orientation
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
parameter_list|)
function_decl|;
name|gint32
name|gimp_image_get_guide_position
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
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
comment|/* __GIMP_IMAGE_PDB_H__ */
end_comment

end_unit

