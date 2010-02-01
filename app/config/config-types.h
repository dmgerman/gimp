begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpConfig typedefs  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CONFIG_TYPES_H__
end_ifndef

begin_define
DECL|macro|__CONFIG_TYPES_H__
define|#
directive|define
name|__CONFIG_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfigtypes.h"
end_include

begin_include
include|#
directive|include
file|"config/config-enums.h"
end_include

begin_define
DECL|macro|GIMP_OPACITY_TRANSPARENT
define|#
directive|define
name|GIMP_OPACITY_TRANSPARENT
value|0.0
end_define

begin_define
DECL|macro|GIMP_OPACITY_OPAQUE
define|#
directive|define
name|GIMP_OPACITY_OPAQUE
value|1.0
end_define

begin_typedef
DECL|typedef|GimpBaseConfig
typedef|typedef
name|struct
name|_GimpBaseConfig
name|GimpBaseConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCoreConfig
typedef|typedef
name|struct
name|_GimpCoreConfig
name|GimpCoreConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDisplayConfig
typedef|typedef
name|struct
name|_GimpDisplayConfig
name|GimpDisplayConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpGuiConfig
typedef|typedef
name|struct
name|_GimpGuiConfig
name|GimpGuiConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPluginConfig
typedef|typedef
name|struct
name|_GimpPluginConfig
name|GimpPluginConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpRc
typedef|typedef
name|struct
name|_GimpRc
name|GimpRc
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpXmlParser
typedef|typedef
name|struct
name|_GimpXmlParser
name|GimpXmlParser
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDisplayOptions
typedef|typedef
name|struct
name|_GimpDisplayOptions
name|GimpDisplayOptions
typedef|;
end_typedef

begin_comment
comment|/* should be in core/core-types.h */
end_comment

begin_typedef
DECL|typedef|GimpGrid
typedef|typedef
name|struct
name|_GimpGrid
name|GimpGrid
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTemplate
typedef|typedef
name|struct
name|_GimpTemplate
name|GimpTemplate
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __CONFIG_TYPES_H__ */
end_comment

end_unit

