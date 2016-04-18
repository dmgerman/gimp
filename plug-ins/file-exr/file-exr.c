begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimp/stdplugins-intl.h"
end_include

begin_include
include|#
directive|include
file|"openexr-wrapper.h"
end_include

begin_define
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-exr-load"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-exr"
end_define

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|"0.0.0"
end_define

begin_comment
comment|/*  * Declare some local functions.  */
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
name|gboolean
name|interactive
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * Some global variables.  */
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
name|gimp_install_procedure
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"Loads files in the OpenEXR file format"
argument_list|,
literal|"This plug-in loads OpenEXR files. "
argument_list|,
literal|"Dominik Ernst<dernst@gmx.de>, "
literal|"Mukund Sivaraman<muks@banu.com>"
argument_list|,
literal|"Dominik Ernst<dernst@gmx.de>, "
literal|"Mukund Sivaraman<muks@banu.com>"
argument_list|,
name|PLUG_IN_VERSION
argument_list|,
name|N_
argument_list|(
literal|"OpenEXR image"
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
literal|"image/x-exr"
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"exr"
argument_list|,
literal|""
argument_list|,
literal|"0,lelong,20000630"
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
operator|==
name|GIMP_RUN_INTERACTIVE
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
DECL|function|load_image (const gchar * filename,gboolean interactive,GError ** error)
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|interactive
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|EXRLoader
modifier|*
name|loader
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|GimpImageBaseType
name|image_type
decl_stmt|;
name|GimpPrecision
name|image_precision
decl_stmt|;
name|gint32
name|image
init|=
operator|-
literal|1
decl_stmt|;
name|GimpImageType
name|layer_type
decl_stmt|;
name|gint32
name|layer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
init|=
name|NULL
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gint
name|tile_height
decl_stmt|;
name|gchar
modifier|*
name|pixels
init|=
name|NULL
decl_stmt|;
name|gint
name|begin
decl_stmt|;
name|gint32
name|success
init|=
name|FALSE
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
name|loader
operator|=
name|exr_loader_new
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|loader
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
literal|"Error opening file '%s' for reading"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
block|}
name|width
operator|=
name|exr_loader_get_width
argument_list|(
name|loader
argument_list|)
expr_stmt|;
name|height
operator|=
name|exr_loader_get_height
argument_list|(
name|loader
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|width
operator|<
literal|1
operator|)
operator|||
operator|(
name|height
operator|<
literal|1
operator|)
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
literal|"Error querying image dimensions from '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
block|}
name|has_alpha
operator|=
name|exr_loader_has_alpha
argument_list|(
name|loader
argument_list|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
switch|switch
condition|(
name|exr_loader_get_precision
argument_list|(
name|loader
argument_list|)
condition|)
block|{
case|case
name|PREC_UINT
case|:
name|image_precision
operator|=
name|GIMP_PRECISION_U32_LINEAR
expr_stmt|;
break|break;
case|case
name|PREC_HALF
case|:
name|image_precision
operator|=
name|GIMP_PRECISION_HALF_LINEAR
expr_stmt|;
break|break;
case|case
name|PREC_FLOAT
case|:
name|image_precision
operator|=
name|GIMP_PRECISION_FLOAT_LINEAR
expr_stmt|;
break|break;
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
literal|"Error querying image precision from '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
block|}
switch|switch
condition|(
name|exr_loader_get_image_type
argument_list|(
name|loader
argument_list|)
condition|)
block|{
case|case
name|IMAGE_TYPE_RGB
case|:
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|layer_type
operator|=
name|has_alpha
condition|?
name|GIMP_RGBA_IMAGE
else|:
name|GIMP_RGB_IMAGE
expr_stmt|;
break|break;
case|case
name|IMAGE_TYPE_GRAY
case|:
name|image_type
operator|=
name|GIMP_GRAY
expr_stmt|;
name|layer_type
operator|=
name|has_alpha
condition|?
name|GIMP_GRAYA_IMAGE
else|:
name|GIMP_GRAY_IMAGE
expr_stmt|;
break|break;
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
literal|"Error querying image type from '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
block|}
name|image
operator|=
name|gimp_image_new_with_precision
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|image_type
argument_list|,
name|image_precision
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
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Could not create new image for '%s': %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|gimp_get_pdb_error
argument_list|()
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
block|}
name|gimp_image_set_filename
argument_list|(
name|image
argument_list|,
name|filename
argument_list|)
expr_stmt|;
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
name|width
argument_list|,
name|height
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
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|format
operator|=
name|gimp_drawable_get_format
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
expr_stmt|;
name|tile_height
operator|=
name|gimp_tile_height
argument_list|()
expr_stmt|;
name|pixels
operator|=
name|g_new0
argument_list|(
name|gchar
argument_list|,
name|tile_height
operator|*
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
for|for
control|(
name|begin
operator|=
literal|0
init|;
name|begin
operator|<
name|height
condition|;
name|begin
operator|+=
name|tile_height
control|)
block|{
name|gint
name|end
decl_stmt|;
name|gint
name|num
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|end
operator|=
name|MIN
argument_list|(
name|begin
operator|+
name|tile_height
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|num
operator|=
name|end
operator|-
name|begin
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|retval
decl_stmt|;
name|retval
operator|=
name|exr_loader_read_pixel_row
argument_list|(
name|loader
argument_list|,
name|pixels
operator|+
operator|(
name|i
operator|*
name|width
operator|*
name|bpp
operator|)
argument_list|,
name|bpp
argument_list|,
name|begin
operator|+
name|i
argument_list|)
expr_stmt|;
if|if
condition|(
name|retval
operator|<
literal|0
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
literal|"Error reading pixel data from '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
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
name|begin
argument_list|,
name|width
argument_list|,
name|num
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
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|begin
operator|/
operator|(
name|gdouble
operator|)
name|height
argument_list|)
expr_stmt|;
block|}
comment|/* try to load an icc profile, it will be generated on the fly if    * chromaticities are given    */
if|if
condition|(
name|image_type
operator|==
name|GIMP_RGB
condition|)
block|{
name|cmsHPROFILE
name|lcms_profile
decl_stmt|;
name|lcms_profile
operator|=
name|exr_loader_get_icc_profile
argument_list|(
name|loader
argument_list|)
expr_stmt|;
if|if
condition|(
name|lcms_profile
condition|)
block|{
name|GimpColorProfile
modifier|*
name|profile
decl_stmt|;
name|profile
operator|=
name|gimp_color_profile_new_from_lcms_profile
argument_list|(
name|lcms_profile
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cmsCloseProfile
argument_list|(
name|lcms_profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
condition|)
block|{
name|gimp_image_set_color_profile
argument_list|(
name|image
argument_list|,
name|profile
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
name|out
label|:
if|if
condition|(
name|buffer
condition|)
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixels
condition|)
name|g_free
argument_list|(
name|pixels
argument_list|)
expr_stmt|;
if|if
condition|(
name|loader
condition|)
name|exr_loader_unref
argument_list|(
name|loader
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
return|return
name|image
return|;
if|if
condition|(
name|image
operator|!=
operator|-
literal|1
condition|)
name|gimp_image_delete
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
end_function

end_unit

