begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpselection_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
comment|/**  * gimp_selection_bounds:  * @image_ID: The image.  * @non_empty: True if there is a selection.  * @x1: x coordinate of upper left corner of selection bounds.  * @y1: y coordinate of upper left corner of selection bounds.  * @x2: x coordinate of lower right corner of selection bounds.  * @y2: y coordinate of lower right corner of selection bounds.  *  * Find the bounding box of the current selection.  *  * This procedure returns whether there is a selection for the  * specified image. If there is one, the upper left and lower right  * corners of the bounding box are returned. These coordinates are  * relative to the image. Please note that the pixel specified by the  * lower righthand coordinate of the bounding box is not part of the  * selection. The selection ends at the upper left corner of this  * pixel. This means the width of the selection can be calculated as  * (x2 - x1), its height as (y2 - y1).  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_bounds (gint32 image_ID,gboolean * non_empty,gint * x1,gint * y1,gint * x2,gint * y2)
name|gimp_selection_bounds
parameter_list|(
name|gint32
name|image_ID
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
literal|"gimp_selection_bounds"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_END
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
name|non_empty
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|x1
operator|=
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|y1
operator|=
name|return_vals
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|x2
operator|=
name|return_vals
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|y2
operator|=
name|return_vals
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
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
comment|/**  * gimp_selection_value:  * @image_ID: The image.  * @x: x coordinate of value.  * @y: y coordinate of value.  *  * Find the value of the selection at the specified coordinates.  *  * This procedure returns the value of the selection at the specified  * coordinates. If the coordinates lie out of bounds, 0 is returned.  *  * Returns: Value of the selection.  */
end_comment

begin_function
name|gint
DECL|function|gimp_selection_value (gint32 image_ID,gint x,gint y)
name|gimp_selection_value
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
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
name|gint
name|value
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_selection_value"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|x
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|y
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
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
condition|)
name|value
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|value
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_selection_is_empty:  * @image_ID: The image.  *  * Determine whether the selection is empty.  *  * This procedure returns non-zero if the selection for the specified  * image is not empty.  *  * Returns: Is the selection empty?  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_is_empty (gint32 image_ID)
name|gimp_selection_is_empty
parameter_list|(
name|gint32
name|image_ID
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
name|is_empty
init|=
name|FALSE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_selection_is_empty"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
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
condition|)
name|is_empty
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|is_empty
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_selection_translate:  * @image_ID: The image.  * @offx: x offset for translation.  * @offy: y offset for translation.  *  * Translate the selection by the specified offsets.  *  * This procedure actually translates the selection for the specified  * image by the specified offsets. Regions that are translated from  * beyond the bounds of the image are set to empty. Valid regions of  * the selection which are translated beyond the bounds of the image  * because of this call are lost.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_translate (gint32 image_ID,gint offx,gint offy)
name|gimp_selection_translate
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
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
literal|"gimp_selection_translate"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|offx
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|offy
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
comment|/**  * _gimp_selection_float:  * @drawable_ID: The drawable from which to float selection.  * @offx: x offset for translation.  * @offy: y offset for translation.  *  * Float the selection from the specified drawable with initial offsets  * as specified.  *  * This procedure determines the region of the specified drawable that  * lies beneath the current selection. The region is then cut from the  * drawable and the resulting data is made into a new layer which is  * instantiated as a floating selection. The offsets allow initial  * positioning of the new floating selection.  *  * Returns: The floated layer.  */
end_comment

