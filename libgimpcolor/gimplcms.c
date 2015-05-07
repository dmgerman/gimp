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
file|<string.h>
end_include

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

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimplcms  * @title: GimpLcms  * @short_description: Definitions and Functions relating to LCMS.  *  * Definitions and Functions relating to LCMS.  **/
end_comment

begin_comment
comment|/**  * GimpColorProfile:  *  * Simply a typedef to #gpointer, but actually is a cmsHPROFILE. It's  * used in public GIMP APIs in order to avoid having to include LCMS  * headers.  **/
end_comment

begin_define
DECL|macro|GIMP_LCMS_MD5_DIGEST_LENGTH
define|#
directive|define
name|GIMP_LCMS_MD5_DIGEST_LENGTH
value|16
end_define

begin_function
specifier|static
name|GQuark
DECL|function|gimp_lcms_error_quark (void)
name|gimp_lcms_error_quark
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GQuark
name|quark
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
name|quark
operator|==
literal|0
argument_list|)
condition|)
name|quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-lcms-error-quark"
argument_list|)
expr_stmt|;
return|return
name|quark
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_lcms_profile_open_from_file:  * @file:  a #GFile  * @error: return location for #GError  *  * This function opens an ICC color profile from @file.  *  * Return value: the #GimpColorProfile, or %NULL. On error, %NULL is  *               returned and @error is set.  *  * Since: GIMP 2.10  **/
end_comment

