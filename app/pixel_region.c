begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdarg.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"pixel_region.h"
end_include

begin_include
include|#
directive|include
file|"pixel_regionP.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager_pvt.h"
end_include

begin_include
include|#
directive|include
file|"tile.h"
end_include

begin_comment
comment|/* ick. */
end_comment

begin_comment
comment|/*********************/
end_comment

begin_comment
comment|/*  Local Variables  */
end_comment

begin_comment
comment|/*********************/
end_comment

begin_comment
comment|/*  Local Functions  */
end_comment

begin_function_decl
specifier|static
name|int
name|get_portion_width
parameter_list|(
name|PixelRegionIterator
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|get_portion_height
parameter_list|(
name|PixelRegionIterator
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|pixel_regions_configure
parameter_list|(
name|PixelRegionIterator
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|pixel_region_configure
parameter_list|(
name|PixelRegionHolder
modifier|*
parameter_list|,
name|PixelRegionIterator
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**************************/
end_comment

begin_comment
comment|/*  Function definitions  */
end_comment

begin_function
name|void
DECL|function|pixel_region_init (PixelRegion * PR,TileManager * tiles,int x,int y,int w,int h,int dirty)
name|pixel_region_init
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|,
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|,
name|int
name|dirty
parameter_list|)
block|{
name|PR
operator|->
name|tiles
operator|=
name|tiles
expr_stmt|;
name|PR
operator|->
name|curtile
operator|=
name|NULL
expr_stmt|;
name|PR
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
name|PR
operator|->
name|bytes
operator|=
name|tiles
operator|->
name|bpp
expr_stmt|;
name|PR
operator|->
name|rowstride
operator|=
name|PR
operator|->
name|bytes
operator|*
name|TILE_WIDTH
expr_stmt|;
name|PR
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|PR
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|PR
operator|->
name|w
operator|=
name|w
expr_stmt|;
name|PR
operator|->
name|h
operator|=
name|h
expr_stmt|;
name|PR
operator|->
name|dirty
operator|=
name|dirty
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|pixel_region_resize (PixelRegion * PR,int x,int y,int w,int h)
name|pixel_region_resize
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|)
block|{
comment|/*  If the data is non-null, data is contiguous--need to advance  */
if|if
condition|(
name|PR
operator|->
name|data
operator|!=
name|NULL
condition|)
block|{
name|PR
operator|->
name|data
operator|+=
operator|(
name|y
operator|-
name|PR
operator|->
name|y
operator|)
operator|*
name|PR
operator|->
name|rowstride
operator|+
operator|(
name|x
operator|-
name|PR
operator|->
name|x
operator|)
operator|*
name|PR
operator|->
name|bytes
expr_stmt|;
block|}
comment|/*  update sizes for both contiguous and tiled regions  */
name|PR
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|PR
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|PR
operator|->
name|w
operator|=
name|w
expr_stmt|;
name|PR
operator|->
name|h
operator|=
name|h
expr_stmt|;
block|}
end_function

begin_comment
comment|/* request that tiles within a region be fetched asynchronously */
end_comment

begin_function
name|void
DECL|function|pixel_region_get_async (PixelRegion * PR,int ulx,int uly,int lrx,int lry)
name|pixel_region_get_async
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|,
name|int
name|ulx
parameter_list|,
name|int
name|uly
parameter_list|,
name|int
name|lrx
parameter_list|,
name|int
name|lry
parameter_list|)
block|{
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
name|uly
init|;
name|y
operator|<
name|lry
condition|;
name|y
operator|+=
name|TILE_HEIGHT
control|)
for|for
control|(
name|x
operator|=
name|ulx
init|;
name|x
operator|<
name|lrx
condition|;
name|x
operator|+=
name|TILE_WIDTH
control|)
name|tile_manager_get_async
argument_list|(
name|PR
operator|->
name|tiles
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|pixel_region_get_row (PixelRegion * PR,int x,int y,int w,unsigned char * data,int subsample)
name|pixel_region_get_row
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|unsigned
name|char
modifier|*
name|data
parameter_list|,
name|int
name|subsample
parameter_list|)
block|{
name|Tile
modifier|*
name|tile
decl_stmt|;
name|unsigned
name|char
modifier|*
name|tile_data
decl_stmt|;
name|int
name|inc
decl_stmt|;
name|int
name|end
decl_stmt|;
name|int
name|boundary
decl_stmt|;
name|int
name|b
decl_stmt|;
name|int
name|npixels
decl_stmt|;
name|end
operator|=
name|x
operator|+
name|w
expr_stmt|;
name|pixel_region_get_async
argument_list|(
name|PR
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|end
argument_list|,
name|y
argument_list|)
expr_stmt|;
while|while
condition|(
name|x
operator|<
name|end
condition|)
block|{
name|tile
operator|=
name|tile_manager_get_tile
argument_list|(
name|PR
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
name|tile_data
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
name|npixels
operator|=
name|tile_ewidth
argument_list|(
name|tile
argument_list|)
operator|-
operator|(
name|x
operator|%
name|TILE_WIDTH
operator|)
expr_stmt|;
if|if
condition|(
operator|(
name|x
operator|+
name|npixels
operator|)
operator|>
name|end
condition|)
comment|/* make sure we don't write past the end */
name|npixels
operator|=
name|end
operator|-
name|x
expr_stmt|;
if|if
condition|(
name|subsample
operator|==
literal|1
condition|)
comment|/* optimize for the common case */
block|{
name|memcpy
argument_list|(
name|data
argument_list|,
name|tile_data
argument_list|,
name|tile_bpp
argument_list|(
name|tile
argument_list|)
operator|*
name|npixels
argument_list|)
expr_stmt|;
name|data
operator|+=
name|tile_bpp
argument_list|(
name|tile
argument_list|)
operator|*
name|npixels
expr_stmt|;
name|x
operator|+=
name|npixels
expr_stmt|;
block|}
else|else
block|{
name|boundary
operator|=
name|x
operator|+
name|npixels
expr_stmt|;
name|inc
operator|=
name|subsample
operator|*
name|tile_bpp
argument_list|(
name|tile
argument_list|)
expr_stmt|;
for|for
control|(
init|;
name|x
operator|<
name|boundary
condition|;
name|x
operator|+=
name|subsample
control|)
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|tile_bpp
argument_list|(
name|tile
argument_list|)
condition|;
name|b
operator|++
control|)
operator|*
name|data
operator|++
operator|=
name|tile_data
index|[
name|b
index|]
expr_stmt|;
name|tile_data
operator|+=
name|inc
expr_stmt|;
block|}
block|}
name|tile_release
argument_list|(
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|pixel_region_set_row (PixelRegion * PR,int x,int y,int w,unsigned char * data)
name|pixel_region_set_row
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|unsigned
name|char
modifier|*
name|data
parameter_list|)
block|{
name|Tile
modifier|*
name|tile
decl_stmt|;
name|unsigned
name|char
modifier|*
name|tile_data
decl_stmt|;
name|int
name|end
decl_stmt|;
name|int
name|npixels
decl_stmt|;
name|end
operator|=
name|x
operator|+
name|w
expr_stmt|;
name|pixel_region_get_async
argument_list|(
name|PR
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|end
argument_list|,
name|y
argument_list|)
expr_stmt|;
while|while
condition|(
name|x
operator|<
name|end
condition|)
block|{
name|tile
operator|=
name|tile_manager_get_tile
argument_list|(
name|PR
operator|->
name|tiles
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
name|tile_data
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
name|npixels
operator|=
name|tile_ewidth
argument_list|(
name|tile
argument_list|)
operator|-
operator|(
name|x
operator|%
name|TILE_WIDTH
operator|)
expr_stmt|;
if|if
condition|(
operator|(
name|x
operator|+
name|npixels
operator|)
operator|>
name|end
condition|)
comment|/* make sure we don't write past the end */
name|npixels
operator|=
name|end
operator|-
name|x
expr_stmt|;
name|memcpy
argument_list|(
name|tile_data
argument_list|,
name|data
argument_list|,
name|tile_bpp
argument_list|(
name|tile
argument_list|)
operator|*
name|npixels
argument_list|)
expr_stmt|;
name|data
operator|+=
name|tile_bpp
argument_list|(
name|tile
argument_list|)
operator|*
name|npixels
expr_stmt|;
name|x
operator|+=
name|npixels
expr_stmt|;
name|tile_release
argument_list|(
name|tile
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|pixel_region_get_col (PixelRegion * PR,int x,int y,int h,unsigned char * data,int subsample)
name|pixel_region_get_col
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|h
parameter_list|,
name|unsigned
name|char
modifier|*
name|data
parameter_list|,
name|int
name|subsample
parameter_list|)
block|{
name|Tile
modifier|*
name|tile
decl_stmt|;
name|unsigned
name|char
modifier|*
name|tile_data
decl_stmt|;
name|int
name|inc
decl_stmt|;
name|int
name|end
decl_stmt|;
name|int
name|boundary
decl_stmt|;
name|int
name|b
decl_stmt|;
name|end
operator|=
name|y
operator|+
name|h
expr_stmt|;
name|pixel_region_get_async
argument_list|(
name|PR
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|x
argument_list|,
name|end
argument_list|)
expr_stmt|;
while|while
condition|(
name|y
operator|<
name|end
condition|)
block|{
name|tile
operator|=
name|tile_manager_get_tile
argument_list|(
name|PR
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
name|tile_data
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
name|boundary
operator|=
name|y
operator|+
operator|(
name|tile_eheight
argument_list|(
name|tile
argument_list|)
operator|-
operator|(
name|y
operator|%
name|TILE_HEIGHT
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|boundary
operator|>
name|end
condition|)
comment|/* make sure we don't write past the end */
name|boundary
operator|=
name|end
expr_stmt|;
name|inc
operator|=
name|subsample
operator|*
name|tile_bpp
argument_list|(
name|tile
argument_list|)
operator|*
name|tile_ewidth
argument_list|(
name|tile
argument_list|)
expr_stmt|;
for|for
control|(
init|;
name|y
operator|<
name|boundary
condition|;
name|y
operator|+=
name|subsample
control|)
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|tile_bpp
argument_list|(
name|tile
argument_list|)
condition|;
name|b
operator|++
control|)
operator|*
name|data
operator|++
operator|=
name|tile_data
index|[
name|b
index|]
expr_stmt|;
name|tile_data
operator|+=
name|inc
expr_stmt|;
block|}
name|tile_release
argument_list|(
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|pixel_region_set_col (PixelRegion * PR,int x,int y,int h,unsigned char * data)
name|pixel_region_set_col
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|h
parameter_list|,
name|unsigned
name|char
modifier|*
name|data
parameter_list|)
block|{
name|Tile
modifier|*
name|tile
decl_stmt|;
name|unsigned
name|char
modifier|*
name|tile_data
decl_stmt|;
name|int
name|inc
decl_stmt|;
name|int
name|end
decl_stmt|;
name|int
name|boundary
decl_stmt|;
name|int
name|b
decl_stmt|;
name|end
operator|=
name|y
operator|+
name|h
expr_stmt|;
name|pixel_region_get_async
argument_list|(
name|PR
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|x
argument_list|,
name|end
argument_list|)
expr_stmt|;
while|while
condition|(
name|y
operator|<
name|end
condition|)
block|{
name|tile
operator|=
name|tile_manager_get_tile
argument_list|(
name|PR
operator|->
name|tiles
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
name|tile_data
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
name|boundary
operator|=
name|y
operator|+
operator|(
name|tile_eheight
argument_list|(
name|tile
argument_list|)
operator|-
operator|(
name|y
operator|%
name|TILE_HEIGHT
operator|)
operator|)
expr_stmt|;
name|inc
operator|=
name|tile_bpp
argument_list|(
name|tile
argument_list|)
operator|*
name|tile_ewidth
argument_list|(
name|tile
argument_list|)
expr_stmt|;
if|if
condition|(
name|boundary
operator|>
name|end
condition|)
comment|/* make sure we don't write past the end */
name|boundary
operator|=
name|end
expr_stmt|;
for|for
control|(
init|;
name|y
operator|<
name|boundary
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|tile_bpp
argument_list|(
name|tile
argument_list|)
condition|;
name|b
operator|++
control|)
name|tile_data
index|[
name|b
index|]
operator|=
operator|*
name|data
operator|++
expr_stmt|;
name|tile_data
operator|+=
name|inc
expr_stmt|;
block|}
name|tile_release
argument_list|(
name|tile
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|int
DECL|function|pixel_region_has_alpha (PixelRegion * PR)
name|pixel_region_has_alpha
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|)
block|{
if|if
condition|(
name|PR
operator|->
name|bytes
operator|==
literal|2
operator|||
name|PR
operator|->
name|bytes
operator|==
literal|4
condition|)
return|return
literal|1
return|;
return|return
literal|0
return|;
block|}
end_function

begin_function
name|void
modifier|*
DECL|function|pixel_regions_register (int num_regions,...)
name|pixel_regions_register
parameter_list|(
name|int
name|num_regions
parameter_list|,
modifier|...
parameter_list|)
block|{
name|PixelRegion
modifier|*
name|PR
decl_stmt|;
name|PixelRegionHolder
modifier|*
name|PRH
decl_stmt|;
name|PixelRegionIterator
modifier|*
name|PRI
decl_stmt|;
name|int
name|found
decl_stmt|;
name|va_list
name|ap
decl_stmt|;
name|PRI
operator|=
operator|(
name|PixelRegionIterator
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|PixelRegionIterator
argument_list|)
argument_list|)
expr_stmt|;
name|PRI
operator|->
name|pixel_regions
operator|=
name|NULL
expr_stmt|;
name|PRI
operator|->
name|process_count
operator|=
literal|0
expr_stmt|;
name|PRI
operator|->
name|dirty_tiles
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|num_regions
operator|<
literal|1
condition|)
return|return
name|FALSE
return|;
name|va_start
argument_list|(
name|ap
argument_list|,
name|num_regions
argument_list|)
expr_stmt|;
name|found
operator|=
name|FALSE
expr_stmt|;
while|while
condition|(
name|num_regions
operator|--
condition|)
block|{
name|PR
operator|=
name|va_arg
argument_list|(
name|ap
argument_list|,
name|PixelRegion
operator|*
argument_list|)
expr_stmt|;
name|PRH
operator|=
operator|(
name|PixelRegionHolder
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|PixelRegionHolder
argument_list|)
argument_list|)
expr_stmt|;
name|PRH
operator|->
name|PR
operator|=
name|PR
expr_stmt|;
if|if
condition|(
name|PR
operator|!=
name|NULL
condition|)
block|{
comment|/*  If there is a defined value for data, make sure tiles is NULL  */
if|if
condition|(
name|PR
operator|->
name|data
condition|)
name|PR
operator|->
name|tiles
operator|=
name|NULL
expr_stmt|;
name|PRH
operator|->
name|original_data
operator|=
name|PR
operator|->
name|data
expr_stmt|;
name|PRH
operator|->
name|startx
operator|=
name|PR
operator|->
name|x
expr_stmt|;
name|PRH
operator|->
name|starty
operator|=
name|PR
operator|->
name|y
expr_stmt|;
name|PRH
operator|->
name|PR
operator|->
name|process_count
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|found
condition|)
block|{
name|found
operator|=
name|TRUE
expr_stmt|;
name|PRI
operator|->
name|region_width
operator|=
name|PR
operator|->
name|w
expr_stmt|;
name|PRI
operator|->
name|region_height
operator|=
name|PR
operator|->
name|h
expr_stmt|;
block|}
block|}
comment|/*  Add the pixel region holder to the list  */
name|PRI
operator|->
name|pixel_regions
operator|=
name|g_slist_prepend
argument_list|(
name|PRI
operator|->
name|pixel_regions
argument_list|,
name|PRH
argument_list|)
expr_stmt|;
block|}
name|va_end
argument_list|(
name|ap
argument_list|)
expr_stmt|;
return|return
name|pixel_regions_configure
argument_list|(
name|PRI
argument_list|)
return|;
block|}
end_function

begin_function
name|void
modifier|*
DECL|function|pixel_regions_process (void * PRI_ptr)
name|pixel_regions_process
parameter_list|(
name|void
modifier|*
name|PRI_ptr
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|PixelRegionHolder
modifier|*
name|PRH
decl_stmt|;
name|PixelRegionIterator
modifier|*
name|PRI
decl_stmt|;
name|PRI
operator|=
operator|(
name|PixelRegionIterator
operator|*
operator|)
name|PRI_ptr
expr_stmt|;
name|PRI
operator|->
name|process_count
operator|++
expr_stmt|;
comment|/*  Unref all referenced tiles and increment the offsets  */
name|list
operator|=
name|PRI
operator|->
name|pixel_regions
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|PRH
operator|=
operator|(
name|PixelRegionHolder
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|(
name|PRH
operator|->
name|PR
operator|!=
name|NULL
operator|)
operator|&&
operator|(
name|PRH
operator|->
name|PR
operator|->
name|process_count
operator|!=
name|PRI
operator|->
name|process_count
operator|)
condition|)
block|{
comment|/*  This eliminates the possibility of incrementing the 	   *  same region twice 	   */
name|PRH
operator|->
name|PR
operator|->
name|process_count
operator|++
expr_stmt|;
comment|/*  Unref the last referenced tile if the underlying region is a tile manager  */
if|if
condition|(
name|PRH
operator|->
name|PR
operator|->
name|tiles
condition|)
block|{
comment|/* only set the dirty flag if PRH->dirty_tiles = true */
name|tile_release
argument_list|(
name|PRH
operator|->
name|PR
operator|->
name|curtile
argument_list|,
name|PRH
operator|->
name|PR
operator|->
name|dirty
operator|&&
name|PRI
operator|->
name|dirty_tiles
argument_list|)
expr_stmt|;
name|PRH
operator|->
name|PR
operator|->
name|curtile
operator|=
name|NULL
expr_stmt|;
block|}
name|PRH
operator|->
name|PR
operator|->
name|x
operator|+=
name|PRI
operator|->
name|portion_width
expr_stmt|;
if|if
condition|(
operator|(
name|PRH
operator|->
name|PR
operator|->
name|x
operator|-
name|PRH
operator|->
name|startx
operator|)
operator|>=
name|PRI
operator|->
name|region_width
condition|)
block|{
name|PRH
operator|->
name|PR
operator|->
name|x
operator|=
name|PRH
operator|->
name|startx
expr_stmt|;
name|PRH
operator|->
name|PR
operator|->
name|y
operator|+=
name|PRI
operator|->
name|portion_height
expr_stmt|;
block|}
block|}
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
return|return
name|pixel_regions_configure
argument_list|(
name|PRI
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|pixel_regions_process_stop (void * PRI_ptr)
name|pixel_regions_process_stop
parameter_list|(
name|void
modifier|*
name|PRI_ptr
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|PixelRegionHolder
modifier|*
name|PRH
decl_stmt|;
name|PixelRegionIterator
modifier|*
name|PRI
decl_stmt|;
name|PRI
operator|=
operator|(
name|PixelRegionIterator
operator|*
operator|)
name|PRI_ptr
expr_stmt|;
name|PRI
operator|->
name|process_count
operator|++
expr_stmt|;
comment|/*  Unref all referenced tiles and increment the offsets  */
name|list
operator|=
name|PRI
operator|->
name|pixel_regions
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|PRH
operator|=
operator|(
name|PixelRegionHolder
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|(
name|PRH
operator|->
name|PR
operator|!=
name|NULL
operator|)
operator|&&
operator|(
name|PRH
operator|->
name|PR
operator|->
name|process_count
operator|!=
name|PRI
operator|->
name|process_count
operator|)
condition|)
block|{
comment|/*  This eliminates the possibility of incrementing the 	   *  same region twice 	   */
name|PRH
operator|->
name|PR
operator|->
name|process_count
operator|++
expr_stmt|;
comment|/*  Unref the last referenced tile if the underlying region is a tile manager  */
if|if
condition|(
name|PRH
operator|->
name|PR
operator|->
name|tiles
condition|)
block|{
name|tile_release
argument_list|(
name|PRH
operator|->
name|PR
operator|->
name|curtile
argument_list|,
name|PRH
operator|->
name|PR
operator|->
name|dirty
argument_list|)
expr_stmt|;
name|PRH
operator|->
name|PR
operator|->
name|curtile
operator|=
name|NULL
expr_stmt|;
block|}
block|}
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|PRI
operator|->
name|pixel_regions
condition|)
block|{
name|list
operator|=
name|PRI
operator|->
name|pixel_regions
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|g_free
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|PRI
operator|->
name|pixel_regions
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|PRI
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*********************************/
end_comment

begin_comment
comment|/*  Static Function Definitions  */
end_comment

begin_function
specifier|static
name|int
DECL|function|get_portion_height (PixelRegionIterator * PRI)
name|get_portion_height
parameter_list|(
name|PixelRegionIterator
modifier|*
name|PRI
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|PixelRegionHolder
modifier|*
name|PRH
decl_stmt|;
name|int
name|min_height
init|=
name|G_MAXINT
decl_stmt|;
name|int
name|height
decl_stmt|;
comment|/*  Find the minimum height to the next vertical tile (in the case of a tile manager)    *  or to the end of the pixel region (in the case of no tile manager)    */
name|list
operator|=
name|PRI
operator|->
name|pixel_regions
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|PRH
operator|=
operator|(
name|PixelRegionHolder
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|PRH
operator|->
name|PR
condition|)
block|{
comment|/*  Check if we're past the point of no return  */
if|if
condition|(
operator|(
name|PRH
operator|->
name|PR
operator|->
name|y
operator|-
name|PRH
operator|->
name|starty
operator|)
operator|>=
name|PRI
operator|->
name|region_height
condition|)
return|return
literal|0
return|;
if|if
condition|(
name|PRH
operator|->
name|PR
operator|->
name|tiles
condition|)
block|{
name|height
operator|=
name|TILE_HEIGHT
operator|-
operator|(
name|PRH
operator|->
name|PR
operator|->
name|y
operator|%
name|TILE_HEIGHT
operator|)
expr_stmt|;
name|height
operator|=
name|BOUNDS
argument_list|(
name|height
argument_list|,
literal|0
argument_list|,
operator|(
name|PRI
operator|->
name|region_height
operator|-
operator|(
name|PRH
operator|->
name|PR
operator|->
name|y
operator|-
name|PRH
operator|->
name|starty
operator|)
operator|)
argument_list|)
expr_stmt|;
block|}
else|else
name|height
operator|=
operator|(
name|PRI
operator|->
name|region_height
operator|-
operator|(
name|PRH
operator|->
name|PR
operator|->
name|y
operator|-
name|PRH
operator|->
name|starty
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|height
operator|<
name|min_height
condition|)
name|min_height
operator|=
name|height
expr_stmt|;
block|}
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
return|return
name|min_height
return|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|get_portion_width (PixelRegionIterator * PRI)
name|get_portion_width
parameter_list|(
name|PixelRegionIterator
modifier|*
name|PRI
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|PixelRegionHolder
modifier|*
name|PRH
decl_stmt|;
name|int
name|min_width
init|=
name|G_MAXINT
decl_stmt|;
name|int
name|width
decl_stmt|;
comment|/*  Find the minimum width to the next vertical tile (in the case of a tile manager)    *  or to the end of the pixel region (in the case of no tile manager)    */
name|list
operator|=
name|PRI
operator|->
name|pixel_regions
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|PRH
operator|=
operator|(
name|PixelRegionHolder
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|PRH
operator|->
name|PR
condition|)
block|{
comment|/*  Check if we're past the point of no return  */
if|if
condition|(
operator|(
name|PRH
operator|->
name|PR
operator|->
name|x
operator|-
name|PRH
operator|->
name|startx
operator|)
operator|>=
name|PRI
operator|->
name|region_width
condition|)
return|return
literal|0
return|;
if|if
condition|(
name|PRH
operator|->
name|PR
operator|->
name|tiles
condition|)
block|{
name|width
operator|=
name|TILE_WIDTH
operator|-
operator|(
name|PRH
operator|->
name|PR
operator|->
name|x
operator|%
name|TILE_WIDTH
operator|)
expr_stmt|;
name|width
operator|=
name|BOUNDS
argument_list|(
name|width
argument_list|,
literal|0
argument_list|,
operator|(
name|PRI
operator|->
name|region_width
operator|-
operator|(
name|PRH
operator|->
name|PR
operator|->
name|x
operator|-
name|PRH
operator|->
name|startx
operator|)
operator|)
argument_list|)
expr_stmt|;
block|}
else|else
name|width
operator|=
operator|(
name|PRI
operator|->
name|region_width
operator|-
operator|(
name|PRH
operator|->
name|PR
operator|->
name|x
operator|-
name|PRH
operator|->
name|startx
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|width
operator|<
name|min_width
condition|)
name|min_width
operator|=
name|width
expr_stmt|;
block|}
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
return|return
name|min_width
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|pixel_regions_configure (PixelRegionIterator * PRI)
name|pixel_regions_configure
parameter_list|(
name|PixelRegionIterator
modifier|*
name|PRI
parameter_list|)
block|{
name|PixelRegionHolder
modifier|*
name|PRH
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
comment|/*  Determine the portion width and height  */
name|PRI
operator|->
name|portion_width
operator|=
name|get_portion_width
argument_list|(
name|PRI
argument_list|)
expr_stmt|;
name|PRI
operator|->
name|portion_height
operator|=
name|get_portion_height
argument_list|(
name|PRI
argument_list|)
expr_stmt|;
if|if
condition|(
name|PRI
operator|->
name|portion_width
operator|==
literal|0
operator|||
name|PRI
operator|->
name|portion_height
operator|==
literal|0
condition|)
block|{
comment|/*  free the pixel regions list  */
if|if
condition|(
name|PRI
operator|->
name|pixel_regions
condition|)
block|{
name|list
operator|=
name|PRI
operator|->
name|pixel_regions
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|g_free
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|PRI
operator|->
name|pixel_regions
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|PRI
argument_list|)
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
name|PRI
operator|->
name|process_count
operator|++
expr_stmt|;
name|list
operator|=
name|PRI
operator|->
name|pixel_regions
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|PRH
operator|=
operator|(
name|PixelRegionHolder
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|(
name|PRH
operator|->
name|PR
operator|!=
name|NULL
operator|)
operator|&&
operator|(
name|PRH
operator|->
name|PR
operator|->
name|process_count
operator|!=
name|PRI
operator|->
name|process_count
operator|)
condition|)
block|{
name|PRH
operator|->
name|PR
operator|->
name|process_count
operator|++
expr_stmt|;
name|pixel_region_configure
argument_list|(
name|PRH
argument_list|,
name|PRI
argument_list|)
expr_stmt|;
block|}
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
return|return
name|PRI
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pixel_region_configure (PixelRegionHolder * PRH,PixelRegionIterator * PRI)
name|pixel_region_configure
parameter_list|(
name|PixelRegionHolder
modifier|*
name|PRH
parameter_list|,
name|PixelRegionIterator
modifier|*
name|PRI
parameter_list|)
block|{
comment|/*  Configure the rowstride and data pointer for the pixel region    *  based on the current offsets into the region and whether the    *  region is represented by a tile manager or not    */
if|if
condition|(
name|PRH
operator|->
name|PR
operator|->
name|tiles
condition|)
block|{
name|PRH
operator|->
name|PR
operator|->
name|curtile
operator|=
name|tile_manager_get_tile
argument_list|(
name|PRH
operator|->
name|PR
operator|->
name|tiles
argument_list|,
name|PRH
operator|->
name|PR
operator|->
name|x
argument_list|,
name|PRH
operator|->
name|PR
operator|->
name|y
argument_list|,
name|TRUE
argument_list|,
name|PRH
operator|->
name|PR
operator|->
name|dirty
argument_list|)
expr_stmt|;
name|PRH
operator|->
name|PR
operator|->
name|offx
operator|=
name|PRH
operator|->
name|PR
operator|->
name|x
operator|%
name|TILE_WIDTH
expr_stmt|;
name|PRH
operator|->
name|PR
operator|->
name|offy
operator|=
name|PRH
operator|->
name|PR
operator|->
name|y
operator|%
name|TILE_HEIGHT
expr_stmt|;
name|PRH
operator|->
name|PR
operator|->
name|rowstride
operator|=
name|tile_ewidth
argument_list|(
name|PRH
operator|->
name|PR
operator|->
name|curtile
argument_list|)
operator|*
name|PRH
operator|->
name|PR
operator|->
name|bytes
expr_stmt|;
name|PRH
operator|->
name|PR
operator|->
name|data
operator|=
name|tile_data_pointer
argument_list|(
name|PRH
operator|->
name|PR
operator|->
name|curtile
argument_list|,
name|PRH
operator|->
name|PR
operator|->
name|offx
argument_list|,
name|PRH
operator|->
name|PR
operator|->
name|offy
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|PRH
operator|->
name|PR
operator|->
name|data
operator|=
name|PRH
operator|->
name|original_data
operator|+
operator|(
name|PRH
operator|->
name|PR
operator|->
name|y
operator|-
name|PRH
operator|->
name|starty
operator|)
operator|*
name|PRH
operator|->
name|PR
operator|->
name|rowstride
operator|+
operator|(
name|PRH
operator|->
name|PR
operator|->
name|x
operator|-
name|PRH
operator|->
name|startx
operator|)
operator|*
name|PRH
operator|->
name|PR
operator|->
name|bytes
expr_stmt|;
block|}
name|PRH
operator|->
name|PR
operator|->
name|w
operator|=
name|PRI
operator|->
name|portion_width
expr_stmt|;
name|PRH
operator|->
name|PR
operator|->
name|h
operator|=
name|PRI
operator|->
name|portion_height
expr_stmt|;
block|}
end_function

end_unit

