begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpbrushlist.h"
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

begin_function_decl
specifier|static
name|void
name|make_color
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
parameter_list|,
name|int
name|readwrite
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|set_app_colors (void)
name|set_app_colors
parameter_list|(
name|void
parameter_list|)
block|{
name|cycled_marching_ants
operator|=
name|FALSE
expr_stmt|;
name|make_color
argument_list|(
operator|&
name|g_black_pixel
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|make_color
argument_list|(
operator|&
name|g_gray_pixel
argument_list|,
literal|127
argument_list|,
literal|127
argument_list|,
literal|127
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|make_color
argument_list|(
operator|&
name|g_white_pixel
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|make_color
argument_list|(
operator|&
name|g_color_pixel
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|make_color
argument_list|(
operator|&
name|g_normal_guide_pixel
argument_list|,
literal|0
argument_list|,
literal|127
argument_list|,
literal|255
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|make_color
argument_list|(
operator|&
name|g_active_guide_pixel
argument_list|,
literal|255
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|FALSE
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
block|}
end_function

begin_comment
comment|/* This probably doesn't belong here - RLL*/
end_comment

begin_comment
comment|/* static unsigned int gamma_correct (int intensity, double gamma) {   unsigned int val;   double ind;   double one_over_gamma;    if (gamma != 0.0)     one_over_gamma = 1.0 / gamma;   else     one_over_gamma = 1.0;    ind = (double) intensity / 256.0;   val = (int) (256 * pow (ind, one_over_gamma));    return val; } */
end_comment

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
return|return
name|gdk_rgb_xpixel_from_rgb
argument_list|(
operator|(
name|red
operator|<<
literal|16
operator|)
operator||
operator|(
name|green
operator|<<
literal|8
operator|)
operator||
name|blue
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|make_color (gulong * pixel_ptr,int red,int green,int blue,int readwrite)
name|make_color
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
parameter_list|,
name|int
name|readwrite
parameter_list|)
block|{
operator|*
name|pixel_ptr
operator|=
name|get_color
argument_list|(
name|red
argument_list|,
name|green
argument_list|,
name|blue
argument_list|)
expr_stmt|;
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
operator|*
name|pixel_ptr
operator|=
name|get_color
argument_list|(
name|red
argument_list|,
name|green
argument_list|,
name|blue
argument_list|)
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
name|g_cmap
operator|=
name|info
operator|->
name|cmap
expr_stmt|;
name|set_app_colors
argument_list|()
expr_stmt|;
block|}
end_function

end_unit

