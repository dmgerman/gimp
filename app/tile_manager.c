begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"tile_cache.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager.h"
end_include

begin_include
include|#
directive|include
file|"tile_swap.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager_pvt.h"
end_include

begin_include
include|#
directive|include
file|"tile_pvt.h"
end_include

begin_comment
comment|/* ick. */
end_comment

begin_function_decl
specifier|static
name|int
name|tile_manager_get_tile_num
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|int
name|xpixel
parameter_list|,
name|int
name|ypixel
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|TileManager
modifier|*
DECL|function|tile_manager_new (int toplevel_width,int toplevel_height,int bpp)
name|tile_manager_new
parameter_list|(
name|int
name|toplevel_width
parameter_list|,
name|int
name|toplevel_height
parameter_list|,
name|int
name|bpp
parameter_list|)
block|{
name|TileManager
modifier|*
name|tm
decl_stmt|;
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
name|tm
operator|=
name|g_new
argument_list|(
name|TileManager
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|tm
operator|->
name|user_data
operator|=
name|NULL
expr_stmt|;
name|tm
operator|->
name|validate_proc
operator|=
name|NULL
expr_stmt|;
name|width
operator|=
name|toplevel_width
expr_stmt|;
name|height
operator|=
name|toplevel_height
expr_stmt|;
name|tm
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|tm
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|tm
operator|->
name|bpp
operator|=
name|bpp
expr_stmt|;
name|tm
operator|->
name|ntile_rows
operator|=
operator|(
name|height
operator|+
name|TILE_HEIGHT
operator|-
literal|1
operator|)
operator|/
name|TILE_HEIGHT
expr_stmt|;
name|tm
operator|->
name|ntile_cols
operator|=
operator|(
name|width
operator|+
name|TILE_WIDTH
operator|-
literal|1
operator|)
operator|/
name|TILE_WIDTH
expr_stmt|;
name|tm
operator|->
name|tiles
operator|=
name|NULL
expr_stmt|;
return|return
name|tm
return|;
block|}
end_function

begin_function
name|void
DECL|function|tile_manager_destroy (TileManager * tm)
name|tile_manager_destroy
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|)
block|{
name|int
name|ntiles
decl_stmt|;
name|int
name|i
decl_stmt|;
if|if
condition|(
name|tm
operator|->
name|tiles
condition|)
block|{
name|ntiles
operator|=
name|tm
operator|->
name|ntile_rows
operator|*
name|tm
operator|->
name|ntile_cols
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|ntiles
condition|;
name|i
operator|++
control|)
block|{
name|TILE_MUTEX_LOCK
argument_list|(
name|tm
operator|->
name|tiles
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|tile_detach
argument_list|(
name|tm
operator|->
name|tiles
index|[
name|i
index|]
argument_list|,
name|tm
argument_list|,
name|i
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|tm
operator|->
name|tiles
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|tm
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tile_manager_set_validate_proc (TileManager * tm,TileValidateProc proc)
name|tile_manager_set_validate_proc
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|TileValidateProc
name|proc
parameter_list|)
block|{
name|tm
operator|->
name|validate_proc
operator|=
name|proc
expr_stmt|;
block|}
end_function

begin_function
name|Tile
modifier|*
DECL|function|tile_manager_get_tile (TileManager * tm,int xpixel,int ypixel,int wantread,int wantwrite)
name|tile_manager_get_tile
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|int
name|xpixel
parameter_list|,
name|int
name|ypixel
parameter_list|,
name|int
name|wantread
parameter_list|,
name|int
name|wantwrite
parameter_list|)
block|{
name|int
name|tile_num
decl_stmt|;
name|tile_num
operator|=
name|tile_manager_get_tile_num
argument_list|(
name|tm
argument_list|,
name|xpixel
argument_list|,
name|ypixel
argument_list|)
expr_stmt|;
if|if
condition|(
name|tile_num
operator|<
literal|0
condition|)
return|return
name|NULL
return|;
return|return
name|tile_manager_get
argument_list|(
name|tm
argument_list|,
name|tile_num
argument_list|,
name|wantread
argument_list|,
name|wantwrite
argument_list|)
return|;
block|}
end_function

begin_function
name|Tile
modifier|*
DECL|function|tile_manager_get (TileManager * tm,int tile_num,int wantread,int wantwrite)
name|tile_manager_get
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|int
name|tile_num
parameter_list|,
name|int
name|wantread
parameter_list|,
name|int
name|wantwrite
parameter_list|)
block|{
name|Tile
modifier|*
modifier|*
name|tiles
decl_stmt|;
name|Tile
modifier|*
modifier|*
name|tile_ptr
decl_stmt|;
name|int
name|ntiles
decl_stmt|;
name|int
name|nrows
decl_stmt|,
name|ncols
decl_stmt|;
name|int
name|right_tile
decl_stmt|;
name|int
name|bottom_tile
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|ntiles
operator|=
name|tm
operator|->
name|ntile_rows
operator|*
name|tm
operator|->
name|ntile_cols
expr_stmt|;
if|if
condition|(
operator|(
name|tile_num
operator|<
literal|0
operator|)
operator|||
operator|(
name|tile_num
operator|>=
name|ntiles
operator|)
condition|)
return|return
name|NULL
return|;
if|if
condition|(
operator|!
name|tm
operator|->
name|tiles
condition|)
block|{
name|tm
operator|->
name|tiles
operator|=
name|g_new
argument_list|(
name|Tile
operator|*
argument_list|,
name|ntiles
argument_list|)
expr_stmt|;
name|tiles
operator|=
name|tm
operator|->
name|tiles
expr_stmt|;
name|nrows
operator|=
name|tm
operator|->
name|ntile_rows
expr_stmt|;
name|ncols
operator|=
name|tm
operator|->
name|ntile_cols
expr_stmt|;
name|right_tile
operator|=
name|tm
operator|->
name|width
operator|-
operator|(
operator|(
name|ncols
operator|-
literal|1
operator|)
operator|*
name|TILE_WIDTH
operator|)
expr_stmt|;
name|bottom_tile
operator|=
name|tm
operator|->
name|height
operator|-
operator|(
operator|(
name|nrows
operator|-
literal|1
operator|)
operator|*
name|TILE_HEIGHT
operator|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|k
operator|=
literal|0
init|;
name|i
operator|<
name|nrows
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|ncols
condition|;
name|j
operator|++
operator|,
name|k
operator|++
control|)
block|{
name|tiles
index|[
name|k
index|]
operator|=
name|g_new
argument_list|(
name|Tile
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|tile_init
argument_list|(
name|tiles
index|[
name|k
index|]
argument_list|,
name|tm
operator|->
name|bpp
argument_list|)
expr_stmt|;
name|tile_attach
argument_list|(
name|tiles
index|[
name|k
index|]
argument_list|,
name|tm
argument_list|,
name|k
argument_list|)
expr_stmt|;
if|if
condition|(
name|j
operator|==
operator|(
name|ncols
operator|-
literal|1
operator|)
condition|)
name|tiles
index|[
name|k
index|]
operator|->
name|ewidth
operator|=
name|right_tile
expr_stmt|;
if|if
condition|(
name|i
operator|==
operator|(
name|nrows
operator|-
literal|1
operator|)
condition|)
name|tiles
index|[
name|k
index|]
operator|->
name|eheight
operator|=
name|bottom_tile
expr_stmt|;
block|}
block|}
block|}
name|tile_ptr
operator|=
operator|&
name|tm
operator|->
name|tiles
index|[
name|tile_num
index|]
expr_stmt|;
if|if
condition|(
name|wantwrite
operator|&&
operator|!
name|wantread
condition|)
block|{
name|g_warning
argument_list|(
literal|"WRITE-ONLY TILE... UNTESTED!"
argument_list|)
expr_stmt|;
block|}
comment|/*   if ((*tile_ptr)->share_count&&       (*tile_ptr)->write_count)     fprintf(stderr,">> MEEPITY %d,%d<< ", 	    (*tile_ptr)->share_count, 	    (*tile_ptr)->write_count 	    ); */
if|if
condition|(
name|wantread
condition|)
block|{
name|TILE_MUTEX_LOCK
argument_list|(
operator|*
name|tile_ptr
argument_list|)
expr_stmt|;
if|if
condition|(
name|wantwrite
condition|)
block|{
if|if
condition|(
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|share_count
operator|>
literal|1
condition|)
block|{
comment|/* Copy-on-write required */
name|Tile
modifier|*
name|newtile
init|=
name|g_new
argument_list|(
name|Tile
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|tile_init
argument_list|(
name|newtile
argument_list|,
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|bpp
argument_list|)
expr_stmt|;
name|newtile
operator|->
name|ewidth
operator|=
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|ewidth
expr_stmt|;
name|newtile
operator|->
name|eheight
operator|=
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|eheight
expr_stmt|;
name|newtile
operator|->
name|valid
operator|=
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|valid
expr_stmt|;
name|newtile
operator|->
name|data
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|tile_size
argument_list|(
name|newtile
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|newtile
operator|->
name|valid
condition|)
name|g_warning
argument_list|(
literal|"Oh boy, r/w tile is invalid... we suck.  Please report."
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|rowhint
condition|)
block|{
name|tile_sanitize_rowhints
argument_list|(
name|newtile
argument_list|)
expr_stmt|;
name|i
operator|=
name|newtile
operator|->
name|eheight
expr_stmt|;
while|while
condition|(
name|i
operator|--
condition|)
block|{
name|newtile
operator|->
name|rowhint
index|[
name|i
index|]
operator|=
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|rowhint
index|[
name|i
index|]
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|data
operator|!=
name|NULL
condition|)
block|{
name|memcpy
argument_list|(
name|newtile
operator|->
name|data
argument_list|,
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|data
argument_list|,
name|tile_size
argument_list|(
name|newtile
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tile_lock
argument_list|(
operator|*
name|tile_ptr
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|newtile
operator|->
name|data
argument_list|,
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|data
argument_list|,
name|tile_size
argument_list|(
name|newtile
argument_list|)
argument_list|)
expr_stmt|;
name|tile_release
argument_list|(
operator|*
name|tile_ptr
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|tile_detach
argument_list|(
operator|*
name|tile_ptr
argument_list|,
name|tm
argument_list|,
name|tile_num
argument_list|)
expr_stmt|;
name|TILE_MUTEX_LOCK
argument_list|(
name|newtile
argument_list|)
expr_stmt|;
name|tile_attach
argument_list|(
name|newtile
argument_list|,
name|tm
argument_list|,
name|tile_num
argument_list|)
expr_stmt|;
operator|*
name|tile_ptr
operator|=
name|newtile
expr_stmt|;
block|}
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|write_count
operator|++
expr_stmt|;
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|dirty
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/*       else 	{ 	  if ((*tile_ptr)->write_count) 	    fprintf(stderr,"STINK! r/o on r/w tile /%d\007  ",(*tile_ptr)->write_count); 	} */
name|TILE_MUTEX_UNLOCK
argument_list|(
operator|*
name|tile_ptr
argument_list|)
expr_stmt|;
name|tile_lock
argument_list|(
operator|*
name|tile_ptr
argument_list|)
expr_stmt|;
block|}
return|return
operator|*
name|tile_ptr
return|;
block|}
end_function

begin_function
name|void
DECL|function|tile_manager_get_async (TileManager * tm,int xpixel,int ypixel)
name|tile_manager_get_async
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|int
name|xpixel
parameter_list|,
name|int
name|ypixel
parameter_list|)
block|{
name|Tile
modifier|*
name|tile_ptr
decl_stmt|;
name|int
name|tile_num
decl_stmt|;
name|tile_num
operator|=
name|tile_manager_get_tile_num
argument_list|(
name|tm
argument_list|,
name|xpixel
argument_list|,
name|ypixel
argument_list|)
expr_stmt|;
if|if
condition|(
name|tile_num
operator|<
literal|0
condition|)
return|return;
name|tile_ptr
operator|=
name|tm
operator|->
name|tiles
index|[
name|tile_num
index|]
expr_stmt|;
name|tile_swap_in_async
argument_list|(
name|tile_ptr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tile_manager_validate (TileManager * tm,Tile * tile)
name|tile_manager_validate
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
name|tile
operator|->
name|valid
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|tm
operator|->
name|validate_proc
condition|)
call|(
modifier|*
name|tm
operator|->
name|validate_proc
call|)
argument_list|(
name|tm
argument_list|,
name|tile
argument_list|)
expr_stmt|;
comment|/* DEBUG STUFF ->  if (tm->user_data)     {       //      fprintf(stderr,"V%p  ",tm->user_data);       fprintf(stderr,"V");     }   else     {       fprintf(stderr,"v");     } */
block|}
end_function

begin_function
name|void
DECL|function|tile_manager_invalidate_tiles (TileManager * tm,Tile * toplevel_tile)
name|tile_manager_invalidate_tiles
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|Tile
modifier|*
name|toplevel_tile
parameter_list|)
block|{
name|double
name|x
decl_stmt|,
name|y
decl_stmt|;
name|int
name|row
decl_stmt|,
name|col
decl_stmt|;
name|int
name|num
decl_stmt|;
name|col
operator|=
name|toplevel_tile
operator|->
name|tlink
operator|->
name|tile_num
operator|%
name|tm
operator|->
name|ntile_cols
expr_stmt|;
name|row
operator|=
name|toplevel_tile
operator|->
name|tlink
operator|->
name|tile_num
operator|/
name|tm
operator|->
name|ntile_cols
expr_stmt|;
name|x
operator|=
operator|(
name|col
operator|*
name|TILE_WIDTH
operator|+
name|toplevel_tile
operator|->
name|ewidth
operator|/
literal|2.0
operator|)
operator|/
operator|(
name|double
operator|)
name|tm
operator|->
name|width
expr_stmt|;
name|y
operator|=
operator|(
name|row
operator|*
name|TILE_HEIGHT
operator|+
name|toplevel_tile
operator|->
name|eheight
operator|/
literal|2.0
operator|)
operator|/
operator|(
name|double
operator|)
name|tm
operator|->
name|height
expr_stmt|;
if|if
condition|(
name|tm
operator|->
name|tiles
condition|)
block|{
name|col
operator|=
name|x
operator|*
name|tm
operator|->
name|width
operator|/
name|TILE_WIDTH
expr_stmt|;
name|row
operator|=
name|y
operator|*
name|tm
operator|->
name|height
operator|/
name|TILE_HEIGHT
expr_stmt|;
name|num
operator|=
name|row
operator|*
name|tm
operator|->
name|ntile_cols
operator|+
name|col
expr_stmt|;
name|tile_invalidate
argument_list|(
operator|&
name|tm
operator|->
name|tiles
index|[
name|num
index|]
argument_list|,
name|tm
argument_list|,
name|num
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tile_invalidate_tile (Tile ** tile_ptr,TileManager * tm,int xpixel,int ypixel)
name|tile_invalidate_tile
parameter_list|(
name|Tile
modifier|*
modifier|*
name|tile_ptr
parameter_list|,
name|TileManager
modifier|*
name|tm
parameter_list|,
name|int
name|xpixel
parameter_list|,
name|int
name|ypixel
parameter_list|)
block|{
name|int
name|tile_num
decl_stmt|;
name|tile_num
operator|=
name|tile_manager_get_tile_num
argument_list|(
name|tm
argument_list|,
name|xpixel
argument_list|,
name|ypixel
argument_list|)
expr_stmt|;
if|if
condition|(
name|tile_num
operator|<
literal|0
condition|)
return|return;
name|tile_invalidate
argument_list|(
name|tile_ptr
argument_list|,
name|tm
argument_list|,
name|tile_num
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tile_invalidate (Tile ** tile_ptr,TileManager * tm,int tile_num)
name|tile_invalidate
parameter_list|(
name|Tile
modifier|*
modifier|*
name|tile_ptr
parameter_list|,
name|TileManager
modifier|*
name|tm
parameter_list|,
name|int
name|tile_num
parameter_list|)
block|{
name|Tile
modifier|*
name|tile
init|=
operator|*
name|tile_ptr
decl_stmt|;
name|TILE_MUTEX_LOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tile
operator|->
name|valid
condition|)
goto|goto
name|leave
goto|;
if|if
condition|(
name|tile
operator|->
name|share_count
operator|>
literal|1
condition|)
block|{
comment|/* This tile is shared.  Replace it with a new, invalid tile. */
name|Tile
modifier|*
name|newtile
init|=
name|g_new
argument_list|(
name|Tile
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|tile_init
argument_list|(
name|newtile
argument_list|,
name|tile
operator|->
name|bpp
argument_list|)
expr_stmt|;
name|newtile
operator|->
name|ewidth
operator|=
name|tile
operator|->
name|ewidth
expr_stmt|;
name|newtile
operator|->
name|eheight
operator|=
name|tile
operator|->
name|eheight
expr_stmt|;
name|tile_detach
argument_list|(
name|tile
argument_list|,
name|tm
argument_list|,
name|tile_num
argument_list|)
expr_stmt|;
name|TILE_MUTEX_LOCK
argument_list|(
name|newtile
argument_list|)
expr_stmt|;
name|tile_attach
argument_list|(
name|newtile
argument_list|,
name|tm
argument_list|,
name|tile_num
argument_list|)
expr_stmt|;
name|tile
operator|=
operator|*
name|tile_ptr
operator|=
name|newtile
expr_stmt|;
block|}
if|if
condition|(
name|tile
operator|->
name|listhead
condition|)
name|tile_cache_flush
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|tile
operator|->
name|valid
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|tile
operator|->
name|data
condition|)
block|{
name|g_free
argument_list|(
name|tile
operator|->
name|data
argument_list|)
expr_stmt|;
name|tile
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tile
operator|->
name|swap_offset
operator|!=
operator|-
literal|1
condition|)
block|{
comment|/* If the tile is on disk, then delete its        *  presence there.        */
name|tile_swap_delete
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
name|leave
label|:
name|TILE_MUTEX_UNLOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tile_manager_map_tile (TileManager * tm,int xpixel,int ypixel,Tile * srctile)
name|tile_manager_map_tile
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|int
name|xpixel
parameter_list|,
name|int
name|ypixel
parameter_list|,
name|Tile
modifier|*
name|srctile
parameter_list|)
block|{
name|int
name|tile_row
decl_stmt|;
name|int
name|tile_col
decl_stmt|;
name|int
name|tile_num
decl_stmt|;
if|if
condition|(
operator|(
name|xpixel
operator|<
literal|0
operator|)
operator|||
operator|(
name|xpixel
operator|>=
name|tm
operator|->
name|width
operator|)
operator|||
operator|(
name|ypixel
operator|<
literal|0
operator|)
operator|||
operator|(
name|ypixel
operator|>=
name|tm
operator|->
name|height
operator|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"tile_manager_map_tile: tile co-ord out of range."
argument_list|)
expr_stmt|;
return|return;
block|}
name|tile_row
operator|=
name|ypixel
operator|/
name|TILE_HEIGHT
expr_stmt|;
name|tile_col
operator|=
name|xpixel
operator|/
name|TILE_WIDTH
expr_stmt|;
name|tile_num
operator|=
name|tile_row
operator|*
name|tm
operator|->
name|ntile_cols
operator|+
name|tile_col
expr_stmt|;
name|tile_manager_map
argument_list|(
name|tm
argument_list|,
name|tile_num
argument_list|,
name|srctile
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tile_manager_map (TileManager * tm,int tile_num,Tile * srctile)
name|tile_manager_map
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|int
name|tile_num
parameter_list|,
name|Tile
modifier|*
name|srctile
parameter_list|)
block|{
name|Tile
modifier|*
modifier|*
name|tiles
decl_stmt|;
name|Tile
modifier|*
modifier|*
name|tile_ptr
decl_stmt|;
name|int
name|ntiles
decl_stmt|;
name|int
name|nrows
decl_stmt|,
name|ncols
decl_stmt|;
name|int
name|right_tile
decl_stmt|;
name|int
name|bottom_tile
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|ntiles
operator|=
name|tm
operator|->
name|ntile_rows
operator|*
name|tm
operator|->
name|ntile_cols
expr_stmt|;
if|if
condition|(
operator|(
name|tile_num
operator|<
literal|0
operator|)
operator|||
operator|(
name|tile_num
operator|>=
name|ntiles
operator|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"tile_manager_map: tile out of range."
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|tm
operator|->
name|tiles
condition|)
block|{
name|g_warning
argument_list|(
literal|"tile_manager_map: empty tile level - init'ing."
argument_list|)
expr_stmt|;
name|tm
operator|->
name|tiles
operator|=
name|g_new
argument_list|(
name|Tile
operator|*
argument_list|,
name|ntiles
argument_list|)
expr_stmt|;
name|tiles
operator|=
name|tm
operator|->
name|tiles
expr_stmt|;
name|nrows
operator|=
name|tm
operator|->
name|ntile_rows
expr_stmt|;
name|ncols
operator|=
name|tm
operator|->
name|ntile_cols
expr_stmt|;
name|right_tile
operator|=
name|tm
operator|->
name|width
operator|-
operator|(
operator|(
name|ncols
operator|-
literal|1
operator|)
operator|*
name|TILE_WIDTH
operator|)
expr_stmt|;
name|bottom_tile
operator|=
name|tm
operator|->
name|height
operator|-
operator|(
operator|(
name|nrows
operator|-
literal|1
operator|)
operator|*
name|TILE_HEIGHT
operator|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|k
operator|=
literal|0
init|;
name|i
operator|<
name|nrows
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|ncols
condition|;
name|j
operator|++
operator|,
name|k
operator|++
control|)
block|{
comment|/*	      printf(",");fflush(stdout);*/
name|tiles
index|[
name|k
index|]
operator|=
name|g_new
argument_list|(
name|Tile
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|tile_init
argument_list|(
name|tiles
index|[
name|k
index|]
argument_list|,
name|tm
operator|->
name|bpp
argument_list|)
expr_stmt|;
name|tile_attach
argument_list|(
name|tiles
index|[
name|k
index|]
argument_list|,
name|tm
argument_list|,
name|k
argument_list|)
expr_stmt|;
if|if
condition|(
name|j
operator|==
operator|(
name|ncols
operator|-
literal|1
operator|)
condition|)
name|tiles
index|[
name|k
index|]
operator|->
name|ewidth
operator|=
name|right_tile
expr_stmt|;
if|if
condition|(
name|i
operator|==
operator|(
name|nrows
operator|-
literal|1
operator|)
condition|)
name|tiles
index|[
name|k
index|]
operator|->
name|eheight
operator|=
name|bottom_tile
expr_stmt|;
block|}
block|}
comment|/*      g_warning ("tile_manager_map: empty tile level - done.");*/
block|}
name|tile_ptr
operator|=
operator|&
name|tm
operator|->
name|tiles
index|[
name|tile_num
index|]
expr_stmt|;
comment|/*  printf(")");fflush(stdout);*/
if|if
condition|(
operator|!
name|srctile
operator|->
name|valid
condition|)
name|g_warning
argument_list|(
literal|"tile_manager_map: srctile not validated yet!  please report."
argument_list|)
expr_stmt|;
name|TILE_MUTEX_LOCK
argument_list|(
operator|*
name|tile_ptr
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|ewidth
operator|!=
name|srctile
operator|->
name|ewidth
operator|||
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|eheight
operator|!=
name|srctile
operator|->
name|eheight
operator|||
operator|(
operator|*
name|tile_ptr
operator|)
operator|->
name|bpp
operator|!=
name|srctile
operator|->
name|bpp
condition|)
block|{
name|g_warning
argument_list|(
literal|"tile_manager_map: nonconformant map (%p -> %p)"
argument_list|,
name|srctile
argument_list|,
operator|*
name|tile_ptr
argument_list|)
expr_stmt|;
block|}
name|tile_detach
argument_list|(
operator|*
name|tile_ptr
argument_list|,
name|tm
argument_list|,
name|tile_num
argument_list|)
expr_stmt|;
comment|/*  printf(">");fflush(stdout);*/
name|TILE_MUTEX_LOCK
argument_list|(
name|srctile
argument_list|)
expr_stmt|;
comment|/*  printf(" [src:%p tm:%p tn:%d] ", srctile, tm, tile_num); fflush(stdout);*/
name|tile_attach
argument_list|(
name|srctile
argument_list|,
name|tm
argument_list|,
name|tile_num
argument_list|)
expr_stmt|;
operator|*
name|tile_ptr
operator|=
name|srctile
expr_stmt|;
name|TILE_MUTEX_UNLOCK
argument_list|(
name|srctile
argument_list|)
expr_stmt|;
comment|/*  printf("}");fflush(stdout);*/
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|tile_manager_get_tile_num (TileManager * tm,int xpixel,int ypixel)
name|tile_manager_get_tile_num
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|int
name|xpixel
parameter_list|,
name|int
name|ypixel
parameter_list|)
block|{
name|int
name|tile_row
decl_stmt|;
name|int
name|tile_col
decl_stmt|;
name|int
name|tile_num
decl_stmt|;
if|if
condition|(
operator|(
name|xpixel
operator|<
literal|0
operator|)
operator|||
operator|(
name|xpixel
operator|>=
name|tm
operator|->
name|width
operator|)
operator|||
operator|(
name|ypixel
operator|<
literal|0
operator|)
operator|||
operator|(
name|ypixel
operator|>=
name|tm
operator|->
name|height
operator|)
condition|)
return|return
operator|-
literal|1
return|;
name|tile_row
operator|=
name|ypixel
operator|/
name|TILE_HEIGHT
expr_stmt|;
name|tile_col
operator|=
name|xpixel
operator|/
name|TILE_WIDTH
expr_stmt|;
name|tile_num
operator|=
name|tile_row
operator|*
name|tm
operator|->
name|ntile_cols
operator|+
name|tile_col
expr_stmt|;
return|return
name|tile_num
return|;
block|}
end_function

begin_function
name|void
DECL|function|tile_manager_set_user_data (TileManager * tm,void * user_data)
name|tile_manager_set_user_data
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|void
modifier|*
name|user_data
parameter_list|)
block|{
name|tm
operator|->
name|user_data
operator|=
name|user_data
expr_stmt|;
block|}
end_function

begin_function
name|void
modifier|*
DECL|function|tile_manager_get_user_data (TileManager * tm)
name|tile_manager_get_user_data
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|)
block|{
return|return
name|tm
operator|->
name|user_data
return|;
block|}
end_function

begin_function
name|int
DECL|function|tile_manager_level_width (TileManager * tm)
name|tile_manager_level_width
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|)
block|{
return|return
name|tm
operator|->
name|width
return|;
block|}
end_function

begin_function
name|int
DECL|function|tile_manager_level_height (TileManager * tm)
name|tile_manager_level_height
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|)
block|{
return|return
name|tm
operator|->
name|height
return|;
block|}
end_function

begin_function
name|int
DECL|function|tile_manager_level_bpp (TileManager * tm)
name|tile_manager_level_bpp
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|)
block|{
return|return
name|tm
operator|->
name|bpp
return|;
block|}
end_function

begin_function
name|void
DECL|function|tile_manager_get_tile_coordinates (TileManager * tm,Tile * tile,int * x,int * y)
name|tile_manager_get_tile_coordinates
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
modifier|*
name|x
parameter_list|,
name|int
modifier|*
name|y
parameter_list|)
block|{
name|TileLink
modifier|*
name|tl
decl_stmt|;
for|for
control|(
name|tl
operator|=
name|tile
operator|->
name|tlink
init|;
name|tl
condition|;
name|tl
operator|=
name|tl
operator|->
name|next
control|)
block|{
if|if
condition|(
name|tl
operator|->
name|tm
operator|==
name|tm
condition|)
break|break;
block|}
if|if
condition|(
name|tl
operator|==
name|NULL
condition|)
block|{
name|g_warning
argument_list|(
literal|"tile_manager_get_tile_coordinates: tile not attached to manager"
argument_list|)
expr_stmt|;
return|return;
block|}
operator|*
name|x
operator|=
name|TILE_WIDTH
operator|*
operator|(
name|tl
operator|->
name|tile_num
operator|%
name|tm
operator|->
name|ntile_cols
operator|)
expr_stmt|;
operator|*
name|y
operator|=
name|TILE_HEIGHT
operator|*
operator|(
name|tl
operator|->
name|tile_num
operator|/
name|tm
operator|->
name|ntile_cols
operator|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tile_manager_map_over_tile (TileManager * tm,Tile * tile,Tile * srctile)
name|tile_manager_map_over_tile
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|,
name|Tile
modifier|*
name|srctile
parameter_list|)
block|{
name|TileLink
modifier|*
name|tl
decl_stmt|;
for|for
control|(
name|tl
operator|=
name|tile
operator|->
name|tlink
init|;
name|tl
condition|;
name|tl
operator|=
name|tl
operator|->
name|next
control|)
block|{
if|if
condition|(
name|tl
operator|->
name|tm
operator|==
name|tm
condition|)
break|break;
block|}
if|if
condition|(
name|tl
operator|==
name|NULL
condition|)
block|{
name|g_warning
argument_list|(
literal|"tile_manager_map_over_tile: tile not attached to manager"
argument_list|)
expr_stmt|;
return|return;
block|}
name|tile_manager_map
argument_list|(
name|tm
argument_list|,
name|tl
operator|->
name|tile_num
argument_list|,
name|srctile
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

