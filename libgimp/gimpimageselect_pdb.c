begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpimageselect_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimpimageselect_pdb  * @title: gimpimageselect  * @short_description: Modify the image's selection.  *  * Functions to modify the image's selection.  **/
end_comment

begin_comment
comment|/**  * gimp_image_select_color:  * @image_ID: The affected image.  * @operation: The selection operation.  * @drawable_ID: The affected drawable.  * @color: The color to select.  *  * Create a selection by selecting all pixels (in the specified  * drawable) with the same (or similar) color to that specified.  *  * This tool creates a selection over the specified image. A by-color  * selection is determined by the supplied color under the constraints  * of the current context settings. Essentially, all pixels (in the  * drawable) that have color sufficiently close to the specified color  * (as determined by the threshold and criterion context values) are  * included in the selection. To select transparent regions, the color  * specified must also have minimum alpha.  *  * This procedure is affected by the following context setters:  * gimp_context_set_antialias(), gimp_context_set_feather(),  * gimp_context_set_feather_radius(), gimp_context_set_sample_merged(),  * gimp_context_set_sample_criterion(),  * gimp_context_set_sample_threshold(),  * gimp_context_set_sample_transparent().  *  * In the case of a merged sampling, the supplied drawable is ignored.  *  * Returns: TRUE on success.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_select_color (gint32 image_ID,GimpChannelOps operation,gint32 drawable_ID,const GimpRGB * color)
name|gimp_image_select_color
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|GIMP_TYPE_CHANNEL_OPS
argument_list|,
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|GIMP_TYPE_RGB
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|operation
argument_list|)
expr_stmt|;
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|gimp_value_set_rgb
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-select-color"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_select_contiguous_color:  * @image_ID: The affected image.  * @operation: The selection operation.  * @drawable_ID: The affected drawable.  * @x: x coordinate of initial seed fill point: (image coordinates).  * @y: y coordinate of initial seed fill point: (image coordinates).  *  * Create a selection by selecting all pixels around specified  * coordinates with the same (or similar) color to that at the  * coordinates.  *  * This tool creates a contiguous selection over the specified image. A  * contiguous color selection is determined by a seed fill under the  * constraints of the current context settings. Essentially, the color  * at the specified coordinates (in the drawable) is measured and the  * selection expands outwards from that point to any adjacent pixels  * which are not significantly different (as determined by the  * threshold and criterion context settings). This process continues  * until no more expansion is possible. If antialiasing is turned on,  * the final selection mask will contain intermediate values based on  * close misses to the threshold bar at pixels along the seed fill  * boundary.  *  * This procedure is affected by the following context setters:  * gimp_context_set_antialias(), gimp_context_set_feather(),  * gimp_context_set_feather_radius(), gimp_context_set_sample_merged(),  * gimp_context_set_sample_criterion(),  * gimp_context_set_sample_threshold(),  * gimp_context_set_sample_transparent(),  * gimp_context_set_diagonal_neighbors().  *  * In the case of a merged sampling, the supplied drawable is ignored.  * If the sample is merged, the specified coordinates are relative to  * the image origin; otherwise, they are relative to the drawable's  * origin.  *  * Returns: TRUE on success.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_select_contiguous_color (gint32 image_ID,GimpChannelOps operation,gint32 drawable_ID,gdouble x,gdouble y)
name|gimp_image_select_contiguous_color
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|GIMP_TYPE_CHANNEL_OPS
argument_list|,
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|operation
argument_list|)
expr_stmt|;
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|x
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|4
argument_list|)
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-select-contiguous-color"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_select_rectangle:  * @image_ID: The image.  * @operation: The selection operation.  * @x: x coordinate of upper-left corner of rectangle.  * @y: y coordinate of upper-left corner of rectangle.  * @width: The width of the rectangle.  * @height: The height of the rectangle.  *  * Create a rectangular selection over the specified image;  *  * This tool creates a rectangular selection over the specified image.  * The rectangular region can be either added to, subtracted from, or  * replace the contents of the previous selection mask.  *  * This procedure is affected by the following context setters:  * gimp_context_set_feather(), gimp_context_set_feather_radius().  *  * Returns: TRUE on success.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_select_rectangle (gint32 image_ID,GimpChannelOps operation,gdouble x,gdouble y,gdouble width,gdouble height)
name|gimp_image_select_rectangle
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|GIMP_TYPE_CHANNEL_OPS
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|operation
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|x
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|4
argument_list|)
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|5
argument_list|)
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-select-rectangle"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_select_round_rectangle:  * @image_ID: The image.  * @operation: The selection operation.  * @x: x coordinate of upper-left corner of rectangle.  * @y: y coordinate of upper-left corner of rectangle.  * @width: The width of the rectangle.  * @height: The height of the rectangle.  * @corner_radius_x: The corner radius in X direction.  * @corner_radius_y: The corner radius in Y direction.  *  * Create a rectangular selection with round corners over the specified  * image;  *  * This tool creates a rectangular selection with round corners over  * the specified image. The rectangular region can be either added to,  * subtracted from, or replace the contents of the previous selection  * mask.  *  * This procedure is affected by the following context setters:  * gimp_context_set_antialias(), gimp_context_set_feather(),  * gimp_context_set_feather_radius().  *  * Returns: TRUE on success.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_select_round_rectangle (gint32 image_ID,GimpChannelOps operation,gdouble x,gdouble y,gdouble width,gdouble height,gdouble corner_radius_x,gdouble corner_radius_y)
name|gimp_image_select_round_rectangle
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|,
name|gdouble
name|corner_radius_x
parameter_list|,
name|gdouble
name|corner_radius_y
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|GIMP_TYPE_CHANNEL_OPS
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|operation
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|x
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|4
argument_list|)
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|5
argument_list|)
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|6
argument_list|)
argument_list|,
name|corner_radius_x
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|7
argument_list|)
argument_list|,
name|corner_radius_y
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-select-round-rectangle"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_select_ellipse:  * @image_ID: The image.  * @operation: The selection operation.  * @x: x coordinate of upper-left corner of ellipse bounding box.  * @y: y coordinate of upper-left corner of ellipse bounding box.  * @width: The width of the ellipse.  * @height: The height of the ellipse.  *  * Create an elliptical selection over the specified image.  *  * This tool creates an elliptical selection over the specified image.  * The elliptical region can be either added to, subtracted from, or  * replace the contents of the previous selection mask.  *  * This procedure is affected by the following context setters:  * gimp_context_set_antialias(), gimp_context_set_feather(),  * gimp_context_set_feather_radius().  *  * Returns: TRUE on success.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_select_ellipse (gint32 image_ID,GimpChannelOps operation,gdouble x,gdouble y,gdouble width,gdouble height)
name|gimp_image_select_ellipse
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|GIMP_TYPE_CHANNEL_OPS
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|operation
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|x
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|4
argument_list|)
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|5
argument_list|)
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-select-ellipse"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_select_polygon:  * @image_ID: The image.  * @operation: The selection operation.  * @num_segs: Number of points (count 1 coordinate as two points).  * @segs: Array of points: { p1.x, p1.y, p2.x, p2.y, ..., pn.x, pn.y}.  *  * Create a polygonal selection over the specified image.  *  * This tool creates a polygonal selection over the specified image.  * The polygonal region can be either added to, subtracted from, or  * replace the contents of the previous selection mask. The polygon is  * specified through an array of floating point numbers and its length.  * The length of array must be 2n, where n is the number of points.  * Each point is defined by 2 floating point values which correspond to  * the x and y coordinates. If the final point does not connect to the  * starting point, a connecting segment is automatically added.  *  * This procedure is affected by the following context setters:  * gimp_context_set_antialias(), gimp_context_set_feather(),  * gimp_context_set_feather_radius().  *  * Returns: TRUE on success.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_select_polygon (gint32 image_ID,GimpChannelOps operation,gint num_segs,const gdouble * segs)
name|gimp_image_select_polygon
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|,
name|gint
name|num_segs
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|segs
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|GIMP_TYPE_CHANNEL_OPS
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|GIMP_TYPE_FLOAT_ARRAY
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|operation
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|num_segs
argument_list|)
expr_stmt|;
name|gimp_value_set_float_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|segs
argument_list|,
name|num_segs
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-select-polygon"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_select_item:  * @image_ID: The image.  * @operation: The desired operation with current selection.  * @item_ID: The item to render to the selection.  *  * Transforms the specified item into a selection  *  * This procedure renders the item's outline into the current selection  * of the image the item belongs to. What exactly the item's outline is  * depends on the item type: for layers, it's the layer's alpha  * channel, for vectors the vector's shape.  *  * This procedure is affected by the following context setters:  * gimp_context_set_antialias(), gimp_context_set_feather(),  * gimp_context_set_feather_radius().  *  * Returns: TRUE on success.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_select_item (gint32 image_ID,GimpChannelOps operation,gint32 item_ID)
name|gimp_image_select_item
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|,
name|gint32
name|item_ID
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|GIMP_TYPE_CHANNEL_OPS
argument_list|,
name|GIMP_TYPE_ITEM_ID
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|operation
argument_list|)
expr_stmt|;
name|gimp_value_set_item_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|item_ID
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-select-item"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

