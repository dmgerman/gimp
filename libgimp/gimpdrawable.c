begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpdrawable.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<glib.h>
end_include

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
value|_gimp_tile_width
end_define

begin_define
DECL|macro|TILE_HEIGHT
define|#
directive|define
name|TILE_HEIGHT
value|_gimp_tile_height
end_define

begin_decl_stmt
specifier|extern
name|gint
name|_gimp_tile_width
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|_gimp_tile_height
decl_stmt|;
end_decl_stmt

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
name|drawable
operator|=
name|g_new
argument_list|(
name|GimpDrawable
argument_list|,
literal|1
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
name|gimp_drawable_width
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|bpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|ntile_rows
operator|=
operator|(
name|drawable
operator|->
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
name|drawable
operator|->
name|width
operator|+
name|TILE_WIDTH
operator|-
literal|1
operator|)
operator|/
name|TILE_WIDTH
expr_stmt|;
name|drawable
operator|->
name|tiles
operator|=
name|NULL
expr_stmt|;
name|drawable
operator|->
name|shadow_tiles
operator|=
name|NULL
expr_stmt|;
return|return
name|drawable
return|;
block|}
end_function

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
if|if
condition|(
name|drawable
condition|)
block|{
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
name|g_free
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
block|}
end_function

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
name|ntiles
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|drawable
condition|)
block|{
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
name|ntiles
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
name|ntiles
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
name|ntiles
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
name|ntiles
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
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_delete (GimpDrawable * drawable)
name|gimp_drawable_delete
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|drawable
condition|)
block|{
if|if
condition|(
name|gimp_drawable_is_layer
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
name|gimp_layer_delete
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
else|else
name|gimp_channel_delete
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_drawable_name (gint32 drawable_ID)
name|gimp_drawable_name
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
if|if
condition|(
name|gimp_drawable_is_layer
argument_list|(
name|drawable_ID
argument_list|)
condition|)
return|return
name|gimp_layer_get_name
argument_list|(
name|drawable_ID
argument_list|)
return|;
return|return
name|gimp_channel_get_name
argument_list|(
name|drawable_ID
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_drawable_visible (gint32 drawable_ID)
name|gimp_drawable_visible
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
if|if
condition|(
name|gimp_drawable_is_layer
argument_list|(
name|drawable_ID
argument_list|)
condition|)
return|return
name|gimp_layer_get_visible
argument_list|(
name|drawable_ID
argument_list|)
return|;
return|return
name|gimp_channel_get_visible
argument_list|(
name|drawable_ID
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_set_name (gint32 drawable_ID,gchar * name)
name|gimp_drawable_set_name
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
block|{
if|if
condition|(
name|gimp_drawable_is_layer
argument_list|(
name|drawable_ID
argument_list|)
condition|)
name|gimp_layer_set_name
argument_list|(
name|drawable_ID
argument_list|,
name|name
argument_list|)
expr_stmt|;
else|else
name|gimp_channel_set_name
argument_list|(
name|drawable_ID
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
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
if|if
condition|(
name|gimp_drawable_is_layer
argument_list|(
name|drawable_ID
argument_list|)
condition|)
name|gimp_layer_set_visible
argument_list|(
name|drawable_ID
argument_list|,
name|visible
argument_list|)
expr_stmt|;
else|else
name|gimp_channel_set_visible
argument_list|(
name|drawable_ID
argument_list|,
name|visible
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
name|ntiles
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
if|if
condition|(
name|drawable
condition|)
block|{
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
name|ntiles
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
name|ntiles
argument_list|)
expr_stmt|;
name|right_tile
operator|=
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
expr_stmt|;
name|bottom_tile
operator|=
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
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpTile
modifier|*
DECL|function|gimp_drawable_get_tile2 (GimpDrawable * drawable,gint shadow,gint x,gint y)
name|gimp_drawable_get_tile2
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
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
name|void
DECL|function|gimp_drawable_attach_new_parasite (gint32 drawable,const gchar * name,gint flags,gint size,const gpointer data)
name|gimp_drawable_attach_new_parasite
parameter_list|(
name|gint32
name|drawable
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
specifier|const
name|gpointer
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
name|gimp_drawable_parasite_attach
argument_list|(
name|drawable
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

