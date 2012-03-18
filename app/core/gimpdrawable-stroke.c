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
file|"libgimpmath/gimpmath.h"
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
file|"base/boundary.h"
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
file|"gimpbezierdesc.h"
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
file|"gimppattern.h"
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
file|"vectors/gimpstroke.h"
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
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GimpScanConvert
modifier|*
name|gimp_drawable_render_boundary
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|BoundSeg
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpScanConvert
modifier|*
name|gimp_drawable_render_vectors
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|gboolean
name|do_stroke
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_stroke_scan_convert
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpFillOptions
modifier|*
name|options
parameter_list|,
name|GimpScanConvert
modifier|*
name|scan_convert
parameter_list|,
name|gboolean
name|do_stroke
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_drawable_fill_boundary (GimpDrawable * drawable,GimpFillOptions * options,const BoundSeg * bound_segs,gint n_bound_segs,gint offset_x,gint offset_y,gboolean push_undo)
name|gimp_drawable_fill_boundary
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpFillOptions
modifier|*
name|options
parameter_list|,
specifier|const
name|BoundSeg
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
name|options
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
name|gimp_drawable_render_boundary
argument_list|(
name|drawable
argument_list|,
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
name|FALSE
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
name|void
DECL|function|gimp_drawable_stroke_boundary (GimpDrawable * drawable,GimpStrokeOptions * options,const BoundSeg * bound_segs,gint n_bound_segs,gint offset_x,gint offset_y,gboolean push_undo)
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
name|BoundSeg
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
name|gimp_drawable_render_boundary
argument_list|(
name|drawable
argument_list|,
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
name|GIMP_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|scan_convert
argument_list|,
name|TRUE
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
DECL|function|gimp_drawable_fill_vectors (GimpDrawable * drawable,GimpFillOptions * options,GimpVectors * vectors,gboolean push_undo,GError ** error)
name|gimp_drawable_fill_vectors
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpFillOptions
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
name|GimpScanConvert
modifier|*
name|scan_convert
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
name|GIMP_IS_FILL_OPTIONS
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
name|options
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
name|scan_convert
operator|=
name|gimp_drawable_render_vectors
argument_list|(
name|drawable
argument_list|,
name|vectors
argument_list|,
name|FALSE
argument_list|,
name|error
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
name|FALSE
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
return|return
name|FALSE
return|;
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
name|GimpScanConvert
modifier|*
name|scan_convert
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
name|scan_convert
operator|=
name|gimp_drawable_render_vectors
argument_list|(
name|drawable
argument_list|,
name|vectors
argument_list|,
name|TRUE
argument_list|,
name|error
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
name|GIMP_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|scan_convert
argument_list|,
name|TRUE
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
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpScanConvert
modifier|*
DECL|function|gimp_drawable_render_boundary (GimpDrawable * drawable,const BoundSeg * bound_segs,gint n_bound_segs,gint offset_x,gint offset_y)
name|gimp_drawable_render_boundary
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|BoundSeg
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
parameter_list|)
block|{
if|if
condition|(
name|bound_segs
condition|)
block|{
name|BoundSeg
modifier|*
name|stroke_segs
decl_stmt|;
name|gint
name|n_stroke_segs
decl_stmt|;
name|stroke_segs
operator|=
name|boundary_sort
argument_list|(
name|bound_segs
argument_list|,
name|n_bound_segs
argument_list|,
operator|&
name|n_stroke_segs
argument_list|)
expr_stmt|;
if|if
condition|(
name|stroke_segs
condition|)
block|{
name|GimpBezierDesc
modifier|*
name|bezier
decl_stmt|;
name|bezier
operator|=
name|gimp_bezier_desc_new_from_bound_segs
argument_list|(
name|stroke_segs
argument_list|,
name|n_bound_segs
argument_list|,
name|n_stroke_segs
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stroke_segs
argument_list|)
expr_stmt|;
if|if
condition|(
name|bezier
condition|)
block|{
name|GimpScanConvert
modifier|*
name|scan_convert
decl_stmt|;
name|scan_convert
operator|=
name|gimp_scan_convert_new
argument_list|()
expr_stmt|;
name|gimp_bezier_desc_translate
argument_list|(
name|bezier
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
name|gimp_scan_convert_add_bezier
argument_list|(
name|scan_convert
argument_list|,
name|bezier
argument_list|)
expr_stmt|;
name|gimp_bezier_desc_free
argument_list|(
name|bezier
argument_list|)
expr_stmt|;
return|return
name|scan_convert
return|;
block|}
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|GimpScanConvert
modifier|*
DECL|function|gimp_drawable_render_vectors (GimpDrawable * drawable,GimpVectors * vectors,gboolean do_stroke,GError ** error)
name|gimp_drawable_render_vectors
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|gboolean
name|do_stroke
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
operator|(
name|do_stroke
condition|?
name|bezier
operator|->
name|num_data
operator|>=
literal|2
else|:
name|bezier
operator|->
name|num_data
operator|>
literal|4
operator|)
condition|)
block|{
name|GimpScanConvert
modifier|*
name|scan_convert
decl_stmt|;
name|scan_convert
operator|=
name|gimp_scan_convert_new
argument_list|()
expr_stmt|;
name|gimp_scan_convert_add_bezier
argument_list|(
name|scan_convert
argument_list|,
name|bezier
argument_list|)
expr_stmt|;
return|return
name|scan_convert
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
name|do_stroke
condition|?
name|_
argument_list|(
literal|"Not enough points to stroke"
argument_list|)
else|:
name|_
argument_list|(
literal|"Not enough points to fill"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_stroke_scan_convert (GimpDrawable * drawable,GimpFillOptions * options,GimpScanConvert * scan_convert,gboolean do_stroke,gboolean push_undo)
name|gimp_drawable_stroke_scan_convert
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpFillOptions
modifier|*
name|options
parameter_list|,
name|GimpScanConvert
modifier|*
name|scan_convert
parameter_list|,
name|gboolean
name|do_stroke
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
decl_stmt|;
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
name|TileManager
modifier|*
name|base
decl_stmt|;
name|TileManager
modifier|*
name|mask
decl_stmt|;
name|GeglBuffer
modifier|*
name|base_buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|mask_buffer
decl_stmt|;
name|GeglNode
modifier|*
name|apply_opacity
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|gint
name|off_x
decl_stmt|;
name|gint
name|off_y
decl_stmt|;
name|PixelRegion
name|basePR
decl_stmt|;
comment|/*  must call gimp_channel_is_empty() instead of relying on    *  gimp_item_mask_intersect() because the selection pretends to    *  be empty while it is being stroked, to prevent masking itself.    */
if|if
condition|(
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
condition|)
block|{
name|x
operator|=
literal|0
expr_stmt|;
name|y
operator|=
literal|0
expr_stmt|;
name|w
operator|=
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|h
operator|=
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
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
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
condition|)
block|{
return|return;
block|}
if|if
condition|(
name|do_stroke
condition|)
block|{
name|GimpStrokeOptions
modifier|*
name|stroke_options
init|=
name|GIMP_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
decl_stmt|;
name|gdouble
name|width
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|width
operator|=
name|gimp_stroke_options_get_width
argument_list|(
name|stroke_options
argument_list|)
expr_stmt|;
name|unit
operator|=
name|gimp_stroke_options_get_unit
argument_list|(
name|stroke_options
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
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
name|stroke_options
argument_list|)
argument_list|,
name|gimp_stroke_options_get_cap_style
argument_list|(
name|stroke_options
argument_list|)
argument_list|,
name|gimp_stroke_options_get_miter_limit
argument_list|(
name|stroke_options
argument_list|)
argument_list|,
name|gimp_stroke_options_get_dash_offset
argument_list|(
name|stroke_options
argument_list|)
argument_list|,
name|gimp_stroke_options_get_dash_info
argument_list|(
name|stroke_options
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/* fill a 1-bpp Tilemanager with black, this will describe the shape    * of the stroke.    */
name|mask
operator|=
name|tile_manager_new
argument_list|(
name|w
argument_list|,
name|h
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|mask_buffer
operator|=
name|gimp_tile_manager_create_buffer
argument_list|(
name|mask
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gegl_buffer_clear
argument_list|(
name|mask_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* render the stroke into it */
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
name|gimp_scan_convert_render
argument_list|(
name|scan_convert
argument_list|,
name|mask
argument_list|,
name|x
operator|+
name|off_x
argument_list|,
name|y
operator|+
name|off_y
argument_list|,
name|gimp_fill_options_get_antialias
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|bytes
operator|=
name|gimp_drawable_bytes_with_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|base
operator|=
name|tile_manager_new
argument_list|(
name|w
argument_list|,
name|h
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
name|base_buffer
operator|=
name|gimp_tile_manager_create_buffer
argument_list|(
name|base
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
name|gimp_fill_options_get_style
argument_list|(
name|options
argument_list|)
condition|)
block|{
case|case
name|GIMP_FILL_STYLE_SOLID
case|:
block|{
name|GeglColor
modifier|*
name|color
init|=
name|gegl_color_new
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
name|GimpRGB
name|fg
decl_stmt|;
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
name|gimp_gegl_color_set_rgba
argument_list|(
name|color
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
name|gegl_buffer_set_color
argument_list|(
name|base_buffer
argument_list|,
name|NULL
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|color
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_FILL_STYLE_PATTERN
case|:
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
decl_stmt|;
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
name|base_buffer
argument_list|,
name|NULL
argument_list|,
name|pattern_buffer
argument_list|,
literal|0
argument_list|,
literal|0
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
argument_list|)
expr_stmt|;
name|gimp_apply_operation
argument_list|(
name|base_buffer
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|apply_opacity
argument_list|,
name|TRUE
argument_list|,
name|base_buffer
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
name|base_buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|mask_buffer
argument_list|)
expr_stmt|;
comment|/* Apply to drawable */
name|pixel_region_init
argument_list|(
operator|&
name|basePR
argument_list|,
name|base
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_region
argument_list|(
name|drawable
argument_list|,
operator|&
name|basePR
argument_list|,
name|push_undo
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Render Stroke"
argument_list|)
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|tile_manager_unref
argument_list|(
name|mask
argument_list|)
expr_stmt|;
name|tile_manager_unref
argument_list|(
name|base
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
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

