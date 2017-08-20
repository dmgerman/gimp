begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Alias|Wavefront pix/matte image reading and writing code  * Copyright (C) 1997 Mike Taylor  * (email: mtaylor@aw.sgi.com, WWW: http://reality.sgi.com/mtaylor)  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  */
end_comment

begin_comment
comment|/* This plug-in was written using the online documentation from  * Alias|Wavefront Inc's PowerAnimator product.  *  * Bug reports or suggestions should be e-mailed to mtaylor@aw.sgi.com  */
end_comment

begin_comment
comment|/* Event history:  * V 1.0, MT, 02-Jul-97: initial version of plug-in  * V 1.1, MT, 04-Dec-97: added .als file extension  */
end_comment

begin_comment
comment|/* Features  *  - loads and exports  *    - 24-bit (.pix)  *    - 8-bit (.matte, .alpha, or .mask) images  *  * NOTE: pix and matte files do not support alpha channels or indexed  *       color, so neither does this plug-in  */
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
file|<string.h>
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
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-pix-load"
end_define

begin_define
DECL|macro|SAVE_PROC
define|#
directive|define
name|SAVE_PROC
value|"file-pix-save"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-pix"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-file-pix"
end_define

begin_comment
comment|/* #define PIX_DEBUG */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|PIX_DEBUG
end_ifdef

begin_define
DECL|macro|PIX_DEBUG_PRINT (a,b)
define|#
directive|define
name|PIX_DEBUG_PRINT
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|g_printerr (a,b)
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|PIX_DEBUG_PRINT (a,b)
define|#
directive|define
name|PIX_DEBUG_PRINT
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/**************  * Prototypes *  **************/
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
name|gint32
name|load_image
parameter_list|(
name|GFile
modifier|*
name|file
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
name|get_short
parameter_list|(
name|GInputStream
modifier|*
name|input
parameter_list|,
name|guint16
modifier|*
name|value
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
name|put_short
parameter_list|(
name|GOutputStream
modifier|*
name|output
parameter_list|,
name|guint16
name|value
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/******************  * Implementation *  ******************/
end_comment

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
comment|/*    * Description:    *     Register the services provided by this plug-in    */
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
literal|"The name of the file to load"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw-filename"
block|,
literal|"The name entered"
block|}
block|}
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
literal|"Drawable to export"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to export the image in"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw-filename"
block|,
literal|"The name of the file to export the image in"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"loads files of the Alias|Wavefront Pix file format"
argument_list|,
literal|"loads files of the Alias|Wavefront Pix file format"
argument_list|,
literal|"Michael Taylor"
argument_list|,
literal|"Michael Taylor"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"Alias Pix image"
argument_list|)
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
name|gimp_register_file_handler_uri
argument_list|(
name|LOAD_PROC
argument_list|)
expr_stmt|;
name|gimp_register_load_handler
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"pix,matte,mask,alpha,als"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"export file in the Alias|Wavefront pix/matte file format"
argument_list|,
literal|"export file in the Alias|Wavefront pix/matte file format"
argument_list|,
literal|"Michael Taylor"
argument_list|,
literal|"Michael Taylor"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"Alias Pix image"
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
name|gimp_register_file_handler_uri
argument_list|(
name|SAVE_PROC
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"pix,matte,mask,alpha,als"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  *  Description:  *      perform registered plug-in function  *  *  Arguments:  *      name         - name of the function to perform  *      nparams      - number of parameters passed to the function  *      param        - parameters passed to the function  *      nreturn_vals - number of parameters returned by the function  *      return_vals  - parameters returned by the function  */
end_comment

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
name|LOAD_PROC
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/* Perform the image load */
name|image_ID
operator|=
name|load_image
argument_list|(
name|g_file_new_for_uri
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
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
comment|/* The image load was successful */
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
comment|/* The image load falied */
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
elseif|else
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
literal|"PIX"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
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
operator|!
name|save_image
argument_list|(
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

begin_comment
comment|/*  * Description:  *     Reads a 16-bit integer from a file in such a way that the machine's  *     byte order should not matter.  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|get_short (GInputStream * input,guint16 * value,GError ** error)
name|get_short
parameter_list|(
name|GInputStream
modifier|*
name|input
parameter_list|,
name|guint16
modifier|*
name|value
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|guchar
name|buf
index|[
literal|2
index|]
decl_stmt|;
name|gsize
name|bytes_read
decl_stmt|;
if|if
condition|(
operator|!
name|g_input_stream_read_all
argument_list|(
name|input
argument_list|,
name|buf
argument_list|,
literal|2
argument_list|,
operator|&
name|bytes_read
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
operator|||
name|bytes_read
operator|!=
literal|2
condition|)
block|{
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|value
condition|)
operator|*
name|value
operator|=
operator|(
name|buf
index|[
literal|0
index|]
operator|<<
literal|8
operator|)
operator|+
name|buf
index|[
literal|1
index|]
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  * Description:  *     Writes a 16-bit integer to a file in such a way that the machine's  *     byte order should not matter.  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|put_short (GOutputStream * output,guint16 value,GError ** error)
name|put_short
parameter_list|(
name|GOutputStream
modifier|*
name|output
parameter_list|,
name|guint16
name|value
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|guchar
name|buf
index|[
literal|2
index|]
decl_stmt|;
name|buf
index|[
literal|0
index|]
operator|=
operator|(
name|value
operator|>>
literal|8
operator|)
operator|&
literal|0xFF
expr_stmt|;
name|buf
index|[
literal|1
index|]
operator|=
name|value
operator|&
literal|0xFF
expr_stmt|;
return|return
name|g_output_stream_write_all
argument_list|(
name|output
argument_list|,
name|buf
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  *  Description:  *      load the given image into gimp  *  *  Arguments:  *      filename      - name on the file to read  *  *  Return Value:  *      Image id for the loaded image  *  */
end_comment

begin_function
specifier|static
name|gint32
DECL|function|load_image (GFile * file,GError ** error)
name|load_image
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GInputStream
modifier|*
name|input
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GimpImageBaseType
name|imgtype
decl_stmt|;
name|GimpImageType
name|gdtype
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|guchar
modifier|*
name|dest_base
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|gint32
name|layer_ID
decl_stmt|;
name|gushort
name|width
decl_stmt|,
name|height
decl_stmt|,
name|depth
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|tile_height
decl_stmt|,
name|row
decl_stmt|;
name|PIX_DEBUG_PRINT
argument_list|(
literal|"Opening file: %s\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Opening '%s'"
argument_list|)
argument_list|,
name|g_file_get_parse_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|input
operator|=
name|G_INPUT_STREAM
argument_list|(
name|g_file_read
argument_list|(
name|file
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
name|input
condition|)
return|return
operator|-
literal|1
return|;
comment|/* Read header information */
if|if
condition|(
operator|!
name|get_short
argument_list|(
name|input
argument_list|,
operator|&
name|width
argument_list|,
name|error
argument_list|)
operator|||
operator|!
name|get_short
argument_list|(
name|input
argument_list|,
operator|&
name|height
argument_list|,
name|error
argument_list|)
operator|||
operator|!
name|get_short
argument_list|(
name|input
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
operator|||
comment|/* Discard obsolete field */
operator|!
name|get_short
argument_list|(
name|input
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
operator|||
comment|/* Discard obsolete field */
operator|!
name|get_short
argument_list|(
name|input
argument_list|,
operator|&
name|depth
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|input
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|PIX_DEBUG_PRINT
argument_list|(
literal|"Width %hu\n"
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|PIX_DEBUG_PRINT
argument_list|(
literal|"Height %hu\n"
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|depth
operator|==
literal|8
condition|)
block|{
comment|/* Loading a matte file */
name|imgtype
operator|=
name|GIMP_GRAY
expr_stmt|;
name|gdtype
operator|=
name|GIMP_GRAY_IMAGE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|depth
operator|==
literal|24
condition|)
block|{
comment|/* Loading an RGB file */
name|imgtype
operator|=
name|GIMP_RGB
expr_stmt|;
name|gdtype
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
block|}
else|else
block|{
comment|/* Header is invalid */
name|g_object_unref
argument_list|(
name|input
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|image_ID
operator|=
name|gimp_image_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|imgtype
argument_list|)
expr_stmt|;
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
name|g_file_get_uri
argument_list|(
name|file
argument_list|)
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
name|gdtype
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
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|layer_ID
argument_list|)
expr_stmt|;
name|tile_height
operator|=
name|gimp_tile_height
argument_list|()
expr_stmt|;
if|if
condition|(
name|depth
operator|==
literal|24
condition|)
block|{
comment|/* Read a 24-bit Pix image */
name|dest_base
operator|=
name|dest
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
literal|3
operator|*
name|width
operator|*
name|tile_height
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
name|height
condition|;
control|)
block|{
for|for
control|(
name|dest
operator|=
name|dest_base
operator|,
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|tile_height
operator|&&
name|i
operator|<
name|height
condition|;
name|i
operator|++
operator|,
name|row
operator|++
control|)
block|{
name|guchar
name|record
index|[
literal|4
index|]
decl_stmt|;
name|gsize
name|bytes_read
decl_stmt|;
name|guchar
name|count
decl_stmt|;
comment|/* Read a row of the image */
name|j
operator|=
literal|0
expr_stmt|;
while|while
condition|(
name|j
operator|<
name|width
condition|)
block|{
if|if
condition|(
operator|!
name|g_input_stream_read_all
argument_list|(
name|input
argument_list|,
name|record
argument_list|,
literal|4
argument_list|,
operator|&
name|bytes_read
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
operator|||
name|bytes_read
operator|!=
literal|4
condition|)
break|break;
for|for
control|(
name|count
operator|=
literal|0
init|;
name|count
operator|<
name|record
index|[
literal|0
index|]
condition|;
operator|++
name|count
control|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|record
index|[
literal|3
index|]
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|record
index|[
literal|2
index|]
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|record
index|[
literal|1
index|]
expr_stmt|;
name|dest
operator|+=
literal|3
expr_stmt|;
name|j
operator|++
expr_stmt|;
if|if
condition|(
name|j
operator|>=
name|width
condition|)
break|break;
block|}
block|}
block|}
name|gegl_buffer_set
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
name|i
operator|-
name|row
argument_list|,
name|width
argument_list|,
name|row
argument_list|)
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|dest_base
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|i
operator|/
operator|(
name|double
operator|)
name|height
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|dest_base
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Read an 8-bit Matte image */
name|dest_base
operator|=
name|dest
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|tile_height
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
name|height
condition|;
control|)
block|{
for|for
control|(
name|dest
operator|=
name|dest_base
operator|,
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|tile_height
operator|&&
name|i
operator|<
name|height
condition|;
name|i
operator|++
operator|,
name|row
operator|++
control|)
block|{
name|guchar
name|record
index|[
literal|2
index|]
decl_stmt|;
name|gsize
name|bytes_read
decl_stmt|;
name|guchar
name|count
decl_stmt|;
comment|/* Read a row of the image */
name|j
operator|=
literal|0
expr_stmt|;
while|while
condition|(
name|j
operator|<
name|width
condition|)
block|{
if|if
condition|(
operator|!
name|g_input_stream_read_all
argument_list|(
name|input
argument_list|,
name|record
argument_list|,
literal|2
argument_list|,
operator|&
name|bytes_read
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
operator|||
name|bytes_read
operator|!=
literal|2
condition|)
break|break;
for|for
control|(
name|count
operator|=
literal|0
init|;
name|count
operator|<
name|record
index|[
literal|0
index|]
condition|;
operator|++
name|count
control|)
block|{
name|dest
index|[
name|j
index|]
operator|=
name|record
index|[
literal|1
index|]
expr_stmt|;
name|j
operator|++
expr_stmt|;
if|if
condition|(
name|j
operator|>=
name|width
condition|)
break|break;
block|}
block|}
name|dest
operator|+=
name|width
expr_stmt|;
block|}
name|gegl_buffer_set
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
name|i
operator|-
name|row
argument_list|,
name|width
argument_list|,
name|row
argument_list|)
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|dest_base
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|i
operator|/
operator|(
name|double
operator|)
name|height
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|dest_base
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
name|input
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

begin_comment
comment|/*  *  Description:  *      save the given file out as an alias pix or matte file  *  *  Arguments:  *      filename    - name of file to save to  *      image_ID    - ID of image to save  *      drawable_ID - current drawable  */
end_comment

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
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|depth
decl_stmt|,
name|i
decl_stmt|,
name|j
decl_stmt|,
name|row
decl_stmt|,
name|tile_height
decl_stmt|,
name|rectHeight
decl_stmt|;
name|gboolean
name|savingColor
init|=
name|TRUE
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|src_base
decl_stmt|;
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
comment|/* Get info about image */
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
name|savingColor
operator|=
operator|!
name|gimp_drawable_is_gray
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|savingColor
condition|)
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
expr_stmt|;
else|else
name|format
operator|=
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
expr_stmt|;
name|depth
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
expr_stmt|;
comment|/* Write the image header */
name|PIX_DEBUG_PRINT
argument_list|(
literal|"Width %hu\n"
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|PIX_DEBUG_PRINT
argument_list|(
literal|"Height %hu\n"
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|put_short
argument_list|(
name|output
argument_list|,
name|width
argument_list|,
name|error
argument_list|)
operator|||
operator|!
name|put_short
argument_list|(
name|output
argument_list|,
name|height
argument_list|,
name|error
argument_list|)
operator|||
operator|!
name|put_short
argument_list|(
name|output
argument_list|,
literal|0
argument_list|,
name|error
argument_list|)
operator|||
operator|!
name|put_short
argument_list|(
name|output
argument_list|,
literal|0
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|output
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|tile_height
operator|=
name|gimp_tile_height
argument_list|()
expr_stmt|;
name|src_base
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|tile_height
operator|*
name|width
operator|*
name|depth
argument_list|)
expr_stmt|;
if|if
condition|(
name|savingColor
condition|)
block|{
comment|/* Writing a 24-bit Pix image */
if|if
condition|(
operator|!
name|put_short
argument_list|(
name|output
argument_list|,
literal|24
argument_list|,
name|error
argument_list|)
condition|)
goto|goto
name|fail
goto|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|height
condition|;
control|)
block|{
name|rectHeight
operator|=
operator|(
name|tile_height
operator|<
operator|(
name|height
operator|-
name|i
operator|)
operator|)
condition|?
name|tile_height
else|:
operator|(
name|height
operator|-
name|i
operator|)
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
name|i
argument_list|,
name|width
argument_list|,
name|rectHeight
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|src_base
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
for|for
control|(
name|src
operator|=
name|src_base
operator|,
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|tile_height
operator|&&
name|i
operator|<
name|height
condition|;
name|i
operator|+=
literal|1
operator|,
name|row
operator|+=
literal|1
control|)
block|{
comment|/* Write a row of the image */
name|guchar
name|record
index|[
literal|4
index|]
decl_stmt|;
name|record
index|[
literal|0
index|]
operator|=
literal|1
expr_stmt|;
name|record
index|[
literal|3
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
name|record
index|[
literal|2
index|]
operator|=
name|src
index|[
literal|1
index|]
expr_stmt|;
name|record
index|[
literal|1
index|]
operator|=
name|src
index|[
literal|2
index|]
expr_stmt|;
name|src
operator|+=
name|depth
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|1
init|;
name|j
operator|<
name|width
condition|;
operator|++
name|j
control|)
block|{
if|if
condition|(
operator|(
name|record
index|[
literal|3
index|]
operator|!=
name|src
index|[
literal|0
index|]
operator|)
operator|||
operator|(
name|record
index|[
literal|2
index|]
operator|!=
name|src
index|[
literal|1
index|]
operator|)
operator|||
operator|(
name|record
index|[
literal|1
index|]
operator|!=
name|src
index|[
literal|2
index|]
operator|)
operator|||
operator|(
name|record
index|[
literal|0
index|]
operator|==
literal|255
operator|)
condition|)
block|{
comment|/* Write current RLE record and start a new one */
if|if
condition|(
operator|!
name|g_output_stream_write_all
argument_list|(
name|output
argument_list|,
name|record
argument_list|,
literal|4
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
block|{
goto|goto
name|fail
goto|;
block|}
name|record
index|[
literal|0
index|]
operator|=
literal|1
expr_stmt|;
name|record
index|[
literal|3
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
name|record
index|[
literal|2
index|]
operator|=
name|src
index|[
literal|1
index|]
expr_stmt|;
name|record
index|[
literal|1
index|]
operator|=
name|src
index|[
literal|2
index|]
expr_stmt|;
block|}
else|else
block|{
comment|/* increment run length in current record */
name|record
index|[
literal|0
index|]
operator|++
expr_stmt|;
block|}
name|src
operator|+=
name|depth
expr_stmt|;
block|}
comment|/* Write last record in row */
if|if
condition|(
operator|!
name|g_output_stream_write_all
argument_list|(
name|output
argument_list|,
name|record
argument_list|,
literal|4
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
block|{
goto|goto
name|fail
goto|;
block|}
block|}
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|i
operator|/
operator|(
name|double
operator|)
name|height
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/* Writing a 8-bit Matte (Mask) image */
if|if
condition|(
operator|!
name|put_short
argument_list|(
name|output
argument_list|,
literal|8
argument_list|,
name|error
argument_list|)
condition|)
goto|goto
name|fail
goto|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|height
condition|;
control|)
block|{
name|rectHeight
operator|=
operator|(
name|tile_height
operator|<
operator|(
name|height
operator|-
name|i
operator|)
operator|)
condition|?
name|tile_height
else|:
operator|(
name|height
operator|-
name|i
operator|)
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
name|i
argument_list|,
name|width
argument_list|,
name|rectHeight
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|src_base
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
for|for
control|(
name|src
operator|=
name|src_base
operator|,
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|tile_height
operator|&&
name|i
operator|<
name|height
condition|;
name|i
operator|+=
literal|1
operator|,
name|row
operator|+=
literal|1
control|)
block|{
comment|/* Write a row of the image */
name|guchar
name|record
index|[
literal|2
index|]
decl_stmt|;
name|record
index|[
literal|0
index|]
operator|=
literal|1
expr_stmt|;
name|record
index|[
literal|1
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
name|src
operator|+=
name|depth
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|1
init|;
name|j
operator|<
name|width
condition|;
operator|++
name|j
control|)
block|{
if|if
condition|(
operator|(
name|record
index|[
literal|1
index|]
operator|!=
name|src
index|[
literal|0
index|]
operator|)
operator|||
operator|(
name|record
index|[
literal|0
index|]
operator|==
literal|255
operator|)
condition|)
block|{
comment|/* Write current RLE record and start a new one */
if|if
condition|(
operator|!
name|g_output_stream_write_all
argument_list|(
name|output
argument_list|,
name|record
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
block|{
goto|goto
name|fail
goto|;
block|}
name|record
index|[
literal|0
index|]
operator|=
literal|1
expr_stmt|;
name|record
index|[
literal|1
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
block|}
else|else
block|{
comment|/* increment run length in current record */
name|record
index|[
literal|0
index|]
operator|++
expr_stmt|;
block|}
name|src
operator|+=
name|depth
expr_stmt|;
block|}
comment|/* Write last record in row */
if|if
condition|(
operator|!
name|g_output_stream_write_all
argument_list|(
name|output
argument_list|,
name|record
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
block|{
goto|goto
name|fail
goto|;
block|}
block|}
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|i
operator|/
operator|(
name|double
operator|)
name|height
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|src_base
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|output
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
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
name|fail
label|:
name|g_free
argument_list|(
name|src_base
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|output
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit

