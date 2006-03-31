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
file|"gimpargument.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
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
name|GimpProcedure
name|patterns_refresh_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_get_list_proc
specifier|static
name|GimpProcedure
name|patterns_get_list_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_get_pattern_proc
specifier|static
name|GimpProcedure
name|patterns_get_pattern_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_get_pattern_data_proc
specifier|static
name|GimpProcedure
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
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
comment|/*    * patterns_refresh    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|patterns_refresh_proc
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * patterns_get_list    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|patterns_get_list_proc
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"filter"
argument_list|,
literal|"filter"
argument_list|,
literal|"An optional regular expression used to filter the list"
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"num-patterns"
argument_list|,
literal|"num patterns"
argument_list|,
literal|"The number of patterns in the pattern list"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRINGARRAY
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"pattern-list"
argument_list|,
literal|"pattern list"
argument_list|,
literal|"The list of pattern names"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * patterns_get_pattern    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|patterns_get_pattern_proc
argument_list|,
literal|0
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"name"
argument_list|,
literal|"name"
argument_list|,
literal|"The pattern name"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"width"
argument_list|,
literal|"width"
argument_list|,
literal|"The pattern width"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"height"
argument_list|,
literal|"height"
argument_list|,
literal|"The pattern height"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * patterns_get_pattern_data    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|patterns_get_pattern_data_proc
argument_list|,
literal|1
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"name"
argument_list|,
literal|"name"
argument_list|,
literal|"The pattern name (\"\" means currently active pattern)"
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"actual-name"
argument_list|,
literal|"actual name"
argument_list|,
literal|"The pattern name"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"width"
argument_list|,
literal|"width"
argument_list|,
literal|"The pattern width"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"height"
argument_list|,
literal|"height"
argument_list|,
literal|"The pattern height"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"mask-bpp"
argument_list|,
literal|"mask bpp"
argument_list|,
literal|"Pattern bytes per pixel"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"length"
argument_list|,
literal|"length"
argument_list|,
literal|"Length of pattern mask data"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT8ARRAY
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"mask-data"
argument_list|,
literal|"mask data"
argument_list|,
literal|"The pattern mask data"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|patterns_refresh_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|patterns_refresh_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
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
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|patterns_refresh_proc
specifier|static
name|GimpProcedure
name|patterns_refresh_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
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
DECL|function|patterns_get_list_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|patterns_get_list_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
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
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|filter
decl_stmt|;
name|gint32
name|num_patterns
init|=
literal|0
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
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
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
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|num_patterns
argument_list|)
expr_stmt|;
name|g_value_set_pointer
argument_list|(
operator|&
name|return_vals
index|[
literal|2
index|]
operator|.
name|value
argument_list|,
name|pattern_list
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|patterns_get_list_proc
specifier|static
name|GimpProcedure
name|patterns_get_list_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
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
DECL|function|patterns_get_pattern_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|patterns_get_pattern_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
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
name|return_vals
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
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|pattern
argument_list|)
argument_list|)
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
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|g_value_take_string
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|2
index|]
operator|.
name|value
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|3
index|]
operator|.
name|value
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|patterns_get_pattern_proc
specifier|static
name|GimpProcedure
name|patterns_get_pattern_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
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
literal|0
block|,
name|NULL
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
DECL|function|patterns_get_pattern_data_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|patterns_get_pattern_data_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
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
name|return_vals
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
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
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
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|pattern
argument_list|)
argument_list|)
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
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|g_value_take_string
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|actual_name
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|2
index|]
operator|.
name|value
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|3
index|]
operator|.
name|value
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|4
index|]
operator|.
name|value
argument_list|,
name|mask_bpp
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|5
index|]
operator|.
name|value
argument_list|,
name|length
argument_list|)
expr_stmt|;
name|g_value_set_pointer
argument_list|(
operator|&
name|return_vals
index|[
literal|6
index|]
operator|.
name|value
argument_list|,
name|mask_data
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|patterns_get_pattern_data_proc
specifier|static
name|GimpProcedure
name|patterns_get_pattern_data_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
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
name|patterns_get_pattern_data_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

