begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplevelsconfig.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
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
file|"gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"base/gimphistogram.h"
end_include

begin_comment
comment|/*  temp cruft  */
end_comment

begin_include
include|#
directive|include
file|"base/levels.h"
end_include

begin_include
include|#
directive|include
file|"gimplevelsconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29ffe5210103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CHANNEL
name|PROP_CHANNEL
block|,
DECL|enumerator|PROP_GAMMA
name|PROP_GAMMA
block|,
DECL|enumerator|PROP_LOW_INPUT
name|PROP_LOW_INPUT
block|,
DECL|enumerator|PROP_HIGH_INPUT
name|PROP_HIGH_INPUT
block|,
DECL|enumerator|PROP_LOW_OUTPUT
name|PROP_LOW_OUTPUT
block|,
DECL|enumerator|PROP_HIGH_OUTPUT
name|PROP_HIGH_OUTPUT
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_levels_config_get_property
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
name|gimp_levels_config_set_property
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
DECL|function|G_DEFINE_TYPE (GimpLevelsConfig,gimp_levels_config,G_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpLevelsConfig
argument_list|,
argument|gimp_levels_config
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_levels_config_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_levels_config_class_init
parameter_list|(
name|GimpLevelsConfigClass
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
name|object_class
operator|->
name|set_property
operator|=
name|gimp_levels_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_levels_config_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CHANNEL
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"channel"
argument_list|,
literal|"Channel"
argument_list|,
literal|"The affected channel"
argument_list|,
name|GIMP_TYPE_HISTOGRAM_CHANNEL
argument_list|,
name|GIMP_HISTOGRAM_VALUE
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GAMMA
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"gamma"
argument_list|,
literal|"Gamma"
argument_list|,
literal|"Gamma"
argument_list|,
literal|0.1
argument_list|,
literal|10.0
argument_list|,
literal|1.0
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_LOW_INPUT
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"low-input"
argument_list|,
literal|"Low Input"
argument_list|,
literal|"Low Input"
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_HIGH_INPUT
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"high-input"
argument_list|,
literal|"High Input"
argument_list|,
literal|"High Input"
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_LOW_OUTPUT
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"low-output"
argument_list|,
literal|"Low Output"
argument_list|,
literal|"Low Output"
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_HIGH_OUTPUT
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"high-output"
argument_list|,
literal|"High Output"
argument_list|,
literal|"High Output"
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_levels_config_init (GimpLevelsConfig * self)
name|gimp_levels_config_init
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|self
parameter_list|)
block|{
name|gimp_levels_config_reset
argument_list|(
name|self
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_levels_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_levels_config_get_property
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
name|GimpLevelsConfig
modifier|*
name|self
init|=
name|GIMP_LEVELS_CONFIG
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
name|PROP_CHANNEL
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|channel
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GAMMA
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|gamma
index|[
name|self
operator|->
name|channel
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LOW_INPUT
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|low_input
index|[
name|self
operator|->
name|channel
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HIGH_INPUT
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|high_input
index|[
name|self
operator|->
name|channel
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LOW_OUTPUT
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|low_output
index|[
name|self
operator|->
name|channel
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HIGH_OUTPUT
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|high_output
index|[
name|self
operator|->
name|channel
index|]
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
DECL|function|gimp_levels_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_levels_config_set_property
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
name|GimpLevelsConfig
modifier|*
name|self
init|=
name|GIMP_LEVELS_CONFIG
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
name|PROP_CHANNEL
case|:
name|self
operator|->
name|channel
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GAMMA
case|:
name|self
operator|->
name|gamma
index|[
name|self
operator|->
name|channel
index|]
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LOW_INPUT
case|:
name|self
operator|->
name|low_input
index|[
name|self
operator|->
name|channel
index|]
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HIGH_INPUT
case|:
name|self
operator|->
name|high_input
index|[
name|self
operator|->
name|channel
index|]
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LOW_OUTPUT
case|:
name|self
operator|->
name|low_output
index|[
name|self
operator|->
name|channel
index|]
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HIGH_OUTPUT
case|:
name|self
operator|->
name|high_output
index|[
name|self
operator|->
name|channel
index|]
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
name|void
DECL|function|gimp_levels_config_reset (GimpLevelsConfig * config)
name|gimp_levels_config_reset
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpHistogramChannel
name|channel
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LEVELS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|config
operator|->
name|channel
operator|=
name|GIMP_HISTOGRAM_VALUE
expr_stmt|;
for|for
control|(
name|channel
operator|=
name|GIMP_HISTOGRAM_VALUE
init|;
name|channel
operator|<=
name|GIMP_HISTOGRAM_ALPHA
condition|;
name|channel
operator|++
control|)
block|{
name|gimp_levels_config_reset_channel
argument_list|(
name|config
argument_list|,
name|channel
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_levels_config_reset_channel (GimpLevelsConfig * config,GimpHistogramChannel channel)
name|gimp_levels_config_reset_channel
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LEVELS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|config
operator|->
name|gamma
index|[
name|channel
index|]
operator|=
literal|1.0
expr_stmt|;
name|config
operator|->
name|low_input
index|[
name|channel
index|]
operator|=
literal|0.0
expr_stmt|;
name|config
operator|->
name|high_input
index|[
name|channel
index|]
operator|=
literal|1.0
expr_stmt|;
name|config
operator|->
name|low_output
index|[
name|channel
index|]
operator|=
literal|0.0
expr_stmt|;
name|config
operator|->
name|high_output
index|[
name|channel
index|]
operator|=
literal|1.0
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_levels_config_stretch (GimpLevelsConfig * config,GimpHistogram * histogram,gboolean is_color)
name|gimp_levels_config_stretch
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|,
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|gboolean
name|is_color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LEVELS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|histogram
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|is_color
condition|)
block|{
name|GimpHistogramChannel
name|channel
decl_stmt|;
comment|/*  Set the overall value to defaults  */
name|gimp_levels_config_reset_channel
argument_list|(
name|config
argument_list|,
name|GIMP_HISTOGRAM_VALUE
argument_list|)
expr_stmt|;
for|for
control|(
name|channel
operator|=
name|GIMP_HISTOGRAM_RED
init|;
name|channel
operator|<=
name|GIMP_HISTOGRAM_BLUE
condition|;
name|channel
operator|++
control|)
name|gimp_levels_config_stretch_channel
argument_list|(
name|config
argument_list|,
name|histogram
argument_list|,
name|channel
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_levels_config_stretch_channel
argument_list|(
name|config
argument_list|,
name|histogram
argument_list|,
name|GIMP_HISTOGRAM_VALUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_levels_config_stretch_channel (GimpLevelsConfig * config,GimpHistogram * histogram,GimpHistogramChannel channel)
name|gimp_levels_config_stretch_channel
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|,
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|)
block|{
name|gdouble
name|count
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LEVELS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|histogram
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|config
operator|->
name|gamma
index|[
name|channel
index|]
operator|=
literal|1.0
expr_stmt|;
name|config
operator|->
name|low_output
index|[
name|channel
index|]
operator|=
literal|0.0
expr_stmt|;
name|config
operator|->
name|high_output
index|[
name|channel
index|]
operator|=
literal|1.0
expr_stmt|;
name|count
operator|=
name|gimp_histogram_get_count
argument_list|(
name|histogram
argument_list|,
name|channel
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
if|if
condition|(
name|count
operator|==
literal|0.0
condition|)
block|{
name|config
operator|->
name|low_input
index|[
name|channel
index|]
operator|=
literal|0.0
expr_stmt|;
name|config
operator|->
name|high_input
index|[
name|channel
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
else|else
block|{
name|gdouble
name|new_count
decl_stmt|;
name|gdouble
name|percentage
decl_stmt|;
name|gdouble
name|next_percentage
decl_stmt|;
comment|/*  Set the low input  */
name|new_count
operator|=
literal|0.0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|255
condition|;
name|i
operator|++
control|)
block|{
name|new_count
operator|+=
name|gimp_histogram_get_value
argument_list|(
name|histogram
argument_list|,
name|channel
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|percentage
operator|=
name|new_count
operator|/
name|count
expr_stmt|;
name|next_percentage
operator|=
operator|(
name|new_count
operator|+
name|gimp_histogram_get_value
argument_list|(
name|histogram
argument_list|,
name|channel
argument_list|,
name|i
operator|+
literal|1
argument_list|)
operator|)
operator|/
name|count
expr_stmt|;
if|if
condition|(
name|fabs
argument_list|(
name|percentage
operator|-
literal|0.006
argument_list|)
operator|<
name|fabs
argument_list|(
name|next_percentage
operator|-
literal|0.006
argument_list|)
condition|)
block|{
name|config
operator|->
name|low_input
index|[
name|channel
index|]
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|i
operator|+
literal|1
argument_list|)
operator|/
literal|255.0
expr_stmt|;
break|break;
block|}
block|}
comment|/*  Set the high input  */
name|new_count
operator|=
literal|0.0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|255
init|;
name|i
operator|>
literal|0
condition|;
name|i
operator|--
control|)
block|{
name|new_count
operator|+=
name|gimp_histogram_get_value
argument_list|(
name|histogram
argument_list|,
name|channel
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|percentage
operator|=
name|new_count
operator|/
name|count
expr_stmt|;
name|next_percentage
operator|=
operator|(
name|new_count
operator|+
name|gimp_histogram_get_value
argument_list|(
name|histogram
argument_list|,
name|channel
argument_list|,
name|i
operator|-
literal|1
argument_list|)
operator|)
operator|/
name|count
expr_stmt|;
if|if
condition|(
name|fabs
argument_list|(
name|percentage
operator|-
literal|0.006
argument_list|)
operator|<
name|fabs
argument_list|(
name|next_percentage
operator|-
literal|0.006
argument_list|)
condition|)
block|{
name|config
operator|->
name|high_input
index|[
name|channel
index|]
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|i
operator|-
literal|1
argument_list|)
operator|/
literal|255.0
expr_stmt|;
break|break;
block|}
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|gimp_levels_config_input_from_color (GimpHistogramChannel channel,const GimpRGB * color)
name|gimp_levels_config_input_from_color
parameter_list|(
name|GimpHistogramChannel
name|channel
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
switch|switch
condition|(
name|channel
condition|)
block|{
case|case
name|GIMP_HISTOGRAM_VALUE
case|:
return|return
name|MAX
argument_list|(
name|MAX
argument_list|(
name|color
operator|->
name|r
argument_list|,
name|color
operator|->
name|g
argument_list|)
argument_list|,
name|color
operator|->
name|b
argument_list|)
return|;
case|case
name|GIMP_HISTOGRAM_RED
case|:
return|return
name|color
operator|->
name|r
return|;
case|case
name|GIMP_HISTOGRAM_GREEN
case|:
return|return
name|color
operator|->
name|g
return|;
case|case
name|GIMP_HISTOGRAM_BLUE
case|:
return|return
name|color
operator|->
name|b
return|;
case|case
name|GIMP_HISTOGRAM_ALPHA
case|:
return|return
name|color
operator|->
name|a
return|;
case|case
name|GIMP_HISTOGRAM_RGB
case|:
return|return
name|MIN
argument_list|(
name|MIN
argument_list|(
name|color
operator|->
name|r
argument_list|,
name|color
operator|->
name|g
argument_list|)
argument_list|,
name|color
operator|->
name|b
argument_list|)
return|;
block|}
return|return
literal|0.0
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_levels_config_adjust_by_colors (GimpLevelsConfig * config,GimpHistogramChannel channel,const GimpRGB * black,const GimpRGB * gray,const GimpRGB * white)
name|gimp_levels_config_adjust_by_colors
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|black
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|gray
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|white
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LEVELS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|black
condition|)
name|config
operator|->
name|low_input
index|[
name|channel
index|]
operator|=
name|gimp_levels_config_input_from_color
argument_list|(
name|channel
argument_list|,
name|black
argument_list|)
expr_stmt|;
if|if
condition|(
name|white
condition|)
name|config
operator|->
name|high_input
index|[
name|channel
index|]
operator|=
name|gimp_levels_config_input_from_color
argument_list|(
name|channel
argument_list|,
name|white
argument_list|)
expr_stmt|;
if|if
condition|(
name|gray
condition|)
block|{
name|gdouble
name|input
decl_stmt|;
name|gdouble
name|range
decl_stmt|;
name|gdouble
name|inten
decl_stmt|;
name|gdouble
name|out_light
decl_stmt|;
name|gdouble
name|lightness
decl_stmt|;
comment|/* Calculate lightness value */
name|lightness
operator|=
name|GIMP_RGB_LUMINANCE
argument_list|(
name|gray
operator|->
name|r
argument_list|,
name|gray
operator|->
name|g
argument_list|,
name|gray
operator|->
name|b
argument_list|)
expr_stmt|;
name|input
operator|=
name|gimp_levels_config_input_from_color
argument_list|(
name|channel
argument_list|,
name|gray
argument_list|)
expr_stmt|;
name|range
operator|=
name|config
operator|->
name|high_input
index|[
name|channel
index|]
operator|-
name|config
operator|->
name|low_input
index|[
name|channel
index|]
expr_stmt|;
if|if
condition|(
name|range
operator|<=
literal|0
condition|)
return|return;
name|input
operator|-=
name|config
operator|->
name|low_input
index|[
name|channel
index|]
expr_stmt|;
if|if
condition|(
name|input
operator|<
literal|0
condition|)
return|return;
comment|/* Normalize input and lightness */
name|inten
operator|=
name|input
operator|/
name|range
expr_stmt|;
name|out_light
operator|=
name|lightness
operator|/
name|range
expr_stmt|;
if|if
condition|(
name|out_light
operator|<=
literal|0
condition|)
return|return;
comment|/* Map selected color to corresponding lightness */
name|config
operator|->
name|gamma
index|[
name|channel
index|]
operator|=
name|log
argument_list|(
name|inten
argument_list|)
operator|/
name|log
argument_list|(
name|out_light
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_levels_config_load_cruft (GimpLevelsConfig * config,gpointer fp,GError ** error)
name|gimp_levels_config_load_cruft
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|,
name|gpointer
name|fp
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|FILE
modifier|*
name|file
init|=
name|fp
decl_stmt|;
name|gint
name|low_input
index|[
literal|5
index|]
decl_stmt|;
name|gint
name|high_input
index|[
literal|5
index|]
decl_stmt|;
name|gint
name|low_output
index|[
literal|5
index|]
decl_stmt|;
name|gint
name|high_output
index|[
literal|5
index|]
decl_stmt|;
name|gdouble
name|gamma
index|[
literal|5
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|fields
decl_stmt|;
name|gchar
name|buf
index|[
literal|50
index|]
decl_stmt|;
name|gchar
modifier|*
name|nptr
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LEVELS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|file
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|file
argument_list|)
operator|||
name|strcmp
argument_list|(
name|buf
argument_list|,
literal|"# GIMP Levels File\n"
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_PARSE
argument_list|,
name|_
argument_list|(
literal|"not a GIMP Levels file"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|5
condition|;
name|i
operator|++
control|)
block|{
name|fields
operator|=
name|fscanf
argument_list|(
name|file
argument_list|,
literal|"%d %d %d %d "
argument_list|,
operator|&
name|low_input
index|[
name|i
index|]
argument_list|,
operator|&
name|high_input
index|[
name|i
index|]
argument_list|,
operator|&
name|low_output
index|[
name|i
index|]
argument_list|,
operator|&
name|high_output
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|fields
operator|!=
literal|4
condition|)
goto|goto
name|error
goto|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|buf
argument_list|,
literal|50
argument_list|,
name|file
argument_list|)
condition|)
goto|goto
name|error
goto|;
name|gamma
index|[
name|i
index|]
operator|=
name|g_ascii_strtod
argument_list|(
name|buf
argument_list|,
operator|&
name|nptr
argument_list|)
expr_stmt|;
if|if
condition|(
name|buf
operator|==
name|nptr
operator|||
name|errno
operator|==
name|ERANGE
condition|)
goto|goto
name|error
goto|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|5
condition|;
name|i
operator|++
control|)
block|{
name|config
operator|->
name|low_input
index|[
name|i
index|]
operator|=
name|low_input
index|[
name|i
index|]
operator|/
literal|255.0
expr_stmt|;
name|config
operator|->
name|high_input
index|[
name|i
index|]
operator|=
name|high_input
index|[
name|i
index|]
operator|/
literal|255.0
expr_stmt|;
name|config
operator|->
name|low_output
index|[
name|i
index|]
operator|=
name|low_output
index|[
name|i
index|]
operator|/
literal|255.0
expr_stmt|;
name|config
operator|->
name|high_output
index|[
name|i
index|]
operator|=
name|high_output
index|[
name|i
index|]
operator|/
literal|255.0
expr_stmt|;
name|config
operator|->
name|gamma
index|[
name|i
index|]
operator|=
name|gamma
index|[
name|i
index|]
expr_stmt|;
block|}
return|return
name|TRUE
return|;
name|error
label|:
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_PARSE
argument_list|,
name|_
argument_list|(
literal|"parse error"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_levels_config_save_cruft (GimpLevelsConfig * config,gpointer fp)
name|gimp_levels_config_save_cruft
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|,
name|gpointer
name|fp
parameter_list|)
block|{
name|FILE
modifier|*
name|file
init|=
name|fp
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LEVELS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|file
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"# GIMP Levels File\n"
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
literal|5
condition|;
name|i
operator|++
control|)
block|{
name|gchar
name|buf
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"%d %d %d %d %s\n"
argument_list|,
call|(
name|gint
call|)
argument_list|(
name|config
operator|->
name|low_input
index|[
name|i
index|]
operator|*
literal|255.999
argument_list|)
argument_list|,
call|(
name|gint
call|)
argument_list|(
name|config
operator|->
name|high_input
index|[
name|i
index|]
operator|*
literal|255.999
argument_list|)
argument_list|,
call|(
name|gint
call|)
argument_list|(
name|config
operator|->
name|low_output
index|[
name|i
index|]
operator|*
literal|255.999
argument_list|)
argument_list|,
call|(
name|gint
call|)
argument_list|(
name|config
operator|->
name|high_output
index|[
name|i
index|]
operator|*
literal|255.999
argument_list|)
argument_list|,
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|config
operator|->
name|gamma
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  temp cruft  */
end_comment

begin_function
name|void
DECL|function|gimp_levels_config_to_cruft (GimpLevelsConfig * config,Levels * cruft,gboolean is_color)
name|gimp_levels_config_to_cruft
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|,
name|Levels
modifier|*
name|cruft
parameter_list|,
name|gboolean
name|is_color
parameter_list|)
block|{
name|GimpHistogramChannel
name|channel
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LEVELS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|cruft
operator|!=
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|channel
operator|=
name|GIMP_HISTOGRAM_VALUE
init|;
name|channel
operator|<=
name|GIMP_HISTOGRAM_ALPHA
condition|;
name|channel
operator|++
control|)
block|{
name|cruft
operator|->
name|gamma
index|[
name|channel
index|]
operator|=
name|config
operator|->
name|gamma
index|[
name|channel
index|]
expr_stmt|;
name|cruft
operator|->
name|low_input
index|[
name|channel
index|]
operator|=
name|config
operator|->
name|low_input
index|[
name|channel
index|]
operator|*
literal|255.999
expr_stmt|;
name|cruft
operator|->
name|high_input
index|[
name|channel
index|]
operator|=
name|config
operator|->
name|high_input
index|[
name|channel
index|]
operator|*
literal|255.999
expr_stmt|;
name|cruft
operator|->
name|low_output
index|[
name|channel
index|]
operator|=
name|config
operator|->
name|low_output
index|[
name|channel
index|]
operator|*
literal|255.999
expr_stmt|;
name|cruft
operator|->
name|high_output
index|[
name|channel
index|]
operator|=
name|config
operator|->
name|high_output
index|[
name|channel
index|]
operator|*
literal|255.999
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|is_color
condition|)
block|{
name|cruft
operator|->
name|gamma
index|[
literal|1
index|]
operator|=
name|cruft
operator|->
name|gamma
index|[
name|GIMP_HISTOGRAM_ALPHA
index|]
expr_stmt|;
name|cruft
operator|->
name|low_input
index|[
literal|1
index|]
operator|=
name|cruft
operator|->
name|low_input
index|[
name|GIMP_HISTOGRAM_ALPHA
index|]
expr_stmt|;
name|cruft
operator|->
name|high_input
index|[
literal|1
index|]
operator|=
name|cruft
operator|->
name|high_input
index|[
name|GIMP_HISTOGRAM_ALPHA
index|]
expr_stmt|;
name|cruft
operator|->
name|low_output
index|[
literal|1
index|]
operator|=
name|cruft
operator|->
name|low_output
index|[
name|GIMP_HISTOGRAM_ALPHA
index|]
expr_stmt|;
name|cruft
operator|->
name|high_output
index|[
literal|1
index|]
operator|=
name|cruft
operator|->
name|high_output
index|[
name|GIMP_HISTOGRAM_ALPHA
index|]
expr_stmt|;
block|}
block|}
end_function

end_unit

