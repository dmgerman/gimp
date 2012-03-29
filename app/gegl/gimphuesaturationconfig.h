begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphuesaturationconfig.h  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HUE_SATURATION_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HUE_SATURATION_CONFIG_H__
define|#
directive|define
name|__GIMP_HUE_SATURATION_CONFIG_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpimagemapconfig.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_HUE_SATURATION_CONFIG
define|#
directive|define
name|GIMP_TYPE_HUE_SATURATION_CONFIG
value|(gimp_hue_saturation_config_get_type ())
end_define

begin_define
DECL|macro|GIMP_HUE_SATURATION_CONFIG (obj)
define|#
directive|define
name|GIMP_HUE_SATURATION_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_HUE_SATURATION_CONFIG, GimpHueSaturationConfig))
end_define

begin_define
DECL|macro|GIMP_HUE_SATURATION_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_HUE_SATURATION_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_HUE_SATURATION_CONFIG, GimpHueSaturationConfigClass))
end_define

begin_define
DECL|macro|GIMP_IS_HUE_SATURATION_CONFIG (obj)
define|#
directive|define
name|GIMP_IS_HUE_SATURATION_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_HUE_SATURATION_CONFIG))
end_define

begin_define
DECL|macro|GIMP_IS_HUE_SATURATION_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_HUE_SATURATION_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_HUE_SATURATION_CONFIG))
end_define

begin_define
DECL|macro|GIMP_HUE_SATURATION_CONFIG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_HUE_SATURATION_CONFIG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_HUE_SATURATION_CONFIG, GimpHueSaturationConfigClass))
end_define

begin_typedef
DECL|typedef|GimpHueSaturationConfigClass
typedef|typedef
name|struct
name|_GimpHueSaturationConfigClass
name|GimpHueSaturationConfigClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpHueSaturationConfig
struct|struct
name|_GimpHueSaturationConfig
block|{
DECL|member|parent_instance
name|GimpImageMapConfig
name|parent_instance
decl_stmt|;
DECL|member|range
name|GimpHueRange
name|range
decl_stmt|;
DECL|member|hue
name|gdouble
name|hue
index|[
literal|7
index|]
decl_stmt|;
DECL|member|saturation
name|gdouble
name|saturation
index|[
literal|7
index|]
decl_stmt|;
DECL|member|lightness
name|gdouble
name|lightness
index|[
literal|7
index|]
decl_stmt|;
DECL|member|overlap
name|gdouble
name|overlap
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpHueSaturationConfigClass
struct|struct
name|_GimpHueSaturationConfigClass
block|{
DECL|member|parent_class
name|GimpImageMapConfigClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_hue_saturation_config_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_hue_saturation_config_reset_range
parameter_list|(
name|GimpHueSaturationConfig
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
comment|/* __GIMP_HUE_SATURATION_CONFIG_H__ */
end_comment

end_unit

