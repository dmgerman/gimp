begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* bmp.c                                          */
end_comment

begin_comment
comment|/* Version 0.52                                   */
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
comment|/* GIMP are taken from the GIF plugin by          */
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
comment|/*            21.03.1998 Little Bug-fix           */
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
comment|/*            29.06.2006 Full support for 16/32   */
end_comment

begin_comment
comment|/*                       bits bitmaps and support */
end_comment

begin_comment
comment|/*                       for alpha channel        */
end_comment

begin_comment
comment|/*                       by p.filiciak@zax.pl     */
end_comment

begin_comment
comment|/*  * GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  * ----------------------------------------------------------------------------  */
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
file|"bmp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
DECL|variable|filename
specifier|const
name|gchar
modifier|*
name|filename
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|interactive
name|gboolean
name|interactive
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|lastvals
name|gboolean
name|lastvals
init|=
name|FALSE
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
literal|"The name entered"
block|}
block|,   }
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|LOAD_PROC
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
name|N_
argument_list|(
literal|"Windows BMP image"
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
literal|"image/bmp"
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"bmp"
argument_list|,
literal|""
argument_list|,
literal|"0,string,BM"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|SAVE_PROC
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
name|N_
argument_list|(
literal|"Windows BMP image"
argument_list|)
argument_list|,
literal|"INDEXED, GRAY, RGB*"
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
literal|"image/bmp"
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
name|SAVE_PROC
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
name|interactive
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|!=
literal|3
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
name|interactive
operator|=
name|TRUE
expr_stmt|;
comment|/* fallthrough */
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_WITH_LAST_VALS
condition|)
name|lastvals
operator|=
name|TRUE
expr_stmt|;
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
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
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
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|!=
literal|5
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
argument_list|,
operator|&
name|error
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

end_unit

