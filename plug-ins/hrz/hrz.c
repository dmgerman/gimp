begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * HRZ reading and writing code Copyright (C) 1996 Albert Cahalan  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_comment
comment|/* $Id$ */
end_comment

begin_comment
comment|/*  * Albert Cahalan<acahalan at cs.uml.edu>, 1997  -  Initial HRZ support.  * Based on PNM code by Erik Nygren (nygren@mit.edu)  *  * Bug reports are wanted. I'd like to remove useless code.  *  * The HRZ file is always 256x240 with RGB values from 0 to 63.  * No compression, no header, just the raw RGB data.  * It is (was?) used for amatuer radio slow-scan TV.  * That makes the size 256*240*3 = 184320 bytes.  */
end_comment

begin_include
include|#
directive|include
file|<setjmp.h>
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
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_include
include|#
directive|include
file|<ctype.h>
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
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_include
include|#
directive|include
file|<sys/mman.h>
end_include

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_comment
comment|/* Declare local data types  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29377a530108
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
comment|/*  run  */
DECL|typedef|HRZSaveInterface
block|}
name|HRZSaveInterface
typedef|;
end_typedef

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
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|int
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

begin_function_decl
specifier|static
name|gint32
name|load_image
parameter_list|(
name|char
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
name|char
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
name|gint
name|save_dialog
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|save_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|save_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* static void   save_toggle_update       (GtkWidget *widget, 					gpointer   data); */
end_comment

begin_define
DECL|macro|hrzscanner_eof (s)
define|#
directive|define
name|hrzscanner_eof
parameter_list|(
name|s
parameter_list|)
value|((s)->eof)
end_define

begin_define
DECL|macro|hrzscanner_fp (s)
define|#
directive|define
name|hrzscanner_fp
parameter_list|(
name|s
parameter_list|)
value|((s)->fp)
end_define

begin_comment
comment|/* Checks for a fatal error */
end_comment

begin_define
DECL|macro|CHECK_FOR_ERROR (predicate,jmpbuf,errmsg)
define|#
directive|define
name|CHECK_FOR_ERROR
parameter_list|(
name|predicate
parameter_list|,
name|jmpbuf
parameter_list|,
name|errmsg
parameter_list|)
define|\
value|if ((predicate)) \         {
comment|/*gimp_message((errmsg));*/
value|longjmp((jmpbuf),1); }
end_define

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GPlugInInfo
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
comment|/* query_proc */
name|run
block|,
comment|/* run_proc */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|psint
specifier|static
name|HRZSaveInterface
name|psint
init|=
block|{
name|FALSE
comment|/* run */
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
parameter_list|()
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
literal|"The name of the file to load"
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
name|int
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
name|int
name|nload_return_vals
init|=
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
name|int
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
name|gimp_install_procedure
argument_list|(
literal|"file_hrz_load"
argument_list|,
literal|"loads files of the hrz file format"
argument_list|,
literal|"FIXME: write help for hrz_load"
argument_list|,
literal|"Albert Cahalan"
argument_list|,
literal|"Albert Cahalan"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Load>/HRZ"
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
literal|"file_hrz_save"
argument_list|,
literal|"saves files in the hrz file format"
argument_list|,
literal|"HRZ saving handles all image types except those with alpha channels."
argument_list|,
literal|"Albert Cahalan"
argument_list|,
literal|"Albert Cahalan"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Save>/HRZ"
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
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
literal|"file_hrz_load"
argument_list|,
literal|"hrz"
argument_list|,
literal|""
argument_list|,
literal|"0,size,184320"
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
literal|"file_hrz_save"
argument_list|,
literal|"hrz"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (char * name,int nparams,GParam * param,int * nreturn_vals,GParam ** return_vals)
name|run
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|int
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
name|STATUS_CALLING_ERROR
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file_hrz_load"
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
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_SUCCESS
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
block|}
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file_hrz_save"
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
name|RUN_INTERACTIVE
case|:
comment|/*  First acquire information with a dialog  */
if|if
condition|(
operator|!
name|save_dialog
argument_list|()
condition|)
return|return;
break|break;
case|case
name|RUN_NONINTERACTIVE
case|:
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|!=
literal|4
condition|)
name|status
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
case|case
name|RUN_WITH_LAST_VALS
case|:
break|break;
default|default:
break|break;
block|}
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
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
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
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
name|STATUS_SUCCESS
expr_stmt|;
block|}
else|else
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
block|}
block|}
end_function

