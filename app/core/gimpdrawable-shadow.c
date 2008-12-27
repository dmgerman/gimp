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
file|<gegl.h>
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
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-shadow.h"
end_include

begin_function
name|TileManager
modifier|*
DECL|function|gimp_drawable_get_shadow_tiles (GimpDrawable * drawable)
name|gimp_drawable_get_shadow_tiles
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|shadow
condition|)
block|{
if|if
condition|(
operator|(
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|!=
name|tile_manager_width
argument_list|(
name|drawable
operator|->
name|shadow
argument_list|)
operator|)
operator|||
operator|(
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|!=
name|tile_manager_height
argument_list|(
name|drawable
operator|->
name|shadow
argument_list|)
operator|)
operator|||
operator|(
name|drawable
operator|->
name|bytes
operator|!=
name|tile_manager_bpp
argument_list|(
name|drawable
operator|->
name|shadow
argument_list|)
operator|)
condition|)
block|{
name|gimp_drawable_free_shadow_tiles
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
else|else
block|{
return|return
name|drawable
operator|->
name|shadow
return|;
block|}
block|}
name|drawable
operator|->
name|shadow
operator|=
name|tile_manager_new
argument_list|(
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
argument_list|,
name|drawable
operator|->
name|bytes
argument_list|)
expr_stmt|;
return|return
name|drawable
operator|->
name|shadow
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_free_shadow_tiles (GimpDrawable * drawable)
name|gimp_drawable_free_shadow_tiles
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|shadow
condition|)
block|{
name|tile_manager_unref
argument_list|(
name|drawable
operator|->
name|shadow
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|shadow
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_merge_shadow_tiles (GimpDrawable * drawable,gboolean push_undo,const gchar * undo_desc)
name|gimp_drawable_merge_shadow_tiles
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
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
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|drawable
operator|->
name|shadow
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/*  A useful optimization here is to limit the update to the    *  extents of the selection mask, as it cannot extend beyond    *  them.    */
if|if
condition|(
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
block|{
name|TileManager
modifier|*
name|tiles
init|=
name|tile_manager_ref
argument_list|(
name|drawable
operator|->
name|shadow
argument_list|)
decl_stmt|;
name|PixelRegion
name|shadowPR
decl_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|shadowPR
argument_list|,
name|tiles
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_region
argument_list|(
name|drawable
argument_list|,
operator|&
name|shadowPR
argument_list|,
name|push_undo
argument_list|,
name|undo_desc
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_REPLACE_MODE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|tile_manager_unref
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

