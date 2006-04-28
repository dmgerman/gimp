begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
DECL|typedef|GimpPlugInShm
typedef|typedef
name|struct
name|_GimpPlugInShm
name|GimpPlugInShm
typedef|;
end_typedef

begin_typedef
DECL|typedef|PlugIn
typedef|typedef
name|struct
name|_PlugIn
name|PlugIn
typedef|;
end_typedef

begin_typedef
DECL|typedef|PlugInDef
typedef|typedef
name|struct
name|_PlugInDef
name|PlugInDef
typedef|;
end_typedef

begin_typedef
DECL|typedef|PlugInProcFrame
typedef|typedef
name|struct
name|_PlugInProcFrame
name|PlugInProcFrame
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

