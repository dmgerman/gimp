begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpprocbrowserdialog.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpuitypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocbrowserdialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocview.h"
end_include

begin_include
include|#
directive|include
file|"libgimp-intl.h"
end_include

begin_define
DECL|macro|DBL_LIST_WIDTH
define|#
directive|define
name|DBL_LIST_WIDTH
value|250
end_define

begin_define
DECL|macro|DBL_WIDTH
define|#
directive|define
name|DBL_WIDTH
value|(DBL_LIST_WIDTH + 400)
end_define

begin_define
DECL|macro|DBL_HEIGHT
define|#
directive|define
name|DBL_HEIGHT
value|250
end_define

begin_enum
enum|enum
DECL|enum|__anon2c08919a0103
block|{
DECL|enumerator|SELECTION_CHANGED
name|SELECTION_CHANGED
block|,
DECL|enumerator|ROW_ACTIVATED
name|ROW_ACTIVATED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c08919a0203
block|{
DECL|enumerator|SEARCH_TYPE_ALL
name|SEARCH_TYPE_ALL
block|,
DECL|enumerator|SEARCH_TYPE_NAME
name|SEARCH_TYPE_NAME
block|,
DECL|enumerator|SEARCH_TYPE_BLURB
name|SEARCH_TYPE_BLURB
block|,
DECL|enumerator|SEARCH_TYPE_HELP
name|SEARCH_TYPE_HELP
block|,
DECL|enumerator|SEARCH_TYPE_AUTHOR
name|SEARCH_TYPE_AUTHOR
block|,
DECL|enumerator|SEARCH_TYPE_COPYRIGHT
name|SEARCH_TYPE_COPYRIGHT
block|,
DECL|enumerator|SEARCH_TYPE_DATE
name|SEARCH_TYPE_DATE
block|,
DECL|enumerator|SEARCH_TYPE_PROC_TYPE
name|SEARCH_TYPE_PROC_TYPE
DECL|typedef|SearchType
block|}
name|SearchType
typedef|;
end_typedef

begin_enum
enum|enum
DECL|enum|__anon2c08919a0303
block|{
DECL|enumerator|COLUMN_PROC_NAME
name|COLUMN_PROC_NAME
block|,
DECL|enumerator|N_COLUMNS
name|N_COLUMNS
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|browser_selection_changed
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|GimpProcBrowserDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_row_activated
parameter_list|(
name|GtkTreeView
modifier|*
name|treeview
parameter_list|,
name|GtkTreePath
modifier|*
name|path
parameter_list|,
name|GtkTreeViewColumn
modifier|*
name|column
parameter_list|,
name|GimpProcBrowserDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_show_procedure
parameter_list|(
name|GimpProcBrowserDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_search
parameter_list|(
name|GimpBrowser
modifier|*
name|browser
parameter_list|,
specifier|const
name|gchar
modifier|*
name|query_text
parameter_list|,
name|gint
name|search_type
parameter_list|,
name|GimpProcBrowserDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpProcBrowserDialog
argument_list|,
argument|gimp_proc_browser_dialog
argument_list|,
argument|GIMP_TYPE_DIALOG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_proc_browser_dialog_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|dialog_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_proc_browser_dialog_class_init (GimpProcBrowserDialogClass * klass)
name|gimp_proc_browser_dialog_class_init
parameter_list|(
name|GimpProcBrowserDialogClass
modifier|*
name|klass
parameter_list|)
block|{
comment|/**    * GimpProcBrowserDialog::selection-changed:    * @dialog: the object that received the signal    *    * Emitted when the selection in the contained #GtkTreeView changes.    */
name|dialog_signals
index|[
name|SELECTION_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"selection-changed"
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
name|GimpProcBrowserDialogClass
argument_list|,
name|selection_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/**    * GimpProcBrowserDialog::row-activated:    * @dialog: the object that received the signal    *    * Emitted when one of the rows in the contained #GtkTreeView is activated.    */
name|dialog_signals
index|[
name|ROW_ACTIVATED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"row-activated"
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
name|GimpProcBrowserDialogClass
argument_list|,
name|row_activated
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|klass
operator|->
name|selection_changed
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|row_activated
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_proc_browser_dialog_init (GimpProcBrowserDialog * dialog)
name|gimp_proc_browser_dialog_init
parameter_list|(
name|GimpProcBrowserDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|scrolled_window
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|renderer
decl_stmt|;
name|GtkTreeSelection
modifier|*
name|selection
decl_stmt|;
name|dialog
operator|->
name|browser
operator|=
name|gimp_browser_new
argument_list|()
expr_stmt|;
name|gimp_browser_add_search_types
argument_list|(
name|GIMP_BROWSER
argument_list|(
name|dialog
operator|->
name|browser
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"by name"
argument_list|)
argument_list|,
name|SEARCH_TYPE_NAME
argument_list|,
name|_
argument_list|(
literal|"by description"
argument_list|)
argument_list|,
name|SEARCH_TYPE_BLURB
argument_list|,
name|_
argument_list|(
literal|"by help"
argument_list|)
argument_list|,
name|SEARCH_TYPE_HELP
argument_list|,
name|_
argument_list|(
literal|"by author"
argument_list|)
argument_list|,
name|SEARCH_TYPE_AUTHOR
argument_list|,
name|_
argument_list|(
literal|"by copyright"
argument_list|)
argument_list|,
name|SEARCH_TYPE_COPYRIGHT
argument_list|,
name|_
argument_list|(
literal|"by date"
argument_list|)
argument_list|,
name|SEARCH_TYPE_DATE
argument_list|,
name|_
argument_list|(
literal|"by type"
argument_list|)
argument_list|,
name|SEARCH_TYPE_PROC_TYPE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dialog
operator|->
name|browser
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|dialog
operator|->
name|browser
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|browser
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|browser
argument_list|,
literal|"search"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_search
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
comment|/* list : list in a scrolled_win */
name|scrolled_window
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_shadow_type
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_ALWAYS
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GIMP_BROWSER
argument_list|(
name|dialog
operator|->
name|browser
argument_list|)
operator|->
name|left_vbox
argument_list|)
argument_list|,
name|scrolled_window
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scrolled_window
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|tree_view
operator|=
name|gtk_tree_view_new
argument_list|()
expr_stmt|;
name|renderer
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|gtk_cell_renderer_text_set_fixed_height_from_font
argument_list|(
name|GTK_CELL_RENDERER_TEXT
argument_list|(
name|renderer
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_tree_view_insert_column_with_attributes
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|dialog
operator|->
name|tree_view
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|renderer
argument_list|,
literal|"text"
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_set_headers_visible
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|dialog
operator|->
name|tree_view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|tree_view
argument_list|,
literal|"row_activated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_row_activated
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|dialog
operator|->
name|tree_view
argument_list|,
name|DBL_LIST_WIDTH
argument_list|,
name|DBL_HEIGHT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|dialog
operator|->
name|tree_view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|tree_view
argument_list|)
expr_stmt|;
name|selection
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|dialog
operator|->
name|tree_view
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|selection
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_selection_changed
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|GIMP_BROWSER
argument_list|(
name|dialog
operator|->
name|browser
argument_list|)
operator|->
name|right_vbox
operator|->
name|parent
operator|->
name|parent
argument_list|,
name|DBL_WIDTH
operator|-
name|DBL_LIST_WIDTH
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_proc_browser_dialog_new:  * @title:     The dialog's title.  * @role:      The dialog's role, see gtk_window_set_role().  * @help_func: The function which will be called if the user presses "F1".  * @help_id:   The help_id which will be passed to @help_func.  * @...:       A %NULL-terminated list destribing the action_area buttons.  *  * Create a new #GimpProcBrowserDialog.  *  * Return Value: a newly created #GimpProcBrowserDialog.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_proc_browser_dialog_new (const gchar * title,const gchar * role,GimpHelpFunc help_func,const gchar * help_id,...)
name|gimp_proc_browser_dialog_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GimpProcBrowserDialog
modifier|*
name|dialog
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PROC_BROWSER_DIALOG
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
literal|"role"
argument_list|,
name|role
argument_list|,
literal|"help-func"
argument_list|,
name|help_func
argument_list|,
literal|"help-id"
argument_list|,
name|help_id
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dialog_add_buttons_valist
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
comment|/* first search (all procedures) */
name|browser_search
argument_list|(
name|GIMP_BROWSER
argument_list|(
name|dialog
operator|->
name|browser
argument_list|)
argument_list|,
literal|""
argument_list|,
name|SEARCH_TYPE_ALL
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_proc_browser_dialog_get_selected:  * @dialog: a #GimpProcBrowserDialog  *  * Retrieves the name of the currently selected procedure.  *  * Return Value: The name of the selected procedure of %NULL if no  *               procedure is selected.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_proc_browser_dialog_get_selected (GimpProcBrowserDialog * dialog)
name|gimp_proc_browser_dialog_get_selected
parameter_list|(
name|GimpProcBrowserDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GtkTreeSelection
modifier|*
name|sel
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROC_BROWSER_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|sel
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|dialog
operator|->
name|tree_view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_selection_get_selected
argument_list|(
name|sel
argument_list|,
name|NULL
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|proc_name
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|dialog
operator|->
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_PROC_NAME
argument_list|,
operator|&
name|proc_name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|proc_name
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|browser_selection_changed (GtkTreeSelection * sel,GimpProcBrowserDialog * dialog)
name|browser_selection_changed
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|GimpProcBrowserDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
name|gtk_tree_selection_get_selected
argument_list|(
name|sel
argument_list|,
name|NULL
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|proc_name
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|dialog
operator|->
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_PROC_NAME
argument_list|,
operator|&
name|proc_name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|browser_show_procedure
argument_list|(
name|dialog
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_name
argument_list|)
expr_stmt|;
block|}
name|g_signal_emit
argument_list|(
name|dialog
argument_list|,
name|dialog_signals
index|[
name|SELECTION_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_row_activated (GtkTreeView * treeview,GtkTreePath * path,GtkTreeViewColumn * column,GimpProcBrowserDialog * dialog)
name|browser_row_activated
parameter_list|(
name|GtkTreeView
modifier|*
name|treeview
parameter_list|,
name|GtkTreePath
modifier|*
name|path
parameter_list|,
name|GtkTreeViewColumn
modifier|*
name|column
parameter_list|,
name|GimpProcBrowserDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|g_signal_emit
argument_list|(
name|dialog
argument_list|,
name|dialog_signals
index|[
name|ROW_ACTIVATED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_show_procedure (GimpProcBrowserDialog * dialog,const gchar * proc_name)
name|browser_show_procedure
parameter_list|(
name|GimpProcBrowserDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|)
block|{
name|gchar
modifier|*
name|proc_blurb
decl_stmt|;
name|gchar
modifier|*
name|proc_help
decl_stmt|;
name|gchar
modifier|*
name|proc_author
decl_stmt|;
name|gchar
modifier|*
name|proc_copyright
decl_stmt|;
name|gchar
modifier|*
name|proc_date
decl_stmt|;
name|GimpPDBProcType
name|proc_type
decl_stmt|;
name|gint
name|n_params
decl_stmt|;
name|gint
name|n_return_vals
decl_stmt|;
name|GimpParamDef
modifier|*
name|params
decl_stmt|;
name|GimpParamDef
modifier|*
name|return_vals
decl_stmt|;
name|gimp_procedural_db_proc_info
argument_list|(
name|proc_name
argument_list|,
operator|&
name|proc_blurb
argument_list|,
operator|&
name|proc_help
argument_list|,
operator|&
name|proc_author
argument_list|,
operator|&
name|proc_copyright
argument_list|,
operator|&
name|proc_date
argument_list|,
operator|&
name|proc_type
argument_list|,
operator|&
name|n_params
argument_list|,
operator|&
name|n_return_vals
argument_list|,
operator|&
name|params
argument_list|,
operator|&
name|return_vals
argument_list|)
expr_stmt|;
name|gimp_browser_set_widget
argument_list|(
name|GIMP_BROWSER
argument_list|(
name|dialog
operator|->
name|browser
argument_list|)
argument_list|,
name|gimp_proc_view_new
argument_list|(
name|proc_name
argument_list|,
name|NULL
argument_list|,
name|proc_blurb
argument_list|,
name|proc_help
argument_list|,
name|proc_author
argument_list|,
name|proc_copyright
argument_list|,
name|proc_date
argument_list|,
name|proc_type
argument_list|,
name|n_params
argument_list|,
name|n_return_vals
argument_list|,
name|params
argument_list|,
name|return_vals
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_blurb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_help
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_author
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_copyright
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_date
argument_list|)
expr_stmt|;
name|gimp_destroy_paramdefs
argument_list|(
name|params
argument_list|,
name|n_params
argument_list|)
expr_stmt|;
name|gimp_destroy_paramdefs
argument_list|(
name|return_vals
argument_list|,
name|n_return_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_search (GimpBrowser * browser,const gchar * query_text,gint search_type,GimpProcBrowserDialog * dialog)
name|browser_search
parameter_list|(
name|GimpBrowser
modifier|*
name|browser
parameter_list|,
specifier|const
name|gchar
modifier|*
name|query_text
parameter_list|,
name|gint
name|search_type
parameter_list|,
name|GimpProcBrowserDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|gchar
modifier|*
modifier|*
name|proc_list
decl_stmt|;
name|gint
name|num_procs
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|GRegex
modifier|*
name|regex
decl_stmt|;
comment|/*  first check if the query is a valid regex  */
name|regex
operator|=
name|g_regex_new
argument_list|(
name|query_text
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|regex
condition|)
block|{
name|gtk_tree_view_set_model
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|dialog
operator|->
name|tree_view
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|store
operator|=
name|NULL
expr_stmt|;
name|gimp_browser_show_message
argument_list|(
name|browser
argument_list|,
name|_
argument_list|(
literal|"No matches"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|browser
operator|->
name|count_label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Search term invalid or incomplete"
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|g_regex_unref
argument_list|(
name|regex
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|search_type
condition|)
block|{
case|case
name|SEARCH_TYPE_ALL
case|:
name|gimp_browser_show_message
argument_list|(
name|browser
argument_list|,
name|_
argument_list|(
literal|"Searching"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedural_db_query
argument_list|(
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
operator|&
name|num_procs
argument_list|,
operator|&
name|proc_list
argument_list|)
expr_stmt|;
break|break;
case|case
name|SEARCH_TYPE_NAME
case|:
block|{
name|GString
modifier|*
name|query
init|=
name|g_string_new
argument_list|(
literal|""
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|q
init|=
name|query_text
decl_stmt|;
name|gimp_browser_show_message
argument_list|(
name|browser
argument_list|,
name|_
argument_list|(
literal|"Searching by name"
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
operator|*
name|q
condition|)
block|{
if|if
condition|(
operator|(
operator|*
name|q
operator|==
literal|'_'
operator|)
operator|||
operator|(
operator|*
name|q
operator|==
literal|'-'
operator|)
condition|)
name|g_string_append
argument_list|(
name|query
argument_list|,
literal|"-"
argument_list|)
expr_stmt|;
else|else
name|g_string_append_c
argument_list|(
name|query
argument_list|,
operator|*
name|q
argument_list|)
expr_stmt|;
name|q
operator|++
expr_stmt|;
block|}
name|gimp_procedural_db_query
argument_list|(
name|query
operator|->
name|str
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
operator|&
name|num_procs
argument_list|,
operator|&
name|proc_list
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|query
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|SEARCH_TYPE_BLURB
case|:
name|gimp_browser_show_message
argument_list|(
name|browser
argument_list|,
name|_
argument_list|(
literal|"Searching by description"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedural_db_query
argument_list|(
literal|".*"
argument_list|,
name|query_text
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
operator|&
name|num_procs
argument_list|,
operator|&
name|proc_list
argument_list|)
expr_stmt|;
break|break;
case|case
name|SEARCH_TYPE_HELP
case|:
name|gimp_browser_show_message
argument_list|(
name|browser
argument_list|,
name|_
argument_list|(
literal|"Searching by help"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedural_db_query
argument_list|(
literal|".*"
argument_list|,
literal|".*"
argument_list|,
name|query_text
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
operator|&
name|num_procs
argument_list|,
operator|&
name|proc_list
argument_list|)
expr_stmt|;
break|break;
case|case
name|SEARCH_TYPE_AUTHOR
case|:
name|gimp_browser_show_message
argument_list|(
name|browser
argument_list|,
name|_
argument_list|(
literal|"Searching by author"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedural_db_query
argument_list|(
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
name|query_text
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
operator|&
name|num_procs
argument_list|,
operator|&
name|proc_list
argument_list|)
expr_stmt|;
break|break;
case|case
name|SEARCH_TYPE_COPYRIGHT
case|:
name|gimp_browser_show_message
argument_list|(
name|browser
argument_list|,
name|_
argument_list|(
literal|"Searching by copyright"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedural_db_query
argument_list|(
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
name|query_text
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
operator|&
name|num_procs
argument_list|,
operator|&
name|proc_list
argument_list|)
expr_stmt|;
break|break;
case|case
name|SEARCH_TYPE_DATE
case|:
name|gimp_browser_show_message
argument_list|(
name|browser
argument_list|,
name|_
argument_list|(
literal|"Searching by date"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedural_db_query
argument_list|(
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
name|query_text
argument_list|,
literal|".*"
argument_list|,
operator|&
name|num_procs
argument_list|,
operator|&
name|proc_list
argument_list|)
expr_stmt|;
break|break;
case|case
name|SEARCH_TYPE_PROC_TYPE
case|:
name|gimp_browser_show_message
argument_list|(
name|browser
argument_list|,
name|_
argument_list|(
literal|"Searching by type"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedural_db_query
argument_list|(
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
name|query_text
argument_list|,
operator|&
name|num_procs
argument_list|,
operator|&
name|proc_list
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|!
name|query_text
operator|||
name|strlen
argument_list|(
name|query_text
argument_list|)
operator|==
literal|0
condition|)
block|{
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|dngettext
argument_list|(
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|,
literal|"%d procedure"
argument_list|,
literal|"%d procedures"
argument_list|,
name|num_procs
argument_list|)
argument_list|,
name|num_procs
argument_list|)
expr_stmt|;
block|}
else|else
block|{
switch|switch
condition|(
name|num_procs
condition|)
block|{
case|case
literal|0
case|:
name|str
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"No matches for your query"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|dngettext
argument_list|(
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|,
literal|"%d procedure matches your query"
argument_list|,
literal|"%d procedures match your query"
argument_list|,
name|num_procs
argument_list|)
argument_list|,
name|num_procs
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|browser
operator|->
name|count_label
argument_list|)
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_procs
operator|>
literal|0
condition|)
block|{
name|GtkTreeSelection
modifier|*
name|selection
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|dialog
operator|->
name|store
operator|=
name|gtk_list_store_new
argument_list|(
name|N_COLUMNS
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
name|gtk_tree_view_set_model
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|dialog
operator|->
name|tree_view
argument_list|)
argument_list|,
name|GTK_TREE_MODEL
argument_list|(
name|dialog
operator|->
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dialog
operator|->
name|store
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_procs
condition|;
name|i
operator|++
control|)
block|{
name|gtk_list_store_append
argument_list|(
name|dialog
operator|->
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|dialog
operator|->
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_PROC_NAME
argument_list|,
name|proc_list
index|[
name|i
index|]
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_list
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|proc_list
argument_list|)
expr_stmt|;
name|gtk_tree_view_columns_autosize
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|dialog
operator|->
name|tree_view
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_tree_sortable_set_sort_column_id
argument_list|(
name|GTK_TREE_SORTABLE
argument_list|(
name|dialog
operator|->
name|store
argument_list|)
argument_list|,
name|COLUMN_PROC_NAME
argument_list|,
name|GTK_SORT_ASCENDING
argument_list|)
expr_stmt|;
name|gtk_tree_model_get_iter_first
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|dialog
operator|->
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|selection
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|dialog
operator|->
name|tree_view
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
else|else
block|{
name|gtk_tree_view_set_model
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|dialog
operator|->
name|tree_view
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|store
operator|=
name|NULL
expr_stmt|;
name|gimp_browser_show_message
argument_list|(
name|browser
argument_list|,
name|_
argument_list|(
literal|"No matches"
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

