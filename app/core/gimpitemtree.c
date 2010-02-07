begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpitemtree.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo-push.h"
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

begin_include
include|#
directive|include
file|"gimpitemtree.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a1b03a50103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_IMAGE
name|PROP_IMAGE
block|,
DECL|enumerator|PROP_CONTAINER_TYPE
name|PROP_CONTAINER_TYPE
block|,
DECL|enumerator|PROP_ITEM_TYPE
name|PROP_ITEM_TYPE
block|,
DECL|enumerator|PROP_ACTIVE_ITEM
name|PROP_ACTIVE_ITEM
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpItemTreePrivate
typedef|typedef
name|struct
name|_GimpItemTreePrivate
name|GimpItemTreePrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpItemTreePrivate
struct|struct
name|_GimpItemTreePrivate
block|{
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|container_type
name|GType
name|container_type
decl_stmt|;
DECL|member|item_type
name|GType
name|item_type
decl_stmt|;
DECL|member|active_item
name|GimpItem
modifier|*
name|active_item
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_ITEM_TREE_GET_PRIVATE (object)
define|#
directive|define
name|GIMP_ITEM_TREE_GET_PRIVATE
parameter_list|(
name|object
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (object, \                                      GIMP_TYPE_ITEM_TREE, \                                      GimpItemTreePrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_item_tree_constructor
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
name|gimp_item_tree_finalize
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
name|gimp_item_tree_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_tree_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_item_tree_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpItemTree,gimp_item_tree,GIMP_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpItemTree
argument_list|,
argument|gimp_item_tree
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_item_tree_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_item_tree_class_init
parameter_list|(
name|GimpItemTreeClass
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
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_item_tree_constructor
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_item_tree_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_item_tree_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_item_tree_get_property
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_item_tree_get_memsize
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_IMAGE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"image"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTAINER_TYPE
argument_list|,
name|g_param_spec_gtype
argument_list|(
literal|"container-type"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_ITEM_STACK
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ITEM_TYPE
argument_list|,
name|g_param_spec_gtype
argument_list|(
literal|"item-type"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ACTIVE_ITEM
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"active-item"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpItemTreePrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_tree_init (GimpItemTree * tree)
name|gimp_item_tree_init
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_item_tree_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_item_tree_constructor
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
name|GimpItemTree
modifier|*
name|tree
decl_stmt|;
name|GimpItemTreePrivate
modifier|*
name|private
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
name|tree
operator|=
name|GIMP_ITEM_TREE
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_ITEM_TREE_GET_PRIVATE
argument_list|(
name|tree
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|private
operator|->
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|g_type_is_a
argument_list|(
name|private
operator|->
name|container_type
argument_list|,
name|GIMP_TYPE_ITEM_STACK
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|g_type_is_a
argument_list|(
name|private
operator|->
name|item_type
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|private
operator|->
name|item_type
operator|!=
name|GIMP_TYPE_ITEM
argument_list|)
expr_stmt|;
name|tree
operator|->
name|container
operator|=
name|g_object_new
argument_list|(
name|private
operator|->
name|container_type
argument_list|,
literal|"name"
argument_list|,
name|g_type_name
argument_list|(
name|private
operator|->
name|item_type
argument_list|)
argument_list|,
literal|"children-type"
argument_list|,
name|private
operator|->
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
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_tree_finalize (GObject * object)
name|gimp_item_tree_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpItemTree
modifier|*
name|tree
init|=
name|GIMP_ITEM_TREE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|tree
operator|->
name|container
condition|)
block|{
name|g_object_unref
argument_list|(
name|tree
operator|->
name|container
argument_list|)
expr_stmt|;
name|tree
operator|->
name|container
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
DECL|function|gimp_item_tree_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_item_tree_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpItemTreePrivate
modifier|*
name|private
init|=
name|GIMP_ITEM_TREE_GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_IMAGE
case|:
name|private
operator|->
name|image
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
comment|/* don't ref */
break|break;
case|case
name|PROP_CONTAINER_TYPE
case|:
name|private
operator|->
name|container_type
operator|=
name|g_value_get_gtype
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ITEM_TYPE
case|:
name|private
operator|->
name|item_type
operator|=
name|g_value_get_gtype
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ACTIVE_ITEM
case|:
name|private
operator|->
name|active_item
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
comment|/* don't ref */
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_tree_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_item_tree_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpItemTreePrivate
modifier|*
name|private
init|=
name|GIMP_ITEM_TREE_GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_IMAGE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|image
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTAINER_TYPE
case|:
name|g_value_set_gtype
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|container_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ITEM_TYPE
case|:
name|g_value_set_gtype
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|item_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ACTIVE_ITEM
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|active_item
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|gint64
DECL|function|gimp_item_tree_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_item_tree_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpItemTree
modifier|*
name|tree
init|=
name|GIMP_ITEM_TREE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|tree
operator|->
name|container
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpItemTree
modifier|*
DECL|function|gimp_item_tree_new (GimpImage * image,GType container_type,GType item_type)
name|gimp_item_tree_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GType
name|container_type
parameter_list|,
name|GType
name|item_type
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|container_type
argument_list|,
name|GIMP_TYPE_ITEM_STACK
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|GIMP_TYPE_ITEM_TREE
argument_list|,
literal|"image"
argument_list|,
name|image
argument_list|,
literal|"container-type"
argument_list|,
name|container_type
argument_list|,
literal|"item-type"
argument_list|,
name|item_type
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_tree_get_active_item (GimpItemTree * tree)
name|gimp_item_tree_get_active_item
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM_TREE
argument_list|(
name|tree
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_ITEM_TREE_GET_PRIVATE
argument_list|(
name|tree
argument_list|)
operator|->
name|active_item
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_item_tree_set_active_item (GimpItemTree * tree,GimpItem * item)
name|gimp_item_tree_set_active_item
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
name|GimpItemTreePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM_TREE
argument_list|(
name|tree
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|item
operator|==
name|NULL
operator|||
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_ITEM_TREE_GET_PRIVATE
argument_list|(
name|tree
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|item
operator|==
name|NULL
operator|||
operator|(
name|gimp_item_is_attached
argument_list|(
name|item
argument_list|)
operator|&&
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
operator|==
name|private
operator|->
name|image
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|item
operator|!=
name|private
operator|->
name|active_item
condition|)
block|{
name|private
operator|->
name|active_item
operator|=
name|item
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|tree
argument_list|)
argument_list|,
literal|"active-item"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_tree_get_insert_pos (GimpItemTree * tree,GimpItem * parent,gint * position,GimpItem * active_item)
name|gimp_item_tree_get_insert_pos
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|,
name|GimpItem
modifier|*
name|parent
parameter_list|,
name|gint
modifier|*
name|position
parameter_list|,
name|GimpItem
modifier|*
name|active_item
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM_TREE
argument_list|(
name|tree
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  if we want to insert in the active item's parent container  */
if|if
condition|(
name|parent
operator|==
name|GIMP_IMAGE_ACTIVE_PARENT
condition|)
block|{
if|if
condition|(
name|active_item
condition|)
block|{
comment|/*  if the active item is a branch, add to the top of that            *  branch; add to the active item's parent container            *  otherwise            */
if|if
condition|(
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|active_item
argument_list|)
argument_list|)
condition|)
block|{
name|parent
operator|=
name|active_item
expr_stmt|;
operator|*
name|position
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|parent
operator|=
name|gimp_item_get_parent
argument_list|(
name|active_item
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/*  use the toplevel container if there is no active item  */
name|parent
operator|=
name|NULL
expr_stmt|;
block|}
block|}
if|if
condition|(
name|parent
condition|)
name|container
operator|=
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|container
operator|=
name|tree
operator|->
name|container
expr_stmt|;
comment|/*  if we want to add on top of the active item  */
if|if
condition|(
operator|*
name|position
operator|==
operator|-
literal|1
condition|)
block|{
if|if
condition|(
name|active_item
condition|)
operator|*
name|position
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|active_item
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  if the active item is not in the specified parent container,        *  fall back to index 0        */
if|if
condition|(
operator|*
name|position
operator|==
operator|-
literal|1
condition|)
operator|*
name|position
operator|=
literal|0
expr_stmt|;
block|}
comment|/*  don't add at a non-existing index  */
operator|*
name|position
operator|=
name|CLAMP
argument_list|(
operator|*
name|position
argument_list|,
literal|0
argument_list|,
name|gimp_container_get_n_children
argument_list|(
name|container
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|parent
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_item_tree_add_item (GimpItemTree * tree,GimpItem * item,GimpItem * parent,gint position)
name|gimp_item_tree_add_item
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpItem
modifier|*
name|parent
parameter_list|,
name|gint
name|position
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM_TREE
argument_list|(
name|tree
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|parent
condition|)
name|container
operator|=
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|container
operator|=
name|tree
operator|->
name|container
expr_stmt|;
if|if
condition|(
name|parent
condition|)
name|gimp_viewable_set_parent
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|item
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_insert
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|,
name|position
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_tree_remove_item (GimpItemTree * tree,GimpItem * item,GimpItem * current_active,GimpItem * new_active)
name|gimp_item_tree_remove_item
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpItem
modifier|*
name|current_active
parameter_list|,
name|GimpItem
modifier|*
name|new_active
parameter_list|)
block|{
name|GimpItem
modifier|*
name|parent
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM_TREE
argument_list|(
name|tree
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|parent
operator|=
name|gimp_item_get_parent
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|container
operator|=
name|gimp_item_get_container
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|index
operator|=
name|gimp_item_get_index
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|gimp_container_remove
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|parent
condition|)
name|gimp_viewable_set_parent
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|item
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_item_removed
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|new_active
condition|)
block|{
name|gint
name|n_children
init|=
name|gimp_container_get_n_children
argument_list|(
name|container
argument_list|)
decl_stmt|;
if|if
condition|(
name|n_children
operator|>
literal|0
condition|)
block|{
name|index
operator|=
name|CLAMP
argument_list|(
name|index
argument_list|,
literal|0
argument_list|,
name|n_children
operator|-
literal|1
argument_list|)
expr_stmt|;
name|new_active
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_container_get_child_by_index
argument_list|(
name|container
argument_list|,
name|index
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|parent
condition|)
block|{
name|new_active
operator|=
name|parent
expr_stmt|;
block|}
block|}
name|g_object_unref
argument_list|(
name|item
argument_list|)
expr_stmt|;
return|return
name|new_active
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_item_tree_reorder_item (GimpItemTree * tree,GimpItem * item,GimpItem * new_parent,gint new_index,gboolean push_undo,const gchar * undo_desc)
name|gimp_item_tree_reorder_item
parameter_list|(
name|GimpItemTree
modifier|*
name|tree
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpItem
modifier|*
name|new_parent
parameter_list|,
name|gint
name|new_index
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
block|{
name|GimpItemTreePrivate
modifier|*
name|private
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpContainer
modifier|*
name|new_container
decl_stmt|;
name|gint
name|n_items
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM_TREE
argument_list|(
name|tree
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_ITEM_TREE_GET_PRIVATE
argument_list|(
name|tree
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_CHECK_INSTANCE_TYPE
argument_list|(
name|item
argument_list|,
name|private
operator|->
name|item_type
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|item
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
operator|==
name|private
operator|->
name|image
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|new_parent
operator|==
name|NULL
operator|||
name|G_TYPE_CHECK_INSTANCE_TYPE
argument_list|(
name|new_parent
argument_list|,
name|private
operator|->
name|item_type
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|new_parent
operator|==
name|NULL
operator|||
name|gimp_item_is_attached
argument_list|(
name|new_parent
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|new_parent
operator|==
name|NULL
operator|||
name|gimp_item_get_image
argument_list|(
name|new_parent
argument_list|)
operator|==
name|private
operator|->
name|image
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|new_parent
operator|==
name|NULL
operator|||
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|new_parent
argument_list|)
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|container
operator|=
name|gimp_item_get_container
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_parent
condition|)
name|new_container
operator|=
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|new_parent
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|new_container
operator|=
name|tree
operator|->
name|container
expr_stmt|;
name|n_items
operator|=
name|gimp_container_get_n_children
argument_list|(
name|new_container
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_container
operator|==
name|container
condition|)
name|n_items
operator|--
expr_stmt|;
name|new_index
operator|=
name|CLAMP
argument_list|(
name|new_index
argument_list|,
literal|0
argument_list|,
name|n_items
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_container
operator|!=
name|container
operator|||
name|new_index
operator|!=
name|gimp_item_get_index
argument_list|(
name|item
argument_list|)
condition|)
block|{
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_item_reorder
argument_list|(
name|private
operator|->
name|image
argument_list|,
name|undo_desc
argument_list|,
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_container
operator|!=
name|container
condition|)
block|{
name|g_object_ref
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|gimp_container_remove
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_viewable_set_parent
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|item
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|new_parent
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_insert
argument_list|(
name|new_container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|,
name|new_index
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|item
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_container_reorder
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|,
name|new_index
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