begin_function
name|GimpColorProfile
DECL|function|gimp_lcms_profile_open_from_file (GFile * file,GError ** error)
name|gimp_lcms_profile_open_from_file
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpColorProfile
name|profile
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|path
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
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
name|path
operator|=
name|g_file_get_path
argument_list|(
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|path
condition|)
block|{
name|GMappedFile
modifier|*
name|mapped
decl_stmt|;
specifier|const
name|guint8
modifier|*
name|data
decl_stmt|;
name|gsize
name|length
decl_stmt|;
name|mapped
operator|=
name|g_mapped_file_new
argument_list|(
name|path
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|mapped
condition|)
return|return
name|NULL
return|;
name|data
operator|=
operator|(
specifier|const
name|guint8
operator|*
operator|)
name|g_mapped_file_get_contents
argument_list|(
name|mapped
argument_list|)
expr_stmt|;
name|length
operator|=
name|g_mapped_file_get_length
argument_list|(
name|mapped
argument_list|)
expr_stmt|;
name|profile
operator|=
name|cmsOpenProfileFromMem
argument_list|(
name|data
argument_list|,
name|length
argument_list|)
expr_stmt|;
name|g_mapped_file_unref
argument_list|(
name|mapped
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GFileInfo
modifier|*
name|info
decl_stmt|;
name|info
operator|=
name|g_file_query_info
argument_list|(
name|file
argument_list|,
name|G_FILE_ATTRIBUTE_STANDARD_SIZE
argument_list|,
name|G_FILE_QUERY_INFO_NONE
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
condition|)
block|{
name|GInputStream
modifier|*
name|input
decl_stmt|;
name|goffset
name|length
init|=
name|g_file_info_get_size
argument_list|(
name|info
argument_list|)
decl_stmt|;
name|guint8
modifier|*
name|data
init|=
name|g_malloc
argument_list|(
name|length
argument_list|)
decl_stmt|;
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
name|input
operator|=
name|G_INPUT_STREAM
argument_list|(
name|g_file_read
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|input
condition|)
block|{
name|gsize
name|bytes_read
decl_stmt|;
if|if
condition|(
name|g_input_stream_read_all
argument_list|(
name|input
argument_list|,
name|data
argument_list|,
name|length
argument_list|,
operator|&
name|bytes_read
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
operator|&&
name|bytes_read
operator|==
name|length
condition|)
block|{
name|profile
operator|=
name|cmsOpenProfileFromMem
argument_list|(
name|data
argument_list|,
name|length
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|input
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|profile
operator|&&
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
condition|)
name|g_set_error
argument_list|(
name|error
argument_list|,
name|gimp_lcms_error_quark
argument_list|()
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"'%s' does not appear to be an ICC color profile"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|profile
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_lcms_profile_open_from_data:  * @data:   pointer to memory containing an ICC profile  * @length: lenght of the profile in memory, in bytes  * @error:  return location for #GError  *  * This function opens an ICC color profile from memory. On error,  * %NULL is returned and @error is set.  *  * Return value: the #GimpColorProfile, or %NULL.  *  * Since: GIMP 2.10  **/
end_comment

begin_function
name|GimpColorProfile
DECL|function|gimp_lcms_profile_open_from_data (const guint8 * data,gsize length,GError ** error)
name|gimp_lcms_profile_open_from_data
parameter_list|(
specifier|const
name|guint8
modifier|*
name|data
parameter_list|,
name|gsize
name|length
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpColorProfile
name|profile
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|data
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|length
operator|>
literal|0
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
name|profile
operator|=
name|cmsOpenProfileFromMem
argument_list|(
name|data
argument_list|,
name|length
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|profile
condition|)
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|gimp_lcms_error_quark
argument_list|()
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Data does not appear to be an ICC color profile"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|profile
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_lcms_profile_dave_to_data:  * @profile: a #GimpColorProfile  * @length:  return location for the number of bytes written  * @error:   return location for #GError  *  * This function saves @profile to an ICC color profile in newly  * allocated memory. On error, %NULL is returned and @error is set.  *  * Return value: a pointer to the written IIC profile in memory, or  *               %NULL. Free with g_free().  *  * Since: GIMP 2.10  **/
end_comment

begin_function
name|guint8
modifier|*
DECL|function|gimp_lcms_profile_save_to_data (GimpColorProfile profile,gsize * length,GError ** error)
name|gimp_lcms_profile_save_to_data
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|,
name|gsize
modifier|*
name|length
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|cmsUInt32Number
name|size
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
name|g_return_val_if_fail
argument_list|(
name|length
operator|!=
name|NULL
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
if|if
condition|(
name|cmsSaveProfileToMem
argument_list|(
name|profile
argument_list|,
name|NULL
argument_list|,
operator|&
name|size
argument_list|)
condition|)
block|{
name|guint8
modifier|*
name|data
init|=
name|g_malloc
argument_list|(
name|size
argument_list|)
decl_stmt|;
if|if
condition|(
name|cmsSaveProfileToMem
argument_list|(
name|profile
argument_list|,
name|data
argument_list|,
operator|&
name|size
argument_list|)
condition|)
block|{
operator|*
name|length
operator|=
name|size
expr_stmt|;
return|return
name|data
return|;
block|}
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|gimp_lcms_error_quark
argument_list|()
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Could not save color profile to memory"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_lcms_profile_close:  * @profile: a #GimpColorProfile  *  * This function closes a #GimpColorProfile and frees its memory.  *  * Since: GIMP 2.10  **/
end_comment

begin_function
name|void
DECL|function|gimp_lcms_profile_close (GimpColorProfile profile)
name|gimp_lcms_profile_close
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|profile
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|cmsCloseProfile
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
end_function

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

begin_comment
comment|/**  * gimp_lcms_profile_get_description:  * @profile: a #GimpColorProfile  *  * Return value: a newly allocated string containing @profile's  *               description. Free with g_free().  *  * Since: GIMP 2.10  **/
end_comment

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

begin_comment
comment|/**  * gimp_lcms_profile_get_manufacturer:  * @profile: a #GimpColorProfile  *  * Return value: a newly allocated string containing @profile's  *               manufacturer. Free with g_free().  *  * Since: GIMP 2.10  **/
end_comment

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

begin_comment
comment|/**  * gimp_lcms_profile_get_model:  * @profile: a #GimpColorProfile  *  * Return value: a newly allocated string containing @profile's  *               model. Free with g_free().  *  * Since: GIMP 2.10  **/
end_comment

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

begin_comment
comment|/**  * gimp_lcms_profile_get_copyright:  * @profile: a #GimpColorProfile  *  * Return value: a newly allocated string containing @profile's  *               copyright. Free with g_free().  *  * Since: GIMP 2.10  **/
end_comment

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

begin_comment
comment|/**  * gimp_lcms_profile_get_label:  * @profile: a #GimpColorProfile  *  * This function returns a newly allocated string containing  * @profile's "title", a string that can be used to label the profile  * in a user interface.  *  * Return value: the @profile's label. Free with g_free().  *  * Since: GIMP 2.10  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_lcms_profile_get_label (GimpColorProfile profile)
name|gimp_lcms_profile_get_label
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
block|{
name|gchar
modifier|*
name|label
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
name|label
operator|=
name|gimp_lcms_profile_get_description
argument_list|(
name|profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|label
operator|&&
operator|!
name|strlen
argument_list|(
name|label
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|label
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|label
condition|)
name|label
operator|=
name|gimp_lcms_profile_get_model
argument_list|(
name|profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|label
operator|&&
operator|!
name|strlen
argument_list|(
name|label
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|label
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|label
condition|)
name|label
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"(unnamed profile)"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|label
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_lcms_profile_get_summary:  * @profile: a #GimpColorProfile  *  * This function return a newly allocated string containing a  * multi-line summary of @profile's description, model, manufacturer  * and copyright, to be used as detailled information about the  * prpfile in a user interface.  *  * Return value: the @profile's summary. Free with g_free().  *  * Since: GIMP 2.10  **/
end_comment

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
comment|/**  * gimp_lcms_profile_is_equal:  * @profile1: a #GimpColorProfile  * @profile2: a #GimpColorProfile  *  * Compares two profiles.  *  * Return value: %TRUE if the profiles are equal, %FALSE otherwise.  *  * Since: GIMP 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_lcms_profile_is_equal (GimpColorProfile profile1,GimpColorProfile profile2)
name|gimp_lcms_profile_is_equal
parameter_list|(
name|GimpColorProfile
name|profile1
parameter_list|,
name|GimpColorProfile
name|profile2
parameter_list|)
block|{
name|cmsUInt8Number
name|digest1
index|[
name|GIMP_LCMS_MD5_DIGEST_LENGTH
index|]
decl_stmt|;
name|cmsUInt8Number
name|digest2
index|[
name|GIMP_LCMS_MD5_DIGEST_LENGTH
index|]
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|profile1
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|profile2
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|cmsMD5computeID
argument_list|(
name|profile1
argument_list|)
operator|||
operator|!
name|cmsMD5computeID
argument_list|(
name|profile2
argument_list|)
condition|)
block|{
return|return
name|FALSE
return|;
block|}
name|cmsGetHeaderProfileID
argument_list|(
name|profile1
argument_list|,
name|digest1
argument_list|)
expr_stmt|;
name|cmsGetHeaderProfileID
argument_list|(
name|profile2
argument_list|,
name|digest2
argument_list|)
expr_stmt|;
return|return
operator|(
name|memcmp
argument_list|(
name|digest1
argument_list|,
name|digest2
argument_list|,
name|GIMP_LCMS_MD5_DIGEST_LENGTH
argument_list|)
operator|==
literal|0
operator|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_lcms_profile_is_rgb:  * @profile: a #GimpColorProfile  *  * Return value: %TRUE if the profile's color space is RGB, %FALSE  * otherwise.  *  * Since: GIMP 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_lcms_profile_is_rgb (GimpColorProfile profile)
name|gimp_lcms_profile_is_rgb
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|profile
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
operator|(
name|cmsGetColorSpace
argument_list|(
name|profile
argument_list|)
operator|==
name|cmsSigRgbData
operator|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_lcms_profile_is_cmyk:  * @profile: a #GimpColorProfile  *  * Return value: %TRUE if the profile's color space is CMYK, %FALSE  * otherwise.  *  * Since: GIMP 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_lcms_profile_is_cmyk (GimpColorProfile profile)
name|gimp_lcms_profile_is_cmyk
parameter_list|(
name|GimpColorProfile
name|profile
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|profile
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
operator|(
name|cmsGetColorSpace
argument_list|(
name|profile
argument_list|)
operator|==
name|cmsSigCmykData
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_lcms_profile_set_tag (cmsHPROFILE profile,cmsTagSignature sig,const gchar * tag)
name|gimp_lcms_profile_set_tag
parameter_list|(
name|cmsHPROFILE
name|profile
parameter_list|,
name|cmsTagSignature
name|sig
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tag
parameter_list|)
block|{
name|cmsMLU
modifier|*
name|mlu
decl_stmt|;
name|mlu
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
name|mlu
argument_list|,
literal|"en"
argument_list|,
literal|"US"
argument_list|,
name|tag
argument_list|)
expr_stmt|;
name|cmsWriteTag
argument_list|(
name|profile
argument_list|,
name|sig
argument_list|,
name|mlu
argument_list|)
expr_stmt|;
name|cmsMLUfree
argument_list|(
name|mlu
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpColorProfile
DECL|function|gimp_lcms_create_srgb_profile_internal (void)
name|gimp_lcms_create_srgb_profile_internal
parameter_list|(
name|void
parameter_list|)
block|{
name|cmsHPROFILE
name|srgb_profile
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
name|gimp_lcms_profile_set_tag
argument_list|(
name|srgb_profile
argument_list|,
name|cmsSigProfileDescriptionTag
argument_list|,
literal|"GIMP built-in sRGB"
argument_list|)
expr_stmt|;
name|gimp_lcms_profile_set_tag
argument_list|(
name|srgb_profile
argument_list|,
name|cmsSigDeviceMfgDescTag
argument_list|,
literal|"GIMP"
argument_list|)
expr_stmt|;
name|gimp_lcms_profile_set_tag
argument_list|(
name|srgb_profile
argument_list|,
name|cmsSigDeviceModelDescTag
argument_list|,
literal|"sRGB"
argument_list|)
expr_stmt|;
name|gimp_lcms_profile_set_tag
argument_list|(
name|srgb_profile
argument_list|,
name|cmsSigCopyrightTag
argument_list|,
literal|"Public Domain"
argument_list|)
expr_stmt|;
comment|/**    * The following line produces a V2 profile with a point curve TRC.    * Profiles with point curve TRCs can't be used in LCMS2 unbounded    * mode ICC profile conversions. A V2 profile might be appropriate    * for embedding in sRGB images saved to disk, if the image is to be    * opened by an image editing application that doesn't understand V4    * profiles.    *    * cmsSetProfileVersion (srgb_profile, 2.1);    **/
return|return
name|srgb_profile
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
specifier|static
name|guint8
modifier|*
name|profile_data
init|=
name|NULL
decl_stmt|;
specifier|static
name|gsize
name|profile_length
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
name|profile_data
operator|==
name|NULL
argument_list|)
condition|)
block|{
name|GimpColorProfile
name|profile
decl_stmt|;
name|profile
operator|=
name|gimp_lcms_create_srgb_profile_internal
argument_list|()
expr_stmt|;
name|profile_data
operator|=
name|gimp_lcms_profile_save_to_data
argument_list|(
name|profile
argument_list|,
operator|&
name|profile_length
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_lcms_profile_close
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_lcms_profile_open_from_data
argument_list|(
name|profile_data
argument_list|,
name|profile_length
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

