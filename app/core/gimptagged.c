begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptagged.c  * Copyright (C) 2008  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimptag.h"
end_include

begin_include
include|#
directive|include
file|"gimptagged.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c7561cf0103
block|{
DECL|enumerator|TAG_ADDED
name|TAG_ADDED
block|,
DECL|enumerator|TAG_REMOVED
name|TAG_REMOVED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_tagged_base_init
parameter_list|(
name|gpointer
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_tagged_signals
specifier|static
name|guint
name|gimp_tagged_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_tagged_interface_get_type (void)
name|gimp_tagged_interface_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tagged_iface_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tagged_iface_type
condition|)
block|{
specifier|const
name|GTypeInfo
name|tagged_iface_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpTaggedInterface
argument_list|)
block|,
name|gimp_tagged_base_init
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|tagged_iface_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_INTERFACE
argument_list|,
literal|"GimpTaggedInterface"
argument_list|,
operator|&
name|tagged_iface_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tagged_iface_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tagged_base_init (gpointer klass)
name|gimp_tagged_base_init
parameter_list|(
name|gpointer
name|klass
parameter_list|)
block|{
specifier|static
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
operator|!
name|initialized
condition|)
block|{
name|gimp_tagged_signals
index|[
name|TAG_ADDED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"tag-added"
argument_list|,
name|GIMP_TYPE_TAGGED
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpTaggedInterface
argument_list|,
name|tag_added
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__OBJECT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_TAG
argument_list|)
expr_stmt|;
name|gimp_tagged_signals
index|[
name|TAG_REMOVED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"tag-removed"
argument_list|,
name|GIMP_TYPE_TAGGED
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpTaggedInterface
argument_list|,
name|tag_removed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__OBJECT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_TAG
argument_list|)
expr_stmt|;
name|initialized
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_tagged_add_tag:  * @tagged: an object that implements the %GimpTagged interface  * @tag:    a %GimpTag  *  * Adds @tag to the @tagged object. The GimpTagged::tag-added signal  * is emitted if and only if the @tag was not already assigned to this  * object.  **/
end_comment

begin_function
name|void
DECL|function|gimp_tagged_add_tag (GimpTagged * tagged,GimpTag * tag)
name|gimp_tagged_add_tag
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GimpTag
modifier|*
name|tag
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TAGGED
argument_list|(
name|tagged
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|tag
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TAGGED_GET_INTERFACE
argument_list|(
name|tagged
argument_list|)
operator|->
name|add_tag
argument_list|(
name|tagged
argument_list|,
name|tag
argument_list|)
condition|)
block|{
name|g_signal_emit
argument_list|(
name|tagged
argument_list|,
name|gimp_tagged_signals
index|[
name|TAG_ADDED
index|]
argument_list|,
literal|0
argument_list|,
name|tag
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_tagged_remove_tag:  * @tagged: an object that implements the %GimpTagged interface  * @tag:    a %GimpTag  *  * Removes @tag from the @tagged object. The GimpTagged::tag-removed  * signal is emitted if and only if the @tag was actually assigned to  * this object.  **/
end_comment

begin_function
name|void
DECL|function|gimp_tagged_remove_tag (GimpTagged * tagged,GimpTag * tag)
name|gimp_tagged_remove_tag
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GimpTag
modifier|*
name|tag
parameter_list|)
block|{
name|GList
modifier|*
name|tag_iter
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TAGGED
argument_list|(
name|tagged
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|tag
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|tag_iter
operator|=
name|gimp_tagged_get_tags
argument_list|(
name|tagged
argument_list|)
init|;
name|tag_iter
condition|;
name|tag_iter
operator|=
name|g_list_next
argument_list|(
name|tag_iter
argument_list|)
control|)
block|{
name|GimpTag
modifier|*
name|tag_ref
init|=
name|tag_iter
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_tag_equals
argument_list|(
name|tag_ref
argument_list|,
name|tag
argument_list|)
condition|)
block|{
name|g_object_ref
argument_list|(
name|tag_ref
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TAGGED_GET_INTERFACE
argument_list|(
name|tagged
argument_list|)
operator|->
name|remove_tag
argument_list|(
name|tagged
argument_list|,
name|tag_ref
argument_list|)
condition|)
block|{
name|g_signal_emit
argument_list|(
name|tagged
argument_list|,
name|gimp_tagged_signals
index|[
name|TAG_REMOVED
index|]
argument_list|,
literal|0
argument_list|,
name|tag_ref
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|tag_ref
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_tagged_set_tags:  * @tagged: an object that implements the %GimpTagged interface  * @tags:   a list of tags  *  * Sets the list of tags assigned to this object. The passed list of  * tags is copied and should be freed by the caller.  **/
end_comment

begin_function
name|void
DECL|function|gimp_tagged_set_tags (GimpTagged * tagged,GList * tags)
name|gimp_tagged_set_tags
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GList
modifier|*
name|tags
parameter_list|)
block|{
name|GList
modifier|*
name|old_tags
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TAGGED
argument_list|(
name|tagged
argument_list|)
argument_list|)
expr_stmt|;
name|old_tags
operator|=
name|g_list_copy
argument_list|(
name|gimp_tagged_get_tags
argument_list|(
name|tagged
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|old_tags
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
name|gimp_tagged_remove_tag
argument_list|(
name|tagged
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|old_tags
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|tags
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tagged_add_tag
argument_list|(
name|tagged
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_tagged_get_tags:  * @tagged: an object that implements the %GimpTagged interface  *  * Returns the list of tags assigned to this object. The returned %GList  * is owned by the @tagged object and must not be modified or destroyed.  *  * Return value: a list of tags  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_tagged_get_tags (GimpTagged * tagged)
name|gimp_tagged_get_tags
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TAGGED
argument_list|(
name|tagged
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_TAGGED_GET_INTERFACE
argument_list|(
name|tagged
argument_list|)
operator|->
name|get_tags
argument_list|(
name|tagged
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_tagged_get_identifier:  * @tagged: an object that implements the %GimpTagged interface  *  * Returns an identifier string which uniquely identifies the tagged  * object. Two different objects must have unique identifiers but may  * have the same checksum (which will be the case if one object is a  * copy of the other). The identifier must be the same across  * sessions, so for example an instance pointer cannot be used as an  * identifier.  *  * Return value: a newly allocated string containing unique identifier  * of the object. It must be freed using #g_free.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_tagged_get_identifier (GimpTagged * tagged)
name|gimp_tagged_get_identifier
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TAGGED
argument_list|(
name|tagged
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_TAGGED_GET_INTERFACE
argument_list|(
name|tagged
argument_list|)
operator|->
name|get_identifier
argument_list|(
name|tagged
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_tagged_get_checksum:  * @tagged: an object that implements the %GimpTagged interface  *  * Returns the checksum of the @tagged object. It is used to remap the  * tags for an object for which the identifier has changed, for  * example if the user has renamed a data file since the last session.  *  * If the object does not want to support such remapping (objects not  * stored in file for example) it can return #NULL.  *  * Return value: checksum string if object needs identifier remapping,  * #NULL otherwise. Returned string must be freed with #g_free().  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_tagged_get_checksum (GimpTagged * tagged)
name|gimp_tagged_get_checksum
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TAGGED
argument_list|(
name|tagged
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GIMP_TAGGED_GET_INTERFACE
argument_list|(
name|tagged
argument_list|)
operator|->
name|get_checksum
argument_list|(
name|tagged
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_tagged_has_tag:  * @tagged: an object that implements the %GimpTagged interface  * @tag:    a %GimpTag  *  * Return value: #TRUE if the object has @tag, #FALSE otherwise.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_tagged_has_tag (GimpTagged * tagged,GimpTag * tag)
name|gimp_tagged_has_tag
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GimpTag
modifier|*
name|tag
parameter_list|)
block|{
name|GList
modifier|*
name|tag_iter
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TAGGED
argument_list|(
name|tagged
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|tag
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|tag_iter
operator|=
name|gimp_tagged_get_tags
argument_list|(
name|tagged
argument_list|)
init|;
name|tag_iter
condition|;
name|tag_iter
operator|=
name|g_list_next
argument_list|(
name|tag_iter
argument_list|)
control|)
block|{
if|if
condition|(
name|gimp_tag_equals
argument_list|(
name|tag_iter
operator|->
name|data
argument_list|,
name|tag
argument_list|)
condition|)
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

