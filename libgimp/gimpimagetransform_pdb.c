begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpimagetransform_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimpimagetransform  * @title: gimpimagetransform  * @short_description: Transformations on images.  *  * Operations to scale, resize, crop, flip and rotate images.  **/
end_comment

begin_comment
comment|/**  * gimp_image_resize:  * @image: The image.  * @new_width: New image width.  * @new_height: New image height.  * @offx: x offset between upper left corner of old and new images: (new - old).  * @offy: y offset between upper left corner of old and new images: (new - old).  *  * Resize the image to the specified extents.  *  * This procedure resizes the image so that it's new width and height  * are equal to the supplied parameters. Offsets are also provided  * which describe the position of the previous image's content. All  * channels within the image are resized according to the specified  * parameters; this includes the image selection mask. All layers  * within the image are repositioned according to the specified  * offsets.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_resize (GimpImage * image,gint new_width,gint new_height,gint offx,gint offy)
name|gimp_image_resize
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
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
name|new_width
argument_list|,
name|G_TYPE_INT
argument_list|,
name|new_height
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
literal|"gimp-image-resize"
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
comment|/**  * gimp_image_resize_to_layers:  * @image: The image.  *  * Resize the image to fit all layers.  *  * This procedure resizes the image to the bounding box of all layers  * of the image. All channels within the image are resized to the new  * size; this includes the image selection mask. All layers within the  * image are repositioned to the new image area.  *  * Returns: TRUE on success.  *  * Since: 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_resize_to_layers (GimpImage * image)
name|gimp_image_resize_to_layers
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
literal|"gimp-image-resize-to-layers"
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
comment|/**  * gimp_image_scale:  * @image: The image.  * @new_width: New image width.  * @new_height: New image height.  *  * Scale the image using the default interpolation method.  *  * This procedure scales the image so that its new width and height are  * equal to the supplied parameters. All layers and channels within the  * image are scaled according to the specified parameters; this  * includes the image selection mask. The interpolation method used can  * be set with gimp_context_set_interpolation().  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_scale (GimpImage * image,gint new_width,gint new_height)
name|gimp_image_scale
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
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
name|new_width
argument_list|,
name|G_TYPE_INT
argument_list|,
name|new_height
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
literal|"gimp-image-scale"
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
comment|/**  * gimp_image_crop:  * @image: The image.  * @new_width: New image width: (0< new_width<= width).  * @new_height: New image height: (0< new_height<= height).  * @offx: X offset: (0<= offx<= (width - new_width)).  * @offy: Y offset: (0<= offy<= (height - new_height)).  *  * Crop the image to the specified extents.  *  * This procedure crops the image so that it's new width and height are  * equal to the supplied parameters. Offsets are also provided which  * describe the position of the previous image's content. All channels  * and layers within the image are cropped to the new image extents;  * this includes the image selection mask. If any parameters are out of  * range, an error is returned.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_crop (GimpImage * image,gint new_width,gint new_height,gint offx,gint offy)
name|gimp_image_crop
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
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
name|new_width
argument_list|,
name|G_TYPE_INT
argument_list|,
name|new_height
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
literal|"gimp-image-crop"
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
comment|/**  * gimp_image_flip:  * @image: The image.  * @flip_type: Type of flip.  *  * Flips the image horizontally or vertically.  *  * This procedure flips (mirrors) the image.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_flip (GimpImage * image,GimpOrientationType flip_type)
name|gimp_image_flip
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpOrientationType
name|flip_type
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
name|GIMP_TYPE_ORIENTATION_TYPE
argument_list|,
name|flip_type
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
literal|"gimp-image-flip"
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
comment|/**  * gimp_image_rotate:  * @image: The image.  * @rotate_type: Angle of rotation.  *  * Rotates the image by the specified degrees.  *  * This procedure rotates the image.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_rotate (GimpImage * image,GimpRotationType rotate_type)
name|gimp_image_rotate
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpRotationType
name|rotate_type
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
name|GIMP_TYPE_ROTATION_TYPE
argument_list|,
name|rotate_type
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
literal|"gimp-image-rotate"
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

end_unit

