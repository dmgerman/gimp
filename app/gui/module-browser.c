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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmodule/gimpmodule.h"
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
file|"core/gimp-modules.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"module-browser.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|NUM_INFO_LINES
define|#
directive|define
name|NUM_INFO_LINES
value|9
end_define

begin_enum
enum|enum
DECL|enum|__anon2b4525190103
block|{
DECL|enumerator|PATH_COLUMN
name|PATH_COLUMN
block|,
DECL|enumerator|AUTO_COLUMN
name|AUTO_COLUMN
block|,
DECL|enumerator|MODULE_COLUMN
name|MODULE_COLUMN
block|,
DECL|enumerator|NUM_COLUMNS
name|NUM_COLUMNS
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|ModuleBrowser
typedef|typedef
name|struct
name|_ModuleBrowser
name|ModuleBrowser
typedef|;
end_typedef

begin_struct
DECL|struct|_ModuleBrowser
struct|struct
name|_ModuleBrowser
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|last_update
name|GimpModule
modifier|*
name|last_update
decl_stmt|;
DECL|member|list
name|GtkListStore
modifier|*
name|list
decl_stmt|;
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
DECL|member|button
name|GtkWidget
modifier|*
name|button
decl_stmt|;
DECL|member|button_label
name|GtkWidget
modifier|*
name|button_label
decl_stmt|;
block|}
struct|;
end_struct

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
name|ModuleBrowser
modifier|*
name|browser
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
name|ModuleBrowser
modifier|*
name|browser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_autoload_toggled
parameter_list|(
name|GtkCellRendererToggle
modifier|*
name|celltoggle
parameter_list|,
name|gchar
modifier|*
name|path_string
parameter_list|,
name|ModuleBrowser
modifier|*
name|browser
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
name|ModuleBrowser
modifier|*
name|browser
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
name|ModuleBrowser
modifier|*
name|browser
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
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
name|GimpModule
modifier|*
name|module
parameter_list|,
name|ModuleBrowser
modifier|*
name|browser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_info_remove
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
name|GimpModule
modifier|*
name|module
parameter_list|,
name|ModuleBrowser
modifier|*
name|browser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_info_update
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
name|GimpModule
modifier|*
name|module
parameter_list|,
name|ModuleBrowser
modifier|*
name|browser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|browser_info_init
parameter_list|(
name|ModuleBrowser
modifier|*
name|browser
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
name|tv
decl_stmt|;
name|ModuleBrowser
modifier|*
name|browser
decl_stmt|;
name|GtkTreeSelection
modifier|*
name|sel
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|GtkTreeViewColumn
modifier|*
name|col
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|rend
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
name|browser
operator|=
name|g_new0
argument_list|(
name|ModuleBrowser
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|browser
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|shell
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Module Manager"
argument_list|)
argument_list|,
literal|"module_db_dialog"
argument_list|,
name|GTK_STOCK_EXECUTE
argument_list|,
name|_
argument_list|(
literal|"Manage Loadable Modules"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_MODULE_DIALOG
argument_list|,
name|GTK_STOCK_REFRESH
argument_list|,
name|browser_refresh_callback
argument_list|,
name|browser
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CLOSE
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
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|6
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
name|gtk_scrolled_window_set_shadow_type
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|listbox
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
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
name|gtk_widget_set_size_request
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
name|browser
operator|->
name|list
operator|=
name|gtk_list_store_new
argument_list|(
name|NUM_COLUMNS
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_BOOLEAN
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
name|browser
operator|->
name|list
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|browser
operator|->
name|list
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|gimp
operator|->
name|module_db
operator|->
name|modules
argument_list|,
name|make_list_item
argument_list|,
name|browser
argument_list|)
expr_stmt|;
name|rend
operator|=
name|gtk_cell_renderer_toggle_new
argument_list|()
expr_stmt|;
name|g_signal_connect
argument_list|(
name|rend
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_autoload_toggled
argument_list|)
argument_list|,
name|browser
argument_list|)
expr_stmt|;
name|col
operator|=
name|gtk_tree_view_column_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_set_title
argument_list|(
name|col
argument_list|,
name|_
argument_list|(
literal|"Autoload"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|col
argument_list|,
name|rend
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_add_attribute
argument_list|(
name|col
argument_list|,
name|rend
argument_list|,
literal|"active"
argument_list|,
name|AUTO_COLUMN
argument_list|)
expr_stmt|;
name|gtk_tree_view_append_column
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|tv
argument_list|)
argument_list|,
name|col
argument_list|)
expr_stmt|;
name|rend
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|col
operator|=
name|gtk_tree_view_column_new_with_attributes
argument_list|(
name|_
argument_list|(
literal|"Module Path"
argument_list|)
argument_list|,
name|rend
argument_list|,
literal|"text"
argument_list|,
name|PATH_COLUMN
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_append_column
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|tv
argument_list|)
argument_list|,
name|col
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
name|browser
operator|->
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
name|NUM_INFO_LINES
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|browser
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
name|browser
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
name|browser
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
name|browser
operator|->
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|browser
operator|->
name|button_label
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|browser
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
name|browser
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
name|browser
operator|->
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|browser
operator|->
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_load_unload_callback
argument_list|)
argument_list|,
name|browser
argument_list|)
expr_stmt|;
name|browser_info_init
argument_list|(
name|browser
argument_list|,
name|browser
operator|->
name|table
argument_list|)
expr_stmt|;
name|browser_info_update
argument_list|(
name|gimp
operator|->
name|module_db
argument_list|,
name|browser
operator|->
name|last_update
argument_list|,
name|browser
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
name|sel
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_select_callback
argument_list|)
argument_list|,
name|browser
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter_root
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|browser
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
comment|/* hook the GimpModuleDB signals so we can refresh the display    * appropriately.    */
name|g_signal_connect
argument_list|(
name|gimp
operator|->
name|module_db
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_info_add
argument_list|)
argument_list|,
name|browser
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimp
operator|->
name|module_db
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_info_remove
argument_list|)
argument_list|,
name|browser
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimp
operator|->
name|module_db
argument_list|,
literal|"module_modified"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_info_update
argument_list|)
argument_list|,
name|browser
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|shell
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|browser_destroy_callback
argument_list|)
argument_list|,
name|browser
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
DECL|function|browser_destroy_callback (GtkWidget * widget,ModuleBrowser * browser)
name|browser_destroy_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|ModuleBrowser
modifier|*
name|browser
parameter_list|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|browser
operator|->
name|gimp
operator|->
name|module_db
argument_list|,
name|browser_info_add
argument_list|,
name|browser
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|browser
operator|->
name|gimp
operator|->
name|module_db
argument_list|,
name|browser_info_remove
argument_list|,
name|browser
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|browser
operator|->
name|gimp
operator|->
name|module_db
argument_list|,
name|browser_info_update
argument_list|,
name|browser
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|browser
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_select_callback (GtkTreeSelection * sel,ModuleBrowser * browser)
name|browser_select_callback
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|ModuleBrowser
modifier|*
name|browser
parameter_list|)
block|{
name|GimpModule
modifier|*
name|module
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
name|browser
operator|->
name|list
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|MODULE_COLUMN
argument_list|,
operator|&
name|module
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|browser
operator|->
name|last_update
operator|==
name|module
condition|)
return|return;
name|browser
operator|->
name|last_update
operator|=
name|module
expr_stmt|;
name|browser_info_update
argument_list|(
name|browser
operator|->
name|gimp
operator|->
name|module_db
argument_list|,
name|browser
operator|->
name|last_update
argument_list|,
name|browser
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_autoload_toggled (GtkCellRendererToggle * celltoggle,gchar * path_string,ModuleBrowser * browser)
name|browser_autoload_toggled
parameter_list|(
name|GtkCellRendererToggle
modifier|*
name|celltoggle
parameter_list|,
name|gchar
modifier|*
name|path_string
parameter_list|,
name|ModuleBrowser
modifier|*
name|browser
parameter_list|)
block|{
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gboolean
name|active
init|=
name|FALSE
decl_stmt|;
name|GimpModule
modifier|*
name|module
init|=
name|NULL
decl_stmt|;
name|path
operator|=
name|gtk_tree_path_new_from_string
argument_list|(
name|path_string
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_tree_model_get_iter
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|browser
operator|->
name|list
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|path
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: bad tree path?"
argument_list|,
name|G_STRLOC
argument_list|)
expr_stmt|;
return|return;
block|}
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|browser
operator|->
name|list
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|AUTO_COLUMN
argument_list|,
operator|&
name|active
argument_list|,
name|MODULE_COLUMN
argument_list|,
operator|&
name|module
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|module
condition|)
block|{
name|gimp_module_set_load_inhibit
argument_list|(
name|module
argument_list|,
name|active
argument_list|)
expr_stmt|;
name|browser
operator|->
name|gimp
operator|->
name|write_modulerc
operator|=
name|TRUE
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|browser
operator|->
name|list
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|AUTO_COLUMN
argument_list|,
operator|!
name|active
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_load_unload_callback (GtkWidget * widget,ModuleBrowser * browser)
name|browser_load_unload_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|ModuleBrowser
modifier|*
name|browser
parameter_list|)
block|{
if|if
condition|(
name|browser
operator|->
name|last_update
operator|->
name|state
operator|!=
name|GIMP_MODULE_STATE_LOADED
condition|)
block|{
if|if
condition|(
name|browser
operator|->
name|last_update
operator|->
name|info
condition|)
block|{
if|if
condition|(
name|g_type_module_use
argument_list|(
name|G_TYPE_MODULE
argument_list|(
name|browser
operator|->
name|last_update
argument_list|)
argument_list|)
condition|)
name|g_type_module_unuse
argument_list|(
name|G_TYPE_MODULE
argument_list|(
name|browser
operator|->
name|last_update
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_module_query_module
argument_list|(
name|browser
operator|->
name|last_update
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_module_modified
argument_list|(
name|browser
operator|->
name|last_update
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_refresh_callback (GtkWidget * widget,ModuleBrowser * browser)
name|browser_refresh_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|ModuleBrowser
modifier|*
name|browser
parameter_list|)
block|{
name|gimp_modules_refresh
argument_list|(
name|browser
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
name|GimpModule
modifier|*
name|module
init|=
name|data
decl_stmt|;
name|ModuleBrowser
modifier|*
name|browser
init|=
name|user_data
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
operator|!
name|browser
operator|->
name|last_update
condition|)
name|browser
operator|->
name|last_update
operator|=
name|module
expr_stmt|;
name|gtk_list_store_append
argument_list|(
name|browser
operator|->
name|list
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|browser
operator|->
name|list
argument_list|,
operator|&
name|iter
argument_list|,
name|PATH_COLUMN
argument_list|,
name|module
operator|->
name|filename
argument_list|,
name|AUTO_COLUMN
argument_list|,
operator|!
name|module
operator|->
name|load_inhibit
argument_list|,
name|MODULE_COLUMN
argument_list|,
name|module
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
DECL|function|browser_info_add (GimpModuleDB * db,GimpModule * module,ModuleBrowser * browser)
name|browser_info_add
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
name|GimpModule
modifier|*
name|module
parameter_list|,
name|ModuleBrowser
modifier|*
name|browser
parameter_list|)
block|{
name|make_list_item
argument_list|(
name|module
argument_list|,
name|browser
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_info_remove (GimpModuleDB * db,GimpModule * mod,ModuleBrowser * browser)
name|browser_info_remove
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
name|GimpModule
modifier|*
name|mod
parameter_list|,
name|ModuleBrowser
modifier|*
name|browser
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|GimpModule
modifier|*
name|module
decl_stmt|;
comment|/* FIXME: Use gtk_list_store_foreach_remove when it becomes available */
if|if
condition|(
operator|!
name|gtk_tree_model_get_iter_root
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|browser
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
name|browser
operator|->
name|list
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|MODULE_COLUMN
argument_list|,
operator|&
name|module
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|module
operator|==
name|mod
condition|)
block|{
name|gtk_list_store_remove
argument_list|(
name|browser
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
name|browser
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
literal|"%s: Tried to remove a module not in the browser's list."
argument_list|,
name|G_STRLOC
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browser_info_update (GimpModuleDB * db,GimpModule * module,ModuleBrowser * browser)
name|browser_info_update
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
name|GimpModule
modifier|*
name|module
parameter_list|,
name|ModuleBrowser
modifier|*
name|browser
parameter_list|)
block|{
name|GTypeModule
modifier|*
name|g_type_module
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|text
index|[
name|NUM_INFO_LINES
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_type_module
operator|=
name|G_TYPE_MODULE
argument_list|(
name|module
argument_list|)
expr_stmt|;
comment|/* only update the info if we're actually showing it */
if|if
condition|(
name|module
operator|!=
name|browser
operator|->
name|last_update
condition|)
return|return;
if|if
condition|(
operator|!
name|module
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
name|browser
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
name|browser
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
name|browser
operator|->
name|button
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|module
operator|->
name|info
condition|)
block|{
name|text
index|[
literal|0
index|]
operator|=
name|module
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
name|module
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
name|module
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
name|module
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
name|module
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
name|module
operator|->
name|on_disk
condition|?
name|_
argument_list|(
literal|"On disk"
argument_list|)
else|:
name|_
argument_list|(
literal|"Only in memory"
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
name|module
operator|->
name|on_disk
condition|?
name|_
argument_list|(
literal|"On disk"
argument_list|)
else|:
name|_
argument_list|(
literal|"No longer available"
argument_list|)
expr_stmt|;
block|}
name|text
index|[
literal|6
index|]
operator|=
name|gimp_module_state_name
argument_list|(
name|module
operator|->
name|state
argument_list|)
expr_stmt|;
if|if
condition|(
name|module
operator|->
name|state
operator|==
name|GIMP_MODULE_STATE_ERROR
operator|&&
name|module
operator|->
name|last_module_error
condition|)
name|text
index|[
literal|7
index|]
operator|=
name|module
operator|->
name|last_module_error
expr_stmt|;
else|else
name|text
index|[
literal|7
index|]
operator|=
literal|"--"
expr_stmt|;
if|if
condition|(
name|g_type_module
operator|->
name|type_infos
operator|||
name|g_type_module
operator|->
name|interface_infos
condition|)
block|{
name|gchar
modifier|*
name|str
decl_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d Types, %d Interfaces"
argument_list|,
name|g_slist_length
argument_list|(
name|g_type_module
operator|->
name|type_infos
argument_list|)
argument_list|,
name|g_slist_length
argument_list|(
name|g_type_module
operator|->
name|interface_infos
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|browser
operator|->
name|label
index|[
name|NUM_INFO_LINES
operator|-
literal|1
index|]
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
block|}
else|else
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|browser
operator|->
name|label
index|[
name|NUM_INFO_LINES
operator|-
literal|1
index|]
argument_list|)
argument_list|,
literal|"---"
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
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|browser
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
comment|/* work out what the button should do (if anything) */
switch|switch
condition|(
name|module
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
name|GIMP_MODULE_STATE_NOT_LOADED
case|:
if|if
condition|(
name|module
operator|->
name|info
condition|)
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|browser
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
else|else
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|browser
operator|->
name|button_label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Query"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|browser
operator|->
name|button
argument_list|)
argument_list|,
name|module
operator|->
name|on_disk
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_MODULE_STATE_LOADED
case|:
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|browser
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
name|browser
operator|->
name|button
argument_list|)
argument_list|,
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
DECL|function|browser_info_init (ModuleBrowser * browser,GtkWidget * table)
name|browser_info_init
parameter_list|(
name|ModuleBrowser
modifier|*
name|browser
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
specifier|static
specifier|const
name|gchar
modifier|*
specifier|const
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
block|,
name|N_
argument_list|(
literal|"Last Error:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Available Types:"
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
name|G_N_ELEMENTS
argument_list|(
name|text
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
name|browser
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
name|browser
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
name|browser
operator|->
name|table
argument_list|)
argument_list|,
name|browser
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
name|browser
operator|->
name|label
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

