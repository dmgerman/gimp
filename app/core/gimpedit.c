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
file|<stdlib.h>
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
file|"base/tile-manager-crop.h"
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
file|"gimpbuffer.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpedit.h"
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
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GimpBuffer
modifier|*
DECL|function|gimp_edit_cut (GimpImage * gimage,GimpDrawable * drawable)
name|gimp_edit_cut
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|TileManager
modifier|*
name|cut
decl_stmt|;
name|TileManager
modifier|*
name|cropped_cut
decl_stmt|;
name|gboolean
name|empty
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
comment|/*  Start a group undo  */
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_CUT
argument_list|,
name|_
argument_list|(
literal|"Cut"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  See if the gimage mask is empty  */
name|empty
operator|=
name|gimp_image_mask_is_empty
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/*  Next, cut the mask portion from the gimage  */
name|cut
operator|=
name|gimp_image_mask_extract
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|cut
condition|)
name|gimage
operator|->
name|gimp
operator|->
name|have_current_cut_buffer
operator|=
name|TRUE
expr_stmt|;
comment|/*  Only crop if the gimage mask wasn't empty  */
if|if
condition|(
name|cut
operator|&&
operator|!
name|empty
condition|)
block|{
name|cropped_cut
operator|=
name|tile_manager_crop
argument_list|(
name|cut
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|cropped_cut
operator|!=
name|cut
condition|)
block|{
name|tile_manager_unref
argument_list|(
name|cut
argument_list|)
expr_stmt|;
name|cut
operator|=
name|NULL
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|cut
condition|)
name|cropped_cut
operator|=
name|cut
expr_stmt|;
else|else
name|cropped_cut
operator|=
name|NULL
expr_stmt|;
comment|/*  end the group undo  */
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|cropped_cut
condition|)
block|{
comment|/*  Free the old global edit buffer  */
if|if
condition|(
name|gimage
operator|->
name|gimp
operator|->
name|global_buffer
condition|)
name|g_object_unref
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|global_buffer
argument_list|)
expr_stmt|;
comment|/*  Set the global edit buffer  */
name|gimage
operator|->
name|gimp
operator|->
name|global_buffer
operator|=
name|gimp_buffer_new
argument_list|(
name|cropped_cut
argument_list|,
literal|"Global Buffer"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_buffer_new
argument_list|(
name|cropped_cut
argument_list|,
literal|"Cut Pixels"
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpBuffer
modifier|*
DECL|function|gimp_edit_copy (GimpImage * gimage,GimpDrawable * drawable)
name|gimp_edit_copy
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|TileManager
modifier|*
name|copy
decl_stmt|;
name|TileManager
modifier|*
name|cropped_copy
decl_stmt|;
name|gboolean
name|empty
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
comment|/*  Start a group undo  */
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_COPY
argument_list|,
name|_
argument_list|(
literal|"Copy"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  See if the gimage mask is empty  */
name|empty
operator|=
name|gimp_image_mask_is_empty
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/*  First, copy the masked portion of the gimage  */
name|copy
operator|=
name|gimp_image_mask_extract
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|copy
condition|)
name|gimage
operator|->
name|gimp
operator|->
name|have_current_cut_buffer
operator|=
name|TRUE
expr_stmt|;
comment|/*  Only crop if the gimage mask wasn't empty  */
if|if
condition|(
name|copy
operator|&&
operator|!
name|empty
condition|)
block|{
name|cropped_copy
operator|=
name|tile_manager_crop
argument_list|(
name|copy
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|cropped_copy
operator|!=
name|copy
condition|)
block|{
name|tile_manager_unref
argument_list|(
name|copy
argument_list|)
expr_stmt|;
name|copy
operator|=
name|NULL
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|copy
condition|)
name|cropped_copy
operator|=
name|copy
expr_stmt|;
else|else
name|cropped_copy
operator|=
name|NULL
expr_stmt|;
comment|/*  end the group undo  */
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|cropped_copy
condition|)
block|{
comment|/*  Free the old global edit buffer  */
if|if
condition|(
name|gimage
operator|->
name|gimp
operator|->
name|global_buffer
condition|)
name|g_object_unref
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|global_buffer
argument_list|)
expr_stmt|;
comment|/*  Set the global edit buffer  */
name|gimage
operator|->
name|gimp
operator|->
name|global_buffer
operator|=
name|gimp_buffer_new
argument_list|(
name|cropped_copy
argument_list|,
literal|"Global Buffer"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_buffer_new
argument_list|(
name|cropped_copy
argument_list|,
literal|"Copied Pixels"
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_edit_paste (GimpImage * gimage,GimpDrawable * drawable,GimpBuffer * paste,gboolean paste_into)
name|gimp_edit_paste
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpBuffer
modifier|*
name|paste
parameter_list|,
name|gboolean
name|paste_into
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpImageType
name|type
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
name|cx
decl_stmt|,
name|cy
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
operator|!
name|drawable
operator|||
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Make a new layer: if drawable == NULL,    *  user is pasting into an empty image.    */
if|if
condition|(
name|drawable
condition|)
name|type
operator|=
name|gimp_drawable_type_with_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
else|else
name|type
operator|=
name|gimp_image_base_type_with_alpha
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new_from_tiles
argument_list|(
name|paste
operator|->
name|tiles
argument_list|,
name|gimage
argument_list|,
name|type
argument_list|,
name|_
argument_list|(
literal|"Pasted Layer"
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|layer
condition|)
return|return
name|NULL
return|;
comment|/*  Start a group undo  */
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_PASTE
argument_list|,
name|_
argument_list|(
literal|"Paste"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Set the offsets to the center of the image  */
if|if
condition|(
name|drawable
condition|)
block|{
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|cx
argument_list|,
operator|&
name|cy
argument_list|)
expr_stmt|;
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
name|cx
operator|+=
operator|(
name|x1
operator|+
name|x2
operator|)
operator|>>
literal|1
expr_stmt|;
name|cy
operator|+=
operator|(
name|y1
operator|+
name|y2
operator|)
operator|>>
literal|1
expr_stmt|;
block|}
else|else
block|{
name|cx
operator|=
name|gimage
operator|->
name|width
operator|>>
literal|1
expr_stmt|;
name|cy
operator|=
name|gimage
operator|->
name|height
operator|>>
literal|1
expr_stmt|;
block|}
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
operator|=
name|cx
operator|-
operator|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|width
operator|>>
literal|1
operator|)
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
operator|=
name|cy
operator|-
operator|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|height
operator|>>
literal|1
operator|)
expr_stmt|;
comment|/*  If there is a selection mask clear it--    *  this might not always be desired, but in general,    *  it seems like the correct behavior.    */
if|if
condition|(
operator|!
name|gimp_image_mask_is_empty
argument_list|(
name|gimage
argument_list|)
operator|&&
operator|!
name|paste_into
condition|)
name|gimp_channel_clear
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  if there's a drawable, add a new floating selection  */
if|if
condition|(
name|drawable
operator|!=
name|NULL
condition|)
block|{
name|floating_sel_attach
argument_list|(
name|layer
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_item_set_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|gimage
argument_list|,
name|layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
comment|/*  end the group undo  */
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_edit_paste_as_new (Gimp * gimp,GimpImage * invoke,GimpBuffer * paste)
name|gimp_edit_paste_as_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|invoke
parameter_list|,
name|GimpBuffer
modifier|*
name|paste
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
comment|/*  create a new image  (always of type GIMP_RGB)  */
name|gimage
operator|=
name|gimp_create_image
argument_list|(
name|gimp
argument_list|,
name|gimp_buffer_get_width
argument_list|(
name|paste
argument_list|)
argument_list|,
name|gimp_buffer_get_height
argument_list|(
name|paste
argument_list|)
argument_list|,
name|GIMP_RGB
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|invoke
condition|)
block|{
name|gimp_image_set_resolution
argument_list|(
name|gimage
argument_list|,
name|invoke
operator|->
name|xresolution
argument_list|,
name|invoke
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|gimage
argument_list|,
name|invoke
operator|->
name|unit
argument_list|)
expr_stmt|;
block|}
name|layer
operator|=
name|gimp_layer_new_from_tiles
argument_list|(
name|paste
operator|->
name|tiles
argument_list|,
name|gimage
argument_list|,
name|gimp_image_base_type_with_alpha
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Pasted Layer"
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
condition|)
block|{
name|gimp_item_set_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|gimage
argument_list|,
name|layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|gimp
argument_list|,
name|gimage
argument_list|,
literal|0x0101
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|gimage
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_edit_clear (GimpImage * gimage,GimpDrawable * drawable)
name|gimp_edit_clear
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|TileManager
modifier|*
name|buf_tiles
decl_stmt|;
name|PixelRegion
name|bufPR
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
name|guchar
name|col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_get_background
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|col
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|col
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
condition|)
return|return
name|TRUE
return|;
comment|/*  nothing to do, but the clear succeded  */
name|buf_tiles
operator|=
name|tile_manager_new
argument_list|(
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
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|bufPR
argument_list|,
name|buf_tiles
argument_list|,
literal|0
argument_list|,
literal|0
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
name|TRUE
argument_list|)
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|bufPR
argument_list|,
name|col
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|bufPR
argument_list|,
name|buf_tiles
argument_list|,
literal|0
argument_list|,
literal|0
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
name|gimp_image_apply_image
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
operator|&
name|bufPR
argument_list|,
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Clear"
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_ERASE_MODE
argument_list|,
name|NULL
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
comment|/*  update the image  */
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
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
comment|/*  free the temporary tiles  */
name|tile_manager_unref
argument_list|(
name|buf_tiles
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_edit_fill (GimpImage * gimage,GimpDrawable * drawable,GimpFillType fill_type)
name|gimp_edit_fill
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpFillType
name|fill_type
parameter_list|)
block|{
name|TileManager
modifier|*
name|buf_tiles
decl_stmt|;
name|PixelRegion
name|bufPR
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
name|guchar
name|col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|undo_desc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|col
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
switch|switch
condition|(
name|fill_type
condition|)
block|{
case|case
name|GIMP_FOREGROUND_FILL
case|:
name|gimp_image_get_foreground
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|col
argument_list|)
expr_stmt|;
name|undo_desc
operator|=
name|_
argument_list|(
literal|"Fill with FG Color"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_BACKGROUND_FILL
case|:
name|gimp_image_get_background
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|col
argument_list|)
expr_stmt|;
name|undo_desc
operator|=
name|_
argument_list|(
literal|"Fill with BG Color"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_WHITE_FILL
case|:
name|col
index|[
name|RED_PIX
index|]
operator|=
literal|255
expr_stmt|;
name|col
index|[
name|GREEN_PIX
index|]
operator|=
literal|255
expr_stmt|;
name|col
index|[
name|BLUE_PIX
index|]
operator|=
literal|255
expr_stmt|;
name|undo_desc
operator|=
name|_
argument_list|(
literal|"Fill with White"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TRANSPARENT_FILL
case|:
name|col
index|[
name|RED_PIX
index|]
operator|=
literal|0
expr_stmt|;
name|col
index|[
name|GREEN_PIX
index|]
operator|=
literal|0
expr_stmt|;
name|col
index|[
name|BLUE_PIX
index|]
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|col
index|[
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
operator|-
literal|1
index|]
operator|=
name|TRANSPARENT_OPACITY
expr_stmt|;
name|undo_desc
operator|=
name|_
argument_list|(
literal|"Fill with Transparency"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_NO_FILL
case|:
return|return
name|TRUE
return|;
comment|/*  nothing to do, but the fill succeded  */
default|default:
name|g_warning
argument_list|(
literal|"%s: unknown fill type"
argument_list|,
name|G_GNUC_PRETTY_FUNCTION
argument_list|)
expr_stmt|;
name|gimp_image_get_background
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|col
argument_list|)
expr_stmt|;
name|undo_desc
operator|=
name|_
argument_list|(
literal|"Fill with BG Color"
argument_list|)
expr_stmt|;
break|break;
block|}
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
condition|)
return|return
name|TRUE
return|;
comment|/*  nothing to do, but the fill succeded  */
name|buf_tiles
operator|=
name|tile_manager_new
argument_list|(
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
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|bufPR
argument_list|,
name|buf_tiles
argument_list|,
literal|0
argument_list|,
literal|0
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
name|TRUE
argument_list|)
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|bufPR
argument_list|,
name|col
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|bufPR
argument_list|,
name|buf_tiles
argument_list|,
literal|0
argument_list|,
literal|0
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
name|gimp_image_apply_image
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
operator|&
name|bufPR
argument_list|,
name|TRUE
argument_list|,
name|undo_desc
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|NULL
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
comment|/*  update the image  */
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
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
comment|/*  free the temporary tiles  */
name|tile_manager_unref
argument_list|(
name|buf_tiles
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

