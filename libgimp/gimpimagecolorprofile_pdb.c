begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpimagecolorprofile_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimpimagecolorprofile  * @title: gimpimagecolorprofile  * @short_description: Operations on an image's color profile.  *  * Operations on an image's color profile.  **/
end_comment

begin_comment
comment|/**  * _gimp_image_get_color_profile:  * @image_ID: The image.  * @num_bytes: (out) Number of bytes in the color_profile array.  *  * Returns the image's color profile  *  * This procedure returns the image's color profile, or NULL if the  * image has no color profile assigned.  *  * Returns: (element-type guint8) (transfer full) The image's  * serialized color profile. The returned value must be freed with  * g_free().  *  * Since: 2.10  **/
end_comment

begin_function
name|guint8
modifier|*
DECL|function|_gimp_image_get_color_profile (gint32 image_ID,gint * num_bytes)
name|_gimp_image_get_color_profile
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|num_bytes
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
name|guint8
modifier|*
name|profile_data
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
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
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-get-color-profile"
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
name|num_bytes
operator|=
literal|0
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
operator|*
name|num_bytes
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
name|profile_data
operator|=
name|gimp_value_dup_int8_array
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
name|profile_data
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_image_get_effective_color_profile:  * @image_ID: The image.  * @num_bytes: (out) Number of bytes in the color_profile array.  *  * Returns the color profile that is used for the image  *  * This procedure returns the color profile that is actually used for  * this image, which is the profile returned by  * gimp_image_get_color_profile() if the image has a profile assigned,  * or a generated default RGB or grayscale profile, according to the  * image's type.  *  * Returns: (element-type guint8) (transfer full) The image's  * serialized color profile. The returned value must be freed with  * g_free().  *  * Since: 2.10  **/
end_comment

begin_function
name|guint8
modifier|*
DECL|function|_gimp_image_get_effective_color_profile (gint32 image_ID,gint * num_bytes)
name|_gimp_image_get_effective_color_profile
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|num_bytes
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
name|guint8
modifier|*
name|profile_data
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
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
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-get-effective-color-profile"
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
name|num_bytes
operator|=
literal|0
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
operator|*
name|num_bytes
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
name|profile_data
operator|=
name|gimp_value_dup_int8_array
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
name|profile_data
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_image_set_color_profile:  * @image_ID: The image.  * @num_bytes: Number of bytes in the color_profile array.  * @color_profile: (element-type guint8) The new serialized color profile.  *  * Sets the image's color profile  *  * This procedure sets the image's color profile, or unsets it if NULL  * is passed as 'color_profile'. This procedure does no color  * conversion. However, it will change the pixel format of all layers  * to contain the babl space matching the profile. You must call this  * procedure before adding layers to the image.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_image_set_color_profile (gint32 image_ID,gint num_bytes,const guint8 * color_profile)
name|_gimp_image_set_color_profile
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|num_bytes
parameter_list|,
specifier|const
name|guint8
modifier|*
name|color_profile
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
name|GIMP_TYPE_INT32
argument_list|,
name|GIMP_TYPE_INT8_ARRAY
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
name|num_bytes
argument_list|)
expr_stmt|;
name|gimp_value_set_int8_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|color_profile
argument_list|,
name|num_bytes
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-set-color-profile"
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
comment|/**  * gimp_image_set_color_profile_from_file:  * @image_ID: The image.  * @uri: The URI of the file containing the new color profile.  *  * Sets the image's color profile from an ICC file  *  * This procedure sets the image's color profile from a file containing  * an ICC profile, or unsets it if NULL is passed as 'uri'. This  * procedure does no color conversion. However, it will change the  * pixel format of all layers to contain the babl space matching the  * profile. You must call this procedure before adding layers to the  * image.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_set_color_profile_from_file (gint32 image_ID,const gchar * uri)
name|gimp_image_set_color_profile_from_file
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
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
name|G_TYPE_STRING
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
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-set-color-profile-from-file"
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
comment|/**  * _gimp_image_convert_color_profile:  * @image_ID: The image.  * @num_bytes: Number of bytes in the color_profile array.  * @color_profile: (element-type guint8) The serialized color profile.  * @intent: Rendering intent.  * @bpc: Black point compensation.  *  * Convert the image's layers to a color profile  *  * This procedure converts from the image's color profile (or the  * default RGB or grayscale profile if none is set) to the given color  * profile. Only RGB and grayscale color profiles are accepted,  * according to the image's type.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_image_convert_color_profile (gint32 image_ID,gint num_bytes,const guint8 * color_profile,GimpColorRenderingIntent intent,gboolean bpc)
name|_gimp_image_convert_color_profile
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|num_bytes
parameter_list|,
specifier|const
name|guint8
modifier|*
name|color_profile
parameter_list|,
name|GimpColorRenderingIntent
name|intent
parameter_list|,
name|gboolean
name|bpc
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
name|GIMP_TYPE_INT32
argument_list|,
name|GIMP_TYPE_INT8_ARRAY
argument_list|,
name|GIMP_TYPE_COLOR_RENDERING_INTENT
argument_list|,
name|G_TYPE_BOOLEAN
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
name|num_bytes
argument_list|)
expr_stmt|;
name|gimp_value_set_int8_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|color_profile
argument_list|,
name|num_bytes
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|intent
argument_list|)
expr_stmt|;
name|g_value_set_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|4
argument_list|)
argument_list|,
name|bpc
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-convert-color-profile"
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
comment|/**  * gimp_image_convert_color_profile_from_file:  * @image_ID: The image.  * @uri: The URI of the file containing the new color profile.  * @intent: Rendering intent.  * @bpc: Black point compensation.  *  * Convert the image's layers to a color profile  *  * This procedure converts from the image's color profile (or the  * default RGB or grayscale profile if none is set) to an ICC profile  * specified by 'uri'. Only RGB and grayscale color profiles are  * accepted, according to the image's type.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_convert_color_profile_from_file (gint32 image_ID,const gchar * uri,GimpColorRenderingIntent intent,gboolean bpc)
name|gimp_image_convert_color_profile_from_file
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|GimpColorRenderingIntent
name|intent
parameter_list|,
name|gboolean
name|bpc
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
name|G_TYPE_STRING
argument_list|,
name|GIMP_TYPE_COLOR_RENDERING_INTENT
argument_list|,
name|G_TYPE_BOOLEAN
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
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|intent
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
name|bpc
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-image-convert-color-profile-from-file"
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

