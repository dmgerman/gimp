begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<stdarg.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<ctype.h>
end_include

begin_include
include|#
directive|include
file|"output.h"
end_include

begin_decl_stmt
DECL|variable|ptrue
specifier|const
name|PBool
name|ptrue
init|=
operator|&
name|ptrue
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pfalse
specifier|const
name|PBool
name|pfalse
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|type_hdr
name|File
modifier|*
name|type_hdr
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|func_hdr
name|File
modifier|*
name|func_hdr
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|prot_hdr
name|File
modifier|*
name|prot_hdr
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pub_import_hdr
name|File
modifier|*
name|pub_import_hdr
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|prot_import_hdr
name|File
modifier|*
name|prot_import_hdr
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|source
name|File
modifier|*
name|source
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|source_head
name|File
modifier|*
name|source_head
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|source_head
comment|/* inlined to the source */
end_comment

begin_struct
DECL|struct|_File
struct|struct
name|_File
block|{
DECL|member|stream
name|FILE
modifier|*
name|stream
decl_stmt|;
DECL|member|filename
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|parent
name|File
modifier|*
name|parent
decl_stmt|;
DECL|member|deps
name|GHashTable
modifier|*
name|deps
decl_stmt|;
block|}
struct|;
end_struct

begin_function
DECL|function|write_guard_name (FILE * s,const gchar * c)
name|void
name|write_guard_name
parameter_list|(
name|FILE
modifier|*
name|s
parameter_list|,
specifier|const
name|gchar
modifier|*
name|c
parameter_list|)
block|{
name|gboolean
name|enc
init|=
name|FALSE
decl_stmt|;
name|fputs
argument_list|(
literal|"_g_"
argument_list|,
name|s
argument_list|)
expr_stmt|;
while|while
condition|(
operator|*
name|c
condition|)
block|{
if|if
condition|(
name|isalnum
argument_list|(
operator|*
name|c
argument_list|)
condition|)
name|fputc
argument_list|(
operator|*
name|c
argument_list|,
name|s
argument_list|)
expr_stmt|;
else|else
name|fputc
argument_list|(
literal|'_'
argument_list|,
name|s
argument_list|)
expr_stmt|;
name|c
operator|++
expr_stmt|;
block|}
name|fputc
argument_list|(
literal|'_'
argument_list|,
name|s
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|write_guard_start (FILE * s,const gchar * c)
name|void
name|write_guard_start
parameter_list|(
name|FILE
modifier|*
name|s
parameter_list|,
specifier|const
name|gchar
modifier|*
name|c
parameter_list|)
block|{
name|fputs
argument_list|(
literal|"#ifndef "
argument_list|,
name|s
argument_list|)
expr_stmt|;
name|write_guard_name
argument_list|(
name|s
argument_list|,
name|c
argument_list|)
expr_stmt|;
name|fputs
argument_list|(
literal|"\n#define "
argument_list|,
name|s
argument_list|)
expr_stmt|;
name|write_guard_name
argument_list|(
name|s
argument_list|,
name|c
argument_list|)
expr_stmt|;
name|fputs
argument_list|(
literal|"\n"
argument_list|,
name|s
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|write_guard_end (FILE * s,const gchar * c)
name|void
name|write_guard_end
parameter_list|(
name|FILE
modifier|*
name|s
parameter_list|,
specifier|const
name|gchar
modifier|*
name|c
parameter_list|)
block|{
name|fputs
argument_list|(
literal|"#endif /* "
argument_list|,
name|s
argument_list|)
expr_stmt|;
name|write_guard_name
argument_list|(
name|s
argument_list|,
name|c
argument_list|)
expr_stmt|;
name|fputs
argument_list|(
literal|" */\n"
argument_list|,
name|s
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|file_new (const gchar * filename)
name|File
modifier|*
name|file_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|File
modifier|*
name|f
init|=
name|g_new
argument_list|(
name|File
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|f
operator|->
name|stream
operator|=
name|tmpfile
argument_list|()
expr_stmt|;
name|f
operator|->
name|filename
operator|=
name|filename
expr_stmt|;
name|f
operator|->
name|deps
operator|=
name|g_hash_table_new
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|)
expr_stmt|;
name|f
operator|->
name|parent
operator|=
name|NULL
expr_stmt|;
return|return
name|f
return|;
block|}
end_function

begin_function
DECL|function|file_sub (File * parent)
name|File
modifier|*
name|file_sub
parameter_list|(
name|File
modifier|*
name|parent
parameter_list|)
block|{
name|File
modifier|*
name|f
init|=
name|g_new
argument_list|(
name|File
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|f
operator|->
name|stream
operator|=
name|tmpfile
argument_list|()
expr_stmt|;
name|f
operator|->
name|filename
operator|=
name|NULL
expr_stmt|;
name|f
operator|->
name|deps
operator|=
name|NULL
expr_stmt|;
name|f
operator|->
name|parent
operator|=
name|parent
expr_stmt|;
return|return
name|f
return|;
block|}
end_function

begin_function
DECL|function|file_add_dep (File * f,Id header)
name|void
name|file_add_dep
parameter_list|(
name|File
modifier|*
name|f
parameter_list|,
name|Id
name|header
parameter_list|)
block|{
while|while
condition|(
name|f
operator|->
name|parent
condition|)
name|f
operator|=
name|f
operator|->
name|parent
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|f
operator|->
name|deps
argument_list|,
name|header
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|write_dep (gpointer key,gpointer value,gpointer user_data)
name|void
name|write_dep
parameter_list|(
name|gpointer
name|key
parameter_list|,
name|gpointer
name|value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|Id
name|i
init|=
name|key
decl_stmt|;
name|FILE
modifier|*
name|stream
init|=
name|user_data
decl_stmt|;
name|fprintf
argument_list|(
name|stream
argument_list|,
literal|"#include %s\n"
argument_list|,
name|i
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|file_flush (File * f)
name|void
name|file_flush
parameter_list|(
name|File
modifier|*
name|f
parameter_list|)
block|{
name|File
modifier|*
name|root
decl_stmt|;
name|File
modifier|*
name|old
decl_stmt|;
specifier|static
specifier|const
name|gint
name|bufsize
init|=
literal|1024
decl_stmt|;
name|FILE
modifier|*
name|real
decl_stmt|;
name|guint8
name|buf
index|[
name|bufsize
index|]
decl_stmt|;
name|size_t
name|i
decl_stmt|;
for|for
control|(
name|root
operator|=
name|f
init|;
name|root
operator|->
name|parent
condition|;
name|root
operator|=
name|root
operator|->
name|parent
control|)
empty_stmt|;
name|real
operator|=
name|fopen
argument_list|(
name|root
operator|->
name|filename
argument_list|,
literal|"w+"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|real
argument_list|)
expr_stmt|;
name|write_guard_start
argument_list|(
name|real
argument_list|,
name|root
operator|->
name|filename
argument_list|)
expr_stmt|;
comment|/* more scoping needed */
name|g_hash_table_foreach
argument_list|(
name|root
operator|->
name|deps
argument_list|,
name|write_dep
argument_list|,
name|real
argument_list|)
expr_stmt|;
name|fflush
argument_list|(
name|root
operator|->
name|stream
argument_list|)
expr_stmt|;
name|old
operator|=
name|NULL
expr_stmt|;
while|while
condition|(
name|f
condition|)
block|{
name|g_free
argument_list|(
name|old
argument_list|)
expr_stmt|;
name|rewind
argument_list|(
name|f
operator|->
name|stream
argument_list|)
expr_stmt|;
name|i
operator|=
literal|0
expr_stmt|;
do|do
block|{
name|i
operator|=
name|fread
argument_list|(
name|buf
argument_list|,
literal|1
argument_list|,
name|bufsize
argument_list|,
name|f
operator|->
name|stream
argument_list|)
expr_stmt|;
name|fwrite
argument_list|(
name|buf
argument_list|,
literal|1
argument_list|,
name|i
argument_list|,
name|real
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|i
operator|==
name|bufsize
condition|)
do|;
name|fclose
argument_list|(
name|f
operator|->
name|stream
argument_list|)
expr_stmt|;
name|old
operator|=
name|f
expr_stmt|;
name|f
operator|=
name|f
operator|->
name|parent
expr_stmt|;
block|}
name|write_guard_end
argument_list|(
name|real
argument_list|,
name|root
operator|->
name|filename
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|real
argument_list|)
expr_stmt|;
name|g_hash_table_destroy
argument_list|(
name|root
operator|->
name|deps
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|root
argument_list|)
expr_stmt|;
block|}
end_function

begin_typedef
DECL|typedef|Func
typedef|typedef
name|void
function_decl|(
modifier|*
name|Func
function_decl|)
parameter_list|()
function_decl|;
end_typedef

begin_decl_stmt
DECL|variable|nilf
specifier|const
name|Func
name|nilf
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|call_func (Func fun,File * s,gpointer * x,gint nargs)
specifier|static
name|void
name|call_func
parameter_list|(
name|Func
name|fun
parameter_list|,
name|File
modifier|*
name|s
parameter_list|,
name|gpointer
modifier|*
name|x
parameter_list|,
name|gint
name|nargs
parameter_list|)
block|{
switch|switch
condition|(
name|nargs
condition|)
block|{
case|case
literal|0
case|:
name|fun
argument_list|(
name|s
argument_list|)
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|fun
argument_list|(
name|s
argument_list|,
name|x
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|fun
argument_list|(
name|s
argument_list|,
name|x
index|[
literal|0
index|]
argument_list|,
name|x
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|fun
argument_list|(
name|s
argument_list|,
name|x
index|[
literal|0
index|]
argument_list|,
name|x
index|[
literal|1
index|]
argument_list|,
name|x
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|fun
argument_list|(
name|s
argument_list|,
name|x
index|[
literal|0
index|]
argument_list|,
name|x
index|[
literal|1
index|]
argument_list|,
name|x
index|[
literal|2
index|]
argument_list|,
name|x
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
literal|5
case|:
name|fun
argument_list|(
name|s
argument_list|,
name|x
index|[
literal|0
index|]
argument_list|,
name|x
index|[
literal|1
index|]
argument_list|,
name|x
index|[
literal|2
index|]
argument_list|,
name|x
index|[
literal|3
index|]
argument_list|,
name|x
index|[
literal|4
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
literal|6
case|:
name|fun
argument_list|(
name|s
argument_list|,
name|x
index|[
literal|0
index|]
argument_list|,
name|x
index|[
literal|1
index|]
argument_list|,
name|x
index|[
literal|2
index|]
argument_list|,
name|x
index|[
literal|3
index|]
argument_list|,
name|x
index|[
literal|4
index|]
argument_list|,
name|x
index|[
literal|5
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
literal|7
case|:
name|fun
argument_list|(
name|s
argument_list|,
name|x
index|[
literal|0
index|]
argument_list|,
name|x
index|[
literal|1
index|]
argument_list|,
name|x
index|[
literal|2
index|]
argument_list|,
name|x
index|[
literal|3
index|]
argument_list|,
name|x
index|[
literal|4
index|]
argument_list|,
name|x
index|[
literal|5
index|]
argument_list|,
name|x
index|[
literal|6
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
literal|8
case|:
name|fun
argument_list|(
name|s
argument_list|,
name|x
index|[
literal|0
index|]
argument_list|,
name|x
index|[
literal|1
index|]
argument_list|,
name|x
index|[
literal|2
index|]
argument_list|,
name|x
index|[
literal|3
index|]
argument_list|,
name|x
index|[
literal|4
index|]
argument_list|,
name|x
index|[
literal|5
index|]
argument_list|,
name|x
index|[
literal|6
index|]
argument_list|,
name|x
index|[
literal|7
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
literal|9
case|:
name|fun
argument_list|(
name|s
argument_list|,
name|x
index|[
literal|0
index|]
argument_list|,
name|x
index|[
literal|1
index|]
argument_list|,
name|x
index|[
literal|2
index|]
argument_list|,
name|x
index|[
literal|3
index|]
argument_list|,
name|x
index|[
literal|4
index|]
argument_list|,
name|x
index|[
literal|5
index|]
argument_list|,
name|x
index|[
literal|6
index|]
argument_list|,
name|x
index|[
literal|7
index|]
argument_list|,
name|x
index|[
literal|8
index|]
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
DECL|function|prv (File * s,const gchar * f,va_list args)
name|void
name|prv
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
specifier|const
name|gchar
modifier|*
name|f
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
name|gint
name|i
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|s
condition|)
return|return;
while|while
condition|(
operator|*
name|f
condition|)
block|{
while|while
condition|(
name|f
index|[
name|i
index|]
operator|&&
name|f
index|[
name|i
index|]
operator|!=
literal|'%'
condition|)
name|i
operator|++
expr_stmt|;
name|fwrite
argument_list|(
name|f
argument_list|,
name|i
argument_list|,
literal|1
argument_list|,
name|s
operator|->
name|stream
argument_list|)
expr_stmt|;
name|f
operator|+=
name|i
expr_stmt|;
name|i
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|f
index|[
literal|0
index|]
operator|==
literal|'%'
condition|)
block|{
name|char
name|c
init|=
name|f
index|[
literal|1
index|]
decl_stmt|;
name|gboolean
name|doit
init|=
name|TRUE
decl_stmt|;
name|f
operator|+=
literal|2
expr_stmt|;
if|if
condition|(
name|c
operator|==
literal|'%'
condition|)
name|fputc
argument_list|(
literal|'%'
argument_list|,
name|s
operator|->
name|stream
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|c
operator|==
literal|'?'
condition|)
block|{
name|doit
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gboolean
argument_list|)
expr_stmt|;
name|c
operator|=
operator|*
name|f
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|c
operator|==
literal|'s'
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|str
init|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
decl_stmt|;
if|if
condition|(
name|doit
condition|)
name|fputs
argument_list|(
name|str
argument_list|,
name|s
operator|->
name|stream
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|c
operator|==
literal|'d'
condition|)
block|{
name|gint
name|n
decl_stmt|;
name|n
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gint
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|s
operator|->
name|stream
argument_list|,
literal|"%d"
argument_list|,
name|n
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|c
operator|==
literal|'v'
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|nextformat
decl_stmt|;
name|va_list
name|nextargs
decl_stmt|;
name|nextformat
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
expr_stmt|;
name|nextargs
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|va_list
argument_list|)
expr_stmt|;
if|if
condition|(
name|doit
condition|)
name|prv
argument_list|(
name|s
argument_list|,
name|nextformat
argument_list|,
name|nextargs
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|c
operator|>=
literal|'0'
operator|&&
name|c
operator|<=
literal|'9'
condition|)
block|{
name|Func
name|fun
decl_stmt|;
name|gint
name|n
decl_stmt|;
name|gpointer
name|x
index|[
literal|8
index|]
decl_stmt|;
name|fun
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|Func
argument_list|)
expr_stmt|;
for|for
control|(
name|n
operator|=
literal|0
init|;
name|n
operator|<
name|c
operator|-
literal|'0'
condition|;
name|n
operator|++
control|)
name|x
index|[
name|n
index|]
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gpointer
argument_list|)
expr_stmt|;
if|if
condition|(
name|doit
condition|)
name|call_func
argument_list|(
name|fun
argument_list|,
name|s
argument_list|,
name|x
argument_list|,
name|c
operator|-
literal|'0'
argument_list|)
expr_stmt|;
block|}
else|else
name|g_error
argument_list|(
literal|"Bad format\n"
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
DECL|function|pr (File * s,const gchar * format,...)
name|void
name|pr
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|prv
argument_list|(
name|s
argument_list|,
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|pr_f (File * s,const gchar * format,...)
name|void
name|pr_f
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|vfprintf
argument_list|(
name|s
operator|->
name|stream
argument_list|,
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|pr_nil (File * s,...)
name|void
name|pr_nil
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
modifier|...
parameter_list|)
block|{ }
end_function

begin_function
DECL|function|pr_c (File * s,gchar c)
name|void
name|pr_c
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
name|gchar
name|c
parameter_list|)
block|{
if|if
condition|(
name|s
condition|)
name|fputc
argument_list|(
name|c
argument_list|,
name|s
operator|->
name|stream
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|pr_low (File * s,const gchar * str)
name|void
name|pr_low
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
specifier|const
name|gchar
modifier|*
name|str
parameter_list|)
block|{
name|gchar
name|x
decl_stmt|;
while|while
condition|(
operator|*
name|str
condition|)
block|{
name|x
operator|=
operator|*
name|str
operator|++
expr_stmt|;
name|pr_c
argument_list|(
name|s
argument_list|,
operator|(
name|x
operator|==
literal|'-'
operator|)
condition|?
literal|'_'
else|:
name|tolower
argument_list|(
name|x
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|pr_up (File * s,const gchar * str)
name|void
name|pr_up
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
specifier|const
name|gchar
modifier|*
name|str
parameter_list|)
block|{
name|gchar
name|x
decl_stmt|;
while|while
condition|(
operator|*
name|str
condition|)
block|{
name|x
operator|=
operator|*
name|str
operator|++
expr_stmt|;
name|pr_c
argument_list|(
name|s
argument_list|,
operator|(
name|x
operator|==
literal|'-'
operator|)
condition|?
literal|'_'
else|:
name|toupper
argument_list|(
name|x
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_decl_stmt
DECL|variable|no_data
specifier|const
name|gconstpointer
name|no_data
init|=
operator|&
name|no_data
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* This depends on a func pointer being about the same as a gpointer */
end_comment

begin_function
DECL|function|pr_list_foreach (File * s,GSList * l,void (* f)(),gpointer arg)
name|void
name|pr_list_foreach
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
name|GSList
modifier|*
name|l
parameter_list|,
name|void
function_decl|(
modifier|*
name|f
function_decl|)
parameter_list|()
parameter_list|,
name|gpointer
name|arg
parameter_list|)
block|{
while|while
condition|(
name|l
condition|)
block|{
if|if
condition|(
name|arg
operator|==
name|no_data
condition|)
name|f
argument_list|(
name|s
argument_list|,
name|l
operator|->
name|data
argument_list|)
expr_stmt|;
else|else
name|f
argument_list|(
name|s
argument_list|,
name|l
operator|->
name|data
argument_list|,
name|arg
argument_list|)
expr_stmt|;
name|l
operator|=
name|l
operator|->
name|next
expr_stmt|;
block|}
block|}
end_function

end_unit

