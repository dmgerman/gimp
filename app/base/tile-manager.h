begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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

begin_define
DECL|macro|GIMP_TYPE_TILE_MANAGER
define|#
directive|define
name|GIMP_TYPE_TILE_MANAGER
value|(gimp_tile_manager_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_TILE_MANAGER (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_TILE_MANAGER
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_TILE_MANAGER))
end_define

begin_decl_stmt
name|GType
name|gimp_tile_manager_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_ifdef
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
end_ifdef

begin_function_decl
name|void
name|tile_manager_exit
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Creates a new tile manager with the specified size */
end_comment

begin_function_decl
name|TileManager
modifier|*
name|tile_manager_new
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Ref/Unref a tile manager.  */
end_comment

begin_function_decl
name|TileManager
modifier|*
name|tile_manager_ref
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_manager_unref
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Make a copy of the tile manager.  */
end_comment

begin_function_decl
name|TileManager
modifier|*
name|tile_manager_duplicate
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Set the validate procedure for the tile manager.  The validate  *  procedure is called when an invalid tile is referenced. If the  *  procedure is NULL, then the tile is set to valid and its memory is  *  allocated, but not initialized.  */
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
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Get a specified tile from a tile manager.  */
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
name|gint
name|xpixel
parameter_list|,
name|gint
name|ypixel
parameter_list|,
name|gboolean
name|wantread
parameter_list|,
name|gboolean
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
name|gint
name|tile_num
parameter_list|,
name|gboolean
name|wantread
parameter_list|,
name|gboolean
name|wantwrite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tile
modifier|*
name|tile_manager_get_at
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|gint
name|tile_col
parameter_list|,
name|gint
name|tile_row
parameter_list|,
name|gboolean
name|wantread
parameter_list|,
name|gboolean
name|wantwrite
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
name|gint
name|xpixel
parameter_list|,
name|gint
name|ypixel
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
name|gint
name|tile_num
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
name|tile_manager_validate_tile
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

begin_function_decl
name|void
name|tile_manager_invalidate_area
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|tile_manager_width
parameter_list|(
specifier|const
name|TileManager
modifier|*
name|tm
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|tile_manager_height
parameter_list|(
specifier|const
name|TileManager
modifier|*
name|tm
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|tile_manager_bpp
parameter_list|(
specifier|const
name|TileManager
modifier|*
name|tm
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|tile_manager_get_memsize
parameter_list|(
specifier|const
name|TileManager
modifier|*
name|tm
parameter_list|,
name|gboolean
name|sparse
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_manager_get_tile_coordinates
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_manager_get_tile_col_row
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|,
name|gint
modifier|*
name|tile_col
parameter_list|,
name|gint
modifier|*
name|tile_row
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_manager_map_over_tile
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|,
name|Tile
modifier|*
name|srctile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|read_pixel_data
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|guchar
modifier|*
name|buffer
parameter_list|,
name|guint
name|stride
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|write_pixel_data
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
specifier|const
name|guchar
modifier|*
name|buffer
parameter_list|,
name|guint
name|stride
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*   Fill buffer with the pixeldata for the pixel at coordinates x,y  *   if x,y is outside the area of the tilemanger, nothing is done.  */
end_comment

begin_function_decl
name|void
name|read_pixel_data_1
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guchar
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|write_pixel_data_1
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|guchar
modifier|*
name|buffer
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

