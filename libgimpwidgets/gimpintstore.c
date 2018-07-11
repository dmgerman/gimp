begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpintstore.c  * Copyright (C) 2004-2007  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpintstore.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimpintstore  * @title: GimpIntStore  * @short_description: A model for integer based name-value pairs  *                     (e.g. enums)  *  * A model for integer based name-value pairs (e.g. enums)  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2ba503bf0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_USER_DATA_TYPE
name|PROP_USER_DATA_TYPE
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpIntStorePrivate
struct|struct
name|_GimpIntStorePrivate
block|{
DECL|member|empty_iter
name|GtkTreeIter
modifier|*
name|empty_iter
decl_stmt|;
DECL|member|user_data_type
name|GType
name|user_data_type
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (obj)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(((GimpIntStore *) (obj))->priv)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_int_store_tree_model_init
parameter_list|(
name|GtkTreeModelIface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_int_store_constructed
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
name|gimp_int_store_finalize
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
name|gimp_int_store_set_property
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
name|gimp_int_store_get_property
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
name|void
name|gimp_int_store_row_inserted
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreePath
modifier|*
name|path
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_int_store_row_deleted
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreePath
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_int_store_add_empty
parameter_list|(
name|GimpIntStore
modifier|*
name|store
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpIntStore
argument_list|,
argument|gimp_int_store
argument_list|,
argument|GTK_TYPE_LIST_STORE
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GTK_TYPE_TREE_MODEL,                                                 gimp_int_store_tree_model_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_int_store_parent_class
end_define

begin_decl_stmt
specifier|static
name|GtkTreeModelIface
modifier|*
name|parent_iface
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_int_store_class_init (GimpIntStoreClass * klass)
name|gimp_int_store_class_init
parameter_list|(
name|GimpIntStoreClass
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
name|constructed
operator|=
name|gimp_int_store_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_int_store_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_int_store_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_int_store_get_property
expr_stmt|;
comment|/**    * GimpIntStore:user-data-type:    *    * Sets the #GType for the GIMP_INT_STORE_USER_DATA column.    *    * You need to set this property when constructing the store if you want    * to use the GIMP_INT_STORE_USER_DATA column and want to have the store    * handle ref-counting of your user data.    *    * Since: 2.4    */
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_USER_DATA_TYPE
argument_list|,
name|g_param_spec_gtype
argument_list|(
literal|"user-data-type"
argument_list|,
literal|"User Data Type"
argument_list|,
literal|"The GType of the user_data column"
argument_list|,
name|G_TYPE_NONE
argument_list|,
name|G_PARAM_CONSTRUCT_ONLY
operator||
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpIntStorePrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_int_store_tree_model_init (GtkTreeModelIface * iface)
name|gimp_int_store_tree_model_init
parameter_list|(
name|GtkTreeModelIface
modifier|*
name|iface
parameter_list|)
block|{
name|parent_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|iface
argument_list|)
expr_stmt|;
name|iface
operator|->
name|row_inserted
operator|=
name|gimp_int_store_row_inserted
expr_stmt|;
name|iface
operator|->
name|row_deleted
operator|=
name|gimp_int_store_row_deleted
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_int_store_init (GimpIntStore * store)
name|gimp_int_store_init
parameter_list|(
name|GimpIntStore
modifier|*
name|store
parameter_list|)
block|{
name|store
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|store
argument_list|,
name|GIMP_TYPE_INT_STORE
argument_list|,
name|GimpIntStorePrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_int_store_constructed (GObject * object)
name|gimp_int_store_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpIntStore
modifier|*
name|store
init|=
name|GIMP_INT_STORE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpIntStorePrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
decl_stmt|;
name|GType
name|types
index|[
name|GIMP_INT_STORE_NUM_COLUMNS
index|]
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|types
index|[
name|GIMP_INT_STORE_VALUE
index|]
operator|=
name|G_TYPE_INT
expr_stmt|;
name|types
index|[
name|GIMP_INT_STORE_LABEL
index|]
operator|=
name|G_TYPE_STRING
expr_stmt|;
name|types
index|[
name|GIMP_INT_STORE_ICON_NAME
index|]
operator|=
name|G_TYPE_STRING
expr_stmt|;
name|types
index|[
name|GIMP_INT_STORE_PIXBUF
index|]
operator|=
name|GDK_TYPE_PIXBUF
expr_stmt|;
name|types
index|[
name|GIMP_INT_STORE_USER_DATA
index|]
operator|=
operator|(
name|priv
operator|->
name|user_data_type
operator|!=
name|G_TYPE_NONE
condition|?
name|priv
operator|->
name|user_data_type
else|:
name|G_TYPE_POINTER
operator|)
expr_stmt|;
name|types
index|[
name|GIMP_INT_STORE_ABBREV
index|]
operator|=
name|G_TYPE_STRING
expr_stmt|;
name|gtk_list_store_set_column_types
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|GIMP_INT_STORE_NUM_COLUMNS
argument_list|,
name|types
argument_list|)
expr_stmt|;
name|gimp_int_store_add_empty
argument_list|(
name|store
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_int_store_finalize (GObject * object)
name|gimp_int_store_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpIntStorePrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|priv
operator|->
name|empty_iter
argument_list|,
name|gtk_tree_iter_free
argument_list|)
expr_stmt|;
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
DECL|function|gimp_int_store_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_int_store_set_property
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
name|GimpIntStorePrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
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
name|PROP_USER_DATA_TYPE
case|:
name|priv
operator|->
name|user_data_type
operator|=
name|g_value_get_gtype
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
DECL|function|gimp_int_store_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_int_store_get_property
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
name|GimpIntStorePrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
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
name|PROP_USER_DATA_TYPE
case|:
name|g_value_set_gtype
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|user_data_type
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
DECL|function|gimp_int_store_row_inserted (GtkTreeModel * model,GtkTreePath * path,GtkTreeIter * iter)
name|gimp_int_store_row_inserted
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreePath
modifier|*
name|path
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|GimpIntStore
modifier|*
name|store
init|=
name|GIMP_INT_STORE
argument_list|(
name|model
argument_list|)
decl_stmt|;
name|GimpIntStorePrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
decl_stmt|;
if|if
condition|(
name|parent_iface
operator|->
name|row_inserted
condition|)
name|parent_iface
operator|->
name|row_inserted
argument_list|(
name|model
argument_list|,
name|path
argument_list|,
name|iter
argument_list|)
expr_stmt|;
if|if
condition|(
name|priv
operator|->
name|empty_iter
operator|&&
name|memcmp
argument_list|(
name|iter
argument_list|,
name|priv
operator|->
name|empty_iter
argument_list|,
sizeof|sizeof
argument_list|(
name|GtkTreeIter
argument_list|)
argument_list|)
condition|)
block|{
name|gtk_list_store_remove
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|priv
operator|->
name|empty_iter
argument_list|)
expr_stmt|;
name|gtk_tree_iter_free
argument_list|(
name|priv
operator|->
name|empty_iter
argument_list|)
expr_stmt|;
name|priv
operator|->
name|empty_iter
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_int_store_row_deleted (GtkTreeModel * model,GtkTreePath * path)
name|gimp_int_store_row_deleted
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreePath
modifier|*
name|path
parameter_list|)
block|{
if|if
condition|(
name|parent_iface
operator|->
name|row_deleted
condition|)
name|parent_iface
operator|->
name|row_deleted
argument_list|(
name|model
argument_list|,
name|path
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_int_store_add_empty (GimpIntStore * store)
name|gimp_int_store_add_empty
parameter_list|(
name|GimpIntStore
modifier|*
name|store
parameter_list|)
block|{
name|GimpIntStorePrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
decl_stmt|;
name|GtkTreeIter
name|iter
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|priv
operator|->
name|empty_iter
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|gtk_list_store_prepend
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_INT_STORE_VALUE
argument_list|,
operator|-
literal|1
argument_list|,
comment|/* This string appears in an empty menu as in                        * "nothing selected and nothing to select"                        */
name|GIMP_INT_STORE_LABEL
argument_list|,
operator|(
name|_
argument_list|(
literal|"(Empty)"
argument_list|)
operator|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|priv
operator|->
name|empty_iter
operator|=
name|gtk_tree_iter_copy
argument_list|(
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_int_store_new:  *  * Creates a #GtkListStore with a number of useful columns.  * #GimpIntStore is especially useful if the items you want to store  * are identified using an integer value.  *  * Return value: a new #GimpIntStore.  *  * Since: 2.2  **/
end_comment

begin_function
name|GtkListStore
modifier|*
DECL|function|gimp_int_store_new (void)
name|gimp_int_store_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_INT_STORE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_int_store_lookup_by_value:  * @model: a #GimpIntStore  * @value: an integer value to lookup in the @model  * @iter:  return location for the iter of the given @value  *  * Iterate over the @model looking for @value.  *  * Return value: %TRUE if the value has been located and @iter is  *               valid, %FALSE otherwise.  *  * Since: 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_int_store_lookup_by_value (GtkTreeModel * model,gint value,GtkTreeIter * iter)
name|gimp_int_store_lookup_by_value
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|gint
name|value
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|gboolean
name|iter_valid
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_TREE_MODEL
argument_list|(
name|model
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|iter
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
name|iter
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
name|iter
argument_list|)
control|)
block|{
name|gint
name|this
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|GIMP_INT_STORE_VALUE
argument_list|,
operator|&
name|this
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|this
operator|==
name|value
condition|)
break|break;
block|}
return|return
name|iter_valid
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_int_store_lookup_by_user_data:  * @model: a #GimpIntStore  * @user_data: a gpointer "user-data" to lookup in the @model  * @iter:  return location for the iter of the given @user_data  *  * Iterate over the @model looking for @user_data.  *  * Return value: %TRUE if the user-data has been located and @iter is  *               valid, %FALSE otherwise.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_int_store_lookup_by_user_data (GtkTreeModel * model,gpointer user_data,GtkTreeIter * iter)
name|gimp_int_store_lookup_by_user_data
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|gboolean
name|iter_valid
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_TREE_MODEL
argument_list|(
name|model
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|iter
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
name|iter
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
name|iter
argument_list|)
control|)
block|{
name|gpointer
name|this
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|GIMP_INT_STORE_USER_DATA
argument_list|,
operator|&
name|this
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|this
operator|==
name|user_data
condition|)
break|break;
block|}
return|return
operator|(
name|gboolean
operator|)
name|iter_valid
return|;
block|}
end_function

end_unit

