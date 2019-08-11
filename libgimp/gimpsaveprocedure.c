begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsaveprocedure.c  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_define
DECL|macro|GIMP_DISABLE_COMPAT_CRUFT
define|#
directive|define
name|GIMP_DISABLE_COMPAT_CRUFT
end_define

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpsaveprocedure.h"
end_include

begin_struct
DECL|struct|_GimpSaveProcedurePrivate
struct|struct
name|_GimpSaveProcedurePrivate
block|{
DECL|member|run_func
name|GimpRunSaveFunc
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
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_save_procedure_constructed
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
name|gimp_save_procedure_finalize
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
name|gimp_save_procedure_install
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
name|gimp_save_procedure_run
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
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpSaveProcedure,gimp_save_procedure,GIMP_TYPE_FILE_PROCEDURE)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpSaveProcedure
argument_list|,
argument|gimp_save_procedure
argument_list|,
argument|GIMP_TYPE_FILE_PROCEDURE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_save_procedure_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_save_procedure_class_init
parameter_list|(
name|GimpSaveProcedureClass
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
name|gimp_save_procedure_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_save_procedure_finalize
expr_stmt|;
name|procedure_class
operator|->
name|install
operator|=
name|gimp_save_procedure_install
expr_stmt|;
name|procedure_class
operator|->
name|run
operator|=
name|gimp_save_procedure_run
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_save_procedure_init (GimpSaveProcedure * procedure)
name|gimp_save_procedure_init
parameter_list|(
name|GimpSaveProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|procedure
operator|->
name|priv
operator|=
name|gimp_save_procedure_get_instance_private
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_save_procedure_constructed (GObject * object)
name|gimp_save_procedure_constructed
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
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"Image"
argument_list|,
literal|"The image to save"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_drawable_id
argument_list|(
literal|"drawable"
argument_list|,
literal|"Drawable"
argument_list|,
literal|"The drawable "
literal|"to save"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"uri"
argument_list|,
literal|"URI"
argument_list|,
literal|"The URI of the file "
literal|"to save to"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"raw-uri"
argument_list|,
literal|"Raw URI"
argument_list|,
literal|"The URI of the file "
literal|"to save to"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_save_procedure_finalize (GObject * object)
name|gimp_save_procedure_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSaveProcedure
modifier|*
name|procedure
init|=
name|GIMP_SAVE_PROCEDURE
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
DECL|function|gimp_save_procedure_install (GimpProcedure * procedure)
name|gimp_save_procedure_install
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
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
name|_gimp_register_save_handler
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
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_file_procedure_get_handles_uri
argument_list|(
name|file_proc
argument_list|)
condition|)
name|_gimp_register_file_handler_uri
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
name|_gimp_register_file_handler_mime
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
name|_gimp_register_file_handler_priority
argument_list|(
name|gimp_procedure_get_name
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|priority
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|gimp_save_procedure_run (GimpProcedure * procedure,const GimpValueArray * args)
name|gimp_save_procedure_run
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
name|GimpSaveProcedure
modifier|*
name|save_proc
init|=
name|GIMP_SAVE_PROCEDURE
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
name|gint32
name|image_id
decl_stmt|;
name|gint32
name|drawable_id
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|uri
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|image_id
operator|=
name|gimp_value_get_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|drawable_id
operator|=
name|gimp_value_get_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
comment|/* raw_uri  = g_value_get_string         (gimp_value_array_index (args, 4)); */
name|file
operator|=
name|g_file_new_for_uri
argument_list|(
name|uri
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
literal|5
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|5
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
name|save_proc
operator|->
name|priv
operator|->
name|run_func
argument_list|(
name|procedure
argument_list|,
name|run_mode
argument_list|,
name|image_id
argument_list|,
name|drawable_id
argument_list|,
name|file
argument_list|,
name|remaining
argument_list|,
name|save_proc
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
name|g_object_unref
argument_list|(
name|file
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
comment|/**  * gimp_save_procedure_new:  * @plug_in:          a #GimpPlugIn.  * @name:             the new procedure's name.  * @proc_type:        the new procedure's #GimpPDBProcType.  * @run_func:         the run function for the new procedure.  * @run_data:         user data passed to @run_func.  * @run_data_destroy: (nullable): free function for @run_data, or %NULL.  *  * Creates a new save procedure named @name which will call @run_func  * when invoked.  *  * See gimp_procedure_new() for information about @proc_type.  *  * #GimpSaveProcedure is a #GimpProcedure subclass that makes it easier  * to write file save procedures.  *  * It automatically adds the standard  *  * (run-mode, image-id, drawable-id, uri, raw-uri)  *  * arguments of a save procedure. It is possible to add additional  * arguments.  *  * When invoked via gimp_procedure_run(), it unpacks these standard  * arguemnts and calls @run_func which is a #GimpRunSaveFunc. The  * "args" #GimpValueArray of #GimpRunSaveFunc only contains  * additionally added arguments.  *  * Returns: a new #GimpProcedure.  *  * Since: 3.0  **/
end_comment

begin_function
name|GimpProcedure
modifier|*
DECL|function|gimp_save_procedure_new (GimpPlugIn * plug_in,const gchar * name,GimpPDBProcType proc_type,GimpRunSaveFunc run_func,gpointer run_data,GDestroyNotify run_data_destroy)
name|gimp_save_procedure_new
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
name|GimpRunSaveFunc
name|run_func
parameter_list|,
name|gpointer
name|run_data
parameter_list|,
name|GDestroyNotify
name|run_data_destroy
parameter_list|)
block|{
name|GimpSaveProcedure
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
name|GIMP_INTERNAL
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
name|GIMP_TYPE_SAVE_PROCEDURE
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

end_unit

