begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppdb.c  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpprotocol.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpwire.h"
end_include

begin_include
include|#
directive|include
file|"gimp-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpgpparams.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb-private.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb_pdb.h"
end_include

begin_include
include|#
directive|include
file|"gimppdbprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin-private.h"
end_include

begin_include
include|#
directive|include
file|"libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimppdb  * @title: GimpPDB  * @short_description: Functions for querying and changing procedural  *                     database (PDB) entries.  *  * Functions for querying and changing procedural database (PDB)  * entries.  **/
end_comment

begin_struct
DECL|struct|_GimpPDBPrivate
struct|struct
name|_GimpPDBPrivate
block|{
DECL|member|plug_in
name|GimpPlugIn
modifier|*
name|plug_in
decl_stmt|;
DECL|member|procedures
name|GHashTable
modifier|*
name|procedures
decl_stmt|;
DECL|member|error_status
name|GimpPDBStatusType
name|error_status
decl_stmt|;
DECL|member|error_message
name|gchar
modifier|*
name|error_message
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_pdb_dispose
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
name|void
name|gimp_pdb_set_error
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpValueArray
modifier|*
name|return_values
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpPDB,gimp_pdb,G_TYPE_OBJECT)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpPDB
argument_list|,
argument|gimp_pdb
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_pdb_parent_class
end_define

begin_function
specifier|static
name|void
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
name|object_class
operator|->
name|dispose
operator|=
name|gimp_pdb_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_pdb_finalize
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
name|priv
operator|=
name|gimp_pdb_get_instance_private
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|pdb
operator|->
name|priv
operator|->
name|procedures
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
name|g_free
argument_list|,
name|g_object_unref
argument_list|)
expr_stmt|;
name|pdb
operator|->
name|priv
operator|->
name|error_status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_dispose (GObject * object)
name|gimp_pdb_dispose
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
name|g_clear_pointer
argument_list|(
operator|&
name|pdb
operator|->
name|priv
operator|->
name|procedures
argument_list|,
name|g_hash_table_unref
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
name|g_clear_object
argument_list|(
operator|&
name|pdb
operator|->
name|priv
operator|->
name|plug_in
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|pdb
operator|->
name|priv
operator|->
name|error_message
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
name|GimpPDB
modifier|*
DECL|function|_gimp_pdb_new (GimpPlugIn * plug_in)
name|_gimp_pdb_new
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|GimpPDB
modifier|*
name|pdb
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
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
name|NULL
argument_list|)
expr_stmt|;
name|pdb
operator|->
name|priv
operator|->
name|plug_in
operator|=
name|g_object_ref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
return|return
name|pdb
return|;
block|}
end_function

