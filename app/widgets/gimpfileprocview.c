begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfileprocview.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-ins.h"
end_include

begin_include
include|#
directive|include
file|"gimpfileprocview.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2984d0810103
block|{
DECL|enumerator|COLUMN_PROC
name|COLUMN_PROC
block|,
DECL|enumerator|COLUMN_LABEL
name|COLUMN_LABEL
block|,
DECL|enumerator|COLUMN_EXTENSIONS
name|COLUMN_EXTENSIONS
block|,
DECL|enumerator|COLUMN_STOCK_ID
name|COLUMN_STOCK_ID
block|,
DECL|enumerator|COLUMN_PIXBUF
name|COLUMN_PIXBUF
block|,
DECL|enumerator|NUM_COLUMNS
name|NUM_COLUMNS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2984d0810203
block|{
DECL|enumerator|CHANGED
name|CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_file_proc_view_class_init
parameter_list|(
name|GimpFileProcViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_file_proc_view_selection_changed
parameter_list|(
name|GtkTreeSelection
modifier|*
name|selection
parameter_list|,
name|GimpFileProcView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_file_proc_view_iter_compare
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|a
parameter_list|,
name|GtkTreeIter
modifier|*
name|b
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|view_signals
specifier|static
name|guint
name|view_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_file_proc_view_get_type (void)
name|gimp_file_proc_view_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|view_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|view_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|view_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpFileProcViewClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init      */
name|NULL
block|,
comment|/* base_finalize  */
operator|(
name|GClassInitFunc
operator|)
name|gimp_file_proc_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpFileProcView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_TREE_VIEW
argument_list|,
literal|"GimpFileProcView"
argument_list|,
operator|&
name|view_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|view_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_proc_view_class_init (GimpFileProcViewClass * klass)
name|gimp_file_proc_view_class_init
parameter_list|(
name|GimpFileProcViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|klass
operator|->
name|changed
operator|=
name|NULL
expr_stmt|;
name|view_signals
index|[
name|CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpFileProcViewClass
argument_list|,
name|changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_file_proc_view_new (Gimp * gimp,GSList * procedures,const gchar * automatic)
name|gimp_file_proc_view_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GSList
modifier|*
name|procedures
parameter_list|,
specifier|const
name|gchar
modifier|*
name|automatic
parameter_list|)
block|{
name|GtkTreeView
modifier|*
name|view
decl_stmt|;
name|GtkTreeViewColumn
modifier|*
name|column
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|store
operator|=
name|gtk_list_store_new
argument_list|(
name|NUM_COLUMNS
argument_list|,
name|G_TYPE_POINTER
argument_list|,
comment|/* COLUMN_PROC       */
name|G_TYPE_STRING
argument_list|,
comment|/* COLUMN_LABEL      */
name|G_TYPE_STRING
argument_list|,
comment|/* COLUMN_EXTENSIONS */
name|G_TYPE_STRING
argument_list|,
comment|/* COLUMN_STOCK_ID   */
name|GDK_TYPE_PIXBUF
argument_list|)
expr_stmt|;
comment|/* COLUMN_PIXBUF     */
name|gtk_tree_sortable_set_sort_func
argument_list|(
name|GTK_TREE_SORTABLE
argument_list|(
name|store
argument_list|)
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|gimp_file_proc_view_iter_compare
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_sortable_set_sort_column_id
argument_list|(
name|GTK_TREE_SORTABLE
argument_list|(
name|store
argument_list|)
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|GTK_SORT_ASCENDING
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|procedures
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
name|PlugInProcDef
modifier|*
name|proc
init|=
name|list
operator|->
name|data
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|domain
init|=
name|plug_ins_locale_domain
argument_list|(
name|gimp
argument_list|,
name|proc
operator|->
name|prog
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|label
init|=
name|plug_in_proc_def_get_label
argument_list|(
name|proc
argument_list|,
name|domain
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|stock_id
init|=
name|plug_in_proc_def_get_stock_id
argument_list|(
name|proc
argument_list|)
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
init|=
name|plug_in_proc_def_get_pixbuf
argument_list|(
name|proc
argument_list|)
decl_stmt|;
if|if
condition|(
name|label
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
name|gtk_list_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_PROC
argument_list|,
name|proc
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|label
argument_list|,
name|COLUMN_EXTENSIONS
argument_list|,
name|proc
operator|->
name|extensions
argument_list|,
name|COLUMN_STOCK_ID
argument_list|,
name|stock_id
argument_list|,
name|COLUMN_PIXBUF
argument_list|,
name|pixbuf
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|pixbuf
condition|)
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|automatic
condition|)
block|{
name|gtk_list_store_prepend
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_PROC
argument_list|,
name|NULL
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|automatic
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
name|view
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_FILE_PROC_VIEW
argument_list|,
literal|"model"
argument_list|,
name|store
argument_list|,
literal|"rules_hint"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|column
operator|=
name|gtk_tree_view_column_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_set_title
argument_list|(
name|column
argument_list|,
name|_
argument_list|(
literal|"File Type"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_expand
argument_list|(
name|column
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_pixbuf_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_attributes
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
literal|"stock_id"
argument_list|,
name|COLUMN_STOCK_ID
argument_list|,
literal|"pixbuf"
argument_list|,
name|COLUMN_PIXBUF
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_attributes
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
literal|"text"
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_append_column
argument_list|(
name|view
argument_list|,
name|column
argument_list|)
expr_stmt|;
name|column
operator|=
name|gtk_tree_view_column_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_set_title
argument_list|(
name|column
argument_list|,
name|_
argument_list|(
literal|"Extensions"
argument_list|)
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_attributes
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
literal|"text"
argument_list|,
name|COLUMN_EXTENSIONS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_append_column
argument_list|(
name|view
argument_list|,
name|column
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gtk_tree_view_get_selection
argument_list|(
name|view
argument_list|)
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_file_proc_view_selection_changed
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
return|;
block|}
end_function

begin_function
name|PlugInProcDef
modifier|*
DECL|function|gimp_file_proc_view_get_proc (GimpFileProcView * view,gchar ** label)
name|gimp_file_proc_view_get_proc
parameter_list|(
name|GimpFileProcView
modifier|*
name|view
parameter_list|,
name|gchar
modifier|*
modifier|*
name|label
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILE_PROC_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|NULL
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
name|gtk_tree_selection_get_selected
argument_list|(
name|selection
argument_list|,
operator|&
name|model
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|PlugInProcDef
modifier|*
name|proc
decl_stmt|;
if|if
condition|(
name|label
condition|)
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_PROC
argument_list|,
operator|&
name|proc
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|label
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
else|else
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_PROC
argument_list|,
operator|&
name|proc
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|proc
return|;
block|}
if|if
condition|(
name|label
condition|)
name|label
operator|=
name|NULL
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_file_proc_view_set_proc (GimpFileProcView * view,PlugInProcDef * proc)
name|gimp_file_proc_view_set_proc
parameter_list|(
name|GimpFileProcView
modifier|*
name|view
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILE_PROC_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
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
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
control|)
block|{
name|PlugInProcDef
modifier|*
name|this
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_PROC
argument_list|,
operator|&
name|this
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|this
operator|==
name|proc
condition|)
break|break;
block|}
if|if
condition|(
name|iter_valid
condition|)
block|{
name|GtkTreeSelection
modifier|*
name|selection
decl_stmt|;
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
name|gtk_tree_selection_select_iter
argument_list|(
name|selection
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
return|return
name|iter_valid
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_proc_view_selection_changed (GtkTreeSelection * selection,GimpFileProcView * view)
name|gimp_file_proc_view_selection_changed
parameter_list|(
name|GtkTreeSelection
modifier|*
name|selection
parameter_list|,
name|GimpFileProcView
modifier|*
name|view
parameter_list|)
block|{
name|g_signal_emit
argument_list|(
name|view
argument_list|,
name|view_signals
index|[
name|CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_file_proc_view_iter_compare (GtkTreeModel * model,GtkTreeIter * a,GtkTreeIter * b,gpointer data)
name|gimp_file_proc_view_iter_compare
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|a
parameter_list|,
name|GtkTreeIter
modifier|*
name|b
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PlugInProcDef
modifier|*
name|proc_a
decl_stmt|;
name|PlugInProcDef
modifier|*
name|proc_b
decl_stmt|;
name|gchar
modifier|*
name|label_a
decl_stmt|;
name|gchar
modifier|*
name|label_b
decl_stmt|;
name|gint
name|retval
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|a
argument_list|,
name|COLUMN_PROC
argument_list|,
operator|&
name|proc_a
argument_list|,
name|COLUMN_LABEL
argument_list|,
operator|&
name|label_a
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|b
argument_list|,
name|COLUMN_PROC
argument_list|,
operator|&
name|proc_b
argument_list|,
name|COLUMN_LABEL
argument_list|,
operator|&
name|label_b
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_a
operator|&&
name|proc_b
condition|)
block|{
if|if
condition|(
name|strncmp
argument_list|(
name|proc_a
operator|->
name|prog
argument_list|,
literal|"gimp_xcf"
argument_list|,
literal|8
argument_list|)
operator|==
literal|0
condition|)
name|retval
operator|=
operator|-
literal|1
expr_stmt|;
elseif|else
if|if
condition|(
name|strncmp
argument_list|(
name|proc_b
operator|->
name|prog
argument_list|,
literal|"gimp_xcf"
argument_list|,
literal|8
argument_list|)
operator|==
literal|0
condition|)
name|retval
operator|=
literal|1
expr_stmt|;
else|else
name|retval
operator|=
name|g_utf8_collate
argument_list|(
name|label_a
argument_list|,
name|label_b
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|proc_a
condition|)
name|retval
operator|=
literal|1
expr_stmt|;
elseif|else
if|if
condition|(
name|proc_b
condition|)
name|retval
operator|=
operator|-
literal|1
expr_stmt|;
else|else
name|retval
operator|=
literal|0
expr_stmt|;
name|g_free
argument_list|(
name|label_a
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label_b
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

end_unit

