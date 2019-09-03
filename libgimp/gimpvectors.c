begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpvectors.c  * Copyright (C) Jehan  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
DECL|struct|_GimpVectorsPrivate
struct|struct
name|_GimpVectorsPrivate
block|{
DECL|member|unused
name|gpointer
name|unused
decl_stmt|;
block|}
struct|;
end_struct

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpVectors,gimp_vectors,GIMP_TYPE_ITEM)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpVectors
argument_list|,
argument|gimp_vectors
argument_list|,
argument|GIMP_TYPE_ITEM
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_vectors_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_vectors_class_init
parameter_list|(
name|GimpVectorsClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_init (GimpVectors * vectors)
name|gimp_vectors_init
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
block|{
name|vectors
operator|->
name|priv
operator|=
name|gimp_vectors_get_instance_private
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_get_by_id:  * @vectors_id: The vectors id.  *  * Returns a #GimpVectors representing @vectors_id. This function  * calls gimp_item_get_by_id() and returns the item if it is vectors  * or %NULL otherwise.  *  * Returns: (nullable) (transfer none): a #GimpVectors for @vectors_id  *          or %NULL if @vectors_id does not represent a valid  *          vectors. The object belongs to libgimp and you must not  *          modify or unref it.  *  * Since: 3.0  **/
end_comment

begin_function
name|GimpVectors
modifier|*
DECL|function|gimp_vectors_get_by_id (gint32 vectors_id)
name|gimp_vectors_get_by_id
parameter_list|(
name|gint32
name|vectors_id
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|gimp_item_get_by_id
argument_list|(
name|vectors_id
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_IS_VECTORS
argument_list|(
name|item
argument_list|)
condition|)
return|return
operator|(
name|GimpVectors
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

