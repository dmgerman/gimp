begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppixelfetcher.c  *  * FIXME: fix the following comment:  * Contains all kinds of miscellaneous routines factored out from different  * plug-ins. They stay here until their API has crystalized a bit and we can  * put them into the file where they belong (Maurits Rijk  *<lpeek.mrijk@consunet.nl> if you want to blame someone for this mess)  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_struct
DECL|struct|_GimpPixelFetcher
struct|struct
name|_GimpPixelFetcher
block|{
DECL|member|col
DECL|member|row
name|gint
name|col
decl_stmt|,
name|row
decl_stmt|;
DECL|member|img_width
name|gint
name|img_width
decl_stmt|;
DECL|member|img_height
name|gint
name|img_height
decl_stmt|;
DECL|member|sel_x1
DECL|member|sel_y1
DECL|member|sel_x2
DECL|member|sel_y2
name|gint
name|sel_x1
decl_stmt|,
name|sel_y1
decl_stmt|,
name|sel_x2
decl_stmt|,
name|sel_y2
decl_stmt|;
DECL|member|img_bpp
name|gint
name|img_bpp
decl_stmt|;
DECL|member|tile_width
DECL|member|tile_height
name|gint
name|tile_width
decl_stmt|,
name|tile_height
decl_stmt|;
DECL|member|bg_color
name|guchar
name|bg_color
index|[
literal|4
index|]
decl_stmt|;
DECL|member|mode
name|GimpPixelFetcherEdgeMode
name|mode
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|tile
name|GimpTile
modifier|*
name|tile
decl_stmt|;
DECL|member|tile_dirty
name|gboolean
name|tile_dirty
decl_stmt|;
DECL|member|shadow
name|gboolean
name|shadow
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|guchar
modifier|*
name|gimp_pixel_fetcher_provide_tile
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_pixel_fetcher_new:  * @drawable: the #GimpDrawable the new region will be attached to.  * @shadow:   a #gboolean indicating whether the region is attached to  *            the shadow tiles or the real %drawable tiles.  *  * Initialize a pixel region from the drawable.  *  * Return value: a pointer to a #GimpPixelRgn structure (or NULL).  **/
end_comment

begin_function
name|GimpPixelFetcher
modifier|*
DECL|function|gimp_pixel_fetcher_new (GimpDrawable * drawable,gboolean shadow)
name|gimp_pixel_fetcher_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|shadow
parameter_list|)
block|{
name|GimpPixelFetcher
modifier|*
name|pf
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|drawable
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
operator|&&
name|height
operator|>
literal|0
operator|&&
name|bpp
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pf
operator|=
name|g_new0
argument_list|(
name|GimpPixelFetcher
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|pf
operator|->
name|sel_x1
argument_list|,
operator|&
name|pf
operator|->
name|sel_y1
argument_list|,
operator|&
name|pf
operator|->
name|sel_x2
argument_list|,
operator|&
name|pf
operator|->
name|sel_y2
argument_list|)
expr_stmt|;
name|pf
operator|->
name|col
operator|=
operator|-
literal|1
expr_stmt|;
name|pf
operator|->
name|row
operator|=
operator|-
literal|1
expr_stmt|;
name|pf
operator|->
name|img_width
operator|=
name|width
expr_stmt|;
name|pf
operator|->
name|img_height
operator|=
name|height
expr_stmt|;
name|pf
operator|->
name|img_bpp
operator|=
name|bpp
expr_stmt|;
name|pf
operator|->
name|tile_width
operator|=
name|gimp_tile_width
argument_list|()
expr_stmt|;
name|pf
operator|->
name|tile_height
operator|=
name|gimp_tile_height
argument_list|()
expr_stmt|;
name|pf
operator|->
name|bg_color
index|[
literal|0
index|]
operator|=
literal|0
expr_stmt|;
name|pf
operator|->
name|bg_color
index|[
literal|1
index|]
operator|=
literal|0
expr_stmt|;
name|pf
operator|->
name|bg_color
index|[
literal|2
index|]
operator|=
literal|0
expr_stmt|;
name|pf
operator|->
name|bg_color
index|[
literal|3
index|]
operator|=
literal|255
expr_stmt|;
name|pf
operator|->
name|mode
operator|=
name|GIMP_PIXEL_FETCHER_EDGE_NONE
expr_stmt|;
name|pf
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|pf
operator|->
name|tile
operator|=
name|NULL
expr_stmt|;
name|pf
operator|->
name|tile_dirty
operator|=
name|FALSE
expr_stmt|;
name|pf
operator|->
name|shadow
operator|=
name|shadow
expr_stmt|;
return|return
name|pf
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pixel_fetcher_destroy:  * @pf: a pointer to a previously initialized #GimpPixelFetcher.  *  * Close a previously initializd pixel region.  **/
end_comment

begin_function
name|void
DECL|function|gimp_pixel_fetcher_destroy (GimpPixelFetcher * pf)
name|gimp_pixel_fetcher_destroy
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|pf
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pf
operator|->
name|tile
condition|)
name|gimp_tile_unref
argument_list|(
name|pf
operator|->
name|tile
argument_list|,
name|pf
operator|->
name|tile_dirty
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pf
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_pixel_fetcher_set_edge_mode:  * @pf:   a pointer to a previously initialized #GimpPixelFetcher.  * @mode: the new edge mode from #GimpPixelFetcherEdgeMode.  *  * Change the edage mode of a previously initialized pixel region.  **/
end_comment

begin_function
name|void
DECL|function|gimp_pixel_fetcher_set_edge_mode (GimpPixelFetcher * pf,GimpPixelFetcherEdgeMode mode)
name|gimp_pixel_fetcher_set_edge_mode
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|,
name|GimpPixelFetcherEdgeMode
name|mode
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|pf
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|pf
operator|->
name|mode
operator|=
name|mode
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_pixel_fetcher_set_bg_color:  * @pf:    a pointer to a previously initialized #GimpPixelFetcher.  * @color: the color to be used as bg color.  *  * Change the background color of a previously initialized pixel region.  **/
end_comment

begin_function
name|void
DECL|function|gimp_pixel_fetcher_set_bg_color (GimpPixelFetcher * pf,const GimpRGB * color)
name|gimp_pixel_fetcher_set_bg_color
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|pf
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|pf
operator|->
name|img_bpp
condition|)
block|{
case|case
literal|2
case|:
name|pf
operator|->
name|bg_color
index|[
literal|1
index|]
operator|=
literal|255
expr_stmt|;
case|case
literal|1
case|:
name|pf
operator|->
name|bg_color
index|[
literal|0
index|]
operator|=
name|gimp_rgb_luminance_uchar
argument_list|(
name|color
argument_list|)
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|pf
operator|->
name|bg_color
index|[
literal|3
index|]
operator|=
literal|255
expr_stmt|;
case|case
literal|3
case|:
name|gimp_rgb_get_uchar
argument_list|(
name|color
argument_list|,
name|pf
operator|->
name|bg_color
argument_list|,
name|pf
operator|->
name|bg_color
operator|+
literal|1
argument_list|,
name|pf
operator|->
name|bg_color
operator|+
literal|2
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_pixel_fetcher_get_pixel:  * @pf:    a pointer to a previously initialized #GimpPixelFetcher.  * @x:     the x coordinate of the pixel to get.  * @y:     the y coordinate of the pixel to get.  * @pixel: the memory location where to return the pixel.  *  * Get a pixel from the pixel region.  **/
end_comment

begin_function
name|void
DECL|function|gimp_pixel_fetcher_get_pixel (GimpPixelFetcher * pf,gint x,gint y,guchar * pixel)
name|gimp_pixel_fetcher_get_pixel
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guchar
modifier|*
name|pixel
parameter_list|)
block|{
name|guchar
modifier|*
name|p
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|pf
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|pixel
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pf
operator|->
name|mode
operator|==
name|GIMP_PIXEL_FETCHER_EDGE_NONE
operator|&&
operator|(
name|x
operator|<
name|pf
operator|->
name|sel_x1
operator|||
name|x
operator|>=
name|pf
operator|->
name|sel_x2
operator|||
name|y
operator|<
name|pf
operator|->
name|sel_y1
operator|||
name|y
operator|>=
name|pf
operator|->
name|sel_y2
operator|)
condition|)
block|{
return|return;
block|}
if|if
condition|(
name|x
operator|<
literal|0
operator|||
name|x
operator|>=
name|pf
operator|->
name|img_width
operator|||
name|y
operator|<
literal|0
operator|||
name|y
operator|>=
name|pf
operator|->
name|img_height
condition|)
block|{
switch|switch
condition|(
name|pf
operator|->
name|mode
condition|)
block|{
case|case
name|GIMP_PIXEL_FETCHER_EDGE_WRAP
case|:
if|if
condition|(
name|x
operator|<
literal|0
operator|||
name|x
operator|>=
name|pf
operator|->
name|img_width
condition|)
block|{
name|x
operator|%=
name|pf
operator|->
name|img_width
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0
condition|)
name|x
operator|+=
name|pf
operator|->
name|img_width
expr_stmt|;
block|}
if|if
condition|(
name|y
operator|<
literal|0
operator|||
name|y
operator|>=
name|pf
operator|->
name|img_height
condition|)
block|{
name|y
operator|%=
name|pf
operator|->
name|img_height
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0
condition|)
name|y
operator|+=
name|pf
operator|->
name|img_height
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PIXEL_FETCHER_EDGE_SMEAR
case|:
name|x
operator|=
name|CLAMP
argument_list|(
name|x
argument_list|,
literal|0
argument_list|,
name|pf
operator|->
name|img_width
operator|-
literal|1
argument_list|)
expr_stmt|;
name|y
operator|=
name|CLAMP
argument_list|(
name|y
argument_list|,
literal|0
argument_list|,
name|pf
operator|->
name|img_height
operator|-
literal|1
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PIXEL_FETCHER_EDGE_BLACK
case|:
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|pf
operator|->
name|img_bpp
condition|;
name|i
operator|++
control|)
name|pixel
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
return|return;
case|case
name|GIMP_PIXEL_FETCHER_EDGE_BACKGROUND
case|:
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|pf
operator|->
name|img_bpp
condition|;
name|i
operator|++
control|)
name|pixel
index|[
name|i
index|]
operator|=
name|pf
operator|->
name|bg_color
index|[
name|i
index|]
expr_stmt|;
return|return;
default|default:
return|return;
block|}
block|}
name|p
operator|=
name|gimp_pixel_fetcher_provide_tile
argument_list|(
name|pf
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|i
operator|=
name|pf
operator|->
name|img_bpp
expr_stmt|;
do|do
block|{
operator|*
name|pixel
operator|++
operator|=
operator|*
name|p
operator|++
expr_stmt|;
block|}
do|while
condition|(
operator|--
name|i
condition|)
do|;
block|}
end_function

