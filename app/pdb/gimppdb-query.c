begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpparamspecs-desc.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb-query.h"
end_include

begin_include
include|#
directive|include
file|"gimppdberror.h"
end_include

begin_include
include|#
directive|include
file|"gimp-pdb-compat.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|PDB_REGEX_FLAGS
define|#
directive|define
name|PDB_REGEX_FLAGS
value|(G_REGEX_CASELESS | G_REGEX_OPTIMIZE)
end_define

begin_define
DECL|macro|COMPAT_BLURB
define|#
directive|define
name|COMPAT_BLURB
value|"This procedure is deprecated! Use '%s' instead."
end_define

begin_typedef
DECL|typedef|PDBDump
typedef|typedef
name|struct
name|_PDBDump
name|PDBDump
typedef|;
end_typedef

begin_struct
DECL|struct|_PDBDump
struct|struct
name|_PDBDump
block|{
DECL|member|pdb
name|GimpPDB
modifier|*
name|pdb
decl_stmt|;
DECL|member|file
name|FILE
modifier|*
name|file
decl_stmt|;
DECL|member|dumping_compat
name|gboolean
name|dumping_compat
decl_stmt|;
block|}
struct|;
end_struct

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
DECL|member|pdb
name|GimpPDB
modifier|*
name|pdb
decl_stmt|;
DECL|member|name_regex
name|GRegex
modifier|*
name|name_regex
decl_stmt|;
DECL|member|blurb_regex
name|GRegex
modifier|*
name|blurb_regex
decl_stmt|;
DECL|member|help_regex
name|GRegex
modifier|*
name|help_regex
decl_stmt|;
DECL|member|author_regex
name|GRegex
modifier|*
name|author_regex
decl_stmt|;
DECL|member|copyright_regex
name|GRegex
modifier|*
name|copyright_regex
decl_stmt|;
DECL|member|date_regex
name|GRegex
modifier|*
name|date_regex
decl_stmt|;
DECL|member|proc_type_regex
name|GRegex
modifier|*
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
name|gimp_pdb_query_entry
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
name|gimp_pdb_print_entry
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
name|gimp_pdb_get_strings
parameter_list|(
name|PDBStrings
modifier|*
name|strings
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gboolean
name|compat
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_free_strings
parameter_list|(
name|PDBStrings
modifier|*
name|strings
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_pdb_dump (GimpPDB * pdb,const gchar * filename)
name|gimp_pdb_dump
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|PDBDump
name|pdb_dump
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
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
name|pdb_dump
operator|.
name|pdb
operator|=
name|pdb
expr_stmt|;
name|pdb_dump
operator|.
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
name|pdb_dump
operator|.
name|file
condition|)
return|return
name|FALSE
return|;
name|pdb_dump
operator|.
name|dumping_compat
operator|=
name|FALSE
expr_stmt|;
name|g_hash_table_foreach
argument_list|(
name|pdb
operator|->
name|procedures
argument_list|,
name|gimp_pdb_print_entry
argument_list|,
operator|&
name|pdb_dump
argument_list|)
expr_stmt|;
name|pdb_dump
operator|.
name|dumping_compat
operator|=
name|TRUE
expr_stmt|;
name|g_hash_table_foreach
argument_list|(
name|pdb
operator|->
name|compat_proc_names
argument_list|,
name|gimp_pdb_print_entry
argument_list|,
operator|&
name|pdb_dump
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|pdb_dump
operator|.
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
DECL|function|gimp_pdb_query (GimpPDB * pdb,const gchar * name,const gchar * blurb,const gchar * help,const gchar * author,const gchar * copyright,const gchar * date,const gchar * proc_type,gint * num_procs,gchar *** procs,GError ** error)
name|gimp_pdb_query
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|PDBQuery
name|pdb_query
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
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
name|pdb_query
operator|.
name|name_regex
operator|=
name|g_regex_new
argument_list|(
name|name
argument_list|,
name|PDB_REGEX_FLAGS
argument_list|,
literal|0
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pdb_query
operator|.
name|name_regex
condition|)
goto|goto
name|cleanup
goto|;
name|pdb_query
operator|.
name|blurb_regex
operator|=
name|g_regex_new
argument_list|(
name|blurb
argument_list|,
name|PDB_REGEX_FLAGS
argument_list|,
literal|0
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pdb_query
operator|.
name|blurb_regex
condition|)
goto|goto
name|cleanup
goto|;
name|pdb_query
operator|.
name|help_regex
operator|=
name|g_regex_new
argument_list|(
name|help
argument_list|,
name|PDB_REGEX_FLAGS
argument_list|,
literal|0
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pdb_query
operator|.
name|help_regex
condition|)
goto|goto
name|cleanup
goto|;
name|pdb_query
operator|.
name|author_regex
operator|=
name|g_regex_new
argument_list|(
name|author
argument_list|,
name|PDB_REGEX_FLAGS
argument_list|,
literal|0
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pdb_query
operator|.
name|author_regex
condition|)
goto|goto
name|cleanup
goto|;
name|pdb_query
operator|.
name|copyright_regex
operator|=
name|g_regex_new
argument_list|(
name|copyright
argument_list|,
name|PDB_REGEX_FLAGS
argument_list|,
literal|0
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pdb_query
operator|.
name|copyright_regex
condition|)
goto|goto
name|cleanup
goto|;
name|pdb_query
operator|.
name|date_regex
operator|=
name|g_regex_new
argument_list|(
name|date
argument_list|,
name|PDB_REGEX_FLAGS
argument_list|,
literal|0
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pdb_query
operator|.
name|date_regex
condition|)
goto|goto
name|cleanup
goto|;
name|pdb_query
operator|.
name|proc_type_regex
operator|=
name|g_regex_new
argument_list|(
name|proc_type
argument_list|,
name|PDB_REGEX_FLAGS
argument_list|,
literal|0
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pdb_query
operator|.
name|proc_type_regex
condition|)
goto|goto
name|cleanup
goto|;
name|success
operator|=
name|TRUE
expr_stmt|;
name|pdb_query
operator|.
name|pdb
operator|=
name|pdb
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
name|pdb
operator|->
name|procedures
argument_list|,
name|gimp_pdb_query_entry
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
name|pdb
operator|->
name|compat_proc_names
argument_list|,
name|gimp_pdb_query_entry
argument_list|,
operator|&
name|pdb_query
argument_list|)
expr_stmt|;
name|cleanup
label|:
if|if
condition|(
name|pdb_query
operator|.
name|proc_type_regex
condition|)
name|g_regex_unref
argument_list|(
name|pdb_query
operator|.
name|proc_type_regex
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb_query
operator|.
name|date_regex
condition|)
name|g_regex_unref
argument_list|(
name|pdb_query
operator|.
name|date_regex
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb_query
operator|.
name|copyright_regex
condition|)
name|g_regex_unref
argument_list|(
name|pdb_query
operator|.
name|copyright_regex
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb_query
operator|.
name|author_regex
condition|)
name|g_regex_unref
argument_list|(
name|pdb_query
operator|.
name|author_regex
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb_query
operator|.
name|help_regex
condition|)
name|g_regex_unref
argument_list|(
name|pdb_query
operator|.
name|help_regex
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb_query
operator|.
name|blurb_regex
condition|)
name|g_regex_unref
argument_list|(
name|pdb_query
operator|.
name|blurb_regex
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb_query
operator|.
name|name_regex
condition|)
name|g_regex_unref
argument_list|(
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
DECL|function|gimp_pdb_proc_info (GimpPDB * pdb,const gchar * proc_name,gchar ** blurb,gchar ** help,gchar ** author,gchar ** copyright,gchar ** date,GimpPDBProcType * proc_type,gint * num_args,gint * num_values,GError ** error)
name|gimp_pdb_proc_info
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|PDBStrings
name|strings
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
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
name|FALSE
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|gimp_pdb_lookup_procedure
argument_list|(
name|pdb
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
condition|)
block|{
name|gimp_pdb_get_strings
argument_list|(
operator|&
name|strings
argument_list|,
name|procedure
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
name|gimp_pdb_lookup_compat_proc_name
argument_list|(
name|pdb
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|compat_name
condition|)
block|{
name|procedure
operator|=
name|gimp_pdb_lookup_procedure
argument_list|(
name|pdb
argument_list|,
name|compat_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
condition|)
name|gimp_pdb_get_strings
argument_list|(
operator|&
name|strings
argument_list|,
name|procedure
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|procedure
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
name|procedure
operator|->
name|proc_type
expr_stmt|;
operator|*
name|num_args
operator|=
name|procedure
operator|->
name|num_args
expr_stmt|;
operator|*
name|num_values
operator|=
name|procedure
operator|->
name|num_values
expr_stmt|;
return|return
name|TRUE
return|;
block|}
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
argument_list|,
name|_
argument_list|(
literal|"Procedure '%s' not found"
argument_list|)
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
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
name|gboolean
DECL|function|match_string (GRegex * regex,const gchar * string)
name|match_string
parameter_list|(
name|GRegex
modifier|*
name|regex
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|)
block|{
if|if
condition|(
operator|!
name|string
condition|)
name|string
operator|=
literal|""
expr_stmt|;
return|return
name|g_regex_match
argument_list|(
name|regex
argument_list|,
name|string
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_query_entry (gpointer key,gpointer value,gpointer user_data)
name|gimp_pdb_query_entry
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
name|GimpProcedure
modifier|*
name|procedure
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
name|pdb
operator|->
name|procedures
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
name|procedure
operator|=
name|list
operator|->
name|data
expr_stmt|;
name|gimp_pdb_get_strings
argument_list|(
operator|&
name|strings
argument_list|,
name|procedure
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
name|procedure
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
name|match_string
argument_list|(
name|pdb_query
operator|->
name|name_regex
argument_list|,
name|proc_name
argument_list|)
operator|&&
name|match_string
argument_list|(
name|pdb_query
operator|->
name|blurb_regex
argument_list|,
name|strings
operator|.
name|blurb
argument_list|)
operator|&&
name|match_string
argument_list|(
name|pdb_query
operator|->
name|help_regex
argument_list|,
name|strings
operator|.
name|help
argument_list|)
operator|&&
name|match_string
argument_list|(
name|pdb_query
operator|->
name|author_regex
argument_list|,
name|strings
operator|.
name|author
argument_list|)
operator|&&
name|match_string
argument_list|(
name|pdb_query
operator|->
name|copyright_regex
argument_list|,
name|strings
operator|.
name|copyright
argument_list|)
operator|&&
name|match_string
argument_list|(
name|pdb_query
operator|->
name|date_regex
argument_list|,
name|strings
operator|.
name|date
argument_list|)
operator|&&
name|match_string
argument_list|(
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
name|gimp_pdb_free_strings
argument_list|(
operator|&
name|strings
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* #define DEBUG_OUTPUT 1 */
end_comment

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
ifndef|#
directive|ifndef
name|DEBUG_OUTPUT
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
endif|#
directive|endif
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
ifndef|#
directive|ifndef
name|DEBUG_OUTPUT
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
endif|#
directive|endif
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_print_entry (gpointer key,gpointer value,gpointer user_data)
name|gimp_pdb_print_entry
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
name|PDBDump
modifier|*
name|pdb_dump
init|=
name|user_data
decl_stmt|;
name|FILE
modifier|*
name|file
init|=
name|pdb_dump
operator|->
name|file
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|proc_name
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GEnumClass
modifier|*
name|arg_class
decl_stmt|;
name|GEnumClass
modifier|*
name|proc_class
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
name|proc_name
operator|=
name|key
expr_stmt|;
if|if
condition|(
name|pdb_dump
operator|->
name|dumping_compat
condition|)
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|pdb_dump
operator|->
name|pdb
operator|->
name|procedures
argument_list|,
name|value
argument_list|)
expr_stmt|;
else|else
name|list
operator|=
name|value
expr_stmt|;
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
name|GimpProcedure
modifier|*
name|procedure
init|=
name|list
operator|->
name|data
decl_stmt|;
name|PDBStrings
name|strings
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
name|gimp_pdb_get_strings
argument_list|(
operator|&
name|strings
argument_list|,
name|procedure
argument_list|,
name|pdb_dump
operator|->
name|dumping_compat
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG_OUTPUT
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"("
argument_list|)
expr_stmt|;
else|#
directive|else
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"(register-procedure "
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
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
name|proc_name
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
name|proc_name
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
ifdef|#
directive|ifdef
name|DEBUG_OUTPUT
name|fprintf
argument_list|(
name|file
argument_list|,
literal|" ("
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
name|GParamSpec
modifier|*
name|pspec
init|=
name|procedure
operator|->
name|args
index|[
name|i
index|]
decl_stmt|;
name|GimpPDBArgType
name|arg_type
decl_stmt|;
name|arg_type
operator|=
name|gimp_pdb_compat_arg_type_from_gtype
argument_list|(
name|pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|arg_value
operator|=
name|g_enum_get_value
argument_list|(
name|arg_class
argument_list|,
name|arg_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|>
literal|0
condition|)
name|fprintf
argument_list|(
name|file
argument_list|,
literal|" "
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
block|}
name|fprintf
argument_list|(
name|file
argument_list|,
literal|") ("
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
name|GParamSpec
modifier|*
name|pspec
init|=
name|procedure
operator|->
name|values
index|[
name|i
index|]
decl_stmt|;
name|GimpPDBArgType
name|arg_type
decl_stmt|;
name|arg_type
operator|=
name|gimp_pdb_compat_arg_type_from_gtype
argument_list|(
name|pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|arg_value
operator|=
name|g_enum_get_value
argument_list|(
name|arg_class
argument_list|,
name|arg_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|>
literal|0
condition|)
name|fprintf
argument_list|(
name|file
argument_list|,
literal|" "
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
block|}
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"))\n"
argument_list|)
expr_stmt|;
else|#
directive|else
comment|/* ! DEBUG_OUTPUT */
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"  "
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|strings
operator|.
name|blurb
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"  "
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|strings
operator|.
name|help
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"  "
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|strings
operator|.
name|author
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"  "
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|strings
operator|.
name|copyright
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"  "
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|strings
operator|.
name|date
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"  "
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
literal|"  ("
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
name|GParamSpec
modifier|*
name|pspec
init|=
name|procedure
operator|->
name|args
index|[
name|i
index|]
decl_stmt|;
name|GimpPDBArgType
name|arg_type
decl_stmt|;
name|gchar
modifier|*
name|desc
init|=
name|gimp_param_spec_get_desc
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\n    (\n"
argument_list|)
expr_stmt|;
name|arg_type
operator|=
name|gimp_pdb_compat_arg_type_from_gtype
argument_list|(
name|pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|arg_value
operator|=
name|g_enum_get_value
argument_list|(
name|arg_class
argument_list|,
name|arg_type
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"      "
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|g_param_spec_get_name
argument_list|(
name|pspec
argument_list|)
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"      "
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
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"      "
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"    )"
argument_list|)
expr_stmt|;
block|}
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\n  )\n"
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"  ("
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
name|GParamSpec
modifier|*
name|pspec
init|=
name|procedure
operator|->
name|values
index|[
name|i
index|]
decl_stmt|;
name|GimpPDBArgType
name|arg_type
decl_stmt|;
name|gchar
modifier|*
name|desc
init|=
name|gimp_param_spec_get_desc
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\n    (\n"
argument_list|)
expr_stmt|;
name|arg_type
operator|=
name|gimp_pdb_compat_arg_type_from_gtype
argument_list|(
name|pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|arg_value
operator|=
name|g_enum_get_value
argument_list|(
name|arg_class
argument_list|,
name|arg_type
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"      "
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|g_param_spec_get_name
argument_list|(
name|pspec
argument_list|)
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"      "
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
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"      "
argument_list|)
expr_stmt|;
name|output_string
argument_list|(
name|file
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"    )"
argument_list|)
expr_stmt|;
block|}
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\n  )"
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\n)\n"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG_OUTPUT */
name|gimp_pdb_free_strings
argument_list|(
operator|&
name|strings
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
DECL|function|gimp_pdb_get_strings (PDBStrings * strings,GimpProcedure * procedure,gboolean compat)
name|gimp_pdb_get_strings
parameter_list|(
name|PDBStrings
modifier|*
name|strings
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
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
name|gimp_object_get_name
argument_list|(
name|procedure
argument_list|)
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
name|procedure
operator|->
name|blurb
expr_stmt|;
name|strings
operator|->
name|help
operator|=
name|procedure
operator|->
name|help
expr_stmt|;
name|strings
operator|->
name|author
operator|=
name|procedure
operator|->
name|author
expr_stmt|;
name|strings
operator|->
name|copyright
operator|=
name|procedure
operator|->
name|copyright
expr_stmt|;
name|strings
operator|->
name|date
operator|=
name|procedure
operator|->
name|date
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_free_strings (PDBStrings * strings)
name|gimp_pdb_free_strings
parameter_list|(
name|PDBStrings
modifier|*
name|strings
parameter_list|)
block|{
if|if
condition|(
name|strings
operator|->
name|compat
condition|)
block|{
name|g_free
argument_list|(
name|strings
operator|->
name|blurb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|strings
operator|->
name|help
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

