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
file|"libgimpmath/gimpmath.h"
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
file|"base/tile.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewcache.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_drawable_preview_private
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_preview_scale
parameter_list|(
name|GimpImageBaseType
name|type
parameter_list|,
name|guchar
modifier|*
name|cmap
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|,
name|gint
name|subsample
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_drawable_get_preview_size (GimpViewable * viewable,gint size,gboolean is_popup,gboolean dot_for_dot,gint * width,gint * height)
name|gimp_drawable_get_preview_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|size
parameter_list|,
name|gboolean
name|is_popup
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|viewable
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
if|if
condition|(
name|gimage
operator|&&
operator|!
name|is_popup
condition|)
block|{
name|gimp_viewable_calc_preview_size
argument_list|(
name|viewable
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|,
name|size
argument_list|,
name|size
argument_list|,
name|dot_for_dot
argument_list|,
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_viewable_calc_preview_size
argument_list|(
name|viewable
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|size
argument_list|,
name|size
argument_list|,
name|dot_for_dot
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_drawable_get_preview (GimpViewable * viewable,gint width,gint height)
name|gimp_drawable_get_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|viewable
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
comment|/* Ok prime the cache with a large preview if the cache is invalid */
if|if
condition|(
operator|!
name|drawable
operator|->
name|preview_valid
operator|&&
name|width
operator|<=
name|PREVIEW_CACHE_PRIME_WIDTH
operator|&&
name|height
operator|<=
name|PREVIEW_CACHE_PRIME_HEIGHT
operator|&&
name|gimage
operator|&&
name|gimage
operator|->
name|width
operator|>
name|PREVIEW_CACHE_PRIME_WIDTH
operator|&&
name|gimage
operator|->
name|height
operator|>
name|PREVIEW_CACHE_PRIME_HEIGHT
condition|)
block|{
name|TempBuf
modifier|*
name|tb
init|=
name|gimp_drawable_preview_private
argument_list|(
name|drawable
argument_list|,
name|PREVIEW_CACHE_PRIME_WIDTH
argument_list|,
name|PREVIEW_CACHE_PRIME_HEIGHT
argument_list|)
decl_stmt|;
comment|/* Save the 2nd call */
if|if
condition|(
name|width
operator|==
name|PREVIEW_CACHE_PRIME_WIDTH
operator|&&
name|height
operator|==
name|PREVIEW_CACHE_PRIME_HEIGHT
condition|)
return|return
name|tb
return|;
block|}
comment|/* Second call - should NOT visit the tile cache...*/
return|return
name|gimp_drawable_preview_private
argument_list|(
name|drawable
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_drawable_preview_private (GimpDrawable * drawable,gint width,gint height)
name|gimp_drawable_preview_private
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|TempBuf
modifier|*
name|preview_buf
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|;
name|PixelRegion
name|destPR
decl_stmt|;
name|GimpImageBaseType
name|type
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|gint
name|subsample
decl_stmt|;
name|TempBuf
modifier|*
name|ret_buf
decl_stmt|;
name|type
operator|=
name|GIMP_RGB
expr_stmt|;
name|bytes
operator|=
literal|0
expr_stmt|;
comment|/*  The easy way  */
if|if
condition|(
name|drawable
operator|->
name|preview_valid
operator|&&
operator|(
name|ret_buf
operator|=
name|gimp_preview_cache_get
argument_list|(
operator|&
name|drawable
operator|->
name|preview_cache
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
operator|)
condition|)
block|{
return|return
name|ret_buf
return|;
block|}
comment|/*  The hard way  */
else|else
block|{
name|type
operator|=
name|GIMP_IMAGE_TYPE_BASE_TYPE
argument_list|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_RGB
case|:
case|case
name|GIMP_GRAY
case|:
name|bytes
operator|=
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED
case|:
name|bytes
operator|=
operator|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|GIMP_INDEXED_IMAGE
operator|)
condition|?
literal|3
else|:
literal|4
expr_stmt|;
break|break;
block|}
comment|/*  calculate 'acceptable' subsample  */
name|subsample
operator|=
literal|1
expr_stmt|;
comment|/* handle some truncation errors */
if|if
condition|(
name|width
operator|<
literal|1
condition|)
name|width
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|height
operator|<
literal|1
condition|)
name|height
operator|=
literal|1
expr_stmt|;
while|while
condition|(
operator|(
name|width
operator|*
operator|(
name|subsample
operator|+
literal|1
operator|)
operator|*
literal|2
operator|<
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
operator|)
operator|&&
operator|(
name|height
operator|*
operator|(
name|subsample
operator|+
literal|1
operator|)
operator|*
literal|2
operator|<
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
name|subsample
operator|+=
literal|1
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|drawable
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|preview_buf
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|bytes
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|destPR
operator|.
name|bytes
operator|=
name|preview_buf
operator|->
name|bytes
expr_stmt|;
name|destPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|destPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|destPR
operator|.
name|w
operator|=
name|width
expr_stmt|;
name|destPR
operator|.
name|h
operator|=
name|height
expr_stmt|;
name|destPR
operator|.
name|rowstride
operator|=
name|width
operator|*
name|destPR
operator|.
name|bytes
expr_stmt|;
name|destPR
operator|.
name|data
operator|=
name|temp_buf_data
argument_list|(
name|preview_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
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
name|gimp_drawable_preview_scale
argument_list|(
name|type
argument_list|,
name|gimage
operator|->
name|cmap
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|,
name|subsample
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_CHANNEL
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|subsample_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|,
name|subsample
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|drawable
operator|->
name|preview_valid
condition|)
name|gimp_preview_cache_invalidate
argument_list|(
operator|&
name|drawable
operator|->
name|preview_cache
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|preview_valid
operator|=
name|TRUE
expr_stmt|;
name|gimp_preview_cache_add
argument_list|(
operator|&
name|drawable
operator|->
name|preview_cache
argument_list|,
name|preview_buf
argument_list|)
expr_stmt|;
return|return
name|preview_buf
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_preview_scale (GimpImageBaseType type,guchar * cmap,PixelRegion * srcPR,PixelRegion * destPR,gint subsample)
name|gimp_drawable_preview_scale
parameter_list|(
name|GimpImageBaseType
name|type
parameter_list|,
name|guchar
modifier|*
name|cmap
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|,
name|gint
name|subsample
parameter_list|)
block|{
DECL|macro|EPSILON
define|#
directive|define
name|EPSILON
value|0.000001
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|s
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|gdouble
modifier|*
name|row
decl_stmt|,
modifier|*
name|r
decl_stmt|;
name|gint
name|destwidth
decl_stmt|;
name|gint
name|src_row
decl_stmt|,
name|src_col
decl_stmt|;
name|gint
name|bytes
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|orig_width
decl_stmt|,
name|orig_height
decl_stmt|;
name|gdouble
name|x_rat
decl_stmt|,
name|y_rat
decl_stmt|;
name|gdouble
name|x_cum
decl_stmt|,
name|y_cum
decl_stmt|;
name|gdouble
name|x_last
decl_stmt|,
name|y_last
decl_stmt|;
name|gdouble
modifier|*
name|x_frac
decl_stmt|,
name|y_frac
decl_stmt|,
name|tot_frac
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|gint
name|frac
decl_stmt|;
name|gboolean
name|advance_dest
decl_stmt|;
name|guchar
name|rgb
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|orig_width
operator|=
name|srcPR
operator|->
name|w
operator|/
name|subsample
expr_stmt|;
name|orig_height
operator|=
name|srcPR
operator|->
name|h
operator|/
name|subsample
expr_stmt|;
name|width
operator|=
name|destPR
operator|->
name|w
expr_stmt|;
name|height
operator|=
name|destPR
operator|->
name|h
expr_stmt|;
comment|/*  Some calculations...  */
name|bytes
operator|=
name|destPR
operator|->
name|bytes
expr_stmt|;
name|destwidth
operator|=
name|destPR
operator|->
name|rowstride
expr_stmt|;
comment|/*  the data pointers...  */
name|src
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|orig_width
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|dest
operator|=
name|destPR
operator|->
name|data
expr_stmt|;
comment|/*  find the ratios of old x to new x and old y to new y  */
name|x_rat
operator|=
operator|(
name|gdouble
operator|)
name|orig_width
operator|/
operator|(
name|gdouble
operator|)
name|width
expr_stmt|;
name|y_rat
operator|=
operator|(
name|gdouble
operator|)
name|orig_height
operator|/
operator|(
name|gdouble
operator|)
name|height
expr_stmt|;
comment|/*  allocate an array to help with the calculations  */
name|row
operator|=
name|g_new0
argument_list|(
name|gdouble
argument_list|,
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|x_frac
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|width
operator|+
name|orig_width
argument_list|)
expr_stmt|;
comment|/*  initialize the pre-calculated pixel fraction array  */
name|src_col
operator|=
literal|0
expr_stmt|;
name|x_cum
operator|=
operator|(
name|gdouble
operator|)
name|src_col
expr_stmt|;
name|x_last
operator|=
name|x_cum
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|width
operator|+
name|orig_width
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|x_cum
operator|+
name|x_rat
operator|<=
operator|(
name|src_col
operator|+
literal|1
operator|+
name|EPSILON
operator|)
condition|)
block|{
name|x_cum
operator|+=
name|x_rat
expr_stmt|;
name|x_frac
index|[
name|i
index|]
operator|=
name|x_cum
operator|-
name|x_last
expr_stmt|;
block|}
else|else
block|{
name|src_col
operator|++
expr_stmt|;
name|x_frac
index|[
name|i
index|]
operator|=
name|src_col
operator|-
name|x_last
expr_stmt|;
block|}
name|x_last
operator|+=
name|x_frac
index|[
name|i
index|]
expr_stmt|;
block|}
comment|/*  counters...  */
name|src_row
operator|=
literal|0
expr_stmt|;
name|y_cum
operator|=
operator|(
name|double
operator|)
name|src_row
expr_stmt|;
name|y_last
operator|=
name|y_cum
expr_stmt|;
name|pixel_region_get_row
argument_list|(
name|srcPR
argument_list|,
literal|0
argument_list|,
name|src_row
operator|*
name|subsample
argument_list|,
name|orig_width
operator|*
name|subsample
argument_list|,
name|src
argument_list|,
name|subsample
argument_list|)
expr_stmt|;
comment|/*  Scale the selected region  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|height
condition|;
control|)
block|{
name|src_col
operator|=
literal|0
expr_stmt|;
name|x_cum
operator|=
operator|(
name|gdouble
operator|)
name|src_col
expr_stmt|;
comment|/* determine the fraction of the src pixel we are using for y */
if|if
condition|(
name|y_cum
operator|+
name|y_rat
operator|<=
operator|(
name|src_row
operator|+
literal|1
operator|+
name|EPSILON
operator|)
condition|)
block|{
name|y_cum
operator|+=
name|y_rat
expr_stmt|;
name|y_frac
operator|=
name|y_cum
operator|-
name|y_last
expr_stmt|;
name|advance_dest
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|src_row
operator|++
expr_stmt|;
name|y_frac
operator|=
name|src_row
operator|-
name|y_last
expr_stmt|;
name|advance_dest
operator|=
name|FALSE
expr_stmt|;
block|}
name|y_last
operator|+=
name|y_frac
expr_stmt|;
name|s
operator|=
name|src
expr_stmt|;
name|r
operator|=
name|row
expr_stmt|;
name|frac
operator|=
literal|0
expr_stmt|;
name|j
operator|=
name|width
expr_stmt|;
while|while
condition|(
name|j
condition|)
block|{
name|tot_frac
operator|=
name|x_frac
index|[
name|frac
operator|++
index|]
operator|*
name|y_frac
expr_stmt|;
comment|/*  If indexed, transform the color to RGB  */
if|if
condition|(
name|type
operator|==
name|GIMP_INDEXED
condition|)
block|{
name|map_to_color
argument_list|(
literal|2
argument_list|,
name|cmap
argument_list|,
name|s
argument_list|,
name|rgb
argument_list|)
expr_stmt|;
name|r
index|[
name|RED_PIX
index|]
operator|+=
name|rgb
index|[
name|RED_PIX
index|]
operator|*
name|tot_frac
expr_stmt|;
name|r
index|[
name|GREEN_PIX
index|]
operator|+=
name|rgb
index|[
name|GREEN_PIX
index|]
operator|*
name|tot_frac
expr_stmt|;
name|r
index|[
name|BLUE_PIX
index|]
operator|+=
name|rgb
index|[
name|BLUE_PIX
index|]
operator|*
name|tot_frac
expr_stmt|;
if|if
condition|(
name|bytes
operator|==
literal|4
condition|)
name|r
index|[
name|ALPHA_PIX
index|]
operator|+=
name|s
index|[
name|ALPHA_I_PIX
index|]
operator|*
name|tot_frac
expr_stmt|;
block|}
else|else
block|{
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
name|r
index|[
name|b
index|]
operator|+=
name|s
index|[
name|b
index|]
operator|*
name|tot_frac
expr_stmt|;
block|}
comment|/*  increment the destination  */
if|if
condition|(
name|x_cum
operator|+
name|x_rat
operator|<=
operator|(
name|src_col
operator|+
literal|1
operator|+
name|EPSILON
operator|)
condition|)
block|{
name|r
operator|+=
name|bytes
expr_stmt|;
name|x_cum
operator|+=
name|x_rat
expr_stmt|;
name|j
operator|--
expr_stmt|;
block|}
comment|/* increment the source */
else|else
block|{
name|s
operator|+=
name|srcPR
operator|->
name|bytes
expr_stmt|;
name|src_col
operator|++
expr_stmt|;
block|}
block|}
if|if
condition|(
name|advance_dest
condition|)
block|{
name|tot_frac
operator|=
literal|1.0
operator|/
operator|(
name|x_rat
operator|*
name|y_rat
operator|)
expr_stmt|;
comment|/*  copy "row" to "dest"  */
name|d
operator|=
name|dest
expr_stmt|;
name|r
operator|=
name|row
expr_stmt|;
name|j
operator|=
name|width
expr_stmt|;
while|while
condition|(
name|j
operator|--
condition|)
block|{
name|b
operator|=
name|bytes
expr_stmt|;
while|while
condition|(
name|b
operator|--
condition|)
operator|*
name|d
operator|++
operator|=
call|(
name|guchar
call|)
argument_list|(
operator|(
operator|*
name|r
operator|++
operator|*
name|tot_frac
operator|)
operator|+
literal|0.5
argument_list|)
expr_stmt|;
block|}
name|dest
operator|+=
name|destwidth
expr_stmt|;
comment|/*  clear the "row" array  */
name|memset
argument_list|(
name|row
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
operator|*
name|destwidth
argument_list|)
expr_stmt|;
name|i
operator|++
expr_stmt|;
block|}
else|else
block|{
name|pixel_region_get_row
argument_list|(
name|srcPR
argument_list|,
literal|0
argument_list|,
name|src_row
operator|*
name|subsample
argument_list|,
name|orig_width
operator|*
name|subsample
argument_list|,
name|src
argument_list|,
name|subsample
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  free up temporary arrays  */
name|g_free
argument_list|(
name|row
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|x_frac
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

