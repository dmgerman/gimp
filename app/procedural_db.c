begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
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
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"plug_in.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/parasite.h"
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_decl_stmt
DECL|variable|procedural_ht
name|GHashTable
modifier|*
name|procedural_ht
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Local functions  */
end_comment

begin_function_decl
specifier|static
name|guint
name|procedural_db_hash_func
parameter_list|(
name|gconstpointer
name|key
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|pdb_id_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|procedural_db_init (void)
name|procedural_db_init
parameter_list|(
name|void
parameter_list|)
block|{
name|app_init_update_status
argument_list|(
name|_
argument_list|(
literal|"Procedural Database"
argument_list|)
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|procedural_ht
condition|)
name|procedural_ht
operator|=
name|g_hash_table_new
argument_list|(
name|procedural_db_hash_func
argument_list|,
name|g_str_equal
argument_list|)
expr_stmt|;
name|pdb_id_init
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|procedural_db_free (void)
name|procedural_db_free
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|procedural_ht
condition|)
name|g_hash_table_destroy
argument_list|(
name|procedural_ht
argument_list|)
expr_stmt|;
name|procedural_ht
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|procedural_db_register (ProcRecord * procedure)
name|procedural_db_register
parameter_list|(
name|ProcRecord
modifier|*
name|procedure
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
operator|!
name|procedural_ht
condition|)
name|procedural_db_init
argument_list|()
expr_stmt|;
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|procedural_ht
argument_list|,
operator|(
name|gpointer
operator|)
name|procedure
operator|->
name|name
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_prepend
argument_list|(
name|list
argument_list|,
operator|(
name|gpointer
operator|)
name|procedure
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|procedural_ht
argument_list|,
operator|(
name|gpointer
operator|)
name|procedure
operator|->
name|name
argument_list|,
operator|(
name|gpointer
operator|)
name|list
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|procedural_db_unregister (gchar * name)
name|procedural_db_unregister
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|procedural_ht
argument_list|,
operator|(
name|gpointer
operator|)
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
block|{
name|list
operator|=
name|g_list_remove
argument_list|(
name|list
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
name|g_hash_table_insert
argument_list|(
name|procedural_ht
argument_list|,
operator|(
name|gpointer
operator|)
name|name
argument_list|,
operator|(
name|gpointer
operator|)
name|list
argument_list|)
expr_stmt|;
else|else
name|g_hash_table_remove
argument_list|(
name|procedural_ht
argument_list|,
operator|(
name|gpointer
operator|)
name|name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|ProcRecord
modifier|*
DECL|function|procedural_db_lookup (gchar * name)
name|procedural_db_lookup
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|ProcRecord
modifier|*
name|procedure
decl_stmt|;
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|procedural_ht
argument_list|,
operator|(
name|gpointer
operator|)
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|!=
name|NULL
condition|)
name|procedure
operator|=
operator|(
name|ProcRecord
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
else|else
name|procedure
operator|=
name|NULL
expr_stmt|;
return|return
name|procedure
return|;
block|}
end_function

begin_function
name|Argument
modifier|*
DECL|function|procedural_db_execute (gchar * name,Argument * args)
name|procedural_db_execute
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|ProcRecord
modifier|*
name|procedure
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|int
name|i
decl_stmt|;
name|return_args
operator|=
name|NULL
expr_stmt|;
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|procedural_ht
argument_list|,
operator|(
name|gpointer
operator|)
name|name
argument_list|)
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
if|if
condition|(
operator|(
name|procedure
operator|=
operator|(
name|ProcRecord
operator|*
operator|)
name|list
operator|->
name|data
operator|)
operator|==
name|NULL
condition|)
block|{
name|return_args
operator|=
operator|(
name|Argument
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|Argument
argument_list|)
argument_list|)
expr_stmt|;
name|return_args
operator|->
name|arg_type
operator|=
name|PDB_STATUS
expr_stmt|;
name|return_args
operator|->
name|value
operator|.
name|pdb_int
operator|=
name|PDB_CALLING_ERROR
expr_stmt|;
return|return
name|return_args
return|;
block|}
name|list
operator|=
name|list
operator|->
name|next
expr_stmt|;
comment|/*  check the arguments  */
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
if|if
condition|(
name|args
index|[
name|i
index|]
operator|.
name|arg_type
operator|!=
name|procedure
operator|->
name|args
index|[
name|i
index|]
operator|.
name|arg_type
condition|)
block|{
name|return_args
operator|=
operator|(
name|Argument
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|Argument
argument_list|)
argument_list|)
expr_stmt|;
name|return_args
operator|->
name|arg_type
operator|=
name|PDB_STATUS
expr_stmt|;
name|return_args
operator|->
name|value
operator|.
name|pdb_int
operator|=
name|PDB_CALLING_ERROR
expr_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"PDB calling error %s"
argument_list|)
argument_list|,
name|procedure
operator|->
name|name
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
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
name|PDB_INTERNAL
case|:
name|return_args
operator|=
call|(
modifier|*
name|procedure
operator|->
name|exec_method
operator|.
name|internal
operator|.
name|marshal_func
call|)
argument_list|(
name|args
argument_list|)
expr_stmt|;
break|break;
case|case
name|PDB_PLUGIN
case|:
name|return_args
operator|=
name|plug_in_run
argument_list|(
name|procedure
argument_list|,
name|args
argument_list|,
name|procedure
operator|->
name|num_args
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
case|case
name|PDB_EXTENSION
case|:
name|return_args
operator|=
name|plug_in_run
argument_list|(
name|procedure
argument_list|,
name|args
argument_list|,
name|procedure
operator|->
name|num_args
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
case|case
name|PDB_TEMPORARY
case|:
name|return_args
operator|=
name|plug_in_run
argument_list|(
name|procedure
argument_list|,
name|args
argument_list|,
name|procedure
operator|->
name|num_args
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
name|return_args
operator|=
operator|(
name|Argument
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|Argument
argument_list|)
argument_list|)
expr_stmt|;
name|return_args
operator|->
name|arg_type
operator|=
name|PDB_STATUS
expr_stmt|;
name|return_args
operator|->
name|value
operator|.
name|pdb_int
operator|=
name|PDB_EXECUTION_ERROR
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|(
name|return_args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|!=
name|PDB_SUCCESS
operator|)
operator|&&
operator|(
name|procedure
operator|->
name|num_values
operator|>
literal|0
operator|)
condition|)
name|memset
argument_list|(
operator|&
name|return_args
index|[
literal|1
index|]
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|Argument
argument_list|)
operator|*
name|procedure
operator|->
name|num_values
argument_list|)
expr_stmt|;
comment|/*  Check if the return value is a PDB_PASS_THROUGH, in which case run the        *  next procedure in the list        */
if|if
condition|(
name|return_args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|!=
name|PDB_PASS_THROUGH
condition|)
break|break;
elseif|else
if|if
condition|(
name|list
condition|)
comment|/*  Pass through, so destroy return values and run another procedure  */
name|procedural_db_destroy_args
argument_list|(
name|return_args
argument_list|,
name|procedure
operator|->
name|num_values
argument_list|)
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_function
name|Argument
modifier|*
DECL|function|procedural_db_run_proc (gchar * name,gint * nreturn_vals,...)
name|procedural_db_run_proc
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
modifier|...
parameter_list|)
block|{
name|ProcRecord
modifier|*
name|proc
decl_stmt|;
name|Argument
modifier|*
name|params
decl_stmt|;
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|int
name|i
decl_stmt|;
if|if
condition|(
operator|(
name|proc
operator|=
name|procedural_db_lookup
argument_list|(
name|name
argument_list|)
operator|)
operator|==
name|NULL
condition|)
block|{
name|return_vals
operator|=
operator|(
name|Argument
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|Argument
argument_list|)
argument_list|)
expr_stmt|;
name|return_vals
operator|->
name|arg_type
operator|=
name|PDB_STATUS
expr_stmt|;
name|return_vals
operator|->
name|value
operator|.
name|pdb_int
operator|=
name|PDB_CALLING_ERROR
expr_stmt|;
return|return
name|return_vals
return|;
block|}
comment|/*  allocate the parameter array  */
name|params
operator|=
name|g_new
argument_list|(
name|Argument
argument_list|,
name|proc
operator|->
name|num_args
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|nreturn_vals
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
name|proc
operator|->
name|num_args
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|proc
operator|->
name|args
index|[
name|i
index|]
operator|.
name|arg_type
operator|!=
operator|(
name|params
index|[
name|i
index|]
operator|.
name|arg_type
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|PDBArgType
argument_list|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Incorrect arguments passed to procedural_db_run_proc:\nArgument %d to '%s' should be a %s, but got passed a %s"
argument_list|)
argument_list|,
name|i
operator|+
literal|1
argument_list|,
name|proc
operator|->
name|name
argument_list|,
name|pdb_type_name
argument_list|(
name|proc
operator|->
name|args
index|[
name|i
index|]
operator|.
name|arg_type
argument_list|)
argument_list|,
name|pdb_type_name
argument_list|(
name|params
index|[
name|i
index|]
operator|.
name|arg_type
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|params
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
switch|switch
condition|(
name|proc
operator|->
name|args
index|[
name|i
index|]
operator|.
name|arg_type
condition|)
block|{
case|case
name|PDB_INT32
case|:
case|case
name|PDB_INT16
case|:
case|case
name|PDB_INT8
case|:
case|case
name|PDB_DISPLAY
case|:
name|params
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
operator|(
name|gint32
operator|)
name|va_arg
argument_list|(
name|args
argument_list|,
name|int
argument_list|)
expr_stmt|;
break|break;
case|case
name|PDB_FLOAT
case|:
name|params
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_float
operator|=
operator|(
name|gdouble
operator|)
name|va_arg
argument_list|(
name|args
argument_list|,
name|double
argument_list|)
expr_stmt|;
break|break;
case|case
name|PDB_STRING
case|:
case|case
name|PDB_INT32ARRAY
case|:
case|case
name|PDB_INT16ARRAY
case|:
case|case
name|PDB_INT8ARRAY
case|:
case|case
name|PDB_FLOATARRAY
case|:
case|case
name|PDB_STRINGARRAY
case|:
case|case
name|PDB_COLOR
case|:
name|params
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|void
operator|*
argument_list|)
expr_stmt|;
break|break;
case|case
name|PDB_REGION
case|:
break|break;
case|case
name|PDB_IMAGE
case|:
case|case
name|PDB_LAYER
case|:
case|case
name|PDB_CHANNEL
case|:
case|case
name|PDB_DRAWABLE
case|:
case|case
name|PDB_SELECTION
case|:
case|case
name|PDB_BOUNDARY
case|:
case|case
name|PDB_PATH
case|:
name|params
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
operator|(
name|gint32
operator|)
name|va_arg
argument_list|(
name|args
argument_list|,
name|int
argument_list|)
expr_stmt|;
break|break;
case|case
name|PDB_PARASITE
case|:
name|params
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|void
operator|*
argument_list|)
expr_stmt|;
break|break;
case|case
name|PDB_STATUS
case|:
name|params
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
operator|(
name|gint32
operator|)
name|va_arg
argument_list|(
name|args
argument_list|,
name|int
argument_list|)
expr_stmt|;
break|break;
case|case
name|PDB_END
case|:
break|break;
block|}
block|}
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
name|proc
operator|->
name|num_values
expr_stmt|;
name|return_vals
operator|=
name|procedural_db_execute
argument_list|(
name|name
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|params
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|Argument
modifier|*
DECL|function|procedural_db_return_args (ProcRecord * procedure,int success)
name|procedural_db_return_args
parameter_list|(
name|ProcRecord
modifier|*
name|procedure
parameter_list|,
name|int
name|success
parameter_list|)
block|{
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|int
name|i
decl_stmt|;
name|return_args
operator|=
operator|(
name|Argument
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|Argument
argument_list|)
operator|*
operator|(
name|procedure
operator|->
name|num_values
operator|+
literal|1
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|return_args
index|[
literal|0
index|]
operator|.
name|arg_type
operator|=
name|PDB_STATUS
expr_stmt|;
name|return_args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|PDB_SUCCESS
expr_stmt|;
block|}
else|else
block|{
name|return_args
index|[
literal|0
index|]
operator|.
name|arg_type
operator|=
name|PDB_STATUS
expr_stmt|;
name|return_args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|PDB_EXECUTION_ERROR
expr_stmt|;
block|}
comment|/*  Set the arg types for the return values  */
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
name|return_args
index|[
name|i
operator|+
literal|1
index|]
operator|.
name|arg_type
operator|=
name|procedure
operator|->
name|values
index|[
name|i
index|]
operator|.
name|arg_type
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_function
name|void
DECL|function|procedural_db_destroy_args (Argument * args,int nargs)
name|procedural_db_destroy_args
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|,
name|int
name|nargs
parameter_list|)
block|{
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
name|int
name|prev_val
init|=
literal|0
decl_stmt|;
name|char
modifier|*
modifier|*
name|strs
decl_stmt|;
if|if
condition|(
operator|!
name|args
condition|)
return|return;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|nargs
condition|;
name|i
operator|++
control|)
block|{
switch|switch
condition|(
name|args
index|[
name|i
index|]
operator|.
name|arg_type
condition|)
block|{
case|case
name|PDB_INT32
case|:
comment|/*  Keep this around in case we need to free an array of strings  */
name|prev_val
operator|=
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
break|break;
case|case
name|PDB_INT16
case|:
case|case
name|PDB_INT8
case|:
case|case
name|PDB_FLOAT
case|:
break|break;
case|case
name|PDB_STRING
case|:
case|case
name|PDB_INT32ARRAY
case|:
case|case
name|PDB_INT16ARRAY
case|:
case|case
name|PDB_INT8ARRAY
case|:
case|case
name|PDB_FLOATARRAY
case|:
name|g_free
argument_list|(
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
argument_list|)
expr_stmt|;
break|break;
case|case
name|PDB_STRINGARRAY
case|:
name|strs
operator|=
operator|(
name|char
operator|*
operator|*
operator|)
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|prev_val
condition|;
name|j
operator|++
control|)
name|g_free
argument_list|(
name|strs
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|strs
argument_list|)
expr_stmt|;
break|break;
case|case
name|PDB_COLOR
case|:
name|g_free
argument_list|(
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
argument_list|)
expr_stmt|;
break|break;
case|case
name|PDB_REGION
case|:
case|case
name|PDB_DISPLAY
case|:
case|case
name|PDB_IMAGE
case|:
case|case
name|PDB_LAYER
case|:
case|case
name|PDB_CHANNEL
case|:
case|case
name|PDB_DRAWABLE
case|:
case|case
name|PDB_SELECTION
case|:
case|case
name|PDB_BOUNDARY
case|:
case|case
name|PDB_PATH
case|:
case|case
name|PDB_PARASITE
case|:
case|case
name|PDB_STATUS
case|:
case|case
name|PDB_END
case|:
break|break;
block|}
block|}
name|g_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* We could just use g_str_hash() here ... that uses a different  * hash function, though  */
end_comment

