begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-jp2.c -- JPEG 2000 file format plug-in  * Copyright (C) 2009 Aurimas JuÅ¡ka<aurimas.juska@gmail.com>  * Copyright (C) 2004 Florian Traverse<florian.traverse@cpe.fr>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|_O_BINARY
end_ifndef

begin_define
DECL|macro|_O_BINARY
define|#
directive|define
name|_O_BINARY
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

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
file|<jasper/jasper.h>
end_include

begin_define
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-jp2-load"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-jp2-load"
end_define

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
name|load_icc_profile
parameter_list|(
name|jas_image_t
modifier|*
name|jas_image
parameter_list|,
name|gint
name|image_ID
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|gimp_install_procedure
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"Loads JPEG 2000 images."
argument_list|,
literal|"The JPEG 2000 image loader."
argument_list|,
literal|"Aurimas JuÅ¡ka"
argument_list|,
literal|"Aurimas JuÅ¡ka, Florian Traverse"
argument_list|,
literal|"2009"
argument_list|,
name|N_
argument_list|(
literal|"JPEG 2000 image"
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
name|gimp_register_magic_load_handler
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"jp2,jpc,jpx,j2k,jpf"
argument_list|,
literal|""
argument_list|,
literal|"4,string,jP,0,string,\xff\x4f\xff\x51\x00"
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_mime
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"image/jp2"
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|gimp_register_file_handler_mime (LOAD_PROC, "image/jpeg2000");   gimp_register_file_handler_mime (LOAD_PROC, "image/jpx");
endif|#
directive|endif
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
name|gint
name|image_ID
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
name|gboolean
name|interactive
decl_stmt|;
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
name|interactive
operator|=
name|TRUE
expr_stmt|;
break|break;
default|default:
name|interactive
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
name|GFile
modifier|*
name|file
init|=
name|g_file_new_for_path
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
decl_stmt|;
name|GimpMetadata
modifier|*
name|metadata
decl_stmt|;
name|metadata
operator|=
name|gimp_image_metadata_load_prepare
argument_list|(
name|image_ID
argument_list|,
literal|"image/jp2"
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata
condition|)
block|{
name|GimpMetadataLoadFlags
name|flags
init|=
name|GIMP_METADATA_LOAD_ALL
decl_stmt|;
name|gimp_image_metadata_load_finish
argument_list|(
name|image_ID
argument_list|,
literal|"image/jp2"
argument_list|,
name|metadata
argument_list|,
name|flags
argument_list|,
name|interactive
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|metadata
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
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
name|fd
decl_stmt|;
name|jas_stream_t
modifier|*
name|stream
decl_stmt|;
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
name|jas_image_t
modifier|*
name|image
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
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|num_components
decl_stmt|;
name|gint
name|colorspace_family
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|guchar
modifier|*
name|pixels
decl_stmt|;
name|jas_matrix_t
modifier|*
name|matrix
decl_stmt|;
name|gint
name|components
index|[
literal|4
index|]
decl_stmt|;
name|jas_init
argument_list|()
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
name|fd
operator|=
name|g_open
argument_list|(
name|filename
argument_list|,
name|O_RDONLY
operator||
name|_O_BINARY
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
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
name|g_file_error_from_errno
argument_list|(
name|errno
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|stream
operator|=
name|jas_stream_fdopen
argument_list|(
name|fd
argument_list|,
literal|"rb"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|stream
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|g_file_error_from_errno
argument_list|(
name|errno
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|image
operator|=
name|jas_image_decode
argument_list|(
name|stream
argument_list|,
operator|-
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|image
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
literal|"Couldn't decode '%s'."
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
literal|80
argument_list|)
expr_stmt|;
name|jas_stream_close
argument_list|(
name|stream
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
name|width
operator|=
name|jas_image_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|height
operator|=
name|jas_image_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/* determine image type */
name|colorspace_family
operator|=
name|jas_clrspc_fam
argument_list|(
name|jas_image_clrspc
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|colorspace_family
condition|)
block|{
case|case
name|JAS_CLRSPC_FAM_GRAY
case|:
name|base_type
operator|=
name|GIMP_GRAY
expr_stmt|;
name|components
index|[
literal|0
index|]
operator|=
name|jas_image_getcmptbytype
argument_list|(
name|image
argument_list|,
name|JAS_IMAGE_CT_GRAY_Y
argument_list|)
expr_stmt|;
if|if
condition|(
name|components
index|[
literal|0
index|]
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
name|_
argument_list|(
literal|"The image '%s' is in grayscale but does not contain "
literal|"any gray component."
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
name|components
index|[
literal|1
index|]
operator|=
name|jas_image_getcmptbytype
argument_list|(
name|image
argument_list|,
name|JAS_IMAGE_CT_OPACITY
argument_list|)
expr_stmt|;
if|if
condition|(
name|components
index|[
literal|1
index|]
operator|!=
operator|-
literal|1
condition|)
block|{
name|num_components
operator|=
literal|2
expr_stmt|;
name|image_type
operator|=
name|GIMP_GRAYA_IMAGE
expr_stmt|;
block|}
else|else
block|{
name|num_components
operator|=
literal|1
expr_stmt|;
name|image_type
operator|=
name|GIMP_GRAY_IMAGE
expr_stmt|;
block|}
break|break;
case|case
name|JAS_CLRSPC_FAM_RGB
case|:
name|base_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|components
index|[
literal|0
index|]
operator|=
name|jas_image_getcmptbytype
argument_list|(
name|image
argument_list|,
name|JAS_IMAGE_CT_RGB_R
argument_list|)
expr_stmt|;
name|components
index|[
literal|1
index|]
operator|=
name|jas_image_getcmptbytype
argument_list|(
name|image
argument_list|,
name|JAS_IMAGE_CT_RGB_G
argument_list|)
expr_stmt|;
name|components
index|[
literal|2
index|]
operator|=
name|jas_image_getcmptbytype
argument_list|(
name|image
argument_list|,
name|JAS_IMAGE_CT_RGB_B
argument_list|)
expr_stmt|;
if|if
condition|(
name|components
index|[
literal|0
index|]
operator|==
operator|-
literal|1
operator|||
name|components
index|[
literal|1
index|]
operator|==
operator|-
literal|1
operator|||
name|components
index|[
literal|2
index|]
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
name|_
argument_list|(
literal|"The image '%s' is in RGB, but is missing some of the "
literal|"components."
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
name|components
index|[
literal|3
index|]
operator|=
name|jas_image_getcmptbytype
argument_list|(
name|image
argument_list|,
name|JAS_IMAGE_CT_OPACITY
argument_list|)
expr_stmt|;
comment|/* ImageMagick seems to write out the 'matte' component type 	 (number 3) */
if|if
condition|(
name|components
index|[
literal|3
index|]
operator|==
operator|-
literal|1
condition|)
name|components
index|[
literal|3
index|]
operator|=
name|jas_image_getcmptbytype
argument_list|(
name|image
argument_list|,
literal|3
argument_list|)
expr_stmt|;
if|if
condition|(
name|components
index|[
literal|3
index|]
operator|!=
operator|-
literal|1
condition|)
block|{
name|num_components
operator|=
literal|4
expr_stmt|;
name|image_type
operator|=
name|GIMP_RGBA_IMAGE
expr_stmt|;
block|}
else|else
block|{
name|num_components
operator|=
literal|3
expr_stmt|;
name|image_type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
block|}
break|break;
case|case
name|JAS_CLRSPC_FAM_XYZ
case|:
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
literal|"The image '%s' is in the CIEXYZ color space, but there is "
literal|"no code in place to convert it to RGB."
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
case|case
name|JAS_CLRSPC_FAM_LAB
case|:
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
literal|"The image '%s' is in the CIELAB color space, but there is "
literal|"no code in place to convert it to RGB."
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
case|case
name|JAS_CLRSPC_FAM_YCBCR
case|:
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
literal|"The image '%s' is in the YCbCr color space, but there is "
literal|"no code in place to convert it to RGB."
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
case|case
name|JAS_CLRSPC_FAM_UNKNOWN
case|:
default|default:
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
literal|"The image '%s' is in an unknown color space."
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
comment|/* check all components if their dimensions match image dimensions */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_components
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|jas_image_cmpttlx
argument_list|(
name|image
argument_list|,
name|components
index|[
name|i
index|]
argument_list|)
operator|!=
name|jas_image_tlx
argument_list|(
name|image
argument_list|)
operator|||
name|jas_image_cmpttly
argument_list|(
name|image
argument_list|,
name|components
index|[
name|i
index|]
argument_list|)
operator|!=
name|jas_image_tly
argument_list|(
name|image
argument_list|)
operator|||
name|jas_image_cmptbrx
argument_list|(
name|image
argument_list|,
name|components
index|[
name|i
index|]
argument_list|)
operator|!=
name|jas_image_brx
argument_list|(
name|image
argument_list|)
operator|||
name|jas_image_cmptbry
argument_list|(
name|image
argument_list|,
name|components
index|[
name|i
index|]
argument_list|)
operator|!=
name|jas_image_bry
argument_list|(
name|image
argument_list|)
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
literal|"Image component %d of image '%s' does not have the "
literal|"same size as the image. This is currently not "
literal|"supported."
argument_list|)
argument_list|,
name|i
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
if|if
condition|(
name|jas_image_cmpthstep
argument_list|(
name|image
argument_list|,
name|components
index|[
name|i
index|]
argument_list|)
operator|!=
literal|1
operator|||
name|jas_image_cmptvstep
argument_list|(
name|image
argument_list|,
name|components
index|[
name|i
index|]
argument_list|)
operator|!=
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
name|_
argument_list|(
literal|"Image component %d of image '%s' does not have both "
literal|"a hstep and vstep."
argument_list|)
argument_list|,
name|i
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
if|if
condition|(
name|jas_image_cmptsgnd
argument_list|(
name|image
argument_list|,
name|components
index|[
name|i
index|]
argument_list|)
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
literal|"Image component %d of image '%s' is signed. "
literal|"This is currently not supported."
argument_list|)
argument_list|,
name|i
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
block|}
name|image_ID
operator|=
name|gimp_image_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|base_type
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
name|gimp_image_get_default_new_layer_mode
argument_list|(
name|image_ID
argument_list|)
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
name|pixels
operator|=
name|malloc
argument_list|(
name|width
operator|*
name|num_components
argument_list|)
expr_stmt|;
name|matrix
operator|=
name|jas_matrix_create
argument_list|(
literal|1
argument_list|,
name|width
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
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|num_components
condition|;
name|j
operator|++
control|)
block|{
specifier|const
name|int
name|channel_prec
init|=
literal|8
decl_stmt|;
name|jas_image_readcmpt
argument_list|(
name|image
argument_list|,
name|components
index|[
name|j
index|]
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|width
argument_list|,
literal|1
argument_list|,
name|matrix
argument_list|)
expr_stmt|;
if|if
condition|(
name|jas_image_cmptprec
argument_list|(
name|image
argument_list|,
name|components
index|[
name|j
index|]
argument_list|)
operator|>=
name|channel_prec
condition|)
block|{
name|int
name|shift
init|=
name|MAX
argument_list|(
name|jas_image_cmptprec
argument_list|(
name|image
argument_list|,
name|components
index|[
name|j
index|]
argument_list|)
operator|-
name|channel_prec
argument_list|,
literal|0
argument_list|)
decl_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|width
condition|;
name|k
operator|++
control|)
block|{
name|pixels
index|[
name|k
operator|*
name|num_components
operator|+
name|j
index|]
operator|=
name|jas_matrix_get
argument_list|(
name|matrix
argument_list|,
literal|0
argument_list|,
name|k
argument_list|)
operator|>>
name|shift
expr_stmt|;
block|}
block|}
else|else
block|{
name|int
name|mul
init|=
literal|1
operator|<<
operator|(
name|channel_prec
operator|-
name|jas_image_cmptprec
argument_list|(
name|image
argument_list|,
name|components
index|[
name|j
index|]
argument_list|)
operator|)
decl_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|width
condition|;
name|k
operator|++
control|)
block|{
name|pixels
index|[
name|k
operator|*
name|num_components
operator|+
name|j
index|]
operator|=
name|jas_matrix_get
argument_list|(
name|matrix
argument_list|,
literal|0
argument_list|,
name|k
argument_list|)
operator|*
name|mul
expr_stmt|;
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
argument_list|,
name|width
argument_list|,
literal|1
argument_list|)
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|pixels
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
block|}
name|load_icc_profile
argument_list|(
name|image
argument_list|,
name|image_ID
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|jas_matrix_destroy
argument_list|(
name|matrix
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|pixels
argument_list|)
expr_stmt|;
name|jas_image_destroy
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|jas_cleanup
argument_list|()
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
DECL|function|load_icc_profile (jas_image_t * jas_image,gint image_ID,GError ** error)
name|load_icc_profile
parameter_list|(
name|jas_image_t
modifier|*
name|jas_image
parameter_list|,
name|gint
name|image_ID
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|jas_cmprof_t
modifier|*
name|cm_prof
decl_stmt|;
name|jas_iccprof_t
modifier|*
name|jas_icc
decl_stmt|;
name|jas_stream_t
modifier|*
name|stream
decl_stmt|;
name|guint32
name|profile_size
decl_stmt|;
name|guchar
modifier|*
name|jas_iccile
decl_stmt|;
name|GimpColorProfile
modifier|*
name|profile
decl_stmt|;
name|cm_prof
operator|=
name|jas_image_cmprof
argument_list|(
name|jas_image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|cm_prof
condition|)
return|return
name|FALSE
return|;
name|jas_icc
operator|=
name|jas_iccprof_createfromcmprof
argument_list|(
name|cm_prof
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|jas_icc
condition|)
return|return
name|FALSE
return|;
name|stream
operator|=
name|jas_stream_memopen
argument_list|(
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|stream
condition|)
return|return
name|FALSE
return|;
name|jas_iccprof_save
argument_list|(
name|jas_icc
argument_list|,
name|stream
argument_list|)
expr_stmt|;
name|jas_stream_rewind
argument_list|(
name|stream
argument_list|)
expr_stmt|;
name|profile_size
operator|=
name|jas_stream_length
argument_list|(
name|stream
argument_list|)
expr_stmt|;
name|jas_iccile
operator|=
name|g_malloc
argument_list|(
name|profile_size
argument_list|)
expr_stmt|;
name|jas_stream_read
argument_list|(
name|stream
argument_list|,
name|jas_iccile
argument_list|,
name|profile_size
argument_list|)
expr_stmt|;
name|jas_stream_close
argument_list|(
name|stream
argument_list|)
expr_stmt|;
name|jas_iccprof_destroy
argument_list|(
name|jas_icc
argument_list|)
expr_stmt|;
name|profile
operator|=
name|gimp_color_profile_new_from_icc_profile
argument_list|(
name|jas_iccile
argument_list|,
name|profile_size
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|jas_iccile
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
condition|)
block|{
name|gimp_image_set_color_profile
argument_list|(
name|image_ID
argument_list|,
name|profile
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

