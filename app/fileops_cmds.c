begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2000 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
end_comment

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"fileops.h"
end_include

begin_include
include|#
directive|include
file|"fileopsP.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"plug_in.h"
end_include

begin_decl_stmt
DECL|variable|file_load_proc
specifier|static
name|ProcRecord
name|file_load_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|file_save_proc
specifier|static
name|ProcRecord
name|file_save_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|file_load_thumbnail_proc
specifier|static
name|ProcRecord
name|file_load_thumbnail_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|file_save_thumbnail_proc
specifier|static
name|ProcRecord
name|file_save_thumbnail_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|temp_name_proc
specifier|static
name|ProcRecord
name|temp_name_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|register_magic_load_handler_proc
specifier|static
name|ProcRecord
name|register_magic_load_handler_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|register_load_handler_proc
specifier|static
name|ProcRecord
name|register_load_handler_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|register_save_handler_proc
specifier|static
name|ProcRecord
name|register_save_handler_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_fileops_procs (void)
name|register_fileops_procs
parameter_list|(
name|void
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
operator|&
name|file_load_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|file_save_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|file_load_thumbnail_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|file_save_thumbnail_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|temp_name_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|register_magic_load_handler_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|register_load_handler_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|register_save_handler_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|file_load_invoker (Argument * args)
name|file_load_invoker
parameter_list|(
name|Argument
modifier|*
name|args
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
name|file_proc
operator|=
name|file_proc_find
argument_list|(
name|load_procs
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|file_load_proc
argument_list|,
name|FALSE
argument_list|)
return|;
name|proc
operator|=
operator|&
name|file_proc
operator|->
name|db_info
expr_stmt|;
return|return
name|procedural_db_execute
argument_list|(
name|proc
operator|->
name|name
argument_list|,
name|args
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|file_load_inargs
specifier|static
name|ProcArg
name|file_load_inargs
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"The run mode: RUN_INTERACTIVE (0) or RUN_NONINTERACTIVE (1)"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to load"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name entered"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|file_load_outargs
specifier|static
name|ProcArg
name|file_load_outargs
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The output image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|file_load_proc
specifier|static
name|ProcRecord
name|file_load_proc
init|=
block|{
literal|"gimp_file_load"
block|,
literal|"Loads a file by extension."
block|,
literal|"This procedure invokes the correct file load handler according to the file's extension and/or prefix. The name of the file to load is typically a full pathname, and the name entered is what the user actually typed before prepending a directory path. The reason for this is that if the user types http://www.xcf/~gimp/ he wants to fetch a URL, and the full pathname will not look like a URL."
block|,
literal|"Josh MacDonald"
block|,
literal|"Josh MacDonald"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
literal|3
block|,
name|file_load_inargs
block|,
literal|1
block|,
name|file_load_outargs
block|,
block|{
block|{
name|file_load_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|file_save_invoker (Argument * args)
name|file_save_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Argument
modifier|*
name|new_args
decl_stmt|;
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|PlugInProcDef
modifier|*
name|file_proc
decl_stmt|;
name|ProcRecord
modifier|*
name|proc
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|file_proc
operator|=
name|file_proc_find
argument_list|(
name|save_procs
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_pointer
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_proc
condition|)
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|file_save_proc
argument_list|,
name|FALSE
argument_list|)
return|;
name|proc
operator|=
operator|&
name|file_proc
operator|->
name|db_info
expr_stmt|;
name|new_args
operator|=
name|g_new
argument_list|(
name|Argument
argument_list|,
name|proc
operator|->
name|num_args
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|new_args
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|Argument
argument_list|)
operator|*
name|proc
operator|->
name|num_args
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|new_args
argument_list|,
name|args
argument_list|,
sizeof|sizeof
argument_list|(
name|Argument
argument_list|)
operator|*
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
name|proc
operator|->
name|num_args
condition|;
name|i
operator|++
control|)
block|{
name|new_args
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
if|if
condition|(
name|proc
operator|->
name|args
index|[
name|i
index|]
operator|.
name|arg_type
operator|==
name|PDB_STRING
condition|)
name|new_args
index|[
name|i
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|g_strdup
argument_list|(
literal|"\0"
argument_list|)
expr_stmt|;
block|}
name|return_vals
operator|=
name|procedural_db_execute
argument_list|(
name|proc
operator|->
name|name
argument_list|,
name|new_args
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|new_args
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|file_save_inargs
specifier|static
name|ProcArg
name|file_save_inargs
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"The run mode: RUN_INTERACTIVE (0) or RUN_NONINTERACTIVE (1)"
block|}
block|,
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Drawable to save"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|file_save_proc
specifier|static
name|ProcRecord
name|file_save_proc
init|=
block|{
literal|"gimp_file_save"
block|,
literal|"Saves a file by extension."
block|,
literal|"This procedure invokes the correct file save handler according to the file's extension and/or prefix. The name of the file to save is typically a full pathname, and the name entered is what the user actually typed before prepending a directory path. The reason for this is that if the user types http://www.xcf/~gimp/ she wants to fetch a URL, and the full pathname will not look like a URL."
block|,
literal|"Josh MacDonald"
block|,
literal|"Josh MacDonald"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
literal|5
block|,
name|file_save_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|file_save_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|file_load_thumbnail_invoker (Argument * args)
name|file_load_thumbnail_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gint32
name|width
init|=
literal|0
decl_stmt|;
name|gint32
name|height
init|=
literal|0
decl_stmt|;
name|gint32
name|num_bytes
init|=
literal|0
decl_stmt|;
name|guint8
modifier|*
name|thumb_data
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|pname
decl_stmt|;
name|gchar
modifier|*
name|fname
decl_stmt|;
name|gchar
modifier|*
name|tname
decl_stmt|;
name|guchar
modifier|*
name|raw_thumb
decl_stmt|;
name|gchar
modifier|*
name|imginfo
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|filename
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|filename
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|pname
operator|=
name|g_dirname
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|fname
operator|=
name|g_basename
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|tname
operator|=
name|g_strconcat
argument_list|(
name|pname
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
literal|".xvpics"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|fname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pname
argument_list|)
expr_stmt|;
name|raw_thumb
operator|=
name|readXVThumb
argument_list|(
name|tname
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|imginfo
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tname
argument_list|)
expr_stmt|;
if|if
condition|(
name|raw_thumb
condition|)
block|{
name|num_bytes
operator|=
literal|3
operator|*
name|width
operator|*
name|height
expr_stmt|;
name|thumb_data
operator|=
name|g_malloc
argument_list|(
name|num_bytes
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
name|width
operator|*
name|height
condition|;
name|i
operator|++
control|)
block|{
name|thumb_data
index|[
name|i
operator|*
literal|3
index|]
operator|=
operator|(
operator|(
name|raw_thumb
index|[
name|i
index|]
operator|>>
literal|5
operator|)
operator|*
literal|255
operator|)
operator|/
literal|7
expr_stmt|;
name|thumb_data
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
operator|(
operator|(
operator|(
name|raw_thumb
index|[
name|i
index|]
operator|>>
literal|2
operator|)
operator|&
literal|7
operator|)
operator|*
literal|255
operator|)
operator|/
literal|7
expr_stmt|;
name|thumb_data
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
operator|(
operator|(
operator|(
name|raw_thumb
index|[
name|i
index|]
operator|)
operator|&
literal|3
operator|)
operator|*
literal|255
operator|)
operator|/
literal|3
expr_stmt|;
block|}
name|g_free
argument_list|(
name|raw_thumb
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|file_load_thumbnail_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|width
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|height
expr_stmt|;
name|return_args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|num_bytes
expr_stmt|;
name|return_args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|thumb_data
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|file_load_thumbnail_inargs
specifier|static
name|ProcArg
name|file_load_thumbnail_inargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file that owns the thumbnail to load"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|file_load_thumbnail_outargs
specifier|static
name|ProcArg
name|file_load_thumbnail_outargs
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"width"
block|,
literal|"The width of the thumbnail"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"height"
block|,
literal|"The height of the thumbnail"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"thumbnail_data_count"
block|,
literal|"The number of bytes in thumbnail data"
block|}
block|,
block|{
name|PDB_INT8ARRAY
block|,
literal|"thumb_data"
block|,
literal|"The thumbnail data"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|file_load_thumbnail_proc
specifier|static
name|ProcRecord
name|file_load_thumbnail_proc
init|=
block|{
literal|"gimp_file_load_thumbnail"
block|,
literal|"Loads the thumbnail for a file."
block|,
literal|"This procedure tries to load a thumbnail that belongs to the file with the given filename. This name is a full pathname. The returned data is an array of colordepth 3 (RGB), regardless of the image type. Width and height of the thumbnail are also returned. Don't use this function if you need a thumbnail of an already opened image, use gimp_image_thumbnail instead."
block|,
literal|"Adam D. Moss, Sven Neumann"
block|,
literal|"Adam D. Moss, Sven Neumann"
block|,
literal|"1999-2000"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|file_load_thumbnail_inargs
block|,
literal|4
block|,
name|file_load_thumbnail_outargs
block|,
block|{
block|{
name|file_load_thumbnail_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|file_save_thumbnail_invoker (Argument * args)
name|file_save_thumbnail_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|TempBuf
modifier|*
name|thumb
decl_stmt|;
name|gimage
operator|=
name|pdb_id_to_image
argument_list|(
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|filename
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|filename
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|thumb
operator|=
name|make_thumb_tempbuf
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_save_thumbnail
argument_list|(
name|gimage
argument_list|,
name|filename
argument_list|,
name|thumb
argument_list|)
condition|)
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|file_save_thumbnail_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|file_save_thumbnail_inargs
specifier|static
name|ProcArg
name|file_save_thumbnail_inargs
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file the thumbnail belongs to"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|file_save_thumbnail_proc
specifier|static
name|ProcRecord
name|file_save_thumbnail_proc
init|=
block|{
literal|"gimp_file_save_thumbnail"
block|,
literal|"Saves a thumbnail for the given image"
block|,
literal|"This procedure saves a thumbnail in the .xvpics format for the given image. The thumbnail is saved so that it belongs to the file with the given filename. This means you have to save the image under this name first, otherwise this procedure will fail. This procedure may become useful if you want to explicitely save a thumbnail with a file."
block|,
literal|"Josh MacDonald"
block|,
literal|"Josh MacDonald"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
literal|2
block|,
name|file_save_thumbnail_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|file_save_thumbnail_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|temp_name_invoker (Argument * args)
name|temp_name_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gchar
modifier|*
name|extension
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
specifier|static
name|gint
name|id
init|=
literal|0
decl_stmt|;
specifier|static
name|gint
name|pid
decl_stmt|;
name|extension
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|extension
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|id
operator|==
literal|0
condition|)
name|pid
operator|=
name|getpid
argument_list|()
expr_stmt|;
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s"
name|G_DIR_SEPARATOR_S
literal|"gimp_temp.%d%d.%s"
argument_list|,
name|temp_path
argument_list|,
name|pid
argument_list|,
name|id
operator|++
argument_list|,
name|extension
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|temp_name_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|name
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|temp_name_inargs
specifier|static
name|ProcArg
name|temp_name_inargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"extension"
block|,
literal|"The extension the file will have"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|temp_name_outargs
specifier|static
name|ProcArg
name|temp_name_outargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"name"
block|,
literal|"The new temp filename"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|temp_name_proc
specifier|static
name|ProcRecord
name|temp_name_proc
init|=
block|{
literal|"gimp_temp_name"
block|,
literal|"Generates a unique filename."
block|,
literal|"Generates a unique filename using the temp path supplied in the user's gimprc."
block|,
literal|"Josh MacDonald"
block|,
literal|"Josh MacDonald"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|temp_name_inargs
block|,
literal|1
block|,
name|temp_name_outargs
block|,
block|{
block|{
name|temp_name_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|register_magic_load_handler_invoker (Argument * args)
name|register_magic_load_handler_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
modifier|*
name|extensions
decl_stmt|;
name|gchar
modifier|*
name|prefixes
decl_stmt|;
name|gchar
modifier|*
name|magics
decl_stmt|;
name|ProcRecord
modifier|*
name|proc
decl_stmt|;
name|PlugInProcDef
modifier|*
name|file_proc
decl_stmt|;
name|name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|name
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|extensions
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
name|prefixes
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
name|magics
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
name|proc
operator|=
name|procedural_db_lookup
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc
operator|&&
operator|(
operator|(
name|proc
operator|->
name|num_args
operator|<
literal|3
operator|)
operator|||
operator|(
name|proc
operator|->
name|num_values
operator|<
literal|1
operator|)
operator|||
operator|(
name|proc
operator|->
name|args
index|[
literal|0
index|]
operator|.
name|arg_type
operator|!=
name|PDB_INT32
operator|)
operator|||
operator|(
name|proc
operator|->
name|args
index|[
literal|1
index|]
operator|.
name|arg_type
operator|!=
name|PDB_STRING
operator|)
operator|||
operator|(
name|proc
operator|->
name|args
index|[
literal|2
index|]
operator|.
name|arg_type
operator|!=
name|PDB_STRING
operator|)
operator|||
operator|(
name|proc
operator|->
name|values
index|[
literal|0
index|]
operator|.
name|arg_type
operator|!=
name|PDB_IMAGE
operator|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
literal|"load handler \"%s\" does not take the standard load handler args"
argument_list|,
name|name
argument_list|)
expr_stmt|;
goto|goto
name|done
goto|;
block|}
name|file_proc
operator|=
name|plug_in_file_handler
argument_list|(
name|name
argument_list|,
name|extensions
argument_list|,
name|prefixes
argument_list|,
name|magics
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
literal|"attempt to register non-existant load handler \"%s\""
argument_list|,
name|name
argument_list|)
expr_stmt|;
goto|goto
name|done
goto|;
block|}
if|if
condition|(
operator|!
name|g_slist_find
argument_list|(
name|load_procs
argument_list|,
name|file_proc
argument_list|)
condition|)
name|load_procs
operator|=
name|g_slist_prepend
argument_list|(
name|load_procs
argument_list|,
name|file_proc
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
name|done
label|:
empty_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|register_magic_load_handler_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|register_magic_load_handler_inargs
specifier|static
name|ProcArg
name|register_magic_load_handler_inargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"procedure_name"
block|,
literal|"The name of the procedure to be used for loading"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"extensions"
block|,
literal|"comma separated list of extensions this handler can load (i.e. \"jpg,jpeg\")"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"prefixes"
block|,
literal|"comma separated list of prefixes this handler can load (i.e. \"http:,ftp:\")"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"magics"
block|,
literal|"comma separated list of magic file information this handler can load (i.e. \"0,string,GIF\")"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|register_magic_load_handler_proc
specifier|static
name|ProcRecord
name|register_magic_load_handler_proc
init|=
block|{
literal|"gimp_register_magic_load_handler"
block|,
literal|"Registers a file load handler procedure."
block|,
literal|"Registers a procedural database procedure to be called to load files of a particular file format using magic file information."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
literal|4
block|,
name|register_magic_load_handler_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|register_magic_load_handler_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|register_load_handler_invoker (Argument * args)
name|register_load_handler_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
name|Argument
name|argv
index|[
literal|4
index|]
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
name|argv
index|[
name|i
index|]
operator|=
name|args
index|[
name|i
index|]
expr_stmt|;
name|argv
index|[
literal|3
index|]
operator|.
name|arg_type
operator|=
name|PDB_STRING
expr_stmt|;
name|argv
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|NULL
expr_stmt|;
return|return
name|register_magic_load_handler_invoker
argument_list|(
name|argv
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|register_load_handler_inargs
specifier|static
name|ProcArg
name|register_load_handler_inargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"procedure_name"
block|,
literal|"The name of the procedure to be used for loading"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"extensions"
block|,
literal|"comma separated list of extensions this handler can load (i.e. \"jpg,jpeg\")"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"prefixes"
block|,
literal|"comma separated list of prefixes this handler can load (i.e. \"http:,ftp:\")"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|register_load_handler_proc
specifier|static
name|ProcRecord
name|register_load_handler_proc
init|=
block|{
literal|"gimp_register_load_handler"
block|,
literal|"Registers a file load handler procedure."
block|,
literal|"Registers a procedural database procedure to be called to load files of a particular file format."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
literal|3
block|,
name|register_load_handler_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|register_load_handler_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|register_save_handler_invoker (Argument * args)
name|register_save_handler_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
modifier|*
name|extensions
decl_stmt|;
name|gchar
modifier|*
name|prefixes
decl_stmt|;
name|ProcRecord
modifier|*
name|proc
decl_stmt|;
name|PlugInProcDef
modifier|*
name|file_proc
decl_stmt|;
name|name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|name
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|extensions
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
name|prefixes
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
name|proc
operator|=
name|procedural_db_lookup
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc
operator|&&
operator|(
operator|(
name|proc
operator|->
name|num_args
operator|<
literal|5
operator|)
operator|||
operator|(
name|proc
operator|->
name|args
index|[
literal|0
index|]
operator|.
name|arg_type
operator|!=
name|PDB_INT32
operator|)
operator|||
operator|(
name|proc
operator|->
name|args
index|[
literal|1
index|]
operator|.
name|arg_type
operator|!=
name|PDB_IMAGE
operator|)
operator|||
operator|(
name|proc
operator|->
name|args
index|[
literal|2
index|]
operator|.
name|arg_type
operator|!=
name|PDB_DRAWABLE
operator|)
operator|||
operator|(
name|proc
operator|->
name|args
index|[
literal|3
index|]
operator|.
name|arg_type
operator|!=
name|PDB_STRING
operator|)
operator|||
operator|(
name|proc
operator|->
name|args
index|[
literal|4
index|]
operator|.
name|arg_type
operator|!=
name|PDB_STRING
operator|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
literal|"save handler \"%s\" does not take the standard save handler args"
argument_list|,
name|name
argument_list|)
expr_stmt|;
goto|goto
name|done
goto|;
block|}
name|file_proc
operator|=
name|plug_in_file_handler
argument_list|(
name|name
argument_list|,
name|extensions
argument_list|,
name|prefixes
argument_list|,
name|NULL
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
literal|"attempt to register non-existant save handler \"%s\""
argument_list|,
name|name
argument_list|)
expr_stmt|;
goto|goto
name|done
goto|;
block|}
if|if
condition|(
operator|!
name|g_slist_find
argument_list|(
name|save_procs
argument_list|,
name|file_proc
argument_list|)
condition|)
name|save_procs
operator|=
name|g_slist_prepend
argument_list|(
name|save_procs
argument_list|,
name|file_proc
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
name|done
label|:
empty_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|register_save_handler_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|register_save_handler_inargs
specifier|static
name|ProcArg
name|register_save_handler_inargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"procedure_name"
block|,
literal|"The name of the procedure to be used for saving"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"extensions"
block|,
literal|"comma separated list of extensions this handler can save (i.e. \"jpg,jpeg\")"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"prefixes"
block|,
literal|"comma separated list of prefixes this handler can save (i.e. \"http:,ftp:\")"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|register_save_handler_proc
specifier|static
name|ProcRecord
name|register_save_handler_proc
init|=
block|{
literal|"gimp_register_save_handler"
block|,
literal|"Registers a file save handler procedure."
block|,
literal|"Registers a procedural database procedure to be called to save files in a particular file format."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
literal|3
block|,
name|register_save_handler_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|register_save_handler_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

