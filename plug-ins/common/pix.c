begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Alias|Wavefront pix/matte image reading and writing code   * Copyright (C) 1997 Mike Taylor  * (email: mtaylor@aw.sgi.com, WWW: http://reality.sgi.com/mtaylor)  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_comment
comment|/* This plug-in was written using the online documentation from   * Alias|Wavefront Inc's PowerAnimator product.  *  * Bug reports or suggestions should be e-mailed to mtaylor@aw.sgi.com  */
end_comment

begin_comment
comment|/* Event history:  * V 1.0, MT, 02-Jul-97: initial version of plug-in  * V 1.1, MT, 04-Dec-97: added .als file extension   */
end_comment

begin_comment
comment|/* Features  *  - loads and saves  *    - 24-bit (.pix)   *    - 8-bit (.matte, .alpha, or .mask) images  *  * NOTE: pix and matte files do not support alpha channels or indexed  *       colour, so neither does this plug-in  */
end_comment

begin_decl_stmt
DECL|variable|ident
specifier|static
name|char
name|ident
index|[]
init|=
literal|"@(#) GIMP Alias|Wavefront pix image file-plugin v1.0  24-jun-97"
decl_stmt|;
end_decl_stmt

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
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
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
file|"libgimp/stdplugins-intl.h"
end_include

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
value|fprintf(stderr,a,b)
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

begin_comment
comment|/* Standard Plug-in Functions */
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

begin_comment
comment|/* Local Helper Functions */
end_comment

begin_function_decl
specifier|static
name|gint32
name|load_image
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|save_image
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|guint16
name|get_short
parameter_list|(
name|FILE
modifier|*
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|put_short
parameter_list|(
name|guint16
name|value
parameter_list|,
name|FILE
modifier|*
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|init_gtk
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/******************  * Implementation *  ******************/
end_comment

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
comment|/*    * Description:    *     Register the services provided by this plug-in     */
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
literal|"The name of the file to save the image in"
block|}
block|}
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
literal|"file_pix_load"
argument_list|,
name|_
argument_list|(
literal|"loads files of the PIX file format"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"loads files of the PIX file format"
argument_list|)
argument_list|,
literal|"Michael Taylor"
argument_list|,
literal|"Michael Taylor"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Load>/PIX"
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
literal|"file_pix_save"
argument_list|,
name|_
argument_list|(
literal|"save file in the Alias|Wavefront pix/matte file format"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"save file in the Alias|Wavefront pix/matte file format"
argument_list|)
argument_list|,
literal|"Michael Taylor"
argument_list|,
literal|"Michael Taylor"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Save>/PIX"
argument_list|,
literal|"RGB*, GRAY*"
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
name|gimp_register_load_handler
argument_list|(
literal|"file_pix_load"
argument_list|,
literal|"pix,matte,mask,alpha,als"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
literal|"file_pix_save"
argument_list|,
literal|"pix,matte,mask,alpha,als"
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
comment|/*     *  Description:    *      perform registered plug-in function     *    *  Arguments:    *      name         - name of the function to perform    *      nparams      - number of parameters passed to the function    *      param        - parameters passed to the function    *      nreturn_vals - number of parameters returned by the function    *      return_vals  - parameters returned by the function    */
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
literal|"file_pix_load"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/* Perform the image load */
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
comment|/* The image load falied */
name|status
operator|=
name|STATUS_EXECUTION_ERROR
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
literal|"file_pix_save"
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
name|RUN_INTERACTIVE
case|:
case|case
name|RUN_WITH_LAST_VALS
case|:
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
name|init_gtk
argument_list|()
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
operator|(
name|CAN_HANDLE_RGB
operator||
name|CAN_HANDLE_GRAY
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
name|INIT_I18N
argument_list|()
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
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
name|image_ID
argument_list|,
name|drawable_ID
argument_list|)
condition|)
block|{
name|status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
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
specifier|static
name|guint16
DECL|function|get_short (FILE * file)
name|get_short
parameter_list|(
name|FILE
modifier|*
name|file
parameter_list|)
block|{
comment|/*     * Description:    *     Reads a 16-bit integer from a file in such a way that the machine's    *     bit ordering should not matter     */
name|guchar
name|buf
index|[
literal|2
index|]
decl_stmt|;
name|fread
argument_list|(
name|buf
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
name|file
argument_list|)
expr_stmt|;
return|return
operator|(
name|buf
index|[
literal|0
index|]
operator|<<
literal|8
operator|)
operator|+
operator|(
name|buf
index|[
literal|1
index|]
operator|<<
literal|0
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|put_short (guint16 value,FILE * file)
name|put_short
parameter_list|(
name|guint16
name|value
parameter_list|,
name|FILE
modifier|*
name|file
parameter_list|)
block|{
comment|/*     * Description:    *     Reads a 16-bit integer from a file in such a way that the machine's    *     bit ordering should not matter     */
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
call|(
name|guchar
call|)
argument_list|(
name|value
operator|>>
literal|8
argument_list|)
expr_stmt|;
name|buf
index|[
literal|1
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|value
operator|%
literal|256
argument_list|)
expr_stmt|;
name|fwrite
argument_list|(
name|buf
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
name|file
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|load_image (gchar * filename)
name|load_image
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
comment|/*    *  Description:    *      load the given image into gimp    *     *  Arguments:    *      filename      - name on the file to read    *    *  Return Value:    *      Image id for the loaded image    *          */
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|tile_height
decl_stmt|,
name|row
decl_stmt|;
name|FILE
modifier|*
name|file
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|progMessage
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|guchar
modifier|*
name|dest_base
decl_stmt|;
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|gint32
name|layer_ID
decl_stmt|;
name|GPixelRgn
name|pixel_rgn
decl_stmt|;
name|gushort
name|width
decl_stmt|,
name|height
decl_stmt|,
name|depth
decl_stmt|;
name|GImageType
name|imgtype
decl_stmt|;
name|GDrawableType
name|gdtype
decl_stmt|;
comment|/* Set up progress display */
name|progMessage
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Loading %s:"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|progMessage
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|progMessage
argument_list|)
expr_stmt|;
name|PIX_DEBUG_PRINT
argument_list|(
literal|"Opening file: %s\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
comment|/* Open the file */
name|file
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
name|NULL
operator|==
name|file
condition|)
block|{
return|return
operator|-
literal|1
return|;
block|}
comment|/* Read header information */
name|width
operator|=
name|get_short
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|height
operator|=
name|get_short
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|get_short
argument_list|(
name|file
argument_list|)
expr_stmt|;
comment|/* Discard obsolete fields */
name|get_short
argument_list|(
name|file
argument_list|)
expr_stmt|;
comment|/* Discard obsolete fields */
name|depth
operator|=
name|get_short
argument_list|(
name|file
argument_list|)
expr_stmt|;
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
name|GRAY
expr_stmt|;
name|gdtype
operator|=
name|GRAY_IMAGE
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
name|RGB
expr_stmt|;
name|gdtype
operator|=
name|RGB_IMAGE
expr_stmt|;
block|}
else|else
block|{
comment|/* Header is invalid */
name|fclose
argument_list|(
name|file
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
name|gdtype
argument_list|,
literal|100
argument_list|,
name|NORMAL_MODE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image_ID
argument_list|,
name|layer_ID
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|layer_ID
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
name|guchar
name|record
index|[
literal|4
index|]
decl_stmt|;
name|gint
name|readlen
decl_stmt|;
name|tile_height
operator|=
name|gimp_tile_height
argument_list|()
expr_stmt|;
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
operator|+=
literal|1
operator|,
name|row
operator|+=
literal|1
control|)
block|{
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
name|readlen
operator|=
name|fread
argument_list|(
name|record
argument_list|,
literal|1
argument_list|,
literal|4
argument_list|,
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|readlen
operator|<
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
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|dest_base
argument_list|,
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
name|free
argument_list|(
name|dest_base
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Read an 8-bit Matte image */
name|guchar
name|record
index|[
literal|2
index|]
decl_stmt|;
name|gint
name|readlen
decl_stmt|;
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
operator|+=
literal|1
operator|,
name|row
operator|+=
literal|1
control|)
block|{
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
name|readlen
operator|=
name|fread
argument_list|(
name|record
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|readlen
operator|<
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
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|dest_base
argument_list|,
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
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|save_image (gchar * filename,gint32 image_ID,gint32 drawable_ID)
name|save_image
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
block|{
comment|/*   *  Description:  *      save the given file out as an alias pix or matte file  *   *  Arguments:   *      filename    - name of file to save to  *      image_ID    - ID of image to save  *      drawable_ID - current drawable  */
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
name|writelen
decl_stmt|,
name|rectHeight
decl_stmt|;
comment|/* gboolean   savingAlpha = FALSE; */
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
name|gchar
modifier|*
name|progMessage
decl_stmt|;
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|GPixelRgn
name|pixel_rgn
decl_stmt|;
name|FILE
modifier|*
name|file
decl_stmt|;
comment|/* Get info about image */
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
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable_ID
argument_list|)
condition|)
block|{
case|case
name|GRAY_IMAGE
case|:
name|savingColor
operator|=
name|FALSE
expr_stmt|;
name|depth
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|GRAYA_IMAGE
case|:
name|savingColor
operator|=
name|FALSE
expr_stmt|;
name|depth
operator|=
literal|2
expr_stmt|;
break|break;
case|case
name|RGB_IMAGE
case|:
name|savingColor
operator|=
name|TRUE
expr_stmt|;
name|depth
operator|=
literal|3
expr_stmt|;
break|break;
case|case
name|RGBA_IMAGE
case|:
name|savingColor
operator|=
name|TRUE
expr_stmt|;
name|depth
operator|=
literal|4
expr_stmt|;
break|break;
default|default:
return|return
name|FALSE
return|;
block|}
empty_stmt|;
comment|/* Open the output file. */
name|file
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"wb"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file
condition|)
return|return
name|FALSE
return|;
comment|/* Set up progress display */
name|progMessage
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Saving %s:"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|progMessage
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|progMessage
argument_list|)
expr_stmt|;
comment|/* Write the image header */
name|PIX_DEBUG_PRINT
argument_list|(
literal|"Width %hu\n"
argument_list|,
name|drawable
operator|->
name|width
argument_list|)
expr_stmt|;
name|PIX_DEBUG_PRINT
argument_list|(
literal|"Height %hu\n"
argument_list|,
name|drawable
operator|->
name|height
argument_list|)
expr_stmt|;
name|put_short
argument_list|(
name|drawable
operator|->
name|width
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|put_short
argument_list|(
name|drawable
operator|->
name|height
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|put_short
argument_list|(
literal|0
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|put_short
argument_list|(
literal|0
argument_list|,
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|savingColor
condition|)
block|{
name|put_short
argument_list|(
literal|24
argument_list|,
name|file
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|put_short
argument_list|(
literal|8
argument_list|,
name|file
argument_list|)
expr_stmt|;
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
name|drawable
operator|->
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
name|guchar
name|record
index|[
literal|4
index|]
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|drawable
operator|->
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
name|drawable
operator|->
name|height
operator|-
name|i
operator|-
literal|1
operator|)
operator|)
condition|?
name|tile_height
else|:
operator|(
name|drawable
operator|->
name|height
operator|-
name|i
operator|-
literal|1
operator|)
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|src_base
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|rectHeight
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
name|drawable
operator|->
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
name|drawable
operator|->
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
name|writelen
operator|=
name|fwrite
argument_list|(
name|record
argument_list|,
literal|1
argument_list|,
literal|4
argument_list|,
name|file
argument_list|)
expr_stmt|;
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
name|writelen
operator|=
name|fwrite
argument_list|(
name|record
argument_list|,
literal|1
argument_list|,
literal|4
argument_list|,
name|file
argument_list|)
expr_stmt|;
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
name|drawable
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/* Writing a 8-bit Matte (Mask) image */
name|guchar
name|record
index|[
literal|2
index|]
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|drawable
operator|->
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
name|drawable
operator|->
name|height
operator|-
name|i
operator|-
literal|1
operator|)
operator|)
condition|?
name|tile_height
else|:
operator|(
name|drawable
operator|->
name|height
operator|-
name|i
operator|-
literal|1
operator|)
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|src_base
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|rectHeight
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
name|drawable
operator|->
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
name|drawable
operator|->
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
name|writelen
operator|=
name|fwrite
argument_list|(
name|record
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|file
argument_list|)
expr_stmt|;
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
name|writelen
operator|=
name|fwrite
argument_list|(
name|record
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|file
argument_list|)
expr_stmt|;
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
name|drawable
operator|->
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
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|init_gtk (void)
name|init_gtk
parameter_list|(
name|void
parameter_list|)
block|{
name|gchar
modifier|*
modifier|*
name|argv
decl_stmt|;
name|gint
name|argc
decl_stmt|;
name|argc
operator|=
literal|1
expr_stmt|;
name|argv
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|argv
index|[
literal|0
index|]
operator|=
name|g_strdup
argument_list|(
literal|"pix"
argument_list|)
expr_stmt|;
name|gtk_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
expr_stmt|;
name|gtk_rc_parse
argument_list|(
name|gimp_gtkrc
argument_list|()
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

