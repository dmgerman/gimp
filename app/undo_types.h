begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__UNDO_TYPES_H__
end_ifndef

begin_define
DECL|macro|__UNDO_TYPES_H__
define|#
directive|define
name|__UNDO_TYPES_H__
end_define

begin_comment
comment|/*  Undo types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2926394a0103
block|{
comment|/* Type 0 is special - in the gimpimage structure it means      * there is no undo group currently being added to. */
DECL|enumerator|IMAGE_UNDO
name|IMAGE_UNDO
init|=
literal|1
block|,
DECL|enumerator|IMAGE_MOD_UNDO
name|IMAGE_MOD_UNDO
block|,
DECL|enumerator|MASK_UNDO
name|MASK_UNDO
block|,
DECL|enumerator|LAYER_DISPLACE_UNDO
name|LAYER_DISPLACE_UNDO
block|,
DECL|enumerator|TRANSFORM_UNDO
name|TRANSFORM_UNDO
block|,
DECL|enumerator|PAINT_UNDO
name|PAINT_UNDO
block|,
DECL|enumerator|LAYER_UNDO
name|LAYER_UNDO
block|,
DECL|enumerator|LAYER_MOD
name|LAYER_MOD
block|,
DECL|enumerator|LAYER_MASK_UNDO
name|LAYER_MASK_UNDO
block|,
DECL|enumerator|LAYER_CHANGE
name|LAYER_CHANGE
block|,
DECL|enumerator|LAYER_POSITION
name|LAYER_POSITION
block|,
DECL|enumerator|CHANNEL_UNDO
name|CHANNEL_UNDO
block|,
DECL|enumerator|CHANNEL_MOD
name|CHANNEL_MOD
block|,
DECL|enumerator|FS_TO_LAYER_UNDO
name|FS_TO_LAYER_UNDO
block|,
DECL|enumerator|GIMAGE_MOD
name|GIMAGE_MOD
block|,
DECL|enumerator|FS_RIGOR
name|FS_RIGOR
block|,
DECL|enumerator|FS_RELAX
name|FS_RELAX
block|,
DECL|enumerator|GUIDE_UNDO
name|GUIDE_UNDO
block|,
comment|/*  18 */
comment|/*  Aggregate undo types  */
DECL|enumerator|FLOAT_MASK_UNDO
name|FLOAT_MASK_UNDO
init|=
literal|20
block|,
DECL|enumerator|EDIT_PASTE_UNDO
name|EDIT_PASTE_UNDO
block|,
DECL|enumerator|EDIT_CUT_UNDO
name|EDIT_CUT_UNDO
block|,
DECL|enumerator|TRANSFORM_CORE_UNDO
name|TRANSFORM_CORE_UNDO
block|,
DECL|enumerator|PAINT_CORE_UNDO
name|PAINT_CORE_UNDO
block|,
DECL|enumerator|FLOATING_LAYER_UNDO
name|FLOATING_LAYER_UNDO
block|,
DECL|enumerator|LINKED_LAYER_UNDO
name|LINKED_LAYER_UNDO
block|,
DECL|enumerator|LAYER_APPLY_MASK_UNDO
name|LAYER_APPLY_MASK_UNDO
block|,
DECL|enumerator|LAYER_MERGE_UNDO
name|LAYER_MERGE_UNDO
block|,
comment|/*  28  */
DECL|enumerator|FS_ANCHOR_UNDO
name|FS_ANCHOR_UNDO
block|,
DECL|enumerator|GIMAGE_MOD_UNDO
name|GIMAGE_MOD_UNDO
block|,
DECL|enumerator|CROP_UNDO
name|CROP_UNDO
block|,
DECL|enumerator|LAYER_SCALE_UNDO
name|LAYER_SCALE_UNDO
block|,
DECL|enumerator|LAYER_RESIZE_UNDO
name|LAYER_RESIZE_UNDO
block|,
DECL|enumerator|QMASK_UNDO
name|QMASK_UNDO
block|,
comment|/*  34 */
DECL|enumerator|RESOLUTION_UNDO
name|RESOLUTION_UNDO
block|,
DECL|enumerator|MISC_UNDO
name|MISC_UNDO
init|=
literal|100
DECL|typedef|UndoType
block|}
name|UndoType
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __UNDO_TYPES_H__ */
end_comment

end_unit

