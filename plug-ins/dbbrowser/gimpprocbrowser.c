begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * dbbrowser_utils.c  * 0.08  26th sept 97  by Thomas NOEL<thomas@minet.net>  *  * 98/12/13  Sven Neumann<sven@gimp.org> : added help display  */
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
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"gimpprocbox.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocbrowser.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocview.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|RESPONSE_SEARCH
define|#
directive|define
name|RESPONSE_SEARCH
value|1
end_define

begin_define
DECL|macro|RESPONSE_SEARCH_NAME
define|#
directive|define
name|RESPONSE_SEARCH_NAME
value|2
end_define

begin_define
DECL|macro|RESPONSE_SEARCH_BLURB
define|#
directive|define
name|RESPONSE_SEARCH_BLURB
value|3
end_define

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
DECL|enum|__anon2c3f9ddd0103
block|{
DECL|enumerator|COLUMN_LABEL
name|COLUMN_LABEL
block|,
DECL|enumerator|COLUMN_PROC_NAME
name|COLUMN_PROC_NAME
block|,
DECL|enumerator|N_COLUMNS
name|N_COLUMNS
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c3f9ddd0208
block|{
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|count_label
name|GtkWidget
modifier|*
name|count_label
decl_stmt|;
DECL|member|search_entry
name|GtkWidget
modifier|*
name|search_entry
decl_stmt|;
DECL|member|proc_box
name|GtkWidget
modifier|*
name|proc_box
decl_stmt|;
DECL|member|store
name|GtkListStore
modifier|*
name|store
decl_stmt|;
DECL|member|tv
name|GtkWidget
modifier|*
name|tv
decl_stmt|;
DECL|member|sel
name|GtkTreeSelection
modifier|*
name|sel
decl_stmt|;
comment|/* the currently selected procedure */
DECL|member|proc_name
name|gchar
modifier|*
name|proc_name
decl_stmt|;
DECL|member|scheme_proc_name
name|gchar
modifier|*
name|scheme_proc_name
decl_stmt|;
DECL|member|proc_blurb
name|gchar
modifier|*
name|proc_blurb
decl_stmt|;
DECL|member|proc_help
name|gchar
modifier|*
name|proc_help
decl_stmt|;
DECL|member|proc_author
name|gchar
modifier|*
name|proc_author
decl_stmt|;
DECL|member|proc_copyright
name|gchar
modifier|*
name|proc_copyright
decl_stmt|;
DECL|member|proc_date
name|gchar
modifier|*
name|proc_date
decl_stmt|;
DECL|member|proc_type
name|GimpPDBProcType
name|proc_type
decl_stmt|;
DECL|member|n_params
name|gint
name|n_params
decl_stmt|;
DECL|member|n_return_vals
name|gint
name|n_return_vals
decl_stmt|;
DECL|member|params
name|GimpParamDef
modifier|*
name|params
decl_stmt|;
DECL|member|return_vals
name|GimpParamDef
modifier|*
name|return_vals
decl_stmt|;
DECL|member|apply_callback
name|GimpProcBrowserApplyCallback
name|apply_callback
decl_stmt|;
DECL|typedef|GimpDBBrowser
block|}
name|GimpDBBrowser
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|browser_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpDBBrowser
modifier|*
name|browser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_selection_changed
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|GimpDBBrowser
modifier|*
name|browser
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
name|GimpDBBrowser
modifier|*
name|browser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_show_procedure
parameter_list|(
name|GimpDBBrowser
modifier|*
name|browser
parameter_list|,
name|gchar
modifier|*
name|proc_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_convert_string
parameter_list|(
name|gchar
modifier|*
name|str
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_proc_browser_dialog_new (GimpProcBrowserApplyCallback apply_callback)
name|gimp_proc_browser_dialog_new
parameter_list|(
name|GimpProcBrowserApplyCallback
name|apply_callback
parameter_list|)
block|{
name|GimpDBBrowser
modifier|*
name|browser
decl_stmt|;
name|GtkWidget
modifier|*
name|paned
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_window
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|renderer
decl_stmt|;
name|browser
operator|=
name|g_new0
argument_list|(
name|GimpDBBrowser
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|browser
operator|->
name|apply_callback
operator|=
name|apply_callback
expr_stmt|;
if|if
condition|(
name|apply_callback
condition|)
block|{
name|browser
operator|->
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Procedure Browser"
argument_list|)
argument_list|,
literal|"dbbrowser"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"plug-in-db-browser"
argument_list|,
name|_
argument_list|(
literal|"Search by _Name"
argument_list|)
argument_list|,
name|RESPONSE_SEARCH_NAME
argument_list|,
name|_
argument_list|(
literal|"Search by _Blurb"
argument_list|)
argument_list|,
name|RESPONSE_SEARCH_BLURB
argument_list|,
name|GTK_STOCK_APPLY
argument_list|,
name|GTK_RESPONSE_APPLY
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|browser
operator|->
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Procedure Browser"
argument_list|)
argument_list|,
literal|"dbbrowser"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"plug-in-db-browser"
argument_list|,
name|_
argument_list|(
literal|"Search by _Name"
argument_list|)
argument_list|,
name|RESPONSE_SEARCH_NAME
argument_list|,
name|_
argument_list|(
literal|"Search by _Blurb"
argument_list|)
argument_list|,
name|RESPONSE_SEARCH_BLURB
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|browser
operator|->
name|dialog
argument_list|)
argument_list|,
name|RESPONSE_SEARCH_NAME
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|browser
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_response
argument_list|)
argument_list|,
name|browser
argument_list|)
expr_stmt|;
comment|/* paned : left=list ; right=description */
name|paned
operator|=
name|gtk_hpaned_new
argument_list|()
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|paned
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
name|browser
operator|->
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|paned
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|paned
argument_list|)
expr_stmt|;
comment|/* left = vbox : the list and the search entry */
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_paned_pack1
argument_list|(
name|GTK_PANED
argument_list|(
name|paned
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|browser
operator|->
name|count_label
operator|=
name|gtk_label_new
argument_list|(
literal|"0 Procedures"
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|browser
operator|->
name|count_label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|browser
operator|->
name|count_label
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
name|browser
operator|->
name|count_label
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
name|vbox
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
name|browser
operator|->
name|tv
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
name|browser
operator|->
name|tv
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
name|browser
operator|->
name|tv
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|apply_callback
condition|)
name|g_signal_connect
argument_list|(
name|browser
operator|->
name|tv
argument_list|,
literal|"row_activated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_row_activated
argument_list|)
argument_list|,
name|browser
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|browser
operator|->
name|tv
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
name|browser
operator|->
name|tv
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|browser
operator|->
name|tv
argument_list|)
expr_stmt|;
name|browser
operator|->
name|sel
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|browser
operator|->
name|tv
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|browser
operator|->
name|sel
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_selection_changed
argument_list|)
argument_list|,
name|browser
argument_list|)
expr_stmt|;
comment|/* search entry */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Search:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|browser
operator|->
name|search_entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_entry_set_activates_default
argument_list|(
name|GTK_ENTRY
argument_list|(
name|browser
operator|->
name|search_entry
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|browser
operator|->
name|search_entry
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
name|browser
operator|->
name|search_entry
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|browser
operator|->
name|search_entry
argument_list|)
expr_stmt|;
comment|/* right = description */
name|browser
operator|->
name|proc_box
operator|=
name|gimp_proc_box_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|browser
operator|->
name|proc_box
argument_list|,
name|DBL_WIDTH
operator|-
name|DBL_LIST_WIDTH
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_paned_pack2
argument_list|(
name|GTK_PANED
argument_list|(
name|paned
argument_list|)
argument_list|,
name|browser
operator|->
name|proc_box
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|browser
operator|->
name|proc_box
argument_list|)
expr_stmt|;
comment|/* now build the list */
name|gtk_widget_show
argument_list|(
name|browser
operator|->
name|dialog
argument_list|)
expr_stmt|;
comment|/* initialize the "return" value (for "apply") */
name|browser
operator|->
name|proc_name
operator|=
name|NULL
expr_stmt|;
name|browser
operator|->
name|scheme_proc_name
operator|=
name|NULL
expr_stmt|;
name|browser
operator|->
name|proc_blurb
operator|=
name|NULL
expr_stmt|;
name|browser
operator|->
name|proc_help
operator|=
name|NULL
expr_stmt|;
name|browser
operator|->
name|proc_author
operator|=
name|NULL
expr_stmt|;
name|browser
operator|->
name|proc_copyright
operator|=
name|NULL
expr_stmt|;
name|browser
operator|->
name|proc_date
operator|=
name|NULL
expr_stmt|;
name|browser
operator|->
name|proc_type
operator|=
literal|0
expr_stmt|;
name|browser
operator|->
name|n_params
operator|=
literal|0
expr_stmt|;
name|browser
operator|->
name|n_return_vals
operator|=
literal|0
expr_stmt|;
name|browser
operator|->
name|params
operator|=
name|NULL
expr_stmt|;
name|browser
operator|->
name|return_vals
operator|=
name|NULL
expr_stmt|;
comment|/* first search (all procedures) */
name|browser_response
argument_list|(
name|browser
operator|->
name|dialog
argument_list|,
name|RESPONSE_SEARCH
argument_list|,
name|browser
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|browser
operator|->
name|search_entry
argument_list|)
expr_stmt|;
return|return
name|browser
operator|->
name|dialog
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|browser_selection_changed (GtkTreeSelection * sel,GimpDBBrowser * browser)
name|browser_selection_changed
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|GimpDBBrowser
modifier|*
name|browser
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
name|browser
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
name|browser
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_row_activated (GtkTreeView * treeview,GtkTreePath * path,GtkTreeViewColumn * column,GimpDBBrowser * browser)
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
name|GimpDBBrowser
modifier|*
name|browser
parameter_list|)
block|{
name|browser_response
argument_list|(
name|browser
operator|->
name|dialog
argument_list|,
name|GTK_RESPONSE_APPLY
argument_list|,
name|browser
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_show_procedure (GimpDBBrowser * browser,gchar * proc_name)
name|browser_show_procedure
parameter_list|(
name|GimpDBBrowser
modifier|*
name|browser
parameter_list|,
name|gchar
modifier|*
name|proc_name
parameter_list|)
block|{
name|g_free
argument_list|(
name|browser
operator|->
name|proc_name
argument_list|)
expr_stmt|;
name|browser
operator|->
name|proc_name
operator|=
name|g_strdup
argument_list|(
name|proc_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|browser
operator|->
name|scheme_proc_name
argument_list|)
expr_stmt|;
name|browser
operator|->
name|scheme_proc_name
operator|=
name|g_strdup
argument_list|(
name|proc_name
argument_list|)
expr_stmt|;
name|browser_convert_string
argument_list|(
name|browser
operator|->
name|scheme_proc_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|browser
operator|->
name|proc_blurb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|browser
operator|->
name|proc_help
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|browser
operator|->
name|proc_author
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|browser
operator|->
name|proc_copyright
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|browser
operator|->
name|proc_date
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|browser
operator|->
name|params
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|browser
operator|->
name|return_vals
argument_list|)
expr_stmt|;
name|gimp_procedural_db_proc_info
argument_list|(
name|proc_name
argument_list|,
operator|&
name|browser
operator|->
name|proc_blurb
argument_list|,
operator|&
name|browser
operator|->
name|proc_help
argument_list|,
operator|&
name|browser
operator|->
name|proc_author
argument_list|,
operator|&
name|browser
operator|->
name|proc_copyright
argument_list|,
operator|&
name|browser
operator|->
name|proc_date
argument_list|,
operator|&
name|browser
operator|->
name|proc_type
argument_list|,
operator|&
name|browser
operator|->
name|n_params
argument_list|,
operator|&
name|browser
operator|->
name|n_return_vals
argument_list|,
operator|&
name|browser
operator|->
name|params
argument_list|,
operator|&
name|browser
operator|->
name|return_vals
argument_list|)
expr_stmt|;
name|gimp_proc_box_set_widget
argument_list|(
name|browser
operator|->
name|proc_box
argument_list|,
name|gimp_proc_view_new
argument_list|(
name|browser
operator|->
name|scheme_proc_name
argument_list|,
name|NULL
argument_list|,
name|browser
operator|->
name|proc_blurb
argument_list|,
name|browser
operator|->
name|proc_help
argument_list|,
name|browser
operator|->
name|proc_author
argument_list|,
name|browser
operator|->
name|proc_copyright
argument_list|,
name|browser
operator|->
name|proc_date
argument_list|,
name|browser
operator|->
name|proc_type
argument_list|,
name|browser
operator|->
name|n_params
argument_list|,
name|browser
operator|->
name|n_return_vals
argument_list|,
name|browser
operator|->
name|params
argument_list|,
name|browser
operator|->
name|return_vals
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_response (GtkWidget * widget,gint response_id,GimpDBBrowser * browser)
name|browser_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpDBBrowser
modifier|*
name|browser
parameter_list|)
block|{
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|GTK_RESPONSE_APPLY
case|:
name|browser
operator|->
name|apply_callback
argument_list|(
name|browser
operator|->
name|proc_name
argument_list|,
name|browser
operator|->
name|scheme_proc_name
argument_list|,
name|browser
operator|->
name|proc_blurb
argument_list|,
name|browser
operator|->
name|proc_help
argument_list|,
name|browser
operator|->
name|proc_author
argument_list|,
name|browser
operator|->
name|proc_copyright
argument_list|,
name|browser
operator|->
name|proc_date
argument_list|,
name|browser
operator|->
name|proc_type
argument_list|,
name|browser
operator|->
name|n_params
argument_list|,
name|browser
operator|->
name|n_return_vals
argument_list|,
name|browser
operator|->
name|params
argument_list|,
name|browser
operator|->
name|return_vals
argument_list|)
expr_stmt|;
break|break;
case|case
name|RESPONSE_SEARCH
case|:
case|case
name|RESPONSE_SEARCH_NAME
case|:
case|case
name|RESPONSE_SEARCH_BLURB
case|:
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
name|gint
name|i
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|query_text
decl_stmt|;
name|GString
modifier|*
name|query
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gtk_tree_view_set_model
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|browser
operator|->
name|tv
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* search */
if|if
condition|(
name|response_id
operator|==
name|RESPONSE_SEARCH_NAME
condition|)
block|{
name|gimp_proc_box_show_message
argument_list|(
name|browser
operator|->
name|proc_box
argument_list|,
name|_
argument_list|(
literal|"Searching by name - please wait"
argument_list|)
argument_list|)
expr_stmt|;
name|query
operator|=
name|g_string_new
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|query_text
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|browser
operator|->
name|search_entry
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
operator|*
name|query_text
condition|)
block|{
if|if
condition|(
operator|(
operator|*
name|query_text
operator|==
literal|'_'
operator|)
operator|||
operator|(
operator|*
name|query_text
operator|==
literal|'-'
operator|)
condition|)
name|g_string_append
argument_list|(
name|query
argument_list|,
literal|"[-_]"
argument_list|)
expr_stmt|;
else|else
name|g_string_append_c
argument_list|(
name|query
argument_list|,
operator|*
name|query_text
argument_list|)
expr_stmt|;
name|query_text
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
elseif|else
if|if
condition|(
name|response_id
operator|==
name|RESPONSE_SEARCH_BLURB
condition|)
block|{
name|gimp_proc_box_show_message
argument_list|(
name|browser
operator|->
name|proc_box
argument_list|,
name|_
argument_list|(
literal|"Searching by blurb - please wait"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedural_db_query
argument_list|(
literal|".*"
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|browser
operator|->
name|search_entry
argument_list|)
argument_list|)
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
block|}
else|else
block|{
name|gimp_proc_box_show_message
argument_list|(
name|browser
operator|->
name|proc_box
argument_list|,
name|_
argument_list|(
literal|"Searching - please wait"
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
block|}
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%d Procedures"
argument_list|)
argument_list|,
name|num_procs
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
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|browser
operator|->
name|store
operator|=
name|gtk_list_store_new
argument_list|(
name|N_COLUMNS
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
name|gtk_tree_view_set_model
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|browser
operator|->
name|tv
argument_list|)
argument_list|,
name|GTK_TREE_MODEL
argument_list|(
name|browser
operator|->
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|browser
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
name|gchar
modifier|*
name|label
decl_stmt|;
name|label
operator|=
name|g_strdup
argument_list|(
name|proc_list
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|browser_convert_string
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_list_store_append
argument_list|(
name|browser
operator|->
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|browser
operator|->
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|label
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
name|label
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
name|browser
operator|->
name|tv
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_tree_sortable_set_sort_column_id
argument_list|(
name|GTK_TREE_SORTABLE
argument_list|(
name|browser
operator|->
name|store
argument_list|)
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|GTK_SORT_ASCENDING
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_procs
operator|>
literal|0
condition|)
block|{
name|gtk_tree_model_get_iter_root
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|browser
operator|->
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_selection_select_iter
argument_list|(
name|browser
operator|->
name|sel
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_proc_box_show_message
argument_list|(
name|browser
operator|->
name|proc_box
argument_list|,
name|_
argument_list|(
literal|"No matches"
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
default|default:
if|if
condition|(
name|browser
operator|->
name|apply_callback
condition|)
block|{
comment|/* we are called by another application:            * just destroy the dialog box            */
name|gtk_widget_destroy
argument_list|(
name|browser
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* we are in the plug_in:            * quit the gtk application            */
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_convert_string (gchar * str)
name|browser_convert_string
parameter_list|(
name|gchar
modifier|*
name|str
parameter_list|)
block|{
while|while
condition|(
operator|*
name|str
condition|)
block|{
if|if
condition|(
operator|*
name|str
operator|==
literal|'_'
condition|)
operator|*
name|str
operator|=
literal|'-'
expr_stmt|;
name|str
operator|++
expr_stmt|;
block|}
block|}
end_function

end_unit

