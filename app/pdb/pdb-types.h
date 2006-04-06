begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PDB_TYPES_H__
end_ifndef

begin_define
DECL|macro|__PDB_TYPES_H__
define|#
directive|define
name|__PDB_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_typedef
DECL|typedef|GimpProcedure
typedef|typedef
name|struct
name|_GimpProcedure
name|GimpProcedure
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPlugInProcedure
typedef|typedef
name|struct
name|_GimpPlugInProcedure
name|GimpPlugInProcedure
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTemporaryProcedure
typedef|typedef
name|struct
name|_GimpTemporaryProcedure
name|GimpTemporaryProcedure
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28bfb7fa0103
block|{
DECL|enumerator|GIMP_PDB_COMPAT_OFF
name|GIMP_PDB_COMPAT_OFF
block|,
DECL|enumerator|GIMP_PDB_COMPAT_ON
name|GIMP_PDB_COMPAT_ON
block|,
DECL|enumerator|GIMP_PDB_COMPAT_WARN
name|GIMP_PDB_COMPAT_WARN
DECL|typedef|GimpPDBCompatMode
block|}
name|GimpPDBCompatMode
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PDB_TYPES_H__ */
end_comment

end_unit

