begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdrawable-stroke.c  * Copyright (C) 2003 Simon Budig<simon@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-fill.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-stroke.h"
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
file|"gimpscanconvert.h"
end_include

begin_include
include|#
directive|include
file|"gimpstrokeoptions.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
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
DECL|function|gimp_drawable_stroke_boundary (GimpDrawable * drawable,GimpStrokeOptions * options,const GimpBoundSeg * bound_segs,gint n_bound_segs,gint offset_x,gint offset_y,gboolean push_undo)
name|gimp_drawable_stroke_boundary
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|,
specifier|const
name|GimpBoundSeg
modifier|*
name|bound_segs
parameter_list|,
name|gint
name|n_bound_segs
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GimpScanConvert
modifier|*
name|scan_convert
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
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|bound_segs
operator|==
name|NULL
operator|||
name|n_bound_segs
operator|!=
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_fill_options_get_style
argument_list|(
name|GIMP_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
operator|!=
name|GIMP_FILL_STYLE_PATTERN
operator|||
name|gimp_context_get_pattern
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|scan_convert
operator|=
name|gimp_scan_convert_new_from_boundary
argument_list|(
name|bound_segs
argument_list|,
name|n_bound_segs
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|scan_convert
condition|)
block|{
name|gimp_drawable_stroke_scan_convert
argument_list|(
name|drawable
argument_list|,
name|options
argument_list|,
name|scan_convert
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_scan_convert_free
argument_list|(
name|scan_convert
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_drawable_stroke_vectors (GimpDrawable * drawable,GimpStrokeOptions * options,GimpVectors * vectors,gboolean push_undo,GError ** error)
name|gimp_drawable_stroke_vectors
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
specifier|const
name|GimpBezierDesc
modifier|*
name|bezier
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
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_fill_options_get_style
argument_list|(
name|GIMP_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
operator|!=
name|GIMP_FILL_STYLE_PATTERN
operator|||
name|gimp_context_get_pattern
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
operator|!=
name|NULL
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
name|bezier
operator|=
name|gimp_vectors_get_bezier
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|bezier
operator|&&
name|bezier
operator|->
name|num_data
operator|>=
literal|2
condition|)
block|{
name|GimpScanConvert
modifier|*
name|scan_convert
init|=
name|gimp_scan_convert_new
argument_list|()
decl_stmt|;
name|gimp_scan_convert_add_bezier
argument_list|(
name|scan_convert
argument_list|,
name|bezier
argument_list|)
expr_stmt|;
name|gimp_drawable_stroke_scan_convert
argument_list|(
name|drawable
argument_list|,
name|options
argument_list|,
name|scan_convert
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_scan_convert_free
argument_list|(
name|scan_convert
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
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
literal|"Not enough points to stroke"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_stroke_scan_convert (GimpDrawable * drawable,GimpStrokeOptions * options,GimpScanConvert * scan_convert,gboolean push_undo)
name|gimp_drawable_stroke_scan_convert
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|,
name|GimpScanConvert
modifier|*
name|scan_convert
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|gdouble
name|width
decl_stmt|;
name|GimpUnit
name|unit
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
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|scan_convert
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_fill_options_get_style
argument_list|(
name|GIMP_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
operator|!=
name|GIMP_FILL_STYLE_PATTERN
operator|||
name|gimp_context_get_pattern
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
operator|!=
name|NULL
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
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
return|return;
name|width
operator|=
name|gimp_stroke_options_get_width
argument_list|(
name|options
argument_list|)
expr_stmt|;
name|unit
operator|=
name|gimp_stroke_options_get_unit
argument_list|(
name|options
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
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
name|gimp_scan_convert_set_pixel_ratio
argument_list|(
name|scan_convert
argument_list|,
name|yres
operator|/
name|xres
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_units_to_pixels
argument_list|(
name|width
argument_list|,
name|unit
argument_list|,
name|yres
argument_list|)
expr_stmt|;
block|}
name|gimp_scan_convert_stroke
argument_list|(
name|scan_convert
argument_list|,
name|width
argument_list|,
name|gimp_stroke_options_get_join_style
argument_list|(
name|options
argument_list|)
argument_list|,
name|gimp_stroke_options_get_cap_style
argument_list|(
name|options
argument_list|)
argument_list|,
name|gimp_stroke_options_get_miter_limit
argument_list|(
name|options
argument_list|)
argument_list|,
name|gimp_stroke_options_get_dash_offset
argument_list|(
name|options
argument_list|)
argument_list|,
name|gimp_stroke_options_get_dash_info
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_fill_scan_convert
argument_list|(
name|drawable
argument_list|,
name|GIMP_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|scan_convert
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

