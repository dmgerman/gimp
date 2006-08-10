begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * file-open.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"file-open.h"
end_include

begin_include
include|#
directive|include
file|"file-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimprecentlist.h"
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
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpImage
modifier|*
DECL|function|file_open_image (Gimp * gimp,GimpContext * context,GimpProgress * progress,const gchar * uri,const gchar * entered_filename,GimpPlugInProcedure * file_proc,GimpRunMode run_mode,GimpPDBStatusType * status,const gchar ** mime_type,GError ** error)
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
name|file_utils_find_proc
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
literal|"Plug-In returned SUCCESS but did not "
literal|"return an image"
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
literal|"Plug-In could not open image"
argument_list|)
argument_list|)
expr_stmt|;
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
name|file_utils_find_proc
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
DECL|function|file_open_with_display (Gimp * gimp,GimpContext * context,GimpProgress * progress,const gchar * uri,GimpPDBStatusType * status,GError ** error)
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
DECL|function|file_open_with_proc_and_display (Gimp * gimp,GimpContext * context,GimpProgress * progress,const gchar * uri,const gchar * entered_filename,GimpPlugInProcedure * file_proc,GimpPDBStatusType * status,GError ** error)
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
comment|/*  can only create a thumbnail if the passed uri and the        *  resulting image's uri match.        */
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
name|uri
argument_list|,
name|mime_type
argument_list|)
expr_stmt|;
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
name|GimpLayer
modifier|*
DECL|function|file_open_layer (Gimp * gimp,GimpContext * context,GimpProgress * progress,GimpImage * dest_image,const gchar * uri,GimpRunMode run_mode,GimpPlugInProcedure * file_proc,GimpPDBStatusType * status,GError ** error)
name|file_open_layer
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
name|GimpLayer
modifier|*
name|new_layer
init|=
name|NULL
decl_stmt|;
name|GimpImage
modifier|*
name|new_image
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
name|GimpLayer
modifier|*
name|layer
init|=
name|NULL
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
name|layer
condition|)
name|layer
operator|=
name|list
operator|->
name|data
expr_stmt|;
block|}
block|}
if|if
condition|(
name|n_visible
operator|>
literal|1
condition|)
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
if|if
condition|(
name|layer
condition|)
block|{
name|GimpItem
modifier|*
name|item
init|=
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
decl_stmt|;
if|if
condition|(
name|item
condition|)
block|{
name|new_layer
operator|=
name|GIMP_LAYER
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|new_layer
argument_list|)
argument_list|,
name|file_utils_uri_display_basename
argument_list|(
name|uri
argument_list|)
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
name|uri
argument_list|,
name|mime_type
argument_list|)
expr_stmt|;
block|}
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
literal|"Image doesn't contain any visible layers"
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
name|new_layer
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|file_open_sanitize_image (GimpImage * image)
name|file_open_sanitize_image
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
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
name|gimp_viewable_invalidate_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

