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
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpscanconvert.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpstrokeoptions.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpunit.h"
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
file|"gimpdrawable.h"
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
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function
name|void
DECL|function|gimp_drawable_stroke_vectors (GimpDrawable * drawable,GimpVectors * vectors,GimpStrokeOptions * options)
name|gimp_drawable_stroke_vectors
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{
comment|/* Stroke options */
name|gdouble
name|opacity
decl_stmt|;
name|GimpRGB
modifier|*
name|color
decl_stmt|;
name|GimpLayerModeEffects
name|paint_mode
decl_stmt|;
name|gdouble
name|width
decl_stmt|;
name|GimpJoinStyle
name|join
decl_stmt|;
name|GimpCapStyle
name|cap
decl_stmt|;
name|gboolean
name|antialias
decl_stmt|;
name|GArray
modifier|*
name|dash_array
init|=
name|NULL
decl_stmt|;
name|gint
name|num_coords
init|=
literal|0
decl_stmt|;
name|GimpStroke
modifier|*
name|stroke
decl_stmt|;
name|GimpScanConvert
modifier|*
name|scan_convert
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
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|y1
decl_stmt|,
name|y2
decl_stmt|,
name|bytes
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|guchar
name|ucolor
index|[
literal|4
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|255
block|}
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
name|guchar
modifier|*
name|src_bytes
decl_stmt|;
name|PixelRegion
name|maskPR
decl_stmt|,
name|basePR
decl_stmt|;
comment|/* get the options from the GimpStrokeOptions */
name|g_object_get
argument_list|(
name|options
argument_list|,
literal|"opacity"
argument_list|,
operator|&
name|opacity
argument_list|,
literal|"foreground"
argument_list|,
operator|&
name|color
argument_list|,
literal|"paint-mode"
argument_list|,
operator|&
name|paint_mode
argument_list|,
literal|"width"
argument_list|,
operator|&
name|width
argument_list|,
literal|"join-style"
argument_list|,
operator|&
name|join
argument_list|,
literal|"cap-style"
argument_list|,
operator|&
name|cap
argument_list|,
literal|"antialias"
argument_list|,
operator|&
name|antialias
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|width_unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|GimpImage
modifier|*
name|gimage
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
name|width
operator|=
operator|(
name|width
operator|*
name|_gimp_unit_get_factor
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|options
operator|->
name|width_unit
argument_list|)
operator|*
operator|(
name|gimage
operator|->
name|xresolution
operator|+
name|gimage
operator|->
name|yresolution
operator|)
operator|/
literal|2
operator|)
expr_stmt|;
block|}
comment|/* what area do we operate on? */
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
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
name|w
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|h
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|scan_convert
operator|=
name|gimp_scan_convert_new
argument_list|(
name|w
argument_list|,
name|h
argument_list|,
name|antialias
argument_list|)
expr_stmt|;
comment|/* For each Stroke in the vector, interpolate it, and add it to the    * ScanConvert */
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
comment|/* Get the interpolated version of this stroke, and add it to our        * scanconvert. */
name|coords
operator|=
name|gimp_stroke_interpolate
argument_list|(
name|stroke
argument_list|,
literal|1
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
block|}
if|if
condition|(
name|num_coords
operator|==
literal|0
condition|)
block|{
name|gimp_scan_convert_free
argument_list|(
name|scan_convert
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*   dash_array = g_array_sized_new (FALSE, FALSE, sizeof (gdouble), dashes_len);   dash_array = g_array_prepend_vals (dash_array,&dashes, dashes_len);   */
name|gimp_scan_convert_stroke
argument_list|(
name|scan_convert
argument_list|,
name|width
argument_list|,
name|join
argument_list|,
name|cap
argument_list|,
literal|10.0
argument_list|,
literal|0.0
argument_list|,
name|dash_array
argument_list|)
expr_stmt|;
comment|/* fill a 1-bpp Tilemanager with black, this will describe the shape    * of the stroke. */
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
name|tile_manager_set_offsets
argument_list|(
name|mask
argument_list|,
name|x1
operator|+
name|x2
argument_list|,
name|y1
operator|+
name|y2
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
argument_list|)
expr_stmt|;
name|gimp_scan_convert_free
argument_list|(
name|scan_convert
argument_list|)
expr_stmt|;
name|bytes
operator|=
name|drawable
operator|->
name|bytes
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|bytes
operator|++
expr_stmt|;
name|src_bytes
operator|=
name|g_malloc0
argument_list|(
name|bytes
argument_list|)
expr_stmt|;
comment|/* Fill a TileManager with the stroke color */
name|gimp_rgb_get_uchar
argument_list|(
name|color
argument_list|,
name|ucolor
operator|+
literal|0
argument_list|,
name|ucolor
operator|+
literal|1
argument_list|,
name|ucolor
operator|+
literal|2
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|color
argument_list|)
expr_stmt|;
name|src_bytes
index|[
name|bytes
operator|-
literal|1
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
name|gimp_image_transform_color
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
operator|->
name|gimage
argument_list|,
name|drawable
argument_list|,
name|src_bytes
argument_list|,
name|GIMP_RGB
argument_list|,
name|ucolor
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
name|tile_manager_set_offsets
argument_list|(
name|base
argument_list|,
name|x1
operator|+
name|x2
argument_list|,
name|y1
operator|+
name|y2
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
name|color_region
argument_list|(
operator|&
name|basePR
argument_list|,
name|src_bytes
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src_bytes
argument_list|)
expr_stmt|;
comment|/* combine mask and stroke color TileManager */
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
name|apply_mask_to_region
argument_list|(
operator|&
name|basePR
argument_list|,
operator|&
name|maskPR
argument_list|,
name|OPAQUE_OPACITY
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
name|gimp_image_apply_image
argument_list|(
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
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
name|opacity
argument_list|,
name|paint_mode
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
name|x1
argument_list|,
name|y1
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

