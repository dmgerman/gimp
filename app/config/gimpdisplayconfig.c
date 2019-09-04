begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpDisplayConfig class  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"config-types.h"
end_include

begin_include
include|#
directive|include
file|"gimprc-blurbs.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|DEFAULT_ACTIVATE_ON_FOCUS
define|#
directive|define
name|DEFAULT_ACTIVATE_ON_FOCUS
value|TRUE
end_define

begin_define
DECL|macro|DEFAULT_MONITOR_RESOLUTION
define|#
directive|define
name|DEFAULT_MONITOR_RESOLUTION
value|96.0
end_define

begin_define
DECL|macro|DEFAULT_MARCHING_ANTS_SPEED
define|#
directive|define
name|DEFAULT_MARCHING_ANTS_SPEED
value|200
end_define

begin_define
DECL|macro|DEFAULT_USE_EVENT_HISTORY
define|#
directive|define
name|DEFAULT_USE_EVENT_HISTORY
value|FALSE
end_define

begin_enum
enum|enum
DECL|enum|__anon2b31156b0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TRANSPARENCY_SIZE
name|PROP_TRANSPARENCY_SIZE
block|,
DECL|enumerator|PROP_TRANSPARENCY_TYPE
name|PROP_TRANSPARENCY_TYPE
block|,
DECL|enumerator|PROP_SNAP_DISTANCE
name|PROP_SNAP_DISTANCE
block|,
DECL|enumerator|PROP_MARCHING_ANTS_SPEED
name|PROP_MARCHING_ANTS_SPEED
block|,
DECL|enumerator|PROP_RESIZE_WINDOWS_ON_ZOOM
name|PROP_RESIZE_WINDOWS_ON_ZOOM
block|,
DECL|enumerator|PROP_RESIZE_WINDOWS_ON_RESIZE
name|PROP_RESIZE_WINDOWS_ON_RESIZE
block|,
DECL|enumerator|PROP_DEFAULT_SHOW_ALL
name|PROP_DEFAULT_SHOW_ALL
block|,
DECL|enumerator|PROP_DEFAULT_DOT_FOR_DOT
name|PROP_DEFAULT_DOT_FOR_DOT
block|,
DECL|enumerator|PROP_INITIAL_ZOOM_TO_FIT
name|PROP_INITIAL_ZOOM_TO_FIT
block|,
DECL|enumerator|PROP_CURSOR_MODE
name|PROP_CURSOR_MODE
block|,
DECL|enumerator|PROP_CURSOR_UPDATING
name|PROP_CURSOR_UPDATING
block|,
DECL|enumerator|PROP_SHOW_BRUSH_OUTLINE
name|PROP_SHOW_BRUSH_OUTLINE
block|,
DECL|enumerator|PROP_SHOW_PAINT_TOOL_CURSOR
name|PROP_SHOW_PAINT_TOOL_CURSOR
block|,
DECL|enumerator|PROP_IMAGE_TITLE_FORMAT
name|PROP_IMAGE_TITLE_FORMAT
block|,
DECL|enumerator|PROP_IMAGE_STATUS_FORMAT
name|PROP_IMAGE_STATUS_FORMAT
block|,
DECL|enumerator|PROP_MONITOR_XRESOLUTION
name|PROP_MONITOR_XRESOLUTION
block|,
DECL|enumerator|PROP_MONITOR_YRESOLUTION
name|PROP_MONITOR_YRESOLUTION
block|,
DECL|enumerator|PROP_MONITOR_RES_FROM_GDK
name|PROP_MONITOR_RES_FROM_GDK
block|,
DECL|enumerator|PROP_NAV_PREVIEW_SIZE
name|PROP_NAV_PREVIEW_SIZE
block|,
DECL|enumerator|PROP_DEFAULT_VIEW
name|PROP_DEFAULT_VIEW
block|,
DECL|enumerator|PROP_DEFAULT_FULLSCREEN_VIEW
name|PROP_DEFAULT_FULLSCREEN_VIEW
block|,
DECL|enumerator|PROP_ACTIVATE_ON_FOCUS
name|PROP_ACTIVATE_ON_FOCUS
block|,
DECL|enumerator|PROP_SPACE_BAR_ACTION
name|PROP_SPACE_BAR_ACTION
block|,
DECL|enumerator|PROP_ZOOM_QUALITY
name|PROP_ZOOM_QUALITY
block|,
DECL|enumerator|PROP_USE_EVENT_HISTORY
name|PROP_USE_EVENT_HISTORY
block|,
comment|/* ignored, only for backward compatibility: */
DECL|enumerator|PROP_DEFAULT_SNAP_TO_GUIDES
name|PROP_DEFAULT_SNAP_TO_GUIDES
block|,
DECL|enumerator|PROP_DEFAULT_SNAP_TO_GRID
name|PROP_DEFAULT_SNAP_TO_GRID
block|,
DECL|enumerator|PROP_DEFAULT_SNAP_TO_CANVAS
name|PROP_DEFAULT_SNAP_TO_CANVAS
block|,
DECL|enumerator|PROP_DEFAULT_SNAP_TO_PATH
name|PROP_DEFAULT_SNAP_TO_PATH
block|,
DECL|enumerator|PROP_CONFIRM_ON_CLOSE
name|PROP_CONFIRM_ON_CLOSE
block|,
DECL|enumerator|PROP_XOR_COLOR
name|PROP_XOR_COLOR
block|,
DECL|enumerator|PROP_PERFECT_MOUSE
name|PROP_PERFECT_MOUSE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_display_config_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_config_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_config_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_config_view_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_config_fullscreen_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDisplayConfig,gimp_display_config,GIMP_TYPE_CORE_CONFIG)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDisplayConfig
argument_list|,
argument|gimp_display_config
argument_list|,
argument|GIMP_TYPE_CORE_CONFIG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_display_config_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_display_config_class_init
parameter_list|(
name|GimpDisplayConfigClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpRGB
name|color
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_display_config_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_display_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_display_config_get_property
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_TRANSPARENCY_SIZE
argument_list|,
literal|"transparency-size"
argument_list|,
literal|"Transparency size"
argument_list|,
name|TRANSPARENCY_SIZE_BLURB
argument_list|,
name|GIMP_TYPE_CHECK_SIZE
argument_list|,
name|GIMP_CHECK_SIZE_MEDIUM_CHECKS
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_TRANSPARENCY_TYPE
argument_list|,
literal|"transparency-type"
argument_list|,
literal|"Transparency type"
argument_list|,
name|TRANSPARENCY_TYPE_BLURB
argument_list|,
name|GIMP_TYPE_CHECK_TYPE
argument_list|,
name|GIMP_CHECK_TYPE_GRAY_CHECKS
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_SNAP_DISTANCE
argument_list|,
literal|"snap-distance"
argument_list|,
literal|"Snap distance"
argument_list|,
name|DEFAULT_SNAP_DISTANCE_BLURB
argument_list|,
literal|1
argument_list|,
literal|255
argument_list|,
literal|8
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_MARCHING_ANTS_SPEED
argument_list|,
literal|"marching-ants-speed"
argument_list|,
literal|"Marching ants speed"
argument_list|,
name|MARCHING_ANTS_SPEED_BLURB
argument_list|,
literal|10
argument_list|,
literal|10000
argument_list|,
name|DEFAULT_MARCHING_ANTS_SPEED
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_RESIZE_WINDOWS_ON_ZOOM
argument_list|,
literal|"resize-windows-on-zoom"
argument_list|,
literal|"Resize windows on zoom"
argument_list|,
name|RESIZE_WINDOWS_ON_ZOOM_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_RESIZE_WINDOWS_ON_RESIZE
argument_list|,
literal|"resize-windows-on-resize"
argument_list|,
literal|"Resize windows on resize"
argument_list|,
name|RESIZE_WINDOWS_ON_RESIZE_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_SHOW_ALL
argument_list|,
literal|"default-show-all"
argument_list|,
literal|"Default show-all"
argument_list|,
name|DEFAULT_SHOW_ALL_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_DOT_FOR_DOT
argument_list|,
literal|"default-dot-for-dot"
argument_list|,
literal|"Default dot-for-dot"
argument_list|,
name|DEFAULT_DOT_FOR_DOT_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_INITIAL_ZOOM_TO_FIT
argument_list|,
literal|"initial-zoom-to-fit"
argument_list|,
literal|"Initial zoom-to-fit"
argument_list|,
name|INITIAL_ZOOM_TO_FIT_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_CURSOR_MODE
argument_list|,
literal|"cursor-mode"
argument_list|,
literal|"Cursor mode"
argument_list|,
name|CURSOR_MODE_BLURB
argument_list|,
name|GIMP_TYPE_CURSOR_MODE
argument_list|,
name|GIMP_CURSOR_MODE_TOOL_CROSSHAIR
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_CURSOR_UPDATING
argument_list|,
literal|"cursor-updating"
argument_list|,
literal|"Cursor updating"
argument_list|,
name|CURSOR_UPDATING_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_BRUSH_OUTLINE
argument_list|,
literal|"show-brush-outline"
argument_list|,
literal|"Show brush outline"
argument_list|,
name|SHOW_BRUSH_OUTLINE_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_PAINT_TOOL_CURSOR
argument_list|,
literal|"show-paint-tool-cursor"
argument_list|,
literal|"Show paint tool cursor"
argument_list|,
name|SHOW_PAINT_TOOL_CURSOR_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_IMAGE_TITLE_FORMAT
argument_list|,
literal|"image-title-format"
argument_list|,
literal|"Image title format"
argument_list|,
name|IMAGE_TITLE_FORMAT_BLURB
argument_list|,
name|GIMP_CONFIG_DEFAULT_IMAGE_TITLE_FORMAT
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_IMAGE_STATUS_FORMAT
argument_list|,
literal|"image-status-format"
argument_list|,
literal|"Image statusbar format"
argument_list|,
name|IMAGE_STATUS_FORMAT_BLURB
argument_list|,
name|GIMP_CONFIG_DEFAULT_IMAGE_STATUS_FORMAT
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_RESOLUTION
argument_list|(
name|object_class
argument_list|,
name|PROP_MONITOR_XRESOLUTION
argument_list|,
literal|"monitor-xresolution"
argument_list|,
literal|"Monitor resolution X"
argument_list|,
name|MONITOR_XRESOLUTION_BLURB
argument_list|,
name|DEFAULT_MONITOR_RESOLUTION
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_RESOLUTION
argument_list|(
name|object_class
argument_list|,
name|PROP_MONITOR_YRESOLUTION
argument_list|,
literal|"monitor-yresolution"
argument_list|,
literal|"Monitor resolution Y"
argument_list|,
name|MONITOR_YRESOLUTION_BLURB
argument_list|,
name|DEFAULT_MONITOR_RESOLUTION
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_MONITOR_RES_FROM_GDK
argument_list|,
literal|"monitor-resolution-from-windowing-system"
argument_list|,
literal|"Monitor resolution from windowing system"
argument_list|,
name|MONITOR_RES_FROM_GDK_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_NAV_PREVIEW_SIZE
argument_list|,
literal|"navigation-preview-size"
argument_list|,
literal|"Navigation preview size"
argument_list|,
name|NAVIGATION_PREVIEW_SIZE_BLURB
argument_list|,
name|GIMP_TYPE_VIEW_SIZE
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_VIEW
argument_list|,
literal|"default-view"
argument_list|,
literal|"Default view options"
argument_list|,
name|DEFAULT_VIEW_BLURB
argument_list|,
name|GIMP_TYPE_DISPLAY_OPTIONS
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_FULLSCREEN_VIEW
argument_list|,
literal|"default-fullscreen-view"
argument_list|,
literal|"Default fullscreen view options"
argument_list|,
name|DEFAULT_FULLSCREEN_VIEW_BLURB
argument_list|,
name|GIMP_TYPE_DISPLAY_OPTIONS
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_ACTIVATE_ON_FOCUS
argument_list|,
literal|"activate-on-focus"
argument_list|,
literal|"Activate on focus"
argument_list|,
name|ACTIVATE_ON_FOCUS_BLURB
argument_list|,
name|DEFAULT_ACTIVATE_ON_FOCUS
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_SPACE_BAR_ACTION
argument_list|,
literal|"space-bar-action"
argument_list|,
literal|"Space bar action"
argument_list|,
name|SPACE_BAR_ACTION_BLURB
argument_list|,
name|GIMP_TYPE_SPACE_BAR_ACTION
argument_list|,
name|GIMP_SPACE_BAR_ACTION_PAN
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_ZOOM_QUALITY
argument_list|,
literal|"zoom-quality"
argument_list|,
literal|"Zoom quality"
argument_list|,
name|ZOOM_QUALITY_BLURB
argument_list|,
name|GIMP_TYPE_ZOOM_QUALITY
argument_list|,
name|GIMP_ZOOM_QUALITY_HIGH
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_EVENT_HISTORY
argument_list|,
literal|"use-event-history"
argument_list|,
literal|"Use event history"
argument_list|,
name|DEFAULT_USE_EVENT_HISTORY_BLURB
argument_list|,
name|DEFAULT_USE_EVENT_HISTORY
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
comment|/*  only for backward compatibility:  */
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_SNAP_TO_GUIDES
argument_list|,
literal|"default-snap-to-guides"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_IGNORE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_SNAP_TO_GRID
argument_list|,
literal|"default-snap-to-grid"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_IGNORE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_SNAP_TO_CANVAS
argument_list|,
literal|"default-snap-to-canvas"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_IGNORE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_SNAP_TO_PATH
argument_list|,
literal|"default-snap-to-path"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_IGNORE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_CONFIRM_ON_CLOSE
argument_list|,
literal|"confirm-on-close"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_IGNORE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_RGB
argument_list|(
name|object_class
argument_list|,
name|PROP_XOR_COLOR
argument_list|,
literal|"xor-color"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
operator|&
name|color
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_IGNORE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_PERFECT_MOUSE
argument_list|,
literal|"perfect-mouse"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_IGNORE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_config_init (GimpDisplayConfig * config)
name|gimp_display_config_init
parameter_list|(
name|GimpDisplayConfig
modifier|*
name|config
parameter_list|)
block|{
name|config
operator|->
name|default_view
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DISPLAY_OPTIONS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|config
operator|->
name|default_view
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_config_view_notify
argument_list|)
argument_list|,
name|config
argument_list|)
expr_stmt|;
name|config
operator|->
name|default_fullscreen_view
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DISPLAY_OPTIONS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|config
operator|->
name|default_fullscreen_view
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_config_fullscreen_notify
argument_list|)
argument_list|,
name|config
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_config_finalize (GObject * object)
name|gimp_display_config_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDisplayConfig
modifier|*
name|display_config
init|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|display_config
operator|->
name|image_title_format
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|display_config
operator|->
name|image_status_format
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|display_config
operator|->
name|default_view
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|display_config
operator|->
name|default_fullscreen_view
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_display_config_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpDisplayConfig
modifier|*
name|display_config
init|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_TRANSPARENCY_SIZE
case|:
name|display_config
operator|->
name|transparency_size
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TRANSPARENCY_TYPE
case|:
name|display_config
operator|->
name|transparency_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SNAP_DISTANCE
case|:
name|display_config
operator|->
name|snap_distance
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MARCHING_ANTS_SPEED
case|:
name|display_config
operator|->
name|marching_ants_speed
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RESIZE_WINDOWS_ON_ZOOM
case|:
name|display_config
operator|->
name|resize_windows_on_zoom
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RESIZE_WINDOWS_ON_RESIZE
case|:
name|display_config
operator|->
name|resize_windows_on_resize
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_SHOW_ALL
case|:
name|display_config
operator|->
name|default_show_all
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_DOT_FOR_DOT
case|:
name|display_config
operator|->
name|default_dot_for_dot
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INITIAL_ZOOM_TO_FIT
case|:
name|display_config
operator|->
name|initial_zoom_to_fit
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CURSOR_MODE
case|:
name|display_config
operator|->
name|cursor_mode
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CURSOR_UPDATING
case|:
name|display_config
operator|->
name|cursor_updating
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_BRUSH_OUTLINE
case|:
name|display_config
operator|->
name|show_brush_outline
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_PAINT_TOOL_CURSOR
case|:
name|display_config
operator|->
name|show_paint_tool_cursor
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_IMAGE_TITLE_FORMAT
case|:
name|g_free
argument_list|(
name|display_config
operator|->
name|image_title_format
argument_list|)
expr_stmt|;
name|display_config
operator|->
name|image_title_format
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_IMAGE_STATUS_FORMAT
case|:
name|g_free
argument_list|(
name|display_config
operator|->
name|image_status_format
argument_list|)
expr_stmt|;
name|display_config
operator|->
name|image_status_format
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MONITOR_XRESOLUTION
case|:
name|display_config
operator|->
name|monitor_xres
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MONITOR_YRESOLUTION
case|:
name|display_config
operator|->
name|monitor_yres
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MONITOR_RES_FROM_GDK
case|:
name|display_config
operator|->
name|monitor_res_from_gdk
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_NAV_PREVIEW_SIZE
case|:
name|display_config
operator|->
name|nav_preview_size
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_VIEW
case|:
if|if
condition|(
name|g_value_get_object
argument_list|(
name|value
argument_list|)
condition|)
name|gimp_config_sync
argument_list|(
name|g_value_get_object
argument_list|(
name|value
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|display_config
operator|->
name|default_view
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_FULLSCREEN_VIEW
case|:
if|if
condition|(
name|g_value_get_object
argument_list|(
name|value
argument_list|)
condition|)
name|gimp_config_sync
argument_list|(
name|g_value_get_object
argument_list|(
name|value
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|display_config
operator|->
name|default_fullscreen_view
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ACTIVATE_ON_FOCUS
case|:
name|display_config
operator|->
name|activate_on_focus
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SPACE_BAR_ACTION
case|:
name|display_config
operator|->
name|space_bar_action
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ZOOM_QUALITY
case|:
name|display_config
operator|->
name|zoom_quality
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_EVENT_HISTORY
case|:
name|display_config
operator|->
name|use_event_history
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_SNAP_TO_GUIDES
case|:
case|case
name|PROP_DEFAULT_SNAP_TO_GRID
case|:
case|case
name|PROP_DEFAULT_SNAP_TO_CANVAS
case|:
case|case
name|PROP_DEFAULT_SNAP_TO_PATH
case|:
case|case
name|PROP_CONFIRM_ON_CLOSE
case|:
case|case
name|PROP_XOR_COLOR
case|:
case|case
name|PROP_PERFECT_MOUSE
case|:
comment|/* ignored */
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_display_config_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpDisplayConfig
modifier|*
name|display_config
init|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_TRANSPARENCY_SIZE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|transparency_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TRANSPARENCY_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|transparency_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SNAP_DISTANCE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|snap_distance
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MARCHING_ANTS_SPEED
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|marching_ants_speed
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RESIZE_WINDOWS_ON_ZOOM
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|resize_windows_on_zoom
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RESIZE_WINDOWS_ON_RESIZE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|resize_windows_on_resize
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_SHOW_ALL
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|default_show_all
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_DOT_FOR_DOT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|default_dot_for_dot
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INITIAL_ZOOM_TO_FIT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|initial_zoom_to_fit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CURSOR_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|cursor_mode
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CURSOR_UPDATING
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|cursor_updating
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_BRUSH_OUTLINE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|show_brush_outline
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_PAINT_TOOL_CURSOR
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|show_paint_tool_cursor
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_IMAGE_TITLE_FORMAT
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|image_title_format
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_IMAGE_STATUS_FORMAT
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|image_status_format
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MONITOR_XRESOLUTION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|monitor_xres
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MONITOR_YRESOLUTION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|monitor_yres
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MONITOR_RES_FROM_GDK
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|monitor_res_from_gdk
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_NAV_PREVIEW_SIZE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|nav_preview_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_VIEW
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|default_view
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_FULLSCREEN_VIEW
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|default_fullscreen_view
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ACTIVATE_ON_FOCUS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|activate_on_focus
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SPACE_BAR_ACTION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|space_bar_action
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ZOOM_QUALITY
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|zoom_quality
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_EVENT_HISTORY
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|use_event_history
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_SNAP_TO_GUIDES
case|:
case|case
name|PROP_DEFAULT_SNAP_TO_GRID
case|:
case|case
name|PROP_DEFAULT_SNAP_TO_CANVAS
case|:
case|case
name|PROP_DEFAULT_SNAP_TO_PATH
case|:
case|case
name|PROP_CONFIRM_ON_CLOSE
case|:
case|case
name|PROP_XOR_COLOR
case|:
case|case
name|PROP_PERFECT_MOUSE
case|:
comment|/* ignored */
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_config_view_notify (GObject * object,GParamSpec * pspec,gpointer data)
name|gimp_display_config_view_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
literal|"default-view"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_config_fullscreen_notify (GObject * object,GParamSpec * pspec,gpointer data)
name|gimp_display_config_fullscreen_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
literal|"default-fullscreen-view"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

