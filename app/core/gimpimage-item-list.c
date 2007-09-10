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
file|"core-types.h"
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
file|"gimpimage-item-list.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo.h"
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

begin_include
include|#
directive|include
file|"gimpprogress.h"
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
DECL|function|gimp_image_item_list_translate (GimpImage * image,GList * list,gint offset_x,gint offset_y,gboolean push_undo)
name|gimp_image_item_list_translate
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GList
modifier|*
name|list
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|gboolean
name|push_undo
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
name|list
condition|)
block|{
name|GList
modifier|*
name|l
decl_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_ITEM_DISPLACE
argument_list|,
name|_
argument_list|(
literal|"Translate Items"
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|l
operator|=
name|list
init|;
name|l
condition|;
name|l
operator|=
name|g_list_next
argument_list|(
name|l
argument_list|)
control|)
name|gimp_item_translate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|l
operator|->
name|data
argument_list|)
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_item_list_flip (GimpImage * image,GList * list,GimpContext * context,GimpOrientationType flip_type,gdouble axis,gboolean clip_result)
name|gimp_image_item_list_flip
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GList
modifier|*
name|list
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|,
name|gdouble
name|axis
parameter_list|,
name|gboolean
name|clip_result
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
block|{
name|GList
modifier|*
name|l
decl_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_TRANSFORM
argument_list|,
name|_
argument_list|(
literal|"Flip Items"
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|l
operator|=
name|list
init|;
name|l
condition|;
name|l
operator|=
name|g_list_next
argument_list|(
name|l
argument_list|)
control|)
name|gimp_item_flip
argument_list|(
name|GIMP_ITEM
argument_list|(
name|l
operator|->
name|data
argument_list|)
argument_list|,
name|context
argument_list|,
name|flip_type
argument_list|,
name|axis
argument_list|,
name|clip_result
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_item_list_rotate (GimpImage * image,GList * list,GimpContext * context,GimpRotationType rotate_type,gdouble center_x,gdouble center_y,gboolean clip_result)
name|gimp_image_item_list_rotate
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GList
modifier|*
name|list
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpRotationType
name|rotate_type
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|,
name|gboolean
name|clip_result
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
block|{
name|GList
modifier|*
name|l
decl_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_TRANSFORM
argument_list|,
name|_
argument_list|(
literal|"Rotate Items"
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|l
operator|=
name|list
init|;
name|l
condition|;
name|l
operator|=
name|g_list_next
argument_list|(
name|l
argument_list|)
control|)
name|gimp_item_rotate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|l
operator|->
name|data
argument_list|)
argument_list|,
name|context
argument_list|,
name|rotate_type
argument_list|,
name|center_x
argument_list|,
name|center_y
argument_list|,
name|clip_result
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_item_list_transform (GimpImage * image,GList * list,GimpContext * context,const GimpMatrix3 * matrix,GimpTransformDirection direction,GimpInterpolationType interpolation_type,gint recursion_level,GimpTransformResize clip_result,GimpProgress * progress)
name|gimp_image_item_list_transform
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GList
modifier|*
name|list
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|GimpTransformDirection
name|direction
parameter_list|,
name|GimpInterpolationType
name|interpolation_type
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|GimpTransformResize
name|clip_result
parameter_list|,
name|GimpProgress
modifier|*
name|progress
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
if|if
condition|(
name|list
condition|)
block|{
name|GList
modifier|*
name|l
decl_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_TRANSFORM
argument_list|,
name|_
argument_list|(
literal|"Transform Items"
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|l
operator|=
name|list
init|;
name|l
condition|;
name|l
operator|=
name|g_list_next
argument_list|(
name|l
argument_list|)
control|)
name|gimp_item_transform
argument_list|(
name|GIMP_ITEM
argument_list|(
name|l
operator|->
name|data
argument_list|)
argument_list|,
name|context
argument_list|,
name|matrix
argument_list|,
name|direction
argument_list|,
name|interpolation_type
argument_list|,
name|recursion_level
argument_list|,
name|clip_result
argument_list|,
name|progress
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_image_item_list_get_list:  * @image:   An @image.  * @exclude: An item to exclude.  * @type:    Which type of items to return.  * @set:     Set the returned items are part of.  *  * This function returns a #GList of #GimpItem<!-- -->s for which the  * @type and @set criterions match.  *  * Return value: The list of items, excluding @exclude.  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_image_item_list_get_list (GimpImage * image,GimpItem * exclude,GimpItemTypeMask type,GimpItemSet set)
name|gimp_image_item_list_get_list
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpItem
modifier|*
name|exclude
parameter_list|,
name|GimpItemTypeMask
name|type
parameter_list|,
name|GimpItemSet
name|set
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GList
modifier|*
name|return_list
init|=
name|NULL
decl_stmt|;
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
name|g_return_val_if_fail
argument_list|(
name|exclude
operator|==
name|NULL
operator|||
name|GIMP_IS_ITEM
argument_list|(
name|exclude
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|type
operator|&
name|GIMP_ITEM_TYPE_LAYERS
condition|)
block|{
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|image
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
if|if
condition|(
name|item
operator|!=
name|exclude
operator|&&
name|gimp_item_is_in_set
argument_list|(
name|item
argument_list|,
name|set
argument_list|)
condition|)
name|return_list
operator|=
name|g_list_prepend
argument_list|(
name|return_list
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|type
operator|&
name|GIMP_ITEM_TYPE_CHANNELS
condition|)
block|{
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|image
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
if|if
condition|(
name|item
operator|!=
name|exclude
operator|&&
name|gimp_item_is_in_set
argument_list|(
name|item
argument_list|,
name|set
argument_list|)
condition|)
name|return_list
operator|=
name|g_list_prepend
argument_list|(
name|return_list
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|type
operator|&
name|GIMP_ITEM_TYPE_VECTORS
condition|)
block|{
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|image
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
if|if
condition|(
name|item
operator|!=
name|exclude
operator|&&
name|gimp_item_is_in_set
argument_list|(
name|item
argument_list|,
name|set
argument_list|)
condition|)
name|return_list
operator|=
name|g_list_prepend
argument_list|(
name|return_list
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|g_list_reverse
argument_list|(
name|return_list
argument_list|)
return|;
block|}
end_function

end_unit

