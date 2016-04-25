begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-darktable.c -- raw file format plug-in that uses darktable  * Copyright (C) 2012 Simon Budig<simon@gimp.org>  * Copyright (C) 2016 Tobias Ellinghaus<me@houz.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_typedef
DECL|typedef|FileFormat
typedef|typedef
name|struct
name|_FileFormat
name|FileFormat
typedef|;
end_typedef

begin_struct
DECL|struct|_FileFormat
struct|struct
name|_FileFormat
block|{
DECL|member|file_type
specifier|const
name|gchar
modifier|*
name|file_type
decl_stmt|;
DECL|member|mime_type
specifier|const
name|gchar
modifier|*
name|mime_type
decl_stmt|;
DECL|member|extensions
specifier|const
name|gchar
modifier|*
name|extensions
decl_stmt|;
DECL|member|magic
specifier|const
name|gchar
modifier|*
name|magic
decl_stmt|;
DECL|member|load_proc
specifier|const
name|gchar
modifier|*
name|load_proc
decl_stmt|;
DECL|member|load_blurb
specifier|const
name|gchar
modifier|*
name|load_blurb
decl_stmt|;
DECL|member|load_help
specifier|const
name|gchar
modifier|*
name|load_help
decl_stmt|;
DECL|member|load_thumb_proc
specifier|const
name|gchar
modifier|*
name|load_thumb_proc
decl_stmt|;
DECL|member|load_thumb_blurb
specifier|const
name|gchar
modifier|*
name|load_thumb_blurb
decl_stmt|;
DECL|member|load_thumb_help
specifier|const
name|gchar
modifier|*
name|load_thumb_help
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint32
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint32
name|load_thumbnail_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint
name|thumb_size
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|file_formats
specifier|static
specifier|const
name|FileFormat
name|file_formats
index|[]
init|=
block|{
block|{
name|N_
argument_list|(
literal|"Canon CR2 raw"
argument_list|)
block|,
literal|"image/x-canon-cr2"
block|,
literal|"cr2"
block|,
literal|"0,string,II*\\0\\020\\0\\0\\0CR"
block|,
literal|"file-cr2-load"
block|,
literal|"Load files in the CR2 raw format via darktable"
block|,
literal|"This plug-in loads files in Canon's raw CR2 format by calling darktable."
block|,
literal|"file-cr2-load-thumb"
block|,
literal|"Load thumbnail from a CR2 raw image via darktable"
block|,
literal|"This plug-in loads a thumbnail from Canon's raw CR2 images by calling darktable-cli."
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Nikon NEF raw"
argument_list|)
block|,
literal|" image/x-nikon-nef "
block|,
literal|"nef"
block|,
literal|"0,string,MM\\0*\\0\\0\\0\\010,0,string,II*\\0\\010\\0\\0\\0"
block|,
literal|"file-nef-load"
block|,
literal|"Load files in the NEF raw format via darktable"
block|,
literal|"This plug-in loads files in Nikon's raw NEF format by calling darktable."
block|,
literal|"file-nef-load-thumb"
block|,
literal|"Load thumbnail from a NEF raw image via darktable"
block|,
literal|"This plug-in loads a thumbnail from Nikon's raw NEF images by calling darktable-cli."
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc */
name|NULL
block|,
comment|/* quit_proc */
name|query
block|,
comment|/* query proc */
name|run
block|,
comment|/* run_proc */
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpParamDef
name|load_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"The run mode { RUN-INTERACTIVE (0), RUN-NONINTERACTIVE (1) }"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to load."
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw-filename"
block|,
literal|"The name entered"
block|}
block|,   }
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|load_return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Output image"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|thumb_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to load"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"thumb-size"
block|,
literal|"Preferred thumbnail size"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|thumb_return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Thumbnail image"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"image-width"
block|,
literal|"Width of full-sized image"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"image-height"
block|,
literal|"Height of full-sized image"
block|}
block|}
decl_stmt|;
comment|/* check if darktable is installed    * TODO: allow setting the location of the executable in preferences    */
name|gchar
modifier|*
name|argv
index|[]
init|=
block|{
literal|"darktable"
block|,
literal|"--version"
block|,
name|NULL
block|}
decl_stmt|;
name|gchar
modifier|*
name|darktable_stdout
init|=
name|NULL
decl_stmt|;
name|gboolean
name|have_darktable
init|=
name|FALSE
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|g_spawn_sync
argument_list|(
name|NULL
argument_list|,
name|argv
argument_list|,
name|NULL
argument_list|,
name|G_SPAWN_STDERR_TO_DEV_NULL
operator||
name|G_SPAWN_SEARCH_PATH
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|darktable_stdout
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gint
name|major
decl_stmt|,
name|minor
decl_stmt|,
name|patch
decl_stmt|;
if|if
condition|(
name|sscanf
argument_list|(
name|darktable_stdout
argument_list|,
literal|"this is darktable %d.%d.%d"
argument_list|,
operator|&
name|major
argument_list|,
operator|&
name|minor
argument_list|,
operator|&
name|patch
argument_list|)
operator|==
literal|3
condition|)
block|{
if|if
condition|(
operator|(
operator|(
name|major
operator|==
literal|1
operator|&&
name|minor
operator|>=
literal|7
operator|)
operator|||
name|major
operator|>=
literal|2
operator|)
condition|)
block|{
if|if
condition|(
name|g_strstr_len
argument_list|(
name|darktable_stdout
argument_list|,
operator|-
literal|1
argument_list|,
literal|"Lua support enabled"
argument_list|)
condition|)
block|{
name|have_darktable
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
name|g_free
argument_list|(
name|darktable_stdout
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|have_darktable
condition|)
return|return;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|file_formats
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
specifier|const
name|FileFormat
modifier|*
name|format
init|=
operator|&
name|file_formats
index|[
name|i
index|]
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|format
operator|->
name|load_proc
argument_list|,
name|format
operator|->
name|load_blurb
argument_list|,
name|format
operator|->
name|load_help
argument_list|,
literal|"Tobias Ellinghaus"
argument_list|,
literal|"Tobias Ellinghaus"
argument_list|,
literal|"2016"
argument_list|,
name|format
operator|->
name|file_type
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_return_vals
argument_list|)
argument_list|,
name|load_args
argument_list|,
name|load_return_vals
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_mime
argument_list|(
name|format
operator|->
name|load_proc
argument_list|,
name|format
operator|->
name|mime_type
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
name|format
operator|->
name|load_proc
argument_list|,
name|format
operator|->
name|extensions
argument_list|,
literal|""
argument_list|,
name|format
operator|->
name|magic
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|format
operator|->
name|load_thumb_proc
argument_list|,
name|format
operator|->
name|load_thumb_blurb
argument_list|,
name|format
operator|->
name|load_thumb_help
argument_list|,
literal|"Tobias Ellinghaus"
argument_list|,
literal|"Tobias Ellinghaus"
argument_list|,
literal|"2016"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|thumb_args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|thumb_return_vals
argument_list|)
argument_list|,
name|thumb_args
argument_list|,
name|thumb_return_vals
argument_list|)
expr_stmt|;
name|gimp_register_thumbnail_loader
argument_list|(
name|format
operator|->
name|load_proc
argument_list|,
name|format
operator|->
name|load_thumb_proc
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|6
index|]
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|gint
name|image_ID
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|run_mode
operator|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
comment|/* check if the format passed is actually supported& load */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|file_formats
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
specifier|const
name|FileFormat
modifier|*
name|format
init|=
operator|&
name|file_formats
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
name|format
operator|->
name|load_proc
operator|&&
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|format
operator|->
name|load_proc
argument_list|)
condition|)
block|{
name|image_ID
operator|=
name|load_image
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|run_mode
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
block|{
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_IMAGE
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
operator|=
name|image_ID
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
break|break;
block|}
elseif|else
if|if
condition|(
name|format
operator|->
name|load_thumb_proc
operator|&&
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|format
operator|->
name|load_thumb_proc
argument_list|)
condition|)
block|{
name|gint
name|width
init|=
literal|0
decl_stmt|;
name|gint
name|height
init|=
literal|0
decl_stmt|;
name|image_ID
operator|=
name|load_thumbnail_image
argument_list|(
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
block|{
operator|*
name|nreturn_vals
operator|=
literal|6
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_IMAGE
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
operator|=
name|image_ID
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_INT32
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
name|width
expr_stmt|;
name|values
index|[
literal|3
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_INT32
expr_stmt|;
name|values
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
name|height
expr_stmt|;
name|values
index|[
literal|4
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_INT32
expr_stmt|;
name|values
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
name|values
index|[
literal|5
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_INT32
expr_stmt|;
name|values
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
literal|1
expr_stmt|;
comment|/* num_layers */
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
break|break;
block|}
block|}
if|if
condition|(
name|i
operator|==
name|G_N_ELEMENTS
argument_list|(
name|file_formats
argument_list|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
name|status
operator|!=
name|GIMP_PDB_SUCCESS
operator|&&
name|error
condition|)
block|{
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
operator|=
name|error
operator|->
name|message
expr_stmt|;
block|}
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|load_image (const gchar * filename,GimpRunMode run_mode,GError ** error)
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
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
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
name|GFile
modifier|*
name|lua_file
init|=
name|gimp_data_directory_file
argument_list|(
literal|"file-darktable"
argument_list|,
literal|"export-on-exit.lua"
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|lua_script
init|=
name|g_file_get_path
argument_list|(
name|lua_file
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|lua_quoted
init|=
name|g_shell_quote
argument_list|(
name|lua_script
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|lua_cmd
init|=
name|g_strdup_printf
argument_list|(
literal|"dofile(%s)"
argument_list|,
name|lua_quoted
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|filename_out
init|=
name|gimp_temp_name
argument_list|(
literal|"exr"
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|export_filename
init|=
name|g_strdup_printf
argument_list|(
literal|"lua/export_on_exit/export_filename=%s"
argument_list|,
name|filename_out
argument_list|)
decl_stmt|;
comment|/* linear sRGB for now as GIMP uses that internally in many places anyway */
name|gchar
modifier|*
name|argv
index|[]
init|=
block|{
literal|"darktable"
block|,
literal|"--library"
block|,
literal|":memory:"
block|,
literal|"--luacmd"
block|,
name|lua_cmd
block|,
literal|"--conf"
block|,
literal|"plugins/lighttable/export/icctype=3"
block|,
literal|"--conf"
block|,
name|export_filename
block|,
operator|(
name|gchar
operator|*
operator|)
name|filename
block|,
name|NULL
block|}
decl_stmt|;
name|g_object_unref
argument_list|(
name|lua_file
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lua_script
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lua_quoted
argument_list|)
expr_stmt|;
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Opening '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_spawn_sync
argument_list|(
name|NULL
argument_list|,
name|argv
argument_list|,
name|NULL
argument_list|,
name|G_SPAWN_STDOUT_TO_DEV_NULL
operator||
name|G_SPAWN_STDERR_TO_DEV_NULL
operator||
name|G_SPAWN_SEARCH_PATH
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|image_ID
operator|=
name|gimp_file_load
argument_list|(
name|run_mode
argument_list|,
name|filename_out
argument_list|,
name|filename_out
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_unlink
argument_list|(
name|filename_out
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lua_cmd
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename_out
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|export_filename
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|load_thumbnail_image (const gchar * filename,gint thumb_size,gint * width,gint * height,GError ** error)
name|load_thumbnail_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint
name|thumb_size
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
name|gchar
modifier|*
name|filename_out
init|=
name|gimp_temp_name
argument_list|(
literal|"jpg"
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|size
init|=
name|g_strdup_printf
argument_list|(
literal|"%d"
argument_list|,
name|thumb_size
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|argv
index|[]
init|=
block|{
literal|"darktable-cli"
block|,
operator|(
name|gchar
operator|*
operator|)
name|filename
block|,
name|filename_out
block|,
literal|"--width"
block|,
name|size
block|,
literal|"--height"
block|,
name|size
block|,
literal|"--hq"
block|,
literal|"false"
block|,
literal|"--core"
block|,
literal|"--conf"
block|,
literal|"plugins/lighttable/export/icctype=3"
block|,
name|NULL
block|}
decl_stmt|;
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Opening thumbnail for '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_spawn_sync
argument_list|(
name|NULL
argument_list|,
name|argv
argument_list|,
name|NULL
argument_list|,
name|G_SPAWN_STDOUT_TO_DEV_NULL
operator||
name|G_SPAWN_STDERR_TO_DEV_NULL
operator||
name|G_SPAWN_SEARCH_PATH
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|gimp_progress_update
argument_list|(
literal|0.5
argument_list|)
expr_stmt|;
name|image_ID
operator|=
name|gimp_file_load
argument_list|(
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|filename_out
argument_list|,
name|filename_out
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
block|{
comment|/* is this needed for thumbnails? */
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
name|filename
argument_list|)
expr_stmt|;
operator|*
name|width
operator|=
operator|*
name|height
operator|=
name|thumb_size
expr_stmt|;
comment|// TODO
block|}
block|}
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|g_unlink
argument_list|(
name|filename_out
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename_out
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|size
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

end_unit

