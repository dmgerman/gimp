begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmisc.c  * Contains all kinds of miscellaneous routines factored out from different  * plug-ins. They stay here until their API has crystalized a bit and we can  * put them into the file where they belong (Maurits Rijk   *<lpeek.mrijk@consunet.nl> if you want to blame someone for this mess)  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

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

begin_function
name|GimpPixelFetcher
modifier|*
DECL|function|gimp_pixel_fetcher_new (GimpDrawable * drawable)
name|gimp_pixel_fetcher_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpPixelFetcher
modifier|*
name|pf
decl_stmt|;
name|pf
operator|=
name|g_new
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
name|gimp_drawable_width
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|pf
operator|->
name|img_height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|pf
operator|->
name|img_bpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|pf
operator|->
name|img_has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
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
literal|0
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
return|return
name|pf
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_pixel_fetcher_set_bg_color (GimpPixelFetcher * pf)
name|gimp_pixel_fetcher_set_bg_color
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|)
block|{
name|GimpRGB
name|background
decl_stmt|;
name|gimp_palette_get_background
argument_list|(
operator|&
name|background
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
literal|1
case|:
case|case
literal|2
case|:
name|pf
operator|->
name|bg_color
index|[
literal|0
index|]
operator|=
name|gimp_rgb_intensity_uchar
argument_list|(
operator|&
name|background
argument_list|)
expr_stmt|;
break|break;
case|case
literal|3
case|:
case|case
literal|4
case|:
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|background
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
name|guchar
modifier|*
name|p
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
operator|(
name|x
operator|<
name|pf
operator|->
name|sel_x1
operator|)
operator|||
operator|(
name|x
operator|>=
name|pf
operator|->
name|sel_x2
operator|)
operator|||
operator|(
name|y
operator|<
name|pf
operator|->
name|sel_y1
operator|)
operator|||
operator|(
name|y
operator|>=
name|pf
operator|->
name|sel_y2
operator|)
condition|)
block|{
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
block|}
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
name|FALSE
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
name|FALSE
argument_list|,
name|row
argument_list|,
name|col
argument_list|)
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
name|p
operator|=
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
expr_stmt|;
for|for
control|(
name|i
operator|=
name|pf
operator|->
name|img_bpp
init|;
name|i
condition|;
name|i
operator|--
control|)
operator|*
name|pixel
operator|++
operator|=
operator|*
name|p
operator|++
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_pixel_fetcher_get_pixel2 (GimpPixelFetcher * pf,gint x,gint y,gint wrapmode,guchar * pixel)
name|gimp_pixel_fetcher_get_pixel2
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
name|gint
name|wrapmode
parameter_list|,
name|guchar
modifier|*
name|pixel
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
name|guchar
modifier|*
name|p
decl_stmt|;
name|gint
name|i
decl_stmt|;
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
switch|switch
condition|(
name|wrapmode
condition|)
block|{
case|case
name|PIXEL_WRAP
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
name|PIXEL_SMEAR
case|:
if|if
condition|(
name|x
operator|<
literal|0
condition|)
name|x
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|x
operator|>=
name|pf
operator|->
name|img_width
condition|)
name|x
operator|=
name|pf
operator|->
name|img_width
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0
condition|)
name|y
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|y
operator|>=
name|pf
operator|->
name|img_height
condition|)
name|y
operator|=
name|pf
operator|->
name|img_height
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|PIXEL_BLACK
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
block|}
break|break;
default|default:
return|return;
block|}
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
name|FALSE
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
name|FALSE
argument_list|,
name|row
argument_list|,
name|col
argument_list|)
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
name|p
operator|=
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
expr_stmt|;
for|for
control|(
name|i
operator|=
name|pf
operator|->
name|img_bpp
init|;
name|i
condition|;
name|i
operator|--
control|)
operator|*
name|pixel
operator|++
operator|=
operator|*
name|p
operator|++
expr_stmt|;
block|}
end_function

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
name|FALSE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_get_bg_guchar (GimpDrawable * drawable,gboolean transparent,guchar * bg)
name|gimp_get_bg_guchar
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|transparent
parameter_list|,
name|guchar
modifier|*
name|bg
parameter_list|)
block|{
name|GimpRGB
name|background
decl_stmt|;
name|gimp_palette_get_background
argument_list|(
operator|&
name|background
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB_IMAGE
case|:
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|background
argument_list|,
operator|&
name|bg
index|[
literal|0
index|]
argument_list|,
operator|&
name|bg
index|[
literal|1
index|]
argument_list|,
operator|&
name|bg
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|bg
index|[
literal|3
index|]
operator|=
literal|255
expr_stmt|;
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|background
argument_list|,
operator|&
name|bg
index|[
literal|0
index|]
argument_list|,
operator|&
name|bg
index|[
literal|1
index|]
argument_list|,
operator|&
name|bg
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|bg
index|[
literal|3
index|]
operator|=
name|transparent
condition|?
literal|0
else|:
literal|255
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY_IMAGE
case|:
name|bg
index|[
literal|0
index|]
operator|=
name|gimp_rgb_intensity_uchar
argument_list|(
operator|&
name|background
argument_list|)
expr_stmt|;
name|bg
index|[
literal|1
index|]
operator|=
literal|255
expr_stmt|;
break|break;
case|case
name|GIMP_GRAYA_IMAGE
case|:
name|bg
index|[
literal|0
index|]
operator|=
name|gimp_rgb_intensity_uchar
argument_list|(
operator|&
name|background
argument_list|)
expr_stmt|;
name|bg
index|[
literal|1
index|]
operator|=
name|transparent
condition|?
literal|0
else|:
literal|255
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_decl_stmt
DECL|variable|_timer
name|GTimer
modifier|*
name|_timer
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_timer_start (void)
name|gimp_timer_start
parameter_list|(
name|void
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
operator|!
name|_timer
argument_list|)
expr_stmt|;
name|_timer
operator|=
name|g_timer_new
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_timer_stop (void)
name|gimp_timer_stop
parameter_list|(
name|void
parameter_list|)
block|{
name|double
name|elapsed
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|_timer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_timer_stop
argument_list|(
name|_timer
argument_list|)
expr_stmt|;
name|elapsed
operator|=
name|g_timer_elapsed
argument_list|(
name|_timer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_timer_destroy
argument_list|(
name|_timer
argument_list|)
expr_stmt|;
name|_timer
operator|=
name|NULL
expr_stmt|;
name|g_print
argument_list|(
literal|"%ld seconds\n"
argument_list|,
name|elapsed
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rgn_render_row (guchar * src,guchar * dest,gint col,gint bpp,GimpRgnFunc2 func,gpointer data)
name|gimp_rgn_render_row
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|col
parameter_list|,
comment|/* row width in pixels */
name|gint
name|bpp
parameter_list|,
name|GimpRgnFunc2
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
while|while
condition|(
name|col
operator|--
condition|)
block|{
name|func
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|bpp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|src
operator|+=
name|bpp
expr_stmt|;
name|dest
operator|+=
name|bpp
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rgn_render_region (const GimpPixelRgn * srcPR,const GimpPixelRgn * destPR,GimpRgnFunc2 func,gpointer data)
name|gimp_rgn_render_region
parameter_list|(
specifier|const
name|GimpPixelRgn
modifier|*
name|srcPR
parameter_list|,
specifier|const
name|GimpPixelRgn
modifier|*
name|destPR
parameter_list|,
name|GimpRgnFunc2
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gint
name|row
decl_stmt|;
name|guchar
modifier|*
name|src
init|=
name|srcPR
operator|->
name|data
decl_stmt|;
name|guchar
modifier|*
name|dest
init|=
name|destPR
operator|->
name|data
decl_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|srcPR
operator|->
name|h
condition|;
name|row
operator|++
control|)
block|{
name|gimp_rgn_render_row
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|srcPR
operator|->
name|w
argument_list|,
name|srcPR
operator|->
name|bpp
argument_list|,
name|func
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|src
operator|+=
name|srcPR
operator|->
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|destPR
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgn_iterate1 (GimpDrawable * drawable,GimpRunMode run_mode,GimpRgnFunc1 func,gpointer data)
name|gimp_rgn_iterate1
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GimpRgnFunc1
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPixelRgn
name|srcPR
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
name|gpointer
name|pr
decl_stmt|;
name|gint
name|total_area
decl_stmt|,
name|area_so_far
decl_stmt|;
name|gint
name|progress_skip
decl_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
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
name|total_area
operator|=
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
operator|(
name|y2
operator|-
name|y1
operator|)
expr_stmt|;
name|area_so_far
operator|=
literal|0
expr_stmt|;
name|progress_skip
operator|=
literal|0
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
argument_list|,
operator|&
name|srcPR
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|guchar
modifier|*
name|src
init|=
name|srcPR
operator|.
name|data
decl_stmt|;
name|gint
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|srcPR
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|gint
name|x
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|srcPR
operator|.
name|w
condition|;
name|x
operator|++
control|)
block|{
name|func
argument_list|(
name|s
argument_list|,
name|srcPR
operator|.
name|bpp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|s
operator|+=
name|srcPR
operator|.
name|bpp
expr_stmt|;
block|}
name|src
operator|+=
name|srcPR
operator|.
name|rowstride
expr_stmt|;
block|}
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
block|{
name|area_so_far
operator|+=
name|srcPR
operator|.
name|w
operator|*
name|srcPR
operator|.
name|h
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|progress_skip
operator|++
operator|)
operator|%
literal|10
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|area_so_far
operator|/
operator|(
name|double
operator|)
name|total_area
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgn_iterate2 (GimpDrawable * drawable,GimpRunMode run_mode,GimpRgnFunc2 func,gpointer data)
name|gimp_rgn_iterate2
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GimpRgnFunc2
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPixelRgn
name|srcPR
decl_stmt|,
name|destPR
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
name|gpointer
name|pr
decl_stmt|;
name|gint
name|total_area
decl_stmt|,
name|area_so_far
decl_stmt|;
name|gint
name|progress_skip
decl_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
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
name|total_area
operator|=
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
operator|(
name|y2
operator|-
name|y1
operator|)
expr_stmt|;
name|area_so_far
operator|=
literal|0
expr_stmt|;
name|progress_skip
operator|=
literal|0
expr_stmt|;
comment|/* Initialize the pixel regions. */
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|2
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|gimp_rgn_render_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|,
name|func
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
block|{
name|area_so_far
operator|+=
name|srcPR
operator|.
name|w
operator|*
name|srcPR
operator|.
name|h
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|progress_skip
operator|++
operator|)
operator|%
literal|10
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|area_so_far
operator|/
operator|(
name|double
operator|)
name|total_area
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  update the processed region  */
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

