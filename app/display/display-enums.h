begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DISPLAY_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__DISPLAY_ENUMS_H__
define|#
directive|define
name|__DISPLAY_ENUMS_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_CURSOR_PRECISION
define|#
directive|define
name|GIMP_TYPE_CURSOR_PRECISION
value|(gimp_cursor_precision_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_cursor_precision_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b7964040103
block|{
DECL|enumerator|GIMP_CURSOR_PRECISION_PIXEL_CENTER
name|GIMP_CURSOR_PRECISION_PIXEL_CENTER
block|,
DECL|enumerator|GIMP_CURSOR_PRECISION_PIXEL_BORDER
name|GIMP_CURSOR_PRECISION_PIXEL_BORDER
block|,
DECL|enumerator|GIMP_CURSOR_PRECISION_SUBPIXEL
name|GIMP_CURSOR_PRECISION_SUBPIXEL
DECL|typedef|GimpCursorPrecision
block|}
name|GimpCursorPrecision
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_HANDLE_TYPE
define|#
directive|define
name|GIMP_TYPE_HANDLE_TYPE
value|(gimp_handle_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_handle_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b7964040203
block|{
DECL|enumerator|GIMP_HANDLE_SQUARE
name|GIMP_HANDLE_SQUARE
block|,
DECL|enumerator|GIMP_HANDLE_FILLED_SQUARE
name|GIMP_HANDLE_FILLED_SQUARE
block|,
DECL|enumerator|GIMP_HANDLE_CIRCLE
name|GIMP_HANDLE_CIRCLE
block|,
DECL|enumerator|GIMP_HANDLE_FILLED_CIRCLE
name|GIMP_HANDLE_FILLED_CIRCLE
block|,
DECL|enumerator|GIMP_HANDLE_CROSS
name|GIMP_HANDLE_CROSS
DECL|typedef|GimpHandleType
block|}
name|GimpHandleType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_HANDLE_ANCHOR
define|#
directive|define
name|GIMP_TYPE_HANDLE_ANCHOR
value|(gimp_handle_anchor_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_handle_anchor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b7964040303
block|{
DECL|enumerator|GIMP_HANDLE_ANCHOR_CENTER
name|GIMP_HANDLE_ANCHOR_CENTER
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_NORTH
name|GIMP_HANDLE_ANCHOR_NORTH
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_NORTH_WEST
name|GIMP_HANDLE_ANCHOR_NORTH_WEST
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_NORTH_EAST
name|GIMP_HANDLE_ANCHOR_NORTH_EAST
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_SOUTH
name|GIMP_HANDLE_ANCHOR_SOUTH
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_SOUTH_WEST
name|GIMP_HANDLE_ANCHOR_SOUTH_WEST
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_SOUTH_EAST
name|GIMP_HANDLE_ANCHOR_SOUTH_EAST
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_WEST
name|GIMP_HANDLE_ANCHOR_WEST
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_EAST
name|GIMP_HANDLE_ANCHOR_EAST
DECL|typedef|GimpHandleAnchor
block|}
name|GimpHandleAnchor
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ZOOM_FOCUS
define|#
directive|define
name|GIMP_TYPE_ZOOM_FOCUS
value|(gimp_zoom_focus_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_zoom_focus_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b7964040403
block|{
comment|/* Make a best guess */
DECL|enumerator|GIMP_ZOOM_FOCUS_BEST_GUESS
name|GIMP_ZOOM_FOCUS_BEST_GUESS
block|,
comment|/* Use the mouse cursor (if within canvas) */
DECL|enumerator|GIMP_ZOOM_FOCUS_POINTER
name|GIMP_ZOOM_FOCUS_POINTER
block|,
comment|/* Use the image center */
DECL|enumerator|GIMP_ZOOM_FOCUS_IMAGE_CENTER
name|GIMP_ZOOM_FOCUS_IMAGE_CENTER
block|,
comment|/* If the image is centered, retain the centering. Else use    * _BEST_GUESS    */
DECL|enumerator|GIMP_ZOOM_FOCUS_RETAIN_CENTERING_ELSE_BEST_GUESS
name|GIMP_ZOOM_FOCUS_RETAIN_CENTERING_ELSE_BEST_GUESS
DECL|typedef|GimpZoomFocus
block|}
name|GimpZoomFocus
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DISPLAY_ENUMS_H__ */
end_comment

end_unit

