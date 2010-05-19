begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainereditor.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainereditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainergridview.h"
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
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_container_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_container_editor_select_item
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_editor_activate_item
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_editor_context_item
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_editor_real_context_item
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
name|GtkWidget
modifier|*
name|gimp_container_editor_get_preview
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_editor_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpUIManager
modifier|*
name|gimp_container_editor_get_menu
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|ui_path
parameter_list|,
name|gpointer
modifier|*
name|popup_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_container_editor_has_button_bar
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_editor_set_show_button_bar
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_container_editor_get_show_button_bar
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpContainerEditor,gimp_container_editor,GTK_TYPE_VBOX,G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,gimp_container_editor_docked_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpContainerEditor
argument_list|,
argument|gimp_container_editor
argument_list|,
argument|GTK_TYPE_VBOX
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,                                                 gimp_container_editor_docked_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_container_editor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_container_editor_class_init
parameter_list|(
name|GimpContainerEditorClass
modifier|*
name|klass
parameter_list|)
block|{
name|klass
operator|->
name|select_item
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|activate_item
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|context_item
operator|=
name|gimp_container_editor_real_context_item
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_docked_iface_init (GimpDockedInterface * iface)
name|gimp_container_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|get_preview
operator|=
name|gimp_container_editor_get_preview
expr_stmt|;
name|iface
operator|->
name|set_context
operator|=
name|gimp_container_editor_set_context
expr_stmt|;
name|iface
operator|->
name|get_menu
operator|=
name|gimp_container_editor_get_menu
expr_stmt|;
name|iface
operator|->
name|has_button_bar
operator|=
name|gimp_container_editor_has_button_bar
expr_stmt|;
name|iface
operator|->
name|set_show_button_bar
operator|=
name|gimp_container_editor_set_show_button_bar
expr_stmt|;
name|iface
operator|->
name|get_show_button_bar
operator|=
name|gimp_container_editor_get_show_button_bar
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_init (GimpContainerEditor * view)
name|gimp_container_editor_init
parameter_list|(
name|GimpContainerEditor
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|view
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_container_editor_construct (GimpContainerEditor * editor,GimpViewType view_type,GimpContainer * container,GimpContext * context,gint view_size,gint view_border_width,GimpMenuFactory * menu_factory,const gchar * menu_identifier,const gchar * ui_identifier)
name|gimp_container_editor_construct
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
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
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_identifier
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|view_size
operator|>
literal|0
operator|&&
name|view_size
operator|<=
name|GIMP_VIEWABLE_MAX_PREVIEW_SIZE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|view_border_width
operator|>=
literal|0
operator|&&
name|view_border_width
operator|<=
name|GIMP_VIEW_MAX_BORDER_WIDTH
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|menu_factory
operator|==
name|NULL
operator|||
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|view_type
condition|)
block|{
case|case
name|GIMP_VIEW_TYPE_GRID
case|:
name|editor
operator|->
name|view
operator|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|gimp_container_grid_view_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|view_size
argument_list|,
name|view_border_width
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_VIEW_TYPE_LIST
case|:
name|editor
operator|->
name|view
operator|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|gimp_container_tree_view_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|view_size
argument_list|,
name|view_border_width
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"%s: unknown GimpViewType passed"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|GIMP_IS_LIST
argument_list|(
name|container
argument_list|)
condition|)
name|gimp_container_view_set_reorderable
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
operator|!
name|GIMP_LIST
argument_list|(
name|container
argument_list|)
operator|->
name|sort_func
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu_factory
operator|&&
name|menu_identifier
operator|&&
name|ui_identifier
condition|)
name|gimp_editor_create_menu
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|menu_factory
argument_list|,
name|menu_identifier
argument_list|,
name|ui_identifier
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|editor
operator|->
name|view
argument_list|,
literal|"select-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_editor_select_item
argument_list|)
argument_list|,
name|editor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|editor
operator|->
name|view
argument_list|,
literal|"activate-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_editor_activate_item
argument_list|)
argument_list|,
name|editor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|editor
operator|->
name|view
argument_list|,
literal|"context-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_editor_context_item
argument_list|)
argument_list|,
name|editor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|{
name|GimpObject
modifier|*
name|object
init|=
name|gimp_context_get_by_type
argument_list|(
name|context
argument_list|,
name|gimp_container_get_children_type
argument_list|(
name|container
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_container_editor_select_item
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
operator|(
name|GimpViewable
operator|*
operator|)
name|object
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GtkSelectionMode
DECL|function|gimp_container_editor_get_selection_mode (GimpContainerEditor * editor)
name|gimp_container_editor_get_selection_mode
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
return|return
name|gimp_container_view_get_selection_mode
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_editor_set_selection_mode (GimpContainerEditor * editor,GtkSelectionMode mode)
name|gimp_container_editor_set_selection_mode
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GtkSelectionMode
name|mode
parameter_list|)
block|{
name|gimp_container_view_set_selection_mode
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|mode
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_container_editor_select_item (GtkWidget * widget,GimpViewable * viewable,gpointer insert_data,GimpContainerEditor * editor)
name|gimp_container_editor_select_item
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpContainerEditorClass
modifier|*
name|klass
init|=
name|GIMP_CONTAINER_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|klass
operator|->
name|select_item
condition|)
name|klass
operator|->
name|select_item
argument_list|(
name|editor
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
operator|->
name|ui_manager
condition|)
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
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
operator|->
name|popup_data
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_activate_item (GtkWidget * widget,GimpViewable * viewable,gpointer insert_data,GimpContainerEditor * editor)
name|gimp_container_editor_activate_item
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpContainerEditorClass
modifier|*
name|klass
init|=
name|GIMP_CONTAINER_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|klass
operator|->
name|activate_item
condition|)
name|klass
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

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_context_item (GtkWidget * widget,GimpViewable * viewable,gpointer insert_data,GimpContainerEditor * editor)
name|gimp_container_editor_context_item
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpContainerEditorClass
modifier|*
name|klass
init|=
name|GIMP_CONTAINER_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|klass
operator|->
name|context_item
condition|)
name|klass
operator|->
name|context_item
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
DECL|function|gimp_container_editor_real_context_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_container_editor_real_context_item
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
name|GimpContainer
modifier|*
name|container
init|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
decl_stmt|;
if|if
condition|(
name|viewable
operator|&&
name|gimp_container_have
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_editor_popup_menu
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_container_editor_get_preview (GimpDocked * docked,GimpContext * context,GtkIconSize size)
name|gimp_container_editor_get_preview
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
return|return
name|gimp_docked_get_preview
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|context
argument_list|,
name|size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_set_context (GimpDocked * docked,GimpContext * context)
name|gimp_container_editor_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|gimp_docked_set_context
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpUIManager
modifier|*
DECL|function|gimp_container_editor_get_menu (GimpDocked * docked,const gchar ** ui_path,gpointer * popup_data)
name|gimp_container_editor_get_menu
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|ui_path
parameter_list|,
name|gpointer
modifier|*
name|popup_data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
return|return
name|gimp_docked_get_menu
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|ui_path
argument_list|,
name|popup_data
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_container_editor_has_button_bar (GimpDocked * docked)
name|gimp_container_editor_has_button_bar
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
return|return
name|gimp_docked_has_button_bar
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_editor_set_show_button_bar (GimpDocked * docked,gboolean show)
name|gimp_container_editor_set_show_button_bar
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|gimp_docked_set_show_button_bar
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_container_editor_get_show_button_bar (GimpDocked * docked)
name|gimp_container_editor_get_show_button_bar
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
return|return
name|gimp_docked_get_show_button_bar
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
return|;
block|}
end_function

end_unit

