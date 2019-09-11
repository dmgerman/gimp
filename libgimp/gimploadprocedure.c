begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimploadprocedure.c  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimploadprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb_pdb.h"
end_include

begin_struct
DECL|struct|_GimpLoadProcedurePrivate
struct|struct
name|_GimpLoadProcedurePrivate
block|{
DECL|member|run_func
name|GimpRunLoadFunc
name|run_func
decl_stmt|;
DECL|member|run_data
name|gpointer
name|run_data
decl_stmt|;
DECL|member|run_data_destroy
name|GDestroyNotify
name|run_data_destroy
decl_stmt|;
DECL|member|handles_raw
name|gboolean
name|handles_raw
decl_stmt|;
DECL|member|thumbnail_proc
name|gchar
modifier|*
name|thumbnail_proc
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_load_procedure_constructed
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
name|gimp_load_procedure_finalize
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
name|gimp_load_procedure_install
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|gimp_load_procedure_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpLoadProcedure,gimp_load_procedure,GIMP_TYPE_FILE_PROCEDURE)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpLoadProcedure
argument_list|,
argument|gimp_load_procedure
argument_list|,
argument|GIMP_TYPE_FILE_PROCEDURE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_load_procedure_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_load_procedure_class_init
parameter_list|(
name|GimpLoadProcedureClass
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
name|GimpProcedureClass
modifier|*
name|procedure_class
init|=
name|GIMP_PROCEDURE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_load_procedure_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_load_procedure_finalize
expr_stmt|;
name|procedure_class
operator|->
name|install
operator|=
name|gimp_load_procedure_install
expr_stmt|;
name|procedure_class
operator|->
name|run
operator|=
name|gimp_load_procedure_run
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_load_procedure_init (GimpLoadProcedure * procedure)
name|gimp_load_procedure_init
parameter_list|(
name|GimpLoadProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|procedure
operator|->
name|priv
operator|=
name|gimp_load_procedure_get_instance_private
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_load_procedure_constructed (GObject * object)
name|gimp_load_procedure_constructed
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
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_FILE
argument_list|(
name|procedure
argument_list|,
literal|"file"
argument_list|,
literal|"File"
argument_list|,
literal|"The file to load"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_VAL_IMAGE
argument_list|(
name|procedure
argument_list|,
literal|"image"
argument_list|,
literal|"Image"
argument_list|,
literal|"Output image"
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_load_procedure_finalize (GObject * object)
name|gimp_load_procedure_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpLoadProcedure
modifier|*
name|procedure
init|=
name|GIMP_LOAD_PROCEDURE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|procedure
operator|->
name|priv
operator|->
name|run_data_destroy
condition|)
name|procedure
operator|->
name|priv
operator|->
name|run_data_destroy
argument_list|(
name|procedure
operator|->
name|priv
operator|->
name|run_data
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|procedure
operator|->
name|priv
operator|->
name|thumbnail_proc
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
DECL|function|gimp_load_procedure_install (GimpProcedure * procedure)
name|gimp_load_procedure_install
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|GimpLoadProcedure
modifier|*
name|load_proc
init|=
name|GIMP_LOAD_PROCEDURE
argument_list|(
name|procedure
argument_list|)
decl_stmt|;
name|GimpFileProcedure
modifier|*
name|file_proc
init|=
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|mime_types
decl_stmt|;
name|gint
name|priority
decl_stmt|;
name|GIMP_PROCEDURE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|install
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|_gimp_pdb_set_file_proc_load_handler
argument_list|(
name|gimp_procedure_get_name
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|gimp_file_procedure_get_extensions
argument_list|(
name|file_proc
argument_list|)
argument_list|,
name|gimp_file_procedure_get_prefixes
argument_list|(
name|file_proc
argument_list|)
argument_list|,
name|gimp_file_procedure_get_magics
argument_list|(
name|file_proc
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_file_procedure_get_handles_remote
argument_list|(
name|file_proc
argument_list|)
condition|)
name|_gimp_pdb_set_file_proc_handles_remote
argument_list|(
name|gimp_procedure_get_name
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|mime_types
operator|=
name|gimp_file_procedure_get_mime_types
argument_list|(
name|file_proc
argument_list|)
expr_stmt|;
if|if
condition|(
name|mime_types
condition|)
name|_gimp_pdb_set_file_proc_mime_types
argument_list|(
name|gimp_procedure_get_name
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|mime_types
argument_list|)
expr_stmt|;
name|priority
operator|=
name|gimp_file_procedure_get_priority
argument_list|(
name|file_proc
argument_list|)
expr_stmt|;
if|if
condition|(
name|priority
operator|!=
literal|0
condition|)
name|_gimp_pdb_set_file_proc_priority
argument_list|(
name|gimp_procedure_get_name
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|priority
argument_list|)
expr_stmt|;
if|if
condition|(
name|load_proc
operator|->
name|priv
operator|->
name|handles_raw
condition|)
name|_gimp_pdb_set_file_proc_handles_raw
argument_list|(
name|gimp_procedure_get_name
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|load_proc
operator|->
name|priv
operator|->
name|thumbnail_proc
condition|)
name|_gimp_pdb_set_file_proc_thumbnail_loader
argument_list|(
name|gimp_procedure_get_name
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|load_proc
operator|->
name|priv
operator|->
name|thumbnail_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|gimp_load_procedure_run (GimpProcedure * procedure,const GimpValueArray * args)
name|gimp_load_procedure_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|)
block|{
name|GimpLoadProcedure
modifier|*
name|load_proc
init|=
name|GIMP_LOAD_PROCEDURE
argument_list|(
name|procedure
argument_list|)
decl_stmt|;
name|GimpValueArray
modifier|*
name|remaining
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_values
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|run_mode
operator|=
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|file
operator|=
name|GIMP_VALUES_GET_FILE
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|remaining
operator|=
name|gimp_value_array_new
argument_list|(
name|gimp_value_array_length
argument_list|(
name|args
argument_list|)
operator|-
literal|2
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|2
init|;
name|i
operator|<
name|gimp_value_array_length
argument_list|(
name|args
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|GValue
modifier|*
name|value
init|=
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|gimp_value_array_append
argument_list|(
name|remaining
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
name|return_values
operator|=
name|load_proc
operator|->
name|priv
operator|->
name|run_func
argument_list|(
name|procedure
argument_list|,
name|run_mode
argument_list|,
name|file
argument_list|,
name|remaining
argument_list|,
name|load_proc
operator|->
name|priv
operator|->
name|run_data
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|remaining
argument_list|)
expr_stmt|;
return|return
name|return_values
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_load_procedure_new:  * @plug_in:          a #GimpPlugIn.  * @name:             the new procedure's name.  * @proc_type:        the new procedure's #GimpPDBProcType.  * @run_func:         the run function for the new procedure.  * @run_data:         user data passed to @run_func.  * @run_data_destroy: (nullable): free function for @run_data, or %NULL.  *  * Creates a new load procedure named @name which will call @run_func  * when invoked.  *  * See gimp_procedure_new() for information about @proc_type.  *  * #GimpLoadProcedure is a #GimpProcedure subclass that makes it easier  * to write file load procedures.  *  * It automatically adds the standard  *  * (GimpRunMode, GFile)  *  * arguments and the standard  *  * (GimpImage)  *  * return value of a load procedure. It is possible to add additional  * arguments.  *  * When invoked via gimp_procedure_run(), it unpacks these standard  * arguments and calls @run_func which is a #GimpRunLoadFunc. The  * "args" #GimpValueArray of #GimpRunLoadFunc only contains  * additionally added arguments.  *  * Returns: a new #GimpProcedure.  *  * Since: 3.0  **/
end_comment

begin_function
name|GimpProcedure
modifier|*
DECL|function|gimp_load_procedure_new (GimpPlugIn * plug_in,const gchar * name,GimpPDBProcType proc_type,GimpRunLoadFunc run_func,gpointer run_data,GDestroyNotify run_data_destroy)
name|gimp_load_procedure_new
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpPDBProcType
name|proc_type
parameter_list|,
name|GimpRunLoadFunc
name|run_func
parameter_list|,
name|gpointer
name|run_data
parameter_list|,
name|GDestroyNotify
name|run_data_destroy
parameter_list|)
block|{
name|GimpLoadProcedure
modifier|*
name|procedure
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
name|g_return_val_if_fail
argument_list|(
name|gimp_is_canonical_identifier
argument_list|(
name|name
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_type
operator|!=
name|GIMP_PDB_PROC_TYPE_INTERNAL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_type
operator|!=
name|GIMP_PDB_PROC_TYPE_EXTENSION
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|run_func
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
name|GIMP_TYPE_LOAD_PROCEDURE
argument_list|,
literal|"plug-in"
argument_list|,
name|plug_in
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
literal|"procedure-type"
argument_list|,
name|proc_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|priv
operator|->
name|run_func
operator|=
name|run_func
expr_stmt|;
name|procedure
operator|->
name|priv
operator|->
name|run_data
operator|=
name|run_data
expr_stmt|;
name|procedure
operator|->
name|priv
operator|->
name|run_data_destroy
operator|=
name|run_data_destroy
expr_stmt|;
return|return
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_load_procedure_set_handles_raw:  * @procedure:   A #GimpLoadProcedure.  * @handles_raw: The procedure's handles raw flag.  *  * Registers a load loader procedure as capable of handling raw  * digital camera loads.  *  * Since: 3.0  **/
end_comment

begin_function
name|void
DECL|function|gimp_load_procedure_set_handles_raw (GimpLoadProcedure * procedure,gint handles_raw)
name|gimp_load_procedure_set_handles_raw
parameter_list|(
name|GimpLoadProcedure
modifier|*
name|procedure
parameter_list|,
name|gint
name|handles_raw
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LOAD_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|priv
operator|->
name|handles_raw
operator|=
name|handles_raw
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_load_procedure_get_handles_raw:  * @procedure: A #GimpLoadProcedure.  *  * Returns: The procedure's handles raw flag as set with  *          gimp_load_procedure_set_handles_raw().  *  * Since: 3.0  **/
end_comment

begin_function
name|gint
DECL|function|gimp_load_procedure_get_handles_raw (GimpLoadProcedure * procedure)
name|gimp_load_procedure_get_handles_raw
parameter_list|(
name|GimpLoadProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LOAD_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|procedure
operator|->
name|priv
operator|->
name|handles_raw
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_load_procedure_set_thumbnail_loader:  * @procedure:      A #GimpLoadProcedure.  * @thumbnail_proc: The name of the thumbnail load procedure.  *  * Associates a thumbnail loader with a file load procedure.  *  * Some file formats allow for embedded thumbnails, other file formats  * contain a scalable image or provide the image data in different  * resolutions. A file plug-in for such a format may register a  * special procedure that allows GIMP to load a thumbnail preview of  * the image. This procedure is then associated with the standard  * load procedure using this function.  *  * Since: 3.0  **/
end_comment

begin_function
name|void
DECL|function|gimp_load_procedure_set_thumbnail_loader (GimpLoadProcedure * procedure,const gchar * thumbnail_proc)
name|gimp_load_procedure_set_thumbnail_loader
parameter_list|(
name|GimpLoadProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|thumbnail_proc
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LOAD_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|procedure
operator|->
name|priv
operator|->
name|thumbnail_proc
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|priv
operator|->
name|thumbnail_proc
operator|=
name|g_strdup
argument_list|(
name|thumbnail_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_load_procedure_get_thumbnail_loader:  * @procedure: A #GimpLoadProcedure.  *  * Returns: The procedure's thumbnail loader procedure as set with  *          gimp_load_procedure_set_thumbnail_loader().  *  * Since: 3.0  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_load_procedure_get_thumbnail_loader (GimpLoadProcedure * procedure)
name|gimp_load_procedure_get_thumbnail_loader
parameter_list|(
name|GimpLoadProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LOAD_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|procedure
operator|->
name|priv
operator|->
name|thumbnail_proc
return|;
block|}
end_function

end_unit

