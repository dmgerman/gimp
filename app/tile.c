begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"tile.h"
end_include

begin_include
include|#
directive|include
file|"tile_pvt.h"
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

begin_comment
comment|/* EXPERIMENTAL Copy-On-Write goodies  *  by Adam D. Moss  *   adam@gimp.org  *   adam@foxbox.org  *  *  * C.O.W. Revisions:  *  *   97.10.05 - Initial release  *   97.10.06 - Much faster tile invalidation +  *              Better swap interaction (should no longer  *                crash GIMP when GIMP swapfile is full).  *   97.10.18 - Very stable now, and even more efficient.  *   98.06.16 - Revised from GIMP 0.99.14 for 1.[01].0 - no  *                longer so sure about stability until  *                more comprehensive testing is done.  *  *  * MISC TODO:  *  *  tile_invalidate: (tile_manager) - don't let a tile become  *   invalidated if its ref-count>1, but move it to a delete-on-last-unref  *   list instead...  */
end_comment

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

begin_decl_stmt
DECL|variable|tile_count
name|int
name|tile_count
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|tile_init (Tile * tile,int bpp)
name|tile_init
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|bpp
parameter_list|)
block|{
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
ifdef|#
directive|ifdef
name|USE_PTHREADS
block|{
name|pthread_mutex_init
argument_list|(
operator|&
name|tile
operator|->
name|mutex
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|tile_count
operator|++
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_decl_stmt
DECL|variable|tile_ref_count
name|int
name|tile_ref_count
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tile_share_count
name|int
name|tile_share_count
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tile_active_count
name|int
name|tile_active_count
init|=
literal|0
decl_stmt|;
end_decl_stmt

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
operator|+=
literal|1
expr_stmt|;
comment|/* Increment this tile's reference count.    */
name|TILE_MUTEX_LOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|tile
operator|->
name|ref_count
operator|+=
literal|1
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
name|tile_active_count
operator|++
expr_stmt|;
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
name|TILE_MUTEX_UNLOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
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
DECL|function|tile_release (Tile * tile,int dirty)
name|tile_release
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|dirty
parameter_list|)
block|{
comment|/* Decrement the global reference count.    */
name|tile_ref_count
operator|-=
literal|1
expr_stmt|;
name|TILE_MUTEX_LOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
comment|/* Decrement this tile's reference count.    */
name|tile
operator|->
name|ref_count
operator|-=
literal|1
expr_stmt|;
comment|/* Decrement write ref count if dirtying    */
if|if
condition|(
name|dirty
condition|)
name|tile
operator|->
name|write_count
operator|-=
literal|1
expr_stmt|;
if|if
condition|(
name|tile
operator|->
name|ref_count
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|tile
operator|->
name|share_count
operator|==
literal|0
condition|)
block|{
comment|/* tile is dead */
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
comment|/* last reference was just released, so move the tile to the 	     tile cache */
name|tile_cache_insert
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
name|tile_active_count
operator|--
expr_stmt|;
block|}
name|TILE_MUTEX_UNLOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
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
name|tile_size
argument_list|(
name|tile
argument_list|)
argument_list|)
expr_stmt|;
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
name|tile
operator|->
name|ref_count
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
name|tile
operator|->
name|share_count
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
name|TILE_MUTEX_UNLOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|tile_count
operator|--
expr_stmt|;
block|}
end_function

begin_function
name|int
DECL|function|tile_size (Tile * tile)
name|tile_size
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
name|int
name|size
decl_stmt|;
comment|/* Return the actual size of the tile data.    *  (Based on its effective width and height).    */
name|size
operator|=
name|tile
operator|->
name|ewidth
operator|*
name|tile
operator|->
name|eheight
operator|*
name|tile
operator|->
name|bpp
expr_stmt|;
return|return
name|size
return|;
block|}
end_function

begin_function
name|int
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
name|int
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
name|int
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
name|int
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
name|TILE_MUTEX_LOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|tile
operator|->
name|valid
operator|=
name|TRUE
expr_stmt|;
name|TILE_MUTEX_UNLOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tile_attach (Tile * tile,void * tm,int tile_num)
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
name|int
name|tile_num
parameter_list|)
block|{
name|TileLink
modifier|*
name|tmp
decl_stmt|;
if|if
condition|(
name|tile
operator|->
name|share_count
operator|>
literal|0
operator|&&
operator|!
name|tile
operator|->
name|valid
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
name|tile_share_count
operator|++
expr_stmt|;
ifdef|#
directive|ifdef
name|TILE_DEBUG
name|g_print
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
name|g_new
argument_list|(
name|TileLink
argument_list|,
literal|1
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
DECL|function|tile_detach (Tile * tile,void * tm,int tile_num)
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
name|int
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
name|g_print
argument_list|(
literal|"tile_detach: %p ~> (%p,%d) *%d\n"
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
if|if
condition|(
operator|(
operator|*
name|link
operator|)
operator|->
name|tm
operator|==
name|tm
operator|&&
operator|(
operator|*
name|link
operator|)
operator|->
name|tile_num
operator|==
name|tile_num
condition|)
break|break;
if|if
condition|(
operator|*
name|link
operator|==
name|NULL
condition|)
block|{
name|g_warning
argument_list|(
literal|"Tried to detach a nonattached tile"
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
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
name|tile_share_count
operator|--
expr_stmt|;
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
block|{
name|tile_destroy
argument_list|(
name|tile
argument_list|)
expr_stmt|;
return|return;
block|}
name|TILE_MUTEX_UNLOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
modifier|*
DECL|function|tile_data_pointer (Tile * tile,int xoff,int yoff)
name|tile_data_pointer
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|xoff
parameter_list|,
name|int
name|yoff
parameter_list|)
block|{
name|int
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
operator|(
name|void
operator|*
operator|)
operator|(
name|tile
operator|->
name|data
operator|+
name|offset
operator|*
name|tile
operator|->
name|bpp
operator|)
return|;
block|}
end_function

end_unit

