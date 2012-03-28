begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|gint
name|pixel_difference
parameter_list|(
specifier|const
name|guchar
modifier|*
name|col1
parameter_list|,
specifier|const
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
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
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
name|gboolean
name|find_contiguous_segment
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
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
specifier|const
name|Babl
modifier|*
name|fish
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
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
name|image
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
specifier|const
name|Babl
modifier|*
name|fish
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
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
specifier|const
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
DECL|function|gimp_image_contiguous_region_by_seed (GimpImage * image,GimpDrawable * drawable,gboolean sample_merged,gboolean antialias,gint threshold,gboolean select_transparent,GimpSelectCriterion select_criterion,gint x,gint y)
name|gimp_image_contiguous_region_by_seed
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|GimpSelectCriterion
name|select_criterion
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
specifier|const
name|Babl
modifier|*
name|src_format
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|fish
init|=
name|NULL
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
name|image
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
name|gimp_image_get_projection
argument_list|(
name|image
argument_list|)
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
name|gimp_pickable_flush
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|src_format
operator|=
name|gimp_pickable_get_format
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|babl_format_has_alpha
argument_list|(
name|src_format
argument_list|)
expr_stmt|;
name|bytes
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|src_format
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
name|image
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
name|gimp_drawable_get_tiles
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
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
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
specifier|const
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
argument_list|,
name|y
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
name|babl_format_is_palette
argument_list|(
name|src_format
argument_list|)
condition|)
block|{
name|fish
operator|=
name|babl_fish
argument_list|(
name|src_format
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
argument_list|)
expr_stmt|;
name|babl_process
argument_list|(
name|fish
argument_list|,
name|start
argument_list|,
name|start_col
argument_list|,
literal|1
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
name|image
argument_list|,
operator|&
name|maskPR
argument_list|,
operator|&
name|srcPR
argument_list|,
name|fish
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|,
name|select_criterion
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
DECL|function|gimp_image_contiguous_region_by_color (GimpImage * image,GimpDrawable * drawable,gboolean sample_merged,gboolean antialias,gint threshold,gboolean select_transparent,GimpSelectCriterion select_criterion,const GimpRGB * color)
name|gimp_image_contiguous_region_by_color
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|GimpSelectCriterion
name|select_criterion
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
comment|/*  Scan over the image's active layer, finding pixels within the    *  specified threshold from the given R, G,& B values.  If    *  antialiasing is on, use the same antialiasing scheme as in    *  fuzzy_select.  Modify the image's mask to reflect the    *  additional selection    */
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|GimpPickable
modifier|*
name|pickable
decl_stmt|;
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
name|GeglBuffer
modifier|*
name|src_buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|mask_buffer
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|guchar
name|col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
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
operator|&
name|col
index|[
literal|0
index|]
argument_list|,
operator|&
name|col
index|[
literal|1
index|]
argument_list|,
operator|&
name|col
index|[
literal|2
index|]
argument_list|,
operator|&
name|col
index|[
literal|3
index|]
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
name|gimp_image_get_projection
argument_list|(
name|image
argument_list|)
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
name|gimp_pickable_flush
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|babl_format_has_alpha
argument_list|(
name|gimp_pickable_get_format
argument_list|(
name|pickable
argument_list|)
argument_list|)
expr_stmt|;
name|src_buffer
operator|=
name|gimp_pickable_get_buffer
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|width
operator|=
name|gegl_buffer_get_width
argument_list|(
name|src_buffer
argument_list|)
expr_stmt|;
name|height
operator|=
name|gegl_buffer_get_height
argument_list|(
name|src_buffer
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|src_buffer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_NONE
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
comment|/*  don't select transparancy if "color" isn't fully transparent            */
if|if
condition|(
name|col
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
name|mask
operator|=
name|gimp_channel_new_mask
argument_list|(
name|image
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|mask_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|mask_buffer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
argument_list|,
name|GEGL_BUFFER_WRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
specifier|const
name|guchar
modifier|*
name|src
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|guchar
modifier|*
name|dest
init|=
name|iter
operator|->
name|data
index|[
literal|1
index|]
decl_stmt|;
while|while
condition|(
name|iter
operator|->
name|length
operator|--
condition|)
block|{
comment|/*  Find how closely the colors match  */
operator|*
name|dest
operator|=
name|pixel_difference
argument_list|(
name|col
argument_list|,
name|src
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|has_alpha
condition|?
literal|4
else|:
literal|3
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|,
name|select_criterion
argument_list|)
expr_stmt|;
name|src
operator|+=
literal|4
expr_stmt|;
name|dest
operator|+=
literal|1
expr_stmt|;
block|}
block|}
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
name|gint
DECL|function|pixel_difference (const guchar * col1,const guchar * col2,gboolean antialias,gint threshold,gint bytes,gboolean has_alpha,gboolean select_transparent,GimpSelectCriterion select_criterion)
name|pixel_difference
parameter_list|(
specifier|const
name|guchar
modifier|*
name|col1
parameter_list|,
specifier|const
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
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
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
name|gint
name|av0
decl_stmt|,
name|av1
decl_stmt|,
name|av2
decl_stmt|;
name|gint
name|bv0
decl_stmt|,
name|bv1
decl_stmt|,
name|bv2
decl_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|bytes
operator|--
expr_stmt|;
switch|switch
condition|(
name|select_criterion
condition|)
block|{
case|case
name|GIMP_SELECT_CRITERION_COMPOSITE
case|:
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
break|break;
case|case
name|GIMP_SELECT_CRITERION_R
case|:
name|max
operator|=
name|abs
argument_list|(
name|col1
index|[
literal|0
index|]
operator|-
name|col2
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_SELECT_CRITERION_G
case|:
name|max
operator|=
name|abs
argument_list|(
name|col1
index|[
literal|1
index|]
operator|-
name|col2
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_SELECT_CRITERION_B
case|:
name|max
operator|=
name|abs
argument_list|(
name|col1
index|[
literal|2
index|]
operator|-
name|col2
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_SELECT_CRITERION_H
case|:
name|av0
operator|=
operator|(
name|gint
operator|)
name|col1
index|[
literal|0
index|]
expr_stmt|;
name|av1
operator|=
operator|(
name|gint
operator|)
name|col1
index|[
literal|1
index|]
expr_stmt|;
name|av2
operator|=
operator|(
name|gint
operator|)
name|col1
index|[
literal|2
index|]
expr_stmt|;
name|bv0
operator|=
operator|(
name|gint
operator|)
name|col2
index|[
literal|0
index|]
expr_stmt|;
name|bv1
operator|=
operator|(
name|gint
operator|)
name|col2
index|[
literal|1
index|]
expr_stmt|;
name|bv2
operator|=
operator|(
name|gint
operator|)
name|col2
index|[
literal|2
index|]
expr_stmt|;
name|gimp_rgb_to_hsv_int
argument_list|(
operator|&
name|av0
argument_list|,
operator|&
name|av1
argument_list|,
operator|&
name|av2
argument_list|)
expr_stmt|;
name|gimp_rgb_to_hsv_int
argument_list|(
operator|&
name|bv0
argument_list|,
operator|&
name|bv1
argument_list|,
operator|&
name|bv2
argument_list|)
expr_stmt|;
comment|/* wrap around candidates for the actual distance */
block|{
name|gint
name|dist1
init|=
name|abs
argument_list|(
name|av0
operator|-
name|bv0
argument_list|)
decl_stmt|;
name|gint
name|dist2
init|=
name|abs
argument_list|(
name|av0
operator|-
literal|360
operator|-
name|bv0
argument_list|)
decl_stmt|;
name|gint
name|dist3
init|=
name|abs
argument_list|(
name|av0
operator|-
name|bv0
operator|+
literal|360
argument_list|)
decl_stmt|;
name|max
operator|=
name|MIN
argument_list|(
name|dist1
argument_list|,
name|dist2
argument_list|)
expr_stmt|;
if|if
condition|(
name|max
operator|>
name|dist3
condition|)
name|max
operator|=
name|dist3
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_SELECT_CRITERION_S
case|:
name|av0
operator|=
operator|(
name|gint
operator|)
name|col1
index|[
literal|0
index|]
expr_stmt|;
name|av1
operator|=
operator|(
name|gint
operator|)
name|col1
index|[
literal|1
index|]
expr_stmt|;
name|av2
operator|=
operator|(
name|gint
operator|)
name|col1
index|[
literal|2
index|]
expr_stmt|;
name|bv0
operator|=
operator|(
name|gint
operator|)
name|col2
index|[
literal|0
index|]
expr_stmt|;
name|bv1
operator|=
operator|(
name|gint
operator|)
name|col2
index|[
literal|1
index|]
expr_stmt|;
name|bv2
operator|=
operator|(
name|gint
operator|)
name|col2
index|[
literal|2
index|]
expr_stmt|;
name|gimp_rgb_to_hsv_int
argument_list|(
operator|&
name|av0
argument_list|,
operator|&
name|av1
argument_list|,
operator|&
name|av2
argument_list|)
expr_stmt|;
name|gimp_rgb_to_hsv_int
argument_list|(
operator|&
name|bv0
argument_list|,
operator|&
name|bv1
argument_list|,
operator|&
name|bv2
argument_list|)
expr_stmt|;
name|max
operator|=
name|abs
argument_list|(
name|av1
operator|-
name|bv1
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_SELECT_CRITERION_V
case|:
name|av0
operator|=
operator|(
name|gint
operator|)
name|col1
index|[
literal|0
index|]
expr_stmt|;
name|av1
operator|=
operator|(
name|gint
operator|)
name|col1
index|[
literal|1
index|]
expr_stmt|;
name|av2
operator|=
operator|(
name|gint
operator|)
name|col1
index|[
literal|2
index|]
expr_stmt|;
name|bv0
operator|=
operator|(
name|gint
operator|)
name|col2
index|[
literal|0
index|]
expr_stmt|;
name|bv1
operator|=
operator|(
name|gint
operator|)
name|col2
index|[
literal|1
index|]
expr_stmt|;
name|bv2
operator|=
operator|(
name|gint
operator|)
name|col2
index|[
literal|2
index|]
expr_stmt|;
name|gimp_rgb_to_hsv_int
argument_list|(
operator|&
name|av0
argument_list|,
operator|&
name|av1
argument_list|,
operator|&
name|av2
argument_list|)
expr_stmt|;
name|gimp_rgb_to_hsv_int
argument_list|(
operator|&
name|bv0
argument_list|,
operator|&
name|bv1
argument_list|,
operator|&
name|bv2
argument_list|)
expr_stmt|;
name|max
operator|=
name|abs
argument_list|(
name|av2
operator|-
name|bv2
argument_list|)
expr_stmt|;
break|break;
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
argument_list|,
name|y
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
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|find_contiguous_segment (GimpImage * image,const guchar * col,PixelRegion * src,PixelRegion * mask,gint width,gint bytes,const Babl * fish,gboolean has_alpha,gboolean select_transparent,GimpSelectCriterion select_criterion,gboolean antialias,gint threshold,gint initial,gint * start,gint * end)
name|find_contiguous_segment
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
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
specifier|const
name|Babl
modifier|*
name|fish
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
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
name|fish
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
name|babl_process
argument_list|(
name|fish
argument_list|,
name|s
argument_list|,
name|s_color
argument_list|,
literal|1
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
argument_list|,
name|select_criterion
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
argument_list|,
name|select_criterion
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
name|fish
condition|)
block|{
name|babl_process
argument_list|(
name|fish
argument_list|,
name|s
argument_list|,
name|s_color
argument_list|,
literal|1
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
argument_list|,
name|select_criterion
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
argument_list|,
name|select_criterion
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
name|fish
condition|)
block|{
name|babl_process
argument_list|(
name|fish
argument_list|,
name|s
argument_list|,
name|s_color
argument_list|,
literal|1
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
argument_list|,
name|select_criterion
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
argument_list|,
name|select_criterion
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
DECL|function|find_contiguous_region_helper (GimpImage * image,PixelRegion * mask,PixelRegion * src,const Babl * fish,gboolean has_alpha,gboolean select_transparent,GimpSelectCriterion select_criterion,gboolean antialias,gint threshold,gint x,gint y,const guchar * col)
name|find_contiguous_region_helper
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
specifier|const
name|Babl
modifier|*
name|fish
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
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
specifier|const
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
specifier|const
name|guchar
operator|*
operator|)
name|tile_data_pointer
argument_list|(
name|tile
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
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
name|image
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
name|fish
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|,
name|select_criterion
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

