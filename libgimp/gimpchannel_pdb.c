begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpchannel_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
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

begin_comment
comment|/**  * SECTION: gimpchannel  * @title: gimpchannel  * @short_description: Functions for manipulating channels.  *  * Functions for manipulating channels.  **/
end_comment

begin_comment
comment|/**  * _gimp_channel_new:  * @image_ID: The image to which to add the channel.  * @width: The channel width.  * @height: The channel height.  * @name: The channel name.  * @opacity: The channel opacity.  * @color: The channel compositing color.  *  * Create a new channel.  *  * This procedure creates a new channel with the specified width,  * height, name, opacity and color.  * The new channel still needs to be added to the image, as this is not  * automatic. Add the new channel with gimp_image_insert_channel().  * Other attributes, such as channel visibility, should be set with  * explicit procedure calls.  * The channel's contents are undefined initially.  *  * Returns: The newly created channel.  **/
end_comment

begin_function
name|gint32
DECL|function|_gimp_channel_new (gint32 image_ID,gint width,gint height,const gchar * name,gdouble opacity,const GimpRGB * color)
name|_gimp_channel_new
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
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint32
name|channel_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|GIMP_TYPE_RGB
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|4
argument_list|)
argument_list|,
name|opacity
argument_list|)
expr_stmt|;
name|gimp_value_set_rgb
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|5
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-channel-new"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|channel_ID
operator|=
name|gimp_value_get_channel_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|channel_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_channel_new_from_component:  * @image_ID: The image to which to add the channel.  * @component: The image component.  * @name: The channel name.  *  * Create a new channel from a color component  *  * This procedure creates a new channel from a color component.  * The new channel still needs to be added to the image, as this is not  * automatic. Add the new channel with gimp_image_insert_channel().  * Other attributes, such as channel visibility, should be set with  * explicit procedure calls.  *  * Returns: The newly created channel.  *  * Since: 2.4  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_channel_new_from_component (gint32 image_ID,GimpChannelType component,const gchar * name)
name|gimp_channel_new_from_component
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpChannelType
name|component
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint32
name|channel_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|GIMP_TYPE_CHANNEL_TYPE
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|component
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-channel-new-from-component"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|channel_ID
operator|=
name|gimp_value_get_channel_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|channel_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_channel_copy:  * @channel_ID: The channel to copy.  *  * Copy a channel.  *  * This procedure copies the specified channel and returns the copy.  * The new channel still needs to be added to the image, as this is not  * automatic. Add the new channel with gimp_image_insert_channel().  *  * Returns: The newly copied channel.  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_channel_copy (gint32 channel_ID)
name|gimp_channel_copy
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint32
name|channel_copy_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_CHANNEL_ID
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_channel_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|channel_ID
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-channel-copy"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|channel_copy_ID
operator|=
name|gimp_value_get_channel_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|channel_copy_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_channel_combine_masks:  * @channel1_ID: The channel1.  * @channel2_ID: The channel2.  * @operation: The selection operation.  * @offx: x offset between upper left corner of channels: (second - first).  * @offy: y offset between upper left corner of channels: (second - first).  *  * Combine two channel masks.  *  * This procedure combines two channel masks. The result is stored in  * the first channel.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_channel_combine_masks (gint32 channel1_ID,gint32 channel2_ID,GimpChannelOps operation,gint offx,gint offy)
name|gimp_channel_combine_masks
parameter_list|(
name|gint32
name|channel1_ID
parameter_list|,
name|gint32
name|channel2_ID
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_CHANNEL_ID
argument_list|,
name|GIMP_TYPE_CHANNEL_ID
argument_list|,
name|GIMP_TYPE_CHANNEL_OPS
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_channel_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|channel1_ID
argument_list|)
expr_stmt|;
name|gimp_value_set_channel_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|channel2_ID
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|operation
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|offx
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|4
argument_list|)
argument_list|,
name|offy
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-channel-combine-masks"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_channel_get_show_masked:  * @channel_ID: The channel.  *  * Get the composite method of the specified channel.  *  * This procedure returns the specified channel's composite method. If  * it is TRUE, then the channel is composited with the image so that  * masked regions are shown. Otherwise, selected regions are shown.  *  * Returns: The channel composite method.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_channel_get_show_masked (gint32 channel_ID)
name|gimp_channel_get_show_masked
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|show_masked
init|=
name|FALSE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_CHANNEL_ID
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_channel_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|channel_ID
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-channel-get-show-masked"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|show_masked
operator|=
name|g_value_get_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|show_masked
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_channel_set_show_masked:  * @channel_ID: The channel.  * @show_masked: The new channel composite method.  *  * Set the composite method of the specified channel.  *  * This procedure sets the specified channel's composite method. If it  * is TRUE, then the channel is composited with the image so that  * masked regions are shown. Otherwise, selected regions are shown.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_channel_set_show_masked (gint32 channel_ID,gboolean show_masked)
name|gimp_channel_set_show_masked
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
name|gboolean
name|show_masked
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_CHANNEL_ID
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_channel_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|channel_ID
argument_list|)
expr_stmt|;
name|g_value_set_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|show_masked
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-channel-set-show-masked"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_channel_get_opacity:  * @channel_ID: The channel.  *  * Get the opacity of the specified channel.  *  * This procedure returns the specified channel's opacity.  *  * Returns: The channel opacity.  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_channel_get_opacity (gint32 channel_ID)
name|gimp_channel_get_opacity
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gdouble
name|opacity
init|=
literal|0.0
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_CHANNEL_ID
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_channel_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|channel_ID
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-channel-get-opacity"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|opacity
operator|=
name|g_value_get_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|opacity
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_channel_set_opacity:  * @channel_ID: The channel.  * @opacity: The new channel opacity.  *  * Set the opacity of the specified channel.  *  * This procedure sets the specified channel's opacity.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_channel_set_opacity (gint32 channel_ID,gdouble opacity)
name|gimp_channel_set_opacity
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_CHANNEL_ID
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_channel_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|channel_ID
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|opacity
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-channel-set-opacity"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_channel_get_color:  * @channel_ID: The channel.  * @color: The channel compositing color.  *  * Get the compositing color of the specified channel.  *  * This procedure returns the specified channel's compositing color.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_channel_get_color (gint32 channel_ID,GimpRGB * color)
name|gimp_channel_get_color
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_CHANNEL_ID
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_channel_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|channel_ID
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-channel-get-color"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|gimp_value_get_rgb
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
operator|&
operator|*
name|color
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_channel_set_color:  * @channel_ID: The channel.  * @color: The new channel compositing color.  *  * Set the compositing color of the specified channel.  *  * This procedure sets the specified channel's compositing color.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_channel_set_color (gint32 channel_ID,const GimpRGB * color)
name|gimp_channel_set_color
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_CHANNEL_ID
argument_list|,
name|GIMP_TYPE_RGB
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_channel_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|channel_ID
argument_list|)
expr_stmt|;
name|gimp_value_set_rgb
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-channel-set-color"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

