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
file|<gtk/gtk.h>
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
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpcoreconfig.h"
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
name|void
DECL|function|gimp_image_new_init (Gimp * gimp)
name|gimp_image_new_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpImageBaseTypeName
modifier|*
name|new_type
decl_stmt|;
name|GimpFillTypeName
modifier|*
name|new_fill_type
decl_stmt|;
comment|/* Available Image Base Types */
name|new_type
operator|=
name|g_new
argument_list|(
name|GimpImageBaseTypeName
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|new_type
operator|->
name|type
operator|=
name|RGB
expr_stmt|;
name|new_type
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"RGB"
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|image_base_type_names
operator|=
name|g_list_append
argument_list|(
name|gimp
operator|->
name|image_base_type_names
argument_list|,
name|new_type
argument_list|)
expr_stmt|;
name|new_type
operator|=
name|g_new
argument_list|(
name|GimpImageBaseTypeName
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|new_type
operator|->
name|type
operator|=
name|GRAY
expr_stmt|;
name|new_type
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Grayscale"
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|image_base_type_names
operator|=
name|g_list_append
argument_list|(
name|gimp
operator|->
name|image_base_type_names
argument_list|,
name|new_type
argument_list|)
expr_stmt|;
comment|/* Available Fill Types */
name|new_fill_type
operator|=
name|g_new
argument_list|(
name|GimpFillTypeName
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|new_fill_type
operator|->
name|type
operator|=
name|FOREGROUND_FILL
expr_stmt|;
name|new_fill_type
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Foreground"
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|fill_type_names
operator|=
name|g_list_append
argument_list|(
name|gimp
operator|->
name|fill_type_names
argument_list|,
name|new_fill_type
argument_list|)
expr_stmt|;
name|new_fill_type
operator|=
name|g_new
argument_list|(
name|GimpFillTypeName
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|new_fill_type
operator|->
name|type
operator|=
name|BACKGROUND_FILL
expr_stmt|;
name|new_fill_type
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Background"
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|fill_type_names
operator|=
name|g_list_append
argument_list|(
name|gimp
operator|->
name|fill_type_names
argument_list|,
name|new_fill_type
argument_list|)
expr_stmt|;
name|new_fill_type
operator|=
name|g_new
argument_list|(
name|GimpFillTypeName
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|new_fill_type
operator|->
name|type
operator|=
name|WHITE_FILL
expr_stmt|;
name|new_fill_type
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"White"
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|fill_type_names
operator|=
name|g_list_append
argument_list|(
name|gimp
operator|->
name|fill_type_names
argument_list|,
name|new_fill_type
argument_list|)
expr_stmt|;
name|new_fill_type
operator|=
name|g_new
argument_list|(
name|GimpFillTypeName
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|new_fill_type
operator|->
name|type
operator|=
name|TRANSPARENT_FILL
expr_stmt|;
name|new_fill_type
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Transparent"
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|fill_type_names
operator|=
name|g_list_append
argument_list|(
name|gimp
operator|->
name|fill_type_names
argument_list|,
name|new_fill_type
argument_list|)
expr_stmt|;
comment|/* Set the last values used to default values. */
name|gimp
operator|->
name|image_new_last_values
operator|.
name|width
operator|=
name|gimp
operator|->
name|config
operator|->
name|default_width
expr_stmt|;
name|gimp
operator|->
name|image_new_last_values
operator|.
name|height
operator|=
name|gimp
operator|->
name|config
operator|->
name|default_height
expr_stmt|;
name|gimp
operator|->
name|image_new_last_values
operator|.
name|unit
operator|=
name|gimp
operator|->
name|config
operator|->
name|default_units
expr_stmt|;
name|gimp
operator|->
name|image_new_last_values
operator|.
name|xresolution
operator|=
name|gimp
operator|->
name|config
operator|->
name|default_xresolution
expr_stmt|;
name|gimp
operator|->
name|image_new_last_values
operator|.
name|yresolution
operator|=
name|gimp
operator|->
name|config
operator|->
name|default_yresolution
expr_stmt|;
name|gimp
operator|->
name|image_new_last_values
operator|.
name|res_unit
operator|=
name|gimp
operator|->
name|config
operator|->
name|default_resolution_units
expr_stmt|;
name|gimp
operator|->
name|image_new_last_values
operator|.
name|type
operator|=
name|gimp
operator|->
name|config
operator|->
name|default_type
expr_stmt|;
name|gimp
operator|->
name|image_new_last_values
operator|.
name|fill_type
operator|=
name|BACKGROUND_FILL
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
DECL|function|gimp_image_new_exit (Gimp * gimp)
name|gimp_image_new_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_list_foreach
argument_list|(
name|gimp
operator|->
name|image_base_type_names
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|gimp
operator|->
name|image_base_type_names
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|image_base_type_names
operator|=
name|NULL
expr_stmt|;
name|g_list_foreach
argument_list|(
name|gimp
operator|->
name|fill_type_names
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|gimp
operator|->
name|fill_type_names
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|fill_type_names
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_image_new_get_base_type_names (Gimp * gimp)
name|gimp_image_new_get_base_type_names
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
return|return
name|gimp
operator|->
name|image_base_type_names
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_image_new_get_fill_type_names (Gimp * gimp)
name|gimp_image_new_get_fill_type_names
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
return|return
name|gimp
operator|->
name|fill_type_names
return|;
block|}
end_function

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
name|INDEXED
condition|)
name|values
operator|->
name|type
operator|=
name|RGB
expr_stmt|;
comment|/* no indexed images */
block|}
else|else
block|{
name|memcpy
argument_list|(
name|values
argument_list|,
operator|&
name|gimp
operator|->
name|image_new_last_values
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpImageNewValues
argument_list|)
argument_list|)
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
name|tile_manager_width
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
name|tile_manager_height
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
name|memcpy
argument_list|(
operator|&
name|gimp
operator|->
name|image_new_last_values
argument_list|,
name|values
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpImageNewValues
argument_list|)
argument_list|)
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
name|gdouble
DECL|function|gimp_image_new_calculate_size (GimpImageNewValues * values)
name|gimp_image_new_calculate_size
parameter_list|(
name|GimpImageNewValues
modifier|*
name|values
parameter_list|)
block|{
name|gdouble
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gdouble
name|size
decl_stmt|;
name|width
operator|=
operator|(
name|gdouble
operator|)
name|values
operator|->
name|width
expr_stmt|;
name|height
operator|=
operator|(
name|gdouble
operator|)
name|values
operator|->
name|height
expr_stmt|;
name|size
operator|=
name|width
operator|*
name|height
operator|*
operator|(
operator|(
name|values
operator|->
name|type
operator|==
name|RGB
condition|?
literal|3
else|:
literal|1
operator|)
operator|+
comment|/* bytes per pixel */
operator|(
name|values
operator|->
name|fill_type
operator|==
name|TRANSPARENT_FILL
condition|?
literal|1
else|:
literal|0
operator|)
operator|)
expr_stmt|;
comment|/* alpha channel */
return|return
name|size
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_image_new_get_size_string (gdouble size)
name|gimp_image_new_get_size_string
parameter_list|(
name|gdouble
name|size
parameter_list|)
block|{
if|if
condition|(
name|size
operator|<
literal|4096
condition|)
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
name|size
argument_list|)
return|;
elseif|else
if|if
condition|(
name|size
operator|<
literal|1024
operator|*
literal|10
condition|)
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%.2f KB"
argument_list|)
argument_list|,
name|size
operator|/
literal|1024
argument_list|)
return|;
elseif|else
if|if
condition|(
name|size
operator|<
literal|1024
operator|*
literal|100
condition|)
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%.1f KB"
argument_list|)
argument_list|,
name|size
operator|/
literal|1024
argument_list|)
return|;
elseif|else
if|if
condition|(
name|size
operator|<
literal|1024
operator|*
literal|1024
condition|)
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
name|size
operator|/
literal|1024
argument_list|)
return|;
elseif|else
if|if
condition|(
name|size
operator|<
literal|1024
operator|*
literal|1024
operator|*
literal|10
condition|)
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%.2f MB"
argument_list|)
argument_list|,
name|size
operator|/
literal|1024
operator|/
literal|1024
argument_list|)
return|;
else|else
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%.1f MB"
argument_list|)
argument_list|,
name|size
operator|/
literal|1024
operator|/
literal|1024
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_new_set_have_current_cut_buffer (Gimp * gimp)
name|gimp_image_new_set_have_current_cut_buffer
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gimp
operator|->
name|have_current_cut_buffer
operator|=
name|TRUE
expr_stmt|;
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
name|FOREGROUND_FILL
case|:
case|case
name|BACKGROUND_FILL
case|:
case|case
name|WHITE_FILL
case|:
name|type
operator|=
operator|(
name|values
operator|->
name|type
operator|==
name|RGB
operator|)
condition|?
name|RGB_GIMAGE
else|:
name|GRAY_GIMAGE
expr_stmt|;
break|break;
case|case
name|TRANSPARENT_FILL
case|:
name|type
operator|=
operator|(
name|values
operator|->
name|type
operator|==
name|RGB
operator|)
condition|?
name|RGBA_GIMAGE
else|:
name|GRAYA_GIMAGE
expr_stmt|;
break|break;
default|default:
name|type
operator|=
name|RGB_GIMAGE
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
name|OPAQUE_OPACITY
argument_list|,
name|NORMAL_MODE
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
argument_list|)
expr_stmt|;
block|}
return|return
name|gimage
return|;
block|}
end_function

end_unit

