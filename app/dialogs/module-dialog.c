begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * module-browser.c  * (C) 1999 Austin Donnelly<austin@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmoduleinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmodules.h"
end_include

begin_include
include|#
directive|include
file|"module-browser.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|NUM_INFO_LINES
define|#
directive|define
name|NUM_INFO_LINES
value|7
end_define

begin_enum
DECL|enum|__anon2c2bc47c0103
enum|enum
block|{
DECL|enumerator|PATH_COLUMN
name|PATH_COLUMN
block|,
DECL|enumerator|INFO_COLUMN
name|INFO_COLUMN
block|,
DECL|enumerator|NUM_COLUMNS
name|NUM_COLUMNS
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c2bc47c0208
block|{
DECL|member|table
name|GtkWidget
modifier|*
name|table
decl_stmt|;
DECL|member|label
name|GtkWidget
modifier|*
name|label
index|[
name|NUM_INFO_LINES
index|]
decl_stmt|;
DECL|member|button_label
name|GtkWidget
modifier|*
name|button_label
decl_stmt|;
DECL|member|last_update
name|GimpModuleInfoObj
modifier|*
name|last_update
decl_stmt|;
DECL|member|button
name|GtkWidget
modifier|*
name|button
decl_stmt|;
DECL|member|list
name|GtkListStore
modifier|*
name|list
decl_stmt|;
DECL|member|load_inhibit_check
name|GtkWidget
modifier|*
name|load_inhibit_check
decl_stmt|;
DECL|member|modules_handler_id
name|GQuark
name|modules_handler_id
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|typedef|BrowserState
block|}
name|BrowserState
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|browser_popdown_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_destroy_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_load_inhibit_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_select_callback
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_load_unload_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_refresh_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|make_list_item
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_info_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpModuleInfoObj
modifier|*
name|mod
parameter_list|,
name|BrowserState
modifier|*
name|st
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_info_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpModuleInfoObj
modifier|*
name|mod
parameter_list|,
name|BrowserState
modifier|*
name|st
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_info_update
parameter_list|(
name|GimpModuleInfoObj
modifier|*
name|mod
parameter_list|,
name|BrowserState
modifier|*
name|st
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_info_init
parameter_list|(
name|BrowserState
modifier|*
name|st
parameter_list|,
name|GtkWidget
modifier|*
name|table
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|module_browser_new (Gimp * gimp)
name|module_browser_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|shell
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
name|listbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|tv
decl_stmt|;
name|BrowserState
modifier|*
name|st
decl_stmt|;
name|GtkTreeSelection
modifier|*
name|sel
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
name|shell
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Module DB"
argument_list|)
argument_list|,
literal|"module_db_dialog"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/module_browser.html"
argument_list|,
name|GTK_WIN_POS_NONE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|browser_popdown_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|listbox
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|listbox
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|listbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|listbox
argument_list|,
literal|125
argument_list|,
literal|100
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|listbox
argument_list|)
expr_stmt|;
name|st
operator|=
name|g_new0
argument_list|(
name|BrowserState
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|st
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|st
operator|->
name|list
operator|=
name|gtk_list_store_new
argument_list|(
name|NUM_COLUMNS
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|tv
operator|=
name|gtk_tree_view_new_with_model
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|st
operator|->
name|list
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|st
operator|->
name|list
argument_list|)
expr_stmt|;
name|gimp_container_foreach
argument_list|(
name|gimp
operator|->
name|modules
argument_list|,
name|make_list_item
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|gtk_tree_view_insert_column_with_attributes
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|tv
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|gtk_cell_renderer_text_new
argument_list|()
argument_list|,
literal|"text"
argument_list|,
name|PATH_COLUMN
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_set_headers_visible
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|tv
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|listbox
argument_list|)
argument_list|,
name|tv
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tv
argument_list|)
expr_stmt|;
name|st
operator|->
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|5
argument_list|,
name|NUM_INFO_LINES
operator|+
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|st
operator|->
name|table
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|st
operator|->
name|table
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
name|st
operator|->
name|table
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbutton_box_new
argument_list|()
expr_stmt|;
name|gtk_button_box_set_layout
argument_list|(
name|GTK_BUTTON_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|GTK_BUTTONBOX_SPREAD
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
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
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Refresh"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_refresh_callback
argument_list|)
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|st
operator|->
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|st
operator|->
name|button_label
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|st
operator|->
name|button
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
name|st
operator|->
name|button
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
name|st
operator|->
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|st
operator|->
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_load_unload_callback
argument_list|)
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|browser_info_init
argument_list|(
name|st
argument_list|,
name|st
operator|->
name|table
argument_list|)
expr_stmt|;
name|browser_info_update
argument_list|(
name|st
operator|->
name|last_update
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|sel
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|tv
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|sel
argument_list|)
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_select_callback
argument_list|)
argument_list|,
name|st
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter_root
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|st
operator|->
name|list
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
name|gtk_tree_selection_select_iter
argument_list|(
name|sel
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
comment|/* hook the GimpContainer signals so we can refresh the display    * appropriately.    */
name|st
operator|->
name|modules_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|gimp
operator|->
name|modules
argument_list|,
literal|"modified"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_info_update
argument_list|)
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
operator|->
name|modules
argument_list|)
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_info_add
argument_list|)
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
operator|->
name|modules
argument_list|)
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_info_remove
argument_list|)
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_destroy_callback
argument_list|)
argument_list|,
name|st
argument_list|)
expr_stmt|;
return|return
name|shell
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|browser_popdown_callback (GtkWidget * widget,gpointer data)
name|browser_popdown_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_destroy_callback (GtkWidget * widget,gpointer data)
name|browser_destroy_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrowserState
modifier|*
name|st
init|=
name|data
decl_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|st
operator|->
name|gimp
operator|->
name|modules
argument_list|)
argument_list|,
name|browser_info_add
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|st
operator|->
name|gimp
operator|->
name|modules
argument_list|)
argument_list|,
name|browser_info_remove
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_container_remove_handler
argument_list|(
name|st
operator|->
name|gimp
operator|->
name|modules
argument_list|,
name|st
operator|->
name|modules_handler_id
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_load_inhibit_callback (GtkWidget * widget,gpointer data)
name|browser_load_inhibit_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrowserState
modifier|*
name|st
init|=
name|data
decl_stmt|;
name|gboolean
name|new_value
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|st
operator|->
name|last_update
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|new_value
operator|=
operator|!
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
expr_stmt|;
if|if
condition|(
name|new_value
operator|==
name|st
operator|->
name|last_update
operator|->
name|load_inhibit
condition|)
return|return;
name|st
operator|->
name|last_update
operator|->
name|load_inhibit
operator|=
name|new_value
expr_stmt|;
name|gimp_module_info_modified
argument_list|(
name|st
operator|->
name|last_update
argument_list|)
expr_stmt|;
name|st
operator|->
name|gimp
operator|->
name|write_modulerc
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_select_callback (GtkTreeSelection * sel,gpointer data)
name|browser_select_callback
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrowserState
modifier|*
name|st
init|=
name|data
decl_stmt|;
name|GimpModuleInfoObj
modifier|*
name|info
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gtk_tree_selection_get_selected
argument_list|(
name|sel
argument_list|,
name|NULL
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|st
operator|->
name|list
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|INFO_COLUMN
argument_list|,
operator|&
name|info
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|st
operator|->
name|last_update
operator|==
name|info
condition|)
return|return;
name|st
operator|->
name|last_update
operator|=
name|info
expr_stmt|;
name|browser_info_update
argument_list|(
name|st
operator|->
name|last_update
argument_list|,
name|st
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_load_unload_callback (GtkWidget * widget,gpointer data)
name|browser_load_unload_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrowserState
modifier|*
name|st
init|=
name|data
decl_stmt|;
if|if
condition|(
name|st
operator|->
name|last_update
operator|->
name|state
operator|==
name|GIMP_MODULE_STATE_LOADED_OK
condition|)
name|gimp_module_info_module_unload
argument_list|(
name|st
operator|->
name|last_update
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
else|else
name|gimp_module_info_module_load
argument_list|(
name|st
operator|->
name|last_update
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_module_info_modified
argument_list|(
name|st
operator|->
name|last_update
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_refresh_callback (GtkWidget * widget,gpointer data)
name|browser_refresh_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrowserState
modifier|*
name|st
init|=
name|data
decl_stmt|;
name|gimp_modules_refresh
argument_list|(
name|st
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|make_list_item (gpointer data,gpointer user_data)
name|make_list_item
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpModuleInfoObj
modifier|*
name|info
init|=
name|data
decl_stmt|;
name|BrowserState
modifier|*
name|st
init|=
name|user_data
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
operator|!
name|st
operator|->
name|last_update
condition|)
name|st
operator|->
name|last_update
operator|=
name|info
expr_stmt|;
name|gtk_list_store_append
argument_list|(
name|st
operator|->
name|list
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|st
operator|->
name|list
argument_list|,
operator|&
name|iter
argument_list|,
name|PATH_COLUMN
argument_list|,
name|info
operator|->
name|fullpath
argument_list|,
name|INFO_COLUMN
argument_list|,
name|info
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_info_add (GimpContainer * container,GimpModuleInfoObj * mod,BrowserState * st)
name|browser_info_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpModuleInfoObj
modifier|*
name|mod
parameter_list|,
name|BrowserState
modifier|*
name|st
parameter_list|)
block|{
name|make_list_item
argument_list|(
name|mod
argument_list|,
name|st
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_info_remove (GimpContainer * container,GimpModuleInfoObj * mod,BrowserState * st)
name|browser_info_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpModuleInfoObj
modifier|*
name|mod
parameter_list|,
name|BrowserState
modifier|*
name|st
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|GimpModuleInfoObj
modifier|*
name|info
decl_stmt|;
comment|/* FIXME: Use gtk_list_store_foreach_remove when it becomes available */
if|if
condition|(
operator|!
name|gtk_tree_model_get_iter_root
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|st
operator|->
name|list
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
return|return;
do|do
block|{
name|gtk_tree_model_get
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|st
operator|->
name|list
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|INFO_COLUMN
argument_list|,
operator|&
name|info
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|==
name|mod
condition|)
block|{
name|gtk_list_store_remove
argument_list|(
name|st
operator|->
name|list
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
do|while
condition|(
name|gtk_tree_model_iter_next
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|st
operator|->
name|list
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
do|;
name|g_warning
argument_list|(
literal|"tried to remove module that wasn't in brower's list"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_info_update (GimpModuleInfoObj * mod,BrowserState * st)
name|browser_info_update
parameter_list|(
name|GimpModuleInfoObj
modifier|*
name|mod
parameter_list|,
name|BrowserState
modifier|*
name|st
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|text
index|[
name|NUM_INFO_LINES
operator|-
literal|1
index|]
decl_stmt|;
name|gchar
modifier|*
name|status
decl_stmt|;
specifier|static
specifier|const
name|gchar
modifier|*
specifier|const
name|statename
index|[]
init|=
block|{
name|N_
argument_list|(
literal|"Module error"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Loaded OK"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Load failed"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Unload requested"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Unloaded OK"
argument_list|)
block|}
decl_stmt|;
comment|/* only update the info if we're actually showing it */
if|if
condition|(
name|mod
operator|!=
name|st
operator|->
name|last_update
condition|)
return|return;
if|if
condition|(
operator|!
name|mod
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|NUM_INFO_LINES
condition|;
name|i
operator|++
control|)
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|st
operator|->
name|label
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|st
operator|->
name|button_label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"<No modules>"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|st
operator|->
name|button
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|st
operator|->
name|load_inhibit_check
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|mod
operator|->
name|info
condition|)
block|{
name|text
index|[
literal|0
index|]
operator|=
name|mod
operator|->
name|info
operator|->
name|purpose
expr_stmt|;
name|text
index|[
literal|1
index|]
operator|=
name|mod
operator|->
name|info
operator|->
name|author
expr_stmt|;
name|text
index|[
literal|2
index|]
operator|=
name|mod
operator|->
name|info
operator|->
name|version
expr_stmt|;
name|text
index|[
literal|3
index|]
operator|=
name|mod
operator|->
name|info
operator|->
name|copyright
expr_stmt|;
name|text
index|[
literal|4
index|]
operator|=
name|mod
operator|->
name|info
operator|->
name|date
expr_stmt|;
name|text
index|[
literal|5
index|]
operator|=
name|mod
operator|->
name|on_disk
condition|?
name|_
argument_list|(
literal|"on disk"
argument_list|)
else|:
name|_
argument_list|(
literal|"only in memory"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|text
index|[
literal|0
index|]
operator|=
literal|"--"
expr_stmt|;
name|text
index|[
literal|1
index|]
operator|=
literal|"--"
expr_stmt|;
name|text
index|[
literal|2
index|]
operator|=
literal|"--"
expr_stmt|;
name|text
index|[
literal|3
index|]
operator|=
literal|"--"
expr_stmt|;
name|text
index|[
literal|4
index|]
operator|=
literal|"--"
expr_stmt|;
name|text
index|[
literal|5
index|]
operator|=
name|mod
operator|->
name|on_disk
condition|?
name|_
argument_list|(
literal|"on disk"
argument_list|)
else|:
name|_
argument_list|(
literal|"nowhere (click 'refresh')"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|mod
operator|->
name|state
operator|==
name|GIMP_MODULE_STATE_ERROR
operator|&&
name|mod
operator|->
name|last_module_error
condition|)
block|{
name|status
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s (%s)"
argument_list|,
name|gettext
argument_list|(
name|statename
index|[
name|mod
operator|->
name|state
index|]
argument_list|)
argument_list|,
name|mod
operator|->
name|last_module_error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|g_strdup
argument_list|(
name|gettext
argument_list|(
name|statename
index|[
name|mod
operator|->
name|state
index|]
argument_list|)
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|NUM_INFO_LINES
operator|-
literal|1
condition|;
name|i
operator|++
control|)
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|st
operator|->
name|label
index|[
name|i
index|]
argument_list|)
argument_list|,
name|gettext
argument_list|(
name|text
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|st
operator|->
name|label
index|[
name|NUM_INFO_LINES
operator|-
literal|1
index|]
argument_list|)
argument_list|,
name|status
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|status
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|st
operator|->
name|load_inhibit_check
argument_list|)
argument_list|,
operator|!
name|mod
operator|->
name|load_inhibit
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|st
operator|->
name|load_inhibit_check
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* work out what the button should do (if anything) */
switch|switch
condition|(
name|mod
operator|->
name|state
condition|)
block|{
case|case
name|GIMP_MODULE_STATE_ERROR
case|:
case|case
name|GIMP_MODULE_STATE_LOAD_FAILED
case|:
case|case
name|GIMP_MODULE_STATE_UNLOADED_OK
case|:
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|st
operator|->
name|button_label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Load"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|st
operator|->
name|button
argument_list|)
argument_list|,
name|mod
operator|->
name|on_disk
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_MODULE_STATE_UNLOAD_REQUESTED
case|:
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|st
operator|->
name|button_label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Unload"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|st
operator|->
name|button
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_MODULE_STATE_LOADED_OK
case|:
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|st
operator|->
name|button_label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Unload"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|st
operator|->
name|button
argument_list|)
argument_list|,
name|mod
operator|->
name|unload
condition|?
name|TRUE
else|:
name|FALSE
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_info_init (BrowserState * st,GtkWidget * table)
name|browser_info_init
parameter_list|(
name|BrowserState
modifier|*
name|st
parameter_list|,
name|GtkWidget
modifier|*
name|table
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gchar
modifier|*
name|text
index|[]
init|=
block|{
name|N_
argument_list|(
literal|"Purpose:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Author:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Version:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Copyright:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Date:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Location:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"State:"
argument_list|)
block|}
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
sizeof|sizeof
argument_list|(
name|text
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|char
operator|*
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|label
operator|=
name|gtk_label_new
argument_list|(
name|gettext
argument_list|(
name|text
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|1
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|st
operator|->
name|label
index|[
name|i
index|]
operator|=
name|gtk_label_new
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|st
operator|->
name|label
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|st
operator|->
name|table
argument_list|)
argument_list|,
name|st
operator|->
name|label
index|[
name|i
index|]
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|1
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|st
operator|->
name|label
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|st
operator|->
name|load_inhibit_check
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Autoload during startup"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|st
operator|->
name|load_inhibit_check
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|st
operator|->
name|load_inhibit_check
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|1
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|st
operator|->
name|load_inhibit_check
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_load_inhibit_callback
argument_list|)
argument_list|,
name|st
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

