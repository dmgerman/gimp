begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TILE_MANAGER_PVT_H__
end_ifndef

begin_define
DECL|macro|__TILE_MANAGER_PVT_H__
define|#
directive|define
name|__TILE_MANAGER_PVT_H__
end_define

begin_include
include|#
directive|include
file|"tile.h"
end_include

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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TILE_MANAGER_PVT_H__ */
end_comment

end_unit

