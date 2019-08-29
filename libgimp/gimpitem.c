begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpitem.c  * Copyright (C) Jehan  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpwire.h"
end_include

begin_comment
comment|/* FIXME kill this include */
end_comment

begin_include
include|#
directive|include
file|"gimpplugin-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure-private.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a3e6cb70103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ID
name|PROP_ID
block|,
DECL|enumerator|N_PROPS
name|N_PROPS
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpItemPrivate
struct|struct
name|_GimpItemPrivate
block|{
DECL|member|id
name|gint
name|id
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_item_set_property
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
name|gimp_item_get_property
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

begin_macro
name|G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpItem
argument_list|,
argument|gimp_item
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_item_parent_class
end_define

begin_decl_stmt
specifier|static
name|GParamSpec
modifier|*
name|props
index|[
name|N_PROPS
index|]
init|=
block|{
name|NULL
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_item_class_init (GimpItemClass * klass)
name|gimp_item_class_init
parameter_list|(
name|GimpItemClass
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
name|object_class
operator|->
name|set_property
operator|=
name|gimp_item_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_item_get_property
expr_stmt|;
name|props
index|[
name|PROP_ID
index|]
operator|=
name|g_param_spec_int
argument_list|(
literal|"id"
argument_list|,
literal|"The item id"
argument_list|,
literal|"The item id for internal use"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
expr_stmt|;
name|g_object_class_install_properties
argument_list|(
name|object_class
argument_list|,
name|N_PROPS
argument_list|,
name|props
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_init (GimpItem * item)
name|gimp_item_init
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
name|item
operator|->
name|priv
operator|=
name|gimp_item_get_instance_private
argument_list|(
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_item_set_property
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
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
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
name|PROP_ID
case|:
name|item
operator|->
name|priv
operator|->
name|id
operator|=
name|g_value_get_int
argument_list|(
name|value
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
name|void
DECL|function|gimp_item_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_item_get_property
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
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
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
name|PROP_ID
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|item
operator|->
name|priv
operator|->
name|id
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

begin_comment
comment|/* Public API. */
end_comment

begin_comment
comment|/**  * gimp_item_get_id:  * @item: The item.  *  * Returns: the item ID.  *  * Since: 3.0  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_item_get_id (GimpItem * item)
name|gimp_item_get_id
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
return|return
name|item
condition|?
name|item
operator|->
name|priv
operator|->
name|id
else|:
operator|-
literal|1
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_get_by_id:  * @item_id: The item id.  *  * Returns a #GimpItem representing @item_id. Since #GimpItem is an  * abstract class, the real object type will actually be the proper  * subclass.  *  * Returns: (nullable) (transfer none): a #GimpItem for @item_id or  *          %NULL if @item_id does not represent a valid item.  *          The object belongs to libgimp and you must not modify  *          or unref it.  *  * Since: 3.0  **/
end_comment

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_get_by_id (gint32 item_id)
name|gimp_item_get_by_id
parameter_list|(
name|gint32
name|item_id
parameter_list|)
block|{
if|if
condition|(
name|item_id
operator|>
literal|0
condition|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp_get_plug_in
argument_list|()
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
init|=
name|_gimp_plug_in_get_procedure
argument_list|(
name|plug_in
argument_list|)
decl_stmt|;
return|return
name|_gimp_procedure_get_item
argument_list|(
name|procedure
argument_list|,
name|item_id
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_is_valid:  * @item: The item to check.  *  * Returns TRUE if the item is valid.  *  * This procedure checks if the given item is valid and refers to an  * existing item.  *  * Returns: Whether the item is valid.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_item_is_valid (GimpItem * item)
name|gimp_item_is_valid
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
return|return
name|gimp_item_id_is_valid
argument_list|(
name|gimp_item_get_id
argument_list|(
name|item
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_is_drawable:  * @item: The item.  *  * Returns whether the item is a drawable.  *  * This procedure returns TRUE if the specified item is a drawable.  *  * Returns: TRUE if the item is a drawable, FALSE otherwise.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_item_is_drawable (GimpItem * item)
name|gimp_item_is_drawable
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
return|return
name|gimp_item_id_is_drawable
argument_list|(
name|gimp_item_get_id
argument_list|(
name|item
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_is_layer:  * @item: The item.  *  * Returns whether the item is a layer.  *  * This procedure returns TRUE if the specified item is a layer.  *  * Returns: TRUE if the item is a layer, FALSE otherwise.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_item_is_layer (GimpItem * item)
name|gimp_item_is_layer
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
return|return
name|gimp_item_id_is_layer
argument_list|(
name|gimp_item_get_id
argument_list|(
name|item
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_is_text_layer:  * @item: The item.  *  * Returns whether the item is a text layer.  *  * This procedure returns TRUE if the specified item is a text  * layer.  *  * Returns: TRUE if the item is a text layer, FALSE otherwise.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_item_is_text_layer (GimpItem * item)
name|gimp_item_is_text_layer
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
return|return
name|gimp_item_id_is_text_layer
argument_list|(
name|gimp_item_get_id
argument_list|(
name|item
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_is_channel:  * @item: The item.  *  * Returns whether the item is a channel.  *  * This procedure returns TRUE if the specified item is a channel.  *  * Returns: TRUE if the item is a channel, FALSE otherwise.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_item_is_channel (GimpItem * item)
name|gimp_item_is_channel
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
return|return
name|gimp_item_id_is_channel
argument_list|(
name|gimp_item_get_id
argument_list|(
name|item
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_is_layer_mask:  * @item: The item.  *  * Returns whether the item is a layer mask.  *  * This procedure returns TRUE if the specified item is a layer  * mask.  *  * Returns: TRUE if the item is a layer mask, FALSE otherwise.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_item_is_layer_mask (GimpItem * item)
name|gimp_item_is_layer_mask
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
return|return
name|gimp_item_id_is_layer_mask
argument_list|(
name|gimp_item_get_id
argument_list|(
name|item
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_is_selection:  * @item: The item.  *  * Returns whether the item is a selection.  *  * This procedure returns TRUE if the specified item is a selection.  *  * Returns: TRUE if the item is a selection, FALSE otherwise.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_item_is_selection (GimpItem * item)
name|gimp_item_is_selection
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
return|return
name|gimp_item_id_is_selection
argument_list|(
name|gimp_item_get_id
argument_list|(
name|item
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_is_vectors:  * @item: The item.  *  * Returns whether the item is a vectors.  *  * This procedure returns TRUE if the specified item is a vectors.  *  * Returns: TRUE if the item is a vectors, FALSE otherwise.  *  * Since: 2.8  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_item_is_vectors (GimpItem * item)
name|gimp_item_is_vectors
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
return|return
name|gimp_item_id_is_vectors
argument_list|(
name|gimp_item_get_id
argument_list|(
name|item
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_get_children:  * @item:         The item.  * @num_children: (out): The number of items in the returned array.  *  * Returns the item's list of children.  *  * This procedure returns the list of items which are children of the  * specified item. The order is topmost to bottommost.  *  * Returns: (array length=num_children) (transfer container):  *          The item's list of children.  *          The returned array must be freed with g_free(). Item  *          elements belong to libgimp and must not be unrefed.  **/
end_comment

begin_function
name|GimpItem
modifier|*
modifier|*
DECL|function|gimp_item_get_children (GimpItem * item,gint * num_children)
name|gimp_item_get_children
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
modifier|*
name|num_children
parameter_list|)
block|{
name|GimpItem
modifier|*
modifier|*
name|children
decl_stmt|;
name|gint
modifier|*
name|ids
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|ids
operator|=
name|_gimp_item_get_children
argument_list|(
name|item
argument_list|,
name|num_children
argument_list|)
expr_stmt|;
name|children
operator|=
name|g_new
argument_list|(
name|GimpItem
operator|*
argument_list|,
operator|*
name|num_children
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|*
name|num_children
condition|;
name|i
operator|++
control|)
name|children
index|[
name|i
index|]
operator|=
name|gimp_item_get_by_id
argument_list|(
name|ids
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ids
argument_list|)
expr_stmt|;
return|return
name|children
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_list_children:  * @item: The item.  *  * Returns the item's list of children.  *  * This procedure returns the list of items which are children of the  * specified item. The order is topmost to bottommost.  *  * Returns: (element-type GimpItem) (transfer container):  *          The item's list of children.  *          The returned ist must be freed with g_list_free(). Item  *          elements belong to libgimp and must not be unrefed.  *  * Since: 3.0  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_item_list_children (GimpItem * item)
name|gimp_item_list_children
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
name|GList
modifier|*
name|children
init|=
name|NULL
decl_stmt|;
name|gint
modifier|*
name|ids
decl_stmt|;
name|gint
name|num_items
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|ids
operator|=
name|_gimp_item_get_children
argument_list|(
name|item
argument_list|,
operator|&
name|num_items
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_items
condition|;
name|i
operator|++
control|)
name|children
operator|=
name|g_list_prepend
argument_list|(
name|children
argument_list|,
name|gimp_item_get_by_id
argument_list|(
name|ids
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ids
argument_list|)
expr_stmt|;
return|return
name|g_list_reverse
argument_list|(
name|children
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_get_children_deprecated: (skip)  * @item_id: The item.  * @num_children: (out): The item's number of children.  *  * Returns the item's list of children.  *  * This procedure returns the list of items which are children of the  * specified item. The order is topmost to bottommost.  *  * Returns: (array length=num_children) (element-type gint32) (transfer full):  *          The item's list of children.  *          The returned value must be freed with g_free().  *  * Since: 2.8  **/
end_comment

begin_function
name|gint
modifier|*
DECL|function|gimp_item_get_children_deprecated (gint32 item_id,gint * num_children)
name|gimp_item_get_children_deprecated
parameter_list|(
name|gint32
name|item_id
parameter_list|,
name|gint
modifier|*
name|num_children
parameter_list|)
block|{
return|return
name|_gimp_item_get_children
argument_list|(
name|gimp_item_get_by_id
argument_list|(
name|item_id
argument_list|)
argument_list|,
name|num_children
argument_list|)
return|;
block|}
end_function

end_unit