begin_comment
comment|/**  * gimp_pixel_fetcher_put_pixel:  * @pf:    a pointer to a previously initialized #GimpPixelFetcher.  * @x:     the x coordinate of the pixel to set.  * @y:     the y coordinate of the pixel to set.  * @pixel: the pixel to set.  *  * Set a pixel in the pixel region.  **/
end_comment

begin_function
name|void
DECL|function|gimp_pixel_fetcher_put_pixel (GimpPixelFetcher * pf,gint x,gint y,const guchar * pixel)
name|gimp_pixel_fetcher_put_pixel
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|guchar
modifier|*
name|pixel
parameter_list|)
block|{
name|guchar
modifier|*
name|p
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|pf
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|pixel
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
name|pf
operator|->
name|sel_x1
operator|||
name|x
operator|>=
name|pf
operator|->
name|sel_x2
operator|||
name|y
operator|<
name|pf
operator|->
name|sel_y1
operator|||
name|y
operator|>=
name|pf
operator|->
name|sel_y2
condition|)
block|{
return|return;
block|}
name|p
operator|=
name|gimp_pixel_fetcher_provide_tile
argument_list|(
name|pf
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|i
operator|=
name|pf
operator|->
name|img_bpp
expr_stmt|;
do|do
block|{
operator|*
name|p
operator|++
operator|=
operator|*
name|pixel
operator|++
expr_stmt|;
block|}
do|while
condition|(
operator|--
name|i
condition|)
do|;
name|pf
operator|->
name|tile_dirty
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|guchar
modifier|*
DECL|function|gimp_pixel_fetcher_provide_tile (GimpPixelFetcher * pf,gint x,gint y)
name|gimp_pixel_fetcher_provide_tile
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|gint
name|col
decl_stmt|,
name|row
decl_stmt|;
name|gint
name|coloff
decl_stmt|,
name|rowoff
decl_stmt|;
name|col
operator|=
name|x
operator|/
name|pf
operator|->
name|tile_width
expr_stmt|;
name|coloff
operator|=
name|x
operator|%
name|pf
operator|->
name|tile_width
expr_stmt|;
name|row
operator|=
name|y
operator|/
name|pf
operator|->
name|tile_height
expr_stmt|;
name|rowoff
operator|=
name|y
operator|%
name|pf
operator|->
name|tile_height
expr_stmt|;
if|if
condition|(
operator|(
name|col
operator|!=
name|pf
operator|->
name|col
operator|)
operator|||
operator|(
name|row
operator|!=
name|pf
operator|->
name|row
operator|)
operator|||
operator|(
name|pf
operator|->
name|tile
operator|==
name|NULL
operator|)
condition|)
block|{
if|if
condition|(
name|pf
operator|->
name|tile
operator|!=
name|NULL
condition|)
name|gimp_tile_unref
argument_list|(
name|pf
operator|->
name|tile
argument_list|,
name|pf
operator|->
name|tile_dirty
argument_list|)
expr_stmt|;
name|pf
operator|->
name|tile
operator|=
name|gimp_drawable_get_tile
argument_list|(
name|pf
operator|->
name|drawable
argument_list|,
name|pf
operator|->
name|shadow
argument_list|,
name|row
argument_list|,
name|col
argument_list|)
expr_stmt|;
name|pf
operator|->
name|tile_dirty
operator|=
name|FALSE
expr_stmt|;
name|gimp_tile_ref
argument_list|(
name|pf
operator|->
name|tile
argument_list|)
expr_stmt|;
name|pf
operator|->
name|col
operator|=
name|col
expr_stmt|;
name|pf
operator|->
name|row
operator|=
name|row
expr_stmt|;
block|}
return|return
name|pf
operator|->
name|tile
operator|->
name|data
operator|+
name|pf
operator|->
name|img_bpp
operator|*
operator|(
name|pf
operator|->
name|tile
operator|->
name|ewidth
operator|*
name|rowoff
operator|+
name|coloff
operator|)
return|;
block|}
end_function

end_unit

