begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppixbuf.c  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimppixbuf.h"
end_include

begin_comment
comment|/**  * SECTION: gimppixbuf  * @title: gimppixbuf  * @short_description: Get a thumbnail pixbuf for a drawable or image.  *  * Get a thumbnail pixbuf for a drawable or image.  **/
end_comment

begin_function_decl
specifier|static
name|GdkPixbuf
modifier|*
name|gimp_pixbuf_from_data
parameter_list|(
name|guchar
modifier|*
name|data
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|GimpPixbufTransparency
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_image_get_thumbnail:  * @image_ID: the image ID  * @width:    the requested thumbnail width  (<= 1024 pixels)  * @height:   the requested thumbnail height (<= 1024 pixels)  * @alpha:    how to handle an alpha channel  *  * Retrieves a thumbnail pixbuf for the image identified by @image_ID.  * The thumbnail will be not larger than the requested size.  *  * Return value: a new #GdkPixbuf  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GdkPixbuf
modifier|*
DECL|function|gimp_image_get_thumbnail (gint32 image_ID,gint width,gint height,GimpPixbufTransparency alpha)
name|gimp_image_get_thumbnail
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpPixbufTransparency
name|alpha
parameter_list|)
block|{
name|gint
name|thumb_width
init|=
name|width
decl_stmt|;
name|gint
name|thumb_height
init|=
name|height
decl_stmt|;
name|gint
name|thumb_bpp
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
operator|&&
name|width
operator|<=
literal|1024
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|height
operator|>
literal|0
operator|&&
name|height
operator|<=
literal|1024
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|=
name|gimp_image_get_thumbnail_data
argument_list|(
name|image_ID
argument_list|,
operator|&
name|thumb_width
argument_list|,
operator|&
name|thumb_height
argument_list|,
operator|&
name|thumb_bpp
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
return|return
name|gimp_pixbuf_from_data
argument_list|(
name|data
argument_list|,
name|thumb_width
argument_list|,
name|thumb_height
argument_list|,
name|thumb_bpp
argument_list|,
name|alpha
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_thumbnail:  * @drawable_ID: the drawable ID  * @width:       the requested thumbnail width  (<= 1024 pixels)  * @height:      the requested thumbnail height (<= 1024 pixels)  * @alpha:       how to handle an alpha channel  *  * Retrieves a thumbnail pixbuf for the drawable identified by  * @drawable_ID. The thumbnail will be not larger than the requested  * size.  *  * Return value: a new #GdkPixbuf  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GdkPixbuf
modifier|*
DECL|function|gimp_drawable_get_thumbnail (gint32 drawable_ID,gint width,gint height,GimpPixbufTransparency alpha)
name|gimp_drawable_get_thumbnail
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpPixbufTransparency
name|alpha
parameter_list|)
block|{
name|gint
name|thumb_width
init|=
name|width
decl_stmt|;
name|gint
name|thumb_height
init|=
name|height
decl_stmt|;
name|gint
name|thumb_bpp
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
operator|&&
name|width
operator|<=
literal|1024
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|height
operator|>
literal|0
operator|&&
name|height
operator|<=
literal|1024
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|=
name|gimp_drawable_get_thumbnail_data
argument_list|(
name|drawable_ID
argument_list|,
operator|&
name|thumb_width
argument_list|,
operator|&
name|thumb_height
argument_list|,
operator|&
name|thumb_bpp
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
return|return
name|gimp_pixbuf_from_data
argument_list|(
name|data
argument_list|,
name|thumb_width
argument_list|,
name|thumb_height
argument_list|,
name|thumb_bpp
argument_list|,
name|alpha
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_sub_thumbnail:  * @drawable_ID: the drawable ID  * @src_x:       the x coordinate of the area  * @src_y:       the y coordinate of the area  * @src_width:   the width of the area  * @src_height:  the height of the area  * @dest_width:  the requested thumbnail width  (<= 1024 pixels)  * @dest_height: the requested thumbnail height (<= 1024 pixels)  * @alpha:       how to handle an alpha channel  *  * Retrieves a thumbnail pixbuf for the drawable identified by  * @drawable_ID. The thumbnail will be not larger than the requested  * size.  *  * Return value: a new #GdkPixbuf  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GdkPixbuf
modifier|*
DECL|function|gimp_drawable_get_sub_thumbnail (gint32 drawable_ID,gint src_x,gint src_y,gint src_width,gint src_height,gint dest_width,gint dest_height,GimpPixbufTransparency alpha)
name|gimp_drawable_get_sub_thumbnail
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
name|src_width
parameter_list|,
name|gint
name|src_height
parameter_list|,
name|gint
name|dest_width
parameter_list|,
name|gint
name|dest_height
parameter_list|,
name|GimpPixbufTransparency
name|alpha
parameter_list|)
block|{
name|gint
name|thumb_width
init|=
name|dest_width
decl_stmt|;
name|gint
name|thumb_height
init|=
name|dest_height
decl_stmt|;
name|gint
name|thumb_bpp
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_x
operator|>=
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_y
operator|>=
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_width
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dest_width
operator|>
literal|0
operator|&&
name|dest_width
operator|<=
literal|1024
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dest_height
operator|>
literal|0
operator|&&
name|dest_height
operator|<=
literal|1024
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|=
name|gimp_drawable_get_sub_thumbnail_data
argument_list|(
name|drawable_ID
argument_list|,
name|src_x
argument_list|,
name|src_y
argument_list|,
name|src_width
argument_list|,
name|src_height
argument_list|,
operator|&
name|thumb_width
argument_list|,
operator|&
name|thumb_height
argument_list|,
operator|&
name|thumb_bpp
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
return|return
name|gimp_pixbuf_from_data
argument_list|(
name|data
argument_list|,
name|thumb_width
argument_list|,
name|thumb_height
argument_list|,
name|thumb_bpp
argument_list|,
name|alpha
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_new_from_pixbuf:  * @image_ID: The RGB image to which to add the layer.  * @name: The layer name.  * @pixbuf: A GdkPixbuf.  * @opacity: The layer opacity.  * @mode: The layer combination mode.  * @progress_start: start of progress  * @progress_end: end of progress  *  * Create a new layer from a %GdkPixbuf.  *  * This procedure creates a new layer from the given %GdkPixbuf.  The  * image has to be an RGB image and just like with gimp_layer_new()  * you will still need to add the layer to it.  *  * If you pass @progress_end> @progress_start to this function,  * gimp_progress_update() will be called for. You have to call  * gimp_progress_init() beforehand then.  *  * Returns: The newly created layer.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gint32
DECL|function|gimp_layer_new_from_pixbuf (gint32 image_ID,const gchar * name,GdkPixbuf * pixbuf,gdouble opacity,GimpLayerModeEffects mode,gdouble progress_start,gdouble progress_end)
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
name|GimpLayerModeEffects
name|mode
parameter_list|,
name|gdouble
name|progress_start
parameter_list|,
name|gdouble
name|progress_end
parameter_list|)
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
name|rowstride
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_comment
comment|/*  * The data that is passed to this function is either freed here or  * owned by the returned pixbuf.  */
end_comment

begin_function
specifier|static
name|GdkPixbuf
modifier|*
DECL|function|gimp_pixbuf_from_data (guchar * data,gint width,gint height,gint bpp,GimpPixbufTransparency alpha)
name|gimp_pixbuf_from_data
parameter_list|(
name|guchar
modifier|*
name|data
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|GimpPixbufTransparency
name|alpha
parameter_list|)
block|{
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
switch|switch
condition|(
name|bpp
condition|)
block|{
case|case
literal|1
case|:
name|pixbuf
operator|=
name|gdk_pixbuf_new
argument_list|(
name|GDK_COLORSPACE_RGB
argument_list|,
name|FALSE
argument_list|,
literal|8
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|{
name|guchar
modifier|*
name|src
init|=
name|data
decl_stmt|;
name|guchar
modifier|*
name|pixels
init|=
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
decl_stmt|;
name|gint
name|rowstride
init|=
name|gdk_pixbuf_get_rowstride
argument_list|(
name|pixbuf
argument_list|)
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
name|height
condition|;
name|y
operator|++
control|)
block|{
name|guchar
modifier|*
name|dest
init|=
name|pixels
decl_stmt|;
name|gint
name|x
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
operator|,
name|src
operator|+=
literal|1
operator|,
name|dest
operator|+=
literal|3
control|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|dest
index|[
literal|1
index|]
operator|=
name|dest
index|[
literal|2
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
block|}
name|pixels
operator|+=
name|rowstride
expr_stmt|;
block|}
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
name|bpp
operator|=
literal|3
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|pixbuf
operator|=
name|gdk_pixbuf_new
argument_list|(
name|GDK_COLORSPACE_RGB
argument_list|,
name|TRUE
argument_list|,
literal|8
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|{
name|guchar
modifier|*
name|src
init|=
name|data
decl_stmt|;
name|guchar
modifier|*
name|pixels
init|=
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
decl_stmt|;
name|gint
name|rowstride
init|=
name|gdk_pixbuf_get_rowstride
argument_list|(
name|pixbuf
argument_list|)
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
name|height
condition|;
name|y
operator|++
control|)
block|{
name|guchar
modifier|*
name|dest
init|=
name|pixels
decl_stmt|;
name|gint
name|x
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
operator|,
name|src
operator|+=
literal|2
operator|,
name|dest
operator|+=
literal|4
control|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|dest
index|[
literal|1
index|]
operator|=
name|dest
index|[
literal|2
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
name|dest
index|[
literal|3
index|]
operator|=
name|src
index|[
literal|1
index|]
expr_stmt|;
block|}
name|pixels
operator|+=
name|rowstride
expr_stmt|;
block|}
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
name|bpp
operator|=
literal|4
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|pixbuf
operator|=
name|gdk_pixbuf_new_from_data
argument_list|(
name|data
argument_list|,
name|GDK_COLORSPACE_RGB
argument_list|,
name|FALSE
argument_list|,
literal|8
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|width
operator|*
name|bpp
argument_list|,
operator|(
name|GdkPixbufDestroyNotify
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|pixbuf
operator|=
name|gdk_pixbuf_new_from_data
argument_list|(
name|data
argument_list|,
name|GDK_COLORSPACE_RGB
argument_list|,
name|TRUE
argument_list|,
literal|8
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|width
operator|*
name|bpp
argument_list|,
operator|(
name|GdkPixbufDestroyNotify
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|bpp
operator|==
literal|4
condition|)
block|{
name|GdkPixbuf
modifier|*
name|tmp
decl_stmt|;
name|gint
name|check_size
init|=
literal|0
decl_stmt|;
switch|switch
condition|(
name|alpha
condition|)
block|{
case|case
name|GIMP_PIXBUF_KEEP_ALPHA
case|:
return|return
name|pixbuf
return|;
case|case
name|GIMP_PIXBUF_SMALL_CHECKS
case|:
name|check_size
operator|=
name|GIMP_CHECK_SIZE_SM
expr_stmt|;
break|break;
case|case
name|GIMP_PIXBUF_LARGE_CHECKS
case|:
name|check_size
operator|=
name|GIMP_CHECK_SIZE
expr_stmt|;
break|break;
block|}
name|tmp
operator|=
name|gdk_pixbuf_new
argument_list|(
name|GDK_COLORSPACE_RGB
argument_list|,
name|FALSE
argument_list|,
literal|8
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gdk_pixbuf_composite_color
argument_list|(
name|pixbuf
argument_list|,
name|tmp
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|GDK_INTERP_NEAREST
argument_list|,
literal|255
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|check_size
argument_list|,
literal|0x66666666
argument_list|,
literal|0x99999999
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|tmp
expr_stmt|;
block|}
return|return
name|pixbuf
return|;
block|}
end_function

end_unit

