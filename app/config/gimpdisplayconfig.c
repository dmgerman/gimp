begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpDisplayConfig class  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpdisplayconfig.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_display_config_class_init
parameter_list|(
name|GimpDisplayConfigClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

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

begin_define
DECL|macro|DEFAULT_IMAGE_TITLE_FORMAT
define|#
directive|define
name|DEFAULT_IMAGE_TITLE_FORMAT
value|"%f-%p.%i (%t)"
end_define

begin_define
DECL|macro|DEFAULT_IMAGE_STATUS_FORMAT
define|#
directive|define
name|DEFAULT_IMAGE_STATUS_FORMAT
value|DEFAULT_IMAGE_TITLE_FORMAT
end_define

begin_enum
enum|enum
DECL|enum|__anon297475cb0103
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
DECL|enumerator|PROP_RESIZE_WINDOWS_ON_ZOOM
name|PROP_RESIZE_WINDOWS_ON_ZOOM
block|,
DECL|enumerator|PROP_RESIZE_WINDOWS_ON_RESIZE
name|PROP_RESIZE_WINDOWS_ON_RESIZE
block|,
DECL|enumerator|PROP_DEFAULT_DOT_FOR_DOT
name|PROP_DEFAULT_DOT_FOR_DOT
block|,
DECL|enumerator|PROP_CURSOR_MODE
name|PROP_CURSOR_MODE
block|,
DECL|enumerator|PROP_CURSOR_UPDATING
name|PROP_CURSOR_UPDATING
block|,
DECL|enumerator|PROP_IMAGE_TITLE_FORMAT
name|PROP_IMAGE_TITLE_FORMAT
block|,
DECL|enumerator|PROP_IMAGE_STATUS_FORMAT
name|PROP_IMAGE_STATUS_FORMAT
block|,
DECL|enumerator|PROP_SHOW_RULERS
name|PROP_SHOW_RULERS
block|,
DECL|enumerator|PROP_SHOW_STATUSBAR
name|PROP_SHOW_STATUSBAR
block|,
DECL|enumerator|PROP_CONFIRM_ON_CLOSE
name|PROP_CONFIRM_ON_CLOSE
block|,
DECL|enumerator|PROP_MONITOR_XRESOLUTION
name|PROP_MONITOR_XRESOLUTION
block|,
DECL|enumerator|PROP_MONITOR_YRESOLUTION
name|PROP_MONITOR_YRESOLUTION
block|,
DECL|enumerator|PROP_MONITOR_RES_FROM_GDK
name|PROP_MONITOR_RES_FROM_GDK
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
DECL|function|gimp_display_config_get_type (void)
name|gimp_display_config_get_type
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
name|GimpDisplayConfigClass
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
name|gimp_display_config_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpDisplayConfig
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
literal|"GimpDisplayConfig"
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
DECL|function|gimp_display_config_class_init (GimpDisplayConfigClass * klass)
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
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_DOT_FOR_DOT
argument_list|,
literal|"default-dot-for-dot"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_CURSOR_MODE
argument_list|,
literal|"cursor-mode"
argument_list|,
name|GIMP_TYPE_CURSOR_MODE
argument_list|,
name|GIMP_CURSOR_MODE_TOOL_ICON
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_CURSOR_UPDATING
argument_list|,
literal|"cursor-updating"
argument_list|,
name|TRUE
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
name|DEFAULT_IMAGE_TITLE_FORMAT
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_IMAGE_STATUS_FORMAT
argument_list|,
literal|"image-status-format"
argument_list|,
name|DEFAULT_IMAGE_STATUS_FORMAT
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
name|PROP_CONFIRM_ON_CLOSE
argument_list|,
literal|"confirm-on-close"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_MONITOR_XRESOLUTION
argument_list|,
literal|"monitor-xresolution"
argument_list|,
name|GIMP_MIN_RESOLUTION
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|72.0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_MONITOR_YRESOLUTION
argument_list|,
literal|"monitor-yresolution"
argument_list|,
name|GIMP_MIN_RESOLUTION
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|72.0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_MONITOR_RES_FROM_GDK
argument_list|,
literal|"monitor-resolution-from-windowing-system"
argument_list|,
name|TRUE
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
decl_stmt|;
name|display_config
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|object
argument_list|)
expr_stmt|;
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
decl_stmt|;
name|display_config
operator|=
name|GIMP_DISPLAY_CONFIG
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
name|PROP_COLORMAP_CYCLING
case|:
name|display_config
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
name|PROP_SHOW_RULERS
case|:
name|display_config
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
name|display_config
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
name|PROP_CONFIRM_ON_CLOSE
case|:
name|display_config
operator|->
name|confirm_on_close
operator|=
name|g_value_get_boolean
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
decl_stmt|;
name|display_config
operator|=
name|GIMP_DISPLAY_CONFIG
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
name|display_config
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
name|display_config
operator|->
name|colormap_cycling
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
name|PROP_SHOW_RULERS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|display_config
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
name|display_config
operator|->
name|show_statusbar
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONFIRM_ON_CLOSE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|display_config
operator|->
name|confirm_on_close
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

