begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__TILE_H__
end_ifndef

begin_define
DECL|macro|__TILE_H__
define|#
directive|define
name|__TILE_H__
end_define

begin_define
DECL|macro|TILE_WIDTH
define|#
directive|define
name|TILE_WIDTH
value|64
end_define

begin_define
DECL|macro|TILE_HEIGHT
define|#
directive|define
name|TILE_HEIGHT
value|64
end_define

begin_comment
comment|/* Uncomment for verbose debugging on copy-on-write logic #define TILE_DEBUG */
end_comment

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

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

begin_typedef
DECL|typedef|Tile
typedef|typedef
name|struct
name|_Tile
name|Tile
typedef|;
end_typedef

begin_struct
DECL|struct|_Tile
struct|struct
name|_Tile
block|{
DECL|member|ref_count
name|short
name|ref_count
decl_stmt|;
comment|/* reference count. when the reference count is  		       *  non-zero then the "data" for this tile must 		       *  be valid. when the reference count for a tile 		       *  is 0 then the "data" for this tile must be 		       *  NULL. 		       */
DECL|member|dirty
name|guint
name|dirty
range|:
literal|1
decl_stmt|;
comment|/* is the tile dirty? has it been modified? */
DECL|member|valid
name|guint
name|valid
range|:
literal|1
decl_stmt|;
comment|/* is the tile valid? */
DECL|member|data
name|guchar
modifier|*
name|data
decl_stmt|;
comment|/* the data for the tile. this may be NULL in which 		       *  case the tile data is on disk. 		       */
DECL|member|real_tile_ptr
name|Tile
modifier|*
name|real_tile_ptr
decl_stmt|;
comment|/* if this tile's 'data' pointer is just a copy-on-write 		       *  mirror of another's, this is that source tile. 		       *  (real_tile itself can actually be a virtual tile 		       *  too.)  This is NULL if this tile is not a virtual 		       *  tile. 		       */
DECL|member|mirrored_by
name|Tile
modifier|*
name|mirrored_by
decl_stmt|;
comment|/* If another tile is mirroring this one, this is 		       *  a pointer to that tile, otherwise this is NULL. 		       *  Note that only one tile may be _directly_ mirroring 		       *  another given tile.  This ensures that the graph 		       *  of mirrorings is no more complex than a linked 		       *  list. 		       */
DECL|member|ewidth
name|int
name|ewidth
decl_stmt|;
comment|/* the effective width of the tile */
DECL|member|eheight
name|int
name|eheight
decl_stmt|;
comment|/* the effective height of the tile */
comment|/*  a tile's effective width and height may be smaller 		       *  (but not larger) than TILE_WIDTH and TILE_HEIGHT. 		       *  this is to handle edge tiles of a drawable. 		       */
DECL|member|bpp
name|int
name|bpp
decl_stmt|;
comment|/* the bytes per pixel (1, 2, 3 or 4) */
DECL|member|tile_num
name|int
name|tile_num
decl_stmt|;
comment|/* the number of this tile within the drawable */
DECL|member|swap_num
name|int
name|swap_num
decl_stmt|;
comment|/* the index into the file table of the file to be used 		       *  for swapping. swap_num 1 is always the global swap file. 		       */
DECL|member|swap_offset
name|off_t
name|swap_offset
decl_stmt|;
comment|/* the offset within the swap file of the tile data. 		       *  if the tile data is in memory this will be set to -1. 		       */
DECL|member|tm
name|void
modifier|*
name|tm
decl_stmt|;
comment|/* A pointer to the tile manager for this tile. 		       *  We need this in order to call the tile managers validate 		       *  proc whenever the tile is referenced yet invalid. 		       */
DECL|member|next
name|Tile
modifier|*
name|next
decl_stmt|;
DECL|member|prev
name|Tile
modifier|*
name|prev
decl_stmt|;
comment|/* List pointers for the tile cache lists */
DECL|member|listhead
name|void
modifier|*
name|listhead
decl_stmt|;
comment|/* Pointer to the head of the list this tile is on */
ifdef|#
directive|ifdef
name|USE_PTHREADS
DECL|member|mutex
name|pthread_mutex_t
name|mutex
decl_stmt|;
endif|#
directive|endif
block|}
struct|;
end_struct

begin_comment
comment|/* Initializes the fields of a tile to "good" values.  */
end_comment

begin_function_decl
name|void
name|tile_init
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|bpp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * c-o-w  */
end_comment

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_comment
comment|/* Referencing a tile causes the reference count to be incremented.  *  If the reference count was previously 0 the tile will will be  *  swapped into memory from disk.  *  * tile_ref2 is a new tile-referencing interface through which you  *  should register your intent to dirty the tile.  This will facilitate  *  copy-on-write tile semantics.  */
end_comment

begin_if
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
end_if

begin_define
DECL|macro|tile_ref (t)
define|#
directive|define
name|tile_ref
parameter_list|(
name|t
parameter_list|)
value|_tile_ref (t, __PRETTY_FUNCTION__)
end_define

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_define
DECL|macro|tile_ref2 (t,d)
define|#
directive|define
name|tile_ref2
parameter_list|(
name|t
parameter_list|,
name|d
parameter_list|)
value|_tile_ref2 (t, d, __PRETTY_FUNCTION__)
end_define

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_function_decl
name|void
name|tile_ref
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_ref2
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|dirty
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Unreferencing a tile causes the reference count to be decremented.  *  When the reference count reaches 0 the tile data will be swapped  *  out to disk. Note that the tile may be in the tile cache which  *  also references the tile causing the reference count not to  *  fall below 1 until the tile is removed from the cache.  *  The dirty flag indicates whether the tile data has been dirtied  *  while referenced.  */
end_comment

begin_if
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
end_if

begin_define
DECL|macro|tile_unref (t,d)
define|#
directive|define
name|tile_unref
parameter_list|(
name|t
parameter_list|,
name|d
parameter_list|)
value|_tile_unref (t, d, __PRETTY_FUNCTION__)
end_define

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_function_decl
name|void
name|tile_unref
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|dirty
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Allocate the data for the tile.  */
end_comment

begin_function_decl
name|void
name|tile_alloc
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Return the size in bytes of the tiles data.  */
end_comment

begin_function_decl
name|int
name|tile_size
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Invalidates a tile. This involves setting its invalid bit and  *  a) if the tile is in memory deleting the tile data or b) if the  *  tile is in the swap file, deleting the space it occupies. This  *  will cause the tile data to need to be recalculated.  * This should probably only be used on sublevel tiles. Invalidating  *  a toplevel tile would mean that it needs to be recalculated. But  *  what do you recalculate a toplevel tile from?  */
end_comment

begin_function_decl
name|void
name|tile_invalidate
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TILE_H__ */
end_comment

end_unit

