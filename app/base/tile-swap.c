begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
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

begin_ifdef
ifdef|#
directive|ifdef
name|USE_PTHREADS
end_ifdef

begin_include
include|#
directive|include
file|<pthread.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|MAX_OPEN_SWAP_FILES
define|#
directive|define
name|MAX_OPEN_SWAP_FILES
value|16
end_define

begin_include
include|#
directive|include
file|"tile_swap.h"
end_include

begin_typedef
DECL|typedef|SwapFile
typedef|typedef
name|struct
name|_SwapFile
name|SwapFile
typedef|;
end_typedef

begin_typedef
DECL|typedef|DefSwapFile
typedef|typedef
name|struct
name|_DefSwapFile
name|DefSwapFile
typedef|;
end_typedef

begin_typedef
DECL|typedef|Gap
typedef|typedef
name|struct
name|_Gap
name|Gap
typedef|;
end_typedef

begin_struct
DECL|struct|_SwapFile
struct|struct
name|_SwapFile
block|{
DECL|member|filename
name|char
modifier|*
name|filename
decl_stmt|;
DECL|member|swap_num
name|int
name|swap_num
decl_stmt|;
DECL|member|swap_func
name|SwapFunc
name|swap_func
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|member|fd
name|int
name|fd
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_DefSwapFile
struct|struct
name|_DefSwapFile
block|{
DECL|member|gaps
name|GList
modifier|*
name|gaps
decl_stmt|;
DECL|member|swap_file_end
name|long
name|swap_file_end
decl_stmt|;
DECL|member|cur_position
name|off_t
name|cur_position
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_Gap
struct|struct
name|_Gap
block|{
DECL|member|start
name|long
name|start
decl_stmt|;
DECL|member|end
name|long
name|end
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|tile_swap_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|guint
name|tile_swap_hash
parameter_list|(
name|int
modifier|*
name|key
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|tile_swap_compare
parameter_list|(
name|int
modifier|*
name|a
parameter_list|,
name|int
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tile_swap_command
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|command
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
name|int
name|tile_swap_default
parameter_list|(
name|int
name|fd
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|cmd
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tile_swap_default_in
parameter_list|(
name|DefSwapFile
modifier|*
name|def_swap_file
parameter_list|,
name|int
name|fd
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
name|DefSwapFile
modifier|*
name|def_swap_file
parameter_list|,
name|int
name|fd
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
name|DefSwapFile
modifier|*
name|def_swap_file
parameter_list|,
name|int
name|fd
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|long
name|tile_swap_find_offset
parameter_list|(
name|DefSwapFile
modifier|*
name|def_swap_file
parameter_list|,
name|int
name|fd
parameter_list|,
name|int
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tile_swap_resize
parameter_list|(
name|DefSwapFile
modifier|*
name|def_swap_file
parameter_list|,
name|int
name|fd
parameter_list|,
name|long
name|new_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|Gap
modifier|*
name|tile_swap_gap_new
parameter_list|(
name|long
name|start
parameter_list|,
name|long
name|end
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tile_swap_gap_destroy
parameter_list|(
name|Gap
modifier|*
name|gap
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|initialize
specifier|static
name|int
name|initialize
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|swap_files
specifier|static
name|GHashTable
modifier|*
name|swap_files
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|open_swap_files
specifier|static
name|GList
modifier|*
name|open_swap_files
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|nopen_swap_files
specifier|static
name|int
name|nopen_swap_files
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|next_swap_num
specifier|static
name|int
name|next_swap_num
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|swap_file_grow
specifier|static
name|long
name|swap_file_grow
init|=
literal|16
operator|*
name|TILE_WIDTH
operator|*
name|TILE_HEIGHT
operator|*
literal|4
decl_stmt|;
end_decl_stmt

begin_ifdef
ifdef|#
directive|ifdef
name|USE_PTHREADS
end_ifdef

begin_decl_stmt
DECL|variable|swapfile_mutex
specifier|static
name|pthread_mutex_t
name|swapfile_mutex
init|=
name|PTHREAD_MUTEX_INITIALIZER
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|seek_err_msg
DECL|variable|read_err_msg
DECL|variable|write_err_msg
specifier|static
name|gboolean
name|seek_err_msg
init|=
name|TRUE
decl_stmt|,
name|read_err_msg
init|=
name|TRUE
decl_stmt|,
name|write_err_msg
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|tile_swap_print_gaps (DefSwapFile * def_swap_file)
name|tile_swap_print_gaps
parameter_list|(
name|DefSwapFile
modifier|*
name|def_swap_file
parameter_list|)
block|{
name|GList
modifier|*
name|gaps
decl_stmt|;
name|Gap
modifier|*
name|gap
decl_stmt|;
name|gaps
operator|=
name|def_swap_file
operator|->
name|gaps
expr_stmt|;
while|while
condition|(
name|gaps
condition|)
block|{
name|gap
operator|=
name|gaps
operator|->
name|data
expr_stmt|;
name|gaps
operator|=
name|gaps
operator|->
name|next
expr_stmt|;
name|g_print
argument_list|(
literal|"  %6ld - %6ld\n"
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

begin_function
specifier|static
name|void
DECL|function|tile_swap_exit1 (gpointer key,gpointer value,gpointer data)
name|tile_swap_exit1
parameter_list|(
name|gpointer
name|key
parameter_list|,
name|gpointer
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
specifier|extern
name|int
name|tile_ref_count
decl_stmt|;
name|SwapFile
modifier|*
name|swap_file
decl_stmt|;
name|DefSwapFile
modifier|*
name|def_swap_file
decl_stmt|;
if|if
condition|(
name|tile_ref_count
operator|!=
literal|0
condition|)
name|g_message
argument_list|(
literal|"tile ref count balance: %d\n"
argument_list|,
name|tile_ref_count
argument_list|)
expr_stmt|;
name|swap_file
operator|=
name|value
expr_stmt|;
if|if
condition|(
name|swap_file
operator|->
name|swap_func
operator|==
name|tile_swap_default
condition|)
block|{
name|def_swap_file
operator|=
name|swap_file
operator|->
name|user_data
expr_stmt|;
if|if
condition|(
name|def_swap_file
operator|->
name|swap_file_end
operator|!=
literal|0
condition|)
block|{
name|g_message
argument_list|(
literal|"swap file not empty: \"%s\"\n"
argument_list|,
name|swap_file
operator|->
name|filename
argument_list|)
expr_stmt|;
name|tile_swap_print_gaps
argument_list|(
name|def_swap_file
argument_list|)
expr_stmt|;
block|}
name|unlink
argument_list|(
name|swap_file
operator|->
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tile_swap_exit ()
name|tile_swap_exit
parameter_list|()
block|{
if|if
condition|(
name|swap_files
condition|)
name|g_hash_table_foreach
argument_list|(
name|swap_files
argument_list|,
name|tile_swap_exit1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|int
DECL|function|tile_swap_add (char * filename,SwapFunc swap_func,gpointer user_data)
name|tile_swap_add
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|,
name|SwapFunc
name|swap_func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|SwapFile
modifier|*
name|swap_file
decl_stmt|;
name|DefSwapFile
modifier|*
name|def_swap_file
decl_stmt|;
ifdef|#
directive|ifdef
name|USE_PTHREADS
name|pthread_mutex_lock
argument_list|(
operator|&
name|swapfile_mutex
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|initialize
condition|)
name|tile_swap_init
argument_list|()
expr_stmt|;
name|swap_file
operator|=
name|g_new
argument_list|(
name|SwapFile
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|swap_file
operator|->
name|filename
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|swap_file
operator|->
name|swap_num
operator|=
name|next_swap_num
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|swap_func
condition|)
block|{
name|swap_func
operator|=
name|tile_swap_default
expr_stmt|;
name|def_swap_file
operator|=
name|g_new
argument_list|(
name|DefSwapFile
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|def_swap_file
operator|->
name|gaps
operator|=
name|NULL
expr_stmt|;
name|def_swap_file
operator|->
name|swap_file_end
operator|=
literal|0
expr_stmt|;
name|def_swap_file
operator|->
name|cur_position
operator|=
literal|0
expr_stmt|;
name|user_data
operator|=
name|def_swap_file
expr_stmt|;
block|}
name|swap_file
operator|->
name|swap_func
operator|=
name|swap_func
expr_stmt|;
name|swap_file
operator|->
name|user_data
operator|=
name|user_data
expr_stmt|;
name|swap_file
operator|->
name|fd
operator|=
operator|-
literal|1
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|swap_files
argument_list|,
operator|&
name|swap_file
operator|->
name|swap_num
argument_list|,
name|swap_file
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|USE_PTHREADS
name|pthread_mutex_unlock
argument_list|(
operator|&
name|swapfile_mutex
argument_list|)
expr_stmt|;
endif|#
directive|endif
return|return
name|swap_file
operator|->
name|swap_num
return|;
block|}
end_function

begin_function
name|void
DECL|function|tile_swap_remove (int swap_num)
name|tile_swap_remove
parameter_list|(
name|int
name|swap_num
parameter_list|)
block|{
name|SwapFile
modifier|*
name|swap_file
decl_stmt|;
ifdef|#
directive|ifdef
name|USE_PTHREADS
name|pthread_mutex_lock
argument_list|(
operator|&
name|swapfile_mutex
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|initialize
condition|)
name|tile_swap_init
argument_list|()
expr_stmt|;
name|swap_file
operator|=
name|g_hash_table_lookup
argument_list|(
name|swap_files
argument_list|,
operator|&
name|swap_num
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|swap_file
condition|)
goto|goto
name|out
goto|;
name|g_hash_table_remove
argument_list|(
name|swap_files
argument_list|,
operator|&
name|swap_num
argument_list|)
expr_stmt|;
if|if
condition|(
name|swap_file
operator|->
name|fd
operator|!=
operator|-
literal|1
condition|)
name|close
argument_list|(
name|swap_file
operator|->
name|fd
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|swap_file
argument_list|)
expr_stmt|;
name|out
label|:
ifdef|#
directive|ifdef
name|USE_PTHREADS
name|pthread_mutex_unlock
argument_list|(
operator|&
name|swapfile_mutex
argument_list|)
expr_stmt|;
endif|#
directive|endif
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
name|void
DECL|function|tile_swap_compress (int swap_num)
name|tile_swap_compress
parameter_list|(
name|int
name|swap_num
parameter_list|)
block|{
name|tile_swap_command
argument_list|(
name|NULL
argument_list|,
name|SWAP_COMPRESS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_swap_init ()
name|tile_swap_init
parameter_list|()
block|{
if|if
condition|(
name|initialize
condition|)
block|{
name|initialize
operator|=
name|FALSE
expr_stmt|;
name|swap_files
operator|=
name|g_hash_table_new
argument_list|(
operator|(
name|GHashFunc
operator|)
name|tile_swap_hash
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|tile_swap_compare
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|guint
DECL|function|tile_swap_hash (int * key)
name|tile_swap_hash
parameter_list|(
name|int
modifier|*
name|key
parameter_list|)
block|{
return|return
operator|(
operator|(
name|guint
operator|)
operator|*
name|key
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|tile_swap_compare (int * a,int * b)
name|tile_swap_compare
parameter_list|(
name|int
modifier|*
name|a
parameter_list|,
name|int
modifier|*
name|b
parameter_list|)
block|{
return|return
operator|(
operator|*
name|a
operator|==
operator|*
name|b
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_swap_command (Tile * tile,int command)
name|tile_swap_command
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|command
parameter_list|)
block|{
name|SwapFile
modifier|*
name|swap_file
decl_stmt|;
ifdef|#
directive|ifdef
name|USE_PTHREADS
name|pthread_mutex_lock
argument_list|(
operator|&
name|swapfile_mutex
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|initialize
condition|)
name|tile_swap_init
argument_list|()
expr_stmt|;
do|do
block|{
name|swap_file
operator|=
name|g_hash_table_lookup
argument_list|(
name|swap_files
argument_list|,
operator|&
name|tile
operator|->
name|swap_num
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|swap_file
condition|)
block|{
name|g_message
argument_list|(
literal|"could not find swap file for tile"
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
block|}
if|if
condition|(
name|swap_file
operator|->
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|tile_swap_open
argument_list|(
name|swap_file
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
goto|goto
name|out
goto|;
block|}
block|}
do|while
condition|(
call|(
modifier|*
name|swap_file
operator|->
name|swap_func
call|)
argument_list|(
name|swap_file
operator|->
name|fd
argument_list|,
name|tile
argument_list|,
name|command
argument_list|,
name|swap_file
operator|->
name|user_data
argument_list|)
condition|)
do|;
name|out
label|:
ifdef|#
directive|ifdef
name|USE_PTHREADS
name|pthread_mutex_unlock
argument_list|(
operator|&
name|swapfile_mutex
argument_list|)
expr_stmt|;
endif|#
directive|endif
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
name|SwapFile
modifier|*
name|tmp
decl_stmt|;
if|if
condition|(
name|swap_file
operator|->
name|fd
operator|!=
operator|-
literal|1
condition|)
return|return;
if|if
condition|(
name|nopen_swap_files
operator|==
name|MAX_OPEN_SWAP_FILES
condition|)
block|{
name|tmp
operator|=
name|open_swap_files
operator|->
name|data
expr_stmt|;
name|close
argument_list|(
name|tmp
operator|->
name|fd
argument_list|)
expr_stmt|;
name|tmp
operator|->
name|fd
operator|=
operator|-
literal|1
expr_stmt|;
name|open_swap_files
operator|=
name|g_list_remove
argument_list|(
name|open_swap_files
argument_list|,
name|open_swap_files
operator|->
name|data
argument_list|)
expr_stmt|;
name|nopen_swap_files
operator|-=
literal|1
expr_stmt|;
block|}
name|swap_file
operator|->
name|fd
operator|=
name|open
argument_list|(
name|swap_file
operator|->
name|filename
argument_list|,
name|O_CREAT
operator||
name|O_RDWR
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
block|{
name|g_message
argument_list|(
literal|"unable to open swap file...BAD THINGS WILL HAPPEN SOON"
argument_list|)
expr_stmt|;
return|return;
block|}
name|open_swap_files
operator|=
name|g_list_append
argument_list|(
name|open_swap_files
argument_list|,
name|swap_file
argument_list|)
expr_stmt|;
name|nopen_swap_files
operator|+=
literal|1
expr_stmt|;
block|}
end_function

begin_comment
comment|/* The actual swap file code. The swap file consists of tiles  *  which have been moved out to disk in order to conserve memory.  *  The swap file format is free form. Any tile in memory may  *  end up anywhere on disk.  * An actual tile in the swap file consists only of the tile data.  *  The offset of the tile on disk is stored in the tile data structure  *  in memory.  */
end_comment

begin_function
specifier|static
name|int
DECL|function|tile_swap_default (int fd,Tile * tile,int cmd,gpointer user_data)
name|tile_swap_default
parameter_list|(
name|int
name|fd
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|cmd
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|DefSwapFile
modifier|*
name|def_swap_file
decl_stmt|;
name|def_swap_file
operator|=
operator|(
name|DefSwapFile
operator|*
operator|)
name|user_data
expr_stmt|;
switch|switch
condition|(
name|cmd
condition|)
block|{
case|case
name|SWAP_IN
case|:
name|tile_swap_default_in
argument_list|(
name|def_swap_file
argument_list|,
name|fd
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
name|def_swap_file
argument_list|,
name|fd
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
name|def_swap_file
argument_list|,
name|fd
argument_list|,
name|tile
argument_list|)
expr_stmt|;
break|break;
case|case
name|SWAP_COMPRESS
case|:
name|g_message
argument_list|(
literal|"tile_swap_default: SWAP_COMPRESS: UNFINISHED"
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_swap_default_in (DefSwapFile * def_swap_file,int fd,Tile * tile)
name|tile_swap_default_in
parameter_list|(
name|DefSwapFile
modifier|*
name|def_swap_file
parameter_list|,
name|int
name|fd
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
name|int
name|bytes
decl_stmt|;
name|int
name|err
decl_stmt|;
name|int
name|nleft
decl_stmt|;
name|off_t
name|offset
decl_stmt|;
name|err
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|def_swap_file
operator|->
name|cur_position
operator|!=
name|tile
operator|->
name|swap_offset
condition|)
block|{
name|def_swap_file
operator|->
name|cur_position
operator|=
name|tile
operator|->
name|swap_offset
expr_stmt|;
name|offset
operator|=
name|lseek
argument_list|(
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
literal|"unable to seek to tile location on disk: %d"
argument_list|,
name|err
argument_list|)
expr_stmt|;
name|seek_err_msg
operator|=
name|FALSE
expr_stmt|;
return|return;
block|}
block|}
name|bytes
operator|=
name|tile_size
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|tile_alloc
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|nleft
operator|=
name|bytes
expr_stmt|;
while|while
condition|(
name|nleft
operator|>
literal|0
condition|)
block|{
do|do
block|{
name|err
operator|=
name|read
argument_list|(
name|fd
argument_list|,
name|tile
operator|->
name|data
operator|+
name|bytes
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
literal|"unable to read tile data from disk: %d/%d ( %d ) bytes read"
argument_list|,
name|err
argument_list|,
name|errno
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
name|def_swap_file
operator|->
name|cur_position
operator|+=
name|bytes
expr_stmt|;
comment|/*  Do not delete the swap from the file  */
comment|/*  tile_swap_default_delete (def_swap_file, fd, tile);  */
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
DECL|function|tile_swap_default_out (DefSwapFile * def_swap_file,int fd,Tile * tile)
name|tile_swap_default_out
parameter_list|(
name|DefSwapFile
modifier|*
name|def_swap_file
parameter_list|,
name|int
name|fd
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
name|int
name|bytes
decl_stmt|;
name|int
name|rbytes
decl_stmt|;
name|int
name|err
decl_stmt|;
name|int
name|nleft
decl_stmt|;
name|off_t
name|offset
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
name|rbytes
operator|=
name|tile_size
argument_list|(
name|tile
argument_list|)
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
name|tile
operator|->
name|swap_offset
operator|=
name|tile_swap_find_offset
argument_list|(
name|def_swap_file
argument_list|,
name|fd
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
if|if
condition|(
name|def_swap_file
operator|->
name|cur_position
operator|!=
name|tile
operator|->
name|swap_offset
condition|)
block|{
name|def_swap_file
operator|->
name|cur_position
operator|=
name|tile
operator|->
name|swap_offset
expr_stmt|;
name|offset
operator|=
name|lseek
argument_list|(
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
literal|"unable to seek to tile location on disk: %d"
argument_list|,
name|errno
argument_list|)
expr_stmt|;
name|seek_err_msg
operator|=
name|FALSE
expr_stmt|;
return|return;
block|}
block|}
name|nleft
operator|=
name|rbytes
expr_stmt|;
while|while
condition|(
name|nleft
operator|>
literal|0
condition|)
block|{
name|err
operator|=
name|write
argument_list|(
name|fd
argument_list|,
name|tile
operator|->
name|data
operator|+
name|rbytes
operator|-
name|nleft
argument_list|,
name|nleft
argument_list|)
expr_stmt|;
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
literal|"unable to write tile data to disk: %d ( %d ) bytes written"
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
name|def_swap_file
operator|->
name|cur_position
operator|+=
name|rbytes
expr_stmt|;
comment|/*  g_free (tile->data);   tile->data = NULL; */
name|tile
operator|->
name|dirty
operator|=
name|FALSE
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
DECL|function|tile_swap_default_delete (DefSwapFile * def_swap_file,int fd,Tile * tile)
name|tile_swap_default_delete
parameter_list|(
name|DefSwapFile
modifier|*
name|def_swap_file
parameter_list|,
name|int
name|fd
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
block|{
name|GList
modifier|*
name|tmp
decl_stmt|;
name|GList
modifier|*
name|tmp2
decl_stmt|;
name|Gap
modifier|*
name|gap
decl_stmt|;
name|Gap
modifier|*
name|gap2
decl_stmt|;
name|long
name|start
decl_stmt|;
name|long
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
name|def_swap_file
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
name|def_swap_file
operator|->
name|gaps
operator|=
name|g_list_remove_link
argument_list|(
name|def_swap_file
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
name|def_swap_file
operator|->
name|gaps
operator|=
name|g_list_remove_link
argument_list|(
name|def_swap_file
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
name|def_swap_file
operator|->
name|gaps
condition|)
name|def_swap_file
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
name|def_swap_file
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
name|def_swap_file
operator|->
name|gaps
operator|=
name|g_list_append
argument_list|(
name|def_swap_file
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
name|def_swap_file
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
name|def_swap_file
operator|->
name|swap_file_end
condition|)
block|{
name|tile_swap_resize
argument_list|(
name|def_swap_file
argument_list|,
name|fd
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
name|def_swap_file
operator|->
name|gaps
operator|=
name|g_list_remove_link
argument_list|(
name|def_swap_file
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
DECL|function|tile_swap_resize (DefSwapFile * def_swap_file,int fd,long new_size)
name|tile_swap_resize
parameter_list|(
name|DefSwapFile
modifier|*
name|def_swap_file
parameter_list|,
name|int
name|fd
parameter_list|,
name|long
name|new_size
parameter_list|)
block|{
if|if
condition|(
name|def_swap_file
operator|->
name|swap_file_end
operator|>
name|new_size
condition|)
name|ftruncate
argument_list|(
name|fd
argument_list|,
name|new_size
argument_list|)
expr_stmt|;
name|def_swap_file
operator|->
name|swap_file_end
operator|=
name|new_size
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|long
DECL|function|tile_swap_find_offset (DefSwapFile * def_swap_file,int fd,int bytes)
name|tile_swap_find_offset
parameter_list|(
name|DefSwapFile
modifier|*
name|def_swap_file
parameter_list|,
name|int
name|fd
parameter_list|,
name|int
name|bytes
parameter_list|)
block|{
name|GList
modifier|*
name|tmp
decl_stmt|;
name|Gap
modifier|*
name|gap
decl_stmt|;
name|long
name|offset
decl_stmt|;
name|tmp
operator|=
name|def_swap_file
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
name|def_swap_file
operator|->
name|gaps
operator|=
name|g_list_remove_link
argument_list|(
name|def_swap_file
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
name|def_swap_file
operator|->
name|swap_file_end
expr_stmt|;
name|tile_swap_resize
argument_list|(
name|def_swap_file
argument_list|,
name|fd
argument_list|,
name|def_swap_file
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
name|def_swap_file
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
name|def_swap_file
operator|->
name|swap_file_end
argument_list|)
expr_stmt|;
name|def_swap_file
operator|->
name|gaps
operator|=
name|g_list_append
argument_list|(
name|def_swap_file
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
name|Gap
modifier|*
DECL|function|tile_swap_gap_new (long start,long end)
name|tile_swap_gap_new
parameter_list|(
name|long
name|start
parameter_list|,
name|long
name|end
parameter_list|)
block|{
name|Gap
modifier|*
name|gap
decl_stmt|;
name|gap
operator|=
name|g_new
argument_list|(
name|Gap
argument_list|,
literal|1
argument_list|)
expr_stmt|;
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
DECL|function|tile_swap_gap_destroy (Gap * gap)
name|tile_swap_gap_destroy
parameter_list|(
name|Gap
modifier|*
name|gap
parameter_list|)
block|{
name|g_free
argument_list|(
name|gap
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

