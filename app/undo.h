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

begin_comment
comment|/*  Argument to undo_event signal emitted by images  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon279f0a7d0103
block|{
DECL|enumerator|UNDO_PUSHED
name|UNDO_PUSHED
block|,
comment|/* a new undo has been added to the undo stack       */
DECL|enumerator|UNDO_EXPIRED
name|UNDO_EXPIRED
block|,
comment|/* an undo has been freed from the undo stack        */
DECL|enumerator|UNDO_POPPED
name|UNDO_POPPED
block|,
comment|/* an undo has been executed and moved to redo stack */
DECL|enumerator|UNDO_REDO
name|UNDO_REDO
block|,
comment|/* a redo has been executed and moved to undo stack  */
DECL|enumerator|UNDO_FREE
name|UNDO_FREE
comment|/* all undo and redo info has been cleared           */
DECL|typedef|undo_event_t
block|}
name|undo_event_t
typedef|;
end_typedef

begin_comment
comment|/*  Stack peeking functions  */
end_comment

begin_typedef
DECL|typedef|undo_map_fn
typedef|typedef
name|gint
function_decl|(
modifier|*
name|undo_map_fn
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|undoitemname
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  main undo functions  */
end_comment

begin_function_decl
name|gboolean
name|undo_pop
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_redo
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|undo_free
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|undo_get_undo_name
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|undo_get_redo_name
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|undo_map_over_undo_stack
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|undo_map_fn
name|fn
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|undo_map_over_redo_stack
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|undo_map_fn
name|fn
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|UndoType
name|undo_get_undo_top_type
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  undo groups  */
end_comment

begin_function_decl
name|gboolean
name|undo_push_group_start
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|UndoType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_group_end
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  image undos  */
end_comment

begin_function_decl
name|gboolean
name|undo_push_image
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_image_mod
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|gboolean
name|sparse
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_image_type
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_image_size
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_image_resolution
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_image_qmask
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_image_guide
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  mask undo  */
end_comment

begin_function_decl
name|gboolean
name|undo_push_mask
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannel
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  item undos  */
end_comment

begin_function_decl
name|gboolean
name|undo_push_item_rename
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  layer undos  */
end_comment

begin_function_decl
name|gboolean
name|undo_push_layer_add
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gint
name|prev_position
parameter_list|,
name|GimpLayer
modifier|*
name|prev_layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_layer_remove
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gint
name|prev_position
parameter_list|,
name|GimpLayer
modifier|*
name|prev_layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_layer_mod
parameter_list|(
name|GimpImage
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
name|gboolean
name|undo_push_layer_mask_add
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
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
name|undo_push_layer_mask_remove
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
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
name|undo_push_layer_reposition
parameter_list|(
name|GimpImage
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
name|gboolean
name|undo_push_layer_displace
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  channel undos  */
end_comment

begin_function_decl
name|gboolean
name|undo_push_channel_add
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gint
name|prev_position
parameter_list|,
name|GimpChannel
modifier|*
name|prev_channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_channel_remove
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gint
name|prev_position
parameter_list|,
name|GimpChannel
modifier|*
name|prev_channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_channel_mod
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_channel_reposition
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  vectors undos  */
end_comment

begin_function_decl
name|gboolean
name|undo_push_vectors_add
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|gint
name|prev_position
parameter_list|,
name|GimpVectors
modifier|*
name|prev_vectors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_vectors_remove
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpVectors
modifier|*
name|channel
parameter_list|,
name|gint
name|prev_position
parameter_list|,
name|GimpVectors
modifier|*
name|prev_vectors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_vectors_mod
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_vectors_reposition
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  floating selection undos  */
end_comment

begin_function_decl
name|gboolean
name|undo_push_fs_to_layer
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpLayer
modifier|*
name|floating_layer
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_fs_rigor
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_fs_relax
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  transform/paint drawable undos  */
end_comment

begin_function_decl
name|gboolean
name|undo_push_transform
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|tool_ID
parameter_list|,
name|GType
name|tool_type
parameter_list|,
name|gdouble
modifier|*
name|trans_info
parameter_list|,
name|TileManager
modifier|*
name|original
parameter_list|,
name|GSList
modifier|*
name|path_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_paint
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|core_ID
parameter_list|,
name|GType
name|core_type
parameter_list|,
name|GimpCoords
modifier|*
name|last_coords
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  parasite undos  */
end_comment

begin_function_decl
name|gboolean
name|undo_push_image_parasite
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gpointer
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_image_parasite_remove
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_item_parasite
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gpointer
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|undo_push_item_parasite_remove
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  EEK undo  */
end_comment

begin_function_decl
name|gboolean
name|undo_push_cantundo
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action
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

