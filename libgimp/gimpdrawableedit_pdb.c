begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpdrawableedit_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimpdrawableedit  * @title: gimpdrawableedit  * @short_description: Drawable edit functions (clear, fill, gradient, stroke etc.)  *  * Drawable edit functions (clear, fill, gradient, stroke etc.)  **/
end_comment

begin_comment
comment|/**  * gimp_drawable_edit_clear:  * @drawable_ID: The drawable to clear from.  *  * Clear selected area of drawable.  *  * This procedure clears the specified drawable. If the drawable has an  * alpha channel, the cleared pixels will become transparent. If the  * drawable does not have an alpha channel, cleared pixels will be set  * to the background color. This procedure only affects regions within  * a selection if there is a selection active.  *  * This procedure is affected by the following context setters:  * gimp_context_set_background().  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_edit_clear (gint32 drawable_ID)
name|gimp_drawable_edit_clear
parameter_list|(
name|gint32
name|drawable_ID
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
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-drawable-edit-clear"
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
comment|/**  * gimp_drawable_edit_fill:  * @drawable_ID: The drawable to fill to.  * @fill_type: The type of fill.  *  * Fill selected area of drawable.  *  * This procedure fills the specified drawable according to fill mode.  * This procedure only affects regions within a selection if there is a  * selection active. If you want to fill the whole drawable, regardless  * of the selection, use gimp_drawable_fill().  *  * This procedure is affected by the following context setters:  * gimp_context_set_opacity(), gimp_context_set_paint_mode(),  * gimp_context_set_foreground(), gimp_context_set_background(),  * gimp_context_set_pattern().  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_edit_fill (gint32 drawable_ID,GimpFillType fill_type)
name|gimp_drawable_edit_fill
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpFillType
name|fill_type
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
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|G_TYPE_ENUM
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|drawable_ID
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
name|fill_type
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-drawable-edit-fill"
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
comment|/**  * gimp_drawable_edit_bucket_fill:  * @drawable_ID: The affected drawable.  * @fill_type: The type of fill.  * @x: The x coordinate of this bucket fill's application.  * @y: The y coordinate of this bucket fill's application.  *  * Fill the area by a seed fill starting at the specified coordinates.  *  * This procedure does a seed fill at the specified coordinates, using  * various parameters from the current context.  * In the case of merged sampling, the x and y coordinates are relative  * to the image's origin; otherwise, they are relative to the  * drawable's origin.  *  * This procedure is affected by the following context setters:  * gimp_context_set_opacity(), gimp_context_set_paint_mode(),  * gimp_context_set_foreground(), gimp_context_set_background(),  * gimp_context_set_pattern(), gimp_context_set_sample_threshold(),  * gimp_context_set_sample_merged(),  * gimp_context_set_sample_criterion(),  * gimp_context_set_diagonal_neighbors(), gimp_context_set_antialias().  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_edit_bucket_fill (gint32 drawable_ID,GimpFillType fill_type,gdouble x,gdouble y)
name|gimp_drawable_edit_bucket_fill
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpFillType
name|fill_type
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
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|G_TYPE_ENUM
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|drawable_ID
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
name|fill_type
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
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-drawable-edit-bucket-fill"
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
comment|/**  * gimp_drawable_edit_gradient_fill:  * @drawable_ID: The affected drawable.  * @gradient_type: The type of gradient.  * @offset: Offset relates to the starting and ending coordinates specified for the blend. This parameter is mode dependent.  * @supersample: Do adaptive supersampling.  * @supersample_max_depth: Maximum recursion levels for supersampling.  * @supersample_threshold: Supersampling threshold.  * @dither: Use dithering to reduce banding.  * @x1: The x coordinate of this gradient's starting point.  * @y1: The y coordinate of this gradient's starting point.  * @x2: The x coordinate of this gradient's ending point.  * @y2: The y coordinate of this gradient's ending point.  *  * Draw a gradient between the starting and ending coordinates with the  * specified gradient type.  *  * This tool requires information on the gradient type. It creates the  * specified variety of gradient using the starting and ending  * coordinates as defined for each gradient type. For shapeburst  * gradient types, the context's distance metric is also relevant and  * can be updated with gimp_context_set_distance_metric().  *  * This procedure is affected by the following context setters:  * gimp_context_set_opacity(), gimp_context_set_paint_mode(),  * gimp_context_set_foreground(), gimp_context_set_background(),  * gimp_context_set_gradient() and all gradient property settings,  * gimp_context_set_distance_metric().  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_edit_gradient_fill (gint32 drawable_ID,GimpGradientType gradient_type,gdouble offset,gboolean supersample,gint supersample_max_depth,gdouble supersample_threshold,gboolean dither,gdouble x1,gdouble y1,gdouble x2,gdouble y2)
name|gimp_drawable_edit_gradient_fill
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpGradientType
name|gradient_type
parameter_list|,
name|gdouble
name|offset
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|supersample_max_depth
parameter_list|,
name|gdouble
name|supersample_threshold
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
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|G_TYPE_ENUM
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_BOOLEAN
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
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|drawable_ID
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
name|gradient_type
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
name|offset
argument_list|)
expr_stmt|;
name|g_value_set_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|supersample
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|4
argument_list|)
argument_list|,
name|supersample_max_depth
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
name|supersample_threshold
argument_list|)
expr_stmt|;
name|g_value_set_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|6
argument_list|)
argument_list|,
name|dither
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
name|x1
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|8
argument_list|)
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|9
argument_list|)
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|10
argument_list|)
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-drawable-edit-gradient-fill"
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
comment|/**  * gimp_drawable_edit_stroke_selection:  * @drawable_ID: The drawable to stroke to.  *  * Stroke the current selection  *  * This procedure strokes the current selection, painting along the  * selection boundary with the active paint method and brush, or using  * a plain line with configurable properties. The paint is applied to  * the specified drawable regardless of the active selection.  *  * This procedure is affected by the following context setters:  * gimp_context_set_opacity(), gimp_context_set_paint_mode(),  * gimp_context_set_paint_method(), gimp_context_set_stroke_method(),  * gimp_context_set_foreground(), gimp_context_set_brush() and all  * brush property settings, gimp_context_set_gradient() and all  * gradient property settings, gimp_context_set_line_width() and all  * line property settings, gimp_context_set_antialias().  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_edit_stroke_selection (gint32 drawable_ID)
name|gimp_drawable_edit_stroke_selection
parameter_list|(
name|gint32
name|drawable_ID
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
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-drawable-edit-stroke-selection"
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
comment|/**  * gimp_drawable_edit_stroke_item:  * @drawable_ID: The drawable to stroke to.  * @item_ID: The item to stroke.  *  * Stroke the specified item  *  * This procedure strokes the specified item, painting along its  * outline (e.g. along a path, or along a channel's boundary), with the  * active paint method and brush, or using a plain line with  * configurable properties.  *  * This procedure is affected by the following context setters:  * gimp_context_set_opacity(), gimp_context_set_paint_mode(),  * gimp_context_set_paint_method(), gimp_context_set_stroke_method(),  * gimp_context_set_foreground(), gimp_context_set_brush() and all  * brush property settings, gimp_context_set_gradient() and all  * gradient property settings, gimp_context_set_line_width() and all  * line property settings, gimp_context_set_antialias().  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_edit_stroke_item (gint32 drawable_ID,gint32 item_ID)
name|gimp_drawable_edit_stroke_item
parameter_list|(
name|gint32
name|drawable_ID
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
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|GIMP_TYPE_ITEM_ID
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|gimp_value_set_item_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|item_ID
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-drawable-edit-stroke-item"
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

