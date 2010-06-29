begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * Config file serialization and deserialization interface  * Copyright (C) 2001-2003  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONFIG_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONFIG_TYPES_H__
define|#
directive|define
name|__GIMP_CONFIG_TYPES_H__
end_define

begin_include
include|#
directive|include
file|<libgimpbase/gimpbasetypes.h>
end_include

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
DECL|typedef|GimpConfigWriter
typedef|typedef
name|struct
name|_GimpConfigWriter
name|GimpConfigWriter
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpConfigPath
typedef|typedef
name|gchar
modifier|*
name|GimpConfigPath
typedef|;
end_typedef

begin_comment
DECL|typedef|GimpConfigPath
comment|/* to satisfy docs */
end_comment

begin_include
include|#
directive|include
file|<libgimpconfig/gimpcolorconfig-enums.h>
end_include

begin_typedef
DECL|typedef|GimpColorConfig
typedef|typedef
name|struct
name|_GimpColorConfig
name|GimpColorConfig
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONFIG_TYPES_H__ */
end_comment

end_unit

