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

begin_comment
comment|/*  * Define MUCH_TILE_DEBUG in addition to TILE_DEBUG to get  * debugging for every single tile_ref2 and tile_unref (that's  * a lot). #define MUCH_TILE_DEBUG heckyeah */
end_comment

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
name|real_tile_ptr
operator|=
name|NULL
expr_stmt|;
name|tile
operator|->
name|mirrored_by
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
name|tile_num
operator|=
operator|-
literal|1
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
name|tm
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

begin_function
name|void
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
operator|&&
name|defined
argument_list|(
name|__GNUC__
argument_list|)
DECL|function|_tile_ref (Tile * tile,char * func_name)
name|_tile_ref
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|char
modifier|*
name|func_name
parameter_list|)
else|#
directive|else
function|tile_ref
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
endif|#
directive|endif
block|{
comment|/* While things get moved over to the new tile_ref2    * interface, tile_ref is a wrapper which just says    * 'yes, we'll be dirtying the tile'    */
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
operator|&&
name|defined
argument_list|(
name|__GNUC__
argument_list|)
name|printf
argument_list|(
literal|"COW-Warning: function %s is using obsolete tile_ref interface\n"
argument_list|,
name|func_name
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
operator|&&
name|defined
argument_list|(
name|__GNUC__
argument_list|)
name|_tile_ref2
argument_list|(
name|tile
argument_list|,
name|TRUE
argument_list|,
name|func_name
argument_list|)
expr_stmt|;
else|#
directive|else
name|tile_ref2
argument_list|(
name|tile
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_function
name|gboolean
DECL|function|tile_is_mirroring (Tile * tile)
name|tile_is_mirroring
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
return|return
operator|(
name|tile
operator|->
name|real_tile_ptr
operator|!=
name|NULL
operator|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|tile_is_mirrored (Tile * tile)
name|tile_is_mirrored
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
return|return
operator|(
name|tile
operator|->
name|mirrored_by
operator|!=
name|NULL
operator|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|tile_is_real (Tile * tile)
name|tile_is_real
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
return|return
operator|(
name|tile
operator|->
name|real_tile_ptr
operator|==
name|NULL
operator|)
return|;
block|}
end_function

begin_comment
comment|/* Follow the real_tile_ptr links back to the tile which provides  *  the real source data for the given tile  */
end_comment

begin_function
name|Tile
modifier|*
DECL|function|tile_find_nonmirroring (Tile * tile)
name|tile_find_nonmirroring
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
if|if
condition|(
operator|!
name|tile_is_mirroring
argument_list|(
name|tile
argument_list|)
condition|)
block|{
return|return
name|tile
return|;
block|}
else|else
block|{
return|return
name|tile_find_nonmirroring
argument_list|(
name|tile
operator|->
name|real_tile_ptr
argument_list|)
return|;
block|}
block|}
end_function

begin_comment
comment|/*   */
end_comment

begin_function
name|Tile
modifier|*
DECL|function|tile_find_finalmirroring (Tile * tile)
name|tile_find_finalmirroring
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
if|if
condition|(
operator|!
name|tile_is_mirrored
argument_list|(
name|tile
argument_list|)
condition|)
block|{
return|return
name|tile
return|;
block|}
else|else
block|{
return|return
name|tile_find_finalmirroring
argument_list|(
name|tile
operator|->
name|mirrored_by
argument_list|)
return|;
block|}
block|}
end_function

begin_comment
comment|/* Take a mirroring-tile and turn it into a bona fide self-contained  *  tile.  */
end_comment

begin_function
name|void
DECL|function|tile_devirtualize (Tile * tile)
name|tile_devirtualize
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
name|Tile
modifier|*
name|real_tile
decl_stmt|;
comment|/* Sanity */
if|if
condition|(
name|tile_is_real
argument_list|(
name|tile
argument_list|)
condition|)
name|g_error
argument_list|(
literal|"Tried to devirtualize a real tile"
argument_list|)
expr_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
if|if
condition|(
name|tile
operator|->
name|ref_count
operator|==
literal|0
condition|)
name|g_warning
argument_list|(
literal|"Trying to devirtualize a mirroring-tile with no ref_count"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* Go find the tile ('real_tile') which owns the real data    */
name|real_tile
operator|=
name|tile_find_nonmirroring
argument_list|(
name|tile
argument_list|)
expr_stmt|;
comment|/* Sanity */
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
if|if
condition|(
name|real_tile
operator|->
name|ref_count
operator|==
literal|0
condition|)
name|g_warning
argument_list|(
literal|"Trying to devirtualize a mirroring-tile whose real_tile has no ref_count"
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
operator|!
name|real_tile
operator|->
name|valid
condition|)
name|g_warning
argument_list|(
literal|"Trying to devirtualize a mirroring-tile whose real_tile is !valid"
argument_list|)
expr_stmt|;
comment|/* Copy the actual tile data from the real_tile to this tile    */
name|tile
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
name|tile_alloc
argument_list|(
name|tile
argument_list|)
expr_stmt|;
comment|/*  printf ("{ %dx%d : %d  - %p[%p]->%p[%p] }", real_tile->ewidth, real_tile->eheight, 	  real_tile->bpp, real_tile, real_tile->data, tile, tile->data);   fflush(stdout);*/
name|memcpy
argument_list|(
name|tile
operator|->
name|data
argument_list|,
name|real_tile
operator|->
name|data
argument_list|,
name|tile_size
argument_list|(
name|real_tile
argument_list|)
argument_list|)
expr_stmt|;
comment|/* 'tile' is now a real tile. */
name|tile
operator|->
name|real_tile_ptr
operator|=
name|NULL
expr_stmt|;
name|tile
operator|->
name|valid
operator|=
name|TRUE
expr_stmt|;
name|tile_cache_insert
argument_list|(
name|tile
argument_list|)
expr_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
name|g_print
argument_list|(
literal|"Tile at %p is now devirtualized.\n"
argument_list|,
name|tile
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_comment
comment|/* Make this tile self-contained.    *  * The next tile in the linked-list of tiles which are mirroring 'tile'  *  is promoted to a real physical tile and unlinked from 'tile'.  This  *  renders 'tile' safe for dirtying (or destruction).  */
end_comment

begin_function
name|void
DECL|function|tile_isolate (Tile * tile)
name|tile_isolate
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
name|Tile
modifier|*
name|temp_tileptr
decl_stmt|;
comment|/* Sanity    */
if|if
condition|(
operator|!
operator|(
name|tile_is_mirrored
argument_list|(
name|tile
argument_list|)
operator|||
name|tile_is_mirroring
argument_list|(
name|tile
argument_list|)
operator|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"Tried to isolate a tile which is neither a mirror source "
literal|"nor destination"
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* This tile is both linked to and linked from? */
if|if
condition|(
name|tile_is_mirrored
argument_list|(
name|tile
argument_list|)
operator|&&
name|tile_is_mirroring
argument_list|(
name|tile
argument_list|)
condition|)
block|{
name|temp_tileptr
operator|=
name|tile
operator|->
name|real_tile_ptr
expr_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
name|g_print
argument_list|(
literal|"tile %p: was middle of chain - relinking %p and %p\n"
argument_list|,
name|tile
argument_list|,
name|temp_tileptr
argument_list|,
name|tile
operator|->
name|mirrored_by
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|tile
operator|->
name|mirrored_by
operator|->
name|real_tile_ptr
operator|=
name|temp_tileptr
expr_stmt|;
name|temp_tileptr
operator|->
name|mirrored_by
operator|=
name|tile
operator|->
name|mirrored_by
expr_stmt|;
name|tile_ref2
argument_list|(
name|temp_tileptr
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tile_devirtualize
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|tile_unref
argument_list|(
name|temp_tileptr
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tile
operator|->
name|mirrored_by
operator|=
name|NULL
expr_stmt|;
return|return;
block|}
comment|/* This tile is mirroring another, but is not mirrored itself? */
if|if
condition|(
name|tile_is_mirroring
argument_list|(
name|tile
argument_list|)
condition|)
block|{
name|temp_tileptr
operator|=
name|tile
operator|->
name|real_tile_ptr
expr_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
name|g_print
argument_list|(
literal|"tile %p: was end of chain - cauterizing %p\n"
argument_list|,
name|tile
argument_list|,
name|temp_tileptr
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* We stop mirroring the tile which we previously were -        *  so reset that tile's mirrored_by pointer.        */
name|temp_tileptr
operator|->
name|mirrored_by
operator|=
name|NULL
expr_stmt|;
name|tile_ref2
argument_list|(
name|temp_tileptr
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tile_devirtualize
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|tile_unref
argument_list|(
name|temp_tileptr
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* This tile is mirrored by another, but is not itself a mirror. */
if|if
condition|(
name|tile_is_mirrored
argument_list|(
name|tile
argument_list|)
condition|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
name|g_print
argument_list|(
literal|"tile %p: was source of chain - devirtualizing %p\n"
argument_list|,
name|tile
argument_list|,
name|tile
operator|->
name|mirrored_by
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|temp_tileptr
operator|=
name|tile
operator|->
name|mirrored_by
expr_stmt|;
name|tile_ref2
argument_list|(
name|temp_tileptr
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tile_devirtualize
argument_list|(
name|temp_tileptr
argument_list|)
expr_stmt|;
name|tile_unref
argument_list|(
name|temp_tileptr
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* The tile which was dependant on this one no longer is -        *  so we can unref once.        */
name|tile_unref
argument_list|(
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tile
operator|->
name|mirrored_by
operator|=
name|NULL
expr_stmt|;
return|return;
block|}
block|}
end_function

begin_comment
comment|/* Turns dest_tile into a mirroring-tile which mirrors the given  *  src_tile using copy-on-write.  */
end_comment

begin_function
name|void
DECL|function|tile_mirror (Tile * dest_tile,Tile * src_tile)
name|tile_mirror
parameter_list|(
name|Tile
modifier|*
name|dest_tile
parameter_list|,
name|Tile
modifier|*
name|src_tile
parameter_list|)
block|{
name|Tile
modifier|*
name|finalmirroring
decl_stmt|;
if|if
condition|(
name|dest_tile
operator|==
name|src_tile
condition|)
block|{
name|g_warning
argument_list|(
literal|"TRIED TO MIRROR TILE TO ITSELF"
argument_list|)
expr_stmt|;
return|return;
block|}
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
name|g_print
argument_list|(
literal|"mirroring "
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|tile_is_real
argument_list|(
name|dest_tile
argument_list|)
condition|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
name|g_print
argument_list|(
literal|"TO REAL "
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|tile_invalidate
argument_list|(
name|dest_tile
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tile_invalidate
argument_list|(
name|dest_tile
argument_list|)
expr_stmt|;
block|}
comment|/*      dest_tile->ref_count = 0; */
name|dest_tile
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
name|dest_tile
operator|->
name|valid
operator|=
name|FALSE
expr_stmt|;
name|dest_tile
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
name|dest_tile
operator|->
name|ewidth
operator|=
name|src_tile
operator|->
name|ewidth
expr_stmt|;
name|dest_tile
operator|->
name|eheight
operator|=
name|src_tile
operator|->
name|eheight
expr_stmt|;
name|dest_tile
operator|->
name|bpp
operator|=
name|src_tile
operator|->
name|bpp
expr_stmt|;
name|dest_tile
operator|->
name|tile_num
operator|=
operator|-
literal|1
expr_stmt|;
comment|/* ! */
comment|/*     */
name|finalmirroring
operator|=
name|tile_find_finalmirroring
argument_list|(
name|src_tile
argument_list|)
expr_stmt|;
name|dest_tile
operator|->
name|real_tile_ptr
operator|=
name|finalmirroring
expr_stmt|;
name|finalmirroring
operator|->
name|mirrored_by
operator|=
name|dest_tile
expr_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
name|g_print
argument_list|(
literal|"%p -> %p\n"
argument_list|,
name|finalmirroring
argument_list|,
name|dest_tile
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* The following should be irrelevant in a mirroring tile - mirroring    *  tiles by definition don't have real data of their own, so they can't    *  be swapped.  They don't have associated TileManagers either, since they    *  rely on their mirrored source tile to contain validated data.    */
name|dest_tile
operator|->
name|swap_num
operator|=
literal|1
expr_stmt|;
name|dest_tile
operator|->
name|swap_offset
operator|=
operator|-
literal|1
expr_stmt|;
name|dest_tile
operator|->
name|tm
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
operator|&&
name|defined
argument_list|(
name|__GNUC__
argument_list|)
DECL|function|_tile_ref2 (Tile * tile,int dirty,char * func_name)
name|_tile_ref2
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|dirty
parameter_list|,
name|char
modifier|*
name|func_name
parameter_list|)
else|#
directive|else
function|tile_ref2
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|dirty
parameter_list|)
endif|#
directive|endif
block|{
ifdef|#
directive|ifdef
name|USE_PTHREADS
name|pthread_mutex_lock
argument_list|(
operator|&
operator|(
name|tile
operator|->
name|mutex
operator|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
operator|&&
name|defined
argument_list|(
name|__GNUC__
argument_list|)
operator|&&
name|defined
argument_list|(
name|MUCH_TILE_DEBUG
argument_list|)
name|g_print
argument_list|(
literal|"tile_ref2:   %02d  %c  %p  %s\n"
argument_list|,
name|tile
operator|->
name|ref_count
argument_list|,
name|dirty
condition|?
literal|'d'
else|:
literal|' '
argument_list|,
name|tile
argument_list|,
name|func_name
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/*g_print ("tile_ref2:   %02d  %c  %p\n", tile->ref_count, 	   dirty?'d':' ', 	   tile);*/
comment|/* Increment the global reference count.    */
name|tile_ref_count
operator|+=
literal|1
expr_stmt|;
comment|/* Increment this tile's reference count.    */
name|tile
operator|->
name|ref_count
operator|+=
literal|1
expr_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
if|if
condition|(
name|tile_is_mirrored
argument_list|(
name|tile
argument_list|)
operator|&&
name|dirty
condition|)
block|{
name|g_print
argument_list|(
literal|"Dirtying a mirrored tile: %p.\n"
argument_list|,
name|tile
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
comment|/*   if (dirty&& tile->dirty)     {       g_print ("Not good: Dirtying a write-locked tile: %p.\n", tile);     } */
comment|/* if this is a read-only attachment to a mirroring tile,    *  then ref the chain, update the data pointer, and return.    */
if|if
condition|(
operator|(
operator|!
name|dirty
operator|)
operator|&&
operator|(
name|tile_is_mirroring
argument_list|(
name|tile
argument_list|)
operator|)
condition|)
block|{
comment|/* ref each of the tiles in the chain, back to the        *  'real' tile which sits at the start.        */
if|#
directive|if
name|USE_PTHREADS
name|pthread_mutex_unlock
argument_list|(
operator|&
operator|(
name|tile
operator|->
name|mutex
operator|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|tile_ref2
argument_list|(
name|tile
operator|->
name|real_tile_ptr
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tile
operator|->
name|data
operator|=
name|tile
operator|->
name|real_tile_ptr
operator|->
name|data
expr_stmt|;
return|return;
block|}
comment|/* dirty, or clean-and-real */
comment|/* Real tile - first reference. */
if|if
condition|(
operator|!
name|tile_is_mirroring
argument_list|(
name|tile
argument_list|)
condition|)
block|{
comment|/* If this is the first reference to the tile then        *  swap the tile data in from disk. Note: this will        *  properly handle the case where the tile data isn't        *  on disk.        */
if|if
condition|(
name|tile
operator|->
name|ref_count
operator|==
literal|1
condition|)
block|{
name|tile_swap_in
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
comment|/* Insert the tile into the cache. If the tile is already        *  in the cache this will have the affect of "touching"        *  the tile.        */
name|tile_cache_insert
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
comment|/* Read/write attachment to a mirrored/ing tile - must be    *  thoughtful.    */
if|if
condition|(
name|dirty
condition|)
block|{
comment|/* Doing a read/write reference to a mirroring/ed tile -        *  we'll have to turn the tile into a 'real' tile.        *  Then return - we're done.        */
block|{
if|if
condition|(
name|tile_is_mirroring
argument_list|(
name|tile
argument_list|)
operator||
name|tile_is_mirrored
argument_list|(
name|tile
argument_list|)
condition|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
name|g_print
argument_list|(
literal|"r/w to mir'd/ing - isolating: "
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|tile_isolate
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
block|}
block|}
comment|/* Mark the tile as dirty if it's being ref'd as dirtyable.    */
name|tile
operator|->
name|dirty
operator||=
name|dirty
expr_stmt|;
if|#
directive|if
name|USE_PTHREADS
name|pthread_mutex_unlock
argument_list|(
operator|&
operator|(
name|tile
operator|->
name|mutex
operator|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* Call 'tile_manager_validate' if the tile was invalid.    */
if|if
condition|(
operator|!
name|tile
operator|->
name|valid
condition|)
name|tile_manager_validate
argument_list|(
operator|(
name|TileManager
operator|*
operator|)
name|tile
operator|->
name|tm
argument_list|,
name|tile
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
operator|&&
name|defined
argument_list|(
name|__GNUC__
argument_list|)
DECL|function|_tile_unref (Tile * tile,int dirty,char * func_name)
name|_tile_unref
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|dirty
parameter_list|,
name|char
modifier|*
name|func_name
parameter_list|)
else|#
directive|else
function|tile_unref
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|dirty
parameter_list|)
endif|#
directive|endif
block|{
ifdef|#
directive|ifdef
name|USE_PTHREADS
name|pthread_mutex_lock
argument_list|(
operator|&
operator|(
name|tile
operator|->
name|mutex
operator|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
operator|&&
name|defined
argument_list|(
name|__GNUC__
argument_list|)
operator|&&
name|defined
argument_list|(
name|MUCH_TILE_DEBUG
argument_list|)
name|g_print
argument_list|(
literal|"tile_unref:  %02d  %c  %p  %s\n"
argument_list|,
name|tile
operator|->
name|ref_count
argument_list|,
name|dirty
condition|?
literal|'d'
else|:
literal|' '
argument_list|,
name|tile
argument_list|,
name|func_name
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/*    g_print ("tile_unref:  %02d  %c  %p\n", tile->ref_count, 	   dirty?'d':' ', 	   tile);*/
comment|/* Decrement the global reference count.    */
name|tile_ref_count
operator|-=
literal|1
expr_stmt|;
comment|/* Decrement this tile's reference count.    */
name|tile
operator|->
name|ref_count
operator|-=
literal|1
expr_stmt|;
comment|/* Mark the tile dirty if indicated    *    *  commented out - we now dirty on ref, not unref    */
comment|/*   tile->dirty |= dirty;   */
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
if|if
condition|(
name|tile_is_mirroring
argument_list|(
name|tile
argument_list|)
condition|)
block|{
comment|/* Mirroring tiles aren't allowed to be submitted as dirty -        * they should have been isolated at ref time.        */
if|if
condition|(
name|dirty
condition|)
name|g_warning
argument_list|(
literal|"Mirroring tile unref'd as dirty."
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|tile_is_mirrored
argument_list|(
name|tile
argument_list|)
condition|)
block|{
comment|/* Mirrored tiles aren't allowed to be submitted as dirty -        * they should have been isolated at ref time.        */
name|fflush
argument_list|(
name|stdout
argument_list|)
expr_stmt|;
if|if
condition|(
name|dirty
condition|)
name|g_warning
argument_list|(
literal|"Mirrored tile unref'd as dirty."
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
comment|/* When we unref a mirroring tile, also unref the tile which    * was being mirrored.    */
if|if
condition|(
name|tile_is_mirroring
argument_list|(
name|tile
argument_list|)
condition|)
block|{
comment|/* Mirroring tiles aren't allowed to be submitted as dirty -        * they should have been ref'd as dirty in the first place so we        * could turn them into 'real' tiles.        */
if|if
condition|(
name|dirty
condition|)
block|{
name|g_warning
argument_list|(
literal|"Bleh, tried to unref a mirroring tile as dirty."
argument_list|)
expr_stmt|;
block|}
comment|/* Go find the mirrored tile and unref that too. */
if|#
directive|if
name|USE_PTHREADS
name|pthread_mutex_unlock
argument_list|(
operator|&
operator|(
name|tile
operator|->
name|mutex
operator|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|tile_unref
argument_list|(
name|tile
operator|->
name|real_tile_ptr
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* If this was the last reference to the tile, then    *  swap it out to disk.    */
if|if
condition|(
name|tile
operator|->
name|ref_count
operator|==
literal|0
condition|)
block|{
comment|/*  Only need to swap out in two cases:        *   1)  The tile is dirty               }        *   2)  The tile has never been swapped }  and is not mirroring        */
if|if
condition|(
operator|(
name|tile
operator|->
name|dirty
operator|||
name|tile
operator|->
name|swap_offset
operator|==
operator|-
literal|1
operator|)
operator|&&
operator|!
name|tile_is_mirroring
argument_list|(
name|tile
argument_list|)
condition|)
name|tile_swap_out
argument_list|(
name|tile
argument_list|)
expr_stmt|;
comment|/*  Otherwise, just throw out the data--the same stuff is in swap        */
else|else
block|{
if|if
condition|(
operator|!
name|tile_is_mirroring
argument_list|(
name|tile
argument_list|)
condition|)
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
block|}
if|#
directive|if
name|USE_PTHREADS
name|pthread_mutex_unlock
argument_list|(
operator|&
operator|(
name|tile
operator|->
name|mutex
operator|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
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
goto|goto
name|out
goto|;
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
name|out
label|:
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
name|void
DECL|function|tile_invalidate (Tile * tile)
name|tile_invalidate
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|USE_PTHREADS
name|pthread_mutex_lock
argument_list|(
operator|&
operator|(
name|tile
operator|->
name|mutex
operator|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
if|if
condition|(
name|tile
operator|->
name|ref_count
operator|>
literal|1
condition|)
block|{
name|g_print
argument_list|(
literal|" (inv%p:ref%d) "
argument_list|,
name|tile
argument_list|,
name|tile
operator|->
name|ref_count
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_print
argument_list|(
literal|" (inv%p) "
argument_list|,
name|tile
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
comment|/* If this tile is mirrored/ing, then maybe isolate it before we    *  invalidate it, so that we don't accidentally delete a tile    *  whose data is still in use by a mirror.    */
if|if
condition|(
name|tile_is_mirrored
argument_list|(
name|tile
argument_list|)
condition|)
block|{
if|if
condition|(
name|tile_is_mirroring
argument_list|(
name|tile
argument_list|)
condition|)
block|{
comment|/* tile is in the middle of a chain.  just relink its 	   *  successor and predecessor.  that's all we need to do for 	   *  a cleanup. 	   */
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
name|g_print
argument_list|(
literal|"tile %p: was middle of chain - relinking %p and %p, "
literal|"no isolation\n"
argument_list|,
name|tile
argument_list|,
name|tile
operator|->
name|real_tile_ptr
argument_list|,
name|tile
operator|->
name|mirrored_by
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|tile
operator|->
name|mirrored_by
operator|->
name|real_tile_ptr
operator|=
name|tile
operator|->
name|real_tile_ptr
expr_stmt|;
name|tile
operator|->
name|real_tile_ptr
operator|->
name|mirrored_by
operator|=
name|tile
operator|->
name|mirrored_by
expr_stmt|;
block|}
else|else
block|{
comment|/* tile is real, and mirrored.  Copy its vital statistics to 	   *  its successor in the tile chain, so it can be safely deleted. 	   */
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
name|g_print
argument_list|(
literal|"tile %p: was source of chain - successor %p swallows soul"
literal|", no isolation\n"
argument_list|,
name|tile
argument_list|,
name|tile
operator|->
name|mirrored_by
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* remove 'tile' from cache - but keep the ref_count up 	   *  so that the tile_unref() which tile_cache_flush() calls 	   *  won't invalidate the tile (we'll be doing that ourselves). 	   */
name|tile
operator|->
name|ref_count
operator|++
expr_stmt|;
name|tile_cache_flush
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|tile
operator|->
name|ref_count
operator|--
expr_stmt|;
comment|/* imbue our successor with our data pointer, validity, 	   *  tile manager, swap_num, swap_offset, and dirty 	   *  flag 	   */
name|tile
operator|->
name|mirrored_by
operator|->
name|data
operator|=
name|tile
operator|->
name|data
expr_stmt|;
name|tile
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
name|tile
operator|->
name|mirrored_by
operator|->
name|dirty
operator|=
name|tile
operator|->
name|dirty
expr_stmt|;
name|tile
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
name|tile
operator|->
name|mirrored_by
operator|->
name|valid
operator|=
name|tile
operator|->
name|valid
expr_stmt|;
name|tile
operator|->
name|valid
operator|=
name|FALSE
expr_stmt|;
name|tile
operator|->
name|mirrored_by
operator|->
name|swap_num
operator|=
name|tile
operator|->
name|swap_num
expr_stmt|;
name|tile
operator|->
name|swap_num
operator|=
literal|0
expr_stmt|;
name|tile
operator|->
name|mirrored_by
operator|->
name|swap_offset
operator|=
name|tile
operator|->
name|swap_offset
expr_stmt|;
name|tile
operator|->
name|swap_num
operator|=
operator|-
literal|1
expr_stmt|;
name|tile
operator|->
name|mirrored_by
operator|->
name|tm
operator|=
name|tile
operator|->
name|tm
expr_stmt|;
name|tile
operator|->
name|tm
operator|=
name|NULL
expr_stmt|;
comment|/* sever links with our successor in both directions. 	   *  our successor is now the new chain source. 	   * 	   * also register this newly-born 'real' tile with the tile cache. 	   */
name|tile
operator|->
name|mirrored_by
operator|->
name|real_tile_ptr
operator|=
name|NULL
expr_stmt|;
name|tile_cache_insert
argument_list|(
name|tile
operator|->
name|mirrored_by
argument_list|)
expr_stmt|;
name|tile
operator|->
name|mirrored_by
operator|=
name|NULL
expr_stmt|;
comment|/* This tile is as clean and invalid as it's going to get. 	   *  Return. 	   */
return|return;
block|}
block|}
else|else
comment|/* not mirrored, maybe mirroring */
block|{
comment|/* for a non-real tile at the end of a chain, the only cleanup        *  we have to do for its safe destruction is cauterize the        *  flapping mirrored_by pointer of its predecessor on the chain.        */
if|if
condition|(
name|tile_is_mirroring
argument_list|(
name|tile
argument_list|)
condition|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|TILE_DEBUG
argument_list|)
name|g_print
argument_list|(
literal|"tile %p: was end of chain - cauterizing %p, no "
literal|"isolation\n"
argument_list|,
name|tile
argument_list|,
name|tile
operator|->
name|real_tile_ptr
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|tile
operator|->
name|real_tile_ptr
operator|->
name|mirrored_by
operator|=
name|NULL
expr_stmt|;
block|}
block|}
comment|/* If this isn't a 'real' tile then it doesn't need invalidating,    *  since it doesn't have any unique data associated with it.    */
if|if
condition|(
operator|!
name|tile_is_real
argument_list|(
name|tile
argument_list|)
condition|)
block|{
if|if
condition|(
name|tile
operator|->
name|valid
condition|)
block|{
name|g_warning
argument_list|(
literal|"tried to invalidate a mirroring tile which was valid."
argument_list|)
expr_stmt|;
name|tile
operator|->
name|valid
operator|=
name|FALSE
expr_stmt|;
block|}
return|return;
block|}
comment|/* Only 'real' tiles permitted past this point.    */
comment|/* Invalidate the tile. (Must be valid first).    */
if|if
condition|(
name|tile
operator|->
name|valid
condition|)
block|{
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
comment|/* If the tile is in memory then trick the 	   *  tile cache routines. We temporarily increment 	   *  the reference count so that flushing a tile does 	   *  not cause it to go out to disk. 	   */
name|tile
operator|->
name|ref_count
operator|+=
literal|1
expr_stmt|;
name|tile_cache_flush
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|tile
operator|->
name|ref_count
operator|-=
literal|1
expr_stmt|;
comment|/* We then free the tile data. 	   */
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
comment|/* If the tile is on disk, then delete its 	   *  presence there. 	   */
name|tile_swap_delete
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
block|}
if|#
directive|if
name|USE_PTHREADS
name|pthread_mutex_unlock
argument_list|(
operator|&
operator|(
name|tile
operator|->
name|mutex
operator|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

end_unit

