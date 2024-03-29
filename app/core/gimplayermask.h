begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LAYER_MASK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LAYER_MASK_H__
define|#
directive|define
name|__GIMP_LAYER_MASK_H__
end_define

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_LAYER_MASK
define|#
directive|define
name|GIMP_TYPE_LAYER_MASK
value|(gimp_layer_mask_get_type ())
end_define

begin_define
DECL|macro|GIMP_LAYER_MASK (obj)
define|#
directive|define
name|GIMP_LAYER_MASK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LAYER_MASK, GimpLayerMask))
end_define

begin_define
DECL|macro|GIMP_LAYER_MASK_CLASS (klass)
define|#
directive|define
name|GIMP_LAYER_MASK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LAYER_MASK, GimpLayerMaskClass))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_MASK (obj)
define|#
directive|define
name|GIMP_IS_LAYER_MASK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LAYER_MASK))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_MASK_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LAYER_MASK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LAYER_MASK))
end_define

begin_define
DECL|macro|GIMP_LAYER_MASK_GET_CLASS (obj)
define|#
directive|define
name|GIMP_LAYER_MASK_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_LAYER_MASK, GimpLayerMaskClass))
end_define

begin_typedef
DECL|typedef|GimpLayerMaskClass
typedef|typedef
name|struct
name|_GimpLayerMaskClass
name|GimpLayerMaskClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpLayerMask
struct|struct
name|_GimpLayerMask
block|{
DECL|member|parent_instance
name|GimpChannel
name|parent_instance
decl_stmt|;
DECL|member|layer
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLayerMaskClass
struct|struct
name|_GimpLayerMaskClass
block|{
DECL|member|parent_class
name|GimpChannelClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_layer_mask_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpLayerMask
modifier|*
name|gimp_layer_mask_new
parameter_list|(
name|GimpImage
modifier|*
name|image
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
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_mask_set_layer
parameter_list|(
name|GimpLayerMask
modifier|*
name|layer_mask
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_layer_mask_get_layer
parameter_list|(
name|GimpLayerMask
modifier|*
name|layer_mask
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LAYER_MASK_H__ */
end_comment

end_unit

