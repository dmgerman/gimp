begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* This is a plugin for GIMP.  *  * Copyright (C) 1997 Jochen Friedrich  * Parts Copyright (C) 1995 Gert Doering  * Parts Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

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
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_comment
comment|/* For G_OS_WIN32 */
end_comment

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
file|"g3.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-faxg3-load"
end_define

begin_define
DECL|macro|VERSION
define|#
directive|define
name|VERSION
value|"0.6"
end_define

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
name|gint32
name|emitgimp
parameter_list|(
name|gint
name|hcol
parameter_list|,
name|gint
name|row
parameter_list|,
specifier|const
name|gchar
modifier|*
name|bitmap
parameter_list|,
name|gint
name|bperrow
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
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
name|gimp_install_procedure
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"loads g3 fax files"
argument_list|,
literal|"This plug-in loads Fax G3 Image files."
argument_list|,
literal|"Jochen Friedrich"
argument_list|,
literal|"Jochen Friedrich, Gert Doering, Spencer Kimball& Peter Mattis"
argument_list|,
name|VERSION
argument_list|,
name|N_
argument_list|(
literal|"G3 fax image"
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
literal|"image/g3-fax"
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"g3"
argument_list|,
literal|""
argument_list|,
literal|"4,string,Research"
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
name|gint32
name|image_ID
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
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
name|GIMP_PDB_CALLING_ERROR
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
name|INIT_I18N
argument_list|()
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
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_SUCCESS
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
block|}
block|}
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|DEBUG
end_ifdef

