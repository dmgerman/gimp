begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"brushes.h"
end_include

begin_include
include|#
directive|include
file|"colormaps.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"gradient.h"
end_include

begin_include
include|#
directive|include
file|"palette.h"
end_include

begin_include
include|#
directive|include
file|"patterns.h"
end_include

begin_include
include|#
directive|include
file|"plug_in.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"tile_swap.h"
end_include

begin_decl_stmt
DECL|variable|g_visual
name|GdkVisual
modifier|*
name|g_visual
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|g_cmap
name|GdkColormap
modifier|*
name|g_cmap
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|g_black_pixel
name|gulong
name|g_black_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|g_gray_pixel
name|gulong
name|g_gray_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|g_white_pixel
name|gulong
name|g_white_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|g_color_pixel
name|gulong
name|g_color_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|g_normal_guide_pixel
name|gulong
name|g_normal_guide_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|g_active_guide_pixel
name|gulong
name|g_active_guide_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|foreground_pixel
name|gulong
name|foreground_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|background_pixel
name|gulong
name|background_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|old_color_pixel
name|gulong
name|old_color_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|new_color_pixel
name|gulong
name|new_color_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|marching_ants_pixels
name|gulong
name|marching_ants_pixels
index|[
literal|8
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|red_ordered_dither
name|GtkDitherInfo
modifier|*
name|red_ordered_dither
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|green_ordered_dither
name|GtkDitherInfo
modifier|*
name|green_ordered_dither
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|blue_ordered_dither
name|GtkDitherInfo
modifier|*
name|blue_ordered_dither
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gray_ordered_dither
name|GtkDitherInfo
modifier|*
name|gray_ordered_dither
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ordered_dither_matrix
name|guchar
modifier|*
modifier|*
modifier|*
name|ordered_dither_matrix
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  These arrays are calculated for quick 24 bit to 16 color conversions  */
end_comment

begin_decl_stmt
DECL|variable|g_lookup_red
name|gulong
modifier|*
name|g_lookup_red
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|g_lookup_green
name|gulong
modifier|*
name|g_lookup_green
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|g_lookup_blue
name|gulong
modifier|*
name|g_lookup_blue
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_pixel_vals
name|gulong
modifier|*
name|color_pixel_vals
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gray_pixel_vals
name|gulong
modifier|*
name|gray_pixel_vals
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|reserved_entries
specifier|static
name|int
name|reserved_entries
init|=
literal|10
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|reserved_entries
comment|/* extra colors aside from color cube */
end_comment

begin_decl_stmt
DECL|variable|reserved_pixels
specifier|static
name|gulong
modifier|*
name|reserved_pixels
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|set_app_colors ()
name|set_app_colors
parameter_list|()
block|{
name|int
name|i
decl_stmt|;
if|if
condition|(
name|g_visual
operator|->
name|depth
operator|==
literal|8
condition|)
block|{
name|g_black_pixel
operator|=
name|reserved_pixels
index|[
literal|0
index|]
expr_stmt|;
name|g_gray_pixel
operator|=
name|reserved_pixels
index|[
literal|1
index|]
expr_stmt|;
name|g_white_pixel
operator|=
name|reserved_pixels
index|[
literal|2
index|]
expr_stmt|;
name|g_color_pixel
operator|=
name|reserved_pixels
index|[
literal|3
index|]
expr_stmt|;
name|g_normal_guide_pixel
operator|=
name|reserved_pixels
index|[
literal|4
index|]
expr_stmt|;
name|g_active_guide_pixel
operator|=
name|reserved_pixels
index|[
literal|5
index|]
expr_stmt|;
name|foreground_pixel
operator|=
name|reserved_pixels
index|[
literal|6
index|]
expr_stmt|;
name|background_pixel
operator|=
name|reserved_pixels
index|[
literal|7
index|]
expr_stmt|;
name|old_color_pixel
operator|=
name|reserved_pixels
index|[
literal|8
index|]
expr_stmt|;
name|new_color_pixel
operator|=
name|reserved_pixels
index|[
literal|9
index|]
expr_stmt|;
block|}
else|else
block|{
name|cycled_marching_ants
operator|=
name|FALSE
expr_stmt|;
block|}
name|store_color
argument_list|(
operator|&
name|g_black_pixel
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|store_color
argument_list|(
operator|&
name|g_gray_pixel
argument_list|,
literal|127
argument_list|,
literal|127
argument_list|,
literal|127
argument_list|)
expr_stmt|;
name|store_color
argument_list|(
operator|&
name|g_white_pixel
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|store_color
argument_list|(
operator|&
name|g_color_pixel
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|store_color
argument_list|(
operator|&
name|g_normal_guide_pixel
argument_list|,
literal|0
argument_list|,
literal|127
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|store_color
argument_list|(
operator|&
name|g_active_guide_pixel
argument_list|,
literal|255
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|store_color
argument_list|(
operator|&
name|foreground_pixel
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|store_color
argument_list|(
operator|&
name|background_pixel
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|store_color
argument_list|(
operator|&
name|old_color_pixel
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|store_color
argument_list|(
operator|&
name|new_color_pixel
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|)
expr_stmt|;
comment|/* marching ants pixels--if enabled */
if|if
condition|(
name|cycled_marching_ants
condition|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|8
condition|;
name|i
operator|++
control|)
block|{
name|marching_ants_pixels
index|[
name|i
index|]
operator|=
name|reserved_pixels
index|[
name|i
operator|+
name|reserved_entries
operator|-
literal|8
index|]
expr_stmt|;
if|if
condition|(
name|i
operator|<
literal|4
condition|)
name|store_color
argument_list|(
operator|&
name|marching_ants_pixels
index|[
name|i
index|]
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
else|else
name|store_color
argument_list|(
operator|&
name|marching_ants_pixels
index|[
name|i
index|]
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|unsigned
name|int
DECL|function|gamma_correct (int intensity,double gamma)
name|gamma_correct
parameter_list|(
name|int
name|intensity
parameter_list|,
name|double
name|gamma
parameter_list|)
block|{
name|unsigned
name|int
name|val
decl_stmt|;
name|double
name|ind
decl_stmt|;
name|double
name|one_over_gamma
decl_stmt|;
if|if
condition|(
name|gamma
operator|!=
literal|0.0
condition|)
name|one_over_gamma
operator|=
literal|1.0
operator|/
name|gamma
expr_stmt|;
else|else
name|one_over_gamma
operator|=
literal|1.0
expr_stmt|;
name|ind
operator|=
operator|(
name|double
operator|)
name|intensity
operator|/
literal|256.0
expr_stmt|;
name|val
operator|=
call|(
name|int
call|)
argument_list|(
literal|256
operator|*
name|pow
argument_list|(
name|ind
argument_list|,
name|one_over_gamma
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|val
return|;
block|}
end_function

begin_comment
comment|/*************************************************************************/
end_comment

begin_function
name|gulong
DECL|function|get_color (int red,int green,int blue)
name|get_color
parameter_list|(
name|int
name|red
parameter_list|,
name|int
name|green
parameter_list|,
name|int
name|blue
parameter_list|)
block|{
name|gulong
name|pixel
decl_stmt|;
if|if
condition|(
name|g_visual
operator|->
name|depth
operator|==
literal|8
condition|)
name|pixel
operator|=
name|color_pixel_vals
index|[
operator|(
name|red_ordered_dither
index|[
name|red
index|]
operator|.
name|s
index|[
literal|1
index|]
operator|+
name|green_ordered_dither
index|[
name|green
index|]
operator|.
name|s
index|[
literal|1
index|]
operator|+
name|blue_ordered_dither
index|[
name|blue
index|]
operator|.
name|s
index|[
literal|1
index|]
operator|)
index|]
expr_stmt|;
else|else
name|store_color
argument_list|(
operator|&
name|pixel
argument_list|,
name|red
argument_list|,
name|green
argument_list|,
name|blue
argument_list|)
expr_stmt|;
return|return
name|pixel
return|;
block|}
end_function

begin_function
name|void
DECL|function|store_color (gulong * pixel_ptr,int red,int green,int blue)
name|store_color
parameter_list|(
name|gulong
modifier|*
name|pixel_ptr
parameter_list|,
name|int
name|red
parameter_list|,
name|int
name|green
parameter_list|,
name|int
name|blue
parameter_list|)
block|{
name|GdkColor
name|col
decl_stmt|;
name|red
operator|=
name|gamma_correct
argument_list|(
name|red
argument_list|,
name|gamma_val
argument_list|)
expr_stmt|;
name|green
operator|=
name|gamma_correct
argument_list|(
name|green
argument_list|,
name|gamma_val
argument_list|)
expr_stmt|;
name|blue
operator|=
name|gamma_correct
argument_list|(
name|blue
argument_list|,
name|gamma_val
argument_list|)
expr_stmt|;
name|col
operator|.
name|red
operator|=
name|red
operator|*
operator|(
literal|65535
operator|/
literal|255
operator|)
expr_stmt|;
name|col
operator|.
name|green
operator|=
name|green
operator|*
operator|(
literal|65535
operator|/
literal|255
operator|)
expr_stmt|;
name|col
operator|.
name|blue
operator|=
name|blue
operator|*
operator|(
literal|65535
operator|/
literal|255
operator|)
expr_stmt|;
name|col
operator|.
name|pixel
operator|=
operator|*
name|pixel_ptr
expr_stmt|;
if|if
condition|(
name|g_visual
operator|->
name|depth
operator|==
literal|8
condition|)
name|gdk_color_change
argument_list|(
name|g_cmap
argument_list|,
operator|&
name|col
argument_list|)
expr_stmt|;
else|else
name|gdk_color_alloc
argument_list|(
name|g_cmap
argument_list|,
operator|&
name|col
argument_list|)
expr_stmt|;
operator|*
name|pixel_ptr
operator|=
name|col
operator|.
name|pixel
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|get_standard_colormaps ()
name|get_standard_colormaps
parameter_list|()
block|{
name|GtkPreviewInfo
modifier|*
name|info
decl_stmt|;
if|if
condition|(
name|cycled_marching_ants
condition|)
name|reserved_entries
operator|+=
literal|8
expr_stmt|;
name|gtk_preview_set_gamma
argument_list|(
name|gamma_val
argument_list|)
expr_stmt|;
name|gtk_preview_set_color_cube
argument_list|(
name|color_cube_shades
index|[
literal|0
index|]
argument_list|,
name|color_cube_shades
index|[
literal|1
index|]
argument_list|,
name|color_cube_shades
index|[
literal|2
index|]
argument_list|,
name|color_cube_shades
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|gtk_preview_set_install_cmap
argument_list|(
name|install_cmap
argument_list|)
expr_stmt|;
name|gtk_preview_set_reserved
argument_list|(
name|reserved_entries
argument_list|)
expr_stmt|;
name|gtk_widget_set_default_visual
argument_list|(
name|gtk_preview_get_visual
argument_list|()
argument_list|)
expr_stmt|;
name|gtk_widget_set_default_colormap
argument_list|(
name|gtk_preview_get_cmap
argument_list|()
argument_list|)
expr_stmt|;
name|info
operator|=
name|gtk_preview_get_info
argument_list|()
expr_stmt|;
name|g_visual
operator|=
name|info
operator|->
name|visual
expr_stmt|;
if|if
condition|(
name|g_visual
operator|->
name|depth
operator|==
literal|8
operator|&&
name|info
operator|->
name|reserved_pixels
operator|==
name|NULL
condition|)
block|{
name|g_print
argument_list|(
literal|"GIMP cannot get enough colormaps to boot.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"Try exiting other color intensive applications.\n"
argument_list|)
expr_stmt|;
name|swapping_free
argument_list|()
expr_stmt|;
name|brushes_free
argument_list|()
expr_stmt|;
name|patterns_free
argument_list|()
expr_stmt|;
name|palettes_free
argument_list|()
expr_stmt|;
name|gradients_free
argument_list|()
expr_stmt|;
name|palette_free
argument_list|()
expr_stmt|;
name|procedural_db_free
argument_list|()
expr_stmt|;
name|plug_in_kill
argument_list|()
expr_stmt|;
name|tile_swap_exit
argument_list|()
expr_stmt|;
name|gtk_exit
argument_list|(
literal|0
argument_list|)
expr_stmt|;
block|}
name|g_cmap
operator|=
name|info
operator|->
name|cmap
expr_stmt|;
name|color_pixel_vals
operator|=
name|info
operator|->
name|color_pixels
expr_stmt|;
name|gray_pixel_vals
operator|=
name|info
operator|->
name|gray_pixels
expr_stmt|;
name|reserved_pixels
operator|=
name|info
operator|->
name|reserved_pixels
expr_stmt|;
name|red_ordered_dither
operator|=
name|info
operator|->
name|dither_red
expr_stmt|;
name|green_ordered_dither
operator|=
name|info
operator|->
name|dither_green
expr_stmt|;
name|blue_ordered_dither
operator|=
name|info
operator|->
name|dither_blue
expr_stmt|;
name|gray_ordered_dither
operator|=
name|info
operator|->
name|dither_gray
expr_stmt|;
name|ordered_dither_matrix
operator|=
name|info
operator|->
name|dither_matrix
expr_stmt|;
name|g_lookup_red
operator|=
name|info
operator|->
name|lookup_red
expr_stmt|;
name|g_lookup_green
operator|=
name|info
operator|->
name|lookup_green
expr_stmt|;
name|g_lookup_blue
operator|=
name|info
operator|->
name|lookup_blue
expr_stmt|;
name|set_app_colors
argument_list|()
expr_stmt|;
block|}
end_function

end_unit

