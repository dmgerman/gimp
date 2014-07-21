begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * file-procedure.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gdk-pixbuf/gdk-pixbuf.h>
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
DECL|enum|__anon2ba049bf0103
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
name|GFile
modifier|*
name|file
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
name|GFile
modifier|*
name|file
parameter_list|,
name|gboolean
name|skip_magic
parameter_list|,
name|gboolean
name|uri_procs_only
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
name|GFile
modifier|*
name|file
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
name|GFile
modifier|*
name|file
parameter_list|,
name|GInputStream
modifier|*
name|input
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
name|GFile
modifier|*
name|file
parameter_list|,
name|GInputStream
modifier|*
name|input
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpPlugInProcedure
modifier|*
DECL|function|file_procedure_find (GSList * procs,GFile * file,GError ** error)
name|file_procedure_find
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
name|GFile
modifier|*
name|file
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
name|list
decl_stmt|;
name|GimpPlugInProcedure
modifier|*
name|size_matched_proc
init|=
name|NULL
decl_stmt|;
name|GInputStream
modifier|*
name|input
init|=
name|NULL
decl_stmt|;
name|gboolean
name|opened
init|=
name|FALSE
decl_stmt|;
name|gsize
name|head_size
init|=
literal|0
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
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
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
comment|/* First, check magicless prefixes/suffixes: */
if|if
condition|(
operator|!
name|file_proc_find_by_extension
argument_list|(
name|procs
argument_list|,
name|file
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
condition|)
block|{
comment|/* If there is not any (with or without magic) file proc that        * can load the file by extension directly, try to find a proc        * that can load the prefix        */
name|file_proc
operator|=
name|file_proc_find_by_prefix
argument_list|(
name|procs
argument_list|,
name|file
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Otherwise try to find a magicless file proc that handles the        * extension        */
name|file_proc
operator|=
name|file_proc_find_by_extension
argument_list|(
name|procs
argument_list|,
name|file
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|file_proc
condition|)
return|return
name|file_proc
return|;
comment|/* Then look for magics */
for|for
control|(
name|list
operator|=
name|procs
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|file_proc
operator|=
name|list
operator|->
name|data
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
name|G_UNLIKELY
argument_list|(
operator|!
name|opened
argument_list|)
condition|)
block|{
name|input
operator|=
name|G_INPUT_STREAM
argument_list|(
name|g_file_read
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|input
condition|)
block|{
name|g_input_stream_read_all
argument_list|(
name|input
argument_list|,
name|head
argument_list|,
sizeof|sizeof
argument_list|(
name|head
argument_list|)
argument_list|,
operator|&
name|head_size
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|head_size
operator|<
literal|4
condition|)
block|{
name|g_object_unref
argument_list|(
name|input
argument_list|)
expr_stmt|;
name|input
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|GDataInputStream
modifier|*
name|data_input
decl_stmt|;
name|data_input
operator|=
name|g_data_input_stream_new
argument_list|(
name|input
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|input
argument_list|)
expr_stmt|;
name|input
operator|=
name|G_INPUT_STREAM
argument_list|(
name|data_input
argument_list|)
expr_stmt|;
block|}
block|}
name|opened
operator|=
name|TRUE
expr_stmt|;
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
name|file
argument_list|,
name|input
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
name|g_object_unref
argument_list|(
name|input
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
name|input
condition|)
block|{
if|#
directive|if
literal|0
block|if (ferror (ifp))         g_set_error_literal (error, G_FILE_ERROR,                              g_file_error_from_errno (errno),                              g_strerror (errno));
endif|#
directive|endif
name|g_object_unref
argument_list|(
name|input
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|size_match_count
operator|==
literal|1
condition|)
return|return
name|size_matched_proc
return|;
comment|/* As a last resort, try matching by name, not skipping magic procs */
name|file_proc
operator|=
name|file_proc_find_by_name
argument_list|(
name|procs
argument_list|,
name|file
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
name|g_set_error_literal
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
DECL|function|file_procedure_find_by_prefix (GSList * procs,GFile * file)
name|file_procedure_find_by_prefix
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|file_proc_find_by_prefix
argument_list|(
name|procs
argument_list|,
name|file
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpPlugInProcedure
modifier|*
DECL|function|file_procedure_find_by_extension (GSList * procs,GFile * file)
name|file_procedure_find_by_extension
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|file_proc_find_by_extension
argument_list|(
name|procs
argument_list|,
name|file
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpPlugInProcedure
modifier|*
DECL|function|file_procedure_find_by_mime_type (GSList * procs,const gchar * mime_type)
name|file_procedure_find_by_mime_type
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_type
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|mime_type
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|procs
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|proc
operator|->
name|mime_type
operator|&&
operator|!
name|strcmp
argument_list|(
name|mime_type
argument_list|,
name|proc
operator|->
name|mime_type
argument_list|)
condition|)
return|return
name|proc
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|file_procedure_in_group (GimpPlugInProcedure * file_proc,FileProcedureGroup group)
name|file_procedure_in_group
parameter_list|(
name|GimpPlugInProcedure
modifier|*
name|file_proc
parameter_list|,
name|FileProcedureGroup
name|group
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
name|gimp_object_get_name
argument_list|(
name|file_proc
argument_list|)
decl_stmt|;
name|gboolean
name|is_xcf_save
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|is_filter
init|=
name|FALSE
decl_stmt|;
name|is_xcf_save
operator|=
operator|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"gimp-xcf-save"
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
name|is_filter
operator|=
operator|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file-gz-save"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file-bz2-save"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file-xz-save"
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
switch|switch
condition|(
name|group
condition|)
block|{
case|case
name|FILE_PROCEDURE_GROUP_SAVE
case|:
comment|/* Only .xcf shall pass */
return|return
name|is_xcf_save
operator|||
name|is_filter
return|;
case|case
name|FILE_PROCEDURE_GROUP_EXPORT
case|:
comment|/* Anything but .xcf shall pass */
return|return
operator|!
name|is_xcf_save
return|;
case|case
name|FILE_PROCEDURE_GROUP_OPEN
case|:
comment|/* No filter applied for Open */
return|return
name|TRUE
return|;
default|default:
case|case
name|FILE_PROCEDURE_GROUP_ANY
case|:
return|return
name|TRUE
return|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpPlugInProcedure
modifier|*
DECL|function|file_proc_find_by_prefix (GSList * procs,GFile * file,gboolean skip_magic)
name|file_proc_find_by_prefix
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|gboolean
name|skip_magic
parameter_list|)
block|{
name|gchar
modifier|*
name|uri
init|=
name|g_file_get_uri
argument_list|(
name|file
argument_list|)
decl_stmt|;
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
block|{
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
return|return
name|proc
return|;
block|}
block|}
block|}
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|GimpPlugInProcedure
modifier|*
DECL|function|file_proc_find_by_extension (GSList * procs,GFile * file,gboolean skip_magic,gboolean uri_procs_only)
name|file_proc_find_by_extension
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|gboolean
name|skip_magic
parameter_list|,
name|gboolean
name|uri_procs_only
parameter_list|)
block|{
name|gchar
modifier|*
name|ext
init|=
name|file_utils_file_get_ext
argument_list|(
name|file
argument_list|)
decl_stmt|;
if|if
condition|(
name|ext
condition|)
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
if|if
condition|(
name|uri_procs_only
operator|&&
operator|!
name|proc
operator|->
name|handles_uri
condition|)
continue|continue;
if|if
condition|(
name|skip_magic
operator|&&
name|proc
operator|->
name|magics_list
condition|)
continue|continue;
if|if
condition|(
name|g_slist_find_custom
argument_list|(
name|proc
operator|->
name|extensions_list
argument_list|,
name|ext
operator|+
literal|1
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|g_ascii_strcasecmp
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|ext
argument_list|)
expr_stmt|;
return|return
name|proc
return|;
block|}
block|}
name|g_free
argument_list|(
name|ext
argument_list|)
expr_stmt|;
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
DECL|function|file_proc_find_by_name (GSList * procs,GFile * file,gboolean skip_magic)
name|file_proc_find_by_name
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
name|GFile
modifier|*
name|file
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
name|file_proc_find_by_extension
argument_list|(
name|procs
argument_list|,
name|file
argument_list|,
name|skip_magic
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
name|proc
operator|=
name|file_proc_find_by_prefix
argument_list|(
name|procs
argument_list|,
name|file
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
name|file
argument_list|,
name|skip_magic
argument_list|,
name|FALSE
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
DECL|function|file_check_single_magic (const gchar * offset,const gchar * type,const gchar * value,const guchar * file_head,gint headsize,GFile * file,GInputStream * input)
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
name|GFile
modifier|*
name|file
parameter_list|,
name|GInputStream
modifier|*
name|input
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
name|GFileInfo
modifier|*
name|info
init|=
name|g_file_query_info
argument_list|(
name|file
argument_list|,
name|G_FILE_ATTRIBUTE_STANDARD_SIZE
argument_list|,
name|G_FILE_QUERY_INFO_NONE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|info
condition|)
return|return
name|FILE_MATCH_NONE
return|;
name|fileval
operator|=
name|g_file_info_get_size
argument_list|(
name|info
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|info
argument_list|)
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
if|if
condition|(
operator|!
name|g_seekable_seek
argument_list|(
name|G_SEEKABLE
argument_list|(
name|input
argument_list|)
argument_list|,
name|offs
argument_list|,
operator|(
name|offs
operator|>=
literal|0
operator|)
condition|?
name|G_SEEK_SET
else|:
name|G_SEEK_END
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
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
block|{
name|guchar
name|byte
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|byte
operator|=
name|g_data_input_stream_read_byte
argument_list|(
name|G_DATA_INPUT_STREAM
argument_list|(
name|input
argument_list|)
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
return|return
name|FILE_MATCH_NONE
return|;
block|}
name|fileval
operator|=
operator|(
name|fileval
operator|<<
literal|8
operator|)
operator||
name|byte
expr_stmt|;
block|}
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
operator|!
name|g_seekable_seek
argument_list|(
name|G_SEEKABLE
argument_list|(
name|input
argument_list|)
argument_list|,
name|offs
argument_list|,
operator|(
name|offs
operator|>=
literal|0
operator|)
condition|?
name|G_SEEK_SET
else|:
name|G_SEEK_END
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
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
name|guchar
name|byte
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|byte
operator|=
name|g_data_input_stream_read_byte
argument_list|(
name|G_DATA_INPUT_STREAM
argument_list|(
name|input
argument_list|)
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
return|return
name|FILE_MATCH_NONE
return|;
block|}
if|if
condition|(
name|byte
operator|!=
name|mem_testval
index|[
name|k
index|]
condition|)
name|found
operator|=
name|FILE_MATCH_NONE
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
DECL|function|file_check_magic_list (GSList * magics_list,const guchar * head,gint headsize,GFile * file,GInputStream * input)
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
name|GFile
modifier|*
name|file
parameter_list|,
name|GInputStream
modifier|*
name|input
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
name|file
argument_list|,
name|input
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

