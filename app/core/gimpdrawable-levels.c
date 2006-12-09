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
file|"base/gimphistogram.h"
end_include

begin_include
include|#
directive|include
file|"base/gimplut.h"
end_include

begin_include
include|#
directive|include
file|"base/levels.h"
end_include

begin_include
include|#
directive|include
file|"base/lut-funcs.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-processor.h"
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
file|"gimpdrawable-histogram.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-levels.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_drawable_levels (GimpDrawable * drawable,GimpContext * context,gint32 channel,gint32 low_input,gint32 high_input,gdouble gamma,gint32 low_output,gint32 high_output)
name|gimp_drawable_levels
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint32
name|channel
parameter_list|,
name|gint32
name|low_input
parameter_list|,
name|gint32
name|high_input
parameter_list|,
name|gdouble
name|gamma
parameter_list|,
name|gint32
name|low_output
parameter_list|,
name|gint32
name|high_output
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|Levels
name|levels
decl_stmt|;
name|GimpLut
modifier|*
name|lut
decl_stmt|;
comment|/* parameter checking */
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
operator|!
name|gimp_drawable_is_indexed
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
name|channel
operator|>=
name|GIMP_HISTOGRAM_VALUE
operator|&&
name|channel
operator|<=
name|GIMP_HISTOGRAM_ALPHA
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|low_input
operator|>=
literal|0
operator|&&
name|low_input
operator|<=
literal|255
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|high_input
operator|>=
literal|0
operator|&&
name|high_input
operator|<=
literal|255
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gamma
operator|>=
literal|0.1
operator|&&
name|gamma
operator|<=
literal|10.0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|low_output
operator|>=
literal|0
operator|&&
name|low_output
operator|<=
literal|255
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|high_output
operator|>=
literal|0
operator|&&
name|high_output
operator|<=
literal|255
argument_list|)
expr_stmt|;
if|if
condition|(
name|channel
operator|==
name|GIMP_HISTOGRAM_ALPHA
condition|)
name|g_return_if_fail
argument_list|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_gray
argument_list|(
name|drawable
argument_list|)
condition|)
name|g_return_if_fail
argument_list|(
name|channel
operator|==
name|GIMP_HISTOGRAM_VALUE
operator|||
name|channel
operator|==
name|GIMP_HISTOGRAM_ALPHA
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable
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
return|return;
comment|/* FIXME: hack */
if|if
condition|(
name|gimp_drawable_is_gray
argument_list|(
name|drawable
argument_list|)
operator|&&
name|channel
operator|==
name|GIMP_HISTOGRAM_ALPHA
condition|)
name|channel
operator|=
literal|1
expr_stmt|;
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|levels_init
argument_list|(
operator|&
name|levels
argument_list|)
expr_stmt|;
name|levels
operator|.
name|low_input
index|[
name|channel
index|]
operator|=
name|low_input
expr_stmt|;
name|levels
operator|.
name|high_input
index|[
name|channel
index|]
operator|=
name|high_input
expr_stmt|;
name|levels
operator|.
name|gamma
index|[
name|channel
index|]
operator|=
name|gamma
expr_stmt|;
name|levels
operator|.
name|low_output
index|[
name|channel
index|]
operator|=
name|low_output
expr_stmt|;
name|levels
operator|.
name|high_output
index|[
name|channel
index|]
operator|=
name|high_output
expr_stmt|;
comment|/* setup the lut */
name|gimp_lut_setup
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|levels_lut_func
argument_list|,
operator|&
name|levels
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
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
name|gimp_drawable_get_shadow_tiles
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pixel_regions_process_parallel
argument_list|(
operator|(
name|PixelProcessorFunc
operator|)
name|gimp_lut_process
argument_list|,
name|lut
argument_list|,
literal|2
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|gimp_lut_free
argument_list|(
name|lut
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Levels"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_levels_stretch (GimpDrawable * drawable,GimpContext * context)
name|gimp_drawable_levels_stretch
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|Levels
name|levels
decl_stmt|;
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|GimpHistogram
modifier|*
name|hist
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
operator|!
name|gimp_drawable_is_indexed
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable
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
return|return;
comment|/* Build the histogram */
name|hist
operator|=
name|gimp_histogram_new
argument_list|()
expr_stmt|;
name|gimp_drawable_calculate_histogram
argument_list|(
name|drawable
argument_list|,
name|hist
argument_list|)
expr_stmt|;
comment|/* Calculate the levels */
name|levels_init
argument_list|(
operator|&
name|levels
argument_list|)
expr_stmt|;
name|levels_stretch
argument_list|(
operator|&
name|levels
argument_list|,
name|hist
argument_list|,
operator|!
name|gimp_drawable_is_gray
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Set up the lut */
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|gimp_lut_setup
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|levels_lut_func
argument_list|,
operator|&
name|levels
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
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
name|gimp_drawable_get_shadow_tiles
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pixel_regions_process_parallel
argument_list|(
operator|(
name|PixelProcessorFunc
operator|)
name|gimp_lut_process
argument_list|,
name|lut
argument_list|,
literal|2
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|gimp_lut_free
argument_list|(
name|lut
argument_list|)
expr_stmt|;
name|gimp_histogram_free
argument_list|(
name|hist
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Levels"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

