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
DECL|macro|R_OK
define|#
directive|define
name|R_OK
value|4
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
file|"core/gimp.h"
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
file|"core/gimpdocuments.h"
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
file|"undo.h"
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
name|GimpImage
modifier|*
DECL|function|file_open_image (Gimp * gimp,const gchar * uri,const gchar * entered_filename,PlugInProcDef * file_proc,GimpRunMode run_mode,GimpPDBStatusType * status,GError ** error)
name|file_open_image
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|PlugInProcDef
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
name|gint
name|gimage_id
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
name|status
operator|!=
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
name|load_procs
argument_list|,
name|uri
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
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Unknown file type"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
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
literal|0
argument_list|,
literal|0
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
name|access
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
literal|0
argument_list|,
literal|0
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
name|pdb_pointer
operator|=
name|filename
condition|?
name|filename
else|:
operator|(
name|gchar
operator|*
operator|)
name|uri
expr_stmt|;
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
operator|(
name|gchar
operator|*
operator|)
name|entered_filename
expr_stmt|;
name|return_vals
operator|=
name|procedural_db_execute
argument_list|(
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
operator|*
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
name|gimage_id
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|procedural_db_destroy_args
argument_list|(
name|return_vals
argument_list|,
name|proc
operator|->
name|num_values
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|args
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
if|if
condition|(
name|gimage_id
operator|!=
operator|-
literal|1
condition|)
block|{
return|return
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
name|gimage_id
argument_list|)
return|;
block|}
else|else
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
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
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Plug-In could not open image"
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|file_open_with_display (Gimp * gimp,const gchar * uri,GimpPDBStatusType * status,GError ** error)
name|file_open_with_display
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
DECL|function|file_open_with_proc_and_display (Gimp * gimp,const gchar * uri,const gchar * entered_filename,PlugInProcDef * file_proc,GimpPDBStatusType * status,GError ** error)
name|file_open_with_proc_and_display
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|PlugInProcDef
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
name|gimage
decl_stmt|;
name|GError
modifier|*
name|my_error
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
name|status
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|file_open_image
argument_list|(
name|gimp
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
name|my_error
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
comment|/* enable& clear all undo steps */
name|gimp_image_undo_enable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/* set the image to clean  */
name|gimp_image_clean_all
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|gimage
argument_list|,
literal|0x0101
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|imagefile
operator|=
name|gimp_documents_add
argument_list|(
name|gimp
argument_list|,
name|uri
argument_list|)
expr_stmt|;
comment|/* save a thumbnail of every opened image */
name|gimp_imagefile_save_thumbnail
argument_list|(
name|imagefile
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|error
condition|)
block|{
name|g_propagate_error
argument_list|(
name|error
argument_list|,
name|my_error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
literal|"Opening '%s' failed:\n%s"
argument_list|,
name|filename
argument_list|,
name|my_error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|my_error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|gimage
return|;
block|}
end_function

end_unit

