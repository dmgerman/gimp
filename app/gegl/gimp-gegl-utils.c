begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl-utils.h  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimptilebackendtilemanager.h"
end_include

begin_function
name|GimpImageType
DECL|function|gimp_babl_format_get_image_type (const Babl * format)
name|gimp_babl_format_get_image_type
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|format
operator|==
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
condition|)
return|return
name|GIMP_GRAY_IMAGE
return|;
elseif|else
if|if
condition|(
name|format
operator|==
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
condition|)
return|return
name|GIMP_GRAYA_IMAGE
return|;
elseif|else
if|if
condition|(
name|format
operator|==
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
condition|)
return|return
name|GIMP_RGB_IMAGE
return|;
elseif|else
if|if
condition|(
name|format
operator|==
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
condition|)
return|return
name|GIMP_RGBA_IMAGE
return|;
elseif|else
if|if
condition|(
name|babl_format_is_palette
argument_list|(
name|format
argument_list|)
condition|)
block|{
if|if
condition|(
name|babl_format_has_alpha
argument_list|(
name|format
argument_list|)
condition|)
return|return
name|GIMP_INDEXEDA_IMAGE
return|;
else|else
return|return
name|GIMP_INDEXED_IMAGE
return|;
block|}
name|g_return_val_if_reached
argument_list|(
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpImageBaseType
DECL|function|gimp_babl_format_get_base_type (const Babl * format)
name|gimp_babl_format_get_base_type
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|format
operator|==
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
operator|||
name|format
operator|==
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
condition|)
block|{
return|return
name|GIMP_GRAY
return|;
block|}
elseif|else
if|if
condition|(
name|format
operator|==
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
operator|||
name|format
operator|==
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
condition|)
block|{
return|return
name|GIMP_RGB
return|;
block|}
elseif|else
if|if
condition|(
name|babl_format_is_palette
argument_list|(
name|format
argument_list|)
condition|)
block|{
return|return
name|GIMP_INDEXED
return|;
block|}
name|g_return_val_if_reached
argument_list|(
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_bpp_to_babl_format:  * @bpp: bytes per pixel  *  * Return the Babl format to use for a given number of bytes per pixel.  * This function assumes that the data is 8bit.  *  * Return value: the Babl format to use  **/
end_comment

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_bpp_to_babl_format (guint bpp)
name|gimp_bpp_to_babl_format
parameter_list|(
name|guint
name|bpp
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|bpp
operator|>
literal|0
operator|&&
name|bpp
operator|<=
literal|4
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|bpp
condition|)
block|{
case|case
literal|1
case|:
return|return
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
return|;
case|case
literal|2
case|:
return|return
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
return|;
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
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_bpp_to_babl_format_with_alpha:  * @bpp: bytes per pixel  *  * Return the Babl format to use for a given number of bytes per pixel.  * This function assumes that the data is 8bit.  *  * Return value: the Babl format to use  **/
end_comment

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_bpp_to_babl_format_with_alpha (guint bpp)
name|gimp_bpp_to_babl_format_with_alpha
parameter_list|(
name|guint
name|bpp
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|bpp
operator|>
literal|0
operator|&&
name|bpp
operator|<=
literal|4
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|bpp
condition|)
block|{
case|case
literal|1
case|:
case|case
literal|2
case|:
return|return
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
return|;
case|case
literal|3
case|:
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
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_interpolation_to_gegl_filter (GimpInterpolationType interpolation)
name|gimp_interpolation_to_gegl_filter
parameter_list|(
name|GimpInterpolationType
name|interpolation
parameter_list|)
block|{
switch|switch
condition|(
name|interpolation
condition|)
block|{
case|case
name|GIMP_INTERPOLATION_NONE
case|:
return|return
literal|"nearest"
return|;
case|case
name|GIMP_INTERPOLATION_LINEAR
case|:
return|return
literal|"linear"
return|;
case|case
name|GIMP_INTERPOLATION_CUBIC
case|:
return|return
literal|"cubic"
return|;
case|case
name|GIMP_INTERPOLATION_LOHALO
case|:
return|return
literal|"lohalo"
return|;
default|default:
break|break;
block|}
return|return
literal|"nearest"
return|;
block|}
end_function

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
name|channels
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
name|channels
operator|=
name|gdk_pixbuf_get_n_channels
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
return|return
name|gegl_buffer_linear_new_from_data
argument_list|(
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gimp_bpp_to_babl_format
argument_list|(
name|channels
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
end_function

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_gegl_buffer_new (const GeglRectangle * rect,const Babl * format)
name|gimp_gegl_buffer_new
parameter_list|(
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
block|{
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rect
operator|!=
name|NULL
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
name|tiles
operator|=
name|tile_manager_new
argument_list|(
name|rect
operator|->
name|width
argument_list|,
name|rect
operator|->
name|height
argument_list|,
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_tile_manager_create_buffer
argument_list|(
name|tiles
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|tile_manager_unref
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
return|return
name|buffer
return|;
block|}
end_function

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_gegl_buffer_dup (GeglBuffer * buffer)
name|gimp_gegl_buffer_dup
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
block|{
specifier|const
name|Babl
modifier|*
name|format
init|=
name|gegl_buffer_get_format
argument_list|(
name|buffer
argument_list|)
decl_stmt|;
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|GeglBuffer
modifier|*
name|dup
decl_stmt|;
name|tiles
operator|=
name|tile_manager_new
argument_list|(
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
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
argument_list|)
expr_stmt|;
name|dup
operator|=
name|gimp_tile_manager_create_buffer
argument_list|(
name|tiles
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|tile_manager_unref
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|dup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dup
return|;
block|}
end_function

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_tile_manager_create_buffer (TileManager * tm,const Babl * format)
name|gimp_tile_manager_create_buffer
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
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
name|gimp_tile_backend_tile_manager_new
argument_list|(
name|tm
argument_list|,
name|format
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
end_function

begin_comment
comment|/* temp hack */
end_comment

begin_function_decl
name|GeglTileBackend
modifier|*
name|gegl_buffer_backend
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|TileManager
modifier|*
DECL|function|gimp_gegl_buffer_get_tiles (GeglBuffer * buffer)
name|gimp_gegl_buffer_get_tiles
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|GeglTileBackend
modifier|*
name|backend
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
name|backend
operator|=
name|gegl_buffer_backend
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TILE_BACKEND_TILE_MANAGER
argument_list|(
name|backend
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_buffer_flush
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|gimp_tile_backend_tile_manager_get_tiles
argument_list|(
name|backend
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_gegl_buffer_refetch_tiles (GeglBuffer * buffer)
name|gimp_gegl_buffer_refetch_tiles
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_tile_source_reinit
argument_list|(
name|GEGL_TILE_SOURCE
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GeglColor
modifier|*
DECL|function|gimp_gegl_color_new (const GimpRGB * rgb)
name|gimp_gegl_color_new
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|GeglColor
modifier|*
name|color
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|color
operator|=
name|gegl_color_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gegl_color_set_pixel
argument_list|(
name|color
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A double"
argument_list|)
argument_list|,
name|rgb
argument_list|)
expr_stmt|;
return|return
name|color
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_progress_notify (GObject * object,const GParamSpec * pspec,GimpProgress * progress)
name|gimp_gegl_progress_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|text
decl_stmt|;
name|gdouble
name|value
decl_stmt|;
name|g_object_get
argument_list|(
name|object
argument_list|,
literal|"progress"
argument_list|,
operator|&
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|text
operator|=
name|g_object_get_data
argument_list|(
name|object
argument_list|,
literal|"gimp-progress-text"
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
condition|)
block|{
if|if
condition|(
name|value
operator|==
literal|0.0
condition|)
block|{
name|gimp_progress_start
argument_list|(
name|progress
argument_list|,
name|text
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return;
block|}
elseif|else
if|if
condition|(
name|value
operator|==
literal|1.0
condition|)
block|{
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
name|gimp_progress_set_value
argument_list|(
name|progress
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_gegl_progress_connect (GeglNode * node,GimpProgress * progress,const gchar * text)
name|gimp_gegl_progress_connect
parameter_list|(
name|GeglNode
modifier|*
name|node
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
block|{
name|GObject
modifier|*
name|operation
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_NODE
argument_list|(
name|node
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|node
argument_list|,
literal|"gegl-operation"
argument_list|,
operator|&
name|operation
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|operation
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|operation
argument_list|,
literal|"notify::progress"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gegl_progress_notify
argument_list|)
argument_list|,
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
condition|)
name|g_object_set_data_full
argument_list|(
name|operation
argument_list|,
literal|"gimp-progress-text"
argument_list|,
name|g_strdup
argument_list|(
name|text
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|operation
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

