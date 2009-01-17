begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"gimpparamspecs-desc.h"
end_include

begin_function
specifier|static
specifier|inline
specifier|const
name|gchar
modifier|*
DECL|function|gimp_param_spec_get_blurb (GParamSpec * pspec)
name|gimp_param_spec_get_blurb
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|blurb
init|=
name|g_param_spec_get_blurb
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
return|return
name|blurb
condition|?
name|blurb
else|:
literal|""
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_param_spec_boolean_desc (GParamSpec * pspec)
name|gimp_param_spec_boolean_desc
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|blurb
init|=
name|gimp_param_spec_get_blurb
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
return|return
name|g_strconcat
argument_list|(
name|blurb
argument_list|,
literal|" (TRUE or FALSE)"
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_param_spec_int32_desc (GParamSpec * pspec)
name|gimp_param_spec_int32_desc
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GParamSpecInt
modifier|*
name|ispec
init|=
name|G_PARAM_SPEC_INT
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|blurb
init|=
name|gimp_param_spec_get_blurb
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
if|if
condition|(
name|ispec
operator|->
name|minimum
operator|==
name|G_MININT32
operator|&&
name|ispec
operator|->
name|maximum
operator|==
name|G_MAXINT32
condition|)
return|return
name|g_strdup
argument_list|(
name|blurb
argument_list|)
return|;
if|if
condition|(
name|ispec
operator|->
name|minimum
operator|==
name|G_MININT32
condition|)
return|return
name|g_strdup_printf
argument_list|(
literal|"%s (%s<= %d)"
argument_list|,
name|blurb
argument_list|,
name|g_param_spec_get_name
argument_list|(
name|pspec
argument_list|)
argument_list|,
name|ispec
operator|->
name|maximum
argument_list|)
return|;
if|if
condition|(
name|ispec
operator|->
name|maximum
operator|==
name|G_MAXINT32
condition|)
return|return
name|g_strdup_printf
argument_list|(
literal|"%s (%s>= %d)"
argument_list|,
name|blurb
argument_list|,
name|g_param_spec_get_name
argument_list|(
name|pspec
argument_list|)
argument_list|,
name|ispec
operator|->
name|minimum
argument_list|)
return|;
return|return
name|g_strdup_printf
argument_list|(
literal|"%s (%d<= %s<= %d)"
argument_list|,
name|blurb
argument_list|,
name|ispec
operator|->
name|minimum
argument_list|,
name|g_param_spec_get_name
argument_list|(
name|pspec
argument_list|)
argument_list|,
name|ispec
operator|->
name|maximum
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_param_spec_double_desc (GParamSpec * pspec)
name|gimp_param_spec_double_desc
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GParamSpecDouble
modifier|*
name|dspec
init|=
name|G_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|blurb
init|=
name|gimp_param_spec_get_blurb
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
if|if
condition|(
name|dspec
operator|->
name|minimum
operator|==
operator|-
name|G_MAXDOUBLE
operator|&&
name|dspec
operator|->
name|maximum
operator|==
name|G_MAXDOUBLE
condition|)
return|return
name|g_strdup
argument_list|(
name|blurb
argument_list|)
return|;
if|if
condition|(
name|dspec
operator|->
name|minimum
operator|==
operator|-
name|G_MAXDOUBLE
condition|)
return|return
name|g_strdup_printf
argument_list|(
literal|"%s (%s<= %g)"
argument_list|,
name|blurb
argument_list|,
name|g_param_spec_get_name
argument_list|(
name|pspec
argument_list|)
argument_list|,
name|dspec
operator|->
name|maximum
argument_list|)
return|;
if|if
condition|(
name|dspec
operator|->
name|maximum
operator|==
name|G_MAXDOUBLE
condition|)
return|return
name|g_strdup_printf
argument_list|(
literal|"%s (%s>= %g)"
argument_list|,
name|blurb
argument_list|,
name|g_param_spec_get_name
argument_list|(
name|pspec
argument_list|)
argument_list|,
name|dspec
operator|->
name|minimum
argument_list|)
return|;
return|return
name|g_strdup_printf
argument_list|(
literal|"%s (%g<= %s<= %g)"
argument_list|,
name|blurb
argument_list|,
name|dspec
operator|->
name|minimum
argument_list|,
name|g_param_spec_get_name
argument_list|(
name|pspec
argument_list|)
argument_list|,
name|dspec
operator|->
name|maximum
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_param_spec_enum_desc (GParamSpec * pspec)
name|gimp_param_spec_enum_desc
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|blurb
init|=
name|gimp_param_spec_get_blurb
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|GString
modifier|*
name|str
init|=
name|g_string_new
argument_list|(
name|blurb
argument_list|)
decl_stmt|;
name|GEnumClass
modifier|*
name|enum_class
init|=
name|g_type_class_peek
argument_list|(
name|pspec
operator|->
name|value_type
argument_list|)
decl_stmt|;
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
name|GSList
modifier|*
name|excluded
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|n
decl_stmt|;
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_ENUM
argument_list|(
name|pspec
argument_list|)
condition|)
name|excluded
operator|=
name|GIMP_PARAM_SPEC_ENUM
argument_list|(
name|pspec
argument_list|)
operator|->
name|excluded_values
expr_stmt|;
else|else
name|excluded
operator|=
name|NULL
expr_stmt|;
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|" { "
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|n
operator|=
literal|0
operator|,
name|enum_value
operator|=
name|enum_class
operator|->
name|values
init|;
name|i
operator|<
name|enum_class
operator|->
name|n_values
condition|;
name|i
operator|++
operator|,
name|enum_value
operator|++
control|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
for|for
control|(
name|list
operator|=
name|excluded
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|gint
name|value
init|=
name|GPOINTER_TO_INT
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|value
operator|==
name|enum_value
operator|->
name|value
condition|)
break|break;
block|}
if|if
condition|(
name|list
condition|)
continue|continue;
if|if
condition|(
name|n
operator|>
literal|0
condition|)
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|", "
argument_list|)
expr_stmt|;
if|if
condition|(
name|G_LIKELY
argument_list|(
name|g_str_has_prefix
argument_list|(
name|enum_value
operator|->
name|value_name
argument_list|,
literal|"GIMP_"
argument_list|)
argument_list|)
condition|)
name|name
operator|=
name|gimp_canonicalize_identifier
argument_list|(
name|enum_value
operator|->
name|value_name
operator|+
literal|5
argument_list|)
expr_stmt|;
else|else
name|name
operator|=
name|gimp_canonicalize_identifier
argument_list|(
name|enum_value
operator|->
name|value_name
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|str
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|" (%d)"
argument_list|,
name|enum_value
operator|->
name|value
argument_list|)
expr_stmt|;
name|n
operator|++
expr_stmt|;
block|}
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|" }"
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
comment|/**  * gimp_param_spec_get_desc:  * @pspec: a #GParamSpec  *  * This function creates a description of the passed @pspec, which is  * suitable for use in the PDB.  Actually, it currently only deals with  * parameter types used in the PDB and should not be used for anything  * else.  *  * Return value: A newly allocated string describing the parameter.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_param_spec_get_desc (GParamSpec * pspec)
name|gimp_param_spec_get_desc
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|G_IS_PARAM_SPEC
argument_list|(
name|pspec
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_UNIT
argument_list|(
name|pspec
argument_list|)
condition|)
block|{     }
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_INT32
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
return|return
name|gimp_param_spec_int32_desc
argument_list|(
name|pspec
argument_list|)
return|;
block|}
else|else
block|{
switch|switch
condition|(
name|G_TYPE_FUNDAMENTAL
argument_list|(
name|pspec
operator|->
name|value_type
argument_list|)
condition|)
block|{
case|case
name|G_TYPE_BOOLEAN
case|:
return|return
name|gimp_param_spec_boolean_desc
argument_list|(
name|pspec
argument_list|)
return|;
case|case
name|G_TYPE_DOUBLE
case|:
return|return
name|gimp_param_spec_double_desc
argument_list|(
name|pspec
argument_list|)
return|;
case|case
name|G_TYPE_ENUM
case|:
return|return
name|gimp_param_spec_enum_desc
argument_list|(
name|pspec
argument_list|)
return|;
block|}
block|}
return|return
name|g_strdup
argument_list|(
name|g_param_spec_get_blurb
argument_list|(
name|pspec
argument_list|)
argument_list|)
return|;
block|}
end_function

end_unit

