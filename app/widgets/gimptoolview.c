begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptooleditor.c  * Copyright (C) 2001-2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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

begin_typedef
DECL|typedef|GimpToolEditorPrivate
typedef|typedef
name|struct
name|_GimpToolEditorPrivate
name|GimpToolEditorPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolEditorPrivate
struct|struct
name|_GimpToolEditorPrivate
block|{
DECL|member|model
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|container
name|GimpContainer
modifier|*
name|container
decl_stmt|;
DECL|member|scrolled
name|GtkWidget
modifier|*
name|scrolled
decl_stmt|;
DECL|member|raise_button
name|GtkWidget
modifier|*
name|raise_button
decl_stmt|;
DECL|member|lower_button
name|GtkWidget
modifier|*
name|lower_button
decl_stmt|;
DECL|member|reset_button
name|GtkWidget
modifier|*
name|reset_button
decl_stmt|;
DECL|member|visible_handler_id
name|GQuark
name|visible_handler_id
decl_stmt|;
DECL|member|default_tool_order
name|GList
modifier|*
name|default_tool_order
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_tool_editor_destroy
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
name|gimp_tool_editor_visible_notify
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpToolEditor
modifier|*
name|tool_editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_editor_eye_data_func
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
name|gimp_tool_editor_eye_clicked
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
name|GimpToolEditor
modifier|*
name|tool_editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_editor_button_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GimpToolEditor
modifier|*
name|tool_editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_editor_button_extend_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GdkModifierType
name|mask
parameter_list|,
name|GimpToolEditor
modifier|*
name|tool_editor
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpToolEditor,gimp_tool_editor,GIMP_TYPE_CONTAINER_TREE_VIEW)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpToolEditor
argument_list|,
argument|gimp_tool_editor
argument_list|,
argument|GIMP_TYPE_CONTAINER_TREE_VIEW
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tool_editor_parent_class
end_define

begin_define
DECL|macro|GIMP_TOOL_EDITOR_GET_PRIVATE (obj)
define|#
directive|define
name|GIMP_TOOL_EDITOR_GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_PRIVATE ((obj), \                                            GIMP_TYPE_TOOL_EDITOR, \                                            GimpToolEditorPrivate))
end_define

