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

begin_comment
comment|/* sanity checking on new tile hinting code */
end_comment

begin_comment
comment|/* #define HINTS_SANITY */
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

begin_typedef
DECL|typedef|Tile
typedef|typedef
name|struct
name|_Tile
name|Tile
typedef|;
end_typedef

begin_comment
comment|/*  explicit guchar type rather than enum since gcc chooses an int  *  representation but arrays of TileRowHints are quite space-critical  *  in GIMP.  */
end_comment

begin_typedef
DECL|typedef|TileRowHint
typedef|typedef
name|guchar
name|TileRowHint
typedef|;
end_typedef

begin_define
DECL|macro|TILEROWHINT_BROKEN
define|#
directive|define
name|TILEROWHINT_BROKEN
value|0
end_define

begin_define
DECL|macro|TILEROWHINT_OPAQUE
define|#
directive|define
name|TILEROWHINT_OPAQUE
value|1
end_define

begin_define
DECL|macro|TILEROWHINT_TRANSPARENT
define|#
directive|define
name|TILEROWHINT_TRANSPARENT
value|2
end_define

begin_define
DECL|macro|TILEROWHINT_MIXED
define|#
directive|define
name|TILEROWHINT_MIXED
value|3
end_define

begin_define
DECL|macro|TILEROWHINT_OUTOFRANGE
define|#
directive|define
name|TILEROWHINT_OUTOFRANGE
value|4
end_define

begin_define
DECL|macro|TILEROWHINT_UNDEFINED
define|#
directive|define
name|TILEROWHINT_UNDEFINED
value|5
end_define

begin_define
DECL|macro|TILEROWHINT_UNKNOWN
define|#
directive|define
name|TILEROWHINT_UNKNOWN
value|6
end_define

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
comment|/*  * tile_lock locks a tile into memory.  This does what tile_ref used  * to do.  It is the responsibility of the tile manager to take care  * of the copy-on-write semantics.  Locks stack; a tile remains locked  * in memory as long as it's been locked more times than it has been  * released.  tile_release needs to know whether the release was for  * write access.  (This is a hack, and should be handled better.)  */
end_comment

begin_function_decl
name|void
name|tile_lock
parameter_list|(
name|Tile
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_release
parameter_list|(
name|Tile
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

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

begin_function_decl
name|int
name|tile_ewidth
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|tile_eheight
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|tile_bpp
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|tile_is_valid
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_mark_valid
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* DOCUMENT ME -- adm */
end_comment

begin_function_decl
name|TileRowHint
name|tile_get_rowhint
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|yoff
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_set_rowhint
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|yoff
parameter_list|,
name|TileRowHint
name|rowhint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_sanitize_rowhints
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
modifier|*
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
function_decl|;
end_function_decl

begin_comment
comment|/* tile_attach attaches a tile to a tile manager: this function  * increments the tile's share count and inserts a tilelink into the  * tile's link list.  tile_detach reverses the process.  * If a tile's share count is zero after a tile_detach, the tile is  * discarded.  */
end_comment

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|void
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

