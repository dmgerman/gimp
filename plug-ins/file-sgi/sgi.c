begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * SGI image file plug-in for GIMP.  *  * Copyright 1997-1998 Michael Sweet (mike@easysw.com)  *  * This program is free software: you can redistribute it and/or modify it  * under the terms of the GNU General Public License as published by the Free  * Software Foundation; either version 3 of the License, or (at your option)  * any later version.  *  * This program is distributed in the hope that it will be useful, but  * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License  * for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  * Contents:  *  *   main()                      - Main entry - just call gimp_main()...  *   query()                     - Respond to a plug-in query...  *   run()                       - Run the plug-in...  *   load_image()                - Load a PNG image into a new image window.  *   save_image()                - Save the specified image to a PNG file.  *   save_ok_callback()          - Destroy the save dialog and save the image.  *   save_dialog()               - Pop up the save dialog.  *  */
end_comment

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
file|"sgi-lib.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/*  * Constants...  */
end_comment

begin_define
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-sgi-load"
end_define

begin_define
DECL|macro|SAVE_PROC
define|#
directive|define
name|SAVE_PROC
value|"file-sgi-save"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-sgi"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-file-sgi"
end_define

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|"1.1.1 - 17 May 1998"
end_define

begin_comment
comment|/*  * Local functions...  */
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
name|gint
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

begin_function_decl
specifier|static
name|gboolean
name|save_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * Globals...  */
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

