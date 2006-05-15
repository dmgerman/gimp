begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpRc, the object for GIMPs user configuration file gimprc.  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"config-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-file.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"gimprc-deserialize.h"
end_include

begin_include
include|#
directive|include
file|"gimprc-serialize.h"
end_include

begin_include
include|#
directive|include
file|"gimprc-unknown.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon297353bb0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_VERBOSE
name|PROP_VERBOSE
block|,
DECL|enumerator|PROP_SYSTEM_GIMPRC
name|PROP_SYSTEM_GIMPRC
block|,
DECL|enumerator|PROP_USER_GIMPRC
name|PROP_USER_GIMPRC
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_rc_config_iface_init
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
name|gimp_rc_dispose
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
name|gimp_rc_finalize
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
name|gimp_rc_set_property
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
name|gimp_rc_get_property
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
name|GimpConfig
modifier|*
name|gimp_rc_duplicate
parameter_list|(
name|GimpConfig
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_rc_load
parameter_list|(
name|GimpRc
modifier|*
name|rc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_rc_idle_save
parameter_list|(
name|GimpRc
modifier|*
name|rc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_rc_notify
parameter_list|(
name|GimpRc
modifier|*
name|rc
parameter_list|,
name|GParamSpec
modifier|*
name|param
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpRc,gimp_rc,GIMP_TYPE_PLUGIN_CONFIG,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,gimp_rc_config_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpRc
argument_list|,
argument|gimp_rc
argument_list|,
argument|GIMP_TYPE_PLUGIN_CONFIG
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_rc_config_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_rc_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_rc_class_init
parameter_list|(
name|GimpRcClass
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
name|gimp_rc_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_rc_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_rc_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_rc_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_VERBOSE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"verbose"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SYSTEM_GIMPRC
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"system-gimprc"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_USER_GIMPRC
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"user-gimprc"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rc_init (GimpRc * rc)
name|gimp_rc_init
parameter_list|(
name|GimpRc
modifier|*
name|rc
parameter_list|)
block|{
name|rc
operator|->
name|autosave
operator|=
name|FALSE
expr_stmt|;
name|rc
operator|->
name|save_idle_id
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rc_dispose (GObject * object)
name|gimp_rc_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpRc
modifier|*
name|rc
init|=
name|GIMP_RC
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|rc
operator|->
name|save_idle_id
condition|)
name|gimp_rc_idle_save
argument_list|(
name|rc
argument_list|)
expr_stmt|;
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

begin_function
specifier|static
name|void
DECL|function|gimp_rc_finalize (GObject * object)
name|gimp_rc_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpRc
modifier|*
name|rc
init|=
name|GIMP_RC
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|rc
operator|->
name|system_gimprc
condition|)
block|{
name|g_free
argument_list|(
name|rc
operator|->
name|system_gimprc
argument_list|)
expr_stmt|;
name|rc
operator|->
name|system_gimprc
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|rc
operator|->
name|user_gimprc
condition|)
block|{
name|g_free
argument_list|(
name|rc
operator|->
name|user_gimprc
argument_list|)
expr_stmt|;
name|rc
operator|->
name|user_gimprc
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
DECL|function|gimp_rc_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_rc_set_property
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
name|GimpRc
modifier|*
name|rc
init|=
name|GIMP_RC
argument_list|(
name|object
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|filename
init|=
name|NULL
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_SYSTEM_GIMPRC
case|:
case|case
name|PROP_USER_GIMPRC
case|:
name|filename
operator|=
name|g_value_get_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_VERBOSE
case|:
name|rc
operator|->
name|verbose
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SYSTEM_GIMPRC
case|:
name|g_free
argument_list|(
name|rc
operator|->
name|system_gimprc
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
condition|)
name|rc
operator|->
name|system_gimprc
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
else|else
name|rc
operator|->
name|system_gimprc
operator|=
name|g_build_filename
argument_list|(
name|gimp_sysconf_directory
argument_list|()
argument_list|,
literal|"gimprc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USER_GIMPRC
case|:
name|g_free
argument_list|(
name|rc
operator|->
name|user_gimprc
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
condition|)
name|rc
operator|->
name|user_gimprc
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
else|else
name|rc
operator|->
name|user_gimprc
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"gimprc"
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
DECL|function|gimp_rc_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_rc_get_property
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
name|GimpRc
modifier|*
name|rc
init|=
name|GIMP_RC
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
name|PROP_VERBOSE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|rc
operator|->
name|verbose
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SYSTEM_GIMPRC
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|rc
operator|->
name|system_gimprc
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USER_GIMPRC
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|rc
operator|->
name|user_gimprc
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
DECL|function|gimp_rc_config_iface_init (GimpConfigInterface * iface)
name|gimp_rc_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|serialize
operator|=
name|gimp_rc_serialize
expr_stmt|;
name|iface
operator|->
name|deserialize
operator|=
name|gimp_rc_deserialize
expr_stmt|;
name|iface
operator|->
name|duplicate
operator|=
name|gimp_rc_duplicate
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rc_duplicate_unknown_token (const gchar * key,const gchar * value,gpointer user_data)
name|gimp_rc_duplicate_unknown_token
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
name|user_data
parameter_list|)
block|{
name|gimp_rc_add_unknown_token
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|user_data
argument_list|)
argument_list|,
name|key
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpConfig
modifier|*
DECL|function|gimp_rc_duplicate (GimpConfig * config)
name|gimp_rc_duplicate
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpConfig
modifier|*
name|dup
init|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_RC
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|dup
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_rc_foreach_unknown_token
argument_list|(
name|config
argument_list|,
name|gimp_rc_duplicate_unknown_token
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
name|void
DECL|function|gimp_rc_load (GimpRc * rc)
name|gimp_rc_load
parameter_list|(
name|GimpRc
modifier|*
name|rc
parameter_list|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_RC
argument_list|(
name|rc
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|->
name|verbose
condition|)
name|g_print
argument_list|(
name|_
argument_list|(
literal|"Parsing '%s'\n"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|rc
operator|->
name|system_gimprc
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|rc
argument_list|)
argument_list|,
name|rc
operator|->
name|system_gimprc
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
name|error
operator|->
name|code
operator|!=
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
condition|)
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|rc
operator|->
name|verbose
condition|)
name|g_print
argument_list|(
name|_
argument_list|(
literal|"Parsing '%s'\n"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|rc
operator|->
name|user_gimprc
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|rc
argument_list|)
argument_list|,
name|rc
operator|->
name|user_gimprc
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
name|error
operator|->
name|code
operator|!=
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
condition|)
block|{
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|gimp_config_file_backup_on_error
argument_list|(
name|rc
operator|->
name|user_gimprc
argument_list|,
literal|"gimprc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_rc_idle_save (GimpRc * rc)
name|gimp_rc_idle_save
parameter_list|(
name|GimpRc
modifier|*
name|rc
parameter_list|)
block|{
name|gimp_rc_save
argument_list|(
name|rc
argument_list|)
expr_stmt|;
name|rc
operator|->
name|save_idle_id
operator|=
literal|0
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rc_notify (GimpRc * rc,GParamSpec * param,gpointer data)
name|gimp_rc_notify
parameter_list|(
name|GimpRc
modifier|*
name|rc
parameter_list|,
name|GParamSpec
modifier|*
name|param
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
operator|!
name|rc
operator|->
name|autosave
condition|)
return|return;
if|if
condition|(
operator|!
name|rc
operator|->
name|save_idle_id
condition|)
name|rc
operator|->
name|save_idle_id
operator|=
name|g_idle_add
argument_list|(
operator|(
name|GSourceFunc
operator|)
name|gimp_rc_idle_save
argument_list|,
name|rc
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_rc_new:  * @system_gimprc: the name of the system-wide gimprc file or %NULL to  *                 use the standard location  * @user_gimprc:   the name of the user gimprc file or %NULL to use the  *                 standard location  * @verbose:       enable console messages about loading and saving  *  * Creates a new GimpRc object and loads the system-wide and the user  * configuration files.  *  * Returns: the new #GimpRc.  */
end_comment

begin_function
name|GimpRc
modifier|*
DECL|function|gimp_rc_new (const gchar * system_gimprc,const gchar * user_gimprc,gboolean verbose)
name|gimp_rc_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|system_gimprc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|user_gimprc
parameter_list|,
name|gboolean
name|verbose
parameter_list|)
block|{
name|GimpRc
modifier|*
name|rc
init|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_RC
argument_list|,
literal|"verbose"
argument_list|,
name|verbose
argument_list|,
literal|"system-gimprc"
argument_list|,
name|system_gimprc
argument_list|,
literal|"user-gimprc"
argument_list|,
name|user_gimprc
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gimp_rc_load
argument_list|(
name|rc
argument_list|)
expr_stmt|;
return|return
name|rc
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_rc_set_autosave (GimpRc * rc,gboolean autosave)
name|gimp_rc_set_autosave
parameter_list|(
name|GimpRc
modifier|*
name|rc
parameter_list|,
name|gboolean
name|autosave
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_RC
argument_list|(
name|rc
argument_list|)
argument_list|)
expr_stmt|;
name|autosave
operator|=
name|autosave
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
if|if
condition|(
name|rc
operator|->
name|autosave
operator|==
name|autosave
condition|)
return|return;
if|if
condition|(
name|autosave
condition|)
name|g_signal_connect
argument_list|(
name|rc
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_rc_notify
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|rc
argument_list|,
name|gimp_rc_notify
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|rc
operator|->
name|autosave
operator|=
name|autosave
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_rc_query:  * @rc:  a #GimpRc object.  * @key: a string used as a key for the lookup.  *  * This function looks up @key in the object properties of @rc. If  * there's a matching property, a string representation of its value  * is returned. If no property is found, the list of unknown tokens  * attached to the @rc object is searched.  *  * Return value: a newly allocated string representing the value or %NULL  *               if the key couldn't be found.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_rc_query (GimpRc * rc,const gchar * key)
name|gimp_rc_query
parameter_list|(
name|GimpRc
modifier|*
name|rc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|key
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|klass
decl_stmt|;
name|GObject
modifier|*
name|rc_object
decl_stmt|;
name|GParamSpec
modifier|*
modifier|*
name|property_specs
decl_stmt|;
name|GParamSpec
modifier|*
name|prop_spec
decl_stmt|;
name|guint
name|i
decl_stmt|,
name|n_property_specs
decl_stmt|;
name|gchar
modifier|*
name|retval
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_RC
argument_list|(
name|rc
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
name|rc_object
operator|=
name|G_OBJECT
argument_list|(
name|rc
argument_list|)
expr_stmt|;
name|klass
operator|=
name|G_OBJECT_GET_CLASS
argument_list|(
name|rc
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
name|NULL
return|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|prop_spec
operator|=
name|NULL
init|;
name|i
operator|<
name|n_property_specs
operator|&&
operator|!
name|prop_spec
condition|;
name|i
operator|++
control|)
block|{
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
name|GIMP_CONFIG_PARAM_SERIALIZE
operator|)
operator|||
name|strcmp
argument_list|(
name|prop_spec
operator|->
name|name
argument_list|,
name|key
argument_list|)
condition|)
block|{
name|prop_spec
operator|=
name|NULL
expr_stmt|;
block|}
block|}
if|if
condition|(
name|prop_spec
condition|)
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
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
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
name|rc_object
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
name|gimp_config_serialize_value
argument_list|(
operator|&
name|value
argument_list|,
name|str
argument_list|,
name|FALSE
argument_list|)
condition|)
name|retval
operator|=
name|g_string_free
argument_list|(
name|str
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
else|else
name|g_string_free
argument_list|(
name|str
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|retval
operator|=
name|g_strdup
argument_list|(
name|gimp_rc_lookup_unknown_token
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|rc
argument_list|)
argument_list|,
name|key
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|property_specs
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|retval
condition|)
block|{
specifier|const
name|gchar
modifier|*
specifier|const
name|path_tokens
index|[]
init|=
block|{
literal|"gimp_dir"
block|,
literal|"gimp_data_dir"
block|,
literal|"gimp_plug_in_dir"
block|,
literal|"gimp_plugin_dir"
block|,
literal|"gimp_sysconf_dir"
block|}
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
operator|!
name|retval
operator|&&
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|path_tokens
argument_list|)
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|strcmp
argument_list|(
name|key
argument_list|,
name|path_tokens
index|[
name|i
index|]
argument_list|)
operator|==
literal|0
condition|)
name|retval
operator|=
name|g_strdup_printf
argument_list|(
literal|"${%s}"
argument_list|,
name|path_tokens
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|retval
condition|)
block|{
name|gchar
modifier|*
name|tmp
init|=
name|gimp_config_path_expand
argument_list|(
name|retval
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|tmp
condition|)
block|{
name|g_free
argument_list|(
name|retval
argument_list|)
expr_stmt|;
name|retval
operator|=
name|tmp
expr_stmt|;
block|}
block|}
return|return
name|retval
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_rc_set_unkown_token:  * @gimprc: a #GimpRc object.  * @token:  * @value:  *  * Calls gimp_rc_add_unknown_token() and triggers an idle-save if  * autosave is enabled on @gimprc.  **/
end_comment

begin_function
name|void
DECL|function|gimp_rc_set_unknown_token (GimpRc * rc,const gchar * token,const gchar * value)
name|gimp_rc_set_unknown_token
parameter_list|(
name|GimpRc
modifier|*
name|rc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|token
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_RC
argument_list|(
name|rc
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_rc_add_unknown_token
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|rc
argument_list|)
argument_list|,
name|token
argument_list|,
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|->
name|autosave
condition|)
name|gimp_rc_notify
argument_list|(
name|rc
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_rc_save:  * @gimprc: a #GimpRc object.  *  * Saves any settings that differ from the system-wide defined  * defaults to the users personal gimprc file.  **/
end_comment

begin_function
name|void
DECL|function|gimp_rc_save (GimpRc * rc)
name|gimp_rc_save
parameter_list|(
name|GimpRc
modifier|*
name|rc
parameter_list|)
block|{
name|GimpRc
modifier|*
name|global
decl_stmt|;
name|gchar
modifier|*
name|header
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|top
init|=
literal|"GIMP gimprc\n"
literal|"\n"
literal|"This is your personal gimprc file.  Any variable defined in this file "
literal|"takes precedence over the value defined in the system-wide gimprc: "
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|bottom
init|=
literal|"\n"
literal|"Most values can be set within GIMP by changing some options in "
literal|"the Preferences dialog."
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|footer
init|=
literal|"end of gimprc"
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_RC
argument_list|(
name|rc
argument_list|)
argument_list|)
expr_stmt|;
name|global
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_RC
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_config_deserialize_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|global
argument_list|)
argument_list|,
name|rc
operator|->
name|system_gimprc
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|header
operator|=
name|g_strconcat
argument_list|(
name|top
argument_list|,
name|rc
operator|->
name|system_gimprc
argument_list|,
name|bottom
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|->
name|verbose
condition|)
name|g_print
argument_list|(
name|_
argument_list|(
literal|"Saving '%s'\n"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|rc
operator|->
name|user_gimprc
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_serialize_to_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|rc
argument_list|)
argument_list|,
name|rc
operator|->
name|user_gimprc
argument_list|,
name|header
argument_list|,
name|footer
argument_list|,
name|global
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|header
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|global
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

