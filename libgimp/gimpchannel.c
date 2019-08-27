begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpchannel.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpChannel,gimp_channel,GIMP_TYPE_DRAWABLE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpChannel
argument_list|,
argument|gimp_channel
argument_list|,
argument|GIMP_TYPE_DRAWABLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_drawable_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_channel_class_init
parameter_list|(
name|GimpChannelClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_init (GimpChannel * channel)
name|gimp_channel_init
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|)
block|{ }
end_function

begin_comment
comment|/**  * gimp_channel_new:  * @image:   The image to which to add the channel.  * @name:    The channel name.  * @width:   The channel width.  * @height:  The channel height.  * @opacity: The channel opacity.  * @color:   The channel compositing color.  *  * Create a new channel.  *  * This procedure creates a new channel with the specified width and  * height. Name, opacity, and color are also supplied parameters. The  * new channel still needs to be added to the image, as this is not  * automatic. Add the new channel with the gimp_image_insert_channel()  * command. Other attributes such as channel show masked, should be  * set with explicit procedure calls. The channel's contents are  * undefined initially.  *  * Returns: (transfer none): The newly created channel.  *          The object belongs to libgimp and you should not free it.  */
end_comment

begin_function
name|GimpChannel
modifier|*
DECL|function|gimp_channel_new (GimpImage * image,const gchar * name,guint width,guint height,gdouble opacity,const GimpRGB * color)
name|gimp_channel_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
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
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
return|return
name|_gimp_channel_new
argument_list|(
name|image
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
argument_list|)
return|;
block|}
end_function

end_unit

