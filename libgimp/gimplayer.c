begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimplayer.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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

begin_define
DECL|macro|GIMP_DISABLE_DEPRECATION_WARNINGS
define|#
directive|define
name|GIMP_DISABLE_DEPRECATION_WARNINGS
end_define

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * gimp_layer_new:  * @image_ID: The image to which to add the layer.  * @name: The layer name.  * @width: The layer width.  * @height: The layer height.  * @type: The layer type.  * @opacity: The layer opacity.  * @mode: The layer combination mode.  *  * Create a new layer.  *  * This procedure creates a new layer with the specified width, height,  * and type. Name, opacity, and mode are also supplied parameters. The  * new layer still needs to be added to the image, as this is not  * automatic. Add the new layer with the gimp_image_insert_layer()  * command. Other attributes such as layer mask modes, and offsets  * should be set with explicit procedure calls.  *  * Returns: The newly created layer.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_layer_new (gint32 image_ID,const gchar * name,gint width,gint height,GimpImageType type,gdouble opacity,GimpLayerMode mode)
name|gimp_layer_new
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpImageType
name|type
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerMode
name|mode
parameter_list|)
block|{
return|return
name|_gimp_layer_new
argument_list|(
name|image_ID
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|type
argument_list|,
name|name
argument_list|,
name|opacity
argument_list|,
name|mode
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_copy:  * @layer_ID: The layer to copy.  *  * Copy a layer.  *  * This procedure copies the specified layer and returns the copy. The  * newly copied layer is for use within the original layer's image. It  * should not be subsequently added to any other image.  *  * Returns: The newly copied layer.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_layer_copy (gint32 layer_ID)
name|gimp_layer_copy
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
block|{
return|return
name|_gimp_layer_copy
argument_list|(
name|layer_ID
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_new_from_pixbuf:  * @image_ID:       The RGB image to which to add the layer.  * @name:           The layer name.  * @pixbuf:         A GdkPixbuf.  * @opacity:        The layer opacity.  * @mode:           The layer combination mode.  * @progress_start: start of progress  * @progress_end:   end of progress  *  * Create a new layer from a %GdkPixbuf.  *  * This procedure creates a new layer from the given %GdkPixbuf.  The  * image has to be an RGB image and just like with gimp_layer_new()  * you will still need to add the layer to it.  *  * If you pass @progress_end> @progress_start to this function,  * gimp_progress_update() will be called for. You have to call  * gimp_progress_init() beforehand then.  *  * Returns: The newly created layer.  *  * Since: 2.4  */
end_comment

begin_function
name|gint32
DECL|function|gimp_layer_new_from_pixbuf (gint32 image_ID,const gchar * name,GdkPixbuf * pixbuf,gdouble opacity,GimpLayerMode mode,gdouble progress_start,gdouble progress_end)
name|gimp_layer_new_from_pixbuf
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerMode
name|mode
parameter_list|,
name|gdouble
name|progress_start
parameter_list|,
name|gdouble
name|progress_end
parameter_list|)
block|{
name|gint32
name|layer
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gdouble
name|range
init|=
name|progress_end
operator|-
name|progress_start
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GDK_IS_PIXBUF
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|image_ID
argument_list|)
operator|!=
name|GIMP_RGB
condition|)
block|{
name|g_warning
argument_list|(
literal|"gimp_layer_new_from_pixbuf() needs an RGB image"
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
if|if
condition|(
name|gdk_pixbuf_get_colorspace
argument_list|(
name|pixbuf
argument_list|)
operator|!=
name|GDK_COLORSPACE_RGB
condition|)
block|{
name|g_warning
argument_list|(
literal|"gimp_layer_new_from_pixbuf() assumes that GdkPixbuf is RGB"
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|width
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|height
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|gdk_pixbuf_get_n_channels
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image_ID
argument_list|,
name|name
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|bpp
operator|==
literal|3
condition|?
name|GIMP_RGB_IMAGE
else|:
name|GIMP_RGBA_IMAGE
argument_list|,
name|opacity
argument_list|,
name|mode
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
operator|==
operator|-
literal|1
condition|)
return|return
operator|-
literal|1
return|;
if|if
condition|(
name|gimp_plugin_precision_enabled
argument_list|()
condition|)
block|{
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
name|dest_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|gegl_buffer_set
argument_list|(
name|dest_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
literal|0
argument_list|,
name|gimp_pixbuf_get_format
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gdk_pixbuf_get_rowstride
argument_list|(
name|pixbuf
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpPixelRgn
name|rgn
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|pixels
decl_stmt|;
name|gint
name|rowstride
decl_stmt|;
name|guint
name|done
init|=
literal|0
decl_stmt|;
name|guint
name|count
init|=
literal|0
decl_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|bpp
operator|==
name|rgn
operator|.
name|bpp
argument_list|)
expr_stmt|;
name|rowstride
operator|=
name|gdk_pixbuf_get_rowstride
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|pixels
operator|=
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
argument_list|,
operator|&
name|rgn
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
specifier|const
name|guchar
modifier|*
name|src
init|=
name|pixels
operator|+
name|rgn
operator|.
name|y
operator|*
name|rowstride
operator|+
name|rgn
operator|.
name|x
operator|*
name|bpp
decl_stmt|;
name|guchar
modifier|*
name|dest
init|=
name|rgn
operator|.
name|data
decl_stmt|;
name|gint
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|rgn
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|dest
argument_list|,
name|src
argument_list|,
name|rgn
operator|.
name|w
operator|*
name|rgn
operator|.
name|bpp
argument_list|)
expr_stmt|;
name|src
operator|+=
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|rgn
operator|.
name|rowstride
expr_stmt|;
block|}
if|if
condition|(
name|range
operator|>
literal|0.0
condition|)
block|{
name|done
operator|+=
name|rgn
operator|.
name|h
operator|*
name|rgn
operator|.
name|w
expr_stmt|;
if|if
condition|(
name|count
operator|++
operator|%
literal|32
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
name|progress_start
operator|+
operator|(
name|gdouble
operator|)
name|done
operator|/
operator|(
name|width
operator|*
name|height
operator|)
operator|*
name|range
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|range
operator|>
literal|0.0
condition|)
name|gimp_progress_update
argument_list|(
name|progress_end
argument_list|)
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_new_from_surface:  * @image_ID:        The RGB image to which to add the layer.  * @name:            The layer name.  * @surface:         A Cairo image surface.  * @progress_start:  start of progress  * @progress_end:    end of progress  *  * Create a new layer from a #cairo_surface_t.  *  * This procedure creates a new layer from the given  * #cairo_surface_t. The image has to be an RGB image and just like  * with gimp_layer_new() you will still need to add the layer to it.  *  * If you pass @progress_end> @progress_start to this function,  * gimp_progress_update() will be called for. You have to call  * gimp_progress_init() beforehand then.  *  * Returns: The newly created layer.  *  * Since: 2.8  */
end_comment

begin_function
name|gint32
DECL|function|gimp_layer_new_from_surface (gint32 image_ID,const gchar * name,cairo_surface_t * surface,gdouble progress_start,gdouble progress_end)
name|gimp_layer_new_from_surface
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|cairo_surface_t
modifier|*
name|surface
parameter_list|,
name|gdouble
name|progress_start
parameter_list|,
name|gdouble
name|progress_end
parameter_list|)
block|{
name|gint32
name|layer
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|cairo_format_t
name|format
decl_stmt|;
name|gdouble
name|range
init|=
name|progress_end
operator|-
name|progress_start
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|surface
operator|!=
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|cairo_surface_get_type
argument_list|(
name|surface
argument_list|)
operator|==
name|CAIRO_SURFACE_TYPE_IMAGE
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|image_ID
argument_list|)
operator|!=
name|GIMP_RGB
condition|)
block|{
name|g_warning
argument_list|(
literal|"gimp_layer_new_from_surface() needs an RGB image"
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|width
operator|=
name|cairo_image_surface_get_width
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|height
operator|=
name|cairo_image_surface_get_height
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|format
operator|=
name|cairo_image_surface_get_format
argument_list|(
name|surface
argument_list|)
expr_stmt|;
if|if
condition|(
name|format
operator|!=
name|CAIRO_FORMAT_ARGB32
operator|&&
name|format
operator|!=
name|CAIRO_FORMAT_RGB24
condition|)
block|{
name|g_warning
argument_list|(
literal|"gimp_layer_new_from_surface() assumes that surface is RGB"
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image_ID
argument_list|,
name|name
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|format
operator|==
name|CAIRO_FORMAT_RGB24
condition|?
name|GIMP_RGB_IMAGE
else|:
name|GIMP_RGBA_IMAGE
argument_list|,
literal|100.0
argument_list|,
name|gimp_image_get_default_new_layer_mode
argument_list|(
name|image_ID
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
operator|==
operator|-
literal|1
condition|)
return|return
operator|-
literal|1
return|;
if|if
condition|(
name|gimp_plugin_precision_enabled
argument_list|()
condition|)
block|{
name|GeglBuffer
modifier|*
name|src_buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
name|src_buffer
operator|=
name|gimp_cairo_surface_create_buffer
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|dest_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|layer
argument_list|)
expr_stmt|;
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
name|g_object_unref
argument_list|(
name|src_buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpPixelRgn
name|rgn
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|pixels
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|gsize
name|rowstride
decl_stmt|;
name|guint
name|count
init|=
literal|0
decl_stmt|;
name|guint
name|done
init|=
literal|0
decl_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|rowstride
operator|=
name|cairo_image_surface_get_stride
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|pixels
operator|=
name|cairo_image_surface_get_data
argument_list|(
name|surface
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
argument_list|,
operator|&
name|rgn
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
specifier|const
name|guchar
modifier|*
name|src
init|=
name|pixels
operator|+
name|rgn
operator|.
name|y
operator|*
name|rowstride
operator|+
name|rgn
operator|.
name|x
operator|*
literal|4
decl_stmt|;
name|guchar
modifier|*
name|dest
init|=
name|rgn
operator|.
name|data
decl_stmt|;
name|gint
name|y
decl_stmt|;
switch|switch
condition|(
name|format
condition|)
block|{
case|case
name|CAIRO_FORMAT_RGB24
case|:
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|rgn
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
name|gint
name|w
init|=
name|rgn
operator|.
name|w
decl_stmt|;
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|GIMP_CAIRO_RGB24_GET_PIXEL
argument_list|(
name|s
argument_list|,
name|d
index|[
literal|0
index|]
argument_list|,
name|d
index|[
literal|1
index|]
argument_list|,
name|d
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|s
operator|+=
literal|4
expr_stmt|;
name|d
operator|+=
literal|3
expr_stmt|;
block|}
name|src
operator|+=
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|rgn
operator|.
name|rowstride
expr_stmt|;
block|}
break|break;
case|case
name|CAIRO_FORMAT_ARGB32
case|:
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|rgn
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
name|gint
name|w
init|=
name|rgn
operator|.
name|w
decl_stmt|;
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|GIMP_CAIRO_ARGB32_GET_PIXEL
argument_list|(
name|s
argument_list|,
name|d
index|[
literal|0
index|]
argument_list|,
name|d
index|[
literal|1
index|]
argument_list|,
name|d
index|[
literal|2
index|]
argument_list|,
name|d
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|s
operator|+=
literal|4
expr_stmt|;
name|d
operator|+=
literal|4
expr_stmt|;
block|}
name|src
operator|+=
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|rgn
operator|.
name|rowstride
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|range
operator|>
literal|0.0
condition|)
block|{
name|done
operator|+=
name|rgn
operator|.
name|h
operator|*
name|rgn
operator|.
name|w
expr_stmt|;
if|if
condition|(
name|count
operator|++
operator|%
literal|32
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
name|progress_start
operator|+
operator|(
name|gdouble
operator|)
name|done
operator|/
operator|(
name|width
operator|*
name|height
operator|)
operator|*
name|range
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|range
operator|>
literal|0.0
condition|)
name|gimp_progress_update
argument_list|(
name|progress_end
argument_list|)
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_get_preserve_trans:  * @layer_ID: The layer.  *  * This procedure is deprecated! Use gimp_layer_get_lock_alpha() instead.  *  * Returns: The layer's preserve transperancy setting.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_layer_get_preserve_trans (gint32 layer_ID)
name|gimp_layer_get_preserve_trans
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
block|{
return|return
name|gimp_layer_get_lock_alpha
argument_list|(
name|layer_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_set_preserve_trans:  * @layer_ID: The layer.  * @preserve_trans: The new layer's preserve transperancy setting.  *  * This procedure is deprecated! Use gimp_layer_set_lock_alpha() instead.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_layer_set_preserve_trans (gint32 layer_ID,gboolean preserve_trans)
name|gimp_layer_set_preserve_trans
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|preserve_trans
parameter_list|)
block|{
return|return
name|gimp_layer_set_lock_alpha
argument_list|(
name|layer_ID
argument_list|,
name|preserve_trans
argument_list|)
return|;
block|}
end_function

end_unit

