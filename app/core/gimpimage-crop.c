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
file|"base/pixel-region.h"
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
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-crop.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-guides.h"
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
file|"gimp-intl.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29b371db0103
block|{
DECL|enumerator|AUTO_CROP_NOTHING
name|AUTO_CROP_NOTHING
init|=
literal|0
block|,
DECL|enumerator|AUTO_CROP_ALPHA
name|AUTO_CROP_ALPHA
init|=
literal|1
block|,
DECL|enumerator|AUTO_CROP_COLOR
name|AUTO_CROP_COLOR
init|=
literal|2
DECL|typedef|AutoCropType
block|}
name|AutoCropType
typedef|;
end_typedef

begin_typedef
DECL|typedef|GetColorFunc
typedef|typedef
name|guchar
modifier|*
function_decl|(
modifier|*
name|GetColorFunc
function_decl|)
parameter_list|(
name|GObject
modifier|*
name|crop_object
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ColorsEqualFunc
typedef|typedef
name|AutoCropType
function_decl|(
modifier|*
name|ColorsEqualFunc
function_decl|)
parameter_list|(
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_image_crop_adjust_guides
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|AutoCropType
name|gimp_image_crop_guess_bgcolor
parameter_list|(
name|GObject
modifier|*
name|get_color_obj
parameter_list|,
name|GetColorFunc
name|get_color_func
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|guchar
modifier|*
name|color
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_image_crop_colors_equal
parameter_list|(
name|guchar
modifier|*
name|col1
parameter_list|,
name|guchar
modifier|*
name|col2
parameter_list|,
name|gint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_image_crop_colors_alpha
parameter_list|(
name|guchar
modifier|*
name|col1
parameter_list|,
name|guchar
modifier|*
name|col2
parameter_list|,
name|gint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_image_crop (GimpImage * gimage,gint x1,gint y1,gint x2,gint y2,gboolean active_layer_only,gboolean crop_layers)
name|gimp_image_crop
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|gboolean
name|active_layer_only
parameter_list|,
name|gboolean
name|crop_layers
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
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
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|lx1
decl_stmt|,
name|ly1
decl_stmt|,
name|lx2
decl_stmt|,
name|ly2
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|gimage
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
comment|/*  Make sure new width and height are non-zero  */
if|if
condition|(
name|width
operator|&&
name|height
condition|)
block|{
name|gimp_set_busy
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|active_layer_only
condition|)
block|{
name|gint
name|doff_x
decl_stmt|,
name|doff_y
decl_stmt|;
name|layer
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|&
name|doff_x
argument_list|,
operator|&
name|doff_y
argument_list|)
expr_stmt|;
name|off_x
operator|=
operator|(
name|doff_x
operator|-
name|x1
operator|)
expr_stmt|;
name|off_y
operator|=
operator|(
name|doff_y
operator|-
name|y1
operator|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_LAYER_RESIZE
argument_list|,
name|_
argument_list|(
literal|"Resize Layer"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
name|floating_sel_relax
argument_list|(
name|layer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_item_resize
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
name|floating_sel_rigor
argument_list|(
name|layer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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
name|GIMP_UNDO_GROUP_IMAGE_CROP
argument_list|,
name|_
argument_list|(
literal|"Crop Image"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  relax the floating layer  */
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
name|gimage
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|gimage
operator|->
name|height
operator|=
name|height
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
name|gimp_item_resize
argument_list|(
name|item
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|-
name|x1
argument_list|,
operator|-
name|y1
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
name|gimp_item_resize
argument_list|(
name|item
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|-
name|x1
argument_list|,
operator|-
name|y1
argument_list|)
expr_stmt|;
block|}
comment|/*  Don't forget the selection mask!  */
name|gimp_item_resize
argument_list|(
name|GIMP_ITEM
argument_list|(
name|gimage
operator|->
name|selection_mask
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|-
name|x1
argument_list|,
operator|-
name|y1
argument_list|)
expr_stmt|;
name|gimp_image_mask_invalidate
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/*  crop all layers  */
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
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|GList
modifier|*
name|next
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
name|next
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|gimp_item_translate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|-
name|x1
argument_list|,
operator|-
name|y1
argument_list|,
name|TRUE
argument_list|)
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
if|if
condition|(
name|crop_layers
condition|)
block|{
name|lx1
operator|=
name|CLAMP
argument_list|(
name|off_x
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|ly1
operator|=
name|CLAMP
argument_list|(
name|off_y
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|lx2
operator|=
name|CLAMP
argument_list|(
operator|(
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|+
name|off_x
operator|)
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|ly2
operator|=
name|CLAMP
argument_list|(
operator|(
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|+
name|off_y
operator|)
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|width
operator|=
name|lx2
operator|-
name|lx1
expr_stmt|;
name|height
operator|=
name|ly2
operator|-
name|ly1
expr_stmt|;
if|if
condition|(
name|width
operator|&&
name|height
condition|)
name|gimp_item_resize
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|-
operator|(
name|lx1
operator|-
name|off_x
operator|)
argument_list|,
operator|-
operator|(
name|ly1
operator|-
name|off_y
operator|)
argument_list|)
expr_stmt|;
else|else
name|gimp_image_remove_layer
argument_list|(
name|gimage
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
name|list
operator|=
name|next
expr_stmt|;
block|}
comment|/*  Make sure the projection matches the gimage size  */
name|gimp_image_projection_allocate
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/*  rigor the floating layer  */
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
comment|/* Adjust any guides we might have laying about */
name|gimp_image_crop_adjust_guides
argument_list|(
name|gimage
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
name|gimp_image_update
argument_list|(
name|gimage
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
name|gimp_image_mask_changed
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
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_crop_auto_shrink (GimpImage * gimage,gint x1,gint y1,gint x2,gint y2,gboolean active_drawable_only,gint * shrunk_x1,gint * shrunk_y1,gint * shrunk_x2,gint * shrunk_y2)
name|gimp_image_crop_auto_shrink
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|gboolean
name|active_drawable_only
parameter_list|,
name|gint
modifier|*
name|shrunk_x1
parameter_list|,
name|gint
modifier|*
name|shrunk_y1
parameter_list|,
name|gint
modifier|*
name|shrunk_x2
parameter_list|,
name|gint
modifier|*
name|shrunk_y2
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|active_drawable
init|=
name|NULL
decl_stmt|;
name|GetColorFunc
name|get_color_func
decl_stmt|;
name|ColorsEqualFunc
name|colors_equal_func
decl_stmt|;
name|GObject
modifier|*
name|get_color_obj
decl_stmt|;
name|guchar
name|bgcolor
index|[
name|MAX_CHANNELS
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
name|gboolean
name|has_alpha
decl_stmt|;
name|PixelRegion
name|PR
decl_stmt|;
name|guchar
modifier|*
name|buffer
init|=
name|NULL
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|abort
decl_stmt|;
name|gboolean
name|retval
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimage
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
name|g_return_val_if_fail
argument_list|(
name|shrunk_x1
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|shrunk_y1
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|shrunk_x2
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|shrunk_y2
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_set_busy
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
comment|/* You should always keep in mind that crop->tx2 and crop->ty2 are the NOT the      coordinates of the bottomright corner of the area to be cropped. They point       at the pixel located one to the right and one to the bottom.      */
if|if
condition|(
name|active_drawable_only
condition|)
block|{
name|active_drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|active_drawable
condition|)
goto|goto
name|FINISH
goto|;
name|bytes
operator|=
name|gimp_drawable_bytes
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|active_drawable
argument_list|)
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|active_drawable
argument_list|)
argument_list|)
expr_stmt|;
name|get_color_obj
operator|=
name|G_OBJECT
argument_list|(
name|active_drawable
argument_list|)
expr_stmt|;
name|get_color_func
operator|=
operator|(
name|GetColorFunc
operator|)
name|gimp_drawable_get_color_at
expr_stmt|;
block|}
else|else
block|{
name|has_alpha
operator|=
name|TRUE
expr_stmt|;
name|bytes
operator|=
name|gimp_image_projection_bytes
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|get_color_obj
operator|=
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|get_color_func
operator|=
operator|(
name|GetColorFunc
operator|)
name|gimp_image_projection_get_color_at
expr_stmt|;
block|}
switch|switch
condition|(
name|gimp_image_crop_guess_bgcolor
argument_list|(
name|get_color_obj
argument_list|,
name|get_color_func
argument_list|,
name|bytes
argument_list|,
name|has_alpha
argument_list|,
name|bgcolor
argument_list|,
name|x1
argument_list|,
name|x2
operator|-
literal|1
argument_list|,
name|y1
argument_list|,
name|y2
operator|-
literal|1
argument_list|)
condition|)
block|{
case|case
name|AUTO_CROP_ALPHA
case|:
name|colors_equal_func
operator|=
operator|(
name|ColorsEqualFunc
operator|)
name|gimp_image_crop_colors_alpha
expr_stmt|;
break|break;
case|case
name|AUTO_CROP_COLOR
case|:
name|colors_equal_func
operator|=
operator|(
name|ColorsEqualFunc
operator|)
name|gimp_image_crop_colors_equal
expr_stmt|;
break|break;
default|default:
goto|goto
name|FINISH
goto|;
break|break;
block|}
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
if|if
condition|(
name|active_drawable_only
condition|)
name|pixel_region_init
argument_list|(
operator|&
name|PR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|active_drawable
argument_list|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
else|else
name|pixel_region_init
argument_list|(
operator|&
name|PR
argument_list|,
name|gimp_image_projection
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* The following could be optimized further by processing    * the smaller side first instead of defaulting to width    --Sven    */
name|buffer
operator|=
name|g_malloc
argument_list|(
operator|(
name|width
operator|>
name|height
condition|?
name|width
else|:
name|height
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
comment|/* Check how many of the top lines are uniform/transparent. */
name|abort
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
operator|&&
operator|!
name|abort
condition|;
name|y
operator|++
control|)
block|{
name|pixel_region_get_row
argument_list|(
operator|&
name|PR
argument_list|,
name|x1
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|buffer
argument_list|,
literal|1
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
operator|&&
operator|!
name|abort
condition|;
name|x
operator|++
control|)
name|abort
operator|=
operator|!
call|(
name|colors_equal_func
call|)
argument_list|(
name|bgcolor
argument_list|,
name|buffer
operator|+
name|x
operator|*
name|bytes
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|y
operator|==
name|y2
operator|&&
operator|!
name|abort
condition|)
goto|goto
name|FINISH
goto|;
name|y1
operator|=
name|y
operator|-
literal|1
expr_stmt|;
comment|/* Check how many of the bottom lines are uniform/transparent. */
name|abort
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|y
operator|=
name|y2
init|;
name|y
operator|>
name|y1
operator|&&
operator|!
name|abort
condition|;
name|y
operator|--
control|)
block|{
name|pixel_region_get_row
argument_list|(
operator|&
name|PR
argument_list|,
name|x1
argument_list|,
name|y
operator|-
literal|1
argument_list|,
name|width
argument_list|,
name|buffer
argument_list|,
literal|1
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
operator|&&
operator|!
name|abort
condition|;
name|x
operator|++
control|)
name|abort
operator|=
operator|!
call|(
name|colors_equal_func
call|)
argument_list|(
name|bgcolor
argument_list|,
name|buffer
operator|+
name|x
operator|*
name|bytes
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
name|y2
operator|=
name|y
operator|+
literal|1
expr_stmt|;
comment|/* compute a new height for the next operations */
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
comment|/* Check how many of the left lines are uniform/transparent. */
name|abort
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|x
operator|=
name|x1
init|;
name|x
operator|<
name|x2
operator|&&
operator|!
name|abort
condition|;
name|x
operator|++
control|)
block|{
name|pixel_region_get_col
argument_list|(
operator|&
name|PR
argument_list|,
name|x
argument_list|,
name|y1
argument_list|,
name|height
argument_list|,
name|buffer
argument_list|,
literal|1
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
operator|&&
operator|!
name|abort
condition|;
name|y
operator|++
control|)
name|abort
operator|=
operator|!
call|(
name|colors_equal_func
call|)
argument_list|(
name|bgcolor
argument_list|,
name|buffer
operator|+
name|y
operator|*
name|bytes
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
name|x1
operator|=
name|x
operator|-
literal|1
expr_stmt|;
comment|/* Check how many of the right lines are uniform/transparent. */
name|abort
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|x
operator|=
name|x2
init|;
name|x
operator|>
name|x1
operator|&&
operator|!
name|abort
condition|;
name|x
operator|--
control|)
block|{
name|pixel_region_get_col
argument_list|(
operator|&
name|PR
argument_list|,
name|x
operator|-
literal|1
argument_list|,
name|y1
argument_list|,
name|height
argument_list|,
name|buffer
argument_list|,
literal|1
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
operator|&&
operator|!
name|abort
condition|;
name|y
operator|++
control|)
name|abort
operator|=
operator|!
call|(
name|colors_equal_func
call|)
argument_list|(
name|bgcolor
argument_list|,
name|buffer
operator|+
name|y
operator|*
name|bytes
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
name|x2
operator|=
name|x
operator|+
literal|1
expr_stmt|;
operator|*
name|shrunk_x1
operator|=
name|x1
expr_stmt|;
operator|*
name|shrunk_y1
operator|=
name|y1
expr_stmt|;
operator|*
name|shrunk_x2
operator|=
name|x2
expr_stmt|;
operator|*
name|shrunk_y2
operator|=
name|y2
expr_stmt|;
name|retval
operator|=
name|TRUE
expr_stmt|;
name|FINISH
label|:
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_image_crop_adjust_guides (GimpImage * gimage,gint x1,gint y1,gint x2,gint y2)
name|gimp_image_crop_adjust_guides
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
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
if|if
condition|(
operator|(
name|guide
operator|->
name|position
operator|<
name|y1
operator|)
operator|||
operator|(
name|guide
operator|->
name|position
operator|>
name|y2
operator|)
condition|)
name|remove_guide
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
if|if
condition|(
operator|(
name|guide
operator|->
name|position
operator|<
name|x1
operator|)
operator|||
operator|(
name|guide
operator|->
name|position
operator|>
name|x2
operator|)
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
block|{
name|gimp_image_remove_guide
argument_list|(
name|gimage
argument_list|,
name|guide
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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
name|guide
operator|->
name|position
operator|-
name|y1
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
name|guide
operator|->
name|position
operator|-
name|x1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|AutoCropType
DECL|function|gimp_image_crop_guess_bgcolor (GObject * get_color_obj,GetColorFunc get_color_func,gint bytes,gboolean has_alpha,guchar * color,gint x1,gint x2,gint y1,gint y2)
name|gimp_image_crop_guess_bgcolor
parameter_list|(
name|GObject
modifier|*
name|get_color_obj
parameter_list|,
name|GetColorFunc
name|get_color_func
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|guchar
modifier|*
name|color
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|y2
parameter_list|)
block|{
name|guchar
modifier|*
name|tl
init|=
name|NULL
decl_stmt|;
name|guchar
modifier|*
name|tr
init|=
name|NULL
decl_stmt|;
name|guchar
modifier|*
name|bl
init|=
name|NULL
decl_stmt|;
name|guchar
modifier|*
name|br
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|alpha
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bytes
condition|;
name|i
operator|++
control|)
name|color
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
comment|/* First check if there's transparency to crop. If not, guess the     * background-color to see if at least 2 corners are equal.    */
if|if
condition|(
operator|!
operator|(
name|tl
operator|=
call|(
modifier|*
name|get_color_func
call|)
argument_list|(
name|get_color_obj
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
operator|)
condition|)
goto|goto
name|ERROR
goto|;
if|if
condition|(
operator|!
operator|(
name|tr
operator|=
call|(
modifier|*
name|get_color_func
call|)
argument_list|(
name|get_color_obj
argument_list|,
name|x1
argument_list|,
name|y2
argument_list|)
operator|)
condition|)
goto|goto
name|ERROR
goto|;
if|if
condition|(
operator|!
operator|(
name|bl
operator|=
call|(
modifier|*
name|get_color_func
call|)
argument_list|(
name|get_color_obj
argument_list|,
name|x2
argument_list|,
name|y1
argument_list|)
operator|)
condition|)
goto|goto
name|ERROR
goto|;
if|if
condition|(
operator|!
operator|(
name|br
operator|=
call|(
modifier|*
name|get_color_func
call|)
argument_list|(
name|get_color_obj
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
operator|)
condition|)
goto|goto
name|ERROR
goto|;
if|if
condition|(
name|has_alpha
condition|)
block|{
name|alpha
operator|=
name|bytes
operator|-
literal|1
expr_stmt|;
if|if
condition|(
operator|(
name|tl
index|[
name|alpha
index|]
operator|==
literal|0
operator|&&
name|tr
index|[
name|alpha
index|]
operator|==
literal|0
operator|)
operator|||
operator|(
name|tl
index|[
name|alpha
index|]
operator|==
literal|0
operator|&&
name|bl
index|[
name|alpha
index|]
operator|==
literal|0
operator|)
operator|||
operator|(
name|tr
index|[
name|alpha
index|]
operator|==
literal|0
operator|&&
name|br
index|[
name|alpha
index|]
operator|==
literal|0
operator|)
operator|||
operator|(
name|bl
index|[
name|alpha
index|]
operator|==
literal|0
operator|&&
name|br
index|[
name|alpha
index|]
operator|==
literal|0
operator|)
condition|)
block|{
name|g_free
argument_list|(
name|tl
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tr
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bl
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|br
argument_list|)
expr_stmt|;
return|return
name|AUTO_CROP_ALPHA
return|;
block|}
block|}
if|if
condition|(
name|gimp_image_crop_colors_equal
argument_list|(
name|tl
argument_list|,
name|tr
argument_list|,
name|bytes
argument_list|)
operator|||
name|gimp_image_crop_colors_equal
argument_list|(
name|tl
argument_list|,
name|bl
argument_list|,
name|bytes
argument_list|)
condition|)
block|{
name|memcpy
argument_list|(
name|color
argument_list|,
name|tl
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimp_image_crop_colors_equal
argument_list|(
name|br
argument_list|,
name|bl
argument_list|,
name|bytes
argument_list|)
operator|||
name|gimp_image_crop_colors_equal
argument_list|(
name|br
argument_list|,
name|tr
argument_list|,
name|bytes
argument_list|)
condition|)
block|{
name|memcpy
argument_list|(
name|color
argument_list|,
name|br
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
else|else
block|{
goto|goto
name|ERROR
goto|;
block|}
name|g_free
argument_list|(
name|tl
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tr
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bl
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|br
argument_list|)
expr_stmt|;
return|return
name|AUTO_CROP_COLOR
return|;
name|ERROR
label|:
name|g_free
argument_list|(
name|tl
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tr
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bl
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|br
argument_list|)
expr_stmt|;
return|return
name|AUTO_CROP_NOTHING
return|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|gimp_image_crop_colors_equal (guchar * col1,guchar * col2,gint bytes)
name|gimp_image_crop_colors_equal
parameter_list|(
name|guchar
modifier|*
name|col1
parameter_list|,
name|guchar
modifier|*
name|col2
parameter_list|,
name|gint
name|bytes
parameter_list|)
block|{
name|gboolean
name|equal
init|=
name|TRUE
decl_stmt|;
name|gint
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bytes
condition|;
name|b
operator|++
control|)
block|{
if|if
condition|(
name|col1
index|[
name|b
index|]
operator|!=
name|col2
index|[
name|b
index|]
condition|)
block|{
name|equal
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
block|}
return|return
name|equal
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_image_crop_colors_alpha (guchar * dummy,guchar * col,gint bytes)
name|gimp_image_crop_colors_alpha
parameter_list|(
name|guchar
modifier|*
name|dummy
parameter_list|,
name|guchar
modifier|*
name|col
parameter_list|,
name|gint
name|bytes
parameter_list|)
block|{
if|if
condition|(
name|col
index|[
name|bytes
operator|-
literal|1
index|]
operator|==
literal|0
condition|)
return|return
name|TRUE
return|;
else|else
return|return
name|FALSE
return|;
block|}
end_function

end_unit

