begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainerview.c  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29c7e97c0103
block|{
DECL|enumerator|SET_CONTAINER
name|SET_CONTAINER
block|,
DECL|enumerator|INSERT_ITEM
name|INSERT_ITEM
block|,
DECL|enumerator|REMOVE_ITEM
name|REMOVE_ITEM
block|,
DECL|enumerator|REORDER_ITEM
name|REORDER_ITEM
block|,
DECL|enumerator|SELECT_ITEM
name|SELECT_ITEM
block|,
DECL|enumerator|ACTIVATE_ITEM
name|ACTIVATE_ITEM
block|,
DECL|enumerator|CONTEXT_ITEM
name|CONTEXT_ITEM
block|,
DECL|enumerator|CLEAR_ITEMS
name|CLEAR_ITEMS
block|,
DECL|enumerator|SET_PREVIEW_SIZE
name|SET_PREVIEW_SIZE
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_container_view_class_init
parameter_list|(
name|GimpContainerViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_view_init
parameter_list|(
name|GimpContainerView
modifier|*
name|panel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_view_destroy
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
name|gimp_container_view_real_set_container
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_view_clear_items
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_view_real_clear_items
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_view_add_foreach
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_view_add
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_view_remove
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_view_reorder
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|new_index
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_view_context_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_view_drop_viewable_callback
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
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|view_signals
specifier|static
name|guint
name|view_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkVBoxClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_container_view_get_type (void)
name|gimp_container_view_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|guint
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
literal|"GimpContainerView"
block|,
sizeof|sizeof
argument_list|(
name|GimpContainerView
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpContainerViewClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_container_view_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_container_view_init
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
name|GTK_TYPE_VBOX
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
DECL|function|gimp_container_view_class_init (GimpContainerViewClass * klass)
name|gimp_container_view_class_init
parameter_list|(
name|GimpContainerViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GTK_TYPE_VBOX
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|SET_CONTAINER
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"set_container"
argument_list|,
name|GTK_RUN_LAST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpContainerViewClass
argument_list|,
name|set_container
argument_list|)
argument_list|,
name|gtk_marshal_NONE__OBJECT
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|INSERT_ITEM
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"insert_item"
argument_list|,
name|GTK_RUN_LAST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpContainerViewClass
argument_list|,
name|insert_item
argument_list|)
argument_list|,
name|gimp_marshal_POINTER__POINTER_INT
argument_list|,
name|GTK_TYPE_POINTER
argument_list|,
literal|2
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|,
name|GTK_TYPE_INT
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|REMOVE_ITEM
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"remove_item"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpContainerViewClass
argument_list|,
name|remove_item
argument_list|)
argument_list|,
name|gtk_marshal_NONE__POINTER_POINTER
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|,
name|GTK_TYPE_POINTER
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|REORDER_ITEM
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"reorder_item"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpContainerViewClass
argument_list|,
name|reorder_item
argument_list|)
argument_list|,
name|gtk_marshal_NONE__POINTER_INT_POINTER
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|3
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|,
name|GTK_TYPE_INT
argument_list|,
name|GTK_TYPE_POINTER
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|SELECT_ITEM
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"select_item"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpContainerViewClass
argument_list|,
name|select_item
argument_list|)
argument_list|,
name|gtk_marshal_NONE__POINTER_POINTER
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|,
name|GTK_TYPE_POINTER
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|ACTIVATE_ITEM
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"activate_item"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpContainerViewClass
argument_list|,
name|activate_item
argument_list|)
argument_list|,
name|gtk_marshal_NONE__POINTER_POINTER
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|,
name|GTK_TYPE_POINTER
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|CONTEXT_ITEM
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"context_item"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpContainerViewClass
argument_list|,
name|context_item
argument_list|)
argument_list|,
name|gtk_marshal_NONE__POINTER_POINTER
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|,
name|GTK_TYPE_POINTER
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|CLEAR_ITEMS
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"clear_items"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpContainerViewClass
argument_list|,
name|clear_items
argument_list|)
argument_list|,
name|gtk_signal_default_marshaller
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|SET_PREVIEW_SIZE
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"set_preview_size"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpContainerViewClass
argument_list|,
name|set_preview_size
argument_list|)
argument_list|,
name|gtk_signal_default_marshaller
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
name|view_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_container_view_destroy
expr_stmt|;
name|klass
operator|->
name|set_container
operator|=
name|gimp_container_view_real_set_container
expr_stmt|;
name|klass
operator|->
name|insert_item
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|remove_item
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|reorder_item
operator|=
name|NULL
expr_stmt|;
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
name|NULL
expr_stmt|;
name|klass
operator|->
name|clear_items
operator|=
name|gimp_container_view_real_clear_items
expr_stmt|;
name|klass
operator|->
name|set_preview_size
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_view_init (GimpContainerView * view)
name|gimp_container_view_init
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|container
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|hash_table
operator|=
name|g_hash_table_new
argument_list|(
name|g_direct_hash
argument_list|,
name|g_direct_equal
argument_list|)
expr_stmt|;
name|view
operator|->
name|preview_size
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_view_destroy (GtkObject * object)
name|gimp_container_view_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpContainerView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|gimp_container_view_set_container
argument_list|(
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_view_set_context
argument_list|(
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_hash_table_destroy
argument_list|(
name|view
operator|->
name|hash_table
argument_list|)
expr_stmt|;
name|view
operator|->
name|hash_table
operator|=
name|NULL
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
name|void
DECL|function|gimp_container_view_set_container (GimpContainerView * view,GimpContainer * container)
name|gimp_container_view_set_container
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|view
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|container
operator|||
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|container
operator|==
name|view
operator|->
name|container
condition|)
return|return;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|view_signals
index|[
name|SET_CONTAINER
index|]
argument_list|,
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_view_real_set_container (GimpContainerView * view,GimpContainer * container)
name|gimp_container_view_real_set_container
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
if|if
condition|(
name|view
operator|->
name|container
condition|)
block|{
name|gimp_container_view_select_item
argument_list|(
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_view_clear_items
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|gtk_signal_disconnect_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|container
argument_list|)
argument_list|,
name|gimp_container_view_add
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_signal_disconnect_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|container
argument_list|)
argument_list|,
name|gimp_container_view_remove
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_signal_disconnect_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|container
argument_list|)
argument_list|,
name|gimp_container_view_reorder
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|g_hash_table_destroy
argument_list|(
name|view
operator|->
name|hash_table
argument_list|)
expr_stmt|;
name|view
operator|->
name|hash_table
operator|=
name|g_hash_table_new
argument_list|(
name|g_direct_hash
argument_list|,
name|g_direct_equal
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|context
condition|)
block|{
name|gtk_signal_disconnect_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|context
argument_list|)
argument_list|,
name|gimp_container_view_context_changed
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_drag_dest_unset
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_unset
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
block|}
block|}
name|view
operator|->
name|container
operator|=
name|container
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|container
condition|)
block|{
name|gimp_container_foreach
argument_list|(
name|view
operator|->
name|container
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_container_view_add_foreach
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|container
argument_list|)
argument_list|,
literal|"add"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_container_view_add
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|container
argument_list|)
argument_list|,
literal|"remove"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_container_view_remove
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|container
argument_list|)
argument_list|,
literal|"reorder"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_container_view_reorder
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|context
condition|)
block|{
name|GimpObject
modifier|*
name|object
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|signal_name
decl_stmt|;
name|signal_name
operator|=
name|gimp_context_type_to_signal_name
argument_list|(
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|context
argument_list|)
argument_list|,
name|signal_name
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_container_view_context_changed
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|object
operator|=
name|gimp_context_get_by_type
argument_list|(
name|view
operator|->
name|context
argument_list|,
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
name|gimp_container_view_select_item
argument_list|(
name|view
argument_list|,
name|object
condition|?
name|GIMP_VIEWABLE
argument_list|(
name|object
argument_list|)
else|:
name|NULL
argument_list|)
expr_stmt|;
name|gimp_gtk_drag_dest_set_by_type
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|,
name|gimp_container_view_drop_viewable_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_view_set_context (GimpContainerView * view,GimpContext * context)
name|gimp_container_view_set_context
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|view
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|context
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|context
operator|==
name|view
operator|->
name|context
condition|)
return|return;
if|if
condition|(
name|view
operator|->
name|context
operator|&&
name|view
operator|->
name|container
condition|)
block|{
name|gtk_signal_disconnect_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|context
argument_list|)
argument_list|,
name|gimp_container_view_context_changed
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_drag_dest_unset
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_unset
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
block|}
name|view
operator|->
name|context
operator|=
name|context
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|context
operator|&&
name|view
operator|->
name|container
condition|)
block|{
name|GimpObject
modifier|*
name|object
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|signal_name
decl_stmt|;
name|signal_name
operator|=
name|gimp_context_type_to_signal_name
argument_list|(
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
operator|->
name|context
argument_list|)
argument_list|,
name|signal_name
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_container_view_context_changed
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|object
operator|=
name|gimp_context_get_by_type
argument_list|(
name|view
operator|->
name|context
argument_list|,
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
name|gimp_container_view_select_item
argument_list|(
name|view
argument_list|,
name|object
condition|?
name|GIMP_VIEWABLE
argument_list|(
name|object
argument_list|)
else|:
name|NULL
argument_list|)
expr_stmt|;
name|gimp_gtk_drag_dest_set_by_type
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|,
name|gimp_container_view_drop_viewable_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_view_set_preview_size (GimpContainerView * view,gint preview_size)
name|gimp_container_view_set_preview_size
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|gint
name|preview_size
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|view
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|preview_size
operator|>
literal|0
operator|&&
name|preview_size
operator|<=
literal|256
comment|/* FIXME: 64 */
argument_list|)
expr_stmt|;
name|view
operator|->
name|preview_size
operator|=
name|preview_size
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|view_signals
index|[
name|SET_PREVIEW_SIZE
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_view_select_item (GimpContainerView * view,GimpViewable * viewable)
name|gimp_container_view_select_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|gpointer
name|insert_data
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|view
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|viewable
operator|||
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|insert_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|view
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|view_signals
index|[
name|SELECT_ITEM
index|]
argument_list|,
name|viewable
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_view_activate_item (GimpContainerView * view,GimpViewable * viewable)
name|gimp_container_view_activate_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|gpointer
name|insert_data
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|view
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|viewable
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|insert_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|view
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|view_signals
index|[
name|ACTIVATE_ITEM
index|]
argument_list|,
name|viewable
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_view_context_item (GimpContainerView * view,GimpViewable * viewable)
name|gimp_container_view_context_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|gpointer
name|insert_data
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|view
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|viewable
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|insert_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|view
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|view_signals
index|[
name|CONTEXT_ITEM
index|]
argument_list|,
name|viewable
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_view_item_selected (GimpContainerView * view,GimpViewable * viewable)
name|gimp_container_view_item_selected
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|view
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|viewable
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|container
operator|&&
name|view
operator|->
name|context
condition|)
block|{
name|gimp_context_set_by_type
argument_list|(
name|view
operator|->
name|context
argument_list|,
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_container_view_select_item
argument_list|(
name|view
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_view_item_activated (GimpContainerView * view,GimpViewable * viewable)
name|gimp_container_view_item_activated
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|view
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|viewable
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_view_activate_item
argument_list|(
name|view
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_view_item_context (GimpContainerView * view,GimpViewable * viewable)
name|gimp_container_view_item_context
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|view
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|viewable
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_view_context_item
argument_list|(
name|view
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_view_clear_items (GimpContainerView * view)
name|gimp_container_view_clear_items
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|view_signals
index|[
name|CLEAR_ITEMS
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_view_real_clear_items (GimpContainerView * view)
name|gimp_container_view_real_clear_items
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|g_hash_table_destroy
argument_list|(
name|view
operator|->
name|hash_table
argument_list|)
expr_stmt|;
name|view
operator|->
name|hash_table
operator|=
name|g_hash_table_new
argument_list|(
name|g_direct_hash
argument_list|,
name|g_direct_equal
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_view_add_foreach (GimpViewable * viewable,GimpContainerView * view)
name|gimp_container_view_add_foreach
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|gpointer
name|insert_data
init|=
name|NULL
decl_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|view_signals
index|[
name|INSERT_ITEM
index|]
argument_list|,
name|viewable
argument_list|,
operator|-
literal|1
argument_list|,
operator|&
name|insert_data
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|view
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_view_add (GimpContainerView * view,GimpViewable * viewable,GimpContainer * container)
name|gimp_container_view_add
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
name|gpointer
name|insert_data
init|=
name|NULL
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|view_signals
index|[
name|INSERT_ITEM
index|]
argument_list|,
name|viewable
argument_list|,
name|index
argument_list|,
operator|&
name|insert_data
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|view
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_view_remove (GimpContainerView * view,GimpViewable * viewable,GimpContainer * container)
name|gimp_container_view_remove
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
name|gpointer
name|insert_data
decl_stmt|;
name|insert_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|view
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|insert_data
condition|)
block|{
name|g_hash_table_remove
argument_list|(
name|view
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|view_signals
index|[
name|REMOVE_ITEM
index|]
argument_list|,
name|viewable
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_view_reorder (GimpContainerView * view,GimpViewable * viewable,gint new_index,GimpContainer * container)
name|gimp_container_view_reorder
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|new_index
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
name|gpointer
name|insert_data
decl_stmt|;
name|insert_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|view
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|insert_data
condition|)
block|{
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|view_signals
index|[
name|REORDER_ITEM
index|]
argument_list|,
name|viewable
argument_list|,
name|new_index
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_view_context_changed (GimpContext * context,GimpViewable * viewable,GimpContainerView * view)
name|gimp_container_view_context_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|gpointer
name|insert_data
decl_stmt|;
name|insert_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|view
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|view_signals
index|[
name|SELECT_ITEM
index|]
argument_list|,
name|viewable
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_view_drop_viewable_callback (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|gimp_container_view_drop_viewable_callback
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
name|data
parameter_list|)
block|{
name|GimpContainerView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gimp_context_set_by_type
argument_list|(
name|view
operator|->
name|context
argument_list|,
name|view
operator|->
name|container
operator|->
name|children_type
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

