begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"pixel-surround.h"
end_include

begin_include
include|#
directive|include
file|"tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"tile.h"
end_include

begin_function
name|void
DECL|function|pixel_surround_init (PixelSurround * ps,TileManager * tm,gint w,gint h,guchar bg[MAX_CHANNELS])
name|pixel_surround_init
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|,
name|TileManager
modifier|*
name|tm
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|guchar
name|bg
index|[
name|MAX_CHANNELS
index|]
parameter_list|)
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
name|MAX_CHANNELS
condition|;
operator|++
name|i
control|)
block|{
name|ps
operator|->
name|bg
index|[
name|i
index|]
operator|=
name|bg
index|[
name|i
index|]
expr_stmt|;
block|}
name|ps
operator|->
name|tile
operator|=
name|NULL
expr_stmt|;
name|ps
operator|->
name|mgr
operator|=
name|tm
expr_stmt|;
name|ps
operator|->
name|bpp
operator|=
name|tile_manager_bpp
argument_list|(
name|tm
argument_list|)
expr_stmt|;
name|ps
operator|->
name|w
operator|=
name|w
expr_stmt|;
name|ps
operator|->
name|h
operator|=
name|h
expr_stmt|;
comment|/* make sure buffer is big enough */
name|ps
operator|->
name|buff_size
operator|=
name|w
operator|*
name|h
operator|*
name|ps
operator|->
name|bpp
expr_stmt|;
name|ps
operator|->
name|buff
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|ps
operator|->
name|buff_size
argument_list|)
expr_stmt|;
name|ps
operator|->
name|row_stride
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
name|guchar
modifier|*
DECL|function|pixel_surround_lock (PixelSurround * ps,gint x,gint y)
name|pixel_surround_lock
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|guchar
modifier|*
name|k
decl_stmt|;
name|guchar
modifier|*
name|ptr
decl_stmt|;
name|ps
operator|->
name|tile
operator|=
name|tile_manager_get_tile
argument_list|(
name|ps
operator|->
name|mgr
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
name|i
operator|=
name|x
operator|%
name|TILE_WIDTH
expr_stmt|;
name|j
operator|=
name|y
operator|%
name|TILE_HEIGHT
expr_stmt|;
comment|/* do we have the whole region? */
if|if
condition|(
name|ps
operator|->
name|tile
operator|&&
operator|(
name|i
operator|<
operator|(
name|tile_ewidth
argument_list|(
name|ps
operator|->
name|tile
argument_list|)
operator|-
name|ps
operator|->
name|w
operator|)
operator|)
operator|&&
operator|(
name|j
operator|<
operator|(
name|tile_eheight
argument_list|(
name|ps
operator|->
name|tile
argument_list|)
operator|-
name|ps
operator|->
name|h
operator|)
operator|)
condition|)
block|{
name|ps
operator|->
name|row_stride
operator|=
name|tile_ewidth
argument_list|(
name|ps
operator|->
name|tile
argument_list|)
operator|*
name|ps
operator|->
name|bpp
expr_stmt|;
comment|/* is this really the correct way? */
return|return
name|tile_data_pointer
argument_list|(
name|ps
operator|->
name|tile
argument_list|,
name|i
argument_list|,
name|j
argument_list|)
return|;
block|}
comment|/* nope, do this the hard way (for now) */
if|if
condition|(
name|ps
operator|->
name|tile
condition|)
block|{
name|tile_release
argument_list|(
name|ps
operator|->
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|ps
operator|->
name|tile
operator|=
literal|0
expr_stmt|;
block|}
comment|/* copy pixels, one by one */
comment|/* no, this is not the best way, but it's much better than before */
name|ptr
operator|=
name|ps
operator|->
name|buff
expr_stmt|;
for|for
control|(
name|j
operator|=
name|y
init|;
name|j
operator|<
name|y
operator|+
name|ps
operator|->
name|h
condition|;
operator|++
name|j
control|)
block|{
for|for
control|(
name|i
operator|=
name|x
init|;
name|i
operator|<
name|x
operator|+
name|ps
operator|->
name|w
condition|;
operator|++
name|i
control|)
block|{
name|Tile
modifier|*
name|tile
init|=
name|tile_manager_get_tile
argument_list|(
name|ps
operator|->
name|mgr
argument_list|,
name|i
argument_list|,
name|j
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
if|if
condition|(
name|tile
condition|)
block|{
name|guchar
modifier|*
name|buff
init|=
name|tile_data_pointer
argument_list|(
name|tile
argument_list|,
name|i
operator|%
name|TILE_WIDTH
argument_list|,
name|j
operator|%
name|TILE_HEIGHT
argument_list|)
decl_stmt|;
for|for
control|(
name|k
operator|=
name|buff
init|;
name|k
operator|<
name|buff
operator|+
name|ps
operator|->
name|bpp
condition|;
operator|++
name|k
operator|,
operator|++
name|ptr
control|)
block|{
operator|*
name|ptr
operator|=
operator|*
name|k
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
else|else
block|{
for|for
control|(
name|k
operator|=
name|ps
operator|->
name|bg
init|;
name|k
operator|<
name|ps
operator|->
name|bg
operator|+
name|ps
operator|->
name|bpp
condition|;
operator|++
name|k
operator|,
operator|++
name|ptr
control|)
block|{
operator|*
name|ptr
operator|=
operator|*
name|k
expr_stmt|;
block|}
block|}
block|}
block|}
name|ps
operator|->
name|row_stride
operator|=
name|ps
operator|->
name|w
operator|*
name|ps
operator|->
name|bpp
expr_stmt|;
return|return
name|ps
operator|->
name|buff
return|;
block|}
end_function

begin_function
name|gint
DECL|function|pixel_surround_rowstride (PixelSurround * ps)
name|pixel_surround_rowstride
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|)
block|{
return|return
name|ps
operator|->
name|row_stride
return|;
block|}
end_function

begin_function
name|void
DECL|function|pixel_surround_release (PixelSurround * ps)
name|pixel_surround_release
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|)
block|{
comment|/* always get new tile (for now), so release the old one */
if|if
condition|(
name|ps
operator|->
name|tile
condition|)
block|{
name|tile_release
argument_list|(
name|ps
operator|->
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|ps
operator|->
name|tile
operator|=
literal|0
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|pixel_surround_clear (PixelSurround * ps)
name|pixel_surround_clear
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|)
block|{
if|if
condition|(
name|ps
operator|->
name|buff
condition|)
block|{
name|g_free
argument_list|(
name|ps
operator|->
name|buff
argument_list|)
expr_stmt|;
name|ps
operator|->
name|buff
operator|=
literal|0
expr_stmt|;
name|ps
operator|->
name|buff_size
operator|=
literal|0
expr_stmt|;
block|}
block|}
end_function

end_unit