begin_decl_stmt
DECL|variable|compression
specifier|static
name|gint
name|compression
init|=
name|SGI_COMP_RLE
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
literal|"The name of the file to load"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw-filename"
block|,
literal|"The name of the file to load"
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
block|,   }
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
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"compression"
block|,
literal|"Compression level (0 = none, 1 = RLE, 2 = ARLE)"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"Loads files in SGI image file format"
argument_list|,
literal|"This plug-in loads SGI image files."
argument_list|,
literal|"Michael Sweet<mike@easysw.com>"
argument_list|,
literal|"Copyright 1997-1998 by Michael Sweet"
argument_list|,
name|PLUG_IN_VERSION
argument_list|,
name|N_
argument_list|(
literal|"Silicon Graphics IRIS image"
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
name|gimp_register_file_handler_mime
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"image/x-sgi"
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"sgi,rgb,rgba,bw,icon"
argument_list|,
literal|""
argument_list|,
literal|"0,short,474"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"Saves files in SGI image file format"
argument_list|,
literal|"This plug-in saves SGI image files."
argument_list|,
literal|"Michael Sweet<mike@easysw.com>"
argument_list|,
literal|"Copyright 1997-1998 by Michael Sweet"
argument_list|,
name|PLUG_IN_VERSION
argument_list|,
name|N_
argument_list|(
literal|"Silicon Graphics IRIS image"
argument_list|)
argument_list|,
literal|"RGB*,GRAY*"
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
name|SAVE_PROC
argument_list|,
literal|"image/x-sgi"
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"sgi,rgb,rgba,bw,icon"
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
name|INIT_I18N
argument_list|()
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
name|NULL
argument_list|,
operator|(
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
operator|)
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
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
comment|/*            * Possibly retrieve data...            */
name|gimp_get_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|compression
argument_list|)
expr_stmt|;
comment|/*            * Then acquire information with a dialog...            */
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
comment|/*            * Make sure all the arguments are there!            */
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
name|compression
operator|=
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
if|if
condition|(
name|compression
operator|<
literal|0
operator|||
name|compression
operator|>
literal|2
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
empty_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/*            * Possibly retrieve data...            */
name|gimp_get_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|compression
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
empty_stmt|;
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
name|gimp_set_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|compression
argument_list|,
sizeof|sizeof
argument_list|(
name|compression
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
comment|/*  * 'load_image()' - Load a PNG image into a new image window.  */
end_comment

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
name|gint
name|i
decl_stmt|,
comment|/* Looping var */
name|x
decl_stmt|,
comment|/* Current X coordinate */
name|y
decl_stmt|,
comment|/* Current Y coordinate */
name|image_type
decl_stmt|,
comment|/* Type of image */
name|layer_type
decl_stmt|,
comment|/* Type of drawable/layer */
name|tile_height
decl_stmt|,
comment|/* Height of tile in GIMP */
name|count
decl_stmt|,
comment|/* Count of rows to put in image */
name|bytes
decl_stmt|;
comment|/* Number of channels to use */
name|sgi_t
modifier|*
name|sgip
decl_stmt|;
comment|/* File pointer */
name|gint32
name|image
decl_stmt|,
comment|/* Image */
name|layer
decl_stmt|;
comment|/* Layer */
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/* Drawable for layer */
name|GimpPixelRgn
name|pixel_rgn
decl_stmt|;
comment|/* Pixel region for layer */
name|guchar
modifier|*
modifier|*
name|pixels
decl_stmt|,
comment|/* Pixel rows */
modifier|*
name|pptr
decl_stmt|;
comment|/* Current pixel */
name|gushort
modifier|*
modifier|*
name|rows
decl_stmt|;
comment|/* SGI image data */
comment|/*   * Open the file for reading...   */
name|sgip
operator|=
name|sgiOpen
argument_list|(
name|filename
argument_list|,
name|SGI_READ
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|sgip
operator|==
name|NULL
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
literal|"Could not open '%s' for reading."
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
empty_stmt|;
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
comment|/*    * Get the image dimensions and create the image...    */
comment|/* Sanitize dimensions (note that they are unsigned short and can    * thus never be larger than GIMP_MAX_IMAGE_SIZE    */
if|if
condition|(
name|sgip
operator|->
name|xsize
operator|==
literal|0
comment|/*|| sgip->xsize> GIMP_MAX_IMAGE_SIZE*/
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
literal|"Invalid width: %hu"
argument_list|)
argument_list|,
name|sgip
operator|->
name|xsize
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
if|if
condition|(
name|sgip
operator|->
name|ysize
operator|==
literal|0
comment|/*|| sgip->ysize> GIMP_MAX_IMAGE_SIZE*/
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
literal|"Invalid height: %hu"
argument_list|)
argument_list|,
name|sgip
operator|->
name|ysize
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
if|if
condition|(
name|sgip
operator|->
name|zsize
operator|==
literal|0
comment|/*|| sgip->zsize> GIMP_MAX_IMAGE_SIZE*/
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
literal|"Invalid number of channels: %hu"
argument_list|)
argument_list|,
name|sgip
operator|->
name|zsize
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|bytes
operator|=
name|sgip
operator|->
name|zsize
expr_stmt|;
switch|switch
condition|(
name|sgip
operator|->
name|zsize
condition|)
block|{
case|case
literal|1
case|:
comment|/* Grayscale */
name|image_type
operator|=
name|GIMP_GRAY
expr_stmt|;
name|layer_type
operator|=
name|GIMP_GRAY_IMAGE
expr_stmt|;
break|break;
case|case
literal|2
case|:
comment|/* Grayscale + alpha */
name|image_type
operator|=
name|GIMP_GRAY
expr_stmt|;
name|layer_type
operator|=
name|GIMP_GRAYA_IMAGE
expr_stmt|;
break|break;
case|case
literal|3
case|:
comment|/* RGB */
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|layer_type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
break|break;
case|case
literal|4
case|:
comment|/* RGBA */
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|layer_type
operator|=
name|GIMP_RGBA_IMAGE
expr_stmt|;
break|break;
default|default:
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|layer_type
operator|=
name|GIMP_RGBA_IMAGE
expr_stmt|;
name|bytes
operator|=
literal|4
expr_stmt|;
break|break;
block|}
name|image
operator|=
name|gimp_image_new
argument_list|(
name|sgip
operator|->
name|xsize
argument_list|,
name|sgip
operator|->
name|ysize
argument_list|,
name|image_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|==
operator|-
literal|1
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
literal|"Could not allocate new image: %s"
argument_list|,
name|gimp_get_pdb_error
argument_list|()
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|gimp_image_set_filename
argument_list|(
name|image
argument_list|,
name|filename
argument_list|)
expr_stmt|;
comment|/*    * Create the "background" layer to hold the image...    */
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|sgip
operator|->
name|xsize
argument_list|,
name|sgip
operator|->
name|ysize
argument_list|,
name|layer_type
argument_list|,
literal|100
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|gimp_image_insert_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
operator|-
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*    * Get the drawable and set the pixel region for our load...    */
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*    * Temporary buffers...    */
name|tile_height
operator|=
name|gimp_tile_height
argument_list|()
expr_stmt|;
name|pixels
operator|=
name|g_new
argument_list|(
name|guchar
operator|*
argument_list|,
name|tile_height
argument_list|)
expr_stmt|;
name|pixels
index|[
literal|0
index|]
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
operator|(
name|gsize
operator|)
name|tile_height
operator|)
operator|*
name|sgip
operator|->
name|xsize
operator|*
name|bytes
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|tile_height
condition|;
name|i
operator|++
control|)
name|pixels
index|[
name|i
index|]
operator|=
name|pixels
index|[
literal|0
index|]
operator|+
name|sgip
operator|->
name|xsize
operator|*
name|bytes
operator|*
name|i
expr_stmt|;
name|rows
operator|=
name|g_new
argument_list|(
argument|unsigned short *
argument_list|,
argument|sgip->zsize
argument_list|)
expr_stmt|;
name|rows
index|[
literal|0
index|]
operator|=
name|g_new
argument_list|(
argument|unsigned short
argument_list|,
argument|((gsize) sgip->xsize) * sgip->zsize
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|sgip
operator|->
name|zsize
condition|;
name|i
operator|++
control|)
name|rows
index|[
name|i
index|]
operator|=
name|rows
index|[
literal|0
index|]
operator|+
name|i
operator|*
name|sgip
operator|->
name|xsize
expr_stmt|;
comment|/*    * Load the image...    */
for|for
control|(
name|y
operator|=
literal|0
operator|,
name|count
operator|=
literal|0
init|;
name|y
operator|<
name|sgip
operator|->
name|ysize
condition|;
name|y
operator|++
operator|,
name|count
operator|++
control|)
block|{
if|if
condition|(
name|count
operator|>=
name|tile_height
condition|)
block|{
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|pixels
index|[
literal|0
index|]
argument_list|,
literal|0
argument_list|,
name|y
operator|-
name|count
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|count
argument_list|)
expr_stmt|;
name|count
operator|=
literal|0
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|y
operator|/
operator|(
name|double
operator|)
name|sgip
operator|->
name|ysize
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|sgip
operator|->
name|zsize
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|sgiGetRow
argument_list|(
name|sgip
argument_list|,
name|rows
index|[
name|i
index|]
argument_list|,
name|sgip
operator|->
name|ysize
operator|-
literal|1
operator|-
name|y
argument_list|,
name|i
argument_list|)
operator|<
literal|0
condition|)
name|printf
argument_list|(
literal|"sgiGetRow(sgip, rows[i], %d, %d) failed!\n"
argument_list|,
name|sgip
operator|->
name|ysize
operator|-
literal|1
operator|-
name|y
argument_list|,
name|i
argument_list|)
expr_stmt|;
if|if
condition|(
name|sgip
operator|->
name|bpp
operator|==
literal|1
condition|)
block|{
comment|/*            * 8-bit (unsigned) pixels...            */
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|pptr
operator|=
name|pixels
index|[
name|count
index|]
init|;
name|x
operator|<
name|sgip
operator|->
name|xsize
condition|;
name|x
operator|++
control|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bytes
condition|;
name|i
operator|++
operator|,
name|pptr
operator|++
control|)
operator|*
name|pptr
operator|=
name|rows
index|[
name|i
index|]
index|[
name|x
index|]
expr_stmt|;
block|}
else|else
block|{
comment|/*            * 16-bit (unsigned) pixels...            */
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|pptr
operator|=
name|pixels
index|[
name|count
index|]
init|;
name|x
operator|<
name|sgip
operator|->
name|xsize
condition|;
name|x
operator|++
control|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bytes
condition|;
name|i
operator|++
operator|,
name|pptr
operator|++
control|)
operator|*
name|pptr
operator|=
name|rows
index|[
name|i
index|]
index|[
name|x
index|]
operator|>>
literal|8
expr_stmt|;
block|}
block|}
comment|/*    * Do the last n rows (count always> 0)    */
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|pixels
index|[
literal|0
index|]
argument_list|,
literal|0
argument_list|,
name|y
operator|-
name|count
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|count
argument_list|)
expr_stmt|;
comment|/*    * Done with the file...    */
name|sgiClose
argument_list|(
name|sgip
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pixels
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pixels
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rows
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rows
argument_list|)
expr_stmt|;
comment|/*    * Update the display...    */
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return
name|image
return|;
block|}
end_function

