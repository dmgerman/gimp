begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpimage.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_undef
undef|#
directive|undef
name|__GIMP_IMAGE_H__
end_undef

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_comment
comment|/**  * gimp_image_get_colormap:  * @image_ID:   The image.  * @num_colors: Returns the number of colors in the colormap array.  *  * Returns the image's colormap  *  * This procedure returns an actual pointer to the image's colormap, as  * well as the number of colors contained in the colormap. If the image  * is not of base type INDEXED, this pointer will be NULL.  *  * Returns: The image's colormap.  */
end_comment

begin_function
name|guchar
modifier|*
DECL|function|gimp_image_get_colormap (gint32 image_ID,gint * num_colors)
name|gimp_image_get_colormap
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|num_colors
parameter_list|)
block|{
name|gint
name|num_bytes
decl_stmt|;
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|cmap
operator|=
name|_gimp_image_get_colormap
argument_list|(
name|image_ID
argument_list|,
operator|&
name|num_bytes
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_colors
condition|)
operator|*
name|num_colors
operator|=
name|num_bytes
operator|/
literal|3
expr_stmt|;
return|return
name|cmap
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_set_colormap:  * @image_ID:   The image.  * @colormap:   The new colormap values.  * @num_colors: Number of colors in the colormap array.  *  * Sets the entries in the image's colormap.  *  * This procedure sets the entries in the specified image's colormap.  * The number of colors is specified by the \"num_colors\" parameter  * and corresponds to the number of INT8 triples that must be contained  * in the \"cmap\" array.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_set_colormap (gint32 image_ID,const guchar * colormap,gint num_colors)
name|gimp_image_set_colormap
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|guchar
modifier|*
name|colormap
parameter_list|,
name|gint
name|num_colors
parameter_list|)
block|{
return|return
name|_gimp_image_set_colormap
argument_list|(
name|image_ID
argument_list|,
name|num_colors
operator|*
literal|3
argument_list|,
name|colormap
argument_list|)
return|;
block|}
end_function