begin_function
name|GimpPlugIn
modifier|*
DECL|function|_gimp_pdb_get_plug_in (GimpPDB * pdb)
name|_gimp_pdb_get_plug_in
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
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
return|return
name|pdb
operator|->
name|priv
operator|->
name|plug_in
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pdb_procedure_exists:  * @pdb:            A #GimpPDB instance.  * @procedure_name: A procedure name  *  * This function checks if a procedure exists in the procedural  * database.  *  * Return: %TRUE if the procedure exists, %FALSE otherwise.  *  * Since: 3.0  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_pdb_procedure_exists (GimpPDB * pdb,const gchar * procedure_name)
name|gimp_pdb_procedure_exists
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_is_canonical_identifier
argument_list|(
name|procedure_name
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|_gimp_pdb_proc_exists
argument_list|(
name|procedure_name
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pdb_lookup_procedure:  * @pdb:            A #GimpPDB instance.  * @procedure_name: A procedure name  *  * This function returns the #GimpProcedure which is registered  * with @procedure_name if it exists, or returns %NULL otherwise.  *  * The returned #GimpProcedure is owned by @pdb and must not be  * modified.  *  * Return: (nullable) (transfer none): A #GimpProcedure, or %NULL.  *  * Since: 3.0  **/
end_comment

begin_function
name|GimpProcedure
modifier|*
DECL|function|gimp_pdb_lookup_procedure (GimpPDB * pdb,const gchar * procedure_name)
name|gimp_pdb_lookup_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
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
name|gimp_is_canonical_identifier
argument_list|(
name|procedure_name
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|g_hash_table_lookup
argument_list|(
name|pdb
operator|->
name|priv
operator|->
name|procedures
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|procedure
condition|)
block|{
name|procedure
operator|=
name|_gimp_pdb_procedure_new
argument_list|(
name|pdb
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
condition|)
name|g_hash_table_insert
argument_list|(
name|pdb
operator|->
name|priv
operator|->
name|procedures
argument_list|,
name|g_strdup
argument_list|(
name|procedure_name
argument_list|)
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
block|}
return|return
name|procedure
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pdb_run_procedure:  * @pdb:            the #GimpPDB object.  * @procedure_name: the procedure registered name.  * @first_type:     the #GType of the first argument, or #G_TYPE_NONE.  * @...:            the call arguments.  *  * Runs the procedure named @procedure_name with arguments given as  * list of (#GType, value) pairs, terminated by #G_TYPE_NONE.  *  * Returns: (transfer full): the return values for the procedure call.  *  * Since: 3.0  */
end_comment

begin_function
name|GimpValueArray
modifier|*
DECL|function|gimp_pdb_run_procedure (GimpPDB * pdb,const gchar * procedure_name,GType first_type,...)
name|gimp_pdb_run_procedure
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|GType
name|first_type
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|return_values
decl_stmt|;
name|va_list
name|args
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
name|gimp_is_canonical_identifier
argument_list|(
name|procedure_name
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|first_type
argument_list|)
expr_stmt|;
name|return_values
operator|=
name|gimp_pdb_run_procedure_valist
argument_list|(
name|pdb
argument_list|,
name|procedure_name
argument_list|,
name|first_type
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
name|return_values
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pdb_run_procedure_valist:  * @pdb:            the #GimpPDB object.  * @procedure_name: the procedure registered name.  * @first_type:     the #GType of the first argument, or #G_TYPE_NONE.  * @args:           the call arguments.  *  * Runs the procedure named @procedure_name with @args given in the  * order as passed to gimp_pdb_run_procedure().  *  * Returns: (transfer full): the return values for the procedure call.  *  * Since: 3.0  */
end_comment

begin_function
name|GimpValueArray
modifier|*
DECL|function|gimp_pdb_run_procedure_valist (GimpPDB * pdb,const gchar * procedure_name,GType first_type,va_list args)
name|gimp_pdb_run_procedure_valist
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|GType
name|first_type
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|arguments
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_values
decl_stmt|;
name|gchar
modifier|*
name|error_msg
init|=
name|NULL
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
name|gimp_is_canonical_identifier
argument_list|(
name|procedure_name
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|arguments
operator|=
name|gimp_value_array_new_from_types_valist
argument_list|(
operator|&
name|error_msg
argument_list|,
name|first_type
argument_list|,
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|arguments
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|g_error_new_literal
argument_list|(
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_INTERNAL_ERROR
argument_list|,
name|error_msg
argument_list|)
decl_stmt|;
name|g_printerr
argument_list|(
literal|"%s: %s"
argument_list|,
name|G_STRFUNC
argument_list|,
name|error_msg
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|error_msg
argument_list|)
expr_stmt|;
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|NULL
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|error
argument_list|)
return|;
block|}
name|return_values
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|pdb
argument_list|,
name|procedure_name
argument_list|,
name|arguments
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|arguments
argument_list|)
expr_stmt|;
return|return
name|return_values
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pdb_run_procedure_array: (rename-to gimp_pdb_run_procedure)  * @pdb:            the #GimpPDB object.  * @procedure_name: the procedure registered name.  * @arguments:      the call arguments.  *  * Runs the procedure named @procedure_name with @arguments.  *  * Returns: (transfer full): the return values for the procedure call.  *  * Since: 3.0  */
end_comment

begin_function
name|GimpValueArray
modifier|*
DECL|function|gimp_pdb_run_procedure_array (GimpPDB * pdb,const gchar * procedure_name,const GimpValueArray * arguments)
name|gimp_pdb_run_procedure_array
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|arguments
parameter_list|)
block|{
name|GPProcRun
name|proc_run
decl_stmt|;
name|GPProcReturn
modifier|*
name|proc_return
decl_stmt|;
name|GimpWireMessage
name|msg
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_values
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
name|gimp_is_canonical_identifier
argument_list|(
name|procedure_name
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|arguments
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|proc_run
operator|.
name|name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|procedure_name
expr_stmt|;
name|proc_run
operator|.
name|n_params
operator|=
name|gimp_value_array_length
argument_list|(
name|arguments
argument_list|)
expr_stmt|;
name|proc_run
operator|.
name|params
operator|=
name|_gimp_value_array_to_gp_params
argument_list|(
name|arguments
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gp_proc_run_write
argument_list|(
name|_gimp_plug_in_get_write_channel
argument_list|(
name|pdb
operator|->
name|priv
operator|->
name|plug_in
argument_list|)
argument_list|,
operator|&
name|proc_run
argument_list|,
name|pdb
operator|->
name|priv
operator|->
name|plug_in
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
name|_gimp_gp_params_free
argument_list|(
name|proc_run
operator|.
name|params
argument_list|,
name|proc_run
operator|.
name|n_params
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|_gimp_plug_in_read_expect_msg
argument_list|(
name|pdb
operator|->
name|priv
operator|->
name|plug_in
argument_list|,
operator|&
name|msg
argument_list|,
name|GP_PROC_RETURN
argument_list|)
expr_stmt|;
name|proc_return
operator|=
name|msg
operator|.
name|data
expr_stmt|;
name|return_values
operator|=
name|_gimp_gp_params_to_value_array
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|proc_return
operator|->
name|params
argument_list|,
name|proc_return
operator|->
name|n_params
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_wire_destroy
argument_list|(
operator|&
name|msg
argument_list|)
expr_stmt|;
name|gimp_pdb_set_error
argument_list|(
name|pdb
argument_list|,
name|return_values
argument_list|)
expr_stmt|;
return|return
name|return_values
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pdb_temp_procedure_name:  * @pdb: the #GimpPDB object.  *  * Generates a unique temporary PDB name.  *  * This function generates a temporary PDB entry name that is  * guaranteed to be unique.  *  * Returns: (transfer full): A unique temporary name for a temporary  *          PDB entry. The returned value must be freed with  *          g_free().  *  * Since: 3.0  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_pdb_temp_procedure_name (GimpPDB * pdb)
name|gimp_pdb_temp_procedure_name
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
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
return|return
name|_gimp_pdb_temp_name
argument_list|()
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pdb_dump_to_file:  * @pdb:  A #GimpPDB.  * @file: The dump filename.  *  * Dumps the current contents of the procedural database  *  * This procedure dumps the contents of the procedural database to the  * specified @file. The file will contain all of the information  * provided for each registered procedure.  *  * Returns: TRUE on success.  *  * Since: 3.0  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_pdb_dump_to_file (GimpPDB * pdb,GFile * file)
name|gimp_pdb_dump_to_file
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
block|{
name|gchar
modifier|*
name|path
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|pdb
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|path
operator|=
name|g_file_get_path
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|success
operator|=
name|_gimp_pdb_dump
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pdb_query_procedures:  * @pdb:         A #GimpPDB.  * @name:        The regex for procedure name.  * @blurb:       The regex for procedure blurb.  * @help:        The regex for procedure help.  * @help_id:     The regex for procedure help-id.  * @authors:     The regex for procedure authors.  * @copyright:   The regex for procedure copyright.  * @date:        The regex for procedure date.  * @proc_type:   The regex for procedure type: { 'Internal GIMP procedure', 'GIMP Plug-in', 'GIMP Extension', 'Temporary Procedure' }.  * @num_matches: (out): The number of matching procedures.  *  * Queries the procedural database for its contents using regular  * expression matching.  *  * This function queries the contents of the procedural database. It  * is supplied with eight arguments matching procedures on  *  * { name, blurb, help, help-id, authors, copyright, date, procedure type}.  *  * This is accomplished using regular expression matching. For  * instance, to find all procedures with "jpeg" listed in the blurb,  * all seven arguments can be supplied as ".*", except for the second,  * which can be supplied as ".*jpeg.*". There are two return arguments  * for this procedure. The first is the number of procedures matching  * the query. The second is a concatenated list of procedure names  * corresponding to those matching the query. If no matching entries  * are found, then the returned string is NULL and the number of  * entries is 0.  *  * Returns: (array length=num_matches) (transfer full): The list  *          of procedure names. Free with g_strfreev().  *  * Since: 3.0  **/
end_comment

begin_function
name|gchar
modifier|*
modifier|*
DECL|function|gimp_pdb_query_procedures (GimpPDB * pdb,const gchar * name,const gchar * blurb,const gchar * help,const gchar * help_id,const gchar * authors,const gchar * copyright,const gchar * date,const gchar * proc_type,gint * num_matches)
name|gimp_pdb_query_procedures
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|authors
parameter_list|,
specifier|const
name|gchar
modifier|*
name|copyright
parameter_list|,
specifier|const
name|gchar
modifier|*
name|date
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_type
parameter_list|,
name|gint
modifier|*
name|num_matches
parameter_list|)
block|{
name|gchar
modifier|*
modifier|*
name|matches
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
name|_gimp_pdb_query
argument_list|(
name|name
argument_list|,
name|blurb
argument_list|,
name|help
argument_list|,
comment|/* FIXME help_id */
name|authors
argument_list|,
name|copyright
argument_list|,
name|date
argument_list|,
name|proc_type
argument_list|,
name|num_matches
argument_list|,
operator|&
name|matches
argument_list|)
expr_stmt|;
return|return
name|matches
return|;
block|}
end_function

begin_function
name|GQuark
DECL|function|_gimp_pdb_error_quark (void)
name|_gimp_pdb_error_quark
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_quark_from_static_string
argument_list|(
literal|"gimp-pdb-error-quark"
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  Temporary API, to go away before 3.0  */
end_comment

begin_comment
comment|/**  * gimp_pdb_get_last_error:  * @pdb: a #GimpPDB.  *  * Retrieves the error message from the last procedure call.  *  * If a procedure call fails, then it might pass an error message with  * the return values. Plug-ins that are using the libgimp C wrappers  * don't access the procedure return values directly. Thus #GimpPDB  * stores the error message and makes it available with this  * function. The next procedure call unsets the error message again.  *  * The returned string is owned by @pdb and must not be freed or  * modified.  *  * Returns: the error message  *  * Since: 3.0  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_pdb_get_last_error (GimpPDB * pdb)
name|gimp_pdb_get_last_error
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
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
if|if
condition|(
name|pdb
operator|->
name|priv
operator|->
name|error_message
operator|&&
name|strlen
argument_list|(
name|pdb
operator|->
name|priv
operator|->
name|error_message
argument_list|)
condition|)
return|return
name|pdb
operator|->
name|priv
operator|->
name|error_message
return|;
switch|switch
condition|(
name|pdb
operator|->
name|priv
operator|->
name|error_status
condition|)
block|{
case|case
name|GIMP_PDB_SUCCESS
case|:
comment|/*  procedure executed successfully  */
return|return
name|_
argument_list|(
literal|"success"
argument_list|)
return|;
case|case
name|GIMP_PDB_EXECUTION_ERROR
case|:
comment|/*  procedure execution failed       */
return|return
name|_
argument_list|(
literal|"execution error"
argument_list|)
return|;
case|case
name|GIMP_PDB_CALLING_ERROR
case|:
comment|/*  procedure called incorrectly     */
return|return
name|_
argument_list|(
literal|"calling error"
argument_list|)
return|;
case|case
name|GIMP_PDB_CANCEL
case|:
comment|/*  procedure execution cancelled    */
return|return
name|_
argument_list|(
literal|"cancelled"
argument_list|)
return|;
default|default:
return|return
literal|"invalid return status"
return|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_pdb_get_last_status:  * @pdb: a #GimpPDB.  *  * Retrieves the status from the last procedure call.  *  * Returns: the #GimpPDBStatusType.  *  * Since: 3.0  **/
end_comment

begin_function
name|GimpPDBStatusType
DECL|function|gimp_pdb_get_last_status (GimpPDB * pdb)
name|gimp_pdb_get_last_status
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
argument_list|)
argument_list|,
name|GIMP_PDB_SUCCESS
argument_list|)
expr_stmt|;
return|return
name|pdb
operator|->
name|priv
operator|->
name|error_status
return|;
block|}
end_function

begin_comment
comment|/*  Cruft API  */
end_comment

begin_comment
comment|/**  * gimp_pdb_get_data:  * @identifier: The identifier associated with data.  * @data: A byte array containing data.  *  * Returns data associated with the specified identifier.  *  * This procedure returns any data which may have been associated with  * the specified identifier. The data is copied into the given memory  * location.  *  * Returns: TRUE on success, FALSE if no data has been associated with  * the identifier  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_pdb_get_data (const gchar * identifier,gpointer data)
name|gimp_pdb_get_data
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gint
name|size
decl_stmt|;
name|guint8
modifier|*
name|hack
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|success
operator|=
name|_gimp_pdb_get_data
argument_list|(
name|identifier
argument_list|,
operator|&
name|size
argument_list|,
operator|&
name|hack
argument_list|)
expr_stmt|;
if|if
condition|(
name|hack
condition|)
block|{
name|memcpy
argument_list|(
name|data
argument_list|,
operator|(
name|gconstpointer
operator|)
name|hack
argument_list|,
name|size
operator|*
sizeof|sizeof
argument_list|(
name|guint8
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|hack
argument_list|)
expr_stmt|;
block|}
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pdb_get_data_size:  * @identifier: The identifier associated with data.  *  * Returns size of data associated with the specified identifier.  *  * This procedure returns the size of any data which may have been  * associated with the specified identifier. If no data has been  * associated with the identifier, an error is returned.  *  * Returns: The number of bytes in the data.  **/
end_comment

begin_function
name|gint
DECL|function|gimp_pdb_get_data_size (const gchar * identifier)
name|gimp_pdb_get_data_size
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|)
block|{
return|return
name|_gimp_pdb_get_data_size
argument_list|(
name|identifier
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pdb_set_data:  * @identifier: The identifier associated with data.  * @data: A byte array containing data.  * @bytes: The number of bytes in the data  *  * Associates the specified identifier with the supplied data.  *  * This procedure associates the supplied data with the provided  * identifier. The data may be subsequently retrieved by a call to  * 'procedural-db-get-data'.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_pdb_set_data (const gchar * identifier,gconstpointer data,guint32 bytes)
name|gimp_pdb_set_data
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gconstpointer
name|data
parameter_list|,
name|guint32
name|bytes
parameter_list|)
block|{
return|return
name|_gimp_pdb_set_data
argument_list|(
name|identifier
argument_list|,
name|bytes
argument_list|,
name|data
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_set_error (GimpPDB * pdb,GimpValueArray * return_values)
name|gimp_pdb_set_error
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpValueArray
modifier|*
name|return_values
parameter_list|)
block|{
name|g_clear_pointer
argument_list|(
operator|&
name|pdb
operator|->
name|priv
operator|->
name|error_message
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|pdb
operator|->
name|priv
operator|->
name|error_status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
if|if
condition|(
name|gimp_value_array_length
argument_list|(
name|return_values
argument_list|)
operator|>
literal|0
condition|)
block|{
name|pdb
operator|->
name|priv
operator|->
name|error_status
operator|=
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_values
argument_list|,
literal|0
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|pdb
operator|->
name|priv
operator|->
name|error_status
condition|)
block|{
case|case
name|GIMP_PDB_SUCCESS
case|:
case|case
name|GIMP_PDB_PASS_THROUGH
case|:
break|break;
case|case
name|GIMP_PDB_EXECUTION_ERROR
case|:
case|case
name|GIMP_PDB_CALLING_ERROR
case|:
case|case
name|GIMP_PDB_CANCEL
case|:
if|if
condition|(
name|gimp_value_array_length
argument_list|(
name|return_values
argument_list|)
operator|>
literal|1
condition|)
block|{
name|GValue
modifier|*
name|value
init|=
name|gimp_value_array_index
argument_list|(
name|return_values
argument_list|,
literal|1
argument_list|)
decl_stmt|;
if|if
condition|(
name|G_VALUE_HOLDS_STRING
argument_list|(
name|value
argument_list|)
condition|)
name|pdb
operator|->
name|priv
operator|->
name|error_message
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
block|}
block|}
end_function

end_unit

