begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMAGE_H__
end_ifndef

begin_define
DECL|macro|__GIMAGE_H__
define|#
directive|define
name|__GIMAGE_H__
end_define

begin_include
include|#
directive|include
file|"boundary.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"channel.h"
end_include

begin_include
include|#
directive|include
file|"layer.h"
end_include

begin_include
include|#
directive|include
file|"paint_funcs.h"
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

begin_comment
comment|/* the image types */
end_comment

begin_define
DECL|macro|RGB_GIMAGE
define|#
directive|define
name|RGB_GIMAGE
value|0
end_define

begin_define
DECL|macro|RGBA_GIMAGE
define|#
directive|define
name|RGBA_GIMAGE
value|1
end_define

begin_define
DECL|macro|GRAY_GIMAGE
define|#
directive|define
name|GRAY_GIMAGE
value|2
end_define

begin_define
DECL|macro|GRAYA_GIMAGE
define|#
directive|define
name|GRAYA_GIMAGE
value|3
end_define

begin_define
DECL|macro|INDEXED_GIMAGE
define|#
directive|define
name|INDEXED_GIMAGE
value|4
end_define

begin_define
DECL|macro|INDEXEDA_GIMAGE
define|#
directive|define
name|INDEXEDA_GIMAGE
value|5
end_define

begin_define
DECL|macro|TYPE_HAS_ALPHA (t)
define|#
directive|define
name|TYPE_HAS_ALPHA
parameter_list|(
name|t
parameter_list|)
value|((t)==RGBA_GIMAGE || (t)==GRAYA_GIMAGE || (t)==INDEXEDA_GIMAGE)
end_define

begin_define
DECL|macro|GRAY_PIX
define|#
directive|define
name|GRAY_PIX
value|0
end_define

begin_define
DECL|macro|ALPHA_G_PIX
define|#
directive|define
name|ALPHA_G_PIX
value|1
end_define

begin_define
DECL|macro|RED_PIX
define|#
directive|define
name|RED_PIX
value|0
end_define

begin_define
DECL|macro|GREEN_PIX
define|#
directive|define
name|GREEN_PIX
value|1
end_define

begin_define
DECL|macro|BLUE_PIX
define|#
directive|define
name|BLUE_PIX
value|2
end_define

begin_define
DECL|macro|ALPHA_PIX
define|#
directive|define
name|ALPHA_PIX
value|3
end_define

begin_define
DECL|macro|INDEXED_PIX
define|#
directive|define
name|INDEXED_PIX
value|0
end_define

begin_define
DECL|macro|ALPHA_I_PIX
define|#
directive|define
name|ALPHA_I_PIX
value|1
end_define

begin_define
DECL|macro|RGB
define|#
directive|define
name|RGB
value|0
end_define

begin_define
DECL|macro|GRAY
define|#
directive|define
name|GRAY
value|1
end_define

begin_define
DECL|macro|INDEXED
define|#
directive|define
name|INDEXED
value|2
end_define

begin_define
DECL|macro|MAX_CHANNELS
define|#
directive|define
name|MAX_CHANNELS
value|4
end_define

begin_comment
comment|/* the image fill types */
end_comment

begin_define
DECL|macro|BACKGROUND_FILL
define|#
directive|define
name|BACKGROUND_FILL
value|0
end_define

begin_define
DECL|macro|WHITE_FILL
define|#
directive|define
name|WHITE_FILL
value|1
end_define

begin_define
DECL|macro|TRANSPARENT_FILL
define|#
directive|define
name|TRANSPARENT_FILL
value|2
end_define

begin_define
DECL|macro|NO_FILL
define|#
directive|define
name|NO_FILL
value|3
end_define

begin_define
DECL|macro|COLORMAP_SIZE
define|#
directive|define
name|COLORMAP_SIZE
value|768
end_define

begin_define
DECL|macro|HORIZONTAL_GUIDE
define|#
directive|define
name|HORIZONTAL_GUIDE
value|1
end_define

begin_define
DECL|macro|VERTICAL_GUIDE
define|#
directive|define
name|VERTICAL_GUIDE
value|2
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a19a4d30103
block|{
DECL|enumerator|Red
name|Red
block|,
DECL|enumerator|Green
name|Green
block|,
DECL|enumerator|Blue
name|Blue
block|,
DECL|enumerator|Gray
name|Gray
block|,
DECL|enumerator|Indexed
name|Indexed
block|,
DECL|enumerator|Auxillary
name|Auxillary
DECL|typedef|ChannelType
block|}
name|ChannelType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a19a4d30203
block|{
DECL|enumerator|ExpandAsNecessary
name|ExpandAsNecessary
block|,
DECL|enumerator|ClipToImage
name|ClipToImage
block|,
DECL|enumerator|ClipToBottomLayer
name|ClipToBottomLayer
block|,
DECL|enumerator|FlattenImage
name|FlattenImage
DECL|typedef|MergeType
block|}
name|MergeType
typedef|;
end_typedef