begin_function
specifier|static
name|guint
DECL|function|procedural_db_hash_func (gconstpointer key)
name|procedural_db_hash_func
parameter_list|(
name|gconstpointer
name|key
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|string
decl_stmt|;
name|guint
name|result
decl_stmt|;
name|int
name|c
decl_stmt|;
comment|/*    * I tried a zillion different hash functions and asked many other    * people for advice.  Many people had their own favorite functions,    * all different, but no-one had much idea why they were good ones.    * I chose the one below (multiply by 9 and add new character)    * because of the following reasons:    *    * 1. Multiplying by 10 is perfect for keys that are decimal strings,    *    and multiplying by 9 is just about as good.    * 2. Times-9 is (shift-left-3) plus (old).  This means that each    *    character's bits hang around in the low-order bits of the    *    hash value for ever, plus they spread fairly rapidly up to    *    the high-order bits to fill out the hash value.  This seems    *    works well both for decimal and non-decimal strings.    *    * tclHash.c --    *    *      Implementation of in-memory hash tables for Tcl and Tcl-based    *      applications.    *    * Copyright (c) 1991-1993 The Regents of the University of California.    * Copyright (c) 1994 Sun Microsystems, Inc.    */
name|string
operator|=
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|key
expr_stmt|;
name|result
operator|=
literal|0
expr_stmt|;
while|while
condition|(
literal|1
condition|)
block|{
name|c
operator|=
operator|*
name|string
expr_stmt|;
name|string
operator|++
expr_stmt|;
if|if
condition|(
name|c
operator|==
literal|0
condition|)
break|break;
name|result
operator|+=
operator|(
name|result
operator|<<
literal|3
operator|)
operator|+
name|c
expr_stmt|;
block|}
return|return
name|result
return|;
block|}
end_function

