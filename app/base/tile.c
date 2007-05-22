begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"tile.h"
end_include

begin_include
include|#
directive|include
file|"tile-private.h"
end_include

begin_include
include|#
directive|include
file|"tile-cache.h"
end_include

begin_include
include|#
directive|include
file|"tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"tile-swap.h"
end_include

begin_comment
comment|/*  Uncomment for verbose debugging on copy-on-write logic  */
end_comment

begin_comment
comment|/*  #define TILE_DEBUG  */
end_comment

begin_comment
comment|/*  Uncomment to enable global counters to profile the tile system. */
end_comment

begin_comment
comment|/*  #define TILE_PROFILING */
end_comment

begin_comment
comment|/*  Sanity checks on tile hinting code  */
end_comment

begin_comment
comment|/*  #define HINTS_SANITY */
end_comment

begin_comment
comment|/*  This is being used from tile-swap, but just for debugging purposes.  */
end_comment

begin_decl_stmt
DECL|variable|tile_ref_count
specifier|static
name|gint
name|tile_ref_count
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_ifdef
ifdef|#
directive|ifdef
name|TILE_PROFILING
end_ifdef

begin_decl_stmt
DECL|variable|tile_count
specifier|static
name|gint
name|tile_count
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tile_share_count
specifier|static
name|gint
name|tile_share_count
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tile_active_count
specifier|static
name|gint
name|tile_active_count
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_ifdef
ifdef|#
directive|ifdef
name|HINTS_SANITY
end_ifdef

