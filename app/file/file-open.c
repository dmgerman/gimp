begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * file-open.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_SYS_PARAM_H
end_ifdef

begin_include
include|#
directive|include
file|<sys/param.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_define
DECL|macro|R_OK
define|#
directive|define
name|R_OK
value|4
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
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
file|"core/gimpdocumentlist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-merge.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimagefile.h"
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
file|"pdb/gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginprocedure.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginerror.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-icc-profile.h"
end_include

begin_include
include|#
directive|include
file|"file-open.h"
end_include

begin_include
include|#
directive|include
file|"file-procedure.h"
end_include

begin_include
include|#
directive|include
file|"file-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|file_open_sanitize_image
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|as_new
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_open_handle_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpImage
modifier|*
DECL|function|file_open_image (Gimp * gimp,GimpContext * context,GimpProgress * progress,const gchar * uri,const gchar * entered_filename,gboolean as_new,GimpPlugInProcedure * file_proc,GimpRunMode run_mode,GimpPDBStatusType * status,const gchar ** mime_type,GError ** error)
name|file_open_image
parameter_list|(
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
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|entered_filename
parameter_list|,
name|gboolean
name|as_new
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|file_proc
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GimpPDBStatusType
modifier|*
name|status
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|mime_type
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|NULL
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
name|status
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
name|file_proc
operator|=
name|file_procedure_find
argument_list|(
name|gimp
operator|->
name|plug_in_manager
operator|->
name|load_procs
argument_list|,
name|uri
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
return|return
name|NULL
return|;
name|filename
operator|=
name|file_utils_filename_from_uri
argument_list|(
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
comment|/* check if we are opening a file */
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"Not a regular file"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|g_access
argument_list|(
name|filename
argument_list|,
name|R_OK
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_ACCES
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
block|}
else|else
block|{
name|filename
operator|=
name|g_strdup
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_pdb_execute_procedure_by_name
argument_list|(
name|gimp
operator|->
name|pdb
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|file_proc
argument_list|)
operator|->
name|name
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|run_mode
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|filename
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|entered_filename
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
operator|*
name|status
operator|=
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
expr_stmt|;
if|if
condition|(
operator|*
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|file_open_sanitize_image
argument_list|(
name|image
argument_list|,
name|as_new
argument_list|)
expr_stmt|;
comment|/* Only set the load procedure if it hasn't already been set. */
if|if
condition|(
operator|!
name|gimp_image_get_load_proc
argument_list|(
name|image
argument_list|)
condition|)
name|gimp_image_set_load_proc
argument_list|(
name|image
argument_list|,
name|file_proc
argument_list|)
expr_stmt|;
name|file_proc
operator|=
name|gimp_image_get_load_proc
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|mime_type
condition|)
operator|*
name|mime_type
operator|=
name|file_proc
operator|->
name|mime_type
expr_stmt|;
block|}
else|else
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"%s plug-in returned SUCCESS but did not "
literal|"return an image"
argument_list|)
argument_list|,
name|gimp_plug_in_procedure_get_label
argument_list|(
name|file_proc
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
operator|*
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"%s plug-In could not open image"
argument_list|)
argument_list|,
name|gimp_plug_in_procedure_get_label
argument_list|(
name|file_proc
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_value_array_free
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|gimp_image_undo_disable
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|file_open_handle_color_profile
argument_list|(
name|image
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|run_mode
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
return|return
name|image
return|;
block|}
end_function

begin_comment
comment|/*  Attempts to load a thumbnail by using a registered thumbnail loader.  */
end_comment

begin_function
name|GimpImage
modifier|*
DECL|function|file_open_thumbnail (Gimp * gimp,GimpContext * context,GimpProgress * progress,const gchar * uri,gint size,const gchar ** mime_type,gint * image_width,gint * image_height)
name|file_open_thumbnail
parameter_list|(
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
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gint
name|size
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|mime_type
parameter_list|,
name|gint
modifier|*
name|image_width
parameter_list|,
name|gint
modifier|*
name|image_height
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|file_proc
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
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
name|mime_type
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|image_width
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|image_height
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|image_width
operator|=
literal|0
expr_stmt|;
operator|*
name|image_height
operator|=
literal|0
expr_stmt|;
name|file_proc
operator|=
name|file_procedure_find
argument_list|(
name|gimp
operator|->
name|plug_in_manager
operator|->
name|load_procs
argument_list|,
name|uri
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
operator|||
operator|!
name|file_proc
operator|->
name|thumb_loader
condition|)
return|return
name|NULL
return|;
name|procedure
operator|=
name|gimp_pdb_lookup_procedure
argument_list|(
name|gimp
operator|->
name|pdb
argument_list|,
name|file_proc
operator|->
name|thumb_loader
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
operator|&&
name|procedure
operator|->
name|num_args
operator|>=
literal|2
operator|&&
name|procedure
operator|->
name|num_values
operator|>=
literal|1
condition|)
block|{
name|GimpPDBStatusType
name|status
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|NULL
decl_stmt|;
name|filename
operator|=
name|file_utils_filename_from_uri
argument_list|(
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|filename
condition|)
name|filename
operator|=
name|g_strdup
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_execute_procedure_by_name
argument_list|(
name|gimp
operator|->
name|pdb
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
operator|->
name|name
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|filename
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|size
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|status
operator|=
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
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
operator|->
name|n_values
operator|>=
literal|3
condition|)
block|{
operator|*
name|image_width
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|g_value_get_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|2
index|]
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|image_height
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|g_value_get_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|3
index|]
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|image
condition|)
block|{
name|file_open_sanitize_image
argument_list|(
name|image
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
operator|*
name|mime_type
operator|=
name|file_proc
operator|->
name|mime_type
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
name|g_printerr
argument_list|(
literal|"opened thumbnail at %d x %d\n"
argument_list|,
name|image
operator|->
name|width
argument_list|,
name|image
operator|->
name|height
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
block|}
name|g_value_array_free
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|image
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|file_open_with_display (Gimp * gimp,GimpContext * context,GimpProgress * progress,const gchar * uri,gboolean as_new,GimpPDBStatusType * status,GError ** error)
name|file_open_with_display
parameter_list|(
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
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
name|as_new
parameter_list|,
name|GimpPDBStatusType
modifier|*
name|status
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
return|return
name|file_open_with_proc_and_display
argument_list|(
name|gimp
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|uri
argument_list|,
name|uri
argument_list|,
name|as_new
argument_list|,
name|NULL
argument_list|,
name|status
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|file_open_with_proc_and_display (Gimp * gimp,GimpContext * context,GimpProgress * progress,const gchar * uri,const gchar * entered_filename,gboolean as_new,GimpPlugInProcedure * file_proc,GimpPDBStatusType * status,GError ** error)
name|file_open_with_proc_and_display
parameter_list|(
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
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|entered_filename
parameter_list|,
name|gboolean
name|as_new
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|file_proc
parameter_list|,
name|GimpPDBStatusType
modifier|*
name|status
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|mime_type
init|=
name|NULL
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
name|status
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image
operator|=
name|file_open_image
argument_list|(
name|gimp
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|uri
argument_list|,
name|entered_filename
argument_list|,
name|as_new
argument_list|,
name|file_proc
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|status
argument_list|,
operator|&
name|mime_type
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|gimp_create_display
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|image
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|as_new
condition|)
block|{
name|GimpDocumentList
modifier|*
name|documents
init|=
name|GIMP_DOCUMENT_LIST
argument_list|(
name|gimp
operator|->
name|documents
argument_list|)
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
name|imagefile
operator|=
name|gimp_document_list_add_uri
argument_list|(
name|documents
argument_list|,
name|uri
argument_list|,
name|mime_type
argument_list|)
expr_stmt|;
comment|/*  can only create a thumbnail if the passed uri and the            *  resulting image's uri match.            */
if|if
condition|(
name|strcmp
argument_list|(
name|uri
argument_list|,
name|gimp_image_get_uri
argument_list|(
name|image
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/*  no need to save a thumbnail if there's a good one already  */
if|if
condition|(
operator|!
name|gimp_imagefile_check_thumbnail
argument_list|(
name|imagefile
argument_list|)
condition|)
block|{
name|gimp_imagefile_save_thumbnail
argument_list|(
name|imagefile
argument_list|,
name|mime_type
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|gimp
operator|->
name|config
operator|->
name|save_document_history
condition|)
name|gimp_recent_list_add_uri
argument_list|(
name|gimp
argument_list|,
name|uri
argument_list|,
name|mime_type
argument_list|)
expr_stmt|;
block|}
comment|/*  the display owns the image now  */
name|g_object_unref
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
return|return
name|image
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|file_open_layers (Gimp * gimp,GimpContext * context,GimpProgress * progress,GimpImage * dest_image,gboolean merge_visible,const gchar * uri,GimpRunMode run_mode,GimpPlugInProcedure * file_proc,GimpPDBStatusType * status,GError ** error)
name|file_open_layers
parameter_list|(
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
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
name|gboolean
name|merge_visible
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|file_proc
parameter_list|,
name|GimpPDBStatusType
modifier|*
name|status
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpImage
modifier|*
name|new_image
decl_stmt|;
name|GList
modifier|*
name|layers
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|mime_type
init|=
name|NULL
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
name|GIMP_IS_IMAGE
argument_list|(
name|dest_image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|status
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|new_image
operator|=
name|file_open_image
argument_list|(
name|gimp
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|uri
argument_list|,
name|uri
argument_list|,
name|FALSE
argument_list|,
name|file_proc
argument_list|,
name|run_mode
argument_list|,
name|status
argument_list|,
operator|&
name|mime_type
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_image
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|n_visible
init|=
literal|0
decl_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|new_image
operator|->
name|layers
argument_list|)
operator|->
name|list
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
if|if
condition|(
operator|!
name|merge_visible
condition|)
name|layers
operator|=
name|g_list_prepend
argument_list|(
name|layers
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_item_get_visible
argument_list|(
name|list
operator|->
name|data
argument_list|)
condition|)
block|{
name|n_visible
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|layers
condition|)
name|layers
operator|=
name|g_list_prepend
argument_list|(
name|layers
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|merge_visible
operator|&&
name|n_visible
operator|>
literal|1
condition|)
block|{
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|g_list_free
argument_list|(
name|layers
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_image_merge_visible_layers
argument_list|(
name|new_image
argument_list|,
name|context
argument_list|,
name|GIMP_CLIP_TO_IMAGE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|layers
operator|=
name|g_list_prepend
argument_list|(
name|NULL
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|layers
condition|)
block|{
name|gchar
modifier|*
name|basename
init|=
name|file_utils_uri_display_basename
argument_list|(
name|uri
argument_list|)
decl_stmt|;
for|for
control|(
name|list
operator|=
name|layers
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
name|GimpLayer
modifier|*
name|layer
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|item
operator|=
name|gimp_item_convert
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
name|dest_image
argument_list|,
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|layer
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|layers
operator|->
name|next
operator|==
name|NULL
condition|)
block|{
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|,
name|basename
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s - %s"
argument_list|,
name|basename
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
name|list
operator|->
name|data
operator|=
name|item
expr_stmt|;
block|}
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|gimp_document_list_add_uri
argument_list|(
name|GIMP_DOCUMENT_LIST
argument_list|(
name|gimp
operator|->
name|documents
argument_list|)
argument_list|,
name|uri
argument_list|,
name|mime_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|config
operator|->
name|save_document_history
condition|)
name|gimp_recent_list_add_uri
argument_list|(
name|gimp
argument_list|,
name|uri
argument_list|,
name|mime_type
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"Image doesn't contain any layers"
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
block|}
return|return
name|g_list_reverse
argument_list|(
name|layers
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  This function is called for filenames passed on the command-line  *  or from the D-Bus service.  */
end_comment

begin_function
name|gboolean
DECL|function|file_open_from_command_line (Gimp * gimp,const gchar * filename,gboolean as_new)
name|file_open_from_command_line
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|as_new
parameter_list|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* we accept URI or filename */
name|uri
operator|=
name|file_utils_any_to_uri
argument_list|(
name|gimp
argument_list|,
name|filename
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|image
operator|=
name|file_open_with_display
argument_list|(
name|gimp
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|uri
argument_list|,
name|as_new
argument_list|,
operator|&
name|status
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|file_utils_uri_display_name
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|gimp_message
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Opening '%s' failed: %s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"conversion filename -> uri failed: %s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|file_open_sanitize_image (GimpImage * image,gboolean as_new)
name|file_open_sanitize_image
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|as_new
parameter_list|)
block|{
if|if
condition|(
name|as_new
condition|)
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* clear all undo steps */
name|gimp_image_undo_free
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/* make sure that undo is enabled */
while|while
condition|(
name|image
operator|->
name|undo_freeze_count
condition|)
name|gimp_image_undo_thaw
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/* set the image to clean  */
name|gimp_image_clean_all
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/* make sure the entire projection is properly constructed, because    * load plug-ins are not required to call gimp_drawable_update() or    * anything.    */
name|gimp_image_update
argument_list|(
name|image
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|image
operator|->
name|width
argument_list|,
name|image
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/* same for drawable previews */
name|gimp_image_invalidate_layer_previews
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_invalidate_channel_previews
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_open_profile_apply_rgb (GimpImage * image,GimpContext * context,GimpProgress * progress,GimpRunMode run_mode)
name|file_open_profile_apply_rgb
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|)
block|{
name|GimpColorConfig
modifier|*
name|config
init|=
name|image
operator|->
name|gimp
operator|->
name|config
operator|->
name|color_management
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
operator|==
name|GIMP_GRAY
condition|)
return|return;
if|if
condition|(
name|config
operator|->
name|mode
operator|==
name|GIMP_COLOR_MANAGEMENT_OFF
condition|)
return|return;
if|if
condition|(
operator|!
name|plug_in_icc_profile_apply_rgb
argument_list|(
name|image
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|run_mode
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
name|error
operator|->
name|domain
operator|==
name|GIMP_PLUG_IN_ERROR
operator|&&
name|error
operator|->
name|code
operator|==
name|GIMP_PLUG_IN_NOT_FOUND
condition|)
block|{
name|gchar
modifier|*
name|msg
init|=
name|g_strdup_printf
argument_list|(
literal|"%s\n\n%s"
argument_list|,
name|error
operator|->
name|message
argument_list|,
name|_
argument_list|(
literal|"Color management has been disabled. "
literal|"It can be enabled again in the "
literal|"Preferences dialog."
argument_list|)
argument_list|)
decl_stmt|;
name|g_object_set
argument_list|(
name|config
argument_list|,
literal|"mode"
argument_list|,
name|GIMP_COLOR_MANAGEMENT_OFF
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_message
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|progress
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
argument_list|,
name|msg
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|msg
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_message
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|progress
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_open_handle_color_profile (GimpImage * image,GimpContext * context,GimpProgress * progress,GimpRunMode run_mode)
name|file_open_handle_color_profile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|)
block|{
if|if
condition|(
name|gimp_image_parasite_find
argument_list|(
name|image
argument_list|,
literal|"icc-profile"
argument_list|)
condition|)
block|{
switch|switch
condition|(
name|image
operator|->
name|gimp
operator|->
name|config
operator|->
name|color_profile_policy
condition|)
block|{
case|case
name|GIMP_COLOR_PROFILE_POLICY_ASK
case|:
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
name|file_open_profile_apply_rgb
argument_list|(
name|image
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_PROFILE_POLICY_KEEP
case|:
break|break;
case|case
name|GIMP_COLOR_PROFILE_POLICY_CONVERT
case|:
name|file_open_profile_apply_rgb
argument_list|(
name|image
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
block|}
end_function

end_unit

