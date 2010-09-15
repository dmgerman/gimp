begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimplayer.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_LAYER_H__
end_undef

begin_include
include|#
directive|include
file|"gimplayer.h"
end_include

begin_comment
comment|/**  * gimp_layer_new:  * @image_ID: The image to which to add the layer.  * @name: The layer name.  * @width: The layer width.  * @height: The layer height.  * @type: The layer type.  * @opacity: The layer opacity.  * @mode: The layer combination mode.  *  * Create a new layer.  *  * This procedure creates a new layer with the specified width, height,  * and type. Name, opacity, and mode are also supplied parameters. The  * new layer still needs to be added to the image, as this is not  * automatic. Add the new layer with the gimp_image_insert_layer()  * command. Other attributes such as layer mask modes, and offsets  * should be set with explicit procedure calls.  *  * Returns: The newly created layer.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_layer_new (gint32 image_ID,const gchar * name,gint width,gint height,GimpImageType type,gdouble opacity,GimpLayerModeEffects mode)
name|gimp_layer_new
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

begin_comment
comment|/**  * gimp_layer_copy:  * @layer_ID: The layer to copy.  *  * Copy a layer.  *  * This procedure copies the specified layer and returns the copy. The  * newly copied layer is for use within the original layer's image. It  * should not be subsequently added to any other image.  *  * Returns: The newly copied layer.  */
end_comment

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

begin_comment
comment|/**  * gimp_layer_get_preserve_trans:  * @layer_ID: The layer.  *  * This procedure is deprecated! Use gimp_layer_get_lock_alpha() instead.  *  * Returns: The layer's preserve transperancy setting.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_layer_get_preserve_trans (gint32 layer_ID)
name|gimp_layer_get_preserve_trans
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
block|{
return|return
name|gimp_layer_get_lock_alpha
argument_list|(
name|layer_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_set_preserve_trans:  * @layer_ID: The layer.  * @preserve_trans: The new layer's preserve transperancy setting.  *  * This procedure is deprecated! Use gimp_layer_set_lock_alpha() instead.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_layer_set_preserve_trans (gint32 layer_ID,gboolean preserve_trans)
name|gimp_layer_set_preserve_trans
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|preserve_trans
parameter_list|)
block|{
return|return
name|gimp_layer_set_lock_alpha
argument_list|(
name|layer_ID
argument_list|,
name|preserve_trans
argument_list|)
return|;
block|}
end_function

end_unit

