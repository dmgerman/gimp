begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpintstore.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_function_decl
specifier|static
name|void
name|gimp_int_store_class_init
parameter_list|(
name|GimpIntStoreClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

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
name|gimp_int_store_init
parameter_list|(
name|GimpIntStore
modifier|*
name|store
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkListStoreClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_iface
specifier|static
name|GtkTreeModelIface
modifier|*
name|parent_iface
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_int_store_get_type (void)
name|gimp_int_store_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|store_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|store_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|store_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpIntStoreClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init      */
name|NULL
block|,
comment|/* base_finalize  */
operator|(
name|GClassInitFunc
operator|)
name|gimp_int_store_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpIntStore
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_int_store_init
block|}
decl_stmt|;
specifier|static
specifier|const
name|GInterfaceInfo
name|iface_info
init|=
block|{
operator|(
name|GInterfaceInitFunc
operator|)
name|gimp_int_store_tree_model_init
block|,
name|NULL
block|,
comment|/* iface_finalize */
name|NULL
comment|/* iface_data     */
block|}
decl_stmt|;
name|store_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_LIST_STORE
argument_list|,
literal|"GimpIntStore"
argument_list|,
operator|&
name|store_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|store_type
argument_list|,
name|GTK_TYPE_TREE_MODEL
argument_list|,
operator|&
name|iface_info
argument_list|)
expr_stmt|;
block|}
return|return
name|store_type
return|;
block|}
end_function

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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_int_store_finalize
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
name|GType
name|types
index|[
name|GIMP_INT_STORE_NUM_COLUMNS
index|]
init|=
block|{
name|G_TYPE_INT
block|,
comment|/*  GIMP_INT_STORE_VALUE      */
name|G_TYPE_STRING
block|,
comment|/*  GIMP_INT_STORE_LABEL      */
name|G_TYPE_STRING
block|,
comment|/*  GIMP_INT_STORE_STOCK_ID   */
name|GDK_TYPE_PIXBUF
block|,
comment|/*  GIMP_INT_STORE_PIXBUF     */
name|G_TYPE_POINTER
comment|/*  GIMP_INT_STORE_USER_DATA  */
block|}
decl_stmt|;
name|store
operator|->
name|empty_iter
operator|=
name|NULL
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
name|GimpIntStore
modifier|*
name|store
init|=
name|GIMP_INT_STORE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|store
operator|->
name|empty_iter
condition|)
block|{
name|gtk_tree_iter_free
argument_list|(
name|store
operator|->
name|empty_iter
argument_list|)
expr_stmt|;
name|store
operator|->
name|empty_iter
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
name|store
operator|->
name|empty_iter
operator|&&
name|memcmp
argument_list|(
name|iter
argument_list|,
name|store
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
name|store
operator|->
name|empty_iter
argument_list|)
expr_stmt|;
name|gtk_tree_iter_free
argument_list|(
name|store
operator|->
name|empty_iter
argument_list|)
expr_stmt|;
name|store
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
if|if
condition|(
name|gtk_tree_model_iter_n_children
argument_list|(
name|model
argument_list|,
name|NULL
argument_list|)
operator|==
literal|0
condition|)
name|gimp_int_store_add_empty
argument_list|(
name|GIMP_INT_STORE
argument_list|(
name|model
argument_list|)
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
name|g_return_if_fail
argument_list|(
name|store
operator|->
name|empty_iter
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|store
operator|->
name|empty_iter
operator|=
name|g_new
argument_list|(
name|GtkTreeIter
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_list_store_prepend
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|store
operator|->
name|empty_iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|store
operator|->
name|empty_iter
argument_list|,
name|GIMP_INT_STORE_VALUE
argument_list|,
operator|-
literal|1
argument_list|,
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
block|}
end_function

begin_comment
comment|/**  * gimp_int_store_new:  *  * Creates a #GtkListStore with a number of useful columns.  * #GimpIntStore is especially useful if the items you want to store  * are identified using an integer value.  *  * Return value: a new #GimpIntStore.  *  * Since: GIMP 2.2  **/
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
comment|/**  * gimp_int_store_lookup_by_value:  * @model: a #GimpIntStore  * @value: an integer value to lookup in the @model  * @iter:  return location for the iter of the given @value  *  * Iterate over the @model looking for @value.  *  * Return value: %TRUE if the value has been located and @iter is  *               valid, %FALSE otherwise.  *  * Since: GIMP 2.2  **/
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

end_unit

