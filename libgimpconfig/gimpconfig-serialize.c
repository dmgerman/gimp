begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Object properties serialization routines  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-serialize.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-utils.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_config_serialize_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GString
modifier|*
name|str
parameter_list|,
name|gboolean
name|escaped
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|serialize_unknown_token
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_config_serialize_properties:  * @object: a #GObject.   * @fd: a file descriptor to write to.  *   * This function writes all object properties to the file descriptor @fd.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_serialize_properties (GObject * object,gint fd,gint indent_level)
name|gimp_config_serialize_properties
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|gint
name|fd
parameter_list|,
name|gint
name|indent_level
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
name|GString
modifier|*
name|str
decl_stmt|;
name|gboolean
name|property_written
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
if|if
condition|(
operator|!
name|property_specs
condition|)
return|return
name|TRUE
return|;
name|str
operator|=
name|g_string_new
argument_list|(
name|NULL
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
name|GIMP_PARAM_SERIALIZE
operator|)
condition|)
continue|continue;
if|if
condition|(
name|property_written
condition|)
name|g_string_assign
argument_list|(
name|str
argument_list|,
literal|"\n"
argument_list|)
expr_stmt|;
else|else
name|g_string_assign
argument_list|(
name|str
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gimp_config_string_indent
argument_list|(
name|str
argument_list|,
name|indent_level
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|"(%s "
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_config_serialize_property
argument_list|(
name|object
argument_list|,
name|prop_spec
argument_list|,
name|str
argument_list|,
name|TRUE
argument_list|)
condition|)
block|{
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|")"
argument_list|)
expr_stmt|;
name|property_written
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|write
argument_list|(
name|fd
argument_list|,
name|str
operator|->
name|str
argument_list|,
name|str
operator|->
name|len
argument_list|)
operator|==
operator|-
literal|1
condition|)
return|return
name|FALSE
return|;
block|}
elseif|else
if|if
condition|(
name|prop_spec
operator|->
name|value_type
operator|!=
name|G_TYPE_STRING
condition|)
block|{
name|g_warning
argument_list|(
literal|"couldn't serialize property %s::%s of type %s"
argument_list|,
name|g_type_name
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|object
argument_list|)
argument_list|)
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
name|g_type_name
argument_list|(
name|prop_spec
operator|->
name|value_type
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|property_specs
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|str
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_serialize_properties:  * @new: a #GObject.   * @old: a #GObject of the same type as @new.   * @fd: a file descriptor to write to.  *   * This function compares the objects @new and @old and writes all properties  * of @new that have different values than @old to the file descriptor @fd.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_serialize_changed_properties (GObject * new,GObject * old,gint fd,gint indent_level)
name|gimp_config_serialize_changed_properties
parameter_list|(
name|GObject
modifier|*
name|new
parameter_list|,
name|GObject
modifier|*
name|old
parameter_list|,
name|gint
name|fd
parameter_list|,
name|gint
name|indent_level
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
name|GString
modifier|*
name|str
decl_stmt|;
name|gboolean
name|property_written
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|new
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|old
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|new
argument_list|)
operator|==
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|old
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|klass
operator|=
name|G_OBJECT_GET_CLASS
argument_list|(
name|new
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
if|if
condition|(
operator|!
name|property_specs
condition|)
return|return
name|TRUE
return|;
name|str
operator|=
name|g_string_new
argument_list|(
name|NULL
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
name|GValue
name|new_value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|GValue
name|old_value
init|=
block|{
literal|0
block|, }
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
name|GIMP_PARAM_SERIALIZE
operator|)
condition|)
continue|continue;
name|g_value_init
argument_list|(
operator|&
name|new_value
argument_list|,
name|prop_spec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|old_value
argument_list|,
name|prop_spec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|new
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
operator|&
name|new_value
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|old
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
operator|&
name|old_value
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_param_values_cmp
argument_list|(
name|prop_spec
argument_list|,
operator|&
name|new_value
argument_list|,
operator|&
name|old_value
argument_list|)
operator|!=
literal|0
condition|)
block|{
if|if
condition|(
name|property_written
condition|)
name|g_string_assign
argument_list|(
name|str
argument_list|,
literal|"\n"
argument_list|)
expr_stmt|;
else|else
name|g_string_assign
argument_list|(
name|str
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gimp_config_string_indent
argument_list|(
name|str
argument_list|,
name|indent_level
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|"(%s "
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_config_serialize_value
argument_list|(
operator|&
name|new_value
argument_list|,
name|str
argument_list|,
name|TRUE
argument_list|)
condition|)
block|{
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|")\n"
argument_list|)
expr_stmt|;
name|property_written
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|write
argument_list|(
name|fd
argument_list|,
name|str
operator|->
name|str
argument_list|,
name|str
operator|->
name|len
argument_list|)
operator|==
operator|-
literal|1
condition|)
return|return
name|FALSE
return|;
block|}
elseif|else
if|if
condition|(
name|prop_spec
operator|->
name|value_type
operator|!=
name|G_TYPE_STRING
condition|)
block|{
name|g_warning
argument_list|(
literal|"couldn't serialize property %s::%s of type %s"
argument_list|,
name|g_type_name
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|new
argument_list|)
argument_list|)
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
name|g_type_name
argument_list|(
name|prop_spec
operator|->
name|value_type
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|g_value_unset
argument_list|(
operator|&
name|new_value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|old_value
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|property_specs
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|str
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_serialize_value:  * @value: a #GValue.  * @str: a #Gstring.  * @escaped: whether to escape string values.  *  * This utility function appends a string representation of #GValue to @str.  *   * Return value: %TRUE if serialization succeeded, %FALSE otherwise.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_serialize_value (const GValue * value,GString * str,gboolean escaped)
name|gimp_config_serialize_value
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GString
modifier|*
name|str
parameter_list|,
name|gboolean
name|escaped
parameter_list|)
block|{
if|if
condition|(
name|G_VALUE_HOLDS_BOOLEAN
argument_list|(
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
name|value
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|str
argument_list|,
name|bool
condition|?
literal|"yes"
else|:
literal|"no"
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|G_VALUE_HOLDS_ENUM
argument_list|(
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
block|{
name|g_string_append
argument_list|(
name|str
argument_list|,
name|enum_value
operator|->
name|value_nick
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
else|else
block|{
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
return|return
name|FALSE
return|;
block|}
block|}
if|if
condition|(
name|G_VALUE_HOLDS_STRING
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|esc
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|cstr
init|=
name|g_value_get_string
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|cstr
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|escaped
condition|)
block|{
name|esc
operator|=
name|g_strescape
argument_list|(
name|cstr
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|"\"%s\""
argument_list|,
name|esc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|esc
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_string_append
argument_list|(
name|str
argument_list|,
name|cstr
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|G_VALUE_HOLDS_DOUBLE
argument_list|(
name|value
argument_list|)
operator|||
name|G_VALUE_HOLDS_FLOAT
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|gdouble
name|v_double
decl_stmt|;
name|gchar
name|buf
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
if|if
condition|(
name|G_VALUE_HOLDS_DOUBLE
argument_list|(
name|value
argument_list|)
condition|)
name|v_double
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
else|else
name|v_double
operator|=
operator|(
name|gdouble
operator|)
name|g_value_get_float
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%f"
argument_list|,
name|v_double
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|str
argument_list|,
name|buf
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|GIMP_VALUE_HOLDS_COLOR
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|GimpRGB
modifier|*
name|color
decl_stmt|;
name|gchar
name|buf
index|[
literal|4
index|]
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|color
operator|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|color
operator|->
name|r
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|color
operator|->
name|g
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|color
operator|->
name|b
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|3
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|color
operator|->
name|a
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|"(color-rgba %s %s %s %s)"
argument_list|,
name|buf
index|[
literal|0
index|]
argument_list|,
name|buf
index|[
literal|1
index|]
argument_list|,
name|buf
index|[
literal|2
index|]
argument_list|,
name|buf
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|G_VALUE_TYPE
argument_list|(
name|value
argument_list|)
operator|==
name|G_TYPE_VALUE_ARRAY
condition|)
block|{
name|GValueArray
modifier|*
name|array
decl_stmt|;
name|array
operator|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|array
condition|)
block|{
name|gint
name|i
decl_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|"%d"
argument_list|,
name|array
operator|->
name|n_values
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
name|array
operator|->
name|n_values
condition|;
name|i
operator|++
control|)
block|{
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|" "
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_serialize_value
argument_list|(
name|g_value_array_get_nth
argument_list|(
name|array
argument_list|,
name|i
argument_list|)
argument_list|,
name|str
argument_list|,
name|escaped
argument_list|)
condition|)
return|return
name|FALSE
return|;
block|}
block|}
else|else
block|{
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|"NULL"
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|g_value_type_transformable
argument_list|(
name|G_VALUE_TYPE
argument_list|(
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
name|value
argument_list|,
operator|&
name|tmp_value
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|str
argument_list|,
name|g_value_get_string
argument_list|(
operator|&
name|tmp_value
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|tmp_value
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_serialize_unknown_tokens:  * @object: a #GObject.  * @fd: a file descriptor to write to.  *   * Writes all unknown tokens attached to #object to the file descriptor @fd.  * See gimp_config_add_unknown_token().  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_serialize_unknown_tokens (GObject * object,gint fd,gint indent_level)
name|gimp_config_serialize_unknown_tokens
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|gint
name|fd
parameter_list|,
name|gint
name|indent_level
parameter_list|)
block|{
name|GString
modifier|*
name|str
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gimp_config_foreach_unknown_token
argument_list|(
name|object
argument_list|,
name|serialize_unknown_token
argument_list|,
name|str
argument_list|)
expr_stmt|;
return|return
operator|(
name|write
argument_list|(
name|fd
argument_list|,
name|str
operator|->
name|str
argument_list|,
name|str
operator|->
name|len
argument_list|)
operator|!=
operator|-
literal|1
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_config_serialize_property (GObject * object,GParamSpec * param_spec,GString * str,gboolean escaped)
name|gimp_config_serialize_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GString
modifier|*
name|str
parameter_list|,
name|gboolean
name|escaped
parameter_list|)
block|{
name|GTypeClass
modifier|*
name|owner_class
decl_stmt|;
name|GimpConfigInterface
modifier|*
name|gimp_config_iface
decl_stmt|;
name|GimpConfigInterface
modifier|*
name|parent_iface
decl_stmt|;
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gboolean
name|retval
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|param_spec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|object
argument_list|,
name|param_spec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|owner_class
operator|=
name|g_type_class_peek
argument_list|(
name|param_spec
operator|->
name|owner_type
argument_list|)
expr_stmt|;
name|gimp_config_iface
operator|=
name|g_type_interface_peek
argument_list|(
name|owner_class
argument_list|,
name|GIMP_TYPE_CONFIG_INTERFACE
argument_list|)
expr_stmt|;
comment|/*  We must call deserialize_property() *only* if the *exact* class    *  which implements it is param_spec->owner_type's class.    *    *  Therefore, we ask param_spec->owner_type's immediate parent class    *  for it's GimpConfigInterface and check if we get a different pointer.    *    *  (if the pointers are the same, param_spec->owner_type's    *   GimpConfigInterface is inherited from one of it's parent classes    *   and thus not able to handle param_spec->owner_type's properties).    */
if|if
condition|(
name|gimp_config_iface
condition|)
block|{
name|GTypeClass
modifier|*
name|owner_parent_class
decl_stmt|;
name|owner_parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|owner_class
argument_list|)
operator|,
name|parent_iface
operator|=
name|g_type_interface_peek
argument_list|(
name|owner_parent_class
argument_list|,
name|GIMP_TYPE_CONFIG_INTERFACE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_config_iface
operator|&&
name|gimp_config_iface
operator|!=
name|parent_iface
operator|&&
comment|/* see comment above */
name|gimp_config_iface
operator|->
name|serialize_property
operator|&&
name|gimp_config_iface
operator|->
name|serialize_property
argument_list|(
name|object
argument_list|,
name|param_spec
operator|->
name|param_id
argument_list|,
operator|(
specifier|const
name|GValue
operator|*
operator|)
operator|&
name|value
argument_list|,
name|param_spec
argument_list|,
name|str
argument_list|)
condition|)
block|{
name|retval
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|retval
operator|=
name|gimp_config_serialize_value
argument_list|(
operator|&
name|value
argument_list|,
name|str
argument_list|,
name|escaped
argument_list|)
expr_stmt|;
block|}
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|serialize_unknown_token (const gchar * key,const gchar * value,gpointer data)
name|serialize_unknown_token
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gchar
modifier|*
name|escaped
init|=
name|g_strescape
argument_list|(
name|value
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_string_append_printf
argument_list|(
operator|(
name|GString
operator|*
operator|)
name|data
argument_list|,
literal|"(%s \"%s\")\n"
argument_list|,
name|key
argument_list|,
name|escaped
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|escaped
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

