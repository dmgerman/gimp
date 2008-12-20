begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdatafactoryview.c  * Copyright (C) 2001-2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"config/gimpbaseconfig.h"
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
file|"core/gimpdata.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
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
file|"gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
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

begin_struct
DECL|struct|_GimpDataFactoryViewPriv
struct|struct
name|_GimpDataFactoryViewPriv
block|{
DECL|member|factory
name|GimpDataFactory
modifier|*
name|factory
decl_stmt|;
DECL|member|edit_button
name|GtkWidget
modifier|*
name|edit_button
decl_stmt|;
DECL|member|new_button
name|GtkWidget
modifier|*
name|new_button
decl_stmt|;
DECL|member|duplicate_button
name|GtkWidget
modifier|*
name|duplicate_button
decl_stmt|;
DECL|member|delete_button
name|GtkWidget
modifier|*
name|delete_button
decl_stmt|;
DECL|member|refresh_button
name|GtkWidget
modifier|*
name|refresh_button
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_data_factory_view_activate_item
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
name|gimp_data_factory_view_tree_name_edited
parameter_list|(
name|GtkCellRendererText
modifier|*
name|cell
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDataFactoryView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDataFactoryView,gimp_data_factory_view,GIMP_TYPE_CONTAINER_EDITOR)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDataFactoryView
argument_list|,
argument|gimp_data_factory_view
argument_list|,
argument|GIMP_TYPE_CONTAINER_EDITOR
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_data_factory_view_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_data_factory_view_class_init
parameter_list|(
name|GimpDataFactoryViewClass
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
name|gimp_data_factory_view_activate_item
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpDataFactoryViewPriv
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_factory_view_init (GimpDataFactoryView * view)
name|gimp_data_factory_view_init
parameter_list|(
name|GimpDataFactoryView
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|view
argument_list|,
name|GIMP_TYPE_DATA_FACTORY_VIEW
argument_list|,
name|GimpDataFactoryViewPriv
argument_list|)
expr_stmt|;
name|view
operator|->
name|priv
operator|->
name|edit_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|priv
operator|->
name|new_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|priv
operator|->
name|duplicate_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|priv
operator|->
name|delete_button
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|priv
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
DECL|function|gimp_data_factory_view_new (GimpViewType view_type,GimpDataFactory * factory,GimpContext * context,gint view_size,gint view_border_width,GimpMenuFactory * menu_factory,const gchar * menu_identifier,const gchar * ui_identifier,const gchar * action_group)
name|gimp_data_factory_view_new
parameter_list|(
name|GimpViewType
name|view_type
parameter_list|,
name|GimpDataFactory
modifier|*
name|factory
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
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_group
parameter_list|)
block|{
name|GimpDataFactoryView
modifier|*
name|factory_view
decl_stmt|;
name|factory_view
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DATA_FACTORY_VIEW
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_data_factory_view_construct
argument_list|(
name|factory_view
argument_list|,
name|view_type
argument_list|,
name|factory
argument_list|,
name|context
argument_list|,
name|view_size
argument_list|,
name|view_border_width
argument_list|,
name|menu_factory
argument_list|,
name|menu_identifier
argument_list|,
name|ui_identifier
argument_list|,
name|action_group
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|factory_view
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|GTK_WIDGET
argument_list|(
name|factory_view
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_data_factory_view_get_edit_button (GimpDataFactoryView * factory_view)
name|gimp_data_factory_view_get_edit_button
parameter_list|(
name|GimpDataFactoryView
modifier|*
name|factory_view
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY_VIEW
argument_list|(
name|factory_view
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|factory_view
operator|->
name|priv
operator|->
name|edit_button
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_data_factory_view_get_duplicate_button (GimpDataFactoryView * factory_view)
name|gimp_data_factory_view_get_duplicate_button
parameter_list|(
name|GimpDataFactoryView
modifier|*
name|factory_view
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY_VIEW
argument_list|(
name|factory_view
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|factory_view
operator|->
name|priv
operator|->
name|duplicate_button
return|;
block|}
end_function

begin_function
name|GimpDataFactory
modifier|*
DECL|function|gimp_data_factory_view_get_data_factory (GimpDataFactoryView * factory_view)
name|gimp_data_factory_view_get_data_factory
parameter_list|(
name|GimpDataFactoryView
modifier|*
name|factory_view
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY_VIEW
argument_list|(
name|factory_view
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|factory_view
operator|->
name|priv
operator|->
name|factory
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_data_factory_view_get_children_type (GimpDataFactoryView * factory_view)
name|gimp_data_factory_view_get_children_type
parameter_list|(
name|GimpDataFactoryView
modifier|*
name|factory_view
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY_VIEW
argument_list|(
name|factory_view
argument_list|)
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
return|return
name|gimp_container_get_children_type
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|factory_view
operator|->
name|priv
operator|->
name|factory
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_data_factory_view_has_data_new_func (GimpDataFactoryView * factory_view)
name|gimp_data_factory_view_has_data_new_func
parameter_list|(
name|GimpDataFactoryView
modifier|*
name|factory_view
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY_VIEW
argument_list|(
name|factory_view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|gimp_data_factory_has_data_new_func
argument_list|(
name|factory_view
operator|->
name|priv
operator|->
name|factory
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_data_factory_view_have (GimpDataFactoryView * factory_view,GimpObject * object)
name|gimp_data_factory_view_have
parameter_list|(
name|GimpDataFactoryView
modifier|*
name|factory_view
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY_VIEW
argument_list|(
name|factory_view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|gimp_container_have
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|factory_view
operator|->
name|priv
operator|->
name|factory
argument_list|)
argument_list|,
name|object
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_data_factory_view_construct (GimpDataFactoryView * factory_view,GimpViewType view_type,GimpDataFactory * factory,GimpContext * context,gint view_size,gint view_border_width,GimpMenuFactory * menu_factory,const gchar * menu_identifier,const gchar * ui_identifier,const gchar * action_group)
name|gimp_data_factory_view_construct
parameter_list|(
name|GimpDataFactoryView
modifier|*
name|factory_view
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|,
name|GimpDataFactory
modifier|*
name|factory
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
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_group
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY_VIEW
argument_list|(
name|factory_view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY
argument_list|(
name|factory
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
name|factory_view
operator|->
name|priv
operator|->
name|factory
operator|=
name|factory
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_container_editor_construct
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|factory_view
argument_list|)
argument_list|,
name|view_type
argument_list|,
name|gimp_data_factory_get_container
argument_list|(
name|factory
argument_list|)
argument_list|,
name|context
argument_list|,
name|view_size
argument_list|,
name|view_border_width
argument_list|,
name|menu_factory
argument_list|,
name|menu_identifier
argument_list|,
name|ui_identifier
argument_list|)
condition|)
block|{
return|return
name|FALSE
return|;
block|}
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|factory_view
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
name|gimp_container_tree_view_connect_name_edited
argument_list|(
name|tree_view
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_factory_view_tree_name_edited
argument_list|)
argument_list|,
name|factory_view
argument_list|)
expr_stmt|;
block|}
name|str
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-edit"
argument_list|,
name|action_group
argument_list|)
expr_stmt|;
name|factory_view
operator|->
name|priv
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
name|action_group
argument_list|,
name|str
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_data_factory_view_has_data_new_func
argument_list|(
name|factory_view
argument_list|)
condition|)
block|{
name|str
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-new"
argument_list|,
name|action_group
argument_list|)
expr_stmt|;
name|factory_view
operator|->
name|priv
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
name|action_group
argument_list|,
name|str
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
name|str
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-duplicate"
argument_list|,
name|action_group
argument_list|)
expr_stmt|;
name|factory_view
operator|->
name|priv
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
name|action_group
argument_list|,
name|str
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-delete"
argument_list|,
name|action_group
argument_list|)
expr_stmt|;
name|factory_view
operator|->
name|priv
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
name|action_group
argument_list|,
name|str
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-refresh"
argument_list|,
name|action_group
argument_list|)
expr_stmt|;
name|factory_view
operator|->
name|priv
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
name|action_group
argument_list|,
name|str
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
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
name|factory_view
operator|->
name|priv
operator|->
name|edit_button
argument_list|)
argument_list|,
name|gimp_container_get_children_type
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|factory
argument_list|)
argument_list|)
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
name|factory_view
operator|->
name|priv
operator|->
name|duplicate_button
argument_list|)
argument_list|,
name|gimp_container_get_children_type
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|factory
argument_list|)
argument_list|)
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
name|factory_view
operator|->
name|priv
operator|->
name|delete_button
argument_list|)
argument_list|,
name|gimp_container_get_children_type
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|factory
argument_list|)
argument_list|)
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
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_factory_view_activate_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_data_factory_view_activate_item
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
name|GimpDataFactoryView
modifier|*
name|view
init|=
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GimpData
modifier|*
name|data
init|=
name|GIMP_DATA
argument_list|(
name|viewable
argument_list|)
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
if|if
condition|(
name|data
operator|&&
name|gimp_data_factory_view_have
argument_list|(
name|view
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
condition|)
block|{
if|if
condition|(
name|view
operator|->
name|priv
operator|->
name|edit_button
operator|&&
name|GTK_WIDGET_SENSITIVE
argument_list|(
name|view
operator|->
name|priv
operator|->
name|edit_button
argument_list|)
condition|)
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|priv
operator|->
name|edit_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_factory_view_tree_name_edited (GtkCellRendererText * cell,const gchar * path_str,const gchar * new_name,GimpDataFactoryView * view)
name|gimp_data_factory_view_tree_name_edited
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
name|GimpDataFactoryView
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
name|GimpData
modifier|*
name|data
decl_stmt|;
name|gchar
modifier|*
name|name
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
name|GIMP_CONTAINER_TREE_VIEW_COLUMN_RENDERER
argument_list|,
operator|&
name|renderer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
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
name|name
operator|=
name|g_strstrip
argument_list|(
name|g_strdup
argument_list|(
name|new_name
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|writable
operator|&&
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
block|{
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|name
operator|=
name|gimp_viewable_get_description
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|GIMP_CONTAINER_TREE_VIEW_COLUMN_NAME
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

