begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TILE_MANAGER_H__
end_ifndef

begin_define
DECL|macro|__TILE_MANAGER_H__
define|#
directive|define
name|__TILE_MANAGER_H__
end_define

begin_include
include|#
directive|include
file|"tile.h"
end_include

begin_typedef
DECL|typedef|TileLevel
typedef|typedef
name|struct
name|_TileLevel
name|TileLevel
typedef|;
end_typedef

begin_typedef
DECL|typedef|TileManager
typedef|typedef
name|struct
name|_TileManager
name|TileManager
typedef|;
end_typedef

begin_typedef
DECL|typedef|TileValidateProc
typedef|typedef
name|void
function_decl|(
modifier|*
name|TileValidateProc
function_decl|)
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
name|level
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/* Creates a new tile manager with the specified  *  width for the toplevel. The toplevel sizes is  *  used to compute the number of levels and there  *  size. Each level is 1/2 the width and height of  *  the level above it.  * The toplevel is level 0. The smallest level in the  *  hierarchy is "nlevels - 1". That level will be smaller  *  than TILE_WIDTH x TILE_HEIGHT  */
end_comment

begin_function_decl
name|TileManager
modifier|*
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
function_decl|;
end_function_decl

begin_comment
comment|/* Destroy a tile manager and all the tiles it contains.  */
end_comment

begin_function_decl
name|void
name|tile_manager_destroy
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Calculate the number of levels necessary to have a complete  *  hierarchy. This procedure is normally called twice with  *  the width and then height and the maximum value returned  *  is then used as the number of levels an image needs.  */
end_comment

begin_function_decl
name|int
name|tile_manager_calc_levels
parameter_list|(
name|int
name|size
parameter_list|,
name|int
name|tile_size
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Set the number of levels this tile manager is managing.  *  This procedure may destroy unnecessary levels in the  *  tile manager if the new number of levels is less than  *  the old number of levels.  * Any newly added levels will consist of invalid tiles.  */
end_comment

begin_function_decl
name|void
name|tile_manager_set_nlevels
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|int
name|nlevels
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Set the validate procedure for the tile manager.  *  The validate procedure is called when an invalid tile  *  is referenced. If the procedure is NULL, then the tile  *  is set to valid and its memory is allocated, but  *  not initialized.  */
end_comment

begin_function_decl
name|void
name|tile_manager_set_validate_proc
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|TileValidateProc
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Get a specified tile from a tile manager. The tile  *  is from the given level and contains the specified  *  pixel. Be aware that the pixel coordinates are  *  dependent on the level.  */
end_comment

begin_function_decl
name|Tile
modifier|*
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
function_decl|;
end_function_decl

begin_comment
comment|/* Get a specified tile from a tile manager.  */
end_comment

begin_function_decl
name|Tile
modifier|*
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
function_decl|;
end_function_decl

begin_comment
comment|/* Request that (if possible) the tile at x,y,layer be swapped  * in.  This is only a hint to improve performance; no guarantees.  * The tile may be swapped in or otherwise made more accessible  * if it is convenient...  */
end_comment

begin_function_decl
name|void
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
parameter_list|,
name|int
name|level
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_manager_map
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|int
name|time_num
parameter_list|,
name|int
name|level
parameter_list|,
name|Tile
modifier|*
name|srctile
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Validate a tiles memory.  */
end_comment

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_comment
comment|/* Given a toplevel tile, this procedure will invalidate  *  (set the dirty bit) for all tiles in lower levels which  *  contain this toplevel tile.  * Note: if a level hasn't been created then the tile for that  *       level won't be invalidated.  */
end_comment

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_comment
comment|/* Invalidates all the tiles in the sublevels.  */
end_comment

begin_function_decl
name|void
name|tile_manager_invalidate_sublevels
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Update a portion lower level tile given a toplevel tile.  */
end_comment

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TILE_MANAGER_H__ */
end_comment

end_unit

