begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainermenu.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainermenu.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview-utils.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2abde40b0103
block|{
DECL|enumerator|SELECT_ITEM
name|SELECT_ITEM
block|,
DECL|enumerator|ACTIVATE_ITEM
name|ACTIVATE_ITEM
block|,
DECL|enumerator|CONTEXT_ITEM
name|CONTEXT_ITEM
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_class_init
parameter_list|(
name|GimpContainerMenuClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_init
parameter_list|(
name|GimpContainerMenu
modifier|*
name|panel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_destroy
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
name|gimp_container_menu_real_set_container
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
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
name|gimp_container_menu_clear_items
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_real_clear_items
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_add_foreach
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_menu_add
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
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
name|gimp_container_menu_remove
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
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
name|gimp_container_menu_reorder
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
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
name|gimp_container_menu_context_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|menu_signals
specifier|static
name|guint
name|menu_signals
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
name|GType
DECL|function|gimp_container_menu_get_type (void)
name|gimp_container_menu_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|menu_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|menu_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|menu_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpContainerMenuClass
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
name|gimp_container_menu_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpContainerMenu
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_container_menu_init
block|,       }
decl_stmt|;
name|menu_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_MENU
argument_list|,
literal|"GimpContainerMenu"
argument_list|,
operator|&
name|menu_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|menu_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_class_init (GimpContainerMenuClass * klass)
name|gimp_container_menu_class_init
parameter_list|(
name|GimpContainerMenuClass
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
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|menu_signals
index|[
name|SELECT_ITEM
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"select_item"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpContainerMenuClass
argument_list|,
name|select_item
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__OBJECT_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|menu_signals
index|[
name|ACTIVATE_ITEM
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"activate_item"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpContainerMenuClass
argument_list|,
name|activate_item
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__OBJECT_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|menu_signals
index|[
name|CONTEXT_ITEM
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"context_item"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpContainerMenuClass
argument_list|,
name|context_item
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__OBJECT_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_container_menu_destroy
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
name|set_container
operator|=
name|gimp_container_menu_real_set_container
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
name|clear_items
operator|=
name|gimp_container_menu_real_clear_items
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
DECL|function|gimp_container_menu_init (GimpContainerMenu * menu)
name|gimp_container_menu_init
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|)
block|{
name|menu
operator|->
name|container
operator|=
name|NULL
expr_stmt|;
name|menu
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
name|menu
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
name|menu
operator|->
name|preview_size
operator|=
literal|0
expr_stmt|;
name|menu
operator|->
name|preview_border_width
operator|=
literal|1
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_destroy (GtkObject * object)
name|gimp_container_menu_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpContainerMenu
modifier|*
name|menu
decl_stmt|;
name|menu
operator|=
name|GIMP_CONTAINER_MENU
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu
operator|->
name|container
condition|)
name|gimp_container_menu_set_container
argument_list|(
name|menu
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu
operator|->
name|context
condition|)
name|gimp_container_menu_set_context
argument_list|(
name|menu
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu
operator|->
name|hash_table
condition|)
block|{
name|g_hash_table_destroy
argument_list|(
name|menu
operator|->
name|hash_table
argument_list|)
expr_stmt|;
name|menu
operator|->
name|hash_table
operator|=
name|NULL
expr_stmt|;
block|}
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
DECL|function|gimp_container_menu_set_container (GimpContainerMenu * menu,GimpContainer * container)
name|gimp_container_menu_set_container
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_MENU
argument_list|(
name|menu
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|container
operator|==
name|NULL
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
operator|!=
name|menu
operator|->
name|container
condition|)
name|GIMP_CONTAINER_MENU_GET_CLASS
argument_list|(
name|menu
argument_list|)
operator|->
name|set_container
argument_list|(
name|menu
argument_list|,
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_real_set_container (GimpContainerMenu * menu,GimpContainer * container)
name|gimp_container_menu_real_set_container
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
if|if
condition|(
name|menu
operator|->
name|container
condition|)
block|{
name|gimp_container_menu_select_item
argument_list|(
name|menu
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_menu_clear_items
argument_list|(
name|menu
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|menu
operator|->
name|container
argument_list|,
name|gimp_container_menu_add
argument_list|,
name|menu
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|menu
operator|->
name|container
argument_list|,
name|gimp_container_menu_remove
argument_list|,
name|menu
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|menu
operator|->
name|container
argument_list|,
name|gimp_container_menu_reorder
argument_list|,
name|menu
argument_list|)
expr_stmt|;
name|g_hash_table_destroy
argument_list|(
name|menu
operator|->
name|hash_table
argument_list|)
expr_stmt|;
name|menu
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
name|menu
operator|->
name|context
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|menu
operator|->
name|context
argument_list|,
name|gimp_container_menu_context_changed
argument_list|,
name|menu
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|menu
operator|->
name|get_name_func
operator|&&
name|gimp_container_view_is_built_in_name_func
argument_list|(
name|menu
operator|->
name|get_name_func
argument_list|)
condition|)
block|{
name|gimp_container_menu_set_name_func
argument_list|(
name|menu
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
name|menu
operator|->
name|container
operator|=
name|container
expr_stmt|;
if|if
condition|(
name|menu
operator|->
name|container
condition|)
block|{
if|if
condition|(
operator|!
name|menu
operator|->
name|get_name_func
condition|)
block|{
name|GimpItemGetNameFunc
name|get_name_func
decl_stmt|;
name|get_name_func
operator|=
name|gimp_container_view_get_built_in_name_func
argument_list|(
name|menu
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
name|gimp_container_menu_set_name_func
argument_list|(
name|menu
argument_list|,
name|get_name_func
argument_list|)
expr_stmt|;
block|}
name|gimp_container_foreach
argument_list|(
name|menu
operator|->
name|container
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_container_menu_add_foreach
argument_list|,
name|menu
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|menu
operator|->
name|container
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_menu_add
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|menu
operator|->
name|container
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_menu_remove
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|menu
operator|->
name|container
argument_list|,
literal|"reorder"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_menu_reorder
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu
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
name|menu
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|menu
operator|->
name|context
argument_list|,
name|signal_name
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_menu_context_changed
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
name|object
operator|=
name|gimp_context_get_by_type
argument_list|(
name|menu
operator|->
name|context
argument_list|,
name|menu
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
name|gimp_container_menu_select_item
argument_list|(
name|menu
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
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_menu_set_context (GimpContainerMenu * menu,GimpContext * context)
name|gimp_container_menu_set_context
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_MENU
argument_list|(
name|menu
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
name|menu
operator|->
name|context
condition|)
return|return;
if|if
condition|(
name|menu
operator|->
name|context
condition|)
block|{
if|if
condition|(
name|menu
operator|->
name|container
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|menu
operator|->
name|context
argument_list|,
name|gimp_container_menu_context_changed
argument_list|,
name|menu
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|menu
operator|->
name|context
argument_list|)
expr_stmt|;
block|}
name|menu
operator|->
name|context
operator|=
name|context
expr_stmt|;
if|if
condition|(
name|menu
operator|->
name|context
condition|)
block|{
name|g_object_ref
argument_list|(
name|menu
operator|->
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu
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
name|menu
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|menu
operator|->
name|context
argument_list|,
name|signal_name
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_menu_context_changed
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
name|object
operator|=
name|gimp_context_get_by_type
argument_list|(
name|menu
operator|->
name|context
argument_list|,
name|menu
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
name|gimp_container_menu_select_item
argument_list|(
name|menu
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
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_menu_set_preview_size (GimpContainerMenu * menu,gint preview_size)
name|gimp_container_menu_set_preview_size
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|gint
name|preview_size
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_MENU
argument_list|(
name|menu
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
name|GIMP_VIEWABLE_MAX_POPUP_SIZE
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu
operator|->
name|preview_size
operator|!=
name|preview_size
condition|)
block|{
name|menu
operator|->
name|preview_size
operator|=
name|preview_size
expr_stmt|;
name|GIMP_CONTAINER_MENU_GET_CLASS
argument_list|(
name|menu
argument_list|)
operator|->
name|set_preview_size
argument_list|(
name|menu
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_menu_set_name_func (GimpContainerMenu * menu,GimpItemGetNameFunc get_name_func)
name|gimp_container_menu_set_name_func
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpItemGetNameFunc
name|get_name_func
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_MENU
argument_list|(
name|menu
argument_list|)
argument_list|)
expr_stmt|;
name|menu
operator|->
name|get_name_func
operator|=
name|get_name_func
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_menu_select_item (GimpContainerMenu * menu,GimpViewable * viewable)
name|gimp_container_menu_select_item
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_MENU
argument_list|(
name|menu
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
if|if
condition|(
name|menu
operator|->
name|hash_table
condition|)
block|{
name|gpointer
name|insert_data
decl_stmt|;
name|insert_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|menu
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|menu
argument_list|,
name|menu_signals
index|[
name|SELECT_ITEM
index|]
argument_list|,
literal|0
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
name|void
DECL|function|gimp_container_menu_activate_item (GimpContainerMenu * menu,GimpViewable * viewable)
name|gimp_container_menu_activate_item
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_MENU
argument_list|(
name|menu
argument_list|)
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
name|menu
operator|->
name|hash_table
condition|)
block|{
name|gpointer
name|insert_data
decl_stmt|;
name|insert_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|menu
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|menu
argument_list|,
name|menu_signals
index|[
name|ACTIVATE_ITEM
index|]
argument_list|,
literal|0
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
name|void
DECL|function|gimp_container_menu_context_item (GimpContainerMenu * menu,GimpViewable * viewable)
name|gimp_container_menu_context_item
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_MENU
argument_list|(
name|menu
argument_list|)
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
name|menu
operator|->
name|hash_table
condition|)
block|{
name|gpointer
name|insert_data
decl_stmt|;
name|insert_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|menu
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|menu
argument_list|,
name|menu_signals
index|[
name|CONTEXT_ITEM
index|]
argument_list|,
literal|0
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
name|void
DECL|function|gimp_container_menu_item_selected (GimpContainerMenu * menu,GimpViewable * viewable)
name|gimp_container_menu_item_selected
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_MENU
argument_list|(
name|menu
argument_list|)
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
name|menu
operator|->
name|container
operator|&&
name|menu
operator|->
name|context
condition|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
comment|/*  ref and remember the context because menu->context may        *  become NULL by calling gimp_context_set_by_type()        */
name|context
operator|=
name|g_object_ref
argument_list|(
name|menu
operator|->
name|context
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|context
argument_list|,
name|gimp_container_menu_context_changed
argument_list|,
name|menu
argument_list|)
expr_stmt|;
name|gimp_context_set_by_type
argument_list|(
name|context
argument_list|,
name|menu
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
name|g_signal_handlers_unblock_by_func
argument_list|(
name|context
argument_list|,
name|gimp_container_menu_context_changed
argument_list|,
name|menu
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
name|gimp_container_menu_select_item
argument_list|(
name|menu
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_menu_item_activated (GimpContainerMenu * menu,GimpViewable * viewable)
name|gimp_container_menu_item_activated
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_MENU
argument_list|(
name|menu
argument_list|)
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
name|gimp_container_menu_activate_item
argument_list|(
name|menu
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_menu_item_context (GimpContainerMenu * menu,GimpViewable * viewable)
name|gimp_container_menu_item_context
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_MENU
argument_list|(
name|menu
argument_list|)
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
name|gimp_container_menu_context_item
argument_list|(
name|menu
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_clear_items (GimpContainerMenu * menu)
name|gimp_container_menu_clear_items
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|)
block|{
name|GIMP_CONTAINER_MENU_GET_CLASS
argument_list|(
name|menu
argument_list|)
operator|->
name|clear_items
argument_list|(
name|menu
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_real_clear_items (GimpContainerMenu * menu)
name|gimp_container_menu_real_clear_items
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|)
block|{
name|g_hash_table_destroy
argument_list|(
name|menu
operator|->
name|hash_table
argument_list|)
expr_stmt|;
name|menu
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
DECL|function|gimp_container_menu_add_foreach (GimpViewable * viewable,GimpContainerMenu * menu)
name|gimp_container_menu_add_foreach
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|)
block|{
name|gpointer
name|insert_data
decl_stmt|;
name|insert_data
operator|=
name|GIMP_CONTAINER_MENU_GET_CLASS
argument_list|(
name|menu
argument_list|)
operator|->
name|insert_item
argument_list|(
name|menu
argument_list|,
name|viewable
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|menu
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
DECL|function|gimp_container_menu_add (GimpContainerMenu * menu,GimpViewable * viewable,GimpContainer * container)
name|gimp_container_menu_add
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
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
name|insert_data
operator|=
name|GIMP_CONTAINER_MENU_GET_CLASS
argument_list|(
name|menu
argument_list|)
operator|->
name|insert_item
argument_list|(
name|menu
argument_list|,
name|viewable
argument_list|,
name|index
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|menu
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
DECL|function|gimp_container_menu_remove (GimpContainerMenu * menu,GimpViewable * viewable,GimpContainer * container)
name|gimp_container_menu_remove
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
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
name|menu
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
name|GIMP_CONTAINER_MENU_GET_CLASS
argument_list|(
name|menu
argument_list|)
operator|->
name|remove_item
argument_list|(
name|menu
argument_list|,
name|viewable
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
name|g_hash_table_remove
argument_list|(
name|menu
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_menu_reorder (GimpContainerMenu * menu,GimpViewable * viewable,gint new_index,GimpContainer * container)
name|gimp_container_menu_reorder
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
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
name|menu
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
name|GIMP_CONTAINER_MENU_GET_CLASS
argument_list|(
name|menu
argument_list|)
operator|->
name|reorder_item
argument_list|(
name|menu
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
DECL|function|gimp_container_menu_context_changed (GimpContext * context,GimpViewable * viewable,GimpContainerMenu * menu)
name|gimp_container_menu_context_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|)
block|{
name|gpointer
name|insert_data
decl_stmt|;
name|insert_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|menu
operator|->
name|hash_table
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|menu
argument_list|,
name|menu_signals
index|[
name|SELECT_ITEM
index|]
argument_list|,
literal|0
argument_list|,
name|viewable
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

