begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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

begin_struct
DECL|struct|_TileManager
struct|struct
name|_TileManager
block|{
DECL|member|ref_count
name|gint
name|ref_count
decl_stmt|;
comment|/*  reference counter                    */
DECL|member|width
name|gint
name|width
decl_stmt|;
comment|/*  the width of the tiled area          */
DECL|member|height
name|gint
name|height
decl_stmt|;
comment|/*  the height of the tiled area         */
DECL|member|bpp
name|gint
name|bpp
decl_stmt|;
comment|/*  the bpp of each tile                 */
DECL|member|ntile_rows
name|gint
name|ntile_rows
decl_stmt|;
comment|/*  the number of tiles in each row      */
DECL|member|ntile_cols
name|gint
name|ntile_cols
decl_stmt|;
comment|/*  the number of tiles in each columns  */
DECL|member|tiles
name|Tile
modifier|*
modifier|*
name|tiles
decl_stmt|;
comment|/*  the tiles for this level             */
DECL|member|validate_proc
name|TileValidateProc
name|validate_proc
decl_stmt|;
comment|/*  this proc is called when an attempt  *                                      *  to get an invalid tile is made       */
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
comment|/*  data to pass to the validate_proc    */
DECL|member|cached_num
name|gint
name|cached_num
decl_stmt|;
comment|/*  number of cached tile                */
DECL|member|cached_tile
name|Tile
modifier|*
name|cached_tile
decl_stmt|;
comment|/*  the actual cached tile               */
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

