begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__UNDO_H__
end_ifndef

begin_define
DECL|macro|__UNDO_H__
define|#
directive|define
name|__UNDO_H__
end_define

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_comment
comment|/*  Undo types  */
end_comment

begin_define
DECL|macro|IMAGE_UNDO
define|#
directive|define
name|IMAGE_UNDO
value|1
end_define

begin_define
DECL|macro|IMAGE_MOD_UNDO
define|#
directive|define
name|IMAGE_MOD_UNDO
value|2
end_define

begin_define
DECL|macro|MASK_UNDO
define|#
directive|define
name|MASK_UNDO
value|3
end_define

begin_define
DECL|macro|LAYER_DISPLACE_UNDO
define|#
directive|define
name|LAYER_DISPLACE_UNDO
value|4
end_define

begin_define
DECL|macro|TRANSFORM_UNDO
define|#
directive|define
name|TRANSFORM_UNDO
value|5
end_define

begin_define
DECL|macro|PAINT_UNDO
define|#
directive|define
name|PAINT_UNDO
value|6
end_define

begin_define
DECL|macro|LAYER_UNDO
define|#
directive|define
name|LAYER_UNDO
value|7
end_define

begin_define
DECL|macro|LAYER_MOD
define|#
directive|define
name|LAYER_MOD
value|8
end_define

begin_define
DECL|macro|LAYER_MASK_UNDO
define|#
directive|define
name|LAYER_MASK_UNDO
value|9
end_define

begin_define
DECL|macro|LAYER_CHANGE
define|#
directive|define
name|LAYER_CHANGE
value|10
end_define

begin_define
DECL|macro|LAYER_POSITION
define|#
directive|define
name|LAYER_POSITION
value|11
end_define

begin_define
DECL|macro|CHANNEL_UNDO
define|#
directive|define
name|CHANNEL_UNDO
value|12
end_define

begin_define
DECL|macro|CHANNEL_MOD
define|#
directive|define
name|CHANNEL_MOD
value|13
end_define

begin_define
DECL|macro|FS_TO_LAYER_UNDO
define|#
directive|define
name|FS_TO_LAYER_UNDO
value|14
end_define

begin_define
DECL|macro|GIMAGE_MOD
define|#
directive|define
name|GIMAGE_MOD
value|15
end_define

begin_define
DECL|macro|FS_RIGOR
define|#
directive|define
name|FS_RIGOR
value|16
end_define

begin_define
DECL|macro|FS_RELAX
define|#
directive|define
name|FS_RELAX
value|17
end_define

begin_define
DECL|macro|GUIDE_UNDO
define|#
directive|define
name|GUIDE_UNDO
value|18
end_define

begin_comment
comment|/*  Aggregate undo types  */
end_comment

begin_define
DECL|macro|FLOAT_MASK_UNDO
define|#
directive|define
name|FLOAT_MASK_UNDO
value|20
end_define

begin_define
DECL|macro|EDIT_PASTE_UNDO
define|#
directive|define
name|EDIT_PASTE_UNDO
value|21
end_define

begin_define
DECL|macro|EDIT_CUT_UNDO
define|#
directive|define
name|EDIT_CUT_UNDO
value|22
end_define

begin_define
DECL|macro|TRANSFORM_CORE_UNDO
define|#
directive|define
name|TRANSFORM_CORE_UNDO
value|23
end_define

begin_define
DECL|macro|PAINT_CORE_UNDO
define|#
directive|define
name|PAINT_CORE_UNDO
value|24
end_define

begin_define
DECL|macro|FLOATING_LAYER_UNDO
define|#
directive|define
name|FLOATING_LAYER_UNDO
value|25
end_define

begin_define
DECL|macro|LINKED_LAYER_UNDO
define|#
directive|define
name|LINKED_LAYER_UNDO
value|26
end_define

begin_define
DECL|macro|LAYER_APPLY_MASK_UNDO
define|#
directive|define
name|LAYER_APPLY_MASK_UNDO
value|27
end_define

begin_define
DECL|macro|LAYER_MERGE_UNDO
define|#
directive|define
name|LAYER_MERGE_UNDO
value|28
end_define

begin_define
DECL|macro|FS_ANCHOR_UNDO
define|#
directive|define
name|FS_ANCHOR_UNDO
value|29
end_define

begin_define
DECL|macro|GIMAGE_MOD_UNDO
define|#
directive|define
name|GIMAGE_MOD_UNDO
value|30
end_define

begin_define
DECL|macro|CROP_UNDO
define|#
directive|define
name|CROP_UNDO
value|31
end_define

begin_define
DECL|macro|LAYER_SCALE_UNDO
define|#
directive|define
name|LAYER_SCALE_UNDO
value|32
end_define

begin_define
DECL|macro|LAYER_RESIZE_UNDO
define|#
directive|define
name|LAYER_RESIZE_UNDO
value|33
end_define

begin_define
DECL|macro|MISC_UNDO
define|#
directive|define
name|MISC_UNDO
value|100
end_define

begin_comment
comment|/*  Undo interface functions  */
end_comment

begin_function_decl
name|int
name|undo_push_group_start
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_group_end
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_image
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
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_image_mod
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
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|void
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_mask
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_layer_displace
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpLayer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_transform
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_paint
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_layer
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_layer_mod
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_layer_mask
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_layer_change
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_layer_position
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_channel
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_channel_mod
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_fs_to_layer
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_fs_rigor
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_fs_relax
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_gimage_mod
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_guide
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_image_parasite
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_drawable_parasite
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_image_parasite_remove
parameter_list|(
name|GImage
modifier|*
parameter_list|,
specifier|const
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_drawable_parasite_remove
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
specifier|const
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_pop
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_redo
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|undo_free
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __UNDO_H__ */
end_comment

end_unit

