begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Object propoerties serialization routines  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"gimpconfig-serialize.h"
end_include

begin_function
name|void
DECL|function|gimp_config_serialize_properties (GObject * object,FILE * file)
name|gimp_config_serialize_properties
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|FILE
modifier|*
name|file
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|klass
decl_stmt|;
name|GParamSpec
modifier|*
modifier|*
name|property_specs
decl_stmt|;
name|guint
name|n_property_specs
decl_stmt|;
name|guint
name|i
decl_stmt|;
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|klass
operator|=
name|G_OBJECT_GET_CLASS
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|property_specs
operator|=
name|g_object_class_list_properties
argument_list|(
name|klass
argument_list|,
operator|&
name|n_property_specs
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
name|n_property_specs
condition|;
name|i
operator|++
control|)
block|{
name|GParamSpec
modifier|*
name|prop_spec
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|cstr
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|prop_spec
operator|=
name|property_specs
index|[
name|i
index|]
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|G_PARAM_READWRITE
operator|)
condition|)
continue|continue;
name|str
operator|=
name|NULL
expr_stmt|;
name|cstr
operator|=
name|NULL
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|prop_spec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|object
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|G_VALUE_HOLDS_BOOLEAN
argument_list|(
operator|&
name|value
argument_list|)
condition|)
block|{
name|gboolean
name|bool
decl_stmt|;
name|bool
operator|=
name|g_value_get_boolean
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
name|cstr
operator|=
name|bool
condition|?
literal|"yes"
else|:
literal|"no"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_STRING
argument_list|(
operator|&
name|value
argument_list|)
condition|)
block|{
name|cstr
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|cstr
condition|)
block|{
name|gchar
modifier|*
name|s
init|=
name|g_strescape
argument_list|(
name|cstr
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
literal|"\"%s\""
argument_list|,
name|s
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|s
argument_list|)
expr_stmt|;
name|cstr
operator|=
name|NULL
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_ENUM
argument_list|(
operator|&
name|value
argument_list|)
condition|)
block|{
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
name|enum_class
operator|=
name|g_type_class_peek
argument_list|(
name|G_VALUE_TYPE
argument_list|(
operator|&
name|value
argument_list|)
argument_list|)
expr_stmt|;
name|enum_value
operator|=
name|g_enum_get_value
argument_list|(
name|G_ENUM_CLASS
argument_list|(
name|enum_class
argument_list|)
argument_list|,
name|g_value_get_enum
argument_list|(
operator|&
name|value
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|enum_value
operator|&&
name|enum_value
operator|->
name|value_nick
condition|)
name|cstr
operator|=
name|enum_value
operator|->
name|value_nick
expr_stmt|;
else|else
name|g_warning
argument_list|(
literal|"Couldn't get nick for enum_value of %s"
argument_list|,
name|G_ENUM_CLASS_TYPE_NAME
argument_list|(
name|enum_class
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_value_type_transformable
argument_list|(
name|G_VALUE_TYPE
argument_list|(
operator|&
name|value
argument_list|)
argument_list|,
name|G_TYPE_STRING
argument_list|)
condition|)
block|{
name|GValue
name|tmp_value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|tmp_value
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
name|g_value_transform
argument_list|(
operator|&
name|value
argument_list|,
operator|&
name|tmp_value
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_strescape
argument_list|(
name|g_value_get_string
argument_list|(
operator|&
name|tmp_value
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|tmp_value
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|cstr
operator|||
name|str
condition|)
block|{
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"(%s %s)\n"
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
name|cstr
condition|?
name|cstr
else|:
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

