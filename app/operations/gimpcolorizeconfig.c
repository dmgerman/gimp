begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcolorizeconfig.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpcolorizeconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b3405700103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_HUE
name|PROP_HUE
block|,
DECL|enumerator|PROP_SATURATION
name|PROP_SATURATION
block|,
DECL|enumerator|PROP_LIGHTNESS
name|PROP_LIGHTNESS
block|,
DECL|enumerator|PROP_COLOR
name|PROP_COLOR
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_colorize_config_iface_init
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
name|gimp_colorize_config_get_property
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
name|gimp_colorize_config_set_property
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
name|gimp_colorize_config_equal
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
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpColorizeConfig,gimp_colorize_config,GIMP_TYPE_SETTINGS,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,gimp_colorize_config_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpColorizeConfig
argument_list|,
argument|gimp_colorize_config
argument_list|,
argument|GIMP_TYPE_SETTINGS
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_colorize_config_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_colorize_config_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_colorize_config_class_init
parameter_list|(
name|GimpColorizeConfigClass
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
name|GimpHSL
name|hsl
decl_stmt|;
name|GimpRGB
name|rgb
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_colorize_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_colorize_config_get_property
expr_stmt|;
name|viewable_class
operator|->
name|default_icon_name
operator|=
literal|"gimp-tool-colorize"
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_HUE
argument_list|,
literal|"hue"
argument_list|,
name|_
argument_list|(
literal|"Hue"
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
name|PROP_SATURATION
argument_list|,
literal|"saturation"
argument_list|,
name|_
argument_list|(
literal|"Saturation"
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
name|PROP_LIGHTNESS
argument_list|,
literal|"lightness"
argument_list|,
name|_
argument_list|(
literal|"Lightness"
argument_list|)
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
name|gimp_hsl_set
argument_list|(
operator|&
name|hsl
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gimp_hsl_set_alpha
argument_list|(
operator|&
name|hsl
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_hsl_to_rgb
argument_list|(
operator|&
name|hsl
argument_list|,
operator|&
name|rgb
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_COLOR
argument_list|,
name|gimp_param_spec_rgb
argument_list|(
literal|"color"
argument_list|,
literal|"Color"
argument_list|,
literal|"The color"
argument_list|,
name|FALSE
argument_list|,
operator|&
name|rgb
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_config_iface_init (GimpConfigInterface * iface)
name|gimp_colorize_config_iface_init
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
name|gimp_colorize_config_equal
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_config_init (GimpColorizeConfig * self)
name|gimp_colorize_config_init
parameter_list|(
name|GimpColorizeConfig
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_colorize_config_get_property
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
name|GimpColorizeConfig
modifier|*
name|self
init|=
name|GIMP_COLORIZE_CONFIG
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
name|PROP_HUE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|hue
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SATURATION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|saturation
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LIGHTNESS
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|lightness
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_COLOR
case|:
block|{
name|GimpHSL
name|hsl
decl_stmt|;
name|GimpRGB
name|rgb
decl_stmt|;
name|gimp_hsl_set
argument_list|(
operator|&
name|hsl
argument_list|,
name|self
operator|->
name|hue
argument_list|,
name|self
operator|->
name|saturation
argument_list|,
operator|(
name|self
operator|->
name|lightness
operator|+
literal|1.0
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|gimp_hsl_set_alpha
argument_list|(
operator|&
name|hsl
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_hsl_to_rgb
argument_list|(
operator|&
name|hsl
argument_list|,
operator|&
name|rgb
argument_list|)
expr_stmt|;
name|gimp_value_set_rgb
argument_list|(
name|value
argument_list|,
operator|&
name|rgb
argument_list|)
expr_stmt|;
block|}
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
DECL|function|gimp_colorize_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_colorize_config_set_property
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
name|GimpColorizeConfig
modifier|*
name|self
init|=
name|GIMP_COLORIZE_CONFIG
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
name|PROP_HUE
case|:
name|self
operator|->
name|hue
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"color"
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SATURATION
case|:
name|self
operator|->
name|saturation
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"color"
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LIGHTNESS
case|:
name|self
operator|->
name|lightness
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"color"
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_COLOR
case|:
block|{
name|GimpRGB
name|rgb
decl_stmt|;
name|GimpHSL
name|hsl
decl_stmt|;
name|gimp_value_get_rgb
argument_list|(
name|value
argument_list|,
operator|&
name|rgb
argument_list|)
expr_stmt|;
name|gimp_rgb_to_hsl
argument_list|(
operator|&
name|rgb
argument_list|,
operator|&
name|hsl
argument_list|)
expr_stmt|;
if|if
condition|(
name|hsl
operator|.
name|h
operator|==
operator|-
literal|1
condition|)
name|hsl
operator|.
name|h
operator|=
name|self
operator|->
name|hue
expr_stmt|;
if|if
condition|(
name|hsl
operator|.
name|l
operator|==
literal|0.0
operator|||
name|hsl
operator|.
name|l
operator|==
literal|1.0
condition|)
name|hsl
operator|.
name|s
operator|=
name|self
operator|->
name|saturation
expr_stmt|;
name|g_object_set
argument_list|(
name|self
argument_list|,
literal|"hue"
argument_list|,
name|hsl
operator|.
name|h
argument_list|,
literal|"saturation"
argument_list|,
name|hsl
operator|.
name|s
argument_list|,
literal|"lightness"
argument_list|,
name|hsl
operator|.
name|l
operator|*
literal|2.0
operator|-
literal|1.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
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
DECL|function|gimp_colorize_config_equal (GimpConfig * a,GimpConfig * b)
name|gimp_colorize_config_equal
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
name|GimpColorizeConfig
modifier|*
name|config_a
init|=
name|GIMP_COLORIZE_CONFIG
argument_list|(
name|a
argument_list|)
decl_stmt|;
name|GimpColorizeConfig
modifier|*
name|config_b
init|=
name|GIMP_COLORIZE_CONFIG
argument_list|(
name|b
argument_list|)
decl_stmt|;
if|if
condition|(
name|config_a
operator|->
name|hue
operator|!=
name|config_b
operator|->
name|hue
operator|||
name|config_a
operator|->
name|saturation
operator|!=
name|config_b
operator|->
name|saturation
operator|||
name|config_a
operator|->
name|lightness
operator|!=
name|config_b
operator|->
name|lightness
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

