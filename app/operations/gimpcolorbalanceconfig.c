begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcolorbalanceconfig.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpcolor/gimpcolor.h"
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
file|"operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorbalanceconfig.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a2b03670103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_RANGE
name|PROP_RANGE
block|,
DECL|enumerator|PROP_CYAN_RED
name|PROP_CYAN_RED
block|,
DECL|enumerator|PROP_MAGENTA_GREEN
name|PROP_MAGENTA_GREEN
block|,
DECL|enumerator|PROP_YELLOW_BLUE
name|PROP_YELLOW_BLUE
block|,
DECL|enumerator|PROP_PRESERVE_LUMINOSITY
name|PROP_PRESERVE_LUMINOSITY
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_color_balance_config_iface_init
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
name|gimp_color_balance_config_get_property
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
name|gimp_color_balance_config_set_property
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
name|gboolean
name|gimp_color_balance_config_serialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_color_balance_config_deserialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|nest_level
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_color_balance_config_equal
parameter_list|(
name|GimpConfig
modifier|*
name|a
parameter_list|,
name|GimpConfig
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_balance_config_reset
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_color_balance_config_copy
parameter_list|(
name|GimpConfig
modifier|*
name|src
parameter_list|,
name|GimpConfig
modifier|*
name|dest
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpColorBalanceConfig,gimp_color_balance_config,GIMP_TYPE_SETTINGS,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,gimp_color_balance_config_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpColorBalanceConfig
argument_list|,
argument|gimp_color_balance_config
argument_list|,
argument|GIMP_TYPE_SETTINGS
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_color_balance_config_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_balance_config_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_color_balance_config_class_init
parameter_list|(
name|GimpColorBalanceConfigClass
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
name|GimpViewableClass
modifier|*
name|viewable_class
init|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_color_balance_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_color_balance_config_get_property
expr_stmt|;
name|viewable_class
operator|->
name|default_stock_id
operator|=
literal|"gimp-tool-color-balance"
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_RANGE
argument_list|,
literal|"range"
argument_list|,
literal|"The affected range"
argument_list|,
name|GIMP_TYPE_TRANSFER_MODE
argument_list|,
name|GIMP_TRANSFER_MIDTONES
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_CYAN_RED
argument_list|,
literal|"cyan-red"
argument_list|,
literal|"Cyan-Red"
argument_list|,
operator|-
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_MAGENTA_GREEN
argument_list|,
literal|"magenta-green"
argument_list|,
literal|"Magenta-Green"
argument_list|,
operator|-
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_YELLOW_BLUE
argument_list|,
literal|"yellow-blue"
argument_list|,
literal|"Yellow-Blue"
argument_list|,
operator|-
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_PRESERVE_LUMINOSITY
argument_list|,
literal|"preserve-luminosity"
argument_list|,
literal|"Preserve Luminosity"
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_balance_config_iface_init (GimpConfigInterface * iface)
name|gimp_color_balance_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|serialize
operator|=
name|gimp_color_balance_config_serialize
expr_stmt|;
name|iface
operator|->
name|deserialize
operator|=
name|gimp_color_balance_config_deserialize
expr_stmt|;
name|iface
operator|->
name|equal
operator|=
name|gimp_color_balance_config_equal
expr_stmt|;
name|iface
operator|->
name|reset
operator|=
name|gimp_color_balance_config_reset
expr_stmt|;
name|iface
operator|->
name|copy
operator|=
name|gimp_color_balance_config_copy
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_balance_config_init (GimpColorBalanceConfig * self)
name|gimp_color_balance_config_init
parameter_list|(
name|GimpColorBalanceConfig
modifier|*
name|self
parameter_list|)
block|{
name|gimp_config_reset
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|self
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_balance_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_color_balance_config_get_property
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
name|GimpColorBalanceConfig
modifier|*
name|self
init|=
name|GIMP_COLOR_BALANCE_CONFIG
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
name|PROP_RANGE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|range
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CYAN_RED
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|cyan_red
index|[
name|self
operator|->
name|range
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MAGENTA_GREEN
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|magenta_green
index|[
name|self
operator|->
name|range
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_YELLOW_BLUE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|yellow_blue
index|[
name|self
operator|->
name|range
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESERVE_LUMINOSITY
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|preserve_luminosity
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
DECL|function|gimp_color_balance_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_color_balance_config_set_property
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
name|GimpColorBalanceConfig
modifier|*
name|self
init|=
name|GIMP_COLOR_BALANCE_CONFIG
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
name|PROP_RANGE
case|:
name|self
operator|->
name|range
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"cyan-red"
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"magenta-green"
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"yellow-blue"
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CYAN_RED
case|:
name|self
operator|->
name|cyan_red
index|[
name|self
operator|->
name|range
index|]
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MAGENTA_GREEN
case|:
name|self
operator|->
name|magenta_green
index|[
name|self
operator|->
name|range
index|]
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_YELLOW_BLUE
case|:
name|self
operator|->
name|yellow_blue
index|[
name|self
operator|->
name|range
index|]
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESERVE_LUMINOSITY
case|:
name|self
operator|->
name|preserve_luminosity
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
name|gboolean
DECL|function|gimp_color_balance_config_serialize (GimpConfig * config,GimpConfigWriter * writer,gpointer data)
name|gimp_color_balance_config_serialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpColorBalanceConfig
modifier|*
name|bc_config
init|=
name|GIMP_COLOR_BALANCE_CONFIG
argument_list|(
name|config
argument_list|)
decl_stmt|;
name|GimpTransferMode
name|range
decl_stmt|;
name|GimpTransferMode
name|old_range
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_config_serialize_property_by_name
argument_list|(
name|config
argument_list|,
literal|"time"
argument_list|,
name|writer
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|old_range
operator|=
name|bc_config
operator|->
name|range
expr_stmt|;
for|for
control|(
name|range
operator|=
name|GIMP_TRANSFER_SHADOWS
init|;
name|range
operator|<=
name|GIMP_TRANSFER_HIGHLIGHTS
condition|;
name|range
operator|++
control|)
block|{
name|bc_config
operator|->
name|range
operator|=
name|range
expr_stmt|;
name|success
operator|=
operator|(
name|gimp_config_serialize_property_by_name
argument_list|(
name|config
argument_list|,
literal|"range"
argument_list|,
name|writer
argument_list|)
operator|&&
name|gimp_config_serialize_property_by_name
argument_list|(
name|config
argument_list|,
literal|"cyan-red"
argument_list|,
name|writer
argument_list|)
operator|&&
name|gimp_config_serialize_property_by_name
argument_list|(
name|config
argument_list|,
literal|"magenta-green"
argument_list|,
name|writer
argument_list|)
operator|&&
name|gimp_config_serialize_property_by_name
argument_list|(
name|config
argument_list|,
literal|"yellow-blue"
argument_list|,
name|writer
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
break|break;
block|}
if|if
condition|(
name|success
condition|)
name|success
operator|=
name|gimp_config_serialize_property_by_name
argument_list|(
name|config
argument_list|,
literal|"preserve-luminosity"
argument_list|,
name|writer
argument_list|)
expr_stmt|;
name|bc_config
operator|->
name|range
operator|=
name|old_range
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_color_balance_config_deserialize (GimpConfig * config,GScanner * scanner,gint nest_level,gpointer data)
name|gimp_color_balance_config_deserialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|nest_level
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpColorBalanceConfig
modifier|*
name|cb_config
init|=
name|GIMP_COLOR_BALANCE_CONFIG
argument_list|(
name|config
argument_list|)
decl_stmt|;
name|GimpTransferMode
name|old_range
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|old_range
operator|=
name|cb_config
operator|->
name|range
expr_stmt|;
name|success
operator|=
name|gimp_config_deserialize_properties
argument_list|(
name|config
argument_list|,
name|scanner
argument_list|,
name|nest_level
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|config
argument_list|,
literal|"range"
argument_list|,
name|old_range
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_color_balance_config_equal (GimpConfig * a,GimpConfig * b)
name|gimp_color_balance_config_equal
parameter_list|(
name|GimpConfig
modifier|*
name|a
parameter_list|,
name|GimpConfig
modifier|*
name|b
parameter_list|)
block|{
name|GimpColorBalanceConfig
modifier|*
name|config_a
init|=
name|GIMP_COLOR_BALANCE_CONFIG
argument_list|(
name|a
argument_list|)
decl_stmt|;
name|GimpColorBalanceConfig
modifier|*
name|config_b
init|=
name|GIMP_COLOR_BALANCE_CONFIG
argument_list|(
name|b
argument_list|)
decl_stmt|;
name|GimpTransferMode
name|range
decl_stmt|;
for|for
control|(
name|range
operator|=
name|GIMP_TRANSFER_SHADOWS
init|;
name|range
operator|<=
name|GIMP_TRANSFER_HIGHLIGHTS
condition|;
name|range
operator|++
control|)
block|{
if|if
condition|(
name|config_a
operator|->
name|cyan_red
index|[
name|range
index|]
operator|!=
name|config_b
operator|->
name|cyan_red
index|[
name|range
index|]
operator|||
name|config_a
operator|->
name|magenta_green
index|[
name|range
index|]
operator|!=
name|config_b
operator|->
name|magenta_green
index|[
name|range
index|]
operator|||
name|config_a
operator|->
name|yellow_blue
index|[
name|range
index|]
operator|!=
name|config_b
operator|->
name|yellow_blue
index|[
name|range
index|]
condition|)
return|return
name|FALSE
return|;
block|}
comment|/* don't compare "range" */
if|if
condition|(
name|config_a
operator|->
name|preserve_luminosity
operator|!=
name|config_b
operator|->
name|preserve_luminosity
condition|)
return|return
name|FALSE
return|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_balance_config_reset (GimpConfig * config)
name|gimp_color_balance_config_reset
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpColorBalanceConfig
modifier|*
name|cb_config
init|=
name|GIMP_COLOR_BALANCE_CONFIG
argument_list|(
name|config
argument_list|)
decl_stmt|;
name|GimpTransferMode
name|range
decl_stmt|;
for|for
control|(
name|range
operator|=
name|GIMP_TRANSFER_SHADOWS
init|;
name|range
operator|<=
name|GIMP_TRANSFER_HIGHLIGHTS
condition|;
name|range
operator|++
control|)
block|{
name|cb_config
operator|->
name|range
operator|=
name|range
expr_stmt|;
name|gimp_color_balance_config_reset_range
argument_list|(
name|cb_config
argument_list|)
expr_stmt|;
block|}
name|gimp_config_reset_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"range"
argument_list|)
expr_stmt|;
name|gimp_config_reset_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"preserve-luminosity"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_color_balance_config_copy (GimpConfig * src,GimpConfig * dest,GParamFlags flags)
name|gimp_color_balance_config_copy
parameter_list|(
name|GimpConfig
modifier|*
name|src
parameter_list|,
name|GimpConfig
modifier|*
name|dest
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GimpColorBalanceConfig
modifier|*
name|src_config
init|=
name|GIMP_COLOR_BALANCE_CONFIG
argument_list|(
name|src
argument_list|)
decl_stmt|;
name|GimpColorBalanceConfig
modifier|*
name|dest_config
init|=
name|GIMP_COLOR_BALANCE_CONFIG
argument_list|(
name|dest
argument_list|)
decl_stmt|;
name|GimpTransferMode
name|range
decl_stmt|;
for|for
control|(
name|range
operator|=
name|GIMP_TRANSFER_SHADOWS
init|;
name|range
operator|<=
name|GIMP_TRANSFER_HIGHLIGHTS
condition|;
name|range
operator|++
control|)
block|{
name|dest_config
operator|->
name|cyan_red
index|[
name|range
index|]
operator|=
name|src_config
operator|->
name|cyan_red
index|[
name|range
index|]
expr_stmt|;
name|dest_config
operator|->
name|magenta_green
index|[
name|range
index|]
operator|=
name|src_config
operator|->
name|magenta_green
index|[
name|range
index|]
expr_stmt|;
name|dest_config
operator|->
name|yellow_blue
index|[
name|range
index|]
operator|=
name|src_config
operator|->
name|yellow_blue
index|[
name|range
index|]
expr_stmt|;
block|}
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|,
literal|"cyan-red"
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|,
literal|"magenta-green"
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|,
literal|"yellow-blue"
argument_list|)
expr_stmt|;
name|dest_config
operator|->
name|range
operator|=
name|src_config
operator|->
name|range
expr_stmt|;
name|dest_config
operator|->
name|preserve_luminosity
operator|=
name|src_config
operator|->
name|preserve_luminosity
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|,
literal|"range"
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|,
literal|"preserve-luminosity"
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_color_balance_config_reset_range (GimpColorBalanceConfig * config)
name|gimp_color_balance_config_reset_range
parameter_list|(
name|GimpColorBalanceConfig
modifier|*
name|config
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_BALANCE_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_reset_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"cyan-red"
argument_list|)
expr_stmt|;
name|gimp_config_reset_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"magenta-green"
argument_list|)
expr_stmt|;
name|gimp_config_reset_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"yellow-blue"
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

