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
file|"brushes.h"
end_include

begin_include
include|#
directive|include
file|"brush_header.h"
end_include

begin_include
include|#
directive|include
file|"brush_select.h"
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
file|"datafiles.h"
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
DECL|variable|active_brush
name|GBrushP
name|active_brush
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brush_list
name|GSList
modifier|*
name|brush_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|num_brushes
name|int
name|num_brushes
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|opacity
name|double
name|opacity
init|=
literal|1.0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paint_mode
name|int
name|paint_mode
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brush_select_dialog
name|BrushSelectP
name|brush_select_dialog
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
DECL|variable|have_default_brush
specifier|static
name|int
name|have_default_brush
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
name|insert_brush_in_list
parameter_list|(
name|GSList
modifier|*
parameter_list|,
name|GBrushP
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|create_default_brush
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|load_brush
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
name|free_brush
parameter_list|(
name|GBrushP
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brushes_free_one
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
name|brush_compare_func
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
DECL|function|brushes_init ()
name|brushes_init
parameter_list|()
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
name|brush_list
condition|)
name|brushes_free
argument_list|()
expr_stmt|;
name|brush_list
operator|=
name|NULL
expr_stmt|;
name|num_brushes
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|brush_path
condition|)
name|create_default_brush
argument_list|()
expr_stmt|;
else|else
name|datafiles_read_directories
argument_list|(
name|brush_path
argument_list|,
name|load_brush
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  assign indexes to the loaded brushes  */
name|list
operator|=
name|brush_list
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
comment|/*  Set the brush index  */
operator|(
operator|(
name|GBrush
operator|*
operator|)
name|list
operator|->
name|data
operator|)
operator|->
name|index
operator|=
name|num_brushes
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
DECL|function|brushes_free_one (gpointer data,gpointer dummy)
name|brushes_free_one
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|dummy
parameter_list|)
block|{
name|free_brush
argument_list|(
operator|(
name|GBrushP
operator|)
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|brush_compare_func (gpointer first,gpointer second)
name|brush_compare_func
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
name|GBrushP
operator|)
name|first
operator|)
operator|->
name|name
argument_list|,
operator|(
operator|(
name|GBrushP
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
DECL|function|brushes_free ()
name|brushes_free
parameter_list|()
block|{
if|if
condition|(
name|brush_list
condition|)
block|{
name|g_slist_foreach
argument_list|(
name|brush_list
argument_list|,
name|brushes_free_one
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|brush_list
argument_list|)
expr_stmt|;
block|}
name|have_default_brush
operator|=
literal|0
expr_stmt|;
name|active_brush
operator|=
name|NULL
expr_stmt|;
name|num_brushes
operator|=
literal|0
expr_stmt|;
name|brush_list
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|brush_select_dialog_free ()
name|brush_select_dialog_free
parameter_list|()
block|{
if|if
condition|(
name|brush_select_dialog
condition|)
block|{
name|brush_select_free
argument_list|(
name|brush_select_dialog
argument_list|)
expr_stmt|;
name|brush_select_dialog
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GBrushP
DECL|function|get_active_brush ()
name|get_active_brush
parameter_list|()
block|{
if|if
condition|(
name|have_default_brush
condition|)
block|{
name|have_default_brush
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|active_brush
condition|)
name|fatal_error
argument_list|(
literal|"Specified default brush not found!"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|active_brush
operator|&&
name|brush_list
condition|)
name|active_brush
operator|=
operator|(
name|GBrushP
operator|)
name|brush_list
operator|->
name|data
expr_stmt|;
return|return
name|active_brush
return|;
block|}
end_function

begin_function
specifier|static
name|GSList
modifier|*
DECL|function|insert_brush_in_list (GSList * list,GBrushP brush)
name|insert_brush_in_list
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|,
name|GBrushP
name|brush
parameter_list|)
block|{
return|return
name|g_slist_insert_sorted
argument_list|(
name|list
argument_list|,
name|brush
argument_list|,
name|brush_compare_func
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|create_default_brush ()
name|create_default_brush
parameter_list|()
block|{
name|GBrushP
name|brush
decl_stmt|;
name|gchar
name|filled
index|[]
init|=
block|{
literal|255
block|}
decl_stmt|;
name|brush
operator|=
name|g_new
argument_list|(
name|GBrush
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|brush
operator|->
name|filename
operator|=
name|NULL
expr_stmt|;
name|brush
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
literal|"Default"
argument_list|)
expr_stmt|;
name|brush
operator|->
name|mask
operator|=
name|temp_buf_new
argument_list|(
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|filled
argument_list|)
expr_stmt|;
name|brush
operator|->
name|spacing
operator|=
literal|25
expr_stmt|;
comment|/*  Swap the brush to disk (if we're being stingy with memory) */
if|if
condition|(
name|stingy_memory_use
condition|)
name|temp_buf_swap
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
name|brush_list
operator|=
name|insert_brush_in_list
argument_list|(
name|brush_list
argument_list|,
name|brush
argument_list|)
expr_stmt|;
comment|/*  Make this the default, active brush  */
name|active_brush
operator|=
name|brush
expr_stmt|;
name|have_default_brush
operator|=
literal|1
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|load_brush (char * filename)
name|load_brush
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
block|{
name|GBrushP
name|brush
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
name|sz_BrushHeader
index|]
decl_stmt|;
name|BrushHeader
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
name|brush
operator|=
operator|(
name|GBrushP
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|GBrush
argument_list|)
argument_list|)
expr_stmt|;
name|brush
operator|->
name|filename
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|brush
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
name|brush
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
name|free_brush
argument_list|(
name|brush
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
name|sz_BrushHeader
argument_list|,
name|fp
argument_list|)
operator|)
operator|<
name|sz_BrushHeader
condition|)
block|{
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|free_brush
argument_list|(
name|brush
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
name|sz_BrushHeader
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
name|GBRUSH_MAGIC
condition|)
block|{
comment|/*  One thing that can save this error is if the brush is version 1  */
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
name|free_brush
argument_list|(
name|brush
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
comment|/*  If this is a version 1 brush, set the fp back 8 bytes  */
if|if
condition|(
name|header
operator|.
name|version
operator|==
literal|1
condition|)
block|{
name|fseek
argument_list|(
name|fp
argument_list|,
operator|-
literal|8
argument_list|,
name|SEEK_CUR
argument_list|)
expr_stmt|;
name|header
operator|.
name|header_size
operator|+=
literal|8
expr_stmt|;
comment|/*  spacing is not defined in version 1  */
name|header
operator|.
name|spacing
operator|=
literal|25
expr_stmt|;
block|}
else|else
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
name|free_brush
argument_list|(
name|brush
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
comment|/*  Get a new brush mask  */
name|brush
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
name|brush
operator|->
name|spacing
operator|=
name|header
operator|.
name|spacing
expr_stmt|;
comment|/*  Read in the brush name  */
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
name|sz_BrushHeader
operator|)
operator|)
condition|)
block|{
name|brush
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
name|brush
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
literal|"Error in GIMP brush file...aborting."
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|free_brush
argument_list|(
name|brush
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
else|else
name|brush
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
literal|"Unnamed"
argument_list|)
expr_stmt|;
comment|/*  Read the brush mask data  */
comment|/*  Read the image data  */
if|if
condition|(
operator|(
name|fread
argument_list|(
name|temp_buf_data
argument_list|(
name|brush
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
condition|)
name|warning
argument_list|(
literal|"GIMP brush file appears to be truncated."
argument_list|)
expr_stmt|;
comment|/*  Clean up  */
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
comment|/*  Swap the brush to disk (if we're being stingy with memory) */
if|if
condition|(
name|stingy_memory_use
condition|)
name|temp_buf_swap
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
name|brush_list
operator|=
name|insert_brush_in_list
argument_list|(
name|brush_list
argument_list|,
name|brush
argument_list|)
expr_stmt|;
comment|/* Check if the current brush is the default one */
if|if
condition|(
name|strcmp
argument_list|(
name|default_brush
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
name|active_brush
operator|=
name|brush
expr_stmt|;
name|have_default_brush
operator|=
literal|1
expr_stmt|;
block|}
comment|/* if */
block|}
end_function

begin_function
name|GBrushP
DECL|function|get_brush_by_index (int index)
name|get_brush_by_index
parameter_list|(
name|int
name|index
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|GBrushP
name|brush
init|=
name|NULL
decl_stmt|;
name|list
operator|=
name|g_slist_nth
argument_list|(
name|brush_list
argument_list|,
name|index
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
name|brush
operator|=
operator|(
name|GBrushP
operator|)
name|list
operator|->
name|data
expr_stmt|;
return|return
name|brush
return|;
block|}
end_function

begin_function
name|void
DECL|function|select_brush (GBrushP brush)
name|select_brush
parameter_list|(
name|GBrushP
name|brush
parameter_list|)
block|{
comment|/*  Make sure the active brush is swapped before we get a new one... */
if|if
condition|(
name|stingy_memory_use
condition|)
name|temp_buf_swap
argument_list|(
name|active_brush
operator|->
name|mask
argument_list|)
expr_stmt|;
comment|/*  Set the active brush  */
name|active_brush
operator|=
name|brush
expr_stmt|;
comment|/*  Make sure the active brush is unswapped... */
if|if
condition|(
name|stingy_memory_use
condition|)
name|temp_buf_unswap
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
comment|/*  Keep up appearances in the brush dialog  */
if|if
condition|(
name|brush_select_dialog
condition|)
name|brush_select_select
argument_list|(
name|brush_select_dialog
argument_list|,
name|brush
operator|->
name|index
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|create_brush_dialog ()
name|create_brush_dialog
parameter_list|()
block|{
if|if
condition|(
operator|!
name|brush_select_dialog
condition|)
block|{
comment|/*  Create the dialog...  */
name|brush_select_dialog
operator|=
name|brush_select_new
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
name|brush_select_dialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|brush_select_dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
else|else
name|gdk_window_raise
argument_list|(
name|brush_select_dialog
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
DECL|function|free_brush (brush)
name|free_brush
parameter_list|(
name|brush
parameter_list|)
name|GBrushP
name|brush
decl_stmt|;
block|{
if|if
condition|(
name|brush
operator|->
name|mask
condition|)
name|temp_buf_free
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|filename
condition|)
name|g_free
argument_list|(
name|brush
operator|->
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|name
condition|)
name|g_free
argument_list|(
name|brush
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|brush
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|double
DECL|function|get_brush_opacity ()
name|get_brush_opacity
parameter_list|()
block|{
return|return
name|opacity
return|;
block|}
end_function

begin_function
name|int
DECL|function|get_brush_spacing ()
name|get_brush_spacing
parameter_list|()
block|{
if|if
condition|(
name|active_brush
condition|)
return|return
name|active_brush
operator|->
name|spacing
return|;
else|else
return|return
literal|0
return|;
block|}
end_function

begin_function
name|int
DECL|function|get_brush_paint_mode ()
name|get_brush_paint_mode
parameter_list|()
block|{
return|return
name|paint_mode
return|;
block|}
end_function

begin_function
name|void
DECL|function|set_brush_opacity (opac)
name|set_brush_opacity
parameter_list|(
name|opac
parameter_list|)
name|double
name|opac
decl_stmt|;
block|{
name|opacity
operator|=
name|opac
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|set_brush_spacing (spac)
name|set_brush_spacing
parameter_list|(
name|spac
parameter_list|)
name|int
name|spac
decl_stmt|;
block|{
if|if
condition|(
name|active_brush
condition|)
name|active_brush
operator|->
name|spacing
operator|=
name|spac
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|set_brush_paint_mode (pm)
name|set_brush_paint_mode
parameter_list|(
name|pm
parameter_list|)
name|int
name|pm
decl_stmt|;
block|{
name|paint_mode
operator|=
name|pm
expr_stmt|;
block|}
end_function

begin_comment
comment|/***********************/
end_comment

begin_comment
comment|/*  BRUSHES_GET_BRUSH  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_get_brush_invoker (Argument * args)
name|brushes_get_brush_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GBrushP
name|brushp
decl_stmt|;
name|success
operator|=
operator|(
name|brushp
operator|=
name|get_active_brush
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
name|brushes_get_brush_proc
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
name|brushp
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
name|brushp
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
name|brushp
operator|->
name|mask
operator|->
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
name|brushp
operator|->
name|spacing
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_refresh_brush_invoker (Argument * args)
name|brushes_refresh_brush_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
comment|/* FIXME: I've hardcoded success to be 1, because brushes_init() is a     *        void function right now.  It'd be nice if it returned a value at     *        some future date, so we could tell if things blew up when reparsing    *        the list (for whatever reason).     *                       - Seth "Yes, this is a kludge" Burgess    *<sjburges@ou.edu>    */
name|success
operator|=
name|TRUE
expr_stmt|;
name|brushes_init
argument_list|()
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_refresh_brush_proc
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
DECL|variable|brushes_get_brush_out_args
name|ProcArg
name|brushes_get_brush_out_args
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"name"
block|,
literal|"the brush name"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"width"
block|,
literal|"the brush width"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"height"
block|,
literal|"the brush height"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"spacing"
block|,
literal|"the brush spacing: (% of MAX [width, height])"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_get_brush_proc
name|ProcRecord
name|brushes_get_brush_proc
init|=
block|{
literal|"gimp_brushes_get_brush"
block|,
literal|"Retrieve information about the currently active brush mask"
block|,
literal|"This procedure retrieves information about the currently active brush mask.  This includes the brush name, the width and height, and the brush spacing paramter.  All paint operations and stroke operations use this mask to control the application of paint to the image."
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
literal|4
block|,
name|brushes_get_brush_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|brushes_get_brush_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* =========================================================== */
end_comment

begin_comment
comment|/* REFRESH BRUSHES                                             */
end_comment

begin_comment
comment|/* =========================================================== */
end_comment

begin_decl_stmt
DECL|variable|brushes_refresh_brush_proc
name|ProcRecord
name|brushes_refresh_brush_proc
init|=
block|{
literal|"gimp_brushes_refresh"
block|,
literal|"Refresh current brushes"
block|,
literal|"This procedure retrieves all brushes currently in the user's brush path "
literal|"and updates the brush dialog accordingly."
block|,
literal|"Seth Burgess<sjburges@ou.edu>"
block|,
literal|"Seth Burgess"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|brushes_refresh_brush_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***********************/
end_comment

begin_comment
comment|/*  BRUSHES_SET_BRUSH  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_set_brush_invoker (Argument * args)
name|brushes_set_brush_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GBrushP
name|brushp
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
name|brush_list
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
name|brushp
operator|=
operator|(
name|GBrushP
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
name|brushp
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
name|select_brush
argument_list|(
name|brushp
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
name|brushes_set_brush_proc
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
DECL|variable|brushes_set_brush_args
name|ProcArg
name|brushes_set_brush_args
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"name"
block|,
literal|"the brush name"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_set_brush_proc
name|ProcRecord
name|brushes_set_brush_proc
init|=
block|{
literal|"gimp_brushes_set_brush"
block|,
literal|"Set the specified brush as the active brush"
block|,
literal|"This procedure allows the active brush mask to be set by specifying its name.  The name is simply a string which corresponds to one of the names of the installed brushes.  If there is no matching brush found, this procedure will return an error.  Otherwise, the specified brush becomes active and will be used in all subsequent paint operations."
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
name|brushes_set_brush_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|brushes_set_brush_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*************************/
end_comment

begin_comment
comment|/*  BRUSHES_GET_OPACITY  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_get_opacity_invoker (Argument * args)
name|brushes_get_opacity_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_get_opacity_proc
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_float
operator|=
name|get_brush_opacity
argument_list|()
operator|*
literal|100.0
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|brushes_get_opacity_out_args
name|ProcArg
name|brushes_get_opacity_out_args
index|[]
init|=
block|{
block|{
name|PDB_FLOAT
block|,
literal|"opacity"
block|,
literal|"the brush opacity: 0<= opacity<= 100"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_get_opacity_proc
name|ProcRecord
name|brushes_get_opacity_proc
init|=
block|{
literal|"gimp_brushes_get_opacity"
block|,
literal|"Get the brush opacity"
block|,
literal|"This procedure returns the opacity setting for brushes.  This value is set globally and will remain the same even if the brush mask is changed.  The return value is a floating point number between 0 and 100."
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
literal|1
block|,
name|brushes_get_opacity_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|brushes_get_opacity_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*************************/
end_comment

begin_comment
comment|/*  BRUSHES_SET_OPACITY  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_set_opacity_invoker (Argument * args)
name|brushes_set_opacity_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|double
name|opacity
decl_stmt|;
name|opacity
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|success
operator|=
operator|(
name|opacity
operator|>=
literal|0.0
operator|&&
name|opacity
operator|<=
literal|100.0
operator|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|set_brush_opacity
argument_list|(
name|opacity
operator|/
literal|100.0
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_set_opacity_proc
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
DECL|variable|brushes_set_opacity_args
name|ProcArg
name|brushes_set_opacity_args
index|[]
init|=
block|{
block|{
name|PDB_FLOAT
block|,
literal|"opacity"
block|,
literal|"the brush opacity: 0<= opacity<= 100"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_set_opacity_proc
name|ProcRecord
name|brushes_set_opacity_proc
init|=
block|{
literal|"gimp_brushes_set_opacity"
block|,
literal|"Set the brush opacity"
block|,
literal|"This procedure modifies the opacity setting for brushes.  This value is set globally and will remain the same even if the brush mask is changed.  The value should be a floating point number between 0 and 100."
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
name|brushes_set_opacity_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|brushes_set_opacity_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*************************/
end_comment

begin_comment
comment|/*  BRUSHES_GET_SPACING  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_get_spacing_invoker (Argument * args)
name|brushes_get_spacing_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_get_spacing_proc
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|get_brush_spacing
argument_list|()
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|brushes_get_spacing_out_args
name|ProcArg
name|brushes_get_spacing_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"spacing"
block|,
literal|"the brush spacing: 0<= spacing<= 1000"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_get_spacing_proc
name|ProcRecord
name|brushes_get_spacing_proc
init|=
block|{
literal|"gimp_brushes_get_spacing"
block|,
literal|"Get the brush spacing"
block|,
literal|"This procedure returns the spacing setting for brushes.  This value is set per brush and will change if a different brush is selected.  The return value is an integer between 0 and 1000 which represents percentage of the maximum of the width and height of the mask."
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
literal|1
block|,
name|brushes_get_spacing_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|brushes_get_spacing_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*************************/
end_comment

begin_comment
comment|/*  BRUSHES_SET_SPACING  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_set_spacing_invoker (Argument * args)
name|brushes_set_spacing_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|spacing
decl_stmt|;
name|spacing
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|success
operator|=
operator|(
name|spacing
operator|>=
literal|0
operator|&&
name|spacing
operator|<=
literal|1000
operator|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|set_brush_spacing
argument_list|(
name|spacing
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_set_spacing_proc
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
DECL|variable|brushes_set_spacing_args
name|ProcArg
name|brushes_set_spacing_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"spacing"
block|,
literal|"the brush spacing: 0<= spacing<= 1000"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_set_spacing_proc
name|ProcRecord
name|brushes_set_spacing_proc
init|=
block|{
literal|"gimp_brushes_set_spacing"
block|,
literal|"Set the brush spacing"
block|,
literal|"This procedure modifies the spacing setting for the current brush.  This value is set on a per-brush basis and will change if a different brush mask is selected.  The value should be a integer between 0 and 1000."
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
name|brushes_set_spacing_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|brushes_set_spacing_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/****************************/
end_comment

begin_comment
comment|/*  BRUSHES_GET_PAINT_MODE  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_get_paint_mode_invoker (Argument * args)
name|brushes_get_paint_mode_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_get_paint_mode_proc
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|get_brush_paint_mode
argument_list|()
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|brushes_get_paint_mode_out_args
name|ProcArg
name|brushes_get_paint_mode_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"paint_mode"
block|,
literal|"the paint mode: { NORMAL (0), DISSOLVE (1), BEHIND (2), MULTIPLY (3), SCREEN (4), OVERLAY (5) DIFFERENCE (6), ADDITION (7), SUBTRACT (8), DARKEN-ONLY (9), LIGHTEN-ONLY (10), HUE (11), SATURATION (12), COLOR (13), VALUE (14) }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_get_paint_mode_proc
name|ProcRecord
name|brushes_get_paint_mode_proc
init|=
block|{
literal|"gimp_brushes_get_paint_mode"
block|,
literal|"Get the brush paint_mode"
block|,
literal|"This procedure returns the paint-mode setting for brushes.  This value is set globally and will not change if a different brush is selected.  The return value is an integer between 0 and 13 which corresponds to the values listed in the argument description."
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
literal|1
block|,
name|brushes_get_paint_mode_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|brushes_get_paint_mode_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/****************************/
end_comment

begin_comment
comment|/*  BRUSHES_SET_PAINT_MODE  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_set_paint_mode_invoker (Argument * args)
name|brushes_set_paint_mode_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|paint_mode
decl_stmt|;
name|paint_mode
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|success
operator|=
operator|(
name|paint_mode
operator|>=
name|NORMAL_MODE
operator|&&
name|paint_mode
operator|<=
name|VALUE_MODE
operator|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|set_brush_paint_mode
argument_list|(
name|paint_mode
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_set_paint_mode_proc
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
DECL|variable|brushes_set_paint_mode_args
name|ProcArg
name|brushes_set_paint_mode_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"paint_mode"
block|,
literal|"the paint mode: { NORMAL (0), DISSOLVE (1), BEHIND (2), MULTIPLY (3), SCREEN (4), OVERLAY (5) DIFFERENCE (6), ADDITION (7), SUBTRACT (8), DARKEN-ONLY (9), LIGHTEN-ONLY (10), HUE (11), SATURATION (12), COLOR (13), VALUE (14) }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_set_paint_mode_proc
name|ProcRecord
name|brushes_set_paint_mode_proc
init|=
block|{
literal|"gimp_brushes_set_paint_mode"
block|,
literal|"Set the brush paint_mode"
block|,
literal|"This procedure modifies the paint_mode setting for the current brush.  This value is set globally and will not change if a different brush mask is selected."
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
name|brushes_set_paint_mode_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|brushes_set_paint_mode_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/******************/
end_comment

begin_comment
comment|/*  BRUSHES_LIST  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_list_invoker (Argument * args)
name|brushes_list_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GBrushP
name|brushp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|char
modifier|*
modifier|*
name|brushes
decl_stmt|;
name|int
name|i
decl_stmt|;
name|brushes
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
name|num_brushes
argument_list|)
expr_stmt|;
name|success
operator|=
operator|(
name|list
operator|=
name|brush_list
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
name|brushp
operator|=
operator|(
name|GBrushP
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|brushes
index|[
name|i
operator|++
index|]
operator|=
name|g_strdup
argument_list|(
name|brushp
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
name|brushes_list_proc
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
name|num_brushes
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
name|brushes
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
DECL|variable|brushes_list_out_args
name|ProcArg
name|brushes_list_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"num_brushes"
block|,
literal|"the number of brushes in the brush list"
block|}
block|,
block|{
name|PDB_STRINGARRAY
block|,
literal|"brush_list"
block|,
literal|"the list of brush names"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_list_proc
name|ProcRecord
name|brushes_list_proc
init|=
block|{
literal|"gimp_brushes_list"
block|,
literal|"Retrieve a complete listing of the available brushes"
block|,
literal|"This procedure returns a complete listing of available GIMP brushes.  Each name returned can be used as input to the 'gimp_brushes_set_brush'"
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
name|brushes_list_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|brushes_list_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

end_unit

