begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpdrawable.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_define
DECL|macro|TILE_WIDTH
define|#
directive|define
name|TILE_WIDTH
value|gimp_tile_width()
end_define

begin_define
DECL|macro|TILE_HEIGHT
define|#
directive|define
name|TILE_HEIGHT
value|gimp_tile_height()
end_define

begin_comment
comment|/**  * gimp_drawable_get:  * @drawable_ID: the ID of the drawable  *  * This function creates a #GimpDrawable structure for the core  * drawable identified by @drawable_ID. The returned structure  * contains some basic information about the drawable and can also  * hold tile data for transfer to and from the core.  *  * Note that the name of this function is somewhat misleading, because  * it suggests that it simply returns a handle.  This is not the case:  * if the function is called multiple times, it creates separate tile  * lists each time, which will usually produce undesired results.  *  * When a plug-in has finished working with a drawable, before exiting  * it should call gimp_drawable_detach() to make sure that all tile data is  * transferred back to the core.  *  * Return value: a new #GimpDrawable wrapper  **/
end_comment

begin_function
name|GimpDrawable
modifier|*
DECL|function|gimp_drawable_get (gint32 drawable_ID)
name|gimp_drawable_get
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
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
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
operator|&&
name|height
operator|>
literal|0
operator|&&
name|bpp
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|g_slice_new0
argument_list|(
name|GimpDrawable
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|drawable_id
operator|=
name|drawable_ID
expr_stmt|;
name|drawable
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|drawable
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|drawable
operator|->
name|bpp
operator|=
name|bpp
expr_stmt|;
name|drawable
operator|->
name|ntile_rows
operator|=
operator|(
name|height
operator|+
name|TILE_HEIGHT
operator|-
literal|1
operator|)
operator|/
name|TILE_HEIGHT
expr_stmt|;
name|drawable
operator|->
name|ntile_cols
operator|=
operator|(
name|width
operator|+
name|TILE_WIDTH
operator|-
literal|1
operator|)
operator|/
name|TILE_WIDTH
expr_stmt|;
return|return
name|drawable
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_detach:  * @drawable: The #GimpDrawable to detach from the core  *  * This function is called when a plug-in is finished working  * with a drawable.  It forces all tile data held in the tile  * list of the #GimpDrawable to be transferred to the core, and  * then frees all associated memory. You must not access the  * @drawable after having called gimp_drawable_detach().  **/
end_comment

begin_function
name|void
DECL|function|gimp_drawable_detach (GimpDrawable * drawable)
name|gimp_drawable_detach
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|drawable
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|tiles
condition|)
name|g_free
argument_list|(
name|drawable
operator|->
name|tiles
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|shadow_tiles
condition|)
name|g_free
argument_list|(
name|drawable
operator|->
name|shadow_tiles
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpDrawable
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_flush:  * @drawable: The #GimpDrawable whose tile data is to be transferred  * to the core.  *  * This function causes all tile data in the tile list of @drawable to be  * transferred to the core.  It is usually called in situations where a  * plug-in acts on a drawable, and then needs to read the results of its  * actions.  Data transferred back from the core will not generally be valid  * unless gimp_drawable_flush() has been called beforehand.  **/
end_comment

begin_function
name|void
DECL|function|gimp_drawable_flush (GimpDrawable * drawable)
name|gimp_drawable_flush
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpTile
modifier|*
name|tiles
decl_stmt|;
name|gint
name|n_tiles
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|drawable
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|tiles
condition|)
block|{
name|tiles
operator|=
name|drawable
operator|->
name|tiles
expr_stmt|;
name|n_tiles
operator|=
name|drawable
operator|->
name|ntile_rows
operator|*
name|drawable
operator|->
name|ntile_cols
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_tiles
condition|;
name|i
operator|++
control|)
if|if
condition|(
operator|(
name|tiles
index|[
name|i
index|]
operator|.
name|ref_count
operator|>
literal|0
operator|)
operator|&&
name|tiles
index|[
name|i
index|]
operator|.
name|dirty
condition|)
name|gimp_tile_flush
argument_list|(
operator|&
name|tiles
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|drawable
operator|->
name|shadow_tiles
condition|)
block|{
name|tiles
operator|=
name|drawable
operator|->
name|shadow_tiles
expr_stmt|;
name|n_tiles
operator|=
name|drawable
operator|->
name|ntile_rows
operator|*
name|drawable
operator|->
name|ntile_cols
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_tiles
condition|;
name|i
operator|++
control|)
if|if
condition|(
operator|(
name|tiles
index|[
name|i
index|]
operator|.
name|ref_count
operator|>
literal|0
operator|)
operator|&&
name|tiles
index|[
name|i
index|]
operator|.
name|dirty
condition|)
name|gimp_tile_flush
argument_list|(
operator|&
name|tiles
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
comment|/*  nuke all references to this drawable from the cache  */
name|_gimp_tile_cache_flush_drawable
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpTile
modifier|*
DECL|function|gimp_drawable_get_tile (GimpDrawable * drawable,gboolean shadow,gint row,gint col)
name|gimp_drawable_get_tile
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|shadow
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|col
parameter_list|)
block|{
name|GimpTile
modifier|*
name|tiles
decl_stmt|;
name|guint
name|right_tile
decl_stmt|;
name|guint
name|bottom_tile
decl_stmt|;
name|gint
name|n_tiles
decl_stmt|;
name|gint
name|tile_num
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|drawable
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|shadow
condition|)
name|tiles
operator|=
name|drawable
operator|->
name|shadow_tiles
expr_stmt|;
else|else
name|tiles
operator|=
name|drawable
operator|->
name|tiles
expr_stmt|;
if|if
condition|(
operator|!
name|tiles
condition|)
block|{
name|n_tiles
operator|=
name|drawable
operator|->
name|ntile_rows
operator|*
name|drawable
operator|->
name|ntile_cols
expr_stmt|;
name|tiles
operator|=
name|g_new
argument_list|(
name|GimpTile
argument_list|,
name|n_tiles
argument_list|)
expr_stmt|;
name|right_tile
operator|=
operator|(
name|drawable
operator|->
name|width
operator|-
operator|(
operator|(
name|drawable
operator|->
name|ntile_cols
operator|-
literal|1
operator|)
operator|*
name|TILE_WIDTH
operator|)
operator|)
expr_stmt|;
name|bottom_tile
operator|=
operator|(
name|drawable
operator|->
name|height
operator|-
operator|(
operator|(
name|drawable
operator|->
name|ntile_rows
operator|-
literal|1
operator|)
operator|*
name|TILE_HEIGHT
operator|)
operator|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|k
operator|=
literal|0
init|;
name|i
operator|<
name|drawable
operator|->
name|ntile_rows
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|drawable
operator|->
name|ntile_cols
condition|;
name|j
operator|++
operator|,
name|k
operator|++
control|)
block|{
name|tiles
index|[
name|k
index|]
operator|.
name|bpp
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|tiles
index|[
name|k
index|]
operator|.
name|tile_num
operator|=
name|k
expr_stmt|;
name|tiles
index|[
name|k
index|]
operator|.
name|ref_count
operator|=
literal|0
expr_stmt|;
name|tiles
index|[
name|k
index|]
operator|.
name|dirty
operator|=
name|FALSE
expr_stmt|;
name|tiles
index|[
name|k
index|]
operator|.
name|shadow
operator|=
name|shadow
expr_stmt|;
name|tiles
index|[
name|k
index|]
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
name|tiles
index|[
name|k
index|]
operator|.
name|drawable
operator|=
name|drawable
expr_stmt|;
if|if
condition|(
name|j
operator|==
operator|(
name|drawable
operator|->
name|ntile_cols
operator|-
literal|1
operator|)
condition|)
name|tiles
index|[
name|k
index|]
operator|.
name|ewidth
operator|=
name|right_tile
expr_stmt|;
else|else
name|tiles
index|[
name|k
index|]
operator|.
name|ewidth
operator|=
name|TILE_WIDTH
expr_stmt|;
if|if
condition|(
name|i
operator|==
operator|(
name|drawable
operator|->
name|ntile_rows
operator|-
literal|1
operator|)
condition|)
name|tiles
index|[
name|k
index|]
operator|.
name|eheight
operator|=
name|bottom_tile
expr_stmt|;
else|else
name|tiles
index|[
name|k
index|]
operator|.
name|eheight
operator|=
name|TILE_HEIGHT
expr_stmt|;
block|}
block|}
if|if
condition|(
name|shadow
condition|)
name|drawable
operator|->
name|shadow_tiles
operator|=
name|tiles
expr_stmt|;
else|else
name|drawable
operator|->
name|tiles
operator|=
name|tiles
expr_stmt|;
block|}
name|tile_num
operator|=
name|row
operator|*
name|drawable
operator|->
name|ntile_cols
operator|+
name|col
expr_stmt|;
return|return
operator|&
name|tiles
index|[
name|tile_num
index|]
return|;
block|}
end_function

