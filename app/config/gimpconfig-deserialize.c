begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Object properties deserialization routines  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<fcntl.h>
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
file|"gimpconfig-deserialize.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-substitute.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-types.h"
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
comment|/*    *  All functions return G_TOKEN_RIGHT_PAREN on success,  *  the GTokenType they would have expected but didn't get  *  or G_TOKEN_NONE if they got the expected token but  *  couldn't parse it.  */
end_comment

begin_function_decl
specifier|static
name|GTokenType
name|gimp_config_deserialize_unknown
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GTokenType
name|gimp_config_deserialize_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GTokenType
name|gimp_config_deserialize_value
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GTokenType
name|gimp_config_deserialize_fundamental
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GTokenType
name|gimp_config_deserialize_enum
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GTokenType
name|gimp_config_deserialize_memsize
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GTokenType
name|gimp_config_deserialize_path
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GTokenType
name|gimp_config_deserialize_color
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GTokenType
name|gimp_config_deserialize_value_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GTokenType
name|gimp_config_deserialize_any
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|inline
name|gboolean
name|scanner_string_utf8_valid
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
specifier|const
name|gchar
modifier|*
name|token_name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_config_deserialize_properties:  * @object: a #GObject.  * @scanner: a #GScanner.  * @embedded_scope: %TRUE if a trailing ')' should not trigger a parse error.  * @store_unknown_tokens: %TRUE if you want to store unknown tokens.  *   * This function uses the @scanner to configure the properties of @object.  *  * The store_unknown_tokens parameter is a special feature for #GimpRc.  * If it set to %TRUE, unknown tokens (e.g. tokens that don't refer to  * a property of @object) with string values are attached to @object as  * unknown tokens. GimpConfig has a couple of functions to handle the  * attached key/value pairs.  *   * Return value:   **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_deserialize_properties (GObject * object,GScanner * scanner,gint nest_level,gboolean store_unknown_tokens)
name|gimp_config_deserialize_properties
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
name|gboolean
name|store_unknown_tokens
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
name|guint
name|scope_id
decl_stmt|;
name|guint
name|old_scope_id
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
name|GTokenType
name|next
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
name|scope_id
operator|=
name|g_type_qname
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|old_scope_id
operator|=
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
name|scope_id
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
name|prop_spec
operator|->
name|flags
operator|&
name|GIMP_PARAM_SERIALIZE
condition|)
block|{
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
name|prop_spec
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|property_specs
argument_list|)
expr_stmt|;
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
while|while
condition|(
name|TRUE
condition|)
block|{
name|next
operator|=
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|next
operator|!=
name|token
operator|&&
operator|!
operator|(
name|store_unknown_tokens
operator|&&
name|token
operator|==
name|G_TOKEN_SYMBOL
operator|&&
name|next
operator|==
name|G_TOKEN_IDENTIFIER
operator|)
condition|)
block|{
break|break;
block|}
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|token
condition|)
block|{
case|case
name|G_TOKEN_LEFT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_SYMBOL
expr_stmt|;
break|break;
case|case
name|G_TOKEN_IDENTIFIER
case|:
name|token
operator|=
name|gimp_config_deserialize_unknown
argument_list|(
name|object
argument_list|,
name|scanner
argument_list|)
expr_stmt|;
break|break;
case|case
name|G_TOKEN_SYMBOL
case|:
name|token
operator|=
name|gimp_config_deserialize_property
argument_list|(
name|object
argument_list|,
name|scanner
argument_list|)
expr_stmt|;
break|break;
case|case
name|G_TOKEN_RIGHT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
break|break;
default|default:
comment|/* do nothing */
break|break;
block|}
block|}
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
name|old_scope_id
argument_list|)
expr_stmt|;
comment|/* If store_unknown_tokens is TRUE but the unknown token value couldn't      be parsed the default error message is rather confusing.      We try to produce something more meaningful here ... */
if|if
condition|(
operator|(
name|store_unknown_tokens
operator|&&
name|token
operator|==
name|G_TOKEN_STRING
operator|&&
name|next
operator|==
name|G_TOKEN_IDENTIFIER
operator|)
condition|)
block|{
name|g_scanner_unexp_token
argument_list|(
name|scanner
argument_list|,
name|G_TOKEN_SYMBOL
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
return|return
name|gimp_config_deserialize_return
argument_list|(
name|scanner
argument_list|,
name|token
argument_list|,
name|nest_level
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|gimp_config_deserialize_unknown (GObject * object,GScanner * scanner)
name|gimp_config_deserialize_unknown
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
block|{
name|gchar
modifier|*
name|key
decl_stmt|;
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|G_TOKEN_STRING
condition|)
return|return
name|G_TOKEN_STRING
return|;
name|key
operator|=
name|g_strdup
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|)
expr_stmt|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|scanner_string_utf8_valid
argument_list|(
name|scanner
argument_list|,
name|key
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|key
argument_list|)
expr_stmt|;
return|return
name|G_TOKEN_NONE
return|;
block|}
name|gimp_config_add_unknown_token
argument_list|(
name|object
argument_list|,
name|key
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_string
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|key
argument_list|)
expr_stmt|;
return|return
name|G_TOKEN_RIGHT_PAREN
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|gimp_config_deserialize_property (GObject * object,GScanner * scanner)
name|gimp_config_deserialize_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GScanner
modifier|*
name|scanner
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
name|GParamSpec
modifier|*
name|prop_spec
decl_stmt|;
name|GTokenType
name|token
init|=
name|G_TOKEN_RIGHT_PAREN
decl_stmt|;
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|prop_spec
operator|=
name|G_PARAM_SPEC
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_symbol
argument_list|)
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
name|owner_class
operator|=
name|g_type_class_peek
argument_list|(
name|prop_spec
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
name|deserialize_property
operator|&&
name|gimp_config_iface
operator|->
name|deserialize_property
argument_list|(
name|object
argument_list|,
name|prop_spec
operator|->
name|param_id
argument_list|,
operator|&
name|value
argument_list|,
name|prop_spec
argument_list|,
name|scanner
argument_list|,
operator|&
name|token
argument_list|)
condition|)
block|{
comment|/* nop */
block|}
else|else
block|{
name|token
operator|=
name|gimp_config_deserialize_value
argument_list|(
operator|&
name|value
argument_list|,
name|object
argument_list|,
name|prop_spec
argument_list|,
name|scanner
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|token
operator|==
name|G_TOKEN_RIGHT_PAREN
operator|&&
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|token
condition|)
block|{
name|g_object_set_property
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
block|}
if|#
directive|if
name|CONFIG_DEBUG
else|else
block|{
name|g_warning
argument_list|(
literal|"couldn't deserialize property %s::%s of type %s"
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
endif|#
directive|endif
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
return|return
name|token
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|gimp_config_deserialize_value (GValue * value,GObject * object,GParamSpec * prop_spec,GScanner * scanner)
name|gimp_config_deserialize_value
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
block|{
if|if
condition|(
name|G_TYPE_FUNDAMENTAL
argument_list|(
name|prop_spec
operator|->
name|value_type
argument_list|)
operator|==
name|G_TYPE_ENUM
condition|)
block|{
return|return
name|gimp_config_deserialize_enum
argument_list|(
name|value
argument_list|,
name|prop_spec
argument_list|,
name|scanner
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|G_TYPE_IS_FUNDAMENTAL
argument_list|(
name|prop_spec
operator|->
name|value_type
argument_list|)
condition|)
block|{
return|return
name|gimp_config_deserialize_fundamental
argument_list|(
name|value
argument_list|,
name|prop_spec
argument_list|,
name|scanner
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|prop_spec
operator|->
name|value_type
operator|==
name|GIMP_TYPE_MEMSIZE
condition|)
block|{
return|return
name|gimp_config_deserialize_memsize
argument_list|(
name|value
argument_list|,
name|prop_spec
argument_list|,
name|scanner
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|prop_spec
operator|->
name|value_type
operator|==
name|GIMP_TYPE_PATH
condition|)
block|{
return|return
name|gimp_config_deserialize_path
argument_list|(
name|value
argument_list|,
name|object
argument_list|,
name|prop_spec
argument_list|,
name|scanner
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|prop_spec
operator|->
name|value_type
operator|==
name|GIMP_TYPE_COLOR
condition|)
block|{
return|return
name|gimp_config_deserialize_color
argument_list|(
name|value
argument_list|,
name|prop_spec
argument_list|,
name|scanner
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|prop_spec
operator|->
name|value_type
operator|==
name|G_TYPE_VALUE_ARRAY
condition|)
block|{
return|return
name|gimp_config_deserialize_value_array
argument_list|(
name|value
argument_list|,
name|object
argument_list|,
name|prop_spec
argument_list|,
name|scanner
argument_list|)
return|;
block|}
comment|/*  This fallback will only work for value_types that    *  can be transformed from a string value.    */
return|return
name|gimp_config_deserialize_any
argument_list|(
name|value
argument_list|,
name|prop_spec
argument_list|,
name|scanner
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|gimp_config_deserialize_fundamental (GValue * value,GParamSpec * prop_spec,GScanner * scanner)
name|gimp_config_deserialize_fundamental
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
block|{
name|GTokenType
name|token
decl_stmt|;
switch|switch
condition|(
name|G_TYPE_FUNDAMENTAL
argument_list|(
name|prop_spec
operator|->
name|value_type
argument_list|)
condition|)
block|{
case|case
name|G_TYPE_STRING
case|:
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
break|break;
case|case
name|G_TYPE_BOOLEAN
case|:
name|token
operator|=
name|G_TOKEN_IDENTIFIER
expr_stmt|;
break|break;
case|case
name|G_TYPE_INT
case|:
case|case
name|G_TYPE_UINT
case|:
case|case
name|G_TYPE_LONG
case|:
case|case
name|G_TYPE_ULONG
case|:
name|token
operator|=
name|G_TOKEN_INT
expr_stmt|;
break|break;
case|case
name|G_TYPE_FLOAT
case|:
case|case
name|G_TYPE_DOUBLE
case|:
name|token
operator|=
name|G_TOKEN_FLOAT
expr_stmt|;
break|break;
default|default:
name|token
operator|=
name|G_TOKEN_NONE
expr_stmt|;
name|g_assert_not_reached
argument_list|()
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|token
condition|)
return|return
name|token
return|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|G_TYPE_FUNDAMENTAL
argument_list|(
name|prop_spec
operator|->
name|value_type
argument_list|)
condition|)
block|{
case|case
name|G_TYPE_STRING
case|:
if|if
condition|(
name|scanner_string_utf8_valid
argument_list|(
name|scanner
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|)
condition|)
name|g_value_set_static_string
argument_list|(
name|value
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_string
argument_list|)
expr_stmt|;
else|else
return|return
name|G_TOKEN_NONE
return|;
break|break;
case|case
name|G_TYPE_BOOLEAN
case|:
if|if
condition|(
operator|!
name|g_ascii_strcasecmp
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|,
literal|"yes"
argument_list|)
operator|||
operator|!
name|g_ascii_strcasecmp
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|,
literal|"true"
argument_list|)
condition|)
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|g_ascii_strcasecmp
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|,
literal|"no"
argument_list|)
operator|||
operator|!
name|g_ascii_strcasecmp
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|,
literal|"false"
argument_list|)
condition|)
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
else|else
block|{
name|g_scanner_error
argument_list|(
name|scanner
argument_list|,
comment|/* please don't translate 'yes' and 'no' */
name|_
argument_list|(
literal|"expected 'yes' or 'no' for boolean token %s, got '%s'"
argument_list|)
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|)
expr_stmt|;
return|return
name|G_TOKEN_NONE
return|;
block|}
break|break;
case|case
name|G_TYPE_INT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_int
argument_list|)
expr_stmt|;
break|break;
case|case
name|G_TYPE_UINT
case|:
name|g_value_set_uint
argument_list|(
name|value
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_int
argument_list|)
expr_stmt|;
break|break;
case|case
name|G_TYPE_LONG
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_int
argument_list|)
expr_stmt|;
break|break;
case|case
name|G_TYPE_ULONG
case|:
name|g_value_set_uint
argument_list|(
name|value
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_int
argument_list|)
expr_stmt|;
break|break;
case|case
name|G_TYPE_FLOAT
case|:
name|g_value_set_float
argument_list|(
name|value
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_float
argument_list|)
expr_stmt|;
break|break;
case|case
name|G_TYPE_DOUBLE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_float
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
break|break;
block|}
return|return
name|G_TOKEN_RIGHT_PAREN
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|gimp_config_deserialize_enum (GValue * value,GParamSpec * prop_spec,GScanner * scanner)
name|gimp_config_deserialize_enum
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
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
switch|switch
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
condition|)
block|{
case|case
name|G_TOKEN_IDENTIFIER
case|:
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
name|enum_value
operator|=
name|g_enum_get_value_by_nick
argument_list|(
name|G_ENUM_CLASS
argument_list|(
name|enum_class
argument_list|)
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|enum_value
condition|)
name|enum_value
operator|=
name|g_enum_get_value_by_name
argument_list|(
name|G_ENUM_CLASS
argument_list|(
name|enum_class
argument_list|)
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|enum_value
condition|)
block|{
name|g_scanner_error
argument_list|(
name|scanner
argument_list|,
name|_
argument_list|(
literal|"invalid value '%s' for token %s"
argument_list|)
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|)
expr_stmt|;
return|return
name|G_TOKEN_NONE
return|;
block|}
break|break;
case|case
name|G_TOKEN_INT
case|:
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
name|enum_value
operator|=
name|g_enum_get_value
argument_list|(
name|enum_class
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_int
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|enum_value
condition|)
block|{
name|g_scanner_error
argument_list|(
name|scanner
argument_list|,
name|_
argument_list|(
literal|"invalid value '%ld' for token %s"
argument_list|)
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_int
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|)
expr_stmt|;
return|return
name|G_TOKEN_NONE
return|;
block|}
break|break;
default|default:
return|return
name|G_TOKEN_IDENTIFIER
return|;
block|}
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|enum_value
operator|->
name|value
argument_list|)
expr_stmt|;
return|return
name|G_TOKEN_RIGHT_PAREN
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|gimp_config_deserialize_memsize (GValue * value,GParamSpec * prop_spec,GScanner * scanner)
name|gimp_config_deserialize_memsize
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
block|{
name|gchar
modifier|*
name|orig_cset_first
init|=
name|scanner
operator|->
name|config
operator|->
name|cset_identifier_first
decl_stmt|;
name|gchar
modifier|*
name|orig_cset_nth
init|=
name|scanner
operator|->
name|config
operator|->
name|cset_identifier_nth
decl_stmt|;
name|scanner
operator|->
name|config
operator|->
name|cset_identifier_first
operator|=
name|G_CSET_DIGITS
expr_stmt|;
name|scanner
operator|->
name|config
operator|->
name|cset_identifier_nth
operator|=
name|G_CSET_DIGITS
literal|"gGmMkKbB"
expr_stmt|;
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|G_TOKEN_IDENTIFIER
condition|)
return|return
name|G_TOKEN_IDENTIFIER
return|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
name|scanner
operator|->
name|config
operator|->
name|cset_identifier_first
operator|=
name|orig_cset_first
expr_stmt|;
name|scanner
operator|->
name|config
operator|->
name|cset_identifier_nth
operator|=
name|orig_cset_nth
expr_stmt|;
if|if
condition|(
name|gimp_memsize_set_from_string
argument_list|(
name|value
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|)
condition|)
return|return
name|G_TOKEN_RIGHT_PAREN
return|;
else|else
return|return
name|G_TOKEN_NONE
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|gimp_config_deserialize_path (GValue * value,GObject * object,GParamSpec * prop_spec,GScanner * scanner)
name|gimp_config_deserialize_path
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
block|{
name|gchar
modifier|*
name|path
decl_stmt|;
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|G_TOKEN_STRING
condition|)
return|return
name|G_TOKEN_STRING
return|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|scanner_string_utf8_valid
argument_list|(
name|scanner
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|)
condition|)
return|return
name|G_TOKEN_NONE
return|;
name|path
operator|=
name|gimp_config_substitute_path
argument_list|(
name|object
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_string
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|path
condition|)
return|return
name|G_TOKEN_NONE
return|;
name|g_value_set_string_take_ownership
argument_list|(
name|value
argument_list|,
name|path
argument_list|)
expr_stmt|;
return|return
name|G_TOKEN_RIGHT_PAREN
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|gimp_config_deserialize_color (GValue * value,GParamSpec * prop_spec,GScanner * scanner)
name|gimp_config_deserialize_color
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
block|{
name|GimpRGB
name|color
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_color
argument_list|(
name|scanner
argument_list|,
operator|&
name|color
argument_list|)
condition|)
return|return
name|G_TOKEN_NONE
return|;
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
return|return
name|G_TOKEN_RIGHT_PAREN
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|gimp_config_deserialize_value_array (GValue * value,GObject * object,GParamSpec * prop_spec,GScanner * scanner)
name|gimp_config_deserialize_value_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
block|{
name|GParamSpecValueArray
modifier|*
name|array_spec
decl_stmt|;
name|GValueArray
modifier|*
name|array
decl_stmt|;
name|GValue
name|array_value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gint
name|n_values
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|array_spec
operator|=
name|G_PARAM_SPEC_VALUE_ARRAY
argument_list|(
name|prop_spec
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|&
name|n_values
argument_list|)
condition|)
return|return
name|G_TOKEN_INT
return|;
name|array
operator|=
name|g_value_array_new
argument_list|(
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
name|n_values
condition|;
name|i
operator|++
control|)
block|{
name|g_value_init
argument_list|(
operator|&
name|array_value
argument_list|,
name|array_spec
operator|->
name|element_spec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|token
operator|=
name|gimp_config_deserialize_value
argument_list|(
operator|&
name|array_value
argument_list|,
name|object
argument_list|,
name|array_spec
operator|->
name|element_spec
argument_list|,
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|==
name|G_TOKEN_RIGHT_PAREN
condition|)
name|g_value_array_append
argument_list|(
name|array
argument_list|,
operator|&
name|array_value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|array_value
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_RIGHT_PAREN
condition|)
return|return
name|token
return|;
block|}
name|g_value_set_boxed_take_ownership
argument_list|(
name|value
argument_list|,
name|array
argument_list|)
expr_stmt|;
return|return
name|G_TOKEN_RIGHT_PAREN
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|gimp_config_deserialize_any (GValue * value,GParamSpec * prop_spec,GScanner * scanner)
name|gimp_config_deserialize_any
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
block|{
name|GValue
name|src
init|=
block|{
literal|0
block|, }
decl_stmt|;
if|if
condition|(
operator|!
name|g_value_type_transformable
argument_list|(
name|G_TYPE_STRING
argument_list|,
name|prop_spec
operator|->
name|value_type
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: %s can not be transformed from a string"
argument_list|,
name|G_STRLOC
argument_list|,
name|g_type_name
argument_list|(
name|prop_spec
operator|->
name|value_type
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|G_TOKEN_NONE
return|;
block|}
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|G_TOKEN_IDENTIFIER
condition|)
return|return
name|G_TOKEN_IDENTIFIER
return|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|src
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
name|g_value_set_static_string
argument_list|(
operator|&
name|src
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|)
expr_stmt|;
name|g_value_transform
argument_list|(
operator|&
name|src
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|src
argument_list|)
expr_stmt|;
return|return
name|G_TOKEN_RIGHT_PAREN
return|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|gboolean
DECL|function|scanner_string_utf8_valid (GScanner * scanner,const gchar * token_name)
name|scanner_string_utf8_valid
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
specifier|const
name|gchar
modifier|*
name|token_name
parameter_list|)
block|{
if|if
condition|(
name|g_utf8_validate
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_string
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
return|return
name|TRUE
return|;
name|g_scanner_error
argument_list|(
name|scanner
argument_list|,
name|_
argument_list|(
literal|"value for token %s is not a valid UTF-8 string"
argument_list|)
argument_list|,
name|token_name
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit

