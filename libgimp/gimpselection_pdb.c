begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpselection_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimpselection  * @title: gimpselection  * @short_description: Functions for manipulating selections.  *  * Functions for manipulating selections.  **/
end_comment

begin_comment
comment|/**  * gimp_selection_bounds:  * @image: The image.  * @non_empty: (out): TRUE if there is a selection.  * @x1: (out): x coordinate of upper left corner of selection bounds.  * @y1: (out): y coordinate of upper left corner of selection bounds.  * @x2: (out): x coordinate of lower right corner of selection bounds.  * @y2: (out): y coordinate of lower right corner of selection bounds.  *  * Find the bounding box of the current selection.  *  * This procedure returns whether there is a selection for the  * specified image. If there is one, the upper left and lower right  * corners of the bounding box are returned. These coordinates are  * relative to the image. Please note that the pixel specified by the  * lower right coordinate of the bounding box is not part of the  * selection. The selection ends at the upper left corner of this  * pixel. This means the width of the selection can be calculated as  * (x2 - x1), its height as (y2 - y1).  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_bounds (GimpImage * image,gboolean * non_empty,gint * x1,gint * y1,gint * x2,gint * y2)
name|gimp_selection_bounds
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
modifier|*
name|non_empty
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
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
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-bounds"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
operator|*
name|non_empty
operator|=
name|FALSE
expr_stmt|;
operator|*
name|x1
operator|=
literal|0
expr_stmt|;
operator|*
name|y1
operator|=
literal|0
expr_stmt|;
operator|*
name|x2
operator|=
literal|0
expr_stmt|;
operator|*
name|y2
operator|=
literal|0
expr_stmt|;
name|success
operator|=
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
operator|*
name|non_empty
operator|=
name|GIMP_VALUES_GET_BOOLEAN
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
expr_stmt|;
operator|*
name|x1
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
expr_stmt|;
operator|*
name|y1
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|return_vals
argument_list|,
literal|3
argument_list|)
expr_stmt|;
operator|*
name|x2
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|return_vals
argument_list|,
literal|4
argument_list|)
expr_stmt|;
operator|*
name|y2
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|return_vals
argument_list|,
literal|5
argument_list|)
expr_stmt|;
block|}
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
comment|/**  * gimp_selection_value:  * @image: The image.  * @x: x coordinate of value.  * @y: y coordinate of value.  *  * Find the value of the selection at the specified coordinates.  *  * This procedure returns the value of the selection at the specified  * coordinates. If the coordinates lie out of bounds, 0 is returned.  *  * Returns: Value of the selection.  **/
end_comment

