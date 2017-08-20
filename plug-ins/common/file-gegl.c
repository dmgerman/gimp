begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-gegl.c -- GEGL based file format plug-in  * Copyright (C) 2012 Simon Budig<simon@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-gegl"
end_define

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
DECL|member|save_proc
specifier|const
name|gchar
modifier|*
name|save_proc
decl_stmt|;
DECL|member|save_blurb
specifier|const
name|gchar
modifier|*
name|save_blurb
decl_stmt|;
DECL|member|save_help
specifier|const
name|gchar
modifier|*
name|save_help
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
name|save_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
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
literal|"OpenEXR image"
argument_list|)
block|,
literal|"image/x-exr"
block|,
literal|"exr"
block|,
literal|"0,lelong,20000630"
block|,
comment|/* no EXR loading (implemented in native GIMP plug-in) */
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
literal|"file-exr-save"
block|,
literal|"Saves files in the OpenEXR file format"
block|,
literal|"This procedure saves images in the OpenEXR format, using gegl:save"
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
literal|"Drawable to save"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw-filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|}
decl_stmt|;
name|gint
name|i
decl_stmt|;
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
condition|)
block|{
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
literal|"Simon Budig"
argument_list|,
literal|"Simon Budig"
argument_list|,
literal|"2012"
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
block|}
if|if
condition|(
name|format
operator|->
name|save_proc
condition|)
block|{
name|gimp_install_procedure
argument_list|(
name|format
operator|->
name|save_proc
argument_list|,
name|format
operator|->
name|save_blurb
argument_list|,
name|format
operator|->
name|save_help
argument_list|,
literal|"Simon Budig"
argument_list|,
literal|"Simon Budig"
argument_list|,
literal|"2012"
argument_list|,
name|format
operator|->
name|file_type
argument_list|,
literal|"*"
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
name|gimp_register_file_handler_mime
argument_list|(
name|format
operator|->
name|save_proc
argument_list|,
name|format
operator|->
name|mime_type
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
name|format
operator|->
name|save_proc
argument_list|,
name|format
operator|->
name|extensions
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
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
literal|2
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
name|gint
name|drawable_ID
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
name|save_proc
operator|&&
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|format
operator|->
name|save_proc
argument_list|)
condition|)
block|{
name|GimpExportReturn
name|export
init|=
name|GIMP_EXPORT_CANCEL
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
comment|/*  eventually export the image */
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
literal|"GEGL"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
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
operator|*
name|nreturn_vals
operator|=
literal|1
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
name|GIMP_PDB_CANCEL
expr_stmt|;
return|return;
block|}
break|break;
default|default:
break|break;
block|}
if|if
condition|(
operator|!
name|save_image
argument_list|(
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
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
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
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
name|gegl_exit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|load_image (const gchar * filename,GError ** error)
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
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
name|gint32
name|layer_ID
decl_stmt|;
name|GimpImageType
name|image_type
decl_stmt|;
name|GimpImageBaseType
name|base_type
decl_stmt|;
name|GimpPrecision
name|precision
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|GeglNode
modifier|*
name|graph
decl_stmt|;
name|GeglNode
modifier|*
name|sink
decl_stmt|;
name|GeglNode
modifier|*
name|source
decl_stmt|;
name|GeglBuffer
modifier|*
name|src_buf
init|=
name|NULL
decl_stmt|;
name|GeglBuffer
modifier|*
name|dest_buf
init|=
name|NULL
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
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
name|graph
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|source
operator|=
name|gegl_node_new_child
argument_list|(
name|graph
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:load"
argument_list|,
literal|"path"
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|sink
operator|=
name|gegl_node_new_child
argument_list|(
name|graph
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-sink"
argument_list|,
literal|"buffer"
argument_list|,
operator|&
name|src_buf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|source
argument_list|,
literal|"output"
argument_list|,
name|sink
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_process
argument_list|(
name|sink
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|graph
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|src_buf
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
literal|"Could not open '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|gimp_progress_update
argument_list|(
literal|0.33
argument_list|)
expr_stmt|;
name|width
operator|=
name|gegl_buffer_get_width
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
name|height
operator|=
name|gegl_buffer_get_height
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
name|format
operator|=
name|gegl_buffer_get_format
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|babl_format_is_palette
argument_list|(
name|format
argument_list|)
condition|)
block|{
name|base_type
operator|=
name|GIMP_INDEXED
expr_stmt|;
if|if
condition|(
name|babl_format_has_alpha
argument_list|(
name|format
argument_list|)
condition|)
name|image_type
operator|=
name|GIMP_INDEXEDA_IMAGE
expr_stmt|;
else|else
name|image_type
operator|=
name|GIMP_INDEXED_IMAGE
expr_stmt|;
name|precision
operator|=
name|GIMP_PRECISION_U8_GAMMA
expr_stmt|;
block|}
else|else
block|{
specifier|const
name|Babl
modifier|*
name|model
init|=
name|babl_format_get_model
argument_list|(
name|format
argument_list|)
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|type
init|=
name|babl_format_get_type
argument_list|(
name|format
argument_list|,
literal|0
argument_list|)
decl_stmt|;
name|gboolean
name|linear
init|=
name|TRUE
decl_stmt|;
if|if
condition|(
name|model
operator|==
name|babl_model
argument_list|(
literal|"Y"
argument_list|)
operator|||
name|model
operator|==
name|babl_model
argument_list|(
literal|"Y'"
argument_list|)
operator|||
name|model
operator|==
name|babl_model
argument_list|(
literal|"YA"
argument_list|)
operator|||
name|model
operator|==
name|babl_model
argument_list|(
literal|"Y'A"
argument_list|)
condition|)
block|{
name|base_type
operator|=
name|GIMP_GRAY
expr_stmt|;
if|if
condition|(
name|babl_format_has_alpha
argument_list|(
name|format
argument_list|)
condition|)
name|image_type
operator|=
name|GIMP_GRAYA_IMAGE
expr_stmt|;
else|else
name|image_type
operator|=
name|GIMP_GRAY_IMAGE
expr_stmt|;
if|if
condition|(
name|model
operator|==
name|babl_model
argument_list|(
literal|"Y'"
argument_list|)
operator|||
name|model
operator|==
name|babl_model
argument_list|(
literal|"Y'A"
argument_list|)
condition|)
name|linear
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|base_type
operator|=
name|GIMP_RGB
expr_stmt|;
if|if
condition|(
name|babl_format_has_alpha
argument_list|(
name|format
argument_list|)
condition|)
name|image_type
operator|=
name|GIMP_RGBA_IMAGE
expr_stmt|;
else|else
name|image_type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
if|if
condition|(
name|model
operator|==
name|babl_model
argument_list|(
literal|"R'G'B'"
argument_list|)
operator|||
name|model
operator|==
name|babl_model
argument_list|(
literal|"R'G'B'A"
argument_list|)
condition|)
name|linear
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|linear
condition|)
block|{
if|if
condition|(
name|type
operator|==
name|babl_type
argument_list|(
literal|"u8"
argument_list|)
condition|)
name|precision
operator|=
name|GIMP_PRECISION_U8_LINEAR
expr_stmt|;
elseif|else
if|if
condition|(
name|type
operator|==
name|babl_type
argument_list|(
literal|"u16"
argument_list|)
condition|)
name|precision
operator|=
name|GIMP_PRECISION_U16_LINEAR
expr_stmt|;
elseif|else
if|if
condition|(
name|type
operator|==
name|babl_type
argument_list|(
literal|"u32"
argument_list|)
condition|)
name|precision
operator|=
name|GIMP_PRECISION_U32_LINEAR
expr_stmt|;
elseif|else
if|if
condition|(
name|type
operator|==
name|babl_type
argument_list|(
literal|"half"
argument_list|)
condition|)
name|precision
operator|=
name|GIMP_PRECISION_HALF_LINEAR
expr_stmt|;
else|else
name|precision
operator|=
name|GIMP_PRECISION_FLOAT_LINEAR
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|type
operator|==
name|babl_type
argument_list|(
literal|"u8"
argument_list|)
condition|)
name|precision
operator|=
name|GIMP_PRECISION_U8_GAMMA
expr_stmt|;
elseif|else
if|if
condition|(
name|type
operator|==
name|babl_type
argument_list|(
literal|"u16"
argument_list|)
condition|)
name|precision
operator|=
name|GIMP_PRECISION_U16_GAMMA
expr_stmt|;
elseif|else
if|if
condition|(
name|type
operator|==
name|babl_type
argument_list|(
literal|"u32"
argument_list|)
condition|)
name|precision
operator|=
name|GIMP_PRECISION_U32_GAMMA
expr_stmt|;
elseif|else
if|if
condition|(
name|type
operator|==
name|babl_type
argument_list|(
literal|"half"
argument_list|)
condition|)
name|precision
operator|=
name|GIMP_PRECISION_HALF_GAMMA
expr_stmt|;
else|else
name|precision
operator|=
name|GIMP_PRECISION_FLOAT_GAMMA
expr_stmt|;
block|}
block|}
name|image_ID
operator|=
name|gimp_image_new_with_precision
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|base_type
argument_list|,
name|precision
argument_list|)
expr_stmt|;
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|layer_ID
operator|=
name|gimp_layer_new
argument_list|(
name|image_ID
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|image_type
argument_list|,
literal|100
argument_list|,
name|gimp_get_default_new_layer_mode
argument_list|()
argument_list|)
expr_stmt|;
name|gimp_image_insert_layer
argument_list|(
name|image_ID
argument_list|,
name|layer_ID
argument_list|,
operator|-
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|dest_buf
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|layer_ID
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|0.66
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|src_buf
argument_list|,
name|NULL
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|dest_buf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_buf
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
name|gboolean
DECL|function|save_image (const gchar * filename,gint32 image_ID,gint32 drawable_ID,GError ** error)
name|save_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
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
name|GeglNode
modifier|*
name|graph
decl_stmt|;
name|GeglNode
modifier|*
name|source
decl_stmt|;
name|GeglNode
modifier|*
name|sink
decl_stmt|;
name|GeglBuffer
modifier|*
name|src_buf
decl_stmt|;
name|src_buf
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|graph
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|source
operator|=
name|gegl_node_new_child
argument_list|(
name|graph
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-source"
argument_list|,
literal|"buffer"
argument_list|,
name|src_buf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|sink
operator|=
name|gegl_node_new_child
argument_list|(
name|graph
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:save"
argument_list|,
literal|"path"
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|source
argument_list|,
literal|"output"
argument_list|,
name|sink
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_process
argument_list|(
name|sink
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|graph
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

