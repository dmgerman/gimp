begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Plugin to load MPEG movies. (C) 1997-99 Adam D. Moss  *  * v1.1 - by Adam D. Moss, adam@gimp.org, adam@foxbox.org  * Requires mpeg_lib by Gregory P. Ward.  See notes below for  * obtaining and patching mpeg_lib.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*******************************************************************  * USING MPEG_LIB WITH THIS PLUGIN:  mpeg_lib 1.2.1 can be found   *  * at ftp://ftp.mni.mcgill.ca/pub/mpeg/ - however, mpeg_lib 1.2.x  *  * contains a bug in end-of-stream reporting, which will cause it  *  * to crash in conjunction with this plugin.  I enclose a simple   *  * patch below which fixes the problem (or at least the symptom.;))*  *******************************************************************  *    Addendum: mpeg_lib 1.3.0 is now released and much better!    *  *******************************************************************/
end_comment

begin_comment
comment|/******************************************************************* *** wrapper.c   Tue Oct 10 22:08:39 1995 --- ../mpeg_lib2/wrapper.c      Sat Sep 20 20:29:46 1997 *************** *** 392,394 ****             "copying from %08X to %08X\n", CurrentImage, Frame); !    memcpy (Frame, CurrentImage, ImageInfo.Size);      return (!MovieDone); --- 392,397 ----             "copying from %08X to %08X\n", CurrentImage, Frame); ! !    if (!MovieDone) !       memcpy (Frame, CurrentImage, ImageInfo.Size); !      return (!MovieDone); *******************************************************************/
end_comment

begin_comment
comment|/*  * Changelog:  *  * 99/05/31  * v1.1: Endianness fix.  *  * 97/09/21  * v1.0: Initial release. [Adam]  */
end_comment

