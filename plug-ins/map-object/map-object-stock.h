begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__MAPOBJECT_STOCK_H__
end_ifndef

begin_define
DECL|macro|__MAPOBJECT_STOCK_H__
define|#
directive|define
name|__MAPOBJECT_STOCK_H__
end_define

begin_define
DECL|macro|STOCK_INTENSITY_AMBIENT_LOW
define|#
directive|define
name|STOCK_INTENSITY_AMBIENT_LOW
value|"intensity-ambient-low"
end_define

begin_define
DECL|macro|STOCK_INTENSITY_AMBIENT_HIGH
define|#
directive|define
name|STOCK_INTENSITY_AMBIENT_HIGH
value|"intensity-ambient-high"
end_define

begin_define
DECL|macro|STOCK_INTENSITY_DIFFUSE_LOW
define|#
directive|define
name|STOCK_INTENSITY_DIFFUSE_LOW
value|"intensity-diffuse-low"
end_define

begin_define
DECL|macro|STOCK_INTENSITY_DIFFUSE_HIGH
define|#
directive|define
name|STOCK_INTENSITY_DIFFUSE_HIGH
value|"intensity-diffuse-high"
end_define

begin_define
DECL|macro|STOCK_REFLECTIVITY_DIFFUSE_LOW
define|#
directive|define
name|STOCK_REFLECTIVITY_DIFFUSE_LOW
value|"reflectivity-diffuse-low"
end_define

begin_define
DECL|macro|STOCK_REFLECTIVITY_DIFFUSE_HIGH
define|#
directive|define
name|STOCK_REFLECTIVITY_DIFFUSE_HIGH
value|"reflectivity-diffuse-high"
end_define

begin_define
DECL|macro|STOCK_REFLECTIVITY_SPECULAR_LOW
define|#
directive|define
name|STOCK_REFLECTIVITY_SPECULAR_LOW
value|"reflectivity-specular-low"
end_define

begin_define
DECL|macro|STOCK_REFLECTIVITY_SPECULAR_HIGH
define|#
directive|define
name|STOCK_REFLECTIVITY_SPECULAR_HIGH
value|"reflectivity-specular-high"
end_define

begin_define
DECL|macro|STOCK_REFLECTIVITY_HIGHLIGHT_LOW
define|#
directive|define
name|STOCK_REFLECTIVITY_HIGHLIGHT_LOW
value|"reflectivity-highlight-low"
end_define

begin_define
DECL|macro|STOCK_REFLECTIVITY_HIGHLIGHT_HIGH
define|#
directive|define
name|STOCK_REFLECTIVITY_HIGHLIGHT_HIGH
value|"reflectivity-highlight-high"
end_define

begin_function_decl
name|void
name|mapobject_stock_init
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
comment|/* __MAPOBJECT_STOCK_H__ */
end_comment

end_unit

