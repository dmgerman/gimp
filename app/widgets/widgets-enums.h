begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*< proxy-skip>*/
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__WIDGETS_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__WIDGETS_ENUMS_H__
define|#
directive|define
name|__WIDGETS_ENUMS_H__
end_define

begin_comment
comment|/*   * these enums that are registered with the type system  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_HELP_BROWSER_TYPE
define|#
directive|define
name|GIMP_TYPE_HELP_BROWSER_TYPE
value|(gimp_help_browser_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_help_browser_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6ca6980103
block|{
DECL|enumerator|GIMP_HELP_BROWSER_GIMP
name|GIMP_HELP_BROWSER_GIMP
block|,
comment|/*< desc="Internal">*/
DECL|enumerator|GIMP_HELP_BROWSER_NETSCAPE
name|GIMP_HELP_BROWSER_NETSCAPE
comment|/*< desc="Netscape">*/
DECL|typedef|GimpHelpBrowserType
block|}
name|GimpHelpBrowserType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ZOOM_TYPE
define|#
directive|define
name|GIMP_TYPE_ZOOM_TYPE
value|(gimp_zoom_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_zoom_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6ca6980203
block|{
DECL|enumerator|GIMP_ZOOM_IN
name|GIMP_ZOOM_IN
block|,
comment|/*< desc="Zoom in">*/
DECL|enumerator|GIMP_ZOOM_OUT
name|GIMP_ZOOM_OUT
comment|/*< desc="Zoom out">*/
DECL|typedef|GimpZoomType
block|}
name|GimpZoomType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_HISTOGRAM_SCALE
define|#
directive|define
name|GIMP_TYPE_HISTOGRAM_SCALE
value|(gimp_histogram_scale_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_histogram_scale_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6ca6980303
block|{
DECL|enumerator|GIMP_HISTOGRAM_SCALE_LINEAR
name|GIMP_HISTOGRAM_SCALE_LINEAR
block|,
comment|/*< desc="Linear">*/
DECL|enumerator|GIMP_HISTOGRAM_SCALE_LOGARITHMIC
name|GIMP_HISTOGRAM_SCALE_LOGARITHMIC
comment|/*< desc="Logarithmic">*/
DECL|typedef|GimpHistogramScale
block|}
name|GimpHistogramScale
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_VIEW_TYPE
define|#
directive|define
name|GIMP_TYPE_VIEW_TYPE
value|(gimp_view_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_view_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6ca6980403
block|{
DECL|enumerator|GIMP_VIEW_TYPE_LIST
name|GIMP_VIEW_TYPE_LIST
block|,
comment|/*< desc="View as List">*/
DECL|enumerator|GIMP_VIEW_TYPE_GRID
name|GIMP_VIEW_TYPE_GRID
comment|/*< desc="View as Grid">*/
DECL|typedef|GimpViewType
block|}
name|GimpViewType
typedef|;
end_typedef

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2c6ca6980503
block|{
DECL|enumerator|GIMP_PREVIEW_BG_CHECKS
name|GIMP_PREVIEW_BG_CHECKS
block|,
DECL|enumerator|GIMP_PREVIEW_BG_WHITE
name|GIMP_PREVIEW_BG_WHITE
DECL|typedef|GimpPreviewBG
block|}
name|GimpPreviewBG
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2c6ca6980603
block|{
DECL|enumerator|GIMP_DROP_NONE
name|GIMP_DROP_NONE
block|,
DECL|enumerator|GIMP_DROP_ABOVE
name|GIMP_DROP_ABOVE
block|,
DECL|enumerator|GIMP_DROP_BELOW
name|GIMP_DROP_BELOW
DECL|typedef|GimpDropType
block|}
name|GimpDropType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2c6ca6980703
block|{
DECL|enumerator|GIMP_MOUSE_CURSOR
name|GIMP_MOUSE_CURSOR
init|=
literal|1024
comment|/* (GDK_LAST_CURSOR + 2) yes, this is insane */
block|,
DECL|enumerator|GIMP_CROSSHAIR_CURSOR
name|GIMP_CROSSHAIR_CURSOR
block|,
DECL|enumerator|GIMP_CROSSHAIR_SMALL_CURSOR
name|GIMP_CROSSHAIR_SMALL_CURSOR
block|,
DECL|enumerator|GIMP_BAD_CURSOR
name|GIMP_BAD_CURSOR
block|,
DECL|enumerator|GIMP_ZOOM_CURSOR
name|GIMP_ZOOM_CURSOR
block|,
DECL|enumerator|GIMP_COLOR_PICKER_CURSOR
name|GIMP_COLOR_PICKER_CURSOR
block|,
DECL|enumerator|GIMP_LAST_CURSOR_ENTRY
name|GIMP_LAST_CURSOR_ENTRY
DECL|typedef|GimpCursorType
block|}
name|GimpCursorType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip, proxy-resume>*/
DECL|enum|__anon2c6ca6980803
block|{
DECL|enumerator|GIMP_TOOL_CURSOR_NONE
name|GIMP_TOOL_CURSOR_NONE
block|,
DECL|enumerator|GIMP_RECT_SELECT_TOOL_CURSOR
name|GIMP_RECT_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_ELLIPSE_SELECT_TOOL_CURSOR
name|GIMP_ELLIPSE_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_FREE_SELECT_TOOL_CURSOR
name|GIMP_FREE_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_FUZZY_SELECT_TOOL_CURSOR
name|GIMP_FUZZY_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BEZIER_SELECT_TOOL_CURSOR
name|GIMP_BEZIER_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_SCISSORS_TOOL_CURSOR
name|GIMP_SCISSORS_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_MOVE_TOOL_CURSOR
name|GIMP_MOVE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_ZOOM_TOOL_CURSOR
name|GIMP_ZOOM_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_CROP_TOOL_CURSOR
name|GIMP_CROP_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_RESIZE_TOOL_CURSOR
name|GIMP_RESIZE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_ROTATE_TOOL_CURSOR
name|GIMP_ROTATE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_SHEAR_TOOL_CURSOR
name|GIMP_SHEAR_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_PERSPECTIVE_TOOL_CURSOR
name|GIMP_PERSPECTIVE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_FLIP_HORIZONTAL_TOOL_CURSOR
name|GIMP_FLIP_HORIZONTAL_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_FLIP_VERTICAL_TOOL_CURSOR
name|GIMP_FLIP_VERTICAL_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_TEXT_TOOL_CURSOR
name|GIMP_TEXT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_COLOR_PICKER_TOOL_CURSOR
name|GIMP_COLOR_PICKER_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BUCKET_FILL_TOOL_CURSOR
name|GIMP_BUCKET_FILL_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BLEND_TOOL_CURSOR
name|GIMP_BLEND_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_PENCIL_TOOL_CURSOR
name|GIMP_PENCIL_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_PAINTBRUSH_TOOL_CURSOR
name|GIMP_PAINTBRUSH_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_AIRBRUSH_TOOL_CURSOR
name|GIMP_AIRBRUSH_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_INK_TOOL_CURSOR
name|GIMP_INK_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_CLONE_TOOL_CURSOR
name|GIMP_CLONE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_ERASER_TOOL_CURSOR
name|GIMP_ERASER_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_SMUDGE_TOOL_CURSOR
name|GIMP_SMUDGE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BLUR_TOOL_CURSOR
name|GIMP_BLUR_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_DODGE_TOOL_CURSOR
name|GIMP_DODGE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BURN_TOOL_CURSOR
name|GIMP_BURN_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_MEASURE_TOOL_CURSOR
name|GIMP_MEASURE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_LAST_STOCK_TOOL_CURSOR_ENTRY
name|GIMP_LAST_STOCK_TOOL_CURSOR_ENTRY
DECL|typedef|GimpToolCursorType
block|}
name|GimpToolCursorType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2c6ca6980903
block|{
DECL|enumerator|GIMP_CURSOR_MODIFIER_NONE
name|GIMP_CURSOR_MODIFIER_NONE
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_PLUS
name|GIMP_CURSOR_MODIFIER_PLUS
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_MINUS
name|GIMP_CURSOR_MODIFIER_MINUS
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_INTERSECT
name|GIMP_CURSOR_MODIFIER_INTERSECT
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_MOVE
name|GIMP_CURSOR_MODIFIER_MOVE
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_RESIZE
name|GIMP_CURSOR_MODIFIER_RESIZE
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_CONTROL
name|GIMP_CURSOR_MODIFIER_CONTROL
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_ANCHOR
name|GIMP_CURSOR_MODIFIER_ANCHOR
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_FOREGROUND
name|GIMP_CURSOR_MODIFIER_FOREGROUND
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_BACKGROUND
name|GIMP_CURSOR_MODIFIER_BACKGROUND
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_PATTERN
name|GIMP_CURSOR_MODIFIER_PATTERN
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_HAND
name|GIMP_CURSOR_MODIFIER_HAND
block|,
DECL|enumerator|GIMP_LAST_CURSOR_MODIFIER_ENTRY
name|GIMP_LAST_CURSOR_MODIFIER_ENTRY
DECL|typedef|GimpCursorModifier
block|}
name|GimpCursorModifier
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip, proxy-skip>*/
DECL|enum|__anon2c6ca6980a03
block|{
DECL|enumerator|GIMP_DEVICE_VALUE_MODE
name|GIMP_DEVICE_VALUE_MODE
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_DEVICE_VALUE_AXES
name|GIMP_DEVICE_VALUE_AXES
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_DEVICE_VALUE_KEYS
name|GIMP_DEVICE_VALUE_KEYS
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_DEVICE_VALUE_TOOL
name|GIMP_DEVICE_VALUE_TOOL
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_DEVICE_VALUE_FOREGROUND
name|GIMP_DEVICE_VALUE_FOREGROUND
init|=
literal|1
operator|<<
literal|4
block|,
DECL|enumerator|GIMP_DEVICE_VALUE_BACKGROUND
name|GIMP_DEVICE_VALUE_BACKGROUND
init|=
literal|1
operator|<<
literal|5
block|,
DECL|enumerator|GIMP_DEVICE_VALUE_BRUSH
name|GIMP_DEVICE_VALUE_BRUSH
init|=
literal|1
operator|<<
literal|6
block|,
DECL|enumerator|GIMP_DEVICE_VALUE_PATTERN
name|GIMP_DEVICE_VALUE_PATTERN
init|=
literal|1
operator|<<
literal|7
block|,
DECL|enumerator|GIMP_DEVICE_VALUE_GRADIENT
name|GIMP_DEVICE_VALUE_GRADIENT
init|=
literal|1
operator|<<
literal|8
DECL|typedef|GimpDeviceValues
block|}
name|GimpDeviceValues
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __WIDGETS_ENUMS_H__ */
end_comment

end_unit

