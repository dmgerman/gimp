begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_comment
comment|/* lcms.h uses the "inline" keyword */
end_comment

begin_include
include|#
directive|include
file|<lcms2.h>
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimperror.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-profile.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* public functions */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_validate_icc_profile (GimpImage * image,const GimpParasite * icc_profile,GError ** error)
name|gimp_image_validate_icc_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|icc_profile
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpColorProfile
modifier|*
name|profile
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|icc_profile
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|gimp_parasite_name
argument_list|(
name|icc_profile
argument_list|)
argument_list|,
name|GIMP_ICC_PROFILE_PARASITE_NAME
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"ICC profile validation failed: "
literal|"Parasite's name is not 'icc-profile'"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|gimp_parasite_flags
argument_list|(
name|icc_profile
argument_list|)
operator|!=
operator|(
name|GIMP_PARASITE_PERSISTENT
operator||
name|GIMP_PARASITE_UNDOABLE
operator|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"ICC profile validation failed: "
literal|"Parasite's flags are not (PERSISTENT | UNDOABLE)"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|gimp_image_get_base_type
argument_list|(
name|image
argument_list|)
operator|==
name|GIMP_GRAY
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"ICC profile validation failed: "
literal|"Cannot attach a color profile to a GRAY image"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|profile
operator|=
name|gimp_lcms_profile_open_from_data
argument_list|(
name|gimp_parasite_data
argument_list|(
name|icc_profile
argument_list|)
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|icc_profile
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|profile
condition|)
block|{
name|g_prefix_error
argument_list|(
name|error
argument_list|,
name|_
argument_list|(
literal|"ICC profile validation failed: "
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
operator|!
name|gimp_lcms_profile_is_rgb
argument_list|(
name|profile
argument_list|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"ICC profile validation failed: "
literal|"Color profile is not for RGB color space"
argument_list|)
argument_list|)
expr_stmt|;
name|cmsCloseProfile
argument_list|(
name|profile
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|cmsCloseProfile
argument_list|(
name|profile
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|const
name|GimpParasite
modifier|*
DECL|function|gimp_image_get_icc_profile (GimpImage * image)
name|gimp_image_get_icc_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_image_parasite_find
argument_list|(
name|image
argument_list|,
name|GIMP_ICC_PROFILE_PARASITE_NAME
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_set_icc_profile (GimpImage * image,const GimpParasite * icc_profile)
name|gimp_image_set_icc_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|icc_profile
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|icc_profile
condition|)
block|{
name|g_return_if_fail
argument_list|(
name|gimp_image_validate_icc_profile
argument_list|(
name|image
argument_list|,
name|icc_profile
argument_list|,
name|NULL
argument_list|)
operator|==
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
argument_list|(
name|image
argument_list|,
name|icc_profile
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_parasite_detach
argument_list|(
name|image
argument_list|,
name|GIMP_ICC_PROFILE_PARASITE_NAME
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpColorProfile
DECL|function|gimp_image_get_profile (GimpImage * image,guint8 * md5_digest,GError ** error)
name|gimp_image_get_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|guint8
modifier|*
name|md5_digest
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpColorConfig
modifier|*
name|config
decl_stmt|;
specifier|const
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|GimpColorProfile
modifier|*
name|profile
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|config
operator|=
name|image
operator|->
name|gimp
operator|->
name|config
operator|->
name|color_management
expr_stmt|;
name|parasite
operator|=
name|gimp_image_get_icc_profile
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|profile
operator|=
name|gimp_lcms_profile_open_from_data
argument_list|(
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|md5_digest
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|profile
condition|)
name|g_prefix_error
argument_list|(
name|error
argument_list|,
name|_
argument_list|(
literal|"Error parsing data attached as 'icc-profile': "
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
operator|&&
operator|!
name|gimp_lcms_profile_is_rgb
argument_list|(
name|profile
argument_list|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"Color profile attached as 'icc-profile' is "
literal|"not for RGB color space"
argument_list|)
argument_list|)
expr_stmt|;
name|cmsCloseProfile
argument_list|(
name|profile
argument_list|)
expr_stmt|;
name|profile
operator|=
name|NULL
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|config
operator|->
name|rgb_profile
condition|)
block|{
name|profile
operator|=
name|gimp_lcms_profile_open_from_file
argument_list|(
name|config
operator|->
name|rgb_profile
argument_list|,
name|md5_digest
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
operator|&&
operator|!
name|gimp_lcms_profile_is_rgb
argument_list|(
name|profile
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"Color profile '%s' is not for RGB color space"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|config
operator|->
name|rgb_profile
argument_list|)
argument_list|)
expr_stmt|;
name|cmsCloseProfile
argument_list|(
name|profile
argument_list|)
expr_stmt|;
name|profile
operator|=
name|NULL
expr_stmt|;
block|}
block|}
return|return
name|profile
return|;
block|}
end_function

end_unit

