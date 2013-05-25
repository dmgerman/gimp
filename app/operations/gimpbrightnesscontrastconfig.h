begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbrightnesscontrastconfig.h  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRIGHTNESS_CONTRAST_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRIGHTNESS_CONTRAST_CONFIG_H__
define|#
directive|define
name|__GIMP_BRIGHTNESS_CONTRAST_CONFIG_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpsettings.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_BRIGHTNESS_CONTRAST_CONFIG
define|#
directive|define
name|GIMP_TYPE_BRIGHTNESS_CONTRAST_CONFIG
value|(gimp_brightness_contrast_config_get_type ())
end_define

begin_define
DECL|macro|GIMP_BRIGHTNESS_CONTRAST_CONFIG (obj)
define|#
directive|define
name|GIMP_BRIGHTNESS_CONTRAST_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BRIGHTNESS_CONTRAST_CONFIG, GimpBrightnessContrastConfig))
end_define

begin_define
DECL|macro|GIMP_BRIGHTNESS_CONTRAST_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_BRIGHTNESS_CONTRAST_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_BRIGHTNESS_CONTRAST_CONFIG, GimpBrightnessContrastConfigClass))
end_define

begin_define
DECL|macro|GIMP_IS_BRIGHTNESS_CONTRAST_CONFIG (obj)
define|#
directive|define
name|GIMP_IS_BRIGHTNESS_CONTRAST_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BRIGHTNESS_CONTRAST_CONFIG))
end_define

begin_define
DECL|macro|GIMP_IS_BRIGHTNESS_CONTRAST_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BRIGHTNESS_CONTRAST_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_BRIGHTNESS_CONTRAST_CONFIG))
end_define

begin_define
DECL|macro|GIMP_BRIGHTNESS_CONTRAST_CONFIG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BRIGHTNESS_CONTRAST_CONFIG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_BRIGHTNESS_CONTRAST_CONFIG, GimpBrightnessContrastConfigClass))
end_define

begin_typedef
DECL|typedef|GimpBrightnessContrastConfigClass
typedef|typedef
name|struct
name|_GimpBrightnessContrastConfigClass
name|GimpBrightnessContrastConfigClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBrightnessContrastConfig
struct|struct
name|_GimpBrightnessContrastConfig
block|{
DECL|member|parent_instance
name|GimpSettings
name|parent_instance
decl_stmt|;
DECL|member|brightness
name|gdouble
name|brightness
decl_stmt|;
DECL|member|contrast
name|gdouble
name|contrast
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBrightnessContrastConfigClass
struct|struct
name|_GimpBrightnessContrastConfigClass
block|{
DECL|member|parent_class
name|GimpSettingsClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_brightness_contrast_config_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpLevelsConfig
modifier|*
name|gimp_brightness_contrast_config_to_levels_config
parameter_list|(
name|GimpBrightnessContrastConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_BRIGHTNESS_CONTRAST_CONFIG_H__ */
end_comment

end_unit

