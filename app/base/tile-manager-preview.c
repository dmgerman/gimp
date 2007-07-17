begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"base-types.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/scale-funcs.h"
end_include

begin_include
include|#
directive|include
file|"pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"tile-manager-preview.h"
end_include

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|tile_manager_create_preview
parameter_list|(
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
name|src_width
parameter_list|,
name|gint
name|src_height
parameter_list|,
name|gint
name|dest_width
parameter_list|,
name|gint
name|dest_height
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|TempBuf
modifier|*
DECL|function|tile_manager_get_preview (TileManager * tiles,gint width,gint height)
name|tile_manager_get_preview
parameter_list|(
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|tiles
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
operator|&&
name|height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|tile_manager_create_preview
argument_list|(
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|tile_manager_width
argument_list|(
name|tiles
argument_list|)
argument_list|,
name|tile_manager_height
argument_list|(
name|tiles
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|tile_manager_get_sub_preview (TileManager * tiles,gint src_x,gint src_y,gint src_width,gint src_height,gint dest_width,gint dest_height)
name|tile_manager_get_sub_preview
parameter_list|(
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
name|src_width
parameter_list|,
name|gint
name|src_height
parameter_list|,
name|gint
name|dest_width
parameter_list|,
name|gint
name|dest_height
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|tiles
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_x
operator|>=
literal|0
operator|&&
name|src_x
operator|<
name|tile_manager_width
argument_list|(
name|tiles
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_y
operator|>=
literal|0
operator|&&
name|src_y
operator|<
name|tile_manager_height
argument_list|(
name|tiles
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_width
operator|>
literal|0
operator|&&
name|src_x
operator|+
name|src_width
operator|<=
name|tile_manager_width
argument_list|(
name|tiles
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_height
operator|>
literal|0
operator|&&
name|src_y
operator|+
name|src_height
operator|<=
name|tile_manager_height
argument_list|(
name|tiles
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dest_width
operator|>
literal|0
operator|&&
name|dest_height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|tile_manager_create_preview
argument_list|(
name|tiles
argument_list|,
name|src_x
argument_list|,
name|src_y
argument_list|,
name|src_width
argument_list|,
name|src_height
argument_list|,
name|dest_width
argument_list|,
name|dest_height
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|tile_manager_create_preview (TileManager * tiles,gint src_x,gint src_y,gint src_width,gint src_height,gint dest_width,gint dest_height)
name|tile_manager_create_preview
parameter_list|(
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
name|src_width
parameter_list|,
name|gint
name|src_height
parameter_list|,
name|gint
name|dest_width
parameter_list|,
name|gint
name|dest_height
parameter_list|)
block|{
name|TempBuf
modifier|*
name|preview
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|;
name|PixelRegion
name|destPR
decl_stmt|;
name|gint
name|subsample
init|=
literal|1
decl_stmt|;
name|preview
operator|=
name|temp_buf_new
argument_list|(
name|dest_width
argument_list|,
name|dest_height
argument_list|,
name|tile_manager_bpp
argument_list|(
name|tiles
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|tiles
argument_list|,
name|src_x
argument_list|,
name|src_y
argument_list|,
name|src_width
argument_list|,
name|src_height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|destPR
argument_list|,
name|preview
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|dest_width
argument_list|,
name|dest_height
argument_list|)
expr_stmt|;
comment|/*  calculate 'acceptable' subsample  */
while|while
condition|(
operator|(
name|dest_width
operator|*
operator|(
name|subsample
operator|+
literal|1
operator|)
operator|*
literal|2
operator|<
name|src_width
operator|)
operator|&&
operator|(
name|dest_height
operator|*
operator|(
name|subsample
operator|+
literal|1
operator|)
operator|*
literal|2
operator|<
name|src_height
operator|)
condition|)
name|subsample
operator|+=
literal|1
expr_stmt|;
name|subsample_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|,
name|subsample
argument_list|)
expr_stmt|;
return|return
name|preview
return|;
block|}
end_function

end_unit

