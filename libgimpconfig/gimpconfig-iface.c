begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * Config file serialization and deserialization interface  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"libgimpbase/gimpbase.h"
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
file|"gimpconfig-deserialize.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-serialize.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpscanner.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/*  * The GimpConfig serialization and deserialization interface.  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_config_iface_base_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|config_iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_config_iface_serialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_config_iface_deserialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|nest_level
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpConfig
modifier|*
name|gimp_config_iface_duplicate
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_config_iface_equal
parameter_list|(
name|GimpConfig
modifier|*
name|a
parameter_list|,
name|GimpConfig
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_config_iface_reset
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_config_iface_copy
parameter_list|(
name|GimpConfig
modifier|*
name|src
parameter_list|,
name|GimpConfig
modifier|*
name|dest
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_config_interface_get_type (void)
name|gimp_config_interface_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|config_iface_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|config_iface_type
condition|)
block|{
specifier|const
name|GTypeInfo
name|config_iface_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpConfigInterface
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|gimp_config_iface_base_init
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|config_iface_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_INTERFACE
argument_list|,
literal|"GimpConfigInterface"
argument_list|,
operator|&
name|config_iface_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_interface_add_prerequisite
argument_list|(
name|config_iface_type
argument_list|,
name|G_TYPE_OBJECT
argument_list|)
expr_stmt|;
block|}
return|return
name|config_iface_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_config_iface_base_init (GimpConfigInterface * config_iface)
name|gimp_config_iface_base_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|config_iface
parameter_list|)
block|{
if|if
condition|(
operator|!
name|config_iface
operator|->
name|serialize
condition|)
block|{
name|config_iface
operator|->
name|serialize
operator|=
name|gimp_config_iface_serialize
expr_stmt|;
name|config_iface
operator|->
name|deserialize
operator|=
name|gimp_config_iface_deserialize
expr_stmt|;
name|config_iface
operator|->
name|duplicate
operator|=
name|gimp_config_iface_duplicate
expr_stmt|;
name|config_iface
operator|->
name|equal
operator|=
name|gimp_config_iface_equal
expr_stmt|;
name|config_iface
operator|->
name|reset
operator|=
name|gimp_config_iface_reset
expr_stmt|;
name|config_iface
operator|->
name|copy
operator|=
name|gimp_config_iface_copy
expr_stmt|;
block|}
comment|/*  always set these to NULL since we don't want to inherit them    *  from parent classes    */
name|config_iface
operator|->
name|serialize_property
operator|=
name|NULL
expr_stmt|;
name|config_iface
operator|->
name|deserialize_property
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_config_iface_serialize (GimpConfig * config,GimpConfigWriter * writer,gpointer data)
name|gimp_config_iface_serialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
return|return
name|gimp_config_serialize_properties
argument_list|(
name|config
argument_list|,
name|writer
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_config_iface_deserialize (GimpConfig * config,GScanner * scanner,gint nest_level,gpointer data)
name|gimp_config_iface_deserialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|nest_level
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
return|return
name|gimp_config_deserialize_properties
argument_list|(
name|config
argument_list|,
name|scanner
argument_list|,
name|nest_level
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpConfig
modifier|*
DECL|function|gimp_config_iface_duplicate (GimpConfig * config)
name|gimp_config_iface_duplicate
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
block|{
name|GObject
modifier|*
name|object
init|=
name|G_OBJECT
argument_list|(
name|config
argument_list|)
decl_stmt|;
name|GObjectClass
modifier|*
name|klass
init|=
name|G_OBJECT_GET_CLASS
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GParamSpec
modifier|*
modifier|*
name|property_specs
decl_stmt|;
name|guint
name|n_property_specs
decl_stmt|;
name|GParameter
modifier|*
name|construct_params
init|=
name|NULL
decl_stmt|;
name|gint
name|n_construct_params
init|=
literal|0
decl_stmt|;
name|guint
name|i
decl_stmt|;
name|GObject
modifier|*
name|dup
decl_stmt|;
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
name|construct_params
operator|=
name|g_new0
argument_list|(
name|GParameter
argument_list|,
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
init|=
name|property_specs
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|G_PARAM_READABLE
operator|)
operator|&&
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|G_PARAM_WRITABLE
operator|)
operator|&&
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|G_PARAM_CONSTRUCT_ONLY
operator|)
condition|)
block|{
name|GParameter
modifier|*
name|construct_param
decl_stmt|;
name|construct_param
operator|=
operator|&
name|construct_params
index|[
name|n_construct_params
operator|++
index|]
expr_stmt|;
name|construct_param
operator|->
name|name
operator|=
name|prop_spec
operator|->
name|name
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|construct_param
operator|->
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
name|construct_param
operator|->
name|value
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|property_specs
argument_list|)
expr_stmt|;
name|dup
operator|=
name|g_object_newv
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|object
argument_list|)
argument_list|,
name|n_construct_params
argument_list|,
name|construct_params
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
name|n_construct_params
condition|;
name|i
operator|++
control|)
name|g_value_unset
argument_list|(
operator|&
name|construct_params
index|[
name|i
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|construct_params
argument_list|)
expr_stmt|;
name|gimp_config_copy
argument_list|(
name|config
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|dup
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|GIMP_CONFIG
argument_list|(
name|dup
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_config_iface_equal (GimpConfig * a,GimpConfig * b)
name|gimp_config_iface_equal
parameter_list|(
name|GimpConfig
modifier|*
name|a
parameter_list|,
name|GimpConfig
modifier|*
name|b
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
name|gboolean
name|equal
init|=
name|TRUE
decl_stmt|;
name|klass
operator|=
name|G_OBJECT_GET_CLASS
argument_list|(
name|a
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
name|equal
operator|&&
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
name|a_value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|GValue
name|b_value
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
name|G_PARAM_READABLE
operator|)
condition|)
continue|continue;
name|g_value_init
argument_list|(
operator|&
name|a_value
argument_list|,
name|prop_spec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|b_value
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
name|a
argument_list|)
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
operator|&
name|a_value
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|G_OBJECT
argument_list|(
name|b
argument_list|)
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
operator|&
name|b_value
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_param_values_cmp
argument_list|(
name|prop_spec
argument_list|,
operator|&
name|a_value
argument_list|,
operator|&
name|b_value
argument_list|)
condition|)
block|{
if|if
condition|(
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_AGGREGATE
operator|)
operator|&&
name|G_IS_PARAM_SPEC_OBJECT
argument_list|(
name|prop_spec
argument_list|)
operator|&&
name|g_type_interface_peek
argument_list|(
name|g_type_class_peek
argument_list|(
name|prop_spec
operator|->
name|value_type
argument_list|)
argument_list|,
name|GIMP_TYPE_CONFIG
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_config_is_equal_to
argument_list|(
name|g_value_get_object
argument_list|(
operator|&
name|a_value
argument_list|)
argument_list|,
name|g_value_get_object
argument_list|(
operator|&
name|b_value
argument_list|)
argument_list|)
condition|)
block|{
name|equal
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
else|else
block|{
name|equal
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
name|g_value_unset
argument_list|(
operator|&
name|a_value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|b_value
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|property_specs
argument_list|)
expr_stmt|;
return|return
name|equal
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_config_iface_reset (GimpConfig * config)
name|gimp_config_iface_reset
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
block|{
name|gimp_config_reset_properties
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_config_iface_copy (GimpConfig * src,GimpConfig * dest,GParamFlags flags)
name|gimp_config_iface_copy
parameter_list|(
name|GimpConfig
modifier|*
name|src
parameter_list|,
name|GimpConfig
modifier|*
name|dest
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
return|return
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|src
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|,
name|flags
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_serialize_to_file:  * @config: a #GObject that implements the #GimpConfigInterface.  * @filename: the name of the file to write the configuration to.  * @header: optional file header (must be ASCII only)  * @footer: optional file footer (must be ASCII only)  * @data: user data passed to the serialize implementation.  * @error:  *  * Serializes the object properties of @config to the file specified  * by @filename. If a file with that name already exists, it is  * overwritten. Basically this function opens @filename for you and  * calls the serialize function of the @config's #GimpConfigInterface.  *  * Return value: %TRUE if serialization succeeded, %FALSE otherwise.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_serialize_to_file (GimpConfig * config,const gchar * filename,const gchar * header,const gchar * footer,gpointer data,GError ** error)
name|gimp_config_serialize_to_file
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|header
parameter_list|,
specifier|const
name|gchar
modifier|*
name|footer
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpConfigWriter
modifier|*
name|writer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
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
name|writer
operator|=
name|gimp_config_writer_new_file
argument_list|(
name|filename
argument_list|,
name|TRUE
argument_list|,
name|header
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|writer
condition|)
return|return
name|FALSE
return|;
name|GIMP_CONFIG_GET_INTERFACE
argument_list|(
name|config
argument_list|)
operator|->
name|serialize
argument_list|(
name|config
argument_list|,
name|writer
argument_list|,
name|data
argument_list|)
expr_stmt|;
return|return
name|gimp_config_writer_finish
argument_list|(
name|writer
argument_list|,
name|footer
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_serialize_to_fd:  * @config: a #GObject that implements the #GimpConfigInterface.  * @fd: a file descriptor, opened for writing  * @data: user data passed to the serialize implementation.  *  * Serializes the object properties of @config to the given file  * descriptor.  *  * Return value: %TRUE if serialization succeeded, %FALSE otherwise.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_serialize_to_fd (GimpConfig * config,gint fd,gpointer data)
name|gimp_config_serialize_to_fd
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|gint
name|fd
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpConfigWriter
modifier|*
name|writer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|fd
operator|>
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|writer
operator|=
name|gimp_config_writer_new_fd
argument_list|(
name|fd
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|writer
condition|)
return|return
name|FALSE
return|;
name|GIMP_CONFIG_GET_INTERFACE
argument_list|(
name|config
argument_list|)
operator|->
name|serialize
argument_list|(
name|config
argument_list|,
name|writer
argument_list|,
name|data
argument_list|)
expr_stmt|;
return|return
name|gimp_config_writer_finish
argument_list|(
name|writer
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_serialize_to_string:  * @config: a #GObject that implements the #GimpConfigInterface.  * @data: user data passed to the serialize implementation.  *  * Serializes the object properties of @config to a string.  *  * Return value: a newly allocated %NUL-terminated string.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_config_serialize_to_string (GimpConfig * config,gpointer data)
name|gimp_config_serialize_to_string
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpConfigWriter
modifier|*
name|writer
decl_stmt|;
name|GString
modifier|*
name|str
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|writer
operator|=
name|gimp_config_writer_new_string
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_GET_INTERFACE
argument_list|(
name|config
argument_list|)
operator|->
name|serialize
argument_list|(
name|config
argument_list|,
name|writer
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_config_writer_finish
argument_list|(
name|writer
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_string_free
argument_list|(
name|str
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_deserialize_file:  * @config: a #GObject that implements the #GimpConfigInterface.  * @filename: the name of the file to read configuration from.  * @data: user data passed to the deserialize implementation.  * @error:  *  * Opens the file specified by @filename, reads configuration data  * from it and configures @config accordingly. Basically this function  * creates a properly configured #GScanner for you and calls the  * deserialize function of the @config's #GimpConfigInterface.  *  * Return value: %TRUE if deserialization succeeded, %FALSE otherwise.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_deserialize_file (GimpConfig * config,const gchar * filename,gpointer data,GError ** error)
name|gimp_config_deserialize_file
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GScanner
modifier|*
name|scanner
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
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
name|scanner
operator|=
name|gimp_scanner_new_file
argument_list|(
name|filename
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|scanner
condition|)
return|return
name|FALSE
return|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|GIMP_CONFIG_GET_INTERFACE
argument_list|(
name|config
argument_list|)
operator|->
name|deserialize
argument_list|(
name|config
argument_list|,
name|scanner
argument_list|,
literal|0
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_scanner_destroy
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
name|g_assert
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|!=
name|NULL
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_deserialize_string:  * @config: a #GObject that implements the #GimpConfigInterface.  * @text: string to deserialize (in UTF-8 encoding)  * @text_len: length of @text in bytes or -1  * @data:  * @error:  *  * Configures @config from @text. Basically this function creates a  * properly configured #GScanner for you and calls the deserialize  * function of the @config's #GimpConfigInterface.  *  * Returns: %TRUE if deserialization succeeded, %FALSE otherwise.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_deserialize_string (GimpConfig * config,const gchar * text,gint text_len,gpointer data,GError ** error)
name|gimp_config_deserialize_string
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|text_len
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GScanner
modifier|*
name|scanner
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|text
operator|!=
name|NULL
operator|||
name|text_len
operator|==
literal|0
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
name|scanner
operator|=
name|gimp_scanner_new_string
argument_list|(
name|text
argument_list|,
name|text_len
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|GIMP_CONFIG_GET_INTERFACE
argument_list|(
name|config
argument_list|)
operator|->
name|deserialize
argument_list|(
name|config
argument_list|,
name|scanner
argument_list|,
literal|0
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_scanner_destroy
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
name|g_assert
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|!=
name|NULL
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_deserialize_return:  * @scanner:  * @expected_token:  * @nest_level:  *  * Returns:  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_deserialize_return (GScanner * scanner,GTokenType expected_token,gint nest_level)
name|gimp_config_deserialize_return
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GTokenType
name|expected_token
parameter_list|,
name|gint
name|nest_level
parameter_list|)
block|{
name|GTokenType
name|next_token
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|scanner
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|next_token
operator|=
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|expected_token
operator|!=
name|G_TOKEN_LEFT_PAREN
condition|)
block|{
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
name|g_scanner_unexp_token
argument_list|(
name|scanner
argument_list|,
name|expected_token
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"fatal parse error"
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
else|else
block|{
if|if
condition|(
name|nest_level
operator|>
literal|0
operator|&&
name|next_token
operator|==
name|G_TOKEN_RIGHT_PAREN
condition|)
block|{
return|return
name|TRUE
return|;
block|}
elseif|else
if|if
condition|(
name|next_token
operator|!=
name|G_TOKEN_EOF
condition|)
block|{
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
name|g_scanner_unexp_token
argument_list|(
name|scanner
argument_list|,
name|expected_token
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"fatal parse error"
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_duplicate:  * @config: a #GObject that implements the #GimpConfigInterface.  *  * Creates a copy of the passed object by copying all object  * properties. The default implementation of the #GimpConfigInterface  * only works for objects that are completely defined by their  * properties.  *  * Return value: the duplicated #GimpConfig object  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gpointer
DECL|function|gimp_config_duplicate (GimpConfig * config)
name|gimp_config_duplicate
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_CONFIG_GET_INTERFACE
argument_list|(
name|config
argument_list|)
operator|->
name|duplicate
argument_list|(
name|config
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_is_equal_to:  * @a: a #GObject that implements the #GimpConfigInterface.  * @b: another #GObject of the same type as @a.  *  * Compares the two objects. The default implementation of the  * #GimpConfigInterface compares the object properties and thus only  * works for objects that are completely defined by their  * properties.  *  * Return value: %TRUE if the two objects are equal.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_is_equal_to (GimpConfig * a,GimpConfig * b)
name|gimp_config_is_equal_to
parameter_list|(
name|GimpConfig
modifier|*
name|a
parameter_list|,
name|GimpConfig
modifier|*
name|b
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONFIG
argument_list|(
name|a
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONFIG
argument_list|(
name|b
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|a
argument_list|)
operator|==
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|b
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GIMP_CONFIG_GET_INTERFACE
argument_list|(
name|a
argument_list|)
operator|->
name|equal
argument_list|(
name|a
argument_list|,
name|b
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_reset:  * @config: a #GObject that implements the #GimpConfigInterface.  *  * Resets the object to its default state. The default implementation of the  * #GimpConfigInterface only works for objects that are completely defined by  * their properties.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_reset (GimpConfig * config)
name|gimp_config_reset
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_GET_INTERFACE
argument_list|(
name|config
argument_list|)
operator|->
name|reset
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_copy:  * @src: a #GObject that implements the #GimpConfigInterface.  * @dest: another #GObject of the same type as @a.  * @flags: a mask of GParamFlags  *  * Compares all read- and write-able properties from @src and @dest  * that have all @flags set. Differing values are then copied from  * @src to @dest. If @flags is 0, all differing read/write properties.  *  * Properties marked as "construct-only" are not touched.  *  * Return value: %TRUE if @dest was modified, %FALSE otherwise  *  * Since: GIMP 2.6  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_copy (GimpConfig * src,GimpConfig * dest,GParamFlags flags)
name|gimp_config_copy
parameter_list|(
name|GimpConfig
modifier|*
name|src
parameter_list|,
name|GimpConfig
modifier|*
name|dest
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|gboolean
name|changed
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONFIG
argument_list|(
name|src
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONFIG
argument_list|(
name|dest
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|src
argument_list|)
operator|==
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|dest
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|)
expr_stmt|;
name|changed
operator|=
name|GIMP_CONFIG_GET_INTERFACE
argument_list|(
name|src
argument_list|)
operator|->
name|copy
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|changed
return|;
block|}
end_function

end_unit

