begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpchannel-project.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel-project.h"
end_include

begin_function
name|void
DECL|function|gimp_channel_project_region (GimpDrawable * drawable,gint x,gint y,gint width,gint height,PixelRegion * projPR,gboolean combine)
name|gimp_channel_project_region
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
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
parameter_list|,
name|PixelRegion
modifier|*
name|projPR
parameter_list|,
name|gboolean
name|combine
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|channel
init|=
name|GIMP_CHANNEL
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|;
name|TileManager
modifier|*
name|temp_tiles
decl_stmt|;
name|guchar
name|col
index|[
literal|3
index|]
decl_stmt|;
name|guchar
name|opacity
decl_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
operator|&
name|channel
operator|->
name|color
argument_list|,
operator|&
name|col
index|[
literal|0
index|]
argument_list|,
operator|&
name|col
index|[
literal|1
index|]
argument_list|,
operator|&
name|col
index|[
literal|2
index|]
argument_list|,
operator|&
name|opacity
argument_list|)
expr_stmt|;
name|gimp_drawable_init_src_region
argument_list|(
name|drawable
argument_list|,
operator|&
name|srcPR
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|&
name|temp_tiles
argument_list|)
expr_stmt|;
if|if
condition|(
name|combine
condition|)
block|{
name|combine_regions
argument_list|(
name|projPR
argument_list|,
operator|&
name|srcPR
argument_list|,
name|projPR
argument_list|,
name|NULL
argument_list|,
name|col
argument_list|,
name|opacity
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|NULL
argument_list|,
operator|(
name|gimp_channel_get_show_masked
argument_list|(
name|channel
argument_list|)
condition|?
name|COMBINE_INTEN_A_CHANNEL_MASK
else|:
name|COMBINE_INTEN_A_CHANNEL_SELECTION
operator|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|initial_region
argument_list|(
name|projPR
argument_list|,
operator|&
name|srcPR
argument_list|,
name|NULL
argument_list|,
name|col
argument_list|,
name|opacity
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|NULL
argument_list|,
operator|(
name|gimp_channel_get_show_masked
argument_list|(
name|channel
argument_list|)
condition|?
name|INITIAL_CHANNEL_MASK
else|:
name|INITIAL_CHANNEL_SELECTION
operator|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|temp_tiles
condition|)
name|tile_manager_unref
argument_list|(
name|temp_tiles
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

