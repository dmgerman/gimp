begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdrawable-stroke.c  * Copyright (C) 2003 Simon Budig<simon@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpunit.h"
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
name|void
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
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_drawable_stroke_boundary (GimpDrawable * drawable,GimpStrokeOptions * options,const BoundSeg * bound_segs,gint n_bound_segs,gint offset_x,gint offset_y)
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
parameter_list|)
block|{
name|GimpScanConvert
modifier|*
name|scan_convert
decl_stmt|;
name|BoundSeg
modifier|*
name|sorted_segs
decl_stmt|;
name|BoundSeg
modifier|*
name|stroke_segs
decl_stmt|;
name|gint
name|n_stroke_segs
decl_stmt|;
name|GimpVector2
modifier|*
name|points
decl_stmt|;
name|gint
name|n_points
decl_stmt|;
name|gint
name|seg
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
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|bound_segs
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|n_bound_segs
operator|>
literal|0
argument_list|)
expr_stmt|;
name|sorted_segs
operator|=
name|sort_boundary
argument_list|(
name|bound_segs
argument_list|,
name|n_bound_segs
argument_list|,
operator|&
name|n_stroke_segs
argument_list|)
expr_stmt|;
name|stroke_segs
operator|=
name|simplify_boundary
argument_list|(
name|sorted_segs
argument_list|,
name|n_stroke_segs
argument_list|,
operator|&
name|n_bound_segs
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|sorted_segs
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_stroke_segs
operator|==
literal|0
condition|)
return|return;
name|scan_convert
operator|=
name|gimp_scan_convert_new
argument_list|()
expr_stmt|;
name|points
operator|=
name|g_new0
argument_list|(
name|GimpVector2
argument_list|,
name|n_bound_segs
operator|+
literal|4
argument_list|)
expr_stmt|;
name|seg
operator|=
literal|0
expr_stmt|;
name|n_points
operator|=
literal|0
expr_stmt|;
comment|/* we offset all coordinates by 0.5 to align the brush with the path */
name|points
index|[
name|n_points
index|]
operator|.
name|x
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
literal|0
index|]
operator|.
name|x1
operator|+
name|offset_y
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|points
index|[
name|n_points
index|]
operator|.
name|y
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
literal|0
index|]
operator|.
name|y1
operator|+
name|offset_y
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|n_points
operator|++
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_stroke_segs
condition|;
name|i
operator|++
control|)
block|{
while|while
condition|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|x1
operator|!=
operator|-
literal|1
operator|||
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|x2
operator|!=
operator|-
literal|1
operator|||
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|y1
operator|!=
operator|-
literal|1
operator|||
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|y2
operator|!=
operator|-
literal|1
condition|)
block|{
name|points
index|[
name|n_points
index|]
operator|.
name|x
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|x1
operator|+
name|offset_x
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|points
index|[
name|n_points
index|]
operator|.
name|y
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|y1
operator|+
name|offset_y
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|n_points
operator|++
expr_stmt|;
name|seg
operator|++
expr_stmt|;
block|}
comment|/* Close the stroke points up */
name|points
index|[
name|n_points
index|]
operator|=
name|points
index|[
literal|0
index|]
expr_stmt|;
name|n_points
operator|++
expr_stmt|;
name|gimp_scan_convert_add_polyline
argument_list|(
name|scan_convert
argument_list|,
name|n_points
argument_list|,
name|points
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|n_points
operator|=
literal|0
expr_stmt|;
name|seg
operator|++
expr_stmt|;
name|points
index|[
name|n_points
index|]
operator|.
name|x
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|x1
operator|+
name|offset_x
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|points
index|[
name|n_points
index|]
operator|.
name|y
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|y1
operator|+
name|offset_y
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|n_points
operator|++
expr_stmt|;
block|}
name|g_free
argument_list|(
name|points
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stroke_segs
argument_list|)
expr_stmt|;
name|gimp_drawable_stroke_scan_convert
argument_list|(
name|drawable
argument_list|,
name|options
argument_list|,
name|scan_convert
argument_list|)
expr_stmt|;
name|gimp_scan_convert_free
argument_list|(
name|scan_convert
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_stroke_vectors (GimpDrawable * drawable,GimpStrokeOptions * options,GimpVectors * vectors)
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
parameter_list|)
block|{
name|GimpScanConvert
modifier|*
name|scan_convert
decl_stmt|;
name|GimpStroke
modifier|*
name|stroke
decl_stmt|;
name|gint
name|num_coords
init|=
literal|0
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
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
name|scan_convert
operator|=
name|gimp_scan_convert_new
argument_list|()
expr_stmt|;
comment|/* For each Stroke in the vector, interpolate it, and add it to the    * ScanConvert    */
for|for
control|(
name|stroke
operator|=
name|gimp_vectors_stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|NULL
argument_list|)
init|;
name|stroke
condition|;
name|stroke
operator|=
name|gimp_vectors_stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|)
control|)
block|{
name|GimpVector2
modifier|*
name|points
decl_stmt|;
name|gboolean
name|closed
decl_stmt|;
name|GArray
modifier|*
name|coords
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/* Get the interpolated version of this stroke, and add it to our        * scanconvert.        */
name|coords
operator|=
name|gimp_stroke_interpolate
argument_list|(
name|stroke
argument_list|,
literal|0.2
argument_list|,
operator|&
name|closed
argument_list|)
expr_stmt|;
if|if
condition|(
name|coords
operator|&&
name|coords
operator|->
name|len
condition|)
block|{
name|points
operator|=
name|g_new0
argument_list|(
name|GimpVector2
argument_list|,
name|coords
operator|->
name|len
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
name|coords
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|points
index|[
name|i
index|]
operator|.
name|x
operator|=
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
name|i
argument_list|)
operator|.
name|x
expr_stmt|;
name|points
index|[
name|i
index|]
operator|.
name|y
operator|=
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
name|i
argument_list|)
operator|.
name|y
expr_stmt|;
name|num_coords
operator|++
expr_stmt|;
block|}
name|gimp_scan_convert_add_polyline
argument_list|(
name|scan_convert
argument_list|,
name|coords
operator|->
name|len
argument_list|,
name|points
argument_list|,
name|closed
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|points
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|coords
condition|)
name|g_array_free
argument_list|(
name|coords
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|num_coords
operator|>
literal|0
condition|)
name|gimp_drawable_stroke_scan_convert
argument_list|(
name|drawable
argument_list|,
name|options
argument_list|,
name|scan_convert
argument_list|)
expr_stmt|;
name|gimp_scan_convert_free
argument_list|(
name|scan_convert
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
DECL|function|gimp_drawable_stroke_scan_convert (GimpDrawable * drawable,GimpStrokeOptions * options,GimpScanConvert * scan_convert)
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
parameter_list|)
block|{
comment|/* Stroke options */
name|gdouble
name|width
decl_stmt|;
name|GArray
modifier|*
name|dash_array
init|=
name|NULL
decl_stmt|;
name|TileManager
modifier|*
name|base
decl_stmt|;
name|TileManager
modifier|*
name|mask
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
decl_stmt|,
name|off_y
decl_stmt|;
name|guchar
name|bg
index|[
literal|1
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|PixelRegion
name|maskPR
decl_stmt|,
name|basePR
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|context
operator|=
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
comment|/* what area do we operate on? */
if|if
condition|(
operator|!
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
condition|)
block|{
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gimp_drawable_mask_bounds
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
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|w
operator|=
name|x2
operator|-
name|x
expr_stmt|;
name|h
operator|=
name|y2
operator|-
name|y
expr_stmt|;
block|}
else|else
block|{
name|x
operator|=
name|y
operator|=
literal|0
expr_stmt|;
name|w
operator|=
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|h
operator|=
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_item_offsets
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
name|width
operator|=
name|options
operator|->
name|width
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|gimp_scan_convert_set_pixel_ratio
argument_list|(
name|scan_convert
argument_list|,
name|gimage
operator|->
name|yresolution
operator|/
name|gimage
operator|->
name|xresolution
argument_list|)
expr_stmt|;
name|width
operator|*=
operator|(
name|gimage
operator|->
name|yresolution
operator|/
name|_gimp_unit_get_factor
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|options
operator|->
name|unit
argument_list|)
operator|)
expr_stmt|;
block|}
name|gimp_scan_convert_stroke
argument_list|(
name|scan_convert
argument_list|,
name|width
argument_list|,
name|options
operator|->
name|join_style
argument_list|,
name|options
operator|->
name|cap_style
argument_list|,
name|options
operator|->
name|miter
argument_list|,
literal|0.0
argument_list|,
name|dash_array
argument_list|)
expr_stmt|;
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
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|mask
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|maskPR
argument_list|,
name|bg
argument_list|)
expr_stmt|;
comment|/* render the stroke into it */
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
name|options
operator|->
name|antialias
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
name|TRUE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|mask
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
switch|switch
condition|(
name|options
operator|->
name|style
condition|)
block|{
case|case
name|GIMP_STROKE_STYLE_SOLID
case|:
block|{
name|guchar
name|tmp_col
index|[
name|MAX_CHANNELS
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|guchar
name|col
index|[
name|MAX_CHANNELS
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|context
operator|->
name|foreground
argument_list|,
operator|&
name|tmp_col
index|[
name|RED_PIX
index|]
argument_list|,
operator|&
name|tmp_col
index|[
name|GREEN_PIX
index|]
argument_list|,
operator|&
name|tmp_col
index|[
name|BLUE_PIX
index|]
argument_list|)
expr_stmt|;
name|gimp_image_transform_color
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|col
argument_list|,
name|GIMP_RGB
argument_list|,
name|tmp_col
argument_list|)
expr_stmt|;
name|col
index|[
name|bytes
operator|-
literal|1
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
name|color_region_mask
argument_list|(
operator|&
name|basePR
argument_list|,
operator|&
name|maskPR
argument_list|,
name|col
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_STROKE_STYLE_PATTERN
case|:
block|{
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
name|TempBuf
modifier|*
name|pat_buf
decl_stmt|;
name|gboolean
name|new_buf
decl_stmt|;
name|pattern
operator|=
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|pat_buf
operator|=
name|gimp_image_transform_temp_buf
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|pattern
operator|->
name|mask
argument_list|,
operator|&
name|new_buf
argument_list|)
expr_stmt|;
name|pattern_region
argument_list|(
operator|&
name|basePR
argument_list|,
operator|&
name|maskPR
argument_list|,
name|pat_buf
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_buf
condition|)
name|temp_buf_free
argument_list|(
name|pat_buf
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
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
name|TRUE
argument_list|,
name|_
argument_list|(
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

