begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"channels_dialog.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"layer.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"floating_sel.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask.h"
end_include

begin_include
include|#
directive|include
file|"interface.h"
end_include

begin_include
include|#
directive|include
file|"paint_funcs.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"layer_pvt.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager_pvt.h"
end_include

begin_comment
comment|/* ick. */
end_comment

begin_function
name|void
DECL|function|floating_sel_attach (Layer * layer,GimpDrawable * drawable)
name|floating_sel_attach
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|Layer
modifier|*
name|floating_sel
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return;
comment|/*  If there is already a floating selection, anchor it  */
if|if
condition|(
name|gimage
operator|->
name|floating_sel
operator|!=
name|NULL
condition|)
block|{
name|floating_sel
operator|=
name|gimage
operator|->
name|floating_sel
expr_stmt|;
name|floating_sel_anchor
argument_list|(
name|gimage_floating_sel
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  if we were pasting to the old floating selection, paste now to the drawable  */
if|if
condition|(
name|drawable
operator|==
name|GIMP_DRAWABLE
argument_list|(
name|floating_sel
argument_list|)
condition|)
name|drawable
operator|=
name|gimage_active_drawable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
comment|/*  set the drawable and allocate a backing store  */
name|layer
operator|->
name|preserve_trans
operator|=
name|TRUE
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|drawable
operator|=
name|drawable
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|backing_store
operator|=
name|tile_manager_new
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|height
argument_list|,
name|drawable_bytes
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  because setting the sensitivity in the layers_dialog lock call redraws the    *  previews, we need to lock the dialogs before the floating sel is actually added.    *  however, they won't lock unless we set the gimage's floating sel pointer    */
name|gimage
operator|->
name|floating_sel
operator|=
name|layer
expr_stmt|;
comment|/*  add the layer to the gimage  */
name|gimage_add_layer
argument_list|(
name|gimage
argument_list|,
name|layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  store the affected area from the drawable in the backing store  */
name|floating_sel_rigor
argument_list|(
name|layer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|floating_sel_remove (Layer * layer)
name|floating_sel_remove
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
operator|(
name|layer
operator|->
name|fs
operator|.
name|drawable
operator|)
argument_list|)
operator|)
condition|)
return|return;
comment|/*  store the affected area from the drawable in the backing store  */
name|floating_sel_relax
argument_list|(
name|layer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  invalidate the preview of the obscured drawable.  We do this here    *  because it will not be done until the floating selection is removed,    *  at which point the obscured drawable's preview will not be declared invalid    */
name|drawable_invalidate_preview
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  remove the layer from the gimage  */
name|gimage_remove_layer
argument_list|(
name|gimage
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|floating_sel_anchor (Layer * layer)
name|floating_sel_anchor
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
condition|)
return|return;
if|if
condition|(
operator|!
name|layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"Cannot anchor this layer because\nit is not a floating selection."
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  Start a floating selection anchoring undo  */
name|undo_push_group_start
argument_list|(
name|gimage
argument_list|,
name|FS_ANCHOR_UNDO
argument_list|)
expr_stmt|;
comment|/*  Relax the floating selection  */
name|floating_sel_relax
argument_list|(
name|layer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  Composite the floating selection contents  */
name|floating_sel_composite
argument_list|(
name|layer
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  remove the floating selection  */
name|gimage_remove_layer
argument_list|(
name|gimage
argument_list|,
name|layer
argument_list|)
expr_stmt|;
comment|/*  end the group undo  */
name|undo_push_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/*  invalidate the boundaries  */
name|gimage_mask_invalidate
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|floating_sel_reset (layer)
name|floating_sel_reset
parameter_list|(
name|layer
parameter_list|)
name|Layer
modifier|*
name|layer
decl_stmt|;
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
condition|)
return|return;
comment|/*  set the underlying drawable to active  */
if|if
condition|(
name|drawable_layer
argument_list|(
operator|(
name|layer
operator|->
name|fs
operator|.
name|drawable
operator|)
argument_list|)
condition|)
name|gimage_set_active_layer
argument_list|(
name|gimage
argument_list|,
name|GIMP_LAYER
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
condition|)
name|gimage_set_active_layer
argument_list|(
name|gimage
argument_list|,
name|GIMP_LAYER_MASK
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
operator|->
name|layer
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|drawable_channel
argument_list|(
operator|(
name|layer
operator|->
name|fs
operator|.
name|drawable
operator|)
argument_list|)
condition|)
block|{
name|gimage_set_active_channel
argument_list|(
name|gimage
argument_list|,
name|GIMP_CHANNEL
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|->
name|layers
condition|)
name|gimage
operator|->
name|active_layer
operator|=
operator|(
operator|(
operator|(
name|Layer
operator|*
operator|)
name|gimage
operator|->
name|layer_stack
operator|->
name|data
operator|)
operator|)
expr_stmt|;
else|else
name|gimage
operator|->
name|active_layer
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|floating_sel_to_layer (Layer * layer)
name|floating_sel_to_layer
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|)
block|{
name|FStoLayerUndo
modifier|*
name|fsu
decl_stmt|;
name|int
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
name|GImage
modifier|*
name|gimage
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
condition|)
return|return;
comment|/*  Check if the floating layer belongs to a channel...  */
if|if
condition|(
name|drawable_channel
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
operator|||
name|drawable_layer_mask
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"Cannot create a new layer from the floating\n"
literal|"selection because it belongs to a\n"
literal|"layer mask or channel."
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  restore the contents of the drawable  */
name|floating_sel_restore
argument_list|(
name|layer
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/*  determine whether the resulting layer needs an update  */
name|drawable_offsets
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|width
operator|=
name|drawable_width
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
expr_stmt|;
name|height
operator|=
name|drawable_height
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
expr_stmt|;
comment|/*  update the fs drawable--this updates the gimage composite preview    *  as well as the underlying drawable's    */
name|drawable_invalidate_preview
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  allocate the undo structure  */
name|fsu
operator|=
operator|(
name|FStoLayerUndo
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|FStoLayerUndo
argument_list|)
argument_list|)
expr_stmt|;
name|fsu
operator|->
name|layer
operator|=
name|layer
expr_stmt|;
name|fsu
operator|->
name|drawable
operator|=
name|layer
operator|->
name|fs
operator|.
name|drawable
expr_stmt|;
name|undo_push_fs_to_layer
argument_list|(
name|gimage
argument_list|,
name|fsu
argument_list|)
expr_stmt|;
comment|/*  clear the selection  */
name|layer_invalidate_boundary
argument_list|(
name|layer
argument_list|)
expr_stmt|;
comment|/*  Set pointers  */
name|layer
operator|->
name|fs
operator|.
name|drawable
operator|=
name|NULL
expr_stmt|;
name|gimage
operator|->
name|floating_sel
operator|=
name|NULL
expr_stmt|;
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|visible
operator|=
name|TRUE
expr_stmt|;
comment|/*  if the floating selection exceeds the attached layer's extents,       update the new layer  */
comment|/*  I don't think that the preview is ever valid as is, since the layer       will be added on top of the others.  Revert this if I'm wrong.       msw@gimp.org   */
name|drawable_update
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|floating_sel_store (Layer * layer,int x,int y,int w,int h)
name|floating_sel_store
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|)
block|{
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|int
name|offx
decl_stmt|,
name|offy
decl_stmt|;
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  Check the backing store& make sure it has the correct dimensions  */
if|if
condition|(
name|layer
operator|->
name|fs
operator|.
name|backing_store
operator|->
name|levels
index|[
literal|0
index|]
operator|.
name|width
operator|!=
name|drawable_width
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|||
name|layer
operator|->
name|fs
operator|.
name|backing_store
operator|->
name|levels
index|[
literal|0
index|]
operator|.
name|height
operator|!=
name|drawable_height
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|||
name|layer
operator|->
name|fs
operator|.
name|backing_store
operator|->
name|levels
index|[
literal|0
index|]
operator|.
name|bpp
operator|!=
name|drawable_bytes
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
condition|)
block|{
comment|/*  free the backing store and allocate anew  */
name|tile_manager_destroy
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|backing_store
argument_list|)
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|backing_store
operator|=
name|tile_manager_new
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|height
argument_list|,
name|drawable_bytes
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*  What this function does is save the specified area of the    *  drawable that this floating selection obscures.  We do this so    *  that it will be possible to subsequently restore the drawable's area    */
name|drawable_offsets
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|,
operator|&
name|offx
argument_list|,
operator|&
name|offy
argument_list|)
expr_stmt|;
comment|/*  Find the minimum area we need to uncover -- in gimage space  */
name|x1
operator|=
name|MAXIMUM
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
argument_list|,
name|offx
argument_list|)
expr_stmt|;
name|y1
operator|=
name|MAXIMUM
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
argument_list|,
name|offy
argument_list|)
expr_stmt|;
name|x2
operator|=
name|MINIMUM
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
operator|+
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|width
argument_list|,
name|offx
operator|+
name|drawable_width
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|MINIMUM
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
operator|+
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|height
argument_list|,
name|offy
operator|+
name|drawable_height
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|x1
operator|=
name|BOUNDS
argument_list|(
name|x
argument_list|,
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|y1
operator|=
name|BOUNDS
argument_list|(
name|y
argument_list|,
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|x2
operator|=
name|BOUNDS
argument_list|(
name|x
operator|+
name|w
argument_list|,
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|y2
operator|=
name|BOUNDS
argument_list|(
name|y
operator|+
name|h
argument_list|,
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|x2
operator|-
name|x1
operator|)
operator|>
literal|0
operator|&&
operator|(
name|y2
operator|-
name|y1
operator|)
operator|>
literal|0
condition|)
block|{
comment|/*  Copy the area from the drawable to the backing store  */
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable_data
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
argument_list|,
operator|(
name|x1
operator|-
name|offx
operator|)
argument_list|,
operator|(
name|y1
operator|-
name|offy
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
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|layer
operator|->
name|fs
operator|.
name|backing_store
argument_list|,
operator|(
name|x1
operator|-
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
operator|)
argument_list|,
operator|(
name|y1
operator|-
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
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
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|floating_sel_restore (Layer * layer,int x,int y,int w,int h)
name|floating_sel_restore
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|)
block|{
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|int
name|offx
decl_stmt|,
name|offy
decl_stmt|;
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  What this function does is "uncover" the specified area in the    *  drawable that this floating selection obscures.  We do this so    *  that either the floating selection can be removed or it can be    *  translated    */
comment|/*  Find the minimum area we need to uncover -- in gimage space  */
name|drawable_offsets
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|,
operator|&
name|offx
argument_list|,
operator|&
name|offy
argument_list|)
expr_stmt|;
name|x1
operator|=
name|MAXIMUM
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
argument_list|,
name|offx
argument_list|)
expr_stmt|;
name|y1
operator|=
name|MAXIMUM
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
argument_list|,
name|offy
argument_list|)
expr_stmt|;
name|x2
operator|=
name|MINIMUM
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
operator|+
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|width
argument_list|,
name|offx
operator|+
name|drawable_width
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|MINIMUM
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
operator|+
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|height
argument_list|,
name|offy
operator|+
name|drawable_height
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|x1
operator|=
name|BOUNDS
argument_list|(
name|x
argument_list|,
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|y1
operator|=
name|BOUNDS
argument_list|(
name|y
argument_list|,
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|x2
operator|=
name|BOUNDS
argument_list|(
name|x
operator|+
name|w
argument_list|,
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|y2
operator|=
name|BOUNDS
argument_list|(
name|y
operator|+
name|h
argument_list|,
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|x2
operator|-
name|x1
operator|)
operator|>
literal|0
operator|&&
operator|(
name|y2
operator|-
name|y1
operator|)
operator|>
literal|0
condition|)
block|{
comment|/*  Copy the area from the backing store to the drawable  */
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|layer
operator|->
name|fs
operator|.
name|backing_store
argument_list|,
operator|(
name|x1
operator|-
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
operator|)
argument_list|,
operator|(
name|y1
operator|-
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
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
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|drawable_data
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
argument_list|,
operator|(
name|x1
operator|-
name|offx
operator|)
argument_list|,
operator|(
name|y1
operator|-
name|offy
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
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|floating_sel_rigor (Layer * layer,int undo)
name|floating_sel_rigor
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|int
name|undo
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
init|=
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|gimage
decl_stmt|;
comment|/*  store the affected area from the drawable in the backing store  */
name|floating_sel_store
argument_list|(
name|layer
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|height
argument_list|)
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|initial
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|undo
condition|)
name|undo_push_fs_rigor
argument_list|(
name|gimage
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|ID
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|floating_sel_relax (Layer * layer,int undo)
name|floating_sel_relax
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|int
name|undo
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
init|=
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|gimage
decl_stmt|;
comment|/*  restore the contents of drawable the floating layer is attached to  */
if|if
condition|(
name|layer
operator|->
name|fs
operator|.
name|initial
operator|==
name|FALSE
condition|)
name|floating_sel_restore
argument_list|(
name|layer
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|height
argument_list|)
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|initial
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|undo
condition|)
name|undo_push_fs_relax
argument_list|(
name|gimage
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|ID
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|floating_sel_composite (Layer * layer,int x,int y,int w,int h,int undo)
name|floating_sel_composite
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|,
name|int
name|undo
parameter_list|)
block|{
name|PixelRegion
name|fsPR
decl_stmt|;
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|Layer
modifier|*
name|d_layer
decl_stmt|;
name|int
name|preserve_trans
decl_stmt|;
name|int
name|active
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|int
name|offx
decl_stmt|,
name|offy
decl_stmt|;
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|int
name|i
decl_stmt|;
name|d_layer
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
condition|)
return|return;
comment|/*  What this function does is composite the specified area of the    *  drawble with the floating selection.  We do this when the gimage    *  is constructed, before any other composition takes place.    */
comment|/*  If this isn't the first composite, restore the image underneath  */
if|if
condition|(
operator|!
name|layer
operator|->
name|fs
operator|.
name|initial
condition|)
name|floating_sel_restore
argument_list|(
name|layer
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|visible
condition|)
name|layer
operator|->
name|fs
operator|.
name|initial
operator|=
name|FALSE
expr_stmt|;
comment|/*  First restore what's behind the image if necessary, then check for visibility  */
if|if
condition|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|visible
condition|)
block|{
comment|/*  Find the minimum area we need to composite -- in gimage space  */
name|drawable_offsets
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|,
operator|&
name|offx
argument_list|,
operator|&
name|offy
argument_list|)
expr_stmt|;
name|x1
operator|=
name|MAXIMUM
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
argument_list|,
name|offx
argument_list|)
expr_stmt|;
name|y1
operator|=
name|MAXIMUM
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
argument_list|,
name|offy
argument_list|)
expr_stmt|;
name|x2
operator|=
name|MINIMUM
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
operator|+
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|width
argument_list|,
name|offx
operator|+
name|drawable_width
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|MINIMUM
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
operator|+
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|height
argument_list|,
name|offy
operator|+
name|drawable_height
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|x1
operator|=
name|BOUNDS
argument_list|(
name|x
argument_list|,
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|y1
operator|=
name|BOUNDS
argument_list|(
name|y
argument_list|,
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|x2
operator|=
name|BOUNDS
argument_list|(
name|x
operator|+
name|w
argument_list|,
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|y2
operator|=
name|BOUNDS
argument_list|(
name|y
operator|+
name|h
argument_list|,
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|x2
operator|-
name|x1
operator|)
operator|>
literal|0
operator|&&
operator|(
name|y2
operator|-
name|y1
operator|)
operator|>
literal|0
condition|)
block|{
comment|/*  composite the area from the layer to the drawable  */
name|pixel_region_init
argument_list|(
operator|&
name|fsPR
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|tiles
argument_list|,
operator|(
name|x1
operator|-
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
operator|)
argument_list|,
operator|(
name|y1
operator|-
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
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
comment|/*  a kludge here to prevent the case of the drawable 	   *  underneath having preserve transparency on, and disallowing 	   *  the composited floating selection from being shown 	   */
if|if
condition|(
name|drawable_layer
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
condition|)
block|{
name|d_layer
operator|=
name|GIMP_LAYER
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|preserve_trans
operator|=
name|d_layer
operator|->
name|preserve_trans
operator|)
condition|)
name|d_layer
operator|->
name|preserve_trans
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
name|preserve_trans
operator|=
name|FALSE
expr_stmt|;
comment|/*  We need to set all gimage channels to active to make sure that 	   *  nothing strange happens while applying the floating selection. 	   *  It wouldn't make sense for the floating selection to be affected 	   *  by the active gimage channels. 	   */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|MAX_CHANNELS
condition|;
name|i
operator|++
control|)
block|{
name|active
index|[
name|i
index|]
operator|=
name|gimage
operator|->
name|active
index|[
name|i
index|]
expr_stmt|;
name|gimage
operator|->
name|active
index|[
name|i
index|]
operator|=
literal|1
expr_stmt|;
block|}
comment|/*  apply the fs with the undo specified by the value 	   *  passed to this function 	   */
name|gimage_apply_image
argument_list|(
name|gimage
argument_list|,
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|,
operator|&
name|fsPR
argument_list|,
name|undo
argument_list|,
name|layer
operator|->
name|opacity
argument_list|,
name|layer
operator|->
name|mode
argument_list|,
name|NULL
argument_list|,
operator|(
name|x1
operator|-
name|offx
operator|)
argument_list|,
operator|(
name|y1
operator|-
name|offy
operator|)
argument_list|)
expr_stmt|;
comment|/*  restore preserve transparency  */
if|if
condition|(
name|preserve_trans
condition|)
name|d_layer
operator|->
name|preserve_trans
operator|=
name|TRUE
expr_stmt|;
comment|/*  restore gimage active channels  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|MAX_CHANNELS
condition|;
name|i
operator|++
control|)
name|gimage
operator|->
name|active
index|[
name|i
index|]
operator|=
name|active
index|[
name|i
index|]
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|BoundSeg
modifier|*
DECL|function|floating_sel_boundary (Layer * layer,int * num_segs)
name|floating_sel_boundary
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|int
modifier|*
name|num_segs
parameter_list|)
block|{
name|PixelRegion
name|bPR
decl_stmt|;
name|int
name|i
decl_stmt|;
if|if
condition|(
name|layer
operator|->
name|fs
operator|.
name|boundary_known
operator|==
name|FALSE
condition|)
block|{
if|if
condition|(
name|layer
operator|->
name|fs
operator|.
name|segs
condition|)
name|g_free
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|segs
argument_list|)
expr_stmt|;
comment|/*  find the segments  */
name|pixel_region_init
argument_list|(
operator|&
name|bPR
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
operator|=
name|find_mask_boundary
argument_list|(
operator|&
name|bPR
argument_list|,
operator|&
name|layer
operator|->
name|fs
operator|.
name|num_segs
argument_list|,
name|WithinBounds
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/*  offset the segments  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|layer
operator|->
name|fs
operator|.
name|num_segs
condition|;
name|i
operator|++
control|)
block|{
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
name|i
index|]
operator|.
name|x1
operator|+=
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
name|i
index|]
operator|.
name|y1
operator|+=
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
name|i
index|]
operator|.
name|x2
operator|+=
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
name|i
index|]
operator|.
name|y2
operator|+=
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
expr_stmt|;
block|}
name|layer
operator|->
name|fs
operator|.
name|boundary_known
operator|=
name|TRUE
expr_stmt|;
block|}
operator|*
name|num_segs
operator|=
name|layer
operator|->
name|fs
operator|.
name|num_segs
expr_stmt|;
return|return
name|layer
operator|->
name|fs
operator|.
name|segs
return|;
block|}
end_function

begin_function
name|void
DECL|function|floating_sel_invalidate (Layer * layer)
name|floating_sel_invalidate
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|)
block|{
comment|/*  Invalidate the attached-to drawable's preview  */
name|drawable_invalidate_preview
argument_list|(
name|layer
operator|->
name|fs
operator|.
name|drawable
argument_list|)
expr_stmt|;
comment|/*  Invalidate the boundary  */
name|layer
operator|->
name|fs
operator|.
name|boundary_known
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

