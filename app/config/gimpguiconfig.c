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
file|"config-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-utils.h"
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

begin_function_decl
specifier|static
name|void
name|gimp_gui_config_class_init
parameter_list|(
name|GimpGuiConfigClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

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
DECL|macro|DEFAULT_GIMP_HELP_BROWSER
define|#
directive|define
name|DEFAULT_GIMP_HELP_BROWSER
value|GIMP_HELP_BROWSER_WEBBROWSER
end_define

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
DECL|macro|DEFAULT_GIMP_HELP_BROWSER
define|#
directive|define
name|DEFAULT_GIMP_HELP_BROWSER
value|GIMP_HELP_BROWSER_GIMP
end_define

begin_define
DECL|macro|DEFAULT_WEB_BROWSER
define|#
directive|define
name|DEFAULT_WEB_BROWSER
value|"mozilla \"%s\""
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_enum
enum|enum
DECL|enum|__anon29255d920103
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
DECL|enumerator|PROP_DEFAULT_THRESHOLD
name|PROP_DEFAULT_THRESHOLD
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
DECL|enumerator|PROP_LAST_OPENED_SIZE
name|PROP_LAST_OPENED_SIZE
block|,
DECL|enumerator|PROP_MAX_NEW_IMAGE_SIZE
name|PROP_MAX_NEW_IMAGE_SIZE
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
DECL|enumerator|PROP_HELP_BROWSER
name|PROP_HELP_BROWSER
block|,
DECL|enumerator|PROP_WEB_BROWSER
name|PROP_WEB_BROWSER
block|}
enum|;
end_enum

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_gui_config_get_type (void)
name|gimp_gui_config_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|config_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|config_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|config_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpGuiConfigClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init      */
name|NULL
block|,
comment|/* base_finalize  */
operator|(
name|GClassInitFunc
operator|)
name|gimp_gui_config_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpGuiConfig
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
name|config_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DISPLAY_CONFIG
argument_list|,
literal|"GimpGuiConfig"
argument_list|,
operator|&
name|config_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|config_type
return|;
block|}
end_function

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
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_TRANSPARENCY_SIZE
argument_list|,
literal|"transparency-size"
argument_list|,
name|TRANSPARENCY_SIZE_BLURB
argument_list|,
name|GIMP_TYPE_CHECK_SIZE
argument_list|,
name|GIMP_MEDIUM_CHECKS
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_TRANSPARENCY_TYPE
argument_list|,
literal|"transparency-type"
argument_list|,
name|TRANSPARENCY_TYPE_BLURB
argument_list|,
name|GIMP_TYPE_CHECK_TYPE
argument_list|,
name|GIMP_GRAY_CHECKS
argument_list|,
literal|0
argument_list|)
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
literal|0
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
name|INFO_WINDOW_PER_DISPLAY_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_RESTART
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
literal|0
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
literal|0
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
literal|0
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
literal|0
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
literal|0
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
literal|0
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
name|GIMP_PARAM_RESTART
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
literal|0
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
literal|0
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
literal|0
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
name|GIMP_PARAM_RESTART
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
name|G_MAXULONG
argument_list|,
literal|1
operator|<<
literal|26
argument_list|,
literal|0
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
name|GIMP_PARAM_PATH_DIR_LIST
argument_list|,
name|gimp_config_build_data_path
argument_list|(
literal|"themes"
argument_list|)
argument_list|,
name|GIMP_PARAM_RESTART
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
literal|0
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
literal|0
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
literal|0
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
name|GIMP_PARAM_PATH_FILE
argument_list|,
name|DEFAULT_WEB_BROWSER
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
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
decl_stmt|;
name|gui_config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|object
argument_list|)
expr_stmt|;
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
decl_stmt|;
name|gui_config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|object
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_TRANSPARENCY_SIZE
case|:
name|gui_config
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
name|gui_config
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
name|g_value_get_ulong
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
decl_stmt|;
name|gui_config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|object
argument_list|)
expr_stmt|;
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
name|gui_config
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
name|gui_config
operator|->
name|transparency_type
argument_list|)
expr_stmt|;
break|break;
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
name|g_value_set_ulong
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

