begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpfilterstack.c  * Copyright (C) 2008-2013 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
name|g_assert
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
if|if
condition|(
name|stack
operator|->
name|graph
condition|)
block|{
name|g_object_unref
argument_list|(
name|stack
operator|->
name|graph
argument_list|)
expr_stmt|;
name|stack
operator|->
name|graph
operator|=
name|NULL
expr_stmt|;
block|}
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
name|gint
name|n_children
decl_stmt|;
name|n_children
operator|=
name|gimp_container_get_n_children
argument_list|(
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_children
operator|==
literal|0
condition|)
name|gimp_filter_set_is_last_node
argument_list|(
name|filter
argument_list|,
name|TRUE
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
name|gint
name|n_children
decl_stmt|;
if|if
condition|(
name|stack
operator|->
name|graph
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
name|gimp_filter_set_is_last_node
argument_list|(
name|filter
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|n_children
operator|=
name|gimp_container_get_n_children
argument_list|(
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_children
operator|>
literal|0
condition|)
block|{
name|GimpFilter
modifier|*
name|last_node
init|=
operator|(
name|GimpFilter
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|container
argument_list|,
name|n_children
operator|-
literal|1
argument_list|)
decl_stmt|;
name|gimp_filter_set_is_last_node
argument_list|(
name|last_node
argument_list|,
name|TRUE
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
name|gint
name|n_children
decl_stmt|;
name|gint
name|old_index
decl_stmt|;
name|n_children
operator|=
name|gimp_container_get_n_children
argument_list|(
name|container
argument_list|)
expr_stmt|;
name|old_index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|stack
operator|->
name|graph
condition|)
name|gimp_filter_stack_remove_node
argument_list|(
name|stack
argument_list|,
name|filter
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_index
operator|==
name|n_children
operator|-
literal|1
condition|)
block|{
name|gimp_filter_set_is_last_node
argument_list|(
name|filter
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|new_index
operator|==
name|n_children
operator|-
literal|1
condition|)
block|{
name|GimpFilter
modifier|*
name|last_node
init|=
operator|(
name|GimpFilter
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|container
argument_list|,
name|n_children
operator|-
literal|1
argument_list|)
decl_stmt|;
name|gimp_filter_set_is_last_node
argument_list|(
name|last_node
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
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
name|new_index
operator|==
name|n_children
operator|-
literal|1
condition|)
block|{
name|gimp_filter_set_is_last_node
argument_list|(
name|filter
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|old_index
operator|==
name|n_children
operator|-
literal|1
condition|)
block|{
name|GimpFilter
modifier|*
name|last_node
init|=
operator|(
name|GimpFilter
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|container
argument_list|,
name|n_children
operator|-
literal|1
argument_list|)
decl_stmt|;
name|gimp_filter_set_is_last_node
argument_list|(
name|last_node
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
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
name|GList
modifier|*
name|reverse_list
init|=
name|NULL
decl_stmt|;
name|GeglNode
modifier|*
name|first
init|=
name|NULL
decl_stmt|;
name|GeglNode
modifier|*
name|previous
init|=
name|NULL
decl_stmt|;
name|GeglNode
modifier|*
name|input
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
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|stack
argument_list|)
operator|->
name|list
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
name|GimpFilter
modifier|*
name|filter
init|=
name|list
operator|->
name|data
decl_stmt|;
name|reverse_list
operator|=
name|g_list_prepend
argument_list|(
name|reverse_list
argument_list|,
name|filter
argument_list|)
expr_stmt|;
block|}
name|stack
operator|->
name|graph
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
for|for
control|(
name|list
operator|=
name|reverse_list
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
init|=
name|gimp_filter_get_node
argument_list|(
name|filter
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|first
condition|)
name|first
operator|=
name|node
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
if|if
condition|(
name|previous
condition|)
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
name|g_list_free
argument_list|(
name|reverse_list
argument_list|)
expr_stmt|;
name|input
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
if|if
condition|(
name|first
operator|&&
name|previous
condition|)
block|{
name|gegl_node_connect_to
argument_list|(
name|input
argument_list|,
literal|"output"
argument_list|,
name|first
argument_list|,
literal|"input"
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
block|}
else|else
block|{
name|gegl_node_connect_to
argument_list|(
name|input
argument_list|,
literal|"output"
argument_list|,
name|output
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
block|}
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
name|GimpFilter
modifier|*
name|filter_below
decl_stmt|;
name|GeglNode
modifier|*
name|node_above
decl_stmt|;
name|GeglNode
modifier|*
name|node_below
decl_stmt|;
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|node
operator|=
name|gimp_filter_get_node
argument_list|(
name|filter
argument_list|)
expr_stmt|;
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|==
literal|0
condition|)
block|{
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
block|}
else|else
block|{
name|GimpFilter
modifier|*
name|filter_above
init|=
operator|(
name|GimpFilter
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
argument_list|)
argument_list|,
name|index
operator|-
literal|1
argument_list|)
decl_stmt|;
name|node_above
operator|=
name|gimp_filter_get_node
argument_list|(
name|filter_above
argument_list|)
expr_stmt|;
block|}
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
name|filter_below
operator|=
operator|(
name|GimpFilter
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
argument_list|)
argument_list|,
name|index
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|filter_below
condition|)
block|{
name|node_below
operator|=
name|gimp_filter_get_node
argument_list|(
name|filter_below
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|node_below
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
block|}
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
name|GimpFilter
modifier|*
name|filter_below
decl_stmt|;
name|GeglNode
modifier|*
name|node_above
decl_stmt|;
name|GeglNode
modifier|*
name|node_below
decl_stmt|;
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|node
operator|=
name|gimp_filter_get_node
argument_list|(
name|filter
argument_list|)
expr_stmt|;
name|gegl_node_disconnect
argument_list|(
name|node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|==
literal|0
condition|)
block|{
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
block|}
else|else
block|{
name|GimpFilter
modifier|*
name|filter_above
init|=
operator|(
name|GimpFilter
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
argument_list|)
argument_list|,
name|index
operator|-
literal|1
argument_list|)
decl_stmt|;
name|node_above
operator|=
name|gimp_filter_get_node
argument_list|(
name|filter_above
argument_list|)
expr_stmt|;
block|}
name|filter_below
operator|=
operator|(
name|GimpFilter
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
argument_list|)
argument_list|,
name|index
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|filter_below
condition|)
block|{
name|node_below
operator|=
name|gimp_filter_get_node
argument_list|(
name|filter_below
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|node_below
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
block|}
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

end_unit

