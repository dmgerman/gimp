begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__LIGHTING_ICONS_H__
end_ifndef

begin_define
DECL|macro|__LIGHTING_ICONS_H__
define|#
directive|define
name|__LIGHTING_ICONS_H__
end_define

begin_define
DECL|macro|LIGHTING_INTENSITY_AMBIENT_LOW
define|#
directive|define
name|LIGHTING_INTENSITY_AMBIENT_LOW
value|"lighting-intensity-ambient-low"
end_define

begin_define
DECL|macro|LIGHTING_INTENSITY_AMBIENT_HIGH
define|#
directive|define
name|LIGHTING_INTENSITY_AMBIENT_HIGH
value|"lighting-intensity-ambient-high"
end_define

begin_define
DECL|macro|LIGHTING_INTENSITY_DIFFUSE_LOW
define|#
directive|define
name|LIGHTING_INTENSITY_DIFFUSE_LOW
value|"lighting-intensity-diffuse-low"
end_define

begin_define
DECL|macro|LIGHTING_INTENSITY_DIFFUSE_HIGH
define|#
directive|define
name|LIGHTING_INTENSITY_DIFFUSE_HIGH
value|"lighting-intensity-diffuse-high"
end_define

begin_define
DECL|macro|LIGHTING_REFLECTIVITY_DIFFUSE_LOW
define|#
directive|define
name|LIGHTING_REFLECTIVITY_DIFFUSE_LOW
value|"lighting-reflectivity-diffuse-low"
end_define

begin_define
DECL|macro|LIGHTING_REFLECTIVITY_DIFFUSE_HIGH
define|#
directive|define
name|LIGHTING_REFLECTIVITY_DIFFUSE_HIGH
value|"lighting-reflectivity-diffuse-high"
end_define

begin_define
DECL|macro|LIGHTING_REFLECTIVITY_SPECULAR_LOW
define|#
directive|define
name|LIGHTING_REFLECTIVITY_SPECULAR_LOW
value|"lighting-reflectivity-specular-low"
end_define

begin_define
DECL|macro|LIGHTING_REFLECTIVITY_SPECULAR_HIGH
define|#
directive|define
name|LIGHTING_REFLECTIVITY_SPECULAR_HIGH
value|"lighting-reflectivity-specular-high"
end_define

begin_define
DECL|macro|LIGHTING_REFLECTIVITY_HIGHLIGHT_LOW
define|#
directive|define
name|LIGHTING_REFLECTIVITY_HIGHLIGHT_LOW
value|"lighting-reflectivity-highlight-low"
end_define

begin_define
DECL|macro|LIGHTING_REFLECTIVITY_HIGHLIGHT_HIGH
define|#
directive|define
name|LIGHTING_REFLECTIVITY_HIGHLIGHT_HIGH
value|"lighting-reflectivity-highlight-high"
end_define

begin_function_decl
name|void
name|lighting_icons_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __LIGHTING_ICONs_H__ */
end_comment

end_unit

