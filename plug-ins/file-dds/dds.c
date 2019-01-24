begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * DDS GIMP plugin  *  * Copyright (C) 2004-2012 Shawn Kirst<skirst@gmail.com>,  * with parts (C) 2003 Arne Reuter<homepage@arnereuter.de> where specified.  *  * This program is free software; you can redistribute it and/or  * modify it under the terms of the GNU General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; see the file COPYING.  If not, write to  * the Free Software Foundation, 51 Franklin Street, Fifth Floor  * Boston, MA 02110-1301, USA.  */
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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
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
file|<libgimp/stdplugins-intl.h>
end_include

begin_include
include|#
directive|include
file|"ddsplugin.h"
end_include

begin_include
include|#
directive|include
file|"dds.h"
end_include

begin_include
include|#
directive|include
file|"misc.h"
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
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
literal|0
block|,
literal|0
block|,
name|query
block|,
name|run
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dds_write_vals
name|DDSWriteVals
name|dds_write_vals
init|=
block|{
name|DDS_COMPRESS_NONE
block|,
name|DDS_MIPMAP_NONE
block|,
name|DDS_SAVE_SELECTED_LAYER
block|,
name|DDS_FORMAT_DEFAULT
block|,
operator|-
literal|1
block|,
name|DDS_MIPMAP_FILTER_DEFAULT
block|,
name|DDS_MIPMAP_WRAP_DEFAULT
block|,
literal|0
block|,
literal|0
block|,
literal|0.0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0.5
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dds_read_vals
name|DDSReadVals
name|dds_read_vals
init|=
block|{
literal|1
block|,
literal|1
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|load_args
specifier|static
name|GimpParamDef
name|load_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
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
literal|"raw_filename"
block|,
literal|"The name entered"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"load_mipmaps"
block|,
literal|"Load mipmaps if present"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"decode_images"
block|,
literal|"Decode YCoCg/AExp images when detected"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|load_return_vals
specifier|static
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
end_decl_stmt

begin_decl_stmt
DECL|variable|save_args
specifier|static
name|GimpParamDef
name|save_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
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
literal|"The name of the file to save the image as"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name entered"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"compression_format"
block|,
literal|"Compression format (0 = None, 1 = BC1/DXT1, 2 = BC2/DXT3, 3 = BC3/DXT5, 4 = BC3n/DXT5nm, 5 = BC4/ATI1N, 6 = BC5/ATI2N, 7 = RXGB (DXT5), 8 = Alpha Exponent (DXT5), 9 = YCoCg (DXT5), 10 = YCoCg scaled (DXT5))"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"mipmaps"
block|,
literal|"How to handle mipmaps (0 = No mipmaps, 1 = Generate mipmaps, 2 = Use existing mipmaps (layers)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"savetype"
block|,
literal|"How to save the image (0 = selected layer, 1 = cube map, 2 = volume map, 3 = texture array"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"format"
block|,
literal|"Custom pixel format (0 = default, 1 = R5G6B5, 2 = RGBA4, 3 = RGB5A1, 4 = RGB10A2)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"transparent_index"
block|,
literal|"Index of transparent color or -1 to disable (for indexed images only)."
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"mipmap_filter"
block|,
literal|"Filtering to use when generating mipmaps (0 = default, 1 = nearest, 2 = box, 3 = triangle, 4 = quadratic, 5 = bspline, 6 = mitchell, 7 = lanczos, 8 = kaiser)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"mipmap_wrap"
block|,
literal|"Wrap mode to use when generating mipmaps (0 = default, 1 = mirror, 2 = repeat, 3 = clamp)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"gamma_correct"
block|,
literal|"Use gamma correct mipmap filtering"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"srgb"
block|,
literal|"Use sRGB colorspace for gamma correction"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"gamma"
block|,
literal|"Gamma value to use for gamma correction (i.e. 2.2)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"perceptual_metric"
block|,
literal|"Use a perceptual error metric during compression"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"preserve_alpha_coverage"
block|,
literal|"Preserve alpha test converage for alpha channel maps"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"alpha_test_threshold"
block|,
literal|"Alpha test threshold value for which alpha test converage should be preserved"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|decode_args
specifier|static
name|GimpParamDef
name|decode_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
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
name|gimp_install_procedure
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"Loads files in DDS image format"
argument_list|,
literal|"Loads files in DDS image format"
argument_list|,
literal|"Shawn Kirst"
argument_list|,
literal|"Shawn Kirst"
argument_list|,
literal|"2008"
argument_list|,
name|N_
argument_list|(
literal|"DDS image"
argument_list|)
argument_list|,
literal|0
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
literal|"image/dds"
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"dds"
argument_list|,
literal|""
argument_list|,
literal|"0,string,DDS"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"Saves files in DDS image format"
argument_list|,
literal|"Saves files in DDS image format"
argument_list|,
literal|"Shawn Kirst"
argument_list|,
literal|"Shawn Kirst"
argument_list|,
literal|"2008"
argument_list|,
name|N_
argument_list|(
literal|"DDS image"
argument_list|)
argument_list|,
literal|"INDEXED, GRAY, RGB"
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
literal|0
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_mime
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"image/dds"
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"dds"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|DECODE_YCOCG_PROC
argument_list|,
literal|"Converts YCoCg encoded pixels to RGB"
argument_list|,
literal|"Converts YCoCg encoded pixels to RGB"
argument_list|,
literal|"Shawn Kirst"
argument_list|,
literal|"Shawn Kirst"
argument_list|,
literal|"2008"
argument_list|,
name|N_
argument_list|(
literal|"Decode YCoCg"
argument_list|)
argument_list|,
literal|"RGBA"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|decode_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|decode_args
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*gimp_plugin_menu_register (DECODE_YCOCG_PROC, "<Image>/Filters/Colors");*/
name|gimp_install_procedure
argument_list|(
name|DECODE_YCOCG_SCALED_PROC
argument_list|,
literal|"Converts YCoCg (scaled) encoded pixels to RGB"
argument_list|,
literal|"Converts YCoCg (scaled) encoded pixels to RGB"
argument_list|,
literal|"Shawn Kirst"
argument_list|,
literal|"Shawn Kirst"
argument_list|,
literal|"2008"
argument_list|,
name|N_
argument_list|(
literal|"Decode YCoCg (scaled)"
argument_list|)
argument_list|,
literal|"RGBA"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|decode_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|decode_args
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*gimp_plugin_menu_register (DECODE_YCOCG_SCALED_PROC, "<Image>/Filters/Colors");*/
name|gimp_install_procedure
argument_list|(
name|DECODE_ALPHA_EXP_PROC
argument_list|,
literal|"Converts alpha exponent encoded pixels to RGB"
argument_list|,
literal|"Converts alpha exponent encoded pixels to RGB"
argument_list|,
literal|"Shawn Kirst"
argument_list|,
literal|"Shawn Kirst"
argument_list|,
literal|"2008"
argument_list|,
name|N_
argument_list|(
literal|"Decode Alpha exponent"
argument_list|)
argument_list|,
literal|"RGBA"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|decode_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|decode_args
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*gimp_plugin_menu_register (DECODE_ALPHA_EXP_PROC, "<Image>/Filters/Colors");*/
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
name|imageID
decl_stmt|;
name|gint32
name|drawableID
decl_stmt|;
name|GimpExportReturn
name|export
init|=
name|GIMP_EXPORT_CANCEL
decl_stmt|;
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
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
name|gimp_ui_init
argument_list|(
literal|"dds"
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_get_data
argument_list|(
name|LOAD_PROC
argument_list|,
operator|&
name|dds_read_vals
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
name|dds_read_vals
operator|.
name|mipmaps
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|dds_read_vals
operator|.
name|decode_images
operator|=
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
if|if
condition|(
name|nparams
operator|!=
name|G_N_ELEMENTS
argument_list|(
name|load_args
argument_list|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
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
name|status
operator|=
name|read_dds
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
name|imageID
argument_list|,
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
operator|&&
name|imageID
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
name|imageID
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
name|gimp_set_data
argument_list|(
name|LOAD_PROC
argument_list|,
operator|&
name|dds_read_vals
argument_list|,
sizeof|sizeof
argument_list|(
name|dds_read_vals
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
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
name|imageID
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
name|drawableID
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
literal|"dds"
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|export
operator|=
name|gimp_export_image
argument_list|(
operator|&
name|imageID
argument_list|,
operator|&
name|drawableID
argument_list|,
literal|"DDS"
argument_list|,
operator|(
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
operator||
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
operator||
name|GIMP_EXPORT_CAN_HANDLE_LAYERS
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
name|gimp_get_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|dds_write_vals
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparams
operator|!=
name|G_N_ELEMENTS
argument_list|(
name|save_args
argument_list|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
else|else
block|{
name|dds_write_vals
operator|.
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
name|dds_write_vals
operator|.
name|mipmaps
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
name|dds_write_vals
operator|.
name|savetype
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
name|dds_write_vals
operator|.
name|format
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
name|dds_write_vals
operator|.
name|transindex
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
name|dds_write_vals
operator|.
name|mipmap_filter
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
name|dds_write_vals
operator|.
name|mipmap_wrap
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
name|dds_write_vals
operator|.
name|gamma_correct
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
name|dds_write_vals
operator|.
name|srgb
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
name|dds_write_vals
operator|.
name|gamma
operator|=
name|param
index|[
literal|14
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|dds_write_vals
operator|.
name|perceptual_metric
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
name|dds_write_vals
operator|.
name|preserve_alpha_coverage
operator|=
name|param
index|[
literal|16
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|dds_write_vals
operator|.
name|alpha_test_threshold
operator|=
name|param
index|[
literal|17
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
if|if
condition|(
operator|(
name|dds_write_vals
operator|.
name|compression
operator|<
name|DDS_COMPRESS_NONE
operator|)
operator|||
operator|(
name|dds_write_vals
operator|.
name|compression
operator|>=
name|DDS_COMPRESS_MAX
operator|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
operator|(
name|dds_write_vals
operator|.
name|mipmaps
operator|<
name|DDS_MIPMAP_NONE
operator|)
operator|||
operator|(
name|dds_write_vals
operator|.
name|mipmaps
operator|>=
name|DDS_MIPMAP_MAX
operator|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
operator|(
name|dds_write_vals
operator|.
name|savetype
operator|<
name|DDS_SAVE_SELECTED_LAYER
operator|)
operator|||
operator|(
name|dds_write_vals
operator|.
name|savetype
operator|>=
name|DDS_SAVE_MAX
operator|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
operator|(
name|dds_write_vals
operator|.
name|format
operator|<
name|DDS_FORMAT_DEFAULT
operator|)
operator|||
operator|(
name|dds_write_vals
operator|.
name|format
operator|>=
name|DDS_FORMAT_MAX
operator|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
operator|(
name|dds_write_vals
operator|.
name|mipmap_filter
operator|<
name|DDS_MIPMAP_FILTER_DEFAULT
operator|)
operator|||
operator|(
name|dds_write_vals
operator|.
name|mipmap_filter
operator|>=
name|DDS_MIPMAP_FILTER_MAX
operator|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
operator|(
name|dds_write_vals
operator|.
name|mipmap_wrap
operator|<
name|DDS_MIPMAP_WRAP_DEFAULT
operator|)
operator|||
operator|(
name|dds_write_vals
operator|.
name|mipmap_wrap
operator|>=
name|DDS_MIPMAP_WRAP_MAX
operator|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|dds_write_vals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|dds_write_vals
operator|.
name|gamma
operator|<
literal|1e-04f
condition|)
comment|/* gimp_gamma () got removed and was always returning 2.2 anyway.          * XXX Review this piece of code if we expect gamma value could          * be parameterized.          */
name|dds_write_vals
operator|.
name|gamma
operator|=
literal|2.2
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|status
operator|=
name|write_dds
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
name|imageID
argument_list|,
name|drawableID
argument_list|,
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|gimp_set_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|dds_write_vals
argument_list|,
sizeof|sizeof
argument_list|(
name|dds_write_vals
argument_list|)
argument_list|)
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
name|imageID
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|DECODE_YCOCG_PROC
argument_list|)
condition|)
block|{
name|imageID
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
name|drawableID
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
name|decode_ycocg_image
argument_list|(
name|drawableID
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|DECODE_YCOCG_SCALED_PROC
argument_list|)
condition|)
block|{
name|imageID
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
name|drawableID
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
name|decode_ycocg_scaled_image
argument_list|(
name|drawableID
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|DECODE_ALPHA_EXP_PROC
argument_list|)
condition|)
block|{
name|imageID
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
name|drawableID
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
name|decode_alpha_exp_image
argument_list|(
name|drawableID
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
else|else
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
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
name|status
expr_stmt|;
block|}
end_function

end_unit
