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
file|<math.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushpipe.h"
end_include

begin_include
include|#
directive|include
file|"brush_header.h"
end_include

begin_include
include|#
directive|include
file|"datafiles.h"
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
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimplistP.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushlistP.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
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
DECL|variable|brush_list
name|GimpBrushList
modifier|*
name|brush_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|standard_brush
specifier|static
name|GimpBrush
modifier|*
name|standard_brush
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|brushes_brush_load
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|brush_compare_func
parameter_list|(
name|gconstpointer
name|first
parameter_list|,
name|gconstpointer
name|second
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  class functions  */
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
DECL|function|gimp_brush_list_add_func (GimpList * list,gpointer val)
name|gimp_brush_list_add_func
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|gpointer
name|val
parameter_list|)
block|{
name|list
operator|->
name|list
operator|=
name|g_slist_insert_sorted
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|val
argument_list|,
name|brush_compare_func
argument_list|)
expr_stmt|;
name|GIMP_BRUSH_LIST
argument_list|(
name|list
argument_list|)
operator|->
name|num_brushes
operator|++
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_list_remove_func (GimpList * list,gpointer val)
name|gimp_brush_list_remove_func
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|gpointer
name|val
parameter_list|)
block|{
name|list
operator|->
name|list
operator|=
name|g_slist_remove
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|val
argument_list|)
expr_stmt|;
name|GIMP_BRUSH_LIST
argument_list|(
name|list
argument_list|)
operator|->
name|num_brushes
operator|--
expr_stmt|;
block|}
end_function

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
name|GimpListClass
modifier|*
name|gimp_list_class
decl_stmt|;
name|gimp_list_class
operator|=
name|GIMP_LIST_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_list_class
operator|->
name|add
operator|=
name|gimp_brush_list_add_func
expr_stmt|;
name|gimp_list_class
operator|->
name|remove
operator|=
name|gimp_brush_list_remove_func
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|gimp_list_get_type
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
name|GtkType
DECL|function|gimp_brush_list_get_type (void)
name|gimp_brush_list_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
init|=
literal|0
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
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|type
operator|=
name|gtk_type_unique
argument_list|(
name|gimp_list_get_type
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
decl_stmt|;
name|list
operator|=
name|GIMP_BRUSH_LIST
argument_list|(
name|gtk_type_new
argument_list|(
name|gimp_brush_list_get_type
argument_list|()
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_LIST
argument_list|(
name|list
argument_list|)
operator|->
name|type
operator|=
name|GIMP_TYPE_BRUSH
expr_stmt|;
name|GIMP_LIST
argument_list|(
name|list
argument_list|)
operator|->
name|weak
operator|=
name|FALSE
expr_stmt|;
return|return
name|list
return|;
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
else|else
name|brush_list
operator|=
name|gimp_brush_list_new
argument_list|()
expr_stmt|;
if|if
condition|(
name|brush_path
operator|!=
name|NULL
operator|&&
operator|!
name|no_data
condition|)
name|datafiles_read_directories
argument_list|(
name|brush_path
argument_list|,
operator|(
name|datafile_loader_t
operator|)
name|brushes_brush_load
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_context_refresh_brushes
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|GimpBrush
modifier|*
DECL|function|brushes_get_standard_brush (void)
name|brushes_get_standard_brush
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|standard_brush
condition|)
block|{
name|standard_brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|gimp_brush_generated_new
argument_list|(
literal|5.0
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  set ref_cout to 2 --> never swap the standard brush  */
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|standard_brush
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|standard_brush
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|standard_brush
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brushes_brush_load (gchar * filename)
name|brushes_brush_load
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
operator|&
name|filename
index|[
name|strlen
argument_list|(
name|filename
argument_list|)
operator|-
literal|4
index|]
argument_list|,
literal|".gbr"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|brush
operator|=
name|gimp_brush_new
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|!=
name|NULL
condition|)
name|gimp_brush_list_add
argument_list|(
name|brush_list
argument_list|,
name|brush
argument_list|)
expr_stmt|;
else|else
name|g_message
argument_list|(
literal|"Warning: failed to load brush \"%s\""
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
operator|&
name|filename
index|[
name|strlen
argument_list|(
name|filename
argument_list|)
operator|-
literal|4
index|]
argument_list|,
literal|".vbr"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|GimpBrushGenerated
modifier|*
name|brush
decl_stmt|;
name|brush
operator|=
name|gimp_brush_generated_load
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|!=
name|NULL
condition|)
name|gimp_brush_list_add
argument_list|(
name|brush_list
argument_list|,
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|g_message
argument_list|(
literal|"Warning: failed to load brush \"%s\""
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
operator|&
name|filename
index|[
name|strlen
argument_list|(
name|filename
argument_list|)
operator|-
literal|4
index|]
argument_list|,
literal|".gpb"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|GimpBrushPipe
modifier|*
name|brush
decl_stmt|;
name|brush
operator|=
name|gimp_brush_pixmap_load
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|!=
name|NULL
condition|)
name|gimp_brush_list_add
argument_list|(
name|brush_list
argument_list|,
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|g_message
argument_list|(
literal|"Warning: failed to load pixmap brush \"%s\""
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
operator|&
name|filename
index|[
name|strlen
argument_list|(
name|filename
argument_list|)
operator|-
literal|4
index|]
argument_list|,
literal|".gih"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|GimpBrushPipe
modifier|*
name|brush
decl_stmt|;
name|brush
operator|=
name|gimp_brush_pipe_load
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|!=
name|NULL
condition|)
name|gimp_brush_list_add
argument_list|(
name|brush_list
argument_list|,
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|g_message
argument_list|(
literal|"Warning: failed to load pixmap pipe \"%s\""
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
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
name|GimpBrush
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
name|GimpBrush
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
while|while
condition|(
name|GIMP_LIST
argument_list|(
name|brush_list
argument_list|)
operator|->
name|list
condition|)
block|{
name|GimpBrush
modifier|*
name|b
init|=
name|GIMP_BRUSH
argument_list|(
name|GIMP_LIST
argument_list|(
name|brush_list
argument_list|)
operator|->
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|b
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|g_strdup
argument_list|(
name|b
operator|->
name|filename
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|filename
condition|)
block|{
name|gchar
modifier|*
name|home
decl_stmt|;
name|gchar
modifier|*
name|local_path
decl_stmt|;
name|gchar
modifier|*
name|first_token
decl_stmt|;
name|gchar
modifier|*
name|token
decl_stmt|;
name|gchar
modifier|*
name|path
decl_stmt|;
name|FILE
modifier|*
name|tmp_fp
decl_stmt|;
name|gint
name|unum
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|brush_vbr_path
condition|)
block|{
comment|/* Get the first path specified in the 		       * brush-vbr-path gimprc variable. 		       */
name|home
operator|=
name|g_get_home_dir
argument_list|()
expr_stmt|;
name|local_path
operator|=
name|g_strdup
argument_list|(
name|brush_vbr_path
argument_list|)
expr_stmt|;
name|first_token
operator|=
name|local_path
expr_stmt|;
name|token
operator|=
name|xstrsep
argument_list|(
operator|&
name|first_token
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
condition|)
block|{
if|if
condition|(
operator|*
name|token
operator|==
literal|'~'
condition|)
if|if
condition|(
name|home
operator|!=
name|NULL
condition|)
name|path
operator|=
name|g_strconcat
argument_list|(
name|home
argument_list|,
name|token
operator|+
literal|1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|path
operator|=
name|g_strdup
argument_list|(
literal|""
argument_list|)
expr_stmt|;
comment|/* Better than nothing */
else|else
name|path
operator|=
name|g_strdup
argument_list|(
name|token
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_strconcat
argument_list|(
name|path
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|b
operator|->
name|name
argument_list|,
literal|".vbr"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|tmp_fp
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
comment|/* make sure we don't overite an existing brush */
name|fclose
argument_list|(
name|tmp_fp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s%s%s_%d.vbr"
argument_list|,
name|path
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|b
operator|->
name|name
argument_list|,
name|unum
argument_list|)
expr_stmt|;
name|unum
operator|++
expr_stmt|;
block|}
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|local_path
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|strcmp
argument_list|(
operator|&
name|filename
index|[
name|strlen
argument_list|(
name|filename
argument_list|)
operator|-
literal|4
index|]
argument_list|,
literal|".vbr"
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|filename
operator|=
name|NULL
expr_stmt|;
block|}
block|}
comment|/*  okay we are ready to try to save the generated file  */
if|if
condition|(
name|filename
condition|)
block|{
name|gimp_brush_generated_save
argument_list|(
name|GIMP_BRUSH_GENERATED
argument_list|(
name|b
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_brush_list_remove
argument_list|(
name|brush_list
argument_list|,
name|b
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static GSList * insert_brush_in_list (GSList    *list, 		      GimpBrush *brush) {   return g_slist_insert_sorted (list, brush, brush_compare_func); }
endif|#
directive|endif
end_endif

begin_function
name|gint
DECL|function|gimp_brush_list_get_brush_index (GimpBrushList * brush_list,GimpBrush * brush)
name|gimp_brush_list_get_brush_index
parameter_list|(
name|GimpBrushList
modifier|*
name|brush_list
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
comment|/* fix me: make a gimp_list function that does this? */
return|return
name|g_slist_index
argument_list|(
name|GIMP_LIST
argument_list|(
name|brush_list
argument_list|)
operator|->
name|list
argument_list|,
name|brush
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpBrush
modifier|*
DECL|function|gimp_brush_list_get_brush_by_index (GimpBrushList * brush_list,gint index)
name|gimp_brush_list_get_brush_by_index
parameter_list|(
name|GimpBrushList
modifier|*
name|brush_list
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
comment|/* fix me: make a gimp_list function that does this? */
name|list
operator|=
name|g_slist_nth
argument_list|(
name|GIMP_LIST
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
name|GimpBrush
operator|*
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
specifier|static
name|void
DECL|function|gimp_brush_list_uniquefy_brush_name (GimpBrushList * brush_list,GimpBrush * brush)
name|gimp_brush_list_uniquefy_brush_name
parameter_list|(
name|GimpBrushList
modifier|*
name|brush_list
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|,
modifier|*
name|listb
decl_stmt|;
name|GimpBrush
modifier|*
name|brushb
decl_stmt|;
name|int
name|number
init|=
literal|1
decl_stmt|;
name|char
modifier|*
name|newname
decl_stmt|;
name|char
modifier|*
name|oldname
decl_stmt|;
name|char
modifier|*
name|ext
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH_LIST
argument_list|(
name|brush_list
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|GIMP_LIST
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
name|brushb
operator|=
name|GIMP_BRUSH
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|!=
name|brushb
operator|&&
name|strcmp
argument_list|(
name|gimp_brush_get_name
argument_list|(
name|brush
argument_list|)
argument_list|,
name|gimp_brush_get_name
argument_list|(
name|brushb
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/* names conflict */
name|oldname
operator|=
name|gimp_brush_get_name
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|newname
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|oldname
argument_list|)
operator|+
literal|10
argument_list|)
expr_stmt|;
comment|/* if this aint enough  							 yer screwed */
name|strcpy
argument_list|(
name|newname
argument_list|,
name|oldname
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|ext
operator|=
name|strrchr
argument_list|(
name|newname
argument_list|,
literal|'#'
argument_list|)
operator|)
condition|)
block|{
name|number
operator|=
name|atoi
argument_list|(
name|ext
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|&
name|ext
index|[
call|(
name|int
call|)
argument_list|(
name|log10
argument_list|(
name|number
argument_list|)
operator|+
literal|1
argument_list|)
index|]
operator|!=
operator|&
name|newname
index|[
name|strlen
argument_list|(
name|newname
argument_list|)
operator|-
literal|1
index|]
condition|)
block|{
name|number
operator|=
literal|1
expr_stmt|;
name|ext
operator|=
operator|&
name|newname
index|[
name|strlen
argument_list|(
name|newname
argument_list|)
index|]
expr_stmt|;
block|}
block|}
else|else
block|{
name|number
operator|=
literal|1
expr_stmt|;
name|ext
operator|=
operator|&
name|newname
index|[
name|strlen
argument_list|(
name|newname
argument_list|)
index|]
expr_stmt|;
block|}
name|sprintf
argument_list|(
name|ext
argument_list|,
literal|"#%d"
argument_list|,
name|number
operator|+
literal|1
argument_list|)
expr_stmt|;
name|listb
operator|=
name|GIMP_LIST
argument_list|(
name|brush_list
argument_list|)
operator|->
name|list
expr_stmt|;
while|while
condition|(
name|listb
condition|)
comment|/* make sure the new name is unique */
block|{
name|brushb
operator|=
name|GIMP_BRUSH
argument_list|(
name|listb
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|!=
name|brushb
operator|&&
name|strcmp
argument_list|(
name|newname
argument_list|,
name|gimp_brush_get_name
argument_list|(
name|brushb
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
block|{
name|number
operator|++
expr_stmt|;
name|sprintf
argument_list|(
name|ext
argument_list|,
literal|"#%d"
argument_list|,
name|number
operator|+
literal|1
argument_list|)
expr_stmt|;
name|listb
operator|=
name|GIMP_LIST
argument_list|(
name|brush_list
argument_list|)
operator|->
name|list
expr_stmt|;
block|}
name|listb
operator|=
name|listb
operator|->
name|next
expr_stmt|;
block|}
name|gimp_brush_set_name
argument_list|(
name|brush
argument_list|,
name|newname
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|newname
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_list_have
argument_list|(
name|GIMP_LIST
argument_list|(
name|brush_list
argument_list|)
argument_list|,
name|brush
argument_list|)
condition|)
block|{
comment|/* ought to have a better way than this to resort the brush */
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_brush_list_remove
argument_list|(
name|brush_list
argument_list|,
name|brush
argument_list|)
expr_stmt|;
name|gimp_brush_list_add
argument_list|(
name|brush_list
argument_list|,
name|brush
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return;
block|}
name|list
operator|=
name|list
operator|->
name|next
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_renamed (GimpBrush * brush,GimpBrushList * brush_list)
name|brush_renamed
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpBrushList
modifier|*
name|brush_list
parameter_list|)
block|{
name|gimp_brush_list_uniquefy_brush_name
argument_list|(
name|brush_list
argument_list|,
name|brush
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_list_add (GimpBrushList * brush_list,GimpBrush * brush)
name|gimp_brush_list_add
parameter_list|(
name|GimpBrushList
modifier|*
name|brush_list
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|gimp_brush_list_uniquefy_brush_name
argument_list|(
name|brush_list
argument_list|,
name|brush
argument_list|)
expr_stmt|;
name|gimp_list_add
argument_list|(
name|GIMP_LIST
argument_list|(
name|brush_list
argument_list|)
argument_list|,
name|brush
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|,
literal|"rename"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|brush_renamed
argument_list|)
argument_list|,
name|brush_list
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_list_remove (GimpBrushList * brush_list,GimpBrush * brush)
name|gimp_brush_list_remove
parameter_list|(
name|GimpBrushList
modifier|*
name|brush_list
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|gtk_signal_disconnect_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|,
name|brush_list
argument_list|)
expr_stmt|;
name|gimp_list_remove
argument_list|(
name|GIMP_LIST
argument_list|(
name|brush_list
argument_list|)
argument_list|,
name|brush
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_brush_list_length (GimpBrushList * brush_list)
name|gimp_brush_list_length
parameter_list|(
name|GimpBrushList
modifier|*
name|brush_list
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_LIST
argument_list|(
name|brush_list
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|brush_list
operator|->
name|num_brushes
return|;
block|}
end_function

begin_function
name|GimpBrush
modifier|*
DECL|function|gimp_brush_list_get_brush (GimpBrushList * blist,gchar * name)
name|gimp_brush_list_get_brush
parameter_list|(
name|GimpBrushList
modifier|*
name|blist
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpBrush
modifier|*
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
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|brush_list
argument_list|)
operator|->
name|list
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
name|brushp
operator|=
operator|(
name|GimpBrush
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
name|brushp
operator|->
name|name
argument_list|,
name|name
argument_list|)
condition|)
return|return
name|brushp
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

