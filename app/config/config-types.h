begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpConfig typedefs  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_typedef
DECL|typedef|GimpConfig
typedef|typedef
name|struct
name|_GimpConfig
name|GimpConfig
typedef|;
end_typedef

begin_comment
DECL|typedef|GimpConfig
comment|/* dummy typedef */
end_comment

begin_typedef
DECL|typedef|GimpConfigInterface
typedef|typedef
name|struct
name|_GimpConfigInterface
name|GimpConfigInterface
typedef|;
end_typedef

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
DECL|typedef|GimpConfigWriter
typedef|typedef
name|struct
name|_GimpConfigWriter
name|GimpConfigWriter
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
DECL|typedef|GimpGrid
typedef|typedef
name|struct
name|_GimpGrid
name|GimpGrid
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

