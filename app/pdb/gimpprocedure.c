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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
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
file|"plug-in/plug-in-run.h"
end_include

begin_include
include|#
directive|include
file|"internal_procs.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|PDBData
typedef|typedef
name|struct
name|_PDBData
name|PDBData
typedef|;
end_typedef

begin_struct
DECL|struct|_PDBData
struct|struct
name|_PDBData
block|{
DECL|member|identifier
name|gchar
modifier|*
name|identifier
decl_stmt|;
DECL|member|bytes
name|gint32
name|bytes
decl_stmt|;
DECL|member|data
name|guint8
modifier|*
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_function
name|void
DECL|function|procedural_db_init (Gimp * gimp)
name|procedural_db_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|procedural_ht
operator|=
name|g_hash_table_new
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|procedural_compat_ht
operator|=
name|g_hash_table_new
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|procedural_db_data_list
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|procedural_db_free_entry (gpointer key,gpointer value,gpointer user_data)
name|procedural_db_free_entry
parameter_list|(
name|gpointer
name|key
parameter_list|,
name|gpointer
name|value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
if|if
condition|(
name|value
condition|)
name|g_list_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|procedural_db_free (Gimp * gimp)
name|procedural_db_free
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|procedural_ht
condition|)
block|{
name|g_hash_table_foreach
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
name|procedural_db_free_entry
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_hash_table_destroy
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|procedural_ht
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|gimp
operator|->
name|procedural_compat_ht
condition|)
block|{
name|g_hash_table_destroy
argument_list|(
name|gimp
operator|->
name|procedural_compat_ht
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|procedural_compat_ht
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|gimp
operator|->
name|procedural_db_data_list
condition|)
block|{
name|PDBData
modifier|*
name|data
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp
operator|->
name|procedural_db_data_list
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
name|data
operator|=
operator|(
name|PDBData
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|identifier
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|gimp
operator|->
name|procedural_db_data_list
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|procedural_db_data_list
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|procedural_db_init_procs (Gimp * gimp,GimpInitStatusFunc status_callback)
name|procedural_db_init_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|)
block|{
specifier|static
specifier|const
struct|struct
DECL|struct|__anon27ddb7230108
block|{
DECL|member|old_name
specifier|const
name|gchar
modifier|*
name|old_name
decl_stmt|;
DECL|member|new_name
specifier|const
name|gchar
modifier|*
name|new_name
decl_stmt|;
block|}
name|compat_procs
index|[]
init|=
block|{
block|{
literal|"gimp_brushes_list"
block|,
literal|"gimp_brushes_get_list"
block|}
block|,
block|{
literal|"gimp_channel_delete"
block|,
literal|"gimp_drawable_delete"
block|}
block|,
block|{
literal|"gimp_channel_get_name"
block|,
literal|"gimp_drawable_get_name"
block|}
block|,
block|{
literal|"gimp_channel_get_tattoo"
block|,
literal|"gimp_drawable_get_tattoo"
block|}
block|,
block|{
literal|"gimp_channel_get_visible"
block|,
literal|"gimp_drawable_get_visible"
block|}
block|,
block|{
literal|"gimp_channel_set_name"
block|,
literal|"gimp_drawable_set_name"
block|}
block|,
block|{
literal|"gimp_channel_set_tattoo"
block|,
literal|"gimp_drawable_set_tattoo"
block|}
block|,
block|{
literal|"gimp_channel_set_visible"
block|,
literal|"gimp_drawable_set_visible"
block|}
block|,
block|{
literal|"gimp_convert_grayscale"
block|,
literal|"gimp_image_convert_grayscale"
block|}
block|,
block|{
literal|"gimp_convert_indexed"
block|,
literal|"gimp_image_convert_indexed"
block|}
block|,
block|{
literal|"gimp_convert_rgb"
block|,
literal|"gimp_image_convert_rgb"
block|}
block|,
block|{
literal|"gimp_crop"
block|,
literal|"gimp_image_crop"
block|}
block|,
block|{
literal|"gimp_drawable_image"
block|,
literal|"gimp_drawable_get_image"
block|}
block|,
block|{
literal|"gimp_gradients_get_active"
block|,
literal|"gimp_gradients_get_gradient"
block|}
block|,
block|{
literal|"gimp_gradients_set_active"
block|,
literal|"gimp_gradients_set_gradient"
block|}
block|,
block|{
literal|"gimp_layer_delete"
block|,
literal|"gimp_drawable_delete"
block|}
block|,
block|{
literal|"gimp_layer_get_linked"
block|,
literal|"gimp_drawable_get_linked"
block|}
block|,
block|{
literal|"gimp_layer_get_name"
block|,
literal|"gimp_drawable_get_name"
block|}
block|,
block|{
literal|"gimp_layer_get_tattoo"
block|,
literal|"gimp_drawable_get_tattoo"
block|}
block|,
block|{
literal|"gimp_layer_get_visible"
block|,
literal|"gimp_drawable_get_visible"
block|}
block|,
block|{
literal|"gimp_layer_mask"
block|,
literal|"gimp_layer_get_mask"
block|}
block|,
block|{
literal|"gimp_layer_set_linked"
block|,
literal|"gimp_drawable_set_linked"
block|}
block|,
block|{
literal|"gimp_layer_set_name"
block|,
literal|"gimp_drawable_set_name"
block|}
block|,
block|{
literal|"gimp_layer_set_tattoo"
block|,
literal|"gimp_drawable_set_tattoo"
block|}
block|,
block|{
literal|"gimp_layer_set_visible"
block|,
literal|"gimp_drawable_set_visible"
block|}
block|,
block|{
literal|"gimp_palette_refresh"
block|,
literal|"gimp_palettes_refresh"
block|}
block|,
block|{
literal|"gimp_patterns_list"
block|,
literal|"gimp_patterns_get_list"
block|}
block|}
struct|;
name|gint
name|i
decl_stmt|;
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
name|status_callback
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|internal_procs_init
argument_list|(
name|gimp
argument_list|,
name|status_callback
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
name|G_N_ELEMENTS
argument_list|(
name|compat_procs
argument_list|)
condition|;
name|i
operator|++
control|)
name|g_hash_table_insert
argument_list|(
name|gimp
operator|->
name|procedural_compat_ht
argument_list|,
operator|(
name|gpointer
operator|)
name|compat_procs
index|[
name|i
index|]
operator|.
name|old_name
argument_list|,
operator|(
name|gpointer
operator|)
name|compat_procs
index|[
name|i
index|]
operator|.
name|new_name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|procedural_db_register (Gimp * gimp,ProcRecord * procedure)
name|procedural_db_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|ProcRecord
modifier|*
name|procedure
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
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
name|procedure
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
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
name|gimp
operator|->
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
DECL|function|procedural_db_unregister (Gimp * gimp,const gchar * name)
name|procedural_db_unregister
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
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
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
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
name|gimp
operator|->
name|procedural_ht
argument_list|,
operator|(
name|gpointer
operator|)
name|name
argument_list|,
name|list
argument_list|)
expr_stmt|;
else|else
name|g_hash_table_remove
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|ProcRecord
modifier|*
DECL|function|procedural_db_lookup (Gimp * gimp,const gchar * name)
name|procedural_db_lookup
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GList
modifier|*
name|list
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
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
return|return
operator|(
name|ProcRecord
operator|*
operator|)
name|list
operator|->
name|data
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|Argument
modifier|*
DECL|function|procedural_db_execute (Gimp * gimp,const gchar * name,Argument * args)
name|procedural_db_execute
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Argument
modifier|*
name|return_args
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
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
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|==
name|NULL
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"PDB calling error:\nprocedure '%s' not found"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|g_new
argument_list|(
name|Argument
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|return_args
operator|->
name|arg_type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|return_args
operator|->
name|value
operator|.
name|pdb_int
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
return|return
name|return_args
return|;
block|}
for|for
control|(
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
name|ProcRecord
modifier|*
name|procedure
decl_stmt|;
name|gint
name|i
decl_stmt|;
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
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|: FIXME: this is impossible, right?  --mitch
endif|#
directive|endif
if|#
directive|if
literal|0
block|if (procedure == NULL) 	{ 	  g_warning ("PDB calling error %s not found", name);  	  return_args = g_new (Argument, 1); 	  return_args->arg_type      = GIMP_PDB_STATUS; 	  return_args->value.pdb_int = GIMP_PDB_CALLING_ERROR;  	  return return_args; 	}
endif|#
directive|endif
name|g_return_val_if_fail
argument_list|(
name|procedure
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
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
name|g_message
argument_list|(
name|_
argument_list|(
literal|"PDB calling error for procedure '%s':\n"
literal|"Argument #%d type mismatch (expected %s, got %s)"
argument_list|)
argument_list|,
name|procedure
operator|->
name|name
argument_list|,
name|i
operator|+
literal|1
argument_list|,
name|pdb_type_name
argument_list|(
name|procedure
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
name|args
index|[
name|i
index|]
operator|.
name|arg_type
argument_list|)
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|g_new
argument_list|(
name|Argument
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|return_args
operator|->
name|arg_type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|return_args
operator|->
name|value
operator|.
name|pdb_int
operator|=
name|GIMP_PDB_CALLING_ERROR
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
name|GIMP_INTERNAL
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
name|gimp
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
name|return_args
operator|=
name|plug_in_run
argument_list|(
name|gimp
argument_list|,
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
name|g_new
argument_list|(
name|Argument
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|return_args
operator|->
name|arg_type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|return_args
operator|->
name|value
operator|.
name|pdb_int
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
return|return
name|return_args
return|;
block|}
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
name|GIMP_PDB_SUCCESS
operator|&&
name|return_args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|!=
name|GIMP_PDB_PASS_THROUGH
operator|&&
name|procedure
operator|->
name|num_values
operator|>
literal|0
condition|)
block|{
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
block|}
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
operator|==
name|GIMP_PDB_PASS_THROUGH
condition|)
block|{
comment|/*  If the return value is GIMP_PDB_PASS_THROUGH and there is            *  a next procedure in the list, destroy the return values            *  and run the next procedure.            */
if|if
condition|(
name|g_list_next
argument_list|(
name|list
argument_list|)
condition|)
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
else|else
block|{
comment|/*  No GIMP_PDB_PASS_THROUGH, break out of the list of            *  procedures and return the current return values.            */
break|break;
block|}
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_function
name|Argument
modifier|*
DECL|function|procedural_db_run_proc (Gimp * gimp,const gchar * name,gint * nreturn_vals,...)
name|procedural_db_run_proc
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
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
name|gint
name|i
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
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|nreturn_vals
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|proc
operator|=
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|name
argument_list|)
operator|)
operator|==
name|NULL
condition|)
block|{
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
name|return_vals
operator|=
name|g_new
argument_list|(
name|Argument
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|return_vals
operator|->
name|arg_type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|return_vals
operator|->
name|value
operator|.
name|pdb_int
operator|=
name|GIMP_PDB_CALLING_ERROR
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
name|GimpPDBArgType
argument_list|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"PDB calling error for procedure '%s':\n"
literal|"Argument #%d type mismatch (expected %s, got %s)"
argument_list|)
argument_list|,
name|proc
operator|->
name|name
argument_list|,
name|i
operator|+
literal|1
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
operator|*
name|nreturn_vals
operator|=
literal|0
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
name|GIMP_PDB_INT32
case|:
case|case
name|GIMP_PDB_INT16
case|:
case|case
name|GIMP_PDB_INT8
case|:
case|case
name|GIMP_PDB_DISPLAY
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
name|gint
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_FLOAT
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
name|gdouble
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STRING
case|:
case|case
name|GIMP_PDB_INT32ARRAY
case|:
case|case
name|GIMP_PDB_INT16ARRAY
case|:
case|case
name|GIMP_PDB_INT8ARRAY
case|:
case|case
name|GIMP_PDB_FLOATARRAY
case|:
case|case
name|GIMP_PDB_STRINGARRAY
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
name|gpointer
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_COLOR
case|:
name|params
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_color
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|GimpRGB
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_REGION
case|:
break|break;
case|case
name|GIMP_PDB_IMAGE
case|:
case|case
name|GIMP_PDB_LAYER
case|:
case|case
name|GIMP_PDB_CHANNEL
case|:
case|case
name|GIMP_PDB_DRAWABLE
case|:
case|case
name|GIMP_PDB_SELECTION
case|:
case|case
name|GIMP_PDB_BOUNDARY
case|:
case|case
name|GIMP_PDB_PATH
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
name|gint
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_PARASITE
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
name|gpointer
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STATUS
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
name|gint
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_END
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
name|gimp
argument_list|,
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
DECL|function|procedural_db_return_args (ProcRecord * procedure,gboolean success)
name|procedural_db_return_args
parameter_list|(
name|ProcRecord
modifier|*
name|procedure
parameter_list|,
name|gboolean
name|success
parameter_list|)
block|{
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|procedure
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|g_new0
argument_list|(
name|Argument
argument_list|,
name|procedure
operator|->
name|num_values
operator|+
literal|1
argument_list|)
expr_stmt|;
name|return_args
index|[
literal|0
index|]
operator|.
name|arg_type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|return_args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
else|else
name|return_args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
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
DECL|function|procedural_db_destroy_args (Argument * args,gint nargs)
name|procedural_db_destroy_args
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|,
name|gint
name|nargs
parameter_list|)
block|{
name|gint
name|i
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
name|GIMP_PDB_INT32
case|:
case|case
name|GIMP_PDB_INT16
case|:
case|case
name|GIMP_PDB_INT8
case|:
case|case
name|GIMP_PDB_FLOAT
case|:
break|break;
case|case
name|GIMP_PDB_STRING
case|:
case|case
name|GIMP_PDB_INT32ARRAY
case|:
case|case
name|GIMP_PDB_INT16ARRAY
case|:
case|case
name|GIMP_PDB_INT8ARRAY
case|:
case|case
name|GIMP_PDB_FLOATARRAY
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
name|GIMP_PDB_STRINGARRAY
case|:
block|{
name|gchar
modifier|*
modifier|*
name|stringarray
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|gint
name|j
decl_stmt|;
name|count
operator|=
name|args
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|stringarray
operator|=
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
name|count
condition|;
name|j
operator|++
control|)
name|g_free
argument_list|(
name|stringarray
index|[
name|j
index|]
argument_list|)
expr_stmt|;
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
block|}
break|break;
case|case
name|GIMP_PDB_COLOR
case|:
case|case
name|GIMP_PDB_REGION
case|:
case|case
name|GIMP_PDB_DISPLAY
case|:
case|case
name|GIMP_PDB_IMAGE
case|:
case|case
name|GIMP_PDB_LAYER
case|:
case|case
name|GIMP_PDB_CHANNEL
case|:
case|case
name|GIMP_PDB_DRAWABLE
case|:
case|case
name|GIMP_PDB_SELECTION
case|:
case|case
name|GIMP_PDB_BOUNDARY
case|:
case|case
name|GIMP_PDB_PATH
case|:
break|break;
case|case
name|GIMP_PDB_PARASITE
case|:
name|gimp_parasite_free
argument_list|(
operator|(
name|GimpParasite
operator|*
operator|)
operator|(
name|args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STATUS
case|:
case|case
name|GIMP_PDB_END
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

begin_function
name|void
DECL|function|procedural_db_set_data (Gimp * gimp,const gchar * identifier,gint32 bytes,const guint8 * data)
name|procedural_db_set_data
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gint32
name|bytes
parameter_list|,
specifier|const
name|guint8
modifier|*
name|data
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|PDBData
modifier|*
name|pdb_data
decl_stmt|;
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
name|identifier
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|bytes
operator|>
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|data
operator|!=
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp
operator|->
name|procedural_db_data_list
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
name|pdb_data
operator|=
operator|(
name|PDBData
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pdb_data
operator|->
name|identifier
argument_list|,
name|identifier
argument_list|)
condition|)
break|break;
block|}
comment|/* If there isn't already data with the specified identifier, create one */
if|if
condition|(
name|list
operator|==
name|NULL
condition|)
block|{
name|pdb_data
operator|=
name|g_new0
argument_list|(
name|PDBData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pdb_data
operator|->
name|identifier
operator|=
name|g_strdup
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|procedural_db_data_list
operator|=
name|g_list_prepend
argument_list|(
name|gimp
operator|->
name|procedural_db_data_list
argument_list|,
name|pdb_data
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
name|pdb_data
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|pdb_data
operator|->
name|bytes
operator|=
name|bytes
expr_stmt|;
name|pdb_data
operator|->
name|data
operator|=
name|g_memdup
argument_list|(
name|data
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|guint8
modifier|*
DECL|function|procedural_db_get_data (Gimp * gimp,const gchar * identifier,gint32 * bytes)
name|procedural_db_get_data
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gint32
modifier|*
name|bytes
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|PDBData
modifier|*
name|pdb_data
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
name|identifier
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|bytes
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|bytes
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp
operator|->
name|procedural_db_data_list
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
name|pdb_data
operator|=
operator|(
name|PDBData
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pdb_data
operator|->
name|identifier
argument_list|,
name|identifier
argument_list|)
condition|)
block|{
operator|*
name|bytes
operator|=
name|pdb_data
operator|->
name|bytes
expr_stmt|;
return|return
name|pdb_data
operator|->
name|data
return|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

