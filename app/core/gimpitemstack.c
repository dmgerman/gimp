begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpitemstack.c  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpitemstack.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_item_stack_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_stack_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_stack_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpItemStack,gimp_item_stack,GIMP_TYPE_FILTER_STACK)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpItemStack
argument_list|,
argument|gimp_item_stack
argument_list|,
argument|GIMP_TYPE_FILTER_STACK
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_item_stack_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_item_stack_class_init
parameter_list|(
name|GimpItemStackClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpContainerClass
modifier|*
name|container_class
init|=
name|GIMP_CONTAINER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_item_stack_constructed
expr_stmt|;
name|container_class
operator|->
name|add
operator|=
name|gimp_item_stack_add
expr_stmt|;
name|container_class
operator|->
name|remove
operator|=
name|gimp_item_stack_remove
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_stack_init (GimpItemStack * stack)
name|gimp_item_stack_init
parameter_list|(
name|GimpItemStack
modifier|*
name|stack
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_stack_constructed (GObject * object)
name|gimp_item_stack_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|container
init|=
name|GIMP_CONTAINER
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|gimp_assert
argument_list|(
name|g_type_is_a
argument_list|(
name|gimp_container_get_children_type
argument_list|(
name|container
argument_list|)
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_stack_add (GimpContainer * container,GimpObject * object)
name|gimp_item_stack_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|g_object_ref_sink
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|GIMP_CONTAINER_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|add
argument_list|(
name|container
argument_list|,
name|object
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_stack_remove (GimpContainer * container,GimpObject * object)
name|gimp_item_stack_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|GIMP_CONTAINER_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|remove
argument_list|(
name|container
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpContainer
modifier|*
DECL|function|gimp_item_stack_new (GType item_type)
name|gimp_item_stack_new
parameter_list|(
name|GType
name|item_type
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|item_type
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_ITEM_STACK
argument_list|,
literal|"name"
argument_list|,
name|g_type_name
argument_list|(
name|item_type
argument_list|)
argument_list|,
literal|"children-type"
argument_list|,
name|item_type
argument_list|,
literal|"policy"
argument_list|,
name|GIMP_CONTAINER_POLICY_STRONG
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_item_stack_get_n_items (GimpItemStack * stack)
name|gimp_item_stack_get_n_items
parameter_list|(
name|GimpItemStack
modifier|*
name|stack
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|n_items
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|stack
argument_list|)
operator|->
name|queue
operator|->
name|head
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
name|GimpItem
modifier|*
name|item
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GimpContainer
modifier|*
name|children
decl_stmt|;
name|n_items
operator|++
expr_stmt|;
name|children
operator|=
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|children
condition|)
name|n_items
operator|+=
name|gimp_item_stack_get_n_items
argument_list|(
name|GIMP_ITEM_STACK
argument_list|(
name|children
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|n_items
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_item_stack_is_flat (GimpItemStack * stack)
name|gimp_item_stack_is_flat
parameter_list|(
name|GimpItemStack
modifier|*
name|stack
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|stack
argument_list|)
operator|->
name|queue
operator|->
name|head
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
name|GimpViewable
modifier|*
name|viewable
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_viewable_get_children
argument_list|(
name|viewable
argument_list|)
condition|)
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_item_stack_get_item_iter (GimpItemStack * stack)
name|gimp_item_stack_get_item_iter
parameter_list|(
name|GimpItemStack
modifier|*
name|stack
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_LIST
argument_list|(
name|stack
argument_list|)
operator|->
name|queue
operator|->
name|head
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_item_stack_get_item_list (GimpItemStack * stack)
name|gimp_item_stack_get_item_list
parameter_list|(
name|GimpItemStack
modifier|*
name|stack
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GList
modifier|*
name|result
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|stack
argument_list|)
operator|->
name|queue
operator|->
name|head
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
name|GimpViewable
modifier|*
name|viewable
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GimpContainer
modifier|*
name|children
decl_stmt|;
name|result
operator|=
name|g_list_prepend
argument_list|(
name|result
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
name|children
operator|=
name|gimp_viewable_get_children
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|children
condition|)
block|{
name|GList
modifier|*
name|child_list
decl_stmt|;
name|child_list
operator|=
name|gimp_item_stack_get_item_list
argument_list|(
name|GIMP_ITEM_STACK
argument_list|(
name|children
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|child_list
condition|)
block|{
name|result
operator|=
name|g_list_prepend
argument_list|(
name|result
argument_list|,
name|child_list
operator|->
name|data
argument_list|)
expr_stmt|;
name|child_list
operator|=
name|g_list_remove
argument_list|(
name|child_list
argument_list|,
name|child_list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
block|}
block|}
return|return
name|g_list_reverse
argument_list|(
name|result
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_stack_get_item_by_tattoo (GimpItemStack * stack,GimpTattoo tattoo)
name|gimp_item_stack_get_item_by_tattoo
parameter_list|(
name|GimpItemStack
modifier|*
name|stack
parameter_list|,
name|GimpTattoo
name|tattoo
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|stack
argument_list|)
operator|->
name|queue
operator|->
name|head
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
name|GimpItem
modifier|*
name|item
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GimpContainer
modifier|*
name|children
decl_stmt|;
if|if
condition|(
name|gimp_item_get_tattoo
argument_list|(
name|item
argument_list|)
operator|==
name|tattoo
condition|)
return|return
name|item
return|;
name|children
operator|=
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|children
condition|)
block|{
name|item
operator|=
name|gimp_item_stack_get_item_by_tattoo
argument_list|(
name|GIMP_ITEM_STACK
argument_list|(
name|children
argument_list|)
argument_list|,
name|tattoo
argument_list|)
expr_stmt|;
if|if
condition|(
name|item
condition|)
return|return
name|item
return|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_stack_get_item_by_path (GimpItemStack * stack,GList * path)
name|gimp_item_stack_get_item_by_path
parameter_list|(
name|GimpItemStack
modifier|*
name|stack
parameter_list|,
name|GList
modifier|*
name|path
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpItem
modifier|*
name|item
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|path
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|container
operator|=
name|GIMP_CONTAINER
argument_list|(
name|stack
argument_list|)
expr_stmt|;
while|while
condition|(
name|path
condition|)
block|{
name|guint32
name|i
init|=
name|GPOINTER_TO_UINT
argument_list|(
name|path
operator|->
name|data
argument_list|)
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_container_get_child_by_index
argument_list|(
name|container
argument_list|,
name|i
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|path
operator|->
name|next
condition|)
block|{
name|container
operator|=
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM_STACK
argument_list|(
name|container
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
name|path
operator|=
name|path
operator|->
name|next
expr_stmt|;
block|}
return|return
name|item
return|;
block|}
end_function

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_stack_get_parent_by_path (GimpItemStack * stack,GList * path,gint * index)
name|gimp_item_stack_get_parent_by_path
parameter_list|(
name|GimpItemStack
modifier|*
name|stack
parameter_list|,
name|GList
modifier|*
name|path
parameter_list|,
name|gint
modifier|*
name|index
parameter_list|)
block|{
name|GimpItem
modifier|*
name|parent
init|=
name|NULL
decl_stmt|;
name|guint32
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|path
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|i
operator|=
name|GPOINTER_TO_UINT
argument_list|(
name|path
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
condition|)
operator|*
name|index
operator|=
name|i
expr_stmt|;
while|while
condition|(
name|path
operator|->
name|next
condition|)
block|{
name|GimpObject
modifier|*
name|child
decl_stmt|;
name|GimpContainer
modifier|*
name|children
decl_stmt|;
name|child
operator|=
name|gimp_container_get_child_by_index
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
argument_list|)
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|child
argument_list|)
argument_list|,
name|parent
argument_list|)
expr_stmt|;
name|children
operator|=
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|child
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM_STACK
argument_list|(
name|children
argument_list|)
argument_list|,
name|parent
argument_list|)
expr_stmt|;
name|parent
operator|=
name|GIMP_ITEM
argument_list|(
name|child
argument_list|)
expr_stmt|;
name|stack
operator|=
name|GIMP_ITEM_STACK
argument_list|(
name|children
argument_list|)
expr_stmt|;
name|path
operator|=
name|path
operator|->
name|next
expr_stmt|;
name|i
operator|=
name|GPOINTER_TO_UINT
argument_list|(
name|path
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
condition|)
operator|*
name|index
operator|=
name|i
expr_stmt|;
block|}
return|return
name|parent
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_stack_viewable_invalidate_previews (GimpViewable * viewable)
name|gimp_item_stack_viewable_invalidate_previews
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|children
init|=
name|gimp_viewable_get_children
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
if|if
condition|(
name|children
condition|)
name|gimp_item_stack_invalidate_previews
argument_list|(
name|GIMP_ITEM_STACK
argument_list|(
name|children
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_viewable_invalidate_preview
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_item_stack_invalidate_previews (GimpItemStack * stack)
name|gimp_item_stack_invalidate_previews
parameter_list|(
name|GimpItemStack
modifier|*
name|stack
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_foreach
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
argument_list|)
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_item_stack_viewable_invalidate_previews
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_stack_viewable_profile_changed (GimpViewable * viewable)
name|gimp_item_stack_viewable_profile_changed
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|children
init|=
name|gimp_viewable_get_children
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
if|if
condition|(
name|children
condition|)
name|gimp_item_stack_profile_changed
argument_list|(
name|GIMP_ITEM_STACK
argument_list|(
name|children
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_COLOR_MANAGED
argument_list|(
name|viewable
argument_list|)
condition|)
name|gimp_color_managed_profile_changed
argument_list|(
name|GIMP_COLOR_MANAGED
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_item_stack_profile_changed (GimpItemStack * stack)
name|gimp_item_stack_profile_changed
parameter_list|(
name|GimpItemStack
modifier|*
name|stack
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_foreach
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
argument_list|)
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_item_stack_viewable_profile_changed
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

