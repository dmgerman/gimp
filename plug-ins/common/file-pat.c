begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * pat plug-in version 1.01  * Loads/exports version 1 GIMP .pat files, by Tim Newsome<drz@frody.bloke.com>  *  * GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"app/core/gimppattern-header.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|SAVE_PROC
define|#
directive|define
name|SAVE_PROC
value|"file-pat-save"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-pat"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-file-pat"
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

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
name|gboolean
name|save_image
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
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
name|gboolean
name|save_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|description
specifier|static
name|gchar
name|description
index|[
literal|256
index|]
init|=
literal|"GIMP Pattern"
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
name|save_args
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
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Drawable to export"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"uri"
block|,
literal|"The URI of the file to export the image in"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw-uri"
block|,
literal|"The URI of the file to export the image in"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"description"
block|,
literal|"Short description of the pattern"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"Exports Gimp pattern file (.PAT)"
argument_list|,
literal|"New Gimp patterns can be created by exporting them "
literal|"in the appropriate place with this plug-in."
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"GIMP pattern"
argument_list|)
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|save_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|save_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plugin_icon_register
argument_list|(
name|SAVE_PROC
argument_list|,
name|GIMP_ICON_TYPE_ICON_NAME
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
name|GIMP_ICON_PATTERN
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_mime
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"image/x-gimp-pat"
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_uri
argument_list|(
name|SAVE_PROC
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"pat"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
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
literal|2
index|]
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|gint32
name|drawable_ID
decl_stmt|;
name|GimpExportReturn
name|export
init|=
name|GIMP_EXPORT_CANCEL
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gegl_init
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
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
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|SAVE_PROC
argument_list|)
operator|==
literal|0
condition|)
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|gint32
name|orig_image_ID
decl_stmt|;
name|image_ID
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|drawable_ID
operator|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|file
operator|=
name|g_file_new_for_uri
argument_list|(
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|orig_image_ID
operator|=
name|image_ID
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|export
operator|=
name|gimp_export_image
argument_list|(
operator|&
name|image_ID
argument_list|,
operator|&
name|drawable_ID
argument_list|,
literal|"PAT"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
operator||
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
argument_list|)
expr_stmt|;
if|if
condition|(
name|export
operator|==
name|GIMP_EXPORT_CANCEL
condition|)
block|{
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
return|return;
block|}
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
name|SAVE_PROC
argument_list|,
name|description
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_image_get_parasite
argument_list|(
name|orig_image_ID
argument_list|,
literal|"gimp-pattern-name"
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|strncpy
argument_list|(
name|description
argument_list|,
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|MIN
argument_list|(
sizeof|sizeof
argument_list|(
name|description
argument_list|)
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|description
index|[
sizeof|sizeof
argument_list|(
name|description
argument_list|)
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|name
init|=
name|g_path_get_basename
argument_list|(
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|g_str_has_suffix
argument_list|(
name|name
argument_list|,
literal|".pat"
argument_list|)
condition|)
name|name
index|[
name|strlen
argument_list|(
name|name
argument_list|)
operator|-
literal|4
index|]
operator|=
literal|'\0'
expr_stmt|;
if|if
condition|(
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
block|{
name|strncpy
argument_list|(
name|description
argument_list|,
name|name
argument_list|,
sizeof|sizeof
argument_list|(
name|description
argument_list|)
argument_list|)
expr_stmt|;
name|description
index|[
sizeof|sizeof
argument_list|(
name|description
argument_list|)
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
block|}
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
if|if
condition|(
operator|!
name|save_dialog
argument_list|()
condition|)
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparams
operator|!=
literal|6
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|strncpy
argument_list|(
name|description
argument_list|,
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
sizeof|sizeof
argument_list|(
name|description
argument_list|)
argument_list|)
expr_stmt|;
name|description
index|[
sizeof|sizeof
argument_list|(
name|description
argument_list|)
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
if|if
condition|(
name|save_image
argument_list|(
name|file
argument_list|,
name|image_ID
argument_list|,
name|drawable_ID
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_set_data
argument_list|(
name|SAVE_PROC
argument_list|,
name|description
argument_list|,
sizeof|sizeof
argument_list|(
name|description
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
if|if
condition|(
name|export
operator|==
name|GIMP_EXPORT_EXPORT
condition|)
name|gimp_image_delete
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|strlen
argument_list|(
name|description
argument_list|)
condition|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"gimp-pattern-name"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|description
argument_list|)
operator|+
literal|1
argument_list|,
name|description
argument_list|)
expr_stmt|;
name|gimp_image_attach_parasite
argument_list|(
name|orig_image_ID
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_detach_parasite
argument_list|(
name|orig_image_ID
argument_list|,
literal|"gimp-pattern-name"
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
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
name|gboolean
DECL|function|save_image (GFile * file,gint32 image_ID,gint32 drawable_ID,GError ** error)
name|save_image
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GOutputStream
modifier|*
name|output
decl_stmt|;
name|GimpPatternHeader
name|ph
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|file_format
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|line_size
decl_stmt|;
name|gint
name|line
decl_stmt|;
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable_ID
argument_list|)
condition|)
block|{
case|case
name|GIMP_GRAY_IMAGE
case|:
name|file_format
operator|=
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_GRAYA_IMAGE
case|:
name|file_format
operator|=
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RGB_IMAGE
case|:
case|case
name|GIMP_INDEXED_IMAGE
case|:
name|file_format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
name|file_format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_message
argument_list|(
literal|"Unsupported image type: %d\n"
literal|"GIMP Patterns must be GRAY or RGB"
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable_ID
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Exporting '%s'"
argument_list|)
argument_list|,
name|g_file_get_parse_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|output
operator|=
name|G_OUTPUT_STREAM
argument_list|(
name|g_file_replace
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|G_FILE_CREATE_NONE
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|output
condition|)
return|return
name|FALSE
return|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|width
operator|=
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|height
operator|=
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|ph
operator|.
name|header_size
operator|=
name|g_htonl
argument_list|(
sizeof|sizeof
argument_list|(
name|GimpPatternHeader
argument_list|)
operator|+
name|strlen
argument_list|(
name|description
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|ph
operator|.
name|version
operator|=
name|g_htonl
argument_list|(
literal|1
argument_list|)
expr_stmt|;
name|ph
operator|.
name|width
operator|=
name|g_htonl
argument_list|(
name|width
argument_list|)
expr_stmt|;
name|ph
operator|.
name|height
operator|=
name|g_htonl
argument_list|(
name|height
argument_list|)
expr_stmt|;
name|ph
operator|.
name|bytes
operator|=
name|g_htonl
argument_list|(
name|babl_format_get_bytes_per_pixel
argument_list|(
name|file_format
argument_list|)
argument_list|)
expr_stmt|;
name|ph
operator|.
name|magic_number
operator|=
name|g_htonl
argument_list|(
name|GIMP_PATTERN_MAGIC
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_output_stream_write_all
argument_list|(
name|output
argument_list|,
operator|&
name|ph
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpPatternHeader
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|GCancellable
modifier|*
name|cancellable
init|=
name|g_cancellable_new
argument_list|()
decl_stmt|;
name|g_cancellable_cancel
argument_list|(
name|cancellable
argument_list|)
expr_stmt|;
name|g_output_stream_close
argument_list|(
name|output
argument_list|,
name|cancellable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|cancellable
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|output
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
operator|!
name|g_output_stream_write_all
argument_list|(
name|output
argument_list|,
name|description
argument_list|,
name|strlen
argument_list|(
name|description
argument_list|)
operator|+
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|GCancellable
modifier|*
name|cancellable
init|=
name|g_cancellable_new
argument_list|()
decl_stmt|;
name|g_cancellable_cancel
argument_list|(
name|cancellable
argument_list|)
expr_stmt|;
name|g_output_stream_close
argument_list|(
name|output
argument_list|,
name|cancellable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|cancellable
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|output
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|line_size
operator|=
name|width
operator|*
name|babl_format_get_bytes_per_pixel
argument_list|(
name|file_format
argument_list|)
expr_stmt|;
comment|/* this can't overflow because drawable->width is<= GIMP_PATTERN_MAX_SIZE */
name|buf
operator|=
name|g_alloca
argument_list|(
name|line_size
argument_list|)
expr_stmt|;
for|for
control|(
name|line
operator|=
literal|0
init|;
name|line
operator|<
name|height
condition|;
name|line
operator|++
control|)
block|{
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
name|line
argument_list|,
name|width
argument_list|,
literal|1
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|file_format
argument_list|,
name|buf
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_output_stream_write_all
argument_list|(
name|output
argument_list|,
name|buf
argument_list|,
name|line_size
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|GCancellable
modifier|*
name|cancellable
init|=
name|g_cancellable_new
argument_list|()
decl_stmt|;
name|g_cancellable_cancel
argument_list|(
name|cancellable
argument_list|)
expr_stmt|;
name|g_output_stream_close
argument_list|(
name|output
argument_list|,
name|cancellable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|cancellable
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|output
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|line
operator|/
operator|(
name|gdouble
operator|)
name|height
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|output
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|save_dialog (void)
name|save_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|grid
decl_stmt|;
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|dialog
operator|=
name|gimp_export_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Pattern"
argument_list|)
argument_list|,
name|PLUG_IN_BINARY
argument_list|,
name|SAVE_PROC
argument_list|)
expr_stmt|;
comment|/* The main grid */
name|grid
operator|=
name|gtk_grid_new
argument_list|()
expr_stmt|;
name|gtk_grid_set_column_spacing
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gimp_export_dialog_get_content_area
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|,
name|grid
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|grid
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|gtk_entry_set_activates_default
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|description
argument_list|)
expr_stmt|;
name|gimp_grid_attach_aligned
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Description:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|entry
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
if|if
condition|(
name|run
condition|)
block|{
name|strncpy
argument_list|(
name|description
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|)
argument_list|,
sizeof|sizeof
argument_list|(
name|description
argument_list|)
argument_list|)
expr_stmt|;
name|description
index|[
sizeof|sizeof
argument_list|(
name|description
argument_list|)
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

end_unit