begin_comment
comment|/************ load HRZ image row *********************/
end_comment

begin_function
name|void
DECL|function|do_hrz_load (void * mapped,GPixelRgn * pixel_rgn)
name|do_hrz_load
parameter_list|(
name|void
modifier|*
name|mapped
parameter_list|,
name|GPixelRgn
modifier|*
name|pixel_rgn
parameter_list|)
block|{
name|unsigned
name|char
modifier|*
name|data
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
name|int
name|start
decl_stmt|,
name|end
decl_stmt|,
name|scanlines
decl_stmt|;
name|data
operator|=
name|g_malloc
argument_list|(
name|gimp_tile_height
argument_list|()
operator|*
literal|256
operator|*
literal|3
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
literal|240
condition|;
control|)
block|{
name|start
operator|=
name|y
expr_stmt|;
name|end
operator|=
name|y
operator|+
name|gimp_tile_height
argument_list|()
expr_stmt|;
name|end
operator|=
name|MIN
argument_list|(
name|end
argument_list|,
literal|240
argument_list|)
expr_stmt|;
name|scanlines
operator|=
name|end
operator|-
name|start
expr_stmt|;
name|d
operator|=
name|data
expr_stmt|;
name|memcpy
argument_list|(
name|d
argument_list|,
operator|(
operator|(
name|unsigned
name|char
operator|*
operator|)
name|mapped
operator|)
operator|+
literal|256
operator|*
literal|3
operator|*
name|y
argument_list|,
literal|256
operator|*
literal|3
operator|*
name|scanlines
argument_list|)
expr_stmt|;
comment|/* this is gross */
comment|/* scale 0..63 into 0..255 properly */
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
literal|256
operator|*
literal|3
operator|*
name|scanlines
condition|;
name|x
operator|++
control|)
name|d
index|[
name|x
index|]
operator|=
operator|(
name|d
index|[
name|x
index|]
operator|>>
literal|4
operator|)
operator||
operator|(
name|d
index|[
name|x
index|]
operator|<<
literal|2
operator|)
expr_stmt|;
name|d
operator|+=
literal|256
operator|*
literal|3
operator|*
name|y
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|y
operator|/
literal|240.0
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_rect
argument_list|(
name|pixel_rgn
argument_list|,
name|data
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
literal|256
argument_list|,
name|scanlines
argument_list|)
expr_stmt|;
name|y
operator|+=
name|scanlines
expr_stmt|;
block|}
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/********************* Load HRZ image **********************/
end_comment

