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
file|<stdarg.h>
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
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-run.h"
end_include

begin_include
include|#
directive|include
file|"gimpargument.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_procedure_free_strings
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpProcedure
modifier|*
DECL|function|gimp_procedure_new (void)
name|gimp_procedure_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|g_new0
argument_list|(
name|GimpProcedure
argument_list|,
literal|1
argument_list|)
decl_stmt|;
return|return
name|procedure
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_procedure_free (GimpProcedure * procedure)
name|gimp_procedure_free
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_free_strings
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
operator|->
name|args
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|procedure
operator|->
name|num_args
condition|;
name|i
operator|++
control|)
name|g_param_spec_unref
argument_list|(
name|procedure
operator|->
name|args
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|procedure
operator|->
name|args
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|args
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|procedure
operator|->
name|values
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|procedure
operator|->
name|num_values
condition|;
name|i
operator|++
control|)
name|g_param_spec_unref
argument_list|(
name|procedure
operator|->
name|values
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|procedure
operator|->
name|values
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|values
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|procedure
operator|->
name|static_proc
condition|)
name|g_free
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpProcedure
modifier|*
DECL|function|gimp_procedure_init (GimpProcedure * procedure,gint n_arguments,gint n_return_values)
name|gimp_procedure_init
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gint
name|n_arguments
parameter_list|,
name|gint
name|n_return_values
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|procedure
operator|->
name|args
operator|==
name|NULL
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|procedure
operator|->
name|values
operator|==
name|NULL
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_arguments
operator|>=
literal|0
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_return_values
operator|>=
literal|0
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|num_args
operator|=
name|n_arguments
expr_stmt|;
name|procedure
operator|->
name|args
operator|=
name|g_new0
argument_list|(
name|GParamSpec
operator|*
argument_list|,
name|n_arguments
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|num_values
operator|=
name|n_return_values
expr_stmt|;
name|procedure
operator|->
name|values
operator|=
name|g_new0
argument_list|(
name|GParamSpec
operator|*
argument_list|,
name|n_return_values
argument_list|)
expr_stmt|;
return|return
name|procedure
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_procedure_set_strings (GimpProcedure * procedure,gchar * name,gchar * original_name,gchar * blurb,gchar * help,gchar * author,gchar * copyright,gchar * date,gchar * deprecated)
name|gimp_procedure_set_strings
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|original_name
parameter_list|,
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
name|date
parameter_list|,
name|gchar
modifier|*
name|deprecated
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_free_strings
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|original_name
operator|=
name|g_strdup
argument_list|(
name|original_name
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|blurb
operator|=
name|g_strdup
argument_list|(
name|blurb
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|help
operator|=
name|g_strdup
argument_list|(
name|help
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|author
operator|=
name|g_strdup
argument_list|(
name|author
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|copyright
operator|=
name|g_strdup
argument_list|(
name|copyright
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|date
operator|=
name|g_strdup
argument_list|(
name|date
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|deprecated
operator|=
name|g_strdup
argument_list|(
name|deprecated
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|static_strings
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_procedure_set_static_strings (GimpProcedure * procedure,gchar * name,gchar * original_name,gchar * blurb,gchar * help,gchar * author,gchar * copyright,gchar * date,gchar * deprecated)
name|gimp_procedure_set_static_strings
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|original_name
parameter_list|,
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
name|date
parameter_list|,
name|gchar
modifier|*
name|deprecated
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_free_strings
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|name
operator|=
name|name
expr_stmt|;
name|procedure
operator|->
name|original_name
operator|=
name|original_name
expr_stmt|;
name|procedure
operator|->
name|blurb
operator|=
name|blurb
expr_stmt|;
name|procedure
operator|->
name|help
operator|=
name|help
expr_stmt|;
name|procedure
operator|->
name|author
operator|=
name|author
expr_stmt|;
name|procedure
operator|->
name|copyright
operator|=
name|copyright
expr_stmt|;
name|procedure
operator|->
name|date
operator|=
name|date
expr_stmt|;
name|procedure
operator|->
name|deprecated
operator|=
name|deprecated
expr_stmt|;
name|procedure
operator|->
name|static_strings
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_procedure_take_strings (GimpProcedure * procedure,gchar * name,gchar * original_name,gchar * blurb,gchar * help,gchar * author,gchar * copyright,gchar * date,gchar * deprecated)
name|gimp_procedure_take_strings
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|original_name
parameter_list|,
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
name|date
parameter_list|,
name|gchar
modifier|*
name|deprecated
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_free_strings
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|name
operator|=
name|name
expr_stmt|;
name|procedure
operator|->
name|original_name
operator|=
name|original_name
expr_stmt|;
name|procedure
operator|->
name|blurb
operator|=
name|blurb
expr_stmt|;
name|procedure
operator|->
name|help
operator|=
name|help
expr_stmt|;
name|procedure
operator|->
name|author
operator|=
name|author
expr_stmt|;
name|procedure
operator|->
name|copyright
operator|=
name|copyright
expr_stmt|;
name|procedure
operator|->
name|date
operator|=
name|date
expr_stmt|;
name|procedure
operator|->
name|deprecated
operator|=
name|deprecated
expr_stmt|;
name|procedure
operator|->
name|static_strings
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|GValueArray
modifier|*
DECL|function|gimp_procedure_execute (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,GValueArray * args)
name|gimp_procedure_execute
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GValueArray
modifier|*
name|args
parameter_list|)
block|{
name|GValueArray
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|args
operator|!=
name|NULL
argument_list|,
name|NULL
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
name|MIN
argument_list|(
name|args
operator|->
name|n_values
argument_list|,
name|procedure
operator|->
name|num_args
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|GValue
modifier|*
name|arg
init|=
operator|&
name|args
operator|->
name|values
index|[
name|i
index|]
decl_stmt|;
name|GParamSpec
modifier|*
name|pspec
init|=
name|procedure
operator|->
name|args
index|[
name|i
index|]
decl_stmt|;
name|GType
name|arg_type
init|=
name|G_VALUE_TYPE
argument_list|(
name|arg
argument_list|)
decl_stmt|;
name|GType
name|spec_type
init|=
name|G_PARAM_SPEC_VALUE_TYPE
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
if|if
condition|(
name|arg_type
operator|!=
name|spec_type
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|type_name
init|=
name|g_type_name
argument_list|(
name|spec_type
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|got
init|=
name|g_type_name
argument_list|(
name|arg_type
argument_list|)
decl_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"PDB calling error for procedure '%s':\n"
literal|"Argument '%s' (#%d, type %s) type mismatch "
literal|"(got %s)."
argument_list|)
argument_list|,
name|procedure
operator|->
name|name
argument_list|,
name|g_param_spec_get_name
argument_list|(
name|pspec
argument_list|)
argument_list|,
name|i
operator|+
literal|1
argument_list|,
name|type_name
argument_list|,
name|got
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|return_vals
operator|->
name|values
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
elseif|else
if|if
condition|(
operator|!
operator|(
name|pspec
operator|->
name|flags
operator|&
name|GIMP_PARAM_NO_VALIDATE
operator|)
condition|)
block|{
name|GValue
name|string_value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|string_value
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_type_transformable
argument_list|(
name|arg_type
argument_list|,
name|G_TYPE_STRING
argument_list|)
condition|)
name|g_value_transform
argument_list|(
name|arg
argument_list|,
operator|&
name|string_value
argument_list|)
expr_stmt|;
else|else
name|g_value_set_static_string
argument_list|(
operator|&
name|string_value
argument_list|,
literal|"<not transformable to string>"
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_param_value_validate
argument_list|(
name|pspec
argument_list|,
name|arg
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|type_name
init|=
name|g_type_name
argument_list|(
name|spec_type
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|old_value
decl_stmt|;
name|gchar
modifier|*
name|new_value
decl_stmt|;
name|old_value
operator|=
name|g_value_dup_string
argument_list|(
operator|&
name|string_value
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_type_transformable
argument_list|(
name|arg_type
argument_list|,
name|G_TYPE_STRING
argument_list|)
condition|)
name|g_value_transform
argument_list|(
name|arg
argument_list|,
operator|&
name|string_value
argument_list|)
expr_stmt|;
else|else
name|g_value_set_static_string
argument_list|(
operator|&
name|string_value
argument_list|,
literal|"<not transformable to string>"
argument_list|)
expr_stmt|;
name|new_value
operator|=
name|g_value_dup_string
argument_list|(
operator|&
name|string_value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|string_value
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"PDB calling error for procedure '%s':\n"
literal|"Argument '%s' (#%d, type %s) out of bounds "
literal|"(validation changed '%s' to '%s')"
argument_list|)
argument_list|,
name|procedure
operator|->
name|name
argument_list|,
name|g_param_spec_get_name
argument_list|(
name|pspec
argument_list|)
argument_list|,
name|i
operator|+
literal|1
argument_list|,
name|type_name
argument_list|,
name|old_value
argument_list|,
name|new_value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|old_value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|new_value
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|return_vals
operator|->
name|values
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
name|g_value_unset
argument_list|(
operator|&
name|string_value
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  call the procedure  */
switch|switch
condition|(
name|procedure
operator|->
name|proc_type
condition|)
block|{
case|case
name|GIMP_INTERNAL
case|:
name|g_return_val_if_fail
argument_list|(
name|args
operator|->
name|n_values
operator|>=
name|procedure
operator|->
name|num_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|procedure
operator|->
name|exec_method
operator|.
name|internal
operator|.
name|marshal_func
argument_list|(
name|procedure
argument_list|,
name|gimp
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|args
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PLUGIN
case|:
case|case
name|GIMP_EXTENSION
case|:
case|case
name|GIMP_TEMPORARY
case|:
name|return_vals
operator|=
name|plug_in_run
argument_list|(
name|gimp
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|procedure
argument_list|,
name|args
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
comment|/*  If there are no return arguments, assume an execution error  */
if|if
condition|(
operator|!
name|return_vals
condition|)
block|{
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|return_vals
operator|->
name|values
argument_list|,
name|GIMP_PDB_EXECUTION_ERROR
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|GValueArray
modifier|*
DECL|function|gimp_procedure_get_arguments (GimpProcedure * procedure)
name|gimp_procedure_get_arguments
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|GValueArray
modifier|*
name|args
decl_stmt|;
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|args
operator|=
name|g_value_array_new
argument_list|(
name|procedure
operator|->
name|num_args
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
name|procedure
operator|->
name|num_args
condition|;
name|i
operator|++
control|)
block|{
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|G_PARAM_SPEC_VALUE_TYPE
argument_list|(
name|procedure
operator|->
name|args
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_array_append
argument_list|(
name|args
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
return|return
name|args
return|;
block|}
end_function

begin_function
name|GValueArray
modifier|*
DECL|function|gimp_procedure_get_return_values (GimpProcedure * procedure,gboolean success)
name|gimp_procedure_get_return_values
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gboolean
name|success
parameter_list|)
block|{
name|GValueArray
modifier|*
name|args
decl_stmt|;
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gint
name|n_args
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
operator|||
name|success
operator|==
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
condition|)
name|n_args
operator|=
name|procedure
operator|->
name|num_values
operator|+
literal|1
expr_stmt|;
else|else
name|n_args
operator|=
literal|1
expr_stmt|;
name|args
operator|=
name|g_value_array_new
argument_list|(
name|n_args
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|GIMP_TYPE_PDB_STATUS_TYPE
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
operator|&
name|value
argument_list|,
name|success
condition|?
name|GIMP_PDB_SUCCESS
else|:
name|GIMP_PDB_EXECUTION_ERROR
argument_list|)
expr_stmt|;
name|g_value_array_append
argument_list|(
name|args
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
condition|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|procedure
operator|->
name|num_values
condition|;
name|i
operator|++
control|)
block|{
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|G_PARAM_SPEC_VALUE_TYPE
argument_list|(
name|procedure
operator|->
name|values
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_array_append
argument_list|(
name|args
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
return|return
name|args
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_procedure_add_argument (GimpProcedure * procedure,GParamSpec * pspec)
name|gimp_procedure_add_argument
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_PARAM_SPEC
argument_list|(
name|pspec
argument_list|)
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
name|procedure
operator|->
name|num_args
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|procedure
operator|->
name|args
index|[
name|i
index|]
operator|==
name|NULL
condition|)
block|{
name|procedure
operator|->
name|args
index|[
name|i
index|]
operator|=
name|pspec
expr_stmt|;
name|g_param_spec_ref
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
name|g_param_spec_sink
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
return|return;
block|}
name|g_warning
argument_list|(
literal|"%s: can't register more than %d arguments for procedure %s"
argument_list|,
name|G_STRFUNC
argument_list|,
name|procedure
operator|->
name|num_args
argument_list|,
name|procedure
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_procedure_add_return_value (GimpProcedure * procedure,GParamSpec * pspec)
name|gimp_procedure_add_return_value
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_PARAM_SPEC
argument_list|(
name|pspec
argument_list|)
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
name|procedure
operator|->
name|num_values
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|procedure
operator|->
name|values
index|[
name|i
index|]
operator|==
name|NULL
condition|)
block|{
name|procedure
operator|->
name|values
index|[
name|i
index|]
operator|=
name|pspec
expr_stmt|;
name|g_param_spec_ref
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
name|g_param_spec_sink
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
return|return;
block|}
name|g_warning
argument_list|(
literal|"%s: can't register more than %d return values for procedure %s"
argument_list|,
name|G_STRFUNC
argument_list|,
name|procedure
operator|->
name|num_values
argument_list|,
name|procedure
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GParamSpec
modifier|*
DECL|function|gimp_procedure_compat_pspec (Gimp * gimp,GimpPDBArgType arg_type,const gchar * name,const gchar * desc)
name|gimp_procedure_compat_pspec
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPDBArgType
name|arg_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|pspec
init|=
name|NULL
decl_stmt|;
switch|switch
condition|(
name|arg_type
condition|)
block|{
case|case
name|GIMP_PDB_INT32
case|:
name|pspec
operator|=
name|gimp_param_spec_int32
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT16
case|:
name|pspec
operator|=
name|gimp_param_spec_int16
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_MININT16
argument_list|,
name|G_MAXINT16
argument_list|,
literal|0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT8
case|:
name|pspec
operator|=
name|gimp_param_spec_int8
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
literal|0
argument_list|,
name|G_MAXUINT8
argument_list|,
literal|0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_FLOAT
case|:
name|pspec
operator|=
name|g_param_spec_double
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
operator|-
name|G_MAXDOUBLE
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|0.0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STRING
case|:
name|pspec
operator|=
name|gimp_param_spec_string
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT32ARRAY
case|:
name|pspec
operator|=
name|gimp_param_spec_int32_array
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT16ARRAY
case|:
name|pspec
operator|=
name|gimp_param_spec_int16_array
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT8ARRAY
case|:
name|pspec
operator|=
name|gimp_param_spec_int8_array
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_FLOATARRAY
case|:
name|pspec
operator|=
name|gimp_param_spec_float_array
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STRINGARRAY
case|:
name|pspec
operator|=
name|gimp_param_spec_string_array
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_COLOR
case|:
name|pspec
operator|=
name|gimp_param_spec_rgb
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_REGION
case|:
break|break;
case|case
name|GIMP_PDB_DISPLAY
case|:
name|pspec
operator|=
name|gimp_param_spec_display_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_IMAGE
case|:
name|pspec
operator|=
name|gimp_param_spec_image_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_LAYER
case|:
name|pspec
operator|=
name|gimp_param_spec_layer_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_CHANNEL
case|:
name|pspec
operator|=
name|gimp_param_spec_channel_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_DRAWABLE
case|:
name|pspec
operator|=
name|gimp_param_spec_drawable_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_SELECTION
case|:
name|pspec
operator|=
name|gimp_param_spec_selection_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_BOUNDARY
case|:
break|break;
case|case
name|GIMP_PDB_VECTORS
case|:
name|pspec
operator|=
name|gimp_param_spec_vectors_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_PARASITE
case|:
name|pspec
operator|=
name|gimp_param_spec_parasite
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STATUS
case|:
name|pspec
operator|=
name|g_param_spec_enum
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|GIMP_TYPE_PDB_STATUS_TYPE
argument_list|,
name|GIMP_PDB_EXECUTION_ERROR
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_END
case|:
break|break;
block|}
if|if
condition|(
operator|!
name|pspec
condition|)
name|g_warning
argument_list|(
literal|"%s: returning NULL for %s (%s)"
argument_list|,
name|G_STRFUNC
argument_list|,
name|name
argument_list|,
name|gimp_pdb_arg_type_to_string
argument_list|(
name|arg_type
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|pspec
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_procedure_add_compat_arg (GimpProcedure * procedure,Gimp * gimp,GimpPDBArgType arg_type,const gchar * name,const gchar * desc)
name|gimp_procedure_add_compat_arg
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPDBArgType
name|arg_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_procedure_compat_pspec
argument_list|(
name|gimp
argument_list|,
name|arg_type
argument_list|,
name|name
argument_list|,
name|desc
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_procedure_add_compat_value (GimpProcedure * procedure,Gimp * gimp,GimpPDBArgType arg_type,const gchar * name,const gchar * desc)
name|gimp_procedure_add_compat_value
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPDBArgType
name|arg_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_procedure_compat_pspec
argument_list|(
name|gimp
argument_list|,
name|arg_type
argument_list|,
name|name
argument_list|,
name|desc
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_procedure_free_strings (GimpProcedure * procedure)
name|gimp_procedure_free_strings
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
if|if
condition|(
operator|!
name|procedure
operator|->
name|static_strings
condition|)
block|{
name|g_free
argument_list|(
name|procedure
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|procedure
operator|->
name|original_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|procedure
operator|->
name|blurb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|procedure
operator|->
name|help
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|procedure
operator|->
name|author
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|procedure
operator|->
name|copyright
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|procedure
operator|->
name|date
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|procedure
operator|->
name|deprecated
argument_list|)
expr_stmt|;
block|}
name|procedure
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
name|procedure
operator|->
name|original_name
operator|=
name|NULL
expr_stmt|;
name|procedure
operator|->
name|blurb
operator|=
name|NULL
expr_stmt|;
name|procedure
operator|->
name|help
operator|=
name|NULL
expr_stmt|;
name|procedure
operator|->
name|author
operator|=
name|NULL
expr_stmt|;
name|procedure
operator|->
name|copyright
operator|=
name|NULL
expr_stmt|;
name|procedure
operator|->
name|date
operator|=
name|NULL
expr_stmt|;
name|procedure
operator|->
name|deprecated
operator|=
name|NULL
expr_stmt|;
name|procedure
operator|->
name|static_strings
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

