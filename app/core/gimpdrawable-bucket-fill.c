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
file|"gimp.h"
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
DECL|function|gimp_drawable_bucket_fill (GimpDrawable * drawable,GimpFillOptions * options,gboolean fill_transparent,GimpSelectCriterion fill_criterion,gdouble threshold,gboolean sample_merged,gboolean diagonal_neighbors,gdouble x,gdouble y)
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
name|x
parameter_list|,
name|gdouble
name|y
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
name|mask_buffer
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
name|gint
name|sel_x1
decl_stmt|,
name|sel_y1
decl_stmt|,
name|sel_x2
decl_stmt|,
name|sel_y2
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
name|sel_x1
argument_list|,
operator|&
name|sel_y1
argument_list|,
operator|&
name|sel_x2
argument_list|,
operator|&
name|sel_y2
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|sel_x1
operator|==
name|sel_x2
operator|)
operator|||
operator|(
name|sel_y1
operator|==
name|sel_y2
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
comment|/*  Do a seed bucket fill...To do this, calculate a new    *  contiguous region.    */
name|mask_buffer
operator|=
name|gimp_pickable_contiguous_region_by_seed
argument_list|(
name|pickable
argument_list|,
name|TRUE
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
name|x
argument_list|,
operator|(
name|gint
operator|)
name|y
argument_list|)
expr_stmt|;
name|gimp_gegl_mask_bounds
argument_list|(
name|mask_buffer
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
comment|/*  If there is a selection, inersect the region bounds    *  with the selection bounds, to avoid processing areas    *  that are going to be masked out anyway.  The actual    *  intersection of the fill region with the mask data    *  happens when combining the fill buffer, in    *  gimp_drawable_apply_buffer().    */
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
name|gimp_rectangle_intersect
argument_list|(
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
argument_list|,
name|sel_x1
operator|+
name|off_x
argument_list|,
name|sel_y1
operator|+
name|off_y
argument_list|,
name|sel_x2
operator|-
name|sel_x1
argument_list|,
name|sel_y2
operator|-
name|sel_y1
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
condition|)
block|{
name|x2
operator|+=
name|x1
expr_stmt|;
name|y2
operator|+=
name|y1
expr_stmt|;
block|}
else|else
block|{
comment|/*  The fill region and the selection are disjoint; bail.  */
name|g_object_unref
argument_list|(
name|mask_buffer
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
return|return;
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
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
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
name|mask_buffer
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
name|g_object_unref
argument_list|(
name|mask_buffer
argument_list|)
expr_stmt|;
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
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
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
name|NULL
argument_list|,
name|x1
argument_list|,
name|y1
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

