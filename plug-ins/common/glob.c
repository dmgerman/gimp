begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* The idea is taken from a plug-in written by George Hartz; the code isn't.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_define
DECL|macro|PROCEDURE_NAME
define|#
directive|define
name|PROCEDURE_NAME
value|"file_glob"
end_define

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
name|gboolean
name|glob_match
parameter_list|(
specifier|const
name|gchar
modifier|*
name|pattern
parameter_list|,
name|gint
modifier|*
name|num_matches
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|matches
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|glob_fnmatch
parameter_list|(
specifier|const
name|gchar
modifier|*
name|pattern
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
name|NULL
block|,
name|query
block|,
name|run
block|, }
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
name|GimpParamDef
name|glob_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"pattern"
block|,
literal|"The glob pattern (in UTF-8 encoding)"
block|}
block|}
decl_stmt|;
specifier|static
name|GimpParamDef
name|glob_return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"num_files"
block|,
literal|"The number of returned names"
block|}
block|,
block|{
name|GIMP_PDB_STRINGARRAY
block|,
literal|"files"
block|,
literal|"The list of matching names"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PROCEDURE_NAME
argument_list|,
literal|"Returns a list of matching filenames"
argument_list|,
literal|"This can be useful in scripts and other plugins "
literal|"(e.g., batch-conversion). See the glob(7) manpage "
literal|"for more info. Note however that this isn't a "
literal|"full-featured glob implementation. It only handles "
literal|"simple patterns like \"/home/foo/bar/*.jpg\". "
literal|"The pattern is expected to be in UTF-8 encoding "
literal|"and all returned names are UTF-8 encoded as well."
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"2004"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|glob_args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|glob_return_vals
argument_list|)
argument_list|,
name|glob_args
argument_list|,
name|glob_return_vals
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
literal|3
index|]
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
name|PROCEDURE_NAME
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gchar
modifier|*
modifier|*
name|matches
decl_stmt|;
name|gint
name|num_matches
decl_stmt|;
if|if
condition|(
operator|!
name|glob_match
argument_list|(
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
operator|&
name|num_matches
argument_list|,
operator|&
name|matches
argument_list|)
condition|)
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
return|return;
block|}
operator|*
name|nreturn_vals
operator|=
literal|3
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
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_INT32
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
name|num_matches
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STRINGARRAY
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_stringarray
operator|=
name|matches
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|glob_match (const gchar * pattern,gint * num_matches,gchar *** matches)
name|glob_match
parameter_list|(
specifier|const
name|gchar
modifier|*
name|pattern
parameter_list|,
name|gint
modifier|*
name|num_matches
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|matches
parameter_list|)
block|{
name|GDir
modifier|*
name|dir
decl_stmt|;
name|GPtrArray
modifier|*
name|array
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|dirname
decl_stmt|;
name|gchar
modifier|*
name|tmp
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|pattern
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|num_matches
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|matches
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
operator|*
name|num_matches
operator|=
literal|0
expr_stmt|;
operator|*
name|matches
operator|=
name|NULL
expr_stmt|;
comment|/*  This is not a complete glob() implementation but rather a very    *  simplistic approach. However it works for the most common use    *  case and is better than nothing.    */
name|tmp
operator|=
name|g_filename_from_utf8
argument_list|(
name|pattern
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
operator|!
name|tmp
condition|)
return|return
name|FALSE
return|;
name|dirname
operator|=
name|g_path_get_dirname
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
name|dir
operator|=
name|g_dir_open
argument_list|(
name|dirname
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir
condition|)
block|{
name|g_free
argument_list|(
name|dirname
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
comment|/*  check if the pattern has a directory part at all  */
name|tmp
operator|=
name|g_path_get_basename
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|pattern
argument_list|,
name|tmp
argument_list|)
operator|==
literal|0
condition|)
block|{
name|g_free
argument_list|(
name|dirname
argument_list|)
expr_stmt|;
name|dirname
operator|=
name|NULL
expr_stmt|;
block|}
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
name|array
operator|=
name|g_ptr_array_new
argument_list|()
expr_stmt|;
for|for
control|(
name|filename
operator|=
name|g_dir_read_name
argument_list|(
name|dir
argument_list|)
init|;
name|filename
condition|;
name|filename
operator|=
name|g_dir_read_name
argument_list|(
name|dir
argument_list|)
control|)
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
if|if
condition|(
name|dirname
condition|)
block|{
name|gchar
modifier|*
name|path
init|=
name|g_build_filename
argument_list|(
name|dirname
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|name
operator|=
name|g_filename_to_utf8
argument_list|(
name|path
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
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|name
operator|=
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
expr_stmt|;
block|}
if|if
condition|(
name|name
operator|&&
name|glob_fnmatch
argument_list|(
name|pattern
argument_list|,
name|name
argument_list|)
condition|)
name|g_ptr_array_add
argument_list|(
name|array
argument_list|,
name|name
argument_list|)
expr_stmt|;
else|else
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
name|g_dir_close
argument_list|(
name|dir
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dirname
argument_list|)
expr_stmt|;
operator|*
name|num_matches
operator|=
name|array
operator|->
name|len
expr_stmt|;
operator|*
name|matches
operator|=
operator|(
name|gchar
operator|*
operator|*
operator|)
name|g_ptr_array_free
argument_list|(
name|array
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  * The following code is borrowed from GTK+.  *  * GTK+ used to use a old version of GNU fnmatch() that was buggy  * in various ways and didn't handle UTF-8. The following is  * converted to UTF-8. To simplify the process of making it  * correct, this is special-cased to the combinations of flags  * that gtkfilesel.c uses.  *  *   FNM_FILE_NAME   - always set  *   FNM_LEADING_DIR - never set  *   FNM_NOESCAPE    - set only on windows  *   FNM_CASEFOLD    - set only on windows  */
end_comment

begin_comment
comment|/* We need to make sure that all constants are defined  * to properly compile this file  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GNU_SOURCE
end_ifndef

begin_define
DECL|macro|_GNU_SOURCE
define|#
directive|define
name|_GNU_SOURCE
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|gunichar
DECL|function|get_char (const char ** str)
name|get_char
parameter_list|(
specifier|const
name|char
modifier|*
modifier|*
name|str
parameter_list|)
block|{
name|gunichar
name|c
init|=
name|g_utf8_get_char
argument_list|(
operator|*
name|str
argument_list|)
decl_stmt|;
operator|*
name|str
operator|=
name|g_utf8_next_char
argument_list|(
operator|*
name|str
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|G_PLATFORM_WIN32
name|c
operator|=
name|g_unichar_tolower
argument_list|(
name|c
argument_list|)
expr_stmt|;
endif|#
directive|endif
return|return
name|c
return|;
block|}
end_function

begin_if
if|#
directive|if
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
operator|||
name|defined
argument_list|(
name|G_WITH_CYGWIN
argument_list|)
end_if

begin_define
DECL|macro|DO_ESCAPE
define|#
directive|define
name|DO_ESCAPE
value|0
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|DO_ESCAPE
define|#
directive|define
name|DO_ESCAPE
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|gunichar
DECL|function|get_unescaped_char (const char ** str,gboolean * was_escaped)
name|get_unescaped_char
parameter_list|(
specifier|const
name|char
modifier|*
modifier|*
name|str
parameter_list|,
name|gboolean
modifier|*
name|was_escaped
parameter_list|)
block|{
name|gunichar
name|c
init|=
name|get_char
argument_list|(
name|str
argument_list|)
decl_stmt|;
operator|*
name|was_escaped
operator|=
name|DO_ESCAPE
operator|&&
name|c
operator|==
literal|'\\'
expr_stmt|;
if|if
condition|(
operator|*
name|was_escaped
condition|)
name|c
operator|=
name|get_char
argument_list|(
name|str
argument_list|)
expr_stmt|;
return|return
name|c
return|;
block|}
end_function

begin_comment
comment|/* Match STRING against the filename pattern PATTERN,  * returning TRUE if it matches, FALSE otherwise.  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|fnmatch_intern (const gchar * pattern,const gchar * string,gboolean component_start,gboolean no_leading_period)
name|fnmatch_intern
parameter_list|(
specifier|const
name|gchar
modifier|*
name|pattern
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
name|gboolean
name|component_start
parameter_list|,
name|gboolean
name|no_leading_period
parameter_list|)
block|{
specifier|const
name|char
modifier|*
name|p
init|=
name|pattern
decl_stmt|,
modifier|*
name|n
init|=
name|string
decl_stmt|;
while|while
condition|(
operator|*
name|p
condition|)
block|{
specifier|const
name|char
modifier|*
name|last_n
init|=
name|n
decl_stmt|;
name|gunichar
name|c
init|=
name|get_char
argument_list|(
operator|&
name|p
argument_list|)
decl_stmt|;
name|gunichar
name|nc
init|=
name|get_char
argument_list|(
operator|&
name|n
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|c
condition|)
block|{
case|case
literal|'?'
case|:
if|if
condition|(
name|nc
operator|==
literal|'\0'
condition|)
return|return
name|FALSE
return|;
elseif|else
if|if
condition|(
name|nc
operator|==
name|G_DIR_SEPARATOR
condition|)
return|return
name|FALSE
return|;
elseif|else
if|if
condition|(
name|nc
operator|==
literal|'.'
operator|&&
name|component_start
operator|&&
name|no_leading_period
condition|)
return|return
name|FALSE
return|;
break|break;
case|case
literal|'\\'
case|:
if|if
condition|(
name|DO_ESCAPE
condition|)
name|c
operator|=
name|get_char
argument_list|(
operator|&
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
name|nc
operator|!=
name|c
condition|)
return|return
name|FALSE
return|;
break|break;
case|case
literal|'*'
case|:
if|if
condition|(
name|nc
operator|==
literal|'.'
operator|&&
name|component_start
operator|&&
name|no_leading_period
condition|)
return|return
name|FALSE
return|;
block|{
specifier|const
name|char
modifier|*
name|last_p
init|=
name|p
decl_stmt|;
for|for
control|(
name|last_p
operator|=
name|p
operator|,
name|c
operator|=
name|get_char
argument_list|(
operator|&
name|p
argument_list|)
init|;
name|c
operator|==
literal|'?'
operator|||
name|c
operator|==
literal|'*'
condition|;
name|last_p
operator|=
name|p
operator|,
name|c
operator|=
name|get_char
argument_list|(
operator|&
name|p
argument_list|)
control|)
block|{
if|if
condition|(
name|c
operator|==
literal|'?'
condition|)
block|{
if|if
condition|(
name|nc
operator|==
literal|'\0'
condition|)
return|return
name|FALSE
return|;
elseif|else
if|if
condition|(
name|nc
operator|==
name|G_DIR_SEPARATOR
condition|)
return|return
name|FALSE
return|;
else|else
block|{
name|last_n
operator|=
name|n
expr_stmt|;
name|nc
operator|=
name|get_char
argument_list|(
operator|&
name|n
argument_list|)
expr_stmt|;
block|}
block|}
block|}
comment|/* If the pattern ends with wildcards, we have a 	     * guaranteed match unless there is a dir separator 	     * in the remainder of the string. 	     */
if|if
condition|(
name|c
operator|==
literal|'\0'
condition|)
block|{
if|if
condition|(
name|strchr
argument_list|(
name|last_n
argument_list|,
name|G_DIR_SEPARATOR
argument_list|)
operator|!=
name|NULL
condition|)
return|return
name|FALSE
return|;
else|else
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|DO_ESCAPE
operator|&&
name|c
operator|==
literal|'\\'
condition|)
name|c
operator|=
name|get_char
argument_list|(
operator|&
name|p
argument_list|)
expr_stmt|;
for|for
control|(
name|p
operator|=
name|last_p
init|;
name|nc
operator|!=
literal|'\0'
condition|;
control|)
block|{
if|if
condition|(
operator|(
name|c
operator|==
literal|'['
operator|||
name|nc
operator|==
name|c
operator|)
operator|&&
name|fnmatch_intern
argument_list|(
name|p
argument_list|,
name|last_n
argument_list|,
name|component_start
argument_list|,
name|no_leading_period
argument_list|)
condition|)
return|return
name|TRUE
return|;
name|component_start
operator|=
operator|(
name|nc
operator|==
name|G_DIR_SEPARATOR
operator|)
expr_stmt|;
name|last_n
operator|=
name|n
expr_stmt|;
name|nc
operator|=
name|get_char
argument_list|(
operator|&
name|n
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
case|case
literal|'['
case|:
block|{
comment|/* Nonzero if the sense of the character class is inverted.  */
name|gboolean
name|not
decl_stmt|;
name|gboolean
name|was_escaped
decl_stmt|;
if|if
condition|(
name|nc
operator|==
literal|'\0'
operator|||
name|nc
operator|==
name|G_DIR_SEPARATOR
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|nc
operator|==
literal|'.'
operator|&&
name|component_start
operator|&&
name|no_leading_period
condition|)
return|return
name|FALSE
return|;
name|not
operator|=
operator|(
operator|*
name|p
operator|==
literal|'!'
operator|||
operator|*
name|p
operator|==
literal|'^'
operator|)
expr_stmt|;
if|if
condition|(
name|not
condition|)
operator|++
name|p
expr_stmt|;
name|c
operator|=
name|get_unescaped_char
argument_list|(
operator|&
name|p
argument_list|,
operator|&
name|was_escaped
argument_list|)
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
specifier|register
name|gunichar
name|cstart
init|=
name|c
decl_stmt|,
name|cend
init|=
name|c
decl_stmt|;
if|if
condition|(
name|c
operator|==
literal|'\0'
condition|)
comment|/* [ (unterminated) loses.  */
return|return
name|FALSE
return|;
name|c
operator|=
name|get_unescaped_char
argument_list|(
operator|&
name|p
argument_list|,
operator|&
name|was_escaped
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|was_escaped
operator|&&
name|c
operator|==
literal|'-'
operator|&&
operator|*
name|p
operator|!=
literal|']'
condition|)
block|{
name|cend
operator|=
name|get_unescaped_char
argument_list|(
operator|&
name|p
argument_list|,
operator|&
name|was_escaped
argument_list|)
expr_stmt|;
if|if
condition|(
name|cend
operator|==
literal|'\0'
condition|)
return|return
name|FALSE
return|;
name|c
operator|=
name|get_char
argument_list|(
operator|&
name|p
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|nc
operator|>=
name|cstart
operator|&&
name|nc
operator|<=
name|cend
condition|)
goto|goto
name|matched
goto|;
if|if
condition|(
operator|!
name|was_escaped
operator|&&
name|c
operator|==
literal|']'
condition|)
break|break;
block|}
if|if
condition|(
operator|!
name|not
condition|)
return|return
name|FALSE
return|;
break|break;
name|matched
label|:
empty_stmt|;
comment|/* Skip the rest of the [...] that already matched.  */
comment|/* XXX 1003.2d11 is unclear if was_escaped is right.  */
while|while
condition|(
name|was_escaped
operator|||
name|c
operator|!=
literal|']'
condition|)
block|{
if|if
condition|(
name|c
operator|==
literal|'\0'
condition|)
comment|/* [... (unterminated) loses.  */
return|return
name|FALSE
return|;
name|c
operator|=
name|get_unescaped_char
argument_list|(
operator|&
name|p
argument_list|,
operator|&
name|was_escaped
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|not
condition|)
return|return
name|FALSE
return|;
block|}
break|break;
default|default:
if|if
condition|(
name|c
operator|!=
name|nc
condition|)
return|return
name|FALSE
return|;
block|}
name|component_start
operator|=
operator|(
name|nc
operator|==
name|G_DIR_SEPARATOR
operator|)
expr_stmt|;
block|}
if|if
condition|(
operator|*
name|n
operator|==
literal|'\0'
condition|)
return|return
name|TRUE
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|glob_fnmatch (const gchar * pattern,const gchar * string)
name|glob_fnmatch
parameter_list|(
specifier|const
name|gchar
modifier|*
name|pattern
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|)
block|{
return|return
name|fnmatch_intern
argument_list|(
name|pattern
argument_list|,
name|string
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

end_unit

