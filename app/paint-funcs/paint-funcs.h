begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PAINT_FUNCS_H__
end_ifndef

begin_define
DECL|macro|__PAINT_FUNCS_H__
define|#
directive|define
name|__PAINT_FUNCS_H__
end_define

begin_comment
comment|/*  Called initially to setup rendering features  */
end_comment

begin_function_decl
name|void
name|paint_funcs_setup
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_funcs_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Paint functions  */
end_comment

begin_function_decl
name|void
name|color_pixels
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
name|guint
name|w
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|blend_pixels
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
name|guchar
name|blend
parameter_list|,
name|guint
name|w
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|shade_pixels
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
name|guchar
name|rblend
parameter_list|,
name|guint
name|w
parameter_list|,
name|guint
name|bytes
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|extract_alpha_pixels
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
name|guint
name|w
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|swap_pixels
parameter_list|(
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

begin_function_decl
name|void
name|scale_pixels
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
parameter_list|,
name|gint
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|add_alpha_pixels
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
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|flatten_pixels
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
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gray_to_rgb_pixels
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
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|copy_component_pixels
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
parameter_list|,
name|guint
name|bytes
parameter_list|,
name|guint
name|pixel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|copy_color_pixels
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
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  apply the mask data to the alpha channel of the pixel data  */
end_comment

begin_function_decl
name|void
name|apply_mask_to_alpha_channel
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
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  combine the mask data with the alpha channel of the pixel data  */
end_comment

begin_function_decl
name|void
name|combine_mask_and_alpha_channel_stipple
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
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|combine_mask_and_alpha_channel_stroke
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
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  copy gray pixels to intensity-alpha pixels.  This function  *  essentially takes a source that is only a grayscale image and  *  copies it to the destination, expanding to RGB if necessary and  *  adding an alpha channel.  (OPAQUE)  */
end_comment

begin_function_decl
name|void
name|copy_gray_to_inten_a_pixels
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
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  lay down the initial pixels in the case of only one  *  channel being visible and no layers...In this singular  *  case, we want to display a grayscale image w/o transparency  */
end_comment

begin_function_decl
name|void
name|initial_channel_pixels
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
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  lay down the initial pixels in the case of an indexed image.  *  This process obviously requires no composition  */
end_comment

begin_function_decl
name|void
name|initial_indexed_pixels
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
name|cmap
parameter_list|,
name|guint
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  lay down the initial pixels in the case of an indexed image.  *  This process obviously requires no composition  */
end_comment

begin_function_decl
name|void
name|initial_indexed_a_pixels
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
specifier|const
name|guchar
modifier|*
name|no_mask
parameter_list|,
specifier|const
name|guchar
modifier|*
name|cmap
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
comment|/*  lay down the initial pixels for the base layer.  *  This process obviously requires no composition.  */
end_comment

begin_function_decl
name|void
name|initial_inten_pixels
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
specifier|const
name|guchar
modifier|*
name|no_mask
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
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  lay down the initial pixels for the base layer.  *  This process obviously requires no composition.  */
end_comment

begin_function_decl
name|void
name|initial_inten_a_pixels
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
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  combine indexed images with an optional mask which  *  is interpreted as binary...destination is indexed...  */
end_comment

begin_function_decl
name|void
name|combine_indexed_and_indexed_pixels
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
name|opacity
parameter_list|,
specifier|const
name|gboolean
modifier|*
name|affect
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  combine indexed images with indexed-alpha images  *  result is an indexed image  */
end_comment

begin_function_decl
name|void
name|combine_indexed_and_indexed_a_pixels
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
name|opacity
parameter_list|,
specifier|const
name|gint
modifier|*
name|affect
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  combine indexed-alpha images with indexed-alpha images  *  result is an indexed-alpha image.  use this for painting  *  to an indexed floating sel  */
end_comment

begin_function_decl
name|void
name|combine_indexed_a_and_indexed_a_pixels
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
name|opacity
parameter_list|,
specifier|const
name|gboolean
modifier|*
name|affect
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  combine intensity with indexed, destination is  *  intensity-alpha...use this for an indexed floating sel  */
end_comment

begin_function_decl
name|void
name|combine_inten_a_and_indexed_a_pixels
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
specifier|const
name|guchar
modifier|*
name|cmap
parameter_list|,
name|guint
name|opacity
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  combine RGB image with RGB or GRAY with GRAY  *  destination is intensity-only...  */
end_comment

begin_function_decl
name|void
name|combine_inten_and_inten_pixels
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
name|opacity
parameter_list|,
specifier|const
name|gboolean
modifier|*
name|affect
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  combine an RGBA or GRAYA image with an RGB or GRAY image  *  destination is intensity-only...  */
end_comment

begin_function_decl
name|void
name|combine_inten_and_inten_a_pixels
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
name|opacity
parameter_list|,
specifier|const
name|gboolean
modifier|*
name|affect
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  combine an RGB or GRAY image with an RGBA or GRAYA image  *  destination is intensity-alpha...  */
end_comment

begin_function_decl
name|void
name|combine_inten_a_and_inten_pixels
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
name|opacity
parameter_list|,
specifier|const
name|gboolean
modifier|*
name|affect
parameter_list|,
name|gboolean
name|mode_affect
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  combine an RGBA or GRAYA image with an RGBA or GRAYA image  *  destination is of course intensity-alpha...  */
end_comment

begin_function_decl
name|void
name|combine_inten_a_and_inten_a_pixels
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
name|opacity
parameter_list|,
specifier|const
name|gboolean
modifier|*
name|affect
parameter_list|,
name|gboolean
name|mode_affect
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  combine a channel with intensity-alpha pixels based  *  on some opacity, and a channel color...  *  destination is intensity-alpha  */
end_comment

begin_function_decl
name|void
name|combine_inten_a_and_channel_mask_pixels
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
specifier|const
name|guchar
modifier|*
name|channel
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|col
parameter_list|,
name|guint
name|opacity
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|combine_inten_a_and_channel_selection_pixels
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
specifier|const
name|guchar
modifier|*
name|channel
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|col
parameter_list|,
name|guint
name|opacity
parameter_list|,
name|guint
name|length
parameter_list|,
name|guint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  extract information from intensity pixels based on  *  a mask.  */
end_comment

begin_function_decl
name|void
name|extract_from_inten_pixels
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
parameter_list|,
name|guint
name|src_bytes
parameter_list|,
name|guint
name|dest_bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  extract information from indexed pixels based on  *  a mask.  */
end_comment

begin_function_decl
name|void
name|extract_from_indexed_pixels
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
name|cmap
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
parameter_list|,
name|guint
name|src_bytes
parameter_list|,
name|guint
name|dest_bytes
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Region functions  */
end_comment

begin_function_decl
name|void
name|color_region
parameter_list|(
name|PixelRegion
modifier|*
name|dest
parameter_list|,
specifier|const
name|guchar
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_region_mask
parameter_list|(
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
specifier|const
name|guchar
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pattern_region
parameter_list|(
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
name|TempBuf
modifier|*
name|pattern
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|blend_region
parameter_list|(
name|PixelRegion
modifier|*
name|src1
parameter_list|,
name|PixelRegion
modifier|*
name|src2
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|guchar
name|blend
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|shade_region
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|guchar
modifier|*
name|color
parameter_list|,
name|guchar
name|blend
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|copy_region
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|copy_region_nocow
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|add_alpha_region
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|flatten_region
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|guchar
modifier|*
name|bg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|extract_alpha_region
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|extract_from_region
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
specifier|const
name|guchar
modifier|*
name|cmap
parameter_list|,
specifier|const
name|guchar
modifier|*
name|bg
parameter_list|,
name|GimpImageBaseType
name|type
parameter_list|,
name|gboolean
name|cut
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|convolve_region
parameter_list|(
name|PixelRegion
modifier|*
name|srcR
parameter_list|,
name|PixelRegion
modifier|*
name|destR
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|matrix
parameter_list|,
name|gint
name|size
parameter_list|,
name|gdouble
name|divisor
parameter_list|,
name|GimpConvolutionType
name|mode
parameter_list|,
name|gboolean
name|alpha_weighting
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|multiply_alpha_region
parameter_list|(
name|PixelRegion
modifier|*
name|srcR
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|separate_alpha_region
parameter_list|(
name|PixelRegion
modifier|*
name|srcR
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gaussian_blur_region
parameter_list|(
name|PixelRegion
modifier|*
name|srcR
parameter_list|,
name|gdouble
name|radius_x
parameter_list|,
name|gdouble
name|radius_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|border_region
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|gint16
name|xradius
parameter_list|,
name|gint16
name|yradius
parameter_list|,
name|gboolean
name|feather
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|subsample_region
parameter_list|(
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

begin_function_decl
name|gfloat
name|shapeburst_region
parameter_list|(
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|distPR
parameter_list|,
name|GimpProgressFunc
name|progress_callback
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|thin_region
parameter_list|(
name|PixelRegion
modifier|*
name|region
parameter_list|,
name|gint16
name|xradius
parameter_list|,
name|gint16
name|yradius
parameter_list|,
name|gboolean
name|edge_lock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fatten_region
parameter_list|(
name|PixelRegion
modifier|*
name|region
parameter_list|,
name|gint16
name|xradius
parameter_list|,
name|gint16
name|yradius
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|smooth_region
parameter_list|(
name|PixelRegion
modifier|*
name|region
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|erode_region
parameter_list|(
name|PixelRegion
modifier|*
name|region
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|dilate_region
parameter_list|(
name|PixelRegion
modifier|*
name|region
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|swap_region
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Apply a mask to an image's alpha channel  */
end_comment

begin_function_decl
name|void
name|apply_mask_to_region
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
name|guint
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Combine a mask with an image's alpha channel  */
end_comment

begin_function_decl
name|void
name|combine_mask_and_region
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
name|guint
name|opacity
parameter_list|,
name|gboolean
name|stipple
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Copy a gray image to an intensity-alpha region  */
end_comment

begin_function_decl
name|void
name|copy_gray_to_region
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Copy a component (indexed by pixel) to a 1-byte region  */
end_comment

begin_function_decl
name|void
name|copy_component
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|guint
name|pixel
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Copy the color bytes (without alpha channel) to a src_bytes-1 - byte region  */
end_comment

begin_function_decl
name|void
name|copy_color
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|initial_region
parameter_list|(
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|,
name|guint
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|,
specifier|const
name|gboolean
modifier|*
name|affect
parameter_list|,
name|InitialMode
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|combine_regions
parameter_list|(
name|PixelRegion
modifier|*
name|src1
parameter_list|,
name|PixelRegion
modifier|*
name|src2
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|,
name|guint
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|,
specifier|const
name|gboolean
modifier|*
name|affect
parameter_list|,
name|CombinationMode
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|combine_regions_replace
parameter_list|(
name|PixelRegion
modifier|*
name|src1
parameter_list|,
name|PixelRegion
modifier|*
name|src2
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|,
name|guint
name|opacity
parameter_list|,
specifier|const
name|gboolean
modifier|*
name|affect
parameter_list|,
name|CombinationMode
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PAINT_FUNCS_H__  */
end_comment

end_unit

