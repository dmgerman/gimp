begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

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
name|GDrawable
modifier|*
DECL|function|gimp_drawable_get (gint32 drawable_ID)
name|gimp_drawable_get
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|drawable
operator|=
name|g_new
argument_list|(
name|GDrawable
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|id
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
DECL|function|gimp_drawable_detach (GDrawable * drawable)
name|gimp_drawable_detach
parameter_list|(
name|GDrawable
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
DECL|function|gimp_drawable_flush (GDrawable * drawable)
name|gimp_drawable_flush
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GTile
modifier|*
name|tiles
decl_stmt|;
name|int
name|ntiles
decl_stmt|;
name|int
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
DECL|function|gimp_drawable_delete (GDrawable * drawable)
name|gimp_drawable_delete
parameter_list|(
name|GDrawable
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
name|gimp_drawable_layer
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
condition|)
name|gimp_layer_delete
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
else|else
name|gimp_channel_delete
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_update (gint32 drawable_ID,gint x,gint y,guint width,guint height)
name|gimp_drawable_update
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|width
parameter_list|,
name|guint
name|height
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_update"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_INT32
argument_list|,
name|x
argument_list|,
name|PARAM_INT32
argument_list|,
name|y
argument_list|,
name|PARAM_INT32
argument_list|,
name|width
argument_list|,
name|PARAM_INT32
argument_list|,
name|height
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_merge_shadow (gint32 drawable_ID,gint undoable)
name|gimp_drawable_merge_shadow
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|undoable
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_merge_shadow"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_INT32
argument_list|,
name|undoable
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint32
DECL|function|gimp_drawable_image_id (gint32 drawable_ID)
name|gimp_drawable_image_id
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_image"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|image_ID
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
operator|==
name|STATUS_SUCCESS
condition|)
name|image_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

begin_function
name|char
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
name|gimp_drawable_layer
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
name|guint
DECL|function|gimp_drawable_width (gint32 drawable_ID)
name|gimp_drawable_width
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|guint
name|width
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_width"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|width
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
operator|==
name|STATUS_SUCCESS
condition|)
name|width
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|width
return|;
block|}
end_function

begin_function
name|guint
DECL|function|gimp_drawable_height (gint32 drawable_ID)
name|gimp_drawable_height
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|guint
name|height
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_height"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|height
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
operator|==
name|STATUS_SUCCESS
condition|)
name|height
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|height
return|;
block|}
end_function

begin_function
name|guint
DECL|function|gimp_drawable_bpp (gint32 drawable_ID)
name|gimp_drawable_bpp
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|guint
name|bpp
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_bytes"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|bpp
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
operator|==
name|STATUS_SUCCESS
condition|)
name|bpp
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|bpp
return|;
block|}
end_function

