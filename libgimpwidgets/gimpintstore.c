begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpintstore.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpintstore.h"
end_include

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
name|NULL
block|,
comment|/* class_init     */
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
block|}
return|return
name|store_type
return|;
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

