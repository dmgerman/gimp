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
file|"gimpchannel.h"
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
file|"gimpimage-projection.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-scale.h"
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
file|"floating_sel.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
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
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpLayer
modifier|*
name|floating_layer
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GSList
modifier|*
name|remove
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|slist
decl_stmt|;
name|GimpGuide
modifier|*
name|guide
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
name|num_channels
decl_stmt|;
name|gint
name|num_layers
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
name|num_channels
operator|=
name|gimage
operator|->
name|channels
operator|->
name|num_children
expr_stmt|;
name|num_layers
operator|=
name|gimage
operator|->
name|layers
operator|->
name|num_children
expr_stmt|;
comment|/*  Get the floating layer if one exists  */
name|floating_layer
operator|=
name|gimp_image_floating_sel
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|undo_push_group_start
argument_list|(
name|gimage
argument_list|,
name|IMAGE_SCALE_UNDO
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
name|undo_push_gimage_mod
argument_list|(
name|gimage
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
name|channel
operator|=
operator|(
name|GimpChannel
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gimp_channel_scale
argument_list|(
name|channel
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|,
name|interpolation_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress_func
condition|)
block|{
call|(
modifier|*
name|progress_func
call|)
argument_list|(
literal|0
argument_list|,
name|num_channels
operator|+
name|num_layers
argument_list|,
name|progress_current
operator|++
argument_list|,
name|progress_data
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  Don't forget the selection mask!  */
comment|/*  if (channel_is_empty(gimage->selection_mask))         gimp_channel_resize(gimage->selection_mask, new_width, new_height, 0, 0)       else   */
name|gimp_channel_scale
argument_list|(
name|gimage
operator|->
name|selection_mask
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|,
name|interpolation_type
argument_list|)
expr_stmt|;
name|gimp_image_mask_invalidate
argument_list|(
name|gimage
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
name|layer
operator|=
operator|(
name|GimpLayer
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_layer_scale_by_factors
argument_list|(
name|layer
argument_list|,
name|img_scale_w
argument_list|,
name|img_scale_h
argument_list|,
name|interpolation_type
argument_list|)
condition|)
block|{
comment|/* Since 0< img_scale_w, img_scale_h, failure due to one or more 	   * vanishing scaled layer dimensions. Implicit delete implemented 	   * here. Upstream warning implemented in resize_check_layer_scaling() 	   * [resize.c line 1295], which offers the user the chance to bail out. 	   */
name|remove
operator|=
name|g_slist_append
argument_list|(
name|remove
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|progress_func
condition|)
block|{
call|(
modifier|*
name|progress_func
call|)
argument_list|(
literal|0
argument_list|,
name|num_channels
operator|+
name|num_layers
argument_list|,
name|progress_current
operator|++
argument_list|,
name|progress_data
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* We defer removing layers lost to scaling until now so as not to mix    * the operations of iterating over and removal from gimage->layers.    */
for|for
control|(
name|slist
operator|=
name|remove
init|;
name|slist
condition|;
name|slist
operator|=
name|g_slist_next
argument_list|(
name|slist
argument_list|)
control|)
block|{
name|layer
operator|=
name|slist
operator|->
name|data
expr_stmt|;
name|gimp_image_remove_layer
argument_list|(
name|gimage
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|remove
argument_list|)
expr_stmt|;
comment|/*  Scale any Guides  */
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
name|guide
operator|=
operator|(
name|GimpGuide
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
switch|switch
condition|(
name|guide
operator|->
name|orientation
condition|)
block|{
case|case
name|ORIENTATION_HORIZONTAL
case|:
name|undo_push_guide
argument_list|(
name|gimage
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
name|ORIENTATION_VERTICAL
case|:
name|undo_push_guide
argument_list|(
name|gimage
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
name|g_error
argument_list|(
literal|"Unknown guide orientation II.\n"
argument_list|)
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
name|undo_push_group_end
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
comment|/**  * gimp_image_check_scaling:  * @gimage:     A #GimpImage.  * @new_width:  The new width.  * @new_height: The new height.  *   * Inventory the layer list in gimage and return #TRUE if, after  * scaling, they all retain positive x and y pixel dimensions.  *   * Return value: #TRUE if scaling the image will shrink none of it's  *               layers completely away.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_check_scaling (const GimpImage * gimage,gint new_width,gint new_height)
name|gimp_image_check_scaling
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
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|layer
operator|=
operator|(
name|GimpLayer
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_layer_check_scaling
argument_list|(
name|layer
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|)
condition|)
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

