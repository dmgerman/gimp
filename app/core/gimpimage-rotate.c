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
file|"gimpimage-projection.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-rotate.h"
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
file|"gimplayer-floating-sel.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_image_rotate_item_offset
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpRotationType
name|rotate_type
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_rotate_guides
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpRotationType
name|rotate_type
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|gimp_image_rotate (GimpImage * gimage,GimpRotationType rotate_type,GimpProgressFunc progress_func,gpointer progress_data)
name|gimp_image_rotate
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpRotationType
name|rotate_type
parameter_list|,
name|GimpProgressFunc
name|progress_func
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|floating_layer
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gdouble
name|center_x
decl_stmt|;
name|gdouble
name|center_y
decl_stmt|;
name|gint
name|progress_max
decl_stmt|;
name|gint
name|progress_current
init|=
literal|1
decl_stmt|;
name|gint
name|new_image_width
decl_stmt|;
name|gint
name|new_image_height
decl_stmt|;
name|gboolean
name|size_changed
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
name|center_x
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
name|center_y
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
comment|/*  Get the floating layer if one exists  */
name|floating_layer
operator|=
name|gimp_image_floating_sel
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_ROTATE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Relax the floating selection  */
if|if
condition|(
name|floating_layer
condition|)
name|floating_sel_relax
argument_list|(
name|floating_layer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  Resize the image (if needed)  */
switch|switch
condition|(
name|rotate_type
condition|)
block|{
case|case
name|GIMP_ROTATE_90
case|:
case|case
name|GIMP_ROTATE_270
case|:
name|new_image_width
operator|=
name|gimage
operator|->
name|height
expr_stmt|;
name|new_image_height
operator|=
name|gimage
operator|->
name|width
expr_stmt|;
name|size_changed
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GIMP_ROTATE_180
case|:
name|new_image_width
operator|=
name|gimage
operator|->
name|width
expr_stmt|;
name|new_image_height
operator|=
name|gimage
operator|->
name|height
expr_stmt|;
name|size_changed
operator|=
name|FALSE
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
return|return;
block|}
comment|/*  Rotate all channels  */
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
name|gimp_item_rotate
argument_list|(
name|item
argument_list|,
name|rotate_type
argument_list|,
name|center_x
argument_list|,
name|center_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|item
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|item
operator|->
name|offset_y
operator|=
literal|0
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
comment|/*  Rotate all vectors  */
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
name|gimp_item_rotate
argument_list|(
name|item
argument_list|,
name|rotate_type
argument_list|,
name|center_x
argument_list|,
name|center_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|item
operator|->
name|width
operator|=
name|new_image_width
expr_stmt|;
name|item
operator|->
name|height
operator|=
name|new_image_height
expr_stmt|;
name|item
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|item
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
name|gimp_item_translate
argument_list|(
name|item
argument_list|,
operator|(
name|new_image_width
operator|-
name|gimage
operator|->
name|width
operator|)
operator|/
literal|2
argument_list|,
operator|(
name|new_image_height
operator|-
name|gimage
operator|->
name|height
operator|)
operator|/
literal|2
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
name|gimp_item_rotate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
argument_list|,
name|rotate_type
argument_list|,
name|center_x
argument_list|,
name|center_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|gimage
operator|->
name|selection_mask
argument_list|)
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|gimage
operator|->
name|selection_mask
argument_list|)
operator|->
name|offset_y
operator|=
literal|0
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
comment|/*  Rotate all layers  */
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
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
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
name|gimp_item_offsets
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
name|gimp_item_rotate
argument_list|(
name|item
argument_list|,
name|rotate_type
argument_list|,
name|center_x
argument_list|,
name|center_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_rotate_item_offset
argument_list|(
name|gimage
argument_list|,
name|rotate_type
argument_list|,
name|item
argument_list|,
name|off_x
argument_list|,
name|off_y
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
comment|/*  Rotate all Guides  */
name|gimp_image_rotate_guides
argument_list|(
name|gimage
argument_list|,
name|rotate_type
argument_list|)
expr_stmt|;
comment|/*  Resize the image (if needed)  */
if|if
condition|(
name|size_changed
condition|)
block|{
name|gimp_image_undo_push_image_size
argument_list|(
name|gimage
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimage
operator|->
name|width
operator|=
name|new_image_width
expr_stmt|;
name|gimage
operator|->
name|height
operator|=
name|new_image_height
expr_stmt|;
if|if
condition|(
name|gimage
operator|->
name|xresolution
operator|!=
name|gimage
operator|->
name|yresolution
condition|)
block|{
name|gdouble
name|tmp
decl_stmt|;
name|gimp_image_undo_push_image_resolution
argument_list|(
name|gimage
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|gimage
operator|->
name|xresolution
expr_stmt|;
name|gimage
operator|->
name|yresolution
operator|=
name|gimage
operator|->
name|xresolution
expr_stmt|;
name|gimage
operator|->
name|xresolution
operator|=
name|tmp
expr_stmt|;
block|}
block|}
comment|/*  Make sure the projection matches the gimage size  */
name|gimp_image_projection_allocate
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/*  Rigor the floating selection  */
if|if
condition|(
name|floating_layer
condition|)
name|floating_sel_rigor
argument_list|(
name|floating_layer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|size_changed
condition|)
name|gimp_viewable_size_changed
argument_list|(
name|GIMP_VIEWABLE
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

begin_function
specifier|static
name|void
DECL|function|gimp_image_rotate_item_offset (GimpImage * gimage,GimpRotationType rotate_type,GimpItem * item,gint off_x,gint off_y)
name|gimp_image_rotate_item_offset
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpRotationType
name|rotate_type
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
block|{
name|gint
name|x
init|=
literal|0
decl_stmt|;
name|gint
name|y
init|=
literal|0
decl_stmt|;
switch|switch
condition|(
name|rotate_type
condition|)
block|{
case|case
name|GIMP_ROTATE_90
case|:
name|x
operator|=
name|gimage
operator|->
name|height
operator|-
name|off_y
operator|-
name|gimp_item_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|y
operator|=
name|off_x
expr_stmt|;
break|break;
case|case
name|GIMP_ROTATE_270
case|:
name|x
operator|=
name|off_y
expr_stmt|;
name|y
operator|=
name|gimage
operator|->
name|width
operator|-
name|off_x
operator|-
name|gimp_item_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ROTATE_180
case|:
return|return;
block|}
name|gimp_item_offsets
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
name|x
operator|-=
name|off_x
expr_stmt|;
name|y
operator|-=
name|off_y
expr_stmt|;
if|if
condition|(
name|x
operator|||
name|y
condition|)
name|gimp_item_translate
argument_list|(
name|item
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_rotate_guides (GimpImage * gimage,GimpRotationType rotate_type)
name|gimp_image_rotate_guides
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpRotationType
name|rotate_type
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
comment|/*  Rotate all Guides  */
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
name|rotate_type
condition|)
block|{
case|case
name|GIMP_ROTATE_90
case|:
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
name|gimp_image_undo_push_image_guide
argument_list|(
name|gimage
argument_list|,
name|NULL
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|guide
operator|->
name|orientation
operator|=
name|GIMP_ORIENTATION_VERTICAL
expr_stmt|;
name|guide
operator|->
name|position
operator|=
name|gimage
operator|->
name|height
operator|-
name|guide
operator|->
name|position
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|gimp_image_undo_push_image_guide
argument_list|(
name|gimage
argument_list|,
name|NULL
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|guide
operator|->
name|orientation
operator|=
name|GIMP_ORIENTATION_HORIZONTAL
expr_stmt|;
break|break;
default|default:
break|break;
block|}
break|break;
case|case
name|GIMP_ROTATE_180
case|:
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
break|break;
case|case
name|GIMP_ROTATE_270
case|:
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
name|gimp_image_undo_push_image_guide
argument_list|(
name|gimage
argument_list|,
name|NULL
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|guide
operator|->
name|orientation
operator|=
name|GIMP_ORIENTATION_VERTICAL
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|gimp_image_undo_push_image_guide
argument_list|(
name|gimage
argument_list|,
name|NULL
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|guide
operator|->
name|orientation
operator|=
name|GIMP_ORIENTATION_HORIZONTAL
expr_stmt|;
name|guide
operator|->
name|position
operator|=
name|gimage
operator|->
name|width
operator|-
name|guide
operator|->
name|position
expr_stmt|;
break|break;
default|default:
break|break;
block|}
break|break;
block|}
block|}
block|}
end_function

end_unit

