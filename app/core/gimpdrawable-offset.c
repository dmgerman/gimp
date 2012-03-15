begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<cairo.h>
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
file|"libgimpmath/gimpmath.h"
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
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-offset.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_drawable_offset (GimpDrawable * drawable,GimpContext * context,gboolean wrap_around,GimpOffsetType fill_type,gint offset_x,gint offset_y)
name|gimp_drawable_offset
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|wrap_around
parameter_list|,
name|GimpOffsetType
name|fill_type
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|PixelRegion
name|destPR
decl_stmt|;
name|TileManager
modifier|*
name|new_tiles
decl_stmt|;
name|GeglBuffer
modifier|*
name|src_buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
name|GeglRectangle
name|src_rect
decl_stmt|;
name|GeglRectangle
name|dest_rect
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|src_x
decl_stmt|,
name|src_y
decl_stmt|;
name|gint
name|dest_x
decl_stmt|,
name|dest_y
decl_stmt|;
name|guchar
name|fill
index|[
name|MAX_CHANNELS
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|wrap_around
condition|)
block|{
comment|/*  avoid modulo operation on negative values  */
while|while
condition|(
name|offset_x
operator|<
literal|0
condition|)
name|offset_x
operator|+=
name|width
expr_stmt|;
while|while
condition|(
name|offset_y
operator|<
literal|0
condition|)
name|offset_y
operator|+=
name|height
expr_stmt|;
name|offset_x
operator|%=
name|width
expr_stmt|;
name|offset_y
operator|%=
name|height
expr_stmt|;
block|}
else|else
block|{
name|offset_x
operator|=
name|CLAMP
argument_list|(
name|offset_x
argument_list|,
operator|-
name|width
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|offset_y
operator|=
name|CLAMP
argument_list|(
name|offset_y
argument_list|,
operator|-
name|height
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|offset_x
operator|==
literal|0
operator|&&
name|offset_y
operator|==
literal|0
condition|)
return|return;
name|new_tiles
operator|=
name|tile_manager_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|src_buffer
operator|=
name|gimp_drawable_get_read_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|dest_buffer
operator|=
name|gimp_tile_manager_create_buffer
argument_list|(
name|new_tiles
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|offset_x
operator|>=
literal|0
condition|)
block|{
name|src_x
operator|=
literal|0
expr_stmt|;
name|dest_x
operator|=
name|offset_x
expr_stmt|;
name|width
operator|=
name|CLAMP
argument_list|(
operator|(
name|width
operator|-
name|offset_x
operator|)
argument_list|,
literal|0
argument_list|,
name|width
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|src_x
operator|=
operator|-
name|offset_x
expr_stmt|;
name|dest_x
operator|=
literal|0
expr_stmt|;
name|width
operator|=
name|CLAMP
argument_list|(
operator|(
name|width
operator|+
name|offset_x
operator|)
argument_list|,
literal|0
argument_list|,
name|width
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|offset_y
operator|>=
literal|0
condition|)
block|{
name|src_y
operator|=
literal|0
expr_stmt|;
name|dest_y
operator|=
name|offset_y
expr_stmt|;
name|height
operator|=
name|CLAMP
argument_list|(
operator|(
name|height
operator|-
name|offset_y
operator|)
argument_list|,
literal|0
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|src_y
operator|=
operator|-
name|offset_y
expr_stmt|;
name|dest_y
operator|=
literal|0
expr_stmt|;
name|height
operator|=
name|CLAMP
argument_list|(
operator|(
name|height
operator|+
name|offset_y
operator|)
argument_list|,
literal|0
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
comment|/*  Copy the center region  */
if|if
condition|(
name|width
operator|&&
name|height
condition|)
block|{
name|src_rect
operator|.
name|x
operator|=
name|src_x
expr_stmt|;
name|src_rect
operator|.
name|y
operator|=
name|src_y
expr_stmt|;
name|src_rect
operator|.
name|width
operator|=
name|width
expr_stmt|;
name|src_rect
operator|.
name|height
operator|=
name|height
expr_stmt|;
name|dest_rect
operator|.
name|x
operator|=
name|dest_x
expr_stmt|;
name|dest_rect
operator|.
name|y
operator|=
name|dest_y
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|src_buffer
argument_list|,
operator|&
name|src_rect
argument_list|,
name|dest_buffer
argument_list|,
operator|&
name|dest_rect
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|wrap_around
condition|)
block|{
comment|/*  Copy appropriately for wrap around  */
if|if
condition|(
name|offset_x
operator|>=
literal|0
operator|&&
name|offset_y
operator|>=
literal|0
condition|)
block|{
name|src_x
operator|=
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|-
name|offset_x
expr_stmt|;
name|src_y
operator|=
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|-
name|offset_y
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|offset_x
operator|>=
literal|0
operator|&&
name|offset_y
operator|<
literal|0
condition|)
block|{
name|src_x
operator|=
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|-
name|offset_x
expr_stmt|;
name|src_y
operator|=
literal|0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|offset_x
operator|<
literal|0
operator|&&
name|offset_y
operator|>=
literal|0
condition|)
block|{
name|src_x
operator|=
literal|0
expr_stmt|;
name|src_y
operator|=
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|-
name|offset_y
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|offset_x
operator|<
literal|0
operator|&&
name|offset_y
operator|<
literal|0
condition|)
block|{
name|src_x
operator|=
literal|0
expr_stmt|;
name|src_y
operator|=
literal|0
expr_stmt|;
block|}
name|dest_x
operator|=
operator|(
name|src_x
operator|+
name|offset_x
operator|)
operator|%
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|dest_x
operator|<
literal|0
condition|)
name|dest_x
operator|=
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|+
name|dest_x
expr_stmt|;
name|dest_y
operator|=
operator|(
name|src_y
operator|+
name|offset_y
operator|)
operator|%
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|dest_y
operator|<
literal|0
condition|)
name|dest_y
operator|=
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|+
name|dest_y
expr_stmt|;
comment|/*  intersecting region  */
if|if
condition|(
name|offset_x
operator|!=
literal|0
operator|&&
name|offset_y
operator|!=
literal|0
condition|)
block|{
name|src_rect
operator|.
name|x
operator|=
name|src_x
expr_stmt|;
name|src_rect
operator|.
name|y
operator|=
name|src_y
expr_stmt|;
name|src_rect
operator|.
name|width
operator|=
name|ABS
argument_list|(
name|offset_x
argument_list|)
expr_stmt|;
name|src_rect
operator|.
name|height
operator|=
name|ABS
argument_list|(
name|offset_y
argument_list|)
expr_stmt|;
name|dest_rect
operator|.
name|x
operator|=
name|dest_x
expr_stmt|;
name|dest_rect
operator|.
name|y
operator|=
name|dest_y
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|src_buffer
argument_list|,
operator|&
name|src_rect
argument_list|,
name|dest_buffer
argument_list|,
operator|&
name|dest_rect
argument_list|)
expr_stmt|;
block|}
comment|/*  X offset  */
if|if
condition|(
name|offset_x
operator|!=
literal|0
condition|)
block|{
if|if
condition|(
name|offset_y
operator|>=
literal|0
condition|)
block|{
name|src_rect
operator|.
name|x
operator|=
name|src_x
expr_stmt|;
name|src_rect
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|src_rect
operator|.
name|width
operator|=
name|ABS
argument_list|(
name|offset_x
argument_list|)
expr_stmt|;
name|src_rect
operator|.
name|height
operator|=
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|-
name|ABS
argument_list|(
name|offset_y
argument_list|)
expr_stmt|;
name|dest_rect
operator|.
name|x
operator|=
name|dest_x
expr_stmt|;
name|dest_rect
operator|.
name|y
operator|=
name|dest_y
operator|+
name|offset_y
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|offset_y
operator|<
literal|0
condition|)
block|{
name|src_rect
operator|.
name|x
operator|=
name|src_x
expr_stmt|;
name|src_rect
operator|.
name|y
operator|=
name|src_y
operator|-
name|offset_y
expr_stmt|;
name|src_rect
operator|.
name|width
operator|=
name|ABS
argument_list|(
name|offset_x
argument_list|)
expr_stmt|;
name|src_rect
operator|.
name|height
operator|=
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|-
name|ABS
argument_list|(
name|offset_y
argument_list|)
expr_stmt|;
name|dest_rect
operator|.
name|x
operator|=
name|dest_x
expr_stmt|;
name|dest_rect
operator|.
name|y
operator|=
literal|0
expr_stmt|;
block|}
name|gegl_buffer_copy
argument_list|(
name|src_buffer
argument_list|,
operator|&
name|src_rect
argument_list|,
name|dest_buffer
argument_list|,
operator|&
name|dest_rect
argument_list|)
expr_stmt|;
block|}
comment|/*  X offset  */
if|if
condition|(
name|offset_y
operator|!=
literal|0
condition|)
block|{
if|if
condition|(
name|offset_x
operator|>=
literal|0
condition|)
block|{
name|src_rect
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|src_rect
operator|.
name|y
operator|=
name|src_y
expr_stmt|;
name|src_rect
operator|.
name|width
operator|=
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|-
name|ABS
argument_list|(
name|offset_x
argument_list|)
expr_stmt|;
name|src_rect
operator|.
name|height
operator|=
name|ABS
argument_list|(
name|offset_y
argument_list|)
expr_stmt|;
name|dest_rect
operator|.
name|x
operator|=
name|dest_x
operator|+
name|offset_x
expr_stmt|;
name|dest_rect
operator|.
name|y
operator|=
name|dest_y
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|offset_x
operator|<
literal|0
condition|)
block|{
name|src_rect
operator|.
name|x
operator|=
name|src_x
operator|-
name|offset_x
expr_stmt|;
name|src_rect
operator|.
name|y
operator|=
name|src_y
expr_stmt|;
name|src_rect
operator|.
name|width
operator|=
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|-
name|ABS
argument_list|(
name|offset_x
argument_list|)
expr_stmt|;
name|src_rect
operator|.
name|height
operator|=
name|ABS
argument_list|(
name|offset_y
argument_list|)
expr_stmt|;
name|dest_rect
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|dest_rect
operator|.
name|y
operator|=
name|dest_y
expr_stmt|;
block|}
name|gegl_buffer_copy
argument_list|(
name|src_buffer
argument_list|,
operator|&
name|src_rect
argument_list|,
name|dest_buffer
argument_list|,
operator|&
name|dest_rect
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/*  Otherwise, fill the vacated regions  */
name|gegl_buffer_flush
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|fill_type
operator|==
name|GIMP_OFFSET_BACKGROUND
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_context_get_background
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|fill
index|[
literal|0
index|]
argument_list|,
operator|&
name|fill
index|[
literal|1
index|]
argument_list|,
operator|&
name|fill
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|fill
index|[
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
operator|-
literal|1
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
block|}
if|if
condition|(
name|offset_x
operator|>=
literal|0
operator|&&
name|offset_y
operator|>=
literal|0
condition|)
block|{
name|dest_x
operator|=
literal|0
expr_stmt|;
name|dest_y
operator|=
literal|0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|offset_x
operator|>=
literal|0
operator|&&
name|offset_y
operator|<
literal|0
condition|)
block|{
name|dest_x
operator|=
literal|0
expr_stmt|;
name|dest_y
operator|=
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|+
name|offset_y
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|offset_x
operator|<
literal|0
operator|&&
name|offset_y
operator|>=
literal|0
condition|)
block|{
name|dest_x
operator|=
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|+
name|offset_x
expr_stmt|;
name|dest_y
operator|=
literal|0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|offset_x
operator|<
literal|0
operator|&&
name|offset_y
operator|<
literal|0
condition|)
block|{
name|dest_x
operator|=
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|+
name|offset_x
expr_stmt|;
name|dest_y
operator|=
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|+
name|offset_y
expr_stmt|;
block|}
comment|/*  intersecting region  */
if|if
condition|(
name|offset_x
operator|!=
literal|0
operator|&&
name|offset_y
operator|!=
literal|0
condition|)
block|{
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|new_tiles
argument_list|,
name|dest_x
argument_list|,
name|dest_y
argument_list|,
name|ABS
argument_list|(
name|offset_x
argument_list|)
argument_list|,
name|ABS
argument_list|(
name|offset_y
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|destPR
argument_list|,
name|fill
argument_list|)
expr_stmt|;
block|}
comment|/*  X offset  */
if|if
condition|(
name|offset_x
operator|!=
literal|0
condition|)
block|{
if|if
condition|(
name|offset_y
operator|>=
literal|0
condition|)
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|new_tiles
argument_list|,
name|dest_x
argument_list|,
name|dest_y
operator|+
name|offset_y
argument_list|,
name|ABS
argument_list|(
name|offset_x
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|-
name|ABS
argument_list|(
name|offset_y
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|offset_y
operator|<
literal|0
condition|)
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|new_tiles
argument_list|,
name|dest_x
argument_list|,
literal|0
argument_list|,
name|ABS
argument_list|(
name|offset_x
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|-
name|ABS
argument_list|(
name|offset_y
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|destPR
argument_list|,
name|fill
argument_list|)
expr_stmt|;
block|}
comment|/*  X offset  */
if|if
condition|(
name|offset_y
operator|!=
literal|0
condition|)
block|{
if|if
condition|(
name|offset_x
operator|>=
literal|0
condition|)
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|new_tiles
argument_list|,
name|dest_x
operator|+
name|offset_x
argument_list|,
name|dest_y
argument_list|,
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|-
name|ABS
argument_list|(
name|offset_x
argument_list|)
argument_list|,
name|ABS
argument_list|(
name|offset_y
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|offset_x
operator|<
literal|0
condition|)
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|new_tiles
argument_list|,
literal|0
argument_list|,
name|dest_y
argument_list|,
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|-
name|ABS
argument_list|(
name|offset_x
argument_list|)
argument_list|,
name|ABS
argument_list|(
name|offset_y
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|destPR
argument_list|,
name|fill
argument_list|)
expr_stmt|;
block|}
block|}
name|g_object_unref
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
name|gimp_drawable_set_tiles
argument_list|(
name|drawable
argument_list|,
name|gimp_item_is_attached
argument_list|(
name|item
argument_list|)
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Offset Drawable"
argument_list|)
argument_list|,
name|new_tiles
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|tile_manager_unref
argument_list|(
name|new_tiles
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

