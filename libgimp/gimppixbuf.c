begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppixbuf.c  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
comment|/**  * gimp_image_get_thumbnail:  * @image_ID: the image ID  * @width:    the requested thumbnail width  (<= 256 pixels)  * @height:   the requested thumbnail height (<= 256 pixels)  * @alpha:    how to handle an alpha channel  *  * Retrieves a thumbnail pixbuf for the image identified by @image_ID.  * The thumbnail will be not larger than the requested size.  *  * Return value: a new #GdkPixbuf  *  * Since: GIMP 2.2  **/
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
decl_stmt|;
name|gint
name|thumb_height
decl_stmt|;
name|gint
name|thumb_bpp
decl_stmt|;
name|gint
name|data_size
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
literal|256
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
literal|256
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|_gimp_image_thumbnail
argument_list|(
name|image_ID
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|&
name|thumb_width
argument_list|,
operator|&
name|thumb_height
argument_list|,
operator|&
name|thumb_bpp
argument_list|,
operator|&
name|data_size
argument_list|,
operator|&
name|data
argument_list|)
condition|)
return|return
name|NULL
return|;
name|g_return_val_if_fail
argument_list|(
name|data_size
operator|==
operator|(
name|thumb_width
operator|*
name|thumb_height
operator|*
name|thumb_bpp
operator|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_thumbnail:  * @drawable_ID: the drawable ID  * @width:       the requested thumbnail width  (<= 256 pixels)  * @height:      the requested thumbnail height (<= 256 pixels)  * @alpha:       how to handle an alpha channel  *  * Retrieves a thumbnail pixbuf for the drawable identified by  * @drawable_ID. The thumbnail will be not larger than the requested  * size.  *  * Return value: a new #GdkPixbuf  *  * Since: GIMP 2.2  **/
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
decl_stmt|;
name|gint
name|thumb_height
decl_stmt|;
name|gint
name|thumb_bpp
decl_stmt|;
name|gint
name|data_size
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
literal|256
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
literal|256
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|_gimp_drawable_thumbnail
argument_list|(
name|drawable_ID
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|&
name|thumb_width
argument_list|,
operator|&
name|thumb_height
argument_list|,
operator|&
name|thumb_bpp
argument_list|,
operator|&
name|data_size
argument_list|,
operator|&
name|data
argument_list|)
condition|)
return|return
name|NULL
return|;
name|g_return_val_if_fail
argument_list|(
name|data_size
operator|==
operator|(
name|thumb_width
operator|*
name|thumb_height
operator|*
name|thumb_bpp
operator|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
block|}
end_function

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
name|g_return_val_if_fail
argument_list|(
name|bpp
operator|==
literal|3
operator|||
name|bpp
operator|==
literal|4
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gdk_pixbuf_new_from_data
argument_list|(
name|data
argument_list|,
name|GDK_COLORSPACE_RGB
argument_list|,
operator|(
name|bpp
operator|==
literal|4
operator|)
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

