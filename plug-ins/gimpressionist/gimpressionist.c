begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"gimpressionist.h"
end_include

begin_comment
comment|/*  * The Page Specific Imports  * */
end_comment

begin_include
include|#
directive|include
file|"brush.h"
end_include

begin_include
include|#
directive|include
file|"color.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"orientation.h"
end_include

begin_include
include|#
directive|include
file|"orientmap.h"
end_include

begin_include
include|#
directive|include
file|"placement.h"
end_include

begin_include
include|#
directive|include
file|"preview.h"
end_include

begin_include
include|#
directive|include
file|"size.h"
end_include

begin_include
include|#
directive|include
file|"paper.h"
end_include

begin_include
include|#
directive|include
file|"presets.h"
end_include

begin_include
include|#
directive|include
file|"ppmtool.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
DECL|variable|dialog
specifier|static
name|GtkWidget
modifier|*
name|dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|store_values (void)
name|store_values
parameter_list|(
name|void
parameter_list|)
block|{
name|paper_store
argument_list|()
expr_stmt|;
name|brush_store
argument_list|()
expr_stmt|;
name|general_store
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|restore_values (void)
name|restore_values
parameter_list|(
name|void
parameter_list|)
block|{
name|brush_restore
argument_list|()
expr_stmt|;
name|paper_restore
argument_list|()
expr_stmt|;
name|orientation_restore
argument_list|()
expr_stmt|;
name|size_restore
argument_list|()
expr_stmt|;
name|place_restore
argument_list|()
expr_stmt|;
name|general_restore
argument_list|()
expr_stmt|;
name|color_restore
argument_list|()
expr_stmt|;
name|update_orientmap_dialog
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|create_one_column_list (GtkWidget * parent,void (* changed_cb)(GtkTreeSelection * selection,gpointer data))
name|create_one_column_list
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|void
function_decl|(
modifier|*
name|changed_cb
function_decl|)
parameter_list|(
name|GtkTreeSelection
modifier|*
name|selection
parameter_list|,
name|gpointer
name|data
parameter_list|)
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GtkTreeSelection
modifier|*
name|selection
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|renderer
decl_stmt|;
name|GtkTreeViewColumn
modifier|*
name|column
decl_stmt|;
name|GtkWidget
modifier|*
name|swin
decl_stmt|,
modifier|*
name|view
decl_stmt|;
name|swin
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
name|swin
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_shadow_type
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|swin
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|parent
argument_list|)
argument_list|,
name|swin
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
name|swin
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|swin
argument_list|,
literal|150
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|store
operator|=
name|gtk_list_store_new
argument_list|(
literal|1
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
name|view
operator|=
name|gtk_tree_view_new_with_model
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
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
name|g_object_unref
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|renderer
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|column
operator|=
name|gtk_tree_view_column_new_with_attributes
argument_list|(
literal|"Preset"
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
name|gtk_tree_view_append_column
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|column
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|swin
argument_list|)
argument_list|,
name|view
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
name|gtk_tree_selection_set_mode
argument_list|(
name|selection
argument_list|,
name|GTK_SELECTION_BROWSE
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
name|changed_cb
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|view
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dialog_response (GtkWidget * widget,gint response_id,gpointer data)
name|dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|GTK_RESPONSE_OK
case|:
name|store_values
argument_list|()
expr_stmt|;
name|pcvals
operator|.
name|run
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
break|break;
default|default:
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|create_dialog (void)
name|create_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|notebook
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|preview_box
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"gimpressionist"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"GIMPressionist"
argument_list|)
argument_list|,
literal|"gimpressionist"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|PLUG_IN_NAME
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_window_set_transient
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
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
name|NULL
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
name|gtk_main_quit
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|preview_box
operator|=
name|create_preview
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|preview_box
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
name|preview_box
argument_list|)
expr_stmt|;
name|notebook
operator|=
name|gtk_notebook_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|notebook
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|notebook
argument_list|)
expr_stmt|;
name|create_presetpage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|create_paperpage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|create_brushpage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|create_orientationpage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|create_sizepage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|create_placementpage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|create_colorpage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|create_generalpage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|updatepreview
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*    * This is to make sure the values from the pcvals will be reflected    * in the GUI here. Otherwise they will be set to the defaults.    * */
name|restore_values
argument_list|()
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_function
name|gint
DECL|function|create_gimpressionist (void)
name|create_gimpressionist
parameter_list|(
name|void
parameter_list|)
block|{
name|pcvals
operator|.
name|run
operator|=
name|FALSE
expr_stmt|;
name|create_dialog
argument_list|()
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
return|return
name|pcvals
operator|.
name|run
return|;
block|}
end_function

end_unit

