begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpmisctools_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
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
comment|/**  * gimp_blend:  * @drawable_ID: The affected drawable.  * @blend_mode: The type of blend.  * @paint_mode: The paint application mode.  * @gradient_type: The type of gradient.  * @opacity: The opacity of the final blend.  * @offset: Offset relates to the starting and ending coordinates specified for the blend. This parameter is mode dependent.  * @repeat: Repeat mode.  * @supersample: Do adaptive supersampling.  * @max_depth: Maximum recursion levels for supersampling.  * @threshold: Supersampling threshold.  * @dither: Use dithering to reduce banding.  * @x1: The x coordinate of this blend's starting point.  * @y1: The y coordinate of this blend's starting point.  * @x2: The x coordinate of this blend's ending point.  * @y2: The y coordinate of this blend's ending point.  *  * Blend between the starting and ending coordinates with the specified  * blend mode and gradient type.  *  * This tool requires information on the paint application mode, the  * blend mode, and the gradient type. It creates the specified variety  * of blend using the starting and ending coordinates as defined for  * each gradient type.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_blend (gint32 drawable_ID,GimpBlendMode blend_mode,GimpLayerModeEffects paint_mode,GimpGradientType gradient_type,gdouble opacity,gdouble offset,GimpRepeatMode repeat,gboolean supersample,gint max_depth,gdouble threshold,gboolean dither,gdouble x1,gdouble y1,gdouble x2,gdouble y2)
name|gimp_blend
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpBlendMode
name|blend_mode
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|,
name|GimpGradientType
name|gradient_type
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gdouble
name|offset
parameter_list|,
name|GimpRepeatMode
name|repeat
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|max_depth
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gboolean
name|dither
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
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
literal|"gimp_blend"
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
name|blend_mode
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|paint_mode
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|gradient_type
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|opacity
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|offset
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|repeat
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|supersample
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|max_depth
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|threshold
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|dither
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x1
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y1
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x2
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y2
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
comment|/**  * gimp_bucket_fill:  * @drawable_ID: The affected drawable.  * @fill_mode: The type of fill.  * @paint_mode: The paint application mode.  * @opacity: The opacity of the final bucket fill.  * @threshold: The threshold determines how extensive the seed fill will be. It's value is specified in terms of intensity levels . This parameter is only valid when there is no selection in the specified image.  * @sample_merged: Use the composite image, not the drawable.  * @x: The x coordinate of this bucket fill's application. This parameter is only valid when there is no selection in the specified image.  * @y: The y coordinate of this bucket fill's application. This parameter is only valid when there is no selection in the specified image.  *  * Fill the area specified either by the current selection if there is  * one, or by a seed fill starting at the specified coordinates.  *  * This tool requires information on the paint application mode, and  * the fill mode, which can either be in the foreground color, or in  * the currently active pattern. If there is no selection, a seed fill  * is executed at the specified coordinates and extends outward in  * keeping with the threshold parameter. If there is a selection in the  * target image, the threshold, sample merged, x, and y arguments are  * unused. If the sample_merged parameter is non-zero, the data of the  * composite image will be used instead of that for the specified  * drawable. This is equivalent to sampling for colors after merging  * all visible layers. In the case of merged sampling, the x,y  * coordinates are relative to the image's origin; otherwise, they are  * relative to the drawable's origin.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_bucket_fill (gint32 drawable_ID,GimpBucketFillMode fill_mode,GimpLayerModeEffects paint_mode,gdouble opacity,gdouble threshold,gboolean sample_merged,gdouble x,gdouble y)
name|gimp_bucket_fill
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpBucketFillMode
name|fill_mode
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
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
literal|"gimp_bucket_fill"
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
name|fill_mode
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|paint_mode
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|opacity
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|threshold
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|sample_merged
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y
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
comment|/**  * gimp_color_picker:  * @image_ID: The image.  * @drawable_ID: The affected drawable.  * @x: x coordinate of upper-left corner of rectangle.  * @y: y coordinate of upper-left corner of rectangle.  * @sample_merged: Use the composite image, not the drawable.  * @sample_average: Average the color of all the pixels in a specified radius.  * @average_radius: The radius of pixels to average.  * @color: The return color.  *  * Determine the color at the given drawable coordinates  *  * This tool determines the color at the specified coordinates. The  * returned color is an RGB triplet even for grayscale and indexed  * drawables. If the coordinates lie outside of the extents of the  * specified drawable, then an error is returned. If the drawable has  * an alpha channel, the algorithm examines the alpha value of the  * drawable at the coordinates. If the alpha value is completely  * transparent (0), then an error is returned. If the sample_merged  * parameter is non-zero, the data of the composite image will be used  * instead of that for the specified drawable. This is equivalent to  * sampling for colors after merging all visible layers. In the case of  * a merged sampling, the supplied drawable is ignored.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_color_picker (gint32 image_ID,gint32 drawable_ID,gdouble x,gdouble y,gboolean sample_merged,gboolean sample_average,gdouble average_radius,GimpRGB * color)
name|gimp_color_picker
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gboolean
name|sample_average
parameter_list|,
name|gdouble
name|average_radius
parameter_list|,
name|GimpRGB
modifier|*
name|color
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
literal|"gimp_color_picker"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|sample_merged
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|sample_average
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|average_radius
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
if|if
condition|(
name|success
condition|)
operator|*
name|color
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_color
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

