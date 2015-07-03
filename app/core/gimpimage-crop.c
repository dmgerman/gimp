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
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpguide.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-crop.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-guides.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-sample-points.h"
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
file|"gimpsamplepoint.h"
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
DECL|function|gimp_image_crop (GimpImage * image,GimpContext * context,gint x,gint y,gint width,gint height,gboolean crop_layers)
name|gimp_image_crop
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
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
name|gboolean
name|crop_layers
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|previous_width
decl_stmt|;
name|gint
name|previous_height
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|previous_width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|previous_height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/*  Make sure new width and height are non-zero  */
if|if
condition|(
name|width
operator|<
literal|1
operator|||
name|height
operator|<
literal|1
condition|)
return|return;
name|gimp_set_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|crop_layers
condition|)
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_CROP
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Crop Image"
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_RESIZE
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Resize Image"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Push the image size to the stack  */
name|gimp_image_undo_push_image_size
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
comment|/*  Set the new width and height  */
name|g_object_set
argument_list|(
name|image
argument_list|,
literal|"width"
argument_list|,
name|width
argument_list|,
literal|"height"
argument_list|,
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Resize all channels  */
for|for
control|(
name|list
operator|=
name|gimp_image_get_channel_iter
argument_list|(
name|image
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_item_resize
argument_list|(
name|item
argument_list|,
name|context
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|-
name|x
argument_list|,
operator|-
name|y
argument_list|)
expr_stmt|;
block|}
comment|/*  Resize all vectors  */
for|for
control|(
name|list
operator|=
name|gimp_image_get_vectors_iter
argument_list|(
name|image
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_item_resize
argument_list|(
name|item
argument_list|,
name|context
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|-
name|x
argument_list|,
operator|-
name|y
argument_list|)
expr_stmt|;
block|}
comment|/*  Don't forget the selection mask!  */
name|gimp_item_resize
argument_list|(
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|,
name|context
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|-
name|x
argument_list|,
operator|-
name|y
argument_list|)
expr_stmt|;
comment|/*  crop all layers  */
name|list
operator|=
name|gimp_image_get_layer_iter
argument_list|(
name|image
argument_list|)
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|list
operator|->
name|data
decl_stmt|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|gimp_item_translate
argument_list|(
name|item
argument_list|,
operator|-
name|x
argument_list|,
operator|-
name|y
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|crop_layers
condition|)
block|{
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gint
name|lx1
decl_stmt|,
name|ly1
decl_stmt|,
name|lx2
decl_stmt|,
name|ly2
decl_stmt|;
name|gimp_item_get_offset
argument_list|(
name|item
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|lx1
operator|=
name|CLAMP
argument_list|(
name|off_x
argument_list|,
literal|0
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|ly1
operator|=
name|CLAMP
argument_list|(
name|off_y
argument_list|,
literal|0
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|lx2
operator|=
name|CLAMP
argument_list|(
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|+
name|off_x
argument_list|,
literal|0
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|ly2
operator|=
name|CLAMP
argument_list|(
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|+
name|off_y
argument_list|,
literal|0
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|width
operator|=
name|lx2
operator|-
name|lx1
expr_stmt|;
name|height
operator|=
name|ly2
operator|-
name|ly1
expr_stmt|;
if|if
condition|(
name|width
operator|>
literal|0
operator|&&
name|height
operator|>
literal|0
condition|)
block|{
name|gimp_item_resize
argument_list|(
name|item
argument_list|,
name|context
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|-
operator|(
name|lx1
operator|-
name|off_x
operator|)
argument_list|,
operator|-
operator|(
name|ly1
operator|-
name|off_y
operator|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_remove_layer
argument_list|(
name|image
argument_list|,
name|GIMP_LAYER
argument_list|(
name|item
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
block|}
comment|/*  Reposition or remove all guides  */
name|list
operator|=
name|gimp_image_get_guides
argument_list|(
name|image
argument_list|)
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|GimpGuide
modifier|*
name|guide
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gboolean
name|remove_guide
init|=
name|FALSE
decl_stmt|;
name|gint
name|position
init|=
name|gimp_guide_get_position
argument_list|(
name|guide
argument_list|)
decl_stmt|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_guide_get_orientation
argument_list|(
name|guide
argument_list|)
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
if|if
condition|(
operator|(
name|position
operator|<
name|y
operator|)
operator|||
operator|(
name|position
operator|>
operator|(
name|y
operator|+
name|height
operator|)
operator|)
condition|)
name|remove_guide
operator|=
name|TRUE
expr_stmt|;
else|else
name|position
operator|-=
name|y
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
if|if
condition|(
operator|(
name|position
operator|<
name|x
operator|)
operator|||
operator|(
name|position
operator|>
operator|(
name|x
operator|+
name|width
operator|)
operator|)
condition|)
name|remove_guide
operator|=
name|TRUE
expr_stmt|;
else|else
name|position
operator|-=
name|x
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|remove_guide
condition|)
name|gimp_image_remove_guide
argument_list|(
name|image
argument_list|,
name|guide
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|position
operator|!=
name|gimp_guide_get_position
argument_list|(
name|guide
argument_list|)
condition|)
name|gimp_image_move_guide
argument_list|(
name|image
argument_list|,
name|guide
argument_list|,
name|position
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
comment|/*  Reposition or remove sample points  */
name|list
operator|=
name|gimp_image_get_sample_points
argument_list|(
name|image
argument_list|)
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|GimpSamplePoint
modifier|*
name|sample_point
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gboolean
name|remove_sample_point
init|=
name|FALSE
decl_stmt|;
name|gint
name|new_x
init|=
name|sample_point
operator|->
name|x
decl_stmt|;
name|gint
name|new_y
init|=
name|sample_point
operator|->
name|y
decl_stmt|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|new_y
operator|-=
name|y
expr_stmt|;
if|if
condition|(
operator|(
name|sample_point
operator|->
name|y
operator|<
name|y
operator|)
operator|||
operator|(
name|sample_point
operator|->
name|y
operator|>
operator|(
name|y
operator|+
name|height
operator|)
operator|)
condition|)
name|remove_sample_point
operator|=
name|TRUE
expr_stmt|;
name|new_x
operator|-=
name|x
expr_stmt|;
if|if
condition|(
operator|(
name|sample_point
operator|->
name|x
operator|<
name|x
operator|)
operator|||
operator|(
name|sample_point
operator|->
name|x
operator|>
operator|(
name|x
operator|+
name|width
operator|)
operator|)
condition|)
name|remove_sample_point
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|remove_sample_point
condition|)
name|gimp_image_remove_sample_point
argument_list|(
name|image
argument_list|,
name|sample_point
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|new_x
operator|!=
name|sample_point
operator|->
name|x
operator|||
name|new_y
operator|!=
name|sample_point
operator|->
name|y
condition|)
name|gimp_image_move_sample_point
argument_list|(
name|image
argument_list|,
name|sample_point
argument_list|,
name|new_x
argument_list|,
name|new_y
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_size_changed_detailed
argument_list|(
name|image
argument_list|,
operator|-
name|x
argument_list|,
operator|-
name|y
argument_list|,
name|previous_width
argument_list|,
name|previous_height
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

