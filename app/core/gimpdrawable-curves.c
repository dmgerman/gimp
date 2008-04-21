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
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/curves.h"
end_include

begin_include
include|#
directive|include
file|"base/gimplut.h"
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
file|"gegl/gimpcurvesconfig.h"
end_include

begin_comment
comment|/* temp */
end_comment

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
file|"gimpcurve.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-curves.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-operation.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-shadow.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_drawable_curves
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpCurvesConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_drawable_curves_spline (GimpDrawable * drawable,GimpProgress * progress,gint32 channel,const guint8 * points,gint n_points)
name|gimp_drawable_curves_spline
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gint32
name|channel
parameter_list|,
specifier|const
name|guint8
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|)
block|{
name|GimpCurvesConfig
modifier|*
name|config
decl_stmt|;
name|GimpCurve
modifier|*
name|curve
decl_stmt|;
name|gint
name|i
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
name|channel
operator|>=
name|GIMP_HISTOGRAM_VALUE
operator|&&
name|channel
operator|<=
name|GIMP_HISTOGRAM_ALPHA
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
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CURVES_CONFIG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|curve
operator|=
name|config
operator|->
name|curve
index|[
name|channel
index|]
expr_stmt|;
name|gimp_data_freeze
argument_list|(
name|GIMP_DATA
argument_list|(
name|curve
argument_list|)
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: create a curves object with the right number of points
endif|#
directive|endif
comment|/*  unset the last point  */
name|gimp_curve_set_point
argument_list|(
name|curve
argument_list|,
name|curve
operator|->
name|n_points
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|n_points
operator|=
name|MIN
argument_list|(
name|n_points
operator|/
literal|2
argument_list|,
name|curve
operator|->
name|n_points
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_points
condition|;
name|i
operator|++
control|)
name|gimp_curve_set_point
argument_list|(
name|curve
argument_list|,
name|i
argument_list|,
operator|(
name|gdouble
operator|)
name|points
index|[
name|i
operator|*
literal|2
index|]
operator|/
literal|255.0
argument_list|,
operator|(
name|gdouble
operator|)
name|points
index|[
name|i
operator|*
literal|2
operator|+
literal|1
index|]
operator|/
literal|255.0
argument_list|)
expr_stmt|;
name|gimp_data_thaw
argument_list|(
name|GIMP_DATA
argument_list|(
name|curve
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_curves
argument_list|(
name|drawable
argument_list|,
name|progress
argument_list|,
name|config
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|config
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_curves_explicit (GimpDrawable * drawable,GimpProgress * progress,gint32 channel,const guint8 * points,gint n_points)
name|gimp_drawable_curves_explicit
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gint32
name|channel
parameter_list|,
specifier|const
name|guint8
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|)
block|{
name|GimpCurvesConfig
modifier|*
name|config
decl_stmt|;
name|GimpCurve
modifier|*
name|curve
decl_stmt|;
name|gint
name|i
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
name|channel
operator|>=
name|GIMP_HISTOGRAM_VALUE
operator|&&
name|channel
operator|<=
name|GIMP_HISTOGRAM_ALPHA
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
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CURVES_CONFIG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|curve
operator|=
name|config
operator|->
name|curve
index|[
name|channel
index|]
expr_stmt|;
name|gimp_data_freeze
argument_list|(
name|GIMP_DATA
argument_list|(
name|curve
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_curve_set_curve_type
argument_list|(
name|curve
argument_list|,
name|GIMP_CURVE_SMOOTH
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
name|gimp_curve_set_curve
argument_list|(
name|curve
argument_list|,
operator|(
name|gdouble
operator|)
name|i
operator|/
literal|255.0
argument_list|,
operator|(
name|gdouble
operator|)
name|points
index|[
name|i
index|]
operator|/
literal|255.0
argument_list|)
expr_stmt|;
name|gimp_data_thaw
argument_list|(
name|GIMP_DATA
argument_list|(
name|curve
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_curves
argument_list|(
name|drawable
argument_list|,
name|progress
argument_list|,
name|config
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|config
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_curves (GimpDrawable * drawable,GimpProgress * progress,GimpCurvesConfig * config)
name|gimp_drawable_curves
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpCurvesConfig
modifier|*
name|config
parameter_list|)
block|{
if|if
condition|(
name|gimp_use_gegl
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
operator|->
name|image
operator|->
name|gimp
argument_list|)
condition|)
block|{
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|node
operator|=
name|g_object_new
argument_list|(
name|GEGL_TYPE_NODE
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp-curves"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|node
argument_list|,
literal|"config"
argument_list|,
name|config
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_operation
argument_list|(
name|drawable
argument_list|,
name|node
argument_list|,
name|TRUE
argument_list|,
name|progress
argument_list|,
name|_
argument_list|(
literal|"Curves"
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|node
argument_list|)
expr_stmt|;
block|}
else|else
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
comment|/* The application should occur only within selection bounds */
if|if
condition|(
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
block|{
name|Curves
name|cruft
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|gimp_curves_config_to_cruft
argument_list|(
name|config
argument_list|,
operator|&
name|cruft
argument_list|,
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_lut_setup
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|curves_lut_func
argument_list|,
operator|&
name|cruft
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
name|gimp_drawable_merge_shadow_tiles
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Curves"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_free_shadow_tiles
argument_list|(
name|drawable
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
block|}
block|}
end_function

end_unit

