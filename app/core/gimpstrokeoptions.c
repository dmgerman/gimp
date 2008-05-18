begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpstrokeoptions.c  * Copyright (C) 2003 Simon Budig  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpdashpattern.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpstrokeoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28bf4d8a0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_STYLE
name|PROP_STYLE
block|,
DECL|enumerator|PROP_WIDTH
name|PROP_WIDTH
block|,
DECL|enumerator|PROP_UNIT
name|PROP_UNIT
block|,
DECL|enumerator|PROP_CAP_STYLE
name|PROP_CAP_STYLE
block|,
DECL|enumerator|PROP_JOIN_STYLE
name|PROP_JOIN_STYLE
block|,
DECL|enumerator|PROP_MITER_LIMIT
name|PROP_MITER_LIMIT
block|,
DECL|enumerator|PROP_ANTIALIAS
name|PROP_ANTIALIAS
block|,
DECL|enumerator|PROP_DASH_UNIT
name|PROP_DASH_UNIT
block|,
DECL|enumerator|PROP_DASH_OFFSET
name|PROP_DASH_OFFSET
block|,
DECL|enumerator|PROP_DASH_INFO
name|PROP_DASH_INFO
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon28bf4d8a0203
block|{
DECL|enumerator|DASH_INFO_CHANGED
name|DASH_INFO_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_stroke_options_set_property
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
name|gimp_stroke_options_get_property
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

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpStrokeOptions
argument_list|,
argument|gimp_stroke_options
argument_list|,
argument|GIMP_TYPE_CONTEXT
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|guint
name|stroke_options_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_options_class_init (GimpStrokeOptionsClass * klass)
name|gimp_stroke_options_class_init
parameter_list|(
name|GimpStrokeOptionsClass
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
name|GParamSpec
modifier|*
name|array_spec
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_stroke_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_stroke_options_get_property
expr_stmt|;
name|klass
operator|->
name|dash_info_changed
operator|=
name|NULL
expr_stmt|;
name|stroke_options_signals
index|[
name|DASH_INFO_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"dash-info-changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpStrokeOptionsClass
argument_list|,
name|dash_info_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__ENUM
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_DASH_PRESET
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_STYLE
argument_list|,
literal|"style"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_STROKE_STYLE
argument_list|,
name|GIMP_STROKE_STYLE_SOLID
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_WIDTH
argument_list|,
literal|"width"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|2000.0
argument_list|,
literal|6.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_UNIT
argument_list|(
name|object_class
argument_list|,
name|PROP_UNIT
argument_list|,
literal|"unit"
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_CAP_STYLE
argument_list|,
literal|"cap-style"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CAP_STYLE
argument_list|,
name|GIMP_CAP_BUTT
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_JOIN_STYLE
argument_list|,
literal|"join-style"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_JOIN_STYLE
argument_list|,
name|GIMP_JOIN_MITER
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_MITER_LIMIT
argument_list|,
literal|"miter-limit"
argument_list|,
name|_
argument_list|(
literal|"Convert a mitered join to a bevelled "
literal|"join if the miter would extend to a "
literal|"distance of more than miter-limit * "
literal|"line-width from the actual join point."
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|10.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_ANTIALIAS
argument_list|,
literal|"antialias"
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_DASH_OFFSET
argument_list|,
literal|"dash-offset"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|2000.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|array_spec
operator|=
name|g_param_spec_double
argument_list|(
literal|"dash-length"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|2000.0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_DASH_INFO
argument_list|,
name|g_param_spec_value_array
argument_list|(
literal|"dash-info"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|array_spec
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_FLAGS
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_options_init (GimpStrokeOptions * options)
name|gimp_stroke_options_init
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_stroke_options_set_property
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
name|GimpStrokeOptions
modifier|*
name|options
init|=
name|GIMP_STROKE_OPTIONS
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
name|PROP_STYLE
case|:
name|options
operator|->
name|style
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WIDTH
case|:
name|options
operator|->
name|width
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UNIT
case|:
name|options
operator|->
name|unit
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CAP_STYLE
case|:
name|options
operator|->
name|cap_style
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_JOIN_STYLE
case|:
name|options
operator|->
name|join_style
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MITER_LIMIT
case|:
name|options
operator|->
name|miter_limit
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ANTIALIAS
case|:
name|options
operator|->
name|antialias
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DASH_OFFSET
case|:
name|options
operator|->
name|dash_offset
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DASH_INFO
case|:
block|{
name|GValueArray
modifier|*
name|value_array
init|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
decl_stmt|;
name|GArray
modifier|*
name|pattern
decl_stmt|;
name|pattern
operator|=
name|gimp_dash_pattern_from_value_array
argument_list|(
name|value_array
argument_list|)
expr_stmt|;
name|gimp_stroke_options_take_dash_pattern
argument_list|(
name|options
argument_list|,
name|GIMP_DASH_CUSTOM
argument_list|,
name|pattern
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
DECL|function|gimp_stroke_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_stroke_options_get_property
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
name|GimpStrokeOptions
modifier|*
name|options
init|=
name|GIMP_STROKE_OPTIONS
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
name|PROP_STYLE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|style
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WIDTH
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CAP_STYLE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|cap_style
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_JOIN_STYLE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|join_style
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MITER_LIMIT
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|miter_limit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ANTIALIAS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|antialias
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DASH_OFFSET
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|dash_offset
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DASH_INFO
case|:
block|{
name|GValueArray
modifier|*
name|value_array
decl_stmt|;
name|value_array
operator|=
name|gimp_dash_pattern_to_value_array
argument_list|(
name|options
operator|->
name|dash_info
argument_list|)
expr_stmt|;
name|g_value_take_boxed
argument_list|(
name|value
argument_list|,
name|value_array
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

begin_comment
comment|/**  * gimp_stroke_options_take_dash_pattern:  * @options: a #GimpStrokeOptions object  * @preset: a value out of the #GimpDashPreset enum  * @pattern: a #GArray or %NULL if @preset is not %GIMP_DASH_CUSTOM  *  * Sets the dash pattern. Either a @preset is passed and @pattern is  * %NULL or @preset is %GIMP_DASH_CUSTOM and @pattern is the #GArray  * to use as the dash pattern. Note that this function takes ownership  * of the passed pattern.  */
end_comment

begin_function
name|void
DECL|function|gimp_stroke_options_take_dash_pattern (GimpStrokeOptions * options,GimpDashPreset preset,GArray * pattern)
name|gimp_stroke_options_take_dash_pattern
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|,
name|GimpDashPreset
name|preset
parameter_list|,
name|GArray
modifier|*
name|pattern
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|preset
operator|==
name|GIMP_DASH_CUSTOM
operator|||
name|pattern
operator|==
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|preset
operator|!=
name|GIMP_DASH_CUSTOM
condition|)
name|pattern
operator|=
name|gimp_dash_pattern_new_from_preset
argument_list|(
name|preset
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|dash_info
condition|)
name|gimp_dash_pattern_free
argument_list|(
name|options
operator|->
name|dash_info
argument_list|)
expr_stmt|;
name|options
operator|->
name|dash_info
operator|=
name|pattern
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
literal|"dash-info"
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|options
argument_list|,
name|stroke_options_signals
index|[
name|DASH_INFO_CHANGED
index|]
argument_list|,
literal|0
argument_list|,
name|preset
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

