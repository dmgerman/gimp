begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdatafactoryview.c  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
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
file|"libgimpmath/gimpmath.h"
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
file|"gimpcontainerlistview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
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
name|gimp_data_factory_view_destroy
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
name|GtkTypeInfo
name|view_info
init|=
block|{
literal|"GimpDataFactoryView"
block|,
sizeof|sizeof
argument_list|(
name|GimpDataFactoryView
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpDataFactoryViewClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_data_factory_view_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_data_factory_view_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|view_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_CONTAINER_EDITOR
argument_list|,
operator|&
name|view_info
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
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpContainerEditorClass
modifier|*
name|editor_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|editor_class
operator|=
operator|(
name|GimpContainerEditorClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_data_factory_view_destroy
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
name|view
operator|->
name|refresh_button
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_factory_view_destroy (GtkObject * object)
name|gimp_data_factory_view_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDataFactoryView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
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
DECL|function|gimp_data_factory_view_new (GimpViewType view_type,GimpDataFactory * factory,GimpDataEditFunc edit_func,GimpContext * context,gint preview_size,gint min_items_x,gint min_items_y,GimpContainerContextFunc context_func)
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
name|min_items_x
parameter_list|,
name|gint
name|min_items_y
parameter_list|,
name|GimpContainerContextFunc
name|context_func
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
name|min_items_x
argument_list|,
name|min_items_y
argument_list|,
name|context_func
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|factory_view
argument_list|)
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
DECL|function|gimp_data_factory_view_construct (GimpDataFactoryView * factory_view,GimpViewType view_type,GimpDataFactory * factory,GimpDataEditFunc edit_func,GimpContext * context,gint preview_size,gint min_items_x,gint min_items_y,GimpContainerContextFunc context_func)
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
name|min_items_x
parameter_list|,
name|gint
name|min_items_y
parameter_list|,
name|GimpContainerContextFunc
name|context_func
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|factory_view
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
name|factory
operator|!=
name|NULL
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
literal|64
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|min_items_x
operator|>
literal|0
operator|&&
name|min_items_x
operator|<=
literal|64
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|min_items_y
operator|>
literal|0
operator|&&
name|min_items_y
operator|<=
literal|64
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
name|min_items_x
argument_list|,
name|min_items_y
argument_list|,
name|context_func
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
name|factory_view
operator|->
name|new_button
operator|=
name|gimp_container_view_add_button
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GIMP_STOCK_NEW
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
name|factory_view
operator|->
name|duplicate_button
operator|=
name|gimp_container_view_add_button
argument_list|(
name|editor
operator|->
name|view
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
name|edit_button
operator|=
name|gimp_container_view_add_button
argument_list|(
name|editor
operator|->
name|view
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
name|factory_view
operator|->
name|delete_button
operator|=
name|gimp_container_view_add_button
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GIMP_STOCK_DELETE
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
name|gimp_container_view_add_button
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GIMP_STOCK_REFRESH
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
name|GimpData
modifier|*
name|data
decl_stmt|;
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
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
operator|->
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
name|GimpData
modifier|*
name|data
decl_stmt|;
name|data
operator|=
operator|(
name|GimpData
operator|*
operator|)
name|gimp_context_get_by_type
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
operator|->
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
name|gimp_data_duplicate
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_data
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
modifier|*
name|ext
decl_stmt|;
name|gint
name|copy_len
decl_stmt|;
name|gint
name|number
decl_stmt|;
name|gchar
modifier|*
name|new_name
decl_stmt|;
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|ext
operator|=
name|strrchr
argument_list|(
name|name
argument_list|,
literal|'#'
argument_list|)
expr_stmt|;
name|copy_len
operator|=
name|strlen
argument_list|(
name|_
argument_list|(
literal|"copy"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|strlen
argument_list|(
name|name
argument_list|)
operator|>=
name|copy_len
operator|&&
name|strcmp
argument_list|(
operator|&
name|name
index|[
name|strlen
argument_list|(
name|name
argument_list|)
operator|-
name|copy_len
index|]
argument_list|,
name|_
argument_list|(
literal|"copy"
argument_list|)
argument_list|)
operator|==
literal|0
operator|)
operator|||
operator|(
name|ext
operator|&&
operator|(
name|number
operator|=
name|atoi
argument_list|(
name|ext
operator|+
literal|1
argument_list|)
operator|)
operator|>
literal|0
operator|&&
operator|(
call|(
name|gint
call|)
argument_list|(
name|log10
argument_list|(
name|number
argument_list|)
operator|+
literal|1
argument_list|)
operator|)
operator|==
name|strlen
argument_list|(
name|ext
operator|+
literal|1
argument_list|)
operator|)
condition|)
block|{
comment|/* don't have redundant "copy"s */
name|new_name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|new_name
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s copy"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|new_data
argument_list|)
argument_list|,
name|new_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|new_name
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|view
operator|->
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|new_data
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_context_set_by_type
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
operator|->
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
name|GimpData
modifier|*
name|data
decl_stmt|;
name|data
operator|=
operator|(
name|GimpData
operator|*
operator|)
name|gimp_context_get_by_type
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
operator|->
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
argument_list|)
expr_stmt|;
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
decl_stmt|;
name|delete_data
operator|=
operator|(
name|GimpDataDeleteData
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|delete
condition|)
return|return;
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
if|if
condition|(
name|delete_data
operator|->
name|data
operator|->
name|filename
condition|)
name|gimp_data_delete_from_disk
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
name|GimpData
modifier|*
name|data
decl_stmt|;
name|data
operator|=
operator|(
name|GimpData
operator|*
operator|)
name|gimp_context_get_by_type
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
operator|->
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
literal|"Are you sure you want to delete\n"
literal|"\"%s\" from the list and from disk?"
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
name|gimp_standard_help_func
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|str
argument_list|,
name|GIMP_STOCK_DELETE
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
name|duplicate_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|edit_sensitive
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
name|duplicate_sensitive
operator|=
operator|(
name|GIMP_DATA_GET_CLASS
argument_list|(
name|viewable
argument_list|)
operator|->
name|duplicate
operator|!=
name|NULL
operator|)
expr_stmt|;
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
name|delete_sensitive
operator|=
name|TRUE
expr_stmt|;
comment|/* TODO: check permissions */
block|}
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
name|edit_button
argument_list|,
name|edit_sensitive
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

end_unit

