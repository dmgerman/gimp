begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__LAYER_H__
end_ifndef

begin_define
DECL|macro|__LAYER_H__
define|#
directive|define
name|__LAYER_H__
end_define

begin_include
include|#
directive|include
file|"boundary.h"
end_include

begin_include
include|#
directive|include
file|"channel.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager.h"
end_include

begin_define
DECL|macro|APPLY
define|#
directive|define
name|APPLY
value|0
end_define

begin_define
DECL|macro|DISCARD
define|#
directive|define
name|DISCARD
value|1
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29015f6d0103
block|{
DECL|enumerator|WhiteMask
name|WhiteMask
block|,
DECL|enumerator|BlackMask
name|BlackMask
block|,
DECL|enumerator|AlphaMask
name|AlphaMask
DECL|typedef|AddMaskType
block|}
name|AddMaskType
typedef|;
end_typedef

begin_comment
comment|/* structure declarations */
end_comment

begin_typedef
DECL|typedef|Layer
typedef|typedef
name|struct
name|_Layer
name|Layer
typedef|;
end_typedef

begin_struct
DECL|struct|_Layer
struct|struct
name|_Layer
block|{
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
comment|/*  name of the layer            */
DECL|member|tiles
name|TileManager
modifier|*
name|tiles
decl_stmt|;
comment|/*  Tiles for layer data         */
DECL|member|visible
name|int
name|visible
decl_stmt|;
comment|/*  controls visibility          */
DECL|member|linked
name|int
name|linked
decl_stmt|;
comment|/*  control linkage              */
DECL|member|preserve_trans
name|int
name|preserve_trans
decl_stmt|;
comment|/*  preserve transparency?       */
DECL|member|mask
name|Channel
modifier|*
name|mask
decl_stmt|;
comment|/*  possible layer mask          */
DECL|member|apply_mask
name|int
name|apply_mask
decl_stmt|;
comment|/*  controls mask application    */
DECL|member|edit_mask
name|int
name|edit_mask
decl_stmt|;
comment|/*  edit mask or layer?          */
DECL|member|show_mask
name|int
name|show_mask
decl_stmt|;
comment|/*  show mask or layer?          */
DECL|member|offset_x
DECL|member|offset_y
name|int
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
comment|/*  offset of layer in image     */
DECL|member|type
name|int
name|type
decl_stmt|;
comment|/*  type of image                */
DECL|member|width
DECL|member|height
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
comment|/*  size of layer                */
DECL|member|bytes
name|int
name|bytes
decl_stmt|;
comment|/*  bytes per pixel              */
DECL|member|opacity
name|int
name|opacity
decl_stmt|;
comment|/*  layer opacity                */
DECL|member|mode
name|int
name|mode
decl_stmt|;
comment|/*  layer combination mode       */
DECL|member|dirty
name|int
name|dirty
decl_stmt|;
comment|/*  dirty bit                    */
DECL|member|ID
name|int
name|ID
decl_stmt|;
comment|/*  provides a unique ID         */
DECL|member|gimage_ID
name|int
name|gimage_ID
decl_stmt|;
comment|/*  ID of gimage owner           */
comment|/*  Preview variables  */
DECL|member|preview
name|TempBuf
modifier|*
name|preview
decl_stmt|;
comment|/*  preview of the channel       */
DECL|member|preview_valid
name|int
name|preview_valid
decl_stmt|;
comment|/*  is the preview valid?        */
comment|/*  Floating selections  */
struct|struct
DECL|struct|__anon29015f6d0208
block|{
DECL|member|backing_store
name|TileManager
modifier|*
name|backing_store
decl_stmt|;
comment|/*  for obscured regions         */
DECL|member|drawable
name|int
name|drawable
decl_stmt|;
comment|/*  floating sel is attached to  */
DECL|member|initial
name|int
name|initial
decl_stmt|;
comment|/*  is fs composited yet?        */
DECL|member|boundary_known
name|int
name|boundary_known
decl_stmt|;
comment|/*  is the current boundary valid*/
DECL|member|segs
name|BoundSeg
modifier|*
name|segs
decl_stmt|;
comment|/*  boundary of floating sel     */
DECL|member|num_segs
name|int
name|num_segs
decl_stmt|;
comment|/*  number of segs in boundary   */
DECL|member|fs
block|}
name|fs
struct|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Special undo types  */
end_comment

begin_typedef
DECL|typedef|LayerUndo
typedef|typedef
name|struct
name|_layer_undo
name|LayerUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_layer_undo
struct|struct
name|_layer_undo
block|{
DECL|member|layer
name|Layer
modifier|*
name|layer
decl_stmt|;
comment|/*  the actual layer         */
DECL|member|prev_position
name|int
name|prev_position
decl_stmt|;
comment|/*  former position in list  */
DECL|member|prev_layer
name|int
name|prev_layer
decl_stmt|;
comment|/*  previous active layer    */
DECL|member|undo_type
name|int
name|undo_type
decl_stmt|;
comment|/*  is this a new layer undo */
comment|/*  or a remove layer undo?  */
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|LayerMaskUndo
typedef|typedef
name|struct
name|_layer_mask_undo
name|LayerMaskUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_layer_mask_undo
struct|struct
name|_layer_mask_undo
block|{
DECL|member|layer
name|Layer
modifier|*
name|layer
decl_stmt|;
comment|/*  the layer                */
DECL|member|apply_mask
name|int
name|apply_mask
decl_stmt|;
comment|/*  apply mask?              */
DECL|member|edit_mask
name|int
name|edit_mask
decl_stmt|;
comment|/*  edit mask or layer?      */
DECL|member|show_mask
name|int
name|show_mask
decl_stmt|;
comment|/*  show the mask?           */
DECL|member|mask
name|Channel
modifier|*
name|mask
decl_stmt|;
comment|/*  the layer mask           */
DECL|member|mode
name|int
name|mode
decl_stmt|;
comment|/*  the application mode     */
DECL|member|undo_type
name|int
name|undo_type
decl_stmt|;
comment|/*  is this a new layer mask */
comment|/*  or a remove layer mask   */
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|FStoLayerUndo
typedef|typedef
name|struct
name|_fs_to_layer_undo
name|FStoLayerUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_fs_to_layer_undo
struct|struct
name|_fs_to_layer_undo
block|{
DECL|member|layer
name|Layer
modifier|*
name|layer
decl_stmt|;
comment|/*  the layer                */
DECL|member|drawable
name|int
name|drawable
decl_stmt|;
comment|/*  drawable of floating sel */
block|}
struct|;
end_struct

begin_comment
comment|/* function declarations */
end_comment

begin_function_decl
name|void
name|layer_allocate
parameter_list|(
name|Layer
modifier|*
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
name|void
name|layer_deallocate
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|layer_new
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|char
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|layer_copy
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|layer_from_tiles
parameter_list|(
name|void
modifier|*
parameter_list|,
name|int
parameter_list|,
name|TileManager
modifier|*
parameter_list|,
name|char
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|layer_add_mask
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|layer_create_mask
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|AddMaskType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|layer_get_ID
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_delete
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_apply_mask
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_translate
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_apply_image
parameter_list|(
name|Layer
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
name|TileManager
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_add_alpha
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_scale
parameter_list|(
name|Layer
modifier|*
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
name|void
name|layer_resize
parameter_list|(
name|Layer
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
name|BoundSeg
modifier|*
name|layer_boundary
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_invalidate_boundary
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|layer_pick_correlate
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* access functions */
end_comment

begin_function_decl
name|unsigned
name|char
modifier|*
name|layer_data
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|layer_mask
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|layer_has_alpha
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|layer_is_floating_sel
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|layer_preview
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|layer_mask_preview
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_invalidate_previews
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __LAYER_H__ */
end_comment

end_unit

