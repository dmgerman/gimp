begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_list_class_init
parameter_list|(
name|GimpListClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_list_init
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_list_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_list_add
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
name|gimp_list_remove
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
name|gimp_list_reorder
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
name|gboolean
name|gimp_list_have
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
name|gimp_list_foreach
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpObject
modifier|*
name|gimp_list_get_child_by_name
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpObject
modifier|*
name|gimp_list_get_child_by_index
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_list_get_child_index
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpContainerClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_list_get_type (void)
name|gimp_list_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|list_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|list_type
condition|)
block|{
name|GtkTypeInfo
name|list_info
init|=
block|{
literal|"GimpList"
block|,
sizeof|sizeof
argument_list|(
name|GimpList
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpListClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_list_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_list_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|list_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_CONTAINER
argument_list|,
operator|&
name|list_info
argument_list|)
expr_stmt|;
block|}
return|return
name|list_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_class_init (GimpListClass * klass)
name|gimp_list_class_init
parameter_list|(
name|GimpListClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpContainerClass
modifier|*
name|container_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|container_class
operator|=
operator|(
name|GimpContainerClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_CONTAINER
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_list_destroy
expr_stmt|;
name|container_class
operator|->
name|add
operator|=
name|gimp_list_add
expr_stmt|;
name|container_class
operator|->
name|remove
operator|=
name|gimp_list_remove
expr_stmt|;
name|container_class
operator|->
name|reorder
operator|=
name|gimp_list_reorder
expr_stmt|;
name|container_class
operator|->
name|have
operator|=
name|gimp_list_have
expr_stmt|;
name|container_class
operator|->
name|foreach
operator|=
name|gimp_list_foreach
expr_stmt|;
name|container_class
operator|->
name|get_child_by_name
operator|=
name|gimp_list_get_child_by_name
expr_stmt|;
name|container_class
operator|->
name|get_child_by_index
operator|=
name|gimp_list_get_child_by_index
expr_stmt|;
name|container_class
operator|->
name|get_child_index
operator|=
name|gimp_list_get_child_index
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_init (GimpList * list)
name|gimp_list_init
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|)
block|{
name|list
operator|->
name|list
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_destroy (GtkObject * object)
name|gimp_list_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|object
argument_list|)
expr_stmt|;
while|while
condition|(
name|list
operator|->
name|list
condition|)
block|{
name|gimp_container_remove
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|list
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|list
operator|->
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_add (GimpContainer * container,GimpObject * object)
name|gimp_list_add
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
name|GimpList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|container
argument_list|)
expr_stmt|;
name|list
operator|->
name|list
operator|=
name|g_list_prepend
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_remove (GimpContainer * container,GimpObject * object)
name|gimp_list_remove
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
name|GimpList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|container
argument_list|)
expr_stmt|;
name|list
operator|->
name|list
operator|=
name|g_list_remove
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_reorder (GimpContainer * container,GimpObject * object,gint new_index)
name|gimp_list_reorder
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
name|GimpList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|container
argument_list|)
expr_stmt|;
name|list
operator|->
name|list
operator|=
name|g_list_remove
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_index
operator|==
operator|-
literal|1
operator|||
name|new_index
operator|==
name|container
operator|->
name|num_children
operator|-
literal|1
condition|)
name|list
operator|->
name|list
operator|=
name|g_list_append
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|object
argument_list|)
expr_stmt|;
else|else
name|list
operator|->
name|list
operator|=
name|g_list_insert
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|object
argument_list|,
name|new_index
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_list_have (GimpContainer * container,GimpObject * object)
name|gimp_list_have
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
name|GimpList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|container
argument_list|)
expr_stmt|;
return|return
name|g_list_find
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|object
argument_list|)
condition|?
name|TRUE
else|:
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_foreach (GimpContainer * container,GFunc func,gpointer user_data)
name|gimp_list_foreach
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|container
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|func
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpContainer
modifier|*
DECL|function|gimp_list_new (GtkType children_type,GimpContainerPolicy policy)
name|gimp_list_new
parameter_list|(
name|GtkType
name|children_type
parameter_list|,
name|GimpContainerPolicy
name|policy
parameter_list|)
block|{
name|GimpList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gtk_type_is_a
argument_list|(
name|children_type
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|policy
operator|==
name|GIMP_CONTAINER_POLICY_STRONG
operator|||
name|policy
operator|==
name|GIMP_CONTAINER_POLICY_WEAK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|list
operator|=
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_LIST
argument_list|)
expr_stmt|;
name|GIMP_CONTAINER
argument_list|(
name|list
argument_list|)
operator|->
name|children_type
operator|=
name|children_type
expr_stmt|;
name|GIMP_CONTAINER
argument_list|(
name|list
argument_list|)
operator|->
name|policy
operator|=
name|policy
expr_stmt|;
return|return
name|GIMP_CONTAINER
argument_list|(
name|list
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpObject
modifier|*
DECL|function|gimp_list_get_child_by_name (GimpContainer * container,gchar * name)
name|gimp_list_get_child_by_name
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpList
modifier|*
name|list
decl_stmt|;
name|GimpObject
modifier|*
name|object
decl_stmt|;
name|GList
modifier|*
name|glist
decl_stmt|;
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|container
argument_list|)
expr_stmt|;
for|for
control|(
name|glist
operator|=
name|list
operator|->
name|list
init|;
name|glist
condition|;
name|glist
operator|=
name|g_list_next
argument_list|(
name|glist
argument_list|)
control|)
block|{
name|object
operator|=
operator|(
name|GimpObject
operator|*
operator|)
name|glist
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|object
operator|->
name|name
argument_list|,
name|name
argument_list|)
condition|)
return|return
name|object
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|GimpObject
modifier|*
DECL|function|gimp_list_get_child_by_index (GimpContainer * container,gint index)
name|gimp_list_get_child_by_index
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|GimpList
modifier|*
name|list
decl_stmt|;
name|GList
modifier|*
name|glist
decl_stmt|;
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|container
argument_list|)
expr_stmt|;
name|glist
operator|=
name|g_list_nth
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|index
argument_list|)
expr_stmt|;
if|if
condition|(
name|glist
condition|)
return|return
operator|(
name|GimpObject
operator|*
operator|)
name|glist
operator|->
name|data
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_list_get_child_index (GimpContainer * container,GimpObject * object)
name|gimp_list_get_child_index
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
name|GimpList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|container
argument_list|)
expr_stmt|;
return|return
name|g_list_index
argument_list|(
name|list
operator|->
name|list
argument_list|,
operator|(
name|gpointer
operator|)
name|object
argument_list|)
return|;
block|}
end_function

end_unit