begin_function
specifier|static
name|void
name|gimp_tool_editor_class_init
parameter_list|(
name|GimpToolEditorClass
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
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpToolEditorPrivate
argument_list|)
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_tool_editor_destroy
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_editor_init (GimpToolEditor * tool_editor)
name|gimp_tool_editor_init
parameter_list|(
name|GimpToolEditor
modifier|*
name|tool_editor
parameter_list|)
block|{
name|GimpToolEditorPrivate
modifier|*
name|priv
init|=
name|GIMP_TOOL_EDITOR_GET_PRIVATE
argument_list|(
name|tool_editor
argument_list|)
decl_stmt|;
name|priv
operator|->
name|model
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|container
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|scrolled
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|visible_handler_id
operator|=
literal|0
expr_stmt|;
name|priv
operator|->
name|default_tool_order
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|raise_button
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|lower_button
operator|=
name|NULL
expr_stmt|;
name|priv
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
DECL|function|gimp_tool_editor_destroy (GtkObject * object)
name|gimp_tool_editor_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolEditorPrivate
modifier|*
name|priv
init|=
name|GIMP_TOOL_EDITOR_GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|priv
operator|->
name|visible_handler_id
condition|)
block|{
name|gimp_container_remove_handler
argument_list|(
name|priv
operator|->
name|container
argument_list|,
name|priv
operator|->
name|visible_handler_id
argument_list|)
expr_stmt|;
name|priv
operator|->
name|visible_handler_id
operator|=
literal|0
expr_stmt|;
block|}
name|priv
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|container
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|raise_button
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|lower_button
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|reset_button
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|scrolled
operator|=
name|NULL
expr_stmt|;
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
DECL|function|gimp_tool_editor_new (GimpContainer * container,GimpContext * context,GList * default_tool_order,gint view_size,gint view_border_width)
name|gimp_tool_editor_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GList
modifier|*
name|default_tool_order
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|)
block|{
name|GimpToolEditor
modifier|*
name|tool_editor
decl_stmt|;
name|GimpContainerTreeView
modifier|*
name|tree_view
decl_stmt|;
name|GimpContainerView
modifier|*
name|container_view
decl_stmt|;
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpToolEditorPrivate
modifier|*
name|priv
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|container
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|context
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|object
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_EDITOR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tool_editor
operator|=
name|GIMP_TOOL_EDITOR
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|tree_view
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|container_view
operator|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GIMP_TOOL_EDITOR_GET_PRIVATE
argument_list|(
name|tool_editor
argument_list|)
expr_stmt|;
name|priv
operator|->
name|container
operator|=
name|container
expr_stmt|;
name|priv
operator|->
name|context
operator|=
name|context
expr_stmt|;
name|priv
operator|->
name|model
operator|=
name|tree_view
operator|->
name|model
expr_stmt|;
name|priv
operator|->
name|default_tool_order
operator|=
name|default_tool_order
expr_stmt|;
name|gimp_container_view_set_view_size
argument_list|(
name|container_view
argument_list|,
name|view_size
argument_list|,
name|view_border_width
argument_list|)
expr_stmt|;
name|gimp_container_view_set_container
argument_list|(
name|container_view
argument_list|,
name|priv
operator|->
name|container
argument_list|)
expr_stmt|;
name|gimp_container_view_set_context
argument_list|(
name|container_view
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|gimp_container_view_set_reorderable
argument_list|(
name|container_view
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_editor_set_show_name
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|tree_view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* Construct tree view */
block|{
name|GimpContainerTreeView
modifier|*
name|tree_view
init|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|tool_editor
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
name|tool_editor
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
name|gimp_tool_editor_eye_data_func
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
name|gimp_tool_editor_eye_clicked
argument_list|)
argument_list|,
name|tool_editor
argument_list|)
expr_stmt|;
name|priv
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
name|gimp_tool_editor_visible_notify
argument_list|)
argument_list|,
name|tool_editor
argument_list|)
expr_stmt|;
block|}
comment|/* buttons */
name|priv
operator|->
name|raise_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|tree_view
argument_list|)
argument_list|,
name|GTK_STOCK_GO_UP
argument_list|,
name|_
argument_list|(
literal|"Raise this tool Raise this tool to the top"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_editor_button_clicked
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_editor_button_extend_clicked
argument_list|)
argument_list|,
name|tool_editor
argument_list|)
expr_stmt|;
name|priv
operator|->
name|lower_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|tree_view
argument_list|)
argument_list|,
name|GTK_STOCK_GO_DOWN
argument_list|,
name|_
argument_list|(
literal|"Lower this tool Lower this tool to the bottom"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_editor_button_clicked
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_editor_button_extend_clicked
argument_list|)
argument_list|,
name|tool_editor
argument_list|)
expr_stmt|;
name|priv
operator|->
name|reset_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|tree_view
argument_list|)
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|_
argument_list|(
literal|"Reset tool order and visibility"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_editor_button_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|tool_editor
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|tool_editor
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_editor_button_clicked (GtkButton * button,GimpToolEditor * tool_editor)
name|gimp_tool_editor_button_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GimpToolEditor
modifier|*
name|tool_editor
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpToolEditorPrivate
modifier|*
name|priv
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|priv
operator|=
name|GIMP_TOOL_EDITOR_GET_PRIVATE
argument_list|(
name|tool_editor
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|priv
operator|->
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|button
operator|==
name|GTK_BUTTON
argument_list|(
name|priv
operator|->
name|raise_button
argument_list|)
condition|)
block|{
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|priv
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|>
literal|0
condition|)
block|{
name|gimp_container_reorder
argument_list|(
name|priv
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|index
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|tool_info
operator|&&
name|button
operator|==
name|GTK_BUTTON
argument_list|(
name|priv
operator|->
name|lower_button
argument_list|)
condition|)
block|{
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|priv
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|+
literal|1
operator|<
name|gimp_container_get_n_children
argument_list|(
name|priv
operator|->
name|container
argument_list|)
condition|)
block|{
name|gimp_container_reorder
argument_list|(
name|priv
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|index
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|tool_info
operator|&&
name|button
operator|==
name|GTK_BUTTON
argument_list|(
name|priv
operator|->
name|reset_button
argument_list|)
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
for|for
control|(
name|list
operator|=
name|priv
operator|->
name|default_tool_order
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpObject
modifier|*
name|object
init|=
name|gimp_container_get_child_by_name
argument_list|(
name|priv
operator|->
name|container
argument_list|,
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|object
condition|)
block|{
name|gboolean
name|visible
decl_stmt|;
name|gpointer
name|data
decl_stmt|;
name|gimp_container_reorder
argument_list|(
name|priv
operator|->
name|container
argument_list|,
name|object
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|data
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
literal|"gimp-tool-default-visible"
argument_list|)
expr_stmt|;
name|visible
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|object
argument_list|,
literal|"visible"
argument_list|,
name|visible
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|i
operator|++
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_editor_button_extend_clicked (GtkButton * button,GdkModifierType mask,GimpToolEditor * tool_editor)
name|gimp_tool_editor_button_extend_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GdkModifierType
name|mask
parameter_list|,
name|GimpToolEditor
modifier|*
name|tool_editor
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpToolEditorPrivate
modifier|*
name|priv
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|priv
operator|=
name|GIMP_TOOL_EDITOR_GET_PRIVATE
argument_list|(
name|tool_editor
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|priv
operator|->
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|mask
operator|==
name|GDK_SHIFT_MASK
condition|)
block|{
comment|/* do nothing */
block|}
if|if
condition|(
name|button
operator|==
name|GTK_BUTTON
argument_list|(
name|priv
operator|->
name|raise_button
argument_list|)
condition|)
block|{
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|priv
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|>
literal|0
condition|)
name|gimp_container_reorder
argument_list|(
name|priv
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|button
operator|==
name|GTK_BUTTON
argument_list|(
name|priv
operator|->
name|lower_button
argument_list|)
condition|)
block|{
name|index
operator|=
name|gimp_container_get_n_children
argument_list|(
name|priv
operator|->
name|container
argument_list|)
operator|-
literal|1
expr_stmt|;
name|index
operator|=
name|index
operator|>=
literal|0
condition|?
name|index
else|:
literal|0
expr_stmt|;
name|gimp_container_reorder
argument_list|(
name|priv
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|index
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_editor_visible_notify (GimpToolInfo * tool_info,GParamSpec * pspec,GimpToolEditor * tool_editor)
name|gimp_tool_editor_visible_notify
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpToolEditor
modifier|*
name|tool_editor
parameter_list|)
block|{
name|GimpToolEditorPrivate
modifier|*
name|priv
decl_stmt|;
name|GtkTreeIter
modifier|*
name|iter
decl_stmt|;
name|priv
operator|=
name|GIMP_TOOL_EDITOR_GET_PRIVATE
argument_list|(
name|tool_editor
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gimp_container_view_lookup
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|tool_editor
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|tool_info
argument_list|)
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
name|priv
operator|->
name|model
argument_list|,
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_model_row_changed
argument_list|(
name|priv
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
DECL|function|gimp_tool_editor_eye_data_func (GtkTreeViewColumn * tree_column,GtkCellRenderer * cell,GtkTreeModel * tree_model,GtkTreeIter * iter,gpointer data)
name|gimp_tool_editor_eye_data_func
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
DECL|function|gimp_tool_editor_eye_clicked (GtkCellRendererToggle * toggle,gchar * path_str,GdkModifierType state,GimpToolEditor * tool_editor)
name|gimp_tool_editor_eye_clicked
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
name|GimpToolEditor
modifier|*
name|tool_editor
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|GimpToolEditorPrivate
modifier|*
name|priv
init|=
name|GIMP_TOOL_EDITOR_GET_PRIVATE
argument_list|(
name|tool_editor
argument_list|)
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
name|priv
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
name|priv
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

