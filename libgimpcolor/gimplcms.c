begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimplcms.c  * Copyright (C) 2014  Michael Natterer<mitch@gimp.org>  *                     Elle Stone<ellestone@ninedegreesbelow.com>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolortypes.h"
end_include

begin_include
include|#
directive|include
file|"gimplcms.h"
end_include

begin_comment
comment|/**  * SECTION: gimplcms  * @title: GimpLcms  * @short_description: Definitions and Functions relating to LCMS.  *  * Definitions and Functions relating to LCMS.  **/
end_comment

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_lcms_profile_get_info (GimpColorProfile profile,cmsInfoType info)
name|gimp_lcms_profile_get_info
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|,
name|cmsInfoType
name|info
parameter_list|)
block|{
name|cmsUInt32Number
name|size
decl_stmt|;
name|gchar
modifier|*
name|text
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|profile
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|size
operator|=
name|cmsGetProfileInfoASCII
argument_list|(
name|profile
argument_list|,
name|info
argument_list|,
literal|"en"
argument_list|,
literal|"US"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|size
operator|>
literal|0
condition|)
block|{
name|gchar
modifier|*
name|data
init|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|size
operator|+
literal|1
argument_list|)
decl_stmt|;
name|size
operator|=
name|cmsGetProfileInfoASCII
argument_list|(
name|profile
argument_list|,
name|info
argument_list|,
literal|"en"
argument_list|,
literal|"US"
argument_list|,
name|data
argument_list|,
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|size
operator|>
literal|0
condition|)
name|text
operator|=
name|gimp_any_to_utf8
argument_list|(
name|data
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
return|return
name|text
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_lcms_profile_get_description (GimpColorProfile profile)
name|gimp_lcms_profile_get_description
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
block|{
return|return
name|gimp_lcms_profile_get_info
argument_list|(
name|profile
argument_list|,
name|cmsInfoDescription
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_lcms_profile_get_manufacturer (GimpColorProfile profile)
name|gimp_lcms_profile_get_manufacturer
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
block|{
return|return
name|gimp_lcms_profile_get_info
argument_list|(
name|profile
argument_list|,
name|cmsInfoManufacturer
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_lcms_profile_get_model (GimpColorProfile profile)
name|gimp_lcms_profile_get_model
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
block|{
return|return
name|gimp_lcms_profile_get_info
argument_list|(
name|profile
argument_list|,
name|cmsInfoModel
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_lcms_profile_get_copyright (GimpColorProfile profile)
name|gimp_lcms_profile_get_copyright
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
block|{
return|return
name|gimp_lcms_profile_get_info
argument_list|(
name|profile
argument_list|,
name|cmsInfoCopyright
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_lcms_profile_get_summary (GimpColorProfile profile)
name|gimp_lcms_profile_get_summary
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
block|{
name|GString
modifier|*
name|string
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|profile
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|string
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|text
operator|=
name|gimp_lcms_profile_get_description
argument_list|(
name|profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
condition|)
block|{
name|g_string_append
argument_list|(
name|string
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
block|}
name|text
operator|=
name|gimp_lcms_profile_get_model
argument_list|(
name|profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
condition|)
block|{
if|if
condition|(
name|string
operator|->
name|len
operator|>
literal|0
condition|)
name|g_string_append
argument_list|(
name|string
argument_list|,
literal|"\n"
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|string
argument_list|,
name|text
argument_list|)
expr_stmt|;
block|}
name|text
operator|=
name|gimp_lcms_profile_get_manufacturer
argument_list|(
name|profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
condition|)
block|{
if|if
condition|(
name|string
operator|->
name|len
operator|>
literal|0
condition|)
name|g_string_append
argument_list|(
name|string
argument_list|,
literal|"\n"
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|string
argument_list|,
name|text
argument_list|)
expr_stmt|;
block|}
name|text
operator|=
name|gimp_lcms_profile_get_copyright
argument_list|(
name|profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
condition|)
block|{
if|if
condition|(
name|string
operator|->
name|len
operator|>
literal|0
condition|)
name|g_string_append
argument_list|(
name|string
argument_list|,
literal|"\n"
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|string
argument_list|,
name|text
argument_list|)
expr_stmt|;
block|}
return|return
name|g_string_free
argument_list|(
name|string
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_lcms_create_srgb_profile:  *  * This function is a replacement for cmsCreate_sRGBProfile() and  * returns an sRGB profile that is functionally the same as the  * ArgyllCMS sRGB.icm profile. "Functionally the same" means it has  * the same red, green, and blue colorants and the V4 "chad"  * equivalent of the ArgyllCMS V2 white point. The profile TRC is also  * functionally equivalent to the ArgyllCMS sRGB.icm TRC and is the  * same as the LCMS sRGB built-in profile TRC.  *  * The actual primaries in the sRGB specification are  * red xy:   {0.6400, 0.3300, 1.0}  * green xy: {0.3000, 0.6000, 1.0}  * blue xy:  {0.1500, 0.0600, 1.0}  *  * The sRGB primaries given below are "pre-quantized" to compensate  * for hexadecimal quantization during the profile-making process.  * Unless the profile-making code compensates for this quantization,  * the resulting profile's red, green, and blue colorants will deviate  * slightly from the correct XYZ values.  *  * LCMS2 doesn't compensate for hexadecimal quantization. The  * "pre-quantized" primaries below were back-calculated from the  * ArgyllCMS sRGB.icm profile. The resulting sRGB profile's colorants  * exactly matches the ArgyllCMS sRGB.icm profile colorants.  *  * Return value: the sRGB cmsHPROFILE.  *  * Since: GIMP 2.10  **/
end_comment

begin_function
name|GimpColorProfile
DECL|function|gimp_lcms_create_srgb_profile (void)
name|gimp_lcms_create_srgb_profile
parameter_list|(
name|void
parameter_list|)
block|{
name|cmsHPROFILE
name|srgb_profile
decl_stmt|;
name|cmsMLU
modifier|*
name|description
decl_stmt|;
name|cmsCIExyY
name|d65_srgb_specs
init|=
block|{
literal|0.3127
block|,
literal|0.3290
block|,
literal|1.0
block|}
decl_stmt|;
name|cmsCIExyYTRIPLE
name|srgb_primaries_pre_quantized
init|=
block|{
block|{
literal|0.639998686
block|,
literal|0.330010138
block|,
literal|1.0
block|}
block|,
block|{
literal|0.300003784
block|,
literal|0.600003357
block|,
literal|1.0
block|}
block|,
block|{
literal|0.150002046
block|,
literal|0.059997204
block|,
literal|1.0
block|}
block|}
decl_stmt|;
name|cmsFloat64Number
name|srgb_parameters
index|[
literal|5
index|]
init|=
block|{
literal|2.4
block|,
literal|1.0
operator|/
literal|1.055
block|,
literal|0.055
operator|/
literal|1.055
block|,
literal|1.0
operator|/
literal|12.92
block|,
literal|0.04045
block|}
decl_stmt|;
name|cmsToneCurve
modifier|*
name|srgb_parametric_curve
init|=
name|cmsBuildParametricToneCurve
argument_list|(
name|NULL
argument_list|,
literal|4
argument_list|,
name|srgb_parameters
argument_list|)
decl_stmt|;
name|cmsToneCurve
modifier|*
name|tone_curve
index|[
literal|3
index|]
decl_stmt|;
name|tone_curve
index|[
literal|0
index|]
operator|=
name|tone_curve
index|[
literal|1
index|]
operator|=
name|tone_curve
index|[
literal|2
index|]
operator|=
name|srgb_parametric_curve
expr_stmt|;
name|srgb_profile
operator|=
name|cmsCreateRGBProfile
argument_list|(
operator|&
name|d65_srgb_specs
argument_list|,
operator|&
name|srgb_primaries_pre_quantized
argument_list|,
name|tone_curve
argument_list|)
expr_stmt|;
name|cmsFreeToneCurve
argument_list|(
name|srgb_parametric_curve
argument_list|)
expr_stmt|;
name|description
operator|=
name|cmsMLUalloc
argument_list|(
name|NULL
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|cmsMLUsetASCII
argument_list|(
name|description
argument_list|,
literal|"en"
argument_list|,
literal|"US"
argument_list|,
literal|"GIMP built-in sRGB"
argument_list|)
expr_stmt|;
name|cmsWriteTag
argument_list|(
name|srgb_profile
argument_list|,
name|cmsSigProfileDescriptionTag
argument_list|,
name|description
argument_list|)
expr_stmt|;
name|cmsMLUfree
argument_list|(
name|description
argument_list|)
expr_stmt|;
comment|/**    * The following line produces a V2 profile with a point curve TRC.    * Profiles with point curve TRCs can't be used in LCMS2 unbounded    * mode ICC profile conversions. A V2 profile might be appropriate    * for embedding in sRGB images saved to disk, if the image is to be    * opened by an image editing application that doesn't understand V4    * profiles.    *    * cmsSetProfileVersion (srgb_profile, 2.1);    **/
return|return
name|srgb_profile
return|;
block|}
end_function

end_unit

