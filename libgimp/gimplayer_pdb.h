begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimplayer_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

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
name|gimp_layer_new
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|char
modifier|*
name|name
parameter_list|,
name|guint
name|width
parameter_list|,
name|guint
name|height
parameter_list|,
name|GimpImageType
name|type
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GLayerMode
name|mode
parameter_list|)
function_decl|;
name|gint32
name|gimp_layer_copy
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|void
name|gimp_layer_delete
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|void
name|gimp_layer_add_alpha
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|gint32
name|gimp_layer_create_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|GimpAddMaskType
name|mask_type
parameter_list|)
function_decl|;
name|void
name|gimp_layer_resize
parameter_list|(
name|gint32
name|layer_ID
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
name|void
name|gimp_layer_scale
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|guint
name|new_width
parameter_list|,
name|guint
name|new_height
parameter_list|,
name|gint
name|local_origin
parameter_list|)
function_decl|;
name|void
name|gimp_layer_translate
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
function_decl|;
name|gboolean
name|gimp_layer_is_floating_selection
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|gint32
name|gimp_layer_get_image_id
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|gint32
name|gimp_layer_get_mask_id
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|gboolean
name|gimp_layer_get_apply_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|gboolean
name|gimp_layer_get_edit_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|GLayerMode
name|gimp_layer_get_mode
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_layer_get_name
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|gdouble
name|gimp_layer_get_opacity
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|gboolean
name|gimp_layer_get_preserve_transparency
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|gint
name|gimp_layer_get_show_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|gint
name|gimp_layer_get_visible
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
name|void
name|gimp_layer_set_apply_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|apply_mask
parameter_list|)
function_decl|;
name|void
name|gimp_layer_set_edit_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|edit_mask
parameter_list|)
function_decl|;
name|void
name|gimp_layer_set_mode
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|GLayerMode
name|mode
parameter_list|)
function_decl|;
name|void
name|gimp_layer_set_name
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
name|void
name|gimp_layer_set_offsets
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
function_decl|;
name|void
name|gimp_layer_set_opacity
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
function_decl|;
name|void
name|gimp_layer_set_preserve_transparency
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|preserve_transparency
parameter_list|)
function_decl|;
name|void
name|gimp_layer_set_show_mask
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|show_mask
parameter_list|)
function_decl|;
name|void
name|gimp_layer_set_visible
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
name|gint32
name|gimp_layer_get_tattoo
parameter_list|(
name|gint32
name|layer_ID
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
comment|/* __GIMP_LAYER_PDB_H__ */
end_comment

end_unit