begin_function
name|guchar
modifier|*
DECL|function|gimp_image_get_thumbnail_data (gint32 image_ID,gint * width,gint * height,gint * bpp)
name|gimp_image_get_thumbnail_data
parameter_list|(
name|gint32
name|image_ID
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
name|_gimp_image_thumbnail
argument_list|(
name|image_ID
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
comment|/**  * gimp_image_get_cmap:  * @image_ID:   The image.  * @num_colors: Number of colors in the colormap array.  *  * This procedure is deprecated! Use gimp_image_get_colormap() instead.  *  * Returns: The image's colormap.  */
end_comment

begin_function
name|guchar
modifier|*
DECL|function|gimp_image_get_cmap (gint32 image_ID,gint * num_colors)
name|gimp_image_get_cmap
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|num_colors
parameter_list|)
block|{
return|return
name|gimp_image_get_colormap
argument_list|(
name|image_ID
argument_list|,
name|num_colors
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_set_cmap:  * @image_ID:   The image.  * @cmap:       The new colormap values.  * @num_colors: Number of colors in the colormap array.  *  * This procedure is deprecated! Use gimp_image_set_colormap() instead.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_set_cmap (gint32 image_ID,const guchar * cmap,gint num_colors)
name|gimp_image_set_cmap
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|guchar
modifier|*
name|cmap
parameter_list|,
name|gint
name|num_colors
parameter_list|)
block|{
return|return
name|gimp_image_set_colormap
argument_list|(
name|image_ID
argument_list|,
name|cmap
argument_list|,
name|num_colors
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_get_layer_position:  * @image_ID: The image.  * @layer_ID: The layer.  *  * Deprecated: Use gimp_image_get_item_position() instead.  *  * Returns: The position of the layer in the layer stack.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gint
DECL|function|gimp_image_get_layer_position (gint32 image_ID,gint32 layer_ID)
name|gimp_image_get_layer_position
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
block|{
return|return
name|gimp_image_get_item_position
argument_list|(
name|image_ID
argument_list|,
name|layer_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_raise_layer:  * @image_ID: The image.  * @layer_ID: The layer to raise.  *  * Deprecated: Use gimp_image_raise_item() instead.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_raise_layer (gint32 image_ID,gint32 layer_ID)
name|gimp_image_raise_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
block|{
return|return
name|gimp_image_raise_item
argument_list|(
name|image_ID
argument_list|,
name|layer_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_lower_layer:  * @image_ID: The image.  * @layer_ID: The layer to lower.  *  * Deprecated: Use gimp_image_lower_item() instead.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_lower_layer (gint32 image_ID,gint32 layer_ID)
name|gimp_image_lower_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
block|{
return|return
name|gimp_image_lower_item
argument_list|(
name|image_ID
argument_list|,
name|layer_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_raise_layer_to_top:  * @image_ID: The image.  * @layer_ID: The layer to raise to top.  *  * Deprecated: Use gimp_image_raise_item_to_top() instead.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_raise_layer_to_top (gint32 image_ID,gint32 layer_ID)
name|gimp_image_raise_layer_to_top
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
block|{
return|return
name|gimp_image_raise_item_to_top
argument_list|(
name|image_ID
argument_list|,
name|layer_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_lower_layer_to_bottom:  * @image_ID: The image.  * @layer_ID: The layer to lower to bottom.  *  * Deprecated: Use gimp_image_lower_item_to_bottom() instead.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_lower_layer_to_bottom (gint32 image_ID,gint32 layer_ID)
name|gimp_image_lower_layer_to_bottom
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
block|{
return|return
name|gimp_image_lower_item_to_bottom
argument_list|(
name|image_ID
argument_list|,
name|layer_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_get_channel_position:  * @image_ID: The image.  * @channel_ID: The channel.  *  * Deprecated: Use gimp_image_get_item_position() instead.  *  * Returns: The position of the channel in the channel stack.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gint
DECL|function|gimp_image_get_channel_position (gint32 image_ID,gint32 channel_ID)
name|gimp_image_get_channel_position
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|channel_ID
parameter_list|)
block|{
return|return
name|gimp_image_get_item_position
argument_list|(
name|image_ID
argument_list|,
name|channel_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_raise_channel:  * @image_ID: The image.  * @channel_ID: The channel to raise.  *  * Deprecated: Use gimp_image_raise_item() instead.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_raise_channel (gint32 image_ID,gint32 channel_ID)
name|gimp_image_raise_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|channel_ID
parameter_list|)
block|{
return|return
name|gimp_image_raise_item
argument_list|(
name|image_ID
argument_list|,
name|channel_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_lower_channel:  * @image_ID: The image.  * @channel_ID: The channel to lower.  *  * Deprecated: Use gimp_image_lower_item() instead.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_lower_channel (gint32 image_ID,gint32 channel_ID)
name|gimp_image_lower_channel
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|channel_ID
parameter_list|)
block|{
return|return
name|gimp_image_lower_item
argument_list|(
name|image_ID
argument_list|,
name|channel_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_get_vectors_position:  * @image_ID: The image.  * @vectors_ID: The vectors object.  *  * Deprecated: Use gimp_image_get_item_position() instead.  *  * Returns: The position of the vectors object in the vectors stack.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gint
DECL|function|gimp_image_get_vectors_position (gint32 image_ID,gint32 vectors_ID)
name|gimp_image_get_vectors_position
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
block|{
return|return
name|gimp_image_get_item_position
argument_list|(
name|image_ID
argument_list|,
name|vectors_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_raise_vectors:  * @image_ID: The image.  * @vectors_ID: The vectors object to raise.  *  * Deprecated: Use gimp_image_raise_item() instead.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_raise_vectors (gint32 image_ID,gint32 vectors_ID)
name|gimp_image_raise_vectors
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
block|{
return|return
name|gimp_image_raise_item
argument_list|(
name|image_ID
argument_list|,
name|vectors_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_lower_vectors:  * @image_ID: The image.  * @vectors_ID: The vectors object to lower.  *  * Deprecated: Use gimp_image_lower_item() instead.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_lower_vectors (gint32 image_ID,gint32 vectors_ID)
name|gimp_image_lower_vectors
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
block|{
return|return
name|gimp_image_lower_item
argument_list|(
name|image_ID
argument_list|,
name|vectors_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_raise_vectors_to_top:  * @image_ID: The image.  * @vectors_ID: The vectors object to raise to top.  *  * Deprecated: Use gimp_image_raise_item_to_top() instead.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_raise_vectors_to_top (gint32 image_ID,gint32 vectors_ID)
name|gimp_image_raise_vectors_to_top
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
block|{
return|return
name|gimp_image_raise_item_to_top
argument_list|(
name|image_ID
argument_list|,
name|vectors_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_lower_vectors_to_bottom:  * @image_ID: The image.  * @vectors_ID: The vectors object to lower to bottom.  *  * Deprecated: Use gimp_image_lower_item_to_bottom() instead.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_lower_vectors_to_bottom (gint32 image_ID,gint32 vectors_ID)
name|gimp_image_lower_vectors_to_bottom
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
block|{
return|return
name|gimp_image_lower_item_to_bottom
argument_list|(
name|image_ID
argument_list|,
name|vectors_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_parasite_find:  * @image_ID: The image.  * @name: The name of the parasite to find.  *  * Deprecated: Use gimp_image_get_parasite() instead.  *  * Returns: The found parasite.  **/
end_comment

begin_function
name|GimpParasite
modifier|*
DECL|function|gimp_image_parasite_find (gint32 image_ID,const gchar * name)
name|gimp_image_parasite_find
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|gimp_image_get_parasite
argument_list|(
name|image_ID
argument_list|,
name|name
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_parasite_attach:  * @image_ID: The image.  * @parasite: The parasite to attach to an image.  *  * Deprecated: Use gimp_image_attach_parasite() instead.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_parasite_attach (gint32 image_ID,const GimpParasite * parasite)
name|gimp_image_parasite_attach
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
return|return
name|gimp_image_attach_parasite
argument_list|(
name|image_ID
argument_list|,
name|parasite
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_parasite_detach:  * @image_ID: The image.  * @name: The name of the parasite to detach from an image.  *  * Deprecated: Use gimp_image_detach_parasite() instead.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_parasite_detach (gint32 image_ID,const gchar * name)
name|gimp_image_parasite_detach
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|gimp_image_detach_parasite
argument_list|(
name|image_ID
argument_list|,
name|name
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_parasite_list:  * @image_ID: The image.  * @num_parasites: The number of attached parasites.  * @parasites: The names of currently attached parasites.  *  * Deprecated: Use gimp_image_get_parasite_list() instead.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_parasite_list (gint32 image_ID,gint * num_parasites,gchar *** parasites)
name|gimp_image_parasite_list
parameter_list|(
name|gint32
name|image_ID
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
operator|*
name|parasites
operator|=
name|gimp_image_get_parasite_list
argument_list|(
name|image_ID
argument_list|,
name|num_parasites
argument_list|)
expr_stmt|;
return|return
operator|*
name|parasites
operator|!=
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_attach_new_parasite:  * @image_ID: the ID of the image to attach the #GimpParasite to.  * @name: the name of the #GimpParasite to create and attach.  * @flags: the flags set on the #GimpParasite.  * @size: the size of the parasite data in bytes.  * @data: a pointer to the data attached with the #GimpParasite.  *  * Convenience function that creates a parasite and attaches it  * to GIMP.  *  * Deprecated: Use gimp_image_parasite_attach() instead.  *  * Return value: TRUE on successful creation and attachment of  * the new parasite.  *  * See Also: gimp_image_parasite_attach()  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_attach_new_parasite (gint32 image_ID,const gchar * name,gint flags,gint size,gconstpointer data)
name|gimp_image_attach_new_parasite
parameter_list|(
name|gint32
name|image_ID
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
name|gimp_image_parasite_attach
argument_list|(
name|image_ID
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

