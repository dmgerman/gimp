begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|USE_PTHREADS
end_ifdef

begin_include
include|#
directive|include
file|<pthread.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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
file|"config/gimpbaseconfig.h"
end_include

begin_include
include|#
directive|include
file|"tile.h"
end_include

begin_include
include|#
directive|include
file|"tile-cache.h"
end_include

begin_include
include|#
directive|include
file|"tile-swap.h"
end_include

begin_include
include|#
directive|include
file|"tile-private.h"
end_include

begin_comment
comment|/*  This is the percentage of the maximum cache size that should be cleared  *   from the cache when an eviction is necessary  */
end_comment

begin_define
DECL|macro|FREE_QUANTUM
define|#
directive|define
name|FREE_QUANTUM
value|0.1
end_define

begin_define
DECL|macro|IDLE_SWAPPER_TIMEOUT
define|#
directive|define
name|IDLE_SWAPPER_TIMEOUT
value|250
end_define

begin_function_decl
specifier|static
name|void
name|tile_cache_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|tile_cache_zorch_next
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tile_cache_flush_internal
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|USE_PTHREADS
end_ifdef

begin_function_decl
specifier|static
name|gpointer
name|tile_idle_thread
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_function_decl
specifier|static
name|gboolean
name|tile_idle_preswap
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|initialize
specifier|static
name|gboolean
name|initialize
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|struct|_TileList
typedef|typedef
struct|struct
name|_TileList
block|{
DECL|member|first
name|Tile
modifier|*
name|first
decl_stmt|;
DECL|member|last
name|Tile
modifier|*
name|last
decl_stmt|;
DECL|typedef|TileList
block|}
name|TileList
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|max_tile_size
specifier|static
name|gulong
name|max_tile_size
init|=
name|TILE_WIDTH
operator|*
name|TILE_HEIGHT
operator|*
literal|4
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cur_cache_size
specifier|static
name|gulong
name|cur_cache_size
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|max_cache_size
specifier|static
name|gulong
name|max_cache_size
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cur_cache_dirty
specifier|static
name|gulong
name|cur_cache_dirty
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|clean_list
specifier|static
name|TileList
name|clean_list
init|=
block|{
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dirty_list
specifier|static
name|TileList
name|dirty_list
init|=
block|{
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_ifdef
ifdef|#
directive|ifdef
name|USE_PTHREADS
end_ifdef

begin_decl_stmt
DECL|variable|preswap_thread
specifier|static
name|pthread_t
name|preswap_thread
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dirty_mutex
specifier|static
name|pthread_mutex_t
name|dirty_mutex
init|=
name|PTHREAD_MUTEX_INITIALIZER
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dirty_signal
specifier|static
name|pthread_cond_t
name|dirty_signal
init|=
name|PTHREAD_COND_INITIALIZER
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tile_mutex
specifier|static
name|pthread_mutex_t
name|tile_mutex
init|=
name|PTHREAD_MUTEX_INITIALIZER
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|CACHE_LOCK
define|#
directive|define
name|CACHE_LOCK
value|pthread_mutex_lock(&tile_mutex)
end_define

begin_define
DECL|macro|CACHE_UNLOCK
define|#
directive|define
name|CACHE_UNLOCK
value|pthread_mutex_unlock(&tile_mutex)
end_define

begin_else
else|#
directive|else
end_else

begin_decl_stmt
DECL|variable|idle_swapper
specifier|static
name|guint
name|idle_swapper
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|CACHE_LOCK
define|#
directive|define
name|CACHE_LOCK
end_define

begin_comment
DECL|macro|CACHE_LOCK
comment|/* nothing */
end_comment

begin_define
DECL|macro|CACHE_UNLOCK
define|#
directive|define
name|CACHE_UNLOCK
end_define

begin_comment
DECL|macro|CACHE_UNLOCK
comment|/* nothing */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|void
DECL|function|tile_cache_insert (Tile * tile)
name|tile_cache_insert
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
name|TileList
modifier|*
name|list
decl_stmt|;
name|TileList
modifier|*
name|newlist
decl_stmt|;
if|if
condition|(
name|initialize
condition|)
name|tile_cache_init
argument_list|()
expr_stmt|;
name|CACHE_LOCK
expr_stmt|;
if|if
condition|(
name|tile
operator|->
name|data
operator|==
name|NULL
condition|)
goto|goto
name|out
goto|;
comment|/* First check and see if the tile is already    *  in the cache. In that case we will simply place    *  it at the end of the tile list to indicate that    *  it was the most recently accessed tile.    */
name|list
operator|=
operator|(
name|TileList
operator|*
operator|)
name|tile
operator|->
name|listhead
expr_stmt|;
name|newlist
operator|=
operator|(
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
condition|?
operator|&
name|dirty_list
else|:
operator|&
name|clean_list
operator|)
expr_stmt|;
comment|/* if list is NULL, the tile is not in the cache */
if|if
condition|(
name|list
condition|)
block|{
comment|/* Tile is in the cache.  Remove it from its current list and 	 put it at the tail of the proper list (clean or dirty) */
if|if
condition|(
name|tile
operator|->
name|next
condition|)
name|tile
operator|->
name|next
operator|->
name|prev
operator|=
name|tile
operator|->
name|prev
expr_stmt|;
else|else
name|list
operator|->
name|last
operator|=
name|tile
operator|->
name|prev
expr_stmt|;
if|if
condition|(
name|tile
operator|->
name|prev
condition|)
name|tile
operator|->
name|prev
operator|->
name|next
operator|=
name|tile
operator|->
name|next
expr_stmt|;
else|else
name|list
operator|->
name|first
operator|=
name|tile
operator|->
name|next
expr_stmt|;
name|tile
operator|->
name|listhead
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|list
operator|==
operator|&
name|dirty_list
condition|)
name|cur_cache_dirty
operator|-=
name|tile_size
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* The tile was not in the cache. First check and see        *  if there is room in the cache. If not then we'll have        *  to make room first. Note: it might be the case that the        *  cache is smaller than the size of a tile in which case        *  it won't be possible to put it in the cache.        */
while|while
condition|(
operator|(
name|cur_cache_size
operator|+
name|max_tile_size
operator|)
operator|>
name|max_cache_size
condition|)
block|{
if|if
condition|(
operator|!
name|tile_cache_zorch_next
argument_list|()
condition|)
block|{
name|g_warning
argument_list|(
literal|"cache: unable to find room for a tile"
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
comment|/* goto grump;*/
block|}
block|}
comment|/*grump:*/
comment|/* Note the increase in the number of bytes the cache        *  is referencing.        */
name|cur_cache_size
operator|+=
name|tile_size
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
comment|/* Put the tile at the end of the proper list */
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
name|newlist
operator|->
name|last
expr_stmt|;
name|tile
operator|->
name|listhead
operator|=
name|newlist
expr_stmt|;
if|if
condition|(
name|newlist
operator|->
name|last
condition|)
name|newlist
operator|->
name|last
operator|->
name|next
operator|=
name|tile
expr_stmt|;
else|else
name|newlist
operator|->
name|first
operator|=
name|tile
expr_stmt|;
name|newlist
operator|->
name|last
operator|=
name|tile
expr_stmt|;
comment|/* gosgood@idt.net 1999-12-04                                  */
comment|/* bytes on cur_cache_dirty miscounted in CVS 1.12:            */
comment|/* Invariant: test for selecting dirty list should be the same */
comment|/* as counting files dirty.                                    */
if|if
condition|(
name|tile
operator|->
name|dirty
operator|||
operator|(
name|tile
operator|->
name|swap_offset
operator|==
operator|-
literal|1
operator|)
condition|)
block|{
name|cur_cache_dirty
operator|+=
name|tile_size
argument_list|(
name|tile
argument_list|)
expr_stmt|;
if|if
condition|(
literal|1
condition|)
block|{
ifdef|#
directive|ifdef
name|USE_PTHREADS
name|pthread_mutex_lock
argument_list|(
operator|&
name|dirty_mutex
argument_list|)
expr_stmt|;
name|pthread_cond_signal
argument_list|(
operator|&
name|dirty_signal
argument_list|)
expr_stmt|;
name|pthread_mutex_unlock
argument_list|(
operator|&
name|dirty_mutex
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
block|}
name|out
label|:
name|CACHE_UNLOCK
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tile_cache_flush (Tile * tile)
name|tile_cache_flush
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
if|if
condition|(
name|initialize
condition|)
name|tile_cache_init
argument_list|()
expr_stmt|;
name|CACHE_LOCK
expr_stmt|;
name|tile_cache_flush_internal
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|CACHE_UNLOCK
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_cache_flush_internal (Tile * tile)
name|tile_cache_flush_internal
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
name|TileList
modifier|*
name|list
decl_stmt|;
comment|/* Find where the tile is in the cache.    */
name|list
operator|=
operator|(
name|TileList
operator|*
operator|)
name|tile
operator|->
name|listhead
expr_stmt|;
if|if
condition|(
name|list
condition|)
block|{
comment|/* Note the decrease in the number of bytes the cache        *  is referencing.        */
name|cur_cache_size
operator|-=
name|tile_size
argument_list|(
name|tile
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|==
operator|&
name|dirty_list
condition|)
name|cur_cache_dirty
operator|-=
name|tile_size
argument_list|(
name|tile
argument_list|)
expr_stmt|;
if|if
condition|(
name|tile
operator|->
name|next
condition|)
name|tile
operator|->
name|next
operator|->
name|prev
operator|=
name|tile
operator|->
name|prev
expr_stmt|;
else|else
name|list
operator|->
name|last
operator|=
name|tile
operator|->
name|prev
expr_stmt|;
if|if
condition|(
name|tile
operator|->
name|prev
condition|)
name|tile
operator|->
name|prev
operator|->
name|next
operator|=
name|tile
operator|->
name|next
expr_stmt|;
else|else
name|list
operator|->
name|first
operator|=
name|tile
operator|->
name|next
expr_stmt|;
name|tile
operator|->
name|listhead
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* untested -- ADM */
end_comment

begin_function
name|void
DECL|function|tile_cache_set_size (gulong cache_size)
name|tile_cache_set_size
parameter_list|(
name|gulong
name|cache_size
parameter_list|)
block|{
if|if
condition|(
name|initialize
condition|)
name|tile_cache_init
argument_list|()
expr_stmt|;
name|max_cache_size
operator|=
name|cache_size
expr_stmt|;
name|CACHE_LOCK
expr_stmt|;
while|while
condition|(
name|cur_cache_size
operator|>
name|max_cache_size
condition|)
block|{
if|if
condition|(
operator|!
name|tile_cache_zorch_next
argument_list|()
condition|)
break|break;
block|}
name|CACHE_UNLOCK
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_cache_init (void)
name|tile_cache_init
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|initialize
condition|)
block|{
name|initialize
operator|=
name|FALSE
expr_stmt|;
name|clean_list
operator|.
name|first
operator|=
name|clean_list
operator|.
name|last
operator|=
name|NULL
expr_stmt|;
name|dirty_list
operator|.
name|first
operator|=
name|dirty_list
operator|.
name|last
operator|=
name|NULL
expr_stmt|;
name|max_cache_size
operator|=
name|base_config
operator|->
name|tile_cache_size
expr_stmt|;
ifdef|#
directive|ifdef
name|USE_PTHREADS
name|pthread_create
argument_list|(
operator|&
name|preswap_thread
argument_list|,
name|NULL
argument_list|,
operator|&
name|tile_idle_thread
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|#
directive|else
name|idle_swapper
operator|=
name|g_timeout_add
argument_list|(
name|IDLE_SWAPPER_TIMEOUT
argument_list|,
name|tile_idle_preswap
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|tile_cache_zorch_next (void)
name|tile_cache_zorch_next
parameter_list|(
name|void
parameter_list|)
block|{
name|Tile
modifier|*
name|tile
decl_stmt|;
if|if
condition|(
name|clean_list
operator|.
name|first
condition|)
name|tile
operator|=
name|clean_list
operator|.
name|first
expr_stmt|;
elseif|else
if|if
condition|(
name|dirty_list
operator|.
name|first
condition|)
name|tile
operator|=
name|dirty_list
operator|.
name|first
expr_stmt|;
else|else
return|return
name|FALSE
return|;
name|CACHE_UNLOCK
expr_stmt|;
name|TILE_MUTEX_LOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|CACHE_LOCK
expr_stmt|;
name|tile_cache_flush_internal
argument_list|(
name|tile
argument_list|)
expr_stmt|;
if|if
condition|(
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
condition|)
block|{
name|tile_swap_out
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|tile
operator|->
name|dirty
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
name|TILE_MUTEX_UNLOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
comment|/* unable to swap out tile for some reason */
name|TILE_MUTEX_UNLOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_if
if|#
directive|if
name|USE_PTHREADS
end_if

begin_function
specifier|static
name|gpointer
DECL|function|tile_idle_thread (gpointer data)
name|tile_idle_thread
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|Tile
modifier|*
name|tile
decl_stmt|;
name|TileList
modifier|*
name|list
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|g_printerr
argument_list|(
literal|"starting tile preswapper\n"
argument_list|)
expr_stmt|;
name|count
operator|=
literal|0
expr_stmt|;
while|while
condition|(
name|TRUE
condition|)
block|{
name|CACHE_LOCK
expr_stmt|;
if|if
condition|(
name|count
operator|>
literal|5
operator|||
name|dirty_list
operator|.
name|first
operator|==
name|NULL
condition|)
block|{
name|CACHE_UNLOCK
expr_stmt|;
name|count
operator|=
literal|0
expr_stmt|;
name|pthread_mutex_lock
argument_list|(
operator|&
name|dirty_mutex
argument_list|)
expr_stmt|;
name|pthread_cond_wait
argument_list|(
operator|&
name|dirty_signal
argument_list|,
operator|&
name|dirty_mutex
argument_list|)
expr_stmt|;
name|pthread_mutex_unlock
argument_list|(
operator|&
name|dirty_mutex
argument_list|)
expr_stmt|;
name|CACHE_LOCK
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|tile
operator|=
name|dirty_list
operator|.
name|first
operator|)
condition|)
block|{
name|CACHE_UNLOCK
expr_stmt|;
name|TILE_MUTEX_LOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|CACHE_LOCK
expr_stmt|;
if|if
condition|(
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
condition|)
block|{
name|list
operator|=
name|tile
operator|->
name|listhead
expr_stmt|;
if|if
condition|(
name|list
operator|==
operator|&
name|dirty_list
condition|)
name|cur_cache_dirty
operator|-=
name|tile_size
argument_list|(
name|tile
argument_list|)
expr_stmt|;
if|if
condition|(
name|tile
operator|->
name|next
condition|)
name|tile
operator|->
name|next
operator|->
name|prev
operator|=
name|tile
operator|->
name|prev
expr_stmt|;
else|else
name|list
operator|->
name|last
operator|=
name|tile
operator|->
name|prev
expr_stmt|;
if|if
condition|(
name|tile
operator|->
name|prev
condition|)
name|tile
operator|->
name|prev
operator|->
name|next
operator|=
name|tile
operator|->
name|next
expr_stmt|;
else|else
name|list
operator|->
name|first
operator|=
name|tile
operator|->
name|next
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
name|clean_list
operator|.
name|last
expr_stmt|;
name|tile
operator|->
name|listhead
operator|=
operator|&
name|clean_list
expr_stmt|;
if|if
condition|(
name|clean_list
operator|.
name|last
condition|)
name|clean_list
operator|.
name|last
operator|->
name|next
operator|=
name|tile
expr_stmt|;
else|else
name|clean_list
operator|.
name|first
operator|=
name|tile
expr_stmt|;
name|clean_list
operator|.
name|last
operator|=
name|tile
expr_stmt|;
name|CACHE_UNLOCK
expr_stmt|;
name|tile_swap_out
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|CACHE_UNLOCK
expr_stmt|;
block|}
name|TILE_MUTEX_UNLOCK
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|CACHE_UNLOCK
expr_stmt|;
block|}
name|count
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* !USE_PTHREADS */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|tile_idle_preswap (gpointer data)
name|tile_idle_preswap
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|Tile
modifier|*
name|tile
decl_stmt|;
if|if
condition|(
name|cur_cache_dirty
operator|*
literal|2
operator|<
name|max_cache_size
condition|)
return|return
name|TRUE
return|;
if|if
condition|(
operator|(
name|tile
operator|=
name|dirty_list
operator|.
name|first
operator|)
condition|)
block|{
name|tile_swap_out
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|dirty_list
operator|.
name|first
operator|=
name|tile
operator|->
name|next
expr_stmt|;
if|if
condition|(
name|tile
operator|->
name|next
condition|)
name|tile
operator|->
name|next
operator|->
name|prev
operator|=
name|NULL
expr_stmt|;
else|else
name|dirty_list
operator|.
name|last
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
name|clean_list
operator|.
name|last
expr_stmt|;
name|tile
operator|->
name|listhead
operator|=
operator|&
name|clean_list
expr_stmt|;
if|if
condition|(
name|clean_list
operator|.
name|last
condition|)
name|clean_list
operator|.
name|last
operator|->
name|next
operator|=
name|tile
expr_stmt|;
else|else
name|clean_list
operator|.
name|first
operator|=
name|tile
expr_stmt|;
name|clean_list
operator|.
name|last
operator|=
name|tile
expr_stmt|;
name|cur_cache_dirty
operator|-=
name|tile_size
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

