begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimptile.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpprotocol.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpwire.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/*  This is the percentage of the maximum cache size that   *  should be cleared from the cache when an eviction is   *  necessary.  */
end_comment

begin_define
DECL|macro|FREE_QUANTUM
define|#
directive|define
name|FREE_QUANTUM
value|0.1
end_define

begin_function_decl
name|void
name|gimp_read_expect_msg
parameter_list|(
name|WireMessage
modifier|*
name|msg
parameter_list|,
name|gint
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_get
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_put
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_cache_insert
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_cache_flush
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_cache_zorch
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|guint
name|gimp_tile_hash
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|_gimp_tile_width
name|gint
name|_gimp_tile_width
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|_gimp_tile_height
name|gint
name|_gimp_tile_height
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tile_hash_table
specifier|static
name|GHashTable
modifier|*
name|tile_hash_table
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tile_list_head
specifier|static
name|GList
modifier|*
name|tile_list_head
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tile_list_tail
specifier|static
name|GList
modifier|*
name|tile_list_tail
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|max_tile_size
specifier|static
name|gulong
name|max_tile_size
init|=
literal|0
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

begin_function
name|void
DECL|function|gimp_tile_ref (GimpTile * tile)
name|gimp_tile_ref
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
block|{
if|if
condition|(
name|tile
condition|)
block|{
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
name|gimp_tile_get
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|tile
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
block|}
name|gimp_tile_cache_insert
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_tile_ref_zero (GimpTile * tile)
name|gimp_tile_ref_zero
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
block|{
if|if
condition|(
name|tile
condition|)
block|{
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
name|ewidth
operator|*
name|tile
operator|->
name|eheight
operator|*
name|tile
operator|->
name|bpp
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|tile
operator|->
name|data
argument_list|,
literal|0
argument_list|,
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
argument_list|)
expr_stmt|;
block|}
name|gimp_tile_cache_insert
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_tile_unref (GimpTile * tile,gboolean dirty)
name|gimp_tile_unref
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|,
name|gboolean
name|dirty
parameter_list|)
block|{
if|if
condition|(
name|tile
condition|)
block|{
name|tile
operator|->
name|ref_count
operator|-=
literal|1
expr_stmt|;
name|tile
operator|->
name|dirty
operator||=
name|dirty
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
name|gimp_tile_flush
argument_list|(
name|tile
argument_list|)
expr_stmt|;
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
block|}
end_function

begin_function
name|void
DECL|function|gimp_tile_flush (GimpTile * tile)
name|gimp_tile_flush
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
block|{
if|if
condition|(
name|tile
operator|&&
name|tile
operator|->
name|data
operator|&&
name|tile
operator|->
name|dirty
condition|)
block|{
name|gimp_tile_put
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|tile
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_tile_cache_size (gulong kilobytes)
name|gimp_tile_cache_size
parameter_list|(
name|gulong
name|kilobytes
parameter_list|)
block|{
name|max_cache_size
operator|=
name|kilobytes
operator|*
literal|1024
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tile_cache_ntiles (gulong ntiles)
name|gimp_tile_cache_ntiles
parameter_list|(
name|gulong
name|ntiles
parameter_list|)
block|{
name|gimp_tile_cache_size
argument_list|(
call|(
name|gulong
call|)
argument_list|(
name|ntiles
operator|*
name|_gimp_tile_width
operator|*
name|_gimp_tile_height
operator|*
literal|4
operator|+
literal|1023
argument_list|)
operator|/
literal|1024
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|guint
DECL|function|gimp_tile_width (void)
name|gimp_tile_width
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|_gimp_tile_width
return|;
block|}
end_function

begin_function
name|guint
DECL|function|gimp_tile_height (void)
name|gimp_tile_height
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|_gimp_tile_height
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_get (GimpTile * tile)
name|gimp_tile_get
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
block|{
specifier|extern
name|GIOChannel
modifier|*
name|_writechannel
decl_stmt|;
specifier|extern
name|guchar
modifier|*
name|_shm_addr
decl_stmt|;
name|GPTileReq
name|tile_req
decl_stmt|;
name|GPTileData
modifier|*
name|tile_data
decl_stmt|;
name|WireMessage
name|msg
decl_stmt|;
name|tile_req
operator|.
name|drawable_ID
operator|=
name|tile
operator|->
name|drawable
operator|->
name|drawable_id
expr_stmt|;
name|tile_req
operator|.
name|tile_num
operator|=
name|tile
operator|->
name|tile_num
expr_stmt|;
name|tile_req
operator|.
name|shadow
operator|=
name|tile
operator|->
name|shadow
expr_stmt|;
if|if
condition|(
operator|!
name|gp_tile_req_write
argument_list|(
name|_writechannel
argument_list|,
operator|&
name|tile_req
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
name|gimp_read_expect_msg
argument_list|(
operator|&
name|msg
argument_list|,
name|GP_TILE_DATA
argument_list|)
expr_stmt|;
name|tile_data
operator|=
name|msg
operator|.
name|data
expr_stmt|;
if|if
condition|(
operator|(
name|tile_data
operator|->
name|drawable_ID
operator|!=
name|tile
operator|->
name|drawable
operator|->
name|drawable_id
operator|)
operator|||
operator|(
name|tile_data
operator|->
name|tile_num
operator|!=
name|tile
operator|->
name|tile_num
operator|)
operator|||
operator|(
name|tile_data
operator|->
name|shadow
operator|!=
name|tile
operator|->
name|shadow
operator|)
operator|||
operator|(
name|tile_data
operator|->
name|width
operator|!=
name|tile
operator|->
name|ewidth
operator|)
operator|||
operator|(
name|tile_data
operator|->
name|height
operator|!=
name|tile
operator|->
name|eheight
operator|)
operator|||
operator|(
name|tile_data
operator|->
name|bpp
operator|!=
name|tile
operator|->
name|bpp
operator|)
condition|)
block|{
name|g_message
argument_list|(
literal|"received tile info did not match computed tile info\n"
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
name|tile_data
operator|->
name|use_shm
condition|)
block|{
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
name|ewidth
operator|*
name|tile
operator|->
name|eheight
operator|*
name|tile
operator|->
name|bpp
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|tile
operator|->
name|data
argument_list|,
name|_shm_addr
argument_list|,
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
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tile
operator|->
name|data
operator|=
name|tile_data
operator|->
name|data
expr_stmt|;
name|tile_data
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|gp_tile_ack_write
argument_list|(
name|_writechannel
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
name|wire_destroy
argument_list|(
operator|&
name|msg
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_put (GimpTile * tile)
name|gimp_tile_put
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
block|{
specifier|extern
name|GIOChannel
modifier|*
name|_writechannel
decl_stmt|;
specifier|extern
name|guchar
modifier|*
name|_shm_addr
decl_stmt|;
name|GPTileReq
name|tile_req
decl_stmt|;
name|GPTileData
name|tile_data
decl_stmt|;
name|GPTileData
modifier|*
name|tile_info
decl_stmt|;
name|WireMessage
name|msg
decl_stmt|;
name|tile_req
operator|.
name|drawable_ID
operator|=
operator|-
literal|1
expr_stmt|;
name|tile_req
operator|.
name|tile_num
operator|=
literal|0
expr_stmt|;
name|tile_req
operator|.
name|shadow
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|gp_tile_req_write
argument_list|(
name|_writechannel
argument_list|,
operator|&
name|tile_req
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
name|gimp_read_expect_msg
argument_list|(
operator|&
name|msg
argument_list|,
name|GP_TILE_DATA
argument_list|)
expr_stmt|;
name|tile_info
operator|=
name|msg
operator|.
name|data
expr_stmt|;
name|tile_data
operator|.
name|drawable_ID
operator|=
name|tile
operator|->
name|drawable
operator|->
name|drawable_id
expr_stmt|;
name|tile_data
operator|.
name|tile_num
operator|=
name|tile
operator|->
name|tile_num
expr_stmt|;
name|tile_data
operator|.
name|shadow
operator|=
name|tile
operator|->
name|shadow
expr_stmt|;
name|tile_data
operator|.
name|bpp
operator|=
name|tile
operator|->
name|bpp
expr_stmt|;
name|tile_data
operator|.
name|width
operator|=
name|tile
operator|->
name|ewidth
expr_stmt|;
name|tile_data
operator|.
name|height
operator|=
name|tile
operator|->
name|eheight
expr_stmt|;
name|tile_data
operator|.
name|use_shm
operator|=
name|tile_info
operator|->
name|use_shm
expr_stmt|;
name|tile_data
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|tile_info
operator|->
name|use_shm
condition|)
name|memcpy
argument_list|(
name|_shm_addr
argument_list|,
name|tile
operator|->
name|data
argument_list|,
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
argument_list|)
expr_stmt|;
else|else
name|tile_data
operator|.
name|data
operator|=
name|tile
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|gp_tile_data_write
argument_list|(
name|_writechannel
argument_list|,
operator|&
name|tile_data
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
name|gimp_read_expect_msg
argument_list|(
operator|&
name|msg
argument_list|,
name|GP_TILE_ACK
argument_list|)
expr_stmt|;
name|wire_destroy
argument_list|(
operator|&
name|msg
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* This function is nearly identical to the function 'tile_cache_insert'  *  in the file 'tile_cache.c' which is part of the main gimp application.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_tile_cache_insert (GimpTile * tile)
name|gimp_tile_cache_insert
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
block|{
name|GList
modifier|*
name|tmp
decl_stmt|;
if|if
condition|(
operator|!
name|tile_hash_table
condition|)
block|{
name|tile_hash_table
operator|=
name|g_hash_table_new
argument_list|(
operator|(
name|GHashFunc
operator|)
name|gimp_tile_hash
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|max_tile_size
operator|=
name|gimp_tile_width
argument_list|()
operator|*
name|gimp_tile_height
argument_list|()
operator|*
literal|4
expr_stmt|;
block|}
comment|/* First check and see if the tile is already    *  in the cache. In that case we will simply place    *  it at the end of the tile list to indicate that    *  it was the most recently accessed tile.    */
name|tmp
operator|=
name|g_hash_table_lookup
argument_list|(
name|tile_hash_table
argument_list|,
name|tile
argument_list|)
expr_stmt|;
if|if
condition|(
name|tmp
condition|)
block|{
comment|/* The tile was already in the cache. Place it at        *  the end of the tile list.        */
if|if
condition|(
name|tmp
operator|==
name|tile_list_tail
condition|)
name|tile_list_tail
operator|=
name|tile_list_tail
operator|->
name|prev
expr_stmt|;
name|tile_list_head
operator|=
name|g_list_remove_link
argument_list|(
name|tile_list_head
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tile_list_head
condition|)
name|tile_list_tail
operator|=
name|NULL
expr_stmt|;
name|g_list_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
comment|/* Remove the old reference to the tiles list node        *  in the tile hash table.        */
name|g_hash_table_remove
argument_list|(
name|tile_hash_table
argument_list|,
name|tile
argument_list|)
expr_stmt|;
name|tile_list_tail
operator|=
name|g_list_append
argument_list|(
name|tile_list_tail
argument_list|,
name|tile
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tile_list_head
condition|)
name|tile_list_head
operator|=
name|tile_list_tail
expr_stmt|;
name|tile_list_tail
operator|=
name|g_list_last
argument_list|(
name|tile_list_tail
argument_list|)
expr_stmt|;
comment|/* Add the tiles list node to the tile hash table. The        *  list node is indexed by the tile itself. This makes        *  for a quick lookup of which list node the tile is in.        */
name|g_hash_table_insert
argument_list|(
name|tile_hash_table
argument_list|,
name|tile
argument_list|,
name|tile_list_tail
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* The tile was not in the cache. First check and see        *  if there is room in the cache. If not then we'll have        *  to make room first. Note: it might be the case that the        *  cache is smaller than the size of a tile in which case        *  it won't be possible to put it in the cache.        */
if|if
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
while|while
condition|(
name|tile_list_head
operator|&&
operator|(
name|cur_cache_size
operator|+
name|max_cache_size
operator|*
name|FREE_QUANTUM
operator|)
operator|>
name|max_cache_size
condition|)
name|gimp_tile_cache_zorch
argument_list|()
expr_stmt|;
if|if
condition|(
operator|(
name|cur_cache_size
operator|+
name|max_tile_size
operator|)
operator|>
name|max_cache_size
condition|)
return|return;
block|}
comment|/* Place the tile at the end of the tile list.        */
name|tile_list_tail
operator|=
name|g_list_append
argument_list|(
name|tile_list_tail
argument_list|,
name|tile
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tile_list_head
condition|)
name|tile_list_head
operator|=
name|tile_list_tail
expr_stmt|;
name|tile_list_tail
operator|=
name|g_list_last
argument_list|(
name|tile_list_tail
argument_list|)
expr_stmt|;
comment|/* Add the tiles list node to the tile hash table.        */
name|g_hash_table_insert
argument_list|(
name|tile_hash_table
argument_list|,
name|tile
argument_list|,
name|tile_list_tail
argument_list|)
expr_stmt|;
comment|/* Note the increase in the number of bytes the cache        *  is referencing.        */
name|cur_cache_size
operator|+=
name|max_tile_size
expr_stmt|;
comment|/* Reference the tile so that it won't be returned to        *  the main gimp application immediately.        */
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
name|gimp_tile_get
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|tile
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_cache_flush (GimpTile * tile)
name|gimp_tile_cache_flush
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
block|{
name|GList
modifier|*
name|tmp
decl_stmt|;
if|if
condition|(
operator|!
name|tile_hash_table
condition|)
block|{
name|tile_hash_table
operator|=
name|g_hash_table_new
argument_list|(
operator|(
name|GHashFunc
operator|)
name|gimp_tile_hash
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|max_tile_size
operator|=
name|gimp_tile_width
argument_list|()
operator|*
name|gimp_tile_height
argument_list|()
operator|*
literal|4
expr_stmt|;
block|}
comment|/* Find where the tile is in the cache.    */
name|tmp
operator|=
name|g_hash_table_lookup
argument_list|(
name|tile_hash_table
argument_list|,
name|tile
argument_list|)
expr_stmt|;
if|if
condition|(
name|tmp
condition|)
block|{
comment|/* If the tile is in the cache, then remove it from the        *  tile list.        */
if|if
condition|(
name|tmp
operator|==
name|tile_list_tail
condition|)
name|tile_list_tail
operator|=
name|tile_list_tail
operator|->
name|prev
expr_stmt|;
name|tile_list_head
operator|=
name|g_list_remove_link
argument_list|(
name|tile_list_head
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tile_list_head
condition|)
name|tile_list_tail
operator|=
name|NULL
expr_stmt|;
name|g_list_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
comment|/* Remove the tile from the tile hash table.        */
name|g_hash_table_remove
argument_list|(
name|tile_hash_table
argument_list|,
name|tile
argument_list|)
expr_stmt|;
comment|/* Note the decrease in the number of bytes the cache        *  is referencing.        */
name|cur_cache_size
operator|-=
name|max_tile_size
expr_stmt|;
comment|/* Unreference the tile.        */
name|gimp_tile_unref
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
specifier|static
name|void
DECL|function|gimp_tile_cache_zorch (void)
name|gimp_tile_cache_zorch
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|tile_list_head
condition|)
name|gimp_tile_cache_flush
argument_list|(
operator|(
name|GimpTile
operator|*
operator|)
name|tile_list_head
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|guint
DECL|function|gimp_tile_hash (GimpTile * tile)
name|gimp_tile_hash
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
block|{
return|return
operator|(
name|gulong
operator|)
name|tile
return|;
block|}
end_function

end_unit

