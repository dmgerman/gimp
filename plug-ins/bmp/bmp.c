begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* bmp.c                                          */
end_comment

begin_comment
comment|/* Version 0.51	                                  */
end_comment

begin_comment
comment|/* This is a File input and output filter for the */
end_comment

begin_comment
comment|/* Gimp. It loads and saves images in windows(TM) */
end_comment

begin_comment
comment|/* bitmap format.                                 */
end_comment

begin_comment
comment|/* Some Parts that deal with the interaction with */
end_comment

begin_comment
comment|/* the Gimp are taken from the GIF plugin by      */
end_comment

begin_comment
comment|/* Peter Mattis& Spencer Kimball and from the    */
end_comment

begin_comment
comment|/* PCX plugin by Francisco Bustamante.            */
end_comment

begin_comment
comment|/*                                                */
end_comment

begin_comment
comment|/* Alexander.Schulz@stud.uni-karlsruhe.de         */
end_comment

begin_comment
comment|/* Changes:   28.11.1997 Noninteractive operation */
end_comment

begin_comment
comment|/*            16.03.1998 Endian-independent!!     */
end_comment

begin_comment
comment|/*	      21.03.1998 Little Bug-fix		  */
end_comment

begin_comment
comment|/*            06.04.1998 Bugfix in Padding        */
end_comment

begin_comment
comment|/*            11.04.1998 Arch. cleanup (-Wall)    */
end_comment

begin_comment
comment|/*                       Parses gtkrc             */
end_comment

begin_comment
comment|/*            14.04.1998 Another Bug in Padding   */
end_comment

begin_comment
comment|/*            28.04.1998 RLE-Encoding rewritten   */
end_comment

begin_comment
comment|/*            29.10.1998 Changes by Tor Lillqvist */
end_comment

begin_comment
comment|/*<tml@iki.fi> to support  */
end_comment

begin_comment
comment|/*                       16 and 32 bit images     */
end_comment

begin_comment
comment|/*            28.11.1998 Bug in RLE-read-padding  */
end_comment

begin_comment
comment|/*                       fixed.                   */
end_comment

begin_comment
comment|/*            19.12.1999 Resolution support added */
end_comment

begin_comment
comment|/*            06.05.2000 Overhaul for 16&24-bit   */
end_comment

begin_comment
comment|/*                       plus better OS/2 code    */
end_comment

begin_comment
comment|/*                       by njl195@zepler.org.uk  */
end_comment