begin_function
DECL|function|putbin (unsigned long d)
name|void
name|putbin
parameter_list|(
name|unsigned
name|long
name|d
parameter_list|)
block|{
name|unsigned
name|long
name|i
init|=
literal|0x80000000
decl_stmt|;
while|while
condition|(
name|i
operator|!=
literal|0
condition|)
block|{
name|putc
argument_list|(
operator|(
name|d
operator|&
name|i
operator|)
condition|?
literal|'1'
else|:
literal|'0'
argument_list|,
name|stderr
argument_list|)
expr_stmt|;
name|i
operator|>>=
literal|1
expr_stmt|;
block|}
name|putc
argument_list|(
literal|'\n'
argument_list|,
name|stderr
argument_list|)
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|byte_tab
specifier|static
name|int
name|byte_tab
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* static int o_stretch; */
end_comment

begin_comment
comment|/* -stretch: double each line */
end_comment

begin_comment
comment|/* static int o_stretch_force=-1; */
end_comment

begin_comment
comment|/* -1: guess from filename */
end_comment

begin_comment
comment|/* static int o_lj; */
end_comment

begin_comment
comment|/* -l: LJ output */
end_comment

begin_comment
comment|/* static int o_turn; */
end_comment

begin_comment
comment|/* -t: turn 90 degrees right */
end_comment

begin_decl_stmt
DECL|variable|black
DECL|variable|white
name|struct
name|g3_tree
modifier|*
name|black
decl_stmt|,
modifier|*
name|white
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|CHUNK
define|#
directive|define
name|CHUNK
value|2048;
end_define

begin_decl_stmt
DECL|variable|rbuf
specifier|static
name|char
name|rbuf
index|[
literal|2048
index|]
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|rbuf
comment|/* read buffer */
end_comment

begin_decl_stmt
DECL|variable|rp
specifier|static
name|int
name|rp
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|rp
comment|/* read pointer */
end_comment

begin_decl_stmt
DECL|variable|rs
specifier|static
name|int
name|rs
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|rs
comment|/* read buffer size */
end_comment

begin_define
DECL|macro|MAX_ROWS
define|#
directive|define
name|MAX_ROWS
value|4300
end_define

begin_define
DECL|macro|MAX_COLS
define|#
directive|define
name|MAX_COLS
value|1728
end_define

begin_comment
DECL|macro|MAX_COLS
comment|/* !! FIXME - command line parameter */
end_comment

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
name|int
name|data
decl_stmt|;
name|int
name|hibit
decl_stmt|;
name|struct
name|g3_tree
modifier|*
name|p
decl_stmt|;
name|int
name|nr_pels
decl_stmt|;
name|int
name|fd
decl_stmt|;
name|int
name|color
decl_stmt|;
name|int
name|i
decl_stmt|,
name|rr
decl_stmt|,
name|rsize
decl_stmt|;
name|int
name|cons_eol
decl_stmt|;
name|gint32
name|image_id
decl_stmt|;
name|gint
name|bperrow
init|=
name|MAX_COLS
operator|/
literal|8
decl_stmt|;
comment|/* bytes per bit row */
name|gchar
modifier|*
name|bitmap
decl_stmt|;
comment|/* MAX_ROWS by (bperrow) bytes */
name|gchar
modifier|*
name|bp
decl_stmt|;
comment|/* bitmap pointer */
name|gint
name|row
decl_stmt|;
name|gint
name|max_rows
decl_stmt|;
comment|/* max. rows allocated */
name|gint
name|col
decl_stmt|,
name|hcol
decl_stmt|;
comment|/* column, highest column ever used */
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
comment|/* initialize lookup trees */
name|build_tree
argument_list|(
operator|&
name|white
argument_list|,
name|t_white
argument_list|)
expr_stmt|;
name|build_tree
argument_list|(
operator|&
name|white
argument_list|,
name|m_white
argument_list|)
expr_stmt|;
name|build_tree
argument_list|(
operator|&
name|black
argument_list|,
name|t_black
argument_list|)
expr_stmt|;
name|build_tree
argument_list|(
operator|&
name|black
argument_list|,
name|m_black
argument_list|)
expr_stmt|;
name|init_byte_tab
argument_list|(
literal|0
argument_list|,
name|byte_tab
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
name|hibit
operator|=
literal|0
expr_stmt|;
name|data
operator|=
literal|0
expr_stmt|;
name|cons_eol
operator|=
literal|0
expr_stmt|;
comment|/* consecutive EOLs read - zero yet */
name|color
operator|=
literal|0
expr_stmt|;
comment|/* start with white */
name|rr
operator|=
literal|0
expr_stmt|;
name|rsize
operator|=
name|lseek
argument_list|(
name|fd
argument_list|,
literal|0L
argument_list|,
name|SEEK_END
argument_list|)
expr_stmt|;
name|lseek
argument_list|(
name|fd
argument_list|,
literal|0L
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|rs
operator|=
name|read
argument_list|(
name|fd
argument_list|,
name|rbuf
argument_list|,
sizeof|sizeof
argument_list|(
name|rbuf
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|rs
operator|<
literal|0
condition|)
block|{
name|perror
argument_list|(
literal|"read"
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|rs
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
name|rr
operator|+=
name|rs
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|float
operator|)
name|rr
operator|/
name|rsize
operator|/
literal|2.0
argument_list|)
expr_stmt|;
comment|/* skip GhostScript header */
name|rp
operator|=
operator|(
name|rs
operator|>=
literal|64
operator|&&
name|strcmp
argument_list|(
name|rbuf
operator|+
literal|1
argument_list|,
literal|"PC Research, Inc"
argument_list|)
operator|==
literal|0
operator|)
condition|?
literal|64
else|:
literal|0
expr_stmt|;
comment|/* initialize bitmap */
name|row
operator|=
name|col
operator|=
name|hcol
operator|=
literal|0
expr_stmt|;
name|bitmap
operator|=
name|g_new0
argument_list|(
name|gchar
argument_list|,
operator|(
name|max_rows
operator|=
name|MAX_ROWS
operator|)
operator|*
name|MAX_COLS
operator|/
literal|8
argument_list|)
expr_stmt|;
name|bp
operator|=
operator|&
name|bitmap
index|[
name|row
operator|*
name|MAX_COLS
operator|/
literal|8
index|]
expr_stmt|;
while|while
condition|(
name|rs
operator|>
literal|0
operator|&&
name|cons_eol
operator|<
literal|4
condition|)
comment|/* i.e., while (!EOF) */
block|{
ifdef|#
directive|ifdef
name|DEBUG
name|g_printerr
argument_list|(
literal|"hibit=%2d, data="
argument_list|,
name|hibit
argument_list|)
expr_stmt|;
name|putbin
argument_list|(
name|data
argument_list|)
expr_stmt|;
endif|#
directive|endif
while|while
condition|(
name|hibit
operator|<
literal|20
condition|)
block|{
name|data
operator||=
operator|(
name|byte_tab
index|[
operator|(
name|int
operator|)
operator|(
name|unsigned
name|char
operator|)
name|rbuf
index|[
name|rp
operator|++
index|]
index|]
operator|<<
name|hibit
operator|)
expr_stmt|;
name|hibit
operator|+=
literal|8
expr_stmt|;
if|if
condition|(
name|rp
operator|>=
name|rs
condition|)
block|{
name|rs
operator|=
name|read
argument_list|(
name|fd
argument_list|,
name|rbuf
argument_list|,
sizeof|sizeof
argument_list|(
name|rbuf
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|rs
operator|<
literal|0
condition|)
block|{
name|perror
argument_list|(
literal|"read2"
argument_list|)
expr_stmt|;
break|break;
block|}
name|rr
operator|+=
name|rs
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|float
operator|)
name|rr
operator|/
name|rsize
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|rp
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|rs
operator|==
literal|0
condition|)
block|{
goto|goto
name|do_write
goto|;
block|}
block|}
ifdef|#
directive|ifdef
name|DEBUG
name|g_printerr
argument_list|(
literal|"hibit=%2d, data="
argument_list|,
name|hibit
argument_list|)
expr_stmt|;
name|putbin
argument_list|(
name|data
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
if|if
condition|(
name|color
operator|==
literal|0
condition|)
comment|/* white */
name|p
operator|=
name|white
operator|->
name|nextb
index|[
name|data
operator|&
name|BITM
index|]
expr_stmt|;
else|else
comment|/* black */
name|p
operator|=
name|black
operator|->
name|nextb
index|[
name|data
operator|&
name|BITM
index|]
expr_stmt|;
while|while
condition|(
name|p
operator|!=
name|NULL
operator|&&
operator|!
operator|(
name|p
operator|->
name|nr_bits
operator|)
condition|)
block|{
name|data
operator|>>=
name|FBITS
expr_stmt|;
name|hibit
operator|-=
name|FBITS
expr_stmt|;
name|p
operator|=
name|p
operator|->
name|nextb
index|[
name|data
operator|&
name|BITM
index|]
expr_stmt|;
block|}
if|if
condition|(
name|p
operator|==
name|NULL
condition|)
comment|/* invalid code */
block|{
name|g_printerr
argument_list|(
literal|"invalid code, row=%d, col=%d, file offset=%lx, skip to eol\n"
argument_list|,
name|row
argument_list|,
name|col
argument_list|,
operator|(
name|unsigned
name|long
operator|)
name|lseek
argument_list|(
name|fd
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
operator|-
name|rs
operator|+
name|rp
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|data
operator|&
literal|0x03f
operator|)
operator|!=
literal|0
condition|)
block|{
name|data
operator|>>=
literal|1
expr_stmt|;
name|hibit
operator|--
expr_stmt|;
if|if
condition|(
name|hibit
operator|<
literal|20
condition|)
block|{
name|data
operator||=
operator|(
name|byte_tab
index|[
operator|(
name|int
operator|)
operator|(
name|unsigned
name|char
operator|)
name|rbuf
index|[
name|rp
operator|++
index|]
index|]
operator|<<
name|hibit
operator|)
expr_stmt|;
name|hibit
operator|+=
literal|8
expr_stmt|;
if|if
condition|(
name|rp
operator|>=
name|rs
condition|)
comment|/* buffer underrun */
block|{
name|rs
operator|=
name|read
argument_list|(
name|fd
argument_list|,
name|rbuf
argument_list|,
sizeof|sizeof
argument_list|(
name|rbuf
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|rs
operator|<
literal|0
condition|)
block|{
name|perror
argument_list|(
literal|"read4"
argument_list|)
expr_stmt|;
break|break;
block|}
name|rr
operator|+=
name|rs
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|float
operator|)
name|rr
operator|/
name|rsize
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|rp
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|rs
operator|==
literal|0
condition|)
goto|goto
name|do_write
goto|;
block|}
block|}
block|}
name|nr_pels
operator|=
operator|-
literal|1
expr_stmt|;
comment|/* handle as if eol */
block|}
else|else
comment|/* p != NULL<-> valid code */
block|{
name|data
operator|>>=
name|p
operator|->
name|nr_bits
expr_stmt|;
name|hibit
operator|-=
name|p
operator|->
name|nr_bits
expr_stmt|;
name|nr_pels
operator|=
operator|(
operator|(
expr|struct
name|g3_leaf
operator|*
operator|)
name|p
operator|)
operator|->
name|nr_pels
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG
name|g_printerr
argument_list|(
literal|"PELs: %d (%c)\n"
argument_list|,
name|nr_pels
argument_list|,
literal|'0'
operator|+
name|color
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
comment|/* handle EOL (including fill bits) */
if|if
condition|(
name|nr_pels
operator|==
operator|-
literal|1
condition|)
block|{
ifdef|#
directive|ifdef
name|DEBUG
name|g_printerr
argument_list|(
literal|"hibit=%2d, data="
argument_list|,
name|hibit
argument_list|)
expr_stmt|;
name|putbin
argument_list|(
name|data
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* skip filler 0bits -> seek for "1"-bit */
while|while
condition|(
operator|(
name|data
operator|&
literal|0x01
operator|)
operator|!=
literal|1
condition|)
block|{
if|if
condition|(
operator|(
name|data
operator|&
literal|0xf
operator|)
operator|==
literal|0
condition|)
comment|/* nibble optimization */
block|{
name|hibit
operator|-=
literal|4
expr_stmt|;
name|data
operator|>>=
literal|4
expr_stmt|;
block|}
else|else
block|{
name|hibit
operator|--
expr_stmt|;
name|data
operator|>>=
literal|1
expr_stmt|;
block|}
comment|/* fill higher bits */
if|if
condition|(
name|hibit
operator|<
literal|20
condition|)
block|{
name|data
operator||=
operator|(
name|byte_tab
index|[
operator|(
name|int
operator|)
operator|(
name|unsigned
name|char
operator|)
name|rbuf
index|[
name|rp
operator|++
index|]
index|]
operator|<<
name|hibit
operator|)
expr_stmt|;
name|hibit
operator|+=
literal|8
expr_stmt|;
if|if
condition|(
name|rp
operator|>=
name|rs
condition|)
comment|/* buffer underrun */
block|{
name|rs
operator|=
name|read
argument_list|(
name|fd
argument_list|,
name|rbuf
argument_list|,
sizeof|sizeof
argument_list|(
name|rbuf
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|rs
operator|<
literal|0
condition|)
block|{
name|perror
argument_list|(
literal|"read3"
argument_list|)
expr_stmt|;
break|break;
block|}
name|rr
operator|+=
name|rs
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|float
operator|)
name|rr
operator|/
name|rsize
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|rp
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|rs
operator|==
literal|0
condition|)
goto|goto
name|do_write
goto|;
block|}
block|}
ifdef|#
directive|ifdef
name|DEBUG
name|g_printerr
argument_list|(
literal|"hibit=%2d, data="
argument_list|,
name|hibit
argument_list|)
expr_stmt|;
name|putbin
argument_list|(
name|data
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
comment|/* end skip 0bits */
name|hibit
operator|--
expr_stmt|;
name|data
operator|>>=
literal|1
expr_stmt|;
name|color
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|col
operator|==
literal|0
condition|)
name|cons_eol
operator|++
expr_stmt|;
comment|/* consecutive EOLs */
else|else
block|{
if|if
condition|(
name|col
operator|>
name|hcol
operator|&&
name|col
operator|<=
name|MAX_COLS
condition|)
name|hcol
operator|=
name|col
expr_stmt|;
name|row
operator|++
expr_stmt|;
comment|/* bitmap memory full? make it larger! */
if|if
condition|(
name|row
operator|>=
name|max_rows
condition|)
block|{
name|gchar
modifier|*
name|p
init|=
name|g_try_realloc
argument_list|(
name|bitmap
argument_list|,
operator|(
name|max_rows
operator|+=
literal|500
operator|)
operator|*
name|MAX_COLS
operator|/
literal|8
argument_list|)
decl_stmt|;
if|if
condition|(
name|p
operator|==
name|NULL
condition|)
block|{
name|perror
argument_list|(
literal|"realloc() failed, page truncated"
argument_list|)
expr_stmt|;
name|rs
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|bitmap
operator|=
name|p
expr_stmt|;
name|memset
argument_list|(
operator|&
name|bitmap
index|[
name|row
operator|*
name|MAX_COLS
operator|/
literal|8
index|]
argument_list|,
literal|0
argument_list|,
operator|(
name|max_rows
operator|-
name|row
operator|)
operator|*
name|MAX_COLS
operator|/
literal|8
argument_list|)
expr_stmt|;
block|}
block|}
name|col
operator|=
literal|0
expr_stmt|;
name|bp
operator|=
operator|&
name|bitmap
index|[
name|row
operator|*
name|MAX_COLS
operator|/
literal|8
index|]
expr_stmt|;
name|cons_eol
operator|=
literal|0
expr_stmt|;
block|}
block|}
else|else
comment|/* not eol */
block|{
if|if
condition|(
name|col
operator|+
name|nr_pels
operator|>
name|MAX_COLS
condition|)
name|nr_pels
operator|=
name|MAX_COLS
operator|-
name|col
expr_stmt|;
if|if
condition|(
name|color
operator|==
literal|0
condition|)
comment|/* white */
name|col
operator|+=
name|nr_pels
expr_stmt|;
else|else
comment|/* black */
block|{
specifier|register
name|int
name|bit
init|=
operator|(
literal|0x80
operator|>>
operator|(
name|col
operator|&
literal|07
operator|)
operator|)
decl_stmt|;
specifier|register
name|char
modifier|*
name|w
init|=
operator|&
name|bp
index|[
name|col
operator|>>
literal|3
index|]
decl_stmt|;
for|for
control|(
name|i
operator|=
name|nr_pels
init|;
name|i
operator|>
literal|0
condition|;
name|i
operator|--
control|)
block|{
operator|*
name|w
operator||=
name|bit
expr_stmt|;
name|bit
operator|>>=
literal|1
expr_stmt|;
if|if
condition|(
name|bit
operator|==
literal|0
condition|)
block|{
name|bit
operator|=
literal|0x80
expr_stmt|;
name|w
operator|++
expr_stmt|;
block|}
name|col
operator|++
expr_stmt|;
block|}
block|}
if|if
condition|(
name|nr_pels
operator|<
literal|64
condition|)
name|color
operator|=
operator|!
name|color
expr_stmt|;
comment|/* terminating code */
block|}
block|}
comment|/* end main loop */
name|do_write
label|:
comment|/* write pbm (or whatever) file */
if|if
condition|(
name|fd
operator|!=
literal|0
condition|)
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
comment|/* close input file */
ifdef|#
directive|ifdef
name|DEBUG
name|g_printerr
argument_list|(
literal|"consecutive EOLs: %d, max columns: %d\n"
argument_list|,
name|cons_eol
argument_list|,
name|hcol
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|image_id
operator|=
name|emitgimp
argument_list|(
name|hcol
argument_list|,
name|row
argument_list|,
name|bitmap
argument_list|,
name|bperrow
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bitmap
argument_list|)
expr_stmt|;
return|return
name|image_id
return|;
block|}
end_function

begin_comment
comment|/* hcol is the number of columns, row the number of rows  * bperrow is the number of bytes actually used by hcol, which may  * be greater than (hcol+7)/8 [in case of an unscaled g3 image less  * than 1728 pixels wide]  */
end_comment

begin_function
specifier|static
name|gint32
DECL|function|emitgimp (gint hcol,gint row,const gchar * bitmap,gint bperrow,const gchar * filename)
name|emitgimp
parameter_list|(
name|gint
name|hcol
parameter_list|,
name|gint
name|row
parameter_list|,
specifier|const
name|gchar
modifier|*
name|bitmap
parameter_list|,
name|gint
name|bperrow
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpPixelRgn
name|pixel_rgn
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|gint32
name|layer_ID
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|guchar
name|tmp
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|xx
decl_stmt|,
name|yy
decl_stmt|,
name|tile_height
decl_stmt|;
comment|/* initialize */
name|tmp
operator|=
literal|0
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG
name|g_printerr
argument_list|(
literal|"emit gimp: %d x %d\n"
argument_list|,
name|hcol
argument_list|,
name|row
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|image_ID
operator|=
name|gimp_image_new
argument_list|(
name|hcol
argument_list|,
name|row
argument_list|,
name|GIMP_GRAY
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
name|hcol
argument_list|,
name|row
argument_list|,
name|GIMP_GRAY_IMAGE
argument_list|,
literal|100
argument_list|,
name|GIMP_NORMAL_MODE
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
ifdef|#
directive|ifdef
name|DEBUG
name|g_printerr
argument_list|(
literal|"tile height: %d\n"
argument_list|,
name|tile_height
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|hcol
operator|*
name|tile_height
argument_list|)
expr_stmt|;
name|xx
operator|=
literal|0
expr_stmt|;
name|yy
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|row
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|hcol
condition|;
name|x
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|x
operator|&
literal|7
operator|)
operator|==
literal|0
condition|)
name|tmp
operator|=
name|bitmap
index|[
name|y
operator|*
name|bperrow
operator|+
operator|(
name|x
operator|>>
literal|3
operator|)
index|]
expr_stmt|;
name|buf
index|[
name|xx
operator|++
index|]
operator|=
name|tmp
operator|&
operator|(
literal|128
operator|>>
operator|(
name|x
operator|&
literal|7
operator|)
operator|)
condition|?
literal|0
else|:
literal|255
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|y
operator|-
name|yy
operator|)
operator|==
name|tile_height
operator|-
literal|1
condition|)
block|{
ifdef|#
directive|ifdef
name|DEBUG
name|g_printerr
argument_list|(
literal|"update tile height: %d\n"
argument_list|,
name|tile_height
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|buf
argument_list|,
literal|0
argument_list|,
name|yy
argument_list|,
name|hcol
argument_list|,
name|tile_height
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|0.5
operator|+
operator|(
name|float
operator|)
name|y
operator|/
name|row
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|xx
operator|=
literal|0
expr_stmt|;
name|yy
operator|+=
name|tile_height
expr_stmt|;
block|}
block|}
if|if
condition|(
name|row
operator|-
name|yy
condition|)
block|{
ifdef|#
directive|ifdef
name|DEBUG
name|g_printerr
argument_list|(
literal|"update rest: %d\n"
argument_list|,
name|row
operator|-
name|yy
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|buf
argument_list|,
literal|0
argument_list|,
name|yy
argument_list|,
name|hcol
argument_list|,
name|row
operator|-
name|yy
argument_list|)
expr_stmt|;
block|}
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
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

end_unit

