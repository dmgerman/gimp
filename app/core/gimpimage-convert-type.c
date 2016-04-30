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
file|"gimpimage-convert-type.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo-push.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimpsubprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_image_convert_type (GimpImage * image,GimpImageBaseType new_type,GimpColorProfile * dest_profile,GimpProgress * progress,GError ** error)
name|gimp_image_convert_type
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImageBaseType
name|new_type
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
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
name|GimpImageBaseType
name|old_type
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|new_layer_format
decl_stmt|;
name|GList
modifier|*
name|all_layers
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|undo_desc
init|=
name|NULL
decl_stmt|;
name|GimpProgress
modifier|*
name|sub_progress
init|=
name|NULL
decl_stmt|;
name|gint
name|nth_layer
decl_stmt|;
name|gint
name|n_layers
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
name|new_type
operator|!=
name|gimp_image_get_base_type
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|new_type
operator|!=
name|GIMP_INDEXED
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dest_profile
operator|==
name|NULL
operator|||
name|GIMP_IS_COLOR_PROFILE
argument_list|(
name|dest_profile
argument_list|)
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
name|new_layer_format
operator|=
name|gimp_babl_format
argument_list|(
name|new_type
argument_list|,
name|gimp_image_get_precision
argument_list|(
name|image
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|dest_profile
operator|&&
operator|!
name|gimp_image_validate_color_profile_by_format
argument_list|(
name|new_layer_format
argument_list|,
name|dest_profile
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
block|{
return|return
name|FALSE
return|;
block|}
switch|switch
condition|(
name|new_type
condition|)
block|{
case|case
name|GIMP_RGB
case|:
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to RGB"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY
case|:
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to Grayscale"
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_return_val_if_reached
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|gimp_set_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|all_layers
operator|=
name|gimp_image_get_layer_list
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|n_layers
operator|=
name|g_list_length
argument_list|(
name|all_layers
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|sub_progress
operator|=
name|gimp_sub_progress_new
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_CONVERT
argument_list|,
name|undo_desc
argument_list|)
expr_stmt|;
comment|/*  Push the image type to the stack  */
name|gimp_image_undo_push_image_type
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Set the new base type  */
name|old_type
operator|=
name|gimp_image_get_base_type
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|image
argument_list|,
literal|"base-type"
argument_list|,
name|new_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  When converting to/from GRAY, convert to the new type's builtin    *  profile if none was passed.    */
if|if
condition|(
name|old_type
operator|==
name|GIMP_GRAY
operator|||
name|new_type
operator|==
name|GIMP_GRAY
condition|)
block|{
if|if
condition|(
operator|!
name|dest_profile
operator|&&
name|gimp_image_get_color_profile
argument_list|(
name|image
argument_list|)
condition|)
name|dest_profile
operator|=
name|gimp_image_get_builtin_color_profile
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|list
operator|=
name|all_layers
operator|,
name|nth_layer
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
name|nth_layer
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
if|if
condition|(
name|sub_progress
condition|)
name|gimp_sub_progress_set_step
argument_list|(
name|GIMP_SUB_PROGRESS
argument_list|(
name|sub_progress
argument_list|)
argument_list|,
name|nth_layer
argument_list|,
name|n_layers
argument_list|)
expr_stmt|;
name|gimp_drawable_convert_type
argument_list|(
name|drawable
argument_list|,
name|image
argument_list|,
name|new_type
argument_list|,
name|gimp_drawable_get_precision
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|dest_profile
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
name|sub_progress
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|old_type
operator|==
name|GIMP_INDEXED
condition|)
name|gimp_image_unset_colormap
argument_list|(
name|image
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  When converting to/from GRAY, set the new profile.    */
if|if
condition|(
name|old_type
operator|==
name|GIMP_GRAY
operator|||
name|new_type
operator|==
name|GIMP_GRAY
condition|)
block|{
if|if
condition|(
name|gimp_image_get_color_profile
argument_list|(
name|image
argument_list|)
condition|)
name|gimp_image_set_color_profile
argument_list|(
name|image
argument_list|,
name|dest_profile
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|gimp_color_managed_profile_changed
argument_list|(
name|GIMP_COLOR_MANAGED
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|sub_progress
condition|)
name|gimp_progress_set_value
argument_list|(
name|sub_progress
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_mode_changed
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|all_layers
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

