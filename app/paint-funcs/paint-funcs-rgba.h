begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * gaussian_blur_region no longer does combination; arguments changed  *   -- scott@poverty.bloomington.in.us, 16Oct97  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PAINT_FUNCS_RGBA_H__
end_ifndef

begin_define
DECL|macro|__PAINT_FUNCS_RGBA_H__
define|#
directive|define
name|__PAINT_FUNCS_RGBA_H__
end_define

begin_include
include|#
directive|include
file|"paint_funcsP.h"
end_include

begin_function_decl
name|void
name|update_tile_rowhints_rgba
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|gint
name|ymin
parameter_list|,
name|gint
name|ymax
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Paint functions  */
end_comment

begin_function_decl
name|void
name|color_pixels_rgba
parameter_list|(
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|color
parameter_list|,
name|gint
name|w
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|blend_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|blend
parameter_list|,
name|gint
name|w
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|shade_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|color
parameter_list|,
name|gint
name|blend
parameter_list|,
name|gint
name|w
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|extract_alpha_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|w
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|darken_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|length
parameter_list|,
name|gint
name|bytes2
parameter_list|,
name|gint
name|has_alpha1
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|lighten_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|length
parameter_list|,
name|gint
name|bytes2
parameter_list|,
name|gint
name|has_alpha2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|hsv_only_pixels_rgba_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|guint
name|mode
parameter_list|,
name|guint
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_only_pixels_rgba_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|guint
name|mode
parameter_list|,
name|guint
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|multiply_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|length
parameter_list|,
name|gint
name|bytes2
parameter_list|,
name|gint
name|has_alpha2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|divide_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|length
parameter_list|,
name|gint
name|bytes2
parameter_list|,
name|gint
name|has_alpha2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|screen_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|length
parameter_list|,
name|gint
name|bytes2
parameter_list|,
name|gint
name|has_alpha2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|overlay_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|length
parameter_list|,
name|gint
name|bytes2
parameter_list|,
name|gint
name|has_alpha2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|add_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|length
parameter_list|,
name|gint
name|bytes2
parameter_list|,
name|gint
name|has_alpha2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|subtract_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|length
parameter_list|,
name|gint
name|bytes2
parameter_list|,
name|gint
name|has_alpha2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|difference_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|length
parameter_list|,
name|gint
name|bytes2
parameter_list|,
name|gint
name|has_alpha2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|dissolve_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|guint
name|x
parameter_list|,
name|guint
name|y
parameter_list|,
name|guint
name|opacity
parameter_list|,
name|guint
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|flatten_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|bg
parameter_list|,
name|guint
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  apply the mask data to the alpha channel of the pixel data  */
end_comment

begin_function_decl
name|void
name|apply_mask_to_alpha_channel_rgba
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
name|guint
name|opacity
parameter_list|,
name|guint
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  combine the mask data with the alpha channel of the pixel data  */
end_comment

begin_function_decl
name|void
name|combine_mask_and_alpha_channel_rgba
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
name|guint
name|opacity
parameter_list|,
name|guint
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  lay down the initial pixels in the case of only one  *  channel being visible and no layers...In this singular  *  case, we want to display a grayscale image w/o transparency  */
end_comment

begin_function_decl
name|void
name|initial_channel_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|guint
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  lay down the initial pixels for the base layer.  *  This process obviously requires no composition.  */
end_comment

begin_function_decl
name|void
name|initial_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
name|guint
name|opacity
parameter_list|,
specifier|const
name|gboolean
modifier|*
name|affect
parameter_list|,
name|guint
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  combine an RGB or GRAY image with an RGBA or GRAYA image  *  destination is intensity-alpha...  */
end_comment

begin_function_decl
name|void
name|combine_pixels_rgba_rgb
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
name|gint
name|opacity
parameter_list|,
specifier|const
name|gint
modifier|*
name|affect
parameter_list|,
name|gint
name|mode_affect
parameter_list|,
name|gint
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  combine an RGBA or GRAYA image with an RGBA or GRAYA image  *  destination is of course intensity-alpha...  */
end_comment

begin_function_decl
name|void
name|combine_pixels_rgba_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
name|gint
name|opacity
parameter_list|,
specifier|const
name|gint
modifier|*
name|affect
parameter_list|,
name|gint
name|mode_affect
parameter_list|,
name|gint
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  combine a channel with intensity-alpha pixels based  *  on some opacity, and a channel color...  *  destination is intensity-alpha  */
end_comment

begin_function_decl
name|void
name|combine_rgba_and_indexeda_pixels
parameter_list|(
name|apply_combine_layer_info
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|combine_rgba_and_channel_mask_pixels
parameter_list|(
name|apply_combine_layer_info
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|combine_rgba_and_channel_selection_pixels
parameter_list|(
name|apply_combine_layer_info
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  paint "behind" the existing pixel row.  *  This is similar in appearance to painting on a layer below  *  the existing pixels.  */
end_comment

begin_function_decl
name|void
name|behind_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
name|gint
name|opacity
parameter_list|,
specifier|const
name|gint
modifier|*
name|affect
parameter_list|,
name|gint
name|length
parameter_list|,
name|gint
name|bytes2
parameter_list|,
name|gint
name|has_alpha2
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  replace the contents of one pixel row with the other  *  The operation is still bounded by mask/opacity constraints  */
end_comment

begin_function_decl
name|void
name|replace_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|opacity
parameter_list|,
name|gboolean
modifier|*
name|affect
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  apply source 2 to source 1, but in a non-additive way,  *  multiplying alpha channels  (works for intensity)  */
end_comment

begin_function_decl
name|void
name|erase_pixels_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src1
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src2
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
name|gint
name|opacity
parameter_list|,
specifier|const
name|gint
modifier|*
name|affect
parameter_list|,
name|gint
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  extract information from intensity pixels based on  *  a mask.  */
end_comment

begin_function_decl
name|void
name|extract_from_pixels_rgba
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask
parameter_list|,
specifier|const
name|guchar
modifier|*
name|bg
parameter_list|,
name|gboolean
name|cut
parameter_list|,
name|guint
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|run_length_encode_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guint
modifier|*
name|dest
parameter_list|,
name|guint
name|w
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|apply_layer_mode_rgba_rgb
parameter_list|(
name|apply_combine_layer_info
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|apply_layer_mode_rgba_rgba
parameter_list|(
name|apply_combine_layer_info
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Opacities */
end_comment

begin_define
DECL|macro|TRANSPARENT_OPACITY
define|#
directive|define
name|TRANSPARENT_OPACITY
value|0
end_define

begin_define
DECL|macro|OPAQUE_OPACITY
define|#
directive|define
name|OPAQUE_OPACITY
value|255
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PAINT_FUNCS_RGBA_H__  */
end_comment

end_unit

