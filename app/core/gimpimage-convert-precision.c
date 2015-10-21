begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimage-convert-precision.c  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gegl/gimp-babl.h"
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
DECL|function|gimp_image_convert_precision (GimpImage * image,GimpPrecision precision,gint layer_dither_type,gint text_layer_dither_type,gint mask_dither_type,GimpProgress * progress)
name|gimp_image_convert_precision
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpPrecision
name|precision
parameter_list|,
name|gint
name|layer_dither_type
parameter_list|,
name|gint
name|text_layer_dither_type
parameter_list|,
name|gint
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
name|GList
modifier|*
name|all_drawables
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
name|gint
name|nth_drawable
decl_stmt|,
name|n_drawables
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
name|precision
operator|==
name|GIMP_PRECISION_U8_GAMMA
operator|||
name|gimp_image_get_base_type
argument_list|(
name|image
argument_list|)
operator|!=
name|GIMP_INDEXED
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
name|all_drawables
operator|=
name|g_list_concat
argument_list|(
name|gimp_image_get_layer_list
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_channel_list
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|n_drawables
operator|=
name|g_list_length
argument_list|(
name|all_drawables
argument_list|)
operator|+
literal|1
comment|/* + selection */
expr_stmt|;
switch|switch
condition|(
name|precision
condition|)
block|{
case|case
name|GIMP_PRECISION_U8_LINEAR
case|:
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to 8 bit linear integer"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PRECISION_U8_GAMMA
case|:
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to 8 bit gamma integer"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PRECISION_U16_LINEAR
case|:
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to 16 bit linear integer"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PRECISION_U16_GAMMA
case|:
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to 16 bit gamma integer"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PRECISION_U32_LINEAR
case|:
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to 32 bit linear integer"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PRECISION_U32_GAMMA
case|:
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to 32 bit gamma integer"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PRECISION_HALF_LINEAR
case|:
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to 16 bit linear floating point"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PRECISION_HALF_GAMMA
case|:
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to 16 bit gamma floating point"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PRECISION_FLOAT_LINEAR
case|:
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to 32 bit linear floating point"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PRECISION_FLOAT_GAMMA
case|:
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to 32 bit gamma floating point"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PRECISION_DOUBLE_LINEAR
case|:
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to 64 bit linear floating point"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PRECISION_DOUBLE_GAMMA
case|:
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Convert Image to 64 bit gamma floating point"
argument_list|)
expr_stmt|;
break|break;
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
literal|"%s"
argument_list|,
name|undo_desc
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
name|gimp_image_get_color_profile
argument_list|(
name|image
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
for|for
control|(
name|list
operator|=
name|all_drawables
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
name|gint
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
name|dither_type
argument_list|,
name|mask_dither_type
argument_list|,
name|old_profile
operator|!=
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
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
name|all_drawables
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_profile
operator|&&
name|gimp_babl_format_get_linear
argument_list|(
name|old_format
argument_list|)
operator|!=
name|gimp_babl_format_get_linear
argument_list|(
name|new_format
argument_list|)
condition|)
block|{
name|GimpColorProfile
modifier|*
name|new_profile
decl_stmt|;
comment|/* the comments in gimp_layer_convert_type() explain the logic        * here        */
if|if
condition|(
name|gimp_babl_format_get_linear
argument_list|(
name|new_format
argument_list|)
condition|)
block|{
name|new_profile
operator|=
name|gimp_color_profile_new_linear_rgb_from_color_profile
argument_list|(
name|old_profile
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|new_profile
operator|=
name|gimp_color_profile_new_srgb_gamma_from_color_profile
argument_list|(
name|old_profile
argument_list|)
expr_stmt|;
block|}
name|gimp_image_set_color_profile
argument_list|(
name|image
argument_list|,
name|new_profile
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_profile
condition|)
name|g_object_unref
argument_list|(
name|new_profile
argument_list|)
expr_stmt|;
block|}
comment|/*  convert the selection mask  */
block|{
name|GimpChannel
modifier|*
name|mask
init|=
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
decl_stmt|;
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
name|mask
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
name|gegl_buffer_copy
argument_list|(
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
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
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
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
name|nth_drawable
operator|++
expr_stmt|;
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

end_unit

