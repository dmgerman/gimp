begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-processor.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/tile.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-contiguous-region.h"
end_include

begin_include
include|#
directive|include
file|"gimppickable.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon290dc0000108
block|{
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
DECL|member|type
name|GimpImageType
name|type
decl_stmt|;
DECL|member|sample_merged
name|gboolean
name|sample_merged
decl_stmt|;
DECL|member|antialias
name|gboolean
name|antialias
decl_stmt|;
DECL|member|threshold
name|gint
name|threshold
decl_stmt|;
DECL|member|select_transparent
name|gboolean
name|select_transparent
decl_stmt|;
DECL|member|has_alpha
name|gboolean
name|has_alpha
decl_stmt|;
DECL|member|color_bytes
name|gint
name|color_bytes
decl_stmt|;
DECL|member|color
name|guchar
name|color
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
DECL|typedef|ContinuousRegionData
block|}
name|ContinuousRegionData
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|contiguous_region_by_color
parameter_list|(
name|ContinuousRegionData
modifier|*
name|cont
parameter_list|,
name|PixelRegion
modifier|*
name|imagePR
parameter_list|,
name|PixelRegion
modifier|*
name|maskPR
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|pixel_difference
parameter_list|(
name|guchar
modifier|*
name|col1
parameter_list|,
name|guchar
modifier|*
name|col2
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gint
name|threshold
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ref_tiles
parameter_list|(
name|TileManager
modifier|*
name|src
parameter_list|,
name|TileManager
modifier|*
name|mask
parameter_list|,
name|Tile
modifier|*
modifier|*
name|s_tile
parameter_list|,
name|Tile
modifier|*
modifier|*
name|m_tile
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guchar
modifier|*
modifier|*
name|s
parameter_list|,
name|guchar
modifier|*
modifier|*
name|m
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|find_contiguous_segment
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|guchar
modifier|*
name|col
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|GimpImageType
name|src_type
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gint
name|threshold
parameter_list|,
name|gint
name|initial
parameter_list|,
name|gint
modifier|*
name|start
parameter_list|,
name|gint
modifier|*
name|end
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|find_contiguous_region_helper
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|GimpImageType
name|src_type
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gint
name|threshold
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guchar
modifier|*
name|col
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpChannel
modifier|*
DECL|function|gimp_image_contiguous_region_by_seed (GimpImage * gimage,GimpDrawable * drawable,gboolean sample_merged,gboolean antialias,gint threshold,gboolean select_transparent,gint x,gint y)
name|gimp_image_contiguous_region_by_seed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gint
name|threshold
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|PixelRegion
name|srcPR
decl_stmt|,
name|maskPR
decl_stmt|;
name|GimpPickable
modifier|*
name|pickable
decl_stmt|;
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
name|GimpImageType
name|src_type
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|Tile
modifier|*
name|tile
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|sample_merged
condition|)
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|gimage
operator|->
name|projection
argument_list|)
expr_stmt|;
else|else
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|src_type
operator|=
name|gimp_pickable_get_image_type
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|GIMP_IMAGE_TYPE_HAS_ALPHA
argument_list|(
name|src_type
argument_list|)
expr_stmt|;
name|bytes
operator|=
name|GIMP_IMAGE_TYPE_BYTES
argument_list|(
name|src_type
argument_list|)
expr_stmt|;
name|tiles
operator|=
name|gimp_pickable_get_tiles
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|tile_manager_width
argument_list|(
name|tiles
argument_list|)
argument_list|,
name|tile_manager_height
argument_list|(
name|tiles
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gimp_channel_new_mask
argument_list|(
name|gimage
argument_list|,
name|srcPR
operator|.
name|w
argument_list|,
name|srcPR
operator|.
name|h
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|tile
operator|=
name|tile_manager_get_tile
argument_list|(
name|srcPR
operator|.
name|tiles
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|tile
condition|)
block|{
name|guchar
modifier|*
name|start
decl_stmt|;
name|guchar
name|start_col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|start
operator|=
name|tile_data_pointer
argument_list|(
name|tile
argument_list|,
name|x
operator|%
name|TILE_WIDTH
argument_list|,
name|y
operator|%
name|TILE_HEIGHT
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
if|if
condition|(
name|select_transparent
condition|)
block|{
comment|/*  don't select transparent regions if the start pixel isn't                *  fully transparent                */
if|if
condition|(
name|start
index|[
name|bytes
operator|-
literal|1
index|]
operator|>
literal|0
condition|)
name|select_transparent
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
else|else
block|{
name|select_transparent
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|GIMP_IMAGE_TYPE_IS_INDEXED
argument_list|(
name|src_type
argument_list|)
condition|)
block|{
name|gimp_image_get_color
argument_list|(
name|gimage
argument_list|,
name|src_type
argument_list|,
name|start
argument_list|,
name|start_col
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bytes
condition|;
name|i
operator|++
control|)
name|start_col
index|[
name|i
index|]
operator|=
name|start
index|[
name|i
index|]
expr_stmt|;
block|}
name|find_contiguous_region_helper
argument_list|(
name|gimage
argument_list|,
operator|&
name|maskPR
argument_list|,
operator|&
name|srcPR
argument_list|,
name|src_type
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|start_col
argument_list|)
expr_stmt|;
name|tile_release
argument_list|(
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
return|return
name|mask
return|;
block|}
end_function

begin_function
name|GimpChannel
modifier|*
DECL|function|gimp_image_contiguous_region_by_color (GimpImage * gimage,GimpDrawable * drawable,gboolean sample_merged,gboolean antialias,gint threshold,gboolean select_transparent,const GimpRGB * color)
name|gimp_image_contiguous_region_by_color
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gint
name|threshold
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
comment|/*  Scan over the gimage's active layer, finding pixels within the    *  specified threshold from the given R, G,& B values.  If    *  antialiasing is on, use the same antialiasing scheme as in    *  fuzzy_select.  Modify the gimage's mask to reflect the    *  additional selection    */
name|GimpPickable
modifier|*
name|pickable
decl_stmt|;
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
name|PixelRegion
name|imagePR
decl_stmt|,
name|maskPR
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|ContinuousRegionData
name|cont
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
name|color
argument_list|,
name|cont
operator|.
name|color
operator|+
literal|0
argument_list|,
name|cont
operator|.
name|color
operator|+
literal|1
argument_list|,
name|cont
operator|.
name|color
operator|+
literal|2
argument_list|,
name|cont
operator|.
name|color
operator|+
literal|3
argument_list|)
expr_stmt|;
if|if
condition|(
name|sample_merged
condition|)
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|gimage
operator|->
name|projection
argument_list|)
expr_stmt|;
else|else
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|cont
operator|.
name|type
operator|=
name|gimp_pickable_get_image_type
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|cont
operator|.
name|has_alpha
operator|=
name|GIMP_IMAGE_TYPE_HAS_ALPHA
argument_list|(
name|cont
operator|.
name|type
argument_list|)
expr_stmt|;
name|tiles
operator|=
name|gimp_pickable_get_tiles
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|width
operator|=
name|tile_manager_width
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
name|height
operator|=
name|tile_manager_height
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|imagePR
argument_list|,
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|cont
operator|.
name|has_alpha
condition|)
block|{
if|if
condition|(
name|select_transparent
condition|)
block|{
comment|/*  don't select transparancy if "color" isn't fully transparent            */
if|if
condition|(
name|cont
operator|.
name|color
index|[
literal|3
index|]
operator|>
literal|0
condition|)
name|select_transparent
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
else|else
block|{
name|select_transparent
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|GIMP_IMAGE_TYPE_IS_INDEXED
argument_list|(
name|cont
operator|.
name|type
argument_list|)
condition|)
block|{
comment|/* indexed colors are always RGB or RGBA */
name|cont
operator|.
name|color_bytes
operator|=
name|cont
operator|.
name|has_alpha
condition|?
literal|4
else|:
literal|3
expr_stmt|;
block|}
else|else
block|{
comment|/* RGB, RGBA, GRAY and GRAYA colors are shaped just like the image */
name|cont
operator|.
name|color_bytes
operator|=
name|imagePR
operator|.
name|bytes
expr_stmt|;
block|}
name|cont
operator|.
name|gimage
operator|=
name|gimage
expr_stmt|;
name|cont
operator|.
name|antialias
operator|=
name|antialias
expr_stmt|;
name|cont
operator|.
name|threshold
operator|=
name|threshold
expr_stmt|;
name|cont
operator|.
name|select_transparent
operator|=
name|select_transparent
expr_stmt|;
name|mask
operator|=
name|gimp_channel_new_mask
argument_list|(
name|gimage
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pixel_regions_process_parallel
argument_list|(
operator|(
name|PixelProcessorFunc
operator|)
name|contiguous_region_by_color
argument_list|,
operator|&
name|cont
argument_list|,
literal|2
argument_list|,
operator|&
name|imagePR
argument_list|,
operator|&
name|maskPR
argument_list|)
expr_stmt|;
return|return
name|mask
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|contiguous_region_by_color (ContinuousRegionData * cont,PixelRegion * imagePR,PixelRegion * maskPR)
name|contiguous_region_by_color
parameter_list|(
name|ContinuousRegionData
modifier|*
name|cont
parameter_list|,
name|PixelRegion
modifier|*
name|imagePR
parameter_list|,
name|PixelRegion
modifier|*
name|maskPR
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|image
init|=
name|imagePR
operator|->
name|data
decl_stmt|;
name|guchar
modifier|*
name|mask
init|=
name|maskPR
operator|->
name|data
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|imagePR
operator|->
name|h
condition|;
name|y
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|i
init|=
name|image
decl_stmt|;
name|guchar
modifier|*
name|m
init|=
name|mask
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|imagePR
operator|->
name|w
condition|;
name|x
operator|++
control|)
block|{
name|guchar
name|rgb
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
comment|/*  Get the rgb values for the color  */
name|gimp_image_get_color
argument_list|(
name|cont
operator|->
name|gimage
argument_list|,
name|cont
operator|->
name|type
argument_list|,
name|i
argument_list|,
name|rgb
argument_list|)
expr_stmt|;
comment|/*  Find how closely the colors match  */
operator|*
name|m
operator|++
operator|=
name|pixel_difference
argument_list|(
name|cont
operator|->
name|color
argument_list|,
name|rgb
argument_list|,
name|cont
operator|->
name|antialias
argument_list|,
name|cont
operator|->
name|threshold
argument_list|,
name|cont
operator|->
name|color_bytes
argument_list|,
name|cont
operator|->
name|has_alpha
argument_list|,
name|cont
operator|->
name|select_transparent
argument_list|)
expr_stmt|;
name|i
operator|+=
name|imagePR
operator|->
name|bytes
expr_stmt|;
block|}
name|image
operator|+=
name|imagePR
operator|->
name|rowstride
expr_stmt|;
name|mask
operator|+=
name|maskPR
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|pixel_difference (guchar * col1,guchar * col2,gboolean antialias,gint threshold,gint bytes,gboolean has_alpha,gboolean select_transparent)
name|pixel_difference
parameter_list|(
name|guchar
modifier|*
name|col1
parameter_list|,
name|guchar
modifier|*
name|col2
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gint
name|threshold
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|)
block|{
name|gint
name|max
init|=
literal|0
decl_stmt|;
comment|/*  if there is an alpha channel, never select transparent regions  */
if|if
condition|(
operator|!
name|select_transparent
operator|&&
name|has_alpha
operator|&&
name|col2
index|[
name|bytes
operator|-
literal|1
index|]
operator|==
literal|0
condition|)
return|return
literal|0
return|;
if|if
condition|(
name|select_transparent
operator|&&
name|has_alpha
condition|)
block|{
name|max
operator|=
name|abs
argument_list|(
name|col1
index|[
name|bytes
operator|-
literal|1
index|]
operator|-
name|col2
index|[
name|bytes
operator|-
literal|1
index|]
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|diff
decl_stmt|;
name|gint
name|b
decl_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|bytes
operator|--
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bytes
condition|;
name|b
operator|++
control|)
block|{
name|diff
operator|=
name|abs
argument_list|(
name|col1
index|[
name|b
index|]
operator|-
name|col2
index|[
name|b
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|diff
operator|>
name|max
condition|)
name|max
operator|=
name|diff
expr_stmt|;
block|}
block|}
if|if
condition|(
name|antialias
operator|&&
name|threshold
operator|>
literal|0
condition|)
block|{
name|gfloat
name|aa
init|=
literal|1.5
operator|-
operator|(
operator|(
name|gfloat
operator|)
name|max
operator|/
name|threshold
operator|)
decl_stmt|;
if|if
condition|(
name|aa
operator|<=
literal|0.0
condition|)
return|return
literal|0
return|;
elseif|else
if|if
condition|(
name|aa
operator|<
literal|0.5
condition|)
return|return
call|(
name|guchar
call|)
argument_list|(
name|aa
operator|*
literal|512
argument_list|)
return|;
else|else
return|return
literal|255
return|;
block|}
else|else
block|{
if|if
condition|(
name|max
operator|>
name|threshold
condition|)
return|return
literal|0
return|;
else|else
return|return
literal|255
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ref_tiles (TileManager * src,TileManager * mask,Tile ** s_tile,Tile ** m_tile,gint x,gint y,guchar ** s,guchar ** m)
name|ref_tiles
parameter_list|(
name|TileManager
modifier|*
name|src
parameter_list|,
name|TileManager
modifier|*
name|mask
parameter_list|,
name|Tile
modifier|*
modifier|*
name|s_tile
parameter_list|,
name|Tile
modifier|*
modifier|*
name|m_tile
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guchar
modifier|*
modifier|*
name|s
parameter_list|,
name|guchar
modifier|*
modifier|*
name|m
parameter_list|)
block|{
if|if
condition|(
operator|*
name|s_tile
operator|!=
name|NULL
condition|)
name|tile_release
argument_list|(
operator|*
name|s_tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|m_tile
operator|!=
name|NULL
condition|)
name|tile_release
argument_list|(
operator|*
name|m_tile
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
operator|*
name|s_tile
operator|=
name|tile_manager_get_tile
argument_list|(
name|src
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
operator|*
name|m_tile
operator|=
name|tile_manager_get_tile
argument_list|(
name|mask
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
operator|*
name|s
operator|=
name|tile_data_pointer
argument_list|(
operator|*
name|s_tile
argument_list|,
name|x
operator|%
name|TILE_WIDTH
argument_list|,
name|y
operator|%
name|TILE_HEIGHT
argument_list|)
expr_stmt|;
operator|*
name|m
operator|=
name|tile_data_pointer
argument_list|(
operator|*
name|m_tile
argument_list|,
name|x
operator|%
name|TILE_WIDTH
argument_list|,
name|y
operator|%
name|TILE_HEIGHT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|find_contiguous_segment (GimpImage * gimage,guchar * col,PixelRegion * src,PixelRegion * mask,gint width,gint bytes,GimpImageType src_type,gboolean has_alpha,gboolean select_transparent,gboolean antialias,gint threshold,gint initial,gint * start,gint * end)
name|find_contiguous_segment
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|guchar
modifier|*
name|col
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|GimpImageType
name|src_type
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gint
name|threshold
parameter_list|,
name|gint
name|initial
parameter_list|,
name|gint
modifier|*
name|start
parameter_list|,
name|gint
modifier|*
name|end
parameter_list|)
block|{
name|guchar
modifier|*
name|s
decl_stmt|;
name|guchar
modifier|*
name|m
decl_stmt|;
name|guchar
name|s_color
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|guchar
name|diff
decl_stmt|;
name|gint
name|col_bytes
init|=
name|bytes
decl_stmt|;
name|Tile
modifier|*
name|s_tile
init|=
name|NULL
decl_stmt|;
name|Tile
modifier|*
name|m_tile
init|=
name|NULL
decl_stmt|;
name|ref_tiles
argument_list|(
name|src
operator|->
name|tiles
argument_list|,
name|mask
operator|->
name|tiles
argument_list|,
operator|&
name|s_tile
argument_list|,
operator|&
name|m_tile
argument_list|,
name|src
operator|->
name|x
argument_list|,
name|src
operator|->
name|y
argument_list|,
operator|&
name|s
argument_list|,
operator|&
name|m
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IMAGE_TYPE_IS_INDEXED
argument_list|(
name|src_type
argument_list|)
condition|)
block|{
name|col_bytes
operator|=
name|has_alpha
condition|?
literal|4
else|:
literal|3
expr_stmt|;
name|gimp_image_get_color
argument_list|(
name|gimage
argument_list|,
name|src_type
argument_list|,
name|s
argument_list|,
name|s_color
argument_list|)
expr_stmt|;
name|diff
operator|=
name|pixel_difference
argument_list|(
name|col
argument_list|,
name|s_color
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|col_bytes
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|diff
operator|=
name|pixel_difference
argument_list|(
name|col
argument_list|,
name|s
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|col_bytes
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|)
expr_stmt|;
block|}
comment|/* check the starting pixel */
if|if
condition|(
operator|!
name|diff
condition|)
block|{
name|tile_release
argument_list|(
name|s_tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tile_release
argument_list|(
name|m_tile
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
operator|*
name|m
operator|--
operator|=
name|diff
expr_stmt|;
name|s
operator|-=
name|bytes
expr_stmt|;
operator|*
name|start
operator|=
name|initial
operator|-
literal|1
expr_stmt|;
while|while
condition|(
operator|*
name|start
operator|>=
literal|0
operator|&&
name|diff
condition|)
block|{
if|if
condition|(
operator|!
operator|(
operator|(
operator|*
name|start
operator|+
literal|1
operator|)
operator|%
name|TILE_WIDTH
operator|)
condition|)
name|ref_tiles
argument_list|(
name|src
operator|->
name|tiles
argument_list|,
name|mask
operator|->
name|tiles
argument_list|,
operator|&
name|s_tile
argument_list|,
operator|&
name|m_tile
argument_list|,
operator|*
name|start
argument_list|,
name|src
operator|->
name|y
argument_list|,
operator|&
name|s
argument_list|,
operator|&
name|m
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IMAGE_TYPE_IS_INDEXED
argument_list|(
name|src_type
argument_list|)
condition|)
block|{
name|gimp_image_get_color
argument_list|(
name|gimage
argument_list|,
name|src_type
argument_list|,
name|s
argument_list|,
name|s_color
argument_list|)
expr_stmt|;
name|diff
operator|=
name|pixel_difference
argument_list|(
name|col
argument_list|,
name|s_color
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|col_bytes
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|diff
operator|=
name|pixel_difference
argument_list|(
name|col
argument_list|,
name|s
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|col_bytes
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
operator|*
name|m
operator|--
operator|=
name|diff
operator|)
condition|)
block|{
name|s
operator|-=
name|bytes
expr_stmt|;
operator|(
operator|*
name|start
operator|)
operator|--
expr_stmt|;
block|}
block|}
name|diff
operator|=
literal|1
expr_stmt|;
operator|*
name|end
operator|=
name|initial
operator|+
literal|1
expr_stmt|;
if|if
condition|(
operator|*
name|end
operator|%
name|TILE_WIDTH
operator|&&
operator|*
name|end
operator|<
name|width
condition|)
name|ref_tiles
argument_list|(
name|src
operator|->
name|tiles
argument_list|,
name|mask
operator|->
name|tiles
argument_list|,
operator|&
name|s_tile
argument_list|,
operator|&
name|m_tile
argument_list|,
operator|*
name|end
argument_list|,
name|src
operator|->
name|y
argument_list|,
operator|&
name|s
argument_list|,
operator|&
name|m
argument_list|)
expr_stmt|;
while|while
condition|(
operator|*
name|end
operator|<
name|width
operator|&&
name|diff
condition|)
block|{
if|if
condition|(
operator|!
operator|(
operator|*
name|end
operator|%
name|TILE_WIDTH
operator|)
condition|)
name|ref_tiles
argument_list|(
name|src
operator|->
name|tiles
argument_list|,
name|mask
operator|->
name|tiles
argument_list|,
operator|&
name|s_tile
argument_list|,
operator|&
name|m_tile
argument_list|,
operator|*
name|end
argument_list|,
name|src
operator|->
name|y
argument_list|,
operator|&
name|s
argument_list|,
operator|&
name|m
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IMAGE_TYPE_IS_INDEXED
argument_list|(
name|src_type
argument_list|)
condition|)
block|{
name|gimp_image_get_color
argument_list|(
name|gimage
argument_list|,
name|src_type
argument_list|,
name|s
argument_list|,
name|s_color
argument_list|)
expr_stmt|;
name|diff
operator|=
name|pixel_difference
argument_list|(
name|col
argument_list|,
name|s_color
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|col_bytes
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|diff
operator|=
name|pixel_difference
argument_list|(
name|col
argument_list|,
name|s
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|col_bytes
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
operator|*
name|m
operator|++
operator|=
name|diff
operator|)
condition|)
block|{
name|s
operator|+=
name|bytes
expr_stmt|;
operator|(
operator|*
name|end
operator|)
operator|++
expr_stmt|;
block|}
block|}
name|tile_release
argument_list|(
name|s_tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tile_release
argument_list|(
name|m_tile
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|find_contiguous_region_helper (GimpImage * gimage,PixelRegion * mask,PixelRegion * src,GimpImageType src_type,gboolean has_alpha,gboolean select_transparent,gboolean antialias,gint threshold,gint x,gint y,guchar * col)
name|find_contiguous_region_helper
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|GimpImageType
name|src_type
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gint
name|threshold
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guchar
modifier|*
name|col
parameter_list|)
block|{
name|gint
name|start
decl_stmt|,
name|end
decl_stmt|;
name|gint
name|new_start
decl_stmt|,
name|new_end
decl_stmt|;
name|gint
name|val
decl_stmt|;
name|Tile
modifier|*
name|tile
decl_stmt|;
name|GQueue
modifier|*
name|coord_stack
decl_stmt|;
name|coord_stack
operator|=
name|g_queue_new
argument_list|()
expr_stmt|;
comment|/* To avoid excessive memory allocation (y, start, end) tuples are    * stored in interleaved format:    *    * [y1] [start1] [end1] [y2] [start2] [end2]    */
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|y
argument_list|)
argument_list|)
expr_stmt|;
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|x
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|x
operator|+
literal|1
argument_list|)
argument_list|)
expr_stmt|;
do|do
block|{
name|y
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_queue_pop_head
argument_list|(
name|coord_stack
argument_list|)
argument_list|)
expr_stmt|;
name|start
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_queue_pop_head
argument_list|(
name|coord_stack
argument_list|)
argument_list|)
expr_stmt|;
name|end
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_queue_pop_head
argument_list|(
name|coord_stack
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
name|start
operator|+
literal|1
init|;
name|x
operator|<
name|end
condition|;
name|x
operator|++
control|)
block|{
name|tile
operator|=
name|tile_manager_get_tile
argument_list|(
name|mask
operator|->
name|tiles
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|val
operator|=
operator|*
operator|(
name|guchar
operator|*
operator|)
operator|(
name|tile_data_pointer
argument_list|(
name|tile
argument_list|,
name|x
operator|%
name|TILE_WIDTH
argument_list|,
name|y
operator|%
name|TILE_HEIGHT
argument_list|)
operator|)
expr_stmt|;
name|tile_release
argument_list|(
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|val
operator|!=
literal|0
condition|)
continue|continue;
name|src
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|src
operator|->
name|y
operator|=
name|y
expr_stmt|;
if|if
condition|(
operator|!
name|find_contiguous_segment
argument_list|(
name|gimage
argument_list|,
name|col
argument_list|,
name|src
argument_list|,
name|mask
argument_list|,
name|src
operator|->
name|w
argument_list|,
name|src
operator|->
name|bytes
argument_list|,
name|src_type
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|x
argument_list|,
operator|&
name|new_start
argument_list|,
operator|&
name|new_end
argument_list|)
condition|)
continue|continue;
if|if
condition|(
name|y
operator|+
literal|1
operator|<
name|src
operator|->
name|h
condition|)
block|{
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|y
operator|+
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|new_start
argument_list|)
argument_list|)
expr_stmt|;
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|new_end
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|y
operator|-
literal|1
operator|>=
literal|0
condition|)
block|{
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|y
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|new_start
argument_list|)
argument_list|)
expr_stmt|;
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|new_end
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
do|while
condition|(
operator|!
name|g_queue_is_empty
argument_list|(
name|coord_stack
argument_list|)
condition|)
do|;
name|g_queue_free
argument_list|(
name|coord_stack
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

