begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpimagecolorprofile.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
comment|/**  * gimp_image_get_color_profile:  * @image_ID: The image.  *  * Returns the image's color profile  *  * This procedure returns the image's color profile.  *  * Returns: The image's color profile. The returned value  *          must be freed with gimp_color_profile_close().  *  * Since: 2.10  **/
end_comment

begin_function
name|GimpColorProfile
DECL|function|gimp_image_get_color_profile (gint32 image_ID)
name|gimp_image_get_color_profile
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
name|guint8
modifier|*
name|data
decl_stmt|;
name|gint
name|length
decl_stmt|;
name|data
operator|=
name|_gimp_image_get_color_profile
argument_list|(
name|image_ID
argument_list|,
operator|&
name|length
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
block|{
name|GimpColorProfile
name|profile
decl_stmt|;
name|profile
operator|=
name|gimp_color_profile_open_from_data
argument_list|(
name|data
argument_list|,
name|length
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
return|return
name|profile
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_set_color_profile:  * @image_ID: The image.  * @profile:  A #GimpColorProfile, or %NULL.  *  * Sets the image's color profile  *  * This procedure sets the image's color profile.  *  * Returns: %TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_set_color_profile (gint32 image_ID,GimpColorProfile profile)
name|gimp_image_set_color_profile
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpColorProfile
name|profile
parameter_list|)
block|{
name|guint8
modifier|*
name|data
init|=
name|NULL
decl_stmt|;
name|gint
name|length
init|=
literal|0
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
if|if
condition|(
name|profile
condition|)
block|{
name|gsize
name|l
decl_stmt|;
name|data
operator|=
name|gimp_color_profile_save_to_data
argument_list|(
name|profile
argument_list|,
operator|&
name|l
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|length
operator|=
name|l
expr_stmt|;
if|if
condition|(
operator|!
name|data
condition|)
return|return
name|FALSE
return|;
block|}
name|success
operator|=
name|_gimp_image_set_color_profile
argument_list|(
name|image_ID
argument_list|,
name|length
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

