begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpcolor_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_brightness_contrast (gint32 drawable_ID,gint brightness,gint contrast)
name|gimp_brightness_contrast
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|brightness
parameter_list|,
name|gint
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
literal|"gimp_brightness_contrast"
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
name|brightness
argument_list|,
name|GIMP_PDB_INT32
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

begin_function
name|gboolean
DECL|function|gimp_levels (gint32 drawable_ID,GimpChannelLutType channel,gint low_input,gint high_input,gdouble gamma,gint low_output,gint high_output)
name|gimp_levels
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpChannelLutType
name|channel
parameter_list|,
name|gint
name|low_input
parameter_list|,
name|gint
name|high_input
parameter_list|,
name|gdouble
name|gamma
parameter_list|,
name|gint
name|low_output
parameter_list|,
name|gint
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
literal|"gimp_levels"
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
name|low_input
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|high_input
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|gamma
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|low_output
argument_list|,
name|GIMP_PDB_INT32
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

begin_function
name|gboolean
DECL|function|gimp_posterize (gint32 drawable_ID,gint levels)
name|gimp_posterize
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
literal|"gimp_posterize"
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

begin_function
name|gboolean
DECL|function|gimp_desaturate (gint32 drawable_ID)
name|gimp_desaturate
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
literal|"gimp_desaturate"
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

begin_function
name|gboolean
DECL|function|gimp_equalize (gint32 drawable_ID,gboolean mask_only)
name|gimp_equalize
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
literal|"gimp_equalize"
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

begin_function
name|gboolean
DECL|function|gimp_invert (gint32 drawable_ID)
name|gimp_invert
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
literal|"gimp_invert"
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

begin_function
name|gboolean
DECL|function|gimp_curves_spline (gint32 drawable_ID,GimpChannelLutType channel,gint num_points,guint8 * control_pts)
name|gimp_curves_spline
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpChannelLutType
name|channel
parameter_list|,
name|gint
name|num_points
parameter_list|,
name|guint8
modifier|*
name|control_pts
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
literal|"gimp_curves_spline"
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
name|GIMP_PDB_INT8ARRAY
argument_list|,
name|control_pts
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

begin_function
name|gboolean
DECL|function|gimp_curves_explicit (gint32 drawable_ID,GimpChannelLutType channel,gint num_bytes,guint8 * curve)
name|gimp_curves_explicit
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpChannelLutType
name|channel
parameter_list|,
name|gint
name|num_bytes
parameter_list|,
name|guint8
modifier|*
name|curve
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
literal|"gimp_curves_explicit"
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
name|num_bytes
argument_list|,
name|GIMP_PDB_INT8ARRAY
argument_list|,
name|curve
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

begin_function
name|gboolean
DECL|function|gimp_color_balance (gint32 drawable_ID,GimpTransferMode transfer_mode,gboolean preserve_lum,gdouble cyan_red,gdouble magenta_green,gdouble yellow_blue)
name|gimp_color_balance
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
literal|"gimp_color_balance"
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

begin_function
name|gboolean
DECL|function|gimp_histogram (gint32 drawable_ID,GimpChannelLutType channel,gint start_range,gint end_range,gdouble * mean,gdouble * std_dev,gdouble * median,gdouble * pixels,gdouble * count,gdouble * percentile)
name|gimp_histogram
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpChannelLutType
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
literal|"gimp_histogram"
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
name|start_range
argument_list|,
name|GIMP_PDB_INT32
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

begin_function
name|gboolean
DECL|function|gimp_hue_saturation (gint32 drawable_ID,GimpHueRange hue_range,gdouble hue_offset,gdouble lightness,gdouble saturation)
name|gimp_hue_saturation
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
literal|"gimp_hue_saturation"
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

begin_function
name|gboolean
DECL|function|gimp_threshold (gint32 drawable_ID,gint low_threshold,gint high_threshold)
name|gimp_threshold
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
literal|"gimp_threshold"
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
name|low_threshold
argument_list|,
name|GIMP_PDB_INT32
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

