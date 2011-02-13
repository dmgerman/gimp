begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpvectors.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimp.h"
end_include

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_undef
undef|#
directive|undef
name|__GIMP_VECTORS_H__
end_undef

begin_include
include|#
directive|include
file|"gimpvectors.h"
end_include

begin_comment
comment|/**  * gimp_vectors_is_valid:  * @vectors_ID: The vectors object to check.  *  * Deprecated: Use gimp_item_is_valid() instead.  *  * Returns: Whether the vectors ID is valid.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_vectors_is_valid (gint32 vectors_ID)
name|gimp_vectors_is_valid
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
block|{
return|return
name|gimp_item_is_valid
argument_list|(
name|vectors_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_get_image:  * @vectors_ID: The vectors object.  *  * Deprecated: Use gimp_item_get_image() instead.  *  * Returns: The vectors image.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gint32
DECL|function|gimp_vectors_get_image (gint32 vectors_ID)
name|gimp_vectors_get_image
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
block|{
return|return
name|gimp_item_get_image
argument_list|(
name|vectors_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_get_name:  * @vectors_ID: The vectors object.  *  * Deprecated: Use gimp_item_get_name() instead.  *  * Returns: The name of the vectors object.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_vectors_get_name (gint32 vectors_ID)
name|gimp_vectors_get_name
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
block|{
return|return
name|gimp_item_get_name
argument_list|(
name|vectors_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_set_name:  * @vectors_ID: The vectors object.  * @name: the new name of the path.  *  * Deprecated: Use gimp_item_set_name() instead.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_vectors_set_name (gint32 vectors_ID,const gchar * name)
name|gimp_vectors_set_name
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|gimp_item_set_name
argument_list|(
name|vectors_ID
argument_list|,
name|name
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_get_visible:  * @vectors_ID: The vectors object.  *  * Deprecated: Use gimp_item_get_visible() instead.  *  * Returns: TRUE if the path is visible, FALSE otherwise.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_vectors_get_visible (gint32 vectors_ID)
name|gimp_vectors_get_visible
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
block|{
return|return
name|gimp_vectors_get_visible
argument_list|(
name|vectors_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_set_visible:  * @vectors_ID: The vectors object.  * @visible: Whether the path is visible.  *  * Deprecated: Use gimp_item_set_visible() instead.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_vectors_set_visible (gint32 vectors_ID,gboolean visible)
name|gimp_vectors_set_visible
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gboolean
name|visible
parameter_list|)
block|{
return|return
name|gimp_item_set_visible
argument_list|(
name|vectors_ID
argument_list|,
name|visible
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_get_linked:  * @vectors_ID: The vectors object.  *  * Deprecated: Use gimp_item_get_linked() instead.  *  * Returns: TRUE if the path is linked, FALSE otherwise.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_vectors_get_linked (gint32 vectors_ID)
name|gimp_vectors_get_linked
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
block|{
return|return
name|gimp_item_get_linked
argument_list|(
name|vectors_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_set_linked:  * @vectors_ID: The vectors object.  * @linked: Whether the path is linked.  *  * Deprecated: Use gimp_item_set_linked() instead.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_vectors_set_linked (gint32 vectors_ID,gboolean linked)
name|gimp_vectors_set_linked
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gboolean
name|linked
parameter_list|)
block|{
return|return
name|gimp_item_set_linked
argument_list|(
name|vectors_ID
argument_list|,
name|linked
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_get_tattoo:  * @vectors_ID: The vectors object.  *  * Deprecated: Use gimp_item_get_tattoo() instead.  *  * Returns: The vectors tattoo.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gint
DECL|function|gimp_vectors_get_tattoo (gint32 vectors_ID)
name|gimp_vectors_get_tattoo
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
block|{
return|return
name|gimp_item_get_tattoo
argument_list|(
name|vectors_ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_set_tattoo:  * @vectors_ID: The vectors object.  * @tattoo: the new tattoo.  *  * Deprecated: Use gimp_item_set_tattoo() instead.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_vectors_set_tattoo (gint32 vectors_ID,gint tattoo)
name|gimp_vectors_set_tattoo
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|tattoo
parameter_list|)
block|{
return|return
name|gimp_vectors_set_tattoo
argument_list|(
name|vectors_ID
argument_list|,
name|tattoo
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_parasite_find:  * @vectors_ID: The vectors object.  * @name: The name of the parasite to find.  *  * Deprecated: Use gimp_item_find_parasite() instead.  *  * Returns: The found parasite.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|GimpParasite
modifier|*
DECL|function|gimp_vectors_parasite_find (gint32 vectors_ID,const gchar * name)
name|gimp_vectors_parasite_find
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|gimp_item_find_parasite
argument_list|(
name|vectors_ID
argument_list|,
name|name
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_parasite_attach:  * @vectors_ID: The vectors object.  * @parasite: The parasite to attach to a vectors object.  *  * Deprecated: Use gimp_item_attach_parasite() instead.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_vectors_parasite_attach (gint32 vectors_ID,const GimpParasite * parasite)
name|gimp_vectors_parasite_attach
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
return|return
name|gimp_item_attach_parasite
argument_list|(
name|vectors_ID
argument_list|,
name|parasite
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_parasite_detach:  * @vectors_ID: The vectors object.  * @name: The name of the parasite to detach from a vectors object.  *  * Deprecated: Use gimp_item_detach_parasite() instead.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_vectors_parasite_detach (gint32 vectors_ID,const gchar * name)
name|gimp_vectors_parasite_detach
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|gimp_item_detach_parasite
argument_list|(
name|vectors_ID
argument_list|,
name|name
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_parasite_list:  * @vectors_ID: The vectors object.  * @num_parasites: The number of attached parasites.  * @parasites: The names of currently attached parasites.  *  * Deprecated: Use gimp_item_list_parasites() instead.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_vectors_parasite_list (gint32 vectors_ID,gint * num_parasites,gchar *** parasites)
name|gimp_vectors_parasite_list
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
modifier|*
name|num_parasites
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|parasites
parameter_list|)
block|{
return|return
name|gimp_item_list_parasites
argument_list|(
name|vectors_ID
argument_list|,
name|num_parasites
argument_list|,
name|parasites
argument_list|)
return|;
block|}
end_function

end_unit

