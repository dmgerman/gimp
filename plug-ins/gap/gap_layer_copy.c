begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_layer_copy.c  *    by hof (Wolfgang Hofer)  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * version 0.99.00 1999.03.03   hof: use the regular gimp_layer_copy and gimp_channel_copy  *                                   (removed private variant)  * version 0.98.00 1998.11.26   hof: added channel copy  * version         1998.11.26   hof: bugfix have to copy the layer's layer_mask too.  *                                          type check of destination image  * version 0.96.00              hof: bugfix memory leak (must set src_tile to unref after use)   * version 0.93.01              hof: when creating the destination layer  *                                   add alpha channel if needed in extra call   * version 0.90.00;             hof: 1.st (pre) release  */
end_comment

begin_comment
comment|/* SYTEM (UNIX) includes */
end_comment

begin_comment
comment|/* GIMP includes */
end_comment

begin_comment
comment|/* GAP includes */
end_comment

begin_include
include|#
directive|include
file|"gap_layer_copy.h"
end_include

begin_include
include|#
directive|include
file|"gap_pdb_calls.h"
end_include

begin_decl_stmt
specifier|extern
name|int
name|gap_debug
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* ==0  ... dont print debug infos */
end_comment

begin_comment
comment|/* ============================================================================  * p_my_layer_copy  *    copy src_layer to the dst_image,  *    return the id of the new created layer (the copy)  * NOTE: source layer MUST have same type (bpp) for now  *       it would be fine to extend the code to convert between any type  * ============================================================================  */
end_comment

begin_function
DECL|function|p_my_layer_copy (gint32 dst_image_id,gint32 src_layer_id,gdouble opacity,GimpLayerModeEffects mode,gint * src_offset_x,gint * src_offset_y)
name|gint32
name|p_my_layer_copy
parameter_list|(
name|gint32
name|dst_image_id
parameter_list|,
name|gint32
name|src_layer_id
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
comment|/* 0.0 upto 100.0 */
name|GimpLayerModeEffects
name|mode
parameter_list|,
name|gint
modifier|*
name|src_offset_x
parameter_list|,
name|gint
modifier|*
name|src_offset_y
parameter_list|)
block|{
name|gint32
name|l_new_layer_id
decl_stmt|;
name|gint32
name|l_ret_id
decl_stmt|;
name|char
modifier|*
name|l_name
decl_stmt|;
name|GimpImageType
name|l_src_type
decl_stmt|;
if|if
condition|(
name|gap_debug
condition|)
name|printf
argument_list|(
literal|"GAP p_my_layer_copy: START\n"
argument_list|)
expr_stmt|;
name|l_ret_id
operator|=
operator|-
literal|1
expr_stmt|;
comment|/* prepare error retcode -1 */
name|l_name
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|opacity
operator|>
literal|99.99
condition|)
name|opacity
operator|=
literal|100.0
expr_stmt|;
if|if
condition|(
name|opacity
operator|<
literal|0.0
condition|)
name|opacity
operator|=
literal|0.0
expr_stmt|;
name|l_name
operator|=
name|gimp_layer_get_name
argument_list|(
name|src_layer_id
argument_list|)
expr_stmt|;
name|l_src_type
operator|=
name|gimp_drawable_type
argument_list|(
name|src_layer_id
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|l_src_type
condition|)
block|{
case|case
name|GIMP_RGB_IMAGE
case|:
comment|/* 0 */
case|case
name|GIMP_RGBA_IMAGE
case|:
comment|/* 1 */
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|dst_image_id
argument_list|)
operator|!=
name|GIMP_RGB
condition|)
block|{
return|return
operator|-
literal|1
return|;
block|}
break|break;
case|case
name|GIMP_GRAY_IMAGE
case|:
comment|/* 2 */
case|case
name|GIMP_GRAYA_IMAGE
case|:
comment|/* 3 */
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|dst_image_id
argument_list|)
operator|!=
name|GIMP_GRAY
condition|)
block|{
return|return
operator|-
literal|1
return|;
block|}
break|break;
case|case
name|GIMP_INDEXED_IMAGE
case|:
comment|/* 4 */
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
comment|/* 5 */
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|dst_image_id
argument_list|)
operator|!=
name|GIMP_INDEXED
condition|)
block|{
return|return
operator|-
literal|1
return|;
block|}
break|break;
block|}
comment|/* copy the layer */
name|l_new_layer_id
operator|=
name|gimp_layer_copy
argument_list|(
name|src_layer_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_new_layer_id
operator|>=
literal|0
condition|)
block|{
if|if
condition|(
name|p_gimp_drawable_set_image
argument_list|(
name|l_new_layer_id
argument_list|,
name|dst_image_id
argument_list|)
operator|>=
literal|0
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|l_new_layer_id
argument_list|)
condition|)
block|{
comment|/* have to add alpha channel */
name|gimp_layer_add_alpha
argument_list|(
name|l_new_layer_id
argument_list|)
expr_stmt|;
block|}
comment|/* findout the offsets of the original layer within the source Image */
name|gimp_drawable_offsets
argument_list|(
name|src_layer_id
argument_list|,
name|src_offset_x
argument_list|,
name|src_offset_y
argument_list|)
expr_stmt|;
name|gimp_layer_set_name
argument_list|(
name|l_new_layer_id
argument_list|,
name|l_name
argument_list|)
expr_stmt|;
name|gimp_layer_set_opacity
argument_list|(
name|l_new_layer_id
argument_list|,
name|opacity
argument_list|)
expr_stmt|;
name|gimp_layer_set_mode
argument_list|(
name|l_new_layer_id
argument_list|,
name|mode
argument_list|)
expr_stmt|;
name|l_ret_id
operator|=
name|l_new_layer_id
expr_stmt|;
comment|/* all done OK */
block|}
block|}
if|if
condition|(
name|l_name
operator|!=
name|NULL
condition|)
block|{
name|g_free
argument_list|(
name|l_name
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gap_debug
condition|)
name|printf
argument_list|(
literal|"GAP p_my_layer_copy: ret %d\n"
argument_list|,
operator|(
name|int
operator|)
name|l_ret_id
argument_list|)
expr_stmt|;
return|return
name|l_ret_id
return|;
block|}
end_function

