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
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
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
file|"gimpimage-colorhash.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-merge.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo.h"
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
file|"gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpparasitelist.h"
end_include

begin_include
include|#
directive|include
file|"gimpundostack.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|GimpLayer
modifier|*
name|gimp_image_merge_layers
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GSList
modifier|*
name|merge_list
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpMergeType
name|merge_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_image_merge_visible_layers (GimpImage * image,GimpContext * context,GimpMergeType merge_type,gboolean discard_invisible)
name|gimp_image_merge_visible_layers
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpMergeType
name|merge_type
parameter_list|,
name|gboolean
name|discard_invisible
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GSList
modifier|*
name|merge_list
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|invisible_list
init|=
name|NULL
decl_stmt|;
name|gboolean
name|had_floating_sel
init|=
name|FALSE
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* if there's a floating selection, anchor it */
if|if
condition|(
name|gimp_image_floating_sel
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|floating_sel_anchor
argument_list|(
name|image
operator|->
name|floating_sel
argument_list|)
expr_stmt|;
name|had_floating_sel
operator|=
name|TRUE
expr_stmt|;
block|}
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
name|layer
operator|=
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
condition|)
block|{
name|merge_list
operator|=
name|g_slist_append
argument_list|(
name|merge_list
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|discard_invisible
condition|)
block|{
name|invisible_list
operator|=
name|g_slist_append
argument_list|(
name|invisible_list
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|merge_list
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|undo_desc
init|=
name|_
argument_list|(
literal|"Merge Visible Layers"
argument_list|)
decl_stmt|;
name|gimp_set_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|invisible_list
condition|)
block|{
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_LAYERS_MERGE
argument_list|,
name|undo_desc
argument_list|)
expr_stmt|;
block|}
name|layer
operator|=
name|gimp_image_merge_layers
argument_list|(
name|image
argument_list|,
name|merge_list
argument_list|,
name|context
argument_list|,
name|merge_type
argument_list|,
name|_
argument_list|(
literal|"Merge Visible Layers"
argument_list|)
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|merge_list
argument_list|)
expr_stmt|;
if|if
condition|(
name|invisible_list
condition|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|invisible_list
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
name|gimp_image_remove_layer
argument_list|(
name|image
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|invisible_list
argument_list|)
expr_stmt|;
block|}
name|gimp_unset_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
return|return
name|layer
return|;
block|}
return|return
name|gimp_image_get_active_layer
argument_list|(
name|image
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_image_flatten (GimpImage * image,GimpContext * context)
name|gimp_image_flatten
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GSList
modifier|*
name|merge_list
init|=
name|NULL
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_set_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
comment|/* if there's a floating selection, anchor it */
if|if
condition|(
name|gimp_image_floating_sel
argument_list|(
name|image
argument_list|)
condition|)
name|floating_sel_anchor
argument_list|(
name|image
operator|->
name|floating_sel
argument_list|)
expr_stmt|;
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
name|layer
operator|=
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
condition|)
name|merge_list
operator|=
name|g_slist_append
argument_list|(
name|merge_list
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
name|layer
operator|=
name|gimp_image_merge_layers
argument_list|(
name|image
argument_list|,
name|merge_list
argument_list|,
name|context
argument_list|,
name|GIMP_FLATTEN_IMAGE
argument_list|,
name|_
argument_list|(
literal|"Flatten Image"
argument_list|)
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|merge_list
argument_list|)
expr_stmt|;
name|gimp_image_alpha_changed
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
return|return
name|layer
return|;
block|}
end_function

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_image_merge_down (GimpImage * image,GimpLayer * current_layer,GimpContext * context,GimpMergeType merge_type)
name|gimp_image_merge_down
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpLayer
modifier|*
name|current_layer
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpMergeType
name|merge_type
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GList
modifier|*
name|layer_list
decl_stmt|;
name|GSList
modifier|*
name|merge_list
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
operator|,
name|layer_list
operator|=
name|NULL
init|;
name|list
operator|&&
operator|!
name|layer_list
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
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|layer
operator|==
name|current_layer
condition|)
break|break;
block|}
for|for
control|(
name|layer_list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
operator|,
name|merge_list
operator|=
name|NULL
init|;
name|layer_list
operator|&&
operator|!
name|merge_list
condition|;
name|layer_list
operator|=
name|g_list_next
argument_list|(
name|layer_list
argument_list|)
control|)
block|{
name|layer
operator|=
name|layer_list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
condition|)
name|merge_list
operator|=
name|g_slist_append
argument_list|(
name|NULL
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
name|merge_list
operator|=
name|g_slist_prepend
argument_list|(
name|merge_list
argument_list|,
name|current_layer
argument_list|)
expr_stmt|;
name|gimp_set_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_image_merge_layers
argument_list|(
name|image
argument_list|,
name|merge_list
argument_list|,
name|context
argument_list|,
name|merge_type
argument_list|,
name|_
argument_list|(
literal|"Merge Down"
argument_list|)
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|merge_list
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_comment
comment|/* merging vectors */
end_comment

begin_function
name|GimpVectors
modifier|*
DECL|function|gimp_image_merge_visible_vectors (GimpImage * image,GError ** error)
name|gimp_image_merge_visible_vectors
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|merge_list
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|cur_item
init|=
name|NULL
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
init|=
name|NULL
decl_stmt|;
name|GimpVectors
modifier|*
name|target_vectors
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|gint
name|pos
init|=
literal|0
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
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|vectors
operator|=
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
condition|)
name|merge_list
operator|=
name|g_slist_append
argument_list|(
name|merge_list
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|merge_list
operator|&&
name|merge_list
operator|->
name|next
condition|)
block|{
name|gimp_set_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_VECTORS_MERGE
argument_list|,
name|_
argument_list|(
literal|"Merge Visible Paths"
argument_list|)
argument_list|)
expr_stmt|;
name|cur_item
operator|=
name|merge_list
expr_stmt|;
name|vectors
operator|=
name|GIMP_VECTORS
argument_list|(
name|cur_item
operator|->
name|data
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_strdup
argument_list|(
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|vectors
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|target_vectors
operator|=
name|GIMP_VECTORS
argument_list|(
name|gimp_item_duplicate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|GIMP_TYPE_VECTORS
argument_list|)
argument_list|)
expr_stmt|;
name|pos
operator|=
name|gimp_image_get_vectors_index
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|gimp_image_remove_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|cur_item
operator|=
name|cur_item
operator|->
name|next
expr_stmt|;
while|while
condition|(
name|cur_item
condition|)
block|{
name|vectors
operator|=
name|GIMP_VECTORS
argument_list|(
name|cur_item
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_vectors_add_strokes
argument_list|(
name|vectors
argument_list|,
name|target_vectors
argument_list|)
expr_stmt|;
name|gimp_image_remove_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|cur_item
operator|=
name|g_slist_next
argument_list|(
name|cur_item
argument_list|)
expr_stmt|;
block|}
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|target_vectors
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|merge_list
argument_list|)
expr_stmt|;
name|gimp_image_add_vectors
argument_list|(
name|image
argument_list|,
name|target_vectors
argument_list|,
name|pos
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|target_vectors
return|;
block|}
else|else
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Not enough visible paths for a merge. "
literal|"There must be at least two."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|CombinationMode
DECL|function|gimp_image_merge_layers_get_operation (GimpLayer * dest,GimpLayer * src)
name|gimp_image_merge_layers_get_operation
parameter_list|(
name|GimpLayer
modifier|*
name|dest
parameter_list|,
name|GimpLayer
modifier|*
name|src
parameter_list|)
block|{
name|GimpImageType
name|type
init|=
name|gimp_drawable_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|dest
argument_list|)
argument_list|)
decl_stmt|;
name|gint
name|bytes
init|=
name|gimp_drawable_bytes
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|src
argument_list|)
argument_list|)
decl_stmt|;
return|return
name|gimp_image_get_combination_mode
argument_list|(
name|type
argument_list|,
name|bytes
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpLayer
modifier|*
DECL|function|gimp_image_merge_layers (GimpImage * image,GSList * merge_list,GimpContext * context,GimpMergeType merge_type,const gchar * undo_desc)
name|gimp_image_merge_layers
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GSList
modifier|*
name|merge_list
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpMergeType
name|merge_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GSList
modifier|*
name|reverse_list
init|=
name|NULL
decl_stmt|;
name|PixelRegion
name|src1PR
decl_stmt|,
name|src2PR
decl_stmt|,
name|maskPR
decl_stmt|;
name|PixelRegion
modifier|*
name|mask
decl_stmt|;
name|GimpLayer
modifier|*
name|merge_layer
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpLayer
modifier|*
name|bottom_layer
decl_stmt|;
name|GimpImageType
name|type
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|x3
decl_stmt|,
name|y3
decl_stmt|,
name|x4
decl_stmt|,
name|y4
decl_stmt|;
name|CombinationMode
name|operation
decl_stmt|;
name|gint
name|position
decl_stmt|;
name|gboolean
name|active
index|[
name|MAX_CHANNELS
index|]
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
name|TRUE
block|,
name|TRUE
block|}
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gchar
modifier|*
name|name
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|layer
operator|=
name|NULL
expr_stmt|;
name|type
operator|=
name|GIMP_RGBA_IMAGE
expr_stmt|;
name|x1
operator|=
name|y1
operator|=
literal|0
expr_stmt|;
name|x2
operator|=
name|y2
operator|=
literal|0
expr_stmt|;
name|bottom_layer
operator|=
name|NULL
expr_stmt|;
comment|/*  Get the layer extents  */
name|count
operator|=
literal|0
expr_stmt|;
while|while
condition|(
name|merge_list
condition|)
block|{
name|layer
operator|=
name|merge_list
operator|->
name|data
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|merge_type
condition|)
block|{
case|case
name|GIMP_EXPAND_AS_NECESSARY
case|:
case|case
name|GIMP_CLIP_TO_IMAGE
case|:
if|if
condition|(
operator|!
name|count
condition|)
block|{
name|x1
operator|=
name|off_x
expr_stmt|;
name|y1
operator|=
name|off_y
expr_stmt|;
name|x2
operator|=
name|off_x
operator|+
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|off_y
operator|+
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|off_x
operator|<
name|x1
condition|)
name|x1
operator|=
name|off_x
expr_stmt|;
if|if
condition|(
name|off_y
operator|<
name|y1
condition|)
name|y1
operator|=
name|off_y
expr_stmt|;
if|if
condition|(
operator|(
name|off_x
operator|+
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
operator|>
name|x2
condition|)
name|x2
operator|=
operator|(
name|off_x
operator|+
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
operator|(
name|off_y
operator|+
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
operator|>
name|y2
condition|)
name|y2
operator|=
operator|(
name|off_y
operator|+
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
expr_stmt|;
block|}
if|if
condition|(
name|merge_type
operator|==
name|GIMP_CLIP_TO_IMAGE
condition|)
block|{
name|x1
operator|=
name|CLAMP
argument_list|(
name|x1
argument_list|,
literal|0
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|y1
argument_list|,
literal|0
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|x2
argument_list|,
literal|0
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|y2
argument_list|,
literal|0
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_CLIP_TO_BOTTOM_LAYER
case|:
if|if
condition|(
name|merge_list
operator|->
name|next
operator|==
name|NULL
condition|)
block|{
name|x1
operator|=
name|off_x
expr_stmt|;
name|y1
operator|=
name|off_y
expr_stmt|;
name|x2
operator|=
name|off_x
operator|+
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|off_y
operator|+
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_FLATTEN_IMAGE
case|:
if|if
condition|(
name|merge_list
operator|->
name|next
operator|==
name|NULL
condition|)
block|{
name|x1
operator|=
literal|0
expr_stmt|;
name|y1
operator|=
literal|0
expr_stmt|;
name|x2
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|y2
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
name|count
operator|++
expr_stmt|;
name|reverse_list
operator|=
name|g_slist_prepend
argument_list|(
name|reverse_list
argument_list|,
name|layer
argument_list|)
expr_stmt|;
name|merge_list
operator|=
name|g_slist_next
argument_list|(
name|merge_list
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|x2
operator|-
name|x1
operator|)
operator|==
literal|0
operator|||
operator|(
name|y2
operator|-
name|y1
operator|)
operator|==
literal|0
condition|)
return|return
name|NULL
return|;
comment|/*  Start a merge undo group. */
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_LAYERS_MERGE
argument_list|,
name|undo_desc
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_strdup
argument_list|(
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|merge_type
operator|==
name|GIMP_FLATTEN_IMAGE
operator|||
name|gimp_drawable_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|==
name|GIMP_INDEXED_IMAGE
condition|)
block|{
name|guchar
name|bg
index|[
literal|4
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|type
operator|=
name|GIMP_IMAGE_TYPE_FROM_BASE_TYPE
argument_list|(
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|merge_layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|type
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|merge_layer
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: could not allocate merge layer."
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|GIMP_ITEM
argument_list|(
name|merge_layer
argument_list|)
operator|->
name|offset_x
operator|=
name|x1
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|merge_layer
argument_list|)
operator|->
name|offset_y
operator|=
name|y1
expr_stmt|;
comment|/*  get the background for compositing  */
name|gimp_image_get_background
argument_list|(
name|image
argument_list|,
name|context
argument_list|,
name|gimp_drawable_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|merge_layer
argument_list|)
argument_list|)
argument_list|,
name|bg
argument_list|)
expr_stmt|;
comment|/*  init the pixel region  */
name|pixel_region_init
argument_list|(
operator|&
name|src1PR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|merge_layer
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  set the region to the background color  */
name|color_region
argument_list|(
operator|&
name|src1PR
argument_list|,
name|bg
argument_list|)
expr_stmt|;
name|position
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
comment|/*  The final merged layer inherits the name of the bottom most layer        *  and the resulting layer has an alpha channel whether or not the        *  original did. Opacity is set to 100% and the MODE is set to normal.        */
name|merge_layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|gimp_drawable_type_with_alpha
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
literal|"merged layer"
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|merge_layer
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: could not allocate merge layer"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|GIMP_ITEM
argument_list|(
name|merge_layer
argument_list|)
operator|->
name|offset_x
operator|=
name|x1
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|merge_layer
argument_list|)
operator|->
name|offset_y
operator|=
name|y1
expr_stmt|;
comment|/*  clear the layer  */
name|pixel_region_init
argument_list|(
operator|&
name|src1PR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|merge_layer
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|clear_region
argument_list|(
operator|&
name|src1PR
argument_list|)
expr_stmt|;
comment|/*  Find the index in the layer list of the bottom layer--we need this        *  in order to add the final, merged layer to the layer list correctly        */
name|layer
operator|=
name|reverse_list
operator|->
name|data
expr_stmt|;
name|position
operator|=
name|gimp_container_num_children
argument_list|(
name|image
operator|->
name|layers
argument_list|)
operator|-
name|gimp_container_get_child_index
argument_list|(
name|image
operator|->
name|layers
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|bottom_layer
operator|=
name|layer
expr_stmt|;
comment|/* Copy the tattoo and parasites of the bottom layer to the new layer */
name|gimp_item_set_tattoo
argument_list|(
name|GIMP_ITEM
argument_list|(
name|merge_layer
argument_list|)
argument_list|,
name|gimp_item_get_tattoo
argument_list|(
name|GIMP_ITEM
argument_list|(
name|bottom_layer
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|GIMP_ITEM
argument_list|(
name|merge_layer
argument_list|)
operator|->
name|parasites
argument_list|)
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|merge_layer
argument_list|)
operator|->
name|parasites
operator|=
name|gimp_parasite_list_copy
argument_list|(
name|GIMP_ITEM
argument_list|(
name|bottom_layer
argument_list|)
operator|->
name|parasites
argument_list|)
expr_stmt|;
while|while
condition|(
name|reverse_list
condition|)
block|{
name|GimpLayerModeEffects
name|mode
decl_stmt|;
name|layer
operator|=
name|reverse_list
operator|->
name|data
expr_stmt|;
comment|/*  determine what sort of operation is being attempted and        *  if it's actually legal...        */
name|operation
operator|=
name|gimp_image_merge_layers_get_operation
argument_list|(
name|merge_layer
argument_list|,
name|layer
argument_list|)
expr_stmt|;
if|if
condition|(
name|operation
operator|==
operator|-
literal|1
condition|)
block|{
name|gimp_layer_add_alpha
argument_list|(
name|layer
argument_list|)
expr_stmt|;
comment|/*  try again ...  */
name|operation
operator|=
name|gimp_image_merge_layers_get_operation
argument_list|(
name|merge_layer
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|operation
operator|==
operator|-
literal|1
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: attempting to merge incompatible layers."
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|x3
operator|=
name|CLAMP
argument_list|(
name|off_x
argument_list|,
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|y3
operator|=
name|CLAMP
argument_list|(
name|off_y
argument_list|,
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|x4
operator|=
name|CLAMP
argument_list|(
name|off_x
operator|+
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|y4
operator|=
name|CLAMP
argument_list|(
name|off_y
operator|+
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
comment|/* configure the pixel regions  */
name|pixel_region_init
argument_list|(
operator|&
name|src1PR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|merge_layer
argument_list|)
argument_list|)
argument_list|,
operator|(
name|x3
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y3
operator|-
name|y1
operator|)
argument_list|,
operator|(
name|x4
operator|-
name|x3
operator|)
argument_list|,
operator|(
name|y4
operator|-
name|y3
operator|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|src2PR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
operator|(
name|x3
operator|-
name|off_x
operator|)
argument_list|,
operator|(
name|y3
operator|-
name|off_y
operator|)
argument_list|,
operator|(
name|x4
operator|-
name|x3
operator|)
argument_list|,
operator|(
name|y4
operator|-
name|y3
operator|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_layer_get_mask
argument_list|(
name|layer
argument_list|)
operator|&&
name|gimp_layer_mask_get_apply
argument_list|(
name|layer
operator|->
name|mask
argument_list|)
condition|)
block|{
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|tiles
operator|=
name|gimp_drawable_get_tiles
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
operator|->
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|tiles
argument_list|,
operator|(
name|x3
operator|-
name|off_x
operator|)
argument_list|,
operator|(
name|y3
operator|-
name|off_y
operator|)
argument_list|,
operator|(
name|x4
operator|-
name|x3
operator|)
argument_list|,
operator|(
name|y4
operator|-
name|y3
operator|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|mask
operator|=
operator|&
name|maskPR
expr_stmt|;
block|}
else|else
block|{
name|mask
operator|=
name|NULL
expr_stmt|;
block|}
comment|/* DISSOLVE_MODE is special since it is the only mode that does not        *  work on the projection with the lower layer, but only locally on        *  the layers alpha channel.        */
name|mode
operator|=
name|gimp_layer_get_mode
argument_list|(
name|layer
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
operator|==
name|bottom_layer
operator|&&
name|mode
operator|!=
name|GIMP_DISSOLVE_MODE
condition|)
name|mode
operator|=
name|GIMP_NORMAL_MODE
expr_stmt|;
name|combine_regions
argument_list|(
operator|&
name|src1PR
argument_list|,
operator|&
name|src2PR
argument_list|,
operator|&
name|src1PR
argument_list|,
name|mask
argument_list|,
name|NULL
argument_list|,
name|gimp_layer_get_opacity
argument_list|(
name|layer
argument_list|)
operator|*
literal|255.999
argument_list|,
name|mode
argument_list|,
name|active
argument_list|,
name|operation
argument_list|)
expr_stmt|;
name|gimp_image_remove_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|)
expr_stmt|;
name|reverse_list
operator|=
name|g_slist_next
argument_list|(
name|reverse_list
argument_list|)
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|reverse_list
argument_list|)
expr_stmt|;
comment|/*  if the type is flatten, remove all the remaining layers  */
if|if
condition|(
name|merge_type
operator|==
name|GIMP_FLATTEN_IMAGE
condition|)
block|{
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
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|layer
operator|=
name|list
operator|->
name|data
expr_stmt|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|gimp_image_remove_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|merge_layer
argument_list|,
name|position
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  Add the layer to the image  */
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|merge_layer
argument_list|,
name|gimp_container_num_children
argument_list|(
name|image
operator|->
name|layers
argument_list|)
operator|-
name|position
operator|+
literal|1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
comment|/* set the name after the original layers have been removed so we    * don't end up with #2 appended to the name    */
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|merge_layer
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_item_set_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|merge_layer
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  End the merge undo group  */
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|merge_layer
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|merge_layer
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|merge_layer
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|merge_layer
return|;
block|}
end_function

end_unit