begin_comment
comment|/*  * 'save_image()' - Save the specified image to a SGI file.  */
end_comment

begin_function
specifier|static
name|gint
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
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
comment|/* Looping var */
name|x
decl_stmt|,
comment|/* Current X coordinate */
name|y
decl_stmt|,
comment|/* Current Y coordinate */
name|tile_height
decl_stmt|,
comment|/* Height of tile in GIMP */
name|count
decl_stmt|,
comment|/* Count of rows to put in image */
name|zsize
decl_stmt|;
comment|/* Number of channels in file */
name|sgi_t
modifier|*
name|sgip
decl_stmt|;
comment|/* File pointer */
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/* Drawable for layer */
name|GimpPixelRgn
name|pixel_rgn
decl_stmt|;
comment|/* Pixel region for layer */
name|guchar
modifier|*
modifier|*
name|pixels
decl_stmt|,
comment|/* Pixel rows */
modifier|*
name|pptr
decl_stmt|;
comment|/* Current pixel */
name|gushort
modifier|*
modifier|*
name|rows
decl_stmt|;
comment|/* SGI image data */
comment|/*    * Get the drawable for the current image...    */
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|zsize
operator|=
literal|0
expr_stmt|;
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
name|zsize
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|GIMP_GRAYA_IMAGE
case|:
name|zsize
operator|=
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_RGB_IMAGE
case|:
name|zsize
operator|=
literal|3
expr_stmt|;
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
name|zsize
operator|=
literal|4
expr_stmt|;
break|break;
default|default:
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Cannot operate on indexed color images."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/*    * Open the file for writing...    */
name|sgip
operator|=
name|sgiOpen
argument_list|(
name|filename
argument_list|,
name|SGI_WRITE
argument_list|,
name|compression
argument_list|,
literal|1
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|zsize
argument_list|)
expr_stmt|;
if|if
condition|(
name|sgip
operator|==
name|NULL
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
literal|"Could not open '%s' for writing."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
empty_stmt|;
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Saving '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
comment|/*    * Allocate memory for "tile_height" rows...    */
name|tile_height
operator|=
name|gimp_tile_height
argument_list|()
expr_stmt|;
name|pixels
operator|=
name|g_new
argument_list|(
name|guchar
operator|*
argument_list|,
name|tile_height
argument_list|)
expr_stmt|;
name|pixels
index|[
literal|0
index|]
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
operator|(
name|gsize
operator|)
name|tile_height
operator|)
operator|*
name|drawable
operator|->
name|width
operator|*
name|zsize
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|tile_height
condition|;
name|i
operator|++
control|)
name|pixels
index|[
name|i
index|]
operator|=
name|pixels
index|[
literal|0
index|]
operator|+
name|drawable
operator|->
name|width
operator|*
name|zsize
operator|*
name|i
expr_stmt|;
name|rows
operator|=
name|g_new
argument_list|(
name|gushort
operator|*
argument_list|,
name|sgip
operator|->
name|zsize
argument_list|)
expr_stmt|;
name|rows
index|[
literal|0
index|]
operator|=
name|g_new
argument_list|(
name|gushort
argument_list|,
operator|(
operator|(
name|gsize
operator|)
name|sgip
operator|->
name|xsize
operator|)
operator|*
name|sgip
operator|->
name|zsize
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|sgip
operator|->
name|zsize
condition|;
name|i
operator|++
control|)
name|rows
index|[
name|i
index|]
operator|=
name|rows
index|[
literal|0
index|]
operator|+
name|i
operator|*
name|sgip
operator|->
name|xsize
expr_stmt|;
comment|/*    * Save the image...    */
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|drawable
operator|->
name|height
condition|;
name|y
operator|+=
name|count
control|)
block|{
comment|/*        * Grab more pixel data...        */
if|if
condition|(
operator|(
name|y
operator|+
name|tile_height
operator|)
operator|>=
name|drawable
operator|->
name|height
condition|)
name|count
operator|=
name|drawable
operator|->
name|height
operator|-
name|y
expr_stmt|;
else|else
name|count
operator|=
name|tile_height
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|pixels
index|[
literal|0
index|]
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|count
argument_list|)
expr_stmt|;
comment|/*        * Convert to shorts and write each color plane separately...        */
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|pptr
operator|=
name|pixels
index|[
literal|0
index|]
init|;
name|i
operator|<
name|count
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|drawable
operator|->
name|width
condition|;
name|x
operator|++
control|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|zsize
condition|;
name|j
operator|++
operator|,
name|pptr
operator|++
control|)
name|rows
index|[
name|j
index|]
index|[
name|x
index|]
operator|=
operator|*
name|pptr
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|zsize
condition|;
name|j
operator|++
control|)
name|sgiPutRow
argument_list|(
name|sgip
argument_list|,
name|rows
index|[
name|j
index|]
argument_list|,
name|drawable
operator|->
name|height
operator|-
literal|1
operator|-
name|y
operator|-
name|i
argument_list|,
name|j
argument_list|)
expr_stmt|;
block|}
empty_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|y
operator|/
operator|(
name|double
operator|)
name|drawable
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
empty_stmt|;
comment|/*    * Done with the file...    */
name|sgiClose
argument_list|(
name|sgip
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pixels
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pixels
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rows
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rows
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
name|frame
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
literal|"SGI"
argument_list|)
argument_list|,
name|PLUG_IN_BINARY
argument_list|,
name|SAVE_PROC
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_int_radio_group_new
argument_list|(
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Compression type"
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|compression
argument_list|,
name|compression
argument_list|,
name|_
argument_list|(
literal|"No compression"
argument_list|)
argument_list|,
name|SGI_COMP_NONE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"RLE compression"
argument_list|)
argument_list|,
name|SGI_COMP_RLE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Aggressive RLE\n(not supported by SGI)"
argument_list|)
argument_list|,
name|SGI_COMP_ARLE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
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
name|frame
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
name|frame
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

