begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpCoreConfig class  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpcoreconfig.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_core_config_class_init
parameter_list|(
name|GimpCoreConfigClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_core_config_finalize
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
name|gimp_core_config_set_property
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
name|gimp_core_config_get_property
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
DECL|enum|__anon2bd126330103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PLUG_IN_PATH
name|PROP_PLUG_IN_PATH
block|,
DECL|enumerator|PROP_TOOL_PLUG_IN_PATH
name|PROP_TOOL_PLUG_IN_PATH
block|,
DECL|enumerator|PROP_MODULE_PATH
name|PROP_MODULE_PATH
block|,
DECL|enumerator|PROP_BRUSH_PATH
name|PROP_BRUSH_PATH
block|,
DECL|enumerator|PROP_PATTERN_PATH
name|PROP_PATTERN_PATH
block|,
DECL|enumerator|PROP_PALETTE_PATH
name|PROP_PALETTE_PATH
block|,
DECL|enumerator|PROP_GRADIENT_PATH
name|PROP_GRADIENT_PATH
block|,
DECL|enumerator|PROP_DEFAULT_BRUSH
name|PROP_DEFAULT_BRUSH
block|,
DECL|enumerator|PROP_DEFAULT_PATTERN
name|PROP_DEFAULT_PATTERN
block|,
DECL|enumerator|PROP_DEFAULT_PALETTE
name|PROP_DEFAULT_PALETTE
block|,
DECL|enumerator|PROP_DEFAULT_GRADIENT
name|PROP_DEFAULT_GRADIENT
block|,
DECL|enumerator|PROP_DEFAULT_COMMENT
name|PROP_DEFAULT_COMMENT
block|,
DECL|enumerator|PROP_DEFAULT_IMAGE_TYPE
name|PROP_DEFAULT_IMAGE_TYPE
block|,
DECL|enumerator|PROP_DEFAULT_IMAGE_WIDTH
name|PROP_DEFAULT_IMAGE_WIDTH
block|,
DECL|enumerator|PROP_DEFAULT_IMAGE_HEIGHT
name|PROP_DEFAULT_IMAGE_HEIGHT
block|,
DECL|enumerator|PROP_DEFAULT_UNIT
name|PROP_DEFAULT_UNIT
block|,
DECL|enumerator|PROP_DEFAULT_XRESOLUTION
name|PROP_DEFAULT_XRESOLUTION
block|,
DECL|enumerator|PROP_DEFAULT_YRESOLUTION
name|PROP_DEFAULT_YRESOLUTION
block|,
DECL|enumerator|PROP_DEFAULT_RESOLUTION_UNIT
name|PROP_DEFAULT_RESOLUTION_UNIT
block|,
DECL|enumerator|PROP_UNDO_LEVELS
name|PROP_UNDO_LEVELS
block|,
DECL|enumerator|PROP_PLUGINRC_PATH
name|PROP_PLUGINRC_PATH
block|,
DECL|enumerator|PROP_MODULE_LOAD_INHIBIT
name|PROP_MODULE_LOAD_INHIBIT
block|,
DECL|enumerator|PROP_PREVIEW_SIZE
name|PROP_PREVIEW_SIZE
block|,
DECL|enumerator|PROP_WRITE_THUMBNAILS
name|PROP_WRITE_THUMBNAILS
block|,
DECL|enumerator|PROP_GAMMA_CORRECTION
name|PROP_GAMMA_CORRECTION
block|,
DECL|enumerator|PROP_INSTALL_COLORMAP
name|PROP_INSTALL_COLORMAP
block|,
DECL|enumerator|PROP_MIN_COLORS
name|PROP_MIN_COLORS
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
DECL|function|gimp_core_config_get_type (void)
name|gimp_core_config_get_type
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
name|GimpCoreConfigClass
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
name|gimp_core_config_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpCoreConfig
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
name|GIMP_TYPE_BASE_CONFIG
argument_list|,
literal|"GimpCoreConfig"
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
DECL|function|gimp_core_config_class_init (GimpCoreConfigClass * klass)
name|gimp_core_config_class_init
parameter_list|(
name|GimpCoreConfigClass
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
name|gimp_core_config_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_core_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_core_config_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_PLUG_IN_PATH
argument_list|,
literal|"plug-in-path"
argument_list|,
name|gimp_config_build_plug_in_path
argument_list|(
literal|"plug-ins"
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_TOOL_PLUG_IN_PATH
argument_list|,
literal|"tool-plug-in-path"
argument_list|,
name|gimp_config_build_plug_in_path
argument_list|(
literal|"tool-plug-ins"
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_MODULE_PATH
argument_list|,
literal|"module-path"
argument_list|,
name|gimp_config_build_plug_in_path
argument_list|(
literal|"modules"
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_BRUSH_PATH
argument_list|,
literal|"brush-path"
argument_list|,
name|gimp_config_build_data_path
argument_list|(
literal|"brushes"
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_PATTERN_PATH
argument_list|,
literal|"pattern-path"
argument_list|,
name|gimp_config_build_data_path
argument_list|(
literal|"patterns"
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_PALETTE_PATH
argument_list|,
literal|"palette-path"
argument_list|,
name|gimp_config_build_data_path
argument_list|(
literal|"palettes"
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_GRADIENT_PATH
argument_list|,
literal|"gradient-path"
argument_list|,
name|gimp_config_build_data_path
argument_list|(
literal|"gradients"
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_BRUSH
argument_list|,
literal|"default-brush"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_PATTERN
argument_list|,
literal|"default-pattern"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_PATTERN
argument_list|,
literal|"default-palette"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_GRADIENT
argument_list|,
literal|"default-gradient"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_COMMENT
argument_list|,
literal|"default-comment"
argument_list|,
literal|"Created with The GIMP"
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_IMAGE_TYPE
argument_list|,
literal|"default-image-type"
argument_list|,
name|GIMP_TYPE_IMAGE_BASE_TYPE
argument_list|,
name|GIMP_RGB
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_IMAGE_WIDTH
argument_list|,
literal|"default-image-width"
argument_list|,
literal|1
argument_list|,
literal|0x8000
argument_list|,
literal|256
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_IMAGE_HEIGHT
argument_list|,
literal|"default-image-height"
argument_list|,
literal|1
argument_list|,
literal|0x8000
argument_list|,
literal|256
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_UNIT
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_UNIT
argument_list|,
literal|"default-unit"
argument_list|,
name|GIMP_UNIT_INCH
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_XRESOLUTION
argument_list|,
literal|"default-xresolution"
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
name|PROP_DEFAULT_YRESOLUTION
argument_list|,
literal|"default-yresolution"
argument_list|,
name|GIMP_MIN_RESOLUTION
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|72.0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_UNIT
argument_list|(
name|object_class
argument_list|,
name|PROP_DEFAULT_RESOLUTION_UNIT
argument_list|,
literal|"default-resolution-unit"
argument_list|,
name|GIMP_UNIT_INCH
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_UNDO_LEVELS
argument_list|,
literal|"undo-levels"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_PLUGINRC_PATH
argument_list|,
literal|"pluginrc-path"
argument_list|,
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
literal|"pluginrc"
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_MODULE_LOAD_INHIBIT
argument_list|,
literal|"module-load-inhibit"
argument_list|,
name|NULL
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
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_WRITE_THUMBNAILS
argument_list|,
literal|"write-thumbnails"
argument_list|,
name|TRUE
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_core_config_finalize (GObject * object)
name|gimp_core_config_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCoreConfig
modifier|*
name|core_config
decl_stmt|;
name|core_config
operator|=
name|GIMP_CORE_CONFIG
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|core_config
operator|->
name|plug_in_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|core_config
operator|->
name|tool_plug_in_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|core_config
operator|->
name|module_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|core_config
operator|->
name|brush_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|core_config
operator|->
name|pattern_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|core_config
operator|->
name|palette_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|core_config
operator|->
name|gradient_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|core_config
operator|->
name|default_brush
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|core_config
operator|->
name|default_pattern
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|core_config
operator|->
name|default_palette
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|core_config
operator|->
name|default_gradient
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|core_config
operator|->
name|default_comment
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|core_config
operator|->
name|plug_in_rc_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|core_config
operator|->
name|module_load_inhibit
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
DECL|function|gimp_core_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_core_config_set_property
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
name|GimpCoreConfig
modifier|*
name|core_config
decl_stmt|;
name|core_config
operator|=
name|GIMP_CORE_CONFIG
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
name|PROP_PLUG_IN_PATH
case|:
name|g_free
argument_list|(
name|core_config
operator|->
name|plug_in_path
argument_list|)
expr_stmt|;
name|core_config
operator|->
name|plug_in_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TOOL_PLUG_IN_PATH
case|:
name|g_free
argument_list|(
name|core_config
operator|->
name|tool_plug_in_path
argument_list|)
expr_stmt|;
name|core_config
operator|->
name|tool_plug_in_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MODULE_PATH
case|:
name|g_free
argument_list|(
name|core_config
operator|->
name|module_path
argument_list|)
expr_stmt|;
name|core_config
operator|->
name|module_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BRUSH_PATH
case|:
name|g_free
argument_list|(
name|core_config
operator|->
name|brush_path
argument_list|)
expr_stmt|;
name|core_config
operator|->
name|brush_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PATTERN_PATH
case|:
name|g_free
argument_list|(
name|core_config
operator|->
name|pattern_path
argument_list|)
expr_stmt|;
name|core_config
operator|->
name|pattern_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PALETTE_PATH
case|:
name|g_free
argument_list|(
name|core_config
operator|->
name|palette_path
argument_list|)
expr_stmt|;
name|core_config
operator|->
name|palette_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_PATH
case|:
name|g_free
argument_list|(
name|core_config
operator|->
name|gradient_path
argument_list|)
expr_stmt|;
name|core_config
operator|->
name|gradient_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_BRUSH
case|:
name|g_free
argument_list|(
name|core_config
operator|->
name|default_brush
argument_list|)
expr_stmt|;
name|core_config
operator|->
name|default_brush
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_PATTERN
case|:
name|g_free
argument_list|(
name|core_config
operator|->
name|default_pattern
argument_list|)
expr_stmt|;
name|core_config
operator|->
name|default_pattern
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_PALETTE
case|:
name|g_free
argument_list|(
name|core_config
operator|->
name|default_palette
argument_list|)
expr_stmt|;
name|core_config
operator|->
name|default_palette
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_GRADIENT
case|:
name|g_free
argument_list|(
name|core_config
operator|->
name|default_gradient
argument_list|)
expr_stmt|;
name|core_config
operator|->
name|default_gradient
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_COMMENT
case|:
name|g_free
argument_list|(
name|core_config
operator|->
name|default_comment
argument_list|)
expr_stmt|;
name|core_config
operator|->
name|default_comment
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_IMAGE_TYPE
case|:
name|core_config
operator|->
name|default_image_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_IMAGE_WIDTH
case|:
name|core_config
operator|->
name|default_image_width
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_IMAGE_HEIGHT
case|:
name|core_config
operator|->
name|default_image_height
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_UNIT
case|:
name|core_config
operator|->
name|default_unit
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_XRESOLUTION
case|:
name|core_config
operator|->
name|default_xresolution
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_YRESOLUTION
case|:
name|core_config
operator|->
name|default_yresolution
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_RESOLUTION_UNIT
case|:
name|core_config
operator|->
name|default_resolution_unit
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UNDO_LEVELS
case|:
name|core_config
operator|->
name|levels_of_undo
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PLUGINRC_PATH
case|:
name|g_free
argument_list|(
name|core_config
operator|->
name|plug_in_rc_path
argument_list|)
expr_stmt|;
name|core_config
operator|->
name|plug_in_rc_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MODULE_LOAD_INHIBIT
case|:
name|g_free
argument_list|(
name|core_config
operator|->
name|module_load_inhibit
argument_list|)
expr_stmt|;
name|core_config
operator|->
name|module_load_inhibit
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIEW_SIZE
case|:
name|core_config
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
name|PROP_WRITE_THUMBNAILS
case|:
name|core_config
operator|->
name|write_thumbnails
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GAMMA_CORRECTION
case|:
name|core_config
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
name|PROP_INSTALL_COLORMAP
case|:
name|core_config
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
name|core_config
operator|->
name|min_colors
operator|=
name|g_value_get_int
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
DECL|function|gimp_core_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_core_config_get_property
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
name|GimpCoreConfig
modifier|*
name|core_config
decl_stmt|;
name|core_config
operator|=
name|GIMP_CORE_CONFIG
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
name|PROP_PLUG_IN_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|plug_in_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TOOL_PLUG_IN_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|tool_plug_in_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MODULE_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|module_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BRUSH_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|brush_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PATTERN_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|pattern_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PALETTE_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|palette_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|gradient_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_BRUSH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|default_brush
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_PATTERN
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|default_pattern
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_PALETTE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|default_palette
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_GRADIENT
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|default_gradient
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_COMMENT
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|default_comment
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_IMAGE_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|default_image_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_IMAGE_WIDTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|default_image_width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_IMAGE_HEIGHT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|default_image_height
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|default_unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_XRESOLUTION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|default_xresolution
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_YRESOLUTION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|default_yresolution
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEFAULT_RESOLUTION_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|default_resolution_unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UNDO_LEVELS
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|levels_of_undo
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PLUGINRC_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|plug_in_rc_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MODULE_LOAD_INHIBIT
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|module_load_inhibit
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
name|core_config
operator|->
name|preview_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WRITE_THUMBNAILS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|core_config
operator|->
name|write_thumbnails
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
name|core_config
operator|->
name|gamma_val
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
name|core_config
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
name|core_config
operator|->
name|min_colors
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

