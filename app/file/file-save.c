begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"plug-in/plug-in-proc.h"
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
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpPDBStatusType
DECL|function|file_save (GimpImage * gimage,GimpRunMode run_mode,GError ** error)
name|file_save
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
DECL|function|file_save_as (GimpImage * gimage,const gchar * uri,const gchar * raw_filename,PlugInProcDef * file_proc,GimpRunMode run_mode,gboolean set_uri_and_proc,GError ** error)
name|file_save_as
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|set_uri_and_proc
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
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
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
operator|==
name|NULL
condition|)
return|return
name|GIMP_PDB_EXECUTION_ERROR
return|;
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
name|raw_filename
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
return|return
name|GIMP_PDB_CALLING_ERROR
return|;
block|}
name|filename
operator|=
name|g_filename_from_uri
argument_list|(
name|uri
argument_list|,
name|NULL
argument_list|,
name|NULL
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
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|GIMP_PDB_EXECUTION_ERROR
return|;
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
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|GIMP_PDB_EXECUTION_ERROR
return|;
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
call|(
name|gpointer
call|)
argument_list|(
name|filename
condition|?
name|filename
else|:
name|uri
argument_list|)
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
operator|(
name|gpointer
operator|)
name|raw_filename
expr_stmt|;
name|return_vals
operator|=
name|procedural_db_execute
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|proc
operator|->
name|name
argument_list|,
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
condition|)
name|g_free
argument_list|(
name|filename
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
comment|/*  set this image to clean  */
name|gimp_image_clean_all
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
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
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|set_uri_and_proc
condition|)
block|{
name|gimp_image_set_uri
argument_list|(
name|gimage
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|gimp_image_set_save_proc
argument_list|(
name|gimage
argument_list|,
name|file_proc
argument_list|)
expr_stmt|;
block|}
comment|/* Write a thumbnail for the saved image, where appropriate */
if|if
condition|(
name|gimage
operator|->
name|gimp
operator|->
name|config
operator|->
name|thumbnail_size
operator|!=
name|GIMP_THUMBNAIL_SIZE_NONE
condition|)
block|{
if|if
condition|(
name|set_uri_and_proc
condition|)
block|{
name|gimp_imagefile_save_thumbnail
argument_list|(
name|imagefile
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|saved_uri
decl_stmt|;
name|saved_uri
operator|=
name|GIMP_OBJECT
argument_list|(
name|gimage
argument_list|)
operator|->
name|name
expr_stmt|;
name|GIMP_OBJECT
argument_list|(
name|gimage
argument_list|)
operator|->
name|name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|uri
expr_stmt|;
name|gimp_imagefile_save_thumbnail
argument_list|(
name|imagefile
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|GIMP_OBJECT
argument_list|(
name|gimage
argument_list|)
operator|->
name|name
operator|=
name|saved_uri
expr_stmt|;
block|}
block|}
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
return|return
name|status
return|;
block|}
end_function

end_unit

