begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
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
name|HAVE_GLIBC_REGEX
end_ifdef

begin_include
include|#
directive|include
file|<regex.h>
end_include

begin_else
else|#
directive|else
end_else

begin_include
include|#
directive|include
file|"regexrepl/regex.h"
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"procedural-db-query.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|PDB_REGCOMP_FLAGS
define|#
directive|define
name|PDB_REGCOMP_FLAGS
value|REG_ICASE
end_define

begin_define
DECL|macro|COMPAT_BLURB
define|#
directive|define
name|COMPAT_BLURB
value|"This procedure is deprecated! Use '%s' instead."
end_define

begin_typedef
DECL|typedef|PDBQuery
typedef|typedef
name|struct
name|_PDBQuery
name|PDBQuery
typedef|;
end_typedef

begin_struct
DECL|struct|_PDBQuery
struct|struct
name|_PDBQuery
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|name_regex
name|regex_t
name|name_regex
decl_stmt|;
DECL|member|blurb_regex
name|regex_t
name|blurb_regex
decl_stmt|;
DECL|member|help_regex
name|regex_t
name|help_regex
decl_stmt|;
DECL|member|author_regex
name|regex_t
name|author_regex
decl_stmt|;
DECL|member|copyright_regex
name|regex_t
name|copyright_regex
decl_stmt|;
DECL|member|date_regex
name|regex_t
name|date_regex
decl_stmt|;
DECL|member|proc_type_regex
name|regex_t
name|proc_type_regex
decl_stmt|;
DECL|member|list_of_procs
name|gchar
modifier|*
modifier|*
name|list_of_procs
decl_stmt|;
DECL|member|num_procs
name|gint
name|num_procs
decl_stmt|;
DECL|member|querying_compat
name|gboolean
name|querying_compat
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|PDBStrings
typedef|typedef
name|struct
name|_PDBStrings
name|PDBStrings
typedef|;
end_typedef

