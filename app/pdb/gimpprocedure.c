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
file|"core/gimp-utils.h"
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
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_procedure_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_procedure_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GValueArray
modifier|*
name|gimp_procedure_real_execute
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_procedure_real_execute_async
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
parameter_list|,
name|gint32
name|display_ID
parameter_list|)
function_decl|;
end_function_decl

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

begin_function_decl
specifier|static
name|gboolean
name|gimp_procedure_validate_args
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GValueArray
modifier|*
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpProcedure
argument_list|,
name|gimp_procedure
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_procedure_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_procedure_class_init (GimpProcedureClass * klass)
name|gimp_procedure_class_init
parameter_list|(
name|GimpProcedureClass
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
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_procedure_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_procedure_get_memsize
expr_stmt|;
name|klass
operator|->
name|execute
operator|=
name|gimp_procedure_real_execute
expr_stmt|;
name|klass
operator|->
name|execute_async
operator|=
name|gimp_procedure_real_execute_async
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_procedure_init (GimpProcedure * procedure)
name|gimp_procedure_init
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|procedure
operator|->
name|proc_type
operator|=
name|GIMP_INTERNAL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_procedure_finalize (GObject * object)
name|gimp_procedure_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|GIMP_PROCEDURE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
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
name|gint64
DECL|function|gimp_procedure_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_procedure_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|GIMP_PROCEDURE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
operator|!
name|procedure
operator|->
name|static_strings
condition|)
block|{
if|if
condition|(
name|procedure
operator|->
name|original_name
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|procedure
operator|->
name|original_name
argument_list|)
operator|+
literal|1
expr_stmt|;
if|if
condition|(
name|procedure
operator|->
name|blurb
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|procedure
operator|->
name|blurb
argument_list|)
operator|+
literal|1
expr_stmt|;
if|if
condition|(
name|procedure
operator|->
name|help
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|procedure
operator|->
name|help
argument_list|)
operator|+
literal|1
expr_stmt|;
if|if
condition|(
name|procedure
operator|->
name|author
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|procedure
operator|->
name|author
argument_list|)
operator|+
literal|1
expr_stmt|;
if|if
condition|(
name|procedure
operator|->
name|copyright
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|procedure
operator|->
name|copyright
argument_list|)
operator|+
literal|1
expr_stmt|;
if|if
condition|(
name|procedure
operator|->
name|date
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|procedure
operator|->
name|date
argument_list|)
operator|+
literal|1
expr_stmt|;
if|if
condition|(
name|procedure
operator|->
name|deprecated
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|procedure
operator|->
name|deprecated
argument_list|)
operator|+
literal|1
expr_stmt|;
block|}
name|memsize
operator|+=
name|procedure
operator|->
name|num_args
operator|*
sizeof|sizeof
argument_list|(
name|GParamSpec
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
name|procedure
operator|->
name|num_args
condition|;
name|i
operator|++
control|)
name|memsize
operator|+=
name|gimp_g_param_spec_get_memsize
argument_list|(
name|procedure
operator|->
name|args
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|procedure
operator|->
name|num_values
operator|*
sizeof|sizeof
argument_list|(
name|GParamSpec
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
name|procedure
operator|->
name|num_values
condition|;
name|i
operator|++
control|)
name|memsize
operator|+=
name|gimp_g_param_spec_get_memsize
argument_list|(
name|procedure
operator|->
name|values
index|[
name|i
index|]
argument_list|)
expr_stmt|;
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|gimp_procedure_real_execute (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,GValueArray * args)
name|gimp_procedure_real_execute
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
return|return
name|procedure
operator|->
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
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_procedure_real_execute_async (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,GValueArray * args,gint32 display_ID)
name|gimp_procedure_real_execute_async
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
parameter_list|,
name|gint32
name|display_ID
parameter_list|)
block|{
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|args
operator|->
name|n_values
operator|>=
name|procedure
operator|->
name|num_args
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|GIMP_PROCEDURE_GET_CLASS
argument_list|(
name|procedure
argument_list|)
operator|->
name|execute
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
name|g_value_array_free
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpProcedure
modifier|*
DECL|function|gimp_procedure_new (GimpMarshalFunc marshal_func)
name|gimp_procedure_new
parameter_list|(
name|GimpMarshalFunc
name|marshal_func
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|marshal_func
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PROCEDURE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|marshal_func
operator|=
name|marshal_func
expr_stmt|;
return|return
name|procedure
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_procedure_set_strings (GimpProcedure * procedure,gchar * original_name,gchar * blurb,gchar * help,gchar * author,gchar * copyright,gchar * date,gchar * deprecated)
name|gimp_procedure_set_strings
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
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
DECL|function|gimp_procedure_set_static_strings (GimpProcedure * procedure,gchar * original_name,gchar * blurb,gchar * help,gchar * author,gchar * copyright,gchar * date,gchar * deprecated)
name|gimp_procedure_set_static_strings
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
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
DECL|function|gimp_procedure_take_strings (GimpProcedure * procedure,gchar * original_name,gchar * blurb,gchar * help,gchar * author,gchar * copyright,gchar * date,gchar * deprecated)
name|gimp_procedure_take_strings
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
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
if|if
condition|(
operator|!
name|gimp_procedure_validate_args
argument_list|(
name|procedure
argument_list|,
name|args
argument_list|)
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
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
comment|/*  call the procedure  */
name|return_vals
operator|=
name|GIMP_PROCEDURE_GET_CLASS
argument_list|(
name|procedure
argument_list|)
operator|->
name|execute
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
name|void
DECL|function|gimp_procedure_execute_async (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,GValueArray * args,gint32 display_ID)
name|gimp_procedure_execute_async
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
parameter_list|,
name|gint32
name|display_ID
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|args
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_procedure_validate_args
argument_list|(
name|procedure
argument_list|,
name|args
argument_list|)
condition|)
name|GIMP_PROCEDURE_GET_CLASS
argument_list|(
name|procedure
argument_list|)
operator|->
name|execute_async
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
argument_list|,
name|display_ID
argument_list|)
expr_stmt|;
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
name|procedure
operator|->
name|args
operator|=
name|g_renew
argument_list|(
name|GParamSpec
operator|*
argument_list|,
name|procedure
operator|->
name|args
argument_list|,
name|procedure
operator|->
name|num_args
operator|+
literal|1
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|args
index|[
name|procedure
operator|->
name|num_args
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
name|procedure
operator|->
name|num_args
operator|++
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
name|procedure
operator|->
name|values
operator|=
name|g_renew
argument_list|(
name|GParamSpec
operator|*
argument_list|,
name|procedure
operator|->
name|values
argument_list|,
name|procedure
operator|->
name|num_values
operator|+
literal|1
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|values
index|[
name|procedure
operator|->
name|num_values
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
name|procedure
operator|->
name|num_values
operator|++
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

begin_function
specifier|static
name|gboolean
DECL|function|gimp_procedure_validate_args (GimpProcedure * procedure,GValueArray * args)
name|gimp_procedure_validate_args
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GValueArray
modifier|*
name|args
parameter_list|)
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
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|)
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
return|return
name|FALSE
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
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|)
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
return|return
name|FALSE
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
return|return
name|TRUE
return|;
block|}
end_function

end_unit

