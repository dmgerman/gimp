begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/boundary.h"
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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-mask.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo-push.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer-floating-sel.h"
end_include

begin_include
include|#
directive|include
file|"gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"gimpselection.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_image_mask_push_undo (GimpImage * gimage,const gchar * undo_desc)
name|gimp_image_mask_push_undo
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_selection_push_undo
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|undo_desc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_mask_invalidate (GimpImage * gimage)
name|gimp_image_mask_invalidate
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_selection_invalidate
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|TileManager
modifier|*
DECL|function|gimp_image_mask_extract (GimpImage * gimage,GimpDrawable * drawable,gboolean cut_image,gboolean keep_indexed,gboolean add_alpha)
name|gimp_image_mask_extract
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|cut_image
parameter_list|,
name|gboolean
name|keep_indexed
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
block|{
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|GimpChannel
modifier|*
name|sel_mask
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|,
name|maskPR
decl_stmt|;
name|guchar
name|bg_color
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|GimpImageBaseType
name|base_type
init|=
name|GIMP_RGB
decl_stmt|;
name|gint
name|bytes
init|=
literal|0
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gboolean
name|non_empty
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
comment|/*  If there are no bounds, then just extract the entire image    *  This may not be the correct behavior, but after getting rid    *  of floating selections, it's still tempting to "cut" or "copy"    *  a small layer and expect it to work, even though there is no    *  actual selection mask    */
name|non_empty
operator|=
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
if|if
condition|(
name|non_empty
operator|&&
operator|(
operator|!
operator|(
name|x2
operator|-
name|x1
operator|)
operator|||
operator|!
operator|(
name|y2
operator|-
name|y1
operator|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Unable to cut or copy because the\n"
literal|"selected region is empty."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/*  How many bytes in the temp buffer?  */
switch|switch
condition|(
name|GIMP_IMAGE_TYPE_BASE_TYPE
argument_list|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB
case|:
name|bytes
operator|=
name|add_alpha
condition|?
literal|4
else|:
name|drawable
operator|->
name|bytes
expr_stmt|;
name|base_type
operator|=
name|GIMP_RGB
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY
case|:
name|bytes
operator|=
name|add_alpha
condition|?
literal|2
else|:
name|drawable
operator|->
name|bytes
expr_stmt|;
name|base_type
operator|=
name|GIMP_GRAY
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED
case|:
if|if
condition|(
name|keep_indexed
condition|)
block|{
name|bytes
operator|=
name|add_alpha
condition|?
literal|2
else|:
name|drawable
operator|->
name|bytes
expr_stmt|;
name|base_type
operator|=
name|GIMP_GRAY
expr_stmt|;
block|}
else|else
block|{
name|bytes
operator|=
name|add_alpha
condition|?
literal|4
else|:
name|drawable
operator|->
name|bytes
expr_stmt|;
name|base_type
operator|=
name|GIMP_INDEXED
expr_stmt|;
block|}
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
break|break;
block|}
comment|/*  get the selection mask */
if|if
condition|(
name|non_empty
condition|)
name|sel_mask
operator|=
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
else|else
name|sel_mask
operator|=
name|NULL
expr_stmt|;
name|gimp_image_get_background
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|bg_color
argument_list|)
expr_stmt|;
comment|/*  If a cut was specified, and the selection mask is not empty,    *  push an undo    */
if|if
condition|(
name|cut_image
operator|&&
name|non_empty
condition|)
name|gimp_drawable_push_undo
argument_list|(
name|drawable
argument_list|,
name|NULL
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
comment|/*  Allocate the temp buffer  */
name|tiles
operator|=
name|tile_manager_new
argument_list|(
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
name|tile_manager_set_offsets
argument_list|(
name|tiles
argument_list|,
name|x1
operator|+
name|off_x
argument_list|,
name|y1
operator|+
name|off_y
argument_list|)
expr_stmt|;
comment|/* configure the pixel regions  */
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|cut_image
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|non_empty
condition|)
comment|/*  If there is a selection, extract from it  */
block|{
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|sel_mask
argument_list|)
operator|->
name|tiles
argument_list|,
operator|(
name|x1
operator|+
name|off_x
operator|)
argument_list|,
operator|(
name|y1
operator|+
name|off_y
operator|)
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|extract_from_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|,
operator|&
name|maskPR
argument_list|,
name|gimp_drawable_cmap
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|bg_color
argument_list|,
name|base_type
argument_list|,
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|cut_image
argument_list|)
expr_stmt|;
if|if
condition|(
name|cut_image
condition|)
block|{
comment|/*  Clear the region  */
name|gimp_channel_clear
argument_list|(
name|sel_mask
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  Update the region  */
name|gimp_image_update
argument_list|(
name|gimage
argument_list|,
name|x1
operator|+
name|off_x
argument_list|,
name|y1
operator|+
name|off_y
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|)
expr_stmt|;
comment|/*  Invalidate the preview  */
name|gimp_viewable_invalidate_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
else|else
comment|/*  Otherwise, get the entire active layer  */
block|{
comment|/*  If the layer is indexed...we need to extract pixels  */
if|if
condition|(
name|base_type
operator|==
name|GIMP_INDEXED
operator|&&
operator|!
name|keep_indexed
condition|)
name|extract_from_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|,
name|NULL
argument_list|,
name|gimp_drawable_cmap
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|bg_color
argument_list|,
name|base_type
argument_list|,
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  If the layer doesn't have an alpha channel, add one  */
elseif|else
if|if
condition|(
name|bytes
operator|>
name|srcPR
operator|.
name|bytes
condition|)
name|add_alpha_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
comment|/*  Otherwise, do a straight copy  */
else|else
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
comment|/*  If we're cutting, remove either the layer (or floating selection),        *  the layer mask, or the channel        */
if|if
condition|(
name|cut_image
condition|)
block|{
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
if|if
condition|(
name|gimp_layer_is_floating_sel
argument_list|(
name|GIMP_LAYER
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
name|floating_sel_remove
argument_list|(
name|GIMP_LAYER
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimp_image_remove_layer
argument_list|(
name|gimage
argument_list|,
name|GIMP_LAYER
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|gimp_layer_apply_mask
argument_list|(
name|gimp_layer_mask_get_layer
argument_list|(
name|GIMP_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|GIMP_MASK_DISCARD
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_CHANNEL
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|gimp_image_remove_channel
argument_list|(
name|gimage
argument_list|,
name|GIMP_CHANNEL
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
return|return
name|tiles
return|;
block|}
end_function

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_image_mask_float (GimpImage * gimage,GimpDrawable * drawable,gboolean cut_image,gint off_x,gint off_y)
name|gimp_image_mask_float
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|cut_image
parameter_list|,
name|gint
name|off_x
parameter_list|,
comment|/* optional offset */
name|gint
name|off_y
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpChannel
modifier|*
name|mask
init|=
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
decl_stmt|;
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|gboolean
name|non_empty
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  Make sure there is a region to float...  */
name|non_empty
operator|=
name|gimp_drawable_mask_bounds
argument_list|(
operator|(
name|drawable
operator|)
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|non_empty
operator|||
operator|(
name|x2
operator|-
name|x1
operator|)
operator|==
literal|0
operator|||
operator|(
name|y2
operator|-
name|y1
operator|)
operator|==
literal|0
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Cannot float selection because the\n"
literal|"selected region is empty."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/*  Start an undo group  */
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_FS_FLOAT
argument_list|,
name|_
argument_list|(
literal|"Float Selection"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Cut or copy the selected region  */
name|tiles
operator|=
name|gimp_image_mask_extract
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|cut_image
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  Clear the selection as if we had cut the pixels  */
if|if
condition|(
operator|!
name|cut_image
condition|)
name|gimp_channel_clear
argument_list|(
name|mask
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* Create a new layer from the buffer, using the drawable's type    *  because it may be different from the image's type if we cut from    *  a channel or layer mask    */
name|layer
operator|=
name|gimp_layer_new_from_tiles
argument_list|(
name|tiles
argument_list|,
name|gimage
argument_list|,
name|gimp_drawable_type_with_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Floating Selection"
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
comment|/*  Set the offsets  */
name|tile_manager_get_offsets
argument_list|(
name|tiles
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
operator|=
name|x1
operator|+
name|off_x
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
operator|=
name|y1
operator|+
name|off_y
expr_stmt|;
comment|/*  Free the temp buffer  */
name|tile_manager_unref
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
comment|/*  Add the floating layer to the gimage  */
name|floating_sel_attach
argument_list|(
name|layer
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
comment|/*  End an undo group  */
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/*  invalidate the gimage's boundary variables  */
name|mask
operator|->
name|boundary_known
operator|=
name|FALSE
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_mask_load (GimpImage * gimage,GimpChannel * channel)
name|gimp_image_mask_load
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_mask_push_undo
argument_list|(
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Selection from Channel"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  load the specified channel to the gimage mask  */
name|gimp_channel_load
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|channel
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_mask_changed
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpChannel
modifier|*
DECL|function|gimp_image_mask_save (GimpImage * gimage)
name|gimp_image_mask_save
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
name|GimpChannel
modifier|*
name|new_channel
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|new_channel
operator|=
name|GIMP_CHANNEL
argument_list|(
name|gimp_item_duplicate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|,
name|GIMP_TYPE_CHANNEL
argument_list|,
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  saved selections are not visible by default  */
name|gimp_drawable_set_visible
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|new_channel
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_add_channel
argument_list|(
name|gimage
argument_list|,
name|new_channel
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|new_channel
return|;
block|}
end_function

end_unit

