begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpColorConfig enums  * Copyright (C) 2004  Stefan DÃ¶hla<stefan@doehla.de>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_CONFIG_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_CONFIG_ENUMS_H__
define|#
directive|define
name|__GIMP_COLOR_CONFIG_ENUMS_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_COLOR_MANAGEMENT_MODE
define|#
directive|define
name|GIMP_TYPE_COLOR_MANAGEMENT_MODE
value|(gimp_color_management_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_color_management_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b89592c0103
block|{
DECL|enumerator|GIMP_COLOR_MANAGEMENT_OFF
name|GIMP_COLOR_MANAGEMENT_OFF
block|,
comment|/*< desc="No color management">*/
DECL|enumerator|GIMP_COLOR_MANAGEMENT_DISPLAY
name|GIMP_COLOR_MANAGEMENT_DISPLAY
block|,
comment|/*< desc="Color managed display">*/
DECL|enumerator|GIMP_COLOR_MANAGEMENT_SOFTPROOF
name|GIMP_COLOR_MANAGEMENT_SOFTPROOF
comment|/*< desc="Print simulation">*/
DECL|typedef|GimpColorManagementMode
block|}
name|GimpColorManagementMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_COLOR_RENDERING_INTENT
define|#
directive|define
name|GIMP_TYPE_COLOR_RENDERING_INTENT
define|\
value|(gimp_color_rendering_intent_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_color_rendering_intent_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b89592c0203
block|{
DECL|enumerator|GIMP_COLOR_RENDERING_INTENT_PERCEPTUAL
name|GIMP_COLOR_RENDERING_INTENT_PERCEPTUAL
block|,
comment|/*< desc="Perceptual">*/
DECL|enumerator|GIMP_COLOR_RENDERING_INTENT_RELATIVE_COLORIMETRIC
name|GIMP_COLOR_RENDERING_INTENT_RELATIVE_COLORIMETRIC
block|,
comment|/*< desc="Relative colorimetric">*/
DECL|enumerator|GIMP_COLOR_RENDERING_INTENT_SATURATION
name|GIMP_COLOR_RENDERING_INTENT_SATURATION
block|,
comment|/*< desc="intent|Saturation">*/
DECL|enumerator|GIMP_COLOR_RENDERING_INTENT_ABSOLUTE_COLORIMETRIC
name|GIMP_COLOR_RENDERING_INTENT_ABSOLUTE_COLORIMETRIC
comment|/*< desc="Absolute colorimetric">*/
DECL|typedef|GimpColorRenderingIntent
block|}
name|GimpColorRenderingIntent
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_COLOR_CONFIG_ENUMS_H__ */
end_comment

end_unit

