begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *   * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
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
file|"paint-funcs/paint-funcs.h"
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
file|"gimpbuffer.h"
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
file|"gimpimage-new.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function
name|GimpImageNewValues
modifier|*
DECL|function|gimp_image_new_values_new (Gimp * gimp,GimpImage * gimage)
name|gimp_image_new_values_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpImageNewValues
modifier|*
name|values
decl_stmt|;
name|values
operator|=
name|g_new0
argument_list|(
name|GimpImageNewValues
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
name|values
operator|->
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|values
operator|->
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|values
operator|->
name|unit
operator|=
name|gimp_image_get_unit
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|gimage
argument_list|,
operator|&
name|values
operator|->
name|xresolution
argument_list|,
operator|&
name|values
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|values
operator|->
name|type
operator|=
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|values
operator|->
name|type
operator|==
name|GIMP_INDEXED
condition|)
name|values
operator|->
name|type
operator|=
name|GIMP_RGB
expr_stmt|;
comment|/* no indexed images */
block|}
else|else
block|{
operator|*
name|values
operator|=
name|gimp
operator|->
name|image_new_last_values
expr_stmt|;
block|}
if|if
condition|(
name|gimp
operator|->
name|global_buffer
operator|&&
name|gimp
operator|->
name|have_current_cut_buffer
condition|)
block|{
name|values
operator|->
name|width
operator|=
name|gimp_buffer_get_width
argument_list|(
name|gimp
operator|->
name|global_buffer
argument_list|)
expr_stmt|;
name|values
operator|->
name|height
operator|=
name|gimp_buffer_get_height
argument_list|(
name|gimp
operator|->
name|global_buffer
argument_list|)
expr_stmt|;
block|}
return|return
name|values
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_new_set_default_values (Gimp * gimp,GimpImageNewValues * values)
name|gimp_image_new_set_default_values
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImageNewValues
modifier|*
name|values
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|image_new_last_values
operator|=
operator|*
name|values
expr_stmt|;
name|gimp
operator|->
name|have_current_cut_buffer
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_new_values_free (GimpImageNewValues * values)
name|gimp_image_new_values_free
parameter_list|(
name|GimpImageNewValues
modifier|*
name|values
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|values
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gsize
DECL|function|gimp_image_new_calculate_memsize (GimpImageNewValues * values)
name|gimp_image_new_calculate_memsize
parameter_list|(
name|GimpImageNewValues
modifier|*
name|values
parameter_list|)
block|{
name|gint
name|channels
decl_stmt|;
name|channels
operator|=
operator|(
operator|(
name|values
operator|->
name|type
operator|==
name|GIMP_RGB
condition|?
literal|3
else|:
literal|1
operator|)
comment|/* color     */
operator|+
operator|(
name|values
operator|->
name|fill_type
operator|==
name|GIMP_TRANSPARENT_FILL
operator|)
comment|/* alpha     */
operator|+
literal|1
comment|/* selection */
operator|)
expr_stmt|;
return|return
name|channels
operator|*
name|values
operator|->
name|width
operator|*
name|values
operator|->
name|height
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_image_new_get_memsize_string (gsize memsize)
name|gimp_image_new_get_memsize_string
parameter_list|(
name|gsize
name|memsize
parameter_list|)
block|{
if|if
condition|(
name|memsize
operator|<
literal|4096
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%d Bytes"
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
name|memsize
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|memsize
operator|<
literal|1024
operator|*
literal|10
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%.2f KB"
argument_list|)
argument_list|,
operator|(
name|gdouble
operator|)
name|memsize
operator|/
literal|1024.0
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|memsize
operator|<
literal|1024
operator|*
literal|100
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%.1f KB"
argument_list|)
argument_list|,
operator|(
name|gdouble
operator|)
name|memsize
operator|/
literal|1024.0
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|memsize
operator|<
literal|1024
operator|*
literal|1024
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%d KB"
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
name|memsize
operator|/
literal|1024
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|memsize
operator|<
literal|1024
operator|*
literal|1024
operator|*
literal|10
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%.2f MB"
argument_list|)
argument_list|,
operator|(
name|gdouble
operator|)
name|memsize
operator|/
literal|1024.0
operator|/
literal|1024.0
argument_list|)
return|;
block|}
else|else
block|{
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%.1f MB"
argument_list|)
argument_list|,
operator|(
name|gdouble
operator|)
name|memsize
operator|/
literal|1024.0
operator|/
literal|1024.0
argument_list|)
return|;
block|}
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_image_new_create_image (Gimp * gimp,GimpImageNewValues * values)
name|gimp_image_new_create_image
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImageNewValues
modifier|*
name|values
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpImageType
name|type
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_new_set_default_values
argument_list|(
name|gimp
argument_list|,
name|values
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|values
operator|->
name|fill_type
condition|)
block|{
case|case
name|GIMP_FOREGROUND_FILL
case|:
case|case
name|GIMP_BACKGROUND_FILL
case|:
case|case
name|GIMP_WHITE_FILL
case|:
name|type
operator|=
operator|(
name|values
operator|->
name|type
operator|==
name|GIMP_RGB
operator|)
condition|?
name|GIMP_RGB_IMAGE
else|:
name|GIMP_GRAY_IMAGE
expr_stmt|;
break|break;
case|case
name|GIMP_TRANSPARENT_FILL
case|:
name|type
operator|=
operator|(
name|values
operator|->
name|type
operator|==
name|GIMP_RGB
operator|)
condition|?
name|GIMP_RGBA_IMAGE
else|:
name|GIMP_GRAYA_IMAGE
expr_stmt|;
break|break;
default|default:
name|type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
break|break;
block|}
name|gimage
operator|=
name|gimp_create_image
argument_list|(
name|gimp
argument_list|,
name|values
operator|->
name|width
argument_list|,
name|values
operator|->
name|height
argument_list|,
name|values
operator|->
name|type
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_set_resolution
argument_list|(
name|gimage
argument_list|,
name|values
operator|->
name|xresolution
argument_list|,
name|values
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|gimage
argument_list|,
name|values
operator|->
name|unit
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|gimage
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|type
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
condition|)
block|{
name|gimp_image_undo_disable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|gimage
argument_list|,
name|layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_drawable_fill_by_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
name|gimp_get_current_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|values
operator|->
name|fill_type
argument_list|)
expr_stmt|;
name|gimp_image_clean_all
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|gimp
argument_list|,
name|gimage
argument_list|,
literal|0x0101
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|gimage
return|;
block|}
end_function

end_unit

