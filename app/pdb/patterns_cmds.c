begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
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
file|"core/gimpcontainer-filter.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppattern.h"
end_include

begin_decl_stmt
DECL|variable|patterns_refresh_proc
specifier|static
name|ProcRecord
name|patterns_refresh_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_get_list_proc
specifier|static
name|ProcRecord
name|patterns_get_list_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_get_pattern_proc
specifier|static
name|ProcRecord
name|patterns_get_pattern_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_get_pattern_data_proc
specifier|static
name|ProcRecord
name|patterns_get_pattern_data_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_patterns_procs (Gimp * gimp)
name|register_patterns_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|patterns_refresh_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|patterns_get_list_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|patterns_get_pattern_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|patterns_get_pattern_data_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|patterns_refresh_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|patterns_refresh_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gimp_data_factory_data_refresh
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|patterns_refresh_proc
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|patterns_refresh_proc
specifier|static
name|ProcRecord
name|patterns_refresh_proc
init|=
block|{
literal|"gimp-patterns-refresh"
block|,
literal|"gimp-patterns-refresh"
block|,
literal|"Refresh current patterns. This function always succeeds."
block|,
literal|"This procedure retrieves all patterns currently in the user's pattern path and updates all pattern dialogs accordingly."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer"
block|,
literal|"2002"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|patterns_refresh_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|patterns_get_list_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|patterns_get_list_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gchar
modifier|*
name|filter
decl_stmt|;
name|gint32
name|num_patterns
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|pattern_list
init|=
name|NULL
decl_stmt|;
name|filter
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|filter
operator|&&
operator|!
name|g_utf8_validate
argument_list|(
name|filter
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|pattern_list
operator|=
name|gimp_container_get_filtered_name_array
argument_list|(
name|gimp
operator|->
name|pattern_factory
operator|->
name|container
argument_list|,
name|filter
argument_list|,
operator|&
name|num_patterns
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|patterns_get_list_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|num_patterns
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|pattern_list
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|patterns_get_list_inargs
specifier|static
name|ProcArg
name|patterns_get_list_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"filter"
block|,
literal|"An optional regular expression used to filter the list"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_get_list_outargs
specifier|static
name|ProcArg
name|patterns_get_list_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"num-patterns"
block|,
literal|"The number of patterns in the pattern list"
block|}
block|,
block|{
name|GIMP_PDB_STRINGARRAY
block|,
literal|"pattern-list"
block|,
literal|"The list of pattern names"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_get_list_proc
specifier|static
name|ProcRecord
name|patterns_get_list_proc
init|=
block|{
literal|"gimp-patterns-get-list"
block|,
literal|"gimp-patterns-get-list"
block|,
literal|"Retrieve a complete listing of the available patterns."
block|,
literal|"This procedure returns a complete listing of available GIMP patterns. Each name returned can be used as input to the 'gimp-context-set-pattern'."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|patterns_get_list_inargs
block|,
literal|2
block|,
name|patterns_get_list_outargs
block|,
block|{
block|{
name|patterns_get_list_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|patterns_get_pattern_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|patterns_get_pattern_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|gint32
name|width
init|=
literal|0
decl_stmt|;
name|gint32
name|height
init|=
literal|0
decl_stmt|;
name|GimpPattern
modifier|*
name|pattern
init|=
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
decl_stmt|;
if|if
condition|(
name|pattern
condition|)
block|{
name|name
operator|=
name|g_strdup
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|pattern
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|width
operator|=
name|pattern
operator|->
name|mask
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|pattern
operator|->
name|mask
operator|->
name|height
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|patterns_get_pattern_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|name
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|width
expr_stmt|;
name|return_args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|height
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|patterns_get_pattern_outargs
specifier|static
name|ProcArg
name|patterns_get_pattern_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"name"
block|,
literal|"The pattern name"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"width"
block|,
literal|"The pattern width"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"height"
block|,
literal|"The pattern height"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_get_pattern_proc
specifier|static
name|ProcRecord
name|patterns_get_pattern_proc
init|=
block|{
literal|"gimp-patterns-get-pattern"
block|,
literal|"gimp-patterns-get-pattern"
block|,
literal|"This procedure is deprecated! Use 'gimp-context-get-pattern' instead."
block|,
literal|"This procedure is deprecated! Use 'gimp-context-get-pattern' instead."
block|,
literal|""
block|,
literal|""
block|,
literal|""
block|,
literal|"gimp-context-get-pattern"
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|3
block|,
name|patterns_get_pattern_outargs
block|,
block|{
block|{
name|patterns_get_pattern_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|patterns_get_pattern_data_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|patterns_get_pattern_data_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
modifier|*
name|actual_name
init|=
name|NULL
decl_stmt|;
name|gint32
name|width
init|=
literal|0
decl_stmt|;
name|gint32
name|height
init|=
literal|0
decl_stmt|;
name|gint32
name|mask_bpp
init|=
literal|0
decl_stmt|;
name|gint32
name|length
init|=
literal|0
decl_stmt|;
name|guint8
modifier|*
name|mask_data
init|=
name|NULL
decl_stmt|;
name|name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|name
operator|&&
operator|!
name|g_utf8_validate
argument_list|(
name|name
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
if|if
condition|(
name|name
operator|&&
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
block|{
name|pattern
operator|=
operator|(
name|GimpPattern
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|pattern_factory
operator|->
name|container
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|pattern
operator|=
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|pattern
condition|)
block|{
name|actual_name
operator|=
name|g_strdup
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|pattern
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|width
operator|=
name|pattern
operator|->
name|mask
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|pattern
operator|->
name|mask
operator|->
name|height
expr_stmt|;
name|mask_bpp
operator|=
name|pattern
operator|->
name|mask
operator|->
name|bytes
expr_stmt|;
name|length
operator|=
name|pattern
operator|->
name|mask
operator|->
name|height
operator|*
name|pattern
operator|->
name|mask
operator|->
name|width
operator|*
name|pattern
operator|->
name|mask
operator|->
name|bytes
expr_stmt|;
name|mask_data
operator|=
name|g_memdup
argument_list|(
name|temp_buf_data
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
argument_list|,
name|length
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|patterns_get_pattern_data_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|actual_name
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|width
expr_stmt|;
name|return_args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|height
expr_stmt|;
name|return_args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|mask_bpp
expr_stmt|;
name|return_args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|length
expr_stmt|;
name|return_args
index|[
literal|6
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|mask_data
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|patterns_get_pattern_data_inargs
specifier|static
name|ProcArg
name|patterns_get_pattern_data_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"name"
block|,
literal|"The pattern name (\"\" means currently active pattern)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_get_pattern_data_outargs
specifier|static
name|ProcArg
name|patterns_get_pattern_data_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"actual-name"
block|,
literal|"The pattern name"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"width"
block|,
literal|"The pattern width"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"height"
block|,
literal|"The pattern height"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"mask-bpp"
block|,
literal|"Pattern bytes per pixel"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"length"
block|,
literal|"Length of pattern mask data"
block|}
block|,
block|{
name|GIMP_PDB_INT8ARRAY
block|,
literal|"mask-data"
block|,
literal|"The pattern mask data"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_get_pattern_data_proc
specifier|static
name|ProcRecord
name|patterns_get_pattern_data_proc
init|=
block|{
literal|"gimp-patterns-get-pattern-data"
block|,
literal|"gimp-patterns-get-pattern-data"
block|,
literal|"This procedure is deprecated! Use 'gimp-pattern-get-pixels' instead."
block|,
literal|"This procedure is deprecated! Use 'gimp-pattern-get-pixels' instead."
block|,
literal|""
block|,
literal|""
block|,
literal|""
block|,
literal|"gimp-pattern-get-pixels"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|patterns_get_pattern_data_inargs
block|,
literal|6
block|,
name|patterns_get_pattern_data_outargs
block|,
block|{
block|{
name|patterns_get_pattern_data_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

