begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpimageguides_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimpimageguides  * @title: gimpimageguides  * @short_description: Functions for manipulating an image's guides.  *  * Functions for manipulating an image's guides.  **/
end_comment

begin_comment
comment|/**  * gimp_image_add_hguide:  * @image: The image.  * @yposition: The guide's y-offset from top of image.  *  * Add a horizontal guide to an image.  *  * This procedure adds a horizontal guide to an image. It takes the  * input image and the y-position of the new guide as parameters. It  * returns the guide ID of the new guide.  *  * Returns: The new guide.  **/
end_comment

begin_function
name|guint
DECL|function|gimp_image_add_hguide (GimpImage * image,gint yposition)
name|gimp_image_add_hguide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|yposition
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
name|guint
name|guide
init|=
literal|0
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|gimp_image_get_id
argument_list|(
name|image
argument_list|)
argument_list|,
name|G_TYPE_INT
argument_list|,
name|yposition
argument_list|,
name|G_TYPE_NONE
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
literal|"gimp-image-add-hguide"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-image-add-hguide"
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
name|guide
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
name|guide
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_image_add_hguide: (skip)  * @image_ID: The image.  * @yposition: The guide's y-offset from top of image.  *  * Add a horizontal guide to an image.  *  * This procedure adds a horizontal guide to an image. It takes the  * input image and the y-position of the new guide as parameters. It  * returns the guide ID of the new guide.  *  * Returns: The new guide.  **/
end_comment

begin_function
name|gint32
DECL|function|_gimp_image_add_hguide (gint32 image_ID,gint yposition)
name|_gimp_image_add_hguide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|yposition
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
name|guide_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|image_ID
argument_list|,
name|G_TYPE_INT
argument_list|,
name|yposition
argument_list|,
name|G_TYPE_NONE
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
literal|"gimp-image-add-hguide"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-image-add-hguide"
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
name|guide_ID
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
name|guide_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_add_vguide:  * @image: The image.  * @xposition: The guide's x-offset from left of image.  *  * Add a vertical guide to an image.  *  * This procedure adds a vertical guide to an image. It takes the input  * image and the x-position of the new guide as parameters. It returns  * the guide ID of the new guide.  *  * Returns: The new guide.  **/
end_comment

begin_function
name|guint
DECL|function|gimp_image_add_vguide (GimpImage * image,gint xposition)
name|gimp_image_add_vguide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|xposition
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
name|guint
name|guide
init|=
literal|0
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|gimp_image_get_id
argument_list|(
name|image
argument_list|)
argument_list|,
name|G_TYPE_INT
argument_list|,
name|xposition
argument_list|,
name|G_TYPE_NONE
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
literal|"gimp-image-add-vguide"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-image-add-vguide"
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
name|guide
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
name|guide
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_image_add_vguide: (skip)  * @image_ID: The image.  * @xposition: The guide's x-offset from left of image.  *  * Add a vertical guide to an image.  *  * This procedure adds a vertical guide to an image. It takes the input  * image and the x-position of the new guide as parameters. It returns  * the guide ID of the new guide.  *  * Returns: The new guide.  **/
end_comment

begin_function
name|gint32
DECL|function|_gimp_image_add_vguide (gint32 image_ID,gint xposition)
name|_gimp_image_add_vguide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|xposition
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
name|guide_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|image_ID
argument_list|,
name|G_TYPE_INT
argument_list|,
name|xposition
argument_list|,
name|G_TYPE_NONE
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
literal|"gimp-image-add-vguide"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-image-add-vguide"
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
name|guide_ID
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
name|guide_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_delete_guide:  * @image: The image.  * @guide: The ID of the guide to be removed.  *  * Deletes a guide from an image.  *  * This procedure takes an image and a guide ID as input and removes  * the specified guide from the specified image.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_delete_guide (GimpImage * image,guint guide)
name|gimp_image_delete_guide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|guint
name|guide
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
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|gimp_image_get_id
argument_list|(
name|image
argument_list|)
argument_list|,
name|G_TYPE_UINT
argument_list|,
name|guide
argument_list|,
name|G_TYPE_NONE
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
literal|"gimp-image-delete-guide"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-image-delete-guide"
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
comment|/**  * _gimp_image_delete_guide: (skip)  * @image_ID: The image.  * @guide_ID: The ID of the guide to be removed.  *  * Deletes a guide from an image.  *  * This procedure takes an image and a guide ID as input and removes  * the specified guide from the specified image.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_image_delete_guide (gint32 image_ID,gint32 guide_ID)
name|_gimp_image_delete_guide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
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
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|image_ID
argument_list|,
name|G_TYPE_UINT
argument_list|,
name|guide_ID
argument_list|,
name|G_TYPE_NONE
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
literal|"gimp-image-delete-guide"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-image-delete-guide"
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
comment|/**  * gimp_image_find_next_guide:  * @image: The image.  * @guide: The ID of the current guide (0 if first invocation).  *  * Find next guide on an image.  *  * This procedure takes an image and a guide ID as input and finds the  * guide ID of the successor of the given guide ID in the image's guide  * list. If the supplied guide ID is 0, the procedure will return the  * first Guide. The procedure will return 0 if given the final guide ID  * as an argument or the image has no guides.  *  * Returns: The next guide's ID.  **/
end_comment

