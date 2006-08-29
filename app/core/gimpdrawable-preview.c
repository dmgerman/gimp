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
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
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
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-colormap.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-preview.h"
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
name|GimpImageType
name|type
parameter_list|,
specifier|const
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
name|TempBuf
modifier|*
DECL|function|gimp_drawable_get_preview (GimpViewable * viewable,GimpContext * context,gint width,gint height)
name|gimp_drawable_get_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
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
name|image
decl_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|viewable
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
name|image
operator|->
name|gimp
operator|->
name|config
operator|->
name|layer_previews
condition|)
return|return
name|NULL
return|;
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
name|image
operator|&&
name|image
operator|->
name|width
operator|>
name|PREVIEW_CACHE_PRIME_WIDTH
operator|&&
name|image
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

begin_function
name|gint
DECL|function|gimp_drawable_preview_bytes (GimpDrawable * drawable)
name|gimp_drawable_preview_bytes
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpImageBaseType
name|base_type
decl_stmt|;
name|gint
name|bytes
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|base_type
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
name|base_type
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
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|?
literal|4
else|:
literal|3
expr_stmt|;
break|break;
block|}
return|return
name|bytes
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_drawable_get_sub_preview (GimpDrawable * drawable,gint src_x,gint src_y,gint src_width,gint src_height,gint dest_width,gint dest_height)
name|gimp_drawable_get_sub_preview
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
name|src_width
parameter_list|,
name|gint
name|src_height
parameter_list|,
name|gint
name|dest_width
parameter_list|,
name|gint
name|dest_height
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
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
name|gint
name|bytes
decl_stmt|;
name|gint
name|subsample
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
name|src_x
operator|>=
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_y
operator|>=
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_width
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dest_width
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dest_height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|(
name|src_x
operator|+
name|src_width
operator|)
operator|<=
name|gimp_item_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|(
name|src_y
operator|+
name|src_height
operator|)
operator|<=
name|gimp_item_height
argument_list|(
name|item
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|->
name|gimp
operator|->
name|config
operator|->
name|layer_previews
condition|)
return|return
name|NULL
return|;
name|bytes
operator|=
name|gimp_drawable_preview_bytes
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
comment|/*  calculate 'acceptable' subsample  */
name|subsample
operator|=
literal|1
expr_stmt|;
while|while
condition|(
operator|(
name|dest_width
operator|*
operator|(
name|subsample
operator|+
literal|1
operator|)
operator|*
literal|2
operator|<
name|src_width
operator|)
operator|&&
operator|(
name|dest_height
operator|*
operator|(
name|subsample
operator|+
literal|1
operator|)
operator|*
literal|2
operator|<
name|src_width
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
name|gimp_drawable_get_tiles
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|src_x
argument_list|,
name|src_y
argument_list|,
name|src_width
argument_list|,
name|src_height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|preview_buf
operator|=
name|temp_buf_new
argument_list|(
name|dest_width
argument_list|,
name|dest_height
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
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|destPR
argument_list|,
name|preview_buf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|dest_width
argument_list|,
name|dest_height
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
name|gimp_drawable_preview_scale
argument_list|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|)
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
return|return
name|preview_buf
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
name|ret_buf
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
operator|->
name|preview_valid
operator|||
operator|!
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
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|ret_buf
operator|=
name|gimp_drawable_get_sub_preview
argument_list|(
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_height
argument_list|(
name|item
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
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
name|ret_buf
argument_list|)
expr_stmt|;
block|}
return|return
name|ret_buf
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_preview_scale (GimpImageType type,const guchar * cmap,PixelRegion * srcPR,PixelRegion * destPR,gint subsample)
name|gimp_drawable_preview_scale
parameter_list|(
name|GimpImageType
name|type
parameter_list|,
specifier|const
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
name|gboolean
name|has_alpha
decl_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|GIMP_IMAGE_TYPE_IS_INDEXED
argument_list|(
name|type
argument_list|)
operator|||
name|cmap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
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
name|has_alpha
operator|=
name|GIMP_IMAGE_TYPE_HAS_ALPHA
argument_list|(
name|type
argument_list|)
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
name|gdouble
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
name|srcPR
operator|->
name|x
argument_list|,
name|srcPR
operator|->
name|y
operator|+
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
name|GIMP_IMAGE_TYPE_IS_INDEXED
argument_list|(
name|type
argument_list|)
condition|)
block|{
name|gint
name|index
init|=
operator|*
name|s
operator|*
literal|3
decl_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
if|if
condition|(
name|s
index|[
name|ALPHA_I_PIX
index|]
operator|&
literal|0x80
condition|)
block|{
name|r
index|[
name|RED_PIX
index|]
operator|+=
name|cmap
index|[
name|index
operator|++
index|]
operator|*
name|tot_frac
expr_stmt|;
name|r
index|[
name|GREEN_PIX
index|]
operator|+=
name|cmap
index|[
name|index
operator|++
index|]
operator|*
name|tot_frac
expr_stmt|;
name|r
index|[
name|BLUE_PIX
index|]
operator|+=
name|cmap
index|[
name|index
operator|++
index|]
operator|*
name|tot_frac
expr_stmt|;
name|r
index|[
name|ALPHA_PIX
index|]
operator|+=
name|tot_frac
expr_stmt|;
block|}
comment|/* else the pixel contributes nothing and needs                    * not to be added                    */
block|}
else|else
block|{
name|r
index|[
name|RED_PIX
index|]
operator|+=
name|cmap
index|[
name|index
operator|++
index|]
operator|*
name|tot_frac
expr_stmt|;
name|r
index|[
name|GREEN_PIX
index|]
operator|+=
name|cmap
index|[
name|index
operator|++
index|]
operator|*
name|tot_frac
expr_stmt|;
name|r
index|[
name|BLUE_PIX
index|]
operator|+=
name|cmap
index|[
name|index
operator|++
index|]
operator|*
name|tot_frac
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|has_alpha
condition|)
block|{
comment|/* premultiply */
name|gdouble
name|local_frac
init|=
name|tot_frac
operator|*
operator|(
name|gdouble
operator|)
name|s
index|[
name|bytes
operator|-
literal|1
index|]
operator|/
literal|255.0
decl_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
operator|(
name|bytes
operator|-
literal|1
operator|)
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
name|local_frac
expr_stmt|;
name|r
index|[
name|bytes
operator|-
literal|1
index|]
operator|+=
name|local_frac
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
if|if
condition|(
name|has_alpha
condition|)
block|{
comment|/* unpremultiply */
name|gdouble
name|alpha
init|=
name|r
index|[
name|bytes
operator|-
literal|1
index|]
decl_stmt|;
if|if
condition|(
name|alpha
operator|>
name|EPSILON
condition|)
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
operator|(
name|bytes
operator|-
literal|1
operator|)
condition|;
name|b
operator|++
control|)
name|d
index|[
name|b
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
operator|(
name|r
index|[
name|b
index|]
operator|/
name|alpha
operator|)
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|d
index|[
name|bytes
operator|-
literal|1
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
operator|(
name|alpha
operator|*
name|tot_frac
operator|*
literal|255.0
operator|)
operator|+
literal|0.5
argument_list|)
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
name|d
index|[
name|b
index|]
operator|=
literal|0
expr_stmt|;
block|}
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
name|d
index|[
name|b
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
operator|(
name|r
index|[
name|b
index|]
operator|*
name|tot_frac
operator|)
operator|+
literal|0.5
argument_list|)
expr_stmt|;
block|}
name|r
operator|+=
name|bytes
expr_stmt|;
name|d
operator|+=
name|bytes
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
name|srcPR
operator|->
name|x
argument_list|,
name|srcPR
operator|->
name|y
operator|+
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

