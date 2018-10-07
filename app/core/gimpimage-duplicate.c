begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gegl/gimp-gegl-loops.h"
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
file|"gimpchannel.h"
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
file|"gimpimage-color-profile.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-colormap.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-duplicate.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-grid.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-guides.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-metadata.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-sample-points.h"
end_include

begin_include
include|#
directive|include
file|"gimpitemstack.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer-floating-selection.h"
end_include

begin_include
include|#
directive|include
file|"gimpparasitelist.h"
end_include

begin_include
include|#
directive|include
file|"gimpsamplepoint.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_image_duplicate_resolution
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_duplicate_save_source_file
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_duplicate_colormap
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpItem
modifier|*
name|gimp_image_duplicate_item
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpLayer
modifier|*
name|gimp_image_duplicate_layers
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpChannel
modifier|*
name|gimp_image_duplicate_channels
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpVectors
modifier|*
name|gimp_image_duplicate_vectors
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_duplicate_floating_sel
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_duplicate_mask
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_duplicate_components
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_duplicate_guides
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_duplicate_sample_points
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_duplicate_grid
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_duplicate_metadata
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_duplicate_quick_mask
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_duplicate_parasites
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_duplicate_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_image_duplicate (GimpImage * image)
name|gimp_image_duplicate
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpImage
modifier|*
name|new_image
decl_stmt|;
name|GimpLayer
modifier|*
name|active_layer
decl_stmt|;
name|GimpChannel
modifier|*
name|active_channel
decl_stmt|;
name|GimpVectors
modifier|*
name|active_vectors
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
name|gimp_set_busy_until_idle
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
comment|/*  Create a new image  */
name|new_image
operator|=
name|gimp_create_image
argument_list|(
name|image
operator|->
name|gimp
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
argument_list|,
name|gimp_image_get_base_type
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_precision
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Store the source uri to be used by the save dialog  */
name|gimp_image_duplicate_save_source_file
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Copy resolution information  */
name|gimp_image_duplicate_resolution
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Copy parasites first so we have a color profile  */
name|gimp_image_duplicate_parasites
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
name|gimp_image_duplicate_color_profile
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Copy the colormap if necessary  */
name|gimp_image_duplicate_colormap
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Copy the layers  */
name|active_layer
operator|=
name|gimp_image_duplicate_layers
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Copy the channels  */
name|active_channel
operator|=
name|gimp_image_duplicate_channels
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Copy any vectors  */
name|active_vectors
operator|=
name|gimp_image_duplicate_vectors
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Copy floating layer  */
name|gimp_image_duplicate_floating_sel
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Copy the selection mask  */
name|gimp_image_duplicate_mask
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Set active layer, active channel, active vectors  */
if|if
condition|(
name|active_layer
condition|)
name|gimp_image_set_active_layer
argument_list|(
name|new_image
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
name|new_image
argument_list|,
name|active_channel
argument_list|)
expr_stmt|;
if|if
condition|(
name|active_vectors
condition|)
name|gimp_image_set_active_vectors
argument_list|(
name|new_image
argument_list|,
name|active_vectors
argument_list|)
expr_stmt|;
comment|/*  Copy state of all color components  */
name|gimp_image_duplicate_components
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Copy any guides  */
name|gimp_image_duplicate_guides
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Copy any sample points  */
name|gimp_image_duplicate_sample_points
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Copy the grid  */
name|gimp_image_duplicate_grid
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Copy the metadata  */
name|gimp_image_duplicate_metadata
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/*  Copy the quick mask info  */
name|gimp_image_duplicate_quick_mask
argument_list|(
name|image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
return|return
name|new_image
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_duplicate_resolution (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_resolution
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|gimp_image_set_resolution
argument_list|(
name|new_image
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|new_image
argument_list|,
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_duplicate_save_source_file (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_save_source_file
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|GFile
modifier|*
name|file
init|=
name|gimp_image_get_file
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|file
condition|)
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|new_image
argument_list|)
argument_list|,
literal|"gimp-image-source-file"
argument_list|,
name|g_object_ref
argument_list|(
name|file
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_duplicate_colormap (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_colormap
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
if|if
condition|(
name|gimp_image_get_base_type
argument_list|(
name|new_image
argument_list|)
operator|==
name|GIMP_INDEXED
condition|)
name|gimp_image_set_colormap
argument_list|(
name|new_image
argument_list|,
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_colormap_size
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpItem
modifier|*
DECL|function|gimp_image_duplicate_item (GimpItem * item,GimpImage * new_image)
name|gimp_image_duplicate_item
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|GimpItem
modifier|*
name|new_item
decl_stmt|;
name|new_item
operator|=
name|gimp_item_convert
argument_list|(
name|item
argument_list|,
name|new_image
argument_list|,
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Make sure the copied item doesn't say: "<old item> copy"  */
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|new_item
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|new_item
return|;
block|}
end_function

begin_function
specifier|static
name|GimpLayer
modifier|*
DECL|function|gimp_image_duplicate_layers (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_layers
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|active_layer
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|count
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_image_get_layer_iter
argument_list|(
name|image
argument_list|)
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
name|GimpLayer
modifier|*
name|new_layer
decl_stmt|;
if|if
condition|(
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
continue|continue;
name|new_layer
operator|=
name|GIMP_LAYER
argument_list|(
name|gimp_image_duplicate_item
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
name|new_image
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Make sure that if the layer has a layer mask,        *  its name isn't screwed up        */
if|if
condition|(
name|new_layer
operator|->
name|mask
condition|)
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
name|layer
operator|->
name|mask
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_get_active_layer
argument_list|(
name|image
argument_list|)
operator|==
name|layer
condition|)
name|active_layer
operator|=
name|new_layer
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|new_image
argument_list|,
name|new_layer
argument_list|,
name|NULL
argument_list|,
name|count
operator|++
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
return|return
name|active_layer
return|;
block|}
end_function

begin_function
specifier|static
name|GimpChannel
modifier|*
DECL|function|gimp_image_duplicate_channels (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_channels
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|active_channel
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|count
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_image_get_channel_iter
argument_list|(
name|image
argument_list|)
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
control|)
block|{
name|GimpChannel
modifier|*
name|channel
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GimpChannel
modifier|*
name|new_channel
decl_stmt|;
name|new_channel
operator|=
name|GIMP_CHANNEL
argument_list|(
name|gimp_image_duplicate_item
argument_list|(
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|,
name|new_image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_get_active_channel
argument_list|(
name|image
argument_list|)
operator|==
name|channel
condition|)
name|active_channel
operator|=
name|new_channel
expr_stmt|;
name|gimp_image_add_channel
argument_list|(
name|new_image
argument_list|,
name|new_channel
argument_list|,
name|NULL
argument_list|,
name|count
operator|++
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
return|return
name|active_channel
return|;
block|}
end_function

begin_function
specifier|static
name|GimpVectors
modifier|*
DECL|function|gimp_image_duplicate_vectors (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_vectors
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|GimpVectors
modifier|*
name|active_vectors
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|count
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_image_get_vectors_iter
argument_list|(
name|image
argument_list|)
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
control|)
block|{
name|GimpVectors
modifier|*
name|vectors
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GimpVectors
modifier|*
name|new_vectors
decl_stmt|;
name|new_vectors
operator|=
name|GIMP_VECTORS
argument_list|(
name|gimp_image_duplicate_item
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|new_image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_get_active_vectors
argument_list|(
name|image
argument_list|)
operator|==
name|vectors
condition|)
name|active_vectors
operator|=
name|new_vectors
expr_stmt|;
name|gimp_image_add_vectors
argument_list|(
name|new_image
argument_list|,
name|new_vectors
argument_list|,
name|NULL
argument_list|,
name|count
operator|++
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
return|return
name|active_vectors
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_duplicate_floating_sel (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_floating_sel
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|floating_sel
decl_stmt|;
name|GimpDrawable
modifier|*
name|floating_sel_drawable
decl_stmt|;
name|GList
modifier|*
name|floating_sel_path
decl_stmt|;
name|GimpItemStack
modifier|*
name|new_item_stack
decl_stmt|;
name|GimpLayer
modifier|*
name|new_floating_sel
decl_stmt|;
name|GimpDrawable
modifier|*
name|new_floating_sel_drawable
decl_stmt|;
name|floating_sel
operator|=
name|gimp_image_get_floating_selection
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|floating_sel
condition|)
return|return;
name|floating_sel_drawable
operator|=
name|gimp_layer_get_floating_sel_drawable
argument_list|(
name|floating_sel
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|floating_sel_drawable
argument_list|)
condition|)
block|{
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|layer
operator|=
name|gimp_layer_mask_get_layer
argument_list|(
name|GIMP_LAYER_MASK
argument_list|(
name|floating_sel_drawable
argument_list|)
argument_list|)
expr_stmt|;
name|floating_sel_path
operator|=
name|gimp_item_get_path
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|new_item_stack
operator|=
name|GIMP_ITEM_STACK
argument_list|(
name|gimp_image_get_layers
argument_list|(
name|new_image
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|floating_sel_path
operator|=
name|gimp_item_get_path
argument_list|(
name|GIMP_ITEM
argument_list|(
name|floating_sel_drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|floating_sel_drawable
argument_list|)
condition|)
name|new_item_stack
operator|=
name|GIMP_ITEM_STACK
argument_list|(
name|gimp_image_get_layers
argument_list|(
name|new_image
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|new_item_stack
operator|=
name|GIMP_ITEM_STACK
argument_list|(
name|gimp_image_get_channels
argument_list|(
name|new_image
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*  adjust path[0] for the floating layer missing in new_image  */
name|floating_sel_path
operator|->
name|data
operator|=
name|GUINT_TO_POINTER
argument_list|(
name|GPOINTER_TO_UINT
argument_list|(
name|floating_sel_path
operator|->
name|data
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|floating_sel_drawable
argument_list|)
condition|)
block|{
name|new_floating_sel
operator|=
name|GIMP_LAYER
argument_list|(
name|gimp_image_duplicate_item
argument_list|(
name|GIMP_ITEM
argument_list|(
name|floating_sel
argument_list|)
argument_list|,
name|new_image
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  can't use gimp_item_convert() for floating selections of channels        *  or layer masks because they maybe don't have a normal layer's type        */
name|new_floating_sel
operator|=
name|GIMP_LAYER
argument_list|(
name|gimp_item_duplicate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|floating_sel
argument_list|)
argument_list|,
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|floating_sel
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_set_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|new_floating_sel
argument_list|)
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|new_floating_sel
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|floating_sel
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*  Make sure the copied layer doesn't say: "<old layer> copy"  */
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|new_floating_sel
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|floating_sel
argument_list|)
argument_list|)
expr_stmt|;
name|new_floating_sel_drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|gimp_item_stack_get_item_by_path
argument_list|(
name|new_item_stack
argument_list|,
name|floating_sel_path
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|floating_sel_drawable
argument_list|)
condition|)
name|new_floating_sel_drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|gimp_layer_get_mask
argument_list|(
name|GIMP_LAYER
argument_list|(
name|new_floating_sel_drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|floating_sel_attach
argument_list|(
name|new_floating_sel
argument_list|,
name|new_floating_sel_drawable
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|floating_sel_path
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_duplicate_mask (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_mask
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|mask
decl_stmt|;
name|GimpDrawable
modifier|*
name|new_mask
decl_stmt|;
name|mask
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|new_mask
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|new_image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_gegl_buffer_copy
argument_list|(
name|gimp_drawable_get_buffer
argument_list|(
name|mask
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|gimp_drawable_get_buffer
argument_list|(
name|new_mask
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_CHANNEL
argument_list|(
name|new_mask
argument_list|)
operator|->
name|bounds_known
operator|=
name|FALSE
expr_stmt|;
name|GIMP_CHANNEL
argument_list|(
name|new_mask
argument_list|)
operator|->
name|boundary_known
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_duplicate_components (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_components
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
init|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpImagePrivate
modifier|*
name|new_private
init|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|new_image
argument_list|)
decl_stmt|;
name|gint
name|count
decl_stmt|;
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
name|new_private
operator|->
name|visible
index|[
name|count
index|]
operator|=
name|private
operator|->
name|visible
index|[
name|count
index|]
expr_stmt|;
name|new_private
operator|->
name|active
index|[
name|count
index|]
operator|=
name|private
operator|->
name|active
index|[
name|count
index|]
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_duplicate_guides (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_guides
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
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
name|gimp_image_add_hguide
argument_list|(
name|new_image
argument_list|,
name|position
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|gimp_image_add_vguide
argument_list|(
name|new_image
argument_list|,
name|position
argument_list|,
name|FALSE
argument_list|)
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_duplicate_sample_points (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_sample_points
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
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
name|gimp_image_add_sample_point_at_pos
argument_list|(
name|new_image
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_duplicate_grid (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_grid
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
if|if
condition|(
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
condition|)
name|gimp_image_set_grid
argument_list|(
name|new_image
argument_list|,
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_duplicate_metadata (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_metadata
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|GimpMetadata
modifier|*
name|metadata
init|=
name|gimp_image_get_metadata
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|metadata
condition|)
block|{
name|metadata
operator|=
name|gimp_metadata_duplicate
argument_list|(
name|metadata
argument_list|)
expr_stmt|;
name|gimp_image_set_metadata
argument_list|(
name|new_image
argument_list|,
name|metadata
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|metadata
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_duplicate_quick_mask (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_quick_mask
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
init|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpImagePrivate
modifier|*
name|new_private
init|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|new_image
argument_list|)
decl_stmt|;
name|new_private
operator|->
name|quick_mask_state
operator|=
name|private
operator|->
name|quick_mask_state
expr_stmt|;
name|new_private
operator|->
name|quick_mask_inverted
operator|=
name|private
operator|->
name|quick_mask_inverted
expr_stmt|;
name|new_private
operator|->
name|quick_mask_color
operator|=
name|private
operator|->
name|quick_mask_color
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_duplicate_parasites (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_parasites
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
init|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpImagePrivate
modifier|*
name|new_private
init|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|new_image
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|parasites
condition|)
block|{
name|g_object_unref
argument_list|(
name|new_private
operator|->
name|parasites
argument_list|)
expr_stmt|;
name|new_private
operator|->
name|parasites
operator|=
name|gimp_parasite_list_copy
argument_list|(
name|private
operator|->
name|parasites
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_duplicate_color_profile (GimpImage * image,GimpImage * new_image)
name|gimp_image_duplicate_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|GimpColorProfile
modifier|*
name|profile
init|=
name|gimp_image_get_color_profile
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpColorProfile
modifier|*
name|hidden
init|=
name|_gimp_image_get_hidden_profile
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|gimp_image_set_color_profile
argument_list|(
name|new_image
argument_list|,
name|profile
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|_gimp_image_set_hidden_profile
argument_list|(
name|new_image
argument_list|,
name|hidden
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

