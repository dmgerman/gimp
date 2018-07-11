begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdocumentview.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"core/gimpimagefile.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocumentview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
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
name|gimp_document_view_activate_item
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
name|GList
modifier|*
name|gimp_document_view_drag_uri_list
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDocumentView,gimp_document_view,GIMP_TYPE_CONTAINER_EDITOR)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDocumentView
argument_list|,
argument|gimp_document_view
argument_list|,
argument|GIMP_TYPE_CONTAINER_EDITOR
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_document_view_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_document_view_class_init
parameter_list|(
name|GimpDocumentViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpContainerEditorClass
modifier|*
name|editor_class
init|=
name|GIMP_CONTAINER_EDITOR_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|editor_class
operator|->
name|activate_item
operator|=
name|gimp_document_view_activate_item
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_document_view_init (GimpDocumentView * view)
name|gimp_document_view_init
parameter_list|(
name|GimpDocumentView
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|open_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|remove_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|refresh_button
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_document_view_new (GimpViewType view_type,GimpContainer * container,GimpContext * context,gint view_size,gint view_border_width,GimpMenuFactory * menu_factory)
name|gimp_document_view_new
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
name|GimpDocumentView
modifier|*
name|document_view
decl_stmt|;
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
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
name|NULL
argument_list|)
expr_stmt|;
name|document_view
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DOCUMENT_VIEW
argument_list|,
literal|"view-type"
argument_list|,
name|view_type
argument_list|,
literal|"container"
argument_list|,
name|container
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
literal|"view-size"
argument_list|,
name|view_size
argument_list|,
literal|"view-border-width"
argument_list|,
name|view_border_width
argument_list|,
literal|"menu-factory"
argument_list|,
name|menu_factory
argument_list|,
literal|"menu-identifier"
argument_list|,
literal|"<Documents>"
argument_list|,
literal|"ui-path"
argument_list|,
literal|"/documents-popup"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|document_view
argument_list|)
expr_stmt|;
name|document_view
operator|->
name|open_button
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
literal|"documents"
argument_list|,
literal|"documents-open"
argument_list|,
literal|"documents-raise-or-open"
argument_list|,
name|GDK_SHIFT_MASK
argument_list|,
literal|"documents-file-open-dialog"
argument_list|,
name|gimp_get_toggle_behavior_mask
argument_list|()
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_view_enable_dnd
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GTK_BUTTON
argument_list|(
name|document_view
operator|->
name|open_button
argument_list|)
argument_list|,
name|GIMP_TYPE_IMAGEFILE
argument_list|)
expr_stmt|;
name|document_view
operator|->
name|remove_button
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
literal|"documents"
argument_list|,
literal|"documents-remove"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_view_enable_dnd
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GTK_BUTTON
argument_list|(
name|document_view
operator|->
name|remove_button
argument_list|)
argument_list|,
name|GIMP_TYPE_IMAGEFILE
argument_list|)
expr_stmt|;
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
literal|"documents"
argument_list|,
literal|"documents-clear"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|document_view
operator|->
name|refresh_button
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
literal|"documents"
argument_list|,
literal|"documents-recreate-preview"
argument_list|,
literal|"documents-reload-previews"
argument_list|,
name|GDK_SHIFT_MASK
argument_list|,
literal|"documents-remove-dangling"
argument_list|,
name|gimp_get_toggle_behavior_mask
argument_list|()
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
name|GtkWidget
modifier|*
name|dnd_widget
decl_stmt|;
name|dnd_widget
operator|=
name|gimp_container_view_get_dnd_widget
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|gimp_dnd_uri_list_source_add
argument_list|(
name|dnd_widget
argument_list|,
name|gimp_document_view_drag_uri_list
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
name|gimp_ui_manager_update
argument_list|(
name|gimp_editor_get_ui_manager
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|document_view
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_document_view_activate_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_document_view_activate_item
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
name|GimpDocumentView
modifier|*
name|view
init|=
name|GIMP_DOCUMENT_VIEW
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
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
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
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
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|open_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|gimp_document_view_drag_uri_list (GtkWidget * widget,gpointer data)
name|gimp_document_view_drag_uri_list
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpViewable
modifier|*
name|viewable
init|=
name|gimp_dnd_get_drag_data
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|viewable
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|uri
init|=
name|gimp_object_get_name
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
return|return
name|g_list_append
argument_list|(
name|NULL
argument_list|,
name|g_strdup
argument_list|(
name|uri
argument_list|)
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

