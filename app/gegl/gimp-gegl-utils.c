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
file|"gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimptilebackendtilemanager.h"
end_include

begin_comment
comment|/**  * gimp_bpp_to_babl_format:  * @bpp: bytes per pixel  * @linear: whether the pixels are linear or gamma-corrected.  *  * Return the Babl format to use for a given number of bytes per pixel.  * This function assumes that the data is 8bit.  *  * Return value: the Babl format to use  **/
end_comment

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_bpp_to_babl_format (guint bpp,gboolean linear)
name|gimp_bpp_to_babl_format
parameter_list|(
name|guint
name|bpp
parameter_list|,
name|gboolean
name|linear
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
if|if
condition|(
name|linear
condition|)
block|{
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
literal|"Y u8"
argument_list|)
return|;
case|case
literal|2
case|:
return|return
name|babl_format
argument_list|(
literal|"YA u8"
argument_list|)
return|;
case|case
literal|3
case|:
return|return
name|babl_format
argument_list|(
literal|"RGB u8"
argument_list|)
return|;
case|case
literal|4
case|:
return|return
name|babl_format
argument_list|(
literal|"RGBA u8"
argument_list|)
return|;
block|}
block|}
else|else
block|{
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
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_bpp_to_babl_format_with_alpha:  * @bpp: bytes per pixel  * @linear: whether the pixels are linear or gamma-corrected.  *  * Return the Babl format to use for a given number of bytes per pixel.  * This function assumes that the data is 8bit.  *  * Return value: the Babl format to use  **/
end_comment

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_bpp_to_babl_format_with_alpha (guint bpp,gboolean linear)
name|gimp_bpp_to_babl_format_with_alpha
parameter_list|(
name|guint
name|bpp
parameter_list|,
name|gboolean
name|linear
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
if|if
condition|(
name|linear
condition|)
block|{
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
literal|"YA u8"
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
literal|"RGBA u8"
argument_list|)
return|;
block|}
block|}
else|else
block|{
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
DECL|function|gimp_layer_mode_to_gegl_operation (GimpLayerModeEffects mode)
name|gimp_layer_mode_to_gegl_operation
parameter_list|(
name|GimpLayerModeEffects
name|mode
parameter_list|)
block|{
switch|switch
condition|(
name|mode
condition|)
block|{
case|case
name|GIMP_NORMAL_MODE
case|:
return|return
literal|"gegl:over"
return|;
case|case
name|GIMP_DISSOLVE_MODE
case|:
return|return
literal|"gimp:dissolve-mode"
return|;
case|case
name|GIMP_BEHIND_MODE
case|:
return|return
literal|"gimp:behind-mode"
return|;
case|case
name|GIMP_MULTIPLY_MODE
case|:
return|return
literal|"gimp:multiply-mode"
return|;
case|case
name|GIMP_SCREEN_MODE
case|:
return|return
literal|"gimp:screen-mode"
return|;
case|case
name|GIMP_OVERLAY_MODE
case|:
return|return
literal|"gimp:overlay-mode"
return|;
case|case
name|GIMP_DIFFERENCE_MODE
case|:
return|return
literal|"gimp:difference-mode"
return|;
case|case
name|GIMP_ADDITION_MODE
case|:
return|return
literal|"gimp:addition-mode"
return|;
case|case
name|GIMP_SUBTRACT_MODE
case|:
return|return
literal|"gimp:subtract-mode"
return|;
case|case
name|GIMP_DARKEN_ONLY_MODE
case|:
return|return
literal|"gimp:darken-mode"
return|;
case|case
name|GIMP_LIGHTEN_ONLY_MODE
case|:
return|return
literal|"gimp:lighten-mode"
return|;
case|case
name|GIMP_HUE_MODE
case|:
return|return
literal|"gimp:hue-mode"
return|;
case|case
name|GIMP_SATURATION_MODE
case|:
return|return
literal|"gimp:saturation-mode"
return|;
case|case
name|GIMP_COLOR_MODE
case|:
return|return
literal|"gimp:color-mode"
return|;
case|case
name|GIMP_VALUE_MODE
case|:
return|return
literal|"gimp:value-mode"
return|;
case|case
name|GIMP_DIVIDE_MODE
case|:
return|return
literal|"gimp:divide-mode"
return|;
case|case
name|GIMP_DODGE_MODE
case|:
return|return
literal|"gimp:dodge-mode"
return|;
case|case
name|GIMP_BURN_MODE
case|:
return|return
literal|"gimp:burn-mode"
return|;
case|case
name|GIMP_HARDLIGHT_MODE
case|:
return|return
literal|"gimp:hardlight-mode"
return|;
case|case
name|GIMP_SOFTLIGHT_MODE
case|:
return|return
literal|"gimp:softlight-mode"
return|;
case|case
name|GIMP_GRAIN_EXTRACT_MODE
case|:
return|return
literal|"gimp:grain-extract-mode"
return|;
case|case
name|GIMP_GRAIN_MERGE_MODE
case|:
return|return
literal|"gimp:grain-merge-mode"
return|;
case|case
name|GIMP_COLOR_ERASE_MODE
case|:
return|return
literal|"gimp:color-erase-mode"
return|;
case|case
name|GIMP_ERASE_MODE
case|:
return|return
literal|"gimp:erase-mode"
return|;
case|case
name|GIMP_REPLACE_MODE
case|:
return|return
literal|"gimp:replace-mode"
return|;
case|case
name|GIMP_ANTI_ERASE_MODE
case|:
return|return
literal|"gimp:anti-erase-mode"
return|;
default|default:
break|break;
block|}
return|return
literal|"gegl:over"
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
name|GIMP_INTERPOLATION_LANCZOS
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
name|GeglRectangle
name|rect
init|=
block|{
literal|0
block|, }
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
name|rect
operator|.
name|width
operator|=
name|width
expr_stmt|;
name|rect
operator|.
name|height
operator|=
name|height
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
argument_list|,
name|TRUE
argument_list|)
argument_list|,
operator|&
name|rect
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
argument_list|,
name|TRUE
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
DECL|function|gimp_tile_manager_create_buffer (TileManager * tm,const Babl * format,gboolean write)
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
parameter_list|,
name|gboolean
name|write
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
argument_list|,
name|write
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
name|gegl_color_set_rgba
argument_list|(
name|color
argument_list|,
name|rgb
operator|->
name|r
argument_list|,
name|rgb
operator|->
name|g
argument_list|,
name|rgb
operator|->
name|b
argument_list|,
name|rgb
operator|->
name|a
argument_list|)
expr_stmt|;
return|return
name|color
return|;
block|}
end_function

end_unit

