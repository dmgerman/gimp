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
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimptemporaryprocedure.h"
end_include

begin_comment
comment|/* eek */
end_comment

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_pdb_eek (void)
name|gimp_pdb_eek
parameter_list|(
name|void
parameter_list|)
block|{
specifier|volatile
name|GType
name|eek
decl_stmt|;
name|eek
operator|=
name|gimp_temporary_procedure_get_type
argument_list|()
expr_stmt|;
block|}
end_function

begin_enum
enum|enum
DECL|enum|__anon27e79f800103
block|{
DECL|enumerator|REGISTER_PROCEDURE
name|REGISTER_PROCEDURE
block|,
DECL|enumerator|UNREGISTER_PROCEDURE
name|UNREGISTER_PROCEDURE
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_pdb_finalize
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
name|gimp_pdb_get_memsize
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
name|void
name|gimp_pdb_real_register_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_real_unregister_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_entry_free
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_entry_memsize
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
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPDB
argument_list|,
argument|gimp_pdb
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_pdb_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|gimp_pdb_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_class_init (GimpPDBClass * klass)
name|gimp_pdb_class_init
parameter_list|(
name|GimpPDBClass
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
name|gimp_pdb_signals
index|[
name|REGISTER_PROCEDURE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"register-procedure"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpPDBClass
argument_list|,
name|register_procedure
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__OBJECT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_PROCEDURE
argument_list|)
expr_stmt|;
name|gimp_pdb_signals
index|[
name|UNREGISTER_PROCEDURE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"unregister-procedure"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpPDBClass
argument_list|,
name|unregister_procedure
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__OBJECT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_PROCEDURE
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_pdb_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_pdb_get_memsize
expr_stmt|;
name|klass
operator|->
name|register_procedure
operator|=
name|gimp_pdb_real_register_procedure
expr_stmt|;
name|klass
operator|->
name|unregister_procedure
operator|=
name|gimp_pdb_real_unregister_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_init (GimpPDB * pdb)
name|gimp_pdb_init
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
block|{
name|pdb
operator|->
name|procedures
operator|=
name|g_hash_table_new
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|)
expr_stmt|;
name|pdb
operator|->
name|compat_proc_names
operator|=
name|g_hash_table_new
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_finalize (GObject * object)
name|gimp_pdb_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPDB
modifier|*
name|pdb
init|=
name|GIMP_PDB
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|pdb
operator|->
name|procedures
condition|)
block|{
name|g_hash_table_foreach
argument_list|(
name|pdb
operator|->
name|procedures
argument_list|,
name|gimp_pdb_entry_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_hash_table_destroy
argument_list|(
name|pdb
operator|->
name|procedures
argument_list|)
expr_stmt|;
name|pdb
operator|->
name|procedures
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|pdb
operator|->
name|compat_proc_names
condition|)
block|{
name|g_hash_table_destroy
argument_list|(
name|pdb
operator|->
name|compat_proc_names
argument_list|)
expr_stmt|;
name|pdb
operator|->
name|compat_proc_names
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
DECL|function|gimp_pdb_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_pdb_get_memsize
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
name|GimpPDB
modifier|*
name|pdb
init|=
name|GIMP_PDB
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|memsize
operator|+=
name|gimp_g_hash_table_get_memsize
argument_list|(
name|pdb
operator|->
name|procedures
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_g_hash_table_get_memsize
argument_list|(
name|pdb
operator|->
name|compat_proc_names
argument_list|)
expr_stmt|;
name|g_hash_table_foreach
argument_list|(
name|pdb
operator|->
name|procedures
argument_list|,
name|gimp_pdb_entry_memsize
argument_list|,
operator|&
name|memsize
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
name|void
DECL|function|gimp_pdb_real_register_procedure (GimpPDB * pdb,GimpProcedure * procedure)
name|gimp_pdb_real_register_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|pdb
operator|->
name|procedures
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_hash_table_replace
argument_list|(
name|pdb
operator|->
name|procedures
argument_list|,
operator|(
name|gpointer
operator|)
name|name
argument_list|,
name|g_list_prepend
argument_list|(
name|list
argument_list|,
name|g_object_ref
argument_list|(
name|procedure
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_real_unregister_procedure (GimpPDB * pdb,GimpProcedure * procedure)
name|gimp_pdb_real_unregister_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|pdb
operator|->
name|procedures
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
name|procedure
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
block|{
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_hash_table_replace
argument_list|(
name|pdb
operator|->
name|procedures
argument_list|,
operator|(
name|gpointer
operator|)
name|name
argument_list|,
name|list
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_hash_table_remove
argument_list|(
name|pdb
operator|->
name|procedures
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpPDB
modifier|*
DECL|function|gimp_pdb_new (Gimp * gimp)
name|gimp_pdb_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpPDB
modifier|*
name|pdb
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
name|pdb
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PDB
argument_list|,
literal|"name"
argument_list|,
literal|"pdb"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pdb
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
return|return
name|pdb
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_pdb_register_procedure (GimpPDB * pdb,GimpProcedure * procedure)
name|gimp_pdb_register_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|pdb
argument_list|,
name|gimp_pdb_signals
index|[
name|REGISTER_PROCEDURE
index|]
argument_list|,
literal|0
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_pdb_unregister_procedure (GimpPDB * pdb,GimpProcedure * procedure)
name|gimp_pdb_unregister_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|pdb
argument_list|,
name|gimp_pdb_signals
index|[
name|UNREGISTER_PROCEDURE
index|]
argument_list|,
literal|0
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpProcedure
modifier|*
DECL|function|gimp_pdb_lookup_procedure (GimpPDB * pdb,const gchar * name)
name|gimp_pdb_lookup_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
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
name|GIMP_IS_PDB
argument_list|(
name|pdb
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
name|pdb
operator|->
name|procedures
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
return|return
name|list
operator|->
name|data
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_pdb_register_compat_proc_name (GimpPDB * pdb,const gchar * old_name,const gchar * new_name)
name|gimp_pdb_register_compat_proc_name
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|old_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|old_name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|new_name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|pdb
operator|->
name|compat_proc_names
argument_list|,
operator|(
name|gpointer
operator|)
name|old_name
argument_list|,
operator|(
name|gpointer
operator|)
name|new_name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_pdb_lookup_compat_proc_name (GimpPDB * pdb,const gchar * old_name)
name|gimp_pdb_lookup_compat_proc_name
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|old_name
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|old_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_hash_table_lookup
argument_list|(
name|pdb
operator|->
name|compat_proc_names
argument_list|,
name|old_name
argument_list|)
return|;
block|}
end_function

begin_function
name|GValueArray
modifier|*
DECL|function|gimp_pdb_execute_procedure_by_name_args (GimpPDB * pdb,GimpContext * context,GimpProgress * progress,const gchar * name,GValueArray * args)
name|gimp_pdb_execute_procedure_by_name_args
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
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
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
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
name|pdb
operator|->
name|procedures
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
literal|"PDB calling error:\n"
literal|"Procedure '%s' not found"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|NULL
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
name|GimpProcedure
modifier|*
name|procedure
init|=
name|list
operator|->
name|data
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
name|return_vals
operator|=
name|gimp_procedure_execute
argument_list|(
name|procedure
argument_list|,
name|pdb
operator|->
name|gimp
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
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
name|g_value_array_free
argument_list|(
name|return_vals
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
name|return_vals
return|;
block|}
end_function

begin_function
name|GValueArray
modifier|*
DECL|function|gimp_pdb_execute_procedure_by_name (GimpPDB * pdb,GimpContext * context,GimpProgress * progress,const gchar * name,...)
name|gimp_pdb_execute_procedure_by_name
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|GValueArray
modifier|*
name|args
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
name|va_list
name|va_args
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
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
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|gimp_pdb_lookup_procedure
argument_list|(
name|pdb
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
operator|==
name|NULL
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"PDB calling error:\n"
literal|"Procedure '%s' not found"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|NULL
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
name|args
operator|=
name|gimp_procedure_get_arguments
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|va_args
argument_list|,
name|name
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
name|GValue
modifier|*
name|value
decl_stmt|;
name|GType
name|arg_type
decl_stmt|;
name|gchar
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|arg_type
operator|=
name|va_arg
argument_list|(
name|va_args
argument_list|,
name|GType
argument_list|)
expr_stmt|;
if|if
condition|(
name|arg_type
operator|==
name|G_TYPE_NONE
condition|)
break|break;
name|value
operator|=
operator|&
name|args
operator|->
name|values
index|[
name|i
index|]
expr_stmt|;
if|if
condition|(
name|arg_type
operator|!=
name|G_VALUE_TYPE
argument_list|(
name|value
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|expected
init|=
name|g_type_name
argument_list|(
name|G_VALUE_TYPE
argument_list|(
name|value
argument_list|)
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
name|g_value_array_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"PDB calling error for procedure '%s':\n"
literal|"Argument #%d type mismatch (expected %s, got %s)"
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
name|i
operator|+
literal|1
argument_list|,
name|expected
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
name|G_VALUE_COLLECT
argument_list|(
name|value
argument_list|,
name|va_args
argument_list|,
name|G_VALUE_NOCOPY_CONTENTS
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
name|g_value_array_free
argument_list|(
name|args
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
block|}
name|va_end
argument_list|(
name|va_args
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_execute_procedure_by_name_args
argument_list|(
name|pdb
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|name
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|g_value_array_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_entry_free (gpointer key,gpointer value,gpointer user_data)
name|gimp_pdb_entry_free
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
block|{
name|g_list_foreach
argument_list|(
name|value
argument_list|,
operator|(
name|GFunc
operator|)
name|g_object_unref
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_entry_memsize (gpointer key,gpointer value,gpointer user_data)
name|gimp_pdb_entry_memsize
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
block|{
name|gint64
modifier|*
name|memsize
init|=
name|user_data
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|value
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
operator|*
name|memsize
operator|+=
sizeof|sizeof
argument_list|(
name|GList
argument_list|)
operator|+
name|gimp_object_get_memsize
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

