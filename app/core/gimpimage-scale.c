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
file|"gimpimage-guides.h"
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
file|"gimplayer-floating-sel.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_image_scale (GimpImage * gimage,gint new_width,gint new_height,GimpInterpolationType interpolation_type,GimpProgressFunc progress_func,gpointer progress_data)
name|gimp_image_scale
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|GIMP_UNDO_GROUP_IMAGE_SCALE
argument_list|,
name|_
argument_list|(
literal|"Scale Image"
argument_list|)
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
comment|/*  Push the image size to the stack  */
name|gimp_image_undo_push_image_size
argument_list|(
name|gimage
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Set the new width and height  */
name|old_width
operator|=
name|gimage
operator|->
name|width
expr_stmt|;
name|old_height
operator|=
name|gimage
operator|->
name|height
expr_stmt|;
name|gimage
operator|->
name|width
operator|=
name|new_width
expr_stmt|;
name|gimage
operator|->
name|height
operator|=
name|new_height
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
comment|/*  Scale all channels  */
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
comment|/*  Scale all vectors  */
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
name|gimp_item_scale
argument_list|(
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
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
comment|/*  Scale all layers  */
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
argument_list|)
condition|)
block|{
comment|/* Since 0< img_scale_w, img_scale_h, failure due to one or more 	   * vanishing scaled layer dimensions. Implicit delete implemented 	   * here. Upstream warning implemented in resize_check_layer_scaling(), 	   * which offers the user the chance to bail out. 	   */
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
comment|/* We defer removing layers lost to scaling until now so as not to mix    * the operations of iterating over and removal from gimage->layers.    */
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
name|gimage
argument_list|,
name|layer
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
name|position
operator|=
operator|(
name|guide
operator|->
name|position
operator|*
name|new_height
operator|)
operator|/
name|old_height
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
name|position
operator|=
operator|(
name|guide
operator|->
name|position
operator|*
name|new_width
operator|)
operator|/
name|old_width
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
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

begin_comment
comment|/**  * gimp_image_scale_check:  * @gimage:     A #GimpImage.  * @new_width:  The new width.  * @new_height: The new height.  *  * Inventory the layer list in gimage and check that it may be  * scaled to @new_height and @new_width without problems.  *  * Return value: #GIMP_IMAGE_SCALE_OK if scaling the image will shrink none  *               of its layers completely away, and the new image size  *               is smaller than the maximum specified in the  *               preferences.  *               #GIMP_IMAGE_SCALE_TOO_SMALL if scaling would remove some  *               existing layers.  *               #GIMP_IMAGE_SCALE_TOO_BIG if the new image size would  *               exceed the maximum specified in the preferences.  **/
end_comment

begin_function
name|GimpImageScaleCheckType
DECL|function|gimp_image_scale_check (const GimpImage * gimage,gint new_width,gint new_height)
name|gimp_image_scale_check
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|glong
name|curr_size
decl_stmt|;
name|glong
name|new_size
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|GIMP_IMAGE_SCALE_TOO_SMALL
argument_list|)
expr_stmt|;
name|curr_size
operator|=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|new_size
operator|=
operator|(
name|curr_size
operator|*
operator|(
operator|(
name|gdouble
operator|)
name|new_width
operator|/
name|gimp_image_get_width
argument_list|(
name|gimage
argument_list|)
operator|)
operator|*
operator|(
operator|(
name|gdouble
operator|)
name|new_height
operator|/
name|gimp_image_get_height
argument_list|(
name|gimage
argument_list|)
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|new_size
operator|>
name|curr_size
operator|&&
name|new_size
operator|>
name|GIMP_GUI_CONFIG
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|max_new_image_size
condition|)
return|return
name|GIMP_IMAGE_SCALE_TOO_BIG
return|;
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

