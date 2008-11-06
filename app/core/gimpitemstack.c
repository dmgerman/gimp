begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpitemstack.c  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
name|GObject
modifier|*
name|gimp_item_stack_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
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
DECL|function|G_DEFINE_TYPE (GimpItemStack,gimp_item_stack,GIMP_TYPE_LIST)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpItemStack
argument_list|,
argument|gimp_item_stack
argument_list|,
argument|GIMP_TYPE_LIST
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
name|constructor
operator|=
name|gimp_item_stack_constructor
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
name|GObject
modifier|*
DECL|function|gimp_item_stack_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_item_stack_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|container
operator|=
name|GIMP_CONTAINER
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|g_type_is_a
argument_list|(
name|container
operator|->
name|children_type
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|object
return|;
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
literal|"unique-names"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
return|;
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
name|gimp_viewable_invalidate_preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

