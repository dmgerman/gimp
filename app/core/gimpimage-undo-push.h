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
file|"undo_types.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

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
name|UndoType
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
name|UndoType
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
name|UndoType
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
name|GimpLayer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_layer_reposition
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
name|undo_push_channel
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|UndoType
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
name|undo_push_qmask
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_resolution
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|undo_push_layer_rename
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
name|undo_push_cantundo
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

begin_function_decl
specifier|const
name|char
modifier|*
name|undo_get_undo_name
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|char
modifier|*
name|undo_get_redo_name
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Stack peeking functions */
end_comment

begin_typedef
DECL|typedef|undo_map_fn
typedef|typedef
name|int
function_decl|(
modifier|*
name|undo_map_fn
function_decl|)
parameter_list|(
specifier|const
name|char
modifier|*
name|undoitemname
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|undo_map_over_undo_stack
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|undo_map_fn
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|undo_map_over_redo_stack
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|undo_map_fn
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Not really appropriate here, since undo_history_new is not defined  * in undo.c, but it saves on having a full header file for just one  * function prototype. */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|undo_history_new
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Argument to undo_event signal emitted by gimages: */
end_comment

begin_typedef
DECL|enum|__anon2a23483a0103
typedef|typedef
enum|enum
block|{
DECL|enumerator|UNDO_PUSHED
name|UNDO_PUSHED
block|,
comment|/* a new undo has been added to the undo stack */
DECL|enumerator|UNDO_EXPIRED
name|UNDO_EXPIRED
block|,
comment|/* an undo has been freed from the undo stack */
DECL|enumerator|UNDO_POPPED
name|UNDO_POPPED
block|,
comment|/* an undo has been executed and moved to redo stack */
DECL|enumerator|UNDO_REDO
name|UNDO_REDO
block|,
comment|/* a redo has been executed and moved to undo stack */
DECL|enumerator|UNDO_FREE
name|UNDO_FREE
comment|/* all undo and redo info has been cleared */
DECL|typedef|undo_event_t
block|}
name|undo_event_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __UNDO_H__ */
end_comment

end_unit