begin_function
name|gint
DECL|function|gimp_selection_value (GimpImage * image,gint x,gint y)
name|gimp_selection_value
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
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
name|gint
name|value
init|=
literal|0
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_INT
argument_list|,
name|x
argument_list|,
name|G_TYPE_INT
argument_list|,
name|y
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-value"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|value
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|value
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_selection_is_empty:  * @image: The image.  *  * Determine whether the selection is empty.  *  * This procedure returns TRUE if the selection for the specified image  * is empty.  *  * Returns: Is the selection empty?  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_is_empty (GimpImage * image)
name|gimp_selection_is_empty
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|is_empty
init|=
name|FALSE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-is-empty"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|is_empty
operator|=
name|GIMP_VALUES_GET_BOOLEAN
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|is_empty
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_selection_translate:  * @image: The image.  * @offx: x offset for translation.  * @offy: y offset for translation.  *  * Translate the selection by the specified offsets.  *  * This procedure actually translates the selection for the specified  * image by the specified offsets. Regions that are translated from  * beyond the bounds of the image are set to empty. Valid regions of  * the selection which are translated beyond the bounds of the image  * because of this call are lost.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_translate (GimpImage * image,gint offx,gint offy)
name|gimp_selection_translate
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
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
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_INT
argument_list|,
name|offx
argument_list|,
name|G_TYPE_INT
argument_list|,
name|offy
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-translate"
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
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
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
comment|/**  * _gimp_selection_float:  * @drawable: The drawable from which to float selection.  * @offx: x offset for translation.  * @offy: y offset for translation.  *  * Float the selection from the specified drawable with initial offsets  * as specified.  *  * This procedure determines the region of the specified drawable that  * lies beneath the current selection. The region is then cut from the  * drawable and the resulting data is made into a new layer which is  * instantiated as a floating selection. The offsets allow initial  * positioning of the new floating selection.  *  * Returns: (transfer none): The floated layer.  **/
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|_gimp_selection_float (GimpDrawable * drawable,gint offx,gint offy)
name|_gimp_selection_float
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
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
name|GimpLayer
modifier|*
name|layer
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_DRAWABLE
argument_list|,
name|drawable
argument_list|,
name|G_TYPE_INT
argument_list|,
name|offx
argument_list|,
name|G_TYPE_INT
argument_list|,
name|offy
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-float"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|layer
operator|=
name|GIMP_VALUES_GET_LAYER
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_selection_invert:  * @image: The image.  *  * Invert the selection mask.  *  * This procedure inverts the selection mask. For every pixel in the  * selection channel, its new value is calculated as (255 - old-value).  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_invert (GimpImage * image)
name|gimp_selection_invert
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-invert"
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
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
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
comment|/**  * gimp_selection_sharpen:  * @image: The image.  *  * Sharpen the selection mask.  *  * This procedure sharpens the selection mask. For every pixel in the  * selection channel, if the value is&gt; 127, the new pixel is  * assigned a value of 255. This removes any \"anti-aliasing\" that  * might exist in the selection mask's boundary.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_sharpen (GimpImage * image)
name|gimp_selection_sharpen
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-sharpen"
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
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
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
comment|/**  * gimp_selection_all:  * @image: The image.  *  * Select all of the image.  *  * This procedure sets the selection mask to completely encompass the  * image. Every pixel in the selection channel is set to 255.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_all (GimpImage * image)
name|gimp_selection_all
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-all"
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
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
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
comment|/**  * gimp_selection_none:  * @image: The image.  *  * Deselect the entire image.  *  * This procedure deselects the entire image. Every pixel in the  * selection channel is set to 0.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_none (GimpImage * image)
name|gimp_selection_none
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-none"
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
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
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
comment|/**  * gimp_selection_feather:  * @image: The image.  * @radius: Radius of feather (in pixels).  *  * Feather the image's selection  *  * This procedure feathers the selection. Feathering is implemented  * using a gaussian blur.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_feather (GimpImage * image,gdouble radius)
name|gimp_selection_feather
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
name|radius
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
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|radius
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-feather"
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
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
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
comment|/**  * gimp_selection_border:  * @image: The image.  * @radius: Radius of border (in pixels).  *  * Border the image's selection  *  * This procedure borders the selection. Bordering creates a new  * selection which is defined along the boundary of the previous  * selection at every point within the specified radius.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_border (GimpImage * image,gint radius)
name|gimp_selection_border
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|radius
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
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_INT
argument_list|,
name|radius
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-border"
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
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
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
comment|/**  * gimp_selection_grow:  * @image: The image.  * @steps: Steps of grow (in pixels).  *  * Grow the image's selection  *  * This procedure grows the selection. Growing involves expanding the  * boundary in all directions by the specified pixel amount.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_grow (GimpImage * image,gint steps)
name|gimp_selection_grow
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|steps
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
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_INT
argument_list|,
name|steps
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-grow"
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
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
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
comment|/**  * gimp_selection_shrink:  * @image: The image.  * @steps: Steps of shrink (in pixels).  *  * Shrink the image's selection  *  * This procedure shrinks the selection. Shrinking involves trimming  * the existing selection boundary on all sides by the specified number  * of pixels.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_shrink (GimpImage * image,gint steps)
name|gimp_selection_shrink
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|steps
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
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_INT
argument_list|,
name|steps
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-shrink"
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
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
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
comment|/**  * gimp_selection_flood:  * @image: The image.  *  * Remove holes from the image's selection  *  * This procedure removes holes from the selection, that can come from  * selecting a patchy area with the Fuzzy Select Tool. In technical  * terms this procedure floods the selection. See the Algorithms page  * in the developer wiki for details.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_flood (GimpImage * image)
name|gimp_selection_flood
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-flood"
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
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
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
comment|/**  * gimp_selection_save:  * @image: The image.  *  * Copy the selection mask to a new channel.  *  * This procedure copies the selection mask and stores the content in a  * new channel. The new channel is automatically inserted into the  * image's list of channels.  *  * Returns: (transfer none): The new channel.  **/
end_comment

begin_function
name|GimpChannel
modifier|*
DECL|function|gimp_selection_save (GimpImage * image)
name|gimp_selection_save
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|GimpChannel
modifier|*
name|channel
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-selection-save"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|channel
operator|=
name|GIMP_VALUES_GET_CHANNEL
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|channel
return|;
block|}
end_function

end_unit

