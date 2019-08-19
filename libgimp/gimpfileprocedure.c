begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfileprocedure.c  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpfileprocedure.h"
end_include

begin_struct
DECL|struct|_GimpFileProcedurePrivate
struct|struct
name|_GimpFileProcedurePrivate
block|{
DECL|member|mime_types
name|gchar
modifier|*
name|mime_types
decl_stmt|;
DECL|member|extensions
name|gchar
modifier|*
name|extensions
decl_stmt|;
DECL|member|prefixes
name|gchar
modifier|*
name|prefixes
decl_stmt|;
DECL|member|magics
name|gchar
modifier|*
name|magics
decl_stmt|;
DECL|member|priority
name|gint
name|priority
decl_stmt|;
DECL|member|handles_uri
name|gboolean
name|handles_uri
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_file_procedure_constructed
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
name|gimp_file_procedure_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE (GimpFileProcedure,gimp_file_procedure,GIMP_TYPE_PROCEDURE)
name|G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpFileProcedure
argument_list|,
argument|gimp_file_procedure
argument_list|,
argument|GIMP_TYPE_PROCEDURE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_file_procedure_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_file_procedure_class_init
parameter_list|(
name|GimpFileProcedureClass
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
name|constructed
operator|=
name|gimp_file_procedure_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_file_procedure_finalize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_procedure_init (GimpFileProcedure * procedure)
name|gimp_file_procedure_init
parameter_list|(
name|GimpFileProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|procedure
operator|->
name|priv
operator|=
name|gimp_file_procedure_get_instance_private
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_procedure_constructed (GObject * object)
name|gimp_file_procedure_constructed
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
name|GIMP_PROC_ARG_ENUM
argument_list|(
name|procedure
argument_list|,
literal|"run-mode"
argument_list|,
literal|"Run mode"
argument_list|,
literal|"The run mode"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_procedure_finalize (GObject * object)
name|gimp_file_procedure_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFileProcedure
modifier|*
name|procedure
init|=
name|GIMP_FILE_PROCEDURE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|procedure
operator|->
name|priv
operator|->
name|mime_types
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|procedure
operator|->
name|priv
operator|->
name|extensions
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|procedure
operator|->
name|priv
operator|->
name|prefixes
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|procedure
operator|->
name|priv
operator|->
name|magics
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

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_file_procedure_set_mime_types:  * @procedure: A #GimpFileProcedure.  * @mime_types: A comma-separated list of MIME types, such as "image/jpeg".  *  * Associates MIME types with a file handler procedure.  *  * Registers MIME types for a file handler procedure. This allows GIMP  * to determine the MIME type of the file opened or saved using this  * procedure. It is recommended that only one MIME type is registered  * per file procedure; when registering more than one MIME type, GIMP  * will associate the first one with files opened or saved with this  * procedure.  *  * Since: 3.0  **/
end_comment

begin_function
name|void
DECL|function|gimp_file_procedure_set_mime_types (GimpFileProcedure * procedure,const gchar * mime_types)
name|gimp_file_procedure_set_mime_types
parameter_list|(
name|GimpFileProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_types
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILE_PROCEDURE
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
name|mime_types
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|priv
operator|->
name|mime_types
operator|=
name|g_strdup
argument_list|(
name|mime_types
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_procedure_get_mime_types:  * @procedure: A #GimpFileProcedure.  *  * Returns: The procedure's mime-type as set with  *          gimp_file_procedure_set_mime_types().  *  * Since: 3.0  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_file_procedure_get_mime_types (GimpFileProcedure * procedure)
name|gimp_file_procedure_get_mime_types
parameter_list|(
name|GimpFileProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILE_PROCEDURE
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
name|mime_types
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_procedure_set_extensions:  * @procedure:  A #GimpFileProcedure.  * @extensions: A comma separated list of extensions this procedure can  *              handle (i.e. "jpg,jpeg").  *  * Since: 3.0  **/
end_comment

begin_function
name|void
DECL|function|gimp_file_procedure_set_extensions (GimpFileProcedure * procedure,const gchar * extensions)
name|gimp_file_procedure_set_extensions
parameter_list|(
name|GimpFileProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extensions
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILE_PROCEDURE
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
name|extensions
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|priv
operator|->
name|extensions
operator|=
name|g_strdup
argument_list|(
name|extensions
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_procedure_get_extensions:  * @procedure: A #GimpFileProcedure.  *  * Returns: The procedure's extensions as set with  *          gimp_file_procedure_set_extensions().  *  * Since: 3.0  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_file_procedure_get_extensions (GimpFileProcedure * procedure)
name|gimp_file_procedure_get_extensions
parameter_list|(
name|GimpFileProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILE_PROCEDURE
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
name|extensions
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_procedure_set_prefixes:  * @procedure: A #GimpFileProcedure.  * @prefixes:  A comma separated list of prefixes this procedure can  *             handle (i.e. "http:,ftp:").  *  * It should almost never be neccessary to register prefixes with file  * procedures, because most sorty of URIs should be handled by GIO.  *  * Since: 3.0  **/
end_comment

begin_function
name|void
DECL|function|gimp_file_procedure_set_prefixes (GimpFileProcedure * procedure,const gchar * prefixes)
name|gimp_file_procedure_set_prefixes
parameter_list|(
name|GimpFileProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prefixes
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILE_PROCEDURE
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
name|prefixes
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|priv
operator|->
name|prefixes
operator|=
name|g_strdup
argument_list|(
name|prefixes
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_procedure_get_prefixes:  * @procedure: A #GimpFileProcedure.  *  * Returns: The procedure's prefixes as set with  *          gimp_file_procedure_set_prefixes().  *  * Since: 3.0  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_file_procedure_get_prefixes (GimpFileProcedure * procedure)
name|gimp_file_procedure_get_prefixes
parameter_list|(
name|GimpFileProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILE_PROCEDURE
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
name|prefixes
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_procedure_set_magics:  * @procedure: A #GimpFileProcedure.  * @magics:    A comma separated list of magic file information this procedure  *             can hande (i.e. "0,string,GIF").  *  * Since: 3.0  **/
end_comment

begin_function
name|void
DECL|function|gimp_file_procedure_set_magics (GimpFileProcedure * procedure,const gchar * magics)
name|gimp_file_procedure_set_magics
parameter_list|(
name|GimpFileProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|magics
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILE_PROCEDURE
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
name|magics
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|priv
operator|->
name|magics
operator|=
name|g_strdup
argument_list|(
name|magics
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_procedure_get_magics:  * @procedure: A #GimpFileProcedure.  *  * Returns: The procedure's magics as set with  *          gimp_file_procedure_set_magics().  *  * Since: 3.0  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_file_procedure_get_magics (GimpFileProcedure * procedure)
name|gimp_file_procedure_get_magics
parameter_list|(
name|GimpFileProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILE_PROCEDURE
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
name|magics
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_procedure_set_priority:  * @procedure: A #GimpFileProcedure.  * @priority: The procedure's priority.  *  * Sets the priority of a file handler procedure. When more than one  * procedure matches a given file, the procedure with the lowest  * priority is used; if more than one procedure has the lowest  * priority, it is unspecified which one of them is used. The default  * priority for file handler procedures is 0.  *  * Since: 3.0  **/
end_comment

begin_function
name|void
DECL|function|gimp_file_procedure_set_priority (GimpFileProcedure * procedure,gint priority)
name|gimp_file_procedure_set_priority
parameter_list|(
name|GimpFileProcedure
modifier|*
name|procedure
parameter_list|,
name|gint
name|priority
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|priv
operator|->
name|priority
operator|=
name|priority
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_procedure_get_priority:  * @procedure: A #GimpFileProcedure.  *  * Returns: The procedure's priority as set with  *          gimp_file_procedure_set_priority().  *  * Since: 3.0  **/
end_comment

begin_function
name|gint
DECL|function|gimp_file_procedure_get_priority (GimpFileProcedure * procedure)
name|gimp_file_procedure_get_priority
parameter_list|(
name|GimpFileProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILE_PROCEDURE
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
name|priority
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_procedure_set_handles_uri:  * @procedure:   A #GimpFileProcedure.  * @handles_uri: The procedure's handles uri flag.  *  * Registers a file procedure as capable of handling arbitrary URIs  * via GIO.  *  * When @handles_uri is set to %TRUE, the procedure will get a #GFile  * passed that can point to a remote file.  *  * When @handles_uri is set to %FALSE, the procedure will get a local  * #GFile passed and can use g_file_get_path() to get to a filename  * that can be used with whatever non-GIO means of dealing with the  * file.  *  * Since: 3.0  **/
end_comment

begin_function
name|void
DECL|function|gimp_file_procedure_set_handles_uri (GimpFileProcedure * procedure,gint handles_uri)
name|gimp_file_procedure_set_handles_uri
parameter_list|(
name|GimpFileProcedure
modifier|*
name|procedure
parameter_list|,
name|gint
name|handles_uri
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|priv
operator|->
name|handles_uri
operator|=
name|handles_uri
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_procedure_get_handles_uri:  * @procedure: A #GimpFileProcedure.  *  * Returns: The procedure's handles uri flag as set with  *          gimp_file_procedure_set_handles_uri().  *  * Since: 3.0  **/
end_comment

begin_function
name|gint
DECL|function|gimp_file_procedure_get_handles_uri (GimpFileProcedure * procedure)
name|gimp_file_procedure_get_handles_uri
parameter_list|(
name|GimpFileProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILE_PROCEDURE
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
name|handles_uri
return|;
block|}
end_function

end_unit

