begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TILE_PYRAMID_H__
end_ifndef

begin_define
DECL|macro|__TILE_PYRAMID_H__
define|#
directive|define
name|__TILE_PYRAMID_H__
end_define

begin_comment
comment|/* Creates a new tile pyramid with the specified size for the  *  toplevel. The toplevel size is used to compute the number of  *  levels and their size. Each level is 1/2 the width and height of  *  the level above it.  *  * The toplevel is level 0. The smallest level in the hierarchy  *  is "nlevels - 1". That level will be smaller than TILE_WIDTH x  *  TILE_HEIGHT  */
end_comment

begin_function_decl
name|TilePyramid
modifier|*
name|tile_pyramid_new
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_pyramid_destroy
parameter_list|(
name|TilePyramid
modifier|*
name|pyramid
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|tile_pyramid_get_level
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gdouble
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|tile_pyramid_get_tiles
parameter_list|(
name|TilePyramid
modifier|*
name|pyramid
parameter_list|,
name|gint
name|level
parameter_list|,
name|gboolean
modifier|*
name|is_premult
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_pyramid_invalidate_area
parameter_list|(
name|TilePyramid
modifier|*
name|pyramid
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_pyramid_set_validate_proc
parameter_list|(
name|TilePyramid
modifier|*
name|pyramid
parameter_list|,
name|TileValidateProc
name|proc
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|tile_pyramid_get_width
parameter_list|(
specifier|const
name|TilePyramid
modifier|*
name|pyramid
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|tile_pyramid_get_height
parameter_list|(
specifier|const
name|TilePyramid
modifier|*
name|pyramid
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|tile_pyramid_get_bpp
parameter_list|(
specifier|const
name|TilePyramid
modifier|*
name|pyramid
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|tile_pyramid_get_memsize
parameter_list|(
specifier|const
name|TilePyramid
modifier|*
name|pyramid
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TILE_PYRAMID_H__ */
end_comment

end_unit

