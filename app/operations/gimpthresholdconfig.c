begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpthresholdconfig.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"gimpthresholdconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2974d1bd0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_LOW
name|PROP_LOW
block|,
DECL|enumerator|PROP_HIGH
name|PROP_HIGH
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_threshold_config_iface_init
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
name|gimp_threshold_config_get_property
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
name|gimp_threshold_config_set_property
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
name|gimp_threshold_config_equal
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

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpThresholdConfig,gimp_threshold_config,GIMP_TYPE_SETTINGS,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,gimp_threshold_config_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpThresholdConfig
argument_list|,
argument|gimp_threshold_config
argument_list|,
argument|GIMP_TYPE_SETTINGS
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_threshold_config_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_threshold_config_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_threshold_config_class_init
parameter_list|(
name|GimpThresholdConfigClass
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
name|gimp_threshold_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_threshold_config_get_property
expr_stmt|;
name|viewable_class
operator|->
name|default_icon_name
operator|=
literal|"gimp-tool-threshold"
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_LOW
argument_list|,
literal|"low"
argument_list|,
name|_
argument_list|(
literal|"Low threshold"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_HIGH
argument_list|,
literal|"high"
argument_list|,
name|_
argument_list|(
literal|"High threshold"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_threshold_config_iface_init (GimpConfigInterface * iface)
name|gimp_threshold_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|equal
operator|=
name|gimp_threshold_config_equal
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_threshold_config_init (GimpThresholdConfig * self)
name|gimp_threshold_config_init
parameter_list|(
name|GimpThresholdConfig
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_threshold_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_threshold_config_get_property
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
name|GimpThresholdConfig
modifier|*
name|self
init|=
name|GIMP_THRESHOLD_CONFIG
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
name|PROP_LOW
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|low
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HIGH
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|high
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
DECL|function|gimp_threshold_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_threshold_config_set_property
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
name|GimpThresholdConfig
modifier|*
name|self
init|=
name|GIMP_THRESHOLD_CONFIG
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
name|PROP_LOW
case|:
name|self
operator|->
name|low
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HIGH
case|:
name|self
operator|->
name|high
operator|=
name|g_value_get_double
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
DECL|function|gimp_threshold_config_equal (GimpConfig * a,GimpConfig * b)
name|gimp_threshold_config_equal
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
name|GimpThresholdConfig
modifier|*
name|config_a
init|=
name|GIMP_THRESHOLD_CONFIG
argument_list|(
name|a
argument_list|)
decl_stmt|;
name|GimpThresholdConfig
modifier|*
name|config_b
init|=
name|GIMP_THRESHOLD_CONFIG
argument_list|(
name|b
argument_list|)
decl_stmt|;
if|if
condition|(
name|config_a
operator|->
name|low
operator|!=
name|config_b
operator|->
name|low
operator|||
name|config_a
operator|->
name|high
operator|!=
name|config_b
operator|->
name|high
condition|)
block|{
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

