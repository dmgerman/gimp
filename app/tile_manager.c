begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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
name|void
name|tile_manager_destroy_level
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|TileLevel
modifier|*
name|level
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
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
name|tmp1
decl_stmt|,
name|tmp2
decl_stmt|;
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
name|int
name|i
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
name|tmp1
operator|=
name|tile_manager_calc_levels
argument_list|(
name|toplevel_width
argument_list|,
name|TILE_WIDTH
argument_list|)
expr_stmt|;
name|tmp2
operator|=
name|tile_manager_calc_levels
argument_list|(
name|toplevel_height
argument_list|,
name|TILE_HEIGHT
argument_list|)
expr_stmt|;
name|tm
operator|->
name|nlevels
operator|=
name|MAX
argument_list|(
name|tmp1
argument_list|,
name|tmp2
argument_list|)
expr_stmt|;
name|tm
operator|->
name|levels
operator|=
name|g_new
argument_list|(
name|TileLevel
argument_list|,
name|tm
operator|->
name|nlevels
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
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|tm
operator|->
name|nlevels
condition|;
name|i
operator|++
control|)
block|{
name|tm
operator|->
name|levels
index|[
name|i
index|]
operator|.
name|width
operator|=
name|width
expr_stmt|;
name|tm
operator|->
name|levels
index|[
name|i
index|]
operator|.
name|height
operator|=
name|height
expr_stmt|;
name|tm
operator|->
name|levels
index|[
name|i
index|]
operator|.
name|bpp
operator|=
name|bpp
expr_stmt|;
name|tm
operator|->
name|levels
index|[
name|i
index|]
operator|.
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
name|levels
index|[
name|i
index|]
operator|.
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
name|levels
index|[
name|i
index|]
operator|.
name|tiles
operator|=
name|NULL
expr_stmt|;
name|width
operator|/=
literal|2
expr_stmt|;
name|height
operator|/=
literal|2
expr_stmt|;
block|}
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
name|tm
operator|->
name|nlevels
condition|;
name|i
operator|++
control|)
name|tile_manager_destroy_level
argument_list|(
name|tm
argument_list|,
operator|&
name|tm
operator|->
name|levels
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tm
operator|->
name|levels
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tm
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|int
DECL|function|tile_manager_calc_levels (int size,int tile_size)
name|tile_manager_calc_levels
parameter_list|(
name|int
name|size
parameter_list|,
name|int
name|tile_size
parameter_list|)
block|{
name|int
name|levels
decl_stmt|;
name|levels
operator|=
literal|1
expr_stmt|;
while|while
condition|(
name|size
operator|>
name|tile_size
condition|)
block|{
name|size
operator|/=
literal|2
expr_stmt|;
name|levels
operator|+=
literal|1
expr_stmt|;
block|}
return|return
name|levels
return|;
block|}
end_function

begin_function
name|void
DECL|function|tile_manager_set_nlevels (TileManager * tm,int nlevels)
name|tile_manager_set_nlevels
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|int
name|nlevels
parameter_list|)
block|{
name|TileLevel
modifier|*
name|levels
decl_stmt|;
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
name|int
name|i
decl_stmt|;
if|if
condition|(
operator|(
name|nlevels
operator|<
literal|1
operator|)
operator|||
operator|(
name|nlevels
operator|==
name|tm
operator|->
name|nlevels
operator|)
condition|)
return|return;
name|levels
operator|=
name|g_new
argument_list|(
name|TileLevel
argument_list|,
name|nlevels
argument_list|)
expr_stmt|;
if|if
condition|(
name|nlevels
operator|>
name|tm
operator|->
name|nlevels
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|tm
operator|->
name|nlevels
condition|;
name|i
operator|++
control|)
name|levels
index|[
name|i
index|]
operator|=
name|tm
operator|->
name|levels
index|[
name|i
index|]
expr_stmt|;
name|width
operator|=
name|tm
operator|->
name|levels
index|[
name|tm
operator|->
name|nlevels
operator|-
literal|1
index|]
operator|.
name|width
expr_stmt|;
name|height
operator|=
name|tm
operator|->
name|levels
index|[
name|tm
operator|->
name|nlevels
operator|-
literal|1
index|]
operator|.
name|height
expr_stmt|;
for|for
control|(
init|;
name|i
operator|<
name|nlevels
condition|;
name|i
operator|++
control|)
block|{
name|levels
index|[
name|i
index|]
operator|.
name|width
operator|=
name|width
expr_stmt|;
name|levels
index|[
name|i
index|]
operator|.
name|height
operator|=
name|height
expr_stmt|;
name|levels
index|[
name|i
index|]
operator|.
name|bpp
operator|=
name|tm
operator|->
name|levels
index|[
literal|0
index|]
operator|.
name|bpp
expr_stmt|;
name|levels
index|[
name|i
index|]
operator|.
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
name|levels
index|[
name|i
index|]
operator|.
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
name|levels
index|[
name|i
index|]
operator|.
name|tiles
operator|=
name|NULL
expr_stmt|;
name|width
operator|/=
literal|2
expr_stmt|;
name|height
operator|/=
literal|2
expr_stmt|;
if|if
condition|(
name|width
operator|<
literal|1
condition|)
name|width
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|height
operator|<
literal|1
condition|)
name|height
operator|=
literal|1
expr_stmt|;
block|}
block|}
else|else
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|nlevels
condition|;
name|i
operator|++
control|)
name|levels
index|[
name|i
index|]
operator|=
name|tm
operator|->
name|levels
index|[
name|i
index|]
expr_stmt|;
for|for
control|(
init|;
name|i
operator|<
name|tm
operator|->
name|nlevels
condition|;
name|i
operator|++
control|)
name|tile_manager_destroy_level
argument_list|(
name|tm
argument_list|,
operator|&
name|tm
operator|->
name|levels
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|tm
operator|->
name|levels
argument_list|)
expr_stmt|;
name|tm
operator|->
name|nlevels
operator|=
name|nlevels
expr_stmt|;
name|tm
operator|->
name|levels
operator|=
name|levels
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
DECL|function|tile_manager_get_tile (TileManager * tm,int xpixel,int ypixel,int level,int wantread,int wantwrite)
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
name|level
parameter_list|,
name|int
name|wantread
parameter_list|,
name|int
name|wantwrite
parameter_list|)
block|{
name|TileLevel
modifier|*
name|tile_level
decl_stmt|;
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
name|level
operator|<
literal|0
operator|)
operator|||
operator|(
name|level
operator|>=
name|tm
operator|->
name|nlevels
operator|)
condition|)
return|return
name|NULL
return|;
name|tile_level
operator|=
operator|&
name|tm
operator|->
name|levels
index|[
name|level
index|]
expr_stmt|;
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
name|tile_level
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
name|tile_level
operator|->
name|height
operator|)
condition|)
return|return
name|NULL
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
name|tile_level
operator|->
name|ntile_cols
operator|+
name|tile_col
expr_stmt|;
return|return
name|tile_manager_get
argument_list|(
name|tm
argument_list|,
name|tile_num
argument_list|,
name|level
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
DECL|function|tile_manager_get (TileManager * tm,int tile_num,int level,int wantread,int wantwrite)
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
name|level
parameter_list|,
name|int
name|wantread
parameter_list|,
name|int
name|wantwrite
parameter_list|)
block|{
name|TileLevel
modifier|*
name|tile_level
decl_stmt|;
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
if|if
condition|(
operator|(
name|level
operator|<
literal|0
operator|)
operator|||
operator|(
name|level
operator|>=
name|tm
operator|->
name|nlevels
operator|)
condition|)
return|return
name|NULL
return|;
name|tile_level
operator|=
operator|&
name|tm
operator|->
name|levels
index|[
name|level
index|]
expr_stmt|;
name|ntiles
operator|=
name|tile_level
operator|->
name|ntile_rows
operator|*
name|tile_level
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
name|tile_level
operator|->
name|tiles
condition|)
block|{
name|tile_level
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
name|tile_level
operator|->
name|tiles
expr_stmt|;
name|nrows
operator|=
name|tile_level
operator|->
name|ntile_rows
expr_stmt|;
name|ncols
operator|=
name|tile_level
operator|->
name|ntile_cols
expr_stmt|;
name|right_tile
operator|=
name|tile_level
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
name|tile_level
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
name|tile_level
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
name|tile_level
operator|->
name|tiles
index|[
name|tile_num
index|]
expr_stmt|;
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
literal|1
expr_stmt|;
block|}
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
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
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
name|TileLevel
modifier|*
name|level
decl_stmt|;
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
name|int
name|i
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
name|levels
index|[
literal|0
index|]
operator|.
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
name|levels
index|[
literal|0
index|]
operator|.
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
name|levels
index|[
literal|0
index|]
operator|.
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
name|levels
index|[
literal|0
index|]
operator|.
name|height
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|tm
operator|->
name|nlevels
condition|;
name|i
operator|++
control|)
block|{
name|level
operator|=
operator|&
name|tm
operator|->
name|levels
index|[
name|i
index|]
expr_stmt|;
if|if
condition|(
name|level
operator|->
name|tiles
condition|)
block|{
name|col
operator|=
name|x
operator|*
name|level
operator|->
name|width
operator|/
name|TILE_WIDTH
expr_stmt|;
name|row
operator|=
name|y
operator|*
name|level
operator|->
name|height
operator|/
name|TILE_HEIGHT
expr_stmt|;
name|num
operator|=
name|row
operator|*
name|level
operator|->
name|ntile_cols
operator|+
name|col
expr_stmt|;
name|tile_invalidate
argument_list|(
operator|&
name|level
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
block|}
end_function

begin_function
name|void
DECL|function|tile_manager_invalidate_sublevels (TileManager * tm)
name|tile_manager_invalidate_sublevels
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
decl_stmt|,
name|j
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|tm
operator|->
name|nlevels
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|tm
operator|->
name|levels
index|[
name|i
index|]
operator|.
name|tiles
condition|)
block|{
name|ntiles
operator|=
name|tm
operator|->
name|levels
index|[
name|i
index|]
operator|.
name|ntile_rows
operator|*
name|tm
operator|->
name|levels
index|[
name|i
index|]
operator|.
name|ntile_cols
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|ntiles
condition|;
name|j
operator|++
control|)
name|tile_invalidate
argument_list|(
operator|&
name|tm
operator|->
name|levels
index|[
name|i
index|]
operator|.
name|tiles
index|[
name|j
index|]
argument_list|,
name|tm
argument_list|,
name|j
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|tile_manager_update_tile (TileManager * tm,Tile * toplevel_tile,int level)
name|tile_manager_update_tile
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|Tile
modifier|*
name|toplevel_tile
parameter_list|,
name|int
name|level
parameter_list|)
block|{
name|TileLevel
modifier|*
name|tile_level
decl_stmt|;
name|Tile
modifier|*
name|tile
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|double
name|x
decl_stmt|,
name|y
decl_stmt|;
name|int
name|srcx
decl_stmt|,
name|srcy
decl_stmt|;
name|int
name|tilex
decl_stmt|,
name|tiley
decl_stmt|;
name|int
name|tilew
decl_stmt|,
name|tileh
decl_stmt|;
name|int
name|bpp
decl_stmt|;
name|int
name|row
decl_stmt|,
name|col
decl_stmt|;
name|int
name|num
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
if|if
condition|(
operator|(
name|level
operator|<
literal|1
operator|)
operator|||
operator|(
name|level
operator|>=
name|tm
operator|->
name|nlevels
operator|)
condition|)
return|return;
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
name|levels
index|[
literal|0
index|]
operator|.
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
name|levels
index|[
literal|0
index|]
operator|.
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
name|levels
index|[
literal|0
index|]
operator|.
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
name|levels
index|[
literal|0
index|]
operator|.
name|height
expr_stmt|;
name|tilex
operator|=
operator|(
operator|(
name|col
operator|*
name|TILE_WIDTH
operator|)
operator|>>
name|level
operator|)
operator|%
literal|64
expr_stmt|;
name|tiley
operator|=
operator|(
operator|(
name|row
operator|*
name|TILE_HEIGHT
operator|)
operator|>>
name|level
operator|)
operator|%
literal|64
expr_stmt|;
if|if
condition|(
name|level
operator|>
literal|6
condition|)
block|{
if|if
condition|(
operator|(
operator|(
name|col
operator|%
operator|(
name|level
operator|-
literal|6
operator|)
operator|)
operator|!=
literal|0
operator|)
operator|||
operator|(
operator|(
name|row
operator|%
operator|(
name|level
operator|-
literal|6
operator|)
operator|)
operator|!=
literal|0
operator|)
condition|)
return|return;
name|tilew
operator|=
literal|1
expr_stmt|;
name|tileh
operator|=
literal|1
expr_stmt|;
block|}
else|else
block|{
name|tilew
operator|=
operator|(
name|toplevel_tile
operator|->
name|ewidth
operator|)
operator|>>
name|level
expr_stmt|;
name|tileh
operator|=
operator|(
name|toplevel_tile
operator|->
name|eheight
operator|)
operator|>>
name|level
expr_stmt|;
block|}
name|tile_level
operator|=
operator|&
name|tm
operator|->
name|levels
index|[
name|level
index|]
expr_stmt|;
name|col
operator|=
operator|(
name|x
operator|*
name|tile_level
operator|->
name|width
operator|)
operator|/
name|TILE_WIDTH
expr_stmt|;
name|row
operator|=
operator|(
name|y
operator|*
name|tile_level
operator|->
name|height
operator|)
operator|/
name|TILE_HEIGHT
expr_stmt|;
name|num
operator|=
name|row
operator|*
name|tile_level
operator|->
name|ntile_cols
operator|+
name|col
expr_stmt|;
name|tile
operator|=
name|tile_manager_get
argument_list|(
name|tm
argument_list|,
name|num
argument_list|,
name|level
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|tile_lock
argument_list|(
name|toplevel_tile
argument_list|)
expr_stmt|;
name|tilew
operator|+=
name|tilex
expr_stmt|;
name|tileh
operator|+=
name|tiley
expr_stmt|;
name|bpp
operator|=
name|tile
operator|->
name|bpp
expr_stmt|;
for|for
control|(
name|i
operator|=
name|tiley
init|;
name|i
operator|<
name|tileh
condition|;
name|i
operator|++
control|)
block|{
name|srcx
operator|=
name|tilex
operator|<<
name|level
expr_stmt|;
name|srcy
operator|=
name|tiley
operator|<<
name|level
expr_stmt|;
name|src
operator|=
name|toplevel_tile
operator|->
name|data
operator|+
operator|(
name|srcy
operator|*
name|toplevel_tile
operator|->
name|ewidth
operator|+
name|srcx
operator|)
operator|*
name|bpp
expr_stmt|;
name|dest
operator|=
name|tile
operator|->
name|data
operator|+
operator|(
name|tiley
operator|*
name|tile
operator|->
name|ewidth
operator|+
name|tilex
operator|)
operator|*
name|bpp
expr_stmt|;
for|for
control|(
name|j
operator|=
name|tilex
init|;
name|j
operator|<
name|tilew
condition|;
name|j
operator|++
control|)
block|{
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|bpp
condition|;
name|k
operator|++
control|)
name|dest
index|[
name|k
index|]
operator|=
name|src
index|[
name|k
index|]
expr_stmt|;
name|dest
operator|+=
name|bpp
expr_stmt|;
name|src
operator|+=
operator|(
name|bpp
operator|<<
name|level
operator|)
expr_stmt|;
block|}
block|}
name|tile_release
argument_list|(
name|tile
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|tile_release
argument_list|(
name|toplevel_tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_manager_destroy_level (TileManager * tm,TileLevel * level)
name|tile_manager_destroy_level
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|TileLevel
modifier|*
name|level
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
name|level
operator|->
name|tiles
condition|)
block|{
name|ntiles
operator|=
name|level
operator|->
name|ntile_rows
operator|*
name|level
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
name|level
operator|->
name|tiles
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|tile_detach
argument_list|(
name|level
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
name|level
operator|->
name|tiles
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
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
DECL|function|tile_manager_map_tile (TileManager * tm,int xpixel,int ypixel,int level,Tile * srctile)
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
name|int
name|level
parameter_list|,
name|Tile
modifier|*
name|srctile
parameter_list|)
block|{
name|TileLevel
modifier|*
name|tile_level
decl_stmt|;
name|int
name|tile_row
decl_stmt|;
name|int
name|tile_col
decl_stmt|;
name|int
name|tile_num
decl_stmt|;
comment|/*  printf("#");fflush(stdout); */
if|if
condition|(
operator|(
name|level
operator|<
literal|0
operator|)
operator|||
operator|(
name|level
operator|>=
name|tm
operator|->
name|nlevels
operator|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"tile_manager_map_tile: level out of range."
argument_list|)
expr_stmt|;
return|return;
block|}
name|tile_level
operator|=
operator|&
name|tm
operator|->
name|levels
index|[
name|level
index|]
expr_stmt|;
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
name|tile_level
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
name|tile_level
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
name|tile_level
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
name|level
argument_list|,
name|srctile
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tile_manager_map (TileManager * tm,int tile_num,int level,Tile * srctile)
name|tile_manager_map
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|int
name|tile_num
parameter_list|,
name|int
name|level
parameter_list|,
name|Tile
modifier|*
name|srctile
parameter_list|)
block|{
name|TileLevel
modifier|*
name|tile_level
decl_stmt|;
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
comment|/*  printf("@");fflush(stdout);*/
if|if
condition|(
operator|(
name|level
operator|<
literal|0
operator|)
operator|||
operator|(
name|level
operator|>=
name|tm
operator|->
name|nlevels
operator|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"tile_manager_map: level out of range."
argument_list|)
expr_stmt|;
return|return;
block|}
name|tile_level
operator|=
operator|&
name|tm
operator|->
name|levels
index|[
name|level
index|]
expr_stmt|;
name|ntiles
operator|=
name|tile_level
operator|->
name|ntile_rows
operator|*
name|tile_level
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
name|tile_level
operator|->
name|tiles
condition|)
block|{
comment|/*      g_warning ("tile_manager_map: empty tile level - init'ing.");*/
name|tile_level
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
name|tile_level
operator|->
name|tiles
expr_stmt|;
name|nrows
operator|=
name|tile_level
operator|->
name|ntile_rows
expr_stmt|;
name|ncols
operator|=
name|tile_level
operator|->
name|ntile_cols
expr_stmt|;
name|right_tile
operator|=
name|tile_level
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
name|tile_level
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
name|tile_level
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
name|tile_level
operator|->
name|tiles
index|[
name|tile_num
index|]
expr_stmt|;
comment|/*  printf(")");fflush(stdout);*/
name|TILE_MUTEX_LOCK
argument_list|(
operator|*
name|tile_ptr
argument_list|)
expr_stmt|;
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

end_unit

