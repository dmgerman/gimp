begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdatalist.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"gimpdata.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatalist.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_data_list_class_init
parameter_list|(
name|GimpDataListClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_list_init
parameter_list|(
name|GimpDataList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_list_add
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
name|gimp_data_list_remove
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
name|gimp_data_list_uniquefy_data_name
parameter_list|(
name|GimpDataList
modifier|*
name|data_list
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
name|gimp_data_list_object_renamed_callback
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|GimpDataList
modifier|*
name|data_list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_data_list_data_compare_func
parameter_list|(
name|gconstpointer
name|first
parameter_list|,
name|gconstpointer
name|second
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpListClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_data_list_get_type (void)
name|gimp_data_list_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
name|GtkTypeInfo
name|info
init|=
block|{
literal|"GimpDataList"
block|,
sizeof|sizeof
argument_list|(
name|GimpDataList
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpDataListClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_data_list_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_data_list_init
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
name|type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_LIST
argument_list|,
operator|&
name|info
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_list_class_init (GimpDataListClass * klass)
name|gimp_data_list_class_init
parameter_list|(
name|GimpDataListClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpContainerClass
modifier|*
name|container_class
decl_stmt|;
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
name|GIMP_TYPE_LIST
argument_list|)
expr_stmt|;
name|container_class
operator|->
name|add
operator|=
name|gimp_data_list_add
expr_stmt|;
name|container_class
operator|->
name|remove
operator|=
name|gimp_data_list_remove
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_list_init (GimpDataList * list)
name|gimp_data_list_init
parameter_list|(
name|GimpDataList
modifier|*
name|list
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_list_add (GimpContainer * container,GimpObject * object)
name|gimp_data_list_add
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
name|gimp_data_list_uniquefy_data_name
argument_list|(
name|GIMP_DATA_LIST
argument_list|(
name|container
argument_list|)
argument_list|,
name|object
argument_list|)
expr_stmt|;
name|list
operator|->
name|list
operator|=
name|g_list_insert_sorted
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|object
argument_list|,
name|gimp_data_list_data_compare_func
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
literal|"name_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_data_list_object_renamed_callback
argument_list|)
argument_list|,
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_list_remove (GimpContainer * container,GimpObject * object)
name|gimp_data_list_remove
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
name|gtk_signal_disconnect_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|gimp_data_list_object_renamed_callback
argument_list|,
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
name|GimpContainer
modifier|*
DECL|function|gimp_data_list_new (GtkType children_type)
name|gimp_data_list_new
parameter_list|(
name|GtkType
name|children_type
parameter_list|)
block|{
name|GimpDataList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gtk_type_is_a
argument_list|(
name|children_type
argument_list|,
name|GIMP_TYPE_DATA
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|list
operator|=
name|GIMP_DATA_LIST
argument_list|(
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_DATA_LIST
argument_list|)
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
name|GIMP_CONTAINER_POLICY_STRONG
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
name|void
DECL|function|gimp_data_list_uniquefy_data_name (GimpDataList * data_list,GimpObject * object)
name|gimp_data_list_uniquefy_data_name
parameter_list|(
name|GimpDataList
modifier|*
name|data_list
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|GList
modifier|*
name|base_list
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GList
modifier|*
name|list2
decl_stmt|;
name|GimpObject
modifier|*
name|object2
decl_stmt|;
name|gint
name|unique_ext
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
name|new_name
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|ext
decl_stmt|;
name|gboolean
name|have
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DATA_LIST
argument_list|(
name|data_list
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|base_list
operator|=
name|GIMP_LIST
argument_list|(
name|data_list
argument_list|)
operator|->
name|list
expr_stmt|;
name|have
operator|=
name|gimp_container_have
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|data_list
argument_list|)
argument_list|,
name|object
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|base_list
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
name|object2
operator|=
name|GIMP_OBJECT
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|object
operator|!=
name|object2
operator|&&
name|strcmp
argument_list|(
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|object2
argument_list|)
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ext
operator|=
name|strrchr
argument_list|(
name|object
operator|->
name|name
argument_list|,
literal|'#'
argument_list|)
expr_stmt|;
if|if
condition|(
name|ext
condition|)
block|{
name|gchar
modifier|*
name|ext_str
decl_stmt|;
name|unique_ext
operator|=
name|atoi
argument_list|(
name|ext
operator|+
literal|1
argument_list|)
expr_stmt|;
name|ext_str
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d"
argument_list|,
name|unique_ext
argument_list|)
expr_stmt|;
comment|/*  check if the extension really is of the form "#<n>"  */
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|ext_str
argument_list|,
name|ext
operator|+
literal|1
argument_list|)
condition|)
block|{
operator|*
name|ext
operator|=
literal|'\0'
expr_stmt|;
block|}
else|else
block|{
name|unique_ext
operator|=
literal|0
expr_stmt|;
block|}
name|g_free
argument_list|(
name|ext_str
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|unique_ext
operator|=
literal|0
expr_stmt|;
block|}
do|do
block|{
name|unique_ext
operator|++
expr_stmt|;
name|g_free
argument_list|(
name|new_name
argument_list|)
expr_stmt|;
name|new_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s#%d"
argument_list|,
name|object
operator|->
name|name
argument_list|,
name|unique_ext
argument_list|)
expr_stmt|;
for|for
control|(
name|list2
operator|=
name|base_list
init|;
name|list2
condition|;
name|list2
operator|=
name|g_list_next
argument_list|(
name|list2
argument_list|)
control|)
block|{
name|object2
operator|=
name|GIMP_OBJECT
argument_list|(
name|list2
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|object
operator|==
name|object2
condition|)
continue|continue;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|object2
operator|->
name|name
argument_list|,
name|new_name
argument_list|)
condition|)
break|break;
block|}
block|}
do|while
condition|(
name|list2
condition|)
do|;
if|if
condition|(
name|have
condition|)
name|gtk_signal_handler_block_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|gimp_data_list_object_renamed_callback
argument_list|,
name|data_list
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|object
argument_list|,
name|new_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|have
condition|)
name|gtk_signal_handler_unblock_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|gimp_data_list_object_renamed_callback
argument_list|,
name|data_list
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|new_name
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|have
condition|)
block|{
name|gint
name|old_index
decl_stmt|;
name|gint
name|new_index
init|=
literal|0
decl_stmt|;
name|old_index
operator|=
name|g_list_index
argument_list|(
name|base_list
argument_list|,
name|object
argument_list|)
expr_stmt|;
for|for
control|(
name|list2
operator|=
name|base_list
init|;
name|list2
condition|;
name|list2
operator|=
name|g_list_next
argument_list|(
name|list2
argument_list|)
control|)
block|{
name|object2
operator|=
name|GIMP_OBJECT
argument_list|(
name|list2
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|object
operator|==
name|object2
condition|)
continue|continue;
if|if
condition|(
name|strcmp
argument_list|(
name|object
operator|->
name|name
argument_list|,
name|object2
operator|->
name|name
argument_list|)
operator|>
literal|0
condition|)
name|new_index
operator|++
expr_stmt|;
else|else
break|break;
block|}
if|if
condition|(
name|new_index
operator|!=
name|old_index
condition|)
block|{
name|gimp_container_reorder
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|data_list
argument_list|)
argument_list|,
name|object
argument_list|,
name|new_index
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_list_object_renamed_callback (GimpObject * object,GimpDataList * data_list)
name|gimp_data_list_object_renamed_callback
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|GimpDataList
modifier|*
name|data_list
parameter_list|)
block|{
name|gimp_data_list_uniquefy_data_name
argument_list|(
name|data_list
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_data_list_data_compare_func (gconstpointer first,gconstpointer second)
name|gimp_data_list_data_compare_func
parameter_list|(
name|gconstpointer
name|first
parameter_list|,
name|gconstpointer
name|second
parameter_list|)
block|{
return|return
name|strcmp
argument_list|(
operator|(
operator|(
specifier|const
name|GimpObject
operator|*
operator|)
name|first
operator|)
operator|->
name|name
argument_list|,
operator|(
operator|(
specifier|const
name|GimpObject
operator|*
operator|)
name|second
operator|)
operator|->
name|name
argument_list|)
return|;
block|}
end_function

end_unit

