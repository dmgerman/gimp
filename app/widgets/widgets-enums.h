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
DECL|enum|__anon28b0b9f50103
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
DECL|enum|__anon28b0b9f50203
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
DECL|macro|GIMP_TYPE_COLOR_DIALOG_STATE
define|#
directive|define
name|GIMP_TYPE_COLOR_DIALOG_STATE
value|(gimp_color_dialog_state_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_color_dialog_state_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28b0b9f50303
block|{
DECL|enumerator|GIMP_COLOR_DIALOG_OK
name|GIMP_COLOR_DIALOG_OK
block|,
DECL|enumerator|GIMP_COLOR_DIALOG_CANCEL
name|GIMP_COLOR_DIALOG_CANCEL
block|,
DECL|enumerator|GIMP_COLOR_DIALOG_UPDATE
name|GIMP_COLOR_DIALOG_UPDATE
DECL|typedef|GimpColorDialogState
block|}
name|GimpColorDialogState
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
DECL|enum|__anon28b0b9f50403
block|{
DECL|enumerator|GIMP_COLOR_FRAME_MODE_PIXEL
name|GIMP_COLOR_FRAME_MODE_PIXEL
block|,
comment|/*< desc="Pixel values">*/
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
DECL|macro|GIMP_TYPE_COLOR_PICK_STATE
define|#
directive|define
name|GIMP_TYPE_COLOR_PICK_STATE
value|(gimp_color_pick_state_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_color_pick_state_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28b0b9f50503
block|{
DECL|enumerator|GIMP_COLOR_PICK_STATE_NEW
name|GIMP_COLOR_PICK_STATE_NEW
block|,
DECL|enumerator|GIMP_COLOR_PICK_STATE_UPDATE
name|GIMP_COLOR_PICK_STATE_UPDATE
DECL|typedef|GimpColorPickState
block|}
name|GimpColorPickState
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CURSOR_FORMAT
define|#
directive|define
name|GIMP_TYPE_CURSOR_FORMAT
value|(gimp_cursor_format_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_cursor_format_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28b0b9f50603
block|{
DECL|enumerator|GIMP_CURSOR_FORMAT_BITMAP
name|GIMP_CURSOR_FORMAT_BITMAP
block|,
comment|/*< desc="Black& white">*/
DECL|enumerator|GIMP_CURSOR_FORMAT_PIXBUF
name|GIMP_CURSOR_FORMAT_PIXBUF
comment|/*< desc="Fancy">*/
DECL|typedef|GimpCursorFormat
block|}
name|GimpCursorFormat
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
DECL|enum|__anon28b0b9f50703
block|{
DECL|enumerator|GIMP_HELP_BROWSER_GIMP
name|GIMP_HELP_BROWSER_GIMP
block|,
comment|/*< desc="Internal">*/
DECL|enumerator|GIMP_HELP_BROWSER_WEB_BROWSER
name|GIMP_HELP_BROWSER_WEB_BROWSER
comment|/*< desc="Web browser">*/
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
DECL|enum|__anon28b0b9f50803
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
DECL|enum|__anon28b0b9f50903
block|{
DECL|enumerator|GIMP_TAB_STYLE_ICON
name|GIMP_TAB_STYLE_ICON
block|,
comment|/*< desc="Icon">*/
DECL|enumerator|GIMP_TAB_STYLE_PREVIEW
name|GIMP_TAB_STYLE_PREVIEW
block|,
comment|/*< desc="Current status">*/
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
comment|/*< desc="Icon& text">*/
DECL|enumerator|GIMP_TAB_STYLE_ICON_BLURB
name|GIMP_TAB_STYLE_ICON_BLURB
block|,
comment|/*< desc="Icon& desc">*/
DECL|enumerator|GIMP_TAB_STYLE_PREVIEW_NAME
name|GIMP_TAB_STYLE_PREVIEW_NAME
block|,
comment|/*< desc="Status& text">*/
DECL|enumerator|GIMP_TAB_STYLE_PREVIEW_BLURB
name|GIMP_TAB_STYLE_PREVIEW_BLURB
comment|/*< desc="Status& desc">*/
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
DECL|enum|__anon28b0b9f50a03
block|{
DECL|enumerator|GIMP_VIEW_TYPE_LIST
name|GIMP_VIEW_TYPE_LIST
block|,
comment|/*< desc="View as list">*/
DECL|enumerator|GIMP_VIEW_TYPE_GRID
name|GIMP_VIEW_TYPE_GRID
comment|/*< desc="View as grid">*/
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
DECL|enum|__anon28b0b9f50b03
block|{
DECL|enumerator|GIMP_WINDOW_HINT_NORMAL
name|GIMP_WINDOW_HINT_NORMAL
block|,
comment|/*< desc="Normal window">*/
DECL|enumerator|GIMP_WINDOW_HINT_UTILITY
name|GIMP_WINDOW_HINT_UTILITY
block|,
comment|/*< desc="Utility window">*/
DECL|enumerator|GIMP_WINDOW_HINT_KEEP_ABOVE
name|GIMP_WINDOW_HINT_KEEP_ABOVE
comment|/*< desc="Keep above">*/
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
DECL|enum|__anon28b0b9f50c03
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
DECL|enum|__anon28b0b9f50d03
block|{
DECL|enumerator|GIMP_VIEW_BG_CHECKS
name|GIMP_VIEW_BG_CHECKS
block|,
DECL|enumerator|GIMP_VIEW_BG_WHITE
name|GIMP_VIEW_BG_WHITE
DECL|typedef|GimpViewBG
block|}
name|GimpViewBG
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28b0b9f50e03
block|{
DECL|enumerator|GIMP_VIEW_BORDER_BLACK
name|GIMP_VIEW_BORDER_BLACK
block|,
DECL|enumerator|GIMP_VIEW_BORDER_WHITE
name|GIMP_VIEW_BORDER_WHITE
block|,
DECL|enumerator|GIMP_VIEW_BORDER_RED
name|GIMP_VIEW_BORDER_RED
block|,
DECL|enumerator|GIMP_VIEW_BORDER_GREEN
name|GIMP_VIEW_BORDER_GREEN
DECL|typedef|GimpViewBorderType
block|}
name|GimpViewBorderType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28b0b9f50f03
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
DECL|enumerator|GIMP_DND_TYPE_PNG
name|GIMP_DND_TYPE_PNG
init|=
literal|5
block|,
DECL|enumerator|GIMP_DND_TYPE_SVG
name|GIMP_DND_TYPE_SVG
init|=
literal|6
block|,
DECL|enumerator|GIMP_DND_TYPE_SVG_XML
name|GIMP_DND_TYPE_SVG_XML
init|=
literal|7
block|,
DECL|enumerator|GIMP_DND_TYPE_IMAGE
name|GIMP_DND_TYPE_IMAGE
init|=
literal|8
block|,
DECL|enumerator|GIMP_DND_TYPE_LAYER
name|GIMP_DND_TYPE_LAYER
init|=
literal|9
block|,
DECL|enumerator|GIMP_DND_TYPE_CHANNEL
name|GIMP_DND_TYPE_CHANNEL
init|=
literal|10
block|,
DECL|enumerator|GIMP_DND_TYPE_LAYER_MASK
name|GIMP_DND_TYPE_LAYER_MASK
init|=
literal|11
block|,
DECL|enumerator|GIMP_DND_TYPE_COMPONENT
name|GIMP_DND_TYPE_COMPONENT
init|=
literal|12
block|,
DECL|enumerator|GIMP_DND_TYPE_VECTORS
name|GIMP_DND_TYPE_VECTORS
init|=
literal|13
block|,
DECL|enumerator|GIMP_DND_TYPE_BRUSH
name|GIMP_DND_TYPE_BRUSH
init|=
literal|14
block|,
DECL|enumerator|GIMP_DND_TYPE_PATTERN
name|GIMP_DND_TYPE_PATTERN
init|=
literal|15
block|,
DECL|enumerator|GIMP_DND_TYPE_GRADIENT
name|GIMP_DND_TYPE_GRADIENT
init|=
literal|16
block|,
DECL|enumerator|GIMP_DND_TYPE_PALETTE
name|GIMP_DND_TYPE_PALETTE
init|=
literal|17
block|,
DECL|enumerator|GIMP_DND_TYPE_FONT
name|GIMP_DND_TYPE_FONT
init|=
literal|18
block|,
DECL|enumerator|GIMP_DND_TYPE_BUFFER
name|GIMP_DND_TYPE_BUFFER
init|=
literal|19
block|,
DECL|enumerator|GIMP_DND_TYPE_IMAGEFILE
name|GIMP_DND_TYPE_IMAGEFILE
init|=
literal|20
block|,
DECL|enumerator|GIMP_DND_TYPE_TEMPLATE
name|GIMP_DND_TYPE_TEMPLATE
init|=
literal|21
block|,
DECL|enumerator|GIMP_DND_TYPE_TOOL
name|GIMP_DND_TYPE_TOOL
init|=
literal|22
block|,
DECL|enumerator|GIMP_DND_TYPE_DIALOG
name|GIMP_DND_TYPE_DIALOG
init|=
literal|23
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
DECL|enum|__anon28b0b9f51003
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
DECL|enum|__anon28b0b9f51103
block|{
DECL|enumerator|GIMP_CURSOR_NONE
name|GIMP_CURSOR_NONE
init|=
literal|1024
block|,
comment|/* (GDK_LAST_CURSOR + 2) yes, this is insane */
DECL|enumerator|GIMP_CURSOR_MOUSE
name|GIMP_CURSOR_MOUSE
block|,
DECL|enumerator|GIMP_CURSOR_CROSSHAIR
name|GIMP_CURSOR_CROSSHAIR
block|,
DECL|enumerator|GIMP_CURSOR_CROSSHAIR_SMALL
name|GIMP_CURSOR_CROSSHAIR_SMALL
block|,
DECL|enumerator|GIMP_CURSOR_BAD
name|GIMP_CURSOR_BAD
block|,
DECL|enumerator|GIMP_CURSOR_ZOOM
name|GIMP_CURSOR_ZOOM
block|,
DECL|enumerator|GIMP_CURSOR_COLOR_PICKER
name|GIMP_CURSOR_COLOR_PICKER
block|,
DECL|enumerator|GIMP_CURSOR_LAST
name|GIMP_CURSOR_LAST
DECL|typedef|GimpCursorType
block|}
name|GimpCursorType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28b0b9f51203
block|{
DECL|enumerator|GIMP_TOOL_CURSOR_NONE
name|GIMP_TOOL_CURSOR_NONE
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_RECT_SELECT
name|GIMP_TOOL_CURSOR_RECT_SELECT
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_ELLIPSE_SELECT
name|GIMP_TOOL_CURSOR_ELLIPSE_SELECT
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_FREE_SELECT
name|GIMP_TOOL_CURSOR_FREE_SELECT
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_FUZZY_SELECT
name|GIMP_TOOL_CURSOR_FUZZY_SELECT
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_PATHS
name|GIMP_TOOL_CURSOR_PATHS
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_ISCISSORS
name|GIMP_TOOL_CURSOR_ISCISSORS
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_MOVE
name|GIMP_TOOL_CURSOR_MOVE
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_ZOOM
name|GIMP_TOOL_CURSOR_ZOOM
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_CROP
name|GIMP_TOOL_CURSOR_CROP
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_RESIZE
name|GIMP_TOOL_CURSOR_RESIZE
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_ROTATE
name|GIMP_TOOL_CURSOR_ROTATE
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_SHEAR
name|GIMP_TOOL_CURSOR_SHEAR
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_PERSPECTIVE
name|GIMP_TOOL_CURSOR_PERSPECTIVE
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_FLIP_HORIZONTAL
name|GIMP_TOOL_CURSOR_FLIP_HORIZONTAL
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_FLIP_VERTICAL
name|GIMP_TOOL_CURSOR_FLIP_VERTICAL
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_TEXT
name|GIMP_TOOL_CURSOR_TEXT
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_COLOR_PICKER
name|GIMP_TOOL_CURSOR_COLOR_PICKER
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_BUCKET_FILL
name|GIMP_TOOL_CURSOR_BUCKET_FILL
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_BLEND
name|GIMP_TOOL_CURSOR_BLEND
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_PENCIL
name|GIMP_TOOL_CURSOR_PENCIL
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_PAINTBRUSH
name|GIMP_TOOL_CURSOR_PAINTBRUSH
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_AIRBRUSH
name|GIMP_TOOL_CURSOR_AIRBRUSH
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_INK
name|GIMP_TOOL_CURSOR_INK
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_CLONE
name|GIMP_TOOL_CURSOR_CLONE
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_ERASER
name|GIMP_TOOL_CURSOR_ERASER
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_SMUDGE
name|GIMP_TOOL_CURSOR_SMUDGE
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_BLUR
name|GIMP_TOOL_CURSOR_BLUR
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_DODGE
name|GIMP_TOOL_CURSOR_DODGE
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_BURN
name|GIMP_TOOL_CURSOR_BURN
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_MEASURE
name|GIMP_TOOL_CURSOR_MEASURE
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_HAND
name|GIMP_TOOL_CURSOR_HAND
block|,
DECL|enumerator|GIMP_TOOL_CURSOR_LAST
name|GIMP_TOOL_CURSOR_LAST
DECL|typedef|GimpToolCursorType
block|}
name|GimpToolCursorType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28b0b9f51303
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
DECL|enumerator|GIMP_CURSOR_MODIFIER_LAST
name|GIMP_CURSOR_MODIFIER_LAST
DECL|typedef|GimpCursorModifier
block|}
name|GimpCursorModifier
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28b0b9f51403
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

