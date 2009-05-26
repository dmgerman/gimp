begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TILE_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__TILE_PRIVATE_H__
define|#
directive|define
name|__TILE_PRIVATE_H__
end_define

begin_comment
comment|/*  Uncomment to enable global counters to profile the tile system. */
end_comment

begin_comment
comment|/*  #define TILE_PROFILING */
end_comment

begin_include
include|#
directive|include
file|<sys/types.h>
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
name|gint
name|tile_num
decl_stmt|;
comment|/* the number of this tile within the drawable */
DECL|member|tm
name|TileManager
modifier|*
name|tm
decl_stmt|;
comment|/* A pointer to the tile manager for this tile.                           *  We need this in order to call the tile managers                           *  validate proc whenever the tile is referenced                           *  yet invalid.                           */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_Tile
struct|struct
name|_Tile
block|{
DECL|member|ref_count
name|gshort
name|ref_count
decl_stmt|;
comment|/* reference count. when the reference count is                           *  non-zero then the "data" for this tile must                          *  be valid. when the reference count for a tile                          *  is 0 then the "data" for this tile must be                          *  NULL.                          */
DECL|member|write_count
name|gshort
name|write_count
decl_stmt|;
comment|/* write count: number of references that are                            for write access */
DECL|member|share_count
name|gshort
name|share_count
decl_stmt|;
comment|/* share count: number of tile managers that                            hold this tile */
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
ifdef|#
directive|ifdef
name|TILE_PROFILING
DECL|member|zorched
name|guint
name|zorched
range|:
literal|1
decl_stmt|;
comment|/* was the tile flushed due to cache pressure 			   [zorched]? */
DECL|member|zorchout
name|guint
name|zorchout
range|:
literal|1
decl_stmt|;
comment|/* was the tile swapped out due to cache 			   pressure [zorched]? */
DECL|member|inonce
name|guint
name|inonce
range|:
literal|1
decl_stmt|;
comment|/* has the tile been swapped in at least once? */
DECL|member|outonce
name|guint
name|outonce
range|:
literal|1
decl_stmt|;
comment|/* has the tile been swapped out at least once? */
endif|#
directive|endif
DECL|member|bpp
name|guchar
name|bpp
decl_stmt|;
comment|/* the bytes per pixel (1, 2, 3 or 4) */
DECL|member|ewidth
name|gushort
name|ewidth
decl_stmt|;
comment|/* the effective width of the tile */
DECL|member|eheight
name|gushort
name|eheight
decl_stmt|;
comment|/* the effective height of the tile                          *  a tile's effective width and height may be smaller                          *  (but not larger) than TILE_WIDTH and TILE_HEIGHT.                          *  this is to handle edge tiles of a drawable.                          */
DECL|member|size
name|gint
name|size
decl_stmt|;
comment|/* size of the tile data (ewidth * eheight * bpp) */
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
comment|/* the data for the tile. this may be NULL in which                          *  case the tile data is on disk.                          */
DECL|member|swap_offset
name|gint64
name|swap_offset
decl_stmt|;
comment|/* the offset within the swap file of the tile data.                          * if the tile data is in memory this will be set                          * to -1.                          */
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
comment|/* List pointers for the tile cache lists */
DECL|member|prev
name|Tile
modifier|*
name|prev
decl_stmt|;
DECL|member|listhead
name|gpointer
name|listhead
decl_stmt|;
comment|/* Pointer to the head of the list this tile is on */
block|}
struct|;
end_struct

begin_comment
comment|/*  tile_data_pointer() as a macro so that it can be inlined  */
end_comment

begin_comment
comment|/*  note that (y)& (TILE_HEIGHT-1) is equivalent to (y) % TILE_HEIGHT      for positive power-of-two divisors */
end_comment

begin_define
DECL|macro|TILE_DATA_POINTER (tile,x,y)
define|#
directive|define
name|TILE_DATA_POINTER
parameter_list|(
name|tile
parameter_list|,
name|x
parameter_list|,
name|y
parameter_list|)
define|\
value|((tile)->data + \    (((y)& (TILE_HEIGHT-1)) * (tile)->ewidth + ((x)& (TILE_WIDTH-1))) * (tile)->bpp)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TILE_PRIVATE_H__ */
end_comment

end_unit