begin_function
name|GimpTile
modifier|*
DECL|function|gimp_drawable_get_tile2 (GimpDrawable * drawable,gboolean shadow,gint x,gint y)
name|gimp_drawable_get_tile2
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|shadow
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|gint
name|row
decl_stmt|;
name|gint
name|col
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|drawable
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|col
operator|=
name|x
operator|/
name|TILE_WIDTH
expr_stmt|;
name|row
operator|=
name|y
operator|/
name|TILE_HEIGHT
expr_stmt|;
return|return
name|gimp_drawable_get_tile
argument_list|(
name|drawable
argument_list|,
name|shadow
argument_list|,
name|row
argument_list|,
name|col
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_get_color_uchar (gint32 drawable_ID,const GimpRGB * color,guchar * color_uchar)
name|gimp_drawable_get_color_uchar
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|guchar
modifier|*
name|color_uchar
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color_uchar
operator|!=
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable_ID
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB_IMAGE
case|:
name|gimp_rgb_get_uchar
argument_list|(
name|color
argument_list|,
operator|&
name|color_uchar
index|[
literal|0
index|]
argument_list|,
operator|&
name|color_uchar
index|[
literal|1
index|]
argument_list|,
operator|&
name|color_uchar
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|color_uchar
index|[
literal|3
index|]
operator|=
literal|255
expr_stmt|;
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
name|gimp_rgba_get_uchar
argument_list|(
name|color
argument_list|,
operator|&
name|color_uchar
index|[
literal|0
index|]
argument_list|,
operator|&
name|color_uchar
index|[
literal|1
index|]
argument_list|,
operator|&
name|color_uchar
index|[
literal|2
index|]
argument_list|,
operator|&
name|color_uchar
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY_IMAGE
case|:
name|color_uchar
index|[
literal|0
index|]
operator|=
name|gimp_rgb_luminance_uchar
argument_list|(
name|color
argument_list|)
expr_stmt|;
name|color_uchar
index|[
literal|1
index|]
operator|=
literal|255
expr_stmt|;
break|break;
case|case
name|GIMP_GRAYA_IMAGE
case|:
name|color_uchar
index|[
literal|0
index|]
operator|=
name|gimp_rgb_luminance_uchar
argument_list|(
name|color
argument_list|)
expr_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
name|color
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|color_uchar
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

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
comment|/**  * gimp_drawable_is_valid:  * @drawable_ID: The drawable to check.  *  * Deprecated: Use gimp_item_is_valid() instead.  *  * Returns: Whether the drawable ID is valid.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_is_valid (gint32 drawable_ID)
name|gimp_drawable_is_valid
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
return|return
name|gimp_item_is_valid
argument_list|(
name|drawable_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_is_layer:  * @drawable_ID: The drawable.  *  * Deprecated: Use gimp_item_is_layer() instead.  *  * Returns: TRUE if the drawable is a layer, FALSE otherwise.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_is_layer (gint32 drawable_ID)
name|gimp_drawable_is_layer
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
return|return
name|gimp_item_is_layer
argument_list|(
name|drawable_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_is_text_layer:  * @drawable_ID: The drawable.  *  * Deprecated: Use gimp_item_is_text_layer() instead.  *  * Returns: TRUE if the drawable is a text layer, FALSE otherwise.  *  * Since: GIMP 2.6  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_is_text_layer (gint32 drawable_ID)
name|gimp_drawable_is_text_layer
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
return|return
name|gimp_item_is_text_layer
argument_list|(
name|drawable_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_is_layer_mask:  * @drawable_ID: The drawable.  *  * Deprecated: Use gimp_item_is_layer_mask() instead.  *  * Returns: TRUE if the drawable is a layer mask, FALSE otherwise.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_is_layer_mask (gint32 drawable_ID)
name|gimp_drawable_is_layer_mask
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
return|return
name|gimp_item_is_layer_mask
argument_list|(
name|drawable_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_is_channel:  * @drawable_ID: The drawable.  *  * Deprecated: Use gimp_item_is_channel() instead.  *  * Returns: TRUE if the drawable is a channel, FALSE otherwise.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_is_channel (gint32 drawable_ID)
name|gimp_drawable_is_channel
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
return|return
name|gimp_item_is_channel
argument_list|(
name|drawable_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_delete:  * @drawable_ID: The drawable to delete.  *  * Deprecated: Use gimp_item_delete() instead.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_delete (gint32 drawable_ID)
name|gimp_drawable_delete
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
return|return
name|gimp_item_delete
argument_list|(
name|drawable_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_image:  * @drawable_ID: The drawable.  *  * Deprecated: Use gimp_item_get_image() instead.  *  * Returns: The drawable's image.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_drawable_get_image (gint32 drawable_ID)
name|gimp_drawable_get_image
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
return|return
name|gimp_item_get_image
argument_list|(
name|drawable_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_name:  * @drawable_ID: The drawable.  *  * Deprecated: Use gimp_item_get_name() instead.  *  * Returns: The drawable name.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_drawable_get_name (gint32 drawable_ID)
name|gimp_drawable_get_name
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
return|return
name|gimp_item_get_name
argument_list|(
name|drawable_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_set_name:  * @drawable_ID: The drawable.  * @name: The new drawable name.  *  * Deprecated: Use gimp_item_set_name() instead.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_set_name (gint32 drawable_ID,const gchar * name)
name|gimp_drawable_set_name
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|gimp_item_set_name
argument_list|(
name|drawable_ID
argument_list|,
name|name
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_visible:  * @drawable_ID: The drawable.  *  * Deprecated: Use gimp_item_get_visible() instead.  *  * Returns: The drawable visibility.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_get_visible (gint32 drawable_ID)
name|gimp_drawable_get_visible
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
return|return
name|gimp_item_get_visible
argument_list|(
name|drawable_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_set_visible:  * @drawable_ID: The drawable.  * @visible: The new drawable visibility.  *  * Deprecated: Use gimp_item_set_visible() instead.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_set_visible (gint32 drawable_ID,gboolean visible)
name|gimp_drawable_set_visible
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|visible
parameter_list|)
block|{
return|return
name|gimp_item_set_visible
argument_list|(
name|drawable_ID
argument_list|,
name|visible
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_linked:  * @drawable_ID: The drawable.  *  * Deprecated: Use gimp_item_get_linked() instead.  *  * Returns: The drawable linked state (for moves).  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_get_linked (gint32 drawable_ID)
name|gimp_drawable_get_linked
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
return|return
name|gimp_item_get_linked
argument_list|(
name|drawable_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_set_linked:  * @drawable_ID: The drawable.  * @linked: The new drawable linked state.  *  * Deprecated: Use gimp_item_set_linked() instead.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_set_linked (gint32 drawable_ID,gboolean linked)
name|gimp_drawable_set_linked
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|linked
parameter_list|)
block|{
return|return
name|gimp_item_set_linked
argument_list|(
name|drawable_ID
argument_list|,
name|linked
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_get_tattoo:  * @drawable_ID: The drawable.  *  * Deprecated: Use gimp_item_get_tattoo() instead.  *  * Returns: The drawable tattoo.  */
end_comment

begin_function
name|gint
DECL|function|gimp_drawable_get_tattoo (gint32 drawable_ID)
name|gimp_drawable_get_tattoo
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
return|return
name|gimp_item_get_tattoo
argument_list|(
name|drawable_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_set_tattoo:  * @drawable_ID: The drawable.  * @tattoo: The new drawable tattoo.  *  * Deprecated: Use gimp_item_set_tattoo() instead.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_set_tattoo (gint32 drawable_ID,gint tattoo)
name|gimp_drawable_set_tattoo
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|tattoo
parameter_list|)
block|{
return|return
name|gimp_item_set_tattoo
argument_list|(
name|drawable_ID
argument_list|,
name|tattoo
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_parasite_find:  * @drawable_ID: The drawable.  * @name: The name of the parasite to find.  *  * Deprecated: Use gimp_item_find_parasite() instead.  *  * Returns: The found parasite.  **/
end_comment

begin_function
name|GimpParasite
modifier|*
DECL|function|gimp_drawable_parasite_find (gint32 drawable_ID,const gchar * name)
name|gimp_drawable_parasite_find
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|gimp_item_find_parasite
argument_list|(
name|drawable_ID
argument_list|,
name|name
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_parasite_attach:  * @drawable_ID: The drawable.  * @parasite: The parasite to attach to a drawable.  *  * Deprecated: Use gimp_item_attach_parasite() instead.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_parasite_attach (gint32 drawable_ID,const GimpParasite * parasite)
name|gimp_drawable_parasite_attach
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
return|return
name|gimp_item_attach_parasite
argument_list|(
name|drawable_ID
argument_list|,
name|parasite
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_parasite_detach:  * @drawable_ID: The drawable.  * @name: The name of the parasite to detach from a drawable.  *  * Deprecated: Use gimp_item_detach_parasite() instead.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_parasite_detach (gint32 drawable_ID,const gchar * name)
name|gimp_drawable_parasite_detach
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|gimp_item_detach_parasite
argument_list|(
name|drawable_ID
argument_list|,
name|name
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_parasite_list:  * @drawable_ID: The drawable.  * @num_parasites: The number of attached parasites.  * @parasites: The names of currently attached parasites.  *  * Deprecated: Use gimp_item_list_parasites() instead.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_parasite_list (gint32 drawable_ID,gint * num_parasites,gchar *** parasites)
name|gimp_drawable_parasite_list
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
modifier|*
name|num_parasites
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|parasites
parameter_list|)
block|{
return|return
name|gimp_item_list_parasites
argument_list|(
name|drawable_ID
argument_list|,
name|num_parasites
argument_list|,
name|parasites
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_attach_new_parasite:  * @drawable_ID: the ID of the #GimpDrawable to attach the #GimpParasite to.  * @name: the name of the #GimpParasite to create and attach.  * @flags: the flags set on the #GimpParasite.  * @size: the size of the parasite data in bytes.  * @data: a pointer to the data attached with the #GimpParasite.  *  * Convenience function that creates a parasite and attaches it  * to GIMP.  *  * Deprecated: use gimp_image_parasite_attach() instead.  *  * Return value: TRUE on successful creation and attachment of  * the new parasite.  *  * See Also: gimp_drawable_parasite_attach()  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_drawable_attach_new_parasite (gint32 drawable_ID,const gchar * name,gint flags,gint size,gconstpointer data)
name|gimp_drawable_attach_new_parasite
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|flags
parameter_list|,
name|gint
name|size
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|GimpParasite
modifier|*
name|parasite
init|=
name|gimp_parasite_new
argument_list|(
name|name
argument_list|,
name|flags
argument_list|,
name|size
argument_list|,
name|data
argument_list|)
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|success
operator|=
name|gimp_item_attach_parasite
argument_list|(
name|drawable_ID
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