begin_function
name|gint32
DECL|function|_gimp_selection_float (gint32 drawable_ID,gint offx,gint offy)
name|_gimp_selection_float
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|layer_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_selection_float"
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
name|offx
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|offy
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
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
condition|)
name|layer_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_layer
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|layer_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_selection_clear:  * @image_ID: The image.  *  * Set the selection to none, clearing all previous content.  *  * This procedure sets the selection mask to empty, assigning the value  * 0 to every pixel in the selection channel.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_clear (gint32 image_ID)
name|gimp_selection_clear
parameter_list|(
name|gint32
name|image_ID
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
literal|"gimp_selection_clear"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
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
comment|/**  * gimp_selection_invert:  * @image_ID: The image.  *  * Invert the selection mask.  *  * This procedure inverts the selection mask. For every pixel in the  * selection channel, its new value is calculated as (255 - old_value).  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_invert (gint32 image_ID)
name|gimp_selection_invert
parameter_list|(
name|gint32
name|image_ID
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
literal|"gimp_selection_invert"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
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
comment|/**  * gimp_selection_sharpen:  * @image_ID: The image.  *  * Sharpen the selection mask.  *  * This procedure sharpens the selection mask. For every pixel in the  * selection channel, if the value is> 0, the new pixel is assigned a  * value of 255. This removes any \"anti-aliasing\" that might exist in  * the selection mask's boundary.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_sharpen (gint32 image_ID)
name|gimp_selection_sharpen
parameter_list|(
name|gint32
name|image_ID
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
literal|"gimp_selection_sharpen"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
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
comment|/**  * gimp_selection_all:  * @image_ID: The image.  *  * Select all of the image.  *  * This procedure sets the selection mask to completely encompass the  * image. Every pixel in the selection channel is set to 255.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_all (gint32 image_ID)
name|gimp_selection_all
parameter_list|(
name|gint32
name|image_ID
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
literal|"gimp_selection_all"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
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
comment|/**  * gimp_selection_none:  * @image_ID: The image.  *  * Deselect the entire image.  *  * This procedure deselects the entire image. Every pixel in the  * selection channel is set to 0.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_none (gint32 image_ID)
name|gimp_selection_none
parameter_list|(
name|gint32
name|image_ID
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
literal|"gimp_selection_none"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
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
comment|/**  * gimp_selection_feather:  * @image_ID: The image.  * @radius: Radius of feather (in pixels).  *  * Feather the image's selection  *  * This procedure feathers the selection. Feathering is implemented  * using a gaussian blur.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_feather (gint32 image_ID,gdouble radius)
name|gimp_selection_feather
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gdouble
name|radius
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
literal|"gimp_selection_feather"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|radius
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
comment|/**  * gimp_selection_border:  * @image_ID: The image.  * @radius: Radius of border (in pixels).  *  * Border the image's selection  *  * This procedure borders the selection. Bordering creates a new  * selection which is defined along the boundary of the previous  * selection at every point within the specified radius.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_border (gint32 image_ID,gint radius)
name|gimp_selection_border
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|radius
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
literal|"gimp_selection_border"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|radius
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
comment|/**  * gimp_selection_grow:  * @image_ID: The image.  * @steps: Steps of grow (in pixels).  *  * Grow the image's selection  *  * This procedure grows the selection. Growing involves expanding the  * boundary in all directions by the specified pixel amount.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_grow (gint32 image_ID,gint steps)
name|gimp_selection_grow
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|steps
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
literal|"gimp_selection_grow"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|steps
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
comment|/**  * gimp_selection_shrink:  * @image_ID: The image.  * @radius: Radius of shrink (in pixels).  *  * Shrink the image's selection  *  * This procedure shrinks the selection. Shrinking invovles trimming  * the existing selection boundary on all sides by the specified number  * of pixels.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_shrink (gint32 image_ID,gint radius)
name|gimp_selection_shrink
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|radius
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
literal|"gimp_selection_shrink"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|radius
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
comment|/**  * gimp_selection_layer_alpha:  * @layer_ID: Layer with alpha.  *  * Transfer the specified layer's alpha channel to the selection mask.  *  * This procedure requires a layer with an alpha channel. The alpha  * channel information is used to create a selection mask such that for  * any pixel in the image defined in the specified layer, that layer  * pixel's alpha value is transferred to the selection mask. If the  * layer is undefined at a particular image pixel, the associated  * selection mask value is set to 0.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_layer_alpha (gint32 layer_ID)
name|gimp_selection_layer_alpha
parameter_list|(
name|gint32
name|layer_ID
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
literal|"gimp_selection_layer_alpha"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_LAYER
argument_list|,
name|layer_ID
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
comment|/**  * gimp_selection_load:  * @channel_ID: The channel.  *  * Transfer the specified channel to the selection mask.  *  * This procedure loads the specified channel into the selection mask.  * This essentially involves a copy of the channel's content in to the  * selection mask. Therefore, the channel must have the same width and  * height of the image, or an error is returned.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_load (gint32 channel_ID)
name|gimp_selection_load
parameter_list|(
name|gint32
name|channel_ID
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
literal|"gimp_selection_load"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_CHANNEL
argument_list|,
name|channel_ID
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
comment|/**  * gimp_selection_save:  * @image_ID: The image.  *  * Copy the selection mask to a new channel.  *  * This procedure copies the selection mask and stores the content in a  * new channel. The new channel is automatically inserted into the  * image's list of channels.  *  * Returns: The new channel.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_selection_save (gint32 image_ID)
name|gimp_selection_save
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|channel_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_selection_save"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
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
condition|)
name|channel_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_channel
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|channel_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_selection_combine:  * @channel_ID: The channel.  * @operation: The selection operation.  *  * Combines the specified channel with the selection mask.  *  * This procedure combines the specified channel into the selection  * mask. It essentially involves a transfer of the channel's content  * into the selection mask. Therefore, the channel must have the same  * width and height of the image, or an error is returned.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_selection_combine (gint32 channel_ID,GimpChannelOps operation)
name|gimp_selection_combine
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
name|GimpChannelOps
name|operation
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
literal|"gimp_selection_combine"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_CHANNEL
argument_list|,
name|channel_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|operation
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

