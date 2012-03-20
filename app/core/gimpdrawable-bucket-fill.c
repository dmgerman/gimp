begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
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
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-nodes.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-apply-operation.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel-combine.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-bucket-fill.h"
end_include

begin_include
include|#
directive|include
file|"gimperror.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-contiguous-region.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_drawable_bucket_fill_internal
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpBucketFillMode
name|fill_mode
parameter_list|,
name|gint
name|paint_mode
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gboolean
name|fill_transparent
parameter_list|,
name|GimpSelectCriterion
name|fill_criterion
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_bucket_fill (GimpDrawable * drawable,GimpContext * context,GimpBucketFillMode fill_mode,gint paint_mode,gdouble opacity,gboolean fill_transparent,GimpSelectCriterion fill_criterion,gdouble threshold,gboolean sample_merged,gdouble x,gdouble y,GError ** error)
name|gimp_drawable_bucket_fill
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpBucketFillMode
name|fill_mode
parameter_list|,
name|gint
name|paint_mode
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gboolean
name|fill_transparent
parameter_list|,
name|GimpSelectCriterion
name|fill_criterion
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|GimpPattern
modifier|*
name|pattern
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|FALSE
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
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|fill_mode
operator|==
name|GIMP_FG_BUCKET_FILL
condition|)
block|{
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|fill_mode
operator|==
name|GIMP_BG_BUCKET_FILL
condition|)
block|{
name|gimp_context_get_background
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|fill_mode
operator|==
name|GIMP_PATTERN_BUCKET_FILL
condition|)
block|{
name|pattern
operator|=
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pattern
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"No patterns available for this operation."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"%s: invalid fill_mode passed"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_drawable_bucket_fill_internal
argument_list|(
name|drawable
argument_list|,
name|fill_mode
argument_list|,
name|paint_mode
argument_list|,
name|opacity
argument_list|,
name|fill_transparent
argument_list|,
name|fill_criterion
argument_list|,
name|threshold
argument_list|,
name|sample_merged
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|color
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_bucket_fill_internal (GimpDrawable * drawable,GimpBucketFillMode fill_mode,gint paint_mode,gdouble opacity,gboolean fill_transparent,GimpSelectCriterion fill_criterion,gdouble threshold,gboolean sample_merged,gdouble x,gdouble y,const GimpRGB * color,GimpPattern * pattern)
name|gimp_drawable_bucket_fill_internal
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpBucketFillMode
name|fill_mode
parameter_list|,
name|gint
name|paint_mode
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gboolean
name|fill_transparent
parameter_list|,
name|GimpSelectCriterion
name|fill_criterion
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|mask_buffer
decl_stmt|;
name|GeglNode
modifier|*
name|apply_opacity
decl_stmt|;
name|PixelRegion
name|bufPR
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
name|mask_offset_x
init|=
literal|0
decl_stmt|;
name|gint
name|mask_offset_y
init|=
literal|0
decl_stmt|;
name|gboolean
name|selection
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|fill_mode
operator|!=
name|GIMP_PATTERN_BUCKET_FILL
operator|||
name|GIMP_IS_PATTERN
argument_list|(
name|pattern
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|fill_mode
operator|==
name|GIMP_PATTERN_BUCKET_FILL
operator|||
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|selection
operator|=
name|gimp_item_mask_bounds
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|x1
operator|==
name|x2
operator|)
operator|||
operator|(
name|y1
operator|==
name|y2
operator|)
condition|)
return|return;
name|gimp_set_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
comment|/*  Do a seed bucket fill...To do this, calculate a new    *  contiguous region. If there is a selection, calculate the    *  intersection of this region with the existing selection.    */
name|mask
operator|=
name|gimp_image_contiguous_region_by_seed
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|,
name|sample_merged
argument_list|,
name|TRUE
argument_list|,
operator|(
name|gint
operator|)
name|threshold
argument_list|,
name|fill_transparent
argument_list|,
name|fill_criterion
argument_list|,
operator|(
name|gint
operator|)
name|x
argument_list|,
operator|(
name|gint
operator|)
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|selection
condition|)
block|{
name|gint
name|off_x
init|=
literal|0
decl_stmt|;
name|gint
name|off_y
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|sample_merged
condition|)
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|gimp_channel_combine_mask
argument_list|(
name|mask
argument_list|,
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_CHANNEL_OP_INTERSECT
argument_list|,
operator|-
name|off_x
argument_list|,
operator|-
name|off_y
argument_list|)
expr_stmt|;
block|}
name|mask_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_channel_bounds
argument_list|(
name|mask
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
comment|/*  make sure we handle the mask correctly if it was sample-merged  */
if|if
condition|(
name|sample_merged
condition|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
comment|/*  Limit the channel bounds to the drawable's extents  */
name|gimp_item_get_offset
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
name|x1
operator|=
name|CLAMP
argument_list|(
name|x1
argument_list|,
name|off_x
argument_list|,
operator|(
name|off_x
operator|+
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|)
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|y1
argument_list|,
name|off_y
argument_list|,
operator|(
name|off_y
operator|+
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|)
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|x2
argument_list|,
name|off_x
argument_list|,
operator|(
name|off_x
operator|+
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|y2
argument_list|,
name|off_y
argument_list|,
operator|(
name|off_y
operator|+
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|)
argument_list|)
expr_stmt|;
name|mask_offset_x
operator|=
name|x1
expr_stmt|;
name|mask_offset_y
operator|=
name|y1
expr_stmt|;
comment|/*  translate mask bounds to drawable coords  */
name|x1
operator|-=
name|off_x
expr_stmt|;
name|y1
operator|-=
name|off_y
expr_stmt|;
name|x2
operator|-=
name|off_x
expr_stmt|;
name|y2
operator|-=
name|off_y
expr_stmt|;
block|}
else|else
block|{
name|mask_offset_x
operator|=
name|x1
expr_stmt|;
name|mask_offset_y
operator|=
name|y1
expr_stmt|;
block|}
name|tiles
operator|=
name|tile_manager_new
argument_list|(
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
name|gimp_drawable_bytes_with_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_tile_manager_create_buffer
argument_list|(
name|tiles
argument_list|,
name|gimp_drawable_get_format_with_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|fill_mode
condition|)
block|{
case|case
name|GIMP_FG_BUCKET_FILL
case|:
case|case
name|GIMP_BG_BUCKET_FILL
case|:
block|{
name|GeglColor
modifier|*
name|gegl_color
init|=
name|gimp_gegl_color_new
argument_list|(
name|color
argument_list|)
decl_stmt|;
name|gegl_buffer_set_color
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|gegl_color
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gegl_color
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PATTERN_BUCKET_FILL
case|:
block|{
name|GeglBuffer
modifier|*
name|pattern_buffer
init|=
name|gimp_pattern_create_buffer
argument_list|(
name|pattern
argument_list|)
decl_stmt|;
name|gegl_buffer_set_pattern
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|pattern_buffer
argument_list|,
operator|-
name|x1
argument_list|,
operator|-
name|y1
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pattern_buffer
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
name|apply_opacity
operator|=
name|gimp_gegl_create_apply_opacity_node
argument_list|(
name|mask_buffer
argument_list|,
literal|1.0
argument_list|,
name|mask_offset_x
argument_list|,
name|mask_offset_y
argument_list|)
expr_stmt|;
name|gimp_apply_operation
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|apply_opacity
argument_list|,
literal|1.0
argument_list|,
name|buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|apply_opacity
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|mask
argument_list|)
expr_stmt|;
comment|/*  Apply it to the image  */
name|pixel_region_init
argument_list|(
operator|&
name|bufPR
argument_list|,
name|tiles
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
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_region
argument_list|(
name|drawable
argument_list|,
operator|&
name|bufPR
argument_list|,
name|TRUE
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Bucket Fill"
argument_list|)
argument_list|,
name|opacity
argument_list|,
name|paint_mode
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|tile_manager_unref
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

