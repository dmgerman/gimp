begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimage-convert-precision.c  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gegl/gimp-babl.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-loops.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-operation.h"
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
file|"gimpimage-convert-precision.h"
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
file|"gimpobjectqueue.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"text/gimptextlayer.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_image_convert_precision (GimpImage * image,GimpPrecision precision,GeglDitherMethod layer_dither_type,GeglDitherMethod text_layer_dither_type,GeglDitherMethod mask_dither_type,GimpProgress * progress)
name|gimp_image_convert_precision
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpPrecision
name|precision
parameter_list|,
name|GeglDitherMethod
name|layer_dither_type
parameter_list|,
name|GeglDitherMethod
name|text_layer_dither_type
parameter_list|,
name|GeglDitherMethod
name|mask_dither_type
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpColorProfile
modifier|*
name|old_profile
decl_stmt|;
name|GimpColorProfile
modifier|*
name|new_profile
init|=
name|NULL
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|old_format
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|new_format
decl_stmt|;
name|GimpObjectQueue
modifier|*
name|queue
decl_stmt|;
name|GimpProgress
modifier|*
name|sub_progress
decl_stmt|;
name|GList
modifier|*
name|layers
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|enum_desc
decl_stmt|;
name|gchar
modifier|*
name|undo_desc
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|precision
operator|!=
name|gimp_image_get_precision
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_babl_is_valid
argument_list|(
name|gimp_image_get_base_type
argument_list|(
name|image
argument_list|)
argument_list|,
name|precision
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_PRECISION
argument_list|,
name|precision
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|enum_desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|undo_desc
operator|=
name|g_strdup_printf
argument_list|(
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to %s"
argument_list|)
argument_list|,
name|enum_desc
argument_list|)
expr_stmt|;
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
literal|"%s"
argument_list|,
name|undo_desc
argument_list|)
expr_stmt|;
name|queue
operator|=
name|gimp_object_queue_new
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|sub_progress
operator|=
name|GIMP_PROGRESS
argument_list|(
name|queue
argument_list|)
expr_stmt|;
name|layers
operator|=
name|gimp_image_get_layer_list
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_object_queue_push_list
argument_list|(
name|queue
argument_list|,
name|layers
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|layers
argument_list|)
expr_stmt|;
name|gimp_object_queue_push
argument_list|(
name|queue
argument_list|,
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_queue_push_container
argument_list|(
name|queue
argument_list|,
name|gimp_image_get_channels
argument_list|(
name|image
argument_list|)
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
name|g_free
argument_list|(
name|undo_desc
argument_list|)
expr_stmt|;
comment|/*  Push the image precision to the stack  */
name|gimp_image_undo_push_image_precision
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|old_profile
operator|=
name|gimp_color_managed_get_color_profile
argument_list|(
name|GIMP_COLOR_MANAGED
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|old_format
operator|=
name|gimp_image_get_layer_format
argument_list|(
name|image
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  Set the new precision  */
name|g_object_set
argument_list|(
name|image
argument_list|,
literal|"precision"
argument_list|,
name|precision
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|new_format
operator|=
name|gimp_image_get_layer_format
argument_list|(
name|image
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* we use old_format and new_format just for looking at their    * TRCs, new_format's space might be incorrect, don't use it    * for anything else.    */
if|if
condition|(
name|gimp_babl_format_get_trc
argument_list|(
name|old_format
argument_list|)
operator|!=
name|gimp_babl_format_get_trc
argument_list|(
name|new_format
argument_list|)
condition|)
block|{
name|GimpImageBaseType
name|base_type
init|=
name|gimp_image_get_base_type
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpTRCType
name|new_trc
init|=
name|gimp_babl_trc
argument_list|(
name|precision
argument_list|)
decl_stmt|;
comment|/* if the image doesn't use the builtin profile, create a new        * one, using the original profile's chromacities and        * whitepoint, but a linear/sRGB-gamma TRC.        */
if|if
condition|(
name|gimp_image_get_color_profile
argument_list|(
name|image
argument_list|)
condition|)
block|{
if|if
condition|(
name|new_trc
operator|==
name|GIMP_TRC_LINEAR
condition|)
block|{
name|new_profile
operator|=
name|gimp_color_profile_new_linear_from_color_profile
argument_list|(
name|old_profile
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|new_profile
operator|=
name|gimp_color_profile_new_srgb_trc_from_color_profile
argument_list|(
name|old_profile
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* we always need a profile for convert_type with changing TRC        * on the same image, use the new precision's builtin profile if        * the profile couldn't be converted or the image used the old        * TRC's builtin profile.        */
if|if
condition|(
operator|!
name|new_profile
condition|)
block|{
name|new_profile
operator|=
name|gimp_babl_get_builtin_color_profile
argument_list|(
name|base_type
argument_list|,
name|new_trc
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|new_profile
argument_list|)
expr_stmt|;
block|}
block|}
while|while
condition|(
operator|(
name|drawable
operator|=
name|gimp_object_queue_pop
argument_list|(
name|queue
argument_list|)
operator|)
condition|)
block|{
if|if
condition|(
name|drawable
operator|==
name|GIMP_DRAWABLE
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
condition|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|gimp_image_undo_push_mask_precision
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|GIMP_CHANNEL
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gegl_buffer_new
argument_list|(
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
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
argument_list|,
name|gimp_image_get_mask_format
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_gegl_buffer_copy
argument_list|(
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_set_buffer
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_progress_set_value
argument_list|(
name|sub_progress
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GeglDitherMethod
name|dither_type
decl_stmt|;
if|if
condition|(
name|gimp_item_is_text_layer
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
name|dither_type
operator|=
name|text_layer_dither_type
expr_stmt|;
else|else
name|dither_type
operator|=
name|layer_dither_type
expr_stmt|;
name|gimp_drawable_convert_type
argument_list|(
name|drawable
argument_list|,
name|image
argument_list|,
name|gimp_drawable_get_base_type
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|precision
argument_list|,
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|old_profile
argument_list|,
name|new_profile
argument_list|,
name|dither_type
argument_list|,
name|mask_dither_type
argument_list|,
name|TRUE
argument_list|,
name|sub_progress
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|new_profile
condition|)
block|{
name|gimp_image_set_color_profile
argument_list|(
name|image
argument_list|,
name|new_profile
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|new_profile
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_color_managed_profile_changed
argument_list|(
name|GIMP_COLOR_MANAGED
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_precision_changed
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
name|g_object_unref
argument_list|(
name|queue
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
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_convert_dither_u8 (GimpImage * image,GimpProgress * progress)
name|gimp_image_convert_dither_u8
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GeglNode
modifier|*
name|dither
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|dither
operator|=
name|gegl_node_new_child
argument_list|(
name|NULL
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:noise-rgb"
argument_list|,
literal|"red"
argument_list|,
literal|1.0
operator|/
literal|256.0
argument_list|,
literal|"green"
argument_list|,
literal|1.0
operator|/
literal|256.0
argument_list|,
literal|"blue"
argument_list|,
literal|1.0
operator|/
literal|256.0
argument_list|,
literal|"linear"
argument_list|,
name|FALSE
argument_list|,
literal|"gaussian"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|dither
condition|)
block|{
name|GimpObjectQueue
modifier|*
name|queue
decl_stmt|;
name|GimpProgress
modifier|*
name|sub_progress
decl_stmt|;
name|GList
modifier|*
name|layers
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
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
literal|"%s"
argument_list|,
name|_
argument_list|(
literal|"Dithering"
argument_list|)
argument_list|)
expr_stmt|;
name|queue
operator|=
name|gimp_object_queue_new
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|sub_progress
operator|=
name|GIMP_PROGRESS
argument_list|(
name|queue
argument_list|)
expr_stmt|;
name|layers
operator|=
name|gimp_image_get_layer_list
argument_list|(
name|image
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|layers
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
if|if
condition|(
operator|!
name|gimp_viewable_get_children
argument_list|(
name|list
operator|->
name|data
argument_list|)
operator|&&
operator|!
name|gimp_item_is_text_layer
argument_list|(
name|list
operator|->
name|data
argument_list|)
condition|)
block|{
name|gimp_object_queue_push
argument_list|(
name|queue
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
block|}
name|g_list_free
argument_list|(
name|layers
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|drawable
operator|=
name|gimp_object_queue_pop
argument_list|(
name|queue
argument_list|)
operator|)
condition|)
block|{
name|gimp_drawable_apply_operation
argument_list|(
name|drawable
argument_list|,
name|sub_progress
argument_list|,
name|_
argument_list|(
literal|"Dithering"
argument_list|)
argument_list|,
name|dither
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|queue
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
name|dither
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

