begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * utils.c - various utility routines that don't fit anywhere else. Usually  * these routines don't affect the state of the program.  */
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
file|<libgimpconfig/gimpconfig.h>
end_include

begin_include
include|#
directive|include
file|<libgimpmath/gimpmath.h>
end_include

begin_include
include|#
directive|include
file|"gimpressionist.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* Mathematical Utilities */
end_comment

begin_function
name|double
DECL|function|dist (double x,double y,double end_x,double end_y)
name|dist
parameter_list|(
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|,
name|double
name|end_x
parameter_list|,
name|double
name|end_y
parameter_list|)
block|{
name|double
name|dx
init|=
name|end_x
operator|-
name|x
decl_stmt|;
name|double
name|dy
init|=
name|end_y
operator|-
name|y
decl_stmt|;
return|return
name|sqrt
argument_list|(
name|dx
operator|*
name|dx
operator|+
name|dy
operator|*
name|dy
argument_list|)
return|;
block|}
end_function

begin_function
name|double
DECL|function|getsiz_proto (double x,double y,int n,smvector_t * vec,double smstrexp,int voronoi)
name|getsiz_proto
parameter_list|(
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|,
name|int
name|n
parameter_list|,
name|smvector_t
modifier|*
name|vec
parameter_list|,
name|double
name|smstrexp
parameter_list|,
name|int
name|voronoi
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
name|double
name|sum
decl_stmt|,
name|ssum
decl_stmt|,
name|dst
decl_stmt|;
name|int
name|first
init|=
literal|0
decl_stmt|,
name|last
decl_stmt|;
if|if
condition|(
operator|(
name|x
operator|<
literal|0.0
operator|)
operator|||
operator|(
name|x
operator|>
literal|1.0
operator|)
condition|)
name|g_warning
argument_list|(
literal|"HUH? x = %f\n"
argument_list|,
name|x
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|if (from == 0)     {       n = numsmvect;       vec = smvector;       smstrexp = gtk_adjustment_get_value (GTK_ADJUSTMENT (smstrexpadjust));       voronoi = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (size_voronoi));     }   else     {       n = pcvals.num_size_vectors;       vec = pcvals.size_vectors;       smstrexp = pcvals.size_strength_exponent;       voronoi = pcvals.size_voronoi;     }
endif|#
directive|endif
if|if
condition|(
name|voronoi
condition|)
block|{
name|gdouble
name|bestdist
init|=
operator|-
literal|1.0
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n
condition|;
name|i
operator|++
control|)
block|{
name|dst
operator|=
name|dist
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|vec
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|vec
index|[
name|i
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|bestdist
operator|<
literal|0.0
operator|)
operator|||
operator|(
name|dst
operator|<
name|bestdist
operator|)
condition|)
block|{
name|bestdist
operator|=
name|dst
expr_stmt|;
name|first
operator|=
name|i
expr_stmt|;
block|}
block|}
name|last
operator|=
name|first
operator|+
literal|1
expr_stmt|;
block|}
else|else
block|{
name|first
operator|=
literal|0
expr_stmt|;
name|last
operator|=
name|n
expr_stmt|;
block|}
name|sum
operator|=
name|ssum
operator|=
literal|0.0
expr_stmt|;
for|for
control|(
name|i
operator|=
name|first
init|;
name|i
operator|<
name|last
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|s
init|=
name|vec
index|[
name|i
index|]
operator|.
name|str
decl_stmt|;
name|dst
operator|=
name|dist
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|vec
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|vec
index|[
name|i
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
name|dst
operator|=
name|pow
argument_list|(
name|dst
argument_list|,
name|smstrexp
argument_list|)
expr_stmt|;
if|if
condition|(
name|dst
operator|<
literal|0.0001
condition|)
name|dst
operator|=
literal|0.0001
expr_stmt|;
name|s
operator|=
name|s
operator|/
name|dst
expr_stmt|;
name|sum
operator|+=
name|vec
index|[
name|i
index|]
operator|.
name|siz
operator|*
name|s
expr_stmt|;
name|ssum
operator|+=
literal|1.0
operator|/
name|dst
expr_stmt|;
block|}
name|sum
operator|=
name|sum
operator|/
name|ssum
operator|/
literal|100.0
expr_stmt|;
return|return
name|CLAMP
argument_list|(
name|sum
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/* String and Path Manipulation Routines */
end_comment

begin_decl_stmt
DECL|variable|parsepath_cached_path
specifier|static
name|GList
modifier|*
name|parsepath_cached_path
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* This function is memoized. Once it finds the value it permanently  * caches it  * */
end_comment

begin_function
name|GList
modifier|*
DECL|function|parsepath (void)
name|parsepath
parameter_list|(
name|void
parameter_list|)
block|{
name|gchar
modifier|*
name|rc_path
decl_stmt|,
modifier|*
name|path
decl_stmt|;
if|if
condition|(
name|parsepath_cached_path
condition|)
return|return
name|parsepath_cached_path
return|;
name|path
operator|=
name|gimp_gimprc_query
argument_list|(
literal|"gimpressionist-path"
argument_list|)
expr_stmt|;
if|if
condition|(
name|path
condition|)
block|{
name|rc_path
operator|=
name|g_filename_from_utf8
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
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|gimprc
init|=
name|gimp_personal_rc_file
argument_list|(
literal|"gimprc"
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|full_path
init|=
name|gimp_config_build_data_path
argument_list|(
literal|"gimpressionist"
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|esc_path
init|=
name|g_strescape
argument_list|(
name|full_path
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"No %s in gimprc:\n"
literal|"You need to add an entry like\n"
literal|"(%s \"%s\")\n"
literal|"to your %s file."
argument_list|)
argument_list|,
literal|"gflare-path"
argument_list|,
literal|"gflare-path"
argument_list|,
name|esc_path
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|gimprc
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gimprc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|esc_path
argument_list|)
expr_stmt|;
name|rc_path
operator|=
name|gimp_config_path_expand
argument_list|(
name|full_path
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|full_path
argument_list|)
expr_stmt|;
block|}
name|parsepath_cached_path
operator|=
name|gimp_path_parse
argument_list|(
name|rc_path
argument_list|,
literal|16
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rc_path
argument_list|)
expr_stmt|;
return|return
name|parsepath_cached_path
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|my_g_free (gpointer data,gpointer userdata)
name|my_g_free
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|userdata
parameter_list|)
block|{
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|free_parsepath_cache (void)
name|free_parsepath_cache
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|parsepath_cached_path
operator|!=
name|NULL
condition|)
return|return;
name|g_list_foreach
argument_list|(
name|parsepath_cached_path
argument_list|,
name|my_g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|parsepath_cached_path
argument_list|)
expr_stmt|;
name|parsepath_cached_path
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|findfile (const gchar * fn)
name|findfile
parameter_list|(
specifier|const
name|gchar
modifier|*
name|fn
parameter_list|)
block|{
name|GList
modifier|*
name|rcpath
decl_stmt|;
name|GList
modifier|*
name|thispath
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|fn
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|rcpath
operator|=
name|parsepath
argument_list|()
expr_stmt|;
name|thispath
operator|=
name|rcpath
expr_stmt|;
while|while
condition|(
name|thispath
condition|)
block|{
name|filename
operator|=
name|g_build_filename
argument_list|(
name|thispath
operator|->
name|data
argument_list|,
name|fn
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
condition|)
return|return
name|filename
return|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|thispath
operator|=
name|thispath
operator|->
name|next
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/* GUI Routines */
end_comment

begin_function
name|void
DECL|function|reselect (GtkWidget * view,gchar * fname)
name|reselect
parameter_list|(
name|GtkWidget
modifier|*
name|view
parameter_list|,
name|gchar
modifier|*
name|fname
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeSelection
modifier|*
name|selection
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|char
modifier|*
name|tmpfile
decl_stmt|;
name|tmpfile
operator|=
name|strrchr
argument_list|(
name|fname
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
name|tmpfile
condition|)
name|fname
operator|=
operator|++
name|tmpfile
expr_stmt|;
name|model
operator|=
name|gtk_tree_view_get_model
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|selection
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|gboolean
name|quit
init|=
name|FALSE
decl_stmt|;
do|do
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
literal|0
argument_list|,
operator|&
name|name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|fname
argument_list|)
condition|)
block|{
name|GtkTreePath
modifier|*
name|tree_path
decl_stmt|;
name|gtk_tree_selection_select_iter
argument_list|(
name|selection
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|tree_path
operator|=
name|gtk_tree_model_get_path
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_view_scroll_to_cell
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|tree_path
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_tree_path_free
argument_list|(
name|tree_path
argument_list|)
expr_stmt|;
name|quit
operator|=
name|TRUE
expr_stmt|;
block|}
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
operator|(
operator|!
name|quit
operator|)
operator|&&
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
do|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|readdirintolist_real (const char * subdir,GtkWidget * view,char * selected,gboolean with_filename_column,gchar * (* get_object_name_cb)(const gchar * dir,gchar * filename,void * context),void * context)
name|readdirintolist_real
parameter_list|(
specifier|const
name|char
modifier|*
name|subdir
parameter_list|,
name|GtkWidget
modifier|*
name|view
parameter_list|,
name|char
modifier|*
name|selected
parameter_list|,
name|gboolean
name|with_filename_column
parameter_list|,
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_object_name_cb
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|dir
parameter_list|,
name|gchar
modifier|*
name|filename
parameter_list|,
name|void
modifier|*
name|context
parameter_list|)
parameter_list|,
name|void
modifier|*
name|context
parameter_list|)
block|{
name|gchar
modifier|*
name|fpath
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|de
decl_stmt|;
name|GDir
modifier|*
name|dir
decl_stmt|;
name|GList
modifier|*
name|flist
init|=
name|NULL
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GtkTreeSelection
modifier|*
name|selection
decl_stmt|;
name|store
operator|=
name|GTK_LIST_STORE
argument_list|(
name|gtk_tree_view_get_model
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|selected
condition|)
block|{
if|if
condition|(
operator|!
name|selected
index|[
literal|0
index|]
condition|)
name|selected
operator|=
name|NULL
expr_stmt|;
else|else
block|{
name|char
modifier|*
name|nsel
decl_stmt|;
name|nsel
operator|=
name|strrchr
argument_list|(
name|selected
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
name|nsel
condition|)
name|selected
operator|=
operator|++
name|nsel
expr_stmt|;
block|}
block|}
name|dir
operator|=
name|g_dir_open
argument_list|(
name|subdir
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir
condition|)
return|return;
for|for
control|(
init|;
condition|;
control|)
block|{
name|gboolean
name|file_exists
decl_stmt|;
name|de
operator|=
name|g_dir_read_name
argument_list|(
name|dir
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|de
condition|)
break|break;
name|fpath
operator|=
name|g_build_filename
argument_list|(
name|subdir
argument_list|,
name|de
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|file_exists
operator|=
name|g_file_test
argument_list|(
name|fpath
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|fpath
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_exists
condition|)
continue|continue;
name|flist
operator|=
name|g_list_insert_sorted
argument_list|(
name|flist
argument_list|,
name|g_strdup
argument_list|(
name|de
argument_list|)
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|g_ascii_strcasecmp
argument_list|)
expr_stmt|;
block|}
name|g_dir_close
argument_list|(
name|dir
argument_list|)
expr_stmt|;
name|selection
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|flist
condition|)
block|{
name|gtk_list_store_append
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
comment|/* Set the filename */
name|gtk_list_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|PRESETS_LIST_COLUMN_FILENAME
argument_list|,
name|flist
operator|->
name|data
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/* Set the object name */
if|if
condition|(
name|with_filename_column
condition|)
block|{
name|gchar
modifier|*
name|object_name
decl_stmt|;
name|object_name
operator|=
name|get_object_name_cb
argument_list|(
name|subdir
argument_list|,
name|flist
operator|->
name|data
argument_list|,
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|object_name
condition|)
block|{
name|gtk_list_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|PRESETS_LIST_COLUMN_OBJECT_NAME
argument_list|,
name|object_name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|object_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Default to the filename */
name|gtk_list_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
literal|1
argument_list|,
name|flist
operator|->
name|data
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|selected
condition|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|flist
operator|->
name|data
argument_list|,
name|selected
argument_list|)
condition|)
block|{
name|gtk_tree_selection_select_iter
argument_list|(
name|selection
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|flist
operator|->
name|data
argument_list|)
expr_stmt|;
name|flist
operator|=
name|g_list_remove
argument_list|(
name|flist
argument_list|,
name|flist
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|selected
condition|)
block|{
if|if
condition|(
name|gtk_tree_model_get_iter_first
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
name|gtk_tree_selection_select_iter
argument_list|(
name|selection
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|readdirintolist_extended (const char * subdir,GtkWidget * view,char * selected,gboolean with_filename_column,gchar * (* get_object_name_cb)(const gchar * dir,gchar * filename,void * context),void * context)
name|readdirintolist_extended
parameter_list|(
specifier|const
name|char
modifier|*
name|subdir
parameter_list|,
name|GtkWidget
modifier|*
name|view
parameter_list|,
name|char
modifier|*
name|selected
parameter_list|,
name|gboolean
name|with_filename_column
parameter_list|,
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_object_name_cb
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|dir
parameter_list|,
name|gchar
modifier|*
name|filename
parameter_list|,
name|void
modifier|*
name|context
parameter_list|)
parameter_list|,
name|void
modifier|*
name|context
parameter_list|)
block|{
name|char
modifier|*
name|tmpdir
decl_stmt|;
name|GList
modifier|*
name|thispath
init|=
name|parsepath
argument_list|()
decl_stmt|;
while|while
condition|(
name|thispath
condition|)
block|{
name|tmpdir
operator|=
name|g_build_filename
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|thispath
operator|->
name|data
argument_list|,
name|subdir
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|readdirintolist_real
argument_list|(
name|tmpdir
argument_list|,
name|view
argument_list|,
name|selected
argument_list|,
name|with_filename_column
argument_list|,
name|get_object_name_cb
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpdir
argument_list|)
expr_stmt|;
name|thispath
operator|=
name|thispath
operator|->
name|next
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|readdirintolist (const char * subdir,GtkWidget * view,char * selected)
name|readdirintolist
parameter_list|(
specifier|const
name|char
modifier|*
name|subdir
parameter_list|,
name|GtkWidget
modifier|*
name|view
parameter_list|,
name|char
modifier|*
name|selected
parameter_list|)
block|{
name|readdirintolist_extended
argument_list|(
name|subdir
argument_list|,
name|view
argument_list|,
name|selected
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * Creates a radio button.  * box - the containing box.  * orient_type - The orientation ID  * label, help_string - self-describing  * radio_group -  *      A pointer to a radio group. The function assigns its value  *      as the radio group of the radio button. Afterwards, it assigns it  *      a new value of the new radio group of the button.  *      This is useful to group buttons. Just reset the variable to NULL,  *      to create a new group.  * */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|create_radio_button (GtkWidget * box,int orient_type,void (* callback)(GtkWidget * wg,void * d),const gchar * label,const gchar * help_string,GSList ** radio_group,GtkWidget ** buttons_array)
name|create_radio_button
parameter_list|(
name|GtkWidget
modifier|*
name|box
parameter_list|,
name|int
name|orient_type
parameter_list|,
name|void
function_decl|(
modifier|*
name|callback
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|wg
parameter_list|,
name|void
modifier|*
name|d
parameter_list|)
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_string
parameter_list|,
name|GSList
modifier|*
modifier|*
name|radio_group
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|buttons_array
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|tmpw
decl_stmt|;
name|buttons_array
index|[
name|orient_type
index|]
operator|=
name|tmpw
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
operator|(
operator|*
name|radio_group
operator|)
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|tmpw
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|tmpw
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|callback
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|orient_type
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|tmpw
argument_list|,
name|help_string
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|radio_group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|tmpw
return|;
block|}
end_function

end_unit

