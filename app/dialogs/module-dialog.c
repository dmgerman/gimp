begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * module-dialog.c  * (C) 1999 Austin Donnelly<austin@gimp.org>  * (C) 2008 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"dialogs-types.h"
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
file|"module-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|RESPONSE_REFRESH
define|#
directive|define
name|RESPONSE_REFRESH
value|1
end_define

begin_enum
enum|enum
DECL|enum|__anon288e23fa0103
block|{
DECL|enumerator|COLUMN_NAME
name|COLUMN_NAME
block|,
DECL|enumerator|COLUMN_ENABLED
name|COLUMN_ENABLED
block|,
DECL|enumerator|COLUMN_MODULE
name|COLUMN_MODULE
block|,
DECL|enumerator|N_COLUMNS
name|N_COLUMNS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon288e23fa0203
block|{
DECL|enumerator|INFO_AUTHOR
name|INFO_AUTHOR
block|,
DECL|enumerator|INFO_VERSION
name|INFO_VERSION
block|,
DECL|enumerator|INFO_DATE
name|INFO_DATE
block|,
DECL|enumerator|INFO_COPYRIGHT
name|INFO_COPYRIGHT
block|,
DECL|enumerator|INFO_LOCATION
name|INFO_LOCATION
block|,
DECL|enumerator|N_INFOS
name|N_INFOS
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|ModuleDialog
typedef|typedef
name|struct
name|_ModuleDialog
name|ModuleDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_ModuleDialog
struct|struct
name|_ModuleDialog
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|selected
name|GimpModule
modifier|*
name|selected
decl_stmt|;
DECL|member|list
name|GtkListStore
modifier|*
name|list
decl_stmt|;
DECL|member|hint
name|GtkWidget
modifier|*
name|hint
decl_stmt|;
DECL|member|grid
name|GtkWidget
modifier|*
name|grid
decl_stmt|;
DECL|member|label
name|GtkWidget
modifier|*
name|label
index|[
name|N_INFOS
index|]
decl_stmt|;
DECL|member|error_box
name|GtkWidget
modifier|*
name|error_box
decl_stmt|;
DECL|member|error_label
name|GtkWidget
modifier|*
name|error_label
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
name|dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ModuleDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dialog_destroy_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|ModuleDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dialog_select_callback
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|ModuleDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dialog_enabled_toggled
parameter_list|(
name|GtkCellRendererToggle
modifier|*
name|celltoggle
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_string
parameter_list|,
name|ModuleDialog
modifier|*
name|private
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
name|dialog_info_add
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
name|GimpModule
modifier|*
name|module
parameter_list|,
name|ModuleDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dialog_info_remove
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
name|GimpModule
modifier|*
name|module
parameter_list|,
name|ModuleDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dialog_info_update
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
name|GimpModule
modifier|*
name|module
parameter_list|,
name|ModuleDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dialog_info_init
parameter_list|(
name|ModuleDialog
modifier|*
name|private
parameter_list|,
name|GtkWidget
modifier|*
name|grid
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|module_dialog_new (Gimp * gimp)
name|module_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|ModuleDialog
modifier|*
name|private
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|sw
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|GtkWidget
modifier|*
name|image
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
name|private
operator|=
name|g_slice_new0
argument_list|(
name|ModuleDialog
argument_list|)
expr_stmt|;
name|private
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Module Manager"
argument_list|)
argument_list|,
literal|"gimp-modules"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_MODULE_DIALOG
argument_list|,
name|_
argument_list|(
literal|"_Refresh"
argument_list|)
argument_list|,
name|RESPONSE_REFRESH
argument_list|,
name|_
argument_list|(
literal|"_Close"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|RESPONSE_REFRESH
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|dialog_response
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|private
operator|->
name|hint
operator|=
name|gimp_hint_box_new
argument_list|(
name|_
argument_list|(
literal|"You will have to restart GIMP "
literal|"for the changes to take effect."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|private
operator|->
name|hint
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|write_modulerc
condition|)
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|hint
argument_list|)
expr_stmt|;
name|sw
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
name|sw
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|sw
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
name|sw
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
name|sw
argument_list|,
literal|124
argument_list|,
literal|100
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|sw
argument_list|)
expr_stmt|;
name|private
operator|->
name|list
operator|=
name|gtk_list_store_new
argument_list|(
name|N_COLUMNS
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
name|GIMP_TYPE_MODULE
argument_list|)
expr_stmt|;
name|view
operator|=
name|gtk_tree_view_new_with_model
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|private
operator|->
name|list
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|private
operator|->
name|list
argument_list|)
expr_stmt|;
name|gtk_tree_view_set_headers_visible
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|gimp_module_db_get_modules
argument_list|(
name|gimp
operator|->
name|module_db
argument_list|)
argument_list|,
name|make_list_item
argument_list|,
name|private
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
name|dialog_enabled_toggled
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|col
operator|=
name|gtk_tree_view_column_new
argument_list|()
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
name|COLUMN_ENABLED
argument_list|)
expr_stmt|;
name|gtk_tree_view_append_column
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|col
argument_list|)
expr_stmt|;
name|gtk_tree_view_insert_column_with_attributes
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Module"
argument_list|)
argument_list|,
name|gtk_cell_renderer_text_new
argument_list|()
argument_list|,
literal|"text"
argument_list|,
name|COLUMN_NAME
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|sw
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|private
operator|->
name|grid
operator|=
name|gtk_grid_new
argument_list|()
expr_stmt|;
name|gtk_grid_set_column_spacing
argument_list|(
name|GTK_GRID
argument_list|(
name|private
operator|->
name|grid
argument_list|)
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
name|private
operator|->
name|grid
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
name|private
operator|->
name|grid
argument_list|)
expr_stmt|;
name|private
operator|->
name|error_box
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
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
name|private
operator|->
name|error_box
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|GIMP_ICON_DIALOG_WARNING
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|private
operator|->
name|error_box
argument_list|)
argument_list|,
name|image
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
name|image
argument_list|)
expr_stmt|;
name|private
operator|->
name|error_label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|private
operator|->
name|error_label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|private
operator|->
name|error_box
argument_list|)
argument_list|,
name|private
operator|->
name|error_label
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
name|private
operator|->
name|error_label
argument_list|)
expr_stmt|;
name|dialog_info_init
argument_list|(
name|private
argument_list|,
name|private
operator|->
name|grid
argument_list|)
expr_stmt|;
name|dialog_info_update
argument_list|(
name|gimp
operator|->
name|module_db
argument_list|,
name|private
operator|->
name|selected
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|sel
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
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
name|dialog_select_callback
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter_first
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|private
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
name|dialog_info_add
argument_list|)
argument_list|,
name|private
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
name|dialog_info_remove
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimp
operator|->
name|module_db
argument_list|,
literal|"module-modified"
argument_list|,
name|G_CALLBACK
argument_list|(
name|dialog_info_update
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|dialog_destroy_callback
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
return|return
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
DECL|function|dialog_response (GtkWidget * widget,gint response_id,ModuleDialog * private)
name|dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ModuleDialog
modifier|*
name|private
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|RESPONSE_REFRESH
condition|)
name|gimp_modules_refresh
argument_list|(
name|private
operator|->
name|gimp
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dialog_destroy_callback (GtkWidget * widget,ModuleDialog * private)
name|dialog_destroy_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|ModuleDialog
modifier|*
name|private
parameter_list|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|private
operator|->
name|gimp
operator|->
name|module_db
argument_list|,
name|dialog_info_add
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|private
operator|->
name|gimp
operator|->
name|module_db
argument_list|,
name|dialog_info_remove
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|private
operator|->
name|gimp
operator|->
name|module_db
argument_list|,
name|dialog_info_update
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|ModuleDialog
argument_list|,
name|private
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dialog_select_callback (GtkTreeSelection * sel,ModuleDialog * private)
name|dialog_select_callback
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|ModuleDialog
modifier|*
name|private
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
name|GimpModule
modifier|*
name|module
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|private
operator|->
name|list
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_MODULE
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
name|g_object_unref
argument_list|(
name|module
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|selected
operator|==
name|module
condition|)
return|return;
name|private
operator|->
name|selected
operator|=
name|module
expr_stmt|;
name|dialog_info_update
argument_list|(
name|private
operator|->
name|gimp
operator|->
name|module_db
argument_list|,
name|private
operator|->
name|selected
argument_list|,
name|private
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dialog_enabled_toggled (GtkCellRendererToggle * celltoggle,const gchar * path_string,ModuleDialog * private)
name|dialog_enabled_toggled
parameter_list|(
name|GtkCellRendererToggle
modifier|*
name|celltoggle
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_string
parameter_list|,
name|ModuleDialog
modifier|*
name|private
parameter_list|)
block|{
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|GtkTreeIter
name|iter
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
name|private
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
name|G_STRFUNC
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
name|private
operator|->
name|list
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_MODULE
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
operator|!
name|module
operator|->
name|load_inhibit
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|module
argument_list|)
expr_stmt|;
name|private
operator|->
name|gimp
operator|->
name|write_modulerc
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|hint
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dialog_list_item_update (ModuleDialog * private,GtkTreeIter * iter,GimpModule * module)
name|dialog_list_item_update
parameter_list|(
name|ModuleDialog
modifier|*
name|private
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GimpModule
modifier|*
name|module
parameter_list|)
block|{
name|gtk_list_store_set
argument_list|(
name|private
operator|->
name|list
argument_list|,
name|iter
argument_list|,
name|COLUMN_NAME
argument_list|,
operator|(
name|module
operator|->
name|info
condition|?
name|gettext
argument_list|(
name|module
operator|->
name|info
operator|->
name|purpose
argument_list|)
else|:
name|gimp_filename_to_utf8
argument_list|(
name|module
operator|->
name|filename
argument_list|)
operator|)
argument_list|,
name|COLUMN_ENABLED
argument_list|,
operator|!
name|module
operator|->
name|load_inhibit
argument_list|,
name|COLUMN_MODULE
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
name|ModuleDialog
modifier|*
name|private
init|=
name|user_data
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
operator|!
name|private
operator|->
name|selected
condition|)
name|private
operator|->
name|selected
operator|=
name|module
expr_stmt|;
name|gtk_list_store_append
argument_list|(
name|private
operator|->
name|list
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|dialog_list_item_update
argument_list|(
name|private
argument_list|,
operator|&
name|iter
argument_list|,
name|module
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dialog_info_add (GimpModuleDB * db,GimpModule * module,ModuleDialog * private)
name|dialog_info_add
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
name|GimpModule
modifier|*
name|module
parameter_list|,
name|ModuleDialog
modifier|*
name|private
parameter_list|)
block|{
name|make_list_item
argument_list|(
name|module
argument_list|,
name|private
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dialog_info_remove (GimpModuleDB * db,GimpModule * module,ModuleDialog * private)
name|dialog_info_remove
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
name|GimpModule
modifier|*
name|module
parameter_list|,
name|ModuleDialog
modifier|*
name|private
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
comment|/* FIXME: Use gtk_list_store_foreach_remove when it becomes available */
if|if
condition|(
operator|!
name|gtk_tree_model_get_iter_first
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|private
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
name|GimpModule
modifier|*
name|this
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|private
operator|->
name|list
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_MODULE
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
name|module
condition|)
block|{
name|gtk_list_store_remove
argument_list|(
name|private
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
name|private
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
literal|"%s: Tried to remove a module not in the dialog's list."
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dialog_info_update (GimpModuleDB * db,GimpModule * module,ModuleDialog * private)
name|dialog_info_update
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
name|GimpModule
modifier|*
name|module
parameter_list|,
name|ModuleDialog
modifier|*
name|private
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|GTK_TREE_MODEL
argument_list|(
name|private
operator|->
name|list
argument_list|)
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|text
index|[
name|N_INFOS
index|]
init|=
block|{
name|NULL
block|, }
decl_stmt|;
name|gchar
modifier|*
name|location
init|=
name|NULL
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gboolean
name|show_error
decl_stmt|;
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
name|GimpModule
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
name|COLUMN_MODULE
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
name|module
condition|)
break|break;
block|}
if|if
condition|(
name|iter_valid
condition|)
name|dialog_list_item_update
argument_list|(
name|private
argument_list|,
operator|&
name|iter
argument_list|,
name|module
argument_list|)
expr_stmt|;
comment|/* only update the info if we're actually showing it */
if|if
condition|(
name|module
operator|!=
name|private
operator|->
name|selected
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
name|N_INFOS
condition|;
name|i
operator|++
control|)
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|private
operator|->
name|label
index|[
name|i
index|]
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|private
operator|->
name|error_label
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|private
operator|->
name|error_box
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|module
operator|->
name|on_disk
condition|)
name|location
operator|=
name|g_filename_display_name
argument_list|(
name|module
operator|->
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|module
operator|->
name|info
condition|)
block|{
name|text
index|[
name|INFO_AUTHOR
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
name|INFO_VERSION
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
name|INFO_DATE
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
name|INFO_COPYRIGHT
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
name|INFO_LOCATION
index|]
operator|=
name|module
operator|->
name|on_disk
condition|?
name|location
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
name|INFO_LOCATION
index|]
operator|=
operator|(
name|module
operator|->
name|on_disk
condition|?
name|location
else|:
name|_
argument_list|(
literal|"No longer available"
argument_list|)
operator|)
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
name|N_INFOS
condition|;
name|i
operator|++
control|)
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|private
operator|->
name|label
index|[
name|i
index|]
argument_list|)
argument_list|,
name|text
index|[
name|i
index|]
condition|?
name|text
index|[
name|i
index|]
else|:
literal|"--"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|location
argument_list|)
expr_stmt|;
comment|/* Show errors */
name|show_error
operator|=
operator|(
name|module
operator|->
name|state
operator|==
name|GIMP_MODULE_STATE_ERROR
operator|&&
name|module
operator|->
name|last_module_error
operator|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|private
operator|->
name|error_label
argument_list|)
argument_list|,
name|show_error
condition|?
name|module
operator|->
name|last_module_error
else|:
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|private
operator|->
name|error_box
argument_list|,
name|show_error
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dialog_info_init (ModuleDialog * private,GtkWidget * grid)
name|dialog_info_init
parameter_list|(
name|ModuleDialog
modifier|*
name|private
parameter_list|,
name|GtkWidget
modifier|*
name|grid
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|gint
name|i
decl_stmt|;
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
literal|"Date:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Copyright:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Location:"
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
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_grid_attach
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|private
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
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|private
operator|->
name|label
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_ellipsize
argument_list|(
name|GTK_LABEL
argument_list|(
name|private
operator|->
name|label
index|[
name|i
index|]
argument_list|)
argument_list|,
name|PANGO_ELLIPSIZE_END
argument_list|)
expr_stmt|;
name|gtk_grid_attach
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
name|private
operator|->
name|label
index|[
name|i
index|]
argument_list|,
literal|1
argument_list|,
name|i
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|private
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