begin_function
specifier|static
name|gint32
DECL|function|load_image (char * filename)
name|load_image
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
block|{
name|GPixelRgn
name|pixel_rgn
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|gint32
name|layer_ID
decl_stmt|;
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|int
name|filedes
decl_stmt|;
name|char
modifier|*
name|temp
decl_stmt|;
name|void
modifier|*
name|mapped
decl_stmt|;
comment|/* memory mapped file data */
name|struct
name|stat
name|statbuf
decl_stmt|;
comment|/* must check file size */
name|temp
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|filename
argument_list|)
operator|+
literal|11
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|temp
argument_list|,
literal|"Loading %s:"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|temp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
comment|/* open the file */
name|filedes
operator|=
name|open
argument_list|(
name|filename
argument_list|,
name|O_RDONLY
argument_list|)
expr_stmt|;
if|if
condition|(
name|filedes
operator|==
operator|-
literal|1
condition|)
block|{
comment|/* errno is set to indicate the error, but the user won't know :-( */
comment|/*gimp_message("hrz filter: can't open file\n");*/
return|return
operator|-
literal|1
return|;
block|}
comment|/* stat the file to see if it is the right size */
name|fstat
argument_list|(
name|filedes
argument_list|,
operator|&
name|statbuf
argument_list|)
expr_stmt|;
if|if
condition|(
name|statbuf
operator|.
name|st_size
operator|!=
literal|256
operator|*
literal|240
operator|*
literal|3
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"hrz filter: file is not HRZ type\n"
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|mapped
operator|=
name|mmap
argument_list|(
name|NULL
argument_list|,
literal|256
operator|*
literal|240
operator|*
literal|3
argument_list|,
name|PROT_READ
argument_list|,
name|MAP_PRIVATE
argument_list|,
name|filedes
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|mapped
operator|==
operator|(
name|void
operator|*
operator|)
operator|(
operator|-
literal|1
operator|)
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"hrz filter: could not map file\n"
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|close
argument_list|(
name|filedes
argument_list|)
expr_stmt|;
comment|/* not needed anymore, data is memory mapped */
comment|/* Create new image of proper size; associate filename */
name|image_ID
operator|=
name|gimp_image_new
argument_list|(
literal|256
argument_list|,
literal|240
argument_list|,
name|RGB
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
literal|"Background"
argument_list|,
literal|256
argument_list|,
literal|240
argument_list|,
name|RGB_IMAGE
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
name|do_hrz_load
argument_list|(
name|mapped
argument_list|,
operator|&
name|pixel_rgn
argument_list|)
expr_stmt|;
comment|/* close the file */
name|munmap
argument_list|(
name|mapped
argument_list|,
literal|256
operator|*
literal|240
operator|*
literal|3
argument_list|)
expr_stmt|;
comment|/* Tell the GIMP to display the image.    */
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

begin_comment
comment|/************** Writes out RGB raw rows ************/
end_comment

begin_function
specifier|static
name|void
DECL|function|saverow (FILE * fp,unsigned char * data)
name|saverow
parameter_list|(
name|FILE
modifier|*
name|fp
parameter_list|,
name|unsigned
name|char
modifier|*
name|data
parameter_list|)
block|{
name|int
name|loop
init|=
literal|256
operator|*
literal|3
decl_stmt|;
name|unsigned
name|char
modifier|*
name|walk
init|=
name|data
decl_stmt|;
while|while
condition|(
name|loop
operator|--
condition|)
block|{
operator|*
name|walk
operator|=
operator|(
operator|*
name|walk
operator|>>
literal|2
operator|)
expr_stmt|;
name|walk
operator|++
expr_stmt|;
block|}
name|fwrite
argument_list|(
name|data
argument_list|,
literal|1
argument_list|,
literal|256
operator|*
literal|3
argument_list|,
name|fp
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/********************* save image *********************/
end_comment

begin_function
specifier|static
name|gint
DECL|function|save_image (char * filename,gint32 image_ID,gint32 drawable_ID)
name|save_image
parameter_list|(
name|char
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
name|GPixelRgn
name|pixel_rgn
decl_stmt|;
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|GDrawableType
name|drawable_type
decl_stmt|;
name|unsigned
name|char
modifier|*
name|data
decl_stmt|;
name|unsigned
name|char
modifier|*
name|d
decl_stmt|;
comment|/* FIX */
name|unsigned
name|char
modifier|*
name|rowbuf
decl_stmt|;
name|char
modifier|*
name|temp
decl_stmt|;
name|int
name|np
init|=
literal|3
decl_stmt|;
name|int
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|int
name|ypos
decl_stmt|,
name|yend
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
comment|/* initialize */
name|d
operator|=
name|NULL
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|drawable_type
operator|=
name|gimp_drawable_type
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
comment|/*  Make sure we're not saving an image with an alpha channel  */
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable_ID
argument_list|)
condition|)
block|{
comment|/* gimp_message ("HRZ save cannot handle images with alpha channels.");  */
return|return
name|FALSE
return|;
block|}
comment|/* open the file */
name|fp
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
name|fp
operator|==
name|NULL
condition|)
block|{
comment|/* Ought to pass errno back... */
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"hrz: can't open \"%s\"\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|xres
operator|=
name|drawable
operator|->
name|width
expr_stmt|;
name|yres
operator|=
name|drawable
operator|->
name|height
expr_stmt|;
if|if
condition|(
operator|(
name|xres
operator|!=
literal|256
operator|)
operator|||
operator|(
name|yres
operator|!=
literal|240
operator|)
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"hrz: Image must be 256x240 for HRZ format.\n"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|drawable_type
operator|==
name|INDEXED_IMAGE
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"hrz: Image must be RGB for HRZ format.\n"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|temp
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|filename
argument_list|)
operator|+
literal|11
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|temp
argument_list|,
literal|"Saving %s:"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|temp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
comment|/* allocate a buffer for retrieving information from the pixel region  */
name|data
operator|=
operator|(
name|unsigned
name|char
operator|*
operator|)
name|g_malloc
argument_list|(
name|gimp_tile_height
argument_list|()
operator|*
name|drawable
operator|->
name|width
operator|*
name|drawable
operator|->
name|bpp
argument_list|)
expr_stmt|;
name|rowbuf
operator|=
name|g_malloc
argument_list|(
literal|256
operator|*
literal|3
argument_list|)
expr_stmt|;
comment|/* Write the body out */
for|for
control|(
name|ypos
operator|=
literal|0
init|;
name|ypos
operator|<
name|yres
condition|;
name|ypos
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|ypos
operator|%
name|gimp_tile_height
argument_list|()
operator|)
operator|==
literal|0
condition|)
block|{
name|yend
operator|=
name|ypos
operator|+
name|gimp_tile_height
argument_list|()
expr_stmt|;
name|yend
operator|=
name|MIN
argument_list|(
name|yend
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|data
argument_list|,
literal|0
argument_list|,
name|ypos
argument_list|,
name|xres
argument_list|,
operator|(
name|yend
operator|-
name|ypos
operator|)
argument_list|)
expr_stmt|;
name|d
operator|=
name|data
expr_stmt|;
block|}
name|saverow
argument_list|(
name|fp
argument_list|,
name|d
argument_list|)
expr_stmt|;
name|d
operator|+=
name|xres
operator|*
name|np
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|ypos
operator|&
literal|0x0f
operator|)
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|ypos
operator|/
literal|240.0
argument_list|)
expr_stmt|;
block|}
comment|/* close the file */
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rowbuf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*********** Save dialog ************/
end_comment

begin_function
specifier|static
name|gint
DECL|function|save_dialog ()
name|save_dialog
parameter_list|()
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
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
literal|"save"
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
name|dlg
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dlg
argument_list|)
argument_list|,
literal|"Save as HRZ"
argument_list|)
expr_stmt|;
name|gtk_window_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dlg
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dlg
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|save_close_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Action area  */
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|"OK"
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|save_ok_callback
argument_list|,
name|dlg
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_grab_default
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|"Cancel"
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gtk_widget_destroy
argument_list|,
name|GTK_OBJECT
argument_list|(
name|dlg
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
return|return
name|psint
operator|.
name|run
return|;
block|}
end_function

begin_comment
comment|/**********  Save interface functions  **********/
end_comment

begin_function
specifier|static
name|void
DECL|function|save_close_callback (GtkWidget * widget,gpointer data)
name|save_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|save_ok_callback (GtkWidget * widget,gpointer data)
name|save_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|psint
operator|.
name|run
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* static void save_toggle_update (GtkWidget *widget, 		    gpointer   data) {   int *toggle_val;    toggle_val = (int *) data;    if (GTK_TOGGLE_BUTTON (widget)->active)     *toggle_val = TRUE;   else     *toggle_val = FALSE; } */
end_comment

end_unit

