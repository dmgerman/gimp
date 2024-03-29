begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpimagegrid_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimpimagegrid  * @title: gimpimagegrid  * @short_description: Functions manuipulating an image's grid.  *  * Functions manuipulating an image's grid.  **/
end_comment

begin_comment
comment|/**  * gimp_image_grid_get_spacing:  * @image: The image.  * @xspacing: (out): The image's grid horizontal spacing.  * @yspacing: (out): The image's grid vertical spacing.  *  * Gets the spacing of an image's grid.  *  * This procedure retrieves the horizontal and vertical spacing of an  * image's grid. It takes the image as parameter.  *  * Returns: TRUE on success.  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_grid_get_spacing (GimpImage * image,gdouble * xspacing,gdouble * yspacing)
name|gimp_image_grid_get_spacing
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
modifier|*
name|xspacing
parameter_list|,
name|gdouble
modifier|*
name|yspacing
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
literal|"gimp-image-grid-get-spacing"
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
name|xspacing
operator|=
literal|0.0
expr_stmt|;
operator|*
name|yspacing
operator|=
literal|0.0
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
name|xspacing
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
expr_stmt|;
operator|*
name|yspacing
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|return_vals
argument_list|,
literal|2
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
comment|/**  * gimp_image_grid_set_spacing:  * @image: The image.  * @xspacing: The image's grid horizontal spacing.  * @yspacing: The image's grid vertical spacing.  *  * Sets the spacing of an image's grid.  *  * This procedure sets the horizontal and vertical spacing of an  * image's grid.  *  * Returns: TRUE on success.  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_grid_set_spacing (GimpImage * image,gdouble xspacing,gdouble yspacing)
name|gimp_image_grid_set_spacing
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
name|xspacing
parameter_list|,
name|gdouble
name|yspacing
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
name|xspacing
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|yspacing
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
literal|"gimp-image-grid-set-spacing"
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
comment|/**  * gimp_image_grid_get_offset:  * @image: The image.  * @xoffset: (out): The image's grid horizontal offset.  * @yoffset: (out): The image's grid vertical offset.  *  * Gets the offset of an image's grid.  *  * This procedure retrieves the horizontal and vertical offset of an  * image's grid. It takes the image as parameter.  *  * Returns: TRUE on success.  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_grid_get_offset (GimpImage * image,gdouble * xoffset,gdouble * yoffset)
name|gimp_image_grid_get_offset
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
modifier|*
name|xoffset
parameter_list|,
name|gdouble
modifier|*
name|yoffset
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
literal|"gimp-image-grid-get-offset"
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
name|xoffset
operator|=
literal|0.0
expr_stmt|;
operator|*
name|yoffset
operator|=
literal|0.0
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
name|xoffset
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
expr_stmt|;
operator|*
name|yoffset
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|return_vals
argument_list|,
literal|2
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
comment|/**  * gimp_image_grid_set_offset:  * @image: The image.  * @xoffset: The image's grid horizontal offset.  * @yoffset: The image's grid vertical offset.  *  * Sets the offset of an image's grid.  *  * This procedure sets the horizontal and vertical offset of an image's  * grid.  *  * Returns: TRUE on success.  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_grid_set_offset (GimpImage * image,gdouble xoffset,gdouble yoffset)
name|gimp_image_grid_set_offset
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
name|xoffset
parameter_list|,
name|gdouble
name|yoffset
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
name|xoffset
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|yoffset
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
literal|"gimp-image-grid-set-offset"
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
comment|/**  * gimp_image_grid_get_foreground_color:  * @image: The image.  * @fgcolor: (out caller-allocates): The image's grid foreground color.  *  * Sets the foreground color of an image's grid.  *  * This procedure gets the foreground color of an image's grid.  *  * Returns: TRUE on success.  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_grid_get_foreground_color (GimpImage * image,GimpRGB * fgcolor)
name|gimp_image_grid_get_foreground_color
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpRGB
modifier|*
name|fgcolor
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
literal|"gimp-image-grid-get-foreground-color"
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
if|if
condition|(
name|success
condition|)
name|GIMP_VALUES_GET_RGB
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|,
operator|&
operator|*
name|fgcolor
argument_list|)
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
comment|/**  * gimp_image_grid_set_foreground_color:  * @image: The image.  * @fgcolor: The new foreground color.  *  * Gets the foreground color of an image's grid.  *  * This procedure sets the foreground color of an image's grid.  *  * Returns: TRUE on success.  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_grid_set_foreground_color (GimpImage * image,const GimpRGB * fgcolor)
name|gimp_image_grid_set_foreground_color
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|fgcolor
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
name|GIMP_TYPE_RGB
argument_list|,
name|fgcolor
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
literal|"gimp-image-grid-set-foreground-color"
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
comment|/**  * gimp_image_grid_get_background_color:  * @image: The image.  * @bgcolor: (out caller-allocates): The image's grid background color.  *  * Sets the background color of an image's grid.  *  * This procedure gets the background color of an image's grid.  *  * Returns: TRUE on success.  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_grid_get_background_color (GimpImage * image,GimpRGB * bgcolor)
name|gimp_image_grid_get_background_color
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpRGB
modifier|*
name|bgcolor
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
literal|"gimp-image-grid-get-background-color"
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
if|if
condition|(
name|success
condition|)
name|GIMP_VALUES_GET_RGB
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|,
operator|&
operator|*
name|bgcolor
argument_list|)
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
comment|/**  * gimp_image_grid_set_background_color:  * @image: The image.  * @bgcolor: The new background color.  *  * Gets the background color of an image's grid.  *  * This procedure sets the background color of an image's grid.  *  * Returns: TRUE on success.  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_grid_set_background_color (GimpImage * image,const GimpRGB * bgcolor)
name|gimp_image_grid_set_background_color
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|bgcolor
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
name|GIMP_TYPE_RGB
argument_list|,
name|bgcolor
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
literal|"gimp-image-grid-set-background-color"
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
comment|/**  * gimp_image_grid_get_style:  * @image: The image.  *  * Gets the style of an image's grid.  *  * This procedure retrieves the style of an image's grid.  *  * Returns: The image's grid style.  *  * Since: 2.4  **/
end_comment

begin_function
name|GimpGridStyle
DECL|function|gimp_image_grid_get_style (GimpImage * image)
name|gimp_image_grid_get_style
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
name|GimpGridStyle
name|style
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
literal|"gimp-image-grid-get-style"
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
name|style
operator|=
name|GIMP_VALUES_GET_ENUM
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
name|style
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_grid_set_style:  * @image: The image.  * @style: The image's grid style.  *  * Sets the style unit of an image's grid.  *  * This procedure sets the style of an image's grid. It takes the image  * and the new style as parameters.  *  * Returns: TRUE on success.  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_grid_set_style (GimpImage * image,GimpGridStyle style)
name|gimp_image_grid_set_style
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpGridStyle
name|style
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
name|GIMP_TYPE_GRID_STYLE
argument_list|,
name|style
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
literal|"gimp-image-grid-set-style"
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

