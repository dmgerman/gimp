begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMAGE_CMDS_H__
end_ifndef

begin_define
DECL|macro|__GIMAGE_CMDS_H__
define|#
directive|define
name|__GIMAGE_CMDS_H__
end_define

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_function_decl
name|void
name|channel_ops_duplicate
parameter_list|(
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_list_images_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_new_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_resize_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_scale_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_delete_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_free_shadow_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_get_layers_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_get_channels_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_get_active_layer_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_get_active_channel_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_get_selection_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_get_component_active_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_get_component_visible_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_set_active_layer_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_set_active_channel_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_unset_active_channel_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_set_component_active_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_set_component_visible_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_pick_correlate_layer_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_raise_layer_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_lower_layer_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_merge_visible_layers_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_merge_down_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_flatten_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_add_layer_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_remove_layer_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_add_layer_mask_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_remove_layer_mask_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_raise_channel_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_lower_channel_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_add_channel_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_remove_channel_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_active_drawable_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_base_type_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_get_filename_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_set_filename_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_width_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_height_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_get_cmap_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_set_cmap_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_enable_undo_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_disable_undo_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_clean_all_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimage_floating_sel_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|channel_ops_duplicate_proc
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMAGE_CMDS_H__  */
end_comment

end_unit

