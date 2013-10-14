begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpdrawablestack.c  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawablestack.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29b166a90103
block|{
DECL|enumerator|UPDATE
name|UPDATE
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_drawable_stack_constructed
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
name|gimp_drawable_stack_add
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
name|gimp_drawable_stack_remove
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
name|gimp_drawable_stack_reorder
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
name|gimp_drawable_stack_update
parameter_list|(
name|GimpDrawableStack
modifier|*
name|stack
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_stack_drawable_update
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpDrawableStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_stack_drawable_visible
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpDrawableStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDrawableStack
argument_list|,
argument|gimp_drawable_stack
argument_list|,
argument|GIMP_TYPE_ITEM_STACK
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_drawable_stack_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|stack_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_stack_class_init (GimpDrawableStackClass * klass)
name|gimp_drawable_stack_class_init
parameter_list|(
name|GimpDrawableStackClass
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
name|stack_signals
index|[
name|UPDATE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"update"
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
name|GimpDrawableStackClass
argument_list|,
name|update
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__INT_INT_INT_INT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|4
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_drawable_stack_constructed
expr_stmt|;
name|container_class
operator|->
name|add
operator|=
name|gimp_drawable_stack_add
expr_stmt|;
name|container_class
operator|->
name|remove
operator|=
name|gimp_drawable_stack_remove
expr_stmt|;
name|container_class
operator|->
name|reorder
operator|=
name|gimp_drawable_stack_reorder
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_stack_init (GimpDrawableStack * stack)
name|gimp_drawable_stack_init
parameter_list|(
name|GimpDrawableStack
modifier|*
name|stack
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_stack_constructed (GObject * object)
name|gimp_drawable_stack_constructed
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
name|GIMP_TYPE_DRAWABLE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_add_handler
argument_list|(
name|container
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_stack_drawable_update
argument_list|)
argument_list|,
name|container
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
name|gimp_drawable_stack_drawable_visible
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
DECL|function|gimp_drawable_stack_add (GimpContainer * container,GimpObject * object)
name|gimp_drawable_stack_add
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
name|GimpDrawableStack
modifier|*
name|stack
init|=
name|GIMP_DRAWABLE_STACK
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
if|if
condition|(
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|object
argument_list|)
argument_list|)
condition|)
name|gimp_drawable_stack_drawable_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|object
argument_list|)
argument_list|,
name|stack
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_stack_remove (GimpContainer * container,GimpObject * object)
name|gimp_drawable_stack_remove
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
name|GimpDrawableStack
modifier|*
name|stack
init|=
name|GIMP_DRAWABLE_STACK
argument_list|(
name|container
argument_list|)
decl_stmt|;
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
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|object
argument_list|)
argument_list|)
condition|)
name|gimp_drawable_stack_drawable_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|object
argument_list|)
argument_list|,
name|stack
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_stack_reorder (GimpContainer * container,GimpObject * object,gint new_index)
name|gimp_drawable_stack_reorder
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
name|GimpDrawableStack
modifier|*
name|stack
init|=
name|GIMP_DRAWABLE_STACK
argument_list|(
name|container
argument_list|)
decl_stmt|;
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
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|object
argument_list|)
argument_list|)
condition|)
name|gimp_drawable_stack_drawable_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|object
argument_list|)
argument_list|,
name|stack
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
DECL|function|gimp_drawable_stack_new (GType drawable_type)
name|gimp_drawable_stack_new
parameter_list|(
name|GType
name|drawable_type
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|drawable_type
argument_list|,
name|GIMP_TYPE_DRAWABLE
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_DRAWABLE_STACK
argument_list|,
literal|"name"
argument_list|,
name|g_type_name
argument_list|(
name|drawable_type
argument_list|)
argument_list|,
literal|"children-type"
argument_list|,
name|drawable_type
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
DECL|function|gimp_drawable_stack_update (GimpDrawableStack * stack,gint x,gint y,gint width,gint height)
name|gimp_drawable_stack_update
parameter_list|(
name|GimpDrawableStack
modifier|*
name|stack
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|g_signal_emit
argument_list|(
name|stack
argument_list|,
name|stack_signals
index|[
name|UPDATE
index|]
argument_list|,
literal|0
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_stack_drawable_update (GimpItem * item,gint x,gint y,gint width,gint height,GimpDrawableStack * stack)
name|gimp_drawable_stack_drawable_update
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpDrawableStack
modifier|*
name|stack
parameter_list|)
block|{
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
name|stack
argument_list|,
name|x
operator|+
name|offset_x
argument_list|,
name|y
operator|+
name|offset_y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_stack_drawable_visible (GimpItem * item,GimpDrawableStack * stack)
name|gimp_drawable_stack_drawable_visible
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpDrawableStack
modifier|*
name|stack
parameter_list|)
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
name|stack
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
end_function

end_unit

