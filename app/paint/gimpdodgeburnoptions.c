begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpdodgeburnoptions.h"
end_include

begin_define
DECL|macro|DODGE_BURN_DEFAULT_TYPE
define|#
directive|define
name|DODGE_BURN_DEFAULT_TYPE
value|GIMP_DODGE
end_define

begin_define
DECL|macro|DODGE_BURN_DEFAULT_MODE
define|#
directive|define
name|DODGE_BURN_DEFAULT_MODE
value|GIMP_MIDTONES
end_define

begin_define
DECL|macro|DODGE_BURN_DEFAULT_EXPOSURE
define|#
directive|define
name|DODGE_BURN_DEFAULT_EXPOSURE
value|50.0
end_define

begin_enum
enum|enum
DECL|enum|__anon2c596ba10103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TYPE
name|PROP_TYPE
block|,
DECL|enumerator|PROP_MODE
name|PROP_MODE
block|,
DECL|enumerator|PROP_EXPOSURE
name|PROP_EXPOSURE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_dodge_burn_options_set_property
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
name|gimp_dodge_burn_options_get_property
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
DECL|function|G_DEFINE_TYPE (GimpDodgeBurnOptions,gimp_dodge_burn_options,GIMP_TYPE_PAINT_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDodgeBurnOptions
argument_list|,
argument|gimp_dodge_burn_options
argument_list|,
argument|GIMP_TYPE_PAINT_OPTIONS
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_dodge_burn_options_class_init
parameter_list|(
name|GimpDodgeBurnOptionsClass
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
name|gimp_dodge_burn_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_dodge_burn_options_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_TYPE
argument_list|,
literal|"type"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DODGE_BURN_TYPE
argument_list|,
name|DODGE_BURN_DEFAULT_TYPE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_MODE
argument_list|,
literal|"mode"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TRANSFER_MODE
argument_list|,
name|DODGE_BURN_DEFAULT_MODE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_EXPOSURE
argument_list|,
literal|"exposure"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
name|DODGE_BURN_DEFAULT_EXPOSURE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodge_burn_options_init (GimpDodgeBurnOptions * options)
name|gimp_dodge_burn_options_init
parameter_list|(
name|GimpDodgeBurnOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodge_burn_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_dodge_burn_options_set_property
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
name|GimpDodgeBurnOptions
modifier|*
name|options
init|=
name|GIMP_DODGE_BURN_OPTIONS
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
name|PROP_TYPE
case|:
name|options
operator|->
name|type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MODE
case|:
name|options
operator|->
name|mode
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EXPOSURE
case|:
name|options
operator|->
name|exposure
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
DECL|function|gimp_dodge_burn_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_dodge_burn_options_get_property
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
name|GimpDodgeBurnOptions
modifier|*
name|options
init|=
name|GIMP_DODGE_BURN_OPTIONS
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
name|PROP_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|mode
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EXPOSURE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|exposure
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

