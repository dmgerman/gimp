begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * file-save.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<stdio.h>
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
DECL|macro|W_OK
define|#
directive|define
name|W_OK
value|2
end_define

begin_define
DECL|macro|access (f,p)
define|#
directive|define
name|access
parameter_list|(
name|f
parameter_list|,
name|p
parameter_list|)
value|_access(f,p)
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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimagefile.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc-def.h"
end_include

begin_include
include|#
directive|include
file|"file-save.h"
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpPDBStatusType
DECL|function|file_save (GimpImage * gimage,GimpContext * context,GimpProgress * progress,GimpRunMode run_mode,GError ** error)
name|file_save
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|PlugInProcDef
modifier|*
name|file_proc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|GIMP_PDB_CALLING_ERROR
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
name|GIMP_PDB_CALLING_ERROR
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
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
name|file_proc
operator|=
name|gimp_image_get_save_proc
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|file_save_as
argument_list|(
name|gimage
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
name|FALSE
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpPDBStatusType
DECL|function|file_save_as (GimpImage * gimage,GimpContext * context,GimpProgress * progress,const gchar * uri,const gchar * raw_filename,PlugInProcDef * file_proc,GimpRunMode run_mode,gboolean save_a_copy,GError ** error)
name|file_save_as
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|raw_filename
parameter_list|,
name|PlugInProcDef
modifier|*
name|file_proc
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|gboolean
name|save_a_copy
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
specifier|const
name|ProcRecord
modifier|*
name|proc
decl_stmt|;
name|Argument
modifier|*
name|args
decl_stmt|;
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gchar
modifier|*
name|filename
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|raw_filename_with_ext
decl_stmt|;
name|gchar
modifier|*
name|uri_with_ext
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|GIMP_PDB_CALLING_ERROR
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
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|raw_filename
operator|!=
name|NULL
argument_list|,
name|GIMP_PDB_CALLING_ERROR
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
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
condition|)
return|return
name|GIMP_PDB_EXECUTION_ERROR
return|;
if|if
condition|(
name|strchr
argument_list|(
name|raw_filename
argument_list|,
literal|'.'
argument_list|)
condition|)
block|{
name|raw_filename_with_ext
operator|=
name|g_strdup
argument_list|(
name|raw_filename
argument_list|)
expr_stmt|;
name|uri_with_ext
operator|=
name|g_strdup
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|raw_filename_with_ext
operator|=
name|g_strconcat
argument_list|(
name|raw_filename
argument_list|,
literal|".xcf"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|uri_with_ext
operator|=
name|g_strconcat
argument_list|(
name|uri
argument_list|,
literal|".xcf"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|file_proc
condition|)
name|file_proc
operator|=
name|file_utils_find_proc
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|save_procs
argument_list|,
name|raw_filename_with_ext
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
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
literal|"Unknown file type"
argument_list|)
argument_list|)
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
goto|goto
name|out
goto|;
block|}
name|filename
operator|=
name|file_utils_filename_from_uri
argument_list|(
name|uri_with_ext
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
comment|/* check if we are saving to a file */
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
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
goto|goto
name|out
goto|;
block|}
if|if
condition|(
name|access
argument_list|(
name|filename
argument_list|,
name|W_OK
argument_list|)
operator|!=
literal|0
condition|)
block|{
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
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
goto|goto
name|out
goto|;
block|}
block|}
block|}
comment|/* ref the image, so it can't get deleted during save */
name|g_object_ref
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|proc
operator|=
name|plug_in_proc_def_get_proc
argument_list|(
name|file_proc
argument_list|)
expr_stmt|;
name|args
operator|=
name|g_new0
argument_list|(
name|Argument
argument_list|,
name|proc
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
name|proc
operator|->
name|num_args
condition|;
name|i
operator|++
control|)
name|args
index|[
name|i
index|]
operator|.
name|arg_type
operator|=
name|proc
operator|->
name|args
index|[
name|i
index|]
operator|.
name|arg_type
expr_stmt|;
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|run_mode
expr_stmt|;
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|gimp_image_get_ID
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
operator|(
name|filename
condition|?
name|filename
else|:
name|uri_with_ext
operator|)
expr_stmt|;
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|raw_filename_with_ext
expr_stmt|;
name|return_vals
operator|=
name|procedural_db_execute
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|proc
operator|->
name|name
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|status
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|GimpDocumentList
modifier|*
name|documents
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
if|if
condition|(
name|save_a_copy
condition|)
block|{
comment|/*  remember the "save-a-copy" filename for the next invocation  */
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"gimp-image-save-a-copy"
argument_list|,
name|g_strdup
argument_list|(
name|uri_with_ext
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  reset the "save-a-copy" filename when the image URI changes  */
if|if
condition|(
name|uri_with_ext
operator|&&
name|strcmp
argument_list|(
name|uri_with_ext
argument_list|,
name|gimp_image_get_uri
argument_list|(
name|gimage
argument_list|)
argument_list|)
condition|)
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"gimp-image-save-a-copy"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_set_uri
argument_list|(
name|gimage
argument_list|,
name|uri_with_ext
argument_list|)
expr_stmt|;
name|gimp_image_set_save_proc
argument_list|(
name|gimage
argument_list|,
name|file_proc
argument_list|)
expr_stmt|;
name|gimp_image_clean_all
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
name|documents
operator|=
name|GIMP_DOCUMENT_LIST
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|documents
argument_list|)
expr_stmt|;
name|imagefile
operator|=
name|gimp_document_list_add_uri
argument_list|(
name|documents
argument_list|,
name|uri_with_ext
argument_list|,
name|file_proc
operator|->
name|mime_type
argument_list|)
expr_stmt|;
name|gimp_imagefile_save_thumbnail
argument_list|(
name|imagefile
argument_list|,
name|file_proc
operator|->
name|mime_type
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|gimp_recent_list_add_uri
argument_list|(
name|uri_with_ext
argument_list|,
name|file_proc
operator|->
name|mime_type
argument_list|)
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
literal|"Plug-In could not save image"
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|out
label|:
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|raw_filename_with_ext
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri_with_ext
argument_list|)
expr_stmt|;
return|return
name|status
return|;
block|}
end_function

end_unit

