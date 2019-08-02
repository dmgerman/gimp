begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * Object properties serialization routines  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfigtypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfigwriter.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-iface.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-path.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-serialize.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-utils.h"
end_include

begin_comment
comment|/**  * SECTION: gimpconfig-serialize  * @title: GimpConfig-serialize  * @short_description: Serializing for libgimpconfig.  *  * Serializing interface for libgimpconfig.  **/
end_comment

begin_function_decl
specifier|static
name|gboolean
name|gimp_config_serialize_rgb
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
name|has_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_config_serialize_properties:  * @config: a #GimpConfig.  * @writer: a #GimpConfigWriter.  *  * This function writes all object properties to the @writer.  *  * Returns: %TRUE if serialization succeeded, %FALSE otherwise  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_serialize_properties (GimpConfig * config,GimpConfigWriter * writer)
name|gimp_config_serialize_properties
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
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
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|klass
operator|=
name|G_OBJECT_GET_CLASS
argument_list|(
name|config
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
init|=
name|property_specs
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_SERIALIZE
operator|)
condition|)
continue|continue;
if|if
condition|(
operator|!
name|gimp_config_serialize_property
argument_list|(
name|config
argument_list|,
name|prop_spec
argument_list|,
name|writer
argument_list|)
condition|)
return|return
name|FALSE
return|;
block|}
name|g_free
argument_list|(
name|property_specs
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_serialize_changed_properties:  * @config: a #GimpConfig.  * @writer: a #GimpConfigWriter.  *  * This function writes all object properties that have been changed from  * their default values to the @writer.  *  * Returns: %TRUE if serialization succeeded, %FALSE otherwise  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_serialize_changed_properties (GimpConfig * config,GimpConfigWriter * writer)
name|gimp_config_serialize_changed_properties
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
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
name|G_VALUE_INIT
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|klass
operator|=
name|G_OBJECT_GET_CLASS
argument_list|(
name|config
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
init|=
name|property_specs
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_SERIALIZE
operator|)
condition|)
continue|continue;
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
name|G_OBJECT
argument_list|(
name|config
argument_list|)
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
operator|!
name|g_param_value_defaults
argument_list|(
name|prop_spec
argument_list|,
operator|&
name|value
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_config_serialize_property
argument_list|(
name|config
argument_list|,
name|prop_spec
argument_list|,
name|writer
argument_list|)
condition|)
return|return
name|FALSE
return|;
block|}
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|property_specs
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_serialize_property:  * @config:     a #GimpConfig.  * @param_spec: a #GParamSpec.  * @writer:     a #GimpConfigWriter.  *  * This function serializes a single object property to the @writer.  *  * Returns: %TRUE if serialization succeeded, %FALSE otherwise  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_serialize_property (GimpConfig * config,GParamSpec * param_spec,GimpConfigWriter * writer)
name|gimp_config_serialize_property
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
block|{
name|GimpConfigInterface
modifier|*
name|config_iface
init|=
name|NULL
decl_stmt|;
name|GimpConfigInterface
modifier|*
name|parent_iface
init|=
name|NULL
decl_stmt|;
name|GValue
name|value
init|=
name|G_VALUE_INIT
decl_stmt|;
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|param_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_SERIALIZE
operator|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|param_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_IGNORE
condition|)
return|return
name|TRUE
return|;
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
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|param_spec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|param_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_DEFAULTS
operator|&&
name|g_param_value_defaults
argument_list|(
name|param_spec
argument_list|,
operator|&
name|value
argument_list|)
condition|)
block|{
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|G_TYPE_IS_OBJECT
argument_list|(
name|param_spec
operator|->
name|owner_type
argument_list|)
condition|)
block|{
name|GTypeClass
modifier|*
name|owner_class
init|=
name|g_type_class_peek
argument_list|(
name|param_spec
operator|->
name|owner_type
argument_list|)
decl_stmt|;
name|config_iface
operator|=
name|g_type_interface_peek
argument_list|(
name|owner_class
argument_list|,
name|GIMP_TYPE_CONFIG
argument_list|)
expr_stmt|;
comment|/*  We must call serialize_property() *only* if the *exact* class        *  which implements it is param_spec->owner_type's class.        *        *  Therefore, we ask param_spec->owner_type's immediate parent class        *  for it's GimpConfigInterface and check if we get a different        *  pointer.        *        *  (if the pointers are the same, param_spec->owner_type's        *   GimpConfigInterface is inherited from one of it's parent classes        *   and thus not able to handle param_spec->owner_type's properties).        */
if|if
condition|(
name|config_iface
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
expr_stmt|;
name|parent_iface
operator|=
name|g_type_interface_peek
argument_list|(
name|owner_parent_class
argument_list|,
name|GIMP_TYPE_CONFIG
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|config_iface
operator|&&
name|config_iface
operator|!=
name|parent_iface
operator|&&
comment|/* see comment above */
name|config_iface
operator|->
name|serialize_property
operator|&&
name|config_iface
operator|->
name|serialize_property
argument_list|(
name|config
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
name|writer
argument_list|)
condition|)
block|{
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/*  If there is no serialize_property() method *or* if it returned    *  FALSE, continue with the default implementation    */
if|if
condition|(
operator|!
name|success
condition|)
block|{
if|if
condition|(
name|G_VALUE_HOLDS_OBJECT
argument_list|(
operator|&
name|value
argument_list|)
operator|&&
name|G_VALUE_TYPE
argument_list|(
operator|&
name|value
argument_list|)
operator|!=
name|G_TYPE_FILE
condition|)
block|{
name|GimpConfigInterface
modifier|*
name|config_iface
init|=
name|NULL
decl_stmt|;
name|GimpConfig
modifier|*
name|prop_object
decl_stmt|;
name|prop_object
operator|=
name|g_value_get_object
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|prop_object
condition|)
name|config_iface
operator|=
name|GIMP_CONFIG_GET_INTERFACE
argument_list|(
name|prop_object
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|config_iface
condition|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
name|param_spec
operator|->
name|name
argument_list|)
expr_stmt|;
comment|/*  if the object property is not GIMP_CONFIG_PARAM_AGGREGATE,                *  deserializing will need to know the exact type                *  in order to create the object                */
if|if
condition|(
operator|!
operator|(
name|param_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_AGGREGATE
operator|)
condition|)
block|{
name|GType
name|object_type
init|=
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|prop_object
argument_list|)
decl_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|g_type_name
argument_list|(
name|object_type
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|success
operator|=
name|config_iface
operator|->
name|serialize
argument_list|(
name|prop_object
argument_list|,
name|writer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
else|else
name|gimp_config_writer_revert
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|GString
modifier|*
name|str
init|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_VALUE_HOLDS_RGB
argument_list|(
operator|&
name|value
argument_list|)
condition|)
block|{
name|gboolean
name|has_alpha
init|=
name|gimp_param_spec_rgb_has_alpha
argument_list|(
name|param_spec
argument_list|)
decl_stmt|;
name|success
operator|=
name|gimp_config_serialize_rgb
argument_list|(
operator|&
name|value
argument_list|,
name|str
argument_list|,
name|has_alpha
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|gimp_config_serialize_value
argument_list|(
operator|&
name|value
argument_list|,
name|str
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
name|param_spec
operator|->
name|name
argument_list|)
expr_stmt|;
name|gimp_config_writer_print
argument_list|(
name|writer
argument_list|,
name|str
operator|->
name|str
argument_list|,
name|str
operator|->
name|len
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
name|g_string_free
argument_list|(
name|str
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|success
condition|)
block|{
comment|/* don't warn for empty string properties */
if|if
condition|(
name|G_VALUE_HOLDS_STRING
argument_list|(
operator|&
name|value
argument_list|)
condition|)
block|{
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"couldn't serialize property %s::%s of type %s"
argument_list|,
name|g_type_name
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|config
argument_list|)
argument_list|)
argument_list|,
name|param_spec
operator|->
name|name
argument_list|,
name|g_type_name
argument_list|(
name|param_spec
operator|->
name|value_type
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_serialize_property_by_name:  * @config:    a #GimpConfig.  * @prop_name: the property's name.  * @writer:    a #GimpConfigWriter.  *  * This function serializes a single object property to the @writer.  *  * Returns: %TRUE if serialization succeeded, %FALSE otherwise  *  * Since: 2.6  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_serialize_property_by_name (GimpConfig * config,const gchar * prop_name,GimpConfigWriter * writer)
name|gimp_config_serialize_property_by_name
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prop_name
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|pspec
decl_stmt|;
name|pspec
operator|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|config
argument_list|)
argument_list|,
name|prop_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pspec
condition|)
return|return
name|FALSE
return|;
return|return
name|gimp_config_serialize_property
argument_list|(
name|config
argument_list|,
name|pspec
argument_list|,
name|writer
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_serialize_value:  * @value: a #GValue.  * @str: a #GString.  * @escaped: whether to escape string values.  *  * This utility function appends a string representation of #GValue to @str.  *  * Returns: %TRUE if serialization succeeded, %FALSE otherwise.  *  * Since: 2.4  **/
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
init|=
name|g_type_class_peek
argument_list|(
name|G_VALUE_TYPE
argument_list|(
name|value
argument_list|)
argument_list|)
decl_stmt|;
name|GEnumValue
modifier|*
name|enum_value
init|=
name|g_enum_get_value
argument_list|(
name|enum_class
argument_list|,
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
argument_list|)
decl_stmt|;
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
name|gimp_config_string_append_escaped
argument_list|(
name|str
argument_list|,
name|cstr
argument_list|)
expr_stmt|;
else|else
name|g_string_append
argument_list|(
name|str
argument_list|,
name|cstr
argument_list|)
expr_stmt|;
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
name|g_ascii_dtostr
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
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
name|GIMP_VALUE_HOLDS_RGB
argument_list|(
name|value
argument_list|)
condition|)
block|{
return|return
name|gimp_config_serialize_rgb
argument_list|(
name|value
argument_list|,
name|str
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
if|if
condition|(
name|GIMP_VALUE_HOLDS_MATRIX2
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|GimpMatrix2
modifier|*
name|trafo
decl_stmt|;
name|trafo
operator|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|trafo
condition|)
block|{
name|gchar
name|buf
index|[
literal|4
index|]
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|k
operator|=
literal|0
init|;
name|i
operator|<
literal|2
condition|;
name|i
operator|++
control|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|2
condition|;
name|j
operator|++
operator|,
name|k
operator|++
control|)
name|g_ascii_dtostr
argument_list|(
name|buf
index|[
name|k
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
name|trafo
operator|->
name|coeff
index|[
name|i
index|]
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|"(matrix %s %s %s %s)"
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
block|}
else|else
block|{
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|"(matrix 1.0 1.0 1.0 1.0)"
argument_list|)
expr_stmt|;
block|}
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
name|GIMP_TYPE_VALUE_ARRAY
condition|)
block|{
name|GimpValueArray
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
name|length
init|=
name|gimp_value_array_length
argument_list|(
name|array
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|"%d"
argument_list|,
name|length
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
name|length
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
name|gimp_value_array_index
argument_list|(
name|array
argument_list|,
name|i
argument_list|)
argument_list|,
name|str
argument_list|,
name|TRUE
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
literal|"0"
argument_list|)
expr_stmt|;
block|}
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
name|G_TYPE_FILE
condition|)
block|{
name|GFile
modifier|*
name|file
init|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|file
condition|)
block|{
name|gchar
modifier|*
name|path
init|=
name|g_file_get_path
argument_list|(
name|file
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|unexpand
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|path
condition|)
block|{
name|unexpand
operator|=
name|gimp_config_path_unexpand
argument_list|(
name|path
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|unexpand
condition|)
block|{
if|if
condition|(
name|escaped
condition|)
name|gimp_config_string_append_escaped
argument_list|(
name|str
argument_list|,
name|unexpand
argument_list|)
expr_stmt|;
else|else
name|g_string_append
argument_list|(
name|str
argument_list|,
name|unexpand
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|unexpand
argument_list|)
expr_stmt|;
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
name|G_VALUE_INIT
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

begin_function
specifier|static
name|gboolean
DECL|function|gimp_config_serialize_rgb (const GValue * value,GString * str,gboolean has_alpha)
name|gimp_config_serialize_rgb
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
name|has_alpha
parameter_list|)
block|{
name|GimpRGB
modifier|*
name|rgb
decl_stmt|;
name|rgb
operator|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|rgb
condition|)
block|{
name|gchar
name|buf
index|[
literal|4
index|]
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|g_ascii_dtostr
argument_list|(
name|buf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
name|rgb
operator|->
name|r
argument_list|)
expr_stmt|;
name|g_ascii_dtostr
argument_list|(
name|buf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
name|rgb
operator|->
name|g
argument_list|)
expr_stmt|;
name|g_ascii_dtostr
argument_list|(
name|buf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
name|rgb
operator|->
name|b
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
name|g_ascii_dtostr
argument_list|(
name|buf
index|[
literal|3
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
name|rgb
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
block|}
else|else
block|{
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|"(color-rgb %s %s %s)"
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
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