begin_comment
comment|/* The id system's remnants ... */
end_comment

begin_decl_stmt
DECL|variable|next_image_id
specifier|static
name|gint
name|next_image_id
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* static gint next_drawable_id; static gint next_display_id; */
end_comment

begin_decl_stmt
DECL|variable|image_hash
specifier|static
name|GHashTable
modifier|*
name|image_hash
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_hash
specifier|static
name|GHashTable
modifier|*
name|drawable_hash
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|display_hash
specifier|static
name|GHashTable
modifier|*
name|display_hash
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|guint
DECL|function|id_hash_func (gconstpointer id)
name|id_hash_func
parameter_list|(
name|gconstpointer
name|id
parameter_list|)
block|{
return|return
operator|*
operator|(
operator|(
name|guint
operator|*
operator|)
name|id
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|id_cmp_func (gconstpointer id1,gconstpointer id2)
name|id_cmp_func
parameter_list|(
name|gconstpointer
name|id1
parameter_list|,
name|gconstpointer
name|id2
parameter_list|)
block|{
return|return
operator|(
operator|*
operator|(
operator|(
name|guint
operator|*
operator|)
name|id1
operator|)
operator|==
operator|*
operator|(
operator|(
name|guint
operator|*
operator|)
name|id2
operator|)
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|add_cb (GimpSet * set,GimpImage * gimage,gpointer data)
name|add_cb
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|guint
modifier|*
name|id
init|=
name|g_new
argument_list|(
name|guint
argument_list|,
literal|1
argument_list|)
decl_stmt|;
operator|*
name|id
operator|=
name|next_image_id
operator|++
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"pdb_id"
argument_list|,
name|id
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|image_hash
argument_list|,
name|id
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|remove_cb (GimpSet * set,GimpImage * image,gpointer data)
name|remove_cb
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|guint
modifier|*
name|id
init|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
literal|"pdb_id"
argument_list|)
decl_stmt|;
name|gtk_object_remove_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
literal|"pdb_id"
argument_list|)
expr_stmt|;
name|g_hash_table_remove
argument_list|(
name|image_hash
argument_list|,
name|id
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pdb_id_init (void)
name|pdb_id_init
parameter_list|(
name|void
parameter_list|)
block|{
name|image_hash
operator|=
name|g_hash_table_new
argument_list|(
name|id_hash_func
argument_list|,
name|id_cmp_func
argument_list|)
expr_stmt|;
name|drawable_hash
operator|=
name|g_hash_table_new
argument_list|(
name|id_hash_func
argument_list|,
name|id_cmp_func
argument_list|)
expr_stmt|;
name|display_hash
operator|=
name|g_hash_table_new
argument_list|(
name|id_hash_func
argument_list|,
name|id_cmp_func
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|image_context
argument_list|)
argument_list|,
literal|"add"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|add_cb
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|image_context
argument_list|)
argument_list|,
literal|"remove"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|remove_cb
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|pdb_image_to_id (GimpImage * gimage)
name|pdb_image_to_id
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|guint
modifier|*
name|id
init|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"pdb_id"
argument_list|)
decl_stmt|;
return|return
name|id
condition|?
operator|(
name|gint
operator|)
operator|*
name|id
else|:
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|pdb_id_to_image (gint id)
name|pdb_id_to_image
parameter_list|(
name|gint
name|id
parameter_list|)
block|{
return|return
name|g_hash_table_lookup
argument_list|(
name|image_hash
argument_list|,
operator|&
name|id
argument_list|)
return|;
block|}
end_function

end_unit

