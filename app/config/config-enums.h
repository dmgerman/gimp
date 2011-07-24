begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CONFIG_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__CONFIG_ENUMS_H__
define|#
directive|define
name|__CONFIG_ENUMS_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_CURSOR_MODE
define|#
directive|define
name|GIMP_TYPE_CURSOR_MODE
value|(gimp_cursor_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_cursor_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29d6aef90103
block|{
DECL|enumerator|GIMP_CURSOR_MODE_TOOL_ICON
name|GIMP_CURSOR_MODE_TOOL_ICON
block|,
comment|/*< desc="Tool icon">*/
DECL|enumerator|GIMP_CURSOR_MODE_TOOL_CROSSHAIR
name|GIMP_CURSOR_MODE_TOOL_CROSSHAIR
block|,
comment|/*< desc="Tool icon with crosshair">*/
DECL|enumerator|GIMP_CURSOR_MODE_CROSSHAIR
name|GIMP_CURSOR_MODE_CROSSHAIR
comment|/*< desc="Crosshair only">*/
DECL|typedef|GimpCursorMode
block|}
name|GimpCursorMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CANVAS_PADDING_MODE
define|#
directive|define
name|GIMP_TYPE_CANVAS_PADDING_MODE
value|(gimp_canvas_padding_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_canvas_padding_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29d6aef90203
block|{
DECL|enumerator|GIMP_CANVAS_PADDING_MODE_DEFAULT
name|GIMP_CANVAS_PADDING_MODE_DEFAULT
block|,
comment|/*< desc="From theme">*/
DECL|enumerator|GIMP_CANVAS_PADDING_MODE_LIGHT_CHECK
name|GIMP_CANVAS_PADDING_MODE_LIGHT_CHECK
block|,
comment|/*< desc="Light check color">*/
DECL|enumerator|GIMP_CANVAS_PADDING_MODE_DARK_CHECK
name|GIMP_CANVAS_PADDING_MODE_DARK_CHECK
block|,
comment|/*< desc="Dark check color">*/
DECL|enumerator|GIMP_CANVAS_PADDING_MODE_CUSTOM
name|GIMP_CANVAS_PADDING_MODE_CUSTOM
block|,
comment|/*< desc="Custom color">*/
DECL|enumerator|GIMP_CANVAS_PADDING_MODE_RESET
name|GIMP_CANVAS_PADDING_MODE_RESET
init|=
operator|-
literal|1
comment|/*< skip>*/
DECL|typedef|GimpCanvasPaddingMode
block|}
name|GimpCanvasPaddingMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_SPACE_BAR_ACTION
define|#
directive|define
name|GIMP_TYPE_SPACE_BAR_ACTION
value|(gimp_space_bar_action_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_space_bar_action_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29d6aef90303
block|{
DECL|enumerator|GIMP_SPACE_BAR_ACTION_NONE
name|GIMP_SPACE_BAR_ACTION_NONE
block|,
comment|/*< desc="No action">*/
DECL|enumerator|GIMP_SPACE_BAR_ACTION_PAN
name|GIMP_SPACE_BAR_ACTION_PAN
block|,
comment|/*< desc="Pan view">*/
DECL|enumerator|GIMP_SPACE_BAR_ACTION_MOVE
name|GIMP_SPACE_BAR_ACTION_MOVE
comment|/*< desc="Switch to Move tool">*/
DECL|typedef|GimpSpaceBarAction
block|}
name|GimpSpaceBarAction
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ZOOM_QUALITY
define|#
directive|define
name|GIMP_TYPE_ZOOM_QUALITY
value|(gimp_zoom_quality_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_zoom_quality_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29d6aef90403
block|{
DECL|enumerator|GIMP_ZOOM_QUALITY_LOW
name|GIMP_ZOOM_QUALITY_LOW
block|,
comment|/*< desc="Low">*/
DECL|enumerator|GIMP_ZOOM_QUALITY_HIGH
name|GIMP_ZOOM_QUALITY_HIGH
comment|/*< desc="High">*/
DECL|typedef|GimpZoomQuality
block|}
name|GimpZoomQuality
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
DECL|enum|__anon29d6aef90503
block|{
DECL|enumerator|GIMP_HELP_BROWSER_GIMP
name|GIMP_HELP_BROWSER_GIMP
block|,
comment|/*< desc="GIMP help browser">*/
DECL|enumerator|GIMP_HELP_BROWSER_WEB_BROWSER
name|GIMP_HELP_BROWSER_WEB_BROWSER
comment|/*< desc="Web browser">*/
DECL|typedef|GimpHelpBrowserType
block|}
name|GimpHelpBrowserType
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
DECL|enum|__anon29d6aef90603
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
DECL|enum|__anon29d6aef90703
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
DECL|macro|GIMP_TYPE_HANDEDNESS
define|#
directive|define
name|GIMP_TYPE_HANDEDNESS
value|(gimp_handedness_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_handedness_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29d6aef90803
block|{
DECL|enumerator|GIMP_HANDEDNESS_LEFT
name|GIMP_HANDEDNESS_LEFT
block|,
comment|/*< desc="Left-handed">*/
DECL|enumerator|GIMP_HANDEDNESS_RIGHT
name|GIMP_HANDEDNESS_RIGHT
comment|/*< desc="Right-handed">*/
DECL|typedef|GimpHandedness
block|}
name|GimpHandedness
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __CONFIG_ENUMS_H__ */
end_comment

end_unit

