begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * file-procedure.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_SYS_PARAM_H
end_ifdef

begin_include
include|#
directive|include
file|<sys/param.h>
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
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginprocedure.h"
end_include

begin_include
include|#
directive|include
file|"file-procedure.h"
end_include

begin_include
include|#
directive|include
file|"file-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae0c1f50103
block|{
DECL|enumerator|FILE_MATCH_NONE
name|FILE_MATCH_NONE
block|,
DECL|enumerator|FILE_MATCH_MAGIC
name|FILE_MATCH_MAGIC
block|,
DECL|enumerator|FILE_MATCH_SIZE
name|FILE_MATCH_SIZE
DECL|typedef|FileMatchType
block|}
name|FileMatchType
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GimpPlugInProcedure
modifier|*
name|file_proc_find_by_prefix
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
name|skip_magic
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpPlugInProcedure
modifier|*
name|file_proc_find_by_extension
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
name|skip_magic
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpPlugInProcedure
modifier|*
name|file_proc_find_by_name
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
name|skip_magic
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_convert_string
parameter_list|(
specifier|const
name|gchar
modifier|*
name|instr
parameter_list|,
name|gchar
modifier|*
name|outmem
parameter_list|,
name|gint
name|maxmem
parameter_list|,
name|gint
modifier|*
name|nmem
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|FileMatchType
name|file_check_single_magic
parameter_list|(
specifier|const
name|gchar
modifier|*
name|offset
parameter_list|,
specifier|const
name|gchar
modifier|*
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
specifier|const
name|guchar
modifier|*
name|file_head
parameter_list|,
name|gint
name|headsize
parameter_list|,
name|FILE
modifier|*
name|ifp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|FileMatchType
name|file_check_magic_list
parameter_list|(
name|GSList
modifier|*
name|magics_list
parameter_list|,
specifier|const
name|guchar
modifier|*
name|head
parameter_list|,
name|gint
name|headsize
parameter_list|,
name|FILE
modifier|*
name|ifp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpPlugInProcedure
modifier|*
DECL|function|file_procedure_find (GSList * procs,const gchar * uri,GError ** error)
name|file_procedure_find
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|file_proc
decl_stmt|;
name|GSList
modifier|*
name|all_procs
init|=
name|procs
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|procs
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* First, check magicless prefixes/suffixes */
name|file_proc
operator|=
name|file_proc_find_by_name
argument_list|(
name|all_procs
argument_list|,
name|uri
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_proc
condition|)
return|return
name|file_proc
return|;
name|filename
operator|=
name|file_utils_filename_from_uri
argument_list|(
name|uri
argument_list|)
expr_stmt|;
comment|/* Then look for magics */
if|if
condition|(
name|filename
condition|)
block|{
name|GimpPlugInProcedure
modifier|*
name|size_matched_proc
init|=
name|NULL
decl_stmt|;
name|FILE
modifier|*
name|ifp
init|=
name|NULL
decl_stmt|;
name|gint
name|head_size
init|=
operator|-
literal|2
decl_stmt|;
name|gint
name|size_match_count
init|=
literal|0
decl_stmt|;
name|guchar
name|head
index|[
literal|256
index|]
decl_stmt|;
while|while
condition|(
name|procs
condition|)
block|{
name|file_proc
operator|=
name|procs
operator|->
name|data
expr_stmt|;
name|procs
operator|=
name|procs
operator|->
name|next
expr_stmt|;
if|if
condition|(
name|file_proc
operator|->
name|magics_list
condition|)
block|{
if|if
condition|(
name|head_size
operator|==
operator|-
literal|2
condition|)
block|{
name|head_size
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|(
name|ifp
operator|=
name|g_fopen
argument_list|(
name|filename
argument_list|,
literal|"rb"
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
name|head_size
operator|=
name|fread
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|head
argument_list|,
literal|1
argument_list|,
sizeof|sizeof
argument_list|(
name|head
argument_list|)
argument_list|,
name|ifp
argument_list|)
expr_stmt|;
block|}
else|else
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
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|head_size
operator|>=
literal|4
condition|)
block|{
name|FileMatchType
name|match_val
decl_stmt|;
name|match_val
operator|=
name|file_check_magic_list
argument_list|(
name|file_proc
operator|->
name|magics_list
argument_list|,
name|head
argument_list|,
name|head_size
argument_list|,
name|ifp
argument_list|)
expr_stmt|;
if|if
condition|(
name|match_val
operator|==
name|FILE_MATCH_SIZE
condition|)
block|{
comment|/* Use it only if no other magic matches */
name|size_match_count
operator|++
expr_stmt|;
name|size_matched_proc
operator|=
name|file_proc
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|match_val
operator|!=
name|FILE_MATCH_NONE
condition|)
block|{
name|fclose
argument_list|(
name|ifp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|file_proc
return|;
block|}
block|}
block|}
block|}
if|if
condition|(
name|ifp
condition|)
block|{
if|if
condition|(
name|ferror
argument_list|(
name|ifp
argument_list|)
condition|)
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
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|ifp
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|size_match_count
operator|==
literal|1
condition|)
return|return
name|size_matched_proc
return|;
block|}
comment|/* As a last resort, try matching by name */
name|file_proc
operator|=
name|file_proc_find_by_name
argument_list|(
name|all_procs
argument_list|,
name|uri
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_proc
condition|)
block|{
comment|/* we found a procedure, clear error that might have been set */
name|g_clear_error
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* set an error message unless one was already set */
if|if
condition|(
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
condition|)
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"Unknown file type"
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|file_proc
return|;
block|}
end_function

begin_function
name|GimpPlugInProcedure
modifier|*
DECL|function|file_procedure_find_by_prefix (GSList * procs,const gchar * uri)
name|file_procedure_find_by_prefix
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|file_proc_find_by_prefix
argument_list|(
name|procs
argument_list|,
name|uri
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpPlugInProcedure
modifier|*
DECL|function|file_procedure_find_by_extension (GSList * procs,const gchar * uri)
name|file_procedure_find_by_extension
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|file_proc_find_by_extension
argument_list|(
name|procs
argument_list|,
name|uri
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpPlugInProcedure
modifier|*
DECL|function|file_proc_find_by_prefix (GSList * procs,const gchar * uri,gboolean skip_magic)
name|file_proc_find_by_prefix
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
name|skip_magic
parameter_list|)
block|{
name|GSList
modifier|*
name|p
decl_stmt|;
for|for
control|(
name|p
operator|=
name|procs
init|;
name|p
condition|;
name|p
operator|=
name|g_slist_next
argument_list|(
name|p
argument_list|)
control|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
init|=
name|p
operator|->
name|data
decl_stmt|;
name|GSList
modifier|*
name|prefixes
decl_stmt|;
if|if
condition|(
name|skip_magic
operator|&&
name|proc
operator|->
name|magics_list
condition|)
continue|continue;
for|for
control|(
name|prefixes
operator|=
name|proc
operator|->
name|prefixes_list
init|;
name|prefixes
condition|;
name|prefixes
operator|=
name|g_slist_next
argument_list|(
name|prefixes
argument_list|)
control|)
block|{
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|uri
argument_list|,
name|prefixes
operator|->
name|data
argument_list|)
condition|)
return|return
name|proc
return|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|GimpPlugInProcedure
modifier|*
DECL|function|file_proc_find_by_extension (GSList * procs,const gchar * uri,gboolean skip_magic)
name|file_proc_find_by_extension
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
name|skip_magic
parameter_list|)
block|{
name|GSList
modifier|*
name|p
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|ext
decl_stmt|;
name|ext
operator|=
name|strrchr
argument_list|(
name|uri
argument_list|,
literal|'.'
argument_list|)
expr_stmt|;
if|if
condition|(
name|ext
condition|)
name|ext
operator|++
expr_stmt|;
for|for
control|(
name|p
operator|=
name|procs
init|;
name|p
condition|;
name|p
operator|=
name|g_slist_next
argument_list|(
name|p
argument_list|)
control|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
init|=
name|p
operator|->
name|data
decl_stmt|;
name|GSList
modifier|*
name|extensions
decl_stmt|;
for|for
control|(
name|extensions
operator|=
name|proc
operator|->
name|extensions_list
init|;
name|ext
operator|&&
name|extensions
condition|;
name|extensions
operator|=
name|g_slist_next
argument_list|(
name|extensions
argument_list|)
control|)
block|{
specifier|const
name|gchar
modifier|*
name|p1
init|=
name|ext
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|p2
init|=
name|extensions
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|skip_magic
operator|&&
name|proc
operator|->
name|magics_list
condition|)
continue|continue;
while|while
condition|(
operator|*
name|p1
operator|&&
operator|*
name|p2
condition|)
block|{
if|if
condition|(
name|g_ascii_tolower
argument_list|(
operator|*
name|p1
argument_list|)
operator|!=
name|g_ascii_tolower
argument_list|(
operator|*
name|p2
argument_list|)
condition|)
break|break;
name|p1
operator|++
expr_stmt|;
name|p2
operator|++
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
operator|*
name|p1
operator|)
operator|&&
operator|!
operator|(
operator|*
name|p2
operator|)
condition|)
return|return
name|proc
return|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|GimpPlugInProcedure
modifier|*
DECL|function|file_proc_find_by_name (GSList * procs,const gchar * uri,gboolean skip_magic)
name|file_proc_find_by_name
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
name|skip_magic
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|proc
operator|=
name|file_proc_find_by_prefix
argument_list|(
name|procs
argument_list|,
name|uri
argument_list|,
name|skip_magic
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
name|proc
operator|=
name|file_proc_find_by_extension
argument_list|(
name|procs
argument_list|,
name|uri
argument_list|,
name|skip_magic
argument_list|)
expr_stmt|;
return|return
name|proc
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_convert_string (const gchar * instr,gchar * outmem,gint maxmem,gint * nmem)
name|file_convert_string
parameter_list|(
specifier|const
name|gchar
modifier|*
name|instr
parameter_list|,
name|gchar
modifier|*
name|outmem
parameter_list|,
name|gint
name|maxmem
parameter_list|,
name|gint
modifier|*
name|nmem
parameter_list|)
block|{
comment|/* Convert a string in C-notation to array of char */
specifier|const
name|guchar
modifier|*
name|uin
init|=
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|instr
decl_stmt|;
name|guchar
modifier|*
name|uout
init|=
operator|(
name|guchar
operator|*
operator|)
name|outmem
decl_stmt|;
name|guchar
name|tmp
index|[
literal|5
index|]
decl_stmt|,
modifier|*
name|tmpptr
decl_stmt|;
name|guint
name|k
decl_stmt|;
while|while
condition|(
operator|(
operator|*
name|uin
operator|!=
literal|'\0'
operator|)
operator|&&
operator|(
operator|(
operator|(
operator|(
name|gchar
operator|*
operator|)
name|uout
operator|)
operator|-
name|outmem
operator|)
operator|<
name|maxmem
operator|)
condition|)
block|{
if|if
condition|(
operator|*
name|uin
operator|!=
literal|'\\'
condition|)
comment|/* Not an escaped character ? */
block|{
operator|*
operator|(
name|uout
operator|++
operator|)
operator|=
operator|*
operator|(
name|uin
operator|++
operator|)
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
operator|*
operator|(
operator|++
name|uin
operator|)
operator|==
literal|'\0'
condition|)
block|{
operator|*
operator|(
name|uout
operator|++
operator|)
operator|=
literal|'\\'
expr_stmt|;
break|break;
block|}
switch|switch
condition|(
operator|*
name|uin
condition|)
block|{
case|case
literal|'0'
case|:
case|case
literal|'1'
case|:
case|case
literal|'2'
case|:
case|case
literal|'3'
case|:
comment|/* octal */
for|for
control|(
name|tmpptr
operator|=
name|tmp
init|;
operator|(
name|tmpptr
operator|-
name|tmp
operator|)
operator|<=
literal|3
condition|;
control|)
block|{
operator|*
operator|(
name|tmpptr
operator|++
operator|)
operator|=
operator|*
operator|(
name|uin
operator|++
operator|)
expr_stmt|;
if|if
condition|(
operator|(
operator|*
name|uin
operator|==
literal|'\0'
operator|)
operator|||
operator|(
operator|!
name|g_ascii_isdigit
argument_list|(
operator|*
name|uin
argument_list|)
operator|)
operator|||
operator|(
operator|*
name|uin
operator|==
literal|'8'
operator|)
operator|||
operator|(
operator|*
name|uin
operator|==
literal|'9'
operator|)
condition|)
break|break;
block|}
operator|*
name|tmpptr
operator|=
literal|'\0'
expr_stmt|;
name|sscanf
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|tmp
argument_list|,
literal|"%o"
argument_list|,
operator|&
name|k
argument_list|)
expr_stmt|;
operator|*
operator|(
name|uout
operator|++
operator|)
operator|=
name|k
expr_stmt|;
break|break;
case|case
literal|'a'
case|:
operator|*
operator|(
name|uout
operator|++
operator|)
operator|=
literal|'\a'
expr_stmt|;
name|uin
operator|++
expr_stmt|;
break|break;
case|case
literal|'b'
case|:
operator|*
operator|(
name|uout
operator|++
operator|)
operator|=
literal|'\b'
expr_stmt|;
name|uin
operator|++
expr_stmt|;
break|break;
case|case
literal|'t'
case|:
operator|*
operator|(
name|uout
operator|++
operator|)
operator|=
literal|'\t'
expr_stmt|;
name|uin
operator|++
expr_stmt|;
break|break;
case|case
literal|'n'
case|:
operator|*
operator|(
name|uout
operator|++
operator|)
operator|=
literal|'\n'
expr_stmt|;
name|uin
operator|++
expr_stmt|;
break|break;
case|case
literal|'v'
case|:
operator|*
operator|(
name|uout
operator|++
operator|)
operator|=
literal|'\v'
expr_stmt|;
name|uin
operator|++
expr_stmt|;
break|break;
case|case
literal|'f'
case|:
operator|*
operator|(
name|uout
operator|++
operator|)
operator|=
literal|'\f'
expr_stmt|;
name|uin
operator|++
expr_stmt|;
break|break;
case|case
literal|'r'
case|:
operator|*
operator|(
name|uout
operator|++
operator|)
operator|=
literal|'\r'
expr_stmt|;
name|uin
operator|++
expr_stmt|;
break|break;
default|default :
operator|*
operator|(
name|uout
operator|++
operator|)
operator|=
operator|*
operator|(
name|uin
operator|++
operator|)
expr_stmt|;
break|break;
block|}
block|}
operator|*
name|nmem
operator|=
operator|(
operator|(
name|gchar
operator|*
operator|)
name|uout
operator|)
operator|-
name|outmem
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|FileMatchType
DECL|function|file_check_single_magic (const gchar * offset,const gchar * type,const gchar * value,const guchar * file_head,gint headsize,FILE * ifp)
name|file_check_single_magic
parameter_list|(
specifier|const
name|gchar
modifier|*
name|offset
parameter_list|,
specifier|const
name|gchar
modifier|*
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
specifier|const
name|guchar
modifier|*
name|file_head
parameter_list|,
name|gint
name|headsize
parameter_list|,
name|FILE
modifier|*
name|ifp
parameter_list|)
block|{
name|FileMatchType
name|found
init|=
name|FILE_MATCH_NONE
decl_stmt|;
name|glong
name|offs
decl_stmt|;
name|gulong
name|num_testval
decl_stmt|;
name|gulong
name|num_operatorval
decl_stmt|;
name|gint
name|numbytes
decl_stmt|,
name|k
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|num_operator_ptr
decl_stmt|;
name|gchar
name|num_operator
decl_stmt|;
comment|/* Check offset */
if|if
condition|(
name|sscanf
argument_list|(
name|offset
argument_list|,
literal|"%ld"
argument_list|,
operator|&
name|offs
argument_list|)
operator|!=
literal|1
condition|)
return|return
name|FILE_MATCH_NONE
return|;
comment|/* Check type of test */
name|num_operator_ptr
operator|=
name|NULL
expr_stmt|;
name|num_operator
operator|=
literal|'\0'
expr_stmt|;
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|type
argument_list|,
literal|"byte"
argument_list|)
condition|)
block|{
name|numbytes
operator|=
literal|1
expr_stmt|;
name|num_operator_ptr
operator|=
name|type
operator|+
name|strlen
argument_list|(
literal|"byte"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|type
argument_list|,
literal|"short"
argument_list|)
condition|)
block|{
name|numbytes
operator|=
literal|2
expr_stmt|;
name|num_operator_ptr
operator|=
name|type
operator|+
name|strlen
argument_list|(
literal|"short"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|type
argument_list|,
literal|"long"
argument_list|)
condition|)
block|{
name|numbytes
operator|=
literal|4
expr_stmt|;
name|num_operator_ptr
operator|=
name|type
operator|+
name|strlen
argument_list|(
literal|"long"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|type
argument_list|,
literal|"size"
argument_list|)
condition|)
block|{
name|numbytes
operator|=
literal|5
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|type
argument_list|,
literal|"string"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|numbytes
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
return|return
name|FILE_MATCH_NONE
return|;
block|}
comment|/* Check numerical operator value if present */
if|if
condition|(
name|num_operator_ptr
operator|&&
operator|(
operator|*
name|num_operator_ptr
operator|==
literal|'&'
operator|)
condition|)
block|{
if|if
condition|(
name|g_ascii_isdigit
argument_list|(
name|num_operator_ptr
index|[
literal|1
index|]
argument_list|)
condition|)
block|{
if|if
condition|(
name|num_operator_ptr
index|[
literal|1
index|]
operator|!=
literal|'0'
condition|)
comment|/* decimal */
name|sscanf
argument_list|(
name|num_operator_ptr
operator|+
literal|1
argument_list|,
literal|"%lu"
argument_list|,
operator|&
name|num_operatorval
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|num_operator_ptr
index|[
literal|2
index|]
operator|==
literal|'x'
condition|)
comment|/* hexadecimal */
name|sscanf
argument_list|(
name|num_operator_ptr
operator|+
literal|3
argument_list|,
literal|"%lx"
argument_list|,
operator|&
name|num_operatorval
argument_list|)
expr_stmt|;
else|else
comment|/* octal */
name|sscanf
argument_list|(
name|num_operator_ptr
operator|+
literal|2
argument_list|,
literal|"%lo"
argument_list|,
operator|&
name|num_operatorval
argument_list|)
expr_stmt|;
name|num_operator
operator|=
operator|*
name|num_operator_ptr
expr_stmt|;
block|}
block|}
if|if
condition|(
name|numbytes
operator|>
literal|0
condition|)
comment|/* Numerical test ? */
block|{
name|gchar
name|num_test
init|=
literal|'='
decl_stmt|;
name|gulong
name|fileval
init|=
literal|0
decl_stmt|;
comment|/* Check test value */
if|if
condition|(
operator|(
name|value
index|[
literal|0
index|]
operator|==
literal|'>'
operator|)
operator|||
operator|(
name|value
index|[
literal|0
index|]
operator|==
literal|'<'
operator|)
condition|)
block|{
name|num_test
operator|=
name|value
index|[
literal|0
index|]
expr_stmt|;
name|value
operator|++
expr_stmt|;
block|}
name|errno
operator|=
literal|0
expr_stmt|;
name|num_testval
operator|=
name|strtol
argument_list|(
name|value
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|errno
operator|!=
literal|0
condition|)
return|return
name|FILE_MATCH_NONE
return|;
if|if
condition|(
name|numbytes
operator|==
literal|5
condition|)
comment|/* Check for file size ? */
block|{
name|struct
name|stat
name|buf
decl_stmt|;
if|if
condition|(
name|fstat
argument_list|(
name|fileno
argument_list|(
name|ifp
argument_list|)
argument_list|,
operator|&
name|buf
argument_list|)
operator|<
literal|0
condition|)
return|return
name|FILE_MATCH_NONE
return|;
name|fileval
operator|=
name|buf
operator|.
name|st_size
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|offs
operator|>=
literal|0
operator|&&
operator|(
name|offs
operator|+
name|numbytes
operator|<=
name|headsize
operator|)
condition|)
comment|/* We have it in memory ? */
block|{
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|numbytes
condition|;
name|k
operator|++
control|)
name|fileval
operator|=
operator|(
name|fileval
operator|<<
literal|8
operator|)
operator||
operator|(
name|glong
operator|)
name|file_head
index|[
name|offs
operator|+
name|k
index|]
expr_stmt|;
block|}
else|else
comment|/* Read it from file */
block|{
name|gint
name|c
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|fseek
argument_list|(
name|ifp
argument_list|,
name|offs
argument_list|,
operator|(
name|offs
operator|>=
literal|0
operator|)
condition|?
name|SEEK_SET
else|:
name|SEEK_END
argument_list|)
operator|<
literal|0
condition|)
return|return
name|FILE_MATCH_NONE
return|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|numbytes
condition|;
name|k
operator|++
control|)
name|fileval
operator|=
operator|(
name|fileval
operator|<<
literal|8
operator|)
operator||
operator|(
name|c
operator|=
name|getc
argument_list|(
name|ifp
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|c
operator|==
name|EOF
condition|)
return|return
name|FILE_MATCH_NONE
return|;
block|}
if|if
condition|(
name|num_operator
operator|==
literal|'&'
condition|)
name|fileval
operator|&=
name|num_operatorval
expr_stmt|;
if|if
condition|(
name|num_test
operator|==
literal|'<'
condition|)
name|found
operator|=
operator|(
name|fileval
operator|<
name|num_testval
operator|)
expr_stmt|;
elseif|else
if|if
condition|(
name|num_test
operator|==
literal|'>'
condition|)
name|found
operator|=
operator|(
name|fileval
operator|>
name|num_testval
operator|)
expr_stmt|;
else|else
name|found
operator|=
operator|(
name|fileval
operator|==
name|num_testval
operator|)
expr_stmt|;
if|if
condition|(
name|found
operator|&&
operator|(
name|numbytes
operator|==
literal|5
operator|)
condition|)
name|found
operator|=
name|FILE_MATCH_SIZE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|numbytes
operator|==
literal|0
condition|)
comment|/* String test */
block|{
name|gchar
name|mem_testval
index|[
literal|256
index|]
decl_stmt|;
name|file_convert_string
argument_list|(
name|value
argument_list|,
name|mem_testval
argument_list|,
sizeof|sizeof
argument_list|(
name|mem_testval
argument_list|)
argument_list|,
operator|&
name|numbytes
argument_list|)
expr_stmt|;
if|if
condition|(
name|numbytes
operator|<=
literal|0
condition|)
return|return
name|FILE_MATCH_NONE
return|;
if|if
condition|(
name|offs
operator|>=
literal|0
operator|&&
operator|(
name|offs
operator|+
name|numbytes
operator|<=
name|headsize
operator|)
condition|)
comment|/* We have it in memory ? */
block|{
name|found
operator|=
operator|(
name|memcmp
argument_list|(
name|mem_testval
argument_list|,
name|file_head
operator|+
name|offs
argument_list|,
name|numbytes
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
block|}
else|else
comment|/* Read it from file */
block|{
if|if
condition|(
name|fseek
argument_list|(
name|ifp
argument_list|,
name|offs
argument_list|,
operator|(
name|offs
operator|>=
literal|0
operator|)
condition|?
name|SEEK_SET
else|:
name|SEEK_END
argument_list|)
operator|<
literal|0
condition|)
return|return
name|FILE_MATCH_NONE
return|;
name|found
operator|=
name|FILE_MATCH_MAGIC
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|found
operator|&&
operator|(
name|k
operator|<
name|numbytes
operator|)
condition|;
name|k
operator|++
control|)
block|{
name|gint
name|c
init|=
name|getc
argument_list|(
name|ifp
argument_list|)
decl_stmt|;
name|found
operator|=
operator|(
name|c
operator|!=
name|EOF
operator|)
operator|&&
operator|(
name|c
operator|==
operator|(
name|gint
operator|)
name|mem_testval
index|[
name|k
index|]
operator|)
expr_stmt|;
block|}
block|}
block|}
return|return
name|found
return|;
block|}
end_function

begin_function
specifier|static
name|FileMatchType
DECL|function|file_check_magic_list (GSList * magics_list,const guchar * head,gint headsize,FILE * ifp)
name|file_check_magic_list
parameter_list|(
name|GSList
modifier|*
name|magics_list
parameter_list|,
specifier|const
name|guchar
modifier|*
name|head
parameter_list|,
name|gint
name|headsize
parameter_list|,
name|FILE
modifier|*
name|ifp
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|offset
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|type
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|value
decl_stmt|;
name|gboolean
name|and
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|found
init|=
name|FALSE
decl_stmt|;
name|FileMatchType
name|match_val
decl_stmt|;
while|while
condition|(
name|magics_list
condition|)
block|{
if|if
condition|(
operator|(
name|offset
operator|=
name|magics_list
operator|->
name|data
operator|)
operator|==
name|NULL
condition|)
break|break;
if|if
condition|(
operator|(
name|magics_list
operator|=
name|magics_list
operator|->
name|next
operator|)
operator|==
name|NULL
condition|)
break|break;
if|if
condition|(
operator|(
name|type
operator|=
name|magics_list
operator|->
name|data
operator|)
operator|==
name|NULL
condition|)
break|break;
if|if
condition|(
operator|(
name|magics_list
operator|=
name|magics_list
operator|->
name|next
operator|)
operator|==
name|NULL
condition|)
break|break;
if|if
condition|(
operator|(
name|value
operator|=
name|magics_list
operator|->
name|data
operator|)
operator|==
name|NULL
condition|)
break|break;
name|magics_list
operator|=
name|magics_list
operator|->
name|next
expr_stmt|;
name|match_val
operator|=
name|file_check_single_magic
argument_list|(
name|offset
argument_list|,
name|type
argument_list|,
name|value
argument_list|,
name|head
argument_list|,
name|headsize
argument_list|,
name|ifp
argument_list|)
expr_stmt|;
if|if
condition|(
name|and
condition|)
name|found
operator|=
name|found
operator|&&
operator|(
name|match_val
operator|!=
name|FILE_MATCH_NONE
operator|)
expr_stmt|;
else|else
name|found
operator|=
operator|(
name|match_val
operator|!=
name|FILE_MATCH_NONE
operator|)
expr_stmt|;
name|and
operator|=
operator|(
name|strchr
argument_list|(
name|offset
argument_list|,
literal|'&'
argument_list|)
operator|!=
name|NULL
operator|)
expr_stmt|;
if|if
condition|(
operator|!
name|and
operator|&&
name|found
condition|)
return|return
name|match_val
return|;
block|}
return|return
name|FILE_MATCH_NONE
return|;
block|}
end_function

end_unit

