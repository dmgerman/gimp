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
file|"gimpimage-qmask.h"
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
file|"gimplayer-floating-sel.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_image_qmask_removed_callback
parameter_list|(
name|GObject
modifier|*
name|qmask
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_image_set_qmask_state (GimpImage * gimage,gboolean qmask_state)
name|gimp_image_set_qmask_state
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gboolean
name|qmask_state
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
name|GimpRGB
name|color
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|qmask_state
operator|==
name|gimage
operator|->
name|qmask_state
condition|)
return|return;
name|selection
operator|=
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|qmask_state
condition|)
block|{
comment|/* Set the defaults */
name|color
operator|=
name|gimage
operator|->
name|qmask_color
expr_stmt|;
name|mask
operator|=
name|gimp_image_get_channel_by_name
argument_list|(
name|gimage
argument_list|,
literal|"Qmask"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|mask
condition|)
block|{
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_QMASK
argument_list|,
name|_
argument_list|(
literal|"Enable QuickMask"
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
name|layer
decl_stmt|;
if|if
condition|(
operator|(
name|layer
operator|=
name|gimp_image_floating_sel
argument_list|(
name|gimage
argument_list|)
operator|)
condition|)
block|{
name|floating_sel_to_layer
argument_list|(
name|layer
argument_list|)
expr_stmt|;
block|}
name|mask
operator|=
name|gimp_channel_new
argument_list|(
name|gimage
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|,
literal|"Qmask"
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_drawable_fill_by_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|,
name|gimp_get_current_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
name|GIMP_TRANSPARENT_FILL
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
argument_list|,
name|FALSE
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
name|color
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
literal|"Qmask"
argument_list|)
expr_stmt|;
block|}
name|gimp_image_add_channel
argument_list|(
name|gimage
argument_list|,
name|mask
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|->
name|qmask_inverted
condition|)
name|gimp_channel_invert
argument_list|(
name|mask
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_push_image_qmask
argument_list|(
name|gimage
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/* connect to the removed signal, so the buttons get updated */
name|g_signal_connect
argument_list|(
name|mask
argument_list|,
literal|"removed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_qmask_removed_callback
argument_list|)
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|mask
operator|=
name|gimp_image_get_channel_by_name
argument_list|(
name|gimage
argument_list|,
literal|"Qmask"
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask
condition|)
block|{
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_QMASK
argument_list|,
name|_
argument_list|(
literal|"Disable QuickMask"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  push the undo here since removing the mask will            *  call the qmask_removed_callback() which will set            *  the qmask_state to FALSE            */
name|gimp_image_undo_push_image_qmask
argument_list|(
name|gimage
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|->
name|qmask_inverted
condition|)
name|gimp_channel_invert
argument_list|(
name|mask
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_mask_load
argument_list|(
name|gimage
argument_list|,
name|mask
argument_list|)
expr_stmt|;
name|gimp_image_remove_channel
argument_list|(
name|gimage
argument_list|,
name|mask
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
name|gimage
operator|->
name|qmask_state
operator|=
name|qmask_state
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|gimp_image_qmask_changed
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_get_qmask_state (const GimpImage * gimage)
name|gimp_image_get_qmask_state
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
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
return|return
name|gimage
operator|->
name|qmask_state
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_qmask_invert (GimpImage * gimage)
name|gimp_image_qmask_invert
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
if|if
condition|(
name|gimage
operator|->
name|qmask_state
condition|)
block|{
name|GimpChannel
modifier|*
name|qmask
decl_stmt|;
name|qmask
operator|=
name|gimp_image_get_channel_by_name
argument_list|(
name|gimage
argument_list|,
literal|"Qmask"
argument_list|)
expr_stmt|;
if|if
condition|(
name|qmask
condition|)
block|{
name|gimp_channel_invert
argument_list|(
name|qmask
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|qmask
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|GIMP_ITEM
argument_list|(
name|qmask
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_ITEM
argument_list|(
name|qmask
argument_list|)
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
block|}
name|gimage
operator|->
name|qmask_inverted
operator|=
operator|!
name|gimage
operator|->
name|qmask_inverted
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_image_qmask_removed_callback (GObject * qmask,GimpImage * gimage)
name|gimp_image_qmask_removed_callback
parameter_list|(
name|GObject
modifier|*
name|qmask
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|gimp_image_set_qmask_state
argument_list|(
name|gimage
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

