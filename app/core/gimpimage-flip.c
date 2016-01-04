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
file|"gimpimage-flip.h"
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
file|"gimpitem.h"
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

begin_function
name|void
DECL|function|gimp_image_flip (GimpImage * image,GimpContext * context,GimpOrientationType flip_type,GimpProgress * progress)
name|gimp_image_flip
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpOrientationType
name|flip_type
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
name|gdouble
name|axis
decl_stmt|;
name|gdouble
name|progress_max
decl_stmt|;
name|gdouble
name|progress_current
init|=
literal|1.0
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
name|gimp_set_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|flip_type
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
name|axis
operator|=
operator|(
name|gdouble
operator|)
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|/
literal|2.0
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|axis
operator|=
operator|(
name|gdouble
operator|)
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
operator|/
literal|2.0
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"%s: unknown flip_type"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
return|return;
block|}
name|progress_max
operator|=
operator|(
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
name|gimp_image_get_layers
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
literal|1
comment|/* selection */
operator|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_FLIP
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Flip all channels  */
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
name|gimp_item_flip
argument_list|(
name|item
argument_list|,
name|context
argument_list|,
name|flip_type
argument_list|,
name|axis
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
comment|/*  Flip all vectors  */
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
name|gimp_item_flip
argument_list|(
name|item
argument_list|,
name|context
argument_list|,
name|flip_type
argument_list|,
name|axis
argument_list|,
name|FALSE
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
name|gimp_item_flip
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
name|flip_type
argument_list|,
name|axis
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
comment|/*  Flip all layers  */
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
name|gimp_item_flip
argument_list|(
name|item
argument_list|,
name|context
argument_list|,
name|flip_type
argument_list|,
name|axis
argument_list|,
name|FALSE
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
comment|/*  Flip all Guides  */
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
if|if
condition|(
name|flip_type
operator|==
name|GIMP_ORIENTATION_VERTICAL
condition|)
name|gimp_image_move_guide
argument_list|(
name|image
argument_list|,
name|guide
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
operator|-
name|position
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
if|if
condition|(
name|flip_type
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|gimp_image_move_guide
argument_list|(
name|image
argument_list|,
name|guide
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|-
name|position
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
comment|/*  Flip all sample points  */
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
name|gint
name|x
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|gimp_sample_point_get_position
argument_list|(
name|sample_point
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|flip_type
operator|==
name|GIMP_ORIENTATION_VERTICAL
condition|)
name|gimp_image_move_sample_point
argument_list|(
name|image
argument_list|,
name|sample_point
argument_list|,
name|x
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
operator|-
name|y
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|flip_type
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|gimp_image_move_sample_point
argument_list|(
name|image
argument_list|,
name|sample_point
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|-
name|x
argument_list|,
name|y
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

