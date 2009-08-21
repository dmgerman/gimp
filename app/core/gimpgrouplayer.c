begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpGroupLayer  * Copyright (C) 2009  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpgrouplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawablestack.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_group_layer_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_group_layer_get_memsize
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

begin_function_decl
specifier|static
name|GimpContainer
modifier|*
name|gimp_group_layer_get_children
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpItem
modifier|*
name|gimp_group_layer_duplicate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GType
name|new_type
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpGroupLayer,gimp_group_layer,GIMP_TYPE_LAYER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpGroupLayer
argument_list|,
argument|gimp_group_layer
argument_list|,
argument|GIMP_TYPE_LAYER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_group_layer_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_group_layer_class_init
parameter_list|(
name|GimpGroupLayerClass
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
name|GimpViewableClass
modifier|*
name|viewable_class
init|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpItemClass
modifier|*
name|item_class
init|=
name|GIMP_ITEM_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_group_layer_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_group_layer_get_memsize
expr_stmt|;
name|viewable_class
operator|->
name|default_stock_id
operator|=
literal|"gtk-directory"
expr_stmt|;
name|viewable_class
operator|->
name|get_children
operator|=
name|gimp_group_layer_get_children
expr_stmt|;
name|item_class
operator|->
name|duplicate
operator|=
name|gimp_group_layer_duplicate
expr_stmt|;
name|item_class
operator|->
name|default_name
operator|=
name|_
argument_list|(
literal|"Group Layer"
argument_list|)
expr_stmt|;
name|item_class
operator|->
name|rename_desc
operator|=
name|_
argument_list|(
literal|"Rename Group Layer"
argument_list|)
expr_stmt|;
name|item_class
operator|->
name|translate_desc
operator|=
name|_
argument_list|(
literal|"Move Group Layer"
argument_list|)
expr_stmt|;
name|item_class
operator|->
name|scale_desc
operator|=
name|_
argument_list|(
literal|"Scale Group Layer"
argument_list|)
expr_stmt|;
name|item_class
operator|->
name|resize_desc
operator|=
name|_
argument_list|(
literal|"Resize Group Layer"
argument_list|)
expr_stmt|;
name|item_class
operator|->
name|flip_desc
operator|=
name|_
argument_list|(
literal|"Flip Group Layer"
argument_list|)
expr_stmt|;
name|item_class
operator|->
name|rotate_desc
operator|=
name|_
argument_list|(
literal|"Rotate Group Layer"
argument_list|)
expr_stmt|;
name|item_class
operator|->
name|transform_desc
operator|=
name|_
argument_list|(
literal|"Transform Group Layer"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_group_layer_init (GimpGroupLayer * layer)
name|gimp_group_layer_init
parameter_list|(
name|GimpGroupLayer
modifier|*
name|layer
parameter_list|)
block|{
name|layer
operator|->
name|children
operator|=
name|gimp_drawable_stack_new
argument_list|(
name|GIMP_TYPE_LAYER
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_group_layer_finalize (GObject * object)
name|gimp_group_layer_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpGroupLayer
modifier|*
name|layer
init|=
name|GIMP_GROUP_LAYER
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|layer
operator|->
name|children
condition|)
block|{
name|g_object_unref
argument_list|(
name|layer
operator|->
name|children
argument_list|)
expr_stmt|;
name|layer
operator|->
name|children
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
name|gint64
DECL|function|gimp_group_layer_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_group_layer_get_memsize
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
name|GimpGroupLayer
modifier|*
name|layer
init|=
name|GIMP_GROUP_LAYER
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
name|layer
operator|->
name|children
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

begin_function
specifier|static
name|GimpContainer
modifier|*
DECL|function|gimp_group_layer_get_children (GimpViewable * viewable)
name|gimp_group_layer_get_children
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|GimpGroupLayer
modifier|*
name|layer
init|=
name|GIMP_GROUP_LAYER
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
return|return
name|layer
operator|->
name|children
return|;
block|}
end_function

begin_function
specifier|static
name|GimpItem
modifier|*
DECL|function|gimp_group_layer_duplicate (GimpItem * item,GType new_type)
name|gimp_group_layer_duplicate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GType
name|new_type
parameter_list|)
block|{
name|GimpItem
modifier|*
name|new_item
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|new_type
argument_list|,
name|GIMP_TYPE_GROUP_LAYER
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|new_item
operator|=
name|GIMP_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|duplicate
argument_list|(
name|item
argument_list|,
name|new_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_GROUP_LAYER
argument_list|(
name|new_item
argument_list|)
condition|)
block|{
name|GimpGroupLayer
modifier|*
name|layer
init|=
name|GIMP_GROUP_LAYER
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GimpGroupLayer
modifier|*
name|new_layer
init|=
name|GIMP_GROUP_LAYER
argument_list|(
name|new_item
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|position
decl_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|layer
operator|->
name|children
argument_list|)
operator|->
name|list
operator|,
name|position
operator|=
literal|0
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
name|child
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GimpItem
modifier|*
name|new_child
decl_stmt|;
name|new_child
operator|=
name|gimp_item_duplicate
argument_list|(
name|child
argument_list|,
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|child
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_viewable_set_parent
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|new_child
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|new_layer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_insert
argument_list|(
name|new_layer
operator|->
name|children
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|new_child
argument_list|)
argument_list|,
name|position
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|new_item
return|;
block|}
end_function

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_group_layer_new (GimpImage * image)
name|gimp_group_layer_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpGroupLayer
modifier|*
name|layer
decl_stmt|;
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
name|layer
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_GROUP_LAYER
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_configure
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
name|image
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
name|gimp_image_base_type_with_alpha
argument_list|(
name|image
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Group Layer"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|GIMP_LAYER
argument_list|(
name|layer
argument_list|)
return|;
block|}
end_function

end_unit

