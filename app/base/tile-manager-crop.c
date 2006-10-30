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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"base-types.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"tile-manager-crop.h"
end_include

begin_comment
comment|/*  Crop the buffer to the size of pixels with non-zero transparency */
end_comment

begin_function
name|TileManager
modifier|*
DECL|function|tile_manager_crop (TileManager * tiles,gint border)
name|tile_manager_crop
parameter_list|(
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|gint
name|border
parameter_list|)
block|{
name|PixelRegion
name|PR
decl_stmt|;
name|TileManager
modifier|*
name|new_tiles
decl_stmt|;
name|gint
name|bytes
decl_stmt|,
name|alpha
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|gint
name|empty
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|ex
decl_stmt|,
name|ey
decl_stmt|;
name|gint
name|found
decl_stmt|;
name|void
modifier|*
name|pr
decl_stmt|;
name|guchar
name|black
index|[
name|MAX_CHANNELS
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tiles
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|bytes
operator|=
name|tile_manager_bpp
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
name|alpha
operator|=
name|bytes
operator|-
literal|1
expr_stmt|;
comment|/*  go through and calculate the bounds  */
name|x1
operator|=
name|tile_manager_width
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
name|y1
operator|=
name|tile_manager_height
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
name|x2
operator|=
literal|0
expr_stmt|;
name|y2
operator|=
literal|0
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|PR
argument_list|,
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|1
argument_list|,
operator|&
name|PR
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|pixel_regions_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|data
operator|=
name|PR
operator|.
name|data
operator|+
name|alpha
expr_stmt|;
name|ex
operator|=
name|PR
operator|.
name|x
operator|+
name|PR
operator|.
name|w
expr_stmt|;
name|ey
operator|=
name|PR
operator|.
name|y
operator|+
name|PR
operator|.
name|h
expr_stmt|;
for|for
control|(
name|y
operator|=
name|PR
operator|.
name|y
init|;
name|y
operator|<
name|ey
condition|;
name|y
operator|++
control|)
block|{
name|found
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|x
operator|=
name|PR
operator|.
name|x
init|;
name|x
operator|<
name|ex
condition|;
name|x
operator|++
operator|,
name|data
operator|+=
name|bytes
control|)
if|if
condition|(
operator|*
name|data
condition|)
block|{
if|if
condition|(
name|x
operator|<
name|x1
condition|)
name|x1
operator|=
name|x
expr_stmt|;
if|if
condition|(
name|x
operator|>
name|x2
condition|)
name|x2
operator|=
name|x
expr_stmt|;
name|found
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
name|found
condition|)
block|{
if|if
condition|(
name|y
operator|<
name|y1
condition|)
name|y1
operator|=
name|y
expr_stmt|;
if|if
condition|(
name|y
operator|>
name|y2
condition|)
name|y2
operator|=
name|y
expr_stmt|;
block|}
block|}
block|}
name|x2
operator|=
name|CLAMP
argument_list|(
name|x2
operator|+
literal|1
argument_list|,
literal|0
argument_list|,
name|tile_manager_width
argument_list|(
name|tiles
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|y2
operator|+
literal|1
argument_list|,
literal|0
argument_list|,
name|tile_manager_height
argument_list|(
name|tiles
argument_list|)
argument_list|)
expr_stmt|;
name|empty
operator|=
operator|(
name|x1
operator|==
name|tile_manager_width
argument_list|(
name|tiles
argument_list|)
operator|&&
name|y1
operator|==
name|tile_manager_height
argument_list|(
name|tiles
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|empty
condition|)
block|{
comment|/*  If there are no visible pixels, return NULL */
name|new_tiles
operator|=
name|NULL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|x1
operator|==
literal|0
operator|&&
name|y1
operator|==
literal|0
operator|&&
name|x2
operator|==
name|tile_manager_width
argument_list|(
name|tiles
argument_list|)
operator|&&
name|y2
operator|==
name|tile_manager_height
argument_list|(
name|tiles
argument_list|)
operator|&&
name|border
operator|==
literal|0
condition|)
block|{
comment|/*  If no cropping, return original buffer  */
name|new_tiles
operator|=
name|tiles
expr_stmt|;
block|}
else|else
block|{
comment|/*  Otherwise, crop the original area  */
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|gint
name|new_width
decl_stmt|,
name|new_height
decl_stmt|;
name|new_width
operator|=
operator|(
name|x2
operator|-
name|x1
operator|)
operator|+
name|border
operator|*
literal|2
expr_stmt|;
name|new_height
operator|=
operator|(
name|y2
operator|-
name|y1
operator|)
operator|+
name|border
operator|*
literal|2
expr_stmt|;
name|new_tiles
operator|=
name|tile_manager_new
argument_list|(
name|new_width
argument_list|,
name|new_height
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
comment|/*  If there is a border, make sure to clear the new tiles first  */
if|if
condition|(
name|border
condition|)
block|{
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|new_tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|new_width
argument_list|,
name|border
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|destPR
argument_list|,
name|black
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|new_tiles
argument_list|,
literal|0
argument_list|,
name|border
argument_list|,
name|border
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|destPR
argument_list|,
name|black
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|new_tiles
argument_list|,
name|new_width
operator|-
name|border
argument_list|,
name|border
argument_list|,
name|border
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|destPR
argument_list|,
name|black
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|new_tiles
argument_list|,
literal|0
argument_list|,
name|new_height
operator|-
name|border
argument_list|,
name|new_width
argument_list|,
name|border
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|destPR
argument_list|,
name|black
argument_list|)
expr_stmt|;
block|}
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|tiles
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|new_tiles
argument_list|,
name|border
argument_list|,
name|border
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|tile_manager_set_offsets
argument_list|(
name|new_tiles
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
block|}
return|return
name|new_tiles
return|;
block|}
end_function

end_unit

