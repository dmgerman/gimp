begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"gimpmemsize.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|memsize_to_string
parameter_list|(
specifier|const
name|GValue
modifier|*
name|src_value
parameter_list|,
name|GValue
modifier|*
name|dest_value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|string_to_memsize
parameter_list|(
specifier|const
name|GValue
modifier|*
name|src_value
parameter_list|,
name|GValue
modifier|*
name|dest_value
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_memsize_get_type (void)
name|gimp_memsize_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|memsize_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|memsize_type
condition|)
block|{
specifier|const
name|GTypeInfo
name|type_info
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|memsize_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_UINT64
argument_list|,
literal|"GimpMemsize"
argument_list|,
operator|&
name|type_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_value_register_transform_func
argument_list|(
name|memsize_type
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|memsize_to_string
argument_list|)
expr_stmt|;
name|g_value_register_transform_func
argument_list|(
name|G_TYPE_STRING
argument_list|,
name|memsize_type
argument_list|,
name|string_to_memsize
argument_list|)
expr_stmt|;
block|}
return|return
name|memsize_type
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_memsize_serialize:  * @memsize: memory size in bytes  *  * Creates a string representation of a given memory size. This string  * can be parsed by gimp_memsize_deserialize() and can thus be used in  * config files. It should not be displayed to the user. If you need a  * nice human-readable string please use gimp_memsize_to_string().  *  * Return value: A newly allocated string representation of @memsize.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_memsize_serialize (guint64 memsize)
name|gimp_memsize_serialize
parameter_list|(
name|guint64
name|memsize
parameter_list|)
block|{
if|if
condition|(
name|memsize
operator|>
operator|(
literal|1
operator|<<
literal|30
operator|)
operator|&&
name|memsize
operator|%
operator|(
literal|1
operator|<<
literal|30
operator|)
operator|==
literal|0
condition|)
return|return
name|g_strdup_printf
argument_list|(
literal|"%"
name|G_GUINT64_FORMAT
literal|"G"
argument_list|,
name|memsize
operator|>>
literal|30
argument_list|)
return|;
elseif|else
if|if
condition|(
name|memsize
operator|>
operator|(
literal|1
operator|<<
literal|20
operator|)
operator|&&
name|memsize
operator|%
operator|(
literal|1
operator|<<
literal|20
operator|)
operator|==
literal|0
condition|)
return|return
name|g_strdup_printf
argument_list|(
literal|"%"
name|G_GUINT64_FORMAT
literal|"M"
argument_list|,
name|memsize
operator|>>
literal|20
argument_list|)
return|;
elseif|else
if|if
condition|(
name|memsize
operator|>
operator|(
literal|1
operator|<<
literal|10
operator|)
operator|&&
name|memsize
operator|%
operator|(
literal|1
operator|<<
literal|10
operator|)
operator|==
literal|0
condition|)
return|return
name|g_strdup_printf
argument_list|(
literal|"%"
name|G_GUINT64_FORMAT
literal|"k"
argument_list|,
name|memsize
operator|>>
literal|10
argument_list|)
return|;
else|else
return|return
name|g_strdup_printf
argument_list|(
literal|"%"
name|G_GUINT64_FORMAT
argument_list|,
name|memsize
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_memsize_deserialize:  * @string:  a string as returned by gimp_memsize_serialize()  * @memsize: return location for memory size in bytes  *  * Parses a string representation of a memory size as returned by  * gimp_memsize_serialize().  *  * Return value: %TRUE if the @string was successfully parsed and  *               @memsize has been set, %FALSE otherwise.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_memsize_deserialize (const gchar * string,guint64 * memsize)
name|gimp_memsize_deserialize
parameter_list|(
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
name|guint64
modifier|*
name|memsize
parameter_list|)
block|{
name|gchar
modifier|*
name|end
decl_stmt|;
name|guint64
name|size
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|string
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|memsize
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|size
operator|=
name|g_ascii_strtoull
argument_list|(
name|string
argument_list|,
operator|&
name|end
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|size
operator|==
name|G_MAXUINT64
operator|&&
name|errno
operator|==
name|ERANGE
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|end
operator|&&
operator|*
name|end
condition|)
block|{
name|guint
name|shift
decl_stmt|;
switch|switch
condition|(
name|g_ascii_tolower
argument_list|(
operator|*
name|end
argument_list|)
condition|)
block|{
case|case
literal|'b'
case|:
name|shift
operator|=
literal|0
expr_stmt|;
break|break;
case|case
literal|'k'
case|:
name|shift
operator|=
literal|10
expr_stmt|;
break|break;
case|case
literal|'m'
case|:
name|shift
operator|=
literal|20
expr_stmt|;
break|break;
case|case
literal|'g'
case|:
name|shift
operator|=
literal|30
expr_stmt|;
break|break;
default|default:
return|return
name|FALSE
return|;
block|}
comment|/* protect against overflow */
if|if
condition|(
name|shift
condition|)
block|{
name|guint64
name|limit
init|=
name|G_MAXUINT64
operator|>>
name|shift
decl_stmt|;
if|if
condition|(
name|size
operator|!=
operator|(
name|size
operator|&
name|limit
operator|)
condition|)
return|return
name|FALSE
return|;
name|size
operator|<<=
name|shift
expr_stmt|;
block|}
block|}
operator|*
name|memsize
operator|=
name|size
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_memsize_to_string:  * @memsize: A memory size in bytes.  *  * This function returns a human readable, translated representation  * of the passed @memsize. Large values are displayed using a  * reasonable memsize unit, e.g.: "345" becomes "345 Bytes", "4500"  * becomes "4.4 KB" and so on.  *  * Return value: A newly allocated human-readable, translated string.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_memsize_to_string (guint64 memsize)
name|gimp_memsize_to_string
parameter_list|(
name|guint64
name|memsize
parameter_list|)
block|{
if|#
directive|if
name|defined
name|_MSC_VER
operator|&&
operator|(
name|_MSC_VER
operator|<
literal|1300
operator|)
comment|/* sorry, error C2520: conversion from unsigned __int64 to double not  *                     implemented, use signed __int64  */
DECL|macro|CAST_DOUBLE
define|#
directive|define
name|CAST_DOUBLE
value|(gdouble)(gint64)
else|#
directive|else
define|#
directive|define
name|CAST_DOUBLE
value|(gdouble)
endif|#
directive|endif
if|if
condition|(
name|memsize
operator|<
literal|1024
condition|)
block|{
name|gint
name|bytes
init|=
operator|(
name|gint
operator|)
name|memsize
decl_stmt|;
return|return
name|g_strdup_printf
argument_list|(
name|dngettext
argument_list|(
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|,
literal|"%d Byte"
argument_list|,
literal|"%d Bytes"
argument_list|,
name|bytes
argument_list|)
argument_list|,
name|bytes
argument_list|)
return|;
block|}
if|if
condition|(
name|memsize
operator|<
literal|1024
operator|*
literal|10
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
argument|_(
literal|"%.2f KB"
argument|)
argument_list|,
argument|CAST_DOUBLE memsize /
literal|1024.0
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|memsize
operator|<
literal|1024
operator|*
literal|100
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
argument|_(
literal|"%.1f KB"
argument|)
argument_list|,
argument|CAST_DOUBLE memsize /
literal|1024.0
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|memsize
operator|<
literal|1024
operator|*
literal|1024
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%d KB"
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
name|memsize
operator|/
literal|1024
argument_list|)
return|;
block|}
name|memsize
operator|/=
literal|1024
expr_stmt|;
if|if
condition|(
name|memsize
operator|<
literal|1024
operator|*
literal|10
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
argument|_(
literal|"%.2f MB"
argument|)
argument_list|,
argument|CAST_DOUBLE memsize /
literal|1024.0
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|memsize
operator|<
literal|1024
operator|*
literal|100
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
argument|_(
literal|"%.1f MB"
argument|)
argument_list|,
argument|CAST_DOUBLE memsize /
literal|1024.0
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|memsize
operator|<
literal|1024
operator|*
literal|1024
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%d MB"
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
name|memsize
operator|/
literal|1024
argument_list|)
return|;
block|}
name|memsize
operator|/=
literal|1024
expr_stmt|;
if|if
condition|(
name|memsize
operator|<
literal|1024
operator|*
literal|10
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
argument|_(
literal|"%.2f GB"
argument|)
argument_list|,
argument|CAST_DOUBLE memsize /
literal|1024.0
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|memsize
operator|<
literal|1024
operator|*
literal|100
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
argument|_(
literal|"%.1f GB"
argument|)
argument_list|,
argument|CAST_DOUBLE memsize /
literal|1024.0
argument_list|)
return|;
block|}
else|else
block|{
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%d GB"
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
name|memsize
operator|/
literal|1024
argument_list|)
return|;
block|}
undef|#
directive|undef
name|CAST_DOUBLE
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|memsize_to_string (const GValue * src_value,GValue * dest_value)
name|memsize_to_string
parameter_list|(
specifier|const
name|GValue
modifier|*
name|src_value
parameter_list|,
name|GValue
modifier|*
name|dest_value
parameter_list|)
block|{
name|g_value_take_string
argument_list|(
name|dest_value
argument_list|,
name|gimp_memsize_serialize
argument_list|(
name|g_value_get_uint64
argument_list|(
name|src_value
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|string_to_memsize (const GValue * src_value,GValue * dest_value)
name|string_to_memsize
parameter_list|(
specifier|const
name|GValue
modifier|*
name|src_value
parameter_list|,
name|GValue
modifier|*
name|dest_value
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|str
decl_stmt|;
name|guint64
name|memsize
decl_stmt|;
name|str
operator|=
name|g_value_get_string
argument_list|(
name|src_value
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|str
operator|||
operator|!
name|gimp_memsize_deserialize
argument_list|(
name|str
argument_list|,
operator|&
name|memsize
argument_list|)
condition|)
name|g_warning
argument_list|(
literal|"Can't convert string to GimpMemsize."
argument_list|)
expr_stmt|;
name|g_value_set_uint64
argument_list|(
name|dest_value
argument_list|,
name|memsize
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * GIMP_TYPE_PARAM_MEMSIZE  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_param_memsize_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_param_memsize_get_type:  *  * Reveals the object type  *  * Returns: the #GType for a memsize object  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|GType
DECL|function|gimp_param_memsize_get_type (void)
name|gimp_param_memsize_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|spec_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|spec_type
condition|)
block|{
specifier|const
name|GTypeInfo
name|type_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GParamSpecClass
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_param_memsize_class_init
block|,
name|NULL
block|,
name|NULL
block|,
sizeof|sizeof
argument_list|(
name|GParamSpecUInt64
argument_list|)
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
name|spec_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_PARAM_UINT64
argument_list|,
literal|"GimpParamMemsize"
argument_list|,
operator|&
name|type_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|spec_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_memsize_class_init (GParamSpecClass * class)
name|gimp_param_memsize_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
block|{
name|class
operator|->
name|value_type
operator|=
name|GIMP_TYPE_MEMSIZE
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_param_spec_memsize:  * @name:          Canonical name of the param  * @nick:          Nickname of the param  * @blurb:         Brief desciption of param.  * @minimum:       Smallest allowed value of the parameter.  * @maximum:       Largest allowed value of the parameter.  * @default_value: Value to use if none is assigned.  * @flags:         a combination of #GParamFlags  *  * Creates a param spec to hold a memory size value.  * See g_param_spec_internal() for more information.  *  * Returns: a newly allocated #GParamSpec instance  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|GParamSpec
modifier|*
DECL|function|gimp_param_spec_memsize (const gchar * name,const gchar * nick,const gchar * blurb,guint64 minimum,guint64 maximum,guint64 default_value,GParamFlags flags)
name|gimp_param_spec_memsize
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|guint64
name|minimum
parameter_list|,
name|guint64
name|maximum
parameter_list|,
name|guint64
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GParamSpecUInt64
modifier|*
name|pspec
decl_stmt|;
name|pspec
operator|=
name|g_param_spec_internal
argument_list|(
name|GIMP_TYPE_PARAM_MEMSIZE
argument_list|,
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|pspec
operator|->
name|minimum
operator|=
name|minimum
expr_stmt|;
name|pspec
operator|->
name|maximum
operator|=
name|maximum
expr_stmt|;
name|pspec
operator|->
name|default_value
operator|=
name|default_value
expr_stmt|;
return|return
name|G_PARAM_SPEC
argument_list|(
name|pspec
argument_list|)
return|;
block|}
end_function

end_unit

