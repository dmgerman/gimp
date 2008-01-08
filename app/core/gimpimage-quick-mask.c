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
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-quick-mask.h"
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
file|"gimpselection.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|CHANNEL_WAS_ACTIVE
define|#
directive|define
name|CHANNEL_WAS_ACTIVE
value|(0x2)
end_define

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_image_set_quick_mask_state (GimpImage * image,gboolean active)
name|gimp_image_set_quick_mask_state
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|active
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|selection
decl_stmt|;
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
name|gboolean
name|channel_was_active
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|active
operator|==
name|gimp_image_get_quick_mask_state
argument_list|(
name|image
argument_list|)
condition|)
return|return;
comment|/*  Keep track of the state so that we can make the right drawable    *  active again when deactiviting quick mask (see bug #134371).    */
if|if
condition|(
name|image
operator|->
name|quick_mask_state
condition|)
name|channel_was_active
operator|=
operator|(
name|image
operator|->
name|quick_mask_state
operator|&
name|CHANNEL_WAS_ACTIVE
operator|)
operator|!=
literal|0
expr_stmt|;
else|else
name|channel_was_active
operator|=
name|gimp_image_get_active_channel
argument_list|(
name|image
argument_list|)
operator|!=
name|NULL
expr_stmt|;
comment|/*  Set image->quick_mask_state early so we can return early when    *  being called recursively.    */
name|image
operator|->
name|quick_mask_state
operator|=
operator|(
name|active
condition|?
name|TRUE
operator||
operator|(
name|channel_was_active
condition|?
name|CHANNEL_WAS_ACTIVE
else|:
literal|0
operator|)
else|:
name|FALSE
operator|)
expr_stmt|;
name|selection
operator|=
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gimp_image_get_quick_mask
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|active
condition|)
block|{
if|if
condition|(
operator|!
name|mask
condition|)
block|{
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_QUICK_MASK
argument_list|,
name|_
argument_list|(
literal|"Enable Quick Mask"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_channel_is_empty
argument_list|(
name|selection
argument_list|)
condition|)
block|{
comment|/* if no selection */
name|GimpLayer
modifier|*
name|floating_sel
init|=
name|gimp_image_floating_sel
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|floating_sel
condition|)
name|floating_sel_to_layer
argument_list|(
name|floating_sel
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gimp_channel_new
argument_list|(
name|image
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_IMAGE_QUICK_MASK_NAME
argument_list|,
operator|&
name|image
operator|->
name|quick_mask_color
argument_list|)
expr_stmt|;
comment|/* Clear the mask */
name|gimp_channel_clear
argument_list|(
name|mask
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* if selection */
name|mask
operator|=
name|GIMP_CHANNEL
argument_list|(
name|gimp_item_duplicate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|selection
argument_list|)
argument_list|,
name|GIMP_TYPE_CHANNEL
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Clear the selection */
name|gimp_channel_clear
argument_list|(
name|selection
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_channel_set_color
argument_list|(
name|mask
argument_list|,
operator|&
name|image
operator|->
name|quick_mask_color
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_rename
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|,
name|GIMP_IMAGE_QUICK_MASK_NAME
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|image
operator|->
name|quick_mask_inverted
condition|)
name|gimp_channel_invert
argument_list|(
name|mask
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_add_channel
argument_list|(
name|image
argument_list|,
name|mask
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|mask
condition|)
block|{
name|GimpLayer
modifier|*
name|floating_sel
init|=
name|gimp_image_floating_sel
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_QUICK_MASK
argument_list|,
name|_
argument_list|(
literal|"Disable Quick Mask"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|->
name|quick_mask_inverted
condition|)
name|gimp_channel_invert
argument_list|(
name|mask
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|floating_sel
operator|&&
name|floating_sel
operator|->
name|fs
operator|.
name|drawable
operator|==
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
condition|)
name|floating_sel_anchor
argument_list|(
name|floating_sel
argument_list|)
expr_stmt|;
name|gimp_selection_load
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|mask
argument_list|)
expr_stmt|;
name|gimp_image_remove_channel
argument_list|(
name|image
argument_list|,
name|mask
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|channel_was_active
condition|)
name|gimp_image_unset_active_channel
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_image_quick_mask_changed
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_get_quick_mask_state (const GimpImage * image)
name|gimp_image_get_quick_mask_state
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
operator|(
name|image
operator|->
name|quick_mask_state
operator|!=
literal|0
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_set_quick_mask_color (GimpImage * image,const GimpRGB * color)
name|gimp_image_set_quick_mask_color
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|quick_mask
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|image
operator|->
name|quick_mask_color
operator|=
operator|*
name|color
expr_stmt|;
name|quick_mask
operator|=
name|gimp_image_get_quick_mask
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|quick_mask
condition|)
name|gimp_channel_set_color
argument_list|(
name|quick_mask
argument_list|,
name|color
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_get_quick_mask_color (const GimpImage * image,GimpRGB * color)
name|gimp_image_get_quick_mask_color
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|color
operator|=
name|image
operator|->
name|quick_mask_color
expr_stmt|;
block|}
end_function

begin_function
name|GimpChannel
modifier|*
DECL|function|gimp_image_get_quick_mask (const GimpImage * image)
name|gimp_image_get_quick_mask
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_image_get_channel_by_name
argument_list|(
name|image
argument_list|,
name|GIMP_IMAGE_QUICK_MASK_NAME
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_quick_mask_invert (GimpImage * image)
name|gimp_image_quick_mask_invert
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|->
name|quick_mask_state
condition|)
block|{
name|GimpChannel
modifier|*
name|quick_mask
init|=
name|gimp_image_get_quick_mask
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|quick_mask
condition|)
name|gimp_channel_invert
argument_list|(
name|quick_mask
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|image
operator|->
name|quick_mask_inverted
operator|=
operator|!
name|image
operator|->
name|quick_mask_inverted
expr_stmt|;
block|}
end_function

end_unit

