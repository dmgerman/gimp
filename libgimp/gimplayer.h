begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimplayer.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LAYER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LAYER_H__
define|#
directive|define
name|__GIMP_LAYER_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
comment|/* For information look into the C source or the html documentation */
DECL|macro|gimp_layer_get_mask_id
define|#
directive|define
name|gimp_layer_get_mask_id
value|gimp_layer_mask
DECL|macro|gimp_layer_get_image_id
define|#
directive|define
name|gimp_layer_get_image_id
value|gimp_drawable_image
DECL|macro|gimp_layer_is_floating_selection
define|#
directive|define
name|gimp_layer_is_floating_selection
value|gimp_layer_is_floating_sel
DECL|macro|gimp_layer_get_preserve_transparency
define|#
directive|define
name|gimp_layer_get_preserve_transparency
value|gimp_layer_get_preserve_trans
DECL|macro|gimp_layer_set_preserve_transparency
define|#
directive|define
name|gimp_layer_set_preserve_transparency
value|gimp_layer_set_preserve_trans
name|gint32
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
function_decl|;
name|gint32
name|gimp_layer_copy
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LAYER_H__ */
end_comment

end_unit

