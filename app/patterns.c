begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_include
include|#
directive|include
file|<dirent.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"colormaps.h"
end_include

begin_include
include|#
directive|include
file|"datafiles.h"
end_include

begin_include
include|#
directive|include
file|"patterns.h"
end_include

begin_include
include|#
directive|include
file|"pattern_header.h"
end_include

begin_include
include|#
directive|include
file|"pattern_select.h"
end_include

begin_include
include|#
directive|include
file|"buildmenu.h"
end_include

begin_include
include|#
directive|include
file|"colormaps.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_comment
comment|/*  global variables  */
end_comment

begin_decl_stmt
DECL|variable|active_pattern
name|GPatternP
name|active_pattern
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pattern_list
name|GSList
modifier|*
name|pattern_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|num_patterns
name|int
name|num_patterns
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pattern_select_dialog
name|PatternSelectP
name|pattern_select_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  static variables  */
end_comment

begin_decl_stmt
DECL|variable|success
specifier|static
name|int
name|success
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|return_args
specifier|static
name|Argument
modifier|*
name|return_args
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|have_default_pattern
specifier|static
name|int
name|have_default_pattern
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  static function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GSList
modifier|*
name|insert_pattern_in_list
parameter_list|(
name|GSList
modifier|*
parameter_list|,
name|GPatternP
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|load_pattern
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|free_pattern
parameter_list|(
name|GPatternP
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|pattern_free_one
parameter_list|(
name|gpointer
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|pattern_compare_func
parameter_list|(
name|gpointer
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  function declarations  */
end_comment

begin_function
name|void
DECL|function|patterns_init (int no_data)
name|patterns_init
parameter_list|(
name|int
name|no_data
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
name|pattern_list
condition|)
name|patterns_free
argument_list|()
expr_stmt|;
name|pattern_list
operator|=
name|NULL
expr_stmt|;
name|num_patterns
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|pattern_path
condition|)
return|return;
if|if
condition|(
operator|!
name|no_data
condition|)
name|datafiles_read_directories
argument_list|(
name|pattern_path
argument_list|,
name|load_pattern
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  assign indexes to the loaded patterns  */
name|list
operator|=
name|pattern_list
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
comment|/*  Set the pattern index  */
operator|(
operator|(
name|GPattern
operator|*
operator|)
name|list
operator|->
name|data
operator|)
operator|->
name|index
operator|=
name|num_patterns
operator|++
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pattern_free_one (gpointer data,gpointer dummy)
name|pattern_free_one
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|dummy
parameter_list|)
block|{
name|free_pattern
argument_list|(
operator|(
name|GPatternP
operator|)
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|pattern_compare_func (gpointer first,gpointer second)
name|pattern_compare_func
parameter_list|(
name|gpointer
name|first
parameter_list|,
name|gpointer
name|second
parameter_list|)
block|{
return|return
name|strcmp
argument_list|(
operator|(
operator|(
name|GPatternP
operator|)
name|first
operator|)
operator|->
name|name
argument_list|,
operator|(
operator|(
name|GPatternP
operator|)
name|second
operator|)
operator|->
name|name
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|patterns_free ()
name|patterns_free
parameter_list|()
block|{
if|if
condition|(
name|pattern_list
condition|)
block|{
name|g_slist_foreach
argument_list|(
name|pattern_list
argument_list|,
name|pattern_free_one
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|pattern_list
argument_list|)
expr_stmt|;
block|}
name|have_default_pattern
operator|=
literal|0
expr_stmt|;
name|active_pattern
operator|=
name|NULL
expr_stmt|;
name|num_patterns
operator|=
literal|0
expr_stmt|;
name|pattern_list
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|pattern_select_dialog_free ()
name|pattern_select_dialog_free
parameter_list|()
block|{
if|if
condition|(
name|pattern_select_dialog
condition|)
block|{
name|pattern_select_free
argument_list|(
name|pattern_select_dialog
argument_list|)
expr_stmt|;
name|pattern_select_dialog
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GPatternP
DECL|function|get_active_pattern ()
name|get_active_pattern
parameter_list|()
block|{
if|if
condition|(
name|have_default_pattern
condition|)
block|{
name|have_default_pattern
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|active_pattern
condition|)
name|fatal_error
argument_list|(
literal|"Specified default pattern not found!"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|active_pattern
operator|&&
name|pattern_list
condition|)
name|active_pattern
operator|=
operator|(
name|GPatternP
operator|)
name|pattern_list
operator|->
name|data
expr_stmt|;
return|return
name|active_pattern
return|;
block|}
end_function

begin_function
specifier|static
name|GSList
modifier|*
DECL|function|insert_pattern_in_list (GSList * list,GPatternP pattern)
name|insert_pattern_in_list
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|,
name|GPatternP
name|pattern
parameter_list|)
block|{
return|return
name|g_slist_insert_sorted
argument_list|(
name|list
argument_list|,
name|pattern
argument_list|,
name|pattern_compare_func
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|load_pattern (char * filename)
name|load_pattern
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
block|{
name|GPatternP
name|pattern
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|int
name|bn_size
decl_stmt|;
name|unsigned
name|char
name|buf
index|[
name|sz_PatternHeader
index|]
decl_stmt|;
name|PatternHeader
name|header
decl_stmt|;
name|unsigned
name|int
modifier|*
name|hp
decl_stmt|;
name|int
name|i
decl_stmt|;
name|pattern
operator|=
operator|(
name|GPatternP
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|GPattern
argument_list|)
argument_list|)
expr_stmt|;
name|pattern
operator|->
name|filename
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|pattern
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
name|pattern
operator|->
name|mask
operator|=
name|NULL
expr_stmt|;
comment|/*  Open the requested file  */
if|if
condition|(
operator|!
operator|(
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"r"
argument_list|)
operator|)
condition|)
block|{
name|free_pattern
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  Read in the header size  */
if|if
condition|(
operator|(
name|fread
argument_list|(
name|buf
argument_list|,
literal|1
argument_list|,
name|sz_PatternHeader
argument_list|,
name|fp
argument_list|)
operator|)
operator|<
name|sz_PatternHeader
condition|)
block|{
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|free_pattern
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  rearrange the bytes in each unsigned int  */
name|hp
operator|=
operator|(
name|unsigned
name|int
operator|*
operator|)
operator|&
name|header
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|(
name|sz_PatternHeader
operator|/
literal|4
operator|)
condition|;
name|i
operator|++
control|)
name|hp
index|[
name|i
index|]
operator|=
operator|(
name|buf
index|[
name|i
operator|*
literal|4
index|]
operator|<<
literal|24
operator|)
operator|+
operator|(
name|buf
index|[
name|i
operator|*
literal|4
operator|+
literal|1
index|]
operator|<<
literal|16
operator|)
operator|+
operator|(
name|buf
index|[
name|i
operator|*
literal|4
operator|+
literal|2
index|]
operator|<<
literal|8
operator|)
operator|+
operator|(
name|buf
index|[
name|i
operator|*
literal|4
operator|+
literal|3
index|]
operator|)
expr_stmt|;
comment|/*  Check for correct file format */
if|if
condition|(
name|header
operator|.
name|magic_number
operator|!=
name|GPATTERN_MAGIC
condition|)
block|{
comment|/*  One thing that can save this error is if the pattern is version 1  */
if|if
condition|(
name|header
operator|.
name|version
operator|!=
literal|1
condition|)
block|{
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|free_pattern
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
comment|/*  Check for correct version  */
if|if
condition|(
name|header
operator|.
name|version
operator|!=
name|FILE_VERSION
condition|)
block|{
name|warning
argument_list|(
literal|"Unknown GIMP version #%d in \"%s\"\n"
argument_list|,
name|header
operator|.
name|version
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|free_pattern
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  Get a new pattern mask  */
name|pattern
operator|->
name|mask
operator|=
name|temp_buf_new
argument_list|(
name|header
operator|.
name|width
argument_list|,
name|header
operator|.
name|height
argument_list|,
name|header
operator|.
name|bytes
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Read in the pattern name  */
if|if
condition|(
operator|(
name|bn_size
operator|=
operator|(
name|header
operator|.
name|header_size
operator|-
name|sz_PatternHeader
operator|)
operator|)
condition|)
block|{
name|pattern
operator|->
name|name
operator|=
operator|(
name|char
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|char
argument_list|)
operator|*
name|bn_size
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|fread
argument_list|(
name|pattern
operator|->
name|name
argument_list|,
literal|1
argument_list|,
name|bn_size
argument_list|,
name|fp
argument_list|)
operator|)
operator|<
name|bn_size
condition|)
block|{
name|warning
argument_list|(
literal|"Error in GIMP pattern file...aborting."
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|free_pattern
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
else|else
name|pattern
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
literal|"Unnamed"
argument_list|)
expr_stmt|;
comment|/*  Read the pattern mask data  */
comment|/*  Read the image data  */
if|if
condition|(
operator|(
name|fread
argument_list|(
name|temp_buf_data
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
argument_list|,
literal|1
argument_list|,
name|header
operator|.
name|width
operator|*
name|header
operator|.
name|height
operator|*
name|header
operator|.
name|bytes
argument_list|,
name|fp
argument_list|)
operator|)
operator|<
name|header
operator|.
name|width
operator|*
name|header
operator|.
name|height
operator|*
name|header
operator|.
name|bytes
condition|)
name|warning
argument_list|(
literal|"GIMP pattern file appears to be truncated."
argument_list|)
expr_stmt|;
comment|/*  Clean up  */
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
comment|/*temp_buf_swap (pattern->mask);*/
name|pattern_list
operator|=
name|insert_pattern_in_list
argument_list|(
name|pattern_list
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
comment|/* Check if the current pattern is the default one */
if|if
condition|(
name|strcmp
argument_list|(
name|default_pattern
argument_list|,
name|prune_filename
argument_list|(
name|filename
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
block|{
name|active_pattern
operator|=
name|pattern
expr_stmt|;
name|have_default_pattern
operator|=
literal|1
expr_stmt|;
block|}
comment|/* if */
block|}
end_function

begin_function
name|GPatternP
DECL|function|get_pattern_by_index (int index)
name|get_pattern_by_index
parameter_list|(
name|int
name|index
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|GPatternP
name|pattern
init|=
name|NULL
decl_stmt|;
name|list
operator|=
name|g_slist_nth
argument_list|(
name|pattern_list
argument_list|,
name|index
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
name|pattern
operator|=
operator|(
name|GPatternP
operator|)
name|list
operator|->
name|data
expr_stmt|;
return|return
name|pattern
return|;
block|}
end_function

begin_function
name|void
DECL|function|select_pattern (pattern)
name|select_pattern
parameter_list|(
name|pattern
parameter_list|)
name|GPatternP
name|pattern
decl_stmt|;
block|{
comment|/*  Set the active pattern  */
name|active_pattern
operator|=
name|pattern
expr_stmt|;
comment|/*  Make sure the active pattern is unswapped... */
comment|/*temp_buf_unswap (pattern->mask);*/
comment|/*  Keep up appearances in the pattern dialog  */
if|if
condition|(
name|pattern_select_dialog
condition|)
name|pattern_select_select
argument_list|(
name|pattern_select_dialog
argument_list|,
name|pattern
operator|->
name|index
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|create_pattern_dialog ()
name|create_pattern_dialog
parameter_list|()
block|{
if|if
condition|(
operator|!
name|pattern_select_dialog
condition|)
block|{
comment|/*  Create the dialog...  */
name|pattern_select_dialog
operator|=
name|pattern_select_new
argument_list|()
expr_stmt|;
block|}
else|else
block|{
comment|/*  Popup the dialog  */
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|pattern_select_dialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|pattern_select_dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
else|else
name|gdk_window_raise
argument_list|(
name|pattern_select_dialog
operator|->
name|shell
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|free_pattern (pattern)
name|free_pattern
parameter_list|(
name|pattern
parameter_list|)
name|GPatternP
name|pattern
decl_stmt|;
block|{
if|if
condition|(
name|pattern
operator|->
name|mask
condition|)
name|temp_buf_free
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|pattern
operator|->
name|filename
condition|)
name|g_free
argument_list|(
name|pattern
operator|->
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|pattern
operator|->
name|name
condition|)
name|g_free
argument_list|(
name|pattern
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**************************/
end_comment

begin_comment
comment|/*  PATTERNS_GET_PATTERN  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|patterns_get_pattern_invoker (Argument * args)
name|patterns_get_pattern_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GPatternP
name|patternp
decl_stmt|;
name|success
operator|=
operator|(
name|patternp
operator|=
name|get_active_pattern
argument_list|()
operator|)
operator|!=
name|NULL
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
name|g_strdup
argument_list|(
name|patternp
operator|->
name|name
argument_list|)
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
name|patternp
operator|->
name|mask
operator|->
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
name|patternp
operator|->
name|mask
operator|->
name|height
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|patterns_get_pattern_out_args
name|ProcArg
name|patterns_get_pattern_out_args
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"name"
block|,
literal|"the pattern name"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"width"
block|,
literal|"the pattern width"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"height"
block|,
literal|"the pattern height"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_get_pattern_proc
name|ProcRecord
name|patterns_get_pattern_proc
init|=
block|{
literal|"gimp_patterns_get_pattern"
block|,
literal|"Retrieve information about the currently active pattern"
block|,
literal|"This procedure retrieves information about the currently active pattern.  This includes the pattern name, and the pattern extents (width and height).  All clone and bucket-fill operations with patterns will use this pattern to control the application of paint to the image."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Output arguments  */
literal|3
block|,
name|patterns_get_pattern_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|patterns_get_pattern_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**************************/
end_comment

begin_comment
comment|/*  PATTERNS_SET_PATTERN  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|patterns_set_pattern_invoker (Argument * args)
name|patterns_set_pattern_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GPatternP
name|patternp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|char
modifier|*
name|name
decl_stmt|;
name|success
operator|=
operator|(
name|name
operator|=
operator|(
name|char
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
operator|)
operator|!=
name|NULL
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|list
operator|=
name|pattern_list
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|patternp
operator|=
operator|(
name|GPatternP
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|patternp
operator|->
name|name
argument_list|,
name|name
argument_list|)
condition|)
block|{
name|success
operator|=
name|TRUE
expr_stmt|;
name|select_pattern
argument_list|(
name|patternp
argument_list|)
expr_stmt|;
break|break;
block|}
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|patterns_set_pattern_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|patterns_set_pattern_args
name|ProcArg
name|patterns_set_pattern_args
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"name"
block|,
literal|"the pattern name"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_set_pattern_proc
name|ProcRecord
name|patterns_set_pattern_proc
init|=
block|{
literal|"gimp_patterns_set_pattern"
block|,
literal|"Set the specified pattern as the active pattern"
block|,
literal|"This procedure allows the active pattern mask to be set by specifying its name.  The name is simply a string which corresponds to one of the names of the installed patterns.  If there is no matching pattern found, this procedure will return an error.  Otherwise, the specified pattern becomes active and will be used in all subsequent paint operations."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|patterns_set_pattern_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|patterns_set_pattern_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*******************/
end_comment

begin_comment
comment|/*  PATTERNS_LIST  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|patterns_list_invoker (Argument * args)
name|patterns_list_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GPatternP
name|patternp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|char
modifier|*
modifier|*
name|patterns
decl_stmt|;
name|int
name|i
decl_stmt|;
name|patterns
operator|=
operator|(
name|char
operator|*
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|char
operator|*
argument_list|)
operator|*
name|num_patterns
argument_list|)
expr_stmt|;
name|success
operator|=
operator|(
name|list
operator|=
name|pattern_list
operator|)
operator|!=
name|NULL
expr_stmt|;
name|i
operator|=
literal|0
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|patternp
operator|=
operator|(
name|GPatternP
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|patterns
index|[
name|i
operator|++
index|]
operator|=
name|g_strdup
argument_list|(
name|patternp
operator|->
name|name
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|patterns_list_proc
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
name|patterns
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|patterns_list_out_args
name|ProcArg
name|patterns_list_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"num_patterns"
block|,
literal|"the number of patterns in the pattern list"
block|}
block|,
block|{
name|PDB_STRINGARRAY
block|,
literal|"pattern_list"
block|,
literal|"the list of pattern names"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|patterns_list_proc
name|ProcRecord
name|patterns_list_proc
init|=
block|{
literal|"gimp_patterns_list"
block|,
literal|"Retrieve a complete listing of the available patterns"
block|,
literal|"This procedure returns a complete listing of available GIMP patterns.  Each name returned can be used as input to the 'gimp_patterns_set_pattern'"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Output arguments  */
literal|2
block|,
name|patterns_list_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|patterns_list_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

end_unit

