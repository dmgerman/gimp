begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GIMP PSD Plug-in  * Copyright 2007 by John Marshall  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"psd.h"
end_include

begin_include
include|#
directive|include
file|"psd-load.h"
end_include

begin_include
include|#
directive|include
file|"psd-thumb-load.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|PSD_SAVE
end_ifdef

begin_include
include|#
directive|include
file|"psd-save.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/*  Local function prototypes  */
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

begin_comment
comment|/*  Local variables  */
end_comment

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
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
comment|/* Register parameters */
comment|/* File Load */
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
comment|/* Thumbnail Load */
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
ifdef|#
directive|ifdef
name|PSD_SAVE
comment|/* File save */
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
endif|#
directive|endif
comment|/* PSD_SAVE */
comment|/* Register procedures */
comment|/* File load */
name|gimp_install_procedure
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"Loads images from the Photoshop PSD file format"
argument_list|,
literal|"This plug-in loads images in Adobe "
literal|"Photoshop (TM) native PSD format."
argument_list|,
literal|"John Marshall"
argument_list|,
literal|"John Marshall"
argument_list|,
literal|"2007"
argument_list|,
name|N_
argument_list|(
literal|"Photoshop image"
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
literal|"image/x-psd"
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"psd"
argument_list|,
literal|""
argument_list|,
literal|"0,string,8BPS"
argument_list|)
expr_stmt|;
comment|/* Thumbnail load */
name|gimp_install_procedure
argument_list|(
name|LOAD_THUMB_PROC
argument_list|,
literal|"Loads thumbnails from the Photoshop PSD file format"
argument_list|,
literal|"This plug-in loads thumnail images from Adobe "
literal|"Photoshop (TM) native PSD format files."
argument_list|,
literal|"John Marshall"
argument_list|,
literal|"John Marshall"
argument_list|,
literal|"2007"
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
name|LOAD_PROC
argument_list|,
name|LOAD_THUMB_PROC
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|PSD_SAVE
comment|/* File save*/
name|gimp_install_procedure
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"Saves images to the Photoshop PSD file format"
argument_list|,
literal|"This plug-in saves images in Adobe "
literal|"Photoshop (TM) native PSD format."
argument_list|,
literal|"John Marshall"
argument_list|,
literal|"John Marshall"
argument_list|,
literal|"2007"
argument_list|,
name|N_
argument_list|(
literal|"Photoshop image"
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
name|gimp_register_save_handler
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"psd"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_mime
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"image/x-psd"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* PSD_SAVE */
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
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
ifdef|#
directive|ifdef
name|PSD_SAVE
name|gint32
name|drawable_ID
decl_stmt|;
name|GimpExportReturn
name|export
init|=
name|GIMP_EXPORT_CANCEL
decl_stmt|;
endif|#
directive|endif
comment|/* PSD_SAVE */
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
comment|/* File load */
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
comment|/* Thumbnail load */
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|LOAD_THUMB_PROC
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|nparams
operator|<
literal|2
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
specifier|const
name|gchar
modifier|*
name|filename
init|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_string
decl_stmt|;
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
name|filename
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
literal|4
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
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
block|}
ifdef|#
directive|ifdef
name|PSD_SAVE
comment|/* File save */
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
literal|"PSD"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
operator||
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
operator||
name|GIMP_EXPORT_CAN_HANDLE_LAYERS
operator||
name|GIMP_EXPORT_CAN_HANDLE_LAYER_MASKS
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
block|{             }
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
endif|#
directive|endif
comment|/* PSD_SAVE */
comment|/* Unknown procedure */
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

end_unit

