begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* TinyScheme Extensions  * (c) 2002 Visual Tools, S.A.  * Manuel Heras-Gilsanz (manuel@heras-gilsanz.com)  *  * This software is subject to the terms stated in the  * LICENSE file.  */
end_comment

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"tinyscheme/scheme-private.h"
end_include

begin_undef
undef|#
directive|undef
name|cons
end_undef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29c4ab810103
block|{
DECL|enumerator|FILE_TYPE_UNKNOWN
DECL|enumerator|FILE_TYPE_FILE
DECL|enumerator|FILE_TYPE_DIR
DECL|enumerator|FILE_TYPE_LINK
name|FILE_TYPE_UNKNOWN
init|=
literal|0
block|,
name|FILE_TYPE_FILE
block|,
name|FILE_TYPE_DIR
block|,
name|FILE_TYPE_LINK
DECL|typedef|FileType
block|}
name|FileType
typedef|;
end_typedef

begin_struct
struct|struct
DECL|struct|named_constant
name|named_constant
block|{
DECL|member|name
specifier|const
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|value
name|FileType
name|value
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|struct
name|named_constant
DECL|variable|file_type_constants
name|file_type_constants
index|[]
init|=
block|{
block|{
literal|"FILE-TYPE-UNKNOWN"
block|,
name|FILE_TYPE_UNKNOWN
block|}
block|,
block|{
literal|"FILE-TYPE-FILE"
block|,
name|FILE_TYPE_FILE
block|}
block|,
block|{
literal|"FILE-TYPE-DIR"
block|,
name|FILE_TYPE_DIR
block|}
block|,
block|{
literal|"FILE-TYPE-LINK"
block|,
name|FILE_TYPE_LINK
block|}
block|,
block|{
name|NULL
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|foreign_fileexists (scheme * sc,pointer args)
name|pointer
name|foreign_fileexists
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|args
parameter_list|)
block|{
name|pointer
name|first_arg
decl_stmt|;
name|char
modifier|*
name|filename
decl_stmt|;
if|if
condition|(
name|args
operator|==
name|sc
operator|->
name|NIL
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|first_arg
operator|=
name|sc
operator|->
name|vptr
operator|->
name|pair_car
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sc
operator|->
name|vptr
operator|->
name|is_string
argument_list|(
name|first_arg
argument_list|)
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|filename
operator|=
name|sc
operator|->
name|vptr
operator|->
name|string_value
argument_list|(
name|first_arg
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_filename_from_utf8
argument_list|(
name|filename
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
return|return
name|sc
operator|->
name|T
return|;
return|return
name|sc
operator|->
name|F
return|;
block|}
end_function

begin_function
DECL|function|foreign_filetype (scheme * sc,pointer args)
name|pointer
name|foreign_filetype
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|args
parameter_list|)
block|{
name|pointer
name|first_arg
decl_stmt|;
name|char
modifier|*
name|filename
decl_stmt|;
name|int
name|retcode
decl_stmt|;
if|if
condition|(
name|args
operator|==
name|sc
operator|->
name|NIL
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|first_arg
operator|=
name|sc
operator|->
name|vptr
operator|->
name|pair_car
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sc
operator|->
name|vptr
operator|->
name|is_string
argument_list|(
name|first_arg
argument_list|)
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|filename
operator|=
name|sc
operator|->
name|vptr
operator|->
name|string_value
argument_list|(
name|first_arg
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_filename_from_utf8
argument_list|(
name|filename
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
condition|)
name|retcode
operator|=
name|FILE_TYPE_FILE
expr_stmt|;
elseif|else
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
name|retcode
operator|=
name|FILE_TYPE_DIR
expr_stmt|;
elseif|else
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_SYMLINK
argument_list|)
condition|)
name|retcode
operator|=
name|FILE_TYPE_LINK
expr_stmt|;
else|else
name|retcode
operator|=
name|FILE_TYPE_UNKNOWN
expr_stmt|;
return|return
name|sc
operator|->
name|vptr
operator|->
name|mk_integer
argument_list|(
name|sc
argument_list|,
name|retcode
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|foreign_filesize (scheme * sc,pointer args)
name|pointer
name|foreign_filesize
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|args
parameter_list|)
block|{
name|pointer
name|first_arg
decl_stmt|;
name|pointer
name|ret
decl_stmt|;
name|struct
name|stat
name|buf
decl_stmt|;
name|char
modifier|*
name|filename
decl_stmt|;
name|int
name|retcode
decl_stmt|;
if|if
condition|(
name|args
operator|==
name|sc
operator|->
name|NIL
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|first_arg
operator|=
name|sc
operator|->
name|vptr
operator|->
name|pair_car
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sc
operator|->
name|vptr
operator|->
name|is_string
argument_list|(
name|first_arg
argument_list|)
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|filename
operator|=
name|sc
operator|->
name|vptr
operator|->
name|string_value
argument_list|(
name|first_arg
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_filename_from_utf8
argument_list|(
name|filename
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|retcode
operator|=
name|stat
argument_list|(
name|filename
argument_list|,
operator|&
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|retcode
operator|==
literal|0
condition|)
name|ret
operator|=
name|sc
operator|->
name|vptr
operator|->
name|mk_integer
argument_list|(
name|sc
argument_list|,
name|buf
operator|.
name|st_size
argument_list|)
expr_stmt|;
else|else
name|ret
operator|=
name|sc
operator|->
name|F
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_function
DECL|function|foreign_filedelete (scheme * sc,pointer args)
name|pointer
name|foreign_filedelete
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|args
parameter_list|)
block|{
name|pointer
name|first_arg
decl_stmt|;
name|pointer
name|ret
decl_stmt|;
name|char
modifier|*
name|filename
decl_stmt|;
name|int
name|retcode
decl_stmt|;
if|if
condition|(
name|args
operator|==
name|sc
operator|->
name|NIL
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|first_arg
operator|=
name|sc
operator|->
name|vptr
operator|->
name|pair_car
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sc
operator|->
name|vptr
operator|->
name|is_string
argument_list|(
name|first_arg
argument_list|)
condition|)
block|{
return|return
name|sc
operator|->
name|F
return|;
block|}
name|filename
operator|=
name|sc
operator|->
name|vptr
operator|->
name|string_value
argument_list|(
name|first_arg
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_filename_from_utf8
argument_list|(
name|filename
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|retcode
operator|=
name|unlink
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|retcode
operator|==
literal|0
condition|)
name|ret
operator|=
name|sc
operator|->
name|T
expr_stmt|;
else|else
name|ret
operator|=
name|sc
operator|->
name|F
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_function
DECL|function|foreign_diropenstream (scheme * sc,pointer args)
name|pointer
name|foreign_diropenstream
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|args
parameter_list|)
block|{
name|pointer
name|first_arg
decl_stmt|;
name|char
modifier|*
name|dirpath
decl_stmt|;
name|GDir
modifier|*
name|dir
decl_stmt|;
if|if
condition|(
name|args
operator|==
name|sc
operator|->
name|NIL
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|first_arg
operator|=
name|sc
operator|->
name|vptr
operator|->
name|pair_car
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sc
operator|->
name|vptr
operator|->
name|is_string
argument_list|(
name|first_arg
argument_list|)
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|dirpath
operator|=
name|sc
operator|->
name|vptr
operator|->
name|string_value
argument_list|(
name|first_arg
argument_list|)
expr_stmt|;
name|dirpath
operator|=
name|g_filename_from_utf8
argument_list|(
name|dirpath
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dir
operator|=
name|g_dir_open
argument_list|(
name|dirpath
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|dir
operator|==
name|NULL
condition|)
return|return
name|sc
operator|->
name|F
return|;
comment|/* Stuffing a pointer in a long may not always be portable ~~~~~ */
return|return
operator|(
name|sc
operator|->
name|vptr
operator|->
name|mk_integer
argument_list|(
name|sc
argument_list|,
operator|(
name|long
operator|)
name|dir
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
DECL|function|foreign_dirreadentry (scheme * sc,pointer args)
name|pointer
name|foreign_dirreadentry
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|args
parameter_list|)
block|{
name|pointer
name|first_arg
decl_stmt|;
name|GDir
modifier|*
name|dir
decl_stmt|;
name|gchar
modifier|*
name|entry
decl_stmt|;
if|if
condition|(
name|args
operator|==
name|sc
operator|->
name|NIL
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|first_arg
operator|=
name|sc
operator|->
name|vptr
operator|->
name|pair_car
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sc
operator|->
name|vptr
operator|->
name|is_integer
argument_list|(
name|first_arg
argument_list|)
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|dir
operator|=
operator|(
name|GDir
operator|*
operator|)
name|sc
operator|->
name|vptr
operator|->
name|ivalue
argument_list|(
name|first_arg
argument_list|)
expr_stmt|;
if|if
condition|(
name|dir
operator|==
name|NULL
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|entry
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_dir_read_name
argument_list|(
name|dir
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
operator|==
name|NULL
condition|)
return|return
name|sc
operator|->
name|EOF_OBJ
return|;
name|entry
operator|=
name|g_filename_to_utf8
argument_list|(
name|entry
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
operator|(
name|sc
operator|->
name|vptr
operator|->
name|mk_string
argument_list|(
name|sc
argument_list|,
name|entry
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
DECL|function|foreign_dirrewind (scheme * sc,pointer args)
name|pointer
name|foreign_dirrewind
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|args
parameter_list|)
block|{
name|pointer
name|first_arg
decl_stmt|;
name|GDir
modifier|*
name|dir
decl_stmt|;
if|if
condition|(
name|args
operator|==
name|sc
operator|->
name|NIL
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|first_arg
operator|=
name|sc
operator|->
name|vptr
operator|->
name|pair_car
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sc
operator|->
name|vptr
operator|->
name|is_integer
argument_list|(
name|first_arg
argument_list|)
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|dir
operator|=
operator|(
name|GDir
operator|*
operator|)
name|sc
operator|->
name|vptr
operator|->
name|ivalue
argument_list|(
name|first_arg
argument_list|)
expr_stmt|;
if|if
condition|(
name|dir
operator|==
name|NULL
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|g_dir_rewind
argument_list|(
name|dir
argument_list|)
expr_stmt|;
return|return
name|sc
operator|->
name|T
return|;
block|}
end_function

begin_function
DECL|function|foreign_dirclosestream (scheme * sc,pointer args)
name|pointer
name|foreign_dirclosestream
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|args
parameter_list|)
block|{
name|pointer
name|first_arg
decl_stmt|;
name|GDir
modifier|*
name|dir
decl_stmt|;
if|if
condition|(
name|args
operator|==
name|sc
operator|->
name|NIL
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|first_arg
operator|=
name|sc
operator|->
name|vptr
operator|->
name|pair_car
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sc
operator|->
name|vptr
operator|->
name|is_integer
argument_list|(
name|first_arg
argument_list|)
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|dir
operator|=
operator|(
name|GDir
operator|*
operator|)
name|sc
operator|->
name|vptr
operator|->
name|ivalue
argument_list|(
name|first_arg
argument_list|)
expr_stmt|;
if|if
condition|(
name|dir
operator|==
name|NULL
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|g_dir_close
argument_list|(
name|dir
argument_list|)
expr_stmt|;
return|return
name|sc
operator|->
name|T
return|;
block|}
end_function

begin_function
DECL|function|foreign_time (scheme * sc,pointer args)
name|pointer
name|foreign_time
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|args
parameter_list|)
block|{
name|time_t
name|now
decl_stmt|;
name|struct
name|tm
modifier|*
name|now_tm
decl_stmt|;
name|pointer
name|ret
decl_stmt|;
if|if
condition|(
name|args
operator|!=
name|sc
operator|->
name|NIL
condition|)
return|return
name|sc
operator|->
name|F
return|;
if|#
directive|if
literal|1
name|time
argument_list|(
operator|&
name|now
argument_list|)
expr_stmt|;
name|now_tm
operator|=
name|localtime
argument_list|(
operator|&
name|now
argument_list|)
expr_stmt|;
else|#
directive|else
name|GTime
name|time
decl_stmt|;
name|GDate
name|date
decl_stmt|;
name|g_date_set_time
argument_list|(
operator|&
name|date
argument_list|,
operator|&
name|now
argument_list|)
expr_stmt|;
name|g_date_to_struct_tm
argument_list|(
operator|&
name|now
argument_list|,
operator|&
name|now_tm
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|ret
operator|=
name|sc
operator|->
name|vptr
operator|->
name|cons
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_integer
argument_list|(
name|sc
argument_list|,
operator|(
name|long
operator|)
name|now_tm
operator|->
name|tm_year
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|cons
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_integer
argument_list|(
name|sc
argument_list|,
operator|(
name|long
operator|)
name|now_tm
operator|->
name|tm_mon
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|cons
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_integer
argument_list|(
name|sc
argument_list|,
operator|(
name|long
operator|)
name|now_tm
operator|->
name|tm_mday
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|cons
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_integer
argument_list|(
name|sc
argument_list|,
operator|(
name|long
operator|)
name|now_tm
operator|->
name|tm_hour
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|cons
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_integer
argument_list|(
name|sc
argument_list|,
operator|(
name|long
operator|)
name|now_tm
operator|->
name|tm_min
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|cons
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_integer
argument_list|(
name|sc
argument_list|,
operator|(
name|long
operator|)
name|now_tm
operator|->
name|tm_sec
argument_list|)
argument_list|,
name|sc
operator|->
name|NIL
argument_list|)
argument_list|)
argument_list|)
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_function
DECL|function|foreign_gettimeofday (scheme * sc,pointer args)
name|pointer
name|foreign_gettimeofday
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|args
parameter_list|)
block|{
name|GTimeVal
name|tv
decl_stmt|;
name|pointer
name|ret
decl_stmt|;
name|g_get_current_time
argument_list|(
operator|&
name|tv
argument_list|)
expr_stmt|;
name|ret
operator|=
name|sc
operator|->
name|vptr
operator|->
name|cons
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_integer
argument_list|(
name|sc
argument_list|,
operator|(
name|long
operator|)
name|tv
operator|.
name|tv_sec
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|cons
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_integer
argument_list|(
name|sc
argument_list|,
operator|(
name|long
operator|)
name|tv
operator|.
name|tv_usec
argument_list|)
argument_list|,
name|sc
operator|->
name|NIL
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_function
DECL|function|foreign_usleep (scheme * sc,pointer args)
name|pointer
name|foreign_usleep
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|args
parameter_list|)
block|{
name|pointer
name|first_arg
decl_stmt|;
name|long
name|usec
decl_stmt|;
if|if
condition|(
name|args
operator|==
name|sc
operator|->
name|NIL
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|first_arg
operator|=
name|sc
operator|->
name|vptr
operator|->
name|pair_car
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sc
operator|->
name|vptr
operator|->
name|is_integer
argument_list|(
name|first_arg
argument_list|)
condition|)
return|return
name|sc
operator|->
name|F
return|;
name|usec
operator|=
name|sc
operator|->
name|vptr
operator|->
name|ivalue
argument_list|(
name|first_arg
argument_list|)
expr_stmt|;
name|g_usleep
argument_list|(
name|usec
argument_list|)
expr_stmt|;
return|return
name|sc
operator|->
name|T
return|;
block|}
end_function

begin_comment
comment|/* This function gets called when TinyScheme is loading the extension */
end_comment

begin_function
DECL|function|init_ftx (scheme * sc)
name|void
name|init_ftx
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
name|sc
operator|->
name|vptr
operator|->
name|scheme_define
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|global_env
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_symbol
argument_list|(
name|sc
argument_list|,
literal|"time"
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_foreign_func
argument_list|(
name|sc
argument_list|,
name|foreign_time
argument_list|)
argument_list|)
expr_stmt|;
name|sc
operator|->
name|vptr
operator|->
name|scheme_define
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|global_env
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_symbol
argument_list|(
name|sc
argument_list|,
literal|"gettimeofday"
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_foreign_func
argument_list|(
name|sc
argument_list|,
name|foreign_gettimeofday
argument_list|)
argument_list|)
expr_stmt|;
name|sc
operator|->
name|vptr
operator|->
name|scheme_define
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|global_env
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_symbol
argument_list|(
name|sc
argument_list|,
literal|"usleep"
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_foreign_func
argument_list|(
name|sc
argument_list|,
name|foreign_usleep
argument_list|)
argument_list|)
expr_stmt|;
name|sc
operator|->
name|vptr
operator|->
name|scheme_define
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|global_env
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_symbol
argument_list|(
name|sc
argument_list|,
literal|"file-exists?"
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_foreign_func
argument_list|(
name|sc
argument_list|,
name|foreign_fileexists
argument_list|)
argument_list|)
expr_stmt|;
name|sc
operator|->
name|vptr
operator|->
name|scheme_define
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|global_env
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_symbol
argument_list|(
name|sc
argument_list|,
literal|"file-type"
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_foreign_func
argument_list|(
name|sc
argument_list|,
name|foreign_filetype
argument_list|)
argument_list|)
expr_stmt|;
name|sc
operator|->
name|vptr
operator|->
name|scheme_define
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|global_env
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_symbol
argument_list|(
name|sc
argument_list|,
literal|"file-size"
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_foreign_func
argument_list|(
name|sc
argument_list|,
name|foreign_filesize
argument_list|)
argument_list|)
expr_stmt|;
name|sc
operator|->
name|vptr
operator|->
name|scheme_define
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|global_env
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_symbol
argument_list|(
name|sc
argument_list|,
literal|"file-delete"
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_foreign_func
argument_list|(
name|sc
argument_list|,
name|foreign_filedelete
argument_list|)
argument_list|)
expr_stmt|;
name|sc
operator|->
name|vptr
operator|->
name|scheme_define
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|global_env
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_symbol
argument_list|(
name|sc
argument_list|,
literal|"dir-open-stream"
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_foreign_func
argument_list|(
name|sc
argument_list|,
name|foreign_diropenstream
argument_list|)
argument_list|)
expr_stmt|;
name|sc
operator|->
name|vptr
operator|->
name|scheme_define
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|global_env
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_symbol
argument_list|(
name|sc
argument_list|,
literal|"dir-read-entry"
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_foreign_func
argument_list|(
name|sc
argument_list|,
name|foreign_dirreadentry
argument_list|)
argument_list|)
expr_stmt|;
name|sc
operator|->
name|vptr
operator|->
name|scheme_define
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|global_env
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_symbol
argument_list|(
name|sc
argument_list|,
literal|"dir-rewind"
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_foreign_func
argument_list|(
name|sc
argument_list|,
name|foreign_dirrewind
argument_list|)
argument_list|)
expr_stmt|;
name|sc
operator|->
name|vptr
operator|->
name|scheme_define
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|global_env
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_symbol
argument_list|(
name|sc
argument_list|,
literal|"dir-close-stream"
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_foreign_func
argument_list|(
name|sc
argument_list|,
name|foreign_dirclosestream
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|file_type_constants
index|[
name|i
index|]
operator|.
name|name
operator|!=
name|NULL
condition|;
operator|++
name|i
control|)
block|{
name|sc
operator|->
name|vptr
operator|->
name|scheme_define
argument_list|(
name|sc
argument_list|,
name|sc
operator|->
name|global_env
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_symbol
argument_list|(
name|sc
argument_list|,
name|file_type_constants
index|[
name|i
index|]
operator|.
name|name
argument_list|)
argument_list|,
name|sc
operator|->
name|vptr
operator|->
name|mk_integer
argument_list|(
name|sc
argument_list|,
name|file_type_constants
index|[
name|i
index|]
operator|.
name|value
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

