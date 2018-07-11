begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpfilterstack.c  * Copyright (C) 2008-2013 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpfilter.h"
end_include

begin_include
include|#
directive|include
file|"gimpfilterstack.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_filter_stack_constructed
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
name|gimp_filter_stack_finalize
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
name|gimp_filter_stack_add
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
name|gimp_filter_stack_remove
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
name|gimp_filter_stack_reorder
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint
name|new_index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_filter_stack_add_node
parameter_list|(
name|GimpFilterStack
modifier|*
name|stack
parameter_list|,
name|GimpFilter
modifier|*
name|filter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_filter_stack_remove_node
parameter_list|(
name|GimpFilterStack
modifier|*
name|stack
parameter_list|,
name|GimpFilter
modifier|*
name|filter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_filter_stack_update_last_node
parameter_list|(
name|GimpFilterStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_filter_stack_filter_active
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|,
name|GimpFilterStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpFilterStack
argument_list|,
name|gimp_filter_stack
argument_list|,
name|GIMP_TYPE_LIST
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_filter_stack_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_filter_stack_class_init (GimpFilterStackClass * klass)
name|gimp_filter_stack_class_init
parameter_list|(
name|GimpFilterStackClass
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
name|gimp_filter_stack_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_filter_stack_finalize
expr_stmt|;
name|container_class
operator|->
name|add
operator|=
name|gimp_filter_stack_add
expr_stmt|;
name|container_class
operator|->
name|remove
operator|=
name|gimp_filter_stack_remove
expr_stmt|;
name|container_class
operator|->
name|reorder
operator|=
name|gimp_filter_stack_reorder
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filter_stack_init (GimpFilterStack * stack)
name|gimp_filter_stack_init
parameter_list|(
name|GimpFilterStack
modifier|*
name|stack
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filter_stack_constructed (GObject * object)
name|gimp_filter_stack_constructed
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
name|GIMP_TYPE_FILTER
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_add_handler
argument_list|(
name|container
argument_list|,
literal|"active-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_filter_stack_filter_active
argument_list|)
argument_list|,
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filter_stack_finalize (GObject * object)
name|gimp_filter_stack_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFilterStack
modifier|*
name|stack
init|=
name|GIMP_FILTER_STACK
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|stack
operator|->
name|graph
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filter_stack_add (GimpContainer * container,GimpObject * object)
name|gimp_filter_stack_add
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
name|GimpFilterStack
modifier|*
name|stack
init|=
name|GIMP_FILTER_STACK
argument_list|(
name|container
argument_list|)
decl_stmt|;
name|GimpFilter
modifier|*
name|filter
init|=
name|GIMP_FILTER
argument_list|(
name|object
argument_list|)
decl_stmt|;
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
if|if
condition|(
name|gimp_filter_get_active
argument_list|(
name|filter
argument_list|)
condition|)
block|{
if|if
condition|(
name|stack
operator|->
name|graph
condition|)
block|{
name|gegl_node_add_child
argument_list|(
name|stack
operator|->
name|graph
argument_list|,
name|gimp_filter_get_node
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_filter_stack_add_node
argument_list|(
name|stack
argument_list|,
name|filter
argument_list|)
expr_stmt|;
block|}
name|gimp_filter_stack_update_last_node
argument_list|(
name|stack
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filter_stack_remove (GimpContainer * container,GimpObject * object)
name|gimp_filter_stack_remove
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
name|GimpFilterStack
modifier|*
name|stack
init|=
name|GIMP_FILTER_STACK
argument_list|(
name|container
argument_list|)
decl_stmt|;
name|GimpFilter
modifier|*
name|filter
init|=
name|GIMP_FILTER
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|stack
operator|->
name|graph
operator|&&
name|gimp_filter_get_active
argument_list|(
name|filter
argument_list|)
condition|)
block|{
name|gimp_filter_stack_remove_node
argument_list|(
name|stack
argument_list|,
name|filter
argument_list|)
expr_stmt|;
name|gegl_node_remove_child
argument_list|(
name|stack
operator|->
name|graph
argument_list|,
name|gimp_filter_get_node
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
block|}
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
if|if
condition|(
name|gimp_filter_get_active
argument_list|(
name|filter
argument_list|)
condition|)
block|{
name|gimp_filter_set_is_last_node
argument_list|(
name|filter
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_filter_stack_update_last_node
argument_list|(
name|stack
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filter_stack_reorder (GimpContainer * container,GimpObject * object,gint new_index)
name|gimp_filter_stack_reorder
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint
name|new_index
parameter_list|)
block|{
name|GimpFilterStack
modifier|*
name|stack
init|=
name|GIMP_FILTER_STACK
argument_list|(
name|container
argument_list|)
decl_stmt|;
name|GimpFilter
modifier|*
name|filter
init|=
name|GIMP_FILTER
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|stack
operator|->
name|graph
operator|&&
name|gimp_filter_get_active
argument_list|(
name|filter
argument_list|)
condition|)
name|gimp_filter_stack_remove_node
argument_list|(
name|stack
argument_list|,
name|filter
argument_list|)
expr_stmt|;
name|GIMP_CONTAINER_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|reorder
argument_list|(
name|container
argument_list|,
name|object
argument_list|,
name|new_index
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_filter_get_active
argument_list|(
name|filter
argument_list|)
condition|)
block|{
name|gimp_filter_stack_update_last_node
argument_list|(
name|stack
argument_list|)
expr_stmt|;
if|if
condition|(
name|stack
operator|->
name|graph
condition|)
name|gimp_filter_stack_add_node
argument_list|(
name|stack
argument_list|,
name|filter
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpContainer
modifier|*
DECL|function|gimp_filter_stack_new (GType filter_type)
name|gimp_filter_stack_new
parameter_list|(
name|GType
name|filter_type
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|filter_type
argument_list|,
name|GIMP_TYPE_FILTER
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_FILTER_STACK
argument_list|,
literal|"name"
argument_list|,
name|g_type_name
argument_list|(
name|filter_type
argument_list|)
argument_list|,
literal|"children-type"
argument_list|,
name|filter_type
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
name|GeglNode
modifier|*
DECL|function|gimp_filter_stack_get_graph (GimpFilterStack * stack)
name|gimp_filter_stack_get_graph
parameter_list|(
name|GimpFilterStack
modifier|*
name|stack
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GeglNode
modifier|*
name|previous
decl_stmt|;
name|GeglNode
modifier|*
name|output
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILTER_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|stack
operator|->
name|graph
condition|)
return|return
name|stack
operator|->
name|graph
return|;
name|stack
operator|->
name|graph
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|previous
operator|=
name|gegl_node_get_input_proxy
argument_list|(
name|stack
operator|->
name|graph
argument_list|,
literal|"input"
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
name|tail
init|;
name|list
condition|;
name|list
operator|=
name|g_list_previous
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpFilter
modifier|*
name|filter
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GeglNode
modifier|*
name|node
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_filter_get_active
argument_list|(
name|filter
argument_list|)
condition|)
continue|continue;
name|node
operator|=
name|gimp_filter_get_node
argument_list|(
name|filter
argument_list|)
expr_stmt|;
name|gegl_node_add_child
argument_list|(
name|stack
operator|->
name|graph
argument_list|,
name|node
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|previous
argument_list|,
literal|"output"
argument_list|,
name|node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|previous
operator|=
name|node
expr_stmt|;
block|}
name|output
operator|=
name|gegl_node_get_output_proxy
argument_list|(
name|stack
operator|->
name|graph
argument_list|,
literal|"output"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|previous
argument_list|,
literal|"output"
argument_list|,
name|output
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
return|return
name|stack
operator|->
name|graph
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_filter_stack_add_node (GimpFilterStack * stack,GimpFilter * filter)
name|gimp_filter_stack_add_node
parameter_list|(
name|GimpFilterStack
modifier|*
name|stack
parameter_list|,
name|GimpFilter
modifier|*
name|filter
parameter_list|)
block|{
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|GeglNode
modifier|*
name|node_above
init|=
name|NULL
decl_stmt|;
name|GeglNode
modifier|*
name|node_below
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|iter
decl_stmt|;
name|node
operator|=
name|gimp_filter_get_node
argument_list|(
name|filter
argument_list|)
expr_stmt|;
name|iter
operator|=
name|g_list_find
argument_list|(
name|GIMP_LIST
argument_list|(
name|stack
argument_list|)
operator|->
name|queue
operator|->
name|head
argument_list|,
name|filter
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|iter
operator|=
name|g_list_previous
argument_list|(
name|iter
argument_list|)
operator|)
condition|)
block|{
name|GimpFilter
modifier|*
name|filter_above
init|=
name|iter
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_filter_get_active
argument_list|(
name|filter_above
argument_list|)
condition|)
block|{
name|node_above
operator|=
name|gimp_filter_get_node
argument_list|(
name|filter_above
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
operator|!
name|node_above
condition|)
name|node_above
operator|=
name|gegl_node_get_output_proxy
argument_list|(
name|stack
operator|->
name|graph
argument_list|,
literal|"output"
argument_list|)
expr_stmt|;
name|node_below
operator|=
name|gegl_node_get_producer
argument_list|(
name|node_above
argument_list|,
literal|"input"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|node_below
argument_list|,
literal|"output"
argument_list|,
name|node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|node
argument_list|,
literal|"output"
argument_list|,
name|node_above
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filter_stack_remove_node (GimpFilterStack * stack,GimpFilter * filter)
name|gimp_filter_stack_remove_node
parameter_list|(
name|GimpFilterStack
modifier|*
name|stack
parameter_list|,
name|GimpFilter
modifier|*
name|filter
parameter_list|)
block|{
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|GeglNode
modifier|*
name|node_above
init|=
name|NULL
decl_stmt|;
name|GeglNode
modifier|*
name|node_below
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|iter
decl_stmt|;
name|node
operator|=
name|gimp_filter_get_node
argument_list|(
name|filter
argument_list|)
expr_stmt|;
name|iter
operator|=
name|g_list_find
argument_list|(
name|GIMP_LIST
argument_list|(
name|stack
argument_list|)
operator|->
name|queue
operator|->
name|head
argument_list|,
name|filter
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|iter
operator|=
name|g_list_previous
argument_list|(
name|iter
argument_list|)
operator|)
condition|)
block|{
name|GimpFilter
modifier|*
name|filter_above
init|=
name|iter
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_filter_get_active
argument_list|(
name|filter_above
argument_list|)
condition|)
block|{
name|node_above
operator|=
name|gimp_filter_get_node
argument_list|(
name|filter_above
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
operator|!
name|node_above
condition|)
name|node_above
operator|=
name|gegl_node_get_output_proxy
argument_list|(
name|stack
operator|->
name|graph
argument_list|,
literal|"output"
argument_list|)
expr_stmt|;
name|node_below
operator|=
name|gegl_node_get_producer
argument_list|(
name|node
argument_list|,
literal|"input"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_disconnect
argument_list|(
name|node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|node_below
argument_list|,
literal|"output"
argument_list|,
name|node_above
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filter_stack_update_last_node (GimpFilterStack * stack)
name|gimp_filter_stack_update_last_node
parameter_list|(
name|GimpFilterStack
modifier|*
name|stack
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gboolean
name|found_last
init|=
name|FALSE
decl_stmt|;
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
name|tail
init|;
name|list
condition|;
name|list
operator|=
name|g_list_previous
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpFilter
modifier|*
name|filter
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|!
name|found_last
operator|&&
name|gimp_filter_get_active
argument_list|(
name|filter
argument_list|)
condition|)
block|{
name|gimp_filter_set_is_last_node
argument_list|(
name|filter
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|found_last
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|gimp_filter_set_is_last_node
argument_list|(
name|filter
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filter_stack_filter_active (GimpFilter * filter,GimpFilterStack * stack)
name|gimp_filter_stack_filter_active
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|,
name|GimpFilterStack
modifier|*
name|stack
parameter_list|)
block|{
if|if
condition|(
name|stack
operator|->
name|graph
condition|)
block|{
if|if
condition|(
name|gimp_filter_get_active
argument_list|(
name|filter
argument_list|)
condition|)
block|{
name|gegl_node_add_child
argument_list|(
name|stack
operator|->
name|graph
argument_list|,
name|gimp_filter_get_node
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_filter_stack_add_node
argument_list|(
name|stack
argument_list|,
name|filter
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_filter_stack_remove_node
argument_list|(
name|stack
argument_list|,
name|filter
argument_list|)
expr_stmt|;
name|gegl_node_remove_child
argument_list|(
name|stack
operator|->
name|graph
argument_list|,
name|gimp_filter_get_node
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_filter_stack_update_last_node
argument_list|(
name|stack
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_filter_get_active
argument_list|(
name|filter
argument_list|)
condition|)
name|gimp_filter_set_is_last_node
argument_list|(
name|filter
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

