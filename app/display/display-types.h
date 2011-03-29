begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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

begin_if
if|#
directive|if
name|CAIRO_VERSION
operator|>=
name|CAIRO_VERSION_ENCODE
argument_list|(
literal|1
operator|,
literal|9
operator|,
literal|15
argument_list|)
end_if

begin_define
DECL|macro|USE_CAIRO_REGION
define|#
directive|define
name|USE_CAIRO_REGION
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|USE_CAIRO_REGION
end_ifndef

begin_define
DECL|macro|cairo_region_t
define|#
directive|define
name|cairo_region_t
value|GdkRegion
end_define

begin_define
DECL|macro|cairo_rectangle_int_t
define|#
directive|define
name|cairo_rectangle_int_t
value|GdkRectangle
end_define

begin_define
DECL|macro|cairo_region_destroy
define|#
directive|define
name|cairo_region_destroy
value|gdk_region_destroy
end_define

begin_define
DECL|macro|cairo_region_union
define|#
directive|define
name|cairo_region_union
value|gdk_region_union
end_define

begin_define
DECL|macro|cairo_region_create_rectangle
define|#
directive|define
name|cairo_region_create_rectangle
value|gdk_region_rectangle
end_define

begin_define
DECL|macro|cairo_region_union_rectangle
define|#
directive|define
name|cairo_region_union_rectangle
value|gdk_region_union_with_rect
end_define

begin_define
DECL|macro|cairo_region_get_extents
define|#
directive|define
name|cairo_region_get_extents
value|gdk_region_get_clipbox
end_define

begin_define
DECL|macro|cairo_region_subtract
define|#
directive|define
name|cairo_region_subtract
value|gdk_region_subtract
end_define

begin_define
DECL|macro|cairo_region_xor
define|#
directive|define
name|cairo_region_xor
value|gdk_region_xor
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|GimpCanvas
typedef|typedef
name|struct
name|_GimpCanvas
name|GimpCanvas
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCanvasItem
typedef|typedef
name|struct
name|_GimpCanvasItem
name|GimpCanvasItem
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCanvasGroup
typedef|typedef
name|struct
name|_GimpCanvasGroup
name|GimpCanvasGroup
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

begin_typedef
DECL|typedef|GimpImageWindow
typedef|typedef
name|struct
name|_GimpImageWindow
name|GimpImageWindow
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCursorView
typedef|typedef
name|struct
name|_GimpCursorView
name|GimpCursorView
typedef|;
end_typedef

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
DECL|typedef|GimpToolDialog
typedef|typedef
name|struct
name|_GimpToolDialog
name|GimpToolDialog
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

