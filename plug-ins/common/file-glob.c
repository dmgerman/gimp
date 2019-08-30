begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"file-glob"
end_define

begin_typedef
DECL|typedef|Glob
typedef|typedef
name|struct
name|_Glob
name|Glob
typedef|;
end_typedef

begin_typedef
DECL|typedef|GlobClass
typedef|typedef
name|struct
name|_GlobClass
name|GlobClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Glob
struct|struct
name|_Glob
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GlobClass
struct|struct
name|_GlobClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GLOB_TYPE
define|#
directive|define
name|GLOB_TYPE
value|(glob_get_type ())
end_define

begin_define
DECL|macro|GLOB
define|#
directive|define
name|GLOB
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GLOB_TYPE, Glob))
end_define

begin_decl_stmt
name|GType
name|glob_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|GList
modifier|*
name|glob_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpProcedure
modifier|*
name|glob_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|glob_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
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
name|gboolean
name|filename_encoding
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

begin_macro
DECL|function|G_DEFINE_TYPE (Glob,glob,GIMP_TYPE_PLUG_IN)
name|G_DEFINE_TYPE
argument_list|(
argument|Glob
argument_list|,
argument|glob
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|GLOB_TYPE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|glob_class_init
parameter_list|(
name|GlobClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPlugInClass
modifier|*
name|plug_in_class
init|=
name|GIMP_PLUG_IN_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|plug_in_class
operator|->
name|query_procedures
operator|=
name|glob_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|glob_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|glob_init (Glob * glob)
name|glob_init
parameter_list|(
name|Glob
modifier|*
name|glob
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|glob_query_procedures (GimpPlugIn * plug_in)
name|glob_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
return|return
name|g_list_append
argument_list|(
name|NULL
argument_list|,
name|g_strdup
argument_list|(
name|PLUG_IN_PROC
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProcedure
modifier|*
DECL|function|glob_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|glob_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|PLUG_IN_PROC
argument_list|)
condition|)
block|{
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|name
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|glob_run
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Returns a list of matching filenames"
argument_list|,
literal|"This can be useful in scripts and "
literal|"other plug-ins (e.g., "
literal|"batch-conversion). See the glob(7) "
literal|"manpage for more info. Note however "
literal|"that this isn't a full-featured glob "
literal|"implementation. It only handles "
literal|"simple patterns like "
literal|"\"/home/foo/bar/*.jpg\"."
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"2004"
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_STRING
argument_list|(
name|procedure
argument_list|,
literal|"pattern"
argument_list|,
literal|"Pattern"
argument_list|,
literal|"The glob pattern (in UTF-8 encoding)"
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_BOOLEAN
argument_list|(
name|procedure
argument_list|,
literal|"filename-encoding"
argument_list|,
literal|"Filename encoding"
argument_list|,
literal|"FALSE to return UTF-8 strings, TRUE to return "
literal|"strings in filename encoding"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_VAL_INT
argument_list|(
name|procedure
argument_list|,
literal|"num-files"
argument_list|,
literal|"Num files"
argument_list|,
literal|"Number of returned filenames"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_VAL_STRING_ARRAY
argument_list|(
name|procedure
argument_list|,
literal|"files"
argument_list|,
literal|"Files"
argument_list|,
literal|"The list of matching filenames"
argument_list|,
name|G_PARAM_READWRITE
operator||
name|GIMP_PARAM_NO_VALIDATE
argument_list|)
expr_stmt|;
block|}
return|return
name|procedure
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|glob_run (GimpProcedure * procedure,const GimpValueArray * args,gpointer run_data)
name|glob_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|pattern
decl_stmt|;
name|gboolean
name|filename_encoding
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|matches
decl_stmt|;
name|gint
name|num_matches
decl_stmt|;
name|pattern
operator|=
name|GIMP_VALUES_GET_STRING
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|filename_encoding
operator|=
name|GIMP_VALUES_GET_BOOLEAN
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|glob_match
argument_list|(
name|pattern
argument_list|,
name|filename_encoding
argument_list|,
operator|&
name|num_matches
argument_list|,
operator|&
name|matches
argument_list|)
condition|)
block|{
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_EXECUTION_ERROR
argument_list|,
name|NULL
argument_list|)
return|;
block|}
name|return_vals
operator|=
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_SUCCESS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_VALUES_SET_INT
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|,
name|num_matches
argument_list|)
expr_stmt|;
name|GIMP_VALUES_TAKE_STRING_ARRAY
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|,
name|matches
argument_list|,
name|num_matches
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|glob_match (const gchar * pattern,gboolean filename_encoding,gint * num_matches,gchar *** matches)
name|glob_match
parameter_list|(
specifier|const
name|gchar
modifier|*
name|pattern
parameter_list|,
name|gboolean
name|filename_encoding
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
name|path
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
if|if
condition|(
name|dirname
condition|)
name|path
operator|=
name|g_build_filename
argument_list|(
name|dirname
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|path
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
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
block|{
if|if
condition|(
name|filename_encoding
condition|)
block|{
name|g_ptr_array_add
argument_list|(
name|array
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|path
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|g_ptr_array_add
argument_list|(
name|array
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|name
operator|=
name|NULL
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
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
comment|/* If the pattern ends with wildcards, we have a              * guaranteed match unless there is a dir separator              * in the remainder of the string.              */
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
specifier|static
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