begin_comment
comment|/*   * The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  * ----------------------------------------------------------------------------  */
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
file|"bmp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
DECL|variable|errorfile
name|FILE
modifier|*
name|errorfile
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|prog_name
name|gchar
modifier|*
name|prog_name
init|=
literal|"bmp"
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|interactive_bmp
name|gint
name|interactive_bmp
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|Bitmap_File_Head
name|struct
name|Bitmap_File_Head_Struct
name|Bitmap_File_Head
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|Bitmap_Head
name|struct
name|Bitmap_Head_Struct
name|Bitmap_Head
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Declare some local functions.  */
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
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GPlugInInfo
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
name|GParamDef
name|load_args
index|[]
init|=
block|{
block|{
name|PARAM_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to load"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name entered"
block|}
block|,   }
decl_stmt|;
specifier|static
name|GParamDef
name|load_return_vals
index|[]
init|=
block|{
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"Output image"
block|}
block|,   }
decl_stmt|;
specifier|static
name|gint
name|nload_args
init|=
sizeof|sizeof
argument_list|(
name|load_args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|load_args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
specifier|static
name|gint
name|nload_return_vals
init|=
operator|(
sizeof|sizeof
argument_list|(
name|load_return_vals
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|load_return_vals
index|[
literal|0
index|]
argument_list|)
operator|)
decl_stmt|;
specifier|static
name|GParamDef
name|save_args
index|[]
init|=
block|{
block|{
name|PARAM_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Drawable to save"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name entered"
block|}
block|,   }
decl_stmt|;
specifier|static
name|gint
name|nsave_args
init|=
sizeof|sizeof
argument_list|(
name|save_args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|save_args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_bmp_load"
argument_list|,
literal|"Loads files of Windows BMP file format"
argument_list|,
literal|"Loads files of Windows BMP file format"
argument_list|,
literal|"Alexander Schulz"
argument_list|,
literal|"Alexander Schulz"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Load>/BMP"
argument_list|,
name|NULL
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|nload_args
argument_list|,
name|nload_return_vals
argument_list|,
name|load_args
argument_list|,
name|load_return_vals
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_bmp_save"
argument_list|,
literal|"Saves files in Windows BMP file format"
argument_list|,
literal|"Saves files in Windows BMP file format"
argument_list|,
literal|"Alexander Schulz"
argument_list|,
literal|"Alexander Schulz"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Save>/BMP"
argument_list|,
literal|"INDEXED, GRAY, RGB"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|nsave_args
argument_list|,
literal|0
argument_list|,
name|save_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
literal|"file_bmp_load"
argument_list|,
literal|"bmp"
argument_list|,
literal|""
argument_list|,
literal|"0,string,BM"
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
literal|"file_bmp_save"
argument_list|,
literal|"bmp"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (gchar * name,gint nparams,GParam * param,gint * nreturn_vals,GParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GParam
name|values
index|[
literal|2
index|]
decl_stmt|;
name|GRunModeType
name|run_mode
decl_stmt|;
name|GStatusType
name|status
init|=
name|STATUS_SUCCESS
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|gint32
name|drawable_ID
decl_stmt|;
name|GimpExportReturnType
name|export
init|=
name|EXPORT_CANCEL
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
name|PARAM_STATUS
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
name|STATUS_EXECUTION_ERROR
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file_bmp_load"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|INIT_I18N
argument_list|()
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|RUN_INTERACTIVE
case|:
name|interactive_bmp
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|RUN_NONINTERACTIVE
case|:
comment|/*  Make sure all the arguments are there!  */
name|interactive_bmp
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|nparams
operator|!=
literal|3
condition|)
name|status
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
name|image_ID
operator|=
name|ReadBMP
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
name|PARAM_IMAGE
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
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file_bmp_save"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|INIT_I18N
argument_list|()
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
comment|/*  eventually export the image */
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|RUN_INTERACTIVE
case|:
case|case
name|RUN_WITH_LAST_VALS
case|:
name|gimp_ui_init
argument_list|(
literal|"bmp"
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
literal|"BMP"
argument_list|,
operator|(
name|CAN_HANDLE_RGB
operator||
name|CAN_HANDLE_GRAY
operator||
name|CAN_HANDLE_INDEXED
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|export
operator|==
name|EXPORT_CANCEL
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
name|STATUS_CANCEL
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
name|RUN_INTERACTIVE
case|:
name|interactive_bmp
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|RUN_NONINTERACTIVE
case|:
comment|/*  Make sure all the arguments are there!  */
name|interactive_bmp
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|nparams
operator|!=
literal|5
condition|)
name|status
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
break|break;
case|case
name|RUN_WITH_LAST_VALS
case|:
name|interactive_bmp
operator|=
name|FALSE
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
name|status
operator|=
name|WriteBMP
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
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|export
operator|==
name|EXPORT_EXPORT
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
name|STATUS_CALLING_ERROR
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
name|gint32
DECL|function|ToL (guchar * puffer)
name|ToL
parameter_list|(
name|guchar
modifier|*
name|puffer
parameter_list|)
block|{
return|return
operator|(
name|puffer
index|[
literal|0
index|]
operator||
name|puffer
index|[
literal|1
index|]
operator|<<
literal|8
operator||
name|puffer
index|[
literal|2
index|]
operator|<<
literal|16
operator||
name|puffer
index|[
literal|3
index|]
operator|<<
literal|24
operator|)
return|;
block|}
end_function

begin_function
name|gint16
DECL|function|ToS (guchar * puffer)
name|ToS
parameter_list|(
name|guchar
modifier|*
name|puffer
parameter_list|)
block|{
return|return
operator|(
name|puffer
index|[
literal|0
index|]
operator||
name|puffer
index|[
literal|1
index|]
operator|<<
literal|8
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|FromL (gint32 wert,guchar * bopuffer)
name|FromL
parameter_list|(
name|gint32
name|wert
parameter_list|,
name|guchar
modifier|*
name|bopuffer
parameter_list|)
block|{
name|bopuffer
index|[
literal|0
index|]
operator|=
operator|(
name|wert
operator|&
literal|0x000000ff
operator|)
operator|>>
literal|0x00
expr_stmt|;
name|bopuffer
index|[
literal|1
index|]
operator|=
operator|(
name|wert
operator|&
literal|0x0000ff00
operator|)
operator|>>
literal|0x08
expr_stmt|;
name|bopuffer
index|[
literal|2
index|]
operator|=
operator|(
name|wert
operator|&
literal|0x00ff0000
operator|)
operator|>>
literal|0x10
expr_stmt|;
name|bopuffer
index|[
literal|3
index|]
operator|=
operator|(
name|wert
operator|&
literal|0xff000000
operator|)
operator|>>
literal|0x18
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|FromS (gint16 wert,guchar * bopuffer)
name|FromS
parameter_list|(
name|gint16
name|wert
parameter_list|,
name|guchar
modifier|*
name|bopuffer
parameter_list|)
block|{
name|bopuffer
index|[
literal|0
index|]
operator|=
operator|(
name|wert
operator|&
literal|0x00ff
operator|)
operator|>>
literal|0x00
expr_stmt|;
name|bopuffer
index|[
literal|1
index|]
operator|=
operator|(
name|wert
operator|&
literal|0xff00
operator|)
operator|>>
literal|0x08
expr_stmt|;
block|}
end_function

end_unit

