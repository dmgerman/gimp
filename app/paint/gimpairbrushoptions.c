begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpairbrushoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|AIRBRUSH_DEFAULT_RATE
define|#
directive|define
name|AIRBRUSH_DEFAULT_RATE
value|80.0
end_define

begin_define
DECL|macro|AIRBRUSH_DEFAULT_FLOW
define|#
directive|define
name|AIRBRUSH_DEFAULT_FLOW
value|10.0
end_define

begin_define
DECL|macro|AIRBRUSH_DEFAULT_MOTION_ONLY
define|#
directive|define
name|AIRBRUSH_DEFAULT_MOTION_ONLY
value|FALSE
end_define

begin_enum
enum|enum
DECL|enum|__anon2b2b580f0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_RATE
name|PROP_RATE
block|,
DECL|enumerator|PROP_MOTION_ONLY
name|PROP_MOTION_ONLY
block|,
DECL|enumerator|PROP_FLOW
name|PROP_FLOW
block|,
DECL|enumerator|PROP_PRESSURE
name|PROP_PRESSURE
comment|/*for backwards copatibility of tool options*/
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_airbrush_options_set_property
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
name|gimp_airbrush_options_get_property
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
DECL|function|G_DEFINE_TYPE (GimpAirbrushOptions,gimp_airbrush_options,GIMP_TYPE_PAINT_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpAirbrushOptions
argument_list|,
argument|gimp_airbrush_options
argument_list|,
argument|GIMP_TYPE_PAINT_OPTIONS
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_airbrush_options_class_init
parameter_list|(
name|GimpAirbrushOptionsClass
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
name|gimp_airbrush_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_airbrush_options_get_property
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_RATE
argument_list|,
literal|"rate"
argument_list|,
name|C_
argument_list|(
literal|"airbrush-tool"
argument_list|,
literal|"Rate"
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|150.0
argument_list|,
name|AIRBRUSH_DEFAULT_RATE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_MOTION_ONLY
argument_list|,
literal|"motion-only"
argument_list|,
name|_
argument_list|(
literal|"Motion only"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|AIRBRUSH_DEFAULT_MOTION_ONLY
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_FLOW
argument_list|,
literal|"flow"
argument_list|,
name|_
argument_list|(
literal|"Flow"
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
name|AIRBRUSH_DEFAULT_FLOW
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
comment|/* backwads-compadibility prop for flow fomerly known as pressure */
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_PRESSURE
argument_list|,
literal|"pressure"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
name|AIRBRUSH_DEFAULT_FLOW
argument_list|,
name|GIMP_CONFIG_PARAM_IGNORE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_options_init (GimpAirbrushOptions * options)
name|gimp_airbrush_options_init
parameter_list|(
name|GimpAirbrushOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_airbrush_options_set_property
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
name|GimpAirbrushOptions
modifier|*
name|options
init|=
name|GIMP_AIRBRUSH_OPTIONS
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
name|PROP_RATE
case|:
name|options
operator|->
name|rate
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MOTION_ONLY
case|:
name|options
operator|->
name|motion_only
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESSURE
case|:
case|case
name|PROP_FLOW
case|:
name|options
operator|->
name|flow
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
name|void
DECL|function|gimp_airbrush_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_airbrush_options_get_property
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
name|GimpAirbrushOptions
modifier|*
name|options
init|=
name|GIMP_AIRBRUSH_OPTIONS
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
name|PROP_RATE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|rate
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MOTION_ONLY
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|motion_only
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESSURE
case|:
case|case
name|PROP_FLOW
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|flow
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

