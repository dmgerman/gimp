begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppaintinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpinkoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpink-blob.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29b3f9100103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SIZE
name|PROP_SIZE
block|,
DECL|enumerator|PROP_TILT_ANGLE
name|PROP_TILT_ANGLE
block|,
DECL|enumerator|PROP_SIZE_SENSITIVITY
name|PROP_SIZE_SENSITIVITY
block|,
DECL|enumerator|PROP_VEL_SENSITIVITY
name|PROP_VEL_SENSITIVITY
block|,
DECL|enumerator|PROP_TILT_SENSITIVITY
name|PROP_TILT_SENSITIVITY
block|,
DECL|enumerator|PROP_BLOB_TYPE
name|PROP_BLOB_TYPE
block|,
DECL|enumerator|PROP_BLOB_ASPECT
name|PROP_BLOB_ASPECT
block|,
DECL|enumerator|PROP_BLOB_ANGLE
name|PROP_BLOB_ANGLE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_ink_options_set_property
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
name|gimp_ink_options_get_property
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
DECL|function|G_DEFINE_TYPE (GimpInkOptions,gimp_ink_options,GIMP_TYPE_PAINT_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpInkOptions
argument_list|,
argument|gimp_ink_options
argument_list|,
argument|GIMP_TYPE_PAINT_OPTIONS
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_ink_options_class_init
parameter_list|(
name|GimpInkOptionsClass
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
name|gimp_ink_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_ink_options_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_SIZE
argument_list|,
literal|"size"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|200.0
argument_list|,
literal|16.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_TILT_ANGLE
argument_list|,
literal|"tilt-angle"
argument_list|,
name|NULL
argument_list|,
operator|-
literal|90.0
argument_list|,
literal|90.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_SIZE_SENSITIVITY
argument_list|,
literal|"size-sensitivity"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_VEL_SENSITIVITY
argument_list|,
literal|"vel-sensitivity"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.8
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_TILT_SENSITIVITY
argument_list|,
literal|"tilt-sensitivity"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.4
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_BLOB_TYPE
argument_list|,
literal|"blob-type"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_INK_BLOB_TYPE
argument_list|,
name|GIMP_INK_BLOB_TYPE_ELLIPSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_BLOB_ASPECT
argument_list|,
literal|"blob-aspect"
argument_list|,
name|NULL
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_BLOB_ANGLE
argument_list|,
literal|"blob-angle"
argument_list|,
name|NULL
argument_list|,
operator|-
literal|90.0
argument_list|,
literal|90.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ink_options_init (GimpInkOptions * options)
name|gimp_ink_options_init
parameter_list|(
name|GimpInkOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ink_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_ink_options_set_property
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
name|GimpInkOptions
modifier|*
name|options
init|=
name|GIMP_INK_OPTIONS
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
name|PROP_SIZE
case|:
name|options
operator|->
name|size
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TILT_ANGLE
case|:
name|options
operator|->
name|tilt_angle
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SIZE_SENSITIVITY
case|:
name|options
operator|->
name|size_sensitivity
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VEL_SENSITIVITY
case|:
name|options
operator|->
name|vel_sensitivity
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TILT_SENSITIVITY
case|:
name|options
operator|->
name|tilt_sensitivity
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BLOB_TYPE
case|:
name|options
operator|->
name|blob_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BLOB_ASPECT
case|:
name|options
operator|->
name|blob_aspect
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BLOB_ANGLE
case|:
name|options
operator|->
name|blob_angle
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
DECL|function|gimp_ink_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_ink_options_get_property
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
name|GimpInkOptions
modifier|*
name|options
init|=
name|GIMP_INK_OPTIONS
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
name|PROP_SIZE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TILT_ANGLE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|tilt_angle
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SIZE_SENSITIVITY
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|size_sensitivity
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VEL_SENSITIVITY
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|vel_sensitivity
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TILT_SENSITIVITY
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|tilt_sensitivity
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BLOB_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|blob_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BLOB_ASPECT
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|blob_aspect
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BLOB_ANGLE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|blob_angle
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

