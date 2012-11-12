begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimptooloptions.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolpreset.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolpreset-load.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolpreset-save.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|DEFAULT_USE_FG_BG
define|#
directive|define
name|DEFAULT_USE_FG_BG
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_USE_BRUSH
define|#
directive|define
name|DEFAULT_USE_BRUSH
value|TRUE
end_define

begin_define
DECL|macro|DEFAULT_USE_DYNAMICS
define|#
directive|define
name|DEFAULT_USE_DYNAMICS
value|TRUE
end_define

begin_define
DECL|macro|DEFAULT_USE_GRADIENT
define|#
directive|define
name|DEFAULT_USE_GRADIENT
value|TRUE
end_define

begin_define
DECL|macro|DEFAULT_USE_PATTERN
define|#
directive|define
name|DEFAULT_USE_PATTERN
value|TRUE
end_define

begin_define
DECL|macro|DEFAULT_USE_PALETTE
define|#
directive|define
name|DEFAULT_USE_PALETTE
value|TRUE
end_define

begin_define
DECL|macro|DEFAULT_USE_FONT
define|#
directive|define
name|DEFAULT_USE_FONT
value|TRUE
end_define

begin_enum
enum|enum
DECL|enum|__anon2a3b0bbf0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_NAME
name|PROP_NAME
block|,
DECL|enumerator|PROP_GIMP
name|PROP_GIMP
block|,
DECL|enumerator|PROP_TOOL_OPTIONS
name|PROP_TOOL_OPTIONS
block|,
DECL|enumerator|PROP_USE_FG_BG
name|PROP_USE_FG_BG
block|,
DECL|enumerator|PROP_USE_BRUSH
name|PROP_USE_BRUSH
block|,
DECL|enumerator|PROP_USE_DYNAMICS
name|PROP_USE_DYNAMICS
block|,
DECL|enumerator|PROP_USE_GRADIENT
name|PROP_USE_GRADIENT
block|,
DECL|enumerator|PROP_USE_PATTERN
name|PROP_USE_PATTERN
block|,
DECL|enumerator|PROP_USE_PALETTE
name|PROP_USE_PALETTE
block|,
DECL|enumerator|PROP_USE_FONT
name|PROP_USE_FONT
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_tool_preset_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_preset_constructed
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
name|gimp_tool_preset_finalize
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
name|gimp_tool_preset_set_property
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
name|gimp_tool_preset_get_property
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
name|gimp_tool_preset_dispatch_properties_changed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|n_pspecs
parameter_list|,
name|GParamSpec
modifier|*
modifier|*
name|pspecs
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|gimp_tool_preset_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_tool_preset_deserialize_property
parameter_list|(
name|GimpConfig
modifier|*
name|config
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
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GTokenType
modifier|*
name|expected
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_preset_set_options
parameter_list|(
name|GimpToolPreset
modifier|*
name|preset
parameter_list|,
name|GimpToolOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_preset_options_notify
parameter_list|(
name|GObject
modifier|*
name|tool_options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpToolPreset
modifier|*
name|preset
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpToolPreset,gimp_tool_preset,GIMP_TYPE_DATA,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,gimp_tool_preset_config_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpToolPreset
argument_list|,
argument|gimp_tool_preset
argument_list|,
argument|GIMP_TYPE_DATA
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_tool_preset_config_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tool_preset_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tool_preset_class_init
parameter_list|(
name|GimpToolPresetClass
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
name|GimpDataClass
modifier|*
name|data_class
init|=
name|GIMP_DATA_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_tool_preset_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_tool_preset_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_tool_preset_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_tool_preset_get_property
expr_stmt|;
name|object_class
operator|->
name|dispatch_properties_changed
operator|=
name|gimp_tool_preset_dispatch_properties_changed
expr_stmt|;
name|data_class
operator|->
name|save
operator|=
name|gimp_tool_preset_save
expr_stmt|;
name|data_class
operator|->
name|get_extension
operator|=
name|gimp_tool_preset_get_extension
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_NAME
argument_list|,
literal|"name"
argument_list|,
name|NULL
argument_list|,
literal|"Unnamed"
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GIMP
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"gimp"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GIMP
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_TOOL_OPTIONS
argument_list|,
literal|"tool-options"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TOOL_OPTIONS
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_FG_BG
argument_list|,
literal|"use-fg-bg"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_USE_FG_BG
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_BRUSH
argument_list|,
literal|"use-brush"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_USE_BRUSH
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_DYNAMICS
argument_list|,
literal|"use-dynamics"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_USE_DYNAMICS
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_PATTERN
argument_list|,
literal|"use-pattern"
argument_list|,
name|NULL
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
name|PROP_USE_PALETTE
argument_list|,
literal|"use-palette"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_USE_PALETTE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_GRADIENT
argument_list|,
literal|"use-gradient"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_USE_GRADIENT
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_FONT
argument_list|,
literal|"use-font"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_USE_FONT
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_preset_config_iface_init (GimpConfigInterface * iface)
name|gimp_tool_preset_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|deserialize_property
operator|=
name|gimp_tool_preset_deserialize_property
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_preset_init (GimpToolPreset * tool_preset)
name|gimp_tool_preset_init
parameter_list|(
name|GimpToolPreset
modifier|*
name|tool_preset
parameter_list|)
block|{
name|tool_preset
operator|->
name|tool_options
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_preset_constructed (GObject * object)
name|gimp_tool_preset_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolPreset
modifier|*
name|preset
init|=
name|GIMP_TOOL_PRESET
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|preset
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_preset_finalize (GObject * object)
name|gimp_tool_preset_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolPreset
modifier|*
name|tool_preset
init|=
name|GIMP_TOOL_PRESET
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gimp_tool_preset_set_options
argument_list|(
name|tool_preset
argument_list|,
name|NULL
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
DECL|function|gimp_tool_preset_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_tool_preset_set_property
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
name|GimpToolPreset
modifier|*
name|tool_preset
init|=
name|GIMP_TOOL_PRESET
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
name|PROP_NAME
case|:
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|tool_preset
argument_list|)
argument_list|,
name|g_value_get_string
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GIMP
case|:
name|tool_preset
operator|->
name|gimp
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
comment|/* don't ref */
break|break;
case|case
name|PROP_TOOL_OPTIONS
case|:
name|gimp_tool_preset_set_options
argument_list|(
name|tool_preset
argument_list|,
name|GIMP_TOOL_OPTIONS
argument_list|(
name|g_value_get_object
argument_list|(
name|value
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_FG_BG
case|:
name|tool_preset
operator|->
name|use_fg_bg
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_BRUSH
case|:
name|tool_preset
operator|->
name|use_brush
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_DYNAMICS
case|:
name|tool_preset
operator|->
name|use_dynamics
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_PATTERN
case|:
name|tool_preset
operator|->
name|use_pattern
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_PALETTE
case|:
name|tool_preset
operator|->
name|use_palette
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_GRADIENT
case|:
name|tool_preset
operator|->
name|use_gradient
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_FONT
case|:
name|tool_preset
operator|->
name|use_font
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
DECL|function|gimp_tool_preset_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_tool_preset_get_property
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
name|GimpToolPreset
modifier|*
name|tool_preset
init|=
name|GIMP_TOOL_PRESET
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
name|PROP_NAME
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|gimp_object_get_name
argument_list|(
name|tool_preset
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GIMP
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|tool_preset
operator|->
name|gimp
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TOOL_OPTIONS
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|tool_preset
operator|->
name|tool_options
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_FG_BG
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|tool_preset
operator|->
name|use_fg_bg
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_BRUSH
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|tool_preset
operator|->
name|use_brush
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_DYNAMICS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|tool_preset
operator|->
name|use_dynamics
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_PATTERN
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|tool_preset
operator|->
name|use_pattern
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_PALETTE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|tool_preset
operator|->
name|use_palette
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_GRADIENT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|tool_preset
operator|->
name|use_gradient
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_FONT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|tool_preset
operator|->
name|use_font
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
DECL|function|gimp_tool_preset_dispatch_properties_changed (GObject * object,guint n_pspecs,GParamSpec ** pspecs)
name|gimp_tool_preset_dispatch_properties_changed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|n_pspecs
parameter_list|,
name|GParamSpec
modifier|*
modifier|*
name|pspecs
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispatch_properties_changed
argument_list|(
name|object
argument_list|,
name|n_pspecs
argument_list|,
name|pspecs
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_pspecs
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|pspecs
index|[
name|i
index|]
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_SERIALIZE
condition|)
block|{
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_tool_preset_get_extension (GimpData * data)
name|gimp_tool_preset_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
return|return
name|GIMP_TOOL_PRESET_FILE_EXTENSION
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_tool_preset_deserialize_property (GimpConfig * config,guint property_id,GValue * value,GParamSpec * pspec,GScanner * scanner,GTokenType * expected)
name|gimp_tool_preset_deserialize_property
parameter_list|(
name|GimpConfig
modifier|*
name|config
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
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GTokenType
modifier|*
name|expected
parameter_list|)
block|{
name|GimpToolPreset
modifier|*
name|tool_preset
init|=
name|GIMP_TOOL_PRESET
argument_list|(
name|config
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_TOOL_OPTIONS
case|:
block|{
name|GObject
modifier|*
name|options
decl_stmt|;
name|gchar
modifier|*
name|type_name
decl_stmt|;
name|GType
name|type
decl_stmt|;
name|GimpContextPropMask
name|serialize_props
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|type_name
argument_list|)
condition|)
block|{
operator|*
name|expected
operator|=
name|G_TOKEN_STRING
expr_stmt|;
break|break;
block|}
name|type
operator|=
name|g_type_from_name
argument_list|(
name|type_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
name|g_scanner_error
argument_list|(
name|scanner
argument_list|,
literal|"unable to determine type of '%s'"
argument_list|,
name|type_name
argument_list|)
expr_stmt|;
operator|*
name|expected
operator|=
name|G_TOKEN_STRING
expr_stmt|;
name|g_free
argument_list|(
name|type_name
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|!
name|g_type_is_a
argument_list|(
name|type
argument_list|,
name|GIMP_TYPE_TOOL_OPTIONS
argument_list|)
condition|)
block|{
name|g_scanner_error
argument_list|(
name|scanner
argument_list|,
literal|"'%s' is not a subclass of GimpToolOptions"
argument_list|,
name|type_name
argument_list|)
expr_stmt|;
operator|*
name|expected
operator|=
name|G_TOKEN_STRING
expr_stmt|;
name|g_free
argument_list|(
name|type_name
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_free
argument_list|(
name|type_name
argument_list|)
expr_stmt|;
name|options
operator|=
name|g_object_new
argument_list|(
name|type
argument_list|,
literal|"gimp"
argument_list|,
name|tool_preset
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GIMP_CONFIG_GET_INTERFACE
argument_list|(
name|options
argument_list|)
operator|->
name|deserialize
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|options
argument_list|)
argument_list|,
name|scanner
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|options
argument_list|)
expr_stmt|;
break|break;
block|}
comment|/* we need both tool and tool-info on the options */
if|if
condition|(
name|gimp_context_get_tool
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
condition|)
block|{
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"tool-info"
argument_list|,
name|gimp_context_get_tool
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_TOOL_OPTIONS
argument_list|(
name|options
argument_list|)
operator|->
name|tool_info
condition|)
block|{
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"tool"
argument_list|,
name|GIMP_TOOL_OPTIONS
argument_list|(
name|options
argument_list|)
operator|->
name|tool_info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* if we have none, the options set_property() logic will              * replace the NULL with its best guess              */
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"tool"
argument_list|,
name|NULL
argument_list|,
literal|"tool-info"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|serialize_props
operator|=
name|gimp_context_get_serialize_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_context_set_serialize_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
name|serialize_props
operator||
name|GIMP_CONTEXT_TOOL_MASK
argument_list|)
expr_stmt|;
name|g_value_take_object
argument_list|(
name|value
argument_list|,
name|options
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_preset_set_options (GimpToolPreset * preset,GimpToolOptions * options)
name|gimp_tool_preset_set_options
parameter_list|(
name|GimpToolPreset
modifier|*
name|preset
parameter_list|,
name|GimpToolOptions
modifier|*
name|options
parameter_list|)
block|{
if|if
condition|(
name|preset
operator|->
name|tool_options
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|preset
operator|->
name|tool_options
argument_list|,
name|gimp_tool_preset_options_notify
argument_list|,
name|preset
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|preset
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|preset
operator|->
name|tool_options
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|options
condition|)
block|{
name|GimpContextPropMask
name|serialize_props
decl_stmt|;
name|preset
operator|->
name|tool_options
operator|=
name|GIMP_TOOL_OPTIONS
argument_list|(
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|serialize_props
operator|=
name|gimp_context_get_serialize_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|preset
operator|->
name|tool_options
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_context_set_serialize_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|preset
operator|->
name|tool_options
argument_list|)
argument_list|,
name|serialize_props
operator||
name|GIMP_CONTEXT_TOOL_MASK
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|serialize_props
operator|&
name|GIMP_CONTEXT_FOREGROUND_MASK
operator|)
condition|)
name|g_object_set
argument_list|(
name|preset
argument_list|,
literal|"use-fg-bg"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|serialize_props
operator|&
name|GIMP_CONTEXT_BRUSH_MASK
operator|)
condition|)
name|g_object_set
argument_list|(
name|preset
argument_list|,
literal|"use-brush"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|serialize_props
operator|&
name|GIMP_CONTEXT_DYNAMICS_MASK
operator|)
condition|)
name|g_object_set
argument_list|(
name|preset
argument_list|,
literal|"use-dynamics"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|serialize_props
operator|&
name|GIMP_CONTEXT_GRADIENT_MASK
operator|)
condition|)
name|g_object_set
argument_list|(
name|preset
argument_list|,
literal|"use-gradient"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|serialize_props
operator|&
name|GIMP_CONTEXT_PATTERN_MASK
operator|)
condition|)
name|g_object_set
argument_list|(
name|preset
argument_list|,
literal|"use-pattern"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|serialize_props
operator|&
name|GIMP_CONTEXT_PALETTE_MASK
operator|)
condition|)
name|g_object_set
argument_list|(
name|preset
argument_list|,
literal|"use-palette"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|serialize_props
operator|&
name|GIMP_CONTEXT_FONT_MASK
operator|)
condition|)
name|g_object_set
argument_list|(
name|preset
argument_list|,
literal|"use-font"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|preset
operator|->
name|tool_options
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_preset_options_notify
argument_list|)
argument_list|,
name|preset
argument_list|)
expr_stmt|;
block|}
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|preset
argument_list|)
argument_list|,
literal|"tool-options"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_preset_options_notify (GObject * tool_options,const GParamSpec * pspec,GimpToolPreset * preset)
name|gimp_tool_preset_options_notify
parameter_list|(
name|GObject
modifier|*
name|tool_options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpToolPreset
modifier|*
name|preset
parameter_list|)
block|{
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|preset
argument_list|)
argument_list|,
literal|"tool-options"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpData
modifier|*
DECL|function|gimp_tool_preset_new (GimpContext * context,const gchar * unused)
name|gimp_tool_preset_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|unused
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tool_info
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|stock_id
operator|=
name|gimp_viewable_get_stock_id
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_PRESET
argument_list|,
literal|"name"
argument_list|,
name|tool_info
operator|->
name|blurb
argument_list|,
literal|"stock-id"
argument_list|,
name|stock_id
argument_list|,
literal|"gimp"
argument_list|,
name|context
operator|->
name|gimp
argument_list|,
literal|"tool-options"
argument_list|,
name|tool_info
operator|->
name|tool_options
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpContextPropMask
DECL|function|gimp_tool_preset_get_prop_mask (GimpToolPreset * preset)
name|gimp_tool_preset_get_prop_mask
parameter_list|(
name|GimpToolPreset
modifier|*
name|preset
parameter_list|)
block|{
name|GimpContextPropMask
name|serialize_props
decl_stmt|;
name|GimpContextPropMask
name|use_props
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_PRESET
argument_list|(
name|preset
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|serialize_props
operator|=
name|gimp_context_get_serialize_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|preset
operator|->
name|tool_options
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|preset
operator|->
name|use_fg_bg
condition|)
block|{
name|use_props
operator||=
operator|(
name|GIMP_CONTEXT_FOREGROUND_MASK
operator|&
name|serialize_props
operator|)
expr_stmt|;
name|use_props
operator||=
operator|(
name|GIMP_CONTEXT_BACKGROUND_MASK
operator|&
name|serialize_props
operator|)
expr_stmt|;
block|}
if|if
condition|(
name|preset
operator|->
name|use_brush
condition|)
name|use_props
operator||=
operator|(
name|GIMP_CONTEXT_BRUSH_MASK
operator|&
name|serialize_props
operator|)
expr_stmt|;
if|if
condition|(
name|preset
operator|->
name|use_dynamics
condition|)
name|use_props
operator||=
operator|(
name|GIMP_CONTEXT_DYNAMICS_MASK
operator|&
name|serialize_props
operator|)
expr_stmt|;
if|if
condition|(
name|preset
operator|->
name|use_pattern
condition|)
name|use_props
operator||=
operator|(
name|GIMP_CONTEXT_PATTERN_MASK
operator|&
name|serialize_props
operator|)
expr_stmt|;
if|if
condition|(
name|preset
operator|->
name|use_palette
condition|)
name|use_props
operator||=
operator|(
name|GIMP_CONTEXT_PALETTE_MASK
operator|&
name|serialize_props
operator|)
expr_stmt|;
if|if
condition|(
name|preset
operator|->
name|use_gradient
condition|)
name|use_props
operator||=
operator|(
name|GIMP_CONTEXT_GRADIENT_MASK
operator|&
name|serialize_props
operator|)
expr_stmt|;
if|if
condition|(
name|preset
operator|->
name|use_font
condition|)
name|use_props
operator||=
operator|(
name|GIMP_CONTEXT_FONT_MASK
operator|&
name|serialize_props
operator|)
expr_stmt|;
return|return
name|use_props
return|;
block|}
end_function

end_unit