begin_function
name|guint
DECL|function|gimp_image_find_next_guide (GimpImage * image,guint guide)
name|gimp_image_find_next_guide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|guint
name|guide
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
name|guint
name|next_guide
init|=
literal|0
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|gimp_image_get_id
argument_list|(
name|image
argument_list|)
argument_list|,
name|G_TYPE_UINT
argument_list|,
name|guide
argument_list|,
name|G_TYPE_NONE
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
literal|"gimp-image-find-next-guide"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-image-find-next-guide"
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
name|next_guide
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
name|next_guide
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_image_find_next_guide: (skip)  * @image_ID: The image.  * @guide_ID: The ID of the current guide (0 if first invocation).  *  * Find next guide on an image.  *  * This procedure takes an image and a guide ID as input and finds the  * guide ID of the successor of the given guide ID in the image's guide  * list. If the supplied guide ID is 0, the procedure will return the  * first Guide. The procedure will return 0 if given the final guide ID  * as an argument or the image has no guides.  *  * Returns: The next guide's ID.  **/
end_comment

begin_function
name|gint32
DECL|function|_gimp_image_find_next_guide (gint32 image_ID,gint32 guide_ID)
name|_gimp_image_find_next_guide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
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
name|next_guide_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|image_ID
argument_list|,
name|G_TYPE_UINT
argument_list|,
name|guide_ID
argument_list|,
name|G_TYPE_NONE
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
literal|"gimp-image-find-next-guide"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-image-find-next-guide"
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
name|next_guide_ID
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
name|next_guide_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_get_guide_orientation:  * @image: The image.  * @guide: The guide.  *  * Get orientation of a guide on an image.  *  * This procedure takes an image and a guide ID as input and returns  * the orientations of the guide.  *  * Returns: The guide's orientation.  **/
end_comment

begin_function
name|GimpOrientationType
DECL|function|gimp_image_get_guide_orientation (GimpImage * image,guint guide)
name|gimp_image_get_guide_orientation
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|guint
name|guide
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
name|GimpOrientationType
name|orientation
init|=
name|GIMP_ORIENTATION_UNKNOWN
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|gimp_image_get_id
argument_list|(
name|image
argument_list|)
argument_list|,
name|G_TYPE_UINT
argument_list|,
name|guide
argument_list|,
name|G_TYPE_NONE
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
literal|"gimp-image-get-guide-orientation"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-image-get-guide-orientation"
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
name|orientation
operator|=
name|g_value_get_enum
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
name|orientation
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_image_get_guide_orientation: (skip)  * @image_ID: The image.  * @guide_ID: The guide.  *  * Get orientation of a guide on an image.  *  * This procedure takes an image and a guide ID as input and returns  * the orientations of the guide.  *  * Returns: The guide's orientation.  **/
end_comment

begin_function
name|GimpOrientationType
DECL|function|_gimp_image_get_guide_orientation (gint32 image_ID,gint32 guide_ID)
name|_gimp_image_get_guide_orientation
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
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
name|GimpOrientationType
name|orientation
init|=
name|GIMP_ORIENTATION_UNKNOWN
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|image_ID
argument_list|,
name|G_TYPE_UINT
argument_list|,
name|guide_ID
argument_list|,
name|G_TYPE_NONE
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
literal|"gimp-image-get-guide-orientation"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-image-get-guide-orientation"
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
name|orientation
operator|=
name|g_value_get_enum
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
name|orientation
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_get_guide_position:  * @image: The image.  * @guide: The guide.  *  * Get position of a guide on an image.  *  * This procedure takes an image and a guide ID as input and returns  * the position of the guide relative to the top or left of the image.  *  * Returns: The guide's position relative to top or left of image.  **/
end_comment

begin_function
name|gint
DECL|function|gimp_image_get_guide_position (GimpImage * image,guint guide)
name|gimp_image_get_guide_position
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|guint
name|guide
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
name|position
init|=
name|G_MININT
comment|/* GIMP_GUIDE_POSITION_UNDEFINED */
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|gimp_image_get_id
argument_list|(
name|image
argument_list|)
argument_list|,
name|G_TYPE_UINT
argument_list|,
name|guide
argument_list|,
name|G_TYPE_NONE
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
literal|"gimp-image-get-guide-position"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-image-get-guide-position"
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
name|position
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
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|position
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_image_get_guide_position: (skip)  * @image_ID: The image.  * @guide_ID: The guide.  *  * Get position of a guide on an image.  *  * This procedure takes an image and a guide ID as input and returns  * the position of the guide relative to the top or left of the image.  *  * Returns: The guide's position relative to top or left of image.  **/
end_comment

begin_function
name|gint
DECL|function|_gimp_image_get_guide_position (gint32 image_ID,gint32 guide_ID)
name|_gimp_image_get_guide_position
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
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
name|position
init|=
name|G_MININT
comment|/* GIMP_GUIDE_POSITION_UNDEFINED */
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|image_ID
argument_list|,
name|G_TYPE_UINT
argument_list|,
name|guide_ID
argument_list|,
name|G_TYPE_NONE
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
literal|"gimp-image-get-guide-position"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-image-get-guide-position"
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
name|position
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
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|position
return|;
block|}
end_function

end_unit

