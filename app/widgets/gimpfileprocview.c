begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfileprocview.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<gegl.h>
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
file|"plug-in/gimppluginprocedure.h"
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
DECL|enum|__anon29eab9da0103
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
DECL|enumerator|COLUMN_HELP_ID
name|COLUMN_HELP_ID
block|,
DECL|enumerator|N_COLUMNS
name|N_COLUMNS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon29eab9da0203
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
name|gimp_file_proc_view_finalize
parameter_list|(
name|GObject
modifier|*
name|object
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

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFileProcView
argument_list|,
argument|gimp_file_proc_view
argument_list|,
argument|GTK_TYPE_TREE_VIEW
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_file_proc_view_parent_class
end_define

begin_decl_stmt
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
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_file_proc_view_finalize
expr_stmt|;
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
specifier|static
name|void
DECL|function|gimp_file_proc_view_init (GimpFileProcView * view)
name|gimp_file_proc_view_init
parameter_list|(
name|GimpFileProcView
modifier|*
name|view
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_proc_view_finalize (GObject * object)
name|gimp_file_proc_view_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFileProcView
modifier|*
name|view
init|=
name|GIMP_FILE_PROC_VIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|view
operator|->
name|meta_extensions
condition|)
block|{
name|g_list_free_full
argument_list|(
name|view
operator|->
name|meta_extensions
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|view
operator|->
name|meta_extensions
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_file_proc_view_new (Gimp * gimp,GSList * procedures,const gchar * automatic,const gchar * automatic_help_id)
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
parameter_list|,
specifier|const
name|gchar
modifier|*
name|automatic_help_id
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
name|N_COLUMNS
argument_list|,
name|GIMP_TYPE_PLUG_IN_PROCEDURE
argument_list|,
comment|/*  COLUMN_PROC   */
name|G_TYPE_STRING
argument_list|,
comment|/*  COLUMN_LABEL       */
name|G_TYPE_STRING
argument_list|,
comment|/*  COLUMN_EXTENSIONS  */
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
comment|/*  COLUMN_HELP_ID     */
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
literal|"rules-hint"
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
name|GimpPlugInProcedure
modifier|*
name|proc
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|!
name|proc
operator|->
name|prefixes_list
condition|)
comment|/*  skip URL loaders  */
block|{
specifier|const
name|gchar
modifier|*
name|label
init|=
name|gimp_procedure_get_label
argument_list|(
name|GIMP_PROCEDURE
argument_list|(
name|proc
argument_list|)
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|help_id
init|=
name|gimp_procedure_get_help_id
argument_list|(
name|GIMP_PROCEDURE
argument_list|(
name|proc
argument_list|)
argument_list|)
decl_stmt|;
name|GSList
modifier|*
name|list2
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
name|COLUMN_HELP_ID
argument_list|,
name|help_id
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|list2
operator|=
name|proc
operator|->
name|extensions_list
init|;
name|list2
condition|;
name|list2
operator|=
name|g_slist_next
argument_list|(
name|list2
argument_list|)
control|)
block|{
name|GimpFileProcView
modifier|*
name|proc_view
init|=
name|GIMP_FILE_PROC_VIEW
argument_list|(
name|view
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|ext
init|=
name|list2
operator|->
name|data
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|dot
init|=
name|strchr
argument_list|(
name|ext
argument_list|,
literal|'.'
argument_list|)
decl_stmt|;
if|if
condition|(
name|dot
operator|&&
name|dot
operator|!=
name|ext
condition|)
name|proc_view
operator|->
name|meta_extensions
operator|=
name|g_list_append
argument_list|(
name|proc_view
operator|->
name|meta_extensions
argument_list|,
name|g_strdup
argument_list|(
name|dot
operator|+
literal|1
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
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
name|COLUMN_HELP_ID
argument_list|,
name|automatic_help_id
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
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
name|GimpPlugInProcedure
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
name|GimpPlugInProcedure
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
if|if
condition|(
name|proc
condition|)
name|g_object_unref
argument_list|(
name|proc
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
operator|*
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
DECL|function|gimp_file_proc_view_set_proc (GimpFileProcView * view,GimpPlugInProcedure * proc)
name|gimp_file_proc_view_set_proc
parameter_list|(
name|GimpFileProcView
modifier|*
name|view
parameter_list|,
name|GimpPlugInProcedure
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
name|GimpPlugInProcedure
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
condition|)
name|g_object_unref
argument_list|(
name|this
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
name|gchar
modifier|*
DECL|function|gimp_file_proc_view_get_help_id (GimpFileProcView * view)
name|gimp_file_proc_view_get_help_id
parameter_list|(
name|GimpFileProcView
modifier|*
name|view
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
name|gchar
modifier|*
name|help_id
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_HELP_ID
argument_list|,
operator|&
name|help_id
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|help_id
return|;
block|}
return|return
name|NULL
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

end_unit

