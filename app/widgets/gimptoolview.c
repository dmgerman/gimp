begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolview.c  * Copyright (C) 2001-2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainertreeview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolview.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_tool_view_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_view_select_item
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_view_activate_item
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_view_visible_notify
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpContainerTreeView
modifier|*
name|tree_view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_view_eye_data_func
parameter_list|(
name|GtkTreeViewColumn
modifier|*
name|tree_column
parameter_list|,
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_view_eye_clicked
parameter_list|(
name|GtkCellRendererToggle
modifier|*
name|toggle
parameter_list|,
name|gchar
modifier|*
name|path_str
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpContainerTreeView
modifier|*
name|tree_view
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpToolView,gimp_tool_view,GIMP_TYPE_CONTAINER_EDITOR)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpToolView
argument_list|,
argument|gimp_tool_view
argument_list|,
argument|GIMP_TYPE_CONTAINER_EDITOR
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tool_view_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tool_view_class_init
parameter_list|(
name|GimpToolViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
init|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpContainerEditorClass
modifier|*
name|editor_class
init|=
name|GIMP_CONTAINER_EDITOR_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_tool_view_destroy
expr_stmt|;
name|editor_class
operator|->
name|select_item
operator|=
name|gimp_tool_view_select_item
expr_stmt|;
name|editor_class
operator|->
name|activate_item
operator|=
name|gimp_tool_view_activate_item
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_view_init (GimpToolView * view)
name|gimp_tool_view_init
parameter_list|(
name|GimpToolView
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|visible_handler_id
operator|=
literal|0
expr_stmt|;
name|view
operator|->
name|raise_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|lower_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|reset_button
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_view_destroy (GtkObject * object)
name|gimp_tool_view_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolView
modifier|*
name|tool_view
init|=
name|GIMP_TOOL_VIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|tool_view
operator|->
name|visible_handler_id
condition|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|tool_view
argument_list|)
decl_stmt|;
name|GimpContainerView
modifier|*
name|view
init|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
decl_stmt|;
name|gimp_container_remove_handler
argument_list|(
name|gimp_container_view_get_container
argument_list|(
name|view
argument_list|)
argument_list|,
name|tool_view
operator|->
name|visible_handler_id
argument_list|)
expr_stmt|;
name|tool_view
operator|->
name|visible_handler_id
operator|=
literal|0
expr_stmt|;
block|}
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_tool_view_new (GimpViewType view_type,GimpContainer * container,GimpContext * context,gint view_size,gint view_border_width,GimpMenuFactory * menu_factory)
name|gimp_tool_view_new
parameter_list|(
name|GimpViewType
name|view_type
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|GimpToolView
modifier|*
name|tool_view
decl_stmt|;
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|tool_view
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_VIEW
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_container_editor_construct
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|tool_view
argument_list|)
argument_list|,
name|view_type
argument_list|,
name|container
argument_list|,
name|context
argument_list|,
name|view_size
argument_list|,
name|view_border_width
argument_list|,
name|menu_factory
argument_list|,
literal|"<Tools>"
argument_list|,
literal|"/tools-popup"
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|tool_view
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|tool_view
argument_list|)
expr_stmt|;
name|tool_view
operator|->
name|raise_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
literal|"tools"
argument_list|,
literal|"tools-raise"
argument_list|,
literal|"tools-raise-to-top"
argument_list|,
name|GDK_SHIFT_MASK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tool_view
operator|->
name|lower_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
literal|"tools"
argument_list|,
literal|"tools-lower"
argument_list|,
literal|"tools-lower-to-bottom"
argument_list|,
name|GDK_SHIFT_MASK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tool_view
operator|->
name|reset_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
literal|"tools"
argument_list|,
literal|"tools-reset"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|view_type
operator|==
name|GIMP_VIEW_TYPE_LIST
condition|)
block|{
name|GimpContainerTreeView
modifier|*
name|tree_view
init|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|tree_widget
init|=
name|GTK_WIDGET
argument_list|(
name|tree_view
argument_list|)
decl_stmt|;
name|GtkStyle
modifier|*
name|tree_style
init|=
name|gtk_widget_get_style
argument_list|(
name|tree_widget
argument_list|)
decl_stmt|;
name|GtkTreeViewColumn
modifier|*
name|column
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|eye_cell
decl_stmt|;
name|GtkIconSize
name|icon_size
decl_stmt|;
name|column
operator|=
name|gtk_tree_view_column_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_insert_column
argument_list|(
name|tree_view
operator|->
name|view
argument_list|,
name|column
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|eye_cell
operator|=
name|gimp_cell_renderer_toggle_new
argument_list|(
name|GIMP_STOCK_VISIBLE
argument_list|)
expr_stmt|;
name|icon_size
operator|=
name|gimp_get_icon_size
argument_list|(
name|GTK_WIDGET
argument_list|(
name|tree_view
argument_list|)
argument_list|,
name|GIMP_STOCK_VISIBLE
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|view_size
operator|-
literal|2
operator|*
name|tree_style
operator|->
name|xthickness
argument_list|,
name|view_size
operator|-
literal|2
operator|*
name|tree_style
operator|->
name|ythickness
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|eye_cell
argument_list|,
literal|"stock-size"
argument_list|,
name|icon_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|column
argument_list|,
name|eye_cell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_cell_data_func
argument_list|(
name|column
argument_list|,
name|eye_cell
argument_list|,
name|gimp_tool_view_eye_data_func
argument_list|,
name|tree_view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_tree_view_prepend_toggle_cell_renderer
argument_list|(
name|tree_view
argument_list|,
name|eye_cell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|eye_cell
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_view_eye_clicked
argument_list|)
argument_list|,
name|tree_view
argument_list|)
expr_stmt|;
name|tool_view
operator|->
name|visible_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|container
argument_list|,
literal|"notify::visible"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_view_visible_notify
argument_list|)
argument_list|,
name|tree_view
argument_list|)
expr_stmt|;
block|}
name|gimp_ui_manager_update
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
operator|->
name|ui_manager
argument_list|,
name|editor
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|tool_view
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_view_select_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_tool_view_select_item
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
if|if
condition|(
name|GIMP_CONTAINER_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|select_item
condition|)
name|GIMP_CONTAINER_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|select_item
argument_list|(
name|editor
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_view_activate_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_tool_view_activate_item
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
if|if
condition|(
name|GIMP_CONTAINER_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|activate_item
condition|)
name|GIMP_CONTAINER_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|activate_item
argument_list|(
name|editor
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  "visible" callbaks  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_tool_view_visible_notify (GimpToolInfo * tool_info,GParamSpec * pspec,GimpContainerTreeView * tree_view)
name|gimp_tool_view_visible_notify
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpContainerTreeView
modifier|*
name|tree_view
parameter_list|)
block|{
name|GtkTreeIter
modifier|*
name|iter
decl_stmt|;
name|iter
operator|=
name|gimp_container_view_lookup
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|tree_view
argument_list|)
argument_list|,
operator|(
name|GimpViewable
operator|*
operator|)
name|tool_info
argument_list|)
expr_stmt|;
if|if
condition|(
name|iter
condition|)
block|{
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|path
operator|=
name|gtk_tree_model_get_path
argument_list|(
name|tree_view
operator|->
name|model
argument_list|,
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_model_row_changed
argument_list|(
name|tree_view
operator|->
name|model
argument_list|,
name|path
argument_list|,
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_view_eye_data_func (GtkTreeViewColumn * tree_column,GtkCellRenderer * cell,GtkTreeModel * tree_model,GtkTreeIter * iter,gpointer data)
name|gimp_tool_view_eye_data_func
parameter_list|(
name|GtkTreeViewColumn
modifier|*
name|tree_column
parameter_list|,
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpViewRenderer
modifier|*
name|renderer
decl_stmt|;
name|gboolean
name|visible
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|tree_model
argument_list|,
name|iter
argument_list|,
name|GIMP_CONTAINER_TREE_VIEW_COLUMN_RENDERER
argument_list|,
operator|&
name|renderer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|,
literal|"visible"
argument_list|,
operator|&
name|visible
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|cell
argument_list|,
literal|"active"
argument_list|,
name|visible
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_view_eye_clicked (GtkCellRendererToggle * toggle,gchar * path_str,GdkModifierType state,GimpContainerTreeView * tree_view)
name|gimp_tool_view_eye_clicked
parameter_list|(
name|GtkCellRendererToggle
modifier|*
name|toggle
parameter_list|,
name|gchar
modifier|*
name|path_str
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpContainerTreeView
modifier|*
name|tree_view
parameter_list|)
block|{
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|path
operator|=
name|gtk_tree_path_new_from_string
argument_list|(
name|path_str
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter
argument_list|(
name|tree_view
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|path
argument_list|)
condition|)
block|{
name|GimpViewRenderer
modifier|*
name|renderer
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|g_object_get
argument_list|(
name|toggle
argument_list|,
literal|"active"
argument_list|,
operator|&
name|active
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|tree_view
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_CONTAINER_TREE_VIEW_COLUMN_RENDERER
argument_list|,
operator|&
name|renderer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|,
literal|"visible"
argument_list|,
operator|!
name|active
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
block|}
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

