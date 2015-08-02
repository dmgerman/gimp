begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimage-color-profile.c  * Copyright (C) 2015 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gegl/gimp-babl.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
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
file|"gimpimage-color-profile.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-colormap.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_image_convert_profile_rgb
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|,
name|GimpColorRenderingIntent
name|intent
parameter_list|,
name|gboolean
name|bpc
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_convert_profile_indexed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|,
name|GimpColorRenderingIntent
name|intent
parameter_list|,
name|gboolean
name|bpc
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_validate_icc_parasite (GimpImage * image,const GimpParasite * icc_parasite,GError ** error)
name|gimp_image_validate_icc_parasite
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|icc_parasite
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
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
name|icc_parasite
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
name|icc_parasite
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
name|icc_parasite
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
return|return
name|gimp_image_validate_icc_profile
argument_list|(
name|image
argument_list|,
name|gimp_parasite_data
argument_list|(
name|icc_parasite
argument_list|)
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|icc_parasite
argument_list|)
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
specifier|const
name|GimpParasite
modifier|*
DECL|function|gimp_image_get_icc_parasite (GimpImage * image)
name|gimp_image_get_icc_parasite
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
DECL|function|gimp_image_set_icc_parasite (GimpImage * image,const GimpParasite * icc_parasite)
name|gimp_image_set_icc_parasite
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|icc_parasite
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
name|icc_parasite
condition|)
block|{
name|g_return_if_fail
argument_list|(
name|gimp_image_validate_icc_parasite
argument_list|(
name|image
argument_list|,
name|icc_parasite
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
name|icc_parasite
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
name|gboolean
DECL|function|gimp_image_validate_icc_profile (GimpImage * image,const guint8 * data,gsize length,GError ** error)
name|gimp_image_validate_icc_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
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
name|data
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|length
operator|!=
literal|0
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
name|profile
operator|=
name|gimp_color_profile_new_from_icc_profile
argument_list|(
name|data
argument_list|,
name|length
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
name|gimp_image_validate_color_profile
argument_list|(
name|image
argument_list|,
name|profile
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|g_object_unref
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
name|guint8
modifier|*
DECL|function|gimp_image_get_icc_profile (GimpImage * image,gsize * length)
name|gimp_image_get_icc_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gsize
modifier|*
name|length
parameter_list|)
block|{
specifier|const
name|GimpParasite
modifier|*
name|parasite
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
name|parasite
operator|=
name|gimp_image_parasite_find
argument_list|(
name|image
argument_list|,
name|GIMP_ICC_PROFILE_PARASITE_NAME
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
if|if
condition|(
name|length
condition|)
operator|*
name|length
operator|=
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
return|return
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
return|;
block|}
if|if
condition|(
name|length
condition|)
operator|*
name|length
operator|=
literal|0
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_set_icc_profile (GimpImage * image,const guint8 * data,gsize length,GError ** error)
name|gimp_image_set_icc_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
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
name|GimpParasite
modifier|*
name|parasite
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
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|data
operator|==
name|NULL
operator|||
name|length
operator|!=
literal|0
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
name|data
condition|)
block|{
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
name|GIMP_ICC_PROFILE_PARASITE_NAME
argument_list|,
name|GIMP_PARASITE_PERSISTENT
operator||
name|GIMP_PARASITE_UNDOABLE
argument_list|,
name|length
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_image_validate_icc_parasite
argument_list|(
name|image
argument_list|,
name|parasite
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
name|gimp_image_set_icc_parasite
argument_list|(
name|image
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_validate_color_profile (GimpImage * image,GimpColorProfile * profile,GError ** error)
name|gimp_image_validate_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpColorProfile
modifier|*
name|profile
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
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
name|GIMP_IS_COLOR_PROFILE
argument_list|(
name|profile
argument_list|)
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
if|if
condition|(
operator|!
name|gimp_color_profile_is_rgb
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
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GimpColorProfile
modifier|*
DECL|function|gimp_image_get_color_profile (GimpImage * image)
name|gimp_image_get_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
specifier|const
name|GimpParasite
modifier|*
name|parasite
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
name|parasite
operator|=
name|gimp_image_get_icc_parasite
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
return|return
name|gimp_color_profile_new_from_icc_profile
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
name|NULL
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_set_color_profile (GimpImage * image,GimpColorProfile * profile,GError ** error)
name|gimp_image_set_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpColorProfile
modifier|*
name|profile
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
specifier|const
name|guint8
modifier|*
name|data
init|=
name|NULL
decl_stmt|;
name|gsize
name|length
init|=
literal|0
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
name|profile
operator|==
name|NULL
operator|||
name|GIMP_IS_COLOR_PROFILE
argument_list|(
name|profile
argument_list|)
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
name|profile
condition|)
name|data
operator|=
name|gimp_color_profile_get_icc_profile
argument_list|(
name|profile
argument_list|,
operator|&
name|length
argument_list|)
expr_stmt|;
return|return
name|gimp_image_set_icc_profile
argument_list|(
name|image
argument_list|,
name|data
argument_list|,
name|length
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpColorProfile
modifier|*
DECL|function|gimp_image_get_builtin_color_profile (GimpImage * image)
name|gimp_image_get_builtin_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
specifier|const
name|Babl
modifier|*
name|format
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
name|format
operator|=
name|gimp_image_get_layer_format
argument_list|(
name|image
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_babl_format_get_linear
argument_list|(
name|format
argument_list|)
condition|)
return|return
name|gimp_color_profile_new_linear_rgb
argument_list|()
return|;
else|else
return|return
name|gimp_color_profile_new_srgb
argument_list|()
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_convert_color_profile (GimpImage * image,GimpColorProfile * dest_profile,GimpColorRenderingIntent intent,gboolean bpc,GimpProgress * progress,GError ** error)
name|gimp_image_convert_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|,
name|GimpColorRenderingIntent
name|intent
parameter_list|,
name|gboolean
name|bpc
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpColorProfile
modifier|*
name|src_profile
decl_stmt|;
name|GimpColorProfile
modifier|*
name|builtin_profile
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
name|dest_profile
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
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
operator|!
name|gimp_image_validate_color_profile
argument_list|(
name|image
argument_list|,
name|dest_profile
argument_list|,
name|error
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|src_profile
operator|=
name|gimp_color_managed_get_color_profile
argument_list|(
name|GIMP_COLOR_MANAGED
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_color_profile_is_equal
argument_list|(
name|src_profile
argument_list|,
name|dest_profile
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|src_profile
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|progress
condition|)
name|gimp_progress_start
argument_list|(
name|progress
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Converting from '%s' to '%s'"
argument_list|)
argument_list|,
name|gimp_color_profile_get_label
argument_list|(
name|src_profile
argument_list|)
argument_list|,
name|gimp_color_profile_get_label
argument_list|(
name|dest_profile
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_CONVERT
argument_list|,
name|_
argument_list|(
literal|"Color profile conversion"
argument_list|)
argument_list|)
expr_stmt|;
name|builtin_profile
operator|=
name|gimp_image_get_builtin_color_profile
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_color_profile_is_equal
argument_list|(
name|dest_profile
argument_list|,
name|builtin_profile
argument_list|)
condition|)
block|{
comment|/*  don't tag the image with the built-in profile  */
name|gimp_image_set_color_profile
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_set_color_profile
argument_list|(
name|image
argument_list|,
name|dest_profile
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|builtin_profile
argument_list|)
expr_stmt|;
comment|/*  omg...  */
name|gimp_image_parasite_detach
argument_list|(
name|image
argument_list|,
literal|"icc-profile-name"
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_image_get_base_type
argument_list|(
name|image
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB
case|:
name|gimp_image_convert_profile_rgb
argument_list|(
name|image
argument_list|,
name|src_profile
argument_list|,
name|dest_profile
argument_list|,
name|intent
argument_list|,
name|bpc
argument_list|,
name|progress
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY
case|:
break|break;
case|case
name|GIMP_INDEXED
case|:
name|gimp_image_convert_profile_indexed
argument_list|(
name|image
argument_list|,
name|src_profile
argument_list|,
name|dest_profile
argument_list|,
name|intent
argument_list|,
name|bpc
argument_list|,
name|progress
argument_list|)
expr_stmt|;
break|break;
block|}
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|src_profile
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_image_convert_profile_rgb (GimpImage * image,GimpColorProfile * src_profile,GimpColorProfile * dest_profile,GimpColorRenderingIntent intent,gboolean bpc,GimpProgress * progress)
name|gimp_image_convert_profile_rgb
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|,
name|GimpColorRenderingIntent
name|intent
parameter_list|,
name|gboolean
name|bpc
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GList
modifier|*
name|layers
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|n_drawables
decl_stmt|;
name|gint
name|nth_drawable
decl_stmt|;
name|layers
operator|=
name|gimp_image_get_layer_list
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|n_drawables
operator|=
name|g_list_length
argument_list|(
name|layers
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|layers
operator|,
name|nth_drawable
operator|=
literal|0
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
operator|,
name|nth_drawable
operator|++
control|)
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|list
operator|->
name|data
decl_stmt|;
name|cmsHPROFILE
name|src_lcms
decl_stmt|;
name|cmsHPROFILE
name|dest_lcms
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|iter_format
decl_stmt|;
name|cmsUInt32Number
name|lcms_format
decl_stmt|;
name|cmsUInt32Number
name|flags
decl_stmt|;
name|cmsHTRANSFORM
name|transform
decl_stmt|;
if|if
condition|(
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
continue|continue;
name|src_lcms
operator|=
name|gimp_color_profile_get_lcms_profile
argument_list|(
name|src_profile
argument_list|)
expr_stmt|;
name|dest_lcms
operator|=
name|gimp_color_profile_get_lcms_profile
argument_list|(
name|dest_profile
argument_list|)
expr_stmt|;
name|iter_format
operator|=
name|gimp_color_profile_get_format
argument_list|(
name|gimp_drawable_get_format
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|lcms_format
argument_list|)
expr_stmt|;
name|flags
operator|=
name|cmsFLAGS_NOOPTIMIZE
expr_stmt|;
if|if
condition|(
name|bpc
condition|)
name|flags
operator||=
name|cmsFLAGS_BLACKPOINTCOMPENSATION
expr_stmt|;
name|transform
operator|=
name|cmsCreateTransform
argument_list|(
name|src_lcms
argument_list|,
name|lcms_format
argument_list|,
name|dest_lcms
argument_list|,
name|lcms_format
argument_list|,
name|intent
argument_list|,
name|flags
argument_list|)
expr_stmt|;
if|if
condition|(
name|transform
condition|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_push_undo
argument_list|(
name|drawable
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|iter_format
argument_list|,
name|GEGL_ACCESS_READWRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|cmsDoTransform
argument_list|(
name|transform
argument_list|,
name|iter
operator|->
name|data
index|[
literal|0
index|]
argument_list|,
name|iter
operator|->
name|data
index|[
literal|0
index|]
argument_list|,
name|iter
operator|->
name|length
argument_list|)
expr_stmt|;
block|}
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|cmsDeleteTransform
argument_list|(
name|transform
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|progress
condition|)
name|gimp_progress_set_value
argument_list|(
name|progress
argument_list|,
operator|(
name|gdouble
operator|)
name|nth_drawable
operator|/
operator|(
name|gdouble
operator|)
name|n_drawables
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|layers
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_convert_profile_indexed (GimpImage * image,GimpColorProfile * src_profile,GimpColorProfile * dest_profile,GimpColorRenderingIntent intent,gboolean bpc,GimpProgress * progress)
name|gimp_image_convert_profile_indexed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|,
name|GimpColorRenderingIntent
name|intent
parameter_list|,
name|gboolean
name|bpc
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|cmsHPROFILE
name|src_lcms
decl_stmt|;
name|cmsHPROFILE
name|dest_lcms
decl_stmt|;
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|gint
name|n_colors
decl_stmt|;
name|GimpColorTransform
name|transform
decl_stmt|;
name|src_lcms
operator|=
name|gimp_color_profile_get_lcms_profile
argument_list|(
name|src_profile
argument_list|)
expr_stmt|;
name|dest_lcms
operator|=
name|gimp_color_profile_get_lcms_profile
argument_list|(
name|dest_profile
argument_list|)
expr_stmt|;
name|n_colors
operator|=
name|gimp_image_get_colormap_size
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|cmap
operator|=
name|g_memdup
argument_list|(
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|)
argument_list|,
name|n_colors
operator|*
literal|3
argument_list|)
expr_stmt|;
name|transform
operator|=
name|cmsCreateTransform
argument_list|(
name|src_lcms
argument_list|,
name|TYPE_RGB_8
argument_list|,
name|dest_lcms
argument_list|,
name|TYPE_RGB_8
argument_list|,
name|intent
argument_list|,
name|cmsFLAGS_NOOPTIMIZE
operator||
operator|(
name|bpc
condition|?
name|cmsFLAGS_BLACKPOINTCOMPENSATION
else|:
literal|0
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|transform
condition|)
block|{
name|cmsDoTransform
argument_list|(
name|transform
argument_list|,
name|cmap
argument_list|,
name|cmap
argument_list|,
name|n_colors
argument_list|)
expr_stmt|;
name|cmsDeleteTransform
argument_list|(
name|transform
argument_list|)
expr_stmt|;
name|gimp_image_set_colormap
argument_list|(
name|image
argument_list|,
name|cmap
argument_list|,
name|n_colors
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"cmsCreateTransform() failed!"
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|cmap
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

