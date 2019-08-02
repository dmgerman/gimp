begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpLangRc: pre-parsing of gimprc returning the language.  * Copyright (C) 2017  Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
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
file|"gimplangrc.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon279bc2eb0103
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
block|,
DECL|enumerator|PROP_LANGUAGE
name|PROP_LANGUAGE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_lang_rc_constructed
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
name|gimp_lang_rc_finalize
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
name|gimp_lang_rc_set_property
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
name|gimp_lang_rc_get_property
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

begin_comment
comment|/* Just use GimpConfig interface's default implementation which will  * fill the PROP_LANGUAGE property. */
end_comment

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpLangRc,gimp_lang_rc,G_TYPE_OBJECT,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,NULL))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpLangRc
argument_list|,
argument|gimp_lang_rc
argument_list|,
argument|G_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG, NULL)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_lang_rc_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_lang_rc_class_init
parameter_list|(
name|GimpLangRcClass
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
name|constructed
operator|=
name|gimp_lang_rc_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_lang_rc_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_lang_rc_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_lang_rc_get_property
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
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SYSTEM_GIMPRC
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"system-gimprc"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_TYPE_FILE
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_USER_GIMPRC
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"user-gimprc"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_TYPE_FILE
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_LANGUAGE
argument_list|,
literal|"language"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_lang_rc_init (GimpLangRc * rc)
name|gimp_lang_rc_init
parameter_list|(
name|GimpLangRc
modifier|*
name|rc
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_lang_rc_constructed (GObject * object)
name|gimp_lang_rc_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpLangRc
modifier|*
name|rc
init|=
name|GIMP_LANG_RC
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|rc
operator|->
name|verbose
condition|)
name|g_print
argument_list|(
literal|"Parsing '%s' for configured language.\n"
argument_list|,
name|gimp_file_get_utf8_name
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
name|gimp_config_deserialize_gfile
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
literal|"%s"
argument_list|,
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
literal|"Parsing '%s' for configured language.\n"
argument_list|,
name|gimp_file_get_utf8_name
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
name|gimp_config_deserialize_gfile
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
name|g_message
argument_list|(
literal|"%s"
argument_list|,
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
block|{
if|if
condition|(
name|rc
operator|->
name|language
condition|)
name|g_print
argument_list|(
literal|"Language property found: %s.\n"
argument_list|,
name|rc
operator|->
name|language
argument_list|)
expr_stmt|;
else|else
name|g_print
argument_list|(
literal|"No language property found.\n"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_lang_rc_finalize (GObject * object)
name|gimp_lang_rc_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpLangRc
modifier|*
name|rc
init|=
name|GIMP_LANG_RC
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|rc
operator|->
name|system_gimprc
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|rc
operator|->
name|user_gimprc
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|rc
operator|->
name|language
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
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
DECL|function|gimp_lang_rc_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_lang_rc_set_property
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
name|GimpLangRc
modifier|*
name|rc
init|=
name|GIMP_LANG_RC
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
if|if
condition|(
name|rc
operator|->
name|system_gimprc
condition|)
name|g_object_unref
argument_list|(
name|rc
operator|->
name|system_gimprc
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_object
argument_list|(
name|value
argument_list|)
condition|)
name|rc
operator|->
name|system_gimprc
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
else|else
name|rc
operator|->
name|system_gimprc
operator|=
name|gimp_sysconf_directory_file
argument_list|(
literal|"gimprc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USER_GIMPRC
case|:
if|if
condition|(
name|rc
operator|->
name|user_gimprc
condition|)
name|g_object_unref
argument_list|(
name|rc
operator|->
name|user_gimprc
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_object
argument_list|(
name|value
argument_list|)
condition|)
name|rc
operator|->
name|user_gimprc
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
else|else
name|rc
operator|->
name|user_gimprc
operator|=
name|gimp_directory_file
argument_list|(
literal|"gimprc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LANGUAGE
case|:
if|if
condition|(
name|rc
operator|->
name|language
condition|)
name|g_free
argument_list|(
name|rc
operator|->
name|language
argument_list|)
expr_stmt|;
name|rc
operator|->
name|language
operator|=
name|g_value_dup_string
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
DECL|function|gimp_lang_rc_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_lang_rc_get_property
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
name|GimpLangRc
modifier|*
name|rc
init|=
name|GIMP_LANG_RC
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
name|g_value_set_object
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
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|rc
operator|->
name|user_gimprc
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LANGUAGE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|rc
operator|->
name|language
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

begin_comment
comment|/**  * gimp_lang_rc_new:  * @system_gimprc: the name of the system-wide gimprc file or %NULL to  *                 use the standard location  * @user_gimprc:   the name of the user gimprc file or %NULL to use the  *                 standard location  * @verbose:       enable console messages about loading the language  *  * Creates a new GimpLangRc object which only looks for the configure  * language.  *  * Returns: the new #GimpLangRc.  */
end_comment

begin_function
name|GimpLangRc
modifier|*
DECL|function|gimp_lang_rc_new (GFile * system_gimprc,GFile * user_gimprc,gboolean verbose)
name|gimp_lang_rc_new
parameter_list|(
name|GFile
modifier|*
name|system_gimprc
parameter_list|,
name|GFile
modifier|*
name|user_gimprc
parameter_list|,
name|gboolean
name|verbose
parameter_list|)
block|{
name|GimpLangRc
modifier|*
name|rc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|system_gimprc
operator|==
name|NULL
operator|||
name|G_IS_FILE
argument_list|(
name|system_gimprc
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|user_gimprc
operator|==
name|NULL
operator|||
name|G_IS_FILE
argument_list|(
name|user_gimprc
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|rc
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_LANG_RC
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
expr_stmt|;
return|return
name|rc
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_lang_rc_get_language:  * @lang_rc:  a #GimpLangRc object.  *  * This function looks up the language set in `gimprc`.  *  * Returns: a newly allocated string representing the language or  *               %NULL if the key couldn't be found.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_lang_rc_get_language (GimpLangRc * rc)
name|gimp_lang_rc_get_language
parameter_list|(
name|GimpLangRc
modifier|*
name|rc
parameter_list|)
block|{
return|return
name|rc
operator|->
name|language
condition|?
name|g_strdup
argument_list|(
name|rc
operator|->
name|language
argument_list|)
else|:
name|NULL
return|;
block|}
end_function

end_unit

