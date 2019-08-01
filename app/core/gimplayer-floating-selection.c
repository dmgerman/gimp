begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpboundary.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-filters.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-floating-selection.h"
end_include

begin_include
include|#
directive|include
file|"gimperror.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
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
file|"gimplayer-floating-selection.h"
end_include

begin_include
include|#
directive|include
file|"gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* public functions  */
end_comment

begin_function
name|void
DECL|function|floating_sel_attach (GimpLayer * layer,GimpDrawable * drawable)
name|floating_sel_attach
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpLayer
modifier|*
name|floating_sel
decl_stmt|;
name|GimpLayer
modifier|*
name|parent
init|=
name|NULL
decl_stmt|;
name|gint
name|position
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LAYER
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
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
operator|!=
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|==
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|floating_sel
operator|=
name|gimp_image_get_floating_selection
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/*  If there is already a floating selection, anchor it  */
if|if
condition|(
name|floating_sel
condition|)
block|{
name|floating_sel_anchor
argument_list|(
name|floating_sel
argument_list|)
expr_stmt|;
comment|/*  if we were pasting to the old floating selection, paste now        *  to the drawable        */
if|if
condition|(
name|drawable
operator|==
operator|(
name|GimpDrawable
operator|*
operator|)
name|floating_sel
condition|)
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|gimp_layer_set_lock_alpha
argument_list|(
name|layer
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_layer_set_floating_sel_drawable
argument_list|(
name|layer
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
comment|/*  Floating selection layer placement, default to the top of the    *  layers stack; parent and position are adapted according to the    *  drawable associated with the floating selection.    */
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|GimpLayer
modifier|*
name|tmp
init|=
name|gimp_layer_mask_get_layer
argument_list|(
name|GIMP_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
name|parent
operator|=
name|GIMP_LAYER
argument_list|(
name|gimp_item_get_parent
argument_list|(
name|GIMP_ITEM
argument_list|(
name|tmp
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|position
operator|=
name|gimp_item_get_index
argument_list|(
name|GIMP_ITEM
argument_list|(
name|tmp
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|parent
operator|=
name|GIMP_LAYER
argument_list|(
name|gimp_item_get_parent
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|position
operator|=
name|gimp_item_get_index
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
name|parent
argument_list|,
name|position
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|floating_sel_anchor (GimpLayer * layer)
name|floating_sel_anchor
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpFilter
modifier|*
name|filter
init|=
name|NULL
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gint
name|dr_off_x
decl_stmt|,
name|dr_off_y
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LAYER
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Don't let gimp_image_remove_layer free the layer while we still need it */
name|g_object_ref
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_FS_ANCHOR
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Anchor Floating Selection"
argument_list|)
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_layer_get_floating_sel_drawable
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|dr_off_x
argument_list|,
operator|&
name|dr_off_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|&&
name|gimp_rectangle_intersect
argument_list|(
name|off_x
argument_list|,
name|off_y
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
name|dr_off_x
argument_list|,
name|dr_off_y
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|filter
operator|=
name|gimp_drawable_get_floating_sel_filter
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|filter
condition|)
block|{
name|gimp_drawable_merge_filter
argument_list|(
name|drawable
argument_list|,
name|filter
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|gimp_image_remove_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/*  invalidate the boundaries  */
name|gimp_drawable_invalidate_boundary
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|layer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|floating_sel_to_layer (GimpLayer * layer,GError ** error)
name|floating_sel_to_layer
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LAYER
argument_list|(
name|layer
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
comment|/*  Check if the floating layer belongs to a channel  */
if|if
condition|(
name|GIMP_IS_CHANNEL
argument_list|(
name|gimp_layer_get_floating_sel_drawable
argument_list|(
name|layer
argument_list|)
argument_list|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"Cannot create a new layer from the floating "
literal|"selection because it belongs to a layer mask "
literal|"or channel."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_FS_TO_LAYER
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Floating Selection to Layer"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_undo_push_fs_to_layer
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|layer
argument_list|)
expr_stmt|;
name|gimp_drawable_detach_floating_sel
argument_list|(
name|gimp_layer_get_floating_sel_drawable
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_layer_set_floating_sel_drawable
argument_list|(
name|layer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_item_set_visible
argument_list|(
name|item
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_layer_set_lock_alpha
argument_list|(
name|layer
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/* When the floating selection is converted to/from a normal layer    * it does something resembling a name change, so emit the    * "name-changed" signal    */
name|gimp_object_name_changed
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_update
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
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|void
DECL|function|floating_sel_activate_drawable (GimpLayer * layer)
name|floating_sel_activate_drawable
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LAYER
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_layer_get_floating_sel_drawable
argument_list|(
name|layer
argument_list|)
expr_stmt|;
comment|/*  set the underlying drawable to active  */
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|GimpLayerMask
modifier|*
name|mask
init|=
name|GIMP_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|gimp_image_set_active_layer
argument_list|(
name|image
argument_list|,
name|gimp_layer_mask_get_layer
argument_list|(
name|mask
argument_list|)
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
name|gimp_image_set_active_channel
argument_list|(
name|image
argument_list|,
name|GIMP_CHANNEL
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_set_active_layer
argument_list|(
name|image
argument_list|,
name|GIMP_LAYER
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|const
name|GimpBoundSeg
modifier|*
DECL|function|floating_sel_boundary (GimpLayer * layer,gint * n_segs)
name|floating_sel_boundary
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gint
modifier|*
name|n_segs
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LAYER
argument_list|(
name|layer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_segs
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|width
operator|=
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
condition|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/*  find the segments  */
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
operator|=
name|gimp_boundary_find
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|babl_format
argument_list|(
literal|"A float"
argument_list|)
argument_list|,
name|GIMP_BOUNDARY_WITHIN_BOUNDS
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_BOUNDARY_HALF_WAY
argument_list|,
operator|&
name|layer
operator|->
name|fs
operator|.
name|num_segs
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
name|off_x
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
name|off_y
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
name|off_x
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
name|off_y
expr_stmt|;
block|}
block|}
else|else
block|{
name|layer
operator|->
name|fs
operator|.
name|num_segs
operator|=
literal|4
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
operator|=
name|g_new0
argument_list|(
name|GimpBoundSeg
argument_list|,
literal|4
argument_list|)
expr_stmt|;
comment|/* top */
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|0
index|]
operator|.
name|x1
operator|=
name|off_x
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|0
index|]
operator|.
name|y1
operator|=
name|off_y
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|0
index|]
operator|.
name|x2
operator|=
name|off_x
operator|+
name|width
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|0
index|]
operator|.
name|y2
operator|=
name|off_y
expr_stmt|;
comment|/* left */
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|1
index|]
operator|.
name|x1
operator|=
name|off_x
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|1
index|]
operator|.
name|y1
operator|=
name|off_y
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|1
index|]
operator|.
name|x2
operator|=
name|off_x
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|1
index|]
operator|.
name|y2
operator|=
name|off_y
operator|+
name|height
expr_stmt|;
comment|/* right */
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|2
index|]
operator|.
name|x1
operator|=
name|off_x
operator|+
name|width
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|2
index|]
operator|.
name|y1
operator|=
name|off_y
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|2
index|]
operator|.
name|x2
operator|=
name|off_x
operator|+
name|width
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|2
index|]
operator|.
name|y2
operator|=
name|off_y
operator|+
name|height
expr_stmt|;
comment|/* bottom */
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|3
index|]
operator|.
name|x1
operator|=
name|off_x
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|3
index|]
operator|.
name|y1
operator|=
name|off_y
operator|+
name|height
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|3
index|]
operator|.
name|x2
operator|=
name|off_x
operator|+
name|width
expr_stmt|;
name|layer
operator|->
name|fs
operator|.
name|segs
index|[
literal|3
index|]
operator|.
name|y2
operator|=
name|off_y
operator|+
name|height
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
name|n_segs
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
DECL|function|floating_sel_invalidate (GimpLayer * layer)
name|floating_sel_invalidate
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LAYER
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Invalidate the attached-to drawable's preview  */
name|gimp_viewable_invalidate_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimp_layer_get_floating_sel_drawable
argument_list|(
name|layer
argument_list|)
argument_list|)
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

