begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * GFLI 1.0  *  * A gimp plug-in to read FLI and FLC movies.  *  * Copyright (C) 1997 Jens Ch. Restemeier<jchrr@hrz.uni-bielefeld.de>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  *  * This is a first loader for FLI and FLC movies. It uses as the same method as  * the gif plug-in to store the animation (i.e. 1 layer/frame).  *   * Current disadvantages:  * - All frames must share the same colormap. Maybe I add an option for   *   generating RGB images in the next version !  * - Generates A LOT OF warnings.  * - Consumes a lot of memory (See wish-list: use the original data or   *   compression).  * - doesn't save movies (will be added to next version, depends on  *   feedback). You can save as animated GIF, of course...  *  * Wish-List:  * - I'd like to have a different format for storing animations, so I can use  *   Layers and Alpha-Channels for effects. I'm working on another movie-loader  *   that _requires_ layers (Gold Disk moviesetter). An older version of   *   this plug-in created one image per frame, and went real soon out of  *   memory.  * - I'd like a method that requests unmodified frames from the original  *   image, and stores modified frames compressed (suggestion: libpng).  * - I'd like a way to store additional information about a image to it, for  *   example copyright stuff or a timecode.  *  * Ideas:  * - I could put all the functions for loading / saving fli into a  *   gimp-independant library. Anybody interested to save fli from his  *   application ?  *  */
end_comment

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
file|<unistd.h>
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
name|gimp_install_procedure
argument_list|(
literal|"file_fli_load"
argument_list|,
literal|"load AA-movies"
argument_list|,
literal|"This is a experimantal plug-in to handle FLI movies"
argument_list|,
literal|"Jens Ch. Restemeier"
argument_list|,
literal|"Jens Ch. Restemeier"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Load>/FLI"
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
name|gimp_register_magic_load_handler
argument_list|(
literal|"file_fli_load"
argument_list|,
literal|"fli,flc"
argument_list|,
literal|""
argument_list|,
literal|"4,short,0x11af,4,short,0x12af"
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
literal|"file_fli_load"
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
block|}
end_function

begin_typedef
DECL|struct|_fli_header
typedef|typedef
struct|struct
name|_fli_header
block|{
DECL|member|filesize
name|unsigned
name|long
name|filesize
decl_stmt|;
DECL|member|magic
name|unsigned
name|short
name|magic
decl_stmt|;
DECL|member|frames
name|unsigned
name|short
name|frames
decl_stmt|;
DECL|member|width
name|unsigned
name|short
name|width
decl_stmt|;
DECL|member|height
name|unsigned
name|short
name|height
decl_stmt|;
DECL|member|depth
name|unsigned
name|short
name|depth
decl_stmt|;
DECL|member|flags
name|unsigned
name|short
name|flags
decl_stmt|;
DECL|member|speed
name|unsigned
name|long
name|speed
decl_stmt|;
DECL|typedef|s_fli_header
block|}
name|s_fli_header
typedef|;
end_typedef

begin_typedef
DECL|struct|_fli_frame
typedef|typedef
struct|struct
name|_fli_frame
block|{
DECL|member|framesize
name|unsigned
name|long
name|framesize
decl_stmt|;
DECL|member|magic
name|unsigned
name|short
name|magic
decl_stmt|;
DECL|member|chunks
name|unsigned
name|short
name|chunks
decl_stmt|;
DECL|typedef|s_fli_frame
block|}
name|s_fli_frame
typedef|;
end_typedef

begin_comment
comment|/* read byte/word/long */
end_comment

begin_function
DECL|function|fli_read_char (FILE * f)
specifier|inline
name|unsigned
name|char
name|fli_read_char
parameter_list|(
name|FILE
modifier|*
name|f
parameter_list|)
block|{
name|unsigned
name|char
name|b
decl_stmt|;
name|fread
argument_list|(
operator|&
name|b
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
name|f
argument_list|)
expr_stmt|;
return|return
name|b
return|;
block|}
end_function

begin_function
DECL|function|fli_read_short (FILE * f)
specifier|inline
name|unsigned
name|short
name|fli_read_short
parameter_list|(
name|FILE
modifier|*
name|f
parameter_list|)
block|{
name|unsigned
name|char
name|b
index|[
literal|2
index|]
decl_stmt|;
name|fread
argument_list|(
operator|&
name|b
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|f
argument_list|)
expr_stmt|;
return|return
call|(
name|unsigned
name|short
call|)
argument_list|(
name|b
index|[
literal|1
index|]
operator|<<
literal|8
argument_list|)
operator||
name|b
index|[
literal|0
index|]
return|;
block|}
end_function

begin_function
DECL|function|fli_read_long (FILE * f)
specifier|inline
name|unsigned
name|long
name|fli_read_long
parameter_list|(
name|FILE
modifier|*
name|f
parameter_list|)
block|{
name|unsigned
name|char
name|b
index|[
literal|4
index|]
decl_stmt|;
name|fread
argument_list|(
operator|&
name|b
argument_list|,
literal|1
argument_list|,
literal|4
argument_list|,
name|f
argument_list|)
expr_stmt|;
return|return
call|(
name|unsigned
name|long
call|)
argument_list|(
name|b
index|[
literal|3
index|]
operator|<<
literal|24
argument_list|)
operator||
operator|(
name|b
index|[
literal|2
index|]
operator|<<
literal|16
operator|)
operator||
operator|(
name|b
index|[
literal|1
index|]
operator|<<
literal|8
operator|)
operator||
name|b
index|[
literal|0
index|]
return|;
block|}
end_function

begin_function
DECL|function|fli_read_header (FILE * f,s_fli_header * fli_header)
name|void
name|fli_read_header
parameter_list|(
name|FILE
modifier|*
name|f
parameter_list|,
name|s_fli_header
modifier|*
name|fli_header
parameter_list|)
block|{
name|fli_header
operator|->
name|filesize
operator|=
name|fli_read_long
argument_list|(
name|f
argument_list|)
expr_stmt|;
comment|/* 0 */
name|fli_header
operator|->
name|magic
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
comment|/* 4 */
name|fli_header
operator|->
name|frames
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
comment|/* 6 */
name|fli_header
operator|->
name|width
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
comment|/* 8 */
name|fli_header
operator|->
name|height
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
comment|/* 10 */
name|fli_header
operator|->
name|depth
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
comment|/* 12 */
name|fli_header
operator|->
name|flags
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
comment|/* 14 */
if|if
condition|(
name|fli_header
operator|->
name|magic
operator|==
literal|0xAF11
condition|)
block|{
comment|/* FLI */
comment|/* FLI saves speed in 1/70s */
name|fli_header
operator|->
name|speed
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
operator|*
literal|14
expr_stmt|;
comment|/* 16 */
block|}
else|else
block|{
if|if
condition|(
name|fli_header
operator|->
name|magic
operator|==
literal|0xAF12
condition|)
block|{
comment|/* FLC */
comment|/* FLC saves speed in 1/1000s */
name|fli_header
operator|->
name|speed
operator|=
name|fli_read_long
argument_list|(
name|f
argument_list|)
expr_stmt|;
comment|/* 16 */
block|}
else|else
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"error: magic number is wrong !\n"
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
DECL|function|fli_read_frame (FILE * f,s_fli_header * fli_header,guchar * framebuf,gchar * cmap)
name|void
name|fli_read_frame
parameter_list|(
name|FILE
modifier|*
name|f
parameter_list|,
name|s_fli_header
modifier|*
name|fli_header
parameter_list|,
name|guchar
modifier|*
name|framebuf
parameter_list|,
name|gchar
modifier|*
name|cmap
parameter_list|)
block|{
name|s_fli_frame
name|fli_frame
decl_stmt|;
name|unsigned
name|long
name|framepos
decl_stmt|;
name|int
name|c
decl_stmt|;
name|unsigned
name|short
name|col_pos
decl_stmt|;
name|col_pos
operator|=
literal|0
expr_stmt|;
name|framepos
operator|=
name|ftell
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|fli_frame
operator|.
name|framesize
operator|=
name|fli_read_long
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|fli_frame
operator|.
name|magic
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|fli_frame
operator|.
name|chunks
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
if|if
condition|(
name|fli_frame
operator|.
name|magic
operator|==
literal|0xF1FA
condition|)
block|{
name|fseek
argument_list|(
name|f
argument_list|,
name|framepos
operator|+
literal|16
argument_list|,
name|SEEK_SET
argument_list|)
expr_stmt|;
for|for
control|(
name|c
operator|=
literal|0
init|;
name|c
operator|<
name|fli_frame
operator|.
name|chunks
condition|;
name|c
operator|++
control|)
block|{
name|unsigned
name|long
name|chunkpos
decl_stmt|,
name|chunksize
decl_stmt|;
name|unsigned
name|short
name|chunktype
decl_stmt|;
name|chunkpos
operator|=
name|ftell
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|chunksize
operator|=
name|fli_read_long
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|chunktype
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|chunktype
condition|)
block|{
case|case
literal|11
case|:
block|{
comment|/* fli_color */
name|unsigned
name|short
name|num_packets
decl_stmt|;
name|int
name|cnt_packets
decl_stmt|;
name|num_packets
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
for|for
control|(
name|cnt_packets
operator|=
name|num_packets
init|;
name|cnt_packets
operator|>
literal|0
condition|;
name|cnt_packets
operator|--
control|)
block|{
name|unsigned
name|short
name|skip_col
decl_stmt|,
name|num_col
decl_stmt|,
name|col_cnt
decl_stmt|;
name|skip_col
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|num_col
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_col
operator|==
literal|0
condition|)
block|{
for|for
control|(
name|col_pos
operator|=
literal|0
init|;
name|col_pos
operator|<
literal|768
condition|;
name|col_pos
operator|++
control|)
block|{
name|cmap
index|[
name|col_pos
index|]
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
operator|<<
literal|2
expr_stmt|;
block|}
block|}
else|else
block|{
name|col_pos
operator|+=
operator|(
name|skip_col
operator|*
literal|3
operator|)
expr_stmt|;
for|for
control|(
name|col_cnt
operator|=
name|num_col
init|;
operator|(
name|col_cnt
operator|>
literal|0
operator|)
operator|&&
operator|(
name|col_pos
operator|<
literal|768
operator|)
condition|;
name|col_cnt
operator|--
control|)
block|{
name|cmap
index|[
name|col_pos
operator|++
index|]
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
operator|<<
literal|2
expr_stmt|;
name|cmap
index|[
name|col_pos
operator|++
index|]
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
operator|<<
literal|2
expr_stmt|;
name|cmap
index|[
name|col_pos
operator|++
index|]
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
operator|<<
literal|2
expr_stmt|;
block|}
block|}
block|}
break|break;
block|}
case|case
literal|13
case|:
comment|/* fli_black */
name|memset
argument_list|(
name|framebuf
argument_list|,
literal|0
argument_list|,
name|fli_header
operator|->
name|width
operator|*
name|fli_header
operator|->
name|height
argument_list|)
expr_stmt|;
break|break;
case|case
literal|15
case|:
block|{
comment|/* fli_brun */
name|unsigned
name|short
name|yc
decl_stmt|;
name|guchar
modifier|*
name|pos
decl_stmt|;
for|for
control|(
name|yc
operator|=
literal|0
init|;
name|yc
operator|<
name|fli_header
operator|->
name|height
condition|;
name|yc
operator|++
control|)
block|{
name|unsigned
name|short
name|xc
decl_stmt|,
name|pc
decl_stmt|,
name|pcnt
decl_stmt|;
name|pc
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|xc
operator|=
literal|0
expr_stmt|;
name|pos
operator|=
name|framebuf
operator|+
operator|(
name|fli_header
operator|->
name|width
operator|*
name|yc
operator|)
expr_stmt|;
for|for
control|(
name|pcnt
operator|=
name|pc
init|;
name|pcnt
operator|>
literal|0
condition|;
name|pcnt
operator|--
control|)
block|{
name|unsigned
name|short
name|ps
decl_stmt|;
name|ps
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
if|if
condition|(
name|ps
operator|&
literal|0x80
condition|)
block|{
name|unsigned
name|short
name|len
decl_stmt|;
name|ps
operator|^=
literal|0xFF
expr_stmt|;
name|ps
operator|+=
literal|1
expr_stmt|;
for|for
control|(
name|len
operator|=
name|ps
init|;
name|len
operator|>
literal|0
condition|;
name|len
operator|--
control|)
block|{
name|pos
index|[
name|xc
operator|++
index|]
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|unsigned
name|char
name|val
decl_stmt|;
name|val
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|memset
argument_list|(
operator|&
operator|(
name|pos
index|[
name|xc
index|]
operator|)
argument_list|,
name|val
argument_list|,
name|ps
argument_list|)
expr_stmt|;
name|xc
operator|+=
name|ps
expr_stmt|;
block|}
block|}
block|}
break|break;
block|}
case|case
literal|16
case|:
block|{
comment|/* fli_copy */
name|unsigned
name|long
name|cc
decl_stmt|;
name|guchar
modifier|*
name|pos
decl_stmt|;
name|pos
operator|=
name|framebuf
expr_stmt|;
for|for
control|(
name|cc
operator|=
name|fli_header
operator|->
name|width
operator|*
name|fli_header
operator|->
name|height
init|;
name|cc
operator|>
literal|0
condition|;
name|cc
operator|--
control|)
block|{
operator|*
operator|(
name|pos
operator|++
operator|)
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
case|case
literal|12
case|:
block|{
comment|/* fli_lc */
name|unsigned
name|short
name|yc
decl_stmt|,
name|firstline
decl_stmt|,
name|numline
decl_stmt|;
name|guchar
modifier|*
name|pos
decl_stmt|;
name|firstline
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|numline
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
for|for
control|(
name|yc
operator|=
literal|0
init|;
name|yc
operator|<
name|numline
condition|;
name|yc
operator|++
control|)
block|{
name|unsigned
name|short
name|xc
decl_stmt|,
name|pc
decl_stmt|,
name|pcnt
decl_stmt|;
name|pc
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|xc
operator|=
literal|0
expr_stmt|;
name|pos
operator|=
name|framebuf
operator|+
operator|(
name|fli_header
operator|->
name|width
operator|*
operator|(
name|firstline
operator|+
name|yc
operator|)
operator|)
expr_stmt|;
for|for
control|(
name|pcnt
operator|=
name|pc
init|;
name|pcnt
operator|>
literal|0
condition|;
name|pcnt
operator|--
control|)
block|{
name|unsigned
name|short
name|ps
decl_stmt|,
name|skip
decl_stmt|;
name|skip
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|ps
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|xc
operator|+=
name|skip
expr_stmt|;
if|if
condition|(
name|ps
operator|&
literal|0x80
condition|)
block|{
name|unsigned
name|char
name|val
decl_stmt|;
name|ps
operator|^=
literal|0xFF
expr_stmt|;
name|ps
operator|+=
literal|1
expr_stmt|;
name|val
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|memset
argument_list|(
operator|&
operator|(
name|pos
index|[
name|xc
index|]
operator|)
argument_list|,
name|val
argument_list|,
name|ps
argument_list|)
expr_stmt|;
name|xc
operator|+=
name|ps
expr_stmt|;
block|}
else|else
block|{
name|unsigned
name|short
name|len
decl_stmt|;
for|for
control|(
name|len
operator|=
name|ps
init|;
name|len
operator|>
literal|0
condition|;
name|len
operator|--
control|)
block|{
name|pos
index|[
name|xc
operator|++
index|]
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
break|break;
block|}
case|case
literal|7
case|:
block|{
comment|/* fli_lc2 */
name|unsigned
name|short
name|yc
decl_stmt|,
name|lc
decl_stmt|,
name|numline
decl_stmt|;
name|guchar
modifier|*
name|pos
decl_stmt|;
name|yc
operator|=
literal|0
expr_stmt|;
name|numline
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
for|for
control|(
name|lc
operator|=
literal|0
init|;
name|lc
operator|<
name|numline
condition|;
name|lc
operator|++
control|)
block|{
name|unsigned
name|short
name|xc
decl_stmt|,
name|pc
decl_stmt|,
name|pcnt
decl_stmt|,
name|lpf
decl_stmt|,
name|lpn
decl_stmt|;
name|pc
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|lpf
operator|=
literal|0
expr_stmt|;
name|lpn
operator|=
literal|0
expr_stmt|;
while|while
condition|(
name|pc
operator|&
literal|0x8000
condition|)
block|{
if|if
condition|(
name|pc
operator|&
literal|0x4000
condition|)
block|{
name|yc
operator|+=
name|pc
operator|&
literal|0x3FFF
expr_stmt|;
block|}
else|else
block|{
name|lpf
operator|=
literal|1
expr_stmt|;
name|lpn
operator|=
name|pc
operator|&
literal|0xFF
expr_stmt|;
block|}
name|pc
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
block|}
name|xc
operator|=
literal|0
expr_stmt|;
name|pos
operator|=
name|framebuf
operator|+
operator|(
name|fli_header
operator|->
name|width
operator|*
name|yc
operator|)
expr_stmt|;
for|for
control|(
name|pcnt
operator|=
name|pc
init|;
name|pcnt
operator|>
literal|0
condition|;
name|pcnt
operator|--
control|)
block|{
name|unsigned
name|short
name|ps
decl_stmt|,
name|skip
decl_stmt|;
name|skip
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|ps
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|xc
operator|+=
name|skip
expr_stmt|;
if|if
condition|(
name|ps
operator|&
literal|0x80
condition|)
block|{
name|unsigned
name|char
name|v1
decl_stmt|,
name|v2
decl_stmt|;
name|ps
operator|^=
literal|0xFF
expr_stmt|;
name|ps
operator|++
expr_stmt|;
name|v1
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|v2
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
while|while
condition|(
name|ps
operator|>
literal|0
condition|)
block|{
name|pos
index|[
name|xc
operator|++
index|]
operator|=
name|v1
expr_stmt|;
name|pos
index|[
name|xc
operator|++
index|]
operator|=
name|v2
expr_stmt|;
name|ps
operator|--
expr_stmt|;
block|}
block|}
else|else
block|{
name|unsigned
name|short
name|len
decl_stmt|;
for|for
control|(
name|len
operator|=
name|ps
init|;
name|len
operator|>
literal|0
condition|;
name|len
operator|--
control|)
block|{
name|pos
index|[
name|xc
operator|++
index|]
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|pos
index|[
name|xc
operator|++
index|]
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|lpf
condition|)
name|pos
index|[
name|xc
index|]
operator|=
name|lpn
expr_stmt|;
name|yc
operator|++
expr_stmt|;
block|}
break|break;
block|}
case|case
literal|4
case|:
block|{
comment|/* fli_color_2 */
name|unsigned
name|short
name|num_packets
decl_stmt|;
name|int
name|cnt_packets
decl_stmt|;
name|num_packets
operator|=
name|fli_read_short
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|col_pos
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|cnt_packets
operator|=
name|num_packets
init|;
name|cnt_packets
operator|>
literal|0
condition|;
name|cnt_packets
operator|--
control|)
block|{
name|unsigned
name|short
name|skip_col
decl_stmt|,
name|num_col
decl_stmt|,
name|col_cnt
decl_stmt|;
name|skip_col
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|num_col
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_col
operator|==
literal|0
condition|)
block|{
for|for
control|(
name|col_pos
operator|=
literal|0
init|;
name|col_pos
operator|<
literal|768
condition|;
name|col_pos
operator|++
control|)
block|{
name|cmap
index|[
name|col_pos
index|]
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|col_pos
operator|+=
operator|(
name|skip_col
operator|+=
literal|3
operator|)
expr_stmt|;
for|for
control|(
name|col_cnt
operator|=
name|num_col
init|;
operator|(
name|col_cnt
operator|>
literal|0
operator|)
operator|&&
operator|(
name|col_pos
operator|<
literal|768
operator|)
condition|;
name|col_cnt
operator|--
control|)
block|{
name|cmap
index|[
name|col_pos
operator|++
index|]
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|cmap
index|[
name|col_pos
operator|++
index|]
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|cmap
index|[
name|col_pos
operator|++
index|]
operator|=
name|fli_read_char
argument_list|(
name|f
argument_list|)
expr_stmt|;
block|}
block|}
block|}
break|break;
block|}
case|case
literal|18
case|:
comment|/* fli_mini (ignored) */
break|break;
block|}
if|if
condition|(
name|chunksize
operator|&
literal|1
condition|)
name|chunksize
operator|++
expr_stmt|;
name|fseek
argument_list|(
name|f
argument_list|,
name|chunkpos
operator|+
name|chunksize
argument_list|,
name|SEEK_SET
argument_list|)
expr_stmt|;
block|}
block|}
name|fseek
argument_list|(
name|f
argument_list|,
name|framepos
operator|+
name|fli_frame
operator|.
name|framesize
argument_list|,
name|SEEK_SET
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|load_image (char * filename)
name|gint32
name|load_image
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
block|{
name|FILE
modifier|*
name|f
decl_stmt|;
name|char
modifier|*
name|name_buf
decl_stmt|;
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|,
name|layer_ID
decl_stmt|;
name|guchar
modifier|*
name|frame_buffer
decl_stmt|;
name|guchar
name|cmap
index|[
literal|768
index|]
decl_stmt|;
name|GPixelRgn
name|pixel_rgn
decl_stmt|;
name|s_fli_header
name|fli_header
decl_stmt|;
name|int
name|cnt
decl_stmt|;
name|name_buf
operator|=
name|g_malloc
argument_list|(
literal|64
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|name_buf
argument_list|,
literal|"Loading %s:"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|name_buf
argument_list|)
expr_stmt|;
name|f
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
operator|!
name|f
condition|)
block|{
name|printf
argument_list|(
literal|"FLI: can't open \"%s\"\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|fli_read_header
argument_list|(
name|f
argument_list|,
operator|&
name|fli_header
argument_list|)
expr_stmt|;
name|fseek
argument_list|(
name|f
argument_list|,
literal|128
argument_list|,
name|SEEK_SET
argument_list|)
expr_stmt|;
name|image_ID
operator|=
name|gimp_image_new
argument_list|(
name|fli_header
operator|.
name|width
argument_list|,
name|fli_header
operator|.
name|height
argument_list|,
name|INDEXED
argument_list|)
expr_stmt|;
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|frame_buffer
operator|=
name|g_malloc
argument_list|(
name|fli_header
operator|.
name|width
operator|*
name|fli_header
operator|.
name|height
argument_list|)
expr_stmt|;
for|for
control|(
name|cnt
operator|=
literal|0
init|;
name|cnt
operator|<
name|fli_header
operator|.
name|frames
condition|;
name|cnt
operator|++
control|)
block|{
name|sprintf
argument_list|(
name|name_buf
argument_list|,
literal|"Frame (%i)"
argument_list|,
name|cnt
operator|+
literal|1
argument_list|)
expr_stmt|;
name|layer_ID
operator|=
name|gimp_layer_new
argument_list|(
name|image_ID
argument_list|,
name|name_buf
argument_list|,
name|fli_header
operator|.
name|width
argument_list|,
name|fli_header
operator|.
name|height
argument_list|,
name|INDEXED_IMAGE
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
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|cnt
operator|/
name|fli_header
operator|.
name|frames
argument_list|)
expr_stmt|;
name|fli_read_frame
argument_list|(
name|f
argument_list|,
operator|&
name|fli_header
argument_list|,
name|frame_buffer
argument_list|,
name|cmap
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
name|fli_header
operator|.
name|width
argument_list|,
name|fli_header
operator|.
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
name|frame_buffer
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|fli_header
operator|.
name|width
argument_list|,
name|fli_header
operator|.
name|height
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
block|}
name|gimp_image_set_cmap
argument_list|(
name|image_ID
argument_list|,
name|cmap
argument_list|,
literal|256
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name_buf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|frame_buffer
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

end_unit

