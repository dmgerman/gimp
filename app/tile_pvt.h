begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__TILE_PVT_H__
end_ifndef

begin_define
DECL|macro|__TILE_PVT_H__
define|#
directive|define
name|__TILE_PVT_H__
end_define

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

begin_include
include|#
directive|include
file|"tile.h"
end_include

begin_typedef
DECL|typedef|TileLink
typedef|typedef
name|struct
name|_TileLink
name|TileLink
typedef|;
end_typedef

begin_struct
DECL|struct|_TileLink
struct|struct
name|_TileLink
block|{
DECL|member|next
name|TileLink
modifier|*
name|next
decl_stmt|;
DECL|member|tile_num
name|int
name|tile_num
decl_stmt|;
comment|/* the number of this tile within the drawable */
DECL|member|tm
name|void
modifier|*
name|tm
decl_stmt|;
comment|/* A pointer to the tile manager for this tile. 		       *  We need this in order to call the tile managers  		       *  validate proc whenever the tile is referenced yet  		       *  invalid. 		       */
block|}
struct|;
end_struct

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
DECL|member|write_count
name|short
name|write_count
decl_stmt|;
comment|/* write count: number of references that are 			 for write access */
DECL|member|share_count
name|short
name|share_count
decl_stmt|;
comment|/* share count: number of tile managers that 			 hold this tile */
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
DECL|member|bpp
name|unsigned
name|char
name|bpp
decl_stmt|;
comment|/* the bytes per pixel (1, 2, 3 or 4) */
DECL|member|ewidth
name|unsigned
name|short
name|ewidth
decl_stmt|;
comment|/* the effective width of the tile */
DECL|member|eheight
name|unsigned
name|short
name|eheight
decl_stmt|;
comment|/* the effective height of the tile */
comment|/*  a tile's effective width and height may be smaller 			   *  (but not larger) than TILE_WIDTH and TILE_HEIGHT. 			   *  this is to handle edge tiles of a drawable. 			   */
DECL|member|rowhint
name|TileRowHint
modifier|*
name|rowhint
decl_stmt|;
comment|/* An array of hints for rendering purposes */
DECL|member|data
name|guchar
modifier|*
name|data
decl_stmt|;
comment|/* the data for the tile. this may be NULL in which 		       *  case the tile data is on disk. 		       */
DECL|member|swap_num
name|int
name|swap_num
decl_stmt|;
comment|/* the index into the file table of the file to be used 		 *  for swapping. swap_num 1 is always the global swap file. 		 */
DECL|member|swap_offset
name|off_t
name|swap_offset
decl_stmt|;
comment|/* the offset within the swap file of the tile data. 		       *  if the tile data is in memory this will be set to -1. 		       */
DECL|member|tlink
name|TileLink
modifier|*
name|tlink
decl_stmt|;
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

begin_ifdef
ifdef|#
directive|ifdef
name|USE_PTHREADS
end_ifdef

begin_define
DECL|macro|TILE_MUTEX_LOCK (tile)
define|#
directive|define
name|TILE_MUTEX_LOCK
parameter_list|(
name|tile
parameter_list|)
value|pthread_mutex_lock(&((tile)->mutex))
end_define

begin_define
DECL|macro|TILE_MUTEX_UNLOCK (tile)
define|#
directive|define
name|TILE_MUTEX_UNLOCK
parameter_list|(
name|tile
parameter_list|)
value|pthread_mutex_unlock(&((tile)->mutex))
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|TILE_MUTEX_LOCK (tile)
define|#
directive|define
name|TILE_MUTEX_LOCK
parameter_list|(
name|tile
parameter_list|)
end_define

begin_comment
DECL|macro|TILE_MUTEX_LOCK (tile)
comment|/* nothing */
end_comment

begin_define
DECL|macro|TILE_MUTEX_UNLOCK (tile)
define|#
directive|define
name|TILE_MUTEX_UNLOCK
parameter_list|(
name|tile
parameter_list|)
end_define

begin_comment
DECL|macro|TILE_MUTEX_UNLOCK (tile)
comment|/* nothing */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TILE_PVT_H__ */
end_comment

end_unit

