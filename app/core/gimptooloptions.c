begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimperror.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimptooloptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c52c1d40103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TOOL
name|PROP_TOOL
block|,
DECL|enumerator|PROP_TOOL_INFO
name|PROP_TOOL_INFO
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_config_iface_init
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
name|gimp_tool_options_dispose
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
name|gimp_tool_options_set_property
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
name|gimp_tool_options_get_property
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
name|gimp_tool_options_config_reset
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_tool_notify
parameter_list|(
name|GimpToolOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpToolOptions,gimp_tool_options,GIMP_TYPE_CONTEXT,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,gimp_tool_options_config_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpToolOptions
argument_list|,
argument|gimp_tool_options
argument_list|,
argument|GIMP_TYPE_CONTEXT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_tool_options_config_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tool_options_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tool_options_class_init
parameter_list|(
name|GimpToolOptionsClass
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
name|dispose
operator|=
name|gimp_tool_options_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_tool_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_tool_options_get_property
expr_stmt|;
name|g_object_class_override_property
argument_list|(
name|object_class
argument_list|,
name|PROP_TOOL
argument_list|,
literal|"tool"
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_TOOL_INFO
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"tool-info"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TOOL_INFO
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_init (GimpToolOptions * options)
name|gimp_tool_options_init
parameter_list|(
name|GimpToolOptions
modifier|*
name|options
parameter_list|)
block|{
name|options
operator|->
name|tool_info
operator|=
name|NULL
expr_stmt|;
name|g_signal_connect
argument_list|(
name|options
argument_list|,
literal|"notify::tool"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_options_tool_notify
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_config_iface_init (GimpConfigInterface * iface)
name|gimp_tool_options_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|reset
operator|=
name|gimp_tool_options_config_reset
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_dispose (GObject * object)
name|gimp_tool_options_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolOptions
modifier|*
name|options
init|=
name|GIMP_TOOL_OPTIONS
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|options
operator|->
name|tool_info
condition|)
block|{
name|g_object_unref
argument_list|(
name|options
operator|->
name|tool_info
argument_list|)
expr_stmt|;
name|options
operator|->
name|tool_info
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  This is such a horrible hack, but necessary because we  *  a) load an option's tool-info from disk in many cases  *  b) screwed up in the past and saved the wrong tool-info in some cases  */
end_comment

begin_function
specifier|static
name|GimpToolInfo
modifier|*
DECL|function|gimp_tool_options_check_tool_info (GimpToolOptions * options,GimpToolInfo * tool_info,gboolean warn)
name|gimp_tool_options_check_tool_info
parameter_list|(
name|GimpToolOptions
modifier|*
name|options
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|gboolean
name|warn
parameter_list|)
block|{
if|if
condition|(
name|tool_info
operator|&&
name|G_OBJECT_TYPE
argument_list|(
name|options
argument_list|)
operator|==
name|tool_info
operator|->
name|tool_options_type
condition|)
block|{
return|return
name|tool_info
return|;
block|}
else|else
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_get_tool_info_iter
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
operator|->
name|gimp
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpToolInfo
modifier|*
name|new_info
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|G_OBJECT_TYPE
argument_list|(
name|options
argument_list|)
operator|==
name|new_info
operator|->
name|tool_options_type
condition|)
block|{
if|if
condition|(
name|warn
condition|)
name|g_printerr
argument_list|(
literal|"%s: correcting bogus deserialized tool "
literal|"type '%s' with right type '%s'\n"
argument_list|,
name|g_type_name
argument_list|(
name|G_OBJECT_TYPE
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|,
name|tool_info
condition|?
name|gimp_object_get_name
argument_list|(
name|tool_info
argument_list|)
else|:
literal|"NULL"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|new_info
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|new_info
return|;
block|}
block|}
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_tool_options_set_property
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
name|GimpToolOptions
modifier|*
name|options
init|=
name|GIMP_TOOL_OPTIONS
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
name|PROP_TOOL
case|:
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
decl_stmt|;
name|GimpToolInfo
modifier|*
name|context_tool
decl_stmt|;
name|context_tool
operator|=
name|gimp_context_get_tool
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|context_tool
operator|==
name|NULL
operator|||
name|context_tool
operator|==
name|tool_info
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_tool_options_check_tool_info
argument_list|(
name|options
argument_list|,
name|tool_info
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|context_tool
condition|)
name|gimp_context_set_tool
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|PROP_TOOL_INFO
case|:
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|options
operator|->
name|tool_info
operator|==
name|NULL
operator|||
name|options
operator|->
name|tool_info
operator|==
name|tool_info
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_tool_options_check_tool_info
argument_list|(
name|options
argument_list|,
name|tool_info
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|options
operator|->
name|tool_info
condition|)
block|{
name|options
operator|->
name|tool_info
operator|=
name|g_object_ref
argument_list|(
name|tool_info
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|->
name|context_props
condition|)
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
name|tool_info
operator|->
name|context_props
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_set_serialize_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
name|tool_info
operator|->
name|context_props
argument_list|)
expr_stmt|;
block|}
block|}
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
DECL|function|gimp_tool_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_tool_options_get_property
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
name|GimpToolOptions
modifier|*
name|options
init|=
name|GIMP_TOOL_OPTIONS
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
name|PROP_TOOL
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|gimp_context_get_tool
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TOOL_INFO
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|tool_info
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
DECL|function|gimp_tool_options_config_reset (GimpConfig * config)
name|gimp_tool_options_config_reset
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
block|{
name|gchar
modifier|*
name|name
init|=
name|g_strdup
argument_list|(
name|gimp_object_get_name
argument_list|(
name|config
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_config_reset_properties
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_tool_notify (GimpToolOptions * options,GParamSpec * pspec)
name|gimp_tool_options_tool_notify
parameter_list|(
name|GimpToolOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|gimp_context_get_tool
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
decl_stmt|;
name|GimpToolInfo
modifier|*
name|new_info
decl_stmt|;
name|new_info
operator|=
name|gimp_tool_options_check_tool_info
argument_list|(
name|options
argument_list|,
name|tool_info
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|new_info
operator|!=
name|tool_info
condition|)
name|g_warning
argument_list|(
literal|"%s: 'tool' property on %s was set to bogus value "
literal|"'%s', it MUST be '%s'."
argument_list|,
name|G_STRFUNC
argument_list|,
name|g_type_name
argument_list|(
name|G_OBJECT_TYPE
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|new_info
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_tool_options_serialize (GimpToolOptions * tool_options,GError ** error)
name|gimp_tool_options_serialize
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
name|gchar
modifier|*
name|header
decl_stmt|;
name|gchar
modifier|*
name|footer
decl_stmt|;
name|gboolean
name|retval
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_OPTIONS
argument_list|(
name|tool_options
argument_list|)
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
name|file
operator|=
name|gimp_tool_info_get_options_file
argument_list|(
name|tool_options
operator|->
name|tool_info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_options
operator|->
name|tool_info
operator|->
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Writing '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|header
operator|=
name|g_strdup_printf
argument_list|(
literal|"GIMP %s options"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|tool_options
operator|->
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
name|footer
operator|=
name|g_strdup_printf
argument_list|(
literal|"end of %s options"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|tool_options
operator|->
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
name|retval
operator|=
name|gimp_config_serialize_to_gfile
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|tool_options
argument_list|)
argument_list|,
name|file
argument_list|,
name|header
argument_list|,
name|footer
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|header
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|footer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_options_deserialize (GimpToolOptions * tool_options,GError ** error)
name|gimp_tool_options_deserialize
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
name|gboolean
name|retval
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_OPTIONS
argument_list|(
name|tool_options
argument_list|)
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
name|file
operator|=
name|gimp_tool_info_get_options_file
argument_list|(
name|tool_options
operator|->
name|tool_info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_options
operator|->
name|tool_info
operator|->
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|retval
operator|=
name|gimp_config_deserialize_gfile
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|tool_options
argument_list|)
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_options_delete (GimpToolOptions * tool_options,GError ** error)
name|gimp_tool_options_delete
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
name|GError
modifier|*
name|my_error
init|=
name|NULL
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_OPTIONS
argument_list|(
name|tool_options
argument_list|)
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
name|file
operator|=
name|gimp_tool_info_get_options_file
argument_list|(
name|tool_options
operator|->
name|tool_info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_options
operator|->
name|tool_info
operator|->
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Deleting '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_file_delete
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
operator|&
name|my_error
argument_list|)
operator|&&
name|my_error
operator|->
name|code
operator|!=
name|G_IO_ERROR_NOT_FOUND
condition|)
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"Deleting \"%s\" failed: %s"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|,
name|my_error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
name|g_clear_error
argument_list|(
operator|&
name|my_error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_options_create_folder (void)
name|gimp_tool_options_create_folder
parameter_list|(
name|void
parameter_list|)
block|{
name|GFile
modifier|*
name|file
init|=
name|gimp_directory_file
argument_list|(
literal|"tool-options"
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_file_make_directory
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

