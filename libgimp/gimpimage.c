begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpimage.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * gimp_image_get_cmap:  * @image_ID: The image.  * @num_colors: Number of colors in the colormap array.  *  * Returns the image's colormap  *  * This procedure returns an actual pointer to the image's colormap, as  * well as the number of colors contained in the colormap. If the image   * is not of base type INDEXED, this pointer will be NULL.  *  * Returns: The image's colormap.  */
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
name|gint
name|num_bytes
decl_stmt|;
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|cmap
operator|=
name|_gimp_image_get_cmap
argument_list|(
name|image_ID
argument_list|,
operator|&
name|num_bytes
argument_list|)
expr_stmt|;
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
comment|/**  * gimp_image_set_cmap:  * @image_ID: The image.  * @cmap: The new colormap values.  * @num_colors: Number of colors in the colormap array.  *  * Sets the entries in the image's colormap.  *  * This procedure sets the entries in the specified image's colormap.  * The number of colors is specified by the \"num_colors\" parameter  * and corresponds to the number of INT8 triples that must be contained  * in the \"cmap\" array.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_set_cmap (gint32 image_ID,guchar * cmap,gint num_colors)
name|gimp_image_set_cmap
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|guchar
modifier|*
name|cmap
parameter_list|,
name|gint
name|num_colors
parameter_list|)
block|{
return|return
name|_gimp_image_set_cmap
argument_list|(
name|image_ID
argument_list|,
name|num_colors
operator|*
literal|3
argument_list|,
name|cmap
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

end_unit

