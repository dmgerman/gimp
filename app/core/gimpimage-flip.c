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
file|"gimp.h"
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
file|"gimplist.h"
end_include

begin_function
name|void
DECL|function|gimp_image_flip (GimpImage * gimage,GimpOrientationType flip_type,GimpProgressFunc progress_func,gpointer progress_data)
name|gimp_image_flip
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|,
name|GimpProgressFunc
name|progress_func
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gdouble
name|axis
decl_stmt|;
name|gint
name|progress_max
decl_stmt|;
name|gint
name|progress_current
init|=
literal|1
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_set_busy
argument_list|(
name|gimage
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
name|gimage
operator|->
name|width
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
name|gimage
operator|->
name|height
operator|/
literal|2.0
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"gimp_image_flip(): unknown flip_type"
argument_list|)
expr_stmt|;
return|return;
block|}
name|progress_max
operator|=
operator|(
name|gimage
operator|->
name|channels
operator|->
name|num_children
operator|+
name|gimage
operator|->
name|layers
operator|->
name|num_children
operator|+
name|gimage
operator|->
name|vectors
operator|->
name|num_children
operator|+
literal|1
comment|/* selection */
operator|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|gimage
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
name|GIMP_LIST
argument_list|(
name|gimage
operator|->
name|channels
argument_list|)
operator|->
name|list
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
operator|(
name|GimpItem
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gimp_item_flip
argument_list|(
name|item
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
name|progress_func
condition|)
call|(
modifier|*
name|progress_func
call|)
argument_list|(
literal|0
argument_list|,
name|progress_max
argument_list|,
name|progress_current
operator|++
argument_list|,
name|progress_data
argument_list|)
expr_stmt|;
block|}
comment|/*  Flip all vectors  */
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimage
operator|->
name|vectors
argument_list|)
operator|->
name|list
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
operator|(
name|GimpItem
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gimp_item_flip
argument_list|(
name|item
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
name|progress_func
condition|)
call|(
modifier|*
name|progress_func
call|)
argument_list|(
literal|0
argument_list|,
name|progress_max
argument_list|,
name|progress_current
operator|++
argument_list|,
name|progress_data
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
name|gimage
argument_list|)
argument_list|)
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
name|progress_func
condition|)
call|(
modifier|*
name|progress_func
call|)
argument_list|(
literal|0
argument_list|,
name|progress_max
argument_list|,
name|progress_current
operator|++
argument_list|,
name|progress_data
argument_list|)
expr_stmt|;
comment|/*  Flip all layers  */
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimage
operator|->
name|layers
argument_list|)
operator|->
name|list
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
operator|(
name|GimpItem
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gimp_item_flip
argument_list|(
name|item
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
name|progress_func
condition|)
call|(
modifier|*
name|progress_func
call|)
argument_list|(
literal|0
argument_list|,
name|progress_max
argument_list|,
name|progress_current
operator|++
argument_list|,
name|progress_data
argument_list|)
expr_stmt|;
block|}
comment|/*  Flip all Guides  */
for|for
control|(
name|list
operator|=
name|gimage
operator|->
name|guides
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
switch|switch
condition|(
name|guide
operator|->
name|orientation
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
name|gimage
argument_list|,
name|guide
argument_list|,
name|gimage
operator|->
name|height
operator|-
name|guide
operator|->
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
name|gimage
argument_list|,
name|guide
argument_list|,
name|gimage
operator|->
name|width
operator|-
name|guide
operator|->
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
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

