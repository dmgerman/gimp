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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_comment
comment|/* FIXME: remove the Path<-> BezierSelect dependency */
end_comment

begin_include
include|#
directive|include
file|"tools/tools-types.h"
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
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-duplicate.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-new.h"
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
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"floating_sel.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"parasitelist.h"
end_include

begin_include
include|#
directive|include
file|"path.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_image_duplicate (GimpImage * gimage)
name|gimp_image_duplicate
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|GimpImage
modifier|*
name|new_gimage
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|,
modifier|*
name|new_layer
decl_stmt|;
name|GimpLayer
modifier|*
name|floating_layer
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|,
modifier|*
name|new_channel
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpGuide
modifier|*
name|guide
init|=
name|NULL
decl_stmt|;
name|GimpLayer
modifier|*
name|active_layer
init|=
name|NULL
decl_stmt|;
name|GimpChannel
modifier|*
name|active_channel
init|=
name|NULL
decl_stmt|;
name|GimpDrawable
modifier|*
name|new_floating_sel_drawable
init|=
name|NULL
decl_stmt|;
name|GimpDrawable
modifier|*
name|floating_sel_drawable
init|=
name|NULL
decl_stmt|;
name|GimpParasiteList
modifier|*
name|parasites
decl_stmt|;
name|PathList
modifier|*
name|paths
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimage
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_set_busy_until_idle
argument_list|()
expr_stmt|;
comment|/*  Create a new image  */
name|new_gimage
operator|=
name|gimp_create_image
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|,
name|gimage
operator|->
name|base_type
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|new_gimage
argument_list|)
expr_stmt|;
comment|/*  Copy resolution and unit information  */
name|new_gimage
operator|->
name|xresolution
operator|=
name|gimage
operator|->
name|xresolution
expr_stmt|;
name|new_gimage
operator|->
name|yresolution
operator|=
name|gimage
operator|->
name|yresolution
expr_stmt|;
name|new_gimage
operator|->
name|unit
operator|=
name|gimage
operator|->
name|unit
expr_stmt|;
comment|/*  Copy floating layer  */
name|floating_layer
operator|=
name|gimp_image_floating_sel
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|floating_layer
condition|)
block|{
name|floating_sel_relax
argument_list|(
name|floating_layer
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|floating_sel_drawable
operator|=
name|floating_layer
operator|->
name|fs
operator|.
name|drawable
expr_stmt|;
name|floating_layer
operator|=
name|NULL
expr_stmt|;
block|}
comment|/*  Copy the layers  */
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
operator|,
name|count
operator|=
literal|0
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
operator|,
name|count
operator|++
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
name|new_layer
operator|=
name|gimp_layer_copy
argument_list|(
name|layer
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_drawable_set_gimage
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|new_layer
argument_list|)
argument_list|,
name|new_gimage
argument_list|)
expr_stmt|;
comment|/*  Make sure the copied layer doesn't say: "<old layer> copy"  */
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|new_layer
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Make sure if the layer has a layer mask, it's name isn't screwed up  */
if|if
condition|(
name|new_layer
operator|->
name|mask
condition|)
block|{
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|new_layer
operator|->
name|mask
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|layer
operator|->
name|mask
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_image_get_active_layer
argument_list|(
name|gimage
argument_list|)
operator|==
name|layer
condition|)
name|active_layer
operator|=
name|new_layer
expr_stmt|;
if|if
condition|(
name|gimage
operator|->
name|floating_sel
operator|==
name|layer
condition|)
name|floating_layer
operator|=
name|new_layer
expr_stmt|;
if|if
condition|(
name|floating_sel_drawable
operator|==
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
condition|)
name|new_floating_sel_drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|new_layer
argument_list|)
expr_stmt|;
comment|/*  Add the layer  */
if|if
condition|(
name|floating_layer
operator|!=
name|new_layer
condition|)
name|gimp_image_add_layer
argument_list|(
name|new_gimage
argument_list|,
name|new_layer
argument_list|,
name|count
argument_list|)
expr_stmt|;
block|}
comment|/*  Copy the channels  */
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
operator|,
name|count
operator|=
literal|0
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
operator|,
name|count
operator|++
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
name|new_channel
operator|=
name|gimp_channel_copy
argument_list|(
name|channel
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_set_gimage
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|new_channel
argument_list|)
argument_list|,
name|new_gimage
argument_list|)
expr_stmt|;
comment|/*  Make sure the copied channel doesn't say: "<old channel> copy"  */
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|new_channel
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|channel
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_get_active_channel
argument_list|(
name|gimage
argument_list|)
operator|==
name|channel
condition|)
name|active_channel
operator|=
operator|(
name|new_channel
operator|)
expr_stmt|;
if|if
condition|(
name|floating_sel_drawable
operator|==
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
condition|)
name|new_floating_sel_drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|new_channel
argument_list|)
expr_stmt|;
comment|/*  Add the channel  */
name|gimp_image_add_channel
argument_list|(
name|new_gimage
argument_list|,
name|new_channel
argument_list|,
name|count
argument_list|)
expr_stmt|;
block|}
comment|/*  Copy the selection mask  */
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|gimage
operator|->
name|selection_mask
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|new_gimage
operator|->
name|selection_mask
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|new_gimage
operator|->
name|selection_mask
operator|->
name|bounds_known
operator|=
name|FALSE
expr_stmt|;
name|new_gimage
operator|->
name|selection_mask
operator|->
name|boundary_known
operator|=
name|FALSE
expr_stmt|;
comment|/*  Set active layer, active channel  */
if|if
condition|(
name|active_layer
condition|)
name|gimp_image_set_active_layer
argument_list|(
name|new_gimage
argument_list|,
name|active_layer
argument_list|)
expr_stmt|;
if|if
condition|(
name|active_channel
condition|)
name|gimp_image_set_active_channel
argument_list|(
name|new_gimage
argument_list|,
name|active_channel
argument_list|)
expr_stmt|;
if|if
condition|(
name|floating_layer
condition|)
name|floating_sel_attach
argument_list|(
name|floating_layer
argument_list|,
name|new_floating_sel_drawable
argument_list|)
expr_stmt|;
comment|/*  Copy the colormap if necessary  */
if|if
condition|(
name|new_gimage
operator|->
name|base_type
operator|==
name|INDEXED
condition|)
name|memcpy
argument_list|(
name|new_gimage
operator|->
name|cmap
argument_list|,
name|gimage
operator|->
name|cmap
argument_list|,
name|gimage
operator|->
name|num_cols
operator|*
literal|3
argument_list|)
expr_stmt|;
name|new_gimage
operator|->
name|num_cols
operator|=
name|gimage
operator|->
name|num_cols
expr_stmt|;
comment|/*  copy state of all color channels  */
for|for
control|(
name|count
operator|=
literal|0
init|;
name|count
operator|<
name|MAX_CHANNELS
condition|;
name|count
operator|++
control|)
block|{
name|new_gimage
operator|->
name|visible
index|[
name|count
index|]
operator|=
name|gimage
operator|->
name|visible
index|[
name|count
index|]
expr_stmt|;
name|new_gimage
operator|->
name|active
index|[
name|count
index|]
operator|=
name|gimage
operator|->
name|active
index|[
name|count
index|]
expr_stmt|;
block|}
comment|/*  Copy any Guides  */
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
name|new_guide
decl_stmt|;
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
name|new_guide
operator|=
name|gimp_image_add_hguide
argument_list|(
name|new_gimage
argument_list|)
expr_stmt|;
name|new_guide
operator|->
name|position
operator|=
name|guide
operator|->
name|position
expr_stmt|;
break|break;
case|case
name|ORIENTATION_VERTICAL
case|:
name|new_guide
operator|=
name|gimp_image_add_vguide
argument_list|(
name|new_gimage
argument_list|)
expr_stmt|;
name|new_guide
operator|->
name|position
operator|=
name|guide
operator|->
name|position
expr_stmt|;
break|break;
default|default:
name|g_error
argument_list|(
literal|"Unknown guide orientation.\n"
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* Copy the qmask info */
name|new_gimage
operator|->
name|qmask_state
operator|=
name|gimage
operator|->
name|qmask_state
expr_stmt|;
name|new_gimage
operator|->
name|qmask_color
operator|=
name|gimage
operator|->
name|qmask_color
expr_stmt|;
comment|/* Copy parasites */
name|parasites
operator|=
name|gimage
operator|->
name|parasites
expr_stmt|;
if|if
condition|(
name|parasites
condition|)
name|new_gimage
operator|->
name|parasites
operator|=
name|gimp_parasite_list_copy
argument_list|(
name|parasites
argument_list|)
expr_stmt|;
comment|/* Copy paths */
name|paths
operator|=
name|gimp_image_get_paths
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|paths
condition|)
block|{
name|GSList
modifier|*
name|plist
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|new_plist
init|=
name|NULL
decl_stmt|;
name|Path
modifier|*
name|path
decl_stmt|;
name|PathList
modifier|*
name|new_paths
decl_stmt|;
for|for
control|(
name|plist
operator|=
name|paths
operator|->
name|bz_paths
init|;
name|plist
condition|;
name|plist
operator|=
name|plist
operator|->
name|next
control|)
block|{
name|path
operator|=
name|plist
operator|->
name|data
expr_stmt|;
name|new_plist
operator|=
name|g_slist_append
argument_list|(
name|new_plist
argument_list|,
name|path_copy
argument_list|(
name|new_gimage
argument_list|,
name|path
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|new_paths
operator|=
name|path_list_new
argument_list|(
name|new_gimage
argument_list|,
name|paths
operator|->
name|last_selected_row
argument_list|,
name|new_plist
argument_list|)
expr_stmt|;
name|gimp_image_set_paths
argument_list|(
name|new_gimage
argument_list|,
name|new_paths
argument_list|)
expr_stmt|;
block|}
name|gimp_image_undo_enable
argument_list|(
name|new_gimage
argument_list|)
expr_stmt|;
return|return
name|new_gimage
return|;
block|}
end_function

end_unit