begin_comment
comment|/* end p_my_layer_copy */
end_comment

begin_comment
comment|/* ============================================================================  * p_my_channel_copy  *   copy a channel to dst_IMAGE  * ============================================================================  */
end_comment

begin_function
DECL|function|p_my_channel_copy (gint32 dst_image_id,gint32 src_channel_id)
name|gint32
name|p_my_channel_copy
parameter_list|(
name|gint32
name|dst_image_id
parameter_list|,
name|gint32
name|src_channel_id
parameter_list|)
block|{
name|gint32
name|l_new_channel_id
decl_stmt|;
name|gint32
name|l_ret_id
decl_stmt|;
name|char
modifier|*
name|l_name
decl_stmt|;
if|if
condition|(
name|gap_debug
condition|)
name|printf
argument_list|(
literal|"GAP :p_my_channel_copy START\n"
argument_list|)
expr_stmt|;
name|l_ret_id
operator|=
operator|-
literal|1
expr_stmt|;
comment|/* prepare error retcode -1 */
name|l_name
operator|=
name|NULL
expr_stmt|;
comment|/* create new channel in destination image */
name|l_name
operator|=
name|gimp_channel_get_name
argument_list|(
name|src_channel_id
argument_list|)
expr_stmt|;
comment|/* copy the channel */
name|l_new_channel_id
operator|=
name|gimp_channel_copy
argument_list|(
name|src_channel_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_new_channel_id
operator|>=
literal|0
condition|)
block|{
if|if
condition|(
name|p_gimp_drawable_set_image
argument_list|(
name|l_new_channel_id
argument_list|,
name|dst_image_id
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|gimp_channel_set_name
argument_list|(
name|l_new_channel_id
argument_list|,
name|l_name
argument_list|)
expr_stmt|;
name|l_ret_id
operator|=
name|l_new_channel_id
expr_stmt|;
comment|/* all done OK */
block|}
block|}
if|if
condition|(
name|l_name
operator|!=
name|NULL
condition|)
block|{
name|g_free
argument_list|(
name|l_name
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gap_debug
condition|)
name|printf
argument_list|(
literal|"GAP :p_my_channel_copy id=%d\n"
argument_list|,
operator|(
name|int
operator|)
name|l_ret_id
argument_list|)
expr_stmt|;
return|return
name|l_ret_id
return|;
block|}
end_function

begin_comment
comment|/* end p_my_channel_copy */
end_comment

end_unit

