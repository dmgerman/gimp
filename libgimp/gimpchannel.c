begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpchannel.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * gimp_channel_new:  * @image_ID: The image to which to add the channel.  * @name: The channel name.  * @width: The channel width.  * @height: The channel height.  * @opacity: The channel opacity.  * @color: The channel compositing color.  *  * Create a new channel.  *  * This procedure creates a new channel with the specified width and  * height. Name, opacity, and color are also supplied parameters. The  * new channel still needs to be added to the image, as this is not  * automatic. Add the new channel with the 'gimp_image_add_channel'  * command. Other attributes such as channel show masked, should be set  * with explicit procedure calls. The channel's contents are undefined  * initially.  *  * Returns: The newly created channel.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_channel_new (gint32 image_ID,gchar * name,guint width,guint height,gdouble opacity,guchar * color)
name|gimp_channel_new
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|guint
name|width
parameter_list|,
name|guint
name|height
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|guchar
modifier|*
name|color
parameter_list|)
block|{
return|return
name|_gimp_channel_new
argument_list|(
name|image_ID
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|name
argument_list|,
name|opacity
argument_list|,
name|color
index|[
literal|0
index|]
argument_list|,
name|color
index|[
literal|1
index|]
argument_list|,
name|color
index|[
literal|2
index|]
argument_list|)
return|;
block|}
end_function

end_unit

