begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__COLORMAPS_H__
end_ifndef

begin_define
DECL|macro|__COLORMAPS_H__
define|#
directive|define
name|__COLORMAPS_H__
end_define

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_comment
comment|/* For the image types  */
end_comment

begin_comment
comment|/*  This is a macro for arranging the red, green, and blue components into  *  a value acceptable to the target X server  */
end_comment

begin_define
DECL|macro|COLOR_COMPOSE (r,g,b)
define|#
directive|define
name|COLOR_COMPOSE
parameter_list|(
name|r
parameter_list|,
name|g
parameter_list|,
name|b
parameter_list|)
value|(lookup_red [r] | lookup_green [g] | lookup_blue [b])
end_define

begin_decl_stmt
specifier|extern
name|GdkVisual
modifier|*
name|g_visual
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GdkColormap
modifier|*
name|g_cmap
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Pixel values of black and white  */
end_comment

begin_decl_stmt
specifier|extern
name|gulong
name|g_black_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gulong
name|g_gray_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gulong
name|g_white_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gulong
name|g_color_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gulong
name|g_normal_guide_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gulong
name|g_active_guide_pixel
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Foreground and Background colors  */
end_comment

begin_decl_stmt
specifier|extern
name|gulong
name|foreground_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gulong
name|background_pixel
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Old and New colors  */
end_comment

begin_decl_stmt
specifier|extern
name|gulong
name|old_color_pixel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gulong
name|new_color_pixel
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Colormap entries reserved for color cycled marching ants--optional  */
end_comment

begin_decl_stmt
specifier|extern
name|gulong
name|marching_ants_pixels
index|[
literal|8
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkDitherInfo
modifier|*
name|red_ordered_dither
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkDitherInfo
modifier|*
name|green_ordered_dither
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkDitherInfo
modifier|*
name|blue_ordered_dither
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkDitherInfo
modifier|*
name|gray_ordered_dither
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
modifier|*
modifier|*
name|ordered_dither_matrix
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gulong
modifier|*
name|g_lookup_red
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gulong
modifier|*
name|g_lookup_green
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gulong
modifier|*
name|g_lookup_blue
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gulong
modifier|*
name|color_pixel_vals
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gulong
modifier|*
name|gray_pixel_vals
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gulong
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|store_color
parameter_list|(
name|gulong
modifier|*
name|pixel
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|get_standard_colormaps
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __COLORMAPS_H__  */
end_comment

end_unit

