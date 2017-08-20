begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpconfig/gimpconfig.h"
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
file|"gimpbuffer.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-fill.h"
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
file|"gimpimage-new.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer-new.h"
end_include

begin_include
include|#
directive|include
file|"gimptemplate.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GimpTemplate
modifier|*
DECL|function|gimp_image_new_get_last_template (Gimp * gimp,GimpImage * image)
name|gimp_image_new_get_last_template
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|image
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|template
operator|=
name|gimp_template_new
argument_list|(
literal|"image new values"
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
operator|->
name|config
operator|->
name|default_image
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|template
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_template_set_from_image
argument_list|(
name|template
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
operator|->
name|image_new_last_template
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|template
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|template
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_new_set_last_template (Gimp * gimp,GimpTemplate * template)
name|gimp_image_new_set_last_template
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|template
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|gimp
operator|->
name|image_new_last_template
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_image_new_from_template (Gimp * gimp,GimpTemplate * template,GimpContext * context)
name|gimp_image_new_from_template
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpColorProfile
modifier|*
name|profile
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|comment
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_create_image
argument_list|(
name|gimp
argument_list|,
name|gimp_template_get_width
argument_list|(
name|template
argument_list|)
argument_list|,
name|gimp_template_get_height
argument_list|(
name|template
argument_list|)
argument_list|,
name|gimp_template_get_base_type
argument_list|(
name|template
argument_list|)
argument_list|,
name|gimp_template_get_precision
argument_list|(
name|template
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|comment
operator|=
name|gimp_template_get_comment
argument_list|(
name|template
argument_list|)
expr_stmt|;
if|if
condition|(
name|comment
condition|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"gimp-comment"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|comment
argument_list|)
operator|+
literal|1
argument_list|,
name|comment
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
argument_list|(
name|image
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
name|gimp_image_set_resolution
argument_list|(
name|image
argument_list|,
name|gimp_template_get_resolution_x
argument_list|(
name|template
argument_list|)
argument_list|,
name|gimp_template_get_resolution_y
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|image
argument_list|,
name|gimp_template_get_resolution_unit
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_set_is_color_managed
argument_list|(
name|image
argument_list|,
name|gimp_template_get_color_managed
argument_list|(
name|template
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|profile
operator|=
name|gimp_template_get_color_profile
argument_list|(
name|template
argument_list|)
expr_stmt|;
name|gimp_image_set_color_profile
argument_list|(
name|image
argument_list|,
name|profile
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
condition|)
name|g_object_unref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_template_get_fill_type
argument_list|(
name|template
argument_list|)
operator|==
name|GIMP_FILL_TRANSPARENT
condition|)
name|has_alpha
operator|=
name|TRUE
expr_stmt|;
else|else
name|has_alpha
operator|=
name|FALSE
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|gimp_image_get_layer_format
argument_list|(
name|image
argument_list|,
name|has_alpha
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|image
operator|->
name|gimp
operator|->
name|config
operator|->
name|default_new_layer_mode
argument_list|)
expr_stmt|;
name|gimp_drawable_fill
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
name|context
argument_list|,
name|gimp_template_get_fill_type
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_clean_all
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|image
return|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_image_new_from_drawable (Gimp * gimp,GimpDrawable * drawable)
name|gimp_image_new_from_drawable
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpImage
modifier|*
name|new_image
decl_stmt|;
name|GimpLayer
modifier|*
name|new_layer
decl_stmt|;
name|GType
name|new_type
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|GimpImageBaseType
name|type
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|GimpColorProfile
modifier|*
name|profile
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|type
operator|=
name|gimp_drawable_get_base_type
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|new_image
operator|=
name|gimp_create_image
argument_list|(
name|gimp
argument_list|,
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
argument_list|,
name|type
argument_list|,
name|gimp_drawable_get_precision
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
if|if
condition|(
name|type
operator|==
name|GIMP_INDEXED
condition|)
name|gimp_image_set_colormap
argument_list|(
name|new_image
argument_list|,
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_colormap_size
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
name|gimp_image_set_resolution
argument_list|(
name|new_image
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|new_image
argument_list|,
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_set_is_color_managed
argument_list|(
name|new_image
argument_list|,
name|gimp_image_get_is_color_managed
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|profile
operator|=
name|gimp_color_managed_get_color_profile
argument_list|(
name|GIMP_COLOR_MANAGED
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_set_color_profile
argument_list|(
name|new_image
argument_list|,
name|profile
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|drawable
argument_list|)
condition|)
name|new_type
operator|=
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
else|else
name|new_type
operator|=
name|GIMP_TYPE_LAYER
expr_stmt|;
name|new_layer
operator|=
name|GIMP_LAYER
argument_list|(
name|gimp_item_convert
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|new_image
argument_list|,
name|new_type
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|new_layer
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|new_layer
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|gimp_item_translate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|new_layer
argument_list|)
argument_list|,
operator|-
name|off_x
argument_list|,
operator|-
name|off_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_set_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|new_layer
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_set_linked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|new_layer
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_layer_set_mode
argument_list|(
name|new_layer
argument_list|,
name|new_image
operator|->
name|gimp
operator|->
name|config
operator|->
name|default_new_layer_mode
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_layer_set_opacity
argument_list|(
name|new_layer
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_layer_can_lock_alpha
argument_list|(
name|new_layer
argument_list|)
condition|)
name|gimp_layer_set_lock_alpha
argument_list|(
name|new_layer
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|new_image
argument_list|,
name|new_layer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
return|return
name|new_image
return|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_image_new_from_component (Gimp * gimp,GimpImage * image,GimpChannelType component)
name|gimp_image_new_from_component
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|component
parameter_list|)
block|{
name|GimpImage
modifier|*
name|new_image
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|desc
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|new_image
operator|=
name|gimp_create_image
argument_list|(
name|gimp
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
argument_list|,
name|GIMP_GRAY
argument_list|,
name|gimp_image_get_precision
argument_list|(
name|image
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
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
name|gimp_image_set_resolution
argument_list|(
name|new_image
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|new_image
argument_list|,
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|channel
operator|=
name|gimp_channel_new_from_component
argument_list|(
name|image
argument_list|,
name|component
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|layer
operator|=
name|GIMP_LAYER
argument_list|(
name|gimp_item_convert
argument_list|(
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|,
name|new_image
argument_list|,
name|GIMP_TYPE_LAYER
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|channel
argument_list|)
expr_stmt|;
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_CHANNEL_TYPE
argument_list|,
name|component
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|layer
argument_list|)
argument_list|,
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s Channel Copy"
argument_list|)
argument_list|,
name|desc
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|new_image
argument_list|,
name|layer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
return|return
name|new_image
return|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_image_new_from_buffer (Gimp * gimp,GimpBuffer * buffer)
name|gimp_image_new_from_buffer
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|gdouble
name|res_x
decl_stmt|;
name|gdouble
name|res_y
decl_stmt|;
name|GimpColorProfile
modifier|*
name|profile
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|format
operator|=
name|gimp_buffer_get_format
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|babl_format_has_alpha
argument_list|(
name|format
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_create_image
argument_list|(
name|gimp
argument_list|,
name|gimp_buffer_get_width
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|gimp_buffer_get_height
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|gimp_babl_format_get_base_type
argument_list|(
name|format
argument_list|)
argument_list|,
name|gimp_babl_format_get_precision
argument_list|(
name|format
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_buffer_get_resolution
argument_list|(
name|buffer
argument_list|,
operator|&
name|res_x
argument_list|,
operator|&
name|res_y
argument_list|)
condition|)
block|{
name|gimp_image_set_resolution
argument_list|(
name|image
argument_list|,
name|res_x
argument_list|,
name|res_y
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|image
argument_list|,
name|gimp_buffer_get_unit
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|profile
operator|=
name|gimp_buffer_get_color_profile
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_image_set_color_profile
argument_list|(
name|image
argument_list|,
name|profile
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new_from_buffer
argument_list|(
name|buffer
argument_list|,
name|image
argument_list|,
name|gimp_image_get_layer_format
argument_list|(
name|image
argument_list|,
name|has_alpha
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Pasted Layer"
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|image
operator|->
name|gimp
operator|->
name|config
operator|->
name|default_new_layer_mode
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|image
return|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_image_new_from_pixbuf (Gimp * gimp,GdkPixbuf * pixbuf,const gchar * layer_name)
name|gimp_image_new_from_pixbuf
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
specifier|const
name|gchar
modifier|*
name|layer_name
parameter_list|)
block|{
name|GimpImage
modifier|*
name|new_image
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpImageBaseType
name|base_type
decl_stmt|;
name|gboolean
name|has_alpha
init|=
name|FALSE
decl_stmt|;
name|guint8
modifier|*
name|icc_data
decl_stmt|;
name|gsize
name|icc_len
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GDK_IS_PIXBUF
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gdk_pixbuf_get_n_channels
argument_list|(
name|pixbuf
argument_list|)
condition|)
block|{
case|case
literal|2
case|:
name|has_alpha
operator|=
name|TRUE
expr_stmt|;
case|case
literal|1
case|:
name|base_type
operator|=
name|GIMP_GRAY
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|has_alpha
operator|=
name|TRUE
expr_stmt|;
case|case
literal|3
case|:
name|base_type
operator|=
name|GIMP_RGB
expr_stmt|;
break|break;
default|default:
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
name|new_image
operator|=
name|gimp_create_image
argument_list|(
name|gimp
argument_list|,
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|base_type
argument_list|,
name|GIMP_PRECISION_U8_GAMMA
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
name|icc_data
operator|=
name|gimp_pixbuf_get_icc_profile
argument_list|(
name|pixbuf
argument_list|,
operator|&
name|icc_len
argument_list|)
expr_stmt|;
if|if
condition|(
name|icc_data
condition|)
block|{
name|gimp_image_set_icc_profile
argument_list|(
name|new_image
argument_list|,
name|icc_data
argument_list|,
name|icc_len
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|icc_data
argument_list|)
expr_stmt|;
block|}
name|layer
operator|=
name|gimp_layer_new_from_pixbuf
argument_list|(
name|pixbuf
argument_list|,
name|new_image
argument_list|,
name|gimp_image_get_layer_format
argument_list|(
name|new_image
argument_list|,
name|has_alpha
argument_list|)
argument_list|,
name|layer_name
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|new_image
operator|->
name|gimp
operator|->
name|config
operator|->
name|default_new_layer_mode
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|new_image
argument_list|,
name|layer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
return|return
name|new_image
return|;
block|}
end_function

end_unit

