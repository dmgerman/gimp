begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptemplateview.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpconfig/gimpconfig.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptemplate.h"
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
file|"gimptemplateview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp-ids.h"
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

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_template_view_class_init
parameter_list|(
name|GimpTemplateViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_template_view_init
parameter_list|(
name|GimpTemplateView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_template_view_activate_item
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
name|gimp_template_view_tree_name_edited
parameter_list|(
name|GtkCellRendererText
modifier|*
name|cell
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_str
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|,
name|GimpTemplateView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpContainerEditorClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_template_view_get_type (void)
name|gimp_template_view_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|view_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|view_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|view_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpTemplateViewClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_template_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpTemplateView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_template_view_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_CONTAINER_EDITOR
argument_list|,
literal|"GimpTemplateView"
argument_list|,
operator|&
name|view_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|view_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_template_view_class_init (GimpTemplateViewClass * klass)
name|gimp_template_view_class_init
parameter_list|(
name|GimpTemplateViewClass
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|editor_class
operator|->
name|activate_item
operator|=
name|gimp_template_view_activate_item
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_template_view_init (GimpTemplateView * view)
name|gimp_template_view_init
parameter_list|(
name|GimpTemplateView
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|create_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|new_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|duplicate_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|edit_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|delete_button
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_template_view_new (GimpViewType view_type,GimpContainer * container,GimpContext * context,gint preview_size,gint preview_border_width,GimpMenuFactory * menu_factory)
name|gimp_template_view_new
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
name|preview_size
parameter_list|,
name|gint
name|preview_border_width
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|GimpTemplateView
modifier|*
name|template_view
decl_stmt|;
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|template_view
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEMPLATE_VIEW
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
name|template_view
argument_list|)
argument_list|,
name|view_type
argument_list|,
name|container
argument_list|,
name|context
argument_list|,
name|preview_size
argument_list|,
name|preview_border_width
argument_list|,
name|menu_factory
argument_list|,
literal|"<Templates>"
argument_list|,
literal|"/templates-popup"
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|template_view
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
name|template_view
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_CONTAINER_TREE_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
condition|)
block|{
name|GimpContainerTreeView
modifier|*
name|tree_view
decl_stmt|;
name|tree_view
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|tree_view
operator|->
name|name_cell
operator|->
name|mode
operator|=
name|GTK_CELL_RENDERER_MODE_EDITABLE
expr_stmt|;
name|GTK_CELL_RENDERER_TEXT
argument_list|(
name|tree_view
operator|->
name|name_cell
argument_list|)
operator|->
name|editable
operator|=
name|TRUE
expr_stmt|;
name|tree_view
operator|->
name|editable_cells
operator|=
name|g_list_prepend
argument_list|(
name|tree_view
operator|->
name|editable_cells
argument_list|,
name|tree_view
operator|->
name|name_cell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|tree_view
operator|->
name|name_cell
argument_list|,
literal|"edited"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_template_view_tree_name_edited
argument_list|)
argument_list|,
name|template_view
argument_list|)
expr_stmt|;
block|}
name|template_view
operator|->
name|create_button
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
literal|"templates"
argument_list|,
literal|"templates-create-image"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|template_view
operator|->
name|new_button
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
literal|"templates"
argument_list|,
literal|"templates-new"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|template_view
operator|->
name|duplicate_button
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
literal|"templates"
argument_list|,
literal|"templates-duplicate"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|template_view
operator|->
name|edit_button
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
literal|"templates"
argument_list|,
literal|"templates-edit"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|template_view
operator|->
name|delete_button
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
literal|"templates"
argument_list|,
literal|"templates-delete"
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
name|template_view
operator|->
name|create_button
argument_list|)
argument_list|,
name|GIMP_TYPE_TEMPLATE
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
name|template_view
operator|->
name|duplicate_button
argument_list|)
argument_list|,
name|GIMP_TYPE_TEMPLATE
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
name|template_view
operator|->
name|edit_button
argument_list|)
argument_list|,
name|GIMP_TYPE_TEMPLATE
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
name|template_view
operator|->
name|delete_button
argument_list|)
argument_list|,
name|GIMP_TYPE_TEMPLATE
argument_list|)
expr_stmt|;
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
name|template_view
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_template_view_activate_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_template_view_activate_item
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
name|GimpTemplateView
modifier|*
name|view
init|=
name|GIMP_TEMPLATE_VIEW
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpContext
modifier|*
name|context
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
name|context
operator|=
name|gimp_container_view_get_context
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
name|create_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_template_view_tree_name_edited (GtkCellRendererText * cell,const gchar * path_str,const gchar * new_name,GimpTemplateView * view)
name|gimp_template_view_tree_name_edited
parameter_list|(
name|GtkCellRendererText
modifier|*
name|cell
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_str
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|,
name|GimpTemplateView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContainerTreeView
modifier|*
name|tree_view
decl_stmt|;
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|tree_view
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
argument_list|)
expr_stmt|;
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
name|GimpObject
modifier|*
name|object
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|old_name
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|tree_view
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|tree_view
operator|->
name|model_column_renderer
argument_list|,
operator|&
name|renderer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|object
operator|=
name|GIMP_OBJECT
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|old_name
operator|=
name|gimp_object_get_name
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|old_name
condition|)
name|old_name
operator|=
literal|""
expr_stmt|;
if|if
condition|(
operator|!
name|new_name
condition|)
name|new_name
operator|=
literal|""
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|old_name
argument_list|,
name|new_name
argument_list|)
condition|)
block|{
name|gimp_object_set_name
argument_list|(
name|object
argument_list|,
name|new_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|name
init|=
name|gimp_viewable_get_description
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|tree_view
operator|->
name|model
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|tree_view
operator|->
name|model_column_name
argument_list|,
name|name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
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

