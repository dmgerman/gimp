begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<locale.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE__NL_MEASUREMENT_MEASUREMENT
end_ifdef

begin_include
include|#
directive|include
file|<langinfo.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<sys/types.h>
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
file|<glib.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<process.h>
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
file|<gobject/gvaluecollector.h>
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
file|"config/gimpbaseconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpparamspecs.h"
end_include

begin_function
name|gint64
DECL|function|gimp_g_type_instance_get_memsize (GTypeInstance * instance)
name|gimp_g_type_instance_get_memsize
parameter_list|(
name|GTypeInstance
modifier|*
name|instance
parameter_list|)
block|{
name|GTypeQuery
name|type_query
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|instance
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_query
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|instance
argument_list|)
argument_list|,
operator|&
name|type_query
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|type_query
operator|.
name|instance_size
expr_stmt|;
return|return
name|memsize
return|;
block|}
end_function

begin_function
name|gint64
DECL|function|gimp_g_object_get_memsize (GObject * object)
name|gimp_g_object_get_memsize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|memsize
operator|+
name|gimp_g_type_instance_get_memsize
argument_list|(
operator|(
name|GTypeInstance
operator|*
operator|)
name|object
argument_list|)
return|;
block|}
end_function

begin_function
name|gint64
DECL|function|gimp_g_hash_table_get_memsize (GHashTable * hash)
name|gimp_g_hash_table_get_memsize
parameter_list|(
name|GHashTable
modifier|*
name|hash
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|hash
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
operator|(
literal|2
operator|*
sizeof|sizeof
argument_list|(
name|gint
argument_list|)
operator|+
literal|5
operator|*
sizeof|sizeof
argument_list|(
name|gpointer
argument_list|)
operator|+
name|g_hash_table_size
argument_list|(
name|hash
argument_list|)
operator|*
literal|3
operator|*
sizeof|sizeof
argument_list|(
name|gpointer
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
name|gint64
DECL|function|gimp_g_slist_get_memsize (GSList * slist,gint64 data_size)
name|gimp_g_slist_get_memsize
parameter_list|(
name|GSList
modifier|*
name|slist
parameter_list|,
name|gint64
name|data_size
parameter_list|)
block|{
return|return
name|g_slist_length
argument_list|(
name|slist
argument_list|)
operator|*
operator|(
name|data_size
operator|+
sizeof|sizeof
argument_list|(
name|GSList
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
name|gint64
DECL|function|gimp_g_list_get_memsize (GList * list,gint64 data_size)
name|gimp_g_list_get_memsize
parameter_list|(
name|GList
modifier|*
name|list
parameter_list|,
name|gint64
name|data_size
parameter_list|)
block|{
return|return
name|g_list_length
argument_list|(
name|list
argument_list|)
operator|*
operator|(
name|data_size
operator|+
sizeof|sizeof
argument_list|(
name|GList
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
name|gint64
DECL|function|gimp_g_value_get_memsize (GValue * value)
name|gimp_g_value_get_memsize
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|gint64
name|memsize
init|=
sizeof|sizeof
argument_list|(
name|GValue
argument_list|)
decl_stmt|;
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
name|str
init|=
name|g_value_get_string
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|str
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|str
argument_list|)
operator|+
literal|1
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_BOXED
argument_list|(
name|value
argument_list|)
condition|)
block|{
if|if
condition|(
name|GIMP_VALUE_HOLDS_RGB
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|memsize
operator|+=
sizeof|sizeof
argument_list|(
name|GimpRGB
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_MATRIX2
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|memsize
operator|+=
sizeof|sizeof
argument_list|(
name|GimpMatrix2
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_PARASITE
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|GimpParasite
modifier|*
name|parasite
init|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|parasite
condition|)
name|memsize
operator|+=
operator|(
sizeof|sizeof
argument_list|(
name|GimpParasite
argument_list|)
operator|+
name|parasite
operator|->
name|size
operator|+
name|parasite
operator|->
name|name
condition|?
operator|(
name|strlen
argument_list|(
name|parasite
operator|->
name|name
argument_list|)
operator|+
literal|1
operator|)
else|:
literal|0
operator|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_ARRAY
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_INT8_ARRAY
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_INT16_ARRAY
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_INT32_ARRAY
argument_list|(
name|value
argument_list|)
operator|||
name|GIMP_VALUE_HOLDS_FLOAT_ARRAY
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|GimpArray
modifier|*
name|array
init|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|array
condition|)
name|memsize
operator|+=
operator|(
sizeof|sizeof
argument_list|(
name|GimpArray
argument_list|)
operator|+
name|array
operator|->
name|static_data
condition|?
literal|0
else|:
name|array
operator|->
name|length
operator|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_VALUE_HOLDS_STRING_ARRAY
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|GimpArray
modifier|*
name|array
init|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|array
condition|)
block|{
name|memsize
operator|+=
sizeof|sizeof
argument_list|(
name|GimpArray
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|array
operator|->
name|static_data
condition|)
block|{
name|gchar
modifier|*
modifier|*
name|tmp
init|=
operator|(
name|gchar
operator|*
operator|*
operator|)
name|array
operator|->
name|data
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|memsize
operator|+=
name|array
operator|->
name|length
operator|*
sizeof|sizeof
argument_list|(
name|gchar
operator|*
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
name|length
condition|;
name|i
operator|++
control|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|tmp
index|[
name|i
index|]
argument_list|)
operator|+
literal|1
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"%s: unhandled boxed value type: %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|G_VALUE_TYPE_NAME
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|G_VALUE_HOLDS_OBJECT
argument_list|(
name|value
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: unhandled object value type: %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|G_VALUE_TYPE_NAME
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|memsize
return|;
block|}
end_function

begin_function
name|gint64
DECL|function|gimp_g_param_spec_get_memsize (GParamSpec * pspec)
name|gimp_g_param_spec_get_memsize
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|str
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|pspec
operator|->
name|flags
operator|&
name|G_PARAM_STATIC_NAME
operator|)
condition|)
block|{
name|str
operator|=
name|g_param_spec_get_name
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
if|if
condition|(
name|str
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|str
argument_list|)
operator|+
literal|1
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
name|pspec
operator|->
name|flags
operator|&
name|G_PARAM_STATIC_NICK
operator|)
condition|)
block|{
name|str
operator|=
name|g_param_spec_get_nick
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
if|if
condition|(
name|str
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|str
argument_list|)
operator|+
literal|1
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
name|pspec
operator|->
name|flags
operator|&
name|G_PARAM_STATIC_BLURB
operator|)
condition|)
block|{
name|str
operator|=
name|g_param_spec_get_blurb
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
if|if
condition|(
name|str
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|str
argument_list|)
operator|+
literal|1
expr_stmt|;
block|}
return|return
name|memsize
operator|+
name|gimp_g_type_instance_get_memsize
argument_list|(
operator|(
name|GTypeInstance
operator|*
operator|)
name|pspec
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  *  basically copied from gtk_get_default_language()  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_get_default_language (const gchar * category)
name|gimp_get_default_language
parameter_list|(
specifier|const
name|gchar
modifier|*
name|category
parameter_list|)
block|{
name|gchar
modifier|*
name|lang
decl_stmt|;
name|gchar
modifier|*
name|p
decl_stmt|;
name|gint
name|cat
init|=
name|LC_CTYPE
decl_stmt|;
if|if
condition|(
operator|!
name|category
condition|)
name|category
operator|=
literal|"LC_CTYPE"
expr_stmt|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|p
operator|=
name|getenv
argument_list|(
literal|"LC_ALL"
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|!=
name|NULL
condition|)
name|lang
operator|=
name|g_strdup
argument_list|(
name|p
argument_list|)
expr_stmt|;
else|else
block|{
name|p
operator|=
name|getenv
argument_list|(
literal|"LANG"
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|!=
name|NULL
condition|)
name|lang
operator|=
name|g_strdup
argument_list|(
name|p
argument_list|)
expr_stmt|;
else|else
block|{
name|p
operator|=
name|getenv
argument_list|(
name|category
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|!=
name|NULL
condition|)
name|lang
operator|=
name|g_strdup
argument_list|(
name|p
argument_list|)
expr_stmt|;
else|else
name|lang
operator|=
name|g_win32_getlocale
argument_list|()
expr_stmt|;
block|}
block|}
else|#
directive|else
if|if
condition|(
name|strcmp
argument_list|(
name|category
argument_list|,
literal|"LC_CTYPE"
argument_list|)
operator|==
literal|0
condition|)
name|cat
operator|=
name|LC_CTYPE
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|category
argument_list|,
literal|"LC_MESSAGES"
argument_list|)
operator|==
literal|0
condition|)
name|cat
operator|=
name|LC_MESSAGES
expr_stmt|;
else|else
name|g_warning
argument_list|(
literal|"unsupported category used with gimp_get_default_language()"
argument_list|)
expr_stmt|;
name|lang
operator|=
name|g_strdup
argument_list|(
name|setlocale
argument_list|(
name|cat
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|p
operator|=
name|strchr
argument_list|(
name|lang
argument_list|,
literal|'.'
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
condition|)
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
name|p
operator|=
name|strchr
argument_list|(
name|lang
argument_list|,
literal|'@'
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
condition|)
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
return|return
name|lang
return|;
block|}
end_function

begin_function
name|GimpUnit
DECL|function|gimp_get_default_unit (void)
name|gimp_get_default_unit
parameter_list|(
name|void
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|HAVE__NL_MEASUREMENT_MEASUREMENT
specifier|const
name|gchar
modifier|*
name|measurement
init|=
name|nl_langinfo
argument_list|(
name|_NL_MEASUREMENT_MEASUREMENT
argument_list|)
decl_stmt|;
switch|switch
condition|(
operator|*
operator|(
operator|(
name|guchar
operator|*
operator|)
name|measurement
operator|)
condition|)
block|{
case|case
literal|1
case|:
comment|/* metric   */
return|return
name|GIMP_UNIT_MM
return|;
case|case
literal|2
case|:
comment|/* imperial */
return|return
name|GIMP_UNIT_INCH
return|;
block|}
endif|#
directive|endif
return|return
name|GIMP_UNIT_INCH
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_boolean_handled_accum (GSignalInvocationHint * ihint,GValue * return_accu,const GValue * handler_return,gpointer dummy)
name|gimp_boolean_handled_accum
parameter_list|(
name|GSignalInvocationHint
modifier|*
name|ihint
parameter_list|,
name|GValue
modifier|*
name|return_accu
parameter_list|,
specifier|const
name|GValue
modifier|*
name|handler_return
parameter_list|,
name|gpointer
name|dummy
parameter_list|)
block|{
name|gboolean
name|continue_emission
decl_stmt|;
name|gboolean
name|signal_handled
decl_stmt|;
name|signal_handled
operator|=
name|g_value_get_boolean
argument_list|(
name|handler_return
argument_list|)
expr_stmt|;
name|g_value_set_boolean
argument_list|(
name|return_accu
argument_list|,
name|signal_handled
argument_list|)
expr_stmt|;
name|continue_emission
operator|=
operator|!
name|signal_handled
expr_stmt|;
return|return
name|continue_emission
return|;
block|}
end_function

begin_function
name|GParameter
modifier|*
DECL|function|gimp_parameters_append (GType object_type,GParameter * params,gint * n_params,...)
name|gimp_parameters_append
parameter_list|(
name|GType
name|object_type
parameter_list|,
name|GParameter
modifier|*
name|params
parameter_list|,
name|gint
modifier|*
name|n_params
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|object_type
argument_list|,
name|G_TYPE_OBJECT
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_params
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|params
operator|!=
name|NULL
operator|||
operator|*
name|n_params
operator|==
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|n_params
argument_list|)
expr_stmt|;
name|params
operator|=
name|gimp_parameters_append_valist
argument_list|(
name|object_type
argument_list|,
name|params
argument_list|,
name|n_params
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return
name|params
return|;
block|}
end_function

begin_function
name|GParameter
modifier|*
DECL|function|gimp_parameters_append_valist (GType object_type,GParameter * params,gint * n_params,va_list args)
name|gimp_parameters_append_valist
parameter_list|(
name|GType
name|object_type
parameter_list|,
name|GParameter
modifier|*
name|params
parameter_list|,
name|gint
modifier|*
name|n_params
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|gchar
modifier|*
name|param_name
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|object_type
argument_list|,
name|G_TYPE_OBJECT
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_params
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|params
operator|!=
name|NULL
operator|||
operator|*
name|n_params
operator|==
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|object_class
operator|=
name|g_type_class_ref
argument_list|(
name|object_type
argument_list|)
expr_stmt|;
name|param_name
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gchar
operator|*
argument_list|)
expr_stmt|;
while|while
condition|(
name|param_name
condition|)
block|{
name|gchar
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|GParamSpec
modifier|*
name|pspec
init|=
name|g_object_class_find_property
argument_list|(
name|object_class
argument_list|,
name|param_name
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|pspec
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: object class `%s' has no property named `%s'"
argument_list|,
name|G_STRFUNC
argument_list|,
name|g_type_name
argument_list|(
name|object_type
argument_list|)
argument_list|,
name|param_name
argument_list|)
expr_stmt|;
break|break;
block|}
name|params
operator|=
name|g_renew
argument_list|(
name|GParameter
argument_list|,
name|params
argument_list|,
operator|*
name|n_params
operator|+
literal|1
argument_list|)
expr_stmt|;
name|params
index|[
operator|*
name|n_params
index|]
operator|.
name|name
operator|=
name|param_name
expr_stmt|;
name|params
index|[
operator|*
name|n_params
index|]
operator|.
name|value
operator|.
name|g_type
operator|=
literal|0
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|params
index|[
operator|*
name|n_params
index|]
operator|.
name|value
argument_list|,
name|G_PARAM_SPEC_VALUE_TYPE
argument_list|(
name|pspec
argument_list|)
argument_list|)
expr_stmt|;
name|G_VALUE_COLLECT
argument_list|(
operator|&
name|params
index|[
operator|*
name|n_params
index|]
operator|.
name|value
argument_list|,
name|args
argument_list|,
literal|0
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: %s"
argument_list|,
name|G_STRFUNC
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|params
index|[
operator|*
name|n_params
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
break|break;
block|}
operator|*
name|n_params
operator|=
operator|*
name|n_params
operator|+
literal|1
expr_stmt|;
name|param_name
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gchar
operator|*
argument_list|)
expr_stmt|;
block|}
name|g_type_class_unref
argument_list|(
name|object_class
argument_list|)
expr_stmt|;
return|return
name|params
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_parameters_free (GParameter * params,gint n_params)
name|gimp_parameters_free
parameter_list|(
name|GParameter
modifier|*
name|params
parameter_list|,
name|gint
name|n_params
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|params
operator|!=
name|NULL
operator|||
name|n_params
operator|==
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|params
condition|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_params
condition|;
name|i
operator|++
control|)
name|g_value_unset
argument_list|(
operator|&
name|params
index|[
name|i
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|params
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_value_array_truncate (GValueArray * args,gint n_values)
name|gimp_value_array_truncate
parameter_list|(
name|GValueArray
modifier|*
name|args
parameter_list|,
name|gint
name|n_values
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|args
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|n_values
operator|>
literal|0
operator|&&
name|n_values
operator|<=
name|args
operator|->
name|n_values
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
name|args
operator|->
name|n_values
init|;
name|i
operator|>
name|n_values
condition|;
name|i
operator|--
control|)
name|g_value_array_remove
argument_list|(
name|args
argument_list|,
name|i
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_get_temp_filename (Gimp * gimp,const gchar * extension)
name|gimp_get_temp_filename
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|)
block|{
specifier|static
name|gint
name|id
init|=
literal|0
decl_stmt|;
specifier|static
name|gint
name|pid
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|path
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|extension
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|id
operator|==
literal|0
condition|)
name|pid
operator|=
name|getpid
argument_list|()
expr_stmt|;
name|basename
operator|=
name|g_strdup_printf
argument_list|(
literal|"gimp-temp-%d%d.%s"
argument_list|,
name|pid
argument_list|,
name|id
operator|++
argument_list|,
name|extension
argument_list|)
expr_stmt|;
name|path
operator|=
name|gimp_config_path_expand
argument_list|(
name|GIMP_BASE_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|temp_path
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|path
argument_list|,
name|basename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
return|return
name|filename
return|;
block|}
end_function

end_unit