begin_comment
comment|/* structure declarations */
end_comment

begin_typedef
DECL|typedef|Guide
typedef|typedef
name|struct
name|_Guide
name|Guide
typedef|;
end_typedef

begin_typedef
DECL|typedef|GImage
typedef|typedef
name|struct
name|_GImage
name|GImage
typedef|;
end_typedef

begin_struct
DECL|struct|_Guide
struct|struct
name|_Guide
block|{
DECL|member|position
name|int
name|position
decl_stmt|;
DECL|member|orientation
name|int
name|orientation
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GImage
struct|struct
name|_GImage
block|{
DECL|member|filename
name|char
modifier|*
name|filename
decl_stmt|;
comment|/*  original filename            */
DECL|member|has_filename
name|int
name|has_filename
decl_stmt|;
comment|/*  has a valid filename         */
DECL|member|width
DECL|member|height
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
comment|/*  width and height attributes  */
DECL|member|base_type
name|int
name|base_type
decl_stmt|;
comment|/*  base gimage type             */
DECL|member|cmap
name|unsigned
name|char
modifier|*
name|cmap
decl_stmt|;
comment|/*  colormap--for indexed        */
DECL|member|num_cols
name|int
name|num_cols
decl_stmt|;
comment|/*  number of cols--for indexed  */
DECL|member|dirty
name|int
name|dirty
decl_stmt|;
comment|/*  dirty flag -- # of ops       */
DECL|member|undo_on
name|int
name|undo_on
decl_stmt|;
comment|/*  Is undo enabled?             */
DECL|member|instance_count
name|int
name|instance_count
decl_stmt|;
comment|/*  number of instances          */
DECL|member|ref_count
name|int
name|ref_count
decl_stmt|;
comment|/*  number of references         */
DECL|member|shadow
name|TileManager
modifier|*
name|shadow
decl_stmt|;
comment|/*  shadow buffer tiles          */
DECL|member|ID
name|int
name|ID
decl_stmt|;
comment|/*  Unique gimage identifier     */
comment|/*  Projection attributes  */
DECL|member|flat
name|int
name|flat
decl_stmt|;
comment|/*  Is the gimage flat?          */
DECL|member|construct_flag
name|int
name|construct_flag
decl_stmt|;
comment|/*  flag for construction        */
DECL|member|proj_type
name|int
name|proj_type
decl_stmt|;
comment|/*  type of the projection image */
DECL|member|proj_bytes
name|int
name|proj_bytes
decl_stmt|;
comment|/*  bpp in projection image      */
DECL|member|proj_level
name|int
name|proj_level
decl_stmt|;
comment|/*  projection level             */
DECL|member|projection
name|TileManager
modifier|*
name|projection
decl_stmt|;
comment|/*  The projection--layers&     */
comment|/*  channels                     */
DECL|member|guides
name|GList
modifier|*
name|guides
decl_stmt|;
comment|/*  guides                       */
comment|/*  Layer/Channel attributes  */
DECL|member|layers
name|GSList
modifier|*
name|layers
decl_stmt|;
comment|/*  the list of layers           */
DECL|member|channels
name|GSList
modifier|*
name|channels
decl_stmt|;
comment|/*  the list of masks            */
DECL|member|layer_stack
name|GSList
modifier|*
name|layer_stack
decl_stmt|;
comment|/*  the layers in MRU order      */
DECL|member|active_layer
name|Layer
modifier|*
name|active_layer
decl_stmt|;
comment|/*  ID of active layer           */
DECL|member|active_channel
name|Channel
modifier|*
name|active_channel
decl_stmt|;
comment|/*  ID of active channel         */
DECL|member|floating_sel
name|Layer
modifier|*
name|floating_sel
decl_stmt|;
comment|/*  ID of fs layer               */
DECL|member|selection_mask
name|Channel
modifier|*
name|selection_mask
decl_stmt|;
comment|/*  selection mask channel       */
DECL|member|visible
name|int
name|visible
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
comment|/*  visible channels             */
DECL|member|active
name|int
name|active
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
comment|/*  active channels              */
DECL|member|by_color_select
name|int
name|by_color_select
decl_stmt|;
comment|/*  TRUE if there's an active    */
comment|/*  "by color" selection dialog  */
comment|/*  Undo apparatus  */
DECL|member|undo_stack
name|GSList
modifier|*
name|undo_stack
decl_stmt|;
comment|/*  stack for undo operations    */
DECL|member|redo_stack
name|GSList
modifier|*
name|redo_stack
decl_stmt|;
comment|/*  stack for redo operations    */
DECL|member|undo_bytes
name|int
name|undo_bytes
decl_stmt|;
comment|/*  bytes in undo stack          */
DECL|member|undo_levels
name|int
name|undo_levels
decl_stmt|;
comment|/*  levels in undo stack         */
DECL|member|pushing_undo_group
name|int
name|pushing_undo_group
decl_stmt|;
comment|/*  undo group status flag       */
comment|/*  Composite preview  */
DECL|member|comp_preview
name|TempBuf
modifier|*
name|comp_preview
decl_stmt|;
comment|/*  the composite preview        */
DECL|member|comp_preview_valid
name|int
name|comp_preview_valid
index|[
literal|3
index|]
decl_stmt|;
comment|/*  preview valid-1/channel      */
block|}
struct|;
end_struct

begin_comment
comment|/* function declarations */
end_comment

begin_function_decl
name|GImage
modifier|*
name|gimage_new
parameter_list|(
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
name|gimage_set_filename
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_resize
parameter_list|(
name|GImage
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
name|void
name|gimage_scale
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GImage
modifier|*
name|gimage_get_named
parameter_list|(
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GImage
modifier|*
name|gimage_get_ID
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|gimage_shadow
parameter_list|(
name|GImage
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
name|gimage_free_shadow
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_delete
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_apply_image
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|PixelRegion
modifier|*
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
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_replace_image
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|PixelRegion
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
name|gimage_get_foreground
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_get_background
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_get_color
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_transform_color
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Guide
modifier|*
name|gimage_add_hguide
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Guide
modifier|*
name|gimage_add_vguide
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_add_guide
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Guide
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_remove_guide
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Guide
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_delete_guide
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Guide
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  layer/channel functions  */
end_comment

begin_function_decl
name|int
name|gimage_get_layer_index
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_get_channel_index
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimage_get_active_layer
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimage_get_active_channel
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimage_get_mask
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_get_component_active
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|ChannelType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_get_component_visible
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|ChannelType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_layer_boundary
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|BoundSeg
modifier|*
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimage_set_active_layer
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimage_set_active_channel
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimage_unset_active_channel
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_set_component_active
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|ChannelType
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_set_component_visible
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|ChannelType
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimage_pick_correlate_layer
parameter_list|(
name|GImage
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
name|gimage_set_layer_mask_apply
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_set_layer_mask_edit
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_set_layer_mask_show
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimage_raise_layer
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimage_lower_layer
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimage_merge_visible_layers
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|MergeType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimage_flatten
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimage_merge_layers
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GSList
modifier|*
parameter_list|,
name|MergeType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimage_add_layer
parameter_list|(
name|GImage
modifier|*
parameter_list|,
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
name|gimage_remove_layer
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|gimage_add_layer_mask
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|,
name|LayerMask
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimage_remove_layer_mask
parameter_list|(
name|GImage
modifier|*
parameter_list|,
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
name|gimage_raise_channel
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimage_lower_channel
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimage_add_channel
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimage_remove_channel
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_construct
parameter_list|(
name|GImage
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
name|void
name|gimage_invalidate
parameter_list|(
name|GImage
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
name|void
name|gimage_validate
parameter_list|(
name|TileManager
modifier|*
parameter_list|,
name|Tile
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_inflate
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_deflate
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Access functions  */
end_comment

begin_function_decl
name|int
name|gimage_is_flat
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_is_empty
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDrawable
modifier|*
name|gimage_active_drawable
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_base_type
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_base_type_with_alpha
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|gimage_filename
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_enable_undo
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_disable_undo
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_dirty
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_clean
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_clean_all
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimage_floating_sel
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|unsigned
name|char
modifier|*
name|gimage_cmap
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  projection access functions  */
end_comment

begin_function_decl
name|TileManager
modifier|*
name|gimage_projection
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_projection_type
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_projection_bytes
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_projection_opacity
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_projection_realloc
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  composite access functions  */
end_comment

begin_function_decl
name|TileManager
modifier|*
name|gimage_composite
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_composite_type
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_composite_bytes
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|gimage_composite_preview
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|ChannelType
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimage_preview_valid
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|ChannelType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_invalidate_preview
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimage_invalidate_previews
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* from drawable.c */
end_comment

begin_function_decl
name|GImage
modifier|*
name|drawable_gimage
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMAGE_H__ */
end_comment

end_unit