begin_function
name|GDrawableType
DECL|function|gimp_drawable_type (gint32 drawable_ID)
name|gimp_drawable_type
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|int
name|result
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_type"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|result
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
operator|==
name|STATUS_SUCCESS
condition|)
name|result
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_drawable_visible (gint32 drawable_ID)
name|gimp_drawable_visible
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
if|if
condition|(
name|gimp_drawable_layer
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
name|gint
DECL|function|gimp_drawable_channel (gint32 drawable_ID)
name|gimp_drawable_channel
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|int
name|result
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_channel"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|result
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|result
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_drawable_color (gint32 drawable_ID)
name|gimp_drawable_color
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|int
name|result
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_color"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|result
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|result
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_drawable_gray (gint32 drawable_ID)
name|gimp_drawable_gray
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|int
name|result
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_gray"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|result
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|result
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_drawable_has_alpha (gint32 drawable_ID)
name|gimp_drawable_has_alpha
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|int
name|result
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_has_alpha"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|result
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|result
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_drawable_indexed (gint32 drawable_ID)
name|gimp_drawable_indexed
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|int
name|result
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_indexed"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|result
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|result
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_drawable_layer (gint32 drawable_ID)
name|gimp_drawable_layer
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|int
name|result
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_layer"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|result
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|result
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_drawable_layer_mask (gint32 drawable_ID)
name|gimp_drawable_layer_mask
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|int
name|result
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_layer_mask"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|result
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|result
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_drawable_mask_bounds (gint32 drawable_ID,gint * x1,gint * y1,gint * x2,gint * y2)
name|gimp_drawable_mask_bounds
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|int
name|result
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_mask_bounds"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|result
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
name|result
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|x1
operator|=
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|y1
operator|=
name|return_vals
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|x2
operator|=
name|return_vals
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|y2
operator|=
name|return_vals
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
block|}
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_offsets (gint32 drawable_ID,gint * offset_x,gint * offset_y)
name|gimp_drawable_offsets
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
modifier|*
name|offset_x
parameter_list|,
name|gint
modifier|*
name|offset_y
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_offsets"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
operator|*
name|offset_x
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|offset_y
operator|=
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
block|}
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_fill (gint32 drawable_ID,gint fill_type)
name|gimp_drawable_fill
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|fill_type
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_fill"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_INT32
argument_list|,
name|fill_type
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_set_name (gint32 drawable_ID,char * name)
name|gimp_drawable_set_name
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|char
modifier|*
name|name
parameter_list|)
block|{
if|if
condition|(
name|gimp_drawable_layer
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
DECL|function|gimp_drawable_set_visible (gint32 drawable_ID,gint visible)
name|gimp_drawable_set_visible
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|visible
parameter_list|)
block|{
if|if
condition|(
name|gimp_drawable_layer
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
name|GTile
modifier|*
DECL|function|gimp_drawable_get_tile (GDrawable * drawable,gint shadow,gint row,gint col)
name|gimp_drawable_get_tile
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|shadow
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|col
parameter_list|)
block|{
name|GTile
modifier|*
name|tiles
decl_stmt|;
name|guint
name|right_tile
decl_stmt|;
name|guint
name|bottom_tile
decl_stmt|;
name|int
name|ntiles
decl_stmt|;
name|int
name|tile_num
decl_stmt|;
name|int
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
name|GTile
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
name|GTile
modifier|*
DECL|function|gimp_drawable_get_tile2 (GDrawable * drawable,gint shadow,gint x,gint y)
name|gimp_drawable_get_tile2
parameter_list|(
name|GDrawable
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
decl_stmt|,
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
name|Parasite
modifier|*
DECL|function|gimp_drawable_find_parasite (gint32 drawable_ID,const char * name)
name|gimp_drawable_find_parasite
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|char
modifier|*
name|name
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|Parasite
modifier|*
name|parasite
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_find_parasite"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_STRING
argument_list|,
name|name
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
name|parasite
operator|=
name|parasite_copy
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_parasite
argument_list|)
expr_stmt|;
block|}
else|else
name|parasite
operator|=
name|NULL
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|parasite
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_attach_parasite (gint32 drawable_ID,const Parasite * p)
name|gimp_drawable_attach_parasite
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|Parasite
modifier|*
name|p
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_attach_parasite"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_PARASITE
argument_list|,
name|p
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_attach_new_parasite (gint32 drawable,const char * name,int flags,int size,const void * data)
name|gimp_drawable_attach_new_parasite
parameter_list|(
name|gint32
name|drawable
parameter_list|,
specifier|const
name|char
modifier|*
name|name
parameter_list|,
name|int
name|flags
parameter_list|,
name|int
name|size
parameter_list|,
specifier|const
name|void
modifier|*
name|data
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|Parasite
modifier|*
name|p
init|=
name|parasite_new
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
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_attach_parasite"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable
argument_list|,
name|PARAM_PARASITE
argument_list|,
name|p
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|parasite_free
argument_list|(
name|p
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_detach_parasite (gint32 drawable_ID,const char * name)
name|gimp_drawable_detach_parasite
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|char
modifier|*
name|name
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_detach_parasite"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_STRING
argument_list|,
name|name
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|guchar
modifier|*
DECL|function|gimp_drawable_get_thumbnail_data (gint32 drawable_ID,gint * width,gint * height,gint * bytes)
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
name|bytes
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|drawable_data
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_drawable_thumbnail"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_INT32
argument_list|,
operator|*
name|width
argument_list|,
name|PARAM_INT32
argument_list|,
operator|*
name|height
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
operator|*
name|width
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|height
operator|=
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|bytes
operator|=
name|return_vals
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|drawable_data
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|return_vals
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
name|g_memmove
argument_list|(
name|drawable_data
argument_list|,
name|return_vals
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32array
argument_list|,
name|return_vals
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
block|}
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|drawable_data
return|;
block|}
end_function

end_unit

