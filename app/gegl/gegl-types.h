begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gegl-types.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__OUR_GEGL_TYPES_H__
end_ifndef

begin_define
DECL|macro|__OUR_GEGL_TYPES_H__
define|#
directive|define
name|__OUR_GEGL_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"base/base-types.h"
end_include

begin_typedef
DECL|typedef|GimpOperationDesaturate
typedef|typedef
name|struct
name|_GimpOperationDesaturate
name|GimpOperationDesaturate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationTileSink
typedef|typedef
name|struct
name|_GimpOperationTileSink
name|GimpOperationTileSink
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationTileSource
typedef|typedef
name|struct
name|_GimpOperationTileSource
name|GimpOperationTileSource
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __OUR_GEGL_TYPES_H__ */
end_comment

end_unit

