begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpitem.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimpitem.h"
end_include

begin_comment
comment|/**  * gimp_item_get_metadata:  * @item_ID: The item.  *  * Returns the item's metadata.  *  * Returns metadata from the item.  *  * Returns: The metadata, or %NULL if there is none.  *  * Since: GIMP 2.10  **/
end_comment

begin_function
name|GimpMetadata
modifier|*
DECL|function|gimp_item_get_metadata (gint32 item_ID)
name|gimp_item_get_metadata
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
block|{
name|GimpMetadata
modifier|*
name|metadata
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|metadata_string
decl_stmt|;
name|metadata_string
operator|=
name|_gimp_item_get_metadata
argument_list|(
name|item_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata_string
condition|)
block|{
name|metadata
operator|=
name|gimp_metadata_deserialize
argument_list|(
name|metadata_string
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|metadata_string
argument_list|)
expr_stmt|;
block|}
return|return
name|metadata
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_set_metadata:  * @item_ID: The item.  * @metadata: The GimpMetadata object.  *  * Set the item's metadata.  *  * Sets metadata on the item, or deletes it if  * @metadata is %NULL.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_item_set_metadata (gint32 item_ID,GimpMetadata * metadata)
name|gimp_item_set_metadata
parameter_list|(
name|gint32
name|item_ID
parameter_list|,
name|GimpMetadata
modifier|*
name|metadata
parameter_list|)
block|{
name|gchar
modifier|*
name|metadata_string
init|=
name|NULL
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
if|if
condition|(
name|metadata
condition|)
name|metadata_string
operator|=
name|gimp_metadata_serialize
argument_list|(
name|metadata
argument_list|)
expr_stmt|;
name|success
operator|=
name|_gimp_item_set_metadata
argument_list|(
name|item_ID
argument_list|,
name|metadata_string
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata_string
condition|)
name|g_free
argument_list|(
name|metadata_string
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

