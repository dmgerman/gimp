begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Config file serialization and deserialization interface  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *   * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<fcntl.h>
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
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

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
file|"gimpconfig-serialize.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-deserialize.h"
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
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*   * The GimpConfig serialization and deserialization interface.  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|gimp_config_iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_config_iface_serialize
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
name|GObject
modifier|*
name|object
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
name|GObject
modifier|*
name|gimp_config_iface_duplicate
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_config_iface_equal
parameter_list|(
name|GObject
modifier|*
name|a
parameter_list|,
name|GObject
modifier|*
name|b
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
specifier|static
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
name|gimp_config_iface_init
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
DECL|function|gimp_config_iface_init (GimpConfigInterface * gimp_config_iface)
name|gimp_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|gimp_config_iface
parameter_list|)
block|{
name|gimp_config_iface
operator|->
name|serialize
operator|=
name|gimp_config_iface_serialize
expr_stmt|;
name|gimp_config_iface
operator|->
name|deserialize
operator|=
name|gimp_config_iface_deserialize
expr_stmt|;
name|gimp_config_iface
operator|->
name|serialize_property
operator|=
name|NULL
expr_stmt|;
name|gimp_config_iface
operator|->
name|deserialize_property
operator|=
name|NULL
expr_stmt|;
name|gimp_config_iface
operator|->
name|duplicate
operator|=
name|gimp_config_iface_duplicate
expr_stmt|;
name|gimp_config_iface
operator|->
name|equal
operator|=
name|gimp_config_iface_equal
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_config_iface_serialize (GObject * object,gint fd,gint indent_level,gpointer data)
name|gimp_config_iface_serialize
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
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
return|return
name|gimp_config_serialize_properties
argument_list|(
name|object
argument_list|,
name|fd
argument_list|,
name|indent_level
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_config_iface_deserialize (GObject * object,GScanner * scanner,gint nest_level,gpointer data)
name|gimp_config_iface_deserialize
parameter_list|(
name|GObject
modifier|*
name|object
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
name|object
argument_list|,
name|scanner
argument_list|,
name|nest_level
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_config_iface_duplicate (GObject * object)
name|gimp_config_iface_duplicate
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GObject
modifier|*
name|dup
init|=
name|g_object_new
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|object
argument_list|)
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gimp_config_copy_properties
argument_list|(
name|object
argument_list|,
name|dup
argument_list|)
expr_stmt|;
return|return
name|dup
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_config_iface_equal (GObject * a,GObject * b)
name|gimp_config_iface_equal
parameter_list|(
name|GObject
modifier|*
name|a
parameter_list|,
name|GObject
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
name|a
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
name|b
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
operator|&
name|b_value
argument_list|)
expr_stmt|;
name|equal
operator|=
operator|(
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
operator|==
literal|0
operator|)
expr_stmt|;
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

begin_comment
comment|/**  * gimp_config_serialize:  * @object: a #GObject that implements the #GimpConfigInterface.  * @filename: the name of the file to write the configuration to.  * @header: optional file header (should be a comment)  * @footer: optional file footer (should be a comment)  * @data: user data passed to the serialize implementation.  * @error:  *   * Serializes the object properties of @object to the file specified  * by @filename. If a file with that name already exists, it is   * overwritten. Basically this function opens @filename for you and  * calls the serialize function of the @object's #GimpConfigInterface.  *  * Return value: %TRUE if serialization succeeded, %FALSE otherwise.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_serialize (GObject * object,const gchar * filename,const gchar * header,const gchar * footer,gpointer data,GError ** error)
name|gimp_config_serialize
parameter_list|(
name|GObject
modifier|*
name|object
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
name|GimpConfigInterface
modifier|*
name|gimp_config_iface
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|tmpname
decl_stmt|;
name|gint
name|fd
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
name|gimp_config_iface
operator|=
name|GIMP_GET_CONFIG_INTERFACE
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_config_iface
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tmpname
operator|=
name|g_strconcat
argument_list|(
name|filename
argument_list|,
literal|"XXXXXX"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fd
operator|=
name|g_mkstemp
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_WRITE
argument_list|,
name|_
argument_list|(
literal|"Failed to create temporary file for '%s': %s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|header
condition|)
name|success
operator|=
operator|(
name|write
argument_list|(
name|fd
argument_list|,
name|header
argument_list|,
name|strlen
argument_list|(
name|header
argument_list|)
argument_list|)
operator|!=
operator|-
literal|1
operator|&&
name|write
argument_list|(
name|fd
argument_list|,
literal|"\n"
argument_list|,
literal|1
argument_list|)
operator|!=
operator|-
literal|1
operator|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|success
operator|=
name|gimp_config_iface
operator|->
name|serialize
argument_list|(
name|object
argument_list|,
name|fd
argument_list|,
literal|0
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
operator|&&
name|footer
condition|)
name|success
operator|=
operator|(
name|write
argument_list|(
name|fd
argument_list|,
literal|"\n"
argument_list|,
literal|1
argument_list|)
operator|!=
operator|-
literal|1
operator|&&
name|write
argument_list|(
name|fd
argument_list|,
name|footer
argument_list|,
name|strlen
argument_list|(
name|footer
argument_list|)
argument_list|)
operator|!=
operator|-
literal|1
operator|&&
name|write
argument_list|(
name|fd
argument_list|,
literal|"\n"
argument_list|,
literal|1
argument_list|)
operator|!=
operator|-
literal|1
operator|)
expr_stmt|;
if|if
condition|(
name|close
argument_list|(
name|fd
argument_list|)
operator|!=
literal|0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
block|{
name|gchar
modifier|*
name|msg
decl_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
block|{
name|msg
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Error when writing to temporary file for '%s': %s\n"
literal|"The original file has not been touched."
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|msg
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Error when writing to temporary file for '%s': %s\n"
literal|"No file has been created."
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_WRITE
argument_list|,
name|msg
argument_list|)
expr_stmt|;
name|unlink
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
block|}
ifdef|#
directive|ifdef
name|G_OS_WIN32
comment|/* win32 rename can't overwrite */
if|if
condition|(
name|success
condition|)
name|unlink
argument_list|(
name|filename
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|success
operator|&&
name|rename
argument_list|(
name|tmpname
argument_list|,
name|filename
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_WRITE
argument_list|,
name|_
argument_list|(
literal|"Failed to create file '%s': %s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|unlink
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_deserialize:  * @object: a #GObject that implements the #GimpConfigInterface.  * @filename: the name of the file to read configuration from.  * @data: user data passed to the deserialize implementation.  * @error:   *   * Opens the file specified by @filename, reads configuration data  * from it and configures @object accordingly. Basically this function  * creates a properly configured #GScanner for you and calls the  * deserialize function of the @object's #GimpConfigInterface.  *   * Return value: %TRUE if deserialization succeeded, %FALSE otherwise.   **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_deserialize (GObject * object,const gchar * filename,gpointer data,GError ** error)
name|gimp_config_deserialize
parameter_list|(
name|GObject
modifier|*
name|object
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
name|GimpConfigInterface
modifier|*
name|gimp_config_iface
decl_stmt|;
name|GScanner
modifier|*
name|scanner
decl_stmt|;
name|gboolean
name|success
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
name|gimp_config_iface
operator|=
name|GIMP_GET_CONFIG_INTERFACE
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_config_iface
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|scanner
operator|=
name|gimp_scanner_new
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
name|success
operator|=
name|gimp_config_iface
operator|->
name|deserialize
argument_list|(
name|object
argument_list|,
name|scanner
argument_list|,
literal|0
argument_list|,
name|data
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

begin_function
name|GQuark
DECL|function|gimp_config_error_quark (void)
name|gimp_config_error_quark
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GQuark
name|q
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|q
operator|==
literal|0
condition|)
name|q
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-config-error-quark"
argument_list|)
expr_stmt|;
return|return
name|q
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_config_string_indent (GString * string,gint indent_level)
name|gimp_config_string_indent
parameter_list|(
name|GString
modifier|*
name|string
parameter_list|,
name|gint
name|indent_level
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|string
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|indent_level
operator|>=
literal|0
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
name|indent_level
condition|;
name|i
operator|++
control|)
name|g_string_append_len
argument_list|(
name|string
argument_list|,
literal|"    "
argument_list|,
literal|4
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_duplicate:  * @object: a #GObject that implements the #GimpConfigInterface.  *   * Creates a copy of the passed object by copying all object  * properties. The default implementation of the #GimpConfigInterface  * only works for objects that are completely defined by their  * properties.  *   * Return value: the duplicated #GObject.  **/
end_comment

begin_function
name|GObject
modifier|*
DECL|function|gimp_config_duplicate (GObject * object)
name|gimp_config_duplicate
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpConfigInterface
modifier|*
name|gimp_config_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_config_iface
operator|=
name|GIMP_GET_CONFIG_INTERFACE
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_config_iface
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|gimp_config_iface
operator|->
name|duplicate
argument_list|(
name|object
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_is_equal_to:  * @a: a #GObject that implements the #GimpConfigInterface.  * @b: another #GObject of the same type as @a.  *   * Compares the two objects. The default implementation of the  * #GimpConfigInterface compares the object properties and thus only  * works for objects that are completely defined by their  * properties.  *   * Return value: %TRUE if the two objects are equal.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_is_equal_to (GObject * a,GObject * b)
name|gimp_config_is_equal_to
parameter_list|(
name|GObject
modifier|*
name|a
parameter_list|,
name|GObject
modifier|*
name|b
parameter_list|)
block|{
name|GimpConfigInterface
modifier|*
name|gimp_config_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|a
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
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
name|gimp_config_iface
operator|=
name|GIMP_GET_CONFIG_INTERFACE
argument_list|(
name|a
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_config_iface
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|gimp_config_iface
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
comment|/*   * Code to store and lookup unknown tokens (string key/value pairs).  */
end_comment

begin_define
DECL|macro|GIMP_CONFIG_UNKNOWN_TOKENS
define|#
directive|define
name|GIMP_CONFIG_UNKNOWN_TOKENS
value|"gimp-config-unknown-tokens"
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon288f5c040108
block|{
DECL|member|key
name|gchar
modifier|*
name|key
decl_stmt|;
DECL|member|value
name|gchar
modifier|*
name|value
decl_stmt|;
DECL|typedef|GimpConfigToken
block|}
name|GimpConfigToken
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|gimp_config_destroy_unknown_tokens
parameter_list|(
name|GSList
modifier|*
name|unknown_tokens
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_config_add_unknown_token:  * @object: a #GObject.  * @key: a nul-terminated string to identify the value.  * @value: a nul-terminated string representing the value.  *   * This function allows to add arbitrary key/value pairs to a GObject.  * It's purpose is to attach additional data to a #GimpConfig object  * that can be stored along with the object properties when  * serializing the object to a configuration file. Please note however  * that the default gimp_config_serialize() implementation does not  * serialize unknown tokens.  *  * If you want to remove a key/value pair from the object, call this  * function with a %NULL @value.   **/
end_comment

begin_function
name|void
DECL|function|gimp_config_add_unknown_token (GObject * object,const gchar * key,const gchar * value)
name|gimp_config_add_unknown_token
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
block|{
name|GimpConfigToken
modifier|*
name|token
decl_stmt|;
name|GSList
modifier|*
name|unknown_tokens
decl_stmt|;
name|GSList
modifier|*
name|last
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|key
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|unknown_tokens
operator|=
operator|(
name|GSList
operator|*
operator|)
name|g_object_get_data
argument_list|(
name|object
argument_list|,
name|GIMP_CONFIG_UNKNOWN_TOKENS
argument_list|)
expr_stmt|;
for|for
control|(
name|last
operator|=
name|NULL
operator|,
name|list
operator|=
name|unknown_tokens
init|;
name|list
condition|;
name|last
operator|=
name|list
operator|,
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|token
operator|=
operator|(
name|GimpConfigToken
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|token
operator|->
name|key
argument_list|,
name|key
argument_list|)
operator|==
literal|0
condition|)
block|{
name|g_free
argument_list|(
name|token
operator|->
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
block|{
name|token
operator|->
name|value
operator|=
name|g_strdup
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
name|token
operator|->
name|key
argument_list|)
expr_stmt|;
name|unknown_tokens
operator|=
name|g_slist_remove
argument_list|(
name|unknown_tokens
argument_list|,
name|token
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|object
argument_list|,
name|GIMP_CONFIG_UNKNOWN_TOKENS
argument_list|,
name|unknown_tokens
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_config_destroy_unknown_tokens
argument_list|)
expr_stmt|;
block|}
return|return;
block|}
block|}
if|if
condition|(
operator|!
name|value
condition|)
return|return;
name|token
operator|=
name|g_new
argument_list|(
name|GimpConfigToken
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|token
operator|->
name|key
operator|=
name|g_strdup
argument_list|(
name|key
argument_list|)
expr_stmt|;
name|token
operator|->
name|value
operator|=
name|g_strdup
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|last
condition|)
block|{
name|g_slist_append
argument_list|(
name|last
argument_list|,
name|token
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|unknown_tokens
operator|=
name|g_slist_append
argument_list|(
name|NULL
argument_list|,
name|token
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|object
argument_list|,
name|GIMP_CONFIG_UNKNOWN_TOKENS
argument_list|,
name|unknown_tokens
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_config_destroy_unknown_tokens
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_config_lookup_unknown_token:  * @object: a #GObject.  * @key: a nul-terminated string to identify the value.  *   * This function retrieves data that was previously attached using  * gimp_config_add_unknown_token(). You should not free or modify  * the returned string.  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_config_lookup_unknown_token (GObject * object,const gchar * key)
name|gimp_config_lookup_unknown_token
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|key
parameter_list|)
block|{
name|GimpConfigToken
modifier|*
name|token
decl_stmt|;
name|GSList
modifier|*
name|unknown_tokens
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|key
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|unknown_tokens
operator|=
operator|(
name|GSList
operator|*
operator|)
name|g_object_get_data
argument_list|(
name|object
argument_list|,
name|GIMP_CONFIG_UNKNOWN_TOKENS
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|unknown_tokens
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|token
operator|=
operator|(
name|GimpConfigToken
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|token
operator|->
name|key
argument_list|,
name|key
argument_list|)
operator|==
literal|0
condition|)
return|return
name|token
operator|->
name|value
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_foreach_unknown_token:  * @object: a #GObject.  * @func: a function to call for each key/value pair.  * @user_data: data to pass to @func.  *   * Calls @func for each key/value stored with the @object using  * gimp_config_add_unknown_token().  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_foreach_unknown_token (GObject * object,GimpConfigForeachFunc func,gpointer user_data)
name|gimp_config_foreach_unknown_token
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GimpConfigForeachFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpConfigToken
modifier|*
name|token
decl_stmt|;
name|GSList
modifier|*
name|unknown_tokens
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|func
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|unknown_tokens
operator|=
operator|(
name|GSList
operator|*
operator|)
name|g_object_get_data
argument_list|(
name|object
argument_list|,
name|GIMP_CONFIG_UNKNOWN_TOKENS
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|unknown_tokens
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|token
operator|=
operator|(
name|GimpConfigToken
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|func
argument_list|(
name|token
operator|->
name|key
argument_list|,
name|token
operator|->
name|value
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_config_destroy_unknown_tokens (GSList * unknown_tokens)
name|gimp_config_destroy_unknown_tokens
parameter_list|(
name|GSList
modifier|*
name|unknown_tokens
parameter_list|)
block|{
name|GimpConfigToken
modifier|*
name|token
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|unknown_tokens
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|token
operator|=
operator|(
name|GimpConfigToken
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|g_free
argument_list|(
name|token
operator|->
name|key
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|token
operator|->
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|token
argument_list|)
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|unknown_tokens
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

