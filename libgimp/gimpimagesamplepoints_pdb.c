begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpimagesamplepoints_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimpimagesamplepoints  * @title: gimpimagesamplepoints  * @short_description: Functions for manipulating an image's sample points.  *  * Functions for manipulating an image's sample points.  **/
end_comment

begin_comment
comment|/**  * gimp_image_add_sample_point:  * @image_ID: The image.  * @position_x: The guide'sample points x-offset from left of image.  * @position_y: The guide'sample points y-offset from top of image.  *  * Add a sample point to an image.  *  * This procedure adds a sample point to an image. It takes the input  * image and the position of the new sample points as parameters. It  * returns the sample point ID of the new sample point.  *  * Returns: The new sample point.  *  * Since: 2.10  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_image_add_sample_point (gint32 image_ID,gint position_x,gint position_y)
name|gimp_image_add_sample_point
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|position_x
parameter_list|,
name|gint
name|position_y
parameter_list|)
block|{
name|GimpPDB
modifier|*
name|pdb
init|=
name|gimp_get_pdb
argument_list|()
decl_stmt|;
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint32
name|sample_point_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|GIMP_TYPE_INT32
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
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|position_x
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
name|position_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb
condition|)
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|pdb
argument_list|,
literal|"gimp-image-add-sample-point"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-add-sample-point"
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
condition|)
name|sample_point_ID
operator|=
name|g_value_get_uint
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|sample_point_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_delete_sample_point:  * @image_ID: The image.  * @sample_point_ID: The ID of the sample point to be removed.  *  * Deletes a sample point from an image.  *  * This procedure takes an image and a sample point ID as input and  * removes the specified sample point from the specified image.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_delete_sample_point (gint32 image_ID,gint32 sample_point_ID)
name|gimp_image_delete_sample_point
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|sample_point_ID
parameter_list|)
block|{
name|GimpPDB
modifier|*
name|pdb
init|=
name|gimp_get_pdb
argument_list|()
decl_stmt|;
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
name|GIMP_TYPE_INT32
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
name|g_value_set_uint
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|sample_point_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb
condition|)
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|pdb
argument_list|,
literal|"gimp-image-delete-sample-point"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-delete-sample-point"
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
comment|/**  * gimp_image_find_next_sample_point:  * @image_ID: The image.  * @sample_point_ID: The ID of the current sample point (0 if first invocation).  *  * Find next sample point on an image.  *  * This procedure takes an image and a sample point ID as input and  * finds the sample point ID of the successor of the given sample point  * ID in the image's sample point list. If the supplied sample point ID  * is 0, the procedure will return the first sample point. The  * procedure will return 0 if given the final sample point ID as an  * argument or the image has no sample points.  *  * Returns: The next sample point's ID.  *  * Since: 2.10  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_image_find_next_sample_point (gint32 image_ID,gint32 sample_point_ID)
name|gimp_image_find_next_sample_point
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|sample_point_ID
parameter_list|)
block|{
name|GimpPDB
modifier|*
name|pdb
init|=
name|gimp_get_pdb
argument_list|()
decl_stmt|;
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint32
name|next_sample_point_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|GIMP_TYPE_INT32
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
name|g_value_set_uint
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|sample_point_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb
condition|)
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|pdb
argument_list|,
literal|"gimp-image-find-next-sample-point"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-find-next-sample-point"
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
condition|)
name|next_sample_point_ID
operator|=
name|g_value_get_uint
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|next_sample_point_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_get_sample_point_position:  * @image_ID: The image.  * @sample_point_ID: The guide.  * @position_y: (out): The sample points's position relative to top of image.  *  * Get position of a sample point on an image.  *  * This procedure takes an image and a sample point ID as input and  * returns the position of the sample point relative to the top and  * left of the image.  *  * Returns: The sample points's position relative to top of image.  *  * Since: 2.10  **/
end_comment

begin_function
name|gint
DECL|function|gimp_image_get_sample_point_position (gint32 image_ID,gint32 sample_point_ID,gint * position_y)
name|gimp_image_get_sample_point_position
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|sample_point_ID
parameter_list|,
name|gint
modifier|*
name|position_y
parameter_list|)
block|{
name|GimpPDB
modifier|*
name|pdb
init|=
name|gimp_get_pdb
argument_list|()
decl_stmt|;
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|position_x
init|=
name|G_MININT
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|GIMP_TYPE_INT32
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
name|g_value_set_uint
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|sample_point_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb
condition|)
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|pdb
argument_list|,
literal|"gimp-image-get-sample-point-position"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-get-sample-point-position"
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
condition|)
block|{
name|position_x
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|position_y
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|position_x
return|;
block|}
end_function

end_unit

