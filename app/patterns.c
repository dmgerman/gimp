begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_DIRENT_H
end_ifdef

begin_include
include|#
directive|include
file|<dirent.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  global variables  */
end_comment

begin_decl_stmt
DECL|variable|active_pattern
name|GPattern
modifier|*
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
name|gint
name|num_patterns
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  static variables  */
end_comment

begin_decl_stmt
DECL|variable|standard_pattern
specifier|static
name|GPattern
modifier|*
name|standard_pattern
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local function prototypes  */
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
name|GPattern
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|load_pattern
parameter_list|(
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|pattern_free_func
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
name|gconstpointer
parameter_list|,
name|gconstpointer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|patterns_init (gboolean no_data)
name|patterns_init
parameter_list|(
name|gboolean
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
if|if
condition|(
name|pattern_path
operator|!=
name|NULL
operator|&&
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
for|for
control|(
name|list
operator|=
name|pattern_list
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
block|}
name|gimp_context_refresh_patterns
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|patterns_free (void)
name|patterns_free
parameter_list|(
name|void
parameter_list|)
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
name|pattern_free_func
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
name|GPattern
modifier|*
DECL|function|patterns_get_standard_pattern (void)
name|patterns_get_standard_pattern
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|standard_pattern
condition|)
block|{
name|guchar
modifier|*
name|data
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|;
name|standard_pattern
operator|=
name|g_new
argument_list|(
name|GPattern
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|standard_pattern
operator|->
name|filename
operator|=
name|NULL
expr_stmt|;
name|standard_pattern
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
literal|"Standard"
argument_list|)
expr_stmt|;
name|standard_pattern
operator|->
name|index
operator|=
operator|-
literal|1
expr_stmt|;
comment|/*  not part of the pattern list  */
name|standard_pattern
operator|->
name|mask
operator|=
name|temp_buf_new
argument_list|(
literal|32
argument_list|,
literal|32
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|=
name|temp_buf_data
argument_list|(
name|standard_pattern
operator|->
name|mask
argument_list|)
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|standard_pattern
operator|->
name|mask
operator|->
name|height
condition|;
name|row
operator|++
control|)
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|standard_pattern
operator|->
name|mask
operator|->
name|width
condition|;
name|col
operator|++
control|)
block|{
name|memset
argument_list|(
name|data
argument_list|,
operator|(
name|col
operator|%
literal|2
operator|)
operator|&&
operator|(
name|row
operator|%
literal|2
operator|)
condition|?
literal|255
else|:
literal|0
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|data
operator|+=
literal|3
expr_stmt|;
block|}
block|}
return|return
name|standard_pattern
return|;
block|}
end_function

begin_function
name|GPattern
modifier|*
DECL|function|pattern_list_get_pattern_by_index (GSList * list,gint index)
name|pattern_list_get_pattern_by_index
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|GPattern
modifier|*
name|pattern
init|=
name|NULL
decl_stmt|;
name|list
operator|=
name|g_slist_nth
argument_list|(
name|list
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
name|GPattern
operator|*
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
name|GPattern
modifier|*
DECL|function|pattern_list_get_pattern (GSList * list,gchar * name)
name|pattern_list_get_pattern
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GPattern
modifier|*
name|pattern
decl_stmt|;
for|for
control|(
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
name|pattern
operator|=
operator|(
name|GPattern
operator|*
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
name|pattern
operator|->
name|name
argument_list|,
name|name
argument_list|)
condition|)
return|return
name|pattern
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|pattern_load (GPattern * pattern,FILE * fp,gchar * filename)
name|pattern_load
parameter_list|(
name|GPattern
modifier|*
name|pattern
parameter_list|,
name|FILE
modifier|*
name|fp
parameter_list|,
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|gint
name|bn_size
decl_stmt|;
name|guchar
name|buf
index|[
name|sz_PatternHeader
index|]
decl_stmt|;
name|PatternHeader
name|header
decl_stmt|;
name|guint
modifier|*
name|hp
decl_stmt|;
name|gint
name|i
decl_stmt|;
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
name|pattern_free
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/*  rearrange the bytes in each unsigned int  */
name|hp
operator|=
operator|(
name|guint
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
name|pattern_free
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
comment|/*  Check for correct version  */
if|if
condition|(
name|header
operator|.
name|version
operator|!=
name|GPATTERN_FILE_VERSION
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Unknown GIMP version #%d in \"%s\"\n"
argument_list|)
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
name|pattern_free
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
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
name|g_new
argument_list|(
name|gchar
argument_list|,
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
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Error in GIMP pattern file...aborting."
argument_list|)
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|pattern_free
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
else|else
name|pattern
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"Unnamed"
argument_list|)
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
name|g_message
argument_list|(
name|_
argument_list|(
literal|"GIMP pattern file appears to be truncated."
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  success  */
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|void
DECL|function|pattern_free (GPattern * pattern)
name|pattern_free
parameter_list|(
name|GPattern
modifier|*
name|pattern
parameter_list|)
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
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|pattern_free_func (gpointer data,gpointer dummy)
name|pattern_free_func
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|dummy
parameter_list|)
block|{
name|pattern_free
argument_list|(
operator|(
name|GPattern
operator|*
operator|)
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|pattern_compare_func (gconstpointer first,gconstpointer second)
name|pattern_compare_func
parameter_list|(
name|gconstpointer
name|first
parameter_list|,
name|gconstpointer
name|second
parameter_list|)
block|{
return|return
name|strcmp
argument_list|(
operator|(
operator|(
specifier|const
name|GPattern
operator|*
operator|)
name|first
operator|)
operator|->
name|name
argument_list|,
operator|(
operator|(
specifier|const
name|GPattern
operator|*
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
specifier|static
name|GSList
modifier|*
DECL|function|insert_pattern_in_list (GSList * list,GPattern * pattern)
name|insert_pattern_in_list
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|,
name|GPattern
modifier|*
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
DECL|function|load_pattern (gchar * filename)
name|load_pattern
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GPattern
modifier|*
name|pattern
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|pattern
operator|=
name|g_new
argument_list|(
name|GPattern
argument_list|,
literal|1
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
literal|"rb"
argument_list|)
operator|)
condition|)
block|{
name|pattern_free
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|pattern_load
argument_list|(
name|pattern
argument_list|,
name|fp
argument_list|,
name|filename
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Pattern load failed"
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
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
block|}
end_function

end_unit

