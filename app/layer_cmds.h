begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__LAYER_CMDS_H__
end_ifndef

begin_define
DECL|macro|__LAYER_CMDS_H__
define|#
directive|define
name|__LAYER_CMDS_H__
end_define

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_new_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_copy_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_create_mask_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_scale_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_resize_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_delete_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_translate_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_add_alpha_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_get_name_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_set_name_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_get_visible_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_set_visible_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_get_preserve_trans_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_set_preserve_trans_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_get_apply_mask_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_set_apply_mask_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_get_show_mask_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_set_show_mask_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_get_edit_mask_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_set_edit_mask_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_get_opacity_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_set_opacity_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_get_mode_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_set_mode_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_set_offsets_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_mask_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|layer_is_floating_sel_proc
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __LAYER_CMDS_H__ */
end_comment

end_unit

