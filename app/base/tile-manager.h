begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
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

begin_struct
DECL|struct|_TileLevel
struct|struct
name|_TileLevel
block|{
DECL|member|width
name|int
name|width
decl_stmt|;
comment|/* the width of the tiled area */
DECL|member|height
name|int
name|height
decl_stmt|;
comment|/* the height of the tiled area */
DECL|member|bpp
name|int
name|bpp
decl_stmt|;
comment|/* the bpp of each tile */
DECL|member|ntile_rows
name|int
name|ntile_rows
decl_stmt|;
comment|/* the number of tiles in each row */
DECL|member|ntile_cols
name|int
name|ntile_cols
decl_stmt|;
comment|/* the number of tiles in each columns */
DECL|member|tiles
name|Tile
modifier|*
name|tiles
decl_stmt|;
comment|/* the tiles for this level */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_TileManager
struct|struct
name|_TileManager
block|{
DECL|member|x
DECL|member|y
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/* tile manager offsets  */
DECL|member|nlevels
name|int
name|nlevels
decl_stmt|;
comment|/* the number of tile levels in the hierarchy */
DECL|member|levels
name|TileLevel
modifier|*
name|levels
decl_stmt|;
comment|/* the hierarchy */
DECL|member|validate_proc
name|TileValidateProc
name|validate_proc
decl_stmt|;
comment|/* this proc is called when an attempt to get an 				    *  invalid tile is made. 				    */
DECL|member|user_data
name|void
modifier|*
name|user_data
decl_stmt|;
comment|/* hook for hanging data off of */
block|}
struct|;
end_struct

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

