begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbrightnesscontrastconfig.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrightnesscontrastconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimplevelsconfig.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon27c964c90103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_BRIGHTNESS
name|PROP_BRIGHTNESS
block|,
DECL|enumerator|PROP_CONTRAST
name|PROP_CONTRAST
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_brightness_contrast_config_get_property
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
name|gimp_brightness_contrast_config_set_property
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

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpBrightnessContrastConfig,gimp_brightness_contrast_config,GIMP_TYPE_SETTINGS,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,NULL))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpBrightnessContrastConfig
argument_list|,
argument|gimp_brightness_contrast_config
argument_list|,
argument|GIMP_TYPE_SETTINGS
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG, NULL)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_brightness_contrast_config_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_brightness_contrast_config_class_init
parameter_list|(
name|GimpBrightnessContrastConfigClass
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
name|gimp_brightness_contrast_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_brightness_contrast_config_get_property
expr_stmt|;
name|viewable_class
operator|->
name|default_stock_id
operator|=
literal|"gimp-tool-brightness-contrast"
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_BRIGHTNESS
argument_list|,
literal|"brightness"
argument_list|,
literal|"Brightness"
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
name|PROP_CONTRAST
argument_list|,
literal|"contrast"
argument_list|,
literal|"Contrast"
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_contrast_config_init (GimpBrightnessContrastConfig * self)
name|gimp_brightness_contrast_config_init
parameter_list|(
name|GimpBrightnessContrastConfig
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_contrast_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_brightness_contrast_config_get_property
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
name|GimpBrightnessContrastConfig
modifier|*
name|self
init|=
name|GIMP_BRIGHTNESS_CONTRAST_CONFIG
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
name|PROP_BRIGHTNESS
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|brightness
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTRAST
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|contrast
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
DECL|function|gimp_brightness_contrast_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_brightness_contrast_config_set_property
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
name|GimpBrightnessContrastConfig
modifier|*
name|self
init|=
name|GIMP_BRIGHTNESS_CONTRAST_CONFIG
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
name|PROP_BRIGHTNESS
case|:
name|self
operator|->
name|brightness
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTRAST
case|:
name|self
operator|->
name|contrast
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpLevelsConfig
modifier|*
DECL|function|gimp_brightness_contrast_config_to_levels_config (GimpBrightnessContrastConfig * config)
name|gimp_brightness_contrast_config_to_levels_config
parameter_list|(
name|GimpBrightnessContrastConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpLevelsConfig
modifier|*
name|levels
decl_stmt|;
name|gdouble
name|brightness
decl_stmt|;
name|gdouble
name|slant
decl_stmt|;
name|gdouble
name|value
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRIGHTNESS_CONTRAST_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|levels
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_LEVELS_CONFIG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|brightness
operator|=
name|config
operator|->
name|brightness
operator|/
literal|2.0
expr_stmt|;
name|slant
operator|=
name|tan
argument_list|(
operator|(
name|config
operator|->
name|contrast
operator|+
literal|1
operator|)
operator|*
name|G_PI_4
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|brightness
operator|>=
literal|0
condition|)
block|{
name|value
operator|=
operator|-
literal|0.5
operator|*
name|slant
operator|+
name|brightness
operator|*
name|slant
operator|+
literal|0.5
expr_stmt|;
if|if
condition|(
name|value
operator|<
literal|0.0
condition|)
block|{
name|value
operator|=
literal|0.0
expr_stmt|;
comment|/* this slightly convoluted math follows by inverting the            * calculation of the brightness/contrast LUT in base/lut-funcs.h */
name|levels
operator|->
name|low_input
index|[
name|GIMP_HISTOGRAM_VALUE
index|]
operator|=
operator|(
operator|-
name|brightness
operator|*
name|slant
operator|+
literal|0.5
operator|*
name|slant
operator|-
literal|0.5
operator|)
operator|/
operator|(
name|slant
operator|-
name|brightness
operator|*
name|slant
operator|)
expr_stmt|;
block|}
name|levels
operator|->
name|low_output
index|[
name|GIMP_HISTOGRAM_VALUE
index|]
operator|=
name|value
expr_stmt|;
name|value
operator|=
literal|0.5
operator|*
name|slant
operator|+
literal|0.5
expr_stmt|;
if|if
condition|(
name|value
operator|>
literal|1.0
condition|)
block|{
name|value
operator|=
literal|1.0
expr_stmt|;
name|levels
operator|->
name|high_input
index|[
name|GIMP_HISTOGRAM_VALUE
index|]
operator|=
operator|(
operator|-
name|brightness
operator|*
name|slant
operator|+
literal|0.5
operator|*
name|slant
operator|+
literal|0.5
operator|)
operator|/
operator|(
name|slant
operator|-
name|brightness
operator|*
name|slant
operator|)
expr_stmt|;
block|}
name|levels
operator|->
name|high_output
index|[
name|GIMP_HISTOGRAM_VALUE
index|]
operator|=
name|value
expr_stmt|;
block|}
else|else
block|{
name|value
operator|=
literal|0.5
operator|-
literal|0.5
operator|*
name|slant
expr_stmt|;
if|if
condition|(
name|value
operator|<
literal|0.0
condition|)
block|{
name|value
operator|=
literal|0.0
expr_stmt|;
name|levels
operator|->
name|low_input
index|[
name|GIMP_HISTOGRAM_VALUE
index|]
operator|=
operator|(
literal|0.5
operator|*
name|slant
operator|-
literal|0.5
operator|)
operator|/
operator|(
name|slant
operator|+
name|brightness
operator|*
name|slant
operator|)
expr_stmt|;
block|}
name|levels
operator|->
name|low_output
index|[
name|GIMP_HISTOGRAM_VALUE
index|]
operator|=
name|value
expr_stmt|;
name|value
operator|=
name|slant
operator|*
name|brightness
operator|+
name|slant
operator|*
literal|0.5
operator|+
literal|0.5
expr_stmt|;
if|if
condition|(
name|value
operator|>
literal|1.0
condition|)
block|{
name|value
operator|=
literal|1.0
expr_stmt|;
name|levels
operator|->
name|high_input
index|[
name|GIMP_HISTOGRAM_VALUE
index|]
operator|=
operator|(
literal|0.5
operator|*
name|slant
operator|+
literal|0.5
operator|)
operator|/
operator|(
name|slant
operator|+
name|brightness
operator|*
name|slant
operator|)
expr_stmt|;
block|}
name|levels
operator|->
name|high_output
index|[
name|GIMP_HISTOGRAM_VALUE
index|]
operator|=
name|value
expr_stmt|;
block|}
return|return
name|levels
return|;
block|}
end_function

end_unit

