begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpGuiConfig class  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
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
file|"gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|DEFAULT_GIMP_HELP_BROWSER
define|#
directive|define
name|DEFAULT_GIMP_HELP_BROWSER
value|GIMP_HELP_BROWSER_GIMP
end_define

begin_define
DECL|macro|DEFAULT_THEME
define|#
directive|define
name|DEFAULT_THEME
value|"Default"
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_define
DECL|macro|DEFAULT_WEB_BROWSER
define|#
directive|define
name|DEFAULT_WEB_BROWSER
value|"not used on Windows"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|DEFAULT_WEB_BROWSER
define|#
directive|define
name|DEFAULT_WEB_BROWSER
value|"mozilla-firefox %s"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_enum
enum|enum
DECL|enum|__anon2b3a91300103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_DEFAULT_THRESHOLD
name|PROP_DEFAULT_THRESHOLD
block|,
DECL|enumerator|PROP_MOVE_TOOL_CHANGES_ACTIVE
name|PROP_MOVE_TOOL_CHANGES_ACTIVE
block|,
DECL|enumerator|PROP_INFO_WINDOW_PER_DISPLAY
name|PROP_INFO_WINDOW_PER_DISPLAY
block|,
DECL|enumerator|PROP_TRUST_DIRTY_FLAG
name|PROP_TRUST_DIRTY_FLAG
block|,
DECL|enumerator|PROP_SAVE_DEVICE_STATUS
name|PROP_SAVE_DEVICE_STATUS
block|,
DECL|enumerator|PROP_SAVE_SESSION_INFO
name|PROP_SAVE_SESSION_INFO
block|,
DECL|enumerator|PROP_RESTORE_SESSION
name|PROP_RESTORE_SESSION
block|,
DECL|enumerator|PROP_SAVE_TOOL_OPTIONS
name|PROP_SAVE_TOOL_OPTIONS
block|,
DECL|enumerator|PROP_SHOW_TIPS
name|PROP_SHOW_TIPS
block|,
DECL|enumerator|PROP_SHOW_TOOL_TIPS
name|PROP_SHOW_TOOL_TIPS
block|,
DECL|enumerator|PROP_TEAROFF_MENUS
name|PROP_TEAROFF_MENUS
block|,
DECL|enumerator|PROP_CAN_CHANGE_ACCELS
name|PROP_CAN_CHANGE_ACCELS
block|,
DECL|enumerator|PROP_SAVE_ACCELS
name|PROP_SAVE_ACCELS
block|,
DECL|enumerator|PROP_RESTORE_ACCELS
name|PROP_RESTORE_ACCELS
block|,
DECL|enumerator|PROP_MENU_MNEMONICS
name|PROP_MENU_MNEMONICS
block|,
DECL|enumerator|PROP_LAST_OPENED_SIZE
name|PROP_LAST_OPENED_SIZE
block|,
DECL|enumerator|PROP_MAX_NEW_IMAGE_SIZE
name|PROP_MAX_NEW_IMAGE_SIZE
block|,
DECL|enumerator|PROP_TOOLBOX_COLOR_AREA
name|PROP_TOOLBOX_COLOR_AREA
block|,
DECL|enumerator|PROP_TOOLBOX_FOO_AREA
name|PROP_TOOLBOX_FOO_AREA
block|,
DECL|enumerator|PROP_TOOLBOX_IMAGE_AREA
name|PROP_TOOLBOX_IMAGE_AREA
block|,
DECL|enumerator|PROP_THEME_PATH
name|PROP_THEME_PATH
block|,
DECL|enumerator|PROP_THEME
name|PROP_THEME
block|,
DECL|enumerator|PROP_USE_HELP
name|PROP_USE_HELP
block|,
DECL|enumerator|PROP_SHOW_HELP_BUTTON
name|PROP_SHOW_HELP_BUTTON
block|,
DECL|enumerator|PROP_HELP_LOCALES
name|PROP_HELP_LOCALES
block|,
DECL|enumerator|PROP_HELP_BROWSER
name|PROP_HELP_BROWSER
block|,
DECL|enumerator|PROP_WEB_BROWSER
name|PROP_WEB_BROWSER
block|,
DECL|enumerator|PROP_TOOLBOX_WINDOW_HINT
name|PROP_TOOLBOX_WINDOW_HINT
block|,
DECL|enumerator|PROP_DOCK_WINDOW_HINT
name|PROP_DOCK_WINDOW_HINT
block|,
DECL|enumerator|PROP_TRANSIENT_DOCKS
name|PROP_TRANSIENT_DOCKS
block|,
DECL|enumerator|PROP_CURSOR_FORMAT
name|PROP_CURSOR_FORMAT
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_gui_config_finalize
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
name|gimp_gui_config_set_property
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
name|gimp_gui_config_get_property
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

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpGuiConfig
argument_list|,
name|gimp_gui_config
argument_list|,
name|GIMP_TYPE_DISPLAY_CONFIG
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_gui_config_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_gui_config_class_init (GimpGuiConfigClass * klass)
name|gimp_gui_config_class_init
parameter_list|(
name|GimpGuiConfigClass
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
name|gchar
modifier|*
name|path
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_gui_config_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_gui_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_gui_config_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_THRESHOLD
argument_list|,
literal|"default-threshold"
argument_list|,
name|DEFAULT_THRESHOLD_BLURB
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|,
literal|15
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_MOVE_TOOL_CHANGES_ACTIVE
argument_list|,
literal|"move-tool-changes-active"
argument_list|,
name|MOVE_TOOL_CHANGES_ACTIVE_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_INFO_WINDOW_PER_DISPLAY
argument_list|,
literal|"info-window-per-display"
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
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_TRUST_DIRTY_FLAG
argument_list|,
literal|"trust-dirty-flag"
argument_list|,
name|TRUST_DIRTY_FLAG_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SAVE_DEVICE_STATUS
argument_list|,
literal|"save-device-status"
argument_list|,
name|SAVE_DEVICE_STATUS_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SAVE_SESSION_INFO
argument_list|,
literal|"save-session-info"
argument_list|,
name|SAVE_SESSION_INFO_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_RESTORE_SESSION
argument_list|,
literal|"restore-session"
argument_list|,
name|RESTORE_SESSION_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SAVE_TOOL_OPTIONS
argument_list|,
literal|"save-tool-options"
argument_list|,
name|SAVE_TOOL_OPTIONS_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_TIPS
argument_list|,
literal|"show-tips"
argument_list|,
name|SHOW_TIPS_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_TOOL_TIPS
argument_list|,
literal|"show-tool-tips"
argument_list|,
name|SHOW_TOOL_TIPS_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_TEAROFF_MENUS
argument_list|,
literal|"tearoff-menus"
argument_list|,
name|TEAROFF_MENUS_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_CAN_CHANGE_ACCELS
argument_list|,
literal|"can-change-accels"
argument_list|,
name|CAN_CHANGE_ACCELS_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SAVE_ACCELS
argument_list|,
literal|"save-accels"
argument_list|,
name|SAVE_ACCELS_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_RESTORE_ACCELS
argument_list|,
literal|"restore-accels"
argument_list|,
name|RESTORE_ACCELS_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_MENU_MNEMONICS
argument_list|,
literal|"menu-mnemonics"
argument_list|,
name|MENU_MNEMONICS_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_RESTART
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_LAST_OPENED_SIZE
argument_list|,
literal|"last-opened-size"
argument_list|,
name|LAST_OPENED_SIZE_BLURB
argument_list|,
literal|0
argument_list|,
literal|1024
argument_list|,
literal|10
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_RESTART
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_MEMSIZE
argument_list|(
name|object_class
argument_list|,
name|PROP_MAX_NEW_IMAGE_SIZE
argument_list|,
literal|"max-new-image-size"
argument_list|,
name|MAX_NEW_IMAGE_SIZE_BLURB
argument_list|,
literal|0
argument_list|,
name|GIMP_MAX_MEMSIZE
argument_list|,
literal|1
operator|<<
literal|26
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_TOOLBOX_COLOR_AREA
argument_list|,
literal|"toolbox-color-area"
argument_list|,
name|TOOLBOX_COLOR_AREA_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_TOOLBOX_FOO_AREA
argument_list|,
literal|"toolbox-foo-area"
argument_list|,
name|TOOLBOX_FOO_AREA_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_TOOLBOX_IMAGE_AREA
argument_list|,
literal|"toolbox-image-area"
argument_list|,
name|TOOLBOX_IMAGE_AREA_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|path
operator|=
name|gimp_config_build_data_path
argument_list|(
literal|"themes"
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_THEME_PATH
argument_list|,
literal|"theme-path"
argument_list|,
name|THEME_PATH_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_DIR_LIST
argument_list|,
name|path
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_RESTART
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_THEME
argument_list|,
literal|"theme"
argument_list|,
name|THEME_BLURB
argument_list|,
name|DEFAULT_THEME
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_HELP
argument_list|,
literal|"use-help"
argument_list|,
name|USE_HELP_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_HELP_BUTTON
argument_list|,
literal|"show-help-button"
argument_list|,
name|SHOW_HELP_BUTTON_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_HELP_LOCALES
argument_list|,
literal|"help-locales"
argument_list|,
name|HELP_LOCALES_BLURB
argument_list|,
literal|""
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_HELP_BROWSER
argument_list|,
literal|"help-browser"
argument_list|,
name|HELP_BROWSER_BLURB
argument_list|,
name|GIMP_TYPE_HELP_BROWSER_TYPE
argument_list|,
name|DEFAULT_GIMP_HELP_BROWSER
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_WEB_BROWSER
argument_list|,
literal|"web-browser"
argument_list|,
name|WEB_BROWSER_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_FILE
argument_list|,
name|DEFAULT_WEB_BROWSER
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_TOOLBOX_WINDOW_HINT
argument_list|,
literal|"toolbox-window-hint"
argument_list|,
name|TOOLBOX_WINDOW_HINT_BLURB
argument_list|,
name|GIMP_TYPE_WINDOW_HINT
argument_list|,
name|GIMP_WINDOW_HINT_NORMAL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_RESTART
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_DOCK_WINDOW_HINT
argument_list|,
literal|"dock-window-hint"
argument_list|,
name|DOCK_WINDOW_HINT_BLURB
argument_list|,
name|GIMP_TYPE_WINDOW_HINT
argument_list|,
name|GIMP_WINDOW_HINT_NORMAL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_RESTART
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_TRANSIENT_DOCKS
argument_list|,
literal|"transient-docks"
argument_list|,
name|TRANSIENT_DOCKS_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_CURSOR_FORMAT
argument_list|,
literal|"cursor-format"
argument_list|,
name|CURSOR_FORMAT_BLURB
argument_list|,
name|GIMP_TYPE_CURSOR_FORMAT
argument_list|,
name|GIMP_CURSOR_FORMAT_PIXBUF
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gui_config_init (GimpGuiConfig * config)
name|gimp_gui_config_init
parameter_list|(
name|GimpGuiConfig
modifier|*
name|config
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gui_config_finalize (GObject * object)
name|gimp_gui_config_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|gui_config
init|=
name|GIMP_GUI_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|gui_config
operator|->
name|theme_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gui_config
operator|->
name|theme
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gui_config
operator|->
name|help_locales
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gui_config
operator|->
name|web_browser
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
DECL|function|gimp_gui_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_gui_config_set_property
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
name|GimpGuiConfig
modifier|*
name|gui_config
init|=
name|GIMP_GUI_CONFIG
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
name|PROP_DEFAULT_THRESHOLD
case|:
name|gui_config
operator|->
name|default_threshold
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MOVE_TOOL_CHANGES_ACTIVE
case|:
name|gui_config
operator|->
name|move_tool_changes_active
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INFO_WINDOW_PER_DISPLAY
case|:
name|gui_config
operator|->
name|info_window_per_display
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TRUST_DIRTY_FLAG
case|:
name|gui_config
operator|->
name|trust_dirty_flag
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAVE_DEVICE_STATUS
case|:
name|gui_config
operator|->
name|save_device_status
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAVE_SESSION_INFO
case|:
name|gui_config
operator|->
name|save_session_info
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RESTORE_SESSION
case|:
name|gui_config
operator|->
name|restore_session
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAVE_TOOL_OPTIONS
case|:
name|gui_config
operator|->
name|save_tool_options
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_TIPS
case|:
name|gui_config
operator|->
name|show_tips
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_TOOL_TIPS
case|:
name|gui_config
operator|->
name|show_tool_tips
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TEAROFF_MENUS
case|:
name|gui_config
operator|->
name|tearoff_menus
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CAN_CHANGE_ACCELS
case|:
name|gui_config
operator|->
name|can_change_accels
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAVE_ACCELS
case|:
name|gui_config
operator|->
name|save_accels
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RESTORE_ACCELS
case|:
name|gui_config
operator|->
name|restore_accels
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MENU_MNEMONICS
case|:
name|gui_config
operator|->
name|menu_mnemonics
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LAST_OPENED_SIZE
case|:
name|gui_config
operator|->
name|last_opened_size
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MAX_NEW_IMAGE_SIZE
case|:
name|gui_config
operator|->
name|max_new_image_size
operator|=
name|g_value_get_uint64
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TOOLBOX_COLOR_AREA
case|:
name|gui_config
operator|->
name|toolbox_color_area
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TOOLBOX_FOO_AREA
case|:
name|gui_config
operator|->
name|toolbox_foo_area
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TOOLBOX_IMAGE_AREA
case|:
name|gui_config
operator|->
name|toolbox_image_area
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_THEME_PATH
case|:
name|g_free
argument_list|(
name|gui_config
operator|->
name|theme_path
argument_list|)
expr_stmt|;
name|gui_config
operator|->
name|theme_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_THEME
case|:
name|g_free
argument_list|(
name|gui_config
operator|->
name|theme
argument_list|)
expr_stmt|;
name|gui_config
operator|->
name|theme
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_HELP
case|:
name|gui_config
operator|->
name|use_help
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_HELP_BUTTON
case|:
name|gui_config
operator|->
name|show_help_button
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HELP_LOCALES
case|:
name|g_free
argument_list|(
name|gui_config
operator|->
name|help_locales
argument_list|)
expr_stmt|;
name|gui_config
operator|->
name|help_locales
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HELP_BROWSER
case|:
name|gui_config
operator|->
name|help_browser
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WEB_BROWSER
case|:
name|g_free
argument_list|(
name|gui_config
operator|->
name|web_browser
argument_list|)
expr_stmt|;
name|gui_config
operator|->
name|web_browser
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TOOLBOX_WINDOW_HINT
case|:
name|gui_config
operator|->
name|toolbox_window_hint
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DOCK_WINDOW_HINT
case|:
name|gui_config
operator|->
name|dock_window_hint
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TRANSIENT_DOCKS
case|:
name|gui_config
operator|->
name|transient_docks
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CURSOR_FORMAT
case|:
name|gui_config
operator|->
name|cursor_format
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
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
DECL|function|gimp_gui_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_gui_config_get_property
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
name|GimpGuiConfig
modifier|*
name|gui_config
init|=
name|GIMP_GUI_CONFIG
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
name|PROP_DEFAULT_THRESHOLD
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|default_threshold
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MOVE_TOOL_CHANGES_ACTIVE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|move_tool_changes_active
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INFO_WINDOW_PER_DISPLAY
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|info_window_per_display
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TRUST_DIRTY_FLAG
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|trust_dirty_flag
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAVE_DEVICE_STATUS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|save_device_status
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAVE_SESSION_INFO
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|save_session_info
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RESTORE_SESSION
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|restore_session
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAVE_TOOL_OPTIONS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|save_tool_options
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_TIPS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|show_tips
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_TOOL_TIPS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|show_tool_tips
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TEAROFF_MENUS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|tearoff_menus
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CAN_CHANGE_ACCELS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|can_change_accels
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAVE_ACCELS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|save_accels
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RESTORE_ACCELS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|restore_accels
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MENU_MNEMONICS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|menu_mnemonics
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LAST_OPENED_SIZE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|last_opened_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MAX_NEW_IMAGE_SIZE
case|:
name|g_value_set_uint64
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|max_new_image_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TOOLBOX_COLOR_AREA
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|toolbox_color_area
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TOOLBOX_FOO_AREA
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|toolbox_foo_area
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TOOLBOX_IMAGE_AREA
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|toolbox_image_area
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_THEME_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|theme_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_THEME
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|theme
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_HELP
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|use_help
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_HELP_BUTTON
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|show_help_button
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HELP_LOCALES
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|help_locales
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HELP_BROWSER
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|help_browser
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WEB_BROWSER
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|web_browser
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TOOLBOX_WINDOW_HINT
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|toolbox_window_hint
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DOCK_WINDOW_HINT
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|dock_window_hint
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TRANSIENT_DOCKS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|transient_docks
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CURSOR_FORMAT
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|cursor_format
argument_list|)
expr_stmt|;
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

end_unit

