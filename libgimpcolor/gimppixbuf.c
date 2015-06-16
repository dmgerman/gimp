begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppixbuf.c  * Copyright (C) 2012  Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"gimpcolortypes.h"
end_include

begin_include
include|#
directive|include
file|"gimppixbuf.h"
end_include

begin_comment
comment|/**  * SECTION: gimppixbuf  * @title: GimpPixbuf  * @short_description: Definitions and Functions relating to GdkPixbuf.  *  * Definitions and Functions relating to GdkPixbuf.  **/
end_comment

begin_comment
comment|/**  * gimp_pixbuf_get_format:  * @pixbuf: a #GdkPixbuf  *  * Returns the Babl format that corresponds to the @pixbuf's pixel format.  *  * Return value: the @pixbuf's pixel format  *  * Since: 2.10  **/
end_comment

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_pixbuf_get_format (GdkPixbuf * pixbuf)
name|gimp_pixbuf_get_format
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|)
block|{
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
literal|3
case|:
return|return
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
return|;
case|case
literal|4
case|:
return|return
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
return|;
block|}
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_pixbuf_create_buffer:  * @pixbuf: a #GdkPixbuf  *  * Returns a #GeglBuffer that's either backed by the @pixbuf's pixels,  * or a copy of them. This function tries to not copy the @pixbuf's  * pixels. If the pixbuf's rowstride is a multiple of its bpp, a  * simple reference to the @pixbuf's pixels is made and @pixbuf will  * be kept around for as long as the buffer exists; otherwise the  * pixels are copied.  *  * Return value: a new #GeglBuffer.  *  * Since: 2.10  **/
end_comment

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_pixbuf_create_buffer (GdkPixbuf * pixbuf)
name|gimp_pixbuf_create_buffer
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|)
block|{
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
name|rowstride
operator|=
name|gdk_pixbuf_get_rowstride
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
if|if
condition|(
operator|(
name|rowstride
operator|%
name|bpp
operator|)
operator|==
literal|0
condition|)
block|{
return|return
name|gegl_buffer_linear_new_from_data
argument_list|(
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gimp_pixbuf_get_format
argument_list|(
name|pixbuf
argument_list|)
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
name|rowstride
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|,
name|g_object_ref
argument_list|(
name|pixbuf
argument_list|)
argument_list|)
return|;
block|}
else|else
block|{
name|GeglBuffer
modifier|*
name|buffer
init|=
name|gegl_buffer_new
argument_list|(
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
name|gimp_pixbuf_get_format
argument_list|(
name|pixbuf
argument_list|)
argument_list|)
decl_stmt|;
name|gegl_buffer_set
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|NULL
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
return|return
name|buffer
return|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_pixbuf_get_icc_profile:  * @pixbuf: a #GdkPixbuf  * @length: return location for the ICC profile's length  *  * Returns the ICC profile attached to the @pixbuf, or %NULL if there  * is none.  *  * Return value: The ICC profile data, or %NULL. The value should be freed  *               with g_free().  *  * Since: 2.10  **/
end_comment

begin_function
name|guint8
modifier|*
DECL|function|gimp_pixbuf_get_icc_profile (GdkPixbuf * pixbuf,gsize * length)
name|gimp_pixbuf_get_icc_profile
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
name|gsize
modifier|*
name|length
parameter_list|)
block|{
name|gchar
modifier|*
name|icc_base64
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
name|length
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|pixbuf
argument_list|,
literal|"icc-profile"
argument_list|,
name|icc_base64
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|icc_base64
condition|)
block|{
name|guint8
modifier|*
name|icc_data
decl_stmt|;
name|icc_data
operator|=
name|g_base64_decode
argument_list|(
name|icc_base64
argument_list|,
name|length
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|icc_base64
argument_list|)
expr_stmt|;
return|return
name|icc_data
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

