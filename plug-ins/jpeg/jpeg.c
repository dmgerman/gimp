begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<setjmp.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<jpeglib.h>
end_include

begin_include
include|#
directive|include
file|<jerror.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_EXIF
end_ifdef

begin_include
include|#
directive|include
file|<libexif/exif-data.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_EXIF */
end_comment

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

begin_include
include|#
directive|include
file|"jpeg.h"
end_include

begin_include
include|#
directive|include
file|"jpeg-load.h"
end_include

begin_include
include|#
directive|include
file|"jpeg-save.h"
end_include

begin_include
include|#
directive|include
file|"gimpexif.h"
end_include

begin_comment
comment|/* Declare local functions.  */
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

begin_decl_stmt
DECL|variable|undo_touched
name|gboolean
name|undo_touched
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|load_interactive
name|gboolean
name|load_interactive
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_comment
name|gchar
modifier|*
name|image_comment
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|display_ID
name|gint32
name|display_ID
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|jsvals
name|JpegSaveVals
name|jsvals
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|orig_image_ID_global
name|gint32
name|orig_image_ID_global
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_ID_global
name|gint32
name|drawable_ID_global
decl_stmt|;
end_decl_stmt

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_EXIF
end_ifdef

begin_decl_stmt
DECL|variable|exif_data
name|ExifData
modifier|*
name|exif_data
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

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
ifdef|#
directive|ifdef
name|HAVE_EXIF
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
endif|#
directive|endif
comment|/* HAVE_EXIF */
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
name|GIMP_PDB_FLOAT
block|,
literal|"quality"
block|,
literal|"Quality of saved image (0<= quality<= 1)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"smoothing"
block|,
literal|"Smoothing factor for saved image (0<= smoothing<= 1)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"optimize"
block|,
literal|"Optimization of entropy encoding parameters (0/1)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"progressive"
block|,
literal|"Enable progressive jpeg image loading (0/1)"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"comment"
block|,
literal|"Image comment"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"subsmp"
block|,
literal|"The subsampling option number"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"baseline"
block|,
literal|"Force creation of a baseline JPEG (non-baseline JPEGs can't be read by all decoders) (0/1)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"restart"
block|,
literal|"Frequency of restart markers (in rows, 0 = no restart markers)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"dct"
block|,
literal|"DCT algorithm to use (speed/quality tradeoff)"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"loads files in the JPEG file format"
argument_list|,
literal|"loads files in the JPEG file format"
argument_list|,
literal|"Spencer Kimball, Peter Mattis& others"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1995-1999"
argument_list|,
name|N_
argument_list|(
literal|"JPEG image"
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
literal|"image/jpeg"
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"jpg,jpeg,jpe"
argument_list|,
literal|""
argument_list|,
literal|"6,string,JFIF,6,string,Exif"
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|HAVE_EXIF
name|gimp_install_procedure
argument_list|(
name|LOAD_THUMB_PROC
argument_list|,
literal|"Loads a thumbnail from a JPEG image"
argument_list|,
literal|"Loads a thumbnail from a JPEG image (only if it exists)"
argument_list|,
literal|"S. Mukund<muks@mukund.org>, Sven Neumann<sven@gimp.org>"
argument_list|,
literal|"S. Mukund<muks@mukund.org>, Sven Neumann<sven@gimp.org>"
argument_list|,
literal|"November 15, 2004"
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
endif|#
directive|endif
comment|/* HAVE_EXIF */
name|gimp_install_procedure
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"saves files in the JPEG file format"
argument_list|,
literal|"saves files in the lossy, widely supported JPEG format"
argument_list|,
literal|"Spencer Kimball, Peter Mattis& others"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1995-1999"
argument_list|,
name|N_
argument_list|(
literal|"JPEG image"
argument_list|)
argument_list|,
literal|"RGB*, GRAY*"
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
literal|"image/jpeg"
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"jpg,jpeg,jpe"
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
literal|4
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
name|gint32
name|orig_image_ID
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|gboolean
name|err
decl_stmt|;
name|GimpExportReturn
name|export
init|=
name|GIMP_EXPORT_CANCEL
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
name|INIT_I18N
argument_list|()
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
name|image_ID_global
operator|=
operator|-
literal|1
expr_stmt|;
name|layer_ID_global
operator|=
operator|-
literal|1
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
name|load_interactive
operator|=
name|TRUE
expr_stmt|;
break|break;
default|default:
name|load_interactive
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
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
name|FALSE
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
ifdef|#
directive|ifdef
name|HAVE_EXIF
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
endif|#
directive|endif
comment|/* HAVE_EXIF */
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
name|orig_image_ID
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
literal|"JPEG"
argument_list|,
operator|(
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|export
condition|)
block|{
case|case
name|GIMP_EXPORT_EXPORT
case|:
block|{
name|gchar
modifier|*
name|tmp
init|=
name|g_filename_from_utf8
argument_list|(
name|_
argument_list|(
literal|"Export Preview"
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|tmp
condition|)
block|{
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
name|display_ID
operator|=
operator|-
literal|1
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_EXPORT_IGNORE
case|:
break|break;
case|case
name|GIMP_EXPORT_CANCEL
case|:
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
break|break;
block|}
break|break;
default|default:
break|break;
block|}
name|g_free
argument_list|(
name|image_comment
argument_list|)
expr_stmt|;
name|image_comment
operator|=
name|NULL
expr_stmt|;
name|parasite
operator|=
name|gimp_image_parasite_find
argument_list|(
name|orig_image_ID
argument_list|,
literal|"gimp-comment"
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|image_comment
operator|=
name|g_strndup
argument_list|(
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
ifdef|#
directive|ifdef
name|HAVE_EXIF
name|exif_data
operator|=
name|gimp_metadata_generate_exif
argument_list|(
name|orig_image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|exif_data
condition|)
name|jpeg_setup_exif_for_save
argument_list|(
name|exif_data
argument_list|,
name|orig_image_ID
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* HAVE_EXIF */
name|load_save_defaults
argument_list|()
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
comment|/*  Make sure all the arguments are there!  */
comment|/*  pw - added two more progressive and comment */
comment|/*  sg - added subsampling, preview, baseline, restarts and DCT */
if|if
condition|(
name|nparams
operator|!=
literal|14
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
comment|/* Once the PDB gets default parameters, remove this hack */
if|if
condition|(
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_float
operator|>
literal|0.05
condition|)
block|{
name|jsvals
operator|.
name|quality
operator|=
literal|100.0
operator|*
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|jsvals
operator|.
name|smoothing
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|jsvals
operator|.
name|optimize
operator|=
name|param
index|[
literal|7
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|jsvals
operator|.
name|progressive
operator|=
name|param
index|[
literal|8
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|jsvals
operator|.
name|baseline
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
name|jsvals
operator|.
name|subsmp
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
name|jsvals
operator|.
name|restart
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
name|jsvals
operator|.
name|dct
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
comment|/* free up the default -- wasted some effort earlier */
name|g_free
argument_list|(
name|image_comment
argument_list|)
expr_stmt|;
name|image_comment
operator|=
name|g_strdup
argument_list|(
name|param
index|[
literal|9
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
block|}
name|jsvals
operator|.
name|preview
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|jsvals
operator|.
name|quality
operator|<
literal|0.0
operator|||
name|jsvals
operator|.
name|quality
operator|>
literal|100.0
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
elseif|else
if|if
condition|(
name|jsvals
operator|.
name|smoothing
operator|<
literal|0.0
operator|||
name|jsvals
operator|.
name|smoothing
operator|>
literal|1.0
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
elseif|else
if|if
condition|(
name|jsvals
operator|.
name|subsmp
operator|<
literal|0
operator|||
name|jsvals
operator|.
name|subsmp
operator|>
literal|2
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
elseif|else
if|if
condition|(
name|jsvals
operator|.
name|dct
operator|<
literal|0
operator|||
name|jsvals
operator|.
name|dct
operator|>
literal|2
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_INTERACTIVE
case|:
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|jsvals
argument_list|)
expr_stmt|;
comment|/* load up the previously used values */
name|parasite
operator|=
name|gimp_image_parasite_find
argument_list|(
name|orig_image_ID
argument_list|,
literal|"jpeg-save-options"
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
specifier|const
name|JpegSaveVals
modifier|*
name|save_vals
init|=
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
decl_stmt|;
name|jsvals
operator|.
name|quality
operator|=
name|save_vals
operator|->
name|quality
expr_stmt|;
name|jsvals
operator|.
name|smoothing
operator|=
name|save_vals
operator|->
name|smoothing
expr_stmt|;
name|jsvals
operator|.
name|optimize
operator|=
name|save_vals
operator|->
name|optimize
expr_stmt|;
name|jsvals
operator|.
name|progressive
operator|=
name|save_vals
operator|->
name|progressive
expr_stmt|;
name|jsvals
operator|.
name|baseline
operator|=
name|save_vals
operator|->
name|baseline
expr_stmt|;
name|jsvals
operator|.
name|subsmp
operator|=
name|save_vals
operator|->
name|subsmp
expr_stmt|;
name|jsvals
operator|.
name|restart
operator|=
name|save_vals
operator|->
name|restart
expr_stmt|;
name|jsvals
operator|.
name|dct
operator|=
name|save_vals
operator|->
name|dct
expr_stmt|;
name|jsvals
operator|.
name|preview
operator|=
name|save_vals
operator|->
name|preview
expr_stmt|;
name|jsvals
operator|.
name|save_exif
operator|=
name|save_vals
operator|->
name|save_exif
expr_stmt|;
name|jsvals
operator|.
name|save_thumbnail
operator|=
name|save_vals
operator|->
name|save_thumbnail
expr_stmt|;
name|jsvals
operator|.
name|save_xmp
operator|=
name|save_vals
operator|->
name|save_xmp
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* We are called with GIMP_RUN_WITH_LAST_VALS but this image                * doesn't have a "jpeg-save-options" parasite. It's better                * to prompt the user with a dialog now so that she has control                * over the JPEG encoding parameters.                */
name|run_mode
operator|=
name|GIMP_RUN_INTERACTIVE
expr_stmt|;
block|}
break|break;
block|}
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
if|if
condition|(
name|jsvals
operator|.
name|preview
condition|)
block|{
comment|/* we freeze undo saving so that we can avoid sucking up                * tile cache with our unneeded preview steps. */
name|gimp_image_undo_freeze
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|undo_touched
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/* prepare for the preview */
name|image_ID_global
operator|=
name|image_ID
expr_stmt|;
name|orig_image_ID_global
operator|=
name|orig_image_ID
expr_stmt|;
name|drawable_ID_global
operator|=
name|drawable_ID
expr_stmt|;
comment|/*  First acquire information with a dialog  */
name|err
operator|=
name|save_dialog
argument_list|()
expr_stmt|;
if|if
condition|(
name|undo_touched
condition|)
block|{
comment|/* thaw undo saving and flush the displays to have them                * reflect the current shortcuts */
name|gimp_image_undo_thaw
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|err
condition|)
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
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
name|orig_image_ID
argument_list|,
name|FALSE
argument_list|)
condition|)
block|{
comment|/*  Store mvals data  */
name|gimp_set_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|jsvals
argument_list|,
sizeof|sizeof
argument_list|(
name|JpegSaveVals
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
block|{
comment|/* If the image was exported, delete the new display. */
comment|/* This also deletes the image.                       */
if|if
condition|(
name|display_ID
operator|!=
operator|-
literal|1
condition|)
name|gimp_display_delete
argument_list|(
name|display_ID
argument_list|)
expr_stmt|;
else|else
name|gimp_image_delete
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
block|}
comment|/* pw - now we need to change the defaults to be whatever        * was used to save this image.  Dump the old parasites        * and add new ones. */
name|gimp_image_parasite_detach
argument_list|(
name|orig_image_ID
argument_list|,
literal|"gimp-comment"
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_comment
operator|&&
name|strlen
argument_list|(
name|image_comment
argument_list|)
condition|)
block|{
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"gimp-comment"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|image_comment
argument_list|)
operator|+
literal|1
argument_list|,
name|image_comment
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
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
name|gimp_image_parasite_detach
argument_list|(
name|orig_image_ID
argument_list|,
literal|"jpeg-save-options"
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"jpeg-save-options"
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|jsvals
argument_list|)
argument_list|,
operator|&
name|jsvals
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
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
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
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
comment|/*  * Here's the routine that will replace the standard error_exit method:  */
end_comment

begin_function
name|void
DECL|function|my_error_exit (j_common_ptr cinfo)
name|my_error_exit
parameter_list|(
name|j_common_ptr
name|cinfo
parameter_list|)
block|{
comment|/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
name|my_error_ptr
name|myerr
init|=
operator|(
name|my_error_ptr
operator|)
name|cinfo
operator|->
name|err
decl_stmt|;
comment|/* Always display the message. */
comment|/* We could postpone this until after returning, if we chose. */
call|(
modifier|*
name|cinfo
operator|->
name|err
operator|->
name|output_message
call|)
argument_list|(
name|cinfo
argument_list|)
expr_stmt|;
comment|/* Return control to the setjmp point */
name|longjmp
argument_list|(
name|myerr
operator|->
name|setjmp_buffer
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|my_output_message (j_common_ptr cinfo)
name|my_output_message
parameter_list|(
name|j_common_ptr
name|cinfo
parameter_list|)
block|{
name|gchar
name|buffer
index|[
name|JMSG_LENGTH_MAX
operator|+
literal|1
index|]
decl_stmt|;
call|(
modifier|*
name|cinfo
operator|->
name|err
operator|->
name|format_message
call|)
argument_list|(
name|cinfo
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