begin_comment
comment|/*  * TODO:  *  * More robustness for broken streams (how much co-operation  *   from mpeg_lib?)  *  * Saving (eventually...)  *  * Crop images properly (e.g. height&~7 ?)  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_include
include|#
directive|include
file|"mpeg.h"
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
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_mpeg_load"
argument_list|,
name|_
argument_list|(
literal|"Loads MPEG movies"
argument_list|)
argument_list|,
literal|"FIXME: write help for mpeg_load"
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Load>/MPEG"
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
name|gimp_register_load_handler
argument_list|(
literal|"file_mpeg_load"
argument_list|,
literal|"mpg,mpeg"
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
name|INIT_I18N
argument_list|()
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file_mpeg_load"
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
name|gint
DECL|function|MPEG_frame_period_ms (gint mpeg_rate_code)
name|MPEG_frame_period_ms
parameter_list|(
name|gint
name|mpeg_rate_code
parameter_list|)
block|{
switch|switch
condition|(
name|mpeg_rate_code
condition|)
block|{
case|case
literal|1
case|:
return|return
literal|44
return|;
comment|/* ~23 fps */
case|case
literal|2
case|:
return|return
literal|42
return|;
comment|/*  24 fps */
case|case
literal|3
case|:
return|return
literal|40
return|;
comment|/*  25 fps */
case|case
literal|4
case|:
return|return
literal|33
return|;
comment|/* ~30 fps */
case|case
literal|5
case|:
return|return
literal|33
return|;
comment|/*  30 fps */
case|case
literal|6
case|:
return|return
literal|20
return|;
comment|/*  50 fps */
case|case
literal|7
case|:
return|return
literal|17
return|;
comment|/* ~60 fps */
case|case
literal|8
case|:
return|return
literal|17
return|;
comment|/*  60 fps */
case|case
literal|0
case|:
comment|/* ? */
default|default:
name|printf
argument_list|(
literal|"mpeg: warning - this MPEG has undefined timing.\n"
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
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
name|GPixelRgn
name|pixel_rgn
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
name|gchar
modifier|*
name|temp
decl_stmt|;
name|Boolean
name|moreframes
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|framenumber
decl_stmt|,
name|delay
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|gint
name|wwidth
decl_stmt|,
name|wheight
decl_stmt|;
comment|/* mpeg structure */
name|ImageDesc
name|img
decl_stmt|;
name|gchar
modifier|*
name|layername
decl_stmt|;
comment|/* FIXME? */
name|temp
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|filename
argument_list|)
operator|+
literal|16
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|temp
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
name|g_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Loading MPEG movie..."
argument_list|)
argument_list|)
expr_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"rb"
argument_list|)
expr_stmt|;
if|if
condition|(
name|fp
operator|==
name|NULL
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"mpeg: fopen failed\n"
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|4
argument_list|)
expr_stmt|;
block|}
name|SetMPEGOption
argument_list|(
name|MPEG_DITHER
argument_list|,
name|FULL_COLOR_DITHER
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|OpenMPEG
argument_list|(
name|fp
argument_list|,
operator|&
name|img
argument_list|)
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"mpeg: OpenMPEG failed\n"
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
name|data
operator|=
name|g_malloc
argument_list|(
name|img
operator|.
name|Size
argument_list|)
expr_stmt|;
name|delay
operator|=
name|MPEG_frame_period_ms
argument_list|(
name|img
operator|.
name|PictureRate
argument_list|)
expr_stmt|;
comment|/*   printf("<%d : %d>  %dx%d - d%d - bmp%d - ps%d - s%d\n", 	 img.PictureRate, MPEG_frame_period_ms(img.PictureRate), 	 img.Width,img.Height,img.Depth,img.BitmapPad,img.PixelSize,img.Size); 	 */
if|if
condition|(
name|img
operator|.
name|PixelSize
operator|!=
literal|32
condition|)
block|{
name|printf
argument_list|(
literal|"mpeg: Hmm, sorry, funny PixelSize (%d) in MPEG.  Aborting.\n"
argument_list|,
name|img
operator|.
name|PixelSize
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|2
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|img
operator|.
name|BitmapPad
operator|!=
literal|32
condition|)
block|{
name|printf
argument_list|(
literal|"mpeg: Hmm, sorry, funny BitmapPad (%d) in MPEG.  Aborting.\n"
argument_list|,
name|img
operator|.
name|BitmapPad
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|3
argument_list|)
expr_stmt|;
block|}
name|wwidth
operator|=
name|img
operator|.
name|Width
expr_stmt|;
name|wheight
operator|=
name|img
operator|.
name|Height
expr_stmt|;
name|image_ID
operator|=
name|gimp_image_new
argument_list|(
name|wwidth
argument_list|,
name|wheight
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
name|moreframes
operator|=
name|TRUE
expr_stmt|;
name|framenumber
operator|=
literal|1
expr_stmt|;
while|while
condition|(
name|moreframes
condition|)
block|{
name|gimp_progress_update
argument_list|(
operator|(
name|framenumber
operator|&
literal|1
operator|)
condition|?
literal|1.0
else|:
literal|0.0
argument_list|)
expr_stmt|;
comment|/* libmpeg - at least the version I have (1.2) - is faulty          in its reporting of whether there are remaining frames... 	 the sample MPEG it comes with is the only one that it seems 	 able to detect the end of, and even then it doesn't notice 	 until it's too late, so we may lose the last frame, or 	 crash... sigh.  	 A patch to mpeg_lib 1.2.x is included in the header of this 	 plugin.  	 */
name|moreframes
operator|=
name|GetMPEGFrame
argument_list|(
operator|(
name|char
operator|*
operator|)
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|moreframes
condition|)
break|break;
if|if
condition|(
name|delay
operator|>
literal|0
condition|)
name|layername
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Frame %d (%dms)"
argument_list|)
argument_list|,
name|framenumber
argument_list|,
name|delay
argument_list|)
expr_stmt|;
else|else
name|layername
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Frame %d"
argument_list|)
argument_list|,
name|framenumber
argument_list|)
expr_stmt|;
name|layer_ID
operator|=
name|gimp_layer_new
argument_list|(
name|image_ID
argument_list|,
name|layername
argument_list|,
name|wwidth
argument_list|,
name|wheight
argument_list|,
name|RGBA_IMAGE
argument_list|,
literal|100
argument_list|,
name|NORMAL_MODE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|layername
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
comment|/* conveniently for us, mpeg_lib returns pixels padded 	 to 32-bit boundaries (is that true for all archs?).  So we 	 only have to fill in the alpha channel. */
for|for
control|(
name|i
operator|=
operator|(
name|wwidth
operator|*
name|wheight
operator|)
operator|-
literal|1
init|;
name|i
operator|>=
literal|0
condition|;
name|i
operator|--
control|)
block|{
if|#
directive|if
name|G_BYTE_ORDER
operator|==
name|G_BIG_ENDIAN
name|unsigned
name|char
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|r
operator|=
name|data
index|[
name|i
operator|*
literal|4
operator|+
literal|3
index|]
expr_stmt|;
name|g
operator|=
name|data
index|[
name|i
operator|*
literal|4
operator|+
literal|2
index|]
expr_stmt|;
name|b
operator|=
name|data
index|[
name|i
operator|*
literal|4
operator|+
literal|1
index|]
expr_stmt|;
name|data
index|[
name|i
operator|*
literal|4
operator|+
literal|2
index|]
operator|=
name|b
expr_stmt|;
name|data
index|[
name|i
operator|*
literal|4
operator|+
literal|1
index|]
operator|=
name|g
expr_stmt|;
name|data
index|[
name|i
operator|*
literal|4
index|]
operator|=
name|r
expr_stmt|;
endif|#
directive|endif
name|data
index|[
name|i
operator|*
literal|4
operator|+
literal|3
index|]
operator|=
literal|255
expr_stmt|;
block|}
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
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|data
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|wwidth
argument_list|,
name|wheight
argument_list|)
expr_stmt|;
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
name|framenumber
operator|++
expr_stmt|;
block|}
name|CloseMPEG
argument_list|()
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

end_unit

