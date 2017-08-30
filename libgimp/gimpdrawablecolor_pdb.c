begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpdrawablecolor_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
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

begin_comment
comment|/**  * SECTION: gimpdrawablecolor  * @title: gimpdrawablecolor  * @short_description: Functions for manipulating a drawable's color.  *  * Functions for manipulating a drawable's color, including curves and  * histograms.  **/
end_comment

begin_comment
comment|/**  * gimp_drawable_brightness_contrast:  * @drawable_ID: The drawable.  * @brightness: Brightness adjustment.  * @contrast: Contrast adjustment.  *  * Modify brightness/contrast in the specified drawable.  *  * This procedures allows the brightness and contrast of the specified  * drawable to be modified. Both 'brightness' and 'contrast' parameters  * are defined between -0.5 and 0.5.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_brightness_contrast (gint32 drawable_ID,gdouble brightness,gdouble contrast)
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
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-brightness-contrast"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|brightness
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|contrast
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_color_balance:  * @drawable_ID: The drawable.  * @transfer_mode: Transfer mode.  * @preserve_lum: Preserve luminosity values at each pixel.  * @cyan_red: Cyan-Red color balance.  * @magenta_green: Magenta-Green color balance.  * @yellow_blue: Yellow-Blue color balance.  *  * Modify the color balance of the specified drawable.  *  * Modify the color balance of the specified drawable. There are three  * axis which can be modified: cyan-red, magenta-green, and  * yellow-blue. Negative values increase the amount of the former,  * positive values increase the amount of the latter. Color balance can  * be controlled with the 'transfer_mode' setting, which allows  * shadows, mid-tones, and highlights in an image to be affected  * differently. The 'preserve-lum' parameter, if TRUE, ensures that the  * luminosity of each pixel remains fixed.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_color_balance (gint32 drawable_ID,GimpTransferMode transfer_mode,gboolean preserve_lum,gdouble cyan_red,gdouble magenta_green,gdouble yellow_blue)
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
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-color-balance"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|transfer_mode
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|preserve_lum
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|cyan_red
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|magenta_green
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|yellow_blue
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_colorize_hsl:  * @drawable_ID: The drawable.  * @hue: Hue in degrees.  * @saturation: Saturation in percent.  * @lightness: Lightness in percent.  *  * Render the drawable as a grayscale image seen through a colored  * glass.  *  * Desaturates the drawable, then tints it with the specified color.  * This tool is only valid on RGB color images. It will not operate on  * grayscale drawables.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_colorize_hsl (gint32 drawable_ID,gdouble hue,gdouble saturation,gdouble lightness)
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
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-colorize-hsl"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|hue
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|saturation
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|lightness
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_curves_explicit:  * @drawable_ID: The drawable.  * @channel: The channel to modify.  * @num_values: The number of values in the new curve.  * @values: The explicit curve.  *  * Modifies the intensity curve(s) for specified drawable.  *  * Modifies the intensity mapping for one channel in the specified  * drawable. The channel can be either an intensity component, or the  * value. The 'values' parameter is an array of doubles which  * explicitly defines how each pixel value in the drawable will be  * modified. Use the gimp_curves_spline() function to modify intensity  * levels with Catmull Rom splines.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_curves_explicit (gint32 drawable_ID,GimpHistogramChannel channel,gint num_values,const gdouble * values)
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
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-curves-explicit"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|channel
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|num_values
argument_list|,
name|GIMP_PDB_FLOATARRAY
argument_list|,
name|values
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_curves_spline:  * @drawable_ID: The drawable.  * @channel: The channel to modify.  * @num_points: The number of values in the control point array.  * @points: The spline control points: { cp1.x, cp1.y, cp2.x, cp2.y, ... }.  *  * Modifies the intensity curve(s) for specified drawable.  *  * Modifies the intensity mapping for one channel in the specified  * drawable. The channel can be either an intensity component, or the  * value. The 'points' parameter is an array of doubles which define a  * set of control points which describe a Catmull Rom spline which  * yields the final intensity curve. Use the gimp_curves_explicit()  * function to explicitly modify intensity levels.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_curves_spline (gint32 drawable_ID,GimpHistogramChannel channel,gint num_points,const gdouble * points)
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
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-curves-spline"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|channel
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|num_points
argument_list|,
name|GIMP_PDB_FLOATARRAY
argument_list|,
name|points
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_desaturate:  * @drawable_ID: The drawable.  * @desaturate_mode: The formula to use to desaturate.  *  * Desaturate the contents of the specified drawable, with the  * specified formula.  *  * This procedure desaturates the contents of the specified drawable,  * with the specified formula. This procedure only works on drawables  * of type RGB color.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_desaturate (gint32 drawable_ID,GimpDesaturateMode desaturate_mode)
name|gimp_drawable_desaturate
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpDesaturateMode
name|desaturate_mode
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-desaturate"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|desaturate_mode
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_equalize:  * @drawable_ID: The drawable.  * @mask_only: Equalization option.  *  * Equalize the contents of the specified drawable.  *  * This procedure equalizes the contents of the specified drawable.  * Each intensity channel is equalized independently. The equalized  * intensity is given as inten' = (255 - inten). The 'mask_only' option  * specifies whether to adjust only the area of the image within the  * selection bounds, or the entire image based on the histogram of the  * selected area. If there is no selection, the entire image is  * adjusted based on the histogram for the entire image.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_equalize (gint32 drawable_ID,gboolean mask_only)
name|gimp_drawable_equalize
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|mask_only
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-equalize"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|mask_only
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_histogram:  * @drawable_ID: The drawable.  * @channel: The channel to query.  * @start_range: Start of the intensity measurement range.  * @end_range: End of the intensity measurement range.  * @mean: Mean intensity value.  * @std_dev: Standard deviation of intensity values.  * @median: Median intensity value.  * @pixels: Alpha-weighted pixel count for entire image.  * @count: Alpha-weighted pixel count for range.  * @percentile: Percentile that range falls under.  *  * Returns information on the intensity histogram for the specified  * drawable.  *  * This tool makes it possible to gather information about the  * intensity histogram of a drawable. A channel to examine is first  * specified. This can be either value, red, green, or blue, depending  * on whether the drawable is of type color or grayscale. Second, a  * range of intensities are specified. The gimp_drawable_histogram()  * function returns statistics based on the pixels in the drawable that  * fall under this range of values. Mean, standard deviation, median,  * number of pixels, and percentile are all returned. Additionally, the  * total count of pixels in the image is returned. Counts of pixels are  * weighted by any associated alpha values and by the current selection  * mask. That is, pixels that lie outside an active selection mask will  * not be counted. Similarly, pixels with transparent alpha values will  * not be counted. The returned mean, std_dev and median are in the  * range (0..255) for 8-bit images or if the plug-in is not  * precision-aware, and in the range (0.0..1.0) otherwise.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_histogram (gint32 drawable_ID,GimpHistogramChannel channel,gdouble start_range,gdouble end_range,gdouble * mean,gdouble * std_dev,gdouble * median,gdouble * pixels,gdouble * count,gdouble * percentile)
name|gimp_drawable_histogram
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
name|gdouble
name|start_range
parameter_list|,
name|gdouble
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
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-histogram"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|channel
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|start_range
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|end_range
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|mean
operator|=
literal|0.0
expr_stmt|;
operator|*
name|std_dev
operator|=
literal|0.0
expr_stmt|;
operator|*
name|median
operator|=
literal|0.0
expr_stmt|;
operator|*
name|pixels
operator|=
literal|0.0
expr_stmt|;
operator|*
name|count
operator|=
literal|0.0
expr_stmt|;
operator|*
name|percentile
operator|=
literal|0.0
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
operator|*
name|mean
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
operator|*
name|std_dev
operator|=
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
operator|*
name|median
operator|=
name|return_vals
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
operator|*
name|pixels
operator|=
name|return_vals
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
operator|*
name|count
operator|=
name|return_vals
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
operator|*
name|percentile
operator|=
name|return_vals
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
block|}
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_hue_saturation:  * @drawable_ID: The drawable.  * @hue_range: Range of affected hues.  * @hue_offset: Hue offset in degrees.  * @lightness: Lightness modification.  * @saturation: Saturation modification.  * @overlap: Overlap other hue channels.  *  * Modify hue, lightness, and saturation in the specified drawable.  *  * This procedure allows the hue, lightness, and saturation in the  * specified drawable to be modified. The 'hue-range' parameter  * provides the capability to limit range of affected hues. The  * 'overlap' parameter provides blending into neighboring hue channels  * when rendering.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_hue_saturation (gint32 drawable_ID,GimpHueRange hue_range,gdouble hue_offset,gdouble lightness,gdouble saturation,gdouble overlap)
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
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-hue-saturation"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|hue_range
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|hue_offset
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|lightness
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|saturation
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|overlap
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_invert_linear:  * @drawable_ID: The drawable.  *  * Invert the contents of the specified drawable in linear light.  *  * This procedure inverts the contents of the specified drawable. Each  * component inverted independently. This procedure works on linear RGB  * or Gray values.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_invert_linear (gint32 drawable_ID)
name|gimp_drawable_invert_linear
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-invert-linear"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_invert_non_linear:  * @drawable_ID: The drawable.  *  * Invert the contents of the specified drawable in perceptual space.  *  * This procedure inverts the contents of the specified drawable. Each  * intensity channel is inverted independently. The inverted intensity  * is given as inten' = (255 - inten).  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_invert_non_linear (gint32 drawable_ID)
name|gimp_drawable_invert_non_linear
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-invert-non-linear"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_levels:  * @drawable_ID: The drawable.  * @channel: The channel to modify.  * @low_input: Intensity of lowest input.  * @high_input: Intensity of highest input.  * @gamma: Gamma adjustment factor.  * @low_output: Intensity of lowest output.  * @high_output: Intensity of highest output.  *  * Modifies intensity levels in the specified drawable.  *  * This tool allows intensity levels in the specified drawable to be  * remapped according to a set of parameters. The low/high input levels  * specify an initial mapping from the source intensities. The gamma  * value determines how intensities between the low and high input  * intensities are interpolated. A gamma value of 1.0 results in a  * linear interpolation. Higher gamma values result in more high-level  * intensities. Lower gamma values result in more low-level  * intensities. The low/high output levels constrain the final  * intensity mapping--that is, no final intensity will be lower than  * the low output level and no final intensity will be higher than the  * high output level. This tool is only valid on RGB color and  * grayscale images.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_levels (gint32 drawable_ID,GimpHistogramChannel channel,gdouble low_input,gdouble high_input,gdouble gamma,gdouble low_output,gdouble high_output)
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
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-levels"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|channel
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|low_input
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|high_input
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|gamma
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|low_output
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|high_output
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_levels_stretch:  * @drawable_ID: The drawable.  *  * Automatically modifies intensity levels in the specified drawable.  *  * This procedure allows intensity levels in the specified drawable to  * be remapped according to a set of guessed parameters. It is  * equivalent to clicking the \"Auto\" button in the Levels tool.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_levels_stretch (gint32 drawable_ID)
name|gimp_drawable_levels_stretch
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-levels-stretch"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_posterize:  * @drawable_ID: The drawable.  * @levels: Levels of posterization.  *  * Posterize the specified drawable.  *  * This procedures reduces the number of shades allows in each  * intensity channel to the specified 'levels' parameter.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_posterize (gint32 drawable_ID,gint levels)
name|gimp_drawable_posterize
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|levels
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-posterize"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|levels
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_threshold:  * @drawable_ID: The drawable.  * @channel: The channel to base the threshold on.  * @low_threshold: The low threshold value.  * @high_threshold: The high threshold value.  *  * Threshold the specified drawable.  *  * This procedures generates a threshold map of the specified drawable.  * All pixels between the values of 'low_threshold' and  * 'high_threshold', on the scale of 'channel' are replaced with white,  * and all other pixels with black.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_threshold (gint32 drawable_ID,GimpHistogramChannel channel,gdouble low_threshold,gdouble high_threshold)
name|gimp_drawable_threshold
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
name|gdouble
name|low_threshold
parameter_list|,
name|gdouble
name|high_threshold
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-drawable-threshold"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|channel
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|low_threshold
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|high_threshold
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

