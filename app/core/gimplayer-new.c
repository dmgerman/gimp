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
file|"gimpbuffer.h"
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
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer-new.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_layer_new_convert_buffer
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_layer_new (GimpImage * image,gint width,gint height,const Babl * format,const gchar * name,gdouble opacity,GimpLayerModeEffects mode)
name|gimp_layer_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|layer
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
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|layer
operator|=
name|GIMP_LAYER
argument_list|(
name|gimp_drawable_new
argument_list|(
name|GIMP_TYPE_LAYER
argument_list|,
name|image
argument_list|,
name|name
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|format
argument_list|)
argument_list|)
expr_stmt|;
name|opacity
operator|=
name|CLAMP
argument_list|(
name|opacity
argument_list|,
name|GIMP_OPACITY_TRANSPARENT
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|layer
operator|->
name|opacity
operator|=
name|opacity
expr_stmt|;
name|layer
operator|->
name|mode
operator|=
name|mode
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_new_from_buffer:  * @buffer:     The buffer to make the new layer from.  * @dest_image: The image the new layer will be added to.  * @format:     The #Babl format of the new layer.  * @name:       The new layer's name.  * @opacity:    The new layer's opacity.  * @mode:       The new layer's mode.  *  * Copies %buffer to a layer taking into consideration the  * possibility of transforming the contents to meet the requirements  * of the target image type  *  * Return value: The new layer.  **/
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_layer_new_from_buffer (GimpBuffer * buffer,GimpImage * dest_image,const Babl * format,const gchar * name,gdouble opacity,GimpLayerModeEffects mode)
name|gimp_layer_new_from_buffer
parameter_list|(
name|GimpBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|)
block|{
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|dest_image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_layer_new_from_gegl_buffer
argument_list|(
name|gimp_buffer_get_buffer
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|dest_image
argument_list|,
name|format
argument_list|,
name|name
argument_list|,
name|opacity
argument_list|,
name|mode
argument_list|,
name|gimp_buffer_get_color_profile
argument_list|(
name|buffer
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_new_from_gegl_buffer:  * @buffer:     The buffer to make the new layer from.  * @dest_image: The image the new layer will be added to.  * @format:     The #Babl format of the new layer.  * @name:       The new layer's name.  * @opacity:    The new layer's opacity.  * @mode:       The new layer's mode.  *  * Copies %buffer to a layer taking into consideration the  * possibility of transforming the contents to meet the requirements  * of the target image type  *  * Return value: The new layer.  **/
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_layer_new_from_gegl_buffer (GeglBuffer * buffer,GimpImage * dest_image,const Babl * format,const gchar * name,gdouble opacity,GimpLayerModeEffects mode,GimpColorProfile * buffer_profile)
name|gimp_layer_new_from_gegl_buffer
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|,
name|GimpColorProfile
modifier|*
name|buffer_profile
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|dest_image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|buffer_profile
operator|==
name|NULL
operator|||
name|GIMP_IS_COLOR_PROFILE
argument_list|(
name|buffer_profile
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  do *not* use the buffer's format because this function gets    *  buffers of any format passed, and converts them    */
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|dest_image
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
argument_list|,
name|format
argument_list|,
name|name
argument_list|,
name|opacity
argument_list|,
name|mode
argument_list|)
expr_stmt|;
name|gimp_layer_new_convert_buffer
argument_list|(
name|layer
argument_list|,
name|buffer
argument_list|,
name|buffer_profile
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_new_from_pixbuf:  * @pixbuf:     The pixbuf to make the new layer from.  * @dest_image: The image the new layer will be added to.  * @format:     The #Babl format of the new layer.  * @name:       The new layer's name.  * @opacity:    The new layer's opacity.  * @mode:       The new layer's mode.  *  * Copies %pixbuf to a layer taking into consideration the  * possibility of transforming the contents to meet the requirements  * of the target image type  *  * Return value: The new layer.  **/
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_layer_new_from_pixbuf (GdkPixbuf * pixbuf,GimpImage * dest_image,const Babl * format,const gchar * name,gdouble opacity,GimpLayerModeEffects mode)
name|gimp_layer_new_from_pixbuf
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|guint8
modifier|*
name|icc_data
decl_stmt|;
name|gsize
name|icc_len
decl_stmt|;
name|GimpColorProfile
modifier|*
name|profile
init|=
name|NULL
decl_stmt|;
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|dest_image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|dest_image
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
name|format
argument_list|,
name|name
argument_list|,
name|opacity
argument_list|,
name|mode
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_pixbuf_create_buffer
argument_list|(
name|pixbuf
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
name|profile
operator|=
name|gimp_color_profile_new_from_icc_profile
argument_list|(
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
name|gimp_layer_new_convert_buffer
argument_list|(
name|layer
argument_list|,
name|buffer
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
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_layer_new_convert_buffer (GimpLayer * layer,GeglBuffer * src_buffer,GimpColorProfile * src_profile,GError ** error)
name|gimp_layer_new_convert_buffer
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
decl_stmt|;
name|GeglBuffer
modifier|*
name|dest_buffer
init|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|GimpColorProfile
modifier|*
name|dest_profile
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_image_get_is_color_managed
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|gegl_buffer_copy
argument_list|(
name|src_buffer
argument_list|,
name|NULL
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|dest_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|src_profile
condition|)
block|{
specifier|const
name|Babl
modifier|*
name|src_format
init|=
name|gegl_buffer_get_format
argument_list|(
name|src_buffer
argument_list|)
decl_stmt|;
name|src_profile
operator|=
name|gimp_babl_format_get_color_profile
argument_list|(
name|src_format
argument_list|)
expr_stmt|;
block|}
name|dest_profile
operator|=
name|gimp_color_managed_get_color_profile
argument_list|(
name|GIMP_COLOR_MANAGED
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_gegl_convert_color_profile
argument_list|(
name|src_buffer
argument_list|,
name|NULL
argument_list|,
name|src_profile
argument_list|,
name|dest_buffer
argument_list|,
name|NULL
argument_list|,
name|dest_profile
argument_list|,
name|GIMP_COLOR_RENDERING_INTENT_PERCEPTUAL
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

