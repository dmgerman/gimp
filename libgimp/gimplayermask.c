begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimplayermask.c  * Copyright (C) Jehan  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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

begin_struct
DECL|struct|_GimpLayerMaskPrivate
struct|struct
name|_GimpLayerMaskPrivate
block|{
DECL|member|unused
name|gpointer
name|unused
decl_stmt|;
block|}
struct|;
end_struct

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpLayerMask,gimp_layer_mask,GIMP_TYPE_CHANNEL)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpLayerMask
argument_list|,
argument|gimp_layer_mask
argument_list|,
argument|GIMP_TYPE_CHANNEL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_layer_mask_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_layer_mask_class_init
parameter_list|(
name|GimpLayerMaskClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_mask_init (GimpLayerMask * layer_mask)
name|gimp_layer_mask_init
parameter_list|(
name|GimpLayerMask
modifier|*
name|layer_mask
parameter_list|)
block|{
name|layer_mask
operator|->
name|priv
operator|=
name|gimp_layer_mask_get_instance_private
argument_list|(
name|layer_mask
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_mask_get_by_id:  * @layer_mask_id: The layer_mask id.  *  * Returns a #GimpLayerMask representing @layer_mask_id. This function  * calls gimp_item_get_by_id() and returns the item if it is  * layer_mask or %NULL otherwise.  *  * Returns: (nullable) (transfer none): a #GimpLayerMask for  *          @layer_mask_id or %NULL if @layer_mask_id does not  *          represent a valid layer_mask. The object belongs to  *          libgimp and you must not modify or unref it.  *  * Since: 3.0  **/
end_comment

begin_function
name|GimpLayerMask
modifier|*
DECL|function|gimp_layer_mask_get_by_id (gint32 layer_mask_id)
name|gimp_layer_mask_get_by_id
parameter_list|(
name|gint32
name|layer_mask_id
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|gimp_item_get_by_id
argument_list|(
name|layer_mask_id
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|item
argument_list|)
condition|)
return|return
operator|(
name|GimpLayerMask
operator|*
operator|)
name|item
return|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

