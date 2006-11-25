begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcontrollerinfo.c  * Copyright (C) 2004-2005 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_define
DECL|macro|GIMP_ENABLE_CONTROLLER_UNDER_CONSTRUCTION
define|#
directive|define
name|GIMP_ENABLE_CONTROLLER_UNDER_CONSTRUCTION
end_define

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpcontroller.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontrollerinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b9528d40103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ENABLED
name|PROP_ENABLED
block|,
DECL|enumerator|PROP_DEBUG_EVENTS
name|PROP_DEBUG_EVENTS
block|,
DECL|enumerator|PROP_CONTROLLER
name|PROP_CONTROLLER
block|,
DECL|enumerator|PROP_MAPPING
name|PROP_MAPPING
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b9528d40203
block|{
DECL|enumerator|EVENT_MAPPED
name|EVENT_MAPPED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_controller_info_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_controller_info_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_controller_info_set_property
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
name|gimp_controller_info_get_property
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
name|gboolean
name|gimp_controller_info_serialize_property
parameter_list|(
name|GimpConfig
modifier|*
name|config
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
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_controller_info_deserialize_property
parameter_list|(
name|GimpConfig
modifier|*
name|config
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
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GTokenType
modifier|*
name|expected
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_controller_info_event
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
specifier|const
name|GimpControllerEvent
modifier|*
name|event
parameter_list|,
name|GimpControllerInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpControllerInfo
argument_list|,
argument|gimp_controller_info
argument_list|,
argument|GIMP_TYPE_VIEWABLE
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_controller_info_config_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_controller_info_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|info_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_controller_info_class_init (GimpControllerInfoClass * klass)
name|gimp_controller_info_class_init
parameter_list|(
name|GimpControllerInfoClass
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
name|GimpViewableClass
modifier|*
name|viewable_class
init|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_controller_info_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_controller_info_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_controller_info_get_property
expr_stmt|;
name|viewable_class
operator|->
name|default_stock_id
operator|=
name|GIMP_STOCK_CONTROLLER
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_ENABLED
argument_list|,
literal|"enabled"
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_DEBUG_EVENTS
argument_list|,
literal|"debug-events"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTROLLER
argument_list|,
literal|"controller"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CONTROLLER
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOXED
argument_list|(
name|object_class
argument_list|,
name|PROP_MAPPING
argument_list|,
literal|"mapping"
argument_list|,
name|NULL
argument_list|,
name|G_TYPE_HASH_TABLE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|info_signals
index|[
name|EVENT_MAPPED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"event-mapped"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpControllerInfoClass
argument_list|,
name|event_mapped
argument_list|)
argument_list|,
name|gimp_boolean_handled_accum
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_BOOLEAN__OBJECT_POINTER_STRING
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
literal|3
argument_list|,
name|G_TYPE_OBJECT
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_controller_info_init (GimpControllerInfo * info)
name|gimp_controller_info_init
parameter_list|(
name|GimpControllerInfo
modifier|*
name|info
parameter_list|)
block|{
name|info
operator|->
name|controller
operator|=
name|NULL
expr_stmt|;
name|info
operator|->
name|mapping
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_controller_info_config_iface_init (GimpConfigInterface * iface)
name|gimp_controller_info_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|serialize_property
operator|=
name|gimp_controller_info_serialize_property
expr_stmt|;
name|iface
operator|->
name|deserialize_property
operator|=
name|gimp_controller_info_deserialize_property
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_controller_info_finalize (GObject * object)
name|gimp_controller_info_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpControllerInfo
modifier|*
name|info
init|=
name|GIMP_CONTROLLER_INFO
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|info
operator|->
name|controller
condition|)
block|{
name|g_object_unref
argument_list|(
name|info
operator|->
name|controller
argument_list|)
expr_stmt|;
name|info
operator|->
name|controller
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|info
operator|->
name|mapping
condition|)
block|{
name|g_hash_table_unref
argument_list|(
name|info
operator|->
name|mapping
argument_list|)
expr_stmt|;
name|info
operator|->
name|mapping
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_controller_info_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_controller_info_set_property
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
name|GimpControllerInfo
modifier|*
name|info
init|=
name|GIMP_CONTROLLER_INFO
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
name|PROP_ENABLED
case|:
name|info
operator|->
name|enabled
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEBUG_EVENTS
case|:
name|info
operator|->
name|debug_events
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTROLLER
case|:
if|if
condition|(
name|info
operator|->
name|controller
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|info
operator|->
name|controller
argument_list|,
name|gimp_controller_info_event
argument_list|,
name|info
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|info
operator|->
name|controller
argument_list|)
expr_stmt|;
block|}
name|info
operator|->
name|controller
operator|=
name|GIMP_CONTROLLER
argument_list|(
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|controller
condition|)
block|{
name|g_signal_connect_object
argument_list|(
name|info
operator|->
name|controller
argument_list|,
literal|"event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_controller_info_event
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|info
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_viewable_set_stock_id
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|info
argument_list|)
argument_list|,
name|GIMP_CONTROLLER_GET_CLASS
argument_list|(
name|info
operator|->
name|controller
argument_list|)
operator|->
name|stock_id
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|PROP_MAPPING
case|:
if|if
condition|(
name|info
operator|->
name|mapping
condition|)
name|g_hash_table_unref
argument_list|(
name|info
operator|->
name|mapping
argument_list|)
expr_stmt|;
name|info
operator|->
name|mapping
operator|=
name|g_value_dup_boxed
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
DECL|function|gimp_controller_info_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_controller_info_get_property
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
name|GimpControllerInfo
modifier|*
name|info
init|=
name|GIMP_CONTROLLER_INFO
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
name|PROP_ENABLED
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|info
operator|->
name|enabled
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DEBUG_EVENTS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|info
operator|->
name|debug_events
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTROLLER
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|info
operator|->
name|controller
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MAPPING
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
name|info
operator|->
name|mapping
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
DECL|function|gimp_controller_info_serialize_mapping (gpointer key,gpointer value,gpointer data)
name|gimp_controller_info_serialize_mapping
parameter_list|(
name|gpointer
name|key
parameter_list|,
name|gpointer
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|event_name
init|=
name|key
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|action_name
init|=
name|value
decl_stmt|;
name|GimpConfigWriter
modifier|*
name|writer
init|=
name|data
decl_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"map"
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|event_name
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|action_name
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_controller_info_serialize_property (GimpConfig * config,guint property_id,const GValue * value,GParamSpec * pspec,GimpConfigWriter * writer)
name|gimp_controller_info_serialize_property
parameter_list|(
name|GimpConfig
modifier|*
name|config
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
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
block|{
name|GHashTable
modifier|*
name|mapping
decl_stmt|;
if|if
condition|(
name|property_id
operator|!=
name|PROP_MAPPING
condition|)
return|return
name|FALSE
return|;
name|mapping
operator|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|mapping
condition|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
name|pspec
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_hash_table_foreach
argument_list|(
name|mapping
argument_list|,
operator|(
name|GHFunc
operator|)
name|gimp_controller_info_serialize_mapping
argument_list|,
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_controller_info_deserialize_property (GimpConfig * config,guint property_id,GValue * value,GParamSpec * pspec,GScanner * scanner,GTokenType * expected)
name|gimp_controller_info_deserialize_property
parameter_list|(
name|GimpConfig
modifier|*
name|config
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
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GTokenType
modifier|*
name|expected
parameter_list|)
block|{
name|GHashTable
modifier|*
name|mapping
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
if|if
condition|(
name|property_id
operator|!=
name|PROP_MAPPING
condition|)
return|return
name|FALSE
return|;
name|mapping
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
while|while
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|token
condition|)
block|{
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
name|G_TOKEN_IDENTIFIER
expr_stmt|;
break|break;
case|case
name|G_TOKEN_IDENTIFIER
case|:
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|,
literal|"map"
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|event_name
decl_stmt|;
name|gchar
modifier|*
name|action_name
decl_stmt|;
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|event_name
argument_list|)
condition|)
goto|goto
name|error
goto|;
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|action_name
argument_list|)
condition|)
goto|goto
name|error
goto|;
name|g_hash_table_insert
argument_list|(
name|mapping
argument_list|,
name|event_name
argument_list|,
name|action_name
argument_list|)
expr_stmt|;
block|}
name|token
operator|=
name|G_TOKEN_RIGHT_PAREN
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
break|break;
block|}
block|}
if|if
condition|(
name|token
operator|==
name|G_TOKEN_LEFT_PAREN
condition|)
block|{
name|token
operator|=
name|G_TOKEN_RIGHT_PAREN
expr_stmt|;
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|token
condition|)
block|{
name|g_value_take_boxed
argument_list|(
name|value
argument_list|,
name|mapping
argument_list|)
expr_stmt|;
block|}
else|else
block|{
goto|goto
name|error
goto|;
block|}
block|}
else|else
block|{
name|error
label|:
name|g_hash_table_unref
argument_list|(
name|mapping
argument_list|)
expr_stmt|;
operator|*
name|expected
operator|=
name|token
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpControllerInfo
modifier|*
DECL|function|gimp_controller_info_new (GType type)
name|gimp_controller_info_new
parameter_list|(
name|GType
name|type
parameter_list|)
block|{
name|GimpControllerClass
modifier|*
name|controller_class
decl_stmt|;
name|GimpController
modifier|*
name|controller
decl_stmt|;
name|GimpControllerInfo
modifier|*
name|info
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|type
argument_list|,
name|GIMP_TYPE_CONTROLLER
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|controller_class
operator|=
name|g_type_class_ref
argument_list|(
name|type
argument_list|)
expr_stmt|;
name|controller
operator|=
name|gimp_controller_new
argument_list|(
name|type
argument_list|)
expr_stmt|;
name|info
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CONTROLLER_INFO
argument_list|,
literal|"name"
argument_list|,
name|controller_class
operator|->
name|name
argument_list|,
literal|"controller"
argument_list|,
name|controller
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|controller
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|controller_class
argument_list|)
expr_stmt|;
return|return
name|info
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_controller_info_set_enabled (GimpControllerInfo * info,gboolean enabled)
name|gimp_controller_info_set_enabled
parameter_list|(
name|GimpControllerInfo
modifier|*
name|info
parameter_list|,
name|gboolean
name|enabled
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTROLLER_INFO
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|enabled
operator|!=
name|info
operator|->
name|enabled
condition|)
name|g_object_set
argument_list|(
name|info
argument_list|,
literal|"enabled"
argument_list|,
name|enabled
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_controller_info_get_enabled (GimpControllerInfo * info)
name|gimp_controller_info_get_enabled
parameter_list|(
name|GimpControllerInfo
modifier|*
name|info
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTROLLER_INFO
argument_list|(
name|info
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|info
operator|->
name|enabled
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_controller_info_set_event_snooper (GimpControllerInfo * info,GimpControllerEventSnooper snooper,gpointer snooper_data)
name|gimp_controller_info_set_event_snooper
parameter_list|(
name|GimpControllerInfo
modifier|*
name|info
parameter_list|,
name|GimpControllerEventSnooper
name|snooper
parameter_list|,
name|gpointer
name|snooper_data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTROLLER_INFO
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
name|info
operator|->
name|snooper
operator|=
name|snooper
expr_stmt|;
name|info
operator|->
name|snooper_data
operator|=
name|snooper_data
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_controller_info_event (GimpController * controller,const GimpControllerEvent * event,GimpControllerInfo * info)
name|gimp_controller_info_event
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
specifier|const
name|GimpControllerEvent
modifier|*
name|event
parameter_list|,
name|GimpControllerInfo
modifier|*
name|info
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|event_name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|event_blurb
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|action_name
init|=
name|NULL
decl_stmt|;
name|event_name
operator|=
name|gimp_controller_get_event_name
argument_list|(
name|controller
argument_list|,
name|event
operator|->
name|any
operator|.
name|event_id
argument_list|)
expr_stmt|;
name|event_blurb
operator|=
name|gimp_controller_get_event_blurb
argument_list|(
name|controller
argument_list|,
name|event
operator|->
name|any
operator|.
name|event_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|debug_events
condition|)
block|{
name|g_print
argument_list|(
literal|"Received '%s' (class '%s')\n"
literal|"    controller event '%s (%s)'\n"
argument_list|,
name|controller
operator|->
name|name
argument_list|,
name|GIMP_CONTROLLER_GET_CLASS
argument_list|(
name|controller
argument_list|)
operator|->
name|name
argument_list|,
name|event_name
argument_list|,
name|event_blurb
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|event
operator|->
name|any
operator|.
name|type
condition|)
block|{
case|case
name|GIMP_CONTROLLER_EVENT_TRIGGER
case|:
name|g_print
argument_list|(
literal|"    (trigger event)\n"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CONTROLLER_EVENT_VALUE
case|:
if|if
condition|(
name|G_VALUE_HOLDS_DOUBLE
argument_list|(
operator|&
name|event
operator|->
name|value
operator|.
name|value
argument_list|)
condition|)
name|g_print
argument_list|(
literal|"    (value event, value = %f)\n"
argument_list|,
name|g_value_get_double
argument_list|(
operator|&
name|event
operator|->
name|value
operator|.
name|value
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|g_print
argument_list|(
literal|"    (value event, unhandled type '%s')\n"
argument_list|,
name|g_type_name
argument_list|(
name|event
operator|->
name|value
operator|.
name|value
operator|.
name|g_type
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|info
operator|->
name|snooper
condition|)
block|{
if|if
condition|(
name|info
operator|->
name|snooper
argument_list|(
name|info
argument_list|,
name|controller
argument_list|,
name|event
argument_list|,
name|info
operator|->
name|snooper_data
argument_list|)
condition|)
block|{
if|if
condition|(
name|info
operator|->
name|debug_events
condition|)
name|g_print
argument_list|(
literal|"    intercepted by event snooper\n\n"
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
if|if
condition|(
operator|!
name|info
operator|->
name|enabled
condition|)
block|{
if|if
condition|(
name|info
operator|->
name|debug_events
condition|)
name|g_print
argument_list|(
literal|"    ignoring because controller is disabled\n\n"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|info
operator|->
name|mapping
condition|)
name|action_name
operator|=
name|g_hash_table_lookup
argument_list|(
name|info
operator|->
name|mapping
argument_list|,
name|event_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|action_name
condition|)
block|{
name|gboolean
name|retval
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|info
operator|->
name|debug_events
condition|)
name|g_print
argument_list|(
literal|"    maps to action '%s'\n"
argument_list|,
name|action_name
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|info
argument_list|,
name|info_signals
index|[
name|EVENT_MAPPED
index|]
argument_list|,
literal|0
argument_list|,
name|controller
argument_list|,
name|event
argument_list|,
name|action_name
argument_list|,
operator|&
name|retval
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|debug_events
condition|)
block|{
if|if
condition|(
name|retval
condition|)
name|g_print
argument_list|(
literal|"    action was found\n\n"
argument_list|)
expr_stmt|;
else|else
name|g_print
argument_list|(
literal|"    action NOT found\n\n"
argument_list|)
expr_stmt|;
block|}
return|return
name|retval
return|;
block|}
else|else
block|{
if|if
condition|(
name|info
operator|->
name|debug_events
condition|)
name|g_print
argument_list|(
literal|"    doesn't map to action\n\n"
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

