begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpdrawablecolor_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimp.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_COLOR_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_COLOR_PDB_H__
define|#
directive|define
name|__GIMP_DRAWABLE_COLOR_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_drawable_brightness_contrast
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|brightness
parameter_list|,
name|gdouble
name|contrast
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_color_balance
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpTransferMode
name|transfer_mode
parameter_list|,
name|gboolean
name|preserve_lum
parameter_list|,
name|gdouble
name|cyan_red
parameter_list|,
name|gdouble
name|magenta_green
parameter_list|,
name|gdouble
name|yellow_blue
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_colorize_hsl
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|hue
parameter_list|,
name|gdouble
name|saturation
parameter_list|,
name|gdouble
name|lightness
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_curves_explicit
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
name|gint
name|num_values
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_curves_spline
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
name|gint
name|num_points
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|points
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_desaturate
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpDesaturateMode
name|desaturate_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_equalize
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|mask_only
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_histogram
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
name|gint
name|start_range
parameter_list|,
name|gint
name|end_range
parameter_list|,
name|gdouble
modifier|*
name|mean
parameter_list|,
name|gdouble
modifier|*
name|std_dev
parameter_list|,
name|gdouble
modifier|*
name|median
parameter_list|,
name|gdouble
modifier|*
name|pixels
parameter_list|,
name|gdouble
modifier|*
name|count
parameter_list|,
name|gdouble
modifier|*
name|percentile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_hue_saturation
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpHueRange
name|hue_range
parameter_list|,
name|gdouble
name|hue_offset
parameter_list|,
name|gdouble
name|lightness
parameter_list|,
name|gdouble
name|saturation
parameter_list|,
name|gdouble
name|overlap
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_invert
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_levels
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
name|gdouble
name|low_input
parameter_list|,
name|gdouble
name|high_input
parameter_list|,
name|gdouble
name|gamma
parameter_list|,
name|gdouble
name|low_output
parameter_list|,
name|gdouble
name|high_output
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_levels_stretch
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_posterize
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|levels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_threshold
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|low_threshold
parameter_list|,
name|gint
name|high_threshold
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DRAWABLE_COLOR_PDB_H__ */
end_comment

end_unit

