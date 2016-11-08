begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-webp - WebP file format plug-in for the GIMP  * Copyright (C) 2015  Nathan Osman  * Copyright (C) 2016  Ben Touchette  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation, either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<webp/encode.h>
end_include

begin_include
include|#
directive|include
file|"file-webp-dialog.h"
end_include

begin_include
include|#
directive|include
file|"file-webp-load.h"
end_include

begin_include
include|#
directive|include
file|"file-webp-save.h"
end_include

begin_include
include|#
directive|include
file|"file-webp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

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

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
name|NULL
block|,
name|query
block|,
name|run
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
name|set_default_params
parameter_list|(
name|WebPSaveParams
modifier|*
name|params
parameter_list|)
block|{
name|params
operator|->
name|preset
operator|=
name|WEBP_PRESET_DEFAULT
expr_stmt|;
name|params
operator|->
name|lossless
operator|=
name|FALSE
expr_stmt|;
name|params
operator|->
name|animation
operator|=
name|FALSE
expr_stmt|;
name|params
operator|->
name|loop
operator|=
name|TRUE
expr_stmt|;
name|params
operator|->
name|quality
operator|=
literal|90.0f
expr_stmt|;
name|params
operator|->
name|alpha_quality
operator|=
literal|100.0f
expr_stmt|;
name|params
operator|->
name|exif
operator|=
name|TRUE
expr_stmt|;
name|params
operator|->
name|iptc
operator|=
name|TRUE
expr_stmt|;
name|params
operator|->
name|xmp
operator|=
name|TRUE
expr_stmt|;
name|params
operator|->
name|delay
operator|=
literal|200
expr_stmt|;
name|params
operator|->
name|force_delay
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|query (void)
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpParamDef
name|load_arguments
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"Interactive, non-interactive"
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
name|load_return_values
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
name|save_arguments
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"Interactive, non-interactive"
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
literal|"The name of the file to save the image to"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw-filename"
block|,
literal|"The name entered"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"preset"
block|,
literal|"preset (Default=0, Picture=1, Photo=2, Drawing=3, Icon=4, Text=5)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"lossless"
block|,
literal|"Use lossless encoding (0/1)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"quality"
block|,
literal|"Quality of the image (0<= quality<= 100)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"alpha-quality"
block|,
literal|"Quality of the image's alpha channel (0<= alpha-quality<= 100)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"animation"
block|,
literal|"Use layers for animation (0/1)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"anim-loop"
block|,
literal|"Loop animation infinitely (0/1)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"exif"
block|,
literal|"Toggle saving exif data (0/1)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"iptc"
block|,
literal|"Toggle saving iptc data (0/1)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"xmp"
block|,
literal|"Toggle saving xmp data (0/1)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"delay"
block|,
literal|"Delay to use when timestamps are not available or forced"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"force-delay"
block|,
literal|"Force delay on all frames"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"Loads images in the WebP file format"
argument_list|,
literal|"Loads images in the WebP file format"
argument_list|,
literal|"Nathan Osman, Ben Touchette"
argument_list|,
literal|"(C) 2015-2016 Nathan Osman, (C) 2016 Ben Touchette"
argument_list|,
literal|"2015,2016"
argument_list|,
name|N_
argument_list|(
literal|"WebP image"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_arguments
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_return_values
argument_list|)
argument_list|,
name|load_arguments
argument_list|,
name|load_return_values
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_mime
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"image/webp"
argument_list|)
expr_stmt|;
name|gimp_register_load_handler
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"webp"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"webp"
argument_list|,
literal|""
argument_list|,
literal|"8,string,WEBP"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"Saves files in the WebP image format"
argument_list|,
literal|"Saves files in the WebP image format"
argument_list|,
literal|"Nathan Osman, Ben Touchette"
argument_list|,
literal|"(C) 2015-2016 Nathan Osman, (C) 2016 Ben Touchette"
argument_list|,
literal|"2015,2016"
argument_list|,
name|N_
argument_list|(
literal|"WebP image"
argument_list|)
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|save_arguments
argument_list|)
argument_list|,
literal|0
argument_list|,
name|save_arguments
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_mime
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"image/webp"
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"webp"
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
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|LOAD_PROC
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
name|FALSE
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
comment|/* Return the new image that was loaded */
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
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|SAVE_PROC
argument_list|)
condition|)
block|{
name|WebPSaveParams
name|params
decl_stmt|;
name|GimpExportReturn
name|export
init|=
name|GIMP_EXPORT_CANCEL
decl_stmt|;
name|gint32
modifier|*
name|layers
init|=
name|NULL
decl_stmt|;
name|gint32
name|n_layers
decl_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
operator|||
name|run_mode
operator|==
name|GIMP_RUN_WITH_LAST_VALS
condition|)
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
case|case
name|GIMP_RUN_INTERACTIVE
case|:
comment|/* Default settings */
name|set_default_params
argument_list|(
operator|&
name|params
argument_list|)
expr_stmt|;
comment|/*  Possibly override with session data  */
name|gimp_get_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|params
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
literal|"WebP"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
operator||
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
operator||
name|GIMP_EXPORT_CAN_HANDLE_LAYERS_AS_ANIMATION
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
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparams
operator|!=
literal|16
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|params
operator|.
name|preset
operator|=
name|get_preset_from_id
argument_list|(
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
name|params
operator|.
name|lossless
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|params
operator|.
name|quality
operator|=
name|param
index|[
literal|7
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|params
operator|.
name|alpha_quality
operator|=
name|param
index|[
literal|8
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|params
operator|.
name|animation
operator|=
name|param
index|[
literal|9
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|params
operator|.
name|loop
operator|=
name|param
index|[
literal|10
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|params
operator|.
name|exif
operator|=
name|param
index|[
literal|11
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|params
operator|.
name|iptc
operator|=
name|param
index|[
literal|12
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|params
operator|.
name|xmp
operator|=
name|param
index|[
literal|13
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|params
operator|.
name|delay
operator|=
name|param
index|[
literal|14
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|params
operator|.
name|force_delay
operator|=
name|param
index|[
literal|15
index|]
operator|.
name|data
operator|.
name|d_int32
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
name|layers
operator|=
name|gimp_image_get_layers
argument_list|(
name|image_ID
argument_list|,
operator|&
name|n_layers
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
if|if
condition|(
operator|!
name|save_dialog
argument_list|(
operator|&
name|params
argument_list|,
name|image_ID
argument_list|,
name|n_layers
argument_list|)
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
block|}
block|}
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
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|n_layers
argument_list|,
name|layers
argument_list|,
name|image_ID
argument_list|,
name|drawable_ID
argument_list|,
operator|&
name|params
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
name|g_free
argument_list|(
name|layers
argument_list|)
expr_stmt|;
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
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
comment|/* save parameters for later */
name|gimp_set_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|params
argument_list|,
sizeof|sizeof
argument_list|(
name|params
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* If an error was supplied, include it in the return values */
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

end_unit

