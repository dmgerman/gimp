begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimplayer.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_function
name|gint32
DECL|function|gimp_layer_new (gint32 image_ID,gchar * name,gint width,gint height,GimpImageType type,gdouble opacity,GimpLayerModeEffects mode)
name|gimp_layer_new
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpImageType
name|type
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|)
block|{
return|return
name|_gimp_layer_new
argument_list|(
name|image_ID
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|type
argument_list|,
name|name
argument_list|,
name|opacity
argument_list|,
name|mode
argument_list|)
return|;
block|}
end_function

begin_function
name|gint32
DECL|function|gimp_layer_copy (gint32 layer_ID)
name|gimp_layer_copy
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
block|{
return|return
name|_gimp_layer_copy
argument_list|(
name|layer_ID
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

end_unit

