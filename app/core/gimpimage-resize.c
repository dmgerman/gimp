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
file|"gimpimage-guides.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-resize.h"
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
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_image_resize (GimpImage * gimage,GimpContext * context,gint new_width,gint new_height,gint offset_x,gint offset_y,GimpProgressFunc progress_func,gpointer progress_data)
name|gimp_image_resize
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|GimpProgressFunc
name|progress_func
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
block|{
name|GList
modifier|*
name|list
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
name|gimp_set_busy
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
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
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_RESIZE
argument_list|,
name|_
argument_list|(
literal|"Resize Image"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Push the image size to the stack  */
name|gimp_image_undo_push_image_size
argument_list|(
name|gimage
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Set the new width and height  */
name|g_object_set
argument_list|(
name|gimage
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
comment|/*  Resize all vectors  */
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
name|gimp_item_resize
argument_list|(
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
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
comment|/*  Reposition all layers  */
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
comment|/*  Reposition or remove all guides  */
name|list
operator|=
name|gimage
operator|->
name|guides
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
name|new_position
init|=
name|guide
operator|->
name|position
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
name|guide
operator|->
name|orientation
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
name|gimage
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
name|guide
operator|->
name|position
condition|)
name|gimp_image_move_guide
argument_list|(
name|gimage
argument_list|,
name|guide
argument_list|,
name|new_position
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_viewable_size_changed
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
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