begin_struct
DECL|struct|_PDBStrings
struct|struct
name|_PDBStrings
block|{
DECL|member|compat
name|gboolean
name|compat
decl_stmt|;
DECL|member|blurb
name|gchar
modifier|*
name|blurb
decl_stmt|;
DECL|member|help
name|gchar
modifier|*
name|help
decl_stmt|;
DECL|member|author
name|gchar
modifier|*
name|author
decl_stmt|;
DECL|member|copyright
name|gchar
modifier|*
name|copyright
decl_stmt|;
DECL|member|date
name|gchar
modifier|*
name|date
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|procedural_db_query_entry
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|procedural_db_print_entry
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|procedural_db_get_strings
parameter_list|(
name|PDBStrings
modifier|*
name|strings
parameter_list|,
name|ProcRecord
modifier|*
name|proc
parameter_list|,
name|gboolean
name|compat
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|procedural_db_dump (Gimp * gimp,const gchar * filename)
name|procedural_db_dump
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|FILE
modifier|*
name|file
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_fopen
argument_list|(
name|filename
argument_list|,
literal|"w"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file
condition|)
return|return
name|FALSE
return|;
name|g_hash_table_foreach
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
name|procedural_db_print_entry
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|procedural_db_query (Gimp * gimp,const gchar * name,const gchar * blurb,const gchar * help,const gchar * author,const gchar * copyright,const gchar * date,const gchar * proc_type,gint * num_procs,gchar *** procs)
name|procedural_db_query
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|,
specifier|const
name|gchar
modifier|*
name|author
parameter_list|,
specifier|const
name|gchar
modifier|*
name|copyright
parameter_list|,
specifier|const
name|gchar
modifier|*
name|date
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_type
parameter_list|,
name|gint
modifier|*
name|num_procs
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|procs
parameter_list|)
block|{
name|PDBQuery
name|pdb_query
decl_stmt|;
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|blurb
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|author
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|copyright
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|date
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_type
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|num_procs
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|procs
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
operator|*
name|num_procs
operator|=
literal|0
expr_stmt|;
operator|*
name|procs
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|regcomp
argument_list|(
operator|&
name|pdb_query
operator|.
name|name_regex
argument_list|,
name|name
argument_list|,
name|PDB_REGCOMP_FLAGS
argument_list|)
condition|)
goto|goto
name|free_name
goto|;
if|if
condition|(
name|regcomp
argument_list|(
operator|&
name|pdb_query
operator|.
name|blurb_regex
argument_list|,
name|blurb
argument_list|,
name|PDB_REGCOMP_FLAGS
argument_list|)
condition|)
goto|goto
name|free_blurb
goto|;
if|if
condition|(
name|regcomp
argument_list|(
operator|&
name|pdb_query
operator|.
name|help_regex
argument_list|,
name|help
argument_list|,
name|PDB_REGCOMP_FLAGS
argument_list|)
condition|)
goto|goto
name|free_help
goto|;
if|if
condition|(
name|regcomp
argument_list|(
operator|&
name|pdb_query
operator|.
name|author_regex
argument_list|,
name|author
argument_list|,
name|PDB_REGCOMP_FLAGS
argument_list|)
condition|)
goto|goto
name|free_author
goto|;
if|if
condition|(
name|regcomp
argument_list|(
operator|&
name|pdb_query
operator|.
name|copyright_regex
argument_list|,
name|copyright
argument_list|,
name|PDB_REGCOMP_FLAGS
argument_list|)
condition|)
goto|goto
name|free_copyright
goto|;
if|if
condition|(
name|regcomp
argument_list|(
operator|&
name|pdb_query
operator|.
name|date_regex
argument_list|,
name|date
argument_list|,
name|PDB_REGCOMP_FLAGS
argument_list|)
condition|)
goto|goto
name|free_date
goto|;
if|if
condition|(
name|regcomp
argument_list|(
operator|&
name|pdb_query
operator|.
name|proc_type_regex
argument_list|,
name|proc_type
argument_list|,
name|PDB_REGCOMP_FLAGS
argument_list|)
condition|)
goto|goto
name|free_proc_type
goto|;
name|success
operator|=
name|TRUE
expr_stmt|;
name|pdb_query
operator|.
name|gimp
operator|=
name|gimp
expr_stmt|;
name|pdb_query
operator|.
name|list_of_procs
operator|=
name|NULL
expr_stmt|;
name|pdb_query
operator|.
name|num_procs
operator|=
literal|0
expr_stmt|;
name|pdb_query
operator|.
name|querying_compat
operator|=
name|FALSE
expr_stmt|;
name|g_hash_table_foreach
argument_list|(
name|gimp
operator|->
name|procedural_ht
argument_list|,
name|procedural_db_query_entry
argument_list|,
operator|&
name|pdb_query
argument_list|)
expr_stmt|;
name|pdb_query
operator|.
name|querying_compat
operator|=
name|TRUE
expr_stmt|;
name|g_hash_table_foreach
argument_list|(
name|gimp
operator|->
name|procedural_compat_ht
argument_list|,
name|procedural_db_query_entry
argument_list|,
operator|&
name|pdb_query
argument_list|)
expr_stmt|;
name|free_proc_type
label|:
name|regfree
argument_list|(
operator|&
name|pdb_query
operator|.
name|proc_type_regex
argument_list|)
expr_stmt|;
name|free_date
label|:
name|regfree
argument_list|(
operator|&
name|pdb_query
operator|.
name|date_regex
argument_list|)
expr_stmt|;
name|free_copyright
label|:
name|regfree
argument_list|(
operator|&
name|pdb_query
operator|.
name|copyright_regex
argument_list|)
expr_stmt|;
name|free_author
label|:
name|regfree
argument_list|(
operator|&
name|pdb_query
operator|.
name|author_regex
argument_list|)
expr_stmt|;
name|free_help
label|:
name|regfree
argument_list|(
operator|&
name|pdb_query
operator|.
name|help_regex
argument_list|)
expr_stmt|;
name|free_blurb
label|:
name|regfree
argument_list|(
operator|&
name|pdb_query
operator|.
name|blurb_regex
argument_list|)
expr_stmt|;
name|free_name
label|:
name|regfree
argument_list|(
operator|&
name|pdb_query
operator|.
name|name_regex
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
operator|*
name|num_procs
operator|=
name|pdb_query
operator|.
name|num_procs
expr_stmt|;
operator|*
name|procs
operator|=
name|pdb_query
operator|.
name|list_of_procs
expr_stmt|;
block|}
return|return
name|success
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|procedural_db_proc_info (Gimp * gimp,const gchar * proc_name,gchar ** blurb,gchar ** help,gchar ** author,gchar ** copyright,gchar ** date,GimpPDBProcType * proc_type,gint * num_args,gint * num_values)
name|procedural_db_proc_info
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
modifier|*
name|date
parameter_list|,
name|GimpPDBProcType
modifier|*
name|proc_type
parameter_list|,
name|gint
modifier|*
name|num_args
parameter_list|,
name|gint
modifier|*
name|num_values
parameter_list|)
block|{
name|ProcRecord
modifier|*
name|proc
decl_stmt|;
name|PDBStrings
name|strings
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc
operator|=
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc
condition|)
block|{
name|procedural_db_get_strings
argument_list|(
operator|&
name|strings
argument_list|,
name|proc
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
specifier|const
name|gchar
modifier|*
name|compat_name
decl_stmt|;
name|compat_name
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp
operator|->
name|procedural_compat_ht
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|compat_name
condition|)
block|{
name|proc
operator|=
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|compat_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc
condition|)
name|procedural_db_get_strings
argument_list|(
operator|&
name|strings
argument_list|,
name|proc
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|proc
condition|)
block|{
operator|*
name|blurb
operator|=
name|strings
operator|.
name|compat
condition|?
name|strings
operator|.
name|blurb
else|:
name|g_strdup
argument_list|(
name|strings
operator|.
name|blurb
argument_list|)
expr_stmt|;
operator|*
name|help
operator|=
name|strings
operator|.
name|compat
condition|?
name|strings
operator|.
name|help
else|:
name|g_strdup
argument_list|(
name|strings
operator|.
name|help
argument_list|)
expr_stmt|;
operator|*
name|author
operator|=
name|strings
operator|.
name|compat
condition|?
name|strings
operator|.
name|author
else|:
name|g_strdup
argument_list|(
name|strings
operator|.
name|author
argument_list|)
expr_stmt|;
operator|*
name|copyright
operator|=
name|strings
operator|.
name|compat
condition|?
name|strings
operator|.
name|copyright
else|:
name|g_strdup
argument_list|(
name|strings
operator|.
name|copyright
argument_list|)
expr_stmt|;
operator|*
name|date
operator|=
name|strings
operator|.
name|compat
condition|?
name|strings
operator|.
name|date
else|:
name|g_strdup
argument_list|(
name|strings
operator|.
name|date
argument_list|)
expr_stmt|;
operator|*
name|proc_type
operator|=
name|proc
operator|->
name|proc_type
expr_stmt|;
operator|*
name|num_args
operator|=
name|proc
operator|->
name|num_args
expr_stmt|;
operator|*
name|num_values
operator|=
name|proc
operator|->
name|num_values
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

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|int
DECL|function|match_strings (regex_t * preg,const gchar * a)
name|match_strings
parameter_list|(
name|regex_t
modifier|*
name|preg
parameter_list|,
specifier|const
name|gchar
modifier|*
name|a
parameter_list|)
block|{
if|if
condition|(
operator|!
name|a
condition|)
name|a
operator|=
literal|""
expr_stmt|;
return|return
name|regexec
argument_list|(
name|preg
argument_list|,
name|a
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|procedural_db_query_entry (gpointer key,gpointer value,gpointer user_data)
name|procedural_db_query_entry
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
name|PDBQuery
modifier|*
name|pdb_query
init|=
name|user_data
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|ProcRecord
modifier|*
name|proc
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|proc_name
decl_stmt|;
name|PDBStrings
name|strings
decl_stmt|;
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GimpEnumDesc
modifier|*
name|type_desc
decl_stmt|;
name|proc_name
operator|=
name|key
expr_stmt|;
if|if
condition|(
name|pdb_query
operator|->
name|querying_compat
condition|)
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|pdb_query
operator|->
name|gimp
operator|->
name|procedural_ht
argument_list|,
name|value
argument_list|)
expr_stmt|;
else|else
name|list
operator|=
name|value
expr_stmt|;
if|if
condition|(
operator|!
name|list
condition|)
return|return;
name|proc
operator|=
operator|(
name|ProcRecord
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|procedural_db_get_strings
argument_list|(
operator|&
name|strings
argument_list|,
name|proc
argument_list|,
name|pdb_query
operator|->
name|querying_compat
argument_list|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_PDB_PROC_TYPE
argument_list|)
expr_stmt|;
name|type_desc
operator|=
name|gimp_enum_get_desc
argument_list|(
name|enum_class
argument_list|,
name|proc
operator|->
name|proc_type
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|enum_class
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|match_strings
argument_list|(
operator|&
name|pdb_query
operator|->
name|name_regex
argument_list|,
name|proc_name
argument_list|)
operator|&&
operator|!
name|match_strings
argument_list|(
operator|&
name|pdb_query
operator|->
name|blurb_regex
argument_list|,
name|strings
operator|.
name|blurb
argument_list|)
operator|&&
operator|!
name|match_strings
argument_list|(
operator|&
name|pdb_query
operator|->
name|help_regex
argument_list|,
name|strings
operator|.
name|help
argument_list|)
operator|&&
operator|!
name|match_strings
argument_list|(
operator|&
name|pdb_query
operator|->
name|author_regex
argument_list|,
name|strings
operator|.
name|author
argument_list|)
operator|&&
operator|!
name|match_strings
argument_list|(
operator|&
name|pdb_query
operator|->
name|copyright_regex
argument_list|,
name|strings
operator|.
name|copyright
argument_list|)
operator|&&
operator|!
name|match_strings
argument_list|(
operator|&
name|pdb_query
operator|->
name|date_regex
argument_list|,
name|strings
operator|.
name|date
argument_list|)
operator|&&
operator|!
name|match_strings
argument_list|(
operator|&
name|pdb_query
operator|->
name|proc_type_regex
argument_list|,
name|type_desc
operator|->
name|value_desc
argument_list|)
condition|)
block|{
name|pdb_query
operator|->
name|num_procs
operator|++
expr_stmt|;
name|pdb_query
operator|->
name|list_of_procs
operator|=
name|g_renew
argument_list|(
name|gchar
operator|*
argument_list|,
name|pdb_query
operator|->
name|list_of_procs
argument_list|,
name|pdb_query
operator|->
name|num_procs
argument_list|)
expr_stmt|;
name|pdb_query
operator|->
name|list_of_procs
index|[
name|pdb_query
operator|->
name|num_procs
operator|-
literal|1
index|]
operator|=
name|g_strdup
argument_list|(
name|proc_name
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|strings
operator|.
name|compat
condition|)
block|{
name|g_free
argument_list|(
name|strings
operator|.
name|blurb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|strings
operator|.
name|help
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|output_string (FILE * file,const gchar * string)
name|output_string
parameter_list|(
name|FILE
modifier|*
name|file
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|)
block|{
if|if
condition|(
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\""
argument_list|)
operator|<
literal|0
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|string
condition|)
while|while
condition|(
operator|*
name|string
condition|)
block|{
switch|switch
condition|(
operator|*
name|string
condition|)
block|{
case|case
literal|'\\'
case|:
if|if
condition|(
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\\\\"
argument_list|)
operator|<
literal|0
condition|)
return|return
name|FALSE
return|;
break|break;
case|case
literal|'\"'
case|:
if|if
condition|(
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\\\""
argument_list|)
operator|<
literal|0
condition|)
return|return
name|FALSE
return|;
break|break;
case|case
literal|'{'
case|:
if|if
condition|(
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"@{"
argument_list|)
operator|<
literal|0
condition|)
return|return
name|FALSE
return|;
break|break;
case|case
literal|'@'
case|:
if|if
condition|(
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"@@"
argument_list|)
operator|<
literal|0
condition|)
return|return
name|FALSE
return|;
break|break;
case|case
literal|'}'
case|:
if|if
condition|(
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"@}"
argument_list|)
operator|<
literal|0
condition|)
return|return
name|FALSE
return|;
break|break;
default|default:
if|if
condition|(
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"%c"
argument_list|,
operator|*
name|string
argument_list|)
operator|<
literal|0
condition|)
return|return
name|FALSE
return|;
block|}
name|string
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\"\n"
argument_list|)
operator|<
literal|0
condition|)
return|return
name|FALSE
return|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|procedural_db_print_entry (gpointer key,gpointer value,gpointer user_data)
name|procedural_db_print_entry
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
name|FILE
modifier|*
name|file
init|=
name|user_data
decl_stmt|;
name|GEnumClass
modifier|*
name|arg_class
decl_stmt|;
name|GEnumClass
modifier|*
name|proc_class
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GString
modifier|*
name|buf
decl_stmt|;
name|gint
name|num
init|=
literal|0
decl_stmt|;
name|arg_class
operator|=
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_PDB_ARG_TYPE
argument_list|)
expr_stmt|;
name|proc_class
operator|=
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_PDB_PROC_TYPE
argument_list|)
expr_stmt|;
name|buf
operator|=
name|g_string_new
argument_list|(
literal|""
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
operator|(
name|GList
operator|*
operator|)
name|value
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
name|ProcRecord
modifier|*
name|procedure
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GEnumValue
modifier|*
name|arg_value
decl_stmt|;
name|GimpEnumDesc
modifier|*
name|type_desc
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|num
operator|++
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\n(register-procedure "
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|||
name|num
operator|!=
literal|1
condition|)
block|{
name|g_string_printf
argument_list|(
name|buf
argument_list|,
literal|"%s<%d>"
argument_list|,
name|procedure
operator|->
name|name
argument_list|,
name|num
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|buf
operator|->
name|str
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|output_string
argument_list|(
name|file
argument_list|,
name|procedure
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
name|type_desc
operator|=
name|gimp_enum_get_desc
argument_list|(
name|proc_class
argument_list|,
name|procedure
operator|->
name|proc_type
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|procedure
operator|->
name|blurb
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|procedure
operator|->
name|help
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|procedure
operator|->
name|author
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|procedure
operator|->
name|copyright
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|procedure
operator|->
name|date
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|type_desc
operator|->
name|value_desc
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"( "
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|procedure
operator|->
name|num_args
condition|;
name|i
operator|++
control|)
block|{
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"( "
argument_list|)
expr_stmt|;
name|arg_value
operator|=
name|g_enum_get_value
argument_list|(
name|arg_class
argument_list|,
name|procedure
operator|->
name|args
index|[
name|i
index|]
operator|.
name|type
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|g_param_spec_get_name
argument_list|(
name|procedure
operator|->
name|args
index|[
name|i
index|]
operator|.
name|pspec
argument_list|)
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|arg_value
operator|->
name|value_name
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|g_param_spec_get_blurb
argument_list|(
name|procedure
operator|->
name|args
index|[
name|i
index|]
operator|.
name|pspec
argument_list|)
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|" ) "
argument_list|)
expr_stmt|;
block|}
name|fprintf
argument_list|(
name|file
argument_list|,
literal|" ) "
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"( "
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|procedure
operator|->
name|num_values
condition|;
name|i
operator|++
control|)
block|{
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"( "
argument_list|)
expr_stmt|;
name|arg_value
operator|=
name|g_enum_get_value
argument_list|(
name|arg_class
argument_list|,
name|procedure
operator|->
name|values
index|[
name|i
index|]
operator|.
name|type
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|g_param_spec_get_name
argument_list|(
name|procedure
operator|->
name|values
index|[
name|i
index|]
operator|.
name|pspec
argument_list|)
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|arg_value
operator|->
name|value_name
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|g_param_spec_get_blurb
argument_list|(
name|procedure
operator|->
name|values
index|[
name|i
index|]
operator|.
name|pspec
argument_list|)
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|" ) "
argument_list|)
expr_stmt|;
block|}
name|fprintf
argument_list|(
name|file
argument_list|,
literal|" ) "
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|" ) "
argument_list|)
expr_stmt|;
block|}
name|g_string_free
argument_list|(
name|buf
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|arg_class
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|proc_class
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|procedural_db_get_strings (PDBStrings * strings,ProcRecord * proc,gboolean compat)
name|procedural_db_get_strings
parameter_list|(
name|PDBStrings
modifier|*
name|strings
parameter_list|,
name|ProcRecord
modifier|*
name|proc
parameter_list|,
name|gboolean
name|compat
parameter_list|)
block|{
name|strings
operator|->
name|compat
operator|=
name|compat
expr_stmt|;
if|if
condition|(
name|compat
condition|)
block|{
name|strings
operator|->
name|blurb
operator|=
name|g_strdup_printf
argument_list|(
name|COMPAT_BLURB
argument_list|,
name|proc
operator|->
name|name
argument_list|)
expr_stmt|;
name|strings
operator|->
name|help
operator|=
name|g_strdup
argument_list|(
name|strings
operator|->
name|blurb
argument_list|)
expr_stmt|;
name|strings
operator|->
name|author
operator|=
name|NULL
expr_stmt|;
name|strings
operator|->
name|copyright
operator|=
name|NULL
expr_stmt|;
name|strings
operator|->
name|date
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|strings
operator|->
name|blurb
operator|=
name|proc
operator|->
name|blurb
expr_stmt|;
name|strings
operator|->
name|help
operator|=
name|proc
operator|->
name|help
expr_stmt|;
name|strings
operator|->
name|author
operator|=
name|proc
operator|->
name|author
expr_stmt|;
name|strings
operator|->
name|copyright
operator|=
name|proc
operator|->
name|copyright
expr_stmt|;
name|strings
operator|->
name|date
operator|=
name|proc
operator|->
name|date
expr_stmt|;
block|}
block|}
end_function

end_unit

