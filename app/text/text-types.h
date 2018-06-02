begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TEXT_TYPES_H__
end_ifndef

begin_define
DECL|macro|__TEXT_TYPES_H__
define|#
directive|define
name|__TEXT_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"text/text-enums.h"
end_include

begin_typedef
DECL|typedef|GimpFont
typedef|typedef
name|struct
name|_GimpFont
name|GimpFont
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFontFactory
typedef|typedef
name|struct
name|_GimpFontFactory
name|GimpFontFactory
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFontList
typedef|typedef
name|struct
name|_GimpFontList
name|GimpFontList
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpText
typedef|typedef
name|struct
name|_GimpText
name|GimpText
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTextLayer
typedef|typedef
name|struct
name|_GimpTextLayer
name|GimpTextLayer
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTextLayout
typedef|typedef
name|struct
name|_GimpTextLayout
name|GimpTextLayout
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTextUndo
typedef|typedef
name|struct
name|_GimpTextUndo
name|GimpTextUndo
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TEXT_TYPES_H__ */
end_comment

end_unit

