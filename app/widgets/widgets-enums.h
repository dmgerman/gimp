begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
comment|/*  * these enums that are registered with the type system  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_ACTIVE_COLOR
define|#
directive|define
name|GIMP_TYPE_ACTIVE_COLOR
value|(gimp_active_color_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_active_color_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b8945b80103
block|{
DECL|enumerator|GIMP_ACTIVE_COLOR_FOREGROUND
name|GIMP_ACTIVE_COLOR_FOREGROUND
block|,
comment|/*< desc="Foreground">*/
DECL|enumerator|GIMP_ACTIVE_COLOR_BACKGROUND
name|GIMP_ACTIVE_COLOR_BACKGROUND
comment|/*< desc="Background">*/
DECL|typedef|GimpActiveColor
block|}
name|GimpActiveColor
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ASPECT_TYPE
define|#
directive|define
name|GIMP_TYPE_ASPECT_TYPE
value|(gimp_aspect_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_aspect_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b8945b80203
block|{
DECL|enumerator|GIMP_ASPECT_SQUARE
name|GIMP_ASPECT_SQUARE
block|,
DECL|enumerator|GIMP_ASPECT_PORTRAIT
name|GIMP_ASPECT_PORTRAIT
block|,
comment|/*< desc="Portrait">*/
DECL|enumerator|GIMP_ASPECT_LANDSCAPE
name|GIMP_ASPECT_LANDSCAPE
comment|/*< desc="Landscape">*/
DECL|typedef|GimpAspectType
block|}
name|GimpAspectType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_COLOR_FRAME_MODE
define|#
directive|define
name|GIMP_TYPE_COLOR_FRAME_MODE
value|(gimp_color_frame_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_color_frame_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b8945b80303
block|{
DECL|enumerator|GIMP_COLOR_FRAME_MODE_PIXEL
name|GIMP_COLOR_FRAME_MODE_PIXEL
block|,
comment|/*< desc="Pixel Values">*/
DECL|enumerator|GIMP_COLOR_FRAME_MODE_RGB
name|GIMP_COLOR_FRAME_MODE_RGB
block|,
comment|/*< desc="RGB">*/
DECL|enumerator|GIMP_COLOR_FRAME_MODE_HSV
name|GIMP_COLOR_FRAME_MODE_HSV
block|,
comment|/*< desc="HSV">*/
DECL|enumerator|GIMP_COLOR_FRAME_MODE_CMYK
name|GIMP_COLOR_FRAME_MODE_CMYK
comment|/*< desc="CMYK">*/
DECL|typedef|GimpColorFrameMode
block|}
name|GimpColorFrameMode
typedef|;
end_typedef

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
DECL|enum|__anon2b8945b80403
block|{
DECL|enumerator|GIMP_HELP_BROWSER_GIMP
name|GIMP_HELP_BROWSER_GIMP
block|,
comment|/*< desc="Internal">*/
DECL|enumerator|GIMP_HELP_BROWSER_WEB_BROWSER
name|GIMP_HELP_BROWSER_WEB_BROWSER
comment|/*< desc="Web Browser">*/
DECL|typedef|GimpHelpBrowserType
block|}
name|GimpHelpBrowserType
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
DECL|enum|__anon2b8945b80503
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
DECL|macro|GIMP_TYPE_TAB_STYLE
define|#
directive|define
name|GIMP_TYPE_TAB_STYLE
value|(gimp_tab_style_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_tab_style_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b8945b80603
block|{
DECL|enumerator|GIMP_TAB_STYLE_ICON
name|GIMP_TAB_STYLE_ICON
block|,
comment|/*< desc="Icon">*/
DECL|enumerator|GIMP_TAB_STYLE_PREVIEW
name|GIMP_TAB_STYLE_PREVIEW
block|,
comment|/*< desc="Current Status">*/
DECL|enumerator|GIMP_TAB_STYLE_NAME
name|GIMP_TAB_STYLE_NAME
block|,
comment|/*< desc="Text">*/
DECL|enumerator|GIMP_TAB_STYLE_BLURB
name|GIMP_TAB_STYLE_BLURB
block|,
comment|/*< desc="Description">*/
DECL|enumerator|GIMP_TAB_STYLE_ICON_NAME
name|GIMP_TAB_STYLE_ICON_NAME
block|,
comment|/*< desc="Icon& Text">*/
DECL|enumerator|GIMP_TAB_STYLE_ICON_BLURB
name|GIMP_TAB_STYLE_ICON_BLURB
block|,
comment|/*< desc="Icon& Desc">*/
DECL|enumerator|GIMP_TAB_STYLE_PREVIEW_NAME
name|GIMP_TAB_STYLE_PREVIEW_NAME
block|,
comment|/*< desc="Status& Text">*/
DECL|enumerator|GIMP_TAB_STYLE_PREVIEW_BLURB
name|GIMP_TAB_STYLE_PREVIEW_BLURB
comment|/*< desc="Status& Desc">*/
DECL|typedef|GimpTabStyle
block|}
name|GimpTabStyle
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
DECL|enum|__anon2b8945b80703
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

begin_define
DECL|macro|GIMP_TYPE_WINDOW_HINT
define|#
directive|define
name|GIMP_TYPE_WINDOW_HINT
value|(gimp_window_hint_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_window_hint_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b8945b80803
block|{
DECL|enumerator|GIMP_WINDOW_HINT_NORMAL
name|GIMP_WINDOW_HINT_NORMAL
block|,
comment|/*< desc="Normal Window">*/
DECL|enumerator|GIMP_WINDOW_HINT_UTILITY
name|GIMP_WINDOW_HINT_UTILITY
block|,
comment|/*< desc="Utility Window">*/
DECL|enumerator|GIMP_WINDOW_HINT_KEEP_ABOVE
name|GIMP_WINDOW_HINT_KEEP_ABOVE
comment|/*< desc="Keep Above">*/
DECL|typedef|GimpWindowHint
block|}
name|GimpWindowHint
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
DECL|enum|__anon2b8945b80903
block|{
DECL|enumerator|GIMP_ZOOM_IN
name|GIMP_ZOOM_IN
block|,
comment|/*< desc="Zoom in">*/
DECL|enumerator|GIMP_ZOOM_OUT
name|GIMP_ZOOM_OUT
block|,
comment|/*< desc="Zoom out">*/
DECL|enumerator|GIMP_ZOOM_TO
name|GIMP_ZOOM_TO
comment|/*< skip>*/
DECL|typedef|GimpZoomType
block|}
name|GimpZoomType
typedef|;
end_typedef

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b8945b80a03
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
DECL|enum|__anon2b8945b80b03
block|{
DECL|enumerator|GIMP_PREVIEW_BORDER_BLACK
name|GIMP_PREVIEW_BORDER_BLACK
block|,
DECL|enumerator|GIMP_PREVIEW_BORDER_WHITE
name|GIMP_PREVIEW_BORDER_WHITE
block|,
DECL|enumerator|GIMP_PREVIEW_BORDER_RED
name|GIMP_PREVIEW_BORDER_RED
block|,
DECL|enumerator|GIMP_PREVIEW_BORDER_GREEN
name|GIMP_PREVIEW_BORDER_GREEN
block|, }
DECL|typedef|GimpPreviewBorderType
name|GimpPreviewBorderType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b8945b80c03
block|{
DECL|enumerator|GIMP_DND_TYPE_NONE
name|GIMP_DND_TYPE_NONE
init|=
literal|0
block|,
DECL|enumerator|GIMP_DND_TYPE_URI_LIST
name|GIMP_DND_TYPE_URI_LIST
init|=
literal|1
block|,
DECL|enumerator|GIMP_DND_TYPE_TEXT_PLAIN
name|GIMP_DND_TYPE_TEXT_PLAIN
init|=
literal|2
block|,
DECL|enumerator|GIMP_DND_TYPE_NETSCAPE_URL
name|GIMP_DND_TYPE_NETSCAPE_URL
init|=
literal|3
block|,
DECL|enumerator|GIMP_DND_TYPE_COLOR
name|GIMP_DND_TYPE_COLOR
init|=
literal|4
block|,
DECL|enumerator|GIMP_DND_TYPE_SVG
name|GIMP_DND_TYPE_SVG
init|=
literal|5
block|,
DECL|enumerator|GIMP_DND_TYPE_SVG_XML
name|GIMP_DND_TYPE_SVG_XML
init|=
literal|6
block|,
DECL|enumerator|GIMP_DND_TYPE_IMAGE
name|GIMP_DND_TYPE_IMAGE
init|=
literal|7
block|,
DECL|enumerator|GIMP_DND_TYPE_LAYER
name|GIMP_DND_TYPE_LAYER
init|=
literal|8
block|,
DECL|enumerator|GIMP_DND_TYPE_CHANNEL
name|GIMP_DND_TYPE_CHANNEL
init|=
literal|9
block|,
DECL|enumerator|GIMP_DND_TYPE_LAYER_MASK
name|GIMP_DND_TYPE_LAYER_MASK
init|=
literal|10
block|,
DECL|enumerator|GIMP_DND_TYPE_COMPONENT
name|GIMP_DND_TYPE_COMPONENT
init|=
literal|11
block|,
DECL|enumerator|GIMP_DND_TYPE_VECTORS
name|GIMP_DND_TYPE_VECTORS
init|=
literal|12
block|,
DECL|enumerator|GIMP_DND_TYPE_BRUSH
name|GIMP_DND_TYPE_BRUSH
init|=
literal|13
block|,
DECL|enumerator|GIMP_DND_TYPE_PATTERN
name|GIMP_DND_TYPE_PATTERN
init|=
literal|14
block|,
DECL|enumerator|GIMP_DND_TYPE_GRADIENT
name|GIMP_DND_TYPE_GRADIENT
init|=
literal|15
block|,
DECL|enumerator|GIMP_DND_TYPE_PALETTE
name|GIMP_DND_TYPE_PALETTE
init|=
literal|16
block|,
DECL|enumerator|GIMP_DND_TYPE_FONT
name|GIMP_DND_TYPE_FONT
init|=
literal|17
block|,
DECL|enumerator|GIMP_DND_TYPE_BUFFER
name|GIMP_DND_TYPE_BUFFER
init|=
literal|18
block|,
DECL|enumerator|GIMP_DND_TYPE_IMAGEFILE
name|GIMP_DND_TYPE_IMAGEFILE
init|=
literal|19
block|,
DECL|enumerator|GIMP_DND_TYPE_TEMPLATE
name|GIMP_DND_TYPE_TEMPLATE
init|=
literal|20
block|,
DECL|enumerator|GIMP_DND_TYPE_TOOL
name|GIMP_DND_TYPE_TOOL
init|=
literal|21
block|,
DECL|enumerator|GIMP_DND_TYPE_DIALOG
name|GIMP_DND_TYPE_DIALOG
init|=
literal|22
block|,
DECL|enumerator|GIMP_DND_TYPE_LAST
name|GIMP_DND_TYPE_LAST
init|=
name|GIMP_DND_TYPE_DIALOG
DECL|typedef|GimpDndType
block|}
name|GimpDndType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b8945b80d03
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
DECL|enum|__anon2b8945b80e03
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
comment|/*< skip>*/
DECL|enum|__anon2b8945b80f03
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
DECL|enumerator|GIMP_HAND_TOOL_CURSOR
name|GIMP_HAND_TOOL_CURSOR
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
DECL|enum|__anon2b8945b81003
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
comment|/*< skip>*/
DECL|enum|__anon2b8945b81103
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