begin_decl_stmt
DECL|variable|tile_exist_peak
specifier|static
name|gint
name|tile_exist_peak
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tile_exist_count
specifier|static
name|gint
name|tile_exist_count
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
specifier|static
name|void
name|tile_destroy
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|tile_sanitize_rowhints (Tile * tile)
name|tile_sanitize_rowhints
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
if|if
condition|(
operator|!
name|tile
operator|->
name|rowhint
condition|)
name|tile
operator|->
name|rowhint
operator|=
name|g_slice_alloc0
argument_list|(
sizeof|sizeof
argument_list|(
name|TileRowHint
argument_list|)
operator|*
name|TILE_HEIGHT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|TileRowHint
DECL|function|tile_get_rowhint (Tile * tile,gint yoff)
name|tile_get_rowhint
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|gint
name|yoff
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|HINTS_SANITY
if|if
condition|(
name|yoff
operator|<
name|tile_eheight
argument_list|(
name|tile
argument_list|)
operator|&&
name|yoff
operator|>=
literal|0
condition|)
block|{
return|return
name|tile
operator|->
name|rowhint
index|[
name|yoff
index|]
return|;
block|}
else|else
block|{
name|g_error
argument_list|(
literal|"GET_ROWHINT OUT OF RANGE"
argument_list|)
expr_stmt|;
block|}
return|return
name|TILEROWHINT_OUTOFRANGE
return|;
else|#
directive|else
return|return
name|tile
operator|->
name|rowhint
index|[
name|yoff
index|]
return|;
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|tile_set_rowhint (Tile * tile,gint yoff,TileRowHint rowhint)
name|tile_set_rowhint
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|gint
name|yoff
parameter_list|,
name|TileRowHint
name|rowhint
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|HINTS_SANITY
if|if
condition|(
name|yoff
operator|<
name|tile_eheight
argument_list|(
name|tile
argument_list|)
operator|&&
name|yoff
operator|>=
literal|0
condition|)
block|{
name|tile
operator|->
name|rowhint
index|[
name|yoff
index|]
operator|=
name|rowhint
expr_stmt|;
block|}
else|else
block|{
name|g_error
argument_list|(
literal|"SET_ROWHINT OUT OF RANGE"
argument_list|)
expr_stmt|;
block|}
else|#
directive|else
name|tile
operator|->
name|rowhint
index|[
name|yoff
index|]
operator|=
name|rowhint
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_function
name|Tile
modifier|*
DECL|function|tile_new (gint bpp)
name|tile_new
parameter_list|(
name|gint
name|bpp
parameter_list|)
block|{
name|Tile
modifier|*
name|tile
init|=
name|g_slice_new
argument_list|(
name|Tile
argument_list|)
decl_stmt|;
name|tile
operator|->
name|ref_count
operator|=
literal|0
expr_stmt|;
name|tile
operator|->
name|write_count
operator|=
literal|0
expr_stmt|;
name|tile
operator|->
name|share_count
operator|=
literal|0
expr_stmt|;
name|tile
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
name|tile
operator|->
name|valid
operator|=
name|FALSE
expr_stmt|;
name|tile
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
name|tile
operator|->
name|ewidth
operator|=
name|TILE_WIDTH
expr_stmt|;
name|tile
operator|->
name|eheight
operator|=
name|TILE_HEIGHT
expr_stmt|;
name|tile
operator|->
name|bpp
operator|=
name|bpp
expr_stmt|;
name|tile
operator|->
name|swap_num
operator|=
literal|1
expr_stmt|;
name|tile
operator|->
name|swap_offset
operator|=
operator|-
literal|1
expr_stmt|;
name|tile
operator|->
name|tlink
operator|=
name|NULL
expr_stmt|;
name|tile
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
name|tile
operator|->
name|prev
operator|=
name|NULL
expr_stmt|;
name|tile
operator|->
name|listhead
operator|=
name|NULL
expr_stmt|;
name|tile
operator|->
name|rowhint
operator|=
name|NULL
expr_stmt|;
ifdef|#
directive|ifdef
name|TILE_PROFILING
name|tile_count
operator|++
expr_stmt|;
endif|#
directive|endif
return|return
name|tile
return|;
block|}
end_function

begin_function
name|void
DECL|function|tile_lock (Tile * tile)
name|tile_lock
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
comment|/* Increment the global reference count.    */
name|tile_ref_count
operator|++
expr_stmt|;
comment|/* Increment this tile's reference count.    */
name|tile
operator|->
name|ref_count
operator|++
expr_stmt|;
if|if
condition|(
name|tile
operator|->
name|ref_count
operator|==
literal|1
condition|)
block|{
if|if
condition|(
name|tile
operator|->
name|listhead
condition|)
block|{
comment|/* remove from cache, move to main store */
name|tile_cache_flush
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
ifdef|#
directive|ifdef
name|TILE_PROFILING
name|tile_active_count
operator|++
expr_stmt|;
endif|#
directive|endif
block|}
if|if
condition|(
name|tile
operator|->
name|data
operator|==
name|NULL
condition|)
block|{
comment|/* There is no data, so the tile must be swapped out */
name|tile_swap_in
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
comment|/* Call 'tile_manager_validate' if the tile was invalid.    */
if|if
condition|(
operator|!
name|tile
operator|->
name|valid
condition|)
block|{
comment|/* an invalid tile should never be shared, so this should work */
name|tile_manager_validate
argument_list|(
operator|(
name|TileManager
operator|*
operator|)
name|tile
operator|->
name|tlink
operator|->
name|tm
argument_list|,
name|tile
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tile_release (Tile * tile,gboolean dirty)
name|tile_release
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|gboolean
name|dirty
parameter_list|)
block|{
comment|/* Decrement the global reference count.    */
name|tile_ref_count
operator|--
expr_stmt|;
comment|/* Decrement this tile's reference count.    */
name|tile
operator|->
name|ref_count
operator|--
expr_stmt|;
comment|/* Decrement write ref count if dirtying    */
if|if
condition|(
name|dirty
condition|)
block|{
name|gint
name|y
decl_stmt|;
name|tile
operator|->
name|write_count
operator|--
expr_stmt|;
if|if
condition|(
name|tile
operator|->
name|rowhint
condition|)
block|{
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|tile
operator|->
name|eheight
condition|;
name|y
operator|++
control|)
name|tile
operator|->
name|rowhint
index|[
name|y
index|]
operator|=
name|TILEROWHINT_UNKNOWN
expr_stmt|;
block|}
block|}
if|if
condition|(
name|tile
operator|->
name|ref_count
operator|==
literal|0
condition|)
block|{
ifdef|#
directive|ifdef
name|TILE_PROFILING
name|tile_active_count
operator|--
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|tile
operator|->
name|share_count
operator|==
literal|0
condition|)
block|{
comment|/* tile is truly dead */
name|tile_destroy
argument_list|(
name|tile
argument_list|)
expr_stmt|;
return|return;
comment|/* skip terminal unlock */
block|}
else|else
block|{
comment|/* last reference was just released, so move the tile to the              tile cache */
name|tile_cache_insert
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|tile_alloc (Tile * tile)
name|tile_alloc
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
if|if
condition|(
name|tile
operator|->
name|data
condition|)
return|return;
comment|/* Allocate the data for the tile.    */
name|tile
operator|->
name|data
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|tile
operator|->
name|size
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|TILE_PROFILING
ifdef|#
directive|ifdef
name|HINTS_SANITY
name|tile_exist_count
operator|++
expr_stmt|;
if|if
condition|(
name|tile_exist_count
operator|>
name|tile_exist_peak
condition|)
name|tile_exist_peak
operator|=
name|tile_exist_count
expr_stmt|;
endif|#
directive|endif
endif|#
directive|endif
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_destroy (Tile * tile)
name|tile_destroy
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
if|if
condition|(
name|G_UNLIKELY
argument_list|(
name|tile
operator|->
name|ref_count
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"tried to destroy a ref'd tile"
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|G_UNLIKELY
argument_list|(
name|tile
operator|->
name|share_count
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"tried to destroy an attached tile"
argument_list|)
expr_stmt|;
return|return;
block|}
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
name|rowhint
condition|)
block|{
name|g_slice_free1
argument_list|(
sizeof|sizeof
argument_list|(
name|TileRowHint
argument_list|)
operator|*
name|TILE_HEIGHT
argument_list|,
name|tile
operator|->
name|rowhint
argument_list|)
expr_stmt|;
name|tile
operator|->
name|rowhint
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
name|g_slice_free
argument_list|(
name|Tile
argument_list|,
name|tile
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|TILE_PROFILING
name|tile_count
operator|--
expr_stmt|;
ifdef|#
directive|ifdef
name|HINTS_SANITY
name|tile_exist_count
operator|--
expr_stmt|;
endif|#
directive|endif
endif|#
directive|endif
block|}
end_function

begin_function
name|gint
DECL|function|tile_size (Tile * tile)
name|tile_size
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
comment|/* Return the actual size of the tile data.    *  (Based on its effective width and height).    */
return|return
name|tile
operator|->
name|size
return|;
block|}
end_function

begin_function
name|gint
DECL|function|tile_ewidth (Tile * tile)
name|tile_ewidth
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
return|return
name|tile
operator|->
name|ewidth
return|;
block|}
end_function

begin_function
name|gint
DECL|function|tile_eheight (Tile * tile)
name|tile_eheight
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
return|return
name|tile
operator|->
name|eheight
return|;
block|}
end_function

begin_function
name|gint
DECL|function|tile_bpp (Tile * tile)
name|tile_bpp
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
return|return
name|tile
operator|->
name|bpp
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|tile_is_valid (Tile * tile)
name|tile_is_valid
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
return|return
name|tile
operator|->
name|valid
return|;
block|}
end_function

begin_function
name|void
DECL|function|tile_mark_valid (Tile * tile)
name|tile_mark_valid
parameter_list|(
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
block|}
end_function

begin_function
name|void
DECL|function|tile_attach (Tile * tile,void * tm,gint tile_num)
name|tile_attach
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|void
modifier|*
name|tm
parameter_list|,
name|gint
name|tile_num
parameter_list|)
block|{
name|TileLink
modifier|*
name|tmp
decl_stmt|;
if|if
condition|(
operator|(
name|tile
operator|->
name|share_count
operator|>
literal|0
operator|)
operator|&&
operator|(
operator|!
name|tile
operator|->
name|valid
operator|)
condition|)
block|{
comment|/* trying to share invalid tiles is problematic, not to mention silly */
name|tile_manager_validate
argument_list|(
operator|(
name|TileManager
operator|*
operator|)
name|tile
operator|->
name|tlink
operator|->
name|tm
argument_list|,
name|tile
argument_list|)
expr_stmt|;
block|}
name|tile
operator|->
name|share_count
operator|++
expr_stmt|;
ifdef|#
directive|ifdef
name|TILE_PROFILING
name|tile_share_count
operator|++
expr_stmt|;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|TILE_DEBUG
name|g_printerr
argument_list|(
literal|"tile_attach: %p -> (%p,%d) *%d\n"
argument_list|,
name|tile
argument_list|,
name|tm
argument_list|,
name|tile_num
argument_list|,
name|tile
operator|->
name|share_count
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* link this tile into the tile's tilelink chain */
name|tmp
operator|=
name|g_slice_new
argument_list|(
name|TileLink
argument_list|)
expr_stmt|;
name|tmp
operator|->
name|tm
operator|=
name|tm
expr_stmt|;
name|tmp
operator|->
name|tile_num
operator|=
name|tile_num
expr_stmt|;
name|tmp
operator|->
name|next
operator|=
name|tile
operator|->
name|tlink
expr_stmt|;
name|tile
operator|->
name|tlink
operator|=
name|tmp
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tile_detach (Tile * tile,void * tm,gint tile_num)
name|tile_detach
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|void
modifier|*
name|tm
parameter_list|,
name|gint
name|tile_num
parameter_list|)
block|{
name|TileLink
modifier|*
modifier|*
name|link
decl_stmt|;
name|TileLink
modifier|*
name|tmp
decl_stmt|;
ifdef|#
directive|ifdef
name|TILE_DEBUG
name|g_printerr
argument_list|(
literal|"tile_detach: %p ~> (%p,%d) r%d *%d\n"
argument_list|,
name|tile
argument_list|,
name|tm
argument_list|,
name|tile_num
argument_list|,
name|tile
operator|->
name|ref_count
argument_list|,
name|tile
operator|->
name|share_count
argument_list|)
expr_stmt|;
endif|#
directive|endif
for|for
control|(
name|link
operator|=
operator|&
name|tile
operator|->
name|tlink
init|;
operator|*
name|link
operator|!=
name|NULL
condition|;
name|link
operator|=
operator|&
operator|(
operator|*
name|link
operator|)
operator|->
name|next
control|)
block|{
if|if
condition|(
operator|(
operator|(
operator|*
name|link
operator|)
operator|->
name|tm
operator|==
name|tm
operator|)
operator|&&
operator|(
operator|(
operator|*
name|link
operator|)
operator|->
name|tile_num
operator|==
name|tile_num
operator|)
condition|)
break|break;
block|}
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|*
name|link
operator|==
name|NULL
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"Tried to detach a nonattached tile -- TILE BUG!"
argument_list|)
expr_stmt|;
return|return;
block|}
name|tmp
operator|=
operator|*
name|link
expr_stmt|;
operator|*
name|link
operator|=
name|tmp
operator|->
name|next
expr_stmt|;
name|g_slice_free
argument_list|(
name|TileLink
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|TILE_PROFILING
name|tile_share_count
operator|--
expr_stmt|;
endif|#
directive|endif
name|tile
operator|->
name|share_count
operator|--
expr_stmt|;
if|if
condition|(
name|tile
operator|->
name|share_count
operator|==
literal|0
operator|&&
name|tile
operator|->
name|ref_count
operator|==
literal|0
condition|)
name|tile_destroy
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gpointer
DECL|function|tile_data_pointer (Tile * tile,gint xoff,gint yoff)
name|tile_data_pointer
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|gint
name|xoff
parameter_list|,
name|gint
name|yoff
parameter_list|)
block|{
name|gsize
name|offset
init|=
name|yoff
operator|*
name|tile
operator|->
name|ewidth
operator|+
name|xoff
decl_stmt|;
return|return
call|(
name|gpointer
call|)
argument_list|(
name|tile
operator|->
name|data
operator|+
name|offset
operator|*
name|tile
operator|->
name|bpp
argument_list|)
return|;
block|}
end_function

begin_function
name|gint
DECL|function|tile_global_refcount (void)
name|tile_global_refcount
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|tile_ref_count
return|;
block|}
end_function

end_unit

