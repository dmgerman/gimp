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
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
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
file|"gegl/gimp-gegl-apply-operation.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-mask.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-mask-combine.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"operations/layer-modes/gimp-layer-modes.h"
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
file|"gimpdrawable-bucket-fill.h"
end_include

begin_include
include|#
directive|include
file|"gimpfilloptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"gimppickable-contiguous-region.h"
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
DECL|function|gimp_drawable_bucket_fill (GimpDrawable * drawable,GimpFillOptions * options,gboolean fill_transparent,GimpSelectCriterion fill_criterion,gdouble threshold,gboolean sample_merged,gboolean diagonal_neighbors,gdouble seed_x,gdouble seed_y)
name|gimp_drawable_bucket_fill
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpFillOptions
modifier|*
name|options
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
name|gboolean
name|diagonal_neighbors
parameter_list|,
name|gdouble
name|seed_x
parameter_list|,
name|gdouble
name|seed_y
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|gdouble
name|mask_x
decl_stmt|;
name|gdouble
name|mask_y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
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
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
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
name|gimp_set_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_bucket_fill_buffer
argument_list|(
name|drawable
argument_list|,
name|options
argument_list|,
name|fill_transparent
argument_list|,
name|fill_criterion
argument_list|,
name|threshold
argument_list|,
name|sample_merged
argument_list|,
name|diagonal_neighbors
argument_list|,
name|seed_x
argument_list|,
name|seed_y
argument_list|,
name|NULL
argument_list|,
operator|&
name|mask_x
argument_list|,
operator|&
name|mask_y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
condition|)
block|{
comment|/*  Apply it to the image  */
name|gimp_drawable_apply_buffer
argument_list|(
name|drawable
argument_list|,
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
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
name|gimp_context_get_opacity
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|,
name|GIMP_LAYER_COLOR_SPACE_AUTO
argument_list|,
name|GIMP_LAYER_COLOR_SPACE_AUTO
argument_list|,
name|gimp_layer_mode_get_paint_composite_mode
argument_list|(
name|gimp_context_get_paint_mode
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|,
operator|(
name|gint
operator|)
name|mask_x
argument_list|,
name|mask_y
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
name|mask_x
argument_list|,
name|mask_y
argument_list|,
name|width
argument_list|,
name|height
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
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_bucket_fill_buffer:  * @drawable: the #GimpDrawable to edit.  * @options:  * @fill_transparent:  * @fill_criterion:  * @threshold:  * @sample_merged:  * @diagonal_neighbors:  * @seed_x: X coordinate to start the fill.  * @seed_y: Y coordinate to start the fill.  * @mask_buffer: mask of the fill in-progress when in an interactive  *               filling process. Set to NULL if you need a one-time  *               fill.  * @mask_x: returned x bound of @mask_buffer.  * @mask_y: returned x bound of @mask_buffer.  * @mask_width: returned width bound of @mask_buffer.  * @mask_height: returned height bound of @mask_buffer.  *  * Creates the fill buffer for a bucket fill operation on @drawable,  * without actually applying it (if you want to apply it directly as a  * one-time operation, use gimp_drawable_bucket_fill() instead). If  * @mask_buffer is not NULL, the intermediate fill mask will also be  * returned. This fill mask can later be reused in successive calls to  * gimp_drawable_get_bucket_fill_buffer() for interactive filling.  *  * Returns: a fill buffer which can be directly applied to @drawable, or  *          used in a drawable filter as preview.  */
end_comment

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_drawable_get_bucket_fill_buffer (GimpDrawable * drawable,GimpFillOptions * options,gboolean fill_transparent,GimpSelectCriterion fill_criterion,gdouble threshold,gboolean sample_merged,gboolean diagonal_neighbors,gdouble seed_x,gdouble seed_y,GeglBuffer ** mask_buffer,gdouble * mask_x,gdouble * mask_y,gint * mask_width,gint * mask_height)
name|gimp_drawable_get_bucket_fill_buffer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpFillOptions
modifier|*
name|options
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
name|gboolean
name|diagonal_neighbors
parameter_list|,
name|gdouble
name|seed_x
parameter_list|,
name|gdouble
name|seed_y
parameter_list|,
name|GeglBuffer
modifier|*
modifier|*
name|mask_buffer
parameter_list|,
name|gdouble
modifier|*
name|mask_x
parameter_list|,
name|gdouble
modifier|*
name|mask_y
parameter_list|,
name|gint
modifier|*
name|mask_width
parameter_list|,
name|gint
modifier|*
name|mask_height
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpPickable
modifier|*
name|pickable
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|new_mask
decl_stmt|;
name|gboolean
name|antialias
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
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
name|gint
name|sel_x
decl_stmt|,
name|sel_y
decl_stmt|,
name|sel_width
decl_stmt|,
name|sel_height
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
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
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
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
if|if
condition|(
operator|!
name|gimp_item_mask_intersect
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|sel_x
argument_list|,
operator|&
name|sel_y
argument_list|,
operator|&
name|sel_width
argument_list|,
operator|&
name|sel_height
argument_list|)
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|mask_buffer
operator|&&
operator|*
name|mask_buffer
operator|&&
name|threshold
operator|==
literal|0.0
condition|)
block|{
name|gfloat
name|pixel
decl_stmt|;
name|gegl_buffer_sample
argument_list|(
operator|*
name|mask_buffer
argument_list|,
name|seed_x
argument_list|,
name|seed_y
argument_list|,
name|NULL
argument_list|,
operator|&
name|pixel
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|,
name|GEGL_SAMPLER_NEAREST
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixel
operator|!=
literal|0.0
condition|)
comment|/* Already selected. This seed won't change the selection. */
return|return
name|NULL
return|;
block|}
name|gimp_set_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|sample_merged
condition|)
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|image
argument_list|)
expr_stmt|;
else|else
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|antialias
operator|=
name|gimp_fill_options_get_antialias
argument_list|(
name|options
argument_list|)
expr_stmt|;
comment|/*  Do a seed bucket fill...To do this, calculate a new    *  contiguous region.    */
name|new_mask
operator|=
name|gimp_pickable_contiguous_region_by_seed
argument_list|(
name|pickable
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|fill_transparent
argument_list|,
name|fill_criterion
argument_list|,
name|diagonal_neighbors
argument_list|,
operator|(
name|gint
operator|)
name|seed_x
argument_list|,
operator|(
name|gint
operator|)
name|seed_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask_buffer
operator|&&
operator|*
name|mask_buffer
condition|)
block|{
name|gimp_gegl_mask_combine_buffer
argument_list|(
name|new_mask
argument_list|,
operator|*
name|mask_buffer
argument_list|,
name|GIMP_CHANNEL_OP_ADD
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
operator|*
name|mask_buffer
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|mask_buffer
condition|)
operator|*
name|mask_buffer
operator|=
name|new_mask
expr_stmt|;
name|gimp_gegl_mask_bounds
argument_list|(
name|new_mask
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|width
operator|-=
name|x
expr_stmt|;
name|height
operator|-=
name|y
expr_stmt|;
comment|/*  If there is a selection, intersect the region bounds    *  with the selection bounds, to avoid processing areas    *  that are going to be masked out anyway.  The actual    *  intersection of the fill region with the mask data    *  happens when combining the fill buffer, in    *  gimp_drawable_apply_buffer().    */
if|if
condition|(
operator|!
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
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
if|if
condition|(
operator|!
name|gimp_rectangle_intersect
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|sel_x
operator|+
name|off_x
argument_list|,
name|sel_y
operator|+
name|off_y
argument_list|,
name|sel_width
argument_list|,
name|sel_height
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|mask_buffer
condition|)
name|g_object_unref
argument_list|(
name|new_mask
argument_list|)
expr_stmt|;
comment|/*  The fill region and the selection are disjoint; bail.  */
name|gimp_unset_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
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
name|gimp_rectangle_intersect
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|mask_offset_x
operator|=
name|x
expr_stmt|;
name|mask_offset_y
operator|=
name|y
expr_stmt|;
comment|/*  translate mask bounds to drawable coords  */
name|x
operator|-=
name|off_x
expr_stmt|;
name|y
operator|-=
name|off_y
expr_stmt|;
block|}
else|else
block|{
name|mask_offset_x
operator|=
name|x
expr_stmt|;
name|mask_offset_y
operator|=
name|y
expr_stmt|;
block|}
name|buffer
operator|=
name|gimp_fill_options_create_buffer
argument_list|(
name|options
argument_list|,
name|drawable
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
operator|-
name|x
argument_list|,
operator|-
name|y
argument_list|)
expr_stmt|;
name|gimp_gegl_apply_opacity
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|buffer
argument_list|,
name|new_mask
argument_list|,
operator|-
name|mask_offset_x
argument_list|,
operator|-
name|mask_offset_y
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask_x
condition|)
operator|*
name|mask_x
operator|=
name|x
expr_stmt|;
if|if
condition|(
name|mask_y
condition|)
operator|*
name|mask_y
operator|=
name|y
expr_stmt|;
if|if
condition|(
name|mask_width
condition|)
operator|*
name|mask_width
operator|=
name|width
expr_stmt|;
if|if
condition|(
name|mask_height
condition|)
operator|*
name|mask_height
operator|=
name|height
expr_stmt|;
if|if
condition|(
operator|!
name|mask_buffer
condition|)
name|g_object_unref
argument_list|(
name|new_mask
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
name|buffer
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_line_art_fill_buffer:  * @drawable: the #GimpDrawable to edit.  * @line_art: the #GimpLineArt computed as fill source.  * @options: the #GimpFillOptions.  * @sample_merged:  * @seed_x: X coordinate to start the fill.  * @seed_y: Y coordinate to start the fill.  * @mask_buffer: mask of the fill in-progress when in an interactive  *               filling process. Set to NULL if you need a one-time  *               fill.  * @mask_x: returned x bound of @mask_buffer.  * @mask_y: returned x bound of @mask_buffer.  * @mask_width: returned width bound of @mask_buffer.  * @mask_height: returned height bound of @mask_buffer.  *  * Creates the fill buffer for a bucket fill operation on @drawable  * based on @line_art and @options, without actually applying it.  * If @mask_buffer is not NULL, the intermediate fill mask will also be  * returned. This fill mask can later be reused in successive calls to  * gimp_drawable_get_bucket_fill_buffer() for interactive filling.  *  * Returns: a fill buffer which can be directly applied to @drawable, or  *          used in a drawable filter as preview.  */
end_comment

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_drawable_get_line_art_fill_buffer (GimpDrawable * drawable,GimpLineArt * line_art,GimpFillOptions * options,gboolean sample_merged,gdouble seed_x,gdouble seed_y,GeglBuffer ** mask_buffer,gdouble * mask_x,gdouble * mask_y,gint * mask_width,gint * mask_height)
name|gimp_drawable_get_line_art_fill_buffer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpLineArt
modifier|*
name|line_art
parameter_list|,
name|GimpFillOptions
modifier|*
name|options
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gdouble
name|seed_x
parameter_list|,
name|gdouble
name|seed_y
parameter_list|,
name|GeglBuffer
modifier|*
modifier|*
name|mask_buffer
parameter_list|,
name|gdouble
modifier|*
name|mask_x
parameter_list|,
name|gdouble
modifier|*
name|mask_y
parameter_list|,
name|gint
modifier|*
name|mask_width
parameter_list|,
name|gint
modifier|*
name|mask_height
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|new_mask
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
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
name|gint
name|sel_x
decl_stmt|,
name|sel_y
decl_stmt|,
name|sel_width
decl_stmt|,
name|sel_height
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
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
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
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
if|if
condition|(
operator|!
name|gimp_item_mask_intersect
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|sel_x
argument_list|,
operator|&
name|sel_y
argument_list|,
operator|&
name|sel_width
argument_list|,
operator|&
name|sel_height
argument_list|)
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|mask_buffer
operator|&&
operator|*
name|mask_buffer
condition|)
block|{
name|gfloat
name|pixel
decl_stmt|;
name|gegl_buffer_sample
argument_list|(
operator|*
name|mask_buffer
argument_list|,
name|seed_x
argument_list|,
name|seed_y
argument_list|,
name|NULL
argument_list|,
operator|&
name|pixel
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|,
name|GEGL_SAMPLER_NEAREST
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixel
operator|!=
literal|0.0
condition|)
comment|/* Already selected. This seed won't change the selection. */
return|return
name|NULL
return|;
block|}
name|gimp_set_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
comment|/*  Do a seed bucket fill...To do this, calculate a new    *  contiguous region.    */
name|new_mask
operator|=
name|gimp_pickable_contiguous_region_by_line_art
argument_list|(
name|NULL
argument_list|,
name|line_art
argument_list|,
operator|(
name|gint
operator|)
name|seed_x
argument_list|,
operator|(
name|gint
operator|)
name|seed_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask_buffer
operator|&&
operator|*
name|mask_buffer
condition|)
block|{
name|gimp_gegl_mask_combine_buffer
argument_list|(
name|new_mask
argument_list|,
operator|*
name|mask_buffer
argument_list|,
name|GIMP_CHANNEL_OP_ADD
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
operator|*
name|mask_buffer
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|mask_buffer
condition|)
operator|*
name|mask_buffer
operator|=
name|new_mask
expr_stmt|;
name|gimp_gegl_mask_bounds
argument_list|(
name|new_mask
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|width
operator|-=
name|x
expr_stmt|;
name|height
operator|-=
name|y
expr_stmt|;
comment|/*  If there is a selection, intersect the region bounds    *  with the selection bounds, to avoid processing areas    *  that are going to be masked out anyway.  The actual    *  intersection of the fill region with the mask data    *  happens when combining the fill buffer, in    *  gimp_drawable_apply_buffer().    */
if|if
condition|(
operator|!
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
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
if|if
condition|(
operator|!
name|gimp_rectangle_intersect
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|sel_x
operator|+
name|off_x
argument_list|,
name|sel_y
operator|+
name|off_y
argument_list|,
name|sel_width
argument_list|,
name|sel_height
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|mask_buffer
condition|)
name|g_object_unref
argument_list|(
name|new_mask
argument_list|)
expr_stmt|;
comment|/*  The fill region and the selection are disjoint; bail.  */
name|gimp_unset_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
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
name|gimp_rectangle_intersect
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|mask_offset_x
operator|=
name|x
expr_stmt|;
name|mask_offset_y
operator|=
name|y
expr_stmt|;
comment|/*  translate mask bounds to drawable coords  */
name|x
operator|-=
name|off_x
expr_stmt|;
name|y
operator|-=
name|off_y
expr_stmt|;
block|}
else|else
block|{
name|mask_offset_x
operator|=
name|x
expr_stmt|;
name|mask_offset_y
operator|=
name|y
expr_stmt|;
block|}
name|buffer
operator|=
name|gimp_fill_options_create_buffer
argument_list|(
name|options
argument_list|,
name|drawable
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
operator|-
name|x
argument_list|,
operator|-
name|y
argument_list|)
expr_stmt|;
name|gimp_gegl_apply_opacity
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|buffer
argument_list|,
name|new_mask
argument_list|,
operator|-
name|mask_offset_x
argument_list|,
operator|-
name|mask_offset_y
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_fill_options_get_antialias
argument_list|(
name|options
argument_list|)
condition|)
block|{
comment|/* Antialias for the line art algorithm is not applied during mask        * creation because it is not based on individual pixel colors.        * Instead we just want to apply it on the borders of the mask at        * the end (since the mask can evolve, we don't want to actually        * touch it, but only the intermediate results).        */
name|GeglNode
modifier|*
name|graph
decl_stmt|;
name|GeglNode
modifier|*
name|input
decl_stmt|;
name|GeglNode
modifier|*
name|op
decl_stmt|;
name|graph
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|input
operator|=
name|gegl_node_new_child
argument_list|(
name|graph
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-source"
argument_list|,
literal|"buffer"
argument_list|,
name|buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|op
operator|=
name|gegl_node_new_child
argument_list|(
name|graph
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:gaussian-blur"
argument_list|,
literal|"std-dev-x"
argument_list|,
literal|0.5
argument_list|,
literal|"std-dev-y"
argument_list|,
literal|0.5
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|input
argument_list|,
literal|"output"
argument_list|,
name|op
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_blit_buffer
argument_list|(
name|op
argument_list|,
name|buffer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|graph
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|mask_x
condition|)
operator|*
name|mask_x
operator|=
name|x
expr_stmt|;
if|if
condition|(
name|mask_y
condition|)
operator|*
name|mask_y
operator|=
name|y
expr_stmt|;
if|if
condition|(
name|mask_width
condition|)
operator|*
name|mask_width
operator|=
name|width
expr_stmt|;
if|if
condition|(
name|mask_height
condition|)
operator|*
name|mask_height
operator|=
name|height
expr_stmt|;
if|if
condition|(
operator|!
name|mask_buffer
condition|)
name|g_object_unref
argument_list|(
name|new_mask
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
name|buffer
return|;
block|}
end_function

end_unit

