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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
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
file|"gimpimage-guides.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-item-list.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-resize.h"
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
file|"gimpprogress.h"
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

begin_function
name|void
DECL|function|gimp_image_resize (GimpImage * image,GimpContext * context,gint new_width,gint new_height,gint offset_x,gint offset_y,GimpProgress * progress)
name|gimp_image_resize
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
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|gimp_image_resize_with_layers
argument_list|(
name|image
argument_list|,
name|context
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|GIMP_ITEM_SET_NONE
argument_list|,
name|progress
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_resize_with_layers (GimpImage * image,GimpContext * context,gint new_width,gint new_height,gint offset_x,gint offset_y,GimpItemSet layer_set,GimpProgress * progress)
name|gimp_image_resize_with_layers
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
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|GimpItemSet
name|layer_set
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GList
modifier|*
name|resize_layers
decl_stmt|;
name|gdouble
name|progress_max
decl_stmt|;
name|gdouble
name|progress_current
init|=
literal|1.0
decl_stmt|;
name|gint
name|old_width
decl_stmt|,
name|old_height
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
name|g_return_if_fail
argument_list|(
name|new_width
operator|>
literal|0
operator|&&
name|new_height
operator|>
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
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
name|resize_layers
operator|=
name|gimp_image_item_list_get_list
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|GIMP_ITEM_TYPE_LAYERS
argument_list|,
name|layer_set
argument_list|)
expr_stmt|;
name|progress_max
operator|=
operator|(
name|gimp_container_get_n_children
argument_list|(
name|gimp_image_get_layers
argument_list|(
name|image
argument_list|)
argument_list|)
operator|+
name|gimp_container_get_n_children
argument_list|(
name|gimp_image_get_channels
argument_list|(
name|image
argument_list|)
argument_list|)
operator|+
name|gimp_container_get_n_children
argument_list|(
name|gimp_image_get_vectors
argument_list|(
name|image
argument_list|)
argument_list|)
operator|+
name|g_list_length
argument_list|(
name|resize_layers
argument_list|)
operator|+
literal|1
comment|/* selection */
operator|)
expr_stmt|;
name|old_width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|old_height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/*  Push the image size to the stack  */
name|gimp_image_undo_push_image_size
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
operator|-
name|offset_x
argument_list|,
operator|-
name|offset_y
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|)
expr_stmt|;
comment|/*  Set the new width and height  */
name|g_object_set
argument_list|(
name|image
argument_list|,
literal|"width"
argument_list|,
name|new_width
argument_list|,
literal|"height"
argument_list|,
name|new_height
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
name|new_width
argument_list|,
name|new_height
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_set_value
argument_list|(
name|progress
argument_list|,
name|progress_current
operator|++
operator|/
name|progress_max
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
name|new_width
argument_list|,
name|new_height
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_set_value
argument_list|(
name|progress
argument_list|,
name|progress_current
operator|++
operator|/
name|progress_max
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
name|new_width
argument_list|,
name|new_height
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_set_value
argument_list|(
name|progress
argument_list|,
name|progress_current
operator|++
operator|/
name|progress_max
argument_list|)
expr_stmt|;
comment|/*  Reposition all layers  */
for|for
control|(
name|list
operator|=
name|gimp_image_get_layer_iter
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
name|gimp_item_translate
argument_list|(
name|item
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_set_value
argument_list|(
name|progress
argument_list|,
name|progress_current
operator|++
operator|/
name|progress_max
argument_list|)
expr_stmt|;
block|}
comment|/*  Resize all resize_layers to image size  */
for|for
control|(
name|list
operator|=
name|resize_layers
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
name|gint
name|old_offset_x
decl_stmt|;
name|gint
name|old_offset_y
decl_stmt|;
comment|/*  group layers can't be resized here  */
if|if
condition|(
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|item
argument_list|)
argument_list|)
condition|)
continue|continue;
name|gimp_item_get_offset
argument_list|(
name|item
argument_list|,
operator|&
name|old_offset_x
argument_list|,
operator|&
name|old_offset_y
argument_list|)
expr_stmt|;
name|gimp_item_resize
argument_list|(
name|item
argument_list|,
name|context
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|,
name|old_offset_x
argument_list|,
name|old_offset_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_set_value
argument_list|(
name|progress
argument_list|,
name|progress_current
operator|++
operator|/
name|progress_max
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|resize_layers
argument_list|)
expr_stmt|;
comment|/*  Reposition or remove all guides  */
for|for
control|(
name|list
operator|=
name|gimp_image_get_guides
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
name|new_position
init|=
name|gimp_guide_get_position
argument_list|(
name|guide
argument_list|)
decl_stmt|;
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
name|new_position
operator|+=
name|offset_y
expr_stmt|;
if|if
condition|(
name|new_position
operator|<
literal|0
operator|||
name|new_position
operator|>
name|new_height
condition|)
name|remove_guide
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|new_position
operator|+=
name|offset_x
expr_stmt|;
if|if
condition|(
name|new_position
operator|<
literal|0
operator|||
name|new_position
operator|>
name|new_width
condition|)
name|remove_guide
operator|=
name|TRUE
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
name|new_position
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
name|new_position
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
comment|/*  Reposition or remove sample points  */
for|for
control|(
name|list
operator|=
name|gimp_image_get_sample_points
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
name|new_y
operator|+=
name|offset_y
expr_stmt|;
if|if
condition|(
operator|(
name|sample_point
operator|->
name|y
operator|<
literal|0
operator|)
operator|||
operator|(
name|sample_point
operator|->
name|y
operator|>
name|new_height
operator|)
condition|)
name|remove_sample_point
operator|=
name|TRUE
expr_stmt|;
name|new_x
operator|+=
name|offset_x
expr_stmt|;
if|if
condition|(
operator|(
name|sample_point
operator|->
name|x
operator|<
literal|0
operator|)
operator|||
operator|(
name|sample_point
operator|->
name|x
operator|>
name|new_width
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
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|old_width
argument_list|,
name|old_height
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

begin_function
name|void
DECL|function|gimp_image_resize_to_layers (GimpImage * image,GimpContext * context,GimpProgress * progress)
name|gimp_image_resize_to_layers
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
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
name|g_return_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|gimp_image_get_layer_iter
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|list
condition|)
return|return;
comment|/* figure out starting values */
name|item
operator|=
name|list
operator|->
name|data
expr_stmt|;
name|x
operator|=
name|gimp_item_get_offset_x
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|y
operator|=
name|gimp_item_get_offset_y
argument_list|(
name|item
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
comment|/*  Respect all layers  */
for|for
control|(
name|list
operator|=
name|g_list_next
argument_list|(
name|list
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
name|item
operator|=
name|list
operator|->
name|data
expr_stmt|;
name|gimp_rectangle_union
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|gimp_item_get_offset_x
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_get_offset_y
argument_list|(
name|item
argument_list|)
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
expr_stmt|;
block|}
name|gimp_image_resize
argument_list|(
name|image
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
argument_list|,
name|progress
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_resize_to_selection (GimpImage * image,GimpContext * context,GimpProgress * progress)
name|gimp_image_resize_to_selection
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|selection
init|=
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
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
if|if
condition|(
name|gimp_channel_is_empty
argument_list|(
name|selection
argument_list|)
condition|)
return|return;
name|gimp_channel_bounds
argument_list|(
name|selection
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
name|gimp_image_resize
argument_list|(
name|image
argument_list|,
name|context
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
operator|-
name|x1
argument_list|,
operator|-
name|y1
argument_list|,
name|progress
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

