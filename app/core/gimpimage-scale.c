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
file|"base/tile-manager.h"
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
file|"gimpimage-sample-points.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-scale.h"
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
file|"gimpprojection.h"
end_include

begin_include
include|#
directive|include
file|"gimpsamplepoint.h"
end_include

begin_include
include|#
directive|include
file|"gimpsubprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimp-log.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_image_scale (GimpImage * image,gint new_width,gint new_height,GimpInterpolationType interpolation_type,GimpProgress * progress)
name|gimp_image_scale
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|GimpInterpolationType
name|interpolation_type
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpProgress
modifier|*
name|sub_progress
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GList
modifier|*
name|remove
init|=
name|NULL
decl_stmt|;
name|gint
name|old_width
decl_stmt|;
name|gint
name|old_height
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|gdouble
name|img_scale_w
init|=
literal|1.0
decl_stmt|;
name|gdouble
name|img_scale_h
init|=
literal|1.0
decl_stmt|;
name|gint
name|progress_steps
decl_stmt|;
name|gint
name|progress_current
init|=
literal|0
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
name|sub_progress
operator|=
name|gimp_sub_progress_new
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|progress_steps
operator|=
operator|(
name|gimp_container_num_children
argument_list|(
name|image
operator|->
name|channels
argument_list|)
operator|+
name|gimp_container_num_children
argument_list|(
name|image
operator|->
name|layers
argument_list|)
operator|+
name|gimp_container_num_children
argument_list|(
name|image
operator|->
name|vectors
argument_list|)
operator|+
literal|1
comment|/* selection */
operator|)
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
name|GIMP_UNDO_GROUP_IMAGE_SCALE
argument_list|,
name|_
argument_list|(
literal|"Scale Image"
argument_list|)
argument_list|)
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
name|img_scale_w
operator|=
operator|(
name|gdouble
operator|)
name|new_width
operator|/
operator|(
name|gdouble
operator|)
name|old_width
expr_stmt|;
name|img_scale_h
operator|=
operator|(
name|gdouble
operator|)
name|new_height
operator|/
operator|(
name|gdouble
operator|)
name|old_height
expr_stmt|;
name|offset_x
operator|=
operator|(
name|old_width
operator|-
name|new_width
operator|)
operator|/
literal|2
expr_stmt|;
name|offset_y
operator|=
operator|(
name|old_height
operator|-
name|new_height
operator|)
operator|/
literal|2
expr_stmt|;
comment|/*  Push the image size to the stack  */
name|gimp_image_undo_push_image_size
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|offset_x
argument_list|,
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
comment|/*  Scale all channels  */
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
name|gimp_sub_progress_set_step
argument_list|(
name|GIMP_SUB_PROGRESS
argument_list|(
name|sub_progress
argument_list|)
argument_list|,
name|progress_current
operator|++
argument_list|,
name|progress_steps
argument_list|)
expr_stmt|;
name|gimp_item_scale
argument_list|(
name|item
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|interpolation_type
argument_list|,
name|sub_progress
argument_list|)
expr_stmt|;
block|}
comment|/*  Scale all vectors  */
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
name|gimp_sub_progress_set_step
argument_list|(
name|GIMP_SUB_PROGRESS
argument_list|(
name|sub_progress
argument_list|)
argument_list|,
name|progress_current
operator|++
argument_list|,
name|progress_steps
argument_list|)
expr_stmt|;
name|gimp_item_scale
argument_list|(
name|item
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|interpolation_type
argument_list|,
name|sub_progress
argument_list|)
expr_stmt|;
block|}
comment|/*  Don't forget the selection mask!  */
name|gimp_sub_progress_set_step
argument_list|(
name|GIMP_SUB_PROGRESS
argument_list|(
name|sub_progress
argument_list|)
argument_list|,
name|progress_current
operator|++
argument_list|,
name|progress_steps
argument_list|)
expr_stmt|;
name|gimp_item_scale
argument_list|(
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|interpolation_type
argument_list|,
name|sub_progress
argument_list|)
expr_stmt|;
comment|/*  Scale all layers  */
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
name|gimp_sub_progress_set_step
argument_list|(
name|GIMP_SUB_PROGRESS
argument_list|(
name|sub_progress
argument_list|)
argument_list|,
name|progress_current
operator|++
argument_list|,
name|progress_steps
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_item_scale_by_factors
argument_list|(
name|item
argument_list|,
name|img_scale_w
argument_list|,
name|img_scale_h
argument_list|,
name|interpolation_type
argument_list|,
name|sub_progress
argument_list|)
condition|)
block|{
comment|/* Since 0< img_scale_w, img_scale_h, failure due to one or more            * vanishing scaled layer dimensions. Implicit delete implemented            * here. Upstream warning implemented in resize_check_layer_scaling(),            * which offers the user the chance to bail out.            */
name|remove
operator|=
name|g_list_prepend
argument_list|(
name|remove
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* We defer removing layers lost to scaling until now so as not to mix    * the operations of iterating over and removal from image->layers.    */
name|remove
operator|=
name|g_list_reverse
argument_list|(
name|remove
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|remove
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
name|GimpLayer
modifier|*
name|layer
init|=
name|list
operator|->
name|data
decl_stmt|;
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
block|}
name|g_list_free
argument_list|(
name|remove
argument_list|)
expr_stmt|;
comment|/*  Scale all Guides  */
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
name|gint
name|position
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
name|gimp_image_undo_push_guide
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gimp_guide_set_position
argument_list|(
name|guide
argument_list|,
operator|(
name|position
operator|*
name|new_height
operator|)
operator|/
name|old_height
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|gimp_image_undo_push_guide
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gimp_guide_set_position
argument_list|(
name|guide
argument_list|,
operator|(
name|position
operator|*
name|new_width
operator|)
operator|/
name|old_width
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
comment|/*  Scale all sample points  */
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
name|gimp_image_undo_push_sample_point
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
name|sample_point
operator|->
name|x
operator|=
name|sample_point
operator|->
name|x
operator|*
name|new_width
operator|/
name|old_width
expr_stmt|;
name|sample_point
operator|->
name|y
operator|=
name|sample_point
operator|->
name|y
operator|*
name|new_height
operator|/
name|old_height
expr_stmt|;
block|}
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|sub_progress
argument_list|)
expr_stmt|;
name|gimp_image_size_changed_detailed
argument_list|(
name|image
argument_list|,
operator|-
name|offset_x
argument_list|,
operator|-
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

begin_comment
comment|/**  * gimp_image_scale_check:  * @image:      A #GimpImage.  * @new_width:   The new width.  * @new_height:  The new height.  * @max_memsize: The maximum new memory size.  * @new_memsize: The new memory size.  *  * Inventory the layer list in image and check that it may be  * scaled to @new_height and @new_width without problems.  *  * Return value: #GIMP_IMAGE_SCALE_OK if scaling the image will shrink none  *               of its layers completely away, and the new image size  *               is smaller than @max_memsize.  *               #GIMP_IMAGE_SCALE_TOO_SMALL if scaling would remove some  *               existing layers.  *               #GIMP_IMAGE_SCALE_TOO_BIG if the new image size would  *               exceed the maximum specified in the preferences.  **/
end_comment

begin_function
name|GimpImageScaleCheckType
DECL|function|gimp_image_scale_check (const GimpImage * image,gint new_width,gint new_height,gint64 max_memsize,gint64 * new_memsize)
name|gimp_image_scale_check
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gint64
name|max_memsize
parameter_list|,
name|gint64
modifier|*
name|new_memsize
parameter_list|)
block|{
name|GList
modifier|*
name|drawables
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint64
name|current_size
decl_stmt|;
name|gint64
name|scalable_size
decl_stmt|;
name|gint64
name|scaled_size
decl_stmt|;
name|gint64
name|undo_size
decl_stmt|;
name|gint64
name|redo_size
decl_stmt|;
name|gint64
name|fixed_size
decl_stmt|;
name|gint64
name|new_size
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_IMAGE_SCALE_TOO_SMALL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|new_memsize
operator|!=
name|NULL
argument_list|,
name|GIMP_IMAGE_SCALE_TOO_SMALL
argument_list|)
expr_stmt|;
name|current_size
operator|=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  the part of the image's memsize that scales linearly with the image  */
name|drawables
operator|=
name|gimp_image_item_list_get_list
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|GIMP_ITEM_TYPE_LAYERS
operator||
name|GIMP_ITEM_TYPE_CHANNELS
argument_list|,
name|GIMP_ITEM_SET_ALL
argument_list|)
expr_stmt|;
name|drawables
operator|=
name|g_list_prepend
argument_list|(
name|drawables
argument_list|,
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|scalable_size
operator|=
literal|0
expr_stmt|;
name|scaled_size
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|list
operator|=
name|drawables
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
name|GimpDrawable
modifier|*
name|drawable
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gdouble
name|width
init|=
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
name|gdouble
name|height
init|=
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
name|scalable_size
operator|+=
name|gimp_drawable_estimate_memsize
argument_list|(
name|drawable
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|scaled_size
operator|+=
name|gimp_drawable_estimate_memsize
argument_list|(
name|drawable
argument_list|,
name|width
operator|*
name|new_width
operator|/
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|height
operator|*
name|new_height
operator|/
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|drawables
argument_list|)
expr_stmt|;
name|scalable_size
operator|+=
name|gimp_projection_estimate_memsize
argument_list|(
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
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
argument_list|)
expr_stmt|;
name|scaled_size
operator|+=
name|gimp_projection_estimate_memsize
argument_list|(
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|)
expr_stmt|;
name|GIMP_LOG
argument_list|(
name|IMAGE_SCALE
argument_list|,
literal|"scalable_size = %"
name|G_GINT64_FORMAT
literal|"  scaled_size = %"
name|G_GINT64_FORMAT
argument_list|,
name|scalable_size
argument_list|,
name|scaled_size
argument_list|)
expr_stmt|;
name|undo_size
operator|=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|redo_size
operator|=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|image
operator|->
name|redo_stack
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  the fixed part of the image's memsize w/o any undo information  */
name|fixed_size
operator|=
name|current_size
operator|-
name|undo_size
operator|-
name|redo_size
operator|-
name|scalable_size
expr_stmt|;
comment|/*  calculate the new size, which is:  */
name|new_size
operator|=
operator|(
name|fixed_size
operator|+
comment|/*  the fixed part                */
name|scaled_size
operator|)
expr_stmt|;
comment|/*  plus the part that scales...  */
name|GIMP_LOG
argument_list|(
name|IMAGE_SCALE
argument_list|,
literal|"old_size = %"
name|G_GINT64_FORMAT
literal|"  new_size = %"
name|G_GINT64_FORMAT
argument_list|,
name|current_size
operator|-
name|undo_size
operator|-
name|redo_size
argument_list|,
name|new_size
argument_list|)
expr_stmt|;
operator|*
name|new_memsize
operator|=
name|new_size
expr_stmt|;
if|if
condition|(
name|new_size
operator|>
name|current_size
operator|&&
name|new_size
operator|>
name|max_memsize
condition|)
return|return
name|GIMP_IMAGE_SCALE_TOO_BIG
return|;
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
if|if
condition|(
operator|!
name|gimp_item_check_scaling
argument_list|(
name|item
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|)
condition|)
return|return
name|GIMP_IMAGE_SCALE_TOO_SMALL
return|;
block|}
return|return
name|GIMP_IMAGE_SCALE_OK
return|;
block|}
end_function

end_unit

