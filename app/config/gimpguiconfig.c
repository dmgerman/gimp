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
file|"base/base-enums.h"
end_include

begin_include
include|#
directive|include
file|"core/core-enums.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig.h"
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
file|"gimpguiconfig.h"
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

begin_enum
enum|enum
DECL|enum|__anon2c85c9a20103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_MARCHING_ANTS_SPEED
name|PROP_MARCHING_ANTS_SPEED
block|,
DECL|enumerator|PROP_COLORMAP_CYCLING
name|PROP_COLORMAP_CYCLING
block|,
DECL|enumerator|PROP_LAST_OPENED_SIZE
name|PROP_LAST_OPENED_SIZE
block|,
DECL|enumerator|PROP_TRANSPARENCY_SIZE
name|PROP_TRANSPARENCY_SIZE
block|,
DECL|enumerator|PROP_TRANSPARENCY_TYPE
name|PROP_TRANSPARENCY_TYPE
block|,
DECL|enumerator|PROP_GAMMA_CORRECTION
name|PROP_GAMMA_CORRECTION
block|,
DECL|enumerator|PROP_PERFECT_MOUSE
name|PROP_PERFECT_MOUSE
block|,
DECL|enumerator|PROP_INSTALL_COLORMAP
name|PROP_INSTALL_COLORMAP
block|,
DECL|enumerator|PROP_MIN_COLORS
name|PROP_MIN_COLORS
block|,
DECL|enumerator|PROP_DEFAULT_THRESHOLD
name|PROP_DEFAULT_THRESHOLD
block|,
DECL|enumerator|PROP_RESIZE_WINDOWS_ON_ZOOM
name|PROP_RESIZE_WINDOWS_ON_ZOOM
block|,
DECL|enumerator|PROP_RESIZE_WINDOWS_ON_RESIZE
name|PROP_RESIZE_WINDOWS_ON_RESIZE
block|,
DECL|enumerator|PROP_PREVIEW_SIZE
name|PROP_PREVIEW_SIZE
block|,
DECL|enumerator|PROP_NAV_PREVIEW_SIZE
name|PROP_NAV_PREVIEW_SIZE
block|,
DECL|enumerator|PROP_IMAGE_TITLE_FORMAT
name|PROP_IMAGE_TITLE_FORMAT
block|,
DECL|enumerator|PROP_SHOW_RULERS
name|PROP_SHOW_RULERS
block|,
DECL|enumerator|PROP_SHOW_STATUSBAR
name|PROP_SHOW_STATUSBAR
block|,
DECL|enumerator|PROP_SHOW_TOOL_TIPS
name|PROP_SHOW_TOOL_TIPS
block|,
DECL|enumerator|PROP_GLOBAL_PAINT_OPTIONS
name|PROP_GLOBAL_PAINT_OPTIONS
block|}
enum|;
end_enum

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
name|GIMP_TYPE_CORE_CONFIG
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
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
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
name|PROP_MARCHING_ANTS_SPEED
argument_list|,
literal|"marching-ants-speed"
argument_list|,
literal|50
argument_list|,
name|G_MAXINT
argument_list|,
literal|300
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_COLORMAP_CYCLING
argument_list|,
literal|"colormap-cycling"
argument_list|,
name|FALSE
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
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_TRANSPARENCY_SIZE
argument_list|,
literal|"transparency-size"
argument_list|,
name|GIMP_TYPE_CHECK_SIZE
argument_list|,
name|GIMP_MEDIUM_CHECKS
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
name|GIMP_TYPE_CHECK_TYPE
argument_list|,
name|GIMP_GRAY_CHECKS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_GAMMA_CORRECTION
argument_list|,
literal|"gamma-correction"
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_PERFECT_MOUSE
argument_list|,
literal|"perfect-mouse"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_INSTALL_COLORMAP
argument_list|,
literal|"install-colormap"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_MIN_COLORS
argument_list|,
literal|"min-colors"
argument_list|,
literal|27
argument_list|,
literal|256
argument_list|,
literal|144
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
literal|0
argument_list|,
literal|255
argument_list|,
literal|15
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_RESIZE_WINDOWS_ON_ZOOM
argument_list|,
literal|"resize-windows-on-zoom"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_RESIZE_WINDOWS_ON_RESIZE
argument_list|,
literal|"resize-windows-on-resize"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_PREVIEW_SIZE
argument_list|,
literal|"preview-size"
argument_list|,
name|GIMP_TYPE_PREVIEW_SIZE
argument_list|,
name|GIMP_PREVIEW_SIZE_SMALL
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_NAV_PREVIEW_SIZE
argument_list|,
literal|"nav-preview-size"
argument_list|,
name|GIMP_TYPE_PREVIEW_SIZE
argument_list|,
name|GIMP_PREVIEW_SIZE_HUGE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_IMAGE_TITLE_FORMAT
argument_list|,
literal|"image-title-format"
argument_list|,
literal|"%f-%p.%i (%t)"
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_RULERS
argument_list|,
literal|"show-rulers"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_STATUSBAR
argument_list|,
literal|"show-statusbar"
argument_list|,
name|TRUE
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
name|TRUE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_GLOBAL_PAINT_OPTIONS
argument_list|,
literal|"global-paint-options"
argument_list|,
name|FALSE
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
name|PROP_MARCHING_ANTS_SPEED
case|:
name|gui_config
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
name|PROP_COLORMAP_CYCLING
case|:
name|gui_config
operator|->
name|colormap_cycling
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
name|PROP_GAMMA_CORRECTION
case|:
name|gui_config
operator|->
name|gamma_val
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PERFECT_MOUSE
case|:
name|gui_config
operator|->
name|perfect_mouse
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INSTALL_COLORMAP
case|:
name|gui_config
operator|->
name|install_cmap
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MIN_COLORS
case|:
name|gui_config
operator|->
name|min_colors
operator|=
name|g_value_get_int
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
name|PROP_RESIZE_WINDOWS_ON_ZOOM
case|:
name|gui_config
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
name|gui_config
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
name|PROP_PREVIEW_SIZE
case|:
name|gui_config
operator|->
name|preview_size
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_NAV_PREVIEW_SIZE
case|:
name|gui_config
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
name|PROP_IMAGE_TITLE_FORMAT
case|:
name|g_free
argument_list|(
name|gui_config
operator|->
name|image_title_format
argument_list|)
expr_stmt|;
name|gui_config
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
name|PROP_SHOW_RULERS
case|:
name|gui_config
operator|->
name|show_rulers
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_STATUSBAR
case|:
name|gui_config
operator|->
name|show_statusbar
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
name|PROP_GLOBAL_PAINT_OPTIONS
case|:
name|gui_config
operator|->
name|global_paint_options
operator|=
name|g_value_get_boolean
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
name|PROP_MARCHING_ANTS_SPEED
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|marching_ants_speed
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_COLORMAP_CYCLING
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|colormap_cycling
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
name|PROP_GAMMA_CORRECTION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|gamma_val
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PERFECT_MOUSE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|perfect_mouse
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INSTALL_COLORMAP
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|install_cmap
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MIN_COLORS
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|min_colors
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
name|PROP_RESIZE_WINDOWS_ON_ZOOM
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
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
name|gui_config
operator|->
name|resize_windows_on_resize
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIEW_SIZE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|preview_size
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
name|gui_config
operator|->
name|nav_preview_size
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
name|gui_config
operator|->
name|image_title_format
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_RULERS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|show_rulers
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_STATUSBAR
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|show_statusbar
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
name|PROP_GLOBAL_PAINT_OPTIONS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gui_config
operator|->
name|global_paint_options
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

