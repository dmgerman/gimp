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
file|"core/gimpmybrush.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppaintinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrushoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2aa108600103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_RADIUS
name|PROP_RADIUS
block|,
DECL|enumerator|PROP_OPAQUE
name|PROP_OPAQUE
block|,
DECL|enumerator|PROP_HARDNESS
name|PROP_HARDNESS
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_mybrush_options_set_property
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
name|gimp_mybrush_options_get_property
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
name|gimp_mybrush_options_mybrush_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpMybrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpMybrushOptions,gimp_mybrush_options,GIMP_TYPE_PAINT_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpMybrushOptions
argument_list|,
argument|gimp_mybrush_options
argument_list|,
argument|GIMP_TYPE_PAINT_OPTIONS
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_mybrush_options_class_init
parameter_list|(
name|GimpMybrushOptionsClass
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
name|GimpContextClass
modifier|*
name|context_class
init|=
name|GIMP_CONTEXT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_mybrush_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_mybrush_options_get_property
expr_stmt|;
name|context_class
operator|->
name|mybrush_changed
operator|=
name|gimp_mybrush_options_mybrush_changed
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_RADIUS
argument_list|,
literal|"radius"
argument_list|,
name|_
argument_list|(
literal|"Radius"
argument_list|)
argument_list|,
operator|-
literal|2.0
argument_list|,
literal|6.0
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
name|PROP_OPAQUE
argument_list|,
literal|"opaque"
argument_list|,
name|_
argument_list|(
literal|"Base Opacity"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|2.0
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
name|PROP_HARDNESS
argument_list|,
literal|"hardness"
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_options_init (GimpMybrushOptions * options)
name|gimp_mybrush_options_init
parameter_list|(
name|GimpMybrushOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_mybrush_options_set_property
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
name|GimpMybrushOptions
modifier|*
name|options
init|=
name|GIMP_MYBRUSH_OPTIONS
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
name|PROP_RADIUS
case|:
name|options
operator|->
name|radius
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HARDNESS
case|:
name|options
operator|->
name|hardness
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OPAQUE
case|:
name|options
operator|->
name|opaque
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
DECL|function|gimp_mybrush_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_mybrush_options_get_property
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
name|GimpMybrushOptions
modifier|*
name|options
init|=
name|GIMP_MYBRUSH_OPTIONS
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
name|PROP_RADIUS
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|radius
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OPAQUE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|opaque
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HARDNESS
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|hardness
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
DECL|function|gimp_mybrush_options_mybrush_changed (GimpContext * context,GimpMybrush * brush)
name|gimp_mybrush_options_mybrush_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpMybrush
modifier|*
name|brush
parameter_list|)
block|{
if|if
condition|(
name|brush
condition|)
name|g_object_set
argument_list|(
name|context
argument_list|,
literal|"radius"
argument_list|,
name|gimp_mybrush_get_radius
argument_list|(
name|brush
argument_list|)
argument_list|,
literal|"opaque"
argument_list|,
name|gimp_mybrush_get_opaque
argument_list|(
name|brush
argument_list|)
argument_list|,
literal|"hardness"
argument_list|,
name|gimp_mybrush_get_hardness
argument_list|(
name|brush
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

