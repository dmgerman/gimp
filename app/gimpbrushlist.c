begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpbrushlist.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushgenerated.h"
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
file|"devices.h"
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
file|"gimpsignal.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"paint_core.h"
end_include

begin_include
include|#
directive|include
file|"gimpset.h"
end_include

begin_include
include|#
directive|include
file|"gimpsetP.h"
end_include

begin_comment
comment|/*  global variables  */
end_comment

begin_decl_stmt
DECL|variable|active_brush
name|GimpBrushP
name|active_brush
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brush_list
name|GimpBrushList
modifier|*
name|brush_list
init|=
name|NULL
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
name|gconstpointer
parameter_list|,
name|gconstpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_list_recalc_indexes
parameter_list|(
name|GimpBrushList
modifier|*
name|brush_list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_list_uniquefy_names
parameter_list|(
name|GimpBrushList
modifier|*
name|brush_list
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* class functions */
end_comment

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpObjectClass
modifier|*
name|parent_class
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_brush_list_class_init (GimpBrushListClass * klass)
name|gimp_brush_list_class_init
parameter_list|(
name|GimpBrushListClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|gimp_object_get_type
argument_list|()
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_list_init (GimpBrushList * list)
name|gimp_brush_list_init
parameter_list|(
name|GimpBrushList
modifier|*
name|list
parameter_list|)
block|{
name|list
operator|->
name|num_brushes
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gimp_brush_list_get_type (void)
name|GtkType
name|gimp_brush_list_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
name|GtkTypeInfo
name|info
init|=
block|{
literal|"GimpBrushList"
block|,
sizeof|sizeof
argument_list|(
name|GimpBrushList
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpBrushListClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_brush_list_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_brush_list_init
block|,
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
name|type
operator|=
name|gtk_type_unique
argument_list|(
name|gimp_set_get_type
argument_list|()
argument_list|,
operator|&
name|info
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GimpBrushList
modifier|*
DECL|function|gimp_brush_list_new ()
name|gimp_brush_list_new
parameter_list|()
block|{
name|GimpBrushList
modifier|*
name|list
init|=
name|GIMP_BRUSH_LIST
argument_list|(
name|gtk_type_new
argument_list|(
name|gimp_brush_list_get_type
argument_list|()
argument_list|)
argument_list|)
decl_stmt|;
name|GIMP_SET
argument_list|(
name|list
argument_list|)
operator|->
name|type
operator|=
name|GIMP_TYPE_BRUSH
expr_stmt|;
name|GIMP_SET
argument_list|(
name|list
argument_list|)
operator|->
name|weak
operator|=
literal|0
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

begin_function
DECL|function|gimp_brush_list_uniquefy_names (GimpBrushList * blist)
name|void
name|gimp_brush_list_uniquefy_names
parameter_list|(
name|GimpBrushList
modifier|*
name|blist
parameter_list|)
block|{
name|GSList
modifier|*
name|list
init|=
name|GIMP_SET
argument_list|(
name|blist
argument_list|)
operator|->
name|list
decl_stmt|;
name|GimpBrushP
name|gb_start
init|=
name|NULL
decl_stmt|;
name|gint
name|gb_count
init|=
literal|0
decl_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|GimpBrushP
name|gb
init|=
operator|(
name|GimpBrushP
operator|)
name|list
operator|->
name|data
decl_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
block|{
name|GimpBrushP
name|gb2
init|=
operator|(
name|GimpBrushP
operator|)
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gb_start
operator|==
name|NULL
condition|)
block|{
name|gb_start
operator|=
name|gb
expr_stmt|;
block|}
if|if
condition|(
name|gb_start
operator|->
name|name
operator|&&
name|gb2
operator|->
name|name
operator|&&
operator|(
name|strcmp
argument_list|(
name|gb_start
operator|->
name|name
argument_list|,
name|gb2
operator|->
name|name
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|gint
name|b_digits
init|=
literal|2
decl_stmt|;
name|gint
name|gb_tmp_cnt
init|=
name|gb_count
operator|++
decl_stmt|;
comment|/* Alter gb2... */
name|g_free
argument_list|(
name|gb2
operator|->
name|name
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|gb_tmp_cnt
operator|/=
literal|10
operator|)
operator|>
literal|0
condition|)
name|b_digits
operator|++
expr_stmt|;
comment|/* name str + " #" + digits + null */
name|gb2
operator|->
name|name
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|gb_start
operator|->
name|name
argument_list|)
operator|+
literal|3
operator|+
name|b_digits
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|gb2
operator|->
name|name
argument_list|,
literal|"%s #%d"
argument_list|,
name|gb_start
operator|->
name|name
argument_list|,
name|gb_count
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gb_start
operator|=
name|gb2
expr_stmt|;
name|gb_count
operator|=
literal|0
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_comment
comment|/*  function declarations  */
end_comment

begin_function
name|void
DECL|function|brushes_init (int no_data)
name|brushes_init
parameter_list|(
name|int
name|no_data
parameter_list|)
block|{
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
name|brush_list
operator|=
name|gimp_brush_list_new
argument_list|()
expr_stmt|;
if|if
condition|(
name|brush_path
operator|==
name|NULL
operator|||
operator|(
name|no_data
operator|)
condition|)
name|create_default_brush
argument_list|()
expr_stmt|;
else|else
name|datafiles_read_directories
argument_list|(
name|brush_path
argument_list|,
operator|(
name|datafile_loader_t
operator|)
name|gimp_brush_new
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_brush_list_recalc_indexes
argument_list|(
name|brush_list
argument_list|)
expr_stmt|;
name|gimp_brush_list_uniquefy_names
argument_list|(
name|brush_list
argument_list|)
expr_stmt|;
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
name|gimp_object_unref
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|brush_compare_func (gconstpointer first,gconstpointer second)
name|brush_compare_func
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
name|GimpBrushP
operator|)
name|first
operator|)
operator|->
name|name
argument_list|,
operator|(
operator|(
specifier|const
name|GimpBrushP
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
comment|/*    gimp_set_foreach (brush_list, brushes_free_one, NULL); */
name|gimp_object_destroy
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|brush_list
argument_list|)
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
name|GimpBrushP
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
comment|/* need a gimp_set_get_first() type function */
name|active_brush
operator|=
operator|(
name|GimpBrushP
operator|)
name|GIMP_SET
argument_list|(
name|brush_list
argument_list|)
operator|->
name|list
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
DECL|function|insert_brush_in_list (GSList * list,GimpBrushP brush)
name|insert_brush_in_list
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|,
name|GimpBrushP
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
name|GimpBrushGenerated
modifier|*
name|brush
decl_stmt|;
name|brush
operator|=
name|gimp_brush_generated_new
argument_list|(
literal|5.0
argument_list|,
literal|.5
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
comment|/*  Swap the brush to disk (if we're being stingy with memory) */
if|if
condition|(
name|stingy_memory_use
condition|)
name|temp_buf_swap
argument_list|(
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
operator|->
name|mask
argument_list|)
expr_stmt|;
comment|/*  Make this the default, active brush  */
name|active_brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|have_default_brush
operator|=
literal|1
expr_stmt|;
block|}
end_function

begin_function
name|GimpBrushP
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
name|GimpBrushP
name|brush
init|=
name|NULL
decl_stmt|;
comment|/* fix me: make a gimp_set function that does this */
name|list
operator|=
name|g_slist_nth
argument_list|(
name|GIMP_SET
argument_list|(
name|brush_list
argument_list|)
operator|->
name|list
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
name|GimpBrushP
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
DECL|function|gimp_brush_do_indexes (GimpBrush * brush,int * index)
specifier|static
name|void
name|gimp_brush_do_indexes
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|int
modifier|*
name|index
parameter_list|)
block|{
name|brush
operator|->
name|index
operator|=
operator|(
operator|*
name|index
operator|)
operator|++
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_list_recalc_indexes (GimpBrushList * brush_list)
name|gimp_brush_list_recalc_indexes
parameter_list|(
name|GimpBrushList
modifier|*
name|brush_list
parameter_list|)
block|{
name|int
name|index
init|=
literal|0
decl_stmt|;
name|gimp_set_foreach
argument_list|(
name|GIMP_SET
argument_list|(
name|brush_list
argument_list|)
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_brush_do_indexes
argument_list|,
operator|&
name|index
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_list_add (GimpBrushList * brush_list,GimpBrushP brush)
name|gimp_brush_list_add
parameter_list|(
name|GimpBrushList
modifier|*
name|brush_list
parameter_list|,
name|GimpBrushP
name|brush
parameter_list|)
block|{
name|gimp_set_add
argument_list|(
name|GIMP_SET
argument_list|(
name|brush_list
argument_list|)
argument_list|,
name|brush
argument_list|)
expr_stmt|;
name|brush_list
operator|->
name|num_brushes
operator|++
expr_stmt|;
name|gimp_brush_list_recalc_indexes
argument_list|(
name|brush_list
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_brush (GimpBrushP brush)
name|select_brush
parameter_list|(
name|GimpBrushP
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
name|device_status_update
argument_list|(
name|current_device
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
name|GimpBrushP
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
argument_list|(
name|FALSE
argument_list|)
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
comment|/* access functions */
end_comment

begin_function
name|double
DECL|function|gimp_brush_get_opacity ()
name|gimp_brush_get_opacity
parameter_list|()
block|{
return|return
name|opacity
return|;
block|}
end_function

begin_function
name|int
DECL|function|gimp_brush_get_spacing ()
name|gimp_brush_get_spacing
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
DECL|function|gimp_brush_get_paint_mode ()
name|gimp_brush_get_paint_mode
parameter_list|()
block|{
return|return
name|paint_mode
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_set_opacity (opac)
name|gimp_brush_set_opacity
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
DECL|function|gimp_brush_set_spacing (spac)
name|gimp_brush_set_spacing
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
DECL|function|gimp_brush_set_paint_mode (pm)
name|gimp_brush_set_paint_mode
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
comment|/****************************/
end_comment

begin_comment
comment|/* PDB Interface To Brushes */
end_comment

begin_comment
comment|/****************************/
end_comment

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
name|gimp_brush_get_opacity
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
name|gimp_brush_set_opacity
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
name|gimp_brush_get_spacing
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
name|gimp_brush_set_spacing
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
name|gimp_brush_get_paint_mode
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
literal|"the paint mode: { NORMAL (0), DISSOLVE (1), BEHIND (2), MULTIPLY/BURN (3), SCREEN (4), OVERLAY (5) DIFFERENCE (6), ADDITION (7), SUBTRACT (8), DARKEN-ONLY (9), LIGHTEN-ONLY (10), HUE (11), SATURATION (12), COLOR (13), VALUE (14), DIVIDE/DODGE (15) }"
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
name|gimp_brush_set_paint_mode
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
literal|"the paint mode: { NORMAL (0), DISSOLVE (1), BEHIND (2), MULTIPLY/BURN (3), SCREEN (4), OVERLAY (5) DIFFERENCE (6), ADDITION (7), SUBTRACT (8), DARKEN-ONLY (9), LIGHTEN-ONLY (10), HUE (11), SATURATION (12), COLOR (13), VALUE (14), DIVIDE/DODGE (15) }"
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

begin_function
name|GimpBrushP
DECL|function|gimp_brush_list_get_brush (GimpBrushListP blist,char * name)
name|gimp_brush_list_get_brush
parameter_list|(
name|GimpBrushListP
name|blist
parameter_list|,
name|char
modifier|*
name|name
parameter_list|)
block|{
name|GimpBrushP
name|brushp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
name|blist
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
name|list
operator|=
name|GIMP_SET
argument_list|(
name|brush_list
argument_list|)
operator|->
name|list
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|brushp
operator|=
operator|(
name|GimpBrushP
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
return|return
name|brushp
return|;
block|}
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
end_function

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
name|GimpBrushP
name|brushp
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
name|brushp
operator|=
name|gimp_brush_list_get_brush
argument_list|(
name|brush_list
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|brushp
condition|)
name|select_brush
argument_list|(
name|brushp
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
literal|0
expr_stmt|;
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
name|GimpBrushP
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
name|brush_list
operator|->
name|num_brushes
argument_list|)
expr_stmt|;
name|success
operator|=
operator|(
name|list
operator|=
name|GIMP_SET
argument_list|(
name|brush_list
argument_list|)
operator|->
name|list
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
name|GimpBrushP
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
name|brush_list
operator|->
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

