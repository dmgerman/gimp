begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PLUG_IN_TYPES_H__
end_ifndef

begin_define
DECL|macro|__PLUG_IN_TYPES_H__
define|#
directive|define
name|__PLUG_IN_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-enums.h"
end_include

begin_define
DECL|macro|GIMP_PLUG_IN_TILE_WIDTH
define|#
directive|define
name|GIMP_PLUG_IN_TILE_WIDTH
value|128
end_define

begin_define
DECL|macro|GIMP_PLUG_IN_TILE_HEIGHT
define|#
directive|define
name|GIMP_PLUG_IN_TILE_HEIGHT
value|128
end_define

begin_typedef
DECL|typedef|GimpPlugIn
typedef|typedef
name|struct
name|_GimpPlugIn
name|GimpPlugIn
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPlugInDebug
typedef|typedef
name|struct
name|_GimpPlugInDebug
name|GimpPlugInDebug
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPlugInDef
typedef|typedef
name|struct
name|_GimpPlugInDef
name|GimpPlugInDef
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPlugInManager
typedef|typedef
name|struct
name|_GimpPlugInManager
name|GimpPlugInManager
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPlugInMenuBranch
typedef|typedef
name|struct
name|_GimpPlugInMenuBranch
name|GimpPlugInMenuBranch
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPlugInProcFrame
typedef|typedef
name|struct
name|_GimpPlugInProcFrame
name|GimpPlugInProcFrame
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPlugInShm
typedef|typedef
name|struct
name|_GimpPlugInShm
name|GimpPlugInShm
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PLUG_IN_TYPES_H__ */
end_comment

end_unit

