begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpdrawable.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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

begin_include
include|#
directive|include
file|"gimptilebackendplugin.h"
end_include

begin_function
name|guchar
modifier|*
DECL|function|gimp_drawable_get_thumbnail_data (gint32 drawable_ID,gint * width,gint * height,gint * bpp)
name|gimp_drawable_get_thumbnail_data
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|bpp
parameter_list|)
block|{
name|gint
name|ret_width
decl_stmt|;
name|gint
name|ret_height
decl_stmt|;
name|guchar
modifier|*
name|image_data
decl_stmt|;
name|gint
name|data_size
decl_stmt|;
name|_gimp_drawable_thumbnail
argument_list|(
name|drawable_ID
argument_list|,
operator|*
name|width
argument_list|,
operator|*
name|height
argument_list|,
operator|&
name|ret_width
argument_list|,
operator|&
name|ret_height
argument_list|,
name|bpp
argument_list|,
operator|&
name|data_size
argument_list|,
operator|&
name|image_data
argument_list|)
expr_stmt|;
operator|*
name|width
operator|=
name|ret_width
expr_stmt|;
operator|*
name|height
operator|=
name|ret_height
expr_stmt|;
return|return
name|image_data
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_thumbnail:  * @drawable_ID: the drawable ID  * @width:       the requested thumbnail width  (<= 1024 pixels)  * @height:      the requested thumbnail height (<= 1024 pixels)  * @alpha:       how to handle an alpha channel  *  * Retrieves a thumbnail pixbuf for the drawable identified by  * @drawable_ID. The thumbnail will be not larger than the requested  * size.  *  * Returns: (transfer full): a new #GdkPixbuf  *  * Since: 2.2  **/
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
name|_gimp_pixbuf_from_data
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

begin_function
name|guchar
modifier|*
DECL|function|gimp_drawable_get_sub_thumbnail_data (gint32 drawable_ID,gint src_x,gint src_y,gint src_width,gint src_height,gint * dest_width,gint * dest_height,gint * bpp)
name|gimp_drawable_get_sub_thumbnail_data
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
modifier|*
name|dest_width
parameter_list|,
name|gint
modifier|*
name|dest_height
parameter_list|,
name|gint
modifier|*
name|bpp
parameter_list|)
block|{
name|gint
name|ret_width
decl_stmt|;
name|gint
name|ret_height
decl_stmt|;
name|guchar
modifier|*
name|image_data
decl_stmt|;
name|gint
name|data_size
decl_stmt|;
name|_gimp_drawable_sub_thumbnail
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
operator|*
name|dest_width
argument_list|,
operator|*
name|dest_height
argument_list|,
operator|&
name|ret_width
argument_list|,
operator|&
name|ret_height
argument_list|,
name|bpp
argument_list|,
operator|&
name|data_size
argument_list|,
operator|&
name|image_data
argument_list|)
expr_stmt|;
operator|*
name|dest_width
operator|=
name|ret_width
expr_stmt|;
operator|*
name|dest_height
operator|=
name|ret_height
expr_stmt|;
return|return
name|image_data
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_sub_thumbnail:  * @drawable_ID: the drawable ID  * @src_x:       the x coordinate of the area  * @src_y:       the y coordinate of the area  * @src_width:   the width of the area  * @src_height:  the height of the area  * @dest_width:  the requested thumbnail width  (<= 1024 pixels)  * @dest_height: the requested thumbnail height (<= 1024 pixels)  * @alpha:       how to handle an alpha channel  *  * Retrieves a thumbnail pixbuf for the drawable identified by  * @drawable_ID. The thumbnail will be not larger than the requested  * size.  *  * Returns: (transfer full): a new #GdkPixbuf  *  * Since: 2.2  **/
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
name|_gimp_pixbuf_from_data
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
comment|/**  * gimp_drawable_get_buffer:  * @drawable_ID: the ID of the #GimpDrawable to get the buffer for.  *  * Returns a #GeglBuffer of a specified drawable. The buffer can be used  * like any other GEGL buffer. Its data will we synced back with the core  * drawable when the buffer gets destroyed, or when gegl_buffer_flush()  * is called.  *  * Returns: (transfer full): The #GeglBuffer.  *  * See Also: gimp_drawable_get_shadow_buffer()  *  * Since: 2.10  */
end_comment

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_drawable_get_buffer (gint32 drawable_ID)
name|gimp_drawable_get_buffer
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
if|if
condition|(
name|gimp_item_is_valid
argument_list|(
name|drawable_ID
argument_list|)
condition|)
block|{
name|GeglTileBackend
modifier|*
name|backend
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|backend
operator|=
name|_gimp_tile_backend_plugin_new
argument_list|(
name|drawable_ID
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gegl_buffer_new_for_backend
argument_list|(
name|NULL
argument_list|,
name|backend
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|backend
argument_list|)
expr_stmt|;
return|return
name|buffer
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_shadow_buffer:  * @drawable_ID: the ID of the #GimpDrawable to get the buffer for.  *  * Returns a #GeglBuffer of a specified drawable's shadow tiles. The  * buffer can be used like any other GEGL buffer. Its data will we  * synced back with the core drawable's shadow tiles when the buffer  * gets destroyed, or when gegl_buffer_flush() is called.  *  * Returns: (transfer full): The #GeglBuffer.  *  * See Also: gimp_drawable_get_shadow_buffer()  *  * Since: 2.10  */
end_comment

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_drawable_get_shadow_buffer (gint32 drawable_ID)
name|gimp_drawable_get_shadow_buffer
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
if|if
condition|(
name|gimp_item_is_valid
argument_list|(
name|drawable_ID
argument_list|)
condition|)
block|{
name|GeglTileBackend
modifier|*
name|backend
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|backend
operator|=
name|_gimp_tile_backend_plugin_new
argument_list|(
name|drawable_ID
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gegl_buffer_new_for_backend
argument_list|(
name|NULL
argument_list|,
name|backend
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|backend
argument_list|)
expr_stmt|;
return|return
name|buffer
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_format:  * @drawable_ID: the ID of the #GimpDrawable to get the format for.  *  * Returns the #Babl format of the drawable.  *  * Returns: The #Babl format.  *  * Since: 2.10  */
end_comment

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_drawable_get_format (gint32 drawable_ID)
name|gimp_drawable_get_format
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
specifier|const
name|Babl
modifier|*
name|format
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|format_str
init|=
name|_gimp_drawable_get_format
argument_list|(
name|drawable_ID
argument_list|)
decl_stmt|;
comment|/* _gimp_drawable_get_format() only returns the encoding, so we    * create the actual space from the image's profile    */
if|if
condition|(
name|format_str
condition|)
block|{
name|gint32
name|image_ID
init|=
name|gimp_item_get_image
argument_list|(
name|drawable_ID
argument_list|)
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|space
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|gimp_item_is_layer
argument_list|(
name|drawable_ID
argument_list|)
condition|)
block|{
name|GimpColorProfile
modifier|*
name|profile
init|=
name|gimp_image_get_color_profile
argument_list|(
name|image_ID
argument_list|)
decl_stmt|;
if|if
condition|(
name|profile
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|space
operator|=
name|gimp_color_profile_get_space
argument_list|(
name|profile
argument_list|,
name|GIMP_COLOR_RENDERING_INTENT_RELATIVE_COLORIMETRIC
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|space
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: failed to create Babl space from "
literal|"profile: %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable_ID
argument_list|)
condition|)
block|{
specifier|const
name|Babl
modifier|*
name|palette
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|palette_alpha
decl_stmt|;
name|guchar
modifier|*
name|colormap
decl_stmt|;
name|gint
name|n_colors
decl_stmt|;
name|babl_new_palette_with_space
argument_list|(
name|format_str
argument_list|,
name|space
argument_list|,
operator|&
name|palette
argument_list|,
operator|&
name|palette_alpha
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable_ID
argument_list|)
condition|)
name|format
operator|=
name|palette_alpha
expr_stmt|;
else|else
name|format
operator|=
name|palette
expr_stmt|;
name|colormap
operator|=
name|gimp_image_get_colormap
argument_list|(
name|image_ID
argument_list|,
operator|&
name|n_colors
argument_list|)
expr_stmt|;
if|if
condition|(
name|colormap
condition|)
block|{
name|babl_palette_set_palette
argument_list|(
name|format
argument_list|,
name|babl_format_with_space
argument_list|(
literal|"R'G'B' u8"
argument_list|,
name|space
argument_list|)
argument_list|,
name|colormap
argument_list|,
name|n_colors
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|colormap
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|format
operator|=
name|babl_format_with_space
argument_list|(
name|format_str
argument_list|,
name|space
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|format_str
argument_list|)
expr_stmt|;
block|}
return|return
name|format
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_thumbnail_format:  * @drawable_ID: the ID of the #GimpDrawable to get the thumbnail format for.  *  * Returns the #Babl thumbnail format of the drawable.  *  * Returns: The #Babl thumbnail format.  *  * Since: 2.10.14  */
end_comment

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_drawable_get_thumbnail_format (gint32 drawable_ID)
name|gimp_drawable_get_thumbnail_format
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
specifier|const
name|Babl
modifier|*
name|format
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|format_str
init|=
name|_gimp_drawable_get_thumbnail_format
argument_list|(
name|drawable_ID
argument_list|)
decl_stmt|;
if|if
condition|(
name|format_str
condition|)
name|format
operator|=
name|babl_format
argument_list|(
name|format_str
argument_list|)
expr_stmt|;
return|return
name|format
return|;
block|}
end_function

end_unit

