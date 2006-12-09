begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DISPLAY_TYPES_H__
end_ifndef

begin_define
DECL|macro|__DISPLAY_TYPES_H__
define|#
directive|define
name|__DISPLAY_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"widgets/widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"display/display-enums.h"
end_include

begin_typedef
DECL|typedef|GimpCanvas
typedef|typedef
name|struct
name|_GimpCanvas
name|GimpCanvas
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDisplay
typedef|typedef
name|struct
name|_GimpDisplay
name|GimpDisplay
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDisplayShell
typedef|typedef
name|struct
name|_GimpDisplayShell
name|GimpDisplayShell
typedef|;
end_typedef

begin_comment
comment|/* typedef struct _GimpDisplayOptions GimpDisplayOptions; in config-types.h */
end_comment

begin_typedef
DECL|typedef|GimpNavigationEditor
typedef|typedef
name|struct
name|_GimpNavigationEditor
name|GimpNavigationEditor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpScaleComboBox
typedef|typedef
name|struct
name|_GimpScaleComboBox
name|GimpScaleComboBox
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpStatusbar
typedef|typedef
name|struct
name|_GimpStatusbar
name|GimpStatusbar
typedef|;
end_typedef

begin_typedef
DECL|typedef|Selection
typedef|typedef
name|struct
name|_Selection
name|Selection
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DISPLAY_TYPES_H__ */
end_comment

end_unit

