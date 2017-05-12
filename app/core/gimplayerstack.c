begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimplayerstack.c  * Copyright (C) 2017 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimplayerstack.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_layer_stack_constructed
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
name|gimp_layer_stack_add
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
name|gimp_layer_stack_remove
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
name|gimp_layer_stack_reorder
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
name|gimp_layer_stack_layer_visible
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_stack_layer_excludes_backdrop
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_stack_update_backdrop
parameter_list|(
name|GimpLayerStack
modifier|*
name|stack
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|ignore_visible
parameter_list|,
name|gboolean
name|ignore_excludes_backdrop
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_stack_update_range
parameter_list|(
name|GimpLayerStack
modifier|*
name|stack
parameter_list|,
name|gint
name|first
parameter_list|,
name|gint
name|last
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpLayerStack,gimp_layer_stack,GIMP_TYPE_DRAWABLE_STACK)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpLayerStack
argument_list|,
argument|gimp_layer_stack
argument_list|,
argument|GIMP_TYPE_DRAWABLE_STACK
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_layer_stack_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_layer_stack_class_init
parameter_list|(
name|GimpLayerStackClass
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
name|gimp_layer_stack_constructed
expr_stmt|;
name|container_class
operator|->
name|add
operator|=
name|gimp_layer_stack_add
expr_stmt|;
name|container_class
operator|->
name|remove
operator|=
name|gimp_layer_stack_remove
expr_stmt|;
name|container_class
operator|->
name|reorder
operator|=
name|gimp_layer_stack_reorder
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_stack_init (GimpLayerStack * stack)
name|gimp_layer_stack_init
parameter_list|(
name|GimpLayerStack
modifier|*
name|stack
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_stack_constructed (GObject * object)
name|gimp_layer_stack_constructed
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
name|GIMP_TYPE_LAYER
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_add_handler
argument_list|(
name|container
argument_list|,
literal|"visibility-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_layer_stack_layer_visible
argument_list|)
argument_list|,
name|container
argument_list|)
expr_stmt|;
name|gimp_container_add_handler
argument_list|(
name|container
argument_list|,
literal|"excludes-backdrop-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_layer_stack_layer_excludes_backdrop
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
DECL|function|gimp_layer_stack_add (GimpContainer * container,GimpObject * object)
name|gimp_layer_stack_add
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
name|GimpLayerStack
modifier|*
name|stack
init|=
name|GIMP_LAYER_STACK
argument_list|(
name|container
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
name|gimp_layer_stack_update_backdrop
argument_list|(
name|stack
argument_list|,
name|GIMP_LAYER
argument_list|(
name|object
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_stack_remove (GimpContainer * container,GimpObject * object)
name|gimp_layer_stack_remove
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
name|GimpLayerStack
modifier|*
name|stack
init|=
name|GIMP_LAYER_STACK
argument_list|(
name|container
argument_list|)
decl_stmt|;
name|gboolean
name|update_backdrop
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|update_backdrop
operator|=
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|object
argument_list|)
argument_list|)
operator|&&
name|gimp_layer_get_excludes_backdrop
argument_list|(
name|GIMP_LAYER
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|update_backdrop
condition|)
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|object
argument_list|)
expr_stmt|;
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
name|update_backdrop
condition|)
name|gimp_layer_stack_update_range
argument_list|(
name|stack
argument_list|,
name|index
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_stack_reorder (GimpContainer * container,GimpObject * object,gint new_index)
name|gimp_layer_stack_reorder
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
name|GimpLayerStack
modifier|*
name|stack
init|=
name|GIMP_LAYER_STACK
argument_list|(
name|container
argument_list|)
decl_stmt|;
name|gboolean
name|update_backdrop
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|update_backdrop
operator|=
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|object
argument_list|)
argument_list|)
operator|&&
name|gimp_layer_get_excludes_backdrop
argument_list|(
name|GIMP_LAYER
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|update_backdrop
condition|)
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|object
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
name|update_backdrop
condition|)
name|gimp_layer_stack_update_range
argument_list|(
name|stack
argument_list|,
name|index
argument_list|,
name|new_index
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
DECL|function|gimp_layer_stack_new (GType layer_type)
name|gimp_layer_stack_new
parameter_list|(
name|GType
name|layer_type
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|layer_type
argument_list|,
name|GIMP_TYPE_LAYER
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_LAYER_STACK
argument_list|,
literal|"name"
argument_list|,
name|g_type_name
argument_list|(
name|layer_type
argument_list|)
argument_list|,
literal|"children-type"
argument_list|,
name|layer_type
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

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_layer_stack_layer_visible (GimpLayer * layer,GimpLayerStack * stack)
name|gimp_layer_stack_layer_visible
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerStack
modifier|*
name|stack
parameter_list|)
block|{
name|gimp_layer_stack_update_backdrop
argument_list|(
name|stack
argument_list|,
name|layer
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_stack_layer_excludes_backdrop (GimpLayer * layer,GimpLayerStack * stack)
name|gimp_layer_stack_layer_excludes_backdrop
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerStack
modifier|*
name|stack
parameter_list|)
block|{
name|gimp_layer_stack_update_backdrop
argument_list|(
name|stack
argument_list|,
name|layer
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_stack_update_backdrop (GimpLayerStack * stack,GimpLayer * layer,gboolean ignore_visible,gboolean ignore_excludes_backdrop)
name|gimp_layer_stack_update_backdrop
parameter_list|(
name|GimpLayerStack
modifier|*
name|stack
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|ignore_visible
parameter_list|,
name|gboolean
name|ignore_excludes_backdrop
parameter_list|)
block|{
if|if
condition|(
operator|(
name|ignore_visible
operator|||
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
operator|&&
operator|(
name|ignore_excludes_backdrop
operator|||
name|gimp_layer_get_excludes_backdrop
argument_list|(
name|layer
argument_list|)
operator|)
condition|)
block|{
name|gint
name|index
decl_stmt|;
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
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_layer_stack_update_range
argument_list|(
name|stack
argument_list|,
name|index
operator|+
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_stack_update_range (GimpLayerStack * stack,gint first,gint last)
name|gimp_layer_stack_update_range
parameter_list|(
name|GimpLayerStack
modifier|*
name|stack
parameter_list|,
name|gint
name|first
parameter_list|,
name|gint
name|last
parameter_list|)
block|{
name|GList
modifier|*
name|iter
decl_stmt|;
name|g_assert
argument_list|(
name|first
operator|>=
literal|0
operator|&&
name|last
operator|>=
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/* if the range is reversed, flip first and last; note that last == -1 is    * used to update all layers from first onward.    */
if|if
condition|(
name|last
operator|>=
literal|0
operator|&&
name|last
operator|<
name|first
condition|)
block|{
name|gint
name|temp
init|=
name|first
decl_stmt|;
name|first
operator|=
name|last
operator|+
literal|1
expr_stmt|;
name|last
operator|=
name|temp
operator|+
literal|1
expr_stmt|;
block|}
name|iter
operator|=
name|gimp_item_stack_get_item_iter
argument_list|(
name|GIMP_ITEM_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|iter
operator|=
name|g_list_nth
argument_list|(
name|iter
argument_list|,
name|first
argument_list|)
init|;
name|iter
operator|&&
name|first
operator|!=
name|last
condition|;
name|iter
operator|=
name|g_list_next
argument_list|(
name|iter
argument_list|)
operator|,
name|first
operator|++
control|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|iter
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_item_get_visible
argument_list|(
name|item
argument_list|)
condition|)
block|{
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|gimp_item_get_offset
argument_list|(
name|item
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
name|gimp_drawable_stack_update
argument_list|(
name|GIMP_DRAWABLE_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

