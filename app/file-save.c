begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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

begin_include
include|#
directive|include
file|<ctype.h>
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

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

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
file|<glib.h>
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

begin_ifndef
ifndef|#
directive|ifndef
name|S_IWUSR
end_ifndef

begin_define
DECL|macro|S_IWUSR
define|#
directive|define
name|S_IWUSR
value|_S_IWRITE
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|S_IRUSR
end_ifndef

begin_define
DECL|macro|S_IRUSR
define|#
directive|define
name|S_IRUSR
value|_S_IREAD
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|S_IWGRP
end_ifndef

begin_define
DECL|macro|S_IWGRP
define|#
directive|define
name|S_IWGRP
value|(_S_IWRITE>>3)
end_define

begin_define
DECL|macro|S_IWOTH
define|#
directive|define
name|S_IWOTH
value|(_S_IWRITE>>6)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|S_IRGRP
end_ifndef

begin_define
DECL|macro|S_IRGRP
define|#
directive|define
name|S_IRGRP
value|(_S_IREAD>>3)
end_define

begin_define
DECL|macro|S_IROTH
define|#
directive|define
name|S_IROTH
value|(_S_IREAD>>6)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|uid_t
define|#
directive|define
name|uid_t
value|gint
end_define

begin_define
DECL|macro|gid_t
define|#
directive|define
name|gid_t
value|gint
end_define

begin_define
DECL|macro|geteuid ()
define|#
directive|define
name|geteuid
parameter_list|()
value|0
end_define

begin_define
DECL|macro|getegid ()
define|#
directive|define
name|getegid
parameter_list|()
value|0
end_define

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
file|<gtk/gtk.h>
end_include

begin_comment
comment|/* EEK */
end_comment

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
file|"core/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdocuments.h"
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
file|"plug_in.h"
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

begin_decl_stmt
DECL|variable|save_procs
name|GSList
modifier|*
name|save_procs
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpPDBStatusType
DECL|function|file_save (GimpImage * gimage,const gchar * filename,const gchar * raw_filename,RunModeType run_mode,gboolean set_filename)
name|file_save
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|raw_filename
parameter_list|,
name|RunModeType
name|run_mode
parameter_list|,
name|gboolean
name|set_filename
parameter_list|)
block|{
name|PlugInProcDef
modifier|*
name|file_proc
decl_stmt|;
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
name|status
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|struct
name|stat
name|statbuf
decl_stmt|;
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
name|file_proc
operator|=
name|gimp_image_get_save_proc
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
name|file_proc
operator|=
name|file_proc_find
argument_list|(
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
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Save failed.\n"
literal|"%s: Unknown file type."
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|GIMP_PDB_CANCEL
return|;
comment|/* inhibits error messages by caller */
block|}
comment|/* check if we are saving to a file */
if|if
condition|(
name|stat
argument_list|(
name|filename
argument_list|,
operator|&
name|statbuf
argument_list|)
operator|==
literal|0
condition|)
block|{
name|uid_t
name|euid
decl_stmt|;
name|gid_t
name|egid
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|statbuf
operator|.
name|st_mode
operator|&
name|S_IFREG
operator|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Save failed.\n"
literal|"%s is not a regular file."
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|GIMP_PDB_CANCEL
return|;
comment|/* inhibits error messages by caller */
block|}
name|euid
operator|=
name|geteuid
argument_list|()
expr_stmt|;
name|egid
operator|=
name|getegid
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
operator|(
operator|(
name|statbuf
operator|.
name|st_mode
operator|&
name|S_IWUSR
operator|)
operator|||
operator|(
operator|(
name|statbuf
operator|.
name|st_mode
operator|&
name|S_IWGRP
operator|)
operator|&&
operator|(
name|statbuf
operator|.
name|st_uid
operator|!=
name|euid
operator|)
operator|)
operator|||
operator|(
operator|(
name|statbuf
operator|.
name|st_mode
operator|&
name|S_IWOTH
operator|)
operator|&&
operator|(
name|statbuf
operator|.
name|st_uid
operator|!=
name|euid
operator|)
operator|&&
operator|(
name|statbuf
operator|.
name|st_gid
operator|!=
name|egid
operator|)
operator|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Save failed.\n"
literal|"%s: Permission denied."
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|GIMP_PDB_CANCEL
return|;
comment|/* inhibits error messages by caller */
block|}
block|}
comment|/* ref the image, so it can't get deleted during save */
name|g_object_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|proc
operator|=
operator|&
name|file_proc
operator|->
name|db_info
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
name|gimp_drawable_get_ID
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gimage
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
name|gpointer
operator|)
name|filename
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
comment|/*  set this image to clean  */
name|gimp_image_clean_all
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_documents_add
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|filename
argument_list|)
expr_stmt|;
comment|/*  use the same plug-in for this image next time  */
comment|/* DISABLED - gets stuck on first saved format... needs 	 attention --Adam */
comment|/* gimage_set_save_proc(gimage, file_proc); */
comment|/* Write a thumbnail for the saved image, where appropriate */
switch|switch
condition|(
name|gimage
operator|->
name|gimp
operator|->
name|config
operator|->
name|thumbnail_mode
condition|)
block|{
case|case
literal|0
case|:
break|break;
default|default:
block|{
name|TempBuf
modifier|*
name|tempbuf
decl_stmt|;
name|tempbuf
operator|=
name|make_thumb_tempbuf
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|file_save_thumbnail
argument_list|(
name|gimage
argument_list|,
name|filename
argument_list|,
name|tempbuf
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|set_filename
condition|)
block|{
comment|/*  set the image title  */
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
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
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|status
return|;
block|}
end_function

begin_comment
comment|/* Set "gimage"s save handler to "save_proc", then save the image.    * Hide the dialog if all went well, otherwise make the user knows an  * error happened and leave the dialog up.  Make sure it's sensitive.  */
end_comment

begin_function
name|gboolean
DECL|function|file_save_with_proc (GimpImage * gimage,const gchar * full_filename,const gchar * raw_filename,PlugInProcDef * save_proc,gboolean set_filename)
name|file_save_with_proc
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|full_filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|raw_filename
parameter_list|,
name|PlugInProcDef
modifier|*
name|save_proc
parameter_list|,
name|gboolean
name|set_filename
parameter_list|)
block|{
name|gint
name|status
init|=
name|GIMP_PDB_EXECUTION_ERROR
decl_stmt|;
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|gimage
operator|!=
name|NULL
condition|)
block|{
name|gimp_image_set_save_proc
argument_list|(
name|gimage
argument_list|,
name|save_proc
argument_list|)
expr_stmt|;
name|status
operator|=
name|file_save
argument_list|(
name|gimage
argument_list|,
name|full_filename
argument_list|,
name|raw_filename
argument_list|,
name|RUN_INTERACTIVE
argument_list|,
name|set_filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/* If there was an error but file_save() didn't print an error    * message, then we'd better.    */
if|if
condition|(
name|status
operator|!=
name|GIMP_PDB_SUCCESS
operator|&&
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Save failed.\n%s"
argument_list|)
argument_list|,
name|full_filename
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

