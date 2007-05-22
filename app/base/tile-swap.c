begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpwin32-io.h"
end_include

begin_include
include|#
directive|include
file|<process.h>
end_include

begin_define
DECL|macro|getpid
define|#
directive|define
name|getpid
value|_getpid
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"base-types.h"
end_include

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

begin_ifndef
ifndef|#
directive|ifndef
name|_O_TEMPORARY
end_ifndef

begin_define
DECL|macro|_O_TEMPORARY
define|#
directive|define
name|_O_TEMPORARY
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"tile.h"
end_include

begin_include
include|#
directive|include
file|"tile-private.h"
end_include

begin_include
include|#
directive|include
file|"tile-swap.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b0c9fd80103
block|{
DECL|enumerator|SWAP_IN
name|SWAP_IN
init|=
literal|1
block|,
DECL|enumerator|SWAP_OUT
name|SWAP_OUT
block|,
DECL|enumerator|SWAP_DELETE
name|SWAP_DELETE
DECL|typedef|SwapCommand
block|}
name|SwapCommand
typedef|;
end_typedef

begin_typedef
DECL|typedef|SwapFunc
typedef|typedef
name|gint
function_decl|(
modifier|*
name|SwapFunc
function_decl|)
parameter_list|(
name|gint
name|fd
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|,
name|SwapCommand
name|cmd
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|MAX_OPEN_SWAP_FILES
define|#
directive|define
name|MAX_OPEN_SWAP_FILES
value|16
end_define

begin_typedef
DECL|typedef|SwapFile
typedef|typedef
name|struct
name|_SwapFile
name|SwapFile
typedef|;
end_typedef

begin_typedef
DECL|typedef|SwapFileGap
typedef|typedef
name|struct
name|_SwapFileGap
name|SwapFileGap
typedef|;
end_typedef

begin_struct
DECL|struct|_SwapFile
struct|struct
name|_SwapFile
block|{
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|fd
name|gint
name|fd
decl_stmt|;
DECL|member|gaps
name|GList
modifier|*
name|gaps
decl_stmt|;
DECL|member|swap_file_end
name|gint64
name|swap_file_end
decl_stmt|;
DECL|member|cur_position
name|gint64
name|cur_position
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_SwapFileGap
struct|struct
name|_SwapFileGap
block|{
DECL|member|start
name|gint64
name|start
decl_stmt|;
DECL|member|end
name|gint64
name|end
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|tile_swap_command
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|gint
name|command
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tile_swap_default_in
parameter_list|(
name|SwapFile
modifier|*
name|swap_file
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tile_swap_default_out
parameter_list|(
name|SwapFile
modifier|*
name|swap_file
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tile_swap_default_delete
parameter_list|(
name|SwapFile
modifier|*
name|swap_file
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|tile_swap_find_offset
parameter_list|(
name|SwapFile
modifier|*
name|swap_file
parameter_list|,
name|gint64
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tile_swap_open
parameter_list|(
name|SwapFile
modifier|*
name|swap_file
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tile_swap_resize
parameter_list|(
name|SwapFile
modifier|*
name|swap_file
parameter_list|,
name|gint64
name|new_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|SwapFileGap
modifier|*
name|tile_swap_gap_new
parameter_list|(
name|gint64
name|start
parameter_list|,
name|gint64
name|end
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tile_swap_gap_destroy
parameter_list|(
name|SwapFileGap
modifier|*
name|gap
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_swap_file
specifier|static
name|SwapFile
modifier|*
name|gimp_swap_file
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|swap_file_grow
specifier|static
specifier|const
name|gint64
name|swap_file_grow
init|=
literal|1024
operator|*
name|TILE_WIDTH
operator|*
name|TILE_HEIGHT
operator|*
literal|4
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|seek_err_msg
specifier|static
name|gboolean
name|seek_err_msg
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|read_err_msg
specifier|static
name|gboolean
name|read_err_msg
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|write_err_msg
specifier|static
name|gboolean
name|write_err_msg
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_function
specifier|static
name|gint
DECL|function|gimp_win32_large_truncate (int fd,gint64 size)
name|gimp_win32_large_truncate
parameter_list|(
name|int
name|fd
parameter_list|,
name|gint64
name|size
parameter_list|)
block|{
if|if
condition|(
name|LARGE_SEEK
argument_list|(
name|fd
argument_list|,
name|size
argument_list|,
name|SEEK_SET
argument_list|)
operator|==
name|size
operator|&&
name|SetEndOfFile
argument_list|(
operator|(
name|HANDLE
operator|)
name|_get_osfhandle
argument_list|(
name|fd
argument_list|)
argument_list|)
condition|)
return|return
literal|0
return|;
else|else
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
end_ifdef

begin_function
specifier|static
name|void
DECL|function|tile_swap_print_gaps (SwapFile * swap_file)
name|tile_swap_print_gaps
parameter_list|(
name|SwapFile
modifier|*
name|swap_file
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|swap_file
operator|->
name|gaps
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|SwapFileGap
modifier|*
name|gap
init|=
name|list
operator|->
name|data
decl_stmt|;
name|g_print
argument_list|(
literal|"  %"
name|G_GINT64_FORMAT
literal|" - %"
name|G_GINT64_FORMAT
literal|"\n"
argument_list|,
name|gap
operator|->
name|start
argument_list|,
name|gap
operator|->
name|end
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|void
DECL|function|tile_swap_init (const gchar * path)
name|tile_swap_init
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|)
block|{
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|dirname
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_swap_file
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|path
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|dirname
operator|=
name|gimp_config_path_expand
argument_list|(
name|path
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|basename
operator|=
name|g_strdup_printf
argument_list|(
literal|"gimpswap.%lu"
argument_list|,
operator|(
name|unsigned
name|long
operator|)
name|getpid
argument_list|()
argument_list|)
expr_stmt|;
comment|/*  create the swap directory if it doesn't exist */
if|if
condition|(
operator|!
name|g_file_test
argument_list|(
name|dirname
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
name|g_mkdir_with_parents
argument_list|(
name|dirname
argument_list|,
name|S_IRUSR
operator||
name|S_IXUSR
operator||
name|S_IWUSR
operator||
name|S_IRGRP
operator||
name|S_IXGRP
operator||
name|S_IROTH
operator||
name|S_IXOTH
argument_list|)
expr_stmt|;
name|gimp_swap_file
operator|=
name|g_slice_new
argument_list|(
name|SwapFile
argument_list|)
expr_stmt|;
name|gimp_swap_file
operator|->
name|filename
operator|=
name|g_build_filename
argument_list|(
name|dirname
argument_list|,
name|basename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_swap_file
operator|->
name|gaps
operator|=
name|NULL
expr_stmt|;
name|gimp_swap_file
operator|->
name|swap_file_end
operator|=
literal|0
expr_stmt|;
name|gimp_swap_file
operator|->
name|cur_position
operator|=
literal|0
expr_stmt|;
name|gimp_swap_file
operator|->
name|fd
operator|=
operator|-
literal|1
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dirname
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tile_swap_exit (void)
name|tile_swap_exit
parameter_list|(
name|void
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|HINTS_SANITY
specifier|extern
name|int
name|tile_exist_peak
decl_stmt|;
name|g_printerr
argument_list|(
literal|"Tile exist peak was %d Tile structs (%d bytes)"
argument_list|,
name|tile_exist_peak
argument_list|,
name|tile_exist_peak
operator|*
sizeof|sizeof
argument_list|(
name|Tile
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|tile_global_refcount
argument_list|()
operator|!=
literal|0
condition|)
name|g_warning
argument_list|(
literal|"tile ref count balance: %d\n"
argument_list|,
name|tile_global_refcount
argument_list|()
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_swap_file
operator|!=
name|NULL
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
if|if
condition|(
name|gimp_swap_file
operator|->
name|swap_file_end
operator|!=
literal|0
condition|)
block|{
name|g_warning
argument_list|(
literal|"swap file not empty: \"%s\"\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|gimp_swap_file
operator|->
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|tile_swap_print_gaps
argument_list|(
name|gimp_swap_file
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
ifdef|#
directive|ifdef
name|G_OS_WIN32
comment|/* should close before unlink */
if|if
condition|(
name|gimp_swap_file
operator|->
name|fd
operator|>
literal|0
condition|)
block|{
name|close
argument_list|(
name|gimp_swap_file
operator|->
name|fd
argument_list|)
expr_stmt|;
name|gimp_swap_file
operator|->
name|fd
operator|=
operator|-
literal|1
expr_stmt|;
block|}
endif|#
directive|endif
name|g_unlink
argument_list|(
name|gimp_swap_file
operator|->
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gimp_swap_file
operator|->
name|filename
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|SwapFile
argument_list|,
name|gimp_swap_file
argument_list|)
expr_stmt|;
name|gimp_swap_file
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_comment
comment|/* check if we can open a swap file */
end_comment

begin_function
name|gboolean
DECL|function|tile_swap_test (void)
name|tile_swap_test
parameter_list|(
name|void
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|gimp_swap_file
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* make sure this duplicates the open() call from tile_swap_open() */
name|gimp_swap_file
operator|->
name|fd
operator|=
name|g_open
argument_list|(
name|gimp_swap_file
operator|->
name|filename
argument_list|,
name|O_CREAT
operator||
name|O_RDWR
operator||
name|_O_BINARY
operator||
name|_O_TEMPORARY
argument_list|,
name|S_IRUSR
operator||
name|S_IWUSR
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_swap_file
operator|->
name|fd
operator|!=
operator|-
literal|1
condition|)
block|{
name|close
argument_list|(
name|gimp_swap_file
operator|->
name|fd
argument_list|)
expr_stmt|;
name|gimp_swap_file
operator|->
name|fd
operator|=
operator|-
literal|1
expr_stmt|;
name|g_unlink
argument_list|(
name|gimp_swap_file
operator|->
name|filename
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

begin_function
name|void
DECL|function|tile_swap_in (Tile * tile)
name|tile_swap_in
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
if|if
condition|(
name|tile
operator|->
name|swap_offset
operator|==
operator|-
literal|1
condition|)
block|{
name|tile_alloc
argument_list|(
name|tile
argument_list|)
expr_stmt|;
return|return;
block|}
name|tile_swap_command
argument_list|(
name|tile
argument_list|,
name|SWAP_IN
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tile_swap_out (Tile * tile)
name|tile_swap_out
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
name|tile_swap_command
argument_list|(
name|tile
argument_list|,
name|SWAP_OUT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tile_swap_delete (Tile * tile)
name|tile_swap_delete
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
name|tile_swap_command
argument_list|(
name|tile
argument_list|,
name|SWAP_DELETE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_swap_command (Tile * tile,gint command)
name|tile_swap_command
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|gint
name|command
parameter_list|)
block|{
if|if
condition|(
name|gimp_swap_file
operator|->
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|tile_swap_open
argument_list|(
name|gimp_swap_file
argument_list|)
expr_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
name|gimp_swap_file
operator|->
name|fd
operator|==
operator|-
literal|1
argument_list|)
condition|)
return|return;
block|}
switch|switch
condition|(
name|command
condition|)
block|{
case|case
name|SWAP_IN
case|:
name|tile_swap_default_in
argument_list|(
name|gimp_swap_file
argument_list|,
name|tile
argument_list|)
expr_stmt|;
break|break;
case|case
name|SWAP_OUT
case|:
name|tile_swap_default_out
argument_list|(
name|gimp_swap_file
argument_list|,
name|tile
argument_list|)
expr_stmt|;
break|break;
case|case
name|SWAP_DELETE
case|:
name|tile_swap_default_delete
argument_list|(
name|gimp_swap_file
argument_list|,
name|tile
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_comment
comment|/* The actual swap file code. The swap file consists of tiles  *  which have been moved out to disk in order to conserve memory.  *  The swap file format is free form. Any tile in memory may  *  end up anywhere on disk.  * An actual tile in the swap file consists only of the tile data.  *  The offset of the tile on disk is stored in the tile data structure  *  in memory.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|tile_swap_default_in (SwapFile * swap_file,Tile * tile)
name|tile_swap_default_in
parameter_list|(
name|SwapFile
modifier|*
name|swap_file
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
name|gint
name|nleft
decl_stmt|;
name|gint64
name|offset
decl_stmt|;
if|if
condition|(
name|tile
operator|->
name|data
condition|)
return|return;
if|if
condition|(
name|swap_file
operator|->
name|cur_position
operator|!=
name|tile
operator|->
name|swap_offset
condition|)
block|{
name|swap_file
operator|->
name|cur_position
operator|=
name|tile
operator|->
name|swap_offset
expr_stmt|;
name|offset
operator|=
name|LARGE_SEEK
argument_list|(
name|swap_file
operator|->
name|fd
argument_list|,
name|tile
operator|->
name|swap_offset
argument_list|,
name|SEEK_SET
argument_list|)
expr_stmt|;
if|if
condition|(
name|offset
operator|==
operator|-
literal|1
condition|)
block|{
if|if
condition|(
name|seek_err_msg
condition|)
name|g_message
argument_list|(
literal|"unable to seek to tile location on disk: %s"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|seek_err_msg
operator|=
name|FALSE
expr_stmt|;
return|return;
block|}
block|}
name|tile_alloc
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|nleft
operator|=
name|tile
operator|->
name|size
expr_stmt|;
while|while
condition|(
name|nleft
operator|>
literal|0
condition|)
block|{
name|gint
name|err
decl_stmt|;
do|do
block|{
name|err
operator|=
name|read
argument_list|(
name|swap_file
operator|->
name|fd
argument_list|,
name|tile
operator|->
name|data
operator|+
name|tile
operator|->
name|size
operator|-
name|nleft
argument_list|,
name|nleft
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
operator|(
name|err
operator|==
operator|-
literal|1
operator|)
operator|&&
operator|(
operator|(
name|errno
operator|==
name|EAGAIN
operator|)
operator|||
operator|(
name|errno
operator|==
name|EINTR
operator|)
operator|)
condition|)
do|;
if|if
condition|(
name|err
operator|<=
literal|0
condition|)
block|{
if|if
condition|(
name|read_err_msg
condition|)
name|g_message
argument_list|(
literal|"unable to read tile data from disk: "
literal|"%s (%d/%d bytes read)"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|,
name|err
argument_list|,
name|nleft
argument_list|)
expr_stmt|;
name|read_err_msg
operator|=
name|FALSE
expr_stmt|;
return|return;
block|}
name|nleft
operator|-=
name|err
expr_stmt|;
block|}
name|swap_file
operator|->
name|cur_position
operator|+=
name|tile
operator|->
name|size
expr_stmt|;
comment|/*  Do not delete the swap from the file  */
comment|/*  tile_swap_default_delete (swap_file, fd, tile);  */
name|read_err_msg
operator|=
name|seek_err_msg
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_swap_default_out (SwapFile * swap_file,Tile * tile)
name|tile_swap_default_out
parameter_list|(
name|SwapFile
modifier|*
name|swap_file
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
name|gint
name|bytes
decl_stmt|;
name|gint
name|nleft
decl_stmt|;
name|gint64
name|offset
decl_stmt|;
name|gint64
name|newpos
decl_stmt|;
name|bytes
operator|=
name|TILE_WIDTH
operator|*
name|TILE_HEIGHT
operator|*
name|tile
operator|->
name|bpp
expr_stmt|;
comment|/*  If there is already a valid swap_offset, use it  */
if|if
condition|(
name|tile
operator|->
name|swap_offset
operator|==
operator|-
literal|1
condition|)
name|newpos
operator|=
name|tile_swap_find_offset
argument_list|(
name|swap_file
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
else|else
name|newpos
operator|=
name|tile
operator|->
name|swap_offset
expr_stmt|;
if|if
condition|(
name|swap_file
operator|->
name|cur_position
operator|!=
name|newpos
condition|)
block|{
name|offset
operator|=
name|LARGE_SEEK
argument_list|(
name|swap_file
operator|->
name|fd
argument_list|,
name|newpos
argument_list|,
name|SEEK_SET
argument_list|)
expr_stmt|;
if|if
condition|(
name|offset
operator|==
operator|-
literal|1
condition|)
block|{
if|if
condition|(
name|seek_err_msg
condition|)
name|g_message
argument_list|(
literal|"unable to seek to tile location on disk: %s"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|seek_err_msg
operator|=
name|FALSE
expr_stmt|;
return|return;
block|}
name|swap_file
operator|->
name|cur_position
operator|=
name|newpos
expr_stmt|;
block|}
name|nleft
operator|=
name|tile
operator|->
name|size
expr_stmt|;
while|while
condition|(
name|nleft
operator|>
literal|0
condition|)
block|{
name|gint
name|err
init|=
name|write
argument_list|(
name|swap_file
operator|->
name|fd
argument_list|,
name|tile
operator|->
name|data
operator|+
name|tile
operator|->
name|size
operator|-
name|nleft
argument_list|,
name|nleft
argument_list|)
decl_stmt|;
if|if
condition|(
name|err
operator|<=
literal|0
condition|)
block|{
if|if
condition|(
name|write_err_msg
condition|)
name|g_message
argument_list|(
literal|"unable to write tile data to disk: "
literal|"%s (%d/%d bytes written)"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|,
name|err
argument_list|,
name|nleft
argument_list|)
expr_stmt|;
name|write_err_msg
operator|=
name|FALSE
expr_stmt|;
return|return;
block|}
name|nleft
operator|-=
name|err
expr_stmt|;
block|}
name|swap_file
operator|->
name|cur_position
operator|+=
name|tile
operator|->
name|size
expr_stmt|;
comment|/* Do NOT free tile->data because we may be pre-swapping.    * tile->data is freed in tile_cache_zorch_next    */
name|tile
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
name|tile
operator|->
name|swap_offset
operator|=
name|newpos
expr_stmt|;
name|write_err_msg
operator|=
name|seek_err_msg
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_swap_default_delete (SwapFile * swap_file,Tile * tile)
name|tile_swap_default_delete
parameter_list|(
name|SwapFile
modifier|*
name|swap_file
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
name|SwapFileGap
modifier|*
name|gap
decl_stmt|;
name|SwapFileGap
modifier|*
name|gap2
decl_stmt|;
name|GList
modifier|*
name|tmp
decl_stmt|;
name|GList
modifier|*
name|tmp2
decl_stmt|;
name|gint64
name|start
decl_stmt|;
name|gint64
name|end
decl_stmt|;
if|if
condition|(
name|tile
operator|->
name|swap_offset
operator|==
operator|-
literal|1
condition|)
return|return;
name|start
operator|=
name|tile
operator|->
name|swap_offset
expr_stmt|;
name|end
operator|=
name|start
operator|+
name|TILE_WIDTH
operator|*
name|TILE_HEIGHT
operator|*
name|tile
operator|->
name|bpp
expr_stmt|;
name|tile
operator|->
name|swap_offset
operator|=
operator|-
literal|1
expr_stmt|;
name|tmp
operator|=
name|swap_file
operator|->
name|gaps
expr_stmt|;
while|while
condition|(
name|tmp
condition|)
block|{
name|gap
operator|=
name|tmp
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|end
operator|==
name|gap
operator|->
name|start
condition|)
block|{
name|gap
operator|->
name|start
operator|=
name|start
expr_stmt|;
if|if
condition|(
name|tmp
operator|->
name|prev
condition|)
block|{
name|gap2
operator|=
name|tmp
operator|->
name|prev
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gap
operator|->
name|start
operator|==
name|gap2
operator|->
name|end
condition|)
block|{
name|gap2
operator|->
name|end
operator|=
name|gap
operator|->
name|end
expr_stmt|;
name|tile_swap_gap_destroy
argument_list|(
name|gap
argument_list|)
expr_stmt|;
name|swap_file
operator|->
name|gaps
operator|=
name|g_list_remove_link
argument_list|(
name|swap_file
operator|->
name|gaps
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
block|}
elseif|else
if|if
condition|(
name|start
operator|==
name|gap
operator|->
name|end
condition|)
block|{
name|gap
operator|->
name|end
operator|=
name|end
expr_stmt|;
if|if
condition|(
name|tmp
operator|->
name|next
condition|)
block|{
name|gap2
operator|=
name|tmp
operator|->
name|next
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gap
operator|->
name|end
operator|==
name|gap2
operator|->
name|start
condition|)
block|{
name|gap2
operator|->
name|start
operator|=
name|gap
operator|->
name|start
expr_stmt|;
name|tile_swap_gap_destroy
argument_list|(
name|gap
argument_list|)
expr_stmt|;
name|swap_file
operator|->
name|gaps
operator|=
name|g_list_remove_link
argument_list|(
name|swap_file
operator|->
name|gaps
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
block|}
elseif|else
if|if
condition|(
name|end
operator|<
name|gap
operator|->
name|start
condition|)
block|{
name|gap
operator|=
name|tile_swap_gap_new
argument_list|(
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
name|tmp2
operator|=
name|g_list_alloc
argument_list|()
expr_stmt|;
name|tmp2
operator|->
name|data
operator|=
name|gap
expr_stmt|;
name|tmp2
operator|->
name|next
operator|=
name|tmp
expr_stmt|;
name|tmp2
operator|->
name|prev
operator|=
name|tmp
operator|->
name|prev
expr_stmt|;
if|if
condition|(
name|tmp
operator|->
name|prev
condition|)
name|tmp
operator|->
name|prev
operator|->
name|next
operator|=
name|tmp2
expr_stmt|;
name|tmp
operator|->
name|prev
operator|=
name|tmp2
expr_stmt|;
if|if
condition|(
name|tmp
operator|==
name|swap_file
operator|->
name|gaps
condition|)
name|swap_file
operator|->
name|gaps
operator|=
name|tmp2
expr_stmt|;
break|break;
block|}
elseif|else
if|if
condition|(
operator|!
name|tmp
operator|->
name|next
condition|)
block|{
name|gap
operator|=
name|tile_swap_gap_new
argument_list|(
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
name|tmp
operator|->
name|next
operator|=
name|g_list_alloc
argument_list|()
expr_stmt|;
name|tmp
operator|->
name|next
operator|->
name|data
operator|=
name|gap
expr_stmt|;
name|tmp
operator|->
name|next
operator|->
name|prev
operator|=
name|tmp
expr_stmt|;
break|break;
block|}
name|tmp
operator|=
name|tmp
operator|->
name|next
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|swap_file
operator|->
name|gaps
condition|)
block|{
name|gap
operator|=
name|tile_swap_gap_new
argument_list|(
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
name|swap_file
operator|->
name|gaps
operator|=
name|g_list_append
argument_list|(
name|swap_file
operator|->
name|gaps
argument_list|,
name|gap
argument_list|)
expr_stmt|;
block|}
name|tmp
operator|=
name|g_list_last
argument_list|(
name|swap_file
operator|->
name|gaps
argument_list|)
expr_stmt|;
name|gap
operator|=
name|tmp
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gap
operator|->
name|end
operator|==
name|swap_file
operator|->
name|swap_file_end
condition|)
block|{
name|tile_swap_resize
argument_list|(
name|swap_file
argument_list|,
name|gap
operator|->
name|start
argument_list|)
expr_stmt|;
name|tile_swap_gap_destroy
argument_list|(
name|gap
argument_list|)
expr_stmt|;
name|swap_file
operator|->
name|gaps
operator|=
name|g_list_remove_link
argument_list|(
name|swap_file
operator|->
name|gaps
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_swap_open (SwapFile * swap_file)
name|tile_swap_open
parameter_list|(
name|SwapFile
modifier|*
name|swap_file
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|swap_file
operator|->
name|fd
operator|==
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/* duplicate this open() call in tile_swap_test() */
name|swap_file
operator|->
name|fd
operator|=
name|g_open
argument_list|(
name|swap_file
operator|->
name|filename
argument_list|,
name|O_CREAT
operator||
name|O_RDWR
operator||
name|_O_BINARY
operator||
name|_O_TEMPORARY
argument_list|,
name|S_IRUSR
operator||
name|S_IWUSR
argument_list|)
expr_stmt|;
if|if
condition|(
name|swap_file
operator|->
name|fd
operator|==
operator|-
literal|1
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Unable to open swap file. GIMP has run out of memory "
literal|"and cannot use the swap file. Some parts of your images "
literal|"may be corrupted. Try to save your work using different "
literal|"filenames, restart GIMP and check the location of the "
literal|"swap directory in your Preferences."
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_swap_resize (SwapFile * swap_file,gint64 new_size)
name|tile_swap_resize
parameter_list|(
name|SwapFile
modifier|*
name|swap_file
parameter_list|,
name|gint64
name|new_size
parameter_list|)
block|{
if|if
condition|(
name|swap_file
operator|->
name|swap_file_end
operator|>
name|new_size
condition|)
block|{
if|if
condition|(
name|LARGE_TRUNCATE
argument_list|(
name|swap_file
operator|->
name|fd
argument_list|,
name|new_size
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Failed to resize swap file: %s"
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
name|swap_file
operator|->
name|swap_file_end
operator|=
name|new_size
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint64
DECL|function|tile_swap_find_offset (SwapFile * swap_file,gint64 bytes)
name|tile_swap_find_offset
parameter_list|(
name|SwapFile
modifier|*
name|swap_file
parameter_list|,
name|gint64
name|bytes
parameter_list|)
block|{
name|SwapFileGap
modifier|*
name|gap
decl_stmt|;
name|GList
modifier|*
name|tmp
decl_stmt|;
name|gint64
name|offset
decl_stmt|;
name|tmp
operator|=
name|swap_file
operator|->
name|gaps
expr_stmt|;
while|while
condition|(
name|tmp
condition|)
block|{
name|gap
operator|=
name|tmp
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|(
name|gap
operator|->
name|end
operator|-
name|gap
operator|->
name|start
operator|)
operator|>=
name|bytes
condition|)
block|{
name|offset
operator|=
name|gap
operator|->
name|start
expr_stmt|;
name|gap
operator|->
name|start
operator|+=
name|bytes
expr_stmt|;
if|if
condition|(
name|gap
operator|->
name|start
operator|==
name|gap
operator|->
name|end
condition|)
block|{
name|tile_swap_gap_destroy
argument_list|(
name|gap
argument_list|)
expr_stmt|;
name|swap_file
operator|->
name|gaps
operator|=
name|g_list_remove_link
argument_list|(
name|swap_file
operator|->
name|gaps
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
return|return
name|offset
return|;
block|}
name|tmp
operator|=
name|tmp
operator|->
name|next
expr_stmt|;
block|}
name|offset
operator|=
name|swap_file
operator|->
name|swap_file_end
expr_stmt|;
name|tile_swap_resize
argument_list|(
name|swap_file
argument_list|,
name|swap_file
operator|->
name|swap_file_end
operator|+
name|swap_file_grow
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|offset
operator|+
name|bytes
operator|)
operator|<
operator|(
name|swap_file
operator|->
name|swap_file_end
operator|)
condition|)
block|{
name|gap
operator|=
name|tile_swap_gap_new
argument_list|(
name|offset
operator|+
name|bytes
argument_list|,
name|swap_file
operator|->
name|swap_file_end
argument_list|)
expr_stmt|;
name|swap_file
operator|->
name|gaps
operator|=
name|g_list_append
argument_list|(
name|swap_file
operator|->
name|gaps
argument_list|,
name|gap
argument_list|)
expr_stmt|;
block|}
return|return
name|offset
return|;
block|}
end_function

begin_function
specifier|static
name|SwapFileGap
modifier|*
DECL|function|tile_swap_gap_new (gint64 start,gint64 end)
name|tile_swap_gap_new
parameter_list|(
name|gint64
name|start
parameter_list|,
name|gint64
name|end
parameter_list|)
block|{
name|SwapFileGap
modifier|*
name|gap
init|=
name|g_slice_new
argument_list|(
name|SwapFileGap
argument_list|)
decl_stmt|;
name|gap
operator|->
name|start
operator|=
name|start
expr_stmt|;
name|gap
operator|->
name|end
operator|=
name|end
expr_stmt|;
return|return
name|gap
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_swap_gap_destroy (SwapFileGap * gap)
name|tile_swap_gap_destroy
parameter_list|(
name|SwapFileGap
modifier|*
name|gap
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|SwapFileGap
argument_list|,
name|gap
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

