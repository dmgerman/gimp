begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimplayer.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"gimp.h"
end_include

begin_struct
DECL|struct|_GimpLayerPrivate
struct|struct
name|_GimpLayerPrivate
block|{
DECL|member|unused
name|gpointer
name|unused
decl_stmt|;
block|}
struct|;
end_struct

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpLayer,gimp_layer,GIMP_TYPE_DRAWABLE)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpLayer
argument_list|,
argument|gimp_layer
argument_list|,
argument|GIMP_TYPE_DRAWABLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_layer_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_layer_class_init
parameter_list|(
name|GimpLayerClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_init (GimpLayer * layer)
name|gimp_layer_init
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
block|{
name|layer
operator|->
name|priv
operator|=
name|gimp_layer_get_instance_private
argument_list|(
name|layer
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Public API. */
end_comment

begin_comment
comment|/**  * gimp_layer_get_by_id:  * @layer_id: The layer id.  *  * Returns a #GimpLayer representing @layer_id. This function calls  * gimp_item_get_by_id() and returns the item if it is layer or %NULL  * otherwise.  *  * Returns: (nullable) (transfer none): a #GimpLayer for @layer_id or  *          %NULL if @layer_id does not represent a valid layer. The  *          object belongs to libgimp and you must not modify or unref  *          it.  *  * Since: 3.0  **/
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_layer_get_by_id (gint32 layer_id)
name|gimp_layer_get_by_id
parameter_list|(
name|gint32
name|layer_id
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|gimp_item_get_by_id
argument_list|(
name|layer_id
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|item
argument_list|)
condition|)
return|return
operator|(
name|GimpLayer
operator|*
operator|)
name|item
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_new:  * @image:   The image to which to add the layer.  * @name:    The layer name.  * @width:   The layer width.  * @height:  The layer height.  * @type:    The layer type.  * @opacity: The layer opacity.  * @mode:    The layer combination mode.  *  * Create a new layer.  *  * This procedure creates a new layer with the specified width, height,  * and type. Name, opacity, and mode are also supplied parameters. The  * new layer still needs to be added to the image, as this is not  * automatic. Add the new layer with the gimp_image_insert_layer()  * command. Other attributes such as layer mask modes, and offsets  * should be set with explicit procedure calls.  *  * Returns: (transfer none): The newly created layer.  *          The object belongs to libgimp and you should not free it.  *  * Since: 3.0  */
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_layer_new (GimpImage * image,const gchar * name,gint width,gint height,GimpImageType type,gdouble opacity,GimpLayerMode mode)
name|gimp_layer_new
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|image
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
comment|/**  * gimp_layer_copy:  * @layer: The layer to copy.  *  * Copy a layer.  *  * This procedure copies the specified layer and returns the copy. The  * newly copied layer is for use within the original layer's image. It  * should not be subsequently added to any other image.  *  * Returns: (transfer none): The newly copied layer.  *          The object belongs to libgimp and you should not free it.  *  * Since: 3.0  */
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_layer_copy (GimpLayer * layer)
name|gimp_layer_copy
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
block|{
return|return
name|_gimp_layer_copy
argument_list|(
name|layer
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_new_from_pixbuf:  * @image:          The RGB image to which to add the layer.  * @name:           The layer name.  * @pixbuf:         A GdkPixbuf.  * @opacity:        The layer opacity.  * @mode:           The layer combination mode.  * @progress_start: start of progress  * @progress_end:   end of progress  *  * Create a new layer from a %GdkPixbuf.  *  * This procedure creates a new layer from the given %GdkPixbuf.  The  * image has to be an RGB image and just like with gimp_layer_new()  * you will still need to add the layer to it.  *  * If you pass @progress_end> @progress_start to this function,  * gimp_progress_update() will be called for. You have to call  * gimp_progress_init() beforehand then.  *  * Returns: (transfer none): The newly created layer.  *          The object belongs to libgimp and you should not free it.  *  * Since: 2.2  */
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_layer_new_from_pixbuf (GimpImage * image,const gchar * name,GdkPixbuf * pixbuf,gdouble opacity,GimpLayerMode mode,gdouble progress_start,gdouble progress_end)
name|gimp_layer_new_from_pixbuf
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
name|GimpLayer
modifier|*
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
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|image
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
name|NULL
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
name|NULL
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
name|image
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
operator|!
name|layer
condition|)
return|return
name|NULL
return|;
name|dest_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
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
comment|/**  * gimp_layer_new_from_surface:  * @image:           The RGB image to which to add the layer.  * @name:            The layer name.  * @surface:         A Cairo image surface.  * @progress_start:  start of progress  * @progress_end:    end of progress  *  * Create a new layer from a #cairo_surface_t.  *  * This procedure creates a new layer from the given  * #cairo_surface_t. The image has to be an RGB image and just like  * with gimp_layer_new() you will still need to add the layer to it.  *  * If you pass @progress_end> @progress_start to this function,  * gimp_progress_update() will be called for. You have to call  * gimp_progress_init() beforehand then.  *  * Returns: (transfer none): The newly created layer.  *          The object belongs to libgimp and you should not free it.  *  * Since: 2.8  */
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_layer_new_from_surface (GimpImage * image,const gchar * name,cairo_surface_t * surface,gdouble progress_start,gdouble progress_end)
name|gimp_layer_new_from_surface
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|GeglBuffer
modifier|*
name|src_buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
name|GimpLayer
modifier|*
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
name|NULL
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
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|image
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
name|NULL
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
name|NULL
return|;
block|}
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
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
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
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
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
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

end_unit

