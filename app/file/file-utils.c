begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * file-utils.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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

begin_include
include|#
directive|include
file|<sys/stat.h>
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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc-def.h"
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

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|PlugInProcDef
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
name|PlugInProcDef
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
name|PlugInProcDef
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
name|gint
name|file_check_single_magic
parameter_list|(
name|gchar
modifier|*
name|offset
parameter_list|,
name|gchar
modifier|*
name|type
parameter_list|,
name|gchar
modifier|*
name|value
parameter_list|,
name|gint
name|headsize
parameter_list|,
name|guchar
modifier|*
name|file_head
parameter_list|,
name|FILE
modifier|*
name|ifp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|file_check_magic_list
parameter_list|(
name|GSList
modifier|*
name|magics_list
parameter_list|,
name|gint
name|headsize
parameter_list|,
name|guchar
modifier|*
name|head
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
name|gchar
modifier|*
DECL|function|file_utils_filename_to_uri (GSList * procs,const gchar * filename,GError ** error)
name|file_utils_filename_to_uri
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
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
name|gchar
modifier|*
name|absolute
decl_stmt|;
name|gchar
modifier|*
name|uri
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
name|filename
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  check for prefixes like http or ftp  */
if|if
condition|(
name|file_proc_find_by_prefix
argument_list|(
name|procs
argument_list|,
name|filename
argument_list|,
name|FALSE
argument_list|)
condition|)
block|{
if|if
condition|(
name|g_utf8_validate
argument_list|(
name|filename
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
return|return
name|g_strdup
argument_list|(
name|filename
argument_list|)
return|;
block|}
else|else
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_CONVERT_ERROR
argument_list|,
name|G_CONVERT_ERROR_ILLEGAL_SEQUENCE
argument_list|,
name|_
argument_list|(
literal|"Invalid character sequence in URI"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
if|if
condition|(
operator|!
name|g_path_is_absolute
argument_list|(
name|filename
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|current
decl_stmt|;
name|current
operator|=
name|g_get_current_dir
argument_list|()
expr_stmt|;
name|absolute
operator|=
name|g_build_filename
argument_list|(
name|current
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|current
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|absolute
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|uri
operator|=
name|g_filename_to_uri
argument_list|(
name|absolute
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|absolute
argument_list|)
expr_stmt|;
return|return
name|uri
return|;
block|}
end_function

begin_function
name|PlugInProcDef
modifier|*
DECL|function|file_utils_find_proc (GSList * procs,const gchar * uri)
name|file_utils_find_proc
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
name|PlugInProcDef
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
name|g_filename_from_uri
argument_list|(
name|uri
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Then look for magics */
if|if
condition|(
name|filename
condition|)
block|{
name|PlugInProcDef
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
name|gint
name|match_val
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
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"rb"
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
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
if|if
condition|(
name|head_size
operator|>=
literal|4
condition|)
block|{
name|match_val
operator|=
name|file_check_magic_list
argument_list|(
name|file_proc
operator|->
name|magics_list
argument_list|,
name|head_size
argument_list|,
name|head
argument_list|,
name|ifp
argument_list|)
expr_stmt|;
if|if
condition|(
name|match_val
operator|==
literal|2
condition|)
comment|/* size match ? */
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
comment|/* As a last ditch, try matching by name */
return|return
name|file_proc_find_by_name
argument_list|(
name|all_procs
argument_list|,
name|uri
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|file_utils_uri_to_utf8_basename (const gchar * uri)
name|file_utils_uri_to_utf8_basename
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|g_assert
argument_list|(
name|uri
operator|!=
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
name|filename
operator|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|strstr
argument_list|(
name|filename
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|)
condition|)
block|{
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|basename
return|;
block|}
elseif|else
if|if
condition|(
name|strstr
argument_list|(
name|filename
argument_list|,
literal|"://"
argument_list|)
condition|)
block|{
name|basename
operator|=
name|strrchr
argument_list|(
name|uri
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
name|basename
operator|=
name|g_strdup
argument_list|(
name|basename
operator|+
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|basename
return|;
block|}
return|return
name|filename
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|file_utils_uri_to_utf8_filename (const gchar * uri)
name|file_utils_uri_to_utf8_filename
parameter_list|(
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
if|if
condition|(
operator|!
name|strncmp
argument_list|(
name|uri
argument_list|,
literal|"file:"
argument_list|,
name|strlen
argument_list|(
literal|"file:"
argument_list|)
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|g_filename_from_uri
argument_list|(
name|uri
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|gchar
modifier|*
name|utf8
init|=
name|g_filename_to_utf8
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
decl_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|utf8
return|;
block|}
block|}
return|return
name|g_strdup
argument_list|(
name|uri
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|PlugInProcDef
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
name|PlugInProcDef
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
name|strncmp
argument_list|(
name|uri
argument_list|,
name|prefixes
operator|->
name|data
argument_list|,
name|strlen
argument_list|(
name|prefixes
operator|->
name|data
argument_list|)
argument_list|)
operator|==
literal|0
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
name|PlugInProcDef
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
name|PlugInProcDef
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
name|gchar
modifier|*
name|p1
init|=
name|ext
decl_stmt|;
name|gchar
modifier|*
name|p2
init|=
operator|(
name|gchar
operator|*
operator|)
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
name|PlugInProcDef
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
name|PlugInProcDef
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
DECL|function|file_convert_string (gchar * instr,gchar * outmem,gint maxmem,gint * nmem)
name|file_convert_string
parameter_list|(
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
name|guchar
modifier|*
name|uin
init|=
operator|(
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
name|gint
DECL|function|file_check_single_magic (gchar * offset,gchar * type,gchar * value,gint headsize,guchar * file_head,FILE * ifp)
name|file_check_single_magic
parameter_list|(
name|gchar
modifier|*
name|offset
parameter_list|,
name|gchar
modifier|*
name|type
parameter_list|,
name|gchar
modifier|*
name|value
parameter_list|,
name|gint
name|headsize
parameter_list|,
name|guchar
modifier|*
name|file_head
parameter_list|,
name|FILE
modifier|*
name|ifp
parameter_list|)
block|{
comment|/* Return values are 0: no match, 1: magic match, 2: size match */
name|glong
name|offs
decl_stmt|;
name|gulong
name|num_testval
decl_stmt|,
name|num_operatorval
decl_stmt|;
name|gulong
name|fileval
decl_stmt|;
name|gint
name|numbytes
decl_stmt|,
name|k
decl_stmt|,
name|c
init|=
literal|0
decl_stmt|,
name|found
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
name|num_operator_ptr
decl_stmt|,
name|num_operator
decl_stmt|,
name|num_test
decl_stmt|;
name|guchar
name|mem_testval
index|[
literal|256
index|]
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
operator|(
literal|0
operator|)
return|;
if|if
condition|(
name|offs
operator|<
literal|0
condition|)
return|return
operator|(
literal|0
operator|)
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
name|num_test
operator|=
literal|'='
expr_stmt|;
if|if
condition|(
name|strncmp
argument_list|(
name|type
argument_list|,
literal|"byte"
argument_list|,
literal|4
argument_list|)
operator|==
literal|0
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
literal|4
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strncmp
argument_list|(
name|type
argument_list|,
literal|"short"
argument_list|,
literal|5
argument_list|)
operator|==
literal|0
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
literal|5
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strncmp
argument_list|(
name|type
argument_list|,
literal|"long"
argument_list|,
literal|4
argument_list|)
operator|==
literal|0
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
literal|4
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strncmp
argument_list|(
name|type
argument_list|,
literal|"size"
argument_list|,
literal|4
argument_list|)
operator|==
literal|0
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
return|return
operator|(
literal|0
operator|)
return|;
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
comment|/* Check test value */
if|if
condition|(
operator|(
name|value
index|[
literal|0
index|]
operator|==
literal|'='
operator|)
operator|||
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
if|if
condition|(
operator|!
name|g_ascii_isdigit
argument_list|(
name|value
index|[
literal|0
index|]
argument_list|)
condition|)
return|return
operator|(
literal|0
operator|)
return|;
comment|/*         * to anybody reading this: is strtol's parsing behaviour        * (e.g. "0x" prefix) broken on some systems or why do we        * do the base detection ourselves?        * */
if|if
condition|(
name|value
index|[
literal|0
index|]
operator|!=
literal|'0'
condition|)
comment|/* decimal */
name|num_testval
operator|=
name|strtol
argument_list|(
name|value
argument_list|,
name|NULL
argument_list|,
literal|10
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|value
index|[
literal|1
index|]
operator|==
literal|'x'
condition|)
comment|/* hexadecimal */
name|num_testval
operator|=
operator|(
name|unsigned
name|long
operator|)
name|strtoul
argument_list|(
name|value
operator|+
literal|2
argument_list|,
name|NULL
argument_list|,
literal|16
argument_list|)
expr_stmt|;
else|else
comment|/* octal */
name|num_testval
operator|=
name|strtol
argument_list|(
name|value
operator|+
literal|1
argument_list|,
name|NULL
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|fileval
operator|=
literal|0
expr_stmt|;
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
operator|(
literal|0
operator|)
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
operator|+
name|numbytes
operator|<=
name|headsize
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
name|long
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
if|if
condition|(
name|fseek
argument_list|(
name|ifp
argument_list|,
name|offs
argument_list|,
name|SEEK_SET
argument_list|)
operator|<
literal|0
condition|)
return|return
operator|(
literal|0
operator|)
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
operator|(
literal|0
operator|)
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
literal|2
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
name|file_convert_string
argument_list|(
operator|(
name|char
operator|*
operator|)
name|value
argument_list|,
operator|(
name|char
operator|*
operator|)
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
operator|(
literal|0
operator|)
return|;
if|if
condition|(
name|offs
operator|+
name|numbytes
operator|<=
name|headsize
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
name|SEEK_SET
argument_list|)
operator|<
literal|0
condition|)
return|return
operator|(
literal|0
operator|)
return|;
name|found
operator|=
literal|1
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
name|c
operator|=
name|getc
argument_list|(
name|ifp
argument_list|)
expr_stmt|;
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
name|int
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

begin_comment
comment|/*  *  Return values are 0: no match, 1: magic match, 2: size match  */
end_comment

begin_function
specifier|static
name|gint
DECL|function|file_check_magic_list (GSList * magics_list,gint headsize,guchar * head,FILE * ifp)
name|file_check_magic_list
parameter_list|(
name|GSList
modifier|*
name|magics_list
parameter_list|,
name|gint
name|headsize
parameter_list|,
name|guchar
modifier|*
name|head
parameter_list|,
name|FILE
modifier|*
name|ifp
parameter_list|)
block|{
name|gchar
modifier|*
name|offset
decl_stmt|;
name|gchar
modifier|*
name|type
decl_stmt|;
name|gchar
modifier|*
name|value
decl_stmt|;
name|gint
name|and
init|=
literal|0
decl_stmt|;
name|gint
name|found
init|=
literal|0
decl_stmt|;
name|gint
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
operator|(
name|gchar
operator|*
operator|)
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
operator|(
name|gchar
operator|*
operator|)
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
operator|(
name|gchar
operator|*
operator|)
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
name|headsize
argument_list|,
name|head
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
name|match_val
expr_stmt|;
else|else
name|found
operator|=
name|match_val
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
operator|(
operator|!
name|and
operator|)
operator|&&
name|found
condition|)
return|return
name|match_val
return|;
block|}
return|return
literal|0
return|;
block|}
end_function

end_unit

