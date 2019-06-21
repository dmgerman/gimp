begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-color-profile.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-metadata.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo-push.h"
end_include

begin_comment
comment|/* public functions */
end_comment

begin_function
name|GimpMetadata
modifier|*
DECL|function|gimp_image_get_metadata (GimpImage * image)
name|gimp_image_get_metadata
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
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
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|private
operator|->
name|metadata
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_set_metadata (GimpImage * image,GimpMetadata * metadata,gboolean push_undo)
name|gimp_image_set_metadata
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata
operator|!=
name|private
operator|->
name|metadata
condition|)
block|{
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_image_metadata
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_set_object
argument_list|(
operator|&
name|private
operator|->
name|metadata
argument_list|,
name|metadata
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|metadata
condition|)
block|{
name|gimp_image_metadata_update_pixel_size
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_metadata_update_bits_per_sample
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_metadata_update_resolution
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_metadata_update_colorspace
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
literal|"metadata"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_metadata_update_pixel_size (GimpImage * image)
name|gimp_image_metadata_update_pixel_size
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpMetadata
modifier|*
name|metadata
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|metadata
operator|=
name|gimp_image_get_metadata
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata
condition|)
block|{
name|gimp_metadata_set_pixel_size
argument_list|(
name|metadata
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_metadata_update_bits_per_sample (GimpImage * image)
name|gimp_image_metadata_update_bits_per_sample
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpMetadata
modifier|*
name|metadata
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|metadata
operator|=
name|gimp_image_get_metadata
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata
condition|)
block|{
switch|switch
condition|(
name|gimp_image_get_component_type
argument_list|(
name|image
argument_list|)
condition|)
block|{
case|case
name|GIMP_COMPONENT_TYPE_U8
case|:
name|gimp_metadata_set_bits_per_sample
argument_list|(
name|metadata
argument_list|,
literal|8
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COMPONENT_TYPE_U16
case|:
case|case
name|GIMP_COMPONENT_TYPE_HALF
case|:
name|gimp_metadata_set_bits_per_sample
argument_list|(
name|metadata
argument_list|,
literal|16
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COMPONENT_TYPE_U32
case|:
case|case
name|GIMP_COMPONENT_TYPE_FLOAT
case|:
name|gimp_metadata_set_bits_per_sample
argument_list|(
name|metadata
argument_list|,
literal|32
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COMPONENT_TYPE_DOUBLE
case|:
name|gimp_metadata_set_bits_per_sample
argument_list|(
name|metadata
argument_list|,
literal|64
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_metadata_update_resolution (GimpImage * image)
name|gimp_image_metadata_update_resolution
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpMetadata
modifier|*
name|metadata
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|metadata
operator|=
name|gimp_image_get_metadata
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata
condition|)
block|{
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|gimp_metadata_set_resolution
argument_list|(
name|metadata
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|,
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_metadata_update_colorspace (GimpImage * image)
name|gimp_image_metadata_update_colorspace
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpMetadata
modifier|*
name|metadata
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|metadata
operator|=
name|gimp_image_get_metadata
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata
condition|)
block|{
comment|/*  See the discussions in issue #3532 and issue #301  */
name|GimpColorProfile
modifier|*
name|profile
init|=
name|gimp_image_get_color_profile
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpMetadataColorspace
name|space
init|=
name|GIMP_METADATA_COLORSPACE_UNSPECIFIED
decl_stmt|;
if|if
condition|(
name|profile
condition|)
block|{
specifier|static
name|GimpColorProfile
modifier|*
name|adobe
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|adobe
condition|)
name|adobe
operator|=
name|gimp_color_profile_new_rgb_adobe
argument_list|()
expr_stmt|;
if|if
condition|(
name|gimp_color_profile_is_equal
argument_list|(
name|profile
argument_list|,
name|adobe
argument_list|)
condition|)
name|space
operator|=
name|GIMP_METADATA_COLORSPACE_ADOBERGB
expr_stmt|;
block|}
else|else
block|{
name|space
operator|=
name|GIMP_METADATA_COLORSPACE_SRGB
expr_stmt|;
block|}
name|gimp_metadata_set_colorspace
argument_list|(
name|metadata
argument_list|,
name|space
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

