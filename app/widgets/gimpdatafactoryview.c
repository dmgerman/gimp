begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdatafactoryview.c  * Copyright (C) 2001-2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewrenderer.h"
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
name|gimp_data_factory_view_class_init
parameter_list|(
name|GimpDataFactoryViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_factory_view_init
parameter_list|(
name|GimpDataFactoryView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_factory_view_edit_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataFactoryView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_factory_view_new_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataFactoryView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_factory_view_duplicate_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataFactoryView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_factory_view_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataFactoryView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_factory_view_refresh_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataFactoryView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_factory_view_select_item
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
DECL|function|gimp_data_factory_view_get_type (void)
name|gimp_data_factory_view_get_type
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
name|GimpDataFactoryViewClass
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
name|gimp_data_factory_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpDataFactoryView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_data_factory_view_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_CONTAINER_EDITOR
argument_list|,
literal|"GimpDataFactoryView"
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
DECL|function|gimp_data_factory_view_class_init (GimpDataFactoryViewClass * klass)
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|editor_class
operator|->
name|select_item
operator|=
name|gimp_data_factory_view_select_item
expr_stmt|;
name|editor_class
operator|->
name|activate_item
operator|=
name|gimp_data_factory_view_activate_item
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
name|edit_button
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
name|delete_button
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
DECL|function|gimp_data_factory_view_new (GimpViewType view_type,GimpDataFactory * factory,GimpDataEditFunc edit_func,GimpContext * context,gint preview_size,gint preview_border_width,GimpMenuFactory * menu_factory,const gchar * menu_identifier,const gchar * ui_identifier)
name|gimp_data_factory_view_new
parameter_list|(
name|GimpViewType
name|view_type
parameter_list|,
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpDataEditFunc
name|edit_func
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
name|edit_func
argument_list|,
name|context
argument_list|,
name|preview_size
argument_list|,
name|preview_border_width
argument_list|,
name|menu_factory
argument_list|,
name|menu_identifier
argument_list|,
name|ui_identifier
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
name|gboolean
DECL|function|gimp_data_factory_view_construct (GimpDataFactoryView * factory_view,GimpViewType view_type,GimpDataFactory * factory,GimpDataEditFunc edit_func,GimpContext * context,gint preview_size,gint preview_border_width,GimpMenuFactory * menu_factory,const gchar * menu_identifier,const gchar * ui_identifier)
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
name|GimpDataEditFunc
name|edit_func
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
name|GimpContainerEditor
modifier|*
name|editor
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
name|preview_size
operator|>
literal|0
operator|&&
name|preview_size
operator|<=
name|GIMP_VIEWABLE_MAX_PREVIEW_SIZE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|preview_border_width
operator|>=
literal|0
operator|&&
name|preview_border_width
operator|<=
name|GIMP_PREVIEW_MAX_BORDER_WIDTH
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|factory_view
operator|->
name|factory
operator|=
name|factory
expr_stmt|;
name|factory_view
operator|->
name|data_edit_func
operator|=
name|edit_func
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
name|factory
operator|->
name|container
argument_list|,
name|context
argument_list|,
name|preview_size
argument_list|,
name|preview_border_width
argument_list|,
name|FALSE
argument_list|,
comment|/* reorderable */
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
name|gimp_data_factory_view_tree_name_edited
argument_list|)
argument_list|,
name|factory_view
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|edit_func
condition|)
block|{
name|factory_view
operator|->
name|edit_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GIMP_STOCK_EDIT
argument_list|,
name|_
argument_list|(
literal|"Edit"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_factory_view_edit_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|factory_view
operator|->
name|factory
operator|->
name|data_new_func
condition|)
block|{
name|factory_view
operator|->
name|new_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GTK_STOCK_NEW
argument_list|,
name|_
argument_list|(
literal|"New"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_factory_view_new_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
name|factory_view
operator|->
name|duplicate_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GIMP_STOCK_DUPLICATE
argument_list|,
name|_
argument_list|(
literal|"Duplicate"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_factory_view_duplicate_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|factory_view
operator|->
name|delete_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GTK_STOCK_DELETE
argument_list|,
name|_
argument_list|(
literal|"Delete"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_factory_view_delete_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|factory_view
operator|->
name|refresh_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GTK_STOCK_REFRESH
argument_list|,
name|_
argument_list|(
literal|"Refresh"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_factory_view_refresh_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
comment|/*  set button sensitivity  */
if|if
condition|(
name|GIMP_CONTAINER_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
operator|->
name|select_item
condition|)
name|GIMP_CONTAINER_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
operator|->
name|select_item
argument_list|(
name|editor
argument_list|,
operator|(
name|GimpViewable
operator|*
operator|)
name|gimp_context_get_by_type
argument_list|(
name|context
argument_list|,
name|factory
operator|->
name|container
operator|->
name|children_type
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|factory_view
operator|->
name|edit_button
condition|)
block|{
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
name|edit_button
argument_list|)
argument_list|,
name|factory
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
block|}
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
name|duplicate_button
argument_list|)
argument_list|,
name|factory
operator|->
name|container
operator|->
name|children_type
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
name|delete_button
argument_list|)
argument_list|,
name|factory
operator|->
name|container
operator|->
name|children_type
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
DECL|function|gimp_data_factory_view_edit_clicked (GtkWidget * widget,GimpDataFactoryView * view)
name|gimp_data_factory_view_edit_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataFactoryView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpData
modifier|*
name|data
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
argument_list|)
expr_stmt|;
name|data
operator|=
operator|(
name|GimpData
operator|*
operator|)
name|gimp_context_get_by_type
argument_list|(
name|context
argument_list|,
name|view
operator|->
name|factory
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|data_edit_func
operator|&&
name|data
operator|&&
name|gimp_container_have
argument_list|(
name|view
operator|->
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
condition|)
block|{
name|view
operator|->
name|data_edit_func
argument_list|(
name|data
argument_list|,
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_factory_view_new_clicked (GtkWidget * widget,GimpDataFactoryView * view)
name|gimp_data_factory_view_new_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataFactoryView
modifier|*
name|view
parameter_list|)
block|{
if|if
condition|(
name|view
operator|->
name|factory
operator|->
name|data_new_func
condition|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpData
modifier|*
name|data
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
argument_list|)
expr_stmt|;
name|data
operator|=
name|gimp_data_factory_data_new
argument_list|(
name|view
operator|->
name|factory
argument_list|,
name|_
argument_list|(
literal|"Untitled"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
block|{
name|gimp_context_set_by_type
argument_list|(
name|context
argument_list|,
name|view
operator|->
name|factory
operator|->
name|container
operator|->
name|children_type
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_data_factory_view_edit_clicked
argument_list|(
name|NULL
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_factory_view_duplicate_clicked (GtkWidget * widget,GimpDataFactoryView * view)
name|gimp_data_factory_view_duplicate_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataFactoryView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpData
modifier|*
name|data
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
argument_list|)
expr_stmt|;
name|data
operator|=
operator|(
name|GimpData
operator|*
operator|)
name|gimp_context_get_by_type
argument_list|(
name|context
argument_list|,
name|view
operator|->
name|factory
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|&&
name|gimp_container_have
argument_list|(
name|view
operator|->
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
condition|)
block|{
name|GimpData
modifier|*
name|new_data
decl_stmt|;
name|new_data
operator|=
name|gimp_data_factory_data_duplicate
argument_list|(
name|view
operator|->
name|factory
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_data
condition|)
block|{
name|gimp_context_set_by_type
argument_list|(
name|context
argument_list|,
name|view
operator|->
name|factory
operator|->
name|container
operator|->
name|children_type
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|new_data
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_data_factory_view_edit_clicked
argument_list|(
name|NULL
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_typedef
DECL|typedef|GimpDataDeleteData
typedef|typedef
name|struct
name|_GimpDataDeleteData
name|GimpDataDeleteData
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDataDeleteData
struct|struct
name|_GimpDataDeleteData
block|{
DECL|member|factory
name|GimpDataFactory
modifier|*
name|factory
decl_stmt|;
DECL|member|data
name|GimpData
modifier|*
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|void
DECL|function|gimp_data_factory_view_delete_callback (GtkWidget * widget,gboolean delete,gpointer data)
name|gimp_data_factory_view_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|delete
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDataDeleteData
modifier|*
name|delete_data
init|=
name|data
decl_stmt|;
if|if
condition|(
name|gimp_container_have
argument_list|(
name|delete_data
operator|->
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|delete_data
operator|->
name|data
argument_list|)
argument_list|)
condition|)
block|{
name|g_object_ref
argument_list|(
name|delete_data
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_container_remove
argument_list|(
name|delete_data
operator|->
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|delete_data
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|delete_data
operator|->
name|data
operator|->
name|filename
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_data_delete_from_disk
argument_list|(
name|delete_data
operator|->
name|data
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
block|}
name|g_object_unref
argument_list|(
name|delete_data
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_factory_view_delete_clicked (GtkWidget * widget,GimpDataFactoryView * view)
name|gimp_data_factory_view_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataFactoryView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpData
modifier|*
name|data
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
argument_list|)
expr_stmt|;
name|data
operator|=
operator|(
name|GimpData
operator|*
operator|)
name|gimp_context_get_by_type
argument_list|(
name|context
argument_list|,
name|view
operator|->
name|factory
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|&&
name|data
operator|->
name|deletable
operator|&&
name|gimp_container_have
argument_list|(
name|view
operator|->
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
condition|)
block|{
name|GimpDataDeleteData
modifier|*
name|delete_data
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|delete_data
operator|=
name|g_new0
argument_list|(
name|GimpDataDeleteData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|delete_data
operator|->
name|factory
operator|=
name|view
operator|->
name|factory
expr_stmt|;
name|delete_data
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Are you sure you want to delete '%s' "
literal|"from the list and from disk?"
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_query_boolean_box
argument_list|(
name|_
argument_list|(
literal|"Delete Data Object"
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_QUESTION
argument_list|,
name|str
argument_list|,
name|GTK_STOCK_DELETE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|G_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|gimp_data_factory_view_delete_callback
argument_list|,
name|delete_data
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_free
argument_list|,
name|delete_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_factory_view_refresh_clicked (GtkWidget * widget,GimpDataFactoryView * view)
name|gimp_data_factory_view_refresh_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataFactoryView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_data_factory_data_save
argument_list|(
name|view
operator|->
name|factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|view
operator|->
name|factory
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_factory_view_select_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_data_factory_view_select_item
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
decl_stmt|;
name|gboolean
name|edit_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|duplicate_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|delete_sensitive
init|=
name|FALSE
decl_stmt|;
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
name|view
operator|=
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|editor
argument_list|)
expr_stmt|;
if|if
condition|(
name|viewable
operator|&&
name|gimp_container_have
argument_list|(
name|view
operator|->
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
condition|)
block|{
name|GimpData
modifier|*
name|data
init|=
name|GIMP_DATA
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|edit_sensitive
operator|=
operator|(
name|view
operator|->
name|data_edit_func
operator|!=
name|NULL
operator|)
expr_stmt|;
name|duplicate_sensitive
operator|=
operator|(
name|GIMP_DATA_GET_CLASS
argument_list|(
name|data
argument_list|)
operator|->
name|duplicate
operator|!=
name|NULL
operator|)
expr_stmt|;
name|delete_sensitive
operator|=
name|data
operator|->
name|deletable
expr_stmt|;
block|}
if|if
condition|(
name|view
operator|->
name|edit_button
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|edit_button
argument_list|,
name|edit_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|duplicate_button
argument_list|,
name|duplicate_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|delete_button
argument_list|,
name|delete_sensitive
argument_list|)
expr_stmt|;
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
decl_stmt|;
name|GimpData
modifier|*
name|data
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
name|view
operator|=
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|&&
name|gimp_container_have
argument_list|(
name|view
operator|->
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_data_factory_view_edit_clicked
argument_list|(
name|NULL
argument_list|,
name|view
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
name|GimpPreviewRenderer
modifier|*
name|renderer
decl_stmt|;
name|GimpData
modifier|*
name|data
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
name|data
operator|->
name|writable
condition|)
block|{
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
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

